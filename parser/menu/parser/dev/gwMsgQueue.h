#ifndef __GW_MESSAGE_QUEUE_H__
#define __GW_MESSAGE_QUEUE_H__

//==========================================================
//  include
//==========================================================

//==========================================================
//  define
//==========================================================
#define _MSQ_BUF_SIZE	8

//==========================================================
//  typedef & struct
//==========================================================
typedef struct _STR_MESSAGE_QUEUE {
	long type;
	union {
		char buf[_MSQ_BUF_SIZE];
		struct {
			unsigned long func;
			unsigned long data;
		};
	};
} STR_MESSAGE_QUEUE;

//==========================================================
//  variable & constant
//==========================================================

//==========================================================
//  Function
//==========================================================
extern int initMsgQueue(void);
extern void removeMsgQueue(void);
extern int sendMsgQueue(STR_MESSAGE_QUEUE *msg, long type);
extern int rcvMsgQueue(STR_MESSAGE_QUEUE *msg, long type);
extern int closeMsgQueue(void);

#endif //__GW_MESSAGE_QUEUE_H__

