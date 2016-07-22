#include <app.h>
#include "../menu/head.h"
#include "../FPGA/SendTXSub.h"

extern void FloatWindowsDispOn(void);
extern void FloatWindowsDispOff(void);
extern void Float_Windows_Setting(int x1, int y1,int x2, int y2,GUI_COLOR color);
extern void FloatWindows_StringAt(const char GUI_FAR *s, int x, int y);
extern void Cursor1DisplayOn(void);
extern void Cursor1DisplayOff(void);
extern void Cursor2DisplayOn(void);
extern void Cursor2DisplayOff(void);
extern void Wait_For_MDMA_Ready(void);

void ShowScrollBall(int x, int y)
	{
	UBYTE i,j;
	GUI_DrawPixel(x,y);
	}
void LCD_Blink(void)
	{	
	if((Blink_State&0x01)==0)
		{
		if((Blink_State&0x02)==0)
			{
			FloatWindowsDispOff();
			Cursor1DisplayOn();
			Cursor2DisplayOn();
			Blink_State|=0x02;
			}
		return;
		}

	if(Blink_State&0x04)	Blink_State &= ~(0x04);
	else				return;

	if(Blink_State&0x02)
		{
		Wait_For_MDMA_Ready();
		Cursor1DisplayOff();
		Cursor2DisplayOff();
		Float_Windows_Setting(0,0,319,0x3b,MEM_WHITE);
		GUI_SetFont(Parameter_Font);
		GUI_SetBkColor(MEM_WHITE);
		GUI_SetColor(Message_Font_Bolor);		
		GUI_SetTextAlign(GUI_TA_LEFT);
		FloatWindows_StringAt(" I am Here ! ",100,100);
		//FloatWindowsDispOn();
		CtrlFlag1 |= Float_Windows_DispOn;
		Blink_State&=~(0x02);
		DMA_Update_Flag = 1;
		}
	else
		{
		FloatWindowsDispOff();
		Cursor1DisplayOn();
		Cursor2DisplayOn();
		Blink_State|=0x02;
		DMA_Update_Flag = 1;
		}		
	}

