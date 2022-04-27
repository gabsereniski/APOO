#include "key.hpp"
#include "keyboard.hpp"

void Key::setReceiver(Receiver* receiver)
{
    this->receiver = receiver;
}

//DIGIT-----------------------------------------------//

KeyDigit::KeyDigit(Digit d):digit(d){}

void KeyDigit::press()
{
    receiver->receiveDigit(digit);
}

//OPERATION-------------------------------------------//

KeyOperation::KeyOperation(Operation op):operation(op){}

void KeyOperation::press()
{   
    receiver->receiveOperation(operation);
}

//CONTROL---------------------------------------------//

KeyControl::KeyControl(Control ctrl):control(ctrl){}

void KeyControl::press()
{
    receiver->receiveControl(control);
}