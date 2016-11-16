/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the main file. (There is a helper function too.)
*****************************************************************************************/

#include "main.hpp"

#include "game.hpp"
#include "spaces.hpp"
#include "backpack.hpp"
#include "bathroom.hpp"
#include "roommate.hpp"
#include "livingroom.hpp"
#include "kitchen.hpp"
#include "bedroom.hpp"

#include <iostream>
#include <string>
using std::cin;
using std::getline;
using std::cout;
using std::endl;
using std::string;

int main()
{
    bool quit = false;
    
    string user_input;
    
    Game *theGame;
    
    do
    {
        system("clear");
        
        cout << "Would you like to play my game?" << endl
             << "Enter 'y' or 'n': ";
             
        getline(cin, user_input);
        
        if (user_input == "y")
        {
            theGame = new Game;
            theGame->play();
            delete theGame;
        }
        
        else if (user_input == "n")
        {
            cout << "See you next time." << endl;
            quit = true;
        }
        
        else
        {
            cout << "I didn't understand that. Enter only a single lowercase 'y' or 'n'."
                 << endl;
            
            pausePrompt();
        }
        
    } while (!quit);
    
    return 0;
}

/*****************************************************************************************
** Function: pausePrompt
** Description: Wastes time until the user presses enter.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: Time is wasted. (It's not a real "press enter to continue" because
**                  I'm using getline, but it works well enough for me.)
*****************************************************************************************/
void pausePrompt()
{
    string trash;
    
    cout << endl << "Press enter to continue" << endl;
    
    getline(cin, trash);
}