# MAKEFILE
#
# MakeFile creada para compilación de este proyecto

PROGNAME = test
CPPFLAGS = -std=c++14 -Wall
OBJS  = main.o
OBJS += game.o
OBJS += player.o
OBJS += tilemap.o
OBJS += rays.o
OBJS += line.o
OBJS += -lsfml-graphics
OBJS += -lsfml-window
OBJS += -lsfml-system
OBJS += -lsfml-audio


all: $(OBJS)
	g++ $(CPPFLAGS) -o $(PROGNAME) $(OBJS)

line: line.cpp line.hpp
	g++ $(CPPFLAGS) -c line.cpp

rays: rays.cpp rays.hpp
	g++ $(CPPFLAGS) -c rays.cpp

tilemap: tilemap.cpp tilemap.hpp
	g++ $(CPPFLAGS) -c tilemap.cpp

player: player.cpp player.hpp
	g++ $(CPPFLAGS) -c player.cpp

game: game.cpp game.hpp
	g++ $(CPPFLAGS) -c game.cpp

main: main.cpp
	g++ $(CPPFLAGS) -c main.cpp

clean:
	-rm *.o