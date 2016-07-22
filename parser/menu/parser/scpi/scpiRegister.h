/******************************************************************************
 * Filename:	scpiRegister.h
 ******************************************************************************/
#ifndef __SCPI_REGISTER_H__
#define __SCPI_REGISTER_H__

//==========================================================
//  include
//==========================================================
//#include <pthread.h>
//#include <semaphore.h>
//#include <termios.h>

//==========================================================
//  define
//==========================================================
#define _INTF_MASK_RQS	0xBF //MASK bit of RQS.


//--- SCPI Status Register ---//
#define _INTF_REG_ENAB	0 //Enable Register.
#define _INTF_REG_EVEN	1 //Event Register.
#define _INTF_REG_NTR	2 //NTR Register.
#define _INTF_REG_PTR	3 //PTR Register.
#define _INTF_REG_COND	4 //Condition Register.

//--- Questionable Status Register(QUSE) ---//
#define _INTF_QUES_OV		(1<<0)	//bit0.Over-Voltage.
#define _INTF_QUES_OC		(1<<1)	//bit1.Over-Current.
#define _INTF_QUES_BIT2		(1<<2)	//bit2.Not Used.
#define _INTF_QUES_POW		(1<<3)	//bit3.AC POWER-OFF.
#define _INTF_QUES_OT		(1<<4)	//bit4.Over-Temperature.
#define _INTF_QUES_BIT5		(1<<5)	//bit5.Not Used.
#define _INTF_QUES_BIT6		(1<<6)	//bit6.Not Used.
#define _INTF_QUES_BIT7		(1<<7)	//bit7.Not Used.
#define _INTF_QUES_BIT8		(1<<8)	//bit8.Not Used..
#define _INTF_QUES_UVP		(1<<9)	//bit9.Under-Voltage.
#define _INTF_QUES_EXT		(1<<10)	//bit10.EXT.
#define _INTF_QUES_RVP		(1<<11)	//bit11.RVP.
#define _INTF_QUES_BIT12	(1<<12)	//bit12.Not Used.
#define _INTF_QUES_BIT13	(1<<13)	//bit13.Not Used.
#define _INTF_QUES_BIT14	(1<<14)	//bit14.Not Used.
#define _INTF_QUES_BIT15	(1<<15)	//bit15.Not Used.

//--- Operation Status Register (OPER) ---//
#define _INTF_OPER_CAL		(1<<0)	//bit0.Calibration Mode.
#define _INTF_OPER_BIT1		(1<<1)	//bit1.Not Used.
#define _INTF_OPER_BIT2		(1<<2)	//bit2.Not Used.
#define _INTF_OPER_BIT3		(1<<3)	//bit3.Not Used.
#define _INTF_OPER_BIT4		(1<<4)	//bit4.Not Used.
#define _INTF_OPER_WTG		(1<<5)	//bit5.Waiting for Trigger.
#define _INTF_OPER_BIT6		(1<<6)	//bit6.Not Used
#define _INTF_OPER_BIT7		(1<<7)	//bit7.Not Used.
#define _INTF_OPER_BIT8		(1<<8)	//bit8.Not Used
#define _INTF_OPER_BIT9		(1<<9)	//bit9.Not Used.
#define _INTF_OPER_BIT10	(1<<10)	//bit10.Not Used
#define _INTF_OPER_BIT11	(1<<11)	//bit11.Not Used
#define _INTF_OPER_BIT12	(1<<12)	//bit12.Not Used
#define _INTF_OPER_BIT13	(1<<13)	//bit13.Not Used.
#define _INTF_OPER_BIT14	(1<<14)	//bit14.Not Used
#define _INTF_OPER_BIT15	(1<<15)	//bit15.Not Used.

//--- CSUM ---//
#define _INTF_CSUM_CC		(1<<0)	//bit0.CC
#define _INTF_CSUM_CR		(1<<1)	//bit1.CR
#define _INTF_CSUM_CV		(1<<2)	//bit2.CV
#define _INTF_CSUM_CP		(1<<3)	//bit3.CP
#define _INTF_CSUM_BIT4		(1<<4)	//bit4.Not Used.
#define _INTF_CSUM_BIT5		(1<<5)	//bit5.Not Used.
#define _INTF_CSUM_BIT6		(1<<6)	//bit6.Not Used
#define _INTF_CSUM_BIT7		(1<<7)	//bit7.Not Used.
#define _INTF_CSUM_PRUN		(1<<8)	//bit8.PRUN
#define _INTF_CSUM_BIT9		(1<<9)	//bit9.Not Used.
#define _INTF_CSUM_BIT10	(1<<10)	//bit10.Not Used
#define _INTF_CSUM_BIT11	(1<<11)	//bit11.Not Used
#define _INTF_CSUM_BIT12	(1<<12)	//bit12.Not Used
#define _INTF_CSUM_BIT13	(1<<13)	//bit13.Not Used.
#define _INTF_CSUM_BIT14	(1<<14)	//bit14.Not Used
#define _INTF_CSUM_BIT15	(1<<15)	//bit15.Not Used.


//--- Standard Event Status Register (ESB) ---//
#define _INTF_ESB_OPC		(1<<0)	//bit0.
#define _INTF_ESB_RQC		(1<<1)	//bit1.
#define _INTF_ESB_QUE		(1<<2)	//bit2.
#define _INTF_ESB_DDE		(1<<3)	//bit3.
#define _INTF_ESB_EXE		(1<<4)	//bit4.
#define _INTF_ESB_CME		(1<<5)	//bit5.
#define _INTF_ESB_URQ		(1<<6)	//bit6.
#define _INTF_ESB_PON		(1<<7)	//bit7.


//==========================================================
//  typedef & struct
//==========================================================
typedef union _REGISTER_STATUS_BYTE {
    unsigned short data;
    struct {
        unsigned short bit0		:1; //bit0. Not used.
        unsigned short err		:1; //bit1. error queue not empty.
        unsigned short csum		:1; //bit2. csum.
        unsigned short ques		:1; //bit3. questionable status.
        unsigned short mav		:1; //bit4. message available.
        unsigned short esb		:1; //bit5. standard event status.
        unsigned short mss		:1; //bit6. masrer summary status.
        unsigned short oper		:1; //bit7. operation status.
        unsigned short bit8		:1; //bit8.
        unsigned short bit9		:1; //bit9.
        unsigned short bit10	:1; //bit10.
        unsigned short bit11	:1; //bit11.
        unsigned short bit12	:1; //bit12.
        unsigned short bit13	:1; //bit13.
        unsigned short bit14	:1; //bit14.
        unsigned short bit15	:1; //bit15.
    };
} REG_STB, REG_SRE;

typedef union _REGISTER_STANDARD_EVENT_STATUS { //ESB
    unsigned short data;
    struct {
        unsigned short opc   :1; //bit0. opertion complete.
        unsigned short rqc   :1; //bit1. request control.
        unsigned short que   :1; //bit2. query error.
        unsigned short dde   :1; //bit3. device dependent error.
        unsigned short exe   :1; //bit4. execution error.
        unsigned short cme   :1; //bit5. command error.
        unsigned short urq   :1; //bit6. user request.
        unsigned short pon   :1; //bit7. power on.
        unsigned short bit8  :1; //bit8.
        unsigned short bit9  :1; //bit9.
        unsigned short bit10 :1; //bit10.
        unsigned short bit11 :1; //bit11.
        unsigned short bit12 :1; //bit12.
        unsigned short bit13 :1; //bit13.
        unsigned short bit14 :1; //bit14.
        unsigned short bit15 :1; //bit15.
    };
} REG_ESR, REG_ESE;

typedef union _REGISTER_OPERATION_STATUS { //OPER
    unsigned short data;
    struct {
        unsigned short cal		:1; //bit0. calibration mode.
        unsigned short bit1		:1; //bit1.
        unsigned short bit2		:1; //bit2.
        unsigned short bit3		:1; //bit3.
        unsigned short bit4		:1; //bit4.
        unsigned short wtg		:1; //bit5. waiting for trigger.
        unsigned short bit6		:1; //bit6.
        unsigned short bit7		:1; //bit7.
        unsigned short bit8		:1; //bit8. 
        unsigned short bit9		:1; //bit9.
        unsigned short bit10	:1; //bit10. 
        unsigned short bit11	:1; //bit11. 
        unsigned short bit12	:1; //bit12. 
        unsigned short bit13	:1; //bit13.
        unsigned short bit14	:1; //bit14.
        unsigned short bit15	:1; //bit15.
    };
} REG_OPERATION_STATUS;

typedef union _REGISTER_CSUM_STATUS { //CSUM
    unsigned short data;
    struct {
        unsigned short cc		:1; //bit0. 
        unsigned short cr		:1; //bit1.
        unsigned short cv		:1; //bit2.
        unsigned short cp		:1; //bit3.
        unsigned short bit4		:1; //bit4.
        unsigned short bit5		:1; //bit5. 
        unsigned short bit6		:1; //bit6.
        unsigned short bit7		:1; //bit7.
        unsigned short prun		:1; //bit8. 
        unsigned short bit9		:1; //bit9.
        unsigned short bit10	:1; //bit10. 
        unsigned short bit11	:1; //bit11. 
        unsigned short bit12	:1; //bit12. 
        unsigned short bit13	:1; //bit13.
        unsigned short bit14	:1; //bit14.
        unsigned short bit15	:1; //bit15.
    };
} REG_CSUMMARY_STATUS;


typedef union _REGISTER_QUESTIONABLE_STATUS { //QUSE
    unsigned short data;
    struct {
        unsigned short ov		:1; //bit0. Over-Voltage.
        unsigned short oc		:1; //bit1. Over-Current.
        unsigned short bit2		:1; //bit2.
        unsigned short op		:1; //bit3. Over- Power.
        unsigned short ot		:1; //bit4. Over-Temperature.
        unsigned short bit5		:1; //bit5.
        unsigned short bit6		:1; //bit6.
        unsigned short bit7		:1; //bit7.
        unsigned short bit8		:1; //bit8. 
        unsigned short uvp		:1; //bit9. uvp
        unsigned short ext		:1; //bit10. ext
        unsigned short rvp		:1; //bit11. rvp
        unsigned short bit12	:1; //bit12. 
        unsigned short bit13	:1; //bit13  
        unsigned short bit14	:1; //bit14.
        unsigned short bit15	:1; //bit15.
    };
} REG_QUESTIONABLE_STATUS;

typedef union _STR_INTERFACE_STATUS {
	unsigned int	data;
	struct {
		//--- Interface Thread Status ---//
		unsigned int use		:1; //bit0. 0:no initial status and pthread_mutex_t; 1:Successfully initialized.
		unsigned int data_in	:1; //bit1. 0:no receive data; 1:Receive data.
		unsigned int data_out	:1; //bit2. 0:no transfer data; 1:Transfer data.
		unsigned int active 	:1; //bit3. 0:Parser Disable; 1:Parser Enable.
		unsigned int present	:1; //bit4. 0:Device no Present; 1:Device Present.
		unsigned int tx_empty	:1; //bit5. 0:Tx-buffer is empty; 1:Tx-buffer have data.
		unsigned int bit6		:1; //bit6.
		unsigned int bit7		:1; //bit7.
		unsigned int reserved	:24; //bit8~31.
	};
} INTF_STATUS;

typedef union _STR_INTERFACE_REQUEST {
	unsigned int	data;
	struct {
		unsigned int reset		:1; //bit0.0:No reset or reset end; 1: Reset the parser is required.
		unsigned int enable 	:1; //bit1.0:No enable the parser or enable end; 1:Enable the parser is required.
		unsigned int disable	:1; //bit2.0:No disable the parser or disable end; 1:Disable the parser is required.
		unsigned int clean_rx	:1; //bit3.0:clean the Rx-buffer or clean end; 1:Clean the Rx-buffer is required.
		unsigned int clean_tx	:1; //bit4.0:clean the Tx-buffer or clean end; 1:Clean the Tx-buffer is required.
		unsigned int address	:1; //bit5.Configure the GPIB address or RS485 address.
		unsigned int terminal	:1; //bit6.Configure terminal.
		unsigned int bit7		:1; //bit7.
		unsigned int reserved	:24;//bit8~31.
	};
} INTF_REQUEST;

typedef struct _STR_INTERFACE {
	//---Interface---//
	INTF_STATUS		status;
	//---Request---//
	INTF_REQUEST	request;
	unsigned int	address;
	//struct termios	terminal;
	int terminal;
	int * semRequest, semDone; 
	//---SCPI Status Register---//
	int			rqs;
	REG_SRE		sre; //service request enable.
	REG_STB		stb; //status byte.
	REG_ESE		ese; //event status enable.
	REG_ESR 	esr; //event status.
	
	struct {
		REG_QUESTIONABLE_STATUS	enab; //Enable register.
		REG_QUESTIONABLE_STATUS	even; //Event register.
		REG_QUESTIONABLE_STATUS	ptr;  //Positive TRansition.
		REG_QUESTIONABLE_STATUS	ntr;  //Negative TRansition.
		REG_QUESTIONABLE_STATUS	cond; //Condition register.
	} ques;
	struct {
		REG_OPERATION_STATUS	enab; //Enable register.
		REG_OPERATION_STATUS	even; //Event register.
		REG_OPERATION_STATUS	ptr;  //Positive TRansition.
		REG_OPERATION_STATUS	ntr;  //Negative TRansition.
		REG_OPERATION_STATUS	cond; //Condition register.
	} oper;
	struct {
		REG_CSUMMARY_STATUS		enab; //Enable register.
		REG_CSUMMARY_STATUS		even; //Event register.
		REG_CSUMMARY_STATUS		ptr;  //Positive TRansition.
		REG_CSUMMARY_STATUS		ntr;  //Negative TRansition.
		REG_CSUMMARY_STATUS		cond; //Condition register.
	} csum;

	
}  __attribute__((aligned (4),packed)) STR_INTF;
//==========================================================
//  variable & constant
//==========================================================

//==========================================================
//  Function
//==========================================================
extern int intf_Initial(STR_INTF *intf);
extern int intf_Close(STR_INTF *intf);
//---------------------------------------------------------
extern int intfRequest_SetData(STR_INTF *intf, int cmd, unsigned long arg);
extern int intfRequest_GetData(STR_INTF *intf, int cmd, unsigned long arg);
extern int intfRequest_IsRequest(STR_INTF *intf);
extern int intfRequest_Clean(STR_INTF *intf);
//---------------------------------------------------------
extern int intfStatus_SetStatus(STR_INTF *intf, int data);
extern int intfStatus_CleanStatus(STR_INTF *intf, int data);
extern int intfStatus_GetStatus(STR_INTF *intf);
extern int intfStatus_IsRemote(STR_INTF *intf);
extern int intfStatus_IsReceiveData(STR_INTF *intf);
extern int intfStatus_IsSendData(STR_INTF *intf);
extern int intfStatus_IsParserActive(STR_INTF *intf);
extern int intfStatus_IsDevicePresent(STR_INTF *intf);
//---------------------------------------------------------
extern int intfSCPI_Clean(STR_INTF *intf);
//---------------------------------------------------------
extern int intfSCPI_SetSRE(STR_INTF *intf, int value);
extern int intfSCPI_GetSRE(STR_INTF *intf);
extern int intfSCPI_SetSTB(STR_INTF *intf, int value);
extern int intfSCPI_GetSTB(STR_INTF *intf);
//---------------------------------------------------------
extern int intfSCPI_SetESE(STR_INTF *intf, int value);
extern int intfSCPI_GetESE(STR_INTF *intf);
extern int intfSCPI_SetESR(STR_INTF *intf, int value);
extern int intfSCPI_GetESR(STR_INTF *intf);
//---------------------------------------------------------
extern int intfSCPI_SetQuesReg(STR_INTF *intf, int reg, int value);
extern int intfSCPI_GetQuesReg(STR_INTF *intf, int reg);
extern int intfSCPI_SetOperReg(STR_INTF *intf, int reg, int value);
extern int intfSCPI_GetOperReg(STR_INTF *intf, int reg);
extern int intfSCPI_SetCsumReg(STR_INTF *intf, int reg, int value);
extern int intfSCPI_GetCsumReg(STR_INTF *intf, int reg);

//---------------------------------------------------------
#endif //__SCPI_intfISTER_H__

