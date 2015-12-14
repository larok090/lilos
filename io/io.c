#include "io.h"
/********************************************************************************\
 *		TODO:
 *		1. Wrap WRITE function into a circular buffer 
 *
\*******************************************************************************/

/* write black and white character to output move cursor to where it was written*/
#define FB_WRITE_CHAR_BW(i, c)						\
	fb_write_cell( (i), (c),FB_BLACK, FB_WHITE );	\
	fb_move_cursor( ((i)/2) + 1 );					\
	(i) += 2

/* Framebuffer (for displaying chracters on screen) */
char *fb = (char *)0x000B8000;
/* Index of framebuffer at this moment */
unsigned int cur_fb_pos = 0;


/** WRITE SECTION BEGINS HERE **/

/*
 * Not sure if cursor works but screen cleared 
 */
void clear_screen( void )
{
	int  fb_pos = 0;
	char blank = (char)0;

	//WHY ARE YOU GREEEN
	while(fb_pos < FB_MAX_SIZ ){
		fb_write_cell( fb_pos, blank , FB_BLACK  , FB_BLACK );	
		fb_pos++;
	}
}
	
/**
 * Write the given buffer to screen
 */
int write(char *buf, unsigned int len)
{
	unsigned int i = 0;

	/* sanity check */
	if(!len)
		return -1;
	if(!buf)
		return -1;	

	for(i = 0; i < len; i++){
		/* do not overflow the buffer - best effort - return num chars written */
		if(cur_fb_pos + 2 > FB_MAX_SIZ)
			return i-2;

		FB_WRITE_CHAR_BW(cur_fb_pos, buf[i]);		
	}

	/* after FB_WRITE_CHAR the cursor is at next empty position
	 * This means that its 2 cursor slots ahead because of how
	 * fb_write_cell works (cells being 16 bits long) and the macro
	 * i - 1 is the first spot after our printed line
	 */
	 fb_move_cursor(i-1);

	return i;
}
/** END WRITE SEC **/


/*** FRAME BUFFER OPERATIONS START ***/

/** 
 * fb_move_cursor:
 * 	Moves the cursor of the framebuffer to the given position
 *
 * 	@param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos)
{
	outb(FB_COMMAND_PORT, 	FB_HIGH_BYTE_COMMAND); 
	outb(FB_DATA_PORT,	((pos >> 8) & 0x00FF));
	outb(FB_COMMAND_PORT, 	FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT,	pos & 0x00FF);
}

/** 
 * fb_write_cell:
 * 		Writes char given foreground and background colors to position i
 * 		in the frambuffer.
 */
void fb_write_cell(unsigned int i, char c , unsigned char fg, unsigned char bg)
{
	fb[i] = c;
	fb[i+1] = ((fg & 0x0F) << 4) | (bg & 0x0F); 
}

/* Clear out the frame buffer reserved mem area */
void fb_flush( void )
{
	int i;
	char *fb_tmp = fb;

	for( i = 0; i < FB_MAX_SIZ; i++){
		fb_tmp = 0;
		fb_tmp++;
	}
}
/** FRAME BUFFER OPERATIONS END ***/

/**
 * m_printf:
 * 	Prints to the source defined by mode argument:
 *
 * 	@param  mode	0: print to screen
 * 					any other number is treated as COM address		 
 * 	@param	buf		The buffer to be printed
 *	@param	len		Length of the buffer
 *
 *	@return			Mode = 0: #of bytes written
 *					Mode = N: 0
 */
int m_printf(unsigned short mode, char *buf, unsigned int len)
{
	int	wrote = 0;

	if(!mode)
		return -1; //Need to get errors 
	if(!buf)
		return 0;
	if(!len)
		return 0;

	/* Extendable for more serial ports */
	switch(mode){
		case TO_SCREEN:
			wrote = write( buf, len);
			break;
		case SERIAL_COM1_BASE:
		case SERIAL_COM2_BASE:
			serial_write(mode, buf, len);	
			wrote = 0;
			break;
		default:
			wrote = -1;
			break;
	}
	
	return wrote;
}
