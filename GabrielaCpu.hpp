#ifndef _GABRIELACPU_H_
#define _GABRIELACPU_H_

#include "calculator.h"

#include <iostream>
class GabrielaCpu: public Cpu{
    Operation op;
    
    std::string reg[2];
    float fReg[2];
    int numOfDigits[2];
    bool hasDecSep[2];
    Signal sign[2];

    float mem;

    char lastReceived;
    int cur;
    bool overflow;
    
    void clearRegister(int r);
    void reset();
    int countDigits(int r);
    float isFloat(float n);
    void conversion(int r);

    void updateOp(Operation op);

    float ALU(float op1, float op2, Operation op);
    void compute();

    void sendDigits(int r);

public:
    GabrielaCpu();
    ~GabrielaCpu();
    
    void setDisplay(Display* display);
    void receiveDigit(Digit d);
    void receiveOperation(Operation op);
    void receiveControl(Control ctrl);
};

#endif