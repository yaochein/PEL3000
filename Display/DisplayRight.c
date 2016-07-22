
#include <app.h>
#include "../menu/head.h"
#include "../FPGA/SendTXSub.h"
#include "keydef.h"

extern void ShowSpace(char no, int x, int y);
extern char GetNowRange(void);

#define Chan_Message_interval				23
#define Chan_Message_01_Y_Address			25
#define Chan_Message_02_Y_Address			Chan_Message_01_Y_Address+Chan_Message_interval
#define Chan_Message_03_Y_Address			Chan_Message_02_Y_Address+Chan_Message_interval
#define Chan_Message_04_Y_Address			Chan_Message_03_Y_Address+Chan_Message_interval
#define Chan_Message_05_Y_Address			Chan_Message_04_Y_Address+Chan_Message_interval
#define Chan_Message_06_Y_Address			Chan_Message_05_Y_Address+Chan_Message_interval
#define Chan_Message_07_Y_Address			Chan_Message_06_Y_Address+Chan_Message_interval
#define Chan_Message_08_Y_Address			Chan_Message_07_Y_Address+Chan_Message_interval
#define Chan_Message_09_Y_Address			Chan_Message_08_Y_Address+Chan_Message_interval
#define Chan_Message_10_Y_Address			Chan_Message_09_Y_Address+Chan_Message_interval
#define Chan_Message_11_Y_Address			Chan_Message_10_Y_Address+Chan_Message_interval
#define Chan_Message_12_Y_Address			Chan_Message_11_Y_Address+Chan_Message_interval

void UpdataChanStatus(void) {
	char str[9],RANGE_Status,STADYNA_status,SPEC_Status,CH_CONT,A_B_Value;
	UBYTE V_Range;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	UBYTE disCurrCNT;
	///UBYTE Parallel_Num = Disp_tmp->CONF.Para_Data.Parallel_Number;
	///UBYTE Booster_Num	 = Disp_tmp->CONF.Para_Data.Booster_Number;

	V_Range = Disp_tmp->VRange;

	ChanRedrawFlag &= (~CHAN_STATUS);
	GUI_SetFont(Right_Font);
	GUI_SetBkColor(Right_Bottom_Bolor);
	GUI_SetColor(Right_Font_Down_Bolor);

	CH_CONT=Disp_tmp->CONF.Ext_Setting.Control;
	RANGE_Status = Disp_tmp->IRange;
	SPEC_Status = Disp_tmp->SPEC;

	if(Disp_tmp->CURRMODE == CC_MODE) {

		if(Data_tmp->CONF.CV_Func_En)
			sprintf( str, "CC+CV");
		else
			sprintf( str, "  CC     ");

		STADYNA_status = Disp_tmp->CC.STADYNA;
		A_B_Value = Disp_tmp->CC.ABSELECT;
	} else if(Disp_tmp->CURRMODE == CR_MODE) {
		if(Data_tmp->CONF.CV_Func_En)
			sprintf( str, "CR+CV");
		else
			sprintf( str, "  CR     ");

		STADYNA_status = Disp_tmp->CR.STADYNA;
		A_B_Value = Disp_tmp->CR.ABSELECT;
	} else if(Disp_tmp->CURRMODE == CV_MODE) {
		sprintf( str, "  CV  ");
		STADYNA_status = 0;
		A_B_Value = Disp_tmp->CV.ABSELECT;
	} else if(Disp_tmp->CURRMODE == CP_MODE) {
		if(Data_tmp->CONF.CV_Func_En)
			sprintf( str, "CP+CV");
		else
			sprintf( str, "  CP     ");

		STADYNA_status = Disp_tmp->CP.STADYNA;
		A_B_Value = Disp_tmp->CP.ABSELECT;
	}
	GUI_SetTextAlign(GUI_TA_LEFT);
	if((M_num!=P_CC)&&(M_num!=P_CR)&&(M_num!=P_CV)&&(M_num!=P_CP)) {
		/* Show What is Mode */
		if(Data_tmp->CV.STA[V_Range].VALUE1)
			GUI_DispStringAt( str, 275, Chan_Message_01_Y_Address);
		else
			GUI_DispStringAt( str, 278, Chan_Message_01_Y_Address);
		/* Show Range Hi or Low */
		//if(Parallel_Num)disCurrCNT=Parallel_Num;
		//else if(Booster_Num)disCurrCNT=Booster_Num+4;
		//else 
		disCurrCNT = 0;
		if(Model_Number==MODEL3031E) {
			static const char p1033Curr[9][3][9]= {	"  6A  ",	"   60A  ",	"  70A  ",	// 1
			                                        "  12A  ",	"  120A  ",	" 140A  ", 	// 2
			                                        "  18A  ",	"  180A  ",	" 210A  ",	// 3
			                                        "  24A  ",	"  240A  ",	" 280A  ",	// 4
			                                        "  30A  ",	"  300A  ",	" 350A  ",	//5
			                                        "  36A  ",	"  360A  ",	" 210A  ",	// 3
			                                        "  42A  ",	"  420A  ",	" 350A  ",	// 5
			                                        "  48A  ",	"  480A  ",	" 490A  ",	// 7
			                                        "  54A  ",	"  540A  ",	" 630A  "
			                                      };// 9
			GUI_DispStringAt(p1033Curr[disCurrCNT][RANGE_Status], 275, Chan_Message_02_Y_Address);
		} else {
			static const char p1031Curr[9][3][9]= {	"  1.5A  ",	"  15A  ",	"  35A  ",	// 1
			                                        "   0.7A  ",	"   7A  ",	"  70A  ", 	// 2
			                                        "  1.05A  ",	" 10.5A  ",	" 105A  ",	// 3
			                                        "   1.4A  ",	"  14A  ",	" 140A  ",	// 4
			                                        "  1.75A  ",	" 17.5A  ",	" 175A  ",	//5
			                                        "  1.05A  ",	" 10.5A  ",	" 105A  ",	// 3
			                                        "  1.75A  ",	" 17.5A  ",	" 175A  ",	// 5
			                                        "  2.45A  ",	" 24.5A  ",	" 245A  ",	// 7
			                                        "  3.15A  ",	" 31.5A  ",	" 315A  "
			                                      };// 9
			GUI_DispStringAt(p1031Curr[disCurrCNT][RANGE_Status], 275, Chan_Message_02_Y_Address);
		}
		if(Model_Number==MODEL3031E) {
			if(V_Range)
				GUI_DispStringAt( " 150V ", 275, Chan_Message_03_Y_Address);
			else
				GUI_DispStringAt( "  15V ", 275, Chan_Message_03_Y_Address);
		}else{
			if(V_Range)
				GUI_DispStringAt( " 500V ", 275, Chan_Message_03_Y_Address);
			else
				GUI_DispStringAt( "  50V ", 275, Chan_Message_03_Y_Address);

		}
		/* Show Static or Dyna or Fast or Slow*/
		if(CV_MODE==Disp_tmp->CURRMODE) {
			if(Disp_tmp->CV.RESPONSE==2)
				GUI_DispStringAt( " Fast ", 278, Chan_Message_04_Y_Address);
			else if(Disp_tmp->CV.RESPONSE==1)
				GUI_DispStringAt( "Normal", 275, Chan_Message_04_Y_Address);
			else
				GUI_DispStringAt( " Slow ", 277, Chan_Message_04_Y_Address);
		}else if(CP_MODE==Disp_tmp->CURRMODE) {
			if(Disp_tmp->CP.RESPONSE==2)
				GUI_DispStringAt( " Fast ", 278, Chan_Message_04_Y_Address);
			else if(Disp_tmp->CP.RESPONSE==1)
				GUI_DispStringAt( "Normal", 275, Chan_Message_04_Y_Address);
			else
				GUI_DispStringAt( " Slow ", 277, Chan_Message_04_Y_Address);
		} else {
			/* Show Static or Dyna */
			if(STADYNA_status)
				GUI_DispStringAt( " Dyna ", 276, Chan_Message_04_Y_Address);
			else
				GUI_DispStringAt( " Static ", 275, Chan_Message_04_Y_Address);
		}
	}

	/* Show Spec On or Off */
	if(SPEC_Status)
		GUI_DispStringAt( " SPEC ", 276, Chan_Message_05_Y_Address);
	else
		GUI_DispStringAt( "            ", 276, Chan_Message_05_Y_Address);

	/* Show CH_CONT On or Off */
	if(CH_CONT)
		GUI_DispStringAt( " EXT ", 280, Chan_Message_06_Y_Address);
	else
		GUI_DispStringAt( "            ", 280, Chan_Message_06_Y_Address);

	if(M_num>CP_MODE) {
		GUI_DispStringAt( "          ", 274, Chan_Message_07_Y_Address);
	} else if(Data_tmp->CONF.Knob_Status)
		GUI_DispStringAt( " Cursor ", 271, Chan_Message_07_Y_Address);
	else {
		if(((DispCT==0)||((DispCT==1)&&((STADYNA_status==0)||(((STADYNA_status))&&(Data_tmp->CONF.Dyna_Level==0)))))&&(CH_CONT==0)) {
			if( Data_tmp->Coarse )
				GUI_DispStringAt( " Coarse ", 271, Chan_Message_07_Y_Address);
			else
				GUI_DispStringAt( "   Fine   ", 274, Chan_Message_07_Y_Address);
		} else {
			GUI_DispStringAt( "              ", 274, Chan_Message_07_Y_Address);
		}
	}
	if(STADYNA_status)
		GUI_DispStringAt( "               ", 271, Chan_Message_08_Y_Address);
	else {
		if( A_B_Value)
			GUI_DispStringAt( " B Value ", 271, Chan_Message_08_Y_Address);
		else
			GUI_DispStringAt( " A Value ", 271, Chan_Message_08_Y_Address);
	}
}
void UpdataChanStatus2(void) {
#if Enable_LED_function	
	char str[9];
	UBYTE iRange,vRange,specStatus;
	UBYTE currTemp =P3k_FLed_Disp.currTemp;	
	F_LED_Str	*Disp_tmp = &P3k_FLed_Disp.seq[currTemp];
	UBYTE disCurrCNT = 0;

	vRange = Disp_tmp->range /2;
	iRange = Disp_tmp->range %2;

	ChanRedrawFlag &= (~CHAN_STATUS);
	GUI_SetFont(Right_Font);
	GUI_SetBkColor(Right_Bottom_Bolor);
	GUI_SetColor(Right_Font_Down_Bolor);
	specStatus = 1;//Disp_tmp->SPEC;	
	
	//GUI_DispStringAt( "   LED ", 275, Chan_Message_05_Y_Address);

	if(Model_Number==MODEL3031E) {
		static const char p1033Curr[9][3][9]= {	
			"  6A  ",	"   60A  ",	"  70A  ",	// 1
		    "  12A  ",	"  120A  ",	" 140A  ", 	// 2
		    "  18A  ",	"  180A  ",	" 210A  ",	// 3
		    "  24A  ",	"  240A  ",	" 280A  ",	// 4
		    "  30A  ",	"  300A  ",	" 350A  ",	//5
		    "  36A  ",	"  360A  ",	" 210A  ",	// 3
		    "  42A  ",	"  420A  ",	" 350A  ",	// 5
		    "  48A  ",	"  480A  ",	" 490A  ",	// 7
		    "  54A  ",	"  540A  ",	" 630A  "
		  };// 9
		GUI_DispStringAt(p1033Curr[disCurrCNT][iRange], 275, Chan_Message_05_Y_Address);
	} else {
		static const char p1031Curr[9][3][9]= {	
			"  1.5A  ",		"  15A  ",	"  35A  ",	// 1
		    "   0.7A  ",	"   7A  ",	"  70A  ", 	// 2
		    "  1.05A  ",	" 10.5A  ",	" 105A  ",	// 3
		    "   1.4A  ",	"  14A  ",	" 140A  ",	// 4
		    "  1.75A  ",	" 17.5A  ",	" 175A  ",	//5
		    "  1.05A  ",	" 10.5A  ",	" 105A  ",	// 3
		    "  1.75A  ",	" 17.5A  ",	" 175A  ",	// 5
		    "  2.45A  ",	" 24.5A  ",	" 245A  ",	// 7
		    "  3.15A  ",	" 31.5A  ",	" 315A  "
		  };// 9
		GUI_DispStringAt(p1031Curr[disCurrCNT][iRange], 275, Chan_Message_05_Y_Address);
	}
		
	if(Model_Number==MODEL3031E) {
		if(vRange)	GUI_DispStringAt( " 150V ", 275, Chan_Message_06_Y_Address);
		else		GUI_DispStringAt( "  15V ", 275, Chan_Message_06_Y_Address);
	}else{
		if(vRange)	GUI_DispStringAt( " 500V ", 275, Chan_Message_06_Y_Address);
		else		GUI_DispStringAt( "  50V ", 275, Chan_Message_06_Y_Address);
	}
	
	//if(Disp_tmp->response==2)
	//	GUI_DispStringAt( " Fast ", 278, Chan_Message_07_Y_Address);
	//else if(Disp_tmp->response==1)
	//	GUI_DispStringAt( "Normal", 275, Chan_Message_07_Y_Address);
	//else
	//	GUI_DispStringAt( " Slow ", 277, Chan_Message_07_Y_Address);
	sprintf(str,"%d",Disp_tmp->response);
	GUI_SetTextAlign(GUI_TA_RIGHT);
	GUI_DispStringAt( str, 300, Chan_Message_07_Y_Address);

	GUI_SetTextAlign(GUI_TA_LEFT);
	GUI_DispStringAt( "%", 300, Chan_Message_07_Y_Address);

	if(specStatus)
		GUI_DispStringAt( " SPEC ", 276, Chan_Message_08_Y_Address);
	else
		GUI_DispStringAt( "            ", 276, Chan_Message_08_Y_Address);	
#endif
}


void DispRightProcess(void) {
	if((ChanRedrawFlag&(BG_CLEAR+CHAN_STATUS))==0)	return;
	if( ChanRedrawFlag & BG_CLEAR ) {
		ChanRedrawFlag &= (~BG_CLEAR);
		ChanRedrawFlag |= CHAN_STATUS;

		switch(M_num){
			case P_CC ... P_CP:	
			case P_FUNC_FLED_EDIT:
			case P_FUNC_FLED_EXECUTE:
			//case P_FUNC_CLED_EDIT:
			case P_FUNC_CLED_EXECUTE:	
				ClearP3KChanSomeBG(Right_Bottom_Bolor);
				break;
			case P_CC_SPEC ... P_CONF_Ext:
			case P_FILE_CHAN:
				ClearP3KChanAllBG(Right_Bottom_Bolor);
				break;
			default:
				ClearP3KChanAllBG(Parameter_Bottom_Bolor);
		}
		DMA_Update_Flag = 1;
	}
	if(ChanRedrawFlag&CHAN_STATUS){
		ChanRedrawFlag &= (~CHAN_STATUS);
		switch(M_num){
			case P_CC ... P_CONF_Ext:
			case P_FILE_CHAN:
				UpdataChanStatus();
				break;
			case P_FUNC_FLED_EDIT:
			case P_FUNC_FLED_EXECUTE:
			//case P_FUNC_CLED_EDIT:
			case P_FUNC_CLED_EXECUTE:
				UpdataChanStatus2();
				break;
			default:
				break;
		}		
		DMA_Update_Flag = 1;
	}
}



