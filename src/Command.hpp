/**
 * \file Command.hpp
 * \author Candice Bentejac
 * \date November 6, 2015
 * \brief Header for the Command class.
 */

#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include "Semicolon.hpp"
#include "DoubleAnd.hpp"
#include "DoubleOr.hpp"
#include "Arguments.hpp"
#include "Executable.hpp"

class Command 
{
  public:
    Command(std::string e, std::string arg, Connector c);
    ~Command();

    Executable getExecutable();
    Arguments getArguments();
    Connector getConnector();

    void setExecutable(Executable e);
    void setArguments(Arguments arg);
    void setConnector(Connector c);

    bool runNext(bool success);
  
  protected:
    Executable executable;
    Arguments arguments;
    Connector connector;
};

#endif
