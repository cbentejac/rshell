# rshell
Written by Candice Bentéjac for the University of California - Riverside CS100 class (Fall 2015).

## Description of rshell
The program consists in a shell called **rshell** and written in C++. This shell must be able to perform the following steps:

1. Print a command prompt (like $).

2. Read in a command (which has the form `cmd = executable [ argumentList ] [ connector cmd ]`) on one line.

`&&`, `||` and `;` are the three connectors that can be used to link commands between each other on the same command line. They work as following:
- **;**: The next command is always executed.
- **&&**: The next command is executed only if the current one succeeds.
- **||**: The next command is executed only if the current one fails.

## Features
- In order to distinguish the normal shell from the **rshell**, `€` will be used instead of `$` as a command prompt. 
- **rshell** displays the username and the host name using the form `[username@hostname]`.
- # can be used to comment a part of command. Everything located after # will be ignored.
- To exit **rshell**, type `exit`.
- An error message is displayed whenever a command fails.
- (The `test`command can be used either with the brackets `[]` or the `test` instruction and is working perfectly fine with the connectors.) ==> Need to finish testSuccess to be able to run following commands.


## Installing and running rshell
### Installing
The following lines will allow you to download **rshell** and compile it from the root.
```
$ git clone https://github.com/xArchange/rshell.git
$ cd rshell
$ git checkout hw1
$ make
```

### Running
To run **rshell** from the root, type `$ bin/rshell`. Then type any command. **rshell** can support both single commands and comands using connectors. As an example, you can enter the following command lines:
```
€ ls -lR
€ ls -a; echo hello && mkdir test || echo world; git status
```

## Known bugs
- The `cd` isn't recognized and thus systematically fails.

- If the command is an `echo` and the user has surrounded the message to display with simple or double quotes, **rshell** will also display these quotes, unlike **bash**. On the other side, **rshell** won't display the connector with `echo`, even if they're between quotes.

- If a command is spelled incorrectly or doesn't exist and thus leads to a fail of `execvp`, it is impossible to directly exit **rshell** using the `exit`command. As an example, if three commands lead to a fail of `execvp`, it will be necessary to run `exit` three times before it becomes effective. _It's like `exit` had to go through a stack of failed commands to be effective._


- If there are several connectors following each other (like `&& && && &&`) or a sequence of characters corresponding to the connectors (like `||||||||`), **rshell** tries to execute and fails.

### Fixed bugs
- Commands that can normally be run with or without arguments fail if the user tries to run them without arguments.

- `exit` is always executed, no matter the value of the connector. Ex: `ls -a || exit` will still exit, even though `ls -a` was successfully executed.

- If the command line is empty, the program will still try to execute it, which leads to an `execvp` error message.

- If the last command (meaning that there's nothing to execute after it) ends with a connector that is not a semicolon, the program tries to execute an empty command, which is a case similar to the "empty line" bug.

- If the connectors are not separated from the rest of the command line by spaces, then they're not recognized as connectors but as arguments, which often leads to an execution problem.

- In the command `€ ls -lR /`, the `/` character is considered as an unvalid option and the command consequently fails. _The problem was actually linked to the number of arguments._

## Author
Candice Bentéjac (cbent002)

Université de Bordeaux / University of California, Riverside
