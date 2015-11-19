/**
 * \file Connector.hpp
 * \author Candice Bentejac
 * \date November 6, 2015
 * \brief Header for the Connector class.
 */

#ifndef _CONNECTOR_HPP_
#define _CONNECTOR_HPP_

#include "Base.hpp"

class Connector
{
  public:
    /**
     * \brief Connector constructor.
     * \param string r the representation of the connector.
     * \param bool success the boolean that indicates whether the connector 
     * needs the success of the previous instruction to execute the next one.
     * \return A new Connector object.
     */
    Connector(std::string r, bool success, int p);
    /** 
     * \brief Connector destructor.
     */
    ~Connector();

    /**
     * \brief Returns the string representation of the connector.
     * \return The Connector representation.
     */
    std::string getRepresentation();
    /**
     * \brief Returns the precedence value of the connector.
     * \return The int value.
     */
    int getPrecedence();
    /**
     * \brief Sets the string representation of the connector.
     * \param string r the new representation of the connector;
     */
    void setRepresentation(std::string r); 
    /**
     * \brief Indicates if the connector needs the previous instruction
     * to have succeeded to run the next one.
     * \return A boolean: false if the success is not needed; true if it is.
     */
    bool getNeedSuccess();
    /**
     * \brief Sets the "needs success of the previous instruction" condition.
     * \param bool success: false if the success is not needed; true if it is.
     */
    void setNeedSuccess(bool success);

  protected:
    /**
     * \brief String representation of the connector.
     */
    std::string representation;
    /** 
     * \brief "Needs success of the previous instruction" condition.
     */
    bool needSuccess;
    /**
     * \brief Int representation of connector's level of precedence
     */
    int precedence;
};

#endif
