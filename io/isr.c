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
	char s[6] = "int ";
	
	if(ino == 3)
		s[5] = '3';
	if(ino == 4){
		s[5] = '4';
	}
	else{
		s[5] = '0';
	}

	write(s, 6);	

	return;
}
