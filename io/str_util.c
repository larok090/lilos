#include "str_util.h"

/** k_str_len:
 *		Reads a null terminated string and returns length
 *
 * @return length of a character string
 */
int k_str_len(char *str)
{
	int len;	
	for(len = 0; str[len] != '\0'; len++);
	
	return len;
}

/**
 * DO NOT USE THESE , 
 *
 * NO EXPLICIT MEMORY SET UP YET 
 * NO WAY TO TEST
 * NO ACTUAL RESULTS ---> future work to be done
 */

/** k_str_cat:
 *			
 *
 */
void k_str_cat(char *a, char *b, char *result)
{	
	int i,j;	
	int tot = 0;
	
	for(i = 0; i < k_str_len(a);i++){// k_str_len(a); i++){
		result[i] = a[i];
		tot++;
	}
	
	for(j = 0;j < k_str_len(b);j++){//k_str_len(b); j++){
		result[i+j] = b[i];
		tot++;
	}

}

/**	str_cat_len:
 * 		Return sum of both char string lengths + 1;
 */
int str_cat_len(char *a, char *b)
{	
	return k_str_len(a) + k_str_len(b);
}
