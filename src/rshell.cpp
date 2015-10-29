#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "Semicolon.hpp"
#include "DoubleAnd.hpp"
#include "DoubleOr.hpp"
#include "Arguments.hpp"
#include "Executable.hpp"

using namespace std;

void userInfo()
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

int main()
{
  cout << "TEST CONNECTORS" << endl << endl;
  
  Semicolon s;
  cout << "Semicolon : " << s.getRepresentation() << s.getNeedSuccess() << s.getNeedFail() << endl;

  DoubleAnd a;
  cout << "DoubleAnd : " << a.getRepresentation() << a.getNeedSuccess() << a.getNeedFail() << endl;

  DoubleOr o;
  cout << "DoubleOr : " << o.getRepresentation() << o.getNeedSuccess() << o.getNeedFail() << endl;

  cout << endl << "TEST ARGUMENTS" << endl << endl;
  char test_char[30] = "test char";
  Arguments ar(test_char);

  ar.readArguments();
  ar.setArguments(const_cast<char*>("New test"));
  ar.readArguments();
  char* test_echo = ar.getArguments();
  cout << test_echo << endl;


  cout << endl << "TEST EXECUTABLE" << endl << endl;
  Executable exec(test_char);
  exec.readExecutable();
  exec.setExecutable(const_cast<char*>("New exec"));
  exec.readExecutable();
  test_echo = exec.getExecutable();
  cout << test_echo << endl << endl;
  
  string cmd;

  cout << "Entering rshell." << endl;
  while(cmd != "exit")
  {
    userInfo();
    getline(cin, cmd);
  }
  return 0;
}
