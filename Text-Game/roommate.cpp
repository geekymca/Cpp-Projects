/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the implementation file for a Roommate class. (A type of Space.)
*****************************************************************************************/

#include "roommate.hpp"
#include "spaces.hpp"

#include "main.hpp"

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::getline;

/*****************************************************************************************
** Function: Constructor (Roommate)
** Description: Prepares the Roommate [room].
** Parameters: A pointer-to-Backpack.
** Pre-Conditions: Nothing.
** Post-Conditions: The Roommate [room] is ready.
*****************************************************************************************/
Roommate::Roommate(Backpack *proton) : Space(proton)
{
    fish_count = FISH_COUNT;
    special_toggle = true; //You may wonder why it's set to true by default.
}// I think the room is the most "special" at the start, and loses "special"-ness after.

/*****************************************************************************************
** Function: special (Roommate)
** Description: Play with some fish.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: Fish may be scared into unconsciousness.
*****************************************************************************************/
void Roommate::special()
{
    if (fish_count > 0)
    {
        cout << "You decide to play with your roommate's fish."
             << endl
             << "You go up and tap the glass, getting the attention of a single fish."
             << endl
             << "The fish looks shocked, as if it's seen a ghost, and faints."
             << endl
             << "You sigh as the fish drifts down to the bottom of the bowl."
             << endl;
             
        fish_count--;
    }
    else
    {
        cout << "All of the fish are unconscious, at the bottom of the bowl."
             << endl
             << "It's as if they've seen a ghost. All " << FISH_COUNT << " of them."
             << endl
             << "There's no point to tapping the glass now."
             << endl;
    }
}

/*****************************************************************************************
** Function: description (Roommate)
** Description: Describes the Roommate [room].
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: The Roommate [room] is described.
*****************************************************************************************/
void Roommate::description()
{
    cout << "You are in your roommate's room."
         << endl << endl;
    if (special_toggle)
    {
        cout << "Your roommate is sitting right there. You decide to say hi."
             << endl << endl
             << "    'Yo'"
             << endl
             << "    'Who's there?'"
             << endl
             << "    'Hey it's just me, something weird happened and-'"
             << endl
             << "    'A GHOST!'"
             << endl << endl
             << "Your roommate screams and runs out of his room, then out of the house."
             << endl
             << "Screaming the whole way. He made sure to lock the door behind him though."
             << endl
             << "A good habit. But your body is still in the restroom, unseen by him."
             << endl
             << "It seems you won't be getting help from your roommate today."
             << endl;
             
        pausePrompt();
             
        cout << "All things considered, you wonder why he was frightened by your voice,"
             << endl
             << "but not the floating proton pack and pair of gloves."
             << endl << endl;
             
             timer_start = true;
    }
    else
    {
        cout << "Your roommate's room is unoccupied. You don't count, because you're a spirit."
             << endl
             << "With him gone, you could snoop through his diary. But you're a man of honor."
             << endl
             << "So you won't do that. "
             << endl << endl
             << "Not yet anyway."
             << endl << endl;
    }
    
    cout << "On your roommate's desk, you see his fidge bowl."
         << endl;
    if (special_toggle)
    {
        cout << "He always said fish with a weird accent, like 'fidge'. He's a funny guy." 
             << endl << endl;
    }
    cout << "In the bowl you see " << fish_count << " fish swimming around."
         << endl;
         
    if (fish_count == 0)
    {
        cout << "That's right, they're all unconscious." << endl;
    }
         
        cout << endl
             << "Next to it, a bag of your roommate's favorite doggy biscuits sits unfinished."
             << endl
             << "You guys don't have a dog anymore."
             << endl;
    
    if (special_toggle)
    {
        special_toggle = false;
    }
    //Toggle this at the very end, to indicate the first visit is over.
}

/*****************************************************************************************
** Function: option (Roommate)
** Description: Presents user choices for the Roommate [room].
** Parameters: Nothing. (Takes user input.)
** Pre-Conditions: Nothing.
** Post-Conditions: The user's action is performed, and the pointer for the next area
**                  is returned if applicable.
*****************************************************************************************/
Space* Roommate::option()
{
    string user_input;
    Space *return_space = this;
    
    cout << "What do you want to do?" << endl
         << "a) play with fish" << endl    
         << "b) head to the bathroom" << endl
         << "c) head to your bedroom" << endl
         << "d) head to the kitchen" << endl
         << "e) head to the living room" << endl
         << "f) grab the doggy biscuits" << endl
         << "i) check your inventory" << endl
         << "h) get a hint" << endl
         << "Choice: ";
    
    getline(cin, user_input);
    
    cout << endl;
     
    if (user_input == "a")
    {
        special();
    }
    else if (user_input == "f")
    {
        if (backpack->contains("doggy biscuits") )
        {
            cout << "You already have enough doggy biscuits, man. Don't be greedy." << endl;
        }
        else if (backpack->full() )
        {
            backpack->fullMessage();
        }
        else
        {
            cout << "You grab a handful of doggy biscuits and shove them into your proton pack."
                 << endl
                 << "Maybe you'll find a dog later."
                 << endl;
            
            backpack->addItem("doggy biscuits");
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
        cout << "Those doggy biscuits will come in handy later. By a doggy door." << endl;
    }
    else
    {
        cout << "Sorry, I didn't understand that choice." << endl
             << "Enter only the lowercase letter of your choice." << endl;
    }
    
    return return_space;
}