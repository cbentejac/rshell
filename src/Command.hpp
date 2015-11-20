/**
 * \file Command.hpp
 * \author Candice Bentejac, Samuel Magness
 * \date November 20, 2015
 * \brief Header for the Command class.
 */

#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include "Semicolon.hpp"
#include "DoubleAnd.hpp"
#include "DoubleOr.hpp"
#include "Arguments.hpp"
#include "Executable.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>


class Command 
{
  public:
    /**
     * \brief Command constructor.
     * \param string e the executable string.
     * \param string arg the arguments list string.
     * \param Connector c the connector.
     * \return A Command object.
     */
    Command(std::string e, std::string arg, Connector c);
    /**
     * \brief Command destructor.
     */
    ~Command();

    /**
     * \brief Returns the Executable object composing the Command object.
     * \return An Executable object.
     */
    Executable getExecutable();
    /**
     * \brief Returns the Arguments object composing the Command object.
     * \return An Argument object.
     */
    Arguments getArguments();
    /**
     * \brief Returns the Connector object composing the Command object.
     * \return A Connector object.
     */
    Connector getConnector();

    /**
     * \brief Sets the Executable object composing the Command object.
     * \param Executable e the new Executable object composing the Command.
     */
    void setExecutable(Executable e);
    /**
     * \brief Sets the Arguments object composing the Command object.
     * \param Arguments arg the new Arguments object to composing the Command.
     */
    void setArguments(Arguments arg);
    /**
     * \brief Sets the Connector object composing the Command object.
     * \param Connector c the new Connector object composing the Command.
     */
    void setConnector(Connector c, int p);

    /**
     * \brief Prints the command on the standard output stream.
     */
    void readCommand();
    /**
     * \brief Determines whether the next instruction must be run or not, 
     * depending on the success and the connector of the previous run command
     * \param bool success: true if the previous command was successfully run; 
     * false if it was not.
     * \return true if the next command can be run; false it cannot.
     */
    bool runNext(bool success);
    /**
     * \brief Determines whether or not the command is a test command.
     * \return True if it's a test command; false if it's not.
     */
    bool isTest();
    /**
     * \brief Simulates the execution of the test command.
     * \return A boolean that states the success or the failure of the test.
     */
    bool testSuccess();
  
  protected:
    /**
     * \brief Executable part of the command.
     */
    Executable executable;
    /**
     * \brief Arguments part of the command.
     */
    Arguments arguments;
    /**
     * \brief Connector part of the command.
     */
    Connector connector;
    /**
     * \brief Integer indicating the command's level of precedence.
     */ 
    int precedence;
};

#endif
