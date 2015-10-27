#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

void user_info()
{
  char* username = getlogin();
  if(username == NULL)
  {
    perror("getlogin failed");
  }

  char hostname[30];
  int r_host = gethostname(hostname, 30);
 
  if(r_host == -1)
  {
    perror("gethostname failed");
  }
  cout << "[" << username << "@" << hostname << "]€ ";
}

int main()
{
  string cmd;

  cout << "Entering rshell." << endl;
  while(cmd != "exit")
  {
    user_info();
    cin >> cmd;
  }
  return 0;
}
