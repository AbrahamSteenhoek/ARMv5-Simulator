/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * loader.h
 *  - contains the declarations of all methods for the Loader class
 * --------------------------------------------------------------------------*/

#include "memory.h"
#include <cmath>
#include <cstring>
#include <algorithm>
#include "elf.h"
#include "stdio.h"
#include "computer.h"
#include <cstdio>

#ifndef LOADER_H
#define LOADER_H

/*----------------------------------------------------------------------------/
 * Class: Loader
 *  - Loads a given file in ELF format into an instance of simulated RAM
 *  - Displays logging messages during the loading process
 * --------------------------------------------------------------------------*/
class Loader
{
    // name of the ELF file
    QString filename;
    // instance of the simulated RAM
    //Memory *ram;
    // indicates completed loading process
    bool success;
    // reference to the CPU to set PC to program entry point
    CPU *cpu;
public:
    Loader(QString _filename, CPU *cpu);

    void load_elf_file();

    void load_elf_segment(FILE *elf_file, Elf32_Phdr &progHeader, Memory *ram);

    bool isElf(Elf32_Ehdr elfHeader);

    bool loaded() { return success; }

    void logMessage(QString class_method, QString status);
};

#endif // LOADER_H
