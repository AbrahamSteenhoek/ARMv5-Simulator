/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * loader.cpp
 *  Contains the definitions of the methods declared in 'loader.cpp'
 * --------------------------------------------------------------------------*/

#include "loader.h"


/*
 * Method: isElf
 * Returns: bool
 *  - Accepts an 32-bit ElfHeader from a file as a parameter and determines if the header is in the correct ELF format.
 *  - if the header is in the incorrect format, returns false.  Otherwise, returns true
 */
bool Loader::isElf(Elf32_Ehdr elfHeader) {
    if (!(elfHeader.e_ident[0] == '\x7f' &&
          elfHeader.e_ident[1] == 'E' &&
          elfHeader.e_ident[2] == 'L' &&
          elfHeader.e_ident[3] == 'F')) {
        return false;
    }
    return true;
}

/*
 * Method: logMessage
 * Returns: void
 *  - Formats a log message with a given class/method label and the status message and displays it to qInfo()
 */
void Loader::logMessage(QString class_method, QString status)
{
    qInfo() << class_method << ": " << status;
}

/*
 * method: load_elf_segment
 * Returns: void
 *  - Loads a segment from the ELF file into memory by reading the info from the given program header entry.
 *  - Requires pointer to the file, an instance of a progHeader, and a pointer to memory
 */
void Loader::load_elf_segment(FILE *elf_file, Elf32_Phdr &progHeader, Memory *ram)
{
    // represents the current class and method.  Used to log progess messages
    QString class_method = "Loader::load_elf_segment";

    // move cursor to segment offset from beginning of file
    if(fseek(elf_file, progHeader.p_offset, SEEK_SET) != 0) {
        cerr << "Error seeking to program header in load_elf_segment method... " << endl;
        cerr << strerror(errno);
        return;
        exit(1);
    }

    // copy data into RAM one byte at a time
    unsigned char byte = 0;
    for(uint j = 0; j < progHeader.p_filesz; j++) {
        if(!fread(&byte, 1, 1, elf_file)) {
            cerr << "Error reading byte from file" << endl;
            cerr << strerror(errno);
            return;
            exit(1);
        }
        ram->WriteByte(progHeader.p_vaddr + j, byte);
    }
}

/*
 * Constructor: Loader
 *  - sets the filename and pointer to memory
 *  - calls function that loads segments from the file into memory
 */
Loader::Loader(QString _filename, CPU *_cpu)
{
    this->filename = _filename;
    this->cpu = _cpu;
    success = false;
    load_elf_file();
    // if load is successful then flag is set
}

/*
 * Memory: load_elf_file
 * Returns: void
 *  - opens the Loader's ELF file and reads each progHeader into an array of progHeaders
 *  - calls the load_elf_segment() method for each progHeader in the array
 *  - displays logging messages as the method is loading the file
 */
void Loader::load_elf_file()
{
    // represents the current class and method.  Used to log progess messages
    QString class_method = "Loader::load_elf_file";

    logMessage(class_method, QString("Opening %1...").arg(filename));
    FILE* elf_file = fopen(filename.toLatin1().data(), "rb");
    if(elf_file == nullptr) {
        cerr << "Unable to open input file with fopen." << filename.toStdString() << endl;
        exit(1);
    }
    Elf32_Ehdr elfHeader;

    logMessage(class_method, "Reading elf header");
    // read ELF header
    if (!fread(&elfHeader,sizeof(elfHeader), 1, elf_file)){
        cerr << "Error reading ELF header.";
        return;
        exit(1);
    }

    if(!isElf(elfHeader)) {
        cerr << "Input file is not an ELF file." << endl;
        return;
        exit(1);
    }

    logMessage(class_method, QString("Number of segments: %1").arg(QString::number(elfHeader.e_phnum)));
    logMessage(class_method, QString("Program header offset: %1").arg(QString::number(elfHeader.e_phoff)));

    // container to hold all the progheaders in the file
    Elf32_Phdr *progHeaders = new Elf32_Phdr[elfHeader.e_phnum];
    // visit every prog header entry
    for(uint i = 0; i < elfHeader.e_phnum; i++) {
        // offset of next prog header from beginning of file
        uint file_pos = elfHeader.e_phoff + elfHeader.e_phentsize * i;
        fseek(elf_file, file_pos, SEEK_SET);
        if(fseek(elf_file, file_pos, SEEK_SET) != 0)  {
            cerr << "Error seeking to program header: " << elfHeader.e_phoff + elfHeader.e_phentsize * i << endl;
            cerr << strerror(errno);
            exit(1);
        }

        unsigned char *data = new unsigned char[elfHeader.e_phentsize];
        fread(data, 1, elfHeader.e_phentsize, elf_file);
        if(!elf_file) {
            cerr << "Error reading program header." << endl;
            cerr << strerror(errno);
            return;
            exit(1);
        }
        uint temp_size = (sizeof(Elf32_Phdr) < elfHeader.e_phentsize)? sizeof(Elf32_Phdr) : elfHeader.e_phentsize;
        memcpy(&progHeaders[i], data, temp_size);
    }

    // load each segment into RAM
    for(int i = 0; i < elfHeader.e_phnum; i++) {
        //logMessage("Loader::load_elf_segment", QString("Segment %1 - Address = %2, Offset = %3, Size = %4").arg(QString::number(i+1), QString::number(progHeaders[i].p_vaddr), QString::number(progHeaders[i].p_offset), QString::number(progHeaders[i].p_filesz)));
        load_elf_segment(elf_file, progHeaders[i], cpu->memory());
    }

    logMessage(class_method, "Finished loading segments");
    // clean up reserved bytes
    delete[] progHeaders;

    fclose(elf_file);
    success = true;

    // set the Memory's instance var indicating prog entry point
    cpu->memory()->setProgEntryPoint(elfHeader.e_entry);
}
