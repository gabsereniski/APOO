#ifndef _KEY_H_
#define _KEY_H_

#include "commons.hpp"
#include "receiver.hpp"

class Key{
protected:
    Receiver *receiver;
public:
    ~Key(){};
    virtual void press() = 0;
    void setReceiver(Receiver *receiver);
};

class KeyDigit: public Key{
    Digit digit;
public:
    KeyDigit(Digit digit);
    ~KeyDigit(){};
    void press();
};

class KeyOperation: public Key{
    Operation operation;
public:
    KeyOperation(Operation operation);
    ~KeyOperation(){};
    void press();
};

class KeyControl: public Key{
    Control control;
public:
    KeyControl(Control control);
    ~KeyControl(){};
    void press();
};

#endif