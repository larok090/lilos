#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/* The I/O ports */
#define FB_COMMAND_PORT			0x3D4
#define FB_DATA_PORT			0x3D5

/* The I/O port commands*/
#define FB_HIGH_BYTE_COMMAND	14
#define FB_LOW_BYTE_COMMAND		15

/* The max size of the frame buffer 80 columns 2 bytes each = 160 * 25 rows = 4000*/
#define FB_MAX_SIZ			 	4000	

/* Colors */
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

/** inb:
 * Read a byte from an I/O port.
 *
 * @param port 	The address of the I/O port
 * @return		The read byte
 */
unsigned char inb(unsigned short port);

/** 
 * fb_move_cursor:
 * 	Moves the cursor of the framebuffer to the given position
 *
 * 	@param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);


/** fb_write_cell:
 * Writes char given foreground and background to position i
 * in the frambuffer.
 *
 * @param i		The location in the framebuffer
 * @param c 	The character
 * @param fg	The foreground color
 * @param bg	The background color
 */
void fb_write_cell(unsigned int i, char c , unsigned char fg, unsigned char bg);	

/**
 * Write the given buffer to the stdout in our case the shell
 *
 * @param len	length of the buffer
 * @param buf 	The buffer with content to be written to shell
 *
 * @return 		The amt of characters written from buf
 */
int write(char *buf, unsigned int len);

/* Sets all the bytes of the frame buffer to display \0 with black on black */
void clear_screen();

/*
 * Set all the memory in frame buffer mapped area to 0
 */
void fb_flush( void );

/** serial_is_trasmit_fifo_empty:
 *	Checks whether the transmit FIFO queue is empty or not for the given 
 *	port.
 */
int serial_is_transmit_fifo_empty(unsigned int com);


#endif /* INCLUDE_IO_H */
