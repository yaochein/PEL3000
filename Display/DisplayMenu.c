#include <app.h>
#include "../menu/head.h"
#include "../menu/menu_msg.h"
#include "../FPGA/SendTXSub.h"
#include "keydef.h"

typedef struct
{
    UBYTE scripnumber;
    UBYTE functionname[19];
    UBYTE scriptcode[508];
}Script_info;

extern Script_info Script[5]; 
extern MENU _menu[MAXMENU];

extern void FloatWindowsDispOn(void);
extern void Float_Windows_Setting(int x1, int y1,int x2, int y2,GUI_COLOR color);
extern void FloatWindows_StringAt(const char GUI_FAR *s, int x, int y);

void DrawMenuFrame(BYTE item, BYTE type)
{
	int i,y,x;

    x= item*64;
	switch(type)
	{
       	case 0: 
			break;
       	case 0x01:								/* Draw frame + separator */
			GUI_SetColor(MEM_BLACK);
			for(i=x+7;i<x+58;i++)				
				GUI_DrawPixel(i,222);				
			GUI_SetColor(GW_WHITE); 	
			for(i=x+7;i<x+58;i++)
				GUI_DrawPixel(i,223);
			break;
		case 0x02:								/* Draw frame */
			break;
		case 0x03:								
			GUI_SetColor(MEM_BLACK);
			GUI_DrawPixel(x-31,235);
			GUI_DrawPixel(x-31,236);
			GUI_DrawPixel(x-32,236);
			GUI_DrawPixel(x-32,237);
			GUI_DrawPixel(x-33,238);
			GUI_SetColor(GW_WHITE);
			GUI_DrawPixel(x-31,238);
			GUI_DrawPixel(x-30,236);
			GUI_DrawPixel(x-30,237);
			GUI_DrawPixel(x-29,238);
			break;
		case 0x04:								/* Pre Menu */
			GUI_SetColor(MEM_BLACK);
			GUI_DrawPixel(x-31,209);
			GUI_DrawPixel(x-31,208);
			GUI_DrawPixel(x-30,208);
			GUI_DrawPixel(x-30,207);
			GUI_DrawPixel(x-29,206);
			GUI_SetColor(GW_WHITE);
			GUI_DrawPixel(x-31,206);
			GUI_DrawPixel(x-32,208);
			GUI_DrawPixel(x-32,207);
			GUI_DrawPixel(x-33,206);
			break;	
		default:
			break;
    }
	
	if(type)
	{
		GUI_SetColor(MEM_BLACK);
		for(i=204;i<240;i++)
			GUI_DrawPixel(x,i);
		GUI_SetColor(GW_WHITE);
		for(i=204;i<240;i++)
			GUI_DrawPixel(x+1,i);

		GUI_SetColor(GW_WHITE);
		for(i=x;i<x+65;i++)
			GUI_DrawPixel(i,204);
	}
	
	if(Soft_Key_Temp)
	{
		/* Clear Previous Setting*/
		for(y=0;y<5;y++)
		{
			x= y*64;
			GUI_SetColor(MEM_BLACK);
			for(i=204;i<240;i++)
				GUI_DrawPixel(x,i);
			GUI_SetColor(GW_WHITE);
			for(i=204;i<240;i++)
				GUI_DrawPixel(x+1,i);

			GUI_SetColor(GW_WHITE);
			for(i=x;i<x+65;i++)
				GUI_DrawPixel(i,204);
		}
		
		/* Using Now Setting*/
		y= Soft_Key_Temp-1;
		x= y*64;
		GUI_SetColor(MEM_BLACK);
		for(i=204;i<240;i++)
			GUI_DrawPixel(x+1,i);

		GUI_SetColor(MEM_BLACK);
		for(i=x;i<x+65;i++)
			GUI_DrawPixel(i,204);		

		y++;
		x= y*64;
		GUI_SetColor(GW_WHITE);
		for(i=204;i<240;i++)
			GUI_DrawPixel(x,i);		
	}		
}

void MenuProcess(BYTE m_no)
{
	WORD 	its_no;//i_no;    /*denote as the item selection number for specified menu*/
	                               /*i_no: define as the subselected item*/
	MENU    tempMenu;        /*point to the specified menu content*/
	MITEMS 	*tempItem;       /*point to the specified item content*/
	MITEM 	*tempITEM;        /*point to the specified item with its internal data*/
	UWORD 	item=1;
	BYTE	typesel;
	BYTE 	POS;
	char 	i,j,str[8];
	int 	item_x_addr[5] = {	32, 96, 160, 224, 288};		/* Item string X location */
	///unsigned char Parallel_Num = 0;
	///unsigned char Booster_Num = 0;
	
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	if((tempMenu=_menu[m_no])==NULL1)
	{
#if Normal_TEST
     	printf("No function");
#endif
    	return;
	}	
	
	if(m_no!=D_M_num)
	{
		D_M_num=m_no;					/*only the valid menu will be updata*/  
		ClearMenuBG(MEM_GRAY);  		/*Draw back ground of menu.*/
	}
	UTILITY.LANGUAGE = 0; //Adam
	
    GUI_SetBkColor(MEM_GRAY);

   	for(its_no=0;its_no<5;its_no++)
	{
		if(MenuRedrawFlag&item)			/* Redraw Menu bar by each issue */
		{
    		GUI_SetColor(MEM_WHITE); 
    		tempItem=&(tempMenu)[its_no];
    		tempITEM=&(tempItem->iptr)[0];

			///Parallel_Num = Disp_tmp->CONF.Para_Data.Parallel_Number;
			///Booster_Num = Disp_tmp->CONF.Para_Data.Booster_Number;

			if( (M_num==P_CC||M_num==P_CR||M_num==P_CV||M_num==P_CP||M_num==P_CAL_MODE)&&((its_no==1)||(its_no==0)))
			{
				if(its_no==1)
				{
					if(Model_Number==MODEL3032E)	
						GUI_DrawBitmap(tempITEM->pbmp[3],tempITEM->x,tempITEM->y);
					else							
						GUI_DrawBitmap(tempITEM->pbmp[0],tempITEM->x,tempITEM->y);
				}
				else
				{
					if(Data_tmp->CONF.CV_Func_En)
						GUI_DrawBitmap(tempITEM->pbmp[4],tempITEM->x,tempITEM->y);
					else
						GUI_DrawBitmap(tempITEM->pbmp[0],tempITEM->x,tempITEM->y);
				}
			}
			else if((M_num==P_CC||M_num==P_CR||M_num==P_CV||M_num==P_CP)&&(its_no==2)){
				if(Model_Number==MODEL3032E)	
						GUI_DrawBitmap(tempITEM->pbmp[3],tempITEM->x,tempITEM->y);
					else							
						GUI_DrawBitmap(tempITEM->pbmp[0],tempITEM->x,tempITEM->y);				
			}else 
				GUI_DrawBitmap(tempITEM->pbmp[(LONG)UTILITY.LANGUAGE],tempITEM->x,tempITEM->y);

			if(tempItem->i_max)
			{
         		if((*tempItem->i_condition)>=tempItem->i_max)   /*Prevent over boundary. Kevin Meng 2003.02.13*/
					*tempItem->i_condition=tempItem->i_max-1;
         		tempITEM=&(tempItem->iptr)[(*tempItem->i_condition)+1];

				if( (M_num==P_CC||M_num==P_CR||M_num==P_CV||M_num==P_CP||M_num==P_CAL_MODE)&&((its_no==1)||(its_no==0)) )
				{				
					if(its_no==1)
					{
						if(Model_Number==MODEL3032E)	
							GUI_DrawBitmap(tempITEM->pbmp[3],tempITEM->x,tempITEM->y);
						else							
							GUI_DrawBitmap(tempITEM->pbmp[0],tempITEM->x,tempITEM->y);
					}
					else
					{
						if(Data_tmp->CONF.CV_Func_En)
							GUI_DrawBitmap(tempITEM->pbmp[4],tempITEM->x,tempITEM->y);
						else
							GUI_DrawBitmap(tempITEM->pbmp[0],tempITEM->x,tempITEM->y);
					}
				}
				else if((M_num==P_CC||M_num==P_CR||M_num==P_CV||M_num==P_CP)&&(its_no==2))
				{
				if(Model_Number==MODEL3032E)	
						GUI_DrawBitmap(tempITEM->pbmp[3],tempITEM->x,tempITEM->y);
					else							
						GUI_DrawBitmap(tempITEM->pbmp[0],tempITEM->x,tempITEM->y);
				}	
				else
					GUI_DrawBitmap(tempITEM->pbmp[(LONG)UTILITY.LANGUAGE],tempITEM->x,tempITEM->y);  //draw title
   	     	}
			
			if(P3K_CALIBRATION_BAR.RANGE==3 && M_num==P_CAL_MODE)
				DrawMenuFrame(its_no,2);
			else
				DrawMenuFrame(its_no,tempItem->frame);
			
			MenuRedrawFlag&=(~item); //Kevin Meng 2005.05.16
		}
		item<<=1;
	}
	
	if(M_num==P_LUA_EXECUTE)
	{
		for(i=0;i<5;i++)
		{
			if(Script[i].functionname[0]!=0)
			{
				GUI_SetFont(&GUI_FontArial15);
				GUI_SetBkColor(GW_GRAY);
				GUI_SetColor(MEM_BLACK);
				strncpy(str,(const char *)&Script[i].functionname,8);	

				for(j=1;j<8;j++)
				{
					if((str[j]>=65)&&(str[j]<=90))
						str[j]+=32;
				}
				GUI_SetTextAlign(GUI_TA_CENTER);
				GUI_DispStringAt(str, item_x_addr[i], 216);	
			}
		}
	}
}
extern void Wait_For_MDMA_Ready(void);
void Menu_Message(char *Message,int x,int y)
	{
	Wait_For_MDMA_Ready();
	Float_Windows_Setting(0,0,319,8,MEM_WHITE);
	GUI_SetFont(Parameter_Font);
	GUI_SetBkColor(MEM_WHITE);
	GUI_SetColor(Message_Font_Bolor);		
	GUI_SetTextAlign(GUI_TA_LEFT);
	FloatWindows_StringAt(Message,x,y);
	//FloatWindowsDispOn();	
	CtrlFlag1 |= Float_Windows_DispOn;
	DMA_Update_Flag = 1;
	}
static char Menu_Message_Buffer_busy;
void Menu_Message_Pro(char Mode,char *Message)
	{
	char i;
	//Mode:0 Write
	//Mode:1 Show
	if(Mode==0)//Mode:0 Write
		{
		Menu_Message_Buffer_busy=1;
		Menu_Message_Data_flag=1;
		i=0;
		while(1)
			{
			if((i>sizeof(Menu_Message_Buffer)-1)||(Message[i]==0))
				{
				Menu_Message_Buffer[i]=0;
				break;
				}
			Menu_Message_Buffer[i]=Message[i];
			i++;
			}
		Menu_Message_Buffer_busy=0;
		}
	else if(Mode==1)//Mode:0 Show
		{
		while(Menu_Message_Buffer_busy)
			OSTimeDly(1);
		Menu_Message_Data_flag=0;
		CtrlFlag1 |= Disp_Middle_Message;
		Menu_Message(Menu_Message_Buffer,10,210);
		}	
	}
void DispMenuProcess(void)
{
	UBYTE err;

	if(Menu_Message_Data_flag)
		Menu_Message_Pro(1,Menu_Message_Buffer);

	if(MenuRedrawFlag&MENU_CHANGE_Again)
	{
		MenuRedrawFlag &= (~MENU_CHANGE_Again);
		MenuRedrawFlag |= MENU_CHANGE;
		DMA_Update_Flag = 1;
	}
	else{
		if(RedrawModeLogo){
			SysRedrawFlag |= PROG_UPDATA;
			RedrawModeLogo=0;
			DMA_Update_Flag = 1;
		}
	}
	if(MenuRedrawFlag&MENU_CHANGE)
	{
		OSSemPend(LcdUnlockSemPtr, 0, &err);              /* Wait for LCD resource.*/			
		if(err==OS_NO_ERR)
		{
			MenuProcess(M_num);     /*D_M_num changed in this function.*/
			MenuRedrawFlag&=(~MENU_CHANGE); //Kevin Meng 2005.05.16
			OSSemPost(LcdUnlockSemPtr);                       /*Release LCD resource.*/ 			
		}
		DMA_Update_Flag = 1;
	}
}

