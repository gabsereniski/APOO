#include "GabrielaDisplay.hpp"

GabrielaDisplay::GabrielaDisplay()
{
    memset(disp, ' ', 19);
    disp[19] = '\0';
}

GabrielaDisplay::~GabrielaDisplay(){}

//PRIVATE FUNCTIONS---------------------------------------------//

void GabrielaDisplay::print()
{
    system("clear");
    puts("");
    printf("         _______________________\n");
    printf("        |  ___________________  |\n");
    printf("        | |%s| |\n", disp);
    printf("        | |___________________| |\n");
    printf("        |_______________________|\n\n");

      puts("r: square root          %: percentage");
      puts("C: clear                A: clear all");
      puts("M: memory read          #: memory clear");
      puts("~: memory subtraction   ^: memory addition");
      puts("Q: quit\n");

    printf(">> ");
}

void GabrielaDisplay::shift()
{
    for(int i = 10; i < 18; i++)
        disp[i] = disp[i+1];
    /*for(int i = 2; i <= 10; i++)
        disp[i] = ' ';*/
}

//PUBLIC FUNCTIONS-------------------------------------------//

void GabrielaDisplay::add(Digit d)
{
    shift();
    disp[18] = d + '0';
    print();    
}

void GabrielaDisplay::addDecimalSeparator()
{
    shift();
    disp[18] = '.';
    print();
}
void GabrielaDisplay::setSignal()
{
    disp[0] = '-';
    print();
}

void GabrielaDisplay::setError()
{
    clear();
    disp[7] = 'E';
    disp[8] = 'R';
    disp[9] = 'R';
    disp[10] = 'O';
    disp[11] = 'R';
    print();
}

void GabrielaDisplay::clear()
{
    memset(disp, ' ', 19);
    print();
}