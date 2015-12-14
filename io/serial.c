#include "io.h"

/*Specific serial port bits to check*/
#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

#define SERIAL_LINE_ENABLE_DLAB			0x080

/** serial_configure_baud_rate:
 * 	Sets the speed of the data being sent. The default speed of a serial
 * 	port is 115200 bits/s. The argument is a divisor of that number, hence
 * 	the resulting speed becomes (115200 / divisor) bits/s.
 *
 * @param com      The COM port to configure
 * @param divisor  The divisor
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
	/* Note - i believe the ordering of the hi/low byte is machine dependent (not sure - conflicting data)
	 * current configuration of bochs emulator for this project does
	 * high 8 bits first then low [12/12/15 O.B])
	 */
	outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
	outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF); 	/* high 8 bits*/
	outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);			/* low 8 bits*/

	return;
}

/**serial_configure_line
 * Configures the line of the given serial port. The port is set to have a
 * data length of 8 bits, no parity bits, one stop bit and break control
 * disabled.
 *
 * @param com The serial port to configure
 */
void serial_configure_line(unsigned short com)
{
	/*
	 * Bit:			| 7 | 6 | 5 4 3 | 2 | 1 0 |
	 * Content:		| d | b | prty  | s |  dl |
	 * Value:		| 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
	 */
	outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);

	return;
}

/** serial_is_trasmit_fifo_empty:
 *	Checks whether the transmit FIFO queue is empty or not for the given 
 *	port.
 *
 *	@param	com	The COM port
 *	@return	0	if the transmit FIFO queue is not empty
 *			1	if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty(unsigned short com)
{
	/* 0x20 = 0010 0000 */
	return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

/** 
 * serial_write:
 * 		Write 'len' bytes from 'buf' to serial port 'com' data reg
 *
 * @param com	The COM port
 * @param buf	Buffer with bytes to write
 * @param len	The length of buf
 *
 * TODO:
 * Do i have to switch the bit that says  data_pt is empty ? *
 * Gonna test the read func as well
 */ 
void serial_write(unsigned short com, char *buf, unsigned int len)
{
	unsigned int i; 

	/* TODO : find a good timeout mechanism / read up more on serial port write management*/
	for(i = 0; i < len; i++){
		/* spin the data transmit port being NON-empty */
		while(serial_is_transmit_fifo_empty(com) == 0); 
		
		outb(SERIAL_DATA_PORT(com), *buf);
		buf += 1;
	}
		
	return;
}
