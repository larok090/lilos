#include "common.h"

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
