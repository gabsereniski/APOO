#include "GabrielaCalculator.hpp"
#include <iostream>

#define OPERATION_SHIFT 10
#define CONTROL_SHIFT 16

GabrielaCalculator::GabrielaCalculator()
{
    cpu = nullptr;
    keyboard = nullptr;
    display = nullptr;
}

GabrielaCalculator::~GabrielaCalculator()
{
    delete cpu;
    delete keyboard;
    delete display;
}

void GabrielaCalculator::setDisplay(Display* display)
{
    this->display = display;
}
void GabrielaCalculator::setCpu(Cpu* cpu)
{
    this->cpu = cpu;
}
void GabrielaCalculator::setKeyboard(Keyboard* keyboard)
{
    this->keyboard = keyboard;
}

void GabrielaCalculator::run()
{
    display->clear();
    
    while(std::cin >> buffer)
    {
        buffer = tolower(buffer);

        if(buffer == 'q') return;

        switch(buffer)
        {
            case '0': keyboard->keys[ZERO]->press(); break;
            case '1': keyboard->keys[ONE]->press(); break;
            case '2': keyboard->keys[TWO]->press(); break;
            case '3': keyboard->keys[THREE]->press(); break;
            case '4': keyboard->keys[FOUR]->press(); break;
            case '5': keyboard->keys[FIVE]->press(); break;
            case '6': keyboard->keys[SIX]->press(); break;
            case '7': keyboard->keys[SEVEN]->press(); break;
            case '8': keyboard->keys[EIGHT]->press(); break;
            case '9': keyboard->keys[NINE]->press(); break;

            case '+': keyboard->keys[ADDITION + OPERATION_SHIFT]->press(); break;
            case '-': keyboard->keys[SUBTRACTION + OPERATION_SHIFT]->press(); break;
            case '/': keyboard->keys[DIVISION + OPERATION_SHIFT]->press(); break;
            case '*': keyboard->keys[MULTIPLICATION + OPERATION_SHIFT]->press(); break;
            case 'r': keyboard->keys[SQUARE_ROOT + OPERATION_SHIFT]->press(); break;
            case '%': keyboard->keys[PERCENTAGE + OPERATION_SHIFT]->press(); break;
            
            case 'c': keyboard->keys[CLEAR + CONTROL_SHIFT]->press(); break;
            case 'a': keyboard->keys[RESET + CONTROL_SHIFT]->press(); break;
            case '.': keyboard->keys[DECIMAL_SEPARATOR + CONTROL_SHIFT]->press(); break;
            case 'm': keyboard->keys[MEMORY_READ + CONTROL_SHIFT]->press(); break;
            case '#': keyboard->keys[MEMORY_CLEAR + CONTROL_SHIFT]->press(); break;
            case '~': keyboard->keys[MEMORY_SUBTRACTION + CONTROL_SHIFT]->press(); break;
            case '^': keyboard->keys[MEMORY_ADDITION + CONTROL_SHIFT]->press(); break;
            case '=': keyboard->keys[EQUAL + CONTROL_SHIFT]->press(); break;

            default: break;
        }
    }
}