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
**         This is the Doodlebug header file.
*****************************************************************************************/

#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP

#include "critter.hpp"

class Doodlebug:public Critter
{
public:
    Doodlebug(Critter*** world, Critter*** temp_world, 
             int row, int col, int total_row, int total_col);
    void move();
    void breed();
    ~Doodlebug() {};
private:
    bool belly_full_flag;//Doodlebugs need to be sure to monitor their diet, so this
    int starve_timer;    // boolean flag and integer timer are here to help them out
};

#endif