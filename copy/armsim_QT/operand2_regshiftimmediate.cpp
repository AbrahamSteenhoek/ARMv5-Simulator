#include "operand2_regshiftimmediate.h"


Operand2_RegShiftImmediate::Operand2_RegShiftImmediate(ushort bits, RegisterBank *regs): Operand2(bits, regs)
{
    // 5 bit field
    shiftImm = Memory::ExtractBits(bits, 7, 11) >> 7;
    shiftType = Memory::ExtractBits(bits, 5, 6) >> 5;
    Rm = Memory::ExtractBits(bits, 0, 3);
    uint valAtRm = regs->readFromReg(Rm);
    value = BarrelShifter::autoShift(shiftType, valAtRm, shiftImm);

    setShifter_carry_out();
}

void Operand2_RegShiftImmediate::setShifter_carry_out()
{
    switch(shiftType) {
    //lsl
    case 0b00:
        s_c_out = (shiftImm == 0)? regs->getFlag(CF) : valAtRm & (1 << (32 - shiftImm));
        break;
    //lsr
    case 0b01:
    //asr
    case 0b10:
        s_c_out = (shiftImm == 0)? (valAtRm & (1 << 31)) : (valAtRm & (1 << (shiftImm - 1)));
        break;
    //ror
    case 0b11:
        s_c_out = (shiftImm == 0)? (valAtRm & (1)) : (valAtRm & (1 << (shiftImm - 1)));
        break;
    }
}


/*
 * Method: toString()
 * - returns a formatted QString representing the ARM assembly that the Operand2 makes up
 */
QString Operand2_RegShiftImmediate::toString()
{
    // base register
    QString text = QString("%1").arg(RegisterBank::regFormatString(Rm));

    // adding lsl #0 is unnecessary
    if(shiftImm != 0) {
        text.append(", ");
        // shift type
        switch(shiftType) {
        case 0b00:
            text.append("lsl ");
            break;
        case 0b01:
            text.append("lsr ");
            break;
        case 0b10:
            text.append("asr ");
            break;
        case 0b11:
            text.append("ror ");
            break;
        }
        text.append("#");
        // immediate shift value
        text.append(QString::number(shiftImm));
    }
    return text;
}
