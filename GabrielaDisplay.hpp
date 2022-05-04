#ifndef _GABRIELADISPLAY_H_
#define _GABRIELADISPLAY_H_

#include "calculator.h"
class GabrielaDisplay: public Display{
    char disp[19];
    void print();
    void shift();

public:
    GabrielaDisplay();
    ~GabrielaDisplay();

    void add(Digit d);
    void setDecimalSeparator();
    void setSignal(Signal);
    void setError();
    void clear();
};

#endif