/**
 * \file Connector.cpp
 * \author Candice Bentejac
 * \date November 6, 2015
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
