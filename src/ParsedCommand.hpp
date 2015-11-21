/**
 * \file ParsedCommand.hpp
 * \author Candice Bentejac, Samuel Magness
 * \date November 20, 2015
 * \brief Header for the ParsedCommand class.
 */

#ifndef _PARSED_COMMAND_HPP_
#define _PARSED_COMMAND_HPP_

#include "Command.hpp"
#include "Test.hpp"
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
     * \brief Determines whether or not the char* ends with a semicolon.
     * \param char* str a character array.
     * \return True if str ends with a semicolon; false if it doesn't.
     */
    static bool endWithSemicolon(char* str);
    /**
     * \brief Determines whether or not the char* ends with "&&".
     * \param char* str a character array.
     * \return True if str ends with "&&"; false if it doesn't.
     */
    static bool endWithDoubleAnd(char* str);
    /**
     * \brief Determines whether or not the char* ends with "||".
     * \param char* str a character array.
     * \return True if str ends with "||"; false if it doesn't.
     */
    static bool endWithDoubleOr(char* str);
    /**
     * \brief Determines whether or not the char* is a connector.
     * \param char* str a character array.
     * \return True if str is a connector; false if it isn't.
     */
    static bool isConnector(char *str);
    /**
     * \brief Determines if a string begins a parenthetical.
     * \param std:string str a command in string form.
     * \return True if str begins a parenthetical; False otherwise.
     */
    static bool beginsParenthetical(std::string str);
    /**
     * \brief counts the number of precedence initiators in a command string.
     * \param std::string command The command string.
     * \return int the number of precedence initiators in the string.
     */
    int bPCount(std::string command);
    /**
     * \brief counts the number of precedence terminators in a command string.
     * \param std::string command The command string.
     * \return int the number of precedence terminators in the string.
     */
    int ePCount(std::string command);
    /**
     * \brief Determines if a string ends a parenthetical.
     * \param std:string str a command in string form.
     * \return True if str ends a parenthetical; False otherwise.
     */
    static bool endsParenthetical(std::string str);
    /**
     * \brief Returns the connector corresponding to a char*.
     * \param char* str a character array.
     * \return A Connector corresponding to str.
     */
    static Connector recognizeConnector(char* str, int p);
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
    Command createCommand(std::string command, int precedence);
    /**\brief recursively executes precedence arguements.
     * \param vector<Command> commands the command objects within
     * the precedence operator.
     * Command c The command immediately preceding the precedence operator.
     * bool sp the success value of the previous command.
     * bool &quit Wether or not the user entered quit.
     * \return The success value of the execution.
     */
    bool readPrecedent(std::vector<Command> commands, Command c, bool sp,
    bool &quit);
    /**
     * \brief determines if all the parentheses sets in the command line 
     * are complete.
     * \return True if all parentheses sets are complete, False otherwise.
     */
    bool pCheck();
    /**
     * \brief determines if command string is an empty precedence operator.
     * \param std::string command The command string.
     * \return True if empty precedence operator, false otherwise.
     */
    bool isEmptyP(std::string command);
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
