#include "Executable.hpp"

using namespace std;

Executable::Executable(string exec) : executable(exec)
{

}

Executable::~Executable()
{

}

string Executable::getExecutable()
{
  return executable;
}

void Executable::setExecutable(string exec)
{
  executable = exec; 
}

void Executable::readExecutable()
{
  cout << executable << endl;
}


