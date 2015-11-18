/**
 * \file Command.cpp
 * \author Candice Bentejac
 * \date November 6, 2015
 * \brief Definitions of the Command class.
 */

#include "Command.hpp"

using namespace std;

Command::Command(string e, string arg, Connector c) : 
  executable(Executable(e)), arguments(Arguments(arg)), connector(c)
{

}


Command::~Command()
{

}


Executable Command::getExecutable()
{
  return executable;
}


Arguments Command::getArguments()
{
  return arguments;
}


Connector Command::getConnector()
{
  return connector;
}


void Command::setExecutable(Executable e)
{
  executable = Executable(e.getExecutable());
}


void Command::setArguments(Arguments arg)
{
  arguments = Arguments(arg.getArguments());
}


void Command::setConnector(Connector c)
{
  connector = c;
}


void Command::readCommand()
{
  cout << getExecutable().getExecutable() << " " << getArguments().getArguments() << " " << getConnector().getRepresentation() << endl;
}


// Determines whether or not the next command must be run
bool Command::runNext(bool success) 
{
  // If the connector "needSuccess" matches the value of success, then it's OK
  if (getConnector().getNeedSuccess() == success)
    return true;
  // If the connector is a ";",  the next command will systematically be run
  else if (getConnector().getRepresentation() == ";")
    return true;
  return false;
}


bool Command::isTest()
{
  if (getExecutable().getExecutable() == "test")
    return true;
  return false;
}


bool Command::testSuccess()
{
//  struct stat buf;
  bool success = true;

/*  char* str = const_cast<char*>(getArguments().getArguments().c_str());
  char* token = strtok(str, " ");

  vector<string> v;

  while (token != NULL)
  {
    v.push_back(string(token));
    token = strtok(NULL, " ");
  }

  // If there are more than the flag and the path, the command is not valid
  if (v.size() > 2)
    success = false;
  else
  {
    char* args[2];
    args[0] = const_cast<char*>(v[0].c_str());
    args[1] = const_cast<char*>(v[1].c_str());

    if (strcmp(args[0], "-e") == 0)
    {
      success = stat(args[0], &buf);
    }

    else if (strcmp(args[0], "-f") == 0)
    {
      success = stat(args[0], &buf);
      if (success)
      {
        if (S_ISREG(buf.st_mode))
	  success = true;
	else
	  success = false;
      }
    }

    else if (strcmp(args[0], "-d") == 0)
    {
      success = stat(args[0], &buf);
      if (success)
      {
        if (S_ISDIR(buf.st_mode))
	  success = true;
	else
	  success = false;
      }
    }
  }*/

  cout << getExecutable().getExecutable() << getArguments().getArguments() << getConnector().getRepresentation() << endl;
  return success;
}
