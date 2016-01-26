#include "io.h"

/* write black and white character to output move cursor to where it was written*/
#define FB_WRITE_CHAR_BW(i, c)						\
	fb_write_cell( (i), (c), FB_BLACK, FB_WHITE );	\
	fb_move_cursor((i)/2 + 1);					\
	(i) += 2

/* Framebuffer (for displaying chracters on screen) */
char *fb = (char *)0x000B8000;

/* Index of framebuffer at this moment */
u16int cur_fb_pos = 0;

u8int cursor_x = 0; // max = 80
u8int cursor_y = 0; // max = 25



/** WRITE SECTION BEGINS HERE **/
/** clear_screen:
 * 		Sets all the bytes of the frame buffer to display blank 
 */
void screen_clear( void )
{
	// Go through framebuffer each i+2 because 2 bytes to a cell
	int i;
	for(i = 0; i < FB_MAX_SIZE; i+=2){
		fb_write_cell( i , ' ', FB_BLACK, FB_WHITE);
	}
	fb_move_cursor( 0 );
}
	
/**
 * Write the given buffer to the stdout in our case the screen
 *
 * @param len	length of the buffer
 * @param buf 	The buffer with content to be written to shell
 *
 * @return 		The amt of characters written from buf
 */
int write(char *buf, int len)
{
	/* sanity check */
	if(!len)
		return -1;
	if(!buf)
		return -1;	

	int i;
	for(i = 0; i < len; i++){

		cursor_x++;

		if(cursor_x % 80 > 0){
			cursor_y++;
			cursor_x = 0;	

			if(cursor_y > 25){
				// SCROLL FUNCTION NEEDED
			}
		}

		/* still building the replacement here */
		if(cur_fb_pos + 2 > FB_MAX_SIZE){
			/* buffer full -> flush return the #bytes written */
			return i-2;
		}
		FB_WRITE_CHAR_BW(cur_fb_pos, buf[i]);		
	}

	return i;
}

/**
 * scroll( void )
 * 		If we run out of framebuffer space move down a line leave line 24 empty
 */
/*
static void scroll( void )
{
	char *video_mem;

}
*/

/** END WRITE SEC **/

/*** FRAME BUFFER OPERATIONS START ***/
/** 
 * fb_move_cursor:
 * 	Moves the cursor of the framebuffer to the given position
 *
 * 	@param pos The new position of the cursor
 *
 * 	@author littleosbook.github.io
 */
void fb_move_cursor(u16int pos)
{
	_outb(FB_COMMAND_PORT, 	FB_HIGH_BYTE_COMMAND); 
	_outb(FB_DATA_PORT,	((pos >> 8) & 0x00FF));
	_outb(FB_COMMAND_PORT, 	FB_LOW_BYTE_COMMAND);
	_outb(FB_DATA_PORT,	pos & 0x00FF);
}

/** fb_write_cell:
 * 		Writes char given foreground and background to position i
 * 		in the frambuffer.
 *
 * @param i		The location in the framebuffer
 * @param c 	The character
 * @param fg	The foreground color
 * @param bg	The background color
 *
 * @author littleosbook.github.io
 */
void fb_write_cell(u16int i, char c , u8int fg, u8int bg)
{
	fb[i] = c;
	fb[i+1] = ((fg & 0x0F) << 4) | (bg & 0x0F); 
}


/** DEPRECATED ---> In process of deletion **/

/** FRAME BUFFER OPERATIONS END ***/

/**
 * m_printf:
 * 	Prints to the source defined by mode argument:
 *			Best effort , writes as much as it can gives back that #
 *
 * 	@param  mode	TO_SCREEN (0): print to screen
 * 					any other number: treated as COM address		 
 * 	@param	buf		The buffer to be printed
 *	@param	len		Length of the buffer
 *
 *	@return			Mode = TO_SCREEN: #of bytes written
 *					Mode = COM_PORT: 0
 */
int m_printf(u16int mode, char *buf, int len)
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
