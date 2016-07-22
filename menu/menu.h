#ifndef MENU_H
#define MENU_H

//#define MESSAGE_
//Define the flags of MenuRedrawFlag
#define MENU_CHANGE     			0x001f
#define MENU1_CHANGE    			0x0001 /*Softkey F1*/
#define MENU2_CHANGE   				0x0002 /*Softkey F2*/
#define MENU3_CHANGE   				0x0004 /*Softkey F3*/
#define MENU4_CHANGE    			0x0008 /*Softkey F4*/
#define MENU5_CHANGE    			0x0010 /*Softkey F5*/
#define MENU_CHANGE_Again    		0x0020 
#define VAR_STR_MENU_UPDATA			0x0020

//Define the flags of SysRedrawFlag
#define SYS_CHANGE					0xffff
#define BG_CLEAR					0x0001
#define TIME_UPDATA					0x0002
#define PROT_ALARM_UPDATA			0x0004
#define REM_LOC_UPDATA				0x0008
#define ERROR_UPDATA				0x0010
#define LOCK_UPDATA					0x0020
#define SHORT_UPDATA				0x0040
#define PROG_UPDATA					0x0080
#define Interface_UPDATA			0x0100

//Define the flags of ChanRedrawFlag
#define CHAN_CHANGE					0xffff
#define BG_CLEAR					0x0001
#define BG_CLEAR1					0x0002
#define CHAN_NO						0x0004
#define CHAN_STATUS					0x0008

//Define the flags of DataRedrawFlag
#define DATA_CHANGE					0xffff
#define BG_CLEAR					0x0001
#define PARA_CHANGE					0x0002
#define UTIL_CHANGE					0x0004
#define BG_CLEAR_FLAG				0x0008
#define PARA_CHANGE_Fast			0x0010

#define TX_INIT_QUERY				0x0001
#define TX_CALI_QUERY				0x0002
#define TX_SIGNAL					0x0004
#define TX_BROADCAST				0x0008
#define TX_SERIAL					0x0010
#define TX_Upgrading				0x0020
#define TX_LoadTime					0x0040
#define TX_Display					0x0080

//Define the flags of KeypadRedrawFlag
#define KEYPAD_CHANGE				0xffff
#define KEYPAD_UPDATA				0x0001
#define KEYPAD_STR_UPDATA			0x0002
#define KEYPAD_NEW_FOLDER			0x0004
#define KEYPAD_RENAME_FOLDER		0x0008
#define KEYPAD_RENAME_Memo			0x0010


//Define the flags of FileUtilRedrawFlag
#define FILEUTIL_CHANGE				0xffff
#define FILEUTIL_DISP_INIT			0x0001
#define FILEUTIL_SHOW_SCR			0x0002
#define FILEUTIL_SHOW_PATH			0x0004
#define FILEUTIL_SHOW_DIR			0x0008

// Define the flags of KeyInFlag
#define KEY_CHANGE					0xffff
#define DIGI_KEY_IN					0x0001
#define SHIFT_KEY					0x0002
#define PRESET_KEY					0x0004
#define LONG_PUSH					0x0008		/* If key was keep push in few time */
#define LONG_PUSH_DONE				0x0010
#define LP_ON						0x0020

// Define the flags of AutoExecute
#define Slave_Data_Update			0x0001
#define Measure_Data_Update			0x0002
#define Time_Update					0x0004
#define Backup_Data_To_Fram			0x0008

//Key
#define F1_Key						0x71
#define F2_Key						0x72
#define F3_Key						0x73
#define F4_Key						0x74
#define F5_Key						0x75

// Define the flags of HelpRedrawFlag
#define HELP_FUN_ON					0x0001
#define HELP_CHANGE					0x0002

// Define the flags of DGIOCtrlFlag
#define DGIO_ON						0x0001
#define DGIO_RUN					0x0002
#define SHORT_FLAG					0x0004
#define EXT_DGIO_INT				0x0008
#define EXT_Frame_CONT_DISP			0x0010
#define EXT_Frame_CONT_KB			0x0020
#define Timer_DGIO_ON				0x0040
#define Timer_DGIO_ON_DATA			0x0080
#define CheckSum_Error				0x0100
#define REM_Mode_Fast				0x0400
#define SEQ_RUN						0x0800
#define Timer_DGIO_ON_DATA_pro		0x1000
#define NO_SN						0x2000
#define RUN_SEQ_CHAN				0x4000

//Define the flags of CtrlFlag1
#define Alarm_Latch					0x0001
#define Cal_Wait_moment				0x0002
#define Float_Windows_DispOff		0x0004
#define Disp_Middle_Message			0x0010
#define BEEP_ACT                 	0x0020
#define Float_Windows_DispOn		0x0040
#define Disp_IRange_Window			0x0080
#define Function_Lock				0x0100
#define P_Recall_Flag				0x0200
#define M_Recall_Flag				0x0400

//Define the flags of Cal_Offset_Error
#define Meas_Err					0x01
#define CPP_Err						0x02
#define ROCP_Err					0x04
#define OPP_Err						0x08
#define OCP_Err						0x10
#define CXCV_Err					0x20

//Define the flags of CalMessageFlag
#define Show_Message				0x0001
#define Clear_Message				0x0002

//Define the flags of CAL_HI_LOW_SET_OK
#define HP_Cal_Finish				0x01
#define LP_Cal_Finish				0x02

#define Default_Cal_Gain			1
#define Default_Cal_Offset			0
#define Default_Cal_Prot_Ref		8500 //7500//7447
#define Default_Cal_OS_Ref			34000//29992//29789
#define Default_Cal_CXCV			0
#define Default_Cal_Prot_DA_Rating	54000//39794	//36480	//24500	/*Rating OCP,CPP*/ /* samuel_kuo 2012/02/01*/
#define Default_Cal_Prot_DA_OCP		48000	/*OCP*/
#define Default_Cal_Prot_DA_OPP		49300//34820	//23400	/*OPP*/


#define Cal_FPGA_Command			0xf0
#define Cal_FPGA_Start				0x00
#define Cal_FPGA_End				0x01
#define Cal_FPGA_Fail				0x02
#define Cal_FPGA_Load_Meas_Default	0x03
#define Cal_FPGA_PSensor_H			0x04
#define Cal_FPGA_Prot				0x05
#define Cal_FPGA_Load_Cal_Default	0x06
#define Cal_FPGA_PSensor_L			0x07
#define Cal_FPGA_OffsetAdjSetDA		0x08
#define Cal_FPGA_OffsetAdjValue		0x09
#define Cal_FPGA_OffsetAdj_End		0x0A


#define Machine_Command				0x00
#define Machine_Meas_Query			0x00
#define Machine_Init_Query			0x01
#define Machine_Input_Trigger		0x02
#define Machine_Seq_ID				0x03
#define Machine_Prot_Status			0x04
#define Machine_modeHandle			0x06
#define Machine_Pause_Prog			0x07
#define Machine_Load_OnOff			0x0B

#define CMD_LOAD_SW					tx_data.ADDRH = Machine_Command;\
									tx_data.ADDRL = Machine_Load_OnOff;\
									SendTXData(&tx_data)	
#define Machine_OCP_Level			0x10
#define Machine_OPP_Level			0x12
#define Machine_Test_Query			0x19
#define Machine_Von_Delay			0x1B
#define Machine_Von_Voltage			0x20
#define Machine_Soft_Start			0x22
#define CMD_SOFT_START				tx_data.ADDRH = Machine_Command;\
									tx_data.ADDRL = Machine_Soft_Start;\
									SendTXData(&tx_data)

#define Machine_SyncTrigg			0x23
#define Machine_MeasureAverage		0x24
#define Machine_TrigInDelay			0x25
#define Machine_TrigOutWidth		0x26

#if debug_tool
#define Machine_FGPA_TEST			0x70
#endif
#define Machine_Enable_Acq4K		0xA0
#define Machine_Setting_IMON		0xD0

#define Para_Ext_Command			0x60
#define Para_Ext_Setting			0x00	/*Operation Master/Slave */
#define CMD_EXT_SETTING 			tx_data.ADDRH = Para_Ext_Command;\
									tx_data.ADDRL = Para_Ext_Setting;\
									SendTXData(&tx_data)


#define Para_Ext_Status				0x01

/*Define the flags of p3k_Measure_Data.Alarm*/
#define No_Alarm					0
#define OTP_Alarm					1
#define RVP_Alarm					2
#define OVP_Alarm					3
#define UVP_Alarm					4
#define Para_Alarm					5
#define OPP_Alarm					6
#define OCP_Alarm					7
#define CPP_Alarm					8
#define ROCP_Alarm					9
#define FCCP_Alarm					10
#define UnReg_Alarm					11
#define Ext_Alarm					12

#define Set_Limit					1
#define Set_LoadOff					0

#define Clear_Alarm					0x00
#define Set_Alarm					0x01

#define Acq_Max_Point				4095

#define Operation_Master			0
#define Operation_Slave				1

#define Ext_Setting_OFF				0
#define Ext_Setting_V				1
#define Ext_Setting_R				2
#define Ext_Setting_InvR			3

#define Mid_Bais_OS 				10

#define FPGA_Reset 					0x0001

// Define the flags of Function Flag
#define FUNC_CLEAR				0
#define FUNC_NORMAL				0x0001
#define FUNC_PROG				0x0002
#define FUNC_NSEQ				0x0004
#define FUNC_FSEQ				0x0008

#if 1//Enable_Battery_Discharge
#define FUNC_OCP				0x0010
#define FUNC_OPP				0x0020
#define FUNC_BATT				0x0040
#define FUNC_FLED				0x0000 //0x0080
#define FUNC_CLED				0x0100
#define FUNC_ON					0x01FE
#else
#define FUNC_ON					0x000E
#endif


#endif   /* ifdef MENU_H */

