

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

extern unsigned short New_Set_Count_To_FPGA;
extern char Stop_Next_Proc;
extern STR_PARSER parser_UART;
extern UBYTE Trg_wait_flag;
extern void Auto_Load_Off(void);
extern BYTE Prog_Seq_Next(BYTE chnum, BYTE x);
extern void BackupNSeq(void);
extern void BackupFSeq(void);
extern void BackupUserDefaultData(char mode);
extern void BackupRunProg(void);
extern void BackupRunSeq(void);
extern void BackupSerialNumber(void);
extern void BuzzerFunction(UBYTE Buzzer_Mode,WORD ith);
extern BYTE Chan_Range(BYTE chnum,BYTE x);
extern BYTE Chan_Vrange(BYTE chnum,BYTE x);
extern void Control_LCDBRCon(void);
extern BYTE Cali_Func(BYTE chnum, BYTE x);
extern BYTE Cal_PSense(BYTE chnum, BYTE x);
extern void Cal_Init_Proc(void);
extern void ClearKeyBoard(void);
extern void clear_status_byte_bits(u_8 srq_byte);
extern void ClearP3KChanAllBG(UWORD c);
extern void ClrDispCnt(char mode, char ct, char sec, char ssc, char bct, char scl);
extern void CutOffTime_Process(void);
extern void Cursor1DisplayOn(void);
extern void Cursor1DisplayOff(void);
extern void Cursor2DisplayOn(void);
extern void Cursor2DisplayOff(void);
extern void DefaultMenu(char mode);
extern ULONG DataCheckSum(unsigned char *dest,long size);
extern char Display_Parameter_Pro(double Parameter,char * buf,char precision);
extern void EDGIO_Control( char mode, char onoff);
extern void Enable_TIMER1 (INT32U PERIOD);
extern void FPGA_Init(void);
extern void FloatWindowsDispOn(void);
extern void FloatWindowsDispOff(void);
extern void Float_Windows_Setting(int x1, int y1,int x2, int y2,GUI_COLOR color);
extern void Float_Windows_Setting1(int x1, int y1,int x2, int y2,GUI_COLOR color);

extern void FloatWindows_StringAt(const char GUI_FAR *s, int x, int y);
extern char GetNowRange(void);
extern void GetResolution(void);
extern void GetResolution_Default(BYTE chan);
extern float Get_Parallel_Parameter(unsigned char IRange);
extern char InitDGIOStatus(char cnt);
extern void LCD_Blink(void);
extern void LoadDefaultProc(char mode);
extern void Menu_Message(char *Message,int x,int y);
extern void Menu_Message_Pro(char Mode,char *Message);
extern void MenuDecoderAddr(p3k_send_tx_list *data);
extern void PlaceFSeqMemory(void);
extern void PlaceNSeqChain(void);
extern void PlaceProgChain(void);
extern void PEL3000_LED_Control( char mode, char onoff);
extern BYTE Recall_Data(BYTE chnum, BYTE x);
extern void RedrawSystemInfo(void);
extern void RedrawInterface(void);
extern void ReadyBackupFSeqData(void);
extern UBYTE Recall2Mem(char mode, UWORD no);
extern void Recall2Display(void);
extern void RestoreRealChan(void);
extern void RecallSetupData(char Address);
extern UBYTE RecallProgDataFromSCPI(UBYTE * Data_Address_Ptr);
extern UBYTE RecallSetupDataFromSCPI(UBYTE *Data_Address_Ptr);
extern UBYTE RecallPresetDataFromSCPI(UBYTE *Data_Address_Ptr);
extern UBYTE RecallNSeqDataFromSCPI(UBYTE * Data_Address_Ptr);
extern UBYTE RecallFSeqDataFromSCPI(UBYTE *Data_Address_Ptr);
extern void Rem_CalPSense(void);
extern UBYTE Rem_Input_Cal_Data(double Rem_Cal_Data,UBYTE Rem_Cal_Point);
extern void Rem_Load_Cal_Default(void);
extern void Rem_Sel_Cal_Point(UBYTE Cal_POINT);
extern void Rem_Save_Cal_Data(void);
extern void SaveCalData_DataFlash(void);
extern BYTE Save_Data(BYTE chnum, BYTE x);
extern BYTE Save_Fill_Action(BYTE chnum, BYTE x);
extern void Save2Mem(char mode, UWORD no);
extern void SaveProgDataToFile(void);
extern void SavePresetDataToFile(void);
extern void SaveSetupDataToFile(void);
extern void SaveNSeqDataToFile(void);
extern void SaveFSeqDataToFile(void);
extern void SaveRecall_FSeq_Data(BYTE dire);
extern void SaveRecall_NSeq_Data(BYTE dire);
extern void SaveRecall_Prog_Data(BYTE dire);
extern void SaveSeqFun(void);
extern void SaveSetupData(void);
extern void SaveSetupDataAction(char SMEMORY_ADDR);
extern void ScrCopyToScrOut(int copysize );
extern void set_status_byte_bits(u_8 srq_byte);
extern void SetRTC(UWORD second_flag);
extern void SendTXData(void *data);
extern void SeqMemSetupFun(void);
extern void ShowCalMessage(void);
extern void Show_Calibration_Error_Window(void);
extern void ShowMessage(char* STR);
extern void ShowSpace(char no,int x,int y);
extern void Show_XYZ_Window(void);
extern void SlaveInitProc(void);
extern void SlaveSyncProc(char chan_number);
extern void SlaveFastSyncProc(char chan_number);
extern void SoftStartDoubleCheck(void);
extern BYTE Time_Set(BYTE chnum, BYTE x);
extern void Update_Panel(void);
extern BYTE Upgrading(char source,char *FileName);
extern BYTE UpgradingMain(char * FileName);
extern void Update_Panel(void);
extern BYTE Upgrading_SCPI(char source,UBYTE *SCPI_Data,LONG FileSize);
extern BYTE UpgradingSetupData_SCPI(UBYTE *SCPI_Data);
extern void Recall_Factory_Action(char Mode);
extern void RecallUserDefault(char mode);
extern void (*WOutgoBuffer)(UBYTE *, UBYTE);
extern void (*WBOutgoBuffer)(UBYTE *, ULONG, UBYTE);
extern void Prot_Setting_Process(void);
extern timer_set SEQ_TIMER;
extern char SEQ_Stop_Continue;
char ErrEventQueueCtr,ErrEventQueueOutPtr,ErrEventQueueInPtr,fQueueErr;
extern UBYTE usbrun;
extern UBYTE PC_scriptrun;
extern p3k_send_tx_list TX_LIST;
extern GELMASTER *gel;
char CommData_Buff[CommData_Size];
unsigned long CommData_Buff_Count;
extern ULONG CommFileData_Count;
extern UBYTE *CommFileData_Pointer;
//extern unsigned short CommFileData_TimeOut;
extern GPIB_RING_BUF GpibBuf;
//extern char ErrEventQueue[100];
//extern char ErrEventQueueInPtr;
extern unsigned short get_DynaFreqDutyRangeLimit (unsigned char CurrMode);
extern void BackupOCP(void);


extern struct tm CurrentTime;
extern UBYTE PC_scriptrun;
extern char disErrQ[64];
extern UBYTE usbrun;
extern char only_text;
extern void ExportProcess(char Mode,float Float_Value,long integer_Value,char *str_data, char precision);
extern long SCPI_InputToStep(double input,double resolution);
extern long SCPI_InputToStep_s(double input,double resolution);
extern void QuesStatusReporting_P3K(void);
extern void ChanStatusReporting_P3K(void);
extern void CSumStatusReporting_P3K(void);
extern void StandardEventStatus(void);
extern void StatusByteRegister(void);
extern void Status_Reporting(void);

extern void Wait_For_MDMA_Ready(void);
#if Enable_AutoLoad
extern void Auto_Load_On(void);
#endif

extern void Cal_Init_Proc(void);
//void idSTB(void);



//==============================================================================
// @ Typedef
//==============================================================================

//==============================================================================
// @ Enum
//==============================================================================

//==============================================================================
// @ Define
//==============================================================================
#define Float_Data 		0
#define Integer_Data	1
#define String_Data		2
#define ULONG			unsigned long
#define UBYTE			unsigned char
#define Disp_Start_Y2						25	/*PEL-2000 Display Setting(Old)*/

#define Disp_Start_X						5
#define Disp_Interval						25
#define Disp_Start_Y0						72	/*Display Setting Mode*/
#define Disp_Start_Y1						120	/*Display Measure + Setting Mode*/
#define Para_Start_X						200
#define Unit_Start_X						202

#define Conf_Para_Start_X					212
#define Conf_Unit_Start_X					212

#define HiLight_Length						51
#define	Scroll_Bar_Width					7
#define Scroll_Bar_Start_X					260
#define	Disp_Item_Num0						3	/*Display Measure + Setting Mode*/
#define	Disp_Item_Num1						5	/*Display Setting Mode*/
#define SCPI_GW								0
#define SCPI_KIKUSUI						1

#define Normal_Parallel_Function			0

#define	SingleChannel						0	/*Command_Mode:0 Single Channel Command*/
#define	AllChannel							1	/*Command_Mode:1 All Channel Command*/

//--- Trigger Active ---
#define _TRIG_ACT_IDLE						0 //Trigger Idle.
#define _TRIG_ACT_WTG						1 //Waiting for Trigger.
#define _TRIG_ACT_IMM						2 //IMMediate Trigger.



//==============================================================================
// @ Declared Functions
//==============================================================================

//==============================================================================
// @ Structures
//==============================================================================

//==============================================================================
// @ Variables
//==============================================================================
char SCPI_Version[30] =	"1.02 in Feb 26,2013";
UBYTE Cal_Point;
UBYTE Cal_Point_Flag;
UBYTE Cal_Status=0;
UBYTE Util_Scpi_Ver_Flag=0;
/*
static UBYTE TrigSW = 0;
static UBYTE TrigImmediate = 0;
static UBYTE TrigContinous = 0;
static double TrigCOND = 0;
static UBYTE TrigCOND_Range = 0xFF;
static double TrigCURR = 0;
static UBYTE TrigCURR_Range = 0xFF;
*/
typedef struct	{
	UBYTE TrigStatus;		/* IDLE:0, TrigWait:1, TrigUpdate:2 */
	UBYTE LoadOnOff;				/*LOAD OFF:0 / LOAD ON:1 / nothing:2 */
	UBYTE Immediate;		/*on/off */
	UBYTE Contionous;		/*on/off */
	UWORD Cond;			/*MHO */
	UBYTE CondRange;		/* range:IL,IM,IH */
	UWORD Curr;			/* A */
	UBYTE CurrRange;		/* range:IL,IM,IH */
	UBYTE ParaNum;         /* number of parallel */
} TriggStr;

static TriggStr Trig = {
	.TrigStatus = 0,
	.LoadOnOff = 0,
	.Immediate =0,
	.Contionous = 0,
	.Cond = 0,
	.CondRange = 6,
	.Curr = 0,
	.CurrRange =6,
	.ParaNum = 0
};



//==============================================================================
// @ Constants
//==============================================================================
short int Cal_crc(unsigned char *ptr, unsigned short len)
{
	static const  char auchCRCHi[]= {
		0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
		0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
		0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,
		0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
		0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,
		0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
		0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,
		0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
		0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
		0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
		0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,
		0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
		0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40
	};
	static const  char auchCRCLo[]= {
		0x00,0xc0,0xc1,0x01,0xc3,0x03,0x02,0xc2,0xc6,0x06,0x07,0xc7,0x05,0xc5,0xc4,0x04,0xcc,0x0c,0x0d,0xcd,
		0x0f,0xcf,0xce,0x0e,0x0a,0xca,0xcb,0x0b,0xc9,0x09,0x08,0xc8,0xd8,0x18,0x19,0xd9,0x1b,0xdb,0xda,0x1a,
		0x1e,0xde,0xdf,0x1f,0xdd,0x1d,0x1c,0xdc,0x14,0xd4,0xd5,0x15,0xd7,0x17,0x16,0xd6,0xd2,0x12,0x13,0xd3,
		0x11,0xd1,0xd0,0x10,0xf0,0x30,0x31,0xf1,0x33,0xf3,0xf2,0x32,0x36,0xf6,0xf7,0x37,0xf5,0x35,0x34,0xf4,
		0x3c,0xfc,0xfd,0x3d,0xff,0x3f,0x3e,0xfe,0xfa,0x3a,0x3b,0xfb,0x39,0xf9,0xf8,0x38,0x28,0xe8,0xe9,0x29,
		0xeb,0x2b,0x2a,0xea,0xee,0x2e,0x2f,0xef,0x2d,0xed,0xec,0x2c,0xe4,0x24,0x25,0xe5,0x27,0xe7,0xe6,0x26,
		0x22,0xe2,0xe3,0x23,0xe1,0x21,0x20,0xe0,0xa0,0x60,0x61,0xa1,0x63,0xa3,0xa2,0x62,0x66,0xa6,0xa7,0x67,
		0xa5,0x65,0x64,0xa4,0x6c,0xac,0xad,0x6d,0xaf,0x6f,0x6e,0xae,0xaa,0x6a,0x6b,0xab,0x69,0xa9,0xa8,0x68,
		0x78,0xb8,0xb9,0x79,0xbb,0x7b,0x7a,0xba,0xbe,0x7e,0x7f,0xbf,0x7d,0xbd,0xbc,0x7c,0xb4,0x74,0x75,0xb5,
		0x77,0xb7,0xb6,0x76,0x72,0xb2,0xb3,0x73,0xb1,0x71,0x70,0xb0,0x50,0x90,0x91,0x51,0x93,0x53,0x52,0x92,
		0x96,0x56,0x57,0x97,0x55,0x95,0x94,0x54,0x9c,0x5c,0x5d,0x9d,0x5f,0x9f,0x9e,0x5e,0x5a,0x9a,0x9b,0x5b,
		0x99,0x59,0x58,0x98,0x88,0x48,0x49,0x89,0x4b,0x8b,0x8a,0x4a,0x4e,0x8e,0x8f,0x4f,0x8d,0x4d,0x4c,0x8c,
		0x44,0x84,0x85,0x45,0x87,0x47,0x46,0x86,0x82,0x42,0x43,0x83,0x41,0x81,0x80,0x40
	};
	unsigned char uchCRCHi=0xFF; /*CRC high byte*/
	unsigned char uchCRCLo=0xFF; /*CRC low byte*/
	unsigned uIndex;
	while(len--) { /*pass through message buffer*/
		uIndex=uchCRCHi^*ptr++; /*calculate the CRC*/
		uchCRCHi=uchCRCLo^auchCRCHi[uIndex];
		uchCRCLo=auchCRCLo[uIndex];
	}
	return (uchCRCHi<<8|uchCRCLo);
}

void SCPI_Printf(char* buff,char* str_data,float Float_Value,char precision)
{
	char *Output_data;
	ULONG i;

	if(Float_Value<0)
		Float_Value=0;

	if(precision==1)
		sprintf( (char*)buff, "%s%1.1f",str_data, Float_Value );
	else if(precision==2)
		sprintf( (char*)buff, "%s%1.2f",str_data, Float_Value );
	else if(precision==3)
		sprintf( (char*)buff, "%s%1.3f",str_data, Float_Value );
	else if(precision==4)
		sprintf( (char*)buff, "%s%1.4f",str_data, Float_Value );
	else if(precision==6) {
		if(Float_Value>=10000)		sprintf( (char*)buff, "%s%5.2f",str_data, Float_Value);
		else if(Float_Value>=1000)	sprintf( (char*)buff, "%s%4.3f",str_data, Float_Value);
		else if( Float_Value >= 100)	sprintf( (char*)buff, "%s%3.4f",str_data, Float_Value);
		else if(Float_Value>=10)		sprintf( (char*)buff, "%s%2.5f",str_data, Float_Value );
		else						sprintf( (char*)buff, "%s%1.6f",str_data, Float_Value );
	} else if(precision==7) {
		if(Float_Value>=10000)		sprintf( (char*)buff, "%s%5.3f",str_data, Float_Value);
		else if(Float_Value>=1000)	sprintf( (char*)buff, "%s%4.4f",str_data, Float_Value);
		else if( Float_Value >= 100)	sprintf( (char*)buff, "%s%3.5f",str_data, Float_Value);
		else if(Float_Value>=10)		sprintf( (char*)buff, "%s%2.6f",str_data, Float_Value );
		else						sprintf( (char*)buff, "%s%1.7f",str_data, Float_Value );
	}	else {//precision = 5;
		if(Float_Value>=10000)		sprintf( (char*)buff, "%s%5.1f",str_data, Float_Value);
		else if(Float_Value>=1000)	sprintf( (char*)buff, "%s%4.2f",str_data, Float_Value);
		else if( Float_Value >= 100)	sprintf( (char*)buff, "%s%3.3f",str_data, Float_Value);
		else if(Float_Value>=10)		sprintf( (char*)buff, "%s%2.4f",str_data, Float_Value );
		else						sprintf( (char*)buff, "%s%1.5f",str_data, Float_Value );
	}
}

void Draw_Set_parameter (void){
#if Enable_Optim_display
	DataRedrawFlag |= BG_CLEAR_FLAG;
	B_DispCT = DispScrCurrLoc;
	only_text = 2;
#endif
}


//==============================================================================
// @ Functions
//==============================================================================
void SetRemoteMode(char Remote_Mode)
{
	/*Remote_Mode = 1, Remote Fast*/
	/*Remote_Mode = 0, Remote Normal*/
	UWORD Backup_TimeOut;
	if(Remote_Mode) { //ON or OFF
		Wait_For_MDMA_Ready();
		if(DGIOCtrlFlag&REM_Mode_Fast)return;
		if(REM_CONT==0) {
			REM_CONT = 1;
			SysRedrawFlag |= REM_LOC_UPDATA;
		}
		Cursor1DisplayOff();
		Cursor2DisplayOff();
		if(parser_UART.errQueue.cnt) {
			if(p3k_Measure_Data.Alarm){
				Float_Windows_Setting(0,0,319,0x3b,Message_Font_Bolor);
				GUI_SetFont(Parameter_Font);
				GUI_SetBkColor(Message_Font_Bolor);
				GUI_SetColor(MEM_WHITE);
				GUI_SetTextAlign(GUI_TA_LEFT);
				FloatWindows_StringAt(" Remote Fast ",100,100);
				GUI_SetBkColor(MEM_WHITE);
				GUI_SetColor(Message_Font_Bolor);
				GUI_SetTextAlign(GUI_TA_LEFT);
				FloatWindows_StringAt("                 Command Error                ",10,170);
			}else{
				Float_Windows_Setting(0,0,319,0x3b,MEM_WHITE);
				GUI_SetFont(Parameter_Font);
				GUI_SetBkColor(MEM_WHITE);
				GUI_SetColor(Message_Font_Bolor);
				GUI_SetTextAlign(GUI_TA_LEFT);
				FloatWindows_StringAt(" Remote Fast ",100,100);
				GUI_SetBkColor(Message_Font_Bolor);
				GUI_SetColor(MEM_WHITE);
				GUI_SetTextAlign(GUI_TA_LEFT);
				FloatWindows_StringAt("                 Command Error                ",10,170);
			}	
		} else {
			if(p3k_Measure_Data.Alarm){
				Float_Windows_Setting(0,0,319,0x3b,Message_Font_Bolor);
				GUI_SetFont(Parameter_Font);
				GUI_SetBkColor(Message_Font_Bolor);
				GUI_SetColor(MEM_WHITE);		
				GUI_SetTextAlign(GUI_TA_LEFT);
				FloatWindows_StringAt(" Remote Fast ",100,100);
			}else{
				Float_Windows_Setting(0,0,319,0x3b,MEM_WHITE);
				GUI_SetFont(Parameter_Font);
				GUI_SetBkColor(MEM_WHITE);
				GUI_SetColor(Message_Font_Bolor);		
				GUI_SetTextAlign(GUI_TA_LEFT);
				FloatWindows_StringAt(" Remote Fast ",100,100);
			}	
		}
		Float_Window_Count = 150;
		FloatWindowsDispOn();

		Backup_TimeOut = 200;
		DMA_Update_Flag = 1;

		CtrlFlag1 |= Disp_IRange_Window + Float_Windows_DispOn;
		Update_Panel();
		DGIOCtrlFlag|=REM_Mode_Fast;

	} else {
		if((DGIOCtrlFlag&REM_Mode_Fast)==0)return;
		if(REM_CONT) {
			REM_CONT=0;
			SysRedrawFlag |= REM_LOC_UPDATA;
		}
		GetResolution();
		DGIOCtrlFlag&=~(REM_Mode_Fast);
		ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
		MenuRedrawFlag|= MENU_CHANGE;
		if(DispMode!=DispMode_SELECT_CH)
			DispMode = DispMode_SELECT_CH;
		if(M_num<= P_FUNC_MAIN) {
			DispMode=1;
		} else {
			DispMode=0;
		}
		DMA_Update_Flag = 1;
		OSTimeDly(30);
		Cursor1DisplayOn();
		Cursor2DisplayOn();
		FloatWindowsDispOff();
		DMA_Update_Flag = 1;
	}
}

void idCommandError(STR_PARSER * p)
{
// Code Begin
	scpi_SetCommandError( p, _ERR_113_Undefined_header);
// Code End
}

void id_CAL(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {

	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}

void id_CLS(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		//1. Clear SESR Register. (IEEE 488.2)
		//2. Clear Operation Status Event Register. (SCPI)
		//3. Clear Questionable Status Event Register. (SCPI)
		//4. Clear Error/Event Queue. (SCPI)
		//5. Clear Error/Event CSUM. (SCPI)
		scpi_InitErrorQueue(p);
		intfSCPI_SetESR(p->pInterface, 0);
		intfSCPI_SetOperReg(p->pInterface, _INTF_REG_EVEN, 0);
		intfSCPI_SetQuesReg(p->pInterface, _INTF_REG_EVEN, 0);
		intfSCPI_SetCsumReg(p->pInterface, _INTF_REG_EVEN, 0);

		/*Clear Output Buffer*/
		Output_Buffer_Count=0;
		for(CommData_Buff_Count=0; CommData_Buff_Count<8192; CommData_Buff_Count++)
			CommData_Buff[CommData_Buff_Count]=0;
		CommData_Buff_Count=0;
		SysRedrawFlag |= 0x10;//ERROR_UPDATA;
	}
// Code End
}

void id_ESE(STR_PARSER * p)
{
	unsigned long ESE_Value;
	UBYTE Command_Done;
	UBYTE RealValue;
	GW_TYPE value;
	char num;
// Code Begin

	//_DEBUG_MSG("idESE\n");

	if(scpi_IsQueryCommand(p)) {
		//length = gw_ValueToString(&buf[0], intfSCPI_GetESE(p->pInterface), _DEC_STRING);
		//scpi_Write( p, (char *)buf, length, _GW_IOWR_BUF, 0);
		RealValue = intfSCPI_GetESE(p->pInterface);
		ExportProcess(Integer_Data,0,RealValue,0,0);
	} else {
		//--- Get number of parameters. ---//
		num = scpi_IsThereParameters(p);

		if(1 == num) {
			//--- Get parameters. ---//
			if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
				//add application code here.
				if(0 > value.si) {
					scpi_SetCommandError( p, _ERR_121_Invalid_character_in_number);
				} else {
					intfSCPI_SetESE(p->pInterface, value.si);
				}
			} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				//add application code here.
				scpi_SetCommandError( p, _ERR_148_Character_data_not_allowed);
			} else if(1 == scpi_IsStringParameters( p, 0)) {
				//add application code here.
				scpi_SetCommandError( p, _ERR_158_String_data_not_allowed);
			} else if(0 == scpi_GetFloatParameters( p, 0, (double*) &value.d)) {
				//add application code here.
				scpi_SetCommandError( p, _ERR_120_Numeric_data_error);
			} else if(0 == scpi_GetExpressionParameters( p, 0, (char*) &value)) {
				//add application code here.
				scpi_SetCommandError( p, _ERR_178_Expression_data_not_allowed);
			} else if(1 == scpi_IsBlockParameters( p, 0)) {
				//length = scpi_GetBlockParameters( p, 0, (unsigned int*) &value.ui);
				//add application code here.
				scpi_SetCommandError( p, _ERR_168_Block_data_not_allowed);
			} else { //anomalism. no type.
				//add application code here.
				scpi_SetCommandError( p, _ERR_310_System_error);
			}
		} else if(1 < num) {	//excess Parameters.
			scpi_SetCommandError( p, _ERR_115_Unexpected_number_of_parameters);
		} else if(0 == num) { //No Parameters.
			//add application code here.
			scpi_SetCommandError( p, _ERR_109_Missing_parameter);
		} else { //anomalism. An error has occurred. The point zero.
			//add application code here.
			scpi_SetCommandError( p, _ERR_310_System_error);
		}
	}
// Code End
}

void id_ESR(STR_PARSER * p)
{
	UWORD RealValue;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		RealValue = intfSCPI_GetESR(p->pInterface);
		ExportProcess(Integer_Data,0,RealValue,0,0);
		intfSCPI_SetESR(p->pInterface, 0);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}

void id_IDN(STR_PARSER * p) //check_0913
{
	char Data_Buffer[60];
	char p3k_Model_Number[24];
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_NSeq_Str	*NSeq_Disp_tmp = &P3k_NSeq_Disp;
	P3k_NSeq_Str	*NSeq_Data_tmp = &P3k_NSeq_Data;
	Serial_Number_Str	*Serial = &P3k_Serial_Number;

// Code Begin
	//printf("idIDN\n");
	if(scpi_IsQueryCommand(p)) {
//		scpi_Write( p, (char *)tIDN, strlen(tIDN), _GW_IOWR_BUF, 0);
		if(Serial->Version == GW_Version) {
			if(MODEL3031E == Data_tmp->INFO.MACHTYPE)
				sprintf(p3k_Model_Number, "GW,PEL-3031E");
			else if(MODEL3032E == Data_tmp->INFO.MACHTYPE)
				sprintf(p3k_Model_Number, "GW,PEL-3032E");
			else
				sprintf(p3k_Model_Number, "GW,PEL-Default");
		} else {
			if(MODEL3031E==P3k_Chan_Data.INFO.MACHTYPE)
				sprintf( p3k_Model_Number, "TEXIO,LSG-175");
			else if(MODEL3032E==P3k_Chan_Data.INFO.MACHTYPE)
				sprintf( p3k_Model_Number, "TEXIO,LSG-350");			
			else
				sprintf( p3k_Model_Number, "TEXIO,LSG-Default");
		}						////sprintf( systemInfo_Data[systemInfo_count++],	" %d.%02d.%03d",Main_Version,Sub_Version,Machine_Number);
		//sprintf(Data_Buffer,"%s,%s,V%s.%03d",p3k_Model_Number,	Serial->Product_Serial_Number,	MASTER_VERSION,1);
		//sprintf(Data_Buffer,"%s,%s,V%01d.%02d.%03d",p3k_Model_Number,Serial->Product_Serial_Number, Main_Version,Sub_Version,Machine_Number);
		sprintf(Data_Buffer,"%s,%s,V%01d.%02d",p3k_Model_Number,Serial->Product_Serial_Number, Main_Version,Sub_Version);

		ExportProcess(String_Data,0,0,Data_Buffer,0);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}


void id_OPC(STR_PARSER * p)
{
// Code Begin
	//_DEBUG_MSG("idOPC\n");
	GW_TYPE value;
	int num = 0;

	if(scpi_IsQueryCommand(p)) {
		ExportProcess(Integer_Data,0,1,0,0); //OCP always=1
	} else {
		intfSCPI_SetESR( p->pInterface, (intfSCPI_GetESR(p->pInterface) | 0x01));
	}
// Code End

}
void idABORt(STR_PARSER * p);
void id_CLS(STR_PARSER * p);
void idSYNCDEFaultRECall(STR_PARSER * p);


void id_RST(STR_PARSER * p)
{
	p3k_send_tx_list	tx_data;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		idABORt(p);
		id_CLS(p);
		if(CtrlFlag1&Alarm_Latch) {
			p3k_Measure_Data.Alarm = No_Alarm;	// Cursor1?PCursor2AU�o??zcuao*/
			Frame_Change();
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
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Prot_Status;
			SendTXData(&tx_data);
			CtrlFlag1 &= ~Alarm_Latch;
			CtrlFlag1 &= ~Function_Lock;
			CtrlFlag1 &= ~Disp_Middle_Message;
			CtrlFlag1 |= Float_Windows_DispOff;
		}
		idSYNCDEFaultRECall(p);
		
		Trig.TrigStatus = 0;
		Trig.LoadOnOff = 0;
		Trig.Immediate =0;
		Trig.Contionous = 0;
		Trig.Cond = 0;
		Trig.CondRange = 6;
		Trig.Curr = 0;
		Trig.CurrRange =6;
		Trig.ParaNum = 0;
		Trg_wait_flag =0;
		SCPI_RemFastDelay = 1;

	}
// Code End
}


void id_RCL(STR_PARSER * p)
{
	GW_TYPE value;
	p3k_send_tx_list	tx_data;
	p3k_file_util_str	*File_Utility = &p3k_File_Utility_BAR;

	char str[30];
	UBYTE i,save_number,Command_Done=0;
	ULONG Value_temp;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

// Code Begin
	if(scpi_IsQueryCommand(p)) {

	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			//data = (int) (value.si * MachineScale[_ISR_SCALE]);
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if((value.si >= 1)&&(value.si <= 256)) {
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
		}
		if(Command_Done) {
			File_Utility->MEMORY_ADDR = (char)(value.si-1);
			Soft_Key_Temp=0;

			if(Recall2Mem(SR_MEMORY_MODE, p3k_File_Utility_BAR.MEMORY_ADDR)==0) {
				Soft_Key_Temp = 1;
				return ;
			}
			if((Data_tmp->CURRMODE!=Disp_tmp->CURRMODE)&&(UTILITY.LOAD_CTL)) {
				UTILITY.LOAD_CTL = Switch_OFF;
				PEL3000_LED_Control( LED_LOAD, Switch_OFF );
				if(!SCPI_Freeze_menu)
					SysRedrawFlag |= PROG_UPDATA;
				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = Machine_Load_OnOff;
				SendTXData(&tx_data);
			}

			Recall2Display();
			tx_data.ADDRH = 0x31;
			tx_data.ADDRL = 0x00;
			SendTXData(&tx_data);
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				ChanRedrawFlag |= CHAN_STATUS;
				DataRedrawFlag |=BG_CLEAR+ PARA_CHANGE;
				MenuRedrawFlag |= MENU_CHANGE;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
			}
			SCPI_RemFastDelay = 1;
		}

	}
// Code End
}



void id_SAV(STR_PARSER * p)
{
	GW_TYPE value;
	p3k_send_tx_list	tx_data;
	p3k_file_util_str	*File_Utility = &p3k_File_Utility_BAR;

	char str[30];
	UBYTE i,save_number,Command_Done=0;
	ULONG Value_temp;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

// Code Begin
	if(scpi_IsQueryCommand(p)) {

	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			//data = (int) (value.si * MachineScale[_ISR_SCALE]);
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if((value.si >= 1)&&(value.si <= 256)) {
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
		}
		if(Command_Done) {
			File_Utility->MEMORY_ADDR = (char)(value.si-1);

			DispMode = DispMode_SELECT_CH;
			if ((M_num ==P_FILE_CHAN)&&(!SCPI_Freeze_menu))
				DataRedrawFlag	|= PARA_CHANGE + BG_CLEAR;
			/* Save Memory No 1~256 */
			MEMORY_SAVE_FLAG = M_Memory_Save_Ok;
			Save2Mem(SR_MEMORY_MODE, File_Utility->MEMORY_ADDR);
			BackupRunProg();
			SCPI_RemFastDelay = 1;
		}
	}
// Code End
}

void id_SRE(STR_PARSER * p)
{
	unsigned long SRE_Value;
	int num = 0;
	GW_TYPE value;

// Code Begin
	//_DEBUG_MSG("idSRE\n");
	if(scpi_IsQueryCommand(p)) {
		SRE_Value = intfSCPI_GetSRE(p->pInterface);
		ExportProcess(Integer_Data,0,SRE_Value,0,0);
	} else {
		//--- Get number of parameters. ---//
		num = scpi_IsThereParameters(p);

		if(1 == num) {
			//--- Get parameters. ---//
			if(1 == scpi_IsIntegerParameters( p, 0)) {
				//add application code here.
				scpi_GetIntegerParameters( p, 0, (int*) &value.si);
				if(0 > value.si) {
					scpi_SetCommandError( p, _ERR_121_Invalid_character_in_number);
				} else {
					intfSCPI_SetSRE(p->pInterface, value.si);
				}
			} else if(1 == scpi_IsKeywordParameters( p, 0)) {
				//add application code here.
				scpi_SetCommandError( p, _ERR_148_Character_data_not_allowed);
			} else if(1 == scpi_IsStringParameters( p, 0)) {
				//add application code here.
				scpi_SetCommandError( p, _ERR_158_String_data_not_allowed);
			} else if(1 == scpi_IsFloatParameters( p, 0)) {
				//add application code here.
				scpi_SetCommandError( p, _ERR_120_Numeric_data_error);
			} else if(1 == scpi_IsExpressionParameters( p, 0)) {
				//add application code here.
				scpi_SetCommandError( p, _ERR_178_Expression_data_not_allowed);
			} else if(1 == scpi_IsBlockParameters( p, 0)) {
				//length = scpi_GetBlockParameters( p, 0, (unsigned int*) &value.ui);
				//add application code here.
				scpi_SetCommandError( p, _ERR_168_Block_data_not_allowed);
			} else { //anomalism. no type.
				//add application code here.
				scpi_SetCommandError( p, _ERR_310_System_error);
			}
		} else if(1 < num) {	//excess Parameters.
			scpi_SetCommandError( p, _ERR_115_Unexpected_number_of_parameters);
		} else if(0 == num) {	//No Parameters.
			//add application code here.
			scpi_SetCommandError( p, _ERR_109_Missing_parameter);
		} else { //anomalism. An error has occurred. The point zero.
			//add application code here.
			scpi_SetCommandError( p, _ERR_310_System_error);
		}
	}
// Code End
}

void id_STB(STR_PARSER * p)
{

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		UWORD realValue;
		realValue = intfSCPI_GetSTB(p->pInterface);
		ExportProcess(Integer_Data,0,realValue,0,0);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End

}

void id_TRG(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	p3k_send_tx_list tx_data;
	UBYTE Para_num;
	Para_num = (UBYTE)Get_Parallel_Parameter(Disp_tmp->IRange);

	ResolutionTemp=((ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Resolution);
	Precision = (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].precision;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {

#if 1
		//if(_TRIG_ACT_WTG == Trig.TrigStatus) {		
		if(1 == Trig.TrigStatus) {		
			
			if(Trig.LoadOnOff==0) { //turn off
				Trig.LoadOnOff=2;	
			} else if(Trig.LoadOnOff==1){ //turn off
				if((Normal_Load==P3k_Chan_Data.Load_Type)&&(UTILITY.LOAD_CTL==0)){
					UTILITY.LOAD_CTL = 1;
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
				
					SysRedrawFlag |= PROG_UPDATA;
					PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
					Trig.CondRange = 6;
					Trig.CurrRange = 6;
				}
				Trig.LoadOnOff=2;
			}else{ //nothing

			}
			
			if(Para_num!=Trig.ParaNum) {
				Trig.CondRange = Trig.CurrRange =6;
				Trig.Curr=0;
				Trig.Cond=0;
				//return;
			}

			
			if(Disp_tmp->IRange==Trig.CurrRange) {
				if(P3k_Chan_Data.CURRMODE==P_CC) Command_Done |= 0x01;
			} else {
				//Trig.Curr=0; //initalValue
			}
			if(Disp_tmp->IRange==Trig.CondRange) {
				if(P3k_Chan_Data.CURRMODE==P_CR)Command_Done |= 0x02;
			} else {
				//Trig.Cond=0;
			}			
			Trig.Immediate = 0;
			if(Trig.Contionous==0)Trig.TrigStatus = _TRIG_ACT_IDLE;	
			Trg_wait_flag =Trig.TrigStatus;
		} else {
			scpi_SetCommandError( p, _ERR_211_Trigger_ignored);
			return;
		}		
		if(Command_Done) {
			if(Command_Done&0x01) {
				Data_tmp->CC.STA[Data_tmp->IRange].VALUE1 = Trig.Curr;
				Disp_tmp->CC.STA[Data_tmp->IRange].VALUE1 = Trig.Curr;
				tx_data.ADDRH=0x01;
				tx_data.ADDRL=0x10;
				SendTXData(&tx_data);
			}
			if(Command_Done&0x02) {
				Disp_tmp->CR.STA[Disp_tmp->IRange].VALUE1 = Trig.Cond;
				Data_tmp->CR.STA[Data_tmp->IRange].VALUE1 = Trig.Cond;
				tx_data.ADDRH=0x02;
				tx_data.ADDRL=0x10;
				SendTXData(&tx_data);
			}
			if((M_num<=P_CR)&&(Disp_tmp->CC.STADYNA==SCPI_Static_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
		}


		
#else
		if(Para_num!=Trig.ParaNum) {
			Trig.CondRange = Trig.CurrRange =6;
			if(Trig.Contionous)Trg_wait_flag = 1;
			else			   Trg_wait_flag = 0;
			return;
		}
		if(Trig.loadonff) {
			if((Trig.Immediate)||(Trig.Contionous)) {
				if(Disp_tmp->IRange==Trig.CurrRange) {
					Command_Done |= 0x01;
				} else {
					Trig.CurrRange = 6; //initalValue
				}
				if(Disp_tmp->IRange==Trig.CondRange) {
					Command_Done |= 0x02;
				} else {
					Trig.CondRange = 6;
				}
			}
		} else {}
		Trig.Immediate = 0;
		if(Trig.Contionous)Trg_wait_flag = 1;
		else			   Trg_wait_flag = 0;
		if(Command_Done) {
			if(Command_Done&0x01) {
				Data_tmp->CC.STA[Data_tmp->IRange].VALUE1 = Trig.Curr;
				Disp_tmp->CC.STA[Data_tmp->IRange].VALUE1 = Trig.Curr;
				tx_data.ADDRH=0x01;
				tx_data.ADDRL=0x10;
				SendTXData(&tx_data);
			}
			if(Command_Done&0x02) {
				Disp_tmp->CR.STA[Disp_tmp->IRange].VALUE1 = Trig.Cond;
				Data_tmp->CR.STA[Data_tmp->IRange].VALUE1 = Trig.Cond;
				tx_data.ADDRH=0x02;
				tx_data.ADDRL=0x10;
				SendTXData(&tx_data);
			}
			if((M_num<=P_CR)&&(Disp_tmp->CC.STADYNA==SCPI_Static_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
		}
#endif		
	}
// Code End
}

void id_TST(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		ExportProcess(Integer_Data,0,0,0,0);		//return 0 is passed; 1 is failed
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}

void id_WAI(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {

	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}

void idABORt(STR_PARSER * p)
{
	p3k_send_tx_list tx_data;
// Code Begin
	if(scpi_IsQueryCommand(p)) {

	} else {
		UTILITY.LOAD_CTL=0x00;
		tx_data.ADDRH=0x00;
		tx_data.ADDRL=0x0B;
		SendTXData(&tx_data);
		if(!SCPI_Freeze_menu)
			SysRedrawFlag |= PROG_UPDATA;
		PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
	}
// Code End
}

void idSYSTemERRor(STR_PARSER * p)
{
	extern volatile unsigned short SysRedrawFlag;
	char str[70],i;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		int err = scpi_GetErrorQueue(p);
		ExportProcess(String_Data,0,0,(char*)Error[err],0);
		if((err!=0)&&(err!=_ERR_350_Queue_overflow)){
			sprintf(str,"'%s'",disErrQ);
			ExportProcess(String_Data,0,0,str,0);
		}
		for (i=0;i<32;i++)	disErrQ[i]='0';

		SysRedrawFlag |= 0x10;//ERROR_UPDATA;
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}

void idINPutSTATeTRIGered(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,SettingBool;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
//		ExportProcess(Integer_Data,0,Trig.SW,0,0);
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			if(Trig.TrigStatus == _TRIG_ACT_IDLE){
				Trig.LoadOnOff = SettingBool;
			}
		}
	}
// Code End

}

void idOUTPutSTATeTRIGered(STR_PARSER * p)
{
	idINPutSTATeTRIGered(p);
}

void idINITiateIMMediate(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(Trig.TrigStatus != _TRIG_ACT_WTG){
			Trig.Immediate = 1;
			Trig.TrigStatus = _TRIG_ACT_WTG;
		}else{
			scpi_SetCommandError( p, _ERR_213_Init_ignored);	
		}
		Trg_wait_flag =Trig.TrigStatus;
	}
// Code End
}

void idINITiateCONTinuous(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,SettingBool;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		ExportProcess(Integer_Data,0,Trig.Contionous,0,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			Trig.Contionous = SettingBool;
			if(Trig.Contionous)Trig.TrigStatus = _TRIG_ACT_WTG;
			Trg_wait_flag =Trig.TrigStatus;
		}
	}
// Code End

}

void idSOURceCURRentLEVelVATRIGgeredAMPLitude(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	ResolutionTemp=((ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Resolution);
	Precision = (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].precision;
	UBYTE Para_num;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
	Para_num = (UBYTE)Para_s;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			Max=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Max*ResolutionTemp;
			Min=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Min*ResolutionTemp;;
			if((Real_Value > Max)||(Real_Value < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Max : (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Min;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			Trig.ParaNum = Para_num ; 
			Trig.Curr= SettingCount;
			Trig.CurrRange = Data_tmp->IRange;
		}
	}

}

void idRESistanceVATRIGgered(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	ULONG cnt1,value_temp;
	double MHO_value;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UBYTE Para_num;

	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
	Para_num = (UBYTE)Para_s;
	ResolutionTemp=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Resolution;
	//MHO_value=(double)(Data_tmp->CR.STA[Data_tmp->IRange].VALUE1*ResolutionTemp)*Para_s;
//These max and min is MHO as base unit
	Max=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max);
	Min=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min);
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			MHO_value = 1000 / value.d;
			value_temp =(ULONG)(SCPI_InputToStep(MHO_value,ResolutionTemp)/Para_s);
			if((value_temp<=Max) && (value_temp>=Min)) {
				SettingCount=(UWORD)value_temp;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max;
			} else if (value.si==SCPI_MAX) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min;
			}
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			Trig.ParaNum = Para_num ;
			Trig.Cond = SettingCount;
			Trig.CondRange = Data_tmp->IRange;
		}
	}

}


void idSOURceCONDuctanceVATRIGgeredAMPLitude(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	ULONG cnt1,value_temp;
	double MHO_value;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UBYTE Para_num;

	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
	Para_num = (UBYTE)Para_s;
	ResolutionTemp=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Resolution;
	MHO_value=(double)(Data_tmp->CR.STA[Data_tmp->IRange].VALUE1*ResolutionTemp)*Para_s;
//These max and min is MHO as base unit
	Max=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max);
	Min=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min);
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			value_temp =(ULONG)(SCPI_InputToStep(value.d,ResolutionTemp)/Para_s);
			if((value_temp<=Max) && (value_temp>=Min)) {
				SettingCount=(UWORD)value_temp;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min;
			} else if (value.si==SCPI_MAX) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max;
			}
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			Trig.ParaNum = Para_num ;
			Trig.Cond = SettingCount;
			Trig.CondRange = Data_tmp->IRange;
		}
	}
}

void idTRIGgerDELayTIME(STR_PARSER * p){
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Real_Value, ResolutionTemp ;
	char Data_Buffer[40];
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	Precision = 7;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==0) {
				ExportProcess(Float_Data,0,0,0,Precision);
			} else {
				ExportProcess(Float_Data,0.005,0,0,Precision);
			}
		} else {
			//Real_Value = (double)UTILITY.TrigInDelayVal * 0.0000005;
			Real_Value = (double)Data_tmp->CONF.Para_Data.TrigInDelay* 0.0000005;
			ExportProcess(Float_Data,Real_Value,0,0,Precision);			
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			SettingCount =SCPI_InputToStep_s(value.d, 0.0000005);
			if(SettingCount> 10000) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done = 1;

		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? 10000 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CONF.Para_Data.TrigInDelay = SettingCount;
			Disp_tmp->CONF.Para_Data.TrigInDelay = SettingCount;
			if((M_num==P_UTIL_OTHER)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= UTIL_CHANGE + BG_CLEAR;
				ChanRedrawFlag |= BG_CLEAR;
			}
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_TrigInDelay;
			SendTXData(&tx_data);
		}
	}
// Code End
}


void idTRIGgerPULSeWIDTh(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Real_Value, ResolutionTemp ;
	char Data_Buffer[40];
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	Precision = 7;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==0) {
				ExportProcess(Float_Data,0.0000025,0,0,Precision);
			} else {
				ExportProcess(Float_Data,0.005,0,0,Precision);
			}
		} else {
			Real_Value = (double)Data_tmp->CONF.Para_Data.TrigOutWidth* 0.0000005;
			ExportProcess(Float_Data,Real_Value,0,0,Precision); 		
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			SettingCount =SCPI_InputToStep_s(value.d, 0.0000005);
			if((SettingCount> 10000)||(SettingCount< 5)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done = 1;

		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? 10000 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CONF.Para_Data.TrigOutWidth = SettingCount;
			Disp_tmp->CONF.Para_Data.TrigOutWidth = SettingCount;
			if((M_num==P_UTIL_OTHER)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= UTIL_CHANGE + BG_CLEAR;
				ChanRedrawFlag |= BG_CLEAR;
			}
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_TrigOutWidth;
			SendTXData(&tx_data);
		}
	}
// Code End

}


void idINPutSTATeIMMediate(STR_PARSER * p)
{
	UBYTE Command_Done=0,SettingBool;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	p3k_send_tx_list tx_data;
	GW_TYPE value;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		ExportProcess(Integer_Data,0,UTILITY.LOAD_CTL,0,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			UTILITY.LOAD_CTL = SettingBool;
			New_Set_Count_To_FPGA = 0;
			Compensation_Flag = 0;
			Compensation_Count = 0;
			Error_Amount_Flag = 0;
#if Enable_Func_DisTime
			if((UTILITY.LOAD_CTL)||(Normal_Load!=P3k_Chan_Data.Load_Type)){
//				if(FSeq_Load <= P3k_Chan_Data.Load_Type)WriteSEQDataToFPGA_flag =1;
				p3k_Measure_Data.Hour=0;
				p3k_Measure_Data.Min=0;
				p3k_Measure_Data.Sec=0;
			}
#endif
			if(((DGIOCtrlFlag & EXT_Frame_CONT_KB)||(CtrlFlag1&Cal_Wait_moment)||(!FPGA_ISR_Data.ISR_Load))&&(UTILITY.LOAD_CTL==0))
				return;
			if(M_num==P_CAL_MODE)
				return;
			if((Ext_UnReg_Flag) && (Data_tmp->CONF.Ext_Setting.Control <= 3))
				return;

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
					if(!SCPI_Freeze_menu) {
						MenuRedrawFlag |= MENU_CHANGE;
						DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
						ChanRedrawFlag |= BG_CLEAR;
					}
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
					if(!SCPI_Freeze_menu) {
						MenuRedrawFlag |= MENU_CHANGE;
						DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
						ChanRedrawFlag |= BG_CLEAR;
					}
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
						if(!SCPI_Freeze_menu) {
							MenuRedrawFlag |= MENU_CHANGE;
							DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
							ChanRedrawFlag |= BG_CLEAR;
							FunctionFlag   = FUNC_CLEAR;
						}
					} else {
						if(!SCPI_Freeze_menu)
							MenuRedrawFlag |= MENU_CHANGE;
					}
					tx_data.ADDRH = Machine_Command;
					tx_data.ADDRL = Machine_Load_OnOff;
					SendTXData(&tx_data);
				} else {
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
						FunctionFlag  |= FUNC_NSEQ;
					} else {
						UTILITY.LOAD_CTL = Switch_OFF;
						FunctionFlag  = FUNC_CLEAR;
						Prog_Seq_Data.SEQ_Stop_Continue = Display_None;
					}
					M_num = P_NSeq_EXECUTE;
					if(!SCPI_Freeze_menu) {
						MenuRedrawFlag |= MENU_CHANGE;
						DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
						ChanRedrawFlag |= BG_CLEAR;
					}
				}
				DMA_Update_Flag = 1;
			} else if(FSeq_Load==P3k_Chan_Data.Load_Type) {
				HelpRedrawFlag &= ~HELP_FUN_ON;
				Soft_Key_Temp = 0;
				if(UTILITY.LOAD_CTL==Switch_OFF) {
					if(P_FSeq_EXECUTE==M_num) {
						M_num = P_Seq_Fast; /* into sequence Main */
						ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
						if(!SCPI_Freeze_menu) {
							MenuRedrawFlag |= MENU_CHANGE;
							DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
							ChanRedrawFlag |= BG_CLEAR;
						}
						FunctionFlag   = FUNC_CLEAR;
					} else {
						if(!SCPI_Freeze_menu)
							MenuRedrawFlag |= MENU_CHANGE;
					}
					tx_data.ADDRH = Machine_Command;
					tx_data.ADDRL = Machine_Load_OnOff;
					SendTXData(&tx_data);
				} else {
					if(P3k_FSeq_Disp.FSeq_Max_Step<0xFF00) { // 1~1024
						if(0){//if((P3k_Disp_Data.CONF.Para_Data.Booster_Number)&&((P3k_FSeq_Disp.FSeq_Range==0)||(P3k_FSeq_Disp.FSeq_Range==2))) {
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
							FunctionFlag   |= FUNC_FSEQ;
						}
					} else { //0
						UTILITY.LOAD_CTL = Switch_OFF;
						FunctionFlag  = FUNC_CLEAR;
						Prog_Seq_Data.SEQ_Stop_Continue = Display_None;
					}
					M_num = P_FSeq_EXECUTE;
					if(!SCPI_Freeze_menu) {
						MenuRedrawFlag |= MENU_CHANGE;
						DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
						ChanRedrawFlag |= BG_CLEAR;
					}
				}
			} else {
				//M_num = P3k_Disp_Data.CURRMODE;
#if Enable_Short_invalidate
				if ((UTILITY.SHORT_CTL)&&(UTILITY.LOAD_CTL==0)){
					UTILITY.SHORT_CTL = 0;
					UTILITY.LOAD_CTL = 0;
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
			SCPI_RemFastDelay = 1;
		}
	}
// Code End

}

void idOUTPutSTATeIMMediate(STR_PARSER * p)
{
	idINPutSTATeIMMediate(p);
}

void idINPutSHORtSTATe(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,SettingBool;
	p3k_send_tx_list tx_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	static char BackUp_ShortKey_Status;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		ExportProcess(Integer_Data,0,(long)UTILITY.SHORT_CTL,0,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
#if 1 //2015/09/09
			if(UTILITY.SHORT_CTL == SettingBool)return;
#endif
			
#if Enable_Short_invalidate
			if(Disp_tmp->CONF.Short_Fun==0){
				scpi_SetCommandError( p, _ERR_221_Settings_conflict);
				return;
			}
			if((Disp_tmp->CONF.Short_Key)&&(SettingBool)){
				if(M_num==P_CONF_OTHER)		DataRedrawFlag |= PARA_CHANGE;
				Disp_tmp->CONF.Short_Key = 0;
				Data_tmp->CONF.Short_Key = 0;
			}
#endif	
			UTILITY.SHORT_CTL = SettingBool;
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Soft_Start;
			SendTXData(&tx_data);

			tx_data.ADDRH = Para_Ext_Command;
			tx_data.ADDRL = Para_Ext_Setting;
			SendTXData(&tx_data);

			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Load_OnOff;
			SendTXData(&tx_data);
			if(!SCPI_Freeze_menu)
				SysRedrawFlag |= PROG_UPDATA;
			PEL3000_LED_Control(LED_SHORT, UTILITY.SHORT_CTL);
#if Enable_Short_invalidate
			if(UTILITY.LOAD_CTL==0)	PEL3000_LED_Control(LED_LOAD, UTILITY.SHORT_CTL);
#endif			
			SCPI_RemFastDelay = 2;
		}
	}
// Code End

}

void idOUTPupSHORtSTATe(STR_PARSER * p)
{
	idINPutSHORtSTATe(p);
}

void idINPutPROTectionCLEar(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {

	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}

void idOUTPutPROTectionCLEar(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {

	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}

void idINPutSTATeTIMerSTATe(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {

	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}

void idOUTPutSTATeTIMerSTATe(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {

	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}

void idINPutMODE(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,i,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	UBYTE MODE_value;
	ULONG cnt1,value_temp,ResolutionTemp;
	float max,min;
	UBYTE Now_LoadType;
	char str[30];
	p3k_send_tx_list tx_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		MODE_value = P3k_Chan_Data.Load_Type;
		if(MODE_value==0)
			//sprintf(str,"%s","LOAD");
			ExportProcess(String_Data,0,0,"LOAD",0);
		else if(MODE_value==1)
			ExportProcess(String_Data,0,0,"PROG",0);
		//sprintf(str,"%s","PROG");
		else if(MODE_value==2)
			ExportProcess(String_Data,0,0,"NSEQ",0);
		//sprintf(str,"%s","NSEQ");
		else if(MODE_value==3)
			ExportProcess(String_Data,0,0,"FSEQ",0);
		else
			ExportProcess(String_Data,0,0,"exter",0);
		//sprintf(str,"%s","FSEQ");
		//ExportProcess(String_Data,0,0,str,0);
		Command_Done=1;
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			Command_Done = 1;
			switch(value.si) {
			case Normal_Load:
				Now_LoadType = Normal_Load;
				M_num = P3k_Disp_Data.CURRMODE;
				break;
			case Prog_Load:
				Now_LoadType = Prog_Load;
				M_num = P_PROG_MAIN;
				break;
			case NSeq_Load:
				Now_LoadType = NSeq_Load;
				M_num = P_Seq_Normal;
				break;
			case FSeq_Load:
				Now_LoadType = FSeq_Load;
				M_num = P_Seq_Fast;
				break;
			default:
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
		}

		if(Command_Done) {
			if(UTILITY.LOAD_CTL) {
				UTILITY.LOAD_CTL=0x0;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
			}
			P3k_Chan_Data.Load_Type = Now_LoadType;
			P3k_Disp_Data.Load_Type = P3k_Chan_Data.Load_Type;
			if(Now_LoadType)
				ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
			SEQ_Save_Status=0;
			Soft_Key_Temp = 0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				if((M_num==P_CC)||(M_num==P_CR)||(M_num==P_CV)||(M_num==P_CP))
					ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
				SysRedrawFlag	|= PROG_UPDATA;
				ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
				DataRedrawFlag |= DATA_CHANGE ;
				Draw_Set_parameter();

				MenuRedrawFlag |= MENU_CHANGE;

			}
		}
	}
// Code End
}
void idMEASureSCALarCURRentDC(STR_PARSER * p)
{
	GW_TYPE value;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UBYTE Precision;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Precision = (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].precision;
		ExportProcess(Float_Data,p3k_Measure_Data.CURR,0,0,Precision);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End

}

void idMEASureSCALarVOLTageDC(STR_PARSER * p)
{
	GW_TYPE value;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UBYTE Precision;
	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Precision = (ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].precision;
		ExportProcess(Float_Data,p3k_Measure_Data.VOLT,0,0,Precision);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
	// Code End

}

void idMEASureSCALarPOWerDC(STR_PARSER * p)
{
	GW_TYPE value;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UBYTE Precision;
	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Precision = (ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].precision;
		ExportProcess(Float_Data,p3k_Measure_Data.WATT,0,0,Precision);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
	// Code End

}

void idMEASureSCALarETIMe(STR_PARSER * p)
{
	GW_TYPE value;
	char Load_str[30];
	ULONG Load_Time_Min,Load_Time_Sec;
	p3k_send_tx_list tx_data;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		tx_data.ADDRH=0x00;
		tx_data.ADDRL=0x00;
		SendTXData(&tx_data);
		Load_Time_Min = p3k_Measure_Data.Hour * 60;
		Load_Time_Sec = (Load_Time_Min + p3k_Measure_Data.Min) * 60 + p3k_Measure_Data.Sec;
		sprintf(Load_str,"%1.1f",(float)Load_Time_Sec);
		ExportProcess(String_Data,0,0,Load_str,0);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End

}

void idFETChVOLTage(STR_PARSER * p)
{
	GW_TYPE value;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UBYTE Precision;
	p3k_send_tx_list tx_data;
	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		tx_data.ADDRH=Machine_Command;
		tx_data.ADDRL=Machine_Test_Query;
		SendTXData(&tx_data);
		Precision = (ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].precision;
		ExportProcess(Float_Data,p3k_Measure_Data.Real_Volt,0,0,Precision);
		
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
	// Code End

}

void idFETChCURRent(STR_PARSER * p)
{
	GW_TYPE value;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UBYTE Precision;
	p3k_send_tx_list tx_data;
// Code Begin
	if(scpi_IsQueryCommand(p)){
		tx_data.ADDRH=Machine_Command;
		tx_data.ADDRL=Machine_Test_Query;
		SendTXData(&tx_data);
		Precision = (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].precision;
		ExportProcess(Float_Data,p3k_Measure_Data.Real_Curr*3,0,0,Precision);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End

}


void idFETChPOWer(STR_PARSER * p)
{
	GW_TYPE value;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UBYTE Precision;
	p3k_send_tx_list tx_data;
	double Watt;
	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		tx_data.ADDRH=Machine_Command;
		tx_data.ADDRL=Machine_Test_Query;
		SendTXData(&tx_data);
		Precision = (ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].precision;
		Watt = p3k_Measure_Data.Real_Curr*p3k_Measure_Data.Real_Volt*3;
		ExportProcess(Float_Data,Watt,0,0,Precision);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
	// Code End

}

void idCONFigureOCP(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[40];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	ResolutionTemp = ((ptrMODEL_TYPE)->PROT[SCPI_IRange_H].Resolution);
	Precision = (ptrMODEL_TYPE)->PROT[SCPI_IRange_H].precision;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==0) {
				Min=(((double)(ptrMODEL_TYPE)->PROT[SCPI_IRange_H].Min)*ResolutionTemp)*Para_s;
				ExportProcess(Float_Data,Min,0,0,Precision);
			} else {
				Max=(((double)(ptrMODEL_TYPE)->PROT[SCPI_IRange_H].Max)*ResolutionTemp)*Para_s;
				ExportProcess(Float_Data,Max,0,0,Precision);
			}
		} else {
			if (copy_SCPI_Company==SCPI_GW) {
				SettingCount = Data_tmp->PROT.OCP[SCPI_IRange_H];//OCP_Count = Data_tmp->PROT.OCP[Data_tmp->IRange];
				Real_Value=((((double)SettingCount)*ResolutionTemp))*Para_s;
				if(Precision==2) {
					if(Data_tmp->PROT.OCP_SET==1)
						sprintf(Data_Buffer,"LIMIT, %1.2f",Real_Value);
					else if(Data_tmp->PROT.OCP_SET==2)
						sprintf(Data_Buffer,"OFF");
					else
						sprintf(Data_Buffer,"Load off, %1.2f",Real_Value);
				} else {
					if(Data_tmp->PROT.OCP_SET==1)
						sprintf(Data_Buffer,"LIMIT, %1.3f",Real_Value);
					else if(Data_tmp->PROT.OCP_SET==2)
						sprintf(Data_Buffer,"OFF");
					else
						sprintf(Data_Buffer,"Load off, %1.3f",Real_Value);
				}
				ExportProcess(String_Data,0,0,Data_Buffer,0);
			} else if (copy_SCPI_Company==SCPI_KIKUSUI) { //++alantsai_FOR_KIKUSUI
				if(p->pData->id==_idSOURceCURRentPROTectionACTion) {
					SettingCount = Data_tmp->PROT.OCP[SCPI_IRange_H];
					Real_Value=((((double)SettingCount)*ResolutionTemp))*Para_s;
					if(Data_tmp->PROT.OCP_SET==1)
						ExportProcess(String_Data,0,0,"LIMIT",0);
					else if(Data_tmp->PROT.OCP_SET==2)
						ExportProcess(String_Data,0,0,"OFF",0);
					else
						ExportProcess(String_Data,0,0,"TRIP",0);

				} else if(p->pData->id==_idSOURceCURRentPROTectionLEVelOVER) {
					SettingCount = Data_tmp->PROT.OCP[SCPI_IRange_H];
					Real_Value=((((double)SettingCount)*ResolutionTemp))*Para_s;
					if(Precision==2)						
						sprintf(Data_Buffer,"%1.2f",Real_Value);
					else 
						sprintf(Data_Buffer,"%1.3f",Real_Value);										
					ExportProcess(String_Data,0,0,Data_Buffer,0);
				}
			}
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			Max=(((double)(ptrMODEL_TYPE)->PROT[SCPI_IRange_H].Max)*ResolutionTemp);
			Min=(((double)(ptrMODEL_TYPE)->PROT[SCPI_IRange_H].Min)*ResolutionTemp);
			if((Real_Value < Min)||(Real_Value > Max)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount= SCPI_InputToStep(Real_Value , ResolutionTemp);
			Command_Done = 1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(copy_SCPI_Company==SCPI_GW) {
				if(value.si<2) {
					SettingCount = (1 == value.si) ? (ptrMODEL_TYPE)->PROT[SCPI_IRange_H].Max : (ptrMODEL_TYPE)->PROT[SCPI_IRange_H].Min;
					Command_Done = 1;
				} else {
					Data_tmp->PROT.OCP_SET = (2 == value.si) ? 1 : 0;
					if(value.si==4)Data_tmp->PROT.OCP_SET=2;
					Command_Done = 2;
				}
			} else if (copy_SCPI_Company==SCPI_KIKUSUI)	{
				if(p->pData->id==_idSOURceCURRentPROTectionACTion) {
					Data_tmp->PROT.OCP_SET = (1 == value.si) ? 0 : 1;
					if(value.si==4)Data_tmp->PROT.OCP_SET=2;
					Command_Done = 2;
				} else if(p->pData->id==_idSOURceCURRentPROTectionLEVelOVER)
					if(value.si<2) {
						SettingCount = (1 == value.si) ? (ptrMODEL_TYPE)->PROT[SCPI_IRange_H+PROT_OPP_L].Max : (ptrMODEL_TYPE)->PROT[SCPI_IRange_H+PROT_OPP_L].Min;
						Command_Done = 1;
					} else {
						scpi_SetCommandError( p, _ERR_310_System_error);
						return;
					}
			}
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->PROT.OCP[SCPI_IRange_H] = SettingCount;
			Disp_tmp->PROT.OCP[SCPI_IRange_H] = SettingCount;
			if((M_num==P_CONF_PROT)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH=0x00;
			tx_data.ADDRL=0x10;
			SendTXData(&tx_data);
		} else if(Command_Done==2) {
			Disp_tmp->PROT.OCP_SET = Data_tmp->PROT.OCP_SET;
			if((M_num==P_CONF_PROT)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH=0x00;
			tx_data.ADDRL=0x04;
			SendTXData(&tx_data);
		}
	}
// Code End
}


void idCONFigureOPP(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[40];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	ResolutionTemp = (ptrMODEL_TYPE)->PROT[SCPI_IRange_H+PROT_OPP_L].Resolution;
	Precision = (ptrMODEL_TYPE)->PROT[SCPI_IRange_H+PROT_OPP_L].precision;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==0) {
				Min=(((double)(ptrMODEL_TYPE)->PROT[SCPI_IRange_H+PROT_OPP_L].Min) * ResolutionTemp)*Para_s;
				ExportProcess(Float_Data,Min,0,0,Precision);
			} else {
				Max=(((double)(ptrMODEL_TYPE)->PROT[SCPI_IRange_H+PROT_OPP_L].Max)*ResolutionTemp)*Para_s;
				ExportProcess(Float_Data,Max,0,0,Precision);
			}
		} else {
			if(copy_SCPI_Company==SCPI_GW) {
				SettingCount = Data_tmp->PROT.OPP[SCPI_IRange_H];
				Real_Value = (((double)SettingCount) * ResolutionTemp)*Para_s;

				if(Data_tmp->PROT.OPP_SET==2){
					sprintf(Data_Buffer,"OFF");	
				}else if(Precision==2) {
					if(Data_tmp->PROT.OPP_SET)
						sprintf(Data_Buffer,"LIMIT, %1.2f",Real_Value);
					else
						sprintf(Data_Buffer,"Load off, %1.2f",Real_Value);
				} else if(Precision==3) {
					if(Data_tmp->PROT.OPP_SET)
						sprintf(Data_Buffer,"LIMIT, %1.3f",Real_Value);
					else
						sprintf(Data_Buffer,"Load off, %1.3f",Real_Value);
				} else {
					if(Data_tmp->PROT.OPP_SET)
						sprintf(Data_Buffer,"LIMIT, %1.4f",Real_Value);
					else
						sprintf(Data_Buffer,"Load off, %1.4f",Real_Value);
				}
				ExportProcess(String_Data,0,0,Data_Buffer,0);
			} else if (copy_SCPI_Company==SCPI_KIKUSUI) { //++alantsai
				if(p->pData->id==_idSOURcePOWerPROTectionACTion) {
					SettingCount = Data_tmp->PROT.OPP[SCPI_IRange_H];
					Real_Value = (((double)SettingCount) * ResolutionTemp)*Para_s;
					if(Data_tmp->PROT.OPP_SET==1)
						ExportProcess(String_Data,0,0,"LIMIT",0);
					else if(Data_tmp->PROT.OPP_SET==2)
						ExportProcess(String_Data,0,0,"OFF",0);
					else
						ExportProcess(String_Data,0,0,"TRIP",0);
				} else if(p->pData->id==_idSOURcePOWerPROTectionLEVelOVER) {
					SettingCount = Data_tmp->PROT.OPP[SCPI_IRange_H];
					Real_Value = (((double)SettingCount) * ResolutionTemp)*Para_s;
					if(Data_tmp->PROT.OPP_SET==2){
						sprintf(Data_Buffer,"OFF");	
					}else if(Precision==2) {
						if(Data_tmp->PROT.OPP_SET)
							sprintf(Data_Buffer,"%1.2f",Real_Value);
						else
							sprintf(Data_Buffer,"%1.2f",Real_Value);
					} else if(Precision==3) {
						if(Data_tmp->PROT.OPP_SET)
							sprintf(Data_Buffer,"%1.3f",Real_Value);
						else
							sprintf(Data_Buffer,"%1.3f",Real_Value);
					} else {
						if(Data_tmp->PROT.OPP_SET)
							sprintf(Data_Buffer,"%1.4f",Real_Value);
						else
							sprintf(Data_Buffer,"%1.4f",Real_Value);
					}

					ExportProcess(String_Data,0,0,Data_Buffer,0);
				}
			}

		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			Max=(((double)(ptrMODEL_TYPE)->PROT[SCPI_IRange_H+PROT_OPP_L].Max)*ResolutionTemp);
			Min=(((double)(ptrMODEL_TYPE)->PROT[SCPI_IRange_H+PROT_OPP_L].Min)*ResolutionTemp);
			if((Real_Value > Max)||(Real_Value < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value,ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(copy_SCPI_Company==SCPI_GW) {
				if(value.si<2) {
					SettingCount = (1 == value.si) ? (ptrMODEL_TYPE)->PROT[SCPI_IRange_H+PROT_OPP_L].Max : (ptrMODEL_TYPE)->PROT[SCPI_IRange_H+PROT_OPP_L].Min;
					Command_Done = 1;
				} else {
					Data_tmp->PROT.OPP_SET = (2 == value.si) ? 1 : 0;
					if(value.si==4)	Data_tmp->PROT.OPP_SET = 2;
					Command_Done = 2;
				}
			} else if (copy_SCPI_Company==SCPI_KIKUSUI) {
				if(p->pData->id==_idSOURcePOWerPROTectionACTion) {
					Data_tmp->PROT.OPP_SET = (1 == value.si) ? 0 : 1;
					if(value.si==4)	Data_tmp->PROT.OPP_SET = 2;
					Command_Done = 2;
				} else if(p->pData->id==_idSOURcePOWerPROTectionLEVelOVER) {
					if(value.si<2) {
						SettingCount = (1 == value.si) ? (ptrMODEL_TYPE)->PROT[SCPI_IRange_H+PROT_OPP_L].Max : (ptrMODEL_TYPE)->PROT[SCPI_IRange_H+PROT_OPP_L].Min;
						Command_Done = 1;
					} else {
						scpi_SetCommandError( p, _ERR_310_System_error);
						return;
					}
				}
			}
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->PROT.OPP[SCPI_IRange_H]=SettingCount;
			Disp_tmp->PROT.OPP[SCPI_IRange_H]=SettingCount;
			if((M_num==P_CONF_PROT)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH = 0x00;
			tx_data.ADDRL = 0x12;
			SendTXData(&tx_data);
		} else if(Command_Done==2) {
			Disp_tmp->PROT.OPP_SET = Data_tmp->PROT.OPP_SET;
			if((M_num==P_CONF_PROT)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH = 0x00;
			tx_data.ADDRL = 0x04;
			SendTXData(&tx_data);
		}
	}
	// Code End

}



void idCONFigureUVP(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[40];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	ResolutionTemp=((ptrMODEL_TYPE)->PROT[Data_tmp->VRange+PROT_UVP_L].Resolution);
	Precision = ((ptrMODEL_TYPE)->PROT[Data_tmp->VRange+PROT_UVP_L].precision);
	//Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==0) {
				Min=((double)(ptrMODEL_TYPE)->PROT[Data_tmp->VRange+PROT_UVP_L].Min)*ResolutionTemp;
				ExportProcess(Float_Data,Min,0,0,Precision);
			} else {
				Max=((double)(ptrMODEL_TYPE)->PROT[Data_tmp->VRange+PROT_UVP_L].Max)*ResolutionTemp;
				ExportProcess(Float_Data,Max,0,0,Precision);
			}
		} else {
			//alantsai++ for KIKUSUI
			if (copy_SCPI_Company==SCPI_GW) {
				SettingCount = Data_tmp->PROT.UVP_VOLT[Data_tmp->VRange];
				Real_Value = (double)SettingCount*ResolutionTemp;
				ExportProcess(Float_Data,Real_Value,0,0,Precision);
			} else if (copy_SCPI_Company==SCPI_KIKUSUI) {
				if(p->pData->id==_idSOURceVOLTagePROTectionSTATe) {
					if(Data_tmp->PROT.UVP_VOLT[Data_tmp->VRange] == 0)
						ExportProcess(String_Data,0,0,"OFF",0);
					else
						ExportProcess(String_Data,0,0,"ON",0);
				}
			}
		}
	} else {
		if(0) { //(Command_Temp.ID == _idVoltProtStat) {
			///StoreErrItemNumToErrEventQTemp(ERR_109_MissingParameter,Command_Temp.Record_Comm);
			return;
		}
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Max=((double)(ptrMODEL_TYPE)->PROT[Data_tmp->VRange+PROT_UVP_L].Max)*ResolutionTemp;
			Min=((double)(ptrMODEL_TYPE)->PROT[Data_tmp->VRange+PROT_UVP_L].Min)*ResolutionTemp;
			if((value.d > Max)||(value.d < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(value.d , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si))
			if (copy_SCPI_Company==SCPI_GW) {
				if(value.si<2) {
					SettingCount = (1 == value.si) ? (ptrMODEL_TYPE)->PROT[Data_tmp->VRange+PROT_UVP_L].Max : (ptrMODEL_TYPE)->PROT[Data_tmp->VRange+4].Min;
					Command_Done = 1;
				} else {
					scpi_SetCommandError( p, _ERR_310_System_error);
					return;
				}
			} else if (copy_SCPI_Company==SCPI_KIKUSUI) {
				if(p->pData->id==_idSOURceVOLTagePROTectionSTATe) {

					if(value.si==0) {
						SettingCount =(ptrMODEL_TYPE)->PROT[Data_tmp->VRange+PROT_UVP_L].Min;
						Command_Done = 1;
					} else if(value.si==1) {
						SettingCount =(ptrMODEL_TYPE)->PROT[Data_tmp->VRange+PROT_UVP_L].Max;
						Command_Done = 1;
					} else {
						scpi_SetCommandError( p, _ERR_310_System_error);
						return;
					}
				}

			}



		if(Command_Done) {
			Data_tmp->PROT.UVP_VOLT[Data_tmp->VRange] = SettingCount;
			Disp_tmp->PROT.UVP_VOLT[Data_tmp->VRange] = SettingCount;
			if((M_num==P_CONF_PROT)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH=0x00;
			tx_data.ADDRL=0x14;
			SendTXData(&tx_data);

		}
	}
	// Code End
}

void idCONFigureUVPTIME(STR_PARSER * p)
{
#if Enable_Ring_Count
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	UWORD Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[40];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	ResolutionTemp=1;;
	Precision = 0;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==0) {
				Min=0;
				ExportProcess(Integer_Data,0,Min,0,Precision);
			} else {
				Max=600;
				ExportProcess(Integer_Data,0,Max,0,Precision);
			}
		} else {			
			SettingCount = Data_tmp->PROT.UVP_Tone_len-1;
			Real_Value = (double)SettingCount*ResolutionTemp;
			if(Real_Value==601)
				ExportProcess(String_Data, 0, 0,"Infinity", 0);
			else if(Real_Value==0)
				ExportProcess(String_Data, 0, 0,"OFF", 0);	
			else
				ExportProcess(Integer_Data, 0, Real_Value, 0, Precision);			
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Max=600;
			Min=0;
			if((value.d > Max)||(value.d < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(value.d , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si))	
			if(value.si<2) {
				SettingCount = (1 == value.si) ? 600 : 0;
				Command_Done = 1;
			} else if(value.si==2){
				SettingCount = 601;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}	
		if(Command_Done) {
			Data_tmp->PROT.UVP_Tone_len = SettingCount+1;
			Disp_tmp->PROT.UVP_Tone_len = SettingCount+1;
			if((M_num==P_CONF_PROT)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
		}
	}
	// Code End
#endif	
}

void idCONFigureOVP(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[40];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	ResolutionTemp=((ptrMODEL_TYPE)->PROT[Data_tmp->VRange+PROT_OVP_L].Resolution);
	Precision = ((ptrMODEL_TYPE)->PROT[Data_tmp->VRange+PROT_OVP_L].precision);
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==0) {
				Min=((double)(ptrMODEL_TYPE)->PROT[Data_tmp->VRange+PROT_OVP_L].Min)*ResolutionTemp;
				ExportProcess(Float_Data,Min,0,0,Precision);
			} else {
				Max=((double)(ptrMODEL_TYPE)->PROT[Data_tmp->VRange+PROT_OVP_L].Max)*ResolutionTemp;
				ExportProcess(Float_Data,Max,0,0,Precision);
			}
		} else {
			SettingCount = Data_tmp->PROT.OVP_VOLT[Data_tmp->VRange];
			Real_Value = ((double)SettingCount)*ResolutionTemp;
			if(SettingCount == ptrMODEL_TYPE->PROT[Data_tmp->VRange+PROT_OVP_L].Max)
				ExportProcess(String_Data,0,0,"OFF",0);
			else
				ExportProcess(Float_Data,Real_Value,0,0,Precision);

		}

	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Max=((double)(ptrMODEL_TYPE)->PROT[Data_tmp->VRange+PROT_OVP_L].Max)*ResolutionTemp;
			Min=((double)(ptrMODEL_TYPE)->PROT[Data_tmp->VRange+PROT_OVP_L].Min)*ResolutionTemp;
			if((value.d > Max)||(value.d < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(value.d , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si<2) {
				SettingCount = (1 == value.si) ? (ptrMODEL_TYPE)->PROT[Data_tmp->VRange+6].Max : (ptrMODEL_TYPE)->PROT[Data_tmp->VRange+6].Min;
				Command_Done = 1;
			}
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			Data_tmp->PROT.OVP_VOLT[Data_tmp->VRange] = SettingCount;
			Disp_tmp->PROT.OVP_VOLT[Data_tmp->VRange] = SettingCount;
			if((M_num==P_CONF_PROT)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH=0x00;
			tx_data.ADDRL=0x14;
			SendTXData(&tx_data);
		}
	}
// Code End
}

void idCONFigureSSTart(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[40];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==0) {
				ExportProcess(Float_Data,0,0,0,3);
			} else {
				ExportProcess(Float_Data,0.2,0,0,3);
			}
		} else {
			if (Data_tmp->CONF.SOFT_START==0)
				ExportProcess(String_Data,0,0,"OFF",0);
			else {
				Real_Value = (double)Data_tmp->CONF.SOFT_START * 0.001;
				ExportProcess(Float_Data,Real_Value,0,0,3);
			}
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			SettingCount =SCPI_InputToStep(value.d, 0.001);
			if(SettingCount> 200) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done = 1;

		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? 200 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CONF.SOFT_START = SettingCount;
			Disp_tmp->CONF.SOFT_START = SettingCount;
			if((M_num==P_CONF_OTHER)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH = 0x00;
			tx_data.ADDRL = Machine_Soft_Start;
			SendTXData(&tx_data);
		}
	}
// Code End
}

void idCONFigureVON(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, VRange,Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[40];

	double Voltage_temp;
	short Voltage_rawdata;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	VRange = Data_tmp->VRange;
	ResolutionTemp = ptrMODEL_TYPE->CONF[Data_tmp->VRange].Resolution;
	Precision = ptrMODEL_TYPE->CONF[Data_tmp->VRange].precision;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		SettingCount = Data_tmp->CONF.VON_VOLT[VRange];
		Real_Value =(double)SettingCount*ResolutionTemp;
		if(Data_tmp->CONF.VON_LATCH) {
			SCPI_Printf(Data_Buffer,"Latch:ON, ",Real_Value,Precision);
		} else {
			SCPI_Printf(Data_Buffer,"Latch:OFF, ",Real_Value,Precision);
		}
		ExportProcess(String_Data,0,0,Data_Buffer,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Max=(double)(ptrMODEL_TYPE->CONF[VRange].Max)*ResolutionTemp;
			Min=(double)(ptrMODEL_TYPE->CONF[VRange].Min)*ResolutionTemp;
			if((value.d > Max)||(value.d < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(value.d , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si<2) {
				SettingCount = (1 == value.si) ? ptrMODEL_TYPE->CONF[VRange].Max : ptrMODEL_TYPE->CONF[VRange].Min;
				Command_Done = 1;
			} else {
				Data_tmp->CONF.VON_LATCH = (2 == value.si) ? 1 : 0;
				Command_Done = 2;
			}
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CONF.VON_VOLT[VRange]=SettingCount;
			Voltage_temp = SettingCount * (ptrMODEL_TYPE->CONF[VRange].Resolution);
			VRange++;
			VRange &= 0x01;
			Voltage_rawdata = Voltage_temp / ptrMODEL_TYPE->CONF[VRange].Resolution;

			if(Voltage_rawdata>ptrMODEL_TYPE->CONF[VRange].Max)
				Voltage_rawdata = ptrMODEL_TYPE->CONF[VRange].Max;
			else if(Voltage_rawdata<ptrMODEL_TYPE->CONF[VRange].Min)
				Voltage_rawdata = ptrMODEL_TYPE->CONF[VRange].Min;

			Data_tmp->CONF.VON_VOLT[VRange] = Voltage_rawdata;

			Disp_tmp->CONF.VON_VOLT[0] = Data_tmp->CONF.VON_VOLT[0];
			Disp_tmp->CONF.VON_VOLT[1] = Data_tmp->CONF.VON_VOLT[1];

			if((M_num==P_CONF_OTHER)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH = 0x00;
			tx_data.ADDRL = 0x20;
			SendTXData(&tx_data);

		} else if(Command_Done==2) {
			Disp_tmp->CONF.VON_LATCH = Data_tmp->CONF.VON_LATCH;
			if((M_num==P_CONF_OTHER)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH=0x00;
			tx_data.ADDRL=0x04;
			SendTXData(&tx_data);
		}
	}
// Code End
}

void idCONFigureVDELay(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision=4;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp=0.001, Para_s;
	char Data_Buffer[40];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	UBYTE CR = 0;
	if(Data_tmp->CURRMODE == SCPI_CR)CR=1;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==0) {
				Min=0.002;
				ExportProcess(Float_Data,Min,0,0,Precision);
			} else {
				Max=0.06;
				ExportProcess(Float_Data,Max,0,0,Precision);
			}
		} else {
			if (Disp_tmp->CONF.D_Von_Delay<=1900)
				ExportProcess(String_Data,0,0,"OFF",0);
			else {
				Real_Value = ((double)Float_Data,Disp_tmp->CONF.D_Von_Delay)*0.000001;
				ExportProcess(Float_Data,Real_Value,0,0,Precision);
			}
		}
	} else {

		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Max = 60;
			Min = 2;
			Real_Value = value.d * 1000;
			if((Real_Value > Max)||(Real_Value < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN)
				SettingCount = 2000;
			else if(value.si==SCPI_MAX)
				SettingCount = 60000;
			else
				SettingCount = 1850;

			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CONF.D_Von_Delay = SettingCount;
			Disp_tmp->CONF.D_Von_Delay = SettingCount;
			if (SettingCount<5000)SettingCount = 5000;
			//Data_tmp->CONF.D_Von_Delay_CR = SettingCount;
			//Disp_tmp->CONF.D_Von_Delay_CR = SettingCount;
			if((M_num==P_CONF_OTHER)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				Draw_Set_parameter();			
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH = 0x00;
			tx_data.ADDRL = 0x04;
			SendTXData(&tx_data);
		}
	}
// Code End
}
#if 1
void idCONFigureRESPonse(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[40];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;



// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(Data_tmp->CONF.Response == 0)
			ExportProcess(Float_Data,1.0,0,0,1);
		else if(Data_tmp->CONF.Response == 1)
			ExportProcess(Float_Data,0.5,0,0,1);
		else if(Data_tmp->CONF.Response == 2)
			ExportProcess(Float_Data,0.2,0,0,1);
		else if(Data_tmp->CONF.Response == 3)
			ExportProcess(Float_Data,0.1,0,0,1);
		else
			ExportProcess(Float_Data,1.0,0,0,1);

	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d * 10;
			if(Real_Value == 1)
				Data_tmp->CONF.Response = 3;
			else if(Real_Value == 2)
				Data_tmp->CONF.Response = 2;
			else if(Real_Value == 5)
				Data_tmp->CONF.Response = 1;
			else if(Real_Value == 10)
				Data_tmp->CONF.Response = 0;
			else {
				scpi_SetCommandError( p, _ERR_108_Parameter_not_allowed);
				return;
			}
			Command_Done = 1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			Data_tmp->CONF.Response = (1 == value.si) ? 0 : 3;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Disp_tmp->CONF.Response = Data_tmp->CONF.Response;
			if((M_num==P_CONF_OTHER)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH = 0x00;
			tx_data.ADDRL = 0x04;
			SendTXData(&tx_data);
		}
	}
// Code End
}
#endif
void idCONFigureCNTime(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision,SettingBool;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if (Disp_tmp->CONF.Count_Time==SCPI_Config_Other_OFF)
			ExportProcess(String_Data,0,0,"OFF",0);
		else if (Disp_tmp->CONF.Count_Time==SCPI_Config_Other_ON)
			ExportProcess(String_Data,0,0,"ON",0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((TEXIO_Version==P3k_Serial_Number.Version)||(value.si>=2)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CONF.Count_Time = SettingBool;
			Disp_tmp->CONF.Count_Time = SettingBool;
			if((M_num==P_CONF_OTHER)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH = 0x00;
			tx_data.ADDRL = 0x06;
			SendTXData(&tx_data);
		}
	}
	// Code End
}

void idCONFigureCOTime(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[40];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==0) {
				ExportProcess(Integer_Data,0,0,0,0);
			} else {
				ExportProcess(Integer_Data,0,(unsigned long)3599999,0,0);
			}
		} else {
			if (Disp_tmp->CONF.cut_off_time_total>0) {
				ExportProcess(Integer_Data,0,Disp_tmp->CONF.cut_off_time_total,0,0);
			} else
				ExportProcess(String_Data,0,0,"OFF",0);
		}
	} else {

		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			if ((value.d>=0)&&(value.d<=(unsigned long)3599999)) {
				Disp_tmp->CONF.cut_off_time_total=value.d;
				Disp_tmp->CONF.Cut_Off_Time_s= (Disp_tmp->CONF.cut_off_time_total) %60;
				Disp_tmp->CONF.Cut_Off_Time_m= (Disp_tmp->CONF.cut_off_time_total/60) %60;
				Disp_tmp->CONF.Cut_Off_Time_h= (Disp_tmp->CONF.cut_off_time_total/3600);
			} else {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si != 1) {
				Disp_tmp->CONF.cut_off_time_total=0;
				Disp_tmp->CONF.Cut_Off_Time_s = 0;
				Disp_tmp->CONF.Cut_Off_Time_m = 0;
				Disp_tmp->CONF.Cut_Off_Time_h= 0;
			} else {
				Disp_tmp->CONF.cut_off_time_total=(unsigned long)3599999;
				Disp_tmp->CONF.Cut_Off_Time_s= (unsigned long)3599999 %60;
				Disp_tmp->CONF.Cut_Off_Time_m= ((unsigned long)3599999/60) %60;
				Disp_tmp->CONF.Cut_Off_Time_h= ((unsigned long)3599999/3600);
			}
			Command_Done = 1;

		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CONF.Cut_Off_Time_s = Disp_tmp->CONF.Cut_Off_Time_s;
			Data_tmp->CONF.Cut_Off_Time_m = Disp_tmp->CONF.Cut_Off_Time_m;
			Data_tmp->CONF.Cut_Off_Time_h = Disp_tmp->CONF.Cut_Off_Time_h;
			Data_tmp->CONF.cut_off_time_total= Disp_tmp->CONF.cut_off_time_total;
			if((M_num==P_CONF_OTHER)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH = 0x00;
			tx_data.ADDRL = 0x07;
			SendTXData(&tx_data);
		}
	}
// Code End

}

void idCONFigureCRUNit(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, SettingBool;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(!Disp_tmp->CONF.D_CR_Unit)
			ExportProcess(String_Data,0,0,"OHM",0);
		else
			ExportProcess(String_Data,0,0,"MHO",0);
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CONF.D_CR_Unit = SettingBool;
			Disp_tmp->CONF.D_CR_Unit = SettingBool;
			if((M_num==P_CONF_OTHER)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH = 0x00;
			tx_data.ADDRL = 0x08;
			SendTXData(&tx_data);
		}
	}
	// Code End

}

void idCONFigureDYNamic(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, SettingBool;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(!Disp_tmp->CONF.Dyna_Level) {
			if(!Disp_tmp->CONF.Dyna_Time)
				ExportProcess(String_Data,0,0,"Value,T1/T2",0);
			else
				ExportProcess(String_Data,0,0,"Value,Fre./Duty",0);
		} else {
			if(!Disp_tmp->CONF.Dyna_Time)
				ExportProcess(String_Data,0,0,"Percent,T1/T2",0);
			else
				ExportProcess(String_Data,0,0,"Percent,Fre./Duty",0);
		}
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si<2) {
				Data_tmp->CONF.Dyna_Level = (1 == value.si) ? 1 : 0;
				Command_Done = 1;
			} else {
				Data_tmp->CONF.Dyna_Time = (3 == value.si) ? 1 : 0;
				Command_Done = 2;
			}
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			Disp_tmp->CONF.Dyna_Level = Data_tmp->CONF.Dyna_Level;
			Disp_tmp->CONF.Dyna_Time = Data_tmp->CONF.Dyna_Time;
			if(((M_num==P_CONF_OTHER)||(M_num<=P_CP))&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH = 0x00;
			tx_data.ADDRL = 0x20;
			SendTXData(&tx_data);
		}
	}
	// Code End

}

void idCONFigureMEMory(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, SettingBool;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if (Disp_tmp->CONF.Memory_Recall==SCPI_Config_Other_Mem_Safety)
			ExportProcess(String_Data,0,0,"Safety",0);
		else if (Disp_tmp->CONF.Memory_Recall==SCPI_Config_Other_Mem_Direct)
			ExportProcess(String_Data,0,0,"Direct",0);
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CONF.Memory_Recall = SettingBool;
			Disp_tmp->CONF.Memory_Recall = SettingBool;
			if((M_num==P_CONF_OTHER)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH = 0x00;
			tx_data.ADDRL = 0x0B;
			SendTXData(&tx_data);
		}
	}
	// Code End

}

void idCONFigureSHORt(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, SettingBool;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if (Disp_tmp->CONF.Short_Key==0)
			ExportProcess(String_Data,0,0,"Toggle",0);
		else if (Disp_tmp->CONF.Short_Key==1)
			ExportProcess(String_Data,0,0,"Hold",0);

	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CONF.Short_Key = SettingBool;
			Disp_tmp->CONF.Short_Key = SettingBool;
			if((M_num==P_CONF_OTHER)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH = 0x00;
			tx_data.ADDRL = 0x0C;
			SendTXData(&tx_data);
		}
	}
	// Code End

}

void idCONFigureSHORtFUNCtion(STR_PARSER * p)
{
#if Enable_Short_invalidate
	GW_TYPE value;
	UBYTE Command_Done=0, SettingBool;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if (Disp_tmp->CONF.Short_Fun==0)
			ExportProcess(String_Data,0,0,"OFF",0);
		else 
			ExportProcess(String_Data,0,0,"ON",0);

	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		}else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CONF.Short_Fun= SettingBool;
			Disp_tmp->CONF.Short_Fun= SettingBool;
			if((M_num==P_CONF_OTHER)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			if((SettingBool==0)&&(UTILITY.SHORT_CTL)){
				UTILITY.SHORT_CTL = 0;	
				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = Machine_Soft_Start;
				SendTXData(&tx_data);

				tx_data.ADDRH = Para_Ext_Command;
				tx_data.ADDRL = Para_Ext_Setting;
				SendTXData(&tx_data);

				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = Machine_Load_OnOff;
				SendTXData(&tx_data);
				if(!SCPI_Freeze_menu)
					SysRedrawFlag |= PROG_UPDATA;
				PEL3000_LED_Control(LED_SHORT, UTILITY.SHORT_CTL);
				if(UTILITY.LOAD_CTL==0)	PEL3000_LED_Control(LED_LOAD, UTILITY.SHORT_CTL);
				SCPI_RemFastDelay = 2;
			}
		}
	}
	// Code End
#endif	
}

void idCONFigureSHORtSAFety(STR_PARSER * p)
{
#if Enable_Short_invalidate
	GW_TYPE value;
	UBYTE Command_Done=0, SettingBool;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if (Disp_tmp->CONF.Short_Satety==0)
			ExportProcess(String_Data,0,0,"OFF",0);
		else 
			ExportProcess(String_Data,0,0,"ON",0); 

	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		}else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CONF.Short_Satety = SettingBool;
			Disp_tmp->CONF.Short_Satety = SettingBool;
			if((M_num==P_CONF_OTHER)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;
				if(DispMode!=DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}			
		}
	}
	// Code End
#endif	
}

void idCONFigureGNGSPECtest(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, SettingBool;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if (Disp_tmp->SPEC==0)
			ExportProcess(String_Data,0,0,"OFF",0);
		else if (Disp_tmp->SPEC==1)
			ExportProcess(String_Data,0,0,"ON",0);

	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((TEXIO_Version==P3k_Serial_Number.Version)||(value.si>=2)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->SPEC = SettingBool;
			Disp_tmp->SPEC = SettingBool;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				if(M_num>=P_CC_SPEC && M_num<=P_CV_SPEC || M_num==P_CP_SPEC) {
					if(DispMode > DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
					DataRedrawFlag |= PARA_CHANGE;
					Draw_Set_parameter();					
				}
				if(M_num>=P_CC && M_num<=P_CONF_OTHER || M_num==P_FILE_CHAN || M_num==P_CP_SPEC)
					ChanRedrawFlag |= CHAN_STATUS;
			}
			tx_data.ADDRH = 0x00;
			tx_data.ADDRL = 0x03;
			SendTXData(&tx_data);
		}
	}
	// Code End

}

void idCONFigureGNGDTIMe(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UWORD SettingCount;
	double Max, Min;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==0) {
				ExportProcess(Float_Data,(float)0,0,0,1);
			} else {
				ExportProcess(Float_Data,(float)1,0,0,1);
			}
		} else {
			ExportProcess(Float_Data,Data_tmp->P_F_Delay/10.0,0,0,1);
		}
	} else {

		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Max=1.0;
			Min=0;
			if((value.d > Max)||(value.d < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(value.d , 0.1);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? 10 : 0;
			Command_Done = 1;

		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Disp_tmp->P_F_Delay = SettingCount;
			Data_tmp->P_F_Delay = SettingCount;
			if((M_num>=P_CC_SPEC && M_num<=P_CP_SPEC)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				Draw_Set_parameter();
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
		}
	}
// Code End
}

void idCONFigureGNGMODE(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, SettingBool;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(Data_tmp->SPECTYPE)
			ExportProcess(String_Data,0,0,"Percent",0);
		else
			ExportProcess(String_Data,0,0,"Value",0);

	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->SPECTYPE = SettingBool;
			Disp_tmp->SPECTYPE = SettingBool;
			if((M_num>=P_CC_SPEC && M_num<=P_CP_SPEC)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DispCT =0;
				DispScrCurrLoc =0;
				DispScrEndCT=4;
				DispScrStartCT=0;
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				Draw_Set_parameter();
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

		}
	}
	// Code End
}

void idCONFigureGNGPASS(STR_PARSER * p)
{
	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		tx_data.ADDRH=0x00;
		tx_data.ADDRL=0x00;
		SendTXData(&tx_data);

		if(Data_tmp->SPEC) {
			if(p3k_Measure_Data.Go_NoGo == 2)
				ExportProcess(String_Data,0,0,"GO",0);
			else
				ExportProcess(String_Data,0,0,"NG",0);
		} else
			ExportProcess(String_Data,0,0,"GO",0);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}

void idCONFigureGNGH(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,i;
	UWORD umax,umin;
	UWORD *Value_Center,*Value_Low,*Percent_Low,*Value_High,*Percent_High;
	UWORD *Value_Center_Disp,*Value_Low_Disp,*Percent_Low_Disp,*Value_High_Disp,*Percent_High_Disp;
	UWORD *CENTERVAL;
	char Data_Buffer[20];
	UBYTE Precision;
	double HIGHVAL_TEMP,HIPCET_TEMP,resolution;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	switch(Data_tmp->CURRMODE) {
	case SCPI_CC:
		switch(Data_tmp->CC.STADYNA) {
		case SCPI_Dynamic_Status:
			Percent_High	= &Data_tmp->CC.DYNA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CC.DYNA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CC.DYNA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CC.DYNA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CC.DYNA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CC.DYNA[Disp_tmp->IRange].CENTERVAL;
			break;
		case SCPI_Static_Status:
			Percent_High	= &Data_tmp->CC.STA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CC.STA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CC.STA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CC.STA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CC.STA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CC.STA[Disp_tmp->IRange].CENTERVAL;
			break;
		default:
			break;
		}
		resolution	= ptrMODEL_TYPE->CC_SPEC[SCPI_Config_GoNoGo_High].Resolution;
		Precision = (ptrMODEL_TYPE->CC_SPEC)[0].precision;
		umax		= ptrMODEL_TYPE->CC_SPEC[SCPI_Config_GoNoGo_High].Max;
		umin		= ptrMODEL_TYPE->CC_SPEC[SCPI_Config_GoNoGo_High].Min;
		break;
	case SCPI_CR:
		switch(Data_tmp->CR.STADYNA) {
		case SCPI_Dynamic_Status:
			Percent_High	= &Data_tmp->CR.DYNA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CR.DYNA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CR.DYNA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CR.DYNA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CR.DYNA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CR.DYNA[Disp_tmp->IRange].CENTERVAL;
			break;
		case SCPI_Static_Status:
			Percent_High	= &Data_tmp->CR.STA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CR.STA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CR.STA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CR.STA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CR.STA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CR.STA[Disp_tmp->IRange].CENTERVAL;
			break;
		default:
			break;
		}
		resolution	= ptrMODEL_TYPE->CR_SPEC[SCPI_Config_GoNoGo_High].Resolution;
		Precision = (ptrMODEL_TYPE->CR_SPEC)[0].precision;
		umax		= ptrMODEL_TYPE->CR_SPEC[SCPI_Config_GoNoGo_High].Max;
		umin		= ptrMODEL_TYPE->CR_SPEC[SCPI_Config_GoNoGo_High].Min;
		break;
	case SCPI_CV:
		Percent_High	= &Data_tmp->CV.STA[Data_tmp->VRange].HIPCET;
		Percent_Low 	= &Data_tmp->CV.STA[Data_tmp->VRange].LOWPCET;
		Value_High		= &Data_tmp->CV.STA[Data_tmp->VRange].HIGHVAL;
		Value_Center	= &Data_tmp->CV.STA[Data_tmp->VRange].CENTERVAL;
		Value_Low		= &Data_tmp->CV.STA[Data_tmp->VRange].LOWVAL;
		CENTERVAL		= &Disp_tmp->CV.STA[Disp_tmp->VRange].CENTERVAL;

		resolution	= ptrMODEL_TYPE->CV_SPEC[SCPI_Config_GoNoGo_High].Resolution;
		Precision = (ptrMODEL_TYPE->CV_SPEC)[0].precision;
		umax		= ptrMODEL_TYPE->CV_SPEC[SCPI_Config_GoNoGo_High].Max;
		umin		= ptrMODEL_TYPE->CV_SPEC[SCPI_Config_GoNoGo_High].Min;
		break;
	case SCPI_CP:
		switch(Data_tmp->CP.STADYNA) {
		case SCPI_Dynamic_Status:
			Percent_High	= &Data_tmp->CP.DYNA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CP.DYNA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CP.DYNA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CP.DYNA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CP.DYNA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CP.DYNA[Disp_tmp->IRange].CENTERVAL;
			break;
		case SCPI_Static_Status:
			Percent_High	= &Data_tmp->CP.STA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CP.STA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CP.STA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CP.STA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CP.STA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CP.STA[Disp_tmp->IRange].CENTERVAL;
			break;
		default:
			break;
		}
		resolution	= ptrMODEL_TYPE->CP_SPEC[SCPI_Config_GoNoGo_High].Resolution;
		Precision = (ptrMODEL_TYPE->CP_SPEC)[0].precision;
		umax		= ptrMODEL_TYPE->CP_SPEC[SCPI_Config_GoNoGo_High].Max;
		umin		= ptrMODEL_TYPE->CP_SPEC[SCPI_Config_GoNoGo_High].Min;
		break;
	default:
		return;
	}

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(Disp_tmp->SPECTYPE==SCPI_Config_GoNoGo_Percent) {
			sprintf(Data_Buffer,"%3.1f",(float)(*Percent_High)*0.1);
			ExportProcess(String_Data,0,0,Data_Buffer,0);
		} else if(Disp_tmp->SPECTYPE==SCPI_Config_GoNoGo_Value) {
			ExportProcess(Float_Data,(float)(*Value_High*resolution),0,0,Precision);
		}
	} else {

		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Command_Done=1;
			switch(Disp_tmp->SPECTYPE) {
			case SCPI_Config_GoNoGo_Percent:
				HIPCET_TEMP = SCPI_InputToStep(value.d,(double)0.1);
				if( (HIPCET_TEMP>1000)||(HIPCET_TEMP<0) ) {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
				break;
			case SCPI_Config_GoNoGo_Value:
				HIGHVAL_TEMP = SCPI_InputToStep(value.d,resolution);
				if( (HIGHVAL_TEMP > umax)||(HIGHVAL_TEMP < *Value_Low) ) {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
				break;
			default:
				Command_Done=0;
				break;
			}
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			switch(Data_tmp->SPECTYPE) {
			case SCPI_Config_GoNoGo_Percent:
				*Percent_High=(UWORD)HIPCET_TEMP;
				HIGHVAL_TEMP=(*Value_Center)*(1+HIPCET_TEMP*0.1);
				if(HIGHVAL_TEMP>umax)
					HIGHVAL_TEMP=umax;
				else if(HIGHVAL_TEMP < *Value_Low)
					HIGHVAL_TEMP = *Value_Low;
				*Value_High=(UWORD)HIGHVAL_TEMP;
				break;

			case SCPI_Config_GoNoGo_Value:
				*Value_High 	= (UWORD)HIGHVAL_TEMP;
				*Value_Center	= (*Value_High+*Value_Low)/2;
				*Percent_High	= (UWORD)((*Value_High - *Value_Center))/(*Value_Center)/0.1;
				*Percent_Low	= (UWORD)((*Value_Center - *Value_Low))/(*Value_Center)/0.1;
				break;

			default:
				break;
			}
			for(i=0 ; i<5 ; i++)
				*(CENTERVAL+i)=*(Value_Center+i);

			if((M_num==P_CC_SPEC||M_num==P_CR_SPEC||M_num==P_CV_SPEC||M_num==P_CP_SPEC)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			if(Disp_tmp->CURRMODE==CC_MODE) {
				tx_data.ADDRH = 0x01;
				if(Disp_tmp->CC.STADYNA )
					tx_data.ADDRL = 0x60;
				else
					tx_data.ADDRL = 0x30;
			} else if(Disp_tmp->CURRMODE==CR_MODE) {
				tx_data.ADDRH = 0x02;
				if(Disp_tmp->CR.STADYNA )
					tx_data.ADDRL = 0x60;
				else
					tx_data.ADDRL = 0x30;
			} else if(Disp_tmp->CURRMODE==CV_MODE) {
				tx_data.ADDRH = 0x03;
				tx_data.ADDRL = 0x30;
			} else if(Disp_tmp->CURRMODE==CP_MODE) {
				tx_data.ADDRH = 0x04;
				if(Disp_tmp->CP.STADYNA )
					tx_data.ADDRL = 0x60;
				else
					tx_data.ADDRL = 0x30;
			}
			SendTXData(&tx_data);
		}
	}
// Code End

}

void idCONFigureGNGL(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,i;
	UWORD umax,umin;
	UWORD *Value_Center,*Value_Low,*Percent_Low,*Value_High,*Percent_High;
	UWORD *Value_Center_Disp,*Value_Low_Disp,*Percent_Low_Disp,*Value_High_Disp,*Percent_High_Disp;
	UWORD *CENTERVAL;
	char Data_Buffer[20];
	double LOWVAL_TEMP,LOWPCET_TEMP,resolution;
	UBYTE Precision;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	switch(Data_tmp->CURRMODE) {
	case SCPI_CC:
		switch(Data_tmp->CC.STADYNA) {
		case SCPI_Dynamic_Status:
			Percent_High	= &Data_tmp->CC.DYNA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CC.DYNA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CC.DYNA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CC.DYNA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CC.DYNA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CC.DYNA[Disp_tmp->IRange].CENTERVAL;
			break;
		case SCPI_Static_Status:
			Percent_High	= &Data_tmp->CC.STA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CC.STA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CC.STA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CC.STA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CC.STA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CC.STA[Disp_tmp->IRange].CENTERVAL;
			break;
		default:
			break;
		}
		resolution	= ptrMODEL_TYPE->CC_SPEC[SCPI_Config_GoNoGo_High].Resolution;
		Precision = (ptrMODEL_TYPE->CC_SPEC)[0].precision;
		umax		= ptrMODEL_TYPE->CC_SPEC[SCPI_Config_GoNoGo_High].Max;
		umin		= ptrMODEL_TYPE->CC_SPEC[SCPI_Config_GoNoGo_High].Min;
		break;
	case SCPI_CR:
		switch(Data_tmp->CR.STADYNA) {
		case SCPI_Dynamic_Status:
			Percent_High	= &Data_tmp->CR.DYNA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CR.DYNA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CR.DYNA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CR.DYNA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CR.DYNA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CR.DYNA[Disp_tmp->IRange].CENTERVAL;
			break;
		case SCPI_Static_Status:
			Percent_High	= &Data_tmp->CR.STA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CR.STA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CR.STA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CR.STA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CR.STA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CR.STA[Disp_tmp->IRange].CENTERVAL;
			break;
		default:
			break;
		}
		resolution	= ptrMODEL_TYPE->CR_SPEC[SCPI_Config_GoNoGo_High].Resolution;
		Precision = (ptrMODEL_TYPE->CR_SPEC)[0].precision;
		umax		= ptrMODEL_TYPE->CR_SPEC[SCPI_Config_GoNoGo_High].Max;
		umin		= ptrMODEL_TYPE->CR_SPEC[SCPI_Config_GoNoGo_High].Min;
		break;
	case SCPI_CV:
		Percent_High	= &Data_tmp->CV.STA[Data_tmp->VRange].HIPCET;
		Percent_Low 	= &Data_tmp->CV.STA[Data_tmp->VRange].LOWPCET;
		Value_High		= &Data_tmp->CV.STA[Data_tmp->VRange].HIGHVAL;
		Value_Center	= &Data_tmp->CV.STA[Data_tmp->VRange].CENTERVAL;
		Value_Low		= &Data_tmp->CV.STA[Data_tmp->VRange].LOWVAL;
		CENTERVAL		= &Disp_tmp->CV.STA[Disp_tmp->VRange].CENTERVAL;

		resolution	= ptrMODEL_TYPE->CV_SPEC[SCPI_Config_GoNoGo_High].Resolution;
		Precision = (ptrMODEL_TYPE->CV_SPEC)[0].precision;
		umax		= ptrMODEL_TYPE->CV_SPEC[SCPI_Config_GoNoGo_High].Max;
		umin		= ptrMODEL_TYPE->CV_SPEC[SCPI_Config_GoNoGo_High].Min;
		break;
	case SCPI_CP:
		switch(Data_tmp->CP.STADYNA) {
		case SCPI_Dynamic_Status:
			Percent_High	= &Data_tmp->CP.DYNA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CP.DYNA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CP.DYNA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CP.DYNA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CP.DYNA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CP.DYNA[Disp_tmp->IRange].CENTERVAL;
			break;
		case SCPI_Static_Status:
			Percent_High	= &Data_tmp->CP.STA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CP.STA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CP.STA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CP.STA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CP.STA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CP.STA[Disp_tmp->IRange].CENTERVAL;
			break;
		default:
			break;
		}
		resolution	= ptrMODEL_TYPE->CP_SPEC[SCPI_Config_GoNoGo_High].Resolution;
		Precision = (ptrMODEL_TYPE->CP_SPEC)[0].precision;
		umax		= ptrMODEL_TYPE->CP_SPEC[SCPI_Config_GoNoGo_High].Max;
		umin		= ptrMODEL_TYPE->CP_SPEC[SCPI_Config_GoNoGo_High].Min;
		break;
	default:
		return;
	}

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(Disp_tmp->SPECTYPE==SCPI_Config_GoNoGo_Percent) {
			sprintf(Data_Buffer,"%3.1f",(float)(*Percent_Low)*0.1);
			ExportProcess(String_Data,0,0,Data_Buffer,0);
		} else if(Disp_tmp->SPECTYPE==SCPI_Config_GoNoGo_Value) {
			ExportProcess(Float_Data,(float)(*Value_Low*resolution),0,0,Precision);
		}
	} else {

		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			if(Disp_tmp->SPECTYPE) {
				LOWPCET_TEMP = SCPI_InputToStep(value.d ,(double)0.1);
				if((LOWPCET_TEMP>1000)||(LOWPCET_TEMP<0)) {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
			} else {
				LOWVAL_TEMP = SCPI_InputToStep(value.d,resolution);
				if((LOWVAL_TEMP > *Value_High)||(LOWVAL_TEMP<0)) {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
			}
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if(Disp_tmp->SPECTYPE) {				/*	Percent */
				*Percent_Low = (UWORD)LOWPCET_TEMP;
				*Value_Low = *Value_Center - (((*Value_Center)*(*Percent_Low))/1000.0);
			} else {								/*	Value	*/
				*Value_Low = (UWORD)LOWVAL_TEMP;
				*Value_Center = (*Value_High+*Value_Low)/2;
				*Percent_High=(UWORD)((*Value_High - *Value_Center)*1000)/(*Value_Center)/1.0;
				*Percent_Low=(UWORD)((*Value_Center - *Value_Low)*1000)/(*Value_Center)/1.0;
			}

			for(i=0 ; i<5 ; i++)
				*(CENTERVAL+i)=*(Value_Center+i);

			if((M_num==P_CC_SPEC||M_num==P_CR_SPEC||M_num==P_CV_SPEC||M_num==P_CP_SPEC)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE ;
				Draw_Set_parameter();
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			if(Data_tmp->CURRMODE==CC_MODE) {
				tx_data.ADDRH = 0x01;
				if(Data_tmp->CC.STADYNA )
					tx_data.ADDRL = 0x60;
				else
					tx_data.ADDRL = 0x30;
			} else if(Data_tmp->CURRMODE==CR_MODE) {
				tx_data.ADDRH = 0x02;
				if(Data_tmp->CR.STADYNA )
					tx_data.ADDRL = 0x60;
				else
					tx_data.ADDRL = 0x30;
			} else if(Data_tmp->CURRMODE==CV_MODE) {
				tx_data.ADDRH = 0x03;
				if(Data_tmp->CR.STADYNA )
					tx_data.ADDRL = 0x60;
				else
					tx_data.ADDRL = 0x30;
			} else if(Data_tmp->CURRMODE==CP_MODE) {
				tx_data.ADDRH = 0x04;
				if(Data_tmp->CR.STADYNA )
					tx_data.ADDRL = 0x60;
				else
					tx_data.ADDRL = 0x30;
			}

			SendTXData(&tx_data);
		}
	}
// Code End

}

void idCONFigureGNGC(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,i;
	UWORD umax,umin,CENTERVAL_new;
	UWORD *Value_Center,*Value_Low,*Percent_Low,*Value_High,*Percent_High;
	UWORD *CENTERVAL;
	UBYTE Precision;
	char Data_Buffer[12];
	double LOWVAL_TEMP,HIGHVAL_TEMP,resolution;

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;

	if(Disp_tmp->SPECTYPE != SCPI_Config_GoNoGo_Percent) {
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}

	switch(Data_tmp->CURRMODE) {
	case SCPI_CC:
		switch(Data_tmp->CC.STADYNA) {
		case SCPI_Dynamic_Status:
			Percent_High	= &Data_tmp->CC.DYNA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CC.DYNA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CC.DYNA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CC.DYNA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CC.DYNA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CC.DYNA[Disp_tmp->IRange].CENTERVAL;
			break;

		case SCPI_Static_Status:
			Percent_High	= &Data_tmp->CC.STA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CC.STA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CC.STA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CC.STA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CC.STA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CC.STA[Disp_tmp->IRange].CENTERVAL;
			break;

		default:
			break;
		}
		resolution	= ptrMODEL_TYPE->CC_SPEC[SCPI_Config_GoNoGo_Center].Resolution*1000;
		Precision 	= (ptrMODEL_TYPE->CC_SPEC)[0].precision;
		umax		= ptrMODEL_TYPE->CC_SPEC[SCPI_Config_GoNoGo_Center].Max;
		umin		= ptrMODEL_TYPE->CC_SPEC[SCPI_Config_GoNoGo_Center].Min;
		break;

	case SCPI_CR:
		switch(Data_tmp->CR.STADYNA) {
		case SCPI_Dynamic_Status:
			Percent_High	= &Data_tmp->CR.DYNA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CR.DYNA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CR.DYNA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CR.DYNA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CR.DYNA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CR.DYNA[Disp_tmp->IRange].CENTERVAL;
			break;

		case SCPI_Static_Status:
			Percent_High	= &Data_tmp->CR.STA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CR.STA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CR.STA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CR.STA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CR.STA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CR.STA[Disp_tmp->IRange].CENTERVAL;
			break;

		default:
			break;
		}
		resolution	= ptrMODEL_TYPE->CR_SPEC[SCPI_Config_GoNoGo_Center].Resolution*1000;
		Precision 	= (ptrMODEL_TYPE->CR_SPEC)[0].precision;
		umax		= ptrMODEL_TYPE->CR_SPEC[SCPI_Config_GoNoGo_Center].Max;
		umin		= ptrMODEL_TYPE->CR_SPEC[SCPI_Config_GoNoGo_Center].Min;
		break;

	case SCPI_CV:
		Percent_High	= &Data_tmp->CV.STA[Data_tmp->VRange].HIPCET;
		Percent_Low 	= &Data_tmp->CV.STA[Data_tmp->VRange].LOWPCET;
		Value_High		= &Data_tmp->CV.STA[Data_tmp->VRange].HIGHVAL;
		Value_Center	= &Data_tmp->CV.STA[Data_tmp->VRange].CENTERVAL;
		Value_Low		= &Data_tmp->CV.STA[Data_tmp->VRange].LOWVAL;
		CENTERVAL		= &Disp_tmp->CV.STA[Disp_tmp->VRange].CENTERVAL;

		resolution	= ptrMODEL_TYPE->CV_SPEC[SCPI_Config_GoNoGo_Center].Resolution*1000;
		Precision 	= (ptrMODEL_TYPE->CV_SPEC)[0].precision;
		umax		= ptrMODEL_TYPE->CV_SPEC[SCPI_Config_GoNoGo_Center].Max;
		umin		= ptrMODEL_TYPE->CV_SPEC[SCPI_Config_GoNoGo_Center].Min;
		break;

	case SCPI_CP:
		switch(Data_tmp->CP.STADYNA) {
		case SCPI_Dynamic_Status:
			Percent_High	= &Data_tmp->CP.DYNA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CP.DYNA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CP.DYNA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CP.DYNA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CP.DYNA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CP.DYNA[Disp_tmp->IRange].CENTERVAL;
			break;

		case SCPI_Static_Status:
			Percent_High	= &Data_tmp->CP.STA[Data_tmp->IRange].HIPCET;
			Percent_Low 	= &Data_tmp->CP.STA[Data_tmp->IRange].LOWPCET;
			Value_High		= &Data_tmp->CP.STA[Data_tmp->IRange].HIGHVAL;
			Value_Center	= &Data_tmp->CP.STA[Data_tmp->IRange].CENTERVAL;
			Value_Low		= &Data_tmp->CP.STA[Data_tmp->IRange].LOWVAL;
			CENTERVAL		= &Disp_tmp->CP.STA[Disp_tmp->IRange].CENTERVAL;
			break;

		default:
			break;
		}
		resolution	= ptrMODEL_TYPE->CP_SPEC[SCPI_Config_GoNoGo_Center].Resolution*1000;
		Precision 	= (ptrMODEL_TYPE->CP_SPEC)[0].precision;
		umax		= ptrMODEL_TYPE->CP_SPEC[SCPI_Config_GoNoGo_Center].Max;
		umin		= ptrMODEL_TYPE->CP_SPEC[SCPI_Config_GoNoGo_Center].Min;
		break;

	default:
		break;
	}
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(Disp_tmp->SPECTYPE==SCPI_Config_GoNoGo_Percent) {
			ExportProcess(Float_Data,(float)(*Value_Center)*resolution/1000.0,0,0,Precision);
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {

			CENTERVAL_new = value.d*1000 / resolution;
			if((CENTERVAL_new > umax) || (CENTERVAL_new < umin)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done = 1;

		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			*Value_Center = CENTERVAL_new;
			HIGHVAL_TEMP = CENTERVAL_new *(1 + (double)((*Percent_High)/1000.0));
			if(HIGHVAL_TEMP > umax)
				HIGHVAL_TEMP = umax;
			LOWVAL_TEMP = CENTERVAL_new *(1 - (double)((*Percent_Low)/1000.0));
			if(LOWVAL_TEMP > HIGHVAL_TEMP)
				LOWVAL_TEMP = HIGHVAL_TEMP;
			*Value_High = (UWORD)HIGHVAL_TEMP;
			*Value_Low = (UWORD)LOWVAL_TEMP;

			for(i=0 ; i<5 ; i++)
				*(CENTERVAL+i) = *(Value_Center+i);

			if((M_num==P_CC_SPEC||M_num==P_CR_SPEC||M_num==P_CV_SPEC||M_num==P_CP_SPEC)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				Draw_Set_parameter();
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			if(Data_tmp->CURRMODE==CC_MODE) {
				tx_data.ADDRH = 0x01;
				if(Data_tmp->CC.STADYNA )
					tx_data.ADDRL = 0x60;
				else
					tx_data.ADDRL = 0x30;
			} else if(Data_tmp->CURRMODE==CR_MODE) {
				tx_data.ADDRH = 0x02;
				if(Data_tmp->CR.STADYNA )
					tx_data.ADDRL = 0x60;
				else
					tx_data.ADDRL = 0x30;
			} else if(Data_tmp->CURRMODE==CV_MODE) {
				tx_data.ADDRH = 0x03;
				if(Data_tmp->CR.STADYNA )
					tx_data.ADDRL = 0x60;
				else
					tx_data.ADDRL = 0x30;
			} else if(Data_tmp->CURRMODE==CP_MODE) {
				tx_data.ADDRH = 0x04;
				if(Data_tmp->CR.STADYNA )
					tx_data.ADDRL = 0x60;
				else
					tx_data.ADDRL = 0x30;
			}
			SendTXData(&tx_data);
		}
	}
// Code End
}

void idCONFigurePARallel(STR_PARSER * p)
{
#if 0
	GW_TYPE value;

	UBYTE Command_Done=0,i;
	char str[32];
	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		switch(Disp_tmp->CONF.Para_Data.Mode) {
		case SCPI_Config_Parallel_Mode_Master:
			if ((Disp_tmp->CONF.Para_Data.Parallel_Number+Disp_tmp->CONF.Para_Data.Booster_Number+2)==SCPI_Config_Parallel_Number_OFF)
				ExportProcess(String_Data,0,0,"Mode:Master, Number:OFF",0);
			else if (((Disp_tmp->CONF.Para_Data.Parallel_Number+2)>=SCPI_Config_Parallel_Number_2) &&
			         ((Disp_tmp->CONF.Para_Data.Parallel_Number+2)<=SCPI_Config_Parallel_Number_5)) {
				sprintf(str,"Mode:Master, Parallel Number:%d",Disp_tmp->CONF.Para_Data.Parallel_Number+1);
				ExportProcess(String_Data,0,0,str,0);
			} else if (((Disp_tmp->CONF.Para_Data.Booster_Number+6)>=SCPI_Config_Booster_Number_1) &&
			           ((Disp_tmp->CONF.Para_Data.Booster_Number+6)<=SCPI_Config_Booster_Number_4)) {
				sprintf(str,"Mode:Master, Booster Number:%d",Disp_tmp->CONF.Para_Data.Booster_Number);
				ExportProcess(String_Data,0,0,str,0);
			} else
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
			break;
		case SCPI_Config_Parallel_Mode_Slave:
			ExportProcess(String_Data,0,0,"Mode:Slave",0);
			break;

		default:
			break;
		}
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			Command_Done=1;
			if(value.si==0) { //m
				Data_tmp->CONF.Para_Data.Mode=0;//value.si;
				Command_Done = 1;
			} else if(value.si==1) { //,s
				Data_tmp->CONF.Para_Data.Parallel_Number =0;
				Data_tmp->CONF.Para_Data.Booster_Number =0;
				Data_tmp->CONF.Para_Data.Mode=1;
				Command_Done = 1;
			} else if(value.si==2) { //off
				Data_tmp->CONF.Para_Data.Parallel_Number=0;
				Data_tmp->CONF.Para_Data.Booster_Number=0;
			} else if(value.si<7) { //p2,p3,p4,p5
				Data_tmp->CONF.Para_Data.Booster_Number= 0;
				Data_tmp->CONF.Para_Data.Parallel_Number=value.si-2;
				Data_tmp->CONF.Para_Data.Mode= 0;
			} else { //b1,b2,b3,b4
				if(Data_tmp->IRange==LOW_RANGE) {
					scpi_SetCommandError( p, _ERR_221_Settings_conflict);
					return;
				}
				Data_tmp->CONF.Para_Data.Parallel_Number=0;
				Data_tmp->CONF.Para_Data.Booster_Number= value.si-6;
				Data_tmp->CONF.Para_Data.Mode= 0;
			}
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Disp_tmp->CONF.Para_Data.Mode=Data_tmp->CONF.Para_Data.Mode;
			Disp_tmp->CONF.Para_Data.Parallel_Number = Data_tmp->CONF.Para_Data.Parallel_Number;
			Disp_tmp->CONF.Para_Data.Booster_Number = Data_tmp->CONF.Para_Data.Booster_Number;
			if(M_num != P_CONF_Para) {
				M_num=P_CONF_Para;
				MenuRedrawFlag = MENU_CHANGE;
			}
			ChanRedrawFlag |= CHAN_CHANGE;
			if((M_num==P_CONF_Para)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH = Para_Ext_Command;
			tx_data.ADDRL = Para_Ext_Setting;
			SendTXData(&tx_data);
			SCPI_RemFastDelay = 1;
		}
	}
#endif
// Code End
}

void idCONFigureSTEPCCH(STR_PARSER * p) //AAAAA
{

	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	UWORD Max_Count,Min_Count;
	char Data_Buffer[20];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
	ResolutionTemp=(ptrMODEL_TYPE->CC)[SCPI_IRange_H*10].Resolution;
	SettingCount=Disp_tmp->CC.VALUE_STEP[SCPI_IRange_H];
	Real_Value=(double)(SettingCount*ResolutionTemp)*Para_s;
	Max_Count=(ptrMODEL_TYPE->CC)[SCPI_IRange_H*10].Max/2;
	Min_Count=(ptrMODEL_TYPE->CC)[SCPI_IRange_H*10].Min+1;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Precision = (ptrMODEL_TYPE->CC)[HIGH_RANGE*10].precision;
		SCPI_Printf(Data_Buffer,"CCH:",Real_Value,Precision);
		ExportProcess(String_Data,0,0,Data_Buffer,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			SettingCount = SCPI_InputToStep((value.d/Para_s),ResolutionTemp);
			if((SettingCount < Min_Count)||(SettingCount>Max_Count)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? Max_Count : Min_Count;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CC.VALUE_STEP[SCPI_IRange_H] = SettingCount;
			Disp_tmp->CC.VALUE_STEP[SCPI_IRange_H] = SettingCount;
			if((M_num==P_CONF_KNOB)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				Draw_Set_parameter();
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
		}
	}
// Code End

}

void idCONFigureSTEPCCL(STR_PARSER * p)
{
	//
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	UWORD Max_Count,Min_Count;
	char Data_Buffer[20];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;

	ResolutionTemp=(ptrMODEL_TYPE->CC)[SCPI_IRange_L*10].Resolution;
	SettingCount=Disp_tmp->CC.VALUE_STEP[SCPI_IRange_L];
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
	Real_Value=(double)(SettingCount*ResolutionTemp)*Para_s;
	Max_Count=(ptrMODEL_TYPE->CC)[SCPI_IRange_L*10].Max/2;
	Min_Count=(ptrMODEL_TYPE->CC)[SCPI_IRange_L*10].Min+1;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Precision = (ptrMODEL_TYPE->CC)[LOW_RANGE*10].precision;
		SCPI_Printf(Data_Buffer,"CCL:",Real_Value,Precision);
		ExportProcess(String_Data,0,0,Data_Buffer,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			SettingCount = SCPI_InputToStep((value.d/Para_s),ResolutionTemp);
			if((SettingCount < Min_Count)||(SettingCount>Max_Count)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? Max_Count : Min_Count;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CC.VALUE_STEP[SCPI_IRange_L] = SettingCount;
			Disp_tmp->CC.VALUE_STEP[SCPI_IRange_L] = SettingCount;
			if((M_num==P_CONF_KNOB)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				Draw_Set_parameter();
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
		}
	}
// Code End
}

void idCONFigureSTEPCC(STR_PARSER * p)
{
	UBYTE For_loop_index,Precision;
	UWORD Step_Count[3];
	double ResolutionTemp[3],Step_Value[3];
	char str[48];
	char str_1[16],str_2[16],str_3[16];

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	float Para_s;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		for (For_loop_index=SCPI_IRange_L; For_loop_index<=SCPI_IRange_H; For_loop_index++) {
			ResolutionTemp[For_loop_index]=(ptrMODEL_TYPE->CC)[For_loop_index*10].Resolution;
			Step_Count[For_loop_index]=Disp_tmp->CC.VALUE_STEP[For_loop_index];
			Step_Value[For_loop_index]=(double)(Step_Count[For_loop_index]*ResolutionTemp[For_loop_index])*Para_s;
		}
		Precision = (ptrMODEL_TYPE->CC)[LOW_RANGE*10].precision;
		SCPI_Printf(str_1,"CCL:",Step_Value[SCPI_IRange_L],Precision);
		//Precision = (ptrMODEL_TYPE->CC)[Mid_RANGE*10].precision;
		//SCPI_Printf(str_2,"CCM:",Step_Value[SCPI_IRange_M],Precision);
		Precision = (ptrMODEL_TYPE->CC)[HIGH_RANGE*10].precision;
		SCPI_Printf(str_3,"CCH:",Step_Value[SCPI_IRange_H],Precision);
		sprintf(str,"%s, %s, %s",str_3,str_2,str_1);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}

void idCONFigureSTEPCRH(STR_PARSER * p)
{
	//
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	UWORD Max_Count,Min_Count;
	char Data_Buffer[20];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;

	ResolutionTemp=(ptrMODEL_TYPE->CR)[SCPI_IRange_H*10].Resolution;
	SettingCount=Disp_tmp->CR.VALUE_STEP[SCPI_IRange_H];
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
	Real_Value=(double)(SettingCount*ResolutionTemp)*Para_s;
	Max_Count=(ptrMODEL_TYPE->CR)[SCPI_IRange_H*10].Max/2;
	Min_Count=(ptrMODEL_TYPE->CR)[SCPI_IRange_H*10].Min+1;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Precision = (ptrMODEL_TYPE->CR)[HIGH_RANGE*10].precision;
		SCPI_Printf(Data_Buffer,"CRH:",Real_Value,Precision);
		ExportProcess(String_Data,0,0,Data_Buffer,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			SettingCount = SCPI_InputToStep((value.d/Para_s),ResolutionTemp);
			if((SettingCount < Min_Count)||(SettingCount>Max_Count)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? Max_Count : Min_Count;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CR.VALUE_STEP[SCPI_IRange_H] = SettingCount;
			Disp_tmp->CR.VALUE_STEP[SCPI_IRange_H] = SettingCount;
			if((M_num==P_CONF_KNOB)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				Draw_Set_parameter();
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
		}
	}
// Code End
}



void idCONFigureSTEPCRL(STR_PARSER * p)
{
	//
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	UWORD Max_Count,Min_Count;
	char Data_Buffer[20];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;

	ResolutionTemp=(ptrMODEL_TYPE->CR)[SCPI_IRange_L*10].Resolution;
	SettingCount=Disp_tmp->CR.VALUE_STEP[SCPI_IRange_L];
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
	Real_Value=(double)(SettingCount*ResolutionTemp)*Para_s;
	Max_Count=(ptrMODEL_TYPE->CR)[SCPI_IRange_L*10].Max/2;
	Min_Count=(ptrMODEL_TYPE->CR)[SCPI_IRange_L*10].Min+1;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Precision = (ptrMODEL_TYPE->CR)[LOW_RANGE*10].precision;
		SCPI_Printf(Data_Buffer,"CRL:",Real_Value,Precision);
		ExportProcess(String_Data,0,0,Data_Buffer,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			SettingCount = SCPI_InputToStep((value.d/Para_s),ResolutionTemp);
			if((SettingCount < Min_Count)||(SettingCount>Max_Count)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? Max_Count : Min_Count;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CR.VALUE_STEP[SCPI_IRange_L] = SettingCount;
			Disp_tmp->CR.VALUE_STEP[SCPI_IRange_L] = SettingCount;
			if((M_num==P_CONF_KNOB)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				Draw_Set_parameter();
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
		}
	}
// Code End
}

void idCONFigureSTEPCR(STR_PARSER * p)
{
	UBYTE For_loop_index;
	UWORD Step_Count[3];
	double ResolutionTemp[3],Step_Value[3];
	UBYTE Precision;
	char str[48];
	char str_1[16],str_2[16],str_3[16];

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	float Para_s;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		for (For_loop_index=SCPI_IRange_L; For_loop_index<=SCPI_IRange_H; For_loop_index++) {
			ResolutionTemp[For_loop_index]=(ptrMODEL_TYPE->CR)[For_loop_index*10].Resolution;
			Step_Count[For_loop_index]=Disp_tmp->CR.VALUE_STEP[For_loop_index];
			Step_Value[For_loop_index]=(double)(Step_Count[For_loop_index]*ResolutionTemp[For_loop_index])*Para_s;
		}
		Precision = (ptrMODEL_TYPE->CR)[LOW_RANGE*10].precision;
		SCPI_Printf(str_1,"CRL:",Step_Value[SCPI_IRange_L],Precision);
	//	Precision = (ptrMODEL_TYPE->CR)[Mid_RANGE*10].precision;
		//SCPI_Printf(str_2,"CRM:",Step_Value[SCPI_IRange_M],Precision);
		Precision = (ptrMODEL_TYPE->CR)[HIGH_RANGE*10].precision;
		SCPI_Printf(str_3,"CRH:",Step_Value[SCPI_IRange_H],Precision);
		sprintf(str,"%s, %s, %s",str_3,str_2,str_1);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}

void idCONFigureSTEPCVH(STR_PARSER * p)
{
	//
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	UWORD Max_Count,Min_Count;
	char Data_Buffer[20];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;

	ResolutionTemp=(ptrMODEL_TYPE->CV)[SCPI_VRange_H*3].Resolution;
	SettingCount=Disp_tmp->CV.VALUE_STEP[SCPI_VRange_H];
	Real_Value=(double)(SettingCount*ResolutionTemp);
	Max_Count=(ptrMODEL_TYPE->CV)[SCPI_VRange_H*3].Max/2;
	Min_Count=(ptrMODEL_TYPE->CV)[SCPI_VRange_H*3].Min+1;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		//sprintf(Data_Buffer,"CVH:%.3f",Real_Value);
		//ExportProcess(String_Data,0,0,Data_Buffer,0);
		Precision = (ptrMODEL_TYPE->CV)[SCPI_VRange_H*3].precision;
		SCPI_Printf(Data_Buffer,"CVH:",Real_Value,Precision);
		ExportProcess(String_Data,0,0,Data_Buffer,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			SettingCount = SCPI_InputToStep(value.d,ResolutionTemp);
			if((SettingCount < Min_Count)||(SettingCount>Max_Count)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? Max_Count : Min_Count;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CV.VALUE_STEP[SCPI_VRange_H] = SettingCount;
			Disp_tmp->CV.VALUE_STEP[SCPI_VRange_H] = SettingCount;
			if((M_num==P_CONF_KNOB)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				Draw_Set_parameter();
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
		}
	}
// Code End
}

void idCONFigureSTEPCVL(STR_PARSER * p)
{
	//
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	UWORD Max_Count,Min_Count;
	char Data_Buffer[20];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;

	ResolutionTemp=(ptrMODEL_TYPE->CV)[SCPI_VRange_L*3].Resolution;
	SettingCount=Disp_tmp->CV.VALUE_STEP[SCPI_VRange_L];
	Real_Value=(double)(SettingCount*ResolutionTemp);
	Max_Count=(ptrMODEL_TYPE->CV)[SCPI_VRange_L*3].Max/2;
	Min_Count=(ptrMODEL_TYPE->CV)[SCPI_VRange_L*3].Min+1;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Precision = (ptrMODEL_TYPE->CV)[SCPI_VRange_L*3].precision;
		SCPI_Printf(Data_Buffer,"CVL:",Real_Value,Precision);
		ExportProcess(String_Data,0,0,Data_Buffer,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			SettingCount = SCPI_InputToStep(value.d,ResolutionTemp);
			if((SettingCount < Min_Count)||(SettingCount>Max_Count)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? Max_Count : Min_Count;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CV.VALUE_STEP[SCPI_VRange_L] = SettingCount;
			Disp_tmp->CV.VALUE_STEP[SCPI_VRange_L] = SettingCount;
			if((M_num==P_CONF_KNOB)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				Draw_Set_parameter();
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
		}
	}
// Code End
}

void idCONFigureSTEPCV(STR_PARSER * p)
{
	UBYTE For_loop_index,Precision;
	UWORD Step_Count[3];
	double ResolutionTemp[3],Step_Value[3];
	char str[32];
	char str_1[16],str_2[16];

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		for (For_loop_index=SCPI_VRange_L; For_loop_index<=SCPI_VRange_H; For_loop_index++) {
			ResolutionTemp[For_loop_index]=(ptrMODEL_TYPE->CV)[For_loop_index*3].Resolution;
			Step_Count[For_loop_index]=Disp_tmp->CV.VALUE_STEP[For_loop_index];
			Step_Value[For_loop_index]=(double)(Step_Count[For_loop_index]*ResolutionTemp[For_loop_index]);
		}
		Precision = (ptrMODEL_TYPE->CV)[SCPI_VRange_L*3].precision;
		SCPI_Printf(str_1,"CVL:",Step_Value[SCPI_VRange_L],Precision);
		Precision = (ptrMODEL_TYPE->CV)[SCPI_VRange_H*3].precision;
		SCPI_Printf(str_2,"CVH:",Step_Value[SCPI_VRange_H],Precision);
		sprintf(str,"%s, %s",str_2,str_1);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}

void idCONFigureSTEPCPH(STR_PARSER * p)
{
	//
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	UWORD Max_Count,Min_Count;
	char Data_Buffer[20];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;

	ResolutionTemp=(ptrMODEL_TYPE->CP)[SCPI_IRange_H*10].Resolution;
	SettingCount=Disp_tmp->CP.VALUE_STEP[SCPI_IRange_H];
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
	Real_Value=(double)(SettingCount*ResolutionTemp)*Para_s;
	Max_Count=(ptrMODEL_TYPE->CP)[SCPI_IRange_H*10].Max/2;
	Min_Count=(ptrMODEL_TYPE->CP)[SCPI_IRange_H*10].Min+1;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Precision = (ptrMODEL_TYPE->CP)[SCPI_IRange_H*10].precision;
		SCPI_Printf(Data_Buffer,"CPH:",Real_Value,Precision);
		ExportProcess(String_Data,0,0,Data_Buffer,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			SettingCount = SCPI_InputToStep((value.d/Para_s),ResolutionTemp);
			if((SettingCount < Min_Count)||(SettingCount>Max_Count)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? Max_Count : Min_Count;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CP.VALUE_STEP[SCPI_IRange_H] = SettingCount;
			Disp_tmp->CP.VALUE_STEP[SCPI_IRange_H] = SettingCount;
			if((M_num==P_CONF_KNOB)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				Draw_Set_parameter();
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
		}
	}
// Code End
}

void idCONFigureSTEPCPL(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	UWORD Max_Count,Min_Count;
	char Data_Buffer[20];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;

	ResolutionTemp=(ptrMODEL_TYPE->CP)[SCPI_IRange_L*10].Resolution;
	SettingCount=Disp_tmp->CP.VALUE_STEP[SCPI_IRange_L];
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
	Real_Value=(double)(SettingCount*ResolutionTemp)*Para_s;
	Max_Count=(ptrMODEL_TYPE->CP)[SCPI_IRange_L*10].Max/2;
	Min_Count=(ptrMODEL_TYPE->CP)[SCPI_IRange_L*10].Min+1;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Precision = (ptrMODEL_TYPE->CP)[SCPI_IRange_L*10].precision;
		SCPI_Printf(Data_Buffer,"CPL:",Real_Value,Precision);
		ExportProcess(String_Data,0,0,Data_Buffer,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			SettingCount = SCPI_InputToStep((value.d/Para_s),ResolutionTemp);
			if((SettingCount < Min_Count)||(SettingCount>Max_Count)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? Max_Count : Min_Count;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CP.VALUE_STEP[SCPI_IRange_L] = SettingCount;
			Disp_tmp->CP.VALUE_STEP[SCPI_IRange_L] = SettingCount;
			if((M_num==P_CONF_KNOB)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				Draw_Set_parameter();
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
		}
	}
// Code End
}

void idCONFigureSTEPCP(STR_PARSER * p)
{
	UBYTE For_loop_index;
	UWORD Step_Count[3];
	double ResolutionTemp[3],Step_Value[3];
	UBYTE Precision;
	char str[48];
	char str_1[16],str_2[16],str_3[16];

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	float Para_s;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		for (For_loop_index=SCPI_IRange_L; For_loop_index<=SCPI_IRange_H; For_loop_index++) {
			ResolutionTemp[For_loop_index]=(ptrMODEL_TYPE->CP)[For_loop_index*10].Resolution;
			Step_Count[For_loop_index]=Disp_tmp->CP.VALUE_STEP[For_loop_index];
			Step_Value[For_loop_index]=(double)(Step_Count[For_loop_index]*ResolutionTemp[For_loop_index])*Para_s;
		}
		Precision = (ptrMODEL_TYPE->CP)[LOW_RANGE*10].precision;
		SCPI_Printf(str_1,"CPL:",Step_Value[SCPI_IRange_L],Precision);
		//Precision = (ptrMODEL_TYPE->CP)[Mid_RANGE*10].precision;
		//SCPI_Printf(str_2,"CPM:",Step_Value[SCPI_IRange_M],Precision);
		Precision = (ptrMODEL_TYPE->CP)[HIGH_RANGE*10].precision;
		SCPI_Printf(str_3,"CPH:",Step_Value[SCPI_IRange_H],Precision);
		sprintf(str,"%s, %s, %s",str_3,str_2,str_1);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}

void idCONFigureEXTernalCONTrol(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	char str[32];

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		switch(Disp_tmp->CONF.Ext_Setting.Control+3) {
		case SCPI_Config_Ext_CtrlOFF:
			sprintf(str,"Control:OFF");
			break;
		case SCPI_Config_Ext_Volt:
			sprintf(str,"Control:Volt");
			break;
		case SCPI_Config_Ext_Res:
			sprintf(str,"Control:Res");
			break;
		case SCPI_Config_Ext_Rinverse:
			sprintf(str,"Control:Rinverse");
			break;
		default:
			return;
		}
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			Data_tmp->CONF.Ext_Setting.Control = value.si;
			Command_Done = 1;

		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if (Command_Done) {
			Disp_tmp->CONF.Ext_Setting.LoadOn_IN=Data_tmp->CONF.Ext_Setting.LoadOn_IN;
			Disp_tmp->CONF.Ext_Setting.Control=Data_tmp->CONF.Ext_Setting.Control;
			if((M_num==P_CONF_Ext)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				ChanRedrawFlag = CHAN_STATUS;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			} else {
				ChanRedrawFlag = CHAN_STATUS;
				DataRedrawFlag = BG_CLEAR + PARA_CHANGE;
			}
			tx_data.ADDRH = Para_Ext_Command;
			tx_data.ADDRL = Para_Ext_Setting;
			SendTXData(&tx_data);

			tx_data.ADDRH = Cal_FPGA_Command;
			tx_data.ADDRL = Cal_FPGA_Load_Meas_Default;
			SendTXData(&tx_data);

			SCPI_RemFastDelay = 1;
		}
	}
// Code End
}

void idCONFigureEXTernalLOADonin(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	char str[32];

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		switch(Disp_tmp->CONF.Ext_Setting.LoadOn_IN) {
		case SCPI_Config_Ext_LoadOFF:
			sprintf(str,"LoadOn In:OFF");
			break;
		case SCPI_Config_Ext_High:
			sprintf(str,"LoadOn In:High");
			break;
		case SCPI_Config_Ext_Low:
			sprintf(str,"LoadOn In:Low");
			break;
		default:
			return;
		}
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			Data_tmp->CONF.Ext_Setting.LoadOn_IN = value.si;
			Command_Done = 1;

		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if (Command_Done) {
			Disp_tmp->CONF.Ext_Setting.LoadOn_IN=Data_tmp->CONF.Ext_Setting.LoadOn_IN;
			Disp_tmp->CONF.Ext_Setting.Control=Data_tmp->CONF.Ext_Setting.Control;
			if((M_num==P_CONF_Ext)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH = Para_Ext_Command;
			tx_data.ADDRL = Para_Ext_Setting;
			SendTXData(&tx_data);
			SCPI_RemFastDelay = 1;
		}
	}
// Code End
}

void idCONFigureEXTernalSYNC(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	char str[16];

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	//if (NF_flag){
	//	scpi_SetCommandError( p, _ERR_113_Undefined_header);
	//	return;
	//}
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		//if(Data_tmp->CONF.Ext_Setting.MultilPara==1)  //master: 1
		//	ExportProcess(String_Data,0,0,"Master",0);
		//else if(Data_tmp->CONF.Ext_Setting.MultilPara==2) //slave
		//	ExportProcess(String_Data,0,0,"Slave",0);
		//else
			ExportProcess(String_Data,0,0,"OFF",0);
//		break;
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
		//	Data_tmp->CONF.Ext_Setting.MultilPara = value.si;
		//	if(Data_tmp->CONF.Ext_Setting.MultilPara==3)Data_tmp->CONF.Ext_Setting.MultilPara=1;
		//	if(value.si)
		//		Data_tmp->CONF.Ext_Setting.LoadOn_IN=SCPI_Config_Ext_LoadOFF;
			Command_Done = 1;
		} else if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((TEXIO_Version==P3k_Serial_Number.Version)||(value.si>=3)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
		//	Data_tmp->CONF.Ext_Setting.MultilPara = value.si;
		//	if(Data_tmp->CONF.Ext_Setting.MultilPara==3)Data_tmp->CONF.Ext_Setting.MultilPara=1;
			if(value.si == 1)
				Data_tmp->CONF.Ext_Setting.LoadOn_IN=SCPI_Config_Ext_LoadOFF;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if (Command_Done) {
		//	Disp_tmp->CONF.Ext_Setting.MultilPara=Data_tmp->CONF.Ext_Setting.MultilPara;
			Disp_tmp->CONF.Ext_Setting.LoadOn_IN=Data_tmp->CONF.Ext_Setting.LoadOn_IN;
			if((M_num==P_CONF_Ext)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH = Para_Ext_Command;
			tx_data.ADDRL = Para_Ext_Setting;
			SendTXData(&tx_data);
			tx_data.ADDRH = Para_Ext_Command;
			tx_data.ADDRL = Para_Ext_Status;
			SendTXData(&tx_data);
			SCPI_RemFastDelay = 1;
		}
	}
// Code End
}



void idMODE(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Range_Temp,Range_Change=0,Mode_Change=0,Command_Done=0;
	p3k_send_tx_list tx_data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	char	DispScrCurrLoc_tmp,str[20];
	UBYTE load_onoff_status;
	load_onoff_status = UTILITY.LOAD_CTL;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		switch(Data_tmp->CURRMODE) {
		case SCPI_CC:
			if (Data_tmp->CONF.CV_Func_En)
				ExportProcess(String_Data,0,0,"CCCV",0);
			else
				ExportProcess(String_Data,0,0,"CC",0);
			break;
		case SCPI_CR:
			if (Data_tmp->CONF.CV_Func_En)
				ExportProcess(String_Data,0,0,"CRCV",0);
			else
				ExportProcess(String_Data,0,0,"CR",0);
			break;
		case SCPI_CV:
			ExportProcess(String_Data,0,0,"CV",0);
			break;
		case SCPI_CP:
			if (Data_tmp->CONF.CV_Func_En)
				ExportProcess(String_Data,0,0,"CPCV",0);
			else
				ExportProcess(String_Data,0,0,"CP",0);
			break;
		default:
			break;
		}
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			switch(value.si) {
			case SCPI_CC:
				if((Data_tmp->CURRMODE != CC_MODE)||(Data_tmp->CONF.CV_Func_En != 0)) {
					Data_tmp->CURRMODE = CC_MODE;
					Data_tmp->CONF.CV_Func_En = 0;
					Mode_Change = 1;
				}
				break;
			case SCPI_CCCV:
				if((Data_tmp->CURRMODE != CC_MODE)||(Data_tmp->CONF.CV_Func_En != 1)) {
					Data_tmp->CURRMODE = CC_MODE;
					Data_tmp->CONF.CV_Func_En = 1;
					Mode_Change=1;
				}
				break;
			case SCPI_CR:
				if((Data_tmp->CURRMODE != CR_MODE)||(Data_tmp->CONF.CV_Func_En != 0)) {
					Data_tmp->CURRMODE = CR_MODE;
					Data_tmp->CONF.CV_Func_En = 0;
					Mode_Change=1;
				}
				break;
			case SCPI_CRCV:
				if((Data_tmp->CURRMODE != CR_MODE)||(Data_tmp->CONF.CV_Func_En != 1)) {
					Data_tmp->CURRMODE = CR_MODE;
					Data_tmp->CONF.CV_Func_En = 1;
					Mode_Change=1;
				}
				break;
			case SCPI_CV:
				if(Data_tmp->CURRMODE != CV_MODE) {
					Data_tmp->CURRMODE = CV_MODE;
					Data_tmp->CONF.CV_Func_En = 0;
					Mode_Change = 1;
				}
				break;
			case SCPI_CP:
				if((Data_tmp->CURRMODE != CP_MODE)||(Data_tmp->CONF.CV_Func_En != 0)) {
					Data_tmp->CURRMODE = CP_MODE;
					Data_tmp->CONF.CV_Func_En = 0;
					Mode_Change=1;
				}
				break;
			case SCPI_CPCV:
				if((Data_tmp->CURRMODE != CP_MODE)||(Data_tmp->CONF.CV_Func_En != 1)) {
					Data_tmp->CURRMODE = CP_MODE;
					Data_tmp->CONF.CV_Func_En = 1;
					Mode_Change=1;
				}
				break;
			default:
				scpi_SetCommandError( p, _ERR_148_Character_data_not_allowed);
				return;
			}

			if(Mode_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE) {
					M_num = Disp_tmp->CURRMODE;
				}
				if((M_num <= P_CONF_Ext)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					Draw_Set_parameter();
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}
				// 1  loadoff
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x0;
					UTILITY.SHORT_CTL	= Switch_OFF;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu))
						SysRedrawFlag |= PROG_UPDATA;
					PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
					PEL3000_LED_Control( LED_SHORT,UTILITY.SHORT_CTL );
				}
#if Enable_AutoLoad
				if((UTILITY.AutoLoadOffMode==0)&&(load_onoff_status)) {
					PEL3000_LED_Control( LED_LOAD, 1 );
				}
#endif
				// 2 modehandle
				tx_data.ADDRH=Machine_Command;
				tx_data.ADDRL=Machine_modeHandle;
				SendTXData(&tx_data);
				// 3 von_delay
				tx_data.ADDRH=Machine_Command;
				tx_data.ADDRL=Machine_Von_Delay;
				SendTXData(&tx_data);

#if Enable_AutoLoad
				if((UTILITY.AutoLoadOffMode==0)&&(load_onoff_status)) {
					OSTimeDly(5);
					Auto_Load_On();
				}
#endif
			}
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
	}
// Code End
}



void idMODECRANge(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Range_Temp, Range_Change=0, Command_Done=0;

	p3k_send_tx_list tx_data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	Data_tmp->IRange=Disp_tmp->IRange;

	char	DispScrCurrLoc_tmp,str[20];
	double	TrunOn_Add_CV=0.0;
	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	UBYTE load_onoff_status;
	load_onoff_status = UTILITY.LOAD_CTL;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		switch(Data_tmp->IRange) {
		case IRange_High:
			ExportProcess(String_Data,0,0,"High",0);
			break;
//		case IRange_Mid:
//			ExportProcess(String_Data,0,0,"Mid",0);
//			break;
		case IRange_Low:
			ExportProcess(String_Data,0,0,"Low",0);
			break;
		default:
			break;
		}
		Command_Done=1;
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(0 == value.si) { //H
				if(Data_tmp->IRange!=IRange_High){
					Data_tmp->IRange=IRange_High;
					Disp_tmp->IRange=Data_tmp->IRange;
					if(Data_tmp->CURRMODE==CR_MODE){
						Data_tmp->VRange=VRange_Low;
						Disp_tmp->VRange=Data_tmp->VRange;
					}
					Range_Change=1;
				}
			} else if(1 == value.si) { //L				
				if(Data_tmp->IRange!=IRange_Low){
					Data_tmp->IRange=IRange_Low;
					Disp_tmp->IRange=Data_tmp->IRange;
					if(Data_tmp->CURRMODE==CR_MODE){
						Data_tmp->VRange=VRange_High;
						Disp_tmp->VRange=Data_tmp->VRange;
					}
					Range_Change=1;
				}
			}			
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done ) {
			Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
			ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
			RestoreRealChan();
			if((M_num <= P_CONF_Ext)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				MenuRedrawFlag|= MENU_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			if(Range_Change) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x0;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu))
						SysRedrawFlag |= PROG_UPDATA;
					PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
				}
#if Enable_AutoLoad
				if((UTILITY.AutoLoadOffRange==0)&&(load_onoff_status)){
					PEL3000_LED_Control( LED_LOAD, 1 );
				}	
#endif
				if(Data_tmp->CURRMODE==CC_MODE)
					tx_data.ADDRH=0x01;
				else if(Data_tmp->CURRMODE==CR_MODE)
					tx_data.ADDRH=0x02;
				else if(Data_tmp->CURRMODE==CV_MODE)
					tx_data.ADDRH=0x03;
				else if(Data_tmp->CURRMODE==CP_MODE)
					tx_data.ADDRH=0x04;
				else
					tx_data.ADDRH=0x01;

				tx_data.ADDRL=0x01;
				SendTXData(&tx_data);

				tx_data.ADDRL=0x00;
				SendTXData(&tx_data);

				tx_data.ADDRH = Para_Ext_Command;
				tx_data.ADDRL = Para_Ext_Setting;
				SendTXData(&tx_data);

				/* Set Front and Rear IMON */
				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = Machine_Setting_IMON;
				SendTXData(&tx_data);
#if Enable_AutoLoad
				Prot_Setting_Process();
				if((UTILITY.AutoLoadOffRange==0)&&(load_onoff_status)) {
					OSTimeDly(5);
					Auto_Load_On();
				}
#endif

			}
		}
	}
// Code End
}

void idMODEVRANge(STR_PARSER * p)
{
	GW_TYPE value;
	p3k_send_tx_list tx_data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Memory_Str	Mem_tmp;

	char str[20];
	Data_tmp->VRange=Disp_tmp->VRange;
	UBYTE Range_Temp, Range_Change=0, Command_Done=0;
	UWORD AddCV_Max=(ptrMODEL_TYPE->CV)[3*Disp_tmp->VRange].Max;
	UWORD AddCV_Min=(ptrMODEL_TYPE->CV)[3*Disp_tmp->VRange].Min;
	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	UBYTE load_onoff_status;
	load_onoff_status = UTILITY.LOAD_CTL;
	if(Data_tmp->CURRMODE==CR_MODE){
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
			return;
	}
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(Data_tmp->VRange)
			ExportProcess(String_Data,0,0,"High",0);
		else
			ExportProcess(String_Data,0,0,"Low",0);

	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(0 == value.si) { //H
				if(Data_tmp->VRange!=VRange_High){
					Data_tmp->VRange=VRange_High;
					Disp_tmp->VRange=Data_tmp->VRange;
					Range_Change=1;
				}
			} else if(1 == value.si) { //L
				if(Data_tmp->VRange!=VRange_Low){
					Data_tmp->VRange=VRange_Low;
					Disp_tmp->VRange=Data_tmp->VRange;
					Range_Change=1;
				}
			}
			
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done ) {
			Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
			ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
			RestoreRealChan();
			if((M_num <= P_CONF_Ext)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				MenuRedrawFlag|= MENU_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			if(Range_Change) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x0;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu))
						SysRedrawFlag |= PROG_UPDATA;
					PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
				}
#if Enable_AutoLoad
				if((UTILITY.AutoLoadOffRange==0)&&(load_onoff_status)) {
					PEL3000_LED_Control( LED_LOAD, 1 );
				}
#endif
				if(Data_tmp->CURRMODE==CC_MODE)
					tx_data.ADDRH=0x01;
				else if(Data_tmp->CURRMODE==CR_MODE)
					tx_data.ADDRH=0x02;
				else if(Data_tmp->CURRMODE==CV_MODE)
					tx_data.ADDRH=0x03;
				else if(Data_tmp->CURRMODE==CP_MODE)
					tx_data.ADDRH=0x04;
				else
					tx_data.ADDRH=0x01;

				tx_data.ADDRL=0x01;
				SendTXData(&tx_data);

				tx_data.ADDRL=0x00;
				SendTXData(&tx_data);
#if Enable_AutoLoad
				if((UTILITY.AutoLoadOffRange==0)&&(load_onoff_status)) {
					OSTimeDly(5);
					Auto_Load_On();
				}
#endif
			}
		}
	}
// Code End
}

void idMODEDYNamic(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, DYN_STA_Change=0;

	p3k_send_tx_list tx_data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	char	DispScrCurrLoc_tmp,str[20];
	unsigned char return_StaDyna;
	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		switch(Data_tmp->CURRMODE) {
		case CC_MODE:
			return_StaDyna = Data_tmp->CC.STADYNA;
			break;
		case CR_MODE:
			return_StaDyna = Data_tmp->CR.STADYNA;
			break;
		case CP_MODE:
			//return_StaDyna = Data_tmp->CP.STADYNA;
			return_StaDyna = 0;
			break;
		case CV_MODE:
			return_StaDyna = 0;
			break;
		default:
			scpi_SetCommandError( p, _ERR_400_Query_error);
			return;
		}
		if(copy_SCPI_Company==SCPI_GW) {
			if (return_StaDyna==SCPI_Static_Status)
				ExportProcess(String_Data,0,0,"Static",0);
			else
				ExportProcess(String_Data,0,0,"Dynamic",0);
		} else if(copy_SCPI_Company==SCPI_KIKUSUI) {
			if (return_StaDyna==SCPI_Static_Status)
				ExportProcess(String_Data,0,0,"OFF",0);
			else
				ExportProcess(String_Data,0,0,"ON",0);
		}
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			switch(Data_tmp->CURRMODE) {
			case CC_MODE:
				Data_tmp->CC.STADYNA=value.si;
				Disp_tmp->CC.STADYNA=Data_tmp->CC.STADYNA;
				break;
			case CR_MODE:
				Data_tmp->CR.STADYNA=value.si;
				Disp_tmp->CR.STADYNA=Data_tmp->CR.STADYNA;
				break;
			//case CP_MODE:
			//	Data_tmp->CP.STADYNA=value.si;
			//	Disp_tmp->CP.STADYNA=Data_tmp->CP.STADYNA;
			//	break;
			default:
				scpi_SetCommandError( p, _ERR_138_Suffix_not_allowed);
				return;
			}
			DYN_STA_Change=1;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;


			if((M_num <= P_CONF_Ext)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
				ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				MenuRedrawFlag|= MENU_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			RestoreRealChan();
			if(DYN_STA_Change) {
#if 0 //Adam_2015_0706				
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x0;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu))
						SysRedrawFlag |= PROG_UPDATA;
					PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
				}
#endif				
				if(Data_tmp->CURRMODE==CC_MODE)
					tx_data.ADDRH=0x01;
				else if(Data_tmp->CURRMODE==CR_MODE)
					tx_data.ADDRH=0x02;
				else if(Data_tmp->CURRMODE==CV_MODE)
					tx_data.ADDRH=0x03;
				else if(Data_tmp->CURRMODE==CP_MODE)
					tx_data.ADDRH=0x04;
				else
					tx_data.ADDRH=0x01;

				tx_data.ADDRL=0x01;
				SendTXData(&tx_data);

				tx_data.ADDRL=0x00;
				SendTXData(&tx_data);
			}
		}
	}
// Code End
}

void idCURRentRECall(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingBool;

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
		
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(Disp_tmp->CC.ABSELECT)
			ExportProcess(String_Data,0,0,"1",0);
		else
			ExportProcess(String_Data,0,0,"0",0);

	} else {

		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}

		if(Command_Done) {			
			Disp_tmp->CC.ABSELECT=SettingBool;
			Data_tmp->CC.ABSELECT = Disp_tmp->CC.ABSELECT;
			//if((M_num==P_CC)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) 
				ChanRedrawFlag |= CHAN_STATUS;
			//else
			//	ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
			tx_data.ADDRH = 0x01;
			tx_data.ADDRL = 0x00;
			SendTXData(&tx_data);
		}		
	}	
// Code End
}


void idCURRentVA(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[30];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	UBYTE Mode_Change=0,Range_Change=0,Load_On_Status=0;

	ResolutionTemp=((ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Resolution);
	Precision = (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].precision;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==0) {
				Min=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Min*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Min,0,0,Precision);
			} else {
				Max=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Max*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Max,0,0,Precision);
			}
		} else {
			SettingCount = Data_tmp->CC.STA[Data_tmp->IRange].VALUE1;
			Real_Value = (double)(SettingCount * ResolutionTemp )*Para_s;
			ExportProcess(Float_Data,Real_Value,0,0,Precision);
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			Max=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Max*ResolutionTemp;
			Min=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Min*ResolutionTemp;;
			if((Real_Value > Max)||(Real_Value < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Max : (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Min;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if(Data_tmp->CURRMODE != CC_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE = CC_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CC.STADYNA!=SCPI_Static_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CC.STADYNA=SCPI_Static_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
				SoftStartDoubleCheck();	
			}
								
			Data_tmp->CC.STA[Data_tmp->IRange].VALUE1 = SettingCount;
			Disp_tmp->CC.STA[Data_tmp->IRange].VALUE1 = SettingCount;
			if((M_num==P_CC)&&(Disp_tmp->CC.STADYNA==SCPI_Static_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH=0x01;
			tx_data.ADDRL=0x10;
			SendTXData(&tx_data);

			if((!Data_tmp->UTILITY.B_ONOFF)&&(Data_tmp->CC.ABSELECT)) {
				Disp_tmp->CC.ABSELECT = Data_tmp->CC.ABSELECT = SCPI_AValue;

				tx_data.ADDRH = 0x01;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				if(Disp_tmp->CURRMODE==CC_MODE)
					ChanRedrawFlag|= CHAN_STATUS;
			}
			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
			Trig.CurrRange =6;
		}
	}
// Code End
}

void idCURRentVB(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[30];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	UBYTE Mode_Change=0,Range_Change=0,Load_On_Status=0;

	ResolutionTemp=((ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Resolution);
	Precision = (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].precision;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==0) {
				Min=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Min*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Min,0,0,Precision);
			} else {
				Max=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Max*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Max,0,0,Precision);
			}
		} else {
			SettingCount = Data_tmp->CC.STA[Data_tmp->IRange].VALUE2;
			Real_Value = (double)(SettingCount * ResolutionTemp )*Para_s;
			ExportProcess(Float_Data,Real_Value,0,0,Precision);
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			Max=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Max*ResolutionTemp;
			Min=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Min*ResolutionTemp;;
			if((Real_Value > Max)||(Real_Value < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Max : (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10].Min;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if(Data_tmp->CURRMODE != CC_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE = CC_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CC.STADYNA!=SCPI_Static_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CC.STADYNA=SCPI_Static_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
				SoftStartDoubleCheck();
			}
			
			Data_tmp->CC.STA[Data_tmp->IRange].VALUE2 = SettingCount;
			Disp_tmp->CC.STA[Data_tmp->IRange].VALUE2 = SettingCount;
			if((M_num==P_CC)&&(Disp_tmp->CC.STADYNA==SCPI_Static_Status)&&(Data_tmp->IRange==Data_tmp->IRange)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x01;
			tx_data.ADDRL=0x12;
			SendTXData(&tx_data);


			if((!Data_tmp->UTILITY.B_ONOFF)&&(!Data_tmp->CC.ABSELECT)) {
				Disp_tmp->CC.ABSELECT = Data_tmp->CC.ABSELECT = SCPI_BValue;

				tx_data.ADDRH = 0x01;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				if(Disp_tmp->CURRMODE==CC_MODE) 	ChanRedrawFlag|= CHAN_STATUS;
			}
			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End

}

void idCURRentSRATe(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	LONG SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	UWORD MaxCount, MinCount;
	char Data_Buffer[30];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	UBYTE Mode_Change=0,Range_Change=0,Load_On_Status=0;
	UBYTE *sr_range;

	ResolutionTemp = (ptrMODEL_TYPE->CC)[2+Data_tmp->IRange*10].Resolution;
	Precision = (ptrMODEL_TYPE->CC)[2+Data_tmp->IRange*10].precision;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min=(double)((ptrMODEL_TYPE->CC)[2+Data_tmp->IRange*10].Min)*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Min,0,0,Precision);
			} else if(value.si==SCPI_MAX) {
				Max=(double)(ptrMODEL_TYPE->CC)[2+Data_tmp->IRange*10].Max*ResolutionTemp;
				ExportProcess(Float_Data,Max,0,0,Precision);
			}
		} else {
			ResolutionTemp = ResolutionTemp ;
			Real_Value = (double)Data_tmp->CC.STA[Data_tmp->IRange].SLEWRATEUP*ResolutionTemp*Para_s;
			ExportProcess(Float_Data,Real_Value,0,0,Precision);
		}
	} else {		
		MaxCount=(ptrMODEL_TYPE->CC)[2+Data_tmp->IRange*10].Max ;
		MinCount=(ptrMODEL_TYPE->CC)[2+Data_tmp->IRange*10].Min ;

		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			SettingCount = SCPI_InputToStep((value.d/Para_s), ResolutionTemp);		
			if((SettingCount < MinCount)||(SettingCount>MaxCount)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			} 			
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MAX) {
				SettingCount = MaxCount;
			} else {
				SettingCount = MinCount;
			}
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if(Data_tmp->CURRMODE != CC_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE = CC_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CC.STADYNA!=SCPI_Static_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CC.STADYNA=SCPI_Static_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
			}

			Data_tmp->CC.STA[Data_tmp->IRange].SLEWRATEDN = SettingCount;
			Disp_tmp->CC.STA[Data_tmp->IRange].SLEWRATEDN = SettingCount;
			Data_tmp->CC.STA[Data_tmp->IRange].SLEWRATEUP = SettingCount;
			Disp_tmp->CC.STA[Data_tmp->IRange].SLEWRATEUP = SettingCount;
			if((M_num==P_CC)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x01;
			tx_data.ADDRL=0x52;
			SendTXData(&tx_data);
			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End
}

void idCURRentL12(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[30];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	UBYTE Mode_Change=0,Range_Change=0,Load_On_Status=0;

	ResolutionTemp=((ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Resolution);
	Precision = (ptrMODEL_TYPE->CC)[4+Data_tmp->IRange*10].precision;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
// Code Begin
	if(P3k_Chan_Data.CONF.Dyna_Level) { //If precent mode, return
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if(scpi_GetNumericSuffix(p,1)==1) { //L1==================================
		if(scpi_IsQueryCommand(p)) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					Min=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Min*ResolutionTemp*Para_s;
					ExportProcess(Float_Data,Min,0,0,Precision);
				} else if (value.si==SCPI_MAX) {
					Max=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Max*ResolutionTemp*Para_s;
					ExportProcess(Float_Data,Max,0,0,Precision);
				}
			} else {
				SettingCount = Data_tmp->CC.DYNA[Data_tmp->IRange].LEVEL1;;
				Real_Value = (double)(SettingCount * ResolutionTemp )*Para_s;
				ExportProcess(Float_Data,Real_Value,0,0,Precision);
			}
		} else {
			if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
				Real_Value = value.d / Para_s;
				Max=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Max*ResolutionTemp;
				Min=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Min*ResolutionTemp;;
				if((Real_Value > Max)||(Real_Value < Min)) {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
				SettingCount = SCPI_InputToStep(Real_Value , ResolutionTemp);
				Command_Done=1;
			} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				SettingCount = (1 == value.si) ? (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Max : (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Min;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}
			if(Command_Done==1) {
				if(Data_tmp->CURRMODE!=CC_MODE) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CURRMODE=CC_MODE;
					Mode_Change=1;
				}
				if(Data_tmp->CC.STADYNA!=SCPI_Dynamic_Status) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CC.STADYNA=SCPI_Dynamic_Status;
					Range_Change=1;
				}
				if(Mode_Change || Range_Change) {
					Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
					ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

					RestoreRealChan();
					if(M_num != Disp_tmp->CURRMODE)
						M_num = Disp_tmp->CURRMODE;
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
						ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
						DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
						MenuRedrawFlag|= MENU_CHANGE;
						if(DispMode>DispMode_BROWSE_ITEMS)
							DispMode = DispMode_BROWSE_ITEMS;
					}
					if(Mode_Change) {
						tx_data.ADDRH=0x00;
						tx_data.ADDRL=0x06;
						SendTXData(&tx_data);
					}
					if(Range_Change) {
						if(Data_tmp->CURRMODE==CC_MODE)
							tx_data.ADDRH=0x01;
						else if(Data_tmp->CURRMODE==CR_MODE)
							tx_data.ADDRH=0x02;
						else if(Data_tmp->CURRMODE==CV_MODE)
							tx_data.ADDRH=0x03;
						else
							tx_data.ADDRH=0x04;
						tx_data.ADDRL=0x00;
						SendTXData(&tx_data);
					}
					SoftStartDoubleCheck();
				}
										
				Data_tmp->CC.DYNA[Data_tmp->IRange].LEVEL1 = SettingCount;
				Disp_tmp->CC.DYNA[Data_tmp->IRange].LEVEL1 = SettingCount;
				if((M_num==P_CC)&&(Disp_tmp->CC.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					DataRedrawFlag |= PARA_CHANGE;
					Draw_Set_parameter();					
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}
				tx_data.ADDRH=0x01;
				tx_data.ADDRL=0x40;
				SendTXData(&tx_data);
				if(Load_On_Status) {
					UTILITY.LOAD_CTL=0x01;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 0;
				}
			}
		}
	} else if(scpi_GetNumericSuffix(p,1)==2) { //L2========================
		if(scpi_IsQueryCommand(p)) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					Min=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Min*ResolutionTemp*Para_s;
					ExportProcess(Float_Data,Min,0,0,Precision);
				} else if (value.si==SCPI_MAX) {
					Max=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Max*ResolutionTemp*Para_s;
					ExportProcess(Float_Data,Max,0,0,Precision);
				}
			} else {
				SettingCount = Data_tmp->CC.DYNA[Data_tmp->IRange].LEVEL2;;
				Real_Value = (double)(SettingCount * ResolutionTemp )*Para_s;
				ExportProcess(Float_Data,Real_Value,0,0,Precision);
			}
		} else {
			if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
				Real_Value = value.d / Para_s;
				Max=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+5].Max*ResolutionTemp;
				Min=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+5].Min*ResolutionTemp;;
				if((Real_Value > Max)||(Real_Value < Min)) {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
				SettingCount = SCPI_InputToStep(Real_Value , ResolutionTemp);
				Command_Done=1;
			} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				SettingCount = (1 == value.si) ? (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+5].Max : (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+5].Min;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}
			if(Command_Done==1) {
				if(Data_tmp->CURRMODE!=CC_MODE) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CURRMODE=CC_MODE;
					Mode_Change=1;
				}
				if(Data_tmp->CC.STADYNA!=SCPI_Dynamic_Status) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CC.STADYNA=SCPI_Dynamic_Status;
					Range_Change=1;
				}
				if(Mode_Change || Range_Change) {
					Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
					ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

					RestoreRealChan();
					if(M_num != Disp_tmp->CURRMODE)
						M_num = Disp_tmp->CURRMODE;
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
						ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
						DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
						MenuRedrawFlag|= MENU_CHANGE;
						if(DispMode>DispMode_BROWSE_ITEMS)
							DispMode = DispMode_BROWSE_ITEMS;
					}

					if(Mode_Change) {
						tx_data.ADDRH=0x00;
						tx_data.ADDRL=0x06;
						SendTXData(&tx_data);
					}
					if(Range_Change) {
						if(Data_tmp->CURRMODE==CC_MODE)
							tx_data.ADDRH=0x01;
						else if(Data_tmp->CURRMODE==CR_MODE)
							tx_data.ADDRH=0x02;
						else if(Data_tmp->CURRMODE==CV_MODE)
							tx_data.ADDRH=0x03;
						else if(Data_tmp->CURRMODE==CP_MODE)
							tx_data.ADDRH=0x04;
						tx_data.ADDRL=0x00;
						SendTXData(&tx_data);
					}
					SoftStartDoubleCheck();	
				}
									
			
				Data_tmp->CC.DYNA[Data_tmp->IRange].LEVEL2 = SettingCount;
				Disp_tmp->CC.DYNA[Data_tmp->IRange].LEVEL2 = SettingCount;
				if((M_num==P_CC)&&(Disp_tmp->CC.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					DataRedrawFlag |= PARA_CHANGE;
					Draw_Set_parameter();					
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				tx_data.ADDRH=0x01;
				tx_data.ADDRL=0x42;
				SendTXData(&tx_data);

				if(Load_On_Status) {
					UTILITY.LOAD_CTL=0x01;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 0;
				}
			}
		}
	}
// Code End
}

void idCURRentSET(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[30];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	UBYTE Mode_Change=0,Range_Change=0,Load_On_Status=0;

	ResolutionTemp=(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Resolution;
	Precision = (ptrMODEL_TYPE->CC)[4+Data_tmp->IRange*10].precision;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

// Code Begin
	if(P3k_Chan_Data.CONF.Dyna_Level==0) { //If value mode, return
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Min*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Min,0,0,Precision);
			} else if (value.si==SCPI_MAX) {
				Max=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Max*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Max,0,0,Precision);
			}
		} else {
			SettingCount = Data_tmp->CC.DYNA[Data_tmp->IRange].LEVEL1;;
			Real_Value = (double)(SettingCount * ResolutionTemp )*Para_s;
			ExportProcess(Float_Data,Real_Value,0,0,Precision);
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			Max=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Max*ResolutionTemp;
			Min=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Min*ResolutionTemp;;
			if((Real_Value > Max)||(Real_Value < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Max : (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Min;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CC.DYNA[Data_tmp->IRange].LEVEL1 = SettingCount;
			Disp_tmp->CC.DYNA[Disp_tmp->IRange].LEVEL1 = SettingCount;
			if(Data_tmp->CURRMODE!=CC_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CC_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CC.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CC.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
				SoftStartDoubleCheck(); 
			}								
			if((M_num==P_CC)&&(Disp_tmp->CC.STADYNA)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x01;
			tx_data.ADDRL=0x54;
			SendTXData(&tx_data);

			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End
}

void idCURRentLEVel(STR_PARSER * p)
{
	GW_TYPE value;
	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	UWORD SettingCount;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	double Max,Min,ResolutionTemp;
	ResolutionTemp=0.1;
	Min=0.0;
	Max=100.0;
// Code Begin
	if(P3k_Chan_Data.CONF.Dyna_Level==0) { //If value mode, return
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				//Min=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Max*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Min,0,0,1);
			} else if (value.si==SCPI_MAX) {
				//Max=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Min*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Max,0,0,1);
			}
		} else {
			ExportProcess(Float_Data,Disp_tmp->CC.DYNA[Disp_tmp->IRange].Level_Percent*ResolutionTemp,0,0,ceild(log10(Disp_tmp->CC.DYNA[Disp_tmp->IRange].Level_Percent*ResolutionTemp)));
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			if((value.d > Max)||(value.d < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(value.d,ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? 1000 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CC.DYNA[Data_tmp->IRange].Level_Percent=SettingCount;
			Disp_tmp->CC.DYNA[Disp_tmp->IRange].Level_Percent=SettingCount;
			if(Data_tmp->CURRMODE!=CC_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CC_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CC.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CC.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
			}

			if((M_num==P_CC)&&(Disp_tmp->CC.STADYNA)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x01;
			tx_data.ADDRL=0x54;
			SendTXData(&tx_data);

			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End
}

void idCURRentRISE(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	LONG SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	UWORD MaxCount, MinCount;
	char Data_Buffer[30];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	UBYTE Mode_Change=0,Range_Change=0,Load_On_Status=0;
	UBYTE *sr_range;

	ResolutionTemp = (ptrMODEL_TYPE->CC)[6+(Data_tmp->IRange)*10].Resolution ;
	Precision = (ptrMODEL_TYPE->CC)[6+Data_tmp->IRange*10].precision;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min=(double)((ptrMODEL_TYPE->CC)[6+(Data_tmp->IRange)*10].Min)*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Min,0,0,Precision);
			} else if (value.si==SCPI_MAX) {
				Max=(double)(ptrMODEL_TYPE->CC)[6+(Data_tmp->IRange)*10].Max*ResolutionTemp;
				ExportProcess(Float_Data,Max,0,0,Precision);
			}
		} else {
			ResolutionTemp = ResolutionTemp ;
			Real_Value = (double)Data_tmp->CC.DYNA[Data_tmp->IRange].SLEWRATEUP*ResolutionTemp*Para_s;
			ExportProcess(Float_Data,Real_Value,0,0,Precision);
		}
	} else {
		MaxCount=(ptrMODEL_TYPE->CC)[2+Data_tmp->IRange*10].Max ;
		MinCount=(ptrMODEL_TYPE->CC)[2+Data_tmp->IRange*10].Min ;
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			SettingCount = SCPI_InputToStep((value.d/Para_s), ResolutionTemp);		
			if((SettingCount < MinCount)||(SettingCount>MaxCount)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			} 			
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MAX) {
				SettingCount = MaxCount;
			} else {
				SettingCount = MinCount;
			}
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if(Data_tmp->CURRMODE != CC_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE = CC_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CC.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CC.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
			}

			Data_tmp->CC.DYNA[Data_tmp->IRange].SLEWRATEUP = SettingCount;
			Disp_tmp->CC.DYNA[Data_tmp->IRange].SLEWRATEUP = SettingCount;			
			if((M_num==P_CC)&&(Disp_tmp->CC.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x01;
			tx_data.ADDRL=0x50;
			SendTXData(&tx_data);
			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End
}

void idCURRentFALL(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	LONG SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	UWORD MaxCount, MinCount;
	char Data_Buffer[30];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	UBYTE Mode_Change=0,Range_Change=0,Load_On_Status=0;
	UBYTE *sr_range;

	ResolutionTemp = (ptrMODEL_TYPE->CC)[7+(Data_tmp->IRange)*10].Resolution ;
	Precision = (ptrMODEL_TYPE->CC)[7+Data_tmp->IRange*10].precision;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min=(double)((ptrMODEL_TYPE->CC)[7+(Data_tmp->IRange)*10].Min)*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Min,0,0,Precision);
			} else if (value.si==SCPI_MAX) {
				Max=(double)(ptrMODEL_TYPE->CC)[7+(Data_tmp->IRange)*10].Max*ResolutionTemp;
				ExportProcess(Float_Data,Max,0,0,Precision);
			}
		} else {
			ResolutionTemp = ResolutionTemp ;
			Real_Value = (double)Data_tmp->CC.DYNA[Data_tmp->IRange].SLEWRATEDN*ResolutionTemp*Para_s;
			ExportProcess(Float_Data,Real_Value,0,0,Precision);
		}

	} else {
		MaxCount=(ptrMODEL_TYPE->CC)[2+Data_tmp->IRange*10].Max ;
		MinCount=(ptrMODEL_TYPE->CC)[2+Data_tmp->IRange*10].Min ;

		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			SettingCount = SCPI_InputToStep((value.d/Para_s), ResolutionTemp);		
			if((SettingCount < MinCount)||(SettingCount>MaxCount)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			} 			
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MAX) {
				SettingCount = MaxCount;
			} else {
				SettingCount = MinCount;
			}
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if(Data_tmp->CURRMODE != CC_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE = CC_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CC.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CC.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
			}

			Data_tmp->CC.DYNA[Data_tmp->IRange].SLEWRATEDN = SettingCount;
			Disp_tmp->CC.DYNA[Data_tmp->IRange].SLEWRATEDN = SettingCount;
			Data_tmp->CC.DYNA[Data_tmp->IRange].SLEWRATEDN_RANGE = Disp_tmp->CC.DYNA[Data_tmp->IRange].SLEWRATEDN_RANGE;
			if((M_num==P_CC)&&(Disp_tmp->CC.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x01;
			tx_data.ADDRL=0x52;
			SendTXData(&tx_data);
			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End
}


void idCURRentT12(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,T1_RANGE_temp,Mode_Change=0,Range_Change=0,Load_On_Status=0;

	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp;
	ULONG cnt1;

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	ResolutionTemp = (ptrMODEL_TYPE->CC)[9].Resolution;
// Code Begin
	if(P3k_Chan_Data.CONF.Dyna_Time) { //If freq mode, return.
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if(scpi_GetNumericSuffix(p,1)==1) { //L1==================================
		if(scpi_IsQueryCommand(p)) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					Min=(double)0.00005;
					ExportProcess(Float_Data,Min,0,0,6);
				} else if (value.si==SCPI_MAX) {
					Max=(double)DyMax / 1000; //30.0;
					ExportProcess(Float_Data,Max,0,0,6);
				}
			} else {
				SettingCount = Data_tmp->CC.DYNA[Data_tmp->IRange].TIME1;
				if(Data_tmp->CC.DYNA[Data_tmp->IRange].T1_RANGE)
					Real_Value = SettingCount;
				else
					Real_Value = SettingCount * ResolutionTemp;
				Real_Value = Real_Value *0.001;
				ExportProcess(Float_Data,Real_Value,0,0,6);
			}
		} else {
			if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
				Real_Value = value.d * 1000;
				cnt1 = SCPI_InputToStep(Real_Value,ResolutionTemp);
				T1_RANGE_temp = Data_tmp->CC.DYNA[Data_tmp->IRange].T1_RANGE;
				Data_tmp->CC.DYNA[Data_tmp->IRange].T1_RANGE=0;
				if(cnt1>(ptrMODEL_TYPE->CC)[8].Max) {
					Data_tmp->CC.DYNA[Data_tmp->IRange].T1_RANGE=1;
					cnt1 /= 1000;
					if(cnt1 > DyMax) {
						scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
						Data_tmp->CC.DYNA[Data_tmp->IRange].T1_RANGE=T1_RANGE_temp;
						return;
					}
				} else {
					if(cnt1 < (ptrMODEL_TYPE->CC)[8].Min) {
						scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
						Data_tmp->CC.DYNA[Data_tmp->IRange].T1_RANGE=T1_RANGE_temp;
						return;
					}
				}
				SettingCount = cnt1;
				Command_Done=1;
			} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				SettingCount = (1 == value.si) ? DyMax : (ptrMODEL_TYPE->CC)[8].Min;
				Data_tmp->CC.DYNA[Data_tmp->IRange].T1_RANGE = value.si;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}
			if(Command_Done==1) {
				if(Data_tmp->CURRMODE!=CC_MODE) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CURRMODE=CC_MODE;
					Mode_Change=1;
				}
				if(Data_tmp->CC.STADYNA!=SCPI_Dynamic_Status) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CC.STADYNA=SCPI_Dynamic_Status;
					Range_Change=1;
				}
				if(Mode_Change || Range_Change) {
					Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
					ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

					RestoreRealChan();
					if(M_num != Disp_tmp->CURRMODE)
						M_num = Disp_tmp->CURRMODE;
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
						ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
						DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
						MenuRedrawFlag|= MENU_CHANGE;
						if(DispMode>DispMode_BROWSE_ITEMS)
							DispMode = DispMode_BROWSE_ITEMS;
					}

					if(Mode_Change) {
						tx_data.ADDRH=0x00;
						tx_data.ADDRL=0x06;
						SendTXData(&tx_data);
					}
					if(Range_Change) {
						if(Data_tmp->CURRMODE==CC_MODE)
							tx_data.ADDRH=0x01;
						else if(Data_tmp->CURRMODE==CR_MODE)
							tx_data.ADDRH=0x02;
						else if(Data_tmp->CURRMODE==CV_MODE)
							tx_data.ADDRH=0x03;
						else if(Data_tmp->CURRMODE==CP_MODE)
							tx_data.ADDRH=0x04;
						tx_data.ADDRL=0x00;
						SendTXData(&tx_data);
					}
				}
				Data_tmp->CC.DYNA[Data_tmp->IRange].TIME1 = SettingCount;
				Disp_tmp->CC.DYNA[Data_tmp->IRange].TIME1 = SettingCount;
				Disp_tmp->CC.DYNA[Data_tmp->IRange].T1_RANGE = Data_tmp->CC.DYNA[Data_tmp->IRange].T1_RANGE;

				if((M_num==P_CC)&&(Disp_tmp->CC.STADYNA)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					DataRedrawFlag |= PARA_CHANGE;
					Draw_Set_parameter();					
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				tx_data.ADDRH=0x01;
				tx_data.ADDRL=0x54;
				SendTXData(&tx_data);

				if(Load_On_Status) {
					UTILITY.LOAD_CTL=0x01;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 0;
				}
			}
		}
	} else if(scpi_GetNumericSuffix(p,1)==2) { //L2========================
		if(scpi_IsQueryCommand(p)) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					Min=(double)0.00005;
					ExportProcess(Float_Data,Min,0,0,6);
				} else if (value.si==SCPI_MAX) {
					Max=(double)DyMax / 1000; //30.0;
					ExportProcess(Float_Data,Max,0,0,1);
				}
			} else {
				SettingCount = Data_tmp->CC.DYNA[Data_tmp->IRange].TIME2;
				if(Data_tmp->CC.DYNA[Data_tmp->IRange].T2_RANGE)
					Real_Value = SettingCount;
				else
					Real_Value = SettingCount * ResolutionTemp;
				Real_Value = Real_Value *0.001;
				ExportProcess(Float_Data,Real_Value,0,0,6);
			}
		} else {
			if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
				Real_Value = value.d * 1000;
				cnt1 = SCPI_InputToStep(Real_Value,ResolutionTemp);
				T1_RANGE_temp = Data_tmp->CC.DYNA[Data_tmp->IRange].T2_RANGE;
				Data_tmp->CC.DYNA[Data_tmp->IRange].T2_RANGE=0;
				if(cnt1>(ptrMODEL_TYPE->CC)[8].Max) {
					Data_tmp->CC.DYNA[Data_tmp->IRange].T2_RANGE=1;
					cnt1 /= 1000;
					if(cnt1 > DyMax) {
						scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
						Data_tmp->CC.DYNA[Data_tmp->IRange].T2_RANGE=T1_RANGE_temp;
						return;
					}
				} else {
					if(cnt1 < (ptrMODEL_TYPE->CC)[8].Min) {
						scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
						Data_tmp->CC.DYNA[Data_tmp->IRange].T2_RANGE=T1_RANGE_temp;
						return;
					}
				}
				SettingCount = cnt1;
				Command_Done=1;
			} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				SettingCount = (1 == value.si) ? DyMax : (ptrMODEL_TYPE->CC)[8].Min;
				Data_tmp->CC.DYNA[Data_tmp->IRange].T2_RANGE = value.si;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}
			if(Command_Done==1) {
				if(Data_tmp->CURRMODE!=CC_MODE) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CURRMODE=CC_MODE;
					Mode_Change=1;
				}
				if(Data_tmp->CC.STADYNA!=SCPI_Dynamic_Status) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CC.STADYNA=SCPI_Dynamic_Status;
					Range_Change=1;
				}
				if(Mode_Change || Range_Change) {
					Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
					ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

					RestoreRealChan();
					if(M_num != Disp_tmp->CURRMODE)
						M_num = Disp_tmp->CURRMODE;
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
						ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
						DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
						MenuRedrawFlag|= MENU_CHANGE;
						if(DispMode>DispMode_BROWSE_ITEMS)
							DispMode = DispMode_BROWSE_ITEMS;
					}

					if(Mode_Change) {
						tx_data.ADDRH=0x00;
						tx_data.ADDRL=0x06;
						SendTXData(&tx_data);
					}
					if(Range_Change) {
						if(Data_tmp->CURRMODE==CC_MODE)
							tx_data.ADDRH=0x01;
						else if(Data_tmp->CURRMODE==CR_MODE)
							tx_data.ADDRH=0x02;
						else if(Data_tmp->CURRMODE==CV_MODE)
							tx_data.ADDRH=0x03;
						else if(Data_tmp->CURRMODE==CP_MODE)
							tx_data.ADDRH=0x04;
						tx_data.ADDRL=0x00;
						SendTXData(&tx_data);
					}
				}
				Data_tmp->CC.DYNA[Data_tmp->IRange].TIME2 = SettingCount;
				Disp_tmp->CC.DYNA[Data_tmp->IRange].TIME2 = SettingCount;
				Disp_tmp->CC.DYNA[Data_tmp->IRange].T2_RANGE = Data_tmp->CC.DYNA[Data_tmp->IRange].T2_RANGE;

				if((M_num==P_CC)&&(Disp_tmp->CC.STADYNA)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					DataRedrawFlag |= PARA_CHANGE;
					Draw_Set_parameter();					
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				tx_data.ADDRH=0x01;
				tx_data.ADDRL=0x54;
				SendTXData(&tx_data);

				if(Load_On_Status) {
					UTILITY.LOAD_CTL=0x01;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 0;
				}
			}
		}
	}
// Code End
}

void idCURRentFREQuency(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Precision_tmp,Load_On_Status=0;
	double Max=20000,Min=10,ResolutionTemp;

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;

// Code Begin
	if(P3k_Chan_Data.CONF.Dyna_Time==0) { //If value mode, return.
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min=(double)1.0;
				ExportProcess(Float_Data,Min,0,0,1);
			} else if (value.si==SCPI_MAX) {
				Max=(double)20000;
				ExportProcess(Float_Data,Max,0,0,1);
			}
		} else {
			switch (Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency_Range) {
			case Dyn_Freq_TimeBase_100Hz:
				ResolutionTemp=100;
				break;
			case Dyn_Freq_TimeBase_10Hz:
				ResolutionTemp =10;
				break;
			case Dyn_Freq_TimeBase_1Hz:
				ResolutionTemp=1;
				break;
			case Dyn_Freq_TimeBase_100mHz:
				ResolutionTemp=0.1;//0.1
				break;
			default:
				break;
			}
			ExportProcess(Float_Data,Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency*ResolutionTemp,0,0,1);
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			if (value.d >= 1000) { //Freq>=10k Hz
				Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_100Hz;
				ResolutionTemp=100;
			} else if(value.d >= 100) { // 100 Hz <= Freq < 10k Hz
				Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_10Hz;
				ResolutionTemp=10;
			} else if(value.d >= 10) { // 10 Hz <= Freq < 100 Hz
				Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_1Hz;
				ResolutionTemp=1;
			} else if(value.d >= 0) { // 0 Hz <= Freq < 10 Hz
				Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_100mHz;
				ResolutionTemp=0.1;
			}
			if((value.d<=Max) && (value.d>=(Min/10))) {
				Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency_Range=Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency_Range;
				Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency = SCPI_InputToStep(value.d,ResolutionTemp);
				Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency=Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency;
				Command_Done=1;
			} else {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(0 == value.si) {
				Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_100mHz;
				Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency_Range=Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency_Range;
				Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency=(UWORD)Min;
				Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency=Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency;
				Command_Done=1;
			} else if(1 == value.si) {
				Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_100Hz;
				Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency_Range=Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency_Range;
				Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency=(UWORD)Max/100;
				Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency=Data_tmp->CC.DYNA[Data_tmp->IRange].Frequency;
				Command_Done=1;
			}
			Command_Done = 1;

		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CC.DYNA[Data_tmp->IRange].Duty =Disp_tmp->CC.DYNA[Data_tmp->IRange].Duty;
			if(Data_tmp->CURRMODE!=CC_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CC_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CC.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CC.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}
				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
			}
			if((M_num==P_CC)&&(Disp_tmp->CC.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH=0x01;
			tx_data.ADDRL=0x40;
			SendTXData(&tx_data);

			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End
}

void idCURRentDUTY(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	double Min=1,Max=99,ResolutionTemp=0.1;
	UWORD SettingCount,max,min;
	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;

// Code Begin
	if(P3k_Chan_Data.CONF.Dyna_Time==0) { //If value mode, return.
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min=(double)1.0;
				ExportProcess(Float_Data,Min,0,0,1);
			} else if (value.si==SCPI_MAX) {
				Max=(double)99.0;
				ExportProcess(Float_Data,Max,0,0,1);
			}
		} else {
			ExportProcess(Float_Data,Data_tmp->CC.DYNA[Data_tmp->IRange].Duty*ResolutionTemp,0,0,1);
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {

			if((value.d > Max)||(value.d < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(value.d,ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(SCPI_MIN== value.si) {
				SettingCount =SCPI_InputToStep(Min,ResolutionTemp);
				Disp_tmp->CC.DYNA[Disp_tmp->IRange].Duty=Data_tmp->CC.DYNA[Data_tmp->IRange].Duty;
			} else if(SCPI_MAX== value.si) {
				SettingCount =SCPI_InputToStep(Max,ResolutionTemp);
				Disp_tmp->CC.DYNA[Disp_tmp->IRange].Duty=Data_tmp->CC.DYNA[Data_tmp->IRange].Duty;
			}
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CC.DYNA[Data_tmp->IRange].Duty = SettingCount;
			Disp_tmp->CC.DYNA[Disp_tmp->IRange].Duty = SettingCount;
#if 1
			min = get_DynaFreqDutyRangeLimit(P_CC);
			max = 1000 - min;
			if(Data_tmp->CC.DYNA[Data_tmp->IRange].Duty<min)Data_tmp->CC.DYNA[Data_tmp->IRange].Duty=min;
			else if(Data_tmp->CC.DYNA[Data_tmp->IRange].Duty>max)Data_tmp->CC.DYNA[Data_tmp->IRange].Duty = max;
#endif
			Disp_tmp->CC.DYNA[Data_tmp->IRange].Duty = Data_tmp->CC.DYNA[Data_tmp->IRange].Duty;
			if(Data_tmp->CURRMODE!=CC_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CC_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CC.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CC.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
			}
			if((M_num==P_CC)&&(Disp_tmp->CC.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH=0x01;
			tx_data.ADDRL=0x40;
			SendTXData(&tx_data);

			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End
}

void idCURRentCVRESPonse(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, SettingCount=0;
	p3k_send_tx_list tx_data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	char	str[20];
	unsigned char return_response;
	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

// Code Begin
	return_response = Data_tmp->CC.CXCV_RESPOSNE;
	if(scpi_IsQueryCommand(p)) {		
		if (return_response==SCPI_RESPonse_FAST)
			ExportProcess(String_Data,0,0,"Fast",0);
		else
			ExportProcess(String_Data,0,0,"Slow",0);		
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {			
			SettingCount=value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			
			if(return_response==SettingCount)return;
			Data_tmp->CC.CXCV_RESPOSNE = SettingCount;
			Disp_tmp->CC.CXCV_RESPOSNE = SettingCount;

			if((M_num <= P_CONF_Ext)&&(!PC_scriptrun)&&(!usbrun)) {
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
				ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				MenuRedrawFlag|= MENU_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}				
			tx_data.ADDRH=0x01;
			tx_data.ADDRL=0x00;
			SendTXData(&tx_data);
			
		}
	}
// Code End
}

void idRESistanceRECall(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingBool;

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
		
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(Disp_tmp->CR.ABSELECT)
			ExportProcess(String_Data,0,0,"1",0);
		else
			ExportProcess(String_Data,0,0,"0",0);

	} else {

		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}

		if(Command_Done) {			
			Disp_tmp->CR.ABSELECT=SettingBool;
			Data_tmp->CR.ABSELECT = Disp_tmp->CR.ABSELECT;
			ChanRedrawFlag |= CHAN_STATUS;
			Draw_Set_parameter();
			
			tx_data.ADDRH = 0x02;
			tx_data.ADDRL = 0x00;
			SendTXData(&tx_data);
		}		
	}	
// Code End
}


void idCONDuctanceRECall(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingBool;

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
		
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(Disp_tmp->CR.ABSELECT)
			ExportProcess(String_Data,0,0,"1",0);
		else
			ExportProcess(String_Data,0,0,"0",0);

	} else {

		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}

		if(Command_Done) {			
			Disp_tmp->CR.ABSELECT=SettingBool;
			Data_tmp->CR.ABSELECT = Disp_tmp->CR.ABSELECT;
			ChanRedrawFlag |= CHAN_STATUS;
			Draw_Set_parameter();
			tx_data.ADDRH = 0x02;
			tx_data.ADDRL = 0x00;
			SendTXData(&tx_data);
		}		
	}	
// Code End
}
void idCONDuctanceVA(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	ULONG cnt1,value_temp;
	double OHM_value,MHO_value;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;

	p3k_send_tx_list tx_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

	ResolutionTemp=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Resolution;
	MHO_value=(double)(Data_tmp->CR.STA[Data_tmp->IRange].VALUE1*ResolutionTemp)*Para_s;
	//OHM_value=(double)(1/MHO_value*1000);

	//These max and min is MHO as base unit
	Max=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max);
	Min=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min);
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		BYTE Precision;
		//if(Data_tmp->CONF.D_CR_Unit)
		Precision = (ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].precision;
		//else
		//Precision =5;
		if (copy_SCPI_Company == SCPI_GW) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					MHO_value=Min*ResolutionTemp*Para_s;
					ExportProcess(Float_Data,MHO_value,0,0,Precision);
				} else if (value.si==SCPI_MAX) {
					MHO_value=Max*ResolutionTemp*Para_s;
					ExportProcess(Float_Data,MHO_value,0,0,Precision);
				}
			} else {
				ExportProcess(Float_Data,MHO_value,0,0,Precision);
			}
		} else if(copy_SCPI_Company == SCPI_KIKUSUI) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					ExportProcess(Float_Data,((double)(Min*ResolutionTemp*Para_s)),0,0,Precision);
				} else if (value.si==SCPI_MAX) {
					ExportProcess(Float_Data,((double)(Max*ResolutionTemp*Para_s)),0,0,Precision);
				}
			} else {
				ExportProcess(Float_Data,MHO_value,0,0,Precision);
			}
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			value_temp =(ULONG)(SCPI_InputToStep(value.d,ResolutionTemp)/Para_s);

			if((value_temp<=Max) && (value_temp>=Min)) {
				SettingCount=(UWORD)value_temp;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min;
			} else if (value.si==SCPI_MAX) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max;
			}
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Disp_tmp->CR.STA[Disp_tmp->IRange].VALUE1 = SettingCount;
			Data_tmp->CR.STA[Data_tmp->IRange].VALUE1 = SettingCount;
			if(Data_tmp->CURRMODE!=CR_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CR_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CR.STADYNA!=SCPI_Static_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CR.STADYNA=SCPI_Static_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					///Draw_Set_parameter();
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
				SoftStartDoubleCheck();
			}
			
			if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Static_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x02;
			tx_data.ADDRL=0x10;
			SendTXData(&tx_data);

			if((!Data_tmp->UTILITY.B_ONOFF)&&(Data_tmp->CR.ABSELECT)) {
				Disp_tmp->CR.ABSELECT = Data_tmp->CR.ABSELECT = SCPI_AValue;

				tx_data.ADDRH = 0x02;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu))
					ChanRedrawFlag|= CHAN_STATUS;
				///Draw_Set_parameter();
			}
			
			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
			Trig.CondRange =6;
		}
	}
// Code End

}

void idCONDuctanceVB(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	ULONG cnt1,value_temp;
	double OHM_value,MHO_value;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;

	p3k_send_tx_list tx_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

	ResolutionTemp=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Resolution;
	MHO_value=(double)(Data_tmp->CR.STA[Data_tmp->IRange].VALUE2*ResolutionTemp)*Para_s;
	OHM_value=(double)(1/MHO_value*1000);

	//These max and min is MHO as base unit
	Max=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max);
	Min=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min);
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		BYTE Precision;
		Precision = (ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].precision;

		if (copy_SCPI_Company == SCPI_GW) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					MHO_value=Min*ResolutionTemp*Para_s;
					ExportProcess(Float_Data,MHO_value,0,0,Precision);
				} else if (value.si==SCPI_MAX) {
					MHO_value=Max*ResolutionTemp*Para_s;
					ExportProcess(Float_Data,MHO_value,0,0,Precision);
				}
			} else {
				ExportProcess(Float_Data,MHO_value,0,0,Precision);
			}
		} else if(copy_SCPI_Company == SCPI_KIKUSUI) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					ExportProcess(Float_Data,((double)(Min*ResolutionTemp*Para_s)),0,0,Precision);
				} else if (value.si==SCPI_MAX) {
					ExportProcess(Float_Data,((double)(Max*ResolutionTemp*Para_s)),0,0,Precision);
				}
			} else {
				ExportProcess(Float_Data,MHO_value,0,0,5);
			}
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			value_temp =(ULONG)(SCPI_InputToStep(value.d,ResolutionTemp)/Para_s);

			if((value_temp<=Max) && (value_temp>=Min)) {
				SettingCount=(UWORD)value_temp;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min;
			} else if (value.si==SCPI_MAX) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max;
			}
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Disp_tmp->CR.STA[Disp_tmp->IRange].VALUE2 = SettingCount;
			Data_tmp->CR.STA[Data_tmp->IRange].VALUE2 = SettingCount;
			if(Data_tmp->CURRMODE!=CR_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CR_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CR.STADYNA!=SCPI_Static_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CR.STADYNA=SCPI_Static_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					Draw_Set_parameter();
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
				SoftStartDoubleCheck();
			}
			
			if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Static_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x02;
			tx_data.ADDRL=0x10;
			SendTXData(&tx_data);

			if((!Data_tmp->UTILITY.B_ONOFF)&&(!Data_tmp->CR.ABSELECT)) {
				Disp_tmp->CR.ABSELECT = Data_tmp->CR.ABSELECT = SCPI_BValue;

				tx_data.ADDRH = 0x02;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				if(Disp_tmp->CURRMODE==CR_MODE)
					ChanRedrawFlag|= CHAN_STATUS;
				Draw_Set_parameter();
			}

			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End

}

void idRESistanceVA(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	ULONG cnt1,value_temp;
	double OHM_value,MHO_value;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;

	p3k_send_tx_list tx_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

	ResolutionTemp=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Resolution;
	MHO_value=(double)(Data_tmp->CR.STA[Data_tmp->IRange].VALUE1*ResolutionTemp)*Para_s;
	OHM_value=(double)(1000/MHO_value);

	//These max and min is MHO as base unit
	Max=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max);
	Min=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min);
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		BYTE Precision;
		//if(Data_tmp->CONF.D_CR_Unit)
		//Precision = (ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].precision;
		//else
		Precision =5;
		if (copy_SCPI_Company == SCPI_GW) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					MHO_value=Max*ResolutionTemp*Para_s;
					OHM_value=(double)(1000/MHO_value);
					ExportProcess(Float_Data,OHM_value,0,0,Precision);
				} else if (value.si==SCPI_MAX) {
					MHO_value=Min*ResolutionTemp*Para_s;
					OHM_value=(double)(1000/MHO_value);
#if 0					
					OHM_value = 9.9e37;
					ExportProcess(Float_Data,OHM_value,0,0,Precision);
#else
					ExportProcess(String_Data,0,0,"9.9e37",0);
#endif
				}
			} else {
				if(MHO_value==0)	{
#if 0					
					OHM_value = 9.9e37;
					ExportProcess(Float_Data,OHM_value,0,0,Precision);
#else
					ExportProcess(String_Data,0,0,"9.9e37",0);
#endif					
				}else	ExportProcess(Float_Data,OHM_value,0,0,Precision);
			}
		} else if(copy_SCPI_Company == SCPI_KIKUSUI) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					ExportProcess(Float_Data,((double)(Min*ResolutionTemp*Para_s)),0,0,Precision);
				} else if (value.si==SCPI_MAX) {
					ExportProcess(Float_Data,((double)(Max*ResolutionTemp*Para_s)),0,0,Precision);
				}
			} else {
				ExportProcess(Float_Data,MHO_value,0,0,Precision);
			}
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			MHO_value=(double)(1000/value.d/Para_s);
			value_temp =(ULONG)(SCPI_InputToStep(MHO_value,ResolutionTemp));

			if((value_temp<=Max) && (value_temp>=Min)) {
				SettingCount=(UWORD)value_temp;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max;
			} else if (value.si==SCPI_MAX) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min;
			}
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Disp_tmp->CR.STA[Disp_tmp->IRange].VALUE1 = SettingCount;
			Data_tmp->CR.STA[Data_tmp->IRange].VALUE1 = SettingCount;
			if(Data_tmp->CURRMODE!=CR_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CR_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CR.STADYNA!=SCPI_Static_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CR.STADYNA=SCPI_Static_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					Draw_Set_parameter();
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
				SoftStartDoubleCheck();
			}
			
			if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Static_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x02;
			tx_data.ADDRL=0x10;
			SendTXData(&tx_data);

			if((!Data_tmp->UTILITY.B_ONOFF)&&(Data_tmp->CR.ABSELECT)) {
				Disp_tmp->CR.ABSELECT = Data_tmp->CR.ABSELECT = SCPI_AValue;

				tx_data.ADDRH = 0x02;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu))
					ChanRedrawFlag|= CHAN_STATUS;
				Draw_Set_parameter();
			}

			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
			Trig.CondRange =6;
		}
	}
// Code End
}

void idRESistanceVB(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	ULONG cnt1,value_temp;
	double OHM_value,MHO_value;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;

	p3k_send_tx_list tx_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

	ResolutionTemp=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Resolution;
	MHO_value=(double)(Data_tmp->CR.STA[Data_tmp->IRange].VALUE2*ResolutionTemp)*Para_s;
	OHM_value=(double)(1/MHO_value*1000);

	//These max and min is MHO as base unit
	Max=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max);
	Min=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min);
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		BYTE Precision;
		Precision = 5;//(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].precision;

		if (copy_SCPI_Company == SCPI_GW) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					MHO_value=Max*ResolutionTemp*Para_s;
					OHM_value=(double)(1000/MHO_value);
					ExportProcess(Float_Data,OHM_value,0,0,Precision);
				} else if (value.si==SCPI_MAX) {
					MHO_value=Min*ResolutionTemp*Para_s;
					OHM_value=(double)(1000/MHO_value);
#if 0					
					OHM_value = 9.9e37;
					ExportProcess(Float_Data,OHM_value,0,0,Precision);
#else
					ExportProcess(String_Data,0,0,"9.9e37",0);
#endif

				}
			} else {
				if(MHO_value==0)	{
#if 0					
					OHM_value = 9.9e37;
					ExportProcess(Float_Data,OHM_value,0,0,Precision);
#else
					ExportProcess(String_Data,0,0,"9.9e37",0);
#endif					
				}else	ExportProcess(Float_Data,OHM_value,0,0,Precision);

			}
		} else if(copy_SCPI_Company == SCPI_KIKUSUI) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					ExportProcess(Float_Data,((double)(Min*ResolutionTemp*Para_s)),0,0,Precision);
				} else if (value.si==SCPI_MAX) {
					ExportProcess(Float_Data,((double)(Max*ResolutionTemp*Para_s)),0,0,Precision);
				}
			} else {
				ExportProcess(Float_Data,MHO_value,0,0,5);
			}
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			MHO_value=(double)(1000/value.d/Para_s);
			value_temp =(ULONG)(SCPI_InputToStep(MHO_value,ResolutionTemp));

			if((value_temp<=Max) && (value_temp>=Min)) {
				SettingCount=(UWORD)value_temp;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max;
			} else if (value.si==SCPI_MAX) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min;
			}
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Disp_tmp->CR.STA[Disp_tmp->IRange].VALUE2 = SettingCount;
			Data_tmp->CR.STA[Data_tmp->IRange].VALUE2 = SettingCount;
			if(Data_tmp->CURRMODE!=CR_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CR_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CR.STADYNA!=SCPI_Static_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CR.STADYNA=SCPI_Static_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					Draw_Set_parameter();
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
				SoftStartDoubleCheck();
			}
			
			if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Static_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
				Draw_Set_parameter();
			}

			tx_data.ADDRH=0x02;
			tx_data.ADDRL=0x10;
			SendTXData(&tx_data);

			if((!Data_tmp->UTILITY.B_ONOFF)&&(!Data_tmp->CR.ABSELECT)) {
				Disp_tmp->CR.ABSELECT = Data_tmp->CR.ABSELECT = SCPI_BValue;

				tx_data.ADDRH = 0x02;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				if(Disp_tmp->CURRMODE==CR_MODE)
					ChanRedrawFlag|= CHAN_STATUS;
				Draw_Set_parameter();
			}

			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End

}


void idRESistanceSRATe(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	LONG SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	UWORD MaxCount, MinCount;
	char Data_Buffer[30];
	long cnt1;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	UBYTE Mode_Change=0,Range_Change=0,Load_On_Status=0;
	UBYTE *sr_range;
	ResolutionTemp = (ptrMODEL_TYPE->CR)[2+Data_tmp->IRange*10].Resolution ;
	Precision = (ptrMODEL_TYPE->CR)[2+Data_tmp->IRange*10].precision;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min=(double)((ptrMODEL_TYPE->CR)[6+(Data_tmp->IRange)*10].Min)*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Min,0,0,Precision);
			} else if(value.si==SCPI_MAX) {
				Max=(double)((ptrMODEL_TYPE->CR)[2+Data_tmp->IRange*10].Max) * ResolutionTemp ;
				ExportProcess(Float_Data,Max,0,0,Precision);
			}
		} else {
			ResolutionTemp = ResolutionTemp ;
			Real_Value = (double)(ResolutionTemp * Data_tmp->CR.STA[Data_tmp->IRange].SLEWRATEUP)*Para_s;
			ExportProcess(Float_Data,Real_Value,0,0,Precision);
		}
	} else {
		MaxCount=(double)ptrMODEL_TYPE->CR[7+Data_tmp->IRange*10].Max;
		MinCount=(double)ptrMODEL_TYPE->CR[7+Data_tmp->IRange*10].Min;
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			SettingCount = SCPI_InputToStep((value.d/Para_s), ResolutionTemp);		
			
			if((SettingCount < MinCount)||(SettingCount>MaxCount)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;

		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {

			if (value.si==SCPI_MAX) {
				SettingCount = MaxCount;
				SettingCount = SettingCount/ Para_s;
			} else {
				SettingCount = MinCount ;
			}
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if(Data_tmp->CURRMODE != CR_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE = CR_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CR.STADYNA!=SCPI_Static_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CR.STADYNA=SCPI_Static_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					Draw_Set_parameter();
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
			}

			Data_tmp->CR.STA[Data_tmp->IRange].SLEWRATEUP = (UWORD)SettingCount;
			Disp_tmp->CR.STA[Data_tmp->IRange].SLEWRATEUP = (UWORD)SettingCount;
			if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Static_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH=0x02;
			tx_data.ADDRL=0x50;
			SendTXData(&tx_data);
			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End
}

void idCONDuctanceL12(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	ULONG cnt1,value_temp;
	double OHM_value,MHO_value;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;

	p3k_send_tx_list tx_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

	ResolutionTemp=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Resolution;
	if(scpi_GetNumericSuffix(p,1)==1) //L1
		MHO_value=(double)(Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL1*ResolutionTemp)*Para_s;
	else
		MHO_value=(double)(Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL2*ResolutionTemp)*Para_s;
	OHM_value=(double)(1/MHO_value*1000);

	//These max and min is MHO as base unit
	Max=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Max);
	Min=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Min);
// Code Begin
	if (Data_tmp->CONF.Dyna_Level) { //if percent mode, return
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	BYTE Precision;
	Precision = (ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].precision;

	if(scpi_GetNumericSuffix(p,1)==1) { //L1==================================
		if(scpi_IsQueryCommand(p)) {
			if (copy_SCPI_Company == SCPI_GW) {
				if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
					if(value.si==SCPI_MIN) {
						MHO_value=Min*ResolutionTemp*Para_s;
						ExportProcess(Float_Data,MHO_value,0,0,Precision);
					} else if (value.si==SCPI_MAX) {
						MHO_value=Max*ResolutionTemp*Para_s;
						ExportProcess(Float_Data,MHO_value,0,0,Precision);
					}
				} else {
					ExportProcess(Float_Data,MHO_value,0,0,Precision);
				}
			} else if(copy_SCPI_Company == SCPI_KIKUSUI) {
				if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
					if(value.si==SCPI_MIN) {
						ExportProcess(Float_Data,((double)(Min*ResolutionTemp*Para_s)),0,0,Precision);
					} else if (value.si==SCPI_MAX) {
						ExportProcess(Float_Data,((double)(Max*ResolutionTemp*Para_s)),0,0,Precision);
					}
				} else {
					ExportProcess(Float_Data,MHO_value,0,0,Precision);
				}
			}
		} else {
			if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
				value_temp =(ULONG)(SCPI_InputToStep(value.d,ResolutionTemp)/Para_s);

				if((value_temp<=Max) && (value_temp>=Min)) {
					SettingCount=(UWORD)value_temp;
					Command_Done = 1;
				} else {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
				Command_Done=1;
			} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min;
				} else if (value.si==SCPI_MAX) {
					SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max;
				}
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}
			if(Command_Done==1) {
				Disp_tmp->CR.DYNA[Disp_tmp->IRange].LEVEL1 = SettingCount;
				Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL1 = SettingCount;
				if(Data_tmp->CURRMODE!=CR_MODE) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CURRMODE=CR_MODE;
					Mode_Change=1;
				}
				if(Data_tmp->CR.STADYNA!=SCPI_Dynamic_Status) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CR.STADYNA=SCPI_Dynamic_Status;
					Range_Change=1;
				}
				if(Mode_Change || Range_Change) {
					Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
					ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
					RestoreRealChan();
					if(M_num != Disp_tmp->CURRMODE)
						M_num = Disp_tmp->CURRMODE;
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
						ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
						DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
						MenuRedrawFlag|= MENU_CHANGE;
						Draw_Set_parameter();
						if(DispMode>DispMode_BROWSE_ITEMS)
							DispMode = DispMode_BROWSE_ITEMS;
					}
					if(Mode_Change) {
						tx_data.ADDRH=0x00;
						tx_data.ADDRL=0x06;
						SendTXData(&tx_data);
					}
					if(Range_Change) {
						if(Data_tmp->CURRMODE==CC_MODE)
							tx_data.ADDRH=0x01;
						else if(Data_tmp->CURRMODE==CR_MODE)
							tx_data.ADDRH=0x02;
						else if(Data_tmp->CURRMODE==CV_MODE)
							tx_data.ADDRH=0x03;
						else if(Data_tmp->CURRMODE==CP_MODE)
							tx_data.ADDRH=0x04;
						tx_data.ADDRL=0x00;
						SendTXData(&tx_data);
					}
					SoftStartDoubleCheck();
				}
				
				if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					DataRedrawFlag |= PARA_CHANGE;
					Draw_Set_parameter();
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				tx_data.ADDRH=0x02;
				tx_data.ADDRL=0x10;
				SendTXData(&tx_data);

				if((!Data_tmp->UTILITY.B_ONOFF)&&(Data_tmp->CR.ABSELECT)) {
					Disp_tmp->CR.ABSELECT = Data_tmp->CR.ABSELECT = SCPI_AValue;

					tx_data.ADDRH = 0x02;
					tx_data.ADDRL = 0x00;
					SendTXData(&tx_data);
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu))
						ChanRedrawFlag|= CHAN_STATUS;
					Draw_Set_parameter();
				}

				if(Load_On_Status) {
					UTILITY.LOAD_CTL=0x01;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 0;
				}
			}
		}
	} else if(scpi_GetNumericSuffix(p,1)==2) { //L2========================
		if(scpi_IsQueryCommand(p)) {
			if (copy_SCPI_Company == SCPI_GW) {
				if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
					if(value.si==SCPI_MIN) {
						MHO_value=Min*ResolutionTemp*Para_s;
						ExportProcess(Float_Data,MHO_value,0,0,Precision);
					} else if (value.si==SCPI_MAX) {
						MHO_value=Max*ResolutionTemp*Para_s;
						ExportProcess(Float_Data,MHO_value,0,0,Precision);
					}
				} else {
					ExportProcess(Float_Data,MHO_value,0,0,Precision);
				}
			} else if(copy_SCPI_Company == SCPI_KIKUSUI) {
				if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
					if(value.si==SCPI_MIN) {
						ExportProcess(Float_Data,((double)(Min*ResolutionTemp*Para_s)),0,0,0);
					} else if (value.si==SCPI_MAX) {
						ExportProcess(Float_Data,((double)(Max*ResolutionTemp*Para_s)),0,0,0);
					}
				} else {
					ExportProcess(Float_Data,MHO_value,0,0,5);
				}
			}
		} else {
			if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
				value_temp =(ULONG)(SCPI_InputToStep(value.d,ResolutionTemp)/Para_s);
				if((value_temp<=Max) && (value_temp>=Min)) {
					SettingCount=(UWORD)value_temp;
					Command_Done = 1;
				} else {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
				Command_Done=1;
			} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min;
				} else if (value.si==SCPI_MAX) {
					SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max;
				}
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}
			if(Command_Done==1) {
				Disp_tmp->CR.DYNA[Disp_tmp->IRange].LEVEL2 = SettingCount;
				Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL2 = SettingCount;
				if(Data_tmp->CURRMODE!=CR_MODE) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CURRMODE=CR_MODE;
					Mode_Change=1;
				}
				if(Data_tmp->CR.STADYNA!=SCPI_Dynamic_Status) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CR.STADYNA=SCPI_Dynamic_Status;
					Range_Change=1;
				}
				if(Mode_Change || Range_Change) {
					Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
					ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

					RestoreRealChan();
					if(M_num != Disp_tmp->CURRMODE)
						M_num = Disp_tmp->CURRMODE;
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
						ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
						DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
						MenuRedrawFlag|= MENU_CHANGE;
						Draw_Set_parameter();
						if(DispMode>DispMode_BROWSE_ITEMS)
							DispMode = DispMode_BROWSE_ITEMS;
					}
					if(Mode_Change) {
						tx_data.ADDRH=0x00;
						tx_data.ADDRL=0x06;
						SendTXData(&tx_data);
					}
					if(Range_Change) {
						if(Data_tmp->CURRMODE==CC_MODE)
							tx_data.ADDRH=0x01;
						else if(Data_tmp->CURRMODE==CR_MODE)
							tx_data.ADDRH=0x02;
						else if(Data_tmp->CURRMODE==CV_MODE)
							tx_data.ADDRH=0x03;
						else if(Data_tmp->CURRMODE==CP_MODE)
							tx_data.ADDRH=0x04;
						tx_data.ADDRL=0x00;
						SendTXData(&tx_data);
					}
				}
				if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					DataRedrawFlag |= PARA_CHANGE;
					Draw_Set_parameter();
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}
				tx_data.ADDRH=0x02;
				tx_data.ADDRL=0x10;
				SendTXData(&tx_data);
				if((!Data_tmp->UTILITY.B_ONOFF)&&(Data_tmp->CR.ABSELECT)) {
					Disp_tmp->CR.ABSELECT = Data_tmp->CR.ABSELECT = SCPI_AValue;

					tx_data.ADDRH = 0x02;
					tx_data.ADDRL = 0x00;
					SendTXData(&tx_data);
					if(!SCPI_Freeze_menu)
						ChanRedrawFlag|= CHAN_STATUS;
					Draw_Set_parameter();
				}

				if(Load_On_Status) {
					UTILITY.LOAD_CTL=0x01;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 0;
				}
			}
		}
	}
// Code End

}

void idCONDuctanceSET(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	ULONG cnt1,value_temp;
	double OHM_value,MHO_value;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;

	p3k_send_tx_list tx_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

	ResolutionTemp=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Resolution;
	MHO_value=(double)(Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL1*ResolutionTemp)*Para_s;
	OHM_value=(double)(1/MHO_value*1000);

	//These max and min is MHO as base unit
	Max=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Max);
	Min=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Min);
// Code Begin
	if (Data_tmp->CONF.Dyna_Level==0) { //if value mode, return
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if(scpi_IsQueryCommand(p)) {
		BYTE Precision;
		Precision = (ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].precision;
		if (copy_SCPI_Company == SCPI_GW) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					MHO_value=Min*ResolutionTemp*Para_s;
					ExportProcess(Float_Data,MHO_value,0,0,Precision);
				} else if (value.si==SCPI_MAX) {
					MHO_value=Max*ResolutionTemp*Para_s;
					ExportProcess(Float_Data,MHO_value,0,0,Precision);
				}
			} else {
				ExportProcess(Float_Data,MHO_value,0,0,Precision);
			}
		} else if(copy_SCPI_Company == SCPI_KIKUSUI) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					ExportProcess(Float_Data,((double)(Min*ResolutionTemp*Para_s)),0,0,0);
				} else if (value.si==SCPI_MAX) {
					ExportProcess(Float_Data,((double)(Max*ResolutionTemp*Para_s)),0,0,0);
				}
			} else {
				ExportProcess(Float_Data,MHO_value,0,0,5);
			}
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			value_temp =(ULONG)(SCPI_InputToStep(value.d,ResolutionTemp)/Para_s);
			if((value_temp<=Max) && (value_temp>=Min)) {
				SettingCount=(UWORD)value_temp;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min;
			} else if (value.si==SCPI_MAX) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max;
			}
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Disp_tmp->CR.DYNA[Disp_tmp->IRange].LEVEL1 = SettingCount;
			Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL1 = SettingCount;
			if(Data_tmp->CURRMODE!=CR_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CR_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CR.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CR.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					Draw_Set_parameter();
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
				SoftStartDoubleCheck();
			}
			
			if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x02;
			tx_data.ADDRL=0x10;
			SendTXData(&tx_data);

			if((!Data_tmp->UTILITY.B_ONOFF)&&(Data_tmp->CR.ABSELECT)) {
				Disp_tmp->CR.ABSELECT = Data_tmp->CR.ABSELECT = SCPI_AValue;

				tx_data.ADDRH = 0x02;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu))
					ChanRedrawFlag|= CHAN_STATUS;
				Draw_Set_parameter();
			}

			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End

}


void idRESistanceL12(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	ULONG cnt1,value_temp;
	double OHM_value,MHO_value;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;

	p3k_send_tx_list tx_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

	ResolutionTemp=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Resolution;
	if(scpi_GetNumericSuffix(p,1)==1) //L1
		MHO_value=(double)(Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL1*ResolutionTemp)*Para_s;
	else
		MHO_value=(double)(Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL2*ResolutionTemp)*Para_s;
	OHM_value=(double)(1/MHO_value*1000);

	//These max and min is MHO as base unit
	Max=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Max);
	Min=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Min);
// Code Begin
	if (Data_tmp->CONF.Dyna_Level) { //if percent mode, return
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	BYTE Precision;
	Precision = 5;//(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].precision;

	if(scpi_GetNumericSuffix(p,1)==1) { //L1==================================
		if(scpi_IsQueryCommand(p)) {
			if (copy_SCPI_Company == SCPI_GW) {
				if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
					if(value.si==SCPI_MIN) {
						MHO_value=Max*ResolutionTemp*Para_s;
						OHM_value=(double)(1000/MHO_value);
						ExportProcess(Float_Data,OHM_value,0,0,Precision);
					} else if (value.si==SCPI_MAX) {
						MHO_value=Min*ResolutionTemp*Para_s;
						OHM_value=(double)(1000/MHO_value);
#if 0					
						OHM_value = 9.9e37;
						ExportProcess(Float_Data,OHM_value,0,0,Precision);
#else
						ExportProcess(String_Data,0,0,"9.9e37",0);
#endif

					}
				} else {
					if(MHO_value==0)	{
#if 0					
						OHM_value = 9.9e37;
						ExportProcess(Float_Data,OHM_value,0,0,Precision);
#else
						ExportProcess(String_Data,0,0,"9.9e37",0);
#endif					
					}else	ExportProcess(Float_Data,OHM_value,0,0,Precision);

				}
			} else if(copy_SCPI_Company == SCPI_KIKUSUI) {
				if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
					if(value.si==SCPI_MIN) {
						ExportProcess(Float_Data,((double)(Min*ResolutionTemp*Para_s)),0,0,Precision);
					} else if (value.si==SCPI_MAX) {
						ExportProcess(Float_Data,((double)(Max*ResolutionTemp*Para_s)),0,0,Precision);
					}
				} else {
					ExportProcess(Float_Data,MHO_value,0,0,Precision);
				}
			}
		} else {
			if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
				MHO_value=(double)(1000/value.d/Para_s);
				value_temp =(ULONG)(SCPI_InputToStep(MHO_value,ResolutionTemp));

				if((value_temp<=Max) && (value_temp>=Min)) {
					SettingCount=(UWORD)value_temp;
					Command_Done = 1;
				} else {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
				Command_Done=1;
			} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max;
				} else if (value.si==SCPI_MAX) {
					SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min;
				}
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}
			if(Command_Done==1) {
				Disp_tmp->CR.DYNA[Disp_tmp->IRange].LEVEL1 = SettingCount;
				Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL1 = SettingCount;
				if(Data_tmp->CURRMODE!=CR_MODE) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CURRMODE=CR_MODE;
					Mode_Change=1;
				}
				if(Data_tmp->CR.STADYNA!=SCPI_Dynamic_Status) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CR.STADYNA=SCPI_Dynamic_Status;
					Range_Change=1;
				}
				if(Mode_Change || Range_Change) {
					Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
					ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
					RestoreRealChan();
					if(M_num != Disp_tmp->CURRMODE)
						M_num = Disp_tmp->CURRMODE;
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
						ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
						DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
						MenuRedrawFlag|= MENU_CHANGE;
						Draw_Set_parameter();
						if(DispMode>DispMode_BROWSE_ITEMS)
							DispMode = DispMode_BROWSE_ITEMS;
					}
					if(Mode_Change) {
						tx_data.ADDRH=0x00;
						tx_data.ADDRL=0x06;
						SendTXData(&tx_data);
					}
					if(Range_Change) {
						if(Data_tmp->CURRMODE==CC_MODE)
							tx_data.ADDRH=0x01;
						else if(Data_tmp->CURRMODE==CR_MODE)
							tx_data.ADDRH=0x02;
						else if(Data_tmp->CURRMODE==CV_MODE)
							tx_data.ADDRH=0x03;
						else if(Data_tmp->CURRMODE==CP_MODE)
							tx_data.ADDRH=0x04;
						tx_data.ADDRL=0x00;
						SendTXData(&tx_data);
					}
					SoftStartDoubleCheck();
				}
				
				if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					DataRedrawFlag |= PARA_CHANGE;
					Draw_Set_parameter();
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				tx_data.ADDRH=0x02;
				tx_data.ADDRL=0x10;
				SendTXData(&tx_data);

				if((!Data_tmp->UTILITY.B_ONOFF)&&(Data_tmp->CR.ABSELECT)) {
					Disp_tmp->CR.ABSELECT = Data_tmp->CR.ABSELECT = SCPI_AValue;

					tx_data.ADDRH = 0x02;
					tx_data.ADDRL = 0x00;
					SendTXData(&tx_data);
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu))
						ChanRedrawFlag|= CHAN_STATUS;
					Draw_Set_parameter();
				}

				if(Load_On_Status) {
					UTILITY.LOAD_CTL=0x01;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 0;
				}
			}
		}
	} else if(scpi_GetNumericSuffix(p,1)==2) { //L2========================
		if(scpi_IsQueryCommand(p)) {
			if (copy_SCPI_Company == SCPI_GW) {
				if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
					if(value.si==SCPI_MIN) {
						MHO_value=Max*ResolutionTemp*Para_s;
						OHM_value=(double)(1000/MHO_value);
						ExportProcess(Float_Data,OHM_value,0,0,Precision);
					} else if (value.si==SCPI_MAX) {
						MHO_value=Min*ResolutionTemp*Para_s;
						OHM_value=(double)(1000/MHO_value);
#if 0					
						OHM_value = 9.9e37;
						ExportProcess(Float_Data,OHM_value,0,0,Precision);
#else
						ExportProcess(String_Data,0,0,"9.9e37",0);
#endif

					}
				} else {
					if(MHO_value==0)	{
#if 0					
						OHM_value = 9.9e37;
						ExportProcess(Float_Data,OHM_value,0,0,Precision);
#else
						ExportProcess(String_Data,0,0,"9.9e37",0);
#endif					
					}else	ExportProcess(Float_Data,OHM_value,0,0,Precision);

				}
			} else if(copy_SCPI_Company == SCPI_KIKUSUI) {
				if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
					if(value.si==SCPI_MIN) {
						ExportProcess(Float_Data,((double)(Min*ResolutionTemp*Para_s)),0,0,0);
					} else if (value.si==SCPI_MAX) {
						ExportProcess(Float_Data,((double)(Max*ResolutionTemp*Para_s)),0,0,0);
					}
				} else {
					ExportProcess(Float_Data,MHO_value,0,0,5);
				}
			}
		} else {
			if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
				MHO_value=(double)(1000/value.d/Para_s);
				value_temp =(ULONG)(SCPI_InputToStep(MHO_value,ResolutionTemp));
				if((value_temp<=Max) && (value_temp>=Min)) {
					SettingCount=(UWORD)value_temp;
					Command_Done = 1;
				} else {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
				Command_Done=1;
			} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max;
				} else if (value.si==SCPI_MAX) {
					SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min;
				}
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}
			if(Command_Done==1) {
				Disp_tmp->CR.DYNA[Disp_tmp->IRange].LEVEL2 = SettingCount;
				Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL2 = SettingCount;
				if(Data_tmp->CURRMODE!=CR_MODE) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CURRMODE=CR_MODE;
					Mode_Change=1;
				}
				if(Data_tmp->CR.STADYNA!=SCPI_Dynamic_Status) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CR.STADYNA=SCPI_Dynamic_Status;
					Range_Change=1;
				}
				if(Mode_Change || Range_Change) {
					Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
					ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

					RestoreRealChan();
					if(M_num != Disp_tmp->CURRMODE)
						M_num = Disp_tmp->CURRMODE;
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
						ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
						DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
						MenuRedrawFlag|= MENU_CHANGE;
						Draw_Set_parameter();
						if(DispMode>DispMode_BROWSE_ITEMS)
							DispMode = DispMode_BROWSE_ITEMS;
					}
					if(Mode_Change) {
						tx_data.ADDRH=0x00;
						tx_data.ADDRL=0x06;
						SendTXData(&tx_data);
					}
					if(Range_Change) {
						if(Data_tmp->CURRMODE==CC_MODE)
							tx_data.ADDRH=0x01;
						else if(Data_tmp->CURRMODE==CR_MODE)
							tx_data.ADDRH=0x02;
						else if(Data_tmp->CURRMODE==CV_MODE)
							tx_data.ADDRH=0x03;
						else if(Data_tmp->CURRMODE==CP_MODE)
							tx_data.ADDRH=0x04;
						tx_data.ADDRL=0x00;
						SendTXData(&tx_data);
					}
				}
				if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					DataRedrawFlag |= PARA_CHANGE;
					Draw_Set_parameter();
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}
				tx_data.ADDRH=0x02;
				tx_data.ADDRL=0x10;
				SendTXData(&tx_data);
				if((!Data_tmp->UTILITY.B_ONOFF)&&(Data_tmp->CR.ABSELECT)) {
					Disp_tmp->CR.ABSELECT = Data_tmp->CR.ABSELECT = SCPI_AValue;

					tx_data.ADDRH = 0x02;
					tx_data.ADDRL = 0x00;
					SendTXData(&tx_data);
					if(!SCPI_Freeze_menu)
						ChanRedrawFlag|= CHAN_STATUS;
					Draw_Set_parameter();
				}

				if(Load_On_Status) {
					UTILITY.LOAD_CTL=0x01;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 0;
				}
			}
		}
	}
// Code End
}

void idRESistanceSET(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	ULONG cnt1,value_temp;
	double OHM_value,MHO_value;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;

	p3k_send_tx_list tx_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

	ResolutionTemp=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Resolution;
	MHO_value=(double)(Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL1*ResolutionTemp)*Para_s;
	OHM_value=(double)(1/MHO_value*1000);

	//These max and min is MHO as base unit
	Max=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Max);
	Min=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Min);
// Code Begin
	if (Data_tmp->CONF.Dyna_Level==0) { //if value mode, return
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if(scpi_IsQueryCommand(p)) {
		BYTE Precision;
		Precision = 5;//(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].precision;
		if (copy_SCPI_Company == SCPI_GW) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					MHO_value=Max*ResolutionTemp*Para_s;
					OHM_value=(double)(1000/MHO_value);
					ExportProcess(Float_Data,OHM_value,0,0,Precision);
				} else if (value.si==SCPI_MAX) {
					MHO_value=Min*ResolutionTemp*Para_s;
					OHM_value=(double)(1000/MHO_value);
#if 0					
					OHM_value = 9.9e37;
					ExportProcess(Float_Data,OHM_value,0,0,Precision);
#else
					ExportProcess(String_Data,0,0,"9.9e37",0);
#endif

				}
			} else {
				if(MHO_value==0)	{
#if 0					
					OHM_value = 9.9e37;
					ExportProcess(Float_Data,OHM_value,0,0,Precision);
#else
					ExportProcess(String_Data,0,0,"9.9e37",0);
#endif					
				}else	ExportProcess(Float_Data,OHM_value,0,0,Precision);

			}
		} else if(copy_SCPI_Company == SCPI_KIKUSUI) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					ExportProcess(Float_Data,((double)(Min*ResolutionTemp*Para_s)),0,0,0);
				} else if (value.si==SCPI_MAX) {
					ExportProcess(Float_Data,((double)(Max*ResolutionTemp*Para_s)),0,0,0);
				}
			} else {
				ExportProcess(Float_Data,MHO_value,0,0,5);
			}
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			MHO_value=(double)(1000/value.d/Para_s);
			value_temp =(ULONG)(SCPI_InputToStep(MHO_value,ResolutionTemp));
			if((value_temp<=Max) && (value_temp>=Min)) {
				SettingCount=(UWORD)value_temp;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max;
			} else if (value.si==SCPI_MAX) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min;
			}
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Disp_tmp->CR.DYNA[Disp_tmp->IRange].LEVEL1 = SettingCount;
			Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL1 = SettingCount;
			if(Data_tmp->CURRMODE!=CR_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CR_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CR.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CR.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					Draw_Set_parameter();
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
				SoftStartDoubleCheck();
			}
			
			if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x02;
			tx_data.ADDRL=0x10;
			SendTXData(&tx_data);

			if((!Data_tmp->UTILITY.B_ONOFF)&&(Data_tmp->CR.ABSELECT)) {
				Disp_tmp->CR.ABSELECT = Data_tmp->CR.ABSELECT = SCPI_AValue;

				tx_data.ADDRH = 0x02;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu))
					ChanRedrawFlag|= CHAN_STATUS;
				Draw_Set_parameter();
			}

			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End
}


void idRESistanceLEVel(STR_PARSER * p)
{
	GW_TYPE value;
	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	UWORD SettingCount;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	double Max,Min,ResolutionTemp;
	ResolutionTemp=0.1;
	Min=0.0;
	Max=100.0;
// Code Begin
	if (Data_tmp->CONF.Dyna_Level==0) { //if value mode, return
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				ExportProcess(Float_Data,Min,0,0,1);
			} else if (value.si==SCPI_MAX) {
				ExportProcess(Float_Data,Max,0,0,1);
			}
		} else {
			ExportProcess(Float_Data,Disp_tmp->CR.DYNA[Disp_tmp->IRange].Level_Percent*ResolutionTemp,0,0,ceild(log10(Disp_tmp->CC.DYNA[Disp_tmp->IRange].Level_Percent*ResolutionTemp)));
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			if((value.d > Max)||(value.d < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(value.d,ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? 1000 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CR.DYNA[Data_tmp->IRange].Level_Percent=SettingCount;
			Disp_tmp->CR.DYNA[Disp_tmp->IRange].Level_Percent=SettingCount;
			if(Data_tmp->CURRMODE != CR_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE = CR_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CR.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CR.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}
				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
			}
			if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x02;
			tx_data.ADDRL=0x50;
			SendTXData(&tx_data);
			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End
}

void idRESistanceRISE(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	LONG SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	UWORD MaxCount, MinCount;
	char Data_Buffer[30];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	UBYTE Mode_Change=0,Range_Change=0,Load_On_Status=0;
	UBYTE *sr_range;
	ResolutionTemp = (ptrMODEL_TYPE->CR)[6+Data_tmp->IRange*10].Resolution ;
	Precision = (ptrMODEL_TYPE->CR)[6+Data_tmp->IRange*10].precision;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min=(double)((ptrMODEL_TYPE->CR)[2+Data_tmp->IRange*10].Min) * ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Min,0,0,Precision);
			} else if(value.si==SCPI_MAX) {
				Max=(double)((ptrMODEL_TYPE->CR)[2+Data_tmp->IRange*10].Max) * ResolutionTemp ;
				ExportProcess(Float_Data,Max,0,0,Precision);
			}
		} else {
			ResolutionTemp = ResolutionTemp ;
			Real_Value = (double)(ResolutionTemp * Data_tmp->CR.DYNA[Data_tmp->IRange].SLEWRATEUP)*Para_s;
			ExportProcess(Float_Data,Real_Value,0,0,Precision);
		}
	} else {

		MaxCount=ptrMODEL_TYPE->CR[7+Data_tmp->IRange*10].Max;
		MinCount=ptrMODEL_TYPE->CR[7+Data_tmp->IRange*10].Min;
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			SettingCount = SCPI_InputToStep((value.d/Para_s), ResolutionTemp);		
			
			if((SettingCount < MinCount)||(SettingCount>MaxCount)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;

		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {

			if (value.si==SCPI_MAX) {
				SettingCount = MaxCount;
				SettingCount = SettingCount/ Para_s;
			} else {
				SettingCount = MinCount ;
			}
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if(Data_tmp->CURRMODE != CR_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE = CR_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CR.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CR.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
			}

			Data_tmp->CR.DYNA[Data_tmp->IRange].SLEWRATEUP = (UWORD)SettingCount;
			Disp_tmp->CR.DYNA[Data_tmp->IRange].SLEWRATEUP = (UWORD)SettingCount;			
			if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x02;
			tx_data.ADDRL=0x50;
			SendTXData(&tx_data);
			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End

}

void idRESistanceFALL(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	LONG SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	UWORD MaxCount, MinCount;
	char Data_Buffer[30];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	UBYTE Mode_Change=0,Range_Change=0,Load_On_Status=0;
	ResolutionTemp = (ptrMODEL_TYPE->CR)[6+Data_tmp->IRange*10].Resolution ;
	Precision = (ptrMODEL_TYPE->CR)[6+Data_tmp->IRange*10].precision;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min=(double)((ptrMODEL_TYPE->CR)[2+Data_tmp->IRange*10].Min) * ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Min,0,0,Precision);
			} else if(value.si==SCPI_MAX) {
				Max=(double)((ptrMODEL_TYPE->CR)[2+Data_tmp->IRange*10].Max) * ResolutionTemp ;
				ExportProcess(Float_Data,Max,0,0,Precision);
			}
		} else {
			ResolutionTemp = ResolutionTemp ;
			Real_Value = (double)(ResolutionTemp * Data_tmp->CR.DYNA[Data_tmp->IRange].SLEWRATEDN)*Para_s;
			ExportProcess(Float_Data,Real_Value,0,0,Precision);
		}
	} else {
		MaxCount=(double)ptrMODEL_TYPE->CR[7+Data_tmp->IRange*10].Max;
		MinCount=(double)ptrMODEL_TYPE->CR[7+Data_tmp->IRange*10].Min;
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			SettingCount = SCPI_InputToStep((value.d/Para_s), ResolutionTemp);		
			
			if((SettingCount < MinCount)||(SettingCount>MaxCount)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;

		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {

			if (value.si==SCPI_MAX) {
				SettingCount = MaxCount;
				SettingCount = SettingCount/ Para_s;
			} else {
				SettingCount = MinCount ;
			}
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if(Data_tmp->CURRMODE != CR_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE = CR_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CR.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CR.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
			}

			Data_tmp->CR.DYNA[Data_tmp->IRange].SLEWRATEDN = (UWORD)SettingCount;
			Disp_tmp->CR.DYNA[Data_tmp->IRange].SLEWRATEDN = (UWORD)SettingCount;			
			if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x02;
			tx_data.ADDRL=0x50;
			SendTXData(&tx_data);
			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End	
}

void idRESistanceT12(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,T1_RANGE_temp,Mode_Change=0,Range_Change=0,Load_On_Status=0;

	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp;
	ULONG cnt1;

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	ResolutionTemp = (ptrMODEL_TYPE->CR)[8].Resolution;
// Code Begin
	if(P3k_Chan_Data.CONF.Dyna_Time) { //If freq mode, return.
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}

	if(scpi_GetNumericSuffix(p,1)==1) { //L1==================================
		if(scpi_IsQueryCommand(p)) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					Min=(double)0.00005;
					ExportProcess(Float_Data,Min,0,0,6);
				} else if (value.si==SCPI_MAX) {
					Max=(double)DyMax/1000;//30.0;
					ExportProcess(Float_Data,Max,0,0,6);
				}
			} else {
				SettingCount = Data_tmp->CR.DYNA[Data_tmp->IRange].TIME1;
				if(Data_tmp->CR.DYNA[Data_tmp->IRange].T1_RANGE)
					Real_Value = SettingCount;
				else
					Real_Value = SettingCount * ResolutionTemp;
				Real_Value = Real_Value *0.001;
				ExportProcess(Float_Data,Real_Value,0,0,6);
			}
		} else {

			if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
				Real_Value = value.d * 1000;
				cnt1 = SCPI_InputToStep(Real_Value,ResolutionTemp);
				T1_RANGE_temp = Data_tmp->CR.DYNA[Data_tmp->IRange].T1_RANGE;
				Data_tmp->CR.DYNA[Data_tmp->IRange].T1_RANGE=0;
				if(cnt1>(ptrMODEL_TYPE->CR)[8].Max) {
					Data_tmp->CR.DYNA[Data_tmp->IRange].T1_RANGE=1;
					cnt1 /= 1000;
					if(cnt1 > DyMax) {
						scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
						Data_tmp->CR.DYNA[Data_tmp->IRange].T1_RANGE=T1_RANGE_temp;
						return;
					}
				} else {
					if(cnt1 < (ptrMODEL_TYPE->CR)[8].Min) {
						scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
						Data_tmp->CR.DYNA[Data_tmp->IRange].T1_RANGE=T1_RANGE_temp;
						return;
					}
				}
				SettingCount = cnt1;
				Command_Done=1;
			} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				SettingCount = (1 == value.si) ? DyMax : (ptrMODEL_TYPE->CR)[8].Min;
				Data_tmp->CR.DYNA[Data_tmp->IRange].T1_RANGE = value.si;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}
			if(Command_Done==1) {
				if(Data_tmp->CURRMODE != CR_MODE) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CURRMODE = CR_MODE;
					Mode_Change=1;
				}
				if(Data_tmp->CR.STADYNA!=SCPI_Dynamic_Status) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CR.STADYNA=SCPI_Dynamic_Status;
					Range_Change=1;
				}
				if(Mode_Change || Range_Change) {
					Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
					ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

					RestoreRealChan();
					if(M_num != Disp_tmp->CURRMODE)
						M_num = Disp_tmp->CURRMODE;
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
						ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
						DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
						MenuRedrawFlag|= MENU_CHANGE;
						if(DispMode>DispMode_BROWSE_ITEMS)
							DispMode = DispMode_BROWSE_ITEMS;
					}

					if(Mode_Change) {
						tx_data.ADDRH=0x00;
						tx_data.ADDRL=0x06;
						SendTXData(&tx_data);
					}
					if(Range_Change) {
						if(Data_tmp->CURRMODE==CC_MODE)
							tx_data.ADDRH=0x01;
						else if(Data_tmp->CURRMODE==CR_MODE)
							tx_data.ADDRH=0x02;
						else if(Data_tmp->CURRMODE==CV_MODE)
							tx_data.ADDRH=0x03;
						else if(Data_tmp->CURRMODE==CP_MODE)
							tx_data.ADDRH=0x04;
						tx_data.ADDRL=0x00;
						SendTXData(&tx_data);
					}
				}
				Data_tmp->CR.DYNA[Data_tmp->IRange].TIME1 = SettingCount;
				Disp_tmp->CR.DYNA[Data_tmp->IRange].TIME1 = SettingCount;
				Disp_tmp->CR.DYNA[Data_tmp->IRange].T1_RANGE = Data_tmp->CR.DYNA[Data_tmp->IRange].T1_RANGE;
				if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					DataRedrawFlag |= PARA_CHANGE;
					Draw_Set_parameter();					
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}
				tx_data.ADDRH=0x02;
				tx_data.ADDRL=0x50;
				SendTXData(&tx_data);
				if(Load_On_Status) {
					UTILITY.LOAD_CTL=0x01;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 0;
				}
			}
		}
	} else if(scpi_GetNumericSuffix(p,1)==2) { //L2========================
		if(scpi_IsQueryCommand(p)) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					Min=(double)0.00005;
					ExportProcess(Float_Data,Min,0,0,6);
				} else if (value.si==SCPI_MAX) {
					Max=(double)DyMax/1000;//30.0;
					ExportProcess(Float_Data,Max,0,0,6);
				}
			} else {
				SettingCount = Data_tmp->CR.DYNA[Data_tmp->IRange].TIME2;
				if(Data_tmp->CR.DYNA[Data_tmp->IRange].T2_RANGE)
					Real_Value = SettingCount;
				else
					Real_Value = SettingCount * ResolutionTemp;
				Real_Value = Real_Value *0.001;
				ExportProcess(Float_Data,Real_Value,0,0,6);
			}
		} else {

			if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
				Real_Value = value.d * 1000;
				cnt1 = SCPI_InputToStep(Real_Value,ResolutionTemp);
				T1_RANGE_temp = Data_tmp->CR.DYNA[Data_tmp->IRange].T2_RANGE;
				Data_tmp->CR.DYNA[Data_tmp->IRange].T2_RANGE=0;
				if(cnt1>(ptrMODEL_TYPE->CR)[8].Max) {
					Data_tmp->CR.DYNA[Data_tmp->IRange].T2_RANGE=1;
					cnt1 /= 1000;
					if(cnt1 > DyMax) {
						scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
						Data_tmp->CR.DYNA[Data_tmp->IRange].T2_RANGE=T1_RANGE_temp;
						return;
					}
				} else {
					if(cnt1 < (ptrMODEL_TYPE->CR)[8].Min) {
						scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
						Data_tmp->CR.DYNA[Data_tmp->IRange].T2_RANGE=T1_RANGE_temp;
						return;
					}
				}
				SettingCount = cnt1;
				Command_Done=1;
			} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				SettingCount = (1 == value.si) ? DyMax : (ptrMODEL_TYPE->CR)[8].Min;
				Data_tmp->CR.DYNA[Data_tmp->IRange].T2_RANGE = value.si;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}
			if(Command_Done==1) {
				if(Data_tmp->CURRMODE != CR_MODE) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CURRMODE = CR_MODE;
					Mode_Change=1;
				}
				if(Data_tmp->CR.STADYNA!=SCPI_Dynamic_Status) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CR.STADYNA=SCPI_Dynamic_Status;
					Range_Change=1;
				}
				if(Mode_Change || Range_Change) {
					Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
					ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

					RestoreRealChan();
					if(M_num != Disp_tmp->CURRMODE)
						M_num = Disp_tmp->CURRMODE;
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
						ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
						DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
						MenuRedrawFlag|= MENU_CHANGE;
						if(DispMode>DispMode_BROWSE_ITEMS)
							DispMode = DispMode_BROWSE_ITEMS;
					}

					if(Mode_Change) {
						tx_data.ADDRH=0x00;
						tx_data.ADDRL=0x06;
						SendTXData(&tx_data);
					}
					if(Range_Change) {
						if(Data_tmp->CURRMODE==CC_MODE)
							tx_data.ADDRH=0x01;
						else if(Data_tmp->CURRMODE==CR_MODE)
							tx_data.ADDRH=0x02;
						else if(Data_tmp->CURRMODE==CV_MODE)
							tx_data.ADDRH=0x03;
						else if(Data_tmp->CURRMODE==CP_MODE)
							tx_data.ADDRH=0x04;
						tx_data.ADDRL=0x00;
						SendTXData(&tx_data);
					}
				}
				Data_tmp->CR.DYNA[Data_tmp->IRange].TIME2 = SettingCount;
				Disp_tmp->CR.DYNA[Data_tmp->IRange].TIME2 = SettingCount;
				Disp_tmp->CR.DYNA[Data_tmp->IRange].T2_RANGE = Data_tmp->CR.DYNA[Data_tmp->IRange].T2_RANGE;
				if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					DataRedrawFlag |= PARA_CHANGE;
					Draw_Set_parameter();					
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				tx_data.ADDRH=0x02;
				tx_data.ADDRL=0x50;
				SendTXData(&tx_data);
				if(Load_On_Status) {
					UTILITY.LOAD_CTL=0x01;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 0;
				}
			}
		}
	}
// Code End
}

void idRESistanceFREQuency(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Precision_tmp,Load_On_Status=0;
	double Max=20000,Min=10,ResolutionTemp;

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;

// Code Begin
	if(P3k_Chan_Data.CONF.Dyna_Time==0) { //If value mode, return.
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min=(double)1.0;
				ExportProcess(Float_Data,Min,0,0,1);
			} else if (value.si==SCPI_MAX) {
				Max=(double)20000;
				ExportProcess(Float_Data,Max,0,0,1);
			}
		} else {
			switch (Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency_Range) {
			case Dyn_Freq_TimeBase_100Hz:
				ResolutionTemp=100;
				break;
			case Dyn_Freq_TimeBase_10Hz:
				ResolutionTemp =10;
				break;
			case Dyn_Freq_TimeBase_1Hz:
				ResolutionTemp=1;
				break;
			case Dyn_Freq_TimeBase_100mHz:
				ResolutionTemp=0.1;//0.1
				break;
			default:
				break;
			}
			ExportProcess(Float_Data,Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency*ResolutionTemp,0,0,1);
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			if (value.d >= 1000) { //Freq>=10k Hz
				Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_100Hz;
				ResolutionTemp=100;
			} else if(value.d >= 100) { // 100 Hz <= Freq < 10k Hz
				Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_10Hz;
				ResolutionTemp=10;
			} else if(value.d >= 10) { // 10 Hz <= Freq < 100 Hz
				Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_1Hz;
				ResolutionTemp=1;
			} else if(value.d >= 0) { // 0 Hz <= Freq < 10 Hz
				Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_100mHz;
				ResolutionTemp=0.1;
			}
			if((value.d<=Max) && (value.d>=(Min/10))) {
				Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency_Range=Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency_Range;
				Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency = SCPI_InputToStep(value.d,ResolutionTemp);
				Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency=Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency;
				Command_Done=1;
			} else {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(0 == value.si) {
				Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_100mHz;
				Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency_Range=Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency_Range;
				Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency=(UWORD)Min;
				Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency=Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency;
				Command_Done=1;
			} else if(1 == value.si) {
				Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_100Hz;
				Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency_Range=Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency_Range;
				Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency=(UWORD)Max/100;
				Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency=Data_tmp->CR.DYNA[Data_tmp->IRange].Frequency;
				Command_Done=1;
			}
			Command_Done = 1;

		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if(Data_tmp->CURRMODE != CR_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE = CR_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CR.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CR.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
			}
			if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x02;
			tx_data.ADDRL=0x50;
			SendTXData(&tx_data);
			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End
}

void idRESistanceDUTY(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	double Min=1,Max=99,ResolutionTemp=0.1;
	UWORD SettingCount,min,max;
	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;

// Code Begin
	if(P3k_Chan_Data.CONF.Dyna_Time==0) { //If value mode, return.
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min=(double)1.0;
				ExportProcess(Float_Data,Min,0,0,1);
			} else if (value.si==SCPI_MAX) {
				Max=(double)99.0;
				ExportProcess(Float_Data,Max,0,0,1);
			}
		} else {
			ExportProcess(Float_Data,Data_tmp->CR.DYNA[Data_tmp->IRange].Duty*ResolutionTemp,0,0,1);
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {

			if((value.d > Max)||(value.d < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(value.d,ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(SCPI_MIN== value.si) {
				SettingCount =SCPI_InputToStep(Min,ResolutionTemp);
				Disp_tmp->CR.DYNA[Disp_tmp->IRange].Duty=Data_tmp->CR.DYNA[Data_tmp->IRange].Duty;
			} else if(SCPI_MAX== value.si) {
				SettingCount =SCPI_InputToStep(Max,ResolutionTemp);
				Disp_tmp->CR.DYNA[Disp_tmp->IRange].Duty=Data_tmp->CR.DYNA[Data_tmp->IRange].Duty;
			}
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CR.DYNA[Data_tmp->IRange].Duty = SettingCount;
			Disp_tmp->CR.DYNA[Disp_tmp->IRange].Duty = SettingCount;
#if 1
			min = get_DynaFreqDutyRangeLimit(P_CR);
			max = 1000 - min;
			if(Data_tmp->CR.DYNA[Data_tmp->IRange].Duty<min)Data_tmp->CR.DYNA[Data_tmp->IRange].Duty=min;
			else if(Data_tmp->CR.DYNA[Data_tmp->IRange].Duty>max)Data_tmp->CR.DYNA[Data_tmp->IRange].Duty = max;
			Disp_tmp->CR.DYNA[Data_tmp->IRange].Duty = Data_tmp->CR.DYNA[Data_tmp->IRange].Duty;
#endif
			if(Data_tmp->CURRMODE != CR_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE = CR_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CR.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CR.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
			}
			if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x02;
			tx_data.ADDRL=0x50;
			SendTXData(&tx_data);
			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}

		}
	}
// Code End
}

void idRESistanceCVRESPonse(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, SettingCount=0;
	p3k_send_tx_list tx_data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	char	str[20];
	unsigned char return_response;
	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

// Code Begin
	return_response = Data_tmp->CR.CXCV_RESPOSNE;
	if(scpi_IsQueryCommand(p)) {		
		if (return_response==SCPI_RESPonse_FAST)
			ExportProcess(String_Data,0,0,"Fast",0);
		else
			ExportProcess(String_Data,0,0,"Slow",0);		
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {			
			SettingCount=value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			
			if(return_response==SettingCount)return;
			Data_tmp->CR.CXCV_RESPOSNE = SettingCount;
			Disp_tmp->CR.CXCV_RESPOSNE = SettingCount;

			if((M_num <= P_CONF_Ext)&&(!PC_scriptrun)&&(!usbrun)) {
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
				ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				MenuRedrawFlag|= MENU_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}				
			tx_data.ADDRH=0x02;
			tx_data.ADDRL=0x00;
			SendTXData(&tx_data);
			
		}
	}
// Code End
}

void idVOLTageRECall(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingBool;

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
		
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(Disp_tmp->CV.ABSELECT)
			ExportProcess(String_Data,0,0,"1",0);
		else
			ExportProcess(String_Data,0,0,"0",0);

	} else {

		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}

		if(Command_Done) {			
			Disp_tmp->CV.ABSELECT=SettingBool;
			Data_tmp->CV.ABSELECT = Disp_tmp->CV.ABSELECT;
			ChanRedrawFlag |= CHAN_STATUS;
			
			tx_data.ADDRH = 0x03;
			tx_data.ADDRL = 0x00;
			SendTXData(&tx_data);
		}		
	}	
// Code End
}


void idVOLTageVA(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,i,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[30];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	ResolutionTemp=((ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].Resolution);

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		UBYTE precisionTemp;
		precisionTemp =((ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].precision);
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min=(double)(ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].Min*ResolutionTemp;
				ExportProcess(Float_Data,Min,0,0,precisionTemp);
			} else if(value.si==SCPI_MAX) {
				Max=(double)(ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].Max*ResolutionTemp;
				ExportProcess(Float_Data,Max,0,0,precisionTemp);
			}
		} else {
			SettingCount = Data_tmp->CV.STA[Data_tmp->VRange].VALUE1;
			Real_Value = (double)(SettingCount * ResolutionTemp);
			ExportProcess(Float_Data,Real_Value,0,0,precisionTemp);
		}
	} else {
		Max=(double)(ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].Max*ResolutionTemp;
		Min=(double)(ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].Min*ResolutionTemp;
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {

			if((value.d > Max)||(value.d < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(value.d , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? (ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].Max : (ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].Min;
			Command_Done = 1;

		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
#if 0
			if(Data_tmp->CURRMODE != CV_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE = CV_MODE;
				Mode_Change=1;
			}

			if(Mode_Change ) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}

			}
#endif
			Data_tmp->CV.STA[Data_tmp->VRange].VALUE1 = SettingCount;
			Disp_tmp->CV.STA[Data_tmp->VRange].VALUE1 = SettingCount;
			if((M_num==CV_MODE)&&(Disp_tmp->CV.STADYNA==SCPI_Static_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x03;
			tx_data.ADDRL=0x10;
			SendTXData(&tx_data);

			if((!Data_tmp->UTILITY.B_ONOFF)&&(Data_tmp->CV.ABSELECT)) {
				Disp_tmp->CV.ABSELECT = Data_tmp->CV.ABSELECT = SCPI_AValue;

				tx_data.ADDRH = 0x03;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu))
					ChanRedrawFlag|= CHAN_STATUS;
			}
			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End
}

void idVOLTageVB(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,i,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[30];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	ResolutionTemp=((ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].Resolution);

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		UBYTE precisionTemp;
		precisionTemp =((ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].precision);
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min=(double)(ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].Min*ResolutionTemp;
				ExportProcess(Float_Data,Min,0,0,precisionTemp);
			} else if(value.si==SCPI_MAX) {
				Max=(double)(ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].Max*ResolutionTemp;
				ExportProcess(Float_Data,Max,0,0,precisionTemp);
			}
		} else {
			SettingCount = Data_tmp->CV.STA[Data_tmp->VRange].VALUE2;
			Real_Value = (double)(SettingCount * ResolutionTemp);
			ExportProcess(Float_Data,Real_Value,0,0,precisionTemp);
		}
	} else {
		Max=(double)(ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].Max*ResolutionTemp;
		Min=(double)(ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].Min*ResolutionTemp;
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {

			if((value.d > Max)||(value.d < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(value.d , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? (ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].Max : (ptrMODEL_TYPE->CV)[Data_tmp->VRange*3].Min;
			Command_Done = 1;

		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
#if 0
			if(Data_tmp->CURRMODE != CV_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE = CV_MODE;
				Mode_Change=1;
			}

			if(Mode_Change ) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}

			}
#endif
			Data_tmp->CV.STA[Data_tmp->VRange].VALUE2 = SettingCount;
			Disp_tmp->CV.STA[Data_tmp->VRange].VALUE2 = SettingCount;
			if((M_num==CV_MODE)&&(Disp_tmp->CV.STADYNA==SCPI_Static_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x03;
			tx_data.ADDRL=0x12;
			SendTXData(&tx_data);

			if((!Data_tmp->UTILITY.B_ONOFF)&&(!Data_tmp->CV.ABSELECT)) {
				Disp_tmp->CV.ABSELECT = Data_tmp->CV.ABSELECT = SCPI_BValue;

				tx_data.ADDRH = 0x03;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu))
					ChanRedrawFlag|= CHAN_STATUS;
			}
			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End
}

void idVOLTageRESPonse(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, SettingCount=0;
	p3k_send_tx_list tx_data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	char	str[20];
	unsigned char return_response;
	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

// Code Begin
	return_response = Data_tmp->CV.RESPONSE;
	if(scpi_IsQueryCommand(p)) {		
		if (return_response==SCPI_RESPonse_CVCP_FAST)
			ExportProcess(String_Data,0,0,"Fast",0);
		else if (return_response==SCPI_RESPonse_CVCP_NORMAL)
			ExportProcess(String_Data,0,0,"Normal",0);		
		else 
			ExportProcess(String_Data,0,0,"Slow",0);
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {			
			SettingCount=value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {			
			if(return_response==SettingCount)return;
			Data_tmp->CV.RESPONSE = SettingCount;
			Disp_tmp->CV.RESPONSE = SettingCount;
			if((M_num <= P_CONF_Ext)&&(!PC_scriptrun)&&(!usbrun)) {
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
				ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				MenuRedrawFlag|= MENU_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}				
			tx_data.ADDRH=0x03;
			tx_data.ADDRL=0x00;
			SendTXData(&tx_data);			
		}
	}
// Code End
}

void idPOWerRECall(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingBool;

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
		
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(Disp_tmp->CP.ABSELECT)
			ExportProcess(String_Data,0,0,"1",0);
		else
			ExportProcess(String_Data,0,0,"0",0);

	} else {

		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}

		if(Command_Done) {			
			Disp_tmp->CP.ABSELECT=SettingBool;
			Data_tmp->CP.ABSELECT = Disp_tmp->CP.ABSELECT;
			ChanRedrawFlag |= CHAN_STATUS;
			
			tx_data.ADDRH = 0x04;
			tx_data.ADDRL = 0x00;
			SendTXData(&tx_data);
		}		
	}	
// Code End
}


void idPOWerVA(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,i,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[30];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	ResolutionTemp =((ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].Resolution);
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		UBYTE precisionTemp;
		precisionTemp = ((ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].precision);
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min= (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].Min*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Min,0,0,precisionTemp);
			} else if(value.si==SCPI_MAX) {
				Max = (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].Max*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Max,0,0,precisionTemp);
			}
		} else {
			SettingCount = Data_tmp->CP.STA[Data_tmp->IRange].VALUE1;
			Real_Value = (double)SettingCount * ResolutionTemp *Para_s;
			ExportProcess(Float_Data,Real_Value,0,0,precisionTemp);
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Max = (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].Max*ResolutionTemp;
			Min= (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].Min*ResolutionTemp;
			Real_Value = value.d / Para_s;
			if((Real_Value > Max)||(Real_Value < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? (ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].Max : (ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].Min;
			Command_Done = 1;

		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if(Data_tmp->CURRMODE != CP_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE = CP_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CP.STADYNA!=SCPI_Static_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CP.STADYNA=SCPI_Static_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
				SoftStartDoubleCheck();
			}
			
			Data_tmp->CP.STA[Data_tmp->IRange].VALUE1 = SettingCount;
			Disp_tmp->CP.STA[Data_tmp->IRange].VALUE1 = SettingCount;
			if((M_num==P_CP)&&(Disp_tmp->CP.STADYNA==SCPI_Static_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH=0x04;
			tx_data.ADDRL=0x10;
			SendTXData(&tx_data);

			if((!Data_tmp->UTILITY.B_ONOFF)&&(Data_tmp->CP.ABSELECT)) {
				Disp_tmp->CP.ABSELECT = Data_tmp->CP.ABSELECT = SCPI_AValue;

				tx_data.ADDRH = 0x04;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				if((Disp_tmp->CURRMODE==CP_MODE)&&(!SCPI_Freeze_menu))
					ChanRedrawFlag|= CHAN_STATUS;
			}

			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End
}

void idPOWerVB(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,i,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[30];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	ResolutionTemp =((ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].Resolution);
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		UBYTE precisionTemp;
		precisionTemp = ((ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].precision);
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min= (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].Min*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Min,0,0,precisionTemp);
			} else if(value.si==SCPI_MAX) {
				Max = (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].Max*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Max,0,0,precisionTemp);
			}
		} else {
			SettingCount = Data_tmp->CP.STA[Data_tmp->IRange].VALUE2;
			Real_Value = (double)SettingCount * ResolutionTemp *Para_s;
			ExportProcess(Float_Data,Real_Value,0,0,precisionTemp);
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Max = (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].Max*ResolutionTemp;
			Min= (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].Min*ResolutionTemp;
			Real_Value = value.d / Para_s;
			if((Real_Value > Max)||(Real_Value < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? (ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].Max : (ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].Min;
			Command_Done = 1;

		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if(Data_tmp->CURRMODE != CP_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE = CP_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CP.STADYNA!=SCPI_Static_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CP.STADYNA=SCPI_Static_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
				SoftStartDoubleCheck();
			}
			
			Data_tmp->CP.STA[Data_tmp->IRange].VALUE2 = SettingCount;
			Disp_tmp->CP.STA[Data_tmp->IRange].VALUE2 = SettingCount;
			if((M_num==P_CP)&&(Disp_tmp->CP.STADYNA==SCPI_Static_Status)&&(Data_tmp->IRange==Data_tmp->IRange)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x04;
			tx_data.ADDRL=0x10;
			SendTXData(&tx_data);

			if((!Data_tmp->UTILITY.B_ONOFF)&&(!Data_tmp->CP.ABSELECT)) {
				Disp_tmp->CP.ABSELECT = Data_tmp->CP.ABSELECT = SCPI_BValue;

				tx_data.ADDRH = 0x04;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				if(Disp_tmp->CURRMODE==CP_MODE)
					ChanRedrawFlag|= CHAN_STATUS;
			}
			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End
}

void idPOWerL12(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,i,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[30];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	ResolutionTemp =((ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Resolution);
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
	UBYTE precisionTemp;
	precisionTemp = ((ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].precision);
// Code Begin
	if(scpi_GetNumericSuffix(p,1)==1) { //L1==================================
		if(scpi_IsQueryCommand(p)) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					Min= (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Min*ResolutionTemp*Para_s;
					ExportProcess(Float_Data,Min,0,0,precisionTemp);
				} else if(value.si==SCPI_MAX) {
					Max = (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Max*ResolutionTemp*Para_s;
					ExportProcess(Float_Data,Max,0,0,precisionTemp);
				}
			} else {
				SettingCount = Data_tmp->CP.DYNA[Data_tmp->IRange].LEVEL1;
				Real_Value = (double)SettingCount * ResolutionTemp *Para_s;
				ExportProcess(Float_Data,Real_Value,0,0,precisionTemp);
			}
		} else {
			if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
				Max =(double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Max*ResolutionTemp;
				Min= (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Min*ResolutionTemp;
				Real_Value = value.d / Para_s;
				if((Real_Value > Max)||(Real_Value < Min)) {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
				SettingCount = SCPI_InputToStep(Real_Value , ResolutionTemp);
				Command_Done=1;
			} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				SettingCount = (1 == value.si) ? (ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Max : (ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Min;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}
			if(Command_Done==1) {
				if(Data_tmp->CURRMODE!=CP_MODE) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CURRMODE=CP_MODE;
					Mode_Change=1;
				}
				if(Data_tmp->CP.STADYNA!=SCPI_Dynamic_Status) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CP.STADYNA=SCPI_Dynamic_Status;
					Range_Change=1;
				}
				if(Mode_Change || Range_Change) {
					Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
					ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

					RestoreRealChan();
					if(M_num != Disp_tmp->CURRMODE)
						M_num = Disp_tmp->CURRMODE;
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
						ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
						DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
						MenuRedrawFlag|= MENU_CHANGE;
						if(DispMode>DispMode_BROWSE_ITEMS)
							DispMode = DispMode_BROWSE_ITEMS;
					}

					if(Mode_Change) {
						tx_data.ADDRH=0x00;
						tx_data.ADDRL=0x06;
						SendTXData(&tx_data);
					}
					if(Range_Change) {
						if(Data_tmp->CURRMODE==CC_MODE)
							tx_data.ADDRH=0x01;
						else if(Data_tmp->CURRMODE==CR_MODE)
							tx_data.ADDRH=0x02;
						else if(Data_tmp->CURRMODE==CV_MODE)
							tx_data.ADDRH=0x03;
						else
							tx_data.ADDRH=0x04;
						tx_data.ADDRL=0x00;
						SendTXData(&tx_data);
					}
					SoftStartDoubleCheck();
				}
				
				Data_tmp->CP.DYNA[Data_tmp->IRange].LEVEL1 = SettingCount;
				Disp_tmp->CP.DYNA[Data_tmp->IRange].LEVEL1 = SettingCount;
				if((M_num==P_CP)&&(Disp_tmp->CP.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					DataRedrawFlag |= PARA_CHANGE;
					Draw_Set_parameter();					
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}
				tx_data.ADDRH=0x04;
				tx_data.ADDRL=0x40;
				SendTXData(&tx_data);

				if(Load_On_Status) {
					UTILITY.LOAD_CTL=0x01;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 0;
				}
			}
		}
	} else if(scpi_GetNumericSuffix(p,1)==2) { //L2========================
		if(scpi_IsQueryCommand(p)) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					Min= (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Min*ResolutionTemp;
					ExportProcess(Float_Data,Min,0,0,precisionTemp);
				} else if(value.si==SCPI_MAX) {
					Max = (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Max*ResolutionTemp;
					ExportProcess(Float_Data,Max,0,0,precisionTemp);
				}
			} else {
				SettingCount = Data_tmp->CP.DYNA[Data_tmp->IRange].LEVEL2;
				Real_Value = (double)SettingCount * ResolutionTemp *Para_s;
				ExportProcess(Float_Data,Real_Value,0,0,precisionTemp);
			}
		} else {
			if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
				Max =(double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Max*ResolutionTemp;
				Min= (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Min*ResolutionTemp;
				Real_Value = value.d / Para_s;
				if((Real_Value > Max)||(Real_Value < Min)) {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
				SettingCount = SCPI_InputToStep(Real_Value , ResolutionTemp);
				Command_Done=1;
			} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				SettingCount = (1 == value.si) ? (ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Max : ptrMODEL_TYPE->CP[Data_tmp->IRange*10+4].Min;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}
			if(Command_Done==1) {
				if(Data_tmp->CURRMODE!=CP_MODE) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CURRMODE=CP_MODE;
					Mode_Change=1;
				}
				if(Data_tmp->CP.STADYNA!=SCPI_Dynamic_Status) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CP.STADYNA=SCPI_Dynamic_Status;
					Range_Change=1;
				}
				if(Mode_Change || Range_Change) {
					Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
					ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

					RestoreRealChan();
					if(M_num != Disp_tmp->CURRMODE)
						M_num = Disp_tmp->CURRMODE;
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
						ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
						DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
						MenuRedrawFlag|= MENU_CHANGE;
						if(DispMode>DispMode_BROWSE_ITEMS)
							DispMode = DispMode_BROWSE_ITEMS;
					}

					if(Mode_Change) {
						tx_data.ADDRH=0x00;
						tx_data.ADDRL=0x06;
						SendTXData(&tx_data);
					}
					if(Range_Change) {
						if(Data_tmp->CURRMODE==CC_MODE)
							tx_data.ADDRH=0x01;
						else if(Data_tmp->CURRMODE==CR_MODE)
							tx_data.ADDRH=0x02;
						else if(Data_tmp->CURRMODE==CV_MODE)
							tx_data.ADDRH=0x03;
						else if(Data_tmp->CURRMODE==CP_MODE)
							tx_data.ADDRH=0x04;
						tx_data.ADDRL=0x00;
						SendTXData(&tx_data);
					}
					SoftStartDoubleCheck();
				}
				
				Data_tmp->CP.DYNA[Data_tmp->IRange].LEVEL2 = SettingCount;
				Disp_tmp->CP.DYNA[Data_tmp->IRange].LEVEL2 = SettingCount;
				if((M_num==P_CP)&&(Disp_tmp->CP.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					DataRedrawFlag |= PARA_CHANGE;
					Draw_Set_parameter();					
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				tx_data.ADDRH=0x04;
				tx_data.ADDRL=0x42;
				SendTXData(&tx_data);

				if(Load_On_Status) {
					UTILITY.LOAD_CTL=0x01;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 0;
				}
			}
		}
	}
// Code End
}

void idPOWerSET(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,i,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[30];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	ResolutionTemp =((ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].Resolution);
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

// Code Begin
	if (Data_tmp->CONF.Dyna_Level==0) { //if value mode, return
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if(scpi_IsQueryCommand(p)) {
		UBYTE precisionTemp;
		precisionTemp = ((ptrMODEL_TYPE->CP)[Data_tmp->IRange*10].precision);
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min= (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Min*ResolutionTemp;
				ExportProcess(Float_Data,Min,0,0,precisionTemp);
			} else if(value.si==SCPI_MAX) {
				Max = (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Max*ResolutionTemp;
				ExportProcess(Float_Data,Max,0,0,precisionTemp);
			}
		} else {
			SettingCount = Data_tmp->CP.DYNA[Data_tmp->IRange].LEVEL1;
			Real_Value = (double)SettingCount * ResolutionTemp *Para_s;
			ExportProcess(Float_Data,Real_Value,0,0,precisionTemp);
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Max = (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Max*ResolutionTemp;
			Min= (double)(ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Min*ResolutionTemp;
			Real_Value = value.d / Para_s;
			if((Real_Value > Max)||(Real_Value < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? (ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Max : (ptrMODEL_TYPE->CP)[Data_tmp->IRange*10+4].Min;
			Command_Done = 1;

		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CP.DYNA[Data_tmp->IRange].LEVEL1=SettingCount;
			Disp_tmp->CP.DYNA[Disp_tmp->IRange].LEVEL1=SettingCount;
			if(Data_tmp->CURRMODE!=CP_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CP_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CP.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CP.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
				SoftStartDoubleCheck();
			}
			
			if((M_num==P_CP)&&(Disp_tmp->CP.STADYNA)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x04;
			tx_data.ADDRL=0x54;
			SendTXData(&tx_data);

			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End

}

void idPOWerLEVel(STR_PARSER * p)
{
	GW_TYPE value;
	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	UWORD SettingCount;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	double Max,Min,ResolutionTemp;
	ResolutionTemp=0.1;
	Min=0.0;
	Max=100.0;
// Code Begin
	if (Data_tmp->CONF.Dyna_Level==0) { //if value mode, return
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				ExportProcess(Float_Data,Min,0,0,1);
			} else if (value.si==SCPI_MAX) {
				ExportProcess(Float_Data,Max,0,0,1);
			}
		} else {
			ExportProcess(Float_Data,Disp_tmp->CP.DYNA[Disp_tmp->IRange].Level_Percent*ResolutionTemp,0,0,ceild(log10(Disp_tmp->CC.DYNA[Disp_tmp->IRange].Level_Percent*ResolutionTemp)));
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			if((value.d > Max)||(value.d < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(value.d,ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? 1000 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Data_tmp->CP.DYNA[Data_tmp->IRange].Level_Percent=SettingCount;
			Disp_tmp->CP.DYNA[Disp_tmp->IRange].Level_Percent=SettingCount;
			if(Data_tmp->CURRMODE!=CP_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CP_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CP.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CP.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
			}

			if((M_num==P_CP)&&(Disp_tmp->CP.STADYNA)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x04;
			tx_data.ADDRL=0x54;
			SendTXData(&tx_data);

			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End
}

void idPOWerT12(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,T1_RANGE_temp,Mode_Change=0,Range_Change=0,Load_On_Status=0;

	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp;
	ULONG cnt1;

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	ResolutionTemp = (ptrMODEL_TYPE->CP)[8].Resolution;
// Code Begin
	if(P3k_Chan_Data.CONF.Dyna_Time) { //If freq mode, return.
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}

	if(scpi_GetNumericSuffix(p,1)==1) { //L1==================================
		if(scpi_IsQueryCommand(p)) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					Min=(double)0.000025;
					ExportProcess(Float_Data,Min,0,0,6);
				} else if (value.si==SCPI_MAX) {
					Max=(double)DyMax/1000;//30.0;
					ExportProcess(Float_Data,Max,0,0,6);
				}
			} else {
				SettingCount = Data_tmp->CP.DYNA[Data_tmp->IRange].TIME1;
				if(Data_tmp->CP.DYNA[Data_tmp->IRange].T1_RANGE)
					Real_Value = SettingCount;
				else
					Real_Value = SettingCount * ResolutionTemp;
				Real_Value = Real_Value *0.001;
				ExportProcess(Float_Data,Real_Value,0,0,6);
			}
		} else {

			if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
				Real_Value = value.d * 1000;
				cnt1 = SCPI_InputToStep(Real_Value,ResolutionTemp);
				T1_RANGE_temp = Data_tmp->CP.DYNA[Data_tmp->IRange].T1_RANGE;
				Data_tmp->CP.DYNA[Data_tmp->IRange].T1_RANGE=0;
				if(cnt1>(ptrMODEL_TYPE->CP)[8].Max) {
					Data_tmp->CP.DYNA[Data_tmp->IRange].T1_RANGE=1;
					cnt1 /= 1000;
					if(cnt1 > DyMax) {
						scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
						Data_tmp->CP.DYNA[Data_tmp->IRange].T1_RANGE=T1_RANGE_temp;
						return;
					}
				} else {
					if(cnt1 < (ptrMODEL_TYPE->CP)[8].Min) {
						scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
						Data_tmp->CP.DYNA[Data_tmp->IRange].T1_RANGE=T1_RANGE_temp;
						return;
					}
				}
				SettingCount = cnt1;
				Command_Done=1;
			} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				SettingCount = (1 == value.si) ? DyMax : (ptrMODEL_TYPE->CP)[8].Min;
				Data_tmp->CP.DYNA[Data_tmp->IRange].T1_RANGE = value.si;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}
			if(Command_Done==1) {
				if(Data_tmp->CURRMODE!=CP_MODE) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CURRMODE=CP_MODE;
					Mode_Change=1;
				}
				if(Data_tmp->CP.STADYNA!=SCPI_Dynamic_Status) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CP.STADYNA=SCPI_Dynamic_Status;
					Range_Change=1;
				}
				if(Mode_Change || Range_Change) {
					Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
					ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

					RestoreRealChan();
					if(M_num != Disp_tmp->CURRMODE)
						M_num = Disp_tmp->CURRMODE;
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
						ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
						DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
						MenuRedrawFlag|= MENU_CHANGE;
						if(DispMode>DispMode_BROWSE_ITEMS)
							DispMode = DispMode_BROWSE_ITEMS;
					}

					if(Mode_Change) {
						tx_data.ADDRH=0x00;
						tx_data.ADDRL=0x06;
						SendTXData(&tx_data);
					}
					if(Range_Change) {
						if(Data_tmp->CURRMODE==CC_MODE)
							tx_data.ADDRH=0x01;
						else if(Data_tmp->CURRMODE==CR_MODE)
							tx_data.ADDRH=0x02;
						else if(Data_tmp->CURRMODE==CV_MODE)
							tx_data.ADDRH=0x03;
						else if(Data_tmp->CURRMODE==CP_MODE)
							tx_data.ADDRH=0x04;
						tx_data.ADDRL=0x00;
						SendTXData(&tx_data);
					}
				}
				Data_tmp->CP.DYNA[Data_tmp->IRange].TIME1 = SettingCount;
				Disp_tmp->CP.DYNA[Data_tmp->IRange].TIME1 = SettingCount;
				Disp_tmp->CP.DYNA[Data_tmp->IRange].T1_RANGE = Data_tmp->CP.DYNA[Data_tmp->IRange].T1_RANGE;

				if((M_num==P_CP)&&(Disp_tmp->CP.STADYNA)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					DataRedrawFlag |= PARA_CHANGE;
					Draw_Set_parameter();					
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				tx_data.ADDRH=0x04;
				tx_data.ADDRL=0x54;
				SendTXData(&tx_data);

				if(Load_On_Status) {
					UTILITY.LOAD_CTL=0x01;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 0;
				}
			}
		}
	} else if(scpi_GetNumericSuffix(p,1)==2) { //L2========================
		if(scpi_IsQueryCommand(p)) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					Min=(double)0.000025;
					ExportProcess(Float_Data,Min,0,0,6);
				} else if (value.si==SCPI_MAX) {
					Max=(double)DyMax/1000;//30.0;
					ExportProcess(Float_Data,Max,0,0,6);
				}
			} else {
				SettingCount = Data_tmp->CP.DYNA[Data_tmp->IRange].TIME2;
				if(Data_tmp->CP.DYNA[Data_tmp->IRange].T2_RANGE)
					Real_Value = SettingCount;
				else
					Real_Value = SettingCount * ResolutionTemp;
				Real_Value = Real_Value *0.001;
				ExportProcess(Float_Data,Real_Value,0,0,6);
			}
		} else {

			if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
				Real_Value = value.d * 1000;
				cnt1 = SCPI_InputToStep(Real_Value,ResolutionTemp);
				T1_RANGE_temp = Data_tmp->CP.DYNA[Data_tmp->IRange].T2_RANGE;
				Data_tmp->CP.DYNA[Data_tmp->IRange].T2_RANGE=0;
				if(cnt1>(ptrMODEL_TYPE->CP)[8].Max) {
					Data_tmp->CP.DYNA[Data_tmp->IRange].T2_RANGE=1;
					cnt1 /= 1000;
					if(cnt1 > DyMax) {
						scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
						Data_tmp->CP.DYNA[Data_tmp->IRange].T2_RANGE=T1_RANGE_temp;
						return;
					}
				} else {
					if(cnt1 < (ptrMODEL_TYPE->CP)[8].Min) {
						scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
						Data_tmp->CP.DYNA[Data_tmp->IRange].T2_RANGE=T1_RANGE_temp;
						return;
					}
				}
				SettingCount = cnt1;
				Command_Done=1;
			} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				SettingCount = (1 == value.si) ? DyMax : (ptrMODEL_TYPE->CP)[8].Min;
				Data_tmp->CP.DYNA[Data_tmp->IRange].T2_RANGE = value.si;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}
			if(Command_Done==1) {
				if(Data_tmp->CURRMODE!=CP_MODE) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CURRMODE=CP_MODE;
					Mode_Change=1;
				}
				if(Data_tmp->CP.STADYNA!=SCPI_Dynamic_Status) {
					if(UTILITY.LOAD_CTL) {
						UTILITY.LOAD_CTL=0x00;
						tx_data.ADDRH = 0x00;
						tx_data.ADDRL = 0x0B;
						SendTXData(&tx_data);
						Load_On_Status = 1;
					}
					Data_tmp->CP.STADYNA=SCPI_Dynamic_Status;
					Range_Change=1;
				}
				if(Mode_Change || Range_Change) {
					Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
					ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

					RestoreRealChan();
					if(M_num != Disp_tmp->CURRMODE)
						M_num = Disp_tmp->CURRMODE;
					if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
						ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
						DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
						MenuRedrawFlag|= MENU_CHANGE;
						if(DispMode>DispMode_BROWSE_ITEMS)
							DispMode = DispMode_BROWSE_ITEMS;
					}

					if(Mode_Change) {
						tx_data.ADDRH=0x00;
						tx_data.ADDRL=0x06;
						SendTXData(&tx_data);
					}
					if(Range_Change) {
						if(Data_tmp->CURRMODE==CC_MODE)
							tx_data.ADDRH=0x01;
						else if(Data_tmp->CURRMODE==CR_MODE)
							tx_data.ADDRH=0x02;
						else if(Data_tmp->CURRMODE==CV_MODE)
							tx_data.ADDRH=0x03;
						tx_data.ADDRL=0x00;
						SendTXData(&tx_data);
					}
				}
				Data_tmp->CP.DYNA[Data_tmp->IRange].TIME2 = SettingCount;
				Disp_tmp->CP.DYNA[Data_tmp->IRange].TIME2 = SettingCount;
				Disp_tmp->CP.DYNA[Data_tmp->IRange].T2_RANGE = Data_tmp->CP.DYNA[Data_tmp->IRange].T2_RANGE;

				if((M_num==P_CP)&&(Disp_tmp->CP.STADYNA)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					DataRedrawFlag |= PARA_CHANGE;
					Draw_Set_parameter();					
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				tx_data.ADDRH=0x04;
				tx_data.ADDRL=0x56;
				SendTXData(&tx_data);

				if(Load_On_Status) {
					UTILITY.LOAD_CTL=0x01;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 0;
				}
			}
		}
	}
// Code End


}

void idPOWerFREQuency(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Precision_tmp,Load_On_Status=0;
	double Max=20000,Min=10,ResolutionTemp;

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;

// Code Begin
	if(P3k_Chan_Data.CONF.Dyna_Time==0) { //If value mode, return.
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min=(double)1.0;
				ExportProcess(Float_Data,Min,0,0,1);
			} else if (value.si==SCPI_MAX) {
				Max=(double)20000;
				ExportProcess(Float_Data,Max,0,0,1);
			}
		} else {
			switch (Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency_Range) {
			case Dyn_Freq_TimeBase_100Hz:
				ResolutionTemp=100;
				break;
			case Dyn_Freq_TimeBase_10Hz:
				ResolutionTemp =10;
				break;
			case Dyn_Freq_TimeBase_1Hz:
				ResolutionTemp=1;
				break;
			case Dyn_Freq_TimeBase_100mHz:
				ResolutionTemp=0.1;//0.1
				break;
			default:
				break;
			}
			ExportProcess(Float_Data,Disp_tmp->CP.DYNA[Disp_tmp->IRange].Frequency*ResolutionTemp,0,0,1);
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			if (value.d >= 1000) { //Freq>=10k Hz
				Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_100Hz;
				ResolutionTemp=100;
			} else if(value.d >= 100) { // 100 Hz <= Freq < 10k Hz
				Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_10Hz;
				ResolutionTemp=10;
			} else if(value.d >= 10) { // 10 Hz <= Freq < 100 Hz
				Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_1Hz;
				ResolutionTemp=1;
			} else if(value.d >= 0) { // 0 Hz <= Freq < 10 Hz
				Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_100mHz;
				ResolutionTemp=0.1;
			}
			if((value.d<=Max) && (value.d>=(Min/10))) {
				Disp_tmp->CP.DYNA[Disp_tmp->IRange].Frequency_Range=Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency_Range;
				Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency = SCPI_InputToStep(value.d,ResolutionTemp);
				Disp_tmp->CP.DYNA[Disp_tmp->IRange].Frequency=Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency;
				Command_Done=1;
			} else {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(0 == value.si) {
				Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_100mHz;
				Disp_tmp->CP.DYNA[Disp_tmp->IRange].Frequency_Range=Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency_Range;
				Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency=(UWORD)Min;
				Disp_tmp->CP.DYNA[Disp_tmp->IRange].Frequency=Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency;
				Command_Done=1;
			} else if(1 == value.si) {
				Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency_Range=Dyn_Freq_TimeBase_100Hz;
				Disp_tmp->CP.DYNA[Disp_tmp->IRange].Frequency_Range=Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency_Range;
				Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency=(UWORD)Max/100;
				Disp_tmp->CP.DYNA[Disp_tmp->IRange].Frequency=Data_tmp->CP.DYNA[Data_tmp->IRange].Frequency;
				Command_Done=1;
			}
			Command_Done = 1;

		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if(Data_tmp->CURRMODE!=CP_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CP_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CP.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CP.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
			}
			if((M_num==P_CP)&&(Disp_tmp->CP.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH=0x04;
			tx_data.ADDRL=0x40;
			SendTXData(&tx_data);

			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End
}

void idPOWerDUTY(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	double Min=1,Max=99,ResolutionTemp=0.1;
	UWORD SettingCount,max,min;
	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;

// Code Begin
	if(P3k_Chan_Data.CONF.Dyna_Time==0) { //If value mode, return.
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min=(double)1.0;
				ExportProcess(Float_Data,Min,0,0,1);
			} else if (value.si==SCPI_MAX) {
				Max=(double)99.0;
				ExportProcess(Float_Data,Max,0,0,1);
			}
		} else {
			ExportProcess(Float_Data,Data_tmp->CP.DYNA[Data_tmp->IRange].Duty*ResolutionTemp,0,0,1);
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {

			if((value.d > Max)||(value.d < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(value.d,ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(SCPI_MIN== value.si) {
				SettingCount =SCPI_InputToStep(Min,ResolutionTemp);
			} else if(SCPI_MAX== value.si) {
				SettingCount =SCPI_InputToStep(Max,ResolutionTemp);
			}
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Disp_tmp->CP.DYNA[Disp_tmp->IRange].Duty=SettingCount;
			Data_tmp->CP.DYNA[Data_tmp->IRange].Duty=SettingCount;
#if 1
			min = get_DynaFreqDutyRangeLimit(P_CP);
			max = 1000 - min;
			if(Data_tmp->CP.DYNA[Data_tmp->IRange].Duty<min)Data_tmp->CP.DYNA[Data_tmp->IRange].Duty=min;
			else if(Data_tmp->CP.DYNA[Data_tmp->IRange].Duty>max)Data_tmp->CP.DYNA[Data_tmp->IRange].Duty = max;
			Disp_tmp->CP.DYNA[Data_tmp->IRange].Duty = Data_tmp->CP.DYNA[Data_tmp->IRange].Duty;
#endif
			if(Data_tmp->CURRMODE!=CP_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CP_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CP.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CP.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
			}
			if((M_num==P_CP)&&(Disp_tmp->CP.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH=0x04;
			tx_data.ADDRL=0x40;
			SendTXData(&tx_data);

			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}

		}
	}
// Code End
}

void idPOWerRESPonse(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, SettingCount=0;
	p3k_send_tx_list tx_data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	char	str[20];
	unsigned char return_response;
	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

// Code Begin
	return_response = Data_tmp->CP.RESPONSE;
	if(scpi_IsQueryCommand(p)) {		
		if (return_response==SCPI_RESPonse_CVCP_FAST)
			ExportProcess(String_Data,0,0,"Fast",0);
		else if (return_response==SCPI_RESPonse_CVCP_NORMAL)
			ExportProcess(String_Data,0,0,"Normal",0);		
		else 
			ExportProcess(String_Data,0,0,"Slow",0);
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {			
			SettingCount=value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			
			if(return_response==SettingCount)return;
			Data_tmp->CP.RESPONSE = SettingCount;
			Disp_tmp->CP.RESPONSE = SettingCount;

			if((M_num <= P_CONF_Ext)&&(!PC_scriptrun)&&(!usbrun)) {
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
				ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				Draw_Set_parameter();
				MenuRedrawFlag|= MENU_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}				
			tx_data.ADDRH=0x04;
			tx_data.ADDRL=0x00;
			SendTXData(&tx_data);			
		}
	}
// Code End
}


void idPOWerCVRESPonse(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, SettingCount=0;
	p3k_send_tx_list tx_data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	char	str[20];
	unsigned char return_response;
	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

// Code Begin
	return_response = Data_tmp->CP.CXCV_RESPOSNE;
	if(scpi_IsQueryCommand(p)) {		
		if (return_response==SCPI_RESPonse_FAST)
			ExportProcess(String_Data,0,0,"Fast",0);
		else
			ExportProcess(String_Data,0,0,"Slow",0);		
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {			
			SettingCount=value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			
			if(return_response==SettingCount)return;
			Data_tmp->CP.CXCV_RESPOSNE = SettingCount;
			Disp_tmp->CP.CXCV_RESPOSNE = SettingCount;

			if((M_num <= P_CONF_Ext)&&(!PC_scriptrun)&&(!usbrun)) {
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
				ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				MenuRedrawFlag|= MENU_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}				
			tx_data.ADDRH=0x04;
			tx_data.ADDRL=0x00;
			SendTXData(&tx_data);
			
		}
	}
// Code End
}

void idFUNCtionCOMPleteRINGTIME(STR_PARSER * p)
{
#if Enable_Ring_Count
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	UWORD Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[40];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	ResolutionTemp=1;;
	Precision = 0;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==0) {
				Min=0;
				ExportProcess(Integer_Data,0,Min,0,Precision);
			} else {
				Max=600;
				ExportProcess(Integer_Data,0,Max,0,Precision);
			}
		} else {			
			SettingCount = Data_tmp->PROT.SEQ_Tone_len-1;
			Real_Value = (double)SettingCount*ResolutionTemp;
			if(Real_Value==601)
				ExportProcess(String_Data, 0, 0,"Infinity", 0);
			else if(Real_Value==0)
				ExportProcess(String_Data, 0, 0,"OFF", 0);	
			else
				ExportProcess(Integer_Data, 0, Real_Value, 0, Precision);			
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Max=600;
			Min=0;
			if((value.d > Max)||(value.d < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(value.d , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si))	
			if(value.si<2) {
				SettingCount = (1 == value.si) ? 600 : 0;
				Command_Done = 1;
			} else if(value.si==2){
				SettingCount = 601;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}	
		if(Command_Done) {
			Data_tmp->PROT.SEQ_Tone_len = SettingCount+1;
			Disp_tmp->PROT.SEQ_Tone_len = SettingCount+1;
			if(((M_num==P_Seq_FUNC)||(M_num==P_FUNC_MAIN))&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;				
			}
		}
	}
		// Code End
#endif

}

void idPROGramSTATe(STR_PARSER * p) //check it, how to do when loadon,
{
	GW_TYPE value;
	UBYTE Command_Done=0, SettingBool;
	BYTE k;
	P3k_Prog_Str		*Prog_Disp_tmp = &p3k_Disp_PROG;
	P3k_Prog_Str		*Prog_Change_tmp = &p3k_Chan_PROG;
	p3k_send_tx_list tx_data;
	UBYTE *Prog_ON_OFF=&Prog_Disp_tmp->SPEC;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if (P3k_Disp_Data.Load_Type!=SCPI_UTI_Other_On)
			ExportProcess(String_Data,0,0,"OFF",0);
		else {
			if(P_PROG_EXECUTE != M_num)
				ExportProcess(String_Data,0,0,"ON,STOP",0);
			else if((Prog_Seq_Data.SEQ_Stop_Continue==0x01)||(Prog_Seq_Data.MANUAL_CTRL==1))
				ExportProcess(String_Data,0,0,"ON,PAUSE",0);
			else
				ExportProcess(String_Data,0,0,"ON,RUN",0);
		}
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = value.si;
			if(SettingBool<2)
				Command_Done = 1;
			else if(SettingBool<4)
				Command_Done = 2;
			else if(SettingBool==4)
				Command_Done = 3;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			asm("nop;");
			P3k_Chan_Data.Load_Type = SettingBool;
			P3k_Disp_Data.Load_Type = SettingBool;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				SysRedrawFlag |= PROG_UPDATA + BG_CLEAR_FLAG;
				MenuRedrawFlag |= MENU1_CHANGE;
			}
		} else if(Command_Done==2) {
			if(P_PROG_EXECUTE == M_num) {
				if(Prog_Seq_Data.SEQ_Stop_Continue==2)return;
				if(Prog_Seq_Data.MANUAL_CTRL)return;
				//if(P3k_Chan_Data.CONF.Ext_Setting.MultilPara)return;
				Prog_Seq_Data.SEQ_Stop_Continue = (2 == SettingBool) ? 1 : 0;
				if(Stop_Next_Proc==1) {
					Stop_Next_Proc=0;
					Prog_Seq_Next(0,0);
				}
				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = Machine_Pause_Prog;
				SendTXData(&tx_data);
				MenuRedrawFlag |= MENU1_CHANGE;
			}
		} else if(Command_Done==3) {
			if(P_PROG_EXECUTE == M_num) {
				//if(P3k_Chan_Data.CONF.Ext_Setting.MultilPara)return;
				if(Prog_Seq_Data.MANUAL_CTRL) {
					Prog_Seq_Data.MANUAL_CTRL = 0x0;
					MenuRedrawFlag |= MENU2_CHANGE;
					if(Display_Continue==Prog_Seq_Data.SEQ_Stop_Continue) {
						Stop_Next_Proc=1;
						return;
					}
					tx_data.ADDRH = Machine_Command;
					tx_data.ADDRL = Machine_Input_Trigger;
					SendTXData(&tx_data);
				}
			}
		}
	}
// Code End

}
typedef struct	{
	UBYTE Prog_No;		/* 	Progam  0~15		   */
	UBYTE Step_No;		/*	Step No  0~15	   */
	UWORD Momory;		/*	0~255	          	   */
	UBYTE RunMode;		/*	Skip,Auto,Manual	   */
	UWORD OnTime;		/*	0.1 ~ 60	          	   */
	UWORD OffTime;		/*	0   ~  60	                */
	UWORD PFTime;		/* 0~ontime+offtime-0.1  */
	UWORD ShortTime;	/*	0  ~  ontime	           */
} ProgStr;
#define Backup					1


void idPROGram(STR_PARSER * p)//AAAAA
{
	GW_TYPE value;
	ProgStr S;

	UBYTE Command_Done ;
	char str[128],index_for_items,j;
	double Time_Resolution=0.1;
	P3k_Prog_Str		*Prog_Disp_tmp = &p3k_Disp_PROG;
	P3k_Prog_Str		*Prog_Change_tmp = &p3k_Chan_PROG;

	//Turns Program On/Off
	UBYTE *Prog_ON_OFF=&Prog_Disp_tmp->SPEC;	/*	Run Program 0=Off, 1=On			*/
	char ON_OFF[2][4]= {"OFF","ON"};

	//Start~Memory
	UBYTE Prog_Start=Prog_Disp_tmp->Prog_No+1;
	UBYTE Prog_Step=Prog_Disp_tmp->Step_No+1;
	UWORD Prog_Memory=Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].MEMORY[Prog_Disp_tmp->Step_No]+1;
	UBYTE *Prog_Start_Step_Memory;	//Start, Step, and Memory were used the same pointer "*Timing"

	//Run Mode
	char Run[3][6]= {"Skip","Auto","Manual"};
	UBYTE *Run_Mode=&Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].RUNMODE[Prog_Disp_tmp->Step_No];

	//Timing
	double On_Time=(double)Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].ONTIME[Prog_Disp_tmp->Step_No]/10;
	double Off_Time=(double)Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].OFFTIME[Prog_Disp_tmp->Step_No]/10;
	double Pass_Fail_Time=(double)Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].PFTIME[Prog_Disp_tmp->Step_No]/10;
	double Short_Time=(double)Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].SHORTTIME[Prog_Disp_tmp->Step_No]/10;
	UWORD *Timing;	//On-Time, Off-Time, Pass/Fail-Time and short time were used the same pointer "*Timing"
	Command_Done =1;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Start:%d, Step:%d, Memory:%d, Run:%s, On-Time:%.1f, Off-Time:%.1f, P/F-Time:%.1f, Short-Time:%.1f"
		        ,Prog_Start,Prog_Step,Prog_Memory,Run[*Run_Mode],On_Time,Off_Time,Pass_Fail_Time,Short_Time);
		ExportProcess(String_Data,0,0,str,0);
	} else {

		//prog :0
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si<SCPI_Program_Step_Lower)||(value.si>SCPI_Program_Step_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			S.Prog_No = value.si;
		} else
			Command_Done =0;
		//step :1
		if(0 == scpi_GetIntegerParameters( p, 1, (int*) &value.si)) {
			if((value.si<SCPI_Program_Step_Lower)||(value.si>SCPI_Program_Step_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			S.Step_No = value.si;
		} else
			Command_Done =0;
		//momory :2
		if(0 == scpi_GetIntegerParameters( p, 2, (int*) &value.si)) {
			if((value.si<SCPI_Program_Memory_Lower)||(value.si>SCPI_Program_Memory_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			S.Momory= value.si;
		} else
			Command_Done =0;
		//Run Mode :3
		if(0 == scpi_GetKeywordParameters( p, 3, (int*) &value.si)) {
			if((value.si<0)||(value.si>2)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			S.RunMode = value.si;
		} else
			Command_Done =0;
		//ontime :4
		if(0 == scpi_GetFloatIntegerParameters( p, 4, (double*) &value.d)) {
			if((value.d<SCPI_Program_Timing_Lower)||(value.d>SCPI_Program_Timing_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			S.OnTime = SCPI_InputToStep(value.d,Time_Resolution);
		} else
			Command_Done =0;
		//offtime :5
		if(0 == scpi_GetFloatIntegerParameters( p, 5, (double*) &value.d)) {
			if((value.d<0)||(value.d>SCPI_Program_Timing_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			S.OffTime = SCPI_InputToStep(value.d,Time_Resolution);
		} else if(0 == scpi_GetKeywordParameters( p, 5, (int*) &value.si)) {
			S.OffTime = value.si;
		} else
			Command_Done =0;
		//pftime :6
		if(0 == scpi_GetFloatIntegerParameters( p, 6, (double*) &value.d)) {
			if((value.d<0)||(value.d>SCPI_Program_Timing_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			S.PFTime = SCPI_InputToStep(value.d,Time_Resolution);
		} else if(0 == scpi_GetKeywordParameters( p, 6, (int*) &value.si)) {
			S.PFTime= value.si;
		} else
			Command_Done =0;
		//shorttime :7

		if(0 == scpi_GetFloatIntegerParameters( p, 7, (double*) &value.d)) {
			if((value.d<0)||(value.d>SCPI_Program_Timing_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			S.ShortTime = SCPI_InputToStep(value.d,Time_Resolution);
		} else if(0 == scpi_GetKeywordParameters( p, 7, (int*) &value.si)) {
			S.ShortTime= value.si;
		} else
			Command_Done =0;
		if(Command_Done==0) {
			scpi_SetCommandError( p, _ERR_220_Parameter_error);
			return;
		}

		if(((S.OffTime+S.OnTime-1)<S.PFTime)||(S.OnTime<S.ShortTime)) {
			scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
			return;
		} else
			Command_Done =1;
		if(Command_Done) {
			//prog :0
			Prog_Disp_tmp->Prog_No = S.Prog_No-1;
			//step :1
			Prog_Disp_tmp->Step_No = S.Step_No-1;
			//momory :2
			Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].MEMORY[Prog_Disp_tmp->Step_No]=S.Momory-1;
			//run mode :3
			Run_Mode=&Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].RUNMODE[Prog_Disp_tmp->Step_No];
			*Run_Mode=S.RunMode;
			//ontime :4
			Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].ONTIME[Prog_Disp_tmp->Step_No]= S.OnTime;
			//offtime :5
			Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].OFFTIME[Prog_Disp_tmp->Step_No]=S.OffTime;
			//pftime :6
			Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].PFTIME[Prog_Disp_tmp->Step_No]=S.PFTime;
			//shortime :7
			Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].SHORTTIME[Prog_Disp_tmp->Step_No]=S.ShortTime;
			*Prog_Change_tmp=*Prog_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if(/*(M_num==P_PROG_MAIN)&&*/(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				ChanRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				Draw_Set_parameter();
				SysRedrawFlag |= PROG_UPDATA + BG_CLEAR_FLAG;
				MenuRedrawFlag |= MENU1_CHANGE;
				MenuRedrawFlag|=MENU3_CHANGE;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_Prog_Data(Backup);
		}



	}
// Code End
}

void idPROGramRECallDEFault(STR_PARSER * p)
{
	GW_TYPE value;
	BYTE M_num_tmp;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		M_num_tmp=M_num;
		M_num=P_PROG_MAIN;
		Recall_Data(0,0);
		SEQ_Save_Status=1;
		Soft_Key_Temp=0;
		if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu))
			MenuRedrawFlag|=MENU3_CHANGE;
		M_num=M_num_tmp;
		SCPI_RemFastDelay = 1;
	}
// Code End
}

void idPROGramSTARt(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE SettingCount;
	UBYTE Command_Done=0;
	P3k_Prog_Str		*Prog_Disp_tmp = &p3k_Disp_PROG;
	P3k_Prog_Str		*Prog_Change_tmp = &p3k_Chan_PROG;
	char str[16];
	//Start
	UBYTE *Prog_Start=&Prog_Disp_tmp->Prog_No;
	UBYTE *Prog_Step=&Prog_Disp_tmp->Step_No;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Start:%d",*Prog_Start+1);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si < SCPI_Program_Step_Lower)||(value.si > SCPI_Program_Step_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			*Prog_Start =SettingCount;
			asm("nop;");
			*Prog_Change_tmp=*Prog_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag|=MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				Draw_Set_parameter();
				SysRedrawFlag |= PROG_UPDATA + BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_Prog_Data(Backup);
		}
	}
// Code End
}

void idPROGramSTEP(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE SettingCount;
	UBYTE Command_Done=0;
	P3k_Prog_Str		*Prog_Disp_tmp = &p3k_Disp_PROG;
	P3k_Prog_Str		*Prog_Change_tmp = &p3k_Chan_PROG;
	char str[16];
	UBYTE *Prog_Step=&Prog_Disp_tmp->Step_No;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Step:%d",*Prog_Step+1);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si < SCPI_Program_Step_Lower)||(value.si > SCPI_Program_Step_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			*Prog_Step = SettingCount-1;
			asm("nop;");
			*Prog_Change_tmp=*Prog_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag|=MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				Draw_Set_parameter();
				SysRedrawFlag |= PROG_UPDATA + BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_Prog_Data(Backup);
		}
	}
// Code End

}

void idPROGramMEMory(STR_PARSER * p)
{
	GW_TYPE value;
	UWORD SettingCount;
	UBYTE Command_Done=0;
	P3k_Prog_Str		*Prog_Disp_tmp = &p3k_Disp_PROG;
	P3k_Prog_Str		*Prog_Change_tmp = &p3k_Chan_PROG;
	char str[16];

	//Memory
	UBYTE *Prog_Memory=&Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].MEMORY[Prog_Disp_tmp->Step_No];

	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Memory:M%3d",*Prog_Memory+1);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si < SCPI_Program_Memory_Lower)||(value.si > SCPI_Program_Memory_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			*Prog_Memory = SettingCount-1;
			asm("nop;");
			*Prog_Change_tmp=*Prog_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag|=MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				Draw_Set_parameter();
				SysRedrawFlag |= PROG_UPDATA + BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_Prog_Data(Backup);
		}
	}
	// Code End

}

void idPROGramRUN(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE SettingCount;
	UBYTE Command_Done=0;
	P3k_Prog_Str		*Prog_Disp_tmp = &p3k_Disp_PROG;
	P3k_Prog_Str		*Prog_Change_tmp = &p3k_Chan_PROG;
	char str[16];

	//Run Mode
	char Run[3][6]= {"Skip","Auto","Manual"};
	UBYTE *Run_Mode=&Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].RUNMODE[Prog_Disp_tmp->Step_No];

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Run:%s",Run[*Run_Mode]);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = value.si;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			*Run_Mode = SettingCount;
			asm("nop;");
			*Prog_Change_tmp=*Prog_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag|=MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				Draw_Set_parameter();
				SysRedrawFlag |= PROG_UPDATA + BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_Prog_Data(Backup);
		}
	}
// Code End
}

void idPROGramONTime(STR_PARSER * p)
{
	GW_TYPE value;
	ProgStr S;
	UWORD SettingCount;

	UBYTE Command_Done=0;
	char str[16];
	double ResolutionTemp =0.1;
	P3k_Prog_Str		*Prog_Disp_tmp = &p3k_Disp_PROG;
	P3k_Prog_Str		*Prog_Change_tmp = &p3k_Chan_PROG;

	//Timing
	float On_Time=(float)(Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].ONTIME[Prog_Disp_tmp->Step_No]*ResolutionTemp);
	UWORD *Timing=&Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].ONTIME[Prog_Disp_tmp->Step_No];


	S.OffTime = Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].OFFTIME[Prog_Disp_tmp->Step_No];
	S.PFTime = Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].PFTIME[Prog_Disp_tmp->Step_No];
	S.ShortTime = Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].SHORTTIME[Prog_Disp_tmp->Step_No];

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"On-Time:%.1f",On_Time);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			if((value.d > SCPI_Program_Timing_Upper)||(value.d < SCPI_Program_Timing_Lower)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			} else {
				S.OnTime = SCPI_InputToStep(value.d , ResolutionTemp);
				if(((S.OffTime+S.OnTime-1)<S.PFTime)||(S.OnTime<S.ShortTime)) {
					scpi_SetCommandError( p, _ERR_221_Settings_conflict);
					return;
				}
			}
			SettingCount = S.OnTime;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			*Timing = SettingCount;
			asm("nop;"); //be safe
			*Prog_Change_tmp=*Prog_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag|=MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				Draw_Set_parameter();
				SysRedrawFlag |= PROG_UPDATA + BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_Prog_Data(Backup);
		}
	}
// Code End
}

void idPROGramOFFTime(STR_PARSER * p)
{
	GW_TYPE value;
	ProgStr S;
	UWORD SettingCount;

	UBYTE Command_Done=0;
	char str[16];
	double ResolutionTemp =0.1;
	P3k_Prog_Str		*Prog_Disp_tmp = &p3k_Disp_PROG;
	P3k_Prog_Str		*Prog_Change_tmp = &p3k_Chan_PROG;


	//Timing
	float Off_Time=(float)(Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].OFFTIME[Prog_Disp_tmp->Step_No]*ResolutionTemp);
	UWORD *Timing=&Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].OFFTIME[Prog_Disp_tmp->Step_No];
	S.PFTime = Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].PFTIME[Prog_Disp_tmp->Step_No];
	S.ShortTime = Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].SHORTTIME[Prog_Disp_tmp->Step_No];
	S.OnTime = Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].ONTIME[Prog_Disp_tmp->Step_No];


// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Off-Time:%.1f",Off_Time);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			if((value.d > SCPI_Program_Timing_Upper)||(value.d < 0)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			} else
				S.OffTime = SCPI_InputToStep(value.d , ResolutionTemp);
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			S.OffTime = 0;

		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(((S.OffTime+S.OnTime-1)<S.PFTime)||(S.OnTime<S.ShortTime)) {
			scpi_SetCommandError( p, _ERR_221_Settings_conflict);
			return;
		}
		SettingCount = S.OffTime;
		Command_Done=1;
		if(Command_Done==1) {
			*Timing = SettingCount;
			asm("nop;"); //be safe
			*Prog_Change_tmp=*Prog_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag|=MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				Draw_Set_parameter();
				SysRedrawFlag |= PROG_UPDATA + BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_Prog_Data(Backup);
		}
	}
// Code End

}

void idPROGramPFTime(STR_PARSER * p)
{
	GW_TYPE value;
	ProgStr S;
	UWORD SettingCount;

	UBYTE Command_Done=0;
	char str[16];
	double ResolutionTemp =0.1;
	P3k_Prog_Str		*Prog_Disp_tmp = &p3k_Disp_PROG;
	P3k_Prog_Str		*Prog_Change_tmp = &p3k_Chan_PROG;


	//Timing
	float Pass_Fail_Time=(float)(Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].PFTIME[Prog_Disp_tmp->Step_No]*ResolutionTemp);
	UWORD *Timing=&Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].PFTIME[Prog_Disp_tmp->Step_No];
	S.OffTime = Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].OFFTIME[Prog_Disp_tmp->Step_No];
	S.ShortTime = Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].SHORTTIME[Prog_Disp_tmp->Step_No];
	S.OnTime = Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].ONTIME[Prog_Disp_tmp->Step_No];
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"P/F-Time:%.1f",Pass_Fail_Time);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			if((value.d > 120)||(value.d < 0)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			} else
				S.PFTime = SCPI_InputToStep(value.d , ResolutionTemp);
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			S.PFTime = 0;

		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(((S.OffTime+S.OnTime-1)<S.PFTime)||(S.OnTime<S.ShortTime)) {
			scpi_SetCommandError( p, _ERR_221_Settings_conflict);
			return;
		}
		SettingCount = S.PFTime;
		Command_Done=1;
		if(Command_Done==1) {
			*Timing = SettingCount;
			asm("nop;"); //be safe
			*Prog_Change_tmp=*Prog_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |=MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				Draw_Set_parameter();
				SysRedrawFlag |= PROG_UPDATA + BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_Prog_Data(Backup);
		}
	}
// Code End
}

void idPROGramSTIMe(STR_PARSER * p)
{
	GW_TYPE value;
	ProgStr S;
	UWORD SettingCount;

	UBYTE Command_Done=0;
	char str[16];
	double ResolutionTemp =0.1;
	P3k_Prog_Str		*Prog_Disp_tmp = &p3k_Disp_PROG;
	P3k_Prog_Str		*Prog_Change_tmp = &p3k_Chan_PROG;


	//Timing

	float Short_Time=(float)(Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].SHORTTIME[Prog_Disp_tmp->Step_No]*ResolutionTemp);
	UWORD *Timing=&Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].SHORTTIME[Prog_Disp_tmp->Step_No];
	S.OffTime = Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].OFFTIME[Prog_Disp_tmp->Step_No];
	S.PFTime = Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].PFTIME[Prog_Disp_tmp->Step_No];
	S.OnTime =Prog_Disp_tmp->Timing_Data[Prog_Disp_tmp->Prog_No].ONTIME[Prog_Disp_tmp->Step_No];
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Short-Time:%.1f",Short_Time);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			if((value.d > 120)||(value.d < 0)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			} else
				S.ShortTime = SCPI_InputToStep(value.d , ResolutionTemp);
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			S.ShortTime = 0;

		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(((S.OffTime+S.OnTime-1)<S.PFTime)||(S.OnTime<S.ShortTime)) {
			scpi_SetCommandError( p, _ERR_221_Settings_conflict);
			return;
		}
		SettingCount = S.ShortTime;
		Command_Done=1;
		if(Command_Done==1) {
			*Timing = SettingCount;
			asm("nop;"); //be safe
			*Prog_Change_tmp=*Prog_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |=MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + PARA_CHANGE_Fast + BG_CLEAR;
				Draw_Set_parameter();
				SysRedrawFlag |= PROG_UPDATA + BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_Prog_Data(Backup);
		}
	}
// Code End
}


void idPROGramCHAinSTARt(STR_PARSER * p)
{
	GW_TYPE value;
	UWORD SettingCount;

	UBYTE Command_Done=0;
	char str[8];
	P3k_Prog_Str		*Prog_Disp_tmp = &p3k_Disp_PROG;
	P3k_Prog_Str		*Prog_Change_tmp = &p3k_Chan_PROG;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"P%d",Prog_Disp_tmp->Chain_Start_Prog+1);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si < 1)||(value.si > 16)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Prog_Disp_tmp->Chain_Start_Prog=SettingCount-1;
			Prog_Change_tmp->Chain_Start_Prog=Prog_Disp_tmp->Chain_Start_Prog;
			SEQ_Save_Status = 1;
			Soft_Key_Temp	= 0;
			if(/*(M_num==P_PROG_CHAIN)&&*/(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				MenuRedrawFlag|=MENU3_CHANGE;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_Prog_Data(Backup);
		}
	}
// Code End
}


void idPROGramCHAin(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE SettingCount[16];

	UBYTE Command_Done=0;
	char str[16],index;
	P3k_Prog_Str		*Prog_Disp_tmp = &p3k_Disp_PROG;
	P3k_Prog_Str		*Prog_Change_tmp = &p3k_Chan_PROG;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		for (index=0; index<16; index++) {
			if (Prog_Disp_tmp->PROGSEQ[index]==0)
				sprintf(str,"P%d->Off",index+1);
			else sprintf(str,"P%d->P%d",index+1,Prog_Disp_tmp->PROGSEQ[index]);
			ExportProcess(String_Data,0,0,str,0);
		}
	} else {
		for (index=0; index<16; index++) {
			if(0 == scpi_GetIntegerParameters( p, index, (int*) &value.si)) {
				if((value.si < SCPI_Program_Step_Lower)||(value.si > SCPI_Program_Step_Upper)) {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
				SettingCount[index] = value.si;
			} else if(0 == scpi_GetKeywordParameters( p, index, (int*) &value.si)) {
				SettingCount[index] = 0;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}
		}
		Command_Done=1;
		if(Command_Done==1) {
			for (index=0; index<16; index++) {
				Prog_Disp_tmp->PROGSEQ[index]=SettingCount[index];
			}
			asm("nop;"); //be safe
			*Prog_Change_tmp->PROGSEQ=*Prog_Disp_tmp->PROGSEQ;
			SEQ_Save_Status = 1;
			Soft_Key_Temp	= 0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				MenuRedrawFlag|=MENU3_CHANGE;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_Prog_Data(Backup);
		}
	}
// Code End
}


void idPROGramCHAinP2P(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE SettingCount[2];

	UBYTE Command_Done=0;
	char str[16],index;
	P3k_Prog_Str		*Prog_Disp_tmp = &p3k_Disp_PROG;
	P3k_Prog_Str		*Prog_Change_tmp = &p3k_Chan_PROG;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			index = value.si;
			if (Prog_Disp_tmp->PROGSEQ[index]==0)
				sprintf(str,"P%d->Off",index+1);
			else sprintf(str,"P%d->P%d",index+1,Prog_Disp_tmp->PROGSEQ[index]);
			ExportProcess(String_Data,0,0,str,0);
		} else {
			scpi_SetCommandError( p, _ERR_109_Missing_parameter);
		}
	} else {
		for (index=0; index<2; index++) {
			if(0 == scpi_GetIntegerParameters( p, index, (int*) &value.si)) {
				if((value.si < SCPI_Program_Step_Lower)||(value.si > SCPI_Program_Step_Upper)) {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
				SettingCount[index] = value.si;
			} else if(0 == scpi_GetKeywordParameters( p, index, (int*) &value.si)) {
				SettingCount[index] = 0;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}
		}
		Command_Done=1;
		if(Command_Done==1) {
			Prog_Disp_tmp->PROGSEQ[SettingCount[0]-1]= SettingCount[1];
			asm("nop;"); //be safe
			*Prog_Change_tmp->PROGSEQ=*Prog_Disp_tmp->PROGSEQ;
			SEQ_Save_Status = 1;
			Soft_Key_Temp	= 0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				Draw_Set_parameter();				
				MenuRedrawFlag|=MENU3_CHANGE;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_Prog_Data(Backup);
		}
	}
// Code End

}


void idPROGramCHAinRECallDEFault(STR_PARSER * p)
{
	UBYTE i;
	P3k_Prog_Str		*Prog_Disp_tmp = &p3k_Disp_PROG;
	P3k_Prog_Str		*Prog_Change_tmp = &p3k_Chan_PROG;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		for(i=0; i<16; i++) {
			Prog_Disp_tmp->PROGSEQ[i]=0;
		}
		Prog_Disp_tmp->Chain_Start_Prog=0;
		asm("nop;"); //be safe
		*Prog_Change_tmp=*Prog_Disp_tmp;
		SaveRecall_Prog_Data(Backup);
		SEQ_Save_Status = 1;
		Soft_Key_Temp	= 0;
		if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
			DataRedrawFlag |= PARA_CHANGE;
			Draw_Set_parameter();			
			MenuRedrawFlag|=MENU3_CHANGE;
		}
		SEQ_Save_Status=0;
		Soft_Key_Temp=0;
	}
// Code End
}


void idPROGramSAVE(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		p3k_Chan_PROG = p3k_Disp_PROG;
		SEQ_Save_Status = 0;
		if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
			MenuRedrawFlag |= MENU3_CHANGE;
			DispMode = DispMode_SELECT_CH;
			DataRedrawFlag |= PARA_CHANGE;
		}
		BackupRunProg();
		SCPI_RemFastDelay = 1;
	}
// Code End
}

void idSEQuenceCOMPleteRINGTIME(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	UWORD Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[40];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	ResolutionTemp=1;;
	Precision = 0;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==0) {
				Min=0;
				ExportProcess(Integer_Data,0,Min,0,Precision);
			} else {
				Max=600;
				ExportProcess(Integer_Data,0,Max,0,Precision);
			}
		} else {			
			SettingCount = Data_tmp->PROT.SEQ_Tone_len-1;
			Real_Value = (double)SettingCount*ResolutionTemp;
			if(Real_Value==601)
				ExportProcess(String_Data, 0, 0,"Infinity", 0);
			else if(Real_Value==0)
				ExportProcess(String_Data, 0, 0,"OFF", 0);	
			else
				ExportProcess(Integer_Data, 0, Real_Value, 0, Precision);			
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Max=600;
			Min=0;
			if((value.d > Max)||(value.d < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(value.d , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si))	
			if(value.si<2) {
				SettingCount = (1 == value.si) ? 600 : 0;
				Command_Done = 1;
			} else if(value.si==2){
				SettingCount = 601;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_310_System_error);
				return;
			}	
		if(Command_Done) {
			Data_tmp->PROT.SEQ_Tone_len = SettingCount+1;
			Disp_tmp->PROT.SEQ_Tone_len = SettingCount+1;
			if(((M_num==P_Seq_FUNC)||(M_num==P_FUNC_MAIN))&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag|= PARA_CHANGE;				
			}
		}
	}
		// Code End
}

void idNSEQuenceCOTime(STR_PARSER * p)
{
#if Enable_Func_DisTime
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingBool;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(P3k_Chan_Data.CONF.T_count_up == SCPI_UTI_Other_On)
			ExportProcess(String_Data,0,0,"UP",0);
		else
			ExportProcess(String_Data,0,0,"DOWN",0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 0 : 1;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 0 : 1;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			P3k_Chan_Data.CONF.T_count_up = SettingBool;
			P3k_Disp_Data.CONF.T_count_up = SettingBool;
			
			if(((M_num==P_Seq_FUNC)||(M_num==P_FUNC_MAIN))&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
			}
			
		}
	}
#endif

}
void idNSEQuenceTIMer(STR_PARSER * p)
{
#if Enable_Func_DisTime
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingBool;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(P3k_Chan_Data.CONF.T_count_up == SCPI_UTI_Other_On)
			ExportProcess(String_Data,0,0,"Elapsed",0);
		else
			ExportProcess(String_Data,0,0,"Remaining",0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 0 : 1;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 0 : 1;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			P3k_Chan_Data.CONF.T_count_up = SettingBool;
			P3k_Disp_Data.CONF.T_count_up = SettingBool;
			
			if(((M_num==P_Seq_FUNC)||(M_num==P_FUNC_MAIN))&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
			}
			
		}
	}
#endif

}


void idNSEQuenceSTATe(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, SettingBool;

	P3k_NSeq_Str *NSeq_Data_tmp = &P3k_NSeq_Data;
	P3k_NSeq_Str *NSeq_Disp_tmp = &P3k_NSeq_Disp;
	p3k_send_tx_list tx_data;
	UBYTE *NSeq_Enable = &NSeq_Disp_tmp->NSeq_Enable;
	*NSeq_Enable=(UBYTE)Command_Temp.DataList1.kwvalue[0];

	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;


// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if (P3k_Disp_Data.Load_Type!=SCPI_Normal_Sequence)
			ExportProcess(String_Data,0,0,"OFF",0);
		else {
			if(P_NSeq_EXECUTE != M_num)
				ExportProcess(String_Data,0,0,"ON,STOP",0);
			else if((Prog_Seq_Data.SEQ_Stop_Continue==0x01)||(Prog_Seq_Data.MANUAL_CTRL==1))
				ExportProcess(String_Data,0,0,"ON,PAUSE",0);
			else
				ExportProcess(String_Data,0,0,"ON,RUN",0);
		}
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? SCPI_Normal_Sequence : SCPI_Load;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = value.si;
			if(SettingBool<2) {
				SettingBool = (1 == value.si) ? SCPI_Normal_Sequence : SCPI_Load;
				Command_Done = 1;
			} else if(SettingBool<4)
				Command_Done = 2;
			else if(SettingBool==4)
				Command_Done = 3;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			P3k_Chan_Data.Load_Type = SettingBool;
			P3k_Disp_Data.Load_Type = SettingBool;
			asm("nop;");
			*NSeq_Data_tmp=*NSeq_Disp_tmp;
			if(/*(M_num==P_PROG_MAIN)&&*/(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				SysRedrawFlag |= PROG_UPDATA + BG_CLEAR_FLAG;
				MenuRedrawFlag |= MENU1_CHANGE;
			}
		} else if(Command_Done==2) {
			if(P_NSeq_EXECUTE == M_num) {
				if(Prog_Seq_Data.SEQ_Stop_Continue==2)return;
				if(Prog_Seq_Data.MANUAL_CTRL)return;
				//if(P3k_Chan_Data.CONF.Ext_Setting.MultilPara)return;
				Prog_Seq_Data.SEQ_Stop_Continue = (2 == SettingBool) ? 1 : 0;
				if(Stop_Next_Proc==1) {
					Stop_Next_Proc=0;
					Prog_Seq_Next(0,0);
				}
				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = Machine_Pause_Prog;
				SendTXData(&tx_data);
				MenuRedrawFlag |= MENU1_CHANGE;
			}
		} else if(Command_Done==3) {
			if(P_NSeq_EXECUTE == M_num) {
				//if(P3k_Chan_Data.CONF.Ext_Setting.MultilPara)return;
				if(Prog_Seq_Data.MANUAL_CTRL) {
					Prog_Seq_Data.MANUAL_CTRL = 0x0;
					MenuRedrawFlag |= MENU2_CHANGE;
					if(Display_Continue==Prog_Seq_Data.SEQ_Stop_Continue) {
						Stop_Next_Proc=1;
						return;
					}
					tx_data.ADDRH = Machine_Command;
					tx_data.ADDRL = Machine_Input_Trigger;
					SendTXData(&tx_data);
				}
			}
		}
	}
// Code End
}
typedef struct	{
	UBYTE StartNo;		/* 	Progam  0~9		   */
	UBYTE SeqNo;		/*	Step No  0~9	   */
	char Memo[28];/*	NSEQ name	   */
	UBYTE Mode;			/*	CC,CR,CV,CP	   */
	UBYTE Range;		/*	ILVL,IMVL,IHVL,ILVH,IMVH,VHVH 	   */
	UWORD Loop;			/*	0~9999	                */
	UBYTE LastLoad;		/*   on/off				  */
	double LastValue;	/*	SettingValue	           */
	ULONG LastValueCount;	/*	SettingValue	           */
	UBYTE Chain;
} NSEQStr;

void idNSEQuence(STR_PARSER * p)
{
	GW_TYPE value;
	int length=0;
	NSEQStr N;

	UBYTE Command_Done=1;
	P3k_NSeq_Str *NSeq_Data_tmp = &P3k_NSeq_Data;
	P3k_NSeq_Str *NSeq_Disp_tmp = &P3k_NSeq_Disp;
	char str[128],index;
	double Para_s;

	//Normal Sequence On/Off
	UBYTE *NSeq_Enable = &NSeq_Disp_tmp->NSeq_Enable;
	char NSeq_ON_OFF_String[4];
	Para_s = Get_Parallel_Parameter(1);

	if (P3k_Disp_Data.Load_Type==SCPI_Normal_Sequence)
		sprintf(NSeq_ON_OFF_String,"%s","ON");
	else sprintf(NSeq_ON_OFF_String,"%s","OFF");

	//Start No
	UBYTE *NSeq_Start = &NSeq_Disp_tmp->NSeq_Start;
	//Seq No
	UBYTE *NSeq_Seq_No = &NSeq_Disp_tmp->NSeq_Number;
	//CC, CR Mode
	double Resolution_tmp;
	UWORD Max_tmp,Min_tmp;
	BYTE Precision_tmp;
	UBYTE V_Range = NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range/2;
	UBYTE I_Range = NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range%2;
	//Normal Sequence Memo Name
	UBYTE *NSeq_Memo = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Memo[0];
	UBYTE index_for_NSeq_memo;
	//Mode and its String
	UBYTE *NSeq_Mode = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Mode;
	char NSeq_Mode_String[4][3]= {"CC","CR","CV","CP"};
	//Range and its String
	UBYTE *NSeq_Range = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range;
	char NSeq_Range_String[4][5]= {"ILVL","IHVL","ILVH","IHVH"};
	//Loop and its String
	UWORD *NSeq_Loop = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Loop;
	char Loop_String[9];
	if (*NSeq_Loop==SCPI_NSEQ_Loop_Infinity)
		sprintf(Loop_String,"%s","Infinity");
	else sprintf(Loop_String,"%d",*NSeq_Loop);
	//Chain and its String
	UBYTE *NSeq_Chain = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Chain;
	char NSeq_Chain_String[4];
	if (*NSeq_Chain==SCPI_NSEQ_Chain_Off)
		sprintf(NSeq_Chain_String,"%s","Off");
	else sprintf(NSeq_Chain_String,"%d",*NSeq_Chain);
	//Last Load and its String
	UBYTE *NSeq_Last_Load = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Last_Load;
	char Last_Load_String[2][4]= {"OFF","ON"};
	//Last Value
	UWORD *NSeq_Last_Level = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Last_Level;

	if(*NSeq_Mode==CC_MODE) {
		Resolution_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
	} else if (*NSeq_Mode==CR_MODE) {
		Resolution_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].precision;
	} else if (*NSeq_Mode==CV_MODE) {
		Resolution_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].Max;
		Min_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].Min;
		Precision_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].precision;
	} else if (*NSeq_Mode==CP_MODE) {
		Resolution_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].precision;
	}

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if (*NSeq_Mode==CV_MODE) Para_s = 1;
		sprintf(str,"Start:%d, Seq No:%d, Memo:%s, Mode:%s, Range:%s, Loop:%s, Last Load:%s, Last:%.*f, Chain:%s"
		        ,*NSeq_Start+1,*NSeq_Seq_No+1
		        ,NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Memo
		        ,NSeq_Mode_String[*NSeq_Mode]
		        ,NSeq_Range_String[*NSeq_Range],Loop_String
		        ,Last_Load_String[*NSeq_Last_Load]
		        ,Precision_tmp
		        ,(*NSeq_Last_Level*Resolution_tmp*Para_s)
		        ,NSeq_Chain_String
		       );
		ExportProcess(String_Data,0,0,str,0);
	} else {
		//start :0
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si<SCPI_NSEQ_Seq_Lower)||(value.si>SCPI_NSEQ_Seq_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.StartNo = value.si;
		} else
			Command_Done =0;
		//seq :1
		if(0 == scpi_GetIntegerParameters( p, 1, (int*) &value.si)) {
			if((value.si<SCPI_NSEQ_Seq_Lower)||(value.si>SCPI_NSEQ_Seq_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.SeqNo = value.si;
		} else
			Command_Done =0;

		//memo :2
		if(1 == scpi_IsStringParameters( p, 2)) {
			length = scpi_GetStringParameters( p, 2, (unsigned int*) &value.ui); //'length', including the string terminator('\0').
			if((0 < length)&&(13 > length)) {
				strcpy(N.Memo, (char*)value.ui);
			} else {
				scpi_SetCommandError( p, _ERR_257_File_name_error);
				return;
			}
		} else
			Command_Done =0;
		//Run Mode :3
		if(0 == scpi_GetKeywordParameters( p, 3, (int*) &value.si)) {
			if((value.si<SCPI_CC)||(value.si>SCPI_CP)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.Mode= value.si;
			if (N.Mode==CV_MODE)Para_s = 1;
		} else
			Command_Done =0;
		//Range :4
		if(0 == scpi_GetKeywordParameters( p, 4, (int*) &value.si)) {
			if((value.si<SCPI_ILVL)||(value.si>SCPI_IHVH)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			if(N.Mode==SCPI_CR){
				if((value.si<SCPI_IHVL)||(value.si>SCPI_ILVH)) {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
			}
			N.Range= value.si;
		} else
			Command_Done =0;
		if(0!=P3k_NSeq_Disp.NSeq_Seq[N.SeqNo-1].NSeq_Max_Step) {
			if((N.Range!=NSeq_Disp_tmp->NSeq_Seq[N.SeqNo-1].NSeq_Range)||(N.Mode!=NSeq_Disp_tmp->NSeq_Seq[N.SeqNo-1].NSeq_Mode)) {
				scpi_SetCommandError( p, _ERR_221_Settings_conflict);
				return;
			}
		}
		//Loop :5
		if(0 == scpi_GetIntegerParameters( p, 5, (int*) &value.si)) {
			if((value.si<1)||(value.si>9999)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.Loop= value.si;
		} else if(0 == scpi_GetKeywordParameters( p, 5, (int*) &value.si)) {
			N.Loop= 0;//Infinity
		} else
			Command_Done =0;
		//LastLoad :6
		if(0 == scpi_GetIntegerParameters( p, 6, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.LastLoad= (1 == value.si) ? 1 : 0;
		} else if(0 == scpi_GetKeywordParameters( p, 6, (int*) &value.si)) {
			N.LastLoad = (1 == value.si) ? 1 : 0;
		} else
			Command_Done =0;
		//LastValue :7
		if(0 == scpi_GetFloatIntegerParameters( p, 7, (double*) &value.d)) {
			N.LastValue = value.d;
		} else
			Command_Done =0;
		//Chain :8
		if(0 == scpi_GetIntegerParameters( p, 8, (int*) &value.si)) {
			if((value.si<SCPI_NSEQ_Seq_Lower)||(value.si>SCPI_NSEQ_Seq_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.Chain= value.si;
		} else if(0 == scpi_GetKeywordParameters( p, 8, (int*) &value.si)) {
			N.Chain= 0;//off
		} else
			Command_Done =0;

		if(Command_Done==0) {
			scpi_SetCommandError( p, _ERR_220_Parameter_error);
			return;
		}
		V_Range = N.Range/3;
		I_Range = N.Range%3;
		if(N.Mode==CC_MODE) {
			Resolution_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
			Max_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
			Min_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
			Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
		} else if(N.Mode==CR_MODE) {
			Resolution_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Resolution;
			Max_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
			Min_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
			Precision_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].precision;
		} else if(N.Mode==CV_MODE) {
			Resolution_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
			Max_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].Max;
			Min_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].Min;
			Precision_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].precision;
		} else if(N.Mode==CP_MODE) {
			Resolution_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].Resolution;
			Max_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].Max;
			Min_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].Min;
			Precision_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].precision;
		}

		N.LastValueCount= SCPI_InputToStep((N.LastValue/Para_s),Resolution_tmp);
		if((N.LastValueCount<Min_tmp)||(N.LastValueCount>Max_tmp)) {
			scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
			return;
		}
		if(Command_Done) {
			//Start
			*NSeq_Start = N.StartNo-1;
			//Seq No
			*NSeq_Seq_No=N.SeqNo-1;
			//Mode
			NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Mode=N.Mode;
			//Range
			NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range=N.Range;
			NSeq_Memo = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Memo[0];
			NSeq_Loop = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Loop;
			NSeq_Chain = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Chain;
			NSeq_Last_Load = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Last_Load;
			NSeq_Last_Level = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Last_Level;
			//Normal Sequence Memo Name
			for (index=0; index<sizeof(*NSeq_Memo); index++) {
				*(NSeq_Memo+index)='\0';//clear name;
				if(index>20)break;
			}
			for (index=0; N.Memo[index]!='\0'; index++) {
				if (islower(N.Memo[index]))
					N.Memo[index]=toupper(N.Memo[index]);
				if(index>20)break;
			}

			for (index=0; index<12; index++)NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Memo[index]=N.Memo[index];
			if(N.Memo[12]!='\0')
				NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Memo[12]='\0';
			//Loop
			*NSeq_Loop =N.Loop;
			//Last Load
			*NSeq_Last_Load =N.LastLoad;
			//Last
			*NSeq_Last_Level = N.LastValueCount;
			//Chain
			*NSeq_Chain =N.Chain;
		}
		asm("nop;"); //be safe
		*NSeq_Data_tmp=*NSeq_Disp_tmp;
		P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
		M_num = P_Seq_Normal;
		P3k_NSeq_Disp = P3k_NSeq_Data;
		ClrDispCnt(0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		SEQ_Save_Status=1;
		Soft_Key_Temp=0;
		if(/*(M_num==P_Seq_Normal)&&*/(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
			MenuRedrawFlag |= MENU_CHANGE ;//- MENU3_CHANGE;
			ChanRedrawFlag |= DATA_CHANGE;
			DataRedrawFlag |= DATA_CHANGE;
			Draw_Set_parameter();			
			SysRedrawFlag |= SYS_CHANGE;
		}
		if(DispMode>DispMode_BROWSE_ITEMS)
			DispMode = DispMode_BROWSE_ITEMS;
		SaveRecall_NSeq_Data(Backup);
	}
// Code End
}

void idNSEQuenceSTARt(STR_PARSER * p)//AAAAA
{
	GW_TYPE value;
	UBYTE SettingCount;
	P3k_NSeq_Str *NSeq_Data_tmp = &P3k_NSeq_Data;
	P3k_NSeq_Str *NSeq_Disp_tmp = &P3k_NSeq_Disp;

	UBYTE Command_Done=0;
	char str[16],index;

	//Start No
	UBYTE *NSeq_Start = &NSeq_Disp_tmp->NSeq_Start;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Start:%d",*NSeq_Start+1);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si < SCPI_NSEQ_Seq_Lower)||(value.si > SCPI_NSEQ_Seq_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			*NSeq_Start = SettingCount-1;
			asm("nop;");
			*NSeq_Data_tmp=*NSeq_Disp_tmp;
			P3k_Chan_Data.Load_Type = P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_NSeq_Data(Backup);
		}
	}
// Code End
}

void idNSEQuenceNUMBer(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE SettingCount;
	P3k_NSeq_Str *NSeq_Data_tmp = &P3k_NSeq_Data;
	P3k_NSeq_Str *NSeq_Disp_tmp = &P3k_NSeq_Disp;

	UBYTE Command_Done=0;
	char str[16];
	UBYTE *NSeq_Seq_No = &NSeq_Disp_tmp->NSeq_Number;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Seq No:%d",*NSeq_Seq_No+1);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si < SCPI_NSEQ_Seq_Lower)||(value.si > SCPI_NSEQ_Seq_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			*NSeq_Seq_No = SettingCount-1;
			asm("nop;");
			*NSeq_Data_tmp=*NSeq_Disp_tmp;
			P3k_Chan_Data.Load_Type = P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_NSeq_Data(Backup);
		}
	}
// Code End
}

void idNSEQuenceMEMO(STR_PARSER * p)
{
	GW_TYPE value;
	char Memo[28],length;
	P3k_NSeq_Str *NSeq_Data_tmp = &P3k_NSeq_Data;
	P3k_NSeq_Str *NSeq_Disp_tmp = &P3k_NSeq_Disp;

	UBYTE Command_Done=0,str_data;
	char str[36],index;
	UBYTE i;

	//Seq No
	UBYTE *NSeq_Seq_No = &NSeq_Disp_tmp->NSeq_Number;

	//Memo
	UBYTE *NSeq_Memo = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Memo[0];

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Memo:%s",NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Memo);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		Command_Done = 1;
		if(1 == scpi_IsStringParameters( p, 0)) {
			length = scpi_GetStringParameters( p, 0, (unsigned int*) &value.ui); //'length', including the string terminator('\0').
			if((0 < length)&&(13 > length)) {
				strcpy(Memo, (char*)value.ui);
			} else {
				scpi_SetCommandError( p, _ERR_257_File_name_error);
				return;
			}
		} else {
			scpi_SetCommandError( p, _ERR_257_File_name_error);
			return;
		}
		if(Command_Done) {
			for (index=0; index<sizeof(*NSeq_Memo); index++) *(NSeq_Memo+index)='\0';//clear name;
			for (index=0; Memo[index]!='\0'; index++) {
				if (islower(Memo[index]))
					Memo[index]=toupper(Memo[index]);
			}

			for (index=0; index<12; index++)NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Memo[index]=Memo[index];
			if(Memo[12]!='\0')
				NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Memo[12]='\0';

			asm("nop;"); //be safe
			*NSeq_Data_tmp = *NSeq_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;

			SEQ_Save_Status=1;
			Soft_Key_Temp=0;

			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_NSeq_Data(Backup);
		}
	}
// Code End
}

void idNSEQuenceMODE(STR_PARSER * p)
{
	GW_TYPE value;
	P3k_NSeq_Str *NSeq_Data_tmp = &P3k_NSeq_Data;
	P3k_NSeq_Str *NSeq_Disp_tmp = &P3k_NSeq_Disp;

	UBYTE Command_Done=0,SettingCount;
	char str[16];
	UBYTE MODE;

	//Normal Sequence On/Off
	UBYTE *NSeq_Enable = &NSeq_Disp_tmp->NSeq_Enable;
	char NSeq_ON_OFF_String[4];
	if (P3k_Disp_Data.Load_Type==SCPI_Normal_Sequence)
		sprintf(NSeq_ON_OFF_String,"%s","ON");
	else sprintf(NSeq_ON_OFF_String,"%s","OFF");

	//Start No
	UBYTE *NSeq_Start = &NSeq_Disp_tmp->NSeq_Start;

	//Seq No
	UBYTE *NSeq_Seq_No = &NSeq_Disp_tmp->NSeq_Number;
	UWORD *NSeq_Last_Level = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Last_Level;
	//CC, CR Mode
	double Resolution_tmp;
	UWORD Max_tmp,Min_tmp;
	BYTE Precision_tmp;
	UBYTE V_Range = NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range/2;
	UBYTE I_Range = NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range%2;

	//Mode and its String
	UBYTE *NSeq_Mode = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Mode;
	char NSeq_Mode_String[4][3]= {"CC","CR","CV","CP"};

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Mode:%s",NSeq_Mode_String[*NSeq_Mode]);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if((0!=P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step)&&(*NSeq_Mode!=value.si)) {
				scpi_SetCommandError( p, _ERR_221_Settings_conflict);
				return;
			}
			SettingCount = value.si;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Mode=SettingCount;
			MODE = NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Mode;
			if(MODE==CC_MODE) {
				Max_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
				Min_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
			} else if(MODE==CR_MODE) {
				Max_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
				Min_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
				if(NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range==0)
					NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range = 1;
				if(NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range==3)
					NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range = 2;
			} else if(MODE==CV_MODE) {
				Max_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].Max;
				Min_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].Min;
			} else if(MODE==CP_MODE) {
				Max_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].Max;
				Min_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].Min;
			}
			if(*NSeq_Last_Level>Max_tmp)*NSeq_Last_Level=Max_tmp;
			else if(*NSeq_Last_Level<Min_tmp)*NSeq_Last_Level=Min_tmp;
			asm("nop;"); //be safe
			*NSeq_Data_tmp=*NSeq_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_NSeq_Data(Backup);
		}
	}
// Code End
}

void idNSEQuenceRANGe(STR_PARSER * p)
{
	GW_TYPE value;
	P3k_NSeq_Str *NSeq_Data_tmp = &P3k_NSeq_Data;
	P3k_NSeq_Str *NSeq_Disp_tmp = &P3k_NSeq_Disp;

	UBYTE Command_Done=0,SettingCount;
	char str[16];
	//Start No
	UBYTE *NSeq_Start = &NSeq_Disp_tmp->NSeq_Start;

	//Seq No
	UBYTE *NSeq_Seq_No = &NSeq_Disp_tmp->NSeq_Number;

	//CC, CR Mode
	double Resolution_tmp;
	UWORD Max_tmp,Min_tmp;
	BYTE Precision_tmp;
	UBYTE V_Range = NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range/2;
	UBYTE I_Range = NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range%2;

	//Range and its String
	UBYTE *NSeq_Range = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range;
	char NSeq_Range_String[4][5]= {"ILVL","IHVL","ILVH","IHVH"};
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Range:%s",NSeq_Range_String[*NSeq_Range]);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if((0!=P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step)&&(NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range!=value.si)) {
				scpi_SetCommandError( p, _ERR_221_Settings_conflict);
				return;
			}
			if(NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Mode==SCPI_CR){
				if((value.si==0)||(value.si==3)){
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
			}
			SettingCount = value.si;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range = SettingCount;
			asm("nop;"); //be safe
			*NSeq_Data_tmp=*NSeq_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_NSeq_Data(Backup);
		}
	}
// Code End
}

void idNSEQuenceLOOP(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UWORD SettingCount;
	P3k_NSeq_Str *NSeq_Data_tmp = &P3k_NSeq_Data;
	P3k_NSeq_Str *NSeq_Disp_tmp = &P3k_NSeq_Disp;
	char str[16];
	//Start No
	UBYTE *NSeq_Start = &NSeq_Disp_tmp->NSeq_Start;
	//Seq No
	UBYTE *NSeq_Seq_No = &NSeq_Disp_tmp->NSeq_Number;
	//Loop and its String
	UWORD *NSeq_Loop = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Loop;
	char Loop_String[9];

	if (*NSeq_Loop==SCPI_NSEQ_Loop_Infinity)
		sprintf(Loop_String,"%s","Infinity");
	else sprintf(Loop_String,"%d",*NSeq_Loop);
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Loop:%s",Loop_String);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si > 9999)||(value.si< 1)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = SCPI_NSEQ_Loop_Infinity;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Loop = SettingCount;
			asm("nop;"); //be safe
			*NSeq_Data_tmp=*NSeq_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_NSeq_Data(Backup);
		}
	}
// Code End
}

void idNSEQuenceLLOad(STR_PARSER * p)
{
	GW_TYPE value;
	P3k_NSeq_Str *NSeq_Data_tmp = &P3k_NSeq_Data;
	P3k_NSeq_Str *NSeq_Disp_tmp = &P3k_NSeq_Disp;

	UBYTE Command_Done=0, SettingBool;
	char str[24];

	//Start No
	UBYTE *NSeq_Start = &NSeq_Disp_tmp->NSeq_Start;

	//Seq No
	UBYTE *NSeq_Seq_No = &NSeq_Disp_tmp->NSeq_Number;

	//Last Load and its String
	UBYTE *NSeq_Last_Load = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Last_Load;
	char Last_Load_String[2][4]= {"OFF","ON"};
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Last Load:%s",Last_Load_String[*NSeq_Last_Load]);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Last_Load = SettingBool;
			NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Last_Load = SettingBool;
			asm("nop;");
			*NSeq_Data_tmp=*NSeq_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_NSeq_Data(Backup);
		}
	}
// Code End
}

void idNSEQuenceLAST(STR_PARSER * p)
{
	GW_TYPE value;
	P3k_NSeq_Str *NSeq_Data_tmp = &P3k_NSeq_Data;
	P3k_NSeq_Str *NSeq_Disp_tmp = &P3k_NSeq_Disp;


	UBYTE Command_Done=0;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char str[30];

	//Start No
	UBYTE *NSeq_Start = &NSeq_Disp_tmp->NSeq_Start;

	//Seq No
	UBYTE *NSeq_Seq_No = &NSeq_Disp_tmp->NSeq_Number;

	//CC, CR Mode
	UWORD Max_tmp,Min_tmp;
	BYTE Precision_tmp;
	UBYTE V_Range = NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range/2;
	UBYTE I_Range = NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range%2;

	//Mode and its String
	UBYTE *NSeq_Mode = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Mode;
	char NSeq_Mode_String[4][3]= {"CC","CR","CV","CP"};

	//Last Value
	UWORD *NSeq_Last_Level = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Last_Level;
	Para_s = (double)Get_Parallel_Parameter(1);

	if(*NSeq_Mode==CC_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
	} else if (*NSeq_Mode==CR_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CR)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].precision;
	} else if (*NSeq_Mode==CV_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].Max;
		Min_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].Min;
		Precision_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].precision;
		Para_s =1;
	} else if (*NSeq_Mode==CP_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CP)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].precision;
	}
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Real_Value = (double)NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Last_Level*ResolutionTemp*Para_s;
		if(Precision_tmp==1)
			sprintf(str,"Last:%4.1f",Real_Value);
		else if(Precision_tmp==2)
			sprintf(str,"Last:%3.2f",Real_Value);
		else if(Precision_tmp==3)
			sprintf(str,"Last:%2.3f",Real_Value);
		else
			sprintf(str,"Last:%2.4f",Real_Value);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			if((Real_Value<Min_tmp*ResolutionTemp)||(Real_Value>Max_tmp*ResolutionTemp)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value ,ResolutionTemp);
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Last_Level = SettingCount;
			NSeq_Data_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Last_Level = SettingCount;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_NSeq_Data(Backup);
		}
	}
// Code End
}

void idNSEQuenceCHAin(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE SettingCount;
	P3k_NSeq_Str *NSeq_Data_tmp = &P3k_NSeq_Data;
	P3k_NSeq_Str *NSeq_Disp_tmp = &P3k_NSeq_Disp;

	UBYTE Command_Done=0;
	char str[16];

	//Start No
	UBYTE *NSeq_Start = &NSeq_Disp_tmp->NSeq_Start;

	//Seq No
	UBYTE *NSeq_Seq_No = &NSeq_Disp_tmp->NSeq_Number;

	//Chain and its String
	UBYTE *NSeq_Chain = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Chain;
	char NSeq_Chain_String[4];
	if (*NSeq_Chain==SCPI_NSEQ_Chain_Off)
		sprintf(NSeq_Chain_String,"%s","Off");
	else sprintf(NSeq_Chain_String,"%d",*NSeq_Chain);

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Chain:%s",NSeq_Chain_String);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si > SCPI_NSEQ_Seq_Upper)||(value.si< SCPI_NSEQ_Seq_Lower)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done = 1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = value.si;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Chain = SettingCount;
			NSeq_Data_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Chain = SettingCount;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_NSeq_Data(Backup);
		}
	}
// Code End
}

typedef struct	{
	UWORD CurrStep;		/* 	step  1~1000		   */
	UWORD MaxStep;	/*	Step  1~1000	   */
	double Value;	/*	SettingValue	           */
	UWORD ValueCount;	/*	SettingValue	           */
	UWORD T_hour;
	UBYTE T_minute;
	UBYTE T_sec;
	UWORD T_millsec;
	UBYTE Load;		/*   on/off	    */
	UBYTE Ramp;		/*	on/off	    */
	UBYTE TrigOut;	/*	on/off        */
	UBYTE Pause;	/*	on/off        */
} NSEQ_Edit_Str;


void idNSEQuenceEDIT(STR_PARSER * p)
{
	GW_TYPE value;
	NSEQ_Edit_Str N;

	P3k_NSeq_Str *NSeq_Data_tmp = &P3k_NSeq_Data;
	P3k_NSeq_Str *NSeq_Disp_tmp = &P3k_NSeq_Disp;

	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	UBYTE Command_Done=1,i;
	UWORD SEQ_sum_setps=0;
	char str[160],index;
	Para_s = Get_Parallel_Parameter(1);
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	//Seq No
	UBYTE *NSeq_Seq_No = &NSeq_Disp_tmp->NSeq_Number;
//Step No
	UWORD *NSeq_Curr_Step = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Curr_Step;
	UWORD *NSeq_Max_Step = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Max_Step;
//Step Struct
	NSeq_Data_Str *NSeq_Step = &NSeq_Disp_tmp->NSeq_Step[*NSeq_Seq_No][*NSeq_Curr_Step];
//Value
	UWORD *NSeq_Value = &NSeq_Step->NSeq_Value;
//Time
	P3k_Time_Str *NSeq_Time = &NSeq_Step->NSeq_Time;
//Status of Load, Ramp, Trigger Out and Pause
	char ON_OFF[2][4]= {"OFF","ON"};

	//CC, CR Mode
	//double Max_Total,Min_Total;
	UWORD Max_tmp,Min_tmp;
	BYTE Precision_tmp;
	UBYTE *NSeq_Mode = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Mode;
	UBYTE V_Range = NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range/2;
	UBYTE I_Range = NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range%2;

	for(i=0;i<10;i++){
		if(*NSeq_Seq_No != i)
		SEQ_sum_setps += NSeq_Disp_tmp->NSeq_Seq[i].NSeq_Max_Step;
	}

	if(*NSeq_Mode==CC_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
	} else if (*NSeq_Mode==CR_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CR)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].precision;
	} else if (*NSeq_Mode==CV_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].Max;
		Min_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].Min;
		Precision_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].precision;
		Para_s =1;
	} else if (*NSeq_Mode==CP_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CP)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].precision;
	}
	Max = Max_tmp*ResolutionTemp;
	Min = Min_tmp*ResolutionTemp;

// Code Begin
	if(scpi_IsQueryCommand(p)) {

		if (copy_SCPI_Company==SCPI_GW) {
#if Enable_NSEQ_Usec
			sprintf(str,"Step:%d/%d, Value:%.*f, Time:%dH:%dM:%dS:%3.2fmS, LOAD:%s, TRIG OUT:%s, RAMP:%s, PAUSE:%s "
					,*NSeq_Curr_Step,*NSeq_Max_Step
					,Precision_tmp ,(*NSeq_Value*ResolutionTemp*Para_s)
					,NSeq_Time->Hour,NSeq_Time->Minute,NSeq_Time->Second,(float)NSeq_Time->MilliSecond*0.05
					,ON_OFF[NSeq_Step->Load_Setting],ON_OFF[NSeq_Step->Ramp_Setting]
					,ON_OFF[NSeq_Step->TrigOut_Setting],ON_OFF[NSeq_Step->Pause_Setting]
				   );
#else
			sprintf(str,"Step:%d/%d, Value:%.*f, Time:%dH:%dM:%dS:%dmS, LOAD:%s, TRIG OUT:%s, RAMP:%s, PAUSE:%s "
					,*NSeq_Curr_Step,*NSeq_Max_Step
					,Precision_tmp ,(*NSeq_Value*ResolutionTemp*Para_s)
					,NSeq_Time->Hour,NSeq_Time->Minute,NSeq_Time->Second,NSeq_Time->MilliSecond
					,ON_OFF[NSeq_Step->Load_Setting],ON_OFF[NSeq_Step->Ramp_Setting]
					,ON_OFF[NSeq_Step->TrigOut_Setting],ON_OFF[NSeq_Step->Pause_Setting]
				   );
#endif

		} else if(copy_SCPI_Company==SCPI_KIKUSUI) {
			if(p->pData->id==_idPROGramSELectedNSPeedSTEPCOUNt)
				sprintf(str,"Step:%d",*NSeq_Curr_Step);
			else
				scpi_SetCommandError( p, _ERR_113_Undefined_header);
		}
		ExportProcess(String_Data,0,0,str,0);
	} else {

		//0. CurrStep
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si<SCPI_NSEQ_Step_Lower)||(value.si>SCPI_NSEQ_Step_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.CurrStep = value.si;
		} else
			Command_Done =0;
		//1. MaxStep
		if(0 == scpi_GetIntegerParameters( p, 1, (int*) &value.si)) {
			if((value.si<SCPI_NSEQ_Step_Lower)||((value.si+SEQ_sum_setps)>SCPI_NSEQ_Step_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.MaxStep = value.si;
		} else
			Command_Done =0;
		if(N.MaxStep<N.CurrStep) {
			scpi_SetCommandError( p, _ERR_221_Settings_conflict);
			return;
		}
		// 2.Value
		if(0 == scpi_GetFloatIntegerParameters( p, 2, (double*) &value.d)) {
			N.Value= value.d/Para_s;
			if((N.Value> Max)||(N.Value < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.ValueCount = SCPI_InputToStep(N.Value,ResolutionTemp);
		} else
			Command_Done =0;

		//3.Time --- Hour
		if(0 == scpi_GetIntegerParameters( p, 3, (int*) &value.si)) {
			if((value.si<SCPI_NSEQ_Time_Hour_mS_Lower)||(value.si>SCPI_NSEQ_Time_Hour_mS_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.T_hour = value.si;
		} else
			Command_Done =0;
		//4.Time --- Minute
		if(0 == scpi_GetIntegerParameters( p, 4, (int*) &value.si)) {
			if((value.si<SCPI_NSEQ_Time_Min_Sec_Lower)||(value.si>SCPI_NSEQ_Time_Min_Sec_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.T_minute= value.si;
		} else
			Command_Done =0;
		//5.Time --- sec
		if(0 == scpi_GetIntegerParameters( p, 5, (int*) &value.si)) {
			if((value.si<SCPI_NSEQ_Time_Min_Sec_Lower)||(value.si>SCPI_NSEQ_Time_Min_Sec_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.T_sec= value.si;
		} else
			Command_Done =0;
#if Enable_NSEQ_Usec
		//6.Time --- msec
		if(0 == scpi_GetFloatIntegerParameters( p, 6, (double*) &value.d)) {
			if((value.d<SCPI_NSEQ_Time_Hour_mS_Lower)||(value.d>999.95)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.T_millsec = (UWORD)(value.d/0.05);
		} else
			Command_Done =0;
#else
		//6.Time --- msec
		if(0 == scpi_GetFloatIntegerParameters( p, 6, (double*) &value.d)) {
			if((value.d<SCPI_NSEQ_Time_Hour_mS_Lower)||(value.d>SCPI_NSEQ_Time_Hour_mS_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.T_millsec = (UWORD)(value.d);
		} else
			Command_Done =0;
#endif


		//7.	load
		if(0 == scpi_GetIntegerParameters( p, 7, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.Load= (1 == value.si) ? 1 : 0;
		} else if(0 == scpi_GetKeywordParameters( p, 7, (int*) &value.si)) {
			N.Load = (1 == value.si) ? 1 : 0;
		} else
			Command_Done =0;
		//8. ramp
		if(0 == scpi_GetIntegerParameters( p, 8, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.Ramp= (1 == value.si) ? 1 : 0;
		} else if(0 == scpi_GetKeywordParameters( p, 8, (int*) &value.si)) {
			N.Ramp= (1 == value.si) ? 1 : 0;
		} else
			Command_Done =0;
		//9. trig out
		if(0 == scpi_GetIntegerParameters( p, 9, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.TrigOut= (1 == value.si) ? 1 : 0;
		} else if(0 == scpi_GetKeywordParameters( p, 9, (int*) &value.si)) {
			N.TrigOut= (1 == value.si) ? 1 : 0;
		} else
			Command_Done =0;
		//10. pause
		if(0 == scpi_GetIntegerParameters( p, 10, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.Pause= (1 == value.si) ? 1 : 0;
		} else if(0 == scpi_GetKeywordParameters( p, 10, (int*) &value.si)) {
			N.Pause= (1 == value.si) ? 1 : 0;
		} else
			Command_Done =0;

		if(Command_Done==0) {
			scpi_SetCommandError( p, _ERR_220_Parameter_error);
			return;
		}

		if(Command_Done) {
#if Enable_NSEQ_Usec
			unsigned long Ramp_mS_Time;
			Ramp_mS_Time = N.T_hour*60*60*1000 + N.T_minute*60*1000 + N.T_sec*1000 + (N.T_millsec /20);

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
				N.T_sec = 0;
				N.T_millsec = 0;
			} else if(Ramp_mS_Time>1000*60*1000) {	/* 1000 Minute ~ 10000 Minute	*/
				N.T_sec = N.T_sec - (N.T_sec%10);
				N.T_millsec = 0;
			} else if(Ramp_mS_Time>100*60*1000) {	/* 100 Minute ~1000 Minute	*/
				N.T_millsec = 0;
			} else if(Ramp_mS_Time>1*60*1000) { /* 1 Minute ~ 100 Minute	*/

			} else {						/* 1 us ~ 60 ms */

			}

#endif			
			//max_step
			*NSeq_Max_Step = N.MaxStep;
			//current_step
			*NSeq_Curr_Step=N.CurrStep;
			NSeq_Step = &NSeq_Disp_tmp->NSeq_Step[*NSeq_Seq_No][*NSeq_Curr_Step];
			//Value
			NSeq_Step->NSeq_Value = N.ValueCount;
			//Time --- Hour
			NSeq_Step->NSeq_Time.Hour=N.T_hour;
			//Time --- Minute
			NSeq_Step->NSeq_Time.Minute=N.T_minute;
			//Time --- Second
			NSeq_Step->NSeq_Time.Second=N.T_sec;
			//Time --- Milli Second
			NSeq_Step->NSeq_Time.MilliSecond=N.T_millsec;
			//Load
			NSeq_Step->Load_Setting=N.Load;
			//Ramp
			NSeq_Step->Ramp_Setting=N.Ramp;
			//Trigger Out
			NSeq_Step->TrigOut_Setting=N.TrigOut;
			//Pause
			NSeq_Step->Pause_Setting=N.Pause;

			asm("nop;"); //be safe
			NSeq_Data_tmp=NSeq_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if(/*(M_num==P_Seq_Normal)&&*/(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_NSeq_Data(Backup);
		}
	}
// Code End
}

void idNSEQuenceEDITPOINt(STR_PARSER * p)
{
	GW_TYPE value;
	UWORD SettingCount;
	UBYTE Command_Done=0;
	char str[12];
	P3k_NSeq_Str *NSeq_Data_tmp = &P3k_NSeq_Data;
	P3k_NSeq_Str *NSeq_Disp_tmp = &P3k_NSeq_Disp;
	UBYTE *NSeq_Seq_No = &NSeq_Disp_tmp->NSeq_Number;
	//Step No
	UWORD *NSeq_Curr_Step = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Curr_Step;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		ExportProcess(Integer_Data,0,*NSeq_Curr_Step,0,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si > 1000) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			if(value.si > (NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Max_Step)) {
				scpi_SetCommandError( p, _ERR_221_Settings_conflict);
				return;
			}
			if(NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Max_Step==0) {
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {

			//current_step
			*NSeq_Curr_Step=SettingCount;
			NSeq_Data_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Curr_Step=SettingCount;
			asm("nop;"); //be safe
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if(/*(M_num==P_Seq_Normal)&&*/(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_NSeq_Data(Backup);
		}
	}
// Code End
}

void idNSEQuenceEDITEND(STR_PARSER * p)
{
	char str[12];
	P3k_NSeq_Str *NSeq_Data_tmp = &P3k_NSeq_Data;
	P3k_NSeq_Str *NSeq_Disp_tmp = &P3k_NSeq_Disp;
	UBYTE *NSeq_Seq_No = &NSeq_Disp_tmp->NSeq_Number;
	//Step No
	UWORD *NSeq_Max_Step = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Max_Step;


// Code Begin
	if(scpi_IsQueryCommand(p)) {
		ExportProcess(Integer_Data,0,*NSeq_Max_Step,0,0);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}


void idNSEQuenceDELetALL(STR_PARSER * p)
{
	UWORD i;
	UBYTE j;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(0==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step)
			return ;
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
		if(M_num==P_NSeq_Edit)
			DispMode = DispMode_SELECT_CH;
		if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
			DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
			MenuRedrawFlag |= MENU2_CHANGE + MENU3_CHANGE;
		}
	}
// Code End
}

void idNSEQuenceSAVE(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		P3k_FSeq_Data = P3k_FSeq_Disp;
		BackupFSeq();
		SEQ_Save_Status = 0;
		if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu))
			MenuRedrawFlag |= MENU3_CHANGE;
		SCPI_RemFastDelay = 1;
	}
// Code End
}

void idFSEQuenceSTATe(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, SettingBool;
	FSeq_Timing_Str *FSeq_Data_tmp = &P3k_FSeq_Data;
	FSeq_Timing_Str *FSeq_Disp_tmp = &P3k_FSeq_Disp;
	p3k_send_tx_list	tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if (P3k_Disp_Data.Load_Type!=SCPI_Fast_Sequence)
			ExportProcess(String_Data,0,0,"OFF",0);
		else {
			if(P_FSeq_EXECUTE != M_num)
				ExportProcess(String_Data,0,0,"ON,STOP",0);
			else
				ExportProcess(String_Data,0,0,"ON,RUN",0);
		}
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? SCPI_Fast_Sequence : SCPI_Load;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? SCPI_Fast_Sequence : SCPI_Load;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if (Command_Done) {
			P3k_Disp_Data.Load_Type = SettingBool;
			P3k_Chan_Data.Load_Type = SettingBool;
			asm("nop;");
			*FSeq_Data_tmp=*FSeq_Disp_tmp;
			if(/*(M_num==P_PROG_MAIN)&&*/(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				SysRedrawFlag |= PROG_UPDATA + BG_CLEAR_FLAG;
				MenuRedrawFlag |= MENU1_CHANGE;
			}
		}
	}

}

typedef struct	{
	char Memo[28];/*	NSEQ name	   */
	UBYTE Mode;			/*	CC,CR	   */
	UBYTE Range;		/*	ILVL,IHVL,ILVH,VHVH 	   */
	UWORD Loop;			/*	0~9999	                */
	double TimeBase;	/*	SettingValue	           */
	UWORD TimeBaseCount;	/*	SettingValue	           */
	UBYTE LastLoad;		/*   on/off				  */
	double LastValue;	/*	SettingValue	           */
	ULONG LastValueCount;	/*	SettingValue	           */
	UWORD RptStep;
} FSEQStr;

void idFSEQuence(STR_PARSER * p)
{
	GW_TYPE value;
	FSEQStr F;

	FSeq_Timing_Str *FSeq_Data_tmp = &P3k_FSeq_Data;
	FSeq_Timing_Str *FSeq_Disp_tmp = &P3k_FSeq_Disp;

	UBYTE Command_Done=1,length;
	char str[128],index;
	char index1;
	double Para_s;
	Para_s = Get_Parallel_Parameter(1);
//CC, CR Mode
	double Resolution_tmp;
	UWORD Max_tmp,Min_tmp;
	BYTE Precision_tmp;
	UBYTE I_Range = FSeq_Disp_tmp->FSeq_Range%2;
//Fast Sequence On/Off
	char FSeq_ON_OFF_String[4];
	if (P3k_Disp_Data.Load_Type==SCPI_Fast_Sequence)
		sprintf(FSeq_ON_OFF_String,"%s","ON");
	else sprintf(FSeq_ON_OFF_String,"%s","OFF");
//Fast Sequence Memo Name
	UBYTE *FSeq_Memo = &FSeq_Disp_tmp->FSeq_Memo[0];
	UBYTE index_for_fseq_memo;
//Mode and its String
	UBYTE *FSeq_Mode = &FSeq_Disp_tmp->FSeq_Mode;
	char FSeq_Mode_String[2][3]= {"CC","CR"};
//Range and its String
	UBYTE *FSeq_Range = &FSeq_Disp_tmp->FSeq_Range;
	char FSeq_Range_String[4][5]= {"ILVL","IHVL","ILVH","IHVH"};
//Loop and its String
	UWORD *FSeq_Loop = &FSeq_Disp_tmp->FSeq_Loop;
	char Loop_String[9];
	if (*FSeq_Loop==SCPI_FSEQ_Loop_Infinity)
		sprintf(Loop_String,"%s","Infinity");
	else sprintf(Loop_String,"%d",*FSeq_Loop);
//Time Base
	UBYTE *Time_Base_Range_Flag = &FSeq_Disp_tmp->FSeq_TB_Range; /* 0:us, 1:10us*/
	ULONG *Time_Base_Count = &FSeq_Disp_tmp->FSeq_Time_Base;
	float Time_Base_Resolution=powf(10.0,(float)(*Time_Base_Range_Flag))*0.001; //convert micro second to milli second
	UWORD Time_Base_Precision =ceild(abs((log10f(Time_Base_Resolution))));
	double Real_Time_Base = *Time_Base_Count*Time_Base_Resolution;
//Last Load and its String
	UBYTE *FSeq_Last_Load = &FSeq_Disp_tmp->FSeq_Last_Load;
	char Last_Load_String[2][4]= {"OFF","ON"};
//Last Value
	UWORD *FSeq_Last_Level = &FSeq_Disp_tmp->FSeq_Last_Level;
//RPTSTEP
#if Enable_FSEQ_RPT
	UWORD *FSeq_Repeat_Step = &FSeq_Disp_tmp->RPTStep;
#else
	UWORD *FSeq_Repeat_Step = &FSeq_Disp_tmp->FSeq_Max_Step;
#endif

	if(*FSeq_Mode==CC_MODE) {
		Resolution_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
	} else if (*FSeq_Mode==CR_MODE) {
		Resolution_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].precision;
	}
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Memo:%s, Mode:%s, Range:%s, Loop:%s, Time Base:%.*f, Last Load:%s, Last:%.*f, RPTSTEP:%d"
		        //,FSeq_ON_OFF_String
		        ,FSeq_Disp_tmp->FSeq_Memo,FSeq_Mode_String[*FSeq_Mode]
		        ,FSeq_Range_String[*FSeq_Range],Loop_String
		        ,Time_Base_Precision,Real_Time_Base
		        ,Last_Load_String[*FSeq_Last_Load]
		        ,Precision_tmp,*FSeq_Last_Level*Resolution_tmp*Para_s
		        ,*FSeq_Repeat_Step+1);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		//memo :0
		if(1 == scpi_IsStringParameters( p, 0)) {
			length = scpi_GetStringParameters( p, 0, (unsigned int*) &value.ui); //'length', including the string terminator('\0').
			if((0 < length)&&(13 > length)) {
				strcpy(F.Memo, (char*)value.ui);
			} else {
				scpi_SetCommandError( p, _ERR_257_File_name_error);
				return;
			}
		} else
			Command_Done =0;

		//Run Mode :1
		if(0 == scpi_GetKeywordParameters( p, 1, (int*) &value.si)) {
			if((value.si<SCPI_CC)||(value.si>SCPI_CR)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			F.Mode= value.si;
		} else
			Command_Done =0;
		if((P3k_FSeq_Disp.FSeq_Max_Step<0xFF00)&&(F.Mode!=*FSeq_Mode)) {
			scpi_SetCommandError( p, _ERR_221_Settings_conflict);
			return;
		}
		//Range :2
		if(0 == scpi_GetKeywordParameters( p, 2, (int*) &value.si)) {
			if((value.si<SCPI_ILVL)||(value.si>SCPI_IHVH)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			if(F.Mode==SCPI_CR){
				if((value.si<SCPI_IHVL)||(value.si>SCPI_ILVH)) {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
			}
			F.Range= value.si;
		} else
			Command_Done =0;
		if((P3k_FSeq_Disp.FSeq_Max_Step<0xFF00)&&(F.Range!=FSeq_Disp_tmp->FSeq_Range)) {
			scpi_SetCommandError( p, _ERR_221_Settings_conflict);
			return;
		}

		//Loop :3
		if(0 == scpi_GetIntegerParameters( p, 3, (int*) &value.si)) {
			if((value.si<1)||(value.si>9999)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			F.Loop= value.si;
		} else if(0 == scpi_GetKeywordParameters( p, 3, (int*) &value.si)) {
			F.Loop= 0;//Infinity
		} else
			Command_Done =0;

		//TimeBase :4
		if(0 == scpi_GetFloatIntegerParameters( p, 4, (double*) &value.d)) {
			if((value.d<0.00002499)||(value.d>0.600001)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			F.TimeBase = value.d;
		} else
			Command_Done =0;


		//LastLoad :5
		if(0 == scpi_GetIntegerParameters( p, 5, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			F.LastLoad= (1 == value.si) ? 1 : 0;
		} else if(0 == scpi_GetKeywordParameters( p, 5, (int*) &value.si)) {
			F.LastLoad = (1 == value.si) ? 1 : 0;
		} else
			Command_Done =0;

		I_Range = F.Range%3;
		if(F.Mode==CC_MODE) {
			Resolution_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
			Max_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
			Min_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
			Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
		} else if (F.Mode==CR_MODE) {
			Resolution_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Resolution;
			Max_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
			Min_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
			Precision_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].precision;
		}
		//LastValue :6
		if(0 == scpi_GetFloatIntegerParameters( p, 6, (double*) &value.d)) {
			F.LastValue = value.d/Para_s;
			if((F.LastValue<Min_tmp*Resolution_tmp)||(F.LastValue>Max_tmp*Resolution_tmp)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			F.LastValueCount = SCPI_InputToStep(F.LastValue,Resolution_tmp);
		} else
			Command_Done =0;
		//Chain :7
		if(0 == scpi_GetIntegerParameters( p, 7, (int*) &value.si)) {
			if((value.si<0)||(value.si>SCPI_NSEQ_Step_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
#if Enable_FSEQ_RPT
			if(value.si>FSeq_Disp_tmp->FSeq_Max_Step+1) {
				scpi_SetCommandError( p, _ERR_221_Settings_conflict);
				return;
			}
#endif	
			F.RptStep= value.si;
		} else
			Command_Done =0;

		if(Command_Done==0) {
			scpi_SetCommandError( p, _ERR_220_Parameter_error);
			return;
		}
		if(Command_Done) {
			FSeq_Memo = &FSeq_Disp_tmp->FSeq_Memo[0];
			//Fast Sequence Memo Name
			for (index=0; index<sizeof(*FSeq_Memo); index++) {
				*(FSeq_Memo+index)='\0';
				if(index>20)break;
			}
			for (index=0; F.Memo!='\0'; index++) {
				if (islower(F.Memo[index]))
					F.Memo[index]=toupper(F.Memo[index]);
				if(index>20)break;
			}
			for (index=0; index<12; index++)FSeq_Disp_tmp->FSeq_Memo[index]=F.Memo[index];
			if (F.Memo[12]!='\0')
				FSeq_Disp_tmp->FSeq_Memo[12]='\0';

			//Mode
			*FSeq_Mode=F.Mode;
			//Range
			*FSeq_Range=F.Range;
			//Loop
			*FSeq_Loop=F.Loop;
			//Time Base
			if(F.TimeBase>=0.06) {
				*Time_Base_Range_Flag=1;/* 0:us, 1:10us*/
				F.TimeBase = F.TimeBase*1000;
				Time_Base_Resolution = 0.01;
			} else {
				*Time_Base_Range_Flag=0;		/* 0:us, 1:10us*/
				Time_Base_Resolution = 0.001;
				F.TimeBase = F.TimeBase*1000;
			}
			P3k_FSeq_Disp.FSeq_Time_Base = SCPI_InputToStep(F.TimeBase,Time_Base_Resolution);
			//Last Load
			*FSeq_Last_Load=F.LastLoad;
			//Last
			P3k_FSeq_Disp.FSeq_Last_Level = SCPI_InputToStep(F.LastValue,Resolution_tmp);
			//RPTSTEP
			*FSeq_Repeat_Step=F.RptStep-1;
			asm("nop;"); //be safe
			*FSeq_Data_tmp=*FSeq_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if(/*(M_num==P_Seq_Fast)&&*/(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				Draw_Set_parameter();				
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_FSeq_Data(Backup);
		}
	}
// Code End
}

void idFSEQuenceMEMO(STR_PARSER * p)
{
	GW_TYPE value;
	char Memo[28],length;

	UBYTE Command_Done=0,str_data;
	char str[36],index;
	UBYTE i;
	FSeq_Timing_Str *FSeq_Data_tmp = &P3k_FSeq_Data;
	FSeq_Timing_Str *FSeq_Disp_tmp = &P3k_FSeq_Disp;

	//Fast Sequence Memo Name
	UBYTE *FSeq_Memo = &FSeq_Disp_tmp->FSeq_Memo[0];
	UBYTE index_for_fseq_memo;


// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Memo:%s",FSeq_Disp_tmp->FSeq_Memo);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		Command_Done = 1;
		if(1 == scpi_IsStringParameters( p, 0)) {
			length = scpi_GetStringParameters( p, 0, (unsigned int*) &value.ui); //'length', including the string terminator('\0').
			if((0 < length)&&(13 > length)) {
				strcpy(Memo, (char*)value.ui);
			} else {
				scpi_SetCommandError( p, _ERR_257_File_name_error);
				return;
			}
		} else {
			scpi_SetCommandError( p, _ERR_257_File_name_error);
			return;
		}
		if(Command_Done) {
			for (index=0; index<sizeof(*FSeq_Memo); index++) {
				*(FSeq_Memo+index)='\0';//clear name;
				if(index>20)break;
			}
			for (index=0; Memo[index]!='\0'; index++) {
				if (islower(Memo[index]))
					Memo[index]=toupper(Memo[index]);
				if(index>20)break;
			}
			for (index=0; index<12; index++)FSeq_Disp_tmp->FSeq_Memo[index]=Memo[index];


			if(Memo[12]!='\0')
				FSeq_Disp_tmp->FSeq_Memo[12]='\0';

			asm("nop;"); //be safe
			*FSeq_Data_tmp=*FSeq_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				Draw_Set_parameter();				
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_FSeq_Data(Backup);
		}
	}
// Code End
}

void idFSEQuenceMODE(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE SettingCount;
	FSeq_Timing_Str *FSeq_Data_tmp = &P3k_FSeq_Data;
	FSeq_Timing_Str *FSeq_Disp_tmp = &P3k_FSeq_Disp;

	UBYTE Command_Done=0;
	char str[16],index;
	UWORD Max_tmp;
	UBYTE I_Range = FSeq_Disp_tmp->FSeq_Range%2;


	//Mode and its String
	UBYTE *FSeq_Mode = &FSeq_Disp_tmp->FSeq_Mode;
	UWORD *FSeq_Last_Level = &FSeq_Disp_tmp->FSeq_Last_Level;
	char FSeq_Mode_String[2][3]= {"CC","CR"};

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Mode:%s",FSeq_Mode_String[*FSeq_Mode]);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = value.si;
			Command_Done = 1;
			if((P3k_FSeq_Disp.FSeq_Max_Step<0xFF00)&&(SettingCount!=*FSeq_Mode)) {
				scpi_SetCommandError( p, _ERR_221_Settings_conflict);
				return;
			}
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			*FSeq_Mode=SettingCount;
			if(*FSeq_Mode==CC_MODE) {
				Max_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
			} else if (*FSeq_Mode==CR_MODE) {
				Max_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
				if(FSeq_Disp_tmp->FSeq_Range==0)
					FSeq_Disp_tmp->FSeq_Range = 1;
				if(FSeq_Disp_tmp->FSeq_Range==3)
					FSeq_Disp_tmp->FSeq_Range = 2;
			}
			if(*FSeq_Last_Level>Max_tmp)*FSeq_Last_Level = Max_tmp;
			asm("nop;"); //be safe
			*FSeq_Data_tmp=*FSeq_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				Draw_Set_parameter();				
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_FSeq_Data(Backup);
		}
	}
// Code End
}

void idFSEQuenceRANGe(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE SettingCount;
	FSeq_Timing_Str *FSeq_Data_tmp = &P3k_FSeq_Data;
	FSeq_Timing_Str *FSeq_Disp_tmp = &P3k_FSeq_Disp;

	UBYTE Command_Done=0;
	char str[16],index;

	//CC, CR Mode
	double Resolution_tmp;
	UWORD Max_tmp,Min_tmp;
	BYTE Precision_tmp;
	UBYTE I_Range = FSeq_Disp_tmp->FSeq_Range%2;

	//Range and its String
	UBYTE *FSeq_Range = &FSeq_Disp_tmp->FSeq_Range;
	char FSeq_Range_String[4][5]= {"ILVL","IHVL","ILVH","IHVH"};
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Range:%s",FSeq_Range_String[*FSeq_Range]);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = value.si;
			Command_Done = 1;
			if((P3k_FSeq_Disp.FSeq_Max_Step<0xFF00)&&(SettingCount!=FSeq_Disp_tmp->FSeq_Range)) {
				scpi_SetCommandError( p, _ERR_221_Settings_conflict);
				return;
			}
			if(P3k_FSeq_Disp.FSeq_Mode == SCPI_CR){
				if((SettingCount==0)||(SettingCount==3)){
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
			}
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			*FSeq_Range = SettingCount;
			asm("nop;"); //be safe
			*FSeq_Data_tmp=*FSeq_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;

			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
			ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
			DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
			Draw_Set_parameter();			
			SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_FSeq_Data(Backup);
		}
	}
// Code End
}

void idFSEQuenceLOOP(STR_PARSER * p)
{
	GW_TYPE value;
	UWORD SettingCount;
	FSeq_Timing_Str *FSeq_Data_tmp = &P3k_FSeq_Data;
	FSeq_Timing_Str *FSeq_Disp_tmp = &P3k_FSeq_Disp;

	UBYTE Command_Done=0;
	char str[16],index;

	//Loop and its String
	UWORD *FSeq_Loop = &FSeq_Disp_tmp->FSeq_Loop;
	char Loop_String[9];

	if (*FSeq_Loop==SCPI_FSEQ_Loop_Infinity)
		sprintf(Loop_String,"%s","Infinity");
	else sprintf(Loop_String,"%d",*FSeq_Loop);
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Loop:%s",Loop_String);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si > 9999)||(value.si< 1)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = SCPI_NSEQ_Loop_Infinity;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			*FSeq_Loop = SettingCount;
			FSeq_Data_tmp->FSeq_Loop = SettingCount;
			asm("nop;"); //be safe
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
			ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
			DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
			Draw_Set_parameter();			
			SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_FSeq_Data(Backup);
		}
	}
// Code End
}

void idFSEQuenceTBASe(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp;
	FSeq_Timing_Str *FSeq_Data_tmp = &P3k_FSeq_Data;
	FSeq_Timing_Str *FSeq_Disp_tmp = &P3k_FSeq_Disp;
	char str[36],index;

	//Time Base
	UBYTE *Time_Base_Range_Flag = &FSeq_Disp_tmp->FSeq_TB_Range; /* 0:us, 1:10us*/
	ULONG *Time_Base_Count = &FSeq_Disp_tmp->FSeq_Time_Base;
	ResolutionTemp=powf(10.0,(float)(*Time_Base_Range_Flag))*0.001; //convert micro second to milli second
	UWORD Time_Base_Precision =ceild(abs((log10f(ResolutionTemp))));
	double Real_Time_Base = *Time_Base_Count*ResolutionTemp;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Real_Value = Real_Time_Base/1000;
		sprintf(str,"Time Base:%.*f",(Time_Base_Precision+3),Real_Value);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d * 1000;
			if (Real_Value>=60) { 	//more than 6ms
				*Time_Base_Range_Flag=1;		/* 0:us, 1:10us*/
				ResolutionTemp= 0.01;
			} else {
				*Time_Base_Range_Flag=0;		/* 0:us, 1:10us*/
				ResolutionTemp = 0.001;
			}
			if ((Real_Value>600.01)||(Real_Value<0.0249)) {	//Unit:ms
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value ,ResolutionTemp);
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			*Time_Base_Count = SettingCount;
			asm("nop;"); //be safe
			*FSeq_Data_tmp=*FSeq_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;

			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
			ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
			DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
			Draw_Set_parameter();			
			SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_FSeq_Data(Backup);
		}
	}
// Code End
}

void idFSEQuenceLLOad(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, SettingBool;
	FSeq_Timing_Str *FSeq_Data_tmp = &P3k_FSeq_Data;
	FSeq_Timing_Str *FSeq_Disp_tmp = &P3k_FSeq_Disp;
	char str[24],index;

	//Last Load and its String
	UBYTE *FSeq_Last_Load = &FSeq_Disp_tmp->FSeq_Last_Load;
	char Last_Load_String[2][4]= {"OFF","ON"};
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Last Load:%s",Last_Load_String[*FSeq_Last_Load]);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			*FSeq_Last_Load = SettingBool;
			FSeq_Data_tmp->FSeq_Last_Load = SettingBool;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;

			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				Draw_Set_parameter();				
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_FSeq_Data(Backup);
		}
	}
// Code End

}

void idFSEQuenceLAST(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	FSeq_Timing_Str *FSeq_Data_tmp = &P3k_FSeq_Data;
	FSeq_Timing_Str *FSeq_Disp_tmp = &P3k_FSeq_Disp;
	char str[36],index;
	UWORD MaxTemp,MinTemp;
	BYTE Precision_tmp;
	UBYTE I_Range = FSeq_Disp_tmp->FSeq_Range%2;

	Para_s = Get_Parallel_Parameter(1);

	//Last Value
	UWORD *FSeq_Last_Level = &FSeq_Disp_tmp->FSeq_Last_Level;

	//Mode and its String
	UBYTE *FSeq_Mode = &FSeq_Disp_tmp->FSeq_Mode;
	char FSeq_Mode_String[2][3]= {"CC","CR"};

	if(*FSeq_Mode==CC_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
		MaxTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
		MinTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
	} else if (*FSeq_Mode==CR_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CR)[I_Range*10].Resolution;
		MaxTemp = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
		MinTemp = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].precision;
	}
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Real_Value = (double)*FSeq_Last_Level*ResolutionTemp*Para_s;
		if(Precision_tmp==1)
			sprintf(str,"Last:%4.1f",Real_Value);
		else if(Precision_tmp==2)
			sprintf(str,"Last:%3.2f",Real_Value);
		else if(Precision_tmp==3)
			sprintf(str,"Last:%2.3f",Real_Value);
		else
			sprintf(str,"Last:%2.4f",Real_Value);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			if((Real_Value<MinTemp*ResolutionTemp)||(Real_Value>MaxTemp*ResolutionTemp)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value ,ResolutionTemp);
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			*FSeq_Last_Level = SettingCount;
			FSeq_Data_tmp->FSeq_Last_Level = SettingCount;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				Draw_Set_parameter();				
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_NSeq_Data(Backup);
		}
	}
// Code End

}

void idFSEQuenceRPTStep(STR_PARSER * p)
{
	GW_TYPE value;
	UWORD SettingCount;
	FSeq_Timing_Str *FSeq_Data_tmp = &P3k_FSeq_Data;
	FSeq_Timing_Str *FSeq_Disp_tmp = &P3k_FSeq_Disp;

	UBYTE Command_Done=0;
	char str[16],index;
	//RPTSTEP
#if Enable_FSEQ_RPT
	UWORD *FSeq_Repeat_Step = &FSeq_Disp_tmp->RPTStep;
#else
	UWORD *FSeq_Repeat_Step = &FSeq_Disp_tmp->FSeq_Max_Step;
#endif

	UWORD *FSeq_curr_Step = &FSeq_Disp_tmp->FSeq_Curr_Step;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"RPTSTEP:%d",*FSeq_Repeat_Step+1);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si > 1000)||(value.si< 1)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
#if Enable_FSEQ_RPT
			if(value.si > FSeq_Disp_tmp->FSeq_Max_Step+1) {
				scpi_SetCommandError( p, _ERR_221_Settings_conflict);
				return;
			}
#endif			
			SettingCount = value.si-1;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			*FSeq_Repeat_Step = SettingCount;
			FSeq_Data_tmp->FSeq_Max_Step= SettingCount;
#if Enable_FSEQ_RPT
			
#else
			if(*FSeq_curr_Step>*FSeq_Repeat_Step) {
				*FSeq_curr_Step=*FSeq_Repeat_Step;
				FSeq_Data_tmp->FSeq_Curr_Step=*FSeq_Repeat_Step;
			}
#endif	

			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				Draw_Set_parameter();				
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_FSeq_Data(Backup);
		}
	}
// Code End

}
typedef struct	{
	UWORD CurrStep;			/*	0~1000	                */
	UWORD MaxStep;			/*	0~1000	                */
	double Value;			/*	SettingValue	           */
	ULONG ValueCount;		/*	SettingValue	           */
	UBYTE TrigOut;  		/*   no/off 				*/
} FSeqEditStr;

void idFSEQuenceEDIT(STR_PARSER * p)
{
	GW_TYPE value;
	FSeqEditStr F;
	FSeq_Timing_Str *FSeq_Data_tmp = &P3k_FSeq_Data;
	FSeq_Timing_Str *FSeq_Disp_tmp = &P3k_FSeq_Disp;

	UBYTE Command_Done=1;
	char str[64],index_for_fill_item;
	char ON_OFF[2][4]= {"OFF","ON"};
	double Resolution_tmp,MaxValue,MinValue,Para_s;
	UWORD Max_tmp,Min_tmp;
	BYTE Precision_tmp;
	UWORD i;

	UBYTE I_Range	= FSeq_Disp_tmp->FSeq_Range%2;
	UBYTE FSeq_Mode = FSeq_Disp_tmp->FSeq_Mode;
	UWORD *FSeq_Disp_Edit_Value = &FSeq_Disp_tmp->FSeq_Step[FSeq_Disp_tmp->FSeq_Curr_Step].FSeq_Value;
	UBYTE *FSeq_Disp_Edit_Trig_Out = &FSeq_Disp_tmp->FSeq_Step[FSeq_Disp_tmp->FSeq_Curr_Step].TrigOut_Setting;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	//SCPI_KIKUSUI least one parameter	(-1)

	if (copy_SCPI_Company==SCPI_KIKUSUI)
		i =1;
	else
		i=0;

	if(FSeq_Mode==CC_MODE) {
		Resolution_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
	} else if (FSeq_Mode==CR_MODE) {
		Resolution_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].precision;
	}
	Para_s = Get_Parallel_Parameter(1);

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Step:%04d/%04d; Value:%.*f, TRIG OUT:%s"
		        ,FSeq_Disp_tmp->FSeq_Curr_Step+1,FSeq_Disp_tmp->FSeq_Max_Step+1
		        ,Precision_tmp,*FSeq_Disp_Edit_Value*Resolution_tmp*Get_Parallel_Parameter(I_Range)
		        ,ON_OFF[*FSeq_Disp_Edit_Trig_Out]);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		//CurrStep :0
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si<SCPI_FSEQ_Max_Step_Lower)||(value.si>SCPI_FSEQ_Step_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			F.CurrStep = value.si;
		} else
			Command_Done =0;
		//MaxStep :1

		if (copy_SCPI_Company==SCPI_GW) {
			if(0 == scpi_GetIntegerParameters( p, 1, (int*) &value.si)) {
				if((value.si<SCPI_FSEQ_Max_Step_Lower)||(value.si>SCPI_FSEQ_Step_Upper)) {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
				F.MaxStep= value.si;
			} else
				Command_Done =0;
			if(F.CurrStep>F.MaxStep) {
				scpi_SetCommandError( p, _ERR_221_Settings_conflict);
				return;
			}
		}

		else if (copy_SCPI_Company==SCPI_KIKUSUI) {
			F.MaxStep= FSeq_Disp_tmp->FSeq_Max_Step+1;
		}
		MaxValue= (double)Max_tmp*Resolution_tmp;
		MinValue= (double)Min_tmp*Resolution_tmp;

		//Value :2
		if(0 == scpi_GetFloatIntegerParameters( p, (2-i), (double*) &value.d)) {
			F.Value = value.d/Para_s;
			if((F.Value<MinValue)||(F.Value>MaxValue)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			F.ValueCount = SCPI_InputToStep(F.Value,Resolution_tmp);
		} else
			Command_Done =0;
		//trig out :3
		if(0 == scpi_GetIntegerParameters( p, 3, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			F.TrigOut= (1 == value.si) ? 1 : 0;
		} else if(0 == scpi_GetKeywordParameters( p, (3-i), (int*) &value.si)) {
			F.TrigOut = (1 == value.si) ? 1 : 0;
		} else
			Command_Done =0;

		if(Command_Done==0) {
			scpi_SetCommandError( p, _ERR_220_Parameter_error);
			return;
		}
		if(Command_Done) {
			//current
			FSeq_Disp_tmp->FSeq_Curr_Step=F.CurrStep-1;
			//max
			FSeq_Disp_tmp->FSeq_Max_Step=F.MaxStep-1;
			//value
			FSeq_Disp_tmp->FSeq_Step[FSeq_Disp_tmp->FSeq_Curr_Step].FSeq_Value = F.ValueCount;
			//trig out
			FSeq_Disp_Edit_Trig_Out = &FSeq_Disp_tmp->FSeq_Step[FSeq_Disp_tmp->FSeq_Curr_Step].TrigOut_Setting;
			*FSeq_Disp_Edit_Trig_Out= F.TrigOut;
			asm("nop;"); //be safe
			*FSeq_Data_tmp=*FSeq_Disp_tmp;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				Draw_Set_parameter();				
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_FSeq_Data(Backup);
		}
	}
// Code End

}
void idFSEQuenceEDITPOINt(STR_PARSER * p)
{
	GW_TYPE value;
	FSeq_Timing_Str *FSeq_Data_tmp = &P3k_FSeq_Data;
	FSeq_Timing_Str *FSeq_Disp_tmp = &P3k_FSeq_Disp;
	UWORD SettingCount;
	UBYTE Command_Done=0;
	char str[12];

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(FSeq_Disp_tmp->FSeq_Max_Step > 0xFFF0) {
			ExportProcess(Integer_Data,0,0,0,0);
		} else {
			ExportProcess(Integer_Data,0,FSeq_Disp_tmp->FSeq_Curr_Step+1,0,0);
		}
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(FSeq_Disp_tmp->FSeq_Max_Step > 0xFFF0) {
				return;
			}
			if((value.si > 1000)||(value.si< 1)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			if(value.si > (FSeq_Disp_tmp->FSeq_Max_Step+1)) {
				scpi_SetCommandError( p, _ERR_221_Settings_conflict);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}

		if(Command_Done) {
			//current
			FSeq_Disp_tmp->FSeq_Curr_Step = SettingCount-1;
			FSeq_Data_tmp->FSeq_Curr_Step = SettingCount-1;
			asm("nop;");
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				Draw_Set_parameter();				
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_FSeq_Data(Backup);
		}
	}
// Code End

}


void idFSEQuenceEDITEND(STR_PARSER * p)
{
	GW_TYPE value;
	FSeq_Timing_Str *FSeq_Disp_tmp = &P3k_FSeq_Disp;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(FSeq_Disp_tmp->FSeq_Max_Step > 0xFFF0)
			ExportProcess(Integer_Data,0,0,0,0);
		else
			ExportProcess(Integer_Data,0,FSeq_Disp_tmp->FSeq_Max_Step+1,0,0);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}

void idFSEQuenceDELetALL(STR_PARSER * p)
{
	UWORD i;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(P3k_FSeq_Disp.FSeq_Max_Step>0xFF00) {
			P3k_FSeq_Disp.FSeq_Max_Step =0;
			return;
		}
		for (i = P3k_FSeq_Disp.FSeq_Curr_Step; i < P3k_FSeq_Disp.FSeq_Max_Step; i++) {
			P3k_FSeq_Disp.FSeq_Step[i].FSeq_Value = 0;
			P3k_FSeq_Disp.FSeq_Step[i].TrigOut_Setting = 0;
		}

		P3k_FSeq_Disp.FSeq_Curr_Step = 0;
		P3k_FSeq_Disp.FSeq_Max_Step=0xFFFF; //-1
#if Enable_FSEQ_RPT
		P3k_FSeq_Disp.RPTStep = 0;
#endif		

		SEQ_Save_Status = 1;
		if(M_num==P_FSeq_Edit)
			DispMode = DispMode_SELECT_CH;
		if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
			DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
			Draw_Set_parameter();			
			MenuRedrawFlag |= MENU2_CHANGE + MENU3_CHANGE;
		}
	}
// Code End
}
typedef struct	{
	double StartValue;			/*	SettingValue	           */
	UWORD StartValueCount;		/*	SettingValueCount      */
	double EndValue;			/*	SettingValue	           */
	UWORD EndValueCount;		/*	SettingValueCount      */
	UWORD StartStep;			/*	0~1000	                */
	UWORD EndStep;			/*	0~1000	                */
} FSeqEditFillStr;

void idFSEQuenceEDITFILL(STR_PARSER * p)
{
	GW_TYPE value;
	FSeqEditFillStr F;

	FSeq_Timing_Str *FSeq_Data_tmp = &P3k_FSeq_Data;
	FSeq_Timing_Str *FSeq_Disp_tmp = &P3k_FSeq_Disp;

	UBYTE Command_Done=1;
	char  str[96],index_for_fill_item;
	double Resolution_tmp;
	UWORD Max_tmp,Min_tmp;
	double Max_Total,Min_Total;
	BYTE Precision_tmp,dat;
	double Para_s;

	UBYTE I_Range 	= FSeq_Disp_tmp->FSeq_Range%2;
	UBYTE FSeq_Mode	= FSeq_Disp_tmp->FSeq_Mode;
	UWORD *FSeq_Data_Fill_Item;
	Para_s = Get_Parallel_Parameter(I_Range);
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	//printf("para data:%d\n",Para_num);

	if(FSeq_Mode==CC_MODE) {
		Resolution_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
	} else if (FSeq_Mode==CR_MODE) {
		Resolution_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].precision;
	}

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if (copy_SCPI_Company==SCPI_GW) {
			sprintf(str,"Start Value:%.*f, End Value:%.*f, Start Step:%d, End Step:%d"
			        ,Precision_tmp,FSeq_Disp_tmp->Fill_Start_Value*Resolution_tmp*Para_s
			        ,Precision_tmp,FSeq_Disp_tmp->Fill_End_Value*Resolution_tmp*Para_s
			        ,FSeq_Disp_tmp->Fill_Start_Step+1,FSeq_Disp_tmp->Fill_End_Step+1);
		} else if(copy_SCPI_Company==SCPI_KIKUSUI) {
			sprintf(str,"Start Step:%d, Start Value:%.*f,End Step:%d , End Value:%.*f"
			        ,FSeq_Disp_tmp->Fill_Start_Step+1,Precision_tmp,FSeq_Disp_tmp->Fill_Start_Value*Resolution_tmp*Para_s
			        ,FSeq_Disp_tmp->Fill_End_Step+1,Precision_tmp,FSeq_Disp_tmp->Fill_End_Value*Resolution_tmp*Para_s);
		}

		ExportProcess(String_Data,0,0,str,0);
	} else {

		Max_Total=(double)Max_tmp*Resolution_tmp;
		Min_Total=(double)Min_tmp*Resolution_tmp;
		//stert_value : 0
		if(copy_SCPI_Company == SCPI_GW) dat =0;
		else							 dat =1;
		if(0 == scpi_GetFloatIntegerParameters( p, dat, (double*) &value.d))

		{
			F.StartValue= value.d/Para_s;
			if((F.StartValue<Min_Total)||(F.StartValue>Max_Total)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			F.StartValueCount = SCPI_InputToStep(F.StartValue,Resolution_tmp);
		} else
			Command_Done =0;
		//end_value : 1
		if(copy_SCPI_Company == SCPI_GW) dat =1;
		else							 dat =3;
		if(0 == scpi_GetFloatIntegerParameters( p, dat, (double*) &value.d))
		{
			F.EndValue= value.d/Para_s;
			if((F.EndValue<Min_Total)||(F.EndValue>Max_Total)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			F.EndValueCount= SCPI_InputToStep(F.EndValue,Resolution_tmp);
		} else
			Command_Done =0;
		//start_step : 2
			if(copy_SCPI_Company == SCPI_GW) dat =2;
			else							 dat =0;
			if(0 == scpi_GetFloatIntegerParameters( p, dat, (double*) &value.d))
			{
			if((value.si<SCPI_FSEQ_Max_Step_Lower)||(value.si>SCPI_FSEQ_Step_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			F.StartStep= value.si;
		} else
			Command_Done =0;
		//end_step : 3
			if(copy_SCPI_Company == SCPI_GW) dat =3;
			else							 dat =2;
			if(0 == scpi_GetFloatIntegerParameters( p, dat, (double*) &value.d))
			{
			if((value.si<SCPI_FSEQ_Max_Step_Lower)||(value.si>SCPI_FSEQ_Step_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			F.EndStep = value.si;
		} else
			Command_Done =0;

		if(Command_Done==0) {
			scpi_SetCommandError( p, _ERR_220_Parameter_error);
			return;
		}
		if(Command_Done) {
			FSeq_Data_tmp->Fill_Start_Value = F.StartValueCount;
			FSeq_Data_tmp->Fill_End_Value = F.EndValueCount;
			FSeq_Data_tmp->Fill_Start_Step=F.StartStep-1;
			FSeq_Data_tmp->Fill_End_Step=F.EndStep-1;
			asm("nop;"); //be safe
			*FSeq_Disp_tmp=*FSeq_Data_tmp;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if(/*(M_num==P_FSeq_Fill)&&*/(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				Draw_Set_parameter();
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(M_num==P_FSeq_Fill) {
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			SaveRecall_FSeq_Data(Backup);
			Save_Fill_Action(0,0);
		}
	}
// Code End

}

void idFSEQuenceSAVE(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		P3k_FSeq_Data = P3k_FSeq_Disp;
		BackupFSeq();
		SEQ_Save_Status = 0;
		if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu))
			MenuRedrawFlag |= MENU3_CHANGE;
	}
// Code End
}

void idOCPSTATe(STR_PARSER * p)
{
#if Enable_OCP_function
	GW_TYPE value;
	UBYTE Command_Done=0, SettingBool;
	P3k_OCP_OPP_Str *Data_tmp = &P3K_OCP_Data;
	P3k_OCP_OPP_Str *Disp_tmp = &P3K_OCP_Disp;
	p3k_send_tx_list	tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if (P3k_Disp_Data.Load_Type!=SCPI_OCP_Func)
			ExportProcess(String_Data,0,0,"OFF",0);
		else {
			if(P_FSeq_EXECUTE != M_num)
				ExportProcess(String_Data,0,0,"ON,OFF",0);
			else if(Disp_tmp->Complete==0)	
				ExportProcess(String_Data,0,0,"ON,START",0);
			else if(Disp_tmp->Complete==1)
				ExportProcess(String_Data,0,0,"ON,RUN",0);
			else
				ExportProcess(String_Data,0,0,"ON,END",0);
		}
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? SCPI_OCP_Func: SCPI_Load;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? SCPI_OCP_Func : SCPI_Load;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if (Command_Done) {
			P3k_Disp_Data.Load_Type = SettingBool;
			P3k_Chan_Data.Load_Type = SettingBool;
			asm("nop;");
			if(/*(M_num==P_PROG_MAIN)&&*/(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				SysRedrawFlag |= PROG_UPDATA + BG_CLEAR_FLAG;
				MenuRedrawFlag |= MENU1_CHANGE;
			}
		}
	}
#endif

}

void idOCPSTATus(STR_PARSER * p) //will check
{
	GW_TYPE value;
	P3k_OCP_OPP_Str *Disp_tmp = &P3K_OCP_Disp;

	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		
		if(P_FSeq_EXECUTE != M_num)
			ExportProcess(String_Data,0,0,"0",0);
		else if(Disp_tmp->Complete==0)	
			ExportProcess(String_Data,0,0,"0",0);
		else if(Disp_tmp->Complete==1)
			ExportProcess(String_Data,0,0,"1",0);
		else
			ExportProcess(String_Data,0,0,"0",0);
		

	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}



typedef struct	{
	UBYTE Temp;			/*1~12									*/
	UBYTE Range;		/*	High,Middle,Low /clear current parameter  */	
	UWORD StartCurrWatt;	/*	 */
	UWORD EndCurrWatt;		/*	 */
	UWORD StepCurrWatt;		/*    */
	UWORD StepTime;		/*	0.01~50	           			*/
	UWORD DelayTime;	/*	0.01~49.99 & <steptime  	*/
	UWORD TrigVolt;		/*	0.01~150					*/
	UWORD LastCurrWatt;
} OCP_FUN_Str;


void idOCPEDITCHANnel(STR_PARSER * p)
{
#if Enable_OCP_function
	GW_TYPE value;
	OCP_FUN_Str O;

	F_OCP_OPP_Str *Disp_tmp = &P3K_OCP_Disp.Seq[P3K_OCP_Disp.CurrTemp];
	F_OCP_OPP_Str *Data_tmp;

	UBYTE Command_Done=1,length;
	char str[128],index;
	double Para_s;
	

	double Resolution_tmp,Real_Value;
	UWORD Max_tmp,Min_tmp,SettingCount;
	BYTE Precision_tmp;
	UBYTE I_Range = Disp_tmp->Range;
	double Time_Reslolution = 0.01;
	
	Resolution_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
	Max_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
	Min_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
	Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
	Para_s = Get_Parallel_Parameter(I_Range);
	char Range_String[3][8]= {"High","Middle","Low"};
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(1) {
			sprintf(str,"No:%02d, Range:%s, Start C:%.*f, End C:%.*f, Step C:%.*f, Step T:%2.2f, Delay:%2.2f, Trig V:%2.2f, Last C:%.*f"
				,P3K_OCP_Disp.CurrTemp+1
				,Range_String[I_Range]
				,Precision_tmp,Disp_tmp->StartCurrWatt*Resolution_tmp*Para_s
				,Precision_tmp,Disp_tmp->EndCurrWatt*Resolution_tmp*Para_s
				,Precision_tmp,Disp_tmp->StepCurrWatt*Resolution_tmp*Para_s
				,Disp_tmp->StepTime*Time_Reslolution
				,Disp_tmp->DelayTime*Time_Reslolution
				,Disp_tmp->TrigVolt*Time_Reslolution
				,Precision_tmp,Disp_tmp->LastCurrWatt*Resolution_tmp*Para_s);	
		}
		ExportProcess(String_Data,0,0,str,0);
	} else {
	
		//Temp :0
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si<1)||(value.si>12)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			O.Temp = value.si-1;
		} else
			Command_Done =0;
		
		//Range :1
		if(0 == scpi_GetKeywordParameters( p, 1, (int*) &value.si)) {
			if((value.si<0)||(value.si>3)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			O.Range = value.si;
		} else
			Command_Done =0;
		
		I_Range = O.Range;
		Resolution_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
		Para_s = Get_Parallel_Parameter(I_Range);
		//Start Curr :2		
		if(0 == scpi_GetFloatIntegerParameters( p, 2, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			if((Real_Value<Min_tmp*Resolution_tmp)||(Real_Value>Max_tmp*Resolution_tmp)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			O.StartCurrWatt = SCPI_InputToStep(Real_Value ,Resolution_tmp);
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}

		//End Curr :3		
		if(0 == scpi_GetFloatIntegerParameters( p, 3, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			if((Real_Value<Min_tmp*Resolution_tmp)||(Real_Value>Max_tmp*Resolution_tmp)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			O.EndCurrWatt = SCPI_InputToStep(Real_Value ,Resolution_tmp);
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}

		if(O.StartCurrWatt>O.EndCurrWatt){
			scpi_SetCommandError( p, _ERR_221_Settings_conflict);
			return;
		}

		//Step Curr :4	
		if(0 == scpi_GetFloatIntegerParameters( p, 4, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			if((Real_Value<Min_tmp*Resolution_tmp)||(Real_Value>Max_tmp*Resolution_tmp/2)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			O.StepCurrWatt = SCPI_InputToStep(Real_Value ,Resolution_tmp);
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}

		//Step Time:5
		if(0 == scpi_GetFloatIntegerParameters( p, 5, (double*) &value.d)) {
			if((value.d<0.009999)||(value.d>50.00001)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Real_Value = value.d;
			O.StepTime = SCPI_InputToStep(Real_Value ,Time_Reslolution);
		} else
			Command_Done =0;


		//Delay Time:6
		if(0 == scpi_GetFloatIntegerParameters( p, 6, (double*) &value.d)) {
			if((value.d<0.009999)||(value.d>50.00001)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Real_Value = value.d;
			O.DelayTime = SCPI_InputToStep(Real_Value ,Time_Reslolution);
		} else
			Command_Done =0;

		if(O.DelayTime>O.StepTime){
			scpi_SetCommandError( p, _ERR_221_Settings_conflict);
			return;
		}
		//Trig Volt :7
		if(0 == scpi_GetFloatIntegerParameters( p, 7, (double*) &value.d)) {
			if((value.d<0)||(value.d>150.001)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			O.TrigVolt = SCPI_InputToStep(value.d,0.01);
		} else
			Command_Done =0;

		//last Curr :8
		if(0 == scpi_GetFloatIntegerParameters( p, 8, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			if((Real_Value<Min_tmp*Resolution_tmp)||(Real_Value>Max_tmp*Resolution_tmp)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			O.LastCurrWatt = SCPI_InputToStep(Real_Value ,Resolution_tmp);
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}		

		if(Command_Done==0) {
			scpi_SetCommandError( p, _ERR_220_Parameter_error);
			return;
		}
		if(Command_Done) {
			//temp
			P3K_OCP_Disp.CurrTemp = O.Temp;			
			Disp_tmp = &P3K_OCP_Disp.Seq[O.Temp];
			Data_tmp = &P3K_OCP_Disp.Seq[O.Temp];
			Disp_tmp->Range = O.Range;
			Disp_tmp->StartCurrWatt = O.StartCurrWatt;
			Disp_tmp->EndCurrWatt = O.EndCurrWatt;
			Disp_tmp->StepCurrWatt = O.StepCurrWatt;
			Disp_tmp->StepTime = O.StepTime;
			Disp_tmp->DelayTime= O.DelayTime;
			Disp_tmp->TrigVolt= O.TrigVolt;
			Disp_tmp->LastCurrWatt= O.LastCurrWatt;

			P3K_OCP_Data.CurrTemp = P3K_OCP_Disp.CurrTemp;
			asm("nop;"); //be safe
			*Data_tmp=*Disp_tmp;			
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if(/*(M_num==P_Seq_Fast)&&*/(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE + BG_CLEAR_FLAG;
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
		}
	}
	// Code End
#endif

}

void idOCPCHANnelTEMP(STR_PARSER * p) //number
{
#if Enable_OCP_function
	GW_TYPE value;
	UWORD SettingCount;
	P3k_OCP_OPP_Str *Data_tmp = &P3K_OCP_Data;
	P3k_OCP_OPP_Str *Disp_tmp = &P3K_OCP_Disp;

	UBYTE Command_Done=0;
	char str[16],index;

	
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		ExportProcess(Integer_Data,0,Disp_tmp->CurrTemp+1,0,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si > 12)||(value.si< 1)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si-1;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {			
			Data_tmp->CurrTemp = SettingCount;
			Disp_tmp->CurrTemp = SettingCount;
			asm("nop;"); //be safe			
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
			ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
			DataRedrawFlag |= BG_CLEAR + PARA_CHANGE + BG_CLEAR_FLAG;
			SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
		}
	}
// Code End
#endif

}
void idOCPCHANnelNUMBer(STR_PARSER * p)
{
	idOCPCHANnelTEMP(p);
}

void idOCPCHANnelRANGe(STR_PARSER * p)
{
#if Enable_OCP_function

	GW_TYPE value;
	UBYTE SettingCount;
	F_OCP_OPP_Str *Data_tmp = &P3K_OCP_Data.Seq[P3K_OCP_Data.CurrTemp];
	F_OCP_OPP_Str *Disp_tmp = &P3K_OCP_Disp.Seq[P3K_OCP_Disp.CurrTemp];

	UBYTE Command_Done=0;
	char str[16],index;

	char Range_String[3][8]= {"Low","Middle","High"};
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"%s",Range_String[Disp_tmp->Range]);
		ExportProcess(String_Data,0,0,str,0);		
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = value.si;
			Command_Done = 1;			
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			Disp_tmp->Range = SettingCount;
			if(Disp_tmp->Range != Data_tmp->Range){
				Disp_tmp->StartCurrWatt = 0;
				Disp_tmp->EndCurrWatt = 1;
				Disp_tmp->StepCurrWatt = 1;
				Disp_tmp->LastCurrWatt = 0;
			}
			
			asm("nop;"); //be safe
			*Data_tmp=*Disp_tmp;			
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
			ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
			DataRedrawFlag |= BG_CLEAR + PARA_CHANGE + BG_CLEAR_FLAG;
			SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
		}
	}
	// Code End
#endif

}

void idOCPCHANnelSTARt(STR_PARSER * p)
{
#if Enable_OCP_function

	GW_TYPE value;
	UBYTE Command_Done=0;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	F_OCP_OPP_Str *Data_tmp = &P3K_OCP_Data.Seq[P3K_OCP_Data.CurrTemp];
	F_OCP_OPP_Str *Disp_tmp = &P3K_OCP_Disp.Seq[P3K_OCP_Disp.CurrTemp];
	
	char str[36],index;
	UWORD MaxTemp,MinTemp;
	BYTE Precision_tmp;
	UBYTE I_Range = Disp_tmp->Range;

	Para_s = Get_Parallel_Parameter(I_Range);
	ResolutionTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
	MaxTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Max-1;
	MinTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
	Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
 
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Real_Value = (double)Disp_tmp->StartCurrWatt*ResolutionTemp*Para_s;
		if(Precision_tmp==1)
			sprintf(str,"%4.1f",Real_Value);
		else if(Precision_tmp==2)
			sprintf(str,"%3.2f",Real_Value);
		else if(Precision_tmp==3)
			sprintf(str,"%2.3f",Real_Value);
		else
			sprintf(str,"%2.4f",Real_Value);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			if((Real_Value<MinTemp*ResolutionTemp)||(Real_Value>MaxTemp*ResolutionTemp)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value ,ResolutionTemp);
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			Disp_tmp->StartCurrWatt = SettingCount;
			Data_tmp->StartCurrWatt = SettingCount;			
			if(Disp_tmp->StartCurrWatt>=Disp_tmp->EndCurrWatt){
				Disp_tmp->EndCurrWatt = Disp_tmp->StartCurrWatt+1;
				Data_tmp->EndCurrWatt = Disp_tmp->EndCurrWatt;
			}
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
		}
	}
// Code End
#endif

}

void idOCPCHANnelEND(STR_PARSER * p)
{
#if Enable_OCP_function

	GW_TYPE value;
	UBYTE Command_Done=0;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	F_OCP_OPP_Str *Data_tmp = &P3K_OCP_Data.Seq[P3K_OCP_Data.CurrTemp];
	F_OCP_OPP_Str *Disp_tmp = &P3K_OCP_Disp.Seq[P3K_OCP_Disp.CurrTemp];
	
	char str[36],index;
	UWORD MaxTemp,MinTemp;
	BYTE Precision_tmp;
	UBYTE I_Range = Disp_tmp->Range;

	Para_s = Get_Parallel_Parameter(I_Range);
	ResolutionTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
	MaxTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
	MinTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Min+1;
	Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
 
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Real_Value = (double)Disp_tmp->EndCurrWatt*ResolutionTemp*Para_s;
		if(Precision_tmp==1)
			sprintf(str,"%4.1f",Real_Value);
		else if(Precision_tmp==2)
			sprintf(str,"%3.2f",Real_Value);
		else if(Precision_tmp==3)
			sprintf(str,"%2.3f",Real_Value);
		else
			sprintf(str,"%2.4f",Real_Value);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			if((Real_Value<MinTemp*ResolutionTemp)||(Real_Value>MaxTemp*ResolutionTemp)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value ,ResolutionTemp);
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			Disp_tmp->EndCurrWatt = SettingCount;
			Data_tmp->EndCurrWatt = SettingCount;
			if(Disp_tmp->EndCurrWatt<=Disp_tmp->StartCurrWatt){
				Disp_tmp->StartCurrWatt = Disp_tmp->EndCurrWatt-1;
				Data_tmp->StartCurrWatt = Disp_tmp->StartCurrWatt; 
			}
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
		}
	}
// Code End
#endif

}

void idOCPCHANnelStepCurrWattent(STR_PARSER * p)
{
#if Enable_OCP_function

	GW_TYPE value;
	UBYTE Command_Done=0;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	F_OCP_OPP_Str *Data_tmp = &P3K_OCP_Data.Seq[P3K_OCP_Data.CurrTemp];
	F_OCP_OPP_Str *Disp_tmp = &P3K_OCP_Disp.Seq[P3K_OCP_Disp.CurrTemp];
	
	char str[36],index;
	UWORD MaxTemp,MinTemp;
	BYTE Precision_tmp;
	UBYTE I_Range = Disp_tmp->Range;

	Para_s = Get_Parallel_Parameter(I_Range);
	ResolutionTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
	MaxTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Max/2;
	MinTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
	Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
 
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Real_Value = (double)Disp_tmp->StepCurrWatt*ResolutionTemp*Para_s;
		if(Precision_tmp==1)
			sprintf(str,"%4.1f",Real_Value);
		else if(Precision_tmp==2)
			sprintf(str,"%3.2f",Real_Value);
		else if(Precision_tmp==3)
			sprintf(str,"%2.3f",Real_Value);
		else
			sprintf(str,"%2.4f",Real_Value);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			if((Real_Value<MinTemp*ResolutionTemp)||(Real_Value>MaxTemp*ResolutionTemp)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value ,ResolutionTemp);
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			Disp_tmp->StepCurrWatt = SettingCount;
			Data_tmp->StepCurrWatt = SettingCount;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
		}
	}
// Code End
#endif

}

void idOCPCHANnelLAST(STR_PARSER * p)
{
#if Enable_OCP_function

	GW_TYPE value;
	UBYTE Command_Done=0;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	F_OCP_OPP_Str *Data_tmp = &P3K_OCP_Data.Seq[P3K_OCP_Data.CurrTemp];
	F_OCP_OPP_Str *Disp_tmp = &P3K_OCP_Disp.Seq[P3K_OCP_Disp.CurrTemp];
	
	char str[36],index;
	UWORD MaxTemp,MinTemp;
	BYTE Precision_tmp;
	UBYTE I_Range = Disp_tmp->Range;

	Para_s = Get_Parallel_Parameter(I_Range);
	ResolutionTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
	MaxTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
	MinTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
	Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
 
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Real_Value = (double)Disp_tmp->LastCurrWatt*ResolutionTemp*Para_s;
		if(Precision_tmp==1)
			sprintf(str,"%4.1f",Real_Value);
		else if(Precision_tmp==2)
			sprintf(str,"%3.2f",Real_Value);
		else if(Precision_tmp==3)
			sprintf(str,"%2.3f",Real_Value);
		else
			sprintf(str,"%2.4f",Real_Value);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			if((Real_Value<MinTemp*ResolutionTemp)||(Real_Value>MaxTemp*ResolutionTemp)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value ,ResolutionTemp);
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			Disp_tmp->LastCurrWatt = SettingCount;
			Data_tmp->LastCurrWatt = SettingCount;			
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
		}
	}
// Code End
#endif

}

void idOCPCHANnelSTEPTIME(STR_PARSER * p)
{
#if Enable_OCP_function

	GW_TYPE value;
	UBYTE Command_Done=0;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp;
	F_OCP_OPP_Str *Data_tmp = &P3K_OCP_Data.Seq[P3K_OCP_Data.CurrTemp];
	F_OCP_OPP_Str *Disp_tmp = &P3K_OCP_Disp.Seq[P3K_OCP_Disp.CurrTemp];
	char str[10],index;
	
	ResolutionTemp=0.01; //convert micro second to milli second
	UWORD Time_Base_Precision =2;
	
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Real_Value = Disp_tmp->StepTime*ResolutionTemp;
		sprintf(str,"%.*f",Time_Base_Precision,Real_Value);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d ;
			if((Real_Value>50.001)||(Real_Value<0.0099))	{
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value ,ResolutionTemp);
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Disp_tmp->StepTime = SettingCount;
			Data_tmp->StepTime = SettingCount;
			if(Disp_tmp->DelayTime>=Disp_tmp->StepTime){
				Disp_tmp->DelayTime = Disp_tmp->StepTime-1;
				Data_tmp->DelayTime = Disp_tmp->DelayTime;
			}
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
			ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
			DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
			SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
		}
	}
// Code End
#endif

}

void idOCPCHANnelDELay(STR_PARSER * p)
{
#if Enable_OCP_function

	GW_TYPE value;
	UBYTE Command_Done=0;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp;
	F_OCP_OPP_Str *Data_tmp = &P3K_OCP_Data.Seq[P3K_OCP_Data.CurrTemp];
	F_OCP_OPP_Str *Disp_tmp = &P3K_OCP_Disp.Seq[P3K_OCP_Disp.CurrTemp];
	char str[10],index;
	
	ResolutionTemp=0.01; //convert micro second to milli second
	UWORD Time_Base_Precision =2;
	
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Real_Value = Disp_tmp->DelayTime*ResolutionTemp;
		sprintf(str,"%.*f",Time_Base_Precision,Real_Value);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d ;
			if((Real_Value>49.991)||(Real_Value<0))	{
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value ,ResolutionTemp);
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Disp_tmp->DelayTime = SettingCount;
			Data_tmp->DelayTime = SettingCount;
			if(Disp_tmp->DelayTime>=Disp_tmp->StepTime){
				Disp_tmp->StepTime = Disp_tmp->DelayTime + 1;
				Data_tmp->StepTime = Disp_tmp->DelayTime + 1;
			}
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
			ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
			DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
			SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
		}
	}
// Code End
#endif

}

void idOCPCHANnelTRIGger(STR_PARSER * p)
{
#if Enable_OCP_function

	GW_TYPE value;
	UBYTE Command_Done=0;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp;
	F_OCP_OPP_Str *Data_tmp = &P3K_OCP_Data.Seq[P3K_OCP_Data.CurrTemp];
	F_OCP_OPP_Str *Disp_tmp = &P3K_OCP_Disp.Seq[P3K_OCP_Disp.CurrTemp];
	char str[10],index;
	
	ResolutionTemp=0.01; //convert micro second to milli second
	UWORD Time_Base_Precision =2;
	
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		Real_Value = Disp_tmp->TrigVolt*ResolutionTemp;
		sprintf(str,"%.*f",Time_Base_Precision,Real_Value);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d ;
			if((Real_Value>150.001)||(Real_Value<0.0099)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value ,ResolutionTemp);
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Disp_tmp->TrigVolt= SettingCount;
			Data_tmp->TrigVolt= SettingCount;
			
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
			ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
			DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
			SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
		}
	}
// Code End
#endif

}

void idOCPSAVE(STR_PARSER * p)
{
#if Enable_OCP_function

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		P3K_OCP_Data = P3K_OCP_Disp;
		BackupOCP();
		SEQ_Save_Status = 0;
		if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu))
			MenuRedrawFlag |= MENU3_CHANGE;
		SCPI_RemFastDelay = 1;
	}
// Code End
#endif

}

void idOCPRESult(STR_PARSER * p)
{
#if Enable_OCP_function

	GW_TYPE value;
	UBYTE Command_Done=0;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	F_OCP_OPP_Str *Data_tmp = &P3K_OCP_Data.Seq[P3K_OCP_Data.CurrTemp];
	F_OCP_OPP_Str *Disp_tmp = &P3K_OCP_Disp.Seq[P3K_OCP_Disp.CurrTemp];
	
	char str[36],index;
	UWORD MaxTemp,MinTemp;
	BYTE Precision_tmp;
	UBYTE I_Range = Disp_tmp->Range;

	Para_s = Get_Parallel_Parameter(1);
	ResolutionTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
	MaxTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
	MinTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
	Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
 
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if((P3K_OCP_Disp.Complete==2)&&(M_num==0x2F)){
			Real_Value = (double)P3K_OCP_Disp.RecCurr[1]*ResolutionTemp*Para_s;
			if(Precision_tmp==1)
				sprintf(str,"%4.1f, %3.2f",Real_Value,Disp_tmp->TrigVolt*0.01);
			else if(Precision_tmp==2)
				sprintf(str,"%3.2f, %3.2f",Real_Value,Disp_tmp->TrigVolt*0.01);
			else if(Precision_tmp==3)
				sprintf(str,"%2.3f, %3.2f",Real_Value,Disp_tmp->TrigVolt*0.01);
			else
				sprintf(str,"%2.4f, %3.2f",Real_Value,Disp_tmp->TrigVolt*0.01);
		}else {
			sprintf(str,"0, 0");
		}
		ExportProcess(String_Data,0,0,str,0);
	} else {		
		scpi_SetCommandError( p, _ERR_310_System_error);		
	}
// Code End
#endif

}

void idOCPRUN(STR_PARSER * p)
{
#if Enable_OCP_function

// Code Begin
	UBYTE i;
	p3k_send_tx_list tx_data;
	if(scpi_IsQueryCommand(p)) {

	} else {
			//if(P3k_Disp_Data.Load_Type!= OCP_Load){
			//	if(UTILITY.LOAD_CTL) {
			//		UTILITY.LOAD_CTL=0x0;
			//		tx_data.ADDRH = 0x00;
			//		tx_data.ADDRL = 0x0B;
			//		SendTXData(&tx_data);					
			//	}
			//}	
			P3k_Chan_Data.Load_Type = OCP_Load;
			P3k_Disp_Data.Load_Type = OCP_Load;
			UTILITY.LOAD_CTL = 1;
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

			PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
			FunctionFlag  |= FUNC_NSEQ;
			M_num = P_FUNC_OCP_EXECUTE;
			MenuRedrawFlag |= MENU_CHANGE;
			DataRedrawFlag |= BG_CLEAR+PARA_CHANGE;
			ChanRedrawFlag |= BG_CLEAR;
		
	}
#endif

}

void idUTILitySYSTem(STR_PARSER * p) {
	id_IDN(p);
}

#if 0
void idUTILityREMote(STR_PARSER * p)
{
// Code Begin
	GW_TYPE value;
	UBYTE SettingBool,Command_Done=0;
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			//if(REM_CONT!=SettingBool) {
				REM_CONT = SettingBool;
				SysRedrawFlag |= REM_LOC_UPDATA;
				if( (DGIOCtrlFlag&REM_Mode_Fast)&&(REM_CONT==0) )
					SetRemoteMode(0);
				if( ((DGIOCtrlFlag&REM_Mode_Fast)==0)&&(REM_CONT) )
					SetRemoteMode(1);
			//}
		}
	}
// Code End
}
#else
void idUTILityREMote(STR_PARSER * p) //Local or Remote 
{
	// Code Begin
	GW_TYPE value;
	UBYTE SettingBool,Command_Done=0;
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if(REM_CONT!=SettingBool) {
				REM_CONT = SettingBool;
				SysRedrawFlag |= REM_LOC_UPDATA;
				if( (DGIOCtrlFlag&REM_Mode_Fast)&&(REM_CONT==0) )
					SetRemoteMode(0);
				if( ((DGIOCtrlFlag&REM_Mode_Fast)==0)&&(REM_CONT) )
					SetRemoteMode(1);
			}
		}
	}
	// Code End
}


#endif
void idUTILityREMoteMODE(STR_PARSER * p)
{
	// Code Begin
	GW_TYPE value;
	UBYTE SettingBool,Command_Done=0;
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			//if(REM_CONT!=SettingBool) {
			REM_CONT = SettingBool;
			SysRedrawFlag |= REM_LOC_UPDATA;
			if( (DGIOCtrlFlag&REM_Mode_Fast)&&(REM_CONT==0) )
				SetRemoteMode(0);
			if( ((DGIOCtrlFlag&REM_Mode_Fast)==0)&&(REM_CONT) )
				SetRemoteMode(1);
			REM_CONT = 1;
			SysRedrawFlag |= REM_LOC_UPDATA;
			//}
		}
	}
	// Code End
}

void idUTILityLOAD(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE SettingCount;
	UBYTE Command_Done=0;
	int String_Count=0;
	char str[32];
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if (UTILITY.ALOAD==SCPI_Auto_Load_Off)
			sprintf(str,"%s","Load:Off, ");
		else if (UTILITY.ALOAD==SCPI_Auto_Load_On)
			sprintf(str,"%s","Load:On, ");

		while(str[String_Count]!='\0')
			String_Count++;				//Present str size

		if (UTILITY.ALOAD_MODE==SCPI_Auto_Load_On_by_Load-SCPI_Auto_Load_On_by_Load)
			sprintf(&str[String_Count],"%s","Load On:Load");
		else if (UTILITY.ALOAD_MODE==SCPI_Auto_Load_On_by_Prog-SCPI_Auto_Load_On_by_Load)
			sprintf(&str[String_Count],"%s","Load On:Prog");
		else if (UTILITY.ALOAD_MODE==SCPI_Auto_Load_On_by_NSeq-SCPI_Auto_Load_On_by_Load)
			sprintf(&str[String_Count],"%s","Load On:NSeq");
		else if (UTILITY.ALOAD_MODE==SCPI_Auto_Load_On_by_FSeq-SCPI_Auto_Load_On_by_Load)
			sprintf(&str[String_Count],"%s","Load On:FSeq");

		ExportProcess(String_Data,0,0,str,0);
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount =  value.si;
			Command_Done = 1;
			switch(value.si) {
			case SCPI_Auto_Load_Off:
				UTILITY.ALOAD=SCPI_Auto_Load_Off;
				break;
			case SCPI_Auto_Load_On:
				UTILITY.ALOAD=SCPI_Auto_Load_On;
				break;
			case SCPI_Auto_Load_On_by_Load:
				UTILITY.ALOAD_MODE=0;
				break;
			case SCPI_Auto_Load_On_by_Prog:
				UTILITY.ALOAD_MODE=1;
				break;
			case SCPI_Auto_Load_On_by_NSeq:
				UTILITY.ALOAD_MODE=2;
				break;
			case SCPI_Auto_Load_On_by_FSeq:
				UTILITY.ALOAD_MODE=3;
				break;
			default:
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				break;
			}
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if (M_num == P_UTIL_LOAD)
				ClrDispCnt(0x00, 0x00, 3, 0x00, 0x00, 0x00);
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= UTIL_CHANGE + BG_CLEAR;
				Draw_Set_parameter();				
				ChanRedrawFlag |= BG_CLEAR;
			}
			if (M_num == P_UTIL_LOAD)DispMode =0;
		}
	}
// Code End
}

void idUTILityLOADMODE(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingBool;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(UTILITY.AutoLoadOffMode == SCPI_UTI_Other_Off)
			ExportProcess(String_Data,0,0,"Off",0);
		else if(UTILITY.AutoLoadOffMode == SCPI_UTI_Other_On)
			ExportProcess(String_Data,0,0,"On",0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			 UTILITY.AutoLoadOffMode = SettingBool;
			 //if (M_num == P_UTIL_LOAD)
				//ClrDispCnt(0x00, 0x00, 3, 0x00, 0x00, 0x00);
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= UTIL_CHANGE + BG_CLEAR;
				ChanRedrawFlag |= BG_CLEAR;
			}
			if (M_num == P_UTIL_LOAD)DispMode =0;
			
		}
	}
// Code End
}


void idUTILityLOADRANGe(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingBool;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(UTILITY.AutoLoadOffRange== SCPI_UTI_Other_Off)
			ExportProcess(String_Data,0,0,"Off",0);
		else if(UTILITY.AutoLoadOffRange == SCPI_UTI_Other_On)
			ExportProcess(String_Data,0,0,"On",0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			 UTILITY.AutoLoadOffRange = SettingBool;
			 //if (M_num == P_UTIL_LOAD)
				//ClrDispCnt(0x00, 0x00, 3, 0x00, 0x00, 0x00);
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= UTIL_CHANGE + BG_CLEAR;
				ChanRedrawFlag |= BG_CLEAR;
			}
			if (M_num == P_UTIL_LOAD)DispMode =0;
		}
	}
// Code End

}


void idUTILityINTerface(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE SettingCount,Command_Done=0;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if (D_interface.INTERFACE==SCPI_Interface_USB)
			ExportProcess(String_Data,0,0,"USB",0);
		else if (D_interface.INTERFACE==SCPI_Interface_GPIB)
			ExportProcess(String_Data,0,0,"GPIB",0);
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? 2 : 1;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			if((SYSType&GPIB_CONNECTED)==0){
				return;
			}
			UTILITY.INTERFACE=SettingCount;
			SysRedrawFlag |= Interface_UPDATA;
		}
	}
// Code End
}



typedef struct	{
	UWORD Year;		/*	SettingValueCount	   */
	UBYTE Month;		/*	SettingValueCount	   */
	UBYTE Day;		/*	SettingValueCount	   */
	UBYTE Hour;		/*	SettingValueCount	   */
	UBYTE Minute;		/*	SettingValueCount	   */
} UTimeStr;

void idUTILityTIME(STR_PARSER * p)
{
	GW_TYPE value;
	UTimeStr T;
	UBYTE Command_Done=1;
	char str[48];

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		sprintf(str,"Month:%d, Day:%d, Year:%d, Hour:%d, Minute:%d",TIMERSET.MONTH,TIMERSET._DAY,TIMERSET.YEAR,TIMERSET._HOUR,TIMERSET._MINUTE);
		ExportProcess(String_Data,0,0,str,0);
	} else {
		//Month : 0
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si<1)||(value.si>12)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			T.Month= value.si;
		} else
			Command_Done =0;
		//Day : 1
		if(0 == scpi_GetIntegerParameters( p, 1, (int*) &value.si)) {
			if((value.si<1)||(value.si>31)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			T.Day= value.si;
		} else
			Command_Done =0;
		//Year : 2
		if(0 == scpi_GetIntegerParameters( p, 2, (int*) &value.si)) {
			if((value.si<1990)||(value.si>2040)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			T.Year = value.si;
		} else
			Command_Done =0;
		//Hour : 3
		if(0 == scpi_GetIntegerParameters( p, 3, (int*) &value.si)) {
			if((value.si<1)||(value.si>24)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			T.Hour = value.si;
		} else
			Command_Done =0;
		//Minute : 4
		if(0 == scpi_GetIntegerParameters( p, 4, (int*) &value.si)) {
			if((value.si<1)||(value.si>59)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			T.Minute = value.si;
		} else
			Command_Done =0;

		if(((T.Month==4)||(T.Month==6)||(T.Month==8)||(T.Month==9)||(T.Month==11))&&(T.Day>30)) {
			Command_Done = 0;
		} else if(((modf(T.Year,(double*)4)==0)&&(T.Month==2))&&(T.Day>29)) {
			Command_Done = 0;
		} else if(((modf(T.Year,(double*)4)!=0)&&(T.Month==2))&&(T.Day>28)) {
			Command_Done = 0;
		}
		if(Command_Done==0) {
			scpi_SetCommandError( p, _ERR_108_Parameter_not_allowed);
			return;
		}
		if(Command_Done) {
			TIMERSET.MONTH = T.Month;
			TIMERSET._DAY = T.Day;
			TIMERSET.YEAR= T.Year;
			TIMERSET._HOUR = T.Hour;
			TIMERSET._MINUTE = T.Minute;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				asm("nop;");
				asm("nop;");
				SetRTC(0);
				SysRedrawFlag |= TIME_UPDATA;
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				if (M_num == P_UTIL_T_DATE)DispMode =0;
			}
			SCPI_RemFastDelay = 1;
		}
	}
// Code End
}

void idUTILityKNOB(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingCount;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(UTILITY.KEYKNOB==SCPI_UTI_Other_Knob_Old_or_Hold)
			ExportProcess(String_Data,0,0,"Old",0);
		else if(UTILITY.KEYKNOB==SCPI_UTI_Other_Knob_Updated)
			ExportProcess(String_Data,0,0,"Updated",0);

	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			UTILITY.KEYKNOB = SettingCount;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= UTIL_CHANGE + BG_CLEAR;
				ChanRedrawFlag |= BG_CLEAR;
			}
			if (M_num == 0x21)DispMode =0;
		}
	}
// Code End
}

void idUTILitySPEaker(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingBool;
	p3k_send_tx_list	tx_data;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(UTILITY.BEEP_ONOFF == SCPI_UTI_Other_Off)
			ExportProcess(String_Data,0,0,"Off",0);
		else if(UTILITY.BEEP_ONOFF == SCPI_UTI_Other_On)
			ExportProcess(String_Data,0,0,"On",0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			UTILITY.BEEP_ONOFF = SettingBool;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= UTIL_CHANGE + BG_CLEAR;
				ChanRedrawFlag |= BG_CLEAR;
			}

			if(UTILITY.KEYKNOB==SCPI_UTI_Other_Knob_Updated) {
				tx_data.ADDRH = Machine_Command;
				tx_data.ADDRL = 0x0C;
				SendTXData(&tx_data);
			}
			if (M_num == 0x21)DispMode =0;
		}
	}
// Code End
}

void idUTILityALARm(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingBool;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(UTILITY.Master_Alarm_Tone == SCPI_UTI_Other_Off)
			ExportProcess(String_Data,0,0,"Off",0);
		else if(UTILITY.Master_Alarm_Tone == SCPI_UTI_Other_On)
			ExportProcess(String_Data,0,0,"On",0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			UTILITY.Master_Alarm_Tone = SettingBool;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= UTIL_CHANGE + BG_CLEAR;
				ChanRedrawFlag |= BG_CLEAR;
			}
			if((UnReg_Alarm != p3k_Measure_Data.Alarm) && (p3k_Measure_Data.Alarm != 0) && (UTILITY.Master_Alarm_Tone) && (!Tone_Flag)) {
				Tone_Flag|=0x01;
				Alarm_Count = 250;
				BuzzerFunction(Buzzer_Alarm,Alarm_Count--);
			}
			if (M_num == 0x21)DispMode =0;
		}
	}
// Code End

}

void idUTILityUNReg(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingBool;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(UTILITY.UnReg_Alarm_Tone == SCPI_UTI_Other_Off)
			ExportProcess(String_Data,0,0,"Off",0);
		else if(UTILITY.UnReg_Alarm_Tone == SCPI_UTI_Other_On)
			ExportProcess(String_Data,0,0,"On",0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			UTILITY.UnReg_Alarm_Tone = SettingBool;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= UTIL_CHANGE + BG_CLEAR;
				ChanRedrawFlag |= BG_CLEAR;
			}
			if((p3k_Measure_Data.Alarm == UnReg_Alarm)&&(UTILITY.UnReg_Alarm_Tone)&&(!Tone_Flag)) {
				Tone_Flag |= 0x04;
				UnReg_Count = 200;
				BuzzerFunction(Buzzer_UnReg,UnReg_Count--);
			}
			if (M_num == 0x21)DispMode =0;
		}
	}
// Code End
}

void idUTILityGNG(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingBool;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(UTILITY.Master_NG_Tone == SCPI_UTI_Other_Off)
			ExportProcess(String_Data,0,0,"Off",0);
		else if(UTILITY.Master_NG_Tone == SCPI_UTI_Other_On)
			ExportProcess(String_Data,0,0,"On",0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			UTILITY.Master_NG_Tone = SettingBool;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= UTIL_CHANGE + BG_CLEAR;
				ChanRedrawFlag |= BG_CLEAR;
			}
			if((p3k_Measure_Data.Go_NoGo == 1)&&(UTILITY.Master_NG_Tone)&&(!Tone_Flag)) {
				Tone_Flag |= 0x02;
				NG_Count = 300;
				BuzzerFunction(Buzzer_NG,NG_Count--);
			}
			if (M_num == 0x21)DispMode =0;
		}
	}
// Code End
}

void idUTILityCONTrast(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingCount;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		ExportProcess(Integer_Data,0,UTILITY.CONTRAST_LV,0,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si > 13)||(value.si < 3)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if (M_num == 0x21)DispMode =0;
			UTILITY.CONTRAST_LV=SettingCount;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= UTIL_CHANGE + BG_CLEAR;
				ChanRedrawFlag |= BG_CLEAR;
			}
			Control_LCDBRCon();
		}
	}
// Code End
}

void idUTILityBRIGhtness(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingCount;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		ExportProcess(Integer_Data,0,UTILITY.BRIGHTNESS_LV,0,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si > 90)||(value.si < 50)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if (M_num == 0x21)DispMode =0;
			UTILITY.BRIGHTNESS_LV = SettingCount;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= UTIL_CHANGE + BG_CLEAR;
				ChanRedrawFlag |= BG_CLEAR;
			}
			Control_LCDBRCon();
			SCPI_RemFastDelay = 1;
		}
	}
// Code End
}

void idUTILityLANGuage(STR_PARSER * p)
{
	GW_TYPE value;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		ExportProcess(String_Data,0,0,"English",0);
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {

		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
	}
// Code End
}

void idMEMorySAVE(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UWORD SettingCount;

	UBYTE i;
	ULONG Value_temp;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si > SCPI_Memory_Quantity_Upper)||(value.si < SCPI_Memory_Quantity_Lower)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			p3k_File_Utility_BAR.MEMORY_ADDR = SettingCount -1 ;
			Save2Mem(SR_MEMORY_MODE, p3k_File_Utility_BAR.MEMORY_ADDR);
			BackupRunProg();
			MEMORY_SAVE_FLAG = M_Memory_Save_Ok;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE ;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)DispMode = DispMode_BROWSE_ITEMS;
			SCPI_RemFastDelay = 1;
		}

	}
// Code End
}

void idMEMoryRECall(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UWORD SettingCount;

	UBYTE i,recall_status;
	ULONG Value_temp;
	char CURRMODE_temp,LOAD_CTL_temp;

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	p3k_file_util_str	*File_Utility=&p3k_File_Utility_BAR;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si > SCPI_Memory_Quantity_Upper)||(value.si < SCPI_Memory_Quantity_Lower)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			recall_status = Data_tmp->CONF.Memory_Recall;
			Data_tmp->CONF.Memory_Recall =1;
			Disp_tmp->CONF.Memory_Recall =1;
			File_Utility->MEMORY_ADDR= SettingCount -1;
			CURRMODE_temp=Data_tmp->CURRMODE;
			Soft_Key_Temp=0;
			if(Recall2Mem(SR_MEMORY_MODE, p3k_File_Utility_BAR.MEMORY_ADDR)==0) {
				Soft_Key_Temp = 1;
				return;
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
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				ChanRedrawFlag |= CHAN_STATUS;
				DataRedrawFlag |=BG_CLEAR+ PARA_CHANGE;
				MenuRedrawFlag |= MENU_CHANGE;
			}
			ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
			DispMode = DispMode_BROWSE_ITEMS;

			Data_tmp->CONF.Memory_Recall = recall_status;
			Disp_tmp->CONF.Memory_Recall = recall_status;
			SCPI_RemFastDelay = 1;
		}
	}
// Code End
}

void idPRESetSAVE(STR_PARSER * p)
{
	GW_TYPE value;
	p3k_file_util_str	*File_Utility=&p3k_File_Utility_BAR;
	UBYTE Command_Done=0;
	UBYTE SettingCount;

	char str[30];
	UBYTE i,save_number;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si > SCPI_Preset_Quantity_Upper)||(value.si < SCPI_Preset_Quantity_Lower)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			save_number= SettingCount;
			File_Utility->PRE_MEMORY_ADDR=save_number;
			Save2Mem( SR_PRESET_MODE, save_number);
			MEMORY_SAVE_FLAG = M_Preset_Save_Ok;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				//MenuRedrawFlag |= MENU_CHANGE ;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
			}
			Freeze_Keyboard = 1;
			if(DispMode>DispMode_BROWSE_ITEMS)DispMode = DispMode_BROWSE_ITEMS;
			SCPI_RemFastDelay = 1;
		}
	}
// Code End
}

void idPRESetRECall(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingCount,recall_status;
	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	p3k_file_util_str	*File_Utility=&p3k_File_Utility_BAR;


	char str[30],save_number,LOAD_CTL_temp,CURRMODE_temp;
	UBYTE i;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si > SCPI_Preset_Quantity_Upper)||(value.si < SCPI_Preset_Quantity_Lower)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			recall_status = Data_tmp->CONF.Memory_Recall;
			Data_tmp->CONF.Memory_Recall =1;
			Disp_tmp->CONF.Memory_Recall =1;
			save_number = SettingCount;
			File_Utility->PRE_MEMORY_ADDR = save_number;
			CURRMODE_temp=Data_tmp->CURRMODE;
			Recall2Mem( SR_PRESET_MODE, save_number);

			if(Recall2Mem( SR_PRESET_MODE, p3k_File_Utility_BAR.PRE_MEMORY_ADDR)==0) {
				Soft_Key_Temp = 1;
				return;
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
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
				ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
			}
			DispMode = DispMode_BROWSE_ITEMS;
			Data_tmp->CONF.Memory_Recall = recall_status;
			Disp_tmp->CONF.Memory_Recall = recall_status;
			SCPI_RemFastDelay = 1;
		}
	}
// Code End
}

void idSETupSAVE(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingCount;
	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	p3k_file_util_str	*File_Utility=&p3k_File_Utility_BAR;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si > SCPI_Setup_Quantity_Upper)||(value.si < SCPI_Setup_Quantity_Lower)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			p3k_File_Utility_BAR.SMEMORY_ADDR = SettingCount-1;
			MEMORY_SAVE_FLAG = M_Setup_Save_Ok;
			SaveSetupDataAction(p3k_File_Utility_BAR.SMEMORY_ADDR);
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE + MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)DispMode = DispMode_BROWSE_ITEMS;
			SCPI_RemFastDelay = 1;
		}
	}
// Code End
}

void idSETupRECall(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingCount,recall_status;

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	p3k_file_util_str	*File_Utility=&p3k_File_Utility_BAR;



	char str[30],CURRMODE_temp,LOAD_CTL_temp;;
	UBYTE i;
	char Recall_result,temp,mem;
	char status=0xff,Setup_Memory_Data=0;
	ULONG Value_temp;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si > SCPI_Setup_Quantity_Upper)||(value.si < SCPI_Setup_Quantity_Lower)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			recall_status = Data_tmp->CONF.Memory_Recall;
			Data_tmp->CONF.Memory_Recall =1;
			Disp_tmp->CONF.Memory_Recall =1;
			File_Utility->SMEMORY_ADDR=SettingCount-1;
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
			}
			MEMORY_SAVE_FLAG = M_Setup_Recall_Ok;
			DispMode = DispMode_SELECT_CH;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				ChanRedrawFlag |= CHAN_STATUS;
				DataRedrawFlag |= BG_CLEAR+ PARA_CHANGE;
				MenuRedrawFlag |= MENU_CHANGE;
			}
			RecallSetupData(p3k_File_Utility_BAR.SMEMORY_ADDR);
			DispMode = DispMode_BROWSE_ITEMS;
			Data_tmp->CONF.Memory_Recall = recall_status;
			Disp_tmp->CONF.Memory_Recall = recall_status;
			SCPI_RemFastDelay = 1;
		}
	}
// Code End

}

void idFACToryRECall(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingCount,recall_status;

	p3k_send_tx_list	tx_data;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	char Default_Message1[60],Default_Message2[60];
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		recall_status = Data_tmp->CONF.Memory_Recall;
		Data_tmp->CONF.Memory_Recall =1;
		Disp_tmp->CONF.Memory_Recall =1;
		if((M_num==0x1A)&&(p3k_File_Utility_BAR.MEDIA==F_Media_Default)&&(!SCPI_Freeze_menu)) {
			GUI_SetFont(Parameter_Font);
			GUI_SetBkColor(Message_Bottom_Bolor);
			GUI_SetColor(Message_Font_Bolor);
			sprintf(Default_Message1,"Recall Factory Default,\n");
			sprintf(Default_Message2,"Please Wait...\n");
			GUI_GotoXY(10, 175);
			GUI_DispChars(' ',51);
			GUI_GotoXY(10, 150);
			GUI_DispChars(' ',51);
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_DispStringAt(Default_Message1, 10, 150);
			GUI_DispStringAt(Default_Message2, 10, 175);
		}
		DMA_Update_Flag = 1;
		Update_Panel();
		Recall_Factory_Action(1);
		Default_info = 0;
		DispMode = DispMode_BROWSE_ITEMS;
		Data_tmp->CONF.Memory_Recall = recall_status;
		Disp_tmp->CONF.Memory_Recall = recall_status;
		SCPI_RemFastDelay = 1;
	}
// Code End
}

void idUSERDEFaultSAVE(STR_PARSER * p)
{
	char Default_Message1[60],Default_Message2[60];
	char str[30];

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if((M_num==0x1A)&&(p3k_File_Utility_BAR.MEDIA==F_Media_Default)&&(!SCPI_Freeze_menu)) {
			GUI_SetFont(Parameter_Font);
			GUI_SetBkColor(Message_Bottom_Bolor);
			GUI_SetColor(Message_Font_Bolor);
			GUI_GotoXY(10, 175);
			GUI_DispChars(' ',51);
			GUI_GotoXY(10, 150);
			GUI_DispChars(' ',51);
			GUI_SetTextAlign(GUI_TA_LEFT);
			sprintf(Default_Message2,"Save User's Default...\n");
			GUI_DispStringAt(Default_Message2, 10, 175);
			DMA_Update_Flag = 1;
			Update_Panel();
		}
		BackupUserDefaultData(1);
		if((M_num==0x1A)&&(p3k_File_Utility_BAR.MEDIA==F_Media_Default)&&(!SCPI_Freeze_menu)) {
			sprintf(SaveFileName_Temp,"User's Default");
			Save_Recall_InfoFlag |= Data_Process+Save_Ok;
			DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
			Default_info = 0;
		}
		if(DispMode>DispMode_BROWSE_ITEMS)DispMode = DispMode_BROWSE_ITEMS;
		SCPI_RemFastDelay = 1;
	}
// Code End
}

void idUSERDEFaultRECall(STR_PARSER * p)
{
	UBYTE Command_Done=0;
	UBYTE recall_status;
	char Default_Message1[60],Default_Message2[60];
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
// Code Begin
	if(scpi_IsQueryCommand(p)) {

	} else {
		recall_status = Data_tmp->CONF.Memory_Recall;
		Data_tmp->CONF.Memory_Recall =1;
		Disp_tmp->CONF.Memory_Recall =1;
		if((M_num==0x1A)&&(p3k_File_Utility_BAR.MEDIA==F_Media_Default)&&(!SCPI_Freeze_menu)) {
			GUI_SetFont(Parameter_Font);
			GUI_SetBkColor(Message_Bottom_Bolor);
			GUI_SetColor(Message_Font_Bolor);
			GUI_GotoXY(10, 175);
			GUI_DispChars(' ',51);
			GUI_GotoXY(10, 150);
			GUI_DispChars(' ',51);
			GUI_SetTextAlign(GUI_TA_LEFT);
			sprintf(Default_Message2,"Recall User's Default...\n");
			GUI_DispStringAt(Default_Message2, 10, 175);
		}
		DMA_Update_Flag = 1;
		Update_Panel();
		RecallUserDefault(1);
		Default_info = 0;
		DispMode = DispMode_BROWSE_ITEMS;
		Data_tmp->CONF.Memory_Recall = recall_status;
		Disp_tmp->CONF.Memory_Recall = recall_status;
		SCPI_RemFastDelay = 1;
	}
// Code End
}

void idSERialMASTer(STR_PARSER * p)
{
	GW_TYPE value;
	char Memo[20],length;

	UBYTE Command_Done=0,str_data;
	char str[36],index;
	UBYTE i;
	Serial_Number_Str *Serial=&P3k_Serial_Number;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		ExportProcess(String_Data,0,0,Serial->Product_Serial_Number,0);

	} else {
		Command_Done = 1;
		for (index=0; index<20; index++)
			Memo[index]='\0';
		if(1 == scpi_IsStringParameters( p, 0)) {
			length = scpi_GetStringParameters( p, 0, (unsigned int*) &value.ui); //'length', including the string terminator('\0').
			if((0 < length)&&(13 > length)) {
				strcpy(Memo, (char*)value.ui);
			} else {
				scpi_SetCommandError( p, _ERR_257_File_name_error);
				return;
			}
		} else {
			scpi_SetCommandError( p, _ERR_257_File_name_error);
			return;
		}
		if(Command_Done) {
			for (index=0; index<20; index++)
				Serial->Product_Serial_Number[index]='\0';
			for (index=0; ((Memo[index]!='\0')&&(index<16)); index++) {
				Serial->Product_Serial_Number[index]=Memo[index];
			}
			for (i=0; Serial->Product_Serial_Number[i]!='\0' || i<16; i++) {
				if ((Serial->Product_Serial_Number[i]>='a') && (Serial->Product_Serial_Number[i]<='z'))
					Serial->Product_Serial_Number[i]-=0x20; //lower case convert to upper case
			}
			ClrDispCnt(0x00, 0x00, 3, 0x00, 0x00, 0x00);
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= UTIL_CHANGE + BG_CLEAR;
				ChanRedrawFlag |= BG_CLEAR;
			}
			BackupSerialNumber();
			SCPI_RemFastDelay = 1;
		}
	}
// Code End
}
void idSTATusPRESet(STR_PARSER * p)
{
// Code Begin
	//_DEBUG_MSG("idStatPres\n");
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		intfSCPI_SetQuesReg(p->pInterface,_INTF_REG_ENAB, 0);
		intfSCPI_SetQuesReg(p->pInterface,_INTF_REG_PTR, 0x7FFF);
		intfSCPI_SetQuesReg(p->pInterface,_INTF_REG_NTR, 0);

		intfSCPI_SetOperReg(p->pInterface,_INTF_REG_ENAB, 0);
		intfSCPI_SetOperReg(p->pInterface,_INTF_REG_PTR, 0x7FFF);
		intfSCPI_SetOperReg(p->pInterface,_INTF_REG_NTR, 0);

		intfSCPI_SetCsumReg(p->pInterface,_INTF_REG_ENAB, 0);
		intfSCPI_SetCsumReg(p->pInterface,_INTF_REG_PTR, 0x7FFF);
		intfSCPI_SetCsumReg(p->pInterface,_INTF_REG_NTR, 0);
	}
// Code End

}

void idSTATusQUEStionableCONDition(STR_PARSER * p)
{
// Code Begin
	//_DEBUG_MSG("idStatQuesCond\n");
	if(scpi_IsQueryCommand(p)) {
		UWORD realValue;
		realValue = intfSCPI_GetQuesReg(p->pInterface,_INTF_REG_COND);
		ExportProcess(Integer_Data,0,realValue,0,0);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End

}

void idSTATusQUEStionableENABle(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		UWORD realValue;
		realValue = intfSCPI_GetQuesReg(p->pInterface,_INTF_REG_ENAB);
		ExportProcess(Integer_Data,0,realValue,0,0);
	} else {
		GW_TYPE value;
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			intfSCPI_SetQuesReg(p->pInterface,_INTF_REG_ENAB, value.si);
		} else {
			scpi_SetCommandError( p, _ERR_113_Undefined_header);
		}
	}
// Code End

}

void idSTATusQUEStionableEVENt(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		UWORD realValue;
		realValue = intfSCPI_GetQuesReg(p->pInterface,_INTF_REG_EVEN);
		ExportProcess(Integer_Data,0,realValue,0,0);
		intfSCPI_SetQuesReg(p->pInterface, _INTF_REG_EVEN, 0);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}

void idSTATusQUEStionableNTRansition(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		UWORD realValue;
		realValue = intfSCPI_GetQuesReg(p->pInterface,_INTF_REG_NTR);
		ExportProcess(Integer_Data,0,realValue,0,0);
	} else {
		GW_TYPE value;
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			intfSCPI_SetQuesReg(p->pInterface,_INTF_REG_NTR, value.si);
		} else {
			scpi_SetCommandError( p, _ERR_113_Undefined_header);
		}
	}
// Code End

}

void idSTATusQUEStionablePTRansition(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		UWORD realValue;
		realValue = intfSCPI_GetQuesReg(p->pInterface,_INTF_REG_PTR);
		ExportProcess(Integer_Data,0,realValue,0,0);
	} else {
		GW_TYPE value;
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			intfSCPI_SetQuesReg(p->pInterface,_INTF_REG_PTR, value.si);
		} else {
			scpi_SetCommandError( p, _ERR_113_Undefined_header);
		}
	}
// Code End

}

void idSTATusOPERationCONDition(STR_PARSER * p)
{
	UWORD realValue;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		realValue = intfSCPI_GetOperReg(p->pInterface,_INTF_REG_COND);
		ExportProcess(Integer_Data,0,realValue,0,0);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End

}

void idSTATusOPERationENABle(STR_PARSER * p)
{

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		UWORD realValue;
		realValue = intfSCPI_GetOperReg(p->pInterface,_INTF_REG_ENAB);
		ExportProcess(Integer_Data,0,realValue,0,0);
	} else {
		GW_TYPE value;
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			intfSCPI_SetOperReg(p->pInterface,_INTF_REG_ENAB, value.si);
		} else {
			scpi_SetCommandError( p, _ERR_113_Undefined_header);
		}
	}
// Code End

}

void idSTATusOPERationEVENt(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		UWORD realValue;
		realValue = intfSCPI_GetOperReg(p->pInterface,_INTF_REG_EVEN);
		ExportProcess(Integer_Data,0,realValue,0,0);
		intfSCPI_SetOperReg(p->pInterface, _INTF_REG_EVEN, 0);
		//}
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End

}

void idSTATusOPERationNTRansition(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		UWORD realValue;
		realValue = intfSCPI_GetOperReg(p->pInterface,_INTF_REG_NTR);
		ExportProcess(Integer_Data,0,realValue,0,0);
	} else {
		GW_TYPE value;
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			intfSCPI_SetOperReg(p->pInterface,_INTF_REG_NTR, value.si);
		} else {
			scpi_SetCommandError( p, _ERR_113_Undefined_header);
		}
	}
// Code End

}

void idSTATusOPERationPTRansition(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		UWORD realValue;
		realValue = intfSCPI_GetOperReg(p->pInterface,_INTF_REG_PTR);
		ExportProcess(Integer_Data,0,realValue,0,0);
	} else {
		GW_TYPE value;
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			intfSCPI_SetOperReg(p->pInterface,_INTF_REG_PTR, value.si);
		} else {
			scpi_SetCommandError( p, _ERR_113_Undefined_header);
		}
	}
// Code End

}

void idSTATusCSUMmaryCONDition(STR_PARSER * p)
{
	UWORD realValue;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		realValue = intfSCPI_GetCsumReg(p->pInterface,_INTF_REG_COND);
		ExportProcess(Integer_Data,0,realValue,0,0);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End

}

void idSTATusCSUMmaryENABle(STR_PARSER * p)
{

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		UWORD realValue;
		realValue = intfSCPI_GetCsumReg(p->pInterface,_INTF_REG_ENAB);
		ExportProcess(Integer_Data,0,realValue,0,0);
	} else {
		GW_TYPE value;
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			intfSCPI_SetCsumReg(p->pInterface,_INTF_REG_ENAB, value.si);
		} else {
			scpi_SetCommandError( p, _ERR_113_Undefined_header);
		}
	}
// Code End

}

void idSTATusCSUMmaryEVENt(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		UWORD realValue;
		realValue = intfSCPI_GetCsumReg(p->pInterface,_INTF_REG_EVEN);
		ExportProcess(Integer_Data,0,realValue,0,0);
		intfSCPI_SetCsumReg(p->pInterface, _INTF_REG_EVEN, 0);
		//}
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End

}

void idSTATusCSUMmaryNTRansition(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		UWORD realValue;
		realValue = intfSCPI_GetCsumReg(p->pInterface,_INTF_REG_NTR);
		ExportProcess(Integer_Data,0,realValue,0,0);
	} else {
		GW_TYPE value;
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			intfSCPI_SetCsumReg(p->pInterface,_INTF_REG_NTR, value.si);
		} else {
			scpi_SetCommandError( p, _ERR_113_Undefined_header);
		}
	}
// Code End

}

void idSTATusCSUMmaryPTRansition(STR_PARSER * p)
{
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		UWORD realValue;
		realValue = intfSCPI_GetCsumReg(p->pInterface,_INTF_REG_PTR);
		ExportProcess(Integer_Data,0,realValue,0,0);
	} else {
		GW_TYPE value;
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			intfSCPI_SetCsumReg(p->pInterface,_INTF_REG_PTR, value.si);
		} else {
			scpi_SetCommandError( p, _ERR_113_Undefined_header);
		}
	}
// Code End

}

void idSYNCWAIT(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UBYTE SettingBool;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	p3k_send_tx_list tx_data;

// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(FPGA05_Writ_flag == Set_Bit_OFF)
			ExportProcess(String_Data,0,0,"Off",0);
		else if(FPGA05_Writ_flag == Set_Bit_ON)
			ExportProcess(String_Data,0,0,"On",0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			FPGA05_Writ_flag = SettingBool;
			//if(Data_tmp->CONF.Ext_Setting.MultilPara==1) {
			//	tx_data.ADDRH = Machine_Command;
			//	tx_data.ADDRL = Machine_SyncTrigg;
			//	SendTXData(&tx_data);
			//}
			SCPI_RemFastDelay = 1;
		}
	}

// Code End
}

void idSYNCDEFaultRECall(STR_PARSER * p)
{
	p3k_send_tx_list tx_data;
	UBYTE booster,parallel,i,cnt_1;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		System_Ready = 0;
		if(UTILITY.LOAD_CTL) {
			UTILITY.LOAD_CTL = Switch_OFF;
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Load_OnOff;
			SendTXData(&tx_data);
			PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
		}
		LoadDefaultProc(Sync_Recall_Default);
		RestoreRealChan();
		Control_LCDBRCon();
		M_num = P_CC;
		FPGA_Init();
		System_Ready = 1;
		OSTimeDly(10);
		MenuRedrawFlag |= MENU_CHANGE;
		ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
		SysRedrawFlag  |= SYS_CHANGE;
		ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
		SCPI_RemFastDelay = 1;
	}
// Code End
}


void idSYNCCHEaksum(STR_PARSER * p)
{
	UWORD CRC=0;
// Code Begin
	unsigned char k[20];
	if(scpi_IsQueryCommand(p)) {
		CRC = Cal_crc((unsigned char *)&P3k_Chan_Data, 1036 );
		CRC += UTILITY.LOAD_CTL;
		//CRC = Cal_crc( k, 10 );
		ExportProcess(Integer_Data,0,CRC,0,0);
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
// Code End
}

void idCV(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE SettingBool;
	UBYTE Command_Done=0,i;
	p3k_send_tx_list tx_data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		ExportProcess(Integer_Data,0,(long)Data_tmp->CONF.CV_Func_En,0,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			Data_tmp->CONF.CV_Func_En = SettingBool;
			Disp_tmp->CONF.CV_Func_En = SettingBool;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag|=MENU1_CHANGE;
				DataRedrawFlag |=PARA_CHANGE;
				Draw_Set_parameter();				
			}
			MenuDecoderAddr(&tx_data);
			SendTXData(&tx_data);
		}
	}
// Code End
}

void idSYSTemKLOCk(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE SettingBool;
	UBYTE Command_Done=0,i;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		ExportProcess(Integer_Data,0,UTILITY.LOCK_KEY,0,0);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}

		if(Command_Done) {
			if(SettingBool) Parserfalg |= 0x01;
			else			Parserfalg &= (~0x01);

			UTILITY.LOCK_KEY = (Parserfalg&0x01);
			SysRedrawFlag |= LOCK_UPDATA;
			if( (DispMode==DispMode_SET_PARAMETERS)&&(M_num<=P_CP) ) {
				DispMode = DispMode_BROWSE_ITEMS;
				DataRedrawFlag|= PARA_CHANGE;
			}
		}
	}
// Code End
}

void idSOURceCURRentPROTectionLEVelOVER(STR_PARSER * p)
{
// Code Begin
	SCPI_Company = SCPI_KIKUSUI;
	idCONFigureOCP(p);
// Code End
}

void idSOURceCURRentPROTectionACTion(STR_PARSER * p)
{
// Code Begin
	SCPI_Company = SCPI_KIKUSUI;
	idCONFigureOCP(p);
// Code End
}

void idSOURceCURRentRANGe(STR_PARSER * p)
{
	idMODECRANge(p);
}

void idSOURceCURRentLEVelIMMediateAMPLitude(STR_PARSER * p)
{
// Code Begin
	idCURRentVA(p);
// Code End
}

void idSOURceCURRentSLEW(STR_PARSER * p)
{
// Code Begin
	idCURRentSRATe(p);
// Code End
}

void idSOURcePOWerPROTectionLEVelOVER(STR_PARSER * p)
{
// Code Begin
	SCPI_Company = SCPI_KIKUSUI;
	idCONFigureOPP(p);
// Code End
}

void idSOURcePOWerPROTectionACTion(STR_PARSER * p)
{
// Code Begin
	SCPI_Company = SCPI_KIKUSUI;
	idCONFigureOPP(p);
// Code End
}

void idSOURcePOWerRANGe(STR_PARSER * p)
{
	idMODECRANge(p);
}

void idSOURcePOWerLEVelIMMediateAMPLitude(STR_PARSER * p)
{
// Code Begin
	idPOWerVA(p);
// Code End
}

void idSOURceCONDuctanceLEVelIMMediateAMPLitude(STR_PARSER * p)
{
// Code Begin
	idRESistanceVA(p);
// Code End
}

void idSOURceCONDuctanceRANGe(STR_PARSER * p)
{
	idMODECRANge(p);

}

void idSOURceVOLTagePROTectionLEVelUNDer(STR_PARSER * p)
{
// Code Begin
	SCPI_Company = SCPI_KIKUSUI;
	idCONFigureUVP(p);
// Code End
}

void idSOURceVOLTageLEVelIMMediateAMPLitude(STR_PARSER * p)
{
	idMODEVRANge(p);
}

void idSOURceVOLTagePROTectionSTATe(STR_PARSER * p)
{
	SCPI_Company = SCPI_KIKUSUI;
	idCONFigureOVP(p);
}

void idSOURceVOLTageRANGe(STR_PARSER * p)
{
	idMODEVRANge(p);
}

void idSOURceFUNCtionSSTart(STR_PARSER * p)
{
// Code Begin
	idCONFigureSSTart(p);
// Code End
}

void idSOURceFUNCtionRESPonse(STR_PARSER * p)
{
// Code Begin
	idCONFigureRESPonse(p);
// Code End
}

void idSOURceFUNCtionCTIMe(STR_PARSER * p)
{
// Code Begin
	idCONFigureCNTime(p);
// Code End
}

void idSOURceFUNCtionMODE(STR_PARSER * p)
{
// Code Begin
	idMODE(p);
// Code End
}

void idSOURcePULSeSTATe(STR_PARSER * p)
{
// Code Begin
	SCPI_Company = SCPI_KIKUSUI;
	idMODEDYNamic(p);
// Code End
}

void idSOURcePULSeFREQuency(STR_PARSER * p)
{
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
		
	switch(Data_tmp->CURRMODE) {
	case CC_MODE:
		idCURRentFREQuency(p);
		break;
	case CR_MODE:
		idRESistanceFREQuency(p);
		break;
	case CP_MODE:
		idPOWerFREQuency(p);
		break;
	default:
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}

}

void idSOURcePULSeDCYCle(STR_PARSER * p)
{
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data; 	
	switch(Data_tmp->CURRMODE) {
	case CC_MODE:
		idCURRentDUTY(p);
		break;
	case CR_MODE:
		idRESistanceDUTY(p);
		break;
	case CP_MODE:
		idPOWerDUTY(p);
		break;
	default:
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}

}

void idSOURcePULSePERiod(STR_PARSER * p)
{
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data; 
	SCPI_Company = SCPI_KIKUSUI;
	
	switch(Data_tmp->CURRMODE) {
	case CC_MODE:
		idCURRentFREQuency(p);
		break;
	case CR_MODE:
		idRESistanceFREQuency(p);
		break;
	case CP_MODE:
		idPOWerFREQuency(p);
		break;
	default:
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}

}


void idSOURcePULSeLEVe1VALueCONDuctance(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	ULONG cnt1,value_temp;
	double OHM_value,MHO_value;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;

	p3k_send_tx_list tx_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

	ResolutionTemp=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Resolution;
	if(scpi_GetNumericSuffix(p,1)==1) //L1
		MHO_value=(double)(Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL1*ResolutionTemp)*Para_s;
	else
		MHO_value=(double)(Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL2*ResolutionTemp)*Para_s;
	OHM_value=(double)(1/MHO_value*1000);

	//These max and min is MHO as base unit
	Max=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Max);
	Min=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Min);
// Code Begin
	if (Data_tmp->CONF.Dyna_Level) { //if percent mode, return
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	BYTE Precision;
	Precision = (ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].precision;
	if(scpi_IsQueryCommand(p)) {
		if (copy_SCPI_Company == SCPI_GW) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					MHO_value=Min*ResolutionTemp*Para_s;
					ExportProcess(Float_Data,MHO_value,0,0,Precision);
				} else if (value.si==SCPI_MAX) {
					MHO_value=Max*ResolutionTemp*Para_s;
					ExportProcess(Float_Data,MHO_value,0,0,Precision);
				}
			} else {
				ExportProcess(Float_Data,MHO_value,0,0,Precision);
			}
		} else if(copy_SCPI_Company == SCPI_KIKUSUI) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					ExportProcess(Float_Data,((double)(Min*ResolutionTemp*Para_s)),0,0,0);
				} else if (value.si==SCPI_MAX) {
					ExportProcess(Float_Data,((double)(Max*ResolutionTemp*Para_s)),0,0,0);
				}
			} else {
				ExportProcess(Float_Data,MHO_value,0,0,5);
			}
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			value_temp =(ULONG)(SCPI_InputToStep(value.d,ResolutionTemp)/Para_s);
			if((value_temp<=Max) && (value_temp>=Min)) {
				SettingCount=(UWORD)value_temp;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min;
			} else if (value.si==SCPI_MAX) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max;
			}
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Disp_tmp->CR.DYNA[Disp_tmp->IRange].LEVEL2 = SettingCount;
			Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL2 = SettingCount;
			if(Data_tmp->CURRMODE!=CR_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CR_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CR.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CR.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}
				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
			}
			if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH=0x02;
			tx_data.ADDRL=0x10;
			SendTXData(&tx_data);
			if((!Data_tmp->UTILITY.B_ONOFF)&&(Data_tmp->CR.ABSELECT)) {
				Disp_tmp->CR.ABSELECT = Data_tmp->CR.ABSELECT = SCPI_AValue;

				tx_data.ADDRH = 0x02;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				if(!SCPI_Freeze_menu)
					ChanRedrawFlag|= CHAN_STATUS;
			}

			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
	
// Code End

}

void idSOURcePULSeLEVe1PERCentageCONDuctance(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,Mode_Change=0,Range_Change=0,Load_On_Status=0;
	ULONG cnt1,value_temp;
	double OHM_value,MHO_value;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;

	p3k_send_tx_list tx_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	unsigned char copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);

	ResolutionTemp=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Resolution;
	if(scpi_GetNumericSuffix(p,1)==1) //L1
		MHO_value=(double)(Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL1*ResolutionTemp)*Para_s;
	else
		MHO_value=(double)(Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL2*ResolutionTemp)*Para_s;
	OHM_value=(double)(1/MHO_value*1000);

	//These max and min is MHO as base unit
	Max=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Max);
	Min=(double)((ptrMODEL_TYPE->CR)[Data_tmp->IRange*10+4].Min);
// Code Begin
	if (Data_tmp->CONF.Dyna_Level) { //if percent mode, return
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	BYTE Precision;
	Precision = (ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].precision;
	if(scpi_IsQueryCommand(p)) {
		if (copy_SCPI_Company == SCPI_GW) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					MHO_value=Min*ResolutionTemp*Para_s;
					ExportProcess(Float_Data,MHO_value,0,0,Precision);
				} else if (value.si==SCPI_MAX) {
					MHO_value=Max*ResolutionTemp*Para_s;
					ExportProcess(Float_Data,MHO_value,0,0,Precision);
				}
			} else {
				ExportProcess(Float_Data,MHO_value,0,0,Precision);
			}
		} else if(copy_SCPI_Company == SCPI_KIKUSUI) {
			if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
				if(value.si==SCPI_MIN) {
					ExportProcess(Float_Data,((double)(Min*ResolutionTemp*Para_s)),0,0,0);
				} else if (value.si==SCPI_MAX) {
					ExportProcess(Float_Data,((double)(Max*ResolutionTemp*Para_s)),0,0,0);
				}
			} else {
				ExportProcess(Float_Data,MHO_value,0,0,5);
			}
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			value_temp =(ULONG)(SCPI_InputToStep(value.d,ResolutionTemp)/Para_s);
			if((value_temp<=Max) && (value_temp>=Min)) {
				SettingCount=(UWORD)value_temp;
				Command_Done = 1;
			} else {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Min;
			} else if (value.si==SCPI_MAX) {
				SettingCount=(ptrMODEL_TYPE->CR)[Data_tmp->IRange*10].Max;
			}
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			Disp_tmp->CR.DYNA[Disp_tmp->IRange].LEVEL2 = SettingCount;
			Data_tmp->CR.DYNA[Data_tmp->IRange].LEVEL2 = SettingCount;
			if(Data_tmp->CURRMODE!=CR_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CR_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CR.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CR.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}
				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
			}
			if((M_num==P_CR)&&(Disp_tmp->CR.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH=0x02;
			tx_data.ADDRL=0x10;
			SendTXData(&tx_data);
			if((!Data_tmp->UTILITY.B_ONOFF)&&(Data_tmp->CR.ABSELECT)) {
				Disp_tmp->CR.ABSELECT = Data_tmp->CR.ABSELECT = SCPI_AValue;

				tx_data.ADDRH = 0x02;
				tx_data.ADDRL = 0x00;
				SendTXData(&tx_data);
				if(!SCPI_Freeze_menu)
					ChanRedrawFlag|= CHAN_STATUS;
			}

			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
	
// Code End

}

void idSOURcePULSeLEVe1VALueCURRent(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[30];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	UBYTE Mode_Change=0,Range_Change=0,Load_On_Status=0;

	ResolutionTemp=((ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Resolution);
	Precision = (ptrMODEL_TYPE->CC)[4+Data_tmp->IRange*10].precision;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
// Code Begin
	if(P3k_Chan_Data.CONF.Dyna_Level) { //If precent mode, return
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Min*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Min,0,0,Precision);
			} else if (value.si==SCPI_MAX) {
				Max=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Max*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Max,0,0,Precision);
			}
		} else {
			SettingCount = Data_tmp->CC.DYNA[Data_tmp->IRange].LEVEL1;;
			Real_Value = (double)(SettingCount * ResolutionTemp )*Para_s;
			ExportProcess(Float_Data,Real_Value,0,0,Precision);
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			Max=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Max*ResolutionTemp;
			Min=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Min*ResolutionTemp;;
			if((Real_Value > Max)||(Real_Value < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Max : (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Min;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if(Data_tmp->CURRMODE!=CC_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CC_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CC.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CC.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}
				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
				SoftStartDoubleCheck();
			}

			Data_tmp->CC.DYNA[Data_tmp->IRange].LEVEL1 = SettingCount;
			Disp_tmp->CC.DYNA[Data_tmp->IRange].LEVEL1 = SettingCount;
			if((M_num==P_CC)&&(Disp_tmp->CC.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}
			tx_data.ADDRH=0x01;
			tx_data.ADDRL=0x40;
			SendTXData(&tx_data);
			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
// Code End

}

void idSOURcePULSeLEVe1PERCentageCURRent(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0, Precision;
	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	char Data_Buffer[30];

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	p3k_send_tx_list tx_data;
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	UBYTE Mode_Change=0,Range_Change=0,Load_On_Status=0;

	ResolutionTemp=((ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Resolution);
	Precision = (ptrMODEL_TYPE->CC)[4+Data_tmp->IRange*10].precision;
	Para_s = Get_Parallel_Parameter(Disp_tmp->IRange);
// Code Begin
	if(P3k_Chan_Data.CONF.Dyna_Level) { //If precent mode, return
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	
	if(scpi_IsQueryCommand(p)) {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if(value.si==SCPI_MIN) {
				Min=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Min*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Min,0,0,Precision);
			} else if (value.si==SCPI_MAX) {
				Max=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+4].Max*ResolutionTemp*Para_s;
				ExportProcess(Float_Data,Max,0,0,Precision);
			}
		} else {
			SettingCount = Data_tmp->CC.DYNA[Data_tmp->IRange].LEVEL2;;
			Real_Value = (double)(SettingCount * ResolutionTemp )*Para_s;
			ExportProcess(Float_Data,Real_Value,0,0,Precision);
		}
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d / Para_s;
			Max=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+5].Max*ResolutionTemp;
			Min=(double)(ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+5].Min*ResolutionTemp;;
			if((Real_Value > Max)||(Real_Value < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = SCPI_InputToStep(Real_Value , ResolutionTemp);
			Command_Done=1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingCount = (1 == value.si) ? (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+5].Max : (ptrMODEL_TYPE->CC)[Data_tmp->IRange*10+5].Min;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if(Data_tmp->CURRMODE!=CC_MODE) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CURRMODE=CC_MODE;
				Mode_Change=1;
			}
			if(Data_tmp->CC.STADYNA!=SCPI_Dynamic_Status) {
				if(UTILITY.LOAD_CTL) {
					UTILITY.LOAD_CTL=0x00;
					tx_data.ADDRH = 0x00;
					tx_data.ADDRL = 0x0B;
					SendTXData(&tx_data);
					Load_On_Status = 1;
				}
				Data_tmp->CC.STADYNA=SCPI_Dynamic_Status;
				Range_Change=1;
			}
			if(Mode_Change || Range_Change) {
				Check_KNOB_VAL_Count=Check_KNOB_VAL_change_time;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);

				RestoreRealChan();
				if(M_num != Disp_tmp->CURRMODE)
					M_num = Disp_tmp->CURRMODE;
				if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
					ChanRedrawFlag |= CHAN_NO + CHAN_STATUS + BG_CLEAR;
					DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
					MenuRedrawFlag|= MENU_CHANGE;
					if(DispMode>DispMode_BROWSE_ITEMS)
						DispMode = DispMode_BROWSE_ITEMS;
				}

				if(Mode_Change) {
					tx_data.ADDRH=0x00;
					tx_data.ADDRL=0x06;
					SendTXData(&tx_data);
				}
				if(Range_Change) {
					if(Data_tmp->CURRMODE==CC_MODE)
						tx_data.ADDRH=0x01;
					else if(Data_tmp->CURRMODE==CR_MODE)
						tx_data.ADDRH=0x02;
					else if(Data_tmp->CURRMODE==CV_MODE)
						tx_data.ADDRH=0x03;
					else if(Data_tmp->CURRMODE==CP_MODE)
						tx_data.ADDRH=0x04;
					tx_data.ADDRL=0x00;
					SendTXData(&tx_data);
				}
				SoftStartDoubleCheck();
			}


			Data_tmp->CC.DYNA[Data_tmp->IRange].LEVEL2 = SettingCount;
			Disp_tmp->CC.DYNA[Data_tmp->IRange].LEVEL2 = SettingCount;
			if((M_num==P_CC)&&(Disp_tmp->CC.STADYNA==SCPI_Dynamic_Status)&&(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				DataRedrawFlag |= PARA_CHANGE;
				if(DispMode>DispMode_BROWSE_ITEMS)
					DispMode = DispMode_BROWSE_ITEMS;
			}

			tx_data.ADDRH=0x01;
			tx_data.ADDRL=0x42;
			SendTXData(&tx_data);

			if(Load_On_Status) {
				UTILITY.LOAD_CTL=0x01;
				tx_data.ADDRH = 0x00;
				tx_data.ADDRL = 0x0B;
				SendTXData(&tx_data);
				Load_On_Status = 0;
			}
		}
	}
	
// Code End

}
extern const P3k_Timing_Str DEFAULT_PROG;
void idPROGramCLEar(STR_PARSER * p)
{
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	p3k_send_tx_list tx_data;
	UWORD i,j;

	P3k_NSeq_Data.NSeq_Number	= 0;
	P3k_NSeq_Data.NSeq_Start	= 0;

	for(i=0 ; i<10 ; i++) {
		for(j=0 ; j<28 ; j++)
			P3k_NSeq_Data.NSeq_Seq[i].NSeq_Memo[j]	= 0;

		P3k_NSeq_Data.NSeq_Seq[i].NSeq_Mode 		= CC_MODE;
		P3k_NSeq_Data.NSeq_Seq[i].NSeq_Range		= 0;		/* ILVL:IRange Low,VRange Low */
		P3k_NSeq_Data.NSeq_Seq[i].NSeq_Last_Load	= Switch_OFF;
		P3k_NSeq_Data.NSeq_Seq[i].NSeq_Chain		= 0;		/* OFF		*/
		P3k_NSeq_Data.NSeq_Seq[i].NSeq_Loop 		= 0;		/* Infinity */
		P3k_NSeq_Data.NSeq_Seq[i].NSeq_Last_Level	= 0;
		P3k_NSeq_Data.NSeq_Seq[i].NSeq_Max_Step 	= 0;
		P3k_NSeq_Data.NSeq_Seq[i].NSeq_Curr_Step	= 0;

		for(j=0 ; j<1024 ; j++) {
			P3k_NSeq_Data.NSeq_Step[i][j].NSeq_Value				= 0;
			P3k_NSeq_Data.NSeq_Step[i][j].NSeq_Time.Hour			= 0;
			P3k_NSeq_Data.NSeq_Step[i][j].NSeq_Time.Minute		= 0;
			P3k_NSeq_Data.NSeq_Step[i][j].NSeq_Time.Second		= 0;
			P3k_NSeq_Data.NSeq_Step[i][j].NSeq_Time.MilliSecond 	= 1;
			P3k_NSeq_Data.NSeq_Step[i][j].Load_Setting			= Switch_OFF;
			P3k_NSeq_Data.NSeq_Step[i][j].Ramp_Setting			= Switch_OFF;
			P3k_NSeq_Data.NSeq_Step[i][j].TrigOut_Setting		= Switch_OFF;
			P3k_NSeq_Data.NSeq_Step[i][j].Pause_Setting 			= Switch_OFF;
		}
	}
	/*Fast Seq*/
	for(i=0 ; i<10 ; i++)
		P3k_FSeq_Data.FSeq_Memo[i]	= 0;

	P3k_FSeq_Data.FSeq_Mode 		= CC_MODE;
	P3k_FSeq_Data.FSeq_Range		= 0;		/* ILVL:IRange Low,VRange Low */
	P3k_FSeq_Data.FSeq_Last_Load	= Switch_OFF;
	P3k_FSeq_Data.FSeq_TB_Range 	= 0;/*us*/
	P3k_FSeq_Data.FSeq_Loop 		= 0;
	P3k_FSeq_Data.FSeq_Last_Level	= 0;
	P3k_FSeq_Data.FSeq_Max_Step 	= 0;
#if Enable_FSEQ_RPT
	P3k_FSeq_Data.RPTStep = 0;
#endif
	P3k_FSeq_Data.FSeq_Curr_Step	= 0;
	P3k_FSeq_Data.FSeq_Time_Base	= 25;

	for(i=0 ; i<1024 ; i++) {
		P3k_FSeq_Data.FSeq_Step[i].FSeq_Value		= 0;
		P3k_FSeq_Data.FSeq_Step[i].TrigOut_Setting	= Switch_OFF;
	}
		
	DataRedrawFlag|=PARA_CHANGE+ BG_CLEAR;;
	SEQ_Save_Status=1;
	Soft_Key_Temp=0;
	MenuRedrawFlag |= MENU_CHANGE;
	ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
	SysRedrawFlag  |= SYS_CHANGE;
	ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
	
	P3k_NSeq_Data = P3k_NSeq_Disp;
	BackupNSeq();
	P3k_FSeq_Data = P3k_FSeq_Disp;
	BackupFSeq();
#if 0	
	BackupRunProg();
#endif
	SCPI_RemFastDelay = 1;

}

void idSOURcePRESetSTORe(STR_PARSER * p)
{
	idPRESetSAVE(p);

}

void idSOURcePRESetRECall(STR_PARSER * p)
{
	idPRESetRECall(p);

}
UBYTE ProgNum_KIKUSUI=0;
void idPROGramSELectedSTATe(STR_PARSER * p)
{
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {		
		if(ProgNum_KIKUSUI>10)
			idFSEQuenceSTATe(p);
		else if(ProgNum_KIKUSUI>0)
			idNSEQuenceSTATe(p);
		else
			scpi_SetCommandError( p, _ERR_221_Settings_conflict);
	}	
}

void idPROGramSELectedEXECuting(STR_PARSER * p)
{
	if(scpi_IsQueryCommand(p)) {
		if(ProgNum_KIKUSUI>10)
			idFSEQuenceSTATe(p);
		else if(ProgNum_KIKUSUI>0)
			idNSEQuenceSTATe(p);
		else
			scpi_SetCommandError( p, _ERR_221_Settings_conflict);	
	} else {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	}
}

void idPROGramSELectedNAME(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0;
	UWORD SettingCount;
	if(scpi_IsQueryCommand(p)) {		
		ExportProcess(Integer_Data,0,ProgNum_KIKUSUI,0,1);		
	} else {
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			if((value.d > 11)||(value.d < 1)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.d;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			ProgNum_KIKUSUI = SettingCount;
			if(SettingCount<=10){
				idNSEQuenceNUMBer(p);
			}
		}
	}

}

void idPROGramSELectedMEMO(STR_PARSER * p)
{
	if(ProgNum_KIKUSUI>10)
		idFSEQuenceMEMO(p);
	else if(ProgNum_KIKUSUI>0)
		idNSEQuenceMEMO(p);
	else
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);

}

void idPROGramSELectedMODE(STR_PARSER * p)
{
	SCPI_Company = SCPI_KIKUSUI;
	if(ProgNum_KIKUSUI>10)
		idFSEQuenceMODE(p);
	else if(ProgNum_KIKUSUI>0)
		idNSEQuenceMODE(p);
	else
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
	SCPI_Company = SCPI_GW;

}

void idPROGramSELectedVRANge(STR_PARSER * p)
{
	SCPI_Company = SCPI_KIKUSUI;
	if(ProgNum_KIKUSUI>10)
		idFSEQuenceRANGe(p);
	else if(ProgNum_KIKUSUI>0)
		idNSEQuenceRANGe(p);
	else
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
	SCPI_Company = SCPI_GW;

}

void idPROGramSELectedCRANge(STR_PARSER * p)
{
	SCPI_Company = SCPI_KIKUSUI;		
	if(ProgNum_KIKUSUI>10)
		idFSEQuenceRANGe(p);
	else if(ProgNum_KIKUSUI>0)
		idNSEQuenceRANGe(p);
	else
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
	SCPI_Company = SCPI_GW;

}

void idPROGramSELectedLOOP(STR_PARSER * p)
{
	if(ProgNum_KIKUSUI>10)
		idFSEQuenceLOOP(p);
	else if(ProgNum_KIKUSUI>0)
		idNSEQuenceLOOP(p);
	else
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);

}

void idPROGramSELectedLINPut(STR_PARSER * p)
{
	if(ProgNum_KIKUSUI>10)
		idFSEQuenceLLOad(p);
	else if(ProgNum_KIKUSUI>0)
		idNSEQuenceLLOad(p);
	else
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);

}

void idPROGramSELectedLOUTput(STR_PARSER * p)
{
	idPROGramSELectedLINPut(p);

}

void idPROGramSELectedLVALue(STR_PARSER * p)
{
	if(ProgNum_KIKUSUI>10)
			idFSEQuenceLAST(p);
		else if(ProgNum_KIKUSUI>0)
			idNSEQuenceLAST(p);
		else
			scpi_SetCommandError( p, _ERR_221_Settings_conflict);

}

void idPROGramSELectedCHAin(STR_PARSER * p)
{
	if((ProgNum_KIKUSUI)&&(ProgNum_KIKUSUI<10))
			idNSEQuenceCHAin(p);
		else
			scpi_SetCommandError( p, _ERR_221_Settings_conflict);

}

void idPROGramSELectedNSPeedSTEPINSert(STR_PARSER * p)
{
	GW_TYPE value;
	NSEQ_Edit_Str N;

	P3k_NSeq_Str *NSeq_Data_tmp = &P3k_NSeq_Data;
	P3k_NSeq_Str *NSeq_Disp_tmp = &P3k_NSeq_Disp;

	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	UBYTE Command_Done=1;
	char str[160],index;
	Para_s = Get_Parallel_Parameter(1);
	UWORD Total_Step,i;
	UBYTE j;


	int Hour,Minute,sec,msec;
	float temp1,temp2,temp3,temp4,temp5,temp6;
	//Seq No
	UBYTE *NSeq_Seq_No = &NSeq_Disp_tmp->NSeq_Number;
	//Step No
	UWORD *NSeq_Curr_Step = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Curr_Step;
	UWORD *NSeq_Max_Step = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Max_Step;
	//Step Struct
	NSeq_Data_Str *NSeq_Step = &NSeq_Disp_tmp->NSeq_Step[*NSeq_Seq_No][*NSeq_Curr_Step];
	//Value
	UWORD *NSeq_Value = &NSeq_Step->NSeq_Value;
	//Time
	P3k_Time_Str *NSeq_Time = &NSeq_Step->NSeq_Time;
	//Status of Load, Ramp, Trigger Out and Pause
	char ON_OFF[2][4]= {"OFF","ON"};

	//CC, CR Mode
	//double Max_Total,Min_Total;
	UWORD Max_tmp,Min_tmp;
	BYTE Precision_tmp;
	UBYTE *NSeq_Mode = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Mode;
	UBYTE V_Range = NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range/2;
	UBYTE I_Range = NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range%2;

	if(*NSeq_Mode==CC_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
	} else if (*NSeq_Mode==CR_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CR)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].precision;
	} else if (*NSeq_Mode==CV_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].Max;
		Min_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].Min;
		Precision_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].precision;
		Para_s =1;
	} else if (*NSeq_Mode==CP_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CP)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].precision;
	}
	Max = Max_tmp*ResolutionTemp;
	Min = Min_tmp*ResolutionTemp;

	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		if(p->pData->id==_idPROGramSELectedNSPeedSTEPEDIT) {
			sprintf(str,"Step:%d/%d, Value:%.*f, Time:%dH:%dM:%dS:%dmS, LOAD:%s, TRIG OUT:%s, RAMP:%s, PAUSE:%s "
			        ,*NSeq_Curr_Step,*NSeq_Max_Step
			        ,Precision_tmp ,(*NSeq_Value*ResolutionTemp*Para_s)
			        ,NSeq_Time->Hour,NSeq_Time->Minute,NSeq_Time->Second,NSeq_Time->MilliSecond
			        ,ON_OFF[NSeq_Step->Load_Setting],ON_OFF[NSeq_Step->Ramp_Setting]
			        ,ON_OFF[NSeq_Step->TrigOut_Setting],ON_OFF[NSeq_Step->Pause_Setting]
			       );
			ExportProcess(String_Data,0,0,str,0);
		} else {
			scpi_SetCommandError( p, _ERR_113_Undefined_header);
		}
	} else {


		//0. CurrStep
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if((value.si<SCPI_NSEQ_Step_Lower)||(value.si>SCPI_NSEQ_Step_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}

			else if(p->pData->id==_idPROGramSELectedNSPeedSTEPEDIT) {

			} else {
				j= NSeq_Disp_tmp->NSeq_Number;
				if(value.si>NSeq_Disp_tmp->NSeq_Seq[j].NSeq_Max_Step) {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				} else {
					NSeq_Disp_tmp->NSeq_Seq[j].NSeq_Max_Step++;
					for (i = NSeq_Disp_tmp->NSeq_Seq[j].NSeq_Max_Step; i > value.si; i--)
						NSeq_Disp_tmp->NSeq_Step[j][i]= NSeq_Disp_tmp->NSeq_Step[j][i-1];
				}
			}
			N.CurrStep = value.si;

		} else
			scpi_SetCommandError( p, _ERR_271_Macro_syntax_error);


		// 1.Value
		if(0 == scpi_GetFloatIntegerParameters( p, 1, (double*) &value.d)) {

			N.Value= value.d/Para_s;
			if((N.Value> Max)||(N.Value < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.ValueCount = SCPI_InputToStep(N.Value,ResolutionTemp);
		} else
			Command_Done =0;


		//2. Hour,Minute,sec,msec;
		if(0 == scpi_GetIntegerParameters( p, 2, (int*) &value.si)) {
			printf("id:888777%d\n",value.si);
			if((value.si<0)) {
				scpi_SetCommandError( p, _ERR_315_Configuration_memory_lost);
				return;
			}

			else
				temp1=(float)value.si/3600000;
			Hour= temp1;
			temp2=temp1-Hour;
			temp3=temp2*3600;
			temp4=temp3/60;
			Minute=temp4;
			temp5=temp4-Minute;
			temp6=temp5*60;
			sec=temp6;
			msec=(temp6-sec)*1000;

			if((Hour<SCPI_NSEQ_Time_Hour_mS_Lower)||(Hour>SCPI_NSEQ_Time_Hour_mS_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.T_hour = Hour;
			if((Minute<SCPI_NSEQ_Time_Min_Sec_Lower)||(Minute>SCPI_NSEQ_Time_Min_Sec_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.T_minute= Minute;
			if((sec<SCPI_NSEQ_Time_Min_Sec_Lower)||(sec>SCPI_NSEQ_Time_Min_Sec_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.T_sec= sec;
			if((msec<SCPI_NSEQ_Time_Hour_mS_Lower)||(msec>SCPI_NSEQ_Time_Hour_mS_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.T_millsec = msec;
		} else
			Command_Done =0;
		//3.	load
		if(0 == scpi_GetIntegerParameters( p, 3, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.Load= (1 == value.si) ? 1 : 0;
		} else if(0 == scpi_GetKeywordParameters( p, 3, (int*) &value.si)) {
			N.Load = (1 == value.si) ? 1 : 0;
		} else
			Command_Done =0;
		//4. ramp
		if(0 == scpi_GetIntegerParameters( p, 4, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.Ramp= (1 == value.si) ? 1 : 0;
		} else if(0 == scpi_GetKeywordParameters( p, 4, (int*) &value.si)) {
			N.Ramp= (1 == value.si) ? 1 : 0;
		} else
			Command_Done =0;
		//5. trig out
		if(0 == scpi_GetIntegerParameters( p, 5, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.TrigOut= (1 == value.si) ? 1 : 0;
		} else if(0 == scpi_GetKeywordParameters( p, 5, (int*) &value.si)) {
			N.TrigOut= (1 == value.si) ? 1 : 0;
		} else
			Command_Done =0;

		//6. pause
		if(0 == scpi_GetIntegerParameters( p, 6, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.Pause= (1 == value.si) ? 1 : 0;
		} else if(0 == scpi_GetKeywordParameters( p, 6, (int*) &value.si)) {
			N.Pause= (1 == value.si) ? 1 : 0;
		} else
			Command_Done =0;

		if(Command_Done==0) {
			scpi_SetCommandError( p, _ERR_220_Parameter_error);
			return;
		}

		if(Command_Done) {
			//max_step
			*NSeq_Max_Step = *NSeq_Max_Step;
			//current_step
			*NSeq_Curr_Step=N.CurrStep;
			NSeq_Step = &NSeq_Disp_tmp->NSeq_Step[*NSeq_Seq_No][*NSeq_Curr_Step];
			//Value
			NSeq_Step->NSeq_Value = N.ValueCount;
			//Time --- Hour
			NSeq_Step->NSeq_Time.Hour=N.T_hour;
			//Time --- Minute
			NSeq_Step->NSeq_Time.Minute=N.T_minute;
			//Time --- Second
			NSeq_Step->NSeq_Time.Second=N.T_sec;
			//Time --- Milli Second
			NSeq_Step->NSeq_Time.MilliSecond=N.T_millsec;
			//Load
			NSeq_Step->Load_Setting=N.Load;
			//Ramp
			NSeq_Step->Ramp_Setting=N.Ramp;
			//Trigger Out
			NSeq_Step->TrigOut_Setting=N.TrigOut;
			//Pause
			NSeq_Step->Pause_Setting=N.Pause;

			asm("nop;"); //be safe
			NSeq_Data_tmp=NSeq_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if(/*(M_num==P_Seq_Normal)&&*/(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				Draw_Set_parameter();					
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_NSeq_Data(Backup);
		}
	}
// Code End
}


void idPROGramSELectedNSPeedSTEPADD(STR_PARSER * p)
{
	GW_TYPE value;
	NSEQ_Edit_Str N;

	P3k_NSeq_Str *NSeq_Data_tmp = &P3k_NSeq_Data;
	P3k_NSeq_Str *NSeq_Disp_tmp = &P3k_NSeq_Disp;

	UWORD SettingCount;
	double Max, Min, Real_Value, ResolutionTemp, Para_s;
	UBYTE Command_Done=1;
	char str[160],index;
	Para_s = Get_Parallel_Parameter(1);
	int Hour,Minute,sec,msec;
	float temp1,temp2,temp3,temp4,temp5,temp6;
	//Seq No
	UBYTE *NSeq_Seq_No = &NSeq_Disp_tmp->NSeq_Number;
	//Step No
	UWORD *NSeq_Curr_Step = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Curr_Step;
	UWORD *NSeq_Max_Step = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Max_Step;
	//Step Struct
	NSeq_Data_Str *NSeq_Step = &NSeq_Disp_tmp->NSeq_Step[*NSeq_Seq_No][*NSeq_Curr_Step];
	//Value
	UWORD *NSeq_Value = &NSeq_Step->NSeq_Value;
	//Time
	P3k_Time_Str *NSeq_Time = &NSeq_Step->NSeq_Time;
	//Status of Load, Ramp, Trigger Out and Pause
	char ON_OFF[2][4]= {"OFF","ON"};
	UBYTE j;
	UWORD Total_Step,i;
	//CC, CR Mode
	//double Max_Total,Min_Total;
	UWORD Max_tmp,Min_tmp;
	BYTE Precision_tmp;
	UBYTE *NSeq_Mode = &NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Mode;
	UBYTE V_Range = NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range/2;
	UBYTE I_Range = NSeq_Disp_tmp->NSeq_Seq[*NSeq_Seq_No].NSeq_Range%2;

	if(*NSeq_Mode==CC_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
	} else if (*NSeq_Mode==CR_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CR)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].precision;
	} else if (*NSeq_Mode==CV_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].Max;
		Min_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].Min;
		Precision_tmp = (ptrMODEL_TYPE->CV)[V_Range*3].precision;
		Para_s =1;
	} else if (*NSeq_Mode==CP_MODE) {
		ResolutionTemp = (ptrMODEL_TYPE->CP)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].Min;
		Precision_tmp = (ptrMODEL_TYPE->CP)[I_Range*10].precision;
	}
	Max = Max_tmp*ResolutionTemp;
	Min = Min_tmp*ResolutionTemp;

	// Code Begin
	if(scpi_IsQueryCommand(p)) {

		scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
	} else {


		//0. CurrStep
		j= NSeq_Disp_tmp->NSeq_Number;
		NSeq_Disp_tmp->NSeq_Seq[j].NSeq_Max_Step++;
		NSeq_Disp_tmp->NSeq_Seq[j].NSeq_Curr_Step++;

		// 1.Value
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			N.Value= value.d/Para_s;
			if((N.Value> Max)||(N.Value < Min)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.ValueCount = SCPI_InputToStep(N.Value,ResolutionTemp);
		} else
			Command_Done =0;
		//2. Hour,Minute,sec,msec;
		if(0 == scpi_GetIntegerParameters( p, 1, (int*)&value.si)) {
			if((value.si<0)||(value.si>3599999999)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}

			else
				temp1=(float)value.si/3600000;
			Hour= temp1;
			temp2=temp1-Hour;
			temp3=temp2*3600;
			temp4=temp3/60;
			Minute=temp4;
			temp5=temp4-Minute;
			temp6=temp5*60;
			sec=temp6;
			msec=(temp6-sec)*1000;

			if((Hour<SCPI_NSEQ_Time_Hour_mS_Lower)||(Hour>SCPI_NSEQ_Time_Hour_mS_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.T_hour = Hour;
			if((Minute<SCPI_NSEQ_Time_Min_Sec_Lower)||(Minute>SCPI_NSEQ_Time_Min_Sec_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.T_minute= Minute;
			if((sec<SCPI_NSEQ_Time_Min_Sec_Lower)||(sec>SCPI_NSEQ_Time_Min_Sec_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.T_sec= sec;
			if((msec<SCPI_NSEQ_Time_Hour_mS_Lower)||(msec>SCPI_NSEQ_Time_Hour_mS_Upper)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.T_millsec = msec;
		} else
			Command_Done =0;
		//3.	load
		if(0 == scpi_GetIntegerParameters( p, 2, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.Load= (1 == value.si) ? 1 : 0;
		} else if(0 == scpi_GetKeywordParameters( p, 2, (int*) &value.si)) {
			N.Load = (1 == value.si) ? 1 : 0;
		} else
			Command_Done =0;
		//4. ramp
		if(0 == scpi_GetIntegerParameters( p, 3, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.Ramp= (1 == value.si) ? 1 : 0;
		} else if(0 == scpi_GetKeywordParameters( p, 3, (int*) &value.si)) {
			N.Ramp= (1 == value.si) ? 1 : 0;
		} else
			Command_Done =0;
		//5. trig out
		if(0 == scpi_GetIntegerParameters( p, 4, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.TrigOut= (1 == value.si) ? 1 : 0;
		} else if(0 == scpi_GetKeywordParameters( p, 4, (int*) &value.si)) {
			N.TrigOut= (1 == value.si) ? 1 : 0;
		} else
			Command_Done =0;

		//6. pause
		if(0 == scpi_GetIntegerParameters( p, 5, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			N.Pause= (1 == value.si) ? 1 : 0;
		} else if(0 == scpi_GetKeywordParameters( p, 5, (int*) &value.si)) {
			N.Pause= (1 == value.si) ? 1 : 0;
		} else
			Command_Done =0;

		if(Command_Done==0) {
			scpi_SetCommandError( p, _ERR_220_Parameter_error);
			return;
		}
		if(Command_Done) {
			//max_step
			*NSeq_Max_Step = *NSeq_Max_Step;
			//current_step
			*NSeq_Curr_Step=*NSeq_Curr_Step;
			NSeq_Step = &NSeq_Disp_tmp->NSeq_Step[*NSeq_Seq_No][*NSeq_Curr_Step];
			//Value
			NSeq_Step->NSeq_Value = N.ValueCount;
			//Time --- Hour
			NSeq_Step->NSeq_Time.Hour=N.T_hour;
			//Time --- Minute
			NSeq_Step->NSeq_Time.Minute=N.T_minute;
			//Time --- Second
			NSeq_Step->NSeq_Time.Second=N.T_sec;
			//Time --- Milli Second
			NSeq_Step->NSeq_Time.MilliSecond=N.T_millsec;
			//Load
			NSeq_Step->Load_Setting=N.Load;
			//Ramp
			NSeq_Step->Ramp_Setting=N.Ramp;
			//Trigger Out
			NSeq_Step->TrigOut_Setting=N.TrigOut;
			//Pause
			NSeq_Step->Pause_Setting=N.Pause;

			asm("nop;"); //be safe
			NSeq_Data_tmp=NSeq_Disp_tmp;
			P3k_Chan_Data.Load_Type=P3k_Disp_Data.Load_Type;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if(/*(M_num==P_Seq_Normal)&&*/(!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				MenuRedrawFlag |= MENU_CHANGE - MENU3_CHANGE;
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				Draw_Set_parameter();				
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			SaveRecall_NSeq_Data(Backup);
		}
	}
	// Code End
}




void idPROGramSELectedNSPeedSTEPDELete(STR_PARSER * p)
{
	// Code Begin
	{
		UWORD i;
		UBYTE j;
		if(scpi_IsQueryCommand(p)) {
			scpi_SetCommandError( p, _ERR_113_Undefined_header);
		} else {
			j = P3k_NSeq_Disp.NSeq_Number;
			for (i = P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Curr_Step; i < P3k_NSeq_Disp.NSeq_Seq[j].NSeq_Max_Step; i++)
				P3k_NSeq_Disp.NSeq_Step[j][i] = P3k_NSeq_Disp.NSeq_Step[j][i + 1];
			P3k_NSeq_Disp.NSeq_Step[j][i+1] = P3k_NSeq_Disp.NSeq_Step[0][1024];
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
			Draw_Set_parameter();			
			MenuRedrawFlag |= MENU2_CHANGE + MENU3_CHANGE;
			//	return M_Success;

		}
	}
// Code End
}


void idPROGramSELectedNSPeedSTEPDELeteALL(STR_PARSER * p)
{
	idNSEQuenceDELetALL(p);
}

void idPROGramSELectedNSPeedSTEPCOUNt(STR_PARSER * p)
{
	SCPI_Company = SCPI_KIKUSUI;
	idNSEQuenceEDIT(p);
}

void idPROGramSELectedNSPeedSTEPEDIT(STR_PARSER * p)
{
	idPROGramSELectedNSPeedSTEPINSert(p);
}

void idPROGramSELectedFSPeedSTEPEND(STR_PARSER * p)
{
	idFSEQuenceRPTStep(p);
}

void idPROGramSELectedFSPeedSTEPEDITPOINt(STR_PARSER * p)
{
	SCPI_Company = SCPI_KIKUSUI;
	idFSEQuenceEDIT(p);
}

void idPROGramSELectedFSPeedTIME(STR_PARSER * p)
{
	idFSEQuenceTBASe(p);
}

void idPROGramSELectedFSPeedSTEPEDITLINear(STR_PARSER * p)
{
// Code Begin
	SCPI_Company = SCPI_KIKUSUI;
	idFSEQuenceEDITFILL(p);
// Code End
}

typedef struct	{
	UWORD StartStep;		/*	1~1000	       */
	UWORD EndStep;			/*	0~1000	       */
	//double SetValue[8];		/*	8      		*/
	UWORD SetCount[8];
} FSeqEditWave;

void idPROGramSELectedFSPeedSTEPEDITWAVE(STR_PARSER * p)
{
	GW_TYPE value;
	FSeqEditWave F;
	FSeq_Timing_Str *FSeq_Data_tmp = &P3k_FSeq_Data;
	FSeq_Timing_Str *FSeq_Disp_tmp = &P3k_FSeq_Disp;

	UBYTE Command_Done=1;
	double Resolution_tmp;
	double Setting;
	UWORD Max_tmp,Min_tmp;
	double Max_Total,Min_Total;
	BYTE dat,i;
	double Para_s;
	UBYTE I_Range	= FSeq_Disp_tmp->FSeq_Range%3;
	UBYTE FSeq_Mode = FSeq_Disp_tmp->FSeq_Mode;
	Para_s = Get_Parallel_Parameter(I_Range);
	UBYTE copy_SCPI_Company = SCPI_Company;
	SCPI_Company =0;

	if(FSeq_Mode==CC_MODE) {
		Resolution_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].Min;
		///Precision_tmp = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
	} else if (FSeq_Mode==CR_MODE) {
		Resolution_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Resolution;
		Max_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Max;
		Min_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].Min;
		///Precision_tmp = (ptrMODEL_TYPE->CR)[I_Range*10].precision;
	}
	Max_Total=(double)Max_tmp*Resolution_tmp;
	Min_Total=(double)Min_tmp*Resolution_tmp;
	
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {		
		//stert_Step : 0
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)){
			F.StartStep = value.d;
			if((F.StartStep<1)||(F.StartStep>1000)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
		} else
			Command_Done =0;

		for(i=0;i<8;i++){
			if(0 == scpi_GetFloatIntegerParameters( p, i+1, (double*) &value.d)){
					Setting = value.d/Para_s;
				if((Setting<Min_Total)||(Setting>Max_Total)) {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
				F.SetCount[i] = SCPI_InputToStep(Setting,Resolution_tmp);
			} else
				Command_Done =0;
		}
		if(Command_Done) {
			//current
			FSeq_Disp_tmp->FSeq_Curr_Step=F.StartStep-1;
			//max
			if(FSeq_Disp_tmp->FSeq_Max_Step<FSeq_Disp_tmp->FSeq_Curr_Step+7){
				FSeq_Disp_tmp->FSeq_Max_Step = FSeq_Disp_tmp->FSeq_Curr_Step+7;
				if(FSeq_Disp_tmp->FSeq_Max_Step>999)FSeq_Disp_tmp->FSeq_Max_Step=999;
			}else if(FSeq_Disp_tmp->FSeq_Max_Step>0xFF00){
				FSeq_Disp_tmp->FSeq_Max_Step = FSeq_Disp_tmp->FSeq_Curr_Step+7;;
			}			
			//value
			for(i=0;i<8;i++)
				FSeq_Disp_tmp->FSeq_Step[FSeq_Disp_tmp->FSeq_Curr_Step+i].FSeq_Value = F.SetCount[i];			

			asm("nop;"); //be safe
			*FSeq_Data_tmp=*FSeq_Disp_tmp;
			SEQ_Save_Status=1;
			Soft_Key_Temp=0;
			if((!PC_scriptrun)&&(!usbrun)&&(!SCPI_Freeze_menu)) {
				ChanRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR_FLAG;
				SysRedrawFlag |= PROG_UPDATA+ BG_CLEAR_FLAG;
			}
			if(DispMode>DispMode_BROWSE_ITEMS)
				DispMode = DispMode_BROWSE_ITEMS;
			///SaveRecall_FSeq_Data(Backup);	
		}
	}

}

void idSYSTemERRorNEXT(STR_PARSER * p)
{
// Code Begin
	idSYSTemERRor(p);

// Code End
}
void idINPutSTATeTRIGgered(STR_PARSER * p)
{
	GW_TYPE value;
	UBYTE Command_Done=0,SettingBool;
// Code Begin
	if(scpi_IsQueryCommand(p)) {
//		ExportProcess(Integer_Data,0,Trig.SW,0,0);
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si>=2) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			SettingBool = (1 == value.si) ? 1 : 0;
			Command_Done = 1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			if(Trig.TrigStatus == _TRIG_ACT_IDLE) {
				Trig.LoadOnOff = SettingBool;
			}
		}
	}
// Code End

}

void idOUTPutSTATeTRIGgered(STR_PARSER * p)
{
	idINPutSTATeTRIGgered(p);
}

void idSYSTemGTLocal(STR_PARSER * p)
{
	if(scpi_IsQueryCommand(p)) {
			scpi_SetCommandError( p, _ERR_113_Undefined_header);
		}else{
			REM_CONT = 0;
			SysRedrawFlag |= REM_LOC_UPDATA;
			if(DGIOCtrlFlag&REM_Mode_Fast)
				SetRemoteMode(0);
	}

}

void idSYSTemLLOut(STR_PARSER * p)
{

}

void idSYSTemRENable(STR_PARSER * p)
{
	idUTILityREMote(p);
}

void idSYSTemVERSion(STR_PARSER * p)
{
// Code Begin
	id_IDN(p);
// Code End
}

void idCALibratePASSword(STR_PARSER * p)
{
// Code Begin
	GW_TYPE value;
	UBYTE SettingCount;
	UBYTE Command_Done=0;
	p3k_send_tx_list tx_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(0 == scpi_GetIntegerParameters( p, 0, (int*) &value.si)) {
			if(value.si == 1000) {
				Command_Done=1;
			} else if(value.si==98) {
				Command_Done=2;
			} else {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done==1) {
			if(M_num!=P_CAL_MODE) {
				Auto_Load_Off();
				KeyInFlag &= ~SHIFT_KEY;
				PEL3000_LED_Control(LED_SHIFT, Switch_OFF);
				if(M_num!=P_UTIL_FILE)
					P_M_num = M_num;
				else
					P_M_num = P_FILE_CHAN;
				Cal_Init_Proc();
				ClrDispCnt(0,0,0,0,0,0);
				KeyinBuf[0] =KeyinBuf[1] = KeyinBuf[2] = KeyinBuf[3] = KeyinBuf[4] = KeyinBuf[5] = KeyinCT = 0x00;
				KeyInFlag&=(~DIGI_KEY_IN);
				Soft_Key_Temp=0;
				MenuRedrawFlag |= MENU_CHANGE;
				DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
				Draw_Set_parameter();				
				HelpRedrawFlag &= ~HELP_FUN_ON;
				ChanRedrawFlag = CHAN_CHANGE;
			}
		} else if(Command_Done==2) {
			if(M_num ==P_CAL_MODE) {
				P_M_num = CC_MODE;
				M_num = P_M_num;
				CAL_HI_LOW_SET_OK = 0;
				P3K_CALIBRATION_BAR.MODE	= P_CC;
				P3K_CALIBRATION_BAR.RANGE	= HIGH_RANGE;
				P3K_CALIBRATION_BAR.START	= 1;
				P3K_CALIBRATION_BAR.PSense	= 0;
				CtrlFlag1&=(~Cal_Wait_moment);
				ClearP3KMeasBG(Parameter_Bottom_Bolor);
				UTILITY.LOAD_CTL	= Switch_OFF;
				tx_data.ADDRH	= Machine_Command;
				tx_data.ADDRL	= Machine_Load_OnOff;
				SendTXData(&tx_data);
				PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
				FPGA_Init();
				Disp_tmp->CURRMODE = P_CC;
				ClrDispCnt(0x01, 0x00, 0x02, 0x00, 0x00, 0x00);
				DataRedrawFlag|= PARA_CHANGE + BG_CLEAR;
				Draw_Set_parameter();				
				MenuRedrawFlag |= MENU_CHANGE;
				ChanRedrawFlag |= CHAN_CHANGE ;
			}
		}
	}
// Code End
}

void idCALibrateMODE(STR_PARSER * p)
{
// Code Begin
	GW_TYPE value;
	UBYTE SettingCount;
	UBYTE Command_Done=0;
	char	str[20];
	if(M_num!=P_CAL_MODE) {
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		switch(P3K_CALIBRATION_BAR.MODE) {
		case SCPI_CC:
			ExportProcess(String_Data,0,0,"CC",0);
			break;
		case SCPI_CR:
			ExportProcess(String_Data,0,0,"CR",0);
			break;
		case SCPI_CV:
			ExportProcess(String_Data,0,0,"CV",0);
			break;
		case SCPI_CP:
			ExportProcess(String_Data,0,0,"CP",0);
			break;
		case CxCV_MODE:
			ExportProcess(String_Data,0,0,"CXCV",0);
			break;
		//case F_IMON_MODE:
		//	ExportProcess(String_Data,0,0,"FIMON",0);
		//	break;
		case R_IMON_MODE:
			ExportProcess(String_Data,0,0,"RIMON",0);
			break;
		case Ext_V_CC_MODE:
			ExportProcess(String_Data,0,0,"EXTV",0);
			break;
		case Ext_R_CC_MODE:
			ExportProcess(String_Data,0,0,"EXTR",0);
			break;
		default:
			break;
		}
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if((value.si<CC_MODE)||(value.si>Ext_R_CC_MODE)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			if(value.si==F_IMON_MODE) {
				scpi_SetCommandError( p, _ERR_100_Command_error);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			P3K_CALIBRATION_BAR.MODE = SettingCount;
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
			if((P3K_CALIBRATION_BAR.MODE==CV_MODE)||(P3K_CALIBRATION_BAR.MODE==CxCV_MODE)) {
			//	if(P3K_CALIBRATION_BAR.RANGE==Mid_RANGE) {
			//		P3K_CALIBRATION_BAR.RANGE=LOW_RANGE;
			//		MenuRedrawFlag |= MENU2_CHANGE;
			//	}
			}
			Rem_Load_Cal_Default();
			DispMode	= DispMode_SELECT_CH;
			DispCT	= 0;
			MenuRedrawFlag |= MENU1_CHANGE + MENU3_CHANGE + MENU4_CHANGE ;
			DataRedrawFlag |= PARA_CHANGE;
		}
	}
// Code End
}

void idCALibrateRANGe(STR_PARSER * p)
{
	// Code Begin
	GW_TYPE value;
	UBYTE SettingCount;
	UBYTE Command_Done=0;
	char	str[20];
	if(M_num!=P_CAL_MODE) {
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		switch(P3K_CALIBRATION_BAR.RANGE) {
		case LOW_RANGE:
			ExportProcess(String_Data,0,0,"LOW",0);
			break;
		case HIGH_RANGE:
			ExportProcess(String_Data,0,0,"HIGH",0);
			break;

		default:
			break;
		}
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if((value.si<0)||(value.si>1)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
			
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			P3K_CALIBRATION_BAR.RANGE = SettingCount;
			p3k_Cal_data.OffsetFlag = 0;
			if(CC_MODE==P3K_CALIBRATION_BAR.MODE)
				p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.CC_offseAdj[P3K_CALIBRATION_BAR.RANGE];
			else if(CR_MODE==P3K_CALIBRATION_BAR.MODE)
				p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.CR_offseAdj[P3K_CALIBRATION_BAR.RANGE];
			else if(CP_MODE==P3K_CALIBRATION_BAR.MODE)
				p3k_Cal_data.OffsetAdjCnt1 = p3k_Cal_data.CP_offseAdj[P3K_CALIBRATION_BAR.RANGE];

			MenuRedrawFlag |= MENU2_CHANGE+MENU4_CHANGE;
			Rem_Load_Cal_Default();
			DispMode	= DispMode_SELECT_CH;
			DispCT	= 0;
			DataRedrawFlag |= PARA_CHANGE;
		}

	}
// Code End
}

void idCALibrateLEVel(STR_PARSER * p)
{
// Code Begin
#define CalMode	P3K_CALIBRATION_BAR.MODE
	UBYTE OffsetModeFlag=0;
	GW_TYPE value;
	UBYTE SettingCount;
	UBYTE Command_Done=0;
	char	str[20];
	p3k_send_tx_list tx_data;
	if(M_num!=P_CAL_MODE) {
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if((CalMode==CC_MODE)||(CalMode==CR_MODE)||(CalMode==CP_MODE))OffsetModeFlag =1;
	if(scpi_IsQueryCommand(p)) {
		if(DispCT==1) { //low point
			ExportProcess(String_Data,0,0,"LP",0);
		} else { //high point or offset
			if((OffsetModeFlag)&&((p3k_Cal_data.OffsetFlag&0x02)==0)) {
				ExportProcess(String_Data,0,0,"OFFSET",0);
			} else {
				ExportProcess(String_Data,0,0,"HP",0);
			}
		}
	} else {
		if(0 == scpi_GetKeywordParameters( p, 0, (int*) &value.si)) {
			if((value.si<0)||(value.si>2)) {
				scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
				return;
			}
			SettingCount = value.si;
			Command_Done=1;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			//SettingCount

			if(DispMode!=DispMode_SELECT_CH)return;
			DataRedrawFlag |= PARA_CHANGE;
			if(SettingCount==0) {
				if(OffsetModeFlag) {
					p3k_Cal_data.OffsetFlag &= ~0x0002;
					DispCT = 0;
				} else {
					scpi_SetCommandError( p, _ERR_221_Settings_conflict);
					return;
				}
			} else if(SettingCount==1) { //HP
				DispCT = 0;
				p3k_Cal_data.OffsetFlag |= 0x0002;

			} else { //LP
				DispCT = 1;
				p3k_Cal_data.OffsetFlag |= 0x0002;
			}
		}
	}

// Code End
}

void idCALibrateRUN(STR_PARSER * p)
{
	// Code Begin
#define CalMode	P3K_CALIBRATION_BAR.MODE
	UBYTE OffsetModeFlag=0;
	GW_TYPE value;
	UBYTE SettingCount;
	UBYTE Command_Done=0;
	char	str[20];
	p3k_send_tx_list tx_data;
	if(M_num!=P_CAL_MODE) {
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if((CalMode==CC_MODE)||(CalMode==CR_MODE)||(CalMode==CP_MODE))OffsetModeFlag =1;
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		Command_Done=1;
		if(Command_Done) {
			if(DispMode!=DispMode_SELECT_CH)return;
			DispMode = DispMode_BROWSE_ITEMS;
			DataRedrawFlag |= PARA_CHANGE;
			if((OffsetModeFlag>0)&&(DispCT==0)&&((p3k_Cal_data.OffsetFlag&0x02)==0)) { //offset
				P3K_CALIBRATION_BAR.POINT = DispCT;
				P3K_CALIBRATION_BAR.Volt_Curr_Sel = Select_Volt;
				tx_data.ADDRH = Cal_FPGA_Command;
				tx_data.ADDRL = Cal_FPGA_Load_Cal_Default;
				SendTXData(&tx_data);
				tx_data.ADDRL = Cal_FPGA_OffsetAdjSetDA;
				SendTXData(&tx_data);
				tx_data.ADDRL = Cal_FPGA_OffsetAdjValue;
				SendTXData(&tx_data);
				tx_data.ADDRL = Cal_FPGA_Start;
				SendTXData(&tx_data);
			} else { //highpoint or lowpoint
				Rem_Sel_Cal_Point(DispCT);
			}
		}
	}

// Code End
}


void idCALibrateVALue(STR_PARSER * p)
{
#define CalMode	P3K_CALIBRATION_BAR.MODE
	UBYTE OffsetModeFlag=0;
	GW_TYPE value;
	double Real_Value;
	UWORD SettingCount;
	UBYTE Command_Done=0;
	char	str[20];
	p3k_send_tx_list tx_data;
	if(M_num!=P_CAL_MODE) {
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if((CalMode==CC_MODE)||(CalMode==CR_MODE)||(CalMode==CP_MODE))OffsetModeFlag =1;
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d)) {
			Real_Value = value.d ;
			Command_Done = 1;
		}  else {
			scpi_SetCommandError( p, _ERR_310_System_error);
			return;
		}
		if(Command_Done) {
			if(OffsetModeFlag&&((p3k_Cal_data.OffsetFlag&0x02)==0)) {
				if((Real_Value>Calibration_Adj_maxValue)||(Real_Value<Calibration_Adj_minValue)) {
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
				SettingCount = (UWORD)Real_Value;
				p3k_Cal_data.OffsetAdjCnt1 = SettingCount;
				p3k_Cal_data.OffsetFlag |= 0x01; //Adj has been
				tx_data.ADDRH = Cal_FPGA_Command;
				tx_data.ADDRL = Cal_FPGA_OffsetAdjValue;
				SendTXData(&tx_data);
			} else {
				if((CalMode==CR_MODE)||(CalMode==CP_MODE)||(CalMode==F_IMON_MODE)||(CalMode==R_IMON_MODE)) {
					scpi_SetCommandError( p, _ERR_221_Settings_conflict);
					return;
				}
				if( M_Out_Of_Range==Rem_Input_Cal_Data(Real_Value,DispCT)) {
					CalMessageFlag |= Show_Message;
					P3K_CALIBRATION_BAR.Volt_Curr_Sel = Select_Volt;
					DataRedrawFlag |= PARA_CHANGE;
					tx_data.ADDRH = Cal_FPGA_Command;
					tx_data.ADDRL = Cal_FPGA_Fail;
					SendTXData(&tx_data);
					scpi_SetCommandError( p, _ERR_222_Data_out_of_range);
					return;
				}
				if(CAL_HI_LOW_SET_OK==0x03) {
					P3K_CALIBRATION_BAR.START = 0x0;
					MenuRedrawFlag |= MENU4_CHANGE;
				}
			
				tx_data.ADDRH = Cal_FPGA_Command;
				tx_data.ADDRL = Cal_FPGA_End;
				SendTXData(&tx_data);
			}
			DataRedrawFlag |= PARA_CHANGE;
			DispMode = DispMode_SELECT_CH;
		}
	}
// Code End
}

void idCALibrateBIValue(STR_PARSER * p)
{
#define CalMode	P3K_CALIBRATION_BAR.MODE
	UBYTE OffsetModeFlag=0;
	GW_TYPE value;
	double Real_Value,Real_Value1;
	UWORD SettingCount;
	UBYTE Command_Done=1;
	char	str[20];
	p3k_send_tx_list tx_data;
	if(M_num!=P_CAL_MODE) {
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	// Code Begin
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if((CalMode==CC_MODE)||(CalMode==CR_MODE)||(CalMode==CP_MODE))OffsetModeFlag =1;
		//1:Voltang
		if(0 == scpi_GetFloatIntegerParameters( p, 0, (double*) &value.d))
			Real_Value = value.d ;
		else
			Command_Done =0;
		//2:current
		if(0 == scpi_GetFloatIntegerParameters( p, 1, (double*) &value.d))
			Real_Value1 = value.d ;

		else
			Command_Done =0;

		if(Command_Done) {
			if((P3K_CALIBRATION_BAR.MODE!=CR_MODE)&&(P3K_CALIBRATION_BAR.MODE!=CP_MODE)&&(P3K_CALIBRATION_BAR.MODE!=F_IMON_MODE)&&(P3K_CALIBRATION_BAR.MODE!=R_IMON_MODE)) {
				scpi_SetCommandError( p, _ERR_221_Settings_conflict);
				return;
			}
			if((OffsetModeFlag)&&((p3k_Cal_data.OffsetFlag&0x02)==0)) {
				scpi_SetCommandError( p, _ERR_221_Settings_conflict);
				return;
			}
			if( M_Out_Of_Range==Rem_Input_Cal_Data(Real_Value,DispCT)) {
				CalMessageFlag |= Show_Message;
				P3K_CALIBRATION_BAR.Volt_Curr_Sel = Select_Volt;
				DataRedrawFlag |= PARA_CHANGE;
				tx_data.ADDRH = Cal_FPGA_Command;
				tx_data.ADDRL = Cal_FPGA_Fail;
				SendTXData(&tx_data);
				return;
			}
			if(Select_Volt==P3K_CALIBRATION_BAR.Volt_Curr_Sel) {
				P3K_CALIBRATION_BAR.Volt_Curr_Sel = Select_Curr;
				DispMode = DispMode_BROWSE_ITEMS;
				DataRedrawFlag |= PARA_CHANGE;
			}
			if( M_Out_Of_Range==Rem_Input_Cal_Data(Real_Value1,DispCT)) {
				CalMessageFlag |= Show_Message;
				P3K_CALIBRATION_BAR.Volt_Curr_Sel = Select_Volt;
				DataRedrawFlag |= PARA_CHANGE;
				tx_data.ADDRH = Cal_FPGA_Command;
				tx_data.ADDRL = Cal_FPGA_Fail;
				SendTXData(&tx_data);
				return;
			}
			if(CAL_HI_LOW_SET_OK==0x03) {
				P3K_CALIBRATION_BAR.START = 0x0;
				MenuRedrawFlag |= MENU4_CHANGE;
			}
		
			tx_data.ADDRH = Cal_FPGA_Command;
			tx_data.ADDRL = Cal_FPGA_End;
			SendTXData(&tx_data);
			DispMode = DispMode_SELECT_CH;
			DataRedrawFlag |= PARA_CHANGE;
		} else {
			scpi_SetCommandError( p, _ERR_310_System_error);
		}

	}
	// Code End

}
void idCALibratePSENsor(STR_PARSER * p)
{
// Code Begin
	p3k_send_tx_list tx_data;
	if(M_num!=P_CAL_MODE) {
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {
		if(P3K_CALIBRATION_BAR.PSense) {
			Soft_Key_Temp = 0;
			CtrlFlag1 |= Cal_Wait_moment;
			MenuRedrawFlag |= MENU3_CHANGE;
			ShowCalMessage();
			Rem_CalPSense();
			if(P3K_CALIBRATION_BAR.RANGE!=IRange_Low) {	/*IF Cal Mode is CPH,Cal Mode need change CPL*/
				tx_data.ADDRH = Cal_FPGA_Command;
				tx_data.ADDRL = Cal_FPGA_Load_Cal_Default;
				SendTXData(&tx_data);
			}
		}
	}
// Code End
}

void idCALibrateSAVE(STR_PARSER * p)
{
// Code Begin
	if(M_num!=P_CAL_MODE) {
		scpi_SetCommandError( p, _ERR_221_Settings_conflict);
		return;
	}
	if(scpi_IsQueryCommand(p)) {
		scpi_SetCommandError( p, _ERR_113_Undefined_header);
	} else {

		CtrlFlag1	|= Cal_Wait_moment;
		Soft_Key_Temp = 0;
		DataRedrawFlag |= PARA_CHANGE;
		Rem_Save_Cal_Data();
	}
// Code End
}


const STR_COMM_FUNC CommandFun[] = {
 //---------ID no---------|-----Function-------|
	{_idCommandError,   idCommandError},
	{_id_CAL,	id_CAL},
	{_id_CLS,	id_CLS},
	{_id_ESE,	id_ESE},
	{_id_ESR,	id_ESR},
	{_id_IDN,	id_IDN},
	{_id_OPC,	id_OPC},
	{_id_RCL,	id_RCL},
	{_id_RST,	id_RST},
	{_id_SAV,	id_SAV},
	{_id_SRE,	id_SRE},
	{_id_STB,	id_STB},
	{_id_TRG,	id_TRG},
	{_id_TST,	id_TST},
	{_id_WAI,	id_WAI},
	{_idABORt,	idABORt},
	{_idSYSTemERRorNEXT,	idSYSTemERRorNEXT},
	{_idINPutSTATeTRIGgered,	idINPutSTATeTRIGgered},
	{_idOUTPutSTATeTRIGgered,	idOUTPutSTATeTRIGgered},
	{_idINITiateIMMediate,	idINITiateIMMediate},
	{_idINITiateCONTinuous,	idINITiateCONTinuous},
	{_idSOURceCURRentLEVelVATRIGgeredAMPLitude,	idSOURceCURRentLEVelVATRIGgeredAMPLitude},
	{_idRESistanceVATRIGgered,	idRESistanceVATRIGgered},
	{_idSOURceCONDuctanceVATRIGgeredAMPLitude,	idSOURceCONDuctanceVATRIGgeredAMPLitude},
	{_idTRIGgerDELayTIME,	idTRIGgerDELayTIME},
	{_idTRIGgerPULSeWIDTh,	idTRIGgerPULSeWIDTh},
	{_idINPutSTATeIMMediate,	idINPutSTATeIMMediate},
	{_idOUTPutSTATeIMMediate,	idOUTPutSTATeIMMediate},
	{_idINPutSHORtSTATe,	idINPutSHORtSTATe},
	{_idOUTPupSHORtSTATe,	idOUTPupSHORtSTATe},
	{_idINPutPROTectionCLEar,	idINPutPROTectionCLEar},
	{_idOUTPutPROTectionCLEar,	idOUTPutPROTectionCLEar},
	{_idINPutSTATeTIMerSTATe,	idINPutSTATeTIMerSTATe},
	{_idOUTPutSTATeTIMerSTATe,	idOUTPutSTATeTIMerSTATe},
	{_idINPutMODE,	idINPutMODE},
	{_idMEASureSCALarCURRentDC,	idMEASureSCALarCURRentDC},
	{_idMEASureSCALarVOLTageDC,	idMEASureSCALarVOLTageDC},
	{_idMEASureSCALarPOWerDC,	idMEASureSCALarPOWerDC},
	{_idMEASureSCALarETIMe,	idMEASureSCALarETIMe},
	{_idFETChCURRent,	idFETChCURRent},
	{_idFETChVOLTage,	idFETChVOLTage},
	{_idFETChPOWer,	idFETChPOWer},
	{_idCONFigureOCP,	idCONFigureOCP},
	{_idCONFigureOPP,	idCONFigureOPP},
	{_idCONFigureUVP,	idCONFigureUVP},
	{_idCONFigureUVPTIME,	idCONFigureUVPTIME},
	{_idCONFigureOVP,	idCONFigureOVP},
	{_idCONFigureSSTart,	idCONFigureSSTart},
	{_idCONFigureVON,	idCONFigureVON},
	{_idCONFigureVDELay,	idCONFigureVDELay},
	{_idCONFigureRESPonse,	idCONFigureRESPonse},
	{_idCONFigureCNTime,	idCONFigureCNTime},
	{_idCONFigureCOTime,	idCONFigureCOTime},
	{_idCONFigureCRUNit,	idCONFigureCRUNit},
	{_idCONFigureDYNamic,	idCONFigureDYNamic},
	{_idCONFigureMEMory,	idCONFigureMEMory},
	{_idCONFigureSHORtFUNCtion,	idCONFigureSHORtFUNCtion},
	{_idCONFigureSHORt,	idCONFigureSHORt},
	{_idCONFigureSHORtSAFety,	idCONFigureSHORtSAFety},
	{_idCONFigureGNGSPECtest,	idCONFigureGNGSPECtest},
	{_idCONFigureGNGDTIMe,	idCONFigureGNGDTIMe},
	{_idCONFigureGNGMODE,	idCONFigureGNGMODE},
	{_idCONFigureGNGPASS,	idCONFigureGNGPASS},
	{_idCONFigureGNGH,	idCONFigureGNGH},
	{_idCONFigureGNGL,	idCONFigureGNGL},
	{_idCONFigureGNGC,	idCONFigureGNGC},
	{_idCONFigureSTEPCCH,	idCONFigureSTEPCCH},
	{_idCONFigureSTEPCCL,	idCONFigureSTEPCCL},
	{_idCONFigureSTEPCC,	idCONFigureSTEPCC},
	{_idCONFigureSTEPCRH,	idCONFigureSTEPCRH},
	{_idCONFigureSTEPCRL,	idCONFigureSTEPCRL},
	{_idCONFigureSTEPCR,	idCONFigureSTEPCR},
	{_idCONFigureSTEPCVH,	idCONFigureSTEPCVH},
	{_idCONFigureSTEPCVL,	idCONFigureSTEPCVL},
	{_idCONFigureSTEPCV,	idCONFigureSTEPCV},
	{_idCONFigureSTEPCPH,	idCONFigureSTEPCPH},
	{_idCONFigureSTEPCPL,	idCONFigureSTEPCPL},
	{_idCONFigureSTEPCP,	idCONFigureSTEPCP},
	{_idCONFigureEXTernalCONTrol,	idCONFigureEXTernalCONTrol},
	{_idCONFigureEXTernalLOADonin,	idCONFigureEXTernalLOADonin},
	{_idCONFigureEXTernalSYNC,	idCONFigureEXTernalSYNC},
	{_idMODE,	idMODE},
	{_idMODECRANge,	idMODECRANge},
	{_idMODEVRANge,	idMODEVRANge},
	{_idMODEDYNamic,	idMODEDYNamic},
	{_idCURRentRECall,	idCURRentRECall},
	{_idCURRentVA,	idCURRentVA},
	{_idCURRentVB,	idCURRentVB},
	{_idCURRentSRATe,	idCURRentSRATe},
	{_idCURRentL12,	idCURRentL12},
	{_idCURRentSET,	idCURRentSET},
	{_idCURRentLEVel,	idCURRentLEVel},
	{_idCURRentRISE,	idCURRentRISE},
	{_idCURRentFALL,	idCURRentFALL},
	{_idCURRentT12,	idCURRentT12},
	{_idCURRentFREQuency,	idCURRentFREQuency},
	{_idCURRentDUTY,	idCURRentDUTY},
	{_idCURRentCVRESPonse,	idCURRentCVRESPonse},
	{_idRESistanceRECall,	idRESistanceRECall},
	{_idCONDuctanceRECall,	idCONDuctanceRECall},
	{_idCONDuctanceVA,	idCONDuctanceVA},
	{_idCONDuctanceVB,	idCONDuctanceVB},
	{_idRESistanceVA,	idRESistanceVA},
	{_idRESistanceVB,	idRESistanceVB},
	{_idRESistanceSRATe,	idRESistanceSRATe},
	{_idCONDuctanceL12,	idCONDuctanceL12},
	{_idCONDuctanceSET,	idCONDuctanceSET},
	{_idRESistanceL12,	idRESistanceL12},
	{_idRESistanceSET,	idRESistanceSET},
	{_idRESistanceLEVel,	idRESistanceLEVel},
	{_idRESistanceRISE,	idRESistanceRISE},
	{_idRESistanceFALL,	idRESistanceFALL},
	{_idRESistanceT12,	idRESistanceT12},
	{_idRESistanceFREQuency,	idRESistanceFREQuency},
	{_idRESistanceDUTY,	idRESistanceDUTY},
	{_idRESistanceCVRESPonse,	idRESistanceCVRESPonse},
	{_idVOLTageRECall,	idVOLTageRECall},
	{_idVOLTageVA,	idVOLTageVA},
	{_idVOLTageVB,	idVOLTageVB},
	{_idVOLTageRESPonse,	idVOLTageRESPonse},
	{_idPOWerRECall,	idPOWerRECall},
	{_idPOWerVA,	idPOWerVA},
	{_idPOWerVB,	idPOWerVB},
	{_idPOWerRESPonse,	idPOWerRESPonse},
	{_idPOWerCVRESPonse,	idPOWerCVRESPonse},
	{_idFUNCtionCOMPleteRINGTIME,	idFUNCtionCOMPleteRINGTIME},
	{_idPROGramSTATe,	idPROGramSTATe},
	{_idPROGram,	idPROGram},
	{_idPROGramRECallDEFault,	idPROGramRECallDEFault},
	{_idPROGramSTARt,	idPROGramSTARt},
	{_idPROGramSTEP,	idPROGramSTEP},
	{_idPROGramMEMory,	idPROGramMEMory},
	{_idPROGramRUN,	idPROGramRUN},
	{_idPROGramONTime,	idPROGramONTime},
	{_idPROGramOFFTime,	idPROGramOFFTime},
	{_idPROGramPFTime,	idPROGramPFTime},
	{_idPROGramSTIMe,	idPROGramSTIMe},
	{_idPROGramCHAinSTARt,	idPROGramCHAinSTARt},
	{_idPROGramCHAin,	idPROGramCHAin},
	{_idPROGramCHAinP2P,	idPROGramCHAinP2P},
	{_idPROGramCHAinRECallDEFault,	idPROGramCHAinRECallDEFault},
	{_idPROGramSAVE,	idPROGramSAVE},
	{_idSEQuenceCOMPleteRINGTIME,	idSEQuenceCOMPleteRINGTIME},
	{_idNSEQuenceTIMer,	idNSEQuenceTIMer},
	{_idNSEQuenceCOTime,	idNSEQuenceCOTime},
	{_idNSEQuenceSTATe,	idNSEQuenceSTATe},
	{_idNSEQuence,	idNSEQuence},
	{_idNSEQuenceSTARt,	idNSEQuenceSTARt},
	{_idNSEQuenceNUMBer,	idNSEQuenceNUMBer},
	{_idNSEQuenceMEMO,	idNSEQuenceMEMO},
	{_idNSEQuenceMODE,	idNSEQuenceMODE},
	{_idNSEQuenceRANGe,	idNSEQuenceRANGe},
	{_idNSEQuenceLOOP,	idNSEQuenceLOOP},
	{_idNSEQuenceLLOad,	idNSEQuenceLLOad},
	{_idNSEQuenceLAST,	idNSEQuenceLAST},
	{_idNSEQuenceCHAin,	idNSEQuenceCHAin},
	{_idNSEQuenceEDIT,	idNSEQuenceEDIT},
	{_idNSEQuenceEDITPOINt,	idNSEQuenceEDITPOINt},
	{_idNSEQuenceEDITEND,	idNSEQuenceEDITEND},
	{_idNSEQuenceDELetALL,	idNSEQuenceDELetALL},
	{_idNSEQuenceSAVE,	idNSEQuenceSAVE},
	{_idFSEQuenceSTATe,	idFSEQuenceSTATe},
	{_idFSEQuence,	idFSEQuence},
	{_idFSEQuenceMEMO,	idFSEQuenceMEMO},
	{_idFSEQuenceMODE,	idFSEQuenceMODE},
	{_idFSEQuenceRANGe,	idFSEQuenceRANGe},
	{_idFSEQuenceLOOP,	idFSEQuenceLOOP},
	{_idFSEQuenceTBASe,	idFSEQuenceTBASe},
	{_idFSEQuenceLLOad,	idFSEQuenceLLOad},
	{_idFSEQuenceLAST,	idFSEQuenceLAST},
	{_idFSEQuenceRPTStep,	idFSEQuenceRPTStep},
	{_idFSEQuenceEDIT,	idFSEQuenceEDIT},
	{_idFSEQuenceEDITPOINt,	idFSEQuenceEDITPOINt},
	{_idFSEQuenceEDITEND,	idFSEQuenceEDITEND},
	{_idFSEQuenceDELetALL,	idFSEQuenceDELetALL},
	{_idFSEQuenceEDITFILL,	idFSEQuenceEDITFILL},
	{_idFSEQuenceSAVE,	idFSEQuenceSAVE},
	{_idOCPSTATe,	idOCPSTATe},
	{_idOCPEDITCHANnel,	idOCPEDITCHANnel},
	{_idOCPCHANnelTEMP,	idOCPCHANnelTEMP},
	{_idOCPCHANnelRANGe,	idOCPCHANnelRANGe},
	{_idOCPCHANnelSTARt,	idOCPCHANnelSTARt},
	{_idOCPCHANnelEND,	idOCPCHANnelEND},
	{_idOCPCHANnelStepCurrWattent,	idOCPCHANnelStepCurrWattent},
	{_idOCPCHANnelLAST,	idOCPCHANnelLAST},
	{_idOCPCHANnelSTEPTIME,	idOCPCHANnelSTEPTIME},
	{_idOCPCHANnelDELay,	idOCPCHANnelDELay},
	{_idOCPCHANnelTRIGger,	idOCPCHANnelTRIGger},
	{_idOCPSAVE,	idOCPSAVE},
	{_idOCPRESult,	idOCPRESult},
	{_idOCPRUN,	idOCPRUN},
	{_idUTILitySYSTem,	idUTILitySYSTem},
	{_idUTILityREMote,	idUTILityREMote},
	{_idUTILityREMoteMODE,	idUTILityREMoteMODE},
	{_idUTILityLOAD,	idUTILityLOAD},
	{_idUTILityLOADMODE,	idUTILityLOADMODE},
	{_idUTILityLOADRANGe,	idUTILityLOADRANGe},
	{_idUTILityINTerface,	idUTILityINTerface},
	{_idUTILityTIME,	idUTILityTIME},
	{_idUTILityKNOB,	idUTILityKNOB},
	{_idUTILitySPEaker,	idUTILitySPEaker},
	{_idUTILityALARm,	idUTILityALARm},
	{_idUTILityUNReg,	idUTILityUNReg},
	{_idUTILityGNG,	idUTILityGNG},
	{_idUTILityCONTrast,	idUTILityCONTrast},
	{_idUTILityBRIGhtness,	idUTILityBRIGhtness},
	{_idUTILityLANGuage,	idUTILityLANGuage},
	{_idMEMorySAVE,	idMEMorySAVE},
	{_idMEMoryRECall,	idMEMoryRECall},
	{_idPRESetSAVE,	idPRESetSAVE},
	{_idPRESetRECall,	idPRESetRECall},
	{_idSETupSAVE,	idSETupSAVE},
	{_idSETupRECall,	idSETupRECall},
	{_idFACToryRECall,	idFACToryRECall},
	{_idUSERDEFaultSAVE,	idUSERDEFaultSAVE},
	{_idUSERDEFaultRECall,	idUSERDEFaultRECall},
	{_idSERialMASTer,	idSERialMASTer},
	{_idSTATusPRESet,	idSTATusPRESet},
	{_idSTATusQUEStionableCONDition,	idSTATusQUEStionableCONDition},
	{_idSTATusQUEStionableENABle,	idSTATusQUEStionableENABle},
	{_idSTATusQUEStionableEVENt,	idSTATusQUEStionableEVENt},
	{_idSTATusQUEStionableNTRansition,	idSTATusQUEStionableNTRansition},
	{_idSTATusQUEStionablePTRansition,	idSTATusQUEStionablePTRansition},
	{_idSTATusOPERationCONDition,	idSTATusOPERationCONDition},
	{_idSTATusOPERationENABle,	idSTATusOPERationENABle},
	{_idSTATusOPERationEVENt,	idSTATusOPERationEVENt},
	{_idSTATusOPERationNTRansition,	idSTATusOPERationNTRansition},
	{_idSTATusOPERationPTRansition,	idSTATusOPERationPTRansition},
	{_idSTATusCSUMmaryCONDition,	idSTATusCSUMmaryCONDition},
	{_idSTATusCSUMmaryENABle,	idSTATusCSUMmaryENABle},
	{_idSTATusCSUMmaryEVENt,	idSTATusCSUMmaryEVENt},
	{_idSTATusCSUMmaryNTRansition,	idSTATusCSUMmaryNTRansition},
	{_idSTATusCSUMmaryPTRansition,	idSTATusCSUMmaryPTRansition},
	{_idSYNCWAIT,	idSYNCWAIT},
	{_idSYNCDEFaultRECall,	idSYNCDEFaultRECall},
	{_idSYNCCHEaksum,	idSYNCCHEaksum},
	{_idCV,	idCV},
	{_idSYSTemKLOCk,	idSYSTemKLOCk},
	{_idSOURceCURRentPROTectionLEVelOVER,	idSOURceCURRentPROTectionLEVelOVER},
	{_idSOURceCURRentPROTectionACTion,	idSOURceCURRentPROTectionACTion},
	{_idSOURceCURRentRANGe,	idSOURceCURRentRANGe},
	{_idSOURceCURRentLEVelIMMediateAMPLitude,	idSOURceCURRentLEVelIMMediateAMPLitude},
	{_idSOURceCURRentSLEW,	idSOURceCURRentSLEW},
	{_idSOURcePOWerPROTectionLEVelOVER,	idSOURcePOWerPROTectionLEVelOVER},
	{_idSOURcePOWerPROTectionACTion,	idSOURcePOWerPROTectionACTion},
	{_idSOURcePOWerRANGe,	idSOURcePOWerRANGe},
	{_idSOURcePOWerLEVelIMMediateAMPLitude,	idSOURcePOWerLEVelIMMediateAMPLitude},
	{_idSOURceCONDuctanceLEVelIMMediateAMPLitude,	idSOURceCONDuctanceLEVelIMMediateAMPLitude},
	{_idSOURceCONDuctanceRANGe,	idSOURceCONDuctanceRANGe},
	{_idSOURceVOLTagePROTectionLEVelUNDer,	idSOURceVOLTagePROTectionLEVelUNDer},
	{_idSOURceVOLTageLEVelIMMediateAMPLitude,	idSOURceVOLTageLEVelIMMediateAMPLitude},
	{_idSOURceVOLTagePROTectionSTATe,	idSOURceVOLTagePROTectionSTATe},
	{_idSOURceVOLTageRANGe,	idSOURceVOLTageRANGe},
	{_idSOURceFUNCtionSSTart,	idSOURceFUNCtionSSTart},
	{_idSOURceFUNCtionRESPonse,	idSOURceFUNCtionRESPonse},
	{_idSOURceFUNCtionCTIMe,	idSOURceFUNCtionCTIMe},
	{_idSOURceFUNCtionMODE,	idSOURceFUNCtionMODE},
	{_idPROGramCLEar,	idPROGramCLEar},
	{_idPROGramSELectedSTATe,	idPROGramSELectedSTATe},
	{_idPROGramSELectedEXECuting,	idPROGramSELectedEXECuting},
	{_idPROGramSELectedNAME,	idPROGramSELectedNAME},
	{_idPROGramSELectedMEMO,	idPROGramSELectedMEMO},
	{_idPROGramSELectedMODE,	idPROGramSELectedMODE},
	{_idPROGramSELectedVRANge,	idPROGramSELectedVRANge},
	{_idPROGramSELectedCRANge,	idPROGramSELectedCRANge},
	{_idPROGramSELectedLOOP,	idPROGramSELectedLOOP},
	{_idPROGramSELectedLINPut,	idPROGramSELectedLINPut},
	{_idPROGramSELectedLOUTput,	idPROGramSELectedLOUTput},
	{_idPROGramSELectedLVALue,	idPROGramSELectedLVALue},
	{_idPROGramSELectedCHAin,	idPROGramSELectedCHAin},
	{_idPROGramSELectedNSPeedSTEPINSert,	idPROGramSELectedNSPeedSTEPINSert},
	{_idPROGramSELectedNSPeedSTEPADD,	idPROGramSELectedNSPeedSTEPADD},
	{_idPROGramSELectedNSPeedSTEPDELete,	idPROGramSELectedNSPeedSTEPDELete},
	{_idPROGramSELectedNSPeedSTEPDELeteALL,	idPROGramSELectedNSPeedSTEPDELeteALL},
	{_idPROGramSELectedNSPeedSTEPCOUNt,	idPROGramSELectedNSPeedSTEPCOUNt},
	{_idPROGramSELectedNSPeedSTEPEDIT,	idPROGramSELectedNSPeedSTEPEDIT},
	{_idPROGramSELectedFSPeedSTEPEND,	idPROGramSELectedFSPeedSTEPEND},
	{_idPROGramSELectedFSPeedSTEPEDITPOINt,	idPROGramSELectedFSPeedSTEPEDITPOINt},
	{_idPROGramSELectedFSPeedTIME,	idPROGramSELectedFSPeedTIME},
	{_idPROGramSELectedFSPeedSTEPEDITLINear,	idPROGramSELectedFSPeedSTEPEDITLINear},
	{_idPROGramSELectedFSPeedSTEPEDITWAVE,	idPROGramSELectedFSPeedSTEPEDITWAVE},
	{_idSYSTemGTLocal,	idSYSTemGTLocal},
	{_idSYSTemLLOut,	idSYSTemLLOut},
	{_idSYSTemRENable,	idSYSTemRENable},
	{_idSYSTemVERSion,	idSYSTemVERSion},
	{_idCALibratePASSword,	idCALibratePASSword},
	{_idCALibrateMODE,	idCALibrateMODE},
	{_idCALibrateRANGe,	idCALibrateRANGe},
	{_idCALibrateLEVel,	idCALibrateLEVel},
	{_idCALibrateVALue,	idCALibrateVALue},
	{_idCALibrateBIValue,	idCALibrateBIValue},
	{_idCALibrateRUN,	idCALibrateRUN},
	{_idCALibratePSENsor,	idCALibratePSENsor},
	{_idCALibrateSAVE,	idCALibrateSAVE},
	{_idCommandMax          ,0}
};




