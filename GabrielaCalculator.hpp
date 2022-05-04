#ifndef _GABRIELACALCULATOR_H_
#define _GABRIELACALCULATOR_H_

#include "calculator.h"

class GabrielaCalculator: public Calculator{
    Display *display;
    Keyboard *keyboard;
    Cpu *cpu;
    char buffer;

public:
    GabrielaCalculator();
    ~GabrielaCalculator();

    void setDisplay(Display* display);
    void setCpu(Cpu* cpu);
    void setKeyboard(Keyboard* keyboard);
    
    void run();
};

#endif