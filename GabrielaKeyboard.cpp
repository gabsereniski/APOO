#include "GabrielaKeyboard.hpp"
#include <iostream>

GabrielaKeyboard::GabrielaKeyboard()
{
    cpu = nullptr;
    keyCount = 0;
}

GabrielaKeyboard::~GabrielaKeyboard()
{
    for(int i = 0; i < keyCount; i++)
        delete keys[i];
    cpu = nullptr;
    keyCount = 0;
}

//PUBLIC FUNCTIONS---------------------------------------------//

void GabrielaKeyboard::addKey(Key *key)
{
    if(keyCount < 24)
    {
        keys[keyCount] = key;
        keys[keyCount]->setReceiver(this);
        keyCount++;
    }
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