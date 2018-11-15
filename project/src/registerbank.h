/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * registerbank.h
 *  Contains the definitions of the methods declared in 'registerbank.h'
 * --------------------------------------------------------------------------*/

#ifndef REGISTERBANK_H
#define REGISTERBANK_H

// specific registers
#define PC 15
#define SP 13
#define LR 14

// condition flags
#define NF 31
#define ZF 30
#define CF 29
#define VF 28

// interrupt flag
#define IF 7

// exception types
#define SWI 0b10011

// modes
#define USR 0b10000
#define SYS 0b11111
#define SVC 0b10011
#define IRQ 0b10010

// registers for specific modes
#define CPSR 16
#define SPSR_svc 21
#define SPSR_irq 22
#define SP_svc 17
#define LR_svc 18
#define SP_irq 19
#define LR_irq 20

#include "memory.h"

class RegisterBank
{
    Memory* regs;
    uint mode;
public:
    RegisterBank();
    RegisterBank(int num_regs);

    // get the value in memory at ####
    // return the correct register depending on the mode
    uint get(uint reg);
    uint getCurModeReg(uint reg);
    bool getFlag(uint flag);
    uint readFromReg(uint reg);
    // get the value of the CPSR register
    uint getCPSR();
    uint getSPSR();
    uint curMode() { return mode; }

    // set reg r(1-15) to specific 32-bit value
    bool set(uint reg, int value);
    // set CPSR register
    bool setCPSR(int value);
    bool setSPSR(int value);
    void setFlag(uint flag, bool val);

    void changeMode(uint m);
    void ExceptionProcessing(uint eType);

    void clear();
    void resetNZCF();
    unsigned char getNZCV();
    
    unsigned char *array() { return regs->array(); }

    static QString regFormatString(unsigned char reg);
};

#endif // REGISTERBANK_H
