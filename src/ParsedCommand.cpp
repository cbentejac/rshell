#include "ParsedCommand.hpp"
#include <assert.h>

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
  commands.push_back(c);
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


void ParsedCommand::parse()
{
  stripComments();
  //vector<string> v = separateCommands();

  /* We need to get a copy of the command line to tokenize it without modifying it in case we would need it later */
  string str = "" + getLine();
  char* str_conv(const_cast<char*>(str.c_str()));
  char* token(strtok(str_conv, " ")); // Launches tokenization

  unsigned i = 0;

  while(token != NULL)
  {
    if(i == 0)
    {
      if(endWithSemicolon(token))
      {
      
      }
    }
    token = strtok(NULL, " ");
  }

}



int main()
{
  ParsedCommand cmd("ls; echo 'truc' && git status # blafzno fidhf"); 
  cmd.stripComments();

  cout << cmd.getLine() << endl;

  vector<string> v = cmd.separateCommands();
  for(unsigned i = 0; i < v.size(); i++)
  {
    cout << v[i] << endl;
  }
  cout << cmd.getLine() << endl;
  return 0;
}
