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
	m_printf(TO_SCREEN, buf, k_str_len(buf));

	/* Serial Init Ports 1 & 2*/
	serial_init(1,2);
	serial_init(2,2);

	/* Serial Print Test to both*/ 
	m_printf(SERIAL_COM1_BASE, buf, TEST_STR_LEN - 1); // -1 because of null term str	
	m_printf(SERIAL_COM2_BASE, buf, TEST_STR_LEN - 1); // -1 because of null term str

/*	Test stuff for strcat 
 *	Distances lengths are wonky and display is still off	* 
 
	char buf2[6] = "Lolok ";
	char buf3[10] = "123456789 ";

	const int res_len = str_cat_len(buf3, buf2);
	char res[res_len];

	k_str_cat(buf3, buf2, res);

	m_printf(TO_SCREEN, res, res_len);
	m_printf(SERIAL_COM2_BASE, res, k_str_len(res));

// */
	return 0;
}
