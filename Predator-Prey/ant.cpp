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
**         This is the Ant implementation file.
*****************************************************************************************/

#include "ant.hpp"
#include "critter.hpp"

#include <cstdlib>

/*****************************************************************************************
** Function: Ant constructor
** Description: Brings an Ant to life.
** Parameters: Takes two dynamic arrays of pointer to Critter, and four integers to
**             represent the size of the arrays and the position of the Ant.
** Pre-Conditions: The array is initialised properly and the integers passed in are
**                 valid (accurate dimensions and valid coordinates).
** Post-Conditions: The Ant will be created.
*****************************************************************************************/
Ant::Ant(Critter ***the_world, Critter ***transient_world, 
         int the_row, int the_col, int total_rows, int total_cols)
    : Critter(the_world, transient_world, the_row, the_col, total_rows, total_cols)
{
    species = ANT;
    breed_timer = ANT_BREED;
}

/*****************************************************************************************
** Function: move (for Ant)
** Description: Possibly moves an Ant.
** Parameters: Nothing, works with world and Ant location.
** Pre-Conditions: The world (both real and temporary) is properly initialised and the
**                 locations of Critters in the world is correct.
** Post-Conditions: The Ant will try to move. It might fail. Ants are pretty stupid.
*****************************************************************************************/
void Ant::move()
{
    if (!getDyingFlag() )
    {
        int new_row = current_row,
            new_col = current_col,
            one_direction = rand() % 4;
        
        if (one_direction == SOUTH)
        {
            new_row++;
        }
        else if (one_direction == NORTH)
        {
            new_row--;
        }
        else if (one_direction == EAST)
        {
            new_col++;
        }
        else if (one_direction == WEST)
        {
            new_col--;
        }
        
        if (isEmpty(new_row, new_col) && tempIsEmpty(new_row, new_col) )
        {
            temp_world[new_row][new_col] = this;
            current_row = new_row;
            current_col = new_col;
        }
        else
        {
            temp_world[current_row][current_col] = this;
        }
    }
}

/*****************************************************************************************
** Function: breed (for Ant)
** Description: Attempts to create life from existing Ant.
** Parameters: Nothing, uses member variables only.
** Pre-Conditions: The Ant's member variables are valid (undefined behavior could
**                 result if the member variables were somehow made invalid).
** Post-Conditions: Creates offspring if the Ant is ready to breed and has an empty
**                  cell to pop out a kid (resets the breeding timer afterwards), does
**                  nothing if the breeding timer is ready but there's no empty cell for
**                  a kid, and counts the timer down by one if the timer is not ready.
*****************************************************************************************/
//Note that we use tempIsEmpty() rather than isEmpty() for breeding because movement
// has already occurred, and we assume there's no risk of collision. Also note that the
// check is for breeding timer <= 1 for simplicity to the user (developer-user).
// This way, if the developer wants the Critter to breed every day, the period can be
// set to 1, every other day set to 2, every third day set to 3, and so on. This makes
// the label "timer" somewhat inaccurate, as a timer would trigger upon reaching 0.

void Ant::breed()
{
    if (breed_timer <= 1)
    {
        int *neighbor_list,
        //This was once a vector, but is now an array.
            list_size;
            
        neighbor_list = new int[4];
        list_size = 0;

        if (tempIsEmpty(current_row + 1, current_col) )
        {
            neighbor_list[list_size] = SOUTH;
            list_size++;
        }
        if (tempIsEmpty(current_row - 1, current_col) )
        {
            neighbor_list[list_size] = NORTH;
            list_size++;
        }
        if (tempIsEmpty(current_row, current_col + 1) )
        {
            neighbor_list[list_size] = EAST;
            list_size++;
        }
        if (tempIsEmpty(current_row, current_col - 1) )
        {
            neighbor_list[list_size] = WEST;
            list_size++;
        }
        
        if (list_size != 0)
        {
            int new_row,
                new_col,
                random_index,
                random_result;
            
            new_row = current_row;
            new_col = current_col;
            
            random_index = rand() % list_size;
            random_result = neighbor_list[random_index];
            
            if (random_result == SOUTH)
            {
                new_row++;
            }
            else if (random_result == NORTH)
            {
                new_row--;
            }
            else if (random_result == EAST)
            {
                new_col++;
            }
            else if (random_result == WEST)
            {
                new_col--;
            }
            
            temp_world[new_row][new_col]
            = new Ant(world, temp_world, new_row, new_col, grid_rows, grid_cols);
                
            breed_timer = ANT_BREED;
        }
        
        delete [] neighbor_list;
        neighbor_list = NULL;
    }
    else
    {
        breed_timer--;
    }
}