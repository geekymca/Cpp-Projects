/*****************************************************************************************
** Program Filename: doodleant
**                   (This is the first time the main function file is called main.cpp
**                    though. Interesting executable name, boring source name.)
** Author: Albert Chang
** Date: 2016-2-1
** Description: Weak predator prey simulation for polymorphism practice.
** Input: Strictly speaking, the program takes no arguments but the user will be prompted
**        for the board size and initial number of bugs.
** Output: Again, nothing is returned and no files are created by the program, but
**         the state of the board will be displayed on the console to keep the user
**         abreast of the situation on the game board.
**
**         This is the Critter header file.
*****************************************************************************************/

#ifndef CRITTER_HPP
#define CRITTER_HPP

#define ANT_BREED 3
#define DOODLE_BREED 8
#define DOODLE_STARVE 3
//These constants are used to define the period of breeding and starving. So having a
// value of one would mean daily (timestep-ly) breeding and instant starvation on any day
// (again, meaning timestep) in which eating did not occur. Entering a value of 0 should
// have the same effect as a value of 1 if my logic is working as intended. Please don't
// actually try using a value of 0 though.

enum bugtype {ANT, DOODLEBUG};
enum compass {NORTH, EAST, SOUTH, WEST};
//I use these enums to simplify logic (for myself, while reading code) in the member
// functions for Critter and its two derived classes.

class Critter
{
public:
    Critter(Critter*** world, Critter*** temp_world, 
            int row, int col, int total_row, int total_col);
    
    virtual void move() = 0;
    virtual void breed() = 0;
      
    bool isEmpty(int row, int col);
    bool tempIsEmpty(int row, int col);
    
    bool isOccupied(int row, int col);
    bool tempIsOccupied(int row, int col);
    
    int getSpecies();
    
    void dying();
    bool getDyingFlag();
     
    virtual ~Critter() {};
protected:
    int species,     //species will use the enum above
        breed_timer,
        grid_rows,   //all Critters will be imbued with knowledge
        grid_cols,   // about the size of their world
        current_row, //they need to know their own position as well
        current_col;
        
    Critter ***world,      //these two triple-pointers are part of the Critters'
            ***temp_world; //  knowledge of their world (and how to move around in it)
        
    bool dying_flag;
};

#endif