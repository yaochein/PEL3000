
//==========================================================
//  include
//==========================================================
//#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//#include "gw_board.h"
#include "../common/gw_CLib.h"
//#include "gwSemaphore.h"
#include "scpiStruct.h"
#include "scpiError.h"
#include "scpiNode.h"
#include "scpiUnit.h"
#include "scpiErrQueue.h"
#include "scpiAPI.h"
#include "tty/devTtyDefine.h"
#include "../menu/menuComm.h"
#include "scpiID.h"
#include <includes.h>
#include "../../comm/commbuf2.h"

//#include "includes.h"
//extern PARSER_RING_BUF_1  PARSERBuf_1;



//#include "gwMsgQueue.h"
//==========================================================
//  Debug
//==========================================================
//-----------------------------------------------------------------------------
#define _DEBUG_SHOW_PARSER_ERROR		0
#define _DEBUG_SHOW_PARSER_FUNCTION		0

#if _DEBUG_SHOW_PARSER_ERROR
#define _DEBUG_SHOW_ERROR	printf("%s,%s,%d\n", __FILE__, __func__, __LINE__)
#else
#define _DEBUG_SHOW_ERROR
#endif

#if _DEBUG_SHOW_PARSER_FUNCTION
#define _DEBUG_PARSER(x)	printf("Parser(%d)\n", x)
#else
#define _DEBUG_PARSER(x)
#endif

#if 0
	#define _DEBUG_SHOW_MESSAGE(x)	printf("%s", x)
#else
	#define _DEBUG_SHOW_MESSAGE(x)
#endif

//==========================================================
//  Define
//==========================================================
#define _NO_ERROR   	0
#define _GET_CHAR_SIZE	64

//==========================================================
//  typedef & struct
//==========================================================

//==========================================================
//  variable & constant
//==========================================================


//==========================================================
//  Function
//==========================================================
void scpiRunMSQ (void);


//-----------------------------------------------
//---

void usleep(int useconds){
	while(useconds>0)useconds--;
	//return 0;	
}

void setLockRemote(void){
	if((UTILITY.LOCK_KEY==0)&&(Parserfalg&0x01)){
		UTILITY.LOCK_KEY = 1; 
		SysRedrawFlag |= LOCK_UPDATA;
		if((DispMode==DispMode_SET_PARAMETERS)&&(M_num<=4) ) {
			DispMode = DispMode_BROWSE_ITEMS;
			DataRedrawFlag|= PARA_CHANGE;
		}
	}
}

int scpiIsGetFollowUpData(STR_PARSER *p)
{
	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)  (p->pComd);
	STR_PARSER_PARAM *pParam = (STR_PARSER_PARAM *) (p->pParam);

	if(pComd->mhp) {
		//Continued to make follow-up data.
		pComd->fun = _PARSER_GET_PARAMETER;
		pParam->p_status = 0;
		pParam->p_len = 0;
		pParam->u_len = 0;
	}
	else {
		pComd->fun = _PARSER_PACKAGE_MSQ;
	}
	return (int) pComd->mhp;
}

//-----------------------------------------------
//---
void scpiSetBufAddrOfPData(STR_PARSER *p)
{ //Set Buffer Address Of PData.
	STR_PARSER_DATA  *pData  = (STR_PARSER_DATA*) (p->pData);
	unsigned long addr = (unsigned long) &(pData->buf[pData->total]);
	if(addr & 0x03) pData->total += (4 - (addr & 0x03));
}

//-----------------------------------------------
//---
void scpiUpdateSuffixOfPData(STR_PARSER *p)
{
	STR_PARSER_DATA  *pData  = (STR_PARSER_DATA*)   (p->pData);

	if(0 != pData->suf_level) {
		pData->suf_level--;
		pData->suffix[pData->suf_level] = -1;
	}
}

//-----------------------------------------------
//---
void scpiCleanSuffixOfPData(STR_PARSER *p)
{
	STR_PARSER_DATA  *pData  = (STR_PARSER_DATA*)   (p->pData);
	int i = 0;
	pData->suf_level = 0;
	for( ; _SCPI_COMMAND_LEVEL_MAX > i; i++) {
		pData->suffix[i] = -1;
	}
}

//-----------------------------------------------
//---
void scpiInitPData(STR_PARSER *p)
{
	STR_PARSER_DATA  *pData  = (STR_PARSER_DATA*)   (p->pData);
	pData->id		= 0;
	pData->dev		= 0;
	pData->query	= 0;
	pData->number	= 0;
	pData->total	= 0;
	pData->info[0].type.data = _NODATA;
	pData->info[0].size = 0;
	pData->info[0].addr = 0;
	pData->buf[0] = 0;
	scpiSetBufAddrOfPData(p);
}

//-----------------------------------------------
//---
void scpiCleanInfoPData(STR_PARSER *p)
{
	STR_PARSER_DATA  *pData  = (STR_PARSER_DATA*)   (p->pData);

	pData->info[pData->number].type.data = _NODATA;
	pData->info[pData->number].size = 0;
    pData->info[pData->number].addr = 0;
}

//-----------------------------------------------
//---
int scpiBlock_Prepare(STR_PARSER *p)
{
	STR_PARSER_DATA  *pData  = (STR_PARSER_DATA*) (p->pData);
	PARAM_INF        *info   = (PARAM_INF*) (&(pData->info[pData->number]));

	if(pData->number < _SCPI_PARAMETER_LEVEL_MAX) {
		info->type.data = _BLOCK;
		info->addr = (char*)(&(pData->buf[pData->total]));
		info->size = 0;
		return 0;
	}
	return -1;
}

unsigned int scpiBlock_GetAddressStorage(STR_PARSER *p)
{
	STR_PARSER_DATA  *pData  = (STR_PARSER_DATA*) (p->pData);
	PARAM_INF        *info   = (PARAM_INF*) (&(pData->info[pData->number]));

	unsigned int addr = (unsigned int) info->addr;
	return (unsigned int) (addr + info->size);
}

int scpiBlock_UpdateAddressStorage(STR_PARSER *p, int length)
{
	STR_PARSER_DATA  *pData  = (STR_PARSER_DATA*) (p->pData);
	PARAM_INF        *info   = (PARAM_INF*) (&(pData->info[pData->number]));

	info->size += length;
	return (int) info->size;
}

int scpiBlock_SaveData(STR_PARSER *p, char *data, int length)
{
	STR_PARSER_DATA  *pData  = (STR_PARSER_DATA*) (p->pData);
	PARAM_INF        *info   = (PARAM_INF*) (&(pData->info[pData->number]));
	int i = 0;

	if(_SCPI_PARAMETER_BUFFER_SIZE >= (pData->total + info->size + length)) {
		for(i = 0; i < length; i++) {
			info->addr[info->size] = *(data + i);
			info->size++;
		}
		return 0;
	}
	else return -1;
}

int scpiBlock_SaveByte(STR_PARSER *p, char data)
{
	STR_PARSER_DATA  *pData  = (STR_PARSER_DATA*) (p->pData);
	PARAM_INF        *info   = (PARAM_INF*) (&(pData->info[pData->number]));

	if(_SCPI_PARAMETER_BUFFER_SIZE > (pData->total + info->size)) {
		info->addr[info->size] = data;
		info->size++;
		return 0;
	}
	else return -1;
}

int scpiBlock_Close(STR_PARSER *p)
{
	STR_PARSER_DATA  *pData  = (STR_PARSER_DATA*) (p->pData);
	PARAM_INF        *info   = (PARAM_INF*) (&(pData->info[pData->number]));

	pData->total += info->size;
	pData->number++;
	//------------------------------------
	//--- The size of point is 4bytes. ---
	scpiSetBufAddrOfPData(p);
	return 0;
}

//-----------------------------------------------
//---
int lua_MsgQueue(STR_PARSER *p, unsigned int id, unsigned int query, unsigned int num, PARAM_INF *param)
{
	STR_PARSER_DATA  *pData  = (STR_PARSER_DATA*) (p->pData);
	PARAM_INF        *info   = (PARAM_INF*) (&(pData->info[0]));
	unsigned int   i = 0, j = 0;

	pData->id = id;
	pData->dev = p->dev;
	pData->query = query;
	pData->number = num;
	pData->total =0;
	pData->suf_level =0;
	for(i = 0; i < _SCPI_COMMAND_LEVEL_MAX; i++) {
		pData->suffix[i] = -1;
	}

	for(j = 0; num > j; j++) {
		//-----------------------------------------------------------------------
		//--- The size of point is 4bytes. ---
		scpiSetBufAddrOfPData(p);
		//-----------------------------------------------------------------------
		info->size = param->size;
		info->type.data = param->type.data;
		info->addr = (char*)(&(pData->buf[pData->total]));
		for(i = 0; i < info->size ; i++) {
			info->addr[i] = param->addr[i];
		}
		pData->total += info->size;
	}

	p->msgSend.func = 0;
	p->msgSend.data = (unsigned long) p;

	i = 0;
	while(0 != sendMsgQueue(&(p->msgSend), _DEV_MACHINE)) {
		usleep(1000);
		if(5 == ++i) return scpi_SetCommandError(p, _ERR_310_System_error);
	}

	i = 0;
	while(1) {
		usleep(1000);
		if(i) {
			if(-1 != rcvMsgQueue(&(p->msgRcv), p->dev)) {
				return 0;
			}
		}
	}
//	return 0;
}

int scpiSavePData(STR_PARSER *p)
{
	unsigned int   i = 0;
	STR_PARSER_PARAM *pParam = (STR_PARSER_PARAM *) (p->pParam);
	STR_PARSER_DATA  *pData  = (STR_PARSER_DATA*) (p->pData);
	PARAM_INF        *info   = (PARAM_INF*) (&(pData->info[pData->number]));

	if((pData->number < _SCPI_PARAMETER_LEVEL_MAX)&&((pData->total + pParam->p_len)< _SCPI_PARAMETER_BUFFER_SIZE)) {
		info->addr = (char*)(&(pData->buf[pData->total]));
		info->size = pParam->p_len;

		if(pParam->t_num) {
			if(pParam->n_dot || pParam->e_symbol || pParam->n_unit)	info->type.data = _FLOAT;
			else							info->type.data = _NUMBER;
			for(i = 0; i < info->size ; i++) {
				info->addr[i] = pParam->change.sc[i];
			}
		}
		else if(pParam->t_block_def || pParam->t_block_ind) {
			info->type.data = _BLOCK;
		}
		else if(pParam->t_base2 || pParam->t_base8 || pParam->t_base16) {
			info->type.data = _NUMBER;
			for(i = 0; i < info->size ; i++) {
				info->addr[i] = pParam->change.sc[i];
			}
		}
		else if(pParam->t_kw) {
			info->type.data = _KEYWORD;
			for(i = 0; i < info->size ; i++) {
				info->addr[i] = pParam->change.sc[i];
			}
		}
		else if(pParam->t_str) {
			info->type.data = _STRING1;
			info->size++;// include the '\0'.
			for(i = 0; i < info->size ; i++) {
				info->addr[i] = pParam->p_buf[i];
			}
		}
		else {
			info->type.data = _NODATA;
		}
		pData->total += info->size;
		pData->number++;
		//-----------------------------------------------------------------------
		//--- The size of point is 4bytes. ---
		scpiSetBufAddrOfPData(p);
		return 0;
	}
	else {
		return -1;
	}
}

//-----------------------------------------------
//---
void scpiInitParser(STR_PARSER_COMD *p)
{
	if(p) {
		unsigned int i = 0;
		p->fun       = _PARSER_GET_COMMAND;
		p->cnt       = 0;
		p->level     = 0;
		p->status    = 0;
		p->err       = _ERR_000_No_Error;
		p->check     = 0;
		p->pCmd      = &(p->com[0][0]);
		for(i = 0; i < _SCPI_COMMAND_LEVEL_MAX; i++) {
			p->com[i][0] = 0;
			p->len[i]    = 0;
			p->suf_com[i][0]= 0;
			p->suf_len[i]= 0;
			p->suf_var[i]= -1;
		}
	}
}

//-----------------------------------------------
//---
int scpiMatchString(char *s1, char *s2, int len)
{
	if((0 == s1)||(0 == s2)||(16 <= len))	return -1;
    int   i = 0;
	char c1 = 0;
	char c2 = 0;

    for(i = 0; i < len; i++) {
		c1 = (('a' <= (*s1))&&('z' >= (*s1)))? ((*s1)-('a' - 'A')): (*s1);
		c2 = (('a' <= (*s2))&&('z' >= (*s2)))? ((*s2)-('a' - 'A')): (*s2);
        if(c1 != c2) {
            return -1;
        }
		s1++;
		s2++;
    }
    return 0;
}

//-----------------------------------------------
//---
int scpiGetNumericSuffix(STR_PARSER *p)
{
	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)  (p->pComd);

	if(0 < pComd->suf_len[pComd->check]) {
		//string-->number.
		pComd->suf_var[pComd->check]  = atoi((char *) &(pComd->suf_com[pComd->check][0]));
		return (int) 0;
	}
	else {
		pComd->suf_var[pComd->check]  = -1;
		return -1;
	}
}

//-----------------------------------------------
//---
int scpiMatchNode(STR_PARSER *p, NODES pNote)
{
	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)  (p->pComd);

    if((pComd->len[pComd->check] == pNote->name->min) || (pComd->len[pComd->check] == pNote->name->max)){
        if(scpiMatchString((char*)(&(pComd->com[pComd->check][0])), (char*) (pNote->name->word), pComd->len[pComd->check]) != 0) {
            return -1;
        }
		if(pComd->suf_var[pComd->check] != -1) {
			if(pNote->type & T_SUFFIX_MASK) {
				if((pComd->suf_var[pComd->check] >= pNote->suffix->min) && (pComd->suf_var[pComd->check] <= pNote->suffix->max)) {
					_DEBUG_SHOW_ERROR;
					return 0;
				}
				else {
					pComd->err = _ERR_114_Header_suffix_out_of_range;
					_DEBUG_SHOW_ERROR;
					return -1;
				}
			}
			else if((pNote->type & T_SUFFIX_MASK)==0) {
				_DEBUG_SHOW_ERROR;
				pComd->err = _ERR_113_Undefined_header;
				return -1;
			}
			else {
				_DEBUG_SHOW_ERROR;
				pComd->err = _ERR_113_Undefined_header;
				return -1;
			}
		}
		else if(pComd->suf_var[pComd->check] == -1) {
			if((pNote->type & T_SUFFIX_MASK)==0) {
				_DEBUG_SHOW_ERROR;
				return 0;
			}
			else if(pNote->type & TO___) {
				_DEBUG_SHOW_ERROR;
				return 0;
			}
			else if(pNote->type & T_R__) {
				_DEBUG_SHOW_ERROR;
				pComd->err = _ERR_131_Invalid_suffix;
				return -1;
			}
			else {
				_DEBUG_SHOW_ERROR;
				return 0;
			}
		}
		else {
			_DEBUG_SHOW_ERROR;
			pComd->err = _ERR_113_Undefined_header;
			return -1;
		}
    }
	_DEBUG_SHOW_ERROR;
    return -1;
}

//-----------------------------------------------
//---
int scpiScanNode(STR_PARSER *p)
{
    unsigned int i = 0;
    STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)  (p->pComd);

	if(0 == pComd->pNow->son)	return -1;

	scpiGetNumericSuffix(p);

    for(i=0; pComd->pNow->son[i] != ((NODES) 0) ;i++){
        if( 0 == scpiMatchNode(p, pComd->pNow->son[i]) ) {
            pComd->pNow = pComd->pNow->son[i];
            return 0;
        }
    }
    return -1;
}

//-----------------------------------------------
//---
void scpiCheckCommand(STR_PARSER *p)
{
	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)  (p->pComd);
    STR_PARSER_PARAM *pParam = (STR_PARSER_PARAM *) (p->pParam);

    if(pComd->asterisk) {
        pComd->pNow = (NODES) &_nodeCommon;
    }

    if(pComd->reset) {
        pComd->pNow = (NODES) &_nodeRoot;
    }

    for( pComd->check = 0; pComd->check < pComd->level; pComd->check++){
        if(0 != scpiScanNode(p) ) {//no note.
	        scpiIsGetFollowUpData(p);
			if(_ERR_000_No_Error == pComd->err) {
	            pComd->err = _ERR_113_Undefined_header;
				_DEBUG_SHOW_ERROR;
			}
			_DEBUG_SHOW_ERROR;
            return;
        }
    }

    if(0 == pComd->pNow->id) {
		scpiIsGetFollowUpData(p);
        pComd->err = _ERR_113_Undefined_header;
		_DEBUG_SHOW_ERROR;
    }
    else {
        if(pComd->query && (0 == (pComd->pNow->type & T__Q_))) {
    		pComd->err = _ERR_113_Undefined_header;
			_DEBUG_SHOW_ERROR;
        }
        if(pComd->mhp) {
            pComd->fun = _PARSER_GET_PARAMETER;
			pParam->p_status = 0;
			pParam->p_len = 0;
			pParam->u_len = 0;
			scpiInitPData(p);
			if((pComd->reset)||(pComd->asterisk)) {
				scpiCleanSuffixOfPData(p);
			}
			return;
        }
		else if(0 == parameters[pComd->pNow->id -1].data[pComd->query].max) {
		}
        else if(1 == parameters[pComd->pNow->id -1].data[pComd->query].items[0].type.opt) {
        }
		else {
        	pComd->err = _ERR_109_Missing_parameter;
			_DEBUG_SHOW_ERROR;
		}
		pComd->fun = _PARSER_PACKAGE_MSQ;
    }
}

//-----------------------------------------------
//---
void scpiGetCommand(STR_PARSER *p)
{
	int err = _NO_ERROR, cnt = 0;
    char data = 0;
	static char dat1;
	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)  (p->pComd);

    while(_PARSER_GET_COMMAND == pComd->fun){
        err = (p->read)((char *) (&data), 1, _GW_IORD);//read 1 byte.

		if(data != dat1){
			dat1 = data;
			//printf("word is: %c \n",data);        	
		}
		if(0 < err) {

			
			if(_ERR_000_No_Error != pComd->err) {
				if(pComd->double_quote) {
					if(pComd->dq_start && (0 == pComd->dq_end)) {
						if('"' == data){
							pComd->dq_end = 1;
						}
						else if('\n' == data) {
							pComd->fun = _PARSER_PACKAGE_MSQ;
							pComd->endword = 1;
							pComd->err = _ERR_151_Invalid_string_data;
							_DEBUG_SHOW_ERROR;
						}
						else {
							//abandon the data.
						}
					}
					else {
						if('\n' == data) {
							pComd->fun = _PARSER_PACKAGE_MSQ;
							pComd->endword = 1;
						}
						else if('"' == data){
							pComd->dq_start = 1;
							pComd->dq_end = 0;
						}
						else {
							//abandon the data.
						}
					}
				}
				else if(pComd->single_quote) {
					if(pComd->sq_start && (0 == pComd->sq_end)) {
						if('\'' == data){
							pComd->sq_end = 1;
						}
						else if('\n' == data) {
							pComd->fun = _PARSER_PACKAGE_MSQ;
							pComd->endword = 1;
							pComd->err = _ERR_151_Invalid_string_data;
							_DEBUG_SHOW_ERROR;
						}
						else {
							//abandon the data.
						}
					}
					else {
						if('\n' == data) {
							pComd->fun = _PARSER_PACKAGE_MSQ;
							pComd->endword = 1;
						}
						else if('\'' == data){
							pComd->sq_start = 1;
							pComd->sq_end = 0;
						}
						else {
							//abandon the data.
						}
					}
				}
				else {
					if('\n' == data) {
						pComd->fun = _PARSER_PACKAGE_MSQ;
						pComd->endword = 1;
					}
					else {
						//abandon the data.
					}
				}
			}
			else { //(_ERR_000_No_Error == pComd->err)
				if('"' == data) {
					if(0 == pComd->level) {
						pComd->double_quote = 1;
						pComd->dq_start 	= 1;
						pComd->dq_end		= 0;
						if(0 == pComd->cnt) {
							pComd->err = _ERR_103_Invalid_separator;
						}
						else {
							pComd->err = _ERR_111_Header_separator_error;
						}
						_DEBUG_SHOW_ERROR;
					}
					else {
						pComd->err = _ERR_113_Undefined_header;
						_DEBUG_SHOW_ERROR;
					}
	            }
				else if('\'' == data) {
					if(0 == pComd->level) {
						pComd->single_quote = 1;
						pComd->sq_start     = 1;
						pComd->sq_end       = 0;
						if(0 == pComd->cnt) {
							pComd->err = _ERR_103_Invalid_separator;
						}
						else {
							pComd->err = _ERR_111_Header_separator_error;
						}
						_DEBUG_SHOW_ERROR;
					}
					else {
						pComd->err = _ERR_113_Undefined_header;
						_DEBUG_SHOW_ERROR;
					}
	            }
				else if(((0x00 <= data)&&(0x09 >= data))||((0x0B <= data)&&(0x20 >= data))) {
					//White Space.
	                if(pComd->colon) {// ": ".
	                    pComd->err = _ERR_102_Syntax_error;
						_DEBUG_SHOW_ERROR;
	                }
	                else if(0 != pComd->cnt){
	                    *(pComd->pCmd) = '\0';
	                    pComd->len[pComd->level] = pComd->cnt;
						pComd->suf_com[pComd->level][pComd->suf_len[pComd->level]]= '\0';
	                    pComd->level++;
	                    pComd->fun = _PARSER_CHECK_COMMAND;
	                    pComd->mhp = 1;
						pComd->space = 1;
	                }
					else { //(0 == pComd->cnt)
						//abandon the data.
					}
	            }
				else if(';' == data) {
					if(pComd->colon) {// ":;".
						pComd->fun = _PARSER_PACKAGE_MSQ;
						pComd->err = _ERR_102_Syntax_error;
						_DEBUG_SHOW_ERROR;
					}
					else if(0 != pComd->cnt) {
						*(pComd->pCmd) = '\0';
						pComd->len[pComd->level] = pComd->cnt;
						pComd->suf_com[pComd->level][pComd->suf_len[pComd->level]]= '\0';
						pComd->level++;
						pComd->fun = _PARSER_CHECK_COMMAND;
					}
				}
	            else if('\n' == data) {
	                if(pComd->colon) {// ":\n".
						pComd->fun = _PARSER_PACKAGE_MSQ;
	                    pComd->err = _ERR_102_Syntax_error;
						pComd->endword = 1;
						_DEBUG_SHOW_ERROR;
	                }
	                else {
						if((0 == pComd->level)&&(0 == pComd->cnt)&&(0 == pComd->suf_len[0])) {
							if(0 < p->countQuery) {
								*(pComd->pCmd) = '\0';
								pComd->len[pComd->level] = pComd->cnt;
								pComd->suf_com[pComd->level][pComd->suf_len[pComd->level]]= '\0';
								pComd->fun = _PARSER_GET_NEXT_COMMAND;
								pComd->endword = 1;
							}else {
								//abandon the data.
							}
						}
						else {
							*(pComd->pCmd) = '\0';
			                pComd->len[pComd->level] = pComd->cnt;
							pComd->suf_com[pComd->level][pComd->suf_len[pComd->level]]= '\0';
		        	        pComd->fun = _PARSER_CHECK_COMMAND;
		            	    pComd->endword = 1;
							if(pComd->cnt != 0){
		    	                pComd->level++;
		                	}
						}
	                }
	            }
	            else if(':' == data) {
	                if(pComd->colon) {// "::".
	                    pComd->err = _ERR_102_Syntax_error;
						_DEBUG_SHOW_ERROR;
	                }else {
	                    pComd->colon = 1;
	                    if((0 == pComd->level)&&(0 == pComd->cnt)) {
	                        pComd->reset = 1;
	                    }
	                    else {
	                        //next level
	                        *(pComd->pCmd) = '\0';
	                        pComd->len[pComd->level] = pComd->cnt;
							pComd->suf_com[pComd->level][pComd->suf_len[pComd->level]]= '\0';
	                        pComd->level++;
	                        if(_SCPI_COMMAND_LEVEL_MAX <= pComd->level) {
	                            pComd->err = _ERR_113_Undefined_header;
								_DEBUG_SHOW_ERROR;
	                        }
	                        else{
								pComd->no_suffix = 0;
								pComd->suffix = 0;
	                            pComd->cnt = 0;
	                            pComd->pCmd = &(pComd->com[pComd->level][0]);
								pComd->suf_len[pComd->level] = 0;
								pComd->suf_com[pComd->level][pComd->suf_len[pComd->level]]= '\0';
	                        }
	                    }
	                }
	            }
	            else if('?' == data) {
	                if(pComd->colon) {// ":?".
	                    pComd->err = _ERR_102_Syntax_error;
						_DEBUG_SHOW_ERROR;
	                }
					else if(0 != pComd->cnt){
	                    pComd->query = 1;
	                    *(pComd->pCmd) = '\0';
	                    pComd->len[pComd->level] = pComd->cnt;
						pComd->suf_com[pComd->level][pComd->suf_len[pComd->level]]= '\0';
	                    pComd->level++;
	                    pComd->fun = _PARSER_CHECK_COMMAND;
	                    pComd->mhp = 1;
	                }
					else {
						pComd->err = _ERR_103_Invalid_separator;
						_DEBUG_SHOW_ERROR;
					}
	            }
				else if('*' == data) {
					if(pComd->colon) {// ":*".
	                    pComd->err = _ERR_102_Syntax_error;
						_DEBUG_SHOW_ERROR;
	                }
					else if((0 == pComd->level)&&(0 == pComd->cnt)) {
						pComd->asterisk = 1;
						*(pComd->pCmd) = data;
	                    pComd->pCmd++;
	                    pComd->cnt++;
					}
	                else{
	                    pComd->err = _ERR_102_Syntax_error;
						_DEBUG_SHOW_ERROR;
	                }
	            }
				else if(('_' == data)||(('A' <= data)&&('Z' >= data))||(('a' <= data)&&('z' >= data))) {
					pComd->colon = 0;
					if(pComd->suffix) {
						int i = 0;
						for( ; i < pComd->suf_len[pComd->level]; i++) {
							*(pComd->pCmd) = pComd->suf_com[pComd->level][i];
							pComd->pCmd++;
							pComd->cnt++;
						}
						pComd->suf_com[pComd->level][0] = '\0';
						pComd->suf_len[pComd->level] = 0;;
						pComd->no_suffix = 1;
						pComd->suffix = 0;
					}

	                if(_SCPI_COMMAND_LENGTH_MAX > pComd->cnt){
						*(pComd->pCmd) = data;
	                    pComd->pCmd++;
	                    pComd->cnt++;
	                }
	                else{
	                    pComd->err = _ERR_112_Program_mnemonic_too_long;
						_DEBUG_SHOW_ERROR;
	                }
	            }
				else if(('0' <= data)&&('9' >= data)) {
					if(pComd->no_suffix) {
						if(_SCPI_COMMAND_LENGTH_MAX > pComd->cnt){
							*(pComd->pCmd) = data;
		                    pComd->pCmd++;
		                    pComd->cnt++;
		                }
		                else{
		                    pComd->err = _ERR_112_Program_mnemonic_too_long;
							_DEBUG_SHOW_ERROR;
		                }
					}
					else if(_SCPI_COMMAND_LENGTH_MAX > pComd->suf_len[pComd->level]){
						pComd->suffix = 1;
						pComd->suf_com[pComd->level][pComd->suf_len[pComd->level]] = data;
						pComd->suf_len[pComd->level]++;
					}
					else{
						pComd->err = _ERR_112_Program_mnemonic_too_long;
						_DEBUG_SHOW_ERROR;
					}
				}
	            else {
					if(0 == pComd->cnt) {
						pComd->err = _ERR_101_Invalid_character;
						_DEBUG_SHOW_ERROR;
					}
					else {
						pComd->err = _ERR_113_Undefined_header;
						_DEBUG_SHOW_ERROR;
					}
				}
			}
        }
        else{
            break;   /*Buffer empty.*/
        }
		//---------------------------------
		cnt++;
		if(_GET_CHAR_SIZE <= cnt)	break;
		//---------------------------------
    }
}

//-----------------------------------------------
//---
int scpiCheckUnit(STR_PARSER *p)
{
	unsigned int i= 0;
	unsigned int number = 0;
	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)  (p->pComd);
	STR_PARSER_PARAM *pParam = (STR_PARSER_PARAM *) (p->pParam);
	STR_PARSER_DATA  *pData  = (STR_PARSER_DATA*)   (p->pData);

	if(0 == parameters[pComd->pNow->id -1].data[pComd->query].items[0].type.list)	number = pData->number;
	unsigned int  unit = parameters[pComd->pNow->id -1].data[pComd->query].items[number].unit;

	if(0 != unit) {
		PARAM_UNIT *p_unit = (PARAM_UNIT*) units[unit - 1];

		for(i = 0; 0 != p_unit[i].sunit; i++) {
			if(0 == strcmp(p_unit[i].sunit, pParam->u_buf)) {
				return (int)p_unit[i].exp;
			}
		}
	}
	pComd->err = _ERR_131_Invalid_suffix;
	_DEBUG_SHOW_ERROR;
	return -1;
}

//-----------------------------------------------

int scpiCheckKeyword(STR_PARSER *p)
{
	unsigned int i = 0;
	unsigned int number = 0;
	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)  (p->pComd);
    STR_PARSER_PARAM *pParam = (STR_PARSER_PARAM *) (p->pParam);
    STR_PARSER_DATA  *pData  = (STR_PARSER_DATA*)   (p->pData);

	if(0 == parameters[pComd->pNow->id -1].data[pComd->query].items[0].type.list)	number = pData->number;
	PARAM_KEYWORD* key = parameters[pComd->pNow->id -1].data[pComd->query].items[number].keys;

	for(i = 0; 0 != ((COMD_WORD*)(key[i].name)); i++) {
		if((key[i].name->min == pParam->p_len)||(key[i].name->max == pParam->p_len)) {
			if(0 == scpiMatchString(key[i].name->word, pParam->p_buf, pParam->p_len)) {
				return (int)key[i].value;
			}
		}
		else if(128 < i) {
			break;
		}
	}
	pComd->err = _ERR_224_Illegal_parameter_value;
	_DEBUG_SHOW_ERROR;
	return -1;

}

//-----------------------------------------------
//---
void scpiCheckParameter(STR_PARSER *p)
{
	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)  (p->pComd);
	STR_PARSER_PARAM *pParam = (STR_PARSER_PARAM *) (p->pParam);
	STR_PARSER_DATA  *pData  = (STR_PARSER_DATA*)   (p->pData);
	STR_PARAMS       *para   = (STR_PARAMS*) (&(parameters[pComd->pNow->id -1].data[pComd->query]));
	int value = 0;

	if(0 == para->max) {
		if((0 == pParam->p_len)&&(0 == pComd->mhp)) {
			//no data.
			pComd->fun = _PARSER_PACKAGE_MSQ;
		}
		else {
			scpiIsGetFollowUpData(p);
			pComd->err = _ERR_108_Parameter_not_allowed;
			_DEBUG_SHOW_ERROR;
		}
	}
	else if(pData->number < para->max) {
		unsigned int number = 0;

		if(0 == para->items[0].type.list)	number = pData->number;
		//------------------------------------------------------------
		if((0 == pParam->p_len)&&(0 == pParam->t_str)) {
			if(0 == para->items[number].type.opt) {
				pComd->err = _ERR_109_Missing_parameter; //_SCPI_MissingParameter;
				_DEBUG_SHOW_ERROR;
			}
		}
		else if(pParam->t_num) {
			if(para->items[number].type.num) {
				if(pParam->n_dot || pParam->e_symbol || pParam->n_unit) {//double data.
					pParam->change.d = (double)strtod((char*)(&(pParam->p_buf)),0);
					if(pParam->n_unit) {
						value = scpiCheckUnit(p);
						if(_ERR_000_No_Error == pComd->err) {
							pParam->change.d *= ((double)pow(10 ,value));
						}
					}
					pParam->p_len = 8;
				}
				else {//integer data.
					pParam->change.si = (int)atoi((char*)(&(pParam->p_buf)));
					pParam->p_len = 4;
				}
			}
			else {
				pComd->err = _ERR_128_Numeric_data_not_allowed;
			}
		}
		else if((pParam->t_block_def || pParam->t_block_ind)) {
			//block data.
			if(para->items[number].type.block) {
			}
			else {
				pComd->err = _ERR_168_Block_data_not_allowed;
			}
		}
		else if((pParam->t_base2 || pParam->t_base8 || pParam->t_base16)) {
			//Number-Base system.
			if(para->items[number].type.num) {
				if(0 == gw_CLIB_str2base((char*)(&(pParam->p_buf)), (unsigned int*)(&(pParam->change.ui)))) {
					pParam->p_len = 4;
				}
				else {
					pComd->err = _ERR_121_Invalid_character_in_number;
					_DEBUG_SHOW_ERROR;
				}
			}
			else {
				pComd->err = _ERR_128_Numeric_data_not_allowed;
			}
		}
		else if(pParam->t_kw) {
			//Keyword-data.
			if(para->items[number].type.kw) {
				value = scpiCheckKeyword(p);
				if(_ERR_000_No_Error == pComd->err) {
					pParam->change.si = value;
					pParam->p_len = 4;
				}
			}
			else {
				pComd->err = _ERR_148_Character_data_not_allowed;
			}
		}
		else if(pParam->t_str) {
			//String-data.
			if(para->items[number].type.str) {
			}
			else {
				pComd->err = _ERR_158_String_data_not_allowed;
			}
		}
		else if(pParam->t_express) {
			//expression.
			if(para->items[number].type.expr) {
			}
			else {
				pComd->err = _ERR_178_Expression_data_not_allowed;
			}
		}
		else {
			if(para->items[number].type.data & _HAVE_PARAM) {
				pComd->err = _ERR_104_Data_type_error;
				_DEBUG_SHOW_ERROR;
			}
			else {
				pComd->err = _ERR_109_Missing_parameter;
				_DEBUG_SHOW_ERROR;
			}
		}

		if(_ERR_000_No_Error == pComd->err) {
			//save information of parameter.ext: type, size, data.
			scpiSavePData(p);
		}
		scpiIsGetFollowUpData(p);
	}
	else if(pData->number >= para->max) {
		scpiIsGetFollowUpData(p);
		pComd->err = _ERR_115_Unexpected_number_of_parameters;
		_DEBUG_SHOW_ERROR;
	}
}


void parseDecimalNumericProgramData(STR_PARSER *p, char data)
{
	//-------------------------------------------------------------------------------------------
	// number format :
	// [+/-][integer][Dot][decimal][space1][{e/E}[space2][+/-][integer]][space3][unit][space2] { ',' | '\n' }

	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)  (p->pComd);
	STR_PARSER_PARAM *pParam = (STR_PARSER_PARAM *) (p->pParam);

	if(_ERR_000_No_Error != pComd->err) {
		if('\n' == data) {
            pComd->endword = 1;
            pComd->mhp = 0;
            pComd->fun = _PARSER_PACKAGE_MSQ;
        }
		else if('"' == data) {
			if(1 == pParam->dq_start) {
				if(0 == pParam->dq_end) {
					pParam->dq_end = 1;
					pComd->err = _ERR_103_Invalid_separator;
					_DEBUG_SHOW_ERROR;
				}
				else {
					pParam->dq_end = 0;
					pComd->err = _ERR_151_Invalid_string_data;
					_DEBUG_SHOW_ERROR;
				}
			}
			else {
				//abandon the data.
			}
		}
		else if('\'' == data) {
			if(1 == pParam->sq_start) {
				if(0 == pParam->sq_end) {
					pParam->sq_end = 1;
					pComd->err = _ERR_103_Invalid_separator;
					_DEBUG_SHOW_ERROR;
				}
				else {
					pParam->sq_end = 0;
					pComd->err = _ERR_151_Invalid_string_data;
					_DEBUG_SHOW_ERROR;
				}
			}
			else {
				//abandon the data.
			}
		}
		else {
			//abandon the data.
		}
	}
	else if(pParam->n_space4) {
		if(((0x00 <= data)&&(0x09 >= data))||((0x0B <= data)&&(0x20 >= data))) {
		}
		else if(',' == data) {
			pComd->mhp = 1;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if(';' == data) {
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if('"' == data) {
			pParam->dq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
        else if('\'' == data) {
			pParam->sq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
		else if(('+' == data)||('-' == data)) {
			pComd->err = _ERR_121_Invalid_character_in_number;
			_DEBUG_SHOW_ERROR;
		}
		else if('_' == data) {
			pComd->err = _ERR_101_Invalid_character;
			_DEBUG_SHOW_ERROR;
		}
		else {
			pComd->err = _ERR_103_Invalid_separator;
			_DEBUG_SHOW_ERROR;
		}
    }
	else if(pParam->n_unit) {
		if(((0x00 <= data)&&(0x09 >= data))||((0x0B <= data)&&(0x20 >= data))) {
			pParam->n_space4 = 1;
		}
		else if(',' == data) {
			pComd->mhp = 1;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if(';' == data) {
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if('"' == data) {
			pParam->dq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
		else if('\'' == data) {
			pParam->sq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
		else if('+' == data) {
			pComd->err = _ERR_121_Invalid_character_in_number;
			_DEBUG_SHOW_ERROR;
		}
		else if('-' == data) {
			pComd->err = _ERR_131_Invalid_suffix;
			_DEBUG_SHOW_ERROR;
		}
		else if(('0' <= data)&&('9' >= data)) {
			pComd->err = _ERR_103_Invalid_separator;
			_DEBUG_SHOW_ERROR;
		}
		else if(('A' <= data)&&('Z' >= data)) {
			pParam->n_unit = 1;
			//save to <Unit-Buffer>.
			pParam->u_buf[pParam->u_len] = data + ('a' - 'A');
			pParam->u_len++;
		}
		else if(('a' <= data)&&('z' >= data)) {
			pParam->n_unit = 1;
			//save to <Unit-Buffer>.
			pParam->u_buf[pParam->u_len] = data;
			pParam->u_len++;
		}
		else if('_' == data) {
			pComd->err = _ERR_101_Invalid_character;
			_DEBUG_SHOW_ERROR;
		}
		else {
			pComd->err = _ERR_103_Invalid_separator;
			_DEBUG_SHOW_ERROR;
		}
    }
	else if(pParam->n_space3) {
		if(((0x00 <= data)&&(0x09 >= data))||((0x0B <= data)&&(0x20 >= data))) {
		}
		else if(',' == data) {
			pComd->mhp = 1;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if(';' == data) {
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if('"' == data) {
			pParam->dq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
		else if('\'' == data) {
			pParam->sq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
		else if(('+' == data)||('-' == data)) {
			pComd->err = _ERR_121_Invalid_character_in_number;
			_DEBUG_SHOW_ERROR;
		}
		else if(('0' <= data)&&('9' >= data)) {
			pComd->err = _ERR_103_Invalid_separator;
			_DEBUG_SHOW_ERROR;
		}
		else if(('A' <= data)&&('Z' >= data)) {
			pParam->n_unit = 1;
			//save to <Unit-Buffer>.
			pParam->u_buf[pParam->u_len] = data + ('a' - 'A');
			pParam->u_len++;
		}
		else if(('a' <= data)&&('z' >= data)) {
			pParam->n_unit = 1;
			//save to <Unit-Buffer>.
			pParam->u_buf[pParam->u_len] = data;
			pParam->u_len++;
		}
		else if('_' == data) {
			pComd->err = _ERR_101_Invalid_character;
			_DEBUG_SHOW_ERROR;
		}
		else {
			pComd->err = _ERR_103_Invalid_separator;
			_DEBUG_SHOW_ERROR;
		}
    }
	else if(pParam->e_integer) {
		if(((0x00 <= data)&&(0x09 >= data))||((0x0B <= data)&&(0x20 >= data)))	{
			pParam->n_space3 = 1;
		}
		else if(',' == data) {
			pComd->mhp = 1;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if(';' == data) {
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if('"' == data) {
			pParam->dq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
		else if('\'' == data) {
			pParam->sq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
		else if(('+' == data)||('-' == data)) {
			pComd->err = _ERR_121_Invalid_character_in_number;
			_DEBUG_SHOW_ERROR;
		}
		else if(('0' <= data)&&('9' >= data)) {
			pParam->e_integer = 1;
			//save to <Param.-Buffer>.
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
		}
		else if(('A' <= data)&&('Z' >= data)) {
			pParam->n_unit = 1;
			//save to <Unit-Buffer>.
			pParam->u_buf[pParam->u_len] = data + ('a' - 'A');
			pParam->u_len++;
		}
		else if(('a' <= data)&&('z' >= data)) {
			pParam->n_unit = 1;
			//save to <Unit-Buffer>.
			pParam->u_buf[pParam->u_len] = data;
			pParam->u_len++;
		}
		else if('_' == data) {
			pComd->err = _ERR_101_Invalid_character;
			_DEBUG_SHOW_ERROR;
		}
		else {
			pComd->err = _ERR_103_Invalid_separator;
			_DEBUG_SHOW_ERROR;
		}
	}
	else if(pParam->e_sign) {
		if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_PACKAGE_MSQ;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
			pComd->err = _ERR_121_Invalid_character_in_number;
			_DEBUG_SHOW_ERROR;
		}
		else if('"' == data) {
			pParam->dq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
		else if('\'' == data) {
			pParam->sq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
		else if(('0' <= data)&&('9' >= data)) {
			pParam->e_integer = 1;
			//save to <Param.-Buffer>.
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
		}
		else {
			pComd->err = _ERR_121_Invalid_character_in_number;
			_DEBUG_SHOW_ERROR;
		}
	}
	else if(pParam->n_space2) {
		if(((0x00 <= data)&&(0x09 >= data))||((0x0B <= data)&&(0x20 >= data))) {
		}
		else if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_PACKAGE_MSQ;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
			pComd->err = _ERR_121_Invalid_character_in_number;
			_DEBUG_SHOW_ERROR;
		}
		else if(('+' == data)||('-' == data)) {
			pParam->e_sign = 1;
			//save to <Param.-Buffer>.
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
		}
		else if(('0' <= data)&&('9' >= data)) {
			pParam->e_integer = 1;
			//save to <Param.-Buffer>.
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
		}
		else {
			pComd->err = _ERR_121_Invalid_character_in_number;
			_DEBUG_SHOW_ERROR;
		}
	}
    else if(pParam->e_symbol) {
		if(((0x00 <= data)&&(0x09 >= data))||((0x0B <= data)&&(0x20 >= data))) {
			pParam->n_space2 = 1;
		}
		else if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_PACKAGE_MSQ;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
			pComd->err = _ERR_131_Invalid_suffix;
			_DEBUG_SHOW_ERROR;
		}
		else if(('+' == data)||('-' == data)) {
			pParam->e_sign = 1;
			//save to <Param.-Buffer>.
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
		}
		else if(('0' <= data)&&('9' >= data)) {
			pParam->e_integer = 1;
			//save to <Param.-Buffer>.
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
		}
		else {
			pComd->err = _ERR_131_Invalid_suffix;
			_DEBUG_SHOW_ERROR;
		}
	}
	else if(pParam->n_space1) {
		if(((0x00 <= data)&&(0x09 >= data))||((0x0B <= data)&&(0x20 >= data))) {
		}
		else if(',' == data) {
			pComd->mhp = 1;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if(';' == data) {
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if('"' == data) {
			pParam->dq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
		else if('\'' == data) {
			pParam->sq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
		else if(('+' == data)||('-' == data)) {
			pComd->err = _ERR_121_Invalid_character_in_number;
			_DEBUG_SHOW_ERROR;
		}
		else if(('0' <= data)&&('9' >= data)) {
			pComd->err = _ERR_103_Invalid_separator;
			_DEBUG_SHOW_ERROR;
		}
		else if(('E' == data)||('e' == data)) {
			pParam->e_symbol = 1;
			//save to <Param.-Buffer>.
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
		}
		else if(('A' <= data)&&('Z' >= data)) {
			pParam->n_unit = 1;
			//save to <Unit-Buffer>.
			pParam->u_buf[pParam->u_len] = data + ('a' - 'A');
			pParam->u_len++;
		}
		else if(('a' <= data)&&('z' >= data)) {
			pParam->n_unit = 1;
			//save to <Unit-Buffer>.
			pParam->u_buf[pParam->u_len] = data;
			pParam->u_len++;
		}
		else if('_' == data) {
			pComd->err = _ERR_101_Invalid_character;
			_DEBUG_SHOW_ERROR;
		}
		else {
			pComd->err = _ERR_103_Invalid_separator;
			_DEBUG_SHOW_ERROR;
		}
	}
	else if(pParam->n_decimal) {
		if(((0x00 <= data)&&(0x09 >= data))||((0x0B <= data)&&(0x20 >= data))) {
			pParam->n_space1 = 1;
		}
		else if(',' == data) {
			pComd->mhp = 1;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if(';' == data) {
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if('"' == data) {
			pParam->dq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
		else if('\'' == data) {
			pParam->sq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
		else if(('+' == data)||('-' == data)) {
			pComd->err = _ERR_121_Invalid_character_in_number;
			_DEBUG_SHOW_ERROR;
		}
		else if(('0' <= data)&&('9' >= data)) {
			pParam->n_decimal = 1;
			//save to <Param.-Buffer>.
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
		}
		else if(('E' == data)||('e' == data)) {
			pParam->e_symbol = 1;
			//save to <Param.-Buffer>.
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
		}
		else if(('A' <= data)&&('Z' >= data)) {
			pParam->n_unit = 1;
			//save to <Unit-Buffer>.
			pParam->u_buf[pParam->u_len] = data + ('a' - 'A');
			pParam->u_len++;
		}
		else if(('a' <= data)&&('z' >= data)) {
			pParam->n_unit = 1;
			//save to <Unit-Buffer>.
			pParam->u_buf[pParam->u_len] = data;
			pParam->u_len++;
		}
		else if('_' == data) {
			pComd->err = _ERR_101_Invalid_character;
			_DEBUG_SHOW_ERROR;
		}
		else {
			pComd->err = _ERR_103_Invalid_separator;
			_DEBUG_SHOW_ERROR;
		}
	}
	else if(pParam->n_dot) {
		if(((0x00 <= data)&&(0x09 >= data))||((0x0B <= data)&&(0x20 >= data))) {
			pParam->n_space1 = 1;
		}
		else if(',' == data) {
			pComd->mhp = 1;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if(';' == data) {
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if('"' == data) {
			pParam->dq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
		else if('\'' == data) {
			pParam->sq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
        else if(('+' == data)||('-' == data)) {
			pComd->err = _ERR_121_Invalid_character_in_number;
			_DEBUG_SHOW_ERROR;
        }
        else if(('0' <= data)&&('9' >= data)) {
			pParam->n_decimal = 1;
			//save to <Param.-Buffer>.
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
        }
        else if(('E' == data)||('e' == data)) {
			pParam->e_symbol = 1;
			//save to <Param.-Buffer>.
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
        }
        else if(('A' <= data)&&('Z' >= data)) {
			pParam->n_unit = 1;
			//save to <Unit-Buffer>.
			pParam->u_buf[pParam->u_len] = data + ('a' - 'A');
			pParam->u_len++;
        }
        else if(('a' <= data)&&('z' >= data)) {
			pParam->n_unit = 1;
			//save to <Unit-Buffer>.
			pParam->u_buf[pParam->u_len] = data;
			pParam->u_len++;
        }
        else if('_' == data) {
			pComd->err = _ERR_101_Invalid_character;
			_DEBUG_SHOW_ERROR;
        }
        else {
			pComd->err = _ERR_103_Invalid_separator;
			_DEBUG_SHOW_ERROR;
        }
    }
	else if(pParam->n_integer) {
		if(((0x00 <= data)&&(0x09 >= data))||((0x0B <= data)&&(0x20 >= data))) {
			pParam->n_space1 = 1;
		}
		else if(',' == data) {
			pComd->mhp = 1;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if(';' == data) {
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if('"' == data) {
			pParam->dq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
		else if('\'' == data) {
			pParam->sq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
		else if('.' == data) {
			pParam->n_dot = 1;
			//save to <Param.-Buffer>.
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
		}
		else if(('+' == data)||('-' == data)) {
			pComd->err = _ERR_121_Invalid_character_in_number;
			_DEBUG_SHOW_ERROR;
		}
		else if(('0' <= data)&&('9' >= data)) {
			pParam->n_integer = 1;
			//save to <Param.-Buffer>.
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
		}
		else if(('E' == data)||('e' == data)) {
			pParam->e_symbol = 1;
			//save to <Param.-Buffer>.
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
		}
		else if(('A' <= data)&&('Z' >= data)) {
			pParam->n_unit = 1;
			//save to <Unit-Buffer>.
			pParam->u_buf[pParam->u_len] = data + ('a' - 'A');
			pParam->u_len++;
		}
		else if(('a' <= data)&&('z' >= data)) {
			pParam->n_unit = 1;
			//save to <Unit-Buffer>.
			pParam->u_buf[pParam->u_len] = data;
			pParam->u_len++;
		}
		else {
			pComd->err = _ERR_101_Invalid_character;
			_DEBUG_SHOW_ERROR;
		}
	}
	else if(pParam->n_sign) {
		if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_PACKAGE_MSQ;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
			pComd->err = _ERR_121_Invalid_character_in_number;
			_DEBUG_SHOW_ERROR;
		}
		else if(('0' <= data)&&('9' >= data)) {
			pParam->n_integer = 1;
			//save to <Param.-Buffer>.
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
		}
		else {
			pComd->err = _ERR_121_Invalid_character_in_number;
			_DEBUG_SHOW_ERROR;
		}
	}
	else {
		pComd->err = _ERR_140_Character_data_error;
		_DEBUG_SHOW_ERROR;
	}
}


void parseCharacterProgramData(STR_PARSER *p, char data)
{
	//-------------------------------------------------------------------------------------------
	// Keyword format :
	// {min | max | def}[space1] { ',' | ';' | '\n' }

	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)	(p->pComd);
	STR_PARSER_PARAM *pParam = (STR_PARSER_PARAM *) (p->pParam);

	if(_ERR_000_No_Error != pComd->err) {
		if('\n' == data) {
            pComd->endword = 1;
            pComd->mhp = 0;
            pComd->fun = _PARSER_PACKAGE_MSQ;
        }
		else if('"' == data) {
			if(1 == pParam->dq_start) {
				if(0 == pParam->dq_end) {
					pParam->dq_end = 1;
					pComd->err = _ERR_103_Invalid_separator;
					_DEBUG_SHOW_ERROR;
				}
				else {
					pParam->dq_end = 0;
					pComd->err = _ERR_151_Invalid_string_data;
					_DEBUG_SHOW_ERROR;
				}
			}
			else {
				//abandon the data.
			}
		}
		else if('\'' == data) {
			if(1 == pParam->sq_start) {
				if(0 == pParam->sq_end) {
					pParam->sq_end = 1;
					pComd->err = _ERR_103_Invalid_separator;
					_DEBUG_SHOW_ERROR;
				}
				else {
					pParam->sq_end = 0;
					pComd->err = _ERR_151_Invalid_string_data;
					_DEBUG_SHOW_ERROR;
				}
			}
			else {
				//abandon the data.
			}
		}
		else {
			//abandon the data.
		}
	}
	else {
		if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
		}
		else if(';' == data) {
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
		}
		else if(',' == data) {
			pComd->mhp = 1;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
		}
		else if('"' == data) {
			pComd->err = _ERR_151_Invalid_string_data;
			pParam->dq_start = 1;
			_DEBUG_SHOW_ERROR;
		}
		else if('\'' == data) {
			pComd->err = _ERR_151_Invalid_string_data;
			pParam->sq_start = 1;
			_DEBUG_SHOW_ERROR;
		}
		else if(((0x00 <= data)&&(0x09 >= data))||((0x0B <= data)&&(0x20 >= data))) {
		//White Space.
			pParam->n_space1 = 1;
		}
		else if(('0' <= data)&&('9' >= data)) {
			if(pParam->n_space1) {
				pComd->err = _ERR_103_Invalid_separator;
				_DEBUG_SHOW_ERROR;
			}
			else {
				//save to <Param-Buffer>.
				pParam->p_buf[pParam->p_len]=data;
				pParam->p_len++;
			}
		}
		else if(('A' <= data)&&('Z' >= data)) {
			if(pParam->n_space1) {
				pComd->err = _ERR_103_Invalid_separator;
				_DEBUG_SHOW_ERROR;
			}
			else {
				//save to <Param-Buffer>.
				pParam->p_buf[pParam->p_len]=data + ('a' - 'A');
				pParam->p_len++;
			}
		}
		else if(('a' <= data)&&('z' >= data)) {
			if(pParam->n_space1) {
				pComd->err = _ERR_103_Invalid_separator;
				_DEBUG_SHOW_ERROR;
			}
			else {
				//save to <Param-Buffer>.
				pParam->p_buf[pParam->p_len]=data;
				pParam->p_len++;
			}
		}
		else if('_' == data) {
			if(pParam->n_space1) {
				pComd->err = _ERR_103_Invalid_separator;
				_DEBUG_SHOW_ERROR;
			}
			else {
				//save to <Param-Buffer>.
				pParam->p_buf[pParam->p_len]=data;
				pParam->p_len++;
			}
		}
		else {
			pComd->err = _ERR_224_Illegal_parameter_value;
			_DEBUG_SHOW_ERROR;
		}
	}
}

void parseStringProgramData(STR_PARSER *p, char data)
{
	//-------------------------------------------------------------------------
	// string format :
	// <1> : "(dq_start) string1 [""] string1"(dq_end)[space1] { ',' | '\n' }
	// <2> : '(sq_start) string1 [''] string1'(sq_end)[space1] { ',' | '\n' }

	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)	(p->pComd);
	STR_PARSER_PARAM *pParam = (STR_PARSER_PARAM *) (p->pParam);

	if(_ERR_000_No_Error != pComd->err) {
		if('\n' == data) {
            pComd->endword = 1;
            pComd->mhp = 0;
            pComd->fun = _PARSER_PACKAGE_MSQ;
        }
		else if('"' == data) {
			if(1 == pParam->dq_start) {
				if(0 == pParam->dq_end) {
					pParam->dq_end = 1;
					pComd->err = _ERR_103_Invalid_separator;
					_DEBUG_SHOW_ERROR;
				}
				else {
					pParam->dq_end = 0;
					pComd->err = _ERR_151_Invalid_string_data;
					_DEBUG_SHOW_ERROR;
				}
			}
			else {
				//abandon the data.
			}
		}
		else if('\'' == data) {
			if(1 == pParam->sq_start) {
				if(0 == pParam->sq_end) {
					pParam->sq_end = 1;
					pComd->err = _ERR_103_Invalid_separator;
					_DEBUG_SHOW_ERROR;
				}
				else {
					pParam->sq_end = 0;
					pComd->err = _ERR_151_Invalid_string_data;
					_DEBUG_SHOW_ERROR;
				}
			}
			else {
				//abandon the data.
			}
		}
		else {
			//abandon the data.
		}
	}
	else {
		if(pParam->dq_start) {
			if(pParam->dq_end) {
				if('\n' == data) {
					pComd->endword = 1;
					pComd->mhp = 0;
					pComd->fun = _PARSER_CHECK_PARAMETER;
					pParam->p_buf[pParam->p_len] = '\0';
				}
				else if(';' == data) {
					pComd->mhp = 0;
					pComd->fun = _PARSER_CHECK_PARAMETER;
					pParam->p_buf[pParam->p_len] = '\0';
				}
				else if(',' == data) {
					pComd->mhp = 1;
					pComd->fun = _PARSER_CHECK_PARAMETER;
					pParam->p_buf[pParam->p_len] = '\0';
				}
				else if('"' == data) {
					if(pParam->n_space1) {
						pComd->err = _ERR_151_Invalid_string_data;
						_DEBUG_SHOW_ERROR;
					}
					else {
						pParam->p_buf[pParam->p_len] = data;
						pParam->p_len++;
						pParam->dq_end = 0;
					}
				}
				else if(((0x00 <= data)&&(0x09 >= data))||((0x0B <= data)&&(0x20 >= data))) {
				//White Space.
					pParam->n_space1 = 1;
				}
				else {
					pComd->err = _ERR_103_Invalid_separator;
					_DEBUG_SHOW_ERROR;
				}
			}
			else { //(0 == pParam->dq_end)
				if('"' == data) {
					pParam->dq_end = 1;
					pParam->p_buf[pParam->p_len] = '\0';
				}
				else if('\n' == data) {
					pComd->endword = 1;
					pComd->mhp = 0;
					pComd->fun = _PARSER_PACKAGE_MSQ;
					pComd->err = _ERR_151_Invalid_string_data;
					_DEBUG_SHOW_ERROR;
				}
				else {
					pParam->p_buf[pParam->p_len] = data;
					pParam->p_len++;
				}
			}
		}
		else if(pParam->sq_start) {
			if(pParam->sq_end) {
				if('\n' == data) {
					pComd->endword = 1;
					pComd->mhp = 0;
					pComd->fun = _PARSER_CHECK_PARAMETER;
					pParam->p_buf[pParam->p_len] = '\0';
				}
				else if(';' == data) {
					pComd->mhp = 0;
					pComd->fun = _PARSER_CHECK_PARAMETER;
					pParam->p_buf[pParam->p_len] = '\0';
				}
				else if(',' == data) {
					pComd->mhp = 1;
					pComd->fun = _PARSER_CHECK_PARAMETER;
					pParam->p_buf[pParam->p_len] = '\0';
				}
				else if('\'' == data) {
					if(pParam->n_space1) {
						pComd->err = _ERR_151_Invalid_string_data;
						_DEBUG_SHOW_ERROR;
					}
					else {
						pParam->p_buf[pParam->p_len] = data;
						pParam->p_len++;
						pParam->sq_end = 0;
					}
				}
				else if(((0x00 <= data)&&(0x09 >= data))||((0x0B <= data)&&(0x20 >= data))) {
				//White Space.
					pParam->n_space1 = 1;
				}
				else {
					pComd->err = _ERR_103_Invalid_separator;
					_DEBUG_SHOW_ERROR;
				}
			}
			else { //(0 == pParam->dq_end)
				if('\'' == data) {
					pParam->sq_end = 1;
					pParam->p_buf[pParam->p_len] = '\0';
				}
				else if('\n' == data) {
					pComd->endword = 1;
					pComd->mhp = 0;
					pComd->fun = _PARSER_PACKAGE_MSQ;
					pComd->err = _ERR_151_Invalid_string_data;
					_DEBUG_SHOW_ERROR;
				}
				else {
					pParam->p_buf[pParam->p_len] = data;
					pParam->p_len++;
				}
			}
		}
		else {
			if('\n' == data) {
				pComd->endword = 1;
				pComd->mhp = 0;
				pComd->fun = _PARSER_PACKAGE_MSQ;
			}
			pComd->err = _ERR_103_Invalid_separator;
			_DEBUG_SHOW_ERROR;
		}
	}
}

void parseNonDecimalNumericProgramData(STR_PARSER *p, char data)
{
	//-------------------------------------------------------------------------------------------
	// --- Non-Decimal Numeric Program Data ---
	// binary format  : #[B|b]<0~1><0~1>...<0~1>+NL.
	// octonary format : #[Q|q]<0~7><0~7>...<0~7>+NL.
	// hexadecimal format : #[H|h]<0~9,A~F><0~9,A~F>...<0~9,A~F>+NL.
	// Defined length of block data format : #<number digits in byte count><byte count><Byte1><Byte2>...<ByteN>+NL.
	// Undefined length of block data format : #0<Byte1><Byte2>...<ByteN>+NL+^End.

	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)	(p->pComd);
	STR_PARSER_PARAM *pParam = (STR_PARSER_PARAM *) (p->pParam);

	if(_ERR_000_No_Error != pComd->err) {
		if('\n' == data) {
            pComd->endword = 1;
            pComd->mhp = 0;
            pComd->fun = _PARSER_PACKAGE_MSQ;
        }
		else {
			//abandon the data.
		}
	}
	else {
		if('\n' == data) {
            pComd->endword = 1;
            pComd->mhp = 0;
            pComd->fun = _PARSER_PACKAGE_MSQ;
			pComd->err = _ERR_101_Invalid_character;
			_DEBUG_SHOW_ERROR;
        }
		else if('0' == data) { //Undefined length of block data.
			if(0 == scpiBlock_Prepare(p)) {
				scpiBlock_SaveByte(p, '#');
				scpiBlock_SaveByte(p, data);
				pParam->t_n_dec = 0;
				pParam->t_block_ind = 1;
				pParam->get_count  = 0;
				pParam->bd_digital = 0; //get <number digits in byte count>.
				pParam->bd_count   = 0;
				pParam->bd_data    = 0;
				pParam->p_len = 0;
			}
			else {
				pComd->err = _ERR_161_Invalid_block_data;
				_DEBUG_SHOW_ERROR;
			}
		}
		else if(('1' <= data)&&('9' >= data)) { //Defined length of block data.
			if(0 == scpiBlock_Prepare(p)) {
				scpiBlock_SaveByte(p, '#');
				scpiBlock_SaveByte(p, data);
				pParam->t_n_dec = 0;
				pParam->t_block_def = 1;
				pParam->get_count  = 1;
				pParam->bd_digital = data - '0'; //get <number digits in byte count>.
				pParam->bd_count   = 0;
				pParam->bd_data    = 0;
				pParam->p_len = 0;
			}
			else {
				pComd->err = _ERR_161_Invalid_block_data;
				_DEBUG_SHOW_ERROR;
			}
		}
		else if(('H' == data)||('h' == data)) {
			//Hexadecimal data.
			pParam->t_n_dec = 0;
			pParam->t_base16 = 1;
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
		}
		else if(('Q' == data)||('q' == data)) {
			//Octonary data.
			pParam->t_n_dec = 0;
			pParam->t_base8 = 1;
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
		}
		else if(('B' == data)||('b' == data)) {
			//Binary data.
			pParam->t_n_dec = 0;
			pParam->t_base2 = 1;
			pParam->p_buf[pParam->p_len] = data;
			pParam->p_len++;
		}
		else {
			pComd->err = _ERR_101_Invalid_character;
			_DEBUG_SHOW_ERROR;
		}
	}
}

void parseBaseNumericProgramData(STR_PARSER *p, char data)
{
	//-------------------------------------------------------------------------------------------
	// --- Non-Decimal Numeric Program Data ---
	// binary format  : #[B|b]<0~1><0~1>...<0~1>[space]+NL.
	// octonary format : #[Q|q]<0~7><0~7>...<0~7>[space]+NL.
	// hexadecimal format : #[H|h]<0~9,A~F><0~9,A~F>...<0~9,A~F>[space]+NL.

	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)	(p->pComd);
	STR_PARSER_PARAM *pParam = (STR_PARSER_PARAM *) (p->pParam);


	if(_ERR_000_No_Error != pComd->err) {
		if('\n' == data) {
            pComd->endword = 1;
            pComd->mhp = 0;
            pComd->fun = _PARSER_PACKAGE_MSQ;
        }
		else if('"' == data) {
			if(1 == pParam->dq_start) {
				if(0 == pParam->dq_end) {
					pParam->dq_end = 1;
					pComd->err = _ERR_103_Invalid_separator;
					_DEBUG_SHOW_ERROR;
				}
				else {
					pParam->dq_end = 0;
					pComd->err = _ERR_151_Invalid_string_data;
					_DEBUG_SHOW_ERROR;
				}
			}
			else {
				//abandon the data.
			}
		}
		else if('\'' == data) {
			if(1 == pParam->sq_start) {
				if(0 == pParam->sq_end) {
					pParam->sq_end = 1;
					pComd->err = _ERR_103_Invalid_separator;
					_DEBUG_SHOW_ERROR;
				}
				else {
					pParam->sq_end = 0;
					pComd->err = _ERR_151_Invalid_string_data;
					_DEBUG_SHOW_ERROR;
				}
			}
			else {
				//abandon the data.
			}
		}
		else {
			//abandon the data.
		}
	}
	else {
		if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if(';' == data) {
			pComd->mhp = 0;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if(',' == data) {
			pComd->mhp = 1;
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pParam->p_buf[pParam->p_len] = '\0';
			pParam->u_buf[pParam->u_len] = '\0';
		}
		else if('"' == data) {
			pParam->dq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
        else if('\'' == data) {
			pParam->sq_start = 1;
			pComd->err = _ERR_151_Invalid_string_data;
			_DEBUG_SHOW_ERROR;
		}
		else if(((0x00 <= data)&&(0x09 >= data))||((0x0B <= data)&&(0x20 >= data))) {
		//White Space.
			pParam->n_space1 = 1;
		}
		else if(pParam->t_base2) {
			if(('0' == data)||('1' == data)) {
				if(pParam->n_space1) {
					pComd->err = _ERR_103_Invalid_separator;
					_DEBUG_SHOW_ERROR;
				}
				else {
					//save to <Param-Buffer>.
					pParam->p_buf[pParam->p_len]=data;
					pParam->p_len++;
				}
			}
			else {
				pComd->err = _ERR_121_Invalid_character_in_number;
				_DEBUG_SHOW_ERROR;
			}
		}
		else if(pParam->t_base8) {
			if(('0' <= data)&&('7' >= data)) {
				if(pParam->n_space1) {
					pComd->err = _ERR_103_Invalid_separator;
					_DEBUG_SHOW_ERROR;
				}
				else {
					//save to <Param-Buffer>.
					pParam->p_buf[pParam->p_len]=data;
					pParam->p_len++;
				}
			}
			else {
				pComd->err = _ERR_121_Invalid_character_in_number;
				_DEBUG_SHOW_ERROR;
			}
		}
		else if(pParam->t_base16) {
			if(('0' <= data)&&('9' >= data)) {
				if(pParam->n_space1) {
					pComd->err = _ERR_103_Invalid_separator;
					_DEBUG_SHOW_ERROR;
				}
				else {
					//save to <Param-Buffer>.
					pParam->p_buf[pParam->p_len]=data;
					pParam->p_len++;
				}
			}
			else if(('A' <= data)&&('F' >= data)) {
				if(pParam->n_space1) {
					pComd->err = _ERR_103_Invalid_separator;
					_DEBUG_SHOW_ERROR;
				}
				else {
					//save to <Param-Buffer>.
					pParam->p_buf[pParam->p_len]=data;
					pParam->p_len++;
				}
			}
			else if(('a' <= data)&&('f' >= data)) {
				if(pParam->n_space1) {
					pComd->err = _ERR_103_Invalid_separator;
					_DEBUG_SHOW_ERROR;
				}
				else {
					//save to <Param-Buffer>.
					pParam->p_buf[pParam->p_len]=data;
					pParam->p_len++;
				}
			}
			else {
				pComd->err = _ERR_121_Invalid_character_in_number;
				_DEBUG_SHOW_ERROR;
			}
		}
		else {
			pComd->err = _ERR_108_Parameter_not_allowed;
			_DEBUG_SHOW_ERROR;
		}
	}
}

void parseDefinitelyLengthBlockProgramData(STR_PARSER *p, char data)
{
	//-------------------------------------------------------------------------------------------
	// --- Defined length of block Program Data ---
	// format : #<number digits in byte count><byte count><Byte1><Byte2>...<ByteN>+NL.

	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)	(p->pComd);
	STR_PARSER_PARAM *pParam = (STR_PARSER_PARAM *) (p->pParam);
	int err = 0;

	if(_ERR_000_No_Error != pComd->err) {
		if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_PACKAGE_MSQ;
		}
		else {
			//abandon the data.
		}
	}
	else {
		if(1 == pParam->get_count) {
			//get <byte count>.
			err = (p->read)((char*) &(pParam->p_buf[pParam->p_len]), (pParam->bd_digital - pParam->p_len), _GW_IORD);
			if(0 < err) {
				pParam->p_len += err;
				if(pParam->p_len == pParam->bd_digital) {
					if(0 == gw_CLIB_IsDecimalString(pParam->p_buf , pParam->p_len)) {
						pParam->get_count = 0;
						pParam->p_buf[pParam->p_len] = '\0';
						pParam->bd_count  = (int)atoi((char*)(&(pParam->p_buf)));
						pParam->bd_data   = 0;
						scpiBlock_SaveData(p, pParam->p_buf , pParam->p_len);
					}
					else {
						pComd->err = _ERR_161_Invalid_block_data;
					}
				}
			}
		}
		else {
			//get <Byte1><Byte2>...<ByteN>.
			if(pParam->bd_count > pParam->bd_data) {
				err = (pParam->bd_count - pParam->bd_data);
				if(_READ_PAGE < err )	err = _READ_PAGE;
				err = (p->read)((char*) scpiBlock_GetAddressStorage(p), err, _GW_IORD);
				if(0 < err) {
					scpiBlock_UpdateAddressStorage(p, err);
					pParam->bd_data += err;
				}
			}
			else if(pParam->bd_count == pParam->bd_data) {
				err = (p->read)((char*) &data, 1, _GW_IORD);
				if(0 < err) {
					if('\n' == data) {
						scpiBlock_Close(p);
						pComd->endword = 1;
						pComd->mhp = 0;
						pComd->fun = _PARSER_PACKAGE_MSQ;
					}
					else {
						pComd->err = _ERR_160_Block_data_error;
					}
				}
			}
			else {
				pComd->err = _ERR_161_Invalid_block_data;
			}
		}
	}
}

void parseIndefinitelyLengthBlockProgramData(STR_PARSER *p, char data)
{
	//-------------------------------------------------------------------------------------------
	// --- Indefined length of block Program Data ---
	// format : #0<Byte1><Byte2>...<ByteN>+NL+^End.

	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)	(p->pComd);
	STR_PARSER_PARAM *pParam = (STR_PARSER_PARAM *) (p->pParam);

	if(_ERR_000_No_Error != pComd->err) {
		if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_PACKAGE_MSQ;
		}
		else {
			//abandon the data.
		}
	}
	else {
		if('\n' == data) {
			scpiBlock_Close(p);
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_PACKAGE_MSQ;
		}
		else {
			if(0 == scpiBlock_SaveByte(p, data)) {
				pParam->bd_data++;
			}
			else {
				pComd->err = _ERR_160_Block_data_error;
			}
		}
	}
}

void parseExpressionProgramData(STR_PARSER *p, char data)
{
	//-------------------------------------------------------------------------------------------
	// --- Expression Program Data ---
	// format : (100+15),(100-15),(10*15),(100/20),(@1 : 3).

	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)	(p->pComd);
	//STR_PARSER_PARAM *pParam = (STR_PARSER_PARAM *) (p->pParam);

	if(_ERR_000_No_Error != pComd->err) {
		if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_PACKAGE_MSQ;
		}
		else {
			//abandon the data.
		}
	}
	else {
		if('\n' == data) {
			pComd->endword = 1;
			pComd->mhp = 0;
			pComd->fun = _PARSER_PACKAGE_MSQ;
		}
		pComd->err = _ERR_178_Expression_data_not_allowed; //Does not currently support this feature.
	}
}

void parseTypeProgramData(STR_PARSER *p, char data)
{
	//-------------------------------------------------------------------------------------------
	// --- Parse Tpye Program Data ---
	// format : (100+15),(100-15),(10*15),(100/20),(@1 : 3).

	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)	(p->pComd);
	STR_PARSER_PARAM *pParam = (STR_PARSER_PARAM *) (p->pParam);

	if(_ERR_000_No_Error != pComd->err) {
		if('\n' == data) {
            pComd->endword = 1;
            pComd->mhp = 0;
            pComd->fun = _PARSER_PACKAGE_MSQ;
        }
		else if('"' == data) {
			if(1 == pParam->dq_start) {
				if(0 == pParam->dq_end) {
					pParam->dq_end = 1;
					pComd->err = _ERR_103_Invalid_separator;
				}
				else {
					pParam->dq_end = 0;
					pComd->err = _ERR_151_Invalid_string_data;
				}
			}
			else {
				//abandon the data.
			}
		}
		else if('\'' == data) {
			if(1 == pParam->sq_start) {
				if(0 == pParam->sq_end) {
					pParam->sq_end = 1;
					pComd->err = _ERR_103_Invalid_separator;
				}
				else {
					pParam->sq_end = 0;
					pComd->err = _ERR_151_Invalid_string_data;
				}
			}
			else {
				//abandon the data.
			}
		}
		else {
			//abandon the data.
		}
	}
	else {
		if('\n' == data) {
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pComd->endword = 1;
			pComd->mhp = 0;
			pParam->p_buf[pParam->p_len] = '\0';
		}
		else if(';' == data) {
			pComd->fun = _PARSER_CHECK_PARAMETER;
			pComd->mhp = 0;
			pParam->p_buf[pParam->p_len] = '\0';
		}
		else if('"' == data) {
			pParam->t_str = 1;//_PT_STR
			pParam->dq_start = 1;
		}
		else if('\'' == data) {
			pParam->t_str = 1;//_PT_STR
			pParam->sq_start = 1;
		}
		else if(((0x00 <= data)&&(0x09 >= data))||((0x0B <= data)&&(0x20 >= data))) {
			pComd->space = 1; //White Space.
		}
		else if(('+' == data)||('-' == data)) {
			if(pComd->space) {
				pParam->n_sign = 1;
				pParam->t_num = 1;//_PT_NUM
				pParam->p_buf[pParam->p_len] = data;
				pParam->p_len++;
			}
			else {
				pComd->err = _ERR_103_Invalid_separator;
			}
		}
		else if(('0' <= data)&&('9' >= data)) {
			if(pComd->space) {
				pParam->n_sign = 0;
				pParam->n_integer= 1;
				pParam->t_num = 1;//_PT_NUM
				pParam->p_buf[pParam->p_len] = data;
				pParam->p_len++;
			}
			else {
				pComd->err = _ERR_103_Invalid_separator;
			}
		}
		else if('.' == data) {
			if(pComd->space) {
				pParam->n_sign = 0;
				pParam->n_integer= 0;
				pParam->n_dot= 1;
				pParam->t_num = 1;//_PT_NUM
				pParam->p_buf[pParam->p_len] = data;
				pParam->p_len++;
			}
			else {
				pComd->err = _ERR_121_Invalid_character_in_number;
			}
		}
/*
		else if(('E' == data)&&('e' >= data)) {
			if(pComd->space) {
				pComd->err = _ERR_224_Illegal_parameter_value;
			}
			else {
				pComd->err = _ERR_103_Invalid_separator;
			}
		}
*/
		else if(('A' <= data)&&('Z' >= data)) {
			if(pComd->space) {
				pParam->t_kw = 1;//_PT_KW
				pParam->p_buf[pParam->p_len] = data + ('a' - 'A');
				pParam->p_len++;
			}
			else {
				pComd->err = _ERR_103_Invalid_separator;
			}
		}
		else if(('a' <= data)&&('z' >= data)) {
			if(pComd->space) {
				pParam->t_kw = 1;//_PT_KW
				pParam->p_buf[pParam->p_len] = data;
				pParam->p_len++;
			}
			else {
				pComd->err = _ERR_103_Invalid_separator;
			}
		}
		else if('#' == data) { //Non-Decimal numberic program data.
			if(pComd->space) {
				pComd->mhp = 0;
				pParam->t_n_dec = 1;
			}
			else {
				pComd->err = _ERR_101_Invalid_character;
			}
		}
		else if('(' == data) { //Expression program data.
			if(pComd->space) {
				pComd->mhp = 0;
				pParam->t_express = 1;
			}
			else {
				pComd->err = _ERR_103_Invalid_separator;
			}
		}
		else if((':' == data)||('*' == data)||(',' == data)||('@' == data)||('?' == data)||(')' == data)) {
			if(pComd->space) {
				pComd->err = _ERR_102_Syntax_error;
			}
			else {
				pComd->err = _ERR_103_Invalid_separator;
			}
		}
		else {
			pComd->err = _ERR_101_Invalid_character;
		}
	}
}

//-----------------------------------------------
//---
void scpiGetParameter(STR_PARSER *p)
{
	int err = _NO_ERROR, cnt = 0;
	char data = 0;
	STR_PARSER_COMD  *pComd  = (STR_PARSER_COMD *)  (p->pComd);
	STR_PARSER_PARAM *pParam = (STR_PARSER_PARAM *) (p->pParam);

	while(_PARSER_GET_PARAMETER == pComd->fun) {
		if(0 == pParam->t_block_def) {
			err = (p->read)((char *) (&data), 1, _GW_IORD);
			if(0 >= err) break;	 /*Buffer empty or error.*/
		}
		if(0 == pParam->p_status) {
			parseTypeProgramData( p, data);
		}
		else if(pParam->t_num) {
			parseDecimalNumericProgramData( p, data);
		}
		else if(pParam->t_kw) {
			parseCharacterProgramData( p, data);
		}
		else if(pParam->t_str) {
			parseStringProgramData( p, data);
		}
		else if(pParam->t_n_dec) {
			parseNonDecimalNumericProgramData( p, data);
		}
		else if(pParam->t_base2 || pParam->t_base8 || pParam->t_base16) {
			parseBaseNumericProgramData( p, data);
		}
		else if(pParam->t_block_def) {
			parseDefinitelyLengthBlockProgramData( p, data);
		}
		else if(pParam->t_block_ind) {
			parseIndefinitelyLengthBlockProgramData( p, data);
		}
		else if(pParam->t_express) {
			parseExpressionProgramData( p, data);
		}
		else {
			if('\n' == data) {
				pComd->endword = 1;
				pComd->mhp = 0;
				pComd->fun = _PARSER_PACKAGE_MSQ;
				pComd->err = _ERR_310_System_error;
			}
			else {
				//abandon the data.
			}
		}
		//---------------------------------
		cnt++;
		if(_GET_CHAR_SIZE <= cnt)	break;
		//---------------------------------
	}
}

//-----------------------------------------------
//---
void scpiGetEndword(STR_PARSER *p)
{
	int err = 0;
    char data = 0;
	STR_PARSER_COMD *pComd = (STR_PARSER_COMD *) (p->pComd);

	while(_PARSER_GET_ENDWORD == pComd->fun) {
		err = (p->read)((char *) (&data), 1, _GW_IORD);//read 1 byte.

		if(0 < err){
			if('\n' == data) {
				pComd->fun = _PARSER_GET_NEXT_COMMAND;
				pComd->endword = 1;
			}
		}
		else{
			break;   /*Buffer empty.*/
		}
	}
}

//-----------------------------------------------
//---
void scpiParser(STR_PARSER *p)
{
	STR_PARSER_COMD *pComd = (STR_PARSER_COMD *) (p->pComd);
	STR_PARSER_DATA *pData = (STR_PARSER_DATA*)  (p->pData);
	int k;

	if(_PARSER_GET_COMMAND == pComd->fun) {
		scpiGetCommand(p);
	}
	if(_PARSER_CHECK_COMMAND == pComd->fun) {
		_DEBUG_PARSER(2);
		scpiCheckCommand(p);
	}
#if Enable_RemoteFast
		unsigned char i;
		for(i=0;i<10;i++){
			if(_PARSER_GET_PARAMETER == pComd->fun) {
				_DEBUG_PARSER(3);
				scpiGetParameter(p);
			}
			if(_PARSER_CHECK_PARAMETER == pComd->fun) {
				_DEBUG_PARSER(4);
				scpiCheckParameter(p);
			}
			if(_PARSER_GET_PARAMETER != pComd->fun)break;
		}
#else
		if(_PARSER_GET_PARAMETER == pComd->fun) {
			_DEBUG_PARSER(3);
			scpiGetParameter(p);
		}
		if(_PARSER_CHECK_PARAMETER == pComd->fun) {
			_DEBUG_PARSER(4);
			scpiCheckParameter(p);
		}
#endif


	if(_PARSER_PACKAGE_MSQ == pComd->fun) {
		_DEBUG_PARSER(5);
		if(_ERR_000_No_Error == pComd->err) {
			STR_PARAMS *para = (STR_PARAMS*) (&(parameters[pComd->pNow->id -1].data[pComd->query]));
			if((pData->number <= para->max)&&(pData->number >= para->min)) {
				unsigned int i = 0;
				for(i = 0; i < pComd->level; i++) {
					pData->suffix[pData->suf_level] = pComd->suf_var[i];
					pData->suf_level++;
				}
				pData->id	 = pComd->pNow->id;
				pData->query = pComd->query;
			}
			else if(pData->number < para->min) {
				pComd->err = _ERR_109_Missing_parameter;
				pData->id	 = 0;
				pData->query = 0;
			}
			else if(pData->number > para->max) {
				pComd->err = _ERR_115_Unexpected_number_of_parameters;
				pData->id	 = 0;
				pData->query = 0;
			}
			else {
				pComd->err = _ERR_108_Parameter_not_allowed;
				pData->id	 = 0;
				pData->query = 0;
			}
		}
		else {
			pData->id    = 0;
			pData->query = 0;
		}
		pData->dev = p->dev;


		if(_ERR_000_No_Error == pComd->err) {
			if(REM_CONT==0) {
				REM_CONT = 1;
				SysRedrawFlag |= REM_LOC_UPDATA;
			}
#if Enable_RemoteFast
			p->msgSend.func = 0;
			p->msgSend.data = (unsigned long) p;
			if(1 == pComd->query) {				
				scpiRunMSQ();
			}else{
				if(DGIOCtrlFlag&REM_Mode_Fast){ 			
					scpiRunMSQ();					
				}else{
					pComd->fun = _PARSER_SEND_MSQ;
				}
			}			
#else
			p->msgSend.func = 0;
			p->msgSend.data = (unsigned long) p;
			pComd->fun = _PARSER_SEND_MSQ;
#endif 
#if 1
			setLockRemote();			
#endif
		}
		else {
			if(0 == pComd->endword) {
				pComd->fun = _PARSER_GET_ENDWORD;
			}
			else {
				pComd->fun = _PARSER_GET_NEXT_COMMAND;
			}
		}

	}

	if(_PARSER_GET_ENDWORD == pComd->fun) {
		_DEBUG_PARSER(9);
		scpiGetEndword(p);
	}

    if(_PARSER_GET_NEXT_COMMAND == pComd->fun) {
		_DEBUG_PARSER(10);
		//-----------------------------------------------
		//--- Push Error Message to Error-Queue. ---
		if(_ERR_000_No_Error != pComd->err) {
			pushErrorQueue( &(p->errQueue), pComd->err);
		}
		else {
			if(1 == pComd->query) {
				p->countQuery++;
			}
		}

		if(1 == pComd->endword) {
			_DEBUG_PARSER(11);
			pComd->pNow = (NODES)&_nodeRoot;
			if(0 < p->countQuery) {
				p->countQuery = 0;
				if(_ERR_000_No_Error != pComd->err) {
					//---------------------------
					//---clean temporary data.---
					(p->write)(0, 0, _GW_IOWR_BUF_CLN);
					//---------------------------
				}
				else {
					//---------------------------
					//---Add Linefeed to Buf.---
					(p->write)((char *) "\n", 1, _GW_IOWR_END);
					//---------------------------
					//--approve temporary data.--
					(p->write)(0, 0, _GW_IOWR_BUF_APP);

					if(Output_Buffer_Count){
						Output_Buffer[Output_Buffer_Count++]='\n';
						Output_Buffer[Output_Buffer_Count++]=0;
						WOutgoBuffer((UBYTE *)Output_Buffer,1);
						Output_Buffer_Count=0;
					}
					if (_DEV_GPIB == p->dev){
						(p->ctrl)(_GW_IOCTL_SET_TX_TOTAL_SIZE,0);
					}
				}
			}
			scpiCleanSuffixOfPData(p);
		}
		else {
			pComd->pNow = pComd->pNow->parant;
			scpiUpdateSuffixOfPData(p);
		}
		scpi_StatusUpdate(p); //20130311,Jadvil.

		//-----------------------------------------------
		//--- Initial  Parser Process ---
		scpiInitPData(p);
        scpiInitParser(pComd);
        pComd->fun    = _PARSER_GET_COMMAND;
    }
}

//-----------------------------------------------

extern STR_PARSER parser_UART;
void scpiRunMSQ (void){
	STR_PARSER *p;
	p = (STR_PARSER *) (&parser_UART);	
	STR_PARSER_COMD *pComd = (STR_PARSER_COMD *) (p->pComd);
	
	_DEBUG_PARSER(6);

	if(_ERR_000_No_Error == pComd->err) {
		if(1) { //if(0 == PowerOnConfig) {
			CommandFun[p->pData->id].api(p);			
			/*
			if((Output_Buffer_Count)&&(1 == pComd->endword))
				{
					Output_Buffer[Output_Buffer_Count++]='\n';
					Output_Buffer[Output_Buffer_Count++]=0;
					WOutgoBuffer((UBYTE *)Output_Buffer,1);
					Output_Buffer_Count=0;
				}
			*/
			if(_ERR_000_No_Error == pComd->err) {
				if(0 < p->specProc.act) {
        			pComd->fun = _PARSER_SPECIAL_PROCESS;
				}
				else {
	        		pComd->fun = _PARSER_GET_NEXT_COMMAND;
				}
			}
			else {
				if(0 == pComd->endword) {
					pComd->fun = _PARSER_GET_ENDWORD;
				}
				else {
					pComd->fun = _PARSER_GET_NEXT_COMMAND;
				}
			}
			//return;
		}
	}else {
		if(0 == pComd->endword) {
			pComd->fun = _PARSER_GET_ENDWORD;
		}
		else {
			pComd->fun = _PARSER_GET_NEXT_COMMAND;
		}
	}
}


