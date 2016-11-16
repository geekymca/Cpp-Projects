#Albert Chang, CS162-400
#makefile for Lab5
#Not sure what type of header should be in a makefile

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

SOURCES = main.cpp engine.cpp critter.cpp ant.cpp doodlebug.cpp

HEADERS = critter.hpp ant.hpp doodlebug.hpp

OBJECTS = main.o engine.o critter.o ant.o doodlebug.o

OUTPUT = doodleant

OUTPUTWIN = doodleant.exe

ass2: ${OBJECTS} ${HEADERS}
	${CXX} ${OBJECTS} -o ${OUTPUT}
    
${OBJECTS}: ${SOURCES}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)
    
clean:
	rm -f ${OUTPUT} ${OBJECTS}