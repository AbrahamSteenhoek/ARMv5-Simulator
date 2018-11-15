#include "barrelshifter.h"

BarrelShifter::BarrelShifter()
{

}


/*
 * Method: lsl
 * - performs a left shift on the number a total of times specified by the shift parameter and returns the result
 */
uint BarrelShifter::lsl(uint num, uint shifts)
{
    return (num << shifts);
}

/*
 * Method: lsr
 * - performs a logical right shift on the number a total of times specified by the shift parameter and returns the result
 */
uint BarrelShifter::lsr(uint num, uint shifts)
{
    return (num >> shifts);
}

/*
 * Method: asr
 * - performs a arithmetic right shift on the number a total of times specified by the shift parameter and returns the result
 */
uint BarrelShifter::asr(int num, uint shifts)
{
    return (num >> shifts);
}

/*
 * Method: ror
 * - performs a right rotate on the number a total of times specified by the shift parameter and returns the result
 */
uint BarrelShifter::ror(uint num, uint moves)
{
    return (num >>moves) | (num << (sizeof(uint)*CHAR_BIT - moves));
}

/*
 * Method: autoShift
 * - calls the appropriate shift or rotate on the number depending on the shiftCode and returns the result
 */
int BarrelShifter::autoShift(unsigned char shiftCode, uint num, uint shifts)
{
    switch(shiftCode) {
        case 0b00:
            return BarrelShifter::lsl(num, shifts);
        case 0b01:
            return BarrelShifter::lsr(num, shifts);
        case 0b10:
            return BarrelShifter::asr(num, shifts);
        case 0b11:
            return BarrelShifter::ror(num, shifts);
    }
}
