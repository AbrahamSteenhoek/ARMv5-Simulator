#pragma once
#include "computer.h"
#include <cassert>

#ifndef TESTCOMPUTER_H
#define TESTCOMPUTER_H


class testComputer
{
public:
    testComputer(Options *opts);
    static void runTests(Options *opts);

};

#endif // TESTCOMPUTER_H
