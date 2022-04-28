#include "GabrielaReceiver.hpp"
#include "GabrielaKeyboard.hpp"

GabrielaKeyboard::GabrielaKeyboard()
{
    cpu = nullptr;

    if(!build())
    {
        for(int i = 0; i < keyCount; i++)
            delete keys[i];
        keyCount = 0;
    }
}

GabrielaKeyboard::~GabrielaKeyboard()
{
    for(int i = 0; i < keyCount; i++)
        delete keys[i];
    cpu = nullptr;
    keyCount = 0;
}

void GabrielaKeyboard::setCpu(GabrielaCpu *cpu)
{
    this->cpu = cpu;
}

void GabrielaKeyboard::addKey(GabrielaKey *key)
{
    if(keyCount < 24)
    {
        keys[keyCount] = key;
        keys[keyCount]->setReceiver(this);
        keyCount++;
    }
}

bool GabrielaKeyboard::build()
{
    keyCount = 0;

    for(int i = 0; i < 24; i++)
    {
        GabrielaKeyDigit *d;
        GabrielaKeyOperation *op;
        GabrielaKeyControl *ctrl;

        switch(i)
        {
            case  0: ctrl = new GabrielaKeyControl(MEMORY_READ);        addKey(ctrl); break;
            case  1: ctrl = new GabrielaKeyControl(MEMORY_CLEAR);       addKey(ctrl); break;
            case  2: ctrl = new GabrielaKeyControl(MEMORY_SUBTRACTION); addKey(ctrl); break;
            case  3: ctrl = new GabrielaKeyControl(MEMORY_ADDITION);    addKey(ctrl); break;
            case  4:    d = new GabrielaKeyDigit(SEVEN);                addKey(d);    break;
            case  5:    d = new GabrielaKeyDigit(EIGHT);                addKey(d);    break;
            case  6:    d = new GabrielaKeyDigit(NINE);                 addKey(d);    break;
            case  7:   op = new GabrielaKeyOperation(DIVISION);         addKey(op);   break;
            case  8: ctrl = new GabrielaKeyControl(RESET);              addKey(ctrl); break;
            case  9:    d = new GabrielaKeyDigit(FOUR);                 addKey(d);    break;
            case 10:    d = new GabrielaKeyDigit(FIVE);                 addKey(d);    break;
            case 11:    d = new GabrielaKeyDigit(SIX);                  addKey(d);    break;
            case 12:   op = new GabrielaKeyOperation(MULTIPLICATION);   addKey(op);   break;
            case 13: ctrl = new GabrielaKeyControl(CLEAR);              addKey(ctrl); break;
            case 14:    d = new GabrielaKeyDigit(ONE);                  addKey(d);    break;
            case 15:    d = new GabrielaKeyDigit(TWO);                  addKey(d);    break;
            case 16:    d = new GabrielaKeyDigit(THREE);                addKey(d);    break;
            case 17:   op = new GabrielaKeyOperation(SUBTRACTION);      addKey(op);   break;
            case 18:   op = new GabrielaKeyOperation(SQUARE_ROOT);      addKey(op);   break;
            case 19: ctrl = new GabrielaKeyControl(DECIMAL_SEPARATOR);  addKey(ctrl); break;
            case 20:    d = new GabrielaKeyDigit(ZERO);                 addKey(d);    break;
            case 21: ctrl = new GabrielaKeyControl(EQUAL);              addKey(ctrl); break;
            case 22:   op = new GabrielaKeyOperation(ADDITION);         addKey(op);   break;
            case 23:   op = new GabrielaKeyOperation(PERCENTAGE);       addKey(op);   break;
        }
    }

    return true;
}

void GabrielaKeyboard::receiveDigit(Digit d)
{
    if(cpu) cpu->receiveDigit(d);
}

void GabrielaKeyboard::receiveOperation(Operation op)
{
    if(cpu) cpu->receiveOperation(op);
}

void GabrielaKeyboard::receiveControl(Control ctrl)
{
    if(cpu) cpu->receiveControl(ctrl);
}

void GabrielaKeyboard::receiveSignal(Signal s){}