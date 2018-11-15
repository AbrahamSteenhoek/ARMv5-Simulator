/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * instruction_branch.cpp
 *  Contains the definitions of the methods declared in 'instruction_branch.cpp'
 * --------------------------------------------------------------------------*/

#include "instruction_branch.h"

Instruction_Branch::Instruction_Branch(uint bits, RegisterBank *regs, Memory *mem, uint cAddr): Instruction (bits, regs, mem), l(false), result (0), curAddr(cAddr)
{
    // is it (B, BL) or (BX)
    bx = ( ((Memory::ExtractBits(bits, 20, 27) >> 20) == 0b00010010) && ((Memory::ExtractBits(bits, 4, 7) >> 4 == 0b0001)) );
    if(bx) {

    }
    else {
        l = bits & (1 << 24);
    }
    //cout << "curAddr = " << QString("%1").arg(curAddr,0, 16, QChar('0')).toStdString() << endl;
    decode();
    disassemble();
    //cout << "branch offset for instr(" << asm_text.toStdString() << ") = " << offset << endl;
    //cout << "result = " << QString("%1").arg(result, 8, 16, QChar('0')).toStdString() << endl;
}

void Instruction_Branch::exec()
{
    //cout << "BRANCH instr: " << QString("%1").arg(bits,8, 16, QChar('0')).toStdString() << endl;
    if(!condPass()) {
        //cout << "branch not taken" << endl;
        return;
    }

    //cout << "BRANCH" << endl;
    if (bx) {
        // for BX, PC = val@Rm AND 0xFFFFFFFE(offset)
        regs->set(15, offset);
    }
    else {
        if(l) {
            regs->set(14, regs->get(15));
        }
        //cout << "BRANCH instr: " << QString("%1").arg(bits,0, 16, QChar('0')).toStdString() << endl;
        //cout << "branching to result: " << QString("%1").arg(result,0, 16, QChar('0')).toStdString() << endl;
        regs->set(15, result);
        //cout << "after branch, PC = " << QString("%1").arg(regs->get(15),0, 16, QChar('0')).toStdString() << endl;
    }
}

// TODO: handle instruction disassembly
void Instruction_Branch::disassemble()
{
    asm_text.append("b");
    if(bx) {
        asm_text.append("x");
        asm_text.append(QString("%1 %2").arg(condCode(), RegisterBank::regFormatString(Rm)));
    }
    else {
        if(l)
            asm_text.append("l");
        asm_text.append(QString("%1 #%2").arg(condCode(), QString::number(result)));
    }
}

void Instruction_Branch::disassemble(uint curAddr)
{

}

void Instruction_Branch::decode()
{
    if (bx) {
        Rm = Memory::ExtractBits(bits, 0, 3);
        uint valRm = regs->readFromReg(Rm);
        offset = valRm & 0xFFFFFFFE;
    }
    else {
        offset = Memory::ExtractBits(bits, 0, 23);
        if((offset & (1 << 23)) != 0) {
            offset |= 0x3F000000;
        }
        offset <<= 2;
        //cout << "offset = " << QString("%1").arg(offset,0, 16, QChar('0')).toStdString() << endl;
        //int curAddr = regs->get(15);
        result = curAddr + offset + 8;
        //cout << "decoded result = " << QString("%1").arg(result,0, 16, QChar('0')).toStdString() << endl;
    }
}
