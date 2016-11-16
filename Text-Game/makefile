#Albert Chang, CS162-400
#makefile for Assignment5 (final project
#Not sure what type of header should be in a makefile

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

SOURCES = main.cpp game.cpp backpack.cpp spaces.cpp bathroom.cpp bedroom.cpp kitchen.cpp livingroom.cpp roommate.cpp outside.cpp

HEADERS = main.hpp game.hpp backpack.hpp spaces.hpp bathroom.hpp bedroom.hpp kitchen.hpp livingroom.hpp roommate.hpp outside.hpp

OBJECTS = main.o game.o backpack.o spaces.o bathroom.o bedroom.o kitchen.o livingroom.o roommate.o outside.o

OUTPUT = buster

ass5: ${OBJECTS} ${HEADERS}
	${CXX} ${OBJECTS} -o ${OUTPUT}
    
${OBJECTS}: ${SOURCES}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)
    
clean:
	rm -f ${OUTPUT} ${OBJECTS}