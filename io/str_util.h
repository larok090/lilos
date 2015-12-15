#ifndef INCLUDE_STR_UTIL_H
#define INCLUDE_STR_UTIL_H

/* arbitrary choice for max num bytes strlen will check length */
#define MAX_STRLEN_CHK		128

int 	k_str_len(char *str);
void k_str_cat(char *a, char *b, char *result); 
int 	str_cat_len(char *a, char *b);

#endif /* INCLUDE_STR_UTIL_H */
