/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * instruction_branch.h
 *  Contains the declarations of the methods declared in 'instruction_branch.h'
 * --------------------------------------------------------------------------*/

#ifndef DATAPROCESSINGINSTRUCTION_H
#define DATAPROCESSINGINSTRUCTION_H

#include "memory.h"
#include "registerbank.h"
#include "instruction.h"
#include <limits.h>

class Instruction_DataProcessing: public Instruction
{
    bool i;
    unsigned char opcode;
    bool s;
    bool r;
    unsigned char dest;
    unsigned char Rn;
    uint source1;
    uint source2;
    bool regShiftimm;

    Operand2* shifter_op;

public:
    // constructor decodes the instruciton
    Instruction_DataProcessing(uint bits, RegisterBank* _regs, Memory* _mem);

    // getters
    bool I() { return i; }
    bool S() { return s; }
    unsigned char Dest() { return dest; }
    unsigned char Opcode() { return opcode; }
    uint Source1() { return source1; }
    uint Source2() { return source2; }
    Operand2* Op2() { return shifter_op; }

    // decodes the machine language into a valid Data Processing instruction and disassembles it simultaneously
    void decode();
    
    // parse the last 12 bits and determine the correct operand
    void decodeOperand2();
    void disassemble();

    // calls the appropriate method according to the opcode
    void exec();
    void setDest(uint val);

    // each type of data processing instr has a specific method to not clog up the exec() method
    uint MOV();
    uint MRS();
    uint MSR();
    uint MVN();
    uint ADD();
    uint SUB();
    uint RSB();
    uint MUL();
    uint AND();
    uint ORR();
    uint EOR();
    uint BIC();
    uint CMP();

    // break the execution methods for each instruction into their respective categories to make debugging easier in the future
    // void arithmetic(); // add,sub
    // void logic(); // and,eor,orr,bic
    // void compare(); // cmp,cmn,tst,teq
};

#endif // DATAPROCESSINGINSTRUCTION_H
