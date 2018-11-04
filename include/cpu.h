#ifndef __CPU_H__
#define __CPU_H__

#include <cstdint>
#include "memory.h"

class CPU {
	private:
		/* CPU Registers */
		uint8_t a;
		uint8_t x;
		uint8_t y;

		uint16_t pc;
		uint16_t sp;

		uint8_t flags;

	public:

		/* 2KB internal RAM */
		uint8_t ram[2048];

		/* Methods */
		void decode(const uint8_t &opcode);
		uint8_t cpu_read(const uint16_t &addr);
		void cpu_write(const uint16_t &addr, const uint8_t &data);
		void dump_reg();
};

#endif
