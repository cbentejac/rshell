/**
 * \file Command.cpp
 * \author Candice Bentejac
 * \date November 6, 2015
 * \brief Definitions of the Command class.
 */

#include "Command.hpp"

using namespace std;

Command::Command(string e, string arg, Connector c) : executable(Executable(e)), arguments(Arguments(arg)), connector(c)
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
  connector = Connector(c);
}


bool Command::runNext(bool success) // Determines whether or not the next command must be ran
{
  if(getConnector().getNeedSuccess() == success) // If the connector attribute "needSuccess" matches the value of success, then it's OK
    return true;
  else if(getConnector().getRepresentation() == ";") // If the connector is a semicolon, the next command will be ran no matther what
    return true;
  return false;
}
