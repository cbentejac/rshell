#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include "Base.hpp"
#include <vector>

class Command 
{
  public:
    Command(); // Default constructor
    Command(std::string cmd); // Constructor 
    ~Command(); // Destructor

    std::string getCommand();
    void setCommand(std::string cmd);

  protected:
    std::string command; // Command line
    vector<std::string> cmd_list; // Command line that has been "sorted"
}

#endif
