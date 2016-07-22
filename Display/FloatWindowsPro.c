#include "includes.h"
#include "keydef.h"
#include "../menu/head.h"

#define	Old_FloatFrame_Program_Before_Sep_14 0			//於Sep 14, 2012 Blocking舊有的Float Windows Frame Function
extern void Pt2Float(void);
extern void Pt2Main(void);
extern void Update_Panel(void);
extern void Wait_For_MDMA_Ready(void);

void FloatWindowsDispOn(void)
{
	BYTE bRd;
	
	bRd = ReadRegByte(REG_SPECIAL_EFFECTS);
	bRd |=0x10; 								//Disable floating window
	WriteRegByte(REG_SPECIAL_EFFECTS,bRd);
}

void FloatWindowsDispOff(void)
{
	BYTE bRd;
	
	bRd = ReadRegByte(REG_SPECIAL_EFFECTS);
	bRd &=0xef; 								//Disable floating window
	WriteRegByte(REG_SPECIAL_EFFECTS,bRd);	
	//MemFree(floatMemoff + _MemAddress);
}

void FloatSetPixel(UWORD x, UWORD y, UBYTE color)
{
	UWORD off, dist;
	UBYTE data, *float_ptr;
	UBYTE dx,dy;

    float_ptr = (UBYTE *)(MemAddress+FloatMem_Off);

    off=320*(60-(y>>2))-x-1;
    float_ptr+=off;
    data=*float_ptr;
    dist=y&0x03;

	switch(dist)
	{
        case 0x01:
            data&=0xcf;
            data|=(color<<4);
            *float_ptr=data;
            break;
        case 0x00:
            data&=0x3f;
            data|=(color<<6);
            *float_ptr=data;
            break;
        case 0x03:
            data&=0xfc;
            data|=color;
            *float_ptr=data;
            break;
        case 0x02:
            data&=0xf3;
            data|=(color<<2);
            *float_ptr=data;
    }
}

void FloatFrame(int StartX, int StartY,int EndX, int EndY,int frame_width,GUI_COLOR frame_color)
{
	/* 將Protection Pop Windows 顯示位置改為置中，樣式的部份，字體為紅色粗體字，背景為黑底
	　，並再加上紅色粗邊框　　Sep 24, 2012新增　宗佑						－－－↓↓*/

	int i, width, column,	number_of_pixel;
	UWORD *mem_ptr, float_offset;
	int coordinate_temp;
	
	if(StartX>EndX)
	{
		coordinate_temp=EndX;
		EndX=StartX;
		StartX=coordinate_temp;
	}
	else if(StartY>EndY)
	{
		coordinate_temp=EndY;
		EndY=StartY;
		StartY=coordinate_temp;
	}


	//Right-Side Frame
	mem_ptr = (UWORD *)(FloatAddress);
	float_offset=256/2-(EndY+StartY);	//0x45=69←上邊框第一個像素,		0x44=68←離上邊框的距離
	mem_ptr+=float_offset;
	for (width=StartX;width<StartX+frame_width;width++)
	{
		for (number_of_pixel=0;number_of_pixel<(EndY+StartY);number_of_pixel++)
		{
			*(mem_ptr++)=(UWORD)frame_color;
		}
		mem_ptr = (UWORD *)(FloatAddress);
		float_offset+=0x100/2;			//256=0x100,		Bus=16 bits,		therefore 0x100/2
		mem_ptr+=float_offset;		
	}
	
	//Left-Side Frame
	mem_ptr = (UWORD *)(FloatAddress);
	float_offset=256*(EndX-StartX-frame_width)/2+(256/2-(EndY+StartY));	//先算 X 座標的像素位置，再減掉 Width，再算上邊框的 Y座標
	mem_ptr+=float_offset;
	for (width=EndY-frame_width;width<EndY;width++)
	{
		for (number_of_pixel=0;number_of_pixel<(EndY+StartY);number_of_pixel++)
		{
			*(mem_ptr++)=(UWORD)frame_color;
		}
		mem_ptr = (UWORD *)(FloatAddress);
		float_offset+=0x100/2;			//256=0x100,		Bus=16 bits,		therefore 0x100/2,		go to next column
		mem_ptr+=float_offset;	
	}

	//Upper-Side Frame
	mem_ptr = (UWORD *)(FloatAddress);
	float_offset=256/2-(EndY+StartY);	//0x45=69←上邊框第一個像素,		0x44=68←離上邊框的距離
	mem_ptr+=float_offset;
	for (column=0;column<EndX-StartX;column++)
	{
		for (width=0;width<frame_width;width++)
		{
			*(mem_ptr++)=(UWORD)frame_color;
		}
		mem_ptr = (UWORD *)(FloatAddress);
		float_offset+=0x100/2;			//256=0x100,		Bus=16 bits,		therefore 0x100/2
		mem_ptr+=float_offset;		
	}

	//Lower-Side Frame
	mem_ptr = (UWORD *)(FloatAddress);
	float_offset=(256-StartY)/2;		//0x078=60+60=120←離下邊框的距離,		從0x76位置畫3個像素,		0x000=StartX=48,		0x200=StartX+2=50
	mem_ptr+=float_offset;
	for (column=0;column<EndX-StartX;column++)
	{
		for (width=0;width<frame_width;width++)
		{
			*(mem_ptr++)=(UWORD)frame_color;
		}
		mem_ptr = (UWORD *)(FloatAddress);
		float_offset+=0x100/2;			//256=0x100,		Bus=16 bits,		therefore 0x100/2
		mem_ptr+=float_offset;		
	}


	/* 將Protection Pop Windows 顯示位置改為置中，樣式的部份，字體為紅色粗體字，背景為黑底
	　，並再加上紅色粗邊框　　Sep 24, 2012新增　宗佑						－－－↑↑*/


#if Old_FloatFrame_Program_Before_Sep_14		//於Sep 14, 2012 Blocking舊有的Float Windows Frame Function
	int i;
	
	for(i=20;i<203;i++)
	{
		FloatSetPixel(100,i,Cursor1Col2);	/*LIGHT GRAY*/
		FloatSetPixel(101,i,Cursor1Col3);	/*ORANGE*/
		FloatSetPixel(102,i,Cursor1Col2);	/*LIGHT GRAY*/
	}
#endif
}

void Float_Windows_Setting(int StartX, int StartY,int EndX, int EndY,GUI_COLOR color)	
{
	int i;
	UWORD *mem_ptr;

	/*　coordinate_temp主要目的：
		一、進行座標變數的交換，作為暫存EndX或EndY這兩個變數之用。
　　　　二、確保StartX與Start Y永遠小於等於EndX與EndY，以避免繪製
			Floating Windows時會產生錯誤。

		Sep 24, 2012新增					宗佑－－－↓↓↓*/
	int coordinate_temp;			
	/*　coordinate_temp主要目的：
		一、進行座標變數的交換，作為暫存EndX或EndY這兩個變數之用。
　　　　二、確保StartX與Start Y永遠小於等於EndX與EndY，以避免繪製
			Floating Windows時會產生錯誤。

		Sep 24, 2012新增					宗佑－－－↑↑↑*/
	
	if(StartX>EndX)
	{
		coordinate_temp=EndX;
		EndX=StartX;
		StartX=coordinate_temp;
	}
	else if(StartY>EndY)
	{
		coordinate_temp=EndY;
		EndY=StartY;
		StartY=coordinate_temp;
	}

	WriteRegByte(REG_FLOAT_WIN_X_START_POS0,StartX&0x00FF);
	WriteRegByte(REG_FLOAT_WIN_X_START_POS1,(StartX&0xFF00)>>8);
	WriteRegByte(REG_FLOAT_WIN_Y_START_POS0,StartY&0x00FF);		/*204/4-1=50=32 h*/	
	WriteRegByte(REG_FLOAT_WIN_Y_START_POS1,(StartY&0xFF00)>>8);
	WriteRegByte(REG_FLOAT_WIN_X_END_POS0,EndX&0x00FF);			/*320-1=319=13f h*/
	WriteRegByte(REG_FLOAT_WIN_X_END_POS1,(EndX&0xFF00)>>8);
	WriteRegByte(REG_FLOAT_WIN_Y_END_POS0,EndY&0x00FF);			/*240/4-1=59=3b h*/
	WriteRegByte(REG_FLOAT_WIN_Y_END_POS1,(EndY&0xFF00)>>8);	

	mem_ptr = (UWORD *)(FloatAddress);	
	for(i=0;i<256*320/2;i++)
        *(mem_ptr++)=(UWORD)color;

}
void FloatWindows_StringAt(const char GUI_FAR *s, int x, int y) 
{
	UWORD Origin_X,Origin_Y;
	UBYTE Origin_Data_1,Origin_Data_2;

	Origin_Data_1 = ReadRegByte(REG_FLOAT_WIN_X_START_POS0);
	Origin_Data_2 = ReadRegByte(REG_FLOAT_WIN_X_START_POS1);
	Origin_X=(Origin_Data_2<<8) + Origin_Data_1;
	Origin_Data_1 = ReadRegByte(REG_FLOAT_WIN_Y_START_POS0);
	Origin_Data_2 = ReadRegByte(REG_FLOAT_WIN_Y_START_POS1);
	Origin_Y=(Origin_Data_2<<8) + Origin_Data_1;
	Pt2Float();
	GUI_DispStringAt(s, x+Origin_X, y+(4*Origin_Y));
	Pt2Main();
}

void FloatWindows_GotoXY(int x, int y) 
{
	UWORD Origin_X,Origin_Y;
	UBYTE Origin_Data_1,Origin_Data_2;
	Origin_Data_1 = ReadRegByte(REG_FLOAT_WIN_X_START_POS0);
	Origin_Data_2 = ReadRegByte(REG_FLOAT_WIN_X_START_POS1);
	Origin_X=(Origin_Data_2<<8) + Origin_Data_1;
	Origin_Data_1 = ReadRegByte(REG_FLOAT_WIN_Y_START_POS0);
	Origin_Data_2 = ReadRegByte(REG_FLOAT_WIN_Y_START_POS1);
	Origin_Y=(Origin_Data_2<<8) + Origin_Data_1;
	GUI_GotoXY(x+Origin_X, y+(4*Origin_Y));
}


static const char IRange_Item[3][10]={"Low"	,"High"	,"High"};

void Show_IRange_Window(void)
{
	char i;
	char IRange_S[20];
	char IRange_Specially_S[20];
	unsigned char Parallel_Num = 0;
	unsigned char Booster_Num = 0;

	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	Wait_For_MDMA_Ready();

	if(M_num==P_CR)
		Float_Windows_Setting(150 ,10,310,24,MEM_LIGHTGRAY_ku);
	else if(M_num==P_CP)
		Float_Windows_Setting(53  ,10,310,24,MEM_LIGHTGRAY_ku);
	else							
		Float_Windows_Setting(160 ,10,310,24,MEM_LIGHTGRAY_ku);

	//Parallel_Num = Disp_tmp->CONF.Para_Data.Parallel_Number;
	//Booster_Num	 = Disp_tmp->CONF.Para_Data.Booster_Number;

	for(i=LOW_RANGE ; i<=HIGH_RANGE ; i++) 
	{
		//if((P3k_Disp_Data.CONF.Para_Data.Booster_Number)&&(i==Mid_RANGE))
		//	continue;	
		if(Booster_Num)
		{
			sprintf(IRange_S,"%.2fA",((ptrMODEL_TYPE->IRange_Display)[15+i+3*(Booster_Num-1)].Current));
		
			if(M_num==P_CR) 
				sprintf(IRange_Specially_S,"%.5fS",((ptrMODEL_TYPE->IRange_Display)[15+i+3*(Booster_Num-1)].Resistance));
			else			
				sprintf(IRange_Specially_S,"%.2fW",((ptrMODEL_TYPE->IRange_Display)[15+i+3*(Booster_Num-1)].Power));
		}
		else
		{
			sprintf(IRange_S,"%.2fA",((ptrMODEL_TYPE->IRange_Display)[i+3*Parallel_Num].Current));

			if(M_num==P_CR) 
				sprintf(IRange_Specially_S,"%.4fS",((ptrMODEL_TYPE->IRange_Display)[i+3*Parallel_Num].Resistance));
			else			
				sprintf(IRange_Specially_S,"%.2fW",((ptrMODEL_TYPE->IRange_Display)[i+3*Parallel_Num].Power));
		}
		GUI_SetFont(Parameter_Font);
		GUI_SetBkColor(MEM_LIGHTGRAY_ku);
		GUI_SetColor(GW_WHITE);
		 
		if(i==P3k_Disp_Data.IRange)
		{
			GUI_SetBkColor(MEM_ORANGE_ku);
			FloatWindows_GotoXY(15,170-(i*25));
			Pt2Float();
			if( (M_num==P_CR)||(M_num==P_CP) )
				GUI_DispChars(' ',50);
			else								
				GUI_DispChars(' ',28);
			Pt2Main();
		}

		if(M_num == P_CR){
			FloatWindows_StringAt(IRange_Item[i]	,20	,170-(i*25));
			GUI_SetTextAlign(GUI_TA_RIGHT);
			FloatWindows_StringAt(IRange_Specially_S	,160	,170-(i*25));
		}else{
			FloatWindows_StringAt(IRange_Item[i]	,20	,170-(i*25));
			GUI_SetTextAlign(GUI_TA_RIGHT);
			FloatWindows_StringAt(IRange_S	,150	,170-(i*25));
		}
		
		if(M_num==P_CP)
		{
			GUI_SetTextAlign(GUI_TA_RIGHT);
			FloatWindows_StringAt(IRange_Specially_S,260,170-(i*25));
		}
	}
	Float_Window_Count = 150;
	CtrlFlag1 |= Disp_IRange_Window + Float_Windows_DispOn;
	DMA_Update_Flag = 1;
	Update_Panel();
}

void Show_TimeUp_Window(void)
{
	char str[30];
	Wait_For_MDMA_Ready();
	Float_Windows_Setting(70,10,255,30,MEM_WHITE);
	GUI_SetFont(Parameter_Font);
	GUI_SetBkColor(MEM_WHITE);
	GUI_SetColor(Message_Font_Bolor);		
	GUI_SetTextAlign(GUI_TA_LEFT);
	
	if(p3k_Measure_Data.VOLT>=100.0)	
		sprintf( str, " Voltage : %3.2fV ", p3k_Measure_Data.VOLT);
	else if( p3k_Measure_Data.VOLT>=10.0)	
		sprintf( str, " Voltage : %2.3fV ", p3k_Measure_Data.VOLT);
	else								
		sprintf( str, " Voltage : %1.4fV ", p3k_Measure_Data.VOLT);

	FloatWindows_StringAt(" Time Up ",115,120);
	FloatWindows_StringAt(str,75,145);
	FloatWindows_StringAt(" Enter ",130,170);

	//CtrlFlag1 |= Disp_Middle_Message + Float_Windows_DispOn;
	CtrlFlag1 |= Function_Lock + Float_Windows_DispOn;
	DMA_Update_Flag = 1;
	Update_Panel();
	//OSTimeDly(50);
}

void Show_Seq_fix(void)
{
	char str[30];
	Wait_For_MDMA_Ready();
	Float_Windows_Setting(70,10,255,30,MEM_WHITE);
	GUI_SetFont(Parameter_Font);
	GUI_SetBkColor(MEM_WHITE);
	GUI_SetColor(Message_Font_Bolor);		
	GUI_SetTextAlign(GUI_TA_LEFT);
	if(M_num ==P_Seq_Fast){	
		FloatWindows_StringAt("Delete all points",88,120);
		if(DispCT ==0x01)
			FloatWindows_StringAt("Before change mode",66,145);
		else
			FloatWindows_StringAt("Before change range",66,145);
		FloatWindows_StringAt(" ENTER ",120,170);
	}else if(M_num ==P_Seq_Normal){
		sprintf( str, " Seq. No: S%d ", P3k_NSeq_Disp.NSeq_Number+1);	
		FloatWindows_StringAt("Delete all points",88,120);
		if(DispCT ==0x03)
			FloatWindows_StringAt("Before change mode",66,145);
		else
			FloatWindows_StringAt("Before change range",66,145);
		FloatWindows_StringAt(" ENTER ",120,170);
	}
	CtrlFlag1 |= Function_Lock + Float_Windows_DispOn;
	DMA_Update_Flag = 1;
	delaySeqAlarmDisplay =3;
	Update_Panel();
}

void Show_Calibration_Error_Window(void)
{
	char Cal_Alarm[5][30]=  {" Measure Offset Error "," CPP Offset Error "," R.OCP Offset Error"," OPP Offset Error"," OCP Offset Error"};
	if(P_CAL_MODE==M_num)
	{
		Wait_For_MDMA_Ready();
		Float_Windows_Setting(0,10,310,52,MEM_WHITE);
		GUI_SetFont(Parameter_Font);
		GUI_SetBkColor(MEM_WHITE);
		GUI_SetColor(NG_Font_Bolor);	
		Pt2Float();
		GUI_DispChars(' ',70);
		Pt2Main();
		
		if(Cal_Offset_Error&CXCV_Err)	
			FloatWindows_StringAt(" CXCV Offset Error"		,50 ,25+1*25);
		if(Cal_Offset_Error&Meas_Err)	
			FloatWindows_StringAt(" Measure Offset Error "	,50 ,25+2*25);
		if(Cal_Offset_Error&CPP_Err)	
			FloatWindows_StringAt(" CPP Offset Error "		,50 ,25+3*25);
		if(Cal_Offset_Error&ROCP_Err)
			FloatWindows_StringAt(" R.OCP Offset Error"		,50 ,25+4*25);
		if(Cal_Offset_Error&OPP_Err)	
			FloatWindows_StringAt(" OPP Offset Error"		,50 ,25+5*25);
		if(Cal_Offset_Error&OCP_Err)	
			FloatWindows_StringAt(" OCP Offset Error"		,50 ,25+6*25);
		Float_Window_Count = 2000;
		CtrlFlag1 |= Disp_IRange_Window + Float_Windows_DispOn;
		DMA_Update_Flag = 1;
		Update_Panel();
		OSTimeDly(200);
	}
}

void Show_Cache_Setting(void)
{
	char Cache_str[100][100];
	UBYTE i,j;
	Wait_For_MDMA_Ready();
	Float_Windows_Setting(0,10,310,52,MEM_WHITE);
	GUI_SetFont(Parameter_Font);
	GUI_SetBkColor(MEM_WHITE);
	GUI_SetColor(NG_Font_Bolor);	
	Pt2Float();
	GUI_DispChars(' ',70);
	Pt2Main();
	
	sprintf(Cache_str[0],"pIMEM_CONTROL=0x%x\n",*(unsigned long *)pIMEM_CONTROL);
	sprintf(Cache_str[1],"pICPLB_STATUS=0x%x\n",*(unsigned long *)pICPLB_STATUS);
	sprintf(Cache_str[2],"ICPLB_FAULT_ADDR=0x%x\n",*(unsigned long *)ICPLB_FAULT_ADDR);	
	sprintf(Cache_str[3],"ICPLB_ADDR0=0x%x\n",*(unsigned long *)ICPLB_ADDR0);
	sprintf(Cache_str[4],"ICPLB_ADDR1=0x%x\n",*(unsigned long *)ICPLB_ADDR1);
	sprintf(Cache_str[5],"ICPLB_ADDR2=0x%x\n",*(unsigned long *)ICPLB_ADDR2);
	sprintf(Cache_str[6],"ICPLB_ADDR3=0x%x\n",*(unsigned long *)ICPLB_ADDR3);

	sprintf(Cache_str[7],"ICPLB_ADDR4=0x%x\n",(unsigned long *)ICPLB_ADDR4);
	sprintf(Cache_str[8],"ICPLB_ADDR5=0x%x\n",(unsigned long *)ICPLB_ADDR5);
	sprintf(Cache_str[9],"ICPLB_ADDR6=0x%x\n",(unsigned long *)ICPLB_ADDR6);
	sprintf(Cache_str[10],"ICPLB_ADDR7=0x%x\n",(unsigned long *)ICPLB_ADDR7);
	sprintf(Cache_str[11],"ICPLB_ADDR8=0x%x\n",(unsigned long *)ICPLB_ADDR8);
	sprintf(Cache_str[12],"ICPLB_ADDR9=0x%x\n",(unsigned long *)ICPLB_ADDR9);
	sprintf(Cache_str[13],"ICPLB_ADDR10=0x%x\n",(unsigned long *)ICPLB_ADDR10);
	
	sprintf(Cache_str[14],"ICPLB_ADDR11=0x%x\n",(unsigned long *)ICPLB_ADDR11);
	sprintf(Cache_str[15],"ICPLB_ADDR12=0x%x\n",(unsigned long *)ICPLB_ADDR12);
	sprintf(Cache_str[16],"ICPLB_ADDR13=0x%x\n",(unsigned long *)ICPLB_ADDR13);
	sprintf(Cache_str[17],"ICPLB_ADDR14=0x%x\n",(unsigned long *)ICPLB_ADDR14);
	sprintf(Cache_str[18],"ICPLB_ADDR15=0x%x\n",(unsigned long *)ICPLB_ADDR15);
	
	sprintf(Cache_str[19],"ICPLB_DATA0=0x%x\n",(unsigned long *)ICPLB_DATA0);
	sprintf(Cache_str[20],"ICPLB_DATA1=0x%x\n",(unsigned long *)ICPLB_DATA1);
	sprintf(Cache_str[21],"ICPLB_DATA2=0x%x\n",(unsigned long *)ICPLB_DATA2);
	sprintf(Cache_str[22],"ICPLB_DATA3=0x%x\n",(unsigned long *)ICPLB_DATA3);
	sprintf(Cache_str[23],"ICPLB_DATA4=0x%x\n",(unsigned long *)ICPLB_DATA4);
	sprintf(Cache_str[24],"ICPLB_DATA5=0x%x\n",(unsigned long *)ICPLB_DATA5);
	sprintf(Cache_str[25],"ICPLB_DATA6=0x%x\n",(unsigned long *)ICPLB_DATA6);
	sprintf(Cache_str[26],"ICPLB_DATA7=0x%x\n",(unsigned long *)ICPLB_DATA7);
	sprintf(Cache_str[27],"ICPLB_DATA8=0x%x\n",(unsigned long *)ICPLB_DATA8);
	sprintf(Cache_str[28],"ICPLB_DATA9=0x%x\n",(unsigned long *)ICPLB_DATA9);
	sprintf(Cache_str[29],"ICPLB_DATA10=0x%x\n",(unsigned long *)ICPLB_DATA10);
	sprintf(Cache_str[30],"ICPLB_DATA11=0x%x\n",(unsigned long *)ICPLB_DATA11);
	sprintf(Cache_str[31],"ICPLB_DATA12=0x%x\n",(unsigned long *)ICPLB_DATA12);
	sprintf(Cache_str[32],"ICPLB_DATA13=0x%x\n",(unsigned long *)ICPLB_DATA13);
	sprintf(Cache_str[33],"ICPLB_DATA14=0x%x\n",(unsigned long *)ICPLB_DATA14);
	sprintf(Cache_str[34],"ICPLB_DATA15=0x%x\n",(unsigned long *)ICPLB_DATA15);

	j = 0;
	for(i=0 ; i<5 ; i++)
	{
		Float_Windows_Setting(0,10,310,52,MEM_WHITE);
		FloatWindows_StringAt(Cache_str[j++] ,30 ,25+0*25);
		FloatWindows_StringAt(Cache_str[j++] ,30 ,25+1*25);
		FloatWindows_StringAt(Cache_str[j++] ,30 ,25+2*25);
		FloatWindows_StringAt(Cache_str[j++] ,30 ,25+3*25);
		FloatWindows_StringAt(Cache_str[j++] ,30 ,25+4*25);
		FloatWindows_StringAt(Cache_str[j++] ,30 ,25+5*25);
		FloatWindows_StringAt(Cache_str[j++] ,30 ,25+6*25);
		Float_Window_Count = 2000;
		CtrlFlag1 |= Disp_IRange_Window + Float_Windows_DispOn;
		DMA_Update_Flag = 1;
		Update_Panel();
		OSTimeDly(1000);
	}
}

void Show_SDRAM_Setting(void)	
{
	char SDRAM_str[5][100];
	Wait_For_MDMA_Ready();
	//Float_Windows_Setting(0,10,310,40,MEM_WHITE);
	Float_Windows_Setting(0,10,310,52,MEM_WHITE);
	GUI_SetFont(Parameter_Font);
	GUI_SetBkColor(MEM_WHITE);
	GUI_SetColor(NG_Font_Bolor);	
	Pt2Float();
	GUI_DispChars(' ',70);
	Pt2Main();

	sprintf(SDRAM_str[0],"EBIU_SDGCTL=0x%x\n",*(unsigned long *)EBIU_SDGCTL);
	sprintf(SDRAM_str[1],"EBIU_SDBCTL=0x%x\n",*(unsigned short *)EBIU_SDBCTL);
	sprintf(SDRAM_str[2],"EBIU_SDRRC=0x%x\n",*(unsigned short *)EBIU_SDRRC);	
	sprintf(SDRAM_str[3],"pEBIU_AMBCTL0=0x%x\n",*(unsigned long *)pEBIU_AMBCTL0);
	sprintf(SDRAM_str[4],"pEBIU_AMBCTL1=0x%x\n",*(unsigned long *)pEBIU_AMBCTL1);	

	FloatWindows_StringAt(SDRAM_str[0] ,30 ,25+0*25);
	FloatWindows_StringAt(SDRAM_str[1] ,30 ,25+1*25);
	FloatWindows_StringAt(SDRAM_str[2] ,30 ,25+2*25);
	FloatWindows_StringAt(SDRAM_str[3] ,30 ,25+3*25);
	FloatWindows_StringAt(SDRAM_str[4] ,30 ,25+4*25);
	Float_Window_Count = 2000;
	CtrlFlag1 |= Disp_IRange_Window + Float_Windows_DispOn;
	DMA_Update_Flag = 1;
	Update_Panel();
	OSTimeDly(1000);
}

void Show_Prot_Error_Window(UBYTE Error_Mode,double Error_Gain,double Error_Offset,UWORD Input_HP,UWORD Input_LP,UWORD System_HP,UWORD System_LP)
{
	char Error_str[5][30]=  {" OCP Error "," Rating OCP Error "," OPP Error"," CPP Offset Error"," CX+CV Error"};
	char Temp_str[50];
	
	Wait_For_MDMA_Ready();
	Float_Windows_Setting(0,10,310,52,MEM_WHITE);
	GUI_SetFont(Parameter_Font);
	GUI_SetBkColor(MEM_WHITE);
	GUI_SetColor(NG_Font_Bolor);	
	Pt2Float();
	GUI_DispChars(' ',70);
	Pt2Main();
	
	FloatWindows_StringAt(Error_str[Error_Mode]	,50 ,25+0*25);
	
	sprintf(Temp_str,"Gain=%3.3f\n",Error_Gain);
	FloatWindows_StringAt(Temp_str				,50 ,25+1*25);
	sprintf(Temp_str,"Offset=%3.3f\n",Error_Offset);
	FloatWindows_StringAt(Temp_str				,50 ,25+2*25);
	sprintf(Temp_str,"Input_HP=%d\n",Input_HP);
	FloatWindows_StringAt(Temp_str				,50 ,25+3*25);
	sprintf(Temp_str,"Input_LP=%d\n",Input_LP);
	FloatWindows_StringAt(Temp_str				,50 ,25+4*25);
	sprintf(Temp_str,"System_HP=%d\n",System_HP);
	FloatWindows_StringAt(Temp_str				,50 ,25+5*25);
	sprintf(Temp_str,"System_LP=%d\n",System_LP);
	FloatWindows_StringAt(Temp_str				,50 ,25+6*25);
	
	Float_Window_Count = 2000;
	CtrlFlag1 |= Disp_IRange_Window + Float_Windows_DispOn;
	DMA_Update_Flag = 1;
	Update_Panel();
	OSTimeDly(1000);
}

void Show_XYZ_Window(void)
{
#if 1
	char Data_str[50];
	Wait_For_MDMA_Ready();
	Float_Windows_Setting(0,10,310,40,MEM_WHITE);
	GUI_SetFont(Parameter_Font);
	GUI_SetBkColor(MEM_WHITE);
	GUI_SetColor(NG_Font_Bolor);	
	Pt2Float();
	GUI_DispChars(' ',70);
	Pt2Main();

	sprintf(Data_str,"XH = %05d,XL = %05d\n",p3k_Cal_data.PSensor.XH_Value,p3k_Cal_data.PSensor.XL_Value);
	FloatWindows_StringAt(Data_str,50 ,50+75);
	sprintf(Data_str,"YH = %05d,YL = %05d\n",p3k_Cal_data.PSensor.YH_Value,p3k_Cal_data.PSensor.YL_Value);
	FloatWindows_StringAt(Data_str,50 ,50+100);
	sprintf(Data_str,"ZH = %05d,ZL = %05d\n",p3k_Cal_data.PSensor.ZH_Value,p3k_Cal_data.PSensor.ZL_Value);
	FloatWindows_StringAt(Data_str,50 ,50+125);
	
	CtrlFlag1 |= Disp_Middle_Message + Float_Windows_DispOn;
	DMA_Update_Flag = 1;
	Update_Panel();
	OSTimeDly(300);
#endif	
}

void Show_APP_Message(UBYTE Kind)
{
	Wait_For_MDMA_Ready();
	Float_Windows_Setting(5,22,313,34,MEM_WHITE);
	GUI_SetFont(Parameter_Font);
	GUI_SetBkColor(MEM_WHITE);
	GUI_SetColor(NG_Font_Bolor);

	if(Kind==0)	
		FloatWindows_StringAt(" Please use the Power Analysis ",		25 ,100);
	else		
		FloatWindows_StringAt(" Please use the Power Analysis ",		25 ,100);

	FloatWindows_StringAt(" license code to enable the Function ",	5 ,125);
	
	CtrlFlag1 |= Disp_Middle_Message + Float_Windows_DispOn;
	DMA_Update_Flag = 1;
	Update_Panel();
	OSTimeDly(100);
}

extern void ClearKeyBoard(void);
extern char Display_Parameter_Pro(double Parameter, char *buf, char precision);
void Show_Mem_Recall_Message(UBYTE Mem_Mode,UBYTE Mem_Range,UWORD Mem_Data,char mode)
{
	float fdat;
	char Data_Str[30];
	char Message_Str[50];
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	
	Wait_For_MDMA_Ready();
	Float_Windows_Setting(52,34,315,53,MEM_WHITE);
	GUI_SetFont(Parameter_Font);
	GUI_SetBkColor(MEM_WHITE);
	GUI_SetColor(NG_Font_Bolor);
	if(Mem_Mode==CC_MODE)
	{
		fdat = Mem_Data * (ptrMODEL_TYPE->CC)[Mem_Range*10].Resolution;
		Display_Parameter_Pro(fdat,Data_Str,(ptrMODEL_TYPE->CC)[Mem_Range*10].precision);
		sprintf(Message_Str," Recall CC %s A ",Data_Str);
	}
	else if(Mem_Mode==CR_MODE)
	{
		fdat = Mem_Data * (ptrMODEL_TYPE->CR)[Mem_Range*10].Resolution;
		if(Data_tmp->CONF.D_CR_Unit==OHM_Unit)
		{
			Display_Parameter_Pro((1000.0/fdat),Data_Str,7);
			sprintf(Message_Str," Recall CR %s \x82 ",Data_Str);
		}
		else
		{
			Display_Parameter_Pro(fdat,Data_Str,(ptrMODEL_TYPE->CR)[Mem_Range*10].precision);
			sprintf(Message_Str," Recall CR %s m\x83 ",Data_Str);
		}
	}
	else if(Mem_Mode==CV_MODE)
	{
		fdat = Mem_Data * (ptrMODEL_TYPE->CV)[Mem_Range*3].Resolution;
		Display_Parameter_Pro(fdat,Data_Str,(ptrMODEL_TYPE->CV)[Mem_Range*3].precision);
		sprintf(Message_Str," Recall CV %s V ",Data_Str);
	}
	else
	{
		fdat = Mem_Data * (ptrMODEL_TYPE->CP)[Mem_Range*10].Resolution;
		Display_Parameter_Pro(fdat,Data_Str,(ptrMODEL_TYPE->CP)[Mem_Range*10].precision);
		sprintf(Message_Str," Recall CP %s W ",Data_Str);
	}

	FloatWindows_StringAt(Message_Str,	45	,35);
	
	if(mode == SR_PRESET_MODE)
		FloatWindows_StringAt(" Press Enter To Recall Preset ",5	,60);
	else
		FloatWindows_StringAt("Press Enter To Recall Memory ",5	,60);

	CtrlFlag1 |= Disp_Middle_Message + Float_Windows_DispOn;
	DMA_Update_Flag = 1;
	Update_Panel();
	OSTimeDly(50);
	ClearKeyBoard();
}

