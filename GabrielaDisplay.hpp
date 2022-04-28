#ifndef _GABRIELADISPLAY_H_
#define _GABRIELADISPLAY_H_

#include "commons.hpp"

#include <iostream>
#include <string.h>

class GabrielaDisplay{
    char disp[19];
    void print();
    void shift();
public:
    GabrielaDisplay();
    ~GabrielaDisplay();
    void add(Digit d);
    void addDecimalSeparator();
    void setSignal();
    void setError();
    void clear();
};

#endif