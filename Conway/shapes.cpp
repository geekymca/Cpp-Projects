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
** This file will contain the draw_glider, draw_glidergun, and draw_oscillator functions.
** The three functions are very similar, so I figured they should be in the same file.
*****************************************************************************************/

#include "prototypes.hpp"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/*Note that the offsets for creating the initial shapes are also not defined to the
preprocessor ahead of time, because that seems like an excessive amount of definitions.*/

/*****************************************************************************************
** Function: draw_glider
** Description: Draws the starting glider for Conway's Game of Life.
** Parameters: Takes a 2D array (of ints) to represent the game board.
** Pre-Conditions: The double pointer passed in properly represents a valid 2D array
**                 with 0 for all of the array's cells (it has to be initialised).
** Post-Conditions: The previously empty (initialised with all 0) array will have a
**                  glider at the position the user specified.
*****************************************************************************************/

void draw_glider(int **game_board) {
    int start_row = 0,
        start_clm = 0;
    
    cout << "Please select the initial position for the glider. The position you" << endl
         << "select will be the northwestmost cell of the glider (if you envision" << endl
         << "it as existing in a 3x3 square) with the other eight cells extending"<< endl
         << "to the east and south of the cell." << endl
         << "The 20 rows and 40 columns of the 20x40 board are numbered with" << endl
         << "the northwestmost cell as row 1, column 1, extending to" << endl
         << "the southeastmost cell as row 20, column 40." << endl
         << "Because the glider cannot start outside of the grid, the highest" << endl
         << "possible starting position is going to be row 18, column 38." 
         << endl << endl;
    
    cout << "Please first enter the row number: ";
    cin >> start_row;
    cout << "Now enter the column number: ";
    cin >> start_clm;

    /*A simple check whether the user's position is within the bounds.*/
    while( ((start_row < 1) || (start_row > (BOARD_ROWS - GLIDER_DIM))) || 
    ((start_clm < 1) || (start_clm > (BOARD_CLMN - GLIDER_DIM))) ) {
        cout << "You entered one or more invalid values. Remember that " << endl
             << "rows can range from 1 to 18, and columns from 1 to 38." << endl
             << "Please enter the row number: ";
        cin >> start_row;
        cout << "Please enter the column number: ";
        cin >> start_clm;
    }
    /*I asked the user to start from index 1, but I will still convert to index 0 in a
    sense with some arithmetic.*/
    start_row = start_row - 1 + GHOST_BOUND;
    start_clm = start_clm - 1 + GHOST_BOUND;
    
    game_board[start_row][start_clm] = game_board[start_row][start_clm + 2]
    = game_board[start_row + 1][start_clm + 1] = game_board[start_row +1][start_clm + 2]
    = game_board[start_row + 2][start_clm + 1] = LIVE;
}

/*****************************************************************************************
** Function: draw_glidergun
** Description: Draws the starting glider gun for Conway's Game of Life.
** Parameters: Takes a 2D array (of ints) to represent the game board.
** Pre-Conditions: The double pointer passed in properly represents a valid 2D array
**                 with 0 for all of the array's cells (it has to be initialised).
** Post-Conditions: The previously empty (initialised with all 0) array will have a
**                  glider gun at the position the user specified.
*****************************************************************************************/

/*I'm going to use s_r and s_c instead of start_row and start_clm, and g_b instead of
game_board for the next function to save some time in typing up the pattern for a
glider gun. The format of the function is very much the same as the format for a glider,
just even longer because of the much larger pattern in the glider gun.*/
void draw_glidergun(int **g_b) {
    int s_r = 0,
        s_c = 0;
    
    cout << "Please select the initial position for the glider gun. The position" << endl
         << "you select will be the northwestmost cell of the glider's box (if" << endl
         << "you envision it as existing in a 9x36 box) with the rest of the box" << endl
         << "extending to the east and south of the cell." << endl
         << "The 20 rows and 40 columns of the 20x40 board are numbered with" << endl
         << "the northwestmost cell as row 1, column 1, extending to" << endl
         << "the southeastmost cell as row 20, column 40." << endl
         << "Because the glider gun cannot start outside of the grid, the highest" << endl
         << "possible starting position is going to be row 12, column 5." 
         << endl << endl;
    
    cout << "Please first enter the row number: ";
    cin >> s_r;
    cout << "Now enter the column number: ";
    cin >> s_c;
        
    /*A simple check whether the user's position is within the bounds.*/
    while( ((s_r < 1) || (s_r > (BOARD_ROWS - GGUN_ROWS))) || 
    ((s_c < 1) || (s_c > (BOARD_CLMN - GGUN_CLMN))) ) {
        cout << "You entered one or more invalid values. Remember that " << endl
             << "rows can range from 1 to 12, and columns from 1 to 5." << endl
             << "Please enter the row number: ";
        cin >> s_r;
        cout << "Please enter the column number: ";
        cin >> s_c;
    }
    /*I asked the user to start from index 1, but I will still convert to index 0 in a
    sense with some arithmetic.*/
    s_r = s_r - 1 + GHOST_BOUND;
    s_c = s_c - 1 + GHOST_BOUND;
    
    
    g_b[s_r + 4][s_c] = g_b[s_r + 5][s_c] = g_b[s_r + 4][s_c + 1] = g_b[s_r + 5][s_c + 1]
    = g_b[s_r + 4][s_c + 10] = g_b[s_r + 5][s_c + 10] = g_b[s_r + 6][s_c + 10]
    = g_b[s_r + 3][s_c + 11] = g_b[s_r + 7][s_c + 11] = g_b[s_r + 2][s_c + 12]
    = g_b[s_r + 8][s_c + 12] = g_b[s_r + 2][s_c + 13] = g_b[s_r + 8][s_c + 13] 
    = g_b[s_r + 5][s_c + 14] = g_b[s_r + 3][s_c + 15] = g_b[s_r + 7][s_c + 15] 
    = g_b[s_r + 4][s_c + 16] = g_b[s_r + 5][s_c + 16] = g_b[s_r + 6][s_c + 16] 
    = g_b[s_r + 5][s_c + 17] = g_b[s_r + 2][s_c + 20] = g_b[s_r + 3][s_c + 20]
    = g_b[s_r + 4][s_c + 20] = g_b[s_r + 2][s_c + 21] = g_b[s_r + 3][s_c + 21]
    = g_b[s_r + 4][s_c + 21] = g_b[s_r + 1][s_c + 22] = g_b[s_r + 5][s_c + 22]
    = g_b[s_r + 5][s_c + 22] = g_b[s_r + 1][s_c + 24] = g_b[s_r + 5][s_c + 24]
    = g_b[s_r + 6][s_c + 24] = g_b[s_r + 2][s_c + 34] = g_b[s_r + 2][s_c + 35]
    = g_b[s_r + 3][s_c + 34] = g_b[s_r + 3][s_c + 35] = g_b[s_r][s_c + 24] = LIVE;
    /*Pardon the long definition, but I'm not sure how else to set all these values in
    the game_board (abbreviated for the first time as g_b here) aside from manually
    setting all the values for the proper cells.*/
}

/*****************************************************************************************
** Function: draw_oscillator
** Description: Draws the starting oscillator for Conway's Game of Life.
** Parameters: Takes a 2D array (of ints) to represent the game board.
** Pre-Conditions: The double pointer passed in properly represents a valid 2D array
**                 with 0 for all of the array's cells (it has to be initialised).
** Post-Conditions: The previously empty (initialised with all 0) array will have a
**                  simple blinker oscillator at the position the user specified.
*****************************************************************************************/

void draw_oscillator(int **game_board) {
    int start_row = 0,
        start_clm = 0;
    
    cout << "Please select the initial position for the oscillator. The position" << endl
         << "you select will be the northwestmost cell of the oscillator's box" << endl
         << "(if you envision it as existing in a 3x3 square, even though it" << endl
         << "alternates between a 1x3 and 3x1 formation without ever touching the" << endl
         << "corners of the square) with the other eight cells extending to the" << endl
         << "east and south of the cell." << endl
         << "The 20 rows and 40 columns of the 20x40 board are numbered with" << endl
         << "the northwestmost cell as row 1, column 1, extending to" << endl
         << "the southeastmost cell as row 20, column 40." << endl
         << "Because the oscillator cannot start outside of the grid, the highest" << endl
         << "possible starting position is going to be row 18, column 38." 
         << endl << endl;
    
    cout << "Please first enter the row number: ";
    cin >> start_row;
    cout << "Now enter the column number: ";
    cin >> start_clm;
        
    /*A simple check whether the user's position is within the bounds.*/
    while( ((start_row < 1) || (start_row > (BOARD_ROWS - GLIDER_DIM))) || 
    ((start_clm < 1) || (start_clm > (BOARD_CLMN - GLIDER_DIM))) ) {
        cout << "You entered one or more invalid values. Remember that " << endl
             << "rows can range from 1 to 18, and columns from 1 to 38." << endl
             << "Please enter the row number: ";
        cin >> start_row;
        cout << "Please enter the column number: ";
        cin >> start_clm;
    }
    /*I asked the user to start from index 1, but I will still convert to index 0 in a
    sense with some arithmetic.*/
    start_row = start_row - 1 + GHOST_BOUND;
    start_clm = start_clm - 1 + GHOST_BOUND;
    
    game_board[start_row + 1][start_clm] = game_board[start_row + 1][start_clm + 1]
    = game_board[start_row + 1][start_clm + 2] = LIVE;
}
