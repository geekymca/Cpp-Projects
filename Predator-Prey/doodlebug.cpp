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
**         This is the Doodlebug implementation file.
*****************************************************************************************/

#include "doodlebug.hpp"
#include "critter.hpp"

#include <cstdlib>

/*****************************************************************************************
** Function: Doodlebug constructor
** Description: Brings a Doodlebug to life.
** Parameters: Takes two dynamic arrays of pointer to Critter, and four integers to
**             represent the size of the arrays and the position of the Doodlebug.
** Pre-Conditions: The array is initialised properly and the integers passed in are
**                 valid (accurate dimensions and valid coordinates).
** Post-Conditions: The Doodlebug will be created.
*****************************************************************************************/
Doodlebug::Doodlebug(Critter ***the_world, Critter ***transient_world, 
                     int the_row, int the_col, int total_rows, int total_cols)
          : Critter(the_world, transient_world, the_row, the_col, total_rows, total_cols)
{
    species = DOODLEBUG;
    breed_timer = DOODLE_BREED;
    starve_timer = DOODLE_STARVE;
    belly_full_flag = false;
}

/*****************************************************************************************
** Function: move (for Doodlebug)
** Description: Possibly moves a Doodlebug.
** Parameters: Nothing, works with world and Doodlebug location.
** Pre-Conditions: The world (both real and temporary) is properly initialised and the
**                 locations of Critters in the world is correct.
** Post-Conditions: The Doodlebug will try to eat and move. Failing that, it will try to
**                  just move anywhere. Failing that, it will sit and slowly starve.
**                  Doodlebugs are only slightly above the Ant in cognitive ability.
*****************************************************************************************/
void Doodlebug::move()
{
    int *food_list,
    //This was once a vector, but is now an array.
        list_size,
        new_row,
        new_col;
        
    food_list = new int[4];
    list_size = 0;
        
    new_row = current_row;
    new_col = current_col;
    
    belly_full_flag = false;
    
    if (isOccupied(current_row + 1, current_col) 
       && world[current_row + 1][current_col]->getSpecies() == ANT
       && !world[current_row + 1][current_col]->getDyingFlag() )
    {
        food_list[list_size] = SOUTH;
        list_size++;
    }
    if (isOccupied(current_row - 1, current_col) 
       && world[current_row - 1][current_col]->getSpecies() == ANT
       && !world[current_row - 1][current_col]->getDyingFlag() )
    {
        food_list[list_size] = NORTH;
        list_size++;
    }
    if (isOccupied(current_row, current_col + 1) 
       && world[current_row][current_col + 1]->getSpecies() == ANT
       && !world[current_row][current_col + 1]->getDyingFlag() )
    {
        food_list[list_size] = EAST;
        list_size++;
    }
    if (isOccupied(current_row, current_col - 1) 
       && world[current_row][current_col - 1]->getSpecies() == ANT
       && !world[current_row][current_col - 1]->getDyingFlag() )
    {
        food_list[list_size] = WEST;
        list_size++;
    }
    
    if (list_size != 0)
    {
        int random_index,
            random_result;
        
        random_index = rand() % list_size;
        random_result = food_list[random_index];
        
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
        
        world[new_row][new_col]->dying();
        temp_world[new_row][new_col] = this;
        current_row = new_row;
        current_col = new_col;
        belly_full_flag = true;
        starve_timer = DOODLE_STARVE;
    }
    else if (!belly_full_flag)
    {
        starve_timer--;
        //One step closer to the grave.
        
        if (starve_timer <= 0)
        {
            dying();
        }
        
        int one_direction = rand() % 4;
        
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
    
    delete [] food_list;
    food_list = NULL;
}

/*****************************************************************************************
** Function: breed (for Doodlebug)
** Description: Attempts to create life from existing Doodlebug.
** Parameters: Nothing, uses member variables only.
** Pre-Conditions: The Doodlebug's member variables are valid (undefined behavior could
**                 result if the member variables were somehow made invalid).
** Post-Conditions: Creates offspring if the Doodlebug is ready to breed and has an empty
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
void Doodlebug::breed()
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
            = new Doodlebug(world, temp_world, new_row, new_col, grid_rows, grid_cols);
                
            breed_timer = DOODLE_BREED;
        }
        
        delete [] neighbor_list;
        neighbor_list = NULL;
    }
    else
    {
        breed_timer--;
    }
}