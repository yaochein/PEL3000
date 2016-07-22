#ifndef __MENU_COMMAND_H__
#define __MENU_COMMAND_H__

//==========================================================
//  include
//==========================================================

//==========================================================
//  define
//==========================================================

//==========================================================
//  typedef & struct
//==========================================================
typedef struct _STR_COMMAND_FUNCTION {
	unsigned int id;
	void (*api)(STR_PARSER *p);
} __attribute__((packed)) STR_COMM_FUNC;

extern const STR_COMM_FUNC CommandFun[];

//==========================================================
//  External Function
//==========================================================
extern int checkCommFun(void);
#if 0//_FUNC_MEASURE_FETCH
extern void scpiMeasurement(STR_PARSER *p);
#endif //_FUNC_MEASURE_FETCH
extern void getIDN(void);
extern void procSystemInformation(void);

//extern void processCommand(STR_PARSER *p);

#endif //__MENU_COMMAND_H__

#define Set_Bit_ON				1
#define Set_Bit_OFF				0
#define Set_Clear				0

#define NO_EVENT_OCCURR			0



typedef struct
{
	unsigned char OCP:1;
	unsigned char OVP:1;
	unsigned char OPP:1;
	unsigned char RVP:1;
	unsigned char OTP:1;
	unsigned char NOT_USED_5:1;
	unsigned char NOT_USED_6:1;
	unsigned char NOT_USED_7:1;
	unsigned char NOT_USED_8:1;
	unsigned char NOT_USED_9:1;
	unsigned char NOT_USED_10:1;
	unsigned char NOT_USED_11:1;
	unsigned char NOT_USED_12:1;
	unsigned char NOT_USED_13:1;
	unsigned char NOT_USED_14:1;
	unsigned char NOT_USED_15:1;
}Ques_Reg_Define_P2K;

typedef struct
{
	unsigned char OCP:1;
	unsigned char OVP:1;
	unsigned char OPP:1;
	unsigned char RVP:1;
	unsigned char OTP:1;
	unsigned char NOT_USED_5:1;
	unsigned char NOT_USED_6:1;
	unsigned char NOT_USED_7:1;
	unsigned char NOT_USED_8:1;
	unsigned char NOT_USED_9:1;
	unsigned char NOT_USED_10:1;
	unsigned char NOT_USED_11:1;
	unsigned char NOT_USED_12:1;
	unsigned char NOT_USED_13:1;
	unsigned char NOT_USED_14:1;
	unsigned char NOT_USED_15:1;
}Chan_Reg_Define_P2K;

typedef struct
{
	unsigned char CH1:1;
	unsigned char CH2:1;
	unsigned char CH3:1;
	unsigned char CH4:1;
	unsigned char CH5:1;
	unsigned char CH6:1;
	unsigned char CH7:1;
	unsigned char CH8:1;
	unsigned char NOT_USED_8:1;
	unsigned char NOT_USED_9:1;
	unsigned char NOT_USED_10:1;
	unsigned char NOT_USED_11:1;
	unsigned char NOT_USED_12:1;
	unsigned char NOT_USED_13:1;
	unsigned char NOT_USED_14:1;
	unsigned char NOT_USED_15:1;
}CSum_Reg_Define_P2K;

typedef union
{
	unsigned short Data;
	Ques_Reg_Define_P2K Reg;
}Ques_Reg_P2K;

typedef union
{
	unsigned short Data;
	Chan_Reg_Define_P2K Reg;
}Chan_Reg_P2K;

typedef union
{
	unsigned short Data;
	CSum_Reg_Define_P2K Reg;
}Csum_Reg_P2K;

typedef struct
{
	Ques_Reg_P2K Condition;
	Ques_Reg_P2K Cond_Previous;
	Ques_Reg_P2K NTR;
	Ques_Reg_P2K PTR;
	Ques_Reg_P2K Event;
	Ques_Reg_P2K Enable;
}Ques_Status_Reg_P2K;

typedef struct
{	
	Chan_Reg_P2K Condition;
	Chan_Reg_P2K Cond_Previous;
	Chan_Reg_P2K NTR;
	Chan_Reg_P2K PTR;
	Chan_Reg_P2K Event;
	Chan_Reg_P2K Enable;
}Chan_Status_Reg_P2K;

typedef struct
{
	Csum_Reg_P2K Event;
	Csum_Reg_P2K Enable;
}CSum_Status_Reg_P2K;

typedef struct
{
	Ques_Status_Reg_P2K Ques;
	Chan_Status_Reg_P2K Chan;
	CSum_Status_Reg_P2K CSum;
}SCPI_Status_Reg_P2K_Str;
/*-------------------------------------------------------------------------------------------*/
typedef struct
{
	unsigned char OVP:1;
	unsigned char OCP:1;
	unsigned char NOT_USED_2:1;
	unsigned char OPP:1;
	unsigned char OTP:1;
	unsigned char NOT_USED_5:1;
	unsigned char NOT_USED_6:1;
	unsigned char NOT_USED_7:1;
	unsigned char NOT_USED_8:1;
	unsigned char UVP:1;
	unsigned char EXT:1;
	unsigned char RVP:1;
	unsigned char NOT_USED_12:1;
	unsigned char NOT_USED_13:1;
	unsigned char NOT_USED_14:1;
	unsigned char NOT_USED_15:1;
}Ques_Reg_Define;

typedef struct
{
	unsigned char CAL:1;
	unsigned char NOT_USED_1:1;
	unsigned char NOT_USED_2:1;
	unsigned char NOT_USED_3:1;
	unsigned char NOT_USED_4:1;
	unsigned char WTG:1;
	unsigned char NOT_USED_6:1;
	unsigned char NOT_USED_7:1;
	unsigned char NOT_USED_8:1;
	unsigned char NOT_USED_9:1;
	unsigned char NOT_USED_10:1;
	unsigned char NOT_USED_11:1;
	unsigned char NOT_USED_12:1;
	unsigned char NOT_USED_13:1;
	unsigned char NOT_USED_14:1;
	unsigned char NOT_USED_15:1;
}Oper_Reg_Define;

typedef struct
{
	unsigned char CC:1;
	unsigned char CV:1;
	unsigned char CR:1;
	unsigned char CP:1;
	unsigned char NOT_USED_4:1;
	unsigned char NOT_USED_5:1;
	unsigned char NOT_USED_6:1;
	unsigned char NOT_USED_7:1;
	unsigned char PRUN:1;
	unsigned char NOT_USED_9:1;
	unsigned char NOT_USED_10:1;
	unsigned char NOT_USED_11:1;
	unsigned char NOT_USED_12:1;
	unsigned char NOT_USED_13:1;
	unsigned char NOT_USED_14:1;
	unsigned char NOT_USED_15:1;
}CSum_Reg_Define;

typedef union
{
	unsigned short Data;
	Ques_Reg_Define Reg;
}Ques_Reg;

typedef union
{
	unsigned short Data;
	Oper_Reg_Define Reg;
}Oper_Reg;

typedef union
{
	unsigned short Data;
	CSum_Reg_Define Reg;
}CSum_Reg;

typedef struct
{
	Ques_Reg Condition;
	Ques_Reg Cond_Previous;
	Ques_Reg NTR;
	Ques_Reg PTR;
	Ques_Reg Event;
	Ques_Reg Enable;
}Ques_Status_Reg;

typedef struct
{
	Oper_Reg Condition;
	Oper_Reg Cond_Previous;
	Oper_Reg NTR;
	Oper_Reg PTR;
	Oper_Reg Event;
	Oper_Reg Enable;
}Oper_Status_Reg;

typedef struct
{
	CSum_Reg Condition;
	CSum_Reg Cond_Previous;
	CSum_Reg NTR;
	CSum_Reg PTR;
	CSum_Reg Event;
	CSum_Reg Enable;
}CSum_Status_Reg;

typedef struct
{
	Ques_Status_Reg 	Ques;
	Oper_Status_Reg 	Oper;
	CSum_Status_Reg 	CSum;
}SCPI_Status_Reg_Str;
/*-------------------------------------------------------------------------------------------*/
typedef struct
{
	unsigned char OPC:1;
	unsigned char RQC:1;
	unsigned char QUE:1;
	unsigned char DDE:1;
	unsigned char EXE:1;
	unsigned char CME:1;
	unsigned char URQ:1;
	unsigned char PON:1;
}Event_Reg_Define;

typedef union
{
	unsigned char Data;
	Event_Reg_Define Reg;
}ESE_Reg;

typedef union
{
	unsigned char Data;
	Event_Reg_Define Reg;
}ESR_Reg;

typedef struct
{
	ESR_Reg SCPI_ESR;
	ESE_Reg SCPI_ESE;
}SCPI_Standard_Event_Reg_Str;
/*------------------------------------------------------------------------------------------*/
typedef struct
{
	unsigned char NOT_USED:1;
	unsigned char ERR:1;
	unsigned char CSUM:1;
	unsigned char QUES:1;
	unsigned char MAV:1;
	unsigned char ESB:1;
	unsigned char RQS_MSS:1;
	unsigned char OPER:1;
}Status_Byte_Reg_Define;

typedef union
{
	unsigned char Data;
	Status_Byte_Reg_Define Reg;
}STB_Reg;

typedef union
{
	unsigned char Data;
	Status_Byte_Reg_Define Reg;
}SRE_Reg;

typedef struct
{
	STB_Reg SCPI_STB;
	SRE_Reg SCPI_SRE;
}SCPI_Status_Byte_Reg_Str;
/*------------------------------------------------------------------------------------------*/
extern SCPI_Status_Reg_Str 			Status_Reg;
extern SCPI_Status_Byte_Reg_Str 	Status_Byte_Reg;
extern SCPI_Standard_Event_Reg_Str 	Standard_Event_Reg;
extern SCPI_Status_Reg_P2K_Str 		Status_Reg_P2K;


