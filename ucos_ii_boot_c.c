/*******************************************************************************
*							µCOS-II Blackfin port test example
*							Blackfin Applications Team, Analog Devices Inc.,
*								Norwood, MA, US
*
* File: 				ucos_ii_boot_c.c
* Author: 				Deep Bodapati
* Last Modified: 		10-22-2006
* Project:				µCOS-II Blackfin port test example
* Platform: 			ADSP-BF533 EZKit Lite Evaluation Board (silicon rev 0.4 and higher)
* Tools:				VisualDSP++ 4.5 (Updated September 2006)
* µCOS-II Version: 		v2.83
*
* Note: The user LEDs on the ADSP-BF533 EZKit Lite Evaluation Board are labeled
* LEDs #4 through 9. On the other hand, the user LEDs on the ADSP-BF537 EZKit
* Lite Evaluation Board are labeled LEDs #1 through 6. For uniform software
* naming convention, the LEDs are labeled LEDs# 1 through 6 for both EZKits.
*
* This file is part of the test example, Ex1, of the µCOS-II port to the
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
#include <includes.h>
#include "keydef.h"
#include "../dio/dio.h"
#include "../menu/head.h"

/*********************************************************************
Static memory
*********************************************************************/
void TIMER1_DGIO(INT16U Delay_100ms);
void TIMER1_Pulse(void);
void Init_Timer_Interrupts(void);
void BuzzerFunction(UBYTE Buzzer_Mode,WORD ith);
void RecoverLastFuncOPP(void);
extern void EZKit_Init_Flags(void);
extern void EZKit_Init_EBIU (void);
extern void Init_SPI(void);
extern void Init_LCD_IO(void) ;
extern void Pt2Main(void);
extern void GUI_ModifyLUT(void);
extern int IsGPIB_Exist(void);
extern void Install_COMMISR(void);
extern void app_main(void);
extern char FRAM_INIT(void);
extern void SetupOnBoardSPI(const unsigned short spi_setting);
extern void SPI_OFF(void);
extern void RecoverLastSetupData(void);
extern void RecoverLastFuncOCP(void);
extern void SetRTC(UWORD second_flag);
extern void sport0Init(void);
extern void sport1Init(void);
extern void LoadDefaultProc(char mode);
extern void Load_Default_Interface(char mode);
extern void Update_Panel(void);
extern void RecoverLastOP(void);
extern void RecoverLastRunProg(void);
extern void RecoverAPPInfo(void);
extern void RecoverLastNSeq(void);
extern void RecoverLastFSeq(void);
extern void RecoverLastSerialNumber(void);
extern void RecoverCalData_DataFlash(char check_done);
extern void RecoverUserDefaultData(void);
extern char check_fpga_work(void);
EX_INTERRUPT_HANDLER(Timer_ISR);
/*
***************************************************************************
*
*	  Main program function
*
***************************************************************************
*/
extern GELMASTER *gel;
void SemphoreInit(void);
extern void Install_ISR(void);
extern void Debug_printf(char *Message);
extern void SendTXData(p3k_send_tx_list *data);
extern void GetResolution(void);
char IsfpgaOk; //Adam_0819
void main(void)
{

	OS_STK *stack;
	INT8U OS_result;
	char i;
	long j;
	p3k_send_tx_list tx_data;
	Serial_Number_Str *Serial=&P3k_Serial_Number;

	System_Ready = 0;
	sport0Init();
	sport1Init();
	EZKit_Init_Flags();
	EZKit_Init_EBIU();
	Init_Timer_Interrupts();

	Init_SPI();

	Init_LCD_IO(); //Initialize CPLD and LCD controller's I/O.
	ColorDefine();

	/* Setup Time */
	rtc_init();			/* Real Time Clock */

	/*************/
	GUI_Init();
	Pt2Main(); //Set function pointer to _SetPixel.

	GUI_ModifyLUT();

	ClrScreen(Parameter_Bottom_Bolor);  /*Test for 8bpp mode(dark blue).  Added by Kevin Meng 2004.09.22*/
	DMA_Update_Flag = 1;
	Update_Panel();
	/****************************************************************************/
	//Turn On Backlight
#if 1
	Init_LCD_Control();
#else
	WriteIO(LCD_BL_EN, 0);
#endif


	/****************************************************************************/

	if(IsGPIB_Exist()) {       //Check with/without GPIB card.
		/*The list of input pins Enable, 0 - Input Buffer Disabled, 1 - Input Buffer Enabled*/
		FIO_ANOM_0311_INEN_W( PF0   /*GPIB Check */
		                      |PF8  /*FPGA nSTATUS Read  */
		                      |PF10 /*FPGA nConfigDone Read */
		                      /*For Disable FPGA config after boot*/
		                      |PF7  /*FPGA Data0*/
#if	0//Enable_config_pin_high

#else
		                      |PF9  /*FPGA nConfig*/
#endif
							  |PF11 /*FPGA DCLK*/

//                          |PF13 /*IRQ IO,UART */
		                      |PF14 /*IRQ GPIB*/
		                    );
		SYSType|=GPIB_CONNECTED; //1: with GPIB card, 0: without GPIB card
	}
#if 0//Enable_config_pin_high
	FIO_ANOM_0311_FLAG_W(PF9 ,pFIO_FLAG_S);
	//OSTimeDly(50);
#endif
	
#if 1
	//OSTimeDly(200);
	IsfpgaOk = check_fpga_work();	//Adam_0819
	Install_ISR();
#else
	Install_ISR();
#endif
	Install_COMMISR();
	OSInit();		// Initialize uCOS-II (app_init is called from within here)

	//BF531 UART
	UART_init();
	SemphoreInit();
	CommInit();

	//Initial GPIB
	if(SYSType&GPIB_CONNECTED)
		GpibPowerOnInit(8);	//Create Semaphores

	GPIBPAR.MYADDR=1;
	M_num = P_CC;
	MenuRedrawFlag |= MENU_CHANGE;
	DataRedrawFlag |= DATA_CHANGE;
	ChanRedrawFlag |= CHAN_CHANGE;
	DGIOCtrlFlag=0x0;
	SysRedrawFlag |= SYS_CHANGE;
	KeyInFlag &= (~KEY_CHANGE);
	/*Get MACHTYPE*/
	tx_data.ADDRH = Machine_Command;
	tx_data.ADDRL = Machine_Init_Query;
	SendTXData(&tx_data);
	GetResolution();

	Load_Default_Interface(Recall_Interface_Y);
	LoadDefaultProc(System_Recall_Default);
	RecoverCalData_DataFlash(1);
#if 1
	if(FRAM_INIT()==(-1)) {
		FRAM_Data.Data_Ready = 0;
		Debug_printf("FRAM_INIT()==(-1)\n");
	} else {
		RecoverLastOP();
	}
#else
	FRAM_INIT();
	FRAM_Data.Data_Ready = 0;
	Debug_printf("FRAM_INIT()==(-1)\n");

#endif
	RecoverLastNSeq();
	RecoverLastFSeq();
	RecoverLastRunProg();
	RecoverLastSerialNumber();
	RecoverLastSetupData();
#if Enable_OCP_function
	RecoverLastFuncOCP();
#endif
#if Enable_OPP_function
	RecoverLastFuncOPP();
#endif
#if Enable_LED_function
	//RecoverLastFuncLED();
#endif


	RecoverUserDefaultData();
	RecoverAPPInfo();
	if(1) { //if(P3k_Serial_Number.version_flag==0){

		P3k_Backup_SN.Serial_Number.Version = P3k_Serial_Number.Version = Company_VERSION;

	}
	// -------------------------------------------------------------
	// Boot Thread (Priority: OS_LOWEST_PRIO-4)
	// Description - Main thread that installs core timer ISR and
	// launches all other threads

	stack = (OS_STK *)malloc( BOOT_THREAD_STACK_SIZE * sizeof(OS_STK) );
	if (stack == (OS_STK *)0) {
		printf("Heap allocation error\n");
		return;
	}

	if ( (OS_result = OSTaskCreateExt(ucos_ii_boot_thread,
	                                  (void *)NULL,
	                                  &stack[BOOT_THREAD_STACK_SIZE-1],
	                                  (BOOT_THREAD_PRIO),
	                                  (BOOT_THREAD_PRIO),
	                                  &stack[0],
	                                  BOOT_THREAD_STACK_SIZE, 			// About Stack of each Task
	                                  (void *)0,
	                                  0 )) )
		while(1);

	// Start uCOS-II - this function call never returns

	OSStart();

}// end of main


//--------------------------------------------------------------------------
// Function:	ucos_ii_boot_thread
//
// Parameters:	None
//
// Return:		None
//
// Description:	This is called the boot thread of the application. This
// intializes the ticker interrupt and calls app_main().
//--------------------------------------------------------------------------
void ucos_ii_boot_thread (void* p)
{
	INT8U OS_result;

	//CoreTimerInit(37, 52648);  //TimeTick 5ms
#if 1
	CoreTimerInit(37, 104945);	//TimeTick 10ms
#else
	CoreTimerInit(37, 104950);	//TimeTick 10ms
	CoreTimerInit(37, 105025);	//TimeTick 10ms
	CoreTimerInit(37, 104891);	//TimeTick 10ms
	CoreTimerInit(37, 105296);	//TimeTick 10ms
#endif
	app_main();

	if ( (OS_result = OSTaskDel(OS_PRIO_SELF)) )
		while(1);
}
void SemphoreInit(void)
{
	KeyCodeDoneSemPtr=OSSemCreate(1);
	OSAssert(KeyCodeDoneSemPtr);
	KeyCodeReadySemPtr=OSSemCreate(0);
	OSAssert(KeyCodeReadySemPtr);
	LcdUnlockSemPtr= OSSemCreate(1);
	OSAssert(LcdUnlockSemPtr);
	InterfaceChangeSemPtr = OSSemCreate(1);		//?
	OSAssert(InterfaceChangeSemPtr);
	InterfaceReadySemPtr = OSSemCreate(0);
	OSAssert(InterfaceReadySemPtr);
	RxBufferOverSemPtr=OSSemCreate(0);
	OSAssert(RxBufferOverSemPtr);
	CalDataReadySemPtr=OSSemCreate(0);
	OSAssert(CalDataReadySemPtr);
	LuaDispReadySemPtr = OSSemCreate(0);
	OSAssert(LuaDispReadySemPtr);
	LuaDispDoneSemPtr = OSSemCreate(0);
	OSAssert(LuaDispDoneSemPtr);
	LuaDispEventSemPtr = OSSemCreate(0);
	OSAssert(LuaDispEventSemPtr);
}

void Timer_ISR_Hook(void)
{
	if(*pTIMER_STATUS & TIMIL1) {
		*pTIMER_DISABLE = TIMDIS1;			//disable Timer
		*pTIMER_STATUS = TIMIL1	| TRUN1;	// clear status
		ssync();
	}

	if(*pTIMER_STATUS & TIMIL2) {
		*pTIMER_DISABLE = TIMDIS2;	//disable Timer
		*pTIMER_STATUS = TIMIL2 | TRUN2;   // clear status
		ssync();
	}

	if(*pTIMER_STATUS & TIMIL0) {
		*pTIMER_DISABLE = TIMDIS0;	//disable Timer
		*pTIMER_STATUS = TIMIL0 | TRUN0;   // clear status
		ssync();

		if(Tone_Flag & 0x01)
			BuzzerFunction(Buzzer_Alarm	,Alarm_Count--);
		else if(Tone_Flag & 0x02)
			BuzzerFunction(Buzzer_NG	,NG_Count--);
		else if(Tone_Flag & 0x04)
			BuzzerFunction(Buzzer_UnReg	,UnReg_Count--);
#if Enable_Ring_Count
		else if(Tone_Flag & 0x08)
			BuzzerFunction(Buzzer_Complete	,Complete_Count--);
#endif

		else
			BuzzerFunction(Buzzer_Key	,Key_Count--);
	}
}
#if Enable_Ring_Count
extern UWORD UVP_Tone_Count;
extern UWORD SEQ_Tone_Count;
#endif

void BuzzerFunction(UBYTE Buzzer_Mode,WORD ith)
{
	ULONG Period_Value;

	if(ith<0) {							/*	Buzzer Off		*/
		*pTIMER_DISABLE	= TIMDIS0;			/*	Timer0 disable.	*/
		*pTIMER_STATUS  = TIMIL0 | TRUN0;	/*	clear status		*/
		*pTIMER0_PERIOD = 6250000;
		*pTIMER0_CONFIG = TMODE_PWMOUT	|
		                  PULSE_HI		|
		                  PERIOD_CNT	|
		                  IRQ_ENA		|
		                  OUT_DIS;
		asm("nop;");
		ssync();

		if(Buzzer_Alarm == Buzzer_Mode) {
			if((UnReg_Alarm != p3k_Measure_Data.Alarm) && (p3k_Measure_Data.Alarm != 0)  && UTILITY.Master_Alarm_Tone) {
				Alarm_Count = 250;
				*pTIMER_ENABLE = TIMEN0;/*Timer0 enable.*/
			} else{
#if Enable_Ring_Count
				if(UVP_Tone_Count>1){
					Alarm_Count = 250;
					*pTIMER_ENABLE = TIMEN0;/*Timer0 enable.*/
				}else{
					Tone_Flag &= ~(0x01);
				}
#else
				Tone_Flag &= ~(0x01);
#endif
			}
		} else if(Buzzer_NG == Buzzer_Mode) {
			if(UTILITY.Master_NG_Tone && (p3k_Measure_Data.Go_NoGo == 1)) {
				NG_Count = 300;
				*pTIMER_ENABLE = TIMEN0;/*Timer0 enable.*/
			} else
				Tone_Flag &= ~(0x02);
		} else if(Buzzer_UnReg == Buzzer_Mode) {
			if(UTILITY.UnReg_Alarm_Tone && (p3k_Measure_Data.Alarm == UnReg_Alarm)) {
				UnReg_Count = 200;
				*pTIMER_ENABLE = TIMEN0;/*Timer0 enable.*/
			} else
				Tone_Flag &= ~(0x04);
		}
#if Enable_Ring_Count
		else if(Buzzer_Complete== Buzzer_Mode) {
			if((SEQ_Tone_Count>1)&&(UTILITY.Master_Alarm_Tone)){
				Complete_Count = 800;
				*pTIMER_ENABLE = TIMEN0;/*Timer0 enable.*/		
			} else{
				Tone_Flag &= ~(0x08);
				Complete_Count = 0;
			}
		}

#endif		
	} else {
		if(Buzzer_Alarm == Buzzer_Mode)
			Period_Value = 140000;
		else if(Buzzer_NG == Buzzer_Mode)
			Period_Value = 70000;
		else if(Buzzer_UnReg == Buzzer_Mode)
			Period_Value = 70000;
#if Enable_Ring_Count		
		else if(Buzzer_Complete == Buzzer_Mode)
			Period_Value = 40000;
#endif		
		else
			Period_Value = 20000;

		*pTIMER_DISABLE	= TIMDIS0;				/*Timer0 disable.*/
		*pTIMER_STATUS  = TIMIL0 | TRUN0;		// clear status
		*pTIMER0_WIDTH  = 20;					//Prevent Timer0 period error. See BF533 HW reference P15-13.
		*pTIMER0_PERIOD = Period_Value;
		*pTIMER0_WIDTH  = Period_Value/2;
		*pTIMER0_CONFIG = TMODE_PWMOUT	|		//Timer0 output enable.
		                  PULSE_HI		|
		                  IRQ_ENA		|
		                  PERIOD_CNT;
		*pTIMER_ENABLE  = TIMEN0;				/*Timer0 enable.*/
	}
}

/****************************************************************************
*   Function:    InitTIMER1
*   Description: Init Timer1 to act as the veritical frame sync
******************************************************************************/
void Enable_TIMER1 (INT32U PERIOD)
{
	*pTIMER_DISABLE = TIMDIS1;	//disable Timer
	*pTIMER_STATUS  = TIMIL1 | TRUN1;	// clear status
	//*pTIMER_STATUS = TIMIL1 | TRUN1 | TOVF_ERR1;   // clear status
	*pTIMER1_PERIOD = PERIOD;
	*pTIMER1_WIDTH = PERIOD/2;
	*pTIMER1_CONFIG = TMODE_PWMOUT	|
	                  PERIOD_CNT	|
	                  IRQ_ENA		|
	                  OUT_DIS;
	*pTIMER_ENABLE  = TIMEN1;
	ssync();
}
void Enable_TIMER2 (INT32U PERIOD)
{
	*pTIMER_DISABLE = TIMDIS2;	//disable Timer
	//*pTIMER_STATUS  = TIMIL2 | TRUN2 ;	// clear status
	*pTIMER_STATUS = TIMIL2 | TRUN2 | TOVF_ERR2;   // clear status
	*pTIMER2_PERIOD = PERIOD;
	*pTIMER2_WIDTH = PERIOD/2;
	*pTIMER2_CONFIG =
	        TMODE_PWMOUT|		/* PWM mode*/
	        PERIOD_CNT	|		/*count to end of period*/
	        IRQ_ENA		|
	        OUT_DIS;
	*pTIMER_ENABLE = TIMEN2;
	ssync();
}
void Init_Timer_Interrupts(void)
{
	register_handler (ik_ivg11,					 // Register Timer ISR and enable
	                  Timer_ISR);	// IVG11 (Timer)
	*pSIC_IMASK = IRQ_TIMER0 | IRQ_TIMER1 | IRQ_TIMER2;
	ssync();
}
void TIMER1_DGIO(INT16U Delay_100ms)
{
	INT32U Total_Delay_Count;

	if(!(DGIOCtrlFlag & Timer_DGIO_ON))
		return;
	Total_Delay_Count=((Delay_100ms-1)*4970000)+4999872-Timer1_DGIO_Count_Temp;
	Enable_TIMER1(Total_Delay_Count);
	if(Timer1_DGIO_Count_Temp)
		Timer1_DGIO_Count_Temp=0;
}
void TIMER1_Pulse(void)
{
	INT32U Total_Delay_Count;

	if(!(DGIOCtrlFlag & Timer_DGIO_ON))
		return;
	Enable_TIMER1(600);  //29us
	//Enable_TIMER1(25000);  //500us
}


