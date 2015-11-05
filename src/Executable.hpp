#ifndef _EXECUTABLE_HPP_
#define _EXECUTABLE_HPP_

#include "Base.hpp"

class Executable
{
  public:
    Executable(std::string exec);
    ~Executable();

    std::string getExecutable();
    void setExecutable(std::string exec);
    void readExecutable();

  protected:
    std::string executable;
};

#endif
