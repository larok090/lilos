#include "io.h"

/* The I/O ports */
#define FB_COMMAND_PORT			0x3D4
#define FB_DATA_PORT			0x3D5

/* The I/O port commands*/
#define FB_HIGH_BYTE_COMMAND	14
#define FB_LOW_BYTE_COMMAND		15

/* Colors */
#define FB_BLACK				0
#define FB_GREEN 				2
#define FB_DARK_GREY			8
#define FB_WHITE				15


/* Framebuffer (for displaying chracters on screen) */
char *fb = (char *)0x000B8000;

/** 
 * fb_move_cursor:
 * 	Moves the cursor of the framebuffer to the given position
 *
 * 	@param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos)
{
	/* TODO - unravel this-> write to notes */
	outb(FB_COMMAND_PORT, 	FB_HIGH_BYTE_COMMAND); 
	outb(FB_DATA_PORT,	((pos >> 8) & 0x00FF));
	outb(FB_COMMAND_PORT, 	FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT,	pos & 0x00FF);
}


/** fb_write_cell:
 * Writes char given foreground and background to position i
 * in the frambuffer.
 *
 * @param i	The location in the gramebuffer
 * @param c 	The character
 * @param fg	The foreground color
 * @param bg	The background color
 */
void fb_write_cell(unsigned int i, char c , unsigned char fg, unsigned char bg){	
	fb[i] = c;
	fb[i+1] = ((fg & 0x0F) << 4) | (bg & 0x0F); 
}
