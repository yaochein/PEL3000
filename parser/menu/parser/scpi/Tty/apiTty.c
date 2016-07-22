/******************************************************************************
 * Filename:	detectDev.c
 ******************************************************************************/

//==========================================================
//  include
//==========================================================
//#include <unistd.h>
#include <stdio.h>
//#include <termios.h>
#include <stdlib.h>
//#include <fcntl.h>
//#include <getopt.h>
#include <string.h>
//#include <sys/ioctl.h>
//#include <sys/types.h>
//#include <linux/ioctl.h>
#include <errno.h>
//#include <sys/stat.h>
//#include <semaphore.h>

//#include "gw_board.h"
#include "devTtyDefine.h"
#include "apiTty.h"
//#include "../menuDefine.h"
//#include "../data/dataMenu.h"


//==========================================================
//  debug
//==========================================================
#if 0
	#define _DEBUG_SHOW_LOCK_FAIL(x,y)	printf("Mutex<%s> %s failed.\n", x, y);
#else
	#define _DEBUG_SHOW_LOCK_FAIL(x,y)
#endif


#if 0
	#define _DEBUG_SHOW_OPEN_DEVICE(x)	printf("\nOpen Device(%s)\n", x)
#else
	#define _DEBUG_SHOW_OPEN_DEVICE(x)
#endif

#if 0
	#define _DEBUG_SHOW_CLOSE_DEVICE(x, y, z)	printf("\nDevice(%s) close(%d): %s\n", x, y, z)
#else
	#define _DEBUG_SHOW_CLOSE_DEVICE(x, y, z)
#endif


#if 0
	#define _DEBUG_SHOW_STATE(x,y)	printf("State=%d, errno=%d\n", x,y)
#else
	#define _DEBUG_SHOW_STATE(x,y)
#endif

//==========================================================
//  define
//==========================================================
#define _TTY_WRITE_PAGE	10240

//==========================================================
//  typedef
//==========================================================

//==========================================================
//  variable & constant
//==========================================================

//Uart Baud Rate : 
//1200(0) 2400(1) 4800(2) 9600(3) 19200(4) 38400(5) 57600(6) 115200(7)
const unsigned int UART_TIMEOUT[]	= { 6666, 3333, 1666, 
										833,  416,  208,
									    138,  69};
/*
const unsigned int UART_BAUD[] 		= { B1200, 	B2400, 	B4800, 
										B9600, 	B19200, B38400, 
										B57600, B115200};
const unsigned int UART_BITS[] 		= {	CS7, 	CS8};
const unsigned int UART_PRIORITY[] 	= {	0, 		PARODD,	PARENB};
const unsigned int UART_STOPBITS[] 	= {	0, 		CSTOPB};
*/


//==========================================================
//  Function
//==========================================================
int unconfig_Tty(STR_DEVICE_TTY *pTty)
{
	/*
	if(0 < pTty->fd) {
		tcsetattr(pTty->fd,TCSANOW, &(pTty->oldtio));
		return _TTY_NO_ERROR;
	}
	else
		*/
		return _TTY_NO_PRESENT;
}

//int config_Tty(STR_DEVICE_TTY *pTty, struct termios *tio)
int config_Tty(STR_DEVICE_TTY *pTty, int *tio)
{
	/*
	if(0 < pTty->fd) {

		struct termios *pNew = (struct termios *) (&pTty->newtio);
		memcpy(pNew, tio, sizeof(struct termios));
		tcflush(pTty->fd, TCIFLUSH);
		tcsetattr(pTty->fd,TCSANOW,pNew);
	    return _TTY_NO_ERROR;
	}
	else
		*/
		return _TTY_NO_PRESENT;
}

int configUART_Tty(STR_DEVICE_TTY *pTty)
{
/*
	if(0 < pTty->fd) {
		struct termios *pOld = (struct termios *) (&pTty->oldtio);
		struct termios *pNew = (struct termios *) (&pTty->newtio);

	    if( tcgetattr(pTty->fd, pOld) < 0)
	    {
	            perror("tcgetattr");
	            return -1;
	    }
		bzero(pNew, sizeof(struct termios));

		pNew->c_cflag =  UART_BAUD[Conf.uart.baud] 
						|UART_BITS[Conf.uart.bits] 
						|UART_PRIORITY[Conf.uart.parity]
						|UART_STOPBITS[Conf.uart.sbit]
						|CLOCAL 
						|CREAD;
		pNew->c_iflag = IGNPAR;
		pNew->c_oflag = 0;
		pNew->c_lflag = 0;
	 	pNew->c_cc[VTIME] = 0;
		pNew->c_cc[VMIN]  = 1;

		tcflush(pTty->fd, TCIFLUSH);
		tcsetattr(pTty->fd,TCSANOW,pNew);
	    return _TTY_NO_ERROR;
	}
	else
*/
		return _TTY_NO_PRESENT;
}

int configDefault_Tty(STR_DEVICE_TTY *pTty)
{
	/*
	if(0 < pTty->fd) {
		struct termios *pOld = (struct termios *) (&pTty->oldtio);
		struct termios *pNew = (struct termios *) (&pTty->newtio);

	    if( tcgetattr(pTty->fd, pOld) < 0)
	    {
	            perror("tcgetattr");
	            return -1;
	    }
		bzero(pNew, sizeof(struct termios));
		pNew->c_cflag = B9600 | CS8 | CLOCAL | CREAD;
		pNew->c_iflag = IGNPAR;
		pNew->c_oflag = 0;
		pNew->c_lflag = 0;
	 	pNew->c_cc[VTIME] = 0;
		pNew->c_cc[VMIN]  = 1;

		tcflush(pTty->fd, TCIFLUSH);
		tcsetattr(pTty->fd,TCSANOW,pNew);
	    return _TTY_NO_ERROR;
	}
	else
		*/
		return _TTY_NO_PRESENT;
}

int init_Tty(STR_DEVICE_TTY *pTty)
{
	/*
	ttyTxQueueInit(&(pTty->tx));
	pTty->fd		= 0;
	pTty->present	= 0;
	pTty->in_cnt	= 0;
	pTty->out_cnt	= 0;
	if(pthread_mutex_init(&pTty->w_lock, NULL) !=0) {
		_DEBUG_SHOW_LOCK_FAIL(pTty->name, "initialization");
		return -1;
	}
	*/
	return _TTY_NO_ERROR;
}

int release_Tty(STR_DEVICE_TTY *pTty)
{
	/*
	if(0 < pTty->fd)	close(pTty->fd);
	pTty->fd		= 0;
	pTty->present	= 0;
	pTty->in_cnt	= 0;
	pTty->out_cnt	= 0;
	if(pthread_mutex_destroy(&pTty->w_lock) !=0) {
		_DEBUG_SHOW_LOCK_FAIL(pTty->name, "release");
        return -1;
    }
    */
	return _TTY_NO_ERROR;
}

int cleanAllBuffer_Tty(STR_DEVICE_TTY *pTty)
{
	//--- Clean Tx and Rx Buffer ,and bulk point ---//
	/*
	pTty->in_cnt	= 0;
	pTty->out_cnt	= 0;
	ttyTxQueueInit(&(pTty->tx));
	*/
	return 0;
}

int open_Tty(STR_DEVICE_TTY *pTty)
{
	/*
	if(0 == pTty->present) {
		pTty->fd = open( pTty->name, O_RDWR | O_NONBLOCK | O_NOCTTY | O_NDELAY);
		if (0 < pTty->fd) {
			pTty->present = 1;
			configDefault_Tty(pTty);
			cleanAllBuffer_Tty(pTty);
			_DEBUG_SHOW_OPEN_DEVICE(pTty->name);
		}
		else {
		}
	}
	*/
	return pTty->present;
}

int close_Tty(STR_DEVICE_TTY *pTty)
{
	int err = -1;
/*
	if(pTty->present) {
		pTty->present = 0;
		err = close(pTty->fd);
		pTty->fd = 0;
		cleanAllBuffer_Tty(pTty);
		_DEBUG_SHOW_CLOSE_DEVICE(pTty->name, err, strerror(err));
	}
*/
	return err;
}

int write_Tty(STR_DEVICE_TTY *pTty, char *addr, unsigned int size, unsigned int flag)
{
	int err = -1;
	//STR_TX_QUEUE *q = &(pTty->tx);
	/*
	if(q) {
		pthread_mutex_lock(&pTty->w_lock);
		if((_GW_IOWR_BUF == flag)||(_GW_IOWR_END == flag)) {
			int nodeSize1 = 0, nodeSize2 = 0;
			nodeSize1 = ttyTxQueueTempPush(q, addr, (int)size, flag);
			if((0 < nodeSize1)&&(nodeSize1 < size)) {
				nodeSize2 = ttyTxQueueTempPush(q, (addr + nodeSize1), (int)((int)size - nodeSize1), flag);
			}
			if(0 < nodeSize2)	err = nodeSize1 + nodeSize2;
			else				err = nodeSize1;
		}
		else if(_GW_IOWR_BULK == flag) {
			err = ttyTxQueueTempPush(q, addr, (int)size, flag);
		}
		else if(_GW_IOWR_DEV == flag) {
			if(ttyTxQueueUsingCapacity(q) > 0) {
				STR_TX_NODE node;
				ttyTxQueueGetFirstIn(q, &node);
				if(node.size > q->count) {
					int diff = 0;
					if(0 == strcmp("/dev/ttygs", pTty->name)){
						if(0 == ((node.size - q->count)%64)) diff = 1;
					}
					err = write(pTty->fd, (char *)(node.addr + q->count), (node.size - q->count - diff));

					if(0 < err) {
						q->count += err;
					}
				}
				if(node.size <= q->count) {
					ttyTxQueuePop(q);
					q->count = 0;
				}
			}
			else err = -1;
		}
		else if(_GW_IOWR_BUF_APP == flag) {
			err = ttyTxQueueTempAccept(q);
		}
		else if(_GW_IOWR_BUF_CLN == flag) {
			err = ttyTxQueueTempFlush(q);
		}
		else {
			err = -1;
		}
		pthread_mutex_unlock(&pTty->w_lock);
    }
	*/
	return err;
}

void cleanTx_Tty(STR_DEVICE_TTY *pTty)
{
	/*
	pthread_mutex_lock(&pTty->w_lock);
	ttyTxQueueClean(&(pTty->tx));
	pthread_mutex_unlock(&pTty->w_lock);
	*/
}

void cleanRx_Tty(STR_DEVICE_TTY *pTty)
{
}

int isEmptyRx_Tty(STR_DEVICE_TTY *pTty)
{
	return 0;
}

int isEmptyTx_Tty(STR_DEVICE_TTY *pTty)
{
	int err = 0;
/*
	pthread_mutex_lock(&pTty->w_lock);
	err = ttyTxQueueUsingCapacity(&(pTty->tx));
	pthread_mutex_unlock(&pTty->w_lock);
*/
	return err;
}

int isBulkoutTx_Tty(STR_DEVICE_TTY *pTty)
{
	return 0;
}

int getInCount_Tty(STR_DEVICE_TTY *pTty)
{
	int err = 0;
/*
	pthread_mutex_lock(&pTty->w_lock);
	err = pTty->in_cnt;
	pTty->in_cnt = 0;
	pthread_mutex_unlock(&pTty->w_lock);
*/
	return err;
}

int getOutCount_Tty(STR_DEVICE_TTY *pTty)
{
	int err = 0;
/*
	pthread_mutex_lock(&pTty->w_lock);
	err = pTty->out_cnt;
	pTty->out_cnt = 0;
	pthread_mutex_unlock(&pTty->w_lock);
*/
	return err;
}

