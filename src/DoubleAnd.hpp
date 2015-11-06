/**
 * \file DoubleAnd.hpp
 * \author Candice Bentejac
 * \date November 6, 2015
 * \brief Header for the DoubleAnd class, which inherits from the Connector class.
 */

#ifndef _DOUBLE_AND_
#define _DOUBLE_AND_

#include "Connector.hpp"

class DoubleAnd : public Connector
{
  public:
    /**
     * \brief DoubleAnd constructor.
     * \return A DoubleAnd object.
     */
    DoubleAnd();
    /**
     * \brief DoubleAnd destructor.
     */
    ~DoubleAnd();
};

#endif
