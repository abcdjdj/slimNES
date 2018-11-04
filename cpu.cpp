#include <cstdio>
#include <cstdlib>
#include "cpu.h"
#include "macro.h"

uint8_t CPU::cpu_read(const uint16_t &addr)
{
	printf("Reading addr 0x%x\n", addr);
	if (addr <= 0x1FFF)
		return ram[addr % 0x800];
	else
		return 0; /* TODO : Other peripherals */
}

void CPU::cpu_write(const uint16_t &addr, const uint8_t &data)
{
	/* TODO : Implement memory access to all 64 KB */
	printf("Writing data=%x to addr 0x%x\n", data, addr);
	if (addr <= 0x1FFF)
		ram[addr % 0x800] = data;
	else
		return; /* TODO : Other peripherals */
}

void CPU::decode(const uint8_t &opcode)
{
	switch(opcode) {
		// ADC
		case 0x69: { ADC(READ8(EA_IMM));	pc += 2;	break; }
		case 0x65: { ADC(READ8(EA_ZP));		pc += 2;	break; }
		case 0x75: { ADC(READ8(EA_ZP_X));	pc += 2;	break; }
		case 0x6D: { ADC(READ8(EA_ABS));	pc += 3;	break; }
		case 0x7D: { ADC(READ8(EA_ABS_X));	pc += 3;	break; }
		case 0x79: { ADC(READ8(EA_ABS_Y));	pc += 3;	break; }
		case 0x61: { ADC(READ8(EA_IND_X));	pc += 2;	break; }
		case 0x71: { ADC(READ8(EA_IND_Y));	pc += 2;	break; }

		// AND
		case 0x29: { AND(READ8(EA_IMM));	pc += 2;	break; }
		case 0x25: { AND(READ8(EA_ZP));		pc += 2;	break; }
		case 0x35: { AND(READ8(EA_ZP_X));	pc += 2;	break; }
		case 0x2D: { AND(READ8(EA_ABS));	pc += 3;	break; }
		case 0x3D: { AND(READ8(EA_ABS_X));	pc += 3;	break; }
		case 0x39: { AND(READ8(EA_ABS_Y));	pc += 3;	break; }
		case 0x21: { AND(READ8(EA_IND_X));	pc += 2;	break; }
		case 0x31: { AND(READ8(EA_IND_Y));	pc += 2;	break; }

		// ASL
		case 0x0A: { ASL_ACC();		pc += 1;	break; }
		case 0x06: { ASL(EA_ZP);	pc += 2;	break; }
		case 0x16: { ASL(EA_ZP_X);	pc += 2;	break; }
		case 0x0E: { ASL(EA_ABS);	pc += 3;	break; }
		case 0x1E: { ASL(EA_ABS_X);	pc += 3;	break; }

		// BIT
		case 0x24: { BIT(READ8(EA_ZP));		pc += 2;	break; }
		case 0x2C: { BIT(READ16(EA_ABS));	pc += 3;	break; }

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
		case 0x18: { FLAG_CLEAR(FLAG_CARRY);	pc += 1;	break; }
		case 0xD8: { FLAG_CLEAR(FLAG_DEC);	pc += 1;	break; }
		case 0x58: { FLAG_CLEAR(FLAG_INTR);	pc += 1;	break; }
		case 0xB8: { FLAG_CLEAR(FLAG_OVER);	pc += 1;	break; }

		// CMP
		case 0xC9: { COMPARE(READ8(EA_IMM), a);		pc += 2;	break; }
		case 0xC5: { COMPARE(READ8(EA_ZP), a);		pc += 2;	break; }
		case 0xD5: { COMPARE(READ8(EA_ZP_X), a);	pc += 2;	break; }
		case 0xCD: { COMPARE(READ8(EA_ABS), a);		pc += 3;	break; }
		case 0xDD: { COMPARE(READ8(EA_ABS_X), a);	pc += 3;	break; }
		case 0xD9: { COMPARE(READ8(EA_ABS_Y), a);	pc += 3;	break; }
		case 0xC1: { COMPARE(READ8(EA_IND_X), a);	pc += 2;	break; }
		case 0xD1: { COMPARE(READ8(EA_IND_Y), a);	pc += 2;	break; }

		// CPX
                case 0xE0: { COMPARE(READ8(EA_IMM), x);	pc += 2;	break; }
                case 0xE4: { COMPARE(READ8(EA_ZP), x);	pc += 2;	break; }
                case 0xEC: { COMPARE(READ8(EA_ABS), x);	pc += 3;	break; }

                // CPY
                case 0xC0: { COMPARE(READ8(EA_IMM), y);	pc += 2;	break; }
                case 0xC4: { COMPARE(READ8(EA_ZP), y);	pc += 2;	break; }
                case 0xCC: { COMPARE(READ8(EA_ABS), y);	pc += 3;	break; }

		// DEC
		case 0xC6: { DEC(EA_ZP);	pc += 2;	break; }
		case 0xD6: { DEC(EA_ZP_X);	pc += 2;	break; }
		case 0xCE: { DEC(EA_ABS);	pc += 3;	break; }
		case 0xDE: { DEC(EA_ABS_X);	pc += 3;	break; }

		// DEX, DEY
		case 0xCA: { DEC_REG(x);	pc += 1;	break; }
		case 0x88: { DEC_REG(y);	pc += 1;	break; }

		// EOR
		case 0x49: { EOR(READ8(EA_IMM));	pc += 2;	break; }
		case 0x45: { EOR(READ8(EA_ZP));		pc += 2;	break; }
		case 0x55: { EOR(READ8(EA_ZP_X));	pc += 2;	break; }
		case 0x4D: { EOR(READ8(EA_ABS));	pc += 3;	break; }
		case 0x5D: { EOR(READ8(EA_ABS_X));	pc += 3;	break; }
		case 0x59: { EOR(READ8(EA_ABS_Y));	pc += 3;	break; }
		case 0x41: { EOR(READ8(EA_IND_X));	pc += 2;	break; }
		case 0x51: { EOR(READ8(EA_IND_Y));	pc += 2;	break; }

		// INC
		case 0xE6: { INC(EA_ZP);	pc += 2;	break; }
		case 0xF6: { INC(EA_ZP_X);	pc += 2;	break; }
		case 0xEE: { INC(EA_ABS);	pc += 3;	break; }
		case 0xFE: { INC(EA_ABS_X);	pc += 3;	break; }

		// INX, INY
		case 0xE8: { INC_REG(x);	pc += 1;	break; }
		case 0xC8: { INC_REG(y);	pc += 1;	break; }

		// JMP
		case 0x4C: { pc = READ16(EA_ABS);	break; }
		case 0x6C: { pc = READ16(EA_IND);	break; }

		// JSR
		case 0x20: { JSR(READ16(EA_IMM));	break; }

		// LDA
		case 0xA9: { LD_REG(READ8(EA_IMM), a);		pc += 2;	break; }
		case 0xA5: { LD_REG(READ8(EA_ZP), a);		pc += 2;	break; }
		case 0xB5: { LD_REG(READ8(EA_ZP_X), a);		pc += 2;	break; }
		case 0xAD: { LD_REG(READ8(EA_ABS), a);		pc += 3;	break; }
		case 0xBD: { LD_REG(READ8(EA_ABS_X), a);	pc += 3;	break; }
		case 0xB9: { LD_REG(READ8(EA_ABS_Y), a);	pc += 3;	break; }
		case 0xA1: { LD_REG(READ8(EA_IND_X), a);	pc += 2;	break; }
		case 0xB1: { LD_REG(READ8(EA_IND_Y), a);	pc += 2;	break; }

		// LDX
		case 0xA2: { LD_REG(READ8(EA_IMM), x);		pc += 2;	break; }
		case 0xA6: { LD_REG(READ8(EA_ZP), x);		pc += 2;	break; }
		case 0xB6: { LD_REG(READ8(EA_ZP_Y), x);		pc += 2;	break; }
		case 0xAE: { LD_REG(READ8(EA_ABS), x);		pc += 3;	break; }
		case 0xBE: { LD_REG(READ8(EA_ABS_Y), x);	pc += 3;	break; }

		// LDY
		case 0xA0: { LD_REG(READ8(EA_IMM), y);		pc += 2;	break; }
		case 0xA4: { LD_REG(READ8(EA_ZP), y);		pc += 2;	break; }
		case 0xB4: { LD_REG(READ8(EA_ZP_X), y);		pc += 2;	break; }
		case 0xAC: { LD_REG(READ8(EA_ABS), y);		pc += 3;	break; }
		case 0xBC: { LD_REG(READ8(EA_ABS_X), y);	pc += 3;	break; }


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
