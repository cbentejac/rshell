#include "ParsedCommand.hpp"
#include <unistd.h>

using namespace std;

static void userInfo();

int main()
{
  string line;

  cout << "Entering rshell." << endl << endl;
  bool quit = false;

  while(!quit)
  {
    userInfo();
    getline(cin, line);
    ParsedCommand cmd(line);
    cmd.execute(quit);
  }
  return 0;
}

static void userInfo()
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
