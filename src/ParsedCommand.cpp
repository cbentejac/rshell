/**
 * \file ParsedCommand.cpp
 * \author Candice Bentejac
 * \date November 6, 2015
 * \brief Definitions of the class ParsedCommand.
 */

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


// Removes the space at the end of a string
void ParsedCommand::trimLine()
{
  while (isspace(getLine()[getLine().size() - 1]))
    setLine(getLine().substr(0, getLine().size() - 1));
}


Command ParsedCommand::getCommand(unsigned i) // Returns the Command contained 
{
  assert(i < commands.size()); // Checks that i isn't out of range
  return commands[i];
}


void ParsedCommand::setCommand(unsigned i, Command c)
{
  assert(i < commands.size()); // Checks that i isn't out of range
  if (c.getConnector().getRepresentation() == ";")
    commands[i] = Command(c.getExecutable().getExecutable(), 
                          c.getArguments().getArguments(), 
			  Semicolon()
			 );
  if (c.getConnector().getRepresentation() == "&&")
    commands[i] = Command(c.getExecutable().getExecutable(), 
                          c.getArguments().getArguments(), 
			  DoubleAnd()
			 );
  if (c.getConnector().getRepresentation() == "||")
    commands[i] = Command(c.getExecutable().getExecutable(), 
                          c.getArguments().getArguments(), 
			  DoubleOr()
			 );    
}


void ParsedCommand::addCommand(Command c)
{
  commands.push_back(Command(c.getExecutable().getExecutable(), 
                     c.getArguments().getArguments(), 
                     c.getConnector())
                    );
}


vector<Command> ParsedCommand::getCommandVector()
{
  return commands;
}


void ParsedCommand::setCommandVector(vector<Command> v)
{
  commands.clear(); // Clears commands before refilling it
  for (unsigned i; i < v.size(); i++)
    commands.push_back(getCommand(i));
}


// True if token ends with a semicolon
static bool endWithSemicolon(char* token) 
{
  string s(token);
  if (s[s.size() - 1] == ';')
    return true;
  return false;
}


// True if token ends with "&&"
static bool endWithDoubleAnd(char* token)
{
  string s(token);
  if (s.size() < 2)
    return false;
  if (s[s.size() - 1] == '&' && s[s.size() - 2] == '&')
    return true;
  return false;
}


// True if token ends with "||"
static bool endWithDoubleOr(char* token)
{
  string s(token);
  if (s.size() < 2)
    return false;
  if (s[s.size() - 1] == '|' && s[s.size() - 2] == '|')
    return true;
  return false;
}


// Returns true if str is a connector representation 
static bool isConnector(char* str) 
{
  vector<Connector> v;
  v.push_back(Semicolon());
  v.push_back(DoubleAnd());
  v.push_back(DoubleOr());

  string s(str);
  for (unsigned i = 0; i < v.size(); i++)
  {
    if (s == v[i].getRepresentation())
      return true;
  }
  return false;
}


// Returns the connector corresponding to a string representation
static Connector recognizeConnector(char* str)
{
  assert(isConnector(str)); // Checks that str is a connector 

  vector<Connector> v;
  v.push_back(Semicolon());
  v.push_back(DoubleAnd());
  v.push_back(DoubleOr());

  string s(str);
  for (unsigned i = 0; i < v.size(); i++)
  {
    if (s == v[i].getRepresentation())
      return v[i];
  }

  return Semicolon(); // Should never be reached, but just in case
}


// Removes comments from the command line typed by the user 
void ParsedCommand::stripComments() 
{
  string str(getLine());
  // Searches for the integer corresponding to # 
  char* search(strchr(const_cast<char*>(str.c_str()), '#')); 

  if (search != NULL) // If an occurrence has been found, pointer is not NULL
    // Removes the part of the original command line that starts with #
    setLine(getLine().substr(0, getLine().size()-(strlen(search))));  
}


// Separates the command line in distinct commands
vector<string> ParsedCommand::separateCommands() 
{
  vector<string> v;
  trimLine();
  string str = getLine();

  if (!getLine().empty()) // Checks that the command line is not empty; if true:
  // Directly return v to avoid trying to execute later an empty Command
  {
    unsigned j = 0; // Position of the last separation made in the command line
    
    // If the user input doesn't end with a semicolon, adds one 
    // Or, if there was another connector, replace it
    if (!endWithSemicolon(const_cast<char*>(str.c_str())))
    {
      if(endWithDoubleAnd(const_cast<char*>(str.c_str())) || endWithDoubleOr(const_cast<char*>(str.c_str())))
        str = str.substr(0, str.size() - 2);
      str += ";";
    }
  
    for (unsigned i = 0; i < str.size(); i++)
    {   
      // If the ";" connector is found, extracts and adds the substring
      if (str[i] == ';')
      {
        string tmp;
        for (j = j; j <= i; j++)
          tmp += str[j]; // Extracts the substring by copiing it
        v.push_back(tmp);
      }
     
      if (str[i] == '&') // If a "&" character is found
      {
        // Checks that there's at least one character after this one 
	assert(i + 1 < str.size()); 
	// If another & is found, extracts and adds the substring to the vector
        if (str[i + 1] == '&') 
        {
          string tmp;
          for (j = j; j <= i + 1; j++)
  	    tmp += str[j];
          v.push_back(tmp);
        }
      }

      if (str[i] == '|') // Same if a "|" character is found
      {
        assert(i + 1 < str.size()); 
        if (str[i + 1] == '|') 
        {
          string tmp;
	  for (j = j; j <= i + 1; j++)
	    tmp += str[j];
          v.push_back(tmp);
        }
      }
    }
  }
  return v;
}


Command ParsedCommand::createCommand(string command)
{
  char* str_conv(const_cast<char*>(command.c_str()));
  char* token(strtok(str_conv, " ")); // Launches tokenization

  unsigned cpt = 0; // To distinguish the executable from arguments in the loop
  // cpt == 0: 1st time in the loop and the string is necessarily an executable

  // Initialization of the command elements;
  string ex;
  string arg;
  Connector c = Semicolon();

  while (token != NULL)
  {
    if (cpt == 0) // First element of the command to parse = executable
    { 
      ex = "" + string(token);
      cpt ++;

      if (endWithSemicolon(token))
      { 
	ex = ex.substr(0, ex.size() - 1);
	c = Semicolon();
      }
      else if (endWithDoubleAnd(token))
      {
	ex = ex.substr(0, ex.size() - 2);
	c = DoubleAnd();
      }
      else if (endWithDoubleOr(token))
      {
	ex = ex.substr(0, ex.size() - 2);
	c = DoubleOr();
      }
    }
    else
    {
      if (isConnector(token)) // If it's a connector, recognize it
        c = recognizeConnector(token);
      
      // If it's not an executable and not a connector, then it's an argument
      // (If there's no argument, this loop won't be reached)
      else 
      {
        // Checks if it's the last element of the command (ends with connector)
	if (endWithSemicolon(token) || endWithDoubleAnd(token) || endWithDoubleOr(token)) 
	{ 
	  // If it's not the 1st argument for this command, adds a space
	  if (!(arg.empty())) 
	    arg += " ";

          arg += "" + string(token);
	  if (endWithSemicolon(token))
	  {
	    arg = arg.substr(0, arg.size() - 1); // Separate the argument from the connector
	    c = Semicolon();
	  }
	  else if (endWithDoubleAnd(token))
	  {
	    arg = arg.substr(0, arg.size() - 2);
	    c = DoubleAnd();
	  }
	  else
	  {
	    arg = arg.substr(0, arg.size() - 2);
	    c = DoubleOr();
	  }
        }
	else
	{
	  if (!(arg.empty()))
	    arg += " ";

          arg += "" + string(token);
        }
      }
    }
    token = strtok(NULL, " "); 
  }
  
  Command cmd(ex, arg, c); // Create the Command object with the string
  return cmd; // The parsed command is added to the vector
}


void ParsedCommand::parse()
{
  stripComments(); // Eliminates the comments from the command line
  // Separates the different commands so that we can parse them one by one
  vector<string> v = separateCommands(); 

  for (unsigned i = 0; i < v.size(); i++)
  {
    Command c = createCommand(v[i]);
    addCommand(c);
  }
}


void ParsedCommand::execute(bool &quit)
{
  parse();

  // Will the next instruction be run? By default, false
  bool runNext = true; 

  for (unsigned i = 0;  i < getCommandVector().size(); i++)
  {
    // Has the command been run normally? By default, false
    bool success = false; 
    
    // If exist is the executable and the next instruction is to be run
    if (getCommand(i).getExecutable().getExecutable() == "exit" && 
        runNext == true) 
    // quit value becomes true
      quit = true;

    // If exit has been found or if the connector "refuses" the next command:
    if (quit == true || runNext == false) 
    // Stop trying executing the rest of the command line
    {
      if (quit)
        cout << "Exiting rshell." << endl << endl;
      break;
    }

    // Designed to handle the case where there are several arguments 
    char* str = const_cast<char*>(
                getCommand(i).getArguments().getArguments().c_str()
		); // Takes the arguments list
    char* token = strtok(str, " "); // Tokenizes to determine the # of args
    vector<string> v;
    
    // The arguments are put in a vector whose size 
    while (token != NULL)
    {
      v.push_back(string(token));
      token = strtok(NULL, " ");
    }
    
    int size = v.size() + 2; // Size of args (exec + args # + null = args # + 2)
    char** args = new char*[size];
    
    for (int j = 0; j < size; j++)
    {
      if (j == 0) // Executable
        args[j] = const_cast<char*>(getCommand(i).getExecutable().getExecutable().c_str());
      else if (j == size - 1) // NULL
        args[j] = NULL;
      else // Arguments
        args[j] = const_cast<char*>(v[j - 1].c_str());
    }

    pid_t c_pid, pid;
    int status;

    c_pid = fork();

    if (c_pid < 0) // Fork problem
    {
      perror("Error: fork failed");
      exit(1);
    }
    else if (c_pid == 0) // Child process
    {
      execvp(args[0], args);
      perror("Error: execvp failed");
    }
    else if (c_pid > 0) // Parent process
    {
      if ((pid = wait(&status)) < 0)
      {
        perror("Error occurred during wait");
	exit(1);
      }
    }
    
    if (WIFEXITED(status)) // The child process ended normally
    {
      if (WEXITSTATUS(status) == 0) // The child process was executed normally
        success = true; 
    }
    
    // Given the success/fail of this command:
    // will the next one be run considering its connector?
    runNext = getCommand(i).runNext(success);
   
   delete[] args; // Delete the array
  }
}

