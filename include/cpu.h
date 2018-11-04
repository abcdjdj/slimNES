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

		/* CPU memory interfacing */
		Memory *memory;

	public:
		/* Constructor & Destructor */
		CPU();
		~CPU();

		/* 2KB internal RAM */
		uint8_t *ram;

		/* Methods */
		void decode(const uint8_t &opcode);
		void set_memory_link(Memory *mem);
		void dump_reg();
};

#endif
