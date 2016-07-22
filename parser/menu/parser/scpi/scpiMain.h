#ifndef __SCPI_MAIN_H__
#define __SCPI_MAIN_H__

//==========================================================
//  include
//==========================================================
//#include <unistd.h>
//#include <sys/stat.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <sys/ipc.h>
//#include <sys/msg.h>
//#include <sys/ioctl.h>

//#include <linux/types.h>
//#include <linux/netlink.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <fcntl.h>
//#include <getopt.h>
#include <errno.h>
//#include <pthread.h>
//#include <semaphore.h>
#include <ctype.h>

//#include "gw_board.h"
//#include "../dev/gwSemaphore.h"
#include "scpiParser.h"
#include "scpiRegister.h"
#include "scpiNode.h"
#include "scpiAPI.h"
#include "tty/devTtyDefine.h"
//#include "tty/devTtyUSB.h"
//#include "tty/devTtyGS.h"
#include "tty/devTtyUART.h"
//#include "tty/devUsbTmcHost.h"
//#include "../menu/data/dataMenu.h"

//==========================================================
//  define & enum
//==========================================================

//==========================================================
//  struct & variable & constant
//==========================================================

//==========================================================
//  DEBUG
//==========================================================
#if 1
	#define _DEBUG_SHOW_VALUE(x,y)	printf("%s%d\n", x, y)
#else
	#define _DEBUG_SHOW_VALUE(x,y)
#endif

#if 1
	#define _DEBUG_SHOW_MESSAGE(x)	printf("%s", x)
#else
	#define _DEBUG_SHOW_MESSAGE(x)
#endif

#if 1
	#define _DEBUG_SHOW_THREAD_ERROR(x)	printf("<%s>Thread Initial Error!\n", x)
#else
	#define _DEBUG_SHOW_THREAD_ERROR(x)
#endif

//==========================================================
//  define
//==========================================================
#define _DEVICE_NO_PRESENT	0
#define _DEVICE_PRESENT		1

//==========================================================
//  typedef
//==========================================================

//==========================================================
//  struct & variable & constant
//==========================================================

//==========================================================
//  Function
//==========================================================
extern int isIntegerPoint(unsigned long addr);
extern int isParserThreadError(STR_PARSER *p, char *name);
extern int scpiRequestProcess(STR_PARSER *p);
extern int scpiRequestReturn(STR_PARSER *p);

#endif //__SCPI_MAIN_H__

