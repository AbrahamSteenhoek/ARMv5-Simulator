/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * operand2_immediate.h
 *  Contains the declarations of the methods declared in 'operand2_immediate.h'
 * --------------------------------------------------------------------------*/

#include "operand2.h"

#ifndef OPERAND2_IMMEDIATE_H
#define OPERAND2_IMMEDIATE_H

/*
 * Class: Operand2_Immediate
 * - represents the immediate operand2 for data processing instructions and the immediate addressing mode for load/store instructions
 */
class Operand2_Immediate: public Operand2
{
    // not unsigned becase offset can possible be negative
    // 12-bit immediate value
    //uint immediate;
public:
    // TODO: handle sign extend for 8-bit immediate it rotate is 0
    Operand2_Immediate(uint bits, RegisterBank* regs, bool rot);

    QString toString();
};

#endif // OPERAND2_IMMEDIATE_H
