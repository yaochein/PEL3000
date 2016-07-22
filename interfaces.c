#define INTERFACE_GLOBALS
//#include <app.h>
#include "includes.h"
#include "keydef.h"
#include "../parser/scpi/threadUART.h"

void (*WOutgoBuffer)(UBYTE *, UBYTE);
void (*WBOutgoBuffer)(UBYTE *, ULONG, UBYTE);
char (*ParserGetc)(unsigned char *err);
void InterfaceTask(void *para);

extern int UartCfgPort(void);
extern void dc_start_hw(void);
extern void ClrDispCnt(char mode, char ct, char sec, char ssc, char bct, char scl);
extern void Cursor1DisplayOn(void);
extern void Cursor2DisplayOn(void);
extern GELMASTER *gel;
extern void thread_Parser_Driver(char initial_falg);
extern void PEL3000_LED_Control( char mode, char onoff);
extern unsigned long sport1Read(unsigned long data);
extern void ResetGPIB(void);
extern void RunProgOff(void);
extern void SetRemoteMode(char Remote_Mode);
extern void FloatWindows_StringAt(const char GUI_FAR *s, int x, int y) ;
extern void Update_Panel(void);
extern void Float_Windows_Setting(int StartX, int StartY,int EndX, int EndY,GUI_COLOR color);

//For LongBuffermatin
ULONG rmt_long_mem_cnt=0;
UBYTE *rmt_data;
UBYTE long_mem_send_flag=0;
UBYTE LongMemoryHeaderBuf[20];
ULONG LongMemoryHeaderSize;

OS_EVENT *RmtCmdDoneSemPtr;
OS_EVENT *RmtLongMemoryReadySemPtr;
OS_EVENT *ReciveRmtDataSemPtr;

extern UBYTE KeyTaskBuf[2];
extern STR_PARSER parser_UART;
long RmtLongMemory=0;
char CommData_temp[255];
UBYTE CommData_count=0;
extern UBYTE PC_scriptrun;
char ErrQueueComm[16][64];
char disErrQ[64];

void delay_fast (unsigned short x){
	unsigned short y;
	while(x--){
		for (y=0;y<1000;y++)	asm("nop;");
	}

}
void InterfaceTask(void *para)
{
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
	OS_CPU_SR  cpu_sr;
	cpu_sr = 0;                                  /* Prevent compiler warning                           */
#endif
	UBYTE oserr,i,keycode,keycnt,err,SEQ_data;
	char str[50],CommData,SYNC_TMEM_temp;
	short x,y;
	p3k_send_tx_list tx_data;
	char initial_flag=1;
	ULONG SPORT1_Data;
	static UBYTE recodeFastStatus=0;
	static UBYTE recodeAlarmStatus=0;
	static UBYTE updateCnt=20;

	//All the interfaces, must initialized before this section.
	while(1) {
		if(OSSemAccept(InterfaceChangeSemPtr)) {
			if((D_interface.INTERFACE==INTERFACE_GPIB)&&(SYSType&GPIB_CONNECTED)) {//if((UTILITY.INTERFACE==INTERFACE_GPIB)&&(SYSType&GPIB_CONNECTED)) {
				/*GPIB selected.*/
				disconnect_USB();
				OSTimeDly(10);
				WriteIO(USB_ID,Host_Mode);//Host Mode
				FIO_ANOM_0311_MASKA_W(PF14,pFIO_MASKA_C);//Disable GPIB ISR
				//Configure NAT9914
				ResetGPIB();
				OS_ENTER_CRITICAL();
				WOutgoBuffer=GPIB_WOutGoBuffer;    /*For character string.*/
				WBOutgoBuffer=GPIB_WBOutGoBuffer;  /*For binary data.*/
				ParserGetc=GPIB_ParserGetc;
				OS_EXIT_CRITICAL();
				GpibCfgPort();
				FIO_ANOM_0311_MASKA_W(PF14,pFIO_MASKA_S);//Enable GPIB ISR
				initial_flag=1;
			} else if(D_interface.INTERFACE==INTERFACE_RS232) {//} else if(UTILITY.INTERFACE==INTERFACE_RS232) {
				/*RS232 selected.*/
				disconnect_USB();
				OSTimeDly(10);
				WriteIO(USB_ID,Host_Mode);//Host Mode
				FIO_ANOM_0311_MASKA_W(PF14,pFIO_MASKA_C);//Disable GPIB ISR
				UartCfgPort();
				OS_ENTER_CRITICAL();
				WOutgoBuffer=UART_WOutGoBuffer;    /*For character string.*/
				WBOutgoBuffer=UART_WBOutGoBuffer;  /*For binary data.*/
				ParserGetc=UART_ParserGetc;
				OS_EXIT_CRITICAL();
				initial_flag=1;
				/*Enable UART interrupt.*/
			} else if(D_interface.INTERFACE==INTERFACE_USB) {//} else if(UTILITY.INTERFACE==INTERFACE_USB) {
				/*USB selected.*/
				WriteIO(USB_ID,Device_Mode);//Device Mode
				OSTimeDly(10);
				FIO_ANOM_0311_MASKA_W(PF14,pFIO_MASKA_C);//Disable GPIB ISR

				OS_ENTER_CRITICAL();
				WOutgoBuffer=USBCDC_WOutGoBuffer;    /*For character string.*/
				WBOutgoBuffer=USBCDC_WBOutGoBuffer;  /*For binary data.*/
				ParserGetc=USBCDC_ParserGetc;
				OS_EXIT_CRITICAL();
				connect_USB();
				dc_start_hw();
				initial_flag=1;
			}
			long_mem_send_flag=0;
			OSSemPost(InterfaceReadySemPtr);
		}
		do {
#if Enable_RemoteFast
			if(DGIOCtrlFlag&REM_Mode_Fast) {
				thread_Parser_Driver(initial_flag);
				initial_flag = 0;
				SPORT1_Data = sport1Read(0xF0000000);
				OS_ENTER_CRITICAL();
				keycode	= (SPORT1_Data&0x0000FF00)>>8;
				keycnt	= SPORT1_Data&0x000000FF;
				OS_EXIT_CRITICAL();

				if((keycode==K_Load_Key)&&(UTILITY.LOAD_CTL)) {
					if (REM_CONT)
						; //Do nothinh while REMOTE Control
					else {
						UTILITY.LOAD_CTL = Switch_OFF;
						RunProgOff();
						PEL3000_LED_Control( LED_LOAD, UTILITY.LOAD_CTL );
						SysRedrawFlag |= PROG_UPDATA;
					}
				} else if( (keycode==K_Shift_Key)&&((KeyInFlag&SHIFT_KEY)==0) ) {
					KeyInFlag |= SHIFT_KEY;
					PEL3000_LED_Control(LED_SHIFT, 1);
				} else if( (keycode==K_Main_Key)&&(KeyInFlag & SHIFT_KEY) ) {
					KeyInFlag &= ~SHIFT_KEY;
					PEL3000_LED_Control(LED_SHIFT, 0);
					SetRemoteMode(0);
				}
				if(updateCnt==0) {
					updateCnt =10;
					if((recodeFastStatus != parser_UART.errQueue.cnt)||(recodeAlarmStatus!=p3k_Measure_Data.Alarm)) {
						recodeFastStatus = parser_UART.errQueue.cnt;
						if((recodeFastStatus<=3)||(recodeAlarmStatus!=p3k_Measure_Data.Alarm)) {
							recodeAlarmStatus=p3k_Measure_Data.Alarm;
							if(parser_UART.errQueue.cnt) {
								if(recodeAlarmStatus) {
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
								} else {
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
								if(recodeAlarmStatus) {
									Float_Windows_Setting(0,0,319,0x3b,Message_Font_Bolor);
									GUI_SetFont(Parameter_Font);
									GUI_SetBkColor(Message_Font_Bolor);
									GUI_SetColor(MEM_WHITE);
									GUI_SetTextAlign(GUI_TA_LEFT);
									FloatWindows_StringAt(" Remote Fast ",100,100);
								} else {
									Float_Windows_Setting(0,0,319,0x3b,MEM_WHITE);
									GUI_SetFont(Parameter_Font);
									GUI_SetBkColor(MEM_WHITE);
									GUI_SetColor(Message_Font_Bolor);
									GUI_SetTextAlign(GUI_TA_LEFT);
									FloatWindows_StringAt(" Remote Fast ",100,100);
								}
							}
							DMA_Update_Flag = 1;
							CtrlFlag1 |= Disp_IRange_Window + Float_Windows_DispOn;
							Update_Panel();
						}
					}
				} else {
					updateCnt--;
				}
#if Enable_RemoteFast
				OSTimeDly(SCPI_RemFastDelay);	//OSTimeDlyHMSM(0,0,0,2);
				if(SCPI_RemFastDelay){
					SCPI_RemFastDelay = 0;
				}else{
					if(D_interface.INTERFACE==INTERFACE_USB){
						delay_fast(800);
					}
				}
#else
				OSTimeDly(1);
#endif

			} else {
				thread_Parser_Driver(initial_flag);
				initial_flag = 0;
				OSTimeDly(2);
			}
#else
			thread_Parser_Driver(initial_flag);
			initial_flag = 0;
			OSTimeDly(2);
#endif

		} while(DGIOCtrlFlag&REM_Mode_Fast);
	}
}




