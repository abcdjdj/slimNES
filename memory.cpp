#include "cpu.h"

Memory::Memory(CPU *cpu)
{
	this->cpu = cpu;
}

uint8_t Memory::cpu_mmap_read(uint16_t addr)
{
	if (addr <= 0x1FFF)
		return cpu->ram[addr % 0x800];
	else
		return 0; /* TODO : Other peripherals */
}

void Memory::cpu_mmap_write(uint16_t addr, uint8_t data)
{
	/* TODO : Implement memory access to all 64 KB */
	if (addr <= 0x1FFF)
		cpu->ram[addr & 0x800] = data;
	else
		return; /* TODO : Other peripherals */
}
