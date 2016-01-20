#include "common.h"

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
