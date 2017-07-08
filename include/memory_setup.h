#ifndef MEMORY_SETUP
#define MEMORY_SETUP
	extern void load_gdt(unsigned int gdt_address);
	struct gdt
	{
		int address;
		short size;
	}__attribute__((packed))
#endif
