/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the header file for an Outside class. (A type of Space.)
*****************************************************************************************/

#ifndef OUTSIDE_HPP
#define OUTSIDE_HPP

#include "spaces.hpp"
#include "backpack.hpp"

class Outside:public Space
{
    public:
        Outside();
        ~Outside() {};
        
        void special();
        void description();
        Space *option();
};

#endif