/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * cpu.h
 *  Contains the declarations of the methods declared in 'cpu.h'
 * --------------------------------------------------------------------------*/

using namespace std;

#ifndef CPU_H
#define CPU_H

#include <vector>
#include <QThread>
#include "memory.h"
#include "registerbank.h"
#include "instruction.h"
#include "instruction_branch.h"
#include "instruction_dataprocessing.h"
#include "instruction_loadstore.h"
#include "instruction_exception.h"

class CPU
{
    // reference to RAM
    Memory *RAM;
    // reference to registers
    RegisterBank* regs;
    // might need to just have unique refs to each reg

    // instruction register holds the current
    uint ir;

    bool irq;

    Instruction *curInstr;


public:
    CPU();
    CPU(Memory* _RAM, RegisterBank* _regs);

    void setMemory(Memory* _RAM) { RAM = _RAM; }
    void setRegs(RegisterBank* _regs) { regs = _regs; }
    void incPC() { regs->set(15, regs->get(15) + 4); }
    void setIRQ(bool on) { irq = on; }
    bool getIRQ() { return irq; }

    Instruction* curInstruction() { return curInstr; }

    RegisterBank* Regs() { return regs; }
    Memory* memory() { return RAM; }

    uint mode() { return regs->curMode(); }

    int fetch();
    Instruction *decode(uint instrAddr);
    void execute();
    void reset();

    static QString disassemblyForInstr(uint instr, RegisterBank *regs, Memory* memory, uint curAddr);

    uint IR() { return ir; }
};

#endif // CPU_H
