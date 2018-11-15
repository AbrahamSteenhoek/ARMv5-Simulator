/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * testloader.h
 *  - contains the declarations of the constructor and all methods for the TestLoader class
 * --------------------------------------------------------------------------*/

#pragma once
#include "loader.h"
#include "memory.h"
#include "cpu.h"
#include "registerbank.h"
#include <cassert>

#ifndef TESTLOADER_H
#define TESTLOADER_H


class testLoader
{
public:
    testLoader();
    static void runTests();
};

#endif // TESTLOADER_H
