/***************************************************************************\
 *
 * 			kmain.c - The entry C code to the OS
 *
 \**************************************************************************/
#include "io/io.h"



void fb_write_cell(unsigned int, char , unsigned char, unsigned char);


int kmain(){
	/* test code for moving and displaying */
	fb_write_cell(0, 'A', FB_GREEN, FB_DARK_GREY);
	fb_move_cursor((unsigned int)2);
	fb_write_cell(2, 'Z', FB_GREEN, FB_DARK_GREY);
	return 0;
}


