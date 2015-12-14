#include "io.h"
#include "log.h"
#include "str_util.h"


void log_msg(const int mode, char *buf, int len)
{	
	/* Serial Init Com 2 - log serial port */
	serial_configure_baud_rate(SERIAL_COM2_BASE, 2);
	serial_configure_line(SERIAL_COM2_BASE);

	char error[8] = "[ERROR] ";
	char debug[8] = "[DEBUG] ";
	char info[7]  = "[INFO] ";

	// get a str_cat;
	switch(mode){
		case L_ERROR:
			m_printf(SERIAL_COM2_BASE, error, 8);
			break;
		case L_DEBUG:
			m_printf(SERIAL_COM2_BASE, debug, 8);
			break;
		case L_INFO:
			m_printf(SERIAL_COM2_BASE, info, 7);
			break;
		default:
			break;
	}
	/* add the actual message that was supposed to be logged */
	m_printf(SERIAL_COM2_BASE, buf, len);
	
	/* separate lines of input */
	char nl = '\n';
	m_printf(SERIAL_COM2_BASE, &nl, 1);
}
