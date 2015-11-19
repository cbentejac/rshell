/**
 * \file Semicolon.hpp
 * \author Candice Bentejac
 * \date November 6, 2015
 * \brief Header for the Semicolon class (inherits from the Connector class).
 */

#ifndef _SEMICOLON_HPP_
#define _SEMICOLON_HPP_

#include "Connector.hpp"

class Semicolon : public Connector 
{
  public:
    /**
     * \brief Semicolon constructor.
     * \return A Semicolon object.
     */
    Semicolon(int p);
    /**
     * \brief Semicolon destructor.
     */
    ~Semicolon();
};

#endif
