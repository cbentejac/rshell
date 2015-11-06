/**
 * \file Connector.hpp
 * \author
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
     * \param bool success the boolean that indicates whether the connector needs the success of the previous instruction to execute the next one.
     * \param bool fail the boolean that indicates whether the connector need the fail of the previous instruction to run the next one.
     * \return A new Connector object.
     */
    Connector(std::string r, bool success, bool fail);
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
     * \brief Sets the string representation of the connector.
     * \param string r the new representation of the connector;
     */
    void setRepresentation(std::string r); 
    /**
     * \brief Indicates if the connector needs the previous instruction to have succeeded to run the next one.
     * \return A boolean: false if the success is not needed; true if it is.
     */
    bool getNeedSuccess();
    /**
     * \brief Sets the "needs success of the previous instruction to run the next one" condition.
     * \param bool success: false if the success is not needed; true if it is.
     */
    void setNeedSuccess(bool success);
    /**
     * \brief Indicates if the connector needs the previous instruction to have failed to run the next one.
     * \return A boolean: false if the fail is not needed, true if it is.
     */
    bool getNeedFail();
    /**
     * \brief Sets the "needs fail of the previous instruction to run the next one" condition.
     * \param bool fail: false if the fail is not needed; true if it is.
     */
    void setNeedFail(bool fail);

  protected:
    /**
     * \brief String representation of the connector.
     */
    std::string representation;
    /** 
     * \brief "Needs success of the previous instruction to run the next one" condition.
     */
    bool needSuccess;
    /**
     * \brief "Needs fail of the previous instruction to run the next one" condition.
     */
    bool needFail;
};

#endif
