
#include "operand2.h"

#ifndef OPERAND2_REGSHIFTREG_H
#define OPERAND2_REGSHIFTREG_H

/*
 * Class: Operand2_Immediate
 * - represents the reg-shifted register for data processing instructions
 */
class Operand2_RegShiftReg: public Operand2
{
    unsigned char shiftType;
    //int value;
    unsigned char Rm;
    unsigned char Rs;

    uint valAtRm;
    uint valAtRs;

public:
    Operand2_RegShiftReg(uint bits, RegisterBank* regs);
    void setShifter_carry_out();
    uint Rm_val() { return valAtRm; }
    uint Rs_val() { return valAtRs; }
    QString toString();
};

#endif // OPERAND2_REGSHIFTREG_H
