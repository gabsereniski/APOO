#ifndef _GABRIELACPU_H_
#define _GABRIELACPU_H_

#include "commons.hpp"
#include "GabrielaReceiver.hpp"
#include "GabrielaKeyboard.hpp"
#include "GabrielaDisplay.hpp"

#include <iostream>
#include <cmath>
#include <sstream>

class GabrielaCpu: public GabrielaReceiver{
    GabrielaDisplay *display;
    Operation op;
    
    std::string regs[2];
    float ops[2];
    int regsNod[2];
    bool regHasDecSep[2];
    Signal regsSign[2];

    float mem;

    char lastReceived;
    int curReg;
    bool overflow;
    
    void clearRegister(int r);

    int countDigits(int r);
    float isFloat(float n);

    float ALU(float op1, float op2, Operation op);
    void compute();

    void updateOp(Operation op);
    void updateDisplay(int r);

    void reset();

public:
    GabrielaCpu();
    ~GabrielaCpu();
    
    void setDisplay(GabrielaDisplay* display);
    void receiveDigit(Digit d);
    void receiveOperation(Operation op);
    void receiveControl(Control ctrl);
    void receiveSignal(Signal s);
};

#endif