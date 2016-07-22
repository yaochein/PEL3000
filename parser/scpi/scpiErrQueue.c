
//==========================================================
//  include
//==========================================================
//#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//#include "gw_board.h"
//#include "gw_CLib.h"
//#include "includes.h"

#include "scpiStruct.h"
#include "scpiError.h"
#include "tty/devTtyDefine.h"
extern char ErrQueueComm[16][64];
extern char disErrQ[64];

extern STR_PARSER_COMD comd_UART;


//==========================================================
//  Debug
//==========================================================

//==========================================================
//  Define
//==========================================================

//==========================================================
//  typedef & struct
//==========================================================

//==========================================================
//  variable & constant
//==========================================================

//==========================================================
//  Function
//==========================================================

int initErrorQueue(STR_ERROR_QUEUE *p)
{
	p->cnt    = 0;
	p->outptr = 0;
	p->inptr  = 0;
	p->buf[0] = 0;
	return 0;
}

int pushErrorQueue(STR_ERROR_QUEUE *p, int err)
{
	extern volatile unsigned short SysRedrawFlag;
	
	SysRedrawFlag |= 0x10;//ERROR_UPDATA;
	if((p->cnt < _ERROR_QUEUE_SIZE)&&(_ERR_000_No_Error != err)) {
		if((_ERROR_QUEUE_SIZE -1)== p->cnt){
			p->buf[p->inptr] = _ERR_350_Queue_overflow;
		}else {
			p->buf[p->inptr] = err;
			char i,j,k,c1=0;	
			for (k=0; k<64; k++)	ErrQueueComm[p->inptr][k] = 0x00;
			for (i=0;i<5;i++){
				j = comd_UART.len[i];
				if (j==0)break;
				ErrQueueComm[p->inptr][c1++]=':';
				for (k=0;k<j;k++)	ErrQueueComm[p->inptr][c1++] = comd_UART.com[i][k];
			}

		}
		p->cnt++;
		p->inptr = (p->inptr + 1) % _ERROR_QUEUE_SIZE;
		return 0;
	}
	else return -1;
}

int getErrorQueue(STR_ERROR_QUEUE *p)
{
	int err = 0;
	char i=0;
	if(p->cnt > 0) {
		err = p->buf[p->outptr];

		if(err){
			for (i=0;i<32;i++){
				disErrQ[i]=ErrQueueComm[p->outptr][i];
				if(ErrQueueComm[p->outptr][i+1]=='0')break;
			}
		}else{
			for (i=0;i<32;i++)	disErrQ[i]='0';			
		}	
		
		p->cnt--;
		p->outptr = (p->outptr + 1) % _ERROR_QUEUE_SIZE;
	}
	return err;
}

int isEmptyErrorQueue(STR_ERROR_QUEUE *p)
{
	return p->cnt;
}

