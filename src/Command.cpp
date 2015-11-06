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

bool Command::runNext(bool success, bool fail)
{
  if(getConnector().getNeedSuccess() == success && getConnector().getNeedFail() == fail) 
  {
    return true;
  }
  else if(getConnector().getRepresentation() == ";")
  {
    return true;
  }
  else
  {
    return false;
  }
}
