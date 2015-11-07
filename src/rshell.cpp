/**
 * \file rshell.cpp
 * \author Candice Bentejac
 * \date November 6, 2015
 * \brief File containing the main.
 */

#include "ParsedCommand.hpp"
#include <unistd.h>

using namespace std;

static void userInfo(); // Declaration of the static function

int main()
{
  string line;
  cout << "Entering rshell." << endl << endl;
  bool quit = false;

  while(!quit) // While quit == false, the user hasn't typed "exit"
  {
    userInfo(); 
    getline(cin, line);
    ParsedCommand cmd(line);
    cmd.execute(quit); // Updates quit value if needed
  }

  return 0;
}


static void userInfo() // Displays username, hostname, and the rshell prompt (€)
{
  char* username = getlogin();
  if(username == NULL)
  {
    perror("getlogin failed");
    exit(1);
  }

  char hostname[30];
  int r_host = gethostname(hostname, 30);
  
  if(r_host == -1)
  {
    perror("gethostname failed");
    exit(1);
  }
  cout << "[" << username << "@" << hostname << "]€ ";
}
