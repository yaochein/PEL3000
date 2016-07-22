#include <app.h>
#include "../bmp/bmp.h"
#include "keydef.h"

//#include "fs_api.h" //test uCFS
//#include "../fs240/system/fs_x/fs_os.h"
//#include "../fs240/fs/device/usb/usb.h"

UBYTE KeySelTable[2][39]={//[XY][46key]

	    {63,78,93,108,123,138,153,168,183,198,213,228,243,
	    	 63,78,93,108,123,138,153,168,183,198,213,228,243,
	    	   63,78,93,108,123,138,153,168,183,198,213,228,243},
	    	      
	    	
	    {139,139,139,139,139,139,139,139,139,139,139,139,139,
	    	156,156,156,156,156,156,156,156,156,156,156,156,156,
	    	   173,173,173,173,173,173,173,173,173,173,173,173,173},
	    	   	
				     		 };

#if 0
UBYTE KeyCursorPosTable[17]={
			123,126,129,132,135,138,141,144,
			147,150,153,156,159,162,165,168,171	     
				};
#endif

UBYTE KeyCursorPosTable[17]={
			147,150,153,156,161,163,167,170,
			174,178,182,186,190,194,198,202,206	     
				};


UBYTE KeypadTable[39]={
		  0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,
		  0x4E,0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,	   
		  0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x30,0x20,0x5F,0x2D	};



const UBYTE KeyinTmp_NFOL[8]="NEW_FOL";
UBYTE KeyPos;//key cursor position
UBYTE KeypadSTR[13];//keyin string tmp
UBYTE KeypadSTRPtr;//keyin cursor//0-11
UBYTE KeyCursorPos;//0-15
UBYTE KeyCursorTwinkleCnt;//
UBYTE KeypadSubSTR[5];


/* Key Pad BMP File */
GUI_BITMAP *Keypad=(GUI_BITMAP*)&bmKeypad;
GUI_BITMAP *KeySelPtr=(GUI_BITMAP*)&bmKeySelPtr;//black retangular
GUI_BITMAP *KeySelPtrEras0=(GUI_BITMAP*)&bmKeySelPtrEras0;//
GUI_BITMAP *KeySelPtrEras1=(GUI_BITMAP*)&bmKeySelPtrEras1;//
GUI_BITMAP *KeyCursor0=(GUI_BITMAP*)&bmKeyCursor0;
GUI_BITMAP *KeyCursor1=(GUI_BITMAP*)&bmKeyCursor1;
GUI_BITMAP *KeyPush=(GUI_BITMAP*)&bmKeyPush;


void BackSpaceFunc(void);
void ShowKeyPadString(char* STR);
void KeypadUpdate(void);
void ShowString(char* STR,int x,int y,int pos);
void KeySelFunc(BYTE cnt);
void DrawKeySelPtr(void);
void ClrKeySelPtr(void);
void EnterChrFunc(void);
void KeyPadProc(void);


void KeyPadProc(void)
	{
	BYTE str[30];
	if(KeypadRedrawFlag & KEYPAD_UPDATA)
		{		
		KeypadRedrawFlag&=(~KEYPAD_UPDATA);
		KeypadUpdate();
		}
    if(KeypadRedrawFlag&KEYPAD_STR_UPDATA)//Update String
    	{
        KeypadRedrawFlag&=(~KEYPAD_STR_UPDATA);
        //sprintf((char *)str,"%s%s",KeypadSTR,KeypadSubSTR);
		sprintf((char *)str,"%s",KeypadSTR);
		ShowKeyPadString((char *)str);
		KeypadSTRPtr=strlen((char *)KeypadSTR);
		if(KeypadSubSTR[0]=='.')
		//if(KeypadSubSTR[0])		/*when KeypadSubSTR[0]='.'*/
			KeyCursorPos=KeypadSTRPtr;
		else
			KeyCursorPos=KeypadSTRPtr+6;
		//GL_DrawBitmap(KeyCursor1,KeyCursorPosTable[KeyCursorPos+1],99);
        OSTimeDly(4);
        ClrKeySelPtr();
        DrawKeySelPtr();
    	}
#if 0
	//Key Cursor-----
	if(KeyCursorTwinkleCnt==0)
		//GL_DrawBitmap(KeyCursor1,KeyCursorPosTable[KeyCursorPos],80);
		GL_DrawBitmap(KeyCursor1,KeyCursorPosTable[KeyCursorPos+1],99);
	else if(KeyCursorTwinkleCnt==13)
		//GL_DrawBitmap(KeyCursor0,KeyCursorPosTable[KeyCursorPos],80);
		GL_DrawBitmap(KeyCursor0,KeyCursorPosTable[KeyCursorPos+1],99);
	if(KeyCursorTwinkleCnt<24)
		KeyCursorTwinkleCnt++;
	else
		KeyCursorTwinkleCnt=0;
#endif
	//--------------
	DMA_Update_Flag = 1;
	}



void ShowKeyPadString(char* STR)
	{
	GUI_SetFont(Upper_Font); 
	GUI_SetColor(GW_BLACKV);
	GUI_SetBkColor(GW_WHITE);        
	/*Clear 27 chars*/
	GUI_SetTextAlign(GUI_TA_LEFT);
	GUI_GotoXY(73,97);
	//GUI_DispChars(' ',41);//For Clear String
	GUI_DispChars(' ',50);//For Clear String
	/*Clear channel mark area.*/        
	GUI_SetBkColor(GW_WHITE);
	GUI_SetTextAlign(GUI_TA_CENTER);        
	GUI_GotoXY(161,97);
	GUI_DispChar(' ');//For Clear String
	GUI_DispStringAt(STR,162,97);
	}

void KeypadUpdate(void)
	{
	UBYTE i;
//    if(AcqSuspendFlag==CMD_OFF) /*Modified by Kevin Meng  2003.03.07*/
//        OSTimeDly(2);
	GL_DrawBitmap(Keypad,61,67);
//	GL_DrawBitmap(Keypad, 42, 50);
    
	DrawKeySelPtr();
	GUI_SetFont(Upper_Font); 
	KeypadRedrawFlag|=KEYPAD_STR_UPDATA;//Update String
	if(KeypadRedrawFlag&KEYPAD_NEW_FOLDER)
		{
		KeypadRedrawFlag&=~KEYPAD_NEW_FOLDER;
		ShowString("New Folder:",73,76,GUI_TA_LEFT);
		KeypadSTRPtr=7;
		KeyCursorPos=13;
		for(i=0 ; i<8 ; i++)	
			KeypadSTR[i] = KeyinTmp_NFOL[i];
		for(i=8 ; i<13 ; i++)	
			KeypadSTR[i] = 0x00;
		for(i=0 ; i<4 ; i++)	
			KeypadSubSTR[i] = 0x00;
		}
	else
		ShowString("Rename:",73,76,GUI_TA_LEFT);
	}
void ShowString(char* STR,int x,int y,int pos)
	{
	GUI_SetColor(GW_BLACKV);
	GUI_SetBkColor(GW_WHITE);        
	/*Clear 27 chars*/
	GUI_SetTextAlign(pos);
	GUI_GotoXY(x,y);
	GUI_DispChars(' ',18);//For Clear String
	/*Clear channel mark area.*/        
	GUI_SetBkColor(GW_WHITE);
	GUI_SetTextAlign(pos);        
	GUI_GotoXY(x,y);
	GUI_DispChar(' ');//For Clear String
	GUI_DispStringAt(STR,x+1,y);
	}
void KeySelFunc(BYTE cnt)
	{
	BYTE KeyPosTmp;
	ClrKeySelPtr();
	KeyPosTmp = ((BYTE)KeyPos+cnt);
	if(KeyPosTmp<0)			KeyPos = 38;
	else if(KeyPosTmp>38)	KeyPos = 0;
	else					KeyPos = KeyPosTmp;
	DrawKeySelPtr();
	}

void DrawKeySelPtr(void)
	{
	UBYTE x,y;
	x = KeySelTable[0][KeyPos];
	y = KeySelTable[1][KeyPos];
	GL_DrawBitmap(KeySelPtr,x,y);
	//GL_InvertRect(x,y,x+10,y+10);
	}
void ClrKeySelPtr(void)
{
UBYTE x,y;
	x=KeySelTable[0][KeyPos];
	y=KeySelTable[1][KeyPos];
	GL_DrawBitmap(KeySelPtrEras0,x,y);
	GL_DrawBitmap(KeySelPtrEras0,x,y+14);
	GL_DrawBitmap(KeySelPtrEras1,x,y+2);
	GL_DrawBitmap(KeySelPtrEras1,x+14,y+2);
}

void EnterChrFunc(void)
	{
	UBYTE x;
	MenuRedrawFlag|= MENU_CHANGE;
	if(K_M_num==P_UTIL_FILE)	x = 8;
	else					x = 12;

	//first char could not be ' '
	//if((KeypadSTRPtr==0)&&(KeypadTable[KeyPos]==' '))

	//  ' '  (space)  not support
	if( (K_M_num==P_UTIL_FILE)&&(KeypadTable[KeyPos]==' ') )
		return;

	if(KeypadSTRPtr<x)
		{
		ClrKeySelPtr();
		GL_DrawBitmap(KeyPush,KeySelTable[0][KeyPos],KeySelTable[1][KeyPos]);
		KeypadSTR[KeypadSTRPtr]	= KeypadTable[KeyPos];
		KeypadSTRPtr++;
		GL_DrawBitmap(KeyCursor0,KeyCursorPosTable[KeyCursorPos+1],99);
		KeyCursorPos++;
		KeyCursorTwinkleCnt=0;//Keep cursor no twinkle
		KeypadRedrawFlag|= KEYPAD_STR_UPDATA;	
		}
	}

void BackSpaceFunc(void)
	{
	MenuRedrawFlag|= MENU_CHANGE;
	if(KeypadSTRPtr>0)
		{
		KeypadSTRPtr--;
		GL_DrawBitmap(KeyCursor0,KeyCursorPosTable[KeyCursorPos+1],99);
		KeyCursorPos--;
		KeypadSTR[KeypadSTRPtr]	= 0x00;
		KeyCursorTwinkleCnt=0;//Keep cursor no twinkle
		KeypadRedrawFlag|= KEYPAD_STR_UPDATA;	
		 }
	}

