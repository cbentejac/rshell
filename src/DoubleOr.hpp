/**
 * \file DoubleOr.hpp
 * \author Candice Bentejac, Samuel Magness
 * \date November 20, 2015
 * \brief Header for the DoubleOr class (inherits from the Connector class).
 */

#ifndef _DOUBLE_OR_
#define _DOUBLE_OR_

#include "Connector.hpp"

class DoubleOr : public Connector
{
  public:
    /**
     * \brief DoubleOr constructor.
     * \param int p the precedence level of the connector.
     * \return A DoubleOr object.
     */
    DoubleOr(int p);
    /**
     * \brief DoubleOr destructor.
     */
    ~DoubleOr();
};

#endif
