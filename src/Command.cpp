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
  char* search = strchr(const_cast<char*>(str.c_str()), '#'); // Research the integer corresponding to # and return a pointer to the first occurence
  if(search != NULL) // If an occurrence has been found, the pointer is not NULL
  {
    cout << "COMMENT FOUND!" << endl;
    cout << strlen(search) << endl;
    command = command.substr(0, command.size()-(strlen(search)));
    cout << command << endl;
  }
      //s = s.substr(0, s.size()-1);
  return command;
}

int main()
{
  Command cmd("ls # -lR");
  cmd.stripComments();
  return 0;
}
