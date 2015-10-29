#include "Connector.hpp"

using namespace std;

Connector::Connector(string r, bool success, bool fail) : representation(r), needSuccess(success), needFail(fail)
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

bool Connector::getNeedFail()
{
  return needFail;
}

void Connector::setNeedFail(bool fail)
{
  needFail = fail;
} 
