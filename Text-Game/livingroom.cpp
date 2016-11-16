/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the implementation file for a Livingroom class. (A type of Space.)
*****************************************************************************************/

#include "livingroom.hpp"
#include "spaces.hpp"

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::getline;

/*****************************************************************************************
** Function: Constructor (Livingroom)
** Description: Prepares the Livingroom.
** Parameters: A pointer-to-Backpack.
** Pre-Conditions: Nothing.
** Post-Conditions: The Livingroom is ready. (Has a remote, and some other flags too.)
*****************************************************************************************/
Livingroom::Livingroom(Backpack *proton, Space *extra_pointer) : Space(proton)
{
    remote = true;
    dog_present = false;
    tried_door = false;
    
    outside = extra_pointer;
}

/*****************************************************************************************
** Function: special (Livingroom)
** Description: Manipulates the TV.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: The TV may be turned on if the player has a remote (altering the
**                  Livingroom's state), and the TV may be entered by the ghost-user.
*****************************************************************************************/
void Livingroom::special()
{
    if (special_toggle)
    {        
        cout << "You approach the TV. You get too close, and accidentally possess the TV."
             << endl << endl
             << "Being a ghost is weird."
             << endl << endl
             << "You find yourself in a dark place within the TV. Cold, damp, and echo-y."
             << endl
             << "Being a weightless ghost, you climb upwards, then find yourself exiting a well."
             << endl
             << "There's a long black wig on your face obscuring your vision."
             << endl
             << "You stumble around until you find yourself back in the living room."
             << endl
             << "You take the wig off and throw it to the floor. It poofs away, magically."
             << endl << endl
             << "Being a ghost is weird."
             << endl;
    }
    else if (backpack->contains("remote") || backpack->contains("sockmote") )
    {
        cout << "You turn the TV on. There's a static image of a well in it. Like for water."
             << endl
             << "Your roommate has strange tastes in entertainment."
             << endl;
        
        special_toggle = true;
    }
    else
    {
        cout << "The TV is off, and you don't have the remote on hand."
             << endl
             << "(No, you do not know how to work the TV's buttons along the edges.)"
             << endl;
    }
}

/*****************************************************************************************
** Function: description (Livingroom)
** Description: Describes the Livingroom.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: The Livingroom is described.
*****************************************************************************************/
void Livingroom::description()
{
    cout << "You are in your living room."
         << endl << endl
         << "There's a door leading outside, along with a doggy door that has been unused"
         << endl
         << "for years. It's kind of jammed. There's a small couch and a small TV as well." 
         << endl << endl
         << "This is your house's entertainment center. But it's not very entertaining."
         << endl
         << "Your roommate watches movies here late at night, but you don't use the TV much."
         << endl << endl;
    if (!special_toggle)
    {
        cout << "Your roommate doesn't leave the TV on when he's not using it."
             << endl
             << "So the TV is off right now."
             << endl;
    }
    else
    {
        cout << "You turned the TV on, and left it on. Way to drive up the electricity bill."
             << endl
             << "It's just a static, flickering image of a well though. The quality isn't great."
             << endl
             << "Kind of looks like your roommate was watching a VHS transfer."
             << endl;
    }
    
    if (remote)
    {
        cout << endl
             << "The remote control for the TV is wedged between some couch cushions."
             << endl
             << "You could pull it out if you want to watch TV."
             << endl;
    }
    
    if (dog_present)
    {
        cout << endl
             << "An unfamiliar dog is enjoying a biscuit you dropped earlier."
             << endl
             << "The doggy door seems to be jammed open now rather than jammed shut."
             << endl;
    }
}

/*****************************************************************************************
** Function: option (Livingroom)
** Description: Presents user choices for the Livingroom.
** Parameters: Nothing. (Takes user input.)
** Pre-Conditions: Nothing.
** Post-Conditions: The user's action is performed, and the pointer for the next area
**                  is returned if applicable.
*****************************************************************************************/
Space* Livingroom::option()
{
    string user_input;
    Space *return_space = this;
    
    cout << "What do you want to do?" << endl
         << "a) play with the TV" << endl
         << "b) head to your bathroom" << endl
         << "c) head to your bedroom" << endl
         << "d) head to your roommate's room" << endl
         << "e) head to the kitchen" << endl
         << "f) open the door and find help" << endl;
    if (backpack->contains("doggy biscuits") )
    {
        if (!dog_present)
        {
            cout << "g) drop a doggy biscuit by the doggy door" << endl;
        }
        else
        {
            cout << "g) drop another doggy biscuit" << endl;
        }
    }
    if (remote)
    {
        cout << "r) pull out the remote" << endl ;
    }
    if (dog_present)
    {
        cout << "x) exit via the doggy door" << endl;
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
    else if (user_input == "r" && remote)
    {
        if (backpack->contains("sock") )
        {
            cout << "You shove the remote into your sock to make the almighty sockmote!"
                 << endl
                 << "You're feeling pretty good about your ingenuity."
                 << endl;
                 
            backpack->removeItem("sock");
            backpack->addItem("sockmote");
            remote = false;
        }
        else if (backpack->full() )
        {
            backpack->fullMessage();
        }
        else
        {
            cout << "You grab the remote and stash it into your proton pack."
                 << endl
                 << "You could use the entertainment given how your day has been."
                 << endl;
            
            backpack->addItem("remote");
            remote = false;
        }
    }
    else if (user_input == "f")
    {
        if (!tried_door)
        {
            cout << "You try to unlock the door, but fail miserably. You suddenly realise"
                 << endl
                 << "that ghosts live by vampire rules when it comes to entering and exiting houses."
                 << endl
                 << "You can't unlock the door as a spirit. Only a living person can. That sucks."
                 << endl;
            tried_door = true;
        }
        else
        {
            cout << "It doesn't matter how hard you try. Supernatural ghost rules, man."
                 << endl
                 << "The door still doesn't unlock."
                 << endl;
        }
    }
    else if (user_input == "g" && backpack->contains("doggy biscuits") )
    {
        if (!dog_present)
        {
            cout << "Shortly after you drop the biscuit, a dog rushes in through the doggy door."
                 << endl
                 << "The dog's hunger for a biscuit seems to be stronger than the stuck door."
                 << endl
                 << "The dog slobbers all over the biscuit as you watch on."
                 << endl;
                 
            dog_present = true;
        }
        else
        {
            cout << "You drop another biscuit for that unfamiliar dog."
                 << endl
                 << "He happily slobbers all over the new biscuit as well."
                 << endl << endl
                 << "Hey, don't forget about your naked body in the bathroom."
                 << endl
                 << "You can't just keep playing with this unfamiliar dog."
                 << endl;
        }
    }
    else if (user_input == "x" && dog_present)
    {
        cout << "You drop your gloves and proton pack,"
             << endl
             << "then shimmy your spirit form through the doggy door."
             << endl;
        
        return_space = outside;
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
        if (!dog_present)
        {
            cout << "There's a doggy door here. You should drop a biscuit." << endl;
        }
        else
        {
            cout << "The doggy door is open. You can probably fit through it." << endl;
        }
    }
    else
    {
        cout << "Sorry, I didn't understand that choice." << endl
             << "Enter only the lowercase letter of your choice." << endl;
    }
    
    return return_space;
}