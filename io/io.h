#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/* Magic number for screen print */
#define TO_SCREEN				0xFFF

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

/* Serial port entrence addresses */
#define SERIAL_COM1_BASE                0x3F8		/* COM1 base port */
#define SERIAL_COM2_BASE				0x2F8		/* COM2 base port */

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

/** fb_move_cursor:
 * 	Moves the cursor of the framebuffer to the given position
 *
 * 	@param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);

/*
 * Set all the memory in frame buffer mapped area to 0
 */
void fb_flush( void );

/* Sets all the bytes of the frame buffer to display \0 with black on black */
void clear_screen();

/**
 * Write the given buffer to the stdout in our case the shell
 *
 * @param len	length of the buffer
 * @param buf 	The buffer with content to be written to shell
 *
 * @return 		The amt of characters written from buf
 */
int write(char *buf, unsigned int len);


/** serial_configure_baud_rate:
 * 	Sets the speed of the data being sent. The default speed of a serial
 * 	port is 115200 bits/s. The argument is a divisor of that number, hence
 * 	the resulting speed becomes (115200 / divisor) bits/s.
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

/**serial_configure_line
 * Configures the line of the given serial port. The port is set to have a
 * data length of 8 bits, no parity bits, one stop bit and break control
 * disabled.
 *
 * @param com The serial port to configure
 */
void serial_configure_line(unsigned short com);

/** serial_is_trasmit_fifo_empty:
 *	Checks whether the transmit FIFO queue is empty or not for the given 
 *	port.
 */
int serial_is_transmit_fifo_empty(unsigned short com);

/** 
 * serial_write:
 * 		Write 'len' bytes from 'buf' to serial port 'com' data reg
 */
void serial_write(unsigned short com, char *buf, unsigned int len);


/**
 * m_printf:
 * 	Prints to the source defined by mode argument:
 */
int m_printf(unsigned short mode,char *buf,unsigned int len);


#endif /* INCLUDE_IO_H */
