/*
 * devTtyUART.c
 *
 *  Created on: 2012/7/11
 *      Author: cody
 */
//==========================================================
//  include
//==========================================================
//#include <unistd.h>
#include <stdio.h>
//#include <termios.h>
//#include <malloc.h>
#include <stdlib.h>
//#include <fcntl.h>
//#include <getopt.h>
#include <string.h>
//#include <sys/ioctl.h>
//#include <sys/types.h>
//#include <linux/ioctl.h>
#include <errno.h>
//#include <sys/stat.h>

//#include "gw_board.h"
#define _THREAD_PARSER_UART 	1
#if _THREAD_PARSER_UART

#include "devTtyDefine.h"
#include "apiTty.h"
extern char (*ParserGetc)(unsigned char *err);


//==========================================================
//  define
//==========================================================
#define _DEV_TTY_UART   "/dev/ttyBF0"

//==========================================================
//  typedef
//==========================================================

//==========================================================
//  variable & constant
//==========================================================
STR_DEVICE_TTY ttyUART = {
 .name = _DEV_TTY_UART
};

//==========================================================
//  Extern Function
//==========================================================

//==========================================================
//  Function
//==========================================================
int init_TtyUART(void)
{
	//printf("init_TtyUART\n");

	return init_Tty(&ttyUART);
}

int release_TtyUART(void)
{
	printf("release_TtyUART\n");

	return release_Tty(&ttyUART);
}

int detect_TtyUART(void)
{
	STR_DEVICE_TTY *p = (STR_DEVICE_TTY *) (&ttyUART);
	int err = 0;
#if 0
	ioctl(p->fd, 0x54FF, &err);
	if(0 == err) {
		close(p->fd);
		p->present = 0;
		return -1;
	}
#else
	p->present = 1;
#endif	
	return err;
}

int open_TtyUART(void)
{
	STR_DEVICE_TTY *p = (STR_DEVICE_TTY *) (&ttyUART);
	
	if(0 == p->present) {
		///p->fd = open( p->name, O_RDWR | O_NONBLOCK | O_NOCTTY | O_NDELAY);
		if (0 < p->fd) {
			p->present = 1;
			configUART_Tty(p);
			cleanAllBuffer_Tty(p);
		}
	}

	return p->present;
}

int close_TtyUART(void)
{
	STR_DEVICE_TTY *p = (STR_DEVICE_TTY *) (&ttyUART);
	close_Tty(p);
	return p->present;
}

int write_TtyUART(char *data, unsigned int size, unsigned int flag)
{
	STR_DEVICE_TTY *p = (STR_DEVICE_TTY *) (&ttyUART);
	if(_GW_IOWR_END == flag)	flag = _GW_IOWR_BUF;
	return write_Tty( p, data, size, flag);
}

int read_TtyUART(char *data, unsigned int size, unsigned int flag)
{
#if 1
	unsigned char err;
	STR_DEVICE_TTY *p = (STR_DEVICE_TTY *) (&ttyUART);
	int length = 0;
	//*data = ParserGetc(&err);
	*data = ParserGetc((unsigned char*)&err);	
	//length = err;
	if(err==0)length =1;
	else length = 0;
	return length;
#else
	STR_DEVICE_TTY *p = (STR_DEVICE_TTY *) (&ttyUART);
	int err = 0, length = 0;
	detect_TtyUART();
	if(_GW_IORD == flag) {
		length = read(p->fd, data, size);

		err = errno;
		if(0 == length) {
			if((err == 2)||(err == 9)||(err == 11)||(err == 19)||(err == 42)) {
				close_TtyUART();
			}
		}
		else if(0 < length) {
			//printf("length = %d\n", length);
			p->in_cnt += length;
		}
	}
	else {
	}
	return length;

#endif
}

//-----------------------------------------------------
//-----------------------------------------------------

int ctrl_TtyUART(unsigned int cmd, unsigned long arg)
{
	STR_DEVICE_TTY *p = (STR_DEVICE_TTY *) (&ttyUART);
	int err = 0;

	if(_GW_IOCTL_DEV_DETECT == cmd) {
		//if(p->present) {
		//	detect_TtyUART();
		//}
		err = p->present;
	}
	else if(_GW_IOCTL_TX_BUF_CLEAN == cmd) {
		cleanTx_Tty(p);
	}
	else if(_GW_IOCTL_RX_BUF_CLEAN == cmd) {
		cleanRx_Tty(p);
	}
	else if(_GW_IOCTL_DEV_PRESENT== cmd) {
		err = p->present;
	}
	else if(_GW_IOCTL_IS_TX_EMPTY == cmd) {
		err = isEmptyTx_Tty(p);
	}
	else if(_GW_IOCTL_IS_RX_EMPTY == cmd) {
	}
	else if(_GW_IOCTL_IS_BULKOUT == cmd) {
		err = isBulkoutTx_Tty(p);
	}
	else if(_GW_IOCTL_TERMINAL == cmd) {
		//err = config_Tty(p,(struct termios *) arg);
	}
	else if(_GW_IOCTL_GET_OUT_COUNT == cmd) {
		err = getOutCount_Tty(p);
	}
	else if(_GW_IOCTL_GET_IN_COUNT == cmd) {
		err = getInCount_Tty(p);
	}
	else {
	}
	return err;
}

#endif //_THREAD_PARSER_UART


