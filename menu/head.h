/***********************************************************************
 
	PEL3031-E  (PEL1000B)

	FPGA 0X05  --> PSENOR	
 
 ***********************************************************************/

#if 0
程式命名  規 則
	
1 變數命名規則:
	區域變數 採Camel Case 規則
		int manyPeople;
	全域變數 採Pascal Case規則
		int  ManyPeople;
		
	變數的名字應當使用“名詞”或者“形容詞＋ 名詞”
	float value;
	float oldValue;
	float newValue;	
	
	靜態變數加前綴s_（表示static）
	static int s_InitValue; // global 靜態變量
	void Init(…)
	{
		static int s_initValue; // local 靜態變量
		…
	}
	類似的數據成員加前綴m_（表示member），這樣可以避免數據成員與成員函數的參數同名
	void Object::SetValue(int width, int height)
	{
		m_width = width;
		m_height = height;
	}
	
2 函數 (Functions)命名規則

	函數名稱完全採用小寫英文字母.字與字之間使用 _ 來連接, 
		setup_page_breaks()	
	用 正確的反義詞組命名具有互斥意義的變量或相反動作的函數等。
		int set_value(…);
		int get_value(…);
	function 的名字應當使用“動詞”或者“動詞＋名詞”。
		draw_box(); // function
		
	要儘量將功能有相關的函數加上相同的前置文字(可容易看出是相同群組的函式)
	 email_, news_, … 等等。
	 
	 
3 常數命名規則
	常數名稱完全採用大寫英文字母.字與字之間使用 _ 來連接, 
		例如. ROOT_PATH
	 
	#define ABC_EFG_HIJ
	typedef ABC_EFG

5 檔案命名規則
	檔案名稱完全採用小寫英文字母.
	字與字之間使用 _ 來連接, 例如. view_new_bugs_page.c
	
6. typedef 
	以全大寫字母，字與字 中間加﹍，前面加t
	typedef struct SettingData
	{
		int     CurrentSetting;
		int     SettingMin;
		int     SettingMax;
		int     DefaultSetting;
	} tSETTINGDATA, *ptSETTINGDATA;

	DATA_STR 		*p_DataTmp = &P3k_Chan_Data; //*pDeatTemp
	
	
other : 
	常用動詞單字:
		acess
		cmd
		check
		clear
		dump
		draw
		exe
		find
		fresh
		goto
		get
		is
		init
		instead
		key
		open
		place
		set
		setup
		updata
		upload
		
	型容詞:
		alarm
		error
		max
		min
		new
		old
		timeout
		right

#endif


#ifndef HEAD_H
#define HEAD_H
#include <time.h>


//--- Version ---------------------------------------------------------------------------------
#define Company_VERSION				0  //   0:GW, 1:TEXIO, 2:NF, 3:Chiyoda  //Wasabi_g2k builded it 
#define Main_Version				0
#define Sub_Version					31
#define Machine_Number				2 //delet
#define File_Version				0
#define Versiondate					(unsigned short)721  //data(0918) + Version(5)
#define Version_2					(unsigned short)1 //data(0918) + Version(5)


//--- System ---------------------------------------------------------------------------------
#define SCLK_50Mhz					0
#define Enable_DMA_Display			1
//-----------------------------------------------------------------------------------
#define Enable_P_Compensation		1
//--- Optim  ---------------------------------------------------------------------------------
#define Enable_RemoteFast			1 //remote control
#define Enable_Optim_display		1
#define Enable_Menu_optim			1///1


//----Functions ---------------------------------------------------
#define Enable_Func_DisTime			1
#define Enable_OCP_function			1 ///// look at OCP
#define Enable_Func_select			1

#define Enalbe_FSEQ_1US				0
#define Enable_FSEQ_RPT				1
#define Enable_NSEQ_Usec			1

// ---- new function -----------------------------------------------
#define Enable_AutoLoad				1 //AutoLoad(Mode): on/off, AutoLoad(Range): on/off -->default:0
///#define Enable_Ext_Measure			1
#define Enable_Ring_Count			1
#define Enable_Battery_Discharge	1
#define Enable_OPP_function			1
#define redraw_new_flag				1 // default : 0
#define Enable_LED_function			1

//---- Modify---------------------------------------------------
#define Enable_fseq_deletAll		1
#define Enable_Ext_CalOffset		1
#define Enable_config_pin_high		0
#define Enable_SoftStartOn			1 //softstart 1~200msec
#define Enable_loadtime_by_rtc		1
#define Enable_OPPOCP_off			1
#define Enable_mark_short_unReg		1
#define Enable_delet_RCT			1
#define Enable_Dymic_T_6			1
#define Enable_Short_invalidate 	1 //0803


//---Will be Deleted
#define Enable_FPGA_test			1
#define Enable_optimization			1

//--- debug mode--------------------------------------------------------------------
#define debug_tool					1 //password:3000
#define Enable_FPGA_history			1
#define test_debug					0 //0---------------------test used
#if test_debug
#define Normal_TEST					1
#define debug_word           		"<< debug mode : 1130_1 >>"
#define debug_MACHTYPE				MODEL3032E//MODEL3111
#define Enable_cathc_photo			1
#else
#define Normal_TEST					0
#define Enable_cathc_photo			0
#endif

#if Enable_Dymic_T_6
	#define DyMax					60000
#else
	#define DyMax 					30000
#endif

#if 1
#define PinON 	FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_C)
#define	PinOFF 	FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_S)
#else
#define PinON 	//FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_C)
#define	PinOFF 	//FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_S)
#endif
// setVolStep to measureStep 
#define	MEASURE_GAIN_3031 			0.8	
#define	MEASURE_GAIN_3032 			1.1

/* calibration setting*/
#define Calibration_Adj_maxValue	20000//50000
#define Calibration_Adj_minValue	0//10000
#define Calibration_Adj_defalut		10000

#define Monitor_H					36000.0
#define Monitor_L					3600.0

#define P_SENSOR_MAX				57000
#define P_SENSOR_MIN				10000


#define MeasureMode					0
#define CalTxtMode					1
#define CalBackup					2
#define printScreen					3
#define RunningRecord				4
#define DownModeEnd					5

#define Small_Current_setting		10
#define Lua_function      		    0
#define Cal_Max_Min					20		/* Cal Max Value=Def*(1+Cal_Max_Min/100) , Cal Min Value=Def*(1-Cal_Max_Min/100) */
#define Fetch_Quer_time 			2		/* Send Fetch Query on 10*Fetch_Quer_time ms */
#define Measure_Quer_time 			10		/* Send Measure Query on 10*Measure_Quer_time ms */
#define Check_KNOB_VAL_change_time	6		




//DispMode Define
//DispMode Define
#define DispMode_SELECT_CH          0
#define DispMode_BROWSE_ITEMS       1
#define DispMode_SET_PARAMETERS     2
#define DispMode_ReadRecord			3
#define DispMode_dis_fpga_setting   4
#define DispMode_dis_fpga_status	5
//#define Debug_display				6
#define test_mode_end			    6


#if Enable_OCP_function


#if Enable_OPP_function
	#if Enable_LED_function
#define KEYINNUM_MAX				70//44
#define MAXMENU 					70//44
	#else
#define KEYINNUM_MAX				54//44
#define MAXMENU 					54//44
	#endif
#else
#define KEYINNUM_MAX				48//44
#define MAXMENU 					48//44
#endif

#else
#define KEYINNUM_MAX				45//44
#define MAXMENU 					45//44
#endif

#define KEYINNUM_WEDTH				16
#define MAX_LANGUAGE  				50
#define MAX_LANGUAGE_USED 			1
#define INTERFACE_RS232 			0
#define INTERFACE_GPIB 				1
#define INTERFACE_USB 				2

#define F1_KEY 						0
#define F2_KEY 						1
#define F3_KEY 						2
#define F4_KEY 						3
#define F5_KEY 						4

#define CC_MODE						0
#define CR_MODE 					1
#define CV_MODE	 					2
#define CP_MODE	 					3
#define CxCV_MODE 					4
#define F_IMON_MODE 				5
#define R_IMON_MODE 				6
#define Ext_V_CC_MODE				7
#define Ext_R_CC_MODE				8
#define MODE_Number 				9

/* For Switch */
#define Switch_ON					1
#define Switch_OFF					0

#define MEDIA_MEMORY 				0
#define MEDIA_USB 					1
#define MEDIA_DEFAULT 				2

#define LED_LOAD					0
#define LED_SHIFT					1
#define LED_PRESET					2
#define LED_SHORT					3

#define LONG_PUSH_TIME				16

#define SR_PRESET_MODE				0
#define SR_MEMORY_MODE				1
#define SR_SEQ_MODE					2


#define T_SYNC_ENABLE				0
#define T_SYNC_LOAD					1
#define T_LOAD_STATUS				2
#define T_ALARM_STATUS				3
#define T_GONG_ENABLE				4

/* Machine Model number */
#define MODEL3031E					0x00
//#define MODEL3070					0x01
//#define MODEL3111					0x02
#define MODEL3032E					0x04
//#define MODEL3020					0x06

/* Frame Control */
#define Sync_Enable					0x01
#define Sync_Load_ON_OFF			0x02
#define Load_Status					0x04
#define Alarm_Status				0x08
#define GO_NG_Enable				0x10

/* Timer TMODE */
#define TMODE_PWMOUT				0x0001
#define TMODE_WDTHCAP				0x0010
#define TMODE_EXTCLK				0x0011

#define CommData_Size				40960
#define CommLength					15

#define Recall_Success				1
#define Recall_Failed				0
#define Recall_Complete				1
#define Machine_Type_Error			2
#define Memory_Version_Error		3
#define Mallo_Version_Error			3

#define Action_Success				1
#define Action_Failed				0


#define Compare_Value				0x8000

/*	Version	*/
#define GW_Version					0x00
#define	TEXIO_Version				0x01
#define NF_Version					0x02
#define Chiyoda_Version				0x03

#if Company_VERSION >= NF_Version
#define NF_flag						1
#else
#define NF_flag						1
#endif

/*DispParameter*/
#define Parameter_Font_Bolor_Para		MEM_DARKGRAY
#define Parameter_Font_Bolor_No_Sync	MEM_DARKRED_ku
#define Parameter_Font					&GUI_FontArialUnicodeMS25
#define Parameter_Bottom_Bolor			MEM_BLACK
#define Parameter_Font_U_Bolor			MEM_DARKGREEN_ku
#define Parameter_Font_R_Bolor			MEM_WHITE
#define Parameter_Font_L_Bolor			MEM_ORANGE_ku
#define Parameter_Select_Bar_Bolor		MEM_DARKBLUE_ku
#define Parameter_Select_Font_Bolor		MEM_DARKBLUE_ku
#define Parameter_Select_Bottom_Bolor	MEM_WHITE
#define Message_Bottom_Bolor			MEM_BLACK
#define Message_Font_Bolor				MEM_DARKRED_ku//MEM_DARKRED_ku
#define Noted_Font_Bolor				MEM_YELLOW
#define GO_Font_Bolor					MEM_WHITE
#define NG_Font_Bolor					MEM_DARKRED_ku
#define Alarm_Font_Bolor				MEM_DARKRED_ku


/* DispUpperProcess */
#define Upper_Font						&GUI_FontArial15
#define Upper_Bottom_Bolor				MEM_LIGHTGRAY_ku
#define Command_message_Bottom_Bolor	MEM_DARKGREEN_ku
#define Command_message_Font_Bolor		MEM_BLACK
#define Alarm_message_Bottom_Bolor		MEM_DARKRED_ku
#define Alarm_message_Font_Bolor		MEM_WHITE

/* DispRightProcess */
#define Right_Font						&GUI_FontArial15			/*&GUI_FontTimesNewRoman17*/
#define Right_Bottom_Bolor				MEM_DARKBLUE_ku
#define Right_Font_Down_Bolor			MEM_DARKGREEN_ku
#define Right_Font_Up_Bolor				MEM_ORANGE_ku
#define Right_Select_Font_Bolor			MEM_WHITE
#define Right_Select_Bottom_Bolor		MEM_ORANGE_ku

/* DispFileProcess */
#define File_Font						&GUI_FontArial18			/*&GUI_FontTimesNewRoman17*/
#define File_Bottom_Bolor				MEM_BLACK
#define File_Path_Font_Bolor			MEM_DARKGREEN_ku
#define File_Print_Font_Bolor			MEM_ORANGE_ku
#define File_Select_Bar_Bolor			MEM_DARKBLUE_ku
#define File_Message_Font_Bolor			MEM_YELLOW//MEM_DARKRED_ku

#define Measure_Font					&GUI_FontArial51
#define Measure_Unit_Font				&GUI_FontArial30
#define Time_Alarm_Font					&GUI_FontArial22

/* *************  SYSTEM INTERRUPT CONTROLLER MASKS *************************************/
#define IRQ_TIMER0		0x00010000
#define IRQ_TIMER1		0x00020000
#define IRQ_TIMER2		0x00040000

//SaveFileFlag
#define 	SaveFileFlagNoKeypad 		0x0000
#define 	SaveFileFlagUseKeypad 		0x0001
#define 	SaveFileFlagNewFolder 		0x0002
#define 	SaveFileFlagRename 			0x0004
#define 	SaveFileFlagKeypadUpdate 	0x0008
#define 	SaveFileFlagCsvFile 		0x0010
#define 	SaveFileFlagStrUpdate 		0x0080

/*For Wave From Save/Recall */
#define Sav_Set				0
#define Sav_Memory			1
#define Sav_Preset			2
#define Sav_Result			3
#define Sav_SEQ				4
#define Sav_NSeq			5
#define Sav_FSeq			6
#define USBNumerTotal 		100

/*USB_Status*/
#define USB_NotExist		0
#define USB_Busy			1
#define USB_Exist			2

/*Save_Recall_InfoFlag*/
#define Data_Process 		0x0001
#define Save_Ok 			0x0002
#define Save_Fail 			0x0004
#define Save_All_Ok			0x0008
#define Save_All_Fail		0x0010
#define Recall_Ok 			0x0020
#define Recall_Fail			0x0040
#define Type_Error			0x0080
#define Device_Error		0x0100
#define No_File				0x0200
#define password_error		0x0400

#define PROT_OCP_L			0
#define PROT_OCP_H			1
#define PROT_OPP_L			2
#define PROT_OPP_H			3
#define PROT_UVP_L			4
#define PROT_UVP_H			5
#define PROT_OVP_L			6
#define PROT_OVP_H			7

#define F_OCP_OPP_CONFIG				0
#define F_OCP_OPP_LOOKFOR				1
#define F_OCP_OPP_COMPLETE				2
#define F_OCP_OPP_TIMEOUT				3
#define F_OCP_OPP_CONFIG_ERR			4


#define BATT_CONFIG						0
#define BATT_DISCHARE					1
#define BATT_COMPLETE					2

#define F_LED_CONFIG					0
#define F_LED_EXECUTE					1
#define F_LED_LOAD_OFF					2




//#pragma pack(1) //======================   Adam add  test  2013 0722======================================

typedef struct	{
				unsigned char _X1:2;
				unsigned char _X10:3;
				unsigned char _X100:3;
				}_Unit;

/*********************************************************************************************/
/*  Define New Format of Memory Map on 082807 */
/*  Add By A.C */

typedef struct	{
				ULONG Offset,Length;/*define the offset for each struct*/
				void *STRU;
				void *DEFAULT;/*default data for Setup operation*/
				WORD Reserved1;
				WORD Reserved2;
				}StruInfo; /*Total 20 bytes.*/

/****************************************************************************************
     Master Data Struct 
****************************************************************************************/
typedef struct	{
				char ONOFF;
				char MYADDR;     		/* Denote DSO address at GPIB chain */
				char PRN_ADDR;   		/* Denote Printer Address at GPIB chain */
				char Reserved[5];
				}gpibpar;				/*Total 8 bytes.*/
             
typedef struct	{						/*Direct Control the COMM1 (UART1 of 5206e)*/
				char ONOFF;
				char BAUD;				/*0:2400,1:4800,2:9600,3:19200,4:38400*/
				char DBITS;				/*Not Used for GDS-820 Feb 19 '03 */
				char STOP;				/*0:1,1:2*/
				char PARITY;			/*0:NONE,1:Odd,2:Even*/
				char Reserved1[3];
				}rs_232; 				/*Total 8 bytes.*/

typedef struct	{				//Direct Control the COMM1 (UART1 of 5206e)
				char INTERFACE;			/*0:RS-232 1:GPIB  2:USB*/
				char BAUD;				/*0:2400,1:4800,2:9600,3:19200,4:38400*/
				char STOP;				/*0:1,1:2*/
				char PARITY;			/*0:NONE,1:Odd,2:Even*/
				char MYADDR;			/* Denote DSO address at GPIB chain */
				char Reserved[3];
				}interface_disp; 		/*Total 8 bytes.*/

//===== PARALLER MODE -----------------------------------------------------------------------//


//===== PARALLER MODE -----------------------------------------------------------------------//
typedef struct	{   
				char INTERFACE; 			/*0:RS-232 1:GPIB  2:USB*/
				char LANGUAGE; 				/*English,Tchinese,Schinese,Korean,Spanish,Russian,Japan,German,Polish*/
											/*BYTE BEEP*//*0:HiFreq, 1:LoFreq, 2:DualTone*/
				char USB_ONOFF;			
				char BEEP;					/*0:HiFreq, 1:LoFreq, 2:DualTone*//*Master Beep*/
				char BEEP_ONOFF;			/*0:OFF 1:ON*/
				char CONTRAST_LV;			/*Level=0~??*/
				char BRIGHTNESS_LV;			/*Level=0~??*/
				char LOCK_KEY;				/*0:OFF 1:ON*/
				char KEYKNOB;				/*0:Old 1:Updated*/
				char LOAD_CTL;				/*0:OFF 1:ON*/  
				char ALOAD;					/*0:OFF 1:ON*/
				char ALOAD_MODE;			/*0:LOAD 1:PROG 2:NSeq 3:FSeq*/
				unsigned char FAN_SPEED;	/*Range=0~255*/
				char MEAS_SCAN;         	/*0:OFF 1:ON*/
				char Master_Alarm_Tone; 	/*0:OFF 1:ON*/ 
				char UnReg_Alarm_Tone;  	/*0:OFF 1:ON*/
				char Master_NG_Tone;		/*0:OFF 1:ON*/ 
				char Rotate_Knob;			/*0:SetValue 1:Measure*/
				char SHORT_CTL;				/*0:OFF 1:ON*/
				char Reserved;
#if Enable_AutoLoad
					char AutoLoadOffMode; //default:1, 1:autoloadoff
					char AutoLoadOffRange;//default:1, 1:autoloadoff
					char ShortonLoadoff;  //0: short on loadoff and loadon,   1: short on loadon, default:0
					char Reserved_2;
				
					ULONG Reserved2[9];
#else
					ULONG Reserved2[10];
#endif

				 }utility;	/*Total 60 bytes.*/

typedef struct	{	
				char MEMNO[10];							/* Memory mapping number 						*/
				short PFTIME[10];						/* Pass & Fail Time 							*/
				short SHORTCHAN[10];					/* Short Channel								*/
				short SHORTTIME[10];					/* Short Time									*/	
				short ONTIME[10];						/* Load On Time 								*/
				short OFFTIME[10];						/* Load Off Time								*/
				char RUNMODE[10];						/* Sequence Run Mode 0:Skip, 1:Auto, 2:Manual	*/
				}prog_str;

typedef struct	{
				char MODE;								/* 	Chan Mode 0:CC, 1:CR, 2:CV, 3:CP			*/
				char STATUS;							/* 	Bit0:Range Hi / Low						*/
														/*	Bit1:Dynamatic On/Off						*/
														/*	Bit2:Go-NoGo On/Off						*/
														/* 	Bit3:Go-NoGo Precent/Value					*/
														/* 	Bit4:T1_RANGE(Only CC Dyn Mode)			*//* 	Bit4:Select A/B							*/
														/* 	Bit5:Response Fast/Slow(Only CV Mode)		*/			
														/* 	Bit6:Vrange								*/
														/* 	Bit7:T2_RANGE(Only CC Dyn Mode)			*/
													
														/* 	Bit6:Vrange								*/			
				UWORD VALUE1;							/*	Static mode = Value1, Dynamic mode = Label1 	*/
				UWORD VALUE2;							/* 	Static mode = Value2, Dynamic mode = Label2 	*/
				UWORD SLEWRATEUP;			
				UWORD SLEWRATEDN;
				UWORD TIME1;							/*	Dynamic Mode Only 					*/
				UWORD TIME2;							/*	Dynamic Mode Only 					*/
				UWORD CENTERVAL;						/*	Go-NoGo Function						*/
				UWORD HIGHVAL;
				UWORD LOWVAL;
				}memdata;			/*	Total 20 Bytes */
typedef struct	{
				double MODE;							/* 	Chan Mode 0:CC, 1:CR, 2:CV, 3:CP			*/
				double STATUS;							/* 	Bit0:Range Hi / Low						*/
														/*	Bit1:Dynamatic On/Off						*/
														/*	Bit2:Go-NoGo On/Off						*/
														/* 	Bit3:Go-NoGo Precent/Value					*/
														/* 	Bit4:T1_RANGE(Only CC Dyn Mode)			*//* 	Bit4:Select A/B							*/
														/* 	Bit5:Response Fast/Slow(Only CV Mode)		*/			
														/* 	Bit6:Vrange								*/
														/* 	Bit7:T2_RANGE(Only CC Dyn Mode)			*/
														
														/* 	Bit6:Vrange								*/			
				double VALUE1;							/*	Static mode = Value1, Dynamic mode = Label1 	*/
				double VALUE2;							/* 	Static mode = Value2, Dynamic mode = Label2 	*/
				double SLEWRATEUP;			
				double SLEWRATEDN;
				double TIME1;							/*	Dynamic Mode Only 					*/
				double TIME2;							/*	Dynamic Mode Only 					*/
				double CENTERVAL;						/*	Go-NoGo Function						*/
				double HIGHVAL;
				double LOWVAL;
				}memdata_recall;	/*	Total 76 Bytes */
typedef struct	{
				char PROGNO;							/* 	Run Prog 0~11 */
				char SEQNO;								/*	Sequence No 0~9 */
				short REPEATCT;							/* 	Run Prog Repeat Counter 1 ~ 9999 		*/
				prog_str PROG[12];

				char SPEC;								/*	Run Program 0=Off, 1=On				*/
				char CHAINSTART;						/*										*/
				char PROGSEQ[14];						/*	12: A point, 13: B point					*/

				char ACTCH[8];							/*	Active Channel Ch1 ~ Ch8 1 = On or 0 = Off	*/
				}runprog;

typedef struct	{
				UBYTE Loop_Point;						/* 	Loop_Point 0~119 */
				short REPEATCT;							/* 	Run SEQ Repeat Counter 0 ~ 9999		*/
				UBYTE Max_Number;						/* 	Loop_Point 0~119 */
				UBYTE Curr_Number;						/* 	Curr_Number 0~119 */
				char MODE;								/*   0:CC_MODE, 1:CR_MODE */
				char RANGE;								/*	Range 0=Low, 1=Hi	*/
				ULONG Duration[120];					/*    0.1ms~6S or 1ms~60s or 10ms~600S or 100ms~6000S or 1s~60000S*/
				ULONG Reserved[11];
				UBYTE Reserved1;
				}runseq;
typedef struct	{
				char ACTCH[8];							/*	Active Channel Ch1 ~ Ch8 1 = On or 0 = Off */
				char Main_Chan;	
				char SPEC;								/*	Run SEQ 0=Off, 1=On	*/
				char TRIG_OUT;								/*	Trig OUT Select	*/
				char TRIG_IN;								/*	Trig OUT Select	*/
				char Reserved[4];
				}__attribute__((packed)) seqdata;

typedef struct	{
				char PROGNO[120];		/* Program number 1~12 */
				char SEQNO[120];		/* Sequence number 1~10 */
				char MEMNO[120];		/* Memory Index 1~120 */
				char RUNMODE[120];		/* Run mode: auto, manual */			
				short SHORTCHAN[120];	/* Short Channel */
				short CH1NG[120];		/* Channel 1 NG counter */
				short CH2NG[120];		/* Channel 2 NG counter */
				short CH3NG[120];		/* Channel 3 NG counter */
				short CH4NG[120];		/* Channel 4 NG counter */
				short CH5NG[120];		/* Channel 5 NG counter */
				short CH6NG[120];		/* Channel 6 NG counter */
				short CH7NG[120];		/* Channel 7 NG counter */
				short CH8NG[120];		/* Channel 8 NG counter */
				UBYTE TOTAL_CT;			/* Total counter */
				UBYTE L_START;
				char GO_CT;				/* 0~119*/
				char REPEAT;			/* 0:One Time 1:Cycle Time */
				char MANUAL_CTRL;		/* 0:Auto, 1:Manual */
				char Temp;				/*	(1)* complement 4 multiplier*/
				short S_CT;				/* Short Counter */
				short ON_CT;			/* On time counter */
				short OFF_CT;			/* Off time counter */
				short PFTIME[120];		/* Pass & Fail Time*/
				}dgiochainlist;
typedef struct	{
				char ONOFF;				/*0:OFF 1:ON*/
				char RMEM;				/*Memory number*/
				char RSTATUS;
				char TMEM;
				char TSTATUS;
				char Reserved[3];
				}extdgio;				/*Total 8 bytes.*/
/****************************************************************************************
     Slave Data Struct 
****************************************************************************************/
// Dynamatic Mode Setup 
typedef struct	{
				UWORD LEVEL1;
				UWORD LEVEL2;
				UWORD SLEWRATEUP;
				UWORD SLEWRATEDN;
				UWORD TIME1;
				UWORD TIME2;
				UWORD CENTERVAL;					/*	Go-NoGo Setup						*/
				UWORD HIGHVAL;
				UWORD LOWVAL;
				UWORD HIPCET;
				UWORD LOWPCET;
				char CURRLOC;					/*	Current Item Location								*/
				char T1_RANGE;					/* 	Timer 1 Range 0=TimeBase_1us, 1=TimeBase_1ms		*/
				char T2_RANGE;					/* 	Timer 2 Range 0=TimeBase_1us, 1=TimeBase_1ms		*/
				char SLEWRATEUP_RANGE;			/* 	SLEWRATEUP Range 0=Range1, 1=Range2, 2=Range3	*/
				char SLEWRATEDN_RANGE;			/* 	SLEWRATEDN Range 0=Range1, 1=Range2, 2=Range3	*/
				}dynamatic_str;				/* 	Total 18 Bytes*/

// Mode Setup
typedef struct	{
				char RANGE;						/*	Range 0=Low, 1=Mid, 2=Hi				*/
				char STADYNA;					/*	Range 0=Static, 1=Dynamatic			*/
				}mode_str;

typedef struct	{
				char MACHTYPE;					/* 	Machine Type						*/
												/* 	0:2020AB						*/
												/* 	1:2030A							*/
												/*	2:2040							*/
												/*	3:2041							*/
												/* 	4:2070							*/
												/* 	5:2071							*/
												/*	6:20140							*/
												/*	7:2030B							*/
												/*	100:default							*/
				unsigned char FIRMVER[9];
				char HARD_INIT;					/* 	Bit0=Mode 0						*/
												/* 	Bit1=Mode 1						*/
												/* 	Bit2=Mode 2						*/
												/* 	Bit3=Not Use						*/
												/* 	Bit4=Cal Fail (1:Fail,0:Ok)			*/
												/* 	Bit5=FRAM Fail (1:Fail,0:Ok)			*/
												/* 	Bit6=FPGA Fail (1:Fail,0:Ok)			*/
												/* 	Bit7=Check Sum Fail (1:Fail,0:Ok)	*/
				unsigned short RUN_PROGRAM_CHECK_SUM;
				}slaveinfo;

// Calbration fix point of each mode ( CC / CR / CV )
// The CC & CR mode has three fix point of each "Range ( H/L )". The CV has three fix point.
typedef struct	{
				char MODE;				/* 0:CC,1:CR,2:CV,3:CC+CV,4:OPP,5:Extern CC,6:Extern CV*/
				char RANGE;				/* 0:LOW,1:HI 		*/
				char POINT;				/* 0:LOW,1:HI		*/
				char START;
				unsigned long DMM;		/* DMM input value 4bytes (base on 10000) */
				unsigned long HI_P;
				unsigned long LOW_P;
				}calibration_str;

typedef struct	{
				memdata S_DATA[120];				/*	Sequence Memory 1~120 (All Data of Current Mode)		*/	
				ULONG Duration[120];				/*    0.1ms~6S or 1ms~60s or 10ms~600S or 100ms~6000S or 1s~60000S*/
				UBYTE Cycle_Point;					/* 	Clcle Point 0~119 */ /*A Point*/
				short REPEATCT;						/* 	Run SEQ Repeat Counter 0 ~ 9999		*/
				UBYTE Max_Number;					/* 	Loop_Point 0~119 */ /*B Point*/
				UBYTE Curr_Number;					/* 	Curr_Number 0~119 */
				char MODE;							/*   0:CC_MODE, 1:CR_MODE */
				char RANGE;							/*	Range 0=Low, 1=Hi	*/
				UBYTE SEQ_Flag;						/*   SEQ ON or SEQ OFF*/
				UBYTE End_Status;					/*   End Status 0:OFF 1:ON*/
				char VR_SET;						/*   0:Low, 1:High   VRange set*/
				UBYTE Reserved[6];
				}chan_seq;

typedef struct	{
				memdata P_DATA[10];					/* 	Preset Memory 1~10 (Data of Current Mode)			*/
				memdata M_DATA[120];				/*	Memory 1~120 (All Data of Current Mode)		*/	
				chan_seq SEQ_DATA;
				chan_seq D_SEQ_DATA;
				runprog RUNSEQ;
				slaveinfo INFO;						/*	Slave information ( machine type, FPGA status, Fram status, etc...) */
				UWORD CCH_STEP;
				UWORD CCL_STEP;
				UWORD CRH_STEP;
				UWORD CRL_STEP;
				UWORD CV_STEP;
				}chan_str;
typedef struct	{
				UWORD CCH_STEP;
				UWORD CCL_STEP;
				UWORD CRH_STEP;
				UWORD CRL_STEP;
				UWORD CV_STEP;
				}disp_chan_str;
/*-------------------------------------------- PEL 3K --------------------------------------------------*/
typedef struct	{
				UBYTE MEDIA;			// Recode Media Value  0:Memory  1:USB   2:Default
				UBYTE DESTINATION;		// 
				UWORD MEMORY_ADDR;		// Memory 1 ~ 256 0:All
				UBYTE SMEMORY_ADDR;		// Setup Memory 1~100 0:All
				UBYTE PRE_MEMORY_ADDR;	// Preset Memory 0~9
				UBYTE MEMORY_STATUS;	
				UBYTE USB_ADDR;			// Usb File name  (open keypad function)
				UBYTE USB_STATUS;
				UBYTE SAVE;				// backup
				UBYTE RECALL;			// backup
				UBYTE USB_Data_Type;	/* Media:USB		Save/Recall Date:  0:Memory   1:Setup   2:Preset   3:NSeq	4:FSeq*/
				UBYTE Mem_Data_Type;	/* Media:Memory	Save/Recall Date:  0:Memory   1:Setup   2:Preset  */
				}p3k_file_util_str;

typedef struct	{
				UWORD VALUE1;
				UWORD VALUE2;
				UWORD SLEWRATEUP;
				UWORD SLEWRATEDN;
				UWORD CURRENTLIMIT;
				UWORD Reserved1;				/* 	Not Use				*/
				UWORD Reserved2;				/* 	Not Use				*/
				UWORD CENTERVAL;				/*	Go-NoGo Setup		*/
				UWORD HIGHVAL;
				UWORD LOWVAL;
				UWORD HIPCET;					/* 	Hi Pcet Value							*/
				UWORD LOWPCET;					/* 	Low Pcet Value						*/
				UBYTE Reserved3[2];				/* 	Reserved	 							*/
				UBYTE SLEWRATEUP_RANGE;	//Deleted it		/* 	SLEWRATEUP Range 0=Range1, 1=Range2, 2=Range3	*/
				UBYTE SLEWRATEDN_RANGE;	//Deleted it			/* 	SLEWRATEDN Range 0=Range1, 1=Range2, 2=Range3	*/
				}p3k_static_str;				/* 	Total 28 Bytes						*/

typedef struct	{
				UWORD LEVEL1;
				UWORD LEVEL2;
				UWORD SLEWRATEUP;
				UWORD SLEWRATEDN;
				UWORD TIME1;
				UWORD TIME2;
				UWORD Reserved1;				/* 	Not Use				*/
				UWORD CENTERVAL;				/*	Go-NoGo Setup						*/
				UWORD HIGHVAL;
				UWORD LOWVAL;
				UWORD HIPCET;
				UWORD LOWPCET;	
				UBYTE T1_RANGE;					/* 	Timer 1 Range 0=Range1(25uS~10mS), 1=Range2(11mS~30000mS)		*/
				UBYTE T2_RANGE;					/* 	Timer 2 Range 0=Range1(25uS~10mS), 1=Range2(11mS~30000mS)		*/
				UBYTE SLEWRATEUP_RANGE;	//delet		/* 	SLEWRATEUP Range 0=Range1, 1=Range2, 2=Range3	*/
				UBYTE SLEWRATEDN_RANGE;	//delet			/* 	SLEWRATEDN Range 0=Range1, 1=Range2, 2=Range3	*/
				UWORD Reserved2;
				UWORD Level_Percent;
				UWORD Duty;
				UWORD Frequency;
				UBYTE Frequency_Range;
				UBYTE Reserved3[3];				
				}p3k_dynamatic_str;			/* 	Total 28 Bytes						*/

typedef struct	{
				UBYTE STADYNA;					/*	0=Static, 1=Dynamatic			*/
				UBYTE ABSELECT;					/* 	0 = A Value, 1 = B Value				*/		
				UBYTE RESPONSE;					/*	0=Slow, ,1=Normal,  2=Fast	*/ //for CV,CP
				UBYTE CXCV_RESPOSNE;			/*	0=Slow, 1=Fast	*/ //for CC,CR,CP
				p3k_static_str STA[3];			/*	0 = Low range, 1 = Hi range	*/
				p3k_dynamatic_str DYNA[3];		/*	0 = Low range, 1 = Hi range	*/
				UWORD VALUE_STEP[3];
				UWORD Reserved;					/* 	Reserved								*/
				}p3k_mode_str;					/* 	Total 180 Bytes						*/


typedef struct	{
				UBYTE B_ONOFF;					/* When B_Val is not be use */
				UBYTE BEEP_ONOFF;				/*0:OFF 1:ON*/
				UBYTE KEYKNOB;					/*0:HOLD 1:UPDATA*/
				UBYTE LOADTIME;					/*Load Sync Delay Time*/
				UBYTE Sample_Rate;				/*	00:500K	0000
													01:250K	0001
													02:100K	0010
													03:50K	0011
													04:25K	0100
													05:10K	0101
													06:5K	0110
													07:2.5K	0111
													08:1K	1000
													09:500	1001
													10:250	1010
													11:100	1011
													12:50	1100
													13:25	1101	*/
				UBYTE Acq_Status;				/*	0:busy 1:Finish	*/
				UBYTE Reserved[2];
				ULONG Reserved1[20];
				}p3k_util;	/* 	Total 88 Bytes	*/


typedef struct	{
				UWORD OCP[3];											
				UWORD OPP[3];					/* 	0:Range Low, 1:Range Hi */
				UWORD VON_VOLT[2];				/*	0:VRange Low, 1:VRange Hi */	
				UWORD UVP_VOLT[2];				/*	0:VRange Low, 1:VRange Hi */	
				UWORD OVP_VOLT[2];				/*	0:VRange Low, 1:VRange Hi */
				UBYTE OCP_SET;					/*	1:Limit, 0:Load Off, 2:OFF			*/
				UBYTE OPP_SET;					/*	1:Limit, 0:Load Off	, 2:OFF		*/
				UBYTE VON_LATCH;				/*	0:Off, 1:On 				*/
#if Enable_Ring_Count
				UBYTE Reserved;
				UWORD UVP_Tone_len;
				UWORD SEQ_Tone_len;
				ULONG Reserved2[19];
#else
				UBYTE Reserved;
				ULONG Reserved1[20];
#endif

				}P3k_Prot_Str;			/*Total 108 bytes*/
// only normal load
typedef struct	{
				UBYTE Control;			/*	0:OFF, 1:V, 2:R, 3:Rinv(Inverse)	*/
				UBYTE LoadOn_IN;		/*	0:OFF, 1:LOW, 2:HIGH */  
				UBYTE MultilPara;		/*	0:OFF, 1:Master, 2:Slave */
				UBYTE Reserved[1];
				ULONG Reserved2;
				}P3k_External_Str;		/*Total 8 bytes*/


typedef struct	{
				UBYTE Mode;				/*0:Master, 1:Slave*/
				UBYTE Number;
				
#if 1
				UBYTE TrigOut;
				UBYTE TrigIN; 
				UWORD TrigOutWidth;
				UWORD TrigInDelay;
#else
				UBYTE Booster_Number;	/*0:OFF,1~4(Disp:2~5)*/
				UBYTE Parallel_Number;	/*0:OFF,1~4(Disp:1~4)*/
				ULONG Reserved;
#endif
				}P3k_Parallel_Str;		/*Total 8 bytes*/


typedef struct	{
				UWORD SOFT_START;				/*	OFF~200mS	*/
				UWORD VON_VOLT[2];
				UWORD Cut_Off_Time_h;
				UBYTE VON_LATCH;
				UBYTE Short_Key;
				UBYTE CH_Control;
				UBYTE Count_Time;
				UBYTE Response;					//deleted it.   /*0:1/1, 1:1/2, 2:1/5, 3:1/10,*/
				UBYTE Sample_Rate;
				UBYTE Acq4K_Enable;				/* 0:OFF,	1:ON	*/
				UBYTE Memory_Recall;			/* 0:SAFETY,	1:DIRECT	*/
				UBYTE CV_Func_En;				/* +CV Function Enable 1:ON , 0:OFF*/
				UBYTE Dyna_Level;				/*	0=Value,	1=Percent			*/
				UBYTE Dyna_Time;				/*	0=TH/TL, 1=Feq./Duty			*/
				UBYTE D_CR_Unit;				/*	0=OHM,	1=MHO				*/
				UBYTE Cut_Off_Time_m;
				UBYTE Cut_Off_Time_s;
				UBYTE Cut_Off_cnt;   // 0:h  1:m  2:s  3:total
				UBYTE Cut_Off_Time; //delet it when scpi complant; //
				P3k_Parallel_Str Para_Data;
				P3k_External_Str Ext_Setting;
				UWORD D_Von_Delay;				/* 0~65535(us)	*/
				UWORD Knob_Status;				/* 0:Step 1:Cursor */
				UWORD D_Von_Delay_CR;
				UWORD T_count_up;	
				ULONG cut_off_time_total;				
#if Enable_Short_invalidate
				UBYTE Short_Fun;
				UBYTE Short_Satety;
				UWORD Reserved5;
				ULONG Reserved3[12];
#else
				ULONG Reserved3[13];
#endif

				}P3k_Conf_Str;			/*Total 104 bytes*/

typedef struct	{
				UBYTE MODE; 				/*	0:CC_MODE 1:CR_MODE 2:CV_MODE  3:CP_MODE		*/
				UBYTE STATUS;				/* 	Bit0:+CV Function Enable 1:ON , 0:OFF				*/
											/*	Bit1:Dynamatic On/Off								*/
											/*	Bit2:Go-NoGo On/Off								*/
											/* 	Bit3:Go-NoGo Precent/Value							*/
											/* 	Bit4:0 = A Value, 1 = B Value						*/
											/* 	Bit5:CV_Response Fast/Slow(Only CV Mode)				*/
											/* 	Bit6:Vrange //										*/
											/* 	Bit7:											*/
				UBYTE IRange;				/*	0=Low,	1=High							*/
				UBYTE P_F_Delay;			/*	GONG Delay Time									*/
				UWORD CV_VALUE;
				//UWORD Reserved1;
				UWORD RESPONSE_VALUE;
				UWORD VALUE1;				/*	Static mode = Value1, Dynamic mode = Label1			*/
				UWORD VALUE2;				/* 	Static mode = Value2, Dynamic mode = Label2			*/
				UWORD SLEWRATEUP;
				UWORD SLEWRATEDN;
				UWORD TIME1;				/*	Dynamic Mode Only								*/
				UWORD TIME2;				/*	Dynamic Mode Only 								*/
				UWORD Reserved2;
				UWORD CENTERVAL;			/*	Go-NoGo Function									*/
				UWORD HIGHVAL;
				UWORD LOWVAL;
				UWORD HIPCET;
				UWORD LOWPCET;
				UBYTE T1_RANGE;				/* 	Timer 1 Range 0=Range1, 1=Range2					*/
				UBYTE T2_RANGE;				/* 	Timer 2 Range 0=Range1, 1=Range2					*/
				UBYTE SLEWRATEUP_RANGE;		//deleted it 	/* 	SLEWRATEUP Range 0=Range1, 1=Range2, 2=Range3	*/
				UBYTE SLEWRATEDN_RANGE;		//deleted it 	/* 	SLEWRATEDN Range 0=Range1, 1=Range2, 2=Range3	*/
				}P3k_Memory_Str;	/*	Total 36 Bytes */

typedef struct	{
				UBYTE MACHTYPE;					/* 	Machine Type						*/
												/* 	0:1031B								*/
												/* 	1:			3070							*/
												/*	2:			3111							*/
												/*	4:1033B								*/
												/* 	6:			3020							*/
												/*	7:default							*/
				UBYTE FIRMVER[9];
				UBYTE HARD_INIT;				/* 	Bit0=Mode 0						*/
												/* 	Bit1=Mode 1						*/
												/* 	Bit2=Mode 2						*/
												/* 	Bit3=Not Use						*/
												/* 	Bit4=Cal Fail (1:Fail,0:Ok)			*/
												/* 	Bit5=FRAM Fail (1:Fail,0:Ok)			*/
												/* 	Bit6=FPGA Fail (1:Fail,0:Ok)			*/
												/* 	Bit7=Check Sum Fail (1:Fail,0:Ok)	*/
				UBYTE Reserved;
				UWORD RUN_PROGRAM_CHECK_SUM;
				UWORD Reserved1;
				}p3k_MachineInfo;/*	Total 16 Bytes */

typedef struct	{
				UWORD VOLT;						/*	Measure Voltage of Slave	*/
				UWORD CURR;						/*	Measure Current of Slave	*/
				UWORD MEAS_REF;					/* 	Measure Reference of Slave  */
				UWORD KNOB_VAL;					/*	Knob Value of Slave		*/
				UBYTE MEAS_STATUS;
				UBYTE SLAVE_STATUS;
				UBYTE Reserved[2];
				}p3k_meas_str;				/*	Total 12 Bytes */

typedef struct	{
				UBYTE CURRMODE;						/* 	0:P_CC 1:P_CR 2:P_CV  3:P_CP				*/			
				UBYTE SPEC;							/* 	Range 0=Go-NoGo Off, 1=Go-NoGo On		*/
				UBYTE SPECTYPE;						/*	Range 0=Value, 1=Percent					*/
				UBYTE P_F_Delay;
				UBYTE Coarse;						/*	0:Fine, 1:Coarse							*/
				UBYTE Parallel_Unit;
				UBYTE IRange;						/*	0=Low,	1=High					*/
				UBYTE VRange;						/*	0=Low,	1=High							*/
				UBYTE Load_Type;					/*	0=Norm,	1=Prog,	2=NSeq,  3=FSeq			*/
				UBYTE Reserved[3];
				WORD Reserved2[2];
				p3k_mode_str CC;
				p3k_mode_str CR;
				p3k_mode_str CV;
				p3k_mode_str CP;
				p3k_util UTILITY;
				P3k_Prot_Str PROT;				/* 	Protection status and level value 				*/
				P3k_Conf_Str CONF;
				P3k_Memory_Str P_DATA[10];				/* 	Preset Memory 1~10 (Data of Current Mode)	*/
				p3k_MachineInfo INFO;						/*	Slave information ( machine type, FPGA status, Fram status, etc...) */
				}P3k_Backup_Str;	  /* Total 1556 Bytes */

typedef struct	{
				UBYTE CURRMODE;					/* 	0:P_CC 1:P_CR 2:P_CV  3:P_CP				*/			
				UBYTE SPEC;						/* 	SPEC Test ON(1)/OFF(0)					*/
				UBYTE SPECTYPE;					/*	Entry Mode	0=Value, 1=Percent			*/
				UBYTE P_F_Delay;
				UBYTE Coarse;					/*	0:Fine, 1:Coarse							*/
				UBYTE Parallel_Unit;
				UBYTE IRange;					/*	0=Low,	1=High					*/
				UBYTE VRange;					/*	0=Low,	1=High							*/
				UBYTE Load_Type;				/*	0=Norm,	1=Prog,	2=NSeq,  3=FSeq			*/
				UBYTE Reserved[3];
				WORD Reserved2[2];
				p3k_mode_str CC;
				p3k_mode_str CR;				/* 	Not support Dynamic Mode 					*/
				p3k_mode_str CV;				/*	Not support Dynamic Mode and No Hi Range	*/
				p3k_mode_str CP;				/*	Not support Dynamic Mode and No Hi Range	*/
				p3k_util UTILITY;
				P3k_Prot_Str PROT;		/* 	Protection status and level value 				*/
				P3k_Conf_Str CONF;
				P3k_Memory_Str P_DATA[10];			/* 	Preset Memory 1~10 (Data of Current Mode)	*/
				P3k_Memory_Str M_DATA[256];		/*	Memory 1~256 (All Data of Current Mode)		*/	
				p3k_MachineInfo INFO;				/*	Slave information ( machine type, FPGA status, Fram status, etc...) */
				p3k_meas_str MEAS;
				}P3k_Data_Str;			/* Total 10928 Bytes */

typedef struct	{
				UBYTE CURRMODE;					/* 	0:P_CC 1:P_CR 2:P_CV  3:P_CP				*/			
				UBYTE SPEC;						/* 	Range 0=Go-NoGo Off, 1=Go-NoGo On		*/
				UBYTE SPECTYPE;					/*	Range 0=Value, 1=Percent					*/
				UBYTE P_F_Delay;
				UBYTE Coarse;					/*	0:Fine, 1:Coarse							*/
				UBYTE Parallel_Unit;
				UBYTE IRange;					/*	0=Low,	1=High					*/
				UBYTE VRange;					/*	0=Low,	1=High							*/
				UBYTE Load_Type;				/*	0=Norm,	1=Prog,	2=NSeq,  3=FSeq			*/
				UBYTE Reserved[3];
				WORD Reserved2[2];
				p3k_mode_str CC;
				p3k_mode_str CR;				
				p3k_mode_str CV;				/*	Not support Dynamic Mode	*/
				p3k_mode_str CP;				/*	Not support Dynamic Mode 	*/
				p3k_util UTILITY;
				P3k_Prot_Str PROT;		/* 	Protection status and level value 				*/
				P3k_Conf_Str CONF;
				}P3k_Disp_Str;			/* Total 1036 Bytes */

typedef struct	{
				float VOLT;						/*	Measure Voltage of Slave	*/
				float CURR;						/*	Measure Current of Slave	*/
				float WATT;						/* 	Measure Reference of Slave  */
				UBYTE Sec;
				UBYTE Min;
				UWORD Hour;
				UBYTE Go_NoGo;					/*   0:NULL  1:NO GO  2:GO*/
				UBYTE Alarm;					/*	0:No Alarm
													1:OTP  
													2:RVP
													3:OVP
													4:UVP
													5:Para
													6:OPP	
													7:OCP
													8:CPP
													9:R.OCP
													10:FCCP
													11:UnReg
													12:Ext.
													*/
				double Real_Volt;
				double Real_Curr;
				UWORD Raw_Volt;
				UWORD Raw_Curr;
				float Ext_Percent;
				}p3k_meas_data;				/*	Total 20 Bytes */

typedef struct	{
				float VOLT[4096];				/*	Measure Voltage of Slave	*/
				float CURR[4096];				/*	Measure Current of Slave	*/
				float WATT[4096];				/* 	Measure Reference of Slave  */
				UWORD Acq4K_Interval;			/*Acquire 4K Point System Sampling Interval(2~60000uS)*/
				UWORD Acq4K_PTC;				/*Acquire 4K Point System Pre-Trigger Counter	(PTC+SWC=0~4095)	*/
				UWORD Acq4K_SWC;				/*Acquire 4K Point System Sweep Counter		(PTC+SWC=0~4095)	*/
				UWORD Reserved1;
				UBYTE Acq4K_Enable;			/*0:OFF, 1:ON*/
				UBYTE Acq4K_Ready;			/*0:OFF, 1:ON*/
				UBYTE Reserved2[2];
				double CC_Resolution;
				double CV_Resolution;
				}p3k_Acq4K_Data_Str;		/*	Total 49180 Bytes */

typedef struct	{
				UWORD XL_Value;
				UWORD YL_Value;
				UWORD ZL_Value;
				UWORD XH_Value;
				UWORD YH_Value;
				UWORD ZH_Value;
				ULONG Reserved[3];
				}PSensor_Str;		/*	Total 24 Bytes */


typedef struct	{
				UBYTE MODE;				/*	0:CC			1:CR			2:CV		3:CP		4:CX CV		5.Front_IMON		6.Rear_IMON	*/
				UBYTE RANGE;			/*	0:LOW		1:HI						*/
				UBYTE POINT;			/*	0:High Point	1:Low Point							*/
				UBYTE START;	
				UBYTE PSense;
				UBYTE Cal_PSense_Flag;
				UBYTE Volt_Curr_Sel;	/*	0:Volt		1:Curr						*/
				UBYTE Reserved;
				UWORD Set_Value_High;
				UWORD Set_Value_Low;
				UWORD Monitor_High;
				UWORD Monitor_Low;
				UWORD CxCV;
				UWORD OCP_High_Point;
				UWORD OCP_Low_Point;
				UWORD OPP_High_Point;
				UWORD OPP_Low_Point;
				UWORD CPP_High_Point;
				UWORD CPP_Low_Point;
				UWORD Rating_OCP_High_Point; //delet
				UWORD Rating_OCP_Low_Point; //delet
				UWORD CxCV_High_Point;
				UWORD CxCV_Low_Point;
				UWORD Reserved1;
				double OPP_Gain;
				double OPP_Offset;
				double OCP_Gain;
				double OCP_Offset;
				double CPP_Gain;
				double CPP_Offset;
				double Rating_OCP_Gain; //delet
				double Rating_OCP_Offset; //delet
				double CxCV_Gain;
				double CxCV_Offset;
				double HP_Volt;
				double HP_Curr;
				double LP_Volt;
				double LP_Curr;
				double Cal_Value_Gain;
				double Cal_Value_Offset;
				PSensor_Str PSensor;
				}p3k_calibration_str;/*	Total 88 Bytes */

typedef struct	{
				double Cal_Value_Gain;
				double Cal_Value_Offset;
				}Cal_Data_str;			/*	Total 16 Bytes */

typedef struct	{
				UWORD Meas_Value_Gain;
				UWORD Meas_Value_Offset;
				}p3k_Meas_cal_Data_str;			/*	Total 4 Bytes */

typedef struct	{
				UWORD CPP;
				UWORD OPP;
				UWORD OCP;
				UWORD Rating_OCP; //delet
				UWORD CxCV;
				UWORD Reserved;
				double OPP_Gain;
				double OPP_Offset;
				double OCP_Gain;
				double OCP_Offset;	
				double Rating_OCP_Gain; //delet
				double Rating_OCP_Offset; //delet
				double CPP_Gain;
				double CPP_Offset;
				double CxCV_Gain;
				double CxCV_Offset;	
				ULONG Reserved1[20];
				}p3k_Prot_cal_Data_str;		/*	Total 172 Bytes */

typedef struct	{
				ULONG CheckSum;
				UBYTE Data_Ready;		/*when Data_Ready=200 =>Valid Data,when Data_Ready!=200 =>Invalid Data*/
				UBYTE Reserved1[3];
				ULONG Reserved2[3];
				Cal_Data_str CC_Data[3];				/* 016*003=048 Byte*/
				Cal_Data_str CR_Data[3];				/* 016*003=048 Byte*/
				Cal_Data_str CV_Data[3];				/* 016*003=048 Byte*/
				Cal_Data_str CP_Data[3];				/* 016*003=048 Byte*/
				p3k_Meas_cal_Data_str Curr[3];			/* 004*003=012 Byte*/
				p3k_Meas_cal_Data_str Volt[2];			/* 004*002=008 Byte*/
				PSensor_Str PSensor;					/* 024*001=024 Byte*/
				p3k_Prot_cal_Data_str Protection[3];	/* 172*003=516 Byte*/
				UBYTE Front_IMON[3]; //delet
				UBYTE Rear_IMON[3];
				UBYTE Reserved4[2];
				UWORD Ext_V_CC[3];						/* 002*003=006 Byte*/
				UWORD Ext_R_CC[3];						/* 002*003=006 Byte*/
				p3k_Meas_cal_Data_str Ext_V_Sense;		/* 004*001=004 Byte*/
				p3k_Meas_cal_Data_str Ext_R_Sense;		/* 004*001=004 Byte*/
				UWORD OffsetAdjCnt1;					/* 002*001=002 Byte*/
				UWORD OffsetFlag;						/* 002*001=002 Byte*/  // bit0: company offsetAdj, bit: display adj or H & L range
				UWORD CC_offseAdj[3];					/* 002*003=006 Byte*/
				UWORD CR_offseAdj[3];					/* 002*003=006 Byte*/
				UWORD CV_offseAdj[3];					/* 002*003=006 Byte*/
				UWORD CP_offseAdj[3];					/* 002*003=006 Byte*/
				UWORD Cal_complete;
#if Enable_Ext_CalOffset
				UWORD Reserved5;
				UWORD Ext_V_offseAdj[3];					/* 002*003=006 Byte*/
				UWORD Ext_R_offseAdj[3];					/* 002*003=006 Byte*/
				p3k_Meas_cal_Data_str Ext_V_Curr[2];		/* 004*002=008 Byte*/
				p3k_Meas_cal_Data_str Ext_V_Volt[2];		/* 004*002=008 Byte*/
				p3k_Meas_cal_Data_str Ext_R_Curr[2];		/* 004*002=008 Byte*/
				p3k_Meas_cal_Data_str Ext_R_Volt[2];		/* 004*002=008 Byte*/


				ULONG Ext_V_CR[3];							/* 004*003=012 Byte*/
				ULONG Ext_R_CR[3];							/* 004*003=012 Byte*/				
				UWORD Ext_V_CV[3];							/* 002*003=006 Byte*/
				UWORD Ext_R_CV[3];							/* 002*003=006 Byte*/
				UWORD Ext_V_CP[3];							/* 002*003=006 Byte*/
				UWORD Ext_R_CP[3];							/* 002*003=006 Byte*/
				
				ULONG Reserved3[25];//ULONG Reserved3[37]; 					/*168 Byte  Remaining 204 WORD Free Space	*/
#else
				UWORD Reserved5;
				ULONG Reserved3[48]; 					/*168 Byte  Remaining 204 WORD Free Space	*/
#endif
				}p3k_cal_Data_str;					/*	Total 1000 Bytes */

typedef struct	{	
				UBYTE MEMORY[16];						/* Memory mapping number 						*/
				UBYTE RUNMODE[16];						/* Step Run Mode 0:Skip, 1:Auto, 2:Manual		*/
				UWORD ONTIME[16];						/* Load On Time 								*/
				UWORD OFFTIME[16];						/* Load Off Time								*/
				UWORD PFTIME[16];						/* Pass & Fail Time 							*/
				UWORD SHORTTIME[16];					/* Short Time									*/	
				//}__attribute__ ((packed, aligned(4)))P3k_Timing_Str;					/*	Total 160 Bytes */
				}P3k_Timing_Str;					/*	Total 160 Bytes */

//#pragma pack(1)
typedef struct	{
				UBYTE Prog_No;					/* 	Progam  0~15						*/
				UBYTE Step_No;					/*	Step No  0~15					*/
				UBYTE SPEC;						/*	Run Program 0=Off, 1=On			*/
				UBYTE Chain_Start_Prog;			/*									*/
				UBYTE PROGSEQ[16];
				UBYTE Reserved[4];
				UWORD REPEATCT;					/* 	Run Prog Repeat Counter 1 ~ 9999	*/
				UWORD Reserved2;
				P3k_Timing_Str Timing_Data[16];	/*	Total 2560 Bytes					*/
				}P3k_Prog_Str;					/*	Total 2584 Bytes					*/
				//}__attribute__ ((packed, aligned(4)))P3k_Prog_Str;					/*	Total 2584 Bytes */	
//#pragma pack()



//#pragma pack(1)

typedef struct	{
		//UBYTE t1;
		UBYTE Prog_No;					/*	Progam	0~15						*/
		UBYTE Step_No;					/*	Step No  0~15					*/	
		//UBYTE REPEATCT;
		UWORD REPEATCT; 				/*	Run Prog Repeat Counter 1 ~ 9999	*/	
		//UBYTE t2;	
		}P3k_test;


//#pragma pack()


typedef struct	{
				/*Setting*/
				UWORD Hour;			/*0~999*/
				UWORD MilliSecond;	/*0~999*/
				UBYTE Minute;		/*0~59*/
				UBYTE Second;		/*0~59*/
				UBYTE Reserved2[2];
				}P3k_Time_Str;		/* Total 8 Bytes */

typedef struct	{
				UBYTE SEQ_Mode;			/* 0:CC,1:CR,2:CV,3:CP		*/
				UBYTE SEQ_Range;		/* 0:ILVL,1:IHVL,2:ILVH,3:IHVH	*/
				UBYTE Reserved[2];
				UWORD Level_Step;		/*	Seq Load Value(Step)		*/
				UWORD Level_Setting;	/*	Seq Load Value(Count)		*/
				UWORD SR_Setting;		/*	Slaw Rate 				*/
				UWORD CS0_Setting;		/*	Circuit Switch Control 0		*/
				UWORD CS1_Setting;		/*	Circuit Switch Control 1		*/
				UWORD Duration_Setting;	/*	Duration Time Setting		*/
				UWORD Ramp_Delta_VH;	/*	Ramp Delta VH			*/
				UWORD Ramp_Delta_VL;	/*	Ramp Delta VL			*/
				UWORD Ramp_Delta_T;		/*	Ramp Delta Time			*/
				UWORD Reserved1;
				P3k_Time_Str SEQ_Time;
				}P3k_FPGA_Seq_Str;		/*	Total 20 Bytes		*/

typedef struct	{
				UWORD Jump_Address;
				UWORD Jump_Number;
				UWORD Ramp_Delta_VH;	/*	Ramp Delta VH			*/
				UWORD Ramp_Delta_VL;	/*	Ramp Delta VL			*/
				UWORD Ramp_Delta_T;		/*	Ramp Delta Time			*/
				UWORD Ramp_SlewRate;
				UWORD Ramp_CS1;
				}P3k_FPGA_Jump_Str;	/*	Total 10 Bytes		*/

typedef struct	{
				UWORD Prog_No;				/* 0~15,Now Run Program number 1~16 or 0~9,     Now Run Seq number  1~10	*/
				UWORD Step_No;				/* 0~15,Now Run Step number 1~16      or 0~1023,Now Run Step number 1~1024*/
				UWORD Mem_NO;				/* Memory Index 1~256				*/
				UWORD SPEC_Result;			/* SPEC Result 0:NULL  1:NO GO  2:GO	*/
				UWORD SPEC_Result_Backup;
				UWORD PFTIME;				/* Pass & Fail Time 0.1~119.9S			*/
				UWORD Loop_Address;
				}P3k_Prog_Disp_Str;		/*	Total 12 Bytes		*/
typedef struct	{
				ULONG CheckSum;
				UBYTE Data_Ready;			/*when Data_Ready=200 =>Valid Data,when Data_Ready!=200 =>Invalid Data*/
				UBYTE MACHTYPE;				/* 	Machine Type						*/
											/* 	0:1031							*/
											/* 	1:3070							*/
											/*	2:3111							*/
											/*	4:1033							*/
											/* 	6:3020							*/
											/*	7:default							*/
				UBYTE F_Version;			/*	File Version						*/
				UBYTE M_Number;				/*	Machine Number					*/
				UBYTE M_Version_M;			/*	Machine Version(Main)				*/
				UBYTE M_Version_S;			/*	Machine Version(subsidiary)			*/
				UBYTE Reserved1[2];
				ULONG Reserved2[2];
				P3k_Memory_Str M_DATA[256];	/* 36 Byte * 256 = 9216 Byte					*/
				P3k_Prog_Str Chan_PROG;		/* 2588 Byte							*/
				ULONG Reserved3[761];		/* 761 * 4 Byte = 3044 Bytes 	*/
			  	}P3k_Backup_Prog_Str;		/*	Total 14848 Bytes(14848/512=29 Page)	*/
typedef struct	{
				/*Setting*/
				UWORD NSeq_Value;
				UWORD Reserved;
				P3k_Time_Str NSeq_Time;
				UBYTE Load_Setting;
				UBYTE Ramp_Setting;
				UBYTE TrigOut_Setting;
				UBYTE Pause_Setting;
				}NSeq_Data_Str;	/* Total 16 Bytes */

typedef struct	{
				/*Setting*/
				UWORD FSeq_Value;
				UWORD Reserved;
				UBYTE TrigOut_Setting;
				UBYTE Reserved2[3];
				}FSeq_Data_Str;	/* Total 8 Bytes */

typedef struct	{
				/*Setting*/
				UBYTE FSeq_Memo[28];
				UBYTE FSeq_Mode;		/* 0:CC,1:CR				*/
				UBYTE FSeq_Range;		/* 0:ILVL,1:IHVL,2:ILVH,3:IHVH	*/
				UBYTE FSeq_Last_Load;	/* 0:OFF,1:ON			*/
				UBYTE FSeq_TB_Range;	/* 0:us, 1:10us*/
				UWORD FSeq_Loop;		/* 0:Infinity,0001~9999	*/
				UWORD FSeq_Last_Level;
				UWORD FSeq_Max_Step;	/*2~1000*/ 
				UWORD FSeq_Curr_Step;	/*0~1000*/
				UWORD Fill_Start_Step;
				UWORD Fill_Start_Value;
				UWORD Fill_End_Step;
				UWORD Fill_End_Value;
				ULONG FSeq_Time_Base;	/*0.010mS~60000ms*/
				FSeq_Data_Str FSeq_Step[1024];
				UWORD RPTStep;
				UWORD Reserved;
				}FSeq_Timing_Str;	/* Total 8244 Bytes */

typedef struct	{
				ULONG CheckSum;
				UBYTE Data_Ready;			/*when Data_Ready=200 =>Valid Data,when Data_Ready!=200 =>Invalid Data*/
				UBYTE MACHTYPE;				/* 	Machine Type						*/
											/* 	0:1031							*/
											/* 	1:3070							*/
											/*	2:3111							*/
											/*	4:1033							*/
											/* 	6:3020							*/
											/*	7:default							*/
				UBYTE F_Version;			/*	File Version						*/
				UBYTE M_Number;				/*	Machine Number					*/
				UBYTE M_Version_M;			/*	Machine Version(Main)				*/
				UBYTE M_Version_S;			/*	Machine Version(subsidiary)			*/
				UBYTE Reserved1[2];
				ULONG Reserved2[2];
				FSeq_Timing_Str FSeq_Data; 	/*	8244 Byte */
				ULONG Reserved5[365];		/*	366 * 4 Byte = 1464 Bytes 	*/
			  	}P3k_Backup_FSeq_Str;		/*	8244 + 1464 + 20 = 9728 Byte (9728 /512 =19 Page)	*/


typedef struct	{
				/*Setting*/
				UBYTE NSeq_Memo[28];
				UBYTE NSeq_Mode;		/* 0:CC,1:CR,2:CV,3:CP		*/
				UBYTE NSeq_Range;		/* 0:ILVL,1:IHVL,2:ILVH,3:IHVH	*/
				UBYTE NSeq_Last_Load;	/* 0:OFF,1:ON			*/
				UBYTE NSeq_Chain;		/* 0:OFF,01~10(S01~S10)	*/
				UWORD NSeq_Loop;		/* 0:Infinity,0001~9999	*/
				UWORD NSeq_Last_Level;
				UWORD NSeq_Max_Step;
				UWORD NSeq_Curr_Step;
				}NSeq_Timing_Str;	/* Total 40 Bytes */

typedef struct	{
				/*Setting*/
				UBYTE NSeq_Enable;		/* 0:OFF,1:ON	*/
				UBYTE NSeq_Number;		/* 0~9(S01~S10)	*/
				UBYTE NSeq_Start;		/* 0~9(S01~S10)	*/
				UBYTE Reserved;
				NSeq_Timing_Str NSeq_Seq[10];
				NSeq_Data_Str NSeq_Step[10][1025];
				}P3k_NSeq_Str;			/* Total 164260 Bytes */

typedef struct	{
				ULONG CheckSum;
				UBYTE Data_Ready;			/*when Data_Ready=200 =>Valid Data,when Data_Ready!=200 =>Invalid Data*/
				UBYTE MACHTYPE;				/* 	Machine Type						*/
											/* 	0:1031							*/
											/* 	1:3070							*/
											/*	2:3111							*/
											/*	4:1033							*/
											/* 	6:3020							*/
											/*	7:default							*/
				UBYTE F_Version;			/*	File Version						*/
				UBYTE M_Number;				/*	Machine Number					*/
				UBYTE M_Version_M;			/*	Machine Version(Main)				*/
				UBYTE M_Version_S;			/*	Machine Version(subsidiary)			*/
				UBYTE Reserved1[2];
				ULONG Reserved2[2];
				UBYTE NSeq_Enable;			/* 0:OFF,1:ON	*/
				UBYTE NSeq_Number;			/* 0~9(S01~S10)	*/
				UBYTE NSeq_Start;			/* 0~9(S01~S10)	*/
				UBYTE Reserved3;
				NSeq_Timing_Str NSeq_Seq[10]; 	/* 40 Byte * 10 = 400 Byte*/
				NSeq_Data_Str NSeq_Step[1024]; 	/* 16 Byte * 1024 = 16384Byte*/
				ULONG Reserved5[790];			/* 790 * 4 Byte = 3160 Bytes 	*/
			  	}P3k_Backup_NSeq_Str;		/*	24 + 400 + 16384 + 3160 = 19968 Bytes(19968/512=39 Page)	*/

typedef struct	{
				/*Setting*/
				UWORD Start_Address;					/*	0~1023								*/
				UWORD Setting_Count;					/*	0~1023								*/
				P3k_FPGA_Seq_Str FPGA_Seq_Data[1025];	/*	0~1023:User Setting Seq,	1024:Last Seq	*/
				P3k_FPGA_Jump_Str P3k_FPGA_Jump_Data[16];
				UWORD Jump_Count; 
				UBYTE MANUAL_CTRL;						/* 0:Auto, 1:Manual */
				UBYTE SEQ_Stop_Continue;				/* 0:Stop, 1:Continue,	2:No Display*/
				UBYTE SEQ_Complete;						/* 0:Run Sequence,	1:Run Sequence Complete*/
				UBYTE Last_Load_Setting;						/* 0:Run Sequence,	1:Run Sequence Complete*/

				/*Display*/
				UWORD Total_Count;					/* Display counter 1~256(Prog) or 1~1024(Seq)  0:No Prog		*/
				UWORD Display_Count;				/* Receive Display Step(ON+OFF+SHORT Time) Count From FPGA 	*/
				UWORD D_Loop_Count;					/* Display counter 0~255(Prog) or 0~1023(Seq) ,2000:No Loop	*/
				UWORD FPGA_Loop_Count[16];
				P3k_Prog_Disp_Str Prog_Disp_Data[1025] ;
				}P3k_Prog_Seq_Str;

typedef struct	{
				UWORD CHANNO;
				UWORD MODE;
				UBYTE ADDRH;
				UBYTE ADDRL;
				}p3k_send_tx_list;

typedef struct	{
				UBYTE ISR_Flag;			/*	0:No Event,	1:ISR Event			*/
				UBYTE ISR_Range;		/*	0=Low,		1=Mid,		2=High	*/
				UBYTE ISR_Load;			/*	0:OFF,		1:ON	*/	/*Load Status(Master) or Parallel enable(Master)*/
				UBYTE Para_Enable;		/*	0:OFF,		1:ON	*/
				}FPGA_ISR_Str;

typedef struct	{
				UWORD Delta_Value_Low;
				UWORD Delta_Value_High;
				UWORD DeltaTime;
				UWORD Delta_TimeBase;
				UWORD Delta_SR_Set;
				UWORD Delta_SR_Base;
				UWORD Delta_Response;
				}p3k_Ramp_Str;

typedef struct	{
				UBYTE CURRMODE;					/* 	0:P_CC 1:P_CR 2:P_CV  3:P_CP				*/
				UBYTE SPEC;						/* 	SPEC Test ON(1)/OFF(0)					*/
				UBYTE SPECTYPE;					/*	Entry Mode	0=Value, 1=Percent			*/
				UBYTE P_F_Delay;
				UBYTE Coarse;					/*	0:Fine, 1:Coarse							*/
				UBYTE Parallel_Unit;
				UBYTE IRange;					/*	0=Low,	1=Mid,	2=High					*/
				UBYTE VRange;					/*	0=Low,	1=High							*/
				UBYTE Load_Type;				/*	0=Norm,	1=Prog,	2=NSeq,  3=FSeq			*/
				UBYTE Reserved[3];
				WORD Reserved2[2];
				p3k_mode_str CC;
				p3k_mode_str CR;				/* 	Not support Dynamic Mode 					*/
				p3k_mode_str CV;				/*	Not support Dynamic Mode and No Hi Range	*/
				p3k_mode_str CP;				/*	Not support Dynamic Mode and No Hi Range	*/
				p3k_util UTILITY;
				P3k_Prot_Str PROT;				/* 	Protection status and level value 				*/
				P3k_Conf_Str CONF;
				p3k_MachineInfo INFO;				/*	Slave information ( machine type, FPGA status, Fram status, etc...) */
				p3k_meas_str MEAS;
				}P3k_Default_Chan_Str; /* 	Total 1064 Bytes						*/

typedef struct	{
				char Product_Serial_Number[20];
				UBYTE Version;			/*	0 = GW, 1=TEXIO	*/
				UBYTE version_flag;
				UBYTE Reserved[2];
				}Serial_Number_Str;		/*Total 12 bytes.*/

#if Enable_Battery_Discharge
typedef struct	{
		UBYTE status; //0:Loadoff, 1:Loadon run, 2:loadon:finish
		UBYTE timeCnt;
		UBYTE checksum;
		UBYTE stopStatus; //2:timeout, 3:overAmperHour, 4:underVoltange, 5:loadoff
		UBYTE Mode;		/*CC/CR/CP*/  //no cv mode
		UBYTE Range;	/*ILVL/IHVL/ILVH/IHVH */
		UBYTE SRUPRange;	/**/
		UBYTE SRDWRange;	/**/
		UWORD SRUP;		/*only CC,CR*/
		UWORD SRDW;		/*only CC,CR*/
		UWORD Setting;	/*SettingValue (Step)*/
		UWORD StopValt;	/*StopValt Codition (Step:0.01V~600V) */

		UWORD StopHour; /*Stop Codition 0~999*/
		UBYTE StopMin; /*Stop Codition 0~59*/
		UBYTE StopSec; /*Stop Codition 0~59*/
		ULONG StopTime; /* Stop Codition 1000hours */

		ULONG StopCapa; /*Stop Capa 0.00~99999.9 */
		
		ULONG AmpereHour; /*Stop Capa 0.1~99999.9 */  //     /1000/3600
		ULONG WattHour; /*Stop Capa 0.1~99999.9 */	//	/1000/3600


	} P3k_BATT_Str;    //36 bytes

#endif
#if Enable_Battery_Discharge //Enable_LED_function
	
typedef struct	{
				UBYTE name[16];		/*	*/

				UBYTE range;		/*	ILVL,IHVL,ILVH,IHVH 	 	*/
				UBYTE mode;			/*	Vo,Io / Vo,Io,Rcoff / Vo,Io,Rd / Vo,Io,Vd / Vd,Rd,pcs	*/	
				UBYTE response;		/*	0=Slow, ,1=Normal,  2=Fast	*/
				UBYTE reserved;		/*	*/	

				UWORD vo;			/*step*/
				UWORD vf;			/*step*/

				UWORD io;			/*step*/
				UWORD rd;			/*step*/

				UWORD rdcoff;		/*step*/ //1~10000
				UWORD pcs;			/*step*/ 

				UWORD vfCnt;		/*step*/ //vf * measureGain (3031:0.8, 3032:1.1)
				UWORD rdCnt;		/*step*/ //(vo-vf)/set2maureGain/Io(DA cnt)

				double ir;
				double c;
				ULONG reserved2[2];
	
} F_LED_Str;    //60    52  bytes


typedef struct	{
				UBYTE currTemp;			/**/
				UBYTE dataReady;
				UBYTE complete; //0:Initial,  
				UBYTE checksum;
				UWORD specTest; //off/on 
				UWORD delayTime;
				UWORD vHigh;
				UWORD vLow;
				UWORD iHigh;
				UWORD iLow;
				UWORD reserverd[2];
				F_LED_Str seq[12];
	
} P3k_LED_Str;    //740   628 bytes




#endif


typedef struct	{
				ULONG CheckSum;
				UBYTE Backup_Data_Ready;	/*when Data_Ready=200 =>Valid Data,when Data_Ready!=200 =>Invalid Data*/
				UBYTE Serial_Number_Ready;	/*when Data_Ready=200 =>Valid Data,when Data_Ready!=200 =>Invalid Data*/
				UBYTE Reserved[2];
				Serial_Number_Str	Serial_Number;
				ULONG Reserved1[120];
				}P3k_Backup_SN_Str;	/*	Total 512 Bytes(1 Page)	*/

typedef struct	{
				ULONG CheckSum;
				UBYTE Backup_Data_Ready;	/*when Data_Ready=200 =>Valid Data,when Data_Ready!=200 =>Invalid Data*/
				UBYTE Def_Data_Ready;		/*when Data_Ready=200 =>Valid Data,when Data_Ready!=200 =>Invalid Data*/
				UBYTE Reserved1[2];
				ULONG Reserved2[3];
				P3k_Default_Chan_Str P3k_Default_Data;
				utility UTILITY;		/*60 Byte*/
				extdgio EXT_DGIO;		/*8   Byte*/
				rs_232 RS232;			/*8   Byte*/
				gpibpar GPIBPAR;		/*8   Byte*/
				ULONG Reserved3[824];
				}Backup_Default_Str;	/*	Total 4608 Bytes(4608/512=9 Page)	*/

typedef struct	{
				ULONG 			CheckSum;
				UBYTE 			Data_Ready;		/*	when Data_Ready=200 =>Valid Data,when Data_Ready!=200 =>Invalid Data*/
				UBYTE 			MACHTYPE; 		/*	Machine Type						*/
												/*	0:1031							*/
												/*	1:3070							*/
												/*	2:3111							*/
												/*	4:1033							*/
												/*	6:3020							*/
												/*	7:default							*/
				UBYTE 			F_Version;		/*	File Version						*/
				UBYTE 			M_Number; 		/*	Machine Number					*/
				UBYTE 			M_Version_M;	/*	Machine Version(Main)				*/
				UBYTE			M_Version_S;	/*	Machine Version(subsidiary) 			*/

				UBYTE			DispMode;
				UBYTE			M_num;
				UBYTE			DispScrCT;
				UBYTE			Reserved[3];
				P3k_Backup_Str	P3k_Backup_Data;	/* Total	1556 Bytes.*/
				ULONG 			Reserved1[119];
				}Backup_Setup_Str;					/* Total 	2048 Bytes */


typedef struct	{
				ULONG CheckSum;
				UBYTE Data_Ready;			/*when Data_Ready=200 =>Valid Data,when Data_Ready!=200 =>Invalid Data*/
				UBYTE MACHTYPE;				/* 	Machine Type						*/
											/* 	0:1031							*/
											/* 	1:3070							*/
											/*	2:3111							*/
											/*	4:1033							*/
											/* 	6:3020							*/
											/*	7:default							*/
				UBYTE F_Version;			/*	File Version						*/
				UBYTE M_Number;				/*	Machine Number					*/
				UBYTE M_Version_M;			/*	Machine Version(Main)				*/
				UBYTE M_Version_S;			/*	Machine Version(subsidiary)			*/
				UBYTE Reserved1[2];
				ULONG Reserved2[2];
				P3k_Memory_Str P_DATA[10];	/* 	Preset Memory 1~10 (Data of Current Mode)	*/
				}Backup_Preset_Str;			/*	Total 380 Bytes	*/

/************************************************************************************/
/*																					*/
/*	Default & Max & Min & Resolution Setting												*/
/*	For CC / CR / CV / CC Spec / CR Spec / CV Spec										*/
/*	All value was always use " Step * Resolution " to calculate real value 						*/
/*																					*/
/************************************************************************************/

typedef struct	{
				UWORD Def;			/* Default Setting */
				UWORD Max;			
				UWORD Min;
				double Resolution;
				BYTE *Unit;					/* mA/S, A, %, V */
				BYTE precision;				/* mA/S, A, %, V */
				}default_str;

typedef struct	{
				float Current;			
				float Resistance;	
				float Power;
				}Parallel_Default_str;

typedef struct	{
				double Magnification;			
				}Parallel_Compensation_DA_str;


typedef struct	{		/* Model Type of Machine */
				default_str *CC;
				default_str *CR;
				default_str *CV;
				default_str *CP;
				default_str *CC_SPEC;
				default_str *CR_SPEC;
				default_str *CV_SPEC;
				default_str *CP_SPEC;
				default_str *CONF;
				default_str *PROT;
				default_str *CALI_HP;
				default_str *CALI_LP;
				default_str *CALI_PowSet_V;
				default_str *CALI_PowSet_C;
				Parallel_Default_str *IRange_Display;
				Parallel_Compensation_DA_str *Compasation_DA_Magnification;
				}type_default;
/******************************************************************************
*Timer setting
******************************************************************************/
typedef struct	{ 
				char DATESEL;//0:year  1:month  2:day
				char TIMESEL;//0:hour  1:minute
				WORD YEAR; 
				char MONTH;
				char _DAY;
				char _HOUR;
				char _MINUTE;
				char _SECOND;
				char Reserved1;
				WORD Reserved2;
				}timer_set; /*Total 12 bytes.*/

#if Enable_FPGA_history

#define Q_num		512
typedef struct	{
				UBYTE mode[Q_num];
				UBYTE cmd[Q_num];	
				UWORD data[Q_num];
				UBYTE time[Q_num];
				}fpgason_Str;

typedef struct	{
				UBYTE B1;
				UBYTE B2;
				UWORD RecCnt;
				UWORD D2;
				UWORD D3;
				//fpgason_Str Qurry[64]; 			
				fpgason_Str Info; 			
				}fpga_history_Str;


#endif

/******************************************************************************
*FRAM Data Structure
******************************************************************************/
typedef struct	{ 
				ULONG			CheckSum;
				UBYTE			Data_Ready;		/*when Data_Ready=200 =>Valid Data,when Data_Ready!=200 =>Invalid Data*/
				UBYTE			DispMode;
				UBYTE			M_num;
				UBYTE			Reserved2;
				UBYTE			DispScrCT;
				UBYTE			Reserved[15];
				rs_232			RS232;				/*Total   8 bytes.*/
				utility			UTILITY;			/*Total 60 bytes.*/
				gpibpar			GPIBPAR;			/*Total   8 bytes.*/
				extdgio			EXT_DGIO;			/*Total   8 bytes.*/
				P3k_Backup_Str	P3k_Backup_Data;	/*Total 1556 bytes.*/
#if Enable_Battery_Discharge
				P3k_BATT_Str	BattData;
				P3k_LED_Str 	fLedData;
				P3k_LED_Str 	cLedData;
				ULONG			Reserved1[1253];
#else
				ULONG			Reserved1[1632];
#endif

				}FRAM_Data_Str; /*Total 8192 bytes.*/
/*********************************************************************************************/
typedef struct	{
				UWORD Logical_Value;/*Logical Or*/
				UWORD Condition;
				UWORD Condition_old;
				UWORD PTR;
				UWORD NTR;
				UWORD Event;
				UWORD Enable;
				}Chan_Status; 

typedef struct	{ 
				UBYTE Logical_Value;/*Logical Or*/
				Chan_Status chan[8];
				UBYTE Event;
				UBYTE Enable;
				}Chan_Summary;

typedef struct	{ 
				UBYTE Logical_Value;/*Logical Or*/
				UBYTE Event;
				UBYTE Enable;
				}Standard_Status;

typedef struct	{ 
				UWORD Logical_Value;/*Logical Or*/
				UBYTE Chan_Status[16];
				UWORD Condition;
				UWORD Condition_old;
				UWORD PTR;
				UWORD NTR;
				UWORD Event;
				UWORD Enable;
				}Chan_Questionable;

typedef unsigned long long  uint64_t;

typedef struct	{
				UBYTE LicenseState;		/* 0:Trial 1:Register */
				UBYTE ModuleFlag;		/* 0:OFF  1:ON */
				UBYTE SoftVer;
				UBYTE Un_install;
				UWORD SoftNum;
				UWORD Reserved1;
				time_t LicenseDate;
				unsigned long SNumber1;
				unsigned long SNumber2;
				unsigned long PID;
				unsigned long VID;
				uint64_t MBR_Data;
				}OptionInfoStrust;		/*Total 36 bytes.*/

typedef struct	{
				ULONG CheckSum;
				UBYTE Data_Ready;			/*when Data_Ready=200 =>Valid Data,when Data_Ready!=200 =>Invalid Data*/
				UBYTE Reserved1[7];
				ULONG Reserved2[2];
				OptionInfoStrust OptionInfo[10];
				ULONG Reserved3[33];
			  	}Backup_APP_Str;			/*	Total 512 Bytes(512/512=1 Page)	*/

#if Enable_OCP_function
	
typedef struct	{
				UBYTE Range;			/*	IL,IM,IH 	   */
				UBYTE Reserved;			/*	IL,IM,IH 	   */
				UWORD StartCurrWatt;		/*	*/
				UWORD EndCurrWatt;		/*	SettingValue	           */
				UWORD StepCurrWatt;	/*	SettingValue	           */
				UWORD StepTime;			/*   on/off				  */
				UWORD TrigVolt;		/*	SettingValue	           */
				UWORD DelayTime;	/*	SettingValue	           */
				UWORD LastCurrWatt;
				ULONG Reserved1[4];
} F_OCP_OPP_Str;    //36 bytes

typedef struct	{
				UBYTE CurrTemp;			/**/
				UBYTE Data_Ready;
				UBYTE Complete; //0:Initial,  1:Looking for OCP, 2:Complete, 3:Search Fail, 4: Config Error
				UBYTE UpdataFlag;
				UWORD CurrWattDA;
				UWORD GetTrigV;
				F_OCP_OPP_Str Seq[12];
				UWORD RecCurr[4];
				UWORD RecVolt[4];
				ULONG Reserved[4];
} P3k_OCP_OPP_Str;    // 400 bytes

typedef struct	{
				UBYTE done;
				UBYTE VoltReady ;
				UBYTE Reserved[2];	
				UWORD timeCnt;
				UWORD startCW;
				UWORD endCW;
				UWORD stepCW;
				UWORD stepT;
				UWORD DelayT;
				UWORD lastC;
				UWORD Reserved2;
				ULONG TempDA;	
				double Cal_Gain;
				double Cal_Offset;
				double TrigV;
				double Reserved3;	
} OCP_OPP_RUN_Str;    //

#endif



#endif


//#pragma pack() //======================   Adam add  test  2013 0722======================================



/*********************************************************************
Global  Variables
*********************************************************************/
#ifdef HEAD_H_GLOBALS
#define HEAD_GLOBAL
#else
#define HEAD_GLOBAL extern
#endif
HEAD_GLOBAL BYTE M_num;						/* Current Menu number */
HEAD_GLOBAL BYTE P_M_num;					/* Previous Menu number */
HEAD_GLOBAL BYTE D_M_num;					/* Previous displayed menu number.*/
HEAD_GLOBAL BYTE F_M_num;					/* File Utility Menu number */
HEAD_GLOBAL BYTE H_M_num;					/* Help Previous Display number */
HEAD_GLOBAL BYTE S_M_num;					/* Seq Previous Display number */

HEAD_GLOBAL BYTE K_M_num;					/* KeyPad Menu Number */

HEAD_GLOBAL UWORD MenuRedrawFlag; 			/* Menu Redraw Flag */
HEAD_GLOBAL UWORD ChanRedrawFlag;			/* Chan Bar Redraw Flag */
HEAD_GLOBAL UWORD AutoExecuteFlag;			/* Auto Execute Flag */
HEAD_GLOBAL volatile UWORD SysRedrawFlag;	/* System Bar Redraw Flag */
HEAD_GLOBAL UWORD DataRedrawFlag; 			/* Data Redraw Flag */
HEAD_GLOBAL UWORD FileUtilRedrawFlag;
HEAD_GLOBAL UWORD KeypadRedrawFlag;
HEAD_GLOBAL UWORD DMA_Update_Flag;
HEAD_GLOBAL UWORD KeyInFlag;
HEAD_GLOBAL UWORD HelpRedrawFlag;
HEAD_GLOBAL UWORD CalMessageFlag;
HEAD_GLOBAL BYTE R_Chan[8];					/* Real Channel number */
HEAD_GLOBAL char ChanNo;
HEAD_GLOBAL char Remote_ChanNo;
HEAD_GLOBAL char DispCT, DispCT1, DispScrStartCT, DispScrEndCT, DispScrCurrLoc, B_DispCT, DispMode;
#if Enable_Optim_display
	HEAD_GLOBAL char B_DispStratCT;
#endif
HEAD_GLOBAL volatile char DATA_PROC_OK;             /*Measure and Fetch set 0,then wait RxMeasureProcess finish to set 1*/
HEAD_GLOBAL volatile UWORD DGIOCtrlFlag;
HEAD_GLOBAL chan_str ChanID[8];						/* record 8 chan data */
HEAD_GLOBAL disp_chan_str D_CH;						/* record Display chan data */	
HEAD_GLOBAL rs_232 RS232;
HEAD_GLOBAL interface_disp D_interface;
HEAD_GLOBAL utility UTILITY;
HEAD_GLOBAL timer_set TIMERSET;
HEAD_GLOBAL gpibpar GPIBPAR;
HEAD_GLOBAL runprog RUNPROG,D_RUNPROG,D_RUN_Temp;

HEAD_GLOBAL seqdata RUNSEQ;
HEAD_GLOBAL p3k_calibration_str P3K_CALIBRATION_BAR;
HEAD_GLOBAL dgiochainlist DGIO_BAR;
HEAD_GLOBAL extdgio EXT_DGIO;
HEAD_GLOBAL UBYTE CAL_HI_LOW_SET_OK;     /* Calibration set Hi and Low finish flag*/
HEAD_GLOBAL char v_keycode,v_keycnt,LongPush_CT;
HEAD_GLOBAL char KeyinBuf[6],KeyinCT;
HEAD_GLOBAL const type_default *ptrMODEL_TYPE;
HEAD_GLOBAL UWORD CtrlFlag1;
HEAD_GLOBAL UBYTE Check_KNOB_VAL_Count;		/* Check Now Master KNOB_VAL change*/
HEAD_GLOBAL char  System_Ready;						/*check System Ready to sync with slave*/
HEAD_GLOBAL ULONG Timer1_DGIO_Count;				/* Check Now Master KNOB_VAL change*/
HEAD_GLOBAL ULONG Timer1_DGIO_Count_Temp;			/* Save Count which prog not finish on stop*/
HEAD_GLOBAL UWORD SaveFileFlag;
HEAD_GLOBAL char Save_Status;
HEAD_GLOBAL UBYTE SEQ_Save_Status;
HEAD_GLOBAL UBYTE Go_NG_Save_Status;
HEAD_GLOBAL char Recall_Status;
HEAD_GLOBAL char SaveFileName[30];
HEAD_GLOBAL char SaveResultFileName[30];
HEAD_GLOBAL char RecallFileName[30];
HEAD_GLOBAL char SaveFileName_Temp[30];
HEAD_GLOBAL WORD SavSetupFileCount;
HEAD_GLOBAL WORD RecSetupFileCount;
HEAD_GLOBAL WORD SavMemoryFileCount;
HEAD_GLOBAL WORD RecMemoryFileCount;
HEAD_GLOBAL WORD SavPresetFileCount;
HEAD_GLOBAL WORD RecPresetFileCount;
HEAD_GLOBAL WORD SavSEQFileCount;
HEAD_GLOBAL WORD RecSEQFileCount;
HEAD_GLOBAL WORD SavNSeqFileCount;
HEAD_GLOBAL WORD RecNSeqFileCount;
HEAD_GLOBAL WORD SavFSeqFileCount;
HEAD_GLOBAL WORD RecFSeqFileCount;
HEAD_GLOBAL WORD ResultFileCount;
HEAD_GLOBAL WORD Save_Recall_InfoFlag;
HEAD_GLOBAL char MEMORY_SAVE_FLAG;		/*	0:  1:Save Memory    2:    3:Save Setup Memory    4:    5:Save Preset	*/
HEAD_GLOBAL UBYTE Status_Byte_Register;
HEAD_GLOBAL UBYTE RecoverRunProgDataFlag;
HEAD_GLOBAL UBYTE Alarm_Flag;
HEAD_GLOBAL UWORD Alarm_Count;
HEAD_GLOBAL volatile UBYTE NG_Flag;
HEAD_GLOBAL UWORD NG_Count;
HEAD_GLOBAL UWORD UnReg_Count;
HEAD_GLOBAL volatile UBYTE Tone_Flag;	/*0x01 Alarm_Tone*/
HEAD_GLOBAL UWORD Complete_Count;										/*0x02 NG_Tone*/
HEAD_GLOBAL WORD Key_Count;
HEAD_GLOBAL char GpibTrgFlag;
HEAD_GLOBAL char Service_Request_Flag;
HEAD_GLOBAL char REM_CONT;
HEAD_GLOBAL char Disp_Select;
HEAD_GLOBAL char Disp_Mode;
HEAD_GLOBAL UBYTE Soft_Key_Temp;
HEAD_GLOBAL UWORD Lua_Pixal_X_Position;
HEAD_GLOBAL char Freeze_Keyboard;
HEAD_GLOBAL char Upgrading_Flag;
HEAD_GLOBAL char Upgrading_Request;
HEAD_GLOBAL char Save_Run_Data_Request;
HEAD_GLOBAL UBYTE SEQ_Status;
HEAD_GLOBAL volatile UBYTE SEQ_Active;
HEAD_GLOBAL volatile UBYTE Prog_Active;
HEAD_GLOBAL char systemInfo_count;
HEAD_GLOBAL char Output_Buffer[8192];
HEAD_GLOBAL ULONG Output_Buffer_Count;
HEAD_GLOBAL char OverWrite_Flag;
HEAD_GLOBAL UBYTE Help_Key_Flag;
HEAD_GLOBAL char CommData_temp_ku[CommData_Size];
HEAD_GLOBAL ULONG CommData_temp_count_ku;
HEAD_GLOBAL ULONG CommFileData_count_ku;
HEAD_GLOBAL UBYTE *CommFileData_Point;
HEAD_GLOBAL char Menu_Message_Buffer[32];
HEAD_GLOBAL char Menu_Message_Data_flag;
HEAD_GLOBAL char Blink_State;/*Bit 0:ON(1)/OFF(0), Bit 1:show(1)/hide(0), Bit 2:process(1)/Not process(0)*/

HEAD_GLOBAL UWORD Model_Number; /* MODEL3031E = 0, MODEL3070 = 1, MODEL3011 = 2, MODEL3032E = 4, MODEL3020 = 6 */

//#if Enable_DMA_Display
HEAD_GLOBAL UBYTE Display_Buffer[200*1024];
//#endif

HEAD_GLOBAL UWORD Float_Window_Count;
HEAD_GLOBAL UBYTE Cal_Offset_Error;
HEAD_GLOBAL unsigned long Default_info;
HEAD_GLOBAL UBYTE System_Info_Memo;/*0:System Info, 1:System Memo*/
HEAD_GLOBAL UBYTE System_Info_Test_Mode;
HEAD_GLOBAL OptionInfoStrust OptionInfo[10];	/* 0:Sequence 1:Bus 2:Search 3:Segmented */
HEAD_GLOBAL Backup_APP_Str Backup_APP_Data;

HEAD_GLOBAL unsigned char Compensation_Flag;
HEAD_GLOBAL unsigned char Compensation_Count;
HEAD_GLOBAL unsigned char Error_Amount_Flag; 
HEAD_GLOBAL unsigned char Ext_UnReg_Flag;
HEAD_GLOBAL unsigned short FunctionFlag; 
HEAD_GLOBAL unsigned char Step_Cursor_Status;
HEAD_GLOBAL unsigned char Magnification_Cnt;
HEAD_GLOBAL Serial_Number_Str P3k_Serial_Number;
/***********************************************************************************
							P3k  Head File
************************************************************************************/
HEAD_GLOBAL p3k_meas_data p3k_Measure_Data;
HEAD_GLOBAL p3k_Acq4K_Data_Str p3k_Acq_4K_Measure_Data;
HEAD_GLOBAL p3k_cal_Data_str p3k_Cal_data;
HEAD_GLOBAL P3k_Data_Str P3k_Chan_Data;
HEAD_GLOBAL P3k_Disp_Str P3k_Disp_Data;
HEAD_GLOBAL P3k_Prog_Str p3k_Disp_PROG,p3k_Chan_PROG;
HEAD_GLOBAL p3k_file_util_str p3k_File_Utility_BAR;
HEAD_GLOBAL UBYTE P3K_CMD,P3K_CMD_R_W,RecordCMD; /*0:Read,1:Write*/
HEAD_GLOBAL UWORD P3K_DATA;
HEAD_GLOBAL FRAM_Data_Str FRAM_Data;
HEAD_GLOBAL FPGA_ISR_Str FPGA_ISR_Data;
HEAD_GLOBAL P3k_Prog_Seq_Str Prog_Seq_Data;

HEAD_GLOBAL P3k_NSeq_Str P3k_NSeq_Data,P3k_NSeq_Disp;
HEAD_GLOBAL FSeq_Timing_Str P3k_FSeq_Data,P3k_FSeq_Disp;

#if Enable_OCP_function
HEAD_GLOBAL P3k_OCP_OPP_Str P3K_OCP_Data,P3K_OCP_Disp;
#endif
#if Enable_OPP_function
HEAD_GLOBAL P3k_OCP_OPP_Str P3K_OPP_Data,P3K_OPP_Disp;
#endif

#if Enable_Battery_Discharge //Enable_LED_function
HEAD_GLOBAL P3k_LED_Str P3k_FLed_Disp;
HEAD_GLOBAL P3k_LED_Str P3k_CLed_Disp;
#endif


#if Enable_Battery_Discharge
HEAD_GLOBAL P3k_BATT_Str BattDisp;
#endif

HEAD_GLOBAL Backup_Default_Str 	Backup_Default_Data;
HEAD_GLOBAL Backup_Setup_Str 	Backup_Setup_Data[101],Backup_Setup_Data_Temp[101]; /* 0~99:Setup Memory , 100:System Setup */
HEAD_GLOBAL Backup_Preset_Str 	Backup_Preset_Data,Backup_Preset_Data_Temp;
HEAD_GLOBAL P3k_Backup_Prog_Str P3k_Backup_Prog_Data,P3k_Backup_Prog_Data_Temp;
HEAD_GLOBAL P3k_Backup_NSeq_Str P3k_Backup_NSeq_Data,P3k_Backup_NSeq_Data_Temp;
HEAD_GLOBAL P3k_Backup_FSeq_Str P3k_Backup_FSeq_Data,P3k_Backup_FSeq_Data_Temp;
HEAD_GLOBAL P3k_Backup_SN_Str 	P3k_Backup_SN;

/*********************************************************************
Status SCPI Command Define
*********************************************************************/
HEAD_GLOBAL volatile Chan_Summary Channel_Summary;
HEAD_GLOBAL volatile Chan_Questionable Channel_Questionable;
HEAD_GLOBAL UBYTE Service_Request_Enable;
HEAD_GLOBAL volatile Standard_Status Machine_Standard_Status;
/*********************************************************************
uC/OS Semaphore Define
*********************************************************************/
HEAD_GLOBAL OS_EVENT *KeyCodeDoneSemPtr;
HEAD_GLOBAL OS_EVENT *KeyCodeReadySemPtr;
HEAD_GLOBAL OS_EVENT *LcdUnlockSemPtr;
HEAD_GLOBAL OS_EVENT *InterfaceChangeSemPtr;
HEAD_GLOBAL OS_EVENT *RxBufferOverSemPtr;
HEAD_GLOBAL OS_EVENT *CalDataReadySemPtr;
HEAD_GLOBAL OS_EVENT *LuaDispReadySemPtr;
HEAD_GLOBAL OS_EVENT *LuaDispDoneSemPtr;
HEAD_GLOBAL OS_EVENT *LuaDispEventSemPtr;

/*********************************************************************
Adam_add
*********************************************************************/
//flag
HEAD_GLOBAL unsigned char SeqSyncWaitStep;//SEQ_step0:waitting_trigger;
HEAD_GLOBAL unsigned char Alarm_logo_flag;   // non:0 , e:1
HEAD_GLOBAL unsigned char checkParaAlarmCount; //para_alarm_flga;
HEAD_GLOBAL unsigned char RedrawModeLogo;// /* FAST LOGO TIMERBUG*/
HEAD_GLOBAL unsigned char SCPI_Company; //GW:0, KIKUSUI:1, 
HEAD_GLOBAL unsigned char getcursortime;//get resolution of display's parameter flag
HEAD_GLOBAL unsigned char SCPI_Freeze_menu; //0:free, 1:frezze
HEAD_GLOBAL unsigned char Parserfalg; //bit 0: klock, bit 1: remote
//HEAD_GLOBAL unsigned char WriteSEQDataToFPGA_flag;
HEAD_GLOBAL unsigned char FPGA05_Writ_flag;
HEAD_GLOBAL unsigned char PassLoad0ffSW_flag; //pass load off 20times
HEAD_GLOBAL unsigned short G_StatusFlag;
HEAD_GLOBAL unsigned char SCPI_RemFastDelay;	//1:delay,0:no delay

//count
HEAD_GLOBAL unsigned char delaySeqAlarmDisplay;//Enter_count; //ENTER WAIT TIME
//parameter
//HEAD_GLOBAL double G_Magnification;      //malt-para-parallel parameter
HEAD_GLOBAL unsigned short RecoderAlarmStatus;//ALARM_data; /* BACKUP ALARM STATUS */
HEAD_GLOBAL unsigned char CursorPrecision; //KeyVaule_parmeter; //for Cursor
HEAD_GLOBAL double _CursorResolution;    //recoder resolution of display's parameter
HEAD_GLOBAL unsigned char CCCRCP_Response_8_12; //if 0.8<=V<=1.2=>response=0.1

#define saveBmpFile			0x01
#define saveRunRecordFile	0x02

#if debug_tool
HEAD_GLOBAL unsigned char FPGA_test_status;
HEAD_GLOBAL unsigned long FPGA_test_cnt;
HEAD_GLOBAL unsigned long FPGA_err_cnt;
#endif

//  Adam_ debug //--------------------------------------------------------------------
#if 1 //debugTool
HEAD_GLOBAL volatile unsigned short FPGA_W[256]; 
HEAD_GLOBAL volatile unsigned short FPGA_R[256];
HEAD_GLOBAL volatile UWORD FPGASetting;
HEAD_GLOBAL volatile UWORD FPGAStatus;
HEAD_GLOBAL volatile unsigned char debug_pass_flag;
#if Enable_FPGA_history
HEAD_GLOBAL fpga_history_Str SetHistroy;
#endif

#endif

//HEAD_GLOBAL volatile unsigned char debug_key;

#if Normal_TEST
HEAD_GLOBAL volatile UWORD A_d1;
HEAD_GLOBAL volatile UWORD A_d2;
HEAD_GLOBAL volatile UWORD A_d3;
HEAD_GLOBAL volatile float A_d4; //on line voltage
HEAD_GLOBAL volatile float A_d5; //max
HEAD_GLOBAL volatile float A_d6; //online curr
HEAD_GLOBAL volatile float A_d7; //max curr
HEAD_GLOBAL volatile char recoder_data[64];
HEAD_GLOBAL volatile char A_d8;
//HEAD_GLOBAL volatile char debug_key;


HEAD_GLOBAL volatile unsigned short test_CountFrequency;
HEAD_GLOBAL volatile unsigned short test_Frequency;
HEAD_GLOBAL volatile unsigned short test_CountFrequency1;
HEAD_GLOBAL volatile unsigned short test_Frequency1;
HEAD_GLOBAL volatile unsigned short test_CountFrequency2;
HEAD_GLOBAL volatile unsigned short test_Frequency2;

#endif

/*===================================================

===

control DSP IO pin~
	FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_C);
	//DataFlash_Function(Read_DataFlash,Type_SetupData);
	FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_S);
	asm("nop;");
	(KeyInFlag & SHIFT_KEY)
	UTILITY.LOAD_CTL   load on\off
	if((K_Knob_Select==key)||(K_Enter_Key==key)
	recode paramater number: Command.DataList2.DATA[10][0]=index_when_copy;
	#if Adam_debug			
		test_CountFrequency++; 
	#endif	
	//#define max(a,b) ((a) > (b) ? (a) : (b))     
	//#define min(a,b) ((a) < (b) ? (a) : (b))

	if(M_num<= 0x0D){
		if(DispMode==2)DispMode=1;
	}else{
		if(DispMode==1) DispMode=0;
	}
	#pragma pad(4)
	#pragma pad()	
*/


