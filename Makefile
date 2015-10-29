all:
	g++ -Wall -Werror -ansi -pedantic src/rshell.cpp src/Connector.cpp src/Semicolon.cpp src/DoubleAnd.cpp src/DoubleOr.cpp src/Arguments.cpp src/Executable.cpp -o src/rshell
