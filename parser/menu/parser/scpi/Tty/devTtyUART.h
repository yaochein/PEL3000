/*
 * devTtyUART.h
 *
 *  Created on: 2012/7/11
 *      Author: cody
 */

#ifndef DEVTTYUART_H_
#define DEVTTYUART_H_

//==========================================================
//  include
//==========================================================
//#include "gw_board.h"

#if 1

//==========================================================
//  define & enum
//==========================================================

//==========================================================
//  struct & variable & constant
//==========================================================

//==========================================================
//  Function
//==========================================================
extern int init_TtyUART(void);
extern int release_TtyUART(void);
extern int write_TtyUART(char *data, unsigned int size, unsigned int flag);
extern int read_TtyUART(char *data, unsigned int size, unsigned int flag);
extern int ctrl_TtyUART(unsigned int cmd, unsigned long arg);
extern int open_TtyUART(void);
extern int close_TtyUART(void);

#endif //_THREAD_PARSER_USB_RS232

#endif /* DEVTTYUART_H_ */
