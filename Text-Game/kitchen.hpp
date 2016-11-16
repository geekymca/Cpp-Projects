/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the header file for a Kitchen class. (A type of Space.)
*****************************************************************************************/

#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include "spaces.hpp"

class Kitchen:public Space
{
    private:
        bool popcorn;
    public:
        Kitchen(Backpack*);
        ~Kitchen() {};
        
        void special();
        void description();
        Space *option();
};

#endif