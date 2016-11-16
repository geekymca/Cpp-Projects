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
**         This is the main file, with the main function.
*****************************************************************************************/

#include <cstdlib>
#include <unistd.h>

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "prototypes.hpp"

int main() {
    int **game_board = NULL,
        user_input = 0;
    /*The user_input variable is for user options, because I don't feel like letting the
    user use other characters besides digits for all the options. The next bool flag is
    just for a simple check later.*/
    bool acceptable_flag = false;
    
    unsigned int current_time = 0;
    /*I figured we might as well keep track of how many generations passed.*/
    
    game_board = new int*[TOTAL_ROWS];
    
    for (int index = 0; index < TOTAL_ROWS; index++) {
        game_board[index] = new int[TOTAL_CLMN];
    }
    
    for (int row = 0; row < TOTAL_ROWS; row++) {
        for (int column = 0; column < (TOTAL_CLMN); column++) {
        game_board[row][column] = 0;
        }
    }
    
    do {
    cout << "Warning: This program only accepts integers as user input." << endl
         << "         No other characters besides integers will work," << endl
         << "         and they might even break the program." << endl
         << "         Please enter the integer 0 if you understand: ";
    
    cin >> user_input;
    } while (user_input != 0);
    
    /* I have commented out some code for creating a completely random initial
    state over here. Try it out if you want to see something more interesting.
    Remember to add includes for cstdlib and ctime if you want to try it.*/
    // srand(time(0));
    
    // for (int row = DEAD_LINE; row < (TOTAL_ROWS - DEAD_LINE); row++) {
        // for (int column = DEAD_LINE; column < (TOTAL_CLMN - DEAD_LINE); column++) {
            // game_board[row][column] = rand()%2;
        // }
    // }
    
    cout << endl
         << "This is Conway's Game of Life. You have three options for" << endl
         << "Conway's Initial Shape on Conway's Game Board." << endl
         << "1: Glider" << endl
         << "2: Glider gun" << endl
         << "3: Oscillator" << endl
         << "4: Describe these options to me (this is not a shape)" << endl
         << "Your choice (enter an integer): ";
         
    cin >> user_input;
    
    /*Some basic error checking in a loop because it's always fun. I know we try to
    avoid hard-coding constants, but you can't seriously expect me to use preprocessor
    definitions for every menu I create.*/
    while ( (user_input < 1) || (user_input > 3) ) {
        if (user_input == 4) {
            cout << endl << "A glider looks like this: " << endl
                 << "= =" << endl
                 << " ==" << endl
                 << " = " << endl
                 << "It will attempt to escape the board to the southeast." << endl
                 << "A glider gun looks like this: " << endl
                 << "                        =           " << endl 
                 << "                      = =           " << endl 
                 << "            ==      ==            ==" << endl 
                 << "           =   =    ==            ==" << endl 
                 << "==        =     =   ==              " << endl 
                 << "==        =   = ==    = =           " << endl 
                 << "          =     =       =           " << endl 
                 << "           =   =                    " << endl 
                 << "            ==                      " << endl 
                 << "As you might expect, it shoots gliders to the southeast." << endl
                 << "An oscillator looks like this: " << endl
                 << "   " << endl
                 << "===" << endl
                 << "   " << endl
                 << "It doesn't do much at all and just blinks at you in place."
                 << endl << endl;
        }
        
        cout << "Please enter an integer from 1 to 4. Here are the options again:"
             << endl << "1: Glider" << endl
             << "2: Glider gun" << endl
             << "3: Oscillator" << endl
             << "4: Describe these options to me (this is not a shape)" << endl
             << "Your choice (enter an integer): ";
    
        cin >> user_input;
    }
    
    /*The next step is done in a loop as well to simplify the user choice if he isn't
    happy with how the starting board is drawn.*/
    do {
        /*This first endline is used to make the formatting neater in the drawing
        functions. I think it should be separate from the functions as the functions
        shouldn't start by printing an endline*/
        cout << endl;
        
        switch (user_input) {
            case 1: 
                draw_glider(game_board);
                break;
            case 2:
                draw_glidergun(game_board);
                break;
            case 3:
                draw_oscillator(game_board);
                break;
        }
        
        cout << "This is the initial state of the board:" << endl;
        draw_board(game_board);
        cout << "Is this acceptable?" << endl
             << "0: No        1: Yes" << endl
             << "Your choice (0 or 1): ";
             
        cin >> user_input;
             
        /*Some more basic error checking of the same format.*/
        while ( (user_input < 0) || (user_input > 1) ) {
            cout << "Please enter 0 for 'no', or 1 for 'yes': ";
            cin >> user_input;
        }
        
        if (user_input == 1) {
            acceptable_flag = true;
        }
        else {
            /*Reinitialise the array if the user didn't like the placement.*/
            for (int row = 0; row < TOTAL_ROWS; row++) {
                for (int column = 0; column < TOTAL_CLMN; column++) {
                game_board[row][column] = 0;
                }
            }
            while ( (user_input < 1) || (user_input > 3) ) {
                cout << "Please enter an integer from 1 to 4. Here are the options again:"
                     << endl << "1: Glider" << endl
                     << "2: Glider gun" << endl
                     << "3: Oscillator" << endl
                     << "4: Describe these options to me (this is not a shape)" << endl
                     << "Your choice (enter an integer): ";

                cin >> user_input;
                
                if (user_input == 4) {
                    cout << endl << "A glider looks like this: " << endl
                         << "= =" << endl
                         << " ==" << endl
                         << " = " << endl
                         << "It will attempt to escape the board to the southeast."
                         << endl << "A glider gun looks like this: " << endl
                         << "                        =           " << endl
                         << "                      = =           " << endl
                         << "            ==      ==            ==" << endl
                         << "           =   =    ==            ==" << endl
                         << "==        =     =   ==              " << endl
                         << "==        =   = ==    = =           " << endl
                         << "          =     =       =           " << endl
                         << "           =   =                    " << endl
                         << "            ==                      " << endl
                         << "As you might expect, it shoots gliders to the southeast."
                         << endl << "An oscillator looks like this: " << endl
                         << "   " << endl
                         << "===" << endl
                         << "   " << endl
                         << "It doesn't do much at all and just blinks at you in place."
                         << endl << endl;
                }
            }
        }
    } while (!acceptable_flag);
    
    cout << endl << "Now the game has started in earnest. You're not playing though. "
         << "Just watching." << endl
         << "If you would like the game to stop after a certain number" << endl
         << "of generations, enter it now. (Enter a negative number" << endl
         << "to have the game run forever): ";

         cin >> user_input;
   
    /*The following block uses two functions suggested by TAs and other students, which
    are unix exclusive (I'm not sure if the first is unix exclusive, but the second
    definitely is). They may need to be removed if running on a Windows machine.
    The animation will be way too fast without usleep though, so a different type of
    delay would have to be added depending on the operating system.*/
    do {
        system("clear"); //This line is probably unix exclusive
        cout << endl << "Current game time: " << current_time << endl;
        draw_board(game_board);
                update_board(game_board);
       
        usleep(100000); //This line is unix exclusive
        current_time++;

    } while (current_time != (user_input + 1) );
    /*It's (user_input + 1) because the first board drawn is at time 0, and the
    time updates at the end of the loop.*/
    
    /*Cleaning up the dynamic game board array before exiting.*/
    for (int index = 0; index < TOTAL_ROWS; index++) {
        delete [] game_board[index];
    }
    delete [] game_board;
    game_board = NULL;
    
    return 0;
}
        


    