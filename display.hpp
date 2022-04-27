#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "commons.hpp"

#include <iostream>
#include <string.h>

class Display{
    char disp[19];
    void print();
    void shift();
public:
    Display();
    ~Display();
    void add(Digit d);
    void addDecimalSeparator();
    void setSignal();
    void setError();
    void clear();
};

#endif