/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * instruction_loadstore.cpp
 *  Contains the definitions of the methods declared in 'instruction_loadstore.cpp'
 * --------------------------------------------------------------------------*/

#include "instruction_loadstore.h"


// only implementing pre-indexing for now
Instruction_LoadStore::Instruction_LoadStore(uint bits, RegisterBank *regs, Memory *mem): Instruction(bits, regs, mem)
{
    instrType = Memory::ExtractBits(bits, 25, 27) >> 25;

    // i flag is the 25th bit
    i = bits & (1<<25);
    // set PUBWL flags
    p = bits & (1<<24);
    u = bits & (1<<23);
    b = bits & (1<<22);
    w = bits & (1<<21);
    l = bits & (1<<20);

    Rd = Memory::ExtractBits(this->bits, 12, 15) >> 12;
    Rn = Memory::ExtractBits(this->bits, 16, 19) >> 16;

    eff_address = 0;
    reglist = vector<unsigned char>();

    decode();
    disassemble();
}

// loads from memory or stores into memory depending on the L flag
void Instruction_LoadStore::exec()
{
    if(!condPass()) {
        // execute nop
        return;
    }

    //cout << "ldr/str instr: " << QString("%1").arg(bits,8, 16, QChar('0')).toStdString() << endl;

    switch(instrType) {
    case 0b010:
    case 0b011:
        // load into destination register from eff_address in  memory
        if(l) {
            load();
        }
        // store into eff_address the value in rd
        else {
            store();
        }
        break;
    case 0b100:
        if (l) {
            ldmfd();
        }
        else {
            stmfd();
        }
        break;
    }
}

/*
 * Method: decode()
 * - compute effective address from source/destination register or base register, depending on L flag
 */
void Instruction_LoadStore::decode()
{
    // ldr/str
    if(instrType == 0b010 || instrType == 0b011) {
        //cout << "ldr/str" << endl;
        decodeOperand2();
        computeEA();
    }
    // ldmia/stmia
    else {
        ushort rList = Memory::ExtractBits(bits, 0, 15);
        // check register list for the set registers
        for(int i = 0; i < 16; i++) {
            if(rList & (1 << i)) {
                reglist.push_back(i);
            }
        }
        //cout << "ldm/stm" << endl;
    }
}

/*
 * Method: decodeOperand2()
 * - subclasses the Operand2 parent class appropriately and assigns and instance of that subclass to the shifter_op pointer
 * - supports immediate, reg-shift immediate
 */
void Instruction_LoadStore::decodeOperand2()
{
    ushort bits0_11 = Memory::ExtractBits(bits, 0,11);
    // 12-bit immediate
    if(i == 0) {
        offset = new Operand2_Immediate(bits0_11, regs, false);
    }
    else {
        offset = new Operand2_RegShiftImmediate(bits0_11, regs);
    }
}

/*
 * Method: computeEA()
 * - computes the effective address of the instruction and sets the eff-address instance variable
 */
void Instruction_LoadStore::computeEA()
{
    // pre-indexed
    if (p) {
        uint valRn = regs->readFromReg(Rn);
        // if u=1, offset is positive, otherwise negative
        int offset_val = (u) ? offset->val() : offset->val() * -1;

        eff_address = valRn + offset_val;
        //cout << "eff_addr = " << eff_address << endl;
    }
}

/*
 * Method: load()
 * - performs a LDR with the instance variables set by the decode method
 */
void Instruction_LoadStore::load()
{
    //cout << "load" << endl;
    int valFromMemory;
    // ldrb
    if(b) {
        //cout << "exec ldrb instr" << endl;
        valFromMemory = mem->ReadByte(eff_address);
    }
    else {
        //cout << "exec ldr instr" << endl;
        valFromMemory = mem->ReadWord(eff_address);
    }
    regs->set(Rd, valFromMemory);

    if(w) {
        regs->set(Rn, eff_address);
    }

    reglist = vector<unsigned char>();
}

/*
 * Method: store()
 * - performs a STR with the instance variables set by the decode method
 */
void Instruction_LoadStore::store()
{
    //cout << "store" << endl;
    if(b) {
        //cout << "exec strb instr" << endl;
        unsigned char byte = regs->readFromReg(Rd);
        //cout << "byte: " << 0+byte << endl;
        mem->WriteByte(eff_address, byte);
    }
    else {
        //cout << "exec str instr" << endl;
        uint valAtRd = regs->readFromReg(Rd);
        mem->WriteWord(eff_address, valAtRd);
    }
    if(w) {
        regs->set(Rn, eff_address);
    }
}

/*
 * Method: LDMFD
 * - performs a LDMFD with the instance variables set by the decode method
 */
void Instruction_LoadStore::ldmfd()
{
    //cout << "ldmfd" << endl;
    uint RnVal_temp = regs->readFromReg(Rn);
    //cout << "r" << QString("%1").arg(Rn).toStdString() << " = " << QString("%1").arg(RnVal_temp, 0, 16, QChar('0')).toStdString() << endl;
    // iterate from back to front
    for(auto i = reglist.begin(); i != reglist.end(); ++i) {
        uint valAtMem = mem->ReadWord(RnVal_temp);
        regs->set(*i, valAtMem);

        RnVal_temp += 4;
    }
    if(w) {
        regs->set(Rn, RnVal_temp);
    }
}

/*
 * Method: STMFD
 * - performs a STMFD with the instance variables set by the decode method
 */
void Instruction_LoadStore::stmfd()
{
    //cout << "stmfd" << endl;
    uint RnVal_temp = regs->get(Rn);

    // push the values in regList from back to front
    for(vector<unsigned char>::reverse_iterator i = reglist.rbegin(); i != reglist.rend(); ++i) {
        RnVal_temp -= 4;
        uint valAtReg = regs->get(*i);
        mem->WriteWord(RnVal_temp, valAtReg);
    }
    if(w) {
        if(RnVal_temp < 0) {
            cout << "setting stack pointer to value less than 0:" << QString("%1").arg(RnVal_temp, 8, 16, QChar('0')).toStdString() << endl;
        }
        regs->set(Rn, RnVal_temp);
    }
}

/*
 * Method: isRegListContinuous
 * - determines if the reglist given in a ldm or stm instr is a continuous list or not
 */
bool Instruction_LoadStore::isReglistContinuous()
{
    if(reglist.size() <= 2)
        return false;
    for(int i = 1; i < reglist.size(); i++) {
        if(reglist.at(i-1) != reglist.at(i) - 1)
            return false;
    }
    return true;
}

/* Method: disassemble()
 * - generates a formatted string representing the ARM disassembly for the encoded machine instruction
 */
void Instruction_LoadStore::disassemble()
{
    // ldm/stm
    if(instrType == 0b100) {
        if(l) {
            asm_text = "ldmfd ";
        }
        else {
            asm_text = "stmfd ";
        }

        asm_text.append(RegisterBank::regFormatString(Rn));
        if(w)
            asm_text.append("!");
        asm_text.append(", {");
        if(isReglistContinuous()) {
            asm_text.append(QString("%1-%2").arg(RegisterBank::regFormatString(*reglist.begin()), RegisterBank::regFormatString(*(reglist.end()-1))));
        }
        else {
            asm_text.append(QString("%1").arg(RegisterBank::regFormatString(*reglist.begin())));
            for(int i = 1; i < reglist.size(); i++) {
                asm_text.append(QString(", %1").arg(RegisterBank::regFormatString(reglist.at(i))));
            }
        }
        asm_text.append("}");

    }
    // ldr/str
    else {
        if(l) {
            asm_text = "ldr";
        }
        else {
            asm_text = "str";
        }
        if(b)
            asm_text.append("b ");
        else
            asm_text.append(" ");

        asm_text.append(QString("%1, [").arg(RegisterBank::regFormatString(Rd)));
        asm_text.append(QString("%1").arg(RegisterBank::regFormatString(Rn)));
        // preindex
        if(p) {
            if(dynamic_cast<Operand2_Immediate*>(offset) != nullptr && offset->val() == 0) {
                asm_text.append("]");
                return;
            }
            asm_text.append(", ");
            if(i == 0)
                asm_text.append("#");

            // handle negative offsets
            if(u == 0)
                asm_text.append("-");
            if(i == 0)
                asm_text.append(QString::number(offset->val()));
            else {
                asm_text.append(offset->toString());
            }
            asm_text.append("]");

            if(w)
                asm_text.append("!");
        }
    }
}
