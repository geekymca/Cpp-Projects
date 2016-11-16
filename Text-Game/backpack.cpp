/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the implementation file for a Backpack class.
*****************************************************************************************/

#include "backpack.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm> // For remove
#include <cstdlib>   // For atoi
using std::string;

using std::atoi;

using std::cout;
using std::endl;
using std::cin;
using std::getline;

using std::remove;

/*****************************************************************************************
** Function: Constructor (Backpack)
** Description: Initialises the backpack's maximum capacity.
** Parameters: Nothing. (The maximum capacity is a preprocessor constant.)
** Pre-Conditions: Nothing.
** Post-Conditions: The Backpack is initialised.
*****************************************************************************************/
Backpack::Backpack()
{
    max_capacity = MAX_CAPACITY;
}

/*****************************************************************************************
** Function: full
** Description: Returns true or false depending on whether the Backpack is full.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: True (if full) or false (if not full) is returned.
*****************************************************************************************/
bool Backpack::full()
{
    return (objects.size() >= max_capacity);
}

/*****************************************************************************************
** Function: fullMessage
** Description: Prints a short warning message for a full pack. Called by Spaces.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: The message is printed.
*****************************************************************************************/
void Backpack::fullMessage()
{
    cout << "Your proton pack is full (yes, with only two items)." << endl
         << "It wasn't meant to be used this way. It's just a replica prop." << endl
         << "You should 'check your inventory' and trash something." << endl;
}

/*****************************************************************************************
** Function: contains
** Description: Returns true or false for whether the Backpack has a specific string.
** Parameters: A string.
** Pre-Conditions: Nothing.
** Post-Conditions: True (if present) or false (if not present) is returned.
*****************************************************************************************/
bool Backpack::contains(string something)
{
    for (unsigned int index = 0; index < objects.size(); index++)
    {
        if (objects[index] == something)
        {
            return true;
        }
    }
    return false;
}

/*****************************************************************************************
** Function: addItem
** Description: Adds a string to the Backpack.
** Parameters: A string.
** Pre-Conditions: Nothing.
** Post-Conditions: If not full, the string is added to the Backpack.
**                  (This check is never actually encountered in the program.)
*****************************************************************************************/
void Backpack::addItem(string something)
{
    if (!full() )
    {
        objects.push_back(something);
    }
}

/*****************************************************************************************
** Function: removeItem
** Description: Removes a string from the Backpack.
** Parameters: A string.
** Pre-Conditions: Nothing.
** Post-Conditions: The specified string is removed from the Backpack.
*****************************************************************************************/
void Backpack::removeItem(string something)
{
    remove(objects.begin(), objects.end(), something);
    objects.pop_back();
}

/*****************************************************************************************
** Function: trashItem
** Description: Prompts user to select an item to remove from the Backpack.
** Parameters: Nothing. (Prompts for user input.)
** Pre-Conditions: Nothing. (If Backpack isn't full, prompts don't make sense.)
** Post-Conditions: The specified string is removed from the Backpack, or nothing is done.
*****************************************************************************************/
void Backpack::trashItem() // Like removeItem, but with prompts.
{
    int user_input;
    string temp_string;

    cout << "What do you want to trash?"
         << endl;
    for (unsigned int index = 0; index < objects.size(); index++)
    {
        cout << index + 1 << ") " << objects[index] << endl;
    }
    cout << "(Enter an invalid choice to skip the trashing.)" << endl
         << "Choice (enter only an integer): ";
    getline(cin, temp_string);
    
    user_input = atoi(temp_string.c_str() ) - 1; //-1 because indices start at 0.
    
    if (user_input < 0 || user_input >= MAX_CAPACITY)
    {
        cout << "I didn't understand that choice. Nothing will be trashed." << endl;
    }
    // else if (objects[user_input] == "doggy biscuits")
    // {
        // cout << "You can't trash the doggy biscuits. Dogs gotta eat." << endl;
    // }
    //I originally had doggy biscuits be untrashable. But now, I just have them as
    // a regrabbable item (infinite supply, like the socks).
    else
    {
        cout << "Trashing " << objects[user_input] << "." << endl
             << "It will be lost forever to the ghostly ether." << endl;
        removeItem(objects[user_input]);
    }
}
    
/*****************************************************************************************
** Function: printContents
** Description: Prints out all the contents of the backpack.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: The contents of the Backpack are printed.
*****************************************************************************************/
void Backpack::printContents()
{
    string trash;
    
    cout << "Your proton pack contains ";
    
    if (objects.size() == 0)
    {
        cout << "nothing.";
    }
    else
    {
        cout << endl;
        
        for (unsigned int index = 0; index < objects.size(); index++)
        {
            cout << objects[index] << "    ";
        }
        cout << endl
             << "Would you like to trash something?" << endl
             << "Enter 'y' or 'n': ";
             
        getline(cin, trash);
        
        if (trash == "y")
        {
            trashItem();
        }
        else if (trash == "n")
        {
            cout << "Okay, your stuff is safe.";
        }
        else
        {
            cout << "Sorry, I didn't understand that. I'll assume you want to keep all your stuff.";
        }
    }
    cout << endl;
}