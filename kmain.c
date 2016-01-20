/***************************************************************************\
 *
 * 			kmain.c - The entry C code to the OS
 *
 \**************************************************************************/
#include "io/io.h"
#include "io/str_util.h"
#include "io/log.h"
#include "io/descriptor_tables.h"

#define TEST_STR_LEN	21

// TODO : sanity checks / min / overflow protection on frame buffer
int kmain()
{
	init_descriptor_tables();
	
	/* Serial Init Ports 1 & 2*/
	serial_init(1,2);			// general serial port
	serial_init(2,2);			// error log serial port

	/* zero out the frame buffer area */
	fb_flush();

	/* make the screen blank (clear all initial load messages from bochs) */
	clear_screen(); 

	/* hello world! */	
	char buf[TEST_STR_LEN] = "hello (kernel) world";	
	m_printf(TO_SCREEN, buf, k_str_len(buf));


	char str[11] = "ERROR: TEST";
	m_printf(SERIAL_COM2_BASE, str, 11); 

	asm volatile ("int $0x3");
	asm volatile ("int $0x4");

	return 0;
}
