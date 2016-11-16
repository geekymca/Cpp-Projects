/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the implementation file for a Bathroom class. (A type of Space.)
*****************************************************************************************/

#include "bathroom.hpp"
#include "spaces.hpp"
#include "backpack.hpp"

#include "main.hpp"

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::getline;

/*****************************************************************************************
** Function: Constructor (Bathroom)
** Description: Prepares the Bathroom.
** Parameters: A pointer-to-Backpack.
** Pre-Conditions: Nothing.
** Post-Conditions: The Bathroom is ready.
*****************************************************************************************/
Bathroom::Bathroom(Backpack *proton) : Space(proton) {}
//I'm creating this constructor, but only passing a value back to the base class constructor.

/*****************************************************************************************
** Function: special (Bathroom)
** Description: Sing the Ghostbusters theme.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: The theme is sung, and the Bathroom may be affected.
*****************************************************************************************/
void Bathroom::special()
{
    if (!special_toggle)
    {
        cout << "You are a man of fine taste, so you enjoy singing in the bathroom."
             << endl
             << "Though your mind is a bit foggy, you clear your throat, and start to sing."
             << endl
             << "Of course, when you're singing in the bathroom, only one song will do."
             << endl
             << "Your favorite song, of course."
             << endl << endl
             << "    'If there's something strange, in the neighborhood'"
             << endl << endl
             << "You hear a faint voice from outside. 'Shut up, your voice sucks!'"
             << endl << endl
             << "    'Who you gonna call-'"
             << endl << endl
             << "Your tiny bathroom window shatters and you feel something slap you in the face."
             << endl;
             
        pausePrompt();
             
        cout << "You look down to see a pair of black electrical gloves."
             << endl
             << "They look kind of useful, so you pick them up and put them on."
             << endl << endl
             << "That's it, they will complete your Bill Murray costume perfectly!"
             << endl
             << "You throw open the bathroom door, grab your proton pack from your room,"
             << endl
             << "and rush back to look in the mirror."
             << endl << endl
             << "You see nothing. Well, you see a floating proton pack and pair of gloves."
             << endl
             << "You also see your naked body on the ground."
             << endl
             << "Something appears to be wrong here."
             << endl;
             
        special_toggle = true;
    }
    else
    {
        cout << "   'Busting makes me feel good!'"
             << endl << endl
             << "An irate voice sounds out from outside."
             << endl
             << "    'You're lucky I only have one pair of gloves!'"
             << endl;
    }
}

/*****************************************************************************************
** Function: description (Bathroom)
** Description: Describes the Bathroom.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: The Bathroom is described.
*****************************************************************************************/
void Bathroom::description()
{
    cout << "You are in your tiny bathroom, connected to your bedroom by a door."
         << endl << endl;
    if (!special_toggle)
    {
        cout << "Though you feel fine now after your tumble, something seems amiss."
             << endl
             << "You stand there naked in your bathroom. Pondering life."
             << endl;
    }
    else
    {
        cout << "Your tiny bathroom window is shattered."
             << endl
             << "Looking in your mirror, you see nothing looking back."
             << endl
             << "Besides some floating Ghostbusters gear."
             << endl << endl
             << "You also see your unconscious self laying on the floor next to the bathtub."
             << endl
             << "Luckily, bits of glass didn't get stuck in your body. It's all naked and clean."
             << endl << endl
             << "You better do something about that."
             << endl
             << "Not the clean part, the unconcious part. Maybe the naked part too."
             << endl;
    }
}

/*****************************************************************************************
** Function: option (Bathroom)
** Description: Presents user choices for the Bathroom.
** Parameters: Nothing. (Takes user input.)
** Pre-Conditions: Nothing.
** Post-Conditions: The user's action is performed, and the pointer for the next area
**                  is returned if applicable.
*****************************************************************************************/
Space* Bathroom::option()
{
    string user_input;
    Space *return_space = this;
    
    cout << "What do you want to do?" << endl;
    if (!special_toggle)
    {
        
        cout << "a) sing" << endl
             << "b) leave the bathroom" << endl
             << "Choice: ";
        
        getline(cin, user_input);
        
        cout << endl;
         
        if (user_input == "a")
        {
            special();
        }
        else if (user_input == "b")
        {
            cout << "For some reason, you are unable to get a good grip on the doorknob."
                 << endl
                 << "You must have taken a harder fall than you expected."
                 << endl;
        }
        else
        {
            cout << "Sorry, I didn't understand that choice." << endl
                 << "Enter only the lowercase letter of your choice." << endl;
        }
    }
    else
    {
        cout << "a) sing" << endl
             << "b) enter your bedroom" << endl
             << "c) head to your roommate's room" << endl
             << "d) head to your kitchen" << endl
             << "e) head to your living room" << endl
             << "i) check your inventory" << endl
             << "h) get a hint" << endl
             << "Choice: ";
             
        getline(cin, user_input);
        
        cout << endl;
        
        if (user_input == "a")
        {
            special();
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
            cout << "Use doggy biscuits by a doggy door. Your roommate has doggy biscuits." << endl;
        }
        else
        {
             cout << "Sorry, I didn't understand that choice." << endl
                  << "Enter only the lowercase letter of your choice." << endl;
        }
    }
    
    return return_space;
}