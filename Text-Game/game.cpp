/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the implementation file for the Game class. Just a wrapper of sorts.
*****************************************************************************************/

#include "game.hpp"
#include "main.hpp"
#include "backpack.hpp"

#include "spaces.hpp"
#include "bathroom.hpp"
#include "bedroom.hpp"
#include "roommate.hpp"
#include "kitchen.hpp"
#include "livingroom.hpp"

#include "outside.hpp"

#include <iostream>
using std::cout;
using std::endl;

/*****************************************************************************************
** Function: Constructor (Game)
** Description: Creates all the Spaces for the game. The Backpack too.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: The Game is ready to play. Who's ready for BusterGhost?
*****************************************************************************************/
Game::Game()
{
    proton = new Backpack;
    
    outside = new Outside();
    
    bathroom = new Bathroom(proton);
    bedroom = new Bedroom(proton);
    roommate = new Roommate(proton);
    kitchen = new Kitchen(proton);
    living = new Livingroom(proton, outside);

    
    timer = TIME_LIMIT;
    timer_started = false;
    game_won = false;
}

/*****************************************************************************************
** Function: Destructor (Game)
** Description: Deletes all the Spaces for the game. The Backpack too.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: The Game is ready to quit. Who's done with BusterGhost?
*****************************************************************************************/
Game::~Game()
{
    delete proton;
    
    delete outside;
    
    delete bathroom;
    delete bedroom;
    delete roommate;
    delete kitchen;
    delete living;
}

/*****************************************************************************************
** Function: play
** Description: Plays the game.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: The Game will be played.
*****************************************************************************************/
void Game::play()
{
    Space *current;
  
    linkRooms(*bathroom, *bedroom, *roommate, *kitchen, *living);
    
    outside->set_north(living); //Special case here.
    
    current = bathroom;
    
    system("clear");
    
    titleScreen();
    pausePrompt();
    
    system("clear");
    
    introduction();
    pausePrompt();
    
    do
    {
        system("clear");
        
        current->description();
        pausePrompt();
        
        current = current->option();
        pausePrompt();
        system("clear");
        
        if (!timer_started && current->timerStart() )
        {
            timer_started = true;
        }
        
        if (timer_started)
        {
            timer--;
            
            if (timer == FIRST_WARNING)
            {
                firstWarning();
                pausePrompt();
            }
            else if (timer == SECOND_WARNING)
            {
                secondWarning();
                pausePrompt();
            }
            else if (timer == THIRD_WARNING)
            {
                thirdWarning();
                pausePrompt();
            }
            else if (timer == LAST_WARNING)
            {
                finalWarning();
                pausePrompt();
            }
            if (current == outside && timer <= 0)
            {
                timer = 1; //Prevent the game from ending while outside.
            }
        }
        
        if (current->success() )
        {
            game_won = true;
            break; //This simplifies the loop logic a little bit.
        }          // I think it's safe to break so close to the end of the loop.
    } while (timer > 0);
    
    if (game_won)
    {
        ending(); //The default ending is the good ending.
    }
    else
    {
        badEnding();
    }   //The bad ending isn't all that bad. You get to meet your hero, Bill Murray.
    
    pausePrompt();
    
    system("clear");
    
    closing();
    pausePrompt();
}

/*****************************************************************************************
** Function: linkRooms
** Description: Links five spaces in a specific order.
** Parameters: Five Space objects. (Derived ones, because Space is abstract.)
** Pre-Conditions: The Space objects are valid.
** Post-Conditions: The Space objects are linked via their NESW pointers.
*****************************************************************************************/
void Game::linkRooms(Space &first, Space &second, Space &third, Space&fourth, Space &fifth)
{
    first.set_north(&second);
    first.set_south(&third);
    first.set_east(&fourth);
    first.set_west(&fifth);
    
    second.set_north(&first);
    second.set_south(&third);
    second.set_east(&fourth);
    second.set_west(&fifth);
    
    third.set_north(&first);
    third.set_south(&second);
    third.set_east(&fourth);
    third.set_west(&fifth);
    
    fourth.set_north(&first);
    fourth.set_south(&second);
    fourth.set_east(&third);
    fourth.set_west(&fifth);
    
    fifth.set_north(&first);
    fifth.set_south(&second);
    fifth.set_east(&third);
    fifth.set_west(&fourth);
}

/*****************************************************************************************
** Function: titleScreen
** Description: Prints a few things.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: A few things are printed.
*****************************************************************************************/
void Game::titleScreen()
{
    cout << "Welcome to BusterGhost, a game that's not about ghostbusting."
         << endl
         << "This title screen is just here to say hi and tell you some extra information."
         << endl << endl
         << "For example, your bag in the game can only hold two items."
         << endl
         << "But you only need one item, so that second spot can hold whatever you want."
         << endl << endl
         << "Also, all menu choices are single characters, and case matters."
         << endl
         << "Uppercase characters are never used."
         << endl
         << "Invalid inputs won't do anything, but they still pass 'time' in the game."
         << endl
         << "Think of it as hesitation leaving you with less time to work with."
         << endl << endl
         << "Well, that's all I had to say. Press enter to start the story."
         << endl;
}

/*****************************************************************************************
** Function: introduction
** Description: Prints a few things.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: A few things are printed.
*****************************************************************************************/
void Game::introduction()
{
    cout << "You are a guy enjoying a shower. In your own home."
         << endl
         << "There's nothing weird going on. Just a naked guy cleaning himself."
         << endl << endl
         << "Suddenly, perhaps because you are distracted by my narration,"
         << endl
         << "you slip and knock your head against the side of the tub."
         << endl << endl
         << "You are dazed for a moment, but manage to stand up."
         << endl << endl
         << "The game starts here."
         << endl;
}

/*****************************************************************************************
** Function: ending
** Description: Prints a few things.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: A few things are printed.
*****************************************************************************************/
void Game::ending()
{
    cout << "Inside, he notices the huge mess you made and investigates your home."
         << endl << endl;
         
    if (timer <= 1)
    {
        cout << "He also notices Bill Murray wandering around, and gives him the all clear."
             << endl
             << "Bill Murray is content that the residents are safe, and leaves your home."
             << endl << endl;
    }
    
    cout << "Finding your naked body in the shower, he calls 911 and waits with your body."
         << endl << endl
         << "After the paramedics arrive and get to your body, you feel your consciousness"
         << endl
         << "fading. Feeling disoriented now, even as a spirit, you hope this means you're"
         << endl
         << "being pulled back into your body again."
         << endl << endl
         << "This is a good thing, right?"
         << endl;
}

/*****************************************************************************************
** Function: badEnding
** Description: Prints a few things.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: A few things are printed.
*****************************************************************************************/
void Game::badEnding()
{
    cout << "You are interrupted by the sound of somebody kicking your front door open."
         << endl << endl
         << "    'Yeah, yeah, yeah, yeah!'"
         << endl << endl
         << "Suddenly, Bill Murray busts into the room. You are starstruck."
         << endl << endl
         << "Before you can say anything, he throws down a trap and zaps you."
         << endl
         << "That is to say, he is pointing his neutrona wand at your invisible face."
         << endl << endl
         << "Unlike yours, his proton pack isn't a replica."
         << endl << endl
         << "You feel your ghost energy draining away, and you are sucked into the trap."
         << endl << endl
         << "Bill Murray picks up the trap and leaves."
         << endl << endl
         << "It seems that unlike your roommate,"
         << endl
         << "Bill Murray ain't afraid of no ghosts."
         << endl;
}

/*****************************************************************************************
** Function: closing
** Description: Prints a few things.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: A few things are printed.
*****************************************************************************************/
void Game::closing()
{
    cout << "The game is over. Hope you enjoyed it."
         << endl
         << "We don't know what happened to your spirit after you finished,"
         << endl
         << "but you, as a physical person, are still fine, and that's what matters."
         << endl
         << "Some stories don't have conclusive endings. This is one of them."
         << endl;
         
    if (!game_won)
    {
        cout << endl
             << "Given the events that occurred at the end though,"
             << endl
             << "it's unlikely your spirit will reunite with your body."
             << endl << endl
             << "But don't take it personally. Bill Murray was just doing his job."
             << endl;
    }
}

/*****************************************************************************************
** Function: firstWarning
** Description: Prints a few things.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: A few things are printed.
*****************************************************************************************/
void Game::firstWarning()
{
    cout << "You hear some faint music in the distance."
         << endl << endl
         << "Familiar music."
         << endl << endl
         << "You resist the urge to start tapping your ethereal toe."
         << endl;
}

/*****************************************************************************************
** Function: secondWarning
** Description: Prints a few things.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: A few things are printed.
*****************************************************************************************/
void Game::secondWarning()
{
    cout << "That music is getting clearer now."
         << endl << endl
         << "    'If there's something weird, and it don't look good'"
         << endl << endl
         << "You recognise that music. It's the 80s classic 'Ghostbusters' theme."
         << endl
         << "The one you were just singing. Sounds like it's coming from some speakers."
         << endl;
}

/*****************************************************************************************
** Function: thirdWarning
** Description: Prints a few things.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: A few things are printed.
*****************************************************************************************/
void Game::thirdWarning()
{
    cout << "You stop to focus on that music you've been hearing again."
         << endl << endl
         << "    'If you've had a dose of a freaky ghost, baby'"
         << endl << endl
         << "It's getting pretty loud now. Somebody outside has good taste."
         << endl;
}

/*****************************************************************************************
** Function: finalWarning
** Description: Prints a few things.
** Parameters: Nothing.
** Pre-Conditions: Nothing.
** Post-Conditions: A few things are printed.
*****************************************************************************************/
void Game::finalWarning()
{
    cout << "The music is absurdly loud now."
         << endl << endl
         << "    'When it comes through your door, unless you just want some more'"
         << endl << endl
         << "It sounds like it's just outside your front door."
         << endl
         << "You're not near the front door, but you have a bad feeling about this."
         << endl;
}