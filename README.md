# rshell
Written by Candice Bentéjac and Samuel Magness for the University of California - Riverside CS100 class (Fall 2015).

## Description of rshell
The program consists in a shell called **rshell** and written in C++. This shell must be able to perform the following steps:

1. Print a command prompt (like $).

2. Read in a command (which has the form `cmd = executable [ argumentList ] [ connector cmd ]`) on one line.

`&&`, `||` and `;` are the three connectors that can be used to link commands between each other on the same command line. They work as following:
- **;**: The next command is always executed.
- **&&**: The next command is executed only if the current one succeeds.
- **||**: The next command is executed only if the current one fails.

Precedence operators (`(` and `)`) can also be used to change the precedence of the returns of commands, connectors, and chains of connectors.

## Features
- In order to distinguish the normal shell from the **rshell**, `€` will be used instead of `$` as a command prompt. 
- **rshell** displays the username and the host name using the form `[username@hostname]`.
- # can be used to comment a part of command. Everything located after # will be ignored.
- To exit **rshell**, type `exit`.
- An error message is displayed whenever a command fails.
- The `test`command can be used either with the brackets `[]` or the `test` instruction and is compatible with the connectors. 


## Design
The commands are represented by the `Command` class. A Command object is composed of three other objects: an Executable object (defined in the `Executable` class), an Arguments object (defined in the `Arguments` class) and a Connector object (defined in the `Connector` class). Special commands (that is to say, commands that cannot be executed by the `execvp()` function) can be defined as subclasses of `Command`, inheriting from it. It is then possible to add any new command that has a special behavior.

The connectors are specified in subclasses that inherit from the `Connector` class: each connector is a subclass of `Connector` and adding a new connector then just consists in adding a new subclass of `Connector`. Every Connector is composed of a string representation of itself and a boolean that tells if it needs the success of the previous run command to execute the next one.

The ParsedCommand class creates objects that contain the user input (which will be parsed) and a vector of Command objects which stores the different commands contained in the user input. When the ParsedCommand object is created, the Command vector is empty. `ParsedCommand` then parse the user input and stores the results of this parsing in the vector: it first removes the comments, divides the user input in substrings, create Command objects from each of these substrings and then add them to the vector. The Command objects contained in the vector are then executed using the `execute()` function. If a Command object actually inherits from the `Command` class and is thus not supported by `execvp()`, we just need to add a `if` case in the `execute()` function, specifying that if this particular command must be run, then it will use the functions defined in its class instead of `execvp()`, and another `if` case when we're trying to determine whether or not the next command should be run.


## Installing and running rshell
### Installing
The following lines will allow you to download **rshell** and compile it from the root.

##### Homework 1
```
$ git clone https://github.com/xArchange/rshell.git
$ cd rshell
$ git checkout hw1
$ make
```

##### Homework 2
```
$ git clone https://github.com/xArchange/rshell.git
$ cd rshell
$ git checkout hw2
$ make
```

### Running
To run **rshell** from the root, type `$ bin/rshell`. Then type any command. **rshell** can support both single commands and comands using connectors. As an example, you can enter the following command lines:
```
€ ls -lR
€ ls -a; echo hello && mkdir test || echo world; git status
```

You can also use the `test` command and the precedence operators:
```
€ test -e /test/file/path && echo “path exists”
€ [ -e /test/file/path ] && echo “path exists”
€ (echo A && echo B) || (echo C && echo D)
```

## Known bugs
- The `cd` isn't recognized and thus systematically fails.

- If the command is an `echo` and the user has surrounded the message to display with simple or double quotes, **rshell** will also display these quotes, unlike **bash**. On the other side, **rshell** won't display the connector or `#` with `echo`, even if they're between quotes.

- If a command is spelled incorrectly or doesn't exist and thus leads to a fail of `execvp`, it is impossible to directly exit **rshell** using the `exit`command. As an example, if three commands lead to a fail of `execvp`, it will be necessary to run `exit` three times before it becomes effective. _It's like `exit` had to go through a stack of failed commands to be effective._

- If there are several connectors following each other (like `&& && && &&`) or a sequence of characters corresponding to the connectors (like `||||||||`), **rshell** tries to execute and fails.

- `echo A && ((echo B && echo C) || echo D) && echo E` prints 
```
A
B
C
C
E
```


## Authors
#### Homework 1
Candice Bentéjac (cbent002)

Université de Bordeaux / University of California, Riverside

#### Homework 2
Samuel Magness (smagn001) & Candice Bentéjac (cbent002)

University of California, Riverside & Université de Bordeaux / University of California, Riverside
