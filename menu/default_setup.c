/***********************************************************************
 *  This file is modified from GDS820 default_setup.c
 *
 *
 *
 ***********************************************************************/
#include "../includes.h" 
#include "../menu/head.h"
#include "../keydef.h"
//#include "../Keydef.h"
//#include "../horizontal/HUANG.H"
//#include <hard.h>
//#include <queue.h>
/**********************************************************************************/
extern ULONG DataCheckSum(unsigned char *dest,long size);



										/*	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16*/
const P3k_Timing_Str DEFAULT_PROG={	{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},	/* Memory No */
										{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	}, 	/* Run mode 	*/
										{	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1	}, 	/* On Time 	*/
										{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},	/* Off Time 	*/
										{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},	/* PF Time 	*/
										{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	}};	/* Short Time */	

const timer_set DEFAULT_TIMERSET={ 	0, 		/* Data Select */
									0, 		/* Time Select */
									2009, 	/* Year */
									1, 		/* Month */
									1, 		/* Day */
									0, 		/* Hour */
									0, 		/* Minute */
									0, 		/* Second */
									0, 		/* Reserved 1 */
									0 		/* Reserved 2 */			};
const utility DEFAULT_UTILITY={		INTERFACE_USB,		/* Interface RS232*/
									0,		/* Language */
									0,		/* USB On/Off */
									0,		/* Beep */
									0,		/*Slave Beep*/
									8,		/* Contrast Level */
									70,		/* Brightness Level */
									0,		/* Key Lock */				
									1,		/*Knob Type 0:HOLD 1:UPDATA*/
									0,		/* Load */			
									0,		/* Auto Load */
									0,		/* Auto Load Mode */
									0,		/* FAN_SPEED */
									1,		/* MEAS_SCAN */
									1,		/* Master_Alarm_Tone */
									0		/* Slave_Alarm_Tone */};

const extdgio DEFAULT_EXTDGIO={		0,		/* On & Off */
									'\xff',	/* RMEM */
									'\xff',	/* RSTATUS */
									'\xff',	/* TMEM */
									'\xff'		/* TSTATUS */			};


const rs_232 DEFAULT_RS232={		1,		/* On/Off	*/
									4,		/* Baud Rate	*/
									0,		/* DBits		*/
									0,		/* Stop		*/
									0		/* Parity		*/
									};

const gpibpar DEFAULT_GPIB={			0,		/* On/Off */
									1,		/* My Address */
									0,		/* Prn Address */
									0,
									0							};

const P3k_Prog_Str DEFAULT_RUNPROG ={
									0,		/* Program no */
									0,		/* Step no */
									0,		/* Program On or Off */	
									0,		/* Chain Start */
									{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* Program Sequence & A, B Point */
									0,      /* Reserved */
									0,      /* Reserved */
									0,      /* Reserved */
									0,      /* Reserved */
									0,		/* Repeat counter */
									0,      /* Reserved */
									/* 		Memory,				Run Mode,			Load on Time, 				*/
									/*		Load Off Time     		PF Time, 				Short Time, 			 		*/

									/* 01 */
							           {{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
							             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
							             
							  		/* 02 */
										{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

							  		/* 03 */
										{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

							  		/* 04 */
										{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

							  		/* 05 */
										{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

							  		/* 06 */
										{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

							  		/* 07 */
										{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

							  		/* 08 */
										{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

							  		/* 09 */
										{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

							  		/* 10 */
										{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

							  		/* 11 */
										{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

							  		/* 12 */
										{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

							  		/* 13 */
										{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

							  		/* 14 */
										{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

							  		/* 15 */
										{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

							  		/* 16 */
										{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}} 
									};
#if 1
const NSeq_Timing_Str DEFUATL_NSEQ_TIME ={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},// NSeq_Memo[28];
											CC_MODE,
											0,		/* ILVL:IRange Low,VRange Low */
											Switch_OFF,
											0,		/* OFF		*/
											0,		/* Infinity */
											0,
											0,
											0
										 };
const NSeq_Data_Str DEFAULT_NSEQ_DATA = {
											0, //NSeq_Value
											0, //Reserved
											{0,1,0,0,{0,0}},
											Switch_OFF, //Load_Setting
											Switch_OFF,//Ramp_Setting
											Switch_OFF, //TrigOut_Setting
											Switch_OFF //Pause_Setting
};
const F_OCP_OPP_Str DEFUAULT_OCPOPP = {
											0,//Range;			/*	IL,IM,IH 	   */
											0,//Reserved;			/*	IL,IM,IH 	   */
											1,//StartCurrWatt;		/*	*/
											1000,//EndCurrWatt;		/*	SettingValue	           */
											10,//StepCurrWatt;	/*	SettingValue	           */
											10,//StepTime;			/*   on/off				  */
											100,//TrigVolt;		/*	SettingValue	           */
											0,//DelayTime;	/*	SettingValue	           */
											0,//LastCurrWatt;
											{0,0,0,0}//Reserved1[4];
};

#endif


#if Enable_LED_function
const F_LED_Str DEFAULT_LED_SEQ = {
				{0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0},// name[16];		/*	*/ 
				0, // range;		/*	ILVL,IHVL,ILVH,IHVH 	 	*/
				0, // mode;			/*	Vo,Io / Vo,Io,Rcoff / Vo,Io,Rd / Vo,Io,Vd / Vd,Rd,pcs	*/	
				5, // response;		/* */
				0, // reserved1;	/*	*/	
				200, // vo;			/*	*/
				100, // vf;			/*	*/
				100, // io;			/*	*/
				10, // rd;			/*	*/
				5000, // rdcoff;		/*	*/
				1, // pcs;			/*	*/
				0, // vfCnt;
				0, // vdCnt;
				0, // ir;
				0, // c;
				{0,0} //reserved2[2];
				
};
const F_LED_Str DEFAULT_CLED_SEQ = {
				{0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0},// name[16];		/*	*/ 
				0, // range;		/*	ILVL,IHVL,ILVH,IHVH 	 	*/
				0, // mode;			/*	Vo,Io / Vo,Io,Rcoff / Vo,Io,Rd / Vo,Io,Vd / Vd,Rd,pcs	*/	
				5, // response;		/* */
				0, // reserved1;	/*	*/	
				6000, // vo;			/*	*/
				0, // vf;			/*	*/
				5000, // io;			/*	*/
				0, // rd;			/*	*/
				2000, // rdcoff;		/*	*/
				0, // pcs;			/*	*/
				0, // vfCnt;
				0, // vdCnt;
				0.007026, // ir;
				1.655037, // c;
				{0,0} //reserved2[2];
				
};

#endif
void Load_Default_Interface(char mode)
{	
	/* mode:0      Recall Default Interface		*/
	/* mode:1 No Recall Default Interface		*/
	char INTERFACE_temp;

	/* Interface Init */	
	if(mode)	/* No Recall Default Interface */
	{
		INTERFACE_temp	= UTILITY.INTERFACE;
		UTILITY			= DEFAULT_UTILITY;
		UTILITY.INTERFACE	= INTERFACE_temp;
	}
	else		/* Recall Default Interface */
	{

		UTILITY	= DEFAULT_UTILITY;
		UTILITY.AutoLoadOffMode = 1;
		UTILITY.AutoLoadOffRange= 1;
		RS232	= DEFAULT_RS232;
		GPIBPAR	= DEFAULT_GPIB;
		if(!(SYSType&GPIB_CONNECTED))
			GPIBPAR.ONOFF=2;
	}
}

void LoadDefaultProc(char mode)
{
	/* mode:0 system Recall Default	*/
	/* mode:1 User Recall Default	*/
	UWORD i,j;
	
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Memory_Str	Default_Memory_Data;
	P3k_Backup_Str	 Default_Backup;
	Backup_Setup_Str Default_Setup;

	/* User Recall Default */
	
	/* Run program init */
	p3k_Chan_PROG = p3k_Disp_PROG = DEFAULT_RUNPROG;

	DispMode		= DispMode_BROWSE_ITEMS;
	M_num			= P_CC;
	DispScrEndCT	= 2;

	Data_tmp->CURRMODE			= CC_MODE;
	Data_tmp->SPEC				= Switch_OFF;
	Data_tmp->SPECTYPE			= GONG_Value;
	Data_tmp->P_F_Delay 		= 0;
	Data_tmp->Coarse			= 0;
	Data_tmp->Parallel_Unit 	= 0;
	Data_tmp->IRange			= HIGH_RANGE;
	Data_tmp->VRange			= VRange_High;
	Data_tmp->Load_Type			= Normal_Load;

	/*CC Setting*/
	Data_tmp->CC.STADYNA	= 0;
	Data_tmp->CC.ABSELECT	= 0;
	Data_tmp->CC.RESPONSE	= 0;
	Data_tmp->CC.CXCV_RESPOSNE = 0;
	
	Default_Memory_Data.MODE		= CC_MODE;
	Default_Memory_Data.STATUS		= 0;			/*+CV OFF, Static, GO-NG Off, GO-NG Value, A Value, Response Slow, VRange Low*/
	Default_Memory_Data.IRange		= HIGH_RANGE;
	Default_Memory_Data.P_F_Delay	= 0;
	Default_Memory_Data.CV_VALUE	= (ptrMODEL_TYPE->CV)[0].Def;
	Default_Memory_Data.RESPONSE_VALUE	= 0;
	Default_Memory_Data.VALUE1		= (ptrMODEL_TYPE->CC)[10].Def;
	Default_Memory_Data.VALUE2		= (ptrMODEL_TYPE->CC)[11].Def;
	Default_Memory_Data.SLEWRATEUP	= (ptrMODEL_TYPE->CC)[12].Def;
	Default_Memory_Data.SLEWRATEDN	= (ptrMODEL_TYPE->CC)[13].Def;
	Default_Memory_Data.TIME1		= 0;
	Default_Memory_Data.TIME2		= 0;
	Default_Memory_Data.Reserved2	= 0;
	Default_Memory_Data.CENTERVAL	= (ptrMODEL_TYPE->CC_SPEC)[0].Def;
	Default_Memory_Data.HIGHVAL 	= (ptrMODEL_TYPE->CC_SPEC)[1].Def;
	Default_Memory_Data.LOWVAL		= (ptrMODEL_TYPE->CC_SPEC)[2].Def;
	Default_Memory_Data.HIPCET		= 1000;
	Default_Memory_Data.LOWPCET 	= 1000;
	Default_Memory_Data.T1_RANGE	= 0;
	Default_Memory_Data.T2_RANGE	= 0;
	Default_Memory_Data.SLEWRATEUP_RANGE = 2;
	Default_Memory_Data.SLEWRATEDN_RANGE = 2;

	for(i=LOW_RANGE ; i<=HIGH_RANGE ; i++)
	{
		Data_tmp->CC.STA[i].VALUE1				= (ptrMODEL_TYPE->CC)[0+(i*10)].Def;
		Data_tmp->CC.STA[i].VALUE2				= (ptrMODEL_TYPE->CC)[1+(i*10)].Def;
		Data_tmp->CC.STA[i].SLEWRATEUP			= (ptrMODEL_TYPE->CC)[2+(i*10)].Def;
		Data_tmp->CC.STA[i].SLEWRATEDN			= (ptrMODEL_TYPE->CC)[3+(i*10)].Def;
		Data_tmp->CC.STA[i].SLEWRATEUP_RANGE	= 2;
		Data_tmp->CC.STA[i].SLEWRATEDN_RANGE	= 2;
		Data_tmp->CC.DYNA[i].LEVEL1 			= (ptrMODEL_TYPE->CC)[4+(i*10)].Def;
		Data_tmp->CC.DYNA[i].LEVEL2 			= (ptrMODEL_TYPE->CC)[5+(i*10)].Def;
		Data_tmp->CC.DYNA[i].SLEWRATEUP 		= (ptrMODEL_TYPE->CC)[6+(i*10)].Def;
		Data_tmp->CC.DYNA[i].SLEWRATEDN 		= (ptrMODEL_TYPE->CC)[7+(i*10)].Def;
		Data_tmp->CC.DYNA[i].TIME1				= 30000;
		Data_tmp->CC.DYNA[i].TIME2				= 30000;
		Data_tmp->CC.DYNA[i].T1_RANGE			= 1;
		Data_tmp->CC.DYNA[i].T2_RANGE			= 1;
		Data_tmp->CC.DYNA[i].SLEWRATEUP_RANGE	= 2;
		Data_tmp->CC.DYNA[i].SLEWRATEDN_RANGE	= 2;
		Data_tmp->CC.DYNA[i].Level_Percent		= 500;
		Data_tmp->CC.DYNA[i].Duty				= 500;
		Data_tmp->CC.DYNA[i].Frequency			= 100;
		Data_tmp->CC.DYNA[i].Frequency_Range	= 0;
		Data_tmp->CC.VALUE_STEP[i]				= 100;
	}

	/*CR Setting*/	
	Data_tmp->CR.STADYNA	= 0;
	Data_tmp->CR.ABSELECT	= 0;
	Data_tmp->CR.RESPONSE	= 0;
	Data_tmp->CR.CXCV_RESPOSNE = 0;

	for(i=LOW_RANGE ; i<=HIGH_RANGE ; i++)
	{
		Data_tmp->CR.STA[i].VALUE1				= (ptrMODEL_TYPE->CR)[0+(i*10)].Def;
		Data_tmp->CR.STA[i].VALUE2				= (ptrMODEL_TYPE->CR)[1+(i*10)].Def;
		Data_tmp->CR.STA[i].SLEWRATEUP			= (ptrMODEL_TYPE->CR)[2+(i*10)].Def;
		Data_tmp->CR.STA[i].SLEWRATEDN			= (ptrMODEL_TYPE->CR)[3+(i*10)].Def;
		Data_tmp->CR.STA[i].SLEWRATEUP_RANGE	= 2;
		Data_tmp->CR.STA[i].SLEWRATEDN_RANGE	= 2;
		Data_tmp->CR.DYNA[i].LEVEL1 			= (ptrMODEL_TYPE->CR)[4+(i*10)].Def;
		Data_tmp->CR.DYNA[i].LEVEL2 			= (ptrMODEL_TYPE->CR)[5+(i*10)].Def;
		Data_tmp->CR.DYNA[i].SLEWRATEUP 		= (ptrMODEL_TYPE->CR)[6+(i*10)].Def;
		Data_tmp->CR.DYNA[i].SLEWRATEDN 		= (ptrMODEL_TYPE->CR)[7+(i*10)].Def;
		Data_tmp->CR.DYNA[i].TIME1				= 30000;
		Data_tmp->CR.DYNA[i].TIME2				= 30000;
		Data_tmp->CR.DYNA[i].T1_RANGE			= 1;
		Data_tmp->CR.DYNA[i].T2_RANGE			= 1;		
		Data_tmp->CR.DYNA[i].SLEWRATEUP_RANGE	= 2;
		Data_tmp->CR.DYNA[i].SLEWRATEDN_RANGE	= 2;
		Data_tmp->CR.DYNA[i].Level_Percent		= 500;
		Data_tmp->CR.DYNA[i].Duty				= 500;
		Data_tmp->CR.DYNA[i].Frequency			= 100;
		Data_tmp->CR.DYNA[i].Frequency_Range	= 0;		
		Data_tmp->CR.VALUE_STEP[i]				= 100;		
	}

	/*CV Setting*/
	Data_tmp->CV.STADYNA	= 0;
	Data_tmp->CV.ABSELECT	= 0;
	Data_tmp->CV.RESPONSE	= 1;
	
	for(i=LOW_RANGE ; i<=HIGH_RANGE ; i++)
	{
		Data_tmp->CV.STA[i].VALUE1				= (ptrMODEL_TYPE->CV)[0+(i*3)].Def;
		Data_tmp->CV.STA[i].VALUE2				= (ptrMODEL_TYPE->CV)[1+(i*3)].Def;
		Data_tmp->CV.STA[i].CURRENTLIMIT		= (ptrMODEL_TYPE->CV)[2+(i*3)].Def;
		Data_tmp->CV.VALUE_STEP[i]				= 100;
		Data_tmp->CV.STA[i].SLEWRATEUP			= (ptrMODEL_TYPE->CP)[2+(i*10)].Def;
		Data_tmp->CV.STA[i].SLEWRATEDN			= (ptrMODEL_TYPE->CP)[3+(i*10)].Def;
		Data_tmp->CV.STA[i].SLEWRATEUP_RANGE	= 0;
		Data_tmp->CV.STA[i].SLEWRATEDN_RANGE	= 0;
		Data_tmp->CV.DYNA[i].SLEWRATEUP 		= (ptrMODEL_TYPE->CP)[6+(i*10)].Def;
		Data_tmp->CV.DYNA[i].SLEWRATEDN 		= (ptrMODEL_TYPE->CP)[7+(i*10)].Def;
		Data_tmp->CV.DYNA[i].SLEWRATEUP_RANGE	= 0;
		Data_tmp->CV.DYNA[i].SLEWRATEDN_RANGE	= 0;
	}

	/*CP Setting*/
	Data_tmp->CP.STADYNA	= 0;
	Data_tmp->CP.ABSELECT	= 0;
	Data_tmp->CP.RESPONSE	= 0;
	Data_tmp->CP.CXCV_RESPOSNE = 0;
	/*CP Mode*/
	for(i=LOW_RANGE ; i<=HIGH_RANGE ; i++)
	{		
		Data_tmp->CP.STA[i].VALUE1				= (ptrMODEL_TYPE->CP)[0+(i*10)].Def;
		Data_tmp->CP.STA[i].VALUE2				= (ptrMODEL_TYPE->CP)[1+(i*10)].Def;
		Data_tmp->CP.STA[i].SLEWRATEUP			= (ptrMODEL_TYPE->CP)[2+(i*10)].Def;
		Data_tmp->CP.STA[i].SLEWRATEDN			= (ptrMODEL_TYPE->CP)[3+(i*10)].Def;
		Data_tmp->CP.STA[i].SLEWRATEUP_RANGE	= 0;
		Data_tmp->CP.STA[i].SLEWRATEDN_RANGE	= 0;
		Data_tmp->CP.DYNA[i].LEVEL1 			= (ptrMODEL_TYPE->CP)[4+(i*10)].Def;
		Data_tmp->CP.DYNA[i].LEVEL2 			= (ptrMODEL_TYPE->CP)[5+(i*10)].Def;
		Data_tmp->CP.DYNA[i].SLEWRATEUP 		= (ptrMODEL_TYPE->CP)[6+(i*10)].Def;
		Data_tmp->CP.DYNA[i].SLEWRATEDN 		= (ptrMODEL_TYPE->CP)[7+(i*10)].Def;
		Data_tmp->CP.DYNA[i].TIME1				= 30000;
		Data_tmp->CP.DYNA[i].TIME2				= 30000;
		Data_tmp->CP.DYNA[i].T1_RANGE			= 1;
		Data_tmp->CP.DYNA[i].T2_RANGE			= 1;		
		Data_tmp->CP.DYNA[i].SLEWRATEUP_RANGE	= 0;
		Data_tmp->CP.DYNA[i].SLEWRATEDN_RANGE	= 0;
		Data_tmp->CP.DYNA[i].Level_Percent		= 500;
		Data_tmp->CP.DYNA[i].Duty				= 500;
		Data_tmp->CP.DYNA[i].Frequency			= 100;
		Data_tmp->CP.DYNA[i].Frequency_Range	= 0;		
		Data_tmp->CP.VALUE_STEP[i]				= 100;
	}

	/*CC SPEC Mode*/
	for(i=LOW_RANGE ; i<=HIGH_RANGE ; i++)
	{
		Data_tmp->CC.STA[i].CENTERVAL		= (ptrMODEL_TYPE->CC_SPEC)[0].Def;
		Data_tmp->CC.STA[i].HIGHVAL 		= (ptrMODEL_TYPE->CC_SPEC)[1].Def;
		Data_tmp->CC.STA[i].LOWVAL			= (ptrMODEL_TYPE->CC_SPEC)[2].Def;		
		Data_tmp->CC.STA[i].HIPCET			= 1000;
		Data_tmp->CC.STA[i].LOWPCET 		= 1000;
		Data_tmp->CC.DYNA[i].CENTERVAL		= (ptrMODEL_TYPE->CC_SPEC)[0].Def;
		Data_tmp->CC.DYNA[i].HIGHVAL		= (ptrMODEL_TYPE->CC_SPEC)[1].Def;
		Data_tmp->CC.DYNA[i].LOWVAL 		= (ptrMODEL_TYPE->CC_SPEC)[2].Def;
		Data_tmp->CC.DYNA[i].HIPCET 		= 1000;
		Data_tmp->CC.DYNA[i].LOWPCET		= 1000;
	}
	
	/*CR SPEC Mode*/
	for(i=LOW_RANGE ; i<=HIGH_RANGE ; i++)
	{
		Data_tmp->CR.STA[i].CENTERVAL		= (ptrMODEL_TYPE->CR_SPEC)[0].Def;
		Data_tmp->CR.STA[i].HIGHVAL 		= (ptrMODEL_TYPE->CR_SPEC)[1].Def;
		Data_tmp->CR.STA[i].LOWVAL			= (ptrMODEL_TYPE->CR_SPEC)[2].Def;		
		Data_tmp->CR.STA[i].HIPCET			= 1000;
		Data_tmp->CR.STA[i].LOWPCET 		= 1000;
		Data_tmp->CR.DYNA[i].CENTERVAL		= (ptrMODEL_TYPE->CR_SPEC)[0].Def;
		Data_tmp->CR.DYNA[i].HIGHVAL		= (ptrMODEL_TYPE->CR_SPEC)[1].Def;
		Data_tmp->CR.DYNA[i].LOWVAL 		= (ptrMODEL_TYPE->CR_SPEC)[2].Def;
		Data_tmp->CR.DYNA[i].HIPCET 		= 1000;
		Data_tmp->CR.DYNA[i].LOWPCET		= 1000;
	}

	/*CV SPEC Mode*/
	for(i=LOW_RANGE ; i<=HIGH_RANGE ; i++)
	{
		Data_tmp->CV.STA[i].CENTERVAL		= (ptrMODEL_TYPE->CV_SPEC)[0].Def;
		Data_tmp->CV.STA[i].HIGHVAL 		= (ptrMODEL_TYPE->CV_SPEC)[1].Def;
		Data_tmp->CV.STA[i].LOWVAL			= (ptrMODEL_TYPE->CV_SPEC)[2].Def;		
		Data_tmp->CV.STA[i].HIPCET			= 1000;
		Data_tmp->CV.STA[i].LOWPCET 		= 1000;
	}	

	/*CP SPEC Mode*/
	for(i=LOW_RANGE ; i<=HIGH_RANGE ; i++)
	{
		Data_tmp->CP.STA[i].CENTERVAL		= (ptrMODEL_TYPE->CP_SPEC)[0].Def;
		Data_tmp->CP.STA[i].HIGHVAL 		= (ptrMODEL_TYPE->CP_SPEC)[1].Def;
		Data_tmp->CP.STA[i].LOWVAL			= (ptrMODEL_TYPE->CP_SPEC)[2].Def;
		Data_tmp->CP.STA[i].HIPCET			= 1000;
		Data_tmp->CP.STA[i].LOWPCET 		= 1000;

		Data_tmp->CP.DYNA[i].CENTERVAL		= (ptrMODEL_TYPE->CP_SPEC)[0].Def;
		Data_tmp->CP.DYNA[i].HIGHVAL		= (ptrMODEL_TYPE->CP_SPEC)[1].Def;
		Data_tmp->CP.DYNA[i].LOWVAL 		= (ptrMODEL_TYPE->CP_SPEC)[2].Def;
		Data_tmp->CP.DYNA[i].HIPCET 		= 1000;
		Data_tmp->CP.DYNA[i].LOWPCET		= 1000;
	}
	
	/*PROT*/		
	Data_tmp->PROT.OCP[LOW_RANGE]					= (ptrMODEL_TYPE->PROT)[PROT_OCP_L].Def;
	//Data_tmp->PROT.OCP[1]					= (ptrMODEL_TYPE->PROT)[1].Def;
	Data_tmp->PROT.OCP[HIGH_RANGE]					= (ptrMODEL_TYPE->PROT)[PROT_OCP_H].Def;

	Data_tmp->PROT.OPP[LOW_RANGE]					= (ptrMODEL_TYPE->PROT)[PROT_OPP_L].Def; 
	//Data_tmp->PROT.OPP[1]					= (ptrMODEL_TYPE->PROT)[4].Def;
	Data_tmp->PROT.OPP[HIGH_RANGE]					= (ptrMODEL_TYPE->PROT)[PROT_OPP_H].Def;

	Data_tmp->PROT.UVP_VOLT[LOW_RANGE]				= (ptrMODEL_TYPE->PROT)[PROT_UVP_L].Def;
	Data_tmp->PROT.UVP_VOLT[HIGH_RANGE]				= (ptrMODEL_TYPE->PROT)[PROT_UVP_H].Def;
	Data_tmp->PROT.OVP_VOLT[LOW_RANGE]				= (ptrMODEL_TYPE->PROT)[PROT_OVP_L].Def;
	Data_tmp->PROT.OVP_VOLT[HIGH_RANGE]				= (ptrMODEL_TYPE->PROT)[PROT_OVP_H].Def;
	Data_tmp->PROT.OCP_SET					= 1;
	Data_tmp->PROT.OPP_SET					= 1;
#if Enable_Ring_Count
	Data_tmp->PROT.UVP_Tone_len 			= 1; //OFF
	Data_tmp->PROT.SEQ_Tone_len 			= 1; //OFF
#endif

	/*UTILITY*/
	Data_tmp->UTILITY.LOADTIME				= 0;
	UTILITY.Master_Alarm_Tone  				= 0;
	UTILITY.Master_NG_Tone					= 0;
	UTILITY.UnReg_Alarm_Tone				= 0;

	/*CONF*/
	Data_tmp->CONF.VON_LATCH 					= 1;
	Data_tmp->CONF.CH_Control					= 0;
	Data_tmp->CONF.VON_VOLT[0]					= (ptrMODEL_TYPE->CONF)[0].Def;
	Data_tmp->CONF.VON_VOLT[1]					= (ptrMODEL_TYPE->CONF)[1].Def;
	Data_tmp->CONF.SOFT_START					= 0;
	Data_tmp->CONF.Short_Key						= 0;
#if Enable_Short_invalidate	
	Data_tmp->CONF.Short_Fun						= 1;
	Data_tmp->CONF.Short_Satety					= 1;
#endif	
	Data_tmp->CONF.Ext_Setting.Control			= 0;
	if(mode==0)Data_tmp->CONF.Ext_Setting.LoadOn_IN		= 0;
	if(mode==0)Data_tmp->CONF.Ext_Setting.MultilPara		= 0;

	Data_tmp->CONF.D_Von_Delay					= 2000;
	//Data_tmp->CONF.D_Von_Delay_CR				= 5000;
	Data_tmp->CONF.Dyna_Level					= 0;
	Data_tmp->CONF.Dyna_Time						= 0;
	Data_tmp->CONF.Knob_Status					= 0;
	Data_tmp->CONF.D_CR_Unit						= 1;
	Data_tmp->CONF.Count_Time					= 0;
	Data_tmp->CONF.Cut_Off_Time_s				= 0;
	Data_tmp->CONF.Cut_Off_Time_m				= 0;
	Data_tmp->CONF.Cut_Off_Time_h				= 0;
	Data_tmp->CONF.Cut_Off_cnt					= 0;
	Data_tmp->CONF.cut_off_time_total			= 0;
	Data_tmp->CONF.Response						= 0;
	if(mode!=Sync_Recall_Default){		
		Data_tmp->CONF.Para_Data.Mode 			= 0;
	}
	//Data_tmp->CONF.Para_Data.Booster_Number  	= 0;
	//Data_tmp->CONF.Para_Data.Parallel_Number 	= 0;
#if 1
	Data_tmp->CONF.Para_Data.TrigInDelay  		= 0;
	Data_tmp->CONF.Para_Data.TrigOutWidth		= 20;
//	Data_tmp->CONF.Para_Data.Parallel_Number 	= 0;
	Data_tmp->CONF.Para_Data.TrigOut				= 1;
	Data_tmp->CONF.Para_Data.TrigIN				= 0;
#endif
	Data_tmp->CONF.Para_Data.Number			 	= 0;
	Data_tmp->CONF.D_CR_Unit				 		= 1;
	Data_tmp->CONF.CV_Func_En					= 0;
#if 1 //2014/1106
	Data_tmp->CONF.Memory_Recall					= 1;
#if Enable_Func_DisTime
		Data_tmp->CONF.T_count_up = 1;
#endif

	p3k_File_Utility_BAR.Mem_Data_Type			= 0;
	//MEMORY_SAVE_FLAG 							= M_Memory_Save_Ok;
	p3k_File_Utility_BAR.MEMORY_ADDR 			= 0;
	p3k_File_Utility_BAR.SMEMORY_ADDR 			= 0;
	p3k_File_Utility_BAR.PRE_MEMORY_ADDR		= 0;
	

#endif
#if 1
		//
		Default_Backup.CURRMODE = CC_MODE;
		Default_Backup.SPEC = Switch_OFF;
		Default_Backup.SPECTYPE = GONG_Value;
		Default_Backup.IRange = HIGH_RANGE;
		Default_Backup.VRange = VRange_High;
		Default_Backup.Load_Type = Normal_Load;
		Default_Backup.UTILITY = P3k_Chan_Data.UTILITY;
		Default_Backup.PROT = P3k_Chan_Data.PROT;
		Default_Backup.CONF = P3k_Chan_Data.CONF;
		Default_Backup.INFO= P3k_Chan_Data.INFO;
		Default_Backup.CC = P3k_Chan_Data.CC;
		Default_Backup.CR = P3k_Chan_Data.CR	;
		Default_Backup.CV = P3k_Chan_Data.CV;
		Default_Backup.CP = P3k_Chan_Data.CP;
		Default_Backup.P_F_Delay = P3k_Chan_Data.P_F_Delay;
		Default_Backup.Coarse = P3k_Chan_Data.Coarse;
		Default_Backup.Parallel_Unit= P3k_Chan_Data.Parallel_Unit;
	
		for(i=0; i<10; i++) Default_Backup.P_DATA[i]= Default_Memory_Data;
	
		Default_Setup.Data_Ready = 200;
		Default_Setup.DispMode = DispMode_BROWSE_ITEMS;
		Default_Setup.M_num = CC_MODE;
		Default_Setup.DispScrCT = 0;
		Default_Setup.MACHTYPE=P3k_Chan_Data.INFO.MACHTYPE;
		Default_Setup.F_Version = File_Version;
		Default_Setup.M_Number = Machine_Number;
		Default_Setup.M_Version_M = Main_Version;
		Default_Setup.M_Version_S = Sub_Version;
		Default_Setup.P3k_Backup_Data = Default_Backup;
		Default_Setup.CheckSum = DataCheckSum((UBYTE *)&Default_Setup,sizeof(Default_Setup));
	
		for(i=0; i<100; i++)Backup_Setup_Data[i]=Default_Setup;
	
#endif

	FPGA_ISR_Data.ISR_Load	= 1;
	SCPI_Freeze_menu = 0;
	G_StatusFlag = 0;
	if(mode)
		return;
	/* system Recall Default */
	TIMERSET	= DEFAULT_TIMERSET;

	for(i=0 ; i<10 ; i++)
		Data_tmp->P_DATA[i] = Default_Memory_Data;
	for(i=0 ; i<256 ; i++)
		Data_tmp->M_DATA[i] = Default_Memory_Data;	
	DGIOCtrlFlag &= (~EXT_Frame_CONT_KB);

	/*Normal Seq*/
	P3k_NSeq_Data.NSeq_Enable	= 0;
	P3k_NSeq_Data.NSeq_Number	= 0;
	P3k_NSeq_Data.NSeq_Start	= 0;

	for(i=0 ; i<10 ; i++)
	{
		P3k_NSeq_Data.NSeq_Seq[i] = DEFUATL_NSEQ_TIME;
#if 0
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
#endif
		for(j=0 ; j<1024 ; j++)
		{
#if 1
	
			P3k_NSeq_Data.NSeq_Step[i][j]=DEFAULT_NSEQ_DATA;
#else
			P3k_NSeq_Data.NSeq_Step[i][j].NSeq_Value				= 0;
			P3k_NSeq_Data.NSeq_Step[i][j].NSeq_Time.Hour			= 0;
			P3k_NSeq_Data.NSeq_Step[i][j].NSeq_Time.Minute			= 0;
			P3k_NSeq_Data.NSeq_Step[i][j].NSeq_Time.Second			= 0;
			P3k_NSeq_Data.NSeq_Step[i][j].NSeq_Time.MilliSecond 	= 1;
			P3k_NSeq_Data.NSeq_Step[i][j].Load_Setting				= Switch_OFF;
			P3k_NSeq_Data.NSeq_Step[i][j].Ramp_Setting				= Switch_OFF;
			P3k_NSeq_Data.NSeq_Step[i][j].TrigOut_Setting			= Switch_OFF;
			P3k_NSeq_Data.NSeq_Step[i][j].Pause_Setting 			= Switch_OFF;
#endif
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

	for(i=0 ; i<1024 ; i++)
	{
		P3k_FSeq_Data.FSeq_Step[i].FSeq_Value		= 0;
		P3k_FSeq_Data.FSeq_Step[i].TrigOut_Setting	= Switch_OFF;
	}
#if Enable_OCP_function
	P3K_OCP_Data.CurrTemp = 0;
	P3K_OCP_Data.Data_Ready = 200;
	P3K_OCP_Data.Complete = 0;
	P3K_OCP_Data.UpdataFlag  = 0;
	for(i=0;i<12;i++){
#if 1
		P3K_OCP_Data.Seq[i] = DEFUAULT_OCPOPP;		
#else
		P3K_OCP_Data.Seq[i].Range = 0;
		P3K_OCP_Data.Seq[i].StartCurrWatt = 1;
		P3K_OCP_Data.Seq[i].EndCurrWatt = 1000;
		P3K_OCP_Data.Seq[i].StepCurrWatt = 1;
		P3K_OCP_Data.Seq[i].StepTime = 10;
		P3K_OCP_Data.Seq[i].DelayTime = 0;
		P3K_OCP_Data.Seq[i].TrigVolt = 250;
		P3K_OCP_Data.Seq[i].LastCurrWatt = 0;
#endif		
	}
#endif	
#if Enable_OPP_function
	P3K_OPP_Data.CurrTemp = 0;
	P3K_OPP_Data.Data_Ready = 200;
	P3K_OPP_Data.Complete = 0;
	P3K_OPP_Data.UpdataFlag  = 0;
	for(i=0;i<12;i++){
#if 1
		P3K_OPP_Data.Seq[i] = DEFUAULT_OCPOPP;	
#else
		P3K_OPP_Data.Seq[i].Range = 0;
		P3K_OPP_Data.Seq[i].StartCurrWatt = 1;
		P3K_OPP_Data.Seq[i].EndCurrWatt = 1000;
		P3K_OPP_Data.Seq[i].StepCurrWatt = 10;
		P3K_OPP_Data.Seq[i].StepTime = 10;
		P3K_OPP_Data.Seq[i].DelayTime = 0;
		P3K_OPP_Data.Seq[i].TrigVolt = 100;
		P3K_OPP_Data.Seq[i].LastCurrWatt = 0;
#endif		
	}
#endif
#if Enable_LED_function
	P3k_FLed_Disp.currTemp = 0;
	P3k_FLed_Disp.dataReady = 0;
	P3k_FLed_Disp.complete = 0; 
	P3k_FLed_Disp.checksum = 0x55;
	P3k_CLed_Disp.currTemp = 0;
	P3k_CLed_Disp.dataReady = 0;
	P3k_CLed_Disp.complete = 0; 
	P3k_CLed_Disp.checksum = 0x55;
	for(i=0;i<12;i++){
		P3k_FLed_Disp.seq[i] = DEFAULT_LED_SEQ;
		P3k_CLed_Disp.seq[i] = DEFAULT_CLED_SEQ;
	}
#endif

#if Enable_Battery_Discharge	
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
#endif

}


