all:
	g++ -Wall -Werror -ansi -pedantic rshell.cpp Connector.cpp Semicolon.cpp DoubleAnd.cpp DoubleOr.cpp Arguments.cpp Executable.cpp -o rshell
