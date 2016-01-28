/**
 *
 * isr.c -- higher lever interrupt service routines and interrupt request handlers.
 */

#include "isr.h"
#include "io.h"
#include "../util/common.h"

/**
 * temporary display of isr
 */
void isr_handler(registers_t regs)
{
	screen_clear();

	u32int ino = regs.error_code;	
	char str[8] = "int no: ";	

	kprint(str);
	kprint_dec(ino);

	return;
}
