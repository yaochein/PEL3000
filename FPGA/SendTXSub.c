#if 1
/*

protection -----------------------------------
			s/h
	ocp		h
	opp		h
	ovp		s
	uvp		s
	
measure -----------------------------------
	// will add time perior option
	volt			average
	curr			average
	catchVolt		one
	catchCurr		one
	// 4096 point measure

extern control -----------------------------------

parallel -----------------------------------

load -----------------------------------
			static	dynatic	mode	setfpga
	LOAD	o		fpga		all		load
	BATT	o				cc cr cp	load-static
	
	OCP		x		dsp		cc		load-static
	OPP		x		dsp		cp		load-static
	
	FLED	o		x		fled		(vf, rd)				
	CLED	o		x		cled		(vi[12288]

	PROG	x		fpga 	all		(1000 step)
	NSEQ	x		fpga 	all		(1000 step)
	FSEQ	x		fpga 	cc,cr		(1000 step)

	cc: const current, cr: const resitant, cv: const volt, cp: const power
	fled: volt<vf=>I=0, I=(v-vf)/Rd
	cled: build iv curve table [12288], by measure volt, set da count.

calibration ----------------------------------------------------
			AD		DA		PROTECTION
	cc		current	cc		ocp
	cr		x		cr		x
	cv		voltange	cv		x
	cp		x		cp		opp
	cx+cv	x		cxcv
	f-i-mon	x		o
	r-i-mon	x		o
	ext v	extV		
	ext r		extR

	

*/
#endif
#include "includes.h"
#include "keydef.h"
#include "TxComm.h"
#include "FPGA.h"
#include "math.h"

#include <stdlib.h>

//=====================================================
#define CP_SR_CNT						250*200
#define SR_StepToCountRatio				200
#define CMD_CXCV_ZERO	Acess_FPGA(Cx_CV_H_Value, 0);\
						Acess_FPGA(Cx_CV_L_Value, 0);\
						Acess_FPGA(Cx_CV_H_Step,  0);\
						Acess_FPGA(Cx_CV_L_Step,  0)
#define CLOSE_SOFT_START	Acess_FPGA(FPGA_Soft_Start_Delta_T,	0)						
#define CP_Error_Amount_Limit 0.015
#define CR_Error_Amount_Limit 0.001
#define CR_Limit_Step	200
					
#define Load_Limit_Ratio 		0.1
#define Minimum_Output 			0.001
#define Minimum_CurrentCC_H 	20
#define Minimum_CurrentCC_L 	40
#define Minimum_CurrentCR_H 	5
#define Minimum_CurrentCR_L 	10
#define Minimum_CurrentCP_H 	10
#define Minimum_CurrentCP_L 	20
#define Measure_Time 20
#define Determine_Point 2
#define First_Step 2


//===================================================
unsigned char  LoadON_Time[4]= {0};	
unsigned short Acquire_Cont = 0, P_Sense;
static UWORD FPGA_05_statue;
char TXData[250];
UWORD Monitor_ExtV_H;
UWORD Monitor_ExtV_L;
UWORD Monitor_ExtR_H;
UWORD Monitor_ExtR_L;
UWORD PEL3000_FPGA_Date;
unsigned short New_Set_Count_To_FPGA;	

p3k_send_tx_list TX_LIST;
//====================================================

extern char last_menu ;
extern UWORD SEQ_Tone_Count;





//=====================================================
void SendTXData(p3k_send_tx_list *data);
void MenuDecoderAddr(p3k_send_tx_list *data);
void MachineSetupFun(void);
void CCModeSetupFun(void);
void CRModeSetupFun(void);
void CVModeSetupFun(void);
void CPModeSetupFun(void);
void SeqMemSetupFun(void);
void SeqPFTimeSetupFun(void);
char GetMemIndexCT(char no);
void SaveMemFun(void);
void SaveSeqFun(void);
void SaveSeqFunAll(void);
void SavePMemFun(void);
void RecallPMemFun(void);
void CalibrationFun(void);
void RecallMemFun(void);
void WriteFlashFun(void);
void Para_Ext_Fun(void);
void FPGA_Init(void);
void FPGA_Ctrl(void);
void FPGA_OCP_OPP_Ctrl(void);
void FPGA_BATT_Ctrl(void);
void FPGA_Led_Ctrl(void);
void FPGA_Normal_Ctrl(void);
void ocp_opp_config(UBYTE IRang);
void ocp_opp_initial (OCP_OPP_RUN_Str* s);
void ocp_opp_history(UBYTE done);
void ocp_opp_set_da(OCP_OPP_RUN_Str* s);
void ocp_opp_trig_volt(OCP_OPP_RUN_Str* s);
void battery_config(void);
char battery_calcute(void);
void battery_loadoff(void);
void battery_config (void);
#if Enable_OCP_function
void FPGA_OCP_OPP_Ctrl(void);
#endif

//============================================================
extern void PEL3000_LED_Control( char mode, char onoff);
extern unsigned short sport0Read_ku(unsigned long data);
extern void Debug_printf(char *Message);
extern void Menu_Message(char *Message,int x,int y);
extern void Update_Panel(void);
extern void RestoreRealChan(void);
extern void ConstDelay(UWORD Delay_Para);
extern void RedrawProgExecute(void);
extern float Get_Parallel_Parameter(unsigned char IRange);
extern void Menu_Message_Pro(char Mode,char *Message);
extern void Prot_Setting_Process(void);

//================================================================
const unsigned short I_Circuit_Switch_Control[30]= {
	I_CC_Low_0		,I_CC_Low_1
	,I_CC_High_0	,I_CC_High_1
	,0				,0

	,I_CR_Low_0		,I_CR_Low_1
	,I_CR_High_0	,I_CR_High_1
	,0				,0

	,I_CV_Low_0		,I_CV_Low_1
	,I_CV_High_0	,I_CV_High_1
	,0				,0

	,I_CP_Low_0		,I_CP_Low_1
	,I_CP_High_0	,I_CP_High_1
	,0				,0

	,I_CC_Low_0		,I_CC_Low_1
	,I_CC_High_0	,I_CC_High_1
	,0				,0
};

const unsigned short I_Calibration_Circuit_Switch_Control[MODE_Number*6]= {
	I_CC_Low_0		,I_CC_Low_1		/* CC_MODE */
	,I_CC_High_0	,I_CC_High_1
	,0				,0

	,I_CR_Low_0		,I_CR_Low_1		/* CR_MODE */
	,I_CR_High_0	,I_CR_High_1
	,0				,0

	,I_Cal_CV_Low	,I_CV_Low_1		/* CV_MODE */
	,I_Cal_CV_High	,I_CV_High_1
	,0				,0

	,I_CP_Low_0		,I_CP_Low_1		/* CP_MODE */
	,I_CP_High_0	,I_CP_High_1
	,0				,0

	,I_Cal_CxCV_Low	,I_CC_Low_1		/* CX CV_MODE */
	,I_Cal_CxCV_High,I_CC_High_1
	,0				,0

	,I_CC_Low_0		,I_CC_Low_1 	/* F_IMON_MODE */
	,I_CC_High_0	,I_CC_High_1
	,0				,0

	,I_CC_Low_0 	,I_CC_Low_1 	/* R_IMON_MODE */
	,I_CC_High_0	,I_CC_High_1
	,0				,0

	,E_CC_Low_0		,E_CC_Low_1		/* Ext_V_CC_MODE */
	,E_CC_High_0	,E_CC_High_1
	,0				,0

	,E_CC_Low_0 	,E_CC_Low_1		/* Ext_R_CC_MODE */
	,E_CC_High_0	,E_CC_High_1
	,0				,0
};

const unsigned short E_Circuit_Switch_Control[30]= {
	E_CC_Low_0		,E_CC_Low_1
	,E_CC_High_0	,E_CC_High_1
	,0				,0

	,E_CR_Low_0		,E_CR_Low_1
	,E_CR_High_0	,E_CR_High_1
	,0				,0

	,E_CV_Low_0		,E_CV_Low_1
	,E_CV_High_0	,E_CV_High_1
	,0				,0

	,E_CP_Low_0		,E_CP_Low_1
	,E_CP_High_0	,E_CP_High_1
	,0				,0

	,E_CC_Low_0		,E_CC_Low_1
	,E_CC_High_0	,E_CC_High_1
	,0				,0
};

UWORD Acess_FPGA(ULONG Comm,UWORD Data) {
	ULONG Send_Data,Temp_Data;
	UWORD Receive_Data;
	unsigned char n;
	n = Comm>>24;
	Send_Data = (Comm&0xFFFF0000);
	Temp_Data = (ULONG)Data;
	Temp_Data &= 0x0000FFFF;
	Send_Data += Temp_Data;

#if 1
	Receive_Data = sport0Read_ku(Send_Data);
#else
	if(WriteSEQDataToFPGA_flag) {
		if(n!=5)Receive_Data = sport0Read_ku(Send_Data);
	} else
		Receive_Data = sport0Read_ku(Send_Data);
#endif

#if debug_tool
#if Enable_FPGA_history
	UWORD cntA;
	UWORD d1;
	if(G_StatusFlag & saveRunRecordFile) {
		if(SetHistroy.RecCnt>Q_num)	SetHistroy.RecCnt = 0;
		cntA = SetHistroy.RecCnt;
		d1 = Send_Data;
		if(d1 != FPGA_W[n]) {
			SetHistroy.Info.mode[cntA]=p3k_Measure_Data.Alarm;
			SetHistroy.Info.cmd[cntA]=n;
			SetHistroy.Info.data[cntA]=d1;
			SetHistroy.Info.time[cntA]= *(volatile unsigned long *) RTC_STAT;
			SetHistroy.RecCnt++;
		}
	}
#endif
	FPGA_W[n] = Send_Data;
	FPGA_R[n] = Receive_Data;
#endif

	return Receive_Data;
}
UWORD Acess_FPGA_Only(ULONG Comm,UWORD Data) {
	ULONG Send_Data,Temp_Data;
	UWORD Receive_Data;
	unsigned char n;
	UWORD cntA;
	UWORD d1;

	n = Comm>>24;
	Send_Data = (Comm&0xFFFF0000);
	Temp_Data = (ULONG)Data;
	Temp_Data &= 0x0000FFFF;
	Send_Data += Temp_Data;

	Receive_Data = sport0Read_ku(Send_Data);

	if(G_StatusFlag & saveRunRecordFile) {
		if(SetHistroy.RecCnt>Q_num)	SetHistroy.RecCnt = 0;
		cntA = SetHistroy.RecCnt;
		d1 = Send_Data;
		if(d1 != FPGA_W[n]) {
			SetHistroy.Info.mode[cntA]=p3k_Measure_Data.Alarm;
			SetHistroy.Info.cmd[cntA]=n;
			SetHistroy.Info.data[cntA]=d1;
			SetHistroy.Info.time[cntA]= *(volatile unsigned long *) RTC_STAT;
			SetHistroy.RecCnt++;
		}
	}
	FPGA_W[n] = Send_Data;
	FPGA_R[n] = Receive_Data;
	return Receive_Data;
}

UWORD Step_To_CNT(UWORD Input_Step,double Input_Gain,double Input_Offset) {
	double Output_CNT_Temp = 0.0;
	UWORD Output_CNT = 0;
	Output_CNT_Temp = ( ((double)Input_Step)*Input_Gain )+Input_Offset;
	
	if(Output_CNT_Temp>0)
		Output_CNT = (UWORD)Output_CNT_Temp;
	else
		Output_CNT = 0;

	if(Output_CNT <= Input_Offset)
		Output_CNT = 0;

	return Output_CNT;
}

void check_max_protection(void) {	/* Inital FPGA Function */
	char i,str[50];
	UWORD MaxVaule;
	for(i=LOW_RANGE ; i<=HIGH_RANGE ; i++) {
		MaxVaule = Default_Cal_Prot_DA_Rating *21/20;

		if(p3k_Cal_data.Protection[i].CPP > MaxVaule) {
			sprintf(str,"CPP Out Of Range,CPP[%d]=%d\n",i,p3k_Cal_data.Protection[i].CPP);
			Menu_Message_Pro(0,str);
			Debug_printf(str);
			p3k_Cal_data.Protection[i].CPP = Default_Cal_Prot_DA_Rating;
		}
		for(i=0; i<2; i++) {
			if(p3k_Cal_data.Protection[i].OCP>Default_Cal_Prot_DA_Rating)
				p3k_Cal_data.Protection[i].OCP = Default_Cal_Prot_DA_Rating;
			if(p3k_Cal_data.Protection[i].OPP>Default_Cal_Prot_DA_Rating)
				p3k_Cal_data.Protection[i].OPP = Default_Cal_Prot_DA_Rating;
		}
	}
}

char check_fpga_work(void) {
	UWORD chek_1, chek_2;
	char IsRight=1;
	for (chek_1=1000; chek_1<=1010; chek_1++) {
		Acess_FPGA(FPGA_Test_Register, chek_1);
		chek_2 = Acess_FPGA(FPGA_Test_Register, chek_1);
		if(chek_1!=chek_2) 	IsRight = 0;
	}

	return IsRight;
}

void FPGA_Init(void) {	/* Inital FPGA Function */
	unsigned short VM_Range = 0, IM_Range = 0, Circuit_SW0 = 0, Circuit_SW1 = 0;
	UWORD CC_H_Load_Off_Value,CC_M_Load_Off_Value,CC_L_Load_Off_Value;
	UWORD CR_H_Load_Off_Value,CR_M_Load_Off_Value,CR_L_Load_Off_Value;
	UWORD CP_H_Load_Off_Value,CP_M_Load_Off_Value,CP_L_Load_Off_Value;
	UWORD CV_H_Load_Off_Value,CV_L_Load_Off_Value;
	UWORD Voltage_H_Temp,Voltage_L_Temp;
	float CR_Def_CNT;
	SALONG LongVal;
	UWORD FPGA_Data_Temp;
	static unsigned char PowerOn_Flag = 0;
	UWORD Pallar_DA;
#if 1
	double ext_V_Gain, ext_R_Gain, Cal_Gain, Cal_Offset;
	UWORD max_Step, max_Count;
	char i;
#endif
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	p3k_send_tx_list tx_data;

	p3k_Measure_Data.VOLT = NULL;
	p3k_Measure_Data.CURR = NULL;
	p3k_Measure_Data.WATT = NULL;

	P_Sense = Set_Normal_P_Sense_Operation;

	CC_H_Load_Off_Value = Step_To_CNT(Min_Startup_Setting_H,	p3k_Cal_data.CC_Data[1].Cal_Value_Gain,p3k_Cal_data.CC_Data[1].Cal_Value_Offset);//CC_M_Load_Off_Value = Step_To_CNT(Min_Startup_Setting_M,	p3k_Cal_data.CC_Data[1].Cal_Value_Gain,p3k_Cal_data.CC_Data[1].Cal_Value_Offset);
	CC_L_Load_Off_Value = Step_To_CNT(Min_Startup_Setting_L,	p3k_Cal_data.CC_Data[0].Cal_Value_Gain,p3k_Cal_data.CC_Data[0].Cal_Value_Offset);

	CR_H_Load_Off_Value = Step_To_CNT(Min_Startup_Setting_H,	p3k_Cal_data.CR_Data[1].Cal_Value_Gain,p3k_Cal_data.CR_Data[1].Cal_Value_Offset);//CR_M_Load_Off_Value = Step_To_CNT(Min_Startup_Setting_M,	p3k_Cal_data.CR_Data[1].Cal_Value_Gain,p3k_Cal_data.CR_Data[1].Cal_Value_Offset);
	CR_L_Load_Off_Value = Step_To_CNT(Min_Startup_Setting_L,	p3k_Cal_data.CR_Data[0].Cal_Value_Gain,p3k_Cal_data.CR_Data[0].Cal_Value_Offset);

	CP_H_Load_Off_Value = Step_To_CNT(Min_Startup_Setting_H,	p3k_Cal_data.CP_Data[1].Cal_Value_Gain,p3k_Cal_data.CP_Data[1].Cal_Value_Offset);//CP_M_Load_Off_Value = Step_To_CNT(Min_Startup_Setting_M,	p3k_Cal_data.CP_Data[1].Cal_Value_Gain,p3k_Cal_data.CP_Data[1].Cal_Value_Offset);
	CP_L_Load_Off_Value = Step_To_CNT(Min_Startup_Setting_L,	p3k_Cal_data.CP_Data[0].Cal_Value_Gain,p3k_Cal_data.CP_Data[0].Cal_Value_Offset);

	CV_H_Load_Off_Value = Step_To_CNT(((ptrMODEL_TYPE->CV)[3].Def*1.1),p3k_Cal_data.CV_Data[1].Cal_Value_Gain,p3k_Cal_data.CV_Data[1].Cal_Value_Offset);
	CV_L_Load_Off_Value = Step_To_CNT(((ptrMODEL_TYPE->CV)[0].Def*1.1),p3k_Cal_data.CV_Data[0].Cal_Value_Gain,p3k_Cal_data.CV_Data[0].Cal_Value_Offset);

	if(p3k_Acq_4K_Measure_Data.Acq4K_Enable)
		Acquire_Cont |= Enable_Acquire_System;
	else
		Acquire_Cont &= ~Enable_Acquire_System;

	if(!PowerOn_Flag) {
		FPGA_Data_Temp = Acess_FPGA(FPGA_External_Status,NULL);
		PowerOn_Flag = 1;
	}

	Acess_FPGA(CC_H_Load_Off, CC_H_Load_Off_Value);	//Acess_FPGA(CC_M_Load_Off, CC_M_Load_Off_Value);
	Acess_FPGA(CC_L_Load_Off, CC_L_Load_Off_Value);
	Acess_FPGA(CR_H_Load_Off, CR_H_Load_Off_Value);	//Acess_FPGA(CR_M_Load_Off, CR_M_Load_Off_Value);
	Acess_FPGA(CR_L_Load_Off, CR_L_Load_Off_Value);
	Acess_FPGA(CP_H_Load_Off, CP_H_Load_Off_Value);	//Acess_FPGA(CP_M_Load_Off, CP_M_Load_Off_Value);
	Acess_FPGA(CP_L_Load_Off, CP_L_Load_Off_Value);
	Acess_FPGA(CV_H_Load_Off, CV_H_Load_Off_Value);
	Acess_FPGA(CV_L_Load_Off, CV_L_Load_Off_Value);

	Acess_FPGA(FPGA_XH_OS_Ref, p3k_Cal_data.PSensor.XH_Value);
	Acess_FPGA(FPGA_YH_OS_Ref, p3k_Cal_data.PSensor.YH_Value);
	Acess_FPGA(FPGA_ZH_OS_Ref, p3k_Cal_data.PSensor.ZH_Value);
	Acess_FPGA(FPGA_XL_OS_Ref, p3k_Cal_data.PSensor.XH_Value);
	Acess_FPGA(FPGA_YL_OS_Ref, p3k_Cal_data.PSensor.YH_Value);
	Acess_FPGA(FPGA_ZL_OS_Ref, p3k_Cal_data.PSensor.ZH_Value);

	check_max_protection();

	if(Data_tmp->CONF.VON_VOLT[1]<30)
		Voltage_H_Temp = 30;
	else
		Voltage_H_Temp = Data_tmp->CONF.VON_VOLT[1];

	if(Data_tmp->CONF.VON_VOLT[0]<50)
		Voltage_L_Temp = 50;
	else
		Voltage_L_Temp = Data_tmp->CONF.VON_VOLT[0];

	Acess_FPGA(FPGA_VON_H, Voltage_H_Temp);
	Acess_FPGA(FPGA_VON_L, Voltage_L_Temp);

	if((Data_tmp->CURRMODE==CV_MODE)||(Data_tmp->CONF.CV_Func_En==Switch_OFF)) {
		Acess_FPGA(Cx_CV_H_Value, 0);
		Acess_FPGA(Cx_CV_L_Value, 0);
		Acess_FPGA(Cx_CV_H_Step,  0);
		Acess_FPGA(Cx_CV_L_Step,  0);
	} else {
		if(Data_tmp->CV.STA[1].VALUE1<10)
			Voltage_H_Temp = 10;
		else
			Voltage_H_Temp = Data_tmp->CV.STA[1].VALUE1;

		if(Data_tmp->CV.STA[0].VALUE1<10)
			Voltage_L_Temp = 10;
		else
			Voltage_L_Temp = Data_tmp->CV.STA[0].VALUE1;

		Acess_FPGA(Cx_CV_H_Value, Step_To_CNT(Voltage_H_Temp,p3k_Cal_data.Protection[1].CxCV_Gain,p3k_Cal_data.Protection[1].CxCV_Offset));
		Acess_FPGA(Cx_CV_L_Value, Step_To_CNT(Voltage_L_Temp,p3k_Cal_data.Protection[0].CxCV_Gain,p3k_Cal_data.Protection[0].CxCV_Offset));
		Acess_FPGA(Cx_CV_H_Step, Voltage_H_Temp);
		Acess_FPGA(Cx_CV_L_Step, Voltage_L_Temp);
	}

	Acess_FPGA(Prot_OS_Ref, 50000);
	Acess_FPGA(FPGA_CX_H_CPP,p3k_Cal_data.Protection[IRange_High].CPP);		//Acess_FPGA(FPGA_CX_M_CPP,p3k_Cal_data.Protection[IRange_Mid].CPP);
	Acess_FPGA(FPGA_CX_L_CPP,p3k_Cal_data.Protection[IRange_Low].CPP);
	Acess_FPGA(FPGA_CX_H_OCP, p3k_Cal_data.Protection[IRange_High].OCP);		//Acess_FPGA(FPGA_CX_M_OCP, p3k_Cal_data.Protection[IRange_Mid].OCP);
	Acess_FPGA(FPGA_CX_L_OCP, p3k_Cal_data.Protection[IRange_Low].OCP);
	Acess_FPGA(FPGA_CX_H_OPP, p3k_Cal_data.Protection[IRange_High].OPP);		//Acess_FPGA(FPGA_CX_M_OPP, p3k_Cal_data.Protection[IRange_Mid].OPP);
	Acess_FPGA(FPGA_CX_L_OPP, p3k_Cal_data.Protection[IRange_Low].OPP);

#if Enable_Ext_CalOffset
	CR_Def_CNT =  (ptrMODEL_TYPE->CR)[0].Max;// /1.05;	/*Max Setting(1.05) ->Setting(1) */
	CR_Def_CNT /= 40000.0;						/*Setting	 -> Ext_Setting*/
	CR_Def_CNT *= 65535.0;

	for(i=0; i<2; i++) {
		Cal_Gain	= p3k_Cal_data.CC_Data[i].Cal_Value_Gain;
		Cal_Offset	= 0;
		max_Step = (ptrMODEL_TYPE->CC)[i*10].Max;
		max_Count = Step_To_CNT(max_Step,Cal_Gain,Cal_Offset);
		ext_V_Gain = (double)p3k_Cal_data.Ext_V_CC[i]/(double)max_Count;
		ext_R_Gain	= (double)p3k_Cal_data.Ext_R_CC[i]/(double)max_Count;

		Cal_Gain = p3k_Cal_data.CR_Data[i].Cal_Value_Gain;
		p3k_Cal_data.Ext_V_CR[i] = (ULONG)(CR_Def_CNT*Cal_Gain* ext_V_Gain);
		p3k_Cal_data.Ext_R_CR[i] = (ULONG)(CR_Def_CNT*Cal_Gain* ext_R_Gain);

		Cal_Gain	= p3k_Cal_data.CV_Data[i].Cal_Value_Gain;
		Cal_Offset	= p3k_Cal_data.CV_Data[i].Cal_Value_Offset;
		max_Step = (ptrMODEL_TYPE->CV)[i*3].Max;
		max_Count = Step_To_CNT(max_Step,Cal_Gain,Cal_Offset);

		p3k_Cal_data.Ext_V_CV[i] = max_Count * ext_V_Gain;
		p3k_Cal_data.Ext_R_CV[i] = max_Count * ext_R_Gain;

		Cal_Gain	= p3k_Cal_data.CP_Data[i].Cal_Value_Gain;
		Cal_Offset	= p3k_Cal_data.CP_Data[i].Cal_Value_Offset;
		max_Step = (ptrMODEL_TYPE->CP)[i*10].Max;
		max_Count = Step_To_CNT(max_Step,Cal_Gain,Cal_Offset);

		p3k_Cal_data.Ext_V_CP[i] = max_Count * ext_V_Gain;
		p3k_Cal_data.Ext_R_CP[i] = max_Count * ext_R_Gain;
	}

#endif

	LongVal.l  = p3k_Cal_data.Ext_V_CR[HIGH_RANGE];///(ULONG)(CR_Def_CNT*p3k_Cal_data.CR_Data[HIGH_RANGE].Cal_Value_Gain);
	Acess_FPGA(FPGA_EXT_CRH_RV_Control_Gain_MSB,  LongVal.s[1]);
	Acess_FPGA(FPGA_EXT_CRH_RV_Control_Gain_LSB,  LongVal.s[0]);

	Acess_FPGA(FPGA_EXT_CRH_RV_Control_Offset,p3k_Cal_data.CR_Data[HIGH_RANGE].Cal_Value_Offset);	//Acess_FPGA(FPGA_EXT_CRM_RV_Control_Offset,p3k_Cal_data.CR_Data[Mid_RANGE].Cal_Value_Offset);
	///Acess_FPGA(FPGA_EXT_CRL_RV_Control_Offset,p3k_Cal_data.CR_Data[LOW_RANGE].Cal_Value_Offset);

	//Acess_FPGA(FPGA_Ext_RV_Control, 59900);
	//Acess_FPGA(FPGA_Ext_RV_Control, 60737);
	Acess_FPGA(FPGA_Ext_RV_Control, 56042); //2015.08.05
	Acess_FPGA(FPGA_OS_Ref, Default_Cal_Prot_Ref);
	Acess_FPGA(FPGA_Ext_R_Cont_Ref, 59577);
	Acess_FPGA(FPGA_Current_Monitor_Out, NULL);
	Acess_FPGA(FPGA_Control, Clear_VON_Latch);
	Acess_FPGA(FPGA_H_Circuit_Switch_Control_0, I_CC_High_0);
	Acess_FPGA(FPGA_H_Circuit_Switch_Control_1, I_CC_High_1);
	Acess_FPGA(FPGA_H_Level_Slew_Rate, Default_Slew_Rate);
	Acess_FPGA(FPGA_On_Off_Reference_Setting, P_Sense | Acquire_Cont | Set_Protection_Ref_Adjust_ON | Set_Cx_Mode | Set_Load_OFF);
	Acess_FPGA(FPGA_VS_OS_Ref ,32000); 			//pel1000 only
	Acess_FPGA(FPGA_Current_Monitor_Out ,4870); //pel1000 only
	Acess_FPGA(CR_OS_REF_H ,30006);				//pel1000 only
	Acess_FPGA(CR_OS_REF_L ,30012); 			//pel1000 only


	if(Data_tmp->CONF.Ext_Setting.Control) {
		Circuit_SW0 = E_Circuit_Switch_Control[(Disp_tmp->CURRMODE*6) + (Disp_tmp->IRange*2) + 0];
		Circuit_SW1 = E_Circuit_Switch_Control[(Disp_tmp->CURRMODE*6) + (Disp_tmp->IRange*2) + 1];
	} else {
		Circuit_SW0 = I_Circuit_Switch_Control[(Disp_tmp->CURRMODE*6) + (Disp_tmp->IRange*2) + 0];
		Circuit_SW1 = I_Circuit_Switch_Control[(Disp_tmp->CURRMODE*6) + (Disp_tmp->IRange*2) + 1];
	}

	if(Data_tmp->CURRMODE==CV_MODE) {
		Acess_FPGA(FPGA_H_Circuit_Switch_Control_0, Circuit_SW0 );
		Acess_FPGA(FPGA_H_Circuit_Switch_Control_1, Circuit_SW1);
	} else {
		if(Disp_tmp->VRange)		VM_Range = 0;
		else					VM_Range = VM_L_Range;

		Acess_FPGA(FPGA_H_Circuit_Switch_Control_0, Circuit_SW0 |VM_Range);
		Acess_FPGA(FPGA_H_Circuit_Switch_Control_1, Circuit_SW1);
	}

	PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL);

	/* OCP Level */
	tx_data.ADDRH = Machine_Command;
	tx_data.ADDRL = Machine_OCP_Level;
	SendTXData(&tx_data);

	/* OPP Level */
	tx_data.ADDRH = Machine_Command;
	tx_data.ADDRL = Machine_OPP_Level;
	SendTXData(&tx_data);

	/* OCP & OPP Setting(Load OFF/Limit) */
	tx_data.ADDRH = Machine_Command;
	tx_data.ADDRL = Machine_Prot_Status;
	SendTXData(&tx_data);

	/* Soft Start */
	tx_data.ADDRH = Machine_Command;
	tx_data.ADDRL = Machine_Soft_Start;
	SendTXData(&tx_data);

	/* Sync */
	tx_data.ADDRH = Machine_Command;
	tx_data.ADDRL = Machine_TrigInDelay;
	SendTXData(&tx_data);
	
	tx_data.ADDRH = Machine_Command;
	tx_data.ADDRL = Machine_TrigOutWidth;
	SendTXData(&tx_data);

	/* Set Front and Rear IMON */
	tx_data.ADDRH = Machine_Command;
	tx_data.ADDRL = Machine_Setting_IMON;
	SendTXData(&tx_data);

	/* Parallel and External Setting */
	tx_data.ADDRH = Para_Ext_Command;
	tx_data.ADDRL = Para_Ext_Setting;
	SendTXData(&tx_data);

	tx_data.ADDRH = Cal_FPGA_Command;
	tx_data.ADDRL = Cal_FPGA_Load_Meas_Default;
	SendTXData(&tx_data);

	/* Von Delay */
	tx_data.ADDRH = Machine_Command;
	tx_data.ADDRL = Machine_Von_Delay;
	SendTXData(&tx_data);
}

#if 1 //Enable_Battery_Discharge
char CR_CP_Compensation(unsigned char Mode,UBYTE alarmFlag) {
	double Cal_Gain,Cal_Offset;
	double Error_Amount,Real_Value,Resolution;
	double Real_Volt,Real_Curr,Real_Watt;
	double Error_Amount_Count,Real_Meas_Count;
	double Real_Siemens,Set_Count_To_FPGA;
	double Compensation_Magnification,Compensation_Value;
	double objectSetValue,objectSetValue_max,objectSetValue_min;
	double Error_Amount_Percent,Error_Amount_Count_Negative;
	static double New_Set_Count_To_FPGA_Temp;
	unsigned short Set_Count,Limit_Count;

	P3k_Data_Str *Data_tmp = &P3k_Chan_Data;
	UBYTE irang;
#if Enable_Battery_Discharge
	if(BATT_Load==P3k_Chan_Data.Load_Type)
		irang = BattDisp.Range%2;
	else
#endif		
		irang = Data_tmp->IRange;

	switch(Mode) {
	case CR_MODE:
		Cal_Gain   = p3k_Cal_data.CR_Data[irang].Cal_Value_Gain;
		Cal_Offset = p3k_Cal_data.CR_Data[irang].Cal_Value_Offset;

		Real_Volt = p3k_Measure_Data.Real_Volt;
		Real_Curr = p3k_Measure_Data.Real_Curr;
		Real_Siemens = Real_Curr / Real_Volt * 1000;

		if(UTILITY.SHORT_CTL)
			Set_Count = (ptrMODEL_TYPE->CR)[irang*10].Max;
		else if(Data_tmp->CR.ABSELECT==B_Value)
			Set_Count = Data_tmp->CR.STA[irang].VALUE2;
		else {
			if((NSeq_Load==P3k_Chan_Data.Load_Type)||(FSeq_Load==P3k_Chan_Data.Load_Type ))
				Set_Count  = Prog_Seq_Data.FPGA_Seq_Data[1024].Level_Step;
			else
				Set_Count = Data_tmp->CR.STA[irang].VALUE1;
		}

		if(Compensation_Flag) {
			if(New_Set_Count_To_FPGA_Temp >= Cal_Offset)
				Set_Count_To_FPGA = New_Set_Count_To_FPGA_Temp - Cal_Offset;
			else
				break;
		} else {
			Set_Count_To_FPGA = Set_Count * Cal_Gain;
		}

		Resolution = (ptrMODEL_TYPE->CR)[irang*10].Resolution;
		Real_Value = (double)Set_Count * Resolution;
		Compensation_Magnification = Real_Value / Real_Siemens;
		Compensation_Value = Set_Count_To_FPGA * Compensation_Magnification;

		if(Set_Count_To_FPGA >= Compensation_Value)
			Error_Amount_Count = Set_Count_To_FPGA - Compensation_Value;
		else
			Error_Amount_Count = Compensation_Value - Set_Count_To_FPGA;

		Error_Amount_Percent = Error_Amount_Count / Set_Count_To_FPGA;

		Limit_Count = Cal_Gain * CR_Limit_Step;

		if(Error_Amount_Percent > CR_Error_Amount_Limit) {
			if(Limit_Count < Set_Count_To_FPGA) {
				Compensation_Flag = 1;
				New_Set_Count_To_FPGA_Temp = Compensation_Value + Cal_Offset;
				if(New_Set_Count_To_FPGA_Temp < 0)
					New_Set_Count_To_FPGA_Temp = 0;
				New_Set_Count_To_FPGA = New_Set_Count_To_FPGA_Temp + 0.5;
				Acess_FPGA(FPGA_H_Level_Setting, New_Set_Count_To_FPGA);
			}
		}
		break;
	case CP_MODE:
	default:
		Cal_Gain	= p3k_Cal_data.CP_Data[irang].Cal_Value_Gain;
		Cal_Offset	= p3k_Cal_data.CP_Data[irang].Cal_Value_Offset;
#if 0
		Real_Volt = p3k_Measure_Data.VOLT;
		Real_Curr = p3k_Measure_Data.CURR;
		Real_Watt = p3k_Measure_Data.WATT;
#else
		Real_Volt = p3k_Measure_Data.Real_Volt;
		Real_Curr = p3k_Measure_Data.Real_Curr;
		Real_Watt = Real_Volt * Real_Curr;
#endif
#if Enable_Battery_Discharge
		if(BATT_Load==P3k_Chan_Data.Load_Type){
				Set_Count = BattDisp.Setting;
#else
		if(0){
#endif			
		
		}else{
			if(UTILITY.SHORT_CTL)
				Set_Count = (ptrMODEL_TYPE->CP)[irang*10].Max;
			else if(Data_tmp->CP.ABSELECT == B_Value)
				Set_Count = Data_tmp->CP.STA[irang].VALUE2;
			else {
				if((NSeq_Load==P3k_Chan_Data.Load_Type)||(FSeq_Load==P3k_Chan_Data.Load_Type ))
					Set_Count  = Prog_Seq_Data.FPGA_Seq_Data[1024].Level_Step;
				else
					Set_Count = Data_tmp->CP.STA[irang].VALUE1;
			}
		}		
		if(Compensation_Flag) {
			objectSetValue = Set_Count * Cal_Gain;
			if(New_Set_Count_To_FPGA_Temp >= Cal_Offset)
				Set_Count_To_FPGA = New_Set_Count_To_FPGA_Temp - Cal_Offset;
			else
				break;
		} else {
			Set_Count_To_FPGA = Set_Count * Cal_Gain;
			objectSetValue = Set_Count_To_FPGA;
		}
		objectSetValue_max = objectSetValue*1.5;
		objectSetValue_min = objectSetValue*0.5;


		Resolution = (ptrMODEL_TYPE->CP)[irang*10].Resolution;
		Real_Value = Set_Count * Resolution;
		Compensation_Magnification = Real_Value / Real_Watt;
		Compensation_Value = Set_Count_To_FPGA * Compensation_Magnification;

		if(Set_Count_To_FPGA >= Compensation_Value)
			Error_Amount_Count = Set_Count_To_FPGA - Compensation_Value;
		else
			Error_Amount_Count = Compensation_Value - Set_Count_To_FPGA;

		Error_Amount_Percent = Error_Amount_Count / Set_Count_To_FPGA;

		if(Error_Amount_Percent > CP_Error_Amount_Limit) {
			Compensation_Flag = 1;
			if(Compensation_Value > objectSetValue_max)
				Compensation_Value = objectSetValue_max;
			else if (Compensation_Value < objectSetValue_min)
				Compensation_Value = objectSetValue_min;
			New_Set_Count_To_FPGA_Temp = Compensation_Value + Cal_Offset;
			if(New_Set_Count_To_FPGA_Temp < 0)
				New_Set_Count_To_FPGA_Temp = 0;
			if(alarmFlag){
				if((New_Set_Count_To_FPGA==0)||(New_Set_Count_To_FPGA_Temp + 0.5)<New_Set_Count_To_FPGA)
					New_Set_Count_To_FPGA = New_Set_Count_To_FPGA_Temp + 0.5;
			}else{
				New_Set_Count_To_FPGA = New_Set_Count_To_FPGA_Temp + 0.5;
			}
			Acess_FPGA(FPGA_H_Level_Setting, New_Set_Count_To_FPGA);
		} else {
		}
		break;
	}
	return 1;
}


void Compensation_Determine(void) {
#define compen_time		2 //5
	double Cal_Gain,Cal_Offset;
	double Resolution,Error_Amount;
	double Measure_Value,Measure_Power_Value;
	double OCP_Setting_Value,OPP_Setting_Value;
	UBYTE alarmFlag = 0;

	static double Real_Curr_New,Real_Volt_New;
	static double Real_Curr_Old,Real_Curr_Old_Positive_Limit,Real_Curr_Old_Negative_Limit;
	static double Real_Volt_Old,Real_Volt_Old_Positive_Limit,Real_Volt_Old_Negative_Limit;

	unsigned short Set_Count,Set_Count_To_FPGA;
	P3k_Data_Str *Data_tmp = &P3k_Chan_Data;	
	UBYTE irang,mode;
	
#if Enable_Battery_Discharge		
	if(BATT_Load==P3k_Chan_Data.Load_Type){
		irang = BattDisp.Range%2;
		mode = BattDisp.Mode;
#else
	if(0){
#endif		
		
	}else{
		irang = Data_tmp->IRange;
		mode = Data_tmp->CURRMODE;
	}

	if(CR_MODE == mode) {
		Cal_Gain   = p3k_Cal_data.CR_Data[irang].Cal_Value_Gain;
		Cal_Offset = p3k_Cal_data.CR_Data[irang].Cal_Value_Offset;

		if(UTILITY.SHORT_CTL)
			Set_Count = (ptrMODEL_TYPE->CR)[irang*10].Max;
		else if(Data_tmp->CR.ABSELECT == B_Value)
			Set_Count = Data_tmp->CR.STA[irang].VALUE2;
		else
			Set_Count = Data_tmp->CR.STA[irang].VALUE1;


	} else {
		Cal_Gain   = p3k_Cal_data.CP_Data[irang].Cal_Value_Gain;
		Cal_Offset = p3k_Cal_data.CP_Data[irang].Cal_Value_Offset;
#if Enable_Battery_Discharge		
		if(BATT_Load==P3k_Chan_Data.Load_Type){
			Set_Count = BattDisp.Setting;
#else
		if(0){
#endif						
		}else{	
			if(UTILITY.SHORT_CTL)
				Set_Count = (ptrMODEL_TYPE->CP)[irang*10].Max;
			else if(Data_tmp->CP.ABSELECT == B_Value)
				Set_Count = Data_tmp->CP.STA[irang].VALUE2;
			else
				Set_Count = Data_tmp->CP.STA[irang].VALUE1;
		}
	}

	Real_Curr_New = p3k_Measure_Data.Real_Curr;
	Real_Volt_New = p3k_Measure_Data.Real_Volt;

	Real_Curr_Old_Positive_Limit = Real_Curr_Old + (Real_Curr_Old * 0.002);
	Real_Curr_Old_Negative_Limit = Real_Curr_Old - (Real_Curr_Old * 0.002);

	Real_Volt_Old_Positive_Limit = Real_Volt_Old + (Real_Volt_Old * 0.05);
	Real_Volt_Old_Negative_Limit = Real_Volt_Old - (Real_Volt_Old * 0.05);

	if((p3k_Measure_Data.VOLT < 0.5) || (p3k_Measure_Data.Alarm == UnReg_Alarm)) {
		New_Set_Count_To_FPGA	= 0;
		Compensation_Flag		= 0;
		Compensation_Count		= 0;
		Error_Amount_Flag		= 0;
		Set_Count_To_FPGA		= Step_To_CNT(Set_Count,Cal_Gain,Cal_Offset);
		Acess_FPGA(FPGA_H_Level_Setting, Set_Count_To_FPGA);
	} else {
		Measure_Power_Value = p3k_Measure_Data.Real_Volt * p3k_Measure_Data.Real_Curr;

		OCP_Setting_Value = Data_tmp->PROT.OCP[irang] * ptrMODEL_TYPE->PROT[irang].Resolution;

		if(irang == LOW_RANGE) {
			if(Data_tmp->PROT.OPP[HIGH_RANGE] > (ptrMODEL_TYPE->PROT[3].Max*0.3))
				OPP_Setting_Value =  ptrMODEL_TYPE->PROT[HIGH_RANGE+2].Max * ptrMODEL_TYPE->PROT[HIGH_RANGE+2].Resolution * 0.3;
			else
				OPP_Setting_Value = Data_tmp->PROT.OPP[LOW_RANGE] * ptrMODEL_TYPE->PROT[LOW_RANGE+2].Resolution;
		} else
			OPP_Setting_Value = Data_tmp->PROT.OPP[HIGH_RANGE] * ptrMODEL_TYPE->PROT[HIGH_RANGE+2].Resolution;
		if((p3k_Measure_Data.Real_Curr > OCP_Setting_Value) || (p3k_Measure_Data.Alarm == OCP_Alarm)){
			alarmFlag = 1;
		}
		if(1){ //if((p3k_Measure_Data.Real_Curr < OCP_Setting_Value) && (p3k_Measure_Data.Alarm != OCP_Alarm)) {
			if((Measure_Power_Value < OPP_Setting_Value) && (p3k_Measure_Data.Alarm != OPP_Alarm)) {
				Real_Curr_Old = Real_Curr_New;
				Real_Volt_Old = Real_Volt_New;

				if(!Compensation_Count) {
					Compensation_Count = 1;
					if(Data_tmp->CONF.SOFT_START > 0) {
						if(Data_tmp->CONF.SOFT_START > 20)
							OSTimeDlyHMSM(0,0,0,Data_tmp->CONF.SOFT_START);
						else
							OSTimeDly(2);
					}
				}

				if(((Real_Curr_New <= Real_Curr_Old_Positive_Limit)&&(Real_Curr_New >= Real_Curr_Old_Negative_Limit)) && ((Real_Volt_New < Real_Volt_Old_Positive_Limit)&&(Real_Volt_New > Real_Volt_Old_Negative_Limit))) {
					Error_Amount_Flag++;

					if((UTILITY.LOAD_CTL || UTILITY.SHORT_CTL) && (Error_Amount_Flag > compen_time)) {
						CR_CP_Compensation(mode,alarmFlag);
						Error_Amount_Flag = compen_time-1;
						PinON;
					}else{
						PinOFF;
					}
				} else
					Error_Amount_Flag = 0;
			}
		}
	}
}
#else
char CR_CP_Compensation(unsigned char Mode) {
	double Cal_Gain,Cal_Offset;
	double Error_Amount,Real_Value,Resolution;
	double Real_Volt,Real_Curr,Real_Watt;
	double Error_Amount_Count,Real_Meas_Count;
	double Real_Siemens,Set_Count_To_FPGA;
	double Compensation_Magnification,Compensation_Value;
	double objectSetValue,objectSetValue_max,objectSetValue_min;
	double Error_Amount_Percent,Error_Amount_Count_Negative;
	static double New_Set_Count_To_FPGA_Temp;
	unsigned short Set_Count,Limit_Count;

	P3k_Data_Str *Data_tmp = &P3k_Chan_Data;

	switch(Mode) {
	case CR_MODE:
		Cal_Gain   = p3k_Cal_data.CR_Data[Data_tmp->IRange].Cal_Value_Gain;
		Cal_Offset = p3k_Cal_data.CR_Data[Data_tmp->IRange].Cal_Value_Offset;

		Real_Volt = p3k_Measure_Data.Real_Volt;
		Real_Curr = p3k_Measure_Data.Real_Curr;
		Real_Siemens = Real_Curr / Real_Volt * 1000;

		if(UTILITY.SHORT_CTL)
			Set_Count = (ptrMODEL_TYPE->CR)[0+(Data_tmp->IRange*10)].Max;
		else if(Data_tmp->CR.ABSELECT==B_Value)
			Set_Count = Data_tmp->CR.STA[Data_tmp->IRange].VALUE2;
		else {
			if((NSeq_Load==P3k_Chan_Data.Load_Type)||(FSeq_Load==P3k_Chan_Data.Load_Type ))
				Set_Count  = Prog_Seq_Data.FPGA_Seq_Data[1024].Level_Step;
			else
				Set_Count = Data_tmp->CR.STA[Data_tmp->IRange].VALUE1;
		}

		if(Compensation_Flag) {
			if(New_Set_Count_To_FPGA_Temp >= Cal_Offset)
				Set_Count_To_FPGA = New_Set_Count_To_FPGA_Temp - Cal_Offset;
			else
				break;
		} else {
			Set_Count_To_FPGA = Set_Count * Cal_Gain;
		}

		Resolution = (ptrMODEL_TYPE->CR)[(Data_tmp->IRange*10)+(Data_tmp->CR.STADYNA*4)].Resolution;
		Real_Value = (double)Set_Count * Resolution;
		Compensation_Magnification = Real_Value / Real_Siemens;
		Compensation_Value = Set_Count_To_FPGA * Compensation_Magnification;

		if(Set_Count_To_FPGA >= Compensation_Value)
			Error_Amount_Count = Set_Count_To_FPGA - Compensation_Value;
		else
			Error_Amount_Count = Compensation_Value - Set_Count_To_FPGA;

		Error_Amount_Percent = Error_Amount_Count / Set_Count_To_FPGA;

		Limit_Count = Cal_Gain * CR_Limit_Step;

		if(Error_Amount_Percent > CR_Error_Amount_Limit) {
			if(Limit_Count < Set_Count_To_FPGA) {
				Compensation_Flag = 1;
				New_Set_Count_To_FPGA_Temp = Compensation_Value + Cal_Offset;
				if(New_Set_Count_To_FPGA_Temp < 0)
					New_Set_Count_To_FPGA_Temp = 0;
				New_Set_Count_To_FPGA = New_Set_Count_To_FPGA_Temp + 0.5;
				Acess_FPGA(FPGA_H_Level_Setting, New_Set_Count_To_FPGA);
			}
		}
		break;
	case CP_MODE:
		Cal_Gain	= p3k_Cal_data.CP_Data[Data_tmp->IRange].Cal_Value_Gain;
		Cal_Offset	= p3k_Cal_data.CP_Data[Data_tmp->IRange].Cal_Value_Offset;

		Real_Volt = p3k_Measure_Data.Real_Volt;
		Real_Curr = p3k_Measure_Data.Real_Curr;
		Real_Watt = Real_Volt * Real_Curr;

		if(UTILITY.SHORT_CTL)
			Set_Count = (ptrMODEL_TYPE->CP)[0+(Data_tmp->IRange*10)].Max;
		else if(Data_tmp->CP.ABSELECT == B_Value)
			Set_Count = Data_tmp->CP.STA[Data_tmp->IRange].VALUE2;
		else {
			if((NSeq_Load==P3k_Chan_Data.Load_Type)||(FSeq_Load==P3k_Chan_Data.Load_Type ))
				Set_Count  = Prog_Seq_Data.FPGA_Seq_Data[1024].Level_Step;
			else
				Set_Count = Data_tmp->CP.STA[Data_tmp->IRange].VALUE1;
		}
		if(Compensation_Flag) {
			objectSetValue = Set_Count * Cal_Gain;
			if(New_Set_Count_To_FPGA_Temp >= Cal_Offset)
				Set_Count_To_FPGA = New_Set_Count_To_FPGA_Temp - Cal_Offset;
			else
				break;
		} else {
			Set_Count_To_FPGA = Set_Count * Cal_Gain;
			objectSetValue = Set_Count_To_FPGA;
		}
		objectSetValue_max = objectSetValue*1.5;
		objectSetValue_min = objectSetValue*0.5;


		Resolution = (ptrMODEL_TYPE->CP)[(Data_tmp->IRange*10)+(Data_tmp->CP.STADYNA*4)].Resolution;
		Real_Value = Set_Count * Resolution;
		Compensation_Magnification = Real_Value / Real_Watt;
		Compensation_Value = Set_Count_To_FPGA * Compensation_Magnification;

		if(Set_Count_To_FPGA >= Compensation_Value)
			Error_Amount_Count = Set_Count_To_FPGA - Compensation_Value;
		else
			Error_Amount_Count = Compensation_Value - Set_Count_To_FPGA;

		Error_Amount_Percent = Error_Amount_Count / Set_Count_To_FPGA;

		if(Error_Amount_Percent > CR_Error_Amount_Limit) {
			Compensation_Flag = 1;
			if(Compensation_Value > objectSetValue_max)
				Compensation_Value = objectSetValue_max;
			else if (Compensation_Value < objectSetValue_min)
				Compensation_Value = objectSetValue_min;
			New_Set_Count_To_FPGA_Temp = Compensation_Value + Cal_Offset;
			if(New_Set_Count_To_FPGA_Temp < 0)
				New_Set_Count_To_FPGA_Temp = 0;
			New_Set_Count_To_FPGA = New_Set_Count_To_FPGA_Temp + 0.5;
			Acess_FPGA(FPGA_H_Level_Setting, New_Set_Count_To_FPGA);
		} else {
		}
		break;
	default:
		break;
	}
	return 1;
}
void Compensation_Determine(void) {
	double Cal_Gain,Cal_Offset;
	double Resolution,Error_Amount;
	double Measure_Value,Measure_Power_Value;
	double OCP_Setting_Value,OPP_Setting_Value;

	static double Real_Curr_New,Real_Volt_New;
	static double Real_Curr_Old,Real_Curr_Old_Positive_Limit,Real_Curr_Old_Negative_Limit;
	static double Real_Volt_Old,Real_Volt_Old_Positive_Limit,Real_Volt_Old_Negative_Limit;

	unsigned short Set_Count,Set_Count_To_FPGA;

	P3k_Data_Str *Data_tmp = &P3k_Chan_Data;

	if(CR_MODE == Data_tmp->CURRMODE) {
		Cal_Gain   = p3k_Cal_data.CR_Data[Data_tmp->IRange].Cal_Value_Gain;
		Cal_Offset = p3k_Cal_data.CR_Data[Data_tmp->IRange].Cal_Value_Offset;

		if(UTILITY.SHORT_CTL)
			Set_Count = (ptrMODEL_TYPE->CR)[0+(Data_tmp->IRange*10)].Max;
		else if(Data_tmp->CR.ABSELECT == B_Value)
			Set_Count = Data_tmp->CR.STA[Data_tmp->IRange].VALUE2;
		else
			Set_Count = Data_tmp->CR.STA[Data_tmp->IRange].VALUE1;
	} else {
		Cal_Gain   = p3k_Cal_data.CP_Data[Data_tmp->IRange].Cal_Value_Gain;
		Cal_Offset = p3k_Cal_data.CP_Data[Data_tmp->IRange].Cal_Value_Offset;

		if(UTILITY.SHORT_CTL)
			Set_Count = (ptrMODEL_TYPE->CP)[0+(Data_tmp->IRange*10)].Max;
		else if(Data_tmp->CP.ABSELECT == B_Value)
			Set_Count = Data_tmp->CP.STA[Data_tmp->IRange].VALUE2;
		else
			Set_Count = Data_tmp->CP.STA[Data_tmp->IRange].VALUE1;
	}

	Real_Curr_New = p3k_Measure_Data.Real_Curr;
	Real_Volt_New = p3k_Measure_Data.Real_Volt;

	Real_Curr_Old_Positive_Limit = Real_Curr_Old + (Real_Curr_Old * 0.05);
	Real_Curr_Old_Negative_Limit = Real_Curr_Old - (Real_Curr_Old * 0.05);

	Real_Volt_Old_Positive_Limit = Real_Volt_Old + (Real_Volt_Old * 0.05);
	Real_Volt_Old_Negative_Limit = Real_Volt_Old - (Real_Volt_Old * 0.05);

	if((p3k_Measure_Data.VOLT < 0.5) || (p3k_Measure_Data.Alarm == UnReg_Alarm)) {
		New_Set_Count_To_FPGA	= 0;
		Compensation_Flag		= 0;
		Compensation_Count		= 0;
		Error_Amount_Flag		= 0;
		Set_Count_To_FPGA		= Step_To_CNT(Set_Count,Cal_Gain,Cal_Offset);
		Acess_FPGA(FPGA_H_Level_Setting, Set_Count_To_FPGA);
	} else {
		Measure_Power_Value = p3k_Measure_Data.Real_Volt * p3k_Measure_Data.Real_Curr;

		OCP_Setting_Value = Data_tmp->PROT.OCP[Data_tmp->IRange] * ptrMODEL_TYPE->PROT[Data_tmp->IRange].Resolution;

		if(Data_tmp->IRange == LOW_RANGE) {
			if((Data_tmp->IRange == LOW_RANGE) && (Data_tmp->PROT.OPP[HIGH_RANGE] > (ptrMODEL_TYPE->PROT[PROT_OPP_H].Max*0.3)))
				OPP_Setting_Value =  ptrMODEL_TYPE->PROT[HIGH_RANGE+PROT_OPP_L].Max * ptrMODEL_TYPE->PROT[HIGH_RANGE+PROT_OPP_L].Resolution * 0.3;
			else
				OPP_Setting_Value = Data_tmp->PROT.OPP[Data_tmp->IRange] * ptrMODEL_TYPE->PROT[Data_tmp->IRange+PROT_OPP_L].Resolution;
		} else
			OPP_Setting_Value = Data_tmp->PROT.OPP[HIGH_RANGE] * ptrMODEL_TYPE->PROT[HIGH_RANGE+PROT_OPP_L].Resolution;

		if((p3k_Measure_Data.Real_Curr < OCP_Setting_Value) && (p3k_Measure_Data.Alarm != OCP_Alarm)) {
			if((Measure_Power_Value < OPP_Setting_Value) && (p3k_Measure_Data.Alarm != OPP_Alarm)) {
				Real_Curr_Old = Real_Curr_New;
				Real_Volt_Old = Real_Volt_New;

				if(!Compensation_Count) {
					Compensation_Count = 1;
					if(Data_tmp->CONF.SOFT_START > 0) {
						if(Data_tmp->CONF.SOFT_START > 20)
							OSTimeDlyHMSM(0,0,0,Data_tmp->CONF.SOFT_START);
						else
							OSTimeDly(2);
					}
				}

				if(((Real_Curr_New <= Real_Curr_Old_Positive_Limit)&&(Real_Curr_New >= Real_Curr_Old_Negative_Limit)) && ((Real_Volt_New < Real_Volt_Old_Positive_Limit)&&(Real_Volt_New > Real_Volt_Old_Negative_Limit))) {
					Error_Amount_Flag++;

					if((UTILITY.LOAD_CTL || UTILITY.SHORT_CTL) && (Error_Amount_Flag > 5)) {
						CR_CP_Compensation(Data_tmp->CURRMODE);
						Error_Amount_Flag = 4;
					}
				} else
					Error_Amount_Flag = 0;
			}
		}
	}
}
#endif
void Timer_Setting(UWORD *T1_RANGE, UWORD *T2_RANGE, UWORD *Timer1, UWORD *Timer2) {
	unsigned char Frequency_Range;
	unsigned short Frequency_Count,Duty;
	double Resolution,Real_Frequency,Real_Total_Timer,Real_Timer1,Real_Timer2;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	if(Data_tmp->CONF.Dyna_Time) {
		switch(Data_tmp->CURRMODE) {
		case CC_MODE:
			Frequency_Range = Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency_Range;
			Frequency_Count = Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency;
			Duty = Data_tmp->CC.DYNA[Data_tmp->IRange].Duty;
			break;
		case CR_MODE:
			Frequency_Range = Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency_Range;
			Frequency_Count = Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency;
			Duty = Data_tmp->CR.DYNA[Data_tmp->IRange].Duty;
			break;
		default:
			break;
		}

		if(Frequency_Range == Dyn_Freq_TimeBase_100Hz)		Resolution = 100;
		else if(Frequency_Range == Dyn_Freq_TimeBase_10Hz)	Resolution = 10;
		else if(Frequency_Range == Dyn_Freq_TimeBase_1Hz)	Resolution = 1;
		else												Resolution = 0.1;

		Real_Frequency 	= Frequency_Count * Resolution;
		Real_Total_Timer = (1 / Real_Frequency) * 1000;
		Real_Timer1 = Real_Total_Timer * Duty * 0.01 * 0.1;
		Real_Timer2 = Real_Total_Timer - Real_Timer1;

		if(Real_Timer1 < 0.010) {
			Real_Timer1 = 0.010;
			Real_Timer2 = Real_Total_Timer - Real_Timer1;
		}
		if(Real_Timer2 < 0.010) {
			Real_Timer2 = 0.010;
			Real_Timer1 = Real_Total_Timer - Real_Timer2;
		}
		if(Real_Timer1 <= 30) {
			*T1_RANGE = Dyn_TimeBase_1us;
			*Timer1 = Real_Timer1 / 0.001;
		} else if(Real_Timer1 < 31) {
			*T1_RANGE = Dyn_TimeBase_1us;
			*Timer1 = 10 / 0.001;
		} else {
			*T1_RANGE = Dyn_TimeBase_1ms;
			*Timer1 = Real_Timer1;
		}
		if(Real_Timer2 <= 10) {
			*T2_RANGE = Dyn_TimeBase_1us;
			*Timer2 = Real_Timer2 / 0.001;
		} else if(Real_Timer2 < 11) {
			*T2_RANGE = Dyn_TimeBase_1us;
			*Timer2 = 10 / 0.001;
		} else {
			*T2_RANGE = Dyn_TimeBase_1ms;
			*Timer2 = Real_Timer2;
		}

	} else {
		switch(Data_tmp->CURRMODE) {
		case CC_MODE:
			*T1_RANGE = Data_tmp->CC.DYNA[Data_tmp->IRange].T1_RANGE;
			*T2_RANGE = Data_tmp->CC.DYNA[Data_tmp->IRange].T2_RANGE;
			*Timer1 = Data_tmp->CC.DYNA[Data_tmp->IRange].TIME1;
			*Timer2 = Data_tmp->CC.DYNA[Data_tmp->IRange].TIME2;
			break;
		case CR_MODE:
			*T1_RANGE = Data_tmp->CR.DYNA[Data_tmp->IRange].T1_RANGE;
			*T2_RANGE = Data_tmp->CR.DYNA[Data_tmp->IRange].T2_RANGE;
			*Timer1 = Data_tmp->CR.DYNA[Data_tmp->IRange].TIME1;
			*Timer2 = Data_tmp->CR.DYNA[Data_tmp->IRange].TIME2;
			break;
		default:
			break;
		}
	}
}

UBYTE Minimum_Current(UBYTE MODE,UWORD *LEVEL1,UWORD *LEVEL2) {
	unsigned short Level1_Min=0,Level2_Min=0;
	unsigned short Load_Off_Value;
	unsigned char Result=0;

	P3k_Data_Str *Data_tmp = &P3k_Chan_Data;

	switch(MODE) {
	case CC_MODE:
		if(Data_tmp->CC.STADYNA) {
			if((*LEVEL1 < Load_Limit_Ratio * (ptrMODEL_TYPE->CC)[0+(Data_tmp->IRange*10)+4].Max)||(*LEVEL2 < Load_Limit_Ratio * (ptrMODEL_TYPE->CC)[1+(Data_tmp->IRange*10)+4].Max))
				Result = 1;
			if(Data_tmp->IRange == HIGH_RANGE ) {
				if(*LEVEL1 < Minimum_CurrentCC_H)
					*LEVEL1 = Minimum_CurrentCC_H;
				if(*LEVEL2 < Minimum_CurrentCC_H)
					*LEVEL2 = Minimum_CurrentCC_H;
			} else {
				if(*LEVEL1 < Minimum_CurrentCC_L)
					*LEVEL1 = Minimum_CurrentCC_L;
				if(*LEVEL2 < Minimum_CurrentCC_L)
					*LEVEL2 = Minimum_CurrentCC_L;
			}
		} else {
			if(*LEVEL1 < Load_Limit_Ratio * (ptrMODEL_TYPE->CC)[0+(Data_tmp->IRange*10)+4].Max)
				Result = 1;

			if(Data_tmp->IRange == HIGH_RANGE) {
				if(*LEVEL1 <= Minimum_CurrentCC_H)
					Load_Off_Value = Step_To_CNT(*LEVEL1, p3k_Cal_data.CC_Data[1].Cal_Value_Gain,p3k_Cal_data.CC_Data[1].Cal_Value_Offset);
				else
					Load_Off_Value = Step_To_CNT(Minimum_CurrentCC_H, p3k_Cal_data.CC_Data[1].Cal_Value_Gain,p3k_Cal_data.CC_Data[1].Cal_Value_Offset);

				Acess_FPGA(CC_H_Load_Off, Load_Off_Value);
			} else {
				if(*LEVEL1 <= Minimum_CurrentCC_L) {
					Load_Off_Value = Step_To_CNT(*LEVEL1, p3k_Cal_data.CC_Data[0].Cal_Value_Gain,p3k_Cal_data.CC_Data[0].Cal_Value_Offset);
				} else {
					Load_Off_Value = Step_To_CNT(Minimum_CurrentCC_L, p3k_Cal_data.CC_Data[0].Cal_Value_Gain,p3k_Cal_data.CC_Data[0].Cal_Value_Offset);
				}

				Acess_FPGA(CC_L_Load_Off, Load_Off_Value);
			}
		}
		break;
	case CR_MODE:
		if(Data_tmp->CR.STADYNA) {
			if((*LEVEL1 < Load_Limit_Ratio * (ptrMODEL_TYPE->CR)[0+(Data_tmp->IRange*10)+4].Max)||(*LEVEL2 < Load_Limit_Ratio * (ptrMODEL_TYPE->CR)[1+(Data_tmp->IRange*10)+4].Max))
				Result = 1;

			if(Data_tmp->IRange == HIGH_RANGE ) {
				if(*LEVEL1 < Minimum_CurrentCR_H)
					*LEVEL1 = Minimum_CurrentCR_H;
				if(*LEVEL2 < Minimum_CurrentCR_H)
					*LEVEL2 = Minimum_CurrentCR_H;
			} else {
				if(*LEVEL1 < Minimum_CurrentCR_L)
					*LEVEL1 = Minimum_CurrentCR_L;
				if(*LEVEL2 < Minimum_CurrentCR_L)
					*LEVEL2 = Minimum_CurrentCR_L;
			}
		} else {
			if(*LEVEL1 < Load_Limit_Ratio * (ptrMODEL_TYPE->CR)[0+(Data_tmp->IRange*10)+4].Max)
				Result = 1;


			if(Data_tmp->IRange == HIGH_RANGE) {
				if(*LEVEL1 <= Minimum_CurrentCR_H)
					Load_Off_Value = Step_To_CNT(*LEVEL1, p3k_Cal_data.CR_Data[1].Cal_Value_Gain,p3k_Cal_data.CR_Data[1].Cal_Value_Offset);
				else
					Load_Off_Value = Step_To_CNT(Minimum_CurrentCR_H, p3k_Cal_data.CR_Data[1].Cal_Value_Gain,p3k_Cal_data.CR_Data[1].Cal_Value_Offset);

				Acess_FPGA(CR_H_Load_Off, Load_Off_Value);
			} else {
				if(*LEVEL1 <= Minimum_CurrentCR_L)
					Load_Off_Value = Step_To_CNT(*LEVEL1, p3k_Cal_data.CR_Data[0].Cal_Value_Gain,p3k_Cal_data.CR_Data[0].Cal_Value_Offset);
				else
					Load_Off_Value = Step_To_CNT(Minimum_CurrentCR_L, p3k_Cal_data.CR_Data[0].Cal_Value_Gain,p3k_Cal_data.CR_Data[0].Cal_Value_Offset);

				Acess_FPGA(CR_L_Load_Off, Load_Off_Value);
			}
		}

		break;
	case CP_MODE:
		if(*LEVEL1 < Load_Limit_Ratio * (ptrMODEL_TYPE->CP)[0+(Data_tmp->IRange*10)+4].Max)
			Result = 1;

		if(Data_tmp->IRange == HIGH_RANGE) {
			if(*LEVEL1 <= Minimum_CurrentCP_H)
				Load_Off_Value = Step_To_CNT(*LEVEL1, p3k_Cal_data.CP_Data[1].Cal_Value_Gain,p3k_Cal_data.CP_Data[1].Cal_Value_Offset);
			else
				Load_Off_Value = Step_To_CNT(Minimum_CurrentCP_H, p3k_Cal_data.CP_Data[1].Cal_Value_Gain,p3k_Cal_data.CP_Data[1].Cal_Value_Offset);

			Acess_FPGA(CP_H_Load_Off, Load_Off_Value);
		} else {
			if(*LEVEL1 <= Minimum_CurrentCP_L)
				Load_Off_Value = Step_To_CNT(*LEVEL1, p3k_Cal_data.CP_Data[0].Cal_Value_Gain,p3k_Cal_data.CP_Data[0].Cal_Value_Offset);
			else
				Load_Off_Value = Step_To_CNT(Minimum_CurrentCP_L, p3k_Cal_data.CP_Data[0].Cal_Value_Gain,p3k_Cal_data.CP_Data[0].Cal_Value_Offset);

			Acess_FPGA(CP_L_Load_Off, Load_Off_Value);
		}
		break;
	default:
		Result = 0;
		break;
	}

	return Result;
}

UWORD get_response(UBYTE Run_Mode) {
	UWORD ResponseValue = 0;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	switch(Run_Mode) { 
	default:
		Debug_printf("FPGA_Ctrl_Cal_Data_Error\n");
	case CC_MODE:
		if(Data_tmp->CC.CXCV_RESPOSNE == CXCV_ResponseSlow)	ResponseValue |= CXCV_Response_slow;
		break;
	case CR_MODE:
		if(Data_tmp->CR.CXCV_RESPOSNE == CXCV_ResponseSlow)	ResponseValue |= CXCV_Response_slow;
		break;
	case CV_MODE:
		if(Data_tmp->CV.RESPONSE== CVCP_ResponseSlow)ResponseValue |= CV_Response_slow;
		else if(Data_tmp->CV.RESPONSE== CVCP_ResponseNormal)ResponseValue |= CV_Response_normal;
		else ResponseValue |= CV_Response_fast;
		break;
	case CP_MODE:
		if(Data_tmp->CP.RESPONSE== CVCP_ResponseSlow)ResponseValue |= CP_Response_slow;
		else if(Data_tmp->CP.RESPONSE== CVCP_ResponseNormal)ResponseValue |= CP_Response_normal;
		else ResponseValue |= CP_Response_fast;
		if(Data_tmp->CP.CXCV_RESPOSNE == CXCV_ResponseSlow)	ResponseValue |= CXCV_Response_slow;
		break;
	}
	return ResponseValue;
}
#if 1
UWORD get_external_cotrol_singnal(void){
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	SALONG LongVal;
	UWORD setValue;
	
	if(Data_tmp->CONF.Ext_Setting.Control==Ext_Setting_V) {
		if(Data_tmp->CURRMODE==CC_MODE) {
			setValue	= p3k_Cal_data.Ext_V_CC[Data_tmp->IRange];
		} else if(Data_tmp->CURRMODE==CR_MODE) {
			LongVal.l  = p3k_Cal_data.Ext_V_CR[Data_tmp->IRange];
			Acess_FPGA(FPGA_EXT_CRH_RV_Control_Offset,p3k_Cal_data.CR_Data[Data_tmp->IRange].Cal_Value_Offset);
			Acess_FPGA(FPGA_EXT_CRH_RV_Control_Gain_MSB,  LongVal.s[1]);
			Acess_FPGA(FPGA_EXT_CRH_RV_Control_Gain_LSB,  LongVal.s[0]);
			setValue	= p3k_Cal_data.Ext_V_CC[Data_tmp->IRange];
		} else if(Data_tmp->CURRMODE==CV_MODE) {
			setValue	= p3k_Cal_data.Ext_V_CV[Data_tmp->VRange];
		} else if(Data_tmp->CURRMODE==CP_MODE) {
			setValue	= p3k_Cal_data.Ext_V_CP[Data_tmp->IRange];
		}
	} else {
		if(Data_tmp->CURRMODE==CC_MODE) {
			setValue	= p3k_Cal_data.Ext_R_CC[Data_tmp->IRange];
		} else if(Data_tmp->CURRMODE==CR_MODE) {
			LongVal.l  = p3k_Cal_data.Ext_R_CR[Data_tmp->IRange];
			Acess_FPGA(FPGA_EXT_CRH_RV_Control_Gain_MSB,  LongVal.s[1]);
			Acess_FPGA(FPGA_EXT_CRH_RV_Control_Gain_LSB,  LongVal.s[0]);
			setValue	= p3k_Cal_data.Ext_R_CC[Data_tmp->IRange];
		} else if(Data_tmp->CURRMODE==CV_MODE) {
			setValue	= p3k_Cal_data.Ext_R_CV[Data_tmp->VRange];
		} else if(Data_tmp->CURRMODE==CP_MODE) {
			setValue	= p3k_Cal_data.Ext_R_CP[Data_tmp->IRange];
		}
	}
	return setValue;
}
#endif

void FPGA_Ctrl(void){	/* FPGA Control Function */ //10 msec/time
	switch(P3k_Chan_Data.Load_Type){
#if Enable_Battery_Discharge
	case BATT_Load:
		FPGA_BATT_Ctrl();
		break;	
#endif
#if Enable_LED_function
	case FLED_Load:
	case CLED_Load:
		FPGA_Led_Ctrl();
		break;
#endif		
	case OCP_Load:	
	case OPP_Load:	
		if(UTILITY.LOAD_CTL)break;	
	default:
		FPGA_Normal_Ctrl();
		break;		
	}
}



#if Enable_LED_function
void set_measure_range(UBYTE iRange, UBYTE vRange){
	P3k_Chan_Data.IRange = P3k_Disp_Data.IRange = iRange;
	P3k_Chan_Data.VRange = P3k_Disp_Data.VRange = vRange;
}
void set_func_mode_range(UBYTE mode,UBYTE iRange,UBYTE vRange){
	UWORD Circuit_SW0 = 0;
	UWORD Circuit_SW1 = 0;
	UWORD VM_Range = 0;
	UWORD SR1_Speed_flag = 0;
	UWORD Response_Setting;
	switch(mode) {
	default:
		Debug_printf("FPGA_Ctrl_Cal_Data_Error\n");
	case CC_MODE:
		Acess_FPGA(FPGA_IS_OS_Ref, p3k_Cal_data.CC_offseAdj[iRange]);
		break;
	case CR_MODE:
		SR1_Speed_flag=Bit5;
		Acess_FPGA(FPGA_IS_OS_Ref, p3k_Cal_data.CR_offseAdj[iRange]);
		break;
	case CV_MODE:
		Acess_FPGA(FPGA_IS_OS_Ref, p3k_Cal_data.CV_offseAdj[1]);
		break;
	case CP_MODE:
		Acess_FPGA(FPGA_IS_OS_Ref, p3k_Cal_data.CP_offseAdj[iRange]);
		break;
	}
	Response_Setting = get_response(mode);	
	Circuit_SW0 = I_Circuit_Switch_Control[(mode*6) + (iRange*2) + 0];
	Circuit_SW1 = I_Circuit_Switch_Control[(mode*6) + (iRange*2) + 1];
	
	if(vRange==LOW_RANGE)	VM_Range = VM_L_Range;
	Acess_FPGA(FPGA_H_Circuit_Switch_Control_0, Circuit_SW0 |VM_Range);
	Acess_FPGA(FPGA_H_Circuit_Switch_Control_1, Circuit_SW1 |Response_Setting |SR1_Speed_flag);
}


void get_func_range(UBYTE loadType,UBYTE* iRange,UBYTE* vRange){
	UBYTE temp;
	switch(loadType){
	case OCP_Load:
		break;
	case OPP_Load:
		break;
	case BATT_Load:
		break;
	case FLED_Load:
		temp = P3k_FLed_Disp.currTemp;
		*iRange = P3k_FLed_Disp.seq[temp].range % 2; 
		*vRange = P3k_FLed_Disp.seq[temp].range / 2; 
		break;	
	case CLED_Load:
		temp = P3k_CLed_Disp.currTemp;
		*iRange = P3k_CLed_Disp.seq[temp].range % 2; 
		*vRange = P3k_CLed_Disp.seq[temp].range / 2; 
		break;
	default:
		break;		
	}
}

void set_func_sr(UBYTE loadType){
	UBYTE temp;
	UWORD sr;
	switch(loadType){
	case OCP_Load:
		break;
	case OPP_Load:
		break;
	case BATT_Load:
		break;
	case FLED_Load:
		temp = P3k_FLed_Disp.currTemp;
		sr = P3k_FLed_Disp.seq[temp].response*500;			
		break;	
	case CLED_Load:
		temp = P3k_CLed_Disp.currTemp;
		sr = P3k_CLed_Disp.seq[temp].response*500;	
		break;	
	default:
		break;		
	}
	Acess_FPGA(FPGA_H_Level_Slew_Rate, sr);
}

void set_func_fled_ad (void){
	ULONG dat1;
	float dat;

	F_LED_Str *D = &P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp];

	UBYTE iRange = D->range % 2;
	UBYTE vRange = D->range / 2;

	float R_cc = (ptrMODEL_TYPE->CC)[iRange*10].Resolution;
	float R_cv = (ptrMODEL_TYPE->CV)[vRange*3].Resolution;
	float R_cr = (ptrMODEL_TYPE->CR)[vRange*10].Resolution; //Adam_test 

	float Gain_cc = p3k_Cal_data.CC_Data[iRange].Cal_Value_Gain;
	UWORD iOffset;
	
	//float Gain_cv = p3k_Cal_data.CV_Data[vRange].Cal_Value_Gain;
	float Gain_cr = p3k_Cal_data.CR_Data[vRange].Cal_Value_Gain; //Adam_test
	float Gain_m;
	if(p3k_Cal_data.CC_Data[iRange].Cal_Value_Offset>0)
		iOffset = (UWORD)p3k_Cal_data.CC_Data[iRange].Cal_Value_Offset;
	else
		iOffset = 0;
	if(Model_Number==MODEL3031E)		Gain_m = MEASURE_GAIN_3031;
	else 							Gain_m = MEASURE_GAIN_3032;

	switch(D->mode){
	case P_F_LED_MODE_VoIo:
		D->rdcoff = 8000;		 
	case P_F_LED_MODE_VoIoRc:
		//step_vf = step_vo * (1-rdcoeff) 								//unit: (V_step)
		//vf_cnt = step_vf / Gain_m  									//unit: (Vm_step) 
		//rd_cnt = ( step_vo * rdcoeff / Gain_m) / (step_io * gain_cc)    		//unit: (Vm_step / io_cnt) 
		D->vf	= ((ULONG)D->vo*(10000-D->rdcoff)/10000);		
		D->vfCnt = (float)D->vf/Gain_m;		
		D->rdCnt = (float)D->vo*(float)D->rdcoff/10000/((float)D->io*Gain_cc)/Gain_m*65535; 	
		break;
	case P_F_LED_MODE_VoIoRd:		
		// step_vf = step_vo - ( step_io * R_cc * 1000 * R_cr / step_cr / R_cv)
		// vf_cnt = vf / Gain_m
		//rd_cnt = ( 1000 * R_cr / step_rd ) * R_cc / gain_cc / R_cv / Gain_m
		D->vf = D->vo - ((float)D->io * R_cc * 1000/ R_cr/ (float)D->rd / R_cv);
		D->vfCnt = (float)D->vf/Gain_m;		
		D->rdCnt = (1000 / R_cr / (float)D->rd )* R_cc / Gain_cc / R_cv / Gain_m *65535;		
		break;
	case P_F_LED_MODE_VoIoVf:
		//vfcnt = step_vf / gain_M
		//rd_cnt = ((vo-vf)/gain_m) / (step_io * gain_cc)
		D->vfCnt = D->vf/Gain_m;	
		D->rdCnt = (float)(D->vo-D->vf)/((float)D->io*Gain_cc)/Gain_m*65535;
		break;
	case P_F_LED_MODE_VfRdPcs:
		//vfcnt = step_vf / gain_M
		//rd_cnt = ( 1000 * R_cr / step_rd ) * R_cc / gain_cc / R_cv / Gain_m *pcs
		D->vfCnt = (float)D->vf/Gain_m;	
		D->rdCnt = (1000 / R_cr / (float)D->rd )* R_cc / Gain_cc / R_cv / Gain_m * (float)D->pcs*65535 ;	
		break;
	default:
		break;
	}
	//Acess_FPGA(FPGA_LED_SLEW_SCALING_GATE, D->rdCnt);
	dat1 = (ULONG)((double)65535/(double)D->rdCnt*65535);
	///printf("r:%x\n",D->rdCnt);
	///printf("g:%x\n",dat1);
	Acess_FPGA(FPGA_LED_SLEW_SCALING_GATE_H, (UWORD)(dat1>>16));
	Acess_FPGA(FPGA_LED_SLEW_SCALING_GATE_L, (UWORD)(dat1&0xFFFF));	
	Acess_FPGA(FPGA_VD_CNT, D->vfCnt);
	Acess_FPGA(FPGA_LED_SLEW_SCALING_OFFSET,iOffset);
	//printf("vf:%d,rd:%d\n",D->vfCnt,D->rdCnt);
 }

void init_fled(void){	
	UWORD i;	
	UBYTE iRange,vRange;

	get_func_range(FLED_Load,&iRange,&vRange);
	set_measure_range(iRange,vRange);
	set_func_mode_range(CC_MODE,iRange,vRange);
	set_func_sr(FLED_Load);
	Prot_Setting_Process();
	CMD_CXCV_ZERO;
	CLOSE_SOFT_START;
	Acess_FPGA(FPGA_LED_MODE_ENABLE, 0x03);	
 	set_func_fled_ad();
}

void set_func_cled_ad (void){
	UWORD i,dat2;
	ULONG dat;
	F_LED_Str *D = &P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp];
	double V=0,I,deltaV;
	
	UBYTE iRange = D->range % 2;
	UBYTE vRange = D->range / 2;
	UWORD maxCurrCnt = (float)(ptrMODEL_TYPE->CC)[iRange*10].Max *(1.12/1.02);
	//UWORD maxCurrCnt = (float)(ptrMODEL_TYPE->CC)[iRange*10].Max ;//*(1.12/1.02);

	
	float R_cc = (ptrMODEL_TYPE->CC)[iRange*10].Resolution;
	float R_cv = (ptrMODEL_TYPE->CV)[vRange*3].Resolution;
	float maxVolt = (ptrMODEL_TYPE->CV)[vRange*3].Max*R_cv*(1.10/1.02);
	float maxCurr = maxCurrCnt *R_cc;
	float Gain_m;

	double iGain	= p3k_Cal_data.CC_Data[iRange].Cal_Value_Gain;
	double iOffset	= p3k_Cal_data.CC_Data[iRange].Cal_Value_Offset;
	
	
	if(Model_Number==MODEL3031E)		Gain_m = MEASURE_GAIN_3031;
	else 							Gain_m = MEASURE_GAIN_3032;
	
	Acess_FPGA(FPGA_LED_MODE_ENABLE, 0x0001);
	Acess_FPGA(FPGA_LED_ADDR_CLEAR,  0x0001);
	dat = (UWORD)(maxVolt / R_cv / Gain_m);
	dat = 65535 * 12288 / dat;
	Acess_FPGA(FPGA_LED_SLEW_SCALING_GATE_H,  0);
	Acess_FPGA(FPGA_LED_SLEW_SCALING_GATE_L,  dat);

	deltaV = maxVolt / 12288;
	for(i=0;i<12288;i++){
		V += deltaV;
		I = (double)D->ir * (exp((double)D->c * V) - 1);

		if(I>maxCurr){
			dat2 = maxCurrCnt;
			dat2 = Step_To_CNT(dat2,iGain,iOffset);
			Acess_FPGA(FPGA_LED_LUT_DATA, dat2);
			///printf("kkkk%d:%1.3f,V:%f,d:%d,I:%f\n",i,I,V,dat2,maxCurr);
			i++;
			break;
		}else{	
			dat2 = I / R_cc;
			//step to count gain offset
			if((i%8)==0)
				printf("I:%1.3f,V:%1.3f,d:%d\n",I,V,dat2);
		}
		dat2 = Step_To_CNT(dat2,iGain,iOffset);
		Acess_FPGA(FPGA_LED_LUT_DATA, dat2);
		///if((i%8)==0)printf("I:%1.3f,V:%1.3f,d:%d\n",I,V,dat2);
	}	
	for(;i<12288;i++){
		V += deltaV;
		Acess_FPGA(FPGA_LED_LUT_DATA, dat2);
		///if((i%512)==0)		printf("I%d:%1.3f,V:%f,d:%d\n",i,I,V,dat2);
	}
	///printf("I%d:%1.3f,V:%f,d:%d\n",i,I,V,dat2);
	///printf("vf:%d,rd:%d\n",D->vfCnt,D->rdCnt);
}
void close_led_fpga(void){
	Acess_FPGA(FPGA_On_Off_Reference_Setting,FPGA_05_statue&0xFFFE);
	Acess_FPGA(FPGA_LED_ADDR_CLEAR,  0x0001);
	Acess_FPGA(FPGA_LED_MODE_ENABLE, 0x0000);
}
void init_cled(void){
	
	UWORD i;	
	UBYTE iRange,vRange;

	get_func_range(CLED_Load,&iRange,&vRange);
	set_measure_range(iRange,vRange);
	set_func_mode_range(CC_MODE,iRange,vRange);
	set_func_sr(CLED_Load);
	Prot_Setting_Process();
	CLOSE_SOFT_START;
	CMD_CXCV_ZERO;
 	set_func_cled_ad();
}

void FPGA_Led_Ctrl(void){

	P3k_LED_Str *disp = &P3k_FLed_Disp;
	static UBYTE timeCnt;
	
	//Initail LED ---
		if(disp->complete==F_LED_CONFIG) { //Inital OCP---
			disp->complete = F_LED_EXECUTE;
		} else {
	// LED				
			FPGA_05_statue = (P_Sense|Acquire_Cont|Set_Protection_Ref_Adjust_ON|Set_Cx_Mode|(UTILITY.LOAD_CTL&0x01));
			Acess_FPGA(FPGA_On_Off_Reference_Setting,FPGA_05_statue);
		}				
}
#endif

#define SR_StepToCountRatio				200
#define SR_StepToCountRatio_CR			13

void FPGA_Normal_Ctrl(void) {	/* FPGA Control Function */
	unsigned short  VM_Range = 0,Circuit_SW0 = 0,Circuit_SW1 = 0;
	double Cal_Gain,Cal_Offset;
	UWORD Dyna_LEVEL1 = 0;
	UWORD Dyna_LEVEL2 = 0;
	UWORD Dyna_T1_RANGE = 0;
	UWORD Dyna_T2_RANGE = 0;
	UWORD SR1_Speed_flag = 0;//Bit5;
	UWORD Dyna_SRUP = 0;
	UWORD Dyna_SRDN = 0;
	UWORD Dyna_T1 = 0;
	UWORD Dyna_T2 = 0;
	UWORD Function_Mode = 0;
	UWORD Voltage_H_Temp,Voltage_L_Temp;
	UWORD FPGA_SetValue_H,FPGA_SetValue_L;
	
	UWORD Max_V_DA,Max_V_Step;
	
	UWORD SettingValue=0;
	UWORD Response_Setting = 0;

	static unsigned char loadoff_count = 0;
	static UWORD FPGA_IS_OS_Ref_callback = 0;
	static UWORD static_DA = 0;
	static char RecLoadStatus1 = 0;
	static char RecLoadStatus2 = 1;	
	
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Parallel_Str *Parallel_Ptr = &P3k_Chan_Data.CONF.Para_Data;

	if(Data_tmp->VRange)	VM_Range = 0;
	else				VM_Range = VM_L_Range;

	switch(Data_tmp->CURRMODE) {
	default:
		Debug_printf("FPGA_Ctrl_Cal_Data_Error\n");
	case CC_MODE:
		Cal_Gain	= p3k_Cal_data.CC_Data[Data_tmp->IRange].Cal_Value_Gain;
		Cal_Offset	= p3k_Cal_data.CC_Data[Data_tmp->IRange].Cal_Value_Offset;
		SettingValue = p3k_Cal_data.CC_offseAdj[Data_tmp->IRange];
		break;
	case CR_MODE:
		Cal_Gain	= p3k_Cal_data.CR_Data[Data_tmp->IRange].Cal_Value_Gain;
		Cal_Offset	= p3k_Cal_data.CR_Data[Data_tmp->IRange].Cal_Value_Offset;
		SettingValue = p3k_Cal_data.CR_offseAdj[Data_tmp->IRange];
		break;
	case CV_MODE:
		Cal_Gain	= p3k_Cal_data.CV_Data[Data_tmp->VRange].Cal_Value_Gain;
		Cal_Offset	= p3k_Cal_data.CV_Data[Data_tmp->VRange].Cal_Value_Offset;
		SettingValue = p3k_Cal_data.CV_offseAdj[1];
		break;
	case CP_MODE:
		Cal_Gain	= p3k_Cal_data.CP_Data[Data_tmp->IRange].Cal_Value_Gain;
		Cal_Offset	= p3k_Cal_data.CP_Data[Data_tmp->IRange].Cal_Value_Offset;
		SettingValue = p3k_Cal_data.CP_offseAdj[Data_tmp->IRange];
		break;
	}

	if((Data_tmp->CONF.Ext_Setting.Control)&&(Data_tmp->CURRMODE==CC_MODE)) {
		if(Data_tmp->CONF.Ext_Setting.Control==1)
			SettingValue = p3k_Cal_data.Ext_V_offseAdj[Data_tmp->IRange];
		else
			SettingValue = p3k_Cal_data.Ext_R_offseAdj[Data_tmp->IRange];
	}
	Response_Setting = get_response(Data_tmp->CURRMODE);

	if((SettingValue != FPGA_IS_OS_Ref_callback)||(SettingValue !=FPGA_W[153])) {
		Acess_FPGA(FPGA_IS_OS_Ref, SettingValue);
		FPGA_IS_OS_Ref_callback = SettingValue;
	}

	if(Data_tmp->CONF.Ext_Setting.Control) {
		Circuit_SW0 = E_Circuit_Switch_Control[(Data_tmp->CURRMODE*6) + (Data_tmp->IRange*2) + 0];
		Circuit_SW1 = E_Circuit_Switch_Control[(Data_tmp->CURRMODE*6) + (Data_tmp->IRange*2) + 1];
	} else {
		Circuit_SW0 = I_Circuit_Switch_Control[(Data_tmp->CURRMODE*6) + (Data_tmp->IRange*2) + 0];
		Circuit_SW1 = I_Circuit_Switch_Control[(Data_tmp->CURRMODE*6) + (Data_tmp->IRange*2) + 1];
	}
	//====	Dynatic  =============================================================================
	if(	(CC_MODE==Data_tmp->CURRMODE && Data_tmp->CC.STADYNA)||(CR_MODE==Data_tmp->CURRMODE && Data_tmp->CR.STADYNA)) {
		//if((P3k_Chan_Data.Load_Type)&&(M_num !=P_CC)&&(P3k_Chan_Data.Load_Type!=4))
		if((P3k_Chan_Data.Load_Type)&&(M_num > P_CP)) //Adam_debug
			Function_Mode = Set_Sequence_Mode; // funtion_mode
		else
			Function_Mode = Set_Dynamic_Mode; // load_mode

		switch(Data_tmp->CURRMODE) {
		default:/* CC_MODE */
			Debug_printf("CX_Dyna_Error\n");
		case CC_MODE:
			if(UTILITY.SHORT_CTL) {
				Dyna_LEVEL1	= (ptrMODEL_TYPE->CC)[0+(Data_tmp->IRange*10)+4].Max;
				Dyna_LEVEL2	= (ptrMODEL_TYPE->CC)[1+(Data_tmp->IRange*10)+4].Max;
				Dyna_SRUP = (ptrMODEL_TYPE->CC)[2+(Data_tmp->IRange*10)+4].Max * SR_StepToCountRatio;
				Dyna_SRDN = (ptrMODEL_TYPE->CC)[3+(Data_tmp->IRange*10)+4].Max * SR_StepToCountRatio;
			} else {
				Dyna_LEVEL1	= Data_tmp->CC.DYNA[Data_tmp->IRange].LEVEL1;
				if(Data_tmp->CONF.Dyna_Level)
					Dyna_LEVEL2	= Data_tmp->CC.DYNA[Data_tmp->IRange].LEVEL1 * Data_tmp->CC.DYNA[Data_tmp->IRange].Level_Percent * 0.001;
				else
					Dyna_LEVEL2	= Data_tmp->CC.DYNA[Data_tmp->IRange].LEVEL2;
				Dyna_SRUP = Data_tmp->CC.DYNA[Data_tmp->IRange].SLEWRATEUP * SR_StepToCountRatio;
				Dyna_SRDN = Data_tmp->CC.DYNA[Data_tmp->IRange].SLEWRATEDN * SR_StepToCountRatio;

			}
			Timer_Setting(&Dyna_T1_RANGE, &Dyna_T2_RANGE, &Dyna_T1, &Dyna_T2);
			break;
		case CR_MODE:
			if(UTILITY.SHORT_CTL) {
				Dyna_LEVEL1	= (ptrMODEL_TYPE->CR)[0+(Data_tmp->IRange*10)+4].Max;
				Dyna_LEVEL2	= (ptrMODEL_TYPE->CR)[1+(Data_tmp->IRange*10)+4].Max;
				Dyna_SRUP = (ptrMODEL_TYPE->CR)[2+(Data_tmp->IRange*10)+4].Min * SR_StepToCountRatio;
				Dyna_SRDN = (ptrMODEL_TYPE->CR)[3+(Data_tmp->IRange*10)+4].Min * SR_StepToCountRatio;
			} else {
				Dyna_LEVEL1	= Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL1;
				if(Data_tmp->CONF.Dyna_Level)
					Dyna_LEVEL2	= Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL1 * Data_tmp->CR.DYNA[Data_tmp->IRange].Level_Percent * 0.001;
				else
					Dyna_LEVEL2	= Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL2;
				Dyna_SRUP = Data_tmp->CR.DYNA[Data_tmp->IRange].SLEWRATEUP * SR_StepToCountRatio;
				Dyna_SRDN = Data_tmp->CR.DYNA[Data_tmp->IRange].SLEWRATEDN * SR_StepToCountRatio;				
			}
			SR1_Speed_flag = Bit5;
			if(Data_tmp->IRange==0) {
				Dyna_SRUP =Dyna_SRUP/10;
				Dyna_SRDN =Dyna_SRDN/10;
			}

			Timer_Setting(&Dyna_T1_RANGE, &Dyna_T2_RANGE, &Dyna_T1, &Dyna_T2);
			break;

		}

		Acess_FPGA(FPGA_H_Circuit_Switch_Control_0, Circuit_SW0 |VM_Range);
		Acess_FPGA(FPGA_L_Circuit_Switch_Control_0, Circuit_SW0 |VM_Range);
		if(Data_tmp->CONF.Para_Data.TrigOut)	SettingValue = (TrigOut_ON | SR1_Speed_flag);
		else								SettingValue = SR1_Speed_flag;

		if(Dyna_T1_RANGE)	Acess_FPGA(FPGA_H_Circuit_Switch_Control_1, Circuit_SW1 |Response_Setting|Time_Unit_1mS |SettingValue );
		else				Acess_FPGA(FPGA_H_Circuit_Switch_Control_1, Circuit_SW1 |Response_Setting|Time_Unit_1uS |SettingValue );
		if(Dyna_T2_RANGE)	Acess_FPGA(FPGA_L_Circuit_Switch_Control_1, Circuit_SW1 |Response_Setting|Time_Unit_1mS |SettingValue );
		else				Acess_FPGA(FPGA_L_Circuit_Switch_Control_1, Circuit_SW1 |Response_Setting|Time_Unit_1uS |SettingValue );
		Acess_FPGA(Cx_CV_Response,(Response_Setting&0x10)>>4);
		if(Dyna_LEVEL1 < Dyna_LEVEL2) {
			Acess_FPGA(FPGA_H_Level_Slew_Rate, Dyna_SRDN);
			Acess_FPGA(FPGA_L_Level_Slew_Rate, Dyna_SRUP);
		} else {
			Acess_FPGA(FPGA_H_Level_Slew_Rate, Dyna_SRUP);
			Acess_FPGA(FPGA_L_Level_Slew_Rate, Dyna_SRDN);
		}
		FPGA_SetValue_H = Step_To_CNT(Dyna_LEVEL1,Cal_Gain,Cal_Offset);
		FPGA_SetValue_L = Step_To_CNT(Dyna_LEVEL2,Cal_Gain,Cal_Offset);

		Acess_FPGA(FPGA_H_T1_Duration, Dyna_T1);
		Acess_FPGA(FPGA_L_T2_Duration, Dyna_T2);
		Acess_FPGA(FPGA_H_Level_Setting, FPGA_SetValue_H);
		Acess_FPGA(FPGA_L_Level_Setting, FPGA_SetValue_L);
		//====	Static  =============================================================================
	} else {
		//if((P3k_Chan_Data.Load_Type)&&(M_num !=P_CC)&&(P3k_Chan_Data.Load_Type!=4))
		if((P3k_Chan_Data.Load_Type)&&(M_num > P_CP)) //Adam_debug
			Function_Mode = Set_Sequence_Mode; // funtion_mode
		else
			Function_Mode = Set_Cx_Mode;

		switch(Data_tmp->CURRMODE) {
		default:/*CC_MODE:*/
			Debug_printf("FPGA_Ctrl_Static_Error\n");
		case CC_MODE:
			if(UTILITY.SHORT_CTL)
				Dyna_LEVEL1 = (ptrMODEL_TYPE->CC)[0+(Data_tmp->IRange*10)].Max;
			else {
				if(Data_tmp->CC.ABSELECT==B_Value)
					Dyna_LEVEL1 = Data_tmp->CC.STA[Data_tmp->IRange].VALUE2;
				else {
					if((NSeq_Load==P3k_Chan_Data.Load_Type)||(FSeq_Load==P3k_Chan_Data.Load_Type ))
						Dyna_LEVEL1  = Prog_Seq_Data.FPGA_Seq_Data[1024].Level_Step;
					else
						Dyna_LEVEL1 = Data_tmp->CC.STA[Data_tmp->IRange].VALUE1;
				}
			}
			Dyna_SRUP = Data_tmp->CC.STA[Data_tmp->IRange].SLEWRATEUP * SR_StepToCountRatio;
			break;
		case CR_MODE:
			if(UTILITY.SHORT_CTL)
				Dyna_LEVEL1 =  (ptrMODEL_TYPE->CR)[0+(Data_tmp->IRange*10)].Max;
			else {
				if(Data_tmp->CR.ABSELECT==B_Value)
					Dyna_LEVEL1 = Data_tmp->CR.STA[Data_tmp->IRange].VALUE2;
				else {
					if((NSeq_Load==P3k_Chan_Data.Load_Type)||(FSeq_Load==P3k_Chan_Data.Load_Type ))
						Dyna_LEVEL1  = Prog_Seq_Data.FPGA_Seq_Data[1024].Level_Step;
					else
						Dyna_LEVEL1 = Data_tmp->CR.STA[Data_tmp->IRange].VALUE1;
				}
			}
			Dyna_SRUP = Data_tmp->CR.STA[Data_tmp->IRange].SLEWRATEUP * SR_StepToCountRatio;
			SR1_Speed_flag=Bit5;
			if(Data_tmp->IRange==0) {
				Dyna_SRUP =Dyna_SRUP/10;;
			}
			break;
		case CV_MODE:
			if(UTILITY.SHORT_CTL)
				Dyna_LEVEL1 = (ptrMODEL_TYPE->CV)[0+(Data_tmp->VRange*3)].Min;
			else {
				if(Data_tmp->CV.ABSELECT==B_Value)
					Dyna_LEVEL1 = Data_tmp->CV.STA[Data_tmp->VRange].VALUE2;
				else {
					if((NSeq_Load==P3k_Chan_Data.Load_Type)||(FSeq_Load==P3k_Chan_Data.Load_Type ))
						Dyna_LEVEL1  = Prog_Seq_Data.FPGA_Seq_Data[1024].Level_Step;
					else
						Dyna_LEVEL1 = Data_tmp->CV.STA[Data_tmp->VRange].VALUE1;
				}
			}
			Dyna_SRUP = 7000;
			break;
		case CP_MODE:
			if(UTILITY.SHORT_CTL)
				Dyna_LEVEL1 = (ptrMODEL_TYPE->CP)[0+(Data_tmp->IRange*10)].Max;
			else {
				if(Data_tmp->CP.ABSELECT==B_Value)
					Dyna_LEVEL1 = Data_tmp->CP.STA[Data_tmp->IRange].VALUE2;
				else {
					if((NSeq_Load==P3k_Chan_Data.Load_Type)||(FSeq_Load==P3k_Chan_Data.Load_Type ))
						Dyna_LEVEL1  = Prog_Seq_Data.FPGA_Seq_Data[1024].Level_Step;
					else
						Dyna_LEVEL1 = Data_tmp->CP.STA[Data_tmp->IRange].VALUE1;
				}
			}
			Dyna_SRUP = CP_SR_CNT/10;
			break;
		}
		FPGA_SetValue_H = Step_To_CNT(Dyna_LEVEL1,Cal_Gain,Cal_Offset);
		Acess_FPGA(FPGA_H_Circuit_Switch_Control_0, Circuit_SW0 |VM_Range);
#if 0
		if(Data_tmp->CONF.Ext_Setting.MultilPara!=2)SettingValue = TrigOut_ON;
		else 										SettingValue = 0;
#else

		SettingValue = 0;
		if(static_DA != FPGA_SetValue_H) {
			SettingValue = TrigOut_ON;
			static_DA = FPGA_SetValue_H;
		}
		if(RecLoadStatus1 != RecLoadStatus2) {
			if(UTILITY.LOAD_CTL) {
				SettingValue = TrigOut_ON;
				static_DA = 0;
			}
			RecLoadStatus1 = RecLoadStatus2;
		}
		if((Data_tmp->CONF.Para_Data.TrigOut)&&(Data_tmp->CONF.Para_Data.TrigIN))
			SettingValue = TrigOut_ON;

#endif
		Acess_FPGA(FPGA_H_Circuit_Switch_Control_1, Circuit_SW1 |Response_Setting |SettingValue|SR1_Speed_flag);

		Acess_FPGA(Cx_CV_Response,(Response_Setting&0x10)>>4);

		Acess_FPGA(FPGA_H_Level_Slew_Rate, Dyna_SRUP);

		if(Data_tmp->CONF.Ext_Setting.Control) {
#if 1
			FPGA_SetValue_H = get_external_cotrol_singnal();		
#else
			if(Data_tmp->CONF.Ext_Setting.Control==Ext_Setting_V)
				FPGA_SetValue_H	= p3k_Cal_data.Ext_V_CC[Data_tmp->IRange];
			else
				FPGA_SetValue_H	= p3k_Cal_data.Ext_R_CC[Data_tmp->IRange];
#endif
		}

		if(UTILITY.LOAD_CTL||UTILITY.SHORT_CTL) {
			loadoff_count =15; //150msec //21//200msec
			if(Compensation_Flag)
				Acess_FPGA(FPGA_H_Level_Setting, New_Set_Count_To_FPGA);
			else
				Acess_FPGA(FPGA_H_Level_Setting, FPGA_SetValue_H);
		} else if((Data_tmp->CURRMODE<=CR_MODE)||(Data_tmp->CURRMODE==CP_MODE)) {
			if(loadoff_count) {
				if(loadoff_count==15)static_DA = 0;
				Acess_FPGA(FPGA_H_Level_Setting, 0);
				loadoff_count--;
				if(PassLoad0ffSW_flag==0)
					return;
				PassLoad0ffSW_flag=0;
			}
		} else if(Data_tmp->CURRMODE ==CV_MODE) {
			if(loadoff_count) {
				Max_V_Step =(ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].Max;//;
				Max_V_DA = Step_To_CNT(Max_V_Step,Cal_Gain,Cal_Offset);
				Acess_FPGA(FPGA_H_Level_Setting, Max_V_DA);
				loadoff_count--;
				if(PassLoad0ffSW_flag==0)
					return;
				PassLoad0ffSW_flag=0;
			}
		}
	}
	/*=== end  Static / Dynatic end ===================================================================*/
	if( (Data_tmp->CURRMODE==CV_MODE)||(Data_tmp->CONF.CV_Func_En==Switch_OFF)||UTILITY.SHORT_CTL ) {
		Acess_FPGA(Cx_CV_H_Value, 0);
		Acess_FPGA(Cx_CV_L_Value, 0);
		Acess_FPGA(Cx_CV_H_Step,  0);
		Acess_FPGA(Cx_CV_L_Step,  0);
	} else {
		if(Data_tmp->CV.STA[1].VALUE1<10)	Voltage_H_Temp = 10;
		else								Voltage_H_Temp = Data_tmp->CV.STA[1].VALUE1;
		if(Data_tmp->CV.STA[0].VALUE1<10)	Voltage_L_Temp = 10;
		else								Voltage_L_Temp = Data_tmp->CV.STA[0].VALUE1;

		Acess_FPGA(Cx_CV_H_Value, Step_To_CNT(Voltage_H_Temp,p3k_Cal_data.Protection[1].CxCV_Gain,p3k_Cal_data.Protection[1].CxCV_Offset));
		Acess_FPGA(Cx_CV_L_Value, Step_To_CNT(Voltage_L_Temp,p3k_Cal_data.Protection[0].CxCV_Gain,p3k_Cal_data.Protection[0].CxCV_Offset));
		if(Model_Number==MODEL3031E){
			Voltage_H_Temp = Voltage_H_Temp/MEASURE_GAIN_3031;
			Voltage_L_Temp = Voltage_L_Temp/MEASURE_GAIN_3031;
		}else{	
			Voltage_H_Temp = Voltage_H_Temp/MEASURE_GAIN_3032;
			Voltage_L_Temp = Voltage_L_Temp/MEASURE_GAIN_3032;
		}
		Acess_FPGA(Cx_CV_H_Step, Voltage_H_Temp);
		Acess_FPGA(Cx_CV_L_Step, Voltage_L_Temp);
	}
	if(Data_tmp->CONF.Para_Data.TrigIN==1)	SettingValue = Set_Trigger_Input;
	else									SettingValue = 0;
	if(((Data_tmp->CONF.Para_Data.TrigOut==1))&&(FPGA05_Writ_flag))SettingValue |= Set_Trigger_Input;//(Set_Wait_ON+Set_Trigger_Input);
	if(UTILITY.LOAD_CTL||UTILITY.SHORT_CTL) {
		FPGA_05_statue = (P_Sense | Acquire_Cont |SettingValue|Set_Protection_Ref_Adjust_ON |Function_Mode |Set_Load_ON );
		RecLoadStatus2 = 1;
	} else {
		FPGA_05_statue= ( P_Sense | Acquire_Cont |SettingValue|Set_Protection_Ref_Adjust_ON |Function_Mode |Set_Load_OFF);
		RecLoadStatus2 = 0;
	}
	Acess_FPGA(FPGA_On_Off_Reference_Setting,FPGA_05_statue);
}
void ring_function_complete (void){
#if Enable_Ring_Count
	last_menu = 0xFF;
	if(UTILITY.Master_Alarm_Tone){
		SEQ_Tone_Count = P3k_Disp_Data.PROT.SEQ_Tone_len; //601;
		Complete_Count = 800;//Alarm_Count = 250;
	}
#endif
}
// ================================================================
#if Enable_OCP_function
#if 1
void FPGA_OCP_OPP_Ctrl(void) {	
	static OCP_OPP_RUN_Str s;
	s.done = 0;
	P3k_OCP_OPP_Str *disp;
	if(OCP_Load==P3k_Chan_Data.Load_Type){
		disp = &P3K_OCP_Disp;
	}else{
#if Enable_OPP_function		
		disp = &P3K_OPP_Disp;
#endif		
	}
		

//Initail OCP ---
	if(disp->Complete==F_OCP_OPP_CONFIG) { //Inital OCP---
		disp->Complete = F_OCP_OPP_LOOKFOR;
		ocp_opp_initial(&s);	
	}
	if(disp->Complete==F_OCP_OPP_LOOKFOR) { //looking for OCP---
		s.timeCnt++;
		if((s.timeCnt%5)==1)DataRedrawFlag |= PARA_CHANGE;
		ocp_opp_set_da(&s);
		ocp_opp_history(s.done);	
		ocp_opp_trig_volt(&s);	
	}
// End OCP
	if(disp->Complete>=F_OCP_OPP_COMPLETE) {	// 2:Complete, 3:Search Fail, 4: Config Error
		s.timeCnt++;
		if((s.timeCnt%8)==1)DataRedrawFlag |= PARA_CHANGE;
		FPGA_05_statue = (P_Sense|Acquire_Cont|Set_Protection_Ref_Adjust_ON|Set_Cx_Mode|(UTILITY.LOAD_CTL&0x01));
		if(disp->Complete==F_OCP_OPP_CONFIG_ERR)FPGA_05_statue &= 0xFFFE; 
		Acess_FPGA(FPGA_On_Off_Reference_Setting,FPGA_05_statue);
	}
}

void ocp_opp_config(UBYTE IRang){
	UBYTE SRH;
	UWORD Dyna_SRUP = 0;
	unsigned short	Circuit_SW0 = 0,Circuit_SW1 = 0;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UWORD All_Prot_Setteng = 0;

	All_Prot_Setteng |= Set_Von_Latch_ON;	
#if 1 //double check 
	if(Data_tmp->PROT.OPP_SET)
		All_Prot_Setteng |= Set_OPP_Limit;
	else {
		All_Prot_Setteng |= Set_OPP_Load_OFF;
		Acess_FPGA(FPGA_Control, Clear_OPP_Latch);
	}

	if(Data_tmp->PROT.OCP_SET)
		All_Prot_Setteng |= Set_OCP_Limit;
	else {
		All_Prot_Setteng |= Set_OCP_Load_OFF;
		Acess_FPGA(FPGA_Control, Clear_OCP_Latch);
	}
#endif
	P3k_Chan_Data.IRange = P3k_Disp_Data.IRange = IRang;
	P3k_Chan_Data.VRange = P3k_Disp_Data.VRange = VRange_High;
	
	if(OCP_Load==P3k_Chan_Data.Load_Type){
		Acess_FPGA(FPGA_IS_OS_Ref, p3k_Cal_data.CC_offseAdj[IRang]);
		Circuit_SW0 = I_Circuit_Switch_Control[IRang*2];
		Circuit_SW1 = I_Circuit_Switch_Control[(IRang*2) + 1];
	}else{
		Acess_FPGA(FPGA_IS_OS_Ref, p3k_Cal_data.CP_offseAdj[IRang]);
		Circuit_SW0 = I_Circuit_Switch_Control[(IRang*2)+18];
		Circuit_SW1 = I_Circuit_Switch_Control[(IRang*2)+19];
	}	
	SRH = 2;//Data_tmp->CC.STA[IRang].SLEWRATEUP_RANGE;
	Acess_FPGA(FPGA_H_Circuit_Switch_Control_0, Circuit_SW0 );	///
	Acess_FPGA(FPGA_H_Circuit_Switch_Control_1, Circuit_SW1 );///
	Dyna_SRUP = 250;//Data_tmp->CC.STA[IRang].SLEWRATEUP * SR_StepToCountRatio;
	Acess_FPGA(FPGA_H_Level_Slew_Rate, Dyna_SRUP);///
	Acess_FPGA(FPGA_On_Off_Latch_Setting, All_Prot_Setteng);
	CMD_CXCV_ZERO;
	CLOSE_SOFT_START;
				
}

void ocp_opp_initial (OCP_OPP_RUN_Str* s){
	P3k_OCP_OPP_Str *disp;
	if(OCP_Load==P3k_Chan_Data.Load_Type){
		disp = &P3K_OCP_Disp;
	}else{
#if Enable_OPP_function			
		disp = &P3K_OPP_Disp;
#endif		
	}
	
	UBYTE tmp;
	UBYTE IRang;	
	double VoltRes = (ptrMODEL_TYPE->CV)[3].Resolution;
	s->VoltReady = 0;
	tmp = disp->CurrTemp;
	s->TempDA = s->startCW = disp->Seq[tmp].StartCurrWatt;
	disp->CurrWattDA = disp->Seq[tmp].StartCurrWatt;	
	s->endCW = disp->Seq[tmp].EndCurrWatt;
	s->stepCW = disp->Seq[tmp].StepCurrWatt;
	s->stepT = disp->Seq[tmp].StepTime;
	s->DelayT = disp->Seq[tmp].DelayTime;
	s->TrigV = disp->Seq[tmp].TrigVolt*VoltRes;
	s->lastC = disp->Seq[tmp].LastCurrWatt;		
	s->timeCnt = 0;
	s->VoltReady = 0;		
	IRang = disp->Seq[tmp].Range;
	
	if(OCP_Load==P3k_Chan_Data.Load_Type){
		s->Cal_Gain	= p3k_Cal_data.CC_Data[IRang].Cal_Value_Gain;
		s->Cal_Offset = p3k_Cal_data.CC_Data[IRang].Cal_Value_Offset;			
	}else{
		s->Cal_Gain	= p3k_Cal_data.CP_Data[IRang].Cal_Value_Gain;
		s->Cal_Offset = p3k_Cal_data.CP_Data[IRang].Cal_Value_Offset;
	}
	ocp_opp_config(IRang);
	s->done = 1;
	
}

void ocp_opp_history(UBYTE done){
	char i;
	P3k_OCP_OPP_Str *disp;
	if(OCP_Load==P3k_Chan_Data.Load_Type){
		disp = &P3K_OCP_Disp;
	}else{
#if Enable_OPP_function			
		disp = &P3K_OPP_Disp;
#endif		
	}

	disp->GetTrigV = (p3k_Measure_Data.Real_Volt+0.005)/0.01;

	if(done) {
		for(i=3; i>0; i--) {
			disp->RecCurr[i]=disp->RecCurr[i-1];
			disp->RecVolt[i]=disp->RecVolt[i-1];
		}
		disp->RecVolt[0]=disp->GetTrigV;
		disp->RecCurr[0]=disp->CurrWattDA;
	} else {
		disp->RecVolt[0]=disp->GetTrigV;
	}
}
void ocp_opp_set_da(OCP_OPP_RUN_Str* s){
	UWORD LEVEL1 ;
	UWORD null = 0;	
	UWORD FPGA_SetValue_H;
	P3k_OCP_OPP_Str *disp;
	if(OCP_Load==P3k_Chan_Data.Load_Type){
		disp = &P3K_OCP_Disp;
	}else{
#if Enable_OPP_function			
		disp = &P3K_OPP_Disp;
#endif		
	}	
	if(s->timeCnt>s->stepT) {
		s->timeCnt = 0;
		if(s->TempDA==s->endCW) {
			disp->Complete=F_OCP_OPP_TIMEOUT; //Search Fail---
			s->TempDA = s->lastC;
			DataRedrawFlag |= PARA_CHANGE;
		} else {
			s->TempDA += s->stepCW;
			if(s->TempDA>s->endCW)	s->TempDA = s->endCW;
			disp->CurrWattDA = s->TempDA;
			s->done = 1;
		}
	}
	LEVEL1 = s->TempDA;
	if(OCP_Load==P3k_Chan_Data.Load_Type)
		Minimum_Current(CC_MODE,&LEVEL1,&null);
	else
		Minimum_Current(CP_MODE,&LEVEL1,&null);
	FPGA_SetValue_H = Step_To_CNT(LEVEL1,s->Cal_Gain,s->Cal_Offset);
	Acess_FPGA(FPGA_H_Level_Setting, FPGA_SetValue_H);
	FPGA_05_statue = (P_Sense|Acquire_Cont|Set_Protection_Ref_Adjust_ON|Set_Cx_Mode|(UTILITY.LOAD_CTL&0x01));
	Acess_FPGA(FPGA_On_Off_Reference_Setting,FPGA_05_statue);
}

void ocp_opp_trig_volt(OCP_OPP_RUN_Str* s){
	UWORD LEVEL1; 
	UWORD FPGA_SetValue_H;
	P3k_OCP_OPP_Str *disp;
	float measure_gain;
	if(Model_Number==MODEL3031E)	measure_gain = MEASURE_GAIN_3031;
	else 						measure_gain = MEASURE_GAIN_3032;
	if(OCP_Load==P3k_Chan_Data.Load_Type){
		disp = &P3K_OCP_Disp;
	}else{
#if Enable_OPP_function			
		disp = &P3K_OPP_Disp;
#endif		
	}
	if(s->timeCnt>s->DelayT) {
		p3k_Measure_Data.Real_Volt	= (Acess_FPGA(FPGA_V_Sense,NULL)*(ptrMODEL_TYPE->CV)[3].Resolution)*measure_gain;
		if(p3k_Measure_Data.Real_Volt < s->TrigV) 		

		{
			if(s->VoltReady) {
				disp->Complete = F_OCP_OPP_COMPLETE;//Complete---
				ring_function_complete();
				disp->UpdataFlag = 2;
				LEVEL1 = s->lastC;
				FPGA_SetValue_H = Step_To_CNT(LEVEL1,s->Cal_Gain,s->Cal_Offset);
				Acess_FPGA(FPGA_H_Level_Setting, FPGA_SetValue_H);
			} else {
				disp->Complete=F_OCP_OPP_CONFIG_ERR; //Start Status Volt < trigVolt
				DataRedrawFlag |= PARA_CHANGE;
			}
		} else {
			s->VoltReady = 1;
		}
	}else{
		if(p3k_Measure_Data.VOLT < s->TrigV)
			if(s->VoltReady==0)	disp->Complete=F_OCP_OPP_CONFIG_ERR; //Start Status Volt < trigVolt				
	}	
}

#else
void FPGA_OCP_OPP_Ctrl(void) {
	unsigned short	Circuit_SW0 = 0,Circuit_SW1 = 0;
	UBYTE SRH,i;
	static double Cal_Gain,Cal_Offset;
	UWORD LEVEL1 = 0;
	UWORD null = 0;
	UWORD Dyna_SRUP = 0;
	UWORD FPGA_SetValue_H;
	UBYTE IRang;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UBYTE da1;
	static ULONG TempDA;
	static UWORD timeCnt;
	static UWORD startC,endC,stepC,stepT,DelayT,lastC;
	double VoltRes = (ptrMODEL_TYPE->CV)[3].Resolution;
	static double TrigV;
	char done = 0;
	static UBYTE VoltReady = 0;
	float measure_gain;
	if(Model_Number==MODEL3031E)	measure_gain = MEASURE_GAIN_3031;
	else 						measure_gain = MEASURE_GAIN_3032;
//Initail OCP ---
	if(P3K_OCP_Disp.Complete==0) { //Inital OCP---
		P3K_OCP_Disp.Complete = 1;

		da1 = P3K_OCP_Disp.CurrTemp;
		TempDA = startC = P3K_OCP_Disp.Seq[da1].StartCurrWatt;
		endC = P3K_OCP_Disp.Seq[da1].EndCurrWatt;
		stepC = P3K_OCP_Disp.Seq[da1].StepCurrWatt;
		stepT = P3K_OCP_Disp.Seq[da1].StepTime;
		DelayT = P3K_OCP_Disp.Seq[da1].DelayTime;
		
		TrigV = P3K_OCP_Disp.Seq[da1].TrigVolt*VoltRes;
		lastC = P3K_OCP_Disp.Seq[da1].LastCurrWatt;
		timeCnt = 0;
		VoltReady = 0;
Acess_FPGA(FPGA_Control,			Clear_Write_Address);

		IRang = P3K_OCP_Disp.Seq[da1].Range;
		P3k_Chan_Data.IRange = P3k_Disp_Data.IRange = IRang;
		P3k_Chan_Data.VRange = P3k_Disp_Data.VRange = VRange_High;
		Cal_Gain	= p3k_Cal_data.CC_Data[IRang].Cal_Value_Gain;
		Cal_Offset	= p3k_Cal_data.CC_Data[IRang].Cal_Value_Offset;
		Acess_FPGA(FPGA_IS_OS_Ref, p3k_Cal_data.CC_offseAdj[IRang]);
		Circuit_SW0 = I_Circuit_Switch_Control[IRang*2];
		Circuit_SW1 = I_Circuit_Switch_Control[(IRang*2) + 1];
		SRH = 2;//Data_tmp->CC.STA[IRang].SLEWRATEUP_RANGE;
		Acess_FPGA(FPGA_H_Circuit_Switch_Control_0, Circuit_SW0 );	///
		
		Dyna_SRUP = 250;//Data_tmp->CC.STA[IRang].SLEWRATEUP * SR_StepToCountRatio;
		Acess_FPGA(FPGA_H_Level_Slew_Rate, Dyna_SRUP);///
		Acess_FPGA(Cx_CV_H_Value, 0);///
		Acess_FPGA(Cx_CV_L_Value, 0);///
		Acess_FPGA(Cx_CV_H_Step,  0);///
		Acess_FPGA(Cx_CV_L_Step,  0);///
	}


	if(P3K_OCP_Disp.Complete==1) { //looking for OCP---
		timeCnt++;
		if((timeCnt%5)==1)DataRedrawFlag |= PARA_CHANGE;
//Set DA value
		if(timeCnt>=stepT) {
			timeCnt = 0;
			if(TempDA==endC) {
				P3K_OCP_Disp.Complete=3; //Search Fail---
				TempDA = lastC;
				DataRedrawFlag |= PARA_CHANGE;
			} else {
				TempDA += stepC;
				if(TempDA>endC)	TempDA = endC;
				P3K_OCP_Disp.CurrWattDA = TempDA;
				done = 1;
			}
		}
		LEVEL1 = TempDA;
		Minimum_Current(CC_MODE,&LEVEL1,&null);
		FPGA_SetValue_H = Step_To_CNT(LEVEL1,Cal_Gain,Cal_Offset);
		Acess_FPGA(FPGA_H_Level_Setting, FPGA_SetValue_H);
		FPGA_05_statue = (P_Sense|Acquire_Cont|Set_Protection_Ref_Adjust_ON|Set_Cx_Mode|(UTILITY.LOAD_CTL&0x01));
		Acess_FPGA(FPGA_On_Off_Reference_Setting,FPGA_05_statue);

//Recoder History
		p3k_Measure_Data.Real_Volt	= (Acess_FPGA(FPGA_V_Sense,NULL)*(ptrMODEL_TYPE->CV)[3].Resolution)*measure_gain;

		P3K_OCP_Disp.GetTrigV = (p3k_Measure_Data.Real_Volt+0.005)/0.01;//Real_Volt
		///P3K_OCP_Disp.GetTrigV = (p3k_Measure_Data.VOLT+0.005)/0.01;
		if(done) {
			for(i=3; i>0; i--) {
				P3K_OCP_Disp.RecCurr[i]=P3K_OCP_Disp.RecCurr[i-1];
				P3K_OCP_Disp.RecVolt[i]=P3K_OCP_Disp.RecVolt[i-1];
			}
			P3K_OCP_Disp.RecVolt[0]=P3K_OCP_Disp.GetTrigV;
			P3K_OCP_Disp.RecCurr[0]=P3K_OCP_Disp.CurrWattDA;
		} else {
			P3K_OCP_Disp.RecVolt[0]=P3K_OCP_Disp.GetTrigV;
		}
//Trig Volt
		if(timeCnt>=DelayT) {
			///if(p3k_Measure_Data.VOLT < TrigV) {
			if(p3k_Measure_Data.Real_Volt < TrigV) {
				if(VoltReady) {
					P3K_OCP_Disp.Complete = 2;//Complete---
					ring_function_complete();
					P3K_OCP_Disp.UpdataFlag = 2;
					LEVEL1 = lastC;
					FPGA_SetValue_H = Step_To_CNT(LEVEL1,Cal_Gain,Cal_Offset);
					Acess_FPGA(FPGA_H_Level_Setting, FPGA_SetValue_H);
				} else {
					P3K_OCP_Disp.Complete=4; //Start Status Volt < trigVolt
					DataRedrawFlag |= PARA_CHANGE;
				}
			} else {
				VoltReady = 1;
			}
		}
	}
// End OCP
	if(P3K_OCP_Disp.Complete>=2) { 		// 2:Complete, 3:Search Fail, 4: Config Error
		timeCnt++;
		if((timeCnt%8)==1)DataRedrawFlag |= PARA_CHANGE;
		FPGA_05_statue = (P_Sense|Acquire_Cont|Set_Protection_Ref_Adjust_ON|Set_Cx_Mode|(UTILITY.LOAD_CTL&0x01));
		if(P3K_OCP_Disp.Complete==4)FPGA_05_statue &= 0xFFFE; 
		Acess_FPGA(FPGA_On_Off_Reference_Setting,FPGA_05_statue);
	}
}
#endif
#endif

#if Enable_Battery_Discharge  //====================================================

void FPGA_BATT_Ctrl (void){
	static char sLoadFlag,sRedraw;
	sRedraw++;
	if(sRedraw>20){
		DataRedrawFlag |= PARA_CHANGE;
		sRedraw = 0;
	}	
	if(BattDisp.status == BATT_CONFIG){ //load on --> configure
		///battery_config();
		BattDisp.stopStatus = 1;
		sLoadFlag = 1;
		BattDisp.status = BATT_DISCHARE;		
	}else if(BattDisp.status == BATT_DISCHARE){ //load on --> discharge
		BattDisp.stopStatus = battery_calcute();
		
	}else if(BattDisp.status == BATT_COMPLETE){ //dischare complete // load off 
		if(sLoadFlag){
			sLoadFlag = 0;
			DataRedrawFlag |= BG_CLEAR_FLAG+PARA_CHANGE;
			battery_loadoff();
		}
	}
}

void battery_config (void){
	double Cal_Gain,Cal_Offset;
	unsigned short	VM_Range = 0,Circuit_SW0 = 0,Circuit_SW1 = 0;
	UBYTE SRH;	
	UWORD Dyna_LEVEL1 = 0;
	UWORD Dyna_SRUP = 0;	
	UWORD Function_Mode = 0;
	UWORD FPGA_SetValue_H,FPGA_SetValue_L;
	UWORD SettingValue=0;
	UBYTE mode;
	UBYTE vrang;
	UBYTE irang;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Parallel_Str *Parallel_Ptr = &P3k_Chan_Data.CONF.Para_Data;
	Data_tmp->CONF.Count_Time = P3k_Disp_Data.CONF.Count_Time = 1;

	BattDisp.WattHour = 0;
	BattDisp.AmpereHour = 0;
	
	mode = BattDisp.Mode;
	if(mode==CV_MODE)	mode = CP_MODE;
	P3k_Chan_Data.CURRMODE= P3k_Disp_Data.CURRMODE	= mode;
	irang = BattDisp.Range%2;		
	vrang = BattDisp.Range/2;

	P3k_Chan_Data.VRange = P3k_Disp_Data.VRange = vrang;
	P3k_Chan_Data.IRange = P3k_Disp_Data.IRange	= irang;

	if(vrang)		VM_Range = 0;
	else			VM_Range = VM_L_Range;
//Adam_2016_0516	Response_Setting = CC_CR_CP_Response_1_2;

	switch(mode) {	
	case CC_MODE:
		Cal_Gain	= p3k_Cal_data.CC_Data[irang].Cal_Value_Gain;
		Cal_Offset	= p3k_Cal_data.CC_Data[irang].Cal_Value_Offset;
		SettingValue = p3k_Cal_data.CC_offseAdj[irang];
		break;
	case CR_MODE:
		Cal_Gain	= p3k_Cal_data.CR_Data[irang].Cal_Value_Gain;
		Cal_Offset	= p3k_Cal_data.CR_Data[irang].Cal_Value_Offset;
		SettingValue = p3k_Cal_data.CR_offseAdj[irang];
		break;
		
	case CP_MODE:
	default:	
		Cal_Gain	= p3k_Cal_data.CP_Data[irang].Cal_Value_Gain;
		Cal_Offset	= p3k_Cal_data.CP_Data[irang].Cal_Value_Offset;
		SettingValue = p3k_Cal_data.CP_offseAdj[irang];
		break;
	}	
	Acess_FPGA(FPGA_IS_OS_Ref, SettingValue);			
	Circuit_SW0 = I_Circuit_Switch_Control[(mode*6) + (irang*2) + 0];
	Circuit_SW1 = I_Circuit_Switch_Control[(mode*6) + (irang*2) + 1];			
	Function_Mode = Set_Cx_Mode;			
	switch(mode) {	
	case CC_MODE:					
		Dyna_LEVEL1 = BattDisp.Setting; 		
		Dyna_SRUP = BattDisp.SRUP * SR_StepToCountRatio;
		SRH = BattDisp.SRUPRange;		
		break;
	case CR_MODE:				
		Dyna_LEVEL1 = BattDisp.Setting; 			
		Dyna_SRUP = (BattDisp.SRUP * SR_StepToCountRatio)/10;
		SRH = BattDisp.SRUPRange;	
		break;
	case CP_MODE:
	default:/*CC_MODE:*/
		Dyna_LEVEL1 = BattDisp.Setting; 		
//Adam_2016_0516		SRH = CP_SR_Range;
		Dyna_SRUP = CP_SR_CNT;		
		break;
	}
	FPGA_SetValue_H = Step_To_CNT(Dyna_LEVEL1,Cal_Gain,Cal_Offset);			
	Acess_FPGA(FPGA_H_Circuit_Switch_Control_0, Circuit_SW0 |VM_Range);
	Acess_FPGA(FPGA_H_Circuit_Switch_Control_1, Circuit_SW1 |SRH);
	Acess_FPGA(FPGA_H_Level_Slew_Rate, Dyna_SRUP);			
//	if((Parallel_Ptr->Booster_Number)||(Parallel_Ptr->Parallel_Number))
//		Compensation_Parallel_DA(&FPGA_SetValue_H,&FPGA_SetValue_L);
//	else
//Adam_2016_0516		G_Magnification = 1;		
	CMD_CXCV_ZERO;
	Acess_FPGA(FPGA_H_Level_Setting, FPGA_SetValue_H);	
	FPGA_05_statue = (P_Sense | Acquire_Cont |Set_Protection_Ref_Adjust_ON |Function_Mode |Set_Load_ON);
	Acess_FPGA(FPGA_On_Off_Reference_Setting,FPGA_05_statue);
}
#if 0
void Cacute_AH_WH(void){
	static char recodsec = 100;
	ULONG dat;	
	if(p3k_Measure_Data.Sec != recodsec){
		recodsec = p3k_Measure_Data.Sec;
		dat = (ULONG)(p3k_Measure_Data.CURR*1000);//(double)p3k_Measure_Data.CURR/3600; 3600*1000 = 3600 000
		BattDisp.AmpereHour += dat;
		dat = (ULONG)(p3k_Measure_Data.WATT*1000);
		BattDisp.WattHour += dat;
	} 
}
#endif
char is_stop_discharge(void){
	ULONG dat;
	float dat1;
	static char cnt;
	if(BattDisp.StopTime){
		if(p3k_Measure_Data.Hour==BattDisp.StopHour){
			if(p3k_Measure_Data.Min==BattDisp.StopMin){
				if(p3k_Measure_Data.Sec==BattDisp.StopSec){
					BattDisp.status = BATT_COMPLETE;
					return 2;
				}	
			}	
		}
	}
	if(BattDisp.StopCapa){
		dat = BattDisp.StopCapa*36000*8; //3600*1000/100
		if(BattDisp.AmpereHour>dat){
			BattDisp.status = BATT_COMPLETE;
			return 3;
		}
	}
	dat1 = BattDisp.StopValt * 0.01;
	if(p3k_Measure_Data.VOLT < dat1){
		cnt++;
		if(cnt>30){
			BattDisp.status = BATT_COMPLETE;
			cnt = 0;
			return 4;
		}
	}else{
		cnt = 0;
	}
	return 1;
}

char battery_calcute (void){
	char tmp=1;
	if(Compensation_Flag)
		Acess_FPGA_Only(FPGA_H_Level_Setting, New_Set_Count_To_FPGA);
	///Cacute_AH_WH();
	tmp = is_stop_discharge();
	return tmp;
}

void battery_loadoff (void){
	UBYTE SRH;	
	UWORD Dyna_SRDW = 0;		
	switch(BattDisp.Mode) {
	default:/*CC_MODE:*/
		Debug_printf("FPGA_Ctrl_Static_Error\n");
	case CC_MODE:						
		Dyna_SRDW = BattDisp.SRUP * SR_StepToCountRatio;
		SRH = BattDisp.SRUPRange;
//Adam_2016_0516		Acess_FPGA(FPGA_H_Circuit_Switch_Control_1, CC_CR_CP_Response_1_2 |SRH);
		Acess_FPGA(FPGA_H_Level_Slew_Rate, Dyna_SRDW);	
		break;
	case CR_MODE:						
		Dyna_SRDW = (BattDisp.SRUP * SR_StepToCountRatio)/10;
		SRH = BattDisp.SRUPRange;
//Adam_2016_0516		Acess_FPGA(FPGA_H_Circuit_Switch_Control_1, CC_CR_CP_Response_1_2 |SRH);
		Acess_FPGA(FPGA_H_Level_Slew_Rate, Dyna_SRDW);	
		break;
	}
	asm("nop;");asm("nop;");asm("nop;");asm("nop;");
	Acess_FPGA(FPGA_H_Level_Setting, 0);
	OSTimeDly(3);
	FunctionFlag = FUNC_CLEAR;
	UTILITY.LOAD_CTL = Switch_OFF;
	PEL3000_LED_Control(LED_LOAD, Switch_OFF);
	SysRedrawFlag |= PROG_UPDATA;

	if((UTILITY.Master_Alarm_Tone)&&(BattDisp.stopStatus != 5)){
		SEQ_Tone_Count = P3k_Disp_Data.PROT.SEQ_Tone_len; //601;
		Complete_Count = 800;//Alarm_Count = 250;
	}	
	FPGA_05_statue = (P_Sense | Acquire_Cont |Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
	Acess_FPGA(FPGA_On_Off_Reference_Setting,FPGA_05_statue);
}
#endif //==============================================================================

void MenuDecoderAddr(p3k_send_tx_list *data) {
	char dyna[]		= { 0x40, 0x42, 0x50, 0x52, 0x54, 0x56, 0x24};
	char sta[]		= { 0x10, 0x12, 0x20 , 0x24 };
	char dynaspec[]	= { 0x60, 0x62, 0x64 };
	char staspec[]	= { 0x30, 0x32, 0x34 };
	char prot[]		= { 0x10, 0x04, 0x12, 0x04, 0x14, 0x16};
	char other[]	= { 0x22, 0x20, 0x04, 0x03, 0x03, 0x03, 0x30 };
	char mode[]		= { 0x01, 0x02, 0x03 };
	char tmp;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	switch(M_num) {
	case P_CC:
		data->ADDRH = 0x01;
		if( Data_tmp->CC.STADYNA )	data->ADDRL = dyna[DispScrCurrLoc];
		else						data->ADDRL = sta[DispScrCurrLoc];
		break;
	case P_CR:
		data->ADDRH = 0x02;
		if(Data_tmp->CR.STADYNA)		data->ADDRL = dyna[DispScrCurrLoc];
		else						data->ADDRL = sta[DispScrCurrLoc];
		if(DispScrCurrLoc==2)		data->ADDRL = 0x24;
		break;
	case P_CV:
		data->ADDRH = 0x03;
		data->ADDRL = sta[DispCT];
		break;
	case P_CP:
		data->ADDRH = 0x04;
		data->ADDRL = sta[DispScrCurrLoc];
		if(DispScrCurrLoc==2)		data->ADDRL = 0x24;
		break;
	case P_CC_SPEC:
		data->ADDRH = 0x01;
		if(Data_tmp->CC.STADYNA)		data->ADDRL = 0x60;
		else						data->ADDRL = 0x30;
		break;
	case P_CR_SPEC:
		data->ADDRH = 0x02;
		if(Data_tmp->CR.STADYNA)		data->ADDRL = 0x60;
		else						data->ADDRL = 0x30;
		break;
	case P_CV_SPEC:
		data->ADDRH = 0x03;
		data->ADDRL = 0x30;
		break;
	case P_CP_SPEC:
		data->ADDRH = 0x04;
		data->ADDRL = 0x30;
		break;
	case P_CONF_PROT:
		data->ADDRH = 0x00;
		data->ADDRL = prot[DispScrCurrLoc];
		break;
	case P_CONF_OTHER:
		data->ADDRH = 0x00;
		data->ADDRL = other[DispScrCurrLoc];
		break;
	default:
		break;
	}
}

void EncoderTXData(void) {
	static UBYTE count=100;
	switch(TX_LIST.ADDRH) {
	case Machine_Command:
		MachineSetupFun();
		break;
	case 0x01:
		CCModeSetupFun();
		FPGA_Ctrl();
		break;
	case 0x02:
		CRModeSetupFun();
		FPGA_Ctrl();
		break;
	case 0x03:
		CVModeSetupFun();
		FPGA_Ctrl();
		break;
	case 0x04:
		CPModeSetupFun();
		FPGA_Ctrl();
		break;
	case 0x10:
		SeqMemSetupFun();
		break;
	case 0x11:
		SeqPFTimeSetupFun();
		break;
	case 0x20:
		SavePMemFun();
		break;
	case 0x21:
		SaveMemFun();
		break;
	case 0x30:
		RecallPMemFun();
		FPGA_Ctrl();
		break;
	case 0x31:
		RecallMemFun();
		break;
	case 0x40 ... 0x47:
		WriteFlashFun();
		break;
	case 0x51:
		SaveSeqFun();
		break;
	case Para_Ext_Command:
		Para_Ext_Fun();
		break;
	case 0x61:
		SaveSeqFunAll();
		break;
	case Cal_FPGA_Command:
		CalibrationFun();
		break;
	default:
		break;
	}
}

void SendTXData(p3k_send_tx_list *data) {
	TX_LIST = *data;
	EncoderTXData();
}

void Alarm_Process(UBYTE Alarm_Mode,UBYTE Alarm_Action) {
	if(Alarm_Action)
		p3k_Measure_Data.Alarm = Alarm_Mode;
	else {
		if(Alarm_Mode == p3k_Measure_Data.Alarm)
			p3k_Measure_Data.Alarm = No_Alarm;
	}
}
char flag_CPP_OPP;
void Update_Alarm_Status(UWORD FPGA_Status_Data,long Negative_Volt_Value) {
	static char RVP_Count;
	static char change_range_ct;
	static unsigned char para_count;
	static unsigned char rocp_count;
	static char recoder_range;
	unsigned short Al_da=0;
	unsigned char ROCP_flag=0;
	short rvp_value;
	double ResolutionTemp,Max;
	UBYTE Para_s;
	Para_s = Get_Parallel_Parameter(P3k_Chan_Data.IRange);

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	p3k_send_tx_list tx_data;

	if( P3k_Chan_Data.VRange != recoder_range) { //Adam:  when chage range, OVP munt more ten times.
		recoder_range = P3k_Chan_Data.VRange;
		change_range_ct = 10;
	}
	/* Para_Alarm  */ //4 #11
	if(para_count==0) {
		if(checkParaAlarmCount) {
			Alarm_Process(Para_Alarm,Set_Alarm);
			Al_da |= (0x01<<Para_Alarm)>>1;
		} else
			Alarm_Process(Para_Alarm,Clear_Alarm);
	} else {
		para_count--;
	}

	/* UnReg_Alarm  */ //4 #10

#if Enable_mark_short_unReg
	if((FPGA_Status_Data&Broken_Event)&&(RVP_Count==0)&&(UTILITY.SHORT_CTL==0)) {
		Alarm_Process(UnReg_Alarm, Set_Alarm);
		Al_da |= (0x01<<UnReg_Alarm)>>1;
		para_count =200;
	} else {
		Alarm_Process(UnReg_Alarm, Clear_Alarm);
	}
#else
	if((FPGA_Status_Data&Broken_Event)&&(RVP_Count==0)) {
		Alarm_Process(UnReg_Alarm, Set_Alarm);
		Al_da |= (0x01<<UnReg_Alarm)>>1;
		para_count =200;
	} else {
		Alarm_Process(UnReg_Alarm, Clear_Alarm);
	}
#endif
#if Enable_OPPOCP_off
	/* OCP_Alarm  */	 //4 #9

	if(Data_tmp->IRange==0) { //Low_Range
		if( Data_tmp->PROT.OCP[1]>ptrMODEL_TYPE->PROT[0].Max)
			ROCP_flag =1;
		else
			ROCP_flag =0;
	}
	if(FPGA_Status_Data&OCP_Prot_Event) {
		if((P3k_Chan_Data.PROT.OCP_SET==2)||(ROCP_flag)) { //ROCP
			Alarm_Process(OCP_Alarm, Clear_Alarm);
			Alarm_Process(ROCP_Alarm, Set_Alarm);
			Al_da |= (0x01<<ROCP_Alarm)>>1;
		} else { //OCP
			Alarm_Process(OCP_Alarm, Set_Alarm);
			Alarm_Process(ROCP_Alarm, Clear_Alarm);
			Al_da |= (0x01<<OCP_Alarm)>>1;
		}
	} else {
		Alarm_Process(OCP_Alarm, Clear_Alarm);
		Alarm_Process(ROCP_Alarm, Clear_Alarm);
	}
#else
	/* OCP_Alarm  */	 //4 #9

	if(FPGA_Status_Data&OCP_Prot_Event) {
		Alarm_Process(OCP_Alarm, Set_Alarm);
		Al_da |= (0x01<<OCP_Alarm)>>1;
		ROCP_flag =0; //OCP 成立時, 則ROCP不允許成立
	} else {
		Alarm_Process(OCP_Alarm, Clear_Alarm);
		ROCP_flag =0;
	}
#endif
	/* OPP_Alarm  */	//4 #8
	if(FPGA_Status_Data&OPP_Prot_Event) {
		Alarm_Process(OPP_Alarm, Set_Alarm);
		Al_da |= (0x01<<OPP_Alarm)>>1;
	} else {
		Alarm_Process(OPP_Alarm, Clear_Alarm);
		flag_CPP_OPP = 0;
	}

	/* Ext_Alarm  */ //4 #12
	if(Data_tmp->CONF.Ext_Setting.Control) {
		if(Ext_UnReg_Flag && Data_tmp->CONF.Ext_Setting.Control) {
			Alarm_Process(Ext_Alarm,Set_Alarm);
			Al_da |= (0x01<<Ext_Alarm)>>1;
		} else if(!Ext_UnReg_Flag)
			Alarm_Process(Ext_Alarm,Clear_Alarm);
	}//2013.0604
	else {
		Alarm_Process(Ext_Alarm,Clear_Alarm);
	}
	/* FCCP_Alarm  */ //4 #7
	Alarm_Process(FCCP_Alarm, Clear_Alarm);

	/* CCP_Alarm  */	//4 #5
	if(FPGA_Status_Data&CPP_Prot_Event) {
		Alarm_Process(CPP_Alarm, Set_Alarm);
		Al_da |= (0x01<<CPP_Alarm)>>1;
		///flag_CPP_OPP = 1;
	} else
		Alarm_Process(CPP_Alarm, Clear_Alarm);

	/* UVP Alarm */ //4 #4
	if((p3k_Measure_Data.VOLT<(Data_tmp->PROT.UVP_VOLT[Data_tmp->VRange]*ptrMODEL_TYPE->PROT[PROT_UVP_L+Data_tmp->VRange].Resolution))&&(P_CAL_MODE!=M_num)) {
		Alarm_Process(UVP_Alarm,Set_Alarm);
		Al_da |= (0x01<<UVP_Alarm)>>1;
	} else
		Alarm_Process(UVP_Alarm,Clear_Alarm);
	/* OVP Alarm */ //4 #3
	if(change_range_ct==0) {
		if((p3k_Measure_Data.VOLT>(Data_tmp->PROT.OVP_VOLT[Data_tmp->VRange]*ptrMODEL_TYPE->PROT[PROT_OVP_L+Data_tmp->VRange].Resolution))&&(P_CAL_MODE!=M_num)) {
			Alarm_Process(OVP_Alarm,Set_Alarm);
			Al_da |= (0x01<<OVP_Alarm)>>1;
		} else
			Alarm_Process(OVP_Alarm,Clear_Alarm);
	} else {
		if((p3k_Measure_Data.VOLT>(Data_tmp->PROT.OVP_VOLT[Data_tmp->VRange]*ptrMODEL_TYPE->PROT[PROT_OVP_L+Data_tmp->VRange].Resolution))&&(P_CAL_MODE!=M_num))
			change_range_ct--;
		else
			Alarm_Process(OVP_Alarm,Clear_Alarm);
	}
	if((p3k_Measure_Data.VOLT >= 0.8)&&(p3k_Measure_Data.VOLT <= 1.2)&&(UTILITY.LOAD_CTL==Switch_ON)) { //2013.0911
		CCCRCP_Response_8_12 = 1;
	} else {
		CCCRCP_Response_8_12 = 0;
	}

	/* RVP Alarm*/ //4 #2
	if(Data_tmp->VRange) 	rvp_value = -15;///-10;
	else					rvp_value = -70;///-50;
	if( (Negative_Volt_Value<=rvp_value)&&(P_CAL_MODE!=M_num))
		RVP_Count++;
	else
		RVP_Count = 0;

	if(RVP_Count>=50) {
		Alarm_Process(RVP_Alarm,Set_Alarm);
		RVP_Count = 50;
		Al_da |= (0x01<<RVP_Alarm)>>1;
	} else
		Alarm_Process(RVP_Alarm,Clear_Alarm);


	/* OTP */  //4 #1
	if(FPGA_Status_Data&PS_OTP_Event) {
		Alarm_Process(OTP_Alarm,Set_Alarm);
		Al_da |= (0x01<<OTP_Alarm)>>1;
	} else
		Alarm_Process(OTP_Alarm,Clear_Alarm);

	RecoderAlarmStatus = Al_da;
	if((M_num != P_CAL_MODE) && (M_num != P_Test_Func) && (M_num != P_NSeq_EXECUTE) && (M_num != P_FSeq_EXECUTE)&&(M_num != P_PROG_EXECUTE)) { //new added???
		tx_data.ADDRH = Para_Ext_Command;
		tx_data.ADDRL = Para_Ext_Setting;
		SendTXData(&tx_data);
	}

	FPGA_R[254] |= RecoderAlarmStatus;

}

void Prot_Setting_Process(void) {
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UWORD All_Prot_Setteng = 0;

	switch(P3k_Chan_Data.Load_Type){
	case BATT_Load:
	case FLED_Load:
	case CLED_Load:
		All_Prot_Setteng |= Set_Von_Latch_ON;
		break;
	default:
		if(( Data_tmp->CONF.VON_LATCH)||(UTILITY.SHORT_CTL))
			All_Prot_Setteng |= Set_Von_Latch_ON;
		else
			All_Prot_Setteng |= Set_Von_Latch_OFF ;
		break;
	}	

	if(Data_tmp->PROT.OPP_SET==1)
		All_Prot_Setteng |= Set_OPP_Limit;
	else {
		All_Prot_Setteng |= Set_OPP_Load_OFF;
		Acess_FPGA(FPGA_Control, Clear_OPP_Latch);
	}
#if Enable_OPPOCP_off
	if((P3k_Chan_Data.IRange==0)&&(p3k_Cal_data.Protection[1].OCP>p3k_Cal_data.Protection[0].OCP)) {
		All_Prot_Setteng |= Set_OCP_Load_OFF;
		Acess_FPGA(FPGA_Control, Clear_OCP_Latch);
	} else if(Data_tmp->PROT.OCP_SET==1) {
		All_Prot_Setteng |= Set_OCP_Limit;

	} else {
		All_Prot_Setteng |= Set_OCP_Load_OFF;
		Acess_FPGA(FPGA_Control, Clear_OCP_Latch);
	}
#else
	if(Data_tmp->PROT.OCP_SET==1) {
		All_Prot_Setteng |= Set_OCP_Limit;

	} else {
		All_Prot_Setteng |= Set_OCP_Load_OFF;
		Acess_FPGA(FPGA_Control, Clear_OCP_Latch);
	}
#endif
	Acess_FPGA(FPGA_On_Off_Latch_Setting, All_Prot_Setteng);
}


void GO_NG_Determine(UBYTE GONG_MODE, UBYTE GONG_Memory) {
	float GONG_Source,GONG_H_Level,GONG_L_Level;
	double GONG_H_Resolution,GONG_L_Resolution;
	UWORD GONG_H_Step=0,GONG_L_Step=0;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	if(CC_MODE==GONG_MODE) {
		//GONG_Source = p3k_Measure_Data.VOLT;
		GONG_Source = p3k_Measure_Data.Real_Volt;
		GONG_H_Resolution = (ptrMODEL_TYPE->CC_SPEC)[1].Resolution;
		GONG_L_Resolution = (ptrMODEL_TYPE->CC_SPEC)[2].Resolution;

		if(Data_tmp->CC.STADYNA) {
			GONG_H_Step = Data_tmp->CC.DYNA[Data_tmp->IRange].HIGHVAL;
			GONG_L_Step = Data_tmp->CC.DYNA[Data_tmp->IRange].LOWVAL;
		} else {
			GONG_H_Step = Data_tmp->CC.STA[Data_tmp->IRange].HIGHVAL;
			GONG_L_Step = Data_tmp->CC.STA[Data_tmp->IRange].LOWVAL;
		}
	} else if(CR_MODE==GONG_MODE) {
		//GONG_Source = p3k_Measure_Data.VOLT;
		GONG_Source = p3k_Measure_Data.Real_Volt;
		GONG_H_Resolution = (ptrMODEL_TYPE->CR_SPEC)[1].Resolution;
		GONG_L_Resolution = (ptrMODEL_TYPE->CR_SPEC)[2].Resolution;

		if(Data_tmp->CR.STADYNA) {
			GONG_H_Step = Data_tmp->CR.DYNA[Data_tmp->IRange].HIGHVAL;
			GONG_L_Step = Data_tmp->CR.DYNA[Data_tmp->IRange].LOWVAL;
		} else {
			GONG_H_Step = Data_tmp->CR.STA[Data_tmp->IRange].HIGHVAL;
			GONG_L_Step = Data_tmp->CR.STA[Data_tmp->IRange].LOWVAL;
		}
	} else if(CV_MODE==GONG_MODE) {
		//GONG_Source = p3k_Measure_Data.CURR;
		GONG_Source = p3k_Measure_Data.Real_Curr;
		GONG_H_Resolution = (ptrMODEL_TYPE->CV_SPEC)[1].Resolution;
		GONG_L_Resolution = (ptrMODEL_TYPE->CV_SPEC)[2].Resolution;
		GONG_H_Step = Data_tmp->CV.STA[Data_tmp->VRange].HIGHVAL;
		GONG_L_Step = Data_tmp->CV.STA[Data_tmp->VRange].LOWVAL;
	} else { /*CP Mode*/
		//GONG_Source = p3k_Measure_Data.VOLT;
		GONG_Source = p3k_Measure_Data.Real_Volt;
		GONG_H_Resolution = (ptrMODEL_TYPE->CP_SPEC)[1].Resolution;
		GONG_L_Resolution = (ptrMODEL_TYPE->CP_SPEC)[2].Resolution;

		if(Data_tmp->CP.STADYNA) {
			GONG_H_Step = Data_tmp->CP.DYNA[Data_tmp->IRange].HIGHVAL;
			GONG_L_Step = Data_tmp->CP.DYNA[Data_tmp->IRange].LOWVAL;
		} else {
			GONG_H_Step = Data_tmp->CP.STA[Data_tmp->IRange].HIGHVAL;
			GONG_L_Step = Data_tmp->CP.STA[Data_tmp->IRange].LOWVAL;
		}
	}

	if(Prog_Load == P3k_Chan_Data.Load_Type) {
		GONG_H_Step = P3k_Chan_Data.M_DATA[GONG_Memory].HIGHVAL;
		GONG_L_Step = P3k_Chan_Data.M_DATA[GONG_Memory].LOWVAL;
	}

	GONG_H_Level = GONG_H_Step * GONG_H_Resolution;
	GONG_L_Level = GONG_L_Step * GONG_L_Resolution;

	if((GONG_Source <= GONG_H_Level) && (GONG_Source >= GONG_L_Level))
		p3k_Measure_Data.Go_NoGo = 2;
	else
		p3k_Measure_Data.Go_NoGo = 1;

}

void GoNoGo_Process(void) {
	static UWORD Pass_Fail_Time_Count=0,Prog_Count=0;
	UWORD GONG_Prog_No,GONG_Step_No,GONG_Delay_Time,GONG_On_Time;
	UBYTE GONG_MODE,GONG_Memory,j;
	UWORD *SPEC_Result_Ptr,*SPEC_Result_Backup_Ptr;
	unsigned short Total_Determine_Point,Last_Determine_Point;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Prog_Disp_Str	*Prog_Disp_Ptr;

	if((Data_tmp->SPEC) && (UTILITY.LOAD_CTL)) {
		if(Prog_Count != Prog_Seq_Data.Display_Count) { /* Determine Step has be changed. */
			Prog_Count = Prog_Seq_Data.Display_Count;
			Pass_Fail_Time_Count = 0;
		}

		if(Prog_Load == P3k_Chan_Data.Load_Type) {
			GONG_Prog_No			= Prog_Seq_Data.Prog_Disp_Data[Prog_Count/3].Prog_No;
			GONG_Step_No			= Prog_Seq_Data.Prog_Disp_Data[Prog_Count/3].Step_No;
			SPEC_Result_Ptr			= &Prog_Seq_Data.Prog_Disp_Data[Prog_Count/3].SPEC_Result;
			SPEC_Result_Backup_Ptr	= &Prog_Seq_Data.Prog_Disp_Data[Prog_Count/3].SPEC_Result_Backup;
			GONG_On_Time 			= p3k_Chan_PROG.Timing_Data[GONG_Prog_No].ONTIME[GONG_Step_No];
			GONG_Delay_Time			= p3k_Chan_PROG.Timing_Data[GONG_Prog_No].PFTIME[GONG_Step_No];
			GONG_Memory				= p3k_Chan_PROG.Timing_Data[GONG_Prog_No].MEMORY[GONG_Step_No];
			GONG_MODE				= P3k_Chan_Data.M_DATA[GONG_Memory].MODE;

			Total_Determine_Point 	= (GONG_On_Time * 100) / Measure_Time;
			Last_Determine_Point	= Total_Determine_Point - 1;

			if(((!GONG_Delay_Time) && ((Pass_Fail_Time_Count > Determine_Point) && (Pass_Fail_Time_Count < Last_Determine_Point)))|| (GONG_Delay_Time && (Pass_Fail_Time_Count >= (GONG_Delay_Time*5)) && (Pass_Fail_Time_Count < Last_Determine_Point))) {
				GO_NG_Determine(GONG_MODE, GONG_Memory);

				if(Prog_Count <= First_Step)
					Prog_Seq_Data.Prog_Disp_Data[Prog_Seq_Data.Total_Count-1].SPEC_Result_Backup = 0;
				else
					Prog_Seq_Data.Prog_Disp_Data[(Prog_Count/3)-1].SPEC_Result_Backup = 0;

				if(1 != *SPEC_Result_Ptr)
					*SPEC_Result_Ptr = p3k_Measure_Data.Go_NoGo;
				*SPEC_Result_Backup_Ptr = p3k_Measure_Data.Go_NoGo;
			} else {
				Pass_Fail_Time_Count++;
				p3k_Measure_Data.Go_NoGo = 0;
			}
		} else {
			GONG_Delay_Time = Data_tmp->P_F_Delay;
			GONG_MODE = Data_tmp->CURRMODE;

			if(Pass_Fail_Time_Count >= (GONG_Delay_Time*5))
				GO_NG_Determine(GONG_MODE, 0);
			else {
				Pass_Fail_Time_Count++;
				p3k_Measure_Data.Go_NoGo = 0;
			}
		}
	} else {
		Prog_Count = 0;
		Pass_Fail_Time_Count = 0;
		p3k_Measure_Data.Go_NoGo = 0;
	}
}

p3k_Ramp_Str Seq_Ramp_Process(UBYTE Ramp_Mode,UBYTE Ramp_IRange,UBYTE Ramp_VRange,UBYTE Ramp_STADYNA,UWORD Ramp_L1_STEP,UWORD Ramp_L2_STEP,P3k_Time_Str Ramp_Time) {
	double SR_T1_Max = 0.0,SR_T1_Min = 0.0,SR_T1_Resolution = 0.0; /*SlewRate TimeBase1 Max/Min Value(mA/us)*/
	double SR_T2_Max = 0.0,SR_T2_Min = 0.0,SR_T2_Resolution = 0.0; /*SlewRate TimeBase2 Max/Min Value(mA/us)*/
	double SR_T3_Max = 0.0,SR_T3_Min = 0.0,SR_T3_Resolution = 0.0; /*SlewRate TimeBase3 Max/Min Value(mA/us)*/
	double Ramp_SR_Real = 0.0;
	UWORD SR_Max_Step = 0,SR_Min_Step = 0,SR_Max_DA_Count = 0;
	UWORD Ramp_STEP;

	UWORD Ramp_Time_Count = 0;

	ULONG Delta_Value_32bit = 0;

	UWORD Ramp_TimeBase_Value = 0;

	double Setting_Gain = 0.0,Setting_Offset = 0.0,Setting_Resolution = 0.0;
	ULONG Ramp_mS_Time;
	p3k_Ramp_Str p3k_Ramp_Data;

	p3k_Ramp_Data.Delta_Response = get_response(Ramp_Mode);

	switch(Ramp_Mode) {
	case CC_MODE:	/* CC Mode */
		Setting_Gain					= p3k_Cal_data.CC_Data[Ramp_IRange].Cal_Value_Gain;
		Setting_Offset					= p3k_Cal_data.CC_Data[Ramp_IRange].Cal_Value_Offset;
		Setting_Resolution				= ptrMODEL_TYPE->CC[(Ramp_IRange*10)+(Ramp_STADYNA*4)].Resolution;
		SR_Max_Step 					= ptrMODEL_TYPE->CC[2+(Ramp_IRange*10)].Max;
		SR_Min_Step 					= ptrMODEL_TYPE->CC[2+(Ramp_IRange*10)].Min;
		SR_Max_DA_Count 				= (SR_Max_Step*20);
		SR_T1_Resolution				= ptrMODEL_TYPE->CC[2+(Ramp_IRange*10)].Resolution;
		break;
	case CR_MODE: 	/* CR Mode */
		Setting_Gain					= p3k_Cal_data.CR_Data[Ramp_IRange].Cal_Value_Gain;
		Setting_Offset					= p3k_Cal_data.CR_Data[Ramp_IRange].Cal_Value_Offset;
		Setting_Resolution				= ptrMODEL_TYPE->CR[(Ramp_IRange*10)+(Ramp_STADYNA*4)].Resolution;
		SR_Max_Step 					= ptrMODEL_TYPE->CR[2+(Ramp_IRange*10)].Max;
		SR_Min_Step 					= ptrMODEL_TYPE->CR[2+(Ramp_IRange*10)].Min;
		SR_Max_DA_Count 				= (SR_Max_Step*20/10);
		SR_T1_Resolution				= ptrMODEL_TYPE->CR[2+(Ramp_IRange*10)].Resolution;
		break;
	case CP_MODE:	/* CP Mode */
		Setting_Gain					= p3k_Cal_data.CP_Data[Ramp_IRange].Cal_Value_Gain;
		Setting_Offset					= p3k_Cal_data.CP_Data[Ramp_IRange].Cal_Value_Offset;
		Setting_Resolution				= ptrMODEL_TYPE->CP[(Ramp_IRange*10)+(Ramp_STADYNA*4)].Resolution;
		SR_Max_Step 					= ptrMODEL_TYPE->CP[2+(Ramp_IRange*10)].Max;
		SR_Min_Step 					= ptrMODEL_TYPE->CP[2+(Ramp_IRange*10)].Min;
		SR_Max_DA_Count 				= (SR_Max_Step*20/10);
		SR_T1_Resolution				= ptrMODEL_TYPE->CP[2+(Ramp_IRange*10)].Resolution;
		break;
	}

	SR_T2_Resolution = SR_T1_Resolution*10.0;
	SR_T3_Resolution = SR_T1_Resolution*100.0;
#if 1//Enable_NSEQ_Usec
	Ramp_mS_Time = Ramp_Time.Hour*60*60*1000 + Ramp_Time.Minute*60*1000 + Ramp_Time.Second*1000 + Ramp_Time.MilliSecond/20;
#else
	Ramp_mS_Time = Ramp_Time.Hour*60*60*1000 + Ramp_Time.Minute*60*1000 + Ramp_Time.Second*1000 + Ramp_Time.MilliSecond;
#endif
	/*
	1uS		~ 60mS		1uS
	60mS	~ 600mS		10uS
	600mS	~ 6S			100uS
	6S		~ 1min		1mS
	1min	~ 100min		100mS
	100min	~ 1000min	1S
	1000min	~ 10000min	10S
	10000min~ 1000H		1min
	*/
	if(Ramp_mS_Time>10000*60*1000) {	/* 10000 Minute ~ 1000 Hour	*/
		p3k_Ramp_Data.Delta_TimeBase = Time_Unit_1min;
		Ramp_Time_Count = Ramp_Time.Hour*60 + Ramp_Time.Minute;
	} else if(Ramp_mS_Time>1000*60*1000) {	/* 1000 Minute ~ 10000 Minute	*/
		p3k_Ramp_Data.Delta_TimeBase = Time_Unit_10S;
		Ramp_Time_Count = (Ramp_Time.Hour*60*60 + Ramp_Time.Minute*60 + Ramp_Time.Second)/10;
	} else if(Ramp_mS_Time>100*60*1000) {	/* 100 Minute ~1000 Minute	*/
		p3k_Ramp_Data.Delta_TimeBase = Time_Unit_1S;
		Ramp_Time_Count = Ramp_Time.Hour*60*60 + Ramp_Time.Minute*60 + Ramp_Time.Second;
#if Enable_NSEQ_Usec
	} else if(Ramp_mS_Time>1*60*1000) {	/* 1 Minute ~ 100 Minute	*/
		p3k_Ramp_Data.Delta_TimeBase = Time_Unit_100mS;
		Ramp_Time_Count = (Ramp_Time.Hour*60*60*1000 + Ramp_Time.Minute*60*1000 + Ramp_Time.Second*1000 + Ramp_Time.MilliSecond/20)/100;
	} else if(Ramp_mS_Time>6000) {	/* 6 Second ~ 1 Minute	*/
		p3k_Ramp_Data.Delta_TimeBase = Time_Unit_1mS;
		Ramp_Time_Count = Ramp_Time.Minute*60*1000 + Ramp_Time.Second*1000 + Ramp_Time.MilliSecond/20;
	} else if(Ramp_mS_Time>600) {	/* 600 ms ~ 6 Second	*/
		p3k_Ramp_Data.Delta_TimeBase = Time_Unit_100uS;
		Ramp_Time_Count = (Ramp_Time.Second*1000*1000 + Ramp_Time.MilliSecond*50)/100;
	} else if(Ramp_mS_Time>60) {	/* 60 ms ~ 600 ms	*/
		p3k_Ramp_Data.Delta_TimeBase = Time_Unit_10uS;
		Ramp_Time_Count = (Ramp_Time.MilliSecond*50)/10;
	} else {						/* 1 us ~ 60 ms	*/
		p3k_Ramp_Data.Delta_TimeBase = Time_Unit_1uS;
		Ramp_Time_Count = (Ramp_Time.MilliSecond*50)/2;
	}
#else
	} else if(Ramp_mS_Time>1*60*1000) {	/* 1 Minute ~ 100 Minute	*/
		p3k_Ramp_Data.Delta_TimeBase = Time_Unit_100mS;
		Ramp_Time_Count = (Ramp_Time.Hour*60*60*1000 + Ramp_Time.Minute*60*1000 + Ramp_Time.Second*1000 + Ramp_Time.MilliSecond)/100;
	} else if(Ramp_mS_Time>6000) {	/* 6 Second ~ 1 Minute	*/
		p3k_Ramp_Data.Delta_TimeBase = Time_Unit_1mS;
		Ramp_Time_Count = Ramp_Time.Minute*60*1000 + Ramp_Time.Second*1000 + Ramp_Time.MilliSecond;
	} else if(Ramp_mS_Time>600) {	/* 600 ms ~ 6 Second	*/
		p3k_Ramp_Data.Delta_TimeBase = Time_Unit_100uS;
		Ramp_Time_Count = (Ramp_Time.Second*1000*1000 + Ramp_Time.MilliSecond*1000)/100;
	} else if(Ramp_mS_Time>60) {	/* 60 ms ~ 600 ms	*/
		p3k_Ramp_Data.Delta_TimeBase = Time_Unit_10uS;
		Ramp_Time_Count = (Ramp_Time.MilliSecond*1000)/10;
	} else {						/* 1 us ~ 60 ms	*/
		p3k_Ramp_Data.Delta_TimeBase = Time_Unit_1uS;
		Ramp_Time_Count = (Ramp_Time.MilliSecond*1000)/2;
	}

#endif
	if(Time_Unit_1uS==p3k_Ramp_Data.Delta_TimeBase)
		p3k_Ramp_Data.DeltaTime = 2;	/* Min TimeTick is 2uS*/
	else
		p3k_Ramp_Data.DeltaTime = 1;

//printf("dat:%d\n",Ramp_mS_Time);
	if(Ramp_Time_Count) {
		if(CV_MODE != Ramp_Mode)
			p3k_Ramp_Data.DeltaTime |= Enable_Ramp;
	}
	if(Ramp_L1_STEP>Ramp_L2_STEP)
		Ramp_STEP = Ramp_L1_STEP - Ramp_L2_STEP;
	else
		Ramp_STEP = Ramp_L2_STEP - Ramp_L1_STEP;

#if 1
	if(Ramp_STEP<15)Ramp_STEP=15; //Adam_test 2014.0814
#endif

	if(Ramp_mS_Time) {
		Delta_Value_32bit	= ((float)(Step_To_CNT(Ramp_STEP,Setting_Gain,0))/(float)(Ramp_Time_Count) )*65536.0;
		//Delta_Value_32bit	= ((float)(Step_To_CNT(Ramp_STEP,Setting_Gain,Setting_Offset))/(float)(Ramp_Time_Count) )*65536.0;
		Ramp_SR_Real		= (Ramp_STEP*Setting_Resolution*1000.0)/(Ramp_mS_Time*1000.0);				/*	mA/us	*/
	} else {
#if 0	
		Delta_Value_32bit	= 65535;
		Ramp_SR_Real = 1.0;
#else
		Ramp_Time_Count = Ramp_Time.MilliSecond*50/2;
		Delta_Value_32bit	= ((float)(Step_To_CNT(Ramp_STEP,Setting_Gain,0))/((float)Ramp_Time_Count) )*65536.0;
		Ramp_SR_Real		= (Ramp_STEP*Setting_Resolution*1000.0)/(Ramp_Time_Count);	
		//Ramp_SR_Real = 0.002;		
#endif
	}
	
	p3k_Ramp_Data.Delta_SR_Set = Ramp_SR_Real * 3000;//SR_Max_DA_Count / SR_Max_Step;

	if(CR_MODE==Ramp_Mode){
		if(p3k_Ramp_Data.Delta_SR_Set<200)p3k_Ramp_Data.Delta_SR_Set = 200;	
	}

	p3k_Ramp_Data.Delta_Value_Low	= (Delta_Value_32bit & 0x0000FFFF);
	p3k_Ramp_Data.Delta_Value_High	= (Delta_Value_32bit & 0xFFFF0000)>>16;

	if(p3k_Ramp_Data.Delta_SR_Set>50000)
		p3k_Ramp_Data.Delta_SR_Set = 50000;

	if(CP_MODE==Ramp_Mode) {
		p3k_Ramp_Data.Delta_SR_Set	= 10000;
	}
	return p3k_Ramp_Data;
}

extern float Get_Parallel_Parameter(unsigned char IRange);
#define Measure_Data_64     64
char Measure_Count = 0;
UWORD Measure_Curr_Sum=0,Measure_Volt_Sum=0,Measure_Ext_Sum=0;
UWORD Measure_Curr_Data64[Measure_Data_64],Measure_Volt_Data64[Measure_Data_64],Measure_Ext_Data64[Measure_Data_64];
UWORD Current_Raw[1024],Record_Count;
float Measure_Volt_Old = 0,Measure_Curr_Old = 0,Meas_Ext_Old = 0;
float Old_Curr_Raw[1024],Display_Curr[1024];

UWORD Ext_Positive_Limit,Ext_Negative_Limit;

UBYTE get_sta_dyna_mode(UBYTE mode){
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UBYTE staDyna;
	switch(mode){
	case CC_MODE:
		staDyna = Data_tmp->CC.STADYNA;
		break;
	case CR_MODE:
		staDyna = Data_tmp->CR.STADYNA;
		break;
	case CP_MODE:
		staDyna = Data_tmp->CP.STADYNA;
		break;
	default:
		staDyna = 0;
		break;
	}
	return staDyna; 
}
UBYTE get_measure_clear_buff_flag(void){
	static UWORD sRagne;
	static UBYTE sSwich,sFlag;
	if(sRagne != FPGA_W[0x42]){
		sRagne =	 FPGA_W[0x42];
		sFlag = 3;
	}else if((Prog_Load==P3k_Chan_Data.Load_Type)||(OCP_Load==P3k_Chan_Data.Load_Type)){
		sFlag = 1;
	} else if (sSwich != UTILITY.LOAD_CTL ) {
		sSwich= UTILITY.LOAD_CTL;
		sFlag = 3;	
	}else{
		if(sFlag)sFlag--;
	}
	return sFlag;
}

#if 1 //2016_0718

void extern_measure_process(void){
	int j;	
	long Measure_Ext_Sum64=0;
	float Ext_Real_Count;
	long Measure_Offset_Value;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	p3k_send_tx_list tx_data;
	UWORD Meas_Ext_Single=0,Meas_Ext_AVG=0;
	if((Data_tmp->CONF.Ext_Setting.Control)||(P_CAL_MODE==M_num)) return;

	Meas_Ext_Single = Acess_FPGA(FPGA_EXT_RV_SENSE,NULL);
	DataRedrawFlag |= PARA_CHANGE;
	Meas_Ext_AVG			= ( Meas_Ext_Single	  + Measure_Ext_Sum  ) / 2;

	if(Meas_Ext_Single>Measure_Ext_Sum)
		Measure_Offset_Value = Meas_Ext_Single - Measure_Ext_Sum;
	else
		Measure_Offset_Value = Measure_Ext_Sum - Meas_Ext_Single;

	Meas_Ext_AVG = Meas_Ext_Single;

	if(Measure_Offset_Value>=50) {
		for(j=0; j<Measure_Data_64; j++)
			Measure_Ext_Data64[j] = Meas_Ext_AVG;
	} else
		Measure_Ext_Data64[Measure_Count] = Meas_Ext_AVG;

	for(j=0; j<Measure_Data_64; j++) {
		Measure_Ext_Sum64  += Measure_Ext_Data64[j];
	}
	Measure_Ext_Sum	 = Measure_Ext_Sum64  >> 6;

	Ext_Real_Count = (float)0.4 / 5.0 * 65535.0; /*  D/A Ref. Volt. = 5.0 */
	Ext_Negative_Limit = 65536 + ((Ext_Real_Count * p3k_Cal_data.Ext_R_Sense.Meas_Value_Gain) / 65535) - p3k_Cal_data.Ext_R_Sense.Meas_Value_Offset;
	Ext_Positive_Limit = (Monitor_H) * 1.05;

	if((Ext_Negative_Limit > Measure_Ext_Sum) && (Ext_Positive_Limit < Measure_Ext_Sum)) {
		p3k_Measure_Data.Ext_Percent = 0.0;
		Ext_UnReg_Flag = 1;
		UTILITY.LOAD_CTL = Switch_OFF;
		CMD_LOAD_SW;
		PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
		SysRedrawFlag |= PROG_UPDATA;
	} else {
		Ext_UnReg_Flag = 0;
		if(Ext_Positive_Limit < Measure_Ext_Sum)
			p3k_Measure_Data.Ext_Percent = 0.0;
		else
			p3k_Measure_Data.Ext_Percent = (float)Measure_Ext_Sum / (float)(Monitor_H);
	}

}


long Measure_Process(void) {
	UBYTE STA_DYNA_Mode;
	int j;
	double Real_Value;
	static UWORD k=0;
	
	long Measure_Curr_Sum64=0,Measure_Volt_Sum64=0,Measure_Ext_Sum64=0;
	float Volt_Real_Gain,Curr_Real_Gain;
	UWORD Volt_Positive_Limit,Curr_Positive_Limit;
	UWORD Measure_Volt_Data,Measure_Volt_Data_AVG=0;
	UWORD Measure_Curr_Data,Measure_Curr_Data_AVG=0;
	
	UBYTE C_IRange;
	long Volt_Negative_Value;
	long Measure_Offset_Value;

	static long MeasureCurrSum8=0;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	p3k_send_tx_list tx_data;
	UBYTE clearBuff = get_measure_clear_buff_flag();
	Measure_Volt_Data = Acess_FPGA(FPGA_V_Sense,NULL);
	Measure_Curr_Data = Acess_FPGA(FPGA_I_Sense,NULL);
	extern_measure_process();	
	
	C_IRange = Data_tmp->IRange;
	
	if((M_num!=P_PROG_EXECUTE)&&(M_num!=P_NSeq_EXECUTE)&&(M_num!=P_FSeq_EXECUTE)){
		if(Data_tmp->CURRMODE == P_CR)C_IRange = HIGH_RANGE;
	}
	Volt_Real_Gain = (float)(p3k_Cal_data.Volt[Data_tmp->VRange].Meas_Value_Gain) / 65535;
	Curr_Real_Gain = (float)(p3k_Cal_data.Curr[C_IRange].Meas_Value_Gain) / 65535;

	Volt_Positive_Limit = (65535 - p3k_Cal_data.Volt[Data_tmp->VRange].Meas_Value_Offset) * Volt_Real_Gain;
	Curr_Positive_Limit = (65535 - p3k_Cal_data.Curr[C_IRange].Meas_Value_Offset) * Curr_Real_Gain;

	if(Measure_Volt_Data > Volt_Positive_Limit) {
		Volt_Negative_Value =  (Measure_Volt_Data - 65535)-1;
		Measure_Volt_Data = 0;
	} else
		Volt_Negative_Value = 0;

	if(Measure_Curr_Data > (65535 * Curr_Real_Gain))
		Measure_Curr_Data = 0;

	if(UTILITY.LOAD_CTL==Switch_OFF) {
		if(Model_Number==MODEL3031E){
			if(Measure_Volt_Data <= 10)
				Measure_Volt_Data = 0;
			if(Measure_Curr_Data <= 50)
				Measure_Curr_Data = 0;
		}else{
			if(Measure_Volt_Data <= 20){
				Measure_Volt_Data = 0;
			}else if((Data_tmp->VRange)&&(Measure_Volt_Data < 40)){
				Measure_Volt_Data = (Measure_Volt_Data-20)*2;
			}
			if(Measure_Curr_Data <= 50)
				Measure_Curr_Data = 0;
		}
	}
	

	if((P3k_Chan_Data.CURRMODE == P_CP)&&(C_IRange ==LOW_RANGE)) {
		static char cnt=0;
		cnt++;
		MeasureCurrSum8 += Measure_Curr_Data;
		if(clearBuff){
			MeasureCurrSum8 = 0;
			cnt=0;
		}else if(cnt<10) {
			return Volt_Negative_Value;
		} else {
			Measure_Curr_Data = (MeasureCurrSum8/10);
			MeasureCurrSum8 = 0;
			cnt=0;
		}
	} ///else
	Measure_Count++;
	Measure_Volt_Data_AVG	= ( Measure_Volt_Data + Measure_Volt_Sum ) / 2;
	Measure_Curr_Data_AVG	= ( Measure_Curr_Data + Measure_Curr_Sum ) / 2;

	if(Measure_Count==Measure_Data_64)		Measure_Count=0;

	STA_DYNA_Mode = get_sta_dyna_mode(Data_tmp->CURRMODE);

	if(Measure_Volt_Data>Measure_Volt_Sum)
		Measure_Offset_Value = Measure_Volt_Data - Measure_Volt_Sum;
	else
		Measure_Offset_Value = Measure_Volt_Sum - Measure_Volt_Data;
	Measure_Volt_Data_AVG = Measure_Volt_Data;

	if( ((Measure_Offset_Value>=10)&&(STA_DYNA_Mode==0)) || (clearBuff )) { //Adam_test
		for(j=0; j<Measure_Data_64; j++)		Measure_Volt_Data64[j] = Measure_Volt_Data_AVG;
	} else									Measure_Volt_Data64[Measure_Count] = Measure_Volt_Data_AVG;


	if(Measure_Curr_Data>Measure_Curr_Sum)	Measure_Offset_Value = Measure_Curr_Data - Measure_Curr_Sum;
	else									Measure_Offset_Value = Measure_Curr_Sum - Measure_Curr_Data;
	Measure_Curr_Data_AVG = Measure_Curr_Data;


	if(((Measure_Offset_Value>=50)&&(STA_DYNA_Mode==0))||(clearBuff )) {
		for(j=0; j<Measure_Data_64; j++)		Measure_Curr_Data64[j] = Measure_Curr_Data_AVG;
	} else
		Measure_Curr_Data64[Measure_Count] = Measure_Curr_Data_AVG;

	for(j=0; j<Measure_Data_64; j++) {
		Measure_Volt_Sum64 += Measure_Volt_Data64[j];
		Measure_Curr_Sum64 += Measure_Curr_Data64[j];
	}

	Measure_Volt_Sum = Measure_Volt_Sum64 >> 6;
	Measure_Curr_Sum = Measure_Curr_Sum64 >> 6;

	p3k_Measure_Data.VOLT = (float)Measure_Volt_Sum * (ptrMODEL_TYPE->CV)[(Data_tmp->VRange)*3].Resolution;
	if(Model_Number==MODEL3031E)p3k_Measure_Data.VOLT *= MEASURE_GAIN_3031;
	else						p3k_Measure_Data.VOLT *= MEASURE_GAIN_3032;
	p3k_Measure_Data.CURR = (float)Measure_Curr_Sum * (ptrMODEL_TYPE->CC)[(C_IRange)*10].Resolution *Get_Parallel_Parameter(C_IRange); //Adam_c
	p3k_Measure_Data.WATT = p3k_Measure_Data.VOLT * p3k_Measure_Data.CURR;
	
	return Volt_Negative_Value;
}

#else
long Measure_Process(void) {
	UBYTE STA_DYNA_Mode;
	int j;
	double Real_Value;
	static UWORD k=0;
	
	long Measure_Curr_Sum64=0,Measure_Volt_Sum64=0,Measure_Ext_Sum64=0;
	float Volt_Real_Gain,Curr_Real_Gain,Ext_Real_Count;
	UWORD Volt_Positive_Limit,Curr_Positive_Limit;
	UWORD Measure_Volt_Data,Measure_Volt_Data_AVG=0;
	UWORD Measure_Curr_Data,Measure_Curr_Data_AVG=0;
	UWORD Meas_Ext_Single=0,Meas_Ext_AVG=0;
	UBYTE C_IRange;
	long Volt_Negative_Value;
	long Measure_Offset_Value;
#if 1
	static long MeasureCurrSum8=0;
#endif

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	p3k_send_tx_list tx_data;
	UBYTE clearBuff = get_measure_clear_buff_flag();

	Measure_Volt_Data = Acess_FPGA(FPGA_V_Sense,NULL);
	Measure_Curr_Data = Acess_FPGA(FPGA_I_Sense,NULL);
	

	if((Data_tmp->CONF.Ext_Setting.Control)&&(P_CAL_MODE!=M_num)) {
		Meas_Ext_Single = Acess_FPGA(FPGA_EXT_RV_SENSE,NULL);
		DataRedrawFlag |= PARA_CHANGE;
	}
	
	C_IRange = Data_tmp->IRange;
	if((M_num!=P_PROG_EXECUTE)&&(M_num!=P_NSeq_EXECUTE)&&(M_num!=P_FSeq_EXECUTE)){
		if(Data_tmp->CURRMODE == P_CR)C_IRange = HIGH_RANGE;
	}
	Volt_Real_Gain = (float)(p3k_Cal_data.Volt[Data_tmp->VRange].Meas_Value_Gain) / 65535;
	Curr_Real_Gain = (float)(p3k_Cal_data.Curr[C_IRange].Meas_Value_Gain) / 65535;

	Volt_Positive_Limit = (65535 - p3k_Cal_data.Volt[Data_tmp->VRange].Meas_Value_Offset) * Volt_Real_Gain;
	Curr_Positive_Limit = (65535 - p3k_Cal_data.Curr[C_IRange].Meas_Value_Offset) * Curr_Real_Gain;

	if(Measure_Volt_Data > Volt_Positive_Limit) {
		Volt_Negative_Value =  (Measure_Volt_Data - 65535)-1;
		Measure_Volt_Data = 0;
	} else
		Volt_Negative_Value = 0;

	if(Measure_Curr_Data > (65535 * Curr_Real_Gain))
		Measure_Curr_Data = 0;

	if(UTILITY.LOAD_CTL==Switch_OFF) {
		if(Model_Number==MODEL3031E){
			if(Measure_Volt_Data <= 10)
				Measure_Volt_Data = 0;
			if(Measure_Curr_Data <= 50)
				Measure_Curr_Data = 0;
		}else{
			if(Measure_Volt_Data <= 20){
				Measure_Volt_Data = 0;
			}else if((Data_tmp->VRange)&&(Measure_Volt_Data < 40)){
				Measure_Volt_Data = (Measure_Volt_Data-20)*2;
			}
			if(Measure_Curr_Data <= 50)
				Measure_Curr_Data = 0;
		}
	}
	

	if((P3k_Chan_Data.CURRMODE == P_CP)&&(C_IRange ==LOW_RANGE)) {
		static char cnt=0;
		cnt++;
		MeasureCurrSum8 += Measure_Curr_Data;
		if(clearBuff){
			MeasureCurrSum8 = 0;
			cnt=0;
		}else if(cnt<10) {
			return Volt_Negative_Value;
		} else {
			Measure_Curr_Data = (MeasureCurrSum8/10);
			MeasureCurrSum8 = 0;
			cnt=0;
		}
	} ///else
	Measure_Count++;
	Measure_Volt_Data_AVG	= ( Measure_Volt_Data + Measure_Volt_Sum ) / 2;
	Measure_Curr_Data_AVG	= ( Measure_Curr_Data + Measure_Curr_Sum ) / 2;
	Meas_Ext_AVG			= ( Meas_Ext_Single	  + Measure_Ext_Sum  ) / 2;

	if(Measure_Count==Measure_Data_64)		Measure_Count=0;


	STA_DYNA_Mode = get_sta_dyna_mode(Data_tmp->CURRMODE);
	

	


	if(Measure_Volt_Data>Measure_Volt_Sum)
		Measure_Offset_Value = Measure_Volt_Data - Measure_Volt_Sum;
	else
		Measure_Offset_Value = Measure_Volt_Sum - Measure_Volt_Data;
	Measure_Volt_Data_AVG = Measure_Volt_Data;
#if Enable_OCP_function
	if( ((Measure_Offset_Value>=10)&&(STA_DYNA_Mode==0)) || (clearBuff )) { //Adam_test
#else
	if( ((Measure_Offset_Value>=10)&&(STA_DYNA_Mode==0)) || (clearBuff )) { //Adam_test
#endif
		for(j=0; j<Measure_Data_64; j++)
			Measure_Volt_Data64[j] = Measure_Volt_Data_AVG;
	} else
		Measure_Volt_Data64[Measure_Count] = Measure_Volt_Data_AVG;


	if(Measure_Curr_Data>Measure_Curr_Sum)
		Measure_Offset_Value = Measure_Curr_Data - Measure_Curr_Sum;
	else
		Measure_Offset_Value = Measure_Curr_Sum - Measure_Curr_Data;
	Measure_Curr_Data_AVG = Measure_Curr_Data;

#if Enable_OCP_function
	if(((Measure_Offset_Value>=50)&&(STA_DYNA_Mode==0))||(clearBuff )) {
#else
	if(((Measure_Offset_Value>=50)&&(STA_DYNA_Mode==0))||(clearBuff )) {
#endif
		for(j=0; j<Measure_Data_64; j++)		Measure_Curr_Data64[j] = Measure_Curr_Data_AVG;
	
	} else
		Measure_Curr_Data64[Measure_Count] = Measure_Curr_Data_AVG;

	if(Meas_Ext_Single>Measure_Ext_Sum)
		Measure_Offset_Value = Meas_Ext_Single - Measure_Ext_Sum;
	else
		Measure_Offset_Value = Measure_Ext_Sum - Meas_Ext_Single;

	Meas_Ext_AVG = Meas_Ext_Single;

	if(Measure_Offset_Value>=50) {
		for(j=0; j<Measure_Data_64; j++)
			Measure_Ext_Data64[j] = Meas_Ext_AVG;
	} else
		Measure_Ext_Data64[Measure_Count] = Meas_Ext_AVG;

	for(j=0; j<Measure_Data_64; j++) {
		Measure_Volt_Sum64 += Measure_Volt_Data64[j];
		Measure_Curr_Sum64 += Measure_Curr_Data64[j];
		Measure_Ext_Sum64  += Measure_Ext_Data64[j];
	}

	Measure_Volt_Sum = Measure_Volt_Sum64 >> 6;
	Measure_Curr_Sum = Measure_Curr_Sum64 >> 6;
	Measure_Ext_Sum	 = Measure_Ext_Sum64  >> 6;

	p3k_Measure_Data.VOLT = (float)Measure_Volt_Sum * (ptrMODEL_TYPE->CV)[(Data_tmp->VRange)*3].Resolution;
	if(Model_Number==MODEL3031E)p3k_Measure_Data.VOLT *= MEASURE_GAIN_3031;
	else						p3k_Measure_Data.VOLT *= MEASURE_GAIN_3032;
	//p3k_Measure_Data.CURR = (float)Measure_Curr_Sum * (ptrMODEL_TYPE->CC)[(Data_tmp->IRange)*10].Resolution * Get_Parallel_Parameter(Data_tmp->IRange); //Adam_c
	p3k_Measure_Data.CURR = (float)Measure_Curr_Sum * (ptrMODEL_TYPE->CC)[(C_IRange)*10].Resolution *Get_Parallel_Parameter(C_IRange); //Adam_c
	p3k_Measure_Data.WATT = p3k_Measure_Data.VOLT * p3k_Measure_Data.CURR;

	Ext_Real_Count = (float)0.4 / 5.0 * 65535.0; /*  D/A Ref. Volt. = 5.0 */
	Ext_Negative_Limit = 65536 + ((Ext_Real_Count * p3k_Cal_data.Ext_R_Sense.Meas_Value_Gain) / 65535) - p3k_Cal_data.Ext_R_Sense.Meas_Value_Offset;
	Ext_Positive_Limit = (Monitor_H) * 1.05;



	if((Ext_Negative_Limit > Measure_Ext_Sum) && (Ext_Positive_Limit < Measure_Ext_Sum)) {
		p3k_Measure_Data.Ext_Percent = 0.0;
		Ext_UnReg_Flag = 1;
		UTILITY.LOAD_CTL = Switch_OFF;
		tx_data.ADDRH = Machine_Command;
		tx_data.ADDRL = Machine_Load_OnOff;
		SendTXData(&tx_data);
		PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
		SysRedrawFlag |= PROG_UPDATA;
	} else {
		Ext_UnReg_Flag = 0;
		if(Ext_Positive_Limit < Measure_Ext_Sum)
			p3k_Measure_Data.Ext_Percent = 0.0;
		else
			p3k_Measure_Data.Ext_Percent = (float)Measure_Ext_Sum / (float)(Monitor_H);
	}
	return Volt_Negative_Value;
}
#endif

void check_cr_range(void){ //Adam_2016_0414
	if(P3k_Chan_Data.CURRMODE == CR_MODE){
		if(P3k_Chan_Data.VRange==P3k_Chan_Data.IRange){
			P3k_Chan_Data.VRange = (1 == P3k_Chan_Data.IRange) ? 0 : 1;
			P3k_Disp_Data.VRange = P3k_Chan_Data.VRange;
		}
	}		
}
void exe_compensation (void){
#if Enable_P_Compensation	
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	char flag=0;
	if(Normal_Load==Data_tmp->Load_Type){
		if(Data_tmp->CURRMODE==P_CP) {
			if((!Data_tmp->CONF.Ext_Setting.Control)&&(!Data_tmp->CP.STADYNA))flag = 1;			
		}
	}
#if Enable_Battery_Discharge
	else if(BATT_Load==Data_tmp->Load_Type){
		if(BattDisp.Mode >= CV_MODE)flag=1; //cp_mode 
	}
#endif
	if(flag)Compensation_Determine();
#endif
}
void Cacute_AH_WH (void){ // 1/50 = 0.02 sec ==>1/8 = 0.125
#if Enable_Battery_Discharge
	static char recodsec = 100;
	ULONG d1,d2;
	static UBYTE cnt;
#if Normal_TEST
	test_CountFrequency++;
#endif	
	if(p3k_Measure_Data.Sec != recodsec){	
		recodsec = p3k_Measure_Data.Sec;
		cnt = 48;
	}
	if(cnt){
		if((cnt%6)==0){ // 8 times / sec
			d1 = (ULONG)(p3k_Measure_Data.CURR*1000);
			d2 = (ULONG)(p3k_Measure_Data.WATT*1000);	
			recodsec = p3k_Measure_Data.Sec;
			//(double)p3k_Measure_Data.CURR/ 8 /3600; 3600*1000 = 3600 000
			BattDisp.AmpereHour += d1;
			BattDisp.WattHour += d2;
		}
		cnt--;
	}
#endif
}

#if Enable_Func_DisTime
	unsigned long StepStarTime;
#endif


UWORD FPGA_Status_Temp;
void MachineSetupFun(void) {
	int i;
	char tmp, range;
	static unsigned char Load_mS,Clear_VON_Count;
	static unsigned char Seq_complete=0;
	static unsigned char RctCount,RctFlag,GapCount;
	unsigned char RctCountTemp;
	UWORD dat,Machine_Data,TimeOut;
	BAINT IntVal;
	long Volt_Negative_Value;
	UWORD FPGA_Data;
	UWORD Voltage_H_Temp,Voltage_L_Temp;
	UBYTE Ramp_STADYNA;
	UWORD Ramp_STEP,LOAD_OFF_STEP,Von_Delay,SettingValue,SR_Value;
	double Real_Value,Real_Value_Limit_Positive,Real_Value_Limit_Negative;
	double measure_gain;
	P3k_Time_Str	P3k_Time_Data;
	p3k_Ramp_Str	p3k_Ramp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
#if debug_tool
	unsigned short chek_1, chek_2;
#endif
#if Enable_Func_DisTime
	static UWORD RunStep=100;
#endif
	static BYTE next_flag = 1; //間隔一段時間, 第二次寫入 (debug next)
	TXData[3] = TX_LIST.ADDRL;				/* Set Addr L Value */
	switch(TX_LIST.ADDRL) {
	case Machine_Meas_Query:		/* Measure Query */
		TXData[1]=0x2;
		if(Model_Number==MODEL3031E)	measure_gain = MEASURE_GAIN_3031;//0.8;
		else 						measure_gain = MEASURE_GAIN_3032;


		FPGA_Status_Temp			= Acess_FPGA(FPGA_Status,NULL);
		p3k_Measure_Data.Real_Volt	= (Acess_FPGA(FPGA_V_Sense,NULL)*(ptrMODEL_TYPE->CV)[(Data_tmp->VRange)*3].Resolution)*measure_gain;
		p3k_Measure_Data.Real_Curr	= (Acess_FPGA(FPGA_I_Sense,NULL)*(ptrMODEL_TYPE->CC)[(Data_tmp->IRange)*10].Resolution);
		p3k_Measure_Data.Raw_Volt	= Acess_FPGA(FPGA_V_Sense_Raw,NULL)*measure_gain;
		p3k_Measure_Data.Raw_Curr	= Acess_FPGA(FPGA_I_Sense_Raw,NULL);

		Volt_Negative_Value = Measure_Process();
#if 1
		FPGA_Status_Temp &= (UWORD)0xFFDF;
#endif
		Update_Alarm_Status(FPGA_Status_Temp,Volt_Negative_Value);
		if((UTILITY.LOAD_CTL)&&((Data_tmp->CONF.VON_LATCH)||(UTILITY.SHORT_CTL))) {
			if((p3k_Measure_Data.VOLT<0.05) && (p3k_Measure_Data.CURR < 0.01)) {
				if(Clear_VON_Count < 30)
					Clear_VON_Count++;
				if(Clear_VON_Count==25)
					Acess_FPGA(FPGA_Control, Clear_VON_Latch);
			} else
				Clear_VON_Count = 0;
		}
#if 1 //2014.0911 //Adam_ni
		if (!UTILITY.LOAD_CTL) {
			//if((FPGA_W[5]&0x01)==0){
			if(RecoderAlarmStatus&0x1E0)
				Acess_FPGA(FPGA_Control, Clear_OCP_Latch|Clear_OPP_Latch|Clear_CPP_Latch);
		}
#endif
		if((Prog_Load == P3k_Chan_Data.Load_Type) || (Normal_Load == P3k_Chan_Data.Load_Type))
			GoNoGo_Process();
		exe_compensation();

		if(UTILITY.LOAD_CTL) {
#if Enable_loadtime_by_rtc
			if(Load_mS) {
				RctCountTemp = *(volatile unsigned long *) RTC_STAT;
				//if(RctFlag){
				if(RctFlag==1) {
					if(RctCountTemp!=RctCount) {
						RctCount = RctCountTemp;
						RctFlag = 2;
						Load_mS=1;
					}
				} else if(RctFlag==2) {
					Load_mS++;
					if(Load_mS>=GapCount) {
						RctFlag = 1;
						if(++LoadON_Time[0] > 59) {
							LoadON_Time[0] = NULL;
							if(++LoadON_Time[1] > 59) {
								LoadON_Time[1] = NULL;
								IntVal.b[0] = LoadON_Time[3];
								IntVal.b[1] = LoadON_Time[2];
								if(++IntVal.i > 999)
									LoadON_Time[0] = LoadON_Time[1] = LoadON_Time[2] = LoadON_Time[3] = IntVal.i = NULL;
								LoadON_Time[3] = IntVal.b[0];
								LoadON_Time[2] = IntVal.b[1];
							}
						}
					}
				} else { // 1st
					Load_mS++;
					if(RctCountTemp!=RctCount) {
						RctCount = RctCountTemp;
						GapCount = Load_mS;
					}
					if(Load_mS>50) {
						LoadON_Time[0]=1;
						Load_mS = 1;
						GapCount = 49-GapCount;
						if(GapCount>50)GapCount=49;
						RctFlag = 1;
					}
				}
			} else {
				LoadON_Time[0] = LoadON_Time[1] = LoadON_Time[2] = LoadON_Time[3] = NULL;
				RctCount = *(volatile unsigned long *) RTC_STAT;
				RctFlag = 0;
#if Enable_Battery_Discharge				
				BattDisp.AmpereHour = BattDisp.WattHour = 0;
#endif					
#if Enable_Func_DisTime
				if(FPGA_R[2]&0x0800)
#endif					
					Load_mS = 1;
			}
#else
			if(Load_mS++ > NULL) {
				if(Load_mS > (100/Fetch_Quer_time)) {
					Load_mS = 1;
					if(++LoadON_Time[0] > 59) {
						LoadON_Time[0] = NULL;
						if(++LoadON_Time[1] > 59) {
							LoadON_Time[1] = NULL;
							IntVal.b[0] = LoadON_Time[3];
							IntVal.b[1] = LoadON_Time[2];
							if(++IntVal.i > 999)
								LoadON_Time[0] = LoadON_Time[1] = LoadON_Time[2] = LoadON_Time[3] = IntVal.i = NULL;
							LoadON_Time[3] = IntVal.b[0];
							LoadON_Time[2] = IntVal.b[1];
						}
					}
				}
			} else
				LoadON_Time[0] = LoadON_Time[1] = LoadON_Time[2] = LoadON_Time[3] = NULL;
#endif
			IntVal.b[0] = LoadON_Time[3];
			IntVal.b[1] = LoadON_Time[2];
			p3k_Measure_Data.Hour = IntVal.i;
			p3k_Measure_Data.Min = LoadON_Time[1];
			p3k_Measure_Data.Sec = LoadON_Time[0];
#if Enable_Battery_Discharge
			Cacute_AH_WH();	 
#endif			
		} else {
			LoadON_Time[0] = LoadON_Time[1] = LoadON_Time[2] = LoadON_Time[3] = NULL;
			Load_mS = NULL;
		}
		if( (FPGA_Status_Temp&Acq4K_PTC_Done)&&(FPGA_Status_Temp&Acq4K_SWC_Done)&&p3k_Acq_4K_Measure_Data.Acq4K_Enable&&p3k_Acq_4K_Measure_Data.Acq4K_Ready ) {
			p3k_Acq_4K_Measure_Data.CC_Resolution = (ptrMODEL_TYPE->CC)[(Data_tmp->IRange)*10].Resolution;
			p3k_Acq_4K_Measure_Data.CV_Resolution = (ptrMODEL_TYPE->CV)[(Data_tmp->VRange)*3].Resolution;

			for(i=0 ; i<4096 ; i++) {
				p3k_Acq_4K_Measure_Data.VOLT[i] = (float)Acess_FPGA(FPGA_AcqMem_V_Sense_Ext_RV_Cont_Ref,NULL);
				p3k_Acq_4K_Measure_Data.CURR[i] = (float)Acess_FPGA(FPGA_AcqMem_I_Sense,NULL);
				p3k_Acq_4K_Measure_Data.WATT[i] = p3k_Acq_4K_Measure_Data.VOLT[i] * p3k_Acq_4K_Measure_Data.CURR[i];
			}

			for(i=0 ; i<10 ; i++) {
				PEL3000_LED_Control(LED_SHORT, Switch_ON);
				OSTimeDly(10);
				PEL3000_LED_Control(LED_SHORT, Switch_OFF);
				OSTimeDly(10);
			}
			PEL3000_LED_Control(LED_SHORT, UTILITY.SHORT_CTL);

			Acquire_Cont &= ~Enable_Acquire_System;

			if((Normal_Load==P3k_Chan_Data.Load_Type)||(OCP_Load==P3k_Chan_Data.Load_Type))
				FPGA_Ctrl();
			else
				Acess_FPGA(FPGA_On_Off_Reference_Setting, P_Sense |Acquire_Cont |Set_Protection_Ref_Adjust_ON |Set_Sequence_Mode |Set_Load_ON);

			p3k_Acq_4K_Measure_Data.Acq4K_Enable= 0;
			p3k_Acq_4K_Measure_Data.Acq4K_Ready	= 0;

			if(P_CONF_OTHER==M_num)
				DataRedrawFlag |= PARA_CHANGE;
		}
		break;
	case Machine_Init_Query:		/* Init Query */
		FPGA_Data = Acess_FPGA(FPGA_Machine_Status, NULL);
		PEL3000_FPGA_Date = (FPGA_Data&0xFFF0)>> 4;
		Data_tmp->INFO.MACHTYPE = (UBYTE)(FPGA_Data&0x000F);
#if test_debug
		//Data_tmp->INFO.MACHTYPE = 4;//(UBYTE)(FPGA_Data&0x000F);
		Data_tmp->INFO.MACHTYPE = debug_MACHTYPE;
#endif
#if 1
		FPGA_W[255] = Versiondate;
		FPGA_R[255] = Version_2;
#endif
		TXData[1] = 0x04;
		break;
	case Machine_Input_Trigger:		/* Load On Time */
		Acess_FPGA(FPGA_Control, Acquire_Trigger_Pulse);
		break;
	case Machine_Seq_ID:	/* Machine Status */
		FPGA_Data = Acess_FPGA(FPGA_Sequence_Mode_Set_ID,NULL);

		if((FPGA_Data&Wait_For_Trig)&&(!Prog_Seq_Data.MANUAL_CTRL)) {
			Prog_Seq_Data.MANUAL_CTRL = 1;

			MenuRedrawFlag |= MENU_CHANGE;
		} else if(!(FPGA_Data & Wait_For_Trig)) {
			Prog_Seq_Data.MANUAL_CTRL = 0;
			MenuRedrawFlag |= MENU_CHANGE;
		}
		if(((FPGA_Data&0xF000)==Run_Status_CX_Mode)&&((p3k_Measure_Data.Sec)||(p3k_Measure_Data.Min))) {
			Prog_Seq_Data.SEQ_Complete = 1;
			break;
		}
		FPGA_Data &= Show_Now_Run_Point;
		if((M_num == 0x17)&&(FPGA_Data))//SeqSyncWaitStep
			Prog_Seq_Data.Display_Count = FPGA_Data-SeqSyncWaitStep;
		else
			Prog_Seq_Data.Display_Count = FPGA_Data;
#if Enable_Func_DisTime
		if(RunStep != Prog_Seq_Data.Display_Count){
			RunStep = Prog_Seq_Data.Display_Count;
			StepStarTime = p3k_Measure_Data.Hour*3600 +p3k_Measure_Data.Min*60+p3k_Measure_Data.Sec;
		}
#endif

		if (Prog_Seq_Data.MANUAL_CTRL) {	//間隔一段時間, 第二次寫入 (debug next)
			if (next_flag ==0)
				MenuRedrawFlag |= MENU2_CHANGE;
			else
				next_flag--;
		} else
			next_flag = 10;

		for(i=0 ; i<16 ; i++)
			Prog_Seq_Data.FPGA_Loop_Count[i] = Acess_FPGA(FPGA_Read_JP_Counter,NULL);
		break;
	case Machine_Prot_Status:	/* Protection Status */
		Prot_Setting_Process();
#if Enable_OPPOCP_off
		if(Data_tmp->PROT.OPP_SET==2) {
			dat = Step_To_CNT(((ptrMODEL_TYPE->PROT)[PROT_OPP_H].Max*22/21),p3k_Cal_data.Protection[IRange_High].OPP_Gain,p3k_Cal_data.Protection[IRange_High].OPP_Offset);
			///dat = p3k_Cal_data.Protection[IRange_High].CPP*22/21;
			if(Model_Number==MODEL3031E)
				if(dat>51000)dat=51000;
			else	
				if(dat>56000)dat=56000;
			Acess_FPGA(FPGA_CX_H_OPP, dat);
			Acess_FPGA(FPGA_CX_L_OPP, dat);
		} else {
			Acess_FPGA(FPGA_CX_H_OPP, p3k_Cal_data.Protection[IRange_High].OPP);
			Acess_FPGA(FPGA_CX_L_OPP, p3k_Cal_data.Protection[IRange_Low].OPP);
		}
		if(Data_tmp->PROT.OCP_SET==2) {
			dat = Step_To_CNT(ptrMODEL_TYPE->PROT[1].Max,p3k_Cal_data.Protection[1].OCP_Gain,p3k_Cal_data.Protection[1].OCP_Offset);
			dat = dat*22/21;
			if(dat>Default_Cal_Prot_DA_OCP)dat=Default_Cal_Prot_DA_OCP;
			Acess_FPGA(FPGA_CX_H_OCP, dat);
			dat = Step_To_CNT(ptrMODEL_TYPE->PROT[0].Max,p3k_Cal_data.Protection[1].OCP_Gain,p3k_Cal_data.Protection[1].OCP_Offset);
			if(dat>Default_Cal_Prot_DA_OCP)dat=Default_Cal_Prot_DA_OCP;
			Acess_FPGA(FPGA_CX_L_OCP, dat);
		} else {
			Acess_FPGA(FPGA_CX_H_OCP, p3k_Cal_data.Protection[IRange_High].OCP);
			Acess_FPGA(FPGA_CX_L_OCP, p3k_Cal_data.Protection[IRange_Low].OCP);
		}
#endif
		break;
	case 0x05:	/* Alarm Clear */

		break;
	case Machine_modeHandle:	/* Chan Mode */
		FPGA_Ctrl();
		break;
	case Machine_Pause_Prog:	/* Chan ID */
		if(Prog_Seq_Data.SEQ_Stop_Continue) {
			P_Sense |= Wait_For_Trig;
			Acess_FPGA(FPGA_On_Off_Reference_Setting, P_Sense | Acquire_Cont |Set_Protection_Ref_Adjust_ON |Set_Sequence_Mode |Set_Load_ON|Set_Wait_ON);
		} else {
			P_Sense &= ~(Wait_For_Trig);
			Acess_FPGA(FPGA_On_Off_Reference_Setting, P_Sense | Acquire_Cont |Set_Protection_Ref_Adjust_ON |Set_Sequence_Mode |Set_Load_ON);
		}
		break;
	case 0x08:	/* Run Program Status */

		break;
	case 0x09:	/* Active Channel */

		break;
	case 0x0a:	/* Short Channel */
		FPGA_Ctrl();		// 2010_05
		break;
	case Machine_Load_OnOff:	/* Load On & Off */
		P_Sense &= ~(Wait_For_Trig);
		switch(P3k_Chan_Data.Load_Type){
		case Normal_Load:
		case OCP_Load ... CLED_Load:
			if( (p3k_Measure_Data.Alarm)&&(UTILITY.LOAD_CTL) ) {
			} else
				FPGA_Ctrl();
			break;		
		default:
			if(UTILITY.LOAD_CTL) {
				Acess_FPGA(FPGA_H_Circuit_Switch_Control_0,	Prog_Seq_Data.FPGA_Seq_Data[1024].CS0_Setting);
				Acess_FPGA(FPGA_H_Circuit_Switch_Control_1,	Prog_Seq_Data.FPGA_Seq_Data[1024].CS1_Setting);
				Acess_FPGA(FPGA_H_Level_Slew_Rate,			Prog_Seq_Data.FPGA_Seq_Data[1024].SR_Setting);
				Acess_FPGA(FPGA_H_Level_Setting,			Prog_Seq_Data.FPGA_Seq_Data[1024].Level_Setting);

				if(P3k_Chan_Data.Load_Type!=Prog_Load) {
					P3k_Chan_Data.CURRMODE	= Prog_Seq_Data.FPGA_Seq_Data[1024].SEQ_Mode;
					P3k_Chan_Data.VRange	= Prog_Seq_Data.FPGA_Seq_Data[1024].SEQ_Range/2;
					P3k_Chan_Data.IRange	= Prog_Seq_Data.FPGA_Seq_Data[1024].SEQ_Range%2;
					switch(P3k_Chan_Data.CURRMODE) {
					default:/*CC_MODE:*/
						Debug_printf("Machine_Load_OnOff\n");
					case CC_MODE:
						P3k_Chan_Data.CC.ABSELECT	= A_Value;
						P3k_Chan_Data.CC.STADYNA	= Function_Static;
						break;
					case CR_MODE:
						P3k_Chan_Data.CR.ABSELECT	= A_Value;
						P3k_Chan_Data.CR.STADYNA	= Function_Static;
						break;
					case CV_MODE:
						P3k_Chan_Data.CV.ABSELECT	= A_Value;
						P3k_Chan_Data.CV.STADYNA	= Function_Static;

						break;
					case CP_MODE:
						P3k_Chan_Data.CP.ABSELECT	= A_Value;
						P3k_Chan_Data.CP.STADYNA	= Function_Static;
						break;
					}
					RestoreRealChan();
				}
				Acess_FPGA(FPGA_On_Off_Reference_Setting, P_Sense | Acquire_Cont |Set_Protection_Ref_Adjust_ON |Set_Sequence_Mode |Set_Load_ON);

			} else {
				check_cr_range();//Adam_2016_0414
				Acess_FPGA(FPGA_On_Off_Reference_Setting, P_Sense | Acquire_Cont |Set_Protection_Ref_Adjust_ON |Set_Sequence_Mode |Set_Load_OFF);
			}
			break;
		}		
		break;
	case 0x0c:	/* Remote / Local Control */
		tmp = 0x00;
		if(REM_CONT)
			tmp |= 0x01;		/* Bit 0 */

		if(UTILITY.BEEP_ONOFF)
			tmp |= 0x02;		/* Bit 1 */

		if(UTILITY.Rotate_Knob)
			tmp |= 0x08;		/* Bit 3 */
		break;
	case 0x0d:
		TXData[4] = ChanNo+1;
		break;
	case 0x0e:
		TXData[5] = Disp_Select;
		break;
	case 0x0f:
		TXData[5] = Disp_Mode;
		break;
	case Machine_OCP_Level:	/* OCP Level */

		dat = Step_To_CNT(ptrMODEL_TYPE->PROT[0].Max,p3k_Cal_data.Protection[1].OCP_Gain,p3k_Cal_data.Protection[1].OCP_Offset);
		Machine_Data = Data_tmp->PROT.OCP[IRange_High];
		p3k_Cal_data.Protection[IRange_High].OCP = Step_To_CNT(Machine_Data,p3k_Cal_data.Protection[IRange_High].OCP_Gain,p3k_Cal_data.Protection[IRange_High].OCP_Offset);
		p3k_Cal_data.Protection[IRange_Low].OCP = p3k_Cal_data.Protection[IRange_High].OCP ;
		if(p3k_Cal_data.Protection[IRange_High].OCP> dat) {
			p3k_Cal_data.Protection[IRange_Low].OCP = dat;
		} else {
			p3k_Cal_data.Protection[IRange_Low].OCP = p3k_Cal_data.Protection[IRange_High].OCP ;
		}
		check_max_protection();

		if(Data_tmp->PROT.OCP_SET==2) {
			dat = Step_To_CNT(ptrMODEL_TYPE->PROT[1].Max,p3k_Cal_data.Protection[1].OCP_Gain,p3k_Cal_data.Protection[1].OCP_Offset);
			dat = dat*22/21;
			if(dat>Default_Cal_Prot_DA_OCP)dat=Default_Cal_Prot_DA_OCP;
			Acess_FPGA(FPGA_CX_H_OCP, dat); ///Default_Cal_Prot_DA_OCP);
			if(dat>Default_Cal_Prot_DA_OCP)dat=Default_Cal_Prot_DA_OCP;
			dat = Step_To_CNT(ptrMODEL_TYPE->PROT[0].Max,p3k_Cal_data.Protection[1].OCP_Gain,p3k_Cal_data.Protection[1].OCP_Offset);
			Acess_FPGA(FPGA_CX_L_OCP, dat);
		} else {
			if((P3k_Chan_Data.IRange==0)&&(p3k_Cal_data.Protection[1].OCP>p3k_Cal_data.Protection[0].OCP)) {
				Prot_Setting_Process();
			}
			Acess_FPGA(FPGA_CX_H_OCP, p3k_Cal_data.Protection[IRange_High].OCP);
			Acess_FPGA(FPGA_CX_L_OCP, p3k_Cal_data.Protection[IRange_Low].OCP);
		}
		Prot_Setting_Process();
		FPGA_Ctrl();
		break;
	case Machine_OPP_Level:	/* OPP Level */

		Machine_Data = Data_tmp->PROT.OPP[IRange_High];
		p3k_Cal_data.Protection[IRange_High].OPP = Step_To_CNT(Machine_Data,p3k_Cal_data.Protection[IRange_High].OPP_Gain,p3k_Cal_data.Protection[IRange_High].OPP_Offset);
		p3k_Cal_data.Protection[LOW_RANGE].OPP = p3k_Cal_data.Protection[HIGH_RANGE].OPP;

		check_max_protection();

		if(Data_tmp->PROT.OPP_SET==2) {
			dat = Step_To_CNT(((ptrMODEL_TYPE->PROT)[PROT_OPP_H].Max*22/21),p3k_Cal_data.Protection[IRange_High].OPP_Gain,p3k_Cal_data.Protection[IRange_High].OPP_Offset);
			if(dat>51000)dat=51000; /// = p3k_Cal_data.Protection[IRange_High].CPP*22/21;
			Acess_FPGA(FPGA_CX_H_OPP, dat);
			Acess_FPGA(FPGA_CX_L_OPP, dat);
			///printf("dat2:%d\n",dat);///Adam_test
		} else {
			Acess_FPGA(FPGA_CX_H_OPP, p3k_Cal_data.Protection[IRange_High].OPP);
			Acess_FPGA(FPGA_CX_L_OPP, p3k_Cal_data.Protection[IRange_Low].OPP);
		}

		FPGA_Ctrl();
		break;
	case 0x18:				/* Init Query */
		TXData[1]=0x04;
		break;
	case Machine_Test_Query:		/* Test Query */
		measure_gain = 0.8;
		p3k_Measure_Data.Real_Volt	= ( Acess_FPGA(FPGA_V_Sense,NULL)*(ptrMODEL_TYPE->CV)[(Data_tmp->VRange)*3].Resolution)*measure_gain;
		p3k_Measure_Data.Real_Curr	= ( Acess_FPGA(FPGA_I_Sense,NULL)*(ptrMODEL_TYPE->CC)[(Data_tmp->IRange)*10].Resolution);
		p3k_Measure_Data.Raw_Volt	= Acess_FPGA(FPGA_V_Sense_Raw,NULL)*measure_gain;
		p3k_Measure_Data.Raw_Curr	= Acess_FPGA(FPGA_I_Sense_Raw,NULL);
		break;
	case Machine_Von_Delay:
		if(0){//(Data_tmp->CURRMODE ==CR_MODE) {
			if(Data_tmp->CONF.D_Von_Delay_CR<= 4900)
				Von_Delay = 0;
			else
				Von_Delay = Data_tmp->CONF.D_Von_Delay_CR;
		} else {
			if(Data_tmp->CONF.D_Von_Delay <= 1900)
				Von_Delay = 0;
			else
				Von_Delay = Data_tmp->CONF.D_Von_Delay;
		}
		Acess_FPGA(FPGA_Von_Delay, Von_Delay);
		break;
	case Machine_Von_Voltage:	/* Von Voltage */
		if(Data_tmp->CONF.VON_VOLT[1] < 30)
			Voltage_H_Temp = 30;
		else{
			if(Model_Number==MODEL3031E)	 Voltage_H_Temp = Data_tmp->CONF.VON_VOLT[1]/MEASURE_GAIN_3031*2;
			else						 Voltage_H_Temp = Data_tmp->CONF.VON_VOLT[1]/MEASURE_GAIN_3032;
		}
		if(Data_tmp->CONF.VON_VOLT[0] < 50)
			Voltage_L_Temp = 50;
		else{
			if(Model_Number==MODEL3031E)	Voltage_L_Temp = (Data_tmp->CONF.VON_VOLT[0]/MEASURE_GAIN_3031*2);
			else						Voltage_L_Temp = (Data_tmp->CONF.VON_VOLT[0]/MEASURE_GAIN_3032);
		}

		Acess_FPGA(FPGA_VON_H, Voltage_H_Temp);
		Acess_FPGA(FPGA_VON_L, Voltage_L_Temp);
		//FPGA_Ctrl();
		break;
	case Machine_Soft_Start:    /* Soft Start */
		P3k_Time_Data.Hour		= 0;
		P3k_Time_Data.Minute		= 0;
		P3k_Time_Data.Second		= 0;
#if Enable_SoftStartOn
		if((P3k_Chan_Data.Load_Type==Normal_Load)||(P3k_Chan_Data.Load_Type==BATT_Load)){
			if(Data_tmp->CONF.SOFT_START>0)
				P3k_Time_Data.MilliSecond = Data_tmp->CONF.SOFT_START;
			else {
				if(p3k_Measure_Data.VOLT>0.3)
					P3k_Time_Data.MilliSecond = 0;
				else
					P3k_Time_Data.MilliSecond = 1;
			}
		} else {
			P3k_Time_Data.MilliSecond = 0;
		}
#else
		P3k_Time_Data.MilliSecond	= Data_tmp->CONF.SOFT_START;
#endif
#if Enable_NSEQ_Usec
	P3k_Time_Data.MilliSecond *= 20;
#endif

		switch(Data_tmp->CURRMODE) {
		case CC_MODE: /* CC Mode */
			Ramp_STADYNA = Data_tmp->CC.ABSELECT;
			if(Data_tmp->CC.STADYNA) {
				Ramp_STEP = Data_tmp->CC.DYNA[Data_tmp->IRange].LEVEL1;
				SR_Value  = Data_tmp->CC.DYNA[Data_tmp->IRange].SLEWRATEUP;
			} else {
				if(Data_tmp->CC.ABSELECT)
					Ramp_STEP = Data_tmp->CC.STA[Data_tmp->IRange].VALUE2;
				else
					Ramp_STEP = Data_tmp->CC.STA[Data_tmp->IRange].VALUE1;
				SR_Value = Data_tmp->CC.STA[Data_tmp->IRange].SLEWRATEUP;
			}
			if((Ramp_STEP<=3000)&&(SR_Value<=25)) {
				SettingValue = 0;
			}

			if(Data_tmp->IRange == HIGH_RANGE)
				LOAD_OFF_STEP = Min_Startup_Setting_H;
			else
				LOAD_OFF_STEP = Min_Startup_Setting_L;
			break;
		case CR_MODE:
			Ramp_STADYNA = Data_tmp->CR.ABSELECT;
			if(Data_tmp->CR.STADYNA) {
				Ramp_STEP = Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL1;
				SR_Value  = Data_tmp->CR.DYNA[Data_tmp->IRange].SLEWRATEUP;
			} else {
				if(Data_tmp->CR.ABSELECT)
					Ramp_STEP = Data_tmp->CR.STA[Data_tmp->IRange].VALUE2;
				else
					Ramp_STEP = Data_tmp->CR.STA[Data_tmp->IRange].VALUE1;
				SR_Value = Data_tmp->CR.STA[Data_tmp->IRange].SLEWRATEUP;
			}
			if((Ramp_STEP<=3000)&&(SR_Value<=25)) {
				SettingValue = 0;
			}
			if(Data_tmp->IRange == HIGH_RANGE)
				LOAD_OFF_STEP = Min_Startup_Setting_H;
			else
				LOAD_OFF_STEP = Min_Startup_Setting_L;
			break;
		case CP_MODE:		/* CP Mode */
			Ramp_STADYNA = Data_tmp->CP.ABSELECT;

			Ramp_STEP = 1;
			LOAD_OFF_STEP = Min_Startup_Setting_H;
			if(Data_tmp->CP.ABSELECT)
				Ramp_STEP = Data_tmp->CP.STA[Data_tmp->IRange].VALUE2;
			else
				Ramp_STEP = Data_tmp->CP.STA[Data_tmp->IRange].VALUE1;

			break;
		}

		if(Data_tmp->CONF.Ext_Setting.Control) {
			if(Data_tmp->CONF.Ext_Setting.Control==Ext_Setting_V)
				Ramp_STEP = p3k_Cal_data.Ext_V_CC[Data_tmp->IRange];
			else
				Ramp_STEP = p3k_Cal_data.Ext_R_CC[Data_tmp->IRange];
		}
		SettingValue = get_response(Data_tmp->CURRMODE); //Adam_2015_1118
		if(Data_tmp->CONF.Ext_Setting.MultilPara == 1)SettingValue |= Bit7;

		p3k_Ramp_Data = Seq_Ramp_Process(Data_tmp->CURRMODE, Data_tmp->IRange, Data_tmp->VRange, Ramp_STADYNA, LOAD_OFF_STEP, Ramp_STEP, P3k_Time_Data);
		//Acess_FPGA(FPGA_Soft_Start_Circuit_Switch_1,p3k_Ramp_Data.Delta_TimeBase|p3k_Ramp_Data.Delta_Response|SettingValue);
		Acess_FPGA(FPGA_Soft_Start_Circuit_Switch_1,p3k_Ramp_Data.Delta_TimeBase|SettingValue);
		Acess_FPGA(FPGA_Soft_Start_Delta_T,			p3k_Ramp_Data.DeltaTime);
		Acess_FPGA(FPGA_Soft_Start_Delta_VL,		p3k_Ramp_Data.Delta_Value_Low);
		Acess_FPGA(FPGA_Soft_Start_Delta_VH,		p3k_Ramp_Data.Delta_Value_High);
		Acess_FPGA(FPGA_Soft_Start_Slew_Rate,		p3k_Ramp_Data.Delta_SR_Set);
		FPGA_Ctrl();
		break;
	case Machine_SyncTrigg:
		SettingValue = Set_Trigger_Input;//(Set_Trigger_Input | Set_Wait_ON);
		if(FPGA05_Writ_flag)FPGA_05_statue |= SettingValue;
		else				FPGA_05_statue &= ~(SettingValue);
		Acess_FPGA(FPGA_On_Off_Reference_Setting,FPGA_05_statue);
		break;
	case Machine_TrigInDelay:
		Acess_FPGA(FPGA_Trig_In_Delay, Data_tmp->CONF.Para_Data.TrigInDelay);
		break;
	case Machine_TrigOutWidth:
		if(P3k_Disp_Data.CONF.Para_Data.TrigOut)
			Acess_FPGA(FPGA_Trig_Out_Width,	P3k_Disp_Data.CONF.Para_Data.TrigOutWidth);
		else
			Acess_FPGA(FPGA_Trig_Out_Width,	0);
		break;	
	case 0x30:	/* Load Sync Delay Time */
		//TXData[4] = Data_tmp->UTILITY.LOADTIME;
		break;
	case 0x32:	/* GO / NG Delay Time */
		TXData[4] = Data_tmp->P_F_Delay;
		break;
	case 0x34:	/* Test */
		break;
	case 0x40:	/* Write Serial Number of Slave*/
		break;
	case 0x50:	/* Read Serial Number of Slave*/
		break;
	case 0x60:	/* Common <---> Upgrading*/
		break;
#if debug_tool
	case 0x70://Machine_FGPA_TEST:
		for (chek_1=1000; chek_1<=1123; chek_1++) {
			Acess_FPGA(FPGA_Test_Register, chek_1);
			chek_2 = Acess_FPGA(FPGA_Test_Register, chek_1);
			if(chek_1!=chek_2)	FPGA_err_cnt++;
			FPGA_test_cnt++;
		}
		break;
#endif
	case '\x90':	/* Common <---> Upgrading*/
		break;
	case '\xA0':		/* Acquirement Rate Setting */ /*Machine_Enable_Acq4K*/
	case Machine_Enable_Acq4K:
		if(p3k_Acq_4K_Measure_Data.Acq4K_Enable) {
			Acquire_Cont &= ~Enable_Acquire_System;
			FPGA_Ctrl();
			Acquire_Cont &= ~Enable_Acquire_Sequence;
			Acquire_Cont |= Enable_Acquire_System;
			Acess_FPGA(FPGA_Acquire_System_Sampling_Rate, 		p3k_Acq_4K_Measure_Data.Acq4K_Interval);
			Acess_FPGA(FPGA_Acquire_System_Pre_Trigger_Counter, p3k_Acq_4K_Measure_Data.Acq4K_PTC);
			Acess_FPGA(FPGA_Acquire_System_Sweep_Counter, 		p3k_Acq_4K_Measure_Data.Acq4K_SWC);
		} else {
			Acquire_Cont &= ~Enable_Acquire_System;
			p3k_Acq_4K_Measure_Data.Acq4K_Ready = 0;
		}
		FPGA_Ctrl();
		/*Wait Acquire PTC*/
		if(p3k_Acq_4K_Measure_Data.Acq4K_Enable) {
			//Debug_printf("Wait Acq4K PTC\n");
			TimeOut = 500;
			while(1) {
				OSTimeDly(1);
				TimeOut--;
				if( (TimeOut==0)||(Acess_FPGA(FPGA_Status,NULL)&Acq4K_PTC_Done) )
					break;
			}
			if(TimeOut)
				Debug_printf("Acq4K PTC Finish\n");
			else {
				Debug_printf("Acq4K PTC Error\n");
				Menu_Message(" Acq4K PTC Error!! ",50,210);
				CtrlFlag1 |= Disp_Middle_Message;
				DMA_Update_Flag = 1;
				Update_Panel();
				OSTimeDly(200);
			}
			p3k_Acq_4K_Measure_Data.Acq4K_Ready = 1;
			Acquire_Cont |= Enable_Acquire_Sequence;
		}
		break;
	case '\xD0':
	case Machine_Setting_IMON:
		Acess_FPGA(FPGA_Rear_IMON_Output_Adjust,p3k_Cal_data.Rear_IMON[P3k_Chan_Data.IRange]);
		//Acess_FPGA(FPGA_Front_IMON_Output_Adjust,p3k_Cal_data.Front_IMON[P3k_Chan_Data.IRange]);
		break;
	default:
		break;
	}
}

void SoftStartDoubleCheck (void) {
	p3k_send_tx_list tx_data;
	if((p3k_Measure_Data.VOLT<0.01)&&(UTILITY.LOAD_CTL)) {
		tx_data.ADDRH = Machine_Command;
		tx_data.ADDRL = Machine_Soft_Start;
		SendTXData(&tx_data);
	}
}

void CCModeSetupFun(void) {
	UWORD dat;
	char tmp;
	int cnt;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	tmp = Data_tmp->IRange;
	switch(TX_LIST.ADDRL) {
	case 0x00:
		tmp = 0x00;
		if( Data_tmp->IRange)
			tmp |= 0x01;
		if( Data_tmp->CC.STADYNA)
			tmp |= 0x02;
		if( Data_tmp->CC.ABSELECT)	/* A_B SELECT */
			tmp |= 0x10;
		if( Data_tmp->VRange)		/* Vrange */
			tmp |= 0x40;
		break;
	case 0x01:
		if(UTILITY.LOAD_CTL)
			Acess_FPGA(FPGA_On_Off_Reference_Setting, P_Sense |Acquire_Cont |Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
	case 0x10:
		SoftStartDoubleCheck();
		dat = Data_tmp->CC.STA[tmp].VALUE1;
		break;
	case 0x12:
		SoftStartDoubleCheck();
		dat = Data_tmp->CC.STA[tmp].VALUE2;
		break;
	case 0x20:											/* SlewRate Up */
		dat = Data_tmp->CC.STA[tmp].SLEWRATEUP;
		break;
	case 0x22:											/* SlewRate Down */
		dat = Data_tmp->CC.STA[tmp].SLEWRATEDN;
		break;
	case 0x24:
		FPGA_Ctrl();
	case 0x30:											/* Spec Center Value */
		TXData[3]=0x30;
		if(tmp)
			TXData[3] = TXData[3] | 0x80;
		dat = Data_tmp->CC.STA[tmp].HIGHVAL;
		TXData[4] = (dat & 0xff00) >> 8;
		TXData[5] = dat & 0x00ff;
		dat = Data_tmp->CC.STA[tmp].LOWVAL;
		TXData[6] = (dat & 0xff00) >> 8;
		TXData[7] = dat & 0x00ff;
		break;
	case 0x40:
		SoftStartDoubleCheck();
		dat = Data_tmp->CC.DYNA[tmp].LEVEL1;
		break;
	case 0x42:
		SoftStartDoubleCheck();
		dat = Data_tmp->CC.DYNA[tmp].LEVEL2;
		break;
	case 0x50:
		dat = Data_tmp->CC.DYNA[tmp].SLEWRATEUP;
		break;
	case 0x52:
		dat = Data_tmp->CC.DYNA[tmp].SLEWRATEDN;
		break;
	case 0x54:
		dat = Data_tmp->CC.DYNA[tmp].TIME1;
		if(Data_tmp->CC.DYNA[tmp].T1_RANGE)
			dat|=0x8000;
		break;
	case 0x56:
		dat = Data_tmp->CC.DYNA[tmp].TIME2;
		if(Data_tmp->CC.DYNA[tmp].T2_RANGE)
			dat|=0x8000;
		break;
	case 0x60:
		TXData[3]=0x60;
		if(tmp)
			TXData[3] = TXData[3] | 0x80;
		dat = Data_tmp->CC.DYNA[tmp].HIGHVAL;
		TXData[4] = (dat & 0xff00) >> 8;
		TXData[5] = dat & 0x00ff;
		dat = Data_tmp->CC.DYNA[tmp].LOWVAL;
		TXData[6] = (dat & 0xff00) >> 8;
		TXData[7] = dat & 0x00ff;
		break;
	default:
		break;
	}
}

void CRModeSetupFun(void) {
	UWORD dat;
	char tmp;
	int cnt;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;

	tmp = Data_tmp->IRange;
	switch(TX_LIST.ADDRL) {
	case 0x00:
		TXData[3] = TX_LIST.ADDRL;
		tmp = 0x00;
		if( Data_tmp->IRange)		tmp |= 0x01;
		if( Data_tmp->CR.STADYNA)	tmp |= 0x02;
		if( Data_tmp->CR.ABSELECT)	tmp |= 0x10;	/* A_B SELECT */
		if( Data_tmp->VRange)		tmp |= 0x40;	/* Vrange */
		TXData[4] = tmp;
		break;
	case 0x01:
		if(UTILITY.LOAD_CTL)
			Acess_FPGA(FPGA_On_Off_Reference_Setting, P_Sense |Acquire_Cont |Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
	case 0x10:											/* A Value */
		SoftStartDoubleCheck();
		dat = Data_tmp->CR.STA[tmp].VALUE1;
		break;
	case 0x12:											/* B Value */
		SoftStartDoubleCheck();
		dat = Data_tmp->CR.STA[tmp].VALUE2;
		break;
	case 0x20:											/* SlewRate Up */
		dat = Data_tmp->CR.STA[tmp].SLEWRATEUP;
		break;
	case 0x22:											/* SlewRate Down */
		dat = Data_tmp->CR.STA[tmp].SLEWRATEDN;
		break;
	case 0x24:
		FPGA_Ctrl();
	case 0x30:
		TXData[3]=0x30;
		if(tmp)
			TXData[3] = TXData[3] | 0x80;
		dat = Data_tmp->CR.STA[tmp].HIGHVAL;
		TXData[4] = (dat & 0xff00) >> 8;
		TXData[5] = dat & 0x00ff;
		dat = Data_tmp->CR.STA[tmp].LOWVAL;
		TXData[6] = (dat & 0xff00) >> 8;
		TXData[7] = dat & 0x00ff;
		break;
	case 0x40:
		SoftStartDoubleCheck();
		dat = Data_tmp->CR.DYNA[tmp].LEVEL1;
		break;
	case 0x42:
		SoftStartDoubleCheck();
		dat = Data_tmp->CR.DYNA[tmp].LEVEL2;
		break;
	case 0x50:
		dat = Data_tmp->CR.DYNA[tmp].SLEWRATEUP;
		break;
	case 0x52:
		dat = Data_tmp->CR.DYNA[tmp].SLEWRATEDN;
		break;
	case 0x54:
		dat = Data_tmp->CR.DYNA[tmp].TIME1;
		if(Data_tmp->CR.DYNA[Data_tmp->IRange].T1_RANGE)
			dat|=0x8000;
		break;
	case 0x56:
		dat = Data_tmp->CR.DYNA[tmp].TIME2;
		if(Data_tmp->CR.DYNA[Data_tmp->IRange].T2_RANGE)
			dat|=0x8000;
		break;
	case 0x60:
		TXData[3]=0x60;
		if(tmp)
			TXData[3] = TXData[3] | 0x80;
		dat = Data_tmp->CR.DYNA[tmp].HIGHVAL;
		TXData[4] = (dat & 0xff00) >> 8;
		TXData[5] = dat & 0x00ff;
		dat = Data_tmp->CR.DYNA[tmp].LOWVAL;
		TXData[6] = (dat & 0xff00) >> 8;
		TXData[7] = dat & 0x00ff;
		break;
	default:
		break;
	}
}

void CVModeSetupFun(void) {
	UWORD dat;
	char tmp;
	int cnt;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	tmp = Data_tmp->IRange;
	switch(TX_LIST.ADDRL) {
	case 0x00:
		TXData[3] = TX_LIST.ADDRL;
		tmp = 0x00;
		if( Data_tmp->IRange)
			tmp |= 0x01;
		if( Data_tmp->CV.ABSELECT)	/* A_B SELECT */
			tmp |= 0x10;
		if( Data_tmp->CV.RESPONSE)
			tmp |= 0x20;
		if( Data_tmp->VRange)	/* Vrange */
			tmp |= 0x40;
		TXData[4] = tmp;
		break;
	case 0x01:
		if(UTILITY.LOAD_CTL)
			Acess_FPGA(FPGA_On_Off_Reference_Setting, P_Sense |Acquire_Cont |Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
	case 0x10:											/* A Value */
		dat = Data_tmp->CV.STA[tmp].VALUE1;
		break;
	case 0x12:											/* B Value */
		dat = Data_tmp->CV.STA[tmp].VALUE2;
		break;
	case 0x14:
		dat = Data_tmp->CV.STA[tmp].CURRENTLIMIT;
		break;
	case 0x30:
		TXData[3]=0x30;
		if(tmp)
			TXData[3] = TXData[3] | 0x80;
		dat = Data_tmp->CV.STA[tmp].HIGHVAL;
		TXData[4] = (dat & 0xff00) >> 8;
		TXData[5] = dat & 0x00ff;
		dat = Data_tmp->CV.STA[tmp].LOWVAL;
		TXData[6] = (dat & 0xff00) >> 8;
		TXData[7] = dat & 0x00ff;
		break;
	default:
		break;
	}
}

void CPModeSetupFun(void) {
	UWORD dat;
	char tmp;
	int cnt;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	tmp = Data_tmp->IRange;
	switch(TX_LIST.ADDRL) {
	case 0x00:
		TXData[3] = TX_LIST.ADDRL;
		tmp = 0x00;
		if( Data_tmp->IRange)
			tmp |= 0x01;
		if( Data_tmp->CP.STADYNA)
			tmp |= 0x02;
		if( Data_tmp->CP.ABSELECT)	/* A_B SELECT */
			tmp |= 0x10;
		if( Data_tmp->VRange)	/* Vrange */
			tmp |= 0x40;
		break;
	case 0x01:
		if(UTILITY.LOAD_CTL)
			Acess_FPGA(FPGA_On_Off_Reference_Setting, P_Sense |Acquire_Cont |Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
	case 0x10:											/* A Value */
		//SoftStartDoubleCheck();
		dat = Data_tmp->CP.STA[tmp].VALUE1;
		break;
	case 0x12:											/* B Value */
		//SoftStartDoubleCheck();
		dat = Data_tmp->CP.STA[tmp].VALUE2;
		break;
	case 0x24:
		FPGA_Ctrl();
	case 0x30:											/* Spec Center Value */
		TXData[3]=0x30;
		if(tmp)
			TXData[3] = TXData[3] | 0x80;
		dat = Data_tmp->CP.STA[tmp].HIGHVAL;
		TXData[4] = (dat & 0xff00) >> 8;
		TXData[5] = dat & 0x00ff;
		dat = Data_tmp->CP.STA[tmp].LOWVAL;
		TXData[6] = (dat & 0xff00) >> 8;
		TXData[7] = dat & 0x00ff;
		break;
	case 0x40:
		//SoftStartDoubleCheck();
		dat = Data_tmp->CP.DYNA[tmp].LEVEL1;
		break;
	case 0x42:
		//SoftStartDoubleCheck();
		dat = Data_tmp->CP.DYNA[tmp].LEVEL2;
		break;
	case 0x54:
		dat = Data_tmp->CP.DYNA[tmp].TIME1;
		if(Data_tmp->CP.DYNA[tmp].T1_RANGE)
			dat|=0x8000;
		break;
	case 0x56:
		dat = Data_tmp->CP.DYNA[tmp].TIME2;
		if(Data_tmp->CP.DYNA[tmp].T2_RANGE)
			dat|=0x8000;
		break;
	case 0x60:
		TXData[3]=0x60;
		if(tmp)
			TXData[3] = TXData[3] | 0x80;
		dat = Data_tmp->CP.DYNA[tmp].HIGHVAL;
		TXData[4] = (dat & 0xff00) >> 8;
		TXData[5] = dat & 0x00ff;
		dat = Data_tmp->CP.DYNA[tmp].LOWVAL;
		TXData[6] = (dat & 0xff00) >> 8;
		TXData[7] = dat & 0x00ff;
		break;
	default:
		break;
	}
}

void SeqMemSetupFun(void) {	/* Soft Test is OK!*/
}

char GetMemIndexCT(char no) {
	int i;
	char tmp=0;

	for( i=0; i<=15 ; i++) {
		/* Get chain list of run program */
		if(p3k_Disp_PROG.Timing_Data[no].RUNMODE[i] == 0) {
		} else {
			DGIO_BAR.PROGNO[DGIO_BAR.TOTAL_CT]	= no;
			DGIO_BAR.SEQNO[DGIO_BAR.TOTAL_CT]	= i;
			DGIO_BAR.RUNMODE[DGIO_BAR.TOTAL_CT]= p3k_Disp_PROG.Timing_Data[no].RUNMODE[i];
			DGIO_BAR.MEMNO[DGIO_BAR.TOTAL_CT]	= p3k_Disp_PROG.Timing_Data[no].MEMORY[i];
			DGIO_BAR.PFTIME[DGIO_BAR.TOTAL_CT]	= p3k_Disp_PROG.Timing_Data[no].PFTIME[i];
			DGIO_BAR.TOTAL_CT++;
			tmp++;
		}
	}
	return(tmp);
}

void SeqPFTimeSetupFun(void) {
	UWORD dat;
	int i;
	char ptr_addr[12]= {0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x80,0x90,0xa0,0xb0 };

	if(TX_LIST.ADDRL) {
		TXData[1] = 24;
		TXData[3] = ptr_addr[p3k_Disp_PROG.Prog_No];
		for( i=0 ; i<=9 ; i++) {
			dat = DGIO_BAR.PFTIME[(10*p3k_Disp_PROG.Prog_No)+i] * 20;		/* PF time value * 20 */
			TXData[2*i+4] = (dat & 0xff00) >> 8;
			TXData[2*i+5] = dat & 0x00ff;
		}
	}
}

void SavePMemFun(void) {
}

void RecallPMemFun(void) {
	TXData[2] = TX_LIST.ADDRH;
	TXData[3] = TX_LIST.ADDRL;
}

void SaveMemFun(void) {
	char addr_h[]= { 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c };
	char no,val_h,val_l,*dest;
	UWORD *sour;
	int i;
	unsigned char *scale;
	unsigned char sr_scale1=16;

	no = p3k_File_Utility_BAR.MEMORY_ADDR;

	val_h = no/10;
	val_l = no - (val_h*10);

	TX_LIST.ADDRH = addr_h[val_h];
	TX_LIST.ADDRL = val_l << 4;

	TXData[1] = 24;		/* Length = 0x18*/
	TXData[2] = TX_LIST.ADDRH;
	TXData[3] = TX_LIST.ADDRL;

	TXData[4] = ChanID[TX_LIST.CHANNO].M_DATA[no].MODE;
	TXData[5] = (ChanID[TX_LIST.CHANNO].M_DATA[no].STATUS&0x6F);

	dest = &TXData[6];
	sour = &ChanID[TX_LIST.CHANNO].M_DATA[no].VALUE1;
	scale =&sr_scale1;

	for( i =0; i<=7 ; i++) {
		/* Mode, Status, Value1, Value2, SR Up, SR Dn, Time1, Time2, Hi value, Low value */
		if( i == 6)
			sour++;
		if((i==2)||(i==3)) {	/*Slew Rate Up and Slew Rate Down*/
			*dest = (((*sour)*(*scale)) & 0xff00) >> 8;
			dest++;
			*dest = ((*sour)*(*scale)) & 0x00ff;
		} else {
			*dest = ( (*sour) & 0xff00) >> 8;
			dest++;
			*dest = (*sour) & 0x00ff;
		}
		dest++;
		sour++;
	}
	if(ChanID[TX_LIST.CHANNO].M_DATA[no].MODE==P_CV) {
		TXData[10]=TXData[14];
		TXData[11]=TXData[15];
	}
	TXData[22] = 0x00;
	TXData[23] = 0x00;
}

void SaveSeqFun(void) {
	char addr_h[]= { 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c };
	char no,val_h,val_l,*dest;
	UWORD *sour;
	int i;
	unsigned char *scale;
	unsigned char sr_scale1=16;

	no =  ChanID[TX_LIST.CHANNO].D_SEQ_DATA.Curr_Number;

	val_h = no/10;
	val_l = no - (val_h*10);

	TX_LIST.ADDRH = addr_h[val_h];
	TX_LIST.ADDRL = val_l << 4;

	TXData[1] = 14;		/* Length = 0x0E*/
	TXData[2] = TX_LIST.ADDRH;
	TXData[3] = TX_LIST.ADDRL;

	TXData[4] = ChanID[TX_LIST.CHANNO].D_SEQ_DATA.S_DATA[no].MODE;				/*Mode*/
	TXData[5] = (ChanID[TX_LIST.CHANNO].D_SEQ_DATA.S_DATA[no].STATUS&0x6F);	/*Status*/

	dest = &TXData[6];
	sour = &ChanID[TX_LIST.CHANNO].D_SEQ_DATA.S_DATA[no].VALUE1;
	scale =&sr_scale1;

	for( i =0; i<=3 ; i++) {
		/* Value1, Value2, SR Up, SR Dn */
		if((i==2)||(i==3)) {	/*Slew Rate Up and Slew Rate Down*/
			*dest = (((*sour)*(*scale)) & 0xff00) >> 8;
			dest++;
			*dest = ((*sour)*(*scale)) & 0x00ff;
		} else {
			*dest = ( (*sour) & 0xff00) >> 8;
			dest++;
			*dest = (*sour) & 0x00ff;
		}
		dest++;
		sour++;
	}
}

void SaveSeqFunAll(void) {
	char addr_h[]= { 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c };
	char no,val_h,val_l,*dest;
	UWORD *sour;
	int i;
	unsigned char *scale;
	unsigned char sr_scale1=16;

	no =  ChanID[TX_LIST.CHANNO].D_SEQ_DATA.Curr_Number;

	val_h = no/10;
	val_l = no - (val_h*10);

	TX_LIST.ADDRH = addr_h[val_h];
	TX_LIST.ADDRL = val_l << 4;

	TXData[1] = 15;		/* Length = 0x0F*/
	TXData[2] = TX_LIST.ADDRH;
	TXData[3] = TX_LIST.ADDRL;

	TXData[4] = 0;

	TXData[5] = ChanID[TX_LIST.CHANNO].D_SEQ_DATA.S_DATA[no].MODE;			/*Mode*/
	TXData[6] = (ChanID[TX_LIST.CHANNO].D_SEQ_DATA.S_DATA[no].STATUS&0x6F);	/*Status*/

	dest = &TXData[7];
	sour = &ChanID[TX_LIST.CHANNO].D_SEQ_DATA.S_DATA[no].VALUE1;
	scale =&sr_scale1;

	for( i =0; i<=3 ; i++) {
		/* Value1, Value2, SR Up, SR Dn */
		if((i==2)||(i==3)) {	/*Slew Rate Up and Slew Rate Down*/
			*dest = (((*sour)*(*scale)) & 0xff00) >> 8;
			dest++;
			*dest = ((*sour)*(*scale)) & 0x00ff;
		} else {
			*dest = ( (*sour) & 0xff00) >> 8;
			dest++;
			*dest = (*sour) & 0x00ff;
		}
		dest++;
		sour++;
	}
}

void Para_Ext_Fun(void) {
	UWORD Para_Ext_Data;
	UWORD FPGA_Data;
	unsigned short ISR_Status,ISR_Range,ISR_LoadOn,ISR_Alarm;
	static unsigned char Para_UnReg_Count;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	p3k_send_tx_list tx_data;

	Para_Ext_Data = 0;

	switch(TX_LIST.ADDRL) {
	case Para_Ext_Setting: /* Set Parallel Master/Slave Status*/
		if(UTILITY.LOAD_CTL)
			Para_Ext_Data |= Ext_LoadON_Status;

		if(UTILITY.SHORT_CTL)
			Para_Ext_Data |= Ext_Short_Status;

		//if(IRange_Mid==Data_tmp->IRange)
		//	Para_Ext_Data |= Ext_IRange_M_Status;
		//else
		if(IRange_Low==Data_tmp->IRange)
			Para_Ext_Data |= Ext_IRange_L_Status;
		else
			Para_Ext_Data |= Ext_IRange_H_Status;

		if(p3k_Measure_Data.Alarm)
			Para_Ext_Data |= Ext_Alarm_Status;

		Para_Ext_Data |= Set_Parallel_Ext_Load_ON_Input;

		if(Operation_Master==Data_tmp->CONF.Para_Data.Mode) {
			if(0){ ///( (Data_tmp->CONF.Para_Data.Parallel_Number)||(Data_tmp->CONF.Para_Data.Booster_Number) ) {
				Para_Ext_Data |= Enable_Parallel;

				if(LOW_RANGE==Data_tmp->IRange)
					Para_Ext_Data |= Set_L_IRange_In_Parallel;
				else
					Para_Ext_Data |= Set_H_M_IRange_In_Parallel;	/* High or Mid */

				Para_Ext_Data |= Set_Parallel_Master;
			} else
				Para_Ext_Data |= Disable_Parallel;
		} else {
			if(FPGA_ISR_Data.Para_Enable)
				Para_Ext_Data |= Set_Parallel_Slave;
		}

		if(Ext_Setting_V==Data_tmp->CONF.Ext_Setting.Control) {
			Para_Ext_Data |= Ext_Control_V;
			Acess_FPGA(FPGA_EXT_RV_SENSE_Gain,  p3k_Cal_data.Ext_V_Sense.Meas_Value_Gain);
			Acess_FPGA(FPGA_EXT_RV_SENSE_Offset,p3k_Cal_data.Ext_V_Sense.Meas_Value_Offset);
		} else if(Ext_Setting_R==Data_tmp->CONF.Ext_Setting.Control) {
			Para_Ext_Data |= Ext_Control_R;
			Acess_FPGA(FPGA_EXT_RV_SENSE_Gain,  p3k_Cal_data.Ext_R_Sense.Meas_Value_Gain);
			Acess_FPGA(FPGA_EXT_RV_SENSE_Offset,p3k_Cal_data.Ext_R_Sense.Meas_Value_Offset);
		} else if(Ext_Setting_InvR==Data_tmp->CONF.Ext_Setting.Control) {
			Para_Ext_Data |= Ext_Control_R + Ext_Control_Invert;
			Acess_FPGA(FPGA_EXT_RV_SENSE_Gain,	p3k_Cal_data.Ext_R_Sense.Meas_Value_Gain);
			Acess_FPGA(FPGA_EXT_RV_SENSE_Offset,p3k_Cal_data.Ext_R_Sense.Meas_Value_Offset);
		} else
			Para_Ext_Data |= 0;

		if( (Data_tmp->CONF.Ext_Setting.Control)&&(CR_MODE==Data_tmp->CURRMODE) )
			Para_Ext_Data |= Ext_Control_CR_MODE;
		//copy_Para_Ext_Data = Para_Ext_Data;
		Para_Ext_Data |= Set_Parallel_Ext_Trig_Input_ON;

		Acess_FPGA(FPGA_External_Applied_Operation_Control,Para_Ext_Data);
		//OSTimeDly(1);
		FPGA_Ctrl();
		break;
	case Para_Ext_Status: /* (Every 20ms/Times) OR Interrupt Occur */
		if(Prog_Load==P3k_Chan_Data.Load_Type) {
			FPGA_Data = Acess_FPGA(FPGA_Sequence_Mode_Set_ID,NULL);
			break;
		}

		FPGA_Data  = Acess_FPGA(FPGA_External_Status,NULL);

		ISR_Status = FPGA_Data & External_Action_ISR;
		ISR_Range  = FPGA_Data & 0x0006;
		ISR_LoadOn = FPGA_Data & External_Status_Load_ON;
		ISR_Alarm  = FPGA_Data & External_Status_Alarm;

		if(ISR_Status)
			FPGA_ISR_Data.ISR_Flag = 1;
		else
			FPGA_ISR_Data.ISR_Flag = 0;

		if(Data_tmp->CONF.Ext_Setting.Control) {				/*External Control*/
			//if(ISR_Range == External_Status_IRange_M)
			//	FPGA_ISR_Data.ISR_Range = IRange_Mid;
			//else
			if(ISR_Range == External_Status_IRange_L)
				FPGA_ISR_Data.ISR_Range = IRange_Low;
			else
				FPGA_ISR_Data.ISR_Range = IRange_High;
		}
		if(P3k_Chan_Data.CONF.Ext_Setting.LoadOn_IN==0) {
			if(P3k_Chan_Data.CONF.Ext_Setting.MultilPara)
				P_Sense |= 0x0100;
			else
				P_Sense &= ~(0x0100);
		}
		if(Operation_Slave == Data_tmp->CONF.Para_Data.Mode) {	/*Parallel Control*/
			if(ISR_Range == External_Status_IRange_L)
				FPGA_ISR_Data.ISR_Range = IRange_Low;
			else
				FPGA_ISR_Data.ISR_Range = IRange_High;			/*High or Mid*/

			if(ISR_LoadOn)
				FPGA_ISR_Data.Para_Enable = Switch_ON;
			else
				FPGA_ISR_Data.Para_Enable = Switch_OFF;
		} else {	/* Operation_Master */
			if((Data_tmp->CONF.Ext_Setting.LoadOn_IN) && (M_num != P_NSeq_EXECUTE) && (M_num != P_FSeq_EXECUTE)&&(M_num != P_PROG_EXECUTE)) {
				if((!ISR_LoadOn && (Data_tmp->CONF.Ext_Setting.LoadOn_IN == 1)) || ((ISR_LoadOn) && (Data_tmp->CONF.Ext_Setting.LoadOn_IN == 2)))
					FPGA_ISR_Data.ISR_Load = Switch_ON;
				else
					FPGA_ISR_Data.ISR_Load = Switch_OFF;

				tx_data.ADDRH = Para_Ext_Command;
				tx_data.ADDRL = Para_Ext_Setting;
				SendTXData(&tx_data);
			} else
				FPGA_ISR_Data.ISR_Load = Switch_ON;
			if(ISR_Alarm) {
				//if(Data_tmp->CONF.Ext_Setting.Control)
				if((M_num != P_CAL_MODE) && (M_num != P_Test_Func) && (M_num != P_NSeq_EXECUTE) && (M_num != P_FSeq_EXECUTE)&&(M_num != P_PROG_EXECUTE)) {
					checkParaAlarmCount = 1;
					tx_data.ADDRH = Para_Ext_Command;
					tx_data.ADDRL = Para_Ext_Setting;
					SendTXData(&tx_data);
				}
				Para_UnReg_Count++;
			} else {
				if((!Ext_UnReg_Flag) && (M_num != P_CAL_MODE) && (M_num != P_Test_Func) && (M_num != P_NSeq_EXECUTE) && (M_num != P_FSeq_EXECUTE) &&(M_num != P_PROG_EXECUTE)) {
					checkParaAlarmCount = 0;
					tx_data.ADDRH = Para_Ext_Command;
					tx_data.ADDRL = Para_Ext_Setting;
					SendTXData(&tx_data);
				}
				Para_UnReg_Count = 0;
			}

			if(Para_UnReg_Count == 50) {
				if((p3k_Measure_Data.Alarm == UnReg_Alarm) || (p3k_Measure_Data.Alarm == No_Alarm))
					Para_UnReg_Count = 50;
				else
					checkParaAlarmCount = 1;


			}
		}
		break;
	}
}

void RecallMemFun(void) {
	char addr_h[]= { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c };
	char no,val_h, val_l;

	no = p3k_File_Utility_BAR.MEMORY_ADDR;
	val_h= no/10;
	val_l = no - (val_h*10);

	TX_LIST.ADDRH = addr_h[val_h];
	TX_LIST.ADDRL = val_l << 4;

	TXData[2] = TX_LIST.ADDRH;
	TXData[3] = TX_LIST.ADDRL;
}

UWORD Read_FPGA_Status(UWORD Interval_Time) {
	UWORD Read_Data_1;
	UWORD Read_Data_2		= 0;
	UWORD Repeat_Number		= 0;
	UWORD Function_TimeOut	= 100;
	while(Repeat_Number<10) {
		OSTimeDly(Interval_Time);
		Read_Data_1 = Acess_FPGA(FPGA_Status,NULL);
		if(Read_Data_1==Read_Data_2)
			Repeat_Number++;
		else
			Repeat_Number = 0;
		Function_TimeOut--;
		Read_Data_2 = Read_Data_1;

		if(Function_TimeOut==0) {
			printf("Read_FPGA_Status Error\n");
			Read_Data_1 = 0;
			break;
		}
	}
	return Read_Data_1;
}
UWORD Read_FPGA_Status_1(UWORD Interval_Time) {
	UWORD Read_Data_1;
	UWORD Read_Data_2		= 0;
	UWORD Repeat_Number		= 0;
	UWORD Function_TimeOut	= 100;
	while(Repeat_Number<6) {
		OSTimeDly(Interval_Time);
		Read_Data_1 = Acess_FPGA(FPGA_Status,NULL);
		if(Read_Data_1==Read_Data_2)
			Repeat_Number++;
		else
			Repeat_Number = 0;
		Function_TimeOut--;
		Read_Data_2 = Read_Data_1;

		if(Function_TimeOut==0) {
			printf("Read_FPGA_Status Error\n");
			Read_Data_1 = 0;
			break;
		}
	}
	return Read_Data_1;
}


void Cal_XYZ_Sensor(UBYTE Select_Sensor,UBYTE Cal_Range) {
	/*Select_Sensor=0, X Sensor*/
	/*Select_Sensor=1, X Sensor*/
	/*Select_Sensor=2, Y Sensor*/
	char i,Error_Message[50];
	UWORD Shift_Value_Temp,Cal_Status_Temp,AD633_Setting;
	UWORD *XYZ_Value_Temp,*XYZ_Value,*XYZ_Value_low;
	ULONG OS_Ref_Setting;
	UWORD x1=0,x2=0;
	UBYTE checkError =0;
	UWORD kk;


	if( (Select_Sensor>2)||(Cal_Range>2) ) {
		Debug_printf("Cal_XYZ_Sensor Error!!\n");
		return;
	}

	if(PSense_X==Select_Sensor) {
		AD633_Setting	= Set_Calibration_AD633_X_OS;
		OS_Ref_Setting	= FPGA_XL_OS_Ref;
		sprintf(Error_Message," PSense_X Calibration Error!! ");
	} else if(PSense_Y==Select_Sensor) {
		AD633_Setting	= Set_Calibration_AD633_Y_OS;
		OS_Ref_Setting	= FPGA_YL_OS_Ref;
		sprintf(Error_Message," PSense_Y Calibration Error!! ");
	} else if(PSense_Z==Select_Sensor) {
		AD633_Setting	= Set_Calibration_AD633_Z_OS;
		OS_Ref_Setting	= FPGA_ZL_OS_Ref;
		sprintf(Error_Message," PSense_Z Calibration Error!! ");
	}


	XYZ_Value_Temp	= &P3K_CALIBRATION_BAR.PSensor.XL_Value	+ Select_Sensor + Cal_Range*3;
	XYZ_Value		= &p3k_Cal_data.PSensor.XL_Value		+ Select_Sensor + Cal_Range*3;
	XYZ_Value_low  = &p3k_Cal_data.PSensor.XL_Value		+ Select_Sensor ;

	Acess_FPGA(FPGA_On_Off_Reference_Setting,AD633_Setting|Set_Protection_Ref_Adjust_ON);
	OSTimeDly(5);
	*XYZ_Value_Temp = 0;

	for(i=0 ; i<16 ; i++) {
		Shift_Value_Temp = Compare_Value>>i;
		Acess_FPGA(OS_Ref_Setting,Shift_Value_Temp|(*XYZ_Value_Temp));
		OSTimeDly(20);

		Cal_Status_Temp = Read_FPGA_Status(1);

		if(Cal_Status_Temp==0) {
			Menu_Message(Error_Message,50,210);
			CtrlFlag1 |= Disp_Middle_Message;
			DMA_Update_Flag = 1;
			Update_Panel();
			OSTimeDly(200);
			(*XYZ_Value_Temp) = (*XYZ_Value);
			P3K_CALIBRATION_BAR.PSense = 1;
			CtrlFlag1 |= Cal_Wait_moment;
			break;
		}
		if(PSense_Z==Select_Sensor) {
			if((Cal_Status_Temp&0x0004)==0)
				Shift_Value_Temp = 0;
		} else {
			if((Cal_Status_Temp&0x0004)!=0)
				Shift_Value_Temp = 0;
		}

		(*XYZ_Value_Temp) |= Shift_Value_Temp;
	}
#if 1
	//if((*XYZ_Value_Temp>33000)||(*XYZ_Value_Temp<26000)) {
	//if((*XYZ_Value_Temp>40000)||(*XYZ_Value_Temp<28000)) {
	if((*XYZ_Value_Temp>P_SENSOR_MAX)||(*XYZ_Value_Temp<P_SENSOR_MIN)) {
//printf("value:%d\n",*XYZ_Value_Temp);
		FPGA_W[253] = Select_Sensor;
		FPGA_R[253] = *XYZ_Value_Temp;
		Menu_Message(Error_Message,50,210);
		CtrlFlag1 |= Disp_Middle_Message;
		DMA_Update_Flag = 1;
		Update_Panel();
		OSTimeDly(200);
		(*XYZ_Value_Temp) = (*XYZ_Value);
		P3K_CALIBRATION_BAR.PSense = 1;
		CtrlFlag1 |= Cal_Wait_moment;
	}
#endif
	(*XYZ_Value) = (*XYZ_Value_Temp);
	(*XYZ_Value_low) = (*XYZ_Value);
	Acess_FPGA(OS_Ref_Setting,(*XYZ_Value));

}

extern void Show_Prot_Error_Window(UBYTE Error_Mode,double Error_Gain,double Error_Offset,UWORD Input_HP,UWORD Input_LP,UWORD System_HP,UWORD System_LP);


#if 1 //20150511
void CalibrationFun(void) {
	unsigned short VM_Range=0,Circuit_SW0=0,Circuit_SW1=0;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UWORD *OFFSET_MON_Point,SR_Value,CP_MAX_Value;
	UWORD *OFFSET_MON_Ext_V, *OFFSET_MON_Ext_R;
	ULONG I_V_MON_Total,Register_Temp;
	int i,j;
	UWORD High_Point,Low_Point;
	char val;
	UWORD Shift_Value_Temp,Cal_Status_Temp,Cal_Data_Temp,Res = 0;
	UBYTE Mode,Rang;
	UWORD Recode_d1,Recode_d2;
	UWORD CxCV_H_count,CxCV_L_count;
	if(Model_Number==MODEL3031E) {
		CxCV_H_count=42000;
		CxCV_L_count=4200;
	} else {
		CxCV_H_count=45300;
		CxCV_L_count=4530;
	}

	Mode = P3K_CALIBRATION_BAR.MODE;
	Rang = P3K_CALIBRATION_BAR.RANGE;

	if((Mode==CV_MODE)||(Mode==CxCV_MODE)) {
		if(Rang==LOW_RANGE)		VM_Range = VM_L_Range;
		else					VM_Range = 0;
	} else if(Mode==CR_MODE) {
		if(Rang)				VM_Range = VM_L_Range;
		else					VM_Range = 0;
	} else {
		VM_Range = 0;
	}
	val = Mode+(Rang*MODE_Number);

	switch(TX_LIST.ADDRL) {
	case Cal_FPGA_Start:		/* Cal Start : Send Load On Command */
		Acess_FPGA(FPGA_On_Off_Reference_Setting,  Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_ON);
		break;
	case Cal_FPGA_End:					/* Cal End :  OCP,Rating OCP,OPP,CPP Calibration & Send Load Off Command */
		//get AD value ten times---(measure current, measure voltage, extern V, extern R)-------------------------
		if(P3K_CALIBRATION_BAR.POINT)
			OFFSET_MON_Point = &P3K_CALIBRATION_BAR.Monitor_Low;
		else
			OFFSET_MON_Point = &P3K_CALIBRATION_BAR.Monitor_High;

		if(Mode==CV_MODE)
			Register_Temp = FPGA_V_Sense;
		else if((Mode==Ext_V_CC_MODE)||(Mode==Ext_R_CC_MODE))
			Register_Temp = FPGA_EXT_RV_SENSE;
		else
			Register_Temp = FPGA_I_Sense;

		I_V_MON_Total = 0;
		for(i=0; i<10; i++) {
			I_V_MON_Total += Acess_FPGA(Register_Temp,NULL);
			OSTimeDly(1);
		}

		*OFFSET_MON_Point = I_V_MON_Total /10;

		if((Mode==CC_MODE)||(Mode==CV_MODE)) {
			if(Mode==CV_MODE)
				Register_Temp = FPGA_V_Sense;
			else if(Mode==CC_MODE)
				Register_Temp = FPGA_I_Sense;
			if(P3K_CALIBRATION_BAR.POINT) {
				OFFSET_MON_Ext_V = &Monitor_ExtV_L;
				OFFSET_MON_Ext_R = &Monitor_ExtR_L;
			} else {
				OFFSET_MON_Ext_V = &Monitor_ExtV_H;
				OFFSET_MON_Ext_R = &Monitor_ExtR_H;
			}
			OSTimeDly(2);
			Acess_FPGA(FPGA_External_Applied_Operation_Control,Ext_Control_V);
			OSTimeDly(5);
			I_V_MON_Total = 0;
			for(i=0; i<10; i++) {
				I_V_MON_Total += Acess_FPGA(Register_Temp,NULL);
				OSTimeDly(1);
			}
			*OFFSET_MON_Ext_V = I_V_MON_Total /10;

			OSTimeDly(2);

			Acess_FPGA(FPGA_External_Applied_Operation_Control,Ext_Control_R);
			OSTimeDly(5);
			I_V_MON_Total = 0;
			for(i=0; i<10; i++) {
				I_V_MON_Total += Acess_FPGA(Register_Temp,NULL);
				OSTimeDly(1);
			}
			*OFFSET_MON_Ext_R = I_V_MON_Total /10;
			OSTimeDly(2);
			Acess_FPGA(FPGA_External_Applied_Operation_Control,Ext_Control_OFF);
			OSTimeDly(5);
		}

		// Calibration OCP, ROCP ---------------------------------------------
		if((Mode==CC_MODE)&&(Rang==HIGH_RANGE)) {
			/* OCP Calibration  */
			Acess_FPGA(FPGA_On_Off_Latch_Setting, Set_All_Prot_Limit);
			OSTimeDly(5);
			Cal_Data_Temp = 0;
			for(i=0 ; i<16 ; i++) {
				Shift_Value_Temp = Compare_Value>>i;
				Acess_FPGA(FPGA_CX_H_OCP,Shift_Value_Temp|Cal_Data_Temp);
				OSTimeDly(20);

				Cal_Status_Temp = Read_FPGA_Status(1);

				if(Cal_Status_Temp==0) {
					Menu_Message(" OCP Calibration Error!! ",50,210);
					CtrlFlag1 |= Disp_Middle_Message;
					DMA_Update_Flag = 1;
					Update_Panel();
					OSTimeDly(200);
				}
				if((Cal_Status_Temp&OCP_Prot_Event)==0)
					Shift_Value_Temp = 0;
				Cal_Data_Temp |= Shift_Value_Temp;
			}
			if(P3K_CALIBRATION_BAR.POINT)
				P3K_CALIBRATION_BAR.OCP_Low_Point	= Cal_Data_Temp;
			else
				P3K_CALIBRATION_BAR.OCP_High_Point	= Cal_Data_Temp;
		}
		if((Mode==CP_MODE)&&(Rang==HIGH_RANGE)) {
			/* OPP Calibration */
			Acess_FPGA(FPGA_On_Off_Latch_Setting, Set_All_Prot_Limit);
			OSTimeDly(5);
			Cal_Data_Temp = 0;
			///FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_S);
			for(i=0 ; i<16 ; i++) {
				Shift_Value_Temp = Compare_Value>>i;
				Acess_FPGA(FPGA_CX_H_OPP,Shift_Value_Temp|Cal_Data_Temp);
				OSTimeDly(1);
				Cal_Status_Temp = Read_FPGA_Status_1(1);

				if(Cal_Status_Temp==0) {
					Menu_Message(" OPP Calibration Error!! ",50,210);
					CtrlFlag1 |= Disp_Middle_Message;
					DMA_Update_Flag = 1;
					Update_Panel();
					OSTimeDly(200);
				}
				if((Cal_Status_Temp&OPP_Prot_Event)==0)
					Shift_Value_Temp = 0;
				Cal_Data_Temp |= Shift_Value_Temp;
			}
			for(i=0; i<35; i++) {
				Cal_Data_Temp -=40;
				Acess_FPGA(FPGA_CX_H_OPP,Cal_Data_Temp);
				OSTimeDly(1);
				Cal_Status_Temp = Read_FPGA_Status_1(1);
				if(Cal_Status_Temp&OPP_Prot_Event)	break;
			}
			Recode_d1 = Cal_Data_Temp +20;
			for(i=0; i<30; i++) {
				Cal_Data_Temp +=8;
				Acess_FPGA(FPGA_CX_H_OPP,Cal_Data_Temp);
				OSTimeDly(1);
				Cal_Status_Temp = Read_FPGA_Status_1(1);
				if(Cal_Status_Temp&OPP_Prot_Event) {
				} else {
					break;
				}
			}
			Recode_d2 = Cal_Data_Temp -4;
			Cal_Data_Temp = (Recode_d1+Recode_d2)/2;

			if(P3K_CALIBRATION_BAR.POINT) {
				P3K_CALIBRATION_BAR.OPP_Low_Point	= Cal_Data_Temp;

			} else {
				P3K_CALIBRATION_BAR.OPP_High_Point	= Cal_Data_Temp;

			}

		}
		/*	CxCV Calibration  */
		if(Mode == CxCV_MODE) {
			if(P3K_CALIBRATION_BAR.POINT)
				P3K_CALIBRATION_BAR.CxCV_Low_Point	= P3K_CALIBRATION_BAR.Set_Value_Low;
			else
				P3K_CALIBRATION_BAR.CxCV_High_Point	= P3K_CALIBRATION_BAR.Set_Value_High;
		}
		Acess_FPGA(FPGA_On_Off_Reference_Setting, Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
		break;
	case Cal_FPGA_Fail:
		Acess_FPGA(FPGA_On_Off_Reference_Setting, Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
		break;
	case Cal_FPGA_Load_Meas_Default:
		if((Data_tmp->CONF.Ext_Setting.Control==0)||(M_num==P_CAL_MODE)) { //Normal
			Acess_FPGA(FPGA_V_Sense_H_Gain,	  p3k_Cal_data.Volt[1].Meas_Value_Gain);
			Acess_FPGA(FPGA_V_Sense_H_Offset,(p3k_Cal_data.Volt[1].Meas_Value_Gain*p3k_Cal_data.Volt[1].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_V_Sense_L_Gain,	  p3k_Cal_data.Volt[0].Meas_Value_Gain);
			Acess_FPGA(FPGA_V_Sense_L_Offset,(p3k_Cal_data.Volt[0].Meas_Value_Gain*p3k_Cal_data.Volt[0].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_I_Sense_H_Gain,	  p3k_Cal_data.Curr[1].Meas_Value_Gain);
			Acess_FPGA(FPGA_I_Sense_H_Offset,(p3k_Cal_data.Curr[1].Meas_Value_Gain*p3k_Cal_data.Curr[1].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_I_Sense_L_Gain,	  p3k_Cal_data.Curr[0].Meas_Value_Gain);
			Acess_FPGA(FPGA_I_Sense_L_Offset,(p3k_Cal_data.Curr[0].Meas_Value_Gain*p3k_Cal_data.Curr[0].Meas_Value_Offset/65535.0));
		} else if (Data_tmp->CONF.Ext_Setting.Control==1) { //Ext_V
			Acess_FPGA(FPGA_V_Sense_H_Gain,	  p3k_Cal_data.Ext_V_Volt[1].Meas_Value_Gain);
			Acess_FPGA(FPGA_V_Sense_H_Offset,(p3k_Cal_data.Ext_V_Volt[1].Meas_Value_Gain*p3k_Cal_data.Volt[1].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_V_Sense_L_Gain,	  p3k_Cal_data.Ext_V_Volt[0].Meas_Value_Gain);
			Acess_FPGA(FPGA_V_Sense_L_Offset,(p3k_Cal_data.Ext_V_Volt[0].Meas_Value_Gain*p3k_Cal_data.Volt[0].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_I_Sense_H_Gain,	  p3k_Cal_data.Ext_V_Curr[1].Meas_Value_Gain);
			Acess_FPGA(FPGA_I_Sense_H_Offset,(p3k_Cal_data.Ext_V_Curr[1].Meas_Value_Gain*p3k_Cal_data.Curr[1].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_I_Sense_L_Gain,	  p3k_Cal_data.Ext_V_Curr[0].Meas_Value_Gain);
			Acess_FPGA(FPGA_I_Sense_L_Offset,(p3k_Cal_data.Ext_V_Curr[0].Meas_Value_Gain*p3k_Cal_data.Curr[0].Meas_Value_Offset/65535.0));
		} else { //Ext_R or Ext_Rinv
			Acess_FPGA(FPGA_V_Sense_H_Gain,	  p3k_Cal_data.Ext_R_Volt[1].Meas_Value_Gain);
			Acess_FPGA(FPGA_V_Sense_H_Offset,(p3k_Cal_data.Ext_R_Volt[1].Meas_Value_Gain*p3k_Cal_data.Volt[1].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_V_Sense_L_Gain,	  p3k_Cal_data.Ext_R_Volt[0].Meas_Value_Gain);
			Acess_FPGA(FPGA_V_Sense_L_Offset,(p3k_Cal_data.Ext_R_Volt[0].Meas_Value_Gain*p3k_Cal_data.Volt[0].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_I_Sense_H_Gain,	  p3k_Cal_data.Ext_R_Curr[1].Meas_Value_Gain);
			Acess_FPGA(FPGA_I_Sense_H_Offset,(p3k_Cal_data.Ext_R_Curr[1].Meas_Value_Gain*p3k_Cal_data.Curr[1].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_I_Sense_L_Gain,	  p3k_Cal_data.Ext_R_Curr[0].Meas_Value_Gain);
			Acess_FPGA(FPGA_I_Sense_L_Offset,(p3k_Cal_data.Ext_R_Curr[0].Meas_Value_Gain*p3k_Cal_data.Curr[0].Meas_Value_Offset/65535.0));
		}

		break;

	case Cal_FPGA_Prot: 	/* Protection  Calibration */
		if((Mode==CC_MODE)&&(Rang==HIGH_RANGE)) {
			///High_Point	= P3K_CALIBRATION_BAR.HP_Volt	/ (ptrMODEL_TYPE->CALI_HP)[14].Resolution;
			///Low_Point	= P3K_CALIBRATION_BAR.LP_Volt	/ (ptrMODEL_TYPE->CALI_HP)[14].Resolution;
			High_Point	= P3K_CALIBRATION_BAR.HP_Volt	/ (ptrMODEL_TYPE->PROT)[0].Resolution;
			Low_Point	= P3K_CALIBRATION_BAR.LP_Volt	/ (ptrMODEL_TYPE->PROT)[0].Resolution;
			/* OCP */
			P3K_CALIBRATION_BAR.OCP_Gain	= (double) (P3K_CALIBRATION_BAR.OCP_High_Point - P3K_CALIBRATION_BAR.OCP_Low_Point) /(double) (High_Point - Low_Point);
			P3K_CALIBRATION_BAR.OCP_Offset	= ( (double)P3K_CALIBRATION_BAR.OCP_High_Point	- (P3K_CALIBRATION_BAR.OCP_Gain*High_Point) );

			if(P3K_CALIBRATION_BAR.OCP_Offset < 0)	Cal_Offset_Error |= OCP_Err;

			if(((((ptrMODEL_TYPE->PROT)[IRange_High].Max)* P3K_CALIBRATION_BAR.OCP_Gain)+P3K_CALIBRATION_BAR.OCP_Offset)>65535.0) {
				P3K_CALIBRATION_BAR.OCP_Gain	= 1;
				P3K_CALIBRATION_BAR.OCP_Offset	= 0;
			}
		}

		if((Mode==CP_MODE)&&(Rang==HIGH_RANGE)) {
			//High_Point	= (P3K_CALIBRATION_BAR.HP_Volt	* P3K_CALIBRATION_BAR.HP_Curr)	/ (ptrMODEL_TYPE->CALI_HP)[5].Resolution;
			//Low_Point	= (P3K_CALIBRATION_BAR.LP_Volt	* P3K_CALIBRATION_BAR.LP_Curr)	/ (ptrMODEL_TYPE->CALI_HP)[5].Resolution;
			High_Point	= (P3K_CALIBRATION_BAR.HP_Volt	* P3K_CALIBRATION_BAR.HP_Curr)	/ (ptrMODEL_TYPE->PROT)[2].Resolution;
			Low_Point	= (P3K_CALIBRATION_BAR.LP_Volt	* P3K_CALIBRATION_BAR.LP_Curr)	/ (ptrMODEL_TYPE->PROT)[2].Resolution;
			/* OPP */
			P3K_CALIBRATION_BAR.OPP_Gain	= (double) (P3K_CALIBRATION_BAR.OPP_High_Point - P3K_CALIBRATION_BAR.OPP_Low_Point) /(double) (High_Point - Low_Point);
			P3K_CALIBRATION_BAR.OPP_Offset	= ( (double)P3K_CALIBRATION_BAR.OPP_High_Point	- (P3K_CALIBRATION_BAR.OPP_Gain*High_Point) );
#if Normal_TEST
			printf("H_P:%d\n",P3K_CALIBRATION_BAR.OPP_High_Point);
			printf("L_P:%d\n",P3K_CALIBRATION_BAR.OPP_Low_Point);
			printf("H_V:%d\n",High_Point);
			printf("L_V:%d\n",Low_Point);
#endif

			if(P3K_CALIBRATION_BAR.OPP_Offset < 0)	Cal_Offset_Error |= OPP_Err;

			CP_MAX_Value = (ptrMODEL_TYPE->PROT)[PROT_OPP_H].Max;
			if(((CP_MAX_Value*P3K_CALIBRATION_BAR.OPP_Gain)+P3K_CALIBRATION_BAR.OPP_Offset)>65535.0) {
				P3K_CALIBRATION_BAR.OPP_Gain	= 1;
				P3K_CALIBRATION_BAR.OPP_Offset	= 0;
			}
		}
		/*	CxCV Calibration  */
		if(Mode==CxCV_MODE) {
			High_Point	= P3K_CALIBRATION_BAR.HP_Volt	/ (ptrMODEL_TYPE->CALI_HP)[val].Resolution; //0.005
			Low_Point	= P3K_CALIBRATION_BAR.LP_Volt	/ (ptrMODEL_TYPE->CALI_HP)[val].Resolution; //0.005
			Recode_d1 = CxCV_H_count;
			Recode_d2 = CxCV_L_count;
			P3K_CALIBRATION_BAR.CxCV_Gain	=  (double)(Recode_d1 - Recode_d2) /(double)(High_Point - Low_Point);
			P3K_CALIBRATION_BAR.CxCV_Offset	= 	(double)Recode_d1 -(double)(P3K_CALIBRATION_BAR.CxCV_Gain*High_Point) ;

			if(P3K_CALIBRATION_BAR.CxCV_Offset < 0)	Cal_Offset_Error |= CXCV_Err;

			if(((((ptrMODEL_TYPE->CV)[0].Max)* P3K_CALIBRATION_BAR.CxCV_Gain)+P3K_CALIBRATION_BAR.CxCV_Offset)>65535.0) {
				//Show_Prot_Error_Window(4,P3K_CALIBRATION_BAR.CxCV_Gain,P3K_CALIBRATION_BAR.CxCV_Offset,High_Point,Low_Point,P3K_CALIBRATION_BAR.CxCV_High_Point,P3K_CALIBRATION_BAR.CxCV_Low_Point);
				P3K_CALIBRATION_BAR.CxCV_Gain	= 1;
				P3K_CALIBRATION_BAR.CxCV_Offset	= 0;
			}

			P3K_CALIBRATION_BAR.CxCV = Step_To_CNT(Data_tmp->CV.STA[Data_tmp->VRange].VALUE1,P3K_CALIBRATION_BAR.CxCV_Gain,P3K_CALIBRATION_BAR.CxCV_Offset);
			if(HIGH_RANGE==Rang)
				Acess_FPGA(Cx_CV_H_Value, P3K_CALIBRATION_BAR.CxCV);
			else
				Acess_FPGA(Cx_CV_L_Value, P3K_CALIBRATION_BAR.CxCV);
		}

		Acess_FPGA(FPGA_On_Off_Reference_Setting, Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
		break;
	case Cal_FPGA_Load_Cal_Default: /* Load  Calibration Default  & Calibration Start*/
		Acess_FPGA(FPGA_V_Sense_H_Gain,		Max_Value);
		Acess_FPGA(FPGA_V_Sense_L_Gain,		Max_Value);
		Acess_FPGA(FPGA_V_Sense_H_Offset,	0);
		Acess_FPGA(FPGA_V_Sense_L_Offset,	0);

		Acess_FPGA(FPGA_I_Sense_H_Gain,		Max_Value);			//Acess_FPGA(FPGA_I_Sense_M_Gain, 	Max_Value);
		Acess_FPGA(FPGA_I_Sense_L_Gain, 	Max_Value);
		Acess_FPGA(FPGA_I_Sense_H_Offset,	0);			//Acess_FPGA(FPGA_I_Sense_M_Offset,	0);
		Acess_FPGA(FPGA_I_Sense_L_Offset,	0);

		Acess_FPGA(FPGA_EXT_RV_SENSE_Gain,  Max_Value);
		Acess_FPGA(FPGA_EXT_RV_SENSE_Offset,0);

		Acess_FPGA(Cx_CV_H_Step, 0);
		Acess_FPGA(Cx_CV_L_Step, 0);
		if((Mode==R_IMON_MODE)&&(P3K_CALIBRATION_BAR.POINT)) {
			Acess_FPGA(FPGA_Rear_IMON_Output_Adjust,63);	//Acess_FPGA(FPGA_Front_IMON_Output_Adjust,63);
		} else {
			Acess_FPGA(FPGA_Rear_IMON_Output_Adjust,0);		//Acess_FPGA(FPGA_Front_IMON_Output_Adjust,0);
		}

		Acess_FPGA(FPGA_On_Off_Latch_Setting, Set_All_Prot_Limit);

		if(Mode==Ext_V_CC_MODE)
			Acess_FPGA(FPGA_External_Applied_Operation_Control,Ext_Control_V);
		else if(Mode==Ext_R_CC_MODE)
			Acess_FPGA(FPGA_External_Applied_Operation_Control,Ext_Control_R);
		else
			Acess_FPGA(FPGA_External_Applied_Operation_Control,Ext_Control_OFF);

		Circuit_SW0 = I_Calibration_Circuit_Switch_Control[(Mode*6) + (Rang*2) + 0];
		Circuit_SW1 = I_Calibration_Circuit_Switch_Control[(Mode*6) + (Rang*2) + 1];

		if(Mode==CV_MODE)			Res |= CV_Response_slow;
		else if(Mode==CP_MODE)		Res |= CP_Response_slow;
		else if (Mode==CxCV_MODE)	Res |= CXCV_Response_slow;

		if((Mode==CC_MODE)||(Mode>=R_IMON_MODE)) //pel3032
			SR_Value = 30000;
		else //CR,CV,CP,CXCV
			SR_Value = 5000;

		Acess_FPGA(FPGA_H_Circuit_Switch_Control_0, Circuit_SW0 |VM_Range);
		Acess_FPGA(FPGA_H_Circuit_Switch_Control_1, Circuit_SW1 |Res);
		Acess_FPGA(FPGA_H_Level_Slew_Rate, SR_Value);

		if(P3K_CALIBRATION_BAR.POINT)
			Cal_Data_Temp = P3K_CALIBRATION_BAR.Set_Value_Low;
		else
			Cal_Data_Temp = P3K_CALIBRATION_BAR.Set_Value_High;
#if 1
FPGA_W[251] = P3K_CALIBRATION_BAR.Set_Value_Low;
FPGA_R[251] = P3K_CALIBRATION_BAR.Set_Value_High;
#endif
		if(Mode==CxCV_MODE) {
			if(P3K_CALIBRATION_BAR.POINT) {
				Acess_FPGA(Cx_CV_L_Value, CxCV_L_count);
				Acess_FPGA(Cx_CV_H_Value, CxCV_L_count);
			} else {
				Acess_FPGA(Cx_CV_L_Value, CxCV_H_count);
				Acess_FPGA(Cx_CV_H_Value, CxCV_H_count);
			}
			Acess_FPGA(FPGA_H_Level_Setting, Cal_Data_Temp);
		} else {
			Acess_FPGA(FPGA_H_Level_Setting, Cal_Data_Temp);
			Acess_FPGA(Cx_CV_H_Value, P3K_CALIBRATION_BAR.CxCV);
			Acess_FPGA(Cx_CV_L_Value, P3K_CALIBRATION_BAR.CxCV);
		}

		Acess_FPGA(FPGA_VON_H, 0);
		Acess_FPGA(FPGA_VON_L, 0);

		Acess_FPGA(FPGA_XH_OS_Ref, P3K_CALIBRATION_BAR.PSensor.XH_Value);
		Acess_FPGA(FPGA_YH_OS_Ref, P3K_CALIBRATION_BAR.PSensor.YH_Value);
		Acess_FPGA(FPGA_ZH_OS_Ref, P3K_CALIBRATION_BAR.PSensor.ZH_Value);
		Acess_FPGA(FPGA_XL_OS_Ref, P3K_CALIBRATION_BAR.PSensor.XH_Value);
		Acess_FPGA(FPGA_YL_OS_Ref, P3K_CALIBRATION_BAR.PSensor.YH_Value);
		Acess_FPGA(FPGA_ZL_OS_Ref, P3K_CALIBRATION_BAR.PSensor.ZH_Value);


		Acess_FPGA(FPGA_CX_H_OPP,  Default_Cal_Prot_DA_OPP);			//Acess_FPGA(FPGA_CX_M_OPP,  Default_Cal_Prot_DA_Normal);
		Acess_FPGA(FPGA_CX_L_OPP,  Default_Cal_Prot_DA_OPP);

		Acess_FPGA(FPGA_CX_H_CPP,  Default_Cal_Prot_DA_Rating);			//Acess_FPGA(FPGA_CX_M_CPP,  Default_Cal_Prot_DA_Rating);
		Acess_FPGA(FPGA_CX_L_CPP,  Default_Cal_Prot_DA_Rating);

		Acess_FPGA(FPGA_CX_H_OCP,  Default_Cal_Prot_DA_OCP);			//Acess_FPGA(FPGA_CX_M_OCP,  Default_Cal_Prot_DA_Normal);
		Acess_FPGA(FPGA_CX_L_OCP,  Default_Cal_Prot_DA_OCP);

		Acess_FPGA(FPGA_On_Off_Reference_Setting, Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
		Acess_FPGA(FPGA_Soft_Start_Delta_VL,0);
		Acess_FPGA(FPGA_Soft_Start_Delta_T,0);

		break;
	case Cal_FPGA_PSensor_L: 	/*  P Sense Low Calibration */
		Circuit_SW0 = I_Calibration_Circuit_Switch_Control[(CC_MODE*6) + (IRange_Low*2) + 0];
		Circuit_SW1 = I_Calibration_Circuit_Switch_Control[(CC_MODE*6) + (IRange_Low*2) + 1];

		Acess_FPGA(FPGA_H_Circuit_Switch_Control_0, Circuit_SW0 |VM_Range);
		Acess_FPGA(FPGA_H_Circuit_Switch_Control_1, Circuit_SW1 );

		Cal_XYZ_Sensor(PSense_Z,IRange_Low);
		Cal_XYZ_Sensor(PSense_X,IRange_Low);
		Cal_XYZ_Sensor(PSense_Y,IRange_Low);
		Acess_FPGA(FPGA_On_Off_Reference_Setting,Set_Normal_P_Sense_Operation |Set_Protection_Ref_Adjust_ON |Set_Cx_Mode );
		break;
	case Cal_FPGA_PSensor_H: 	/*  P Sense H Calibration */
		Circuit_SW0	 = I_Calibration_Circuit_Switch_Control[(CC_MODE*6) + 0];
		Circuit_SW1 = I_Calibration_Circuit_Switch_Control[(CC_MODE*6) + (IRange_High*2) + 1];

		Acess_FPGA(FPGA_H_Circuit_Switch_Control_0, Circuit_SW0 |VM_Range);
		Acess_FPGA(FPGA_H_Circuit_Switch_Control_1, Circuit_SW1 );

		Cal_XYZ_Sensor(PSense_Z,IRange_High);
		Cal_XYZ_Sensor(PSense_X,IRange_High);
		Cal_XYZ_Sensor(PSense_Y,IRange_High);
		Acess_FPGA(FPGA_On_Off_Reference_Setting,Set_Normal_P_Sense_Operation |Set_Protection_Ref_Adjust_ON |Set_Cx_Mode );
		break;
	case Cal_FPGA_OffsetAdjSetDA:
		Acess_FPGA(FPGA_H_Level_Setting, 0);
		break;
	case Cal_FPGA_OffsetAdjValue:
		Acess_FPGA(FPGA_IS_OS_Ref, p3k_Cal_data.OffsetAdjCnt1);
		break;
	case Cal_FPGA_OffsetAdj_End:
		Acess_FPGA(FPGA_On_Off_Reference_Setting, Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
		break;

	default:
		break;
	}
}

#else
void CalibrationFun(void) {
	unsigned short VM_Range=0,Circuit_SW0=0,Circuit_SW1=0;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UWORD *OFFSET_MON_Point,SR_Value,CP_MAX_Value;
	UWORD *OFFSET_MON_Ext_V, *OFFSET_MON_Ext_R;
	ULONG I_V_MON_Total,Register_Temp;
	int i,j;
	UWORD High_Point,Low_Point;
	char val;
	UWORD Shift_Value_Temp,Cal_Status_Temp,Cal_Data_Temp,Res = 0;

	if((P3K_CALIBRATION_BAR.MODE==CV_MODE)||(P3K_CALIBRATION_BAR.MODE==CxCV_MODE)) {
		if(P3K_CALIBRATION_BAR.RANGE==LOW_RANGE)		VM_Range = VM_L_Range;
		else										VM_Range = 0;
	} else if(P3K_CALIBRATION_BAR.MODE==CR_MODE) {
		if(P3K_CALIBRATION_BAR.RANGE)				VM_Range = VM_L_Range;
		else										VM_Range = 0;
	} else {
		VM_Range = 0;
	}
	val = P3K_CALIBRATION_BAR.MODE+(P3K_CALIBRATION_BAR.RANGE*MODE_Number);

	switch(TX_LIST.ADDRL) {
	case Cal_FPGA_Start:		/* Cal Start : Send Load On Command */
		//Acess_FPGA(FPGA_On_Off_Reference_Setting, P_Sense |Acquire_Cont |Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_ON);
		Acess_FPGA(FPGA_On_Off_Reference_Setting,  Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_ON);
		break;
	case Cal_FPGA_End:					/* Cal End :  OCP,Rating OCP,OPP,CPP Calibration & Send Load Off Command */
		//get AD value ten times---(measure current, measure voltage, extern V, extern R)-------------------------
		if(P3K_CALIBRATION_BAR.POINT)
			OFFSET_MON_Point = &P3K_CALIBRATION_BAR.Monitor_Low;
		else
			OFFSET_MON_Point = &P3K_CALIBRATION_BAR.Monitor_High;

		if(P3K_CALIBRATION_BAR.MODE==CV_MODE)
			Register_Temp = FPGA_V_Sense;
		else if( (P3K_CALIBRATION_BAR.MODE==Ext_V_CC_MODE)||(P3K_CALIBRATION_BAR.MODE==Ext_R_CC_MODE) )
			Register_Temp = FPGA_EXT_RV_SENSE;
		else
			Register_Temp = FPGA_I_Sense;

		I_V_MON_Total = 0;
		for(i=0; i<10; i++) {
			I_V_MON_Total += Acess_FPGA(Register_Temp,NULL);
			OSTimeDly(1);
		}

		*OFFSET_MON_Point = I_V_MON_Total /10;
#if Enable_Ext_Measure
		if((P3K_CALIBRATION_BAR.MODE==CC_MODE)||(P3K_CALIBRATION_BAR.MODE==CV_MODE)) {
			if(P3K_CALIBRATION_BAR.MODE==CV_MODE)
				Register_Temp = FPGA_V_Sense;
			else if(P3K_CALIBRATION_BAR.MODE==CC_MODE)
				Register_Temp = FPGA_I_Sense;
			if(P3K_CALIBRATION_BAR.POINT) {
				OFFSET_MON_Ext_V = &Monitor_ExtV_L;
				OFFSET_MON_Ext_R = &Monitor_ExtR_L;
			} else {
				OFFSET_MON_Ext_V = &Monitor_ExtV_H;
				OFFSET_MON_Ext_R = &Monitor_ExtR_H;
			}

			OSTimeDly(2);
			Acess_FPGA(FPGA_External_Applied_Operation_Control,Ext_Control_V);
			OSTimeDly(5);
			I_V_MON_Total = 0;
			for(i=0; i<10; i++) {
				I_V_MON_Total += Acess_FPGA(Register_Temp,NULL);
				OSTimeDly(1);
			}
			*OFFSET_MON_Ext_V = I_V_MON_Total /10;

			OSTimeDly(2);

			Acess_FPGA(FPGA_External_Applied_Operation_Control,Ext_Control_R);
			OSTimeDly(5);
			I_V_MON_Total = 0;
			for(i=0; i<10; i++) {
				I_V_MON_Total += Acess_FPGA(Register_Temp,NULL);
				OSTimeDly(1);
			}
			*OFFSET_MON_Ext_R = I_V_MON_Total /10;

			OSTimeDly(2);
			Acess_FPGA(FPGA_External_Applied_Operation_Control,Ext_Control_OFF);
			OSTimeDly(5);


		}

#endif
		// Calibration OCP, ROCP ---------------------------------------------
//			if( (P3K_CALIBRATION_BAR.MODE==CC_MODE)&&((P3K_CALIBRATION_BAR.RANGE==HIGH_RANGE)||(P3K_CALIBRATION_BAR.RANGE == LOW_RANGE)) )
		if((P3K_CALIBRATION_BAR.MODE==CC_MODE)&&(P3K_CALIBRATION_BAR.RANGE==HIGH_RANGE)) {
			/* OCP Calibration  */
			Acess_FPGA(FPGA_On_Off_Latch_Setting, Set_All_Prot_Limit);
			OSTimeDly(5);
			Cal_Data_Temp = 0;
			for(i=0 ; i<16 ; i++) {
				Shift_Value_Temp = Compare_Value>>i;
				Acess_FPGA(FPGA_CX_H_OCP,Shift_Value_Temp|Cal_Data_Temp);
				OSTimeDly(20);

				Cal_Status_Temp = Read_FPGA_Status(1);

				if(Cal_Status_Temp==0) {
					Menu_Message(" OCP Calibration Error!! ",50,210);
					CtrlFlag1 |= Disp_Middle_Message;
					DMA_Update_Flag = 1;
					Update_Panel();
					OSTimeDly(200);
				}
				if((Cal_Status_Temp&OCP_Prot_Event)==0)
					Shift_Value_Temp = 0;
				Cal_Data_Temp |= Shift_Value_Temp;
			}
			if(P3K_CALIBRATION_BAR.POINT)
				P3K_CALIBRATION_BAR.OCP_Low_Point	= Cal_Data_Temp;
			else
				P3K_CALIBRATION_BAR.OCP_High_Point	= Cal_Data_Temp;
#if 0
			/* Rating OCP */
			Acess_FPGA(FPGA_On_Off_Latch_Setting, Set_All_Prot_Limit);
			OSTimeDly(5);
			Cal_Data_Temp = 0;
			for(i=0 ; i<16 ; i++) {
				Shift_Value_Temp = Compare_Value>>i;
				if(P3K_CALIBRATION_BAR.RANGE==HIGH_RANGE)
					Acess_FPGA(FPGA_CX_H_ROCP,Shift_Value_Temp|Cal_Data_Temp);
				else
					Acess_FPGA(FPGA_CX_L_ROCP,Shift_Value_Temp|Cal_Data_Temp);
				OSTimeDly(20);

				Cal_Status_Temp = Read_FPGA_Status(1);

				if(Cal_Status_Temp==0) {
					Menu_Message(" Rating OCP Calibration Error!! ",50,210);
					CtrlFlag1 |= Disp_Middle_Message;
					DMA_Update_Flag = 1;
					Update_Panel();
					OSTimeDly(200);
				}
				if((Cal_Status_Temp&Rating_OCP_Prot)==0)
					Shift_Value_Temp = 0;
				Cal_Data_Temp |= Shift_Value_Temp;
			}

			if(P3K_CALIBRATION_BAR.POINT)
				P3K_CALIBRATION_BAR.Rating_OCP_Low_Point	= Cal_Data_Temp;
			else
				P3K_CALIBRATION_BAR.Rating_OCP_High_Point	= Cal_Data_Temp;
#endif
		}
		// Calibration OPP, CCP ---------------------------------------------
		//if( (P3K_CALIBRATION_BAR.MODE==CP_MODE)&&((P3K_CALIBRATION_BAR.RANGE == HIGH_RANGE)||(P3K_CALIBRATION_BAR.RANGE == LOW_RANGE)) )
		if((P3K_CALIBRATION_BAR.MODE==CP_MODE)&&(P3K_CALIBRATION_BAR.RANGE == HIGH_RANGE)) {
			/* OPP Calibration */
			Acess_FPGA(FPGA_On_Off_Latch_Setting, Set_All_Prot_Limit);
			OSTimeDly(5);
			Cal_Data_Temp = 0;
			FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_S);
			for(i=0 ; i<16 ; i++) {
				Shift_Value_Temp = Compare_Value>>i;
				Acess_FPGA(FPGA_CX_H_OPP,Shift_Value_Temp|Cal_Data_Temp);
#if 1
				//OSTimeDly(70);
#endif
				OSTimeDly(1);
//FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_C);
				Cal_Status_Temp = Read_FPGA_Status_1(1);
//FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_S);

				if(Cal_Status_Temp==0) {
					Menu_Message(" OPP Calibration Error!! ",50,210);
					CtrlFlag1 |= Disp_Middle_Message;
					DMA_Update_Flag = 1;
					Update_Panel();
					OSTimeDly(200);
				}

				if((Cal_Status_Temp&OPP_Prot_Event)==0)
					Shift_Value_Temp = 0;
				Cal_Data_Temp |= Shift_Value_Temp;
			}
#if 1
			UWORD Recode_d1,Recode_d2;
			//printf("OK_P:%d\n",Cal_Data_Temp);//Cal_Data_Temp = Cal_Data_Temp + 10;
			int k;
			for(k=0; k<35; k++) {
				Cal_Data_Temp -=40;
				Acess_FPGA(FPGA_CX_H_OPP,Cal_Data_Temp);
				OSTimeDly(1);
				Cal_Status_Temp = Read_FPGA_Status_1(1);
				//printf("D%d:%d",k,Cal_Data_Temp);
				if(Cal_Status_Temp&OPP_Prot_Event) {
					//printf("D%d:%d",k,Cal_Data_Temp);
					//printf("-->S\n");
					break;
				} else {
					//printf("D%d:%d",k,Cal_Data_Temp);//printf("-->B\n");//break;
				}
			}
			Recode_d1 = Cal_Data_Temp +20;
			for(k=0; k<30; k++) {
				Cal_Data_Temp +=8;
				Acess_FPGA(FPGA_CX_H_OPP,Cal_Data_Temp);
				OSTimeDly(1);
				Cal_Status_Temp = Read_FPGA_Status_1(1);
				//printf("D%d:%d",k,Cal_Data_Temp);
				if(Cal_Status_Temp&OPP_Prot_Event) {
					//printf("D%d:%d",k,Cal_Data_Temp);//printf("-->S\n");//break;
				} else {
					//printf("D%d:%d",k,Cal_Data_Temp);
					//printf("-->B\n");
					break;
				}
			}
			Recode_d2 = Cal_Data_Temp -4;
			Cal_Data_Temp = (Recode_d1+Recode_d2)/2;

#endif

			if(P3K_CALIBRATION_BAR.POINT) {
				P3K_CALIBRATION_BAR.OPP_Low_Point	= Cal_Data_Temp;


			} else {
				P3K_CALIBRATION_BAR.OPP_High_Point	= Cal_Data_Temp;

			}
#if 0
			/*	CPP  Calibration  */
			Acess_FPGA(FPGA_On_Off_Latch_Setting, Set_All_Prot_Limit);
			OSTimeDly(5);
			Cal_Data_Temp = 0;
			for(i=0; i<16; i++) {
				Shift_Value_Temp = Compare_Value>>i;
				Acess_FPGA(FPGA_CX_H_CPP,Shift_Value_Temp|Cal_Data_Temp );
				//OSTimeDly(20);
				OSTimeDly(30);
				FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_C);
				Cal_Status_Temp = Read_FPGA_Status(1);
				FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_S);
				if(Cal_Status_Temp==0) {
					Menu_Message(" CPP Calibration Error!! ",50,210);
					CtrlFlag1 |= Disp_Middle_Message;
					DMA_Update_Flag = 1;
					Update_Panel();
					OSTimeDly(200);
				}
				if((Cal_Status_Temp&CPP_Prot_Event)==0)
					Shift_Value_Temp = 0;
				Cal_Data_Temp |= Shift_Value_Temp;
			}

			if(P3K_CALIBRATION_BAR.POINT) {
				P3K_CALIBRATION_BAR.CPP_Low_Point	= Cal_Data_Temp;
				//FPGA_W[252]=Cal_Data_Temp;
			} else {
				P3K_CALIBRATION_BAR.CPP_High_Point	= Cal_Data_Temp;
				
			}
#endif
		}
		/*	CxCV Calibration  */
		if(P3K_CALIBRATION_BAR.MODE == CxCV_MODE) {
			if(P3K_CALIBRATION_BAR.POINT)
				P3K_CALIBRATION_BAR.CxCV_Low_Point	= P3K_CALIBRATION_BAR.Set_Value_Low;
			else
				P3K_CALIBRATION_BAR.CxCV_High_Point	= P3K_CALIBRATION_BAR.Set_Value_High;
		}
		//Acess_FPGA(FPGA_On_Off_Reference_Setting, P_Sense |Acquire_Cont |Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
		Acess_FPGA(FPGA_On_Off_Reference_Setting, Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
		break;
	case Cal_FPGA_Fail:
		//Acess_FPGA(FPGA_On_Off_Reference_Setting, P_Sense |Acquire_Cont |Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
		Acess_FPGA(FPGA_On_Off_Reference_Setting, Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
		break;
	case Cal_FPGA_Load_Meas_Default:
#if Enable_Ext_Measure
		if((Data_tmp->CONF.Ext_Setting.Control==0)||(M_num==P_CAL_MODE)) { //Normal
			Acess_FPGA(FPGA_V_Sense_H_Gain,	  p3k_Cal_data.Volt[1].Meas_Value_Gain);
			Acess_FPGA(FPGA_V_Sense_H_Offset,(p3k_Cal_data.Volt[1].Meas_Value_Gain*p3k_Cal_data.Volt[1].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_V_Sense_L_Gain,	  p3k_Cal_data.Volt[0].Meas_Value_Gain);
			Acess_FPGA(FPGA_V_Sense_L_Offset,(p3k_Cal_data.Volt[0].Meas_Value_Gain*p3k_Cal_data.Volt[0].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_I_Sense_H_Gain,	  p3k_Cal_data.Curr[1].Meas_Value_Gain);
			Acess_FPGA(FPGA_I_Sense_H_Offset,(p3k_Cal_data.Curr[1].Meas_Value_Gain*p3k_Cal_data.Curr[1].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_I_Sense_L_Gain,	  p3k_Cal_data.Curr[0].Meas_Value_Gain);
			Acess_FPGA(FPGA_I_Sense_L_Offset,(p3k_Cal_data.Curr[0].Meas_Value_Gain*p3k_Cal_data.Curr[0].Meas_Value_Offset/65535.0));
		} else if (Data_tmp->CONF.Ext_Setting.Control==1) { //Ext_V
			Acess_FPGA(FPGA_V_Sense_H_Gain,	  p3k_Cal_data.Ext_V_Volt[1].Meas_Value_Gain);
			Acess_FPGA(FPGA_V_Sense_H_Offset,(p3k_Cal_data.Ext_V_Volt[1].Meas_Value_Gain*p3k_Cal_data.Volt[1].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_V_Sense_L_Gain,	  p3k_Cal_data.Ext_V_Volt[0].Meas_Value_Gain);
			Acess_FPGA(FPGA_V_Sense_L_Offset,(p3k_Cal_data.Ext_V_Volt[0].Meas_Value_Gain*p3k_Cal_data.Volt[0].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_I_Sense_H_Gain,	  p3k_Cal_data.Ext_V_Curr[1].Meas_Value_Gain);
			Acess_FPGA(FPGA_I_Sense_H_Offset,(p3k_Cal_data.Ext_V_Curr[1].Meas_Value_Gain*p3k_Cal_data.Curr[1].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_I_Sense_L_Gain,	  p3k_Cal_data.Ext_V_Curr[0].Meas_Value_Gain);
			Acess_FPGA(FPGA_I_Sense_L_Offset,(p3k_Cal_data.Ext_V_Curr[0].Meas_Value_Gain*p3k_Cal_data.Curr[0].Meas_Value_Offset/65535.0));
		} else { //Ext_R or Ext_Rinv
			Acess_FPGA(FPGA_V_Sense_H_Gain,	  p3k_Cal_data.Ext_R_Volt[1].Meas_Value_Gain);
			Acess_FPGA(FPGA_V_Sense_H_Offset,(p3k_Cal_data.Ext_R_Volt[1].Meas_Value_Gain*p3k_Cal_data.Volt[1].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_V_Sense_L_Gain,	  p3k_Cal_data.Ext_R_Volt[0].Meas_Value_Gain);
			Acess_FPGA(FPGA_V_Sense_L_Offset,(p3k_Cal_data.Ext_R_Volt[0].Meas_Value_Gain*p3k_Cal_data.Volt[0].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_I_Sense_H_Gain,	  p3k_Cal_data.Ext_R_Curr[1].Meas_Value_Gain);
			Acess_FPGA(FPGA_I_Sense_H_Offset,(p3k_Cal_data.Ext_R_Curr[1].Meas_Value_Gain*p3k_Cal_data.Curr[1].Meas_Value_Offset/65535.0));
			Acess_FPGA(FPGA_I_Sense_L_Gain,	  p3k_Cal_data.Ext_R_Curr[0].Meas_Value_Gain);
			Acess_FPGA(FPGA_I_Sense_L_Offset,(p3k_Cal_data.Ext_R_Curr[0].Meas_Value_Gain*p3k_Cal_data.Curr[0].Meas_Value_Offset/65535.0));
		}
#else
Acess_FPGA(FPGA_V_Sense_H_Gain,	  p3k_Cal_data.Volt[1].Meas_Value_Gain);
Acess_FPGA(FPGA_V_Sense_H_Offset,(p3k_Cal_data.Volt[1].Meas_Value_Gain*p3k_Cal_data.Volt[1].Meas_Value_Offset/65535.0));
Acess_FPGA(FPGA_V_Sense_L_Gain,	  p3k_Cal_data.Volt[0].Meas_Value_Gain);
Acess_FPGA(FPGA_V_Sense_L_Offset,(p3k_Cal_data.Volt[0].Meas_Value_Gain*p3k_Cal_data.Volt[0].Meas_Value_Offset/65535.0));
Acess_FPGA(FPGA_I_Sense_H_Gain,	  p3k_Cal_data.Curr[1].Meas_Value_Gain);
Acess_FPGA(FPGA_I_Sense_H_Offset,(p3k_Cal_data.Curr[1].Meas_Value_Gain*p3k_Cal_data.Curr[1].Meas_Value_Offset/65535.0));
Acess_FPGA(FPGA_I_Sense_L_Gain,	  p3k_Cal_data.Curr[0].Meas_Value_Gain);
Acess_FPGA(FPGA_I_Sense_L_Offset,(p3k_Cal_data.Curr[0].Meas_Value_Gain*p3k_Cal_data.Curr[0].Meas_Value_Offset/65535.0));
#endif
		break;
	case Cal_FPGA_PSensor_H: 	/*  P Sense H Calibration */
		//Circuit_SW0 = I_Calibration_Circuit_Switch_Control[(CC_MODE*6) + (IRange_High*2) + 0];
		Circuit_SW0	 = I_Calibration_Circuit_Switch_Control[(CC_MODE*6) + 0];
		Circuit_SW1 = I_Calibration_Circuit_Switch_Control[(CC_MODE*6) + (IRange_High*2) + 1];

		Acess_FPGA(FPGA_H_Circuit_Switch_Control_0, Circuit_SW0 |VM_Range);
		Acess_FPGA(FPGA_H_Circuit_Switch_Control_1, Circuit_SW1 );

		Cal_XYZ_Sensor(PSense_Z,IRange_High);
		Cal_XYZ_Sensor(PSense_X,IRange_High);
		Cal_XYZ_Sensor(PSense_Y,IRange_High);
		Acess_FPGA(FPGA_On_Off_Reference_Setting,Set_Normal_P_Sense_Operation |Set_Protection_Ref_Adjust_ON |Set_Cx_Mode );
		break;
	case Cal_FPGA_Prot: 	/* Protection  Calibration */
		if((P3K_CALIBRATION_BAR.MODE==CC_MODE)&&(P3K_CALIBRATION_BAR.RANGE==HIGH_RANGE)) {
			High_Point	= P3K_CALIBRATION_BAR.HP_Volt	/ (ptrMODEL_TYPE->CALI_HP)[14].Resolution;
			Low_Point	= P3K_CALIBRATION_BAR.LP_Volt	/ (ptrMODEL_TYPE->CALI_HP)[14].Resolution;
			//High_Point	= P3K_CALIBRATION_BAR.HP_Volt	/ (double)0.15;
			//Low_Point	= P3K_CALIBRATION_BAR.LP_Volt	/ (double)0.15;
//printf("val: %d\n",val);

			/* OCP */
			P3K_CALIBRATION_BAR.OCP_Gain	= (double) (P3K_CALIBRATION_BAR.OCP_High_Point - P3K_CALIBRATION_BAR.OCP_Low_Point) /(double) (High_Point - Low_Point);
			P3K_CALIBRATION_BAR.OCP_Offset	= ( (double)P3K_CALIBRATION_BAR.OCP_High_Point	- (P3K_CALIBRATION_BAR.OCP_Gain*High_Point) );

			if(P3K_CALIBRATION_BAR.OCP_Offset < 0)
				Cal_Offset_Error |= OCP_Err;


			if(((((ptrMODEL_TYPE->PROT)[IRange_High].Max)* P3K_CALIBRATION_BAR.OCP_Gain)+P3K_CALIBRATION_BAR.OCP_Offset)>65535.0) {
				//Show_Prot_Error_Window(0,P3K_CALIBRATION_BAR.OCP_Gain,P3K_CALIBRATION_BAR.OCP_Offset,High_Point,Low_Point,P3K_CALIBRATION_BAR.OCP_High_Point,P3K_CALIBRATION_BAR.OCP_Low_Point);
				P3K_CALIBRATION_BAR.OCP_Gain	= 1;
				P3K_CALIBRATION_BAR.OCP_Offset	= 0;
			}
#if 0
			/* Rating OCP*/
			P3K_CALIBRATION_BAR.Rating_OCP_Gain		= (double) (P3K_CALIBRATION_BAR.Rating_OCP_High_Point - P3K_CALIBRATION_BAR.Rating_OCP_Low_Point) /(double) (High_Point - Low_Point);
			P3K_CALIBRATION_BAR.Rating_OCP_Offset	= ( (double)P3K_CALIBRATION_BAR.Rating_OCP_High_Point - (P3K_CALIBRATION_BAR.Rating_OCP_Gain*High_Point) );
			if(P3K_CALIBRATION_BAR.Rating_OCP_Offset < 0)
				Cal_Offset_Error |= ROCP_Err;
			if(((((ptrMODEL_TYPE->PROT)[IRange_High].Max)* P3K_CALIBRATION_BAR.Rating_OCP_Gain)+P3K_CALIBRATION_BAR.Rating_OCP_Offset)>65535.0) {
				//Show_Prot_Error_Window(1,P3K_CALIBRATION_BAR.Rating_OCP_Gain,P3K_CALIBRATION_BAR.Rating_OCP_Offset,High_Point,Low_Point,P3K_CALIBRATION_BAR.Rating_OCP_High_Point,P3K_CALIBRATION_BAR.Rating_OCP_Low_Point);
				P3K_CALIBRATION_BAR.Rating_OCP_Gain		= 1;
				P3K_CALIBRATION_BAR.Rating_OCP_Offset	= 0;
			}
#endif
		}

		if((P3K_CALIBRATION_BAR.MODE==CP_MODE)&&(P3K_CALIBRATION_BAR.RANGE==HIGH_RANGE)) {
			//High_Point	= (P3K_CALIBRATION_BAR.HP_Volt	* P3K_CALIBRATION_BAR.HP_Curr)	/ (ptrMODEL_TYPE->CP)[(IRange_High * 10)].Resolution;
			//Low_Point	= (P3K_CALIBRATION_BAR.LP_Volt	* P3K_CALIBRATION_BAR.LP_Curr)	/ (ptrMODEL_TYPE->CP)[(IRange_High * 10)].Resolution;
			High_Point	= (P3K_CALIBRATION_BAR.HP_Volt	* P3K_CALIBRATION_BAR.HP_Curr)	/ (ptrMODEL_TYPE->CALI_HP)[5].Resolution;
			Low_Point	= (P3K_CALIBRATION_BAR.LP_Volt	* P3K_CALIBRATION_BAR.LP_Curr)	/ (ptrMODEL_TYPE->CALI_HP)[5].Resolution;
			/* OPP */
			P3K_CALIBRATION_BAR.OPP_Gain	= (double) (P3K_CALIBRATION_BAR.OPP_High_Point - P3K_CALIBRATION_BAR.OPP_Low_Point) /(double) (High_Point - Low_Point);
			P3K_CALIBRATION_BAR.OPP_Offset	= ( (double)P3K_CALIBRATION_BAR.OPP_High_Point	- (P3K_CALIBRATION_BAR.OPP_Gain*High_Point) );
#if Normal_TEST
			printf("H_P:%d\n",P3K_CALIBRATION_BAR.OPP_High_Point);
			printf("L_P:%d\n",P3K_CALIBRATION_BAR.OPP_Low_Point);
			printf("H_V:%d\n",High_Point);
			printf("L_V:%d\n",Low_Point);
#endif

			if(P3K_CALIBRATION_BAR.OPP_Offset < 0)	Cal_Offset_Error |= OPP_Err;

			CP_MAX_Value = (ptrMODEL_TYPE->PROT)[PROT_OPP_H].Max;
			if(((CP_MAX_Value*P3K_CALIBRATION_BAR.OPP_Gain)+P3K_CALIBRATION_BAR.OPP_Offset)>65535.0) {
				//Show_Prot_Error_Window(2,P3K_CALIBRATION_BAR.OPP_Gain,P3K_CALIBRATION_BAR.OPP_Offset,High_Point,Low_Point,P3K_CALIBRATION_BAR.OPP_High_Point,P3K_CALIBRATION_BAR.OPP_Low_Point);
				P3K_CALIBRATION_BAR.OPP_Gain	= 1;
				P3K_CALIBRATION_BAR.OPP_Offset	= 0;
			}
#if 0
			/* CPP */
			P3K_CALIBRATION_BAR.CPP_Gain	= (double) (P3K_CALIBRATION_BAR.CPP_High_Point - P3K_CALIBRATION_BAR.CPP_Low_Point) /(double) (High_Point - Low_Point);
			P3K_CALIBRATION_BAR.CPP_Offset	= ( (double)P3K_CALIBRATION_BAR.CPP_High_Point	- (P3K_CALIBRATION_BAR.CPP_Gain*High_Point) );

			if(P3K_CALIBRATION_BAR.CPP_Offset < 0)
				Cal_Offset_Error |= CPP_Err;

			if(((CP_MAX_Value*P3K_CALIBRATION_BAR.CPP_Gain)+P3K_CALIBRATION_BAR.CPP_Offset)>65535.0) {
				//Show_Prot_Error_Window(3,P3K_CALIBRATION_BAR.CPP_Gain,P3K_CALIBRATION_BAR.CPP_Offset,High_Point,Low_Point,P3K_CALIBRATION_BAR.CPP_High_Point,P3K_CALIBRATION_BAR.CPP_Low_Point);
				P3K_CALIBRATION_BAR.CPP_Gain	= 1;
				P3K_CALIBRATION_BAR.CPP_Offset	= 0;
			}
#endif
		}
		/*	CxCV Calibration  */
		if(P3K_CALIBRATION_BAR.MODE == CxCV_MODE) {
			High_Point	= P3K_CALIBRATION_BAR.HP_Volt	/ (ptrMODEL_TYPE->CALI_HP)[val].Resolution; //0.005
			Low_Point	= P3K_CALIBRATION_BAR.LP_Volt	/ (ptrMODEL_TYPE->CALI_HP)[val].Resolution; //0.005
#if 1
			UWORD H_count = 42000;
			UWORD L_count = 4200;
			if(Model_Number == MODEL3031E) {

			}
#endif
			//P3K_CALIBRATION_BAR.CxCV_Gain	= (double) (P3K_CALIBRATION_BAR.CxCV_High_Point - P3K_CALIBRATION_BAR.CxCV_Low_Point) /(double) (High_Point - Low_Point);
			P3K_CALIBRATION_BAR.CxCV_Gain	= (double) (H_count - L_count) /(double) (High_Point - Low_Point);
			P3K_CALIBRATION_BAR.CxCV_Offset	= ((double)H_count	- (P3K_CALIBRATION_BAR.CxCV_Gain*High_Point) );

			if(P3K_CALIBRATION_BAR.CxCV_Offset < 0)
				Cal_Offset_Error |= CXCV_Err;

			if(((((ptrMODEL_TYPE->CV)[0].Max)* P3K_CALIBRATION_BAR.CxCV_Gain)+P3K_CALIBRATION_BAR.CxCV_Offset)>65535.0) {
				//Show_Prot_Error_Window(4,P3K_CALIBRATION_BAR.CxCV_Gain,P3K_CALIBRATION_BAR.CxCV_Offset,High_Point,Low_Point,P3K_CALIBRATION_BAR.CxCV_High_Point,P3K_CALIBRATION_BAR.CxCV_Low_Point);
				P3K_CALIBRATION_BAR.CxCV_Gain	= 1;
				P3K_CALIBRATION_BAR.CxCV_Offset	= 0;
			}

			P3K_CALIBRATION_BAR.CxCV = Step_To_CNT(Data_tmp->CV.STA[Data_tmp->VRange].VALUE1,P3K_CALIBRATION_BAR.CxCV_Gain,P3K_CALIBRATION_BAR.CxCV_Offset);
			if(HIGH_RANGE==P3K_CALIBRATION_BAR.RANGE)
				Acess_FPGA(Cx_CV_H_Value, P3K_CALIBRATION_BAR.CxCV);
			else
				Acess_FPGA(Cx_CV_L_Value, P3K_CALIBRATION_BAR.CxCV);
		}

		//Acess_FPGA(FPGA_On_Off_Reference_Setting, P_Sense |Acquire_Cont |Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
		Acess_FPGA(FPGA_On_Off_Reference_Setting, Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
		break;
	case Cal_FPGA_Load_Cal_Default: /* Load  Calibration Default  & Calibration Start*/
		Acess_FPGA(FPGA_V_Sense_H_Gain,		Max_Value);
		Acess_FPGA(FPGA_V_Sense_L_Gain,		Max_Value);
		Acess_FPGA(FPGA_V_Sense_H_Offset,	0);
		Acess_FPGA(FPGA_V_Sense_L_Offset,	0);

		Acess_FPGA(FPGA_I_Sense_H_Gain,		Max_Value);			//Acess_FPGA(FPGA_I_Sense_M_Gain, 	Max_Value);
		Acess_FPGA(FPGA_I_Sense_L_Gain, 	Max_Value);
		Acess_FPGA(FPGA_I_Sense_H_Offset,	0);			//Acess_FPGA(FPGA_I_Sense_M_Offset,	0);
		Acess_FPGA(FPGA_I_Sense_L_Offset,	0);

		Acess_FPGA(FPGA_EXT_RV_SENSE_Gain,  Max_Value);
		Acess_FPGA(FPGA_EXT_RV_SENSE_Offset,0);

		Acess_FPGA(Cx_CV_H_Step, 0);
		Acess_FPGA(Cx_CV_L_Step, 0);
		if((P3K_CALIBRATION_BAR.MODE==R_IMON_MODE)&&(P3K_CALIBRATION_BAR.POINT)) {
			Acess_FPGA(FPGA_Rear_IMON_Output_Adjust,63);	//Acess_FPGA(FPGA_Front_IMON_Output_Adjust,63);
		} else {
			Acess_FPGA(FPGA_Rear_IMON_Output_Adjust,0);		//Acess_FPGA(FPGA_Front_IMON_Output_Adjust,0);
		}

		Acess_FPGA(FPGA_On_Off_Latch_Setting, Set_All_Prot_Limit);

		if(P3K_CALIBRATION_BAR.MODE==Ext_V_CC_MODE)
			Acess_FPGA(FPGA_External_Applied_Operation_Control,Ext_Control_V);
		else if(P3K_CALIBRATION_BAR.MODE==Ext_R_CC_MODE)
			Acess_FPGA(FPGA_External_Applied_Operation_Control,Ext_Control_R);
		else
			Acess_FPGA(FPGA_External_Applied_Operation_Control,Ext_Control_OFF);

		Circuit_SW0 = I_Calibration_Circuit_Switch_Control[(P3K_CALIBRATION_BAR.MODE*6) + (P3K_CALIBRATION_BAR.RANGE*2) + 0];
		Circuit_SW1 = I_Calibration_Circuit_Switch_Control[(P3K_CALIBRATION_BAR.MODE*6) + (P3K_CALIBRATION_BAR.RANGE*2) + 1];

		if(P3K_CALIBRATION_BAR.MODE==CV_MODE)			Res |= CV_Response_slow;
		else if(P3K_CALIBRATION_BAR.MODE==CP_MODE)		Res |= CP_Response_slow;
		else if (P3K_CALIBRATION_BAR.MODE==CxCV_MODE)	Res |= CXCV_Response_slow;

		if((P3K_CALIBRATION_BAR.MODE==CC_MODE)||(P3K_CALIBRATION_BAR.MODE>=R_IMON_MODE))
			SR_Value = 30000;
		else //CR,CV,CP,CXCV
			SR_Value = 5000;

		Acess_FPGA(FPGA_H_Circuit_Switch_Control_0, Circuit_SW0 |VM_Range);
		Acess_FPGA(FPGA_H_Circuit_Switch_Control_1, Circuit_SW1 |Res);
		Acess_FPGA(FPGA_H_Level_Slew_Rate, SR_Value);

		if(P3K_CALIBRATION_BAR.POINT)
			Cal_Data_Temp = P3K_CALIBRATION_BAR.Set_Value_Low;
		else
			Cal_Data_Temp = P3K_CALIBRATION_BAR.Set_Value_High;

		if(P3K_CALIBRATION_BAR.MODE==CxCV_MODE) {

			if(P3K_CALIBRATION_BAR.POINT) {
				Acess_FPGA(Cx_CV_L_Value, CxCV_L_count);
				Acess_FPGA(Cx_CV_H_Value, CxCV_L_count);
			} else {
				Acess_FPGA(Cx_CV_L_Value, CxCV_H_count);
				Acess_FPGA(Cx_CV_H_Value, CxCV_H_count);
			}
			Acess_FPGA(FPGA_H_Level_Setting, Cal_Data_Temp);
		} else {
			Acess_FPGA(FPGA_H_Level_Setting, Cal_Data_Temp);
			Acess_FPGA(Cx_CV_H_Value, P3K_CALIBRATION_BAR.CxCV);
			Acess_FPGA(Cx_CV_L_Value, P3K_CALIBRATION_BAR.CxCV);
		}

		Acess_FPGA(FPGA_VON_H, 0);
		Acess_FPGA(FPGA_VON_L, 0);

		Acess_FPGA(FPGA_XH_OS_Ref, P3K_CALIBRATION_BAR.PSensor.XH_Value);
		Acess_FPGA(FPGA_YH_OS_Ref, P3K_CALIBRATION_BAR.PSensor.YH_Value);
		Acess_FPGA(FPGA_ZH_OS_Ref, P3K_CALIBRATION_BAR.PSensor.ZH_Value);
#if 1
		Acess_FPGA(FPGA_XL_OS_Ref, P3K_CALIBRATION_BAR.PSensor.XH_Value);
		Acess_FPGA(FPGA_YL_OS_Ref, P3K_CALIBRATION_BAR.PSensor.YH_Value);
		Acess_FPGA(FPGA_ZL_OS_Ref, P3K_CALIBRATION_BAR.PSensor.ZH_Value);
#else
Acess_FPGA(FPGA_XL_OS_Ref, P3K_CALIBRATION_BAR.PSensor.XL_Value);
Acess_FPGA(FPGA_YL_OS_Ref, P3K_CALIBRATION_BAR.PSensor.YL_Value);
Acess_FPGA(FPGA_ZL_OS_Ref, P3K_CALIBRATION_BAR.PSensor.ZL_Value);
#endif

		Acess_FPGA(FPGA_CX_H_OPP,  Default_Cal_Prot_DA_OPP);			//Acess_FPGA(FPGA_CX_M_OPP,  Default_Cal_Prot_DA_Normal);
		Acess_FPGA(FPGA_CX_L_OPP,  Default_Cal_Prot_DA_OPP);

		Acess_FPGA(FPGA_CX_H_CPP,  Default_Cal_Prot_DA_Rating);			//Acess_FPGA(FPGA_CX_M_CPP,  Default_Cal_Prot_DA_Rating);
		Acess_FPGA(FPGA_CX_L_CPP,  Default_Cal_Prot_DA_Rating);

		Acess_FPGA(FPGA_CX_H_OCP,  Default_Cal_Prot_DA_OCP);			//Acess_FPGA(FPGA_CX_M_OCP,  Default_Cal_Prot_DA_Normal);
		Acess_FPGA(FPGA_CX_L_OCP,  Default_Cal_Prot_DA_OCP);

		//Acess_FPGA(FPGA_On_Off_Reference_Setting, P_Sense |Acquire_Cont |Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
		Acess_FPGA(FPGA_On_Off_Reference_Setting, Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
#if 1
		Acess_FPGA(FPGA_Soft_Start_Delta_VL,0);
		Acess_FPGA(FPGA_Soft_Start_Delta_T,0);
#endif
		break;
	case Cal_FPGA_PSensor_L: 	/*  P Sense Low Calibration */
		Circuit_SW0 = I_Calibration_Circuit_Switch_Control[(CC_MODE*6) + (IRange_Low*2) + 0];
		Circuit_SW1 = I_Calibration_Circuit_Switch_Control[(CC_MODE*6) + (IRange_Low*2) + 1];

		Acess_FPGA(FPGA_H_Circuit_Switch_Control_0, Circuit_SW0 |VM_Range);
		Acess_FPGA(FPGA_H_Circuit_Switch_Control_1, Circuit_SW1 );

		Cal_XYZ_Sensor(PSense_Z,IRange_Low);
		Cal_XYZ_Sensor(PSense_X,IRange_Low);
		Cal_XYZ_Sensor(PSense_Y,IRange_Low);
		Acess_FPGA(FPGA_On_Off_Reference_Setting,Set_Normal_P_Sense_Operation |Set_Protection_Ref_Adjust_ON |Set_Cx_Mode );
		break;
	case Cal_FPGA_OffsetAdjSetDA:
		Acess_FPGA(FPGA_H_Level_Setting, 0);
		break;
	case Cal_FPGA_OffsetAdjValue:
		Acess_FPGA(FPGA_IS_OS_Ref, p3k_Cal_data.OffsetAdjCnt1);
		break;
	case Cal_FPGA_OffsetAdj_End:
		//Acess_FPGA(FPGA_On_Off_Reference_Setting, P_Sense |Acquire_Cont |Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
		Acess_FPGA(FPGA_On_Off_Reference_Setting, Set_Protection_Ref_Adjust_ON |Set_Cx_Mode |Set_Load_OFF);
		break;

	default:
		break;
	}
}
#endif
void WriteFlashFun(void) {
	WORD i;
	if(TX_LIST.ADDRH==0x40) {		/* Erase Flash */
		TXData[1] = 4;
		TXData[2] = TX_LIST.ADDRH;
		TXData[3] = 1;
	}
}

void WriteSEQDataToFPGA(void) {
	UWORD i;
	p3k_send_tx_list tx_data;
	UBYTE _pause_flag =0;
	UBYTE _step0_wait=0;
	unsigned short dat1,dat2;

	Acess_FPGA(Cx_CV_Response, 0);
	Acess_FPGA(FPGA_IS_OS_Ref, p3k_Cal_data.CC_offseAdj[1]);

//	WriteSEQDataToFPGA_flag =1;
	/*Write Prog Data To FPGA*/
	Acess_FPGA(FPGA_Control,			Clear_Write_Address);
	Acess_FPGA(FPGA_Seq_Start_Address,	Prog_Seq_Data.Start_Address);

	for(i=0 ; i<Prog_Seq_Data.Setting_Count ; i++) {
		if((Prog_Seq_Data.FPGA_Seq_Data[i].CS1_Setting)& PAUSE_ON)
			_pause_flag = 1;
		if(0) { ////   if((i==0)&&(_pause_flag)){ //add first step for wait trigIn signal
			_step0_wait =1;
			Acess_FPGA(FPGA_Seq_Load_On_Setting,	0);
			Acess_FPGA(FPGA_Seq_Slew_Rate,			0x4100);
			dat1 = Prog_Seq_Data.FPGA_Seq_Data[0].CS0_Setting;  //抓回正確的 range, 全部都CC mode為主, Adam~
			if((dat1&0x6000)==0x6000)		dat2 = I_CC_Low_0;
			else if((dat1&0x1400)==0x1400)	dat2 = I_CC_High_0;
			else							dat2 = 0;//I_CC_Mid_0; //Adam???
			if(dat1 & 0x800)					dat2 |= 0x800;

			Acess_FPGA(FPGA_Seq_Circuit_Switch_0,	dat2); //
			Acess_FPGA(FPGA_Seq_Circuit_Switch_1,	0x4050);//Adam???
			Acess_FPGA(FPGA_Seq_Duration_Time,		0);
			Acess_FPGA(FPGA_Seq_Ramp_Delta_VH,		0);
			Acess_FPGA(FPGA_Seq_Ramp_Delta_VL,		0);
			Acess_FPGA(FPGA_Seq_Ramp_Delta_T,		0);
		}
		Acess_FPGA(FPGA_Seq_Load_On_Setting,	Prog_Seq_Data.FPGA_Seq_Data[i].Level_Setting);
		Acess_FPGA(FPGA_Seq_Slew_Rate,			Prog_Seq_Data.FPGA_Seq_Data[i].SR_Setting);
		Acess_FPGA(FPGA_Seq_Circuit_Switch_0,	Prog_Seq_Data.FPGA_Seq_Data[i].CS0_Setting);
		Acess_FPGA(FPGA_Seq_Circuit_Switch_1,	Prog_Seq_Data.FPGA_Seq_Data[i].CS1_Setting);
		Acess_FPGA(FPGA_Seq_Duration_Time,		Prog_Seq_Data.FPGA_Seq_Data[i].Duration_Setting);
		Acess_FPGA(FPGA_Seq_Ramp_Delta_VH,		Prog_Seq_Data.FPGA_Seq_Data[i].Ramp_Delta_VH);
		Acess_FPGA(FPGA_Seq_Ramp_Delta_VL,		Prog_Seq_Data.FPGA_Seq_Data[i].Ramp_Delta_VL);
		Acess_FPGA(FPGA_Seq_Ramp_Delta_T,		Prog_Seq_Data.FPGA_Seq_Data[i].Ramp_Delta_T);
	}

	if(Prog_Seq_Data.Setting_Count) {
		for(i=0 ; i<16 ; i++) {
			if(_step0_wait)
				Acess_FPGA(FPGA_Jump_Point_Address,	(Prog_Seq_Data.P3k_FPGA_Jump_Data[i].Jump_Address+1));
			else
				Acess_FPGA(FPGA_Jump_Point_Address, Prog_Seq_Data.P3k_FPGA_Jump_Data[i].Jump_Address);

			Acess_FPGA(FPGA_Write_JP_Counter,	Prog_Seq_Data.P3k_FPGA_Jump_Data[i].Jump_Number);
			Acess_FPGA(FPGA_Jump_Ramp_SlewRate, Prog_Seq_Data.P3k_FPGA_Jump_Data[i].Ramp_SlewRate);
			Acess_FPGA(FPGA_Jump_Ramp_CS1,		Prog_Seq_Data.P3k_FPGA_Jump_Data[i].Ramp_CS1);
			Acess_FPGA(FPGA_Jump_Ramp_Delta_VH, Prog_Seq_Data.P3k_FPGA_Jump_Data[i].Ramp_Delta_VH);
			Acess_FPGA(FPGA_Jump_Ramp_Delta_VL, Prog_Seq_Data.P3k_FPGA_Jump_Data[i].Ramp_Delta_VL);
		}
	}
//	WriteSEQDataToFPGA_flag = 0;
	SeqSyncWaitStep = _step0_wait;

}

void PlaceFSeqMemory(void) {
	double Cal_Gain,Cal_Offset;
	UBYTE Memory_Mode,Memory_IRange,Memory_VRange;
	UWORD LoadON_Value,LoadOFF_Value,Memory_SlewRate,Memory_SR_Setting =0;
	UWORD i,Response_Setting,Memory_Time_Unit = 0;
	P3k_FPGA_Seq_Str	*FPGA_Seq_Ptr;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	Prog_Seq_Data.Setting_Count = 0;

	if(P3k_FSeq_Data.FSeq_Loop!=1) {
		Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Jump_Address = 0;
		if(0==P3k_FSeq_Data.FSeq_Loop)
			Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Jump_Number = 0;
		else
			Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Jump_Number = P3k_FSeq_Data.FSeq_Loop - 1;
	}

	if(0==P3k_FSeq_Data.FSeq_TB_Range)
		Memory_Time_Unit = Time_Unit_1uS;
	else
		Memory_Time_Unit = Time_Unit_10uS;

#if Enable_FSEQ_RPT
	for(i=0 ; i<P3k_FSeq_Data.RPTStep+1 ; i++ ) {
#else
	for(i=0 ; i<P3k_FSeq_Data.FSeq_Max_Step+1 ; i++ ) {
#endif
		Memory_Mode 	= P3k_FSeq_Data.FSeq_Mode;
		Memory_VRange	= P3k_FSeq_Data.FSeq_Range/2;
		Memory_IRange	= P3k_FSeq_Data.FSeq_Range%2;

		FPGA_Seq_Ptr = &Prog_Seq_Data.FPGA_Seq_Data[Prog_Seq_Data.Setting_Count++];
		FPGA_Seq_Ptr->SEQ_Mode	= P3k_FSeq_Data.FSeq_Mode;
		FPGA_Seq_Ptr->SEQ_Range	= P3k_FSeq_Data.FSeq_Range;
		Response_Setting = get_response(Memory_Mode);
		switch(Memory_Mode) {
		default:
			Debug_printf("PlaceFSeqMemory Error\n");
		case CC_MODE:
			Cal_Gain			= p3k_Cal_data.CC_Data[Memory_IRange].Cal_Value_Gain;
			Cal_Offset			= p3k_Cal_data.CC_Data[Memory_IRange].Cal_Value_Offset;
			LoadON_Value		= P3k_FSeq_Data.FSeq_Step[i].FSeq_Value;
			LoadOFF_Value		= (ptrMODEL_TYPE->CC)[0+(Memory_IRange*10)].Min;
			Memory_SlewRate 	= Data_tmp->CC.STA[Memory_IRange].SLEWRATEUP * SR_StepToCountRatio;

			break;
		case CR_MODE:
			Cal_Gain			= p3k_Cal_data.CR_Data[Memory_IRange].Cal_Value_Gain;
			Cal_Offset			= p3k_Cal_data.CR_Data[Memory_IRange].Cal_Value_Offset;
			LoadON_Value		= P3k_FSeq_Data.FSeq_Step[i].FSeq_Value;
			LoadOFF_Value		= (ptrMODEL_TYPE->CR)[0+(Memory_IRange*10)].Min;
			Memory_SlewRate 	= (Data_tmp->CR.STA[Data_tmp->IRange].SLEWRATEUP * SR_StepToCountRatio)/10;

			break;
		}

		FPGA_Seq_Ptr->CS0_Setting	= I_Circuit_Switch_Control[(Memory_Mode*6) + (Memory_IRange*2) + 0];
		FPGA_Seq_Ptr->CS1_Setting	= I_Circuit_Switch_Control[(Memory_Mode*6) + (Memory_IRange*2) + 1];

		FPGA_Seq_Ptr->Duration_Setting = P3k_FSeq_Data.FSeq_Time_Base;

		FPGA_Seq_Ptr->Ramp_Delta_VH 	= 0;
		FPGA_Seq_Ptr->Ramp_Delta_VL 	= 0;
		FPGA_Seq_Ptr->Ramp_Delta_T		= 0;

		if(VRange_Low==Memory_VRange)
			FPGA_Seq_Ptr->CS0_Setting |= VM_L_Range;

		FPGA_Seq_Ptr->Level_Step	= LoadON_Value;
		FPGA_Seq_Ptr->Level_Setting	= Step_To_CNT(FPGA_Seq_Ptr->Level_Step ,Cal_Gain,Cal_Offset);

		FPGA_Seq_Ptr->SR_Setting	= Memory_SlewRate;
		FPGA_Seq_Ptr->CS1_Setting  |= Memory_SR_Setting | Memory_Time_Unit ;
		/* Last Setting*/
		Prog_Seq_Data.FPGA_Seq_Data[1024] = *FPGA_Seq_Ptr;
		if(P3k_FSeq_Data.FSeq_Last_Load)
			Prog_Seq_Data.FPGA_Seq_Data[1024].Level_Step = P3k_FSeq_Data.FSeq_Last_Level;
		else
			Prog_Seq_Data.FPGA_Seq_Data[1024].Level_Step = LoadOFF_Value;
		Prog_Seq_Data.FPGA_Seq_Data[1024].Level_Setting = Step_To_CNT(Prog_Seq_Data.FPGA_Seq_Data[1024].Level_Step,Cal_Gain,Cal_Offset);
		Prog_Seq_Data.Last_Load_Setting = P3k_FSeq_Data.FSeq_Last_Load;

		if(Switch_ON==P3k_FSeq_Data.FSeq_Step[i].TrigOut_Setting)	FPGA_Seq_Ptr->CS1_Setting |= TrigOut_ON;
	}

	if(P3k_FSeq_Data.FSeq_Loop!=1) {
		Prog_Seq_Data.FPGA_Seq_Data[Prog_Seq_Data.Setting_Count-1].CS1_Setting |= Jump_ON | Jump_A_Point;
		Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Ramp_Delta_VH	= 0;
		Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Ramp_Delta_VL	= 0;
		Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Ramp_SlewRate	= 0;
		Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Ramp_CS1		= 0;
	}
	WriteSEQDataToFPGA();
}
#if Enable_Func_DisTime
		unsigned long total_SEQ_time;
#endif

void PlaceNSeqMemory(UWORD Seq_No) {
	double Cal_Gain,Cal_Offset;
	UBYTE Memory_Mode,Memory_IRange,Memory_VRange;
	UWORD LoadON_Value,LoadOFF_Value,Memory_SlewRate,Memory_SR_Setting;
	UWORD Response_Setting,Memory_Time_Unit = 0;
	UWORD i;
	ULONG Jump_Setting,Ramp_mS_Time;
	UWORD Pre_Step,Goal_Step;
	UBYTE re_Range;

	p3k_Ramp_Str p3k_Ramp_Data;
	NSeq_Timing_Str		*NSeq_Timing_Ptr;
	NSeq_Data_Str		*NSeq_Data_Ptr;
	P3k_FPGA_Seq_Str	*FPGA_Seq_Ptr;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	P3k_Parallel_Str *Parallel_Ptr = &P3k_Chan_Data.CONF.Para_Data;

	NSeq_Timing_Ptr = &P3k_NSeq_Data.NSeq_Seq[Seq_No];
	if(NSeq_Timing_Ptr->NSeq_Loop!=1) {
		Prog_Seq_Data.P3k_FPGA_Jump_Data[Prog_Seq_Data.Jump_Count].Jump_Address	= Prog_Seq_Data.Setting_Count;
		if(0==NSeq_Timing_Ptr->NSeq_Loop)
			Prog_Seq_Data.P3k_FPGA_Jump_Data[Prog_Seq_Data.Jump_Count].Jump_Number = 0;
		else
			Prog_Seq_Data.P3k_FPGA_Jump_Data[Prog_Seq_Data.Jump_Count].Jump_Number = NSeq_Timing_Ptr->NSeq_Loop - 1;
	}

	re_Range = NSeq_Timing_Ptr->NSeq_Range;
	for(i=0 ; i<NSeq_Timing_Ptr->NSeq_Max_Step ; i++ ) {
		NSeq_Data_Ptr	= &P3k_NSeq_Data.NSeq_Step[Seq_No][i+1];
		Memory_Mode 	= NSeq_Timing_Ptr->NSeq_Mode;
		Memory_VRange	= re_Range / 2;
		Memory_IRange	= re_Range % 2;

		FPGA_Seq_Ptr = &Prog_Seq_Data.FPGA_Seq_Data[Prog_Seq_Data.Setting_Count++];
		FPGA_Seq_Ptr->SEQ_Mode	= NSeq_Timing_Ptr->NSeq_Mode;
		FPGA_Seq_Ptr->SEQ_Range	= re_Range;
		Response_Setting = get_response(Memory_Mode);

		switch(Memory_Mode) {
		default:
			Debug_printf("PlaceNSeqMemory Error\n");
		case CC_MODE:
			Cal_Gain			= p3k_Cal_data.CC_Data[Memory_IRange].Cal_Value_Gain;
			Cal_Offset			= p3k_Cal_data.CC_Data[Memory_IRange].Cal_Value_Offset;
			LoadON_Value		= NSeq_Data_Ptr->NSeq_Value;
			LoadOFF_Value		= (ptrMODEL_TYPE->CC)[0+(Memory_IRange*10)].Min;
			Memory_SlewRate 	= Data_tmp->CC.STA[Memory_IRange].SLEWRATEUP * SR_StepToCountRatio;
			//Memory_SR_Setting	= Data_tmp->CC.STA[Memory_IRange].SLEWRATEUP_RANGE;
			break;
		case CR_MODE:
			Cal_Gain			= p3k_Cal_data.CR_Data[Memory_IRange].Cal_Value_Gain;
			Cal_Offset			= p3k_Cal_data.CR_Data[Memory_IRange].Cal_Value_Offset;
			LoadON_Value		= NSeq_Data_Ptr->NSeq_Value;
			LoadOFF_Value		= (ptrMODEL_TYPE->CR)[0+(Memory_IRange*10)].Min;
			Memory_SlewRate 	= (Data_tmp->CR.STA[Data_tmp->IRange].SLEWRATEUP * SR_StepToCountRatio)/10;
			//Memory_SR_Setting	= Data_tmp->CR.STA[Data_tmp->IRange].SLEWRATEUP_RANGE;
			break;
		case CV_MODE:
			Cal_Gain			= p3k_Cal_data.CV_Data[Memory_VRange].Cal_Value_Gain;
			Cal_Offset			= p3k_Cal_data.CV_Data[Memory_VRange].Cal_Value_Offset;
			LoadON_Value		= NSeq_Data_Ptr->NSeq_Value;
			LoadOFF_Value		= (ptrMODEL_TYPE->CV)[0+Memory_VRange*3].Max;
			//Memory_SR_Setting	= SlewRate_L_Range;
			if(Memory_VRange)
				Memory_SlewRate = 600;
			else {
				Memory_SlewRate = 6000;
//					Response_Setting |= CV_Response_L;
			}
			break;
		case CP_MODE:
			Cal_Gain			= p3k_Cal_data.CP_Data[Memory_IRange].Cal_Value_Gain;
			Cal_Offset			= p3k_Cal_data.CP_Data[Memory_IRange].Cal_Value_Offset;
			LoadON_Value		= NSeq_Data_Ptr->NSeq_Value;
			LoadOFF_Value		= (ptrMODEL_TYPE->CP)[0+(Memory_IRange*10)].Min;
			Memory_SlewRate 	= CP_SR_CNT;
//				Memory_SR_Setting	= CP_SR_Range;
			break;
		}

		FPGA_Seq_Ptr->CS0_Setting	= I_Circuit_Switch_Control[(Memory_Mode*6) + (Memory_IRange*2) + 0];
		FPGA_Seq_Ptr->CS1_Setting	= I_Circuit_Switch_Control[(Memory_Mode*6) + (Memory_IRange*2) + 1];
		FPGA_Seq_Ptr->SEQ_Time		= NSeq_Data_Ptr->NSeq_Time;

#if Enable_NSEQ_Usec
		Ramp_mS_Time = NSeq_Data_Ptr->NSeq_Time.Hour*60*60*1000 + NSeq_Data_Ptr->NSeq_Time.Minute*60*1000 + NSeq_Data_Ptr->NSeq_Time.Second*1000 + (NSeq_Data_Ptr->NSeq_Time.MilliSecond/20);
#else
		Ramp_mS_Time = NSeq_Data_Ptr->NSeq_Time.Hour*60*60*1000 + NSeq_Data_Ptr->NSeq_Time.Minute*60*1000 + NSeq_Data_Ptr->NSeq_Time.Second*1000 + NSeq_Data_Ptr->NSeq_Time.MilliSecond;
#endif

		/*
		1uS			~ 	60mS		1uS
		60mS		~ 	600mS 		10uS
		600mS		~ 	6S			100uS
		6S			~	1min		1mS
		1min		~ 	100min		100mS
		100min		~ 	1000min		1S
		1000min 		~	10000min	10S
		10000min	~ 	1000H 		1min
		*/
		if(Ramp_mS_Time>10000*60*1000) {	/* 10000 Minute ~ 1000 Hour */
			Memory_Time_Unit = Time_Unit_1min;
			FPGA_Seq_Ptr->Duration_Setting = NSeq_Data_Ptr->NSeq_Time.Hour*60 + NSeq_Data_Ptr->NSeq_Time.Minute;
		} else if(Ramp_mS_Time>1000*60*1000) {	/* 1000 Minute ~ 10000 Minute	*/
			Memory_Time_Unit = Time_Unit_10S;
			FPGA_Seq_Ptr->Duration_Setting = (NSeq_Data_Ptr->NSeq_Time.Hour*60*60 + NSeq_Data_Ptr->NSeq_Time.Minute*60 + NSeq_Data_Ptr->NSeq_Time.Second)/10;
		} else if(Ramp_mS_Time>100*60*1000) {	/* 100 Minute ~1000 Minute	*/
			Memory_Time_Unit = Time_Unit_1S;
			FPGA_Seq_Ptr->Duration_Setting = NSeq_Data_Ptr->NSeq_Time.Hour*60*60 + NSeq_Data_Ptr->NSeq_Time.Minute*60 + NSeq_Data_Ptr->NSeq_Time.Second;
		
#if Enable_NSEQ_Usec
		} else if(Ramp_mS_Time>1*60*1000) { /* 1 Minute ~ 100 Minute	*/
			Memory_Time_Unit = Time_Unit_100mS;
			FPGA_Seq_Ptr->Duration_Setting = (NSeq_Data_Ptr->NSeq_Time.Hour*60*60*1000 + NSeq_Data_Ptr->NSeq_Time.Minute*60*1000 + NSeq_Data_Ptr->NSeq_Time.Second*1000 + NSeq_Data_Ptr->NSeq_Time.MilliSecond/20)/100;
		} else if(Ramp_mS_Time>6000) {	/* 6 Second ~ 1 Minute	*/
			Memory_Time_Unit = Time_Unit_1mS;
			FPGA_Seq_Ptr->Duration_Setting = NSeq_Data_Ptr->NSeq_Time.Minute*60*1000 + NSeq_Data_Ptr->NSeq_Time.Second*1000 + NSeq_Data_Ptr->NSeq_Time.MilliSecond/20;
		} else if(Ramp_mS_Time>600) {	/* 600 ms ~ 6 Second	*/
			Memory_Time_Unit = Time_Unit_100uS;
			FPGA_Seq_Ptr->Duration_Setting = (NSeq_Data_Ptr->NSeq_Time.Second*1000*1000 + NSeq_Data_Ptr->NSeq_Time.MilliSecond*50)/100;
		} else if(Ramp_mS_Time>60) {	/* 60 ms ~ 600 ms	*/
			Memory_Time_Unit = Time_Unit_10uS;
			FPGA_Seq_Ptr->Duration_Setting = (NSeq_Data_Ptr->NSeq_Time.MilliSecond*50)/10;
		} else {						/* 1 us ~ 60 ms */
			Memory_Time_Unit = Time_Unit_1uS;
			FPGA_Seq_Ptr->Duration_Setting = NSeq_Data_Ptr->NSeq_Time.MilliSecond*50;
		}
#else
		} else if(Ramp_mS_Time>1*60*1000) { /* 1 Minute ~ 100 Minute	*/
			Memory_Time_Unit = Time_Unit_100mS;
			FPGA_Seq_Ptr->Duration_Setting = (NSeq_Data_Ptr->NSeq_Time.Hour*60*60*1000 + NSeq_Data_Ptr->NSeq_Time.Minute*60*1000 + NSeq_Data_Ptr->NSeq_Time.Second*1000 + NSeq_Data_Ptr->NSeq_Time.MilliSecond)/100;
		} else if(Ramp_mS_Time>6000) {	/* 6 Second ~ 1 Minute	*/
			Memory_Time_Unit = Time_Unit_1mS;
			FPGA_Seq_Ptr->Duration_Setting = NSeq_Data_Ptr->NSeq_Time.Minute*60*1000 + NSeq_Data_Ptr->NSeq_Time.Second*1000 + NSeq_Data_Ptr->NSeq_Time.MilliSecond;
		} else if(Ramp_mS_Time>600) { /* 600 ms ~ 6 Second	*/
			Memory_Time_Unit = Time_Unit_100uS;
			FPGA_Seq_Ptr->Duration_Setting = (NSeq_Data_Ptr->NSeq_Time.Second*1000*1000 + NSeq_Data_Ptr->NSeq_Time.MilliSecond*1000)/100;
		} else if(Ramp_mS_Time>60) {	/* 60 ms ~ 600 ms	*/
			Memory_Time_Unit = Time_Unit_10uS;
			FPGA_Seq_Ptr->Duration_Setting = (NSeq_Data_Ptr->NSeq_Time.MilliSecond*1000)/10;
		} else {						/* 1 us ~ 60 ms */
			Memory_Time_Unit = Time_Unit_1uS;
			FPGA_Seq_Ptr->Duration_Setting = NSeq_Data_Ptr->NSeq_Time.MilliSecond*1000;
		}
#endif

#if Enable_Func_DisTime
		UWORD N_loop;
		N_loop = P3k_NSeq_Data.NSeq_Seq[Seq_No].NSeq_Loop;
		if(N_loop==0)	total_SEQ_time = 36000001;
		if(total_SEQ_time<36000000){
			total_SEQ_time += (Ramp_mS_Time/1000)*N_loop; //unit: sec
		}		
#endif
		FPGA_Seq_Ptr->Ramp_Delta_VH 	= 0;
		FPGA_Seq_Ptr->Ramp_Delta_VL 	= 0;
		FPGA_Seq_Ptr->Ramp_Delta_T		= 0;

		if(VRange_Low==Memory_VRange)
			FPGA_Seq_Ptr->CS0_Setting |= VM_L_Range;

		if(LOADON_MODE==NSeq_Data_Ptr->Load_Setting)
			FPGA_Seq_Ptr->Level_Step = LoadON_Value;
		else/*LOADOFF_MODE*/
			FPGA_Seq_Ptr->Level_Step = LoadOFF_Value;
		if(FPGA_Seq_Ptr->SEQ_Mode != CV_MODE)
			FPGA_Seq_Ptr->Level_Setting = Step_To_CNT(FPGA_Seq_Ptr->Level_Step ,Cal_Gain,Cal_Offset);
		else
			FPGA_Seq_Ptr->Level_Setting = Step_To_CNT(FPGA_Seq_Ptr->Level_Step ,Cal_Gain,Cal_Offset);
		FPGA_Seq_Ptr->SR_Setting	= Memory_SlewRate;
		FPGA_Seq_Ptr->CS1_Setting  |= Memory_Time_Unit ;
		/* Last Setting*/
		Prog_Seq_Data.FPGA_Seq_Data[1024] = *FPGA_Seq_Ptr;
		if(NSeq_Timing_Ptr->NSeq_Last_Load)
			Prog_Seq_Data.FPGA_Seq_Data[1024].Level_Step = NSeq_Timing_Ptr->NSeq_Last_Level;
		else
			Prog_Seq_Data.FPGA_Seq_Data[1024].Level_Step = LoadOFF_Value;
		Prog_Seq_Data.FPGA_Seq_Data[1024].Level_Setting = Step_To_CNT(Prog_Seq_Data.FPGA_Seq_Data[1024].Level_Step,Cal_Gain,Cal_Offset);
		Prog_Seq_Data.Last_Load_Setting = NSeq_Timing_Ptr->NSeq_Last_Load;
		if((Switch_ON == NSeq_Data_Ptr->Ramp_Setting)&&(Memory_Mode!=P_CV)){
			if((Prog_Seq_Data.Setting_Count == 1)||((Prog_Seq_Data.Setting_Count>1)&&((FPGA_Seq_Ptr->SEQ_Mode!=(FPGA_Seq_Ptr-1)->SEQ_Mode)||(FPGA_Seq_Ptr->SEQ_Range!=(FPGA_Seq_Ptr-1)->SEQ_Range)))) {
				if(CV_MODE==Memory_Mode)
					Pre_Step = ((ptrMODEL_TYPE->CV)[0].Def*1.1);
				else {
					if(Memory_IRange == HIGH_RANGE)
						Pre_Step = Min_Startup_Setting_H;
					else
						Pre_Step = Min_Startup_Setting_L;
				}
			} else
				Pre_Step = (FPGA_Seq_Ptr-1)->Level_Step;

			Goal_Step = FPGA_Seq_Ptr->Level_Step;
			p3k_Ramp_Data = Seq_Ramp_Process(Memory_Mode,Memory_IRange,Memory_VRange,Function_Static,Pre_Step,Goal_Step,NSeq_Data_Ptr->NSeq_Time);
			Memory_Time_Unit	= p3k_Ramp_Data.Delta_TimeBase;
			Memory_SlewRate		= p3k_Ramp_Data.Delta_SR_Set;
			//Memory_SR_Setting	= p3k_Ramp_Data.Delta_SR_Base;
			Response_Setting	= p3k_Ramp_Data.Delta_Response;
			FPGA_Seq_Ptr->Ramp_Delta_VH	= p3k_Ramp_Data.Delta_Value_High;
			FPGA_Seq_Ptr->Ramp_Delta_VL	= p3k_Ramp_Data.Delta_Value_Low;
			FPGA_Seq_Ptr->Ramp_Delta_T	= p3k_Ramp_Data.DeltaTime;
			FPGA_Seq_Ptr->Ramp_Delta_T |= Enable_Ramp;

			FPGA_Seq_Ptr->SR_Setting	= Memory_SlewRate;
			FPGA_Seq_Ptr->CS1_Setting	= I_Circuit_Switch_Control[(Memory_Mode*6) + (Memory_IRange*2) + 1];
			FPGA_Seq_Ptr->CS1_Setting  |= Memory_Time_Unit | Response_Setting;
		}else{
			FPGA_Seq_Ptr->CS1_Setting |= Response_Setting; //Adam_debug
		}
		
		if(Switch_ON==NSeq_Data_Ptr->TrigOut_Setting)
			FPGA_Seq_Ptr->CS1_Setting |= TrigOut_ON;

		if(Switch_ON==NSeq_Data_Ptr->Pause_Setting) {
			FPGA_Seq_Ptr->Duration_Setting =0;
			FPGA_Seq_Ptr->CS1_Setting |= PAUSE_ON;
		}
	}

	if(NSeq_Timing_Ptr->NSeq_Loop!=1) {
		Jump_Setting = Prog_Seq_Data.Jump_Count << 9;
		Prog_Seq_Data.FPGA_Seq_Data[Prog_Seq_Data.Setting_Count-1].CS1_Setting |= Jump_ON | Jump_Setting;

		Pre_Step = FPGA_Seq_Ptr->Level_Step;
		Goal_Step= Prog_Seq_Data.FPGA_Seq_Data[Prog_Seq_Data.P3k_FPGA_Jump_Data[Prog_Seq_Data.Jump_Count].Jump_Address].Level_Step;
		p3k_Ramp_Data = Seq_Ramp_Process(Memory_Mode,Memory_IRange,Memory_VRange,Function_Static,Pre_Step,Goal_Step,P3k_NSeq_Data.NSeq_Step[Seq_No][1].NSeq_Time);
		Prog_Seq_Data.P3k_FPGA_Jump_Data[Prog_Seq_Data.Jump_Count].Ramp_Delta_VH	= p3k_Ramp_Data.Delta_Value_High;
		Prog_Seq_Data.P3k_FPGA_Jump_Data[Prog_Seq_Data.Jump_Count].Ramp_Delta_VL	= p3k_Ramp_Data.Delta_Value_Low;
		Prog_Seq_Data.P3k_FPGA_Jump_Data[Prog_Seq_Data.Jump_Count].Ramp_SlewRate	= p3k_Ramp_Data.Delta_SR_Set;
		Memory_Time_Unit	= p3k_Ramp_Data.Delta_TimeBase;
		//Memory_SR_Setting	= p3k_Ramp_Data.Delta_SR_Base;
		Response_Setting	= p3k_Ramp_Data.Delta_Response;
		//Prog_Seq_Data.P3k_FPGA_Jump_Data[Prog_Seq_Data.Jump_Count].Ramp_CS1 = I_Circuit_Switch_Control[(Memory_Mode*6) + (Memory_IRange*2) + 1];
		Prog_Seq_Data.P3k_FPGA_Jump_Data[Prog_Seq_Data.Jump_Count].Ramp_CS1 = Response_Setting;
		Prog_Seq_Data.Jump_Count++;
	}
}

void PlaceProgMemory(UWORD Input_MODE,UBYTE Memory_No,UWORD Run_Time) {
	/*Input_MODE = 0, Short 	*/
	/*Input_MODE = 1, LOAD ON	*/
	/*Input_MODE = 2, LOAD OFF	*/
	double Cal_Gain,Cal_Offset;
	UBYTE Memory_VRange;
	UWORD LoadON_Value   ,LoadOFF_Value   ,Short_Value;
	UWORD LoadON_SlewRate,LoadOFF_SlewRate,Short_SlewRate;
	UWORD LoadON_SR_Range,LoadOFF_SR_Range,Short_SR_Range;
	UWORD Response_Setting;
	P3k_Memory_Str	 *Memory_Ptr;
	P3k_FPGA_Seq_Str *FPGA_Seq_Ptr;

	FPGA_Seq_Ptr = &Prog_Seq_Data.FPGA_Seq_Data[Prog_Seq_Data.Setting_Count++];
	Memory_Ptr	 = &P3k_Chan_Data.M_DATA[Memory_No];

	if(Memory_Ptr->STATUS&0x40)
		Memory_VRange = VRange_High;
	else
		Memory_VRange = VRange_Low;

	FPGA_Seq_Ptr->SEQ_Mode	= Memory_Ptr->MODE;
	FPGA_Seq_Ptr->SEQ_Range	= Memory_Ptr->IRange + Memory_VRange*2;

	Response_Setting = Memory_Ptr->RESPONSE_VALUE; //get_response(Memory_Ptr->MODE);
	Short_SR_Range = 1; //Adam_debug
	switch(Memory_Ptr->MODE) {
	default:/*CC_MODE:*/
		Debug_printf("PlaceProgMemory Error\n");
	case CC_MODE:
		Cal_Gain		= p3k_Cal_data.CC_Data[Memory_Ptr->IRange].Cal_Value_Gain;
		Cal_Offset		= p3k_Cal_data.CC_Data[Memory_Ptr->IRange].Cal_Value_Offset;
		LoadON_Value	= Memory_Ptr->VALUE1;
		LoadON_SlewRate	= Memory_Ptr->SLEWRATEUP * SR_StepToCountRatio;
		LoadON_SR_Range	= Memory_Ptr->SLEWRATEUP_RANGE;

		LoadOFF_Value	= (ptrMODEL_TYPE->CC)[0+(Memory_Ptr->IRange*10)].Min;
		LoadOFF_SlewRate= Memory_Ptr->SLEWRATEUP * SR_StepToCountRatio;
		LoadOFF_SR_Range= Memory_Ptr->SLEWRATEUP_RANGE;

		Short_Value		= (ptrMODEL_TYPE->CC)[0+(Memory_Ptr->IRange*10)].Max;
		Short_SlewRate	= (ptrMODEL_TYPE->CC)[2+(Memory_Ptr->IRange*10)].Max * SR_StepToCountRatio;
		break;
	case CR_MODE:
		Cal_Gain		= p3k_Cal_data.CR_Data[Memory_Ptr->IRange].Cal_Value_Gain;
		Cal_Offset		= p3k_Cal_data.CR_Data[Memory_Ptr->IRange].Cal_Value_Offset;
		LoadON_Value	= Memory_Ptr->VALUE1;
		LoadON_SlewRate	= (Memory_Ptr->SLEWRATEUP * SR_StepToCountRatio)/10;
		LoadON_SR_Range	= Memory_Ptr->SLEWRATEUP_RANGE;

		LoadOFF_Value	= (ptrMODEL_TYPE->CR)[0+(Memory_Ptr->IRange*10)].Min;
		LoadOFF_SlewRate= (Memory_Ptr->SLEWRATEUP * SR_StepToCountRatio)/10;
		LoadOFF_SR_Range= Memory_Ptr->SLEWRATEUP_RANGE;

		Short_Value		= (ptrMODEL_TYPE->CR)[0+(Memory_Ptr->IRange*10)].Max;
		Short_SlewRate	= ((ptrMODEL_TYPE->CR)[2+(Memory_Ptr->IRange*10)].Max * SR_StepToCountRatio)/10;
		break;
	case CV_MODE:
		Cal_Gain		= p3k_Cal_data.CV_Data[Memory_VRange].Cal_Value_Gain;
		Cal_Offset		= p3k_Cal_data.CV_Data[Memory_VRange].Cal_Value_Offset;

		LoadON_Value	= Memory_Ptr->VALUE1;
		LoadOFF_Value	= (ptrMODEL_TYPE->CV)[0+Memory_VRange*3].Max;
		Short_Value		= (ptrMODEL_TYPE->CV)[0+Memory_VRange*3].Min;

		if(Memory_VRange)
			LoadON_SlewRate = LoadOFF_SlewRate =  600; //Adam_debug
		else {
			LoadON_SlewRate = LoadOFF_SlewRate =  6000; //Adam_debug
		}
		break;
	case CP_MODE:
		Cal_Gain		= p3k_Cal_data.CP_Data[Memory_Ptr->IRange].Cal_Value_Gain;
		Cal_Offset		= p3k_Cal_data.CP_Data[Memory_Ptr->IRange].Cal_Value_Offset;
		LoadON_Value	= Memory_Ptr->VALUE1;

		LoadOFF_Value	= (ptrMODEL_TYPE->CP)[0+(Memory_Ptr->IRange*10)].Min;

		Short_Value		= (ptrMODEL_TYPE->CP)[0+(Memory_Ptr->IRange*10)].Max;
		LoadON_SlewRate	= LoadOFF_SlewRate = Short_SlewRate	= CP_SR_CNT;
		break;
	}
	FPGA_Seq_Ptr->CS0_Setting 		= I_Circuit_Switch_Control[(Memory_Ptr->MODE*6) + (Memory_Ptr->IRange*2) + 0];
	FPGA_Seq_Ptr->CS1_Setting 		= I_Circuit_Switch_Control[(Memory_Ptr->MODE*6) + (Memory_Ptr->IRange*2) + 1];
	FPGA_Seq_Ptr->Duration_Setting	= Run_Time*100; /*Time Resolution = 100mS*/
	FPGA_Seq_Ptr->Ramp_Delta_VH		= 0;
	FPGA_Seq_Ptr->Ramp_Delta_VL		= 0;
	FPGA_Seq_Ptr->Ramp_Delta_T		= 0;

	if(VRange_Low==Memory_VRange)
		FPGA_Seq_Ptr->CS0_Setting |= VM_L_Range;

	if(SHORT_MODE==Input_MODE) {
		FPGA_Seq_Ptr->Level_Step	= Short_Value;
		FPGA_Seq_Ptr->Level_Setting = Step_To_CNT(Short_Value,Cal_Gain,Cal_Offset);
		FPGA_Seq_Ptr->SR_Setting	= Short_SlewRate;
		FPGA_Seq_Ptr->CS1_Setting  |= Short_SR_Range | Time_Unit_1mS ;
	} else if(LOADON_MODE==Input_MODE) {
		FPGA_Seq_Ptr->Level_Step	= LoadON_Value;
		FPGA_Seq_Ptr->Level_Setting = Step_To_CNT(LoadON_Value,Cal_Gain,Cal_Offset);
		FPGA_Seq_Ptr->SR_Setting	= LoadON_SlewRate;
		FPGA_Seq_Ptr->CS1_Setting  |= LoadON_SR_Range | Time_Unit_1mS ;
	} else { /*LOADOFF_MODE*/
		FPGA_Seq_Ptr->Level_Step	= LoadOFF_Value;
		FPGA_Seq_Ptr->Level_Setting = Step_To_CNT(LoadOFF_Value,Cal_Gain,Cal_Offset);
		FPGA_Seq_Ptr->SR_Setting	= LoadOFF_SlewRate;
		FPGA_Seq_Ptr->CS1_Setting  |= LoadOFF_SR_Range | Time_Unit_1mS ;
		/* Last Setting*/
		Prog_Seq_Data.FPGA_Seq_Data[1024] = *FPGA_Seq_Ptr;
		Prog_Seq_Data.Last_Load_Setting = Switch_OFF;
	}
}

void PlaceNSeqStep(void) {
	UBYTE Goal_Mode,Goal_IRange,Goal_VRange;
	UBYTE Pre_Mode,Pre_IRange,Pre_VRange;
	UWORD Goal_Step,Pre_Step;
	UWORD i;  //ADAM 0911
	p3k_Ramp_Str p3k_Ramp_Data;
	UWORD Prog_No_Temp = 99;

	P3k_FPGA_Seq_Str *FPGA_Seq_Ptr;

	Prog_Seq_Data.Setting_Count	= 0;
	Prog_Seq_Data.Jump_Count	= 1;

	for(i=0 ; i<Prog_Seq_Data.Total_Count ; i++) {
		if(Prog_Seq_Data.D_Loop_Count==i) {
			Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Jump_Address	= Prog_Seq_Data.Setting_Count;
			Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Jump_Number	= 0;
		}

		if(Prog_No_Temp!=Prog_Seq_Data.Prog_Disp_Data[i].Prog_No) {
			Prog_No_Temp = Prog_Seq_Data.Prog_Disp_Data[i].Prog_No;
			PlaceNSeqMemory(Prog_No_Temp);
		}

		if(P3k_NSeq_Data.NSeq_Seq[Prog_No_Temp].NSeq_Loop==1)
			Prog_Seq_Data.Prog_Disp_Data[i].Loop_Address = 0;
		else
			Prog_Seq_Data.Prog_Disp_Data[i].Loop_Address = Prog_Seq_Data.Jump_Count - 1;
	}

	if( (Prog_Seq_Data.D_Loop_Count!=2000)&&(Prog_Seq_Data.Setting_Count)) {
		FPGA_Seq_Ptr = &Prog_Seq_Data.FPGA_Seq_Data[Prog_Seq_Data.Setting_Count];
		*FPGA_Seq_Ptr = *(FPGA_Seq_Ptr-1);
		FPGA_Seq_Ptr->CS1_Setting |= Jump_ON;
		FPGA_Seq_Ptr->CS1_Setting &= 0xE1FF;		/*Use Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Jump_Address and Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Jump_Number*/
		FPGA_Seq_Ptr->CS1_Setting &= ~TrigOut_ON;
		FPGA_Seq_Ptr->CS1_Setting &= ~PAUSE_ON;
		FPGA_Seq_Ptr->CS1_Setting &= 0x3FFF;		/*Time_Unit_1uS*/
		FPGA_Seq_Ptr->Duration_Setting = 0;

		FPGA_Seq_Ptr = &Prog_Seq_Data.FPGA_Seq_Data[Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Jump_Address];

		Goal_Mode 	= FPGA_Seq_Ptr->SEQ_Mode;
		Goal_VRange	= FPGA_Seq_Ptr->SEQ_Range/2;
		Goal_IRange	= FPGA_Seq_Ptr->SEQ_Range%2;
		Goal_Step	= FPGA_Seq_Ptr->Level_Step;

		FPGA_Seq_Ptr = &Prog_Seq_Data.FPGA_Seq_Data[Prog_Seq_Data.Setting_Count-1];

		Pre_Mode	= FPGA_Seq_Ptr->SEQ_Mode;
		Pre_VRange	= FPGA_Seq_Ptr->SEQ_Range/2;
		Pre_IRange	= FPGA_Seq_Ptr->SEQ_Range%2;
		Pre_Step	= FPGA_Seq_Ptr->Level_Step;

		if( (Pre_Mode!=Goal_Mode)||(Pre_VRange!=Goal_VRange)||(Pre_IRange!=Goal_IRange) ) {
			if(CV_MODE==Pre_Mode)
				Pre_Step = ((ptrMODEL_TYPE->CV)[0].Def*1.1);
			else {
				if(Pre_IRange == HIGH_RANGE)
					Pre_Step = Min_Startup_Setting_H;
				else
					Pre_Step = Min_Startup_Setting_L;
			}
		}

		p3k_Ramp_Data = Seq_Ramp_Process(Goal_Mode,Goal_IRange,Goal_VRange,Function_Static,Pre_Step,Goal_Step,FPGA_Seq_Ptr->SEQ_Time);

		Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Ramp_Delta_VH	= p3k_Ramp_Data.Delta_Value_High;
		Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Ramp_Delta_VL	= p3k_Ramp_Data.Delta_Value_Low;
		Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Ramp_SlewRate	= p3k_Ramp_Data.Delta_SR_Set;
		//Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Ramp_CS1		= I_Circuit_Switch_Control[(Goal_Mode*6) + (Goal_IRange*2) + 1];
		Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Ramp_CS1		=  p3k_Ramp_Data.Delta_Response;
		Prog_Seq_Data.Setting_Count++;
		Prog_Seq_Data.Prog_Disp_Data[Prog_Seq_Data.Total_Count] = Prog_Seq_Data.Prog_Disp_Data[Prog_Seq_Data.Total_Count-1];
		Prog_Seq_Data.Total_Count++;
	} else {
		if(P3k_Chan_Data.CONF.Ext_Setting.MultilPara)
			Prog_Seq_Data.FPGA_Seq_Data[1024].CS1_Setting |=  TrigOut_ON;
	}
	WriteSEQDataToFPGA();
}

void PlaceProgStep(void) {
	UBYTE Prog_Setting,Step_Setting;
	UWORD i;
	P3k_Timing_Str		*Timing_Ptr;
	P3k_Prog_Disp_Str	*Prog_Disp_Ptr;
	UWORD Time_Setting,Memory_Setting;
	Prog_Seq_Data.Setting_Count = 0;

	for(i=0 ; i<Prog_Seq_Data.Total_Count ; i++) {
		Prog_Disp_Ptr	= &Prog_Seq_Data.Prog_Disp_Data[i];
		Prog_Setting	= Prog_Disp_Ptr->Prog_No;
		Step_Setting	= Prog_Disp_Ptr->Step_No;
		Timing_Ptr		= &p3k_Chan_PROG.Timing_Data[Prog_Setting];
		Memory_Setting	= Timing_Ptr->MEMORY[Step_Setting];

		if( Prog_Seq_Data.D_Loop_Count==i ) {
			Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Jump_Address	= Prog_Seq_Data.Setting_Count;
			Prog_Seq_Data.P3k_FPGA_Jump_Data[0].Jump_Number	= 0;
		}
		/* Short Time */
		Time_Setting = Timing_Ptr->SHORTTIME[Step_Setting];
		PlaceProgMemory(SHORT_MODE,Memory_Setting,Time_Setting);

		/* ON Time */
		Time_Setting = Timing_Ptr->ONTIME[Step_Setting] - Timing_Ptr->SHORTTIME[Step_Setting];
		PlaceProgMemory(LOADON_MODE,Memory_Setting,Time_Setting);

		/* OFF Time */
		Time_Setting = Timing_Ptr->OFFTIME[Step_Setting];
		PlaceProgMemory(LOADOFF_MODE,Memory_Setting,Time_Setting);

		if( (Manual_MODE==Timing_Ptr->RUNMODE[Step_Setting])&&(Prog_Seq_Data.Setting_Count) ) {
			if(Timing_Ptr->OFFTIME[Step_Setting])
				Prog_Seq_Data.FPGA_Seq_Data[Prog_Seq_Data.Setting_Count-1].CS1_Setting |= PAUSE_ON;
			else if(Timing_Ptr->ONTIME[Step_Setting])
				Prog_Seq_Data.FPGA_Seq_Data[Prog_Seq_Data.Setting_Count-2].CS1_Setting |= PAUSE_ON;
			else
				Prog_Seq_Data.FPGA_Seq_Data[Prog_Seq_Data.Setting_Count-3].CS1_Setting |= PAUSE_ON;
		}
	}

	if( (Prog_Seq_Data.D_Loop_Count!=2000)&&(Prog_Seq_Data.Setting_Count) )
		Prog_Seq_Data.FPGA_Seq_Data[Prog_Seq_Data.Setting_Count-1].CS1_Setting |= Jump_ON;
	WriteSEQDataToFPGA();
}

void clear_struct_data (unsigned char *pta, int size ) {
	while(size>0) {
		*pta++ = 0;
		size --;
	}
}

void PlaceNSeqChain(void) {
	UBYTE Seq_Array[10];	/* 0:OFF ,S01~S10 */
	UBYTE Loop_Item;
	UBYTE End_Item;
	UBYTE i;
	UWORD j;
	UBYTE Chain_Seq_No;

	P3k_Prog_Disp_Str	*Prog_Disp_Ptr;

	for(i=0 ; i<10 ; i++)
		Seq_Array[i] = 0;		/* Initialize Data	*/

	Loop_Item	= 0;
	End_Item	= 0;

	clear_struct_data((unsigned char *)&Prog_Seq_Data, sizeof(Prog_Seq_Data));

	Chain_Seq_No = P3k_NSeq_Data.NSeq_Start + 1;

	for(i=0 ; i<=10 ; i++) {
		if(Chain_Seq_No) {
			for(j=0 ; j<i ; j++) {
				if(Chain_Seq_No==Seq_Array[j]) {
					Loop_Item	= j+1;	/* Loop Seq No */
					End_Item	= i;	/* End Seq No */
					break;
				}
			}

			if(End_Item)
				break;

			Seq_Array[i] = Chain_Seq_No;
			Chain_Seq_No = P3k_NSeq_Data.NSeq_Seq[Chain_Seq_No-1].NSeq_Chain;
		} else {
			Loop_Item	= 0;			/* No Loop */
			End_Item	= i;			/* End Seq No */
			break;
		}
	}
#if Enable_Func_DisTime
	if(Loop_Item){
		total_SEQ_time = 36000001;
	}else{
		total_SEQ_time = 0;
	}
#endif

	Prog_Disp_Ptr	= &Prog_Seq_Data.Prog_Disp_Data[0];
	Prog_Seq_Data.Total_Count	= 0;
	Prog_Seq_Data.D_Loop_Count	= 2000;

	for(i=0 ; i<End_Item ; i++) {
		if(P3k_NSeq_Data.NSeq_Seq[Seq_Array[i]-1].NSeq_Max_Step) {
			for(j=0 ; j<P3k_NSeq_Data.NSeq_Seq[Seq_Array[i]-1].NSeq_Max_Step ; j++) {
				if( (Loop_Item==(i+1))&&(2000==Prog_Seq_Data.D_Loop_Count) )
					Prog_Seq_Data.D_Loop_Count = Prog_Seq_Data.Total_Count;

				Prog_Disp_Ptr->Prog_No = Seq_Array[i]-1;
				Prog_Disp_Ptr->Step_No = j;
				Prog_Disp_Ptr++;
				Prog_Seq_Data.Total_Count++;
			}
		} else {
			Seq_Array[i] = 0;
			if(Loop_Item==(i+1))
				Loop_Item++;
		}
	}
	PlaceNSeqStep();
}

void PlaceProgChain(void) {
	UBYTE Prog_Array[16];	/*	0:OFF ,P01~P16 */
	UBYTE Loop_Item;
	UBYTE End_Item;
	UBYTE i,j;
	UBYTE Chain_Prog_No,Step_Number;
	P3k_Timing_Str		*Timing_Ptr;
	P3k_Prog_Disp_Str	*Prog_Disp_Ptr;

	for(i=0 ; i<16 ; i++)
		Prog_Array[i] = 0;		/* Initialize Data	*/
	Loop_Item	= 0;
	End_Item	= 0;

	Chain_Prog_No = p3k_Chan_PROG.Chain_Start_Prog + 1;
	for(i=0 ; i<16 ; i++) {
		if(Chain_Prog_No) {
			for(j=0 ; j<i ; j++) {
				if(Chain_Prog_No==Prog_Array[j]) {
					Loop_Item	= j+1;	/*Loop Prog No*/
					End_Item	= i;	/*End Prog No*/
					break;
				}
			}

			if(End_Item)
				break;

			Prog_Array[i] = Chain_Prog_No;
			Chain_Prog_No = p3k_Chan_PROG.PROGSEQ[Chain_Prog_No-1];
		} else {
			Loop_Item	= 0;		/*No Loop*/
			End_Item	= i;		/*End Prog No*/
			break;
		}
	}

	Prog_Disp_Ptr = &Prog_Seq_Data.Prog_Disp_Data[0];
	Prog_Seq_Data.Total_Count	= 0;
	Prog_Seq_Data.D_Loop_Count	= 2000;

	for(i=0 ; i<End_Item ; i++) {
		Timing_Ptr	= &p3k_Chan_PROG.Timing_Data[Prog_Array[i]-1];
		Step_Number = 0;

		for(j=0 ; j<16 ; j++) {
			if(Timing_Ptr->RUNMODE[j]!=Skip_MODE) {
				if( (Loop_Item==(i+1))&&(2000==Prog_Seq_Data.D_Loop_Count) )
					Prog_Seq_Data.D_Loop_Count = Prog_Seq_Data.Total_Count;

				Prog_Disp_Ptr->Prog_No				= Prog_Array[i]-1;
				Prog_Disp_Ptr->Step_No				= j;
				Prog_Disp_Ptr->Mem_NO				= Timing_Ptr->MEMORY[j];
				Prog_Disp_Ptr->SPEC_Result			= 0;
				Prog_Disp_Ptr->SPEC_Result_Backup 	= 0;
				Prog_Disp_Ptr->PFTIME				= Timing_Ptr->PFTIME[j];
				Prog_Disp_Ptr++;
				Prog_Seq_Data.Total_Count++;
				Step_Number++;
			}
		}
		if(0==Step_Number) {
			Prog_Array[i] = 0;
			if(Loop_Item==(i+1))
				Loop_Item++;
		}
	}
	PlaceProgStep();
}

