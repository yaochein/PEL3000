
//==========================================================
//  include
//==========================================================
//#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scpiStruct.h"
#include "scpiID.h"
#include "scpiError.h"
#include "scpiNode.h"
#include "scpiUnit.h"
#include "scpiErrQueue.h"
#include "scpiRegister.h"
#include "tty/devTtyDefine.h"
#include "scpiAPI.h"
#include "tty/devTxQueue.h"

//==========================================================
//  Debug
//==========================================================
#if 0
	#define _DEBUG_SHOW_LOCK_FAIL(x)	printf("Mutex<%s> initialization failed.\n", x);
#else
	#define _DEBUG_SHOW_LOCK_FAIL(x)
#endif

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
int scpi_InterfaceRequest(STR_INTF *intf, int cmd, unsigned long arg)
{
	return intfRequest_SetData(intf, cmd, arg);
}

//-----------------------------------------------
//--- scpi_StatusUpdate ---
//return :	0,1 => MSS(RQS) status.
//			-1=> error.
int scpi_StatusUpdate(STR_PARSER *p)
{	
	if(p) {
		STR_INTF *reg = p->pInterface;
		int err = p->pComd->err;
		int error_queue = scpi_IsEmptyErrorQueue(p);
		int output_buffer = scpi_IsEmptyOutputBuffer(p);
		if(0 == reg->status.use)	return -1;
				
		//--- ESR ---//
		reg->esr.cme |= ((_ERR_100_Command_error <= err)&&(_ERR_200_Execution_error > err)) ? 1 : 0;
		reg->esr.exe |= ((_ERR_200_Execution_error <= err)&&(_ERR_300_Device_specific_error > err)) ? 1 : 0;
		reg->esr.dde |= ((_ERR_300_Device_specific_error <= err)&&(_ERR_400_Query_error > err)) ? 1 : 0;
		reg->esr.que |= ((_ERR_400_Query_error <= err)&&(_ERR_500_Power_on > err)) ? 1 : 0;
		reg->esr.pon |= ((_ERR_500_Power_on <= err)&&(_ERR_600_User_request > err)) ? 1 : 0;
		reg->esr.urq |= ((_ERR_600_User_request <= err)&&(_ERR_700_Request_control > err)) ? 1 : 0;
		reg->esr.rqc |= ((_ERR_700_Request_control <= err)&&(_ERR_800_Operation_complete> err)) ? 1 : 0;
		//--- STB ---//
		reg->stb.err = (error_queue > 0) ? 1 : 0;								//ESR bit 1:  ERR
		reg->stb.csum= ((reg->csum.enab.data & reg->csum.even.data)==0) ? 0 : 1;//ESR bit 2:  CSUM
		reg->stb.ques=((reg->ques.enab.data & reg->ques.even.data)==0)? 0:1;	//ESR bit 3:  QUES
		reg->stb.mav = (output_buffer > 0) ? 1 : 0;								//ESR bit 4:  MAV	
		reg->stb.esb = (reg->esr.data & reg->ese.data) ? 1 : 0;					//ESR bit 5:  ESB	
		reg->stb.oper= ((reg->oper.enab.data & reg->oper.even.data)==0)? 0:1;	//ESR bit 7:  OPER
		reg->stb.mss = (reg->stb.data & reg->sre.data & _INTF_MASK_RQS) ? 1 :0;	//ESR bit 6:  MSS
		err = reg->stb.mss;
		return err;
	}	
	return -1;
}

//-----------------------------------------------
//--- scpi_InitErrorQueue ---
//return :	0 => no error.
//			-1=> error.
int scpi_InitErrorQueue(STR_PARSER *p)
{
	if(p) return initErrorQueue( &(p->errQueue));
	else  return -1;
}

//-----------------------------------------------
//--- scpi_GetErrorString ---
//return :	0 => error.
char* scpi_GetErrorString(STR_PARSER *p)
{
	if(p)	return (char*)Error[getErrorQueue( &(p->errQueue))];
	else	return 0;
}

//-----------------------------------------------
//--- scpi_GetErrorQueue ---
//return :	0 => no error.
//			-1=> error.
int scpi_GetErrorQueue(STR_PARSER *p)
{ //only use "System:error?"
	if(p)	return getErrorQueue( &(p->errQueue));
	else	return -1;
}

//-----------------------------------------------
//--- scpi_IsEmptyErrorQueue ---
//return : Non-zero => have data.
//			0 => empty.
//			-1=> error.
int scpi_IsEmptyErrorQueue(STR_PARSER *p)
{
	if(p)	return isEmptyErrorQueue( &(p->errQueue));
	else	return -1;
}

//-----------------------------------------------
//--- scpi_SetCommandError ---
//return :	0 => no error.
//			-1=> error.
int scpi_SetCommandError(STR_PARSER *p, int err)
{
	if(p) {
		if(_DEV_LUA == p->dev) {
			pushErrorQueue( &(p->errQueue), err);
			return 0;
		}
		else if(p->pComd) {
			p->pComd->err = err;
//			printf("Command Error<%d>:%s\n", err, Error[err]);
			return 0;
		}
	}
	return -1;
}

//-----------------------------------------------
//--- scpi_GetCommandError ---
//return :	0 => no error.
//			>0=> parse error.
//			-1=> error.
int scpi_GetCommandError(STR_PARSER *p)
{
	if(p) {
		if(p->pComd) {
			return p->pComd->err;
		}
	}
	return -1;
}

//-----------------------------------------------
//--- scpi_IsQueryChain ---
//return :	0 => no command line.
//			1 => command lone.
//			-1=> error.
int scpi_IsQueryChain(STR_PARSER *p)
{
	if(p)	return p->countQuery;
	else	return -1;
}

//-----------------------------------------------
//--- scpi_IsQueryCommand ---
//return :	0 => setting command.
//			1 => query command.
//			-1=> error.
int scpi_IsQueryCommand(STR_PARSER *p)
{
	if(p)	return p->pData->query;
	else	return -1;
}

//-----------------------------------------------
//--- scpi_GetNumericSuffix ---
//return :	positive => Numeric Suffix data.
//			-1=> error or no suffix.
int scpi_GetNumericSuffix(STR_PARSER *p, int level)
{
	if(p)	return p->pData->suffix[level];
	else	return -1;
}

//-----------------------------------------------
//--- scpi_IsThereParameters ---
//return :	positive => Number of parameters.
//			-1=> error.
int scpi_IsThereParameters(STR_PARSER *p)
{
	if(p)	return p->pData->number;
	else	return -1;
}

//-----------------------------------------------
//--- scpi_IsIntegerParameters ---
//return :	0 => not Integer Parameters.
//			1 => Integer Parameters.
//			-1=> error.
int scpi_IsIntegerParameters(STR_PARSER *p, int number)
{
	if(p) {
		if(number < p->pData->number) {
			return p->pData->info[number].type.num;
		}
	}
	return -1;
}

//-----------------------------------------------
//--- scpi_IsKeywordParameters ---
//return :	0 => not Keyword Parameters.
//			1 => Keyword Parameters.
//			-1=> error.
int scpi_IsKeywordParameters(STR_PARSER *p, int number)
{
	if(p) {
		if(number < p->pData->number) {
			return p->pData->info[number].type.kw;
		}
	}
	return -1;
}

//-----------------------------------------------
//--- scpi_IsStringParameters ---
//return :	0 => not String Parameters.
//			1 => String Parameters.
//			-1=> error.
int scpi_IsStringParameters(STR_PARSER *p, int number)
{
	if(p) {
		if(number < p->pData->number) {
			return p->pData->info[number].type.str;
		}
	}
	return -1;
}

//-----------------------------------------------
//--- scpi_IsFloatParameters ---
//return :	0 => not Float Parameters.
//			1 => Float Parameters.
//			-1=> error.
int scpi_IsFloatParameters(STR_PARSER *p, int number)
{
	if(p) {
		if(number < p->pData->number) {
			return p->pData->info[number].type.fl;
		}
	}
	return -1;
}
//-----------------------------------------------
//--- scpi_IsExpressionParameters ---
//return :	0 => not Expression Parameters.
//			1 => Expression Parameters.
//			-1=> error.
int scpi_IsExpressionParameters(STR_PARSER *p, int number)
{
	if(p) {
		if(number < p->pData->number) {
			return p->pData->info[number].type.expr;
		}
	}
	return -1;
}
//-----------------------------------------------
//--- scpi_IsBlockParameters ---
//return :	0 => not Block Parameters.
//			1 => Block Parameters.
//			-1=> error.
int scpi_IsBlockParameters(STR_PARSER *p, int number)
{
	if(p) {
		if(number < p->pData->number) {
			return p->pData->info[number].type.block;
		}
	}
	return -1;
}

//-----------------------------------------------
//--- scpi_IsListParameters ---
//return :	0 => not List Parameters.
//			1 => List Parameters.
//			-1=> error.
int scpi_IsListParameters(STR_PARSER *p, int number)
{
	if(p) {
		if(number < p->pData->number) {
			return p->pData->info[number].type.list;
		}
	}
	return -1;
}
//-----------------------------------------------
//--- scpi_IsOptionParameters ---
//return :	0 => not Option Parameters.
//			1 => Option Parameters.
//			-1=> error.
int scpi_IsOptionParameters(STR_PARSER *p, int number)
{
	if(p) {
		if(number < p->pData->number) {
			return p->pData->info[number].type.opt;
		}
	}
	return -1;
}

//-----------------------------------------------
//--- scpi_GetIntegerParameters ---
//return :	0 => no error.
//			-1=> error.
int scpi_GetIntegerParameters(STR_PARSER *p, int number, int *data)
{
	if(p) {
		if(number < p->pData->number) {
			if(p->pData->info[number].type.num) {
				*data =  *((int*)(p->pData->info[number].addr));
				return 0;
			}
		 }
	}
	return -1;
}

//-----------------------------------------------
//--- scpi_GetKeywordParameters ---
//return :	0 => no error.
//			-1=> error.
int scpi_GetKeywordParameters(STR_PARSER *p, int number, int *data)
{
	if(p) {
		if(number < p->pData->number) {
			if(p->pData->info[number].type.kw) {
				*data = *((int*)(p->pData->info[number].addr));
				return 0;
			}
		}
	}
	return -1;
}

//-----------------------------------------------
//--- scpi_GetStringParameters ---
//return :	0 => no error and String Size (include '\0').
//			1 => empty string , '\0'.
//			-1=> error.
int scpi_GetStringParameters(STR_PARSER *p, int number, unsigned int *addr)
{
	if(p) {
		if(number < p->pData->number) {
			if(p->pData->info[number].type.str) {
				*addr = (unsigned int) p->pData->info[number].addr;
				return p->pData->info[number].size;
			}
		}
	}
	return -1;
}

//-----------------------------------------------
//--- scpi_GetFloatParameters ---
//return :	0 => no error.
//			-1=> error.
int scpi_GetFloatParameters(STR_PARSER *p, int number, double *data)
{
	int c1;
	if(p) {
		if(number < p->pData->number) {
			if(p->pData->info[number].type.fl) {
				*data = *((double*)(p->pData->info[number].addr));
				return 0;
			}		
		}
	}
	return -1;
}

//-----------------------------------------------
//--- scpi_GetFloatParameters ---
//return :	0 => no error.
//			-1=> error.
int scpi_GetFloatIntegerParameters(STR_PARSER *p, int number, double *data)
{
	int c1;
	if(p) {
		if(number < p->pData->number) {
			if(p->pData->info[number].type.num) {
				c1 = *((int*)(p->pData->info[number].addr));
				*data =  (double)c1;
				return 0;
			}else if(p->pData->info[number].type.fl) {
				*data = *((double*)(p->pData->info[number].addr));
				return 0;
			}

		
		}
	}
	return -1;
}


//-----------------------------------------------
//--- scpi_GetExpressionParameters ---
//return :	0 => not error.
//			-1=> error.
int scpi_GetExpressionParameters(STR_PARSER *p, int number, char *data)
{
	if(p) {
		if(number < p->pData->number) {
			if(p->pData->info[number].type.expr) {
				; //	no support.
			}
		}
	}
	return -1;
}

//-----------------------------------------------
//--- scpi_GetBlockParameters ---
//return : >0 => no error and block size.
//			-1=> error.
int scpi_GetBlockParameters(STR_PARSER *p, int number, unsigned int *addr)
{
	if(p) {
		if(number < p->pData->number) {
			if(p->pData->info[number].type.block) {
				*addr = (unsigned int) p->pData->info[number].addr;
				return p->pData->info[number].size;
			}
		}
	}
	return -1;
}

//-----------------------------------------------
//--- scpi_IsEmptyOutputBuffer ---
//return : Non-zero => have data.
//			0 => empty.
//			-1=> error.
int scpi_IsEmptyOutputBuffer(STR_PARSER *p)
{
	if(p) return (p->ctrl)(_GW_IOCTL_IS_TX_EMPTY, 0);
	else  return -1;
}

//-----------------------------------------------
//--- scpi_CleanOutputBuffer ---
//return :  0 => clean ok.
//			-1=> error.
int scpi_CleanOutputBuffer(STR_PARSER *p)
{
	if(p) return (p->ctrl)(_GW_IOCTL_TX_BUF_CLEAN, 0);
	else  return -1;
}

//-----------------------------------------------
//--- scpi_Write ---
//return : Data written szie.
int scpi_Write(STR_PARSER *p, char *data, unsigned int size, unsigned int flag, unsigned int part)
{

	if(!part) {
		if(0 < scpi_IsQueryChain(p)) {
			(p->write)((char *) ";", 1, _GW_IOWR_BUF);
		}
	}

	return (p->write)((char *) data, size, flag);
}


//-----------------------------------------------
//--- scpi_CheckParameterTable ---
//return : error ID.
int scpi_CheckParameterTable(void)
{
	int i = 0, err = 0;
	for(i = 0; (_idCommandMax -1) > i; i++) {
		if((parameters[i].id -1) != i) {
			err = i;
			break;
		}
	}
	return err;
}

