
#ifndef INSTRUCTION_EXCEPTION_H
#define INSTRUCTION_EXCEPTION_H

#include "memory.h"
#include "registerbank.h"
#include "instruction.h"

class Instruction_Exception : public Instruction
{
    uint e_code;
    uint dest_addr;
    uint max_bytes_to_store;
public:
    Instruction_Exception(uint bits, RegisterBank* _regs, Memory *_mem);

    uint E_CODE() { return e_code; }
    void exec();
    void disassemble();
    void decode();

};

#endif // INSTRUCTION_EXCEPTION_H
