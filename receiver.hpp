#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#include "commons.hpp"

class Receiver{
public:
    virtual void receiveDigit(Digit d) = 0;
    virtual void receiveOperation(Operation op) = 0;
    virtual void receiveControl(Control ctrl) = 0;
    //virtual void receiveSignal(Signal s) = 0;
};

#endif