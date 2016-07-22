#ifndef __DEV_TX_QUEUE_H__
#define __DEV_TX_QUEUE_H__

//==========================================================
//  include
//==========================================================

//==========================================================
//  define
//==========================================================
#define _TX_BUFFER_SIZE	1024
#define _TX_QUEUE_SIZE	64

#define _GW_IOWR_END		0x00	//(LF + ^End).
#define _GW_IOWR_DEV		0x01	//write to device.
#define _GW_IOWR_BUF		0x02	//For data is a local variable. Complete data is written to the temporary buffer.
#define _GW_IOWR_BULK		0x03	//For data is global variable. Write bulk-data.
#define _GW_IOWR_BUF_APP	0x04	//approve temporary data.
#define _GW_IOWR_BUF_CLN	0x05	//clean temporary data.

//==========================================================
//  typedef & struct
//==========================================================
typedef struct _STR_TX_BUFFER {
	int  ctr;	//stored data length.
	int  inp;	//input-point of queue.
	int  outp;	//output-point of queue.
	char buf[_TX_BUFFER_SIZE];	//The address of Queue.
} STR_TX_BUFFER;

typedef struct _STR_TX_NODE {
	int				type;	//0:buffer, 1:constant data or block data.
	unsigned int	addr;	//Data storage address.
	int				size;	//Data size.
} STR_TX_NODE;

typedef struct _STR_TX_QUEUE {
	int count;	//Output counter.
	int tp;		//temporary stored data point.
	int tl;		//temporary stored data length.
    int ctr;	//stored data length.
    int inp;	//input-point of queue.
    int outp;	//output-point of queue.
    STR_TX_NODE  node[_TX_QUEUE_SIZE]; //The address of Queue.
    STR_TX_BUFFER buf;
} STR_TX_QUEUE;

//==========================================================
//  variable & const.
//==========================================================

//==========================================================
//  function
//==========================================================
extern int ttyTxQueueInit(STR_TX_QUEUE *q);
extern int ttyTxQueueUsingCapacity(STR_TX_QUEUE *q);
extern int ttyTxQueueGetFirstIn(STR_TX_QUEUE *q, STR_TX_NODE *node);
extern int ttyTxQueueGetLastIn(STR_TX_QUEUE *q, STR_TX_NODE *node);
extern int ttyTxQueuePop(STR_TX_QUEUE *q);
extern int ttyTxQueueTempPush(STR_TX_QUEUE *q, char *addr, int size, int flag);
extern int ttyTxQueueTempAccept(STR_TX_QUEUE *q);
extern int ttyTxQueueTempFlush(STR_TX_QUEUE *q);
extern int ttyTxQueueTempLength(STR_TX_QUEUE *q);
extern int ttyTxQueueClean(STR_TX_QUEUE *q);

#endif //__DEV_TX_QUEUE_H__

