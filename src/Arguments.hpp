/**
 * \file Arguments.hpp
 * \author Candice Bentejac
 * \date November 6, 2015
 * \brief Header for the Arguments class.
 */

#ifndef _ARGUMENTS_HPP
#define _ARGUMENTS_HPP

#include "Base.hpp"

class Arguments {

  public:
    /**
     * \brief Arguments constructor.
     * \param string arg the list of arguments of the command.
     * \return A new Argument object.
     */
    Arguments(std::string arg);
    /**
     * \brief Arguments destructor. 
     */
    ~Arguments();

    /**
     * \brief Returns the arguments list of the Arguments object.
     * \return The string containing the arguments list.
     */
    std::string getArguments();
    /**
     * \brief Sets the arguments list of the Arguments object.
     * \param string arg the new arguments list.
     */
    void setArguments(std::string arg);
    /**
     * \brief Prints the arguments list on the standard output stream.
     */
    void readArguments();

  protected:
    /**
     * \brief Arguments list.
     */
    std::string arguments;
};

#endif
