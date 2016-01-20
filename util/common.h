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

/**
 * memset -- fills len bytes pointed to by ptr with value of mem
 */
void memset(void *, int, int);


#endif
