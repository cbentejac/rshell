#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include "Semicolon.hpp"
#include "DoubleAnd.hpp"
#include "DoubleOr.hpp"
#include "Arguments.hpp"
#include "Executable.hpp"
#include <vector>

class Command 
{
  public:
    Command(std::string line);
    ~Command();

    /* Getters and setters */
    std::string getLine();
    void setLine(std::string cmd);
    std::vector<Executable> getExecutables();
    void setExecutables(std::vector<Executable> ex);
    std::vector<Arguments> getArguments();
    void setArguments(std::vector<Arguments> args);
    std::vector<Connector> getConnectors();
    void setConnectors(std::vector<Connector> connect);
    
    void addExecutable(Executable e);
    void addArguments(Arguments a);
    void addConnector(Connector c);

    /* Parsing methods */
    std::string stripComments(); // Remove comments from the command line
    void parse(); // Parse the command line

  protected:
    std::string command; // Command typed by the user
    // Vectors will be used to handle the case where the user typed several commands on the same line
    std::vector<Executable> executables; 
    std::vector<Arguments> arguments;
    std::vector<Connector> connectors;

};

#endif
