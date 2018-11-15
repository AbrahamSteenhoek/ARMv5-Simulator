/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * testCPU.cpp
 *  - contains the definitions of the constructor and all methods for the testCPU class
 * --------------------------------------------------------------------------*/

#include "testcpu.h"

testCPU::testCPU()
{

}

void testCPU::runTests()
{
    qInfo() << "testing CPU class...";

    Memory *RAM = new Memory("64");
    RegisterBank *regs = new RegisterBank(17);
    CPU *testCPU = new CPU(RAM,regs);

    RAM->WriteByte(4, 0xFF);
    RAM->WriteByte(8, 0xEE);
    RAM->WriteByte(12, 0xDD);
    // PC should start at 0
    assert(testCPU->fetch() == 0x00);
    testCPU->incPC();
    assert(testCPU->fetch() == 0xFF);
    testCPU->incPC();
    assert(testCPU->fetch() == 0xEE);
    testCPU->incPC();
    assert(testCPU->fetch() == 0xDD);

    // test that decode returns the proper subclass of Instruction parent class
    RAM->clear();
    regs->set(15, 0);
    RAM->WriteWord(0x0, 0xE1A05003);
    RAM->WriteWord(0x4, 0xE5954019);
    RAM->WriteWord(0x8, 0xE0854106);
    assert(testCPU->fetch() == 0xE1A05003);
    testCPU->incPC();
    Instruction* instr = testCPU->decode(regs->get(15));
    assert(dynamic_cast<Instruction_DataProcessing*>(instr) != nullptr);
    assert(testCPU->fetch() == 0xE5954019);
    testCPU->incPC();
    instr = testCPU->decode(regs->get(15));
    assert(dynamic_cast<Instruction_LoadStore*>(instr) != nullptr);
    assert(testCPU->fetch() == 0xE0854106);
    testCPU->incPC();
    instr = testCPU->decode(regs->get(15));
    assert(dynamic_cast<Instruction_DataProcessing*>(instr) != nullptr);

    // testing CPSR manipulation
    regs->setCPSR(0xFFFFFFFF);
    regs->getNZCV();
    regs->resetNZCF();
    assert(regs->getCPSR() == 0x0FFFFFFF);
    regs->setFlag(31, 1);
    assert(regs->getCPSR() == 0x8FFFFFFF);
    regs->setFlag(31, 0);
    assert(regs->getCPSR() == 0x0FFFFFFF);
    regs->setFlag(30, 1);
    assert(regs->getCPSR() == 0x4FFFFFFF);
    regs->setFlag(29, 1);
    assert(regs->getCPSR() == 0x6FFFFFFF);

    regs = new RegisterBank();
    RAM = new Memory("");

    //test mode switching
    regs->clear();
    regs->set(SP, 0xEE);
    regs->set(LR, 0xFF);
    regs->setCPSR(0xE);
    assert(regs->get(SP) == 0xEE);
    assert(regs->get(LR) == 0xFF);
    assert(regs->getSPSR() == 0xE);
    regs->setFlag(IF, 0);
    regs->ExceptionProcessing(SWI);
    assert(Memory::ExtractBits(regs->getCPSR(), 0, 4) == SVC);
    assert(regs->getFlag(IF) == 1);
    assert(regs->get(SP) == 0x0);
    assert(regs->get(LR) == 0x0);
    assert(regs->getSPSR() == 0xE);
    assert(regs->get(PC) == 0x8);
    regs->setSPSR(0xF);
    assert(regs->getSPSR() == 0xF);
    //cout << "CPSR: " << regs->getCPSR()<< endl;
    assert(regs->getCPSR() == 0b10010011);

    regs->setFlag(IF, 1);
    regs->ExceptionProcessing(IRQ);
    assert(Memory::ExtractBits(regs->getCPSR(), 0, 4) == IRQ);
    assert(regs->getFlag(IF) == 1);


    qInfo() << "CPU unit tests successful." << endl;
}
