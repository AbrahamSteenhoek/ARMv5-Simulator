/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * instruction_loadstore.h
 *  Contains the declarations of the methods declared in 'instruction_loadstore.h'
 * --------------------------------------------------------------------------*/


#ifndef INSTRUCTION_LOADSTORE_H
#define INSTRUCTION_LOADSTORE_H

#include "instruction.h"
#include "registerbank.h"
#include "memory.h"

// NOTE: disassembly is not implemented yet in pseudocode because of the many variations on load/store instructions
class Instruction_LoadStore: public Instruction
{
    // immediate or reg offset
    bool i;
    // pre or post index
    bool p;
    // up/down
    bool u;
    // unsigned byte or word
    bool b;
    // writeback
    bool w;
    // load or store
    bool l;

    unsigned char Rd;
    unsigned char Rn;

    // effective address calculated from base register and offset
    uint eff_address;

    // source 2
    Operand2* offset;

    // register list from low-to-high order
    vector<unsigned char> reglist;

public:
    Instruction_LoadStore(uint bits, RegisterBank *regs, Memory *mem);

    // calls load or store depending on the L flag
    void exec();

    void decode();
    void decodeOperand2();
    void computeEA();

    void load();
    void store();
    // ldmia
    void ldmfd();
    // stmdb
    void stmfd();

    // getters for debugging
    unsigned char rd() { return Rd; }
    unsigned char rn() { return Rn; }
    vector<unsigned char> getRegList() { return reglist; }

    bool isReglistContinuous();

    void disassemble();

};

#endif // INSTRUCTION_LOADSTORE_H
