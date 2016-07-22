/******************************************************************************
 * Filename:	gwMessage.c
 */
//==========================================================
//  include
//==========================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//#include <sys/types.h>
//#include <sys/ipc.h>
//#include <sys/msg.h>

#include "gwMsgQueue.h"
//typedef _mode_t	mode_t;
//==========================================================
//  define
//==========================================================

//----------------------------
//--- Message Queue Function ---

//==========================================================
//  typedef & struct
//==========================================================

//==========================================================
//  variable & constant
//==========================================================
int idMsgQueue = -1;

//==========================================================
//  Function
//==========================================================
int initMsgQueue(void)
{

    return 0;
}

void removeMsgQueue(void)
{

}

int sendMsgQueue(STR_MESSAGE_QUEUE *msg, long type)
{

    return 0;
}

int rcvMsgQueue(STR_MESSAGE_QUEUE *msg, long type)
{

    return 1;
}

int closeMsgQueue(void)
{

	return 1;
}

void changeMsgQueue(unsigned short mode)
{

}

