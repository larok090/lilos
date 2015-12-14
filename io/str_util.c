#include "str_util.h"

/**
 * Return a null-terminated string's length
 * 
 * Up to 128 characters
 */
int k_str_len(char *str)
{
	int len = 0;
	
	while(str[len] != '\0' && len <= MAX_STRLEN_CHK)
		len++;
	
	return len;
}



