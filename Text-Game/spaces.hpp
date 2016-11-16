/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the header file for the abstract Spaces class.
*****************************************************************************************/

#ifndef SPACES_HPP
#define SPACES_HPP

#include "backpack.hpp"

class Space
{
    protected:
        bool special_toggle;
        bool game_win;
        bool timer_start;
        Space *north;
        Space *south;
        Space *east;
        Space *west;
        Backpack *backpack;
    public:
        Space(Backpack* = NULL);
        virtual ~Space() {};
        
        void set_backpack(Backpack*); //Just in case. We don't actually use this.
        
        void set_north(Space*); //No "get" functions, because that's handled in option().
        void set_south(Space*); //This just allows world-linking after creating each Space.
        void set_east(Space*);
        void set_west(Space*);       
        
        virtual void special() = 0;
        virtual void description() = 0;
        virtual Space *option() = 0;
        bool success(); //I'm going to have the winning room indicate the game-win state.
        bool timerStart(); //This I'm not sure I need. But I have an idea.
};

#endif