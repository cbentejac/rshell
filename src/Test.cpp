/**
 * \file Test.cpp
 * \author Candice Bentejac
 * \date November 20, 2015
 * \brief Definitions of the Test class.
 */

#include "Test.hpp"

using namespace std;

Test::Test() : Command("test", "-e", Semicolon())
{

}

Test::Test(string arg, Connector c) : Command("test", arg, c)
{

}

Test::~Test()
{

}
