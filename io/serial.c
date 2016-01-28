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
 *
 * @author littleosbook.github.io
 */
void serial_configure_baud_rate(u16int com, u16int divisor)
{
	/* Note - i believe the ordering of the hi/low byte is machine dependent (not sure - conflicting data)
	 * current configuration of bochs emulator for this project does
	 * high 8 bits first then low [12/12/15 O.B])
	 */
	_outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
	_outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF); 	/* high 8 bits*/
	_outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);			/* low 8 bits*/

	return;
}

/**serial_configure_line
 * Configures the line of the given serial port. The port is set to have a
 * data length of 8 bits, no parity bits, one stop bit and break control
 * disabled.
 *
 * @param com The serial port to configure
 * 
 * @author littleosbook.github.io
 */
void serial_configure_line(u16int com)
{
	/*
	 * Bit:			| 7 | 6 | 5 4 3 | 2 | 1 0 |
	 * Content:		| d | b | prty  | s |  dl |
	 * Value:		| 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
	 */
	_outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);

	return;
}

/** serial_is_trasmit_fifo_empty:
 *	Checks whether the transmit FIFO queue is empty or not for the given 
 *	port.
 *
 *	@param	com	The COM port
 *	@return	0	if the transmit FIFO queue is not empty
 *			1	if the transmit FIFO queue is empty
 *
 *	@author littleosbook.github.io
 */
int serial_is_transmit_fifo_empty(u16int com)
{
	/* 0x20 = 0010 0000 */
	return _inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
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
void serial_write(u16int com, char *buf, int len)
{
	int i; 

	/* TODO : find a good timeout mechanism / read up more on serial port write management*/
	for(i = 0; i < len; i++){
		/* spin the data transmit port being NON-empty */
		while(serial_is_transmit_fifo_empty(com) == 0); 
		
		_outb(SERIAL_DATA_PORT(com), *buf);
		buf++;
	}
	
	return;
}

/** serial_init:
 * 		initializes a serial port com1 or com2 with divisor for baud rate config
 * 		Config bits set - 0x03 - data len 8 bits. no pairty bits, 1 stop bit 
 * 		break ctrl off
 *
 * 		@return		 0: success
 * 					-1: failure
 */
int serial_init(const u16int pt_num, const u16int div)
{
	if(!div)
		return -1;

	switch(pt_num)
	{
		case 1:
			serial_configure_baud_rate(SERIAL_COM1_BASE, div);
			serial_configure_line(SERIAL_COM1_BASE);
			break;
		case 2:
			serial_configure_baud_rate(SERIAL_COM2_BASE, div);
			serial_configure_line(SERIAL_COM2_BASE);
			break;
		default:
			return -1;
	}

	return 0;
}
