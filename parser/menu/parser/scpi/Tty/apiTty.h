#ifndef __API_TTY_H__
#define __API_TTY_H__

//==========================================================
//  include
//==========================================================
//#include <termios.h>

//==========================================================
//  define & enum
//==========================================================
#define _TTY_NO_ERROR		 0
#define _TTY_NO_PRESENT		-1
#define _TTY_DEVICE_CLOSE	-2
#define _TTY_RX_BUF_FULL	-3
#define _TTY_TX_BUF_FULL	-4
#define _TTY_RX_BUF_EMPTY	-5
#define _TTY_TX_BUF_EMPTY	-6

//==========================================================
//  struct & variable & constant
//==========================================================

//==========================================================
//  Function
//==========================================================
extern int unconfig_Tty(STR_DEVICE_TTY *pTty);
//extern int config_Tty(STR_DEVICE_TTY *pTty, struct termios *tio);
//extern int config_Tty(STR_DEVICE_TTY *pTty, int *tio);
extern int configDefault_Tty(STR_DEVICE_TTY *pTty);
extern int configUART_Tty(STR_DEVICE_TTY *pTty);
extern int init_Tty(STR_DEVICE_TTY *pTty);
extern int release_Tty(STR_DEVICE_TTY *pTty);
extern int cleanAllBuffer_Tty(STR_DEVICE_TTY *pTty);
extern int open_Tty(STR_DEVICE_TTY *pTty);
extern int close_Tty(STR_DEVICE_TTY *pTty);
extern int write_Tty(STR_DEVICE_TTY *pTty, char *addr, unsigned int size, unsigned int flag);
extern void cleanTx_Tty(STR_DEVICE_TTY *pTty);
extern void cleanRx_Tty(STR_DEVICE_TTY *pTtyp);
extern int isEmptyRx_Tty(STR_DEVICE_TTY *pTty);
extern int isEmptyTx_Tty(STR_DEVICE_TTY *pTty);
extern int isBulkoutTx_Tty(STR_DEVICE_TTY *pTty);
extern int getInCount_Tty(STR_DEVICE_TTY *pTty);
extern int getOutCount_Tty(STR_DEVICE_TTY *pTty);

#endif //__API_TTY_H__

