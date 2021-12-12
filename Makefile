
### This is the normal makefile to build tests

CPPVERFLAG = -std=c++17
EXTRAARGS = -mavx2 -march=native
LDFLAGS = -lpthread -lstdc++
WARNINGS = -Wall -Wpedantic -Wextra -Werror
CC ?= g++
BIN = ./bin

dep_manager: install_remove.o depend.o main.o
	$(shell mkdir -p $(BIN))
	$(shell mv install_remove.o $(BIN)/install_remove.o)
	$(shell mv depend.o $(BIN)/depend.o)
	$(shell mv main.o $(BIN)/main.o)
	$(CC) -o dependency_manager $(BIN)/install_remove.o $(BIN)/depend.o $(BIN)/main.o -I./include -O0 -g $(CPPVERFLAG) $(LDFLAGS) $(EXTRAARGS) $(WARNINGS)

install_remove.o: install_remove.cc
	$(CC) -g -c install_remove.cc -I./include -O0 $(CPPVERFLAG) $(LDFLAGS) $(EXTRAARGS) $(WARNINGS)

./depend.o: depend.cc
	$(CC) -g -c depend.cc -I./include -O0 $(CPPVERFLAG) $(LDFLAGS) $(EXTRAARGS) $(WARNINGS)

./main.o: main.cc 
	$(CC) -g -c main.cc -I./include -O0 $(CPPVERFLAG) $(LDFLAGS) $(EXTRAARGS) $(WARNINGS)

	
clean:
	rm -Rf $(BIN) dependency_manager
