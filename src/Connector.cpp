#include "Connector.hpp"

using namespace std;

Connector::Connector(string r, bool success) : representation(r), needSuccess(success)
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
