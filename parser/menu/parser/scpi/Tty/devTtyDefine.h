#ifndef __DEV_TTY_DEFINE_H__
#define __DEV_TTY_DEFINE_H__

//==========================================================
//  include
//==========================================================
//#include <pthread.h>
//#include <termios.h>

#include "devTxQueue.h"

//==========================================================
//  define
//==========================================================
#define _CR		0x13 //Carriage Return.
#define _LF		0x0A //Linefeed.


#define	_DEV_UART				1
#define	_DEV_LAN_WEB			2
#define	_DEV_GPIB				3
#define	_DEV_USB_CDC			4
#define	_DEV_USB_TMC_DEVICE		5
#define	_DEV_USB_TMC_HOST		6
#define	_DEV_USB_RS232			7
#define	_DEV_LUA				8
#define	_DEV_INET_SOCKET		9
#define	_DEV_MACHINE			10
#define _DEV_TDK_UART			11
#define _DEV_TIMETASK			12


#define _DEV_UNIX_SOCKET		_DEV_LAN_WEB

//----------------------------------------------------------
#define _GW_IOCTL_DEV_DETECT	0 //Detect the Device.
#define _GW_IOCTL_DEV_PRESENT	1 //Device present?
#define _GW_IOCTL_TX_BUF_CLEAN	2 //clean Tx-buffer.
#define _GW_IOCTL_IS_TX_EMPTY	3 //Is Tx-buffer empty?
#define _GW_IOCTL_RX_BUF_CLEAN	4 //clean Rx-buffer.
#define _GW_IOCTL_IS_RX_EMPTY	5 //Is Rx-buffer empty?
#define _GW_IOCTL_SET_ADDRESS	6 //Set address of GPIB.
#define _GW_IOCTL_QUERY_ADDRESS	7 //Query address of GPIB.
// #define _GW_IOCTL_REQ_BULKOUT	8 //Request Bulk-output.
#define _GW_IOCTL_IS_BULKOUT	9 //Is Bulk-output?
#define _GW_IOCTL_TERMINAL		10//Configure terminal.
#define _GW_IOCTL_GET_OUT_COUNT	11//Currently the number of output bytes.
#define _GW_IOCTL_GET_IN_COUNT	12//How many bytes are currently receiving.
#define _GW_IOCTL_GET_REG_STB		13
#define _GW_IOCTL_SET_REG_STB		14
#define _GW_IOCTL_GET_STATUS		15
#define _GW_IOCTL_GET_TX_BUF_SIZE	16
#define _GW_IOCTL_GET_TX_TOTAL_SIZE 17//Get number of total bytes(scpi command size) that driver(kernel space) have received.
#define _GW_IOCTL_SET_TX_TOTAL_SIZE 18//Send scpi command size(total) to kernel space(For GPIB only)
#define _GW_IOCTL_ADDITIONAL	0xFF

#define _GW_IORD	1	//read from device.

//==========================================================
//  typedef & struct
//==========================================================
#define _READ_PAGE		512
#define _WRITE_PAGE		512

typedef struct pthread_mutex_t_ * pthread_mutex_t;
//==========================================================
//  typedef & struct
//==========================================================
typedef struct _STR_DEVICE_TTY {
	int		fd;
	int		present;
	STR_TX_QUEUE tx;
	unsigned int in_cnt, out_cnt;
	//struct termios oldtio, newtio;
	int oldtio, newtio;
	char name[32];
	pthread_mutex_t w_lock;
} STR_DEVICE_TTY;

//==========================================================
//  variable & constant
//==========================================================

#endif //__DEV_TTY_DEFINE_H__

