/**
 * \file Test.hpp
 * \author Candice Bentejac
 * \date November 20, 2015
 * \brief Header for the Test class (inherits from the Command class). 
 */

#ifndef _TEST_HPP_
#define _TEST_HPP_

#include "Command.hpp"

class Test : public Command
{
  public:
    /**
     * \brief Test constructor.
     * \param Connector c the connector of the test command.
     * \return A Test object.
     */
    Test(Connector c);
    /**
     * \brief Test constructor.
     * \param string argument the flag and path to test.
     * \param Connector c the connector of the test command.
     * \return A Test object.
     */
    Test(std::string arg, Connector c);
    /**
     * \brief Parse a test command line.
     * \return A Test object.
     */
    static Test parseTest(std::string cmd, int p);
    /**
     * \brief Test destructor.
     */
    ~Test();
};

#endif
