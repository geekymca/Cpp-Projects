/*****************************************************************************************
** Program Filename: buster
**                   
** Author: Albert Chang
** Date: 2016-3-9
** Description: BusterGhost, a game about being a ghost (and meeting a buster).
** Input: The player has to enter single letter/digit choices in menus.
** Output: No return or file output, but stuff is printed to console.
**
**         This is the header file for a Backpack class.
*****************************************************************************************/

#ifndef BACKPACK_HPP
#define BACKPACK_HPP

#include <string>
#include <vector>
using std::string;
using std::vector;

#define MAX_CAPACITY 2

class Backpack
{
    private:
        vector<string> objects;
        unsigned int max_capacity;
    public:
        Backpack();
        bool full();
        void fullMessage();
        
        bool contains(string);
        
        void addItem(string);
        void removeItem(string);
        void trashItem(); //Prompts to discard item.
        
        void printContents();
};

#endif