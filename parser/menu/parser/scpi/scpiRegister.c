/******************************************************************************
 * Filename:	scpiRegister.c
 ******************************************************************************/

//==========================================================
//  include
//==========================================================
//#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <fcntl.h>
//#include <getopt.h>
#include <errno.h>
//#include <pthread.h>
//#include <semaphore.h>
//#include <sys/socket.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <linux/types.h>
//#include <linux/netlink.h>
#include <ctype.h>
//#include <sys/ipc.h>
//#include <sys/msg.h>

//#include "gw_board.h"
#include "../common/gw_CLib.h"
#include "scpiStruct.h"
#include "scpiError.h"
#include "scpiNode.h"
#include "scpiUnit.h"
#include "scpiErrQueue.h"
#include "scpiRegister.h"
#include "tty/devTtyDefine.h"
#include "scpiAPI.h"
extern int  usleep(int useconds);

//==========================================================
//  Debug
//==========================================================
#if 0
	#define _DEBUG_SHOW_MESSAGE(x)	printf("Mutex<%s> initialization failed.\n", x);
#else
	#define _DEBUG_SHOW_MESSAGE(x)
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

//-----------------------------------------------
//--- intf_Initial ---
//return :	0 => no error.
//			-1=> error.
int intf_Initial(STR_INTF *intf)
{
	if(intf) {
		intf->status.data  = 0;
		intf->request.data = 0;
		intf->address  = 0;
		intf->sre.data = 0;
		intf->stb.data = 0;
		intf->ese.data = 0;
		intf->esr.data = 0x80;
		intf->status.use = 1;
/*
		if(sem_init(&(intf->semRequest), 0, 0) != 0) {
			_DEBUG_SHOW_MESSAGE("Semaphore(semRequest) initialization failed!");
			return -1;
		}
		if (sem_init(&(intf->semDone), 0, 0) != 0)	{
			sem_destroy(&(intf->semRequest));
			_DEBUG_SHOW_MESSAGE("Semaphore(semDone) initialization failed!");
			return -1;
		}
		
*/
		return 0;
	}
	else return -1;
}

//-----------------------------------------------
//--- intf_Close ---
//return :	0 => no error.
//			-1=> error.
int intf_Close(STR_INTF *intf)
{
	if(intf) {
		if(0 == intf->status.use)	return -1;
		///sem_destroy(&(intf->semRequest));
		///sem_destroy(&(intf->semDone));
		intf->status.use = 0;
		return 0;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfRequest_SetData ---
//return :	positive => SPE data.
//			-1=> error.
int intfRequest_SetData(STR_INTF *intf, int cmd, unsigned long arg)
{
	if(intf) {
		if(0 == intf->status.use)	return -1;
		//intf->request.data |= (cmd & _INTF_REQUEST_MASK);
		if(_INTF_REQUEST_ADDRESS & cmd) {
			//intf->address = arg;
		}
		else if(_INTF_REQUEST_TERMINAL & cmd) {
//			intf->terminal = *((struct termios*)arg);
		}
		else {
		}
		///sem_post(&(intf->semRequest));
		//usleep(20000);//20ms.
		///sem_wait(&(intf->semDone));
		return 0;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfRequest_GetData ---
//return :	positive => SPE data.
//			-1=> error.
int intfRequest_GetData(STR_INTF *intf, int cmd, unsigned long arg)
{
	if(intf) {
		if(0 == intf->status.use)	return -1;
		if(_INTF_REQUEST_ADDRESS & intf->request.data & cmd) {
			// *((unsigned int*)arg) = intf->address;
		}
		else if(_INTF_REQUEST_TERMINAL & intf->request.data  & cmd) {
	///		*((struct termios*)arg) = intf->terminal;
		}
		else {
		}
		return 0;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfRequest_IsRequest ---
//return :	positive => SPE data.
//			-1=> error.
int intfRequest_IsRequest(STR_INTF *intf)
{
	if(intf) {
		int status = 0;
		if(0 == intf->status.use)	return -1;
		///if( !sem_trywait(&(intf->semRequest)) ) {
		///	status = intf->request.data & _INTF_REQUEST_MASK;
		///}
		return status;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfRequest_Clean ---
//return :	positive => SPE data.
//			-1=> error.
int intfRequest_Clean(STR_INTF *intf)
{
	if(intf) {
		if(0 == intf->status.use)	return -1;
		//intf->request.data = 0;
		///sem_post(&(intf->semDone));
		return 0;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfStatus_SetStatus ---
//return :	positive => SPE data.
//			-1=> error.
int intfStatus_SetStatus(STR_INTF *intf, int data)
{
	if(intf) {
		int status = 0;
		if(0 == intf->status.use)	return -1;
		intf->status.data |= (data & _INTF_STATUS_MASK);
		status = intf->status.data & _INTF_STATUS_MASK;
		return status;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfStatus_GetStatus ---
//return :	positive => SPE data.
//			-1=> error.
int intfStatus_GetStatus(STR_INTF *intf)
{
	if(intf) {
		int status = 0;
		if(0 == intf->status.use)	return -1;
		status = intf->status.data & _INTF_STATUS_MASK;
		intf->status.data_in = 0;
		intf->status.data_out= 0;
		return status;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfStatus_CleanStatus ---
//return :	positive => SPE data.
//			-1=> error.
int intfStatus_CleanStatus(STR_INTF *intf, int data)
{
	if(intf) {
		int status = 0;
		if(0 == intf->status.use)	return -1;
		intf->status.data &= ((~data) & _INTF_STATUS_MASK);
		status = intf->status.data & _INTF_STATUS_MASK;
		return status;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfStatus_IsRemote ---
//return :	0 => Local Control.
//			1 => Remote Control.
//			-1=> error.
int intfStatus_IsRemote(STR_INTF *intf)
{
	if(intf) {
		int status = 0;
		if(0 == intf->status.use)	return -1;
		status = (intf->status.data_in) || (intf->status.data_out) || (intf->status.tx_empty);
		intf->status.data_in = 0;
		intf->status.data_out = 0;
		intf->status.tx_empty = 0;
		return status;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfStatus_IsReceiveData ---
//return :	0 => Not received the data ,and clean the flag.
//			1 => Receiving data ,and clean the flag.
//			-1=> error.
int intfStatus_IsReceiveData(STR_INTF *intf)
{
	if(intf) {
		int status = 0;
		if(0 == intf->status.use)	return -1;
		status = intf->status.data_in;
		intf->status.data_in = 0;
		return status;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfStatus_IsSendData ---
//return :	0 => No transmission of data ,and clean the flag.
//			1 => Sending data ,and clean the flag.
//			-1=> error.
int intfStatus_IsSendData(STR_INTF *intf)
{
	if(intf) {
		int status = 0;
		if(0 == intf->status.use)	return -1;
		status = intf->status.data_out;
		intf->status.data_out = 0;
		return status;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfStatus_IsParserActive ---
//return :	0 => Parser is disable.
//			1 => Parser is enable.
//			-1=> error.
int intfStatus_IsParserActive(STR_INTF *intf)
{
	if(intf) {
		int status = 0;
		if(0 == intf->status.use)	return -1;
		status = intf->status.active;
		return status;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfStatus_IsDevicePresent ---
//return :	0 => Device no present.
//			1 => Device Present.
//			-1=> error.
int intfStatus_IsDevicePresent(STR_INTF *intf)
{
	if(intf) {
		int status = 0;
		if(0 == intf->status.use)	return -1;
		status = intf->status.present;
		return status;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfSCPI_Clean ---
//return :	0 => no error and Clean all SCPI Status intfister.
//			-1=> error.
int intfSCPI_Clean(STR_INTF *intf)
{
	if(intf) {
		if(0 == intf->status.use)	return -1;
		intf->sre.data = 0;
		intf->stb.data = 0;
		intf->ese.data = 0;
		intf->esr.data = 0;
		return 0;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfSCPI_SetSRE ---
// value :
// 	_intf_SRE_BIT0		//Not used.
// 	_intf_SRE_BIT1		//Not used.
// 	_intf_SRE_ERR		//error queue not empty.
// 	_intf_SRE_QUES		//questionable status.
// 	_intf_SRE_MAV		//message available.
// 	_intf_SRE_ESB		//standard event status.
// 	_intf_SRE_MSS		//masrer summary status.
// 	_intf_SRE_OPER		//operation status.
//return :	positive => SRE data.
//			-1=> error.
int intfSCPI_SetSRE(STR_INTF *intf, int value)//SRE (enable)
{
	if(intf) {
		if(0 == intf->status.use)	return -1;
		intf->sre.data = value;
		return value;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfSCPI_GetSRE ---
//return :	positive => SRE data.
//			-1=> error.
int intfSCPI_GetSRE(STR_INTF *intf)//SRE (enable)
{
	if(intf) {
		int status = 0;
		if(0 == intf->status.use)	return -1;
		status =  intf->sre.data;
		return status;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfSCPI_SetSTB ---
// value :
// 	_intf_SRE_BIT0		//Not used.
// 	_intf_SRE_BIT1		//Not used.
// 	_intf_SRE_ERR		//error queue not empty.
// 	_intf_SRE_QUES		//questionable status.
// 	_intf_SRE_MAV		//message available.
// 	_intf_SRE_ESB		//standard event status.
// 	_intf_SRE_MSS		//masrer summary status.
// 	_intf_SRE_OPER		//operation status.
//return :	positive => SRE data.
//			-1=> error.
int intfSCPI_SetSTB(STR_INTF *intf, int value)//SRE (status)
{
	if(intf) {
		if(0 == intf->status.use)	return -1;
		intf->stb.data = value;
		return value;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfSCPI_GetSTB ---
//return :	positive => SRE data.
//			-1=> error.
int intfSCPI_GetSTB(STR_INTF *intf)//SRE (status)
{
	if(intf) {
		int status = 0;
		if(0 == intf->status.use)	return -1;
		status = intf->stb.data;
		return status;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfSCPI_SetESE ---
// value :
//	_intf_ESE_OPC	//opertion complete.
//	_intf_ESE_RQC	//request control.
//	_intf_ESE_QUE	//query error.
//	_intf_ESE_DDE	//device dependent error.
//	_intf_ESE_EXE	//execution error.
//	_intf_ESE_CME	//command error.
//	_intf_ESE_URQ	//user request.
//	_intf_ESE_PON	//power on.
//return :	positive => ESE data.
//			-1=> error.
int intfSCPI_SetESE(STR_INTF *intf, int value)//SRE bit5--> ESB (Enable)
{
	if(intf) {
		if(0 == intf->status.use)	return -1;
		intf->ese.data = value;
		return value;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfSCPI_GetESE ---
//return :	positive => ESE data.
//			-1=> error.
int intfSCPI_GetESE(STR_INTF *intf)//SRE bit5--> ESB (Enable)
{
	if(intf) {
		int status = 0;
		if(0 == intf->status.use)	return -1;
		status =  intf->ese.data;
		return status;
	}
	else return -1;
}

//-----------------------------------------------
//--- scpi_SetESR ---
// value :
//	_intf_ESE_OPC	//opertion complete.
//	_intf_ESE_RQC	//request control.
//	_intf_ESE_QUE	//query error.
//	_intf_ESE_DDE	//device dependent error.
//	_intf_ESE_EXE	//execution error.
//	_intf_ESE_CME	//command error.
//	_intf_ESE_URQ	//user request.
//	_intf_ESE_PON	//power on.
//return :	positive => ESE data.
//			-1=> error.
int intfSCPI_SetESR(STR_INTF *intf, int value)//SRE bit5--> ESB (Event)
{
	if(intf) {
		if(0 == intf->status.use)	return -1;
		intf->esr.data = value;
		return value;
	}
	else return -1;
}

//-----------------------------------------------
//--- scpi_GetESR ---
//return :	positive => ESE data.
//			-1=> error.
int intfSCPI_GetESR(STR_INTF *intf) //SRE bit5--> ESB (Event)
{
	if(intf) {
		int status = 0;
		if(0 == intf->status.use)	return -1;
		status = intf->esr.data;
		return status;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfSCPI_SetQuesReg ---
// Questionable Status Register (Enable, Event, NTR, PTR, Condition)
// reg :
//	_INTF_REG_ENAB
//	_INTF_REG_EVEN
//	_INTF_REG_NTR
//	_INTF_REG_PTR
//	_INTF_REG_COND
// value :
//	_INTF_QUES_OV		//bit0.Over-Voltage.
//	_INTF_QUES_OC		//bit1.Over-Current.
//	_INTF_QUES_BIT2		//bit2.Not Used.
//	_INTF_QUES_POW		//bit3.AC POWER-OFF.
//	_INTF_QUES_OT		//bit4.Over-Temperature.
//	_INTF_QUES_OP		//bit5.Over-Power.
//	_INTF_QUES_VL		//bit6.Voltage-Limit.
//	_INTF_QUES_IL		//bit7.Current-Limit.
//	_INTF_QUES_CLF		//bit8.Calibration Lead Fault.
//	_INTF_QUES_INH		//bit9.remote inhibit is active.
//	_INTF_QUES_BIT10	//bit10.Not Used.
//	_INTF_QUES_SD		//bit11.Shutdown Alarm.
//	_INTF_QUES_PL		//bit12.Power Limit.
//	_INTF_QUES_BIT13	//bit13.Not Used.
//	_INTF_QUES_BIT14	//bit14.Not Used.
//	_INTF_QUES_BIT15	//bit15.Not Used.
//return :	positive => data of Questionable Status Register (Enable, Event, NTR, PTR, Condition).
//			-1=> error.
int intfSCPI_SetQuesReg(STR_INTF *intf, int reg, int value)//SRE bit3--> QUES 
{
	if(intf) {
		if(0 == intf->status.use)	return -1;
		switch(reg) {
		case _INTF_REG_ENAB:	intf->ques.enab.data = value; break;
		case _INTF_REG_EVEN:	intf->ques.even.data = value; break;
		case _INTF_REG_NTR:		intf->ques.ntr.data  = value; break;
		case _INTF_REG_PTR:		intf->ques.ptr.data  = value; break;
		case _INTF_REG_COND:
			intf->ques.even.data |= ((~(intf->ques.cond.data)) & value & intf->ques.ptr.data);
			intf->ques.even.data |= (intf->ques.cond.data & (~value) & intf->ques.ntr.data);
			intf->ques.cond.data = value;
			break;
		default:	return -1;
		}
		return value;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfSCPI_GetQuesReg ---
// reg :
//	_INTF_REG_ENAB
//	_INTF_REG_EVEN
//	_INTF_REG_NTR
//	_INTF_REG_PTR
//	_INTF_REG_COND
//return :	positive => data of Questionable Status Register (Enable, Event, NTR, PTR, Condition).
//			-1=> error.
int intfSCPI_GetQuesReg(STR_INTF *intf, int reg)//SRE bit3--> QUES 
{
	if(intf) {
		int status = 0;
		if(0 == intf->status.use)	return -1;
		switch(reg) {
		case _INTF_REG_ENAB:	status = intf->ques.enab.data; break;
		case _INTF_REG_EVEN:	status = intf->ques.even.data; break;
		case _INTF_REG_NTR:		status = intf->ques.ntr.data;  break;
		case _INTF_REG_PTR:		status = intf->ques.ptr.data;  break;
		case _INTF_REG_COND:	status = intf->ques.cond.data; break;
		default:	return -1;
		}
		return status;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfSCPI_SetOperReg ---
// Operation Status Register (Enable, Event, NTR, PTR, Condition).
// reg :
//	_INTF_REG_ENAB
//	_INTF_REG_EVEN
//	_INTF_REG_NTR
//	_INTF_REG_PTR
//	_INTF_REG_COND
// value :
//	_INTF_OPER_CAL		//bit0.Calibration Mode.
//	_INTF_OPER_BIT1		//bit1.Not Used.
//	_INTF_OPER_BIT2		//bit2.Not Used.
//	_INTF_OPER_BIT3		//bit3.Not Used.
//	_INTF_OPER_BIT4		//bit4.Not Used.
//	_INTF_OPER_WTG		//bit5.Waiting for Trigger.
//	_INTF_OPER_WA		//bit6.Waiting for ARM.
//	_INTF_OPER_BIT7		//bit7.Not Used.
//	_INTF_OPER_CV		//bit8.Constant Voltage Mode.
//	_INTF_OPER_BIT9		//bit9.Not Used.
//	_INTF_OPER_CC		//bit10.Constant Current Mode.
//	_INTF_OPER_OND		//bit11.Output ON Delay.
//	_INTF_OPER_OFD		//bit12.Output OFF Delay.
//	_INTF_OPER_BIT13	//bit13.Not Used.
//	_INTF_OPER_PR		//bit14.Program Running.
//	_INTF_OPER_BIT15	//bit15.Not Used.
//return :	positive => data of Operation Status Register (Enable, Event, NTR, PTR, Condition).
//			-1=> error.
int intfSCPI_SetOperReg(STR_INTF *intf, int reg, int value)//SRE bit7--> OPER 
{
	if(intf) {
		if(0 == intf->status.use)	return -1;
		switch(reg) {
		case _INTF_REG_ENAB:	intf->oper.enab.data = value; break;
		case _INTF_REG_EVEN:	intf->oper.even.data = value; break;
		case _INTF_REG_NTR:		intf->oper.ntr.data  = value; break;
		case _INTF_REG_PTR:		intf->oper.ptr.data  = value; break;
		case _INTF_REG_COND:
			intf->oper.even.data |= ((~(intf->oper.cond.data)) & value & intf->oper.ptr.data);
			intf->oper.even.data |= (intf->oper.cond.data & (~value) & intf->oper.ntr.data);
			intf->oper.cond.data = value;
		default:	return -1;
		}
		return value;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfSCPI_GetOperReg ---
// reg :
//	_INTF_REG_ENAB
//	_INTF_REG_EVEN
//	_INTF_REG_NTR
//	_INTF_REG_PTR
//	_INTF_REG_COND
//return :	positive => data of Operation Status Register (Enable, Event, NTR, PTR, Condition).
//			-1=> error.
int intfSCPI_GetOperReg(STR_INTF *intf, int reg) //SRE bit7--> OPER
{
	if(intf) {
		int status = 0;
		if(0 == intf->status.use)	return -1;
		switch(reg) {
		case _INTF_REG_ENAB:	status = intf->oper.enab.data; break;
		case _INTF_REG_EVEN:	status = intf->oper.even.data; break;
		case _INTF_REG_NTR:		status = intf->oper.ntr.data;  break;
		case _INTF_REG_PTR:		status = intf->oper.ptr.data;  break;
		case _INTF_REG_COND:	status = intf->oper.cond.data; break;
		default:	return -1;
		}
		return status;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfSCPI_SetOperReg ---
// Operation Status Register (Enable, Event, NTR, PTR, Condition).
// reg :
//	_INTF_REG_ENAB
//	_INTF_REG_EVEN
//	_INTF_REG_NTR
//	_INTF_REG_PTR
//	_INTF_REG_COND
// value :
//	_INTF_CSUM_CC		//bit0
//	_INTF_CSUM_CR		//bit1
//	_INTF_CSUM_CV		//bit2
//	_INTF_CSUM_CP		//bit3
//	_INTF_CSUM_BIT4		//bit4
//	_INTF_CSUM_BIT5		//bit5
//	_INTF_CSUM_BIT6		//bit6
//	_INTF_CSUM_BIT7		//bit7
//	_INTF_CSUM_PRUN		//bit8
//	_INTF_CSUM_BIT9		//bit9
//	_INTF_CSUM_BIT10	//bit10
//	_INTF_CSUM_BIT11	//bit11
//	_INTF_CSUM_BIT12	//bit12
//	_INTF_CSUM_BIT13	//bit13
//	_INTF_CSUM_BIT14	//bit14
//	_INTF_CSUM_BIT15	//bit15
//return :	positive => data of Operation Status Register (Enable, Event, NTR, PTR, Condition).
//			-1=> error.
int intfSCPI_SetCsumReg(STR_INTF *intf, int reg, int value)//SRE bit2--> CSUM
{
	if(intf) {
		if(0 == intf->status.use)	return -1;
		switch(reg) {
		case _INTF_REG_ENAB:	intf->csum.enab.data = value; break;
		case _INTF_REG_EVEN:	intf->csum.even.data = value; break;
		case _INTF_REG_NTR:		intf->csum.ntr.data  = value; break;
		case _INTF_REG_PTR:		intf->csum.ptr.data  = value; break;
		case _INTF_REG_COND:
			intf->csum.even.data |= ((~(intf->csum.cond.data)) & value & intf->csum.ptr.data);
			intf->csum.even.data |= (intf->csum.cond.data & (~value) & intf->csum.ntr.data);
			intf->csum.cond.data = value;
		default:	return -1;
		}
		return value;
	}
	else return -1;
}

//-----------------------------------------------
//--- intfSCPI_GetOperReg ---
// reg :
//	_INTF_REG_ENAB
//	_INTF_REG_EVEN
//	_INTF_REG_NTR
//	_INTF_REG_PTR
//	_INTF_REG_COND
//return :	positive => data of Operation Status Register (Enable, Event, NTR, PTR, Condition).
//			-1=> error.
int intfSCPI_GetCsumReg(STR_INTF *intf, int reg)//SRE bit2--> CSUM
{
	if(intf) {
		int status = 0;
		if(0 == intf->status.use)	return -1;
		switch(reg) {
		case _INTF_REG_ENAB:	status = intf->csum.enab.data; break;
		case _INTF_REG_EVEN:	status = intf->csum.even.data; break;
		case _INTF_REG_NTR:		status = intf->csum.ntr.data;  break;
		case _INTF_REG_PTR:		status = intf->csum.ptr.data;  break;
		case _INTF_REG_COND:	status = intf->csum.cond.data; break;
		default:	return -1;
		}
		return status;
	}
	else return -1;
}



