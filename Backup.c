#include <includes.h>
#include "keydef.h"
extern UBYTE WriteOnBoardFlash(long Start_Page, unsigned char *Data_Point, long Data_Size);
extern void Menu_Message(char *Message,int x,int y);
extern void Update_Panel(void);
extern void CountinueArrayRead512(long total_addr, unsigned char *ptr, long size);
extern void Debug_printf(char *Message);
extern char FRAM_WRITE_MEM(unsigned char *ptr, long size);
extern char FRAM_READ_MEM(unsigned char *,long);
extern void EDGIO_Control( char mode, char onoff);

ULONG DataCheckSum(unsigned char *dest,long size)
{
	UBYTE CheckSum_Start_addr;
	ULONG CheckSum_Total;
	long i;

	CheckSum_Total=0;
	CheckSum_Start_addr=4;

	for(i=CheckSum_Start_addr ; i<size ; i++)
		CheckSum_Total += *(dest + i);
	CheckSum_Total = CheckSum_Total+1; //PEL1000 Adam_test	 1
	return(CheckSum_Total);
}

#define Read_DataFlash		0
#define Write_DataFlash		1

#define Type_CalData		0
#define Type_ProgData		1
#define Type_NSeqData		2
#define Type_FSeqData		3
#define Type_DefData		4
#define Type_SetupData		5
#define Type_APPData		6
#define Type_SerialNumber	7
#define Type_funcOCP		8
#define Type_funcOPP		9
#define Type_funcLED		10


volatile UBYTE BackupBusyFlag = 0;
void DataFlash_Save_Recall(UBYTE SelectMode,long DataPage,long DataSize,UBYTE *DataPtr)
{
	UWORD Backup_TimeOut = 300;

	if(SelectMode) {
		while(BackupBusyFlag) {
			OSTimeDly(1);
			Backup_TimeOut--;
			if(Backup_TimeOut==0) {
				printf("BackupMasterMemo TimeOut\n");
				break;
			}
		}
		BackupBusyFlag = 1;
		if( WriteOnBoardFlash(DataPage,DataPtr,DataSize) == 0 ) {
			Menu_Message(" Write Data Flash Error!! ",50,210);
			CtrlFlag1 |= Disp_Middle_Message;
			DMA_Update_Flag = 1;
			Update_Panel();
			OSTimeDly(200);
		}
		BackupBusyFlag = 0;
	} else
		CountinueArrayRead512((DataPage*512),DataPtr,DataSize);
}


#define Page_Size 512;
void DataFlash_Function(UBYTE SelectMode,UBYTE Data_Type)
{
	long Input_DataPage,Input_DataSize;
	UBYTE *Input_DataPtr;
	unsigned char USB_File_Type;

	p3k_file_util_str *File_Ptr = &p3k_File_Utility_BAR;

	USB_File_Type = p3k_File_Utility_BAR.USB_Data_Type;

	/*SelectMode = 0 Read  DataFlash*/
	/*SelectMode = 1 Write DataFlash*/

	if(Type_SetupData == Data_Type) {
		if(USB_File_Type == F_Setup_Data) {
			Input_DataPage = 2600;								/* 2600~3050 */
			Input_DataSize = sizeof(Backup_Setup_Data);
			Input_DataPtr  = (UBYTE *)&Backup_Setup_Data;		/* 171520 Bytes /335 Page */
		} else {
			Input_DataPage = 2600 + (File_Ptr->SMEMORY_ADDR * 4);
			Input_DataSize = sizeof(Backup_Setup_Data[File_Ptr->SMEMORY_ADDR]);
			Input_DataPtr = (unsigned char *)&Backup_Setup_Data[File_Ptr->SMEMORY_ADDR];
		}
#if 0
		Input_DataPage = 2600;								/* 2600~2935 */
		Input_DataSize = sizeof(Backup_Setup_Data);
		Input_DataPtr  = (UBYTE *)&Backup_Setup_Data;		/* 171520 Bytes /335 Page */
#endif
	} else if(Type_CalData==Data_Type) {
		Input_DataPage = 3200;								/*3200~3201*/
		Input_DataSize = sizeof(p3k_Cal_data);
		Input_DataPtr  = (UBYTE *)&p3k_Cal_data;			/*1024 Byte/2 Page*/
	} else if(Type_APPData==Data_Type) {
		Input_DataPage = 3203;								/*3203~3203*/
		Input_DataSize = sizeof(Backup_APP_Data);
		Input_DataPtr  = (UBYTE *)&Backup_APP_Data;			/*512 Byte/1 Page*/
	} else if(Type_ProgData==Data_Type) {
		Input_DataPage = 3210;								/*3210~3238*/
		Input_DataSize = sizeof(P3k_Backup_Prog_Data);
		Input_DataPtr  = (UBYTE *)&P3k_Backup_Prog_Data;	/*14848 Byte/29 Page*/
	} else if(Type_NSeqData==Data_Type) {
		Input_DataPage = 3240;								/*3240~3278*/
		Input_DataSize = sizeof(P3k_Backup_NSeq_Data);
		Input_DataPtr  = (UBYTE *)&P3k_Backup_NSeq_Data;	/*19968 Byte/39 Page*/
	} else if(Type_FSeqData==Data_Type) {
		Input_DataPage = 3280;								/*3280~3298*/
		Input_DataSize = sizeof(P3k_Backup_FSeq_Data);
		Input_DataPtr  = (UBYTE *)&P3k_Backup_FSeq_Data;	/*9728 Byte/19 Page*/
	} else if(Type_DefData==Data_Type) {
		Input_DataPage = 3300;								/*3300~3308*/
		Input_DataSize = sizeof(Backup_Default_Data);
		Input_DataPtr  = (UBYTE *)&Backup_Default_Data;		/*4608 Byte/9 Page*/
	} else if(Type_SerialNumber==Data_Type) {
		Input_DataPage = 3310;								/*3310~3311*/
		Input_DataSize = sizeof(P3k_Backup_SN);
		Input_DataPtr  = (UBYTE *)&P3k_Backup_SN;		/*512 Byte/1 Page*/
#if Enable_OCP_function
	} else if(Type_funcOCP==Data_Type) {
		Input_DataPage = 3311;								/*3311~?*/
		Input_DataSize = sizeof(P3K_OCP_Data);
		Input_DataPtr  = (UBYTE *)&P3K_OCP_Data;		/*512 Byte/1 Page*/	
#endif
#if Enable_OPP_function
	} else if(Type_funcOPP==Data_Type) {
		Input_DataPage = 3312;								/*3311~?*/
		Input_DataSize = sizeof(P3K_OPP_Data);
		Input_DataPtr  = (UBYTE *)&P3K_OPP_Data;		/*512 Byte/1 Page*/
#endif
#if 0//Enable_LED_function
		} else if(Type_funcLED==Data_Type) {
			Input_DataPage = 3313;								/*3313~3346*/
			Input_DataSize = sizeof(P3k_FLed_Data);
			Input_DataPtr  = (UBYTE *)&P3k_FLed_Data;		/*512 Byte/1 Page*/
#endif

	} else {
		Debug_printf("DataFlash_Function Error\n");
		Input_DataPage = 3200;
		Input_DataSize = sizeof(p3k_Cal_data);
		Input_DataPtr  = (UBYTE *)&p3k_Cal_data;
	}
	DataFlash_Save_Recall(SelectMode,Input_DataPage,Input_DataSize,Input_DataPtr);
}

void SaveCalData_DataFlash(void)
{

	UWORD cal_mode;
	const char cal_mode_arry[MODE_Number][2]= {{0,1},{2,3},{4,5},{6,7},{8,9},{10,11},{10,11},{12,13},{14,15}};
	cal_mode = (0x01<<cal_mode_arry[P3K_CALIBRATION_BAR.MODE][P3K_CALIBRATION_BAR.RANGE]);
	p3k_Cal_data.Cal_complete |= cal_mode;
	FPGA_W[254] = p3k_Cal_data.Cal_complete;

	p3k_Cal_data.Data_Ready = 200;
	p3k_Cal_data.CheckSum = DataCheckSum((UBYTE *)&p3k_Cal_data,sizeof(p3k_Cal_data));
	DataFlash_Function(Write_DataFlash,Type_CalData);
}

void RecoverCalData_DataFlash(char check_done)
{
#define default_cpp_gain	1.05 //107.24 //108.24
#define default_opp_gain	1.05 //107.24
#define default_ocp_gain	1.453  //109.22
	char str[100],i;
	p3k_cal_Data_str *Cal_tmp = &p3k_Cal_data;

	DataFlash_Function(Read_DataFlash,Type_CalData);
//	p3k_Cal_data.CheckSum = 0;

	if((check_done)&&((p3k_Cal_data.CheckSum==DataCheckSum((UBYTE *)&p3k_Cal_data,sizeof(p3k_Cal_data)))&&(p3k_Cal_data.CheckSum)))
		p3k_Cal_data.Data_Ready = 200;
	else {
		p3k_Cal_data.Data_Ready = 0;
		Debug_printf("Loading Cal Data default!!\n");
		sprintf(str,"Record CheckSum=0x%x\n",p3k_Cal_data.CheckSum);
		Debug_printf(str);
		sprintf(str,"Real CheckSum=0x%x\n",DataCheckSum((UBYTE *)&p3k_Cal_data,sizeof(p3k_Cal_data)));
		Debug_printf(str);

		for(i=IRange_Low ; i<=IRange_High ; i++) {
			/*  Mode	     Range*/

			Cal_tmp->CC_offseAdj[i] = Calibration_Adj_defalut;
			Cal_tmp->CR_offseAdj[i] = Calibration_Adj_defalut;
			Cal_tmp->CP_offseAdj[i] = Calibration_Adj_defalut;
			Cal_tmp->CV_offseAdj[i] = Calibration_Adj_defalut;

			Cal_tmp->CC_Data[i].Cal_Value_Gain		= Default_Cal_Gain;
			Cal_tmp->CR_Data[i].Cal_Value_Gain		= 1.351;			//Default_Cal_Gain;
			Cal_tmp->CV_Data[i].Cal_Value_Gain		= Default_Cal_Gain;
			Cal_tmp->CP_Data[i].Cal_Value_Gain		= Default_Cal_Gain;

			Cal_tmp->CC_Data[i].Cal_Value_Offset	= Default_Cal_Offset;
			Cal_tmp->CR_Data[i].Cal_Value_Offset	= Default_Cal_Offset;
			Cal_tmp->CV_Data[i].Cal_Value_Offset	= Default_Cal_Offset;
			Cal_tmp->CP_Data[i].Cal_Value_Offset	= Default_Cal_Offset;

			Cal_tmp->Curr[i].Meas_Value_Gain		= 41666;
			Cal_tmp->Curr[i].Meas_Value_Offset		= 6383;

			Cal_tmp->Protection[i].CPP 				= Default_Cal_Prot_DA_Rating;
			Cal_tmp->Protection[i].OCP 				= Default_Cal_Prot_DA_OCP;
			Cal_tmp->Protection[i].OPP 				= Default_Cal_Prot_DA_OPP;
			Cal_tmp->Protection[i].CxCV				= Default_Cal_CXCV;

			Cal_tmp->Protection[i].OCP_Gain 			= default_ocp_gain;
			Cal_tmp->Protection[i].OPP_Gain			= default_opp_gain;
			Cal_tmp->Protection[i].CxCV_Gain			= Default_Cal_Gain;

			Cal_tmp->Protection[i].OCP_Offset		= Default_Cal_Offset;
			Cal_tmp->Protection[i].OPP_Offset		= Default_Cal_Offset;
			Cal_tmp->Protection[i].CxCV_Offset		= Default_Cal_Offset;
			if(1) { //if(check_done==0){
				Cal_tmp->Protection[i].CPP_Gain		= default_cpp_gain;
				Cal_tmp->Protection[i].CPP_Offset	= Default_Cal_Offset;
			}
			Cal_tmp->Front_IMON[i]					= 12;
			Cal_tmp->Rear_IMON[i]					= 32;
			Cal_tmp->Ext_V_CC[i]					= 33000;//30660;
			Cal_tmp->Ext_R_CC[i]					= 33000;//30660;
		}

		for(i=VRange_Low ; i<=VRange_High ; i++) {
			Cal_tmp->Volt[i].Meas_Value_Gain	= 44380;//22359;
			Cal_tmp->Volt[i].Meas_Value_Offset	= 6383;
		}

		Cal_tmp->Ext_V_Sense.Meas_Value_Gain = 58000;
		Cal_tmp->Ext_V_Sense.Meas_Value_Offset= 0;
		Cal_tmp->Ext_R_Sense.Meas_Value_Gain = 58000;
		Cal_tmp->Ext_R_Sense.Meas_Value_Offset= 0;

		Cal_tmp->PSensor.XH_Value =	Default_Cal_OS_Ref;
		Cal_tmp->PSensor.YH_Value =	Default_Cal_OS_Ref;
		Cal_tmp->PSensor.ZH_Value =	Default_Cal_OS_Ref;
		Cal_tmp->PSensor.XL_Value =	Default_Cal_OS_Ref;
		Cal_tmp->PSensor.YL_Value =	Default_Cal_OS_Ref;
		Cal_tmp->PSensor.ZL_Value =	Default_Cal_OS_Ref;
		Cal_tmp->Cal_complete = 0;
	}
}

void Add_System_Info(UBYTE *Start_Address)
{
	*(Start_Address++) = P3k_Chan_Data.INFO.MACHTYPE;
	*(Start_Address++) = File_Version;
	*(Start_Address++) = Machine_Number;
	*(Start_Address++) = Main_Version;
	*(Start_Address++) = Sub_Version;
}

void SaveRecall_APP_Info(BYTE dire)/* 0: Backup Data Recover to Prog Data   1: Prog Data To Backup Data*/
{
	UWORD i;

	if(dire) {
		for(i=0 ; i<10 ; i++)
			Backup_APP_Data.OptionInfo[i] = OptionInfo[i];

		Backup_APP_Data.Data_Ready = 200;
		Backup_APP_Data.CheckSum = DataCheckSum((UBYTE *)&Backup_APP_Data,sizeof(Backup_APP_Data));
	} else {
		if(Backup_APP_Data.Data_Ready==200) {
			for(i=0 ; i<10 ; i++)
				OptionInfo[i] = Backup_APP_Data.OptionInfo[i];
		} else {
			for(i=0 ; i<10 ; i++) {
				OptionInfo[i].ModuleFlag	= 0;
				OptionInfo[i].SoftVer		= 0;
				OptionInfo[i].SoftNum		= 0;
				OptionInfo[i].Un_install	= 0;
				OptionInfo[i].PID			= 0;
				OptionInfo[i].VID			= 0;
				OptionInfo[i].SNumber1	= 0;
				OptionInfo[i].SNumber2	= 0;
				OptionInfo[i].MBR_Data	= 0;
			}
		}
	}
}

void SaveRecall_NSeq_Data(BYTE dire)/* 0: Backup Data Recover to NSeq Data   1: NSeq Data To Backup Data*/
{
	UWORD i,j,k;

	if(dire) {
		Add_System_Info(&P3k_Backup_NSeq_Data.MACHTYPE);
		P3k_Backup_NSeq_Data.NSeq_Enable	= P3k_NSeq_Data.NSeq_Enable;
		P3k_Backup_NSeq_Data.NSeq_Number	= P3k_NSeq_Data.NSeq_Number;
		P3k_Backup_NSeq_Data.NSeq_Start		= P3k_NSeq_Data.NSeq_Start;
		k = 0;

		for(i=0 ; i<10 ; i++) {
			P3k_Backup_NSeq_Data.NSeq_Seq[i] = P3k_NSeq_Data.NSeq_Seq[i];

			if(P3k_NSeq_Data.NSeq_Seq[i].NSeq_Max_Step) {
				for(j=0 ; j<P3k_NSeq_Data.NSeq_Seq[i].NSeq_Max_Step ; j++) {
					if(k>=1024) {
						Debug_printf("SaveRecall_NSeq_Data Error\n");
						return;
					} else
						P3k_Backup_NSeq_Data.NSeq_Step[k++] = P3k_NSeq_Data.NSeq_Step[i][j+1];
				}
			}
		}
		P3k_Backup_NSeq_Data.Data_Ready = 200;
		P3k_Backup_NSeq_Data.CheckSum = DataCheckSum((UBYTE *)&P3k_Backup_NSeq_Data,sizeof(P3k_Backup_NSeq_Data));
	} else {
		if(P3k_Backup_NSeq_Data.Data_Ready==200) {
			P3k_NSeq_Data.NSeq_Enable	= P3k_Backup_NSeq_Data.NSeq_Enable;
			P3k_NSeq_Data.NSeq_Number	= P3k_Backup_NSeq_Data.NSeq_Number;
			P3k_NSeq_Data.NSeq_Start	= P3k_Backup_NSeq_Data.NSeq_Start;
			k = 0;

			for(i=0 ; i<10 ; i++) {
				P3k_NSeq_Data.NSeq_Seq[i] = P3k_Backup_NSeq_Data.NSeq_Seq[i];

				if(P3k_NSeq_Data.NSeq_Seq[i].NSeq_Max_Step) {
					for(j=0 ; j<P3k_NSeq_Data.NSeq_Seq[i].NSeq_Max_Step ; j++) {
						if(k >= 1024) {
							Debug_printf("SaveRecall_NSeq_Data Error\n");
							return;
						} else
							P3k_NSeq_Data.NSeq_Step[i][j+1] = P3k_Backup_NSeq_Data.NSeq_Step[k++];
					}
				}
			}
		}
	}
}

void SaveRecall_FSeq_Data(BYTE dire)/* 0: Backup Data Recover to FSeq Data   1: FSeq Data To Backup Data*/
{
	if(dire) {
		Add_System_Info(&P3k_Backup_FSeq_Data.MACHTYPE);
		P3k_Backup_FSeq_Data.Data_Ready	= 200;
		P3k_Backup_FSeq_Data.FSeq_Data	= P3k_FSeq_Data;
		P3k_Backup_FSeq_Data.CheckSum	= DataCheckSum((UBYTE *)&P3k_Backup_FSeq_Data,sizeof(P3k_Backup_FSeq_Data));
	} else {
		if(P3k_Backup_FSeq_Data.Data_Ready==200)
			P3k_FSeq_Data = P3k_Backup_FSeq_Data.FSeq_Data;
	}
}

void SaveRecall_Prog_Data(BYTE dire)/* 0: Backup Data Recover to Prog Data   1: Prog Data To Backup Data*/
{
	UWORD i;

	if(dire) {
		Add_System_Info(&P3k_Backup_Prog_Data.MACHTYPE);

		for(i=0 ; i<256 ; i++)
			P3k_Backup_Prog_Data.M_DATA[i] = P3k_Chan_Data.M_DATA[i];

		P3k_Backup_Prog_Data.Chan_PROG = p3k_Chan_PROG;
		P3k_Backup_Prog_Data.Data_Ready = 200;
		P3k_Backup_Prog_Data.CheckSum = DataCheckSum((UBYTE *)&P3k_Backup_Prog_Data,sizeof(P3k_Backup_Prog_Data));
	} else {
		if(P3k_Backup_Prog_Data.Data_Ready==200) {
			for(i=0 ; i<256 ; i++)
				P3k_Chan_Data.M_DATA[i] = P3k_Backup_Prog_Data.M_DATA[i];

			p3k_Chan_PROG = P3k_Backup_Prog_Data.Chan_PROG;
		}
	}
}

void SaveRecall_Preset_Data(BYTE dire)/* 0: Backup Data Recover to Preset Data   1: Preset Data To Backup Data*/
{
	UWORD i;

	if(dire) {
		Add_System_Info(&Backup_Preset_Data.MACHTYPE);

		for(i=0 ; i<10 ; i++)
			Backup_Preset_Data.P_DATA[i] = P3k_Chan_Data.P_DATA[i];

		Backup_Preset_Data.Data_Ready	= 200;
		Backup_Preset_Data.CheckSum = DataCheckSum((UBYTE *)&Backup_Preset_Data,sizeof(Backup_Preset_Data));
	} else {
		if(Backup_Preset_Data.Data_Ready==200) {
			for(i=0 ; i<10 ; i++)
				P3k_Chan_Data.P_DATA[i] = Backup_Preset_Data.P_DATA[i];
		}
	}
}

void SaveRecall_Setup_Data(BYTE dire)/* 0: Backup Data Recover to Setup Data   1: Setup Data To Backup Data*/
{
	UWORD i;

	p3k_file_util_str *File = &p3k_File_Utility_BAR;

	Add_System_Info(&Backup_Setup_Data[File->SMEMORY_ADDR].MACHTYPE);
	Backup_Setup_Data[File->SMEMORY_ADDR].Data_Ready = 200;
	Backup_Setup_Data[File->SMEMORY_ADDR].CheckSum = DataCheckSum((UBYTE *)&Backup_Setup_Data[File->SMEMORY_ADDR],sizeof(Backup_Setup_Data[File->SMEMORY_ADDR]));
#if 0
	if(dire) {
		Add_System_Info(&Backup_Setup->MACHTYPE);

		for(i=0 ; i<101 ; i++)
			Backup_Setup->P3k_Setup_Data[i]	= P3k_Setup_Data[i];

		Backup_Setup->Data_Ready = 200;
		Backup_Setup->CheckSum = DataCheckSum((UBYTE *)&Backup_Setup_Data,sizeof(Backup_Setup_Data));
	} else {
		if(Backup_Setup->Data_Ready == 200) {
			for(i=0 ; i<101 ; i++)
				P3k_Setup_Data[i] = Backup_Setup->P3k_Setup_Data[i];
		}
	}
#endif
}

void SaveRecall_FRAM_Data(BYTE dire)/* 0: FRAM Data Recover to Channel Status   1: Channel Status Save To FRAM Data*/
{
	char i;
	UBYTE *Backup_Data,*Actual_Data;
	P3k_Data_Str 	*Data_tmp	= &P3k_Chan_Data;
	P3k_Backup_Str	*Backup_tmp = &FRAM_Data.P3k_Backup_Data;

	Backup_Data	= &(Backup_tmp->CURRMODE);
	Actual_Data	= &(Data_tmp->CURRMODE);

	if(dire) {
		for(i=0 ; i<10 ; i++)
			*(Backup_Data+i) = *(Actual_Data+i);

		Backup_tmp->CC				= Data_tmp->CC;
		Backup_tmp->CR				= Data_tmp->CR;
		Backup_tmp->CV				= Data_tmp->CV;
		Backup_tmp->CP				= Data_tmp->CP;
		Backup_tmp->UTILITY			= Data_tmp->UTILITY;
		Backup_tmp->PROT			= Data_tmp->PROT;
		Backup_tmp->CONF			= Data_tmp->CONF;
		Backup_tmp->INFO			= Data_tmp->INFO;

		for(i=0 ; i<10 ; i++)
			Backup_tmp->P_DATA[i]	= Data_tmp->P_DATA[i];

		FRAM_Data.RS232		= RS232;
		FRAM_Data.UTILITY	= UTILITY;
		FRAM_Data.GPIBPAR	= GPIBPAR;
		FRAM_Data.EXT_DGIO	= EXT_DGIO;

		if(DispMode>DispMode_BROWSE_ITEMS)
			FRAM_Data.DispMode = DispMode_BROWSE_ITEMS;
		else
			FRAM_Data.DispMode = DispMode;

		if( (M_num==P_UTIL_INTERFACE || M_num==P_UTIL_T_DATE || M_num==P_UTIL_LOAD || M_num==P_UTIL_OTHER || M_num==P_PROG_MAIN || M_num==P_FILE_CHAN || M_num==P_PROG_EXECUTE || M_num==P_PROG_Detail || M_num==P_NSeq_EXECUTE || M_num==P_FSeq_EXECUTE)&&(FRAM_Data.DispMode) )
			FRAM_Data.DispMode = DispMode_SELECT_CH;

		if(M_num==P_PROG_EXECUTE)
			FRAM_Data.M_num = P_PROG_MAIN;

		if(M_num==P_NSeq_EXECUTE)
			FRAM_Data.M_num = P_Seq_Normal;

		if(M_num==P_FSeq_EXECUTE)
			FRAM_Data.M_num = P_Seq_Fast;

		if(M_num==P_UTIL_SYSMEMO)
			FRAM_Data.M_num = P_UTIL_SYSINFO;
		else if( (M_num==P_Input_Password)||(M_num==P_CAL_MODE)||(M_num==P_UTIL_FILE)||(M_num==P_FILE_MACHINE) )
			FRAM_Data.M_num = P_M_num;
		else if(M_num==P_UTIL_KEYPAD)
			FRAM_Data.M_num = K_M_num;
		else if(M_num==P_HELP_HELP)
			FRAM_Data.M_num = H_M_num;
		else
			FRAM_Data.M_num = M_num;

		FRAM_Data.DispScrCT = DispScrEndCT-DispScrStartCT;

		FRAM_Data.Data_Ready = 200;
#if Enable_Battery_Discharge
		FRAM_Data.BattData = BattDisp;
		FRAM_Data.fLedData= P3k_FLed_Disp;
		FRAM_Data.cLedData= P3k_CLed_Disp;
#endif		
		FRAM_Data.CheckSum = DataCheckSum((UBYTE *)&FRAM_Data,sizeof(FRAM_Data));
	} else {
		if(FRAM_Data.Data_Ready == 200) {
			RS232	 = FRAM_Data.RS232;
			UTILITY	 = FRAM_Data.UTILITY;
			GPIBPAR	 = FRAM_Data.GPIBPAR;
			EXT_DGIO = FRAM_Data.EXT_DGIO;
		}
	}
}

void SaveRecall_UserDefault(BYTE dire)
{
	/* 0: Default recover to Channel Status   1: Channel Status save to Default*/
	UBYTE *Def_Data_Ptr,*Chan_Data_Ptr;
	char i,INTERFACE_Temp;

	if(dire) {
		Def_Data_Ptr = &Backup_Default_Data.P3k_Default_Data.CURRMODE;
		Chan_Data_Ptr= &P3k_Chan_Data.CURRMODE;

		for(i=0 ; i<10 ; i++)
			*(Def_Data_Ptr+i) = *(Chan_Data_Ptr+i);

		Backup_Default_Data.P3k_Default_Data.CC			= P3k_Chan_Data.CC;
		Backup_Default_Data.P3k_Default_Data.CR			= P3k_Chan_Data.CR;
		Backup_Default_Data.P3k_Default_Data.CV			= P3k_Chan_Data.CV;
		Backup_Default_Data.P3k_Default_Data.CP			= P3k_Chan_Data.CP;
		Backup_Default_Data.P3k_Default_Data.UTILITY	= P3k_Chan_Data.UTILITY;
		Backup_Default_Data.P3k_Default_Data.PROT		= P3k_Chan_Data.PROT;
		Backup_Default_Data.P3k_Default_Data.CONF		= P3k_Chan_Data.CONF;
		Backup_Default_Data.P3k_Default_Data.INFO		= P3k_Chan_Data.INFO;
		Backup_Default_Data.P3k_Default_Data.MEAS		= P3k_Chan_Data.MEAS;
		Backup_Default_Data.UTILITY						= UTILITY;
		Backup_Default_Data.EXT_DGIO					= EXT_DGIO;
		Backup_Default_Data.RS232						= RS232;
		Backup_Default_Data.GPIBPAR						= GPIBPAR;
		Backup_Default_Data.Def_Data_Ready 				= 200;
	} else {
		if( (Backup_Default_Data.Def_Data_Ready==200)&&(Backup_Default_Data.Backup_Data_Ready==200) ) {
			Def_Data_Ptr = &Backup_Default_Data.P3k_Default_Data.CURRMODE;
			Chan_Data_Ptr= &P3k_Chan_Data.CURRMODE;

			for(i=0 ; i<10 ; i++)
				*(Chan_Data_Ptr+i) = *(Def_Data_Ptr+i);

			P3k_Chan_Data.CC		= Backup_Default_Data.P3k_Default_Data.CC;
			P3k_Chan_Data.CR		= Backup_Default_Data.P3k_Default_Data.CR;
			P3k_Chan_Data.CV		= Backup_Default_Data.P3k_Default_Data.CV;
			P3k_Chan_Data.CP		= Backup_Default_Data.P3k_Default_Data.CP;
			P3k_Chan_Data.UTILITY	= Backup_Default_Data.P3k_Default_Data.UTILITY;
			P3k_Chan_Data.PROT		= Backup_Default_Data.P3k_Default_Data.PROT;
			P3k_Chan_Data.CONF		= Backup_Default_Data.P3k_Default_Data.CONF;
			P3k_Chan_Data.INFO		= Backup_Default_Data.P3k_Default_Data.INFO;
			P3k_Chan_Data.MEAS		= Backup_Default_Data.P3k_Default_Data.MEAS;
			INTERFACE_Temp			= UTILITY.INTERFACE;
			UTILITY					= Backup_Default_Data.UTILITY;
			UTILITY.INTERFACE		= INTERFACE_Temp;
			EXT_DGIO				= Backup_Default_Data.EXT_DGIO;
		}
	}
}

void ReadyBackupFSeqData(void)
{
	SaveRecall_FSeq_Data(1);
}

void BackupNSeq(void)
{
	SaveRecall_NSeq_Data(1);
	DataFlash_Function(Write_DataFlash,Type_NSeqData);
}

void BackupFSeq(void)
{
	SaveRecall_FSeq_Data(1);
	DataFlash_Function(Write_DataFlash,Type_FSeqData);
}

#if Enable_OCP_function

void BackupOCP(void)
{
	P3K_OCP_Data.Data_Ready = 200;	
	DataFlash_Function(Write_DataFlash,Type_funcOCP);
}

#endif

#if Enable_OPP_function
void BackupOPP(void) {
	P3K_OPP_Data.Data_Ready = 200;
	DataFlash_Function(Write_DataFlash,Type_funcOPP);
}

#endif
#if Enable_LED_function
void BackupLED(void) {
//	P3k_FLed_Data.Data_Ready = 200;
	DataFlash_Function(Write_DataFlash,Type_funcLED);
}
#endif


void RecoverLastNSeq(void)
{
	char str[30];

	DataFlash_Function(Read_DataFlash,Type_NSeqData);

	if( (P3k_Backup_NSeq_Data.CheckSum==DataCheckSum((UBYTE *)&P3k_Backup_NSeq_Data,sizeof(P3k_Backup_NSeq_Data)))&&(P3k_Backup_NSeq_Data.CheckSum) )
		SaveRecall_NSeq_Data(0);
	else {
		P3k_Backup_NSeq_Data.Data_Ready = 0;
		Debug_printf("Loading NSeq Data default!!\n");
		sprintf(str,"NSeq_Data_Record=0x%x\n",P3k_Backup_NSeq_Data.CheckSum);
		Debug_printf(str);
		sprintf(str,"NSeq_Data_Real=0x%x\n",DataCheckSum((UBYTE *)&P3k_Backup_NSeq_Data,sizeof(P3k_Backup_NSeq_Data)) );
		Debug_printf(str);
	}
	P3k_NSeq_Disp = P3k_NSeq_Data;
}

void RecoverLastFSeq(void)
{
	char str[30];

	DataFlash_Function(Read_DataFlash,Type_FSeqData);

	if( (P3k_Backup_FSeq_Data.CheckSum==DataCheckSum((UBYTE *)&P3k_Backup_FSeq_Data,sizeof(P3k_Backup_FSeq_Data)))&&(P3k_Backup_FSeq_Data.CheckSum) )
		SaveRecall_FSeq_Data(0);
	else {
		P3k_Backup_FSeq_Data.Data_Ready = 0;
		Debug_printf("Loading FSeq Data default!!\n");
		sprintf(str,"FSeq_Data_Record=0x%x\n",P3k_Backup_FSeq_Data.CheckSum);
		Debug_printf(str);
		sprintf(str,"FSeq_Data_Real=0x%x\n",DataCheckSum((UBYTE *)&P3k_Backup_FSeq_Data,sizeof(P3k_Backup_FSeq_Data)) );
		Debug_printf(str);
	}
	P3k_FSeq_Disp = P3k_FSeq_Data;
}

void BackupAPPInfo(void)
{
	SaveRecall_APP_Info(1);
	DataFlash_Function(Write_DataFlash,Type_APPData);
}

void RecoverAPPInfo(void)
{
	UWORD i;
	char str[30];

	DataFlash_Function(Read_DataFlash,Type_APPData);

	if( (Backup_APP_Data.CheckSum==DataCheckSum((UBYTE *)&Backup_APP_Data,sizeof(Backup_APP_Data)))&&(Backup_APP_Data.CheckSum) )
		SaveRecall_APP_Info(0);
	else {
		Backup_APP_Data.Data_Ready = 0;
		for(i=0 ; i<10 ; i++) {
			OptionInfo[i].ModuleFlag	= 0;
			OptionInfo[i].SoftVer		= 0;
			OptionInfo[i].SoftNum		= 0;
			OptionInfo[i].Un_install	= 0;
			OptionInfo[i].PID			= 0;
			OptionInfo[i].VID			= 0;
			OptionInfo[i].SNumber1	= 0;
			OptionInfo[i].SNumber2	= 0;
			OptionInfo[i].MBR_Data	= 0;
		}
		Debug_printf("Loading APP Data default!!\n");
		sprintf(str,"APP_Data_Record=0x%x\n",Backup_APP_Data.CheckSum);
		Debug_printf(str);
		sprintf(str,"APP_Data_Real=0x%x\n",DataCheckSum((UBYTE *)&Backup_APP_Data,sizeof(Backup_APP_Data)) );
		Debug_printf(str);
	}
}

void BackupRunProg(void)
{
	SaveRecall_Prog_Data(1);
	DataFlash_Function(Write_DataFlash,Type_ProgData);
}

void RecoverLastRunProg(void)
{
	char str[30];

	DataFlash_Function(Read_DataFlash,Type_ProgData);

	if( (P3k_Backup_Prog_Data.CheckSum==DataCheckSum((UBYTE *)&P3k_Backup_Prog_Data,sizeof(P3k_Backup_Prog_Data)))&&(P3k_Backup_Prog_Data.CheckSum) )
		SaveRecall_Prog_Data(0);
	else {
		P3k_Backup_Prog_Data.Data_Ready = 0;
		Debug_printf("Loading Prog Data default!!\n");
		sprintf(str,"Prog_Data_Record=0x%x\n",P3k_Backup_Prog_Data.CheckSum);
		Debug_printf(str);
		sprintf(str,"Prog_Data_Real=0x%x\n",DataCheckSum((UBYTE *)&P3k_Backup_Prog_Data,sizeof(P3k_Backup_Prog_Data)) );
		Debug_printf(str);
	}
	p3k_Disp_PROG = p3k_Chan_PROG;
}

void BackupUserDefaultData(char mode)
{
	/*mode:0 Save Factory to Default*/
	/*mode:1 Save Channel Status to Default*/

	if(mode)
		SaveRecall_UserDefault(1);
	else
		Backup_Default_Data.Def_Data_Ready = 0;

	Backup_Default_Data.Backup_Data_Ready = 200;
	Backup_Default_Data.CheckSum = DataCheckSum((UBYTE *)&Backup_Default_Data,sizeof(Backup_Default_Data));
	DataFlash_Function(Write_DataFlash,Type_DefData);
}

void RecoverUserDefaultData(void)
{
	char str[50];

	DataFlash_Function(Read_DataFlash,Type_DefData);

	if( (Backup_Default_Data.CheckSum==DataCheckSum((UBYTE *)&Backup_Default_Data,sizeof(Backup_Default_Data)))&&(Backup_Default_Data.CheckSum) )
		Backup_Default_Data.Backup_Data_Ready = 200;
	else {
		Backup_Default_Data.Backup_Data_Ready = 0;
		Backup_Default_Data.Def_Data_Ready = 0;
		Debug_printf("Loading Default Data default!!\n");
		sprintf(str,"Default_Data_Record=0x%x\n",Backup_Default_Data.CheckSum);
		Debug_printf(str);
		sprintf(str,"Default_Data_Real=0x%x\n",DataCheckSum((UBYTE *)&Backup_Default_Data,sizeof(Backup_Default_Data)) );
		Debug_printf(str);
	}
}

void BackupStatus(void)
{
	UWORD Backup_TimeOut = 300;

	if((p3k_File_Utility_BAR.USB_Data_Type == F_Setup_Data) && (BackupBusyFlag))
		return;

	SaveRecall_FRAM_Data(1);

	while(BackupBusyFlag) {
		OSTimeDly(1);
		Backup_TimeOut--;
		if(Backup_TimeOut==0) {
			printf("BackupMasterMemo TimeOut\n");
			break;
		}
	}
	BackupBusyFlag = 1;

	if(FRAM_WRITE_MEM((UBYTE *)&FRAM_Data, sizeof(FRAM_Data))==(-1))
		Debug_printf("FRAM writing error!!\n");

	BackupBusyFlag = 0;
}

extern char Ftype;// 0:fm25L04   1:fm25LC64
void RecoverLastOP(void)
{
	char str[30];

	if(FRAM_READ_MEM((UBYTE *)&FRAM_Data,sizeof(FRAM_Data))==(-1)) {
		Debug_printf("FRAM reading error!!\n");
		FRAM_Data.Data_Ready = 0;
	}
#if 0
	FRAM_Data.CheckSum = 0;
#endif
//Adam_test Don't read FRAM
	if((FRAM_Data.CheckSum==DataCheckSum((UBYTE *)&FRAM_Data,sizeof(FRAM_Data)))&&(FRAM_Data.CheckSum) ) {
		SaveRecall_FRAM_Data(0);

		if(!(SYSType&GPIB_CONNECTED)) {
			GPIBPAR.ONOFF=2;
#if 0 /*When No GPIB Card and PC send *RST,INTERFACE maybe USB-> RS232*/
			if((!RS232.ONOFF)&&(!UTILITY.USB_ONOFF)) {
				RS232.ONOFF = 0x1;
				UTILITY.INTERFACE = INTERFACE_RS232;
			}
#else
			if(UTILITY.INTERFACE == INTERFACE_GPIB) {
				UTILITY.USB_ONOFF = 0x1;
				UTILITY.INTERFACE = INTERFACE_USB;
			}
#endif
		} else {
			if(GPIBPAR.ONOFF==2)
				GPIBPAR.ONOFF = 0;
		}

		UTILITY.LOAD_CTL	= 0;/*for Run Prog*/
		UTILITY.SHORT_CTL= 0;

		EXT_DGIO.TSTATUS=0xff;

		EDGIO_Control(T_SYNC_ENABLE, Switch_OFF);
	} else {
		FRAM_Data.Data_Ready = 0;
		EXT_DGIO.RSTATUS |= 0x1;
		EXT_DGIO.TSTATUS  = 0xff;
		EDGIO_Control(T_SYNC_ENABLE, Switch_OFF);
		Debug_printf("Loading USER SETUP default!!\n");
		sprintf(str,"FRAM_Data_Record=0x%x\n",FRAM_Data.CheckSum);
		Debug_printf(str);
		sprintf(str,"FRAM_Data_Real=0x%x\n",DataCheckSum((UBYTE *)&FRAM_Data,sizeof(FRAM_Data)) );
		Debug_printf(str);
		sprintf(str,"Ftype=%d\n",Ftype);/* 0:FM25L04   1:FM25CL64*/
		Debug_printf(str);
	}
}

void RecoverLastSerialNumber(void)
{
	DataFlash_Function(Read_DataFlash,Type_SerialNumber);

	if( (P3k_Backup_SN.CheckSum==DataCheckSum((UBYTE *)&P3k_Backup_SN,sizeof(P3k_Backup_SN)))&&(P3k_Backup_SN.CheckSum) ) {
		memcpy((void*)P3k_Serial_Number.Product_Serial_Number, (void*)P3k_Backup_SN.Serial_Number.Product_Serial_Number,10);
		P3k_Serial_Number.Version = P3k_Backup_SN.Serial_Number.Version;
		P3k_Serial_Number.version_flag= P3k_Backup_SN.Serial_Number.version_flag;
		P3k_Backup_SN.Backup_Data_Ready = 200;
	} else {
		P3k_Backup_SN.Backup_Data_Ready = 0;
		P3k_Backup_SN.Serial_Number_Ready = 0;
		Debug_printf("Loading Serial Number default!!\n");
		sprintf((char *)P3k_Serial_Number.Product_Serial_Number, "00000001");
	}

}

void BackupSerialNumber(void)
{
	memcpy((void*)P3k_Backup_SN.Serial_Number.Product_Serial_Number, (void*)P3k_Serial_Number.Product_Serial_Number,10);
	P3k_Backup_SN.Serial_Number.Version = P3k_Serial_Number.Version;
	P3k_Backup_SN.Serial_Number_Ready = 200;
	P3k_Backup_SN.CheckSum = DataCheckSum((UBYTE *)&P3k_Backup_SN,sizeof(P3k_Backup_SN));

	DataFlash_Function(Write_DataFlash,Type_SerialNumber);
}

void RecoverLastSetupData(void)
{
	char str[30];

	p3k_file_util_str *File = &p3k_File_Utility_BAR;

	///FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_C);
	DataFlash_Function(Read_DataFlash,Type_SetupData);
	///FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_S);

	if( (Backup_Setup_Data[File->SMEMORY_ADDR].CheckSum==DataCheckSum((UBYTE *)&Backup_Setup_Data[File->SMEMORY_ADDR],sizeof(Backup_Setup_Data[File->SMEMORY_ADDR])))&&(Backup_Setup_Data[File->SMEMORY_ADDR].CheckSum) )
		SaveRecall_Setup_Data(0);
	else {
		Backup_Setup_Data[File->SMEMORY_ADDR].Data_Ready = 0;
		Debug_printf("Loading Setup Data default!!\n");
		sprintf(str,"Setup_Data_Record=0x%x\n",Backup_Setup_Data[File->SMEMORY_ADDR].CheckSum);
		Debug_printf(str);
		sprintf(str,"Setup_Data_Real=0x%x\n",DataCheckSum((UBYTE *)&Backup_Setup_Data[File->SMEMORY_ADDR],sizeof(Backup_Setup_Data[File->SMEMORY_ADDR])) );
		Debug_printf(str);
	}
}
#if Enable_OCP_function
void RecoverLastFuncOCP(void){
	char i;
	DataFlash_Function(Read_DataFlash,Type_funcOCP);
	if(P3K_OCP_Data.Data_Ready != 200){
		P3K_OCP_Data.CurrTemp = 0;
		P3K_OCP_Data.Data_Ready = 200;
		P3K_OCP_Data.Complete = 0;
		P3K_OCP_Data.UpdataFlag  = 0;
		for(i=0;i<12;i++){
			P3K_OCP_Data.Seq[i].Range = 0;
			P3K_OCP_Data.Seq[i].StartCurrWatt = 1;
			P3K_OCP_Data.Seq[i].EndCurrWatt = 1000;
			P3K_OCP_Data.Seq[i].StepCurrWatt = 10;
			P3K_OCP_Data.Seq[i].StepTime = 10;
			P3K_OCP_Data.Seq[i].DelayTime = 0;
			P3K_OCP_Data.Seq[i].TrigVolt = 100;
			P3K_OCP_Data.Seq[i].LastCurrWatt = 0;
		}
	}
	P3K_OCP_Disp = P3K_OCP_Data;
}
#endif
#if Enable_OPP_function
void RecoverLastFuncOPP(void) {
	char i;
	DataFlash_Function(Read_DataFlash,Type_funcOPP);
	if(P3K_OPP_Data.Data_Ready != 200) {
		P3K_OPP_Data.CurrTemp = 0;
		P3K_OPP_Data.Data_Ready = 200;
		P3K_OPP_Data.Complete = 0;
		P3K_OPP_Data.UpdataFlag  = 0;
		for(i=0; i<12; i++) {
			P3K_OPP_Data.Seq[i].Range = 0;
			P3K_OPP_Data.Seq[i].StartCurrWatt = 1;
			P3K_OPP_Data.Seq[i].EndCurrWatt = 1000;
			P3K_OPP_Data.Seq[i].StepCurrWatt = 10;
			P3K_OPP_Data.Seq[i].StepTime = 10;
			P3K_OPP_Data.Seq[i].DelayTime = 0;
			P3K_OPP_Data.Seq[i].TrigVolt = 100;
			P3K_OPP_Data.Seq[i].LastCurrWatt = 0;
		}
	}
	P3K_OPP_Disp = P3K_OPP_Data;
}
#endif
#if 0//Enable_LED_function
void RecoverLastFuncLED(void) {
	UWORD i;
	DataFlash_Function(Read_DataFlash,Type_funcLED);
//	if(P3k_FLed_Data.Data_Ready != 200) {
//		P3k_FLed_Data.Data_Ready = 200;
		P3k_FLed_Data.complete = 0;		
//		P3k_FLed_Data.Seq.range2 = 3;
		P3k_FLed_Data.seq[0].mode= 1;
		//P3k_FLed_Data.seq[0].SR= 250;
		//P3k_FLed_Data.seq[0].vMax=0;
		///for(i=0;i<8192;i++){
		///	P3k_FLed_Data.Seq.viTable[i]=0;
		///}		
//	}
	P3k_FLed_Disp = P3k_FLed_Data;
}
#endif

void BackupSetupData(void)
{
	SaveRecall_Setup_Data(1);
	///FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_C);
	DataFlash_Function(Write_DataFlash,Type_SetupData);
	///FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_S);
}

extern void WriteFile(void *pData, unsigned long Size, char *FileName);
void SaveSetupDataToFile(void)
{
	p3k_file_util_str *File = &p3k_File_Utility_BAR;

	SaveRecall_Setup_Data(1);
	WriteFile((UBYTE *)&Backup_Setup_Data, sizeof(Backup_Setup_Data), SaveFileName);
	FMinfo |= FM_READ_DEVICE;
	OSTimeDly(2);
}

void SavePresetDataToFile(void)
{
	SaveRecall_Preset_Data(1);
	WriteFile((UBYTE *)&Backup_Preset_Data, sizeof(Backup_Preset_Data), SaveFileName);
	FMinfo |= FM_READ_DEVICE;
	OSTimeDly(2);
}

void SaveProgDataToFile(void)
{
	SaveRecall_Prog_Data(1);
	WriteFile((UBYTE *)&P3k_Backup_Prog_Data, sizeof(P3k_Backup_Prog_Data), SaveFileName);
	FMinfo |= FM_READ_DEVICE;
	OSTimeDly(2);
}

void SaveNSeqDataToFile(void)
{
	SaveRecall_NSeq_Data(1);
	WriteFile((UBYTE *)&P3k_Backup_NSeq_Data, sizeof(P3k_Backup_NSeq_Data), SaveFileName);
	FMinfo |= FM_READ_DEVICE;
	OSTimeDly(2);
}

void SaveFSeqDataToFile(void)
{
	SaveRecall_FSeq_Data(1);
	WriteFile((UBYTE *)&P3k_Backup_FSeq_Data, sizeof(P3k_Backup_FSeq_Data), SaveFileName);
	FMinfo |= FM_READ_DEVICE;
	OSTimeDly(2);
}
