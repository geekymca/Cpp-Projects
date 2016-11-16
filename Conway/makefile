#Albert Chang, CS162-400
#makefile for Assignment1
#Not sure what type of header should be in a makefile

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

SOURCES = conway.cpp drawupdate.cpp shapes.cpp

HEADERS = prototypes.hpp

OUTPUT = conway
    
ass1: ${SOURCES} ${HEADERS}
	${CXX} ${SOURCES} -o ${OUTPUT}
    
clean:
	rm -f ${OUTPUT}