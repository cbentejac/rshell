#include "Command.hpp"

using namespace std;

Command::Command(string line) : command(line)
{
  executables.clear();
  arguments.clear();
  connectors.clear();
}

Command::~Command()
{

}

/* Getters and Setters */
string Command::getLine()
{
  return command;
}

void Command::setLine(string cmd)
{
  command = cmd;
}

vector<Executable> Command::getExecutables()
{
  return executables;
}

void Command::setExecutables(vector<Executable> ex)
{
  executables = ex;
}

vector<Arguments> Command::getArguments()
{
  return arguments;
}

void Command::setArguments(vector<Arguments> args)
{
  arguments = args;
}

vector<Connector> Command::getConnectors()
{
  return connectors;
}

void Command::setConnectors(vector<Connector> connect)
{
  connectors = connect;
}


void Command::addExecutable(Executable e)
{
  executables.push_back(e);
}

void Command::addArguments(Arguments a)
{
  arguments.push_back(a);
}

void Command::addConnector(Connector c)
{
  connectors.push_back(c);
}


/* Static methods that will be used to handle the case were the user does'nt respect the connectors syntax */
static bool endWithSemicolon(char* str) // Returns true if the string ends with a semicolon
{
  char* s = strchr(str, ';');
  if(s != NULL)
    return true;
  return false;
}

static bool endWithAnd(char *str)
{
  string s(str);
  if(s[s.size() - 1] == '&' && s[s.size() - 2] == '&')
    return true;
  return false;
}

static bool endWithOr(char *str)
{
  string s(str);
  if(s[s.size() - 1] == '|' && s[s.size() - 2] == '|')
    return true;
  return false;
}

static bool endWithConnector(char* str)
{
  return endWithSemicolon(str) || endWithAnd(str) || endWithOr(str);
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


/* Parsing methods */

string Command::stripComments() // Removes comments from the command line typed by the user
{
  string str = command;
  char* search = strchr(const_cast<char*>(str.c_str()), '#'); // Casts a copy of the command attribute; then searches for the integer corresponding to # and return a pointer to the first occurence
  if(search != NULL) // If an occurrence has been found, the pointer is not NULL
  {
    setLine(command.substr(0, command.size()-(strlen(search)))); // Modify the commnand attribute by removing the part of the original command line that starts with # 
  }
  return getLine();
}


void Command::parse() // Determines the executables, arguments, and connectors of the command line
{
  setLine(stripComments()); // Removes comments

  /* We need to get a copy of the command line to tokenize it without modifying it in case we would need it later */
  string str = getLine();
  char* str_conv = const_cast<char*>(str.c_str());
  char* token = strtok(str_conv, " "); // Launches tokenization

  int i = 0; // "Position" in the command; 0 will always be the position of an executable

  /* Tokenization of the command line; the string is divided in substrings that were separated by spaces */
  while(token != NULL)
  {
    if(i == 0) // If i == 0, then it must be an executable
    {
      if(endWithConnector(token))// Check if it ends with a connector (semicolon or other connectors with wrong syntax)
      {
        string s(token); // Copy of the token
        if(endWithSemicolon(token)) // Ends with a semicolon (connector of size 1)
	{
          s = s.substr(0, s.size() - 1); // Removes the semicolon
	  addExecutable(Executable(const_cast<char*>(s.c_str())));
	  addConnector(Semicolon());
	}
	else // Ends with && or || (connector of size 2)
	{
	  s = s.substr(0, s.size() - 2); // Removes the && or the ||
	  addExecutable(Executable(const_cast<char*>(s.c_str())));
	  if(endWithAnd(token))
	    addConnector(DoubleAnd());
	  else
	    addConnector(DoubleOr());
	}
	addArguments(Arguments(const_cast<char*>(""))); // No arguments for this command, as the executable is immediately followed by a connector
      }
      else // The executable doesn't end with a connector: either there is an argument or a connector or nothing after
      {
        addExecutable(Executable(token)); 
        i++; // The next token to be analyzed won't be an executable, so i must be different from 0
      }
    }

    if(isConnector(token))
    {
      addConnector(recognizeConnector(token));
      i = 0; // A connector ends an instruction, so we reinitialize i to tell the program that if there is a next token, it will be an executable
    }
      
    cout << token << " ends with ;? : " << endWithSemicolon(token) << endl;
    cout << token << " is connector? : " << isConnector(token) << endl;
    cout << token << " ends with &&? : " << endWithAnd(token) << endl;
    cout << token << " ends with ||? : " << endWithOr(token) << endl;
    
    token = strtok(NULL, " ");

  }

}


int main()
{
  Command cmd("ls; ls -lR&& ls|| echo 'hello' && ls  # -lR");
  cmd.stripComments();

  cmd.parse();
  
  for(unsigned i = 0; i < cmd.getExecutables().size(); i++)
  {
    cout << endl << "Affichage contenu des vecteurs" << endl; 
    cmd.getExecutables()[i].readExecutable();
    cmd.getArguments()[i].readArguments();
    cout << cmd.getConnectors()[i].getRepresentation() << endl;
  }

  
  return 0;
}
