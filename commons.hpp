#ifndef _COMMONS_H_
#define _COMMONS_H_

enum Digit {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

enum Operation {ADDITION, SUBTRACTION, DIVISION, MULTIPLICATION, 
                SQUARE_ROOT, PERCENTAGE, NONE};

enum Control {CLEAR, RESET, DECIMAL_SEPARATOR, MEMORY_READ, MEMORY_CLEAR, 
              MEMORY_ADDITION, MEMORY_SUBTRACTION, EQUAL};

enum Signal {POSITIVE, NEGATIVE};

class Receiver;
class Key;
class Keyboard;
class Display;
class Cpu;
class Calculator;

#endif