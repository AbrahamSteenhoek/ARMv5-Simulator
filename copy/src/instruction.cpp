/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * instruction.cpp
 *  Contains the definitions of the methods declared in 'instruction.cpp'
 * --------------------------------------------------------------------------*/



#include "instruction.h"

Instruction::Instruction(uint bits, RegisterBank *_regs, Memory *_mem): bits(bits), regs(_regs), mem(_mem)
{
    // cond [1] is the first 4 bits of the encoded instruction
    cond = bits >> 28;
}


bool Instruction::condPass() {
    bool N = regs->getCPSR() & (1 << 31);
    bool Z = regs->getCPSR() & (1 << 30);
    bool C = regs->getCPSR() & (1 << 29);
    bool V = regs->getCPSR() & (1 << 28);

    switch(cond) {
        //EQ
    case 0b0000:
        return (Z) ? true : false;
        //NE
    case 0b0001:
        return (!Z)? true : false;
        //CS/HS
    case 0b0010:
        return (C) ? true : false;
        //CC/LO
    case 0b0011:
        return (!C) ? true : false;
        //MI
    case 0b0100:
        return (N) ? true : false;
        //PL
    case 0b0101:
        return (!N) ? true : false;
        //VS
    case 0b0110:
        return (V) ? true : false;
        //VC
    case 0b0111:
        return (!V) ? true : false;
        //HI
    case 0b1000:
        return (C && !Z) ? true : false;
        //LS
    case 0b1001:
        return (!C || Z) ? true : false;
        //GE
    case 0b1010:
        return (N == V) ? true : false;
        //LT
    case 0b1011:
        return (N != V) ? true : false;
        //GT
    case 0b1100:
        return ((!Z) || (N != V)) ? true : false;
        //LE
    case 0b1101:
        return (Z || (N != V)) ? true : false;
        // ALWAYS
    case 0b1110:
        return true;

    }

    return false;
}

QString Instruction::condCode()
{
    switch(cond) {
        //EQ
    case 0b0000:
        return "eq";
        //NE
    case 0b0001:
        return "ne";
        //CS/HS
    case 0b0010:
        return "cs";
        //CC/LO
    case 0b0011:
        return "cc";
        //MI
    case 0b0100:
        return "mi";
        //PL
    case 0b0101:
        return "pl";
        //VS
    case 0b0110:
        return "vs";
        //VC
    case 0b0111:
        return "vc";
        //HI
    case 0b1000:
        return "hi";
        //LS
    case 0b1001:
        return "ls";
        //GE
    case 0b1010:
        return "ge";
        //LT
    case 0b1011:
        return "lt";
        //GT
    case 0b1100:
        return "gt";
        //LE
    case 0b1101:
        return "le";
        // ALWAYS
    case 0b1110:
        return "";

    }
}
