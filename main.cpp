#include <cstdio>
#include "cpu.h"

int main(void)
{
	/* Initialization */
	CPU cpu;

	cpu.dump_reg();
	cpu.decode(0x75);
	cpu.dump_reg();

	return 0;
}
