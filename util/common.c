#include "common.h"
#include "../io/io.h"

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
void kprint(char *buf)
{
	int i = 0;
	while (buf[i])
	{
	   screen_put(buf[i++]);
	}
}

/**
 * kprint_dec:
 * 	 takes an integer input and prints the character version to screen
 */
void kprint_dec(int buf)
{
	char c = 'e';

	if(buf == 1){
		c = '1';
	}
	else if(buf == 2){
		c = '2';
	}
	else if(buf == 3){
		c = '3';
	}
	else if(buf == 4){
		c = '4';
	}
	else if(buf == 5){
		c = '5';
	}
	else if(buf == 6){
		c = '6';
	}
	else if(buf == 7){
		c = '7';
	}
	else if(buf == 8){
		c = '8';
	}
	else if(buf == 9){
		c = '9';
	}
	else if(buf == 0){
		c = '0';
	}

	screen_put(c);	
}

void kprint_hex(char *buf)
{
	int i = 0;
	while (buf[i])
	{
	   screen_put(buf[i++]);
	}
}
