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
**         This is the "engine" file, with several functions for handling the board that
**         were originally just part of the main function.
*****************************************************************************************/

#include "critter.hpp"
#include "ant.hpp"
#include "doodlebug.hpp"

#include <iostream>

using std::cout;
using std::endl;

//I think the board would be better off as a class (so all these board management
// functions would be member functions and all the Critters would have a pointer to the
// same instance of this class), but from the assignment specifications it seems like the
// board being a dynamic array (and nothing more than that) is what Terry intends for us
// to do. I suppose he said this out of consideration for us (being unfamiliar with OOP
// in this introductory course) but it does kind of reduce the OOP-ness of this prorgam.

/*****************************************************************************************
** Function: drawBoard
** Description: Draws the board
** Parameters: Takes a dynamic 2D array of pointer to Critter along with integer values
**             to indicate the array's dimensions.
** Pre-Conditions: The array is initialised properly and the integers passed in are
**                 accurate dimensions of the array.
** Post-Conditions: The board will be drawn (with blank spaces, X, and O).
*****************************************************************************************/
void drawBoard(Critter ***board, int grid_row, int grid_col)
{
    for (int row_index = 0; row_index < grid_row; row_index++)
    {
        for (int col_index = 0; col_index < grid_col; col_index++)
        {
            if (board[row_index][col_index] == NULL)
            {
                cout << " ";
            }
            else if (board[row_index][col_index]->getSpecies() == ANT)
            {
                cout << "O";
            }
            else if (board[row_index][col_index]->getSpecies() == DOODLEBUG)
            {
                cout << "X";
            }
        }
        cout << endl;
    }
}
    
/*****************************************************************************************
** Function: doodleMove
** Description: Moves them doodles.
** Parameters: Takes a dynamic 2D array of pointer to Critter along with integer values
**             to indicate the array's dimensions.
** Pre-Conditions: The array is initialised properly and the integers passed in are
**                 accurate dimensions of the array.
** Post-Conditions: The movement of the doodles will be updated on the temporary board
**                  (not the main board).
*****************************************************************************************/
void doodleMove(Critter ***board, int grid_row, int grid_col)
{
    for (int row_index = 0; row_index < grid_row; row_index++)
    {
        for (int col_index = 0; col_index < grid_col; col_index++)
        {
            if (board[row_index][col_index] != NULL &&
                board[row_index][col_index]->getSpecies() == DOODLEBUG)
            {
                board[row_index][col_index]->move();
            }
        }
    }
}

/*****************************************************************************************
** Function: antMove
** Description: Moves them ants.
** Parameters: Takes a dynamic 2D array of pointer to Critter along with integer values
**             to indicate the array's dimensions.
** Pre-Conditions: The array is initialised properly and the integers passed in are
**                 accurate dimensions of the array.
** Post-Conditions: The movement of the ants will be updated on the temporary board
**                  (not the main board).
*****************************************************************************************/
void antMove(Critter ***board, int grid_row, int grid_col)
{
    for (int row_index = 0; row_index < grid_row; row_index++)
    {
        for (int col_index = 0; col_index < grid_col; col_index++)
        {
            if (board[row_index][col_index] != NULL &&
                board[row_index][col_index]->getSpecies() == ANT)
            {
                if (board[row_index][col_index]->getDyingFlag() )
                {
                    delete board[row_index][col_index];
                    board[row_index][col_index] = NULL;
                }
                else
                {
                    board[row_index][col_index]->move();
                }
            }
        }
    }
}

/*****************************************************************************************
** Function: doodleBreed
** Description: Breeds them doodles.
** Parameters: Takes a dynamic 2D array of pointer to Critter along with integer values
**             to indicate the array's dimensions.
** Pre-Conditions: The array is initialised properly and the integers passed in are
**                 accurate dimensions of the array.
** Post-Conditions: Possible offspring of the doodles will be updated on the temporary
**                  board (not the main board).
*****************************************************************************************/
void doodleBreed(Critter ***board, int grid_row, int grid_col)
{
    for (int row_index = 0; row_index < grid_row; row_index++)
    {
        for (int col_index = 0; col_index < grid_col; col_index++)
        {
            if (board[row_index][col_index] != NULL &&
                board[row_index][col_index]->getSpecies() == DOODLEBUG)
            {
                board[row_index][col_index]->breed();
            }
        }
    }
}

/*****************************************************************************************
** Function: doodleBreed
** Description: Breeds them ants.
** Parameters: Takes a dynamic 2D array of pointer to Critter along with integer values
**             to indicate the array's dimensions.
** Pre-Conditions: The array is initialised properly and the integers passed in are
**                 accurate dimensions of the array.
** Post-Conditions: Possible offspring of the ants will be updated on the temporary
**                  board (not the main board).
*****************************************************************************************/
void antBreed(Critter ***board, int grid_row, int grid_col)
{
    for (int row_index = 0; row_index < grid_row; row_index++)
    {
        for (int col_index = 0; col_index < grid_col; col_index++)
        {
            if (board[row_index][col_index] != NULL &&
                board[row_index][col_index]->getSpecies() == ANT)
            {
                board[row_index][col_index]->breed();
            }
        }
    }
}

/*****************************************************************************************
** Function: clearDying
** Description: Removes the dessicated corpses of doodles from the board.
**              Can also remove ants (but ants are removed in earlier function).
** Parameters: Takes a dynamic 2D array of pointer to Critter along with integer values
**             to indicate the array's dimensions.
** Pre-Conditions: The array is initialised properly and the integers passed in are
**                 accurate dimensions of the array.
** Post-Conditions: Dead Critters will be removed from board if they're still on it.
*****************************************************************************************/
void clearDying(Critter ***board, int grid_row, int grid_col)
{
    for (int row_index = 0; row_index < grid_row; row_index++)
    {
        for (int col_index = 0; col_index < grid_col; col_index++)
        {
            if (board[row_index][col_index] != NULL &&
                board[row_index][col_index]->getDyingFlag() )
            {
                delete board[row_index][col_index];
                board[row_index][col_index] = NULL;
            }
        }
    }
}