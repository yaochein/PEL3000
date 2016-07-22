/* File   :KEYDEF
   Purpose:Define the symbolic name for each keyboard scan code
   Date   :12/05/1996
*/
#ifndef KEYDEF_H
#define KEYDEF_H

/* Start of Menu Number Define */

/* Chan Key Function */
#define P_CC				0x00
#define P_CR				0x01
#define P_CV 				0x02
#define P_CP 				0x03
#define P_CC_SPEC			0x04
#define P_CR_SPEC			0x05
#define P_CV_SPEC			0x06
#define P_CP_SPEC			0x07

#define P_CONF_PROT			0x08
#define P_CONF_OTHER		0x09
#define P_CONF_Para			0x0A
#define P_CONF_KNOB			0x0B
#define P_CONF_Ext			0x0C

/* Function Main */	
#define P_FUNC_MAIN			0x0D

/* Program  Function */	
#define P_PROG_MAIN			0x0E
#define P_PROG_CHAIN		0x0F
#define P_PROG_EXECUTE		0x10
#define P_PROG_Detail		0x11 

/* Sequence  Function */
#define P_Seq_FUNC			0x12
#define P_Seq_Normal		0x13
#define P_Seq_Fast			0x14
#define P_NSeq_Edit			0x15
#define P_FSeq_Edit			0x16
#define P_NSeq_EXECUTE		0x17
#define P_FSeq_Fill			0x18
#define P_FSeq_EXECUTE		0x19

/* File Key Function */
#define P_FILE_CHAN			0x1A
#define P_FILE_MACHINE		0x1B

/* Calibration Function */
#define P_CAL_MODE			0x1C

/* Utility Key Function */
#define P_UTIL_MAIN			0x1D
#define P_UTIL_INTERFACE	0x1E

#define P_UTIL_T_DATE		0x1F
#define P_UTIL_LOAD			0x20
#define P_UTIL_OTHER		0x21
#define P_UTIL_SYSINFO		0x22
#define P_UTIL_SYSMEMO		0x23

/* File System & Keypad Function */
#define P_UTIL_KEYPAD		0x24
#define P_UTIL_FILE			0x25

/* Password */
#define P_Input_Password	0x26
#define P_Input_Serial		0x27

/* Help Function */
#define P_HELP_HELP			0x28

/* LUA execute */	
#define P_LUA_EXECUTE		0x29

#define P_Test_Func			0x2A
#define P_FUNC_POWER		0x2B
#define P_Cal_Value			0x2C

#define P_FUNC_MAIN_2		0x2D
#define P_FUNC_OCP			0x2E
#define P_FUNC_OCP_EXECUTE	0x2F //P_NSeq_EXECUTE

#define P_FUNC_OPP			0x30
#define P_FUNC_OPP_EXECUTE	0x31
#define P_FUNC_batt			0x32
#define P_FUNC_batt_EXECUTE	0x33
#define P_FUNC_FLED			0x34
#define P_FUNC_FLED_EDIT	0x35
#define P_FUNC_FLED_EXECUTE	0x36
#define P_FUNC_CLED			0x37
#define P_FUNC_CLED_EDIT	0x38
#define P_FUNC_CLED_EXECUTE	0x39




/* Media Information */
#define P_Memory_Type		0
#define P_Memory_Number		1
#define P_Memory_Max		2

#define P_USB_Type			0
#define P_USB_Save			1
#define P_USB_Recall		2
#define P_USB_Max			3


#define F_Media_Memory		0
#define F_Media_USB 		1
#define F_Media_Default 	2

#define F_Memory_Data		0
#define F_Setup_Data		1
#define F_Preset_Data		2
#define F_NSeq_Data			3
#define F_FSeq_Data			4

#define M_Nothing			0
#define M_Memory_Save_Ok	1
#define M_Clear_Message		2
#define M_Setup_Save_Ok		3
#define M_Setup_Recall_Ok	4
#define M_Preset_Save_Ok	5
#define M_Preset_Save_All_Ok 6


/* CC and CR Mode */
#define Function_Static		0x00
#define Function_Dynamic	0x01

#define Dyn_TimeBase_1us	0x00
#define Dyn_TimeBase_1ms	0x01

#define SlewRate_TimeBase_1	0x00
#define SlewRate_TimeBase_2	0x01
#define SlewRate_TimeBase_3	0x02

#define SLEWRATE_Range_1	10		/* 10mA/us 		*/
#define SLEWRATE_Range_2	100		/* 100mA/us		*/
#define SLEWRATE_Range_3	1000	/* 1000mA/us	*/

#define Dyn_Freq_TimeBase_100Hz		0x00
#define Dyn_Freq_TimeBase_10Hz		0x01
#define Dyn_Freq_TimeBase_1Hz		0x02
#define Dyn_Freq_TimeBase_100mHz	0x03

#define CCCR_Sta_A_VALUE	0x00
#define CCCR_Sta_B_VALUE	0x01
#define CCCR_Sta_SR			0x02
#define CCCR_Sta_Add_CV		0x03
#define CCCR_Sta_CV_Response 0x04
#define CCCR_Sta_Max		0x05

#define CCCR_Dyn_L1			0x00
#define CCCR_Dyn_L2			0x01
#define CCCR_Dyn_SRUP		0x02
#define CCCR_Dyn_SRDN		0x03
#define CCCR_Dyn_T1			0x04
#define CCCR_Dyn_T2			0x05
#define CCCR_Dyn_Add_CV		0x06
#define CCCR_Dyn_CV_Response 0x07
#define CCCR_Dyn_Max		0x08

/* CV Mode */
#define CV_A_VALUE			0x00
#define CV_B_VALUE			0x01
#define CV_Max				0x02

/* CP Mode */
#define CP_Sta_A_VALUE		0x00
#define CP_Sta_B_VALUE		0x01
#define CP_Sta_Add_CV		0x02
#define CP_Sta_CV_Response	0x03
#define CP_Sta_Max			0x04

#define CP_Dyn_L1			0x00 //delet
#define CP_Dyn_L2			0x01 //delet
#define CP_Dyn_T1			0x02 //delet
#define CP_Dyn_T2			0x03 //delet
#define CP_Dyn_Add_CV		0x04 //delet
#define CP_Dyn_Max			0x05 //delet

/* Configure Protection */
#define P_OCP_LEVEL			0x00
#define P_OCP_SETTING		0x01
#define P_OPP_LEVEL			0x02
#define P_OPP_SETTING		0x03
#define P_UVP_LEVEL			0x04
#if Enable_Ring_Count
#define P_UVP_SETTING		0x05
#define P_OVP_LEVEL			0x06
#define Pro_Max				0x07
#else
#define P_OVP_LEVEL			0x05
#define Pro_Max				0x06
#endif


/* Configure Other */
#define P_SOFT_START		0
#define P_VON_VOLTAGE		1
#define P_VON_LATCH			2
#define P_Von_Delay			3
#define P_COUNTTIME			4
#define P_CUTOFFTIME		5
#define P_CR_Unit			6
#define P_Dyna_Level		7
#define P_Dyna_Time			8
#define P_Mem_Recall		9

#if Enable_Short_invalidate
#define P_SHORT_Fun			10
#define P_SHORT_KEY			11
#define P_SHORT_Safety		12
#define P_Conf_Max			13
#else
#define P_SHORT_KEY			10
#define P_Conf_Max			11
#endif


#define P_1_1_Response		0x00
#define P_1_2_Response		0x01
#define P_1_5_Response		0x02
#define P_1_10_Response		0x03

#define OHM_Unit			0
#define MHO_Unit			1

/*Configure Spec */
#define P_SPEC_TEST			0x00
#define	P_SPEC_DELAY		0x01
#define	P_SPEC_ENTRY		0x02
#define	P_SPEC_HIGH			0x03
#define	P_SPEC_LOW			0x04
#define	P_SPEC_CENTER		0x05
#define	P_SPEC_MAX			0x06

/*Configure Step*/
#define P_Knob_Status		0
#define P_CCH_STEP			1	//#define P_CCM_STEP			2
#define P_CCL_STEP			2
#define P_CRH_STEP			3	//#define P_CRM_STEP			5
#define P_CRL_STEP			4
#define P_CVH_STEP			5
#define P_CVL_STEP			6
#define P_CPH_STEP			7	//#define P_CPM_STEP			10
#define P_CPL_STEP			8
#define P_Konb_MAX			9

/*Configure Parallel*/
#if 1

#define P_Sync_TrigIn		0
#define P_Sync_TrigInDelay	1
#define P_Sync_TrigOut		2
#define P_Sync_TrigOutWidth 3
#define P_Sync_MAX			4

#endif

#define P_Para_Operation	0
#define P_Para_Unit			1
#define P_Para_Booster		2
#define P_Para_MAX			3



/*Configure External*/
#define P_Ext_Control		0
#define P_Ext_LoadON_IN		1
#define P_Extmulti_para     2
#define P_Ext_MAX			3

#define P_Func_M_start		0
#define P_Func_M_comp		1
#define P_Func_M_count		2
#define P_Func_M_Max		3


/*Normal Sequence*/
#define P_NSeq_Start		0
#define P_NSeq_No			1
#define P_NSeq_Memo			2
#define P_NSeq_Mode			3
#define P_NSeq_Range		4
#define P_NSeq_Loop			5
#define P_NSeq_Last_Load	6
#define P_NSeq_Last_Set		7
#define P_NSeq_Chain		8
#define P_NSeq_Max			9

#define P_NSeqEdit_Step		0
#define P_NSeqEdit_Value	1
#define P_NSeqEdit_Time_H	2
#define P_NSeqEdit_Time_M	3
#define P_NSeqEdit_Time_S	4
#define P_NSeqEdit_Time_mS	5
#define P_NSeqEdit_Load		6
#define P_NSeqEdit_Ramp		7
#define P_NSeqEdit_Trig		8
#define P_NSeqEdit_Pause	9
#define P_NSeqEdit_Max		10

/*Fast Sequence*/
#define P_FSeq_Memo			0
#define P_FSeq_Mode			1
#define P_FSeq_Range		2
#define P_FSeq_Loop			3
#define P_FSeq_TimeBase		4
#define P_FSeq_Last_Load	5
#define P_FSeq_Last_Set		6
#define P_FSeq_RptStep		7
#define P_FSeq_Max			8

#define P_FSeqEdit_Step		0
#define P_FSeqEdit_Value	1
#define P_FSeqEdit_Trig		2
#define P_FSeqEdit_Max		3

#define P_Fill_Value_S		0
#define P_Fill_Value_E		1
#define P_Fill_Step_S		2
#define P_Fill_Step_E		3
#define P_Fill_Max			4

/*Program Main*/
#define Program_PROG		0
#define Program_STEP 		1
#define Program_Memory 		2
#define Program_Run	 		3
#define Program_On_Time		4
#define Program_Off_Time 	5
#define Program_P_F_Time 	6
#define Program_Short_Time	7
#define Prog_Max			8

/* Utility Other */
#define Util_Knob_Type		0
#define Util_Speaker		1
#define Util_Alarm_Tone		2
#define Util_UnReg_Tone		3
#define Util_Go_NoGO_Tone	4
#define Util_Contrast		5
#define Util_Brightness		6
#define Util_Language		7

/* OCP Function*/
#define P_F_OCP_CurrTemp	0
#define P_F_OCP_Range		1
#define P_F_OCP_StartCurr	2
#define P_F_OCP_EndCurr		3
#define P_F_OCP_StepCurr	4
#define P_F_OCP_StepTime	5
#define P_F_OCP_DelayTrig	6
#define P_F_OCP_TrigVolt	7
#define P_F_OCP_LastCurr	8
#define P_F_OCP_Max			9

/* OPP Function*/
#define P_F_OPP_CurrTemp	0
#define P_F_OPP_Range		1
#define P_F_OPP_StartCurr	2
#define P_F_OPP_EndCurr		3
#define P_F_OPP_StepCurr	4
#define P_F_OPP_StepTime	5
#define P_F_OPP_DelayTrig	6
#define P_F_OPP_TrigVolt	7
#define P_F_OPP_LastCurr	8
#define P_F_OPP_Max			9


/* Battery Discharge Function*/
#define P_F_BATT_Mode		0
#define P_F_BATT_Range		1
#define P_F_BATT_Set		2
#define P_F_BATT_SRUP		3
#define P_F_BATT_SRDW		4
#define P_F_BATT_StopV		5
#define P_F_BATT_StopT		6
#define P_F_BATT_StopC		7
#define P_F_BATT_Max		8

/* FLED  Function*/
#define P_F_LED_No			0
#define P_F_LED_Momo		1
#define P_F_LED_Range		2
#define P_F_LED_RESPONSE	3
#define P_F_LED_PATAMTER	4
#define P_F_LED_Max			5

//Vo,Io / Vo,Io,Rcoff / Vo,Io,Rd / Vo,Io,Vd / Vd,Rd,pcs	
#define P_F_LED_MODE_VoIo	0
#define P_F_LED_MODE_VoIoRc	1
#define P_F_LED_MODE_VoIoRd	2
#define P_F_LED_MODE_VoIoVf	3
#define P_F_LED_MODE_VfRdPcs 4

#define P_F_LED_Edit_P1		0
#define P_F_LED_Edit_P2		1
#define P_F_LED_Edit_P3		2

/* CLED  Function*/
#define P_CLED_No			0
#define P_CLED_Momo			1
#define P_CLED_Range		2
#define P_CLED_RESPONSE		3
#define P_CLED_VO			4
#define P_CLED_IO			5
#define P_CLED_Max			6

/* CLED_EXE  Function*/
#define P_CLED_EXE_VO		0
#define P_CLED_EXE_IO		1
#define P_CLED_EXE_RDCOEFF	2
#define P_CLED_EXE_Max		3



/*Interface*/
#define Interface_Select	0x00
#define Baud_Rate			0x01
#define Stop_Bit			0x02
#define RS232_Parity		0x03
#define GPIB_Address		0x04

#define tx_NO_DATA			0x04
#define tx_SIGNAL_DATA		0x05
#define tx_DOUBLE_DATA		0x06
#define tx_FOUR_DATA		0x08

/* Keyboard Information */
#define K_Invalid_Key 		0x00
#define K_Digital_0 		0x60
#define K_Digital_1 		0x61
#define K_Digital_2 		0x62
#define K_Digital_3 		0x63
#define K_Digital_4 		0x64
#define K_Digital_5 		0x65
#define K_Digital_6 		0x66
#define K_Digital_7 		0x67
#define K_Digital_8 		0x68
#define K_Digital_9 		0x69
#define K_Digital_Dot 		0x6a
#define K_Clear_Key 		0x6b
#define K_Enter_Key 		0x6c
#define K_Preset_Key 		0x6d
#define K_Shift_Key 		0x6e
#define K_Load_Key			0x6f
#define K_Short_Key			0x70
#define K_F1_Key			0x71
#define K_F2_Key			0x72
#define K_F3_Key			0x73
#define K_F4_Key			0x74
#define K_F5_Key			0x75
#define K_Func_Key			0x76
#define K_Help_Key			0x77
#define K_Main_Key			0x78
#define K_Knob_Select		0x7b
#define K_Knob_Rotate		0xd6

#define A_Value				0x00
#define B_Value				0x01

#define Cal_High_Point			0
#define Cal_Low_Point			1
#define Cal_Item_Num			2

#define Select_Volt				0
#define Select_Curr				1

#define HIGH_RANGE 				1
//#define Mid_RANGE 				1
#define LOW_RANGE 				0

#define IRange_High 			1
//#define IRange_Mid 				1
#define IRange_Low 				0

#define VRange_High 			1
#define VRange_Low 				0

#define Range_ILVL				0
#define Range_IHVL				1
#define Range_ILVH				2
#define Range_IHVH				3

#define RESPONSE_SLOW			1
#define RESPONSE_MIDDLE			1
#define RESPONSE_FAST			100



#define PSense_X				0
#define PSense_Y				1
#define PSense_Z				2

#define GONG_Value				0
#define GONG_Percent			1

#define Buzzer_Alarm			0
#define Buzzer_NG				1
#define Buzzer_Key				2
#define Buzzer_UnReg			3
#define Buzzer_Complete			4


#define Skip_MODE				0
#define Auto_MODE				1
#define Manual_MODE				2

#define SHORT_MODE				0
#define LOADON_MODE				1
#define LOADOFF_MODE			2

#define Display_Stop			0	/* Continue Run Prog */
#define Display_Continue		1	/* Stop Run Prog */
#define Display_None			2	/* Continue Run Prog */

#define M_Out_Of_Range			0	/* It is Message to Show Out Of Range*/
#define M_Success				1	/* It is Message to Show Success*/

#define Normal_Load				0
#define Prog_Load				1
#define NSeq_Load				2
#define FSeq_Load				3
#define OCP_Load				4
#if 1 //Enable_Battery_Discharge
#define OPP_Load				5
#define BATT_Load				6
#define FLED_Load				7
#define CLED_Load				8
#endif


#define System_Recall_Default	0
#define User_Recall_Default		1
#define Sync_Recall_Default		2
#define Recall_Interface_Y		0
#define Recall_Interface_N		1

#define Recall_DataType_Preset	0
#define Recall_DataType_Prog	1
#define Recall_DataType_Setup	2
#define Recall_DataType_NSEQ	3
#define Recall_DataType_FSEQ	4
#define Recall_DataType_Cal		5


#define File_Source				0
#define USB_Source				1

#define Lic_Uninstall			0
#define Lic_Install				1

#define CVCP_ResponseSlow		0
#define CVCP_ResponseNormal	1
#define CVCP_ResponseFast		2

#define CXCV_ResponseSlow		0
#define CXCV_ResponseFast		1


#endif   /* ifdef KEYDEF_H */

