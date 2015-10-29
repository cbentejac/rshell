#ifndef _ARGUMENTS_HPP
#define _ARGUMENTS_HPP

#include "Base.hpp"

class Arguments {

  public:
    Arguments(char* arg);
    ~Arguments();

    char* getArguments();
    void setArguments(char* arg);
    void readArguments();

  protected:
    char* arguments;

};

#endif
