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
File        : gw_CLib.c
Purpose     : File system's standard c-lib replacement routines
---------------------------END-OF-HEADER------------------------------
*/

/*********************************************************************
*
*       #include Section
*
**********************************************************************
*/
#include <string.h>
#include "gw_CLib.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       gw_CLIB_atoi
*
*  Function description:
*    Convert string to int. The function stops with
*    the first character it cannot convert. It expects decimal numbers only.
*    It can handle +/- at the beginning and leading 0. It cannot handle
*    HEX or any other numbers.
*
*  Parameters:
*    s           - Pointer to a zero terminated string.
*
*  Return value:
*    ==0         - In case of any problem or if the converted value is zero.
*    !=0         - Integer value of the converted string.
*/
int gw_CLIB_atoi(const char *s) {
    unsigned int base;
    const char   *t;
    signed char  sign;
    char         c;
    int          value;
    int          len;
    int          i;

    value = 0;
    /* */
    /* Check for +/- */
    /* */
    sign = 1;
    len = gw_CLIB_strlen(s);
    if (len <= 0) {
        return 0;
    }
    t = s;
    if (*t == '-') {
        t++;
        sign = -1;
    }
    else if (*t == '+') {
        t++;
    }
    /* */
    /* Skip leading 0 */
    /* */
    len = gw_CLIB_strlen(t);
    if (len <= 0) {
        return 0;
    }
    while (*t == '0') {
        t++;
        len--;
        if (len <= 0) {
            break;
        }
    }
    /* */
    /* Find end of number */
    /* */
    for (i = 0; i < len; i++) {
        if (t[i] > '9') {
            break;
        }
        if (t[i] < '0') {
            break;
        }
    }
    len = i;
    if (len <= 0) {
        return 0;
    }
    /* */
    /* Calculate base */
    /* */
    base = 1;
    for (i = 1; i < len; i++) {
        base *= 10;
    }
    /* */
    /* Get value */
    /* */
    for (i = 0; i < len; i++) {
        c = t[i];
        if (c > '9') {
            break;
        }
        if (c < '0') {
            break;
        }
        c -= '0';
        value += c*base;
        base /= 10;
    }
    return sign * value;
}

/*********************************************************************
*
*       gw_CLIB_memcmp
*
*  Function description:
*    Compare bytes in two buffers
*
*  Parameters:
*    s1          - Pointer to first buffer.
*    s2          - Pointer to second buffer.
*    NumBytes    - Number of bytes to compare
*
*  Return value:
*    0           - bytes are equal
*    1           - bytes are different
*/

int gw_CLIB_memcmp(const void *s1, const void *s2, unsigned long NumBytes) {
    const char * p1;
    const char * p2;

    p1 = (const char*) s1;
    p2 = (const char*) s2;

    while (NumBytes--) {
        if (*p1++ != *p2++) {
            return 1;           /* Not equal */
        }
    }
    return 0;                   /* Equal */
}

/*********************************************************************
*
*       gw_CLIB_memset
*
*  Function description:
*    Copy the value of c (converted to an unsigned
*    char) into each of the first n characters of the object pointed to
*    by s.
*
*  Parameters:
*    s           - Pointer to an object.
*    c           - 'Character' value to be set.
*    n           - Number of characters to be set.
*
*  Return value:
*    Value of s.
*/
void * gw_CLIB_memset(void *pData, int Fill, unsigned long NumBytes) {
    char * p;
    int  NumInts;

    p = (char *)pData;
    /* */
    /* Write bytes until we are done or have reached an int boundary */
    /* */
    while (NumBytes && ((sizeof(int) - 1) & (unsigned long)p)) {
        *p++ = Fill;
        NumBytes--;
    }
    /* */
    /* Write Ints */
    /* */
    NumInts = (unsigned)NumBytes / sizeof(int);
    if (NumInts) {
        int FillInt;
        int *pInt;
        NumBytes &= (sizeof(int) - 1);
        if (sizeof(int) == 2) {         /* May some compilers generate a warning at this line: Condition is always true/false */
            FillInt = Fill * 0x101;     /* May some compilers generate a warning at this line: Unreachable code */
        } else if (sizeof(int) == 4) {  /* May some compilers generate a warning at this line: Condition is always true/false */
            FillInt = Fill * 0x1010101; /* May some compilers generate a warning at this line: Unreachable code */
        }
        pInt = (int*)p;
        /* */
        /* Fill large amount of data at a time */
        /* */
        while (NumInts >= 4) {
            *pInt++ = FillInt;
            *pInt++ = FillInt;
            *pInt++ = FillInt;
            *pInt++ = FillInt;
            NumInts -= 4;
        }
        /* */
        /* Fill one int at a time */
        /* */
        while (NumInts) {
            *pInt++ = FillInt;
            NumInts--;
        }
        p = (char*)pInt;
    }
    /* Fill the remainder byte wise */
    while (NumBytes) {
        *p++ = Fill;
        NumBytes--;
    }
    return pData;
}

/*********************************************************************
*
*             gw_CLIB_strncat
*
*  Function description:
*    Appends n characters from the array
*    pointed to by s2 to the array pointed to by s1.
*
*  Parameters:
*    s1          - Pointer to a character array.
*    s2          - Pointer to a character array.
*    n           - Number of characters to append
*
*  Return value:
*    Value of s1.
*/
char * gw_CLIB_strncat(char *s1, const char *s2, unsigned long n)  {
    char *s;

    if (s1) {
        for (s = s1; *s != '\0'; ++s);       /* find end of s1[] */
        if (s2) {
            for (; (0 < n) && (*s2 != 0); --n) {  /* copy at most n chars from s2[] */
                *s++ = *s2++;
            }
            *s = '\0';
        }
    }
    return s1;
}


/*********************************************************************
*
*             gw_CLIB_strcat
*
*  Function description:
*    Adds characters from the array
*    pointed to by s2 to the array pointed to by s1.
*
*  Parameters:
*    s1          - Pointer to a character array.
*    s2          - Pointer to a character array.
*
*  Return value:
*    Value of s1.
*/
char * gw_CLIB_strcat(char *s1, const char *s2) {
    char * s;

    if (s1) {
        for (s = s1; *s != '\0'; ++s);            /* find end of s1[] */
        if (s2) {
            for (; (*s = *s2) != '\0'; ++s, ++s2);    /* copy s2[] to end */
        }
    }
    return (s1);
}

/*********************************************************************
*
*       gw_CLIB_strcmp
*
*  Function description:
*    Compare the sring pointed to by s1 with the
*    string pointed to by s2.
*
*  Parameters:
*    s1          - Pointer to a zero terminated string.
*    s2          - Pointer to a zero terminated string.
*
*  Return value:
*    0           - bytes are equal
*    1           - bytes are different
*/
int gw_CLIB_strcmp(const char *s1, const char *s2)	{
    char c1, c2;
    do {
        c1 = *s1++;
        c2 = *s2++;
        if (c1 != c2) {
            return 1;   /* Different */
        }
    } while (c1);
    return 0;           /* Equal */
}


/*********************************************************************
*
*      gw_CLIB_strcpy
*
*  Description:
*    Copy characters from the array
*    pointed to by s2 to the array pointed to by s1.
*
*  Parameters:
*    dest         - Pointer to a character array.
*    src          - Pointer to a character array.
*
*  Return value:
*    Value of s1.
*/
char * gw_CLIB_strcpy(char *dest, const char *src) {
    char *p = 0;
    if (dest) {
        p = dest;
        while(*src != 0) {
            *dest++  = *src++;
        }
        *dest = 0;
    }
    return p;
}


/*********************************************************************
*
*       gw_CLIB_strlen
*
*  Function description:
*    Compute the length of a string pointed to by s.
*
*  Parameters:
*    s           - Pointer to a zero terminated string.
*
*  Return value:
*    Number of characters preceding the terminating 0.
*/
unsigned int gw_CLIB_strlen(const char *s) {
    unsigned int Len;

    Len = 0;
    while (*s++) {
        Len++;
    }
    return Len;
}

/*********************************************************************
*
*       gw_CLIB_strncmp
*
*  Function description:
*    Compare no more than n characters from the
*    array pointed to by s1 to the array pointed to by s2.
*
*  Parameters:
*    s1          - Pointer to a character array.
*    s2          - Pointer to a character array.
*    n           - Number of characters to compare.
*
*  Return value:
*    0           - bytes are equal
*    1           - bytes are different
*/
int gw_CLIB_strncmp(const char *s1, const char *s2, int n) {
    for (; n > 0; n--) {
        char c1, c2;
        c1 = *s1++;
        c2 = *s2++;
        if (c1 != c2) {
            return 1;       /* Different */
        }
        if (*s1 == '\0') {
            return 0;       /* Equal */
        }
    }
    return 0;               /* Equal */
}


/*********************************************************************
*
*       gw_CLIB_strncpy
*
*  Function description:
*    Copy not more than n characters from the array
*    pointed to by s2 to the array pointed to by s1.
*
*  Parameters:
*    s1          - Pointer to a character array.
*    s2          - Pointer to a character array.
*    n           - Number of characters to copy.
*
*  Return value:
*    Value of s1.
*/
char* gw_CLIB_strncpy(char *s1, const char *s2, int n) {
    char *s;

    for (s = s1; (0 < n) && (*s2 != '\0'); --n) {
        *s++ = *s2++;         /* copy at most n chars from s2[] */
    }
    for (; 0 < n; --n) {
        *s++ = '\0';
    }
    return s1;
}

/*********************************************************************
*
*       gw_CLIB_toupper
*
*  Function description:
*    yConvert a lowecase letter to a corresponding
*    uppercase letter.
*
*  Parameters:
*    c           - Letter to convert.
*
*  Return value:
*    Corresponding uppercase character.
*/
int gw_CLIB_toupper(int c) {
    if ((c >= 'a') && (c <= 'z')) {
        c &= 0xdf;
    }
    return c;
}

/*********************************************************************
*
*       gw_CLIB_strchr
*
*  Function description:
*
*  Parameters:
*
*  Return value:
*
*/
char* gw_CLIB_strchr(const char *s, int c)	{
    while (*s){
        if (*s == c) {
            return (char*) s;
        }
        s++;
    }
    return 0;
}

/*********************************************************************
*
*       gw_CLIB_strrchr
*
*  Function description:
*
*  Parameters:
*
*  Return value:
*
*/
char* gw_CLIB_strrchr(const char *s, int c)	{
    int i = gw_CLIB_strlen(s);
    char *p = (char *) (s+i);

    for (; 0 < i; i--) {
        if (*p == c) {
            return (char*) p;
        }
        p--;
    }
    return 0;
}

/*********************************************************************
*
*             gw_CLIB_strstr
*
*  Function description:
*    Adds characters from the array
*    pointed to by s2 to the array pointed to by s1.
*
*  Parameters:
*    s1          - Pointer to a character array.
*    s2          - Pointer to a character array.
*
*  Return value:
*    Value of s1.
*/
char * gw_CLIB_strstr(const char *haystack, const char *needle) {
    char *s = 0;

    if (haystack && needle) {
        for (s = (char*)haystack; *s != '\0'; ++s) {
            if (gw_CLIB_strcmp(s, needle) == 0) {
                return s;
            }
        }
    }
    return 0;
}

/*********************************************************************
*
*       gw_CLIB_itoa
*
*  Function description:
*    yConvert a lowecase letter to a corresponding
*    uppercase letter.
*
*  Parameters:
*    c           - Letter to convert.
*
*  Return value:
*    Corresponding uppercase character.
*/
char * gw_CLIB_itoa(char *s, int c) {
	char *p = 0;

	if(s) {
		p = s;

		if(c & 0x80000000) {
			c &= 0x80000000;
			*s = '-';
			s++;
		}
		if(0 == c) {
			*s = '0';
			s++;
		}
		else {
			int i = 1000000000, j = 10;
			for(i = 1000000000, j = 10; j > 0; i /= 10, j--){
				if(c >= i) {
					*s = ((c / i) % 10) + '0';
					s++;
				}
			}
		}
		*s = '\0';
	}
    return (char *) p;
}

char * gw_CLIB_uitoa(char *s, unsigned int c) {
	char *p = 0;

	if(s) {
		p = s;
		if(0 == c) {
			*s = '0';
			s++;
		}
		else {
			int i = 1000000000, j = 10;
			for(i = 1000000000, j = 10; j > 0; i /= 10, j--){
				if(c >= i) {
					*s = ((c / i) % 10) + '0';
					s++;
				}
			}
		}
		*s = '\0';
	}
    return (char *) p;
}

char * gw_CLIB_ctoa(char *s, char c) {
	char *p = 0;

	if(s) {
		p = s;
		if(c & 0x80) {
			c &= 0x80;
			*s = '-';
			s++;
		}

		if(0 == c) {
			*s = '0';
			s++;
		}
		else {
			int i = 0, j = 0;
			for(i = 100, j = 3; j > 0; i /= 10, j--){
				if(c >= i) {
					*s = ((c / i) % 10) + '0';
					s++;
				}
			}
		}
		*s = '\0';
	}
    return (char *) p;
}

char * gw_CLIB_uctoa(char *s, unsigned char c) {
	char *p = 0;

	if(s) {
		p = s;
		if(0 == c) {
			*s = '0';
			s++;
		}
		else {
			int i = 0, j = 0;
			for(i = 100, j = 3; j > 0; i /= 10, j--){
				if(c >= i) {
					*s = ((c / i) % 10) + '0';
					s++;
				}
			}
		}
		*s = '\0';
	}
    return (char *) p;
}


char * gw_CLIB_iptoa(char *dest, unsigned char *sour) {
	char *p = 0;
	char buf[8];

	if(dest && sour) {
		p = dest;
		gw_CLIB_uctoa(dest, (unsigned char)sour[0]);
		strcat(dest, ".");

		gw_CLIB_uctoa(buf,(unsigned char)sour[1]);
		strcat(dest, buf);
		strcat(dest, ".");

		gw_CLIB_uctoa(buf,(unsigned char)sour[2]);
		strcat(dest, buf);
		strcat(dest, ".");

		gw_CLIB_uctoa(buf,(unsigned char)sour[3]);
		strcat(dest, buf);
	}
	return (char *) p;
}

  inline char bcd2hex(char BCD)
    {
        return (BCD > 9) ? (BCD-10+'A'):(BCD+'0');
    }
    inline void char2hex(char value,char **out)
    {
        *(*out)++ = bcd2hex(value >> 4);
        *(*out)++ = bcd2hex(value & 0x0f);
    }
    
void gw_CLIB_bytes2hex(int value, char *out_buf, char bytes)
{
    char *p;

  

    p = out_buf;
    *p++ = '0';
    *p++ = 'x';
    if(bytes > 3)char2hex(value >> 24,&p);
    if(bytes > 2)char2hex(value >> 16,&p);
    if(bytes > 1)char2hex(value >> 8,&p);
    char2hex(value &0xff,&p);
    *p = 0;
}

/*********************************************************************
*
*       gw_CLIB_IsDecimalString
*
*  Function description:
*
*  Parameters:
*
*  Return value:
*
*/
int gw_CLIB_IsDecimalString(char *s, int length)
{
	int i = 0;

	if(s && (0 < length)) {
		for(i = 0; i < length; i++) {
			if(('0' > *(s+i))||('9' < *(s+i))) return -1;
		}
		return 0;
	}
	return -1;
}

/*********************************************************************
*
*       gw_CLIB_IsIntegerString
*
*  Function description:
*
*  Parameters:
*
*  Return value:
*
*/
int gw_CLIB_IsIntegerString(char *s, int length)
{
//[space1][+/-]integer[space2].
	int i = 0;
	int f_space1 = 0, f_sign = 0, f_integer = 0, f_space2 = 0;

	if((0 == s)||(0 >= length)) {
		return -1;
	}

	for(i = 0; i < length; i++) {
		if(' ' == *(s+i)) {
			if(f_space2) {
			}
			else if(f_integer) {
				f_space2 = 1;
			}
			else if(f_sign) {
				return -1;
			}
			else if(f_space1) {
			}
			else {
				f_space1 = 1;
			}
		}
		else if(('+' == *(s+i))||('-' == *(s+i))) {
			if(f_space2) {
				return -1;
			}
			else if(f_integer) {
				return -1;
			}
			else if(f_sign) {
				return -1;
			}
			else if(f_space1) {
				f_sign = 1;
			}
			else {
				f_sign = 1;
			}
		}
		else if(('0' <= *(s+i))&&('9' >= *(s+i))) {
			if(f_space2) {
				return -1;
			}
			else if(f_integer) {
			}
			else if(f_sign) {
				f_integer = 1;
			}
			else if(f_space1) {
				f_integer = 1;
			}
			else {
				f_integer = 1;
			}
		}
		else {
			return -1;
		}
	}
	return 0;
}

/*********************************************************************
*
*       gw_CLIB_IsFloatString
*
*  Function description:
*
*  Parameters:
*
*  Return value:
*
*/
int gw_CLIB_IsFloatString(char *s, int length)
{
//[space1][+/-]integer[.][decimal][space2].
//[space1][+/-][integer].decimal[space2].
	int i = 0;
	int f_space1 = 0, f_sign = 0, f_integer = 0, f_dot = 0, f_decimal = 0, f_space2 = 0;

	if((0 == s)||(0 >= length)) {
		return -1;
	}

	for(i = 0; i < length; i++) {
		if(' ' == *(s+i)) {
			if(f_space2) {
			}
			else if(f_decimal) {
				f_space2 = 1;
			}
			else if(f_dot) {
				f_space2 = 1;
			}
			else if(f_integer) {
				f_space2 = 1;
			}
			else if(f_sign) {
				return -1;
			}
			else if(f_space1) {
			}
			else {
				f_space1 = 1;
			}
		}
		else if(('+' == *(s+i))||('-' == *(s+i))) {
			if(f_space2) {
				return -1;
			}
			else if(f_decimal) {
				return -1;
			}
			else if(f_dot) {
				return -1;
			}
			else if(f_integer) {
				return -1;
			}
			else if(f_sign) {
				return -1;
			}
			else if(f_space1) {
				f_sign = 1;
			}
			else {
				f_sign = 1;
			}
		}
		else if('.' == *(s+i)) {
			if(f_space2) {
				return -1;
			}
			else if(f_decimal) {
				return -1;
			}
			else if(f_dot) {
				return -1;
			}
			else if(f_integer) {
				f_dot = 1;
			}
			else if(f_sign) {
				f_dot = 1;
			}
			else if(f_space1) {
				f_dot = 1;
			}
			else {
				f_dot = 1;
			}
		}
		else if(('0' <= *(s+i))&&('9' >= *(s+i))) {
			if(f_space2) {
				return -1;
			}
			else if(f_decimal) {
			}
			else if(f_dot) {
				f_decimal = 1;
			}
			else if(f_integer) {
			}
			else if(f_sign) {
				f_integer = 1;
			}
			else if(f_space1) {
				f_integer = 1;
			}
			else {
				f_integer = 1;
			}
		}
		else {
			return -1;
		}
	}
	return 0;
}

/*********************************************************************
*
*       gw_CLIB_str2base
*
*  Function description:
*
*  Parameters:
*
*  Return value:
*
*/
#define _GW__NO_ERROR			 0
#define _GW__ERROR				-1
#define _GW__UNDEFINED_BASE		-2
#define _GW__DATA_NOT_ALLOWED	-3
#define _GW__DATA_RANGE_OVER	-4


int gw_CLIB_str2base(char *s, unsigned int *out_value)
{
	char *p = 0;
	unsigned short i = 0, len = 0;
	unsigned int base = 0, val0 = 0, val1 = 0;

	len = gw_CLIB_strlen(s);
	if(s && (0 < len)) {
		p = s;
		if(('b' == *p)||('B' == *p)) {
			base = 2;
			p++;
		}
		else if(('q' == *p)||('Q' == *p)) {
			base = 8;
			p++;
		}
		else if(('h' == *p)||('H' == *p)) {
			base = 16;
			p++;
		}
		else if(('0' <= *p)||('9' >= *p)) {
			base = 10;
		}
		else return _GW__UNDEFINED_BASE;

		for(i = 1 ; i < len; i++, p++){
			val0 *= base;

			if(2 == base) {
				if(('0' <= *p)&&('1' >= *p)) {
					val1 = *p - '0';
				}
				else return _GW__DATA_NOT_ALLOWED;
			}
			else if(8 == base) {
				if(('0' <= *p)&&('7' >= *p)) {
					val1 = *p - '0';
				}
				else return _GW__DATA_NOT_ALLOWED;
			}
			else if(16 == base) {
				if(('0' <= *p)&&('9' >= *p)) {
					val1 = *p - '0';
				}
				else if(('a' <= *p)&&('f' >= *p)) {
					val1 = *p - 'a' + 10;
				}
				else if(('A' <= *p)&&('F' >= *p)) {
					val1 = *p - 'A' + 10;
				}
				else return _GW__DATA_NOT_ALLOWED;
			}
			else { //base 10.
				if(('0' <= *p)&&('9' >= *p)) {
					val1 = *p - '0';
				}
				else return _GW__DATA_NOT_ALLOWED;
			}

			if(val1 < base) {
				if((0xFFFFFFFF - val1) >= val0) {
					val0 += val1;
				}
				else return _GW__DATA_RANGE_OVER;
			}
			else return _GW__DATA_NOT_ALLOWED;

		}
		*out_value = val0;
		return _GW__NO_ERROR;
	}
	return _GW__ERROR;

}

/*********************************************************************
*
*       swapByte
*
*  Function description:
*
*  Parameters:
*
*  Return value:
*
*/
void swapByte(char *sour, int size)
{
	int i = 0;
	unsigned char *p = (unsigned char*) sour;
	unsigned char buf = 0;

	for( ; size > i; i++) {
		buf = *(p + i);
		*(p + i) = ((buf & 0x0F)<<4)|((buf & 0xF0)>>4);
	}
}

/*************************** End of file ****************************/
