/**
 * \file Executable.cpp
 * \author Candice Bentejac
 * \date November 6, 2015
 * \brief Definitions of the Executable class.
 */

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
