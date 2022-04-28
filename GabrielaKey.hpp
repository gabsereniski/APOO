#ifndef _GABRIELAKEY_H_
#define _GABRIELAKEY_H_

#include "commons.hpp"
#include "GabrielaReceiver.hpp"

class GabrielaKey{
protected:
    GabrielaReceiver *receiver;
public:
    ~GabrielaKey(){};
    virtual void press() = 0;
    void setReceiver(GabrielaReceiver *receiver);
};

class GabrielaKeyDigit: public GabrielaKey{
    Digit digit;
public:
    GabrielaKeyDigit(Digit digit);
    ~GabrielaKeyDigit(){};
    void press();
};

class GabrielaKeyOperation: public GabrielaKey{
    Operation operation;
public:
    GabrielaKeyOperation(Operation operation);
    ~GabrielaKeyOperation(){};
    void press();
};

class GabrielaKeyControl: public GabrielaKey{
    Control control;
public:
    GabrielaKeyControl(Control control);
    ~GabrielaKeyControl(){};
    void press();
};

#endif