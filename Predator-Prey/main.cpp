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
**         This is the main file, with the main function.
*****************************************************************************************/

#include "critter.hpp"
#include "ant.hpp"
#include "doodlebug.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using std::cout;
using std::endl;
using std::cin;

//We generally think classes should be in their own source files with their own headers,
// but the board management functions aren't part of a class. (In fact, they were just
// simple loops inside the main function before I decided to move them out to clean up
// the code a bit.)
void drawBoard(Critter ***board, int grid_row, int grid_col);
void doodleMove(Critter ***board, int grid_row, int grid_col);
void antMove(Critter ***board, int grid_row, int grid_col);
void doodleBreed(Critter ***board, int grid_row, int grid_col);
void antBreed(Critter ***board, int grid_row, int grid_col);
void clearDying(Critter ***board, int grid_row, int grid_col);

int main ()
{
    //Seed the RNG at the beginning of the program before anything is done.
    srand(time(0) );
    
    Critter ***overworld,
            ***underworld;
            
    int doodle_count,
        ant_count,
        grid_row,
        grid_col,
        num_cells,
        bias_fix,
        user_input,
        generation = 0;
        
    cout << "This program only accepts integer input, with no validation." << endl
         << "Please don't break the program." << endl << endl
         << "How many rows do you want in the world? ";
         
    cin >> grid_row;
        
    cout << "How many columns? ";
    
    cin >> grid_col;
    
    num_cells = grid_row * grid_col;
    bias_fix = num_cells;
    //The bias fix will be used during initial placement of the bugs. This helps to
    // prevent all the bugs starting at the upper left (towards 0,0) of the world.
    
    cout << "Before we continue to the bug count, note that ants are placed before the"
         << endl
         << "doodlebugs and if you enter a sum of ants and doodlebugs that exceeds the"
         << endl
         << "size of the world, the initialisation will be stuck in an infinite loop."
         << endl
         << "For reference, you have " << num_cells << " total cells to place them."
         << endl
         << "How many ants do you want? ";
         
    cin >> ant_count;
    
    cout << "You have " << num_cells - ant_count 
         << " cells left to place doodlebugs." << endl
         << "How many doodlebugs do you want? ";
         
    cin >> doodle_count;

    //Create the two identical worlds, starting with row then column.
    overworld = new Critter**[grid_row];
    underworld = new Critter**[grid_row];
    
    for (int index = 0; index < grid_row; index++)
    {
        overworld[index] = new Critter*[grid_col];
        underworld[index] = new Critter*[grid_col];
    }
    
    //Make sure the worlds are initialised with NULL pointers.
    for (int row_index = 0; row_index < grid_row; row_index++)
    {
        for (int col_index = 0; col_index < grid_col; col_index++)
        {
            overworld[row_index][col_index] = NULL;
            underworld[row_index][col_index] = NULL;
        }
    }
    
    //Place the Ants into the world.
    do
    {
        for (int row_index = 0; row_index < grid_row; row_index++)
        {
            for (int col_index = 0; col_index < grid_col; col_index++)
            {
                if (ant_count == 0)
                {
                    break;
                }
                if (rand() % bias_fix == 0 && overworld[row_index][col_index] == NULL)
                {
                    overworld[row_index][col_index] 
                    = new Ant(overworld, underworld, row_index, col_index, grid_row, grid_col);
                    ant_count--;
                }
            }
            if (ant_count == 0)
            {
                break;
            }
        }
        if (bias_fix > 1)
        {
            bias_fix--;
        }
    } while (ant_count > 0);
    
    //Reinitialise the bias fix for Doodlebug placement.
    bias_fix = num_cells;
    
    //Place the Doodlebugs into the world.
    do
    {
        for (int row_index = 0; row_index < grid_row; row_index++)
        {
            for (int col_index = 0; col_index < grid_col; col_index++)
            {
                if (doodle_count == 0)
                {
                    break;
                }
                if (rand() % bias_fix == 0 && overworld[row_index][col_index] == NULL)
                {
                    overworld[row_index][col_index] 
                    = new Doodlebug(overworld, underworld, row_index, col_index, grid_row, grid_col);
                    doodle_count--;
                }
            }
            if (doodle_count == 0)
            {
                break;
            }
        }
        if (bias_fix > 1)
        {
            bias_fix--;
        }
    } while (doodle_count > 0);
    
    cout << "Enter a number of timesteps to run the simulation for: ";
    
    cin >> user_input;
    
    do
    {
        //Print the board out first, to show initial state
        system("clear");
        drawBoard(overworld, grid_row, grid_col);
        cout << "Time: " << generation << endl;
        
        //Check for continuation when the timer is up
        if (user_input <= 0)
        {
            cout << "If you want to continue the simulation, enter a number of timesteps"
                 << endl 
                 << "to indicate how much longer to run, or enter 0 to quit."
                 << endl << "Your choice: ";
                 
            cin >> user_input;
        }
        user_input--;
        
        //Minor delay for animation purposes before continuing
        usleep(250000);
        
        //First move the Doodlebugs
        doodleMove(overworld, grid_row, grid_col);
        
        //Next move the Ants, (eaten Ants are removed)
        antMove(overworld, grid_row, grid_col);
        
        //The transient spiritual underworld is copied back to the overworld
        // for manifestation into the physical realm
        for (int row_index = 0; row_index < grid_row; row_index++)
        {
            for (int col_index = 0; col_index < grid_col; col_index++)
            {
                overworld[row_index][col_index] = underworld[row_index][col_index];
            }
        }
        //The underworld is not emptied out yet because it's still of use.
        
        //Then the Doodlebugs breed
        doodleBreed(overworld, grid_row, grid_col);
        
        //Then the Ants breed
        antBreed(overworld, grid_row, grid_col);
        
        //The transient spiritual underworld is copied back to the overworld
        // for manifestation into the physical realm (again)
        for (int row_index = 0; row_index < grid_row; row_index++)
        {
            for (int col_index = 0; col_index < grid_col; col_index++)
            {
                overworld[row_index][col_index] = underworld[row_index][col_index];
                underworld[row_index][col_index] = NULL;
            }
        }
        //The underworld is emptied out this time because we're done with movement
        // and creation of new life.
        
        //Clear off any starved Doodlebugs
        clearDying(overworld, grid_row, grid_col);
        
        generation++;
    } while (user_input >= 0);
    
    //In order, delete the Critters, the second level array, the top level array.
    for (int row_index = 0; row_index < grid_row; row_index++)
    {
        for (int col_index = 0; col_index < grid_col; col_index++)
        {
            if (overworld[row_index][col_index] != NULL)
            {
                delete overworld[row_index][col_index];
            }
            if (underworld[row_index][col_index] != NULL)
            {
                delete underworld[row_index][col_index];
            }
        }
        delete [] overworld[row_index];
        delete [] underworld[row_index];
    }
    
    delete [] overworld;
    delete [] underworld;
    
    return 0;
}
    
    