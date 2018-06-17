#include <cstdio>
#include <cstdlib>
#include "cpu.h"
#include "memory.h"
#include "macro.h"

CPU::CPU()
{
/*	this->ram = new uint8_t[2048];
	this->a = 5;
	this->x = 0x60;
	pc = 0x50;
	ram[0x20] = 22;
	ram[pc+1] = 0xC0; */
}

CPU::~CPU()
{
	delete this->ram;
}

void CPU::set_memory_link(Memory *mem)
{
	this->memory = mem;
}

void CPU::decode(const uint8_t &opcode)
{
	switch(opcode) {
		// ADC
		case 0x69: { ADC(OPERAND_IMM_8);	break; }
		case 0x65: { ADC(OPERAND_ZP);		break; }
		case 0x75: { ADC(OPERAND_ZP_X);		break; }
		case 0x6D: { ADC(OPERAND_ABS);		break; }
		case 0x7D: { ADC(OPERAND_ABS_X);	break; }
		case 0x79: { ADC(OPERAND_ABS_Y);	break; }
		case 0x61: { ADC(OPERAND_IND_X);	break; }
		case 0x71: { ADC(OPERAND_IND_Y);	break; }

		// AND
		case 0x29: { AND(OPERAND_IMM_8);	break; }
		case 0x25: { AND(OPERAND_ZP);		break; }
		case 0x35: { AND(OPERAND_ZP_X);		break; }
		case 0x2D: { AND(OPERAND_ABS);		break; }
		case 0x3D: { AND(OPERAND_ABS_X);	break; }
		case 0x39: { AND(OPERAND_ABS_Y);	break; }
		case 0x21: { AND(OPERAND_IND_X);	break; }
		case 0x31: { AND(OPERAND_IND_Y);	break; }

		default: printf("Unknown opcode %x\n", opcode);
	}
}

void CPU::dump_reg()
{
	printf("************* REG DUMP **************\n");
	printf("A : %d\n", a);
	printf("X : %d\n", x);
	printf("Y : %d\n", y);

	printf("P : 0x%x\n", flags);

	printf("PC : %d\n", pc);
	printf("SP : %d\n", sp);

	printf("*************************************\n\n\n");
}
