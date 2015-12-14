#include "str_util.h"

/** k_str_len:
 *		Reads a null terminated string and returns length
 *
 * @return length of a character string
 */
int k_str_len(char *str)
{
	int len = 0;
	
	while(str[len] != '\0')
		len++;
	
	return len;
}

/** k_str_cat:
 *				
 *
 */
inline void k_str_cat(char *a, char *b, char *result)
{	
	int i,j;	
	
	for(i = 0; i < k_str_len(a); i++){
		*result = a[i];
		result++;
	}
	
	for(j = 0;j < k_str_len(b); j++){
		*result = b[i];
		result++;
	}

	*result = '\0';
}

/**	str_cat_len:
 * 		Return sum of both char string lengths + 1;
 */
inline int str_cat_len(char *a, char *b)
{	
	return k_str_len(a) + k_str_len(b) + 1;
}
