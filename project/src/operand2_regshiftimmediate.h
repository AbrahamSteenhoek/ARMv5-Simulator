
#include "operand2.h"

#ifndef OPERAND2_REGSHIFTIMMEDIATE_H
#define OPERAND2_REGSHIFTIMMEDIATE_H

/*
 * Class: Operand2_Immediate
 * - represents the reg-shifted immediate for data processing instructions
 */
class Operand2_RegShiftImmediate: public Operand2
{
    // 5-bit shift number
    uint shiftImm;
    unsigned char shiftType;
    //int value;
    unsigned char Rm;
    uint valAtRm;

public:
    Operand2_RegShiftImmediate(ushort bits, RegisterBank* regs);
    void setShifter_carry_out();
    uint Rm_val() { return valAtRm; }
    QString toString();
};

#endif // OPERAND2_REGSHIFTIMMEDIATE_H
