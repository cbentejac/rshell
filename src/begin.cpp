#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

int main()
{
  string cmd;

  char* username = getlogin();
  if(username == NULL)
    perror("getlogin failed");

  char host[30];
  int r_host = gethostname(host, 30);
  if(r_host == -1)
    perror("gethostname failed");

  while(cmd != "exit")
  {
    cout << "[" << username << "@" << host << "]R$ ";
    cin >> cmd;
  }
  return 0;
}
