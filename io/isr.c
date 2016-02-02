/**
 * isr.c -- higher lever interrupt service routines and interrupt request handlers.
 */

#include "isr.h"
#include "../util/common.h"

/**
 * temporary display of isr
 */
void isr_handler(registers_t regs)
{
	u32int ino = regs.error_code;	
	char str[20] = "\ninterrupt no: ";	

	print(str);
	print_dec((int)ino);

	return;
}
