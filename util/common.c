#include "common.h"
#include "../io/io.h"

//static char int_to_char(int);

/**
 * memset:
 * 		Fills len bytes starting from ptr with mem.
 */
void memset(void *ptr, int mem, int len)
{
	u16int i;
	char *p = (char *)ptr;

	for(i = 0; i < len; i++){	
		*p = mem;
		p++;
	}

	return;
}

/**
 * memcpy:
 * 		Copies first len bytes from src to dest 
 * 		DOES NOT care about what is in dest so be careful...
 */
void memcpy(void *src, void *dest, int len)
{
	char *dest_t = (char *)dest;
	char *src_t = (char *)src;

	int i;
	for(i=0; i < len; i++){
		dest_t[i] = src_t[i];
	}
	
	return;
}

/**
 * Write the given buffer to the stdout in our case the screen
 * 	- Caviat: Non null term strings will give blow up. Need to figure this out ****
 */
void print(char *buf)
{
   int i = 0;
   while (buf[i])
   { 
       screen_put(buf[i]);
	   i++;
   }
}

/**
 * kprint_dec:
 * 	 takes an integer input and prints the character version to screen
 */
void print_dec(int n)
{
	// range of numeric val = 48(0) - 57(9)
    screen_put(n + 48);
}

void print_hex(char *buf)
{
	screen_put('0');
	screen_put('x');

   int i = 0;
   while (buf[i])
   { 
       screen_put(buf[i]);
	   i++;
   }
}

/*
static char int_to_char(int buf)
{
	if(buf == 1){
		return '1';
	}
	else if(buf == 2){
		return '2';
	}
	else if(buf == 3){
		return '3';
	}
	else if(buf == 4){
		return '4';
	}
	else if(buf == 5){
		return '5';
	}
	else if(buf == 6){
		return '6';
	}
	else if(buf == 7){
		return '7';
	}
	else if(buf == 8){
		return '8';
	}
	else if(buf == 9){
		return '9';
	}
	else if(buf == 0){
		return '0';
	}

	return 'e';

}*/
