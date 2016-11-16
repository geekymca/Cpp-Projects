/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the header file for a Roommate class. (A type of Space.)
*****************************************************************************************/

#ifndef ROOMMATE_HPP
#define ROOMMATE_HPP

#include "spaces.hpp"
#include "backpack.hpp"

#define FISH_COUNT 3

class Roommate:public Space
{
    private:
        int fish_count;
    public:
        Roommate(Backpack*);
        ~Roommate() {};
        
        void special();
        void description();
        Space *option();
};

#endif