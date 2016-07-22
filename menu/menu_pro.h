/***********************************************************************************
 *    This file is modified form GDS830 menu3.h
 *
 *
 ***********************************************************************************/
#ifndef MENUPRO_H
#define MENUPRO_H

void Cal_Init_Proc(void);
BYTE Normal_Mode(BYTE chnum,BYTE x);
BYTE Normal_IRange(BYTE chnum,BYTE x);
BYTE Normal_VRange(BYTE chnum,BYTE x);
BYTE Normal_Type(BYTE chnum,BYTE x);
BYTE Password_Process(BYTE chnum,BYTE x);
BYTE Configure_Main(BYTE chnum,BYTE x);
BYTE Config_Protection(BYTE chnum, BYTE x);
BYTE Config_Other(BYTE chnum, BYTE x);
BYTE Config_GoNoGo(BYTE chnum,BYTE x);
BYTE Config_External(BYTE chnum,BYTE x);
BYTE Config_Knob(BYTE chnum, BYTE x);
BYTE Prog_Chain(BYTE chnum, BYTE x);
BYTE Seq_Edit(BYTE chnum,BYTE x);
BYTE Utility_Proc(BYTE chnum, BYTE x);
BYTE Save_Data(BYTE chnum, BYTE x);
BYTE Recall_Data(BYTE chnum, BYTE x);
BYTE Edit_Chain_Start(BYTE chnum, BYTE x);
BYTE Help_func(BYTE chnum, BYTE x);
BYTE Prog_Seq_Next(BYTE chnum, BYTE x);
BYTE Prog_Seq_Stop_Continue(BYTE chnum, BYTE x);
BYTE FileMedia_Proc(BYTE chnum, BYTE x);
BYTE FileUtil_Proc(BYTE chnum, BYTE x);
BYTE FileKeyPad_Proc(BYTE chnum, BYTE x);
BYTE Time_Set(BYTE chnum, BYTE x);
BYTE Pre_Menu(BYTE chnum,BYTE x);
UBYTE MakeChanStatus(void);
void Save2Mem(char mode, UWORD no);
UBYTE Recall2Mem(char mode, UWORD no);
void Recall2Display(void);
BYTE Cal_Func(BYTE chnum, BYTE x);
BYTE Cal_Save(BYTE chnum, BYTE x);
BYTE Cal_PSense(BYTE chnum, BYTE x);
BYTE SEQ_VIEW_NEXT(BYTE chnum,BYTE x);
void WriteFile(void *pData, unsigned long Size, char *FileName);
int FileNameConvert(int Name_Count, char *Name_str, char Mode);
int NextFileName(int FileCount, char *FileName, char Mode, char cnt);
char CheckSameFile(char *FileName);
void RecallFileNameFun(const char *name, char *FileName, char Mode, char cnt);
long round_recall (double fdVal);
BYTE RecallDataFromFile(char Data_Type,char *FileName);
void SaveSetupDataAction(char SMEMORY_ADDR);
void RecallSetupData(char Address);
void RecallUserDefault(char mode);
void WriteFileDate(char *Name1_Str, char *Name2_Str, char *Name3_Str, char *Name4_Str, char *Name5_Str, char *Name6_Str, char *Name7_Str, char *Name8_Str, char *Name9_Str, char *Name10_Str);
void WriteFileDate_string(char *Name1_Str, char Mode);
void SaveGoNGResult(void);
BYTE Upgrading(char source,char *FileName);
BYTE Upgrading_SCPI(char source,UBYTE *SCPI_Data,LONG FileSize);
BYTE UpgradingMain(char *FileName);
BYTE Prog_Function(BYTE chnum, BYTE x);
BYTE Seq_Function(BYTE chnum, BYTE x);
BYTE APP_Function(BYTE chnum, BYTE x);
BYTE Fill_Function(BYTE chnum, BYTE x);
BYTE Save_Fill_Action(BYTE chnum, BYTE x);
BYTE Add_FSeq(BYTE chnum, BYTE x);
BYTE Del_FSeq(BYTE chnum, BYTE x);
BYTE Add_NSeq(BYTE chnum, BYTE x);
BYTE Del_NSeq(BYTE chnum, BYTE x);
BYTE Del_NSeq_all(BYTE chnum, BYTE x);
BYTE Test1_Function(BYTE chnum, BYTE x);
BYTE Test2_Function(BYTE chnum, BYTE x);
BYTE Test3_Function(BYTE chnum, BYTE x);
BYTE UpgradingFPGA(char *FileName);
BYTE File_Test_FPGA (char *FileName);
BYTE Save_Acq_4K_Meas_Data(BYTE chnum, BYTE x);
BYTE Save_1K_Meas_Data(BYTE chnum, BYTE x);
BYTE DebugToolSelet(BYTE chnum, BYTE x);
BYTE DebugToolSave(BYTE chnum, BYTE x);
BYTE Save_CalData_To_USB(BYTE chnum, BYTE x);
BYTE Save_PrintScr_To_USB (BYTE chnum, BYTE x);
BYTE JumpCalValue (BYTE chnum, BYTE x);
BYTE Read_CalDefault (BYTE chnum, BYTE x);

BYTE Config_Parallel(BYTE chnum, BYTE x);
BYTE Seq_Select(BYTE chnum, BYTE x);
BYTE EnableFlag(BYTE chnum, BYTE x);
BYTE goto_fled_option(BYTE chnum, BYTE x);
BYTE goto_cled_option(BYTE chnum, BYTE x);
BYTE EditNormalSeq(BYTE chnum, BYTE x);
BYTE EditFastSeq(BYTE chnum, BYTE x);
BYTE APP_Function_OCP(BYTE chnum, BYTE x);
#if Enable_OPP_function
BYTE APP_Function_OPP(BYTE chnum, BYTE x);
#endif
#if Enable_Battery_Discharge
BYTE goto_func_batt(BYTE chnum, BYTE x);
BYTE goto_func_batt2(BYTE chnum, BYTE x);
BYTE goto_func_batt_exe(BYTE chnum, BYTE x);

BYTE goto_func_led(BYTE chnum, BYTE x);
BYTE goto_func_led_exe(BYTE chnum, BYTE x);
BYTE goto_curve_led(BYTE chnum, BYTE x);
BYTE goto_curve_led_exe(BYTE chnum, BYTE x);

#endif
BYTE goto_func_main2(BYTE chnum, BYTE x);

BYTE Recall_Factory_Default(BYTE chnum, BYTE x);
BYTE EnterPowerFunc(BYTE chnum, BYTE x);
#endif

