/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * cpu.cpp
 *  Contains the definitions of the methods declared in 'cpu.cpp'
 * --------------------------------------------------------------------------*/

#include "cpu.h"

CPU::CPU()
{

}

CPU::CPU(Memory *_RAM, RegisterBank *_regs): irq(false)
{
    RAM = _RAM;
    regs = _regs;
}

/*
 * Method: fetch()
 * - fetches the instruction at the program counter and saves it in the CPU's intruction pointer
 * - The PC is incremented after every fetch
 */
int CPU::fetch()
{
    ir = RAM->ReadWord(regs->get(15));

    return ir;
}

/*
 * Method: decode()
 * - parses the instruction in the instruction pointer and returns a pointer to the appropriate type of Instruction subclass
 * - sets the computer's curInstr pointer to the same instruciton pointer.
 * - currently supports Data Processing and Load/Store instructions
 */
Instruction* CPU::decode(uint instrAddr)
{
    // TODO: add Instruction_Exception subclass
    uint instrType = Memory::ExtractBits(ir, 25, 27) >> 25;
    if((Memory::ExtractBits(ir, 24,27) >> 24) == 0b1111) {
        curInstr = new Instruction_Exception(ir, regs, RAM);
    }
    else {

        switch(instrType) {
        // Data Processing
        case 0b000:
        case 0b001:
            curInstr = new Instruction_DataProcessing(ir, regs, RAM);
            break;
        // Load/Store
        case 0b010:
        case 0b011:
        // LDM/STM
        case 0b100:
            curInstr = new Instruction_LoadStore(ir, regs, RAM);
            break;
        // B, BL
        case 0b101:
            curInstr = new Instruction_Branch(ir, regs, RAM, instrAddr);
            break;
        default:
            //cout << "SWI" << endl;
            break;
        }
        // BX
        if( ((Memory::ExtractBits(ir, 20, 27) >> 20) == 0b00010010) && ((Memory::ExtractBits(ir, 4, 7) >> 4 == 0b0001)) ) {
            curInstr = new Instruction_Branch(ir, regs, RAM, instrAddr);
        }
    }

    return curInstr;
}

/*
 * Method: execute
 * - Calls the exec() method of the curInstr pointer
 * - polymorphism handles the different types of execution for different instructions
 */
void CPU::execute()
{
    //cout << "executing: ";
    curInstr->exec();
    //cout << "executed" << endl;
}

void CPU::reset()
{
    regs->changeMode(SVC);
    if(RAM->ReadWord(0) != 0x00000000)
        regs->set(15, 0x0000);
}

/*
 * Method: disassemblyForInstr
 * - returns the format string for the instruction passed in
 */
QString CPU::disassemblyForInstr(uint instr, RegisterBank* regs, Memory* memory, uint curAddr)
{
    Instruction *iptr = nullptr;
    QString text = "";
    bool swi = (Memory::ExtractBits(instr, 24,27) >> 24) == 0b1111;
    if (instr == 0) {
        return "";
    }
    // SWI instr
    if (swi) {
        iptr = new Instruction_Exception(instr, regs, memory);
    }
    else {
        uint instrType = Memory::ExtractBits(instr, 25, 27) >> 25;

        switch(instrType) {
        // Data Processing
        case 0b000:
        case 0b001:
            iptr = new Instruction_DataProcessing(instr, regs, memory);
            break;
        // Load/Store
        case 0b010:
        case 0b011:
        case 0b100:
            iptr = new Instruction_LoadStore(instr, regs, memory);
            break;
        case 0b101:
            iptr = new Instruction_Branch(instr, regs, memory, curAddr);
            break;
        default:
            text = "";
            break;
        }
        if( ((Memory::ExtractBits(instr, 20, 27) >> 20) == 0b00010010) && ((Memory::ExtractBits(instr, 4, 7) >> 4 == 0b0001)) ) {
            iptr = new Instruction_Branch(instr, regs, memory, curAddr);
        }
        //text = iptr->text();

    }
    text = (iptr != nullptr)? iptr->text(): "";
    //cout << "here" << endl;
    return text;
}
