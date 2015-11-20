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
#include <cstdlib>

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
			  Semicolon(0)
			 );
  if (c.getConnector().getRepresentation() == "&&")
    commands[i] = Command(c.getExecutable().getExecutable(), 
                          c.getArguments().getArguments(), 
			  DoubleAnd(0)
			 );
  if (c.getConnector().getRepresentation() == "||")
    commands[i] = Command(c.getExecutable().getExecutable(), 
                          c.getArguments().getArguments(), 
			  DoubleOr(0)
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
bool ParsedCommand::endWithSemicolon(char* token) 
{
  string s(token);
  if (s[s.size() - 1] == ';')
    return true;
  return false;
}


// True if token ends with "&&"
bool ParsedCommand::endWithDoubleAnd(char* token)
{
  string s(token);
  if (s.size() < 2)
    return false;
  if (s[s.size() - 1] == '&' && s[s.size() - 2] == '&')
    return true;
  return false;
}


// True if token ends with "||"
bool ParsedCommand::endWithDoubleOr(char* token)
{
  string s(token);
  if (s.size() < 2)
    return false;
  if (s[s.size() - 1] == '|' && s[s.size() - 2] == '|')
    return true;
  return false;
}


// Returns true if str is a connector representation 
bool ParsedCommand::isConnector(char* str) 
{
  vector<Connector> v;
  v.push_back(Semicolon(0));
  v.push_back(DoubleAnd(0));
  v.push_back(DoubleOr(0));

  string s(str);
  for (unsigned i = 0; i < v.size(); i++)
  {
    if (s == v[i].getRepresentation())
      return true;
  }
  return false;
}


// Returns true if str begins a parenthetical statement.
bool ParsedCommand::beginsParenthetical(std::string str)
{
  if (str.at(0) == '(')
    return true;
  else
    return false;
}


// Returns true if str ends a parenthetical statement.
bool ParsedCommand::endsParenthetical(std::string str)
{
  unsigned int s = str.size();
  if (str.at(s-1) == ';')
  {
    if (str.at(s-2) == ')')
      return true;
    else 
      return false;
  }
  if ((str.at(s-1) == '&') && (str.at(s-2) == '&'))
  {
    if(str.at(s-3) == ')')
      return true;
    else
      return false;
  }
  if ((str.at(s-1) == '|') && (str.at(s-2) == '|'))
  {
    if (str.at(s-3) == ')')
      return true;
    else
      return false;
  }
  return false;
}
// Returns the connector corresponding to a string representation
Connector ParsedCommand::recognizeConnector(char* str, int p)
{
  assert(isConnector(str)); // Checks that str is a connector 

  vector<Connector> v;
  v.push_back(Semicolon(p));
  v.push_back(DoubleAnd(p));
  v.push_back(DoubleOr(p));

  string s(str);
  for (unsigned i = 0; i < v.size(); i++)
  {
    if (s == v[i].getRepresentation())
      return v[i];
  }

  return Semicolon(0); // Should never be reached, but just in case
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
      if(endWithDoubleAnd(const_cast<char*>(str.c_str())) || 
         endWithDoubleOr(const_cast<char*>(str.c_str())))
        str = str.substr(0, str.size() - 2);
      str += " ;";
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


Command ParsedCommand::createCommand(string command, int precedence)
{ 
  //Remove the parentheses, we no longer need them.
  if (beginsParenthetical(command))
    command.erase(command.begin());
  if (endsParenthetical(command))
  {
    unsigned int s = command.size();
    if (command.at(s-1) == ';')
      command.erase(command.end()-2);
    else
      command.erase(command.end()-3);
  }
    
  string copy = "" + command; // Copy of command that will be tokenized
  // We need to keep command untouched for the test parsing
  
  char* str_conv(const_cast<char*>(copy.c_str()));
  char* token(strtok(str_conv, " ")); // Launches tokenization

  unsigned cpt = 0; // To distinguish the executable from arguments in the loop
  // cpt == 0: 1st time in the loop and the string is necessarily an executable

  // Initialization of the command elements;
  string ex;
  string arg;
  Connector c = Semicolon(precedence);

  while (token != NULL)
  {
    if (cpt == 0) // First element of the command to parse = executable
    { 
      ex = "" + string(token);
      cpt ++;

      if (endWithSemicolon(token))
      { 
	ex = ex.substr(0, ex.size() - 1);
	c = Semicolon(precedence);
      }
      else if (endWithDoubleAnd(token))
      {
	ex = ex.substr(0, ex.size() - 2);
	c = DoubleAnd(precedence);
      }
      else if (endWithDoubleOr(token))
      {
	ex = ex.substr(0, ex.size() - 2);
	c = DoubleOr(precedence);
      }

      // If it's a test command
      else if (strcmp(token, "[") == 0 || 
               token[0] == '[' || 
	       ex == "test")
      {
        return Test::parseTest(command, precedence);
      }
    }
    else
    {
      if (isConnector(token)) // If it's a connector, recognize it
        c = recognizeConnector(token, precedence);
      
      // If it's not an executable and not a connector, then it's an argument
      // (If there's no argument, this loop won't be reached)
      else 
      {

	// If it's not the 1st argument for this command, adds a space
	if (!(arg.empty())) 
	  arg += " ";

        arg += "" + string(token);

        // Checks if it's the last element of the command (ends with connector)
	if (endWithSemicolon(token) || 
	    endWithDoubleAnd(token) || 
	    endWithDoubleOr(token)) 
	{ 
	  if (endWithSemicolon(token))
	  {
	    // Separate the argument from the connector
	    arg = arg.substr(0, arg.size() - 1); 
            c = Semicolon(precedence);
	  }
	  else if (endWithDoubleAnd(token))
	  {
	    arg = arg.substr(0, arg.size() - 2);
	    c = DoubleAnd(precedence);
	  }
	  else
	  {
	    arg = arg.substr(0, arg.size() - 2);
	    c = DoubleOr(precedence);
	  }
        }
      }
    }
    token = strtok(NULL, " "); 
  }
  
  return Command(ex, arg, c); // Create the Command object with the string
}

bool ParsedCommand::readPrecedent (vector<Command> commands, Command c, bool sp, bool &quit)
{
  // Will the next instruction be run? By default, true
  bool runNext = true; 

  // Establish success outside of loop so that it can be returned
  bool success = false; 

  for (unsigned i = 0;  i < commands.size(); i++)
  {
    // Has the command been run normally? By default, false
    success = false; 
    
    //if command has higher precedence than the previous command,
    //begin recursion
    if ((i != 0) && (getCommand(i).getConnector().getPrecedence() >
     getCommand(i-1).getConnector().getPrecedence()))
    {
      //identify command before precedence operator
      Command pc = getCommand(i-1);
      //and identify the arguements within precedence operator
      vector<Command> pv;
      int p = getCommand(i).getConnector().getPrecedence();
      while (getCommand(i).getConnector().getPrecedence() >= p)
      {
        pv.push_back(getCommand(i));
        i++;
      }
        pv.push_back(getCommand(i));
      //execute the commands within the precedence operator and return 
      //success value
      success = readPrecedent(pv, pc, success, quit);
      //if the end of the Command vector has been reached, end function.
      //otherwise, continue parsing the vector as normal.
      if (i >= commands.size()-1)
        return success; 
    }
    // If exit is the executable and the next instruction is to be run
    if (getCommand(i).getExecutable().getExecutable() == "exit" && 
        runNext == true) 
    // quit value becomes true
      quit = true;

    // If exit has been found
    if (quit == true) 
    // Stop trying executing the rest of the command line
    {
      cout << "Exiting rshell." << endl << endl;
      return success;
    }

    // If the next command should be run and is not a test
    if (runNext == true && !commands.at(i).isTest()) 
    {
      // Designed to handle the case where there are several arguments 
      char* str = const_cast<char*>(
                  commands.at(i).getArguments().getArguments().c_str()
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
          args[j] = const_cast<char*>(commands.at(i).getExecutable().getExecutable().c_str());
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
        runNext = commands.at(i).runNext(success) && c.runNext(sp);
      
      delete[] args; // Delete the array
    }

    else // If the current command isn't run, see if we run the next one or not
    {
      // If the command is a test command, see if we must run the next command
      if (getCommand(i).isTest())
        runNext = getCommand(i).runNext(getCommand(i).testSuccess()) && c.runNext(sp);
    
      // If the connector is ||, then we mustn't run the next command
      else if (getCommand(i).getConnector().getRepresentation() == "||")
        runNext = false;
      else // If it's && or ;, then we should run it
        runNext = true && c.runNext(sp);
    }
  }
  return success;
}

void ParsedCommand::parse()
{
  stripComments(); // Eliminates the comments from the command line
  // Separates the different commands so that we can parse them one by one
  vector<string> v = separateCommands(); 
  //Keeps track of how many parentheses each command is within
  int p = 0; 

  for (unsigned i = 0; i < v.size(); i++)
  {
    if (beginsParenthetical(v[i]))
    {
      p++;
    }
    else if (endsParenthetical(v[i]))
    {
      p--;
     // if (p < 0)
        //HANDLE ERROR: END PARENTHESES WITH NO BEGINNING
    }
    Command c = createCommand(v[i], p);
    addCommand(c);
  }
  //if (p != 0)
    //HANDLE ERROR: BEGINNING PARENTHESES WITH NO END
}


void ParsedCommand::execute(bool &quit)
{
  parse();

  // Will the next instruction be run? By default, true
  bool runNext = true; 

  for (unsigned i = 0;  i < getCommandVector().size(); i++)
  {
    // Has the command been run normally? By default, false
    bool success = false; 
    
    //if command has higher precedence than the previous command,
    //begin reading precedence. Subsequent commands having lower recursion
    //is how bash normally handles order of operations, so we don't need
    //more code for it.
    if ((i != 0) && (getCommand(i).getConnector().getPrecedence() >
     getCommand(i-1).getConnector().getPrecedence()))
    {
      //identify connector before precedence operator
      Command pc = getCommand(i-1);
      //and identify the arguements within precedence operator
      vector<Command> pv;
      int p = getCommand(i).getConnector().getPrecedence();
      while (getCommand(i-1).getConnector().getPrecedence() >= p)
      {
        pv.push_back(getCommand(i));
        i++;
      }
      //execute the commands within the precedence operator and return 
      //success value
      success = readPrecedent(pv, pc, success, quit);
      //if the end of the Command vector has been reached, exit.
      //otherwise, continue parsing the vector as normal.
      if (i >= getCommandVector().size()-1)
        break; 
    }
    // If exit is the executable and the next instruction is to be run
    if (getCommand(i).getExecutable().getExecutable() == "exit" && 
        runNext == true) 
    // quit value becomes true
      quit = true;

    // If exit has been found
    if (quit == true) 
    // Stop trying executing the rest of the command line
    {
      cout << "Exiting rshell." << endl << endl;
      break;
    }

    // If the next command should be run and is not a test
    if (runNext == true && !getCommand(i).isTest()) 
    {
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

    else // If the current command isn't run, see if we run the next one or not
    {
      // If the command is a test command, see if we must run the next command
      if (getCommand(i).isTest())
        runNext = getCommand(i).runNext(getCommand(i).testSuccess());
    
      // If the connector is ||, then we mustn't run the next command
      else if (getCommand(i).getConnector().getRepresentation() == "||")
        runNext = false;
      else // If it's && or ;, then we should run it
        runNext = true;
    }
  }
}

