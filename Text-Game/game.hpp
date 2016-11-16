/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the header file for the Game class. Just a wrapper of sorts.
*****************************************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

#include "backpack.hpp"
#include "spaces.hpp"

#define TIME_LIMIT 20
#define FIRST_WARNING 15
#define SECOND_WARNING 10
#define THIRD_WARNING 5
#define LAST_WARNING 1
//These are pretty flexible, but LAST_WARNING should stay at 1 as an "oh crap" warning.

class Game
{
    private:
        Space *bathroom;
        Space *bedroom;
        Space *roommate;
        Space *kitchen;
        Space *living;
        
        Space *outside;
        
        Backpack *proton;
        
        int timer;
        bool timer_started;
        bool game_won;
        
    public:
        Game();
        ~Game();
        
        void play();
        
        void linkRooms(Space &first, Space &second, Space &third, Space&fourth, Space &fifth);
        
        void titleScreen();
        void introduction();
        
        void ending();
        void badEnding();
        
        void closing();
        
        void firstWarning();
        void secondWarning();
        void thirdWarning();
        void finalWarning();
};

#endif