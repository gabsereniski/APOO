#ifndef _GABRIELARECEIVER_H_
#define _GABRIELARECEIVER_H_

#include "commons.hpp"

class GabrielaReceiver{
public:
    virtual void receiveDigit(Digit d) = 0;
    virtual void receiveOperation(Operation op) = 0;
    virtual void receiveControl(Control ctrl) = 0;
};

#endif