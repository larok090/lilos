#include "../util/common.h"

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

/* The max size of the frame buffer 80 columns 2 bytes each = 80 * 25 rows = 4000*/
#define FB_MAX_SIZE			 	(80 * 25)		

/* Colors */
#define FB_BLACK				0
#define FB_GREEN 				2
#define FB_DARK_GREY			8
#define FB_WHITE				15

#define SERIAL_COM1_BASE		0x3F8		/* COM1 base port */
#define SERIAL_COM2_BASE		0x2F8		/* COM2 base port */



/** (asm)_outb:
 * 	Sends the given data to the given I/O port. Defnied in io.s
 *
 * 	@param port The I/O port to send the data to
 * 	@param data The data to send to the I/O port
 */
inline void _outb(u16int port, u8int data);

/** (asm)_inb:
 * Read a byte from an I/O port.
 *
 * @param port 	The address of the I/O port
 * @return		The read byte
 */
inline u8int _inb(u16int port);

void 	fb_write_cell(u16int i, char c , u8int fg, u8int bg);	
void 	fb_move_cursor(u16int pos);

void 	serial_configure_baud_rate(u16int com, u16int divisor);
void 	serial_configure_line(u16int com);
int		serial_is_transmit_fifo_empty(u16int com);
int 	serial_init(const u16int pt_num, const u16int div);

void 	screen_clear( void );

void 	serial_write(u16int com, char *buf, int len);
int 	write(char *buf, int len);

int 	m_printf(u16int mode,char *buf,int len);


#endif /* INCLUDE_IO_H */
