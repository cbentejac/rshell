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
