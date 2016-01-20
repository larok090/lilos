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
	/* zero out the frame buffer area */
	fb_flush();

	/* make the screen blank (clear all initial load messages from bochs) */
	clear_screen(); 

	/* hello world! */	
	char buf[TEST_STR_LEN] = "hello (kernel) world";	
	m_printf(TO_SCREEN, buf, k_str_len(buf));

	/* Serial Init Ports 1 & 2*/
	serial_init(1,2);
	serial_init(2,2);

	/* Serial Print Test to both*/ 
	m_printf(SERIAL_COM1_BASE, buf, k_str_len(buf)); // -1 because of null term str	
	char str[5] = "OSKAR";
	m_printf(SERIAL_COM2_BASE, str, 5); // -1 because of null term str

	return 0;
}
