/***************************************************************************\
 *
 * 			kmain.c - The entry C code to the OS
 *
 \**************************************************************************/
#include "io/io.h"


// TODO : change green on clear_screen
// TODO : sanity checks / min / overflow protection on frame buffer
int kmain()
{

	/* zero out the frame buffer area */
	fb_flush();

	/* make the screen blank (clear all initial load messages from bochs) */
	clear_screen();

	/* hello world! */
	char buf[21] = "hello (kernel) world";	
	write( buf, 21);

	return 0;
}
