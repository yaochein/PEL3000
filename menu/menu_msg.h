/***********************************************************************************
 *    This file is modified from GDS830 menu5.h
 *
 *
 ***********************************************************************************/
#ifndef MENUMSG_H
#define MENUMSG_H

typedef char (*Func)();
typedef struct item{
        unsigned short x;       /*Display Location X*/
        unsigned short y;       /*Display Location Y*/
        GUI_BITMAP  *pbmp[MAX_LANGUAGE];   /*For multi-language. 2003.03.31*/
        unsigned short  length;  /*String width */
        }MITEM;
typedef struct items{
        MITEM          *iptr;       /*Point to the display item */
        Func           a;           /*Point to the respond Program */
        unsigned char  *i_condition;/*selected option */
        unsigned char  i_max;       /*selectable option */
        char           frame; /*0:
                                      1: a Item Bar inside the button*/
	}items;
typedef const items MITEMS;
typedef items* MENU;

#define NULL1 ((void*)0)

#endif   /* ifdef MENUMSG_H */

