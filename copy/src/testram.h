/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * testram.h
 *  - contains the declarations of the constructor and all methods for the testRAM class
 * --------------------------------------------------------------------------*/

#pragma once
#include "memory.h"
#include <cassert>

#ifndef TESTRAM_H
#define TESTRAM_H



class testRAM
{
public:
    testRAM();
    static void runTests();
};

#endif // TESTRAM_H
