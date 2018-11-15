#include "operand2_rotateimmediate.h"

Operand2_RotateImmediate::Operand2_RotateImmediate(ushort bits): Operand2(bits)
{
    // 4-bit rotate value
    rot = Memory::ExtractBits(bits, 8, 11) >> 8;
    // 8-bit immediate
    imm = Memory::ExtractBits(bits, 0, 7);
}
