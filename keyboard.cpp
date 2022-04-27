#include "receiver.hpp"
#include "keyboard.hpp"

Keyboard::Keyboard()
{
    cpu = nullptr;

    

    if(!build())
    {
        for(int i = 0; i < keyCount; i++)
            delete keys[i];
        keyCount = 0;
    }
}

Keyboard::~Keyboard()
{
    for(int i = 0; i < keyCount; i++)
        delete keys[i];
    cpu = nullptr;
    keyCount = 0;
}

void Keyboard::setCpu(Cpu *cpu)
{
    this->cpu = cpu;
}

void Keyboard::addKey(Key *key)
{
    if(keyCount < 24)
    {
        keys[keyCount] = key;
        keys[keyCount]->setReceiver(this);
        keyCount++;
    }
}
/*
void Keyboard::print()
{

    printf("| ");
    for(int j = 0; j < 5; j++) printf(" ___");   
    printf("  |\n");
    int k = 0;
    for(int i = 0; i < 5; i++)
    {
        printf("| ");
        for(int j = 0; j < 5; j++) printf("|%s", label[k++]);   
        printf("| |\n| ");
        k -= 5;
        for(int j = 0; j < 5; j++) printf("|%s", sub[k++]);    
        printf("| |\n| "); 
        for(int j = 0; j < 5; j++) printf("|___"); 
        printf("| |\n");
    }

    printf("|_______________________|\n\n>>");
           
}*/

bool Keyboard::build()
{
    keyCount = 0;

    for(int i = 0; i < 24; i++)
    {
        KeyDigit *d;
        KeyOperation *op;
        KeyControl *ctrl;

        switch(i)
        {
            case  0: ctrl = new KeyControl(MEMORY_READ);        addKey(ctrl);   break;
            case  1: ctrl = new KeyControl(MEMORY_CLEAR);       addKey(ctrl);   break;
            case  2: ctrl = new KeyControl(MEMORY_SUBTRACTION); addKey(ctrl);   break;
            case  3: ctrl = new KeyControl(MEMORY_ADDITION);    addKey(ctrl);   break;
            case  4:    d = new KeyDigit(SEVEN);                addKey(d);      break;
            case  5:    d = new KeyDigit(EIGHT);                addKey(d);      break;
            case  6:    d = new KeyDigit(NINE);                 addKey(d);      break;
            case  7:   op = new KeyOperation(DIVISION);         addKey(op);     break;
            case  8: ctrl = new KeyControl(RESET);              addKey(ctrl);   break;
            case  9:    d = new KeyDigit(FOUR);                 addKey(d);      break;
            case 10:    d = new KeyDigit(FIVE);                 addKey(d);      break;
            case 11:    d = new KeyDigit(SIX);                  addKey(d);      break;
            case 12:   op = new KeyOperation(MULTIPLICATION);   addKey(op);     break;
            case 13: ctrl = new KeyControl(CLEAR);              addKey(ctrl);   break;
            case 14:    d = new KeyDigit(ONE);                  addKey(d);      break;
            case 15:    d = new KeyDigit(TWO);                  addKey(d);      break;
            case 16:    d = new KeyDigit(THREE);                addKey(d);      break;
            case 17:   op = new KeyOperation(SUBTRACTION);      addKey(op);     break;
            case 18:   op = new KeyOperation(SQUARE_ROOT);      addKey(op);     break;
            case 19: ctrl = new KeyControl(DECIMAL_SEPARATOR);  addKey(ctrl);   break;
            case 20:    d = new KeyDigit(ZERO);                 addKey(d);      break;
            case 21:    ctrl = new KeyControl(EQUAL);           addKey(ctrl);   break;
            case 22:   op = new KeyOperation(ADDITION);         addKey(op);     break;
            case 23:   op = new KeyOperation(PERCENTAGE);       addKey(op);     break;
        }
    }

    return true;
}

void Keyboard::receiveDigit(Digit d)
{
    if(cpu) cpu->receiveDigit(d);
}

void Keyboard::receiveOperation(Operation op)
{
    if(cpu) cpu->receiveOperation(op);
}

void Keyboard::receiveControl(Control ctrl)
{
    if(cpu) cpu->receiveControl(ctrl);
}