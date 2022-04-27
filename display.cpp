#include "display.hpp"

Display::Display()
{
    memset(disp, ' ', 19);
    disp[19] = '\0';
}

void Display::print()
{
    system("clear");
    printf(" _______________________\n");
    printf("|  ___________________  |\n");
    printf("| |%s| |\n", disp);
    printf("| |___________________| |\n");
}

void Display::shift()
{
    for(int i = 2; i < 18; i++)
        disp[i] = disp[i+1];
}

void Display::add(Digit d)
{
    shift();
    disp[18] = d + '0';
    print();    
}

void Display::addDecimalSeparator()
{
    shift();
    disp[18] = '.';
    print();
}
void Display::setSignal()
{
    disp[0] = '-';
    print();
}

void Display::setError()
{
    disp[1] = 'E';
    print();
}

void Display::clear()
{
    memset(disp, ' ', 19);
    print();
}