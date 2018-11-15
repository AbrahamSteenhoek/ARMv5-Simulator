#include "operand2_regshiftreg.h"


Operand2_RegShiftReg::Operand2_RegShiftReg(uint bits, RegisterBank *regs): Operand2(bits, regs)
{
    Rm = Memory::ExtractBits(bits, 0, 3);
    Rs = Memory::ExtractBits(bits, 8, 11) >> 8;
    valAtRm = regs->readFromReg(Rm);
    valAtRs = regs->readFromReg(Rs);

    //cout << "Rm: " << valAtRm << " Rs: " << valAtRs << endl;
    shiftType = Memory::ExtractBits(bits, 5, 6) >> 5;
    value = BarrelShifter::autoShift(shiftType, valAtRm, valAtRs);
    //cout << "value: " << value << endl;

    setShifter_carry_out();
}

void Operand2_RegShiftReg::setShifter_carry_out()
{
    // Rs[7:0]
    unsigned char Rs_7_0 = Memory::ExtractBits(valAtRs, 0, 7);
    // Rs[4:0]
    unsigned char Rs_4_0 = Memory::ExtractBits(valAtRs, 0, 4);

    if(Rs_7_0 == 0) {
        s_c_out = regs->getFlag(CF);
        return;
    }

    switch(shiftType) {
    //lsl
    case 0b00:
        if (Rs_7_0 < 32)
            s_c_out = valAtRm & (1 << (32-Rs_7_0));
        else if (Rs_7_0 == 32)
            s_c_out = valAtRm & 0b1;
        /* Rs[7:0] > 32 */
        else
            s_c_out = 0;

        break;
    //lsr
    case 0b01:
        if (Rs_7_0 < 32)
            s_c_out = valAtRm & (1 << (Rs_7_0-1));
        else if (Rs_7_0 == 32)
            s_c_out = valAtRm & (1 << 31);
        /* Rs[7:0] > 32 */
        else
            s_c_out = 0;
    //asr
    case 0b10:
        if (Rs_7_0 < 32)
            s_c_out = valAtRm & (1 << (Rs_7_0-1));
        /* Rs[7:0] >= 32 */
        else
            s_c_out = valAtRm & (1 << 31);

        break;
    //ror
    case 0b11:
        if(Rs_4_0 == 0)
            s_c_out = valAtRm & (1 << 31);
        else /* Rs[4:0] > 0 */
            s_c_out = valAtRm & (1 << (Rs_4_0 - 1));
        break;
    }
}


/*
 * Method: toString()
 * - returns a formatted QString representing the ARM assembly that the Operand2 makes up
 */
QString Operand2_RegShiftReg::toString()
{
    // base register and then shift register
    QString text = QString("%1, ").arg(RegisterBank::regFormatString(Rm));
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
    text.append(QString("%1").arg(RegisterBank::regFormatString(Rs)));

    return text;
}
