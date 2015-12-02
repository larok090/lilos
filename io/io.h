#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/* Colors  for writing cursor*/
#define FB_BLACK				0
#define FB_GREEN 				2
#define FB_DARK_GREY			8
#define FB_WHITE				15


/** outb:
 * 	Sends the given data to the given I/O port. Defnied in io.s
 *
 * 	@param port The I/O port to send the data to
 * 	@param data The data to send to the I/O port
 */
void outb(unsigned short port, unsigned char data);

/** 
 * fb_move_cursor:
 * 	Moves the cursor of the framebuffer to the given position
 *
 * 	@param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);


#endif /* INCLUDE_IO_H */
