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
		case 0x69: { ADC(READ8(EA_IMM));	break; }
		case 0x65: { ADC(READ8(EA_ZP));		break; }
		case 0x75: { ADC(READ8(EA_ZP_X));	break; }
		case 0x6D: { ADC(READ8(EA_ABS));	break; }
		case 0x7D: { ADC(READ8(EA_ABS_X));	break; }
		case 0x79: { ADC(READ8(EA_ABS_Y));	break; }
		case 0x61: { ADC(READ8(EA_IND_X));	break; }
		case 0x71: { ADC(READ8(EA_IND_Y));	break; }

		// AND
		case 0x29: { AND(READ8(EA_IMM));	break; }
		case 0x25: { AND(READ8(EA_ZP));		break; }
		case 0x35: { AND(READ8(EA_ZP_X));	break; }
		case 0x2D: { AND(READ8(EA_ABS));	break; }
		case 0x3D: { AND(READ8(EA_ABS_X));	break; }
		case 0x39: { AND(READ8(EA_ABS_Y));	break; }
		case 0x21: { AND(READ8(EA_IND_X));	break; }
		case 0x31: { AND(READ8(EA_IND_Y));	break; }

		// ASL
		case 0x0A: { ASL_ACC();		break; }
		case 0x06: { ASL(EA_ZP);	break; }
		case 0x16: { ASL(EA_ZP_X);	break; }
		case 0x0E: { ASL(EA_ABS);	break; }
		case 0x1E: { ASL(EA_ABS_X);	break; }

		// BIT
		case 0x24: { BIT(READ8(EA_ZP));		break; }
		case 0x2C: { BIT(READ16(EA_ABS));	break; }

		// Branching
		case 0x10: { BRANCH(!(flags & FLAG_SIGN));	break; }
		case 0x30: { BRANCH(flags & FLAG_SIGN);		break; }
		case 0x50: { BRANCH(!(flags & FLAG_OVER));	break; }
		case 0x70: { BRANCH(flags & FLAG_OVER);		break; }
		case 0x90: { BRANCH(!(flags & FLAG_CARRY));	break; }
		case 0xB0: { BRANCH(flags & FLAG_CARRY);	break; }
		case 0xD0: { BRANCH(!(flags & FLAG_ZERO));	break; }
		case 0xF0: { BRANCH(flags & FLAG_ZERO);		break; }

		// Clear flags
		case 0x18: { FLAG_CLEAR(FLAG_CARRY);		break; }
		case 0xD8: { FLAG_CLEAR(FLAG_DEC);		break; }
		case 0x58: { FLAG_CLEAR(FLAG_INTR);		break; }
		case 0xB8: { FLAG_CLEAR(FLAG_OVER);		break; }

		// CMP
		case 0xC9: { CMP(READ8(EA_IMM));		break; }
		case 0xC5: { CMP(READ8(EA_ZP));			break; }
		case 0xD5: { CMP(READ8(EA_ZP_X));		break; }
		case 0xCD: { CMP(READ8(EA_ABS));		break; }
		case 0xDD: { CMP(READ8(EA_ABS_X));		break; }
		case 0xD9: { CMP(READ8(EA_ABS_Y));		break; }
		case 0xC1: { CMP(READ8(EA_IND_X));		break; }
		case 0xD1: { CMP(READ8(EA_IND_Y));		break; }


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
