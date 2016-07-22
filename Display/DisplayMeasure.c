#include <app.h>
#include "../menu/head.h"
#include "keydef.h"
#include "../FPGA/SendTXSub.h"
//#include "../GUI/Gui.H"

extern void PEL3000_LED_Control( char mode, char onoff);
extern char Display_Parameter_Pro(double Parameter, char *buf, char precision);
extern void Debug_printf(char *Message);
extern void Show_SDRAM_Setting(void);

//void Display_Measure_Pro(double Parameter, char *buf, char precision)
#define Volt_Mode 0
#define Curr_Mode 1
#define Watt_Mode 2
unsigned char last_menu;//Adam_debug
void Display_Measure_Pro(UBYTE Meas_Mode, char *buf)
{
	P3k_Data_Str *Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str *Disp_tmp = &P3k_Disp_Data;//Adam_debug
	float Parameter;
	char precision;
	unsigned char R_IRange , R_VRange;
	
	if(buf==0)
	{
		Debug_printf(" Display_Measure_Pro Buf Error\n");
		return;
	}
	if((M_num==P_PROG_EXECUTE)||(M_num==P_NSeq_EXECUTE)||(M_num==P_FSeq_EXECUTE)){
		R_IRange = Prog_Seq_Data.FPGA_Seq_Data[Prog_Seq_Data.Display_Count].SEQ_Range; //0~3
		R_VRange = R_IRange/2;	
		R_IRange = (R_IRange % 2);

		if(Prog_Seq_Data.FPGA_Seq_Data[Prog_Seq_Data.Display_Count].SEQ_Mode==P_CR){ //Adam_debug
			R_IRange = 1;
		}
		Data_tmp->VRange =R_VRange;
		Data_tmp->IRange = R_IRange;
		Disp_tmp->VRange =R_VRange; 	//Adam_debug
		Disp_tmp->IRange = R_IRange;//Adam_debug 
	}else{
		R_VRange = Data_tmp->VRange;
		R_IRange = Data_tmp->IRange;		
		
	}
	if(P_CR == P3k_Chan_Data.CURRMODE==P_CR) R_IRange = 1; //Adam_2016_0414

	if(Meas_Mode==Volt_Mode)
	{
		Parameter = p3k_Measure_Data.VOLT;
		precision = (ptrMODEL_TYPE->CV)[3*R_VRange].precision;
	}	
	else if(Meas_Mode==Curr_Mode)
	{
		if(LOW_RANGE==R_IRange)
		{
			Parameter = p3k_Measure_Data.CURR*1000.0; 				
			precision =(ptrMODEL_TYPE->CC)[10*R_IRange].precision-3;
		}
		else
		{
			Parameter = p3k_Measure_Data.CURR;
			precision =(ptrMODEL_TYPE->CC)[10*R_IRange].precision;
		}
	}
	else
	{
		Parameter = p3k_Measure_Data.WATT;
		precision = (ptrMODEL_TYPE->CP)[10*R_IRange].precision;
	}

	if(Parameter<0)
		Parameter = 0.0;	
	if( ((precision==2)&&(Parameter>1000.0-0.1))||((precision==3)&&(Parameter>100.0-0.003))||((precision==4)&&(Parameter>10.0-0.0003)) )
		precision--;

	if(precision==1)
	{
		if(Parameter>10000.0-0.1)
			sprintf(buf,"%1.0f",Parameter);
		else if(Parameter>=1000)

			sprintf(buf,"%1.1f",Parameter);
		else if(Parameter>=100)	
			sprintf(buf,"  %1.1f",Parameter);
		else if(Parameter>=10)	
			sprintf(buf,"    %1.1f",Parameter);
		else
			sprintf(buf,"      %1.1f",Parameter);
	}
	else if(precision==2)
	{
		if(Parameter>1000.0-0.1)
			sprintf(buf,"%1.0f",Parameter);
		else if(Parameter>=100)		
			sprintf(buf,"%1.2f",Parameter);
		else if(Parameter>=10)	
			sprintf(buf,"  %1.2f",Parameter);
		else
			sprintf(buf,"    %1.2f",Parameter);
	}
	else if(precision==3)
	{
		if(Parameter>1000.0-0.1)
			sprintf(buf,"%1.1f",Parameter);			
		else if(Parameter>100.0)
			sprintf(buf,"%1.2f",Parameter);
		else if(Parameter>=10)
			sprintf(buf,"%1.3f",Parameter);
		else
			sprintf(buf,"  %1.3f",Parameter);
	}
	else if(precision==4)		
	{
		if(Parameter>10.0)
			sprintf(buf,"%1.2f",Parameter);
		else 
			sprintf(buf,"%1.4f",Parameter);
	} 
	else if(precision==0)
	{
		if(Parameter>10000.0-0.1)
			sprintf(buf,"%1.0f",Parameter);
		else if(Parameter>=1000)

			sprintf(buf,"%1.1f",Parameter);
		else if(Parameter>=100)	
			sprintf(buf,"  %1.1f",Parameter);
		else if(Parameter>=10)	
			sprintf(buf,"    %1.1f",Parameter);
		else
			sprintf(buf,"      %1.1f",Parameter);
	}
	else
	{
		if(Parameter>=10000-0.1)		
			sprintf(buf,"%5.0f",Parameter);
		else if(Parameter>=1000-0.1)	
			sprintf(buf,"%4.1f",Parameter);
		else if( Parameter >= 100)	
			sprintf(buf,"%3.2f",Parameter);
		else if(Parameter>=10)		
			sprintf(buf,"%2.3f",Parameter);
		else
			sprintf(buf,"%1.5f",Parameter);						
	}
	*(buf+20)=0;

}


extern void ShowSpace(char no, int x, int y);
//const char Meas_Alarm[13][20]={"               ","    OTP   ","    RVP   ","    OVP   ","    UVP   ","    Para  ","    OPP   ","    OCP   ","    CPP   ","  R.OCP  ","    FCCP  ","  UnReg  ", "  Ext.OV  "};
const char Meas_Alarm[14][20]={"               ","    OTP    ","    RVP    ","    OVP    ","    UVP    ","    Para    ","    OPP    ","    OCP    ","    ROPP   ","    ROCP   ","   F.ROCP ","   UnReg  ", "   Ext.OV  ","    Alarm   "};


#define currentFlag		0x01
#define voltageFlag		0x02
#define powerFlag		0x04
#define alarmFlag		0x08
#define gonogoFlag		0x10
#define runtimeFlag		0x20
#define unitFlag		0x40
#define MeasureAllFlag	0x7F
#if Enable_Func_DisTime
extern unsigned long total_SEQ_time;
#endif


void RedrawMeasure(void)
{
	const char Meas_GoNoGo[3][15]= {"           "," NG "," GO "};
	char str[30];
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	unsigned char gonogo;	
	static unsigned char dis_cnt=0;
	static unsigned char i;
	static unsigned char j=0;
	static unsigned char last_sec;
	static unsigned char last_range =10;
	static float recode_C,recode_V,recode_W;
	static unsigned char recodeAlarm,recodeGonogo,recodeRuntime;
	static unsigned char redrawMeasureflag = 0;
#if Enable_Func_select
	UBYTE funcDisFlag = 0; // 0: normal,  1:dis:nseq
	if((UTILITY.LOAD_CTL==Switch_OFF)&&(P3k_Chan_Data.Load_Type!=Normal_Load)&&(M_num<4)){
		funcDisFlag = 1;
	}	
#endif

	dis_cnt = (dis_cnt+1)%2;	
	j++;
	if(j>=10){
		j =0;
		i=(i+1)%7;
		redrawMeasureflag |= (0x01<<i);
	}	
	if((M_num!=last_menu)||((last_range!=Data_tmp->IRange+(Data_tmp->VRange*3)))){
		last_menu = M_num;
		last_range = (Data_tmp->IRange+(Data_tmp->VRange*3));
		dis_cnt=2;
	}
	GUI_SetFont(Measure_Font);
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Noted_Font_Bolor);

	switch(dis_cnt){
		case 0:
			if((p3k_Measure_Data.VOLT!=recode_V)||(redrawMeasureflag & voltageFlag)){
				Display_Measure_Pro(Volt_Mode,str);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, 136, 17);
				recode_V=p3k_Measure_Data.VOLT;
				DMA_Update_Flag = 1;
			}
			if((p3k_Measure_Data.CURR!=recode_C)||(redrawMeasureflag & currentFlag)){
				Display_Measure_Pro(Curr_Mode,str);
				GUI_SetTextAlign(GUI_TA_RIGHT);	
				GUI_DispStringAt(str, 136, 61);
				recode_C=p3k_Measure_Data.CURR;
				DMA_Update_Flag = 1;
			}
			redrawMeasureflag &= ~(0x03);
			break;
		case 1:	
#if Enable_Func_select	
			if((p3k_Measure_Data.WATT!=recode_W)||(redrawMeasureflag & powerFlag)) {
				if(funcDisFlag){

				}else{
					Display_Measure_Pro(Watt_Mode,str);
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, 294, 17);
					recode_W=p3k_Measure_Data.WATT;
				}	
				GUI_SetFont(Measure_Unit_Font);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( "V",154,30);
				DMA_Update_Flag = 1;
			}
			if(redrawMeasureflag & unitFlag) {
				GUI_SetFont(Measure_Unit_Font);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( "V",154,30);
				if(funcDisFlag==0){
					GUI_DispStringAt( "W",294,30);
				}
				//if(LOW_RANGE==Data_tmp->IRange) //Adam_debug
				if((LOW_RANGE==Data_tmp->IRange)&&(Data_tmp->CURRMODE != P_CR))
					GUI_DispStringAt( "mA ",135,75);
				else
					GUI_DispStringAt( "A   ",135,75);
				DMA_Update_Flag = 1;
			}
#else
		if((p3k_Measure_Data.WATT!=recode_W)||(redrawMeasureflag & powerFlag)) {
			Display_Measure_Pro(Watt_Mode,str);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, 294, 17);
			recode_W=p3k_Measure_Data.WATT;
			GUI_SetFont(Measure_Unit_Font);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( "V",154,30);
			DMA_Update_Flag = 1;
		}
		if(redrawMeasureflag & unitFlag) {
			GUI_SetFont(Measure_Unit_Font);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( "V",154,30);
			GUI_DispStringAt( "W",294,30);
			//if(LOW_RANGE==Data_tmp->IRange) //Adam_debug
			if((LOW_RANGE==Data_tmp->IRange)&&(Data_tmp->CURRMODE != P_CR))
				GUI_DispStringAt( "mA ",135,75);
			else
				GUI_DispStringAt( "A   ",135,75);
			DMA_Update_Flag = 1;
		}
#endif
	
			GUI_SetFont(Time_Alarm_Font);
			GUI_SetColor(Alarm_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			if((p3k_Measure_Data.Alarm!=recodeAlarm)||(redrawMeasureflag & alarmFlag)){
#if Enable_OPPOCP_off
				if((P3k_Chan_Data.PROT.OPP_SET==2)&&(p3k_Measure_Data.Alarm==6))
					GUI_DispStringAt( Meas_Alarm[8], 312, 65-1);	
				else
					GUI_DispStringAt( Meas_Alarm[p3k_Measure_Data.Alarm], 312, 65-1);	
#else
				if((p3k_Measure_Data.Alarm==5)&&((!P3k_Chan_Data.CONF.Para_Data.Parallel_Number)&&(!P3k_Chan_Data.CONF.Para_Data.Booster_Number)))
					GUI_DispStringAt( Meas_Alarm[p3k_Measure_Data.Alarm+8], 312, 65-1);
				else
					GUI_DispStringAt( Meas_Alarm[p3k_Measure_Data.Alarm], 312, 65-1);
#endif
				
				recodeAlarm = p3k_Measure_Data.Alarm;
				DMA_Update_Flag = 1;
			}
			gonogo = p3k_Measure_Data.Go_NoGo;
			if((1==Data_tmp->SPEC)&&(Switch_ON==UTILITY.LOAD_CTL)&&(FunctionFlag&FUNC_NORMAL))
			{		
				if(1==gonogo)		
					GUI_SetColor(NG_Font_Bolor);
				else							
					GUI_SetColor(GO_Font_Bolor);				
				if((recodeGonogo != gonogo)||(redrawMeasureflag & gonogoFlag)){	
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( Meas_GoNoGo[gonogo], 230, 65);
					recodeGonogo = gonogo;
					DMA_Update_Flag = 1;
				}
			}
			else
			{
				if((recodeGonogo != 0)||(redrawMeasureflag & gonogoFlag)){
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( Meas_GoNoGo[0], 235, 65);
					recodeGonogo = 0;
					DMA_Update_Flag = 1;					
				}
			}			
			GUI_SetFont(Time_Alarm_Font);

			if( Data_tmp->CONF.Count_Time||Data_tmp->CONF.cut_off_time_total){					

				GUI_SetFont(Time_Alarm_Font);
				GUI_SetColor(Noted_Font_Bolor);
				if((last_sec!=p3k_Measure_Data.Sec)||(redrawMeasureflag & runtimeFlag)){
#if Enable_Func_DisTime
				unsigned long time_count;
					if(M_num != P_NSeq_EXECUTE){
						if(p3k_Measure_Data.Hour>=1000)
							sprintf( str, " 999:59:59 ");
						else
							sprintf( str, "     %01d:%02d:%02d ", p3k_Measure_Data.Hour, p3k_Measure_Data.Min, p3k_Measure_Data.Sec);
					}else{
						if((total_SEQ_time>3600000)||(Data_tmp->CONF.T_count_up)){ 
							sprintf( str, "     %01d:%02d:%02d ", p3k_Measure_Data.Hour, p3k_Measure_Data.Min, p3k_Measure_Data.Sec);
						}else{
							GUI_SetColor(GO_Font_Bolor);
							time_count = p3k_Measure_Data.Hour*3600 + p3k_Measure_Data.Min*60 + p3k_Measure_Data.Sec;
							if(total_SEQ_time>time_count){
								time_count = total_SEQ_time - time_count ;
								sprintf( str, "     %01d:%02d:%02d ", time_count/3600, (time_count/60)%60, time_count%60);
							}else{
								sprintf( str, " 0:00:00 ");
							}
						}
					}					
#else
					if(p3k_Measure_Data.Hour>=1000)
						sprintf( str, " 999:59:59 ");
					else
						sprintf( str, "     %01d:%02d:%02d ", p3k_Measure_Data.Hour, p3k_Measure_Data.Min, p3k_Measure_Data.Sec);
#endif
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, 315, 84+2);
					last_sec=p3k_Measure_Data.Sec;
					DMA_Update_Flag = 1;
				}
			}else{
				GUI_SetFont(Time_Alarm_Font);
				GUI_SetColor(Noted_Font_Bolor);
				//GUI_SetBkColor(MEM_DARKGREEN_ku); //
				if(redrawMeasureflag & runtimeFlag){
					sprintf( str, "                   ");					
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, 315, 84+2);
					last_sec=p3k_Measure_Data.Sec;
					DMA_Update_Flag = 1;
				}
			}
			asm("nop;");
			redrawMeasureflag &= ~(0x7C);/////////////
			break;		
		case 2:
			Display_Measure_Pro(Volt_Mode,str);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, 136, 17);
			Display_Measure_Pro(Curr_Mode,str);
			GUI_SetTextAlign(GUI_TA_RIGHT);	
			GUI_DispStringAt(str, 136, 61);
#if Enable_Func_select
			if(funcDisFlag){				
				GUI_SetFont(Measure_Font);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( " 	                    		  ", 318, 17);				
				GUI_SetColor(Parameter_Select_Bar_Bolor);
				GUI_SetFont(Measure_Unit_Font);
				GUI_SetBkColor(Parameter_Font_U_Bolor);
				//GUI_DispStringAt( "  PROG  ",210,25);
				
				if(P3k_Chan_Data.Load_Type==Prog_Load)
					GUI_DispStringAt( "  PROG  ",200,30);
				else if(P3k_Chan_Data.Load_Type==NSeq_Load)
					GUI_DispStringAt( "  NSEQ  ",200,30);
				else if(P3k_Chan_Data.Load_Type==FSeq_Load)
					GUI_DispStringAt( "  FSEQ  ",200,30);
				else if(P3k_Chan_Data.Load_Type==OCP_Load)
					GUI_DispStringAt( "   OCP  ",200,30);
#if Enable_Battery_Discharge
				else if(P3k_Chan_Data.Load_Type==OPP_Load)
					GUI_DispStringAt( "   OPP  ",200,30);
				else if(P3k_Chan_Data.Load_Type==BATT_Load)
					GUI_DispStringAt( "  BATT  ",200,30);
#endif
#if Enable_LED_function
				else if(P3k_Chan_Data.Load_Type==FLED_Load)
					GUI_DispStringAt( "   LED  ",200,30);
				else if(P3k_Chan_Data.Load_Type==CLED_Load)
					GUI_DispStringAt( "  CLED  ",200,30);
#endif				
				GUI_SetColor(Noted_Font_Bolor);
				GUI_SetFont(Measure_Font);
				GUI_SetBkColor(Parameter_Bottom_Bolor);
			}else{
				Display_Measure_Pro(Watt_Mode,str);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, 294, 17);		
				GUI_SetFont(Measure_Unit_Font);
				GUI_DispStringAt( "W",294,30);
			}
			GUI_SetFont(Measure_Unit_Font);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( "V",154,30);		
#else
			Display_Measure_Pro(Watt_Mode,str);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, 294, 17);		
			GUI_SetFont(Measure_Unit_Font);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( "V",154,30);		
			GUI_DispStringAt( "W",294,30);
#endif

			if((LOW_RANGE==Data_tmp->IRange)&&(Data_tmp->CURRMODE != P_CR))
				GUI_DispStringAt( "mA ",135,75);
			else							
				GUI_DispStringAt( "A   ",135,75);
			dis_cnt =1;
			redrawMeasureflag = MeasureAllFlag;
			DMA_Update_Flag = 1;
			break;
		default:
			break;
	}
	GUI_SetTextAlign(GUI_TA_LEFT);
	
}


#if 0// 2013.10.23
	void RedrawMeasure(void)
{
	const char Meas_GoNoGo[3][15]= {"           "," NG "," GO "};
	char str[30];
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	char i;
	
	GUI_SetFont(Measure_Font);
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Noted_Font_Bolor);
#if 0//Enable_DMA_Display
	Display_Parameter_Pro(p3k_Measure_Data.VOLT,str,(ptrMODEL_TYPE->CV)[3*Data_tmp->VRange].precision);
	ShowSpace( 5, 150, 16);
	GUI_SetTextAlign(GUI_TA_RIGHT);
	GUI_DispStringAt( str, 150, 16);
#else
	Display_Measure_Pro(Volt_Mode,str);
	GUI_SetTextAlign(GUI_TA_RIGHT);
	GUI_DispStringAt( str, 136, 17);
#endif

#if 0//Enable_DMA_Display
	if(LOW_RANGE==Data_tmp->IRange)		Display_Parameter_Pro((p3k_Measure_Data.CURR*1000.0),str,(ptrMODEL_TYPE->CC)[10*Data_tmp->IRange].precision-3);
	else								Display_Parameter_Pro(p3k_Measure_Data.CURR,str,(ptrMODEL_TYPE->CC)[10*Data_tmp->IRange].precision);
	ShowSpace( 5, 150, 60);
	GUI_SetTextAlign(GUI_TA_RIGHT);
	GUI_DispStringAt( str, 150, 60);
#else

	Display_Measure_Pro(Curr_Mode,str);
	GUI_SetTextAlign(GUI_TA_RIGHT);	
	GUI_DispStringAt(str, 136, 61);

#endif


	Display_Measure_Pro(Watt_Mode,str);
	GUI_SetTextAlign(GUI_TA_RIGHT);
	GUI_DispStringAt( str, 294, 17);


	GUI_SetFont(Measure_Unit_Font);
	GUI_SetTextAlign(GUI_TA_RIGHT);
	GUI_DispStringAt( "V",154,30);
	GUI_DispStringAt( "W",294,30);

	if(LOW_RANGE==Data_tmp->IRange)
		GUI_DispStringAt( "mA ",135,75);
	else							
		GUI_DispStringAt( "A   ",135,75);

	GUI_SetFont(Time_Alarm_Font);
	if( Data_tmp->CONF.Count_Time||Data_tmp->CONF.Cut_Off_Time )
	{
		GUI_SetFont(Time_Alarm_Font);
		GUI_SetColor(Noted_Font_Bolor);
		if(p3k_Measure_Data.Hour>=1000)	
			sprintf( str, " 999:59:59 ");
		else						
			sprintf( str, "     %01d:%02d:%02d ", p3k_Measure_Data.Hour, p3k_Measure_Data.Min, p3k_Measure_Data.Sec);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, 315, 84);
	}

	GUI_SetColor(Alarm_Font_Bolor);
	GUI_SetTextAlign(GUI_TA_RIGHT);

	GUI_DispStringAt( Meas_Alarm[p3k_Measure_Data.Alarm], 312, 65);
		
	if((1==Data_tmp->SPEC)&&(Switch_ON==UTILITY.LOAD_CTL)&&(FunctionFlag&FUNC_NORMAL))
	{
		if(1==p3k_Measure_Data.Go_NoGo)		
			GUI_SetColor(NG_Font_Bolor);
		else							
			GUI_SetColor(GO_Font_Bolor);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( Meas_GoNoGo[p3k_Measure_Data.Go_NoGo], 230, 65);
	}
	else
	{
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( Meas_GoNoGo[0], 235, 65);
	}
}
#endif
void DispMeasureData(void){

#if 1
	static char p3k_Measure_Temp;
	switch(M_num){
	case P_CC ... P_CP:
	case P_FUNC_FLED_EXECUTE:
	case P_FUNC_CLED_EXECUTE:
		if(p3k_Measure_Temp==0)
			ClearP3KMeasBG(Parameter_Bottom_Bolor);
		p3k_Measure_Temp=1;
		RedrawMeasure();
		break;
	case P_CAL_MODE:
		if((!p3k_Measure_Data.Alarm)||(p3k_Measure_Data.Alarm == UnReg_Alarm)){
			GUI_SetFont(Time_Alarm_Font);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(MEM_DARKRED_ku);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt(Meas_Alarm[p3k_Measure_Data.Alarm], 312, 40);
			DMA_Update_Flag = 1;
			last_menu = 0xFF;
		}
		break;
	case P_PROG_EXECUTE:
	case P_NSeq_EXECUTE:
	case P_FSeq_EXECUTE:
	case P_FUNC_OCP_EXECUTE:
	case P_FUNC_OPP_EXECUTE:
#if Enable_Battery_Discharge		
	case P_FUNC_batt_EXECUTE:
#endif
		RedrawMeasure();
		if(UTILITY.LOAD_CTL == Switch_OFF){
			DataRedrawFlag |= PARA_CHANGE;
			last_menu = 0xFF;
		}
		p3k_Measure_Temp = 1;
		DMA_Update_Flag = 1;
		break;
	default:
		if(p3k_Measure_Temp) {
			p3k_Measure_Temp=0;
			ClearDataBG(Parameter_Bottom_Bolor);
			DMA_Update_Flag = 1;
		}
		last_menu = 0xFF;
		break;
	}

#else
	static char sClearMeasBg;
	if(P_CP>=M_num){
		if(sClearMeasBg==0)	ClearP3KMeasBG(Parameter_Bottom_Bolor);
		sClearMeasBg=1;
		RedrawMeasure();
	}else if((!UTILITY.LOAD_CTL)&&((P_PROG_EXECUTE==M_num)||(P_NSeq_EXECUTE==M_num)||(P_FSeq_EXECUTE==M_num))){
		RedrawMeasure();
		sClearMeasBg = 0;		
	}else if((P_CAL_MODE == M_num)&&((!p3k_Measure_Data.Alarm)||(p3k_Measure_Data.Alarm == UnReg_Alarm))){
		GUI_SetFont(Time_Alarm_Font);
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(MEM_DARKRED_ku);
		GUI_SetTextAlign(GUI_TA_RIGHT);		
		GUI_DispStringAt(Meas_Alarm[p3k_Measure_Data.Alarm], 312, 40);
		DMA_Update_Flag = 1;
		last_menu = 0xFF;
	}else{
		if(sClearMeasBg){
			sClearMeasBg=0;
			ClearDataBG(Parameter_Bottom_Bolor);
			DMA_Update_Flag = 1;
		}
		if((M_num==P_PROG_EXECUTE)||(M_num==P_NSeq_EXECUTE)||(M_num==P_FSeq_EXECUTE)) {

		}else	last_menu = 0xFF;
	}
#endif
}

