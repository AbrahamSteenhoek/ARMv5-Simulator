#ifndef INSTRUCTION_MISC_H
#define INSTRUCTION_MISC_H

#include "instruction.h"
#include "registerbank.h"
#include "memory.h"

class Instruction_Misc: public Instruction
{
public:
    Instruction_Misc(uint bits, RegisterBank *_regs, Memory *_mem);


    // exec does nothing for SWI and no-op for now
    void exec() {}
};

#endif // INSTRUCTION_MISC_H
