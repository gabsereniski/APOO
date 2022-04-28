#ifndef _GABRIELACALCULATOR_H_
#define _GABRIELACALCULATOR_H_

#include "GabrielaKeyboard.hpp"
#include "GabrielaDisplay.hpp"
#include "GabrielaCpu.hpp"

class GabrielaCalculator{
    GabrielaDisplay *display;
    GabrielaKeyboard *keyboard;
    GabrielaCpu *cpu;
    char buffer;
public:
    GabrielaCalculator();
    ~GabrielaCalculator();
    void run();
};

#endif