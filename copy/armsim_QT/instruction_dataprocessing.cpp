/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * instruction_dataprocessing.cpp
 *  Contains the definitions of the methods declared in 'instruction_dataprocessing.cpp'
 * --------------------------------------------------------------------------*/



#include "instruction_dataprocessing.h"

// assigs the Rd, Rn, and operand2 type for the instruction
Instruction_DataProcessing::Instruction_DataProcessing(uint bits, RegisterBank *_regs, Memory *_mem): Instruction(bits, _regs, _mem)
{
    i = (bits & (1 << 25));
    s = (bits & (1 << 20));
    r = (bits & (1 << 22));
    regShiftimm = !(bits & (1 << 4));
    opcode = Memory::ExtractBits(bits, 21, 24) >> 21;

    Rn = Memory::ExtractBits(bits, 16,19) >> 16;
    dest = Memory::ExtractBits(bits, 12, 15) >> 12;
    asm_text = "";

    shifter_op = new Operand2_Immediate(bits, regs, true);
    source1 = 0;
    source2 = 0;

    decode();
    disassemble();
}

/*
 * Method: decode()
 * - calculates the values for source1 and source 2 of the data processing instruction
 * - handles cases for MOV, MVN, ADD, SUB, RSB, MUL, AND, ORR, EOR, BIC
 */
void Instruction_DataProcessing::decode()
{
    // initialize shifter_op as immediate, regshiftimm, or regshiftreg
    decodeOperand2();

    // conditionals to test for which type of operand2 is appropriate
    switch(opcode) {
    //MOV
    case 0b1101:
    // MVN
    case 0b1111:
        source1 = shifter_op->val();
        break;
    // ADD
    case 0b0100:
    // SUB
    case 0b0010:
    // RSB
    case 0b0011:
    // ORR
    case 0b1100:
    // EOR
    case 0b0001:
    // BIC
    case 0b1110:
    // AND or MUL
    case 0b0000:
        //MUL
        if ((Memory::ExtractBits(bits, 4,7) >> 4) == 0b1001) {
            shifter_op = new Operand2_RegShiftReg(bits, regs);
            source1 = ((Operand2_RegShiftReg*)shifter_op)->Rm_val();
            source2 = ((Operand2_RegShiftReg*)shifter_op)->Rs_val();
            dest = Memory::ExtractBits(bits, 16,19) >> 16;
        }
        // ADD (or any other instruction)
        else {
            source1 = regs->readFromReg(Rn);
            source2 = shifter_op->val();
        }
        break;
    // CMP
    case 0b1010:
    // MRS
    case 0b1000:
        source1 = regs->readFromReg(Rn);
        source2 = shifter_op->val();
        break;
    // MSR
    case 0b1001:
    case 0b1011:
        // immediate
        if(i) {
            // shifter_op should be an Operand2_Immediate type
            source1 = shifter_op->val();
        }
        // val from register
        else {
            unsigned char Rm = bits & 0b1111;
            source1 = regs->readFromReg(Rm);
        }
        break;
    default:
        break;
    }
}

/*
 * Method: decodeOperand2()
 * - subclasses the Operand2 parent class appropriately and assigns and instance of that subclass to the shifter_op pointer
 * - supports immediate, reg-shift immediate, and reg-shift reg operand2 types
 */
void Instruction_DataProcessing::decodeOperand2()
{
    ushort bits = Memory::ExtractBits(this->bits, 0,11);
    if(i) {
        shifter_op = new Operand2_Immediate(bits, regs, true);
    }
    else {
        // reg shift imm
        if(regShiftimm) {
            shifter_op = new Operand2_RegShiftImmediate(bits, regs);
        }
        // reg shift reg
        else {
            shifter_op = new Operand2_RegShiftReg(bits, regs);
        }
    }
}

/*
 * Method: disassemble()
 * - generates a formatted string representing the ARM disassembly for the encoded machine instruction
 */
void Instruction_DataProcessing::disassemble()
{
    // first comes appropriate instruction
    switch(opcode) {
    // if instruction is mov, call mov
    // MOV
    case 0b1101:
        asm_text.append("mov");
        if(s)
            asm_text.append("s");
        break;
    // ADD
    case 0b0100:
        asm_text.append("add");
        break;
    // SUB
    case 0b0010:
        asm_text.append("sub");
        break;
    // RSB
    case 0b0011:
        asm_text.append("rsb");
        break;
    // ORR
    case 0b1100:
        asm_text.append("orr");
        break;
    // EOR
    case 0b0001:
        asm_text.append("eor");
        break;
    // BIC
    case 0b1110:
        asm_text.append("bic");
        break;
    // MVN
    case 0b1111:
        asm_text.append("mvn");
        break;
    case 0b0000:
        // MUL
        if ((Memory::ExtractBits(bits, 4,7) >> 4) == 0b1001) {
            asm_text.append("mul");
        }
        // AND
        else {
            asm_text.append("and");
        }
        break;
    // CMP
    case 0b1010:
        if(s)
            asm_text.append("cmp");
        else
            asm_text.append("mrs");
        break;
    case 0b1000:
        asm_text.append(QString("mrs %1, ").arg(RegisterBank::regFormatString(dest)));
        if(r)
            asm_text.append("SPSR");
        else
            asm_text.append("CPSR");
        return;
    // MSR imm & reg
    case 0b1011:
    case 0b1001:
        asm_text.append("msr ");
        if(r)
            asm_text.append("SPSR, ");
        else
            asm_text.append("CPSR, ");
        asm_text.append(QString("%1").arg(RegisterBank::regFormatString(dest)));
        return;
    default:
        break;
    }
    asm_text.append(QString("%1 ").arg(condCode()));

    // next comes destination register
    asm_text.append(QString("%1, ").arg(RegisterBank::regFormatString(dest)));

    // next comes the base register

    // mov & mvn instructions have a special case with shifter_op
    // MUL has special syntax too
    if(opcode == 0b1101 || opcode == 0b1111 || (opcode == 0b0000 && (Memory::ExtractBits(bits, 4,7) >> 4) == 0b1001)) {
        asm_text.append(shifter_op->toString());
        return;
    }

    asm_text.append(QString("%1, ").arg(RegisterBank::regFormatString(Rn)));
    asm_text.append(shifter_op->toString());

}

/*
 * Method: exec()
 * - Calls the appropriate data processing instruction method to calculate or process the data from source1 and source2
 */
void Instruction_DataProcessing::exec()
{
    if(!condPass()) {
        return;
    }

    //cout << "DataP instr: " << QString("%1").arg(bits,8, 16, QChar('0')).toStdString() << endl;
    int result = regs->get(dest);
    switch(opcode) {
    // if instruction is mov, call mov
    case 0b1101:
        result = MOV();
        break;
    case 0b0100:
        result = ADD();
        break;
    case 0b0010:
        result = SUB();
        break;
    case 0b0011:
        result = RSB();
        break;
    case 0b1100:
        result = ORR();
        break;
    case 0b0001:
        result = EOR();
        break;
    case 0b1110:
        result = BIC();
        break;
    case 0b1111:
        result = MVN();
        break;
    case 0b0000:
        // MUL
        if ((Memory::ExtractBits(bits, 4,7) >> 4) == 0b1001) {
            result = MUL();
        }
        // AND
        else {
            result = AND();
        }
        break;
        // CMP
    case 0b1010:
        if(s) {
            CMP();
            // CMP does not change the base register
            result = regs->get(dest);
        }
        // MRS
        else {
            result = MRS();
        }
        break;
        // MRS
    case 0b1000:
        result = MRS();
        break;

        // MSR imm & reg
    case 0b1011:
    case 0b1001:
        MSR();
        break;
    default:
        break;
    }
    setDest(result);
}

/*
 * Method: setDest()
 * - sets the Rd to the processed value
 */
void Instruction_DataProcessing::setDest(uint val)
{
    regs->set(dest, val);
}

uint Instruction_DataProcessing::MOV()
{
    if(s) {
        if(dest == 15) {
            regs->setCPSR(regs->getSPSR());
        }
        else {
            bool N = regs->readFromReg(dest) & (1 << 31);
            bool Z = regs->readFromReg(dest) == 0;
            bool C = shifter_op->shifter_carry_out();
            // V flag unaffected
            regs->setFlag(NF, N);
            regs->setFlag(ZF, Z);
            regs->setFlag(CF, C);
        }
    }

    return source1;
}

uint Instruction_DataProcessing::MRS()
{
    uint val = (r)? regs->getSPSR() : regs->getCPSR();

    return val;
}

//TODO
uint Instruction_DataProcessing::MSR()
{
    //cout << "exec MSR"  <<  endl;
    unsigned char field_mask = Rn;
    uint byte_mask = 0x0;
    if(field_mask & (1))
        byte_mask |= 0x000000FF;
    if(field_mask & (1 << 1))
        byte_mask |= 0x0000FF00;
    if(field_mask & (1 << 2))
        byte_mask |= 0x00FF0000;
    if(field_mask & (1 << 3))
        byte_mask |= 0xFF000000;

    if(r == 0) {
        regs->setCPSR((regs->getCPSR() & !byte_mask) | (source1 & byte_mask));
    }
    else  {
        if(regs->curMode() != SYS) {
            regs->setSPSR((regs->getSPSR() & !byte_mask) | (source1 & byte_mask));
        }
    }



    return 0;
}

uint Instruction_DataProcessing::MVN()
{
    return ~source1;
}

uint Instruction_DataProcessing::ADD()
{
    return source1 + source2;
}

uint Instruction_DataProcessing::SUB()
{
    //cout << "result = " << QString("%1").arg(source1 - source2, 8,16,QChar('0')).toStdString() << endl;
    return source1 - source2;
}

uint Instruction_DataProcessing::RSB()
{
    return source2 - source1;
}

uint Instruction_DataProcessing::MUL()
{
    return source1 * source2;
}

uint Instruction_DataProcessing::AND()
{
    return source1 & source2;
}

uint Instruction_DataProcessing::ORR()
{
    return source1 | source2;
}

uint Instruction_DataProcessing::EOR()
{
    return source1 ^ source2;
}

uint Instruction_DataProcessing::BIC()
{
    return source1 & ~source2;
}

uint Instruction_DataProcessing::CMP() 
{
    uint result = source1 - source2;

    bool N = result & (1 << 31);
    bool Z = (result == 0) ? 1 : 0;
    bool C = (source2 <= source1) ? 1 : 0;

    uint msb = 1 << 31;
    bool V = (((source1 & msb) != (source2 & msb)) && ((source1 & msb) != (result & msb)));

    regs->setFlag(NF, N);
    regs->setFlag(ZF, Z);
    regs->setFlag(CF, C);
    regs->setFlag(VF, V);

    return 0;
}
