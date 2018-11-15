/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * operand2.h
 *  Contains the declarations of the methods declared in 'operand2.h'
 * --------------------------------------------------------------------------*/

#ifndef OPERAND2_H
#define OPERAND2_H

//#include "instruction.h"
#include "barrelshifter.h"
#include "registerbank.h"


/*
 * Method: Operand2
 * - Parent class for all variants of Operand2, which is used in Data Processing and load/store instructions
 */
class Operand2
{
protected:

    int value;
    // shifter_carry_out
    bool s_c_out;

    RegisterBank* regs;
public:
    Operand2(ushort bits, RegisterBank* regs);
    int val() { return value; }

    bool shifter_carry_out() { return s_c_out; }
    void setShifter_carry_out();

    virtual QString toString() = 0;
};

#endif // OPERAND2_H
