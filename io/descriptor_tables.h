/* This is following the GDT chapter from www.jamesmolloy.co.uk
 * -> tutorial on GDT  (chapter 4)
 *
 * @author www.jamesmolloy.co.uk
 */
#ifndef INCLUDE_DESC_TABLES_H
#define INCLUDE_DESC_TABLES_H

/* Move to a common.h type file [12/22/15 OB]*/
#ifndef SHORT_TYPE_DECL

#define u8int 	unsigned char 	
#define u16int 	unsigned short
#define u32int 	unsigned int
#define s32int 	long

#endif

/**
 * Struct gdt - global descriptor table 
 * 	struct for loading the global descriptor table
 * 	into the processor
 *  packed for keeping the exact number of bytes 
 * 	always allocated to each instance
 */
struct gdt_ptr_struct
{
	u16int 	limit;			// The upper 16 bits of all selector limits
	u32int 	base;			// The address of the first gdt_entry_t struct
}__attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;

struct gdt_entry_struct
{
	u16int	limit_low;		// The lower 16 bits of the limit
	u16int	base_low;		// The lower 16 bits of the base
	u8int	base_middle;	// The next 8 bits of the base.
	u8int	access;			// Access flags ( user / os mode bit)
	u8int	granularity;
	u8int 	base_high;		// The last 8 bits of the base.
}__attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;

void init_descriptor_tables();

#endif /* INCLUDE_DESC_TABLES_H */
