#ifndef _GABRIELAKEYBOARD_H_
#define _GABRIELAKEYBOARD_H_

#include "commons.hpp"
#include "GabrielaReceiver.hpp"
#include "GabrielaKey.hpp"
#include "GabrielaCpu.hpp"

#include <string.h>

class GabrielaKeyboard: public GabrielaReceiver{
private:
    int keyCount;
    GabrielaKey *keys[24];
    GabrielaCpu *cpu;
    bool build();

public:
    GabrielaKeyboard();
    ~GabrielaKeyboard();

    void setCpu(GabrielaCpu *cpu);

    void addKey(GabrielaKey *key);

    void receiveDigit(Digit d);
    void receiveOperation(Operation op);
    void receiveControl(Control ctrl);

    friend class GabrielaCalculator;
};

#endif