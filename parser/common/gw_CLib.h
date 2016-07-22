/*
**********************************************************************
*                          Micrium, Inc.
*                      949 Crestview Circle
*                     Weston,  FL 33327-1848
*
*                            uC/FS
*
*             (c) Copyright 2001 - 2008, Micrium, Inc.
*                      All rights reserved.
*
***********************************************************************

----------------------------------------------------------------------
File        : gw_CLib.h
Purpose     : Header file for the file system's CLIB functions.
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
None.
---------------------------END-OF-HEADER------------------------------
*/

#ifndef __GW_CLIB_H__
#define __GW_CLIB_H__

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

int gw_CLIB_atoi(const char *s);
int gw_CLIB_memcmp(const void *s1, const void *s2, unsigned long NumBytes);
void * gw_CLIB_memset(void *pData, int Fill, unsigned long NumBytes);
char * gw_CLIB_strncat(char *s1, const char *s2, unsigned long n);
char * gw_CLIB_strcat(char *s1, const char *s2);
int gw_CLIB_strcmp(const char *s1, const char *s2);
char * gw_CLIB_strcpy(char *dest, const char *src);
unsigned gw_CLIB_strlen(const char *s);
int gw_CLIB_strncmp(const char *s1, const char *s2, int n);
char *gw_CLIB_strncpy(char *s1, const char *s2, int n);
int gw_CLIB_toupper(int c);
char* gw_CLIB_strchr(const char *s, int c);
char* gw_CLIB_strrchr(const char *s, int c);
char * gw_CLIB_strstr(const char *haystack, const char *needle);
char * gw_CLIB_itoa(char *s, int c);
char * gw_CLIB_uitoa(char *s, unsigned int c);
char * gw_CLIB_ctoa(char *s, char c);
char * gw_CLIB_uctoa(char *s, unsigned char c);
char * gw_CLIB_iptoa(char *dest, unsigned char *sour);
int gw_CLIB_IsDecimalString(char *s, int length);
int gw_CLIB_IsIntegerString(char *s, int length);
int gw_CLIB_IsFloatString(char *s, int length);
int gw_CLIB_str2base(char *s, unsigned int *out_value);
void swapByte(char *sour, int size);

#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif  /* __GW_CLIB_H__  */

/*************************** End of file ****************************/

