CCPP = g++
CPPFLAGS =  -std=c++11 -std=c++11

SRC := $(wildcard *.cpp */*.cpp lib/*/*.cpp lib/*/*/*.cpp)
OBJ = main

default: build

build:
	$(CCPP) $(CPPFLAGS) -o $(OBJ) $(SRC)

run: build
	./$(OBJ)

cleanup:
	rm $(OBJ)