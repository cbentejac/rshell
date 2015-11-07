# Variables
CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic
SOURCES = src/rshell.cpp src/Connector.cpp src/Semicolon.cpp src/DoubleAnd.cpp src/DoubleOr.cpp src/Arguments.cpp src/Executable.cpp src/Command.cpp src/ParsedCommand.cpp
EXECUTABLE = rshell

all: 
	$(MAKE) rshell

rshell:
	mkdir bin; \
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE); \
	mv $(EXECUTABLE) ./bin


clean:
	rm -rf bin



