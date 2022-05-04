#include "GabrielaCalculator.hpp"
#include "GabrielaKeyboard.hpp"
#include "GabrielaDisplay.hpp"
#include "GabrielaCpu.hpp"

#include <iostream>

bool buildKeyboard(Keyboard *kb)
{
    for(int i = 0; i < 10; i++)
    {
        KeyDigit *d = new KeyDigit((Digit)i);
        if(!d) return false;
        kb->addKey(d);
    }

    for(int i = 0; i < 6; i++)
    {
        KeyOperation *op = new KeyOperation((Operation)i);
        if(!op) return false;
        kb->addKey(op);
    }

    for(int i = 0; i < 8; i++)
    {
        KeyControl *ctrl = new KeyControl((Control)i);
        if(!ctrl) return false;
        kb->addKey(ctrl);
    }

    return true;
}

bool buildCalculator(Calculator *calc, Cpu *cpu, Display *display, Keyboard *keyboard)
{
    if(!calc || !cpu || !display || !keyboard) return false;

    calc->setCpu(cpu);
    calc->setDisplay(display);
    calc->setKeyboard(keyboard);

    keyboard->setCpu(cpu);
    cpu->setDisplay(display);

    return true;
}

int main()
{
    GabrielaCalculator *calc = new GabrielaCalculator;
    
    Cpu *cpu = new GabrielaCpu;
    Display *display = new GabrielaDisplay;
    Keyboard *keyboard = new GabrielaKeyboard;

    if(!buildKeyboard(keyboard))
    {
        puts("Erro ao construir teclado");
        exit(0);
    }

    if(!buildCalculator(calc, cpu, display, keyboard))
    {
        puts("Erro ao construir calculadora");
        exit(0);
    }

    calc->run();

    return 0;
}
