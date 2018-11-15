#pragma once
#include "instruction.h"
#include "cpu.h"
#include <cassert>
#include "instruction_dataprocessing.h"

#ifndef TESTINSTRUCTION_H
#define TESTINSTRUCTION_H


class testInstruction
{
public:
    testInstruction();
    static void runTests();
};

#endif // TESTINSTRUCTION_H
