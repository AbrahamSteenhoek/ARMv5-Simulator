#include "instruction_exception.h"

Instruction_Exception::Instruction_Exception(uint bits, RegisterBank *regs, Memory *mem): Instruction (bits, regs, mem)
{
    e_code = 0;
    decode();
    disassemble();
}

void Instruction_Exception::exec()
{
    //cout << "exec SWI " << e_code << endl;
    if (e_code != 0x11)
        regs->ExceptionProcessing(SWI);
}

void Instruction_Exception::disassemble()
{
    // for now the SWI instruction is the only instruction
    asm_text.append(QString("swi %1").arg(QString::number(e_code)));
}

void Instruction_Exception::decode()
{
    e_code = Memory::ExtractBits(bits, 0, 23);
}
