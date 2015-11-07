/**
 * \file Executable.hpp
 * \author Candice Bentejac
 * \date November 6, 2015
 * \brief Header for the Executable class.
 */

#ifndef _EXECUTABLE_HPP_
#define _EXECUTABLE_HPP_

#include "Base.hpp"

class Executable
{
  public:
    /**
     * \brief Executable constructor.
     * \param string exec the substring corresponding to the executable.
     * \return An Executable object.
     */
    Executable(std::string exec);
    /**
     * \brief Executable destructor.
     */
    ~Executable();

    /**
     * \brief Returns the string corresponding to the executable.
     * \return The string containing the executable. 
     */
    std::string getExecutable();
    /**
     * \brief Sets the string corresponding to the executable.
     * \param string exec the new string corresponding to the executable.
     */
    void setExecutable(std::string exec);
    /**
     * \brief Prints the executable string on the standard output stream.
     */
    void readExecutable();

  protected:
    /**
     * \brief Executable string.
     */
    std::string executable;
};

#endif
