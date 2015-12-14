/***************************************************************************\
 *
 * 			kmain.c - The entry C code to the OS
 *
 \**************************************************************************/
#include "io/io.h"
#include "io/str_util.h"
#include "io/log.h"

#define TEST_STR_LEN	21

// TODO : sanity checks / min / overflow protection on frame buffer
int kmain()
{
	/* zero out the frame buffer area */
	fb_flush();

	/* make the screen blank (clear all initial load messages from bochs) */
	clear_screen(); 

	/* hello world! */	
	char buf[TEST_STR_LEN] = "hello (kernel) world";	
	m_printf(TO_SCREEN, buf, TEST_STR_LEN);

	/* Serial Init */
	serial_configure_baud_rate(SERIAL_COM1_BASE, 2);
	serial_configure_line(SERIAL_COM1_BASE);

	/* serial print */ 
	m_printf(SERIAL_COM1_BASE, buf, TEST_STR_LEN - 1); // -1 because of null term str

	/* Serial Init Com 2 */
	serial_configure_baud_rate(SERIAL_COM2_BASE, 2);
	serial_configure_line(SERIAL_COM2_BASE);
	

	return 0;
}
