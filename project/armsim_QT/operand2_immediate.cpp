/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * operand2_immediate.cpp
 *  Contains the definition of the methods declared in 'operand2_immediate.cpp'
 * --------------------------------------------------------------------------*/

#include "operand2_immediate.h"

Operand2_Immediate::Operand2_Immediate(uint bits, RegisterBank* regs, bool rot): Operand2(bits, regs)
{
    // 8-bit imm rotated right by rotate*2
    if(rot) {
        uint rotate = Memory::ExtractBits(bits, 8, 11) >> 8;
        uint temp = Memory::ExtractBits(bits, 0, 7);
        value = BarrelShifter::ror(temp, rotate*2);
        //cout << "rotate val: " << rotate << endl;
        if(rotate == 0)  {
            s_c_out = regs->getFlag(CF);
        }
        else {
            s_c_out = value & (1 << 31);
        }
    }
    // 12-bit immediate
    else {
        value = Memory::ExtractBits(bits, 0,11);
        //cout << "imm val = " << value << endl;
    }

}

/*
 * Method: toString()
 * - returns a formatted QString representing the ARM assembly that the Operand2 makes up
 */
QString Operand2_Immediate::toString()
{
    return QString("#%1").arg(value);
}
