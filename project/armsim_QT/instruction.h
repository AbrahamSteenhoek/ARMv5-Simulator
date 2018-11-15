/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * instruction.h
 *  Contains the declarations of the methods declared in 'instruction.h'
 * --------------------------------------------------------------------------*/

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "registerbank.h"
//#include "operand2.h"
#include "operand2_immediate.h"
#include "operand2_regshiftimmediate.h"
#include "operand2_regshiftreg.h"
#include "barrelshifter.h"

class Instruction
{
protected:
    // every instruction comes with a 4-bit condition field
    unsigned char cond;

    unsigned char instrType;
    // etra 28-bits after condition field
    uint bits;
    // ARM asm representation of machine language instruction
    QString asm_text;
    // reference to memory and registers is necessary to perform instructions and to set/access CPSR flags
    RegisterBank *regs;
    Memory *mem;

public:
    // constructor decodes the intruction
    Instruction(uint bits, RegisterBank* _regs, Memory *_mem);

    bool condPass();
    // every instruction subclass must be able to be executed
    virtual void exec() = 0;
    virtual void disassemble() = 0;
    virtual void decode() = 0;

    QString condCode();

    // ARM assembly text of instruction
    QString text() { return asm_text; }

};

#endif // INSTRUCTION_H
