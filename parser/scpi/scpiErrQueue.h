#ifndef __SCPI_ERROR_QUEUE_H__
#define __SCPI_ERROR_QUEUE_H__

#include "scpiStruct.h"

extern int initErrorQueue(STR_ERROR_QUEUE *p);
extern int pushErrorQueue(STR_ERROR_QUEUE *p, int err);
extern int getErrorQueue(STR_ERROR_QUEUE *p);
extern int isEmptyErrorQueue(STR_ERROR_QUEUE *p);
#endif //__SCPI_ERROR_QUEUE_H__

