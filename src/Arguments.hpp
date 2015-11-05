#ifndef _ARGUMENTS_HPP
#define _ARGUMENTS_HPP

#include "Base.hpp"

class Arguments {

  public:
    Arguments(std::string arg);
    ~Arguments();

    std::string getArguments();
    void setArguments(std::string  arg);
    void readArguments();

  protected:
    std::string arguments;

};

#endif
