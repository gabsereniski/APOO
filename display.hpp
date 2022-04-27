#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "commons.hpp"

#include <iostream>
#include <string.h>

class Display{
    char disp[19];

    char label[25][5] = {   "OFF", "MR ", "MC ", "M- ", "M+ ",
                            "7  ", "8  ", "9  ", "/  ", "AC ",
                            "4  ", "5  ", "6  ", "*  ", "C  ",
                            "1  ", "2  ", "3  ", "-  ", "SR ",
                            ".  ", "0  ", "=  ", "+  ", "%  "   };
    char sub[25][5] =   {   "Q  ", "M  ", "#  ", "~  ", "^  ",
                            "   ", "   ", "   ", "   ", "A  ",
                            "   ", "   ", "   ", "   ", "   ",
                            "   ", "   ", "   ", "   ", "r  ",
                            "   ", "   ", "   ", "   ", "   "  };

    void print();
    void shift();
public:
    Display();
    //~Display();
    void add(Digit d);
    void addDecimalSeparator();
    void setSignal();
    void setError();
    void clear();
};

#endif