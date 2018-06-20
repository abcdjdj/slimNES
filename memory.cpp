#include "cpu.h"
#include <cstdio>

Memory::Memory(CPU *cpu)
{
	this->cpu = cpu;
}

uint8_t Memory::cpu_mmap_read(uint16_t addr)
{
	printf("Reading addr 0x%x\n", addr);
	if (addr <= 0x1FFF)
		return cpu->ram[addr % 0x800];
	else
		return 0; /* TODO : Other peripherals */
}

void Memory::cpu_mmap_write(uint16_t addr, uint8_t data)
{
	/* TODO : Implement memory access to all 64 KB */
	printf("Writing data=%x to addr 0x%x\n", data, addr);
	if (addr <= 0x1FFF)
		cpu->ram[addr % 0x800] = data;
	else
		return; /* TODO : Other peripherals */
}
