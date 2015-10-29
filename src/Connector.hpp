#ifndef _CONNECTOR_HPP_
#define _CONNECTOR_HPP_

#include "Base.hpp"

class Connector
{
  public:
    Connector(std::string r, bool success, bool fail);
    ~Connector();

    std::string getRepresentation();
    void setRepresentation(std::string representation); 
    bool getNeedSuccess();
    void setNeedSuccess(bool success);
    bool getNeedFail();
    void setNeedFail(bool fail);

  protected:
    std::string representation;
    bool needSuccess;
    bool needFail;
};

#endif
