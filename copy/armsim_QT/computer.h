/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * computer.h
 *  Contains the declarations of the methods declared in 'computer.h'
 * --------------------------------------------------------------------------*/

#include <unordered_set>
#include <ostream>
#include "memory.h"
#include "cpu.h"
#include "options.h"

#ifndef COMPUTER_H
#define COMPUTER_H


class Computer
{
    CPU *cpu;
    Memory *RAM;
    // something here for regs
    RegisterBank* regs;

    // flags for running and tracing options
    bool running;
    bool tracing;
    bool traceAll;

    // list of breakpoint addresses
    unordered_set<uint> breakpoints;
    bool breakpoint;

    unsigned char lastKeyPressed;

    // number of fetch-decode-execute cycles since last load/reset
    int step_number;
    // curInstr holds the address of the current instruction
    uint curInstrAddr;


    // stream to print trace to
    ofstream *traceStream;

public:
    Computer(Options *_opts);
    void run();
    void step();

    // methods for runing conditions
    void setRunning(bool flag) { running = flag; }

    // methods for tracing conditions
    void setTracing(bool flag) { tracing = flag; }
    bool getTracing() { return tracing; }
    void setTracingStream(ofstream *strm) { traceStream = strm; }
    ofstream* getTracingStream() { return traceStream; }
    void traceLine();

    int getStep_number() { return step_number; }

    void addBreakpoint(uint bp);
    void clearBreakpoints() { breakpoints.clear(); }
    void printBreakpoints() { cout << "breakpoints: " ; std::copy(breakpoints.begin(), breakpoints.end(), std::ostream_iterator<int>(std::cout, " ")); }
    void setBreakPoint(bool flag) { breakpoint = flag; }

    RegisterBank* registers(){ return regs; }
    uint mode() { return regs->curMode(); }
    Memory* memory() { return RAM; }
    CPU* getCPU() { return cpu; }
    void setCPU(CPU* _cpu) { cpu = _cpu; }
    void clearMemory();
};

#endif // COMPUTER_H
