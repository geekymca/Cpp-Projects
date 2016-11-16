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
** This is just a prototype file with preprocessor definitions and function prototypes.
** Nothing fancy, just having it all in one place for simplicity.
*****************************************************************************************/

#ifndef PROTOTYPES_HPP
#define PROTOTYPES_HPP


#define GHOST_BOUND 6
#define DEAD_LINE 1
#define BOARD_ROWS 20
#define BOARD_CLMN 40
/*I think CLMN looks better than COLS as an abbreviation of columns.*/

#define TOTAL_ROWS (GHOST_BOUND * 2 + BOARD_ROWS)
#define TOTAL_CLMN (GHOST_BOUND * 2 + BOARD_CLMN)

#define GLIDER_DIM (3 - 1)
#define BLINKER_DIM (3 - 1)
#define GGUN_ROWS (9 - 1)
#define GGUN_CLMN (36 - 1)
/*I use constant expressions - 1 to show that the constants are defined relative to
the dimensions of the pattern.*/

#define LIVE 1
#define DEAD 0

void draw_board(int **);
void update_board(int **);
void draw_glider(int **);
void draw_glidergun(int **);
void draw_oscillator(int **);


#endif