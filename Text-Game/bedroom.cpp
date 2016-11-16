/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the implementation file for a Bedroom class. (A type of Space.)
*****************************************************************************************/

#include "bedroom.hpp"
#include "spaces.hpp"

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::getline;

/*****************************************************************************************
** Function: Constructor (Bedroom)
** Description: Prepares the Bedroom.
** Parameters: A pointer-to-Backpack.
** Pre-Conditions: Nothing.
** Post-Conditions: The Bedroom is ready.
*****************************************************************************************/
Bedroom::Bedroom(Backpack *proton) : Space(proton) {}

/*****************************************************************************************
** Function: special (Bedroom)
** Description: Toggle the lights.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: The lights are switched from on to off or off to on.
*****************************************************************************************/
void Bedroom::special()
{
    if (!special_toggle)
    {
        cout << "You turn the lights off. Now you're standing in the dark. Why did you do that?"
             << endl;
    }
    else
    {
        cout << "You turn the lights back on. You wonder why you had an urge to turn them off."
             << endl
             << "It's almost as if a third party is controlling your ghostly actions. Almost."
             << endl
             << "Better not think about this too much."
             << endl;
    }
    
    special_toggle = !special_toggle;
}

/*****************************************************************************************
** Function: description (Bedroom)
** Description: Describes the Bedroom.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: The Bedroom is described.
*****************************************************************************************/
void Bedroom::description()
{
    cout << "You are in your own bedroom. Your body is still in the connecting bathroom."
         << endl << endl;
    if (special_toggle)
    {
        cout << "Your room is all dark. So dark, in fact, that you feel you cannot do anything."
             << endl
             << "You should probably turn the lights on. You know where the switch is."
             << endl;
    }
    else
    {
        cout << "There isn't much to do in your bedroom. You're a boring guy,"
             << endl
             << "and all you have decorating your bedroom are piles of unwashed clothes."
             << endl << endl
             << "You could shove some dirty laundry into your proton pack maybe."
             << endl
             << "You have a strong feeling that won't help you though."
             << endl;
    }
}

/*****************************************************************************************
** Function: option (Bedroom)
** Description: Presents user choices for the Bedroom.
** Parameters: Nothing. (Takes user input.)
** Pre-Conditions: Nothing.
** Post-Conditions: The user's action is performed, and the pointer for the next area
**                  is returned if applicable.
*****************************************************************************************/
Space* Bedroom::option()
{
    string user_input;
    Space *return_space = this;
    
    cout << "What do you want to do?" << endl
         << "a) play with the light switch" << endl
         << "b) enter the bathroom" << endl
         << "c) head to your roommate's room" << endl
         << "d) head to the kitchen" << endl
         << "e) head to the living room" << endl
         << "f) grab a dirty sock" << endl
         << "i) check your inventory" << endl
         << "h) get a hint" << endl
         << "Choice: ";
    
    getline(cin, user_input);
    
    cout << endl;
     
    if (user_input == "a")
    {
        special();
    }
    else if (special_toggle)
    {
        cout << "It's dark. You stumble around and accomplish nothing." << endl;
        
        if (user_input == "i")
        {
            cout << endl 
                 << "You're lucky you didn't accidentally destroy your proton pack."
                 << endl;
        }
        if (user_input == "h")
        {
            cout << endl << "(It's so dark you can't even read the hint.)" << endl;
        }
    }
    else if (user_input == "f")
    {
        if (backpack->contains("sock") || backpack->contains("sockmote") )
        {
            cout << "You already have one dirty sock in your proton pack."
                 << endl
                 << "You don't need another stinking it up."
                 << endl;
        }
        else if (backpack->contains("remote") )
        {
            cout << "You combine the sock with your TV remote to make the almighty sockmote!"
                 << endl
                 << "You're feeling pretty good about your ingenuity."
                 << endl;
            
            backpack->removeItem("remote");
            backpack->addItem("sockmote");
        }
        else if (backpack->full() )
        {
            backpack->fullMessage();
        }
        else
        {
            cout << "You grab a dirty sock and stash it in your proton pack."
                 << endl
                 << "You think to yourself, 'this could come in handy'."
                 << endl
                 << "(It won't. You are silly for thinking that.)"
                 << endl;
            
            backpack->addItem("sock");
        }
    }
    else if (user_input == "b")
    {
        return_space = north;
    }
    else if (user_input == "c")
    {
        return_space = south;
    }
    else if (user_input == "d")
    {
        return_space = east;
    }
    else if (user_input == "e")
    {
        return_space = west;
    }
    else if (user_input == "i")
    {
        backpack->printContents();
    }
    else if (user_input == "h")
    {
        cout << "You need doggy biscuits for a doggy door." << endl
             << "You don't need socks." << endl
             << "(Unless you need to keep a remote snug.)" << endl;
    }
    else
    {
        cout << "Sorry, I didn't understand that choice." << endl
             << "Enter only the lowercase letter of your choice." << endl;
    }
    
    return return_space;
}