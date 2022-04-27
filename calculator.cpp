#include "calculator.hpp"

Calculator::Calculator()
{
    cpu = new Cpu;
    keyboard = new Keyboard;
    display = new Display;

    keyboard->setCpu(cpu);
    cpu->setDisplay(display);

}

void Calculator::run()
{
    display->clear();
    while(std::cin >> buffer)
    {
        buffer = tolower(buffer);

        if(buffer == 'q')
        {
            //system("clear");
            return;
        }

        switch(buffer)
        {
            case '0': keyboard->keys[20]->press(); break;
            case '1': keyboard->keys[14]->press(); break;
            case '2': keyboard->keys[15]->press(); break;
            case '3': keyboard->keys[16]->press(); break;
            case '4': keyboard->keys[9]->press(); break;
            case '5': keyboard->keys[10]->press(); break;
            case '6': keyboard->keys[11]->press(); break;
            case '7': keyboard->keys[4]->press(); break;
            case '8': keyboard->keys[5]->press(); break;
            case '9': keyboard->keys[6]->press(); break;

            case '+': keyboard->keys[22]->press(); break;
            case '-': keyboard->keys[17]->press(); break;
            case '/': keyboard->keys[7]->press(); break;
            case '*': keyboard->keys[12]->press(); break;
            case 'r': keyboard->keys[18]->press(); break;
            case '%': keyboard->keys[23]->press(); break;
            
            case 'c': keyboard->keys[13]->press(); break;
            case 'a': keyboard->keys[8]->press(); break;
            case '.': keyboard->keys[19]->press(); break;
            case 'm': keyboard->keys[0]->press(); break;
            case '#': keyboard->keys[1]->press(); break;
            case '~': keyboard->keys[2]->press(); break;
            case '^': keyboard->keys[3]->press(); break;
            case '=': keyboard->keys[21]->press(); break;

            default: break;
        }
    }
}