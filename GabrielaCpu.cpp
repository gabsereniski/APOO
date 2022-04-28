#include "GabrielaCpu.hpp"

#define GET_RESULT -1

GabrielaCpu::GabrielaCpu()
{
    display = nullptr;
    mem = 0.0;
    overflow = 0;

    for(int r = 0; r < 2; r++)
        clearRegister(r);

    lastReceived = '\0';
    curReg = 0;
}

GabrielaCpu::~GabrielaCpu()
{
    display = nullptr;
    mem = 0.0;

    for(int r = 0; r < 2; r++)
        clearRegister(r);

    lastReceived = '\0';
    curReg = 0;
}

//PRIVATE FUNCTIONS---------------------------------------------//

void GabrielaCpu::clearRegister(int r)
{
    ops[r] = 0.0;
    regs[r] = "0";
    regsNod[r] = 0;
    regHasDecSep[r] = false;
    regsSign[r] = POSITIVE;
}

void GabrielaCpu::reset()
{
    mem = 0.0;
    overflow = 0;
    lastReceived = '\0';
    curReg = 0;

    for(int r = 0; r < 2; r++)
        clearRegister(r);
}

int GabrielaCpu::countDigits(int r)
{
    float f = isFloat(ops[r]);
    int c = 0;
    
    for(int i = 0; regs[r][i] != '.'; i++)
    {
        if(regs[r][i] == '-') continue;
        c++;
    }

    if(c > 8) overflow = true;
    if(!f) return c;

    int d = 0;
    std::string fl = std::to_string(f);

    for(int i = 0; i < fl.size(); i++)
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
    regs[0] = std::to_string(ops[0]);
    regsNod[0] = countDigits(0);
    
    if(overflow) display->setError();    
    if(ops[0] < 0) regsSign[0] = NEGATIVE;
    if(isFloat(ops[0])) regHasDecSep[0] = true;

    sendDigits(0);

    if(lastReceived == 'o') clearRegister(1);
}

void GabrielaCpu::sendDigits(int r)
{
    display->clear();

    int c = 0, i = 0;

    if(regsSign[r]) display->setSignal();
    
    while(c < regsNod[r])
    {
        char d = regs[r][i];
        if(d == '-')
        {
            i++;
            continue; 
        }
        if(d == '.' && regHasDecSep[r])
        {
            display->addDecimalSeparator();
            i++;
            continue;
        }
        if(d == '.' && !regHasDecSep[r]) break;
        display->add((Digit)(d - '0'));
        c++, i++;
        if(c > 8)
        {
            display->setError();
            break;
        }

    }
}

//PUBLIC FUNCTIONS-------------------------------------------//

void GabrielaCpu::setDisplay(GabrielaDisplay* display)
{
    this->display = display;
}

void GabrielaCpu::receiveDigit(Digit d)
{
    if(lastReceived == '\0' || lastReceived == '=') 
    {
        curReg = 0; 
        display->clear();
        clearRegister(0);
        clearRegister(1);
    }
    else if(lastReceived == 'o') curReg = 1, display->clear();

    if(lastReceived != 'd' && lastReceived != '-' && lastReceived != '.')
        clearRegister(curReg);

    if(regsNod[curReg] < 8)
    {  
        if(!d && !regsNod[curReg]) return;

        regs[curReg] += std::to_string(d);
        regsNod[curReg]++;
        display->add(d);
    }
    
    lastReceived = 'd';
}

void GabrielaCpu::receiveOperation(Operation op)
{      
    if((lastReceived == 'o' || lastReceived == '\0') && (op == SUBTRACTION))
    {
        display->clear();
        regsSign[curReg] = NEGATIVE;
        regs[curReg] = "-";
        lastReceived = '-';
        display->setSignal();
        return;
    }

    else if((lastReceived == 'o') && op == this->op && 
            (op != SQUARE_ROOT && op != PERCENTAGE)) return;

    if(!curReg)
    {
        ops[0] = std::stof(regs[0]);
        
        if(op == SQUARE_ROOT || op == PERCENTAGE)
        {
            ops[0] = ALU(ops[0], 0.0, op);
            return compute();
        }
        
        updateOp(op);
        curReg++;

        return;
    }

    else
    {
        ops[1] = std::stof(regs[1]);
        if((op == SQUARE_ROOT || op == PERCENTAGE) && lastReceived == 'd')
        {
            ops[1] = ALU(ops[1], 0.0, op);
            compute();
            regs[1] = std::to_string(ops[1]);
            sendDigits(1);
        }
        else if((op == SQUARE_ROOT || op == PERCENTAGE))
        {
            ops[0] = ALU(ops[0], 0.0, op);
            compute();
            regs[0] = std::to_string(ops[0]);
            sendDigits(0);
        }   
    }

    if(lastReceived != '=')
    {
        ops[0] = ALU(ops[0], ops[1], this->op);
        compute();
    } 
    
    else if(lastReceived == '=' && op == GET_RESULT)
    {
        ops[0] = ALU(ops[0], ops[1], this->op);
        compute();
    }
    
    if(op != GET_RESULT && op != SQUARE_ROOT && op != PERCENTAGE)
        this->op = op, lastReceived = 'o';
}

void GabrielaCpu::receiveControl(Control ctrl)
{
    switch(ctrl)
    {
        case CLEAR:
            clearRegister(curReg);
            display->clear();
            break;
        
        case RESET:
            reset();
            display->clear();
            break;
        
        case DECIMAL_SEPARATOR:
            if(regHasDecSep[curReg]) break;
            if(!regsNod[curReg])
            {
                regs[curReg] += ".";
                regsNod[curReg]++;
                regHasDecSep[curReg] = true;
            }
            else
            {
                regs[curReg] += ".";
                regHasDecSep[curReg] = true;
            }
            lastReceived = '.';
            display->addDecimalSeparator();
            break;

        case MEMORY_READ:
            ops[curReg] = mem;
            regs[curReg] = std::to_string(mem);
            sendDigits(curReg);
            break;

        case MEMORY_CLEAR:
            mem = 0.0;
            break;

        case MEMORY_ADDITION: 
            if(lastReceived == '=' || lastReceived == 'o')       
                mem += std::stof(regs[0]);
            else
                mem += std::stof(regs[1]);
            regs[curReg] = "0";
            break;
        
        case MEMORY_SUBTRACTION:
            if(lastReceived == '=' || lastReceived == 'o')       
                mem -= std::stof(regs[0]);
            else
                mem -= std::stof(regs[1]);
            regs[curReg] = "0";
            break;
        
        case EQUAL:
            receiveOperation((Operation)GET_RESULT);
            lastReceived = '=';
            break;
    }
}
