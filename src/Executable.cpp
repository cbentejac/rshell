#include "Executable.hpp"

using namespace std;

Executable::Executable(char* exec) : executable(exec)
{

}

Executable::~Executable()
{

}

char* Executable::getExecutable()
{
  return executable;
}

void Executable::setExecutable(char* exec)
{
  executable = exec; 
}

void Executable::readExecutable()
{
  cout << executable << endl;
}


