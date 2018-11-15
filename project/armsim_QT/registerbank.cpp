#include "registerbank.h"

// default constructor hardcodes in Supervisor, System, IRQ, and User modes
RegisterBank::RegisterBank(): mode (SYS)
{
    regs = new Memory(QString("%1").arg(QString::number(23 * 4)));
}

RegisterBank::RegisterBank(int num_regs)
{
    regs = new Memory(QString::number(4*num_regs));
}

uint RegisterBank::get(uint reg)
{
    reg = getCurModeReg(reg);

    if(reg * 4 <= regs->addr_space()) {
        return regs->ReadWord(reg * 4);
    }
    else {
        cerr << "Attempting to read outside of memory space of register bank.";
        exit(1);
    }
}

uint RegisterBank::getCurModeReg(uint reg)
{
    reg = (reg & 0b1111);
    if(reg == SP || reg == LR) {
        switch(mode) {
        // return normal regs for SYS mode
        case SYS:
            break;
        case SVC:
            //cout << "SVC mode.  Accessing reg: " << reg << endl;
            reg = (reg == SP)? SP_svc : LR_svc;
            break;
        case IRQ:
            //cout << "IRQ mode.  Accessing reg: " << reg << endl;
            reg = (reg == SP)? SP_irq : LR_irq;
            break;
        }
    }
    return reg;
}

bool RegisterBank::getFlag(uint flag)
{
    return getCPSR() & (1 << flag);
}

uint RegisterBank::readFromReg(uint reg)
{
    uint val = get(reg);
    if(reg == 15) {
        val += 8;
    }
    return val;
}

uint RegisterBank::getCPSR()
{
    return regs->ReadWord(CPSR * 4);
}

uint RegisterBank::getSPSR()
{
    switch(mode) {
    case USR:
    case SYS:
        return getCPSR();
    case SVC:
        return regs->ReadWord(SPSR_svc * 4);
    case IRQ:
        return regs->ReadWord(SPSR_irq * 4);
    }
}

bool RegisterBank::set(uint reg, int value)
{
    reg = getCurModeReg(reg);

    if(reg * 4 <= regs->addr_space()) {
        return regs->WriteWord(reg * 4, value);
    }
    else {
        cerr << "Attempting to read outside of memory space of register bank.";
        exit(1);
    }
}

bool RegisterBank::setCPSR(int value)
{
    mode = Memory::ExtractBits(value, 0, 5);

    return regs->WriteWord(CPSR * 4, value);
}

bool RegisterBank::setSPSR(int value)
{
    switch(mode) {
    case USR:
    case SYS:
        return setCPSR(value);
    case SVC:
        return regs->WriteWord(SPSR_svc * 4, value);
    case IRQ:
        return regs->WriteWord(SPSR_irq * 4, value);
    }
}

void RegisterBank::setFlag(uint flag, bool bitval)
{
    uint CPSR_temp = getCPSR();

    CPSR_temp = (CPSR_temp & ~(1 << flag)) | (bitval << flag);
    setCPSR(CPSR_temp);
}

// TODO: look at class notes for Exception processing and fix this method
void RegisterBank::changeMode(uint m)
{
    // set the mode instance var
    mode = m;
    //cout << "changing to mode: " << mode << endl;

    // change the mode bits in the CPSR
    uint CPSR_temp = getCPSR();
    CPSR_temp = CPSR_temp >> 5;
    CPSR_temp = CPSR_temp << 5;
    CPSR_temp |= mode;
    setCPSR(CPSR_temp);
}

void RegisterBank::ExceptionProcessing(uint eType)
{
    switch(eType) {
    case SWI:
        mode = SVC;
        break;
    case IRQ:
        mode = IRQ;
        break;
    default:
        cout << "unrecignized exception type";
        break;
    }

    // sets appropriate SPSR
    setSPSR(getCPSR());

    // Mode specific LR is set
    if(eType == SWI)
        set(LR, get(PC));
    else if (eType == IRQ)
        set(LR, get(PC) + 4);

    // change the mode bits in the CPSR
    uint CPSR_temp = getCPSR();
    CPSR_temp = CPSR_temp >> 5;
    CPSR_temp = CPSR_temp << 5;
    CPSR_temp |= eType;
    setCPSR(CPSR_temp);

    // disable interrupts
    setFlag(IF, 1);

    // set PC to address of exception handler
    if(eType == SWI)
        set(PC, 0x00000008);
    else if (eType == IRQ)
        set(PC, 0x00000018);

}

QString RegisterBank::regFormatString(unsigned char reg)
{
    switch(reg) {
    case 13:
        return "sp";
    case 14:
        return "lr";
    case 15:
        return "pc";
    default:
        return QString("r%1").arg(QString::number(reg));
    }
}

void RegisterBank::clear()
{ 
    for(int i = 0; i < 16; ++i) {
        set(i, 0);
    }
    resetNZCF();
}

void RegisterBank::resetNZCF() {
    uint NZCF_temp = getCPSR();
    NZCF_temp = NZCF_temp << 4;
    NZCF_temp = NZCF_temp >> 4;
    setCPSR(NZCF_temp);
}

unsigned char RegisterBank::getNZCV()
{
    unsigned char NZCV = getCPSR() >> 28;
    return NZCV;
}



