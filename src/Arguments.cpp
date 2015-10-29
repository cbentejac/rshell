#include "Arguments.hpp"

using namespace std;

Arguments::Arguments(char* arg) : arguments(arg)
{

}

Arguments::~Arguments()
{

}

char* Arguments::getArguments()
{
  return arguments;
}

void Arguments::setArguments(char* arg)
{
  arguments = strcpy(arguments, arg); 
}

void Arguments::readArguments()
{
  cout << arguments << endl;
}
