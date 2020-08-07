# MAKEFILE
#
# MakeFile creada para compilación de este proyecto

PROGNAME = test
CPPFLAGS = -std=c++14 -Wall
OBJS  = main.o
OBJS += game.o
OBJS += -lsfml-graphics
OBJS += -lsfml-window
OBJS += -lsfml-system
OBJS += -lsfml-audio


all: $(OBJS)
	g++ $(CPPFLAGS) -o $(PROGNAME) $(OBJS)

game: game.cpp game.hpp
	g++ $(CPPFLAGS) -c game.cpp

main: main.cpp
	g++ $(CPPFLAGS) -c main.cpp

clean:
	-rm *.o