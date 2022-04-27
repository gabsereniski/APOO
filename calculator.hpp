#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include "keyboard.hpp"
#include "display.hpp"
#include "cpu.hpp"

class Calculator{
    Display *display;
    Keyboard *keyboard;
    Cpu *cpu;
    char buffer;
public:
    Calculator();
    //~Calculator();
    void run();
    //friend class Keyboard;
};

#endif