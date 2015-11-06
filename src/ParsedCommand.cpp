#include "ParsedCommand.hpp"
#include <unistd.h> 
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

ParsedCommand::ParsedCommand(string line) : commandLine(line)
{
  commands.clear(); 
}

ParsedCommand::~ParsedCommand()
{

}

string ParsedCommand::getLine()
{
  return commandLine;
}

void ParsedCommand::setLine(string line)
{
  commandLine = line;
}

Command ParsedCommand::getCommand(unsigned i)
{
  assert(i < commands.size());
  return commands[i];
}

void ParsedCommand::setCommand(unsigned i, Command c)
{
  assert(i < commands.size());
  Connector connect = c.getConnector();
  if(connect.getRepresentation() == ";")
    commands[i] = Command(c.getExecutable().getExecutable(), c.getArguments().getArguments(), Semicolon());
  if(connect.getRepresentation() == "&&")
    commands[i] = Command(c.getExecutable().getExecutable(), c.getArguments().getArguments(), DoubleAnd());
  if(connect.getRepresentation() == "||")
    commands[i] = Command(c.getExecutable().getExecutable(), c.getArguments().getArguments(), DoubleOr());
    
}

void ParsedCommand::addCommand(Command c)
{
  commands.push_back(Command(c.getExecutable().getExecutable(), c.getArguments().getArguments(), c.getConnector()));
}

void ParsedCommand::deleteLastCommand()
{
  commands.pop_back();
}
vector<Command> ParsedCommand::getCommandVector()

{
  return commands;
}

void ParsedCommand::setCommandVector(vector<Command> v)
{
  commands.clear();
  for(unsigned i; i < v.size(); i++)
  {
    commands.push_back(getCommand(i));
  }
}

static bool endWithSemicolon(char* token)
{
  string s(token);
  if(s[s.size() - 1] == ';')
    return true;
  return false;
}

static bool isConnector(char* str) // Returns true if the string is a connector 
{
  vector<Connector> v;
  v.push_back(Semicolon());
  v.push_back(DoubleAnd());
  v.push_back(DoubleOr());

  string s(str);
  for(unsigned i = 0; i < v.size(); i++)
  {
    if(s == v[i].getRepresentation())
      return true;
  }
  return false;
}

static Connector recognizeConnector(char *str)
{
  assert(isConnector(str));

  vector<Connector> v;
  v.push_back(Semicolon());
  v.push_back(DoubleAnd());
  v.push_back(DoubleOr());

  string s(str);
  for(unsigned i = 0; i < v.size(); i++)
  {
    if(s == v[i].getRepresentation())
      return v[i];
  }
  return Semicolon();
}

void ParsedCommand::stripComments() // Removes comments from the command line typed by the user
{
  string str(getLine());
  char* search(strchr(const_cast<char*>(str.c_str()), '#')); //  Searches for the integer corresponding to # and return a pointer to the first occurence
  if(search != NULL) // If an occurrence has been found, the pointer is not NULL
  {
    setLine(getLine().substr(0, getLine().size()-(strlen(search)))); // Removes the part of the original command line that starts with # 
  }
}

vector<string> ParsedCommand::separateCommands() // Separate the command line in distinct commands
{
  vector<string> v;
  
  string str = "" + getLine();
  string s(str);
  if(!endWithSemicolon(const_cast<char*>(s.c_str())))
  {
    str += ";";
  }

  unsigned j = 0;
  
  for(unsigned i = 0; i < str.size(); i++)
  {
    if(str[i] == ';')
    {
      string tmp;
      for(j = j; j <= i; j++)
      {
        tmp += str[j];
      }
      v.push_back(tmp);
    }
    
    if(str[i] == '&')   
    {
      assert(i + 1 < str.size());
      if(str[i + 1] == '&')
      {
        string tmp;
        for(j = j; j <= i + 1; j++)
	{
	  tmp += str[j];
	}
	v.push_back(tmp);
      }
    }

    if(str[i] == '|')
    {
      assert(i + 1 < str.size());
      if(str[i + 1] == '|')
      {
        string tmp;
	for(j = j; j <= i + 1; j++)
	{
	  tmp += str[j];
	}
	v.push_back(tmp);
      }
    }
  }
  return v;
}

Command ParsedCommand::createCommand(string command)
{
  char* str_conv(const_cast<char*>(command.c_str()));
  char* token(strtok(str_conv, " "));

  unsigned cpt = 0;

  // Initialization of the command elements;
  string ex;
  string arg;
  Connector c = DoubleAnd();
  while(token != NULL)
  {
    if(cpt == 0) // First element of the command to parse, so it must be an executable
    { 
      if(endWithSemicolon(token))
      { 
        ex += "" + string(token);
	ex = ex.substr(0, ex.size() - 1);
	c = Semicolon();
	cpt++;
      }
      else
      {
	ex = "" + string(token);
	cpt++;
      } 
    }
    else
    {
      if(isConnector(token))
      {
        c = recognizeConnector(token);
      }
      else // If it's not an executable and not a connector, then it's an argument (if there's no argument, this loop won't be reached)
      {
	if(endWithSemicolon(token))
	{
	  if(!(arg.empty()))
	    arg += " ";
	  arg += "" + string(token);
	  arg = arg.substr(0, arg.size() - 1);
	  c = Semicolon();
        }
	else
	{
	  if(!(arg.empty()))
	    arg += " ";
	  arg += "" + string(token);
        }
      }
    }
    token = strtok(NULL, " "); 
  }
  Command cmd(ex, arg, c);
  return cmd; // The parsed command is added to the vector
}


void ParsedCommand::parse()
{
  stripComments(); // Eliminates the comments from the command line
  vector<string> v = separateCommands(); // Separates the different commands so that we can treat them one by one

  for(unsigned i = 0; i < v.size(); i++)
  {
    Command c = createCommand(v[i]);
    addCommand(c);
  }
}

void ParsedCommand::execute(bool &quit)
{
  parse();

  bool runNext = true; // Will the next instruction be ran? By default, true in case the connector is a semicolon
 // bool quit = false; // Exit rshell? By default, false because it must be triggered by the user

  for(unsigned i = 0;  i < getCommandVector().size(); i++)
  {
    bool success = false;
    bool fail = false;
    
    if(getCommand(i).getExecutable().getExecutable() == "exit") // If exit is the executable, quit value becomes true
      quit = true;

    if(quit == true || runNext == false) // If exit has been found or if the connector "refuses" to execute the next command, stop trying executing the rest of the command line
    {
      if(quit)
        cout << "Exiting rshell." << endl << endl;
      break;
    }

    char* args[3] = { const_cast<char*>(getCommand(i).getExecutable().getExecutable().c_str()), const_cast<char*>(getCommand(i).getArguments().getArguments().c_str()), NULL };
    
    pid_t c_pid, pid;
    int status;

    c_pid = fork();

    if(c_pid < 0)
    {
      perror("Error: fork failed");
      exit(1);
    }
    else if(c_pid == 0)
    {
      execvp(args[0], args);
      perror("Error: execvp failed");
      fail = true;
    }
    else if(c_pid > 0)
    {
      if((pid = wait(&status)) < 0)
      {
        perror("Error occurred during wait");
	exit(1);
      }
    }
    
    if(WIFEXITED(status)) // The child process ended normally
    {
      if(WEXITSTATUS(status) != 0)
      {
        fail = true; 
      }
      else
      {
        success = true;
      }
    }
    else
    {
      fail = true;
    }
    runNext = getCommand(i).runNext(success, fail);
  }
}

