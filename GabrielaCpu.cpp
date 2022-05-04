#include "GabrielaCpu.hpp"

#include <cmath>
#include <sstream>

GabrielaCpu::GabrielaCpu()
{
    display = nullptr;
    mem = 0.0;
    overflow = 0;

    for(int r = 0; r < 2; r++)
        clearRegister(r);

    lastReceived = '\0';
    cur = 0;
}

GabrielaCpu::~GabrielaCpu()
{
    display = nullptr;
    mem = 0.0;

    for(int r = 0; r < 2; r++)
        clearRegister(r);

    lastReceived = '\0';
    cur = 0;
}

//PRIVATE FUNCTIONS---------------------------------------------//

void GabrielaCpu::clearRegister(int r)
{
    fReg[r] = 0.0;
    reg[r] = "0";
    numOfDigits[r] = 0;
    hasDecSep[r] = false;
    sign[r] = POSITIVE;
}

void GabrielaCpu::reset()
{
    mem = 0.0;
    overflow = 0;
    lastReceived = '\0';
    cur = 0;

    for(int r = 0; r < 2; r++)
        clearRegister(r);
}

int GabrielaCpu::countDigits(int r)
{
    float f = isFloat(fReg[r]);
    int c = 0;
    
    for(int i = 0; reg[r][i] != '.'; i++)
    {
        if(reg[r][i] == '-') continue;
        c++;
    }

    if(c > 8) overflow = true;
    if(!f) return c;

    int d = 0;
    std::string fl = std::to_string(f);

    for(int i = 1; i < fl.size(); i++)
    {
        bool flag = 1;
        for(int j = i+1; j < fl.size(); j++)
            if(fl[j] != '0') flag = 0;
        if(flag) break;
        d++;
    }
    
    if(c + 1 > 8) overflow = true;

    return c + d;
}

float GabrielaCpu::isFloat(float op)
{
    int n = op;
    return op - (float)n;
}
void GabrielaCpu::conversion(int r)
{
    reg[r] += "000000000000000";

    numOfDigits[r] = countDigits(r);
    
    if(overflow) if(display) display->setError();    
    if(fReg[r] < 0) sign[r] = NEGATIVE;
    if(isFloat(fReg[r])) hasDecSep[r] = true;
}
void GabrielaCpu::updateOp(Operation op)
{
    this->op = op;
    lastReceived = 'o';
}

float GabrielaCpu::ALU(float op1, float op2, Operation op)
{
    switch(op)
    {
        case ADDITION: return op1 + op2;
        case SUBTRACTION: return op1 - op2;
        case DIVISION: return op1 / op2;
        case MULTIPLICATION: return op1 * op2;
        case SQUARE_ROOT: return sqrt(op1);
        case PERCENTAGE: return op1 /= 100.0;
    }

    return 0.0;
}

void GabrielaCpu::compute()
{
    reg[0] = std::to_string(fReg[0]);
    
    conversion(0);

    sendDigits(0);

    if(lastReceived == 'o') clearRegister(1);
}

void GabrielaCpu::sendDigits(int r)
{
    if(display) display->clear();

    int c = 0, i = 0;

    if(sign[r]) if(display) display->setSignal(NEGATIVE);
    
    while(c < numOfDigits[r])
    {
        char d = reg[r][i];
        if(d == '-')
        {
            i++;
            continue; 
        }
        if(d == '.' && hasDecSep[r])
        {
            if(display) display->setDecimalSeparator();
            i++;
            continue;
        }
        if(d == '.' && !hasDecSep[r]) break;
        if(display) display->add((Digit)(d - '0'));
        c++, i++;
        if(c > 8)
        {
            if(display) display->setError();
            break;
        }

    }
}

//PUBLIC FUNCTIONS-------------------------------------------//

void GabrielaCpu::setDisplay(Display* display)
{
    this->display = display;
}

void GabrielaCpu::receiveDigit(Digit d)
{
    if(lastReceived == '\0' || lastReceived == '=') 
    {
        cur = 0; 
        if(display) display->clear();
        clearRegister(0);
        clearRegister(1);
    }
    else if(lastReceived == 'o')
    {
        cur = 1;
        if(display) display->clear();
    }

    if(lastReceived != 'd' && lastReceived != '-' && lastReceived != '.')
        clearRegister(cur);

    if(numOfDigits[cur] < 8)
    {  
        if(!d && !numOfDigits[cur]) return;

        reg[cur] += std::to_string(d);
        numOfDigits[cur]++;
        if(display) display->add(d);
    }
    
    lastReceived = 'd';
}

void GabrielaCpu::receiveOperation(Operation op)
{      
    if((lastReceived == 'o' || lastReceived == '\0') && (op == SUBTRACTION))
    {
        if(display) display->clear();
        sign[cur] = NEGATIVE;
        reg[cur] = "-";
        lastReceived = '-';
        if(display) display->setSignal(NEGATIVE);
        return;
    }

    else if((lastReceived == 'o') && op == this->op && 
            (op != SQUARE_ROOT && op != PERCENTAGE)) return;

    if(!cur)
    {
        fReg[0] = std::stof(reg[0]);
        
        if(op == SQUARE_ROOT || op == PERCENTAGE)
        {
            fReg[0] = ALU(fReg[0], 0.0, op);
            return compute();
        }
        
        updateOp(op);
        cur++;

        return;
    }

    else
    {
        fReg[1] = std::stof(reg[1]);
        if((op == SQUARE_ROOT || op == PERCENTAGE) && lastReceived == 'd')
        {
            fReg[1] = ALU(fReg[1], 0.0, op);
            compute();
            reg[1] = std::to_string(fReg[1]);
            sendDigits(1);
        }
        else if((op == SQUARE_ROOT || op == PERCENTAGE))
        {
            fReg[0] = ALU(fReg[0], 0.0, op);
            compute();
            reg[0] = std::to_string(fReg[0]);
            sendDigits(0);
        }   
    }

    if(lastReceived != '=')
    {
        fReg[0] = ALU(fReg[0], fReg[1], this->op);
        compute();
    } 
    
    else if(lastReceived == '=' && op == NONE)
    {
        fReg[0] = ALU(fReg[0], fReg[1], this->op);
        compute();
    }
    
    if(op != NONE && op != SQUARE_ROOT && op != PERCENTAGE)
        this->op = op, lastReceived = 'o';
}

void GabrielaCpu::receiveControl(Control ctrl)
{
    int r = !(lastReceived == '=');
    switch(ctrl)
    {
        case CLEAR:
            clearRegister(cur);
            if(display) display->clear();
            break;
        
        case RESET:
            reset();
            if(display) display->clear();
            break;
        
        case DECIMAL_SEPARATOR:
            if(hasDecSep[cur]) break;
            if(!numOfDigits[cur])
            {
                reg[cur] += ".";
                numOfDigits[cur]++;
                hasDecSep[cur] = true;
            }
            else
            {
                reg[cur] += ".";
                hasDecSep[cur] = true;
            }
            lastReceived = '.';
            if(display) display->setDecimalSeparator();
            break;

        case MEMORY_READ:
            fReg[r] = mem;
            reg[r] = std::to_string(mem);
            conversion(r);
            sendDigits(r);

            break;

        case MEMORY_CLEAR:
            mem = 0.0;
            break;

        case MEMORY_ADDITION: 
            if(lastReceived == '=' || lastReceived == 'o')       
                mem += std::stof(reg[0]);
            else
                mem += std::stof(reg[cur]);
            reg[cur] = "0";
            break;
        
        case MEMORY_SUBTRACTION:
            if(lastReceived == '=' || lastReceived == 'o')       
                mem -= std::stof(reg[0]);
            else
                mem -= std::stof(reg[cur]);
            reg[cur] = "0";
            break;

        case EQUAL:
            receiveOperation(NONE);
            lastReceived = '=';
            break;
    }
}
