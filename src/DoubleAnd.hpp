/**
 * \file DoubleAnd.hpp
 * \author Candice Bentejac, Samuel Magness
 * \date November 20, 2015
 * \brief Header for the DoubleAnd class (inherits from the Connector class).
 */

#ifndef _DOUBLE_AND_
#define _DOUBLE_AND_

#include "Connector.hpp"

class DoubleAnd : public Connector
{
  public:
    /**
     * \brief DoubleAnd constructor.
     * \param int p the precedence level of the connector.
     * \return A DoubleAnd object.
     */
    DoubleAnd(int p);
    /**
     * \brief DoubleAnd destructor.
     */
    ~DoubleAnd();
};

#endif
