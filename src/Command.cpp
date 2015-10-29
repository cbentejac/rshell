#include "Command.hpp"

using namespace std;

Command::Command(string line) : command(line)
{

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


/* Parsing methods */
string Command::stripComments()
{
  string str = command;
  char* search = strchr(const_cast<char*>(str.c_str()), '#'); // Casts a copy of the command attribute; then searches for the integer corresponding to # and return a pointer to the first occurence
  if(search != NULL) // If an occurrence has been found, the pointer is not NULL
  {
    setLine(command.substr(0, command.size()-(strlen(search)))); // Modify the commnand attribute by removing the part of the original command line that starts with # 
  }
  return getLine();
}

int main()
{
  Command cmd("ls # -lR");
  cmd.stripComments();
  cout << cmd.getLine() << endl;
  return 0;
}
