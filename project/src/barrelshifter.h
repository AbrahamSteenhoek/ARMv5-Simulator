/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * barrelshifter.h
 *  Contains the declarations of the methods declared in 'barrelshifter.h'
 * --------------------------------------------------------------------------*/
#include "memory.h"

#ifndef BARRELSHIFTER_H
#define BARRELSHIFTER_H


class BarrelShifter
{
public:
    BarrelShifter();

    static uint lsl(uint num, uint shifts);
    static uint lsr(uint num, uint shifts);
    static uint asr(int num, uint shifts);
    static uint ror(uint num, uint moves);

    // determines the appropriate shift to use on the num depending on the shiftCode
    static int autoShift(unsigned char shiftCode, uint num, uint shifts);
};

#endif // BARRELSHIFTER_H
