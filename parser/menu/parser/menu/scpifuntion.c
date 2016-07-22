
//==============================================================================
// @ Include
//==============================================================================
#include "../../includes.h"
#include "../scpi/scpiStruct.h"
#include "../scpi/scpiID.h"
#include "../scpi/scpiError.h"
#include "../scpi/scpiErrQueue.h"
#include "../scpi/tty/devTtyDefine.h"
#include "../scpi/scpiAPI.h"
#include "../scpi/scpiSpecProc.h"

#include "menuComm.h" 
#include <stdio.h>
#include "keydef.h"
#include "math.h"
#include "../../menu/menu.h"





//extern unsigned short New_Set_Count_To_FPGA;
extern STR_PARSER parser_UART;


#define run_flag		0

#define Float_Data 		0
#define Integer_Data	1
#define String_Data		2
#define ULONG			unsigned long
#define UBYTE			unsigned char
extern UBYTE PC_scriptrun;
extern UBYTE usbrun;

void ExportProcess(char Mode,float Float_Value,long integer_Value,char *str_data, char precision)
{
	char scpi_out_buff[60];
	char *Output_data;
	ULONG i;

	if(Float_Value<0)
		Float_Value=0;
	if(integer_Value<0)
		integer_Value=0;
	if(Mode==Float_Data) 	/* Float */
	{
		if(precision==0)
			sprintf( scpi_out_buff, "%1.0f", Float_Value );
		else if(precision==1)
			sprintf( scpi_out_buff, "%1.1f", Float_Value );
		else if(precision==2)
			sprintf( scpi_out_buff, "%1.2f", Float_Value );
		else if(precision==3)
			sprintf( scpi_out_buff, "%1.3f", Float_Value );
		else if(precision==4)
			sprintf( scpi_out_buff, "%1.4f", Float_Value );
		else if(precision==6)
		{
			if(Float_Value>=10000)
				sprintf( scpi_out_buff, "%5.2f", Float_Value);
			else if(Float_Value>=1000)
				sprintf( scpi_out_buff, "%4.3f", Float_Value);
			else if( Float_Value >= 100)
				sprintf( scpi_out_buff, "%3.4f", Float_Value);
			else if(Float_Value>=10)
				sprintf( scpi_out_buff, "%2.5f", Float_Value );
			else
				sprintf( scpi_out_buff, "%1.6f", Float_Value );
		}
		else if(precision==7)
		{
			if(Float_Value>=10000)
				sprintf( scpi_out_buff, "%5.3f", Float_Value);
			else if(Float_Value>=1000)
				sprintf( scpi_out_buff, "%4.4f", Float_Value);
			else if( Float_Value >= 100)
				sprintf( scpi_out_buff, "%3.5f", Float_Value);
			else if(Float_Value>=10)
				sprintf( scpi_out_buff, "%2.6f", Float_Value );
			else
				sprintf( scpi_out_buff, "%1.7f", Float_Value );
		}		
		else
		{			
			if(Float_Value>=10000)
				sprintf( scpi_out_buff, "%5.1f", Float_Value);
			else if(Float_Value>=1000)
				sprintf( scpi_out_buff, "%4.2f", Float_Value);
			else if( Float_Value >= 100)
				sprintf( scpi_out_buff, "%3.3f", Float_Value);
			else if(Float_Value>=10)
				sprintf( scpi_out_buff, "%2.4f", Float_Value );
			else
				sprintf( scpi_out_buff, "%1.5f", Float_Value );
		}
	}
	else if(Mode==Integer_Data) /* Integer */
		sprintf( scpi_out_buff, "%d", integer_Value);

	if(Mode==String_Data)
		Output_data=str_data;
	else
		Output_data=scpi_out_buff;

	if(Output_data==0)
	{
		return;
	}

	//if((!PC_scriptrun)&&(!usbrun))
	//{		
		if(Output_Buffer_Count)
			Output_Buffer[Output_Buffer_Count++]=';';		
		while(1)
		{
			if((Output_Buffer_Count>=8192)||(0==*Output_data))
				break;
			Output_Buffer[Output_Buffer_Count++]=*Output_data++;
		}	
	//}
	//else
	//{
	//	WOutgoBuffer((UBYTE *)Output_data,1);
	//	WOutgoBuffer("\n",1);
	//}
}

long SCPI_InputToStep(double input,double resolution)
{
	long step;
	step = (input*1000000.0+5)/(resolution*1000000.0);
	return step;
}
long SCPI_InputToStep_s(double input,double resolution)
{
	long step;
	step = (input*100000000.0+5)/(resolution*100000000.0);
	return step;
}


SCPI_Status_Reg_Str 		Status_Reg;
SCPI_Status_Byte_Reg_Str 	Status_Byte_Reg;
SCPI_Standard_Event_Reg_Str Standard_Event_Reg;
SCPI_Status_Reg_P2K_Str 	Status_Reg_P2K;

void QuesStatusReporting_P3K(void)
{
#if	run_flag

	Status_Reg_P2K.Ques.Cond_Previous.Data = Status_Reg_P2K.Ques.Condition.Data;
	Status_Reg_P2K.Ques.Condition.Data = 0;
	
	switch(p3k_Measure_Data.Alarm)
	{
		case OCP_Alarm:
			Status_Reg_P2K.Ques.Condition.Reg.OCP = Set_Bit_ON; 
			if(Status_Reg_P2K.Ques.Event.Data == NO_EVENT_OCCURR)
			{
				if(Status_Reg_P2K.Ques.NTR.Reg.OCP == Set_Bit_ON) 
				{
					if(Status_Reg_P2K.Ques.Condition.Reg.OCP < Status_Reg_P2K.Ques.Cond_Previous.Reg.OCP)
						Status_Reg_P2K.Ques.Event.Reg.OCP = Set_Bit_ON;
				}
				if(Status_Reg.Ques.PTR.Reg.OCP == Set_Bit_ON)
				{
					if(Status_Reg_P2K.Ques.Condition.Reg.OCP > Status_Reg_P2K.Ques.Cond_Previous.Reg.OCP)
						Status_Reg_P2K.Ques.Event.Reg.OCP = Set_Bit_ON; 
				}
			}
			break;
		case OVP_Alarm:
			Status_Reg_P2K.Ques.Condition.Reg.OVP = Set_Bit_ON;
			if(Status_Reg_P2K.Ques.Event.Data == NO_EVENT_OCCURR)
			{
				if(Status_Reg_P2K.Ques.NTR.Reg.OVP == Set_Bit_ON) 
				{
					if(Status_Reg_P2K.Ques.Condition.Reg.OVP < Status_Reg_P2K.Ques.Cond_Previous.Reg.OVP)
						Status_Reg_P2K.Ques.Event.Reg.OVP = Set_Bit_ON;
				}
				if(Status_Reg.Ques.PTR.Reg.OVP == Set_Bit_ON) 
				{
					if(Status_Reg_P2K.Ques.Condition.Reg.OVP > Status_Reg_P2K.Ques.Cond_Previous.Reg.OVP)
						Status_Reg_P2K.Ques.Event.Reg.OVP = Set_Bit_ON; 
				}
			}
			break;
		case OPP_Alarm:
			Status_Reg_P2K.Ques.Condition.Reg.OPP = Set_Bit_ON;
			if(Status_Reg_P2K.Ques.Event.Data == NO_EVENT_OCCURR)
			{
				if(Status_Reg_P2K.Ques.NTR.Reg.OPP == Set_Bit_ON) 
				{
					if(Status_Reg_P2K.Ques.Condition.Reg.OPP < Status_Reg_P2K.Ques.Cond_Previous.Reg.OPP)
						Status_Reg_P2K.Ques.Event.Reg.OPP = Set_Bit_ON;
				}
				if(Status_Reg.Ques.PTR.Reg.OPP == Set_Bit_ON)
				{
					if(Status_Reg_P2K.Ques.Condition.Reg.OPP > Status_Reg_P2K.Ques.Cond_Previous.Reg.OPP)
						Status_Reg_P2K.Ques.Event.Reg.OPP = Set_Bit_ON; 
				}
			}
			break;
		case RVP_Alarm:
			Status_Reg_P2K.Ques.Condition.Reg.RVP = Set_Bit_ON;
			if(Status_Reg_P2K.Ques.Event.Data == NO_EVENT_OCCURR)
			{
				if(Status_Reg_P2K.Ques.NTR.Reg.RVP == Set_Bit_ON) 
				{
					if(Status_Reg_P2K.Ques.Condition.Reg.RVP < Status_Reg_P2K.Ques.Cond_Previous.Reg.RVP)
						Status_Reg_P2K.Ques.Event.Reg.RVP = Set_Bit_ON;
				}
				if(Status_Reg_P2K.Ques.PTR.Reg.RVP == Set_Bit_ON)
				{
					if(Status_Reg_P2K.Ques.Condition.Reg.RVP > Status_Reg_P2K.Ques.Cond_Previous.Reg.RVP)
						Status_Reg_P2K.Ques.Event.Reg.RVP = Set_Bit_ON; 
				}		
			}	
			break;			
		case OTP_Alarm:
			Status_Reg_P2K.Ques.Condition.Reg.OTP = Set_Bit_ON;
			if(Status_Reg_P2K.Ques.Event.Data == NO_EVENT_OCCURR)
			{
				if(Status_Reg_P2K.Ques.NTR.Reg.OTP == Set_Bit_ON) 
				{
					if(Status_Reg_P2K.Ques.Condition.Reg.OTP < Status_Reg_P2K.Ques.Cond_Previous.Reg.OTP)
						Status_Reg_P2K.Ques.Event.Reg.OTP = Set_Bit_ON;
				}
				if(Status_Reg_P2K.Ques.PTR.Reg.OTP == Set_Bit_ON)
				{
					if(Status_Reg_P2K.Ques.Condition.Reg.OTP > Status_Reg_P2K.Ques.Cond_Previous.Reg.OTP)
						Status_Reg_P2K.Ques.Event.Reg.OTP = Set_Bit_ON; 
				}
			}
			break;
		default:
			break;			
	}
#endif	
}

void ChanStatusReporting_P3K(void)
{
#if	run_flag
	Status_Reg_P2K.Chan.Cond_Previous.Data = Status_Reg_P2K.Chan.Condition.Data;
	Status_Reg_P2K.Chan.Condition.Data = 0;
	
	switch(p3k_Measure_Data.Alarm)
	{
		case OCP_Alarm:
			Status_Reg_P2K.Chan.Condition.Reg.OCP = Set_Bit_ON; 
			if(Status_Reg_P2K.Chan.Event.Data == NO_EVENT_OCCURR)
			{
				if(Status_Reg_P2K.Chan.NTR.Reg.OCP == Set_Bit_ON) 
				{
					if(Status_Reg_P2K.Chan.Condition.Reg.OCP < Status_Reg_P2K.Chan.Cond_Previous.Reg.OCP)
						Status_Reg_P2K.Chan.Event.Reg.OCP = Set_Bit_ON;
				}
				if(Status_Reg_P2K.Chan.PTR.Reg.OCP == Set_Bit_ON)
				{
					if(Status_Reg_P2K.Chan.Condition.Reg.OCP > Status_Reg_P2K.Chan.Cond_Previous.Reg.OCP)
						Status_Reg_P2K.Chan.Event.Reg.OCP = Set_Bit_ON; 
				}
			}
			break;
		case OVP_Alarm:
			Status_Reg_P2K.Chan.Condition.Reg.OVP = Set_Bit_ON;
			if(Status_Reg_P2K.Chan.Event.Data == NO_EVENT_OCCURR)
			{
				if(Status_Reg_P2K.Chan.NTR.Reg.OVP == Set_Bit_ON) 
				{
					if(Status_Reg_P2K.Chan.Condition.Reg.OVP < Status_Reg_P2K.Chan.Cond_Previous.Reg.OVP)
						Status_Reg_P2K.Chan.Event.Reg.OVP = Set_Bit_ON;
				}
				if(Status_Reg_P2K.Chan.PTR.Reg.OVP == Set_Bit_ON) 
				{
					if(Status_Reg_P2K.Chan.Condition.Reg.OVP > Status_Reg_P2K.Chan.Cond_Previous.Reg.OVP)
						Status_Reg_P2K.Chan.Event.Reg.OVP = Set_Bit_ON; 
				}
			}
			break;
		case OPP_Alarm:
			Status_Reg_P2K.Chan.Condition.Reg.OPP = Set_Bit_ON;
			if(Status_Reg_P2K.Chan.Event.Data == NO_EVENT_OCCURR)
			{
				if(Status_Reg_P2K.Chan.NTR.Reg.OPP == Set_Bit_ON) 
				{
					if(Status_Reg_P2K.Chan.Condition.Reg.OPP < Status_Reg_P2K.Chan.Cond_Previous.Reg.OPP)
						Status_Reg_P2K.Chan.Event.Reg.OPP = Set_Bit_ON;
				}
				if(Status_Reg_P2K.Chan.PTR.Reg.OPP == Set_Bit_ON)
				{
					if(Status_Reg_P2K.Chan.Condition.Reg.OPP > Status_Reg_P2K.Chan.Cond_Previous.Reg.OPP)
						Status_Reg_P2K.Chan.Event.Reg.OPP = Set_Bit_ON; 
				}
			}
			break;
		case RVP_Alarm:
			Status_Reg_P2K.Chan.Condition.Reg.RVP = Set_Bit_ON;
			if(Status_Reg_P2K.Chan.Event.Data == NO_EVENT_OCCURR)
			{
				if(Status_Reg_P2K.Chan.NTR.Reg.RVP == Set_Bit_ON) 
				{
					if(Status_Reg_P2K.Chan.Condition.Reg.RVP < Status_Reg_P2K.Chan.Cond_Previous.Reg.RVP)
						Status_Reg_P2K.Chan.Event.Reg.RVP = Set_Bit_ON;
				}
				if(Status_Reg_P2K.Chan.PTR.Reg.RVP == Set_Bit_ON)
				{
					if(Status_Reg_P2K.Chan.Condition.Reg.RVP > Status_Reg_P2K.Chan.Cond_Previous.Reg.RVP)
						Status_Reg_P2K.Chan.Event.Reg.RVP = Set_Bit_ON; 
				}		
			}	
			break;			
		case OTP_Alarm:
			Status_Reg_P2K.Chan.Condition.Reg.OTP = Set_Bit_ON;
			if(Status_Reg_P2K.Chan.Event.Data == NO_EVENT_OCCURR)
			{
				if(Status_Reg_P2K.Chan.NTR.Reg.OTP == Set_Bit_ON) 
				{
					if(Status_Reg_P2K.Chan.Condition.Reg.OTP < Status_Reg_P2K.Chan.Cond_Previous.Reg.OTP)
						Status_Reg_P2K.Chan.Event.Reg.OTP = Set_Bit_ON;
				}
				if(Status_Reg_P2K.Chan.PTR.Reg.OTP == Set_Bit_ON)
				{
					if(Status_Reg_P2K.Chan.Condition.Reg.OTP > Status_Reg_P2K.Chan.Cond_Previous.Reg.OTP)
						Status_Reg_P2K.Chan.Event.Reg.OTP = Set_Bit_ON; 
				}
			}
			break;
		default:
			break;			
	}
#endif	
}

void CSumStatusReporting_P3K(void)
{
#if	run_flag
	Status_Reg_P2K.CSum.Event.Reg.CH1 == Set_Bit_ON;
#endif

}

void StandardEventStatus(void)
{	
#if	run_flag
	STR_PARSER *p;
	p = &parser_UART;
	if(p) {
		STR_INTF *reg = p->pInterface;
		int err = p->pComd->err;
		//int error_queue = scpi_IsEmptyErrorQueue(p);
		//int output_buffer = scpi_IsEmptyOutputBuffer(p);
//		if(0 == reg->status.use)	return -1;
		//--- Questionable Status ---//

		//--- Operation Status ---//
		
		//--- ESR ---//

		Standard_Event_Reg.SCPI_ESR.Reg.CME= ((_ERR_100_Command_error <= err)&&(_ERR_200_Execution_error > err)) ? 1 : 0;
		Standard_Event_Reg.SCPI_ESR.Reg.EXE= ((_ERR_200_Execution_error <= err)&&(_ERR_300_Device_specific_error > err)) ? 1 : 0;
		Standard_Event_Reg.SCPI_ESR.Reg.DDE= ((_ERR_300_Device_specific_error <= err)&&(_ERR_400_Query_error > err)) ? 1 : 0;
		Standard_Event_Reg.SCPI_ESR.Reg.QUE= ((_ERR_400_Query_error <= err)&&(_ERR_500_Power_on > err)) ? 1 : 0;
		Standard_Event_Reg.SCPI_ESR.Reg.PON= ((_ERR_500_Power_on <= err)&&(_ERR_600_User_request > err)) ? 1 : 0;
		Standard_Event_Reg.SCPI_ESR.Reg.URQ= ((_ERR_600_User_request <= err)&&(_ERR_700_Request_control > err)) ? 1 : 0;
		Standard_Event_Reg.SCPI_ESR.Reg.RQC= ((_ERR_700_Request_control <= err)&&(_ERR_800_Operation_complete> err)) ? 1 : 0;

		
		reg->esr.cme |= ((_ERR_100_Command_error <= err)&&(_ERR_200_Execution_error > err)) ? 1 : 0;
		reg->esr.exe |= ((_ERR_200_Execution_error <= err)&&(_ERR_300_Device_specific_error > err)) ? 1 : 0;
		reg->esr.dde |= ((_ERR_300_Device_specific_error <= err)&&(_ERR_400_Query_error > err)) ? 1 : 0;
		reg->esr.que |= ((_ERR_400_Query_error <= err)&&(_ERR_500_Power_on > err)) ? 1 : 0;
		reg->esr.pon |= ((_ERR_500_Power_on <= err)&&(_ERR_600_User_request > err)) ? 1 : 0;
		reg->esr.urq |= ((_ERR_600_User_request <= err)&&(_ERR_700_Request_control > err)) ? 1 : 0;
		reg->esr.rqc |= ((_ERR_700_Request_control <= err)&&(_ERR_800_Operation_complete> err)) ? 1 : 0;
	
	}	
#endif
}

void StatusByteRegister(void)
{
#if	run_flag
	/* Bit 1 -> ERR Setting */
	if(parser_UART.errQueue.cnt > 0)
	{
		StandardEventStatus();
		Status_Byte_Reg.SCPI_STB.Reg.ERR = Set_Bit_ON;
	}
	else
		Status_Byte_Reg.SCPI_STB.Reg.ERR = Set_Bit_OFF;

/* Bit 2 -> CSUM  Setting */
	Status_Byte_Reg.SCPI_STB.Reg.CSUM = (Status_Reg_P2K.CSum.Event.Data & Status_Reg_P2K.CSum.Enable.Data) ? Set_Bit_ON : Set_Bit_OFF;

/* Bit 3 -> QUES  Setting */
	Status_Byte_Reg.SCPI_STB.Reg.QUES = (Status_Reg_P2K.Ques.Event.Data & Status_Reg_P2K.Ques.Enable.Data) ? Set_Bit_ON : Set_Bit_OFF;

/* Bit 4 -> MAV  Setting */
	if(UTILITY.INTERFACE == INTERFACE_GPIB)
	{
		if(GpibBuf.RingBufTxCtr)
			Status_Byte_Reg.SCPI_STB.Reg.MAV = Set_Bit_ON;
		else
			Status_Byte_Reg.SCPI_STB.Reg.MAV = Set_Bit_OFF;
	}
	
/* Bit 5 -> ESB  Setting */	
	Status_Byte_Reg.SCPI_STB.Reg.ESB = (Standard_Event_Reg.SCPI_ESR.Data & Standard_Event_Reg.SCPI_ESE.Data) ? Set_Bit_ON : Set_Bit_OFF;

/* Bit 6 -> RQS/MSS  Setting */
	if((Status_Byte_Reg.SCPI_STB.Data & 0xBF) & Status_Byte_Reg.SCPI_SRE.Data)
	{
		Status_Byte_Reg.SCPI_STB.Reg.RQS_MSS = Set_Bit_ON;
		if(UTILITY.INTERFACE == INTERFACE_GPIB)
		{
			clear_status_byte_bits(~(Status_Byte_Reg.SCPI_STB.Data));
			set_status_byte_bits(Status_Byte_Reg.SCPI_STB.Data);
			//Status_Byte_Reg.SCPI_STB.Reg.RQS_MSS = Set_Bit_OFF;
		}
	}
	else
		Status_Byte_Reg.SCPI_STB.Reg.RQS_MSS = Set_Bit_OFF;
	
/* Bit 7 -> OPER  Setting */
	Status_Byte_Reg.SCPI_STB.Reg.OPER = Set_Bit_OFF;
#endif

}


void Status_Reporting(void)
{	
#if run_flag
		/* for new parser */
	//updateScpiStatus();

	/* Questionable Status Condition & Event Register Setting */
	QuesStatusReporting_P3K();

	/* Channel Status Condition & Event Register Setting */
	ChanStatusReporting_P3K();

	/* CSummary Status Condition & Event Register Setting */
	CSumStatusReporting_P3K();

	/* Standard Byte Register Setting */
	StatusByteRegister();
#endif	
}


