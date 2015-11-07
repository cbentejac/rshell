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


Command ParsedCommand::getCommand(unsigned i) // Returns the Command contained 
{
  assert(i < commands.size()); // Checks that i isn't out of range
  return commands[i];
}


void ParsedCommand::setCommand(unsigned i, Command c)
{
  assert(i < commands.size()); // Checks that i isn't out of range
  if(c.getConnector().getRepresentation() == ";")
    commands[i] = Command(c.getExecutable().getExecutable(), c.getArguments().getArguments(), Semicolon());
  if(c.getConnector().getRepresentation() == "&&")
    commands[i] = Command(c.getExecutable().getExecutable(), c.getArguments().getArguments(), DoubleAnd());
  if(c.getConnector().getRepresentation() == "||")
    commands[i] = Command(c.getExecutable().getExecutable(), c.getArguments().getArguments(), DoubleOr());    
}


void ParsedCommand::addCommand(Command c)
{
  commands.push_back(Command(c.getExecutable().getExecutable(), c.getArguments().getArguments(), c.getConnector()));
}


vector<Command> ParsedCommand::getCommandVector()
{
  return commands;
}


void ParsedCommand::setCommandVector(vector<Command> v)
{
  commands.clear(); // Clears commands before refilling it
  for(unsigned i; i < v.size(); i++)
    commands.push_back(getCommand(i));
}


static bool endWithSemicolon(char* token) // True if token ends with a semicolon; false if it doesn't
{
  string s(token);
  if(s[s.size() - 1] == ';')
    return true;
  return false;
}


static bool isConnector(char* str) // Returns true if str is a connector representation
{
  vector<Connector> v;
  v.push_back(Semicolon());
  v.push_back(DoubleAnd());
  v.push_back(DoubleOr());

  string s(str);
  for(unsigned i = 0; i < v.size(); i++)
    if(s == v[i].getRepresentation())
      return true;
  return false;
}


static Connector recognizeConnector(char* str) // Returns the connector corresponding to a string representation
{
  assert(isConnector(str)); // Checks that str is a connector

  vector<Connector> v;
  v.push_back(Semicolon());
  v.push_back(DoubleAnd());
  v.push_back(DoubleOr());

  string s(str);
  for(unsigned i = 0; i < v.size(); i++)
    if(s == v[i].getRepresentation())
      return v[i];

  return Semicolon(); // Should never be reached, but if there is no correspondance, return a semicolon connector
}


void ParsedCommand::stripComments() // Removes comments from the command line typed by the user
{
  string str(getLine());
  char* search(strchr(const_cast<char*>(str.c_str()), '#')); //  Searches for the integer corresponding to # and return a pointer to the first occurence

  if(search != NULL) // If an occurrence has been found, the pointer is not NULL
    setLine(getLine().substr(0, getLine().size()-(strlen(search)))); // Removes the part of the original command line that starts with # 
}


vector<string> ParsedCommand::separateCommands() // Separates the command line in distinct commands
{
  vector<string> v;
  string str = getLine();
  unsigned j = 0; // Position of the last separation made in the command line

  if(!endWithSemicolon(const_cast<char*>(str.c_str()))) // If the user input doesn't end with a semicolon, adds one (helps avoiding bugs later)
    str += ";";
  
  for(unsigned i = 0; i < str.size(); i++)
  {
    if(str[i] == ';') // If the ; connector is found, extracts then adds the substring to the vector commands
    {
      string tmp;
      for(j = j; j <= i; j++)
        tmp += str[j];
      v.push_back(tmp);
    }
    
    if(str[i] == '&') // If a & character is found
    {
      assert(i + 1 < str.size()); // Checks that there's at least one character after it (to avoid "index out of range")
      if(str[i + 1] == '&') // If another & is found, then extracts and adds the substring (with connector &&) to the vector commands
      {
        string tmp;
        for(j = j; j <= i + 1; j++)
	  tmp += str[j];
	v.push_back(tmp);
      }
    }

    if(str[i] == '|') // If a | character is found
    {
      assert(i + 1 < str.size()); // Checks that there's at least one character after it (to avoid "index out of range")
      if(str[i + 1] == '|') // If another | is found, then extracts and adds the substring (with connector ||) to the vector commands
      {
        string tmp;
	for(j = j; j <= i + 1; j++)
	  tmp += str[j];
	v.push_back(tmp);
      }
    }
  }

  return v;
}


Command ParsedCommand::createCommand(string command)
{
  char* str_conv(const_cast<char*>(command.c_str()));
  char* token(strtok(str_conv, " ")); // Launches tokenization

  unsigned cpt = 0; // Allows us to distinguish the executable from any arguments in the while loop 
  // If cpt == 0, then it's the first time in the loop and the string is necessarily an executable)

  // Initialization of the command elements;
  string ex;
  string arg;
  Connector c = Semicolon();

  while(token != NULL)
  {
    if(cpt == 0) // First element of the command to parse, so it must be an executable
    { 
      if(endWithSemicolon(token))
      { 
        ex = "" + string(token);
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
      if(isConnector(token)) // If it's a connector, recognize it
        c = recognizeConnector(token);

      else // If it's not an executable and not a connector, then it's an argument (if there's no argument, this loop won't be reached)
      {
	if(endWithSemicolon(token)) // Checks if it's the last element of the command
	{ 
	  if(!(arg.empty())) // If it's not the first argument for this command, adds a space between them
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
  
  Command cmd(ex, arg, c); // Create the Command object associeted with the string
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

static bool emptyArguments(Command cmd) // Checks if a command as an empty list of arguments (used to avoid bugs with commands like ls)
{
  if(cmd.getArguments().getArguments() == "")
    return true;
  return false;
}

void ParsedCommand::execute(bool &quit)
{
  parse();

  bool runNext = true; // Will the next instruction be ran? By default, true in case the connector is a semicolon

  for(unsigned i = 0;  i < getCommandVector().size(); i++)
  {
    bool success = false; // Has the command been ran normally? By default, let's say it's not the case
    
    if(getCommand(i).getExecutable().getExecutable() == "exit" && runNext == true) // If exit is the executable and the next instruction is to be ran:
    // quit value becomes true
      quit = true;

    if(quit == true || runNext == false) // If exit has been found or if the connector "refuses" to execute the next command:
    // Stop trying executing the rest of the command line
    {
      if(quit)
        cout << "Exiting rshell." << endl << endl;
      break;
    }

    char* args[3] = { const_cast<char*>(getCommand(i).getExecutable().getExecutable().c_str()), 
                      const_cast<char*>(getCommand(i).getArguments().getArguments().c_str()), 
		      NULL 
		    }; // Will be executed with execvp; last element must be NULL

    if(emptyArguments(getCommand(i))) // Fixes the "empty arguments list" bug (replace "" by NULL)
      args[1] = NULL;
    
    pid_t c_pid, pid;
    int status;

    c_pid = fork();

    if(c_pid < 0) // Fork problem
    {
      perror("Error: fork failed");
      exit(1);
    }
    else if(c_pid == 0) // Child process
    {
      execvp(args[0], args);
      perror("Error: execvp failed");
    }
    else if(c_pid > 0) // Parent process
      if((pid = wait(&status)) < 0)
      {
        perror("Error occurred during wait");
	exit(1);
      }
    
    if(WIFEXITED(status)) // The child process ended normally
      if(WEXITSTATUS(status) == 0) // The child process was executed normally
        success = true; 
    
    runNext = getCommand(i).runNext(success); // Given the success/fail of this command, will the next one be ran considering its connector?
  }
}
