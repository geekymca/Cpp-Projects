/*****************************************************************************************
** Program Filename: conway
** Author: Albert Chang
** Date: 2016-1-8
** Description: Runs a basic version of Conway's Game of Life. The board is limited to
**              40x20 visible cells, and there aren't many options for the initial state.
** Input: Strictly speaking, the program takes no arguments but the user will be asked
**        to decide on the initial state of the board.
** Output: Again, nothing is returned and no files are created by the program, but
**         the state of the board will be displayed on the console to keep the user
**         abreast of the situation on the game board.
**
** This file will contain the draw_board and update_board functions. In a sense, this
** file contains the primary engine of the game.
*****************************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

#include "prototypes.hpp"

/*****************************************************************************************
** Function: draw_board
** Description: Draws a 40x20 Conway's Game Board for Conway's Game of Life.
** Parameters: Takes a 2D array (of ints) to represent the game board.
** Pre-Conditions: The double pointer passed in properly represents a valid 2D array
**                 with 0 or 1 for each of the cell's values (0 for empty, 1 for living)
** Post-Conditions: Nothing is actually done by the draw_board function to the game board
**                  passed in, it draws the board to the console and nothing more.
*****************************************************************************************/

/*Note that the printing of a '*' indicates an error in the game board. This isn't
mentioned to the user though, and it's just for possible debugging purposes.*/
void draw_board(int **game_board) {
    cout << "/----------------------------------------\\" << endl;
    for (int row = GHOST_BOUND; row < (TOTAL_ROWS - GHOST_BOUND); row++) {
        cout << "|";
        for (int column = GHOST_BOUND; column < (TOTAL_CLMN - GHOST_BOUND); column++) {
            if (game_board[row][column] == DEAD) {
                cout << " ";
            }
            else if (game_board[row][column] == LIVE) {
                cout << "=";
            }
            else {
                cout << "*";
            }
        }
        cout << "|" << endl;
    }
    cout << "\\----------------------------------------/" << endl;
}

/*****************************************************************************************
** Function: update_board
** Description: Updates a 40x20 Conway's Game Board for Conway's Game of Life.
** Parameters: Takes a 2D array (of ints) to represent the game board.
** Pre-Conditions: The double pointer passed in properly represents a valid 2D array
**                 with 0 or 1 for each of the cell's values (0 for empty, 1 for living)
** Post-Conditions: The state of the game board will have advanced by one tick for each
**                  time the function is called.
*****************************************************************************************/

void update_board(int **game_board) {
    int **temp_board,
        neighbor_sum = 0;
    
    temp_board = new int*[TOTAL_ROWS];

    for (int index = 0; index < (TOTAL_ROWS); index++) {
        temp_board[index] = new int[TOTAL_CLMN];
    }
    
    /*Unlike the game board, the temporary board is not initialised to 0. It will be
    filled by proper values soon enough if the function is working properly.*/
    
    /*First we calculate the next state of game_board and save this into temp_board.
    Note that the DEAD_LINE (which is just 1) is used to leave the buffer of one line
    along the edges as we slightly cheat the game.*/
    for (int row = DEAD_LINE; row < (TOTAL_ROWS - DEAD_LINE); row++) {
        for (int column = DEAD_LINE; column < (TOTAL_CLMN - DEAD_LINE); column++) {
            neighbor_sum = game_board[row - 1][column - 1] + game_board[row - 1][column]
                         + game_board[row - 1][column + 1] + game_board[row][column + 1]
                         + game_board[row + 1][column + 1] + game_board[row + 1][column]
                         + game_board[row + 1][column - 1] + game_board[row][column - 1];
            if ((neighbor_sum == 3) || 
            ((neighbor_sum == 2) && game_board[row][column] == LIVE)) {
                temp_board[row][column]=LIVE;
            }
            else {
                temp_board[row][column]=DEAD;
            }
        }
    }
    
    /*Next we copy all the temp_board values back into game_board.*/
    for (int row = DEAD_LINE; row < (TOTAL_ROWS - DEAD_LINE); row++) {
        for (int column = DEAD_LINE; column < (TOTAL_CLMN - DEAD_LINE); column++) {
            game_board[row][column] = temp_board[row][column];
        }
    }
    
    /*Cleaning up the dynamic temporary board array before exiting the function.*/
    for (int index = 0; index < TOTAL_ROWS; index++) {
        delete [] temp_board[index];
    }
    delete [] temp_board;
    temp_board = NULL;
}