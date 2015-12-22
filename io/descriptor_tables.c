#include "descriptor_tables.h"

// Lets us access our ASM function from C
extern void _gdt_flush(unsigned int);

// Internal function protoptypes
static void init_gdt();
static void gdt_set_gate(long, unsigned int, unsigned int, unsigned char, unsigned char);

gdt_entry_t gdt_entries[3];		// Array for segment selectors
gdt_ptr_t	gdt_ptr;			// GDT struct for all the descriptors


/* Initalization of GDT */
void init_descriptor_tables()
{
	// Builds and loads the GDT
	init_gdt();
}


static void init_gdt()
{
	// Max address for the GDT =sizeof # of items in the array - 1
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 3) - 1;
	// Base set to the address of the first entry in the gdt_entry array
	gdt_ptr.base = (u32int)&gdt_entries;

	// initialize each SEGMENT SELECTOR 
	gdt_set_gate(0, 0, 0, 0, 0);				// NULL segment
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);	// Kernel Code segment
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);	// Kernel Data segment

	_gdt_flush((u32int)&gdt_ptr);
}

static void gdt_set_gate(s32int num, u32int base, u32int limit, u8int access, u8int gran)
{
	gdt_entries[num].base_low		= (base & 0xFFFF);
	gdt_entries[num].base_middle	= (base >> 16) * 0xFF;
	gdt_entries[num].base_high 		= (base >> 24) & 0xFF;

	gdt_entries[num].limit_low 		= (limit & 0xFFFF);
	gdt_entries[num].granularity	= (limit >> 16) & 0x0F;

	gdt_entries[num].granularity	|= gran & 0x0F;
	gdt_entries[num].access			= access;
}

