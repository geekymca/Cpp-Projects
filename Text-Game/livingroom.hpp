/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the header file for a Livingroom class. (A type of Space.)
*****************************************************************************************/

#ifndef LIVINGROOM_HPP
#define LIVINGROOM_HPP

#include "spaces.hpp"
#include "backpack.hpp"

class Livingroom:public Space
{
    private:
        bool remote;
        bool dog_present;
        bool tried_door;
        
        Space *outside;
    public:
        Livingroom(Backpack*, Space*);
        ~Livingroom() {};
        
        void special();
        void description();
        Space *option();
};

#endif