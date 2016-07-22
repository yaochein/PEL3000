
#include "includes.h"
#include "keydef.h"
#include "../FPGA/SendTXSub.h"
#include "Math.h"
/*********************************************************************
Global  Function
*********************************************************************/
void DigitalProcess(UBYTE key, BYTE cnt);
void VarKnobProcess(BYTE cnt);
void VarKnobEnterProcess(BYTE cnt);
WORD Cnt_Select(BYTE cnt, WORD number, WORD max_num);
WORD Cnt_Select2(BYTE cnt, WORD number, WORD max_num, WORD min_num);
LONG Cnt_Select_Timer(WORD cnt, LONG number, ULONG max_num, LONG min_num);
ULONG Cnt_Select_Step(WORD cnt, LONG number, ULONG max_num, LONG min_num);
ULONG Cnt_Select_Slow(WORD cnt, ULONG number, ULONG max_num, ULONG min_num);
void ScrollCnt_Select(char no,char max, char *start, char *end, char line);
void RestoreRealChan(void);
void KeyinBufProcess(UBYTE key);
void ClearKeyProcess(BYTE cnt);
WORD Scr_Cnt_Select(BYTE cnt, WORD number, WORD max_num, WORD min_num);
void GNGPcet2Step(char no);
void GNGStep2Pcet(char no);
char GetNowRange(void);
long GetChanData(BYTE cnt, BYTE cnt1);
void SaveChanData(BYTE cnt,long dat);
unsigned short get_DynaFreqDutyRangeLimit (unsigned char CurrMode);
long InputToStep(double input,double resolution);
#if Enable_Battery_Discharge
void get_sr_paramter(char cnt_STEP, UBYTE* Range , UWORD* value, UWORD max,UWORD min);
void handle_sr_enter (long* cnt1,long SR_Max, UBYTE* Range_Point, UWORD* value, UWORD max,UWORD min);
#endif


/*********************************************************************
Ext Function
*********************************************************************/
extern void SendTXData(p3k_send_tx_list *data);
extern void KeySelFunc(BYTE cnt);
extern void Control_LCDBRCon(void);
extern void EDGIO_Control(char mode, char onoff);
extern void ClrDispCnt(char mode, char ct, char sec, char ssc, char bct, char scl);
extern void VarSelect(BYTE cnt);
extern BYTE FMselect(BYTE n1, BYTE n2);
extern void EnterChrFunc(void);
extern int NextFileName(int FileCount, char *FileName, char Mode, char cnt);
extern void RecallFileNameFun(const char *name, char *FileName, char Mode, char cnt);
extern void BuzzerFunction(UBYTE Buzzer_Mode,WORD ith);
extern void SetRTC(UWORD);
extern BYTE Password_Process(BYTE chnum,BYTE x);
extern unsigned long sport0Read(unsigned long data);
extern void PEL3000_LED_Control( char mode, char onoff);
extern void sport0Write(unsigned long data);
extern void Debug_printf(char *Message);
extern void ShowCalMessage(void);
extern void Auto_Load_Off(void);
extern float Get_Parallel_Parameter(unsigned char IRange);
extern int FileNameConvert(int Name_Count, char *Name_str, char Mode);
extern BYTE Normal_IRange(BYTE chnum,BYTE x);
extern void Menu_Message(char *Message,int x,int y);
extern void Update_Panel(void);
void set_func_fled_ad (void);

extern const type_default P3070E;
extern const type_default P1033E;
extern const type_default P1031E;
extern const type_default P3111E;
extern GELMASTER *gel;
extern char FMnowPath[maxdirlen];
extern char USB_Status_Display;
extern unsigned short New_Set_Count_To_FPGA;
extern void Show_Seq_fix(void);
extern unsigned char debugmode;
extern unsigned char last_menu;
#if Enable_Ring_Count
extern UWORD UVP_Tone_Count;
extern UWORD SEQ_Tone_Count;
#endif


void ClearKeyProcess(BYTE cnt)
{
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	if( KeyInFlag & SHIFT_KEY ) {
		KeyInFlag &= ~SHIFT_KEY;
		PEL3000_LED_Control(LED_SHIFT, Switch_OFF);
		/* Key Lock Function */
		UTILITY.LOCK_KEY++;
		UTILITY.LOCK_KEY&=0x1;
		SysRedrawFlag |= LOCK_UPDATA;
		if( (DispMode==DispMode_SET_PARAMETERS)&&(M_num<=P_CP) ) {
			DispMode = DispMode_BROWSE_ITEMS;
			DataRedrawFlag|= PARA_CHANGE;
		}
	} else if( KeyInFlag & DIGI_KEY_IN ) {
		/* Clear KeyinBuf data & KeyinCT */
		KeyInFlag &= (~DIGI_KEY_IN);
		KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
		DataRedrawFlag|=PARA_CHANGE;
		if((DispMode == DispMode_SET_PARAMETERS)&&(Disp_tmp->CONF.Ext_Setting.Control)&&(M_num==P_CV))
			DataRedrawFlag |= BG_CLEAR_FLAG;
	}
}
extern void Save2Mem(char mode, UWORD no);
extern UBYTE Recall2Mem(char mode, UWORD no);
extern void Recall2Display(void);
extern unsigned char Delay_Read_Key;
void DigitalProcess(UBYTE key, BYTE cnt)
{
	p3k_send_tx_list tx_data;
	UBYTE keybuf;
	static char FirstLongPush=0;
	char status=0xff,mem,i;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	static unsigned char cnt1=0;

	if(cnt1<100)cnt1++;

	if( (KeyInFlag&SHIFT_KEY)&&(key==K_Digital_Dot) ) {
		/* Shift Mode *//* Calibration Mode */
		/* Process Dot Key in Shift Mode */
		/* Use Calbration Function */
	} else if( (KeyInFlag&PRESET_KEY)&&(key<10) ) {
		/* Preset Memory Mode */
		/* Recall from Preset Memory 0 ~ 9 to Current Display */
		/* Save Data of Current Display to Preset Memory 0 ~ 9 */
		/* Send command to Slave ( Recall Preset Memory ) */

		if(1){
			cnt1 = 0;
		HelpRedrawFlag &= ~HELP_FUN_ON;
			if(KeyInFlag&LP_ON) {
				
				KeyInFlag &= ~LP_ON;
				p3k_File_Utility_BAR.PRE_MEMORY_ADDR = key;

				if( (M_num==P_FILE_CHAN)&&(F_Media_Memory==p3k_File_Utility_BAR.MEDIA) ) {
					Freeze_Keyboard=1;
					DataRedrawFlag |= PARA_CHANGE;
					DispMode =DispMode_SELECT_CH;
				}

				if( KeyInFlag & SHIFT_KEY ) {
					//KeyInFlag &= ~SHIFT_KEY;
					if( LongPush_CT == LONG_PUSH_TIME ) {	/* Save by all channel */
						if(Data_tmp->CONF.Ext_Setting.Control)
							return;
						OSTimeDly(2);
						Save2Mem( SR_PRESET_MODE, key);
						tx_data.ADDRH = 0x20;
						tx_data.ADDRL = key << 4;
						SendTXData(&tx_data);
#if Normal_TEST
						printf("Save Preset %d All OK!\n",key);
#endif
						if(((p3k_Measure_Data.Alarm==0)||(!UTILITY.Master_Alarm_Tone))&&((!p3k_Measure_Data.Go_NoGo)||(!UTILITY.Master_NG_Tone)))
							CtrlFlag1 |= BEEP_ACT;
					} else {
						/* Recall by all channel */
						/* Recall preset XX for all channel */
						/* Recall preset XX to display buffer */
						System_Ready=0;/*Avoid Master and Slave Data Asynchronous*/
						if(Data_tmp->CONF.Ext_Setting.Control) {
							System_Ready = 1;
							return;
						}
						OSTimeDly(2);
						if(Recall2Mem( SR_PRESET_MODE, key)==0) {
							System_Ready = 1;
							return;
						}
						Recall2Display();
						ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
						MenuRedrawFlag |= MENU_CHANGE;
						DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
						ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
						tx_data.ADDRH = 0x30;
						tx_data.ADDRL = key + 0xA0;
						SendTXData(&tx_data);
						System_Ready=1;
#if Normal_TEST
						printf("Recall Preset %d All OK!\n",key);
#endif
					}
				} else {
					if( LongPush_CT == LONG_PUSH_TIME ) {
						/* Save */
						
						Save2Mem( SR_PRESET_MODE, key);
						tx_data.ADDRH = 0x20;
						tx_data.ADDRL = key << 4;
#if Normal_TEST
						printf("Save Preset %d OK!\n", key);
#endif
						if(((p3k_Measure_Data.Alarm==0)||(!UTILITY.Master_Alarm_Tone))&&((!p3k_Measure_Data.Go_NoGo)||(!UTILITY.Master_NG_Tone)))
							CtrlFlag1 |= BEEP_ACT;	
						SendTXData(&tx_data);
					} else {
						//Delay_Read_Key =0;
						/* Recall */
						//OSTimeDly(2);
						if(Recall2Mem( SR_PRESET_MODE, key)==0)
							return;
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
						tx_data.ADDRL = key << 4;
						ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
						MenuRedrawFlag |= MENU_CHANGE;
						DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
						ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
						
						SendTXData(&tx_data);

						
						//OSTimeDly(100);
#if Normal_TEST
						printf("Recall Preset %d OK!\n", key);
#endif
					}
					//OSTimeDly(10);///
					
					//OSTimeDly(5);///
				}
				
			} else {
				KeyInFlag |= LP_ON;
				KeyInFlag |= LONG_PUSH;
				KeyInFlag &= (~LONG_PUSH_DONE);
				v_keycode = key+0x60;
				v_keycnt = cnt;
				LongPush_CT =0x0;
			}
		}	
	} else {
		if( M_num>=P_CC && M_num<=P_CV && DispMode==DispMode_SELECT_CH) {
			/* When select channel number */
		} else {
			KeyinBufProcess(key);
		}
	}
}
const int KeyinNum[KEYINNUM_MAX][KEYINNUM_WEDTH] = {
	/*	   0    1   2   3   4    5   6    7   8   9    A   B   C   D   E   F		*/
	{ 5, 5, 5, 5, 4, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_CC				0x00*/
	{ 6, 6, 5, 5, 4, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_CR				0x01*/
	{ 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_CV				0x02*/
	{ 5, 5, 5, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_CP 				0x03*/
	{ 0, 2, 0, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_CC_SPEC 		0x04*/
	{ 0, 2, 0, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_CR_SPEC 		0x05*/
	{ 0, 2, 0, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_CV_SPEC 		0x06*/
	{ 0, 2, 0, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_CP_SPEC 		0x07*/
#if Enable_Ring_Count
	{ 6, 0, 5, 0, 4, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_CONF_PROT		0x08*/
#else
	{ 6, 0, 5, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_CONF_PROT		0x08*/
#endif
	{ 4, 5, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_CONF_OTHER 	0x09*/
	{ 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_CONF_Para		0x0A*/
	{ 0, 5, 6, 6, 6, 6, 4, 4, 4, 4, 5, 5, 0, 0, 0, 0 },	/* P_CONF_KNOB 		0x0B*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_CONF_Ext 		0x0C*/
#if Enable_Menu_optim
	{ 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_MAIN		0x0D*/
#else
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_MAIN		0x0D*/
#endif
	{ 1, 1, 2, 0, 3, 3, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_PROG_MAIN		0x0E*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_PROG_CHAIN		0x0F*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_PROG_EXECUTE	0x10*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_PROG_Detail		0x11*/
#if Enable_Ring_Count
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_Seq_FUNC		0x12*/
#else
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_Seq_FUNC		0x12*/
#endif
	{ 0, 0, 0, 0, 0, 3, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_Seq_Normal 		0x13*/
	{ 0, 0, 0, 3, 5, 0, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_Seq_Fast 		0x14*/
#if Enable_NSEQ_Usec
	{ 3, 5, 2, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_NSeq_Edit		0x15*/
#else
	{ 3, 5, 2, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_NSeq_Edit		0x15*/
#endif
	{ 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FSeq_Edit		0x16*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_NSeq_EXECUTE	0x17*/
	{ 5, 5, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FSeq_Fill			0x18*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FSeq_EXECUTE	0x19*/

	{ 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_FILE_CHAN		0x1A*/
	{ 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_FILE_MACHINE	0x1B*/

	{ 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_CAL_MODE		0x1C*/

	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_UTIL_MAIN		0x1D*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_UTIL_INTERFACE	0x1E*/
	{ 1, 1, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_UTIL_T_DATE		0x1F*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_UTIL_LOAD		0x20*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_UTIL_OTHER		0x21*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_UTIL_SYSINFO	0x22*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_UTIL_SYSMEMO	0x23*/

	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_UTIL_KEYPAD		0x24*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_UTIL_FILE		0x25*/

	{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_Input_Password	0x26*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_Input_Serial		0x27*/

	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_HELP_HELP		0x28*/

	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_LUA_EXECUTE	0x29*/

	{ 0, 2, 4, 2, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* P_Test_Func		0x2A*/

	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_POWER	0x2B*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_Cal_Value		0x2C*/
#if Enable_OCP_function
	{ 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_MAIN_2		0x2D*/
	{ 1, 0, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_OCP		0x2E*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_OCP_EXECUTE	0x2F*/
		
#endif	
#if Enable_Battery_Discharge	
	{ 1, 0, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_OPP		0x30*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_OPP_EXECUTE	0x31*/

	{ 0, 0, 5, 5, 5, 5, 2, 5, 0, 0, 0, 0, 0, 0, 0, 0 }, /* Func_bett			0x32*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* Func_bett_execute	0x33*/
	{ 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_FLED		0x34*/
	{ 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_LED_edit	0x35*/
#endif
#if Enable_LED_function
	{ 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_LED_exe	0x36*/
	{ 0, 0, 0, 3, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_LED2		0x37*/
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_LED_edit2	0x38*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_LED_exe2	0x39*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_LED2		0x3A*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_LED2		0x3B*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_LED2		0x3C*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_LED2		0x3D*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_LED2		0x3E*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_LED2		0x3F*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_LED2		0x40*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_LED2		0x41*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_LED2		0x42*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_LED2		0x43*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_LED2		0x44*/
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* P_FUNC_LED2		0x45*/
#endif

};

void KeyinBufProcess(UBYTE key)
{
	UBYTE keybuf;
	int cnt_max;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	if( (P_CAL_MODE==M_num)&&(DispMode_SELECT_CH==DispMode) )
		return;

	if(M_num==P_CONF_OTHER || M_num==P_CONF_PROT || M_num==P_CONF_KNOB) {
		cnt_max = KeyinNum[M_num][DispScrCurrLoc];
		if((M_num==P_CONF_OTHER)&&(DispScrCurrLoc==P_CUTOFFTIME)) {
			if(P3k_Chan_Data.CONF.Cut_Off_cnt==0)
				cnt_max =2;
			else if(P3k_Chan_Data.CONF.Cut_Off_cnt==1)
				cnt_max =1;
			else if(P3k_Chan_Data.CONF.Cut_Off_cnt==2)
				cnt_max =1;
		}
	} else
		cnt_max = KeyinNum[M_num][DispCT];	/* Get Key In total Number */
#if 0
	if( (M_num==P_CAL_MODE)&&((P3K_CALIBRATION_BAR.MODE==F_IMON_MODE)||(P3K_CALIBRATION_BAR.MODE==R_IMON_MODE)) )
		cnt_max = 1;
#endif
	if(cnt_max!=0x00) {
		if( (M_num==P_FILE_CHAN)&&(F_Media_USB==p3k_File_Utility_BAR.MEDIA) )
			return;
		DispMode = DispMode_BROWSE_ITEMS;


		switch(M_num){
			case P_CC ... P_CONF_OTHER:
			case P_Test_Func:
			case P_CONF_KNOB:
			case P_CONF_Para:
#if Enable_Battery_Discharge
			case P_FUNC_batt:
#endif
#if Enable_LED_function
   			case P_FUNC_FLED ... P_FUNC_CLED_EDIT:
#endif				
				DispMode=DispMode_SET_PARAMETERS;
				break;
			default:
				break;
		}


		KeyInFlag |= DIGI_KEY_IN;			/* To check keyin */
		DataRedrawFlag |= PARA_CHANGE;		/* Parameter updata */
		if((DispMode == DispMode_SET_PARAMETERS)&&(Disp_tmp->CONF.Ext_Setting.Control)&&(M_num==P_CV))
			DataRedrawFlag |= BG_CLEAR_FLAG;

		if(K_Digital_Dot==key)
			keybuf = '.';
		else
			keybuf = '0' + key;

		if( KeyinCT <= cnt_max ) {
			KeyinBuf[KeyinCT] = keybuf;
			KeyinCT++;
		}
	}
}

void Dyna_Timer_Freq_Setting(long *data, UWORD max, UWORD min)
{
	UBYTE *t_range,*F_Range;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	if(Disp_tmp->CONF.Dyna_Time) {
		switch(M_num) {
		case P_CC:
			if((DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CC.STADYNA))
				F_Range = &Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency_Range;
			break;
		case P_CR:
			if((DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CR.STADYNA))
				F_Range = &Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency_Range;
			break;
		default:
			break;
		}

		if(((M_num == P_CC)||(M_num == P_CR)) && (DispScrCurrLoc == CCCR_Dyn_T1)) {	/*	Frequency */
			if(*F_Range == Dyn_Freq_TimeBase_100Hz) {
				if(*data == min) {
					*F_Range = Dyn_Freq_TimeBase_10Hz;
					*data = 99;
				}
			} else if(*F_Range == Dyn_Freq_TimeBase_10Hz) {
				if(*data == min) {
					*F_Range = Dyn_Freq_TimeBase_1Hz;
					*data = 99;
				} else if(*data == max) {
					*F_Range = Dyn_Freq_TimeBase_100Hz;
					*data = *data / 10;
				}
			} else if(*F_Range == Dyn_Freq_TimeBase_1Hz) {
				if(*data == min) {
					*F_Range = Dyn_Freq_TimeBase_100mHz;
					*data = 99;
				} else if(*data == max) {
					*F_Range = Dyn_Freq_TimeBase_10Hz;
					*data = *data / 10;
				}
			} else if(*F_Range == Dyn_Freq_TimeBase_100mHz) {
				if(*data == max) {
					*F_Range = Dyn_Freq_TimeBase_1Hz;
					*data = *data / 10;
				}
			}
		}
	} else {
		switch(M_num) {
		case P_CC:
			if((DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CC.STADYNA))
				t_range = &Disp_tmp->CC.DYNA[Disp_tmp->IRange].T1_RANGE;			/* Get Time 1 range is 1 or 2 */
			else if((DispScrCurrLoc == CCCR_Dyn_T2) && (Disp_tmp->CC.STADYNA))
				t_range = &Disp_tmp->CC.DYNA[Disp_tmp->IRange].T2_RANGE;			/* Get Time 2 range is 1 or 2 */
			break;
		case P_CR:
			if((DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CR.STADYNA))
				t_range = &Disp_tmp->CR.DYNA[Disp_tmp->IRange].T1_RANGE;			/* Get Time 1 range is 1 or 2 */
			else if((DispScrCurrLoc == CCCR_Dyn_T2) && (Disp_tmp->CR.STADYNA))
				t_range = &Disp_tmp->CR.DYNA[Disp_tmp->IRange].T2_RANGE;			/* Get Time 2 range is 1 or 2 */
			break;

		default:
			break;
		}
		if((((M_num == P_CC)||(M_num == P_CR)) && ((DispScrCurrLoc == CCCR_Dyn_T1) || (DispScrCurrLoc == CCCR_Dyn_T2)))) {	/* Time 1 & 2 Setting */
			if(*t_range == Dyn_TimeBase_1ms) {
				if(*data == min) {
					*t_range = Dyn_TimeBase_1us;
					*data = 29999;

				}
			} else {
				if(*data == max) {
					*t_range = Dyn_TimeBase_1ms;
					*data = (*data / 1000);
				}
			}
		}
	}
}

void find_curve_led_paramter(UWORD data){
#if Enable_LED_function	
	const double RdStr[8]={0.000045,0.000045,0.006995,0.040933,0.107437,0.203406,0.324508,0.466977};
	char i;
	F_LED_Str *Disp_tmp = &P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp];
	UBYTE vRange = Disp_tmp->range / 2;
	UBYTE iRange = Disp_tmp->range % 2;
	float Vo = Disp_tmp->vo *(ptrMODEL_TYPE->CV)[vRange*3].Resolution;	
	double Io = Disp_tmp->io*(ptrMODEL_TYPE->CC)[iRange*10].Resolution;
	double Ir,Rdcoeff;
	double objRocoff = data*0.0001;
	double C;
	double x = RdStr[data/1000];
	double detaX = x;
	
	for(i=0;i<16;i++){
		detaX = detaX/2;
		Rdcoeff = (x-1)/log(x);
		if(objRocoff<Rdcoeff){
			x=x-detaX;
		}else{ 
			x= x+detaX;	
		}		
	}
	Ir = Io*x/(1-x);
	C = log(Io/Ir+1)/Vo;

	Disp_tmp->ir = Ir;
	Disp_tmp->c = C;	
	//printf("I:%1.2f,C:%1.2f\n",Ir,C);
#endif	
}

void recall_default_parameter(char mDispCT){
	UWORD data,data1,max,min;
	UBYTE temp;
	switch(M_num){
		case P_Seq_Normal:
		if(CC_MODE==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode) {
			max = (ptrMODEL_TYPE->CC)[0].Max;
			min = (ptrMODEL_TYPE->CC)[0].Min;
		} else if(CR_MODE==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode) {
			max = (ptrMODEL_TYPE->CR)[0].Max;
			min = (ptrMODEL_TYPE->CR)[0].Min;
		} else if(CV_MODE==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode) {
			max = (ptrMODEL_TYPE->CV)[0].Max;
			min = (ptrMODEL_TYPE->CV)[0].Min;
		} else { /*CP MODE*/
			max = (ptrMODEL_TYPE->CP)[0].Max;
			min = (ptrMODEL_TYPE->CP)[0].Min;
		}
		data = GetChanData(P_NSeq_Last_Set,0);
		if(data>max)			data = max;
		else if(data<min)	data = min;
		SaveChanData(P_NSeq_Last_Set, data);		
		break;
	case P_Seq_Fast:
		if(CC_MODE==P3k_FSeq_Disp.FSeq_Mode) {
			max = (ptrMODEL_TYPE->CC)[0].Max;
			min = (ptrMODEL_TYPE->CC)[0].Min;
		} else {	/*CR_MODE*/
			max = (ptrMODEL_TYPE->CR)[0].Max;
			min = (ptrMODEL_TYPE->CR)[0].Min;
		}
		data = GetChanData(P_FSeq_Last_Set,0);
		if(data>max)			data = max;
		else if(data<min)	data = min;
		SaveChanData(P_FSeq_Last_Set, data);	
		break;
	case P_FUNC_OCP:
		SaveChanData(2, 1);
		SaveChanData(3, 1000);
		SaveChanData(4, 1);
		SaveChanData(7, 250);
		SaveChanData(8, 0);
		break;
	case P_FUNC_OPP:
		SaveChanData(2, 0);
		SaveChanData(3, 1);
		SaveChanData(4, 1);
		SaveChanData(8, 0);
		break;
	case P_FUNC_batt:
		BattDisp.StopValt = 20;
		BattDisp.SRUPRange = BattDisp.SRDWRange = 0;
		BattDisp.SRUP = BattDisp.SRDW = 250;		
		break;
	case P_FUNC_FLED:
		temp = P3k_FLed_Disp.currTemp;
		P3k_FLed_Disp.seq[temp].vo = (ptrMODEL_TYPE->CV)[0].Max/102*40;
		P3k_FLed_Disp.seq[temp].vf = (ptrMODEL_TYPE->CV)[0].Max/102*20;
		P3k_FLed_Disp.seq[temp].io = (ptrMODEL_TYPE->CC)[0].Max/10.2;
		P3k_FLed_Disp.seq[temp].rd = 500;
		P3k_FLed_Disp.seq[temp].rdcoff = 3000;		
		P3k_FLed_Disp.seq[temp].pcs = 1;
		break;
	case P_FUNC_CLED:
		temp = P3k_CLed_Disp.currTemp;
		P3k_CLed_Disp.seq[temp].vo= (ptrMODEL_TYPE->CV)[0].Max/102*30;
		P3k_CLed_Disp.seq[temp].io= (ptrMODEL_TYPE->CC)[0].Max/10.2;
		P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].rdcoff = 3000;	
		find_curve_led_paramter(P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].rdcoff);				
		break;
	default:
		break;


	}





}


void VarKnobProcess(BYTE cnt)
{
	BYTE KeyAccTable[33]= {	-18, -17, -15, -15, -11, -11, -10, -10, -6, -6, -5, -5, -2, -2, -1, -1,
	                        0,   1,   1,   2,   2,   5,   5,   6,  6,  10, 10, 11, 11, 15, 15, 17,
	                        18
	                      };

	int i;
	double fcnt;
	char type,range,SYNC_TMEM_temp,FileName_Temp[30],val;
	char DispCT_temp,Sta_Dyna,Total_Disp_Item;
	long data,cnt_STEP,tmp,min;
	UWORD data1,max,h_old,l_old,umax,umin,h_new,l_new;
	UWORD LEVEL1,LEVEL2;
	ULONG Seq_Data,Seq_max,Seq_min;
	ULONG SEQ_MAX,SEQ_MIN;
	LONG max_value;
	UBYTE V_Range,*sr_range,*t_range,*F_Range,temp;
	unsigned char _flagCursorScale = 0;
	p3k_send_tx_list tx_data;
	double CursorValue;


	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Prog_Str	*Prog_tmp = &p3k_Disp_PROG;

	V_Range = Disp_tmp->VRange;

	switch(M_num) {
	case P_CC:
		Sta_Dyna = Disp_tmp->CC.STADYNA;
		if(Sta_Dyna)
			Total_Disp_Item = (4 + (Disp_tmp->CC.STADYNA)*2)+1;
		else
			Total_Disp_Item = (4 + (Disp_tmp->CC.STADYNA)*2)-1+1;

		if(DispMode == DispMode_BROWSE_ITEMS) {
			B_DispCT = DispScrCurrLoc;
			DispScrCurrLoc = Scr_Cnt_Select(cnt, DispScrCurrLoc, Total_Disp_Item , 0 );
			DispCT = DispScrCurrLoc;
			ScrollCnt_Select(DispScrCurrLoc, Total_Disp_Item+1, &DispScrStartCT, &DispScrEndCT, 2);
			if( (CCCR_Sta_B_VALUE==DispScrCurrLoc)&&(Disp_tmp->UTILITY.B_ONOFF)&&(Function_Static==Disp_tmp->CC.STADYNA) ) {
				/* When B vaue is ON */
				if(cnt > 0)
					DispScrCurrLoc--;
				else if(cnt < 0)
					DispScrCurrLoc++;
			}
			if(DispScrCurrLoc != B_DispCT) {
				DataRedrawFlag|= PARA_CHANGE+PARA_CHANGE_Fast;
				ChanRedrawFlag |= CHAN_STATUS;
			}
		} else if(DispMode == DispMode_SET_PARAMETERS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5]= KeyinCT = 0x00 ;
			data = GetChanData(DispScrCurrLoc,0);
			/* Get Max. Setting & Min. Setting */

			if(DispScrCurrLoc<=CCCR_Dyn_SRDN)
				t_range = &Disp_tmp->IRange;											/* Get CC Mode Range */

			if(DispScrCurrLoc==CCCR_Dyn_SRUP) {
				//if(Disp_tmp->CC.STADYNA)
				//	sr_range = &Disp_tmp->CC.DYNA[Disp_tmp->IRange].SLEWRATEUP_RANGE;
				//else
				//	sr_range = &Disp_tmp->CC.STA[Disp_tmp->IRange].SLEWRATEUP_RANGE;
			} else if(DispScrCurrLoc==CCCR_Dyn_SRDN) {
				//if(Disp_tmp->CC.STADYNA)
				//	sr_range = &Disp_tmp->CC.DYNA[Disp_tmp->IRange].SLEWRATEDN_RANGE;
				//else
				//	sr_range = &Disp_tmp->CC.STA[Disp_tmp->IRange].SLEWRATEDN_RANGE;
			}

			if(((DispScrCurrLoc == CCCR_Dyn_L2) && (Disp_tmp->CONF.Dyna_Level) && (Disp_tmp->CC.STADYNA==Function_Dynamic)) || ((DispScrCurrLoc == CCCR_Dyn_T2) && (Disp_tmp->CONF.Dyna_Time) && (Disp_tmp->CC.STADYNA==Function_Dynamic))) {
				if(DispScrCurrLoc == CCCR_Dyn_T2) {
					min = get_DynaFreqDutyRangeLimit(P_CC);
					max = 1000 - min;
				} else {
					max = 1000;
					min = 0;
				}

			} else if((((DispScrCurrLoc == CCCR_Dyn_SRUP) || (DispScrCurrLoc == CCCR_Dyn_SRDN)) && (Disp_tmp->CC.STADYNA==Function_Dynamic)) || ((DispScrCurrLoc == CCCR_Sta_SR) && (Disp_tmp->CC.STADYNA==Function_Static))) {
				max = (ptrMODEL_TYPE->CC)[DispScrCurrLoc+(*t_range)*10+(Disp_tmp->CC.STADYNA)*4].Max;
				min = (ptrMODEL_TYPE->CC)[DispScrCurrLoc+(*t_range)*10+(Disp_tmp->CC.STADYNA)*4].Min;

			} else if(((DispScrCurrLoc == CCCR_Dyn_T1) || (DispScrCurrLoc == CCCR_Dyn_T2)) && (Disp_tmp->CC.STADYNA==Function_Dynamic) && (!Disp_tmp->CONF.Dyna_Time)) {
				if((Disp_tmp->CC.DYNA[Disp_tmp->IRange].T1_RANGE == Dyn_TimeBase_1ms && (DispScrCurrLoc == CCCR_Dyn_T1)) || (Disp_tmp->CC.DYNA[Disp_tmp->IRange].T2_RANGE == Dyn_TimeBase_1ms && (DispScrCurrLoc == CCCR_Dyn_T2))) {
					max = DyMax;
					min = 29;
				} else {
					max = DyMax/2;
					min = 50;
				}

			} else if((DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CONF.Dyna_Time) && (Disp_tmp->CC.STADYNA==Function_Dynamic)) {
				if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_100Hz)
					max = 200;
				else
					max = 100;
				min = 10;
				_flagCursorScale =1;
			} else if(((DispScrCurrLoc==CCCR_Dyn_Add_CV)&&(Disp_tmp->CC.STADYNA==Function_Dynamic))||((DispScrCurrLoc==CCCR_Sta_Add_CV)&&(Disp_tmp->CC.STADYNA==Function_Static))) {
				max = (ptrMODEL_TYPE->CV)[V_Range*3].Max;
				min = (ptrMODEL_TYPE->CV)[V_Range*3].Min -1 ;
			} else if(((DispScrCurrLoc==CCCR_Dyn_CV_Response)&&(Disp_tmp->CC.STADYNA==Function_Dynamic))||((DispScrCurrLoc==CCCR_Sta_CV_Response)&&(Disp_tmp->CC.STADYNA==Function_Static))) {
				max = 1;
				min = 0;
			} else {
				max = (ptrMODEL_TYPE->CC)[DispScrCurrLoc+(*t_range)*10+(Disp_tmp->CC.STADYNA)*4].Max;
				min = (ptrMODEL_TYPE->CC)[DispScrCurrLoc+(*t_range)*10+(Disp_tmp->CC.STADYNA)*4].Min;
			}

			if(Disp_tmp->CONF.Knob_Status) {
				cnt_STEP = cnt;
				CursorValue = powf(10.0,Magnification_Cnt-CursorPrecision);
				cnt_STEP *= InputToStep((_CursorResolution/2+CursorValue),_CursorResolution);
				if(cnt_STEP==0)cnt_STEP=cnt;
				if(cnt_STEP>(65534/2))cnt_STEP = 32764;
				else if(cnt_STEP<(-65534/2))cnt_STEP = -32764;
			} else if((DispScrCurrLoc <= CCCR_Sta_B_VALUE)&&((Data_tmp->Coarse)&&((!Disp_tmp->CONF.Dyna_Level)||(!Disp_tmp->CC.STADYNA)||((Disp_tmp->CC.STADYNA)&&(DispScrCurrLoc==0)))))
				cnt_STEP = cnt * Disp_tmp->CC.VALUE_STEP[Disp_tmp->IRange];
			else
				cnt_STEP = cnt;
			if(((DispScrCurrLoc==CCCR_Dyn_SRUP||DispScrCurrLoc==CCCR_Dyn_SRDN)&&(Disp_tmp->CC.STADYNA==Function_Dynamic))||(DispScrCurrLoc==CCCR_Sta_SR && Disp_tmp->CC.STADYNA==Function_Static) ) {
				max_value = max /Get_Parallel_Parameter(Disp_tmp->IRange);
				data = Cnt_Select_Step(cnt_STEP, data, max_value, min);

			} else {
				data = Cnt_Select_Step(cnt_STEP, data, max, min);
			}

			if(Disp_tmp->CC.STADYNA == Function_Dynamic)
				Dyna_Timer_Freq_Setting(&data,max,min);

			SaveChanData(DispScrCurrLoc,data);


			if(UTILITY.KEYKNOB) {
				if(((DispScrCurrLoc==CCCR_Dyn_Add_CV)&&(Disp_tmp->CC.STADYNA==Function_Dynamic))||((DispScrCurrLoc==CCCR_Sta_Add_CV)&&(Disp_tmp->CC.STADYNA==Function_Static)))
					Data_tmp->CV.STA[Data_tmp->VRange].VALUE1 = Disp_tmp->CV.STA[Data_tmp->VRange].VALUE1;
				else
					Data_tmp->CC = Disp_tmp->CC;
				MenuDecoderAddr(&tx_data);
				SendTXData(&tx_data);
			}

			DataRedrawFlag |=PARA_CHANGE;
#if 1
			if((DispScrCurrLoc<=CCCR_Sta_B_VALUE)&&(!Disp_tmp->CC.STADYNA)&&(!Disp_tmp->UTILITY.B_ONOFF)) {
				if(UTILITY.KEYKNOB) {
					tx_data.ADDRH = 0x01;
					tx_data.ADDRL = 0x00;
					SendTXData(&tx_data);
				}
			}
#endif
		}
		break;
	case P_CR:
		Sta_Dyna = Disp_tmp->CR.STADYNA;
		if(Sta_Dyna)
			Total_Disp_Item = (4 + (Disp_tmp->CR.STADYNA)*2)+1;
		else
			Total_Disp_Item = (4 + (Disp_tmp->CR.STADYNA)*2)-1+1;

		if(DispMode == DispMode_BROWSE_ITEMS) {
			B_DispCT = DispScrCurrLoc;
			DispScrCurrLoc = Scr_Cnt_Select(cnt, DispScrCurrLoc, Total_Disp_Item , 0 );
			DispCT=DispScrCurrLoc;
			ScrollCnt_Select(DispScrCurrLoc, Total_Disp_Item+1, &DispScrStartCT, &DispScrEndCT, 2);
			if(DispScrCurrLoc==CCCR_Sta_B_VALUE&& Disp_tmp->UTILITY.B_ONOFF && Disp_tmp->CR.STADYNA==Function_Static) {
				/* When B vaue is ON */
				if(cnt>0)
					DispScrCurrLoc--;
				else if(cnt<0)
					DispScrCurrLoc++;
			}
			if(DispScrCurrLoc != B_DispCT) {
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
				ChanRedrawFlag |= CHAN_STATUS;
			}
		} else if(DispMode == DispMode_SET_PARAMETERS) {
			Compensation_Flag = 0;
			Compensation_Count = 0;
			Error_Amount_Flag = 0;

			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;

			data = GetChanData(DispScrCurrLoc,0);
			/* Get Max. Setting & Min. Setting */

			if(DispScrCurrLoc<=CCCR_Dyn_SRDN)
				t_range = &Disp_tmp->IRange;								/* Get CC Mode Range */

			if(((DispScrCurrLoc == CCCR_Dyn_L2) && (Disp_tmp->CONF.Dyna_Level) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) || ((DispScrCurrLoc == CCCR_Dyn_T2) && (Disp_tmp->CONF.Dyna_Time) && (Disp_tmp->CR.STADYNA==Function_Dynamic))) {
				if(DispScrCurrLoc == CCCR_Dyn_T2) {
					min = get_DynaFreqDutyRangeLimit(P_CR);
					max = 1000 - min;
				} else {
					max = 1000;
					min = 0;
				}
			} else if((((DispScrCurrLoc == CCCR_Dyn_SRUP) || (DispScrCurrLoc == CCCR_Dyn_SRDN)) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) || ((DispScrCurrLoc == CCCR_Sta_SR) && (Disp_tmp->CR.STADYNA==Function_Static))) {
				max = (ptrMODEL_TYPE->CR)[DispScrCurrLoc+(*t_range)*10+(Disp_tmp->CR.STADYNA)*4].Max;
				min = (ptrMODEL_TYPE->CR)[DispScrCurrLoc+(*t_range)*10+(Disp_tmp->CR.STADYNA)*4].Min;
			} else if(((DispScrCurrLoc == CCCR_Dyn_T1) || (DispScrCurrLoc == CCCR_Dyn_T2)) && (Disp_tmp->CR.STADYNA==Function_Dynamic) && (!Disp_tmp->CONF.Dyna_Time)) {
				if((Disp_tmp->CR.DYNA[Disp_tmp->IRange].T1_RANGE == Dyn_TimeBase_1ms && (DispScrCurrLoc == CCCR_Dyn_T1)) || (Disp_tmp->CR.DYNA[Disp_tmp->IRange].T2_RANGE == Dyn_TimeBase_1ms && (DispScrCurrLoc == CCCR_Dyn_T2))) {
					max = DyMax;
					min = 29;
				} else {
					max = DyMax/2;
					min = 50;
				}

			} else if((DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CONF.Dyna_Time) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) {
				if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_100Hz)
					max = 200;
				else
					max = 100;
				min = 10;
				_flagCursorScale =1;
			} else if(((DispScrCurrLoc==CCCR_Dyn_Add_CV)&&(Disp_tmp->CR.STADYNA==Function_Dynamic))||((DispScrCurrLoc==CCCR_Sta_Add_CV)&&(Disp_tmp->CR.STADYNA==Function_Static))) {
				max = (ptrMODEL_TYPE->CV)[V_Range*3].Max;
				min = (ptrMODEL_TYPE->CV)[V_Range*3].Min-1;
			} else if(((DispScrCurrLoc==CCCR_Dyn_CV_Response)&&(Disp_tmp->CR.STADYNA==Function_Dynamic))||((DispScrCurrLoc==CCCR_Sta_CV_Response)&&(Disp_tmp->CR.STADYNA==Function_Static))) {
				max = 1;
				min = 0;
			} else {
				max = (ptrMODEL_TYPE->CR)[DispScrCurrLoc+(*t_range)*10+(Disp_tmp->CR.STADYNA)*4].Max;
				min = (ptrMODEL_TYPE->CR)[DispScrCurrLoc+(*t_range)*10+(Disp_tmp->CR.STADYNA)*4].Min;
			}

			if(Disp_tmp->CONF.Knob_Status) {
				cnt_STEP = cnt;
				CursorValue = powf(10.0,Magnification_Cnt-CursorPrecision);
				cnt_STEP *= InputToStep((_CursorResolution/2+CursorValue),_CursorResolution);
				if(cnt_STEP==0)cnt_STEP=cnt;
				if(cnt_STEP>(65534/2))cnt_STEP = 32764;
				else if(cnt_STEP<(-65534/2))cnt_STEP = -32764;
			} else if((DispScrCurrLoc <= CCCR_Sta_B_VALUE)&&((Data_tmp->Coarse)&&((!Disp_tmp->CONF.Dyna_Level)||(!Disp_tmp->CR.STADYNA)||((Disp_tmp->CR.STADYNA)&&(DispScrCurrLoc==0)))))
				cnt_STEP = cnt * Disp_tmp->CR.VALUE_STEP[Disp_tmp->IRange];
			else
				cnt_STEP = cnt;
			if(((DispScrCurrLoc==CCCR_Dyn_SRUP||DispScrCurrLoc==CCCR_Dyn_SRDN)&&(Disp_tmp->CR.STADYNA==Function_Dynamic))||(DispScrCurrLoc==CCCR_Sta_SR && Disp_tmp->CR.STADYNA==Function_Static) ) {
				//cnt_STEP *= Get_Parallel_Parameter(Disp_tmp->IRange);
				max_value = max /Get_Parallel_Parameter(Disp_tmp->IRange);
				data = Cnt_Select_Step(cnt_STEP, data, max_value, min);

			} else
				data = Cnt_Select_Step(cnt_STEP, data, max, min);

			if(Disp_tmp->CR.STADYNA == Function_Dynamic)
				Dyna_Timer_Freq_Setting(&data, max, min);

			SaveChanData(DispScrCurrLoc,data);
			if(UTILITY.KEYKNOB) {
				if(((DispScrCurrLoc==CCCR_Dyn_Add_CV)&&(Disp_tmp->CR.STADYNA==Function_Dynamic))||((DispScrCurrLoc==CCCR_Sta_Add_CV)&&(Disp_tmp->CR.STADYNA==Function_Static)))
					Data_tmp->CV.STA[Data_tmp->VRange].VALUE1 = Disp_tmp->CV.STA[Data_tmp->VRange].VALUE1;
				else
					Data_tmp->CR = Disp_tmp->CR;
				MenuDecoderAddr(&tx_data);
				SendTXData(&tx_data);
			}

			DataRedrawFlag |=PARA_CHANGE;
#if 1
			if((DispScrCurrLoc<=CCCR_Sta_B_VALUE)&&(!Disp_tmp->CR.STADYNA)&&(!Disp_tmp->UTILITY.B_ONOFF)) {
				if(UTILITY.KEYKNOB) {
					tx_data.ADDRH = 0x02;
					tx_data.ADDRL = 0x00;
					SendTXData(&tx_data);
				}
			}
#endif
		}
		break;
	case P_CV:
		if(DispMode == DispMode_BROWSE_ITEMS) {
			B_DispCT = DispCT;
			DispCT = Scr_Cnt_Select(cnt, DispCT, 1, 0);
			if(DispCT==CV_B_VALUE && Disp_tmp->UTILITY.B_ONOFF) {		/* When B vaue is ON */
				if(cnt>0)
					DispCT--;
				else if(cnt<0)
					DispCT++;
			}
			if(B_DispCT != DispCT) {
				DataRedrawFlag|= PARA_CHANGE+PARA_CHANGE_Fast;
				ChanRedrawFlag |= CHAN_STATUS;
			}
		} else if(DispMode == DispMode_SET_PARAMETERS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			data = GetChanData(DispCT,0);
			/* Get Max. Setting & Min. Setting */

			range = Disp_tmp->VRange;
			max = (ptrMODEL_TYPE->CV)[DispCT + range*3].Max;
			min = (ptrMODEL_TYPE->CV)[DispCT + range*3].Min;

			if(Disp_tmp->CONF.Knob_Status) {
				cnt_STEP = cnt;
				CursorValue = powf(10.0,Magnification_Cnt-CursorPrecision);
				cnt_STEP *= InputToStep((_CursorResolution/2+CursorValue),_CursorResolution);
				if(cnt_STEP==0)cnt_STEP=cnt;
				if(cnt_STEP>(65534/2))cnt_STEP = 32764;
				else if(cnt_STEP<(-65534/2))cnt_STEP = -32764;
			} else if((Data_tmp->Coarse)&&(DispScrCurrLoc<=CV_B_VALUE))
				cnt_STEP = cnt * Disp_tmp->CV.VALUE_STEP[Disp_tmp->VRange];
			else
				cnt_STEP = cnt;


			data = Cnt_Select_Step(cnt_STEP, data, max, min);		/* inc */
			SaveChanData(DispCT,data);
			Data_tmp->CV = Disp_tmp->CV;


			if(UTILITY.KEYKNOB) {
				Data_tmp->CV = Disp_tmp->CV;
				MenuDecoderAddr(&tx_data);
				SendTXData(&tx_data);
			}

			DataRedrawFlag |=PARA_CHANGE;

			if((DispMode == DispMode_SET_PARAMETERS)&&(Disp_tmp->CONF.Ext_Setting.Control)&&(M_num==P_CV))
				DataRedrawFlag |= BG_CLEAR_FLAG;
			if((DispCT<=CV_B_VALUE)&&(Disp_tmp->CV.STADYNA==Function_Static)&&(!Disp_tmp->UTILITY.B_ONOFF)) {
				if(UTILITY.KEYKNOB) {
					tx_data.ADDRH = 0x03;
					tx_data.ADDRL = 0x00;
					SendTXData(&tx_data);
				}
			}
		}
		break;
	case P_CP:
		//Sta_Dyna = Disp_tmp->CP.STADYNA;
		Total_Disp_Item = (2 + (Disp_tmp->CP.STADYNA)*2)+1;

		if(DispMode == DispMode_BROWSE_ITEMS) {
			B_DispCT = DispScrCurrLoc;
			DispScrCurrLoc = Scr_Cnt_Select(cnt, DispScrCurrLoc, Total_Disp_Item , 0 );
			DispCT = DispScrCurrLoc;
			ScrollCnt_Select(DispScrCurrLoc, Total_Disp_Item+1, &DispScrStartCT, &DispScrEndCT, 2);

			if(DispCT==CP_Sta_B_VALUE && Disp_tmp->UTILITY.B_ONOFF ) {	/* When B vaue is ON */
				if(cnt>0)
					DispScrCurrLoc--;
				else if(cnt<0)
					DispScrCurrLoc++;
			}

			if(DispScrCurrLoc != B_DispCT) {
				DataRedrawFlag|= PARA_CHANGE+PARA_CHANGE_Fast;
				ChanRedrawFlag |= CHAN_STATUS;
			}
		} else if(DispMode == DispMode_SET_PARAMETERS) {
			Compensation_Flag = 0;
			Compensation_Count = 0;
			Error_Amount_Flag = 0;

			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00 ;
			data = GetChanData(DispCT,0);

			/* Get Max. Setting & Min. Setting */
			if(DispScrCurrLoc<=CP_Dyn_L2)
				t_range = &Disp_tmp->IRange;									/* Get CC Mode Range */

			if(DispScrCurrLoc==CP_Sta_Add_CV) {
				max = (ptrMODEL_TYPE->CV)[V_Range*3].Max;
				min = (ptrMODEL_TYPE->CV)[V_Range*3].Min-1;
			} else if(DispScrCurrLoc==CP_Sta_Add_CV) {
				max = (ptrMODEL_TYPE->CV)[V_Range*3].Max;
				min = (ptrMODEL_TYPE->CV)[V_Range*3].Min - 1;
			} else if(DispScrCurrLoc==CP_Sta_CV_Response) {
				max = 1;
				min = 0;
			} else {
				max = (ptrMODEL_TYPE->CP)[DispScrCurrLoc+(*t_range)*10].Max;
				min = (ptrMODEL_TYPE->CP)[DispScrCurrLoc+(*t_range)*10].Min;
			}

			if(Disp_tmp->CONF.Knob_Status) {
				cnt_STEP = cnt;
				CursorValue = powf(10.0,Magnification_Cnt-CursorPrecision);
				cnt_STEP *= InputToStep((_CursorResolution/2+CursorValue),_CursorResolution);
				if(cnt_STEP==0)cnt_STEP=cnt;
				if(cnt_STEP>(65534/2))cnt_STEP = 32764;
				else if(cnt_STEP<(-65534/2))cnt_STEP = -32764;
			} else if((DispScrCurrLoc <= CP_Sta_B_VALUE)&&(Data_tmp->Coarse))
				cnt_STEP = cnt * Disp_tmp->CP.VALUE_STEP[Disp_tmp->IRange];
			else
				cnt_STEP = cnt;

			data = Cnt_Select_Step(cnt_STEP, data, max, min);		/* inc */


			SaveChanData(DispScrCurrLoc,data);
			if(UTILITY.KEYKNOB) {
				if(DispScrCurrLoc==CP_Sta_Add_CV)
					Data_tmp->CV.STA[Data_tmp->VRange].VALUE1 = Disp_tmp->CV.STA[Data_tmp->VRange].VALUE1;
				else
					Data_tmp->CP = Disp_tmp->CP;
				MenuDecoderAddr(&tx_data);
				SendTXData(&tx_data);
			}


			DataRedrawFlag |=PARA_CHANGE;
			if((DispScrCurrLoc<=CP_Sta_B_VALUE)&&(!Disp_tmp->UTILITY.B_ONOFF)) {
				if(UTILITY.KEYKNOB) {
					tx_data.ADDRH = 0x04;
					tx_data.ADDRL = 0x00;
					SendTXData(&tx_data);

				}
			}
		}
		break;
	case P_CC_SPEC:
	case P_CR_SPEC:
	case P_CV_SPEC:
	case P_CP_SPEC:
		if((DispScrCurrLoc!=P_SPEC_HIGH)||(DispScrCurrLoc!=P_SPEC_LOW))
			val = 0;
		else
			val = DispScrCurrLoc-2;
		type = Disp_tmp->SPECTYPE;
		switch(M_num) {
		case P_CC_SPEC:
			umax = ptrMODEL_TYPE->CC_SPEC[val].Max;
			umin = ptrMODEL_TYPE->CC_SPEC[val].Min;
			break;
		case P_CR_SPEC:
			umax = ptrMODEL_TYPE->CR_SPEC[val].Max;
			umin = ptrMODEL_TYPE->CR_SPEC[val].Min;
			break;
		case P_CV_SPEC:
			umax = ptrMODEL_TYPE->CV_SPEC[val].Max;
			umin = ptrMODEL_TYPE->CV_SPEC[val].Min;
			break;
		case P_CP_SPEC:
			umax = ptrMODEL_TYPE->CP_SPEC[val].Max;
			umin = ptrMODEL_TYPE->CP_SPEC[val].Min;
			break;
		}
		if(type)
			Total_Disp_Item = P_SPEC_MAX - 1;
		else
			Total_Disp_Item = P_SPEC_MAX - 2;
		if(DispMode_BROWSE_ITEMS==DispMode) {
			B_DispCT = DispScrCurrLoc;
			DispScrCurrLoc = Scr_Cnt_Select(cnt, DispScrCurrLoc, Total_Disp_Item , 0 );
			DispCT = DispScrCurrLoc;
			ScrollCnt_Select(DispScrCurrLoc, Total_Disp_Item+1, &DispScrStartCT, &DispScrEndCT, 4);
			if(DispScrCurrLoc != B_DispCT)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		} else if(DispMode == DispMode_SET_PARAMETERS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			/*	Transfer Data From Value to Counter	*/
			if(DispScrCurrLoc==P_SPEC_TEST) {
				data = Cnt_Select2(cnt, Disp_tmp->SPEC, 1, 0);
				if(data==Disp_tmp->SPEC)
					break;
				else
					Disp_tmp->SPEC = data;
			} else if(DispScrCurrLoc==P_SPEC_DELAY) {
				data = Cnt_Select2(cnt, Disp_tmp->P_F_Delay, 10, 0);
				if(data==Disp_tmp->P_F_Delay)
					break;
				else
					Disp_tmp->P_F_Delay=data;
			} else if(DispScrCurrLoc==P_SPEC_ENTRY) {
				data = Cnt_Select2(cnt, Disp_tmp->SPECTYPE, 1, 0);
				if(data==Disp_tmp->SPECTYPE)
					break;
				else
					Disp_tmp->SPECTYPE=data;
			} else if(DispScrCurrLoc==P_SPEC_CENTER) {
				data=Cnt_Select_Step(cnt,GetChanData(6,0),umax,umin);
				SaveChanData(6,data);
				if(data) {
					h_old = GetChanData(9,0);        	 //GET HIPCET*/
					h_new = data+((((float)(h_old))/1000.0)*data);
					if(h_new>umax){
						h_new = umax;
#if 1
						h_old = (UWORD) ((float)umax*1000/(float)data-999);
						if(data==umax)	h_old = 0;	//printf("H_pcet:%d\n",h_old);
						SaveChanData(9,h_old);
#endif
					}
					l_old = GetChanData(10,0);         //GET LOWPCET*/
					l_new = data-(((float)(l_old))/1000.0)*data;
					if(l_new>data)
						l_new = data;
					SaveChanData(7,h_new);
					SaveChanData(8,l_new);
				} else {
					SaveChanData(7,data);
					SaveChanData(8,data);
				}
			} else if(DispScrCurrLoc==P_SPEC_HIGH) {
				if(Disp_tmp->SPECTYPE) {
					data = GetChanData(9,0);
					data = Cnt_Select2(cnt, data, 1000, 0);
#if 1
					UWORD CentValue;
					CentValue = GetChanData(6,0);		  //GET HIPCET
					h_old = 	(UWORD)((float)(umax-CentValue)*1000/(float)CentValue)+1;
					if(data>h_old)	data=h_old;					
#endif					
					SaveChanData(9, data);
					GNGPcet2Step(0);
				} else {
					umin = GetChanData(8,0);   /*Get Low Value*/
					data = Cnt_Select_Step(cnt, GetChanData(1+6,0), umax, umin);
					SaveChanData(1+6,data);
					GNGStep2Pcet(0);
				}
			} else if(DispScrCurrLoc==P_SPEC_LOW) {
				if(Disp_tmp->SPECTYPE) {
					data = GetChanData(10,0);
					data = Cnt_Select2(cnt, data, 1000, 0);
					SaveChanData(10, data);
					GNGPcet2Step(1);
				} else {
					umax=GetChanData(7,0);   /*Get High Value*/
					data = Cnt_Select_Step(cnt, GetChanData(2+6,0), umax, umin);
					SaveChanData(2+6,data);
					GNGStep2Pcet(1);
				}
			}
			DataRedrawFlag|= PARA_CHANGE;
		}
		break;
	case P_CONF_PROT:
		if(DispMode == DispMode_BROWSE_ITEMS) {
			B_DispCT = DispScrCurrLoc;
			tmp = DispScrCurrLoc;
#if Enable_Ring_Count
			tmp = Scr_Cnt_Select(cnt, tmp, P_OVP_LEVEL, 0);
			DispScrCurrLoc = tmp;
			ScrollCnt_Select(tmp, Pro_Max, &DispScrStartCT, &DispScrEndCT, 4);
#else
			tmp = Scr_Cnt_Select(cnt, tmp, 5, 0);
			DispScrCurrLoc = tmp;
			ScrollCnt_Select(tmp, 6, &DispScrStartCT, &DispScrEndCT, 4);
#endif			
			if( DispScrCurrLoc != B_DispCT)
				DataRedrawFlag|= PARA_CHANGE+PARA_CHANGE_Fast;
		} else if(DispMode == DispMode_SET_PARAMETERS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00 ;
			data = GetChanData(DispScrCurrLoc,0);
			if((DispScrCurrLoc==P_OCP_SETTING)||(DispScrCurrLoc==P_OPP_SETTING)) {
#if Enable_OPPOCP_off
				max = 2;
#else
				max = 1;
#endif
				min = 0;
#if Enable_Ring_Count
			}else if(DispScrCurrLoc==P_UVP_SETTING){
				data++;
				max = 602;
				min = 1;
#endif

			} else {
				if(DispScrCurrLoc==P_OCP_LEVEL)
					range = PROT_OCP_H;
				else if(DispScrCurrLoc==P_OPP_LEVEL)
					range = PROT_OPP_H;
				else if(DispScrCurrLoc==P_UVP_LEVEL) {
					if(VRange_Low==Data_tmp->VRange)
						range = PROT_UVP_L;
					else
						range = PROT_UVP_H;
				} else if(DispScrCurrLoc==P_OVP_LEVEL) {
					if(VRange_Low==Data_tmp->VRange)
						range = PROT_OVP_L;
					else
						range = PROT_OVP_H;
				}
				max=ptrMODEL_TYPE->PROT[range].Max;
				min=ptrMODEL_TYPE->PROT[range].Min;
			}

			data = Cnt_Select_Step(cnt, data, max, min);
			SaveChanData(DispScrCurrLoc, data);
			DataRedrawFlag|= PARA_CHANGE;

			if(UTILITY.KEYKNOB) {
				Data_tmp->PROT = Disp_tmp->PROT;
				MenuDecoderAddr(&tx_data);
				SendTXData(&tx_data);
			}
		}
		break;
	case P_CONF_OTHER:
		if(DispMode == DispMode_BROWSE_ITEMS) {
			B_DispCT = DispScrCurrLoc;
			tmp = DispScrCurrLoc;
			tmp = Scr_Cnt_Select(cnt, tmp, P_Conf_Max - 1, 0);
			DispScrCurrLoc = tmp;
			ScrollCnt_Select(tmp, P_Conf_Max, &DispScrStartCT, &DispScrEndCT, 4);

			if( DispScrCurrLoc != B_DispCT)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		} else if(DispMode == DispMode_SET_PARAMETERS) {
			KeyInFlag&=(~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00 ;
			data = GetChanData(DispScrCurrLoc,0);

			if(P_SOFT_START==DispScrCurrLoc) {
				max = ptrMODEL_TYPE->CONF[2].Max;
				min = ptrMODEL_TYPE->CONF[2].Min;
			} else if(P_VON_VOLTAGE==DispScrCurrLoc) {
				range =  GetNowRange();
				range &= 0x01;
				max	  =  ptrMODEL_TYPE->CONF[range].Max;
				min	  =  ptrMODEL_TYPE->CONF[range].Min;
			} else if(P_CUTOFFTIME==DispScrCurrLoc) {
				if(P3k_Chan_Data.CONF.Cut_Off_cnt==0) {
					max = 999;
					data = P3k_Chan_Data.CONF.Cut_Off_Time_h;
				} else if(P3k_Chan_Data.CONF.Cut_Off_cnt==1) {
					max = 59;
					data = P3k_Chan_Data.CONF.Cut_Off_Time_m;
				} else if(P3k_Chan_Data.CONF.Cut_Off_cnt==2) {
					max = 59;
					data = P3k_Chan_Data.CONF.Cut_Off_Time_s;
				}
				min = 0;
			}

			else if(DispScrCurrLoc == P_Von_Delay) {
				max = 60000;
				min = 1900;
				if(P3k_Disp_Data.CURRMODE==CR_MODE)
					min = 4900;
			} else {
				max = 1;				/* Turn On or Off */
				min = 0;
			}

			if(DispScrCurrLoc == P_Von_Delay)
				cnt_STEP = cnt * 100;
			else
				cnt_STEP = cnt;

			data = Cnt_Select_Step(cnt_STEP, data, max, min);

			SaveChanData(DispScrCurrLoc, data);
			DataRedrawFlag|= PARA_CHANGE;
			Data_tmp->CONF = Disp_tmp->CONF;

			if(DispScrCurrLoc == P_SHORT_KEY) {
				if(UTILITY.KEYKNOB) {
					tx_data.ADDRH = Machine_Command;
					tx_data.ADDRL = 0x03;
					SendTXData(&tx_data);
				}
			}

			if(DispScrCurrLoc == P_SOFT_START) {
				if(UTILITY.KEYKNOB) {
					tx_data.ADDRH = 0x01;
					tx_data.ADDRL = 0x00;
					SendTXData(&tx_data);
				}
			}
		}
		break;
	case P_CONF_KNOB:
		if(DispMode == DispMode_BROWSE_ITEMS) {
			B_DispCT = DispScrCurrLoc;
			tmp = DispScrCurrLoc;
			tmp = Scr_Cnt_Select(cnt, tmp, P_Konb_MAX-1, 0);
			DispScrCurrLoc = tmp;
			DispCT = DispScrCurrLoc;
			ScrollCnt_Select(tmp, P_Konb_MAX, &DispScrStartCT, &DispScrEndCT, 4);

			if( DispScrCurrLoc != B_DispCT)
				DataRedrawFlag|= PARA_CHANGE+PARA_CHANGE_Fast;
		} else if(DispMode==DispMode_SET_PARAMETERS) {
			KeyInFlag&=(~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00 ;
			data = GetChanData(DispScrCurrLoc,0);

			if(DispScrCurrLoc==P_Knob_Status) {
				max = 1;
				min = 0;
			} else {
				if(!Disp_tmp->CONF.Knob_Status) {
					Magnification_Cnt = 0;

					switch(DispScrCurrLoc) {
					case P_CCH_STEP:
						max = (ptrMODEL_TYPE->CC)[10].Max/2;
						break;
					case P_CCL_STEP:
						max = (ptrMODEL_TYPE->CC)[0].Max/2;
						break;
					case P_CRH_STEP:
						max = (ptrMODEL_TYPE->CR)[10].Max/2;
						break;
					case P_CRL_STEP:
						max = (ptrMODEL_TYPE->CR)[0].Max/2;
						break;
					case P_CVH_STEP:
						max = (ptrMODEL_TYPE->CV)[3].Max/2;
						break;
					case P_CVL_STEP:
						max = (ptrMODEL_TYPE->CV)[0].Max/2;
						break;
					case P_CPH_STEP:
						max = (ptrMODEL_TYPE->CP)[10].Max/2;
						break;
					case P_CPL_STEP:
						max = (ptrMODEL_TYPE->CP)[0].Max/2;
						break;
					default:
						break;
					}
					min = 1;
				}
			}

			data = Cnt_Select2(cnt, data, max, min);
			SaveChanData(DispScrCurrLoc, data);

			for(i=0; i<2; i++) {
				Data_tmp->CC.VALUE_STEP[i]= Disp_tmp->CC.VALUE_STEP[i];
				Data_tmp->CR.VALUE_STEP[i]= Disp_tmp->CR.VALUE_STEP[i];
				Data_tmp->CV.VALUE_STEP[i]= Disp_tmp->CV.VALUE_STEP[i];
				Data_tmp->CP.VALUE_STEP[i]= Disp_tmp->CP.VALUE_STEP[i];
			}

			Data_tmp->CONF.Knob_Status = Disp_tmp->CONF.Knob_Status;
			DataRedrawFlag|= PARA_CHANGE;
		}
		break;
	case P_PROG_MAIN:
		if(DispMode==DispMode_SELECT_CH) {
			B_DispCT = DispCT;
			DispCT = Scr_Cnt_Select(cnt, DispCT, Prog_Max-1, 0);
			if( B_DispCT != DispCT)
				DataRedrawFlag|= PARA_CHANGE+PARA_CHANGE_Fast;
		} else if(DispMode==DispMode_BROWSE_ITEMS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			if( Program_PROG==DispCT||Program_STEP==DispCT ) {
				max = 15;
				min = 0;
			} else if(Program_Memory==DispCT) {
				max = 255;
				min = 0;
			} else if(Program_Run==DispCT) {
				max = 2;
				min = 0;
			} else if(Program_On_Time==DispCT) {
				max = 600;
				min = 1;
			} else if(Program_Off_Time==DispCT) {
				max = 600;
				min = 0;
			} else if(Program_P_F_Time==DispCT) {
				max = (Prog_tmp->Timing_Data[Prog_tmp->Prog_No].ONTIME[Prog_tmp->Step_No]+Prog_tmp->Timing_Data[Prog_tmp->Prog_No].OFFTIME[Prog_tmp->Step_No])-1;
				min = 0;
			} else if(Program_Short_Time==DispCT) {
				max = Prog_tmp->Timing_Data[Prog_tmp->Prog_No].ONTIME[Prog_tmp->Step_No];
				min = 0;
			} else {
				max = 1;
				min = 0;
			}
			data1 = data = GetChanData(DispCT,0);
			data = Cnt_Select2(cnt, data, max, min);
			SaveChanData(DispCT, data);
			if(data1!=data)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		}
		break;
	case P_PROG_CHAIN:
		if(DispMode == DispMode_SELECT_CH) {
			tmp=p3k_Disp_PROG.Chain_Start_Prog;
			p3k_Disp_PROG.Chain_Start_Prog = Cnt_Select2(cnt, p3k_Disp_PROG.Chain_Start_Prog, 15, 0);
			if(tmp!=p3k_Disp_PROG.Chain_Start_Prog)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		} else if(DispMode == DispMode_BROWSE_ITEMS) {
			B_DispCT=DispScrCurrLoc;
			tmp=DispScrCurrLoc;
			DispScrCurrLoc = Scr_Cnt_Select(cnt, DispScrCurrLoc, 15, 0);
			ScrollCnt_Select(DispScrCurrLoc, 16, &DispScrStartCT, &DispScrEndCT, 3);
			if(tmp!=DispScrCurrLoc)
				DataRedrawFlag |= PARA_CHANGE;
		} else if(DispMode == DispMode_SET_PARAMETERS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;

			tmp = p3k_Disp_PROG.PROGSEQ[DispScrCurrLoc];
			tmp = Cnt_Select2(cnt , tmp, 16, 0);
			if(p3k_Disp_PROG.PROGSEQ[DispScrCurrLoc] != tmp) {
				p3k_Disp_PROG.PROGSEQ[DispScrCurrLoc] = tmp;
				DataRedrawFlag |= PARA_CHANGE;
			}
		}
		break;
	case P_PROG_Detail:
		B_DispCT = DispScrCurrLoc;
		tmp = DispScrCurrLoc;
		tmp = Scr_Cnt_Select(cnt, tmp, Prog_Seq_Data.Total_Count-1, 0);
		DispScrCurrLoc = tmp;
		if(Prog_Seq_Data.Total_Count > 3)
			ScrollCnt_Select(tmp, Prog_Seq_Data.Total_Count, &DispScrStartCT, &DispScrEndCT, 3);
		else
			ScrollCnt_Select(tmp, Prog_Seq_Data.Total_Count, &DispScrStartCT, &DispScrEndCT, Prog_Seq_Data.Total_Count-1);
		if( DispScrCurrLoc != B_DispCT)
			DataRedrawFlag|= PARA_CHANGE+PARA_CHANGE_Fast;
		break;
	case P_UTIL_KEYPAD:
		KeySelFunc(KeyAccTable[16+cnt]);
		break;
	case P_FILE_MACHINE:
		break;
	case P_FILE_CHAN:
		if(p3k_File_Utility_BAR.MEDIA==F_Media_Default)  /*Media-Default*/
			break;
		if(DispMode == DispMode_SELECT_CH) {
			B_DispCT = DispCT;
			if( p3k_File_Utility_BAR.MEDIA==F_Media_USB )
				DispCT = Scr_Cnt_Select(cnt, DispCT, 2, 0);
			else 		/*Media-Memory*/
				DispCT = Scr_Cnt_Select(cnt, DispCT, 1, 0);

			if( DispCT != B_DispCT)
				DataRedrawFlag|=PARA_CHANGE+PARA_CHANGE_Fast;
		} else {
			if(F_Media_USB==p3k_File_Utility_BAR.MEDIA) {	/*USB*/
				if(DispCT==P_USB_Type) {
					tmp = p3k_File_Utility_BAR.USB_Data_Type;
					tmp = Cnt_Select2(cnt, tmp, 4, 0);
					if(p3k_File_Utility_BAR.USB_Data_Type!=tmp) {
						DataRedrawFlag |= PARA_CHANGE;
						p3k_File_Utility_BAR.USB_Data_Type = tmp;
					}
				}
				if(USB_Status_Display==USB_Exist) {
					if(DispCT==P_USB_Save) {
						if(p3k_File_Utility_BAR.USB_Data_Type==F_Setup_Data) { /*Setup*/
							SavSetupFileCount = Cnt_Select(cnt,SavSetupFileCount,USBNumerTotal);
							//SavSetupFileCount = NextFileName(SavSetupFileCount,SaveFileName,Sav_Set,cnt);
							FileNameConvert(SavSetupFileCount, SaveFileName, Sav_Set);
						} else if(p3k_File_Utility_BAR.USB_Data_Type==F_Memory_Data) { /*Memory*/
							SavMemoryFileCount = Cnt_Select(cnt,SavMemoryFileCount,USBNumerTotal);
							//SavMemoryFileCount = NextFileName(SavMemoryFileCount,SaveFileName,Sav_Memory,cnt);
							FileNameConvert(SavMemoryFileCount, SaveFileName, Sav_Memory);
						} else if(p3k_File_Utility_BAR.USB_Data_Type==F_Preset_Data) { /*Preset*/
							SavPresetFileCount = Cnt_Select(cnt,SavPresetFileCount,USBNumerTotal);
							//SavPresetFileCount = NextFileName(SavPresetFileCount,SaveFileName,Sav_Preset,cnt);
							FileNameConvert(SavPresetFileCount, SaveFileName, Sav_Preset);
						} else if(p3k_File_Utility_BAR.USB_Data_Type==F_NSeq_Data) { /*Seq Data*/
							SavNSeqFileCount = Cnt_Select(cnt,SavNSeqFileCount,USBNumerTotal);
							//SavNSeqFileCount = NextFileName(SavNSeqFileCount,SaveFileName,Sav_NSeq,cnt);
							FileNameConvert(SavNSeqFileCount, SaveFileName, Sav_NSeq);
						} else if(p3k_File_Utility_BAR.USB_Data_Type==F_FSeq_Data) { /*Seq Data*/
							SavFSeqFileCount = Cnt_Select(cnt,SavFSeqFileCount,USBNumerTotal);
							//SavFSeqFileCount = NextFileName(SavFSeqFileCount,SaveFileName,Sav_FSeq,cnt);
							FileNameConvert(SavFSeqFileCount, SaveFileName, Sav_FSeq);
						}
						DataRedrawFlag |= PARA_CHANGE;
					}
					if(DispCT==P_USB_Recall) {
						strcpy(FileName_Temp,RecallFileName);
						if(p3k_File_Utility_BAR.USB_Data_Type==F_Setup_Data)
							RecallFileNameFun(FMnowPath, RecallFileName, Sav_Set,	cnt);
						else if(p3k_File_Utility_BAR.USB_Data_Type==F_Memory_Data)
							RecallFileNameFun(FMnowPath, RecallFileName, Sav_Memory,	cnt);
						else if(p3k_File_Utility_BAR.USB_Data_Type==F_Preset_Data)
							RecallFileNameFun(FMnowPath, RecallFileName, Sav_Preset,	cnt);
						else if(p3k_File_Utility_BAR.USB_Data_Type==F_NSeq_Data)
							RecallFileNameFun(FMnowPath, RecallFileName, Sav_NSeq,	cnt);
						else if(p3k_File_Utility_BAR.USB_Data_Type==F_FSeq_Data)
							RecallFileNameFun(FMnowPath, RecallFileName, Sav_FSeq,	cnt);

						if(strcmp(FileName_Temp,RecallFileName))
							DataRedrawFlag |= PARA_CHANGE;
					}
				}
			} else if(F_Media_Memory==p3k_File_Utility_BAR.MEDIA) {	/*Memory*/
				KeyInFlag &= (~DIGI_KEY_IN);
				KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00 ;

				if(DispCT==P_Memory_Type) {
					tmp = p3k_File_Utility_BAR.Mem_Data_Type;
					tmp = Cnt_Select2(cnt, tmp, 2, 0);

					if(p3k_File_Utility_BAR.Mem_Data_Type != tmp) {
						DataRedrawFlag |= PARA_CHANGE;
						p3k_File_Utility_BAR.Mem_Data_Type = tmp;
					}
				}
				if(DispCT==P_Memory_Number) {
					if(F_Memory_Data==p3k_File_Utility_BAR.Mem_Data_Type) {
						tmp = p3k_File_Utility_BAR.MEMORY_ADDR;
						tmp = Cnt_Select2(cnt, tmp, 255, 0);
						if(p3k_File_Utility_BAR.MEMORY_ADDR!=tmp) {
							p3k_File_Utility_BAR.MEMORY_ADDR = tmp;
							DataRedrawFlag |= PARA_CHANGE;
						}
					} else if(F_Setup_Data==p3k_File_Utility_BAR.Mem_Data_Type) {
						tmp = p3k_File_Utility_BAR.SMEMORY_ADDR;
						tmp = Cnt_Select2(cnt, tmp, 99, 0);
						if(p3k_File_Utility_BAR.SMEMORY_ADDR != tmp) {
							p3k_File_Utility_BAR.SMEMORY_ADDR = tmp;
							DataRedrawFlag |= PARA_CHANGE;
						}
					} else if(F_Preset_Data==p3k_File_Utility_BAR.Mem_Data_Type) {
						tmp = p3k_File_Utility_BAR.PRE_MEMORY_ADDR;
						tmp = Cnt_Select2(cnt, tmp, 9, 0);
						if(p3k_File_Utility_BAR.PRE_MEMORY_ADDR != tmp) {
							p3k_File_Utility_BAR.PRE_MEMORY_ADDR = tmp;
							DataRedrawFlag |= PARA_CHANGE;
						}
					}
				}
			}
		}
		break;
	case P_UTIL_T_DATE:
		if( DispMode==DispMode_SELECT_CH) {
			B_DispCT = DispCT;
			DispCT = Scr_Cnt_Select(cnt, DispCT, 4, 0 );

			if( DispCT != B_DispCT)
				DataRedrawFlag|=PARA_CHANGE+PARA_CHANGE_Fast;
		} else {
			if(DispCT==0)
				TIMERSET.MONTH = Cnt_Select2(cnt, TIMERSET.MONTH, 12, 1);
			else if(DispCT==1)
				TIMERSET._DAY = Cnt_Select2(cnt, TIMERSET._DAY, 31, 1);
			else if(DispCT==2)
				TIMERSET.YEAR = Cnt_Select2(cnt, TIMERSET.YEAR, 2038, 1990);
			else if(DispCT==3)
				TIMERSET._HOUR = Cnt_Select2(cnt, TIMERSET._HOUR, 23, 0);
			else if(DispCT==4)
				TIMERSET._MINUTE = Cnt_Select2(cnt, TIMERSET._MINUTE, 59, 0);
			DataRedrawFlag|=PARA_CHANGE;
		}
		break;
	case P_UTIL_OTHER:
		if(DispMode==DispMode_SELECT_CH) {
			B_DispCT = DispScrCurrLoc;
			tmp = DispScrCurrLoc;
			tmp = Scr_Cnt_Select(cnt, tmp, 7, 0);
			DispScrCurrLoc = tmp;
			ScrollCnt_Select(tmp, 8, &DispScrStartCT, &DispScrEndCT, 4);

			if( DispScrCurrLoc != B_DispCT)
				DataRedrawFlag|= PARA_CHANGE+PARA_CHANGE_Fast;
		} else {
			switch(DispScrCurrLoc) {
			case Util_Knob_Type:
				UTILITY.KEYKNOB = Cnt_Select2(cnt, UTILITY.KEYKNOB, 1, 0);
				break;
			case Util_Speaker:
				tmp=UTILITY.BEEP_ONOFF;
				UTILITY.BEEP_ONOFF = Cnt_Select2(cnt, UTILITY.BEEP_ONOFF, 1, 0);		/* On, Off */
				if(tmp!=UTILITY.BEEP_ONOFF) {
					if(UTILITY.KEYKNOB) {
						tx_data.ADDRH = Machine_Command;
						tx_data.ADDRL = 0x0C;
						SendTXData(&tx_data);
					}
				}
				if((UTILITY.BEEP_ONOFF)&&(!Tone_Flag)) {
					Key_Count = 3;
					BuzzerFunction(Buzzer_Key,Key_Count--);
				}
				break;
			case Util_Alarm_Tone:
#if Enable_Ring_Count
				Tone_Flag&=(~0x01);
				UVP_Tone_Count = 0;
				Tone_Flag&=(~0x08);
				SEQ_Tone_Count = 0;
#endif				
				UTILITY.Master_Alarm_Tone = Cnt_Select2(cnt, UTILITY.Master_Alarm_Tone, 1, 0);
				if((UnReg_Alarm != p3k_Measure_Data.Alarm) && (p3k_Measure_Data.Alarm != 0) && (UTILITY.Master_Alarm_Tone) && (!Tone_Flag)) {
					Tone_Flag|=0x01;
					Alarm_Count = 250;
					BuzzerFunction(Buzzer_Alarm,Alarm_Count--);
				}
				break;
			case Util_UnReg_Tone:
				UTILITY.UnReg_Alarm_Tone = Cnt_Select2(cnt, UTILITY.UnReg_Alarm_Tone, 1, 0);
				if((p3k_Measure_Data.Alarm == UnReg_Alarm)&&(UTILITY.UnReg_Alarm_Tone)&&(!Tone_Flag)) {
					Tone_Flag |= 0x04;
					UnReg_Count = 200;
					BuzzerFunction(Buzzer_UnReg,UnReg_Count--);
				}
				break;
			case Util_Go_NoGO_Tone:
				UTILITY.Master_NG_Tone = Cnt_Select2(cnt, UTILITY.Master_NG_Tone, 1, 0);
				if((p3k_Measure_Data.Go_NoGo == 1)&&(UTILITY.Master_NG_Tone)&&(!Tone_Flag)) {
					Tone_Flag |= 0x02;
					NG_Count = 300;
					BuzzerFunction(Buzzer_NG,NG_Count--);
				}
				break;
			case Util_Contrast:
				UTILITY.CONTRAST_LV = Cnt_Select2(cnt, UTILITY.CONTRAST_LV, 13, 3);	/* 1 ~ 4 */
				Control_LCDBRCon();
				break;
			case Util_Brightness:
				UTILITY.BRIGHTNESS_LV = Cnt_Select2(cnt, UTILITY.BRIGHTNESS_LV, 90, 50);	/* 1 ~ 5 */
				Control_LCDBRCon();
				break;
			case Util_Language:
				UTILITY.LANGUAGE = Cnt_Select2(cnt, UTILITY.LANGUAGE, 0, 0);
				break;
			}
			DataRedrawFlag |=PARA_CHANGE;
		}
		break;
	case P_UTIL_INTERFACE:
		if(DispMode==DispMode_SELECT_CH) {
			B_DispCT= DispCT;
			if(UTILITY.INTERFACE==INTERFACE_RS232)
				DispCT = Scr_Cnt_Select(cnt, DispCT, 3, 0);
			else if(UTILITY.INTERFACE==INTERFACE_GPIB)
				DispCT = Scr_Cnt_Select(cnt, DispCT, 1, 0);
			else if(UTILITY.INTERFACE==INTERFACE_USB)
				DispCT = Scr_Cnt_Select(cnt, DispCT, 0, 0);
			if( B_DispCT != DispCT)
				DataRedrawFlag|=PARA_CHANGE+PARA_CHANGE_Fast;
		} else {
			if( (D_interface.INTERFACE==INTERFACE_GPIB)&&(DispCT==1) )
				DispCT_temp = GPIB_Address;
			else
				DispCT_temp = DispCT;

			if(Interface_Select==DispCT_temp) {
				D_interface.INTERFACE=Cnt_Select2(cnt, D_interface.INTERFACE, 2, 1);		/* RS232 GPIB USB */
				if((!(SYSType&GPIB_CONNECTED))&&(D_interface.INTERFACE==INTERFACE_GPIB)) {
					if(cnt<0){
						D_interface.INTERFACE++;
					}else if(cnt>0)
						D_interface.INTERFACE++;
				}
			} else if(Baud_Rate	==DispCT_temp)
				D_interface.BAUD	= Cnt_Select2(cnt, D_interface.BAUD, 4, 0);		/* 2400, 4800, 9600, 19200, 38400 */
			else if(Stop_Bit	==DispCT_temp)
				D_interface.STOP	= Cnt_Select2(cnt, D_interface.STOP, 1, 0);		/* 1, 2 */
			else if(RS232_Parity==DispCT_temp)
				D_interface.PARITY	= Cnt_Select2(cnt, D_interface.PARITY, 2, 0);		/* None, Even, Odd */
			else
				D_interface.MYADDR	= Cnt_Select2(cnt, D_interface.MYADDR, 30, 1);
			DataRedrawFlag|=PARA_CHANGE;
		}
		break;
	case P_UTIL_LOAD:
#if Enable_AutoLoad
		if(DispMode==DispMode_SELECT_CH) {
			B_DispCT = DispCT;
#if Enable_Short_invalidate
			DispCT=Scr_Cnt_Select(cnt, DispCT, 3, 0);
#else
			DispCT=Scr_Cnt_Select(cnt, DispCT, 4, 0);
#endif			
			if( B_DispCT != DispCT)
				DataRedrawFlag|=PARA_CHANGE+PARA_CHANGE_Fast;
		} else {
			if(DispCT==0)
				UTILITY.ALOAD = Cnt_Select2(cnt, UTILITY.ALOAD, 1, 0);		/* On, Off */
			else if(DispCT==1)
				UTILITY.ALOAD_MODE = Cnt_Select2(cnt, UTILITY.ALOAD_MODE, 3, 0);	/*0:LOAD 1:PROG 2:NSeq 3:FSeq*/
			else if(DispCT==2)
				UTILITY.AutoLoadOffMode= Cnt_Select2(cnt, UTILITY.AutoLoadOffMode, 1, 0);	/*0:LOAD 1:PROG 2:NSeq 3:FSeq*/
			else if(DispCT==3)
				UTILITY.AutoLoadOffRange= Cnt_Select2(cnt, UTILITY.AutoLoadOffRange, 1, 0);	/*0:LOAD 1:PROG 2:NSeq 3:FSeq*/
#if Enable_Short_invalidate==0
			else
				UTILITY.ShortonLoadoff = Cnt_Select2(cnt, UTILITY.ShortonLoadoff, 1, 0);	/*0:LOAD 1:PROG 2:NSeq 3:FSeq*/
#endif
			DataRedrawFlag|=PARA_CHANGE;
		}
#else
		if(DispMode==DispMode_SELECT_CH) {
			B_DispCT = DispCT;
			DispCT=Scr_Cnt_Select(cnt, DispCT, 1, 0);
			if( B_DispCT != DispCT)
				DataRedrawFlag|=PARA_CHANGE+PARA_CHANGE_Fast;
		} else {
			if(DispCT==0)
				UTILITY.ALOAD = Cnt_Select2(cnt, UTILITY.ALOAD, 1, 0);		/* On, Off */
			else
				UTILITY.ALOAD_MODE = Cnt_Select2(cnt, UTILITY.ALOAD_MODE, 3, 0);	/*0:LOAD 1:PROG 2:NSeq 3:FSeq*/
			DataRedrawFlag|=PARA_CHANGE;
		}
#endif
		break;
	case P_UTIL_FILE:
		VarSelect(KeyAccTable[16+cnt]);
		break;
	case P_HELP_HELP:
		DataRedrawFlag |= PARA_CHANGE;
		break;
	case P_CAL_MODE:

		if(DispMode==DispMode_SELECT_CH) {
			B_DispCT	= DispCT;
#if Enable_Ext_CalOffset
			if((P3K_CALIBRATION_BAR.MODE==CC_MODE)||(P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)||(P3K_CALIBRATION_BAR.MODE>=Ext_V_CC_MODE)) {
#else
			if((P3K_CALIBRATION_BAR.MODE==CC_MODE)||(P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)) {
#endif
				if(p3k_Cal_data.OffsetFlag&0x01) { // 1st company
					if(DispCT==0) {
						if(p3k_Cal_data.OffsetFlag&0x02) {
							if(cnt<0)
								DispCT =1;
							else
								p3k_Cal_data.OffsetFlag &= 0xFD;
						} else {
							if(cnt<0)
								p3k_Cal_data.OffsetFlag |= 0x02;
						}
					} else { // 1
						DispCT	= Scr_Cnt_Select(cnt, DispCT,1, 0);
					}


				} else { //non_company

				}
				DataRedrawFlag|=PARA_CHANGE+PARA_CHANGE_Fast;
			} else {
				DispCT	= Scr_Cnt_Select(cnt, DispCT,1, 0);
				if(B_DispCT!=DispCT)
					DataRedrawFlag|=PARA_CHANGE+PARA_CHANGE_Fast;
			}

		}

		else if(DispMode==DispMode_BROWSE_ITEMS) {
#if Enable_Ext_CalOffset
			if(((P3K_CALIBRATION_BAR.MODE==CC_MODE)||(P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)||(P3K_CALIBRATION_BAR.MODE>=Ext_V_CC_MODE))&&((p3k_Cal_data.OffsetFlag&0x02)==0)) {
#else
			if(((P3K_CALIBRATION_BAR.MODE==CC_MODE)||(P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE))&&((p3k_Cal_data.OffsetFlag&0x02)==0)) {
#endif
				cnt *= 10;
				p3k_Cal_data.OffsetAdjCnt1 = Cnt_Select_Step(cnt, p3k_Cal_data.OffsetAdjCnt1,Calibration_Adj_maxValue, Calibration_Adj_minValue);
				tx_data.ADDRH = Cal_FPGA_Command;
				tx_data.ADDRL = Cal_FPGA_OffsetAdjValue;
				SendTXData(&tx_data);
				DataRedrawFlag |= PARA_CHANGE;
				return;
			}
		}
		break;
	case P_UTIL_SYSINFO:
		if(systemInfo_count<7)
			break;
		B_DispCT = DispScrCurrLoc;
		if((cnt<0)&&(DispScrEndCT<systemInfo_count-1)) {
			DispScrStartCT++;
			DispScrEndCT++;
			DispCT = DispScrCurrLoc = DispScrEndCT;
			DataRedrawFlag|= PARA_CHANGE+PARA_CHANGE_Fast;
		} else if((cnt>0)&&(DispScrStartCT>0)) {
			DispScrStartCT--;
			DispScrEndCT--;
			DispCT = DispScrCurrLoc = DispScrStartCT;
			DataRedrawFlag|= PARA_CHANGE+PARA_CHANGE_Fast;
		}
		break;
	case P_CONF_Para:
		if(DispMode == DispMode_BROWSE_ITEMS ) {
			B_DispCT = DispCT;
			DispCT = Scr_Cnt_Select(cnt, DispCT, P_Sync_MAX-1, 0);
			if(B_DispCT != DispCT)
				DataRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast;
		} else if(DispMode == DispMode_SET_PARAMETERS) {
			data = GetChanData(DispCT,0);
			if(DispCT==P_Sync_TrigOut)
				data = Cnt_Select_Slow(cnt, data, 1, 0);
			else if(DispCT==P_Sync_TrigIn)
				data = Cnt_Select_Slow(cnt, data, 1, 0);
			else if(DispCT==P_Sync_TrigInDelay)
				data = Cnt_Select_Slow(cnt, data, 10000, 0);
			else if(DispCT==P_Sync_TrigOutWidth)
				data = Cnt_Select_Slow(cnt, data, 10000, 5);
			SaveChanData(DispCT, data);
			DataRedrawFlag |= PARA_CHANGE;
		}
		break;
	case P_CONF_Ext:
		if(DispMode == DispMode_BROWSE_ITEMS ) {
			B_DispCT = DispCT;
#if NF_flag
			DispCT = Scr_Cnt_Select(cnt, DispCT, P_Ext_MAX-2, 0);
#else
			DispCT = Scr_Cnt_Select(cnt, DispCT, P_Ext_MAX-1, 0);
#endif
			if((P3k_Chan_Data.CONF.Ext_Setting.MultilPara)&&(DispCT==1)) {
				if(cnt<0)
					DispCT = 2;
				else
					DispCT = 0;
			}

			if(B_DispCT != DispCT)
				DataRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast;
		} else if(DispMode == DispMode_SET_PARAMETERS) {
			data = GetChanData(DispCT,0);
			if(DispCT==P_Ext_LoadON_IN) {
				data = Cnt_Select_Slow(cnt, data, 2, 0);
				Disp_tmp->CONF.Ext_Setting.LoadOn_IN = data;
			} else if(DispCT==P_Ext_Control) {
				data = Cnt_Select_Slow(cnt, data, 3, 0);
				Disp_tmp->CONF.Ext_Setting.Control = data;
			} else if(DispCT==P_Extmulti_para) {
				data = Cnt_Select_Slow(cnt, data, 2, 0);
				Disp_tmp->CONF.Ext_Setting.MultilPara = data;
			}
			DataRedrawFlag |= PARA_CHANGE;
		}
		break;
	case P_Test_Func:
		if(DispMode == DispMode_BROWSE_ITEMS ) {
			B_DispCT = DispCT;
			if(debugmode)
				DispCT = Scr_Cnt_Select(cnt, DispCT, 4, 0 );// 2
			else
				DispCT = Scr_Cnt_Select(cnt, DispCT, 3, 0 );// 2
			if(B_DispCT != DispCT)
				DataRedrawFlag |=PARA_CHANGE+PARA_CHANGE_Fast;
		} else if(DispMode == DispMode_SET_PARAMETERS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;

			if(DispCT==0)
				umax = 1;
			else if(DispCT==1)
				umax = 255;
			else if(DispCT==2)
				umax = 65535;
			else
				umax = 255;
			umin = 0;
			if(DispCT==0)
				P3K_CMD_R_W	= Cnt_Select_Step(cnt,P3K_CMD_R_W,umax,umin);
			else if(DispCT==1)
				P3K_CMD	= Cnt_Select_Step(cnt,P3K_CMD,umax,umin);
			else if(DispCT==2)
				P3K_DATA = Cnt_Select_Step(cnt,P3K_DATA,umax,umin);
			else if(DispCT==3) {
				RecordCMD = Cnt_Select_Step(cnt,RecordCMD,umax,umin);
#if debug_tool
				FPGASetting =FPGA_W[RecordCMD];
				FPGAStatus = FPGA_R[RecordCMD];
#endif
			}

			DataRedrawFlag |=PARA_CHANGE;
		}
		break;
	case P_Cal_Value:
		DispCT = Scr_Cnt_Select(cnt, DispCT, 10, 0);
		DataRedrawFlag |=PARA_CHANGE;

		break;
#if Enable_Func_select
	case P_FUNC_MAIN:
	case P_FUNC_MAIN_2:		
		if(DispMode_SELECT_CH==DispMode) {
			B_DispCT = DispCT;
			DispCT = Scr_Cnt_Select(cnt, DispCT, P_Func_M_Max - 1, 0);				
			if( B_DispCT != DispCT)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		} else if(DispMode==DispMode_BROWSE_ITEMS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			data = GetChanData(DispCT,0); ///P3k_Disp_Data.Load_Type;
			if(P_Func_M_start==DispCT) {				
#if Enable_LED_function
				max = CLED_Load;
#elif Enable_Battery_Discharge
				max = BATT_Load;
#else
				max = OCP_Load;
#endif

				min = Normal_Load;
			}else if(P_Func_M_comp==DispCT) {				
				max = 602;
				min = 1;
				data++;
			} else if(P_Func_M_count==DispCT){
				max = 1;
				min = 0;
			}					
			data1 = data;
			data = Cnt_Select_Step(cnt, data, max, min);	
			SaveChanData(DispCT, data);
			if(data1!=data) {
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;				
			}
		}
		break;			
	
#endif			
	case P_Seq_Normal:
		if(DispMode_SELECT_CH==DispMode) {
			B_DispCT = DispCT;
			DispCT = Scr_Cnt_Select(cnt, DispCT, P_NSeq_Max - 1, 0);
			if( B_DispCT != DispCT)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		} else if(DispMode==DispMode_BROWSE_ITEMS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			if( P_NSeq_Start==DispCT||P_NSeq_No==DispCT ) {
				max = 9;
				min = 0;
			} else if(P_NSeq_Mode==DispCT) {
				max = 3;
				min = 0;
			} else if(P_NSeq_Range==DispCT) {
				max = 3;
				min = 0;
				if(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode==CR_MODE){
					max = 2;
					min = 1;
				}				
			} else if(P_NSeq_Loop==DispCT) {
				max = 9999;
				min = 0;
			} else if(P_NSeq_Last_Load==DispCT) {
				max = 1;
				min = 0;
			} else if(P_NSeq_Last_Set==DispCT) {
				if(CC_MODE==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode) {
					max = (ptrMODEL_TYPE->CC)[0].Max;
					min = (ptrMODEL_TYPE->CC)[0].Min;
				} else if(CR_MODE==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode) {
					max = (ptrMODEL_TYPE->CR)[0].Max;
					min = (ptrMODEL_TYPE->CR)[0].Min;
				} else if(CV_MODE==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode) {
					max = (ptrMODEL_TYPE->CV)[0].Max;
					min = (ptrMODEL_TYPE->CV)[0].Min;
				} else { /*CP MODE*/
					max = (ptrMODEL_TYPE->CP)[0].Max;
					min = (ptrMODEL_TYPE->CP)[0].Min;
				}
			} else if(P_NSeq_Chain==DispCT) {
				max = 10;
				min = 0;
			} else
				break;
			data1 = data = GetChanData(DispCT,0);
			data = Cnt_Select_Step(cnt, data, max, min);		/* inc */
			SaveChanData(DispCT, data);
			if(data1!=data) {
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
				if(P_NSeq_Mode==DispCT) 	recall_default_parameter(DispCT);				
			}
		}
		break;
	case P_NSeq_Edit:
		if(0==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step)
			break;
		if(DispMode_SELECT_CH==DispMode) {
			B_DispCT = DispCT;
			DispCT = Scr_Cnt_Select(cnt, DispCT, P_NSeqEdit_Max - 1, 0);
			if( B_DispCT != DispCT)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		} else if(DispMode==DispMode_BROWSE_ITEMS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			if(P_NSeqEdit_Step==DispCT) {
				max = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step;
				min = 1;
			} else if(P_NSeqEdit_Value==DispCT) {
				if(CC_MODE==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode) {
					max = (ptrMODEL_TYPE->CC)[0].Max;
					min = (ptrMODEL_TYPE->CC)[0].Min;
				} else if(CR_MODE==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode) {
					max = (ptrMODEL_TYPE->CR)[0].Max;
					min = (ptrMODEL_TYPE->CR)[0].Min;
				} else if(CV_MODE==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode) {
					max = (ptrMODEL_TYPE->CV)[0].Max;
					min = (ptrMODEL_TYPE->CV)[0].Min;
				} else { /*CP MODE*/
					max = (ptrMODEL_TYPE->CP)[0].Max;
					min = (ptrMODEL_TYPE->CP)[0].Min;
				}
			} else if(P_NSeqEdit_Time_H==DispCT) {
				max = 999;
				min = 0;
			} else if(P_NSeqEdit_Time_M==DispCT) {
				max = 59;
				min = 0;
			} else if(P_NSeqEdit_Time_S==DispCT) {
				max = 59;
				min = 0;
			} else if(P_NSeqEdit_Time_mS==DispCT) {
#if Enable_NSEQ_Usec
				max = 19999;
#else
				max = 999;
#endif
				min = 0;
			} else {
				max = 1;
				min = 0;
			}
			data1 = data = GetChanData(DispCT,0);
			if(P_NSeqEdit_Step==DispCT)
				data = Cnt_Select_Slow(cnt, data, max, min);	/* inc */
			else
				data = Cnt_Select_Step(cnt, data, max, min);	/* inc */
			SaveChanData(DispCT, data);
			if(data1!=data)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		}
		break;
	case P_Seq_Fast:
		if(DispMode_SELECT_CH==DispMode) {
			B_DispCT = DispCT;
			DispCT = Scr_Cnt_Select(cnt, DispCT, P_FSeq_Max - 1, 0);
			if( B_DispCT != DispCT)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		}
#if 1
		else if(DispMode==DispMode_BROWSE_ITEMS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			if( (P_FSeq_Mode==DispCT)||(P_FSeq_Last_Load==DispCT) ) {
				max = 1;
				min = 0;
			} else if(P_FSeq_Range==DispCT) {
				max = 3;
				min = 0;
				if(P3k_FSeq_Disp.FSeq_Mode== CR_MODE){
					max = 2;
					min = 1;
				}
			} else if(P_FSeq_Loop==DispCT) {
				max = 9999;
				min = 0;
			} else if(P_FSeq_Last_Set==DispCT) {
				if(CC_MODE==P3k_FSeq_Disp.FSeq_Mode) {
					max = (ptrMODEL_TYPE->CC)[0].Max;
					min = (ptrMODEL_TYPE->CC)[0].Min;
				} else {	/*CR_MODE*/
					max = (ptrMODEL_TYPE->CR)[0].Max;
					min = (ptrMODEL_TYPE->CR)[0].Min;
				}
			} else if(P_FSeq_RptStep==DispCT) {
#if Enable_FSEQ_RPT
				max = P3k_FSeq_Disp.FSeq_Max_Step+1;
				min = 0;
#else			
				max = 999;
				min = 0;
#endif

			} else if(P_FSeq_TimeBase==DispCT) {
				Seq_max = 60001;
#if Enalbe_FSEQ_1US
				Seq_min = 1;
				range = P3k_FSeq_Disp.FSeq_TB_Range;
				Seq_Data = Cnt_Select_Step(cnt,P3k_FSeq_Disp.FSeq_Time_Base,60001,1);
#else
				Seq_min = 25;
				range = P3k_FSeq_Disp.FSeq_TB_Range;
				Seq_Data = Cnt_Select_Step(cnt,P3k_FSeq_Disp.FSeq_Time_Base,60001,25);
#endif
				if(Seq_Data==Seq_max) {
					if(range==0) {
						range = 1;
						Seq_Data = (Seq_Data/10)+1;
					} else
						Seq_Data=60000;
				} else if((Seq_Data==6000)&&(range==1)) {
					range = 0;
					Seq_Data = Seq_Data*10;
				}
				P3k_FSeq_Disp.FSeq_TB_Range	= range;
				P3k_FSeq_Disp.FSeq_Time_Base	= Seq_Data;
				DataRedrawFlag |= PARA_CHANGE;
				break;
			} else
				break;
			data1 = data = GetChanData(DispCT,0);
			data = Cnt_Select_Step(cnt, data, max, min);		/* inc */
			SaveChanData(DispCT, data);
			if(data1!=data) {
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
				if(P_FSeq_Mode==DispCT)recall_default_parameter(DispCT);				
			}
		}
#endif
		break;
	case P_FSeq_Edit:
		if(DispMode_SELECT_CH==DispMode) {
			B_DispCT = DispCT;
			DispCT = Scr_Cnt_Select(cnt, DispCT, P_FSeqEdit_Max - 1, 0);
			if( B_DispCT != DispCT)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		} else if(DispMode==DispMode_BROWSE_ITEMS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			if(P_FSeqEdit_Step==DispCT) {

				max = P3k_FSeq_Disp.FSeq_Max_Step;
				min = 0;
			} else if(P_FSeqEdit_Value==DispCT) {
				if(CC_MODE==P3k_FSeq_Disp.FSeq_Mode) {
					max = (ptrMODEL_TYPE->CC)[0].Max;
					min = (ptrMODEL_TYPE->CC)[0].Min;
				} else { /*CR MODE*/
					max = (ptrMODEL_TYPE->CR)[0].Max;
					min = (ptrMODEL_TYPE->CR)[0].Min;
				}
			} else {
				max = 1;
				min = 0;
			}
			data1 = data = GetChanData(DispCT,0);
			if(P_FSeqEdit_Step==DispCT)
				data = Cnt_Select_Slow(cnt, data, max, min);	/* inc */
			else
				data = Cnt_Select_Step(cnt, data, max, min);	/* inc */
			SaveChanData(DispCT, data);
			if(data1!=data)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		}
		break;
	case P_FSeq_Fill:
		if(DispMode_SELECT_CH==DispMode) {
			B_DispCT = DispCT;
			DispCT = Scr_Cnt_Select(cnt, DispCT, P_Fill_Max - 1, 0);
			if( B_DispCT != DispCT)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		} else if(DispMode==DispMode_BROWSE_ITEMS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			if( (P_Fill_Step_S==DispCT)||(P_Fill_Step_E==DispCT) ) {
				max = 999;
				min = 0;
			} else {
				if(CC_MODE==P3k_FSeq_Disp.FSeq_Mode) {
					max = (ptrMODEL_TYPE->CC)[0].Max;
					min = (ptrMODEL_TYPE->CC)[0].Min;
				} else { /*CR MODE*/
					max = (ptrMODEL_TYPE->CR)[0].Max;
					min = (ptrMODEL_TYPE->CR)[0].Min;
				}
			}
			data1 = data = GetChanData(DispCT,0);
			data = Cnt_Select_Step(cnt, data, max, min);	/* inc */
			SaveChanData(DispCT, data);
			if(data1!=data)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		}
		break;
#if Enable_OCP_function
	case P_FUNC_OCP:
		if(DispMode_SELECT_CH==DispMode) {
			B_DispCT = DispCT;
			DispCT = Scr_Cnt_Select(cnt, DispCT, P_F_OCP_Max- 1, 0);
			if( B_DispCT != DispCT)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		}
		else if(DispMode==DispMode_BROWSE_ITEMS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;

			if(DispCT==P_F_OCP_CurrTemp){
				max = 11;
				min = 0;		
			}else if(DispCT==P_F_OCP_Range){
				max = 1;
				min = 0;					
			} else if(DispCT==P_F_OCP_StartCurr){
				max = (ptrMODEL_TYPE->CC)[0].Max-1;
				min = (ptrMODEL_TYPE->CC)[0].Min;
			} else if(DispCT==P_F_OCP_EndCurr) {				
				max = (ptrMODEL_TYPE->CC)[0].Max;
				min = (ptrMODEL_TYPE->CC)[0].Min+2;
			} else if(DispCT==P_F_OCP_StepCurr) {
				max = (ptrMODEL_TYPE->CC)[0].Max/2;
				min = (ptrMODEL_TYPE->CC)[0].Min+1;
			} else if(DispCT==P_F_OCP_StepTime){
				max = 5000;
				min = 1;
			} else if(DispCT==P_F_OCP_TrigVolt) {
				max = (ptrMODEL_TYPE->CV)[3].Def;
				min = 1;
			} else if(DispCT==P_F_OCP_DelayTrig) {
				max = 500;
				data = GetChanData(P_F_OCP_StepTime,0);
				if(max>=data)max = data-1;
				min = 0;
			} else if(DispCT==P_F_OCP_LastCurr) {
				max = (ptrMODEL_TYPE->CC)[0].Max;
				min = (ptrMODEL_TYPE->CC)[0].Min;
			}

			data1 = data = GetChanData(DispCT,0);
			data = Cnt_Select_Step(cnt, data, max, min);		/* inc */
			SaveChanData(DispCT, data);
			if(data1!=data) {
				DataRedrawFlag |= PARA_CHANGE;
				if(DispCT==P_F_OCP_Range)recall_default_parameter(DispCT);	
			}
		}

		break;

#endif

#if Enable_OPP_function
	case P_FUNC_OPP:
		if(DispMode_SELECT_CH==DispMode) {
			B_DispCT = DispCT;
			DispCT = Scr_Cnt_Select(cnt, DispCT, P_F_OPP_Max- 1, 0);
			if( B_DispCT != DispCT)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		} else if(DispMode==DispMode_BROWSE_ITEMS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;

			if(DispCT==P_F_OPP_CurrTemp) {
				max = 11;
				min = 0;
			} else if(DispCT==P_F_OPP_Range) {
				max = 1;
				min = 0;
			} else if(DispCT==P_F_OPP_StartCurr) {
				max = (ptrMODEL_TYPE->CP)[0].Max-1;
				min = (ptrMODEL_TYPE->CP)[0].Min;
			} else if(DispCT==P_F_OPP_EndCurr) {
				max = (ptrMODEL_TYPE->CP)[0].Max;
				min = (ptrMODEL_TYPE->CP)[0].Min+2;
			} else if(DispCT==P_F_OPP_StepCurr) {
				max = (ptrMODEL_TYPE->CP)[0].Max/2;
				min = (ptrMODEL_TYPE->CP)[0].Min+1;
			} else if(DispCT==P_F_OPP_StepTime) {
				max = 5000;
				min = 1;
			} else if(DispCT==P_F_OPP_TrigVolt) {
				max = (ptrMODEL_TYPE->CV)[3].Max/21*20;
				min = 1;
			} else if(DispCT==P_F_OPP_DelayTrig) {
				max = 5000;
				data = GetChanData(P_F_OPP_StepTime,0);
				if(max>=data)max = data-1;
				min = 0;
			} else if(DispCT==P_F_OPP_LastCurr) {
				max = (ptrMODEL_TYPE->CP)[0].Max;
				min = (ptrMODEL_TYPE->CP)[0].Min;
			}

			data1 = data = GetChanData(DispCT,0);
			data = Cnt_Select_Step(cnt, data, max, min);		/* inc */
			SaveChanData(DispCT, data);
			if(data1!=data) {
				DataRedrawFlag |= PARA_CHANGE;
				if(DispCT==P_F_OPP_Range) recall_default_parameter(DispCT);	
			}
		}

		break;
#endif

#if Enable_Battery_Discharge
	case P_FUNC_batt:
		if(DispMode_BROWSE_ITEMS==DispMode) {
			B_DispCT = DispCT;
			tmp =DispScrCurrLoc;
			tmp = Scr_Cnt_Select(cnt, tmp, P_F_BATT_Max - 1, 0);
			DispScrCurrLoc = tmp;
			ScrollCnt_Select(tmp, P_F_BATT_Max, &DispScrStartCT, &DispScrEndCT, 4);
			DispCT = DispScrCurrLoc;
			if( B_DispCT != DispCT)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		} else if(DispMode==DispMode_SET_PARAMETERS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00; 
			if(DispCT==P_F_BATT_Mode) {
				max = 2;
				min = 0;	
				data1 = data = BattDisp.Mode;
				data = Cnt_Select_Step(cnt, data, max, min);	
				if(data != data1){
					BattDisp.Mode = data;
					recall_default_parameter(DispCT);
				}
			} else if(DispCT==P_F_BATT_Range) {
				max = Range_IHVH; 
				min = Range_ILVL;
				data1 = data = BattDisp.Range;
				data = Cnt_Select_Step(cnt, data, max, min);	
				if(data != data1){
					BattDisp.Range = data;
					recall_default_parameter(DispCT);
				} 
			} else if(DispCT==P_F_BATT_StopT) {
				if(BattDisp.timeCnt==0){//if(P3k_Chan_Data.CONF.Cut_Off_cnt==0) {
					max = 999;
					min = 0;
					BattDisp.StopHour = Cnt_Select_Step(cnt, BattDisp.StopHour, max, min);
				} else if(BattDisp.timeCnt==1) {
					max = 59;
					min = 0;
					BattDisp.StopMin= Cnt_Select_Step(cnt, BattDisp.StopMin, max, min);
				} else if(BattDisp.timeCnt==2) {
					max = 59;
					min = 0;
					BattDisp.StopSec= Cnt_Select_Step(cnt, BattDisp.StopSec, max, min);
				}
			} else if(DispCT==P_F_BATT_StopC) {
				//max = 50000;
				min = 0;
				BattDisp.StopCapa= Cnt_Select_Step(cnt, BattDisp.StopCapa, 999999, min);
			} else if(DispCT==P_F_BATT_StopV) {
				max = 15000;
				min = 1;
				BattDisp.StopValt= Cnt_Select_Step(cnt, BattDisp.StopValt, max, min);						
			} else {
				if(CC_MODE == BattDisp.Mode){
					if(DispCT==P_F_BATT_Set) {
						max = (ptrMODEL_TYPE->CC)[0].Max;
						min = (ptrMODEL_TYPE->CC)[0].Min;
						BattDisp.Setting = Cnt_Select_Step(cnt, BattDisp.Setting, max, min);
					} else if((DispCT==P_F_BATT_SRUP)||(DispCT==P_F_BATT_SRDW)) {
						max = (ptrMODEL_TYPE->CC)[2].Max;
						min = (ptrMODEL_TYPE->CC)[2].Min;
						if(DispCT==P_F_BATT_SRUP)
							get_sr_paramter(cnt, &BattDisp.SRUPRange,&BattDisp.SRUP, max,min);
						else
							get_sr_paramter(cnt, &BattDisp.SRDWRange,&BattDisp.SRDW, max,min);
					} 
				} else if(CR_MODE == BattDisp.Mode){
					if(DispCT==P_F_BATT_Set) {
						max = (ptrMODEL_TYPE->CR)[0].Max;
						min = (ptrMODEL_TYPE->CR)[0].Min;
						BattDisp.Setting= Cnt_Select_Step(cnt, BattDisp.Setting, max, min);
					} else if((DispCT==P_F_BATT_SRUP)||(DispCT==P_F_BATT_SRDW)){
						max = (ptrMODEL_TYPE->CR)[2].Max;
						min = (ptrMODEL_TYPE->CR)[2].Min;
						if(DispCT==P_F_BATT_SRUP)
							get_sr_paramter(cnt, &BattDisp.SRUPRange,&BattDisp.SRUP, max,min);
						else
							get_sr_paramter(cnt, &BattDisp.SRDWRange,&BattDisp.SRDW, max,min);
					}
				}else { //CP
					if(DispCT==P_F_BATT_Set) {
						max = (ptrMODEL_TYPE->CP)[0].Max;
						min = (ptrMODEL_TYPE->CP)[0].Min;
						BattDisp.Setting= Cnt_Select_Step(cnt, BattDisp.Setting, max, min);
					} 
				}
			}				
			DataRedrawFlag |= PARA_CHANGE;
		}	
		break;
		
#endif
#if Enable_LED_function
	case P_FUNC_FLED:
		if(DispMode_BROWSE_ITEMS==DispMode) {
			B_DispCT = DispCT;
			tmp =DispScrCurrLoc;
			tmp = Scr_Cnt_Select(cnt, tmp, P_F_LED_Max - 1, 0);
			DispScrCurrLoc = tmp;
			ScrollCnt_Select(tmp, P_F_LED_Max, &DispScrStartCT, &DispScrEndCT, 4);
			DispCT = DispScrCurrLoc;
			if( B_DispCT != DispCT)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		} else if(DispMode==DispMode_SET_PARAMETERS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			temp = P3k_FLed_Disp.currTemp;
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00; 
			if(DispCT==P_F_LED_No) {
				max = 11; 
				min = 0;	
				P3k_FLed_Disp.currTemp = Cnt_Select_Step(cnt, P3k_FLed_Disp.currTemp, max, min); 
			}else if(DispCT==P_F_LED_Range) {
				max = Range_IHVH; 
				min = Range_ILVL;
				data = data1 = P3k_FLed_Disp.seq[temp].range;
				data = Cnt_Select_Step(cnt, data, max, min);
				if(data != data1){
					P3k_FLed_Disp.seq[temp].range = data;
					recall_default_parameter(DispCT);
				}
			} else if(DispCT==P_F_LED_RESPONSE) {							
				max = RESPONSE_FAST;//(ptrMODEL_TYPE->CC)[2].Max;
				min = RESPONSE_SLOW;
				P3k_FLed_Disp.seq[temp].response= Cnt_Select_Step(cnt, P3k_FLed_Disp.seq[temp].response, max, min); 
				//get_sr_paramter(cnt, &P3k_FLed_Disp.Seq[0].SRRange,&P3k_FLed_Disp.Seq[0].SR, max,min);							
			} else if(DispCT==P_F_LED_PATAMTER){
				max = 4;
				min = 0;
				P3k_FLed_Disp.seq[temp].mode= Cnt_Select_Step(cnt, P3k_FLed_Disp.seq[temp].mode, max, min); 
			}
			DataRedrawFlag |= PARA_CHANGE;
		}	
		break;
	case P_FUNC_FLED_EDIT:
	case P_FUNC_FLED_EXECUTE:
		if(DispMode_BROWSE_ITEMS==DispMode) {
			B_DispCT = DispCT;
			tmp =DispScrCurrLoc;
			if(P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp].mode == 0)
				tmp = Scr_Cnt_Select(cnt, tmp, 1, 0);
			else
				tmp = Scr_Cnt_Select(cnt, tmp, 2, 0);
			DispScrCurrLoc = tmp;
			DispCT = DispScrCurrLoc;
			if( B_DispCT != DispCT)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;

		} else if(DispMode==DispMode_SET_PARAMETERS) {
			
			data = GetChanData(DispCT,0);						
			switch(P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp].mode){
				case P_F_LED_MODE_VoIo:
				case P_F_LED_MODE_VoIoRc:	
					if(DispCT==P_F_LED_Edit_P1){ //Vo
						max = (ptrMODEL_TYPE->CV)[0].Max;
						min = (ptrMODEL_TYPE->CV)[0].Min;		
					}else if(DispCT==P_F_LED_Edit_P2){//Io	
						max = (ptrMODEL_TYPE->CC)[0].Max;
						min = (ptrMODEL_TYPE->CC)[0].Min;	
					}else if(DispCT==P_F_LED_Edit_P3) {//Rcoff
						max = 10000;
						min = 1;				
					}
					break;					
				case P_F_LED_MODE_VoIoRd:
					if(DispCT==P_F_LED_Edit_P1){//Vo
						max = (ptrMODEL_TYPE->CV)[0].Max;
						min = (ptrMODEL_TYPE->CV)[0].Min;			
					}else if(DispCT==P_F_LED_Edit_P2){//Io	
						max = (ptrMODEL_TYPE->CC)[0].Max;
						min = (ptrMODEL_TYPE->CC)[0].Min;		
					}else if(DispCT==P_F_LED_Edit_P3) {//Rd
						max = (ptrMODEL_TYPE->CR)[0].Max;
						min = (ptrMODEL_TYPE->CR)[0].Min;	
					}
					break;
				case P_F_LED_MODE_VoIoVf:
					if(DispCT==P_F_LED_Edit_P1){//Vo
						max = (ptrMODEL_TYPE->CV)[0].Max;
						min = GetChanData(P_F_LED_Edit_P3,0)+1;			
					}else if(DispCT==P_F_LED_Edit_P2){//Io	
						max = (ptrMODEL_TYPE->CC)[0].Max;
						min = (ptrMODEL_TYPE->CC)[0].Min;	
					}else if(DispCT==P_F_LED_Edit_P3) {//Vf
						max = GetChanData(P_F_LED_Edit_P1,0)-1;//(ptrMODEL_TYPE->CV)[0].Max;
						min = (ptrMODEL_TYPE->CV)[0].Min;			
					}
					break;
				case P_F_LED_MODE_VfRdPcs:
					if(DispCT==P_F_LED_Edit_P1){ //Vf
						max = (ptrMODEL_TYPE->CV)[0].Max;
						min = (ptrMODEL_TYPE->CV)[0].Min;	 
					}else if(DispCT==P_F_LED_Edit_P2){//Rd	
						max = (ptrMODEL_TYPE->CC)[0].Max;
						min = (ptrMODEL_TYPE->CC)[0].Min;	 
					}else if(DispCT==P_F_LED_Edit_P3) {//pcs
						max = 1000;
						min = 1;	
					}
					break;
				default:
					break;	
			}								
			data = Cnt_Select_Step(cnt, data, max, min);	
			SaveChanData(DispCT, data);
			DataRedrawFlag |= PARA_CHANGE;
			if(UTILITY.LOAD_CTL)set_func_fled_ad();
		}
		break;
	case P_FUNC_CLED:
		if(DispMode_BROWSE_ITEMS==DispMode) {
			B_DispCT = DispCT;
			tmp =DispScrCurrLoc;
			tmp = Scr_Cnt_Select(cnt, tmp, P_CLED_Max - 1, 0);
			DispScrCurrLoc = tmp;
			ScrollCnt_Select(tmp, P_CLED_Max, &DispScrStartCT, &DispScrEndCT, 4);
			DispCT = DispScrCurrLoc;
			if( B_DispCT != DispCT)
				DataRedrawFlag |= PARA_CHANGE+PARA_CHANGE_Fast;
		} else if(DispMode==DispMode_SET_PARAMETERS) {
			KeyInFlag &= (~DIGI_KEY_IN);
			temp = P3k_CLed_Disp.currTemp;
			KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00; 
			if(DispCT==P_CLED_No) {
				max = 11; 
				min = 0;	
				P3k_CLed_Disp.currTemp = Cnt_Select_Step(cnt, P3k_CLed_Disp.currTemp, max, min); 
			}else if(DispCT==P_CLED_Range) {
				max = Range_IHVH; 
				min = Range_ILVL;
				data = data1 = P3k_CLed_Disp.seq[temp].range;
				data = Cnt_Select_Step(cnt, data, max, min);
				if(data != data1){
					P3k_CLed_Disp.seq[temp].range = data;
					recall_default_parameter(DispCT);
				}
			} else if(DispCT==P_CLED_RESPONSE) {							
				max = RESPONSE_FAST;//(ptrMODEL_TYPE->CC)[2].Max;
				min = RESPONSE_SLOW;
				P3k_CLed_Disp.seq[temp].response= Cnt_Select_Step(cnt, P3k_CLed_Disp.seq[temp].response, max, min); 
				//get_sr_paramter(cnt, &P3k_FLed_Disp.Seq[0].SRRange,&P3k_FLed_Disp.Seq[0].SR, max,min);							
			} else if(DispCT==P_CLED_VO){
				max = (ptrMODEL_TYPE->CV)[0].Max;
				min = (ptrMODEL_TYPE->CV)[0].Min;
				P3k_CLed_Disp.seq[temp].vo= Cnt_Select_Step(cnt, P3k_CLed_Disp.seq[temp].vo, max, min); 
				find_curve_led_paramter(P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].rdcoff);				
			} else if(DispCT==P_CLED_IO){
				max = (ptrMODEL_TYPE->CC)[0].Max;
				min = (ptrMODEL_TYPE->CC)[0].Min;
				P3k_CLed_Disp.seq[temp].io= Cnt_Select_Step(cnt, P3k_CLed_Disp.seq[temp].io, max, min); 
				find_curve_led_paramter(P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].rdcoff);				
			}
			DataRedrawFlag |= PARA_CHANGE;
		}	
		break;
	case P_FUNC_CLED_EDIT:
		if(DispMode_BROWSE_ITEMS==DispMode) {			

		} else if(DispMode==DispMode_SET_PARAMETERS) {			
			data = GetChanData(DispCT,0);			
			max = 7000;
			min = 1000;							
			data = Cnt_Select_Step(cnt, data, max, min);	
			SaveChanData(DispCT, data);

			find_curve_led_paramter(data);		

			DataRedrawFlag |= PARA_CHANGE;
		}
		break;	
#endif

	default:
		break;
	}
}

#if Enable_Battery_Discharge

void get_sr_paramter(char cnt_STEP, UBYTE* Range, UWORD* value, UWORD max,UWORD min){
	char irange = BattDisp.Range%2;
	UWORD max_value;	
	max_value = max /Get_Parallel_Parameter(irange);
	*value = Cnt_Select_Step(cnt_STEP, *value , max_value, min);
}
#endif


long InputToStep(double input,double resolution)
{
	long step;
	step = (input*100000.1)/(resolution*100000.0);
	//step = (long)((input/resolution)+(double)0.0000005);
	return step;
}

void Rem_Sel_Cal_Point(UBYTE Cal_POINT)
{
	p3k_send_tx_list tx_data;

	P3K_CALIBRATION_BAR.POINT = Cal_POINT;
	P3K_CALIBRATION_BAR.Volt_Curr_Sel = Select_Volt;
	/* Load  Calibration Default  & Calibration Start*/

	tx_data.ADDRH = Cal_FPGA_Command;
	tx_data.ADDRL = Cal_FPGA_Load_Cal_Default;
	SendTXData(&tx_data);

	/* Cal Start : Send Load On Command */
	tx_data.ADDRH = Cal_FPGA_Command;
	tx_data.ADDRL = Cal_FPGA_Start;
	SendTXData(&tx_data);
#if 1 //2015.0511 
	tx_data.ADDRH = Cal_FPGA_Command;
	tx_data.ADDRL = Cal_FPGA_OffsetAdjValue;
	SendTXData(&tx_data);
#endif	
}

UBYTE Rem_Input_Cal_Data(double Rem_Cal_Data,UBYTE Rem_Cal_Point)
{
	char val;
	double cal_max,cal_min;
	UBYTE mode,rang;
	mode = P3K_CALIBRATION_BAR.MODE;
	rang = P3K_CALIBRATION_BAR.RANGE;
	
	val = mode +(rang*MODE_Number);

	if((mode==CR_MODE)||(mode==CP_MODE)||(mode==R_IMON_MODE)) {
		if(Select_Volt==P3K_CALIBRATION_BAR.Volt_Curr_Sel){
			if(mode == CR_MODE){
				if(DispCT)	cal_max = ((double)ptrMODEL_TYPE->CALI_LP[(rang*MODE_Number)+1].Def) * ptrMODEL_TYPE->CALI_LP[(rang*MODE_Number)+1].Resolution;
				else		cal_max = ((double)ptrMODEL_TYPE->CALI_HP[(rang*MODE_Number)+1].Def) * ptrMODEL_TYPE->CALI_HP[(rang*MODE_Number)+1].Resolution;
			}else if(mode == CP_MODE){
				if(DispCT)	cal_max = ((double)ptrMODEL_TYPE->CALI_LP[(rang*MODE_Number)+3].Def) * ptrMODEL_TYPE->CALI_LP[(rang*MODE_Number)+3].Resolution;
				else		cal_max = ((double)ptrMODEL_TYPE->CALI_HP[(rang*MODE_Number)+3].Def) * ptrMODEL_TYPE->CALI_HP[(rang*MODE_Number)+3].Resolution;
			}else{
				cal_max = ((double)ptrMODEL_TYPE->CALI_HP[val].Def) * ptrMODEL_TYPE->CALI_HP[val].Resolution;
			}
		}else {
			if(mode == CR_MODE){
				if(DispCT) 	cal_max = ((double)ptrMODEL_TYPE->CALI_LP[rang*MODE_Number].Def) * ptrMODEL_TYPE->CALI_LP[rang*MODE_Number].Resolution;
				else		cal_max = ((double)ptrMODEL_TYPE->CALI_HP[rang*MODE_Number].Def) * ptrMODEL_TYPE->CALI_HP[rang*MODE_Number].Resolution;
			}else if(mode == CP_MODE){
				if(DispCT)	cal_max = ((double)ptrMODEL_TYPE->CALI_LP[rang*MODE_Number].Min) * ptrMODEL_TYPE->CALI_LP[rang*MODE_Number].Resolution;
				else		cal_max = ((double)ptrMODEL_TYPE->CALI_HP[rang*MODE_Number].Min) * ptrMODEL_TYPE->CALI_HP[rang*MODE_Number].Resolution;
			}else{
				cal_max = ((double)ptrMODEL_TYPE->CALI_HP[rang*MODE_Number].Max) * ptrMODEL_TYPE->CALI_HP[rang*MODE_Number].Resolution;
			}
		}
	} else{
		if(DispCT)	cal_max = ((double)ptrMODEL_TYPE->CALI_LP[val].Def)*ptrMODEL_TYPE->CALI_LP[val].Resolution;
		else		cal_max = ((double)ptrMODEL_TYPE->CALI_HP[val].Def)*ptrMODEL_TYPE->CALI_HP[val].Resolution;
	}


#if 1
	if((mode==CP_MODE)&&(rang==0))
		cal_min = cal_max*0.2;
	else
		cal_min = cal_max*0.8;
	cal_max = cal_max*1.15;
	if((Rem_Cal_Data>cal_max)||(Rem_Cal_Data<cal_min)){
		return M_Out_Of_Range;
	}
#endif


	if( (mode==CR_MODE)||(mode==CP_MODE)||(mode==F_IMON_MODE)||(mode==R_IMON_MODE)) {
		if(Cal_High_Point==Rem_Cal_Point) {
			if(Select_Volt==P3K_CALIBRATION_BAR.Volt_Curr_Sel)
				P3K_CALIBRATION_BAR.HP_Volt = Rem_Cal_Data;
			else if(Select_Curr==P3K_CALIBRATION_BAR.Volt_Curr_Sel) {
				P3K_CALIBRATION_BAR.HP_Curr = Rem_Cal_Data;
				CAL_HI_LOW_SET_OK |= 0x01;
			}
		} else if(Cal_Low_Point==Rem_Cal_Point) {
			if(Select_Volt==P3K_CALIBRATION_BAR.Volt_Curr_Sel)
				P3K_CALIBRATION_BAR.LP_Volt = Rem_Cal_Data;
			else if(Select_Curr==P3K_CALIBRATION_BAR.Volt_Curr_Sel) {
				P3K_CALIBRATION_BAR.LP_Curr = Rem_Cal_Data;
				CAL_HI_LOW_SET_OK |= 0x02;
			}
		}
	} else {
		if(Cal_High_Point==Rem_Cal_Point) {
			P3K_CALIBRATION_BAR.HP_Volt = Rem_Cal_Data;
			CAL_HI_LOW_SET_OK |= 0x01;
		} else if(Cal_Low_Point==Rem_Cal_Point) {
			P3K_CALIBRATION_BAR.LP_Volt = Rem_Cal_Data;
			CAL_HI_LOW_SET_OK |= 0x02;
		}
	}
	return M_Success;
}

unsigned short DynaPercentOrDutySetting(double KeyinBuf)
{
	unsigned short Percent_Max_Count,Percent_Min_Count,Keyin_Value_Count;

	Keyin_Value_Count = InputToStep(KeyinBuf,0.1);
	Percent_Max_Count = 1000;
	Percent_Min_Count = 0;

	if(Keyin_Value_Count >= Percent_Max_Count)
		Keyin_Value_Count = Percent_Max_Count;
	else if(Keyin_Value_Count <= Percent_Min_Count)
		Keyin_Value_Count = Percent_Min_Count;

	return Keyin_Value_Count;
}

void VarKnobEnterProcess(BYTE cnt)
{
	UBYTE tmp;
	UWORD h_old,l_old,umax,h_new,l_new,Old_Value;
	long cnt1,cnt2,SR_Max;
	unsigned char cnt_1;
	UWORD i,j,k,data,cnt_STEP;
	double fdat,fdat1,fcnt,resolution,cal_max,cal_min;
	double Cnt_tmp;
	char type,range1,val;
	ULONG SPROT0_CMD,SPROT0_DATA;
	UBYTE err,*Range_Point,*F_Range_Point,Seq_Mode_Temp;
	long umin;
	UWORD F_Max,F_Min;
	unsigned short dutyMax,dutyMin;
	float para_s;
	//static UBYTE RECODE_Para_num;
#if Enable_OCP_function
	double CurrRes ;
	UBYTE CurrPre ;
	double VoltRes ;
	UBYTE VoltPre ;
	double TimeRes ;
	UBYTE TimePre ;
#endif		

	p3k_send_tx_list tx_data;

	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Prog_Str	*Prog_tmp = &p3k_Disp_PROG;
#if Enable_OCP_function	
	F_OCP_OPP_Str *OCP = &P3K_OCP_Disp.Seq[P3K_OCP_Disp.CurrTemp];
#endif
#if Enable_OPP_function
	F_OCP_OPP_Str *OPP = &P3K_OPP_Disp.Seq[P3K_OPP_Disp.CurrTemp];
#endif

	UBYTE V_Range = Disp_tmp->VRange;
	UBYTE I_Range = Disp_tmp->IRange;

	switch(M_num) {
	case P_CC:

		DispMode++;
		if(DispMode > DispMode_SET_PARAMETERS) {
			DispMode = DispMode_BROWSE_ITEMS;	/* Back to Browers */
			if( KeyInFlag & DIGI_KEY_IN) {

				KeyInFlag &= ~DIGI_KEY_IN;
				if( ((DispScrCurrLoc==CCCR_Dyn_Add_CV)&&(Disp_tmp->CC.STADYNA==Function_Dynamic))||((DispScrCurrLoc==CCCR_Sta_Add_CV)&&(Disp_tmp->CC.STADYNA==Function_Static)) ) {
					cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CV)[V_Range*3].Resolution);
					umax = (ptrMODEL_TYPE->CV)[V_Range*3].Max;
					umin = (ptrMODEL_TYPE->CV)[V_Range*3].Min;
				} else {
					switch(DispScrCurrLoc) {
					case CCCR_Dyn_L1:
					case CCCR_Dyn_L2:
						if((DispScrCurrLoc == CCCR_Dyn_L2) && (Disp_tmp->CONF.Dyna_Level) && (Disp_tmp->CC.STADYNA==Function_Dynamic))
							cnt1 = DynaPercentOrDutySetting(atof(KeyinBuf));
						else {
							cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CC)[DispScrCurrLoc+(I_Range*10)+(Disp_tmp->CC.STADYNA)*4].Resolution);
							cnt1 /= Get_Parallel_Parameter(I_Range);
						}

						Range_Point = &I_Range;
						break;
					case CCCR_Dyn_SRUP:
					case CCCR_Dyn_SRDN:

						cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CC)[DispScrCurrLoc+(I_Range*10)+(Disp_tmp->CC.STADYNA)*4].Resolution);
						SR_Max = ((ptrMODEL_TYPE->CC)[DispScrCurrLoc+(I_Range*10)+(Disp_tmp->CC.STADYNA)*4].Max)*100;
						if(cnt1>SR_Max)
							cnt1 = SR_Max;

						//cnt1 = (cnt1/Get_Parallel_Parameter(Disp_tmp->IRange))+1;
						cnt1 = (cnt1/Get_Parallel_Parameter(Disp_tmp->IRange));

						Range_Point = &I_Range;
						break;
					case CCCR_Dyn_T1:
					case CCCR_Dyn_T2:
						if(Disp_tmp->CONF.Dyna_Time) {
							if(DispScrCurrLoc==CCCR_Dyn_T1) {
								F_Range_Point = &Disp_tmp->CC.DYNA[I_Range].Frequency_Range;
								*F_Range_Point = Dyn_Freq_TimeBase_100mHz;
							}
						} else {
							if(DispScrCurrLoc==CCCR_Dyn_T1)
								Range_Point = &Disp_tmp->CC.DYNA[I_Range].T1_RANGE;
							else
								Range_Point = &Disp_tmp->CC.DYNA[I_Range].T2_RANGE;

							*Range_Point = Dyn_TimeBase_1us;
						}

						if((DispScrCurrLoc == CCCR_Dyn_T2) && (Disp_tmp->CONF.Dyna_Time) && (Disp_tmp->CC.STADYNA==Function_Dynamic)) {
							cnt1 = DynaPercentOrDutySetting(atof(KeyinBuf));
							dutyMin = get_DynaFreqDutyRangeLimit(P_CC);
							dutyMax = 1000 - dutyMin;
							if(cnt1<dutyMin)cnt1=dutyMin;
							else if(cnt1>dutyMax)cnt1=dutyMax;
						} else {
							if(Disp_tmp->CONF.Dyna_Time) {
								if(*F_Range_Point == Dyn_Freq_TimeBase_100mHz) {
									cnt1 = InputToStep(atof(KeyinBuf),0.1);
									if(cnt1 > 100) {
										*F_Range_Point = Dyn_Freq_TimeBase_1Hz;
										cnt1 = cnt1 / 10;
									}
								}

								if(*F_Range_Point == Dyn_Freq_TimeBase_1Hz) {
									cnt1 = InputToStep(atof(KeyinBuf),1);
									if(cnt1 > 100) {
										*F_Range_Point = Dyn_Freq_TimeBase_10Hz;
										cnt1 = cnt1 / 10;
									}
								}

								if(*F_Range_Point == Dyn_Freq_TimeBase_10Hz) {
									cnt1 = InputToStep(atof(KeyinBuf),10);
									if(cnt1 > 100) {
										*F_Range_Point = Dyn_Freq_TimeBase_100Hz;
										cnt1 = cnt1 / 10;
									}
								}

								if(*F_Range_Point == Dyn_Freq_TimeBase_100Hz) {
									cnt1 = InputToStep(atof(KeyinBuf),100);
									if(cnt1 > 200)
										*F_Range_Point = Dyn_Freq_TimeBase_100Hz;
								}

								if(*F_Range_Point == Dyn_Freq_TimeBase_100Hz)
									F_Max = 200;
								else
									F_Max = 100;
								F_Min = 10;
							} else {
								cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CC)[DispScrCurrLoc+(0)*10+(Disp_tmp->CC.STADYNA)*4].Resolution);
								if(cnt1 >= (ptrMODEL_TYPE->CC)[DispScrCurrLoc+(0)*10+(Disp_tmp->CC.STADYNA)*4].Max/2) {
									*Range_Point = Dyn_TimeBase_1ms;
									cnt1 = cnt1 / 1000;
								}
							}
						}
						break;
					default:
						break;
					}

					//if(((((DispScrCurrLoc == CCCR_Dyn_SRUP) || (DispScrCurrLoc == CCCR_Dyn_SRDN)) && (Disp_tmp->CC.STADYNA==Function_Dynamic)) || ((DispScrCurrLoc == CCCR_Sta_SR) && (Disp_tmp->CC.STADYNA==Function_Static))) && (P3k_Chan_Data.INFO.MACHTYPE == MODEL3111)) {
					//	umax = (ptrMODEL_TYPE->CC)[DispScrCurrLoc + (*Range_Point) * 10 + (Disp_tmp->CC.STADYNA)*4].Max ;
					//	umin = (ptrMODEL_TYPE->CC)[DispScrCurrLoc + (*Range_Point) * 10 + (Disp_tmp->CC.STADYNA)*4].Min + 1;
					//} else {
						umax = (ptrMODEL_TYPE->CC)[DispScrCurrLoc+(*Range_Point)*10+(Disp_tmp->CC.STADYNA)*4].Max;
						///if(*Range_Point == Dyn_TimeBase_1ms)
						///	umin = 29;
						///else
							umin = (ptrMODEL_TYPE->CC)[DispScrCurrLoc+(*Range_Point)*10+(Disp_tmp->CC.STADYNA)*4].Min;
					//}
				}

				if(((DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CONF.Dyna_Time)) && (Disp_tmp->CC.STADYNA == Function_Dynamic)) {
					if(cnt1 > F_Max)
						cnt1 = F_Max;

					if(cnt1 < F_Min)
						cnt1 = F_Min;
					SaveChanData(DispScrCurrLoc,cnt1);
				} else if((((DispScrCurrLoc == CCCR_Dyn_L2) && (Disp_tmp->CONF.Dyna_Level)) || ((DispScrCurrLoc == CCCR_Dyn_T2) && (Disp_tmp->CONF.Dyna_Time))) && (Disp_tmp->CC.STADYNA==Function_Dynamic))
					SaveChanData(DispScrCurrLoc,cnt1);
				else {
					if(cnt1 > umax)
						cnt1 = umax;

					if(cnt1 < umin)
						cnt1 = umin;
					SaveChanData(DispScrCurrLoc,cnt1);
				}
//printf("cnt2:%d\n",cnt1);				

				KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			} else {
				if( (0==Disp_tmp->UTILITY.B_ONOFF)&&(Disp_tmp->CC.STADYNA==Function_Static) ) {
					if(DispScrCurrLoc<=CCCR_Sta_B_VALUE)
						Disp_tmp->CC.ABSELECT = DispScrCurrLoc;
				}
			}
			B_DispCT = DispScrCurrLoc;

			if(((DispScrCurrLoc==CCCR_Dyn_Add_CV)&&(Disp_tmp->CC.STADYNA==Function_Dynamic))||((DispScrCurrLoc==CCCR_Sta_Add_CV)&&(Disp_tmp->CC.STADYNA==Function_Static))) {
				Data_tmp->CV.STA[V_Range].VALUE1 = Disp_tmp->CV.STA[V_Range].VALUE1;
				MenuRedrawFlag|=MENU1_CHANGE;
			} else
				Data_tmp->CC = Disp_tmp->CC;

			MenuDecoderAddr(&tx_data);
			SendTXData(&tx_data);
			if( (DispCT<=CCCR_Sta_B_VALUE)&&(Disp_tmp->CC.STADYNA==Function_Static)&&(0==Disp_tmp->UTILITY.B_ONOFF) ) {
				tx_data.ADDRH = 0x01;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				ChanRedrawFlag|= CHAN_STATUS;
			}
#if Enable_Optim_display
			DataRedrawFlag |= BG_CLEAR_FLAG;
#endif			
		}
		DataRedrawFlag|= PARA_CHANGE;
		break;
	case P_CR:
		DispMode++;
		if(DispMode > DispMode_SET_PARAMETERS) {
			Compensation_Flag = 0;
			Compensation_Count = 0;
			Error_Amount_Flag = 0;

			DispMode = DispMode_BROWSE_ITEMS;	/* Back to Browers */
			if( KeyInFlag & DIGI_KEY_IN) {
				KeyInFlag &= ~DIGI_KEY_IN;
				if(((DispScrCurrLoc==CCCR_Dyn_Add_CV)&&(Disp_tmp->CR.STADYNA==Function_Dynamic))||((DispScrCurrLoc==CCCR_Sta_Add_CV)&&(Disp_tmp->CR.STADYNA==Function_Static))) {
					cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CV)[V_Range*3].Resolution);
					umax = (ptrMODEL_TYPE->CV)[V_Range*3].Max;
					umin = (ptrMODEL_TYPE->CV)[V_Range*3].Min;
				} else {
					switch(DispScrCurrLoc) {
					case CCCR_Dyn_L1:
					case CCCR_Dyn_L2:
						if(Data_tmp->CONF.D_CR_Unit) {
							if((DispScrCurrLoc == CCCR_Dyn_L2) && (Disp_tmp->CONF.Dyna_Level) && (Disp_tmp->CR.STADYNA==Function_Dynamic))
								cnt1 = cnt2 = DynaPercentOrDutySetting(atof(KeyinBuf));
							else {
								cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CR)[DispScrCurrLoc+(I_Range*10)+(Disp_tmp->CR.STADYNA)*4].Resolution);
								cnt1 /= Get_Parallel_Parameter(I_Range);
							}
						} else {
							if((DispScrCurrLoc == CCCR_Dyn_L2) && (Disp_tmp->CONF.Dyna_Level) && (Disp_tmp->CR.STADYNA==Function_Dynamic))
								cnt1 = cnt2 = DynaPercentOrDutySetting(atof(KeyinBuf));
							else {
								if(atof(KeyinBuf)>0.0)
									cnt1 = InputToStep((1000.0/atof(KeyinBuf)),(ptrMODEL_TYPE->CR)[DispScrCurrLoc+(I_Range*10)+(Disp_tmp->CR.STADYNA)*4].Resolution);
								else
									cnt1 = 9999999;
								cnt1 /= Get_Parallel_Parameter(I_Range);
							}
						}
						Range_Point = &I_Range;
						break;
					case CCCR_Dyn_SRUP:
					case CCCR_Dyn_SRDN:

						cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CR)[DispScrCurrLoc+(I_Range*10)+(Disp_tmp->CR.STADYNA)*4].Resolution);
						//SR_Max = ((ptrMODEL_TYPE->CR)[DispScrCurrLoc+(I_Range*10)+(Disp_tmp->Cr.STADYNA)*4].Max)*100;
						SR_Max = ((ptrMODEL_TYPE->CR)[DispScrCurrLoc+(I_Range*10)+(Disp_tmp->CR.STADYNA)*4].Max)*100;
						if(cnt1>SR_Max)
							cnt1 = SR_Max;

						cnt1 = (cnt1/Get_Parallel_Parameter(Disp_tmp->IRange));
						Range_Point = &I_Range;
						break;
					case CCCR_Dyn_T1:
					case CCCR_Dyn_T2:
						if(Disp_tmp->CONF.Dyna_Time) {
							if(DispScrCurrLoc==CCCR_Dyn_T1) {
								F_Range_Point = &Disp_tmp->CR.DYNA[I_Range].Frequency_Range;
								*F_Range_Point = Dyn_Freq_TimeBase_100mHz;

							}
						} else {
							if(DispScrCurrLoc==CCCR_Dyn_T1)
								Range_Point = &Disp_tmp->CR.DYNA[I_Range].T1_RANGE;
							else
								Range_Point = &Disp_tmp->CR.DYNA[I_Range].T2_RANGE;

							*Range_Point = Dyn_TimeBase_1us;
						}

						if((DispScrCurrLoc == CCCR_Dyn_T2) && (Disp_tmp->CONF.Dyna_Time) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) {
							cnt1 = DynaPercentOrDutySetting(atof(KeyinBuf));
							dutyMin = get_DynaFreqDutyRangeLimit(P_CR);
							dutyMax = 1000 - dutyMin;
							if(cnt1<dutyMin)cnt1=dutyMin;
							else if(cnt1>dutyMax)cnt1=dutyMax;
						} else {
							if(Disp_tmp->CONF.Dyna_Time) {
								if(*F_Range_Point == Dyn_Freq_TimeBase_100mHz) {
									cnt1 = InputToStep(atof(KeyinBuf),0.1);
									if(cnt1 > 100) {
										*F_Range_Point = Dyn_Freq_TimeBase_1Hz;
										cnt1 = cnt1 / 10;
									}
								}
								if(*F_Range_Point == Dyn_Freq_TimeBase_1Hz) {
									cnt1 = InputToStep(atof(KeyinBuf),1);
									if(cnt1 > 100) {
										*F_Range_Point = Dyn_Freq_TimeBase_10Hz;
										cnt1 = cnt1 / 10;
									}
								}
								if(*F_Range_Point == Dyn_Freq_TimeBase_10Hz) {
									cnt1 = InputToStep(atof(KeyinBuf),10);
									if(cnt1 > 100) {
										*F_Range_Point = Dyn_Freq_TimeBase_100Hz;
										cnt1 = cnt1 / 10;
									}
								}
								if(*F_Range_Point == Dyn_Freq_TimeBase_100Hz) {
									cnt1 = InputToStep(atof(KeyinBuf),100);
									if(cnt1 > 200)
										*F_Range_Point = Dyn_Freq_TimeBase_100Hz;
								}

								if(*F_Range_Point == Dyn_Freq_TimeBase_100Hz)
									F_Max = 200;
								else
									F_Max = 100;
								F_Min = 10;
							} else {
								cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CR)[DispScrCurrLoc+(0)*10+(Disp_tmp->CR.STADYNA)*4].Resolution);
								if(cnt1 >= (ptrMODEL_TYPE->CR)[DispScrCurrLoc+(0)*10+(Disp_tmp->CR.STADYNA)*4].Max/2) {
									*Range_Point = Dyn_TimeBase_1ms;
									cnt1 = cnt1 / 1000;
								}
							}
						}
						break;
					default:
						break;
					}
					//if(((((DispScrCurrLoc == CCCR_Dyn_SRUP) || (DispScrCurrLoc == CCCR_Dyn_SRDN)) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) || ((DispScrCurrLoc == CCCR_Sta_SR) && (Disp_tmp->CR.STADYNA==Function_Static))) && (P3k_Chan_Data.INFO.MACHTYPE == MODEL3111)) {
					//	umax = (ptrMODEL_TYPE->CR)[DispScrCurrLoc + (*Range_Point) * 10 + (Disp_tmp->CR.STADYNA)*4].Max ;
					//	umin = (ptrMODEL_TYPE->CR)[DispScrCurrLoc + (*Range_Point) * 10 + (Disp_tmp->CR.STADYNA)*4].Min + 1;
					//} else {
						umax = (ptrMODEL_TYPE->CR)[DispScrCurrLoc+(*Range_Point)*10+(Disp_tmp->CR.STADYNA)*4].Max;
						///if(*Range_Point == Dyn_TimeBase_1ms)
						///	umin = 29;
						///else
						umin = (ptrMODEL_TYPE->CR)[DispScrCurrLoc+(*Range_Point)*10+(Disp_tmp->CR.STADYNA)*4].Min;
					//}
				}

				if(((DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CONF.Dyna_Time)) && (Disp_tmp->CR.STADYNA == Function_Dynamic)) {
					if(cnt1 > F_Max)
						cnt1 = F_Max;

					if(cnt1 < F_Min)
						cnt1 = F_Min;
					SaveChanData(DispScrCurrLoc,cnt1);
				} else if((((DispScrCurrLoc == CCCR_Dyn_L2) && (Disp_tmp->CONF.Dyna_Level)) || ((DispScrCurrLoc == CCCR_Dyn_T2) && (Disp_tmp->CONF.Dyna_Time))) && (Disp_tmp->CR.STADYNA==Function_Dynamic))
					SaveChanData(DispScrCurrLoc,cnt1);
				else {
					if(cnt1 > umax)
						cnt1 = umax;

					if(cnt1 < umin)
						cnt1 = umin;
					SaveChanData(DispScrCurrLoc,cnt1);
				}

				KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
				/* Get KeyinBuf Value to check the value is not over default value */
				/* If OK, save data to Real Channel struct */
			} else {
				if(Disp_tmp->CR.STADYNA==Function_Static) {
					if((!Disp_tmp->UTILITY.B_ONOFF)&&(DispScrCurrLoc<=CCCR_Sta_B_VALUE))
						Disp_tmp->CR.ABSELECT = DispScrCurrLoc;
				}
			}
			B_DispCT = DispScrCurrLoc;
			if(((DispScrCurrLoc==CCCR_Dyn_Add_CV)&&(Disp_tmp->CR.STADYNA==Function_Dynamic))||((DispScrCurrLoc==CCCR_Sta_Add_CV)&&(Disp_tmp->CR.STADYNA==Function_Static))) {
				Data_tmp->CV.STA[V_Range].VALUE1 = Disp_tmp->CV.STA[V_Range].VALUE1;
				MenuRedrawFlag|=MENU1_CHANGE;
			} else
				Data_tmp->CR = Disp_tmp->CR;

			MenuDecoderAddr(&tx_data);
			SendTXData(&tx_data);
			if((DispScrCurrLoc<=CCCR_Sta_B_VALUE)&&(Disp_tmp->CR.STADYNA==Function_Static)&&(!Disp_tmp->UTILITY.B_ONOFF)) {
				tx_data.ADDRH = 0x02;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				ChanRedrawFlag|= CHAN_STATUS;
			}
#if Enable_Optim_display
			DataRedrawFlag |= BG_CLEAR_FLAG;
#endif			
		}
		DataRedrawFlag|= PARA_CHANGE;
		break;
	case P_CV:
		DispMode++;
		if(DispMode > DispMode_SET_PARAMETERS) {
			DispMode = DispMode_BROWSE_ITEMS;	/* Back to Browers */
			if( KeyInFlag & DIGI_KEY_IN) {
				KeyInFlag &= ~DIGI_KEY_IN;
				cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CV)[DispCT+(V_Range*3)].Resolution);
				umax = (ptrMODEL_TYPE->CV)[V_Range*3].Max;
				umin = (ptrMODEL_TYPE->CV)[V_Range*3].Min;
				if(cnt1>umax)
					cnt1 = umax;
				else if(cnt1<umin)
					cnt1 = umin;
				SaveChanData( DispCT, cnt1);
				KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			} else {
				if(Disp_tmp->CV.STADYNA==Function_Static) {
					if(DispCT<=CV_B_VALUE)
						Disp_tmp->CV.ABSELECT = DispCT;
				}
			}
			B_DispCT = DispCT;
			Data_tmp->CV = Disp_tmp->CV;
			MenuDecoderAddr(&tx_data);
			SendTXData(&tx_data);
#if 1
			if((DispCT<=CV_B_VALUE)&&(Disp_tmp->CV.STADYNA==Function_Static)&&(!Disp_tmp->UTILITY.B_ONOFF)) {
				tx_data.ADDRH = 0x03;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				ChanRedrawFlag|= CHAN_STATUS;
			}
#endif
#if Enable_Optim_display
			DataRedrawFlag |= BG_CLEAR_FLAG;
#endif

		}
		DataRedrawFlag|= PARA_CHANGE;
		if((DispMode == DispMode_SET_PARAMETERS)&&(Disp_tmp->CONF.Ext_Setting.Control)&&(M_num==P_CV))
			DataRedrawFlag |= BG_CLEAR_FLAG;
		break;
	case P_CP:
		DispMode++;
		if(DispMode > DispMode_SET_PARAMETERS) {
			Compensation_Flag = 0;
			Compensation_Count = 0;
			Error_Amount_Flag = 0;
			DispMode = DispMode_BROWSE_ITEMS;	/* Back to Browers */

			if( KeyInFlag & DIGI_KEY_IN) {
				KeyInFlag &= ~DIGI_KEY_IN;

				if(DispScrCurrLoc==CP_Sta_Add_CV) {
					cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CV)[V_Range*3].Resolution);
					umax = (ptrMODEL_TYPE->CV)[V_Range*3].Max;
					umin = (ptrMODEL_TYPE->CV)[V_Range*3].Min;
				} else {
					switch(DispScrCurrLoc) {
					case CP_Dyn_L1:
					case CP_Dyn_L2:
						cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CP)[DispScrCurrLoc+(I_Range*10)+(Disp_tmp->CP.STADYNA)*4].Resolution);
						cnt1 /= Get_Parallel_Parameter(I_Range);
						Range_Point = &I_Range;
						break;
					case CP_Dyn_T1:
					case CP_Dyn_T2:

					default:
						break;
					}
					if(DispScrCurrLoc==CP_Dyn_T1 || DispScrCurrLoc==CP_Dyn_T2) {
						umax = (ptrMODEL_TYPE->CP)[DispScrCurrLoc+2+(*Range_Point)*10].Max;
						umin = (ptrMODEL_TYPE->CP)[DispScrCurrLoc+2+(*Range_Point)*10].Min;
					} else {
						umax = (ptrMODEL_TYPE->CP)[DispScrCurrLoc+(*Range_Point)*10].Max;
						umin = (ptrMODEL_TYPE->CP)[DispScrCurrLoc+(*Range_Point)*10].Min;
					}
				}


				if(cnt1 > umax)
					cnt1 = umax;

				if(cnt1 < umin)
					cnt1 = umin;
				SaveChanData(DispScrCurrLoc,cnt1);


				KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
				/* Get KeyinBuf Value to check the value is not over default value */
				/* If OK, save data to Real Channel struct */
			} else {
				if(Disp_tmp->CP.STADYNA==Function_Static) {
					if((!Disp_tmp->UTILITY.B_ONOFF)&&(DispScrCurrLoc<=CP_Sta_B_VALUE))
						Disp_tmp->CP.ABSELECT = DispScrCurrLoc;
				}
			}
			B_DispCT = DispCT;

			if(((DispScrCurrLoc==CP_Dyn_Add_CV)&&(Disp_tmp->CP.STADYNA==Function_Dynamic))||((DispScrCurrLoc==CP_Sta_Add_CV)&&(Disp_tmp->CP.STADYNA==Function_Static))) {
				Data_tmp->CV.STA[V_Range].VALUE1 = Disp_tmp->CV.STA[V_Range].VALUE1;
				MenuRedrawFlag|=MENU1_CHANGE;
			} else
				Data_tmp->CP = Disp_tmp->CP;

			MenuDecoderAddr(&tx_data);
			SendTXData(&tx_data);
#if 1
			if((DispScrCurrLoc<=CP_Sta_B_VALUE)&&(Disp_tmp->CP.STADYNA==Function_Static)&&(!Disp_tmp->UTILITY.B_ONOFF)) {
				tx_data.ADDRH = 0x04;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				ChanRedrawFlag|= CHAN_STATUS;
			}
#endif
#if Enable_Optim_display
			DataRedrawFlag |= BG_CLEAR_FLAG;
#endif

		}
		DataRedrawFlag|= PARA_CHANGE;
		break;
	case P_CC_SPEC:
	case P_CR_SPEC:
	case P_CV_SPEC:
	case P_CP_SPEC:
		DispMode++;
		if(DispMode > DispMode_SET_PARAMETERS) {
			DispMode = DispMode_BROWSE_ITEMS;
			if((DispScrCurrLoc!=P_SPEC_HIGH)||(DispScrCurrLoc!=P_SPEC_LOW))
				val = 0;
			else
				val = DispScrCurrLoc-2;
			type = Disp_tmp->SPECTYPE;
			switch(M_num) {
			case P_CC_SPEC:
				resolution	= ptrMODEL_TYPE->CC_SPEC[val].Resolution*1000;
				umax		= ptrMODEL_TYPE->CC_SPEC[val].Max;
				umin		= ptrMODEL_TYPE->CC_SPEC[val].Min;
				break;
			case P_CR_SPEC:
				resolution	= ptrMODEL_TYPE->CR_SPEC[val].Resolution*1000;
				umax		= ptrMODEL_TYPE->CR_SPEC[val].Max;
				umin		= ptrMODEL_TYPE->CR_SPEC[val].Min;
				break;
			case P_CV_SPEC:
			default:
				resolution	= ptrMODEL_TYPE->CV_SPEC[val].Resolution*1000;
				umax		= ptrMODEL_TYPE->CV_SPEC[val].Max;
				umin		= ptrMODEL_TYPE->CV_SPEC[val].Min;
				break;
			case P_CP_SPEC:
				resolution	= ptrMODEL_TYPE->CP_SPEC[val].Resolution*1000;
				umax		= ptrMODEL_TYPE->CP_SPEC[val].Max;
				umin		= ptrMODEL_TYPE->CP_SPEC[val].Min;
				break;
			}
			if(KeyInFlag&DIGI_KEY_IN) {
				KeyInFlag &= (~DIGI_KEY_IN);
				if(P_SPEC_CENTER==DispCT) {						/* Center Value */
					cnt1 = (atof(KeyinBuf) / resolution)*1000;
					/* Judge Max or Min */
					if(cnt1>umax)
						cnt1 = umax;
					else if(cnt1<umin)
						cnt1 = umin;

					/* H(new) = C(n) +{[H(o) - C(o)] / C(o)}  *C(n)  -- Cal High Value */
					h_old = GetChanData(9,0);         //GET HIPCET
					h_new = cnt1+(((float)(h_old)/1000.0)*cnt1);

					if(h_new>umax){
						h_new=umax;
#if 1
						h_old = (UWORD) ((float)umax*1000/(float)cnt1-999);
						if(cnt1==umax)	h_old = 0;	//printf("H_pcet:%d\n",h_old);
						SaveChanData(9,h_old);
#endif
					}

					/* L(new) = C(n) - ( C(o) - L(o)  / C(o)  *C(n) )  -- Cal Low Value  */
					l_old=GetChanData(10,0);         //GET LOWPCET
					l_new=cnt1-((float)(l_old)/1000.0)*cnt1;
					if(l_new>cnt1)
						l_new=cnt1;
					/* Save To Chan */
					SaveChanData(0+6,cnt1);		/*Save Center Value */
					SaveChanData(1+6,h_new);		/*Save High Value */
					SaveChanData(2+6,l_new);		/*Save Low Value */
				} else if(DispCT==P_SPEC_HIGH) {				/* High Value or High Percent*/
					l_old = GetChanData(8,0);   		/*Get Low Value */
					if(type) {
						/* High Percent*/
						fcnt=atof(KeyinBuf)*10;
						if(fcnt>1000)
							fcnt=1000;
#if 1
						UWORD CentValue;
						CentValue = GetChanData(6,0);         //GET HIPCET
						h_old = 	(UWORD)((float)(umax-CentValue)*1000/(float)CentValue)+1;
						if(fcnt>h_old)	fcnt=h_old;	
						
#endif						
						SaveChanData(9,fcnt);	/*Save High Percent */
						GNGPcet2Step(0);
					} else {
						/* High Value */
						cnt1 = (atof(KeyinBuf) / resolution)*1000;
						if(cnt1>umax)
							cnt1 = umax;
						else if(cnt1<l_old)
							cnt1 = l_old;
						SaveChanData(1+6, cnt1);/*Save High Value */
						GNGStep2Pcet(0);
					}
				} else if(DispCT==P_SPEC_LOW) {
					/*Low Percent */
					h_old=GetChanData(7,0);  		/*Get High Value */
					if(type) {
						fcnt=atof(KeyinBuf)*10;
						if(fcnt>1000)
							fcnt=1000;
						SaveChanData(10,fcnt);	/*Save Low Percent */
						GNGPcet2Step(1);
					} else {
						/* Low Value */
						cnt1=(atof(KeyinBuf) / resolution)*1000;
						if(cnt1>h_old)
							cnt1 = h_old;
						else if(cnt1<0)
							cnt1 = 0;
						SaveChanData(2+6,cnt1);	/*Save Low Value */
						GNGStep2Pcet(1);
					}
				} else if(DispCT==P_SPEC_DELAY) {	/*Delay Time*/
					cnt1=atof(KeyinBuf)*10;
					if(cnt1>10)
						cnt1 = 10;
					else if(cnt1<0)
						cnt1 = 0;
					Disp_tmp->P_F_Delay=cnt1;
				}
				KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			}
			B_DispCT = DispCT;
			if(M_num==P_CC_SPEC)
				Data_tmp->CC = Disp_tmp->CC;
			else if(M_num==P_CR_SPEC)
				Data_tmp->CR = Disp_tmp->CR;
			else if(M_num==P_CP_SPEC)
				Data_tmp->CP = Disp_tmp->CP;
			else
				Data_tmp->CV = Disp_tmp->CV;
			if(DispCT==P_SPEC_TEST) {
				Data_tmp->SPEC = Disp_tmp->SPEC;
				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = 0x03;
				ChanRedrawFlag |= CHAN_STATUS;
			} else if(DispCT==P_SPEC_DELAY) {
				Data_tmp->P_F_Delay = Disp_tmp->P_F_Delay;
				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = 0x32;
			} else if(DispCT==P_SPEC_ENTRY) {
				if(Data_tmp->SPECTYPE!=Disp_tmp->SPECTYPE) {
					Data_tmp->SPECTYPE = Disp_tmp->SPECTYPE;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					DispScrCurrLoc = DispScrStartCT = 0;
					DispScrEndCT = 4;
				} else
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;;
				break;
			} else
				MenuDecoderAddr(&tx_data);
			SendTXData(&tx_data);
#if Enable_Optim_display
			DataRedrawFlag |= BG_CLEAR_FLAG;
#endif
		}
		DataRedrawFlag |= PARA_CHANGE;
		break;
	case P_CONF_OTHER:
		if((DispMode==1)&&(DispScrCurrLoc==P_CUTOFFTIME))
			P3k_Chan_Data.CONF.Cut_Off_cnt=0;
		DispMode++;
		if(DispMode > DispMode_SET_PARAMETERS) {
			DispMode=DispMode_BROWSE_ITEMS;
			if(KeyInFlag&DIGI_KEY_IN) {
				KeyInFlag&=(~DIGI_KEY_IN);
				if(DispScrCurrLoc==P_SOFT_START) {
					/* SOFT START */
					cnt1= atof(KeyinBuf) / ptrMODEL_TYPE->CONF[2].Resolution;
					if(cnt1>ptrMODEL_TYPE->CONF[2].Max)
						cnt1 = ptrMODEL_TYPE->CONF[2].Max;
					else if(cnt1<ptrMODEL_TYPE->CONF[2].Min)
						cnt1 = ptrMODEL_TYPE->CONF[2].Min;
				} else if(DispScrCurrLoc==P_VON_VOLTAGE) {
					/* Von Voltage */
					cnt1= atof(KeyinBuf) / ptrMODEL_TYPE->CONF[V_Range].Resolution;
					if(cnt1>ptrMODEL_TYPE->CONF[V_Range].Max)
						cnt1 = ptrMODEL_TYPE->CONF[V_Range].Max;
					else if(cnt1<ptrMODEL_TYPE->CONF[V_Range].Min)
						cnt1 = ptrMODEL_TYPE->CONF[V_Range].Min;
				} else if(DispScrCurrLoc==P_CUTOFFTIME) {
					/* Cut Off Time */
					cnt1 = atof(KeyinBuf) / ptrMODEL_TYPE->CONF[3].Resolution;
					if(P3k_Chan_Data.CONF.Cut_Off_cnt==0) {
						if(cnt1>999)cnt1=999;
						if(cnt1<0)cnt1=0;
					} else if(P3k_Chan_Data.CONF.Cut_Off_cnt==1) {
						if(cnt1>59)cnt1=59;
						if(cnt1<0)cnt1=0;
					} else if(P3k_Chan_Data.CONF.Cut_Off_cnt==2) {
						if(cnt1>59)cnt1=59;
						if(cnt1<0)cnt1=0;
					}

				} else if(P_Von_Delay==DispScrCurrLoc) {
					umax = 60000;
					umin = 1900;
					if(P3k_Disp_Data.CURRMODE == CR_MODE)
						umin = 4900;
					cnt1 = atof(KeyinBuf) / 0.001;
					if(cnt1 > umax)
						cnt1 = umax;
					else if(cnt1 < umin)
						cnt1 = umin;
				}
				SaveChanData(DispScrCurrLoc, cnt1);
				KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			}
			B_DispCT = DispScrCurrLoc;
			data = Data_tmp->CONF.VON_VOLT[V_Range];
			Data_tmp->CONF = Disp_tmp->CONF;
			Data_tmp->CONF.VON_VOLT[V_Range] = data;
			if(DispScrCurrLoc==P_Von_Delay) {
				/* Von Delay */
				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = Machine_Von_Delay;
				SendTXData(&tx_data);
			} else if(DispScrCurrLoc<=P_CUTOFFTIME || DispScrCurrLoc == P_SHORT_KEY) {
				MenuDecoderAddr(&tx_data);
				SendTXData(&tx_data);
			}

			if(DispScrCurrLoc==P_CUTOFFTIME) {
				if(P3k_Chan_Data.CONF.Cut_Off_cnt==0) {
					DispMode =2;
					P3k_Chan_Data.CONF.Cut_Off_cnt=1;
					P3k_Disp_Data.CONF.Cut_Off_cnt=1;
				} else if(P3k_Chan_Data.CONF.Cut_Off_cnt==1) {
					DispMode =2;
					P3k_Chan_Data.CONF.Cut_Off_cnt=2;
					P3k_Disp_Data.CONF.Cut_Off_cnt=2;
				} else {
					P3k_Chan_Data.CONF.Cut_Off_cnt=0;
					P3k_Disp_Data.CONF.Cut_Off_cnt=0;
				}
			}
#if Enable_Optim_display
			DataRedrawFlag |= BG_CLEAR_FLAG;
#endif
		}
		DataRedrawFlag|=PARA_CHANGE;
		break;
	case P_CONF_PROT:
		DispMode++;
		if(DispMode > DispMode_SET_PARAMETERS) {
			DispMode=DispMode_BROWSE_ITEMS;
			if(KeyInFlag & DIGI_KEY_IN) {
				KeyInFlag&=(~DIGI_KEY_IN);
				if(DispScrCurrLoc==P_OCP_LEVEL)
					range1 = PROT_OCP_H;
				else if(DispScrCurrLoc==P_OPP_LEVEL)
					range1 = PROT_OPP_H;
				else if(DispScrCurrLoc==P_UVP_LEVEL) {
					if(VRange_Low==V_Range)
						range1 = PROT_UVP_L;
					else
						range1 = PROT_UVP_H;
				} else if(DispScrCurrLoc==P_OVP_LEVEL) {
					if(VRange_Low==V_Range)
						range1 = PROT_OVP_L;
					else
						range1 = PROT_OVP_H;
				}
#if Enable_Ring_Count
				if(DispScrCurrLoc==P_UVP_SETTING) {
					cnt1 = atof(KeyinBuf)+1;
					if(cnt1>602)		cnt1 = 602;
					else if(cnt1<0) cnt1 = 0;
				}else{
					if(DispScrCurrLoc!=P_OCP_SETTING || DispScrCurrLoc!=P_OPP_SETTING)
						cnt1 = atof(KeyinBuf) / ptrMODEL_TYPE->PROT[range1].Resolution;

					if((P_OCP_LEVEL==DispScrCurrLoc)||(P_OPP_LEVEL==DispScrCurrLoc) )
						cnt1 /= Get_Parallel_Parameter(I_Range);

					if(cnt1>ptrMODEL_TYPE->PROT[range1].Max)
						cnt1 = ptrMODEL_TYPE->PROT[range1].Max;
					else if(cnt1<ptrMODEL_TYPE->PROT[range1].Min)
						cnt1 = ptrMODEL_TYPE->PROT[range1].Min;
				}
#else
				if(DispScrCurrLoc!=P_OCP_SETTING || DispScrCurrLoc!=P_OPP_SETTING)
					cnt1 = atof(KeyinBuf) / ptrMODEL_TYPE->PROT[range1].Resolution;

				if((P_OCP_LEVEL==DispScrCurrLoc)||(P_OPP_LEVEL==DispScrCurrLoc) )
					cnt1 /= Get_Parallel_Parameter(I_Range);

				if(cnt1>ptrMODEL_TYPE->PROT[range1].Max)
					cnt1 = ptrMODEL_TYPE->PROT[range1].Max;
				else if(cnt1<ptrMODEL_TYPE->PROT[range1].Min)
					cnt1 = ptrMODEL_TYPE->PROT[range1].Min;
#endif			
				SaveChanData(DispScrCurrLoc,cnt1);			/* Save Data */
				KeyinBuf[0]=KeyinBuf[1]=KeyinBuf[2]=KeyinBuf[3]=KeyinBuf[4]=KeyinBuf[5]=KeyinCT=0x00;
			}
			B_DispCT = DispScrCurrLoc;
			Data_tmp->PROT = Disp_tmp->PROT;
			MenuDecoderAddr(&tx_data);
			SendTXData(&tx_data);
#if Enable_Optim_display
			DataRedrawFlag |= BG_CLEAR_FLAG;
#endif			
#if Enable_OPPOCP_off
			if(DispScrCurrLoc<=P_OCP_SETTING){
				if((Data_tmp->CURRMODE>=P_CV)&&(Data_tmp->IRange==LOW_RANGE)&&(Data_tmp->PROT.OCP[1]>ptrMODEL_TYPE->PROT[0].Max)){
					if(P3k_Chan_Data.INFO.MACHTYPE == MODEL3031E)
						Menu_Message("OCP Level:6.6A, Setting:OFF",24,210);
					else
						Menu_Message("OCP Level:1.65A, Setting:OFF",24,210);
					CtrlFlag1 |= Disp_Middle_Message;
					DMA_Update_Flag = 1;
					Update_Panel();
					OSTimeDly(150);
				}
			}

#endif
		}
		DataRedrawFlag |= PARA_CHANGE;
		break;
	case P_CONF_KNOB:
		para_s = Get_Parallel_Parameter(I_Range);
		DispMode++;
		if(DispMode > DispMode_SET_PARAMETERS) {
			DispMode=DispMode_BROWSE_ITEMS;
			if(KeyInFlag&DIGI_KEY_IN) {
				KeyInFlag&=(~DIGI_KEY_IN);
				if(DispScrCurrLoc==P_CCH_STEP) {
					/* CCH SETP */
					cnt1=atof(KeyinBuf) / (ptrMODEL_TYPE->CC)[10].Resolution/para_s;
					if(cnt1>((ptrMODEL_TYPE->CC)[10].Max/2))
						cnt1=((ptrMODEL_TYPE->CC)[10].Max/2);
					else if(cnt1<1)
						cnt1=1;
				} else if(DispScrCurrLoc==P_CCL_STEP) {
					/* CCL SETP */
					cnt1=atof(KeyinBuf) / (ptrMODEL_TYPE->CC)[0].Resolution/para_s;
					if(cnt1>((ptrMODEL_TYPE->CC)[0].Max/2))
						cnt1=((ptrMODEL_TYPE->CC)[0].Max/2);
					else if(cnt1<1)
						cnt1=1;
				} else if(DispScrCurrLoc==P_CRH_STEP) {
					/* CRH SETP */
					cnt1=atof(KeyinBuf)/(ptrMODEL_TYPE->CR)[10].Resolution/para_s;
					if(cnt1>((ptrMODEL_TYPE->CR)[10].Max/2))
						cnt1=((ptrMODEL_TYPE->CR)[10].Max/2);
					else if(cnt1<1)
						cnt1=1;
				} else if(DispScrCurrLoc==P_CRL_STEP) {
					/* CRL SETP */
					cnt1=atof(KeyinBuf)/(ptrMODEL_TYPE->CR)[0].Resolution/para_s;
					if(cnt1>((ptrMODEL_TYPE->CR)[0].Max/2))
						cnt1=((ptrMODEL_TYPE->CR)[0].Max/2);
					else if(cnt1<1)
						cnt1=1;
				} else if(DispScrCurrLoc==P_CVH_STEP) {
					/* CVH SETP */
					cnt1=atof(KeyinBuf) / (ptrMODEL_TYPE->CV)[3].Resolution;
					if(cnt1>((ptrMODEL_TYPE->CV)[3].Max/2))
						cnt1=((ptrMODEL_TYPE->CV)[3].Max/2);
					else if(cnt1<1)
						cnt1=1;
				} else if(DispScrCurrLoc==P_CVL_STEP) {
					/* CVL SETP */
					cnt1=atof(KeyinBuf) / (ptrMODEL_TYPE->CV)[0].Resolution;
					if(cnt1>((ptrMODEL_TYPE->CV)[0].Max/2))
						cnt1=((ptrMODEL_TYPE->CV)[0].Max/2);
					else if(cnt1<1)
						cnt1=1;
				} else if(DispScrCurrLoc==P_CPH_STEP) {
					/* CPH SETP */
					cnt1=atof(KeyinBuf) / (ptrMODEL_TYPE->CP)[10].Resolution/para_s;
					if(cnt1>((ptrMODEL_TYPE->CP)[10].Max/2))
						cnt1=((ptrMODEL_TYPE->CP)[10].Max/2);
					else if(cnt1<1)
						cnt1=1;
				} else if(DispScrCurrLoc==P_CPL_STEP) {
					/* CPL SETP */
					cnt1=atof(KeyinBuf) / (ptrMODEL_TYPE->CP)[0].Resolution/para_s;
					if(cnt1>((ptrMODEL_TYPE->CP)[0].Max/2))
						cnt1=((ptrMODEL_TYPE->CP)[0].Max/2);
					else if(cnt1<1)
						cnt1=1;
				}
				SaveChanData(DispScrCurrLoc, cnt1);
				KeyinBuf[0]=KeyinBuf[1]=KeyinBuf[2]=KeyinBuf[3]=KeyinBuf[4]=KeyinBuf[5]=KeyinCT=0x00;
			}
			B_DispCT = DispScrCurrLoc;
			for(i=0; i<2; i++) {
				Data_tmp->CC.VALUE_STEP[i]= Disp_tmp->CC.VALUE_STEP[i];
				Data_tmp->CR.VALUE_STEP[i]= Disp_tmp->CR.VALUE_STEP[i];
				Data_tmp->CV.VALUE_STEP[i]= Disp_tmp->CV.VALUE_STEP[i];
				Data_tmp->CP.VALUE_STEP[i]= Disp_tmp->CP.VALUE_STEP[i];
			}
			Data_tmp->CONF.Knob_Status = Disp_tmp->CONF.Knob_Status;
			ChanRedrawFlag |= CHAN_STATUS;
		}
		DataRedrawFlag|=PARA_CHANGE;
#if Enable_Optim_display
			DataRedrawFlag |= BG_CLEAR_FLAG;
#endif		
		break;
	case P_PROG_MAIN:
		DispMode++;
		if(DispMode==DispMode_SET_PARAMETERS) {
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			MenuRedrawFlag|=MENU3_CHANGE;
			DispMode = DispMode_SELECT_CH;
			if(KeyInFlag & DIGI_KEY_IN) {
				KeyInFlag&=(~DIGI_KEY_IN);
				fcnt=atof(KeyinBuf);
				if(DispCT==Program_PROG) {
					fcnt=fcnt-1;
					if(fcnt>15)
						fcnt = 15;
					else if(fcnt<0)
						fcnt = 0;
				} else if(DispCT==Program_STEP) {
					fcnt=fcnt-1;
					if(fcnt>15)
						fcnt = 15;
					else if(fcnt<0)
						fcnt = 0;
				} else if(DispCT==Program_Memory) {
					fcnt=fcnt-1;
					if(fcnt>255)
						fcnt = 255;
					else if(fcnt<0)
						fcnt = 0;
				} else if(DispCT==Program_On_Time) {
					fcnt = fcnt*10;
					if(fcnt>600)
						fcnt = 600;
					else if(fcnt<1)
						fcnt = 1;
				} else if(DispCT==Program_Off_Time) {
					fcnt = fcnt*10;
					if(fcnt>600)
						fcnt = 600;
					else if(fcnt<0)
						fcnt = 0;
				} else if(DispCT==Program_P_F_Time) {
					/* PF Time is not over Load On + Load Off time */
					fcnt = fcnt*10;
					if(fcnt >= (Prog_tmp->Timing_Data[Prog_tmp->Prog_No].ONTIME[Prog_tmp->Step_No]+Prog_tmp->Timing_Data[Prog_tmp->Prog_No].OFFTIME[Prog_tmp->Step_No]))
						fcnt = (Prog_tmp->Timing_Data[Prog_tmp->Prog_No].ONTIME[Prog_tmp->Step_No]+Prog_tmp->Timing_Data[Prog_tmp->Prog_No].OFFTIME[Prog_tmp->Step_No])-1;
					else if(fcnt<0)
						fcnt=0;
				} else if(DispCT==Program_Short_Time) {
					/* Short Time is not over Load on Time */
					fcnt = fcnt *10;
					if(fcnt >= Prog_tmp->Timing_Data[Prog_tmp->Prog_No].ONTIME[Prog_tmp->Step_No])
						fcnt = Prog_tmp->Timing_Data[Prog_tmp->Prog_No].ONTIME[Prog_tmp->Step_No];
					else if(fcnt<0)
						fcnt = 0;
				}
				KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
				SaveChanData(DispCT, fcnt);
			}
#if Enable_Optim_display
			DataRedrawFlag |= BG_CLEAR_FLAG;
#endif			
		}
		DataRedrawFlag |= PARA_CHANGE;
		break;
	case P_PROG_CHAIN:
		if(DispMode==DispMode_SET_PARAMETERS) {
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			MenuRedrawFlag|=MENU3_CHANGE;
			DispMode=DispMode_BROWSE_ITEMS;
			if(KeyInFlag&DIGI_KEY_IN) {
				KeyInFlag&=(~DIGI_KEY_IN);
				cnt1=atoi(KeyinBuf);
				if(cnt1>17)
					cnt1 = 16;
				else if(cnt1<0)
					cnt1 = 0;
				p3k_Disp_PROG.PROGSEQ[DispScrCurrLoc]=cnt1;
				KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			}
		} else
			DispMode++;
		if(DispMode==DispMode_BROWSE_ITEMS) {
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			MenuRedrawFlag|=MENU3_CHANGE;
			DataRedrawFlag|=BG_CLEAR_FLAG;
		}
		DataRedrawFlag |=PARA_CHANGE;
		break;
	case P_FILE_CHAN:
		if(F_Media_Default==p3k_File_Utility_BAR.MEDIA)/*Media Default*/
			break;
		DispMode++;
		DispMode&=0x01;
#if 1
		if(DispMode==DispMode_SELECT_CH) {
			if(F_Media_USB==p3k_File_Utility_BAR.MEDIA) {	/*Media USB*/
				if(DispCT==P_USB_Type) {
					if(USB_Status_Display==USB_Exist) {
						if(Soft_Key_Temp!=1)
							Soft_Key_Temp=0;
						if(p3k_File_Utility_BAR.USB_Data_Type==F_Setup_Data) { /*Setup Memory*/
							SavSetupFileCount = NextFileName(SavSetupFileCount,SaveFileName,Sav_Set,0);
							RecallFileNameFun(FMnowPath, RecallFileName, Sav_Set, 0);
						} else if(p3k_File_Utility_BAR.USB_Data_Type==F_Memory_Data) { /*Memory*/
							SavMemoryFileCount = NextFileName(SavMemoryFileCount,SaveFileName,Sav_Memory,0);
							RecallFileNameFun(FMnowPath, RecallFileName, Sav_Memory, 0);
						} else if(p3k_File_Utility_BAR.USB_Data_Type==F_Preset_Data) { /*Preset*/
							SavPresetFileCount = NextFileName(SavPresetFileCount,SaveFileName,Sav_Preset,0);
							RecallFileNameFun(FMnowPath, RecallFileName, Sav_Preset, 0);
						} else if(p3k_File_Utility_BAR.USB_Data_Type==F_NSeq_Data) { /*SEQ Data*/
							SavNSeqFileCount = NextFileName(SavNSeqFileCount,SaveFileName,Sav_NSeq,0);
							RecallFileNameFun(FMnowPath, RecallFileName, Sav_NSeq, 0);
						} else if(p3k_File_Utility_BAR.USB_Data_Type==F_FSeq_Data) { /*SEQ Data*/
							SavFSeqFileCount = NextFileName(SavFSeqFileCount,SaveFileName,Sav_FSeq,0);
							RecallFileNameFun(FMnowPath, RecallFileName, Sav_FSeq, 0);
						}
						MenuRedrawFlag |= MENU4_CHANGE;
					}
				}
			}
			if(F_Media_Memory==p3k_File_Utility_BAR.MEDIA) { /*Media Memory*/
				if(DispCT==1) {
					if( KeyInFlag & DIGI_KEY_IN) {
						KeyInFlag &= ~DIGI_KEY_IN;
						cnt1=atoi(KeyinBuf);
						if(F_Memory_Data==p3k_File_Utility_BAR.Mem_Data_Type) {
							cnt1=cnt1-1;
							if(cnt1>255)
								cnt1 = 255;
							else if(cnt1<0)
								cnt1 = 0;
							p3k_File_Utility_BAR.MEMORY_ADDR=cnt1;
						} else if(F_Setup_Data==p3k_File_Utility_BAR.Mem_Data_Type) {
							cnt1=cnt1-1;
							if(cnt1>99)
								cnt1 = 99;
							else if(cnt1<0)
								cnt1 = 0;
							p3k_File_Utility_BAR.SMEMORY_ADDR=cnt1;
						} else if(F_Preset_Data==p3k_File_Utility_BAR.Mem_Data_Type) {
							cnt1=cnt1;
							if(cnt1>9)		cnt1 = 9;
							else if(cnt1<0)	cnt1 = 0;
							p3k_File_Utility_BAR.PRE_MEMORY_ADDR=cnt1;
						}
						KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
					}
				}
				DataRedrawFlag |= PARA_CHANGE ;
			}
		}
#endif
		DataRedrawFlag |= PARA_CHANGE;
		break;
	case P_UTIL_T_DATE:
		DispMode++;
		DispMode&=0x01;
		if( (DispMode==DispMode_SELECT_CH)&&(KeyInFlag&DIGI_KEY_IN) ) {
			KeyInFlag&=(~DIGI_KEY_IN);
			if(DispCT==0) {					/* MONTH */
				TIMERSET.MONTH=(char)(atof(KeyinBuf)+0.5);
				if(TIMERSET.MONTH>12)
					TIMERSET.MONTH = 12;
				else if(TIMERSET.MONTH<1)
					TIMERSET.MONTH = 1;
			}
			if(DispCT==1) {					/* DAY */
				TIMERSET._DAY=(char)(atof(KeyinBuf)+0.5);
				if(TIMERSET._DAY>31)
					TIMERSET._DAY = 31;
				else if(TIMERSET._DAY<1)
					TIMERSET._DAY = 1;
			}
			if(DispCT==2) {					/* YEAR */
				TIMERSET.YEAR=(WORD)(atof(KeyinBuf)+0.5);
				if(TIMERSET.YEAR>2038)
					TIMERSET.YEAR = 2038;
				else if(TIMERSET.YEAR<1990)
					TIMERSET.YEAR = 1990;
			}
			if(DispCT==3) {					/* HOUR */
				TIMERSET._HOUR=(char)(atof(KeyinBuf)+0.5);
				if(TIMERSET._HOUR>23)
					TIMERSET._HOUR = 23;
				else if(TIMERSET._HOUR<0)
					TIMERSET._HOUR = 0;
			}
			if(DispCT==4) {					/* MINUTE */
				TIMERSET._MINUTE=(char)(atof(KeyinBuf)+0.5);
				if(TIMERSET._MINUTE>59)
					TIMERSET._MINUTE = 59;
				else if(TIMERSET._MINUTE<0)
					TIMERSET._MINUTE = 0;
			}
			KeyinBuf[0]=KeyinBuf[1]=KeyinBuf[2]=KeyinBuf[3]=KeyinBuf[4]=KeyinBuf[5]=KeyinCT=0x00;
		}
		if(DispMode==DispMode_SELECT_CH) {
			SetRTC(0);
			SysRedrawFlag |= TIME_UPDATA;
		}
		DataRedrawFlag|=PARA_CHANGE;
		break;
	case P_UTIL_LOAD:
	case P_UTIL_OTHER:
		DispMode++;
		DispMode&=0x01;
		
#if Enable_Ring_Count
		if (M_num==P_UTIL_OTHER){
			if(DispMode==DispMode_SELECT_CH) {
				if(DispScrCurrLoc==Util_Alarm_Tone) {
					Tone_Flag&=(~0x01);
					UVP_Tone_Count = 0;
					Tone_Flag&=(~0x08);
					SEQ_Tone_Count = 0;
				}
			}
		}
#endif
			
		DataRedrawFlag|=PARA_CHANGE;
#if Enable_Optim_display
		DataRedrawFlag |= BG_CLEAR_FLAG;
#endif		
		break;
	case P_UTIL_INTERFACE:
		DispMode++;
		if(DispMode==DispMode_SET_PARAMETERS) {
			DispMode=DispMode_SELECT_CH;
			if(DispCT==0) {
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				if(UTILITY.INTERFACE!=D_interface.INTERFACE) {
					UTILITY.INTERFACE=D_interface.INTERFACE;
					SysRedrawFlag |= Interface_UPDATA;
					if(UTILITY.INTERFACE==INTERFACE_RS232) {
						RS232.ONOFF = 0x1;
						if(SYSType&GPIB_CONNECTED)
							GPIBPAR.ONOFF = 0x0;
						UTILITY.USB_ONOFF = 0x0;
					} else if(UTILITY.INTERFACE==INTERFACE_GPIB) {
						if(!(SYSType&GPIB_CONNECTED))
							break;
						RS232.ONOFF		= 0x0;
						GPIBPAR.ONOFF		= 0x1;
						UTILITY.USB_ONOFF	= 0x0;
					} else if(UTILITY.INTERFACE==INTERFACE_USB) {
						RS232.ONOFF = 0x0;
						if(SYSType&GPIB_CONNECTED)
							GPIBPAR.ONOFF = 0x0;
						UTILITY.USB_ONOFF = 0x1;
					}
					OSSemPost(InterfaceChangeSemPtr);
					OSSemPend(InterfaceReadySemPtr, 0, &err);
				}
			} else if(DispCT==1) {
				if((RS232.BAUD!=D_interface.BAUD)&&(UTILITY.INTERFACE==INTERFACE_RS232)) {
					RS232.BAUD = D_interface.BAUD;
					OSSemPost(InterfaceChangeSemPtr);
					OSSemPend(InterfaceReadySemPtr, 0, &err);
				}
				if((GPIBPAR.MYADDR!=D_interface.MYADDR)&&(UTILITY.INTERFACE==INTERFACE_GPIB)) {
					GPIBPAR.MYADDR = D_interface.MYADDR;
					OSSemPost(InterfaceChangeSemPtr);
					OSSemPend(InterfaceReadySemPtr, 0, &err);
					SysRedrawFlag |= Interface_UPDATA;
				}
			} else if(DispCT==2) {
				if(RS232.STOP!=D_interface.STOP) {
					RS232.STOP = D_interface.STOP;
					OSSemPost(InterfaceChangeSemPtr);
					OSSemPend(InterfaceReadySemPtr, 0, &err);
				}
			} else if(DispCT==3) {
				if(RS232.PARITY!=D_interface.PARITY) {
					RS232.PARITY = D_interface.PARITY;
					OSSemPost(InterfaceChangeSemPtr);
					OSSemPend(InterfaceReadySemPtr, 0, &err);
				}
			}
		}
		DataRedrawFlag|=PARA_CHANGE;
		break;
	case P_CAL_MODE:		/* Calibration Mode */
		DispMode++;
		if(DispMode==DispMode_BROWSE_ITEMS) {
#if Enable_Ext_CalOffset			
			if(((P3K_CALIBRATION_BAR.MODE==CC_MODE)||(P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)||(P3K_CALIBRATION_BAR.MODE>=Ext_V_CC_MODE))&&((p3k_Cal_data.OffsetFlag&0x02)==0)) {
#else
			if(((P3K_CALIBRATION_BAR.MODE==CC_MODE)||(P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE))&&((p3k_Cal_data.OffsetFlag&0x02)==0)) {
#endif
#if 1
			if(P3K_CALIBRATION_BAR.PSense){
				DispMode=DispMode_SELECT_CH;
				p3k_Cal_data.OffsetFlag = 0;
				return;
			}
#endif

				//CC,CR,CP 1st enter offsetAdj // FPGA  0x40:0, 0x99:¥i½Õ

				P3K_CALIBRATION_BAR.POINT = DispCT;
				P3K_CALIBRATION_BAR.Volt_Curr_Sel = Select_Volt;
				/* Load  Calibration Default  & Calibration Start*/

				tx_data.ADDRH = Cal_FPGA_Command;
				tx_data.ADDRL = Cal_FPGA_Load_Cal_Default;
				SendTXData(&tx_data);


				tx_data.ADDRH = Cal_FPGA_Command;
				tx_data.ADDRL = Cal_FPGA_OffsetAdjSetDA;
				SendTXData(&tx_data);

				tx_data.ADDRH = Cal_FPGA_Command;
				tx_data.ADDRL = Cal_FPGA_OffsetAdjValue;
				SendTXData(&tx_data);

				/* Cal Start : Send Load On Command */
				tx_data.ADDRH = Cal_FPGA_Command;
				tx_data.ADDRL = Cal_FPGA_Start;
				SendTXData(&tx_data);

			} else
				Rem_Sel_Cal_Point(DispCT);
		} else if(DispMode==DispMode_SET_PARAMETERS) {
			DispMode = DispMode_SELECT_CH;
			if(KeyInFlag&DIGI_KEY_IN) {
				KeyInFlag &= (~DIGI_KEY_IN);
				fdat = atof(KeyinBuf);
				KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
#if 0 //Adam 2015/0504
				if(1){//if( M_Out_Of_Range==Rem_Input_Cal_Data(fdat,DispCT) ) {
					CalMessageFlag |= Show_Message;
					P3K_CALIBRATION_BAR.Volt_Curr_Sel = Select_Volt;
					DataRedrawFlag |= PARA_CHANGE;
					tx_data.ADDRH = Cal_FPGA_Command;
					tx_data.ADDRL = Cal_FPGA_Fail;
					SendTXData(&tx_data);
					ShowCalMessage();
					return;
				}


#endif


#if Enable_Ext_CalOffset
				if(((P3K_CALIBRATION_BAR.MODE==CC_MODE)||(P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)||(P3K_CALIBRATION_BAR.MODE>=Ext_V_CC_MODE))&&((p3k_Cal_data.OffsetFlag&0x02)==0)) {
#else
				if(((P3K_CALIBRATION_BAR.MODE==CC_MODE)||(P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE))&&((p3k_Cal_data.OffsetFlag&0x02)==0)) {
#endif
					cnt1 = (ULONG)fdat;
					if(cnt1>Calibration_Adj_maxValue)cnt1 =Calibration_Adj_maxValue; //LIMIT SETTING VALUE
					if(cnt1<Calibration_Adj_minValue)cnt1 =Calibration_Adj_minValue; //LIMIT SETTING VALUE
					p3k_Cal_data.OffsetAdjCnt1 = (UWORD)cnt1;
					p3k_Cal_data.OffsetFlag |= 0x01; //Adj has been
					tx_data.ADDRH = Cal_FPGA_Command;
					tx_data.ADDRL = Cal_FPGA_OffsetAdjValue;
					SendTXData(&tx_data);
					DataRedrawFlag |= PARA_CHANGE;
					return;
				} else if( M_Out_Of_Range==Rem_Input_Cal_Data(fdat,DispCT)) {
					CalMessageFlag |= Show_Message;
					P3K_CALIBRATION_BAR.Volt_Curr_Sel = Select_Volt;
					DataRedrawFlag |= PARA_CHANGE;
					tx_data.ADDRH = Cal_FPGA_Command;
					tx_data.ADDRL = Cal_FPGA_Fail;
					SendTXData(&tx_data);
#if 1
					ShowCalMessage();
#endif
					return;
				}
			} else {
#if Enable_Ext_CalOffset
				if(((P3K_CALIBRATION_BAR.MODE==CC_MODE)||(P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)||(P3K_CALIBRATION_BAR.MODE>=Ext_V_CC_MODE))&&((p3k_Cal_data.OffsetFlag&0x02)==0)) {
#else
				if(((P3K_CALIBRATION_BAR.MODE==CC_MODE)||(P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE))&&((p3k_Cal_data.OffsetFlag&0x02)==0)) {
#endif
					p3k_Cal_data.OffsetFlag |= 0x01; //Adj has been
					DataRedrawFlag |= PARA_CHANGE;
					return;
				} else if((P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)) {
					if( (Cal_High_Point==DispCT)&&(Select_Curr==P3K_CALIBRATION_BAR.Volt_Curr_Sel) )
						CAL_HI_LOW_SET_OK |= 0x01;
					else if( (Cal_Low_Point==DispCT)&&(Select_Curr==P3K_CALIBRATION_BAR.Volt_Curr_Sel) )
						CAL_HI_LOW_SET_OK |= 0x02;
				} else {
					if(Cal_High_Point==DispCT)
						CAL_HI_LOW_SET_OK |= 0x01;
					else if(Cal_Low_Point==DispCT)
						CAL_HI_LOW_SET_OK |= 0x02;
				}
			}
			if((Select_Volt==P3K_CALIBRATION_BAR.Volt_Curr_Sel)&&((P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)||(P3K_CALIBRATION_BAR.MODE==F_IMON_MODE)||(P3K_CALIBRATION_BAR.MODE==R_IMON_MODE)) ) {
				P3K_CALIBRATION_BAR.Volt_Curr_Sel = Select_Curr;
				DispMode = DispMode_BROWSE_ITEMS;
				DataRedrawFlag |= PARA_CHANGE;
				return;
			}
			if(CAL_HI_LOW_SET_OK==0x03) {
				P3K_CALIBRATION_BAR.START = 0x0;
				MenuRedrawFlag |= MENU4_CHANGE;
			}
			if((P3K_CALIBRATION_BAR.MODE==CC_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)) {
				CtrlFlag1 |= Cal_Wait_moment;
				ShowCalMessage();
			}
			tx_data.ADDRH = Cal_FPGA_Command;
			tx_data.ADDRL = Cal_FPGA_End;
			SendTXData(&tx_data);
		}
		DataRedrawFlag |= PARA_CHANGE;
		break;



	case P_UTIL_KEYPAD:
		EnterChrFunc();
		break;
	case P_FILE_MACHINE:
		break;
	case P_UTIL_FILE:
		FMselect(0,0);
		break;
	case P_HELP_HELP:
		break;
	case P_Input_Password:
		Password_Process(0,0);
		break;
	case P_CONF_Para:
		DispMode++;
		if(DispMode>DispMode_SET_PARAMETERS){
			B_DispCT = DispCT;
			DispMode = DispMode_BROWSE_ITEMS;
			if(KeyInFlag & DIGI_KEY_IN) {
				KeyInFlag&=(~DIGI_KEY_IN);
				if(DispCT==P_Sync_TrigInDelay) {
					cnt1=atof(KeyinBuf)*2;
					if(cnt1>10000)	cnt1=10000;
					else if(cnt1<0)	cnt1=0;
					Disp_tmp->CONF.Para_Data.TrigInDelay= cnt1;					
				} else if(DispCT==P_Sync_TrigOutWidth) {
					cnt1=atof(KeyinBuf)*2;
					if(cnt1>10000)	cnt1=10000;
					else if(cnt1<5)	cnt1=5;
					Disp_tmp->CONF.Para_Data.TrigOutWidth = cnt1;					
				}
				SaveChanData(DispCT, cnt1);
				KeyinBuf[0]=KeyinBuf[1]=KeyinBuf[2]=KeyinBuf[3]=KeyinBuf[4]=KeyinBuf[5]=KeyinCT=0x00;
			}
			if(DispCT==P_Sync_TrigInDelay) {				
				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = Machine_TrigInDelay;
				SendTXData(&tx_data);
			} else if((DispCT==P_Sync_TrigOut)||(DispCT==P_Sync_TrigOutWidth)) {				
				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = Machine_TrigOutWidth;
				SendTXData(&tx_data);
			}		
			Data_tmp->CONF.Para_Data = Disp_tmp->CONF.Para_Data;			
			ChanRedrawFlag |= CHAN_CHANGE;
#if Enable_Optim_display
			DataRedrawFlag |= BG_CLEAR_FLAG;
#endif
		}		
		DataRedrawFlag |= PARA_CHANGE;
		break;
	case P_CONF_Ext:
		DispMode++;
		if(DispMode > DispMode_SET_PARAMETERS) {
			data = GetChanData(DispCT,0);
			SaveChanData(DispCT, data);
			B_DispCT = DispCT;
			DispMode = DispMode_BROWSE_ITEMS;
			if(P_Ext_Control==DispCT) {
				Auto_Load_Off();
				/* Parallel and External Setting */
				tx_data.ADDRH = Para_Ext_Command;
				tx_data.ADDRL = Para_Ext_Setting;
				SendTXData(&tx_data);
				ChanRedrawFlag |= CHAN_STATUS;

				if(	(CC_MODE==Data_tmp->CURRMODE && Data_tmp->CC.STADYNA)||(CR_MODE==Data_tmp->CURRMODE && Data_tmp->CR.STADYNA)||(CP_MODE==Data_tmp->CURRMODE && Data_tmp->CP.STADYNA) ) {
					Disp_tmp->CP.STADYNA = Data_tmp->CP.STADYNA = Function_Static;
					Disp_tmp->CC.STADYNA = Data_tmp->CC.STADYNA = Function_Static;
					Disp_tmp->CR.STADYNA = Data_tmp->CR.STADYNA = Function_Static;

					if(CC_MODE==Data_tmp->CURRMODE)
						tx_data.ADDRH = 0x01;

					else if(CR_MODE==Data_tmp->CURRMODE)
						tx_data.ADDRH = 0x02;
					else
						tx_data.ADDRH = 0x04;

					tx_data.ADDRL = 0x01;
					SendTXData(&tx_data);

					tx_data.ADDRL = 0x00;
					SendTXData(&tx_data);
				}
				tx_data.ADDRH = Cal_FPGA_Command;
				tx_data.ADDRL = Cal_FPGA_Load_Meas_Default;
				SendTXData(&tx_data);
			} else if(P_Extmulti_para==DispCT) {
				//SaveChanData(DispCT, data);
				if(P3k_Chan_Data.CONF.Ext_Setting.MultilPara)
					SaveChanData(1, 0);
			}
#if Enable_Optim_display
			DataRedrawFlag |= BG_CLEAR_FLAG;
#endif			
		}
		DataRedrawFlag|=PARA_CHANGE;
		break;
	case P_Test_Func:
		if(debugmode)return;
		DispMode++;
		if(DispMode > DispMode_SET_PARAMETERS) {
			DispMode = DispMode_BROWSE_ITEMS;	/* Back to Browers */

			if( KeyInFlag & DIGI_KEY_IN) {
				KeyInFlag &= ~DIGI_KEY_IN;
				cnt1= atof(KeyinBuf);
				if((DispCT==1)||(DispCT==3))
					umax = 255;
				else
					umax = 65535;

				if(cnt1 > umax)
					cnt1 = umax;
				else if(cnt1 < 0)
					cnt1 = 0;

				if(DispCT==1)
					P3K_CMD = cnt1;
				else if(DispCT==2)
					P3K_DATA = cnt1;
				else if(DispCT==3)
					RecordCMD = cnt1;

				KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			}
			B_DispCT = DispCT;

			if(DispCT==3) {
#if debug_tool
				FPGASetting =FPGA_W[RecordCMD];
				FPGAStatus = FPGA_R[RecordCMD];
#endif
			} else if(P3K_CMD_R_W) { /*Write*/
				if(DispCT==2) {
#if debug_tool
					FPGA_W[P3K_CMD]=P3K_DATA;
					asm("nop;");asm("nop;");asm("nop;");
#endif
					SPROT0_CMD=0x00000000+(P3K_CMD<<24)+P3K_DATA;
					sport0Write(SPROT0_CMD);

				}
			} else {	/*Read*/
				if(DispCT==1) {
					SPROT0_CMD=0x00000000+(P3K_CMD<<24);
					SPROT0_DATA=sport0Read(SPROT0_CMD);
					P3K_DATA=(SPROT0_DATA&0x0000FFFF);
#if debug_tool
					asm("nop;");asm("nop;");
					FPGA_R[P3K_CMD] = P3K_DATA;
#endif
				}
			}
		}
		DataRedrawFlag|= PARA_CHANGE;
		break;
#if Enable_Func_select
	case P_FUNC_MAIN:
	case P_FUNC_MAIN_2:
		DispMode++;
		if(DispMode==DispMode_SET_PARAMETERS) {			
			DispMode = DispMode_SELECT_CH;				
			///B_DispCT = DispScrCurrLoc;
			if(P_Func_M_start==DispCT) {				
				if(P3k_Chan_Data.Load_Type != P3k_Disp_Data.Load_Type){
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x0;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
					}
					P3k_Chan_Data.Load_Type = P3k_Disp_Data.Load_Type;			
					SEQ_Save_Status=0;
					Soft_Key_Temp = 0;
					SysRedrawFlag	|= PROG_UPDATA;
					DataRedrawFlag |= DATA_CHANGE ;
				}
			}else if(P_Func_M_comp==DispCT) {				
				if( KeyInFlag & DIGI_KEY_IN) {
					KeyInFlag &= ~DIGI_KEY_IN;
					if(DispCT==P_Func_M_comp) {
						cnt1 = atof(KeyinBuf)+1;
						umax = 602;
						umin = 1;
					} 
					if(cnt1>umax)		cnt1 = umax;
					else if(cnt1<umin)	cnt1 = umin;
					SaveChanData(DispCT , cnt1);
					KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
				}
				Data_tmp->PROT = Disp_tmp->PROT;
				Data_tmp->CONF.T_count_up = Disp_tmp->CONF.T_count_up;
			} else if(P_Func_M_count==DispCT){
				Data_tmp->PROT = Disp_tmp->PROT;
				Data_tmp->CONF.T_count_up = Disp_tmp->CONF.T_count_up;	
			}						
		}		
		DataRedrawFlag |= PARA_CHANGE;
		break;		
	
#endif		

	case P_Seq_Normal:
		if(0!=P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step) {
			if((DispCT ==0x03)||(DispCT ==0x04)) {
				Show_Seq_fix();
				SysRedrawFlag |= PROG_UPDATA;
				return;
			}
		}
		DispMode++;
		if(DispMode==DispMode_SET_PARAMETERS) {
			SEQ_Save_Status = 1;
			MenuRedrawFlag |= MENU3_CHANGE;
			DispMode = DispMode_SELECT_CH;
			if( KeyInFlag & DIGI_KEY_IN) {
				KeyInFlag &= ~DIGI_KEY_IN;
				if(DispCT==P_NSeq_Loop) {
					cnt1 = atof(KeyinBuf);
					umax = 9999;
					umin = 0;
				} else if(DispCT==P_NSeq_Last_Set) {
					V_Range = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Range/2;
					I_Range = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Range%2;
					Seq_Mode_Temp = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode;
					if(CC_MODE==Seq_Mode_Temp) {
						cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CC)[I_Range*10].Resolution);
						umax = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
						umin = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
					} else if(CR_MODE==Seq_Mode_Temp) {
						cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CR)[I_Range*10].Resolution);
						umax = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
						umin = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
					} else if(CV_MODE==Seq_Mode_Temp) {
						cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CV)[V_Range*3].Resolution);
						umax = (ptrMODEL_TYPE->CV)[V_Range*3].Max;
						umin = (ptrMODEL_TYPE->CV)[V_Range*3].Min;
					} else { /*CP_MODE*/
						cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CP)[I_Range*10].Resolution);
						umax = (ptrMODEL_TYPE->CP)[I_Range*10].Max;
						umin = (ptrMODEL_TYPE->CP)[I_Range*10].Min;
					}
					if(CV_MODE!=Seq_Mode_Temp)
						cnt1 /= Get_Parallel_Parameter(I_Range);
				}


				if(cnt1>umax)
					cnt1 = umax;
				else if(cnt1<umin)
					cnt1 = umin;

				SaveChanData(DispCT , cnt1);
				KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			}
#if Enable_Optim_display
			DataRedrawFlag |= BG_CLEAR_FLAG;
#endif	
		} else if( (DispMode==DispMode_BROWSE_ITEMS)&&(DispCT==P_NSeq_Memo) ) {
			for(i=0 ; i<12 ; i++) {
				if(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Memo[i]==0)
					break;
				KeypadSTR[i] = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Memo[i];
			}
			for( ; i<13 ; i++)
				KeypadSTR[i] = 0;
			Soft_Key_Temp		= 0;
			SEQ_Save_Status	= 1;
			DispMode 			= DispMode_SELECT_CH;
			K_M_num 			= M_num;
			M_num 			= P_UTIL_KEYPAD;
			MenuRedrawFlag		|= MENU_CHANGE;
			KeypadRedrawFlag	|= KEYPAD_UPDATA ;
#if Enable_Optim_display
			DataRedrawFlag |= BG_CLEAR_FLAG;
#endif			
		}
		DataRedrawFlag |= PARA_CHANGE;
		break;
	case P_NSeq_Edit:
		if(0==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step)
			break;
		DispMode++;
		if(DispMode==DispMode_SET_PARAMETERS) {
			SEQ_Save_Status = 1;
			MenuRedrawFlag |= MENU3_CHANGE;
			DispMode = DispMode_SELECT_CH;
			if( KeyInFlag & DIGI_KEY_IN) {
				KeyInFlag &= ~DIGI_KEY_IN;
				if(P_NSeqEdit_Step==DispCT) {
					cnt1 = atof(KeyinBuf);
					umax = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step;
					umin = 1;
				} else if(DispCT==P_NSeqEdit_Value) {
					V_Range = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Range/2;
					I_Range = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Range%2;
					Seq_Mode_Temp = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode;

					if(CC_MODE==Seq_Mode_Temp) {
						cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CC)[I_Range*10].Resolution);
						umax = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
						umin = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
					} else if(CR_MODE==Seq_Mode_Temp) {
						cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CR)[I_Range*10].Resolution);
						umax = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
						umin = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
					} else if(CV_MODE==Seq_Mode_Temp) {
						cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CV)[V_Range*3].Resolution);
						umax = (ptrMODEL_TYPE->CV)[V_Range*3].Max;
						umin = (ptrMODEL_TYPE->CV)[V_Range*3].Min;
					} else { /*CP_MODE*/
						cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CP)[I_Range*10].Resolution);
						umax = (ptrMODEL_TYPE->CP)[I_Range*10].Max;
						umin = (ptrMODEL_TYPE->CP)[I_Range*10].Min;
					}
					if(CV_MODE!=Seq_Mode_Temp)
						cnt1 /= Get_Parallel_Parameter(I_Range);
				} else if(DispCT==P_NSeqEdit_Time_H) {
					cnt1 = atof(KeyinBuf);
					umax = 999;
					umin = 0;
				} else if(DispCT==P_NSeqEdit_Time_M) {
					cnt1 = atof(KeyinBuf);
					umax = 59;
					umin = 0;
				} else if(DispCT==P_NSeqEdit_Time_S) {
					cnt1 = atof(KeyinBuf);
					umax = 59;
					umin = 0;
				} else if(DispCT==P_NSeqEdit_Time_mS) {
#if Enable_NSEQ_Usec
					cnt1 = InputToStep(atof(KeyinBuf),0.05);
					umax = 19999;
#else
					cnt1 = atof(KeyinBuf);
					umax = 999;
#endif
					umin = 0;
				}
				if(cnt1>umax)
					cnt1 = umax;
				else if(cnt1<umin)
					cnt1 = umin;
				SaveChanData(DispCT , cnt1);
				KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			}
			if( (DispCT>=P_NSeqEdit_Time_H)&&(DispCT<=P_NSeqEdit_Time_mS) ) {
				if( (0==GetChanData(P_NSeqEdit_Time_H,0))&&(0==GetChanData(P_NSeqEdit_Time_M,0))&&(0==GetChanData(P_NSeqEdit_Time_S,0))&&(0==GetChanData(P_NSeqEdit_Time_mS,0)) )
					SaveChanData(P_NSeqEdit_Time_mS,1);
			}
		}
		DataRedrawFlag |= PARA_CHANGE;
#if Enable_Optim_display
		DataRedrawFlag |= BG_CLEAR_FLAG;
#endif		
		break;
	case P_Seq_Fast:
		if(P3k_FSeq_Disp.FSeq_Max_Step<0xFF00) {
			if((DispCT ==0x01)||(DispCT ==0x02)) {
				Show_Seq_fix();
				SysRedrawFlag |= PROG_UPDATA;
				return;
			}
		}
		DispMode++;
		if(DispMode==DispMode_SET_PARAMETERS) {
			SEQ_Save_Status = 1;
			MenuRedrawFlag |= MENU3_CHANGE;
			DispMode = DispMode_SELECT_CH;
			if( KeyInFlag & DIGI_KEY_IN) {
				KeyInFlag &= ~DIGI_KEY_IN;
				if(DispCT==P_FSeq_Loop) {
					cnt1 = atof(KeyinBuf);
					umax = 9999;
					umin = 0;
				} else if(DispCT==P_FSeq_TimeBase) {
					cnt1 = InputToStep(atof(KeyinBuf),0.001);
					if(atof(KeyinBuf)<60.001) {			/*Time Base Set 1uS*/
						range1 = 0;
						cnt1 = InputToStep(atof(KeyinBuf),0.001);
					} else {							/*Time Base Set 10uS*/
						range1 = 1;
						cnt1 = InputToStep(atof(KeyinBuf),0.01);
					}
					if(cnt1>60000)
						cnt1 = 60000;
#if Enalbe_FSEQ_1US
					else if(cnt1<1)
						cnt1 = 1;
#else
					else if(cnt1<25)
						cnt1 = 25;
#endif

					P3k_FSeq_Disp.FSeq_TB_Range	= range1;
					P3k_FSeq_Disp.FSeq_Time_Base	= cnt1;
					KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
					DataRedrawFlag |= PARA_CHANGE;
					break;
				} else if(DispCT==P_FSeq_Last_Set) {
					V_Range = P3k_FSeq_Disp.FSeq_Range/2;
					I_Range = P3k_FSeq_Disp.FSeq_Range%2;
					Seq_Mode_Temp = P3k_FSeq_Disp.FSeq_Mode;
					if(CC_MODE==Seq_Mode_Temp) {
						cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CC)[I_Range*10].Resolution);
						umax = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
						umin = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
					} else {	/*CR_MODE*/
						cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CR)[I_Range*10].Resolution);
						umax = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
						umin = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
					}
					cnt1 /= Get_Parallel_Parameter(I_Range);
				} else if(DispCT==P_FSeq_RptStep) {
#if Enable_FSEQ_RPT
					cnt1 = atof(KeyinBuf);
					cnt1 = cnt1-1;
					umax = P3k_FSeq_Disp.FSeq_Max_Step+1;
					umin = 0;
#else
					cnt1 = atof(KeyinBuf);
					cnt1 = cnt1 -1;
					umax = 999;
					umin = 0;
#endif

				}
				if(cnt1>umax)
					cnt1 = umax;
				else if(cnt1<umin)
					cnt1 = umin;
				SaveChanData(DispCT , cnt1);
#if Enable_Optim_display
				DataRedrawFlag |= BG_CLEAR_FLAG;
#endif
				KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			}
		} else if( (DispMode==DispMode_BROWSE_ITEMS)&&(DispCT==P_FSeq_Memo) ) {
			for(i=0 ; i<12 ; i++) {
				if(P3k_FSeq_Disp.FSeq_Memo[i]==0)
					break;
				KeypadSTR[i] = P3k_FSeq_Disp.FSeq_Memo[i];
			}
			for( ; i<13 ; i++)
				KeypadSTR[i] = 0;
			Soft_Key_Temp		= 0;
			SEQ_Save_Status = 1;
			DispMode			= DispMode_SELECT_CH;
			K_M_num 			= M_num;
			M_num			= P_UTIL_KEYPAD;
			MenuRedrawFlag		|= MENU_CHANGE;
			KeypadRedrawFlag	|= KEYPAD_UPDATA;
			
		}
		DataRedrawFlag |= PARA_CHANGE;
		break;
	case P_FSeq_Edit:
		if(P3k_FSeq_Disp.FSeq_Max_Step>0xFF00)
			break;
		DispMode++;
		if(DispMode==DispMode_SET_PARAMETERS) {
			SEQ_Save_Status = 1;
			MenuRedrawFlag |= MENU3_CHANGE;
			DispMode = DispMode_SELECT_CH;
			if( KeyInFlag & DIGI_KEY_IN) {
				KeyInFlag &= ~DIGI_KEY_IN;
				if(P_FSeqEdit_Step==DispCT) {
					cnt1 = atof(KeyinBuf);
					cnt1 = cnt1 - 1;
					umax = P3k_FSeq_Disp.FSeq_Max_Step;
					umin = 0;
				} else if(DispCT==P_FSeqEdit_Value) {
					V_Range = P3k_FSeq_Disp.FSeq_Range/2;
					I_Range = P3k_FSeq_Disp.FSeq_Range%2;
					Seq_Mode_Temp = P3k_FSeq_Disp.FSeq_Mode;
					if(CC_MODE==Seq_Mode_Temp) {
						cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CC)[I_Range*10].Resolution);
						umax = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
						umin = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
					} else { /*CR_MODE*/
						cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CR)[I_Range*10].Resolution);
						umax = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
						umin = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
					}
					cnt1 /= Get_Parallel_Parameter(I_Range);
				}
				if(cnt1>umax)
					cnt1 = umax;
				else if(cnt1<umin)
					cnt1 = umin;
				SaveChanData(DispCT , cnt1);
				KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			}
#if Enable_Optim_display
			DataRedrawFlag |= BG_CLEAR_FLAG;
#endif			
		}
		DataRedrawFlag |= PARA_CHANGE;
		break;
	case P_FSeq_Fill:
		DispMode++;
		if(DispMode==DispMode_SET_PARAMETERS) {
			DispMode = DispMode_SELECT_CH;
			if( KeyInFlag & DIGI_KEY_IN) {
				KeyInFlag &= ~DIGI_KEY_IN;
				if( (P_Fill_Step_S==DispCT)||(P_Fill_Step_E==DispCT) ) {
					cnt1 = atof(KeyinBuf);
					cnt1 = cnt1 - 1;
					umax = 999;
					umin = 0;
				} else {	/*P_Fill_Value_S and P_Fill_Value_E*/
					V_Range = P3k_FSeq_Disp.FSeq_Range/2; //Adam_debug
					I_Range = P3k_FSeq_Disp.FSeq_Range%2; //Adam_debug
					Seq_Mode_Temp = P3k_FSeq_Disp.FSeq_Mode;
					if(CC_MODE==Seq_Mode_Temp) {
						cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CC)[I_Range*10].Resolution);
						umax = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
						umin = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
					} else { /*CR_MODE*/
						cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CR)[I_Range*10].Resolution);
						umax = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
						umin = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
					}
					cnt1 /= Get_Parallel_Parameter(I_Range);
				}
				if(cnt1>umax)
					cnt1 = umax;
				else if(cnt1<umin)
					cnt1 = umin;
				SaveChanData(DispCT , cnt1);
				KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			}
#if Enable_Optim_display
			DataRedrawFlag |= BG_CLEAR_FLAG;
#endif			
		}
		DataRedrawFlag |= PARA_CHANGE;
		break;
#if Enable_OCP_function
	case P_FUNC_OCP:	

		DispMode++;
		if(DispMode==DispMode_SET_PARAMETERS) {
			SEQ_Save_Status = 1;
			MenuRedrawFlag |= MENU3_CHANGE;
			DispMode = DispMode_SELECT_CH;
			if( KeyInFlag & DIGI_KEY_IN) {
				KeyInFlag &= ~DIGI_KEY_IN;				
				
#if 1
CurrRes = (ptrMODEL_TYPE->CC)[OCP->Range*10].Resolution;
CurrPre = (ptrMODEL_TYPE->CC)[OCP->Range*10].precision;
VoltRes = (ptrMODEL_TYPE->CV)[3].Resolution;
VoltPre = (ptrMODEL_TYPE->CV)[3].precision;
TimeRes = 0.01;
TimePre = 2;
#endif
				if(DispCT==P_F_OCP_CurrTemp){
					cnt1 = atof(KeyinBuf)-1;
					umax = 11; umin = 0;	
					DataRedrawFlag =DATA_CHANGE;
				} else if(DispCT==P_F_OCP_StartCurr){
					cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
					umax = (ptrMODEL_TYPE->CC)[0].Max-1;
					umin = (ptrMODEL_TYPE->CC)[0].Min;				
				} else if(DispCT==P_F_OCP_EndCurr) {				
					cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
					umax = (ptrMODEL_TYPE->CC)[0].Max;
					umin = (ptrMODEL_TYPE->CC)[0].Min+2;				
				} else if(DispCT==P_F_OCP_StepCurr) {
					cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
					umax = (ptrMODEL_TYPE->CC)[0].Max/2;
					umin = (ptrMODEL_TYPE->CC)[0].Min+1;				
				} else if(DispCT==P_F_OCP_StepTime){
					cnt1 = InputToStep(atof(KeyinBuf),TimeRes);
					umax = 5000;
					umin = 1;				
				} else if(DispCT==P_F_OCP_TrigVolt) {
					cnt1 = InputToStep(atof(KeyinBuf),VoltRes);
					umax = (ptrMODEL_TYPE->CV)[3].Def;
					umin = 1;				
				} else if(DispCT==P_F_OCP_DelayTrig) {
					cnt1 = InputToStep(atof(KeyinBuf),TimeRes);
					umax = 500;
					cnt2 = GetChanData(P_F_OCP_StepTime,0);
					if(umax>=data)umax = cnt2-1;
					umin = 0;
				} else if(DispCT==P_F_OCP_LastCurr) {
					cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
					umax = (ptrMODEL_TYPE->CC)[0].Max;
					umin = (ptrMODEL_TYPE->CC)[0].Min;
				}
				if(cnt1>umax)		cnt1 = umax;
				else if(cnt1<umin)	cnt1 = umin;					
				SaveChanData(DispCT, cnt1);
				KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
			}
		}
		DataRedrawFlag |= PARA_CHANGE;
		if(DispMode==DispMode_SELECT_CH)	DataRedrawFlag |= DATA_CHANGE;
		break;

#endif
#if Enable_OPP_function
		case P_FUNC_OPP:	
			DispMode++;
			if(DispMode==DispMode_SET_PARAMETERS) {
				SEQ_Save_Status = 1;
				MenuRedrawFlag |= MENU3_CHANGE;
				DispMode = DispMode_SELECT_CH;
				if( KeyInFlag & DIGI_KEY_IN) {
					KeyInFlag &= ~DIGI_KEY_IN;	
#if 1
					CurrRes = (ptrMODEL_TYPE->CP)[OPP->Range*10].Resolution;
					CurrPre = (ptrMODEL_TYPE->CP)[OPP->Range*10].precision;
					VoltRes = (ptrMODEL_TYPE->CV)[3].Resolution;
					VoltPre = (ptrMODEL_TYPE->CV)[3].precision;
					TimeRes = 0.01;
					TimePre = 2;
#endif
					if(DispCT==P_F_OPP_CurrTemp) {
						cnt1 = atof(KeyinBuf)-1;
						umax = 11;
						umin = 0;
						DataRedrawFlag =DATA_CHANGE;
					} else if(DispCT==P_F_OPP_StartCurr) {
						cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
						cnt1 /= Get_Parallel_Parameter(OPP->Range);
						umax = (ptrMODEL_TYPE->CP)[0].Max-1;
						umin = (ptrMODEL_TYPE->CP)[0].Min;
					} else if(DispCT==P_F_OPP_EndCurr) {
						cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
						cnt1 /= Get_Parallel_Parameter(OPP->Range);
						umax = (ptrMODEL_TYPE->CP)[0].Max;
						umin = (ptrMODEL_TYPE->CP)[0].Min+2;
					} else if(DispCT==P_F_OPP_StepCurr) {
						cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
						cnt1 /= Get_Parallel_Parameter(OPP->Range);
						umax = (ptrMODEL_TYPE->CP)[0].Max/2;
						umin = (ptrMODEL_TYPE->CP)[0].Min+1;
					} else if(DispCT==P_F_OPP_StepTime) {
						cnt1 = InputToStep(atof(KeyinBuf),TimeRes);
						umax = 5000;
						umin = 1;
					} else if(DispCT==P_F_OPP_TrigVolt) {
						cnt1 = InputToStep(atof(KeyinBuf),VoltRes);
						umax = (ptrMODEL_TYPE->CV)[3].Max/21*20;
						umin = 1;
					} else if(DispCT==P_F_OPP_DelayTrig) {
						cnt1 = InputToStep(atof(KeyinBuf),TimeRes);
						umax = 500;
						cnt2 = GetChanData(P_F_OPP_StepTime,0);
						if(umax>=cnt1)umax = cnt2-1;
						umin = 0;
					} else if(DispCT==P_F_OPP_LastCurr) {
						cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
						cnt1 /= Get_Parallel_Parameter(OPP->Range);
						umax = (ptrMODEL_TYPE->CP)[0].Max;
						umin = (ptrMODEL_TYPE->CP)[0].Min;
					}
					if(cnt1>umax)		cnt1 = umax;
					else if(cnt1<umin)	cnt1 = umin;
					SaveChanData(DispCT, cnt1);
					KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
				}
			}
			DataRedrawFlag |= PARA_CHANGE;
			if(DispMode==DispMode_SELECT_CH)	DataRedrawFlag |= DATA_CHANGE;
			break;
#endif
	
#if Enable_Battery_Discharge
		case P_FUNC_batt:
			DispMode++;
			if(DispMode>DispMode_SET_PARAMETERS) {
				DispMode = DispMode_BROWSE_ITEMS;
				if( KeyInFlag & DIGI_KEY_IN) {
					KeyInFlag &= ~DIGI_KEY_IN;
					I_Range = BattDisp.Range%2;
					V_Range = BattDisp.Range/2;
					if(DispCT==P_F_BATT_StopV) {
						cnt1 = InputToStep(atof(KeyinBuf),0.01);
						//cnt1 /= Get_Parallel_Parameter(I_Range);
						umax = 15000;
						umin = 1;
						if(cnt1>umax)		cnt1 = umax;
						else if(cnt1<umin)	cnt1 = umin;
						BattDisp.StopValt = cnt1;
					} else if(DispCT==P_F_BATT_StopT) { 				
						if(BattDisp.timeCnt==0) {							
							cnt1 = InputToStep(atof(KeyinBuf),1);
							umax = 999;
							umin = 0;
						} else if(BattDisp.timeCnt==1) {
							cnt1 = InputToStep(atof(KeyinBuf),1);
							umax = 59;
							umin = 0;
						} else {
							cnt1 = InputToStep(atof(KeyinBuf),1);
							umax = 59;
							umin = 0;
						}					
					} else if(DispCT==P_F_BATT_StopC) {
						cnt1 = InputToStep(atof(KeyinBuf),0.01);
						umax = 50000;
						umin = 0;
						if(cnt1>999999) 	cnt1 = 999999;
						else if(cnt1<umin)	cnt1 = umin;
					} else {
						if(CC_MODE == BattDisp.Mode){
							if(DispCT==P_F_BATT_Set) {
								umax = (ptrMODEL_TYPE->CC)[10*I_Range].Max;
								umin = (ptrMODEL_TYPE->CC)[10*I_Range].Min;
								CurrRes = (ptrMODEL_TYPE->CC)[10*I_Range].Resolution;
								cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
								cnt1 /= Get_Parallel_Parameter(I_Range);
							} else if((DispCT==P_F_BATT_SRUP)||(DispCT==P_F_BATT_SRDW)) {
								umax = (ptrMODEL_TYPE->CC)[2+10*I_Range].Max;
								umin = (ptrMODEL_TYPE->CC)[2+10*I_Range].Min;								
								cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CC)[2+(I_Range*10)].Resolution);
								//cnt1 /= Get_Parallel_Parameter(I_Range);
								//SR_Max = umax*100;								
								if(DispCT==P_F_BATT_SRUP)
									handle_sr_enter(&cnt1,SR_Max, &BattDisp.SRUPRange,&BattDisp.SRUP, umax,umin);
								else
									handle_sr_enter(&cnt1,SR_Max, &BattDisp.SRDWRange,&BattDisp.SRDW, umax,umin);
							} 
						} else if(CR_MODE == BattDisp.Mode){
							if(DispCT==P_F_BATT_Set) {
								umax = (ptrMODEL_TYPE->CR)[10*I_Range].Max;
								umin = (ptrMODEL_TYPE->CR)[10*I_Range].Min;
								CurrRes = (ptrMODEL_TYPE->CR)[10*I_Range].Resolution;
								cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
								cnt1 /= Get_Parallel_Parameter(I_Range);
							} else if((DispCT==P_F_BATT_SRUP)||(DispCT==P_F_BATT_SRDW)){
								umax = (ptrMODEL_TYPE->CR)[2+10*I_Range].Max;
								umin = (ptrMODEL_TYPE->CR)[2+10*I_Range].Min;								
								cnt1 = InputToStep(atof(KeyinBuf),(ptrMODEL_TYPE->CR)[2+(I_Range*10)].Resolution);
								//cnt1 /= Get_Parallel_Parameter(I_Range);
								//SR_Max = umax*100;								
								if(DispCT==P_F_BATT_SRUP)
									handle_sr_enter(&cnt1,SR_Max, &BattDisp.SRUPRange,&BattDisp.SRUP, umax,umin);
								else
									handle_sr_enter(&cnt1,SR_Max, &BattDisp.SRDWRange,&BattDisp.SRDW, umax,umin);
							}
						}else { //CP MODE
							if(DispCT==P_F_BATT_Set) {
								umax = (ptrMODEL_TYPE->CP)[10*I_Range].Max;
								umin = (ptrMODEL_TYPE->CP)[10*I_Range].Min;
								CurrRes = (ptrMODEL_TYPE->CP)[10*I_Range].Resolution;
								cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
								cnt1 /= Get_Parallel_Parameter(I_Range);
							} 
						}						
					}
					if((DispCT!=P_F_BATT_SRUP)&&(DispCT!=P_F_BATT_SRDW)&&(DispCT!=P_F_BATT_StopC)){
						if(cnt1>umax)		cnt1 = umax;
						else if(cnt1<umin)	cnt1 = umin;
					}
					SaveChanData(DispCT, cnt1);
					KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
				}
				if(DispCT==P_F_BATT_StopT) {					
					if(BattDisp.timeCnt==0) {							
						BattDisp.timeCnt=1;
						DispMode =DispMode_SET_PARAMETERS;
					} else if(BattDisp.timeCnt==1) {							
						BattDisp.timeCnt=2;
						DispMode =DispMode_SET_PARAMETERS;
					} else {
						BattDisp.timeCnt=0; 						
					}	
				}
					
			}			
			DataRedrawFlag |= PARA_CHANGE;
			if(DispMode==DispMode_BROWSE_ITEMS) DataRedrawFlag |= DATA_CHANGE;
			break;	
#endif
#if Enable_LED_function
		case P_FUNC_FLED:
			DispMode++;
			if(DispMode>DispMode_SET_PARAMETERS) {
				DispMode = DispMode_BROWSE_ITEMS;
				if( KeyInFlag & DIGI_KEY_IN) {
					KeyInFlag &= ~DIGI_KEY_IN;					
					if(DispCT==P_F_LED_RESPONSE){ //Vo
						umax = RESPONSE_FAST;
						umin = RESPONSE_SLOW;
						CurrRes = 1;
						cnt1 = InputToStep(atof(KeyinBuf),CurrRes); 
					}											 
					if(cnt1>umax)		cnt1 = umax;
					else if(cnt1<umin)	cnt1 = umin;
					SaveChanData(DispCT, cnt1);
					KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
				}					
				if(DispCT==P_F_LED_Range) recall_default_parameter(DispCT);
				//SEQ_Save_Status	= 1;
				//MenuRedrawFlag |= MENU3_CHANGE;
				
			} else if( (DispMode==DispMode_SET_PARAMETERS)&&(DispCT==P_F_LED_Momo)) {
				for(i=0 ; i<12 ; i++) {
					if(P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp].name[i]==0)
						break;
					KeypadSTR[i] = P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp].name[i];
				}
				for( ; i<13 ; i++)
					KeypadSTR[i] = 0;
				Soft_Key_Temp		= 0;
				//SEQ_Save_Status = 1;
				DispMode			= DispMode_SELECT_CH;
				K_M_num 			= M_num;
				M_num			= P_UTIL_KEYPAD;
				MenuRedrawFlag		|= MENU_CHANGE;
				KeypadRedrawFlag	|= KEYPAD_UPDATA;		
			}					
			DataRedrawFlag |= PARA_CHANGE;
			if(DispMode==DispMode_BROWSE_ITEMS) DataRedrawFlag |= DATA_CHANGE;
			break;
		case P_FUNC_FLED_EDIT:
		case P_FUNC_FLED_EXECUTE:	
			DispMode++;
			if(DispMode>DispMode_SET_PARAMETERS) {
				DispMode = DispMode_BROWSE_ITEMS;
				V_Range = P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp].range / 2;
				I_Range = P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp].range % 2;	
				if( KeyInFlag & DIGI_KEY_IN) {
					KeyInFlag &= ~DIGI_KEY_IN;
					switch(P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp].mode){
						case P_F_LED_MODE_VoIo:
						case P_F_LED_MODE_VoIoRc:	
							if(DispCT==P_F_LED_Edit_P1){ //Vo
								umax = (ptrMODEL_TYPE->CV)[0].Max;
								umin = (ptrMODEL_TYPE->CV)[0].Min;
								CurrRes = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
								cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
							}else if(DispCT==P_F_LED_Edit_P2){//Io	
								umax = (ptrMODEL_TYPE->CC)[0].Max;
								umin = (ptrMODEL_TYPE->CC)[0].Min;
								CurrRes = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
								cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
								cnt1 /= Get_Parallel_Parameter(I_Range);
							}else if(DispCT==P_F_LED_Edit_P3) {//Rcoff
								umax = 10000;
								umin = 1;
								CurrRes = 0.01;
								cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
							}
							break;					
						case P_F_LED_MODE_VoIoRd:
							if(DispCT==P_F_LED_Edit_P1){//Vo
								umax = (ptrMODEL_TYPE->CV)[0].Max;
								umin = (ptrMODEL_TYPE->CV)[0].Min;
								CurrRes = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
								cnt1 = InputToStep(atof(KeyinBuf),CurrRes);		
							}else if(DispCT==P_F_LED_Edit_P2){//Io	
								umax = (ptrMODEL_TYPE->CC)[0].Max;
								umin = (ptrMODEL_TYPE->CC)[0].Min;
								CurrRes = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
								cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
								cnt1 /= Get_Parallel_Parameter(I_Range);		
							}else if(DispCT==P_F_LED_Edit_P3) {//Rd
								umax = (ptrMODEL_TYPE->CR)[0].Max;
								umin = (ptrMODEL_TYPE->CR)[0].Min;
								CurrRes = (ptrMODEL_TYPE->CR)[V_Range*10].Resolution;
								cnt1 = InputToStep((1000/atof(KeyinBuf)),CurrRes);
								cnt1 /= Get_Parallel_Parameter(I_Range);	
							}
							break;
						case P_F_LED_MODE_VoIoVf:
							if(DispCT==P_F_LED_Edit_P1){//Vo
								umax = (ptrMODEL_TYPE->CV)[0].Max;
								umin = GetChanData(P_F_LED_Edit_P3,0)+1;	
								CurrRes = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
								cnt1 = InputToStep(atof(KeyinBuf),CurrRes);		
							}else if(DispCT==P_F_LED_Edit_P2){//Io	
								umax = (ptrMODEL_TYPE->CC)[0].Max;
								umin = (ptrMODEL_TYPE->CC)[0].Min;
								CurrRes = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
								cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
								cnt1 /= Get_Parallel_Parameter(I_Range);	
							}else if(DispCT==P_F_LED_Edit_P3) {//Vf
								umax = GetChanData(P_F_LED_Edit_P1,0)-1;
								umin = (ptrMODEL_TYPE->CV)[0].Min;
								CurrRes = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
								cnt1 = InputToStep(atof(KeyinBuf),CurrRes);			
							}
							break;
						case P_F_LED_MODE_VfRdPcs:
							if(DispCT==P_F_LED_Edit_P1){ //Vf
								umax = (ptrMODEL_TYPE->CV)[0].Max;
								umin = (ptrMODEL_TYPE->CV)[0].Min;
								CurrRes = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
								cnt1 = InputToStep(atof(KeyinBuf),CurrRes);	 
							}else if(DispCT==P_F_LED_Edit_P2){//Rd	
								umax = (ptrMODEL_TYPE->CR)[0].Max;
								umin = (ptrMODEL_TYPE->CR)[0].Min;
								CurrRes = (ptrMODEL_TYPE->CR)[V_Range*10].Resolution;
								cnt1 = InputToStep((1000/atof(KeyinBuf)),CurrRes);
								cnt1 /= Get_Parallel_Parameter(I_Range);		 
							}else if(DispCT==P_F_LED_Edit_P3) {//pcs
								umax = 1000;
								umin = 1;
								CurrRes = 1;
								cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
							}
							break;
						default:
							break;	
					}					 
					if(cnt1>umax)		cnt1 = umax;
					else if(cnt1<umin)	cnt1 = umin;
					SaveChanData(DispCT, cnt1);
					KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
				}
				//SEQ_Save_Status	= 1;
				//MenuRedrawFlag |= MENU3_CHANGE;
				
			} 					
			DataRedrawFlag |= PARA_CHANGE ; 
			
			if(DispMode<=DispMode_SET_PARAMETERS)B_DispCT = DispCT;
			if(DispMode==DispMode_BROWSE_ITEMS)
				DataRedrawFlag |= DATA_CHANGE;			
			if(UTILITY.LOAD_CTL)set_func_fled_ad();
			break;
		case P_FUNC_CLED:
			DispMode++;
			if(DispMode>DispMode_SET_PARAMETERS) {
				DispMode = DispMode_BROWSE_ITEMS;
				if( KeyInFlag & DIGI_KEY_IN) {
					KeyInFlag &= ~DIGI_KEY_IN;
					V_Range = P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].range / 2;
					I_Range = P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].range % 2;
					if(DispCT==P_CLED_RESPONSE){ //Vo
						umax = RESPONSE_FAST;
						umin = RESPONSE_SLOW;
						CurrRes = 1;
						cnt1 = InputToStep(atof(KeyinBuf),CurrRes);	
					}else if(DispCT==P_CLED_VO){ //Vo
						umax = (ptrMODEL_TYPE->CV)[0].Max;
						umin = (ptrMODEL_TYPE->CV)[0].Min;
						CurrRes = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
						cnt1 = InputToStep(atof(KeyinBuf),CurrRes);	
						//find_curve_led_paramter(P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].rdcoff);	
					}else if(DispCT==P_CLED_IO){//Io	
						umax = (ptrMODEL_TYPE->CC)[0].Max;
						umin = (ptrMODEL_TYPE->CC)[0].Min;
						CurrRes = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
						cnt1 = InputToStep(atof(KeyinBuf),CurrRes);
						cnt1 /= Get_Parallel_Parameter(I_Range);	
						//find_curve_led_paramter(P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].rdcoff);
					}					
										 
					if(cnt1>umax)		cnt1 = umax;
					else if(cnt1<umin)	cnt1 = umin;
					SaveChanData(DispCT, cnt1);
					///find_curve_led_paramter(P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].rdcoff);
					KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;

					

				}
				find_curve_led_paramter(P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].rdcoff);
				if(DispCT==P_CLED_Range){
					
				}
				
			} else if( (DispMode==DispMode_SET_PARAMETERS)&&(DispCT==P_CLED_Momo)) {
				for(i=0 ; i<12 ; i++) {
					if(P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].name[i]==0)
						break;
					KeypadSTR[i] = P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].name[i];
				}
				for( ; i<13 ; i++)
					KeypadSTR[i] = 0;
				Soft_Key_Temp		= 0;
				//SEQ_Save_Status = 1;
				DispMode			= DispMode_SELECT_CH;
				K_M_num 			= M_num;
				M_num			= P_UTIL_KEYPAD;
				MenuRedrawFlag		|= MENU_CHANGE;
				KeypadRedrawFlag	|= KEYPAD_UPDATA;		
			}					
			DataRedrawFlag |= PARA_CHANGE;
			if(DispMode==DispMode_BROWSE_ITEMS) DataRedrawFlag |= DATA_CHANGE;
			break;
		case P_FUNC_CLED_EDIT:
			DispMode++;
			if(DispMode>DispMode_SET_PARAMETERS) {
				DispMode = DispMode_BROWSE_ITEMS;
				if( KeyInFlag & DIGI_KEY_IN) {
					KeyInFlag &= ~DIGI_KEY_IN;
					//Rcoff
					umax = 7000;
					umin = 1000;
					CurrRes = 0.01;
					cnt1 = InputToStep(atof(KeyinBuf),CurrRes);							
					if(cnt1>umax)		cnt1 = umax;
					else if(cnt1<umin)	cnt1 = umin;
					SaveChanData(DispCT, cnt1);
					KeyinBuf[0] = KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
					find_curve_led_paramter(cnt1);	
				}
				//SEQ_Save_Status	= 1;
				//MenuRedrawFlag |= MENU3_CHANGE;				
			} 					
			DataRedrawFlag |= PARA_CHANGE ; 
			//if(DispMode==DispMode_BROWSE_ITEMS) DataRedrawFlag |= DATA_CHANGE;
			break;	
#endif

	default:
		break;
	}
}

#if Enable_Battery_Discharge

void handle_sr_enter (long* cnt,long SR_Max, UBYTE* Range_Point, UWORD* value1, UWORD max,UWORD min){	
	UBYTE Irang = (BattDisp.Range%2);
	long cnt1 = *cnt;	
	if(cnt1>max){
		cnt1 = max;
		*value1 = (cnt1/Get_Parallel_Parameter(Irang));
	}else if(cnt1<min){
		*value1 = min;
	}else{
		*value1 = (cnt1/Get_Parallel_Parameter(Irang));
	}	
}
#endif


void ScrollCnt_Select(char no,char max, char *start, char *end, char line)
{
	if(no == (max-1)) {
		*end = no;
		*start = no-line;
	} else if(no == 0) {
		*start = no;
		*end = no+line;
	}

	if(no > *end) {
		*end = *end+1;
		if( *end > max)
			*end = line;
		*start = *end - line;
	} else if(no < *start) {
		*start = *start - 1;
		if(*start < 0)
			*start = max - line+1;
		*end = *start + line;
	}
}

WORD Cnt_Select(BYTE cnt, WORD number, WORD max_num)
{
	if(cnt==0)
		return number;

	if(cnt<0)
		number--;
	else
		number++;

	if(number>=max_num)
		number = 0;
	else if(number<0)
		number = max_num - 1;

	return number;
}

WORD Cnt_Select2(BYTE cnt, WORD number, WORD max_num, WORD min_num)
{
	if(cnt==0)
		return number;

	if(cnt<0)
		number--;
	else
		number++;

	if(number>=max_num)
		number = max_num;
	else if(number<=min_num)
		number = min_num;

	return number;
}

ULONG Cnt_Select_Step(WORD cnt, LONG number, ULONG max_num, LONG min_num)
{
	LONG number_Temp = number;

	number_Temp += cnt;

	if(number_Temp > (LONG)max_num)
		number_Temp = (LONG)max_num;
	else if(number_Temp < (LONG)min_num)
		number_Temp = (LONG)min_num;
	return number_Temp;
}

LONG Cnt_Select_Timer(WORD cnt, LONG number, ULONG max_num, LONG min_num)
{
	LONG number_Temp = number;

	if(0==cnt)
		number_Temp = number;
	else if(cnt>0)
		number_Temp++;
	else
		number_Temp--;

	return number_Temp;
}


ULONG Cnt_Select_Slow(WORD cnt, ULONG number, ULONG max_num, ULONG min_num)
{
	LONG number_Temp = number;

	if(0==cnt)
		number_Temp = number;
	else if(cnt>0)
		number_Temp++;
	else
		number_Temp--;

	if(number_Temp>(LONG)max_num)
		number_Temp = (LONG)max_num;
	else if(number_Temp<(LONG)min_num)
		number_Temp = (LONG)min_num;

	return number_Temp;
}

WORD Scr_Cnt_Select(BYTE cnt, WORD number, WORD max_num, WORD min_num)
{
	if(cnt==0)
		return number;
#if 1
	if(cnt<0)
		number++;
	else
		number--;
#else
	number-=cnt;
#endif
	if(number>=max_num)
		number = max_num;
	else if(number<=min_num)
		number = min_num;

	return number;
}
void RestoreRealChan(void)
{
	char no,i;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	Disp_tmp->CC				= Data_tmp->CC;
	Disp_tmp->CR				= Data_tmp->CR;
	Disp_tmp->CV				= Data_tmp->CV;
	Disp_tmp->CP				= Data_tmp->CP;
	Disp_tmp->PROT				= Data_tmp->PROT;
	Disp_tmp->UTILITY			= Data_tmp->UTILITY;
	Disp_tmp->CONF   			= Data_tmp->CONF;
	Disp_tmp->CURRMODE			= Data_tmp->CURRMODE;
	Disp_tmp->P_F_Delay			= Data_tmp->P_F_Delay;
	Disp_tmp->Parallel_Unit		= Data_tmp->Parallel_Unit;
	Disp_tmp->UTILITY.B_ONOFF	= Data_tmp->UTILITY.B_ONOFF;
	Disp_tmp->IRange			= Data_tmp->IRange;
	Disp_tmp->VRange			= Data_tmp->VRange;
	Disp_tmp->SPEC				= Data_tmp->SPEC;
#if 1 //2014.10.23 by Adam
	Disp_tmp->SPECTYPE		= Data_tmp->SPECTYPE;
#endif
	Disp_tmp->Load_Type			= Data_tmp->Load_Type;
}

void GNGPcet2Step(char no)
{
	unsigned short center_val,val,h_val,l_val;
	unsigned short max,min;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	center_val	= (unsigned short)GetChanData((0+6), 0);	/*	CENTERVAL			*/
	val			= (unsigned short)GetChanData( no+9, 0); 	/*	HIPCET or LOWPCET	*/
	h_val		= (unsigned short)GetChanData( 7, 0); 		/*	High Value			*/
	l_val		= (unsigned short)GetChanData( 8, 0); 		/*	Low Value			*/

#if 1
	switch(M_num) {
	case P_CC_SPEC:
		max = ptrMODEL_TYPE->CC_SPEC[no+1].Max;
		min = ptrMODEL_TYPE->CC_SPEC[no+1].Min;
		break;
	case P_CR_SPEC:
		max = ptrMODEL_TYPE->CR_SPEC[no+1].Max;
		min = ptrMODEL_TYPE->CR_SPEC[no+1].Min;
		break;
	case P_CV_SPEC:
		max = ptrMODEL_TYPE->CV_SPEC[no+1].Max;
		min = ptrMODEL_TYPE->CV_SPEC[no+1].Min;
		break;
	case P_CP_SPEC:
		max = ptrMODEL_TYPE->CP_SPEC[no+1].Max;
		min = ptrMODEL_TYPE->CP_SPEC[no+1].Min;
		break;
	}
#endif
	switch(no) {
	case 0:		/* High value */
		/*  (Center Value * Pcet)/1000 + Center Value */
		val = ((center_val * val)/1000) + center_val;

		if( val >= max)			val = max;
		else if( val <= l_val)	val = l_val;

		SaveChanData(7, val);					/*Save High Value */
		break;
	case 1:		/* Low value */
		/* Center Value - (Cneter Value * Pcet)/1000 */
		val = center_val - ( center_val * val /1000);

		if( val <= 0)			val = 0;
		else if(val >= h_val)	val = h_val;
		SaveChanData(8, val);					/*Save Low Value */
		break;
	}
}

void GNGStep2Pcet(char no)
{
	unsigned short center_val, H_val,L_val,H_PCET,L_PCET;

	H_val = (unsigned short)GetChanData( 7, 0);				//High Value
	L_val = (unsigned short)GetChanData( 8, 0);				//Low Value

	center_val=(H_val+L_val)/2;

	SaveChanData( 6, center_val);      /*Save Centerval*/

	if((center_val>0)&&((H_val - center_val)>0))
		H_PCET=(double)( (H_val - center_val)*1000 ) / center_val/1.0;
	else
		H_PCET=0;

	if(H_PCET>1000)
		H_PCET=1000;

	SaveChanData( 9, H_PCET);      /*Save HIPCET*/

	if((center_val>0)&&((center_val - L_val)>0))
		L_PCET=(double)( (center_val - L_val)*1000 ) / center_val/1.0;
	else
		L_PCET=0;

	SaveChanData( 10, L_PCET);      /*Save LOWPCET*/

}

char GetNowRange(void)
{
	char tmp;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	tmp = (char)Disp_tmp->VRange;

	return(tmp);
}

void GetResolution(void)
{
	char str[100];
	UBYTE type,*rang;
	rang = &P3k_Chan_Data.IRange;
	type = P3k_Chan_Data.INFO.MACHTYPE;

	switch(type) {	
	case MODEL3031E:
		ptrMODEL_TYPE = &P1031E;
		Model_Number = MODEL3031E;
		break;
	case MODEL3032E:
		ptrMODEL_TYPE = &P1033E;
		Model_Number = MODEL3032E;
		break;
	default:
		ptrMODEL_TYPE = &P1031E;
		Model_Number = MODEL3031E;
		break;
	}
}

char get_chan_prec(BYTE cnt){
	BYTE precision;
	char cnt1,range;	
	UBYTE Seq_Mode_Temp;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UBYTE V_Range = Disp_tmp->VRange;
	UBYTE I_Range = Disp_tmp->IRange;

	switch(M_num){
		case P_CC:
			if(cnt<=CCCR_Dyn_SRDN)
				range = I_Range;
			else if(cnt==CCCR_Dyn_T1)
				range = Disp_tmp->CC.DYNA[Disp_tmp->IRange].T1_RANGE;
			else
				range = Disp_tmp->CC.DYNA[Disp_tmp->IRange].T2_RANGE;

			cnt1 = cnt+(range*10)+(Disp_tmp->CC.STADYNA*4);

			if(((Disp_tmp->CONF.Dyna_Level) && (cnt == CCCR_Dyn_L2) && (Disp_tmp->CC.STADYNA==Function_Dynamic)) || ((Disp_tmp->CONF.Dyna_Time) && (cnt == CCCR_Dyn_T2) && (Disp_tmp->CC.STADYNA==Function_Dynamic)))
				precision = 1;
			else if((Disp_tmp->CONF.Dyna_Time) && (cnt == CCCR_Dyn_T1) && (Disp_tmp->CC.STADYNA==Function_Dynamic)) {
				if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_100Hz)
					precision = 0;
				else if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_10Hz)
					precision = 0;
				else if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_1Hz)
					precision = 0;
				else
					precision = 1;
			} else
				precision = (ptrMODEL_TYPE->CC)[cnt1].precision;

			if( ((Disp_tmp->CC.STADYNA==Function_Dynamic)&&(cnt==CCCR_Dyn_Add_CV))||((Disp_tmp->CC.STADYNA==Function_Static)&&(cnt==CCCR_Sta_Add_CV)) ) {
				precision = (ptrMODEL_TYPE->CV)[V_Range*3].precision;
			} 
			break; 
		case P_CV:
			cnt1 = cnt+(V_Range*3);
			precision = (ptrMODEL_TYPE->CV)[cnt1].precision;
			break;
		case P_CR:
			if(cnt<=CCCR_Dyn_SRDN)
				range = Disp_tmp->IRange;
			else if(cnt==CCCR_Dyn_T1)
				range = Disp_tmp->CR.DYNA[Disp_tmp->IRange].T1_RANGE;
			else
				range = Disp_tmp->CR.DYNA[Disp_tmp->IRange].T2_RANGE;

			cnt1 = cnt+(range*10)+(Disp_tmp->CR.STADYNA*4);

			if(((Disp_tmp->CONF.Dyna_Level) && (cnt == CCCR_Dyn_L2) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) || ((Disp_tmp->CONF.Dyna_Time) && (cnt == CCCR_Dyn_T2) && (Disp_tmp->CR.STADYNA==Function_Dynamic)))
				precision = 1;
			else if((Disp_tmp->CONF.Dyna_Time) && (cnt == CCCR_Dyn_T1) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) {
				if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_100Hz)
					precision = 0;
				else if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_10Hz)
					precision = 0;
				else if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_1Hz)
					precision = 0;
				else
					precision = 1;
			} else
				precision = (ptrMODEL_TYPE->CR)[cnt1].precision;
			if(((Disp_tmp->CR.STADYNA==Function_Dynamic)&&(cnt==CCCR_Dyn_Add_CV))||((Disp_tmp->CR.STADYNA==Function_Static)&&(cnt==CCCR_Sta_Add_CV))) {
				precision = (ptrMODEL_TYPE->CV)[V_Range*3].precision;
			}
			break;
		case P_CP:
			if(cnt<=CP_Dyn_L2) {
				//range = Disp_tmp->IRange;
				cnt1 = cnt+(I_Range)*10+(Disp_tmp->CP.STADYNA*4);
			} else if(cnt==CP_Dyn_T1) {
				range = Disp_tmp->CP.DYNA[Disp_tmp->IRange].T1_RANGE;
				cnt1 = cnt+(range)*10+(Disp_tmp->CP.STADYNA*6);
			} else if(cnt==CP_Dyn_T2) {
				range = Disp_tmp->CP.DYNA[Disp_tmp->IRange].T2_RANGE;
				cnt1 = cnt+(range)*10+(Disp_tmp->CP.STADYNA*6);
			}

			if(((Disp_tmp->CONF.Dyna_Level) && (cnt == CP_Dyn_L2) && (Disp_tmp->CP.STADYNA==Function_Dynamic)) || ((Disp_tmp->CONF.Dyna_Time) && (cnt == CP_Dyn_T2) && (Disp_tmp->CP.STADYNA==Function_Dynamic)))
				precision = 1;
			else if((Disp_tmp->CONF.Dyna_Time) && (cnt == CP_Dyn_T1) && (Disp_tmp->CP.STADYNA==Function_Dynamic)) {
				if(Disp_tmp->CP.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_100Hz)
					precision = 0;
				else if(Disp_tmp->CP.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_10Hz)
					precision = 0;
				else if(Disp_tmp->CP.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_1Hz)
					precision = 0;
				else
					precision = 1;
			} else
				precision = (ptrMODEL_TYPE->CP)[cnt1].precision;

			if(((Disp_tmp->CP.STADYNA==Function_Dynamic)&&(cnt==CP_Dyn_Add_CV))||((Disp_tmp->CP.STADYNA==Function_Static)&&(cnt==CP_Sta_Add_CV))) {
				precision = (ptrMODEL_TYPE->CV)[V_Range*3].precision;
			}
			break;
		case P_CC_SPEC:
			precision = (ptrMODEL_TYPE->CC_SPEC)[cnt].precision;
			break;
		case P_CR_SPEC:
			precision = (ptrMODEL_TYPE->CR_SPEC)[cnt].precision;
			break;
		case P_CV_SPEC:
			precision = (ptrMODEL_TYPE->CV_SPEC)[cnt].precision;
			break;
		case P_CP_SPEC:
			precision = (ptrMODEL_TYPE->CP_SPEC)[cnt].precision;
			break;
		case P_CONF_OTHER:
			if(P_SOFT_START == cnt)
				precision = ptrMODEL_TYPE->CONF[2].precision;
			else if(P_VON_VOLTAGE == cnt)
				precision = ptrMODEL_TYPE->CONF[V_Range].precision;
			else if(P_CUTOFFTIME == cnt)
				precision = ptrMODEL_TYPE->CONF[3].precision;
			else if(P_Von_Delay == cnt)
				precision = 3;
			break;
		case P_CONF_PROT:
			if(cnt==P_OCP_LEVEL)
				precision = ptrMODEL_TYPE->PROT[PROT_OCP_H].precision;
			else if(cnt==P_OPP_LEVEL)
				precision = ptrMODEL_TYPE->PROT[PROT_OPP_H].precision;
			else if(cnt==P_UVP_LEVEL) {
				if(VRange_Low==Data_tmp->VRange)
					precision = ptrMODEL_TYPE->PROT[PROT_UVP_L].precision;
				else
					precision = ptrMODEL_TYPE->PROT[PROT_UVP_H].precision;
#if Enable_Ring_Count
			}else if(cnt==P_UVP_SETTING){
				precision = 0;
#endif

			} else if(cnt==P_OVP_LEVEL) {
				if(VRange_Low==Data_tmp->VRange)
					precision = ptrMODEL_TYPE->PROT[PROT_OVP_L].precision;
				else
					precision = ptrMODEL_TYPE->PROT[PROT_OVP_H].precision;
			}
			break;
		case P_CONF_KNOB:
			if (cnt==P_CCH_STEP)
				precision = (ptrMODEL_TYPE->CC)[10].precision;
			else if (cnt==P_CCL_STEP)
				precision = (ptrMODEL_TYPE->CC)[0].precision;
			else if (cnt==P_CRH_STEP)
				precision = (ptrMODEL_TYPE->CR)[10].precision;
			else if (cnt==P_CRL_STEP)
				precision = (ptrMODEL_TYPE->CR)[0].precision;
			else if (cnt==P_CVH_STEP)
				precision = (ptrMODEL_TYPE->CV)[3].precision;
			else if (cnt==P_CVL_STEP)
				precision = (ptrMODEL_TYPE->CV)[0].precision;
			else if (cnt==P_CPH_STEP)
				precision = (ptrMODEL_TYPE->CP)[10].precision;
			else if (cnt==P_CPL_STEP)
				precision = (ptrMODEL_TYPE->CP)[0].precision;
			break;
		case P_NSeq_Edit:
		case P_Seq_Normal:
			V_Range = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Range/2;
			I_Range = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Range%2;
			Seq_Mode_Temp = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode;
			if(CC_MODE==Seq_Mode_Temp)
				precision = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
			else if(CR_MODE==Seq_Mode_Temp)
				precision = (ptrMODEL_TYPE->CR)[I_Range*10].precision;
			else if(CV_MODE==Seq_Mode_Temp)
				precision = (ptrMODEL_TYPE->CV)[V_Range*3].precision;
			else
				precision = (ptrMODEL_TYPE->CP)[I_Range*10].precision;	/*CP_MODE*/
			break;
		case P_Seq_Fast:
		case P_FSeq_Edit:
		case P_FSeq_Fill:
			if(cnt==P_FSeq_TimeBase)
				precision = P3k_FSeq_Disp.FSeq_TB_Range+5;
			else { /*P_FSeq_Last_Set and P_FSeqEdit_Value*/
				V_Range = P3k_FSeq_Disp.FSeq_Range/2;
				I_Range = P3k_FSeq_Disp.FSeq_Range%2;
				Seq_Mode_Temp = P3k_FSeq_Disp.FSeq_Mode;
				if(CC_MODE==Seq_Mode_Temp)
					precision = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
				else
					precision = (ptrMODEL_TYPE->CR)[I_Range*10].precision;/*CR_MODE*/
				
			}
			break;
#if Enable_Battery_Discharge
		case P_FUNC_batt:
		case P_FUNC_batt_EXECUTE:
			Seq_Mode_Temp = BattDisp.Mode;
			V_Range = BattDisp.Range/2;
			I_Range = BattDisp.Range%2;

			if(Seq_Mode_Temp==CC_MODE){
				if(cnt==P_F_BATT_Set){
					precision = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
				}else if(cnt==P_F_BATT_SRUP){
					precision = (ptrMODEL_TYPE->CC)[I_Range*10+2].precision;
				}else if(cnt==P_F_BATT_SRDW){			
					precision = (ptrMODEL_TYPE->CC)[I_Range*10+2].precision;
				}
			}else if(Seq_Mode_Temp==CR_MODE){
				if(cnt==P_F_BATT_Set){
					precision = (ptrMODEL_TYPE->CR)[I_Range*10].precision;
				}else if(cnt==P_F_BATT_SRUP){
					precision = (ptrMODEL_TYPE->CR)[I_Range*10+2].precision;
				}else if(cnt==P_F_BATT_SRDW){			
					precision = (ptrMODEL_TYPE->CR)[I_Range*10+2].precision;
				}
			}else{ //cp_mode
				if(cnt==P_F_BATT_Set){
					precision = (ptrMODEL_TYPE->CP)[I_Range*10].precision;
				}
			}	
			break;
#endif	
#if Enable_LED_function
		case P_FUNC_FLED:
			//Seq_Mode_Temp = P3k_FLed_Data.Seq.mode;
			V_Range = P3k_FLed_Disp.seq[0].range/2;
			I_Range = P3k_FLed_Disp.seq[0].range%2;	
		
			if(cnt==P_F_LED_RESPONSE){
				precision = (ptrMODEL_TYPE->CC)[I_Range*10+2].precision;
			}	
			break;
		case P_FUNC_FLED_EDIT:
		case P_FUNC_FLED_EXECUTE:
			switch(P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp].mode){
				case P_F_LED_MODE_VoIo:
				case P_F_LED_MODE_VoIoRc:	
					if(cnt==P_F_LED_Edit_P1){ //Vo
						precision = (ptrMODEL_TYPE->CV)[0].precision; 	
					}else if(cnt==P_F_LED_Edit_P2){//Io 
						precision = (ptrMODEL_TYPE->CC)[0].precision;
					}else if(cnt==P_F_LED_Edit_P3) {//Rcoff
						precision = 2;	
					}
					break;					
				case P_F_LED_MODE_VoIoRd:
					if(cnt==P_F_LED_Edit_P1){//Vo
						precision = (ptrMODEL_TYPE->CV)[0].precision; 
					}else if(cnt==P_F_LED_Edit_P2){//Io 
						precision = (ptrMODEL_TYPE->CC)[0].precision; 
					}else if(cnt==P_F_LED_Edit_P3) {//Rd
						precision = 7;
					}
					break;
				case P_F_LED_MODE_VoIoVf:
					if(cnt==P_F_LED_Edit_P1){//Vo
						precision = (ptrMODEL_TYPE->CV)[0].precision; 	
					}else if(cnt==P_F_LED_Edit_P2){//Io 
						precision = (ptrMODEL_TYPE->CC)[0].precision;
					}else if(cnt==P_F_LED_Edit_P3) {//Vf
						precision = (ptrMODEL_TYPE->CV)[0].precision; 	
					}
					break;
				case P_F_LED_MODE_VfRdPcs:
					if(cnt==P_F_LED_Edit_P1){ //Vf
						precision = (ptrMODEL_TYPE->CV)[0].precision;
					}else if(cnt==P_F_LED_Edit_P2){//Rd 
						precision = 7;
					}else if(cnt==P_F_LED_Edit_P3) {//pcs
						precision = 0;
					}
					break;
				default:
					break;	
			}
			break;
		case P_FUNC_CLED:
			if(cnt==P_CLED_VO){ //Vo
				precision = (ptrMODEL_TYPE->CV)[0].precision;	
			}else if(cnt==P_CLED_IO){
				precision = (ptrMODEL_TYPE->CC)[0].precision;
			}
			break;	
		case P_FUNC_CLED_EDIT:
			precision = 2;
			break;
		case P_FUNC_CLED_EXECUTE:
			if(cnt==P_CLED_EXE_VO){ //Vo
				precision = (ptrMODEL_TYPE->CV)[0].precision;	
			}else if(cnt==P_CLED_EXE_IO){
				precision = (ptrMODEL_TYPE->CC)[0].precision;
			}else{
				precision = 2;
			}
			break;	
			
#endif	
	}
	return precision;
}



long GetChanData(BYTE cnt, BYTE cnt1)
{
	long tmp;
	UBYTE I_Range,V_Range;
	UWORD *tmp1, *tmp2;
	UWORD Curr_Number;
	UBYTE currTemp;
	NSeq_Timing_Str *NSeq_Timing_Ptr;
	NSeq_Data_Str	*NSeq_Data_Ptr;
	FSeq_Data_Str	*FSeq_Data_Ptr;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Prog_Str	*Prog_tmp = &p3k_Disp_PROG;

	V_Range = Disp_tmp->VRange;
	I_Range = Disp_tmp->IRange;

	switch(M_num) {
	case P_CC:	/* CC Mode */
		if(Disp_tmp->CC.STADYNA)
			tmp1 = &Disp_tmp->CC.DYNA[I_Range].LEVEL1;
		else
			tmp1 = &Disp_tmp->CC.STA[I_Range].VALUE1;

		if( ((Disp_tmp->CC.STADYNA==Function_Dynamic)&&(cnt==CCCR_Dyn_Add_CV))||((Disp_tmp->CC.STADYNA==Function_Static)&&(cnt==CCCR_Sta_Add_CV)) ) {
			if(!Data_tmp->CONF.CV_Func_En)
				tmp = -1;
			else
				tmp = Disp_tmp->CV.STA[V_Range].VALUE1;
		} else if( ((Disp_tmp->CC.STADYNA==Function_Dynamic)&&(cnt==CCCR_Dyn_CV_Response))||((Disp_tmp->CC.STADYNA==Function_Static)&&(cnt==CCCR_Sta_CV_Response)) ) {
			tmp = Disp_tmp->CC.CXCV_RESPOSNE;
		} else {
			if((Disp_tmp->CONF.Dyna_Level) && (cnt == CCCR_Dyn_L2) && (Disp_tmp->CC.STADYNA == Function_Dynamic))
				tmp = Disp_tmp->CC.DYNA[I_Range].Level_Percent;
			else if((Disp_tmp->CONF.Dyna_Time) && (cnt == CCCR_Dyn_T2) && (Disp_tmp->CC.STADYNA == Function_Dynamic))
				tmp = Disp_tmp->CC.DYNA[I_Range].Duty;
			else if((Disp_tmp->CONF.Dyna_Time) && (cnt == CCCR_Dyn_T1) && (Disp_tmp->CC.STADYNA == Function_Dynamic))
				tmp = Disp_tmp->CC.DYNA[I_Range].Frequency;
			else
				tmp = *(tmp1 + cnt);
		}
		break;
	case P_CC_SPEC: /* CC Go-NoGo */
		if(Disp_tmp->CC.STADYNA)
			tmp1 = &Disp_tmp->CC.DYNA[I_Range].CENTERVAL;
		else
			tmp1 = &Disp_tmp->CC.STA[I_Range].CENTERVAL;
		tmp = *(tmp1 + (cnt -6) );
		break;
	case P_CR:	/* CR Mode */
		if(Disp_tmp->CR.STADYNA)
			tmp1 = &Disp_tmp->CR.DYNA[I_Range].LEVEL1;
		else
			tmp1 = &Disp_tmp->CR.STA[I_Range].VALUE1;

		if( ((Disp_tmp->CR.STADYNA==Function_Dynamic)&&(cnt==CCCR_Dyn_Add_CV))||((Disp_tmp->CR.STADYNA==Function_Static)&&(cnt==CCCR_Sta_Add_CV)) ) {
			if(!Data_tmp->CONF.CV_Func_En)
				tmp = -1;
			else
				tmp = Disp_tmp->CV.STA[V_Range].VALUE1;
		} else if( ((Disp_tmp->CR.STADYNA==Function_Dynamic)&&(cnt==CCCR_Dyn_CV_Response))||((Disp_tmp->CR.STADYNA==Function_Static)&&(cnt==CCCR_Sta_CV_Response)) ) {
			tmp = Disp_tmp->CR.CXCV_RESPOSNE;
		} else {
			if((Disp_tmp->CONF.Dyna_Level) && (cnt == CCCR_Dyn_L2) && (Disp_tmp->CR.STADYNA == Function_Dynamic))
				tmp = Disp_tmp->CR.DYNA[I_Range].Level_Percent;
			else if((Disp_tmp->CONF.Dyna_Time) && (cnt == CCCR_Dyn_T2) && (Disp_tmp->CR.STADYNA == Function_Dynamic))
				tmp = Disp_tmp->CR.DYNA[I_Range].Duty;
			else if((Disp_tmp->CONF.Dyna_Time) && (cnt == CCCR_Dyn_T1) && (Disp_tmp->CR.STADYNA == Function_Dynamic))
				tmp = Disp_tmp->CR.DYNA[I_Range].Frequency;
			else
				tmp = *(tmp1 + cnt);
		}
		break;
	case P_CR_SPEC: /* CR Go-NoGo */		/* CR Go-NoGo range was same with CR mode */
		if(Disp_tmp->CR.STADYNA)
			tmp1 = &Disp_tmp->CR.DYNA[I_Range].CENTERVAL;
		else
			tmp1 = &Disp_tmp->CR.STA[I_Range].CENTERVAL;
		tmp = *(tmp1 + (cnt -6) );
		break;
	case P_CV:	/* CV Mode */
		if(Disp_tmp->CV.STADYNA)
			tmp1 = &Disp_tmp->CV.DYNA[V_Range].LEVEL1;
		else
			tmp1 = &Disp_tmp->CV.STA[V_Range].VALUE1;
		tmp = *(tmp1 + cnt);
		break;
	case P_CV_SPEC: /* CV Go-NoGo */
		tmp1 = &Disp_tmp->CV.STA[V_Range].CENTERVAL;
		tmp = *(tmp1 + (cnt -6) );
		break;
	case P_CP:	/* CP Mode */
		tmp1 = &Disp_tmp->CP.STA[I_Range].VALUE1;
		if(cnt==CP_Sta_Add_CV) {
			if(!Data_tmp->CONF.CV_Func_En)
				tmp = -1;
			else
				tmp = Disp_tmp->CV.STA[V_Range].VALUE1;
		} else if(cnt==CP_Sta_CV_Response) {
			tmp = Disp_tmp->CP.CXCV_RESPOSNE;
		} else {
			tmp = *(tmp1 + cnt);
		}
		break;
	case P_CP_SPEC: /* CP Go-NoGo */
		if(Disp_tmp->CP.STADYNA)
			tmp1 = &Disp_tmp->CP.DYNA[I_Range].CENTERVAL;
		else
			tmp1 = &Disp_tmp->CP.STA[I_Range].CENTERVAL;
		tmp = *(tmp1 + (cnt -6) );
		break;
	case P_CONF_PROT:	/* Protection Status */
		switch(cnt) {
		case P_OCP_LEVEL:
			tmp = Disp_tmp->PROT.OCP[HIGH_RANGE];
			break;
		case P_OCP_SETTING:
			tmp = Disp_tmp->PROT.OCP_SET;
			break;
		case P_OPP_LEVEL:
			tmp = Disp_tmp->PROT.OPP[HIGH_RANGE];
			break;
		case P_OPP_SETTING:
			tmp = Disp_tmp->PROT.OPP_SET;

			break;
		case P_UVP_LEVEL:
			tmp = Disp_tmp->PROT.UVP_VOLT[V_Range];
			break;
#if Enable_Ring_Count
		case P_UVP_SETTING:
			tmp = Disp_tmp->PROT.UVP_Tone_len;
			if(tmp>0)tmp = tmp -1;
			break;
#endif			
		case P_OVP_LEVEL:
			tmp = Disp_tmp->PROT.OVP_VOLT[V_Range];
			break;
		default:
			break;
		}
		break;
	case P_CONF_OTHER:	/* Configure Status */
		switch(cnt) {
		case P_SOFT_START:
			tmp = Disp_tmp->CONF.SOFT_START;
			break;
		case P_VON_VOLTAGE:
			tmp = Data_tmp->CONF.VON_VOLT[V_Range];
			break;
		case P_VON_LATCH:
			tmp = Disp_tmp->CONF.VON_LATCH;
			break;
		case P_SHORT_KEY:
			tmp = Disp_tmp->CONF.Short_Key;
			break;
#if Enable_Short_invalidate
		case P_SHORT_Fun:
			tmp = Disp_tmp->CONF.Short_Fun;
			break;
		case P_SHORT_Safety:
			tmp = Disp_tmp->CONF.Short_Satety;
			break;	
#endif			
		case P_COUNTTIME:
			tmp = Disp_tmp->CONF.Count_Time;
			break;
		case P_CUTOFFTIME:
			if (Data_tmp->CONF.Cut_Off_cnt==0)//hours
				tmp = Disp_tmp->CONF.cut_off_time_total;
			else if (Data_tmp->CONF.Cut_Off_cnt==1)//minuint
				tmp = Disp_tmp->CONF.cut_off_time_total;
			else if (Data_tmp->CONF.Cut_Off_cnt==2)//sec
				tmp = Disp_tmp->CONF.cut_off_time_total;
			else if (Data_tmp->CONF.Cut_Off_cnt==3)//total_time
				tmp = Disp_tmp->CONF.cut_off_time_total;
			break;
#if 0
		case P_Response:
			tmp = Disp_tmp->CONF.Response;
			break;
#endif
		case P_Mem_Recall:
			tmp = Disp_tmp->CONF.Memory_Recall;
			break;
		case P_Dyna_Level:
			tmp = Disp_tmp->CONF.Dyna_Level;
			break;
		case P_Dyna_Time:
			tmp = Disp_tmp->CONF.Dyna_Time;
			break;
		case P_CR_Unit:
			tmp = Disp_tmp->CONF.D_CR_Unit;
			break;
		case P_Von_Delay:
			//if(P3k_Disp_Data.CURRMODE==CR_MODE)
			//	tmp = Disp_tmp->CONF.D_Von_Delay_CR;
			//else
				tmp = Disp_tmp->CONF.D_Von_Delay;
			break;
		default:
			break;
		}
		break;
	case P_CONF_KNOB:
		switch(cnt) {
		case P_Knob_Status:
			tmp = Disp_tmp->CONF.Knob_Status;
			break;
		case P_CCH_STEP:
			tmp = Disp_tmp->CC.VALUE_STEP[1];
			break;
		case P_CCL_STEP:
			tmp = Disp_tmp->CC.VALUE_STEP[0];
			break;
		case P_CRH_STEP:
			tmp = Disp_tmp->CR.VALUE_STEP[1];
			break;
		case P_CRL_STEP:
			tmp = Disp_tmp->CR.VALUE_STEP[0];
			break;
		case P_CVH_STEP:
			tmp = Disp_tmp->CV.VALUE_STEP[1];
			break;
		case P_CVL_STEP:
			tmp = Disp_tmp->CV.VALUE_STEP[0];
			break;
		case P_CPH_STEP:
			tmp = Disp_tmp->CP.VALUE_STEP[1];
			break;
		case P_CPL_STEP:
			tmp = Disp_tmp->CP.VALUE_STEP[0];
			break;
		default:
			break;
		}
		break;
	case P_PROG_MAIN:
		switch(cnt) {
		case Program_PROG:
			tmp = Prog_tmp->Prog_No;
			break;
		case Program_STEP:
			tmp = Prog_tmp->Step_No;
			break;
		case Program_Memory:
			tmp = Prog_tmp->Timing_Data[Prog_tmp->Prog_No].MEMORY[Prog_tmp->Step_No];
			break;
		case Program_Run:
			tmp = Prog_tmp->Timing_Data[Prog_tmp->Prog_No].RUNMODE[Prog_tmp->Step_No];
			break;
		case Program_On_Time:
			tmp = Prog_tmp->Timing_Data[Prog_tmp->Prog_No].ONTIME[Prog_tmp->Step_No];
			break;
		case Program_Off_Time:
			tmp = Prog_tmp->Timing_Data[Prog_tmp->Prog_No].OFFTIME[Prog_tmp->Step_No];
			break;
		case Program_P_F_Time:
			tmp = Prog_tmp->Timing_Data[Prog_tmp->Prog_No].PFTIME[Prog_tmp->Step_No];
			break;
		case Program_Short_Time:
			tmp = Prog_tmp->Timing_Data[Prog_tmp->Prog_No].SHORTTIME[Prog_tmp->Step_No];
			break;
		default:
			break;
		}
		break;
	case P_UTIL_T_DATE:
		if(cnt==0)
			tmp = TIMERSET.MONTH;
		else if(cnt==1)
			tmp = TIMERSET._DAY;
		else if(cnt==2)
			tmp = TIMERSET.YEAR;
		else if(cnt==3)
			tmp = TIMERSET._HOUR;
		else if(cnt==4)
			tmp = TIMERSET._MINUTE;
		break;
	case P_UTIL_INTERFACE:
		switch(cnt) {
		case Interface_Select:
			tmp = D_interface.INTERFACE;
			break;
		case Baud_Rate:
			tmp = D_interface.BAUD;
			break;
		case Stop_Bit:
			tmp = D_interface.STOP;
			break;
		case RS232_Parity:
			tmp = D_interface.PARITY;
			break;
		case GPIB_Address:
			tmp = D_interface.MYADDR;
			break;
		}
		break;
	case P_CONF_Para:
		switch(cnt) {
		case P_Sync_TrigIn:
			tmp = Disp_tmp->CONF.Para_Data.TrigIN;
			break;
		case P_Sync_TrigInDelay:
			tmp = Disp_tmp->CONF.Para_Data.TrigInDelay;
			break;		
		case P_Sync_TrigOut:
			tmp = Disp_tmp->CONF.Para_Data.TrigOut;
			break;
		case P_Sync_TrigOutWidth:
			tmp = Disp_tmp->CONF.Para_Data.TrigOutWidth;	
			break;
				
		default:
			break;
		}
		//printf("No:%d, read:%d\n",cnt,tmp);
		break;
	case P_CONF_Ext:
		if(cnt==P_Ext_Control)
			tmp = Disp_tmp->CONF.Ext_Setting.Control;
		else if(cnt==P_Ext_LoadON_IN)
			tmp = Disp_tmp->CONF.Ext_Setting.LoadOn_IN;
		else if(cnt==P_Extmulti_para)
			tmp = Disp_tmp->CONF.Ext_Setting.MultilPara;

		break;
#if Enable_Ring_Count
	case P_FUNC_MAIN:
	case P_FUNC_MAIN_2:	
		switch(cnt) {
			case P_Func_M_start:
				tmp = P3k_Disp_Data.Load_Type;
				break;
			case P_Func_M_comp:
				tmp = Disp_tmp->PROT.SEQ_Tone_len;
				if(tmp>0)tmp = tmp -1;
				break;
			case P_Func_M_count:
				tmp = Disp_tmp->CONF.T_count_up;				
				break;
			default:
				break;
		}
		break;
#endif		
	case P_Seq_Normal:
		Curr_Number = P3k_NSeq_Disp.NSeq_Number;
		switch(cnt) {
		case P_NSeq_Start:
			tmp = P3k_NSeq_Disp.NSeq_Start;
			break;
		case P_NSeq_No:
			tmp = P3k_NSeq_Disp.NSeq_Number;
			break;
		case P_NSeq_Memo:
			tmp = P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Memo[0];
			break;
		case P_NSeq_Mode:
			tmp = P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Mode;
			break;
		case P_NSeq_Range:
			tmp = P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Range;
			break;
		case P_NSeq_Loop:
			tmp = P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Loop;
			break;
		case P_NSeq_Last_Load:
			tmp = P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Last_Load;
			break;
		case P_NSeq_Last_Set:
			tmp = P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Last_Level;
			break;
		case P_NSeq_Chain:
			tmp = P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Chain;
			break;
		default:
			break;
		}
		break;
	case P_NSeq_Edit:
		NSeq_Timing_Ptr = &P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number];
		Curr_Number		= NSeq_Timing_Ptr->NSeq_Curr_Step;
		NSeq_Data_Ptr	= &P3k_NSeq_Disp.NSeq_Step[P3k_NSeq_Disp.NSeq_Number][Curr_Number];


		if(cnt==P_NSeqEdit_Step)
			tmp = NSeq_Timing_Ptr->NSeq_Curr_Step;
		else if(cnt==P_NSeqEdit_Value)
			tmp = NSeq_Data_Ptr->NSeq_Value;
		else if(cnt==P_NSeqEdit_Time_H)
			tmp = NSeq_Data_Ptr->NSeq_Time.Hour;
		else if(cnt==P_NSeqEdit_Time_M)
			tmp = NSeq_Data_Ptr->NSeq_Time.Minute;
		else if(cnt==P_NSeqEdit_Time_S)
			tmp = NSeq_Data_Ptr->NSeq_Time.Second;
		else if(cnt==P_NSeqEdit_Time_mS)
			tmp = NSeq_Data_Ptr->NSeq_Time.MilliSecond;
		else if(cnt==P_NSeqEdit_Load)
			tmp = NSeq_Data_Ptr->Load_Setting;
		else if(cnt==P_NSeqEdit_Ramp)
			tmp = NSeq_Data_Ptr->Ramp_Setting;
		else if(cnt==P_NSeqEdit_Trig)
			tmp = NSeq_Data_Ptr->TrigOut_Setting;
		else if(cnt==P_NSeqEdit_Pause)
			tmp = NSeq_Data_Ptr->Pause_Setting;
		else
			tmp = NSeq_Timing_Ptr->NSeq_Max_Step;
		break;
	case P_Seq_Fast:
		switch(cnt) {
		case P_FSeq_Memo:
			tmp = P3k_FSeq_Disp.FSeq_Memo[0];
			break;
		case P_FSeq_Mode:
			tmp = P3k_FSeq_Disp.FSeq_Mode;
			break;
		case P_FSeq_Range:
			tmp = P3k_FSeq_Disp.FSeq_Range;
			break;
		case P_FSeq_Loop:
			tmp = P3k_FSeq_Disp.FSeq_Loop;
			break;
		case P_FSeq_TimeBase:
			tmp = P3k_FSeq_Disp.FSeq_Time_Base;
			break;
		case P_FSeq_Last_Load:
			tmp = P3k_FSeq_Disp.FSeq_Last_Load;
			break;
		case P_FSeq_Last_Set:
			tmp = P3k_FSeq_Disp.FSeq_Last_Level;
			break;
		case P_FSeq_RptStep:
#if Enable_FSEQ_RPT
			tmp = P3k_FSeq_Disp.RPTStep;
			if (tmp > 0xFF00)tmp =0;
#else
			tmp = P3k_FSeq_Disp.FSeq_Max_Step;
			if (tmp > 0xFF00)tmp =0;
#endif

			break;
		default:
			break;
		}
		break;
	case P_FSeq_Edit:
		FSeq_Data_Ptr = &P3k_FSeq_Disp.FSeq_Step[P3k_FSeq_Disp.FSeq_Curr_Step];
		if(cnt==P_FSeqEdit_Step)
			tmp = P3k_FSeq_Disp.FSeq_Curr_Step;
		else if(cnt==P_FSeqEdit_Value)
			tmp = FSeq_Data_Ptr->FSeq_Value;
		else if(cnt==P_FSeqEdit_Trig)
			tmp = FSeq_Data_Ptr->TrigOut_Setting;
		else
			tmp = P3k_FSeq_Disp.FSeq_Max_Step;
		break;
	case P_FSeq_Fill:
		if(cnt==P_Fill_Value_S)
			tmp = P3k_FSeq_Disp.Fill_Start_Value;
		else if(cnt==P_Fill_Value_E)
			tmp = P3k_FSeq_Disp.Fill_End_Value;
		else if(cnt==P_Fill_Step_S)
			tmp = P3k_FSeq_Disp.Fill_Start_Step;
		else{
			tmp = P3k_FSeq_Disp.Fill_End_Step;
			if (tmp > 0xFF00)tmp =0;
		}
		break;

#if Enable_OCP_function	
	case P_FUNC_OCP:
		
		currTemp = P3K_OCP_Disp.CurrTemp; 
		if(cnt==P_F_OCP_CurrTemp)
			tmp = currTemp;
		else if(cnt==P_F_OCP_Range)
			tmp = P3K_OCP_Disp.Seq[currTemp].Range;
		else if(cnt==P_F_OCP_StartCurr)
			tmp = P3K_OCP_Disp.Seq[currTemp].StartCurrWatt;
		else if(cnt==P_F_OCP_EndCurr)
			tmp = P3K_OCP_Disp.Seq[currTemp].EndCurrWatt;
		else if(cnt==P_F_OCP_StepCurr)
			tmp = P3K_OCP_Disp.Seq[currTemp].StepCurrWatt;
		else if(cnt==P_F_OCP_StepTime)
			tmp = P3K_OCP_Disp.Seq[currTemp].StepTime;
		else if(cnt==P_F_OCP_TrigVolt)
			tmp = P3K_OCP_Disp.Seq[currTemp].TrigVolt;
		else if(cnt==P_F_OCP_DelayTrig)
			tmp = P3K_OCP_Disp.Seq[currTemp].DelayTime;
		else if(cnt==P_F_OCP_LastCurr)
			tmp = P3K_OCP_Disp.Seq[currTemp].LastCurrWatt;
		break;
#endif
#if Enable_OPP_function
	case P_FUNC_OPP:
		currTemp = P3K_OPP_Disp.CurrTemp;
		if(cnt==P_F_OPP_CurrTemp)
			tmp = currTemp;
		else if(cnt==P_F_OPP_Range)
			tmp = P3K_OPP_Disp.Seq[currTemp].Range;
		else if(cnt==P_F_OPP_StartCurr)
			tmp = P3K_OPP_Disp.Seq[currTemp].StartCurrWatt;
		else if(cnt==P_F_OPP_EndCurr)
			tmp = P3K_OPP_Disp.Seq[currTemp].EndCurrWatt;
		else if(cnt==P_F_OPP_StepCurr)
			tmp = P3K_OPP_Disp.Seq[currTemp].StepCurrWatt;
		else if(cnt==P_F_OPP_StepTime)
			tmp = P3K_OPP_Disp.Seq[currTemp].StepTime;
		else if(cnt==P_F_OPP_TrigVolt)
			tmp = P3K_OPP_Disp.Seq[currTemp].TrigVolt;
		else if(cnt==P_F_OPP_DelayTrig)
			tmp = P3K_OPP_Disp.Seq[currTemp].DelayTime;
		else if(cnt==P_F_OPP_LastCurr)
			tmp = P3K_OPP_Disp.Seq[currTemp].LastCurrWatt;
		break;
#endif
	
#if Enable_Battery_Discharge
	case P_FUNC_batt:
		if(cnt==P_F_BATT_Mode) {
			tmp = BattDisp.Mode;
		}else if(cnt==P_F_BATT_Range) {
			tmp = BattDisp.Range;
		}else if(cnt==P_F_BATT_Set) {
			tmp = BattDisp.Setting;
		}else if(cnt==P_F_BATT_SRUP) {
			tmp = BattDisp.SRUP;		
		}else if(cnt==P_F_BATT_SRDW) {
			tmp = BattDisp.SRDW;
		} else if(cnt==P_F_BATT_StopT) { 				
			if(BattDisp.timeCnt==0) {
				tmp = BattDisp.StopHour;
			} else if(BattDisp.timeCnt==1) {
				tmp = BattDisp.StopMin;
			} else {
				tmp = BattDisp.StopSec;
			}
			BattDisp.StopTime = BattDisp.StopHour*3600+BattDisp.StopMin*60+BattDisp.StopSec;
		} else if(cnt==P_F_BATT_StopC) {
			tmp = BattDisp.StopCapa;		
		} else if(cnt==P_F_BATT_StopV) {
			tmp = BattDisp.StopValt;
		}							
		break;
#endif
#if Enable_LED_function
	case P_FUNC_FLED:
		currTemp = P3k_FLed_Disp.currTemp;
		if(cnt==P_F_LED_RESPONSE) //Vo
			tmp = P3k_FLed_Disp.seq[currTemp].response;	
	case P_FUNC_FLED_EDIT:
	case P_FUNC_FLED_EXECUTE:	
		currTemp = P3k_FLed_Disp.currTemp;			
		switch(P3k_FLed_Disp.seq[currTemp].mode){	
			case P_F_LED_MODE_VoIo:
			case P_F_LED_MODE_VoIoRc:
				if(cnt==P_F_LED_Edit_P1){ //Vo
					tmp = P3k_FLed_Disp.seq[currTemp].vo;		
				}else if(cnt==P_F_LED_Edit_P2){//Io	
					tmp = P3k_FLed_Disp.seq[currTemp].io;
				}else if(cnt==P_F_LED_Edit_P3) {//Rcoff
					tmp = P3k_FLed_Disp.seq[currTemp].rdcoff;	
				}
				break;
			case P_F_LED_MODE_VoIoRd:				
				if(cnt==P_F_LED_Edit_P1){//Vo
					tmp = P3k_FLed_Disp.seq[currTemp].vo;
				}else if(cnt==P_F_LED_Edit_P2){//Io	
					tmp = P3k_FLed_Disp.seq[currTemp].io;
				}else if(cnt==P_F_LED_Edit_P3) {//Rd
					tmp = P3k_FLed_Disp.seq[currTemp].rd;
				}
				break;
			case P_F_LED_MODE_VoIoVf:
				if(cnt==P_F_LED_Edit_P1){//Vo
					tmp = P3k_FLed_Disp.seq[currTemp].vo;
				}else if(cnt==P_F_LED_Edit_P2){//Io	
					tmp = P3k_FLed_Disp.seq[currTemp].io;
				}else if(cnt==P_F_LED_Edit_P3) {//Vf
					tmp = P3k_FLed_Disp.seq[currTemp].vf;
				}
				break;
			case P_F_LED_MODE_VfRdPcs:				
				if(cnt==P_F_LED_Edit_P1){ //Vf
					tmp = P3k_FLed_Disp.seq[currTemp].vf;
				}else if(cnt==P_F_LED_Edit_P2){//Rd	
					tmp = P3k_FLed_Disp.seq[currTemp].rd;
				}else if(cnt==P_F_LED_Edit_P3) {//pcs
					tmp = P3k_FLed_Disp.seq[currTemp].pcs;
				}
				break;
			default:
				break;
		}
		
		break;
	case P_FUNC_CLED:
		currTemp = P3k_CLed_Disp.currTemp;
		if(cnt==P_CLED_RESPONSE){ //Vo
			tmp = P3k_CLed_Disp.seq[currTemp].response;	
		}else if(cnt==P_CLED_VO){ //Vo
			tmp = P3k_CLed_Disp.seq[currTemp].vo;	
		}else if(cnt==P_CLED_IO){
			tmp = P3k_CLed_Disp.seq[currTemp].io;
		}
		break;
	case P_FUNC_CLED_EDIT:
		currTemp = P3k_CLed_Disp.currTemp;
		tmp = P3k_CLed_Disp.seq[currTemp].rdcoff;
		break;
	case P_FUNC_CLED_EXECUTE:
		currTemp = P3k_CLed_Disp.currTemp;
		if(cnt==P_CLED_EXE_VO){ //Vo
			tmp = P3k_CLed_Disp.seq[currTemp].vo;	
		}else if(cnt==P_CLED_EXE_IO){
			tmp = P3k_CLed_Disp.seq[currTemp].io;
		}else{
			tmp = P3k_CLed_Disp.seq[currTemp].rdcoff;
		}
		break;			
#endif
	default:
		break;
	}
//printf("%d:%d\n",cnt,tmp); //Adam_test	
	return(tmp);
}

void SaveChanData(BYTE cnt,long dat)
{
	NSeq_Timing_Str *NSeq_Timing_Ptr;
	unsigned short tmp;
	double Voltage_temp;
	UWORD *tmp1;
	UWORD Curr_Number,max,min;
	UBYTE I_Range,V_Range;
	long VON_rawdata;
	UBYTE currTemp;	
	FSeq_Data_Str	*FSeq_Data_Ptr;
	NSeq_Data_Str	*NSeq_Data_Ptr;
#if Enable_NSEQ_Usec
	P3k_Time_Str 	*NSEQ_T;
	unsigned long Ramp_mS_Time;
#endif	
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Prog_Str	*Prog_tmp = &p3k_Disp_PROG;

	V_Range = Disp_tmp->VRange;
	I_Range = Disp_tmp->IRange;

	Check_KNOB_VAL_Count = Check_KNOB_VAL_change_time;
	switch(M_num) {
	case P_CC:	/* CC Mode */
		if( Disp_tmp->CC.STADYNA)
			tmp1 = &Disp_tmp->CC.DYNA[I_Range].LEVEL1;
		else {
			tmp1 = &Disp_tmp->CC.STA[I_Range].VALUE1;
			if(cnt<=CCCR_Sta_B_VALUE)
				Disp_tmp->CC.ABSELECT = cnt;
		}

		if( ((Disp_tmp->CC.STADYNA==Function_Dynamic)&&(cnt==CCCR_Dyn_Add_CV))||((Disp_tmp->CC.STADYNA==Function_Static)&&(cnt==CCCR_Sta_Add_CV)) ) {
			if(dat < 0) {
				Data_tmp->CONF.CV_Func_En = 0;
				dat = 0;
			} else
				Data_tmp->CONF.CV_Func_En = 1;
			Disp_tmp->CV.STA[V_Range].VALUE1 = dat;
		} else if( ((Disp_tmp->CC.STADYNA==Function_Dynamic)&&(cnt==CCCR_Dyn_CV_Response))||((Disp_tmp->CC.STADYNA==Function_Static)&&(cnt==CCCR_Sta_CV_Response)) ) {
			Disp_tmp->CC.CXCV_RESPOSNE= dat;
		} else {
			if((Disp_tmp->CONF.Dyna_Level) && (cnt == CCCR_Dyn_L2) && (Disp_tmp->CC.STADYNA==Function_Dynamic))
				Disp_tmp->CC.DYNA[I_Range].Level_Percent = dat;
			else if((Disp_tmp->CONF.Dyna_Time) && (cnt == CCCR_Dyn_T2) && (Disp_tmp->CC.STADYNA==Function_Dynamic))
				Disp_tmp->CC.DYNA[I_Range].Duty = dat;
			else if((Disp_tmp->CONF.Dyna_Time) && (cnt == CCCR_Dyn_T1) && (Disp_tmp->CC.STADYNA==Function_Dynamic)) {
				Disp_tmp->CC.DYNA[I_Range].Frequency = dat;
				Data_tmp->CC.DYNA[I_Range].Frequency = dat;
				Data_tmp->CC.DYNA[I_Range].Frequency_Range = Disp_tmp->CC.DYNA[I_Range].Frequency_Range;
				min = get_DynaFreqDutyRangeLimit(P_CC);
				max = 1000 -  min;
				if(Disp_tmp->CC.DYNA[I_Range].Duty < min)Disp_tmp->CC.DYNA[I_Range].Duty = min;
				else if(Disp_tmp->CC.DYNA[I_Range].Duty > max)Disp_tmp->CC.DYNA[I_Range].Duty = max;
				Data_tmp->CC.DYNA[I_Range].Duty =Disp_tmp->CC.DYNA[I_Range].Duty;
			} else
				*(tmp1 + cnt) = dat;			
		}
//printf("dta:%d\n",dat);		
		break;
	case P_CC_SPEC: /* CC Go-NoGo */
		if( Disp_tmp->CC.STADYNA)
			tmp1 = &Disp_tmp->CC.DYNA[I_Range].CENTERVAL;
		else
			tmp1 = &Disp_tmp->CC.STA[I_Range].CENTERVAL;
		*(tmp1 + (cnt-6) ) = dat;
		break;
	case P_CR:	/* CR Mode */
		if( Disp_tmp->CR.STADYNA==Function_Dynamic )
			tmp1 = &Disp_tmp->CR.DYNA[I_Range].LEVEL1;
		else {
			tmp1 = &Disp_tmp->CR.STA[I_Range].VALUE1;
			if(cnt<=CCCR_Sta_B_VALUE)
				Disp_tmp->CR.ABSELECT = cnt;
		}

		if(((Disp_tmp->CR.STADYNA==Function_Dynamic)&&(cnt==CCCR_Dyn_Add_CV))||((Disp_tmp->CR.STADYNA==Function_Static)&&(cnt==CCCR_Sta_Add_CV))) {
			if(dat < 0) {
				Data_tmp->CONF.CV_Func_En = 0;
				dat = 0;
			} else
				Data_tmp->CONF.CV_Func_En = 1;

			Disp_tmp->CV.STA[V_Range].VALUE1 = dat;
		} else if(((Disp_tmp->CR.STADYNA==Function_Dynamic)&&(cnt==CCCR_Dyn_CV_Response))||((Disp_tmp->CR.STADYNA==Function_Static)&&(cnt==CCCR_Sta_CV_Response))) {
			Disp_tmp->CR.CXCV_RESPOSNE= dat;
		} else {
			if((Disp_tmp->CONF.Dyna_Level) && (cnt == CCCR_Dyn_L2) && (Disp_tmp->CR.STADYNA==Function_Dynamic))
				Disp_tmp->CR.DYNA[I_Range].Level_Percent = dat;
			else if((Disp_tmp->CONF.Dyna_Time) && (cnt == CCCR_Dyn_T2) && (Disp_tmp->CR.STADYNA==Function_Dynamic))
				Disp_tmp->CR.DYNA[I_Range].Duty = dat;
			else if((Disp_tmp->CONF.Dyna_Time) && (cnt == CCCR_Dyn_T1) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) {
				Disp_tmp->CR.DYNA[I_Range].Frequency = dat;
				Data_tmp->CR.DYNA[I_Range].Frequency = dat;
				Data_tmp->CR.DYNA[I_Range].Frequency_Range = Disp_tmp->CR.DYNA[I_Range].Frequency_Range;
				min = get_DynaFreqDutyRangeLimit(P_CR);
				max = 1000 -  min;
				if(Disp_tmp->CR.DYNA[I_Range].Duty < min)Disp_tmp->CR.DYNA[I_Range].Duty = min;
				else if(Disp_tmp->CR.DYNA[I_Range].Duty > max)Disp_tmp->CR.DYNA[I_Range].Duty = max;
				Data_tmp->CR.DYNA[I_Range].Duty =Disp_tmp->CR.DYNA[I_Range].Duty;
			} else
				*(tmp1 + cnt) = dat;
		}
		break;
	case P_CR_SPEC: /* CR Go-NoGo */
		if( Disp_tmp->CR.STADYNA)
			tmp1 = &Disp_tmp->CR.DYNA[I_Range].CENTERVAL;
		else
			tmp1 = &Disp_tmp->CR.STA[I_Range].CENTERVAL;
		*(tmp1 + (cnt-6) ) = dat;
		break;
	case P_CV:	/* CV Mode */
		if( Disp_tmp->CV.STADYNA)
			tmp1 = &Disp_tmp->CV.DYNA[V_Range].LEVEL1;
		else {
			tmp1 = &Disp_tmp->CV.STA[V_Range].VALUE1;
			if( cnt<=CV_B_VALUE )
				Disp_tmp->CV.ABSELECT = cnt;
		}
		*(tmp1 + cnt) = dat;
		break;
	case P_CV_SPEC: /* CV Go-NoGo */
		tmp1 = &Disp_tmp->CV.STA[V_Range].CENTERVAL;
		*(tmp1 + (cnt-6) ) = dat;
		break;
	case P_CP:	/* CP Mode */
		tmp1 = &Disp_tmp->CP.STA[I_Range].VALUE1;
		if(cnt<=CP_Sta_B_VALUE)
			Disp_tmp->CP.ABSELECT = cnt;

		if(cnt==CP_Sta_Add_CV) {
			if(dat < 0) {
				Data_tmp->CONF.CV_Func_En = 0;
				dat = 0;
			} else
				Data_tmp->CONF.CV_Func_En = 1;

			Disp_tmp->CV.STA[V_Range].VALUE1 = dat;
		} else if(cnt==CP_Sta_CV_Response) {
			Disp_tmp->CP.CXCV_RESPOSNE = dat;
		} else {
			*(tmp1 + cnt) = dat;
		}
		break;
	case P_CP_SPEC: /* CP Go-NoGo */
		if(Disp_tmp->CP.STADYNA)
			tmp1 = &Disp_tmp->CP.DYNA[I_Range].CENTERVAL;
		else
			tmp1 = &Disp_tmp->CP.STA[I_Range].CENTERVAL;

		*(tmp1 + (cnt-6) ) = dat;
		break;
	case P_CONF_PROT:	/* Protection Mode */
		if(cnt == P_OCP_LEVEL)
			Disp_tmp->PROT.OCP[HIGH_RANGE]	= dat;
		else if(cnt == P_OCP_SETTING)
			Disp_tmp->PROT.OCP_SET			= dat;
		else if(cnt == P_OPP_LEVEL)
			Disp_tmp->PROT.OPP[HIGH_RANGE]	= dat;
		else if(cnt == P_OPP_SETTING)
			Disp_tmp->PROT.OPP_SET			= dat;
		else if(cnt == P_UVP_LEVEL)
			Disp_tmp->PROT.UVP_VOLT[V_Range]= dat;
#if Enable_Ring_Count
		else if(cnt == P_UVP_SETTING)
			Disp_tmp->PROT.UVP_Tone_len = dat;
#endif		
		else if(cnt == P_OVP_LEVEL)
			Disp_tmp->PROT.OVP_VOLT[V_Range]= dat;
		break;
	case P_CONF_OTHER:	/* Other Of Configure */
		switch(cnt) {
		case P_SOFT_START:
			Disp_tmp->CONF.SOFT_START = dat;
			break;
		case P_VON_VOLTAGE:
			Data_tmp->CONF.VON_VOLT[V_Range] = Disp_tmp->CONF.VON_VOLT[V_Range] = dat;
			Voltage_temp= dat * (ptrMODEL_TYPE->CONF[V_Range].Resolution);
			V_Range++;
			V_Range&=0x01;
			VON_rawdata = Voltage_temp / ptrMODEL_TYPE->CONF[V_Range].Resolution;
			if(VON_rawdata > ptrMODEL_TYPE->CONF[V_Range].Max)
				VON_rawdata = ptrMODEL_TYPE->CONF[V_Range].Max;
			else if(VON_rawdata < ptrMODEL_TYPE->CONF[V_Range].Min)
				VON_rawdata = ptrMODEL_TYPE->CONF[V_Range].Min;
			Disp_tmp->CONF.VON_VOLT[V_Range] = VON_rawdata;
			break;
		case P_VON_LATCH:
			Disp_tmp->CONF.VON_LATCH = dat;
			break;
		case P_Von_Delay:
			//if(P3k_Disp_Data.CURRMODE==CR_MODE)

			//	Disp_tmp->CONF.D_Von_Delay_CR = dat;
			//else
				Disp_tmp->CONF.D_Von_Delay = dat;
			break;
#if 0
		case P_Response:
			Disp_tmp->CONF.Response	= dat;
			break;
#endif
		case P_COUNTTIME:
			Disp_tmp->CONF.Count_Time = dat;
			break;
		case P_CUTOFFTIME:
			if (Data_tmp->CONF.Cut_Off_cnt==0)//hours
				Disp_tmp->CONF.Cut_Off_Time_h= dat;
			else if (Data_tmp->CONF.Cut_Off_cnt==1)//minuint
				Disp_tmp->CONF.Cut_Off_Time_m= dat;
			else if (Data_tmp->CONF.Cut_Off_cnt==2)//sec
				Disp_tmp->CONF.Cut_Off_Time_s= dat;
			else if (Data_tmp->CONF.Cut_Off_cnt==3)//total_time
				Disp_tmp->CONF.cut_off_time_total= dat;
			Disp_tmp->CONF.cut_off_time_total = Disp_tmp->CONF.Cut_Off_Time_h*3600+Disp_tmp->CONF.Cut_Off_Time_m*60+Disp_tmp->CONF.Cut_Off_Time_s;
			break;
		case P_CR_Unit:
			Disp_tmp->CONF.D_CR_Unit = dat;
			break;
		case P_Dyna_Level:
			Disp_tmp->CONF.Dyna_Level = dat;
			break;
		case P_Dyna_Time:
			Disp_tmp->CONF.Dyna_Time = dat;
			break;
		case P_Mem_Recall:
			Disp_tmp->CONF.Memory_Recall = dat;
			break;
		case P_SHORT_KEY:
			Disp_tmp->CONF.Short_Key = dat;
			break;
#if Enable_Short_invalidate
		case P_SHORT_Fun:
			Disp_tmp->CONF.Short_Fun = dat;
			break;
		case P_SHORT_Safety:
			Disp_tmp->CONF.Short_Satety = dat;
			break;	
#endif				
		default:
			break;
		}
		break;
	case P_CONF_KNOB:
		switch(cnt) {
		case P_Knob_Status:
			Disp_tmp->CONF.Knob_Status = dat;
			break;
		case P_CCH_STEP:
			Disp_tmp->CC.VALUE_STEP[1] = dat;
			break;
			//case P_CCM_STEP:
			//	Disp_tmp->CC.VALUE_STEP[1] = dat;
			//	break;
		case P_CCL_STEP:
			Disp_tmp->CC.VALUE_STEP[0] = dat;
			break;
		case P_CRH_STEP:
			Disp_tmp->CR.VALUE_STEP[1] = dat;
			break;
		case P_CRL_STEP:
			Disp_tmp->CR.VALUE_STEP[0] = dat;
			break;
		case P_CVH_STEP:
			Disp_tmp->CV.VALUE_STEP[1] = dat;
			break;
		case P_CVL_STEP:
			Disp_tmp->CV.VALUE_STEP[0] = dat;
			break;
		case P_CPH_STEP:
			Disp_tmp->CP.VALUE_STEP[1] = dat;
			break;
		case P_CPL_STEP:
			Disp_tmp->CP.VALUE_STEP[0] = dat;
			break;
		default:
			break;
		}
		break;
	case P_PROG_MAIN:
		if(cnt==Program_PROG)
			Prog_tmp->Prog_No = dat;
		else if(cnt==Program_STEP)
			Prog_tmp->Step_No= dat;
		else if(cnt==Program_Memory)
			Prog_tmp->Timing_Data[Prog_tmp->Prog_No].MEMORY[Prog_tmp->Step_No] = dat;
		else if(cnt==Program_Run)
			Prog_tmp->Timing_Data[Prog_tmp->Prog_No].RUNMODE[Prog_tmp->Step_No] = dat;
		else if(cnt==Program_On_Time) {
			Prog_tmp->Timing_Data[Prog_tmp->Prog_No].ONTIME[Prog_tmp->Step_No] = dat;

			if(Prog_tmp->Timing_Data[Prog_tmp->Prog_No].SHORTTIME[Prog_tmp->Step_No] >= Prog_tmp->Timing_Data[Prog_tmp->Prog_No].ONTIME[Prog_tmp->Step_No])
				Prog_tmp->Timing_Data[Prog_tmp->Prog_No].SHORTTIME[Prog_tmp->Step_No] = Prog_tmp->Timing_Data[Prog_tmp->Prog_No].ONTIME[Prog_tmp->Step_No];

			if(Prog_tmp->Timing_Data[Prog_tmp->Prog_No].PFTIME[Prog_tmp->Step_No] >= (Prog_tmp->Timing_Data[Prog_tmp->Prog_No].ONTIME[Prog_tmp->Step_No]+Prog_tmp->Timing_Data[Prog_tmp->Prog_No].OFFTIME[Prog_tmp->Step_No]))
				Prog_tmp->Timing_Data[Prog_tmp->Prog_No].PFTIME[Prog_tmp->Step_No] = (Prog_tmp->Timing_Data[Prog_tmp->Prog_No].ONTIME[Prog_tmp->Step_No]+Prog_tmp->Timing_Data[Prog_tmp->Prog_No].OFFTIME[Prog_tmp->Step_No])-1;
		} else if(cnt==Program_Off_Time) {
			Prog_tmp->Timing_Data[Prog_tmp->Prog_No].OFFTIME[Prog_tmp->Step_No] = dat;

			if(Prog_tmp->Timing_Data[Prog_tmp->Prog_No].PFTIME[Prog_tmp->Step_No] >= (Prog_tmp->Timing_Data[Prog_tmp->Prog_No].ONTIME[Prog_tmp->Step_No]+Prog_tmp->Timing_Data[Prog_tmp->Prog_No].OFFTIME[Prog_tmp->Step_No]))
				Prog_tmp->Timing_Data[Prog_tmp->Prog_No].PFTIME[Prog_tmp->Step_No] = (Prog_tmp->Timing_Data[Prog_tmp->Prog_No].ONTIME[Prog_tmp->Step_No]+Prog_tmp->Timing_Data[Prog_tmp->Prog_No].OFFTIME[Prog_tmp->Step_No])-1;
		} else if(cnt==Program_P_F_Time)
			Prog_tmp->Timing_Data[Prog_tmp->Prog_No].PFTIME[Prog_tmp->Step_No]		= dat;
		else if(cnt==Program_Short_Time)
			Prog_tmp->Timing_Data[Prog_tmp->Prog_No].SHORTTIME[Prog_tmp->Step_No]	= dat;
		break;
	case P_CONF_Para:
		if(cnt==P_Sync_TrigOut)
			Disp_tmp->CONF.Para_Data.TrigOut= dat;
		else if(cnt==P_Sync_TrigIn)
			Disp_tmp->CONF.Para_Data.TrigIN= dat;
		else if(cnt==P_Sync_TrigOutWidth)
			Disp_tmp->CONF.Para_Data.TrigOutWidth= dat;
		else if(cnt==P_Sync_TrigInDelay)
			Disp_tmp->CONF.Para_Data.TrigInDelay= dat;
		//printf("No:%d,save:%d\n",cnt,dat);
		break;
	case P_CONF_Ext:
		if(cnt==P_Ext_Control)
			Disp_tmp->CONF.Ext_Setting.Control	= dat;
		else if(cnt==P_Ext_LoadON_IN)
			Disp_tmp->CONF.Ext_Setting.LoadOn_IN = dat;
		else if(cnt==P_Extmulti_para)
			Disp_tmp->CONF.Ext_Setting.MultilPara = dat;

		Data_tmp->CONF.Ext_Setting = Disp_tmp->CONF.Ext_Setting;
		break;
#if Enable_Ring_Count		
	case P_FUNC_MAIN:
	case P_FUNC_MAIN_2:
		switch(cnt) {
			case P_Func_M_start:
				P3k_Disp_Data.Load_Type = dat;
				break;
			case P_Func_M_comp:
				Disp_tmp->PROT.SEQ_Tone_len = dat;	
				break;
			case P_Func_M_count:
				Disp_tmp->CONF.T_count_up = dat;
				last_menu = 0xFF;
			default:
				break;
		}
		break;	
#endif			
	case P_Seq_Normal:
		Curr_Number = P3k_NSeq_Disp.NSeq_Number;
		if(cnt==P_NSeq_Start)
			P3k_NSeq_Disp.NSeq_Start	= dat;
		else if(cnt==P_NSeq_No)
			P3k_NSeq_Disp.NSeq_Number	= dat;
		else if(cnt==P_NSeq_Memo)
			P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Memo[0]		= dat;
		else if(cnt==P_NSeq_Mode){
			P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Mode			= dat;
			if(dat==CR_MODE){
				if(P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Range==0)
					P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Range = 1;
				if(P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Range==3)
					P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Range = 2;
			}
		}else if(cnt==P_NSeq_Range)
			P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Range			= dat;
		else if(cnt==P_NSeq_Loop)
			P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Loop			= dat;
		else if(cnt==P_NSeq_Last_Load)
			P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Last_Load		= dat;
		else if(cnt==P_NSeq_Last_Set)
			P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Last_Level	= dat;
		else if(cnt==P_NSeq_Chain)
			P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Chain			= dat;
		break;
	case P_NSeq_Edit:
		NSeq_Timing_Ptr = &P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number];
		Curr_Number		= NSeq_Timing_Ptr->NSeq_Curr_Step;
		NSeq_Data_Ptr	= &P3k_NSeq_Disp.NSeq_Step[P3k_NSeq_Disp.NSeq_Number][Curr_Number];
#if Enable_NSEQ_Usec
		NSEQ_T = &P3k_NSeq_Disp.NSeq_Step[P3k_NSeq_Disp.NSeq_Number][Curr_Number].NSeq_Time;
#endif

		if(cnt==P_NSeqEdit_Step)
			NSeq_Timing_Ptr->NSeq_Curr_Step 		= dat;
		else if(cnt==P_NSeqEdit_Value)
			NSeq_Data_Ptr->NSeq_Value				= dat;
		else if(cnt==P_NSeqEdit_Time_H)
			NSeq_Data_Ptr->NSeq_Time.Hour			= dat;
		else if(cnt==P_NSeqEdit_Time_M)
			NSeq_Data_Ptr->NSeq_Time.Minute			= dat;
		else if(cnt==P_NSeqEdit_Time_S)
			NSeq_Data_Ptr->NSeq_Time.Second			= dat;
		else if(cnt==P_NSeqEdit_Time_mS)
			NSeq_Data_Ptr->NSeq_Time.MilliSecond	= dat;
		else if(cnt==P_NSeqEdit_Load)
			NSeq_Data_Ptr->Load_Setting				= dat;
		else if((P3k_NSeq_Disp.NSeq_Seq[Curr_Number].NSeq_Mode!=P_CV) && (cnt==P_NSeqEdit_Ramp))
			NSeq_Data_Ptr->Ramp_Setting	= dat;
		else if(cnt==P_NSeqEdit_Trig)
			NSeq_Data_Ptr->TrigOut_Setting			= dat;
		else if(cnt==P_NSeqEdit_Pause)
			NSeq_Data_Ptr->Pause_Setting			= dat;
		else
			NSeq_Timing_Ptr->NSeq_Max_Step 			= dat;
#if Enable_NSEQ_Usec
		
		Ramp_mS_Time = NSEQ_T->Hour*60*60*1000 + NSEQ_T->Minute*60*1000 + NSEQ_T->Second*1000 + (NSEQ_T->MilliSecond/20);

		/*
		1uS 		~	60mS		1uS
		60mS		~	600mS		10uS
		600mS		~	6S			100uS
		6S			~	1min		1mS
		1min		~	100min		100mS
		100min		~	1000min 	1S
		1000min 		~	10000min	10S
		10000min	~	1000H		1min
		*/
		if(Ramp_mS_Time>10000*60*1000) {	/* 10000 Minute ~ 1000 Hour */
			NSEQ_T->Second = 0;
			NSEQ_T->MilliSecond = 0;
		} else if(Ramp_mS_Time>1000*60*1000) {	/* 1000 Minute ~ 10000 Minute	*/
			NSEQ_T->Second = NSEQ_T->Second - (NSEQ_T->Second%10);;
			NSEQ_T->MilliSecond = 0;
		} else if(Ramp_mS_Time>100*60*1000) {	/* 100 Minute ~1000 Minute	*/
			NSEQ_T->MilliSecond = 0;
		} else if(Ramp_mS_Time>1*60*1000) { /* 1 Minute ~ 100 Minute	*/

		} else {						/* 1 us ~ 60 ms */

		}
		
#endif

		break;
	case P_Seq_Fast:
		if(cnt==P_FSeq_Memo)
			P3k_FSeq_Disp.FSeq_Memo[0]		= dat;
		else if(cnt==P_FSeq_Mode){
			P3k_FSeq_Disp.FSeq_Mode		= dat;
			if(dat==CR_MODE){
				if(P3k_FSeq_Disp.FSeq_Range==0)
					P3k_FSeq_Disp.FSeq_Range = 1;
				if(P3k_FSeq_Disp.FSeq_Range==3)
					P3k_FSeq_Disp.FSeq_Range = 2;
			}
		}else if(cnt==P_FSeq_Range)
			P3k_FSeq_Disp.FSeq_Range		= dat;
		else if(cnt==P_FSeq_Loop)
			P3k_FSeq_Disp.FSeq_Loop		= dat;
		else if(cnt==P_FSeq_TimeBase)
			P3k_FSeq_Disp.FSeq_Time_Base	= dat;
		else if(cnt==P_FSeq_Last_Load)
			P3k_FSeq_Disp.FSeq_Last_Load	= dat;
		else if(cnt==P_FSeq_Last_Set)
			P3k_FSeq_Disp.FSeq_Last_Level	= dat;
		else if(cnt==P_FSeq_RptStep) {
#if Enable_FSEQ_RPT
			if(dat>1999)	dat = 0;
			P3k_FSeq_Disp.RPTStep= dat; 		
			if( P3k_FSeq_Disp.RPTStep > P3k_FSeq_Disp.FSeq_Max_Step )
				P3k_FSeq_Disp.RPTStep = P3k_FSeq_Disp.FSeq_Max_Step;
#else
			P3k_FSeq_Disp.FSeq_Max_Step = dat;
			if( P3k_FSeq_Disp.FSeq_Curr_Step>P3k_FSeq_Disp.FSeq_Max_Step )
				P3k_FSeq_Disp.FSeq_Curr_Step = P3k_FSeq_Disp.FSeq_Max_Step;
#endif

		}
		break;
	case P_FSeq_Edit:
		FSeq_Data_Ptr = &P3k_FSeq_Disp.FSeq_Step[P3k_FSeq_Disp.FSeq_Curr_Step];
		if(cnt==P_FSeqEdit_Step)
			P3k_FSeq_Disp.FSeq_Curr_Step	= dat;
		else if(cnt==P_FSeqEdit_Value)
			FSeq_Data_Ptr->FSeq_Value		= dat;
		else if(cnt==P_FSeqEdit_Trig)
			FSeq_Data_Ptr->TrigOut_Setting	= dat;
		else
			P3k_FSeq_Disp.FSeq_Max_Step		= dat;
		break;
	case P_FSeq_Fill:
		if(cnt==P_Fill_Value_S)
			P3k_FSeq_Disp.Fill_Start_Value	= dat;
		else if(cnt==P_Fill_Value_E)
			P3k_FSeq_Disp.Fill_End_Value	= dat;
		else if(cnt==P_Fill_Step_S)
			P3k_FSeq_Disp.Fill_Start_Step	= dat;
		else
			P3k_FSeq_Disp.Fill_End_Step	= dat;
		break;
#if Enable_OCP_function	
	case P_FUNC_OCP:		
		currTemp = P3K_OCP_Disp.CurrTemp; 
		if(cnt==P_F_OCP_CurrTemp)
			P3K_OCP_Disp.CurrTemp = dat; //0~11
		else if(cnt==P_F_OCP_Range)
			P3K_OCP_Disp.Seq[currTemp].Range = dat;
		else if(cnt==P_F_OCP_StartCurr){
			P3K_OCP_Disp.Seq[currTemp].StartCurrWatt = dat;
			if(P3K_OCP_Disp.Seq[currTemp].EndCurrWatt<=dat)
				P3K_OCP_Disp.Seq[currTemp].EndCurrWatt = dat+1;
		}else if(cnt==P_F_OCP_EndCurr){
			P3K_OCP_Disp.Seq[currTemp].EndCurrWatt = dat;
			if(P3K_OCP_Disp.Seq[currTemp].StartCurrWatt>=dat)
				P3K_OCP_Disp.Seq[currTemp].StartCurrWatt = dat-1;
		}else if(cnt==P_F_OCP_StepCurr)
			P3K_OCP_Disp.Seq[currTemp].StepCurrWatt = dat;
		else if(cnt==P_F_OCP_StepTime){
			P3K_OCP_Disp.Seq[currTemp].StepTime = dat;
			if(P3K_OCP_Disp.Seq[currTemp].DelayTime>=dat)
				P3K_OCP_Disp.Seq[currTemp].DelayTime = dat - 1;
		}else if(cnt==P_F_OCP_TrigVolt)
			P3K_OCP_Disp.Seq[currTemp].TrigVolt = dat;
		else if(cnt==P_F_OCP_DelayTrig){
			P3K_OCP_Disp.Seq[currTemp].DelayTime = dat;
		}else if(cnt==P_F_OCP_LastCurr)
			P3K_OCP_Disp.Seq[currTemp].LastCurrWatt = dat;
		break;
#endif	
#if Enable_OPP_function
		case P_FUNC_OPP:
			currTemp = P3K_OPP_Disp.CurrTemp;
			if(cnt==P_F_OPP_CurrTemp)
				P3K_OPP_Disp.CurrTemp = dat; //0~11
			else if(cnt==P_F_OPP_Range)
				P3K_OPP_Disp.Seq[currTemp].Range = dat;
			else if(cnt==P_F_OPP_StartCurr) {
				P3K_OPP_Disp.Seq[currTemp].StartCurrWatt = dat;
				if(P3K_OPP_Disp.Seq[currTemp].EndCurrWatt<=dat)
					P3K_OPP_Disp.Seq[currTemp].EndCurrWatt = dat+1;
			} else if(cnt==P_F_OPP_EndCurr) {
				P3K_OPP_Disp.Seq[currTemp].EndCurrWatt = dat;
				if(P3K_OPP_Disp.Seq[currTemp].StartCurrWatt>=dat)
					P3K_OPP_Disp.Seq[currTemp].StartCurrWatt = dat-1;
			} else if(cnt==P_F_OPP_StepCurr)
				P3K_OPP_Disp.Seq[currTemp].StepCurrWatt = dat;
			else if(cnt==P_F_OPP_StepTime) {
				P3K_OPP_Disp.Seq[currTemp].StepTime = dat;
				if(P3K_OPP_Disp.Seq[currTemp].DelayTime>=dat)
					P3K_OPP_Disp.Seq[currTemp].DelayTime = dat - 1;
			} else if(cnt==P_F_OPP_TrigVolt)
				P3K_OPP_Disp.Seq[currTemp].TrigVolt = dat;
			else if(cnt==P_F_OPP_DelayTrig) {
				P3K_OPP_Disp.Seq[currTemp].DelayTime = dat;
			} else if(cnt==P_F_OPP_LastCurr)
				P3K_OPP_Disp.Seq[currTemp].LastCurrWatt = dat;
			break;
#endif
	
#if Enable_Battery_Discharge
		case P_FUNC_batt:
			if(cnt==P_F_BATT_Mode) {
				BattDisp.Mode = dat;
			}else if(cnt==P_F_BATT_Range) {
				BattDisp.Range = dat;
			}else if(cnt==P_F_BATT_Set) {
				BattDisp.Setting = dat;
			}else if(cnt==P_F_BATT_SRUP) {
				//BattDisp.SRUP = dat;		
			}else if(cnt==P_F_BATT_SRDW) {
				//BattDisp.SRDW = dat;
			}else if(cnt==P_F_BATT_StopT) { 				
				if(BattDisp.timeCnt==0) {
					BattDisp.StopHour = dat;
				} else if(BattDisp.timeCnt==1) {
					BattDisp.StopMin = dat;
				} else {
					BattDisp.StopSec = dat;
				}
				BattDisp.StopTime = BattDisp.StopHour*3600+BattDisp.StopMin*60+BattDisp.StopSec;
			} else if(cnt==P_F_BATT_StopC) {
				BattDisp.StopCapa = dat;		
			} else if(DispCT==P_F_BATT_StopV) {
				BattDisp.StopValt = dat;
			}							
			break;
#endif
#if Enable_LED_function
		case P_FUNC_FLED:
			currTemp = P3k_FLed_Disp.currTemp;
			if(DispCT==P_F_LED_RESPONSE){ //RESPONSE
				P3k_FLed_Disp.seq[currTemp].response = dat;	
			}
			break;
		case P_FUNC_FLED_EDIT:
		case P_FUNC_FLED_EXECUTE:	
			currTemp = P3k_FLed_Disp.currTemp;
			switch(P3k_FLed_Disp.seq[currTemp].mode){
				case P_F_LED_MODE_VoIo:
				case P_F_LED_MODE_VoIoRc:	
					if(cnt==P_F_LED_Edit_P1){ //Vo
						P3k_FLed_Disp.seq[currTemp].vo = dat;		
					}else if(cnt==P_F_LED_Edit_P2){//Io	
						P3k_FLed_Disp.seq[currTemp].io = dat;	
					}else if(cnt==P_F_LED_Edit_P3) {//Rcoff
						P3k_FLed_Disp.seq[currTemp].rdcoff = dat;		
					}
					break;					
				case P_F_LED_MODE_VoIoRd:
					if(cnt==P_F_LED_Edit_P1){//Vo
						P3k_FLed_Disp.seq[currTemp].vo = dat;	
					}else if(cnt==P_F_LED_Edit_P2){//Io	
						P3k_FLed_Disp.seq[currTemp].io = dat;	
					}else if(cnt==P_F_LED_Edit_P3) {//Rd
						P3k_FLed_Disp.seq[currTemp].rd = dat;	
					}
					break;
				case P_F_LED_MODE_VoIoVf:
					if(cnt==P_F_LED_Edit_P1){//Vo
						P3k_FLed_Disp.seq[currTemp].vo = dat;	
					}else if(cnt==P_F_LED_Edit_P2){//Io	
						P3k_FLed_Disp.seq[currTemp].io = dat;	
					}else if(cnt==P_F_LED_Edit_P3) {//Vf
						P3k_FLed_Disp.seq[currTemp].vf = dat;	
					}
					break;
				case P_F_LED_MODE_VfRdPcs:
					if(cnt==P_F_LED_Edit_P1){ //Vf
						P3k_FLed_Disp.seq[currTemp].vf = dat;	
					}else if(cnt==P_F_LED_Edit_P2){//Rd	
						P3k_FLed_Disp.seq[currTemp].rd = dat;	
					}else if(cnt==P_F_LED_Edit_P3) {//pcs
						P3k_FLed_Disp.seq[currTemp].pcs = dat;	
					}
					break;
				default:
					break;	
			}
			
		break;
	case P_FUNC_CLED:
		currTemp = P3k_CLed_Disp.currTemp;
		if(DispCT==P_CLED_RESPONSE){ //RESPONSE
			P3k_CLed_Disp.seq[currTemp].response = dat;	
		}else if(DispCT==P_CLED_VO){ //Vo
			P3k_CLed_Disp.seq[currTemp].vo= dat;	
		}else if(DispCT==P_CLED_IO){
			P3k_CLed_Disp.seq[currTemp].io= dat;
		}
		break;
	case P_FUNC_CLED_EDIT:
		currTemp = P3k_CLed_Disp.currTemp;
		P3k_CLed_Disp.seq[currTemp].rdcoff = dat;	
		
		break;	
#endif				

	default:
		break;
	}
}
unsigned short get_DynaFreqDutyRangeLimit (unsigned char CurrMode)
{
	unsigned char Frequency_Range;
	unsigned short Frequency_Count,MaxMinErr;
	double Resolution,Real_Frequency,Real_Total_Timer,RealTime1_100,f_MaxMinErr;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	switch(CurrMode) {
	case CC_MODE:
		Frequency_Range = Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency_Range;
		Frequency_Count = Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency;
		break;
	case CR_MODE:
		Frequency_Range = Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency_Range;
		Frequency_Count = Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency;
		break;
	case CP_MODE:
		Frequency_Range = Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency_Range;
		Frequency_Count = Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency;
		break;
	default:
		return 0;
	}
	if(Frequency_Range == Dyn_Freq_TimeBase_100Hz)
		Resolution = 100;
	else if(Frequency_Range == Dyn_Freq_TimeBase_10Hz)
		Resolution = 10;
	else if(Frequency_Range == Dyn_Freq_TimeBase_1Hz)
		Resolution = 1;
	else
		Resolution = 0.1;

	Real_Frequency = Frequency_Count * Resolution;
	Real_Total_Timer = (1 / Real_Frequency) * 1000;
	RealTime1_100 = Real_Total_Timer * 0.01 ;

	if(Real_Frequency<1000) {
		return 10;//max = 990;	min = 10;
	} else { //
		f_MaxMinErr = (double)0.010025*10/RealTime1_100;
		MaxMinErr = (unsigned short)f_MaxMinErr;
		if(MaxMinErr<10) {
			return 10;//max = 990;	min = 10;
		} else {
			return MaxMinErr;//max = 1000-MaxMinErr; min = MaxMinErr;
		}
	}
}


