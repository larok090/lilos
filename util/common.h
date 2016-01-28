/** 
 *  common.h - Defines common typedefs and memset / memcpy utilities
 */

#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H


typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;

void memset(void *ptr, int mem, int len);
void memcpy(void *src, void *dest, int len); 

void kprint(char *buf);
void kprint_dec(int buf);
void kprint_hex(char *buf);

#endif
