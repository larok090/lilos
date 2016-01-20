/**
 *	isr.h:
 *		structs for high level interrupt service routines (ISR).
 */
#include "../util/common.h"

typedef struct registers
{
	u32int ds;			// Data segment selector
	u32int edi, esi, ebp, ebx, edx, ecx, eax;	// pushed using push a in interrupt.s
	u32int int_no, error_code;			//Interrupt number and error code (if not 0)
	u32int eip, cs, eflags, useresp, ss;	// Pushed by the processor automatically.
}	registers_t;

void isr_handler(registers_t);
