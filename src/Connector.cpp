/**
 * \file Connector.cpp
 * \author Candice Bentejac, Samuel Magness
 * \date November 20, 2015
 * \brief Definitions of the Connector class.
 */

#include "Connector.hpp"

using namespace std;

Connector::Connector(string r, bool success, int p) : 
  representation(r), needSuccess(success), precedence(p)
{

}


Connector::~Connector()
{

}


string Connector::getRepresentation()
{
  return representation;
}

int Connector::getPrecedence()
{
  return precedence;
}

void Connector::setRepresentation(string r)
{
  representation = r;
}


bool Connector::getNeedSuccess()
{
  return needSuccess;
}


void Connector::setNeedSuccess(bool success)
{
  needSuccess = success;
}
