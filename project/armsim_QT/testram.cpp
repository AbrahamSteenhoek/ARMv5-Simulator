/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * testram.cpp
 *  - contains the definitions of the constructor and all methods for the testRAM class
 * --------------------------------------------------------------------------*/

#include "testram.h"


testRAM::testRAM()
{

}

void testRAM::runTests()
{
    qInfo() << "Testing RAM...";

    //qInfo() << "testing setting RAM to specific value in constructor";
    Memory testRAM_1("4");
    assert(testRAM_1.addr_space() == 4);

    //qInfo() << "testing WriteByte/HalfWord/Word & ReadByte/HalfWord/Word";
    // test WriteByte
    testRAM_1.WriteByte(0, 0x01);
    testRAM_1.WriteByte(1, 0x82);
    testRAM_1.WriteByte(2, 0x03);
    testRAM_1.WriteByte(3, 0x84);

    // test overloaded brackets[]
    assert(testRAM_1[0] == 0x01);
    assert(testRAM_1[1] == 0x82);
    assert(testRAM_1[2] == 0x03);
    assert(testRAM_1[3] == 0x84);


    //test ReadByte
    assert(testRAM_1.ReadByte(0) == 0x01);
    assert(testRAM_1.ReadByte(1) == 0x82);
    assert(testRAM_1.ReadByte(2) == 0x03);
    assert(testRAM_1.ReadByte(3) == 0x84);

    //qInfo() << "testing calcChecksum";
    // test checksum
    assert(testRAM_1.calcChecksumForRAM() == 268);

    Memory testRAM_2("");
    //qInfo() << "testing RAM default memory set if no memory is specified";
    // test default memory set
    assert(testRAM_2.addr_space() == 32768);

    // test writeHalfWord
    testRAM_2.WriteHalfWord(0, 0x4455);

    assert(testRAM_2.ReadByte(0) == 0x55);
    assert(testRAM_2.ReadByte(1) == 0x44);

    // test readHalfWord
    assert(testRAM_2.ReadHalfWord(0) == 0x4455);

    // test that WriteHalfWord ignores addresses that aren't divisible by 2
    assert(testRAM_2.WriteHalfWord(1, 0x9999) == false);
    assert(testRAM_2.ReadHalfWord(0) == 0x4455);

    // test writeWord
    testRAM_2.WriteWord(0, 0x11223344);

    assert(testRAM_2.ReadByte(0) == 0x44);
    assert(testRAM_2.ReadByte(1) == 0x33);
    assert(testRAM_2.ReadByte(2) == 0x22);
    assert(testRAM_2.ReadByte(3) == 0x11);

    // test readWord
    assert(testRAM_2.ReadWord(0) == 0x11223344);

    // test that writeword returns false writing to addressess that aren't divisible by 4
    assert(testRAM_2.WriteWord(1, 0x99999999) == false);
    assert(testRAM_2.WriteWord(2, 0x99999999) == false);
    assert(testRAM_2.WriteWord(3, 0x99999999) == false);
    assert(testRAM_2.ReadWord(0) == 0x11223344);


    // test checksum
    testRAM_2.WriteWord(0, 0x84038201);
    assert(testRAM_2.calcChecksumForRAM() == 536854790);

    //qInfo() << "testing TestFlag";
    // test TestFlag
    assert(testRAM_2.TestFlag(0, 31) == 1);
    assert(testRAM_2.TestFlag(0, 30) == 0);
    assert(testRAM_2.TestFlag(0, 29) == 0);
    assert(testRAM_2.TestFlag(0, 28) == 0);
    assert(testRAM_2.TestFlag(0, 27) == 0);
    assert(testRAM_2.TestFlag(0, 26) == 1);
    assert(testRAM_2.TestFlag(0, 25) == 0);
    assert(testRAM_2.TestFlag(0, 24) == 0);
    assert(testRAM_2.TestFlag(0, 23) == 0);
    assert(testRAM_2.TestFlag(0, 22) == 0);
    assert(testRAM_2.TestFlag(0, 21) == 0);
    assert(testRAM_2.TestFlag(0, 20) == 0);
    assert(testRAM_2.TestFlag(0, 19) == 0);
    assert(testRAM_2.TestFlag(0, 18) == 0);
    assert(testRAM_2.TestFlag(0, 17) == 1);
    assert(testRAM_2.TestFlag(0, 16) == 1);
    assert(testRAM_2.TestFlag(0, 15) == 1);
    assert(testRAM_2.TestFlag(0, 14) == 0);
    assert(testRAM_2.TestFlag(0, 13) == 0);
    assert(testRAM_2.TestFlag(0, 12) == 0);
    assert(testRAM_2.TestFlag(0, 11) == 0);
    assert(testRAM_2.TestFlag(0, 10) == 0);
    assert(testRAM_2.TestFlag(0, 9) == 1);
    assert(testRAM_2.TestFlag(0, 8) == 0);
    assert(testRAM_2.TestFlag(0, 7) == 0);
    assert(testRAM_2.TestFlag(0, 6) == 0);
    assert(testRAM_2.TestFlag(0, 5) == 0);
    assert(testRAM_2.TestFlag(0, 4) == 0);
    assert(testRAM_2.TestFlag(0, 3) == 0);
    assert(testRAM_2.TestFlag(0, 2) == 0);
    assert(testRAM_2.TestFlag(0, 1) == 0);
    assert(testRAM_2.TestFlag(0, 0) == 1);

    //qInfo() << "testing SetFlag";
    testRAM_2.WriteWord(0, 0);
    testRAM_2.SetFlag(0, 0, 1);
    assert(testRAM_2.ReadWord(0) == 1);
    testRAM_2.SetFlag(0, 1, 1);
    assert(testRAM_2.ReadWord(0) == 3);
    testRAM_2.SetFlag(0, 0, 0);
    assert(testRAM_2.ReadWord(0) == 2);
    testRAM_2.SetFlag(0, 1, 0);
    assert(testRAM_2.ReadWord(0) == 0);

    //qInfo() << "testing ExtractBits";
    assert(Memory::ExtractBits(0x5, 1,3) == 0x4);
    assert(Memory::ExtractBits(0xFFFFFFFF, 0, 31) == 0xFFFFFFFF);
    assert(Memory::ExtractBits(0xFFFFFFFF, 1, 31) == 0xFFFFFFFE);
    assert(Memory::ExtractBits(0xFFFFFFFF, 0, 30) == 0x7FFFFFFF);

    qInfo() << "RAM unit tests successful" << endl;
}
