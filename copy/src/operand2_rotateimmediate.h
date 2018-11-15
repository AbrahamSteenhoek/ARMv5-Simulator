#include "operand2.h"

#ifndef OPERAND2_ROTATEIMMEDIATE_H
#define OPERAND2_ROTATEIMMEDIATE_H


class Operand2_RotateImmediate: public Operand2
{
    // value to rotate immediate by
    unsigned char rot;
    // 8 bit immediate value rot
    unsigned char imm;
public:
    Operand2_RotateImmediate(ushort bits);

    unsigned char Rotate() { return rot; }
    unsigned char Immediate() { return imm; }
};

#endif // OPERAND2_ROTATEIMMEDIATE_H
