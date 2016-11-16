/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the implementation file for an Outside class. (A type of Space.)
*****************************************************************************************/

#include "outside.hpp"
#include "spaces.hpp"

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::getline;

/*****************************************************************************************
** Function: Constructor (Outside)
** Description: Prepares the Outside.
** Parameters: A pointer-to-Backpack.
** Pre-Conditions: Nothing.
** Post-Conditions: The Outside is ready. (Has a remote, and some other flags too.)
*****************************************************************************************/
Outside::Outside()
{
    srand(time(0) ); //Seed rand, because we're using it here.
}

/*****************************************************************************************
** Function: special (Outside)
** Description: Bushdiving.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: The player's bush-status is toggled.
*****************************************************************************************/
void Outside::special()
{
    if (!special_toggle)
    {        
        cout << "You panic and dive towards a bush."
             << endl
             << "You are now possessing a bush."
             << endl;
    }
    else
    {
        cout << "You calm down and exit the bush. Think clearly now."
             << endl
             << "You have a chance to save your naked body."
             << endl;
    }
    special_toggle = !special_toggle;
}

/*****************************************************************************************
** Function: description (Outside)
** Description: Describes the backyard.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: The backyard is described.
*****************************************************************************************/
void Outside::description()
{
    cout << "You are outside your house in your backyard."
         << endl << endl
         << "There's a door leading inside, but you can't use it as a ghost."
         << endl
         << "You couldn't use it as a non-ghost either. It's locked."
         << endl << endl
         << "There's a doggy door that you can use, but you probably shouldn't head back."
         << endl << endl
         << "You see a man that looks worried. Presumably his dog just ran into your house."
         << endl << endl;
         
    if (rand() % 2 == 0)
    {
        cout << "    'Buster, where are you hiding?'"
             << endl << endl;
    }
    else
    {
        cout << "    'Come on, boy! Where did you go?'"
             << endl << endl;
    }
    
    cout << "Confirming your suspicions, the man is indeed searching for his dog."
         << endl
         << "He does not seem to notice the open doggy door leading inside."
         << endl << endl
         << "You feel for this guy. You miss your dog too. It's been years."
         << endl
         << "You also wonder why this guy was walking his dog in your backyard."
         << endl << endl
         << "But this is no time to get sentimental. Your naked body is in danger."
         << endl;
    
    if (special_toggle)
    {
        cout << endl
             << "You are hiding inside a bush. Kind of hard to do stuff there."
             << endl;
    }
}

/*****************************************************************************************
** Function: option (Outside)
** Description: Presents user choices for the backyard.
** Parameters: Nothing. (Takes user input.)
** Pre-Conditions: Nothing.
** Post-Conditions: The user's action is performed, and the pointer for the living room
**                  is returned if applicable. (The user shouldn't go back inside.)
*****************************************************************************************/
Space* Outside::option()
{
    string user_input;
    Space *return_space = this;
    
    cout << "What do you want to do?" << endl;
    if (!special_toggle)
    {
        cout << "a) panic" << endl;
    }
    else
    {
        cout << "a) calm down and exit the bush" << endl;
    }
    cout << "b) bark" << endl;
    cout << "c) head back inside the house" << endl
         << "d) check your inventory" << endl
         << "e) get a hint" << endl
         << "Choice: ";
    
    getline(cin, user_input);
    
    cout << endl;
     
    if (user_input == "a")
    {
        special();
    }
    else if (user_input == "b")
    {
        cout << "You do your best dog impression and bark towards the man."
             << endl << endl
             << "He hears it, but doesn't see you, so he busts down the door to find his dog."
             << endl 
             << "(Keep in mind this is your back door. You're going to have to pay for that.)"
             << endl;
             
             game_win = true;
    }
    else if (user_input == "c")
    {
        cout << "You decide to head back into the house. You're probably making a big mistake."
             << endl << endl
             << "You shimmy on back into the house through the doggy door."
             << endl << endl
             << "Back inside, you suit up again with the electrical gloves and proton pack."
             << endl;
             
        return_space = north;
    }
    else if (user_input == "d")
    {
        cout << "Remember, you left your proton pack inside the house."
             << endl
             << "You don't need it now, but you could go back in to look at it."
             << endl;
    }
    else if (user_input == "e")
    {
        cout << "Try barking. You have nothing to lose." << endl
             << "Besides your dignity, of course." << endl;
    }
    else
    {
        cout << "Sorry, I didn't understand that choice." << endl
             << "Enter only the lowercase letter of your choice." << endl;
    }
    
    return return_space;
}