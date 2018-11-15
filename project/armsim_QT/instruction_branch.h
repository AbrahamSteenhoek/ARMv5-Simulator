/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * instruction_branch.h
 *  Contains the declarations of the methods declared in 'instruction_branch.h'
 * --------------------------------------------------------------------------*/

#ifndef INSTRUCTION_BRANCH_H
#define INSTRUCTION_BRANCH_H

#include "instruction.h"
#include "registerbank.h"
#include "memory.h"

class Instruction_Branch: public Instruction
{
    bool bx;
    bool l;
    int offset;
    uint Rm;
    int result;
    uint curAddr;

public:
    Instruction_Branch(uint bits, RegisterBank *regs, Memory *mem, uint cAddr);

    void exec();
    void disassemble();
    void disassemble(uint curAddr);
    void decode();
};

#endif // INSTRUCTION_BRANCH_H
