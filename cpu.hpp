#ifndef _CPU_H_
#define _CPU_H_

#include "commons.hpp"
#include "receiver.hpp"
#include "keyboard.hpp"
#include "display.hpp"

#include <iostream>
#include <cmath>
#include <sstream>

class Cpu: public Receiver{
    Display *display;
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
    Cpu();
    ~Cpu();
    
    void setDisplay(Display* display);

    void receiveDigit(Digit d);
    void receiveOperation(Operation op);
    void receiveControl(Control ctrl);
    void receiveSignal(Signal s);
};

#endif