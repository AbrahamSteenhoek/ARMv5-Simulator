/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * testcpu.h
 *  - contains the declarations of the constructor and all methods for the testCPU class
 * --------------------------------------------------------------------------*/
#pragma once
#include "cpu.h"
#include <cassert>

#ifndef TESTCPU_H
#define TESTCPU_H


class testCPU
{
public:
    testCPU();
    static void runTests();
};

#endif // TESTCPU_H
