/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the implementation file for the abstract Spaces class.
*****************************************************************************************/

#include "spaces.hpp"
#include "backpack.hpp"

/*****************************************************************************************
** Function: Constructor (Space)
** Description: Initialises some values for a Space.
** Parameters: A pointer-to-Backpack (for inventory management within the Space).
** Pre-Conditions: Nothing.
** Post-Conditions: The Space is initialised (derived Space, because Space is abstract).
*****************************************************************************************/
Space::Space(Backpack *proton)
{
    game_win = false; //Explicitly note that the game isn't over yet.
    special_toggle = false; //This will be used by most spaces.
    
    timer_start = false;//This will only be used by one space.
    backpack = proton;  //Each space has access to the backpack.
    
    north = NULL;
    south = NULL;
    east = NULL;
    west = NULL;
}

/*****************************************************************************************
** Function: set_north
** Description: Sets one of the Space's four pointers. 
** Parameters: A pointer-to-Space.
** Pre-Conditions: Nothing.
** Post-Conditions: The pointer is set.
*****************************************************************************************/
void Space::set_north(Space* location)
{
    north = location;
}

/*****************************************************************************************
** Function: set_south
** Description: Sets one of the Space's four pointers. 
** Parameters: A pointer-to-Space.
** Pre-Conditions: Nothing.
** Post-Conditions: The pointer is set.
*****************************************************************************************/
void Space::set_south(Space* location)
{
    south = location;
}

/*****************************************************************************************
** Function: set_east
** Description: Sets one of the Space's four pointers. 
** Parameters: A pointer-to-Space.
** Pre-Conditions: Nothing.
** Post-Conditions: The pointer is set.
*****************************************************************************************/
void Space::set_east(Space* location)
{
    east = location;
}

/*****************************************************************************************
** Function: set_west
** Description: Sets one of the Space's four pointers. 
** Parameters: A pointer-to-Space.
** Pre-Conditions: Nothing.
** Post-Conditions: The pointer is set.
*****************************************************************************************/
void Space::set_west(Space* location)
{
    west = location;
}

/*****************************************************************************************
** Function: set_backpack
** Description: Sets the Backpack pointer. 
** Parameters: A pointer-to-Backpack.
** Pre-Conditions: Nothing.
** Post-Conditions: The pointer is set.
*****************************************************************************************/
void Space::set_backpack(Backpack* pack)
{
    backpack = pack;
}

/*****************************************************************************************
** Function: success
** Description: Returns the game-winning boolean flag.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: The flag is returned.
*****************************************************************************************/
bool Space::success()
{
    return game_win;
}

/*****************************************************************************************
** Function: timerStart
** Description: Returns the timer-started boolean flag.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: The flag is returned.
*****************************************************************************************/
bool Space::timerStart()
{
    return timer_start;
}