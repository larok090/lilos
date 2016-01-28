#include "io.h"

#define CURSOR_POS() 80 * cursor_y + cursor_x
#define SET_CHAR_COLOR(bg,fg) ( (bg << 4) | (fg & 0x0F) ) << 8;

/* Framebuffer (for displaying chracters on screen) */
u16int *fb = (u16int *)0x000B8000;

u8int cursor_x = 0; // max = 80
u8int cursor_y = 0; // max = 25

static void scroll( void );

/** WRITE SECTION BEGINS HERE **/
//=================================================//

/** clear_screen:
 * 		Sets all the bytes of the frame buffer to display blank 
 */
void screen_clear( void )
{
	// 0x20 is the empty character
	u16int blank = 0x20 | SET_CHAR_COLOR(FB_BLACK, FB_WHITE);

	// Go through framebuffer set blank
	int i;
	for(i = 0; i < FB_MAX_SIZE; i++){
		fb[i] = blank;
	}
	cursor_x = 0;
	cursor_y = 0;
	fb_move_cursor( 0 );
}


// Writes a single character out to the screen.
// @author jamesmolloy.co.uk
void screen_put(char c)
{
   u16int attribute = SET_CHAR_COLOR(FB_BLACK, FB_WHITE);
   u16int *location;

   // Handle a backspace, by moving the cursor back one space
   if (c == 0x08 && cursor_x)
   {
       cursor_x--;
   }

   // Handle a tab by increasing the cursor's X, but only to a point
   // where it is divisible by 8.
   else if (c == 0x09)
   {
       cursor_x = (cursor_x+8) & ~(8-1);
   }

   // Handle carriage return
   else if (c == '\r')
   {
       cursor_x = 0;
   }

   // Handle newline by moving cursor back to left and increasing the row
   else if (c == '\n')
   {
       cursor_x = 0;
       cursor_y++;
   }
   // Handle any other printable character.
   else if(c >= ' ')
   {
       location = fb + (cursor_y*80 + cursor_x);
       *location = c | attribute;
       cursor_x++;
   }
	
   // Check if we need to insert a new line because we have reached the end
   // of the screen.
   if (cursor_x >= 80)
   {
       cursor_x = 0;
       cursor_y ++;
   }

   // Scroll the screen if needed.
   scroll();

   // Move the hardware cursor.
   fb_move_cursor(CURSOR_POS());

}

/**
 * Write the given buffer to the stdout in our case the screen
 * 	- Caviat: Non null term strings will give blow up. Need to figure this out ****
 */
void screen_write(char *c)
{
   int i = 0;
   while (c[i])
   {
       screen_put(c[i]);
	   i++;
   }
}

// Scrolls the text on the screen up by one line.
// @author jamesmolloy.co.uk
static void scroll()
{

   // Get a space character with the default colour attributes.
   u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
   u16int blank = 0x20 /* space */ | (attributeByte << 8);

   // Row 25 is the end, this means we need to scroll up
   if(cursor_y >= 25)
   {
       // Move the current text chunk that makes up the screen
       // back in the buffer by a line
       int i;
       for (i = 0*80; i < 24*80; i++)
       {
           fb[i] = fb[i+80];
       }

       // The last line should now be blank. Do this by writing
       // 80 spaces to it.
       for (i = 24*80; i < 25*80; i++)
       {
           fb[i] = blank;
       }
       // The cursor should now be on the last line.
       cursor_y = 24;
   }
}

/** END WRITE SEC **/
//=======================================================//

/*** FRAME BUFFER OPERATIONS START ***/
//========================================================//
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

/** FRAME BUFFER OPERATIONS END ***/
