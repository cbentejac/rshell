/**
 * \file ParsedCommand.hpp
 * \author Candice Bentejac
 * \date November 6, 2015
 * \brief Header for the ParsedCommand class.
 */

#ifndef _PARSED_COMMAND_HPP_
#define _PARSED_COMMAND_HPP_

#include "Command.hpp"
#include <vector>

class ParsedCommand {
  
  public:
    /**
     * \brief ParsedCommand constructor.
     * \param string line the user input.
     * \return A ParsedCommand object.
     */
    ParsedCommand(std::string line);
    /**
     * \brief ParsedCommand destructor.
     */
    ~ParsedCommand();

    /**
     * \brief Returns the user input.
     * \return User input.
     */
    std::string getLine();
    /**
     * \brief Sets the command line entered by the user.
     * \param string line the new command line.
     */
    void setLine(std::string line);

    /** 
     * \brief Removes the white spaces at the end of the command line.
     */
    void trimLine();
    /**
     * \brief Returns the object Command at the index i in the vector commands.
     * \param unsigned i the index of the Command in the vector commands.
     * \return The Command object at the index i of the vector commands.
     */
    Command getCommand(unsigned i); 
    /**
     * \brief Sets the object Command at the index i in the vector commands.
     * \param unsigned i the index of the Command in the vector commands.
     * \param Command c the new Command object.
     */
    void setCommand(unsigned i, Command c);
    /**
     * \brief Pushes a Command object to the end of the vector commands.
     * \param Command c the Command object to add to the vector commands.
     */
    void addCommand(Command c);

    /**
     * \brief Returns the vector commands.
     * \return The vector commands.
     */
    std::vector<Command> getCommandVector();
    /**
     * \brief Sets the vector commands.
     * \param vector<Command> v the new vector commands.
     */
    void setCommandVector(std::vector<Command> v); // Sets the vector commands

    /**
     * \brief Add spaces between the && or || connectors and the rest
     */
    void addSpaces();
    /**
     * \brief Removes the comments from the user input
     */
    void stripComments();
    /**
     * \brief Separate the user input into different command strings.
     * \return A string vector where a string corresponds to a single command.
     */
    std::vector<std::string> separateCommands();
    /**
     * \brief Given a string, returns a Command object.
     * \param string command an isolated stand-alone command.
     * \return A Command object.
     */
    Command createCommand(std::string command);
    /**
     * \brief Fills the vector commands with Command objects.
     */
    void parse();
    /** 
     * \brief Executes the commands contained in the vector commands.
     * \param bool &quit: true if the user has entered "exit"; false if not.
     */
    void execute(bool &quit);
  
  protected:
    /**
     * \brief The user input.
     */
    std::string commandLine;
    /**
     * \brief The vector containing all the Command objects that represent the 
     * different single commands the user typed on a single line.
     */
    std::vector<Command> commands;
};

#endif
