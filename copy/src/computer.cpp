/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * computer.cpp
 *  Contains the definitions of the methods declared in 'computer.cpp'
 * --------------------------------------------------------------------------*/

#include "computer.h"

Computer::Computer(Options* _opts): running(0), tracing(0), step_number(1), breakpoint(0)
{
    Options& opts = *_opts;
    // instantiate RAM
    RAM = new Memory(opts["mem"]);
    traceAll = opts.traceall();

    // instantiate regs
    // 16 regs(r0-r15) + CPSR = 17 regs total
    regs = new RegisterBank();
    regs->changeMode(SYS);

    // instantiate cpu
    cpu = new CPU();
    // hook up references between CPU and RAM/regs
    cpu->setMemory(RAM);
    cpu->setRegs(regs);

    breakpoints = {};
}

/*
 * Method: run()
 * - performs the fetch-decode-execute cycle on loop until the running flag is disabled, which can be either from user intervention or from reaching a SWI instruction
 */
void Computer::run()
{
    int instr;

    while(running) {

        if(breakpoint == true && breakpoints.find(regs->get(15)) != breakpoints.end()) {
            running = false;
            cpu->incPC();
            break;
        }
        step();

        // halt on the SWI 0x11 instruction
        if(dynamic_cast<Instruction_Exception*>(cpu->curInstruction()) != nullptr) {
            if(((Instruction_Exception*)cpu->curInstruction())->E_CODE() == 0x11) {
                running = false;
                continue;
            }
        }

        // if interrupts are enabled AND the CPU IRQ pin is high
        // finish executing current instruction, then
        if(regs->getFlag(IF) == 1 && cpu->getIRQ() == 1) {
            cpu->setIRQ(0);
            // handle IRQ expection
            //cout << "IRQ" << endl;
            regs->ExceptionProcessing(IRQ);
        }

    }

}

/*
 * Method: step()
 * - Performs a single cycle of fetch-decode-execute
 */
void Computer::step()
{
    int instr = cpu->fetch();
    curInstrAddr = regs->get(15);
    cpu->decode(curInstrAddr);
    cpu->incPC();
    //cout << "instr at addr: " << QString("%1").arg(curInstrAddr,0, 16, QChar('0')).toStdString() << endl;
    cpu->execute();

    step_number++;
    if((*traceStream).is_open()) {
        traceLine();
    }
}

/*
 * Method: traceLine()
 * - adds another trace line to the trace log file
 * - trace line follows the following format:
 * - step_number program_counter checksum nzcf mode r0 r1 r2 r3 r4 r5 r6 r7 r8 r9 r10 r11 r12 r13 r14
 */
void Computer::traceLine()
{
    // if traceall flag is not set, only execute instructions while in SYS mode.  Exit otherwise
    if(traceAll == 0) {
        if(regs->curMode() != SYS && curInstrAddr < RAM->progEntryPoint())
            return;
    }

    // first add step_number
    QString line = QString("%1 ").arg(step_number, 6, 10, QChar('0'));
    // PC (0x)
    line.append(QString("%1 ").arg(curInstrAddr, 8, 16, QChar('0')));
    // checksum (10)
    line.append(QString("%1 ").arg(RAM->calcChecksumForRAM(), 8, 16, QChar('0')));
    // nzcf
    uint cpsr = regs->getCPSR();
    bool n = (cpsr & (1<<31)) != 0;
    bool z = (cpsr & (1<<30)) != 0;
    bool c = (cpsr & (1<<29)) != 0;
    bool f = (cpsr & (1<<28)) != 0;
    line.append(QString("%1%2%3%4 ").arg(QString::number(n), QString::number(z), QString::number(c), QString::number(f)));

    //CPU mode (SYS, SVC, and IRQ)
    switch(mode()) {
    case SYS:
        line.append("SYS ");
        break;
    case SVC:
        line.append("SVC ");
        break;
    case IRQ:
        line.append("IRQ ");
        break;
    }

    // r0-14
    for(int i = 0; i <= 14; i++) {
        line.append(QString("%1=").arg(QString::number(i)));
        line.append(QString("%1 ").arg(regs->get(i), 8, 16, QChar('0')));
    }

    *traceStream << line.toUpper().toStdString() << endl;
}

/*
 * Method: addBreakpoint
 * - adds a breakpoint to the computer's internally stored breakpoint list
 */
void Computer::addBreakpoint(uint bp)
{
    // no need to add duplicate breakpoints
    if(breakpoints.find(bp) == breakpoints.end())
        breakpoints.insert(bp);
}

/*
 * Method: clearMemory()
 * - zeroes out the computer's memory
 */
void Computer::clearMemory()
{
    RAM->clear();
    regs->clear();
    step_number = 0;
}
