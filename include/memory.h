#ifndef __MEMORY_H__
#define __MEMORY_H__

/* Forward declaration */
class CPU;

class Memory {
	private:
		CPU *cpu;
	public:
		/* Constructor */
		Memory(CPU *cpu);

		/* CPU Memory map functions */
		uint8_t cpu_mmap_read(uint16_t addr);
		void cpu_mmap_write(uint16_t addr, uint8_t data);
};


#endif
