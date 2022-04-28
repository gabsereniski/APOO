#include "GabrielaKey.hpp"
#include "GabrielaKeyboard.hpp"

void GabrielaKey::setReceiver(GabrielaReceiver* receiver)
{
    this->receiver = receiver;
}

//DIGIT-----------------------------------------------//

GabrielaKeyDigit::GabrielaKeyDigit(Digit d):digit(d){}

void GabrielaKeyDigit::press()
{
    receiver->receiveDigit(digit);
}

//OPERATION-------------------------------------------//

GabrielaKeyOperation::GabrielaKeyOperation(Operation op):operation(op){}

void GabrielaKeyOperation::press()
{   
    receiver->receiveOperation(operation);
}

//CONTROL---------------------------------------------//

GabrielaKeyControl::GabrielaKeyControl(Control ctrl):control(ctrl){}

void GabrielaKeyControl::press()
{
    receiver->receiveControl(control);
}