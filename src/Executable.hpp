#ifndef _EXECUTABLE_HPP_
#define _EXECUTABLE_HPP_

#include "Base.hpp"

class Executable
{
  public:
    Executable(char* exec);
    ~Executable();

    char* getExecutable();
    void setExecutable(char* exec);
    void readExecutable();

  protected:
    char* executable;
};

#endif
