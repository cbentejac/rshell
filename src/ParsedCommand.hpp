#ifndef _PARSED_COMMAND_HPP_
#define _PARSED_COMMAND_HPP_

#include "Command.hpp"
#include <vector>

class ParsedCommand {
  
  public:
    ParsedCommand(std::string line);
    ~ParsedCommand();

    std::string getLine();
    void setLine(std::string line);

    Command getCommand(unsigned i); // Returns the object Command at the index i in the vector commands
    void setCommand(unsigned i, Command c); // Sets the object Command at the index i in the vector commands
    void addCommand(Command c); // Adds a Command to the vector commands
    void deleteLastCommand(); // Removes the last element of commands

    std::vector<Command> getCommandVector(); // Returns the vector commands
    void setCommandVector(std::vector<Command> v); // Sets the vector commands

    void stripComments(); // Removes the comments from commandLine
    std::vector<std::string> separateCommands(); // Returns a string vector containing strings that correspond to Command (every element of the returned vector can be used to create a Command object)
    Command createCommand(std::string command);
    void parse();
  
  protected:
    std::string commandLine;
    std::vector<Command> commands;

};

#endif
