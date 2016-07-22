
/*******************************************************************************
*							湣OS-II Blackfin port test example
*							Blackfin Applications Team, Analog Devices Inc.,
*								Norwood, MA, US
*
* File: 				app_c.c
* Author: 				Deep Bodapati
* Last Modified: 		10-22-2006
* Project:				湣OS-II Blackfin port test example
* Platform: 			ADSP-BF533 EZKit Lite Evaluation Board (silicon rev 0.4 and higher)
* Tools:				VisualDSP++ 4.5 (Updated September 2006)
* 湣OS-II Version: 		v2.83
*
* Note: The user LEDs on the ADSP-BF533 EZKit Lite Evaluation Board are labeled
* LEDs #4 through 9. On the other hand, the user LEDs on the ADSP-BF537 EZKit
* Lite Evaluation Board are labeled LEDs #1 through 6. For uniform software
* naming convention, the LEDs are labeled LEDs# 1 through 6 for both EZKits.



*
* This file is part of the test example, Ex1, of the 湣OS-II port to the
* Blackfin processor. The test launches a boot thread, which in turn launches
* 4 threads of priorities 6, 7, 8 and 9 blink LEDs# 2, 3, 4 and 5 on the
* ADSP-BF533 EZKit Lite Evaluation Board and yield the processor by sleeping
* for 7, 8, 9 and 10 ticks respectively (thus effectively blinking the LEDs).
* In addition, the boot thread also launches two threads of priorities 5
* and 10 that blink LEDs# 1 and 6 controlled through the push-button switches
* SW4 and SW5 respectively.
******************************************************************************/
/*
Copyright...

This code is placed in the public domain, and can be distributed freely with no restrictions provided that the heading
of each source module file is not modified to remove the credit to the original author.

Disclaimer...

This program code is provided "as is". There is no warranty, either expressed or implied as to its fitness for use in
any application. It is provided only as an example of porting the MicroC/OS operating system to the Blackfin processor.
Its use is strictly at the risk of the user. The author will not be liable for any damages direct or consequential related
to the use of this software including, but not limited to loss of profit.
*/

/*********************************************************************
Include files
*********************************************************************/
#define	HEAD_H_GLOBALS

#include <app.h>
#include "../bmp/bmp.h"
#include "../menu/head.h"
#include "../menu/menu.h"
#include "../menu/menu_msg.h"
#include "keydef.h"
#include "Keypad.h"
#include "TxComm.h"
#include "../FPGA/SendTXSub.h"
#include "../Parser_Lib/Parser.h"
#include "../parser/menu/menuComm.h"
#include "../parser/scpi/scpiParser.h"
#include "../parser/scpi/threadUART.h"
#include "../parser/scpi/scpiRegister.h"

#include "math.h"

extern GELMASTER *gel;
extern p3k_send_tx_list TX_LIST;
extern unsigned short New_Set_Count_To_FPGA;
extern char IsfpgaOk;//Adam_0819
#if Enable_LED_function
extern const F_LED_Str DEFAULT_LED_SEQ;
#endif
WORD RTCDisplayCount;
BYTE inform_cnt=0;
extern unsigned char last_menu;

#if Enable_Ring_Count
UWORD UVP_Tone_Count = 0;
UWORD SEQ_Tone_Count = 0;
#endif



/*********************************************************************
Ext Variables
*********************************************************************/
extern MENU _menu[MAXMENU];
extern char CAL_STATE;
extern unsigned char last_menu; //Adam_debug

/*********************************************************************
Function
*********************************************************************/
BYTE Empty_Func(BYTE menu_no, BYTE item_no);
void ItemProcess(BYTE m_no,BYTE its_no);
void DrawMenuFrame(BYTE item, BYTE type);
void DrawArrowPoint(int x, int y);
void ClrDispCnt(char mode, char ct, char sec, char ssc, char bct, char scl);
char CheckLongPush(BYTE key, BYTE cnt);
void InitMachineProc(void);
void RunProgOff(void);
void ShowScrollBar_Other(UWORD Scroll_Xpos,UWORD Scroll_Ypos,UBYTE TotalDispItem,UBYTE OnePageDispItem,UBYTE EveryItemInterval,UBYTE ScrollBar_width,UBYTE DispStartPos);
void ShowScrollBall(int x, int y);
void ClearKeyBoard(void);
void Menu_Message(char *Message,int x,int y);
void Update_Panel(void);
void BackupStatus(void);
void Dis_News(UBYTE index);

/*********************************************************************
External Function
*********************************************************************/
extern void Status_Reporting(void);
extern void LCD_Blink(void);
extern void DispMenuProcess(void);
extern void DispUpperProcess(void);
extern void DispRightProcess(void);
extern void DispMeasureData(void);
extern void DispParameter(BYTE cnt);
extern void VarKnobProcess(BYTE cnt);
extern void VarKnobEnterProcess(BYTE cnt);
extern void ClearKeyProcess(BYTE cnt);
extern void DigitalProcess(UBYTE key, BYTE cnt);
extern void FileUtilDispProc(void);
extern void HelpFunction(void);
extern void update_rtc(void);
//extern UWORD Step_To_CNT(UWORD Input_Step,double Input_Gain,double Input_Offset);
extern void EZKit_Init_EBIU(void);
extern void EZKit_Init_Flash(void);
extern void EZKit_Init_Flags(void);
extern void EZKit_Clear_LED(char);
extern void EZKit_Set_LED(char);
extern void UART_main(void*);
extern void RestoreRealChan(void);
extern void EDGIO_Control(char mode, char onoff);
extern void StoreErrItemNumToErrEventQ(unsigned char temp_uc);
extern void StoreErrItemNumToErrEventQTemp(unsigned char temp_uc,char* Command_address);
extern void BuzzerOnOff(UWORD);
extern void BuzzerTone(WORD);
extern void TIMER1_DGIO(INT16U Delay_100ms);
extern void TIMER1_Pulse(void);
extern void FM_MainTask(void);
extern int NextFileName(int FileCount, char *FileName, char Mode, char cnt);
extern void status_byte_Init(void);
extern void RecallSetupData(char Address);
extern void BuzzerFunction(UBYTE Buzzer_Mode,WORD ith);
extern char FRAM_INIT(void);
extern void idTRG(void);
extern void rtc_get (struct tm  *tmp);
extern int WriteBmpFile(void);
extern void Control_LCDBRCon(void);
extern void BasicFrame(void);
extern void CursorInit(void);
extern BYTE Save_Data(BYTE chnum, BYTE x);
extern void SaveSetupDataAction(char SMEMORY_ADDR);
extern void sport1Write(unsigned long data);
extern unsigned long sport1Read(unsigned long data);
extern void FloatWindowsDispOn(void);
extern void FloatWindowsDispOff(void);
extern void FPGA_Init(void);
extern void FPGA_Ctrl(void);
extern void CalWaitProcess(void);
extern void AlarmProcess(UBYTE key);
extern void Show_Alarm_Message(void);
extern void Auto_Load_Off(void);
extern void PlaceNSeqChain(void);
extern void PlaceFSeqMemory(void);
extern UBYTE Recall2Mem(char mode, UWORD no);
extern void Recall2Display(void);
extern void Frame_Change(void);
extern void WriteRunRecordFile(void);
extern void FPGA_OCP_OPP_Ctrl(void);
extern void PlaceProgChain(void);
extern void battery_config(void);
extern void init_fled(void);
extern void init_cled(void);
extern void close_led_fpga(void);

void PEL3000_LED_Control( char mode, char onoff) {
	static char PEL3000_LED_Status=0x00;

	switch(mode) {
	case LED_LOAD:			/* Load On Off */
		if(onoff)	PEL3000_LED_Status |= 0x01;
		else		PEL3000_LED_Status &= (~0x01);
		break;
	case LED_SHIFT:			/* Shift */
		if(onoff)	PEL3000_LED_Status |= 0x02;
		else		PEL3000_LED_Status &= (~0x02);
		break;
	case LED_PRESET:		/* Preset */
		if(onoff)	PEL3000_LED_Status |= 0x04;
		else		PEL3000_LED_Status &=(~0x04);
		break;
	case LED_SHORT:			/* Short */
		if(onoff)	PEL3000_LED_Status |= 0x08;
		else		PEL3000_LED_Status &=(~0x08);
		break;
	default:
		break;
	}
	sport1Write(0xF1000000+PEL3000_LED_Status);
}

//extern nodes IdPos;
extern char USB_Status_Display,USB_Status;
task_params_list_t params[] = {
	// LED#, pointer to event
	{	0, 	(void *)0},
	{	1, 	(void *)0},
	{	2, 	(void *)0},
	{	3, 	(void *)0},
	{	4, 	(void *)0},
	{	5, 	(void *)0}
};

//--------------------------------------------------------------------------
// Function:	app_init
//
// Parameters:	None
//
// Return:		None
//
// Description:	Initialization function of a given application. Called from
// main() of the test (before uC/OS-II has been started)
//--------------------------------------------------------------------------
void app_init(void) {
	// Create 2 semaphores for 2 LEDs that will toggled through push buttons
	//LED1_semaphore = OSSemCreate(1);
	//LED6_semaphore = OSSemCreate(1);
	//params[0].event = LED1_semaphore;
	//params[5].event = LED6_semaphore;
}// end of app_init




//--------------------------------------------------------------------------
// Function:	app_main
//
// Parameters:	None
//
// Return:		None
//
// Description:	Main function of a given application. Called from
// ucos_ii_boot_thread (after uC/OS-II has been started)
//--------------------------------------------------------------------------
extern UBYTE TxBoardCastInit;
void app_main(void) {
	app_launch_threads();
}

//KeyTask
UBYTE KeyCntTestBuf[400];
WORD KeyCntPtr=0;
#if Enable_Optim_display
#define KEY_BUF_DEEP  5
#else
#define KEY_BUF_DEEP 7
#endif
UWORD key_buf_index=0;
WORD VarDelayCnt=0;

extern char v_keycode,v_keycnt,LongPush_CT;
BYTE BeepStatus=0;
WORD BeepCount=-1;
UBYTE KeyTaskBuf[2];
BYTE cnt_buf[KEY_BUF_DEEP];
UBYTE key_buf[KEY_BUF_DEEP];
unsigned char Delay_Read_Key;




#if 1//TEST

char pass_local_loadonoff_sw(void){
	char passFlag = 0;
	if(((UTILITY.LOCK_KEY)||(REM_CONT)||(DGIOCtrlFlag&EXT_Frame_CONT_KB)||(CtrlFlag1&Cal_Wait_moment)||(!FPGA_ISR_Data.ISR_Load))&&(UTILITY.LOAD_CTL==Switch_OFF))
		passFlag = 1;
	else if(M_num==P_CAL_MODE)
		passFlag = 1;
	else if((Ext_UnReg_Flag)&&(P3k_Disp_Data.CONF.Ext_Setting.Control <= 3))
		passFlag = 1;
	else if(UTILITY.LOAD_CTL==Switch_OFF) {
		if(KeyInFlag & SHIFT_KEY) {
			KeyInFlag &= ~SHIFT_KEY;
			PEL3000_LED_Control(LED_SHIFT, Switch_OFF);
			if(P3k_Chan_Data.Load_Type==Normal_Load) {
				M_num = P_FUNC_MAIN;
				ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
				DispMode = DispMode_SELECT_CH;
				ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				MenuRedrawFlag |= MENU_CHANGE;
				HelpRedrawFlag &= ~HELP_FUN_ON;
				Dis_News(1);
				passFlag = 1;
			} else {
				//Run func
			}
		} else {
			if(P3k_Chan_Data.Load_Type!=Normal_Load) {
				Dis_News(0);
				passFlag = 1;
			}
		}
	}	
	return passFlag;
}
void protect_extern_loadonin_onoff(char loadCtl){
	if((loadCtl==Switch_OFF)&&(P3k_Chan_Data.CONF.Ext_Setting.LoadOn_IN)) {
		P3k_Chan_Data.CONF.Ext_Setting.LoadOn_IN = 0;
		P3k_Disp_Data.CONF.Ext_Setting.LoadOn_IN = 0;
		if(M_num<4)P_M_num = P3k_Disp_Data.CURRMODE;
		if(M_num == P_CONF_Ext) {
			DataRedrawFlag |= BG_CLEAR_FLAG;
		} else {
			M_num = P_CONF_Ext;
			DataRedrawFlag |= DATA_CHANGE;//PARA_CHANGE + BG_CLEAR;
		}
		ClrDispCnt(0x01, 0x01, 0x01, 0x00, 0x00, 0x00);
		MenuRedrawFlag |= MENU_CHANGE;
		ChanRedrawFlag |= CHAN_CHANGE;
	}
}


#define FUNC_REDRAW_FLAG	MenuRedrawFlag |= MENU_CHANGE;\
							DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;\
							ChanRedrawFlag |= BG_CLEAR
#define INIT_LOAD_ONOFF		New_Set_Count_To_FPGA = 0;\
							Compensation_Flag = 0;\
							Compensation_Count = 0;\
							Error_Amount_Flag = 0;\
							last_menu = 0xFF

#define INIT_TIME			p3k_Measure_Data.Hour=0;\
							p3k_Measure_Data.Min=0;\
							p3k_Measure_Data.Sec=0
						
#define LOAD_ONOFF_SW		UTILITY.LOAD_CTL = loadCtl;\
							CMD_LOAD_SW
	

void cmd_load_onoff(char loadCtl){
	p3k_send_tx_list tx_data;	
	UWORD i;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;	
	const char led_num[5]= {1,2,2,2,2};
	
	INIT_LOAD_ONOFF;
	if(P3k_Chan_Data.Load_Type) {		
		INIT_TIME;
		HelpRedrawFlag &= ~HELP_FUN_ON;
		Soft_Key_Temp = 0;
	}else{
		protect_extern_loadonin_onoff(loadCtl);
	}
	
	switch(P3k_Chan_Data.Load_Type){	
	case Prog_Load:
		if(loadCtl==Switch_OFF) {
			if(Prog_Seq_Data.Total_Count) {
				M_num = P_PROG_Detail;
				if(Prog_Seq_Data.Total_Count > 4)	ClrDispCnt(0x00, 0x00, 3, 0x00, 0x00, 0x00);
				else								ClrDispCnt(0x00, 0x00, Prog_Seq_Data.Total_Count-1, 0x00, 0x00, 0x00);
			} else {
				M_num = P_PROG_MAIN;
				ClrDispCnt(0x00, 0x00, 3, 0x00, 0x00, 0x00);
			}
			SEQ_Save_Status = 0;
			FUNC_REDRAW_FLAG;
			FunctionFlag   = FUNC_CLEAR;
			LOAD_ONOFF_SW;
		} else {
			CMD_SOFT_START;
			PlaceProgChain();
			if(Prog_Seq_Data.Total_Count) {
				if(M_num!=P_PROG_Detail)		S_M_num = M_num;
				Prog_Seq_Data.SEQ_Stop_Continue = Display_Stop;
				Prog_Seq_Data.MANUAL_CTRL = 0;
				Prog_Seq_Data.SEQ_Complete = 0;
				LOAD_ONOFF_SW;
			} else {
				//loadCtl = 0;
				Prog_Seq_Data.SEQ_Stop_Continue = Display_None;
			}
			M_num = P_PROG_EXECUTE;
			FUNC_REDRAW_FLAG;
			if(Prog_Seq_Data.Total_Count)	FunctionFlag |= FUNC_PROG;
		}
		break;
	case NSeq_Load:
		if(loadCtl==Switch_OFF) {
			if(P_NSeq_EXECUTE==M_num) {
				M_num = P_Seq_Normal;
				ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
				FUNC_REDRAW_FLAG;
				FunctionFlag   = FUNC_CLEAR;
			}
			LOAD_ONOFF_SW;
		} else {
			CMD_SOFT_START;
			PlaceNSeqChain();
			if(Prog_Seq_Data.Total_Count)	{
				if(M_num!=P_PROG_Detail)		S_M_num = M_num;
				Prog_Seq_Data.SEQ_Stop_Continue = Display_Stop;
				Prog_Seq_Data.MANUAL_CTRL = 0;
				Prog_Seq_Data.SEQ_Complete = 0;
				LOAD_ONOFF_SW;
				FunctionFlag  |= FUNC_NSEQ;
			} else {
				//loadCtl = Switch_OFF;
				FunctionFlag  = FUNC_CLEAR;
				Prog_Seq_Data.SEQ_Stop_Continue = Display_None;
			}
			M_num = P_NSeq_EXECUTE;
			FUNC_REDRAW_FLAG;
		}
		break;
	case FSeq_Load:
		if(loadCtl==Switch_OFF) {
			if(P_FSeq_EXECUTE==M_num) {
				M_num = P_Seq_Fast;
				ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
				FUNC_REDRAW_FLAG;
				FunctionFlag = FUNC_CLEAR;
			}
			LOAD_ONOFF_SW;
		} else {			
			if(P3k_FSeq_Disp.FSeq_Max_Step<0xFF00) { // 1~1000	
				CMD_SOFT_START;
				PlaceFSeqMemory();
				if(M_num!=P_PROG_Detail) S_M_num = M_num;
				Prog_Seq_Data.SEQ_Stop_Continue = Display_Stop;
				Prog_Seq_Data.MANUAL_CTRL = 0;
				Prog_Seq_Data.SEQ_Complete = 0;
				LOAD_ONOFF_SW;
				FunctionFlag   |= FUNC_FSEQ;				
			} else { //0
				//loadCtl = Switch_OFF;
				FunctionFlag  = FUNC_CLEAR;
				Prog_Seq_Data.SEQ_Stop_Continue = Display_None;
			}
			M_num = P_FSeq_EXECUTE;
			FUNC_REDRAW_FLAG;
		}
		break;
#if Enable_OCP_function		
	case OCP_Load:
		if(loadCtl==Switch_OFF) {
			if(P_FUNC_OCP_EXECUTE==M_num) {
				M_num = P_FUNC_OCP;
				ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
				FUNC_REDRAW_FLAG;
				FunctionFlag = FUNC_CLEAR;
			}
			LOAD_ONOFF_SW;
		} else {
			P3K_OCP_Data.Complete = 0;
			for (i=0; i<4; i++) {
				P3K_OCP_Data.RecCurr[i]=0;
				P3K_OCP_Data.RecVolt[i]=0;
			}
			P3K_OCP_Data.UpdataFlag = 1;
			P3K_OCP_Disp = P3K_OCP_Data;
			LOAD_ONOFF_SW;
			FunctionFlag  |= FUNC_NSEQ;			
			M_num = P_FUNC_OCP_EXECUTE;
			FUNC_REDRAW_FLAG;
		}
		break;
#endif		
#if Enable_OPP_function		
	case OPP_Load:
		if(loadCtl==Switch_OFF) {
			if(P_FUNC_OPP_EXECUTE==M_num) {
				M_num = P_FUNC_OPP;
				ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
				FUNC_REDRAW_FLAG;
				FunctionFlag   = FUNC_CLEAR;
			}
			LOAD_ONOFF_SW;
		} else {
			P3K_OPP_Data.Complete = 0;
			for (i=0; i<4; i++) {
				P3K_OPP_Data.RecCurr[i]=0;
				P3K_OPP_Data.RecVolt[i]=0;
			}
			P3K_OPP_Data.UpdataFlag = 1;
			P3K_OPP_Disp = P3K_OPP_Data;
			LOAD_ONOFF_SW;
			FunctionFlag  |= FUNC_OPP;
			M_num = P_FUNC_OPP_EXECUTE;
			FUNC_REDRAW_FLAG;
		}
		break;
#endif		
#if Enable_Battery_Discharge		
	case BATT_Load:		
		if(loadCtl==Switch_OFF) {
			if(P_FUNC_batt_EXECUTE==M_num) {
				FUNC_REDRAW_FLAG;
				FunctionFlag   = FUNC_CLEAR;
				BattDisp.status = BATT_COMPLETE;
				BattDisp.stopStatus = 5;
			}
			LOAD_ONOFF_SW;
		} else {			
			FunctionFlag  |= FUNC_BATT;
			BattDisp.status = BATT_CONFIG;
			battery_config();
			CMD_SOFT_START;
			M_num = P_FUNC_batt_EXECUTE;
			FUNC_REDRAW_FLAG;
			LOAD_ONOFF_SW;
		}
		break;
#endif		
#if Enable_LED_function		
	case FLED_Load:
		if(loadCtl==Switch_OFF) {			
			FUNC_REDRAW_FLAG;
			FunctionFlag   = FUNC_CLEAR;
			LOAD_ONOFF_SW;
			close_led_fpga();
		} else {
			init_fled();
			P3k_FLed_Disp.complete = F_LED_CONFIG;
			FunctionFlag  |= FUNC_FLED;
			M_num = P_FUNC_FLED_EXECUTE;
			
			ClrDispCnt(0x01,0x00,led_num[P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp].mode],0x00,0x00,0x00);
			FUNC_REDRAW_FLAG;
			LOAD_ONOFF_SW;
		}
		break;
	case CLED_Load:
		if(loadCtl==Switch_OFF) {			
			FUNC_REDRAW_FLAG;
			FunctionFlag   = FUNC_CLEAR;
			LOAD_ONOFF_SW;
			close_led_fpga();			
		} else {
			init_cled();
			P3k_CLed_Disp.complete = F_LED_CONFIG;
			FunctionFlag  |= FUNC_CLED;
			M_num = P_FUNC_CLED_EXECUTE;
			
			ClrDispCnt(0x01,0x00,1,0x00,0x00,0x00);
			FUNC_REDRAW_FLAG;
			LOAD_ONOFF_SW;
		}
		break;
#endif		
	default:
		if((loadCtl==Switch_OFF)&&(UTILITY.ShortonLoadoff)&&(UTILITY.SHORT_CTL))	{
			UTILITY.SHORT_CTL = 0;
			SysRedrawFlag |= PROG_UPDATA + SHORT_UPDATA;
			PEL3000_LED_Control(LED_SHORT, UTILITY.SHORT_CTL);
		}
		DataRedrawFlag |= PARA_CHANGE;
		FunctionFlag |= FUNC_NORMAL;		
		CMD_SOFT_START;
		CMD_EXT_SETTING;
		LOAD_ONOFF_SW;;
		break;
	}
	SysRedrawFlag |= PROG_UPDATA;
	PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );	

}


void cmd_button_load_onoff(void){	
	char loadCtl = UTILITY.LOAD_CTL;
	if(pass_local_loadonoff_sw())return;
	loadCtl++;
	loadCtl&=0x01;	
	cmd_load_onoff(loadCtl);
	UTILITY.LOAD_CTL = loadCtl;
}

#else
void cmd_button_load_onoff(void){
	p3k_send_tx_list tx_data;	
	UWORD i;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	
	New_Set_Count_To_FPGA = 0;
	Compensation_Flag = 0;
	Compensation_Count = 0;
	Error_Amount_Flag = 0;
	last_menu = 0xFF; //Adam_debug
	if(((UTILITY.LOCK_KEY)||(REM_CONT)||(DGIOCtrlFlag & EXT_Frame_CONT_KB)||(CtrlFlag1&Cal_Wait_moment)||(!FPGA_ISR_Data.ISR_Load))&&(UTILITY.LOAD_CTL==0))
		break;

	if(M_num==P_CAL_MODE)
		break;

	if((Ext_UnReg_Flag) && (Disp_tmp->CONF.Ext_Setting.Control <= 3))
		break;

	
#if Enable_Func_select
	if(UTILITY.LOAD_CTL==Switch_OFF) {
		if(KeyInFlag & SHIFT_KEY) {
			KeyInFlag &= ~SHIFT_KEY;
			PEL3000_LED_Control(LED_SHIFT, Switch_OFF);
			if(P3k_Chan_Data.Load_Type==Normal_Load) {
				M_num = P_FUNC_MAIN;
				ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
				DispMode = DispMode_SELECT_CH;
				ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				MenuRedrawFlag |= MENU_CHANGE;
				HelpRedrawFlag &= ~HELP_FUN_ON;
				Dis_News(1);
				return 0;
			} else {
				//Run func
			}
		} else {
			if(P3k_Chan_Data.Load_Type==Normal_Load) {
				//Run Load
			} else {
				Dis_News(0);
				return 0;
			}
		}
	}
#endif
	if((UTILITY.LOAD_CTL)&&(P3k_Chan_Data.CONF.Ext_Setting.LoadOn_IN)) {
		P3k_Chan_Data.CONF.Ext_Setting.LoadOn_IN = 0;
		P3k_Disp_Data.CONF.Ext_Setting.LoadOn_IN = 0;
		if(M_num<4)P_M_num = P3k_Disp_Data.CURRMODE;
		if(M_num == P_CONF_Ext) {
			DataRedrawFlag |= BG_CLEAR_FLAG;
		} else {
			M_num = P_CONF_Ext;
			DataRedrawFlag |= DATA_CHANGE;//PARA_CHANGE + BG_CLEAR;
		}
		ClrDispCnt(0x01, 0x01, 0x01, 0x00, 0x00, 0x00);
		MenuRedrawFlag |= MENU_CHANGE;
		ChanRedrawFlag |= CHAN_CHANGE;
	}
#if 1
	if(P3k_Chan_Data.Load_Type) {
		if(UTILITY.LOAD_CTL==Switch_OFF) {
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Soft_Start;
			SendTXData(&tx_data);
		}
	}
#endif
#if Enable_LED_function
	if(FLED_Load==P3k_Chan_Data.Load_Type) {
		if(UTILITY.LOAD_CTL==0)init_fled();
	}
#endif
	UTILITY.LOAD_CTL++;
	UTILITY.LOAD_CTL&=0x01;
#if Enable_Func_DisTime
	if((UTILITY.LOAD_CTL)||(Normal_Load!=P3k_Chan_Data.Load_Type)) {
		if(FSeq_Load <= P3k_Chan_Data.Load_Type)WriteSEQDataToFPGA_flag =1;
		p3k_Measure_Data.Hour=0;
		p3k_Measure_Data.Min=0;
		p3k_Measure_Data.Sec=0;
	}
#endif

	/* Check run program mode */
	if(Prog_Load==P3k_Chan_Data.Load_Type) {	/* Flag of Run Program was turn on */
		HelpRedrawFlag &= ~HELP_FUN_ON;
		Soft_Key_Temp = 0;

		if(UTILITY.LOAD_CTL==Switch_OFF) {
			if(Prog_Seq_Data.Total_Count) {
				M_num = P_PROG_Detail;
				if(Prog_Seq_Data.Total_Count > 4)
					ClrDispCnt(0x00, 0x00, 3, 0x00, 0x00, 0x00);
				else
					ClrDispCnt(0x00, 0x00, Prog_Seq_Data.Total_Count-1, 0x00, 0x00, 0x00);
			} else {
				M_num = P_PROG_MAIN;
				ClrDispCnt(0x00, 0x00, 3, 0x00, 0x00, 0x00);
			}
			SEQ_Save_Status = 0;
			MenuRedrawFlag |= MENU_CHANGE;
			DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
			ChanRedrawFlag |= BG_CLEAR;
			FunctionFlag   = FUNC_CLEAR;
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Load_OnOff;
			SendTXData(&tx_data);
		} else {
			PlaceProgChain();
			if(Prog_Seq_Data.Total_Count) {
				if(M_num!=P_PROG_Detail)
					S_M_num = M_num;
				Prog_Seq_Data.SEQ_Stop_Continue = Display_Stop;
				Prog_Seq_Data.MANUAL_CTRL = 0;
				Prog_Seq_Data.SEQ_Complete = 0;
				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = Machine_Load_OnOff;
				SendTXData(&tx_data);
			} else {
				UTILITY.LOAD_CTL = 0;
				Prog_Seq_Data.SEQ_Stop_Continue = Display_None;
			}
			M_num = P_PROG_EXECUTE;
			MenuRedrawFlag |= MENU_CHANGE;
			DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
			ChanRedrawFlag |= BG_CLEAR;
			if(Prog_Seq_Data.Total_Count)
				FunctionFlag   |= FUNC_PROG;

		}
	} else if(NSeq_Load==P3k_Chan_Data.Load_Type) {
		HelpRedrawFlag &= ~HELP_FUN_ON;
		Soft_Key_Temp = 0;
		if(UTILITY.LOAD_CTL==Switch_OFF) {
			if(P_NSeq_EXECUTE==M_num) {
				M_num = P_Seq_Normal;
				ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
				ChanRedrawFlag |= BG_CLEAR;
				FunctionFlag   = FUNC_CLEAR;
			}
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Load_OnOff;
			SendTXData(&tx_data);
		} else {
			PlaceNSeqChain();
			if(Prog_Seq_Data.Total_Count)	{
				if(M_num!=P_PROG_Detail)
					S_M_num = M_num;
				Prog_Seq_Data.SEQ_Stop_Continue = Display_Stop;
				Prog_Seq_Data.MANUAL_CTRL = 0;
				Prog_Seq_Data.SEQ_Complete = 0;
				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = Machine_Load_OnOff;
				SendTXData(&tx_data);
				FunctionFlag  |= FUNC_NSEQ;
			} else {
				UTILITY.LOAD_CTL = Switch_OFF;
				FunctionFlag  = FUNC_CLEAR;
				Prog_Seq_Data.SEQ_Stop_Continue = Display_None;
			}
			M_num = P_NSeq_EXECUTE;
			MenuRedrawFlag |= MENU_CHANGE;
			DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
			ChanRedrawFlag |= BG_CLEAR;
		}
	} else if(FSeq_Load==P3k_Chan_Data.Load_Type) {
		HelpRedrawFlag &= ~HELP_FUN_ON;
		Soft_Key_Temp = 0;
		if(UTILITY.LOAD_CTL==Switch_OFF) {
			if(P_FSeq_EXECUTE==M_num) {
				M_num = P_Seq_Fast;	/* into sequence Main */
				ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
				ChanRedrawFlag |= BG_CLEAR;
				FunctionFlag   = FUNC_CLEAR;
			}
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Load_OnOff;
			SendTXData(&tx_data);
		} else {
			if(P3k_FSeq_Disp.FSeq_Max_Step<0xFF00) { // 1~1024
				if(0) { //if((P3k_Disp_Data.CONF.Para_Data.Booster_Number)&&((P3k_FSeq_Disp.FSeq_Range==0)||(P3k_FSeq_Disp.FSeq_Range==2))){
					UTILITY.LOAD_CTL = Switch_OFF;
					FunctionFlag  = FUNC_CLEAR;
					Prog_Seq_Data.SEQ_Stop_Continue = Display_None;
					BoosterLowRangeAlarm =1;
				} else {
					PlaceFSeqMemory();
					if(M_num!=P_PROG_Detail)
						S_M_num = M_num;
					Prog_Seq_Data.SEQ_Stop_Continue = Display_Stop;
					Prog_Seq_Data.MANUAL_CTRL = 0;
					Prog_Seq_Data.SEQ_Complete = 0;
					tx_data.ADDRH = Machine_Command;
					tx_data.ADDRL = Machine_Load_OnOff;
					SendTXData(&tx_data);
					FunctionFlag   |= FUNC_FSEQ;
				}
			} else { //0
				UTILITY.LOAD_CTL = Switch_OFF;
				FunctionFlag  = FUNC_CLEAR;
				Prog_Seq_Data.SEQ_Stop_Continue = Display_None;
			}

			M_num = P_FSeq_EXECUTE;
			MenuRedrawFlag |= MENU_CHANGE;
			DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
			ChanRedrawFlag |= BG_CLEAR;
		}
#if Enable_OCP_function

	} else if(OCP_Load==P3k_Chan_Data.Load_Type) {
		HelpRedrawFlag &= ~HELP_FUN_ON;
		Soft_Key_Temp = 0;
		if(UTILITY.LOAD_CTL==Switch_OFF) {
			if(P_FUNC_OCP_EXECUTE==M_num) {
				M_num = P_FUNC_OCP;
				ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
				ChanRedrawFlag |= BG_CLEAR;
				FunctionFlag   = FUNC_CLEAR;
			}
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Load_OnOff;
			SendTXData(&tx_data);
		} else {
			if(1) {
				P3K_OCP_Data.Complete = 0;
				for (i=0; i<4; i++) {
					P3K_OCP_Data.RecCurr[i]=0;
					P3K_OCP_Data.RecVolt[i]=0;
				}
				P3K_OCP_Data.UpdataFlag = 1;
				P3K_OCP_Disp = P3K_OCP_Data;
				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = Machine_Load_OnOff;
				SendTXData(&tx_data);
				FunctionFlag  |= FUNC_NSEQ;
			}
			M_num = P_FUNC_OCP_EXECUTE;
			MenuRedrawFlag |= MENU_CHANGE;
			DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
			ChanRedrawFlag |= BG_CLEAR;
		}

#endif
#if Enable_OPP_function
	} else if(OPP_Load==P3k_Chan_Data.Load_Type) {
		HelpRedrawFlag &= ~HELP_FUN_ON;
		Soft_Key_Temp = 0;
		if(UTILITY.LOAD_CTL==Switch_OFF) {
			if(P_FUNC_OPP_EXECUTE==M_num) {
				M_num = P_FUNC_OPP;
				ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
				ChanRedrawFlag |= BG_CLEAR;
				FunctionFlag   = FUNC_CLEAR;
			}
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Load_OnOff;
			SendTXData(&tx_data);
		} else {

			P3K_OPP_Data.Complete = 0;
			for (i=0; i<4; i++) {
				P3K_OPP_Data.RecCurr[i]=0;
				P3K_OPP_Data.RecVolt[i]=0;
			}
			P3K_OPP_Data.UpdataFlag = 1;
			P3K_OPP_Disp = P3K_OPP_Data;
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Load_OnOff;
			SendTXData(&tx_data);
			FunctionFlag  |= FUNC_OPP;

			M_num = P_FUNC_OPP_EXECUTE;
			MenuRedrawFlag |= MENU_CHANGE;
			DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
			ChanRedrawFlag |= BG_CLEAR;
		}

#endif
#if Enable_Battery_Discharge
	} else if(BATT_Load==P3k_Chan_Data.Load_Type) {
		HelpRedrawFlag &= ~HELP_FUN_ON;
		Soft_Key_Temp = 0;
		if(UTILITY.LOAD_CTL==Switch_OFF) {
			if(P_FUNC_batt_EXECUTE==M_num) {
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
				ChanRedrawFlag |= BG_CLEAR;
				FunctionFlag   = FUNC_CLEAR;
				BattDisp.status = BATT_COMPLETE;
				BattDisp.stopStatus = 5;
			}
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Load_OnOff;
			SendTXData(&tx_data);
		} else {
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Load_OnOff;
			SendTXData(&tx_data);
			FunctionFlag  |= FUNC_BATT;
			BattDisp.status = BATT_CONFIG;
			M_num = P_FUNC_batt_EXECUTE;
			MenuRedrawFlag |= MENU_CHANGE;
			DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
			ChanRedrawFlag |= BG_CLEAR;
		}
#endif
#if Enable_LED_function
	} else if(FLED_Load==P3k_Chan_Data.Load_Type) {
		HelpRedrawFlag &= ~HELP_FUN_ON;
		Soft_Key_Temp = 0;
#if 1
		if(UTILITY.LOAD_CTL==Switch_OFF) {
			if(P_FUNC_FLED_EXECUTE==M_num) {
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
				ChanRedrawFlag |= BG_CLEAR;
				FunctionFlag   = FUNC_CLEAR;
			}

			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Load_OnOff;
			SendTXData(&tx_data);
		} else {
			P3k_FLed_Disp.complete = F_LED_CONFIG;
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Load_OnOff;
			SendTXData(&tx_data);
			FunctionFlag  |= FUNC_FLED;
			M_num = P_FUNC_FLED_EXECUTE;
			MenuRedrawFlag |= MENU_CHANGE;
			DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
			ChanRedrawFlag |= BG_CLEAR;
		}
#endif
#endif

	} else {

#if Enable_AutoLoad
#if Enable_Short_invalidate
		if(UTILITY.SHORT_CTL)
#else
		if((UTILITY.LOAD_CTL==0)&&(UTILITY.ShortonLoadoff)&&(UTILITY.SHORT_CTL))
#endif
		{
			UTILITY.SHORT_CTL = 0;
			SysRedrawFlag |= PROG_UPDATA + SHORT_UPDATA;
			PEL3000_LED_Control(LED_SHORT, UTILITY.SHORT_CTL);
		}
#endif
		DataRedrawFlag |= PARA_CHANGE;
		FunctionFlag |= FUNC_NORMAL;
		tx_data.ADDRH = Machine_Command;
		tx_data.ADDRL = Machine_Soft_Start;
		SendTXData(&tx_data);

		tx_data.ADDRH = Para_Ext_Command;
		tx_data.ADDRL = Para_Ext_Setting;
		SendTXData(&tx_data);

		tx_data.ADDRH = Machine_Command;
		tx_data.ADDRL = Machine_Load_OnOff;
		SendTXData(&tx_data);
	}
	SysRedrawFlag |= PROG_UPDATA;
	PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
	break;

}

#endif














void KeyTask(void* pdata) { /*This task will be executed every 40ms.*/
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
	OS_CPU_SR  cpu_sr;
	cpu_sr = 0; 								 /* Prevent compiler warning						   */
#endif
	UBYTE tmp;
	UBYTE err;
	UBYTE keycode, keycnt;
	UBYTE last_key=0, first_nonzero_key_flag=0, maxkey1=0, maxkey2=0; //These variables are used to cancel error keycode(direction).
	WORD nokey_cnt=0, last_key_cnt=0, maxkey_cnt1=0, maxkey_cnt2=0;
	UWORD i, j,k;
	char cnt;
	ULONG SPORT1_Data;

	while(1) {
		SPORT1_Data = sport1Read(0xF0000000);
		OS_ENTER_CRITICAL();
		keycode	= (SPORT1_Data&0x0000FF00)>>8;
		keycnt	= SPORT1_Data&0x000000FF;
		OS_EXIT_CRITICAL();

		if(keycode) { //Counting the zero key num
			first_nonzero_key_flag=1;
			nokey_cnt=0;
			VarDelayCnt=0;
		} else {
			if( KeyInFlag & LONG_PUSH) {
				keycode=v_keycode;
				keycnt=0x0;
				v_keycode=0;
				key_buf[0] = key_buf[1] = keycode;
				cnt_buf[0] = 0xff;
				cnt_buf[1] = 0x0;
				key_buf_index = 6;
				last_key = 0;
				first_nonzero_key_flag=1;
				nokey_cnt=0;
				VarDelayCnt=0;
			} else {	/* Below code are OLD */
				if(VarDelayCnt<15)
					VarDelayCnt++;
				else
					VarDelayCnt=0;

				if(nokey_cnt>=(KEY_BUF_DEEP-2)) //If we got 4 zero key continuously, it's not necessary to compare the last key.
					last_key=0;
				else
					nokey_cnt++;
			}
		}
		if(first_nonzero_key_flag) { //We must continuously record 5 key codes since we got the first non zero key code.
			key_buf[key_buf_index]=keycode;
			cnt_buf[key_buf_index++]=keycnt;
			if(key_buf_index>=KEY_BUF_DEEP) {
				key_buf_index=0;
				first_nonzero_key_flag=0;
				//Key buffer process.
				maxkey1=0;
				maxkey2=0;
				maxkey_cnt1=0;
				maxkey_cnt2=0;
				for(i=0; i<KEY_BUF_DEEP; i++) { //Find the first non zero key code.
					if(key_buf[i]) {
						maxkey1=key_buf[i];
						maxkey_cnt1=cnt_buf[i];
						i++;
						j=i;
						break;
					}
				}
				for(; j<KEY_BUF_DEEP; j++) {  //Find the second non zero key code but that not equal to the first.
					if( (key_buf[j]) && (maxkey1!=key_buf[j]) ) {
						maxkey2=key_buf[j];
						maxkey_cnt2=cnt_buf[j];
						j++;
						break;
					}
				}
				if(maxkey2!=0) { //Second key is not zero => compare with the first key.
					for(; i<KEY_BUF_DEEP; i++) {
						if(maxkey1==key_buf[i])
							maxkey_cnt1+=cnt_buf[i];
					}
					for(; j<KEY_BUF_DEEP; j++) {
						if(maxkey2==key_buf[j])
							maxkey_cnt2+=cnt_buf[j];
					}
					if(maxkey_cnt2>=maxkey_cnt1) {
						maxkey1=maxkey2;
						maxkey_cnt1=maxkey_cnt2;
					}
				} else {
					//Calculate the key count of first key.
					for(; i<KEY_BUF_DEEP; i++) {
						if(maxkey1==key_buf[i]) {
							maxkey_cnt1+=cnt_buf[i];
						}
					}
				}
				if(last_key==0) {
					//It's a new key.
					OSSemPend(KeyCodeDoneSemPtr, 0, &err);
					KeyTaskBuf[0]=maxkey1;
					KeyTaskBuf[1]=maxkey_cnt1;
					OSSemPost(KeyCodeReadySemPtr);//New key code ready.
					last_key=maxkey1;
					last_key_cnt=maxkey_cnt1;
					if(KeyCntPtr>=400) //Test
						KeyCntPtr=0;
					KeyCntTestBuf[KeyCntPtr++]=maxkey_cnt1;
				} else if(maxkey1!=last_key) {
					//Different key, do nothing.
					last_key=0;
					last_key_cnt=0;
					if(KeyCntPtr>=400) //Test
						KeyCntPtr=0;
					KeyCntTestBuf[KeyCntPtr++]=127;
				} else {
					if(((last_key_cnt<0)&&(maxkey_cnt1<0))||((last_key_cnt>0)&&(maxkey_cnt1>0))) {
						//It's the same key(knob with the same direction).
						OSSemPend(KeyCodeDoneSemPtr, 0, &err);
						if(err==0) {
							KeyTaskBuf[0]=maxkey1;
							KeyTaskBuf[1]=maxkey_cnt1;
							OSSemPost(KeyCodeReadySemPtr);//New key code ready.
						}
						last_key=maxkey1;
						last_key_cnt=maxkey_cnt1;
						if(KeyCntPtr>=400) //Test
							KeyCntPtr=0;
						KeyCntTestBuf[KeyCntPtr++]=maxkey_cnt1;
					} else {	//knob with different direction.
						last_key=0;
						last_key_cnt=0;
						if(KeyCntPtr>=400) //Test
							KeyCntPtr=0;
						KeyCntTestBuf[KeyCntPtr++]=127;
					}
				}
			}//if(key_buf_index>=KEY_BUF_DEEP)
		}//if(first_nonzero_key_flag)
		//}

		do {
			OSTimeDly(1);//Time duration = 10 ms
		} while(DGIOCtrlFlag&REM_Mode_Fast);
	}//while(1)
}


void Dis_News(UBYTE index) {
	if(index==0)
		Menu_Message("Press Shift, then press Load On.",25,210);
	else if(index==1)
		Menu_Message("Select  the  function.",70,210);
	CtrlFlag1 |= Disp_Middle_Message;
	DMA_Update_Flag = 1;
	Update_Panel();
	OSTimeDly(120);
}

BYTE KeyProcess(UBYTE key, BYTE cnt) { /*Include handle all Knob and Key without Menu*/
	p3k_send_tx_list tx_data;
	UBYTE err,static_dymatic;
	BYTE inform_cnt=0;
	UWORD i,j;
	char Duration_Time_High,Duration_Time_Low,Loop_Number_High,Loop_Number_Low,data;
	char str[50],tmp,SYNC_TMEM_temp;
	UBYTE End_Status;
	unsigned char Magnification_Limit_Cnt=0;

	P3k_Data_Str 		*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;

	if(K_Invalid_Key==key)	return(inform_cnt);

	tmp = CheckLongPush(key,cnt);

	if(tmp==2)		cnt = 0x01;
	else if(tmp==1)	return(0);
	if(cnt==0)		return(0);						/* judge long push key */

	if((tmp!=2)&&(UTILITY.BEEP_ONOFF)&&(!Tone_Flag)) {
		Key_Count = 3;
		BuzzerFunction(Buzzer_Key,Key_Count--);
	}
	switch(key) {
 	case K_Digital_0 ... K_Digital_9:
		key = key - K_Digital_0;
		if( (UTILITY.LOCK_KEY) || (REM_CONT) || (DGIOCtrlFlag & RUN_SEQ_CHAN) || (DGIOCtrlFlag & EXT_Frame_CONT_KB)||(CtrlFlag1&Cal_Wait_moment)||(FunctionFlag&FUNC_ON)||((M_num == P_CONF_OTHER)&&(UTILITY.LOAD_CTL))||(CtrlFlag1&Cal_Wait_moment)||((M_num == P_CONF_KNOB)&&(Disp_tmp->CONF.Knob_Status)))
			break;
		DigitalProcess(key,cnt);
		break;
	case K_Digital_Dot: /* . */
		if( (UTILITY.LOCK_KEY) || (REM_CONT) || (DGIOCtrlFlag & RUN_SEQ_CHAN)  || (DGIOCtrlFlag & EXT_Frame_CONT_KB)||(CtrlFlag1&Cal_Wait_moment)||(FunctionFlag&FUNC_ON)||((M_num == P_CONF_OTHER)&&(UTILITY.LOAD_CTL))||(CtrlFlag1&Cal_Wait_moment))
			break;
		if( KeyInFlag & SHIFT_KEY) {
			Auto_Load_Off();
			KeyInFlag &= ~SHIFT_KEY;
			PEL3000_LED_Control(LED_SHIFT, Switch_OFF);
			if(M_num != P_Input_Password) {
				if(M_num!=P_UTIL_FILE)
					P_M_num = M_num;
				else
					P_M_num = P_FILE_CHAN;
				M_num = P_Input_Password;
				ClrDispCnt(0,0,0,0,0,0);
				KeyinBuf[0] =KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
				KeyInFlag&=(~DIGI_KEY_IN);
				Soft_Key_Temp=0;
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				HelpRedrawFlag &= ~HELP_FUN_ON;
				ChanRedrawFlag |= BG_CLEAR;
			}
		} else
			DigitalProcess(key,cnt);
		break;
	case K_Clear_Key: /* Clear */		/* For KeyIn use */
		if( REM_CONT  || (DGIOCtrlFlag & RUN_SEQ_CHAN) || (DGIOCtrlFlag & EXT_Frame_CONT_KB)||(CtrlFlag1&Cal_Wait_moment)||(FunctionFlag&FUNC_ON))				/* If Remote Control Mode, not use */
			break;
		if( UTILITY.LOCK_KEY ) {
			if( !(KeyInFlag & SHIFT_KEY) )
				break;
		}
		ClearKeyProcess(cnt);
		break;
	case K_Enter_Key: /* Enter */
		if( (UTILITY.LOCK_KEY) || (REM_CONT) || (DGIOCtrlFlag & RUN_SEQ_CHAN) || (DGIOCtrlFlag & EXT_Frame_CONT_KB)||(CtrlFlag1&Cal_Wait_moment)||(FunctionFlag&FUNC_ON)||((M_num == P_CONF_OTHER)&&(UTILITY.LOAD_CTL)))
			break;
		VarKnobEnterProcess(cnt);
		break;
	case K_Preset_Key: /* PRESET */ /* Maybe change form Lock key to Preset Key */
#if Enable_cathc_photo
		if(USB_Status==USB_Exist) {
			if(G_StatusFlag) {
				if(G_StatusFlag & saveBmpFile) {
					WriteBmpFile();
					G_StatusFlag &= ~(saveBmpFile);
				}				
				KeyInFlag &= ~PRESET_KEY;
				PEL3000_LED_Control(LED_PRESET, Switch_OFF);
				break;
			}
		}
		
		if( KeyInFlag & PRESET_KEY ) {
			KeyInFlag &= ~PRESET_KEY;
			PEL3000_LED_Control(LED_PRESET, Switch_OFF);
		} else {
			KeyInFlag |= PRESET_KEY;
			G_StatusFlag |= saveBmpFile;
			PEL3000_LED_Control(LED_PRESET, Switch_ON);
		}
		
#else
		if(USB_Status==USB_Exist) {
			if(G_StatusFlag) {
				if(G_StatusFlag & saveBmpFile) {
					WriteBmpFile();
					G_StatusFlag &= ~(saveBmpFile);
				}
				if(G_StatusFlag & saveRunRecordFile) {
					G_StatusFlag &= ~(saveRunRecordFile);
					WriteRunRecordFile();
				}
				KeyInFlag &= ~PRESET_KEY;
				PEL3000_LED_Control(LED_PRESET, Switch_OFF);
				break;
			}
		}

		if((UTILITY.LOCK_KEY)||(REM_CONT)||(DGIOCtrlFlag & EXT_Frame_CONT_KB) || (CtrlFlag1&Cal_Wait_moment) || (FunctionFlag&FUNC_ON))				/* If Remote Control Mode, not use */
			break;

		if((M_num == P_CC) && (Disp_tmp->CC.STADYNA == 0) && (KeyInFlag&SHIFT_KEY) && (!Data_tmp->CONF.Ext_Setting.Control)) {
			Disp_tmp->CC.ABSELECT++;
			Disp_tmp->CC.ABSELECT&=0x1;
			Data_tmp->CC.ABSELECT = Disp_tmp->CC.ABSELECT;
			ChanRedrawFlag |= CHAN_STATUS;

			tx_data.ADDRH = 0x01;
			tx_data.ADDRL = 0x00;
			SendTXData(&tx_data);
		} else if((M_num == P_CR) && (Disp_tmp->CR.STADYNA == 0) && (KeyInFlag&SHIFT_KEY) && (!Data_tmp->CONF.Ext_Setting.Control)) {
			Disp_tmp->CR.ABSELECT++;
			Disp_tmp->CR.ABSELECT&=0x1;
			Data_tmp->CR.ABSELECT = Disp_tmp->CR.ABSELECT;
			ChanRedrawFlag |= CHAN_STATUS;

			tx_data.ADDRH = 0x02;
			tx_data.ADDRL = 0x00;
			SendTXData(&tx_data);
		} else if(M_num == P_CV && KeyInFlag & SHIFT_KEY) {
			Disp_tmp->CV.ABSELECT++;
			Disp_tmp->CV.ABSELECT&=0x1;
			Data_tmp->CV.ABSELECT = Disp_tmp->CV.ABSELECT;
			ChanRedrawFlag |= CHAN_STATUS;
			tx_data.ADDRH = 0x03;
			tx_data.ADDRL = 0x00;
			SendTXData(&tx_data);
		} else if((M_num == P_CP) && (Disp_tmp->CP.STADYNA == 0) && (KeyInFlag&SHIFT_KEY) && (!Data_tmp->CONF.Ext_Setting.Control)) {
			Error_Amount_Flag = 0;
			Compensation_Flag = 0;
			Compensation_Count = 0;
			Disp_tmp->CP.ABSELECT++;
			Disp_tmp->CP.ABSELECT&=0x1;
			Data_tmp->CP.ABSELECT = Disp_tmp->CP.ABSELECT;
			ChanRedrawFlag |= CHAN_STATUS;
			tx_data.ADDRH = 0x04;
			tx_data.ADDRL = 0x00;
			SendTXData(&tx_data);
		} else {
			if( KeyInFlag & PRESET_KEY ) {
				KeyInFlag &= ~PRESET_KEY;
				PEL3000_LED_Control(LED_PRESET, Switch_OFF);
			} else {
				KeyInFlag |= PRESET_KEY;
				PEL3000_LED_Control(LED_PRESET, Switch_ON);
			}
		}
#endif		
		break;
	case K_Shift_Key: 
		if((CtrlFlag1&Cal_Wait_moment)||(FunctionFlag&FUNC_ON))
			break;		
			if( KeyInFlag & SHIFT_KEY ) {
				KeyInFlag &= ~SHIFT_KEY;
				PEL3000_LED_Control(LED_SHIFT, Switch_OFF);
			} else {
				KeyInFlag |= SHIFT_KEY;
				PEL3000_LED_Control(LED_SHIFT, Switch_ON);				
			}		
		break;
	case K_Load_Key: /* Load On,Off */
		cmd_button_load_onoff();
		break;
	case K_Knob_Rotate: /*Variable knob rotated*/
		if( (UTILITY.LOCK_KEY) || (REM_CONT)||(DGIOCtrlFlag & EXT_Frame_CONT_KB)||(CtrlFlag1&Cal_Wait_moment)||((M_num == P_CONF_OTHER)&&(UTILITY.LOAD_CTL)))
			break;

		if((DispMode == DispMode_BROWSE_ITEMS) && (Disp_tmp->CONF.Knob_Status) && (M_num == P_CONF_KNOB))
			break;

		VarKnobProcess(cnt);
		inform_cnt = 0-cnt;	
		break;
	case K_Knob_Select: /* VarSelected & Enter */
		if((DispMode == DispMode_SET_PARAMETERS) && (M_num <= P_CP)) {
			if(!Disp_tmp->CONF.Knob_Status) {
				switch(Data_tmp->CURRMODE) {
				case CC_MODE:
					static_dymatic = Data_tmp->CC.STADYNA;
					break;
				case CR_MODE:
					static_dymatic = Data_tmp->CR.STADYNA;
					break;
				case CV_MODE:
					static_dymatic = 0;
					break;
				case CP_MODE:
					static_dymatic = Data_tmp->CP.STADYNA;
					break;
				default:
					break;
				}
				if((DispCT>=2)||((DispCT==1)&&(static_dymatic==1)&&(Data_tmp->CONF.Dyna_Level==1))) {

				} else {
					Data_tmp->Coarse++;
					Data_tmp->Coarse&=0x1;
					ChanRedrawFlag |= CHAN_STATUS;
				}
			} else {
				Magnification_Cnt++;

				if(M_num == P_CR)
					Magnification_Limit_Cnt = 5;
				else
					Magnification_Limit_Cnt = 4;

				if(Magnification_Cnt > Magnification_Limit_Cnt)
					Magnification_Cnt = 0;

				DataRedrawFlag |= PARA_CHANGE;
			}
		} else if( (UTILITY.LOCK_KEY) || (REM_CONT)||(DGIOCtrlFlag & RUN_SEQ_CHAN) || (DGIOCtrlFlag & EXT_Frame_CONT_KB)||(CtrlFlag1&Cal_Wait_moment)||(FunctionFlag&FUNC_ON)||((M_num == P_CONF_OTHER)&&(UTILITY.LOAD_CTL)))
			break;

		break;
	case K_Short_Key:		/*SHORT*/
		New_Set_Count_To_FPGA = 0;
		Compensation_Flag = 0;
		Compensation_Count = 0;
		Error_Amount_Flag = 0;

		if( (UTILITY.LOCK_KEY) || (REM_CONT)||(DGIOCtrlFlag & RUN_SEQ_CHAN) || (DGIOCtrlFlag & EXT_Frame_CONT_KB)||(CtrlFlag1&Cal_Wait_moment)||(FunctionFlag&FUNC_ON))
			break;
#if Enable_AutoLoad
#if Enable_Short_invalidate
		if ((P3k_Disp_Data.CONF.Short_Fun==0)||((P3k_Disp_Data.CONF.Short_Satety)&&(UTILITY.LOAD_CTL==0))) {
			if(P3k_Disp_Data.CONF.Short_Fun==0)
				Menu_Message("Confirm the option of Short Function.",8,210);
			else
				Menu_Message("Confirm the option of Short Safety.",16,210);
			CtrlFlag1 |= Disp_Middle_Message;
			DMA_Update_Flag = 1;
			Update_Panel();
			OSTimeDly(120);
			break;
		}
#else
		if ((UTILITY.ShortonLoadoff)&&(UTILITY.LOAD_CTL==0))	break;
#endif
#endif
		UTILITY.SHORT_CTL++;
		UTILITY.SHORT_CTL &= 0x01;
		if(Normal_Load!=P3k_Chan_Data.Load_Type) { //Adam_debug
			UTILITY.SHORT_CTL = 0;
		}
		Prot_Setting_Process();
		tx_data.ADDRH = Machine_Command;
		tx_data.ADDRL = Machine_Soft_Start;
		SendTXData(&tx_data);

		tx_data.ADDRH = Para_Ext_Command;
		tx_data.ADDRL = Para_Ext_Setting;
		SendTXData(&tx_data);

		tx_data.ADDRH = Machine_Command;
		tx_data.ADDRL = Machine_Load_OnOff;
		SendTXData(&tx_data);

		SysRedrawFlag |= PROG_UPDATA + SHORT_UPDATA;
		PEL3000_LED_Control(LED_SHORT, UTILITY.SHORT_CTL);
#if Enable_Short_invalidate
		if(UTILITY.LOAD_CTL==0)	PEL3000_LED_Control(LED_LOAD, UTILITY.SHORT_CTL);
#endif
		break;
	case K_Func_Key:		/*Func menu, File menu*/
		if(KeyInFlag & SHIFT_KEY) { /*File menu*/
			if( (UTILITY.LOCK_KEY)||(REM_CONT) || (M_num==P_CAL_MODE)||(DGIOCtrlFlag & EXT_Frame_CONT_KB)||(CtrlFlag1&Cal_Wait_moment)||(FunctionFlag&FUNC_ON))
				break;
			KeyInFlag &= ~SHIFT_KEY;
			PEL3000_LED_Control(LED_SHIFT, Switch_OFF);
			if(M_num == P_FILE_CHAN)
				break;
			Soft_Key_Temp=0;

			if( (F_Media_USB==p3k_File_Utility_BAR.MEDIA)&&(USB_Status_Display!=USB_Exist) ) {
				Save_Status	= 0;
				Recall_Status	= 0;
			} else {
				Save_Status	= 1;
				Recall_Status	= 1;
			}
			if(USB_Status_Display==USB_Exist) {
				if(p3k_File_Utility_BAR.USB_Data_Type==F_Memory_Data)	SavMemoryFileCount	= NextFileName(SavMemoryFileCount,	SaveFileName,Sav_Memory,	0);
				else if(p3k_File_Utility_BAR.USB_Data_Type==F_Setup_Data)	SavSetupFileCount	= NextFileName(SavSetupFileCount,	SaveFileName,Sav_Set,		0);
				else if(p3k_File_Utility_BAR.USB_Data_Type==F_Preset_Data)	SavPresetFileCount	= NextFileName(SavPresetFileCount,	SaveFileName,Sav_Preset,	0);
				else if(p3k_File_Utility_BAR.USB_Data_Type==F_NSeq_Data)	SavNSeqFileCount	= NextFileName(SavNSeqFileCount,	SaveFileName,Sav_NSeq,		0);
				else if(p3k_File_Utility_BAR.USB_Data_Type==F_FSeq_Data)	SavFSeqFileCount	= NextFileName(SavFSeqFileCount,	SaveFileName,Sav_FSeq,		0);
			}
			if(M_num != P_FILE_CHAN)
				P_M_num = M_num;			/* Save Current M_num to P_M_num */
			F_M_num = P_FILE_CHAN;		/* Save Current Status of FILE is Setup CHAN Data */
			M_num = P_FILE_CHAN; 		/* Updata M_num */
			Default_info = 0;
			MEMORY_SAVE_FLAG = M_Nothing;
			ChanRedrawFlag |= CHAN_CHANGE;
			ClrDispCnt(0x00,0x00,0x05,0x00,0x00,0x00);
			MenuRedrawFlag |= MENU_CHANGE;
			DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
			HelpRedrawFlag &= ~HELP_FUN_ON;
		} else {	/*Func menu*/
			if( (UTILITY.LOCK_KEY)||(REM_CONT) ||(M_num==P_CAL_MODE)||(DGIOCtrlFlag & EXT_Frame_CONT_KB)||(CtrlFlag1&Cal_Wait_moment)||(FunctionFlag&FUNC_ON))
				break;
			Soft_Key_Temp=0;
			if(M_num != P_FUNC_MAIN) {
				M_num = P_FUNC_MAIN;
				ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				ChanRedrawFlag |= BG_CLEAR;
				HelpRedrawFlag &= ~HELP_FUN_ON;
			}
		}
		break;
	case K_Main_Key:  /*Main menu, Local menu,Test menu*/
		if((CtrlFlag1&Cal_Wait_moment) || (FunctionFlag&FUNC_ON))
			break;
		Soft_Key_Temp=0;
		if((KeyInFlag & SHIFT_KEY)&&(KeyInFlag & PRESET_KEY)&&debug_pass_flag) { //Adam_debug
			KeyInFlag &= ~PRESET_KEY;
			PEL3000_LED_Control(LED_PRESET, Switch_OFF);

			KeyInFlag &= ~SHIFT_KEY;
			PEL3000_LED_Control(LED_SHIFT, Switch_OFF);

			if(M_num != P_Test_Func) {
				if(M_num!=P_HELP_HELP) {
					if(M_num!=P_UTIL_FILE)
						P_M_num = M_num;
					else
						P_M_num = P_FILE_CHAN;
				}
				//A_d8 = M_num;
				M_num = P_Test_Func;
				ClrDispCnt(1,0,0,0,0,0);
				KeyinBuf[0] =KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
				KeyInFlag&=(~DIGI_KEY_IN);
				Soft_Key_Temp=0;
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag|=PARA_CHANGE + BG_CLEAR;
				HelpRedrawFlag &= ~HELP_FUN_ON;
				ChanRedrawFlag |= BG_CLEAR;
			}
			break;
		}
		if(KeyInFlag & SHIFT_KEY) { /* Local menu */
			/* Setting Remote Control or Local */
			KeyInFlag &= ~SHIFT_KEY;
			PEL3000_LED_Control(LED_SHIFT, Switch_OFF);
			if(REM_CONT) {
				REM_CONT = 0;
				SysRedrawFlag |= REM_LOC_UPDATA;
			}
			if(DGIOCtrlFlag & EXT_Frame_CONT_KB) {
				EXT_DGIO.RSTATUS |= 0x1;
				DGIOCtrlFlag |= EXT_Frame_CONT_DISP;
				DGIOCtrlFlag &= (~EXT_Frame_CONT_KB);
			}
		} else {
			/*Main menu*/
			if( (UTILITY.LOCK_KEY) || (REM_CONT) || (M_num==P_CAL_MODE)||(DGIOCtrlFlag & EXT_Frame_CONT_KB))
				break;

			if(M_num != Disp_tmp->CURRMODE) {
				Disp_tmp->CONF = Data_tmp->CONF;
				asm("nop;");
				if(Disp_tmp->CURRMODE==CP_MODE && M_num==P_CP)
					break;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				if(CP_MODE==Disp_tmp->CURRMODE)
					M_num = P_CP;
				else
					M_num = Disp_tmp->CURRMODE;
				ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				MenuRedrawFlag |= MENU_CHANGE;
				HelpRedrawFlag &= ~HELP_FUN_ON;
			}
		}
		break;
	case K_Help_Key:   /*Help menu, UTIL menu*/
		if((UTILITY.LOCK_KEY)||(REM_CONT)||(M_num==P_CAL_MODE)||(DGIOCtrlFlag & EXT_Frame_CONT_KB)||(CtrlFlag1&Cal_Wait_moment))
			break;

		if( KeyInFlag & SHIFT_KEY ) {
			Soft_Key_Temp = 1;
			KeyInFlag &= ~SHIFT_KEY;
			PEL3000_LED_Control(LED_SHIFT, Switch_OFF);
			if(M_num != P_UTIL_SYSINFO) {
				if( (M_num==P_UTIL_SYSMEMO)&&(UTILITY.SHORT_CTL)&&(KeyInFlag&SHIFT_KEY)&&(KeyInFlag&PRESET_KEY)&&(UTILITY.LOAD_CTL) )
					System_Info_Test_Mode = 1;
				else
					System_Info_Test_Mode = 0;
				M_num = P_UTIL_SYSINFO;
				System_Info_Memo = 0;
				ClrDispCnt(0x00, 0x00, 3, 0x00, 0x00, 0x00);
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				ChanRedrawFlag |= BG_CLEAR;
			}
			HelpRedrawFlag &= ~HELP_FUN_ON;
		} else {
			if( !(HelpRedrawFlag & HELP_FUN_ON)) {
				Soft_Key_Temp=0;
				Help_Key_Flag=0;
				HelpFunction();
				if(M_num!=P_HELP_HELP)
					H_M_num = M_num;
				M_num = P_HELP_HELP;
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				HelpRedrawFlag |= HELP_FUN_ON;
			}
		}
		break;
 	case K_F1_Key ... K_F5_Key:    
		if(CtrlFlag1&Cal_Wait_moment) {
			if(CAL_HI_LOW_SET_OK) {
				if(key!=K_F5_Key)
					break;
			} else
				break;
		}
		key	= key & 0x7;
		if((UTILITY.LOCK_KEY)||(REM_CONT)||(DGIOCtrlFlag & EXT_Frame_CONT_KB)||(DGIOCtrlFlag & RUN_SEQ_CHAN))
			break;
		Check_KNOB_VAL_Count = Check_KNOB_VAL_change_time;
		Soft_Key_Temp = key;
		ItemProcess(M_num,key-1);       /*M_num changed in this function.*/
		RestoreRealChan();
		break;
	default:
		break;
	}
	return(inform_cnt);
}

typedef union	{				// Byte  -  Addressable INT
	unsigned short i;			// unsigned short  	:  Var.i
	unsigned char b[2];			// unsigned char  	:  Var.b[0]:Var.b[1]
} BAINT;

extern UBYTE  LoadON_Time[4];
extern void Show_TimeUp_Window(void);
extern void Show_Seq_fix(void);

void ShortHold_Process(void) {
	p3k_send_tx_list tx_data;

	if( (P3k_Chan_Data.CONF.Short_Key)&&(UTILITY.SHORT_CTL)&&(VarDelayCnt) ) {
		UTILITY.SHORT_CTL = Switch_OFF;

		tx_data.ADDRH = Machine_Command;
		tx_data.ADDRL = Machine_Soft_Start;
		SendTXData(&tx_data);

		tx_data.ADDRH = Para_Ext_Command;
		tx_data.ADDRL = Para_Ext_Setting;
		SendTXData(&tx_data);

		tx_data.ADDRH = Machine_Command;
		tx_data.ADDRL = Machine_Load_OnOff;
		SendTXData(&tx_data);

		SysRedrawFlag |= PROG_UPDATA+ SHORT_UPDATA;
		DMA_Update_Flag = 1;
		PEL3000_LED_Control(LED_SHORT, UTILITY.SHORT_CTL);
#if Enable_Short_invalidate
		PEL3000_LED_Control(LED_LOAD, UTILITY.LOAD_CTL);
#endif
	}
}

void CutOffTime_Process(void) {
	p3k_send_tx_list tx_data;
	ULONG Load_Second;
	BAINT IntVal;
	if( (P3k_Chan_Data.CONF.cut_off_time_total)&&(UTILITY.LOAD_CTL)&&(Normal_Load==P3k_Chan_Data.Load_Type) ) {
		IntVal.b[0] = LoadON_Time[3];
		IntVal.b[1] = LoadON_Time[2];
		Load_Second = IntVal.i*60*60 + LoadON_Time[1]*60 + LoadON_Time[0];

		if(Load_Second>=P3k_Chan_Data.CONF.cut_off_time_total) {
			Show_TimeUp_Window();
			UTILITY.LOAD_CTL = Switch_OFF;
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Load_OnOff;
			SendTXData(&tx_data);
			PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
			SysRedrawFlag |= PROG_UPDATA;
			DMA_Update_Flag = 1;
		}
	}
#if debug_tool
#define Machine_FGPA_TEST			0x70
	if(M_num==0x2A) {
		if(FPGA_test_status) {
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_FGPA_TEST;
			SendTXData(&tx_data);
		}
		DMA_Update_Flag = 1;
		DataRedrawFlag |= PARA_CHANGE;
	}
#endif

}

char CheckLongPush(BYTE key, BYTE cnt) {
	static BYTE key_temp=0;

	if(KeyInFlag & LONG_PUSH) {
		if(cnt=='\xff') {
			KeyInFlag &=~(LONG_PUSH);
			if(KeyInFlag & LONG_PUSH_DONE)			/* Key Release and Job done */
				return(1);
			else {
				KeyInFlag |= (LONG_PUSH_DONE);
				return(2);		/* Do save/reacll */
			}
		} else {
			if((cnt==0)&&(key_temp==key))
				LongPush_CT++;							/* Wait few time */
			else {
				LongPush_CT=0;
				KeyInFlag |= LP_ON;
			}

			key_temp=key;
			if(LongPush_CT>= LONG_PUSH_TIME) {
				KeyInFlag &=~(LONG_PUSH);
				LongPush_CT=LONG_PUSH_TIME;		/* Save or Recall */
				if( KeyInFlag & LONG_PUSH_DONE)
					return(1);
				else {
					KeyInFlag|=LONG_PUSH_DONE;
					return(2);	/* Do save/reacll */
				}
			} else
				return(1);
		}
	} else
		return(0);	/* Do nothing */
}



extern STR_PARSER_COMD comd_UART;
extern void InitMDMA_Copy(UWORD *source, UWORD *dest, ULONG num);
extern void MDMA_Copy(UWORD *source, UWORD *dest);
extern void Wait_For_MDMA_Ready(void);
void MenuDispTask(void *data) {

#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
	OS_CPU_SR  cpu_sr;
	cpu_sr = 0; 								 /* Prevent compiler warning						   */
#endif

	char str[50];
	int i;
	BYTE key, cnt, keyboard_flag=0;
	p3k_send_tx_list tx_data;
	UBYTE SEQ_data;
	char status=0xff,temp,mem,load_off;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	static unsigned char setDMAUpdateSpeed;

	Menu_Message_Data_flag	= 0;
	Output_Buffer_Count		= 0;
	Freeze_Keyboard			= 1;
	Remote_ChanNo			= 0;
	Blink_State				= 0x02;
	Default_info			= 0;
	InitMachineProc();
#if 1 //Adam_0819
	if(FPGA_R[7]!=1010) {
		Menu_Message("FPGA Communication failure!! ",30,210);
		CtrlFlag1 |= Disp_Middle_Message;
		DMA_Update_Flag = 1;
		Update_Panel();
		OSTimeDly(200);

	} else if(p3k_Cal_data.Data_Ready!=200) {
		Menu_Message(" Loading Cal Data default!! ",50,210);
		CtrlFlag1 |= Disp_Middle_Message;
		DMA_Update_Flag = 1;
		Update_Panel();
		OSTimeDly(200);
	}
#else
	if(p3k_Cal_data.Data_Ready!=200) {
		Menu_Message(" Loading Cal Data default!! ",50,210);
		CtrlFlag1 |= Disp_Middle_Message;
		DMA_Update_Flag = 1;
		Update_Panel();
		OSTimeDly(200);
	}
#endif
	if(P3k_Chan_Data.INFO.MACHTYPE==0x07) {
		Menu_Message(" MACHTYPE Error!! ",50,210);
		CtrlFlag1 |= Disp_Middle_Message;
		DMA_Update_Flag = 1;
		Update_Panel();
		OSTimeDly(200);
	}
	DMA_Update_Flag = 1;
	Update_Panel();
	ClearKeyBoard();
	while(1) {
		/*Command from keyboard.*/
		keyboard_flag=0;
		if( (0==Freeze_Keyboard)&&(0==Upgrading_Flag)) {

			if(OSSemAccept(KeyCodeReadySemPtr)) {
				intf_UART.esr.opc = 0; //Machine_Standard_Status.Event&=0xfe;
				key = KeyTaskBuf[0];
				cnt = KeyTaskBuf[1];

				if((key>111)&&(key!=123)&&(M_num!=P_Input_Password)&&(M_num!=P_Test_Func)) {
					KeyinBuf[0] =KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
					KeyInFlag&=(~DIGI_KEY_IN);
				}
				OSSemPost(KeyCodeDoneSemPtr);
				if(delaySeqAlarmDisplay)delaySeqAlarmDisplay--;
#if Enable_Ring_Count
				if( (CtrlFlag1&Alarm_Latch)||(CtrlFlag1&Function_Lock)||(UVP_Tone_Count)||(SEQ_Tone_Count))
#else
				if( (CtrlFlag1&Alarm_Latch)||(CtrlFlag1&Function_Lock) )
#endif
				{
					if(delaySeqAlarmDisplay) {

					} else if((K_Knob_Select==key)||(K_Enter_Key==key)) {
#if Enable_Ring_Count
						if(UVP_Tone_Count>1) {
							Tone_Flag&=(~0x01);
							UVP_Tone_Count = 0;
						}
						if(SEQ_Tone_Count>1) {
							Tone_Flag&=(~0x08);
							SEQ_Tone_Count = 0;
						}
#endif
						p3k_Measure_Data.Alarm = No_Alarm;
						Frame_Change();
#if 1 //Adam_2015_0706
						if(M_num<= 0x0D) {
							if(DispMode==2)DispMode=1;
						} else if(P_NSeq_EXECUTE==M_num) {
							M_num = P_Seq_Normal;
							ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
							FunctionFlag   = FUNC_CLEAR;
						} else if(P_FSeq_EXECUTE==M_num) {
							M_num = P_Seq_Fast; /* into sequence Main */
							ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
						} else {
							if(DispMode==1) DispMode=0;
						}
						Alarm_logo_flag =0;
						ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
						DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
						MenuRedrawFlag |= MENU_CHANGE;
						FunctionFlag   = FUNC_CLEAR;
						HelpRedrawFlag &= ~HELP_FUN_ON;
#else
						if(M_num<= 0x0D) {
							if(DispMode==2)DispMode=1;
						} else {
							if(DispMode==1) DispMode=0;
						}
						Alarm_logo_flag =0;
						ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
						DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
						MenuRedrawFlag |= MENU_CHANGE;
						HelpRedrawFlag &= ~HELP_FUN_ON;
#endif



						if(CtrlFlag1&Alarm_Latch) {
							tx_data.ADDRH = Machine_Command;
							tx_data.ADDRL = Machine_Prot_Status;
							SendTXData(&tx_data);
						}
						CtrlFlag1 &= ~Alarm_Latch;
						CtrlFlag1 &= ~Function_Lock;
						CtrlFlag1 &= ~Disp_Middle_Message;
						CtrlFlag1 |= Float_Windows_DispOff;
					}
					key = K_Invalid_Key;
					DMA_Update_Flag = 1;
				}
				if(Operation_Slave==P3k_Chan_Data.CONF.Para_Data.Mode) {
					if( (K_Enter_Key==key||K_Knob_Select==key||'\xd6'==key||K_Shift_Key==key)||((KeyInFlag&SHIFT_KEY)&&(K_Clear_Key==key||K_Main_Key==key)) ) {

					} else
						key = K_Invalid_Key;
				}
				if( (CtrlFlag1&P_Recall_Flag)||(CtrlFlag1&M_Recall_Flag) ) {
					if( (K_Enter_Key==key)||(K_Knob_Select==key) ) {
						if(CtrlFlag1&P_Recall_Flag) {
							Recall2Mem( SR_PRESET_MODE, p3k_File_Utility_BAR.PRE_MEMORY_ADDR);
							if((Data_tmp->CURRMODE!=Disp_tmp->CURRMODE)&&(UTILITY.LOAD_CTL)) {
								UTILITY.LOAD_CTL = Switch_OFF;
								PEL3000_LED_Control( LED_LOAD, Switch_OFF );
								SysRedrawFlag |= PROG_UPDATA;
								tx_data.ADDRH = Machine_Command;
								tx_data.ADDRL = Machine_Load_OnOff;
								SendTXData(&tx_data);
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
						} else {
							Recall2Mem(SR_MEMORY_MODE, p3k_File_Utility_BAR.MEMORY_ADDR);
							if((Data_tmp->CURRMODE!=Disp_tmp->CURRMODE)&&(UTILITY.LOAD_CTL)) {
								UTILITY.LOAD_CTL = Switch_OFF;
								PEL3000_LED_Control( LED_LOAD, Switch_OFF );
								SysRedrawFlag |= PROG_UPDATA;
								tx_data.ADDRH = Machine_Command;
								tx_data.ADDRL = Machine_Load_OnOff;
								SendTXData(&tx_data);
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
						key = K_Invalid_Key;
					}
					CtrlFlag1 &= (~P_Recall_Flag);
					CtrlFlag1 &= (~M_Recall_Flag);
					DMA_Update_Flag = 1;
				}

				if( (CtrlFlag1&Disp_Middle_Message)&&((CtrlFlag1&Float_Windows_DispOn)==0) ) {
					CtrlFlag1 &= ~Disp_Middle_Message;
					CtrlFlag1 |= Float_Windows_DispOff;
					DMA_Update_Flag = 1;
#if Enable_Ring_Count //seq complete trig signal					
					if(Tone_Flag&0x08) {
						SEQ_Tone_Count = 0;
						Complete_Count = 0;
						Tone_Flag &= ~0x08;
					}
#endif
				}

				if( (CtrlFlag1&Disp_IRange_Window)&&(key!=F2_Key) )
					Float_Window_Count = 0;

				if(Blink_State&0x01)
					Blink_State&=(~0x01);

				if( (Data_tmp->CONF.Ext_Setting.Control)&&(P_CC==M_num||P_CR==M_num||P_CV==M_num||P_CP==M_num) ) {
					if( K_Knob_Select==key||K_Knob_Rotate==key||K_Enter_Key==key||(key>=K_Digital_0&&key<=K_Digital_Dot) )
						key = K_Invalid_Key;
				}
				inform_cnt = KeyProcess(key, cnt); /*M_num changed here. Using LcdUnlockSemPtr and GUI.*/
				intf_UART.esr.opc = 1; //Machine_Standard_Status.Event |= 0x01;
				keyboard_flag=1;
			}
		} else {
			if(Freeze_Keyboard)
				Freeze_Keyboard--;
		}

		/*Command from programming*/
		if(_PARSER_SEND_MSQ == comd_UART.fun) {
			scpiRunMSQ();
			if(CtrlFlag1&Disp_Middle_Message) {
				CtrlFlag1 &= ~Disp_Middle_Message;
				CtrlFlag1 |= Float_Windows_DispOff;
			}

		}
		if((CtrlFlag1&Disp_IRange_Window)&&(Float_Window_Count==0)) {
			CtrlFlag1 &= ~Disp_IRange_Window;
			CtrlFlag1 |= Float_Windows_DispOff;	//FloatWindowsDispOff();
			DataRedrawFlag |= PARA_CHANGE;
			DMA_Update_Flag = 1;
		}

		ShortHold_Process();
		CutOffTime_Process();
		LCD_Blink();
		CalWaitProcess();
		AlarmProcess(key);
		Wait_For_MDMA_Ready();
		DispMenuProcess();
		DispMeasureData();
		DispUpperProcess();
		DispRightProcess();
		DispParameter(cnt);
		FileUtilDispProc();
#if 1
		Update_Panel();
#endif
		if( (M_num!=P_PROG_EXECUTE)&&(M_num!=P_NSeq_EXECUTE)&&(M_num!=P_FSeq_EXECUTE)) FM_MainTask();
		if(M_num==P_UTIL_KEYPAD) KeyPadProc();

		do {
			if(DGIOCtrlFlag&REM_Mode_Fast)CutOffTime_Process();
			if(p3k_Measure_Data.Alarm != 0) {
				if(UnReg_Alarm != p3k_Measure_Data.Alarm) {
#if Enable_Ring_Count
					if((UTILITY.Master_Alarm_Tone)&&(Tone_Flag==0)) {
						if(UVP_Alarm != p3k_Measure_Data.Alarm) {
							Tone_Flag|=0x01;
							Alarm_Count = 250;
							BuzzerFunction(Buzzer_Alarm,Alarm_Count--);
						} else {
							if(UVP_Tone_Count>1) {
								Tone_Flag|=0x01;
								Alarm_Count = 250;
								BuzzerFunction(Buzzer_Alarm,Alarm_Count--);
							} else {
							}
						}
					}
#else
					if((UTILITY.Master_Alarm_Tone)&&(Tone_Flag==0)) {
						Tone_Flag|=0x01;
						Alarm_Count = 250;
						BuzzerFunction(Buzzer_Alarm,Alarm_Count--);
					}
#endif

				} else {
					if((UTILITY.UnReg_Alarm_Tone)&&(Tone_Flag==0)) {
						Tone_Flag|=0x04;
						UnReg_Count = 200;
						BuzzerFunction(Buzzer_UnReg,UnReg_Count--);
					}
				}
			} else if(p3k_Measure_Data.Go_NoGo == 1) {
				if((UTILITY.Master_NG_Tone)&&(Tone_Flag==0)) {
					Tone_Flag|=0x02;
					NG_Count = 300;
					BuzzerFunction(Buzzer_NG,NG_Count--);
				}
			}
#if Enable_Ring_Count
			else if((SEQ_Tone_Count>1)&&(Tone_Flag==0)&&(UTILITY.Master_Alarm_Tone)) {
				Tone_Flag|=0x08;
				Complete_Count = 800;
				BuzzerFunction(Buzzer_Complete,Complete_Count--);
			} else if((UVP_Tone_Count>1)&&(CtrlFlag1==1)&&(Alarm_logo_flag)&&(Tone_Flag==0)&&(UTILITY.Master_Alarm_Tone)) {
				Tone_Flag=1;
				Alarm_Count = 250;
				BuzzerFunction(Buzzer_Alarm,Alarm_Count--);
			} else {

			}
#endif

			OSTimeDly(2);

		} while(DGIOCtrlFlag&REM_Mode_Fast);

	}
}

void TimerTask(void *data) {
	p3k_send_tx_list tx_data;
	UWORD time_cont=0,Blink_time=0;
	UBYTE Fetch_Quer_Count = Fetch_Quer_time; /* Check Count ,if Count=0 ,Master Send Measure Query*/
	UBYTE Measure_Quer_Count = Measure_Quer_time;
#if 1//Normal_TEST
	static unsigned char CountSec;
#endif

	RTCDisplayCount	= 0;
	while(1) {
		if(Float_Window_Count)
			Float_Window_Count--;

		if(Check_KNOB_VAL_Count)
			Check_KNOB_VAL_Count--;

		if(Blink_State&0x01) {
			Blink_time++;
			if(Blink_time>50) {
				Blink_time=0;
				Blink_State|=0x04;
			}
		}
#if Enable_OCP_function
		if(OCP_Load==P3k_Chan_Data.Load_Type) {
			if(UTILITY.LOAD_CTL) {
				FPGA_OCP_OPP_Ctrl();
			}
		}
#endif
#if Enable_OPP_function
		if(OPP_Load==P3k_Chan_Data.Load_Type) {
			if(UTILITY.LOAD_CTL) {
				FPGA_OCP_OPP_Ctrl();
			}
		}
#endif

		/* Send Fetch Query by 20mS */
		if(Fetch_Quer_Count>0)
			Fetch_Quer_Count--;
		if((Fetch_Quer_Count==0)&&(System_Ready)) {
			Fetch_Quer_Count = Fetch_Quer_time;
			AutoExecuteFlag |= Slave_Data_Update;
		}

		/* Send Measure Query by 100mS */
		if(UTILITY.MEAS_SCAN) {
			if(Measure_Quer_Count>0)
				Measure_Quer_Count--;
			if((Measure_Quer_Count==0)&&(System_Ready)) {
				Measure_Quer_Count=Measure_Quer_time;
				AutoExecuteFlag |= Measure_Data_Update;
			}
		}

		if(CountSec)
			CountSec--;
		else {
			CountSec = 100;
#if Enable_Ring_Count
			if(UVP_Tone_Count) {
				if(UVP_Tone_Count<=601) UVP_Tone_Count--;
				if(UVP_Tone_Count==1)	Tone_Flag &= ~(0x01);
			}
			if(SEQ_Tone_Count) {
				if(SEQ_Tone_Count<=601) SEQ_Tone_Count--;
				if(SEQ_Tone_Count==1)	Tone_Flag &= ~(0x01);
			}

#endif
#if Normal_TEST
			test_Frequency = test_CountFrequency;
			test_CountFrequency =0;
			test_Frequency1 = test_CountFrequency1;
			test_CountFrequency1 =0;
			test_Frequency2 = test_CountFrequency2;
			test_CountFrequency2 =0;
#endif
		}

		if(RTCDisplayCount)
			RTCDisplayCount--;
		else {
			RTCDisplayCount = 1000; //Check it every 10 second.
			AutoExecuteFlag |= Time_Update;
		}

		if(!Upgrading_Flag && System_Ready && (M_num != P_CAL_MODE) && (M_num != P_Input_Password)) {
			if(time_cont<50)
				time_cont++;
			else {
				time_cont=0;
				AutoExecuteFlag |= Backup_Data_To_Fram;
			}
		}

		do {
			OSTimeDly(1);
		}
#if Enable_RemoteFast
		while(0);
#else
		while(DGIOCtrlFlag&REM_Mode_Fast);
#endif
	}
}

void RandomDelay(void) {
	int Random_Number,i;
	Random_Number = (rand()%10)+1;
	Random_Number *= 10000;
	for(i=0 ; i<Random_Number ; i++) {
		asm("nop;");
		ssync();
	}
}

void ConstDelay(UWORD Delay_Para) {
	int Random_Number,i;
	//Random_Number = (rand()%10)+1;
	Random_Number = Delay_Para*2000;
	for(i=0 ; i<Random_Number ; i++) {
		asm("nop;");
		ssync();
	}
}
/*=======================================================================================
1.每20mS更新Slave的參數、詢問目前SEQ組數(如果正在Run SEQ)、處理外部控制的訊號(並聯或External)
2.每10秒更新RTC資料
3.每隔10ms確認是否要啟動Buzzer功能
4.每隔500mS備份系統資料到FRAM
========================================================================================*/
void AutoExecuteTask(void *data) {
	p3k_send_tx_list tx_data;
	AutoExecuteFlag=0;

	while(1) {
		if(AutoExecuteFlag & Slave_Data_Update) {
			AutoExecuteFlag &= (~Slave_Data_Update);
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Meas_Query;
			SendTXData(&tx_data);

			if( (UTILITY.LOAD_CTL)&&(Prog_Load==P3k_Chan_Data.Load_Type||NSeq_Load==P3k_Chan_Data.Load_Type||FSeq_Load==P3k_Chan_Data.Load_Type)&&((P_PROG_EXECUTE==M_num)||(P_NSeq_EXECUTE==M_num)||(P_FSeq_EXECUTE==M_num)) ) {
				if(Prog_Seq_Data.SEQ_Complete==0) {
					tx_data.ADDRH = Machine_Command;
					tx_data.ADDRL = Machine_Seq_ID;
					SendTXData(&tx_data);
					DataRedrawFlag |= PARA_CHANGE;
				} else {
					if(Prog_Seq_Data.Last_Load_Setting==Switch_OFF) {
						UTILITY.LOAD_CTL = Switch_OFF;
						SysRedrawFlag |= PROG_UPDATA;
						PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
						tx_data.ADDRH = Machine_Command;
						tx_data.ADDRL = Machine_Load_OnOff;
						SendTXData(&tx_data);
					}
					if( Prog_Load==P3k_Chan_Data.Load_Type ) {
						if(Prog_Seq_Data.Total_Count) {
							M_num = P_PROG_Detail; /* into sequence view */
#if Enable_Ring_Count
							last_menu = 0xFF;
							if(UTILITY.Master_Alarm_Tone) {
								SEQ_Tone_Count = P3k_Disp_Data.PROT.SEQ_Tone_len; //601;
								Complete_Count = 800;//Alarm_Count = 250;
							}
#endif

						} else
							M_num = P_PROG_MAIN;	 /* into sequence Main */
						SEQ_Save_Status = 0;

						if(Prog_Seq_Data.Total_Count > 4)
							ClrDispCnt(0x00, 0x00, 3, 0x00, 0x00, 0x00);
						else
							ClrDispCnt(0x00, 0x00, Prog_Seq_Data.Total_Count-1, 0x00, 0x00, 0x00);

						MenuRedrawFlag |= MENU_CHANGE;
						DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
						ChanRedrawFlag |= BG_CLEAR;
						FunctionFlag = FUNC_CLEAR;
					} else {
#if 1					//Adam 2016_0314
						unsigned char R_IRange , R_VRange;
						R_IRange = (Prog_Seq_Data.FPGA_Seq_Data[Prog_Seq_Data.Setting_Count-1].SEQ_Range)%4; //0~5
						R_VRange = (R_IRange)/2;
						R_IRange = (R_IRange % 2);
						///asm("nop;");asm("nop;");asm("nop;");
						P3k_Chan_Data.VRange =R_VRange;
						P3k_Chan_Data.IRange = R_IRange;
						P3k_Disp_Data.VRange =R_VRange;
						P3k_Disp_Data.IRange = R_IRange;
#endif

						if(CC_MODE==P3k_Chan_Data.CURRMODE)
							M_num = P_CC;
						else if(CR_MODE==P3k_Chan_Data.CURRMODE)
							M_num = P_CR;
						else if(CV_MODE==P3k_Chan_Data.CURRMODE)
							M_num = P_CV;
						else if(CP_MODE==P3k_Chan_Data.CURRMODE)
							M_num = P_CP;
						ClrDispCnt(0x01,0x00,0x02,0x00,0x00,0x00);
						MenuRedrawFlag |= MENU_CHANGE_Again;
						DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
						ChanRedrawFlag |= BG_CLEAR;
						Menu_Message(" Sequence Complete ",50,210);
						RedrawModeLogo =1;
						CtrlFlag1 |= Disp_Middle_Message;
						FunctionFlag = FUNC_CLEAR;
						ClearKeyBoard();
#if Enable_Ring_Count
						last_menu = 0xFF;
						if(UTILITY.Master_Alarm_Tone) {
							SEQ_Tone_Count = P3k_Disp_Data.PROT.SEQ_Tone_len; //601;
							Complete_Count = 800;//Alarm_Count = 250;
						}
#endif
					}
				}
			}
			FPGA_ISR();
		} else {
			if(AutoExecuteFlag & Measure_Data_Update) {
				AutoExecuteFlag &= (~Measure_Data_Update);
				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = 0x18;
				SendTXData(&tx_data);
			} else if(AutoExecuteFlag & Backup_Data_To_Fram) {
				AutoExecuteFlag &= (~Backup_Data_To_Fram);
				BackupStatus();
			}
			if(BeepCount>0) {
				BeepCount--;
				BeepStatus = Switch_ON;
				BuzzerTone(BeepCount);
			} else if(BeepCount==0) {
				BeepCount--;
				BeepStatus = Switch_OFF;
				BuzzerOnOff(0);//OFF
			}
			if((CtrlFlag1&BEEP_ACT)&&(UTILITY.BEEP==0)&&(BeepStatus==Switch_OFF)) {
				CtrlFlag1 &= (~BEEP_ACT);
				BeepCount = 2;
				BuzzerOnOff(1);			/*ON*/
				BuzzerTone(BeepCount-1);
			}
			if((DGIOCtrlFlag&REM_Mode_Fast)==0) {
				if(AutoExecuteFlag & Time_Update) {
					AutoExecuteFlag &= (~Time_Update);
					update_rtc();     //Change CtrlFlag every 10 sec.
				}
			}
		}
		OSTimeDly(1);
	}
}
//--------------------------------------------------------------------------
// Function:	app_launch_threads
//
// Parameters:	None
//
// Return:		None
//
// Description:	This is called from app_main and launches
// the application threads.
//--------------------------------------------------------------------------
extern void UsbMainTask(void *data);
extern void LuaScriptTask(void *data);
void app_launch_threads(void) {
	OS_STK *stack;
	INT8U OS_result;
	INT32U i;
	BYTE TData=55;
	BYTE RData;
	UBYTE comm_err;
	/*-----------------KeyTask Create-----------------*/
	stack = (OS_STK *)malloc( STACK_SIZE * sizeof( OS_STK) );
	if (stack == 0) {
		printf("Heap allocation error\n");
		return;
	}
	if ((OS_result = OSTaskCreateExt(KeyTask,
	                                 (void *)NULL,
	                                 &stack[STACK_SIZE-1],
	                                 6,
	                                 6,
	                                 &stack[0],
	                                 STACK_SIZE,
	                                 (void *)0,
	                                 0 ))) {
		while(1)
			printf("Error\n");
	}
	/*-----------------MenuDispTask Create-----------------*/
	stack = (OS_STK *)malloc( STACK_SIZE * sizeof( OS_STK) );
	if (stack == 0) {
		printf("Heap allocation error\n");
		return;
	}
	if ((OS_result = OSTaskCreateExt(MenuDispTask,
	                                 (void *)NULL,
	                                 &stack[STACK_SIZE-1],
	                                 16,
	                                 16,
	                                 &stack[0],
	                                 STACK_SIZE,
	                                 (void *)0,
	                                 0 )))while(1) {
			printf("Error\n");
		};
	/*-----------------TimerTask Create-----------------*/
	stack = (OS_STK *)malloc( STACK_SIZE * sizeof( OS_STK) );
	if (stack == 0) {
		printf("Heap allocation error\n");
		return;
	}
	if ((OS_result = OSTaskCreateExt(TimerTask,
	                                 (void *)NULL,
	                                 &stack[STACK_SIZE-1],
	                                 5,
	                                 5,
	                                 &stack[0],
	                                 STACK_SIZE,
	                                 (void *)0,
	                                 0 ))) {
		printf("Error Task %d\n",7);
		while(1);
	};

	/*-----------------AutoExecuteTask Create-----------------*/
	stack = (OS_STK *)malloc( STACK_SIZE * sizeof( OS_STK) );
	if (stack == 0) {
		printf("Heap allocation error\n");
		return;
	}
	if ((OS_result = OSTaskCreateExt(AutoExecuteTask,
	                                 (void *)NULL,
	                                 &stack[STACK_SIZE-1],
	                                 15,
	                                 15,
	                                 &stack[0],
	                                 STACK_SIZE,
	                                 (void *)0,
	                                 0 ))) {
		printf("Error Task %d\n",7);
		while(1);
	};
	/*-----------------UsbMainTask Create-----------------*/
	stack = (OS_STK *)malloc( STACK_SIZE * sizeof( OS_STK) );
	if (stack == 0) {
		printf("Heap allocation error\n");
		return;
	}

	if ((OS_result = OSTaskCreateExt(UsbMainTask,
	                                 (void *)NULL,
	                                 &stack[STACK_SIZE-1],
	                                 18,
	                                 18,
	                                 &stack[0],
	                                 STACK_SIZE,
	                                 (void *)0,
	                                 0 ))) {
		printf("Error Task %d\n",17);
		while(1);
	};
	OSTimeDly(10);

	/*-----------------InterfaceTask Create-----------------*/
	stack = (OS_STK *)malloc( STACK_SIZE * sizeof( OS_STK) );
	if (stack == 0) {
		printf("Heap allocation error\n");
		return;
	}
	if ((OS_result = OSTaskCreateExt(InterfaceTask,
	                                 (void *)NULL,
	                                 &stack[STACK_SIZE-1],
	                                 19,
	                                 19,
	                                 &stack[0],
	                                 STACK_SIZE,
	                                 (void *)0,
	                                 0 ))) {
		printf("Error Task %d\n",18);
		while(1);
	};


}// end of app_launch_threads
//--------------------------------------------------------------------------//
// Function:	IVG12_ISR_Hook
//
// Parameters:	None
//
// Return:		None
//
// Description:	IVG12_ISR_Hook
//--------------------------------------------------------------------------//
#include <sys\exception.h>
#include <cdefBF533.h>
#include <sys/05000311.h>
extern void isrhandler_USB_Hc(void);
extern void isrhandler_GPIB(void);
extern void hwacces_isr_hw_disable( void );
#pragma default_section(CODE, "L1_code")
void IVG12_ISR_Hook (void) {
	static unsigned short PF_FLAG;
	FIO_ANOM_0311_FLAG_R(PF_FLAG, pFIO_FLAG_D);
	if (PF_FLAG & PF15) {			// if PF15 is interrupting source,
		FIO_ANOM_0311_FLAG_W(PF15,pFIO_FLAG_C);
		isrhandler_USB_Hc();
	}
	if (PF_FLAG & PF13) {			// if PF13 is interrupting source,
		FIO_ANOM_0311_FLAG_W(PF13,pFIO_FLAG_C);
#if 1 //Adam_0819
		if(IsfpgaOk)FPGA_ISR();
#else
		FPGA_ISR();
#endif
	}
	if (PF_FLAG & PF14) {			// if PF14 is interrupting source,
		FIO_ANOM_0311_FLAG_W(PF14,pFIO_FLAG_C);
		isrhandler_GPIB();
	}
}// end of IVG12_ISR_Hook
#pragma default_section(CODE, "sdram0")

/*********************************************************************
Function
*********************************************************************/
BYTE Empty_Func(BYTE menu_no, BYTE item_no) {
//       HintDelay("Not available under this mode");
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////
void ItemProcess(BYTE m_no,BYTE its_no) {
	/*VER 0.0.2*/
//  WORD   its_no;
	MENU   tempMenu;
	MITEMS *tempItem;

//  its_no-='s';   /*its_no: the Item Number 0,...,5*/
	tempMenu=_menu[m_no];
	tempItem=&(tempMenu/*->mptr*/)[its_no];

	if(*(tempItem->a)!=(void *)Empty_Func)
		tempItem->a(m_no,its_no);
	/*execute the function for item selected & change item's condition*/
}
void ClrDispCnt(char mode, char ct, char sec, char ssc, char bct, char scl) {
	DispMode = mode;
	DispCT = ct;
	DispScrEndCT = sec;
	DispScrStartCT = ssc;
	B_DispCT = bct;
	DispScrCurrLoc = scl;
}

void Debug_printf(char *Message) {
#if Normal_TEST
	printf(Message);
#endif
}

void InitMachineProc(void) {
	char i,j,k,l,str[100],SYNC_TMEM_temp,multi_Channel_temp,Parallel_Result;
	BYTE c_chan[8];
	UBYTE oserr;
	UBYTE *Backup_Data,*Actual_Data;

	p3k_send_tx_list tx_data;
	struct tm _mTIME; //Current Time update by TimerTask
	P3k_Data_Str 	*Data_tmp	= &P3k_Chan_Data;
	P3k_Disp_Str 	*Disp_tmp	= &P3k_Disp_Data;
	P3k_Backup_Str	*Backup_tmp	= &FRAM_Data.P3k_Backup_Data;

	if(M_num == P_CAL_MODE && M_num == P_Test_Func)
		return;

	CursorInit();
#if Normal_TEST
	ClrScreen(Parameter_Bottom_Bolor);  /*Test for 8bpp mode(dark blue).  Added by Kevin Meng 2004.09.22*/
	HelpRedrawFlag=0;
#endif

	ChanNo=0;	// 2010_05
	R_Chan[ChanNo]=0;
	ChanID[0].INFO.MACHTYPE = MODEL3031E;
	System_Ready		= 0;
	TxBoardCastInit	= 0;

	rtc_get(&_mTIME);
	TIMERSET.YEAR	 = _mTIME.tm_year;
	TIMERSET.MONTH	 = _mTIME.tm_mon;
	TIMERSET._DAY	 = _mTIME.tm_mday;
	TIMERSET._HOUR	 = _mTIME.tm_hour;
	TIMERSET._MINUTE = _mTIME.tm_min;

	if( (FRAM_Data.Data_Ready==200)&&(Backup_tmp->INFO.MACHTYPE == Data_tmp->INFO.MACHTYPE) ) {
		DispMode		= FRAM_Data.DispMode;
		M_num			= FRAM_Data.M_num;
//M_num =	1;///
		DispScrEndCT	= FRAM_Data.DispScrCT;
		if(1) { //M_num==P_UTIL_INTERFACE)
			D_interface.INTERFACE	= UTILITY.INTERFACE;
			D_interface.BAUD		= RS232.BAUD;
			D_interface.STOP		= RS232.STOP;
			D_interface.PARITY		= RS232.PARITY;
			D_interface.MYADDR		= GPIBPAR.MYADDR;
		}

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
			Data_tmp->P_DATA[i] = Backup_tmp->P_DATA[i];
#if Enable_Battery_Discharge
		if(FRAM_Data.BattData.checksum ==0x55) { //recall lastValue
			BattDisp = FRAM_Data.BattData;
		} else { //recall default
			BattDisp.status = BATT_CONFIG;
			BattDisp.timeCnt = 0;
			BattDisp.checksum = 0x55;
			BattDisp.stopStatus = 0;
			BattDisp.Mode = CC_MODE;
			BattDisp.Range = 0;
			BattDisp.SRUPRange = 0;
			BattDisp.SRDWRange = 0;
			BattDisp.SRUP = (ptrMODEL_TYPE->CC)[2].Def;
			BattDisp.SRDW = (ptrMODEL_TYPE->CC)[2].Def;
			BattDisp.Setting = 0;
			BattDisp.StopValt = 300;
			BattDisp.StopHour=0;
			BattDisp.StopMin=0;
			BattDisp.StopSec=0;
			BattDisp.StopTime=0;
			BattDisp.StopCapa=20;
		}
#endif
#if Enable_LED_function
		if(FRAM_Data.fLedData.checksum==0x55) { //recall lastValue
			P3k_FLed_Disp = FRAM_Data.fLedData;
		} else { //recall default
			P3k_FLed_Disp.currTemp = 0;
			P3k_FLed_Disp.dataReady = 0;
			P3k_FLed_Disp.complete = 0;
			P3k_FLed_Disp.checksum = 0x55;
			for(i=0; i<12; i++)P3k_FLed_Disp.seq[i] = DEFAULT_LED_SEQ;
			FRAM_Data.fLedData = P3k_FLed_Disp;
		}
		if(FRAM_Data.cLedData.checksum==0x55) { //recall lastValue
			P3k_CLed_Disp = FRAM_Data.cLedData;
		} else { //recall default
			P3k_CLed_Disp.currTemp = 0;
			P3k_CLed_Disp.dataReady = 0;
			P3k_CLed_Disp.complete = 0;
			P3k_CLed_Disp.checksum = 0x55;
			for(i=0; i<12; i++)	P3k_CLed_Disp.seq[i] = DEFAULT_LED_SEQ;
			FRAM_Data.cLedData = P3k_CLed_Disp;
		}
#endif






	} else {
		sprintf(str,"FRAM_Data.Data_Ready=%d\n",FRAM_Data.Data_Ready);
		Debug_printf(str);
		sprintf(str,"Backup_tmp->INFO.MACHTYPE=%d\n",Backup_tmp->INFO.MACHTYPE);
		Debug_printf(str);
		sprintf(str,"Data_tmp->INFO.MACHTYPE=%d\n",Data_tmp->INFO.MACHTYPE);
		Debug_printf(str);
	}

	if(RecoverRunProgDataFlag)
		p3k_Disp_PROG = p3k_Chan_PROG;

	if(M_num==P_FILE_CHAN) {
		if( (F_Media_USB==p3k_File_Utility_BAR.MEDIA)&&(USB_Status_Display!=USB_Exist) ) {
			Save_Status	= 0;
			Recall_Status	= 0;
		} else {
			Save_Status	= 1;
			Recall_Status	= 1;
		}
	}

	if((M_num==P_CC)&&(Data_tmp->CURRMODE!=P_CC))
		M_num = Data_tmp->CURRMODE;

	RestoreRealChan();
	System_Ready	= 1;
	SysRedrawFlag |= SYS_CHANGE;
	UTILITY.FAN_SPEED=0;
	ClrScreen(Parameter_Bottom_Bolor);  /*Test for 8bpp mode(dark blue).  Added by Kevin Meng 2004.09.22*/
	ClearMenuBG(MEM_GRAY);
	status_byte_Init();
	Control_LCDBRCon();
	BasicFrame();

	p3k_Acq_4K_Measure_Data.Acq4K_Enable	= 0;
	p3k_Acq_4K_Measure_Data.Acq4K_Interval	= 2;
	p3k_Acq_4K_Measure_Data.Acq4K_PTC		= 0;
	p3k_Acq_4K_Measure_Data.Acq4K_SWC		= Acq_Max_Point;
	p3k_Acq_4K_Measure_Data.Acq4K_Ready		= 0;
	FPGA_Init();	// 2010_05
	FPGA_Ctrl();

	PEL3000_LED_Control( LED_LOAD,	Switch_OFF );
	PEL3000_LED_Control( LED_SHIFT, Switch_OFF );
	PEL3000_LED_Control( LED_PRESET,Switch_OFF );
	PEL3000_LED_Control( LED_SHORT, Switch_OFF );

	if(UTILITY.ALOAD) {
		UTILITY.LOAD_CTL = Switch_ON;

		if(Prog_Load == UTILITY.ALOAD_MODE) {	/* Flag of Run Program was turn on */
			HelpRedrawFlag &= ~HELP_FUN_ON;
			Soft_Key_Temp = 0;
			PlaceProgChain();

			if(Prog_Seq_Data.Total_Count) {
				if(M_num!=P_PROG_Detail)
					S_M_num = M_num;

				Prog_Seq_Data.SEQ_Stop_Continue = Display_Stop;
				Prog_Seq_Data.MANUAL_CTRL = 0;
				Prog_Seq_Data.SEQ_Complete = 0;
				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = Machine_Load_OnOff;
				SendTXData(&tx_data);
			} else {
				/* No Program */
				/* Sequence is not data to execute run program */
				UTILITY.LOAD_CTL = 0;
				Prog_Seq_Data.SEQ_Stop_Continue = Display_None;
			}

			M_num = P_PROG_EXECUTE;
			MenuRedrawFlag |= MENU_CHANGE;
			DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
			ChanRedrawFlag |= BG_CLEAR;
		} else if(NSeq_Load == UTILITY.ALOAD_MODE) {
			HelpRedrawFlag &= ~HELP_FUN_ON;
			Soft_Key_Temp = 0;
			PlaceNSeqChain();
			if(Prog_Seq_Data.Total_Count) {
				if(M_num!=P_PROG_Detail)
					S_M_num = M_num;
				Prog_Seq_Data.SEQ_Stop_Continue = Display_Stop;
				Prog_Seq_Data.MANUAL_CTRL = 0;
				Prog_Seq_Data.SEQ_Complete = 0;
				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = Machine_Load_OnOff;
				SendTXData(&tx_data);
			} else {
				/* No Program */
				/* Sequence is not data to execute run program */
				UTILITY.LOAD_CTL = Switch_OFF;
				Prog_Seq_Data.SEQ_Stop_Continue = Display_None;
			}
			M_num = P_NSeq_EXECUTE;
			MenuRedrawFlag |= MENU_CHANGE;
			DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
			ChanRedrawFlag |= BG_CLEAR;
		} else if(FSeq_Load == UTILITY.ALOAD_MODE) {
			HelpRedrawFlag &= ~HELP_FUN_ON;
			Soft_Key_Temp = 0;
//			WriteSEQDataToFPGA_flag = 0;
			if(P3k_FSeq_Disp.FSeq_Max_Step<0xFF00) { // 1~1000
				if(0) { //if((P3k_Disp_Data.CONF.Para_Data.Booster_Number)&&((P3k_FSeq_Disp.FSeq_Range==0)||(P3k_FSeq_Disp.FSeq_Range==2))){
					UTILITY.LOAD_CTL = Switch_OFF;
					FunctionFlag  = FUNC_CLEAR;
					Prog_Seq_Data.SEQ_Stop_Continue = Display_None;
				} else {
					PlaceFSeqMemory();
					if(M_num!=P_PROG_Detail)
						S_M_num = M_num;
					Prog_Seq_Data.SEQ_Stop_Continue = Display_Stop;
					Prog_Seq_Data.MANUAL_CTRL = 0;
					Prog_Seq_Data.SEQ_Complete = 0;
					tx_data.ADDRH = Machine_Command;
					tx_data.ADDRL = Machine_Load_OnOff;
					SendTXData(&tx_data);
				}
			} else {
				/* No Program */
				/* Sequence is not data to execute run program */
				UTILITY.LOAD_CTL = Switch_OFF;
				Prog_Seq_Data.SEQ_Stop_Continue = Display_None;
			}


			M_num = P_FSeq_EXECUTE;
			MenuRedrawFlag |= MENU_CHANGE;
			DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
			ChanRedrawFlag |= BG_CLEAR;

		} else {
			/* Flag of Run Program was turn on */
			/* Setting Load Key Flag */
			/* Need to control Load Key LED light */
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Soft_Start;
			SendTXData(&tx_data);

			tx_data.ADDRH = Para_Ext_Command;
			tx_data.ADDRL = Para_Ext_Setting;
			SendTXData(&tx_data);

			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Load_OnOff;
			SendTXData(&tx_data);
		}
		SysRedrawFlag |= PROG_UPDATA;
		PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
	}
}

int CalMode=0;
int IsCalMode(void) {
	return CalMode;
}
void HintDelay(char *str) {

}

void ShowHintDelay(char *str) {

}
void RunProgOff(void) {
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	p3k_send_tx_list tx_data;
	char SYNC_TMEM_temp;
	static unsigned char dis_count=0;


	if(((OCP_Alarm==p3k_Measure_Data.Alarm)&&(Set_Limit==Data_tmp->PROT.OCP_SET)) || ((OPP_Alarm==p3k_Measure_Data.Alarm)&&(Set_Limit==Data_tmp->PROT.OPP_SET))|| (UnReg_Alarm==p3k_Measure_Data.Alarm))
		return;
	if(CPP_Alarm==p3k_Measure_Data.Alarm)return;
	if(Para_Alarm==p3k_Measure_Data.Alarm)return;
	///if(ROCP_Alarm == p3k_Measure_Data.Alarm)return;

	Show_Alarm_Message();
	Frame_Change();

	UTILITY.LOAD_CTL = Switch_OFF;
	Soft_Key_Temp = 0;
	UTILITY.SHORT_CTL = Switch_OFF;
	PEL3000_LED_Control(LED_SHORT, UTILITY.SHORT_CTL);
	FunctionFlag   = FUNC_CLEAR;
	if(Prog_Load==P3k_Chan_Data.Load_Type) {		/* Flag of Run Program was turn on */
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
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Load_OnOff;
			SendTXData(&tx_data);
		}
	}
	PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
	SysRedrawFlag |= PROG_UPDATA;
	if((Ext_UnReg_Flag)&&(P3k_Disp_Data.CONF.Ext_Setting.LoadOn_IN)) {
		P3k_Chan_Data.CONF.Ext_Setting.LoadOn_IN = 0;
		P3k_Disp_Data.CONF.Ext_Setting.LoadOn_IN = 0;
	}
}

void ClearKeyBoard(void) {
	char i;
	for(i=0 ; i<6 ; i++) {
		if(OSSemAccept(KeyCodeReadySemPtr))
			OSSemPost(KeyCodeDoneSemPtr);
		OSTimeDly(2);
	}
}
void Update_Panel(void) {
	if(DMA_Update_Flag) {
		DMA_Update_Flag = 0;
	} else {
		return;
	}

#if	Enable_DMA_Display
	if(CtrlFlag1&Float_Windows_DispOn) {
		InitMDMA_Copy((UWORD *)&Display_Buffer[120*1024],(UWORD *)(0x2035E000),(80*1024)/2);
		MDMA_Copy(    (UWORD *)&Display_Buffer[120*1024],(UWORD *)(0x2035E000));
		CtrlFlag1 &= ~Float_Windows_DispOn;
		CtrlFlag1 &= ~Float_Windows_DispOff;
		FloatWindowsDispOn();
	} else {
		InitMDMA_Copy((UWORD *)Display_Buffer,(UWORD *)(0x20340000),(120*1024)/2);
		MDMA_Copy(    (UWORD *)Display_Buffer,(UWORD *)(0x20340000));
	}

	if(CtrlFlag1&Float_Windows_DispOff) {
		CtrlFlag1 &= ~Float_Windows_DispOff;
		FloatWindowsDispOff();
	}
#else
	if(CtrlFlag1 & Float_Windows_DispOn) {
		CtrlFlag1 &= ~Float_Windows_DispOn;
		CtrlFlag1 &= ~Float_Windows_DispOff;
		FloatWindowsDispOn();
	}

	if(CtrlFlag1&Float_Windows_DispOff) {
		CtrlFlag1 &= ~Float_Windows_DispOff;
		FloatWindowsDispOff();
	}
#endif
}



