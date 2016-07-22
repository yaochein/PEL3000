#ifndef   FPGA_H
#define   FPGA_H

typedef union BAFLOAT	{							// Byte  -  Addressable FLOAT
						float f;                	// float 			:  Var.f
						unsigned char b[4];         // unsigned char  	:  Var.b[0]:Var.b[1]
						}BAFLOAT;               	// 		 		:  Var.b[2]:Var.b[3]

typedef union BALONG	{							// Byte  -  Addressable LONG
						unsigned long l;            // unsigned long 	:  Var.l
						unsigned char b[4];			// unsigned char	:  Var.b[0]:Var.b[1]
						}BALONG;					// 		 		:  Var.b[2]:Var.b[3]

typedef union BAINT		{							// Byte  -  Addressable INT
						unsigned short i;			// unsigned short  	:  Var.i
						unsigned char b[2];			// unsigned char  	:  Var.b[0]:Var.b[1]
						}BAINT;	

typedef union			{							/* Short  -  Addressable LONG	*/
						unsigned long l;            /* unsigned long 	:  Var.l		*/
						unsigned short s[2];		/* unsigned short	:  Var.s[0]:Var.s[1]*/
						}SALONG;
/* Control Board FPGA Register Command Define */
#define FPGA_Control							0x00000000
#define FPGA_Machine_Status						0x01000000
#define FPGA_Status								0x02000000
#define FPGA_Sequence_Mode_Set_ID				0x04000000
#define FPGA_On_Off_Reference_Setting			0x05000000
#define FPGA_On_Off_Latch_Setting				0x06000000
#define FPGA_Test_Register						0x07000000
#define FPGA_Soft_Start_Slew_Rate				0x08000000
#define FPGA_Soft_Start_Circuit_Switch_1 		0x09000000
#define FPGA_Soft_Start_Delta_VH				0x0A000000
#define FPGA_Soft_Start_Delta_VL				0x0B000000
#define FPGA_Soft_Start_Delta_T					0x0C000000
#define FPGA_Acquire_System_Sampling_Rate		0x0D000000
#define FPGA_Acquire_System_Pre_Trigger_Counter	0x0E000000
#define FPGA_Acquire_System_Sweep_Counter		0x0F000000

#define CC_H_Load_Off							0x11000000	//#define CC_M_Load_Off							0x11000000
#define CC_L_Load_Off							0x12000000

#define CR_H_Load_Off							0x14000000	//#define CR_M_Load_Off							0x14000000
#define CR_L_Load_Off							0x15000000

#define CP_H_Load_Off							0x17000000	//#define CP_M_Load_Off							0x17000000
#define CP_L_Load_Off							0x18000000

#define CV_H_Load_Off							0x19000000
#define CV_L_Load_Off							0x1A000000
#define FPGA_Von_Delay							0x1B000000

/* Measurement FPGA Register Command Define */
#define FPGA_V_Sense							0x20000000
#define FPGA_I_Sense							0x21000000
#define FPGA_AcqMem_V_Sense_Ext_RV_Cont_Ref		0x22000000
#define FPGA_AcqMem_I_Sense						0x23000000
#define FPGA_V_Sense_DMA_Control				0x24000000	//No
#define FPGA_I_Sense_DMA_Control				0x25000000	//NO
#define FPGA_V_Sense_Raw						0x26000000
#define FPGA_I_Sense_Raw						0x27000000

#define FPGA_V_Sense_H_Gain						0x30000000
#define FPGA_V_Sense_H_Offset					0x31000000
#define FPGA_V_Sense_L_Gain						0x32000000
#define FPGA_V_Sense_L_Offset					0x33000000
#define FPGA_I_Sense_H_Gain						0x36000000
#define FPGA_I_Sense_H_Offset					0x37000000//#define FPGA_I_Sense_M_Gain	0x36000000//#define FPGA_I_Sense_M_Offset					0x37000000
#define FPGA_I_Sense_L_Gain						0x38000000
#define FPGA_I_Sense_L_Offset					0x39000000

/* Static & Dynamic FPGA Register Command Define */
#define FPGA_H_Level_Setting					0x40000000
#define FPGA_H_Level_Slew_Rate					0x41000000
#define FPGA_H_Circuit_Switch_Control_0			0x42000000
#define FPGA_H_Circuit_Switch_Control_1			0x43000000
#define FPGA_H_T1_Duration						0x44000000
#define FPGA_H_Level_Ramp_Delta_VH				0x45000000
#define FPGA_H_Level_Ramp_Delta_VL				0x46000000
#define FPGA_H_Level_Ramp_Delta_T				0x47000000
#define FPGA_L_Level_Setting					0x48000000
#define FPGA_L_Level_Slew_Rate					0x49000000
#define FPGA_L_Circuit_Switch_Control_0			0x4A000000
#define FPGA_L_Circuit_Switch_Control_1			0x4B000000
#define FPGA_L_T2_Duration						0x4C000000
#define FPGA_L_Level_Ramp_Delta_VH				0x4D000000
#define FPGA_L_Level_Ramp_Delta_VL				0x4E000000
#define FPGA_L_Level_Ramp_Delta_T				0x4F000000

/* Sequence OR Run-Program FPGA Register Command Define */
#define FPGA_Seq_Start_Address					0x50000000
#define FPGA_Seq_Load_On_Setting				0x51000000
#define FPGA_Seq_Slew_Rate						0x52000000
#define FPGA_Seq_Circuit_Switch_0				0x53000000
#define FPGA_Seq_Circuit_Switch_1				0x54000000
#define FPGA_Seq_Duration_Time					0x55000000
#define FPGA_Seq_Ramp_Delta_VH					0x56000000
#define FPGA_Seq_Ramp_Delta_VL					0x57000000
#define FPGA_Seq_Ramp_Delta_T					0x58000000
#define FPGA_Seq_Last_Load_On					0x59000000
#define FPGA_Seq_Last_SR						0x5A000000
#define FPGA_Seq_Last_CS0						0x5B000000
#define FPGA_Seq_Last_CS1						0x5C000000

/* Sequence OR Run-Program Jump Point Register Command Define */
#define FPGA_Jump_Point_Address					0x60000000
#define FPGA_Write_JP_Counter					0x61000000
#define FPGA_Read_JP_Counter					0x62000000
#define FPGA_Jump_Ramp_SlewRate					0x63000000
#define FPGA_Jump_Ramp_CS1						0x64000000
#define FPGA_Jump_Ramp_Delta_VH					0x65000000
#define FPGA_Jump_Ramp_Delta_VL					0x66000000

/* Protection & Reference Adjust & Calibration FPGA Register Command Define */
#define FPGA_CX_H_OCP							0x91000000	//#define FPGA_CX_M_OCP							0x91000000
#define FPGA_CX_L_OCP							0x92000000

#define FPGA_ZH_OS_Ref							0x93000000
#define FPGA_XH_OS_Ref							0x94000000//#define FPGA_CX_H_ROCP	0x95000000//#define FPGA_CX_M_ROCP	0x96000000//#define FPGA_CX_L_ROCP 						0x97000000
#define CR_OS_REF_H								0x96000000	//#define CR_OS_REF_M							0x96000000
#define CR_OS_REF_L 							0x97000000

#define FPGA_YH_OS_Ref							0x98000000
#define FPGA_IS_OS_Ref							0x99000000
#define FPGA_VS_OS_Ref							0x9A000000
#define FPGA_VON_H								0x9B000000
#define FPGA_VON_L								0x9C000000

#define FPGA_CX_H_OPP							0x9E000000	//#define FPGA_CX_M_OPP							0x9E000000
#define FPGA_CX_L_OPP							0x9F000000

#define Cx_CV_H_Value							0xA0000000
#define Cx_CV_L_Value							0xA1000000
#define Prot_OS_Ref								0xA2000000

#define FPGA_CX_H_CPP							0xA4000000	//#define FPGA_CX_M_CPP							0xA4000000
#define FPGA_CX_L_CPP							0xA5000000

#define FPGA_Ext_RV_Control						0xA6000000
#define FPGA_OS_Ref								0xA7000000
#define FPGA_Ext_R_Cont_Ref						0xA8000000
#define FPGA_Current_Monitor_Out				0xA9000000
#define FPGA_ZL_OS_Ref							0xAA000000
#define FPGA_XL_OS_Ref							0xAB000000
#define FPGA_YL_OS_Ref							0xAC000000
#define Cx_CV_H_Step							0xAD000000
#define Cx_CV_L_Step							0xAE000000
#define Cx_CV_Response							0xAF000000


/* External Control & Parallel Operation FPGA Register Command Define */
#define FPGA_External_Status					0xB0000000
#define FPGA_External_Applied_Operation_Control	0xB1000000
#define FPGA_EXT_RV_SENSE						0xB2000000
#define FPGA_EXT_RV_SENSE_Gain					0xB3000000
#define FPGA_EXT_RV_SENSE_Offset				0xB4000000

#define FPGA_EXT_CRH_RV_Control_Gain_MSB		0xB7000000
#define FPGA_EXT_CRH_RV_Control_Gain_LSB		0xB8000000

//#define FPGA_EXT_CRM_RV_Control_Gain_MSB		0xB7000000
//#define FPGA_EXT_CRM_RV_Control_Gain_LSB		0xB8000000

//#define FPGA_EXT_CRL_RV_Control_Gain_MSB		0xB9000000//no used
//#define FPGA_EXT_CRL_RV_Control_Gain_LSB		0xBA000000//no used

#define FPGA_EXT_CRH_RV_Control_Offset			0xBC000000
//#define FPGA_EXT_CRM_RV_Control_Offset			0xBC000000
#define FPGA_EXT_CRL_RV_Control_Offset			0xBD000000 //no used

/* Trigger-IN-Delay, Trigger-Out-Width, Adjust */
#define FPGA_Trig_In_Delay						0xC0000000
#define FPGA_Trig_Out_Width						0xC1000000

/* Front Panel BNC Output Cintrol FPGA Register Command Define */
//#define FPGA_Front_IMON_Output_Adjust			0xD0000000
#define FPGA_Rear_IMON_Output_Adjust			0xD1000000

#if Enable_LED_function
#define FPGA_LED_MODE_ENABLE					0xE0000000
#define FPGA_LED_ADDR_CLEAR						0xE1000000
#define FPGA_LED_LUT_DATA						0xE2000000
#define FPGA_VD_CNT								0xE3000000
#define FPGA_LED_SLEW_SCALING_GATE_H			0xE4000000
#define FPGA_LED_SLEW_SCALING_GATE_L			0xE5000000
#define FPGA_LED_SLEW_SCALING_OFFSET			0xE6000000


#endif


/* Key Board CPLD Register Command Define */
#define CPLD_Key_Read							0xF0000000
#define CPLD_Key_LED_Control					0xF1000000

/* FPGA Cx Mode Circuit Switch Control Command */
/* Format => Internal | External : Mode : Range : Switch */

#define I_CC_High_0								0x0111
#define I_CC_High_1								0

#define I_CC_Low_0								0x0011
#define I_CC_Low_1								0

#if 1
#define I_CR_High_0								0x0112
#define I_CR_High_1								0x0020

#define I_CR_Low_0								0x0112
#define I_CR_Low_1								0x0020

#else
#define I_CR_High_0								0x0112
#define I_CR_High_1								0

#define I_CR_Low_0								0x0112
#define I_CR_Low_1								0
#endif
#define I_CV_High_0								0x0121
#define I_CV_High_1								0

#define I_CV_Low_0								0x0021
#define I_CV_Low_1								0

#define I_CP_High_0								0x0341
#define I_CP_High_1								0

#define I_CP_Low_0								0x0041
#define I_CP_Low_1								0

#define E_CC_High_0								0x0114
#define E_CC_High_1								0

#define E_CC_Low_0								0x0014
#define E_CC_Low_1								0

#define E_CR_High_0								I_CR_High_0
#define E_CR_High_1								0

#define E_CR_Low_0								I_CR_Low_0
#define E_CR_Low_1								0

#define E_CV_High_0								0x0124
#define E_CV_High_1								0

#define E_CV_Low_0								0x0024
#define E_CV_Low_1								0

#define E_CP_High_0								0x0344
#define E_CP_High_1								0

#define E_CP_Low_0								0x0044
#define E_CP_Low_1								0


/*	FPGA_H_Circuit_Switch_Control_0			0x42		*/
/*	FPGA_L_Circuit_Switch_Control_0			0x4A	*/
#define VM_L_Range								0x1000

/*	Others Setting Control Command					*/
/*	FPGA_H_Circuit_Switch_Control_1			0x43		*/
/*	FPGA_L_Circuit_Switch_Control_1			0x4B	*/
/*	FPGA_Seq_Circuit_Switch_1				0x54		*/
//#define SlewRate_L_Range						0x0000	/*Bit 00~01*/
//#define SlewRate_M_Range						0x0001	/*Bit 00~01*/
//#define SlewRate_H_Range						0x0002	/*Bit 00~01*/
//#define CC_CR_CP_Response_1_10					0x0000	/*Bit 02~04*/
//#define CC_CR_CP_Response_1_5					0x0004	/*Bit 02~04*/
//#define CC_CR_CP_Response_1_2					0x0008	/*Bit 02~04*/
//#define CC_CR_CP_Response_1_1					0x0010	/*Bit 02~04*/

#define CV_Response_fast						0x0000	/*Bit 00~01*/
#define CV_Response_normal						0x0002	/*Bit 00~01*/
#define CV_Response_slow						0x0001	/*Bit 00~01*/

#define CP_Response_fast						0x0000	/*Bit 02~03*/
#define CP_Response_normal						0x0008	/*Bit 02~03*/
#define CP_Response_slow						0x0004	/*Bit 02~03*/

#define CXCV_Response_fast						0x0000	/*Bit 04*/
#define CXCV_Response_slow						0x0010	/*Bit 04*/



//#define CV_Response_L							0x0020	/*Bit 05*/
#define PAUSE_ON								0x0040	/*Bit 06*/
#define TrigOut_ON								0x0080	/*Bit 07*/
#define Jump_ON									0x0100	/*Bit 08*/
#define Jump_A_Point							0x0000	/*Bit 09~12*/
#define Jump_B_Point							0x0200	/*Bit 09~12*/
#define Jump_C_Point							0x0400	/*Bit 09~12*/
#define Jump_D_Point							0x0600	/*Bit 09~12*/
#define Jump_E_Point							0x0800	/*Bit 09~12*/
#define Jump_F_Point							0x0A00	/*Bit 09~12*/
#define Jump_G_Point							0x0C00	/*Bit 09~12*/
#define Jump_H_Point							0x0E00	/*Bit 09~12*/
#define Jump_I_Point							0x1000	/*Bit 09~12*/
#define Jump_J_Point							0x1200	/*Bit 09~12*/
#define Jump_K_Point							0x1400	/*Bit 09~12*/
#define Jump_L_Point							0x1600	/*Bit 09~12*/
#define Jump_M_Point							0x1800	/*Bit 09~12*/
#define Jump_N_Point							0x1A00	/*Bit 09~12*/
#define Jump_O_Point							0x1C00	/*Bit 09~12*/
#define Jump_P_Point							0x1E00	/*Bit 09~12*/
#if 1
#define Time_Unit_1uS							0x0000	/*Bit 13~15*/
#define Time_Unit_10uS							0x2000	/*Bit 13~15*/
#define Time_Unit_100uS							0x4000	/*Bit 13~15*/
#define Time_Unit_1mS							0x6000	/*Bit 13~15*/
#define Time_Unit_100mS							0x8000	/*Bit 13~15*/
#define Time_Unit_1S							0xA000	/*Bit 13~15*/
#define Time_Unit_10S							0xC000	/*Bit 13~15*/
#define Time_Unit_1min							0xE000	/*Bit 13~15*/
#else
#define Time_Unit_uS							0x0000	/*Bit 14~15*/
#define Time_Unit_mS							0x4000	/*Bit 14~15*/
#define Time_Unit_S								0x8000	/*Bit 14~15*/
#define Time_Unit_Min							0xC000	/*Bit 14~15*/
#endif
#define Ramp_TimeTick_2uS						0x0002
#define Ramp_TimeTick_1mS						0x0001
#define Enable_Ramp								0x8000

#define I_Cal_CV_High							I_CV_High_0
#define I_Cal_CV_Low							I_CV_High_0|VM_L_Range

#define I_Cal_CxCV_High							I_CC_High_0
#define I_Cal_CxCV_Low							I_CC_High_0|VM_L_Range

//#define H_VRANGE_IM_H_Range						1024
//#define H_VRANGE_IM_L_Range						1280
//#define L_VRANGE_IM_H_Range						1024
//#define L_VRANGE_IM_L_Range						1280

/* Others External Applied Setting Control Command  */
#define Function_ON								1
#define Protec_Ref_Adjust_ON					0x0010
#define Measure_Ment_ON							0x0020
#define Enable_Acquire_System					0x0040
#define Enable_Acquire_Sequence					0x0080
#define Acquire_Ment_00							0x0000
#define Acquire_Ment_01							0x0400
#define Acquire_Ment_10							0x0800
#define Acquire_Ment_11							0x0C00
#define Pause_ON								0x1000
#define Acquirement_Free_Run					0x0000
#define Acquirement_2K_Stop						0x0400
#define Acquirement_4K_Stop						0x0800
#define Acquirement_Stop						0x0C00

/* FPGA_On_Off_Reference_Setting */
#define Set_Load_OFF							0x0000
#define Set_Load_ON								0x0001	/*Bit 00*/
#define Set_Cx_Mode								0x0002	/*Bit 01~03*/
#define Set_Dynamic_Mode						0x0004	/*Bit 01~03*/
#define Set_Sequence_Mode						0x0006	/*Bit 01~03*/
#define Set_Run_Program_Mode					0x0008	/*Bit 01~03*/
#define Set_Protection_Ref_Adjust_ON			0x0010	/*Bit 04*/

#define Set_Trigger_Input						0x0800	/*Bit 11*/
#define Set_Wait_ON								0x1000	/*Bit 12*/
#if 1 //2014_0909
#define Set_Normal_P_Sense_Operation			0		/*Bit 13~15*/
#define Set_Calibration_AD633_X_OS				0x6000	/*Bit 13~15*/
#define Set_Calibration_AD633_Y_OS				0xA000	/*Bit 13~15*/
#define Set_Calibration_AD633_Z_OS				0xE000	/*Bit 13~15*/
#else
#define Set_Normal_P_Sense_Operation			0		/*Bit 14~15*/
#define Set_Calibration_AD633_X_OS				0x4000	/*Bit 14~15*/
#define Set_Calibration_AD633_Y_OS				0x8000	/*Bit 14~15*/
#define Set_Calibration_AD633_Z_OS				0xC000	/*Bit 14~15*/
#endif
/* FPGA_Control */
#define Clear_All_Register						0x0001	/*Bit 00*/
#define Clear_CPP_Latch							0x0002	/*Bit 01*/
#define Clear_OPP_Latch							0x0004	/*Bit 02*/
#define Clear_Rating_OCP_Latch					0x0008	/*Bit 03*/
#define Clear_OCP_Latch							0x0010	/*Bit 04*/
//#define Clear_Front_OCP_Latch					0x0020	/*Bit 05*/
#define Clear_VON_Latch							0x0040	/*Bit 06*/
#define Clear_Write_Address						0x0100	/*Bit 08*/
#define Acquire_Trigger_Pulse					0x0200	/*Bit 09*/

/* FPGA_On_Off_Latch_Setting */
#define Set_All_Prot_Limit						0x0000
#define Set_CPP_Limit							0x0000	/*Bit 00~01*/
#define Set_OPP_Limit							0x0000	/*Bit 02~03*/
#define Set_OPP_Load_OFF						0x000C	/*Bit 02~03*/
//#define Set_ROCP_Limit							0x0000	/*Bit 04~05*/
#define Set_OCP_Limit							0x0000	/*Bit 06~07*/
#define Set_OCP_Load_OFF						0x00C0	/*Bit 06~07*/
//#define Set_FOCP_Limit							0x0000	/*Bit 08~09*/
#define Set_Von_Latch_ON						0x0C00	/*Bit 10~11*/
#define Set_Von_Latch_OFF						0x0400	/*Bit 10~11*/

#define Ext_LoadON_Status						0x0001	/*Bit 00*/
#define Ext_IRange_H_Status						0x0006	/*Bit 01+Bit 02*/
#define Ext_IRange_M_Status						0x0002	/*Bit 01+Bit 02*/
#define Ext_IRange_L_Status						0x0004	/*Bit 01+Bit 02*/
#define Ext_IRange_None_Status					0x0000	/*Bit 01+Bit 02*/

#define Ext_Normal_Mode							0
#define Ext_Muilt_Mode							1

#define Ext_Alarm_Status						0x0008	/*Bit 03*/
#define	Ext_Short_Status						0x0010	/*Bit 04*/

#define Ext_Control_OFF							0
#define Ext_Control_R							0x0020	/*Bit 05*/
#define Ext_Control_V							0x0040	/*Bit 06*/
#define Ext_Control_Invert						0x0080	/*Bit 07*/
#define Ext_Control_CR_MODE						0x0100	/*Bit 08*/

#define Enable_Parallel							0x0200	/*Bit 09*/
#define Disable_Parallel						0
#define Set_H_M_IRange_In_Parallel				0x0400	/*Bit 10*/
#define Set_L_IRange_In_Parallel				0
#define Set_Parallel_Slave						0x0800	/*Bit 11*/
#define Set_Parallel_Master						0
//#define	Set_Parallel_I_Monitor_Summary			0x1000	/*Bit 12*/
#define	Set_Parallel_Ext_Trig_Input_ON			0x4000	/*Bit 14*/
#define	Set_Parallel_Ext_Trig_Input_OFF			0
#define	Set_Parallel_Ext_Load_ON_Input			0x8000	/*Bit 15*/
#define	Set_Parallel_Ext_Load_OFF_Input			0

#define External_Status_Load_ON					0x0001	/*Bit 00*/

#define External_Status_IRange_H				0x0006	/*Bit 01~02*/ //Adam_???
#define External_Status_IRange_M				0x0002	/*Bit 01~02*/
#define External_Status_IRange_L				0x0004	/*Bit 01~02*/
#define External_Status_IRange_None				0x0000	/*Bit 01~02*/

#define External_Status_Alarm					0x0008	/*Bit 03*/
#define External_Status_Branch					0x0010

#define External_Action_ISR						0x8000	/*Bit 15*/

#define Bit0									0x01
#define Bit1									0x02
#define Bit2									0x04
#define Bit3									0x08
#define Bit4									0x10
#define Bit5									0x20
#define Bit6									0x40
#define Bit7									0x80

#define Max_Value								65535
#define Default_Slew_Rate						16383

#define Min_Startup_Setting_H					50
#define Min_Startup_Setting_L					50

/*FPGA_Status Event*/
#define System_Fun_Busy						0x0002	/*Bit 01*/
#define Broken_Event						0x0008	/*Bit 03*/	/* Power Stage BROKEN detector bit(1)	*/
#define PS_OTP_Event						0x0010	/*Bit 04*/	/* Power Stage Over-Heat detector bit(1)	*/
//#define BAIS_OTP_Event						0x0020	/*Bit 05*/	/* BAIS Power Over-Heat detector bit(1)	*/
#define CPP_Prot_Event						0x0040	/*Bit 06*/
#define OPP_Prot_Event						0x0080	/*Bit 07*/
//#define Rating_OCP_Prot						0x0100	/*Bit 08*/
#define OCP_Prot_Event						0x0200	/*Bit 09*/
//#define Front_OCP_Prot						0x0400	/*Bit 10*/
#define VON_Event							0x0800	/*Bit 11*/
#define Acq4K_PTC_Done						0x4000	/*Bit 14*/
#define Acq4K_SWC_Done						0x8000	/*Bit 15*/

/*FPGA_Sequence_Mode_Set_ID*/
#define Show_Now_Run_Point					0x0FFF	/*Bit 00~11*/
#define Wait_For_Trig						0x1000	/*Bit 12*/
#define Run_Status_CX_Mode					0x2000	/*Bit 13~15*/
#define Run_Status_Dynamic					0x4000	/*Bit 13~15*/
#define Run_Status_Sequence					0x6000	/*Bit 13~15*/
#define Run_Status_Program					0x8000	/*Bit 13~15*/
#endif	// 2010_05   PRESET_KEY   SHIFT_KEY   LED_PRESET   LED_SHIFT
   
/**************************************************************************
                              End Of File
***************************************************************************/
