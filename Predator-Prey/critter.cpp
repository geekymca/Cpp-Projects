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
**         This is the Critter implementation file.
*****************************************************************************************/

#include "critter.hpp"

#include <cstdlib>

/*****************************************************************************************
** Function: Critter constructor
** Description: Brings a Critter to life (but not really, because only sub-Critters
**              are actually useful).
** Parameters: Takes two dynamic arrays of pointer to Critter, and four integers to
**             represent the size of the arrays and the position of the Critter.
** Pre-Conditions: The array is initialised properly and the integers passed in are
**                 valid (accurate dimensions and valid coordinates).
** Post-Conditions: The Critter will be created (again, not really).
*****************************************************************************************/
Critter::Critter(Critter ***the_world, Critter ***transient_world, 
                 int the_row, int the_col, int total_rows, int total_cols)
{
    world = the_world;
    temp_world = transient_world;
    current_row = the_row;
    current_col = the_col;
    grid_rows = total_rows;
    grid_cols = total_cols;
    dying_flag = false;
}

/*****************************************************************************************
** Function: isEmpty
** Description: Checks if a cell in the real world is empty.
** Parameters: Takes two integer coordinates.
** Pre-Conditions: The integers are valid (valid integers, not coordinates).
** Post-Conditions: Return true if the real world coordinates represent an empty cell.
**                  False otherwise.
*****************************************************************************************/
bool Critter::isEmpty(int row, int col)
{
    if (row >= 0 && col >= 0 && row < grid_rows && col < grid_cols)
    {
        if (world[row][col] == NULL)
        {
            return true;
        }
    }
    return false;
}

/*****************************************************************************************
** Function: tempIsEmpty
** Description: Checks if a cell in the temporary world is empty.
** Parameters: Takes two integer coordinates.
** Pre-Conditions: The integers are valid (valid integers, not coordinates).
** Post-Conditions: Return true if the temporary world coordinates represent an empty
**                  cell. False otherwise.
*****************************************************************************************/
bool Critter::tempIsEmpty(int row, int col)
{
    if (row >= 0 && col >= 0 && row < grid_rows && col < grid_cols)
    {
        if (temp_world[row][col] == NULL)
        {
            return true;
        }
    }
    return false;
}

/*****************************************************************************************
** Function: isOccupied
** Description: Checks if a cell in the real world is occupied.
** Parameters: Takes two integer coordinates.
** Pre-Conditions: The integers are valid (valid integers, not coordinates).
** Post-Conditions: Return true if the real world coordinates contains a Critter.
**                  False otherwise.
*****************************************************************************************/
bool Critter::isOccupied(int row, int col)
{
    if (row >= 0 && col >= 0 && row < grid_rows && col < grid_cols)
    {
        if (world[row][col] != NULL)
        {
            return true;
        }
    }
    return false;
}

/*****************************************************************************************
** Function: tempIsOccupied
** Description: Checks if a cell in the temporary world is occupied.
** Parameters: Takes two integer coordinates.
** Pre-Conditions: The integers are valid (valid integers, not coordinates).
** Post-Conditions: Return true if the temporary world coordinates contains a Critter.
**                  False otherwise.
*****************************************************************************************/
bool Critter::tempIsOccupied(int row, int col)
{
    if (row >= 0 && col >= 0 && row < grid_rows && col < grid_cols)
    {
        if (temp_world[row][col] != NULL)
        {
            return true;
        }
    }
    return false;
}

/*****************************************************************************************
** Function: getSpecies
** Description: Returns the species of the Critter (an integer, because I used an enum).
** Parameters: Nothing, returns a member variable only.
** Pre-Conditions: The Critter's species is an integer value.
** Post-Conditions: Returns the integer value of the species. Again, I'm using an enum,
**                  so this has a meaning for this program but not really a meaning as
**                  an integer value.
*****************************************************************************************/
int Critter::getSpecies()
{
    return species;
}

/*****************************************************************************************
** Function: dying
** Description: Marks the Critter for death to claim at the end of this timestep.
** Parameters: Nothing, sets a member variable only.
** Pre-Conditions: The Critter's dying flag exists.
** Post-Conditions: The Critter's dying flag is set, and Death will know to claim
**                  the Critter when sweeping the world for souls.
*****************************************************************************************/
void Critter::dying()
{
    dying_flag = true;
}

/*****************************************************************************************
** Function: getDyingFlag
** Description: Returns the state of the dying flag.
** Parameters: Nothing, returns a member variable only.
** Pre-Conditions: The Critter's dying flag exists.
** Post-Conditions: Returns the dying flag for Death or other Critters to see. 
**                  
**                  Predators in our world only eat live prey, because there is no 
**                  challenge or honor in feeding on those that can't put up a fight.
**                  Scavengers not welcome.
*****************************************************************************************/
bool Critter::getDyingFlag()
{
    return dying_flag;
}