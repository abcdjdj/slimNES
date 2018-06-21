/* Flag masks */
#define FLAG_CARRY (0x01)
#define FLAG_ZERO  (0x02)
#define FLAG_INTR  (0x04)
#define FLAG_DEC   (0x08)
#define FLAG_BRK   (0x10)
#define FLAG_OVER  (0x40)
#define FLAG_SIGN  (0x80)

/* Flag register manipulation */
#define FLAG_SET(mask) { flags |= mask; }
#define FLAG_CLEAR(mask) { flags &= ~mask; }
#define FLAG_CONDITION(cond, mask) do {\
	if (cond) {\
		FLAG_SET(mask);\
	} else {\
		FLAG_CLEAR(mask);\
	}\
} while(0)

#define READ8(addr) (memory->cpu_mmap_read(addr))
#define READ16(addr) ((READ8((addr) + 1) << 8) | READ8(addr))
#define WRITE8(addr, data) (memory->cpu_mmap_write(addr, data))

/* Addressing modes (effective addresses) */
#define EA_PC_RELATIVE(offset) (pc + (offset))
#define EA_IMM (EA_PC_RELATIVE(1))

#define EA_ZP (READ8(EA_IMM))
#define EA_ZP_X ((x + READ8(EA_IMM)) & 0xFF)

#define EA_ABS (READ16(EA_IMM))
#define EA_ABS_X (x + READ16(EA_IMM))
#define EA_ABS_Y (y + READ16(EA_IMM))

#define EA_IND (READ16(EA_IMM))
#define EA_IND_X (READ16((x + READ8(EA_IMM)) & 0xFF))
#define EA_IND_Y (READ16(READ8(EA_IMM)) + y)

/* ADC */
#define ADC(__valexpr) do {\
	uint8_t operand = __valexpr;\
	printf("ADC Operand = %d\n", operand);\
	uint16_t ans = a + operand + (flags & 0x01);\
	FLAG_CONDITION(ans & 0x100, FLAG_CARRY);\
	FLAG_CONDITION(((a ^ ans) & (operand ^ ans) & 0x80), FLAG_OVER);\
	FLAG_CONDITION(ans & 0x80, FLAG_SIGN);\
	FLAG_CONDITION(ans == 0, FLAG_ZERO);\
	a = ans & 0xFF;\
	pc += 2;\
} while(0)

/* AND */
#define AND(__valexpr) do {\
	uint8_t operand = __valexpr;\
	printf("AND Operand = %d\n", operand);\
	a &= operand;\
	FLAG_CONDITION(a == 0, FLAG_ZERO);\
	FLAG_CONDITION(a & 0x80, FLAG_SIGN);\
	pc += 2;\
} while(0)

/* ASL */
#define ASL(__ea_expr) do {\
	uint16_t addr = __ea_expr;\
	uint8_t operand = READ8(addr);\
	printf("ASL Operand = %d\n", operand);\
	FLAG_CONDITION(operand & 0x80, FLAG_CARRY);\
	operand <<= 1;\
	FLAG_CONDITION(operand & 0x80, FLAG_SIGN);\
	FLAG_CONDITION(operand == 0, FLAG_ZERO);\
	WRITE8(addr, operand);\
} while(0)

#define ASL_ACC() do {\
	FLAG_CONDITION(a & 0x80, FLAG_CARRY);\
	a <<= 1;\
	FLAG_CONDITION(a & 0x80, FLAG_SIGN);\
	FLAG_CONDITION(a == 0, FLAG_ZERO);\
} while(0)

/* BIT */
#define BIT(__valexpr) do {\
	uint8_t operand = __valexpr;\
	FLAG_CONDITION((a & operand) == 0, FLAG_ZERO);\
	flags = (flags & 0x3F) | (operand & 0xC0);\
} while(0)

/* Branching */
/* TODO : Compiler specific behaviour during uint8 to int8 conversion */
#define BRANCH(cond) do {\
	if(cond) {\
		pc += 2 + (int8_t)READ8(EA_IMM);\
		printf("PC set to 0x%x\n", pc);\
	}\
} while(0)
