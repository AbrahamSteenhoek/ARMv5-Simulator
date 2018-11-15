/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * testcomputer.cpp
 *  - contains the definitions of the constructor and all methods for the testComputer class
 * --------------------------------------------------------------------------*/

#include "testcomputer.h"

testComputer::testComputer(Options *opts)
{

}

void testComputer::runTests(Options *opts)
{
    qInfo() << "testing Computer class...";
    //Memory *RAM = new Memory("64");
    //RegisterBank *regs = new RegisterBank(17);
    //CPU *testCPU = new CPU(RAM,regs);
    Computer *testComputer = new Computer(opts);
    //testComputer->setCPU(testCPU);

    testComputer->memory()->WriteByte( 0, 0xFF);
    testComputer->memory()->WriteByte( 4, 0xFF);
    testComputer->memory()->WriteByte( 8, 0xEE);
    testComputer->memory()->WriteByte(12, 0xDD);

    //testComputer->run();
    //assert(testComputer->getStep_number() == 0);
    testComputer->setRunning(true);
    //testComputer->run();
    //assert(testComputer->getStep_number() == 4);

    qInfo() << "Computer tests complete." << endl;
}
