/******************************************************************************
 * Filename:	devTxQueue.c
 */
//#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <fcntl.h>
//#include <getopt.h>
#include <string.h>
///#include <sys/ioctl.h>
//#include <sys/types.h>
///#include <linux/ioctl.h>
#include <errno.h>
//#include <semaphore.h>
#include "devTxQueue.h"

//==========================================================
//  DEBUG
//==========================================================

//==========================================================
//  Define
//==========================================================

//==========================================================
//  variable & const.
//==========================================================

//==========================================================
//  function
//==========================================================
static int ttyTxBufferInit(STR_TX_BUFFER *q)
{
	if(q) {
		q->ctr  = 0;
		q->inp  = 0;
		q->outp = 0;
		return 0;
	}
	else return -1;
}

static int ttyTxBufferPush(STR_TX_BUFFER *q, char *addr, int size)
{
	int i = 0;

	if(q && addr) {
		if(_TX_BUFFER_SIZE < (q->ctr + size)) {
			size = _TX_BUFFER_SIZE - q->ctr;
		}
		for(i = 0; i < size ; i++) {
			q->buf[q->inp] = addr[i];
			q->inp = (q->inp + 1) % _TX_BUFFER_SIZE;
            q->ctr++;
        }
		return size;
    }
    else return -1;
}

static int ttyTxBufferPop( STR_TX_BUFFER *q, int size)
{
	if(q && size) {
		if(q->ctr < size) {
			size = q->ctr;
		}
		q->outp = (q->outp + size) % _TX_BUFFER_SIZE;
		q->ctr -= size;
		return size;
	}
	else return -1;
}

static int ttyTxBufferFlush( STR_TX_BUFFER *q, int size)
{
	if(q) {
		if(q->ctr < size) {
			size = q->ctr;
		}
		q->inp = (q->inp < size) ? ((q->inp + _TX_BUFFER_SIZE) - size) : (q->inp - size);
		q->ctr -= size;
		return size;
	}
	else return -1;
}

static int ttyTxBufferDemand(STR_TX_BUFFER *q, unsigned long arg, int size)
{
	if(q) {
		if(_TX_BUFFER_SIZE < (q->ctr + size))	return -1;
		if(_TX_BUFFER_SIZE < (q->inp + size)) {
			size = _TX_BUFFER_SIZE - q->inp;
		}
		*((unsigned long*)arg) = (unsigned long)((char*) &(q->buf[q->inp]));
		return size;
    }
    else	return -1;
}

static int ttyTxBufferFree(STR_TX_BUFFER *q)
{
	if(q)	return (_TX_BUFFER_SIZE - q->ctr);
    else	return -1;
}

//==========================================================
//==========================================================
int ttyTxQueueInit(STR_TX_QUEUE *q)
{
	if(q) {
		q->count= 0;
		q->tp   = 0;
		q->tl   = 0;
		q->ctr  = 0;
		q->inp  = 0;
		q->outp = 0;
		ttyTxBufferInit(&q->buf);
		return 0;
	}
	else return -1;
}

int ttyTxQueueUsingCapacity(STR_TX_QUEUE *q)
{
	if(q) {
		return q->ctr;
	}
	else return -1;
}

int ttyTxQueueGetFirstIn(STR_TX_QUEUE *q, STR_TX_NODE *node)
{
	if(q && node) {
		if(0 == q->ctr) return -1;
		node->type = q->node[q->outp].type;
		node->addr = q->node[q->outp].addr;
		node->size = q->node[q->outp].size;
		return 0;
	}
	else return -1;
}

int ttyTxQueueGetLastIn(STR_TX_QUEUE *q, STR_TX_NODE *node)
{
	if(q && node) {
		if(0 == q->ctr) return -1;
		node->type = q->node[q->inp - 1].type;
		node->addr = q->node[q->inp - 1].addr;
		node->size = q->node[q->inp - 1].size;
		return 0;
	}
	else return -1;
}

int ttyTxQueuePop(STR_TX_QUEUE *q)
{
	if(q) {
		if(0 == q->ctr) return -1;
		if((_GW_IOWR_BUF == q->node[q->outp].type)||(_GW_IOWR_END == q->node[q->outp].type)) {
			ttyTxBufferPop(&(q->buf), q->node[q->outp].size);
		}
		q->outp = (q->outp + 1) % _TX_QUEUE_SIZE;
		q->ctr--;
		return 0;
	}
	else return -1;
}

int ttyTxQueueTempPush(STR_TX_QUEUE *q, char *addr, int size, int flag)
{

	if(q && addr) {
		if(_TX_QUEUE_SIZE <= (q->ctr + q->tl))	return -1;
		if((_GW_IOWR_BUF == flag)||(_GW_IOWR_END == flag)) {
			if(ttyTxBufferFree(&(q->buf)) < size)	return -1;
			int nodeSize = 0;
			unsigned long nodeAddr = 0;
			STR_TX_NODE node;

			nodeSize = ttyTxBufferDemand(&(q->buf), (unsigned long) &nodeAddr, size);
			if(0 > nodeSize)	return -1;
			ttyTxBufferPush(&(q->buf), addr, nodeSize);
			node.type = flag;
			node.addr = nodeAddr;
			node.size = nodeSize;
			if(0 < q->tl) {
				if(_GW_IOWR_BUF == q->node[q->tp -1].type) {
					if(_GW_IOWR_BUF == node.type) {
						if((q->node[q->tp-1].addr + q->node[q->tp-1].size) == node.addr) {
							q->node[q->tp-1].size += node.size;
							return node.size;
						}
					}
					else if(_GW_IOWR_END == node.type) {
						if((q->node[q->tp-1].addr + q->node[q->tp-1].size) == node.addr) {
							q->node[q->tp-1].size += node.size;
							q->node[q->tp-1].type = _GW_IOWR_END;
							return node.size;
						}
					}
					else {
					}
				}
			}
			q->node[q->tp].type = node.type;
			q->node[q->tp].addr = node.addr;
			q->node[q->tp].size = node.size;
			q->tp = (q->tp + 1) % _TX_QUEUE_SIZE;
			q->tl++;
			return node.size;
		}
		else if(_GW_IOWR_BULK == flag) {
			q->node[q->tp].type = _GW_IOWR_BULK;
			q->node[q->tp].addr = (unsigned long) addr;
			q->node[q->tp].size = size;
			q->tp = (q->tp + 1) % _TX_QUEUE_SIZE;
			q->tl++;
			return size;
		}
		else {
			return -1;
		}
	}
	else return -1;
}

int ttyTxQueueTempAccept(STR_TX_QUEUE *q)
{
	if(q) {
		if(0 < q->tl) {
			q->inp  = q->tp;
			q->ctr += q->tl;
			q->tl   = 0;
			return 0;
		}
		else return -1;
	}
	else return -1;
}

int ttyTxQueueTempFlush(STR_TX_QUEUE *q)
{
	if(q) {
		while(0 < q->tl) {
			if(_GW_IOWR_BUF == q->node[q->tp -1].type) {
				ttyTxBufferFlush( &(q->buf), q->node[q->tp -1].size);
			}
			q->tp = (0 == q->tp) ? (_TX_QUEUE_SIZE -1) : (q->tp - 1);
			q->tl--;
		}
		return 0;
	}
	else return -1;
}

int ttyTxQueueTempLength(STR_TX_QUEUE *q)
{
	if(q) {
		return q->tl;
	}
	else return -1;
}

int ttyTxQueueClean(STR_TX_QUEUE *q)
{
	if(q) {
		while(0 < q->ctr) {
			if((_GW_IOWR_BUF == q->node[q->outp].type)||(_GW_IOWR_END == q->node[q->outp].type)) {
				ttyTxBufferPop(&(q->buf), q->node[q->outp].size);
			}
			q->outp = (q->outp + 1) % _TX_QUEUE_SIZE;
			q->ctr--;
		}
		return 0;
	}
	else return -1;
}


//==========================================================
//==========================================================

