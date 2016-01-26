/***************************************************************************\
 *
 * 			kmain.c - The entry C code to the OS
 *
 \**************************************************************************/
#include "io/io.h"
#include "io/descriptor_tables.h"

// TODO : sanity checks / min / overflow protection on frame buffer
int kmain()
{
	init_descriptor_tables();
	
	/* Serial Init Ports 1 & 2*/
	serial_init(1,2);			// general serial port
	serial_init(2,2);			// error log serial port

	/* make the screen blank (clear all initial load messages from bochs) */
	screen_clear(); 

	/* hello world!*/
	char buf[21] = "hello (kernel) world";	
	m_printf(TO_SCREEN, buf, 20); 
	m_printf(SERIAL_COM1_BASE, buf, 20); 


	/* Error log (serial pt 2) test */
	char str[11] = "ERROR: TEST";
	m_printf(SERIAL_COM2_BASE, str, 11); 


	/* Interupt test */ 
//	asm volatile ("int $0x3");
//	asm volatile ("int $0x4");

	return 0;
}
