/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * testloader.cpp
 *  - contains the definitions of the constructor and all methods for the TestLoader class
 * --------------------------------------------------------------------------*/


#include "testloader.h"

testLoader::testLoader()
{

}

void testLoader::runTests()
{
    qInfo() << "Teasting Loader class...";

    Memory *ram_test1 = new Memory("");
    Memory *ram_test2 = new Memory("");
    Memory *ram_test3 = new Memory("");
    RegisterBank *regs = new RegisterBank(17);
    CPU *testCPU1 = new CPU(ram_test1 ,regs);
    CPU *testCPU2 = new CPU(ram_test2 ,regs);
    CPU *testCPU3 = new CPU(ram_test3 ,regs);

    Loader *loader = new Loader("test2.exe", testCPU2);
    assert(ram_test2->calcChecksumForRAM() == 536864433);
    assert(regs->get(15) == 0x1038);
    assert(regs->get(13) == 0x7000);

    loader = new Loader("test1.exe", testCPU1);
    assert(ram_test1->calcChecksumForRAM() == 536861081);
    assert(regs->get(15) == 0x138);
    assert(regs->get(13) == 0x7000);

    loader = new Loader("test3.exe", testCPU3);
    assert(ram_test3->calcChecksumForRAM() == 536861199);
    assert(regs->get(15) == 0x1038);
    assert(regs->get(13) == 0x7000);

    qInfo() << "Loader unit tests successful" << endl;
}
