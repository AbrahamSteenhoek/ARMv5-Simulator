/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * ram.h
 *  - contains the declarations for the RAM class and all of its methods
 *  - contains methods to read into and write from memory, tests for valid integer values, and bit flag tests
 *  - contians method to compute the checksum of the RAM
 * --------------------------------------------------------------------------*/

#include "options.h"
#include "elf.h"
#include "outputdevice.h"
#include <queue>

#ifndef RAM_H
#define RAM_H

// 1 MB is 1048576 bytes
#define MAX_MEM_SIZE 1048576
#define DEF_MEM_SIZE 32768

class Memory
{
    // total memory space available
    uint memsize;

    uint pEntry;

    // each index is 1 byte (unsigned char type)
    unsigned char* memory;

    unsigned char lastKeyPressed;
    unsigned char writeChar;

    OutputDevice *outputDevice;

public:
    Memory(QString);
    bool isPosNum(QString);

    // bit is in the range [0..31]
    bool TestFlag(uint addr, uint32_t bit);
    void SetFlag(uint addr, uint32_t bit, bool flag);
    void setProgEntryPoint(uint addr) { pEntry = addr; }
    uint progEntryPoint() { return pEntry; }

    void setLastKeyPressed(unsigned char key) { lastKeyPressed = key; }
    unsigned char getLastKeyPressed() { return lastKeyPressed; }
    void setOutputDevice(OutputDevice* oD) { outputDevice = oD; }

    // returns a 4-byte word.  startbit-endbit ranges from [0..31]
    uint32_t static ExtractBits(uint32_t word, uint32_t startBit, uint32_t endBit);

    // write methods
    bool WriteByte(uint addr, unsigned char byte);
    bool WriteHalfWord(uint addr, ushort halfWord);
    bool WriteWord(uint addr, uint32_t word);

    // read methods
    unsigned char ReadByte(uint addr);
    ushort ReadHalfWord(uint addr);
    uint ReadWord(uint addr);

    // getters & setters
    unsigned char &operator[](uint32_t addr) { return memory[addr]; }
    unsigned char *array() { return memory; }

    // returns size of memory reserved for RAM
    uint addr_space() { return memsize; }

    void clear();

    int calcChecksumForRAM();
    int static calcChecksum(int arr_len, unsigned char *array);

    ~Memory();
};

#endif // RAM_H
