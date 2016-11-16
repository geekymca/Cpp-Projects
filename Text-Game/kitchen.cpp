/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the implementation file for a Kitchen class. (A type of Space.)
*****************************************************************************************/

#include "kitchen.hpp"
#include "spaces.hpp"

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::getline;

/*****************************************************************************************
** Function: Constructor (Kitchen)
** Description: Prepares the Kitchen.
** Parameters: A pointer-to-Backpack.
** Pre-Conditions: Nothing.
** Post-Conditions: The Kitchen is ready. (It also has a single pack of popcorn.)
*****************************************************************************************/
Kitchen::Kitchen(Backpack *proton) : Space(proton)
{
    popcorn = true;
}

/*****************************************************************************************
** Function: special (Kitchen)
** Description: Burn stuff with the stove.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: If the user chooses to burn things, they may be removed from the
**                  user's Backpack. The user gets nothing out of it.
*****************************************************************************************/
void Kitchen::special()
{
    if (!special_toggle)
    {
        cout << "You turn the stove on. The knob breaks off from your clumsy ghost hands."
             << endl
             << "Looks like you just created a fire hazard."
             << endl;
        
        special_toggle = true;
    }
    else
    {
        string user_input;
        
        cout << "You decide to use the stove since you're still paying for the gas bill."
             << endl << endl
             << "What do you want to cook?"
             << endl;
        
        if (backpack->contains("doggy biscuits") )
        {
            cout << "d) a single doggy biscuit" << endl;
        }
        if (backpack->contains("popcorn") )
        {
            cout << "p) the microwave popcorn pack" << endl;
        }
        if (backpack->contains("sock") || backpack->contains("sockmote") )
        {
            cout << "s) your dirty sock" << endl;
        }
        cout << "x) nothing, you changed your mind about cooking" << endl
             << "Choice: ";
             
        getline(cin, user_input);
        
        cout << endl;
        
        if (user_input == "d" && backpack->contains("doggy biscuits") )
        {
            cout << "You put a doggy biscuit directly on the open flame."
                 << endl << endl
                 << "Doggy biscuits are precooked. That was a waste of time."
                 << endl
                 << "The biscuit goes up in flames, but you still have many more."
                 << endl;
        }
        else if (user_input == "p" && backpack->contains("popcorn") )
        {
            cout << "You put the microwave popcorn pack directly on the open flame."
                 << endl << endl
                 << "That's not how you cook microwave popcorn."
                 << endl
                 << "The pack goes up in flames."
                 << endl;
            
            backpack->removeItem("popcorn");
        }
        else if (user_input == "s" && (backpack->contains("sock") || backpack->contains("sockmote") ) )
        {
            cout << "You put your sock directly on the open flame."
                 << endl << endl
                 << "What are you thinking? Why are you cooking your sock?"
                 << endl
                 << "The sock goes up in flames."
                 << endl;
                 
            if (backpack->contains("sockmote") )
            {
                cout << endl
                     << "You seem to have forgotten about your TV remote tucked inside the sock."
                     << endl
                     << "The plastic warps, and you have a disgusting smelling mess on your stove."
                     << endl
                     << "Way to go. You have more than just a fire hazard now."
                     << endl;
                     
                backpack->removeItem("sockmote");
            }
            else
            {
                backpack->removeItem("sock");
            }
        }
        else if (user_input == "x")
        {
            cout << "That's a wise choice. You don't have time to cook as a wandering spirit."
                 << endl;
        }
        else
        {
            cout << "Sorry, I didn't understand that choice." << endl
                 << "You step away from the stove anyway." << endl;
        }
    }
}

/*****************************************************************************************
** Function: description (Kitchen)
** Description: Describes the Kitchen.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: The Kitchen is described.
*****************************************************************************************/
void Kitchen::description()
{
    cout << "You are in your kitchen."
         << endl << endl
         << "Some houses have a back door in the kitchen where dogs might enter."
         << endl
         << "Like a tiny, dog-sized door. Not yours though."
         << endl << endl;
    if (!special_toggle)
    {
        cout << "While your roommate sometimes leaves food out, he's careful about fire hazards."
             << endl
             << "The stove and oven are off, and all food is away from their proximity."
             << endl
             << "Your microwave is broken though. Last week, your roommate tried to microwave"
             << endl
             << "a fork for some reason. That didn't end well."
             << endl;
    }
    else
    {
        cout << "There's an open flame going at your stove. You should avoid touching that."
             << endl
             << "You can't get burned in your current state, but you have to keep your"
             << endl
             << "proton pack safe. That thing's expensive."
             << endl << endl
             << "Starting the fire didn't magically un-break your microwave though."
             << endl;
    }
    
    if (popcorn)
    {
        cout << endl
             << "An unpopped pack of microwave popcorn sits on the counter. Feeling hungry?"
             << endl;
    }
}

/*****************************************************************************************
** Function: option (Kitchen)
** Description: Presents user choices for the Kitchen.
** Parameters: Nothing. (Takes user input.)
** Pre-Conditions: Nothing.
** Post-Conditions: The user's action is performed, and the pointer for the next area
**                  is returned if applicable.
*****************************************************************************************/
Space* Kitchen::option()
{
    string user_input;
    Space *return_space = this;
    
    cout << "What do you want to do?" << endl
         << "a) play with the stove" << endl
         << "b) head to your bathroom" << endl
         << "c) head to your bedroom" << endl
         << "d) head to your roommate's room" << endl
         << "e) head to the living room" << endl;
    if (popcorn)
    {
         cout << "f) grab the popcorn pack" << endl;
    }         
    cout << "i) check your inventory" << endl
         << "h) get a hint" << endl
         << "Choice: ";
    
    getline(cin, user_input);
    
    cout << endl;
     
    if (user_input == "a")
    {
        special();
    }
    else if (user_input == "f" && popcorn)
    {
        if (backpack->full() )
        {
            backpack->fullMessage();
        }
        else
        {
            cout << "You grab the microwave popcorn and stash it in your proton pack."
                 << endl
                 << "You think to yourself, 'this could come in hungry'."
                 << endl
                 << "Then you think, 'handy. I meant handy.'"
                 << endl
                 << "(You cannot eat as a ghost. But you don't know this.)"
                 << endl;
            
            backpack->addItem("popcorn");
            popcorn = false;
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
        cout << "If you have doggy biscuits, you should find a doggy door." << endl;
    }
    else
    {
        cout << "Sorry, I didn't understand that choice." << endl
             << "Enter only the lowercase letter of your choice." << endl;
    }
    
    return return_space;
}