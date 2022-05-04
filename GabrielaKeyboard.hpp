#ifndef _GABRIELAKEYBOARD_H_
#define _GABRIELAKEYBOARD_H_

#include "calculator.h"

class GabrielaKeyboard: public Keyboard{
private:
    int keyCount;

public:
    GabrielaKeyboard();
    ~GabrielaKeyboard();

    void addKey(Key *key);

    void receiveDigit(Digit d);
    void receiveOperation(Operation op);
    void receiveControl(Control ctrl);
};

#endif