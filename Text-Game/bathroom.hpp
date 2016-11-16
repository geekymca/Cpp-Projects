/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the header file for a Bathroom class. (A type of Space.)
*****************************************************************************************/

#ifndef BATHROOM_HPP
#define BATHROOM_HPP

#include "spaces.hpp"
#include "backpack.hpp"

class Bathroom:public Space
{
    public:
        Bathroom(Backpack*);
        ~Bathroom() {};
        
        void special();
        void description();
        Space *option();
};

#endif