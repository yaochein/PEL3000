
/*********************************************************************
Include Files
*********************************************************************/
#include <includes.h>
//#include "fs_api.h"
#include "head.h"
#include "menu_msg.h"
#include "menu_pro.h"
#include "../bmp/bmp.h"
#include "keydef.h"
#include "math.h"
#include "../FPGA/SendTXSub.h"
#include "fm.h"
#include "../fs240/fs/device/usb/usb.h"

#include "../../Drivers/Drive_Data_Flash.h"

/*********************************************************************
Ext Variables
*********************************************************************/
extern p3k_send_tx_list TX_LIST;
char Stop_Next_Proc=0;
extern GELMASTER *gel;
extern char USB_Status;
extern char USB_Status_Display;
extern UWORD Monitor_ExtV_H;
extern UWORD Monitor_ExtV_L;
extern UWORD Monitor_ExtR_H;
extern UWORD Monitor_ExtR_L;

/*********************************************************************
Ext Function
*********************************************************************/
extern void ClrDispCnt(char mode, char ct, char sec, char ssc, char bct, char scl);
extern void SetRTC(UWORD);
extern void rtc_get (struct tm  *tmp);
extern void BackupRunProg(void);
extern void TIMER1_DGIO(INT16U Delay_100ms);
extern void TIMER1_Pulse(void);
extern int FMrename(void);
extern void GNGStep2Pcet(char no);
extern void RestoreRealChan(void);
extern void ProgramAllUserProgram512(long,unsigned char*,long);
extern void CountinueArrayRead512(long total_addr, unsigned char *ptr, long size);
extern void EDGIO_Control( char mode, char onoff);
extern void LoadDefaultProc(char mode);
extern void Load_Default_Interface(char mode);
extern void Control_LCDBRCon(void);
extern void ShowMessage(char* STR);
extern void Menu_Message_Pro(char Mode,char *Message);
extern void Menu_Message(char *Message,int x,int y);
extern void sport0Write(unsigned long data);
extern void Show_IRange_Window(void);
extern void Show_Calibration_Error_Window(void);
extern void Show_XYZ_Window(void);
extern void SaveCalData_DataFlash(void);
extern void PEL3000_LED_Control( char mode, char onoff);
extern void FPGA_Init(void);
extern void Update_Panel(void);
extern void Init_DMA_Sport0(void);
extern void Enable_Continuous_DMA_Sport0(UBYTE WaveNumber);
extern void Disable_Continuous_DMA_Sport0(void);
extern void ShowCalMessage(void);
extern void Debug_printf(char *Message);
extern void BackupSetupData(void);
extern void BackupNSeq(void);
extern void BackupFSeq(void);
extern void BackupUserDefaultData(char mode);
extern void BackupStatus(void);
extern void SaveProgDataToFile(void);
extern void SaveSetupDataToFile(void);
extern void SavePresetDataToFile(void);
extern void SaveNSeqDataToFile(void);
extern void SaveFSeqDataToFile(void);
extern UWORD get_response(UBYTE Run_Mode);
extern void RecoverCalData_DataFlash(char check_done);
extern void BackupOCP(void);
#if Enable_OPP_function
extern void BackupOPP(void);
#endif

#if Enable_fseq_deletAll
extern void Del_FSeq_All(void);
#endif
void Auto_Load_Off(void);
void Auto_Load_On(void);
#if Enable_LED_function
extern void BackupLED(void);
extern Prot_Setting_Process(void);
extern find_curve_led_paramter(UWORD data);

#endif
extern GetChanData(BYTE cnt, BYTE cnt1); 
extern UWORD Step_To_CNT(UWORD Input_Step,double Input_Gain,double Input_Offset);
/* SPORT0 DMA transmit buffer */
extern volatile int iTxBuffer1[18][4096];
/* SPORT0 DMA receive buffer */
extern volatile int iRxBuffer1[4096];
/*********************************************************************
Function
*********************************************************************/
char  FMpredir[maxdirlen];

extern FMfilestru FMfile;
extern char FMnowPath[maxdirlen];
extern struct tm CurrentTime;
extern char mybuffer[150];
/* 文件指針調整模式 */
#define SEEK_SET    0               // 從文件開始處移動文件指針
#define SEEK_CUR    1               // 從文件當前位置移動文件指針
#define SEEK_END    2               // 從文件尾移動文件指針

/*Recall Default flag define for Default_info.*/
#define Def_Factory_CONFIRM			0x0001  /*Recall Factory Confirm*/
#define Def_Save_CONFIRM			0x0002  /*Save User's Default*/
#define Def_Recall_CONFIRM			0x0004  /*Recall User's Default*/

extern void Read_USB_Info(void);
extern void APP_Create_Option_LIC(void);

BYTE Normal_Mode(BYTE chnum,BYTE x)
{
	char status,status1,i;
	p3k_send_tx_list tx_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UBYTE load_onoff_status;

	load_onoff_status = UTILITY.LOAD_CTL;
	Auto_Load_Off();
#if Enable_AutoLoad
	if((UTILITY.AutoLoadOffMode==0)&&(load_onoff_status)) {
		PEL3000_LED_Control( LED_LOAD, 1 );
	}
#endif

	Magnification_Cnt = 0;

	status = Data_tmp->CURRMODE;
	status++;

	if(status>3)
		status =P_CC;

	Disp_tmp->CURRMODE = status;

	if(CC_MODE==status)
		M_num = P_CC;
	else if(CR_MODE==status) {
		M_num = P_CR;
		status1 = Data_tmp->IRange;
		if(status1==Disp_tmp->VRange) {
			Disp_tmp->VRange = (0 == status1) ? 1 : 0;
			Data_tmp->VRange = Disp_tmp->VRange ;
			MenuRedrawFlag |= MENU3_CHANGE;
			tx_data.ADDRH = 0x02;
			tx_data.ADDRL = 0x01;
			SendTXData(&tx_data);
			tx_data.ADDRL = 0x00;
			SendTXData(&tx_data);
		}
	} else if(CV_MODE==status)
		M_num = P_CV;
	else
		M_num = P_CP;

	MenuRedrawFlag|=MENU_CHANGE;
	Data_tmp->CURRMODE = status;			// If Help Function not Enable
	ClrDispCnt(0x01,0x00,0x02,0x00,0x00,0x00);

	if(Disp_tmp->CONF.CH_Control) {
		if(Disp_tmp->CURRMODE==P_CC) {
			DispMode = DispMode_SELECT_CH;
			if(Disp_tmp->CC.STADYNA)
				Disp_tmp->CC.STADYNA =Data_tmp->CC.STADYNA = 0;
		}
		if(Disp_tmp->CURRMODE==P_CV)
			DispCT=2;
	}

	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= CHAN_STATUS;

	if(Disp_tmp->CURRMODE!=P_CV)
		ChanRedrawFlag |= BG_CLEAR;

	tx_data.ADDRH = Machine_Command;
	tx_data.ADDRL = Machine_modeHandle;
	SendTXData(&tx_data);
	tx_data.ADDRH = Machine_Command;
	tx_data.ADDRL = Machine_Von_Delay;
	SendTXData(&tx_data);
#if Enable_AutoLoad
	if((UTILITY.AutoLoadOffMode==0)&&(load_onoff_status)) {
		OSTimeDly(5);
		Auto_Load_On();
	}
#endif
	return (0);
}

BYTE Normal_IRange(BYTE chnum,BYTE x)
{
	p3k_send_tx_list tx_data;
	char status;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UBYTE load_onoff_status;
	load_onoff_status = UTILITY.LOAD_CTL;
	/* Must set to load off */
	if(0==Float_Window_Count) {
		Show_IRange_Window();
		return 0;
	}
	Auto_Load_Off();
#if Enable_AutoLoad
	if((UTILITY.AutoLoadOffRange==0)&&(load_onoff_status)) {
		PEL3000_LED_Control( LED_LOAD, 1 );
	}
#endif
	Magnification_Cnt = 0;
	if(CC_MODE==Data_tmp->CURRMODE)
		tx_data.ADDRH = 0x01;
	else if(CR_MODE==Data_tmp->CURRMODE)
		tx_data.ADDRH = 0x02;
	else if(CV_MODE==Data_tmp->CURRMODE)
		tx_data.ADDRH = 0x03;
	else
		tx_data.ADDRH = 0x04;
	status = Data_tmp->IRange;
	status--;

	if(status<LOW_RANGE)		status=HIGH_RANGE;

	Disp_tmp->IRange = Data_tmp->IRange = status;

	Show_IRange_Window();
	if(CR_MODE==Data_tmp->CURRMODE) {
		Disp_tmp->VRange = (0 == status) ? 1 : 0;
		Data_tmp->VRange = Disp_tmp->VRange ;
		MenuRedrawFlag |= MENU3_CHANGE;
	}
	DispMode=DispMode_BROWSE_ITEMS;				/* Return to Brower Mode */

	if((Disp_tmp->CONF.CH_Control)&&(Disp_tmp->CURRMODE==P_CC))
		DispMode = DispMode_SELECT_CH;

	ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
	MenuRedrawFlag |= MENU2_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;// + BG_CLEAR;
	ChanRedrawFlag |= CHAN_STATUS;

	if((Disp_tmp->CONF.CH_Control)&&(M_num==P_CC))
		DataRedrawFlag |= BG_CLEAR_FLAG;

	tx_data.ADDRL = 0x01;
	SendTXData(&tx_data);

	tx_data.ADDRL = 0x00;
	SendTXData(&tx_data);

	tx_data.ADDRH = Para_Ext_Command;
	tx_data.ADDRL = Para_Ext_Setting;
	SendTXData(&tx_data);

	/* Set Front and Rear IMON */
	tx_data.ADDRH = Machine_Command;
	tx_data.ADDRL = Machine_Setting_IMON;
	SendTXData(&tx_data);
	Prot_Setting_Process();
#if Enable_AutoLoad
	if((UTILITY.AutoLoadOffRange==0)&&(load_onoff_status)) {
		OSTimeDly(1);
		Auto_Load_On();
	}
#endif
	return (0);
}

BYTE Normal_VRange(BYTE chnum,BYTE x)
{
	char status;

	p3k_send_tx_list tx_data;

	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UBYTE load_onoff_status;

	if(CR_MODE==Data_tmp->CURRMODE)return 0;

	load_onoff_status = UTILITY.LOAD_CTL;

	Auto_Load_Off();
#if Enable_AutoLoad
	if((UTILITY.AutoLoadOffRange==0)&&(load_onoff_status)) {
		PEL3000_LED_Control( LED_LOAD, 1 );
	}
#endif
	Magnification_Cnt = 0;

	if(CC_MODE==Data_tmp->CURRMODE)
		tx_data.ADDRH = 0x01;
	else if(CR_MODE==Data_tmp->CURRMODE)
		tx_data.ADDRH = 0x02;
	else if(CV_MODE==Data_tmp->CURRMODE)
		tx_data.ADDRH = 0x03;
	else
		tx_data.ADDRH = 0x04;

	status = Data_tmp->VRange;
	status++;
	status&=0x01;
	Disp_tmp->VRange = Data_tmp->VRange = status;

	DispMode=DispMode_BROWSE_ITEMS; 			/* Return to Brower Mode */

	if((Disp_tmp->CONF.CH_Control)&&(CC_MODE==Disp_tmp->CURRMODE))
		DispMode = DispMode_SELECT_CH;

	ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
	MenuRedrawFlag |= MENU3_CHANGE;
	DataRedrawFlag |= PARA_CHANGE+BG_CLEAR;
	ChanRedrawFlag |= CHAN_STATUS;

	if((Disp_tmp->CONF.CH_Control)&&(M_num==P_CC))
		DataRedrawFlag |= BG_CLEAR_FLAG;

	tx_data.ADDRL = 0x01;
	SendTXData(&tx_data);

	tx_data.ADDRL = 0x00;
	SendTXData(&tx_data);
#if Enable_AutoLoad
	if((UTILITY.AutoLoadOffRange==0)&&(load_onoff_status)) {
		OSTimeDly(5);
		Auto_Load_On();
	}
#endif
	return (0);
}

BYTE Normal_Type(BYTE chnum,BYTE x)
{
	char status;

	p3k_send_tx_list tx_data;

	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	Magnification_Cnt = 0;

	switch(Data_tmp->CURRMODE) {
	case CC_MODE:
		if(Data_tmp->CONF.Ext_Setting.Control)
			return (0);
		status = Data_tmp->CC.STADYNA;
		status++;
		status&=0x01;
		Disp_tmp->CC.STADYNA = Data_tmp->CC.STADYNA = status;
		tx_data.ADDRH = 0x01;
		break;
	case CR_MODE:
		if(Data_tmp->CONF.Ext_Setting.Control)
			return (0);
		status = Data_tmp->CR.STADYNA;
		status++;
		status&=0x01;
		Disp_tmp->CR.STADYNA = Data_tmp->CR.STADYNA = status;
		tx_data.ADDRH = 0x02;
		break;
	case CV_MODE:
		status = Data_tmp->CV.RESPONSE;
		status++;
		//status&=0x01;
		if(status> CVCP_ResponseFast)status = CVCP_ResponseSlow;
		Disp_tmp->CV.RESPONSE = Data_tmp->CV.RESPONSE = status;
		tx_data.ADDRH = 0x03;
		break;
	case CP_MODE:
		if(Data_tmp->CONF.Ext_Setting.Control)
			return (0);
		status = Data_tmp->CP.RESPONSE;;
		status++;
		if(status> CVCP_ResponseFast)status = CVCP_ResponseSlow;
		Disp_tmp->CR.RESPONSE = Data_tmp->CP.RESPONSE = status;
		tx_data.ADDRH = 0x04;
		break;
	default:
		break;
	}

	ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
	MenuRedrawFlag |=MENU4_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= CHAN_STATUS;

	tx_data.ADDRL = 0x01;
	SendTXData(&tx_data);

	tx_data.ADDRL = 0x00;
	SendTXData(&tx_data);
	return (0);
}

BYTE Configure_Main(BYTE chnum,BYTE x)
{
	Soft_Key_Temp=1;
	P_M_num = M_num;
	ClrDispCnt(0x01, 0x00, 0x04, 0x00, 0x00, 0x00);
	ChanRedrawFlag |= BG_CLEAR + CHAN_STATUS;
	M_num = P_CONF_PROT;
	MenuRedrawFlag|=MENU_CHANGE;
	DataRedrawFlag|=(PARA_CHANGE + BG_CLEAR);
	return(0);
}

BYTE Password_Process(BYTE chnum,BYTE x)
{
	char p3k_Model_Number[10];
	char debug_mode[10];

	p3k_send_tx_list tx_data;

	switch(P3k_Chan_Data.INFO.MACHTYPE) {
	case MODEL3031E:
		sprintf( p3k_Model_Number, "3031" );
		break;
	case MODEL3032E:
		sprintf( p3k_Model_Number, "3032" );
		break;	
	default:
		break;
	}
#if 1
	sprintf( debug_mode, "1000" );
	if(strncmp((const char *)KeyinBuf, (const char *)debug_mode, 4) == 0)
		debug_pass_flag = 1;
#endif


	if(strncmp((const char *)KeyinBuf, (const char *)p3k_Model_Number, 4) == 0)//Adam_debug
		Cal_Init_Proc();
	else
		Save_Recall_InfoFlag|=Data_Process+password_error;

	KeyinCT = KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = 0x00;

	if( KeyInFlag & DIGI_KEY_IN)
		KeyInFlag &= ~DIGI_KEY_IN;

	DataRedrawFlag |= PARA_CHANGE;
	return(0);
}

BYTE Config_Protection(BYTE chnum, BYTE x)
{
	p3k_send_tx_list tx_data;

	if( M_num != P_CONF_PROT) {
		ClrDispCnt(0x01, 0x00, 0x04, 0x00, 0x00, 0x00);
		M_num = P_CONF_PROT;
		DataRedrawFlag |= (PARA_CHANGE + BG_CLEAR);
		MenuRedrawFlag |= MENU_CHANGE;
		tx_data.ADDRH = 0x00;
		tx_data.ADDRL = 0x04;
		SendTXData(&tx_data);
	}
	return(0);
}

BYTE Config_Other(BYTE chnum, BYTE x)
{
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	if( M_num != P_CONF_OTHER) {
		P3k_Chan_Data.CONF.Cut_Off_cnt =0;
		M_num = P_CONF_OTHER;
		ClrDispCnt(0x01, 0x00, 0x04, 0x00, 0x00, 0x00);
		DataRedrawFlag |= (PARA_CHANGE + BG_CLEAR);
		MenuRedrawFlag |= MENU_CHANGE;
	}
	return(0);
}

BYTE Config_GoNoGo(BYTE chnum,BYTE x)
{
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	if((M_num == P_CC_SPEC)||(M_num == P_CR_SPEC)||(M_num == P_CV_SPEC)||(M_num == P_CP_SPEC))
		return (0);

	if(CC_MODE==Data_tmp->CURRMODE)
		M_num = P_CC_SPEC;
	else if(CR_MODE==Data_tmp->CURRMODE)
		M_num = P_CR_SPEC;
	else if(CV_MODE==Data_tmp->CURRMODE)
		M_num = P_CV_SPEC;
	else
		M_num = P_CP_SPEC;

	ClrDispCnt(0x01, 0x00, 0x04, 0x00, 0x00, 0x00);
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;

	return (0);
}

BYTE Config_Parallel(BYTE chnum, BYTE x)
{
	if( M_num != P_CONF_Para) {
		M_num = P_CONF_Para;
		Soft_Key_Temp = 1;
		ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
		MenuRedrawFlag |= MENU_CHANGE;
	}

	return 1;
}

BYTE Config_Knob(BYTE chnum, BYTE x)
{
	if( M_num != P_CONF_KNOB) {
		M_num = P_CONF_KNOB;
		ClrDispCnt(0x01, 0x00, 0x04, 0x00, 0x00, 0x00);
		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
		MenuRedrawFlag |= MENU_CHANGE;
		ChanRedrawFlag |= CHAN_STATUS;
	}
	return(0);
}

BYTE Config_External(BYTE chnum,BYTE x)
{
	if( M_num != P_CONF_Ext) {
		M_num = P_CONF_Ext;
		ClrDispCnt(0x01, 0x00, 0x04, 0x00, 0x00, 0x00);
		MenuRedrawFlag |= MENU_CHANGE;
		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	}

	return(0);
}

BYTE Prog_Chain(BYTE chnum, BYTE x)
{
	Soft_Key_Temp=0;
	SEQ_Save_Status=0;
	p3k_Disp_PROG = p3k_Chan_PROG;
	M_num = P_PROG_CHAIN;
	ClrDispCnt(0x00, 0x00, 0x03, 0x00, 0x00, 0x00);
	MenuRedrawFlag |= MENU_CHANGE;
	ClearP3KChanAllBG(Parameter_Bottom_Bolor);

	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;

	return(0);
}

BYTE Utility_Proc(BYTE chnum, BYTE x)
{
	UBYTE err;
	ULONG RUNPROG_temp_count;

	struct tm _mTIME; //Current Time update by TimerTask

	switch(M_num) {
	case P_UTIL_MAIN:
	case P_UTIL_INTERFACE:
	case P_UTIL_OTHER:
	case P_UTIL_T_DATE:
	case P_UTIL_LOAD:
	case P_UTIL_SYSINFO:
	case P_UTIL_SYSMEMO:
		switch(x) {
		case F1_KEY:		/* System Information */
			System_Info_Test_Mode = 0;
			System_Info_Memo++;
			System_Info_Memo &= 0x1;

			if(System_Info_Memo)
				M_num = P_UTIL_SYSMEMO;
			else
				M_num = P_UTIL_SYSINFO;
			break;
		case F2_KEY:		/* Auto Load Setting */
			if(M_num==P_UTIL_LOAD)
				return(0);
			M_num=P_UTIL_LOAD;
			break;
		case F3_KEY:		/* Interface Setting */
			if(M_num==P_UTIL_INTERFACE)
				return(0);
			M_num = P_UTIL_INTERFACE;
			D_interface.INTERFACE	= UTILITY.INTERFACE;
			D_interface.BAUD		= RS232.BAUD;
			D_interface.STOP		= RS232.STOP;
			D_interface.PARITY		= RS232.PARITY;
			D_interface.MYADDR		= GPIBPAR.MYADDR;
			break;
		case F4_KEY:		/* Time & Date Setting */
			if(M_num==P_UTIL_T_DATE)
				return(0);
			M_num=P_UTIL_T_DATE;
			rtc_get(&_mTIME);
			TIMERSET.YEAR		= _mTIME.tm_year;
			TIMERSET.MONTH	= _mTIME.tm_mon;
			TIMERSET._DAY		= _mTIME.tm_mday;
			TIMERSET._HOUR	= _mTIME.tm_hour;
			TIMERSET._MINUTE  = _mTIME.tm_min;
			break;
		case F5_KEY:		/* Other Setting */
			if(M_num==P_UTIL_OTHER)
				return(0);
			M_num=P_UTIL_OTHER;
			break;
		default:
			break;
		}
		if(M_num==P_UTIL_OTHER)
			ClrDispCnt(0x00, 0x00, 0x04, 0x00, 0x00, 0x00);
		else if(M_num==P_UTIL_SYSINFO || M_num==P_UTIL_SYSMEMO)
			ClrDispCnt(0x00, 0x00, 3, 0x00, 0x00, 0x00);
		else
			ClrDispCnt(0x00, 0x00, 0x05, 0x00, 0x00, 0x00);
		MenuRedrawFlag|=MENU_CHANGE;
		DataRedrawFlag|=BG_CLEAR + PARA_CHANGE;
		//ClearChanBG(Parameter_Bottom_Bolor);	/* Clear Chan Bar Display*/
		ClearP3KChanAllBG(Parameter_Bottom_Bolor);
		break;
	default:
		break;
	}
	return(0);
}

BYTE Save_Data(BYTE chnum, BYTE x)
{
	char Default_Message1[60],Default_Message2[60];
	char str[30];

	P3k_Prog_Str *Prog_tmp = &p3k_Disp_PROG;
	P3k_Disp_Str *Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str *Data_tmp = &P3k_Chan_Data;

	p3k_send_tx_list tx_data;

	switch(M_num) {
	case P_PROG_CHAIN:
		if( (!SEQ_Save_Status)&&(M_num==P_PROG_CHAIN) )
			return(0);
		p3k_Chan_PROG	= p3k_Disp_PROG;
		SEQ_Save_Status= 0;
		BackupRunProg();
		break;
	case P_PROG_MAIN:
		if( (!SEQ_Save_Status)&&(M_num==P_PROG_MAIN) )
			return(0);
		p3k_Chan_PROG = p3k_Disp_PROG;
		SEQ_Save_Status = 0;
		DispMode = DispMode_SELECT_CH;
		DataRedrawFlag |= PARA_CHANGE;
#if Enable_Optim_display
		DataRedrawFlag |= BG_CLEAR_FLAG;
#endif
		BackupRunProg();
		break;
	case P_FILE_CHAN:												/* Save data of Chan */
		if(!Save_Status)
			return(0);

		if(F_Media_Memory==p3k_File_Utility_BAR.MEDIA) {			/* Media = Memory */
			DispMode = DispMode_SELECT_CH;
			DataRedrawFlag	|= PARA_CHANGE + BG_CLEAR;
			if(F_Memory_Data==p3k_File_Utility_BAR.Mem_Data_Type) {	/* Save Memory No 1~256 */
				MEMORY_SAVE_FLAG = M_Memory_Save_Ok;
				Save2Mem(SR_MEMORY_MODE, p3k_File_Utility_BAR.MEMORY_ADDR);
				BackupRunProg();
			}

			if(F_Setup_Data==p3k_File_Utility_BAR.Mem_Data_Type) {	/* Setup Memory 1~100 */
				MEMORY_SAVE_FLAG = M_Setup_Save_Ok;
				SaveSetupDataAction(p3k_File_Utility_BAR.SMEMORY_ADDR);
			}

			if(F_Preset_Data==p3k_File_Utility_BAR.Mem_Data_Type) {	/* Preset P0~P9 */
				MEMORY_SAVE_FLAG = M_Preset_Save_Ok;
				Save2Mem( SR_PRESET_MODE,p3k_File_Utility_BAR.PRE_MEMORY_ADDR);
			}

		} else if(F_Media_USB==p3k_File_Utility_BAR.MEDIA) {			/* Media = USB */
			if(DispMode==DispMode_BROWSE_ITEMS)
				return(0);
			GUI_SetFont(Parameter_Font);
			GUI_SetBkColor(Message_Bottom_Bolor);
			GUI_SetColor(Message_Font_Bolor);
			GUI_GotoXY(10, 175);
			GUI_DispChars(' ',51);
			GUI_SetTextAlign(GUI_TA_LEFT);

			if((OverWrite_Flag==0)&&(CheckSameFile(SaveFileName))) {
				sprintf(str,"OverWrite %s?\n",SaveFileName);
				GUI_DispStringAt(str, 10, 175);
				OverWrite_Flag=1;
				Save_Recall_InfoFlag |= Data_Process;
				break;
			}

			sprintf(str,"Saving in %s",SaveFileName);
			GUI_DispStringAt(str, 10, 175);
			strcpy(SaveFileName_Temp,SaveFileName);
			DMA_Update_Flag = 1;
			Update_Panel();

			if(p3k_File_Utility_BAR.USB_Data_Type==F_Memory_Data)
				SaveProgDataToFile();								/* Save Memory All Data(No.1~256) to USB*/
			else if(p3k_File_Utility_BAR.USB_Data_Type==F_Setup_Data)
				SaveSetupDataToFile();								/* Save Setup Memory 1~100 to USB*/
			else if(p3k_File_Utility_BAR.USB_Data_Type==F_Preset_Data)
				SavePresetDataToFile();								/* Save Preset All Data(0~9) to USB*/
			else if(p3k_File_Utility_BAR.USB_Data_Type==F_NSeq_Data)
				SaveNSeqDataToFile();
			else if(p3k_File_Utility_BAR.USB_Data_Type==F_FSeq_Data)
				SaveFSeqDataToFile();

			Save_Recall_InfoFlag |= Data_Process+Save_Ok;
		} else if(F_Media_Default==p3k_File_Utility_BAR.MEDIA) {
			GUI_SetFont(Parameter_Font);
			GUI_SetBkColor(Message_Bottom_Bolor);
			GUI_SetColor(Message_Font_Bolor);
			GUI_GotoXY(10, 175);
			GUI_DispChars(' ',51);
			GUI_GotoXY(10, 150);
			GUI_DispChars(' ',51);
			GUI_SetTextAlign(GUI_TA_LEFT);

			if(Default_info&Def_Save_CONFIRM) {
				sprintf(Default_Message2,"Save User's Default...\n");
				GUI_DispStringAt(Default_Message2, 10, 175);
				DMA_Update_Flag = 1;
				Update_Panel();
				BackupUserDefaultData(1);
				sprintf(SaveFileName_Temp,"User's Default");
				Save_Recall_InfoFlag |= Data_Process+Save_Ok;
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				Default_info = 0;
			} else {
				sprintf(Default_Message1,"Warning!Press F3 again will\n");
				sprintf(Default_Message2,"Save User's Default !\n");
				GUI_DispStringAt(Default_Message1, 10, 150);
				GUI_DispStringAt(Default_Message2, 10, 175);
				Default_info = Def_Save_CONFIRM;
			}
		}
		break;
	case P_FILE_MACHINE:
		break;
	case P_UTIL_KEYPAD:
		if(KeypadRedrawFlag & KEYPAD_NEW_FOLDER)
			FMinfo |= FM_MKDIR;
		else if(KeypadRedrawFlag & KEYPAD_RENAME_FOLDER)
			FMinfo |= FM_RENAME;
		break;
	case P_PROG_Detail:
		if(!Go_NG_Save_Status)
			return(0);
		SaveGoNGResult();
		break;
	case P_Seq_Normal:
		if((!SEQ_Save_Status)&&(M_num==P_Seq_Normal))
			return(0);
	case P_NSeq_Edit:
		if((!SEQ_Save_Status)&&(M_num==P_NSeq_Edit))
			return(0);
		P3k_NSeq_Data = P3k_NSeq_Disp;
		BackupNSeq();
		SEQ_Save_Status = 0;
		break;
	case P_Seq_Fast:
		if((!SEQ_Save_Status)&&(M_num==P_Seq_Fast))
			return(0);
	case P_FSeq_Edit:
		if((!SEQ_Save_Status)&&(M_num==P_FSeq_Edit)){
#if Enable_fseq_deletAll
			Del_FSeq_All();
#endif
			return(0);
		}
		P3k_FSeq_Data = P3k_FSeq_Disp;
		BackupFSeq();
		SEQ_Save_Status = 0;
		break;
#if Enable_OCP_function
	case P_FUNC_OCP:
		P3K_OCP_Data = P3K_OCP_Disp;
		BackupOCP();
		SEQ_Save_Status = 0;
		
		break;
#endif	
#if Enable_OPP_function
	case P_FUNC_OPP:
		P3K_OPP_Data = P3K_OPP_Disp;
		BackupOPP();
		SEQ_Save_Status = 0;
		break;
#endif
#if 0//Enable_LED_function
		case P_FUNC_FLED:
		case P_FUNC_FLED_EDIT:
			P3k_FLed_Data = P3k_FLed_Disp;
			BackupLED();
			SEQ_Save_Status = 0;
			break;

		case P_FUNC_CLED:
		case P_FUNC_CLED_EDIT:
			P3k_CLed_Data = P3k_CLed_Disp;
			BackupLED();
			SEQ_Save_Status = 0;
			break;
#endif

	default:
		break;
	}
	MenuRedrawFlag |= MENU3_CHANGE;
	return(0);
}

extern const P3k_Timing_Str DEFAULT_PROG;
BYTE Recall_Data(BYTE chnum, BYTE x)
{
	char Default_Message1[60],Default_Message2[60];
	char str[30];
	char str_1[30];
	unsigned char i,Recall_result;
	unsigned char USB_File_Type;
	unsigned short j;

	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	p3k_send_tx_list tx_data;

	USB_File_Type = p3k_File_Utility_BAR.USB_Data_Type;

	switch(M_num) {
	case P_PROG_CHAIN:	/* Recall Default */
		for(i=0; i<14; i++)
			p3k_Disp_PROG.PROGSEQ[i]=0;
		ClrDispCnt(0x01, 0x00, 0x03, 0x00, 0x00, 0x00);
		p3k_Disp_PROG.Chain_Start_Prog=0;
		DataRedrawFlag|=PARA_CHANGE+BG_CLEAR_FLAG;
		SEQ_Save_Status=1;
		Soft_Key_Temp=0;
		MenuRedrawFlag|=MENU3_CHANGE;
		break;
	case P_PROG_MAIN:	/* Recall Default */
		for(j=0; j<1024; j++) {
			Prog_Seq_Data.Prog_Disp_Data[j-1].Prog_No = 0;
			Prog_Seq_Data.Prog_Disp_Data[j-1].Step_No = 0;
			Prog_Seq_Data.Prog_Disp_Data[j-1].SPEC_Result = 0;
		}

		p3k_Disp_PROG.Timing_Data[p3k_Disp_PROG.Prog_No] = DEFAULT_PROG;
		DispMode = DispMode_SELECT_CH;
		DataRedrawFlag |= PARA_CHANGE;
#if Enable_Optim_display
		DataRedrawFlag |= BG_CLEAR_FLAG;
#endif
		SEQ_Save_Status=1;
		Soft_Key_Temp=0;
		MenuRedrawFlag|=MENU3_CHANGE;
		break;
	case P_FILE_CHAN:
		if(!Recall_Status)
			return(0);

		switch(p3k_File_Utility_BAR.MEDIA) {
		case F_Media_Memory:
			Soft_Key_Temp=0;
			if(F_Memory_Data==p3k_File_Utility_BAR.Mem_Data_Type) {	/* Memory No 1~256 */
				if(Recall2Mem(SR_MEMORY_MODE, p3k_File_Utility_BAR.MEMORY_ADDR)==0) {
					Soft_Key_Temp = 1;
					return(0);
				}

				if((Data_tmp->CURRMODE!=Disp_tmp->CURRMODE)&&(UTILITY.LOAD_CTL)) {
#if Enable_AutoLoad
					if(UTILITY.AutoLoadOffMode==0) {
						PEL3000_LED_Control( LED_LOAD, 1 );
					}
#endif

					UTILITY.LOAD_CTL = Switch_OFF;
					PEL3000_LED_Control( LED_LOAD, Switch_OFF );
					SysRedrawFlag |= PROG_UPDATA;
					tx_data.ADDRH = Machine_Command;
					tx_data.ADDRL = Machine_Load_OnOff;
					SendTXData(&tx_data);
#if Enable_AutoLoad
					if(UTILITY.AutoLoadOffMode==0) {
						OSTimeDly(5);
						Auto_Load_On();
					}
#endif					
				}

				Recall2Display();
				tx_data.ADDRH = 0x31;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				ChanRedrawFlag |= CHAN_STATUS;
				DataRedrawFlag |=BG_CLEAR+ PARA_CHANGE;
				MenuRedrawFlag |= MENU_CHANGE;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
			}

			if(F_Setup_Data==p3k_File_Utility_BAR.Mem_Data_Type) {	/* Setup Memory 1~100 */
				GUI_SetFont(Parameter_Font);
				GUI_SetBkColor(Message_Bottom_Bolor);
				GUI_SetColor(Message_Font_Bolor);
				GUI_GotoXY(10, 175);
				GUI_DispChars(' ',51);
				GUI_SetTextAlign(GUI_TA_LEFT);

				if(Backup_Setup_Data[p3k_File_Utility_BAR.SMEMORY_ADDR].Data_Ready==200) {
					sprintf(str,"Recall in Setup Memory %d",p3k_File_Utility_BAR.SMEMORY_ADDR+1);
					GUI_DispStringAt(str, 10, 175);
				} else {
					sprintf(str,"No Data to Recall");
					GUI_DispStringAt(str, 10, 175);
					MEMORY_SAVE_FLAG = M_Clear_Message;
					DispMode = DispMode_SELECT_CH;
					break;
				}

				MEMORY_SAVE_FLAG = M_Setup_Recall_Ok;
				DispMode = DispMode_SELECT_CH;
				ChanRedrawFlag |= CHAN_STATUS;
				DataRedrawFlag |= BG_CLEAR+ PARA_CHANGE;
				MenuRedrawFlag |= MENU_CHANGE;
				RecallSetupData(p3k_File_Utility_BAR.SMEMORY_ADDR);
				if(M_num == P_CC) {
					DispCT=0;
					DispCT1=0;
					DispScrStartCT=0;
					DispScrEndCT=2;
					DispScrCurrLoc=0;
					B_DispCT=0;
				}
			}

			if(F_Preset_Data==p3k_File_Utility_BAR.Mem_Data_Type) {	/* Preset P0~P9 */
				if(Recall2Mem( SR_PRESET_MODE, p3k_File_Utility_BAR.PRE_MEMORY_ADDR)==0) {
					Soft_Key_Temp = 1;
					return(0);
				}

				if((Data_tmp->CURRMODE!=Disp_tmp->CURRMODE)&&(UTILITY.LOAD_CTL)) {
#if Enable_AutoLoad
					if(UTILITY.AutoLoadOffMode==0) {
						PEL3000_LED_Control( LED_LOAD, 1 );
					}
#endif
					UTILITY.LOAD_CTL = Switch_OFF;
					PEL3000_LED_Control( LED_LOAD, Switch_OFF );
					SysRedrawFlag |= PROG_UPDATA;
					tx_data.ADDRH = Machine_Command;
					tx_data.ADDRL = Machine_Load_OnOff;
					SendTXData(&tx_data);
#if Enable_AutoLoad
					if(UTILITY.AutoLoadOffMode==0) {
						OSTimeDly(5);
						Auto_Load_On();
					}
#endif					
				}

				Recall2Display();
				tx_data.ADDRH = 0x30;
				tx_data.ADDRL = p3k_File_Utility_BAR.PRE_MEMORY_ADDR << 4;
				SendTXData(&tx_data);
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
#if Normal_TEST
				printf("Recall Preset %d OK!\n", p3k_File_Utility_BAR.PRE_MEMORY_ADDR);
#endif
			}
			break;
		case F_Media_USB:
			if(DispMode==DispMode_BROWSE_ITEMS)
				return(0);

			if((RecallFileName[0]==0)||(strcmp("No File",RecallFileName))==0) {
				DataRedrawFlag |= PARA_CHANGE;
				Save_Recall_InfoFlag |= No_File + Data_Process;
				Debug_printf("No file to Recall\n");
				return(0);
			}

			GUI_SetFont(Parameter_Font);
			GUI_SetBkColor(Message_Bottom_Bolor);
			GUI_SetColor(Message_Font_Bolor);
			GUI_GotoXY(10, 175);
			GUI_DispChars(' ',51);
			GUI_SetTextAlign(GUI_TA_LEFT);
			sprintf(str,"Recalling in %s",RecallFileName);
			GUI_DispStringAt(str, 10, 175);
			DataRedrawFlag |= PARA_CHANGE;
			DMA_Update_Flag = 1;
			Update_Panel();

			switch(USB_File_Type) {
			case F_Memory_Data:
				Recall_result = RecallDataFromFile(Recall_DataType_Prog,RecallFileName);
				sprintf(str,"USB RunProg");
				break;
			case F_Setup_Data:
				Recall_result = RecallDataFromFile(Recall_DataType_Setup,RecallFileName);
				sprintf(str,"USB Setup");
				break;
			case F_Preset_Data:
				Recall_result = RecallDataFromFile(Recall_DataType_Preset,RecallFileName);
				sprintf(str,"USB Preset");
				break;
			case F_NSeq_Data:
				Recall_result = RecallDataFromFile(Recall_DataType_NSEQ,RecallFileName);
				sprintf(str,"USB N.Seq.");
				break;
			case F_FSeq_Data:
				Recall_result = RecallDataFromFile(Recall_DataType_FSEQ,RecallFileName);
				sprintf(str,"USB F.Seq.");
				break;
			default:
				break;
			}

			if(Recall_Complete==Recall_result) {
				Save_Recall_InfoFlag |= Data_Process+Recall_Ok;
				sprintf(str_1,"Recall %s All Data ok\n",str);
				Debug_printf(str_1);
			} else if(Machine_Type_Error==Recall_result) {
				Save_Recall_InfoFlag |= Data_Process+Type_Error;
				Debug_printf("Machine Type Error\n");
			} else {
				Save_Recall_InfoFlag|=Data_Process+Recall_Fail;
				sprintf(str_1,"Recall %s All Data Failed\n",str);
				Debug_printf(str_1);
				sprintf(str_1,"Recall_result=%d\n",Recall_result);
				Debug_printf(str_1);
			}
			break;
		case F_Media_Default:
			GUI_SetFont(Parameter_Font);
			GUI_SetBkColor(Message_Bottom_Bolor);
			GUI_SetColor(Message_Font_Bolor);
			GUI_GotoXY(10, 175);
			GUI_DispChars(' ',51);
			GUI_GotoXY(10, 150);
			GUI_DispChars(' ',51);
			GUI_SetTextAlign(GUI_TA_LEFT);

			if(Default_info&Def_Recall_CONFIRM) {
				sprintf(Default_Message2,"Recall User's Default...\n");
				GUI_DispStringAt(Default_Message2, 10, 175);
				DMA_Update_Flag = 1;
				Update_Panel();
				RecallUserDefault(1);
				Default_info = 0;
			} else {
				sprintf(Default_Message1,"Warning!Press F4 again will\n");
				sprintf(Default_Message2,"Recall User's Default !\n");
				GUI_DispStringAt(Default_Message1, 10, 150);
				GUI_DispStringAt(Default_Message2, 10, 175);
				Default_info = Def_Recall_CONFIRM;
				MenuRedrawFlag |= MENU_CHANGE;
			}
			break;
		default:
			break;
		}
		break;
	case P_FILE_MACHINE:
		break;
	default:
		break;
	}
	MenuRedrawFlag |= MENU_CHANGE;
	return(0);
}

BYTE Edit_Chain_Start(BYTE chnum, BYTE x)
{
	switch(x) {
	case F1_KEY:
		if(DispMode==0)
			return(0);
		ClrDispCnt(0x00, 0x00, 0x03, 0x00, 0x00, 0x00);
		break;
	default:
		break;
	}
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	//ClearChanBG(Parameter_Bottom_Bolor);
	MenuRedrawFlag |= MENU_CHANGE;
	return(0);
}

extern BYTE *NewHelpStr,*OldHelpStr;
extern BYTE *HelpMenuStr[MAXMENU+5/*+HELP_MAX_OFFSET*/][MAX_LANGUAGE];
BYTE *TempHelpStr=(void *)0;
BYTE Help_func(BYTE chnum, BYTE x)
{
	if(Help_Key_Flag==0) {
		Soft_Key_Temp=0;
		Help_Key_Flag=1;
		TempHelpStr=NewHelpStr;
		NewHelpStr=(BYTE *)(BYTE*)HelpMenuStr[M_num][UTILITY.LANGUAGE];
		OldHelpStr=(void *)0;
		DataRedrawFlag |=BG_CLEAR + PARA_CHANGE;
		MenuRedrawFlag|= MENU_CHANGE;
	}
	return(0);
}

BYTE Prog_Seq_Next(BYTE chnum, BYTE x)
{
	p3k_send_tx_list tx_data;
	if(P3k_Chan_Data.CONF.Ext_Setting.MultilPara)
		return (0);
	if(Prog_Seq_Data.MANUAL_CTRL) {
		Prog_Seq_Data.MANUAL_CTRL = 0x0;
		MenuRedrawFlag |= MENU2_CHANGE;
		if(Display_Continue==Prog_Seq_Data.SEQ_Stop_Continue) {
			Stop_Next_Proc=1;
			return (0);
		}
		tx_data.ADDRH = Machine_Command;
		tx_data.ADDRL = Machine_Input_Trigger;
		SendTXData(&tx_data);
	}
	return(0);
}

BYTE Prog_Seq_Stop_Continue(BYTE chnum, BYTE x)
{
	p3k_send_tx_list tx_data;

	if(Prog_Seq_Data.SEQ_Stop_Continue==2)
		return (0);
	if (Prog_Seq_Data.MANUAL_CTRL) //the same time continue  & next bug
		return (0);
	if(P3k_Chan_Data.CONF.Ext_Setting.MultilPara)
		return (0);

	Prog_Seq_Data.SEQ_Stop_Continue++;
	Prog_Seq_Data.SEQ_Stop_Continue &= 0x01;

	if(Stop_Next_Proc==1) {
		Stop_Next_Proc=0;
		Prog_Seq_Next(0,0);
	}

	tx_data.ADDRH = Machine_Command;
	tx_data.ADDRL = Machine_Pause_Prog;
	SendTXData(&tx_data);
	MenuRedrawFlag |= MENU1_CHANGE;
	return (0);
}

BYTE FileMedia_Proc(BYTE chnum, BYTE x)
{
	char tmp;

	switch(chnum) {
	case P_FILE_CHAN:
		tmp = p3k_File_Utility_BAR.MEDIA;
		tmp++;
		if(tmp>=3)
			tmp=0;
		p3k_File_Utility_BAR.MEDIA=tmp;
		if(F_Media_USB==p3k_File_Utility_BAR.MEDIA)		/* Media = USB 	*/
			USB_Status_Display=USB_Status;
		else
			USB_Status_Display=USB_Busy;
		if( (F_Media_USB==p3k_File_Utility_BAR.MEDIA)&&(USB_Status_Display!=USB_Exist) ) {
			Save_Status	= 0;
			Recall_Status	= 0;
		} else {
			Save_Status	= 1;
			Recall_Status	= 1;
		}
		DispMode = DispMode_SELECT_CH;
		DispCT = 0;
		Default_info = 0;
		MEMORY_SAVE_FLAG = M_Nothing;
		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
		MenuRedrawFlag |= MENU_CHANGE;
		break;
	case P_FILE_MACHINE:
		break;
	default:
		break;
	}
	MenuRedrawFlag|=MENU1_CHANGE;
	return(0);
}

extern FMvar FM;
extern UWORD FM_InfoFlag;
BYTE FileUtil_Proc(BYTE chnum, BYTE x)
{
	if(USB_Status_Display<=USB_Busy)
		return 0;

	Soft_Key_Temp=0;
	P_M_num = M_num;
	M_num = P_UTIL_FILE;
	MenuRedrawFlag |= MENU_CHANGE;
	Frame_Change();
	FileUtilRedrawFlag |= FILEUTIL_DISP_INIT;
	FM_InfoFlag |= FM_SHOW_INIT+FM_SHOW_PATH+FM_SHOW_FILE_LIST+FM_SHOW_ALL;
	FM.DispStartPos=0;
	FM.SelPtr=0;
	return(0);
}

BYTE FileKeyPad_Proc(BYTE chnum, BYTE x)
{
	switch(x) {
	case F2_KEY:
		SaveFileFlag|=SaveFileFlagNewFolder;
		SaveFileFlag&=~(SaveFileFlagRename);
		KeypadRedrawFlag |= KEYPAD_NEW_FOLDER;
		break;
	case F3_KEY:
		if(FMrename()==-1)
			return -1;
		SaveFileFlag|=SaveFileFlagRename;
		SaveFileFlag&=~(SaveFileFlagNewFolder);
		KeypadRedrawFlag |=KEYPAD_RENAME_FOLDER;
		break;
	default:
		break;
	}
	Soft_Key_Temp = 0;
	K_M_num = M_num;
	M_num = P_UTIL_KEYPAD;
	MenuRedrawFlag		|= MENU_CHANGE;
	KeypadRedrawFlag	|= KEYPAD_UPDATA;
	return(0);
}

BYTE Time_Set(BYTE chnum, BYTE x)
{
	char tmp;

	SetRTC(0);

	MenuRedrawFlag |= MENU_CHANGE+VAR_STR_MENU_UPDATA;
	SysRedrawFlag |= TIME_UPDATA;
	return(0);
}

BYTE Pre_Menu(BYTE chnum,BYTE x)
{
	p3k_send_tx_list tx_data;
	BYTE tmp;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	Soft_Key_Temp=0;
	switch(M_num) {
	case P_CC_SPEC:
		M_num = P_CC;
		DispCT = 0x00;
		ClrDispCnt( 0x01, 0x00, 0x04, 0x00, 0x00, 0x00);
		ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
		break;
	case P_CR_SPEC:
		M_num = P_CR;
		DispCT = 0x00;
		DispMode = DispMode_BROWSE_ITEMS;
		ClrDispCnt( 0x01, 0x00, 0x04, 0x00, 0x00, 0x00);
		ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
		break;
	case P_CV_SPEC:
		M_num = P_CV;
		DispCT = 0x00;
		DispMode = DispMode_BROWSE_ITEMS;
		ClrDispCnt( 0x01, 0x00, 0x04, 0x00, 0x00, 0x00);
		ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
		break;
	case P_CP_SPEC:
		M_num = P_CP;
		DispCT = 0x00;
		DispMode = DispMode_BROWSE_ITEMS;
		ClrDispCnt( 0x01, 0x00, 0x04, 0x00, 0x00, 0x00);
		ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
		break;
	case P_CONF_PROT:
	case P_CONF_OTHER:
		if(0==P_M_num)	M_num = Disp_tmp->CURRMODE;
		else			M_num = P_M_num;
		ClrDispCnt( 0x01, 0x00, 0x04, 0x00, 0x00, 0x00);
		if( (Disp_tmp->CONF.CH_Control)&&(M_num==P_CC) )
			DispMode=DispMode_SELECT_CH;
		if( (Disp_tmp->CONF.CH_Control)&&(M_num==P_CV) )
			DispCT=0x2;
		ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
		break;
	case P_CONF_KNOB:
	case P_CONF_Para:
	case P_CONF_Ext:
		Soft_Key_Temp = 1;
		M_num = P_CONF_PROT;
		ClrDispCnt(0x01, 0x00, 0x04, 0x00, 0x00, 0x00);
		ChanRedrawFlag |= BG_CLEAR + CHAN_STATUS;
		MenuRedrawFlag |= MENU_CHANGE;
		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
		break;
	case P_PROG_MAIN:
	case P_Seq_FUNC:
	case P_FUNC_POWER:
#if Enable_OCP_function
	case P_FUNC_MAIN_2:
#endif		
	case P_Seq_Normal:
	case P_Seq_Fast:
	case P_FUNC_OCP:
		M_num = P_FUNC_MAIN;
		ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		MenuRedrawFlag |= MENU_CHANGE;
		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
		ChanRedrawFlag |= BG_CLEAR;
		HelpRedrawFlag &= ~HELP_FUN_ON;
		break;
	case P_PROG_CHAIN:
		M_num = P_PROG_MAIN;
		SEQ_Save_Status=0;
		MenuRedrawFlag |= MENU3_CHANGE;
		DataRedrawFlag |= (PARA_CHANGE + BG_CLEAR );
		ChanRedrawFlag |= BG_CLEAR;
		ClrDispCnt( 0x00, 0x00, 0x03, 0x00, 0x00, 0x00);
		break;
	case P_UTIL_INTERFACE:
	case P_UTIL_OTHER:
	case P_UTIL_T_DATE:
	case P_UTIL_LOAD:
	case P_UTIL_SYSINFO:
	case P_UTIL_SYSMEMO:
		M_num = P_UTIL_MAIN;
		MenuRedrawFlag |= MENU_CHANGE;
		DataRedrawFlag |= PARA_CHANGE+BG_CLEAR;
		break;
	case P_UTIL_KEYPAD:
		if(K_M_num==P_UTIL_FILE) {
			M_num = P_UTIL_FILE;
			FM_InfoFlag|=FM_SHOW_FILE_LIST+FM_SHOW_PATH+FM_SHOW_ALL;//Print file list and redraw scroll bar.
			FileUtilRedrawFlag|=FILEUTIL_DISP_INIT;
		} else {		
			M_num = K_M_num;
			if((K_M_num==P_FUNC_FLED)||(K_M_num==P_FUNC_CLED)){
				//DataRedrawFlag |= BG_CLEAR;
				DataRedrawFlag |= BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE ;
				MenuRedrawFlag |= BG_CLEAR;
				DispMode = DispMode_BROWSE_ITEMS;
			}else{
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
			}
		}
		break;
	case P_UTIL_FILE:
		if(!F_M_num)
			M_num = Disp_tmp->CURRMODE;
		else
			M_num = F_M_num;

		DispMode =DispMode_SELECT_CH;

		if(P_FILE_MACHINE==M_num)
			ClearP3KChanAllBG(Parameter_Bottom_Bolor);
		else
			ChanRedrawFlag |= BG_CLEAR + CHAN_STATUS;

		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
		break;
	case P_HELP_HELP:
		if(Help_Key_Flag) {
			Help_Key_Flag=0;
			NewHelpStr=TempHelpStr;
			OldHelpStr=(void *)0;
			DataRedrawFlag |=BG_CLEAR + PARA_CHANGE;
			MenuRedrawFlag|= MENU1_CHANGE;
			break;
		}

		if(!H_M_num)
			M_num = Disp_tmp->CURRMODE;
		else
			M_num = H_M_num;

		DataRedrawFlag|=PARA_CHANGE+BG_CLEAR;

		if((M_num == P_PROG_CHAIN)||(M_num == P_PROG_MAIN)) {
			SEQ_Save_Status=0;
			MenuRedrawFlag|=MENU3_CHANGE;
		}

		if(M_num == P_PROG_CHAIN)
			DispScrEndCT = 0x3;

		if(M_num >= P_CC && M_num <= P_CP)
			ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
		else if((M_num >= P_CC_SPEC && M_num <= P_CONF_OTHER) || M_num == P_CONF_KNOB)
			ClrDispCnt(0x01, 0x00, 0x04, 0x00, 0x00, 0x00);
		else if(M_num == P_CONF_Para || M_num == P_CONF_Ext)
			ClrDispCnt(0x01, 0x00, 0x01, 0x00, 0x00, 0x00);

		if( M_num==P_UTIL_KEYPAD || M_num==P_UTIL_FILE)
			M_num=P_FILE_CHAN;

		if( (M_num >= P_CC && M_num <= P_CONF_Ext)||(M_num== P_FILE_CHAN))
			ChanRedrawFlag|= CHAN_CHANGE;
		else
			ClearP3KChanAllBG(Parameter_Bottom_Bolor);

		HelpRedrawFlag &= ~HELP_FUN_ON;
		break;
	case P_CAL_MODE:
		//System_Ready	= 0;
		if(P_M_num==P_CAL_MODE) P_M_num =CC_MODE;
		M_num		= P_M_num;
		CAL_HI_LOW_SET_OK = 0;
		P3K_CALIBRATION_BAR.MODE	= P_CC;
		P3K_CALIBRATION_BAR.RANGE	= HIGH_RANGE;
		P3K_CALIBRATION_BAR.START	= 1;
		P3K_CALIBRATION_BAR.PSense	= 0;
		CtrlFlag1&=(~Cal_Wait_moment);
		DataRedrawFlag|=PARA_CHANGE+BG_CLEAR;
		ClrDispCnt(0x00, 0x00, 0x03, 0x00, 0x00, 0x00);
		if((M_num==P_CONF_OTHER)||(M_num==P_CONF_PROT)||(M_num==P_CC_SPEC)||(M_num==P_CR_SPEC)||(M_num==P_CV_SPEC)||(M_num==P_CP_SPEC)||(M_num==P_CONF_Ext)||(M_num==P_CONF_KNOB)||(M_num==P_CONF_Para)) {
			DispMode		= 1;
			DispScrEndCT	= 4;
		}
		if((M_num==P_PROG_CHAIN)||(M_num==P_PROG_MAIN)) {
			SEQ_Save_Status	=  0;
			MenuRedrawFlag		|= MENU3_CHANGE;
		}
		UTILITY.LOAD_CTL	= Switch_OFF;
		tx_data.ADDRH	= Machine_Command;
		tx_data.ADDRL	= Machine_Load_OnOff;
		SendTXData(&tx_data);
		PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
		if( M_num==P_UTIL_KEYPAD || M_num==P_UTIL_FILE)
			M_num=P_FILE_CHAN;
		if(((M_num>=P_CC)&&(M_num<=P_CONF_Ext))||(M_num==P_FILE_CHAN))
			ChanRedrawFlag |= CHAN_CHANGE;
		else
			ClearP3KChanAllBG(Parameter_Bottom_Bolor);
		FPGA_Init();
		//System_Ready=1;
		break;
	case P_Input_Password:
	case P_Cal_Value:
	case P_Test_Func:
		M_num = P_M_num;
		DataRedrawFlag |= PARA_CHANGE+BG_CLEAR;
		KeyinCT = KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = 0x00;
		ClrDispCnt(0x00, 0x00, 0x05, 0x00, 0x00, 0x00);
		if( M_num==P_CONF_OTHER||M_num==P_CONF_PROT||M_num==P_CC_SPEC||M_num==P_CR_SPEC||M_num==P_CV_SPEC||M_num==P_CP_SPEC||M_num==P_CONF_Ext||M_num==P_CONF_KNOB||M_num==P_CONF_Para) {
			DispMode		= 1;
			DispScrEndCT	= 4;
		}
		if((M_num == P_PROG_CHAIN)||(M_num == P_PROG_MAIN)) {
			SEQ_Save_Status=0;
			MenuRedrawFlag|=MENU3_CHANGE;
		}
		if((M_num == P_PROG_CHAIN))
			DispScrEndCT=0x3;
		if( M_num==P_UTIL_KEYPAD || M_num==P_UTIL_FILE)
			M_num=P_FILE_CHAN;
		if( (M_num>=P_CC&&M_num<=P_CONF_Ext)||(M_num==P_FILE_CHAN))
			ChanRedrawFlag|= CHAN_CHANGE;
		else
			ClearP3KChanAllBG(Parameter_Bottom_Bolor);
		break;
	case P_PROG_Detail:
		if(!S_M_num)
			M_num = Disp_tmp->CURRMODE;
		else
			M_num = S_M_num;
		if((M_num >= 0x05)||(M_num <= 0x0C)) {
			M_num = P_PROG_MAIN;
		}

		DataRedrawFlag|=PARA_CHANGE+BG_CLEAR;
		ClrDispCnt(0x00, 0x00, 0x05, 0x00, 0x00, 0x00);
		if(M_num==P_CC_SPEC||M_num==P_CR_SPEC||M_num==P_CV_SPEC)
			ClrDispCnt(0x01, 0x00, 0x00, 0x00, 0x00, 0x00);
		if((M_num == P_PROG_CHAIN)||(M_num == P_PROG_MAIN)) {
			SEQ_Save_Status=0;
			MenuRedrawFlag|=MENU3_CHANGE;
		}
		if(M_num == P_PROG_CHAIN)
			DispScrEndCT=0x3;
		if( M_num==P_UTIL_KEYPAD || M_num==P_UTIL_FILE)
			M_num=P_FILE_CHAN;
		if(M_num == P_UTIL_OTHER)
			DispScrEndCT=4;
		if(M_num == P_CONF_OTHER||M_num == P_CONF_PROT)
			DispMode =1;
		if( (M_num>= P_CC && M_num <= P_CONF_OTHER)||(M_num== P_FILE_CHAN))
			ChanRedrawFlag|= CHAN_CHANGE;
		else
			ClearP3KChanAllBG(Parameter_Bottom_Bolor);
		break;
	case P_NSeq_Edit:
		Seq_Select(0,F2_KEY);
		break;
	case P_FSeq_Edit:
		Seq_Select(0,F3_KEY);
		break;
	case P_FSeq_Fill:
		EditFastSeq(0,0);
		break;
#if Enable_OPP_function
	case P_FUNC_OPP:
	case P_FUNC_FLED:
	case P_FUNC_CLED:	
		APP_Function(0,0);
		break;
#endif		

#if Enable_Battery_Discharge
	case P_FUNC_batt:
		APP_Function(0,0);
		break;
	case P_FUNC_batt_EXECUTE:
		if(UTILITY.LOAD_CTL==Switch_OFF)
			goto_func_batt(0,0);
		break;	
#endif		
#if Enable_LED_function
	case P_FUNC_FLED_EDIT:
	case P_FUNC_FLED_EXECUTE:
		if(UTILITY.LOAD_CTL==Switch_OFF)
			goto_func_led(0,0);
		break;
	case P_FUNC_CLED_EDIT:
	case P_FUNC_CLED_EXECUTE:
		if(UTILITY.LOAD_CTL==Switch_OFF)
			goto_curve_led(0,0);
		break;	
#endif
	default:
		break;
	}

	if(M_num<=P_CP){
		Disp_tmp->CURRMODE = M_num;
		ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
	}

	MenuRedrawFlag |= MENU_CHANGE;
	return (0);
}

UBYTE MakeChanStatus(void)
{
	UBYTE tmp;
	p3k_mode_str *ptr;
	P3k_Data_Str *Data_tmp = &P3k_Chan_Data;

	if(CC_MODE==Data_tmp->CURRMODE)
		ptr = &Data_tmp->CC;	/* CC Mode */
	else if(CR_MODE==Data_tmp->CURRMODE)
		ptr = &Data_tmp->CR;	/* CR Mode */
	else if(CV_MODE==Data_tmp->CURRMODE)
		ptr = &Data_tmp->CV;	/* CV Mode */
	else
		ptr = &Data_tmp->CP;	/* CP Mode */

	tmp = 0;

	if(Data_tmp->CONF.CV_Func_En)
		tmp |= 0x01;		/* +CV Function Enable 1:ON , 0:OFF	*/
	if(ptr->STADYNA)
		tmp |= 0x02;		/* Static or Dynamic				*/
	if(Data_tmp->SPEC)
		tmp |= 0x04;		/* Go-NoGo On or Off				*/
	if(Data_tmp->SPECTYPE)
		tmp |= 0x08;		/* Go-NoGo Show Type Value or Pcet	*/
	if(ptr->ABSELECT)
		tmp |= 0x10;		/* 0 = A Value or 1 = B Value		*/
	if(ptr->RESPONSE)
		tmp |= 0x20;		/* CV Mode Response Slow or Fast	*/
	if(Data_tmp->VRange)
		tmp |= 0x40;		/* Vrange Hi or Low				*/
	return(tmp);
}

void Save2Mem(char mode, UWORD no)
{
	/*	Mode 0: Preset	*/
	/*	Mode 1: Memory	*/
	int i;
	UBYTE Memory_Range;
	UWORD *val,*mem;

	p3k_mode_str	*ptr;
	P3k_Memory_Str	*Memory_Ptr;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	if(CC_MODE==Data_tmp->CURRMODE)
		ptr = &Data_tmp->CC;
	else if(CR_MODE==Data_tmp->CURRMODE)
		ptr = &Data_tmp->CR;
	else if(CV_MODE==Data_tmp->CURRMODE)
		ptr = &Data_tmp->CV;
	else
		ptr = &Data_tmp->CP;

	if(SR_PRESET_MODE==mode)
		Memory_Ptr = &Data_tmp->P_DATA[no];	/* Preset */
	else if(SR_MEMORY_MODE==mode)
		Memory_Ptr = &Data_tmp->M_DATA[no];	/* Memory */

	Memory_Ptr->MODE		= Data_tmp->CURRMODE;
	Memory_Ptr->STATUS		= MakeChanStatus();
	Memory_Ptr->IRange		= Data_tmp->IRange;
	Memory_Ptr->P_F_Delay	= Data_tmp->P_F_Delay;
	Memory_Ptr->CV_VALUE	= Data_tmp->CV.STA[Data_tmp->VRange].VALUE1;
	mem = &Memory_Ptr->VALUE1;

	Memory_Ptr->RESPONSE_VALUE = get_response(Data_tmp->CURRMODE);

	if(CV_MODE==Memory_Ptr->MODE)
		Memory_Range = Data_tmp->VRange;
	else
		Memory_Range = Data_tmp->IRange;

	if( ptr->STADYNA)
		val = &ptr->DYNA[Memory_Range].LEVEL1;
	else
		val = &ptr->STA[Memory_Range].VALUE1;

	for(i=0 ; i<14 ; i++)
		*(mem++) = *(val++);
}

extern void Show_Mem_Recall_Message(UBYTE Mem_Mode,UBYTE Mem_Range,UWORD Mem_Data,char mode);

#define CV_Response_fast						0x0000	/*Bit 00~01*/
#define CV_Response_normal						0x0002	/*Bit 00~01*/
#define CV_Response_slow						0x0001	/*Bit 00~01*/

#define CP_Response_fast						0x0000	/*Bit 02~03*/
#define CP_Response_normal						0x0008	/*Bit 02~03*/
#define CP_Response_slow						0x0004	/*Bit 02~03*/

#define CXCV_Response_fast						0x0000	/*Bit 04*/
#define CXCV_Response_slow						0x0010	/*Bit 04*/

UBYTE Recall2Mem(char mode, UWORD no)
{
	int i;
	UBYTE *Status_Val[7],Memory_Range;
	p3k_mode_str *ptr;
	UWORD *sval,*m_sval,RespValue;

	P3k_Memory_Str	*Memory_Ptr;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	if(SR_PRESET_MODE==mode)
		Memory_Ptr = &Data_tmp->P_DATA[no];	/* Preset */
	else if(SR_MEMORY_MODE==mode)
		Memory_Ptr = &Data_tmp->M_DATA[no];	/* Memory */

	if( (Data_tmp->CONF.Memory_Recall==0)&&((CtrlFlag1&(P_Recall_Flag+M_Recall_Flag))==0) ) {
		if(SR_PRESET_MODE==mode)
			CtrlFlag1 |= P_Recall_Flag;
		else if(SR_MEMORY_MODE==mode)
			CtrlFlag1 |= M_Recall_Flag;

		if(Memory_Ptr->MODE==CV_MODE) {
			if(Memory_Ptr->STATUS&0x40)
				Show_Mem_Recall_Message(Memory_Ptr->MODE,VRange_High,Memory_Ptr->VALUE1,mode);
			else
				Show_Mem_Recall_Message(Memory_Ptr->MODE,VRange_Low,Memory_Ptr->VALUE1,mode);
		} else
			Show_Mem_Recall_Message(Memory_Ptr->MODE,Memory_Ptr->IRange,Memory_Ptr->VALUE1,mode);

		return 0;
	}

	Data_tmp->CURRMODE	= Memory_Ptr->MODE;
	RespValue = Memory_Ptr->RESPONSE_VALUE;

	if(CC_MODE==Data_tmp->CURRMODE)
		ptr = &Data_tmp->CC;
	else if(CR_MODE==Data_tmp->CURRMODE)
		ptr = &Data_tmp->CR;
	else if(CV_MODE==Data_tmp->CURRMODE)
		ptr = &Data_tmp->CV;
	else
		ptr = &Data_tmp->CP;

	Status_Val[0] = &Data_tmp->CONF.CV_Func_En;
	Status_Val[1] = &ptr->STADYNA;
	Status_Val[2] = &Data_tmp->SPEC;
	Status_Val[3] = &Data_tmp->SPECTYPE;
	Status_Val[4] = &ptr->ABSELECT;
	Status_Val[5] = &ptr->RESPONSE;
	Status_Val[6] = &Data_tmp->VRange;
#if 1
	if(CC_MODE==Data_tmp->CURRMODE) {
		//cxcv_cc
		if(RespValue&CXCV_Response_slow) Data_tmp->CC.CXCV_RESPOSNE =CXCV_ResponseSlow;
		else Data_tmp->CC.CXCV_RESPOSNE =CXCV_ResponseFast;
	} else if(CR_MODE==Data_tmp->CURRMODE) {
		if(RespValue&CXCV_Response_slow) Data_tmp->CR.CXCV_RESPOSNE =CXCV_ResponseSlow;
		else Data_tmp->CR.CXCV_RESPOSNE =CXCV_ResponseFast;
	} else if(CV_MODE==Data_tmp->CURRMODE) {
		//cv
		if((RespValue&0x03)==CV_Response_slow) Data_tmp->CV.RESPONSE = CVCP_ResponseSlow;
		else if((RespValue&0x03)==CV_Response_normal)Data_tmp->CV.RESPONSE = CVCP_ResponseNormal;
		else Data_tmp->CV.RESPONSE = CVCP_ResponseFast;
	} else {

		if(RespValue&CXCV_Response_slow) Data_tmp->CP.CXCV_RESPOSNE =CXCV_ResponseSlow;
		else Data_tmp->CP.CXCV_RESPOSNE =CXCV_ResponseFast;
		if((RespValue&0x0C)==CP_Response_slow) Data_tmp->CP.RESPONSE = CVCP_ResponseSlow;
		else if((RespValue&0x0C)==CP_Response_normal)Data_tmp->CP.RESPONSE = CVCP_ResponseNormal;
		else Data_tmp->CP.RESPONSE = CVCP_ResponseFast;
	}
#endif

	Data_tmp->IRange	= Memory_Ptr->IRange;
	Data_tmp->P_F_Delay = Memory_Ptr->P_F_Delay;
	m_sval				=&Memory_Ptr->VALUE1;

	for(i=0 ; i<7 ; i++) {
		if( Memory_Ptr->STATUS&(0x01<<i) )
			*Status_Val[i] = 1;
		else
			*Status_Val[i] = 0;
	}

	if(Data_tmp->CURRMODE!=CV_MODE)
		Data_tmp->CV.STA[Data_tmp->VRange].VALUE1 = Memory_Ptr->CV_VALUE;

	if(CV_MODE==Memory_Ptr->MODE)
		Memory_Range = Data_tmp->VRange;
	else
		Memory_Range = Data_tmp->IRange;

	if( ptr->STADYNA)
		sval  = &ptr->DYNA[Memory_Range].LEVEL1;
	else
		sval  = &ptr->STA[Memory_Range].VALUE1;

	for(i=0 ; i<14 ; i++)
		*(sval++) = *(m_sval++);

	return 1;
}

void Recall2Display(void)
{
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	Disp_tmp->CURRMODE = Data_tmp->CURRMODE;
	switch(Data_tmp->CURRMODE) {
	case CC_MODE:
		Disp_tmp->CC = Data_tmp->CC;
		M_num = P_CC;
		break;
	case CR_MODE:
		Disp_tmp->CR = Data_tmp->CR;
		M_num = P_CR;
		break;
	case CV_MODE:
		Disp_tmp->CV = Data_tmp->CV;
		M_num = P_CV;
		break;
	case CP_MODE:
		Disp_tmp->CP = Data_tmp->CP;
		M_num = P_CP;
		break;
	}
	Disp_tmp->IRange	= Data_tmp->IRange;
	Disp_tmp->VRange	= Data_tmp->VRange;
	Disp_tmp->SPEC		= Data_tmp->SPEC;
	Disp_tmp->SPECTYPE	= Data_tmp->SPECTYPE;
	Disp_tmp->P_F_Delay	= Data_tmp->P_F_Delay;
	Disp_tmp->CONF.CV_Func_En = Data_tmp->CONF.CV_Func_En;
	Disp_tmp->CV.STA[Disp_tmp->VRange].VALUE1 = Data_tmp->CV.STA[Data_tmp->VRange].VALUE1;
}

void Rem_Load_Cal_Default(void) /*Load Cal Default*/
{
	/*	  CC		  CR		  CV		  CP		CX CV	F_IMON	  R_IMON	    Ext_V_CC	 Ext_R_CC*/
	//UWORD Default_Cal_DA_Value[MODE_Number]={28300,	24320,	31300,	15300,	28300,	15000,	 10220,	  30660,	 30660};
//	UWORD Default_Cal_DA_Value[MODE_Number]= {28300,	24320,	28200,	27800,	28300,	15000,	 13000,	  30660,	 30660};
	UWORD Cal_DA_Def_31[MODE_Number]= {30700,	26000,	28700,	27800,	30700,	0,	 11500,	  33000,	 33000};
	UWORD Cal_DA_Def_32[MODE_Number]= {30500,	19200,	46500,	30600,	30600,	0,	 11200,	  33800,	 33800};
	char val;
	p3k_send_tx_list tx_data;
	UBYTE Mode,Rang;
	P3K_CALIBRATION_BAR.START			= 0x1;
	P3K_CALIBRATION_BAR.Volt_Curr_Sel	= Select_Volt;
	CAL_HI_LOW_SET_OK = 0;
	Mode = P3K_CALIBRATION_BAR.MODE;
	Rang = P3K_CALIBRATION_BAR.RANGE;
	val = Mode+(Rang*MODE_Number);
//read H-point, L-point Value
	P3K_CALIBRATION_BAR.HP_Volt = ((double)(ptrMODEL_TYPE->CALI_HP)[val].Def) * ((ptrMODEL_TYPE->CALI_HP)[val].Resolution);
	P3K_CALIBRATION_BAR.LP_Volt = ((double)(ptrMODEL_TYPE->CALI_LP)[val].Def) * ((ptrMODEL_TYPE->CALI_LP)[val].Resolution);
	if((Mode==CR_MODE)||(Mode==CP_MODE)||(Mode==R_IMON_MODE)) {
		if(Mode==CP_MODE) {
			P3K_CALIBRATION_BAR.HP_Curr = ((double)(ptrMODEL_TYPE->CALI_HP)[Rang*MODE_Number].Min)*((ptrMODEL_TYPE->CALI_HP)[Rang*MODE_Number].Resolution);
			P3K_CALIBRATION_BAR.LP_Curr = ((double)(ptrMODEL_TYPE->CALI_LP)[Rang*MODE_Number].Min)*((ptrMODEL_TYPE->CALI_LP)[Rang*MODE_Number].Resolution);
		} else if(Mode==R_IMON_MODE){
			P3K_CALIBRATION_BAR.HP_Curr = ((double)(ptrMODEL_TYPE->CALI_HP)[Rang*MODE_Number].Max)*((ptrMODEL_TYPE->CALI_HP)[Rang*MODE_Number].Resolution);
			P3K_CALIBRATION_BAR.LP_Curr = ((double)(ptrMODEL_TYPE->CALI_LP)[Rang*MODE_Number].Max)*((ptrMODEL_TYPE->CALI_LP)[Rang*MODE_Number].Resolution);
		} else {
			P3K_CALIBRATION_BAR.HP_Curr = ((double)(ptrMODEL_TYPE->CALI_HP)[Rang*MODE_Number+7].Max)*((ptrMODEL_TYPE->CALI_HP)[Rang*MODE_Number+7].Resolution);
			P3K_CALIBRATION_BAR.LP_Curr = ((double)(ptrMODEL_TYPE->CALI_LP)[Rang*MODE_Number+7].Max)*((ptrMODEL_TYPE->CALI_LP)[Rang*MODE_Number+7].Resolution);
		}
	}
	if(Model_Number==MODEL3031E)
		P3K_CALIBRATION_BAR.Set_Value_High	= Cal_DA_Def_31[Mode];
	else
		P3K_CALIBRATION_BAR.Set_Value_High	= Cal_DA_Def_32[Mode];

	if(Mode==CR_MODE){	//CR HRange{24320,300}
		if(Model_Number==MODEL3031E) 	P3K_CALIBRATION_BAR.Set_Value_Low	= 320;
		else							P3K_CALIBRATION_BAR.Set_Value_Low	= 240;
		if(Rang==LOW_RANGE){ //CR LRange{2432,30}
			P3K_CALIBRATION_BAR.Set_Value_High/= 10;
			P3K_CALIBRATION_BAR.Set_Value_Low /= 10;
		}
	} else if(Mode>=F_IMON_MODE)//IMON, EXE_V,EXE_R:  (H = L)
		P3K_CALIBRATION_BAR.Set_Value_Low = P3K_CALIBRATION_BAR.Set_Value_High;
	else //CC,CV,CP,CXCV (L = H/10)
		P3K_CALIBRATION_BAR.Set_Value_Low = P3K_CALIBRATION_BAR.Set_Value_High/10;	

	P3K_CALIBRATION_BAR.CxCV = Default_Cal_CXCV;
	P3K_CALIBRATION_BAR.Monitor_High	= 65535;
	P3K_CALIBRATION_BAR.Monitor_Low		= 65535;

	tx_data.ADDRH = Cal_FPGA_Command;
	tx_data.ADDRL = Cal_FPGA_Load_Cal_Default;
	SendTXData(&tx_data);
}

BYTE Cal_Func(BYTE chnum, BYTE x)
{
	char val;
	switch(x) {
	case F1_KEY:		/* Calibration mode */

		val = P3K_CALIBRATION_BAR.MODE;
		val++;
		if(val>=MODE_Number)			val = CC_MODE;
		else if(val==F_IMON_MODE)	val = R_IMON_MODE ;

		P3K_CALIBRATION_BAR.MODE = val;
		if(P3K_CALIBRATION_BAR.Cal_PSense_Flag==0) {
			if(CP_MODE==P3K_CALIBRATION_BAR.MODE)
				P3K_CALIBRATION_BAR.PSense = 1;
			else
				P3K_CALIBRATION_BAR.PSense = 0;
		}

		p3k_Cal_data.OffsetFlag = 0;

		if(CC_MODE==P3K_CALIBRATION_BAR.MODE)
			p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.CC_offseAdj[P3K_CALIBRATION_BAR.RANGE];
		else if(CR_MODE==P3K_CALIBRATION_BAR.MODE)
			p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.CR_offseAdj[P3K_CALIBRATION_BAR.RANGE];
		else if(CP_MODE==P3K_CALIBRATION_BAR.MODE)
			p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.CP_offseAdj[P3K_CALIBRATION_BAR.RANGE];
		else if(CV_MODE==P3K_CALIBRATION_BAR.MODE)
			p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.CV_offseAdj[P3K_CALIBRATION_BAR.RANGE];
#if 1//Enable_Ext_CalOffset
		else if (P3K_CALIBRATION_BAR.MODE==Ext_V_CC_MODE)
			p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.Ext_V_offseAdj[P3K_CALIBRATION_BAR.RANGE];
		else if (P3K_CALIBRATION_BAR.MODE==Ext_R_CC_MODE)
			p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.Ext_R_offseAdj[P3K_CALIBRATION_BAR.RANGE];		
		else
			p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.CC_offseAdj[P3K_CALIBRATION_BAR.RANGE];
		
#else
		else if (P3K_CALIBRATION_BAR.MODE==Ext_V_CC_MODE) {
			if(P3K_CALIBRATION_BAR.RANGE)	p3k_Cal_data.OffsetAdjCnt1 = FPGA_W[253];
			else							p3k_Cal_data.OffsetAdjCnt1 = FPGA_W[252];
			if(p3k_Cal_data.OffsetAdjCnt1)	p3k_Cal_data.OffsetAdjCnt1=30000;
		} else if (P3K_CALIBRATION_BAR.MODE==Ext_R_CC_MODE) {
			if(P3K_CALIBRATION_BAR.RANGE)	p3k_Cal_data.OffsetAdjCnt1 = FPGA_W[253];
			else							p3k_Cal_data.OffsetAdjCnt1 = FPGA_W[252];
			if(p3k_Cal_data.OffsetAdjCnt1)	p3k_Cal_data.OffsetAdjCnt1=30000;
		}
#endif
		MenuRedrawFlag |= MENU1_CHANGE + MENU3_CHANGE + MENU4_CHANGE ;
		break;
	case F2_KEY:		/* Calibration range */
		val = P3K_CALIBRATION_BAR.RANGE;
		val--;
		if(val<LOW_RANGE)	val=HIGH_RANGE;
		P3K_CALIBRATION_BAR.RANGE = val;

		p3k_Cal_data.OffsetFlag = 0;
		if(CC_MODE==P3K_CALIBRATION_BAR.MODE)
			p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.CC_offseAdj[P3K_CALIBRATION_BAR.RANGE];
		else if(CR_MODE==P3K_CALIBRATION_BAR.MODE)
			p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.CR_offseAdj[P3K_CALIBRATION_BAR.RANGE];
		else if(CP_MODE==P3K_CALIBRATION_BAR.MODE)
			p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.CP_offseAdj[P3K_CALIBRATION_BAR.RANGE];
		else if(CV_MODE==P3K_CALIBRATION_BAR.MODE)
			p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.CV_offseAdj[P3K_CALIBRATION_BAR.RANGE];
#if 1//Enable_Ext_CalOffset
		else if (P3K_CALIBRATION_BAR.MODE==Ext_V_CC_MODE)
			p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.Ext_V_offseAdj[P3K_CALIBRATION_BAR.RANGE];
		else if (P3K_CALIBRATION_BAR.MODE==Ext_R_CC_MODE)
			p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.Ext_R_offseAdj[P3K_CALIBRATION_BAR.RANGE];		
		else
			p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.CC_offseAdj[P3K_CALIBRATION_BAR.RANGE];
		
#else
		else if (P3K_CALIBRATION_BAR.MODE==Ext_V_CC_MODE) {
			if(P3K_CALIBRATION_BAR.RANGE)	p3k_Cal_data.OffsetAdjCnt1 = FPGA_W[253];
			else							p3k_Cal_data.OffsetAdjCnt1 = FPGA_W[252];
			if(p3k_Cal_data.OffsetAdjCnt1)	p3k_Cal_data.OffsetAdjCnt1=30000;
		} else if (P3K_CALIBRATION_BAR.MODE==Ext_R_CC_MODE) {
			if(P3K_CALIBRATION_BAR.RANGE)	p3k_Cal_data.OffsetAdjCnt1 = FPGA_W[253];
			else							p3k_Cal_data.OffsetAdjCnt1 = FPGA_W[252];
			if(p3k_Cal_data.OffsetAdjCnt1)	p3k_Cal_data.OffsetAdjCnt1=30000;
		}
#endif
		MenuRedrawFlag |= MENU2_CHANGE+MENU4_CHANGE;
		break;
	default:
		break;
	}
	Rem_Load_Cal_Default();

	DispMode	= DispMode_SELECT_CH;
	DispCT	= 0;
	DataRedrawFlag |= PARA_CHANGE;

	return(0);
}
void Rem_CalPSense(void)
{
	p3k_send_tx_list tx_data;

	P3K_CALIBRATION_BAR.PSense = 0;
	P3K_CALIBRATION_BAR.Cal_PSense_Flag = 1;

	tx_data.ADDRH = Cal_FPGA_Command;
	tx_data.ADDRL = Cal_FPGA_PSensor_H;
	SendTXData(&tx_data);

	SaveCalData_DataFlash();
#if 0
		Acess_FPGA(FPGA_XH_OS_Ref, P3K_CALIBRATION_BAR.PSensor.XH_Value);
		Acess_FPGA(FPGA_YH_OS_Ref, P3K_CALIBRATION_BAR.PSensor.YH_Value);
		Acess_FPGA(FPGA_ZH_OS_Ref, P3K_CALIBRATION_BAR.PSensor.ZH_Value);
		Acess_FPGA(FPGA_XL_OS_Ref, P3K_CALIBRATION_BAR.PSensor.XH_Value);
		Acess_FPGA(FPGA_YL_OS_Ref, P3K_CALIBRATION_BAR.PSensor.YH_Value);
		Acess_FPGA(FPGA_ZL_OS_Ref, P3K_CALIBRATION_BAR.PSensor.ZH_Value);
#endif		
}
BYTE Cal_PSense(BYTE chnum, BYTE x)
{
	p3k_send_tx_list tx_data;

	if(P3K_CALIBRATION_BAR.PSense) {
		Soft_Key_Temp = 0;
		CtrlFlag1 |= Cal_Wait_moment;
		MenuRedrawFlag |= MENU3_CHANGE;

		ShowCalMessage();
		Rem_CalPSense();
		//Show_XYZ_Window();

		if(P3K_CALIBRATION_BAR.RANGE!=IRange_Low) {	/*IF Cal Mode is CPH,Cal Mode need change CPL*/
			tx_data.ADDRH = Cal_FPGA_Command;
			tx_data.ADDRL = Cal_FPGA_Load_Cal_Default;
			SendTXData(&tx_data);
		}
	}
	return(0);
}



	



void Rem_Save_Cal_Data(void)
{
	double Gain_Result;
	double Set_High_Point,Set_Low_Point;
	double Setting_Resolution = 1.0;
	UBYTE val,mode,range;
	p3k_send_tx_list tx_data;
	UWORD Cal_Save_Data,Ext_Cal_Temp1,Ext_Cal_Temp2;
	float Full_Scale_Voltage,Full_Scale_Current,I_Real_IMON_Voltage,I_Real_SR_CNT;
	float I_Real_Full_Scale_Voltage;
	UWORD 					*Ext_Cal_Data	= NULL;
	P3k_Disp_Str			*Disp_tmp 		= &P3k_Disp_Data;
	P3k_Data_Str			*Data_tmp 		= &P3k_Chan_Data;
	Cal_Data_str			*Cal_Set_Data	= NULL;
	p3k_Meas_cal_Data_str 	*Cal_Meas_Data	= NULL;
	p3k_Meas_cal_Data_str 	*Cal_Meas_Data_V	= NULL;
	p3k_Meas_cal_Data_str 	*Cal_Meas_Data_R	= NULL;

	p3k_Prot_cal_Data_str	*Protection_Cal	= NULL;
	
	mode = P3K_CALIBRATION_BAR.MODE;
	range = P3K_CALIBRATION_BAR.RANGE;	
	val = mode +(range*MODE_Number);
	CAL_HI_LOW_SET_OK = 0;
	P3K_CALIBRATION_BAR.START = 1;
	P3K_CALIBRATION_BAR.Cal_Value_Gain		= 1;
	P3K_CALIBRATION_BAR.Cal_Value_Offset	= 0;
	

	if(CC_MODE==mode)
		p3k_Cal_data.CC_offseAdj[range] = p3k_Cal_data.OffsetAdjCnt1;
	else if(CR_MODE==mode)
		p3k_Cal_data.CR_offseAdj[range] = p3k_Cal_data.OffsetAdjCnt1;
	else if(CP_MODE==mode)
		p3k_Cal_data.CP_offseAdj[range] = p3k_Cal_data.OffsetAdjCnt1;
#if Enable_Ext_CalOffset
	else if(Ext_V_CC_MODE==mode)
		p3k_Cal_data.Ext_V_offseAdj[range] = p3k_Cal_data.OffsetAdjCnt1;
	else if(Ext_R_CC_MODE==mode)
		p3k_Cal_data.Ext_R_offseAdj[range] = p3k_Cal_data.OffsetAdjCnt1;
#endif
	if(mode==CR_MODE) {
		Setting_Resolution	= (ptrMODEL_TYPE->CR)[(range*10)].Resolution/1000.0;
		Set_High_Point		= (P3K_CALIBRATION_BAR.HP_Curr/P3K_CALIBRATION_BAR.HP_Volt)/Setting_Resolution;
		Set_Low_Point		= (P3K_CALIBRATION_BAR.LP_Curr/P3K_CALIBRATION_BAR.LP_Volt)/Setting_Resolution;
	} else if(mode==CP_MODE) {
		Setting_Resolution	= (ptrMODEL_TYPE->CP)[(range*10)].Resolution;
		Set_High_Point		= (P3K_CALIBRATION_BAR.HP_Volt*P3K_CALIBRATION_BAR.HP_Curr)/Setting_Resolution;
		Set_Low_Point		= (P3K_CALIBRATION_BAR.LP_Volt*P3K_CALIBRATION_BAR.LP_Curr)/Setting_Resolution;
	} else if(mode==CV_MODE) { 
		Setting_Resolution	= (ptrMODEL_TYPE->CALI_HP)[val].Resolution;
		Set_High_Point		= P3K_CALIBRATION_BAR.HP_Volt/Setting_Resolution;
		Set_Low_Point		= P3K_CALIBRATION_BAR.LP_Volt/Setting_Resolution;
	} else { 
		Setting_Resolution	= (ptrMODEL_TYPE->CALI_HP)[val].Resolution;
		Set_High_Point		= P3K_CALIBRATION_BAR.HP_Volt/Setting_Resolution;
		Set_Low_Point		= P3K_CALIBRATION_BAR.LP_Volt/Setting_Resolution;
	}

	if((mode==CC_MODE)||(mode==CxCV_MODE)) {
		Cal_Set_Data	= &p3k_Cal_data.CC_Data[range];
		Cal_Meas_Data	= &p3k_Cal_data.Curr[range];

		if(mode==CC_MODE){
			Cal_Meas_Data_V = &p3k_Cal_data.Ext_V_Curr[range];
			Cal_Meas_Data_R = &p3k_Cal_data.Ext_R_Curr[range];
		}
		
	} else if(mode==CR_MODE)
		Cal_Set_Data 	= &p3k_Cal_data.CR_Data[range];
	else if(mode==CV_MODE) {
		if(VRange_Low==range) {
			Cal_Set_Data	= &p3k_Cal_data.CV_Data[VRange_Low];
			Cal_Meas_Data	= &p3k_Cal_data.Volt[VRange_Low];		
		} else {
			Cal_Set_Data	= &p3k_Cal_data.CV_Data[VRange_High];
			Cal_Meas_Data	= &p3k_Cal_data.Volt[VRange_High];
		}

		Cal_Meas_Data_V = &p3k_Cal_data.Ext_V_Volt[range];
		Cal_Meas_Data_R = &p3k_Cal_data.Ext_R_Volt[range];
	
	} else if(mode==CP_MODE)
		Cal_Set_Data	= &p3k_Cal_data.CP_Data[range];
	else if(mode==Ext_V_CC_MODE) {
		Cal_Meas_Data	= &p3k_Cal_data.Ext_V_Sense;
		Ext_Cal_Data	= &p3k_Cal_data.Ext_V_CC[range];
	} else if(mode==Ext_R_CC_MODE) {
		Cal_Meas_Data	= &p3k_Cal_data.Ext_R_Sense;
		Ext_Cal_Data	= &p3k_Cal_data.Ext_R_CC[range];
	} else if( (mode==F_IMON_MODE)||(mode==R_IMON_MODE) ) {
		Cal_Set_Data	= &p3k_Cal_data.CC_Data[range];
		Cal_Meas_Data	= &p3k_Cal_data.Curr[range];
	} else {
		Cal_Set_Data	= &p3k_Cal_data.CC_Data[range];
		Cal_Meas_Data	= &p3k_Cal_data.Curr[range];
		Debug_printf("Cal_Save Error\n");
	}

	if(mode<=CP_MODE) {
		P3K_CALIBRATION_BAR.Cal_Value_Gain		= ((double)(P3K_CALIBRATION_BAR.Set_Value_High-P3K_CALIBRATION_BAR.Set_Value_Low))/(Set_High_Point-Set_Low_Point);
		P3K_CALIBRATION_BAR.Cal_Value_Offset	= (double)P3K_CALIBRATION_BAR.Set_Value_High-(Set_High_Point*P3K_CALIBRATION_BAR.Cal_Value_Gain);

		if(P3K_CALIBRATION_BAR.Cal_Value_Offset < 0) {
			Menu_Message(" CX Mode Offset Error!! ",50,210);
			CtrlFlag1 |= Disp_Middle_Message;
			DMA_Update_Flag = 1;
			Update_Panel();
			OSTimeDly(200);
		}
		Cal_Set_Data->Cal_Value_Gain	= P3K_CALIBRATION_BAR.Cal_Value_Gain;
		Cal_Set_Data->Cal_Value_Offset	= P3K_CALIBRATION_BAR.Cal_Value_Offset;
	}

	if( (Ext_V_CC_MODE==mode)||(Ext_R_CC_MODE==mode) ){
		/* External Control */
		Ext_Cal_Temp1 = (ptrMODEL_TYPE->CALI_HP)[val].Min / Set_High_Point * P3K_CALIBRATION_BAR.Set_Value_High; ///check ok
		Ext_Cal_Temp2 = ((ptrMODEL_TYPE->CALI_HP)[val].Min/10.0) / Set_Low_Point * P3K_CALIBRATION_BAR.Set_Value_Low; ///check ok
		*Ext_Cal_Data = Ext_Cal_Temp1;

		/* External Meas */
		//Gain_Result = ((double)(40000.0 - 4000.0)/(double)(P3K_CALIBRATION_BAR.Monitor_High - P3K_CALIBRATION_BAR.Monitor_Low));
		Gain_Result = ((double)(Monitor_H - Monitor_L)/(double)(P3K_CALIBRATION_BAR.Monitor_High - P3K_CALIBRATION_BAR.Monitor_Low));
		if( (P3K_CALIBRATION_BAR.Monitor_High*Gain_Result)<Monitor_H ) {
			Cal_Offset_Error |= Meas_Err;
			Cal_Meas_Data->Meas_Value_Offset = 0;
		} else
			Cal_Meas_Data->Meas_Value_Offset = (P3K_CALIBRATION_BAR.Monitor_High*Gain_Result) - Monitor_H;
		Cal_Meas_Data->Meas_Value_Gain = Gain_Result * 65535.0;
	}
	Cal_Offset_Error = 0;
	if( (mode==CC_MODE)||(mode==CV_MODE) ) {
		if(mode==CV_MODE) {
			Setting_Resolution	= (ptrMODEL_TYPE->CALI_HP)[val].Resolution;///check ok
			if(Model_Number==MODEL3031E)Setting_Resolution	*= MEASURE_GAIN_3031;///check ok
			else						Setting_Resolution	*= MEASURE_GAIN_3032;///check ok
			Set_High_Point		= P3K_CALIBRATION_BAR.HP_Volt/Setting_Resolution;
			Set_Low_Point		= P3K_CALIBRATION_BAR.LP_Volt/Setting_Resolution;
			Gain_Result = ((double)(Set_High_Point - Set_Low_Point)/(double)(P3K_CALIBRATION_BAR.Monitor_High - P3K_CALIBRATION_BAR.Monitor_Low));
		} else {
			Gain_Result = ((double)(Set_High_Point - Set_Low_Point)/(double)(P3K_CALIBRATION_BAR.Monitor_High - P3K_CALIBRATION_BAR.Monitor_Low));
		}


		if((Set_High_Point / Gain_Result) > P3K_CALIBRATION_BAR.Monitor_High) {
			Cal_Offset_Error |= Meas_Err;
			Cal_Meas_Data->Meas_Value_Offset = 0;
		} else
			Cal_Meas_Data->Meas_Value_Offset = P3K_CALIBRATION_BAR.Monitor_High - (Set_High_Point / Gain_Result);

		Cal_Meas_Data->Meas_Value_Gain = (UWORD)(Gain_Result * (double)65535.0);


		//Ext_V
		Gain_Result = ((double)(Set_High_Point - Set_Low_Point)/(double)(Monitor_ExtV_H - Monitor_ExtV_L));
		Cal_Meas_Data_V->Meas_Value_Offset = Monitor_ExtV_H - (Set_High_Point / Gain_Result);
		Cal_Meas_Data_V->Meas_Value_Gain = (UWORD)(Gain_Result * (double)65535.0);		
		//Ext_R
		Gain_Result = ((double)(Set_High_Point - Set_Low_Point)/(double)(Monitor_ExtR_H - Monitor_ExtR_L));
		Cal_Meas_Data_R->Meas_Value_Offset = Monitor_ExtR_H - (Set_High_Point / Gain_Result);
		Cal_Meas_Data_R->Meas_Value_Gain = (UWORD)(Gain_Result * (double)65535.0);	


		tx_data.ADDRH = Cal_FPGA_Command;
		tx_data.ADDRL = Cal_FPGA_Load_Meas_Default;
		SendTXData(&tx_data);

		P3K_CALIBRATION_BAR.Monitor_High	= Cal_Meas_Data->Meas_Value_Gain;
		P3K_CALIBRATION_BAR.Monitor_Low		= Cal_Meas_Data->Meas_Value_Offset;
		DataRedrawFlag |= PARA_CHANGE ;
	}
	tx_data.ADDRH = Cal_FPGA_Command;
	tx_data.ADDRL = Cal_FPGA_Prot;
	SendTXData(&tx_data);

	Protection_Cal = &p3k_Cal_data.Protection[range];
	if((mode==CC_MODE)&&(range==HIGH_RANGE)) {
		/*OCP*/
		Protection_Cal->OCP_Gain			= P3K_CALIBRATION_BAR.OCP_Gain;
		Protection_Cal->OCP_Offset		= P3K_CALIBRATION_BAR.OCP_Offset;
		p3k_Cal_data.Protection[LOW_RANGE].OCP_Gain 			= p3k_Cal_data.Protection[HIGH_RANGE].OCP_Gain;
		p3k_Cal_data.Protection[LOW_RANGE].OCP_Offset		= p3k_Cal_data.Protection[HIGH_RANGE].OCP_Offset;
		p3k_Cal_data.Protection[HIGH_RANGE].OCP = Step_To_CNT(Data_tmp->PROT.OCP[HIGH_RANGE],P3K_CALIBRATION_BAR.OCP_Gain,P3K_CALIBRATION_BAR.OCP_Offset);
		p3k_Cal_data.Protection[LOW_RANGE].OCP  = p3k_Cal_data.Protection[HIGH_RANGE].OCP;
	}

	if((mode==CP_MODE)&&(range==HIGH_RANGE)) {
		Protection_Cal->OPP_Gain	= P3K_CALIBRATION_BAR.OPP_Gain;
		Protection_Cal->OPP_Offset	= P3K_CALIBRATION_BAR.OPP_Offset;
		Protection_Cal->CPP_Gain	= 1;//P3K_CALIBRATION_BAR.CPP_Gain;
		Protection_Cal->CPP_Offset	= 0;//P3K_CALIBRATION_BAR.CPP_Offset;

		Protection_Cal->OPP = Step_To_CNT(Data_tmp->PROT.OPP[HIGH_RANGE],P3K_CALIBRATION_BAR.OPP_Gain,P3K_CALIBRATION_BAR.OPP_Offset);
		Protection_Cal->CPP = Step_To_CNT(((ptrMODEL_TYPE->PROT)[PROT_OPP_H].Max/21*22),P3K_CALIBRATION_BAR.OPP_Gain,P3K_CALIBRATION_BAR.OPP_Offset);

		p3k_Cal_data.Protection[LOW_RANGE].OPP_Gain		= p3k_Cal_data.Protection[HIGH_RANGE].OPP_Gain;
		p3k_Cal_data.Protection[LOW_RANGE].OPP_Offset	= p3k_Cal_data.Protection[HIGH_RANGE].OPP_Offset;
		p3k_Cal_data.Protection[LOW_RANGE].OPP			= p3k_Cal_data.Protection[HIGH_RANGE].OPP;
		p3k_Cal_data.Protection[LOW_RANGE].CPP_Gain		= p3k_Cal_data.Protection[HIGH_RANGE].CPP_Gain;
		p3k_Cal_data.Protection[LOW_RANGE].CPP_Offset	= p3k_Cal_data.Protection[HIGH_RANGE].CPP_Offset;
		//p3k_Cal_data.Protection[HIGH_RANGE].CPP = p3k_Cal_data.Protection[LOW_RANGE].OPP/21*22;
		p3k_Cal_data.Protection[LOW_RANGE].CPP			= p3k_Cal_data.Protection[HIGH_RANGE].CPP;
	}

	if(mode == CxCV_MODE) {
		Protection_Cal->CxCV_Gain	= P3K_CALIBRATION_BAR.CxCV_Gain;
		Protection_Cal->CxCV_Offset	= P3K_CALIBRATION_BAR.CxCV_Offset;
		Protection_Cal->CxCV	 = P3K_CALIBRATION_BAR.CxCV;
	}

	if(mode==R_IMON_MODE) {
		if(range)
			Full_Scale_Voltage = 10.0;
		else
			Full_Scale_Voltage = 1.0;

		Full_Scale_Current	= (ptrMODEL_TYPE->CALI_HP)[range*MODE_Number+Ext_V_CC_MODE].Min * (ptrMODEL_TYPE->CALI_HP)[range*MODE_Number+Ext_V_CC_MODE].Resolution;///check ok
		//Full_Scale_Current	= (ptrMODEL_TYPE->CALI_HP)[P3K_CALIBRATION_BAR.RANGE*MODE_Number+R_IMON_MODE].Def * (ptrMODEL_TYPE->CALI_HP)[P3K_CALIBRATION_BAR.RANGE*MODE_Number+R_IMON_MODE].Resolution;
		I_Real_IMON_Voltage	= (Full_Scale_Voltage*P3K_CALIBRATION_BAR.HP_Curr)/Full_Scale_Current;
		I_Real_SR_CNT	= (P3K_CALIBRATION_BAR.LP_Volt-P3K_CALIBRATION_BAR.HP_Volt)/63.0;
		p3k_Cal_data.Rear_IMON[range] = (UBYTE)(((I_Real_IMON_Voltage - P3K_CALIBRATION_BAR.HP_Volt)/I_Real_SR_CNT)+0.5);

		if(p3k_Cal_data.Rear_IMON[range]>63) {
			p3k_Cal_data.Rear_IMON[range] = 63;
			Debug_printf(" Rear_IMON Cal Failed\n ");
			Menu_Message(" Rear_IMON Cal Failed!! ",50,210);
			CtrlFlag1 |= Disp_Middle_Message;
			DMA_Update_Flag = 1;
			Update_Panel();
			OSTimeDly(200);
		}
	}
	SaveCalData_DataFlash();
}

BYTE Cal_Save(BYTE chnum, BYTE x)
{
	if(P3K_CALIBRATION_BAR.START) {

	} else {
		CtrlFlag1	|= Cal_Wait_moment;
		Soft_Key_Temp = 0;
		DataRedrawFlag |= PARA_CHANGE;
		Rem_Save_Cal_Data();
		MenuRedrawFlag|=MENU4_CHANGE;
	}
	return(0);
}

void WriteFile(void *pData, unsigned long Size, char *FileName) /* FileName must less than eight */
{
	FS_FILE *Write_File;
	char temp_fname[maxdirlen];

	sprintf(temp_fname, "%s\\%s", FMnowPath, FileName);
	if( (Write_File=FS_FOpen(temp_fname,"wb"))==0) {
		Debug_printf("write file error\n");
	} else {
		if(FS_FWrite(pData, sizeof(char), Size, Write_File)==Size)
			FS_FClose(Write_File);
		else {
			FS_FClose(Write_File);
			Debug_printf("Writing Failed/n");
		}
	}
}
int FileNameConvert(int Name_Count, char *Name_str, char Mode)
{
	//Mode Sav_Set :  Save Setup File Name
	//Mode Sav_Memory: Save Memory File Name
	//Mode Sav_Preset:	Save Preset File Name
	char temp_str[6];
	unsigned char Master_Type[8];
	temp_str[0]=Name_Count /10 + '0';
	temp_str[1]=(Name_Count %10) + '0';
	temp_str[2]=0;

	if(P3k_Serial_Number.Version >= NF_Version) {
		if(P3k_Chan_Data.INFO.MACHTYPE==MODEL3031E)		sprintf((char *)Master_Type, "3031E");
		else if(P3k_Chan_Data.INFO.MACHTYPE==MODEL3032E)	sprintf((char *)Master_Type, "3032E");
		
	} else {
		if(P3k_Chan_Data.INFO.MACHTYPE==MODEL3031E)		sprintf((char *)Master_Type, "3031E");
		else if(P3k_Chan_Data.INFO.MACHTYPE==MODEL3032E)	sprintf((char *)Master_Type, "3032E");
		
	}

	if(Sav_Set==Mode)			sprintf(Name_str, "%s_%s%s", Master_Type, temp_str, ".S");
	else if(Sav_Memory==Mode)	sprintf(Name_str, "%s_%s%s", Master_Type, temp_str, ".M");
	else if(Sav_Preset==Mode)	sprintf(Name_str, "%s_%s%s", Master_Type, temp_str, ".P");
	else if(Sav_SEQ==Mode)		sprintf(Name_str, "%s_%s%s", Master_Type, temp_str, ".A");
	else if(Sav_NSeq==Mode)		sprintf(Name_str, "%s_%s%s", Master_Type, temp_str, ".N");
	else if(Sav_FSeq==Mode)		sprintf(Name_str, "%s_%s%s", Master_Type, temp_str, ".F");
	else if(Sav_Result==Mode)	sprintf(Name_str, "RESULT%s%s",	temp_str, ".CSV");
	return Name_Count;
}
int NextFileName(int FileCount, char *FileName, char Mode, char cnt)
{
	//Mode Sav_Set :		Save Setup File Name
	//Mode Sav_Memory:	Save Memory File Name
	//Mode Sav_Preset:	Save Preset File Name
	WORD Times=0;
	char  *Name_ptr;
	int  i;

	if(strcmp(FMnowPath, FMpredir)!=0)
		FileCount=0;
	FileNameConvert(FileCount, FileName, Mode);

	Times = FM.TotalFiles + 1;
	while(1) {
		while(Times) {
			if(! strcmp(FileName, FMfile[Times].my_name) ) //times + 1
				break;
			Times--;
		}
		if(Times==0) {
			break;
		} else {
			Times=FM.TotalFiles + 1;
			if(cnt<0)		FileCount--;
			else			FileCount++;

			if(FileCount<0)						FileCount = USBNumerTotal - 1;
			else if(FileCount>=USBNumerTotal)	FileCount = 0;
			FileNameConvert(FileCount, FileName, Mode);
		}
	}
	strcpy(FMpredir, FMnowPath);

	return FileCount;
}
char CheckSameFile(char *FileName)
{
	WORD Times=0;
	Times=FM.TotalFiles + 1;
	for(Times=0; Times<FM.TotalFiles + 1; Times++) {
		if(!strcmp(FileName, FMfile[Times].my_name) )
			return 1;
	}
	return 0;
}

void RecallFileNameFun(const char *name, char *FileName, char Mode, char cnt)
{
	//Mode Rec_Set  : Recall Setup File Name
	//Mode Rec_Wav : Recall Waveform File Name
	//Mode Rec_Img : Recall Image File Name
	//Mode pri_file    : Import Printer File Name

	WORD Times=0, counter, *counter_ptr;
	char *Name_ptr;
	char *Setup_str=".S";
	char *Wave_str=".P";
	char *Memory_str=".M";
	char *SEQ_str=".A";
	char *NSeq_str=".N";
	char *FSeq_str=".F";
	char *temp_str="  ";
	char *Rec_str;
	char *Null_str="No File";
	char str_cmp=0;
	int  i;

	if(Mode==Sav_Set) {
		counter_ptr = &RecSetupFileCount;
		strcpy(temp_str, Setup_str);
	} else if(Mode==Sav_Memory) {
		counter_ptr = &RecMemoryFileCount;
		strcpy(temp_str, Memory_str);
	} else if(Mode==Sav_Preset) {
		counter_ptr = &RecPresetFileCount;
		strcpy(temp_str, Wave_str);
	} else if(Mode==Sav_SEQ) {
		counter_ptr = &RecSEQFileCount;
		strcpy(temp_str, SEQ_str);
	} else if(Mode==Sav_NSeq) {
		counter_ptr = &RecNSeqFileCount;
		strcpy(temp_str, NSeq_str);
	} else if(Mode==Sav_FSeq) {
		counter_ptr = &RecFSeqFileCount;
		strcpy(temp_str, FSeq_str);
	}
	counter=*counter_ptr;
	Rec_str=temp_str;
	if(cnt>0) {
		counter++;
		if(counter> FM.TotalFiles)
			return;
	} else if(cnt<0) {
		counter--;
		//if(counter<FM.FolderVal+1)
		if(counter<0)
			return;
	}
	Times=FM.TotalFiles + 1;
	while(Times) {
		Name_ptr=FMfile[counter+1].my_name;
		while(*Name_ptr!=0)
			Name_ptr++;
		Name_ptr-=2;
		for(i=0; i<2; i++, Name_ptr++ , Rec_str++) {
			if( (*Name_ptr!=*Rec_str) && (*Name_ptr!=*Rec_str + 0x20) )
				str_cmp=1;
		}
		if(str_cmp==0) {
			strcpy(FileName, FMfile[counter+1].my_name);
			*counter_ptr=counter;
			break;
		}
		str_cmp=0;
		Times--;
		Rec_str=temp_str;
		if(cnt>0) {
			counter++;
			if(counter> FM.TotalFiles)
				break;
		} else {
			counter--;
			if(counter<0)
				break;
		}
	}
	if(Times==0)
		strcpy(FileName, Null_str);
}
long round_recall (double fdVal)
{
	if (fdVal > 0)	fdVal += 0.5;
	else			fdVal -= 0.5;
	return (long)fdVal;				/* Casting to long truncates the value to an integer */
}
extern void SaveRecall_Prog_Data(BYTE dire);
extern void SaveRecall_Setup_Data(BYTE dire);
extern void SaveRecall_Preset_Data(BYTE dire);
extern void SaveRecall_NSeq_Data(BYTE dire);
extern void SaveRecall_FSeq_Data(BYTE dire);
extern ULONG DataCheckSum(unsigned char *dest,long size);
UBYTE RecallFSeqDataFromSCPI(UBYTE *Data_Address_Ptr)
{
	P3k_Backup_FSeq_Data_Temp = P3k_Backup_FSeq_Data;
#if 1
	memcpy((UBYTE *)&P3k_Backup_FSeq_Data,Data_Address_Ptr,sizeof(P3k_Backup_FSeq_Data));
	if( (P3k_Backup_FSeq_Data.CheckSum==DataCheckSum((UBYTE *)&P3k_Backup_FSeq_Data,sizeof(P3k_Backup_FSeq_Data)))&&(P3k_Backup_FSeq_Data.CheckSum) ) {
		if( P3k_Backup_FSeq_Data.MACHTYPE!=P3k_Chan_Data.INFO.MACHTYPE ) {
			P3k_Backup_FSeq_Data = P3k_Backup_FSeq_Data_Temp;
			return Machine_Type_Error;
		}
		if( P3k_Backup_FSeq_Data.F_Version>File_Version ) {
			P3k_Backup_FSeq_Data = P3k_Backup_FSeq_Data_Temp;
			return Memory_Version_Error;
		}
		SaveRecall_FSeq_Data(0);
		P3k_FSeq_Disp = P3k_FSeq_Data;
		BackupFSeq();
		return Recall_Complete;
	} else {
		P3k_Backup_FSeq_Data = P3k_Backup_FSeq_Data_Temp;
		return Recall_Failed;
	}
#else
	return 1;
#endif
}
UBYTE RecallCalSCPI(UBYTE *Data_Address_Ptr)
{
	if(1) { //(sizeof(p3k_Cal_data)==1024){
		memcpy((UBYTE *)&p3k_Cal_data,Data_Address_Ptr,sizeof(p3k_Cal_data));
		return Recall_Complete;
	} else {
		P3k_Backup_FSeq_Data = P3k_Backup_FSeq_Data_Temp;
		return Recall_Failed;
	}
}

UBYTE RecallNSeqDataFromSCPI(UBYTE *Data_Address_Ptr)
{
	P3k_Backup_NSeq_Data_Temp = P3k_Backup_NSeq_Data;
	memcpy((UBYTE *)&P3k_Backup_NSeq_Data,Data_Address_Ptr,sizeof(P3k_Backup_NSeq_Data));
	if( (P3k_Backup_NSeq_Data.CheckSum==DataCheckSum((UBYTE *)&P3k_Backup_NSeq_Data,sizeof(P3k_Backup_NSeq_Data)))&&(P3k_Backup_NSeq_Data.CheckSum) ) {
		if( P3k_Backup_NSeq_Data.MACHTYPE!=P3k_Chan_Data.INFO.MACHTYPE ) {
			P3k_Backup_NSeq_Data = P3k_Backup_NSeq_Data_Temp;
			return Machine_Type_Error;
		}
		if( P3k_Backup_NSeq_Data.F_Version>File_Version ) {
			P3k_Backup_NSeq_Data = P3k_Backup_NSeq_Data_Temp;
			return Memory_Version_Error;
		}
		SaveRecall_NSeq_Data(0);
		P3k_NSeq_Disp = P3k_NSeq_Data;
		BackupNSeq();
		return Recall_Complete;
	} else {
		P3k_Backup_NSeq_Data = P3k_Backup_NSeq_Data_Temp;
		return Recall_Failed;
	}
}

unsigned long Check_Sum;
UBYTE RecallProgDataFromSCPI(UBYTE *Data_Address_Ptr)
{
	P3k_Backup_Prog_Data_Temp = P3k_Backup_Prog_Data;
	memcpy((UBYTE *)&P3k_Backup_Prog_Data,Data_Address_Ptr,sizeof(P3k_Backup_Prog_Data));
	Check_Sum = DataCheckSum((UBYTE *)&P3k_Backup_Prog_Data,sizeof(P3k_Backup_Prog_Data));

	if( (P3k_Backup_Prog_Data.CheckSum == Check_Sum) && (P3k_Backup_Prog_Data.CheckSum) ) {
		if( P3k_Backup_Prog_Data.MACHTYPE!=P3k_Chan_Data.INFO.MACHTYPE ) {
			P3k_Backup_Prog_Data = P3k_Backup_Prog_Data_Temp;
			return Machine_Type_Error;
		}

		if( P3k_Backup_Prog_Data.F_Version > File_Version ) {
			P3k_Backup_Prog_Data = P3k_Backup_Prog_Data_Temp;
			return Memory_Version_Error;
		}

		SaveRecall_Prog_Data(0);
		p3k_Disp_PROG = p3k_Chan_PROG;
		BackupRunProg();
		return Recall_Complete;
	} else {
		P3k_Backup_Prog_Data = P3k_Backup_Prog_Data_Temp;
		return Recall_Failed;
	}
}

UBYTE RecallSetupDataFromSCPI(UBYTE *Data_Address_Ptr)
{
	p3k_file_util_str *File = &p3k_File_Utility_BAR;

	Backup_Setup_Data_Temp[File->SMEMORY_ADDR] = Backup_Setup_Data[File->SMEMORY_ADDR];
	//memcpy((UBYTE *)&Backup_Setup_Data[File->SMEMORY_ADDR],Data_Address_Ptr,sizeof(Backup_Setup_Data[File->SMEMORY_ADDR]));
	memcpy((UBYTE *)&Backup_Setup_Data,Data_Address_Ptr,sizeof(Backup_Setup_Data));
	if( (Backup_Setup_Data[File->SMEMORY_ADDR].CheckSum==DataCheckSum((UBYTE *)&Backup_Setup_Data[File->SMEMORY_ADDR],sizeof(Backup_Setup_Data[File->SMEMORY_ADDR])))&&(Backup_Setup_Data[File->SMEMORY_ADDR].CheckSum) ) {
		if( Backup_Setup_Data[File->SMEMORY_ADDR].MACHTYPE != P3k_Chan_Data.INFO.MACHTYPE ) {
			Backup_Setup_Data[File->SMEMORY_ADDR] = Backup_Setup_Data_Temp[File->SMEMORY_ADDR];
			return Machine_Type_Error;
		}
		if( Backup_Setup_Data[File->SMEMORY_ADDR].F_Version>File_Version ) {
			Backup_Setup_Data[File->SMEMORY_ADDR] = Backup_Setup_Data_Temp[File->SMEMORY_ADDR];
			return Memory_Version_Error;
		}
		SaveRecall_Setup_Data(0);
		BackupSetupData();
		return Recall_Complete;
	} else {
		Backup_Setup_Data[File->SMEMORY_ADDR] = Backup_Setup_Data_Temp[File->SMEMORY_ADDR];
		return Recall_Failed;
	}
}

UBYTE RecallPresetDataFromSCPI(UBYTE *Data_Address_Ptr)
{
	Backup_Preset_Data_Temp = Backup_Preset_Data;
	memcpy((UBYTE *)&Backup_Preset_Data,Data_Address_Ptr,sizeof(Backup_Preset_Data));
	if( (Backup_Preset_Data.CheckSum==DataCheckSum((UBYTE *)&Backup_Preset_Data,sizeof(Backup_Preset_Data)))&&(Backup_Preset_Data.CheckSum) ) {
		if( Backup_Preset_Data.MACHTYPE!=P3k_Chan_Data.INFO.MACHTYPE ) {
			Backup_Preset_Data = Backup_Preset_Data_Temp;
			return Machine_Type_Error;
		}

		if( Backup_Preset_Data.F_Version>File_Version ) {
			Backup_Preset_Data = Backup_Preset_Data_Temp;
			return Memory_Version_Error;
		}

		SaveRecall_Preset_Data(0);
		return Recall_Complete;
	} else {
		Backup_Preset_Data = Backup_Preset_Data_Temp;
		return Recall_Failed;
	}
}

#if 1
BYTE RecallDataFromFile(char Data_Type,char *FileName)
{
	char temp_fname[maxdirlen];
	LONG FileSize,Recall_Data_Size;
	FS_FILE *Wave_File;

	if(Data_Type>Recall_DataType_Cal) {
		Debug_printf("RecallDataFromFile Error\n");
		Data_Type = Recall_DataType_Cal;
	}

	if(Data_Type==Recall_DataType_Preset)
		Recall_Data_Size = sizeof(Backup_Preset_Data);
	else if(Data_Type==Recall_DataType_Prog)
		Recall_Data_Size = sizeof(P3k_Backup_Prog_Data);
	else if(Data_Type==Recall_DataType_Setup)
		Recall_Data_Size = sizeof(Backup_Setup_Data);
	else if(Data_Type==Recall_DataType_NSEQ)
		Recall_Data_Size = sizeof(P3k_Backup_NSeq_Data);
	else if(Data_Type==Recall_DataType_FSEQ)
		Recall_Data_Size = sizeof(P3k_Backup_FSeq_Data);
	else if(Data_Type==Recall_DataType_Cal)
		Recall_Data_Size = sizeof(p3k_Cal_data)-24;

	sprintf(temp_fname, "%s\\%s", FMnowPath, FileName);
	if( (Wave_File=FS_FOpen(temp_fname, "rb") )==0)
		return Recall_Failed;
	else {
		FS_FSeek(Wave_File, 0, FS_SEEK_END);
		FileSize = FS_FTell(Wave_File);
		
		if( FileSize!=Recall_Data_Size )
			return Recall_Failed;
		
		FS_FSeek(Wave_File,0,SEEK_SET);
#if 1
		UBYTE *Memory_start_address,Recall_Result;
		UBYTE (*RecallDataFromSCPI)(UBYTE *);

		Memory_start_address = malloc(FileSize);

		if(0==Memory_start_address) {
//			printf("Heap allocation error\n");
			sprintf(mybuffer,"No Memory %d size",FileSize);
			ShowMessage(mybuffer);
			return Recall_Failed;
		}

		FS_FRead(Memory_start_address, sizeof(char), FileSize, Wave_File);
		FS_FClose(Wave_File);

		if(Data_Type==Recall_DataType_Preset)
			RecallDataFromSCPI = RecallPresetDataFromSCPI;
		else if(Data_Type==Recall_DataType_Prog)
			RecallDataFromSCPI = RecallProgDataFromSCPI;
		else if(Data_Type==Recall_DataType_Setup)
			RecallDataFromSCPI = RecallSetupDataFromSCPI;
		else if(Data_Type==Recall_DataType_NSEQ)
			RecallDataFromSCPI = RecallNSeqDataFromSCPI;
		else if(Data_Type==Recall_DataType_FSEQ)
			RecallDataFromSCPI = RecallFSeqDataFromSCPI;
		else if(Data_Type==Recall_DataType_Cal)
			RecallDataFromSCPI = RecallCalSCPI;
		Recall_Result = RecallDataFromSCPI(Memory_start_address);

		free(Memory_start_address);
		return Recall_Result; 
#else
		P3k_Backup_FSeq_Data_Temp = P3k_Backup_FSeq_Data;
		FS_FRead((UBYTE *)&P3k_Backup_FSeq_Data, sizeof(char), FileSize, Wave_File);
		FS_FClose(Wave_File);
		if( (P3k_Backup_FSeq_Data.CheckSum==DataCheckSum((UBYTE *)&P3k_Backup_FSeq_Data,sizeof(P3k_Backup_FSeq_Data)))&&(P3k_Backup_FSeq_Data.CheckSum) ) {
			if( P3k_Backup_FSeq_Data.MACHTYPE!=P3k_Chan_Data.INFO.MACHTYPE ) {
				P3k_Backup_FSeq_Data = P3k_Backup_FSeq_Data_Temp;
				return Machine_Type_Error;
			}
			if( P3k_Backup_FSeq_Data.F_Version>File_Version ) {
				P3k_Backup_FSeq_Data = P3k_Backup_FSeq_Data_Temp;
				return Memory_Version_Error;
			}
			SaveRecall_FSeq_Data(0);
			P3k_FSeq_Disp = P3k_FSeq_Data;
			return Recall_Complete;
		} else {
			P3k_Backup_FSeq_Data = P3k_Backup_FSeq_Data_Temp;
			return Recall_Failed;
		}
#endif
	}
}
#endif
void SaveSetupDataAction(char SMEMORY_ADDR)
{
	if(DispMode>DispMode_BROWSE_ITEMS)
		Backup_Setup_Data[SMEMORY_ADDR].DispMode = DispMode_BROWSE_ITEMS;
	else
		Backup_Setup_Data[SMEMORY_ADDR].DispMode = DispMode;

	if((M_num==P_UTIL_INTERFACE || M_num==P_UTIL_T_DATE || M_num==P_PROG_MAIN || M_num==P_FILE_CHAN || M_num==P_UTIL_OTHER || M_num==P_PROG_EXECUTE || M_num==P_PROG_Detail)&&Backup_Setup_Data[SMEMORY_ADDR].DispMode)
		Backup_Setup_Data[SMEMORY_ADDR].DispMode = DispMode_SELECT_CH;

	if(M_num==P_PROG_EXECUTE)
		Backup_Setup_Data[SMEMORY_ADDR].M_num = P_PROG_MAIN;
	else if((M_num==P_Input_Password)||(M_num==P_CAL_MODE)||(M_num==P_UTIL_FILE)||(M_num==P_UTIL_KEYPAD)||(M_num==P_FILE_MACHINE))
		Backup_Setup_Data[SMEMORY_ADDR].M_num = P_M_num;
	else if(M_num==P_HELP_HELP)
		Backup_Setup_Data[SMEMORY_ADDR].M_num = H_M_num;
	else if(M_num==P_UTIL_SYSMEMO)
		Backup_Setup_Data[SMEMORY_ADDR].M_num = P_UTIL_SYSINFO;
	else
		Backup_Setup_Data[SMEMORY_ADDR].M_num = M_num;

	Backup_Setup_Data[SMEMORY_ADDR].DispScrCT	= DispScrEndCT - DispScrStartCT;


	if(Backup_Setup_Data[SMEMORY_ADDR].M_num==P_UTIL_OTHER)
		Backup_Setup_Data[SMEMORY_ADDR].DispScrCT = 4;

	Backup_Setup_Data[SMEMORY_ADDR].P3k_Backup_Data = FRAM_Data.P3k_Backup_Data;
	Backup_Setup_Data[SMEMORY_ADDR].Data_Ready = 200;

	BackupSetupData();
}

void RecallSetupData(char Address)
{
	char i,j,REM_CONT_Temp,l,k;
	UBYTE *Backup_Data,*Actual_Data;

	P3k_Data_Str 	*Data_tmp	= &P3k_Chan_Data;
	P3k_Backup_Str	*Backup_tmp;

	p3k_send_tx_list tx_data;

	System_Ready = 0;

	if(UTILITY.LOAD_CTL) {
		UTILITY.LOAD_CTL = Switch_OFF;
		tx_data.ADDRH = Machine_Command;
		tx_data.ADDRL = Machine_Load_OnOff;
		SendTXData(&tx_data);
		PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
		SysRedrawFlag |= PROG_UPDATA;
	}

	DispMode		= Backup_Setup_Data[Address].DispMode;
	M_num			= Backup_Setup_Data[Address].M_num;
	DispScrEndCT	= Backup_Setup_Data[Address].DispScrCT;

	Backup_tmp	= &Backup_Setup_Data[Address].P3k_Backup_Data;

	Backup_Data = &(Backup_tmp->CURRMODE);
	Actual_Data = &(Data_tmp->CURRMODE);

	for(i=0 ; i<10 ; i++)
		*(Actual_Data+i)= *(Backup_Data+i);

	Data_tmp->CC		= Backup_tmp->CC;
	Data_tmp->CR		= Backup_tmp->CR;
	Data_tmp->CV		= Backup_tmp->CV;
	Data_tmp->CP		= Backup_tmp->CP;
	Data_tmp->UTILITY	= Backup_tmp->UTILITY;
	Data_tmp->PROT		= Backup_tmp->PROT;
	Data_tmp->CONF		= Backup_tmp->CONF;
	Data_tmp->INFO		= Backup_tmp->INFO;

	for(i=0 ; i<10 ; i++)
		Data_tmp->P_DATA[i]= Backup_tmp->P_DATA[i];

	if(M_num==P_FILE_CHAN) {
		Default_info = 0;
		if(p3k_File_Utility_BAR.MEDIA==F_Media_Memory) { /* Media = Memory	*/
			Save_Status=1;
			Recall_Status=1;
		} else if(p3k_File_Utility_BAR.MEDIA==F_Media_USB) { /* Media = USB	*/
			if(USB_Status_Display==USB_Exist) {
				Save_Status	= 1;
				Recall_Status	= 1;
			}
		} else if(p3k_File_Utility_BAR.MEDIA==F_Media_Default) { /* Media = Default	*/
			Save_Status = 1;
			Recall_Status = 1;
		}
	}

	ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	MenuRedrawFlag |= MENU_CHANGE;

	RestoreRealChan();
	Control_LCDBRCon();
	FPGA_Init();
	System_Ready = 1;
	OSTimeDly(10);
	MenuRedrawFlag |= MENU_CHANGE;
	ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	SysRedrawFlag  |= SYS_CHANGE;
}

char *wave_ptr;
void WriteFileDate(char *Name1_Str, char *Name2_Str, char *Name3_Str, char *Name4_Str, char *Name5_Str, char *Name6_Str, char *Name7_Str, char *Name8_Str, char *Name9_Str, char *Name10_Str)
{
	if( *(Name1_Str)!=0) {
		strcpy(wave_ptr, Name1_Str);
		while( *(wave_ptr++));
		wave_ptr--;
	}

	if( *(Name2_Str)!=0) {
		strcpy(wave_ptr, Name2_Str);
		while( *(wave_ptr++));
		wave_ptr--;
	}

	if( *(Name3_Str)!=0) {
		strcpy(wave_ptr, Name3_Str);
		while( *(wave_ptr++));
		wave_ptr--;
	}

	if( *(Name4_Str)!=0) {
		strcpy(wave_ptr, Name4_Str);
		while( *(wave_ptr++));
		wave_ptr--;
	}

	if( *(Name5_Str)!=0) {
		strcpy(wave_ptr, Name5_Str);
		while( *(wave_ptr++));
		wave_ptr--;
	}

	if( *(Name6_Str)!=0) {
		strcpy(wave_ptr, Name6_Str);
		while( *(wave_ptr++));
		wave_ptr--;
	}

	if( *(Name7_Str)!=0) {
		strcpy(wave_ptr, Name7_Str);
		while( *(wave_ptr++));
		wave_ptr--;
	}

	if( *(Name8_Str)!=0) {
		strcpy(wave_ptr, Name8_Str);
		while( *(wave_ptr++));
		wave_ptr--;
	}

	if( *(Name9_Str)!=0) {
		strcpy(wave_ptr, Name9_Str);
		while( *(wave_ptr++));
		wave_ptr--;
	}

	if( *(Name10_Str)!=0) {
		strcpy(wave_ptr, Name10_Str);
		while( *(wave_ptr++));
		wave_ptr--;
	}

	*(wave_ptr++)=0x0D;
	*(wave_ptr++)=0x0A;
}

void WriteFileDate_string(char *Name1_Str, char Mode)
{
	/*Mode:0 Write String*/
	/*Mode:1 Write final String*/
	char  Str_Buf[50];

	if(Mode==0) {
		sprintf(Str_Buf,"%s,", Name1_Str);
		strcpy(wave_ptr, Str_Buf);
		while( *(wave_ptr++));
		wave_ptr--;
	} else if(Mode==1) {
		sprintf(Str_Buf,"%s", Name1_Str);
		strcpy(wave_ptr, Str_Buf);
		while( *(wave_ptr++));
		wave_ptr--;
		*(wave_ptr++)=0x0D;
		*(wave_ptr++)=0x0A;
	}
}

void SaveGoNGResult(void)
{

}

BYTE Upgrading(char source,char *FileName)
{
	p3k_send_tx_list tx_data;
	char temp_fname[maxdirlen],str[20],i;
	LONG FileSize,FileSize_temp,UPG_CheckSum=0,Record_CheckSum=0,CheckSum_temp[4],Read_File_Part,Read_File_Part2;
	FS_FILE *Wave_File;
	UWORD Page_Sum,Page_Size=512;
	UBYTE *Memory_current_address,*Memory_start_address;

	Auto_Load_Off();

	disconnect_USB();
	WriteIO(USB_ID,0);//Host Mode

	sprintf(temp_fname, "%s\\%s", FMnowPath, FileName);
	if( (Wave_File=FS_FOpen(temp_fname, "rb") )==0) {
		sprintf(mybuffer,"File can not open");
		ShowMessage(mybuffer);
		return 0;
	} else {
		FS_FSeek(Wave_File, 0, FS_SEEK_END);						/*move 1 read position from end of file*/
		FileSize=FS_FTell(Wave_File);								/*read position of read position*/
		FS_FSeek(Wave_File,0,SEEK_SET);								/*move 1 read position from start of file*/
		Memory_start_address = malloc(FileSize);
		if (Memory_start_address == 0) {
			printf("Heap allocation error\n");
			sprintf(mybuffer,"No Memory %d size",FileSize);
			ShowMessage(mybuffer);
			return 1;
		}
		sprintf(mybuffer,"Reading");
		ShowMessage(mybuffer);

		Memory_current_address=Memory_start_address;
		Read_File_Part=FileSize/12;
		Read_File_Part2=FileSize%12;
		for(i=0; i<12; i++) {
			FS_FRead((void *)Memory_current_address, sizeof(char), Read_File_Part, Wave_File);
			Memory_current_address+=Read_File_Part;
			sprintf(mybuffer,"%s.",mybuffer);
			GUI_SetBkColor(File_Bottom_Bolor);
			GUI_SetColor(File_Message_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_DispStringAt(mybuffer,9,174);
		}
		if(Read_File_Part2)
			FS_FRead((void *)Memory_current_address, sizeof(char), Read_File_Part2, Wave_File);
		Memory_current_address=Memory_start_address;
		FS_FClose(Wave_File);

		sprintf(mybuffer,"Checking...");
		ShowMessage(mybuffer);
		FileSize_temp=FileSize-4;
		while(FileSize_temp--)
			UPG_CheckSum += (unsigned long)(*(Memory_current_address++));
		UPG_CheckSum=~UPG_CheckSum;
		CheckSum_temp[0]=(unsigned long)(*(Memory_current_address++));
		CheckSum_temp[0]=CheckSum_temp[0]&0x000000ff;
		CheckSum_temp[1]=(unsigned long)(*(Memory_current_address++));
		CheckSum_temp[1]=CheckSum_temp[1]&0x000000ff;
		CheckSum_temp[2]=(unsigned long)(*(Memory_current_address++));
		CheckSum_temp[2]=CheckSum_temp[2]&0x000000ff;
		CheckSum_temp[3]=(unsigned long)(*(Memory_current_address));
		CheckSum_temp[3]=CheckSum_temp[3]&0x000000ff;
		Record_CheckSum=(CheckSum_temp[3]<<24)+(CheckSum_temp[2]<<16)+(CheckSum_temp[1]<<8)+CheckSum_temp[0];
		if(Record_CheckSum!=UPG_CheckSum) {
			sprintf(mybuffer,"Checksum error!");
			ShowMessage(mybuffer);
			free(Memory_start_address);
			return 0;
		}

		sprintf(mybuffer,"Upgrading...");
		ShowMessage(mybuffer);
		Page_Sum=(FileSize-4)/Page_Size;
		if((FileSize-4)%Page_Size)
			Page_Sum++;
		Memory_current_address=Memory_start_address;
		WriteIO(DATA_FLASH_SEL, 0);//PF2 map to #1 on board data flash.  Kevin Meng 2006.3.2
		WriteIO(DATA_FLASH_WP,1);//Disable write protect;
		if(source==0)		ProgramAllUserProgram512(AppCode_Start_Page,Memory_current_address,Page_Sum);			/*	Reprogram Gel2000	*/
		else if(source==1)	ProgramAllUserProgram512(LogoPic_Start_Page,Memory_current_address,Page_Sum);			/*	Reprogram BootLogo	*/
		else if(source==2)	ProgramAllUserProgram512(OnBoard_Monitor_Start_Page,Memory_current_address,Page_Sum);	/*	Reprogram Monitor		*/
		else if(source==3)	ProgramAllUserProgram512(FPGACode_Start_Page,Memory_current_address,Page_Sum);			/*	Reprogram FPGA		*/
		WriteIO(DATA_FLASH_WP,0);//Enable write protect;

		sprintf(mybuffer,"Data checking...");
		ShowMessage(mybuffer);
		if(source==0)		CountinueArrayRead512(AppCode_Start_Page*Page_Size,Memory_current_address,FileSize);
		else if(source==1)	CountinueArrayRead512(LogoPic_Start_Page*Page_Size,Memory_current_address,FileSize);
		else if(source==2)	CountinueArrayRead512(OnBoard_Monitor_Start_Page*Page_Size,Memory_current_address,FileSize);
		else if(source==3)	CountinueArrayRead512(FPGACode_Start_Page*Page_Size,Memory_current_address,FileSize);

		FileSize_temp=FileSize-4;
		UPG_CheckSum=0;
		while(FileSize_temp--)
			UPG_CheckSum += (unsigned long)(*(Memory_current_address++));
		UPG_CheckSum=~UPG_CheckSum;
		if(Record_CheckSum!=UPG_CheckSum) {
			sprintf(mybuffer,"Upgrade error!!");
			ShowMessage(mybuffer);
			free(Memory_start_address);
			printf("Upgrade error!!\n");
			printf("Record_CheckSum=0x%x\n",Record_CheckSum);
			printf("UPG_CheckSum=0x%x\n",UPG_CheckSum);
			return 0;
		}
		sprintf(mybuffer,"Upgrade Done! Please Cycle Power");
		ShowMessage(mybuffer);
		free(Memory_start_address);
	}
	return 1;
}
BYTE Upgrading_SCPI(char source,UBYTE *SCPI_Data,LONG FileSize)
{
	p3k_send_tx_list tx_data;
	char str[20],i;
	LONG FileSize_temp,UPG_CheckSum=0,Record_CheckSum=0,CheckSum_temp[4],Read_File_Part,Read_File_Part2;
	UWORD Page_Sum,Page_Size=512;
	UBYTE *Memory_current_address;

	Auto_Load_Off();

	disconnect_USB();
	WriteIO(USB_ID,0);//Host Mode

	Debug_printf("Checking...\n");
	Menu_Message_Pro(0,"Checking CheckSum...");

	Memory_current_address=SCPI_Data;

	FileSize_temp=FileSize-4;
	while(FileSize_temp--)
		UPG_CheckSum += (unsigned long)(*(Memory_current_address++));
	UPG_CheckSum=~UPG_CheckSum;
	CheckSum_temp[0]=(unsigned long)(*(Memory_current_address++));
	CheckSum_temp[0]=CheckSum_temp[0]&0x000000ff;
	CheckSum_temp[1]=(unsigned long)(*(Memory_current_address++));
	CheckSum_temp[1]=CheckSum_temp[1]&0x000000ff;
	CheckSum_temp[2]=(unsigned long)(*(Memory_current_address++));
	CheckSum_temp[2]=CheckSum_temp[2]&0x000000ff;
	CheckSum_temp[3]=(unsigned long)(*(Memory_current_address));
	CheckSum_temp[3]=CheckSum_temp[3]&0x000000ff;
	Record_CheckSum=(CheckSum_temp[3]<<24)+(CheckSum_temp[2]<<16)+(CheckSum_temp[1]<<8)+CheckSum_temp[0];
	if(Record_CheckSum!=UPG_CheckSum) {
		Debug_printf("Checksum error!\n");
		Menu_Message_Pro(0,"Checksum error!");
		return 0;
	}

	Debug_printf("Upgrading...\n");
	Menu_Message_Pro(0,"Upgrading Firmware...");

	Page_Sum=(FileSize-4)/Page_Size;
	if((FileSize-4)%Page_Size)
		Page_Sum++;
	Memory_current_address=SCPI_Data;
	WriteIO(DATA_FLASH_SEL, 0);/*PF2 map to #1 on board data flash.  Kevin Meng 2006.3.2*/
	WriteIO(DATA_FLASH_WP,1);/*Disable write protect; */
	if(source==0)		ProgramAllUserProgram512(AppCode_Start_Page,Memory_current_address,Page_Sum);			/*Reprogram Gel2000*/
	else if(source==1)	ProgramAllUserProgram512(LogoPic_Start_Page,Memory_current_address,Page_Sum);			/*Reprogram BootLogo*/
	else if(source==2)	ProgramAllUserProgram512(OnBoard_Monitor_Start_Page,Memory_current_address,Page_Sum);	/*Reprogram Monitor*/
	else if(source==3)	ProgramAllUserProgram512(FPGACode_Start_Page,Memory_current_address,Page_Sum);			/*Reprogram FPGA*/
	WriteIO(DATA_FLASH_WP,0);/*Enable write protect;*/

	if(source==0)		CountinueArrayRead512(AppCode_Start_Page*Page_Size,Memory_current_address,FileSize);
	else if(source==1)	CountinueArrayRead512(LogoPic_Start_Page*Page_Size,Memory_current_address,FileSize);
	else if(source==2)	CountinueArrayRead512(OnBoard_Monitor_Start_Page*Page_Size,Memory_current_address,FileSize);
	else if(source==3)	CountinueArrayRead512(FPGACode_Start_Page*Page_Size,Memory_current_address,FileSize);

	FileSize_temp=FileSize-4;
	UPG_CheckSum=0;
	while(FileSize_temp--)
		UPG_CheckSum += (unsigned long)(*(Memory_current_address++));
	UPG_CheckSum=~UPG_CheckSum;
	if(Record_CheckSum!=UPG_CheckSum) {
		Menu_Message_Pro(0,"Upgrading Failed...");
		Debug_printf("Upgrade error!!\n");
		return 0;
	}
	Debug_printf("Upgrade Done! Please Cycle Power\n");
	Menu_Message_Pro(0,"Upgrade Done! Please Cycle Power");
	return 1;
}
extern int uncompress (unsigned char *dest, unsigned long *destLen, const unsigned char *source, unsigned long sourceLen);
BYTE UpgradingMain(char *FileName)
{
	p3k_send_tx_list tx_data;
	char temp_fname[maxdirlen],i;
	LONG FileSize,CheckSum_temp[4],FileSize_temp;
	FS_FILE *Wave_File;
	UWORD Page_Sum,Page_Size=512;
	ULONG Data_FileSize[2],UPG_CheckSum,Record_CheckSum[2];
	ULONG Data_Flash_Page[2];
	UBYTE *Memory_current_address,*Memory_start_address;
	LONG Read_File_Part,Read_File_Part2;
	Data_Flash_Page[0] = AppCode_Start_Page;
	Data_Flash_Page[1] = FPGACode_Start_Page;

	Auto_Load_Off();

	disconnect_USB();
	WriteIO(USB_ID,0);//Host Mode

	sprintf(temp_fname, "%s\\%s", FMnowPath, FileName);
	if( (Wave_File=FS_FOpen(temp_fname, "rb") )==0) {
		sprintf(mybuffer,"File can not open");
		ShowMessage(mybuffer);
		return 0;
	} else {
		//get File Size
		FS_FSeek(Wave_File, 0, FS_SEEK_END);						/*move 1 read position from end of file*/
		FileSize=FS_FTell(Wave_File);								/*read position of read position*/
		FS_FSeek(Wave_File,0,SEEK_SET); 							/*move 1 read position from start of file*/

		Memory_start_address = malloc(FileSize);
		if(Memory_start_address==0) {
			printf("Heap allocation error\n");
			sprintf(mybuffer,"No Memory %d size",FileSize);
			ShowMessage(mybuffer);
			FS_FClose(Wave_File);
			return 1;
		}
		sprintf(mybuffer,"Reading");
		ShowMessage(mybuffer);

		Memory_current_address	= Memory_start_address;
		Read_File_Part			= FileSize/12;
		Read_File_Part2			= FileSize%12;
		for(i=0 ; i<12 ; i++) {
			FS_FRead((void *)Memory_current_address, sizeof(char), Read_File_Part, Wave_File);
			Memory_current_address += Read_File_Part;
			sprintf(mybuffer,"%s.",mybuffer);
			GUI_SetBkColor(File_Bottom_Bolor);
			GUI_SetColor(File_Message_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_DispStringAt(mybuffer,9,174);
			DMA_Update_Flag = 1;
			Update_Panel();
		}
		if(Read_File_Part2)
			FS_FRead((void *)Memory_current_address, sizeof(char), Read_File_Part2, Wave_File);
		FS_FClose(Wave_File);
		sprintf(mybuffer,"Checking");
		ShowMessage(mybuffer);
		Memory_current_address = Memory_start_address;
		for(i=0 ; i<2 ; i++) {
			Data_FileSize[i] =  0;
			Data_FileSize[i] =   *(Memory_current_address++);
			Data_FileSize[i] += (*(Memory_current_address++))<<8;
			Data_FileSize[i] += (*(Memory_current_address++))<<16;
			Data_FileSize[i] += (*(Memory_current_address++))<<24;
		}
		for(i=0 ; i<2 ; i++) {
			UPG_CheckSum	= 0;
			FileSize_temp	= Data_FileSize[i]-4;
			while(FileSize_temp--)
				UPG_CheckSum += (unsigned long)(*(Memory_current_address++));
			UPG_CheckSum	= ~UPG_CheckSum;
			CheckSum_temp[0]= (unsigned long)(*(Memory_current_address++));
			CheckSum_temp[1]= (unsigned long)(*(Memory_current_address++));
			CheckSum_temp[2]= (unsigned long)(*(Memory_current_address++));
			CheckSum_temp[3]= (unsigned long)(*(Memory_current_address++));
			CheckSum_temp[0]= CheckSum_temp[0]&0x000000ff;
			CheckSum_temp[1]= CheckSum_temp[1]&0x000000ff;
			CheckSum_temp[2]= CheckSum_temp[2]&0x000000ff;
			CheckSum_temp[3]= CheckSum_temp[3]&0x000000ff;

			Record_CheckSum[i] = (CheckSum_temp[3]<<24)+(CheckSum_temp[2]<<16)+(CheckSum_temp[1]<<8)+CheckSum_temp[0];
			if(Record_CheckSum[i]!=UPG_CheckSum) {
				sprintf(mybuffer,"%d Checksum error!",i);
				ShowMessage(mybuffer);
				free((void *)Memory_start_address);
				return 0;
			}
			sprintf(mybuffer,"%s.",mybuffer);
			GUI_SetBkColor(File_Bottom_Bolor);
			GUI_SetColor(File_Message_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_DispStringAt(mybuffer,9,174);
		}
		sprintf(mybuffer,"Upgrading");
		ShowMessage(mybuffer);
		Memory_current_address = Memory_start_address+8;
		for(i=0 ; i<2 ; i++) {
			Page_Sum = (Data_FileSize[i]-4)/Page_Size;
			if((Data_FileSize[i]-4)%Page_Size)
				Page_Sum++;
			WriteIO(DATA_FLASH_SEL,0);//PF2 map to #1 on board data flash.  Kevin Meng 2006.3.2
			WriteIO(DATA_FLASH_WP, 1);//Disable write protect;
#if 1
			unsigned short i1 = 0;
			unsigned char k1=0;
			while(Page_Sum){
				if(Page_Sum>=90)
					ProgramAllUserProgram512((Data_Flash_Page[i]+i1),(void *)(Memory_current_address+i1*Page_Size),90);
				else
					ProgramAllUserProgram512((Data_Flash_Page[i]+i1),(void *)(Memory_current_address+i1*Page_Size),Page_Sum);
				i1=i1+90;
				//k1++;
				if(Page_Sum>=90)Page_Sum=Page_Sum-90;
				else			Page_Sum = 0;
				//k1=0;
				sprintf(mybuffer,"%s.",mybuffer);
				GUI_SetBkColor(File_Bottom_Bolor);
				GUI_SetColor(File_Message_Font_Bolor);
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt(mybuffer,9,174);
				DMA_Update_Flag = 1;
				Update_Panel();
								
			}
			WriteIO(DATA_FLASH_WP,0);//Enable write protect;
			Memory_current_address += Data_FileSize[i];
#else
			//printf("b:%x\n",Memory_current_address);
			ProgramAllUserProgram512(Data_Flash_Page[i],(void *)Memory_current_address,Page_Sum);
			//printf("a:%x\n",Memory_current_address);
			WriteIO(DATA_FLASH_WP,0);//Enable write protect;
			Memory_current_address += Data_FileSize[i];
			sprintf(mybuffer,"%s.",mybuffer);
			GUI_SetBkColor(File_Bottom_Bolor);
			GUI_SetColor(File_Message_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_DispStringAt(mybuffer,9,174);
			DMA_Update_Flag = 1;
			Update_Panel();
#endif
		}

		sprintf(mybuffer,"Data checking");
		ShowMessage(mybuffer);
		for(i=0 ; i<2 ; i++) {
			Memory_current_address = Memory_start_address;
			CountinueArrayRead512(Data_Flash_Page[i]*Page_Size,(void *)Memory_current_address,Data_FileSize[i]);
			OSTimeDly(3);
			FileSize_temp = Data_FileSize[i]-4;
			UPG_CheckSum  = 0;
			while(FileSize_temp--)
				UPG_CheckSum += (unsigned long)(*(Memory_current_address++));
			UPG_CheckSum=~UPG_CheckSum;
			if(Record_CheckSum[i]!=UPG_CheckSum) {
				sprintf(mybuffer,"Upgrade error!!");
				ShowMessage(mybuffer);
				printf("%d Upgrade error!!\n",i);
				printf("UPG_CheckSum=0x%x Record_CheckSum=0x%x\n",UPG_CheckSum,Record_CheckSum[i]);
				free((void *)Memory_start_address);
				return 0;
			}
			sprintf(mybuffer,"%s.",mybuffer);
			GUI_SetBkColor(File_Bottom_Bolor);
			GUI_SetColor(File_Message_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_DispStringAt(mybuffer,9,174);
		}
		free((void *)Memory_start_address);
		System_Ready = 0;
		OSTimeDly(10);

		sprintf(mybuffer,"Upgrade Done! Please Cycle Power");
		ShowMessage(mybuffer);
	}
	return 1;
}

BYTE Prog_Function(BYTE chnum, BYTE x)
{
	Soft_Key_Temp=0;
	p3k_Disp_PROG = p3k_Chan_PROG;
	M_num = P_PROG_MAIN;
	SEQ_Save_Status=0;
	ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	return 1;
}

BYTE Seq_Function(BYTE chnum, BYTE x)
{
	Soft_Key_Temp=0;
	M_num = P_Seq_FUNC;
	SEQ_Save_Status=0;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	return 1;
}
#if Enable_OCP_function
BYTE APP_Function(BYTE chnum, BYTE x)
{
	Soft_Key_Temp=0;
	M_num = P_FUNC_MAIN_2;
	SEQ_Save_Status=0;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	return 1;
}

BYTE APP_Function_OCP(BYTE chnum, BYTE x)
{
	Soft_Key_Temp=0;
	M_num = P_FUNC_OCP;	
	SEQ_Save_Status=0;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	P3K_OCP_Disp = P3K_OCP_Data;
	return 1;
}
#endif
#if Enable_OPP_function
BYTE APP_Function_OPP(BYTE chnum, BYTE x) {
	Soft_Key_Temp=0;
	M_num = P_FUNC_OPP;
	SEQ_Save_Status=0;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	P3K_OPP_Disp = P3K_OPP_Data;
	return 1;
}
#endif
#if 1
BYTE goto_func_main2(BYTE chnum, BYTE x){
	M_num = P_FUNC_MAIN_2;
	ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	HelpRedrawFlag &= ~HELP_FUN_ON;
	return 1;
}
#endif
#if Enable_Battery_Discharge
BYTE goto_func_batt(BYTE chnum, BYTE x) {
	Soft_Key_Temp=0;
	M_num = P_FUNC_batt;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	ClrDispCnt(0x01, 0x00, 0x04, 0x00, 0x00, 0x00);
	return 1;
}
BYTE goto_func_batt2(BYTE chnum, BYTE x) { //OPP
	Soft_Key_Temp=0;
	M_num = P_FUNC_OPP;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	ClrDispCnt(0x01, 0x00, 0x00, 0x00, 0x00, 0x00);
	return 1;
}
BYTE goto_func_batt_exe(BYTE chnum, BYTE x) {
	Soft_Key_Temp=0;
	M_num = P_FUNC_batt_EXECUTE;
	SEQ_Save_Status=0;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	return 1;
}

#endif
#if Enable_LED_function
BYTE goto_func_led(BYTE chnum, BYTE x) {
	Soft_Key_Temp=0;
	M_num = P_FUNC_FLED;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	ClrDispCnt(0x01, 0x00, 4, 0x00, 0x00, 0x00);
	return 1;
}

BYTE goto_func_led_exe(BYTE chnum, BYTE x) {
	Soft_Key_Temp=0;
	M_num = P_FUNC_FLED_EXECUTE;
	SEQ_Save_Status=0;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	return 1;
}

BYTE goto_curve_led(BYTE chnum, BYTE x) {
	Soft_Key_Temp=0;
	M_num = P_FUNC_CLED;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	ClrDispCnt(0x01, 0x00, 4, 0x00, 0x00, 0x00);
	return 1;
}

BYTE goto_curve_led_exe(BYTE chnum, BYTE x) {
	Soft_Key_Temp=0;
	M_num = P_FUNC_CLED_EXECUTE;
	SEQ_Save_Status=0;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	return 1;
}

#endif


BYTE Save_Fill_Action(BYTE chnum, BYTE x)
{

	FSeq_Data_Str *FSeq_Data_Ptr;
	UWORD Step_Temp,i,Level1_Value,Level2_Value;
	LONG Difference_Value;

#if 1
	UWORD max_step,SetStep;
	if(P3k_FSeq_Disp.FSeq_Max_Step>0xFF00)	max_step = 0;
	else									max_step = P3k_FSeq_Disp.FSeq_Max_Step+1;
	if(P3k_FSeq_Disp.Fill_Start_Step>P3k_FSeq_Disp.Fill_End_Step)	SetStep = P3k_FSeq_Disp.Fill_Start_Step;
	else															SetStep = P3k_FSeq_Disp.Fill_End_Step;
	if(max_step>SetStep){
	}else{
		for(i=max_step;i<=SetStep;i++){ 						//added new space step
			P3k_FSeq_Disp.FSeq_Step[i].FSeq_Value = 0;
			P3k_FSeq_Disp.FSeq_Step[i].TrigOut_Setting = 0;
		}
		P3k_FSeq_Disp.FSeq_Max_Step = SetStep; 			//maxstep = setstep
	}	
#endif	
	if(P3k_FSeq_Disp.Fill_Start_Step==P3k_FSeq_Disp.Fill_End_Step) {
		P3k_FSeq_Disp.FSeq_Step[P3k_FSeq_Disp.Fill_Start_Step].FSeq_Value = P3k_FSeq_Disp.Fill_Start_Value;
	} else {
		if(P3k_FSeq_Disp.Fill_Start_Step>P3k_FSeq_Disp.Fill_End_Step) {
			Step_Temp		= P3k_FSeq_Disp.Fill_Start_Step - P3k_FSeq_Disp.Fill_End_Step;
			Level1_Value	= P3k_FSeq_Disp.Fill_End_Value;
			Level2_Value	= P3k_FSeq_Disp.Fill_Start_Value;
			FSeq_Data_Ptr	= &P3k_FSeq_Disp.FSeq_Step[P3k_FSeq_Disp.Fill_End_Step];
			Difference_Value= P3k_FSeq_Disp.Fill_Start_Value - P3k_FSeq_Disp.Fill_End_Value;
		} else {
			Step_Temp		= P3k_FSeq_Disp.Fill_End_Step - P3k_FSeq_Disp.Fill_Start_Step;
			Level1_Value	= P3k_FSeq_Disp.Fill_Start_Value;
			Level2_Value	= P3k_FSeq_Disp.Fill_End_Value;
			FSeq_Data_Ptr	= &P3k_FSeq_Disp.FSeq_Step[P3k_FSeq_Disp.Fill_Start_Step];
			Difference_Value= P3k_FSeq_Disp.Fill_End_Value - P3k_FSeq_Disp.Fill_Start_Value;
		}
		for(i=0 ; i<=Step_Temp ; i++) {
			FSeq_Data_Ptr->FSeq_Value = Level1_Value + (i*Difference_Value/Step_Temp);
			FSeq_Data_Ptr++;
		}
		(FSeq_Data_Ptr-1)->FSeq_Value = Level2_Value;
	}

	P3k_FSeq_Data.Fill_Start_Step	= P3k_FSeq_Disp.Fill_Start_Step;
	P3k_FSeq_Data.Fill_Start_Value	= P3k_FSeq_Disp.Fill_Start_Value;
	P3k_FSeq_Data.Fill_End_Step	= P3k_FSeq_Disp.Fill_End_Step;
	P3k_FSeq_Data.Fill_End_Value	= P3k_FSeq_Disp.Fill_End_Value;

	ClrDispCnt( 0x00, 0x00, 0x05, 0x00, 0x00, 0x00);
	M_num = P_FSeq_Edit;
	Soft_Key_Temp	= 0;
	SEQ_Save_Status= 1;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	return M_Success;
}

BYTE Fill_Function(BYTE chnum, BYTE x)
{
	ClrDispCnt( 0x00, 0x00, 0x05, 0x00, 0x00, 0x00);
	M_num = P_FSeq_Fill;
	Soft_Key_Temp  = 0;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	//P3k_FSeq_Disp = P3k_FSeq_Data;
	return M_Success;
}

BYTE Add_FSeq(BYTE chnum, BYTE x)
{
	UWORD i;

	if((P3k_FSeq_Disp.FSeq_Max_Step>=999)&&(P3k_FSeq_Disp.FSeq_Max_Step<0xFF00))
		return M_Out_Of_Range;
	if(P3k_FSeq_Disp.FSeq_Max_Step> 0xFF00) {
		P3k_FSeq_Disp.FSeq_Max_Step=0;
		P3k_FSeq_Disp.FSeq_Curr_Step=0;
	} else {
		P3k_FSeq_Disp.FSeq_Max_Step++;
		P3k_FSeq_Disp.FSeq_Curr_Step++;
	}
#if Enable_FSEQ_RPT
	P3k_FSeq_Disp.RPTStep = P3k_FSeq_Disp.FSeq_Max_Step;
#endif	

	//for (i = max; i > FSeq_Curr_step ) 往後推一格
	//data_addr(i) = data_addr(i - 1);
	//data_addr(curr) = define_value(0); 新值等於零


	for (i = P3k_FSeq_Disp.FSeq_Max_Step; i > P3k_FSeq_Disp.FSeq_Curr_Step; i--)
		P3k_FSeq_Disp.FSeq_Step[i] = P3k_FSeq_Disp.FSeq_Step[i - 1];
	P3k_FSeq_Disp.FSeq_Step[i].FSeq_Value = 0;
	P3k_FSeq_Disp.FSeq_Step[i].TrigOut_Setting = 0;
	SEQ_Save_Status = 1;
	DispMode = DispMode_SELECT_CH;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	MenuRedrawFlag |= MENU1_CHANGE + MENU3_CHANGE;
	return M_Success;
}
BYTE Del_FSeq(BYTE chnum, BYTE x)
{
	UWORD i;
	if(P3k_FSeq_Disp.FSeq_Max_Step>0xFF00) {
		P3k_FSeq_Disp.FSeq_Max_Step =0;
		return M_Out_Of_Range;
	}
//for (i=FSeq_Curr_step;i<max;i++)往前推一格
//data_addr(i) = data_addr(i + 1);
//data_addr(i+1) = 0 (i前次最大數值清為零
// max = max -1;  最大值減1
//if (curr_step > max)curr_step = max 假設目前值大於最大值則減1
	for (i = P3k_FSeq_Disp.FSeq_Curr_Step; i < P3k_FSeq_Disp.FSeq_Max_Step; i++)
		P3k_FSeq_Disp.FSeq_Step[i] = P3k_FSeq_Disp.FSeq_Step[i + 1];
	P3k_FSeq_Disp.FSeq_Step[i+1].FSeq_Value = 0;
	P3k_FSeq_Disp.FSeq_Step[i+1].TrigOut_Setting = 0;
	P3k_FSeq_Disp.FSeq_Max_Step--;
	if(P3k_FSeq_Disp.FSeq_Curr_Step > P3k_FSeq_Disp.FSeq_Max_Step)
		P3k_FSeq_Disp.FSeq_Curr_Step = P3k_FSeq_Disp.FSeq_Max_Step;
#if Enable_FSEQ_RPT
	if(P3k_FSeq_Disp.RPTStep>P3k_FSeq_Disp.FSeq_Max_Step)
		P3k_FSeq_Disp.RPTStep = P3k_FSeq_Disp.FSeq_Max_Step;
#endif

	SEQ_Save_Status = 1;
	DispMode = DispMode_SELECT_CH;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	MenuRedrawFlag |= MENU2_CHANGE + MENU3_CHANGE;
	return M_Success;
}
#if Enable_fseq_deletAll
void Del_FSeq_All(void)
{
	UWORD i;
	if(P3k_FSeq_Disp.FSeq_Max_Step>0xFF00) {
		P3k_FSeq_Disp.FSeq_Max_Step =0;		
	}
	for (i = 0; i < 1001; i++){
		P3k_FSeq_Disp.FSeq_Step[i].FSeq_Value = 0;
		P3k_FSeq_Disp.FSeq_Step[i].TrigOut_Setting = 0;
	}
	P3k_FSeq_Disp.FSeq_Max_Step = 0xFFFF;
	P3k_FSeq_Disp.FSeq_Curr_Step = 0;
#if Enable_FSEQ_RPT
	P3k_FSeq_Disp.RPTStep = 0;
#endif	
	SEQ_Save_Status = 1;
	DispMode = DispMode_SELECT_CH;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	MenuRedrawFlag |= MENU2_CHANGE + MENU3_CHANGE;	
}
#endif

BYTE Add_NSeq(BYTE chnum, BYTE x)
{
	UWORD Total_Step,i;
	UBYTE j;
	Total_Step = 0;
	for(i=0 ; i<10 ; i++)
		Total_Step += P3k_NSeq_Disp.NSeq_Seq[i].NSeq_Max_Step;
	if(Total_Step>=1000) //max_step chage 1000 steps
		return M_Out_Of_Range;

//for (i = max; i > FSeq_Curr_step ) 往後推一格
//data_addr(i) = data_addr(i - 1);
//data_addr(curr) = define_value(0); 新值等於零

	j = P3k_NSeq_Disp.NSeq_Number;
	P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Max_Step++;
	P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Curr_Step++;
	for (i = P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Max_Step; i > P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Curr_Step; i--)
		P3k_NSeq_Disp.NSeq_Step[j][i] = P3k_NSeq_Disp.NSeq_Step[j][i - 1];
	P3k_NSeq_Disp.NSeq_Step[j][i] = P3k_NSeq_Disp.NSeq_Step[0][1024];
	P3k_NSeq_Disp.NSeq_Step[j][i].NSeq_Time.MilliSecond = 100; // new step during time = 0.1 sec
	SEQ_Save_Status = 1;
	DispMode = DispMode_SELECT_CH;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	MenuRedrawFlag |= MENU1_CHANGE + MENU3_CHANGE;
	return M_Success;
}

BYTE Del_NSeq(BYTE chnum, BYTE x)
{
	UWORD i;
	UBYTE j;
	if(0==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step)
		return M_Out_Of_Range;

//for (i=FSeq_Curr_step;i<max;i++)往前推一格
//data_addr(i) = data_addr(i + 1);
//data_addr(i+1) = 0 (i前次最大數值清為零
// max = max -1;  最大值減1
//if (curr_step > max)curr_step = max 假設目前值大於最大值則減1
	//if(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Curr_Step>1)
	//	P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Curr_Step--;
	j = P3k_NSeq_Disp.NSeq_Number;
	for (i = P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Curr_Step; i < P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Max_Step; i++)
		P3k_NSeq_Disp.NSeq_Step[j][i] = P3k_NSeq_Disp.NSeq_Step[j][i + 1];
	P3k_NSeq_Disp.NSeq_Step[j][i+1] = P3k_NSeq_Disp.NSeq_Step[0][1024];//歸零
	P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Max_Step--;
	if(0==P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Max_Step) {
		P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Curr_Step = 0;
		B_DispCT = DispCT = 0;
	}
	if ( P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Curr_Step >= P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Max_Step)
		P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Curr_Step = P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Max_Step;
	SEQ_Save_Status = 1;
	DispMode = DispMode_SELECT_CH;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	MenuRedrawFlag |= MENU2_CHANGE + MENU3_CHANGE;
	return M_Success;
}

BYTE Del_NSeq_all(BYTE chnum, BYTE x)
{
	UWORD i;
	UBYTE j;
	if(0==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step)
		return M_Out_Of_Range;
	j = P3k_NSeq_Disp.NSeq_Number;
	for (i = P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Curr_Step; i < P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Max_Step; i++)
		P3k_NSeq_Disp.NSeq_Step[j][i] = P3k_NSeq_Disp.NSeq_Step[0][1024];
	P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Max_Step=0;
	if(0==P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Max_Step) {
		P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Curr_Step = 0;
		B_DispCT = DispCT = 0;
	}
	if ( P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Curr_Step >= P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Max_Step)
		P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Curr_Step = P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Max_Step;

	SEQ_Save_Status = 1;
	DispMode = DispMode_SELECT_CH;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	MenuRedrawFlag |= MENU2_CHANGE + MENU3_CHANGE;
	return M_Success;
}



BYTE Test1_Function(BYTE chnum, BYTE x)
{
	UWORD i;
	for(i=0 ; i<4096 ; i++)
		iTxBuffer1[0][i] = 0x1A00AAAA;	/*Voltage*/
	Init_DMA_Sport0();
	return 1;
}

BYTE Test2_Function(BYTE chnum, BYTE x)
{
	System_Ready = 0;
	OSTimeDly(1);

	Enable_Continuous_DMA_Sport0(0);
	return 1;
}
extern void Show_Prot_Error_Window(UBYTE Error_Mode,double Error_Gain,double Error_Offset,UWORD Input_HP,UWORD Input_LP,UWORD System_HP,UWORD System_LP);
BYTE Test3_Function(BYTE chnum, BYTE x)
{
	Show_Prot_Error_Window(0,1.5,1.8,100,200,300,400);
	return 1;
}


BYTE UpgradingFPGA(char *FileName)
{
	char temp_fname[maxdirlen],i,j,Command_Buf[6];
	LONG FileSize,k,Command_Number;
	FS_FILE *Wave_File;
	UBYTE *Memory_current_address,*Memory_start_address;
	ULONG SPROT0_CMD;

	sprintf(temp_fname, "%s\\%s", FMnowPath, FileName);
	if( (Wave_File=FS_FOpen(temp_fname, "rb") )==0) {
		sprintf(mybuffer,"File can not open");
		ShowMessage(mybuffer);
		return 0;
	} else {
		//get File Size
		FS_FSeek(Wave_File, 0, FS_SEEK_END);						/*move 1 read position from end of file*/
		FileSize=FS_FTell(Wave_File);								/*read position of read position*/
		FS_FSeek(Wave_File,0,SEEK_SET); 							/*move 1 read position from start of file*/

		Memory_start_address = malloc(FileSize);
		if(0==Memory_start_address) {
			printf("Heap allocation error\n");
			sprintf(mybuffer,"No Memory %d size",FileSize);
			ShowMessage(mybuffer);
			FS_FClose(Wave_File);
			free(Memory_start_address);
			return 0;
		}
		Memory_current_address=Memory_start_address;
		FS_FRead(Memory_current_address, sizeof(char), FileSize, Wave_File);
		Command_Buf[5]=Command_Buf[4]=Command_Buf[3]=Command_Buf[2]=Command_Buf[1]=Command_Buf[0]=0;
		for(i=0,j=0; i<6; i++) {
			if((*Memory_current_address==',')||(FileSize==0))
				break;
			else {
				Command_Buf[j++]=*(Memory_current_address++);
				FileSize--;
			}
		}
		if((*(Memory_current_address++)!=',')||(FileSize==0)) {
			FS_FClose(Wave_File);
			free(Memory_start_address);
			sprintf(mybuffer,"Command Number Error or File Error");
			ShowMessage(mybuffer);
			return 0;
		}
		FileSize--;
		Command_Number=atoi(Command_Buf);
		Memory_current_address++;/*0x0D*/
		FileSize--;
		Memory_current_address++;/*0x0A*/
		FileSize--;

		for(k=0; k<Command_Number; k++) {
			Command_Buf[5]=Command_Buf[4]=Command_Buf[3]=Command_Buf[2]=Command_Buf[1]=Command_Buf[0]=0;
			for(i=0,j=0; i<6; i++) {
				if((*Memory_current_address==',')||(FileSize==0))
					break;
				else {
					Command_Buf[j++]=*(Memory_current_address++);
					FileSize--;
				}
			}
			if((*(Memory_current_address++)!=',')||(FileSize==0)) {
				FS_FClose(Wave_File);
				free(Memory_start_address);
				sprintf(mybuffer,"Command CMD Error or File Error");
				ShowMessage(mybuffer);
				return 0;
			}
			FileSize--;
			if(atoi(Command_Buf)<256)
				P3K_CMD = atoi(Command_Buf);
			else {
				FS_FClose(Wave_File);
				free(Memory_start_address);
				sprintf(mybuffer,"Command CMD Over 255");
				ShowMessage(mybuffer);
				return 0;
			}
			Command_Buf[5]=Command_Buf[4]=Command_Buf[3]=Command_Buf[2]=Command_Buf[1]=Command_Buf[0]=0;
			for(i=0,j=0; i<6; i++) {
				if((*Memory_current_address==0x0D)||(FileSize==0))
					break;
				else {
					Command_Buf[j++]=*(Memory_current_address++);
					FileSize--;
				}
			}
			if((*(Memory_current_address++)!=0x0D)||(FileSize==0)) {
				FS_FClose(Wave_File);
				free((void *)Memory_start_address);
				sprintf(mybuffer,"Command Data Error or File Error");
				ShowMessage(mybuffer);
				return 0;
			}
			FileSize--;
			if(atoi(Command_Buf)<65536)
				P3K_DATA=atoi(Command_Buf);
			else {
				FS_FClose(Wave_File);
				free((void *)Memory_start_address);
				sprintf(mybuffer,"Command Data Over 65535");
				ShowMessage(mybuffer);
				return 0;
			}
			Memory_current_address++;/*0x0A*/
			FileSize--;
			SPROT0_CMD = 0x00000000 + (P3K_CMD<<24)+P3K_DATA;
			sport0Write(SPROT0_CMD);
			if(Prog_Load==P3k_Chan_Data.Load_Type) {
				sprintf(mybuffer,"CMD=%d,Data=%d",P3K_CMD,P3K_DATA);
				ShowMessage(mybuffer);
				//printf("%s",mybuffer);
				OSTimeDly(200);
			}
		}
		FS_FClose(Wave_File);
		free((void *)Memory_start_address);
	}
	return 1;
}
char Read_File_Data[81920];
BYTE File_Test_FPGA (char *FileName)	// 2010_03
{
	char temp_fname[maxdirlen];
	unsigned short i, Number, FPGA_Data;
	unsigned long SPROT0_CMD;
	unsigned char  Command;
	WORD Send_Number;
	FS_FILE *Wave_File;
	LONG fptr, FileSize;
	char *ptr;

	sprintf(temp_fname, "%s\\%s", FMnowPath, FileName);
	if( (Wave_File=FS_FOpen(temp_fname, "rb") )==0)
		return 0;
	else {
		FS_FSeek(Wave_File, 0, FS_SEEK_END);
		FileSize=FS_FTell(Wave_File);
		FS_FSeek(Wave_File,0,SEEK_SET);
		FS_FRead(Read_File_Data, sizeof(char), FileSize, Wave_File);
		FS_FClose(Wave_File);
		if(FileSize>sizeof(Read_File_Data)) {
#if Normal_TEST
			printf("File Size Over %d Bytes\n",sizeof(Read_File_Data));
#endif
			return 0;
		}

		ptr = Read_File_Data;
		Command  = FPGA_Data = fptr = Number = 0;
		while(fptr < FileSize) {
			if((*(ptr + fptr) >= '0')||(*(ptr + fptr) <= '9'))sscanf(ptr + fptr, "%d", &i);
			else  printf("Convert => Error!\n");
			while(++fptr < FileSize) {
				if(*(ptr + fptr)== ',') {
					if(i>255)FPGA_Data = i;
					else Command = i;
					fptr++;
					break;
				}
				if(*(ptr + fptr)== '\r')FPGA_Data = i;
				if(*(ptr + fptr) == '\n') {
					//printf("Number=%d\n",Number);
					++Number;
					SPROT0_CMD=0x00000000+(Command<<24)+FPGA_Data;
					sport0Write(SPROT0_CMD);
					i = 0;
					//printf("No.%03u Comm => %03u Send => %05u Read => %05u\n", Number, Command, FPGA_Data, i);
					if(Prog_Load==P3k_Chan_Data.Load_Type) {
						sprintf(mybuffer,"N => %03u C => %03u S => %05u R => %05u\n", Number, Command, FPGA_Data, i);
						//printf("%s",mybuffer);
						ShowMessage(mybuffer);
						OSTimeDly(50);
					}
					Command  = FPGA_Data = 0,fptr++;
					break;
				}
			}
		}
		//printf("Convert => Finish\n");
	}
	return 1;
}

void WrinteSystemInfo_usb(void)
{
	char str[20];
	char p3k_Model_Number[20];

	Serial_Number_Str	*Serial = &P3k_Serial_Number;
	if(Serial->Version == TEXIO_Version) {
		if(MODEL3031E==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "LSG-175");
		else if(MODEL3032E==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "LSG-350");		
		else
			sprintf( p3k_Model_Number, "LSG-Default");
	} else {		
		if(MODEL3031E==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "PEL-3031E");
		else if(MODEL3032E==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "PEL-3032E");		
		else
			sprintf( p3k_Model_Number, "PEL-Default");
	}
	sprintf( str,	" %d.%02d.%03d",Main_Version,Sub_Version,Machine_Number);
	WriteFileDate_string("",0);
	WriteFileDate_string("",0);
	WriteFileDate_string(p3k_Model_Number,0);
	//WriteFileDate_string("",0);
	WriteFileDate_string(str,1);
	WriteFileDate_string("",1);

}



extern UWORD Current_Raw[1024],Record_Count;
extern float Old_Curr_Raw[1024],Display_Curr[1024];
BYTE Save_1K_Meas_Data(BYTE chnum, BYTE x)
{
	char *Start_Wave_ptr;
	char str[50];
	ULONG File_Size;
	UWORD i;
	UBYTE *Acq_4K_Meas_Data;

	if(USB_Exist!=USB_Status) {
		sprintf(mybuffer," USB Not Exist or USB Busy,Please Try Again!! ");
		ShowMessage(mybuffer);
		return 0;
	}

	sprintf(mybuffer,"Save 1K Meas Data in %s",SaveResultFileName);
	ShowMessage(mybuffer);

	Acq_4K_Meas_Data = malloc(1024*100);
	if (Acq_4K_Meas_Data == 0) {
		printf("Heap allocation error\n");
		sprintf(mybuffer,"No Memory %d size",1024*100);
		ShowMessage(mybuffer);
		return 0;
	}

	wave_ptr = (char *)Acq_4K_Meas_Data;
	Start_Wave_ptr = wave_ptr;
	WriteFileDate_string("Catch Measure",0);
	WrinteSystemInfo_usb();
	WriteFileDate_string("Number",0);
	WriteFileDate_string("Current Raw Data",0);
	WriteFileDate_string("Old Current Data",0);
	WriteFileDate_string("Disp Current Data",1);

	for(i=0 ; i<1024 ; i++) {
		sprintf( str, " %04d " , i+1 );
		WriteFileDate_string(str,0);
		sprintf( str, " %d " ,Current_Raw[i] );
		WriteFileDate_string(str,0);
		sprintf( str, " %f " , Old_Curr_Raw[i] );
		WriteFileDate_string(str,0);
		sprintf( str, " %f " , Display_Curr[i] );
		WriteFileDate_string(str,1);
	}

	File_Size = wave_ptr - Start_Wave_ptr;
	WriteFile(Start_Wave_ptr, File_Size, SaveResultFileName);
	FMinfo|=FM_READ_DEVICE;
	OSTimeDly(2);
	free((void *)Acq_4K_Meas_Data);
	sprintf(mybuffer,"%s Save Finish",SaveResultFileName);
	ShowMessage(mybuffer);
	return 1;
}
void WriteRunRecordFile(void){
	char *Start_Wave_ptr;
	char str[50];
	ULONG File_Size;
	UWORD i;
	const char Meas_Alarm[14][20]={" none "," OTP "," RVP "," OVP "," UVP "," Para "," OPP "," OCP "," ROPP "," ROCP "," F.ROCP "," UnReg ", " Ext.OV "," Alarm "};
	
	UBYTE *Printf_RunRecord_Data;
	if(USB_Exist!=USB_Status) {
		sprintf(mybuffer," USB Not Exist or USB Busy,Please Try Again!! ");
		ShowMessage(mybuffer);
		return;
	}	
	sprintf(mybuffer,"Save Cal Data in %s",SaveResultFileName);
	ShowMessage(mybuffer);
	Printf_RunRecord_Data = malloc(600*100);
	if (Printf_RunRecord_Data == 0) {
		printf("Heap allocation error\n");
		sprintf(mybuffer,"No Memory %d size",600*100);
		ShowMessage(mybuffer);
		return;
	}
	wave_ptr = (char *)Printf_RunRecord_Data;
	Start_Wave_ptr = wave_ptr;
	WriteFileDate_string("Running Record",0);
	WrinteSystemInfo_usb();
	//-----------------------------------------
	WriteFileDate_string("SystemTime",0);
	WriteFileDate_string("CMD",0);
	WriteFileDate_string("DATA(hex)",0);
	WriteFileDate_string("DATA(10)",0);
	WriteFileDate_string("Alarm",1);
	//-----------------------------------------
	for(i=0;i<SetHistroy.RecCnt;i++){
		sprintf( str, "%d sec" , SetHistroy.Info.time[i]);
		WriteFileDate_string(str,0);
		sprintf( str, "0x%02X" , SetHistroy.Info.cmd[i]);
		WriteFileDate_string(str,0);
		sprintf( str, "0x%04X" , SetHistroy.Info.data[i]);
		WriteFileDate_string(str,0);
		sprintf( str, "%d" , SetHistroy.Info.data[i]);
		WriteFileDate_string(str,0);		
		sprintf( str, "%s" , Meas_Alarm[SetHistroy.Info.mode[i]]);
		WriteFileDate_string(str,1);
	}

	File_Size=wave_ptr - Start_Wave_ptr;
	WriteFile(Start_Wave_ptr, File_Size, SaveResultFileName);
	FMinfo|=FM_READ_DEVICE;
	OSTimeDly(2);
	free((void *)Printf_RunRecord_Data);
	sprintf(mybuffer,"%s Save Finish",SaveResultFileName);
	ShowMessage(mybuffer);
}

BYTE Save_Acq_4K_Meas_Data(BYTE chnum, BYTE x)
{
	char *Start_Wave_ptr;
	char str[50];
	ULONG File_Size;
	UWORD i;
	UBYTE *Acq_4K_Meas_Data;

	if(USB_Exist!=USB_Status) {
		sprintf(mybuffer," USB Not Exist or USB Busy,Please Try Again!! ");
		ShowMessage(mybuffer);
		return 0;
	}

	sprintf(mybuffer,"Save 4K Acq Data in %s",SaveResultFileName);
	ShowMessage(mybuffer);

	Acq_4K_Meas_Data = malloc(4100*100);
	if (Acq_4K_Meas_Data == 0) {
		printf("Heap allocation error\n");
		sprintf(mybuffer,"No Memory %d size",4100*100);
		ShowMessage(mybuffer);
		return 0;
	}

	wave_ptr = (char *)Acq_4K_Meas_Data;
	Start_Wave_ptr = wave_ptr;

	WriteFileDate_string("Acq4K Interval(us)",0);
	sprintf( str, "%d" , p3k_Acq_4K_Measure_Data.Acq4K_Interval);
	WriteFileDate_string(str,1);

	WriteFileDate_string("Acq4K Pre-Trigger Counter",0);
	sprintf( str, "%d" , p3k_Acq_4K_Measure_Data.Acq4K_PTC);
	WriteFileDate_string(str,1);

	WriteFileDate_string("Acq4K Sweep Counter",0);
	sprintf( str, "%d" , p3k_Acq_4K_Measure_Data.Acq4K_SWC);
	WriteFileDate_string(str,1);

	WriteFileDate_string("Acq4K CC Resolution",0);
	sprintf( str, "%f" , p3k_Acq_4K_Measure_Data.CC_Resolution);
	WriteFileDate_string(str,1);

	WriteFileDate_string("Acq4K CV Resolution",0);
	sprintf( str, "%f" , p3k_Acq_4K_Measure_Data.CV_Resolution);
	WriteFileDate_string(str,1);

	WriteFileDate_string("Number",0);
	WriteFileDate_string("Voltage",0);
	WriteFileDate_string("Current",0);
	WriteFileDate_string("Watt",1);

	for(i=0 ; i<4096 ; i++) {
		sprintf( str, " %04d " , i+1 );
		WriteFileDate_string(str,0);
		sprintf( str, " %f " , p3k_Acq_4K_Measure_Data.VOLT[i] );
		WriteFileDate_string(str,0);
		sprintf( str, " %f " , p3k_Acq_4K_Measure_Data.CURR[i] );
		WriteFileDate_string(str,0);
		sprintf( str, " %f " , p3k_Acq_4K_Measure_Data.WATT[i] );
		WriteFileDate_string(str,1);
	}

	File_Size=wave_ptr - Start_Wave_ptr;
	WriteFile(Start_Wave_ptr, File_Size, SaveResultFileName);
	FMinfo|=FM_READ_DEVICE;
	OSTimeDly(2);
	free((void *)Acq_4K_Meas_Data);
	sprintf(mybuffer,"%s Save Finish",SaveResultFileName);
	ShowMessage(mybuffer);
	return 1;
}

BYTE Save_CalData_To_USB(BYTE chnum, BYTE x)
{
	char *Start_Wave_ptr;
	char str[50];
	ULONG File_Size;
	UWORD i;
	UBYTE *Printf_Cal_Data;
	if(USB_Exist!=USB_Status) {
		sprintf(mybuffer," USB Not Exist or USB Busy,Please Try Again!! ");
		ShowMessage(mybuffer);
		return 0;
	}

	sprintf(mybuffer,"Save Cal Data in %s",SaveResultFileName);
	ShowMessage(mybuffer);

	Printf_Cal_Data = malloc(600*100);
	if (Printf_Cal_Data == 0) {
		printf("Heap allocation error\n");
		sprintf(mybuffer,"No Memory %d size",600*100);
		ShowMessage(mybuffer);
		return 0;
	}

	wave_ptr = (char *)Printf_Cal_Data;
	Start_Wave_ptr = wave_ptr;
	WriteFileDate_string("Calibration Parameter",0);
	WrinteSystemInfo_usb();
	//-----------------------------------------
	WriteFileDate_string("Mode",0);
	WriteFileDate_string("Gain",0);
	WriteFileDate_string("Offset",1);
	//-----------------------------------------
	WriteFileDate_string("",1);
	WriteFileDate_string("ADJ_Offset",1);

	WriteFileDate_string("ADJ_Offset_CCH",0);
	sprintf( str, "%d" , p3k_Cal_data.CC_offseAdj[1]);
	WriteFileDate_string(str,1);
	WriteFileDate_string("ADJ_Offset_CCL",0);
	sprintf( str, "%d" , p3k_Cal_data.CC_offseAdj[0]);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ADJ_Offset_CRH",0);
	sprintf( str, "%d" , p3k_Cal_data.CR_offseAdj[1]);
	WriteFileDate_string(str,1);
	WriteFileDate_string("ADJ_Offset_CRL",0);
	sprintf( str, "%d" , p3k_Cal_data.CR_offseAdj[0]);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ADJ_Offset_CPH",0);
	sprintf( str, "%d" , p3k_Cal_data.CP_offseAdj[1]);
	WriteFileDate_string(str,1);
	WriteFileDate_string("ADJ_Offset_CPL",0);
	sprintf( str, "%d" , p3k_Cal_data.CP_offseAdj[0]);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ADJ_Offset_CVH",0);
	sprintf( str, "%d" , p3k_Cal_data.CV_offseAdj[1]);
	WriteFileDate_string(str,1);
	WriteFileDate_string("ADJ_Offset_CVL",0);
	sprintf( str, "%d" , p3k_Cal_data.CV_offseAdj[0]);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ADJ_Offset_Ext_RH",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_R_offseAdj[1]);
	WriteFileDate_string(str,1);
	WriteFileDate_string("ADJ_Offset_Ext_RL",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_R_offseAdj[0]);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ADJ_Offset_Ext_VH",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_V_offseAdj[1]);
	WriteFileDate_string(str,1);
	WriteFileDate_string("ADJ_Offset_Ext_VL",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_V_offseAdj[0]);
	WriteFileDate_string(str,1);
	
	//-----------------------------------------
	WriteFileDate_string("",1);
	WriteFileDate_string("SETTING",1);

	WriteFileDate_string("CCH",0);
	sprintf( str, "%1.4f" , p3k_Cal_data.CC_Data[1].Cal_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%1.4f" , p3k_Cal_data.CC_Data[1].Cal_Value_Offset);
	WriteFileDate_string(str,1);

	WriteFileDate_string("CCL",0);
	sprintf( str, "%1.4f" , p3k_Cal_data.CC_Data[0].Cal_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%1.4f" , p3k_Cal_data.CC_Data[0].Cal_Value_Offset);
	WriteFileDate_string(str,1);

	WriteFileDate_string("CRH",0);
	sprintf( str, "%1.4f" , p3k_Cal_data.CR_Data[1].Cal_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%1.4f" , p3k_Cal_data.CR_Data[1].Cal_Value_Offset);
	WriteFileDate_string(str,1);

	WriteFileDate_string("CRL",0);
	sprintf( str, "%1.4f" , p3k_Cal_data.CR_Data[0].Cal_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%1.4f" , p3k_Cal_data.CR_Data[0].Cal_Value_Offset);
	WriteFileDate_string(str,1);

	WriteFileDate_string("CVH",0);
	sprintf( str, "%1.4f" , p3k_Cal_data.CV_Data[1].Cal_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%1.4f" , p3k_Cal_data.CV_Data[1].Cal_Value_Offset);
	WriteFileDate_string(str,1);

	WriteFileDate_string("CVL",0);
	sprintf( str, "%1.4f" , p3k_Cal_data.CV_Data[0].Cal_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%1.4f" , p3k_Cal_data.CV_Data[0].Cal_Value_Offset);
	WriteFileDate_string(str,1);

	WriteFileDate_string("CPH",0);
	sprintf( str, "%1.4f" , p3k_Cal_data.CP_Data[1].Cal_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%1.4f" , p3k_Cal_data.CP_Data[1].Cal_Value_Offset);
	WriteFileDate_string(str,1);

	WriteFileDate_string("CPL",0);
	sprintf( str, "%1.4f" , p3k_Cal_data.CP_Data[0].Cal_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%1.4f" , p3k_Cal_data.CP_Data[0].Cal_Value_Offset);
	WriteFileDate_string(str,1);

	WriteFileDate_string("IMON_H",0);
	sprintf( str, "%d" , p3k_Cal_data.Rear_IMON[1]);
	WriteFileDate_string(str,1);
	WriteFileDate_string("IMON_L",0);
	sprintf( str, "%d" , p3k_Cal_data.Rear_IMON[0]);
	WriteFileDate_string(str,1);

	WriteFileDate_string("EXT_VH",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_V_CC[1]);
	WriteFileDate_string(str,1);
	WriteFileDate_string("EXT_VL",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_V_CC[0]);
	WriteFileDate_string(str,1);

	WriteFileDate_string("EXT_CC_RH",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_R_CC[1]);
	WriteFileDate_string(str,1);
	WriteFileDate_string("EXT_CC_RL",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_R_CC[0]);
	WriteFileDate_string(str,1);

	WriteFileDate_string("EXT_CR_RH",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_R_CR[1]);
	WriteFileDate_string(str,1);
	WriteFileDate_string("EXT_CR_RL",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_R_CR[0]);
	WriteFileDate_string(str,1);

	WriteFileDate_string("EXT_CV_RH",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_R_CV[1]);
	WriteFileDate_string(str,1);
	WriteFileDate_string("EXT_CV_RL",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_R_CV[0]);
	WriteFileDate_string(str,1);

	WriteFileDate_string("EXT_CP_RH",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_R_CP[1]);
	WriteFileDate_string(str,1);
	WriteFileDate_string("EXT_CP_RL",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_R_CP[0]);
	WriteFileDate_string(str,1);
	
	//-----------------------------------------
	WriteFileDate_string("",1);
	WriteFileDate_string("MEASURE",1);
//Measure
	WriteFileDate_string("M_Volt_H",0);
	sprintf( str, "%d" , p3k_Cal_data.Volt[1].Meas_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%d" , (p3k_Cal_data.Volt[1].Meas_Value_Gain*p3k_Cal_data.Volt[1].Meas_Value_Offset)>>16);
	WriteFileDate_string(str,1);

	WriteFileDate_string("M_Volt_L",0);
	sprintf( str, "%d" , p3k_Cal_data.Volt[0].Meas_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%d" , (p3k_Cal_data.Volt[0].Meas_Value_Gain*p3k_Cal_data.Volt[0].Meas_Value_Offset)>>16);
	WriteFileDate_string(str,1);

	WriteFileDate_string("M_Curr_H",0);
	sprintf( str, "%d" , p3k_Cal_data.Curr[1].Meas_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%d" , (p3k_Cal_data.Curr[1].Meas_Value_Gain*p3k_Cal_data.Curr[1].Meas_Value_Offset)>>16);
	WriteFileDate_string(str,1);

	WriteFileDate_string("M_Curr_L",0);
	sprintf( str, "%d" , p3k_Cal_data.Curr[0].Meas_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%d" , (p3k_Cal_data.Curr[0].Meas_Value_Gain*p3k_Cal_data.Curr[0].Meas_Value_Offset)>>16);
	WriteFileDate_string(str,1);

	WriteFileDate_string("M_EXT_V_CURR_H",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_V_Curr[1].Meas_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%d" , (p3k_Cal_data.Ext_V_Curr[1].Meas_Value_Gain*p3k_Cal_data.Ext_V_Curr[1].Meas_Value_Offset)>>16);
	WriteFileDate_string(str,1);

	WriteFileDate_string("M_EXT_V_CURR_L",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_V_Curr[0].Meas_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%d" , (p3k_Cal_data.Ext_V_Curr[0].Meas_Value_Gain*p3k_Cal_data.Ext_V_Curr[0].Meas_Value_Offset)>>16);
	WriteFileDate_string(str,1);

	WriteFileDate_string("M_EXT_V_VOLT_H",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_V_Volt[1].Meas_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%d" , (p3k_Cal_data.Ext_V_Volt[1].Meas_Value_Gain*p3k_Cal_data.Ext_V_Volt[1].Meas_Value_Offset)>>16);
	WriteFileDate_string(str,1);

	WriteFileDate_string("M_EXT_V_VOLT_L",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_V_Volt[0].Meas_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%d" , (p3k_Cal_data.Ext_V_Volt[0].Meas_Value_Gain*p3k_Cal_data.Ext_V_Volt[0].Meas_Value_Offset)>>16);
	WriteFileDate_string(str,1);

	WriteFileDate_string("M_EXT_R_CURR_H",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_R_Curr[1].Meas_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%d" , (p3k_Cal_data.Ext_R_Curr[1].Meas_Value_Gain*p3k_Cal_data.Ext_R_Curr[1].Meas_Value_Offset)>>16);
	WriteFileDate_string(str,1);

	WriteFileDate_string("M_EXT_R_CURR_L",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_R_Curr[0].Meas_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%d" , (p3k_Cal_data.Ext_R_Curr[0].Meas_Value_Gain*p3k_Cal_data.Ext_R_Curr[0].Meas_Value_Offset)>>16);
	WriteFileDate_string(str,1);

	WriteFileDate_string("M_EXT_R_VOLT_H",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_R_Volt[1].Meas_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%d" , (p3k_Cal_data.Ext_R_Volt[1].Meas_Value_Gain*p3k_Cal_data.Ext_R_Volt[1].Meas_Value_Offset)>>16);
	WriteFileDate_string(str,1);

	WriteFileDate_string("M_EXT_R_VOLT_L",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_R_Volt[0].Meas_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%d" , (p3k_Cal_data.Ext_R_Volt[0].Meas_Value_Gain*p3k_Cal_data.Ext_R_Volt[0].Meas_Value_Offset)>>16);
	WriteFileDate_string(str,1);
	//--------------------------------------------------------------
	WriteFileDate_string("",1);
	WriteFileDate_string("Ext Sensor",1);
// Ext Sensor
	WriteFileDate_string("EXT_Sorser_V",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_V_Sense.Meas_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%d" , (p3k_Cal_data.Ext_V_Sense.Meas_Value_Gain*p3k_Cal_data.Ext_V_Sense.Meas_Value_Offset)>>16);
	WriteFileDate_string(str,1);

	WriteFileDate_string("EXT_Sorser_R",0);
	sprintf( str, "%d" , p3k_Cal_data.Ext_R_Sense.Meas_Value_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%d" , (p3k_Cal_data.Ext_R_Sense.Meas_Value_Gain*p3k_Cal_data.Ext_R_Sense.Meas_Value_Offset)>>16);
	WriteFileDate_string(str,1);



	//-----------------------------------------
	WriteFileDate_string("",1);
	WriteFileDate_string("PROTECION",1);

	WriteFileDate_string("OCP_H",0);
	sprintf( str, "%d" , p3k_Cal_data.Protection[1].OCP);
	WriteFileDate_string(str,1);

	WriteFileDate_string("OCP_L",0);
	sprintf( str, "%d" , p3k_Cal_data.Protection[0].OCP);
	WriteFileDate_string(str,1);

	WriteFileDate_string("OCP_H_Cal_Data",0);
	sprintf( str, "%1.4f" , p3k_Cal_data.Protection[1].OCP_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%1.4f" , p3k_Cal_data.Protection[1].OCP_Offset);
	WriteFileDate_string(str,1);

	WriteFileDate_string("OCP_L_Cal_Data",0);
	sprintf( str, "%1.4f" , p3k_Cal_data.Protection[0].OCP_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%1.4f" , p3k_Cal_data.Protection[0].OCP_Offset);
	WriteFileDate_string(str,1);


	WriteFileDate_string("OPP_H",0);
	sprintf( str, "%d" , p3k_Cal_data.Protection[1].OPP);
	WriteFileDate_string(str,1);

	WriteFileDate_string("OPP_L",0);
	sprintf( str, "%d" , p3k_Cal_data.Protection[0].OPP);
	WriteFileDate_string(str,1);

	WriteFileDate_string("OPP_H_Cal_Data",0);
	sprintf( str, "%1.4f" , p3k_Cal_data.Protection[1].OPP_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%1.4f" , p3k_Cal_data.Protection[1].OPP_Offset);
	WriteFileDate_string(str,1);

	WriteFileDate_string("OPP_L_Cal_Data",0);
	sprintf( str, "%1.4f" , p3k_Cal_data.Protection[0].OPP_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%1.4f" , p3k_Cal_data.Protection[0].OPP_Offset);
	WriteFileDate_string(str,1);

	WriteFileDate_string("CPP_H",0);
	sprintf( str, "%d" , p3k_Cal_data.Protection[1].CPP);
	WriteFileDate_string(str,1);

	WriteFileDate_string("CPP_L",0);
	sprintf( str, "%d" , p3k_Cal_data.Protection[0].CPP);
	WriteFileDate_string(str,1);

	WriteFileDate_string("CPP_H_Cal_Data",0);
	sprintf( str, "%1.4f" , p3k_Cal_data.Protection[1].CPP_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%1.4f" , p3k_Cal_data.Protection[1].CPP_Offset);
	WriteFileDate_string(str,1);

	WriteFileDate_string("CPP_L_Cal_Data",0);
	sprintf( str, "%1.4f" , p3k_Cal_data.Protection[0].CPP_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%1.4f" , p3k_Cal_data.Protection[0].CPP_Offset);
	WriteFileDate_string(str,1);

	WriteFileDate_string("CXCV_H_Cal_Data",0);
	sprintf( str, "%1.4f" , p3k_Cal_data.Protection[1].CxCV_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%1.4f" , p3k_Cal_data.Protection[1].CxCV_Offset);
	WriteFileDate_string(str,0);
	sprintf( str, "%d" , p3k_Cal_data.Protection[1].CxCV);
	WriteFileDate_string(str,1);

	WriteFileDate_string("CXCV_L_Cal_Data",0);
	sprintf( str, "%1.4f" , p3k_Cal_data.Protection[0].CxCV_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%1.4f" , p3k_Cal_data.Protection[0].CxCV_Offset);
	WriteFileDate_string(str,0);
	sprintf( str, "%d" , p3k_Cal_data.Protection[1].CxCV);
	WriteFileDate_string(str,1);

	//-----------------------------------------
	WriteFileDate_string("",1);
	WriteFileDate_string("P_SENSOR",1);

	WriteFileDate_string("P_Sensor_XH",0);
	sprintf( str, "%d" , p3k_Cal_data.PSensor.XH_Value);
	WriteFileDate_string(str,1);
	WriteFileDate_string("P_Sensor_YH",0);
	sprintf( str, "%d" , p3k_Cal_data.PSensor.YH_Value);
	WriteFileDate_string(str,1);
	WriteFileDate_string("P_Sensor_ZH",0);
	sprintf( str, "%d" , p3k_Cal_data.PSensor.ZH_Value);
	WriteFileDate_string(str,1);
	WriteFileDate_string("P_Sensor_XL",0);
	sprintf( str, "%d" , p3k_Cal_data.PSensor.XL_Value);
	WriteFileDate_string(str,1);
	WriteFileDate_string("P_Sensor_YL",0);
	sprintf( str, "%d" , p3k_Cal_data.PSensor.YL_Value);
	WriteFileDate_string(str,1);
	WriteFileDate_string("P_Sensor_ZL",0);
	sprintf( str, "%d" , p3k_Cal_data.PSensor.ZL_Value);
	WriteFileDate_string(str,1);
#if 0
	WriteFileDate_string("ROCP_H",0);
	sprintf( str, "%d" , p3k_Cal_data.Protection[2].Rating_OCP);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ROCP_M",0);
	sprintf( str, "%d" , p3k_Cal_data.Protection[1].Rating_OCP);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ROCP_L",0);
	sprintf( str, "%d" , p3k_Cal_data.Protection[0].Rating_OCP);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ROCP_H_Cal_Data",0);
	sprintf( str, "%f" , p3k_Cal_data.Protection[2].Rating_OCP_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%f" , p3k_Cal_data.Protection[2].Rating_OCP_Offset);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ROCP_M_Cal_Data",0);
	sprintf( str, "%f" , p3k_Cal_data.Protection[1].Rating_OCP_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%f" , p3k_Cal_data.Protection[1].Rating_OCP_Offset);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ROCP_L_Cal_Data",0);
	sprintf( str, "%f" , p3k_Cal_data.Protection[0].Rating_OCP_Gain);
	WriteFileDate_string(str,0);
	sprintf( str, "%f" , p3k_Cal_data.Protection[0].Rating_OCP_Offset);
	WriteFileDate_string(str,1);
#endif


	File_Size=wave_ptr - Start_Wave_ptr;
	WriteFile(Start_Wave_ptr, File_Size, SaveResultFileName);
	FMinfo|=FM_READ_DEVICE;
	OSTimeDly(2);
	free((void *)Printf_Cal_Data);
	sprintf(mybuffer,"%s Save Finish",SaveResultFileName);
	ShowMessage(mybuffer);
	return 1;
}
BYTE Save_FPGA_register(BYTE chnum, BYTE x)
{
	char *Start_Wave_ptr;
	char str[50];
	ULONG File_Size;
	UWORD i;
	UBYTE *Printf_Cal_Data;
	if(USB_Exist!=USB_Status) {
		sprintf(mybuffer," USB Not Exist !! ");
		ShowMessage(mybuffer);
		return 0;
	}

	sprintf(mybuffer,"Save FPGA in %s",SaveResultFileName);
	ShowMessage(mybuffer);

	Printf_Cal_Data = malloc(600*100);
	if (Printf_Cal_Data == 0) {
		printf("Heap allocation error\n");
		sprintf(mybuffer,"No Memory %d size",600*100);
		ShowMessage(mybuffer);
		return 0;
	}

	wave_ptr = (char *)Printf_Cal_Data;
	Start_Wave_ptr = wave_ptr;

#if 1
	WriteFileDate_string("FPGA Register Record",0);
	WrinteSystemInfo_usb();
	WriteFileDate_string("CMD",0);
	WriteFileDate_string("Wrinte(hex)",0);
	WriteFileDate_string("Wrinte(10)",0);
	WriteFileDate_string("Read(hex)",0);
	WriteFileDate_string("Read(10)",1);

	for(i=0; i<256; i++) {
		sprintf( str, "0x%02X:" , i);
		WriteFileDate_string(str,0);
		sprintf( str, "0x%04X" , FPGA_W[i]);
		WriteFileDate_string(str,0);
		sprintf( str, "%05d" , FPGA_W[i]);
		WriteFileDate_string(str,0);
		sprintf( str, "0x%04X" , FPGA_R[i]);
		WriteFileDate_string(str,0);
		sprintf( str, "%05d" , FPGA_R[i]);
		WriteFileDate_string(str,1);
	}
#endif
	File_Size=wave_ptr - Start_Wave_ptr;
	WriteFile(Start_Wave_ptr, File_Size, SaveResultFileName);
	FMinfo|=FM_READ_DEVICE;
	OSTimeDly(2);
	free((void *)Printf_Cal_Data);
	sprintf(mybuffer,"%s Save Finish",SaveResultFileName);
	ShowMessage(mybuffer);
	return 1;
}
BYTE Save_CalBackup_To_USB(BYTE chnum, BYTE x)
{
	char *Start_Wave_ptr;
	char str[50];
	ULONG File_Size;
	UWORD i;
	UBYTE *Printf_Cal_Data;
	UBYTE *Cal_Data_Curr;
	char SaveResultSDA[30];
	unsigned short checksum;

	if(USB_Exist!=USB_Status) {
		sprintf(mybuffer," USB Not Exist!! ");
		ShowMessage(mybuffer);
		return 0;
	}
	for(i=0; i<30; i++) {
		SaveResultSDA[i]=SaveResultFileName[i];
	}
	SaveResultSDA[9]='C';
	SaveResultSDA[10]='A';
	SaveResultSDA[11]='L';
	sprintf(mybuffer,"Save Cal Data in %s",SaveResultSDA);
	ShowMessage(mybuffer);
	Printf_Cal_Data = malloc(200*100);
	if (Printf_Cal_Data == 0) {
		printf("Heap allocation error\n");
		sprintf(mybuffer,"No Memory %d size",200*100);
		ShowMessage(mybuffer);
		return 0;
	}
	wave_ptr = (char *)Printf_Cal_Data;
	Start_Wave_ptr = wave_ptr;
	Cal_Data_Curr = (UBYTE*)&p3k_Cal_data;
	for(i=0; i<1000; i++) *(wave_ptr++) = *(Cal_Data_Curr++);

	File_Size=wave_ptr - Start_Wave_ptr;
	WriteFile(Start_Wave_ptr, File_Size, SaveResultSDA);
	FMinfo|=FM_READ_DEVICE;
	OSTimeDly(2);
	free((void *)Printf_Cal_Data);
	sprintf(mybuffer,"%s Save Finish",SaveResultSDA);
	ShowMessage(mybuffer);
	return 1;
}


unsigned char debugmode=0;
BYTE DebugToolSelet(BYTE chnum, BYTE x)
{
	debugmode++;
	DispMode = DispMode_BROWSE_ITEMS;
#if debug_tool	
	if (debugmode>2)debugmode = 0;
	FPGA_test_cnt = 0;
	FPGA_err_cnt = 0;
	FPGA_test_status = 0;
#else
	if (debugmode>1)debugmode = 0;
#endif
	DataRedrawFlag |= DATA_CHANGE;
	ChanRedrawFlag |= BG_CLEAR;
	return 1;
}
BYTE Save_PrintScr_To_USB(BYTE chnum, BYTE x)
{
	G_StatusFlag |= saveBmpFile;
	//KeyInFlag |= SHIFT_KEY;
	PEL3000_LED_Control(LED_PRESET, Switch_ON);
	return 1;
}
extern void clear_struct_data (unsigned char *pta, int size );
BYTE Save_RunRecord_To_USB(BYTE chnum, BYTE x)
{	
	clear_struct_data((unsigned char *)&SetHistroy, sizeof(SetHistroy));
	G_StatusFlag |= saveRunRecordFile;
	PEL3000_LED_Control(LED_PRESET, Switch_ON);
	return 1;
}

BYTE JumpCalValue (BYTE chnum, BYTE x)
{
	M_num = P_Cal_Value;
	ClrDispCnt(1,0,0,0,0,0);
	KeyinBuf[0] =KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
	KeyInFlag&=(~DIGI_KEY_IN);
	Soft_Key_Temp=0;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag|=PARA_CHANGE + BG_CLEAR;
	HelpRedrawFlag &= ~HELP_FUN_ON;
	ChanRedrawFlag |= BG_CLEAR;
	return 1;
}

BYTE DebugToolSave(BYTE chnum, BYTE x)
{
	UBYTE done;
	if(debugmode==0) {
		done = Save_FPGA_register(0,0);
	} else if(debugmode==1) {
		if(DispCT==MeasureMode) {
			done = Save_1K_Meas_Data(0,0);
		} else if(DispCT==CalTxtMode) {
			done = Save_CalData_To_USB(0,0);		
		} else if(DispCT==CalBackup) {
			done = Save_CalBackup_To_USB(0,0);
		} else if(DispCT==printScreen) {
			if((KeyInFlag&PRESET_KEY)==0)
				done = Save_PrintScr_To_USB(0,0);	
		} else if(DispCT==RunningRecord) {
			if((KeyInFlag&PRESET_KEY)==0)
				done = Save_RunRecord_To_USB(0,0);	
		}
	}
#if debug_tool
	else if(debugmode==2) {
		FPGA_test_status = 1;
	}
#endif
	return done;
}



BYTE Read_CalDefault(BYTE chnum, BYTE x)
{
	RecoverCalData_DataFlash(0);
	ClrDispCnt(1,0,0,0,0,0);
	KeyinBuf[0] =KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
	KeyInFlag&=(~DIGI_KEY_IN);
	Soft_Key_Temp=0;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag|=PARA_CHANGE + BG_CLEAR;
	HelpRedrawFlag &= ~HELP_FUN_ON;
	ChanRedrawFlag |= BG_CLEAR;
	return 1;
}

void Cal_Init_Proc(void)
{
	p3k_send_tx_list tx_data;
	char val;
	char i;
	if(M_num!=P_CAL_MODE) {
		if(UTILITY.LOAD_CTL)
			Auto_Load_Off();

		Soft_Key_Temp = 0;

		M_num = P_CAL_MODE;
		ClrDispCnt(0,0,0,0,0,0);
		MenuRedrawFlag |= MENU_CHANGE;
		DataRedrawFlag |= PARA_CHANGE+BG_CLEAR;
		/* Init Calibration parameter */
		P3K_CALIBRATION_BAR.MODE	= CC_MODE;
		P3K_CALIBRATION_BAR.POINT	= Cal_High_Point;
		P3K_CALIBRATION_BAR.RANGE	= IRange_High;
		P3K_CALIBRATION_BAR.Cal_PSense_Flag	= 0;

		for(i=0; i<3; i++) {
			if((p3k_Cal_data.CC_offseAdj[i]==0xFFFF)||(p3k_Cal_data.CC_offseAdj[i]<=Calibration_Adj_minValue)||(p3k_Cal_data.CC_offseAdj[i]>Calibration_Adj_maxValue))
				p3k_Cal_data.CC_offseAdj[i]=Calibration_Adj_defalut;
			if((p3k_Cal_data.CR_offseAdj[i]==0xFFFF)||(p3k_Cal_data.CR_offseAdj[i]<=Calibration_Adj_minValue)||(p3k_Cal_data.CR_offseAdj[i]>Calibration_Adj_maxValue))
				p3k_Cal_data.CR_offseAdj[i]=Calibration_Adj_defalut;
			if((p3k_Cal_data.CP_offseAdj[i]==0xFFFF)||(p3k_Cal_data.CP_offseAdj[i]<=Calibration_Adj_minValue)||(p3k_Cal_data.CP_offseAdj[i]>Calibration_Adj_maxValue))
				p3k_Cal_data.CP_offseAdj[i]=Calibration_Adj_defalut;
#if Enable_Ext_CalOffset
			if((p3k_Cal_data.Ext_V_offseAdj[i]==0xFFFF)||(p3k_Cal_data.Ext_V_offseAdj[i]<=Calibration_Adj_minValue)||(p3k_Cal_data.Ext_V_offseAdj[i]>Calibration_Adj_maxValue))
				p3k_Cal_data.Ext_V_offseAdj[i]=Calibration_Adj_defalut;
			if((p3k_Cal_data.Ext_R_offseAdj[i]==0xFFFF)||(p3k_Cal_data.Ext_R_offseAdj[i]<=Calibration_Adj_minValue)||(p3k_Cal_data.Ext_R_offseAdj[i]>Calibration_Adj_maxValue))
				p3k_Cal_data.Ext_R_offseAdj[i]=Calibration_Adj_defalut;
#endif
			p3k_Cal_data.CV_offseAdj[i]=Calibration_Adj_defalut;
		}
		p3k_Cal_data.OffsetFlag = 0 ;
		p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.CC_offseAdj[1]; //Adam_debug 
		Rem_Load_Cal_Default();

		P3K_CALIBRATION_BAR.PSensor = p3k_Cal_data.PSensor;
	}
}

void CalWaitProcess(void)
{
	if(CtrlFlag1&Cal_Wait_moment) {
		CtrlFlag1 &= (~Cal_Wait_moment);
		DataRedrawFlag |= PARA_CHANGE;
		DMA_Update_Flag = 1;
		if(CAL_HI_LOW_SET_OK==0x03) {
			P3K_CALIBRATION_BAR.START = 0x0;
			MenuRedrawFlag |= MENU4_CHANGE;
		}
		if(CAL_HI_LOW_SET_OK)
			return;
		P3K_CALIBRATION_BAR.START = 1;
		MenuRedrawFlag |= MENU4_CHANGE;
	}

}

extern void FloatWindowsDispOn(void);
extern void Float_Windows_Setting(int x1, int y1,int x2, int y2,GUI_COLOR color);
extern void FloatWindows_StringAt(const char GUI_FAR *s, int x, int y);
extern void Wait_For_MDMA_Ready(void);
extern void FloatFrame(int StartX, int StartY,int EndX, int EndY,int frame_width,GUI_COLOR frame_color);
extern void Frame_Change(void);
extern char flag_CPP_OPP;
#if Enable_Ring_Count
extern UWORD UVP_Tone_Count;	
#endif
void Show_Alarm_Message(void)
{
	Wait_For_MDMA_Ready();
	Alarm_logo_flag =1;

	Float_Windows_Setting(50,18,258,42,MEM_BLACK);
	FloatFrame(50,18,258,42,3,MEM_DARKRED_ku);

	GUI_SetFont(Time_Alarm_Font);
	GUI_SetBkColor(MEM_BLACK);
	GUI_SetColor(MEM_DARKRED_ku);
	GUI_SetTextAlign(GUI_TA_LEFT);

	if(OTP_Alarm==p3k_Measure_Data.Alarm)
		FloatWindows_StringAt("  OTP Alarm ",104,82);
	else if(RVP_Alarm==p3k_Measure_Data.Alarm)
		FloatWindows_StringAt("  RVP Alarm ",104,82);
	else if(OVP_Alarm==p3k_Measure_Data.Alarm)
		FloatWindows_StringAt("  OVP Alarm ",104,82);
	else if(UVP_Alarm==p3k_Measure_Data.Alarm){
		FloatWindows_StringAt("  UVP Alarm ",104,82);
#if Enable_Ring_Count
		if(UTILITY.Master_Alarm_Tone)		
			UVP_Tone_Count =P3k_Disp_Data.PROT.UVP_Tone_len; //601;
#endif
	}else if(OPP_Alarm==p3k_Measure_Data.Alarm){
#if Enable_OPPOCP_off		
		if(P3k_Chan_Data.PROT.OPP_SET==2)
			FloatWindows_StringAt(" ROPP Alarm ",104,82);
		else
#endif			
			FloatWindows_StringAt("  OPP Alarm ",104,82);
	}else if(ROCP_Alarm==p3k_Measure_Data.Alarm)
		FloatWindows_StringAt(" ROCP Alarm ",104,82);
	else if(OCP_Alarm==p3k_Measure_Data.Alarm){
		FloatWindows_StringAt("  OCP Alarm ",104,82);
	}else if(CPP_Alarm==p3k_Measure_Data.Alarm)
		FloatWindows_StringAt("  ROPP Alarm ",104,82);
	else if(FCCP_Alarm==p3k_Measure_Data.Alarm)
		FloatWindows_StringAt(" F.ROCP Alarm ",104,82);
	else if(Para_Alarm==p3k_Measure_Data.Alarm)
		FloatWindows_StringAt("  Para Alarm ",104,82);
	else if(UnReg_Alarm==p3k_Measure_Data.Alarm)
		FloatWindows_StringAt(" unReg Alarm ",104,82);
	else if(Ext_Alarm==p3k_Measure_Data.Alarm)
		FloatWindows_StringAt("  Ext. Alarm ",104,82);

	FloatWindows_StringAt(" Please Press Enter ",72,107);
	FloatWindows_StringAt(" To Clear Alarm ",97,132);

	CtrlFlag1 |= Alarm_Latch;
	CtrlFlag1 |= Float_Windows_DispOn;
	DMA_Update_Flag = 1;
}

void AlarmProcess(UBYTE key) //LOAD, SEQ,
{
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	p3k_send_tx_list tx_data;

	if(p3k_Measure_Data.Alarm==0)return;
	if((UTILITY.LOAD_CTL==0)&&(UTILITY.SHORT_CTL==0))return;
	if(CPP_Alarm==p3k_Measure_Data.Alarm)return;
	if(Para_Alarm==p3k_Measure_Data.Alarm)return;
	if(((OCP_Alarm==p3k_Measure_Data.Alarm)&&(Set_Limit==Data_tmp->PROT.OCP_SET)) || ((OPP_Alarm==p3k_Measure_Data.Alarm)&&(Set_Limit==Data_tmp->PROT.OPP_SET))||(UnReg_Alarm==p3k_Measure_Data.Alarm))return;
	///if(ROCP_Alarm==p3k_Measure_Data.Alarm)return;

	if(DGIOCtrlFlag&REM_Mode_Fast) {

	} else {
		Show_Alarm_Message();
		Frame_Change();
	}
	DMA_Update_Flag = 1;
	FunctionFlag   = FUNC_CLEAR;
	UTILITY.LOAD_CTL = Switch_OFF;
	UTILITY.SHORT_CTL = Switch_OFF;
	if(Prog_Load==P3k_Chan_Data.Load_Type) { 	/* Flag of Run Program was turn on */
		Soft_Key_Temp = 0;
		if(UTILITY.LOAD_CTL==Switch_OFF) {
			if(Prog_Seq_Data.Total_Count) {
				if(M_num == P_PROG_EXECUTE)
					M_num = P_PROG_Detail;
			} else {
				M_num = P_PROG_MAIN;		/* into sequence Main */
			}
			SEQ_Save_Status = 0;
			ClrDispCnt(0x00, 0x00, 0x03, 0x00, 0x00, 0x00);
			MenuRedrawFlag |= MENU_CHANGE;
			DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
			ChanRedrawFlag |= BG_CLEAR;
		}
	}
	SysRedrawFlag |= PROG_UPDATA;
	tx_data.ADDRH = Machine_Command;
	tx_data.ADDRL = Machine_Load_OnOff;
	SendTXData(&tx_data);

	PEL3000_LED_Control(LED_SHORT, UTILITY.SHORT_CTL);
	PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
	if((Ext_UnReg_Flag)&&(P3k_Chan_Data.CONF.Ext_Setting.LoadOn_IN)) {
		P3k_Chan_Data.CONF.Ext_Setting.LoadOn_IN = 0;
		P3k_Disp_Data.CONF.Ext_Setting.LoadOn_IN = 0;
	}
	if(key==K_Enter_Key) {
		delaySeqAlarmDisplay = 3;//Adam_2016_0414
	}
}

UBYTE WriteOnBoardFlash(long Start_Page, UBYTE *Data_Point, long Data_Size)
{
	UBYTE *Malloc_Data_Address,str[30];
	UBYTE Write_Result = 1;
	UWORD Page_Sum;
	ULONG Page_Size = 512,i;
	Page_Sum = Data_Size/Page_Size;
	if(Data_Size%Page_Size)
		Page_Sum++;
	WriteIO(DATA_FLASH_SEL, 0); 	/* PF2 map to #1 on board data flash */
	WriteIO(DATA_FLASH_WP,1);		/* Disable write protect */
	ProgramAllUserProgram512(Start_Page,Data_Point,Page_Sum);
	WriteIO(DATA_FLASH_WP,0);		/* Enable write protect */

#if Normal_TEST
	Malloc_Data_Address = malloc(Data_Size);

	CountinueArrayRead512(Start_Page*Page_Size,Malloc_Data_Address,Data_Size);
	for(i=0 ; i<Data_Size ; i++) {
		if( (*(Malloc_Data_Address+i))!=(*(Data_Point+i)) ) {
			printf("Write Data Flash Error\n");
			Write_Result = 0;
			break;
		}
	}
	free(Malloc_Data_Address);
#endif

	return Write_Result;
}

BYTE Save_Cache_Setting_To_USB(BYTE chnum, BYTE x)
{
	char *Start_Wave_ptr;
	char str[50];
	ULONG File_Size;
	UWORD i;
	UBYTE *Printf_Cal_Data;
	if(USB_Exist!=USB_Status) {
		sprintf(mybuffer," USB Not Exist or USB Busy,Please Try Again!! ");
		ShowMessage(mybuffer);
		return 0;
	}

	sprintf(mybuffer,"Save Cache Setting in %s",SaveResultFileName);
	ShowMessage(mybuffer);

	Printf_Cal_Data = malloc(8200*100);
	if (Printf_Cal_Data == 0) {
		printf("Heap allocation error\n");
		sprintf(mybuffer,"No Memory %d size",8200*100);
		ShowMessage(mybuffer);
		return 0;
	}

	wave_ptr = (char *)Printf_Cal_Data;
	Start_Wave_ptr = wave_ptr;

	WriteFileDate_string("SRAM_BASE_ADDRESS",0);
	sprintf( str, "0x%x" , *(unsigned long *)SRAM_BASE_ADDRESS);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DMEM_CONTROL",0);
	sprintf( str, "0x%x" , *(unsigned long *)DMEM_CONTROL);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_STATUS",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_STATUS);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_FAULT_ADDR",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_FAULT_ADDR);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_ADDR0",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_ADDR0);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_ADDR1",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_ADDR1);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_ADDR2",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_ADDR2);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_ADDR3",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_ADDR3);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_ADDR4",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_ADDR4);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_ADDR5",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_ADDR5);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_ADDR6",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_ADDR6);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_ADDR7",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_ADDR7);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_ADDR8",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_ADDR8);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_ADDR9",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_ADDR9);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_ADDR10",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_ADDR10);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_ADDR11",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_ADDR11);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_ADDR12",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_ADDR12);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_ADDR13",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_ADDR13);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_ADDR14",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_ADDR14);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_ADDR15",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_ADDR15);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_DATA0",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_DATA0);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_DATA1",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_DATA1);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_DATA2",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_DATA2);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_DATA3",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_DATA3);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_DATA4",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_DATA4);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_DATA5",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_DATA5);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_DATA6",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_DATA6);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_DATA7",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_DATA7);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_DATA8",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_DATA8);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_DATA9",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_DATA9);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_DATA10",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_DATA10);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_DATA11",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_DATA11);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_DATA12",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_DATA12);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_DATA13",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_DATA13);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_DATA14",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_DATA14);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DCPLB_DATA15",0);
	sprintf( str, "0x%x" , *(unsigned long *)DCPLB_DATA15);
	WriteFileDate_string(str,1);

	WriteFileDate_string("DTEST_COMMAND",0);
	sprintf( str, "0x%x" , *(unsigned long *)DTEST_COMMAND);
	WriteFileDate_string(str,1);

	WriteFileDate_string("IMEM_CONTROL",0);
	sprintf( str, "0x%x" , *(unsigned long *)IMEM_CONTROL);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_STATUS",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_STATUS);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_FAULT_ADDR",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_FAULT_ADDR);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_ADDR0",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_ADDR0);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_ADDR1",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_ADDR1);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_ADDR2",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_ADDR2);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_ADDR3",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_ADDR3);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_ADDR4",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_ADDR4);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_ADDR5",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_ADDR5);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_ADDR6",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_ADDR6);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_ADDR7",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_ADDR7);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_ADDR8",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_ADDR8);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_ADDR9",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_ADDR9);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_ADDR10",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_ADDR10);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_ADDR11",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_ADDR11);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_ADDR12",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_ADDR12);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_ADDR13",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_ADDR13);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_ADDR14",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_ADDR14);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_ADDR15",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_ADDR15);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_DATA0",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_DATA0);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_DATA1",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_DATA1);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_DATA2",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_DATA2);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_DATA3",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_DATA3);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_DATA4",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_DATA4);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_DATA5",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_DATA5);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_DATA6",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_DATA6);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_DATA7",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_DATA7);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_DATA8",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_DATA8);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_DATA9",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_DATA9);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_DATA10",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_DATA10);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_DATA11",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_DATA11);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_DATA12",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_DATA12);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_DATA13",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_DATA13);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_DATA14",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_DATA14);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ICPLB_DATA15",0);
	sprintf( str, "0x%x" , *(unsigned long *)ICPLB_DATA15);
	WriteFileDate_string(str,1);

	WriteFileDate_string("ITEST_COMMAND",0);
	sprintf( str, "0x%x" , *(unsigned long *)ITEST_COMMAND);
	WriteFileDate_string(str,1);

	File_Size=wave_ptr - Start_Wave_ptr;
	WriteFile(Start_Wave_ptr, File_Size, SaveResultFileName);
	FMinfo|=FM_READ_DEVICE;
	OSTimeDly(2);
	free((void *)Printf_Cal_Data);
	sprintf(mybuffer,"%s Save Finish",SaveResultFileName);
	ShowMessage(mybuffer);
	return 1;
}

void Auto_Load_Off(void)
{
	p3k_send_tx_list tx_data;

	if(UTILITY.LOAD_CTL||UTILITY.SHORT_CTL) {
		UTILITY.SHORT_CTL	= Switch_OFF;
		UTILITY.LOAD_CTL	= Switch_OFF;

		PassLoad0ffSW_flag =1;

		tx_data.ADDRH	= Machine_Command;
		tx_data.ADDRL	= Machine_Load_OnOff;
		SendTXData(&tx_data);
		SysRedrawFlag |= PROG_UPDATA;
		PEL3000_LED_Control( LED_SHORT,UTILITY.SHORT_CTL );
		PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
	}
}
#if Enable_AutoLoad
void Auto_Load_On(void)
{
	p3k_send_tx_list tx_data;

	Compensation_Flag = 0;
	if(UTILITY.LOAD_CTL==Switch_OFF) {
		tx_data.ADDRH = Machine_Command;
		tx_data.ADDRL = Machine_Soft_Start;
		SendTXData(&tx_data);

		tx_data.ADDRH = Para_Ext_Command;
		tx_data.ADDRL = Para_Ext_Setting;
		SendTXData(&tx_data);

		UTILITY.LOAD_CTL	= Switch_ON;
		tx_data.ADDRH	= Machine_Command;
		tx_data.ADDRL	= Machine_Load_OnOff;
		SendTXData(&tx_data);
		SysRedrawFlag |= PROG_UPDATA;
		PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
	}
}

#endif

BYTE EnableFlag(BYTE chnum, BYTE x)
{
	UBYTE Now_LoadType;
	switch(M_num){
		case P_PROG_MAIN:
			Now_LoadType = Prog_Load;
			break;
		case P_Seq_Normal:
			Now_LoadType = NSeq_Load;
			break;			
		case P_Seq_Fast:
			Now_LoadType = FSeq_Load;
			break;			
		case P_FUNC_OCP:
			Now_LoadType = OCP_Load;	
			break;			
		case P_FUNC_batt:
			Now_LoadType = BATT_Load;
			break;
		case P_FUNC_OPP:
			Now_LoadType = OPP_Load;
			break;
		case P_FUNC_FLED:
			Now_LoadType = FLED_Load;
			break;
		case P_FUNC_CLED:
			Now_LoadType = CLED_Load;
			break;
		default:	
			Debug_printf("EnableFlag Error\n");
			Now_LoadType = Normal_Load;
			break;
	}	

	if(Now_LoadType==P3k_Chan_Data.Load_Type)
		P3k_Chan_Data.Load_Type = Normal_Load;
	else
		P3k_Chan_Data.Load_Type = Now_LoadType;

	P3k_Disp_Data.Load_Type = P3k_Chan_Data.Load_Type;
	SysRedrawFlag	|= PROG_UPDATA;
	MenuRedrawFlag	|= MENU_CHANGE;
	return(0);
}

BYTE Seq_Select(BYTE chnum, BYTE x)
{
	switch(x) {
	case F2_KEY:
		if(M_num == P_NSeq_Edit) {
			M_num = P_Seq_Normal;
		} else {
			M_num = P_Seq_Normal;
			P3k_NSeq_Disp = P3k_NSeq_Data;
			SEQ_Save_Status = 0;
			Soft_Key_Temp = 0;
		}
		break;
	case F3_KEY:
		if(M_num == P_FSeq_Edit) {
			M_num = P_Seq_Fast;
		} else {
			M_num = P_Seq_Fast;
			P3k_FSeq_Disp = P3k_FSeq_Data;
			SEQ_Save_Status = 0;
			Soft_Key_Temp = 0;
		}
		break;
#if Enable_OCP_function
	case F4_KEY:
		if(M_num == P_FUNC_MAIN_2) {
			M_num = P_FUNC_MAIN_2;
		} else {
			M_num = P_FUNC_MAIN_2;
			//P3k_FSeq_Disp = P3k_FSeq_Data;
			//SEQ_Save_Status = 0;
			Soft_Key_Temp = 0;
		}
		break;	
#endif
	default:
		break;
	}

	ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	//SEQ_Save_Status = 0;
	//Soft_Key_Temp = 0;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	return(0);
}

BYTE EditNormalSeq(BYTE chnum, BYTE x)
{
	ClrDispCnt( 0x00, 0x00, 0x05, 0x00, 0x00, 0x00);
	M_num = P_NSeq_Edit;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	return(0);
}


#if Enable_LED_function  
BYTE goto_fled_option(BYTE chnum, BYTE x){
	const char led_num[5]= {1,2,2,2,2};
	UBYTE index = P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp].mode;
	switch(x) {
	case F2_KEY:		
		Soft_Key_Temp = 0;
		M_num = P_FUNC_FLED_EDIT;
		ClrDispCnt(0x01,0x00,led_num[index],0x00,0x00,0x00);
		MenuRedrawFlag |= MENU_CHANGE;
		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR +BG_CLEAR_FLAG;
		ChanRedrawFlag |= BG_CLEAR + CHAN_STATUS;
		break;
	case F3_KEY:
	case F4_KEY:
		//P3k_FLed_Disp.disFlag = 1;

		break;	

	default:
		break;
	}
	
	return(0);
}
BYTE goto_cled_option(BYTE chnum, BYTE x){	
	switch(x) {
	case F2_KEY:		
		Soft_Key_Temp = 0;
		M_num = P_FUNC_CLED_EDIT;
		ClrDispCnt(0x01,0x00,0,0x00,0x00,0x00);
		find_curve_led_paramter(GetChanData(0,0));
		MenuRedrawFlag |= MENU_CHANGE;
		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR +BG_CLEAR_FLAG;
		ChanRedrawFlag |= BG_CLEAR + CHAN_STATUS;
		break;
	case F3_KEY:
	case F4_KEY:
		//P3k_FLed_Disp.disFlag = 1;

		break;	

	default:
		break;
	}
	
	return(0);
}

#endif


BYTE EditFastSeq(BYTE chnum, BYTE x)
{
	ClrDispCnt( 0x00, 0x00, 0x05, 0x00, 0x00, 0x00);
	M_num = P_FSeq_Edit;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	return(0);
}

void Recall_Factory_Action(char Mode)
{
	/*Mode: 1 Recall Factory From Keyboard*/
	/*Mode: 0 Recall Factory From SCPI*/
	UBYTE oserr;
	p3k_send_tx_list tx_data;
	char INTERFACE_temp;
	P3k_Data_Str *Data_tmp = &P3k_Chan_Data;
	System_Ready = 0;
	if(UTILITY.LOAD_CTL) {
		UTILITY.LOAD_CTL = Switch_OFF;
		tx_data.ADDRH = Machine_Command;
		tx_data.ADDRL = Machine_Load_OnOff;
		SendTXData(&tx_data);
		PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
		//SysRedrawFlag |= PROG_UPDATA;
	}

	INTERFACE_temp = UTILITY.INTERFACE;

	if(Mode)
		Load_Default_Interface(Recall_Interface_Y);
	else
		Load_Default_Interface(Recall_Interface_N);

	LoadDefaultProc(System_Recall_Default);

	BackupUserDefaultData(0);
	BackupRunProg();
	BackupNSeq();
	BackupFSeq();
	BackupSetupData();
	BackupStatus();

	if(INTERFACE_temp != UTILITY.INTERFACE) {
		OSSemPost(InterfaceChangeSemPtr);
		OSSemPend(InterfaceReadySemPtr, 0, &oserr);
	}

	RestoreRealChan();
	Control_LCDBRCon();
	M_num = Data_tmp->CURRMODE;
	FPGA_Init();
	System_Ready = 1;
	OSTimeDly(10);
	MenuRedrawFlag |= MENU_CHANGE;
	ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	SysRedrawFlag  |= SYS_CHANGE;
	ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
}

extern void SaveRecall_UserDefault(BYTE dire);
void RecallUserDefault(char mode)
{
	/* mode:1 Recall Default From Keyboard,Recall Interface	*/
	/* mode:0 Recall Default From SCPI,No Recall Interface	*/
	char i,INTERFACE_temp;
	UBYTE oserr;
	p3k_send_tx_list	tx_data;
	P3k_Disp_Str *Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str *Data_tmp = &P3k_Chan_Data;

	System_Ready = 0;
	if(UTILITY.LOAD_CTL) {
		UTILITY.LOAD_CTL = Switch_OFF;
		tx_data.ADDRH = Machine_Command;
		tx_data.ADDRL = Machine_Load_OnOff;
		SendTXData(&tx_data);
		PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
	}

	INTERFACE_temp = UTILITY.INTERFACE;

	LoadDefaultProc(User_Recall_Default);
	SaveRecall_UserDefault(0);

	if( (mode)&&(Backup_Default_Data.Def_Data_Ready==200) ) {	/*Recall Interface*/
		UTILITY.INTERFACE		= Backup_Default_Data.UTILITY.INTERFACE;
		RS232				= Backup_Default_Data.RS232;
		GPIBPAR 				= Backup_Default_Data.GPIBPAR;
	}

	if(INTERFACE_temp != UTILITY.INTERFACE) {
		OSSemPost(InterfaceChangeSemPtr);
		OSSemPend(InterfaceReadySemPtr, 0, &oserr);
	}

	RestoreRealChan();
	Control_LCDBRCon();
	M_num = Data_tmp->CURRMODE;
	FPGA_Init();
	System_Ready = 1;
	OSTimeDly(10);
	MenuRedrawFlag |= MENU_CHANGE;
	ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	SysRedrawFlag  |= SYS_CHANGE;
	ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
}
BYTE Recall_Factory_Default(BYTE chnum, BYTE x)
{
	char Default_Message1[60],Default_Message2[60],Default_Message3[60];

	if(p3k_File_Utility_BAR.MEDIA!=F_Media_Default)
		return(0);

	GUI_SetFont(Parameter_Font);
	GUI_SetBkColor(Message_Bottom_Bolor);
	GUI_SetColor(Message_Font_Bolor);

	if(Default_info&Def_Factory_CONFIRM) {
		sprintf(Default_Message1,"Recall Factory Default,\n");
		sprintf(Default_Message2,"Please Wait...\n");
		GUI_GotoXY(10, 175);
		GUI_DispChars(' ',51);
		GUI_GotoXY(10, 150);
		GUI_DispChars(' ',51);
		GUI_SetTextAlign(GUI_TA_LEFT);
		GUI_DispStringAt(Default_Message1, 10, 150);
		GUI_DispStringAt(Default_Message2, 10, 175);
		DMA_Update_Flag = 1;
		Update_Panel();
		Recall_Factory_Action(1);
#if 1
		D_interface.INTERFACE = UTILITY.INTERFACE;
		UBYTE err;
		OSSemPost(InterfaceChangeSemPtr);
		OSSemPend(InterfaceReadySemPtr, 0, &err);
#endif		
		Default_info = 0;
	} else {
		sprintf(Default_Message1,"Warning!!! \n");
		sprintf(Default_Message2,"Pressing F2 Again Will\n");
		sprintf(Default_Message3,"Recall The Default Settings !\n");
		GUI_GotoXY(10, 125);
		GUI_DispChars(' ',51);
		GUI_GotoXY(10, 175);
		GUI_DispChars(' ',51);
		GUI_GotoXY(10, 150);
		GUI_DispChars(' ',51);
		GUI_SetTextAlign(GUI_TA_LEFT);
		GUI_DispStringAt(Default_Message1, 10, 125);
		GUI_DispStringAt(Default_Message2, 10, 150);
		GUI_DispStringAt(Default_Message3, 10, 175);
		Default_info = Def_Factory_CONFIRM;
		MenuRedrawFlag |= MENU_CHANGE;
	}
	return(0);
}

extern void Show_APP_Message(UBYTE Kind);
BYTE EnterPowerFunc(BYTE chnum, BYTE x)
{
	if(OptionInfo[0].ModuleFlag==0) {
		Show_APP_Message(0);
		return 1;
	}
	M_num = P_FUNC_POWER;
	Soft_Key_Temp	 = 0;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	ChanRedrawFlag |= BG_CLEAR;
	ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	return 1;
}


