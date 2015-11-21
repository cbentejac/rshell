/**
 * \file Test.cpp
 * \author Candice Bentejac, Samuel Magness
 * \date November 20, 2015
 * \brief Definitions of the Test class.
 */

#include "Test.hpp"
#include "ParsedCommand.hpp"

using namespace std;


Test::Test(Connector c) : Command("test", "-e ", c)
{

}


Test::Test(string arg, Connector c) : Command("test", arg, c)
{

}


Test::~Test()
{

}


Test Test::parseTest(string cmd, int p)
{
  string arg;
  Connector c = Semicolon(0);

  string tmp;

  // Adds space where needed to avoid the case [xxx ] or [ xxx]
  // [xxx] won't work, as in the original bash
  for (unsigned i = 0; i < cmd.size() - 1; i++)
  {
    // Space between the flag and "test" or "["
    if (cmd[i] != ' ' && cmd[i + 1] == '-')
      tmp += " ";

    tmp += cmd[i];
    
    // Space between arguments and "]"
    if (cmd[i + 1] == ']' && cmd[i] != ' ')
      tmp += " ";

    // Space between "]" and connector
    if (cmd[i] == ']' && cmd[i + 1] != ' ')
      tmp += " ";
    
    // Space between "[" and arguments
    if (cmd[i] == '[')
      tmp += " ";  
  }
  tmp += cmd[cmd.size() - 1];

  char* str = const_cast<char*>(tmp.c_str());
  char* token = strtok(str, " ");

  bool flag = false; // Checks if the user has typed a flag

  while (token != NULL)
  { 
    // "test", [, ] have been treated to be separated from arg and connector
    // They're necessarily token on their own that we can ignore
    if (string(token).compare("[") != 0 &&
        string(token).compare("]") != 0 &&
	string(token).compare("test") != 0)
    {
      // If token is a connector
      if (ParsedCommand::isConnector(token))
        c = ParsedCommand::recognizeConnector(token, p);

      else // If it's not a connector, it's an argument
      {
        // Handles case where there are several arguments (flag + path)
        if (!arg.empty())
  	  arg += " ";
	arg += string(token);

        // If a flag exists, it means the user has typed one
	if(string(token).compare("-d") == 0 ||
	   string(token).compare("-e") == 0 ||
	   string(token).compare("-f") == 0)
	{
	    flag = true;
	}
        
	// If the argument ends with a connector (no space)
	if (ParsedCommand::endWithSemicolon(token) ||
	    ParsedCommand::endWithDoubleAnd(token) ||
	    ParsedCommand::endWithDoubleOr(token))
	{
	  if (ParsedCommand::endWithSemicolon(token))
	  {
	    // Separate the argument from the connector
	    arg = arg.substr(0, arg.size() - 1); 
            c = Semicolon(p);
	  }
	  else if (ParsedCommand::endWithDoubleAnd(token))
  	  {
	    arg = arg.substr(0, arg.size() - 2);
	    c = DoubleAnd(p);
	  }
	  else
	  {
	    arg = arg.substr(0, arg.size() - 2);
	    c = DoubleOr(p);
          }
        }
      }
    }

    token = strtok(NULL, " ");
  }
 
  if (flag)
    return Test(arg, c);

  Test test(c);

  if (arg.empty()) // If there's no flag and no arguments
  {
    test.setArguments(Arguments(""));   
  }

  else // If there is no flag but an argument 
  {
    tmp.clear();
    tmp = test.getArguments().getArguments();
    tmp += arg;
    test.setArguments(Arguments(tmp));
  }
  
  return test;
}
