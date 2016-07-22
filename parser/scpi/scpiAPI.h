#ifndef __SCPI_API_H__
#define __SCPI_API_H__

//==========================================================
//  include
//==========================================================
#include "scpiStruct.h"

//==========================================================
//  define
//==========================================================

#define _TRY_OPEN_DEVICE_PER_SEC	_3_SEC
#define _UPDATE_STATUS_PER_SEC		_1_SEC

//-----------------------------------------------
//--- Interface Status ---//
#define _INTF_STATUS_MASK		0x000000FF
#define _INTF_STATUS_USE		(1<<0) //bit0. 0:no initial status and pthread_mutex_t; 1:Successfully initialized.
#define _INTF_STATUS_DATA_IN	(1<<1) //bit1. 0:no receive data; 1:Receive data.
#define _INTF_STATUS_DATA_OUT	(1<<2) //bit2. 0:no transfer data; 1:Transfer data.
#define _INTF_STATUS_ACTIVE 	(1<<3) //bit3. 0:Parser Disable; 1:Parser Enable.
#define _INTF_STATUS_PRESENT	(1<<4) //bit4. 0:Device no Present; 1:Device Present.
#define _INTF_STATUS_TX_EMPTY	(1<<5) //bit5. 0:Tx-buffer is empty; 1:Tx-buffer have data.

//--- Interface Request ---//
#define _INTF_REQUEST_MASK		0x000000FF
#define _INTF_REQUEST_RESET		(1<<0) //bit0.0:No reset or reset end; 1: Reset the parser is required.
#define _INTF_REQUEST_ENABLE 	(1<<1) //bit1.0:No enable the parser or enable end; 1:Enable the parser is required.
#define _INTF_REQUEST_DISABLE	(1<<2) //bit2.0:No disable the parser or disable end; 1:Disable the parser is required.
#define _INTF_REQUEST_CLEAN_RX	(1<<3) //bit3.0:clean the Rx-buffer or clean end; 1:Clean the Rx-buffer is required.
#define _INTF_REQUEST_CLEAN_TX	(1<<4) //bit4.0:clean the Tx-buffer or clean end; 1:Clean the Tx-buffer is required.
#define _INTF_REQUEST_ADDRESS	(1<<5) //bit5.Configure the GPIB address or RS485 address.
#define _INTF_REQUEST_TERMINAL	(1<<6) //bit6.Configure terminal.

//-----------------------------------------------
//--- STatus Byte (STB) ---
#define _REG_STB_BIT0		(1<<0) //Not used.
#define _REG_STB_BIT1		(1<<1) //Not used.
#define _REG_STB_ERR		(1<<2) //error queue not empty.
#define _REG_STB_QUES		(1<<3) //questionable status.
#define _REG_STB_MAV		(1<<4) //message available.
#define _REG_STB_ESB		(1<<5) //standard event status.
#define _REG_STB_MSS		(1<<6) //masrer summary status.
#define _REG_STB_OPER		(1<<7) //operation status.
#define _REG_STB_BIT8		(1<<8) //Not used.
#define _REG_STB_BIT9		(1<<9) //Not used.
#define _REG_STB_BIT10		(1<<10)//Not used.
#define _REG_STB_BIT11		(1<<11)//Not used.
#define _REG_STB_BIT12		(1<<12)//Not used.
#define _REG_STB_BIT13		(1<<13)//Not used.
#define _REG_STB_BIT14		(1<<14)//Not used.
#define _REG_STB_BIT15		(1<<15)//Not used.

//-----------------------------------------------
//--- Service Request Enable (SRE) ---
#define _REG_SRE_BIT0		(1<<0) //Not used.
#define _REG_SRE_BIT1		(1<<1) //Not used.
#define _REG_SRE_ERR		(1<<2) //error queue not empty.
#define _REG_SRE_QUES		(1<<3) //questionable status.
#define _REG_SRE_MAV		(1<<4) //message available.
#define _REG_SRE_ESB		(1<<5) //standard event status.
#define _REG_SRE_MSS		(1<<6) //masrer summary status.
#define _REG_SRE_OPER		(1<<7) //operation status.
#define _REG_SRE_BIT8		(1<<8)
#define _REG_SRE_BIT9		(1<<9)
#define _REG_SRE_BIT10		(1<<10)
#define _REG_SRE_BIT11		(1<<11)
#define _REG_SRE_BIT12		(1<<12)
#define _REG_SRE_BIT13		(1<<13)
#define _REG_SRE_BIT14		(1<<14)
#define _REG_SRE_BIT15		(1<<15)

//-----------------------------------------------
//--- standard Event Status Register (ESR) ---
#define _REG_ESR_OPC		(1<<0) //opertion complete.
#define _REG_ESR_RQC		(1<<1) //request control.
#define _REG_ESR_QUE		(1<<2) //query error.
#define _REG_ESR_DDE		(1<<3) //device dependent error.
#define _REG_ESR_EXE		(1<<4) //execution error.
#define _REG_ESR_CME		(1<<5) //command error.
#define _REG_ESR_URQ		(1<<6) //user request.
#define _REG_ESR_PON		(1<<7) //power on.
#define _REG_ESR_BIT8		(1<<8)
#define _REG_ESR_BIT9		(1<<9)
#define _REG_ESR_BIT10		(1<<10)
#define _REG_ESR_BIT11		(1<<11)
#define _REG_ESR_BIT12		(1<<12)
#define _REG_ESR_BIT13		(1<<13)
#define _REG_ESR_BIT14		(1<<14)
#define _REG_ESR_BIT15		(1<<15)

//-----------------------------------------------
//--- standard Event Status Enable register (ESE) ---
#define _REG_ESE_OPC		(1<<0) //opertion complete.
#define _REG_ESE_RQC		(1<<1) //request control.
#define _REG_ESE_QUE		(1<<2) //query error.
#define _REG_ESE_DDE		(1<<3) //device dependent error.
#define _REG_ESE_EXE		(1<<4) //execution error.
#define _REG_ESE_CME		(1<<5) //command error.
#define _REG_ESE_URQ		(1<<6) //user request.
#define _REG_ESE_PON		(1<<7) //power on.
#define _REG_ESE_BIT8		(1<<8)
#define _REG_ESE_BIT9		(1<<9)
#define _REG_ESE_BIT10		(1<<10)
#define _REG_ESE_BIT11		(1<<11)
#define _REG_ESE_BIT12		(1<<12)
#define _REG_ESE_BIT13		(1<<13)
#define _REG_ESE_BIT14		(1<<14)
#define _REG_ESE_BIT15		(1<<15)

//==========================================================
//  typedef & struct
//==========================================================
#pragma pad(4)

typedef union _GW_TYPE{
	char	sc[8];
	short	ss[4];
	int 	si;
	long	sl;
	float	f;
	unsigned char	uc[8];
	unsigned short	us[4];
	unsigned int	ui;
	unsigned long	ul;
	double			d;
	char	*psc;
	short	*pss;
	int 	*psi;
	long	*psl;
	float	*pf;
	unsigned char	*puc;
	unsigned short	*pus;
	unsigned int	*pui;
	unsigned long	*pul;
	double			*pd;
	void			*pt; //point.
} __attribute__((aligned (4),packed)) GW_TYPE;
#pragma pad()

#if 1
/* IRange */
#define	SCPI_IRange_H			1
#define	SCPI_IRange_M			1
#define	SCPI_IRange_L			0

/* VRange */
#define	SCPI_VRange_L			0
#define SCPI_VRange_H			1
#define	SCPI_VRange_AddCV_Min	2		//ref		ScpiUnit.c		ModeVRANGe[]
#define	SCPI_VRange_AddCV_Max	3		//ref		ScpiUnit.c		ModeVRANGe[]
#define	SCPI_VRange_OFF			4

/* RESPonse for +CV Mode only */
#define SCPI_RESPonse_FAST		1
#define	SCPI_RESPonse_SLOW		0

/* RESPonse for +CV Mode only */
#define SCPI_RESPonse_CVCP_FAST		2
#define	SCPI_RESPonse_CVCP_NORMAL	1
#define	SCPI_RESPonse_CVCP_SLOW		0


/* Static / Dynamic */
#define SCPI_Static_Status		0
#define	SCPI_Dynamic_Status 	1

/* A / B Value*/
#define SCPI_AValue				0
#define SCPI_BValue				1

/* Protection */
#define	SCPI_NO_Status			0x00
#define SCPI_OCP				0x01
#define SCPI_OVP				0x02
#define SCPI_OPP				0x04
#define	SCPI_RVP				0x08
#define SCPI_OTP				0x10
#define	SCPI_GO_NG				0x20
#define	SCPI_UVP				0x40

/* Show Command */
#define SCPI_Show_LVI			0
#define SCPI_Show_LVW			1
#define	SCPI_Show_LIW			2
#define	SCPI_Show_RVI			3
#define	SCPI_Show_RVW			4
#define	SCPI_Show_RIW			5
#define SCPI_Show_LRV			6
#define	SCPI_Show_LRI			7
#define	SCPI_Show_LRW			8
#define	SCPI_Show_LRS			9
#define	SCPI_Show_LIRV			10
#define	SCPI_Show_LVRI			11
#define	SCPI_Show_VI			12
#define	SCPI_Show_VW			13
#define	SCPI_Show_IW			14
#define	SCPI_Show_S				15

/* CX, CXCV Mode For Normal, Fast Sequence and KiKuSui*/
#define SCPI_CC					0
#define SCPI_CR					1
#define SCPI_CV					2
#define SCPI_CP					3
#define SCPI_CCCV				4
#define SCPI_CRCV				5
#define SCPI_CPCV				6

/*
Nov 17~18 new create by Zon-Yo¡@¡@¡Ð¡Ð¡Ð¡õ¡õ¡õ
These indices of each parameter of four modes (CC, CR, CV, CP mode)
Plese refrence " strWord FourKindsofTypeMode[] " in ScpiUnit.c file
*/
#define SCPI_VA					4	//Value A at static mode
#define SCPI_VB					5	//Value B at static mode
#define SCPI_SRATe				6	//Slewrate at static mode 
#define SCPI_L1					7	//Level 1 at dynamic mode
#define SCPI_L2					8	//Level 2 at dynamice mode
#define SCPI_SET				9	//4 The SET and its Level was appeared when will
#define SCPI_Level				10  //4 exchange //Dynamic Level(value/percent)
									//4 in Go-NoGo of Configureation menu
#define SCPI_RISE				11	//RISE time of slew rate at dynamic mode
#define SCPI_FALL				12	//FALL time of slew rate at dynamic mode
#define SCPI_T1					13	//Timer1 at dynamic mode
#define SCPI_T2					14	//Timer2 at dynamic mode
#define SCPI_FREQ				15	//4 The FREQ and DUTY was appeared when will
#define SCPI_DUTY				16  //4 exchange Dynamic Time(Freq/Duty, T1/T2)
									//4 in Go-NoGo of Configureation menu
								
// Range or Level. ie:H, M, L, MAX, MIN
#define SCPI_MIN						0
#define SCPI_MAX						1
//Nov 17~18 new create by Zon-Yo¡@¡@¡Ð¡Ð¡Ð¡ô¡ô¡ô

// Protection Options in Configure Menu
#if 0
#define SCPI_MIN						0
#define SCPI_MAX						1
#endif 
#define SCPI_LoadOFF			2		//LoadOFF, OFF their index are 2 for ConfigProtection[] in ScpiUnit.c file
#define SCPI_LIMIT				3
#define SCPI_CLEAR				4

// Other Options in Configure Menu
#define SCPI_Config_Other_MIN						0
#define SCPI_Config_Other_OFF						0
#define SCPI_Config_Other_MAX						1
#define SCPI_Config_Other_ON						1
#define SCPI_Config_Other_Response_SLOW				2
#define SCPI_Config_Other_Latch_OFF					2
#define SCPI_Config_Other_Response_FAST				3
#define SCPI_Config_Other_Latch_ON					3

#define SCPI_Config_Other_CRUnit_OHM				0
#define SCPI_Config_Other_CRUnit_MHO				1

#define SCPI_Config_Other_Dyna_Value				0
#define SCPI_Config_Other_Dyna_Percent				1

#define SCPI_Config_Other_Dyna_Time					0
#define SCPI_Config_Other_Dyna_Freq_Duty			1

#define SCPI_Config_Other_Mem_Safety				0
#define SCPI_Config_Other_Mem_Direct				1
#define SCPI_Config_Other_Short_Toggle				12
#define SCPI_Config_Other_Short_Hold				13

/* Go-NoGo Options in Configure Menu,please you maight	
     ref "struct strWord ConfigGoNoGo[]" in ScpiUnit.c file	*/
#define SCPI_Config_GoNoGo_NULL				0
#define SCPI_Config_GoNoGo_GO				1
#define SCPI_Config_GoNoGo_NOGO				2
#define SCPI_Config_GoNoGo_MIN				0
#define SCPI_Config_GoNoGo_MAX				1
#define SCPI_Config_GoNoGo_OFF				0
#define SCPI_Config_GoNoGo_ON				1
#define SCPI_Config_GoNoGo_Value			0
#define SCPI_Config_GoNoGo_Percent			1
#define SCPI_Config_GoNoGo_Center			0
#define SCPI_Config_GoNoGo_High				1
#define SCPI_Config_GoNoGo_Low				2

/* Parallel is a sub options of Next menu in Configure menu 
     ref "struct strWord ConfigParallel[]" in ScpiUnit.c file*/
#define SCPI_Config_Parallel_Mode_Master	0
#define	SCPI_Config_Parallel_Mode_Slave		1
#define SCPI_Config_Parallel_Number_OFF		2
#define SCPI_Config_Parallel_Number_2		3
#define SCPI_Config_Parallel_Number_3		4
#define SCPI_Config_Parallel_Number_4		5
#define SCPI_Config_Parallel_Number_5		6
#define SCPI_Config_Booster_Number_1		7
#define SCPI_Config_Booster_Number_2		8
#define SCPI_Config_Booster_Number_3		9
#define SCPI_Config_Booster_Number_4		10


/* External is a sub options of Next menu in Configure menu 
     ref "struct strWord ConfigExternal[]" in ScpiUnit.c file*/
#define SCPI_Config_Ext_LoadOFF			0
#define	SCPI_Config_Ext_High			1
#define SCPI_Config_Ext_Low				2
#define SCPI_Config_Ext_CtrlOFF			3
#define	SCPI_Config_Ext_Volt			4
#define SCPI_Config_Ext_Res				5
#define SCPI_Config_Ext_Rinverse		6

/* Load Options in Utility Menu */
#define SCPI_Auto_Load_Off			0
#define SCPI_Auto_Load_On			1
#define SCPI_Auto_Load_On_by_Load	2
#define SCPI_Auto_Load_On_by_Prog	3
#define SCPI_Auto_Load_On_by_NSeq	4
#define SCPI_Auto_Load_On_by_FSeq	5

/* Interface Options in Utility Menu */
#define SCPI_Interface_RS232 		0
#define SCPI_Interface_GPIB 		1
#define SCPI_Interface_USB 			2

/* Baud Rate Options of Interface by RS232*/
#define SCPI_UART_BAUD_1200			-1			
#define SCPI_UART_BAUD_2400			0
#define SCPI_UART_BAUD_4800			1			
#define SCPI_UART_BAUD_9600			2			
#define SCPI_UART_BAUD_19200		3			
#define SCPI_UART_BAUD_38400		4			
#define SCPI_UART_BAUD_115200		5

/* Stop Bit Options of Interface by RS232*/
#define SCPI_Stop_Bit_1				0
#define SCPI_Stop_Bit_2				1

/* Parity Check Options of Interface by RS232*/
#define SCPI_Interfac_Parity_None	0
#define SCPI_Interfac_Parity_Odd	1
#define SCPI_Interfac_Parity_Even	2

/* Don't Care for  Multiple Parameter */
#define SCPI_Dont_Care				100
#define SCPI_Dont_Care1				1001


/* Other Options in Utility Menu */
#define SCPI_UTI_Other_Knob_Old_or_Hold		0
#define SCPI_UTI_Other_Knob_Updated			1
#define SCPI_UTI_Other_Off					0
#define SCPI_UTI_Other_On					1
#define SCPI_UTI_Other_Language_English		0

/* Load, Program, Normal/Fast Sequence*/
#define SCPI_Load						0
#define SCPI_Program					1
#define SCPI_Normal_Sequence			2
#define SCPI_Fast_Sequence				3
#define SCPI_OCP_Func					4


/* Program Options */
// Program Item Index
#define SCPI_Program_ON_OFF				0
#define SCPI_Program_Start				0
#define SCPI_Program_Step				1
#define SCPI_Program_Memory				2
#define SCPI_Program_Run_Mode			3
#define SCPI_Program_On_Time			4
#define SCPI_Program_Off_Time			5
#define SCPI_Program_Pass_Fail_Time		6
#define SCPI_Program_Short_Time			7
#define SCPI_Program_Timing_Upper		60.0
#define SCPI_Program_Timing_Lower		0.1

// Program Item Status
#define SCPI_Program_Run_Mode_Skip		0
#define SCPI_Program_Run_Mode_Auto		1
#define SCPI_Program_Run_Mode_Manual	2
#define SCPI_Program_Turns_Timing_Off	0
#define SCPI_Program_Step_Lower			1
#define SCPI_Program_Step_Upper			16
#define SCPI_Program_Memory_Lower		1
#define SCPI_Program_Memory_Upper		256
#define SCPI_Turns_Program_Off			17		//Because Max Program Quantity = 16;	0->Turn Off
#define SCPI_Turns_Program_On			18		//Because Max Program Quantity = 16;	1->Turn On
#define SCPI_Program_Chain_P2P_Off		0

/* Normal Sequence Options */
//Normal Sequence Main Menu Item Index
//4 #define SCPI_Dont_Care						100
#define SCPI_NSEQ_Last_Load_Off			0		
#define SCPI_NSEQ_Last_Load_On			1	
#define SCPI_Turns_NSEQ_Off				0		
#define SCPI_Turns_NSEQ_On				1
#define SCPI_NSEQ_Loop_Infinity			0
#define SCPI_NSEQ_Chain_Off				0

//Normal Sequence EDIT Item Index
//4 #define SCPI_Dont_Care						100
#define SCPI_NSEQ_Step_Lower			1
#define SCPI_NSEQ_Step_Upper			1000
#define SCPI_NSEQ_Seq_Lower				1
#define SCPI_NSEQ_Seq_Upper				10
#define SCPI_NSEQ_Time_Hour_mS_Lower	0
#define SCPI_NSEQ_Time_Hour_mS_Upper	999
#define SCPI_NSEQ_Time_Min_Sec_Lower	0
#define SCPI_NSEQ_Time_Min_Sec_Upper	59
#define SCPI_NSEQ_Edit_Item_Off			0
#define SCPI_NSEQ_Edit_Item_On			1

/* Fast Sequence Options */
//Fast Sequence Main Menu Item Index
//4 #define SCPI_Dont_Care						100
#define SCPI_FSEQ_Last_Load_Off			0		
#define SCPI_FSEQ_Last_Load_On			1
#define SCPI_Turns_FSEQ_Off				0		
#define SCPI_Turns_FSEQ_On				1
#define SCPI_FSEQ_Loop_Infinity			0

//Fast Sequence Edit Item Index
//4 #define SCPI_Dont_Care						100
#define SCPI_FSEQ_Edit_Trig_Out_Off		0
#define SCPI_FSEQ_Edit_Trig_Out_On		1

// Fast Sequence FILL Item Index
#define SCPI_FSEQ_FILL_Start_Value		0
#define SCPI_FSEQ_FILL_End_Value		1
#define SCPI_FSEQ_FILL_Start_Step		2
#define SCPI_FSEQ_FILL_End_Step			3
#define SCPI_FSEQ_Step_Lower			1
#define SCPI_FSEQ_Max_Step_Lower		1
#define SCPI_FSEQ_Step_Upper			1000

/* File Options */
#define SCPI_Memory_Quantity_Lower		1
#define SCPI_Memory_Quantity_Upper		256
#define SCPI_Setup_Quantity_Lower		1
#define SCPI_Setup_Quantity_Upper		100
#define SCPI_Preset_Quantity_Lower		0
#define SCPI_Preset_Quantity_Upper		9

/* Normal Sequence Mode */
#define SCPI_NCC				0
#define SCPI_NCR				1
#define SCPI_NCV				2
#define SCPI_NCP				3
#define SCPI_FCC				4
#define SCPI_FCR				5

/*Normal and Fast Sequence IRange, VRange */
#define SCPI_ILVL				0
//#define SCPI_IMVL				1
#define SCPI_IHVL				1
#define SCPI_ILVH				2
//#define SCPI_IMVH				4
#define SCPI_IHVH				3

/* Calibration */
#define SCPI_CC_MODE			0
#define SCPI_CR_MODE 			1
#define SCPI_CV_MODE	 		2
#define SCPI_CP_MODE	 		3
#define SCPI_CxCV_MODE 			4
#define SCPI_F_IMON_MODE 		5
#define SCPI_R_IMON_MODE 		6
#define SCPI_Ext_V_CC_MODE		7
#define SCPI_Ext_R_CC_MODE		8
#define SCPI_MODE_Number 		9


#define Set_Bit_ON				1
#define Set_Bit_OFF				0
#define Set_Clear				0

#define NO_EVENT_OCCURR			0

#endif




//==========================================================
//  variable & constant
//==========================================================

//==========================================================
//  Function
//==========================================================
/*
void idExample(STR_PARSER *p)
{
	GW_TYPE value;
	int suffix[6];
	int num = 0; //Number of parameters.
	int i   = 0;
	int length = 0;

	if(scpi_IsQueryCommand(p)) { //Query Command.

		//--- Get Number Suffix of Command. ---//
		for(i = 0; i < 6 ; i++) {
			suffix[i] = scpi_GetNumericSuffix(p, i);
		}

		//--- Get number of parameters. ---//
		num = scpi_IsThereParameters(p);

		if(0 < num) {
			//--- Get parameters. ---//
			for(i = 0; i < num; i++) {
				if(0 == scpi_GetIntegerParameters( p, i, (int*) &value.si)) {
					printf("ReceiveInteger<%d>\n", value.si);
					//add application code here.
					
				}
				else if(0 == scpi_GetKeywordParameters( p, i, (int*) &value.si)) {
					printf("ReceiveKeyword<%d>\n", value.si);
					//add application code here.
					
				}
				else if(0 <= scpi_GetStringParameters( p, i, (unsigned int*) &value.ui)) {
					printf("ReceiveString<%s>\n", (char*) value.ui);
					//add application code here.
					
				}
				else if(0 == scpi_GetFloatParameters( p, i, (double*) &value.d)) {
					printf("ReceiveFloat<%f>\n", value.d);
					//add application code here.
					
				}
				else if(0 == scpi_GetExpressionParameters( p, i, (char*) &value)) {
					//no support.
				}
				else if(scpi_IsBlockParameters( p, i)) {
					length = scpi_GetBlockParameters( p, i, (unsigned int*) &value.ui);
					printf("ReceiveBlockData <address=0x%x, length=%d>\n", (unsigned int)value.ui, length);
					//add application code here.
					
				}
				else { //anomalism. no type.
					scpi_SetCommandError( p, _ERR_113_Undefined_header);
					//add application code here.
					
				}
			}
		}
		else if(0 == num) {	//No Parameters.
			//add application code here.
			
		}
		else { //anomalism. An error has occurred. The point zero.
			//add application code here.
			
		}
	}
	else { //Set Command.
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
}
*/

//==========================================================
//  API Function
//==========================================================

extern int scpi_InterfaceRequest(STR_INTF *intf, int cmd, unsigned long arg);

//--- Interface API ---
extern int scpi_StatusUpdate(STR_PARSER *p);

//--- Error-Queue API ---
extern int scpi_InitErrorQueue(STR_PARSER *p);
extern char* scpi_GetErrorString(STR_PARSER *p);
extern int scpi_GetErrorQueue(STR_PARSER *p);
extern int scpi_IsEmptyErrorQueue(STR_PARSER *p);

//--- Command API ---
extern int scpi_SetCommandError(STR_PARSER *p, int err); //system:error?
extern int scpi_GetCommandError(STR_PARSER *p); //CommandError
extern int scpi_IsQueryChain(STR_PARSER *p);
extern int scpi_IsQueryCommand(STR_PARSER *p);
extern int scpi_GetNumericSuffix(STR_PARSER *p, int level);

//--- Parameter API ---
extern int scpi_IsThereParameters(STR_PARSER *p);
extern int scpi_IsIntegerParameters(STR_PARSER *p, int number);
extern int scpi_IsKeywordParameters(STR_PARSER *p, int number);
extern int scpi_IsStringParameters(STR_PARSER *p, int number);
extern int scpi_IsFloatParameters(STR_PARSER *p, int number);
extern int scpi_IsExpressionParameters(STR_PARSER *p, int number);
extern int scpi_IsBlockParameters(STR_PARSER *p, int number);
extern int scpi_IsListParameters(STR_PARSER *p, int number);
extern int scpi_IsOptionParameters(STR_PARSER *p, int number);
extern int scpi_GetIntegerParameters(STR_PARSER *p, int number, int *data);
extern int scpi_GetKeywordParameters(STR_PARSER *p, int number, int *data);
extern int scpi_GetStringParameters(STR_PARSER *p, int number, unsigned int *addr);
extern int scpi_GetFloatParameters(STR_PARSER *p, int number, double *data);
extern int scpi_GetFloatIntegerParameters(STR_PARSER *p, int number, double *data);
extern int scpi_GetExpressionParameters(STR_PARSER *p, int number, char *data);
extern int scpi_GetBlockParameters(STR_PARSER *p, int number, unsigned int *addr);

//--- Other API ---
extern int scpi_IsEmptyOutputBuffer(STR_PARSER *p);
extern int scpi_CleanOutputBuffer(STR_PARSER *p);
extern int scpi_Write(STR_PARSER *p, char *data, unsigned int size, unsigned int flag, unsigned int part);

extern int scpi_CheckParameterTable(void);

#endif //__SCPI_API_H__
