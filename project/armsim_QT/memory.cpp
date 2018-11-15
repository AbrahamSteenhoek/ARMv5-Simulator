/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * ram.h
 *  - contains the definitions for the RAM class and all of its methods
 *  - contains methods to read into and write from memory, tests for valid integer values, and bit flag tests
 *  - contians method to compute the checksum of the RAM
 * --------------------------------------------------------------------------*/

#include "memory.h"
/*
Method: isPosNum
Returns: bool
    - receives QString as input and only returns true if the QString represents a positive integer
*/
bool Memory::isPosNum(QString str)
{
    for(QChar c : str) {
        if(!c.isNumber())
            return false;
    }
    return true;
}

/*
 * Method: TestFlag
 * Returns: bool
 *  - returns the bit value at the selected bit position from range [0..31] in a word(32bit) of memory
 */
bool Memory::TestFlag(uint addr, uint32_t bit)
{   if(addr + 4 > memsize) {
        cerr << "Attempting to read outside of available memory space with TestFlag method." << endl;
        exit(1);
    }
    uint word = ReadWord(addr);
    return (word & (1 << bit));
}

/*
 * Method: SetFlag
 * Returns: bool
 *  - sets the bit at the selected bit position from range [0..31] in a word(32bit) of memory
 */
void Memory::SetFlag(uint addr, uint32_t bit, bool flag)
{
    if(addr + 4 > memsize) {
            cerr << "Attempting to read outside of available memory space with SetFlag method." << endl;
            exit(1);
    }
    uint word = ReadWord(addr);
    if(flag == 1) {
        word |= (1 << bit);
    }
    else {
        word &= ~(1 << bit);
    }
    WriteWord(addr, word);
}

/*
 * Method: ExtractBits
 * Returns uint
 *  - A static utility method that returns the bits in the range startBit..endBit from word, where startBit and endBit are in the range [0..31]
 */
uint32_t Memory::ExtractBits(uint32_t word, uint32_t startBit, uint32_t endBit)
{
    uint extract = 0;

    for (uint i = startBit; i <= endBit; i++) {
        extract |= (word & (1 << i));
    }
    return extract;
}

/*
 * Method: WriteByte
 * Returns: bool
 *  - changes the byte at a specific 32 bit memory address (addr) to the byte value passed in (byte)
 *  - returns true if write is successful, false if write would cause buffer overflow
 */
bool Memory::WriteByte(uint addr, unsigned char byte)
{
    if(addr == 0x100000) {
        // notify console and update memory-mapped IO
        writeChar = byte;
        outputDevice->writeCharToConsole(writeChar);
        return true;
    }

    if (addr >= addr_space()) {
        cerr << "Attempting to write outside of RAM space with WriteByte method." << endl;
        exit(1);
        return false;
    }

    memory[addr] = byte;
    return true;
}

/*
 * Method: WriteHalfWord
 * Returns: bool
 *  - changes the 2 bytes starting at a specific 32 bit memory address (addr) to the 2-byte value passed in (halfWord)
 *  - returns true if write is successful, false if write would cause buffer overflow
 *  - ignores attempts to write at an address that is not divisible by 2
 */
bool Memory::WriteHalfWord(uint addr, ushort halfWord)
{
    if(addr + 2 > memsize) {
            cerr << "Attempting to write outside of available memory space with WriteHalfWord method." << endl;
            exit(1);
        }
    if(addr % 2 == 0) {
        // LSB
        unsigned char byte1 = halfWord & 0xFF;
        // MSB
        unsigned char byte2 = (halfWord >> 8);

        memory[addr] = byte1;
        memory[addr + 1] = byte2;
        return true;
    }
    else {
        //cerr << "WriteHalfWord method required an address that is divisible by 2" << endl;
        return false;
    }
}

/*
 * Method: WriteWord
 * Returns: bool
 *  - changes the 4-byte word starting at a specific 32 bit memory address (addr) to the 4-byte value passed in (word)
 *  - returns true if write is successful, false if write would cause buffer overflow
 *  - ignores attempts to write at an address that is not divisible by 4
 */
bool Memory::WriteWord(uint addr, uint32_t word)
{
    if(addr + 4 > memsize) {
            cerr << "Attempting to write outside of available memory space with WriteWord method." << endl;
            exit(1);
    }
    if (addr % 4 == 0) {
    memory[addr] = word & 0xFFFFFF;
    memory[addr + 1] = word >> 8;
    memory[addr + 2] = word >> 16;
    memory[addr + 3] = word >> 24;
    return true;
    }else {
        //cerr << "WriteWord method required an address that is divisible by 4" << endl;
        return false;
    }
}

/*
 * Method: ReadByte
 * Returns: bool
 *  - reads the byte at a specific 32 bit memory address (addr) and returns its value
 *  - Quits the program if user attempts to read outside of available memory space
 */
unsigned char Memory::ReadByte(uint addr)
{
    // returns the last character pressed on the keyboard instead of the actual spot in memory
    if(addr == 0x100001) {
        return lastKeyPressed;
    }
    if (addr >= addr_space()) {
        cerr << "Attempting to read outside of RAM space with ReadByte method." << endl;
        exit(1);
    }

    return memory[addr];
}

/*
 * Method: ReadHalfWord
 * Returns: bool
 *  - reads the HalfWord(2 bytes) starting at a specific 32 bit memory address (addr) and returns its value
 *  - Quits the program if user attempts to read outside of available memory space
 */
ushort Memory::ReadHalfWord(uint addr)
{
    if(addr + 2 > memsize) {
            cerr << "Attempting to read outside of available memory space with ReadHalfWord method." << endl;
            exit(1);
    }
    if(addr % 2 == 0){
        return memory[addr] | (memory[addr + 1] << 8);
    }
    else {
        cerr << "ReadHalfWord method required an address that is divisible by 2" << endl;
    }
}

/*
 * Method: ReadWord
 * Returns: bool
 *  - reads the Word(4 bytes) starting at a specific 32 bit memory address (addr) and returns its value
 *  - Quits the program if user attempts to read outside of available memory space
 */
uint Memory::ReadWord(uint addr)
{
    //cout << "addr is " << addr << endl;
    //cout << "memsize is " << memsize << endl;
    if(addr + 4 > memsize) {
            cerr << "Address: " << addr << " is outside of available memory space: ReadWord method." << endl;
            exit(1);
    }
    if (addr % 4 == 0) {
    return memory[addr] | (memory[addr + 1] << 8) | (memory[addr + 2] << 16) | (memory[addr + 3] << 24);
    }
    else {
        cerr << "invalid addr: " << addr << "ReadWord method required an address that is divisible by 4" << endl;
        exit(1);
    }
}

/*
 * Method: clear
 *  - zeroes out the entire address space reserved for this instance of simulated memory
 */
void Memory::clear()
{
    memset(memory, 0, memsize);
}

/*
 * Method: calcChecksum
 * Returns: int
 *  - calculates the checksum for a given array of 1-byte values and returns the final sum
 */
int Memory::calcChecksum(int arr_len, unsigned char *array)
{
    int cksum = 0;

    for(int i = 0; i < arr_len; i++) {
        cksum += array[i] ^ i;
    }

    return cksum;
}

/*
 * Method: calcChecksumForRAM
 * Returns: int
 *  - calculates the checksum for this instance of RAM and returns the final sum
 */
int Memory::calcChecksumForRAM() {
    int cksum = 0;

    for(int i = 0; i < memsize; i++) {
        cksum += memory[i] ^ i;
    }

    return cksum;
}

/*
 * Constructor: RAM
 *  - creates an instance of simulated memory with the amount of bytes passed in from memsize_QStr
 *  - if no memory size is given, the default is 32Kb (32768 bytes)
 *  - max memory size is limited to 1MB
 */
Memory::Memory(QString memsize_QStr)
{
    if (memsize_QStr.isNull() || memsize_QStr == "") {
        memsize = DEF_MEM_SIZE;
    }
    else {
        if (!Memory::isPosNum(memsize_QStr)) {
            cerr << "--mem option requires positive <int> type" << endl;
            exit(1);
        }
        memsize = memsize_QStr.toInt();

    }
    
    // mem size is limited to 1MB
    if (memsize == 0 || memsize > MAX_MEM_SIZE) {
        cerr << "max memory size is limited to 1MB" << endl;
        exit(1);
    }

    // zero out the memory before loading into it
    memory = (unsigned char*) calloc(addr_space(), sizeof(unsigned char));
}

Memory::~Memory()
{
    delete[] memory;
}
