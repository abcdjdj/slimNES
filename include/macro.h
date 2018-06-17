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

/* Addressing modes */
#define PC_RELATIVE(offset) (memory->cpu_mmap_read(pc + (offset)))
#define OPERAND_IMM_8 (PC_RELATIVE(1))
#define OPERAND_IMM_16 ((PC_RELATIVE(2) << 8) | PC_RELATIVE(1))
#define OPERAND_ZP (memory->cpu_mmap_read(OPERAND_IMM_8))
#define OPERAND_ZP_X (memory->cpu_mmap_read((OPERAND_IMM_8 + x) & 0xFF))
/* Little Endian!! */
#define OPERAND_ABS (memory->cpu_mmap_read(OPERAND_IMM_16))
#define OPERAND_ABS_X (memory->cpu_mmap_read((OPERAND_IMM_16 + x)))
#define OPERAND_ABS_Y (memory->cpu_mmap_read((OPERAND_IMM_16 + y)))

/* Warning : OPERAND_IND results in a 16 bit result */
/* TODO : Optimize performance by caching intermediate values */
#define OPERAND_IND ((memory->cpu_mmap_read(OPERAND_IMM_16 + 1) << 8)\
			| (memory->cpu_mmap_read(OPERAND_IMM_16)))

#define OPERAND_IND_X (memory->cpu_mmap_read(((memory->cpu_mmap_read((x + OPERAND_IMM_8 + 1) & 0xFF)) << 8)\
			| (memory->cpu_mmap_read((x + OPERAND_IMM_8) & 0xFF))))
#define OPERAND_IND_Y (memory->cpu_mmap_read(\
			((memory->cpu_mmap_read(OPERAND_IMM_8 + 1) << 8)\
			| (memory->cpu_mmap_read(OPERAND_IMM_8))) + y))

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
