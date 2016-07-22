//*************************************************************************************
// NOTE: 
// I.  There are several conditions that may cause function error:
//       1. HELP message includes string "<L.. "
//       2.
// II. The total line of HELP message must less than 999 lines.
//*************************************************************************************
#include "../INCLUDES.H"   
#include "head.h"
#include "menu.h"
#include "help_msg.h"
//#include "../bmpfont/uwb5-16m.h"
//#include "../acquire/command6.h"
#include "../keydef.h"
//#include "../gui/GWColor.h"
//#include "savrec.h"



BYTE HelpTagBuf[10];
BYTE *HelpLineNum[1000];
BYTE *HelpStr;
BYTE *NewHelpStr=(void *)0;
BYTE *OldHelpStr=(void *)0;
WORD HelpDispStartLineNum, HelpMaxLineNum;
WORD HelpX=0, HelpY=0;
BYTE HelpFontW, HelpFontH;
BYTE HelpTagC=-1,HelpTagB=-1,HelpTagF=-1;
BYTE DoubleByteFlag;
GUI_FLASH GUI_FONT *OldFont;

BYTE *BatteryStr;
BYTE *OldBatteryStr=(void *)0;
WORD BatteryStartLineNum, BatteryMaxLineNum;
BYTE *BatteryLineNum[50];
WORD BatteryX=0, BatteryY=0;
BYTE BatteryTagC=-1,BatteryTagB=-1,BatteryTagF=-1;

/*************************************************************************************/
/*	External Variables																	  */
/*																					  */
/*************************************************************************************/

//extern UWORD InformationFlag, ProgramInformationFlag;  // is not need....??

extern BYTE *HelpMenuStr[MAXMENU+5/*+HELP_MAX_OFFSET*/][MAX_LANGUAGE];

/* Font Define */
extern GW_ColorDefine ColorDef;   /*Defined in GWColor.h*/
extern GUI_FLASH const GUI_FONT GUI_Font13HB_1;
extern GUI_FLASH const GUI_FONT GUI_Font13H_1;
extern GUI_FLASH const GUI_FONT GUI_Font15CP1251;
extern GUI_FLASH const GUI_FONT GUI_F16BIG5;
extern GUI_FLASH const GUI_FONT GUI_F16GBK;
//extern GUI_FLASH const GUI_FONT GUI_F16KSC;
extern GUI_FLASH const GUI_FONT GUI_F13KSC;
extern GUI_FLASH const GUI_FONT GUI_F14POLISH;
extern GUI_FLASH const GUI_FONT GUI_F14SJIS;


void HelpBrowser(BYTE ,BYTE *);
BYTE SetHelpTag(void);
BYTE ShowHelp(void);
void HelpFunction(void);
void SearchHelpLineInformation(BYTE *);

/********************************************************************************************/
/* If you want to use this HELP function, please check & modify below parameter. 							*/

//#define ShowMaxLine 12					/* 設定畫面最大行數 */
#define ShowMaxLine 9					/* 設定畫面最大行數 */
#define posYMax 		186				/* 設定每次顯示的行數,當 Y 的位置大於設定值則顯示完畢 */
#define HELP_X0 		5//5+22			/* 設定Help X 啟始位置*/
#define HELP_Y0 		40				/* 設定Help Y  啟始位置*/
#define WaveLineX1 	2//+22				/* 設定外框 X1 位置*/
#define WaveLineX2 	318//277+22			/* 設定外框 X2 位置*/
#define WaveLineY1 	37					/* 設定外框 Y1 位置*/
#define WaveLineY2 	203					/* 設定外框 Y2 位置*/

extern UWORD HelpRedrawFlag;			/* Bit0 = Help Function On/Off, Bit1 = Help Display need to Change */
extern UWORD DataRedrawFlag;
/********************************************************************************************/

void HelpBrowser(BYTE line, BYTE *str)
{
	WORD offset, i;
	
	if(str==(void *)0)
   		return;     /*Nothing to do.*/
	else if(str==OldHelpStr)
	{
    	if(line==0)
        	return; /*The same HELP topic.*/
	}
	else if(str!=OldHelpStr)
	{
    	HelpDispStartLineNum=0; /*Change to new HELP topic.*/
    	SearchHelpLineInformation(str);
	}

	OldHelpStr=str;
    
	if((HelpDispStartLineNum==0)&&(line<0))
    	return;/*End of message.*/
	else if((HelpDispStartLineNum==(HelpMaxLineNum-ShowMaxLine /*-15*/))&&(line>0))
    	return;/*End of message.*/
	else if(((HelpMaxLineNum-ShowMaxLine)<0)&&(line>0))
    	return;/*End of message.*/

	GUI_SetLBorder(HELP_X0);				// Setting left start address when be change line

	GUI_SetBkColor(GW_BLACK);
	GUI_SetColor(ColorDef.MsgText);

	//ClearDataBG(GW_BLACK);
	//ClearChanBG(GW_BLACK);
	ClearP3KChanAllBG(GW_BLACK);
	ClearP3KDataAllBG(GW_BLACK);

//	ClearHelpBG(GW_BLACK);

   	// Draw Wave Fomr Area Line
   	for(i=WaveLineX1;i<=WaveLineX2;i++)
	{
   		GUI_DrawPixel(i,WaveLineY1);		// X Line 
		GUI_DrawPixel(i,WaveLineY2);
   	}
	
   	for(i=WaveLineY1;i<WaveLineY2;i++)
	{
   		GUI_DrawPixel(WaveLineX1,i);		// Y Line
		GUI_DrawPixel(WaveLineX2,i);
   	}

	HelpDispStartLineNum+=line;
	HelpX=0;
	HelpY=0;
	offset=HelpMaxLineNum-ShowMaxLine; //-15;

	if(HelpDispStartLineNum<=0)
    	HelpDispStartLineNum=0;

	if(offset>0)
	{
    	if(HelpDispStartLineNum>offset)
        	HelpDispStartLineNum=offset;
    	HelpStr=(BYTE *)HelpLineNum[HelpDispStartLineNum];  /*Point to the variable knob selected line.*/
	}
	else
    	HelpStr=(BYTE *)HelpLineNum[0]; /*Point to the first line of HELP message.*/

	GUI_GotoXY(HELP_X0+HelpX, HELP_Y0+HelpY);
	while(1)
	{
    	if(SetHelpTag()==-1)
		{
//         		HintDelay("HELP parsing error!!");
//			printf("HELP parsing error! !");			// take off HintDelay Function
        	HelpTagC=-1;  /*Reset TAG.*/
        	HelpTagB=-1;
       	 	HelpTagF=-1;
        	break;
    	}
    	if(ShowHelp()==-1)
		{
    		HelpTagC=-1;  /*Reset TAG.*/
    		HelpTagB=-1;
    		HelpTagF=-1;
    		break;
    	}
	}
	//GUI_SetFont(&GUI_GWFont6x8);
	GUI_SetFont(Parameter_Font);
	GUI_SetLBorder(0);
}

/*Get tag from string. If we got '>', then make something change. And then change to ShowHelp(). */
BYTE SetHelpTag(void)
{
	BYTE token=0,ch;
	BYTE i,j=0;
	while(1)
	{
        for(i=0;i<10;i++)
		{
    		ch=*(HelpStr++);
    		if(ch=='<')
			{
        		if(*HelpStr=='<')
				{
        			HelpStr--; /*Got "<<" means '<' character.*/
        			return(0);
        		}
        		else
            		token=1;
    		}
    		else if(ch=='>')
			{
        		if(j>0)
				{
        			token=2;
        			break;  /*Get one tag.*/
        		}
        		else
            		return(-1);/*Parsing error.*/
    		}
    		else if(ch==0x00)
			{
        		HelpStr--; /*Roll back. Change to ShowHelp().*/
        		return(0);
    		}
    		else
			{
        		if(token==1)
            		HelpTagBuf[j++]=ch;
        		else
				{
        			HelpStr--; /*Roll back. Change to ShowHelp().*/
        			return(0);
        		}
    		}
		}
		
		token=0;
		j=0;
		if(i>=10)
			return(-1);/*Parsing error.*/
		switch(HelpTagBuf[0])
		{
			case 'C':   /*Change color.*/
				if(HelpTagC!=HelpTagBuf[1])
				{
					if(HelpTagBuf[1]=='0')				/*WHITE*/
						GUI_SetColor(ColorDef.MsgText);
					else if(HelpTagBuf[1]=='1')			/*YELLOW*/
						GUI_SetColor(ColorDef.Chan1);
					else if(HelpTagBuf[1]=='2')			/*ORANGE*/
						GUI_SetColor(MEM_ORANGE_ku);
					else if(HelpTagBuf[1]=='3')			/*LIGHT_RED*/
						GUI_SetColor(ColorDef.Math);
					else if(HelpTagBuf[1]=='4')			
						GUI_SetColor(MEM_DARKGREEN_ku);
					else
						GUI_SetColor(MEM_DARKBLUE_ku);
					HelpTagC=HelpTagBuf[1];
				}
				break;
			case 'B':   /*Change background color.*/
				if(HelpTagB!=HelpTagBuf[1])
				{
					if(HelpTagBuf[1]=='0')
						GUI_SetBkColor(ColorDef.BackGnd);
					else
						GUI_SetBkColor(ColorDef.MsgText);
					HelpTagB=HelpTagBuf[1];
				}
				break;
			case 'F':   /*Change text font.(0:normal 1:bold)*/
				if(HelpTagF!=HelpTagBuf[1])
				{
					DoubleByteFlag=0;
					if(HelpTagBuf[1]=='0')
					{
						//GUI_SetFont(&GUI_Font13H_1);
						GUI_SetFont(Upper_Font);
					}
					else if(HelpTagBuf[1]=='2')
					{
						GUI_SetFont(&GUI_Font15CP1251);/*RUSSION FONT*/
					}
					else if(HelpTagBuf[1]=='3')
					{
						DoubleByteFlag=1; /*Set double byte font.*/
						//(const GUI_FONT *)OldFont=&GUI_F16BIG5;
						OldFont=(GUI_FONT *)&GUI_F16BIG5;
						GUI_SetFont(&GUI_F16BIG5);/*Traditional CHINESE FONT*/
					}
					else if(HelpTagBuf[1]=='4')
					{
						DoubleByteFlag=1; /*Set double byte font.*/
						//(const GUI_FONT *)OldFont=&GUI_F16GBK;
						OldFont=(GUI_FONT *)&GUI_F16GBK;
						GUI_SetFont(&GUI_F16GBK);/*Simplified CHINESE FONT*/
					}
					else if(HelpTagBuf[1]=='5')
					{
						DoubleByteFlag=1; /*Set double byte font.*/
						//(const GUI_FONT *)OldFont=&GUI_F13KSC;
						OldFont=(GUI_FONT *)&GUI_F13KSC;
						GUI_SetFont(&GUI_F13KSC);/*KOREAN FONT*/
					}
					else if(HelpTagBuf[1]=='6')
						GUI_SetFont(&GUI_F14POLISH);/*POLISH FONT*/
					else if(HelpTagBuf[1]=='7')
					{
						DoubleByteFlag=1; /*Set double byte font.*/
						GUI_SetFont(&GUI_F14SJIS);/*JAPAN FONT*/
					}
				   	HelpTagF=HelpTagBuf[1];
				}
				break;
			default:
				break;
		}
	}
}
////////////////////////////////////////////////////////////////////
/*This function trait "<<" as a character '<'.*/
BYTE ShowHelp(void)
{
	UBYTE ch;
	UWORD double_ch;
	WORD pos_y;
	while(1)
	{
    	ch=*(HelpStr++);
    	if(ch=='<')
		{
    		if(*(HelpStr++)!='<')
			{
        		HelpStr-=2;/*Got a Tag, roll back.  Change to SetHelpTag().*/
        		return(0);
    		}
    	}
    	else if(ch==0x00)
        	return(-1);

    	pos_y=GUI_GetDispPosY();

		if(pos_y>posYMax/*196*/)	
        	return(-1);

    	if((DoubleByteFlag==1)&&(ch>0x80)) /*Check for double byte character.*/
		{ 
        	double_ch=((UWORD)ch)<<8;
        	double_ch+=(UBYTE)*(HelpStr++);
        	GUI_DispChar(double_ch);
    	}
    	else
        	GUI_DispChar(ch);
  	}
}

extern OS_EVENT*LcdUnlockSemPtr;
void SearchHelpLineInformation(BYTE *str)
{
	WORD line;
	OldHelpStr=str;
	
	if((*str!='<')&&(*(str+1)!='M')&&(*(str+5)!='>')) /*Check total line number tag <Mxxx>*/
	{ 
		//HintDelay("HELP parsing error!!");
		printf("HELP parsing error! !");
	    return;
	}
	else
    	line=(*(str+2)-0x30)*100+(*(str+3)-0x30)*10+*(str+4)-0x30;		/* Cal total line of Help message */

	if(line>=999)
    	line=999;
	
	HelpMaxLineNum = line; /*Record the maximum line number of current help topic.*/
	line=0;
	str+=6;
	
	while(*str!=0x00)
	{
    	if(*(str++)=='<')
		{
    		if(*(str++)=='L')
			{
         		if(*(str++)=='>')
				{
             		HelpLineNum[line++]=str;
             		if(line>999)
					{
						//HintDelay("HELP parsing error!!");
						printf("HELP parsing error! !"); 		/* take off HinDelay function */
                        break;
             		}
         		}
         		else
				{
					//HintDelay("HELP parsing error!!");
					printf("HELP parsing error! !");			/* take off HinDelay function */
                    break;
         		}
    		}
    		else
        		str--;	/* if word is not " L " */
    	}
	}
	HelpLineNum[line]=(void *)0;
}

void HelpFunction(void)
{
	UBYTE err;
	WORD i;
	P3k_Disp_Str *Disp_tmp = &P3k_Disp_Data;
	Serial_Number_Str	*Serial = &P3k_Serial_Number;

	if(!(HelpRedrawFlag & HELP_FUN_ON))
	{
		HelpX = 1;
		HelpY = 1;
		HelpDispStartLineNum = 0;
		DoubleByteFlag = 0;			
		NewHelpStr = (BYTE*)HelpMenuStr[M_num][Serial->Version];
		OldHelpStr = (void*)0;
	}
}

