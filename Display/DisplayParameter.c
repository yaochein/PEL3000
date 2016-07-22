#include <app.h>
#include "../menu/head.h"
#include "../FPGA/SendTXSub.h"
#include "keydef.h"
#include "math.h"

void ShowScrollBar_Other(UWORD Scroll_Xpos,UWORD Scroll_Ypos,UBYTE TotalDispItem,UBYTE OnePageDispItem,UBYTE EveryItemInterval,UBYTE ScrollBar_width,UBYTE DispStartPos);
extern long GetChanData(BYTE cnt, BYTE cnt1);
extern char GetNowRange(void);
extern void ClrDispCnt(char mode, char ct, char sec, char ssc, char bct, char scl);
extern void HelpBrowser(BYTE, BYTE *);
extern void Update_Panel(void);
extern void RedrawMeasure(void);
extern char get_chan_prec(BYTE cnt);

extern UBYTE KeyTaskBuf[2];
extern char USB_Status_Display;
extern char FMShowfilePath[maxshowfiledir];//The current path for display in file menu.
extern BYTE inform_cnt;
extern BYTE *NewHelpStr;
extern unsigned char last_menu;

#define Disp_Start_Y2						25	/*PEL-2000 Display Setting(Old)*/

#define Disp_Start_X						5
#define Disp_Interval						25
#define Disp_Start_Y0						72	/*Display Setting Mode*/
#define Disp_Start_Y1						120	/*Display Measure + Setting Mode*/
#define Para_Start_X						200
#define Unit_Start_X						202

#define Conf_Para_Start_X					212
#define Conf_Unit_Start_X					212

#define HiLight_Length						51
#define	Scroll_Bar_Width					7
#define Scroll_Bar_Start_X					260
#define	Disp_Item_Num0						3	/*Display Measure + Setting Mode*/
#define	Disp_Item_Num1						5	/*Display Setting Mode*/

/************************************/
/* \x80 -> Rising Edge	Icon				*/
/* \x7F -> Falling Edge	Icon				*/
/* \x82 -> Ohm Icon					*/
/************************************/
static const char cc_sta[5][20]= {	" CC A Value "," CC B Value "," SlewRate "," +CV "," +CV Response"};
static const char cr_sta[5][20]= {	" CR A Value "," CR B Value "," SlewRate "," +CV "," +CV Response"};
static const char ccr_dyna[8][15]= {" Level1 "," Level2 "," SlewRate \x80 "," SlewRate \x7F "," Timer1 "," Timer2 "," +CV "," +CV Response"};
static const char ccr_dyna_percent[8][15]= {" Set "," Level "," SlewRate \x80 "," SlewRate \x7F "," Timer1 "," Timer2 "," +CV "," +CV_Response"};
static const char ccr_dyna_freq_duty[8][15]= {" Level1 "," Level2 "," SlewRate \x80 "," SlewRate \x7F "," Frequency "," Duty "," +CV "," +CV_Response"};
static const char ccr_dyna_percent_freq_duty[8][15]= {" Set "," Level "," SlewRate \x80 "," SlewRate \x7F "," Frequency "," Duty "," +CV "," +CV_Response"};
static const char cxcv_reponse [2][15]= {"Slow ","Fast "};



static const char cc_sta_unit[5][15]	= {	" A ",		" A ",		"mA/us"," V ","   "};
static const char cc_dyna_unit[8][15]	= {	" A ",		" A ",		"mA/us","mA/us"," ms "," ms "," V ","   "};
static const char cc_dyna_percent_unit[8][15]	= {	" A ", " % ", "mA/us", "mA/us", " ms ", " ms ", " V ","   "};
static const char cc_dyna_freq_duty_unit[8][15]	= {	" A ", " A ", "mA/us", "mA/us", " Hz ", " % ", " V ","   "};
static const char cc_dyna_percent_freq_duty_unit[8][15]	= {	" A ", " % ", "mA/us", "mA/us", " Hz ", " % ", " V ","   "};

static const char cr_sta_unit[5][15]	= {	" \x82    "," \x82    ","mA/us"," V ","   "};
static const char cr_dyna_unit[8][15]	= { " \x82    "," \x82    ","mA/us","mA/us"," ms "," ms "," V ","   "};
static const char cr_dyna_percent_unit[8][15]	= {	" \x82 ", " % ", "mA/us", "mA/us", " ms ", " ms ", " V ","   "};
static const char cr_dyna_freq_duty_unit[8][15]	= {	" \x82 ", " \x82 ", "mA/us", "mA/us", " Hz ", " % ", " V ","   "};
static const char cr_dyna_percent_freq_duty_unit[8][15]	= {	" \x82 ", " % ", "mA/us", "mA/us", " Hz ", " % ", " V ","   "};

static const char cg_sta_unit[5][15]	= {	" mS ",	" mS ",	"mA/us"," V ","   "};//
static const char cg_dyna_unit[8][15]	= { " mS ",	" mS ",	"mA/us","mA/us"," ms "," ms "," V ","   "};//
static const char cg_dyna_percent_unit[8][15]	= {	" mS ", " % ", "mA/us", "mA/us", " ms ", " ms ", " V ","   "};
static const char cg_dyna_freq_duty_unit[8][15]	= {	" mS ", " mS ", "mA/us", "mA/us", " Hz ", " % ", " V ","   "};
static const char cg_dyna_percent_freq_duty_unit[8][15]	= {	" mS ", " % ", "mA/us", "mA/us", " Hz ", " % ", " V ","   "};

static const char cv_sta[2][15] = 	{" CV A Value "," CV B Value "};
static const char cv_unit[2][5] = {" V ",	" V "  };

static const char cp_sta[4][15] = 	{" CP A Value "," CP B Value "," +CV "," +CV_Response" };
static const char cp_unit[4][15] = {	" W "," W "," V ","    "};

static const char cp_dyna[5][15]		= {" Level1 ",	" Level2 ",	" Timer1 ",	" Timer2 ",	" +CV "};
static const char cp_dyna_percent[5][15]= {" Set "," Level "," Timer1 "," Timer2 "," +CV "};
static const char cp_dyna_freq_duty[5][15]= {" Level1 "," Level2 "," Frequency "," Duty "," +CV "};
static const char cp_dyna_percent_freq_duty[5][15]= {" Set "," Level "," Frequency "," Duty "," +CV "};

static const char cp_dyna_unit[5][15]	= {" W ",		" W ",		" ms ",		" ms ",		" V "};
static const char cp_dyna_percent_unit[5][15]	= {	" W", " % ",  " ms ", " ms ", " V "};
static const char cp_dyna_freq_duty_unit[5][15]	= {	" W ", " W ",  " Hz ", " % ", " V "};
static const char cp_dyna_percent_freq_duty_unit[5][15]	= {	" W ", " % ", " Hz ", " % ", " V "};

static const char spec_str[6][15] = { " SPEC Test "," Delay Time "," Entry Mode "," High ", " Low ", " Center " };
static const char Dyna_Level[2][15]	= { " Value " , " Percent "};
static const char Dyna_Time[2][30]	= { " T1/T2 " , "Freq./Duty "};
//static const char Input_Mode[2][15]	= { " OHM " , " MHO "};
static const char Input_Mode[2][15]	= { " \x82 " , " mS "};
static const char spec_unit_val[3][4] = { " V " , " V ", " V " };
static const char spec_unit_pcet[3][4] = { " % ", " % ", " V " };
static const char spec1_unit_val[3][4] = { " A ", " A ", " A " };
static const char spec1_unit_pcet[3][4] = {" % ", " % ", " A "};
#if Enable_Ring_Count
static const char prot_title_str[7][30] = {	" OCP Level ", " OCP Setting ", " OPP Level ", " OPP Setting "," UVP Level "," UVP Ring Time"," OVP Level "};
static const char prot_unit[7][5] = { " A ", "", " W ", "", " V ", " s "," V "};
#else
static const char prot_title_str[6][30] = {	" OCP Level ", " OCP Setting ", " OPP Level ", " OPP Setting "," UVP Level "," OVP Level "};
static const char prot_unit[6][5] = { " A ", "", " W ", "", " V "," V "};
#endif
#if Enable_OPPOCP_off
static const char prot_str[3][20] = {	" Load Off ",	" LIMIT ","   OFF   ",};
#else
static const char prot_str[2][20] = {	" Load Off ",	" LIMIT "};
#endif
//static const char conf_other[P_Conf_Max][25] = {	" Soft Start "," Von Voltage "," Von Latch "," Von Delay "," Response "," Count Time "," CutOff Time "," CR Unit "," Dyna. Level "," Dyna. Time "," Mem. Recall "," Short Key "};
#if Enable_Short_invalidate
static const char conf_other[P_Conf_Max][25] = {	" Soft Start "," Von Voltage "," Von Latch "," Von Delay "," Count Time "," CutOff Time "," CR Unit "," Dyna. Level "," Dyna. Time "," Mem. Recall "," Short Function "," Short Key "," Short Safety "};
#else
static const char conf_other[P_Conf_Max][25] = {	" Soft Start "," Von Voltage "," Von Latch "," Von Delay "," Count Time "," CutOff Time "," CR Unit "," Dyna. Level "," Dyna. Time "," Mem. Recall "," Short Key "};
#endif
//static const char conf_knob[12][25] = {	" Status "," CCH Step "," CCM Step "," CCL Step "," CRH Step "," CRM Step "," CRL Step "," CVH Step "," CVL Step "," CPH Step "," CPM Step "," CPL Step "};
static const char conf_knob[9][25] = {	" Status "," CCH Step "," CCL Step "," CRH Step "," CRL Step "," CVH Step "," CVL Step "," CPH Step "," CPL Step "};

static const char short_key[2][9] = { " Toggle "," Hold "};
static const char level_str[2][7] = { " Low ", " High " };
static const char onoff_str[2][9] = { " OFF ",	"  ON " };
static const char Memory_str[2][16] = { " Safety ",	" Direct " };
static const char Chan_Response[4][15] = { " 1/1 ", " 1/2 ", " 1/5 ", " 1/10 " };
#if Enable_Short_invalidate
static const char conf_other_space[P_Conf_Max] = { 6,7,4,7,4,6,5,7,9,6,6,6,6 };
#else
static const char conf_other_space[P_Conf_Max] = { 6,7,4,7,4,6,5,7,9,6,6 };
#endif
//static const char conf_knob_space[P_Konb_MAX] = { 7,7,7,7,7,7,7,7,7,7,7,7 };
static const char conf_knob_space[P_Konb_MAX] = { 10,7,7,7,7,7,7,7,7};
static const char display_Language[1][15] = { " English " };
static const char item_str[8][20] = { "PROG:", "STEP:", "Memory:", "Run:", "On-Time:", "Off-Time:", "P/F-Time:", "Short-Time:" };
static const char run[3][20] = { "      Skip", "      Auto", " Manual" };
static const int SeqMain_item_x_addr[8] = { 60,175, 10,  10,  10,160,160,160 };			/* Item string X location */
static const int SeqMain_item_y_addr[8] = { 66, 66, 110, 135,160, 110, 135,160 };			/* Item string Y location */
static const int Short_Chan_x_addr[9] = {5, 95, 125, 155,185,215,245,275,305 };		/* Short Chan string X location */
static const int Short_Chan_space_x_addr[9] = {100, 40, 78,116,154,192,230,268,306 };		/* Short Chan string X location */
static const int SeqMain_val_x_addr[8] = { 160, 265, 145, 145, 145, 311, 311, 311 };		/* Value string X location */
static const int hilight_space[8] = { 22,20,29,29,29,32,32,32 };
static const int val_space_x_addr[8] = { 160, 265, 145, 145, 145, 311, 311, 311};
static const char val_space[16] = { 2,2,4,7,4,4,5,4,1,1,1,1,1,1,1,1 };
static const char Interface_title[5][20] = { " Interface ", " Baud Rate ", " Stop Bit ", " Parity ", " Address "};
static const char Interface_Kind[3][20] = { " RS232 ", " GPIB ", " USB " };
static const int Interface_addr_y[5] = {  40, 65, 90, 115, 65};
static const char Interface_space[5] = { 5, 5, 2, 4, 2 };
static const char parity[3][10] = { " None ", " Odd ", " Even " };
static const char baudrate[5][10] = { " 2400 ", " 4800 ", " 9600 ", " 19200 ", " 38400 " };
static const char stopbit[2][4] = { " 1 ", " 2 " };
static const char DateTime_title[5][10] = { " Month ", " Day ", " Year ", " Hour ", " Minute " };
static const char DateTime_space[5] = { 2, 2, 4, 2, 2 };
static const char utility_Other[8][25] = { " Knob Type ", " Speaker ", " Alarm Tone ", " UnReg Tone ", " Go_NoGo Tone ", " Contrast ", " Brightness ", " Language " };
static const char knob_type[2][9] = { " Old "," Updated "};
static const char utility_Other_space[8] = { 7, 3, 3, 3, 3, 2, 2, 7};
#if Enable_AutoLoad
static const char AutoLoad_title[5][20] = { " Auto Load ", " Auto Load On "," Load Off (Mode) "," Load Off (Range) " ," Short (safety) "};
#else
static const char AutoLoad_title[2][20] = { " Auto Load ", " Auto Load On " };
#endif
static const char AutoLoad_mode[4][10]	= { " Load ", " Prog ", " NSeq ", " FSeq " };
#if Enable_AutoLoad
static const char AutoLoad_space[5] = { 3, 4 , 3, 3,3};
#else
static const char AutoLoad_space[2] = { 3, 4 };
#endif


static const char okng[3][8] = { "       ", "NG" ,"GO" };
static const int SeqView_item_x_addr[8] = {	60,	125, 190, 255,  60, 125, 190, 255 };		/* Item string X location */
static const int SeqView_item_y_addr[8] = {	50,	 50,  50,  50, 130, 130, 130, 130 };		/* Item string Y location */
static const int SeqView_val_x_addr[8]  = {  55, 120, 185, 250,  55, 120, 185, 250 };		/* Value string X location */
static const int SeqView_val_y_addr[8]  = {  80,  80,  80,  80, 160, 160, 160, 160 };			/* Value string Y location */
static const char ViewNext_P_F[3][2] = { "P", "F" ," "};
static const char ViewNext_G_N[3][6] = { " ","NG" ,"GO"};
static const int ProgDetail_Item_X_Addr[8] = {	70, 100, 130, 160, 190, 220, 250, 280};		/* Item string X location */
static const int ProgDetail_Item_Y_Addr[4] = {	90, 115, 140, 165};		/* Item string Y location */
static const char CalMode_unit[MODE_Number][3] = {"A","V","V","V","V","V","V","A","A"};
static const char CalMode_title[2][20]= {"High Point","Low Point"};
static const int CalMode_Select_Bar_X_Addr[4]= {5,5,205,205};
static const int CalMode_Select_Bar_Y_Addr[4]= {72,97,72,97};
static const int CalMode_Select_Y_Addr[2]= {72,97};
static const char CalMode_Highlight_Length[4]= {41,41,30,30};
static const char Parallel_item[4][30]= {" Trigger In "," Trigger In Delay"," Trigger Out "," Trigger Out Width "};
static const char Parallel_Mode[2][10]= {" OFF "," ON "};
static const char Sync_space[P_Sync_MAX] = { 4,8,4,8 };

static const char External_item[3][30]= {" Control "," LoadOn IN "," Sync-Mode"};
static const char External_Control[4][10]= {" OFF "," V "," R "," Rinv "};
static const char External_LoadOnIn[3][10]= {" OFF "," High "," Low "};
static const char External_Multi[3][10]= {"    OFF ","  Master ","  Slave "};
static const char knob_status[2][20] = { "Step (coarse/fine)",	"   Cursor        " };
static const char Show_space[10][30] = {	"      ",						/* 2 Char Space */
                                       "        ",						/* 3 Char Space */
                                       "          ",					/* 4 Char Space */
                                       "            ",					/* 5 Char Space */
                                       "              ",				/* 6 Char Space */
                                       "                ",				/* 7 Char Space */
                                       "                  ",			/* 8 Char Space */
                                       "                    ",			/* 9 Char Space */
                                       "                      ", 		/* 10 Char Space */
                                       "                        "
                                       };	/* 11 Char Space */





#if Enable_Optim_display
char only_text= 0;
#define XY_OFF_new(x,y)    ((319-x)*256+y)

void Draw_Bar_25 (UWORD x,UWORD y,UBYTE lenth)
{
	UBYTE tall = 25;
	UWORD wide =5*lenth;
	UBYTE *i;
	UBYTE *p;
	UWORD k,j;
	char color = GUI_Context.aColorIndex[0];
	p = (UBYTE*)(MemAddress+XY_OFF_new(x,y));
	for(k=0; k<wide; k++) {
		i = p;
		j=tall;
		while(j--) {
			*(i++)=color;
		}
		p -= 256;
	}
}

void Draw_Bar_50 (UWORD x,UWORD y,UBYTE lenth,UBYTE dirBar)
{
	UBYTE tall = 25;//26;
	UWORD wide =5*lenth;
	UBYTE *i;
	UBYTE *p;
	UWORD k,j;
	char color1 =0;
	char color2 =0;
	p = (UBYTE*)(MemAddress+XY_OFF_new(x,y));
	if(dirBar)	color1 =0x11;
	else		color2 =0x11;
	if(B_DispCT != DispScrCurrLoc) {
		for(k=0; k<wide; k++) {
			i = p;
			j=tall;
			while(j--) {
				*(i++)=color1;
			}
			j=tall;
			while(j--) {
				*(i++)=color2;
			}
			p -= 256;
		}
	} else {
		for(k=0; k<wide; k++) {
			i = p;
			j=tall;
			while(j--) {
				*(i++)=color1;
			}
			p -= 256;
		}
	}
}

void Draw_Bar_125 (UWORD x,UWORD y,UBYTE lenth,UBYTE dirBar)
{
	UWORD wide =5*lenth;
	UBYTE *i;
	UBYTE *p;
	UWORD k,j;
	char color1 = 0;
	char color2 = 0;
	char t1,t2;
	p = (UBYTE*)(MemAddress+XY_OFF_new(x,y));
	if(dirBar) {
		color1 =0x11;
		t1=25;
		t2=25*(DispScrEndCT - DispScrStartCT);
	} else {
		color2 =0x11;
		t1=25*(DispScrEndCT - DispScrStartCT);
		t2=25;
	}

	for(k=0; k<wide; k++) {
		i = p;
		j=t1;
		while(j--) {
			*(i++)=color1;
		}
		j=t2;
		while(j--) {
			*(i++)=color2;
		}
		p -= 256;
	}
}
void Draw_New_Bar_25 (UWORD x,UWORD y,UBYTE lenth,UBYTE dirBar)
{
	UBYTE tall=25;
	UWORD wide =5*lenth;
	UBYTE *i;
	UBYTE *i2;
	UBYTE *p;
	UBYTE *p2;

	UWORD k,j;
	char color1 =0;
	char color2 =0;
	p = (UBYTE*)(MemAddress+XY_OFF_new(x,y));
	p2 = (UBYTE*)(0x20340000+XY_OFF_new(x,y));
	if(dirBar) {
		color1 =0x11;
	} else {
		color2 =0x11;
	}
	if(B_DispCT != DispScrCurrLoc) {
		for(k=0; k<wide; k++) {
			i = p;
			i2 = p2;
			j=tall;
			while(j--) {
				if(*(i)==color2) { //i2
					*(i2)=color1;
					*(i)=color1;
				}
				i++;
				i2++;
			}
			p -= 256;
			p2 -= 256;
		}
		DMA_Update_Flag = 0;
	}
}

void Draw_New_Bar_50 (UWORD x,UWORD y,UBYTE lenth,UBYTE dirBar)
{
	UBYTE tall=25;
	UWORD wide =5*lenth;
	UBYTE *i;
	UBYTE *i2;
	UBYTE *p;
	UBYTE *p2;

	UWORD k,j;
	char color1 =0;
	char color2 =0;
	p = (UBYTE*)(MemAddress+XY_OFF_new(x,y));
	p2 = (UBYTE*)(0x20340000+XY_OFF_new(x,y));
	if(dirBar) {
		color1 =0x11;
	} else {
		color2 =0x11;
	}
	if(B_DispCT != DispScrCurrLoc) {
		for(k=0; k<wide; k++) {
			i = p;
			i2 = p2;
			j=tall;
			while(j--) {
				if(*(i)==color2) {
					*(i2)=color1;
					*(i)=color1;
				}
				i++;
				i2++;
			}
			j=tall;
			while(j--) {
				if(*(i)==color1) {
					*(i)=color2;
					*(i2)=color2;
				}
				i++;
				i2++;
			}
			p -= 256;
			p2 -= 256;
		}
		DMA_Update_Flag = 0;
	}
}

//type 0 : draw Configure, recoder BarLenth
//type 1~2 draw bar,
//type 2 : draw ScrollBar
#define minus(x,y)	((x>y)? (x-y):(y-x))

void DebugPrintf(char *Message)
{
#if 0
	printf(Message);
#endif
}

UBYTE DrawBar (char type,char i,char j)
{
	static char ScrBarFlag ;
	static char DrBarFlag ;
	static char ScrollBarMax;
	static char Item_Y ;
	static char ScrollBarLenth ;

	if(type==0) {
		DrBarFlag = 0;
		ScrollBarMax = i;
		Item_Y = j;
#if Enable_Optim_display		
		if(only_text==2)	only_text = 0;
		else 			only_text = 1;
#endif		
		if(Item_Y<=72)	ScrollBarLenth = Disp_Item_Num1;
		else			ScrollBarLenth = Disp_Item_Num0;
		if(DataRedrawFlag&BG_CLEAR_FLAG) {
			B_DispStratCT = DispScrStartCT;
			ScrBarFlag=0;
			return 1;
		} else {
			if(DispScrStartCT != B_DispStratCT) {
				B_DispStratCT = DispScrStartCT;
				ScrBarFlag=0;
			} else
				ScrBarFlag=1;
			return 0;
		}
	} else {
		if(((DispScrCurrLoc == DispScrEndCT)||(DispScrCurrLoc == DispScrStartCT))&&(ScrBarFlag!=1)) {
			if(ScrBarFlag==0) {
				if(type==2) {
					DebugPrintf(":1\n");
					ShowScrollBar_Other(Scroll_Bar_Start_X,Item_Y,ScrollBarMax,ScrollBarLenth,Disp_Interval,Scroll_Bar_Width,DispScrStartCT);
				}
				ScrBarFlag=2;
			}
			if(DrBarFlag==0) {
				if( i == DispScrCurrLoc) {
					DebugPrintf(":2\n");
					Draw_Bar_125(Disp_Start_X,Item_Y+j*Disp_Interval,HiLight_Length,1); //bar on start station
				} else {
					Draw_Bar_125(Disp_Start_X,Item_Y+j*Disp_Interval,HiLight_Length,0); //bar on end station
					DebugPrintf(":3\n");
				}
				DrBarFlag = 1;
			}
			return 1;
		} else {
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&((i!=B_DispCT)&&(i!=DispScrCurrLoc)))//no moved.
				return 0;
			if( i == DispScrCurrLoc || i == B_DispCT ) {
				if(DrBarFlag==0) {
					if(DataRedrawFlag&BG_CLEAR_FLAG) {													//normal
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
						Draw_Bar_25(Disp_Start_X,Item_Y+j*Disp_Interval,HiLight_Length); 				//bar on start station (Enter)
						DebugPrintf(":4\n");
					} else {																				//only change color (blue <-> black)
						if((minus(DispScrCurrLoc,B_DispCT))<=1) { //????
							if( i == DispScrCurrLoc) {//change color bule <--> back
								Draw_New_Bar_50(Disp_Start_X,Item_Y+j*Disp_Interval,HiLight_Length,1); //bar on up station
								DebugPrintf(":5\n");
							} else {
								Draw_New_Bar_50(Disp_Start_X,Item_Y+j*Disp_Interval,HiLight_Length,0); //bar on down station
								DebugPrintf(":6\n");
							}
						} else {
							if(i==DispScrCurrLoc) {
								Draw_New_Bar_25(Disp_Start_X,Item_Y+j*Disp_Interval,HiLight_Length,1); //bar on start station
								Draw_New_Bar_25(Disp_Start_X,Item_Y+(j+2)*Disp_Interval,HiLight_Length,0); //bar on up station
								DebugPrintf(":7\n");
							} else {
								Draw_New_Bar_25(Disp_Start_X,Item_Y+j*Disp_Interval,HiLight_Length,0); //bar on start station
								Draw_New_Bar_25(Disp_Start_X,Item_Y+(j+2)*Disp_Interval,HiLight_Length,1); //bar on down station
								DebugPrintf(":8\n");
							}
						}
					}
					DrBarFlag =1;
				}
			}
			if(DataRedrawFlag&BG_CLEAR_FLAG)	return 1; //draw words
			else							return 0; //don't draw words
		}
	}
}
#endif


void Displine(UWORD Start_Point_X,UWORD Start_Point_Y,UWORD Line_Length,GUI_COLOR color)
{
	UWORD i;
	GUI_SetColor(color);
	for(i=0 ; i<Line_Length ; i++)
		GUI_DrawPixel(Start_Point_X+i,Start_Point_Y);
}
void Disp_ext_line(UWORD Start_Point_X,UWORD Start_Point_Y,UWORD Line_Length,GUI_COLOR color)
{
	UWORD i;
	GUI_SetColor(color);
	for(i=0 ; i<Line_Length ; i++)
		GUI_DrawPixel(Start_Point_X,Start_Point_Y+i);
}

extern void Debug_printf(char *Message);

char Display_Parameter_Pro(double Parameter, char *buf, char precision)
{
	if(buf==0) {
		Debug_printf(" Display_Parameter_Pro Buf Error\n");
		return 0;
	}
	*(buf+9)=0;

	if(Parameter<0)
		Parameter=0;
	if(getcursortime)CursorPrecision = precision;
	if(precision==0)
		sprintf( buf, " %1.0f ", Parameter );
	else if(precision==1)
		sprintf( buf, " %1.1f ", Parameter );
	else if(precision==2)
		sprintf( buf, " %1.2f ", Parameter );
	else if(precision==3)
		sprintf( buf, " %1.3f ", Parameter );
	else if(precision==4)
		sprintf( buf, " %1.4f ", Parameter );
	else if(precision==5)
		sprintf( buf, " %1.5f ", Parameter );
	else if(precision==6)
		sprintf( buf, " %1.6f ", Parameter );
	else {
		if(Parameter>=10000)
			sprintf( buf, " %5.1f ", Parameter);
		else if(Parameter>=1000)
			sprintf( buf, " %4.2f ", Parameter);
		else if( Parameter >= 100)
			sprintf( buf, " %3.3f ", Parameter);
		else if(Parameter>=10)
			sprintf( buf, " %2.4f ", Parameter );
		else
			sprintf( buf, " %1.5f ", Parameter );
	}
	if((*(buf+9))!=0) {
		*(buf+8)=' ';
		*(buf+9)=0;
	}
	return 1;
}


char Search_precision(char cnt)
{
	UBYTE V_Range;
	UBYTE I_Range;
	UBYTE Seq_Mode_Temp;
	char precision_Data;

	if( (P_NSeq_Edit==M_num)||(P_Seq_Normal==M_num) ) {
		V_Range = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Range/2;
		I_Range = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Range%2;
		Seq_Mode_Temp = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode;
		if(CC_MODE==Seq_Mode_Temp)
			precision_Data = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
		else if(CR_MODE==Seq_Mode_Temp)
			precision_Data = (ptrMODEL_TYPE->CR)[I_Range*10].precision;
		else if(CV_MODE==Seq_Mode_Temp)
			precision_Data = (ptrMODEL_TYPE->CV)[V_Range*3].precision;
		else
			precision_Data = (ptrMODEL_TYPE->CP)[I_Range*10].precision;	/*CP_MODE*/
	} else if( (P_Seq_Fast==M_num)||(P_FSeq_Edit==M_num)||(P_FSeq_Fill==M_num) ) {
		if(cnt==P_FSeq_TimeBase) {
			if(P3k_FSeq_Disp.FSeq_TB_Range)
				precision_Data = 2;
			else
				precision_Data = 3;
		} else {	/*P_FSeq_Last_Set and P_FSeqEdit_Value*/
			V_Range = P3k_FSeq_Disp.FSeq_Range/2;
			I_Range = P3k_FSeq_Disp.FSeq_Range%2;
			Seq_Mode_Temp = P3k_FSeq_Disp.FSeq_Mode;
			if(CC_MODE==Seq_Mode_Temp)
				precision_Data = (ptrMODEL_TYPE->CC)[I_Range*10].precision;
			else
				precision_Data = (ptrMODEL_TYPE->CR)[I_Range*10].precision;/*CR_MODE*/
		}
	}
	return precision_Data;
}

float Get_Parallel_Parameter(unsigned char IRange)
{
	float Para_parameter;
#if 1
	Para_parameter = 1;
#else
	
	P3k_Parallel_Str *Parallel_Ptr = &P3k_Chan_Data.CONF.Para_Data;
	
	if(IRange_Low == IRange)
		Para_parameter = (Parallel_Ptr->Parallel_Number) + 1;
	else
		Para_parameter = (Parallel_Ptr->Parallel_Number) + (Parallel_Ptr->Booster_Number*2) + 1;
#endif
	return Para_parameter;
}

double StepToReal(long dat, char cnt){
	double resolution,data;
	char cnt1,range;
	short tmax,tmin;
	long CxCV_data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	UBYTE V_Range = Disp_tmp->VRange;
	UBYTE I_Range = Disp_tmp->IRange;
	UBYTE Seq_Mode_Temp;
	switch(M_num){
		case P_CC:
			if(cnt<=CCCR_Dyn_SRDN)
				range = I_Range;
			else if(cnt==CCCR_Dyn_T1)
				range = Disp_tmp->CC.DYNA[Disp_tmp->IRange].T1_RANGE;
			else
				range = Disp_tmp->CC.DYNA[Disp_tmp->IRange].T2_RANGE;

			cnt1 = cnt+(range*10)+(Disp_tmp->CC.STADYNA*4);

			if(((Disp_tmp->CONF.Dyna_Level) && (cnt == CCCR_Dyn_L2) && (Disp_tmp->CC.STADYNA==Function_Dynamic)) || ((Disp_tmp->CONF.Dyna_Time) && (cnt == CCCR_Dyn_T2) && (Disp_tmp->CC.STADYNA==Function_Dynamic)))
				resolution = 0.1;
			else if((Disp_tmp->CONF.Dyna_Time) && (cnt == CCCR_Dyn_T1) && (Disp_tmp->CC.STADYNA==Function_Dynamic)) {
				if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_100Hz)
					resolution = 100;
				else if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_10Hz)
					resolution = 10;
				else if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_1Hz)
					resolution = 1;
				else
					resolution = 0.1;
			} else
				resolution = (ptrMODEL_TYPE->CC)[cnt1].Resolution;

			if( ((Disp_tmp->CC.STADYNA==Function_Dynamic)&&(cnt==CCCR_Dyn_Add_CV))||((Disp_tmp->CC.STADYNA==Function_Static)&&(cnt==CCCR_Sta_Add_CV)) ) {
				CxCV_data = dat;
				resolution = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
				data = CxCV_data * resolution;
			} else {
				data = dat*resolution;
				if((CCCR_Dyn_L1 == cnt) || ((CCCR_Dyn_L2 == cnt)&&(Disp_tmp->CC.STADYNA==Function_Static)) ||((CCCR_Dyn_L2 == cnt)&&(!Disp_tmp->CONF.Dyna_Level)) ||((cnt==CCCR_Dyn_SRUP)||((Disp_tmp->CC.STADYNA==Function_Dynamic)&&(cnt==CCCR_Dyn_SRDN))))

					data *= Get_Parallel_Parameter(I_Range);
			}
			break;			
		case P_CV:
			cnt1 = cnt+(V_Range*3);
			resolution = (ptrMODEL_TYPE->CV)[cnt1].Resolution;
			data = dat*resolution;
			break;
		case P_CR:
			if(cnt<=CCCR_Dyn_SRDN)
				range = Disp_tmp->IRange;
			else if(cnt==CCCR_Dyn_T1)
				range = Disp_tmp->CR.DYNA[Disp_tmp->IRange].T1_RANGE;
			else
				range = Disp_tmp->CR.DYNA[Disp_tmp->IRange].T2_RANGE;

			cnt1 = cnt+(range*10)+(Disp_tmp->CR.STADYNA*4);

			if(((Disp_tmp->CONF.Dyna_Level) && (cnt == CCCR_Dyn_L2) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) || ((Disp_tmp->CONF.Dyna_Time) && (cnt == CCCR_Dyn_T2) && (Disp_tmp->CR.STADYNA==Function_Dynamic)))
				resolution = 0.1;
			else if((Disp_tmp->CONF.Dyna_Time) && (cnt == CCCR_Dyn_T1) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) {
				if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_100Hz)
					resolution = 100;
				else if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_10Hz)
					resolution = 10;
				else if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_1Hz)
					resolution = 1;
				else
					resolution = 0.1;
			} else
				resolution = (ptrMODEL_TYPE->CR)[cnt1].Resolution;
			if(((Disp_tmp->CR.STADYNA==Function_Dynamic)&&(cnt==CCCR_Dyn_Add_CV))||((Disp_tmp->CR.STADYNA==Function_Static)&&(cnt==CCCR_Sta_Add_CV))) {
				CxCV_data = dat;
				resolution = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
				data = CxCV_data * resolution;
			} else {
#if 0
				if(cnt==CCCR_Dyn_SRUP) {
					if(Disp_tmp->CR.STADYNA)
						resolution *= powf(10.0,(float)Disp_tmp->CR.DYNA[Disp_tmp->IRange].SLEWRATEUP_RANGE);
					else
						resolution *= powf(10.0,(float)Disp_tmp->CR.STA[Disp_tmp->IRange].SLEWRATEUP_RANGE);
				} else if(cnt==CCCR_Dyn_SRDN) {
					if(Disp_tmp->CR.STADYNA)
						resolution *= powf(10.0,(float)Disp_tmp->CR.DYNA[Disp_tmp->IRange].SLEWRATEDN_RANGE);
					else
						resolution *= powf(10.0,(float)Disp_tmp->CR.STA[Disp_tmp->IRange].SLEWRATEDN_RANGE);
				}
#endif
				data = dat*resolution;
				if((CCCR_Dyn_L1 == cnt) || ((CCCR_Dyn_L2 == cnt)&&(Disp_tmp->CR.STADYNA==Function_Static)) ||((CCCR_Dyn_L2 == cnt)&&(!Disp_tmp->CONF.Dyna_Level)) ||((cnt==CCCR_Dyn_SRUP)||((Disp_tmp->CR.STADYNA==Function_Dynamic)&&(cnt==CCCR_Dyn_SRDN))))
					data *= Get_Parallel_Parameter(I_Range);
			}
			break;		
		case P_CP:
			if(cnt<=CP_Dyn_L2) {
				//range = Disp_tmp->IRange;
				cnt1 = cnt+(I_Range)*10+(Disp_tmp->CP.STADYNA*4);
			} else if(cnt==CP_Dyn_T1) {
				range = Disp_tmp->CP.DYNA[Disp_tmp->IRange].T1_RANGE;
				cnt1 = cnt+(range)*10+(Disp_tmp->CP.STADYNA*6);
			} else if(cnt==CP_Dyn_T2) {
				range = Disp_tmp->CP.DYNA[Disp_tmp->IRange].T2_RANGE;
				cnt1 = cnt+(range)*10+(Disp_tmp->CP.STADYNA*6);
			}

			if(((Disp_tmp->CONF.Dyna_Level) && (cnt == CP_Dyn_L2) && (Disp_tmp->CP.STADYNA==Function_Dynamic)) || ((Disp_tmp->CONF.Dyna_Time) && (cnt == CP_Dyn_T2) && (Disp_tmp->CP.STADYNA==Function_Dynamic)))
				resolution = 0.1;
			else if((Disp_tmp->CONF.Dyna_Time) && (cnt == CP_Dyn_T1) && (Disp_tmp->CP.STADYNA==Function_Dynamic)) {
				if(Disp_tmp->CP.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_100Hz)
					resolution = 100;
				else if(Disp_tmp->CP.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_10Hz)
					resolution = 10;
				else if(Disp_tmp->CP.DYNA[Disp_tmp->IRange].Frequency_Range == Dyn_Freq_TimeBase_1Hz)
					resolution = 1;
				else
					resolution = 0.1;
			} else
				resolution = (ptrMODEL_TYPE->CP)[cnt1].Resolution;

			if(((Disp_tmp->CP.STADYNA==Function_Dynamic)&&(cnt==CP_Dyn_Add_CV))||((Disp_tmp->CP.STADYNA==Function_Static)&&(cnt==CP_Sta_Add_CV))) {
				CxCV_data = dat;
				resolution = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
				data = CxCV_data * resolution;
			} else
				data = dat * resolution;

			if((CP_Dyn_L1 == cnt) || ((CP_Dyn_L2 == cnt)&&(Disp_tmp->CP.STADYNA==Function_Static))|| ((CP_Dyn_L2 == cnt)&&(!Disp_tmp->CONF.Dyna_Level)))
				data *= Get_Parallel_Parameter(I_Range);
			break;		
		case P_CC_SPEC:
			resolution = (ptrMODEL_TYPE->CC_SPEC)[cnt].Resolution;
			data = dat*resolution;
			break;		
		case P_CR_SPEC:
			resolution = (ptrMODEL_TYPE->CR_SPEC)[cnt].Resolution;
			data = dat*resolution;
			break;		
		case P_CV_SPEC:
			resolution = (ptrMODEL_TYPE->CV_SPEC)[cnt].Resolution;
			data = dat*resolution;
			break;		
		case P_CP_SPEC:
			resolution = (ptrMODEL_TYPE->CP_SPEC)[cnt].Resolution;
			data = dat*resolution;
			break;		
		case P_CONF_OTHER:
			if(P_SOFT_START == cnt)
				resolution = ptrMODEL_TYPE->CONF[2].Resolution;
			else if(P_VON_VOLTAGE == cnt)
				resolution = ptrMODEL_TYPE->CONF[V_Range].Resolution;
			else if(P_CUTOFFTIME == cnt)
				resolution = ptrMODEL_TYPE->CONF[3].Resolution;
			else if(P_Von_Delay == cnt)
				resolution = 0.001;

			data = dat * resolution;
			break;
		case P_CONF_PROT:
			if(cnt==P_OCP_LEVEL)
				resolution = ptrMODEL_TYPE->PROT[PROT_OCP_H].Resolution;
			else if(cnt==P_OPP_LEVEL)
				resolution = ptrMODEL_TYPE->PROT[PROT_OPP_H].Resolution;
			else if(cnt==P_UVP_LEVEL) {
				if(VRange_Low==Data_tmp->VRange)
					resolution = ptrMODEL_TYPE->PROT[PROT_UVP_L].Resolution;
				else
					resolution = ptrMODEL_TYPE->PROT[PROT_UVP_H].Resolution;
#if Enable_Ring_Count
			}else if(cnt==P_UVP_SETTING){
				resolution = 1;
#endif

			} else if(cnt==P_OVP_LEVEL) {
				if(VRange_Low==Data_tmp->VRange)
					resolution = ptrMODEL_TYPE->PROT[PROT_OVP_L].Resolution;
				else
					resolution = ptrMODEL_TYPE->PROT[PROT_OVP_H].Resolution;
			}
			data = dat * resolution;

			if( (P_OCP_LEVEL==cnt)||(P_OPP_LEVEL==cnt) )
				data *= Get_Parallel_Parameter(I_Range);
			break;
		case P_CONF_KNOB:
			if (cnt==P_CCH_STEP)
				resolution = (ptrMODEL_TYPE->CC)[10].Resolution;
			else if (cnt==P_CCL_STEP)
				resolution = (ptrMODEL_TYPE->CC)[0].Resolution;
			else if (cnt==P_CRH_STEP)
				resolution = (ptrMODEL_TYPE->CR)[10].Resolution;
			else if (cnt==P_CRL_STEP)
				resolution = (ptrMODEL_TYPE->CR)[0].Resolution;
			else if (cnt==P_CVH_STEP)
				resolution = (ptrMODEL_TYPE->CV)[3].Resolution;
			else if (cnt==P_CVL_STEP)
				resolution = (ptrMODEL_TYPE->CV)[0].Resolution;
			else if (cnt==P_CPH_STEP)
				resolution = (ptrMODEL_TYPE->CP)[10].Resolution;
			else if (cnt==P_CPL_STEP)
				resolution = (ptrMODEL_TYPE->CP)[0].Resolution;
			data = dat*resolution;
			break;
		case P_NSeq_Edit:
		case P_Seq_Normal:
			V_Range = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Range/2;
			I_Range = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Range%2;
			Seq_Mode_Temp = P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode;
			if(CC_MODE==Seq_Mode_Temp)
				resolution = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
			else if(CR_MODE==Seq_Mode_Temp)
				resolution = (ptrMODEL_TYPE->CR)[I_Range*10].Resolution;
			else if(CV_MODE==Seq_Mode_Temp)
				resolution = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
			else
				resolution = (ptrMODEL_TYPE->CP)[I_Range*10].Resolution;	/*CP_MODE*/
			data = dat*resolution;
			if(CV_MODE!=Seq_Mode_Temp)
				data *= Get_Parallel_Parameter(I_Range);
			break;
		case P_Seq_Fast:
		case P_FSeq_Edit:
		case P_FSeq_Fill:
			if(cnt==P_FSeq_TimeBase)
				data = dat*powf(10.0,(float)(P3k_FSeq_Disp.FSeq_TB_Range))*0.001;
			else { /*P_FSeq_Last_Set and P_FSeqEdit_Value*/
				V_Range = P3k_FSeq_Disp.FSeq_Range/2;
				I_Range = P3k_FSeq_Disp.FSeq_Range%2;
				Seq_Mode_Temp = P3k_FSeq_Disp.FSeq_Mode;
				if(CC_MODE==Seq_Mode_Temp)
					resolution = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
				else
					resolution = (ptrMODEL_TYPE->CR)[I_Range*10].Resolution;/*CR_MODE*/
				data = dat*resolution;
				data *= Get_Parallel_Parameter(I_Range);
			}
			break;	
#if Enable_Battery_Discharge
		case P_FUNC_batt:
		case P_FUNC_batt_EXECUTE:
			Seq_Mode_Temp = BattDisp.Mode;
			V_Range = BattDisp.Range/2;
			I_Range = BattDisp.Range%2;

			if(Seq_Mode_Temp==CC_MODE){
				if(cnt==P_F_BATT_Set){
					resolution = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
				}else if(cnt==P_F_BATT_SRUP){
					resolution = (ptrMODEL_TYPE->CC)[I_Range*10+2].Resolution;
					//resolution *= powf(10.0,(float)BattDisp.SRUPRange);
				}else if(cnt==P_F_BATT_SRDW){			
					resolution = (ptrMODEL_TYPE->CC)[I_Range*10+2].Resolution;
					//resolution *= powf(10.0,(float)BattDisp.SRDWRange);
				}
			}else if(Seq_Mode_Temp==CR_MODE){
				if(cnt==P_F_BATT_Set){
					resolution = (ptrMODEL_TYPE->CR)[I_Range*10].Resolution;
				}else if(cnt==P_F_BATT_SRUP){
					resolution = (ptrMODEL_TYPE->CR)[I_Range*10+2].Resolution;
					//resolution *= powf(10.0,(float)BattDisp.SRUPRange);
				}else if(cnt==P_F_BATT_SRDW){			
					resolution = (ptrMODEL_TYPE->CR)[I_Range*10+2].Resolution;
					//resolution *= powf(10.0,(float)BattDisp.SRDWRange);
				}
			}else{ //cp_mode
				if(cnt==P_F_BATT_Set){
					resolution = (ptrMODEL_TYPE->CP)[I_Range*10].Resolution;
				}else{
					dat = 0;
				}
			}
			data = dat*resolution;
			data *= Get_Parallel_Parameter(I_Range);		
			break;
#endif	
#if Enable_LED_function
		case P_FUNC_FLED:
			//Seq_Mode_Temp = P3k_FLed_Data.Seq.mode;
			V_Range = P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp].range/2;
			I_Range = P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp].range%2;	
		
			if(cnt==P_F_LED_RESPONSE){
				///resolution = (ptrMODEL_TYPE->CC)[I_Range*10+2].Resolution;
			}		
			data = dat*resolution;
			data *= Get_Parallel_Parameter(I_Range);		
			break;
		case P_FUNC_FLED_EDIT:
		case P_FUNC_FLED_EXECUTE:
			V_Range = P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp].range/2;
			I_Range = P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp].range%2;	
			switch(P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp].mode){
				case P_F_LED_MODE_VoIo:
				case P_F_LED_MODE_VoIoRc:	
					if(cnt==P_F_LED_Edit_P1){ //Vo
						resolution = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;		
					}else if(cnt==P_F_LED_Edit_P2){//Io	
						resolution = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
					}else if(cnt==P_F_LED_Edit_P3) {//Rcoff
						resolution = 0.01;	
					}
					break;					
				case P_F_LED_MODE_VoIoRd:
					if(cnt==P_F_LED_Edit_P1){//Vo
						resolution = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;	
					}else if(cnt==P_F_LED_Edit_P2){//Io	
						resolution = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;	
					}else if(cnt==P_F_LED_Edit_P3) {//Rd
						resolution = (ptrMODEL_TYPE->CR)[V_Range*10].Resolution;
					}
					break;
				case P_F_LED_MODE_VoIoVf:
					if(cnt==P_F_LED_Edit_P1){//Vo
						resolution = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;		
					}else if(cnt==P_F_LED_Edit_P2){//Io	
						resolution = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
					}else if(cnt==P_F_LED_Edit_P3) {//Vf
						resolution = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;		
					}
					break;
				case P_F_LED_MODE_VfRdPcs:
					if(cnt==P_F_LED_Edit_P1){ //Vf
						resolution = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
					}else if(cnt==P_F_LED_Edit_P2){//Rd	
						resolution = (ptrMODEL_TYPE->CR)[V_Range*10].Resolution;
					}else if(cnt==P_F_LED_Edit_P3) {//pcs
						resolution = 1;
					}
					break;
				default:
					break;	
			}				
			data = dat*resolution;
			data *= Get_Parallel_Parameter(I_Range);	
			break;
		case P_FUNC_CLED:
			//Seq_Mode_Temp = P3k_FLed_Data.Seq.mode;
			V_Range = P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].range/2;
			I_Range = P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].range%2;	
		
			if(cnt==P_CLED_VO){
				resolution = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
			}else if(cnt==P_CLED_IO){
				resolution = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
			}		
			data = dat*resolution;
			data *= Get_Parallel_Parameter(I_Range);		
			break;
		case P_FUNC_CLED_EDIT:
			resolution = 0.01;					
			data = dat*resolution;
			break;
		case P_FUNC_CLED_EXECUTE:
			V_Range = P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].range/2;
			I_Range = P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].range%2;			
			if(cnt==P_CLED_EXE_VO){
				resolution = (ptrMODEL_TYPE->CV)[V_Range*3].Resolution;
			}else if(cnt==P_CLED_EXE_IO){
				resolution = (ptrMODEL_TYPE->CC)[I_Range*10].Resolution;
			}else{
				resolution = 0.01;	
			}
			data = dat*resolution;
			if(cnt==P_CLED_EXE_IO)	data *= Get_Parallel_Parameter(I_Range);		
			break;
		
#endif	
		}
	return(data);
}

void ShowSpace(char no, int x, int y){
	GUI_SetTextAlign(GUI_TA_RIGHT);
	GUI_DispStringAt( Show_space[no-2], x, y);
}

void ShowSpace_LEFT(char no, int x, int y)
{
	GUI_SetTextAlign(GUI_TA_LEFT);
	GUI_DispStringAt( Show_space[no-2], x, y);
}



#if Enable_Optim_display
extern void LCD_WRITE_MEM_Char(unsigned int Off,unsigned char data);
static void _SetPixel_New(UWORD x, UWORD y) {
		ULONG Off = ((319-x)*256)+y;
	char color = GUI_Context.aColorIndex[1];
	LCD_WRITE_MEM_Char(Off, color);		
}

void DrawArrowPoint(int x, int y)
{
	/*
					     ###
						###
						  ###
		                         	    ###
		##################
		O#################
		##################
						   ###
						###
					    ###
					 ###

		O = (x, y)					*/



	int i,j;

	for( i = y-1 ; i<=y+1 ; i++)
		for( j = x ; j<= x+18 ; j++)
			_SetPixel_New( j, i);
	for( i=0 ; i<= 3 ; i++)
		for( j=x+12+i ; j<=x+14+i ; j++)
			_SetPixel_New( j, y-5+i);
	for( i=0 ; i<= 3 ; i++)
		for( j=x+12+i ; j<=x+14+i ; j++)
			_SetPixel_New( j , y+5-i);

}

void ShowScrollBar_Other(UWORD Scroll_Xpos,UWORD Scroll_Ypos,UBYTE TotalDispItem,UBYTE OnePageDispItem,UBYTE EveryItemInterval,UBYTE ScrollBar_width,UBYTE DispStartPos)
{
	UBYTE Ypos,Len;
	UBYTE i,j;
	UWORD LastDispItemYpos;
//	Scroll_Xpos=256;
//	Scroll_Ypos=40;
//	TotalDispItem=12;					/*Total Display Item*/
//	OnePageDispItem=6;				/* Display Item of One Page*/
//	EveryItemInterval=25;				/* Interval of Every Item*/
//	ScrollBar_width=10;
//	DispStartPos=DispScrStartCT;

	LastDispItemYpos=Scroll_Ypos+(OnePageDispItem-1)*EveryItemInterval;

	if((TotalDispItem)<=OnePageDispItem) {
		Ypos = Scroll_Ypos;
		Len = OnePageDispItem*EveryItemInterval;
	} else {
		Ypos = ((OnePageDispItem*EveryItemInterval*DispStartPos)/(TotalDispItem))+Scroll_Ypos;
		Len = (OnePageDispItem*EveryItemInterval*OnePageDispItem)/(TotalDispItem);
	}

	if(!Len)
		Len=1;

	GUI_SetColor(MEM_WHITE);

	if(Ypos>Scroll_Ypos) {
		for(i=Scroll_Ypos; i<Ypos; i++)
			for(j=1; j<=ScrollBar_width; j++)
				_SetPixel_New(Scroll_Xpos+j,i);
	}

	if((Ypos+Len)<LastDispItemYpos+EveryItemInterval-1) {
		for(i=Ypos+Len; i<LastDispItemYpos+EveryItemInterval-1; i++)
			for(j=1; j<=ScrollBar_width; j++)
				_SetPixel_New(Scroll_Xpos+j,i);
	}

	GUI_SetColor(MEM_ORANGE_ku);

	for(i=Ypos; i<Len+Ypos; i++)
		for(j=1; j<=ScrollBar_width; j++)
			_SetPixel_New(Scroll_Xpos+j,i);
		
}
#else


void DrawArrowPoint(int x, int y)
{
	/*
					     ###
						###
						  ###
		                         	    ###
		##################
		O#################
		##################
						   ###
						###
					    ###
					 ###

		O = (x, y)					*/



	int i,j;

	for( i = y-1 ; i<=y+1 ; i++)
		for( j = x ; j<= x+18 ; j++)
			GUI_DrawPixel( j, i);
	for( i=0 ; i<= 3 ; i++)
		for( j=x+12+i ; j<=x+14+i ; j++)
			GUI_DrawPixel( j, y-5+i);
	for( i=0 ; i<= 3 ; i++)
		for( j=x+12+i ; j<=x+14+i ; j++)
			GUI_DrawPixel( j , y+5-i);

}

void ShowScrollBar_Other(UWORD Scroll_Xpos,UWORD Scroll_Ypos,UBYTE TotalDispItem,UBYTE OnePageDispItem,UBYTE EveryItemInterval,UBYTE ScrollBar_width,UBYTE DispStartPos)
{
	UBYTE Ypos,Len;
	UBYTE i,j;
	UWORD LastDispItemYpos;
//	Scroll_Xpos=256;
//	Scroll_Ypos=40;
//	TotalDispItem=12;					/*Total Display Item*/
//	OnePageDispItem=6;				/* Display Item of One Page*/
//	EveryItemInterval=25;				/* Interval of Every Item*/
//	ScrollBar_width=10;
//	DispStartPos=DispScrStartCT;

	LastDispItemYpos=Scroll_Ypos+(OnePageDispItem-1)*EveryItemInterval;

	if((TotalDispItem)<=OnePageDispItem) {
		Ypos = Scroll_Ypos;
		Len = OnePageDispItem*EveryItemInterval;
	} else {
		Ypos = ((OnePageDispItem*EveryItemInterval*DispStartPos)/(TotalDispItem))+Scroll_Ypos;
		Len = (OnePageDispItem*EveryItemInterval*OnePageDispItem)/(TotalDispItem);
	}

	if(!Len)
		Len=1;

	GUI_SetColor(MEM_WHITE);

	if(Ypos>Scroll_Ypos) {
		for(i=Scroll_Ypos; i<Ypos; i++)
			for(j=1; j<=ScrollBar_width; j++)
				GUI_DrawPixel(Scroll_Xpos+j,i);
	}

	if((Ypos+Len)<LastDispItemYpos+EveryItemInterval-1) {
		for(i=Ypos+Len; i<LastDispItemYpos+EveryItemInterval-1; i++)
			for(j=1; j<=ScrollBar_width; j++)
				GUI_DrawPixel(Scroll_Xpos+j,i);
	}

	GUI_SetColor(MEM_ORANGE_ku);

	for(i=Ypos; i<Len+Ypos; i++)
		for(j=1; j<=ScrollBar_width; j++)
			GUI_DrawPixel(Scroll_Xpos+j,i);
		
}


#endif

void ShowCalMessage(void)
{
	GUI_SetFont(Parameter_Font);
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(GW_LIGHTRED);
	GUI_SetTextAlign(GUI_TA_LEFT);
	if((P3K_CALIBRATION_BAR.MODE==CC_MODE)||(P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)) {
		GUI_GotoXY(75, 150);
		GUI_DispChars(' ',60);
		if(CtrlFlag1&Cal_Wait_moment)		GUI_DispStringAt("Wait a moment...", 90, 150);
		else							GUI_DispStringAt("Data Out Of Range", 90, 150);
	} else {
		if(CtrlFlag1&Cal_Wait_moment)		GUI_DispStringAt("Wait a moment...", 90, 125);
		else							GUI_DispStringAt("Data Out Of Range", 90, 125);
	}
	CalMessageFlag |= Clear_Message;
	DMA_Update_Flag = 1;
	Update_Panel();
}

#if Enable_Ext_CalOffset
void RedrawCalMode(void)
{
	char str[9],val,Volt_str[9],Curr_str[9];
	double point;
	UWORD i;
	UBYTE display_range=1;
	UBYTE Adj_company =0;

#define CalMode		P3K_CALIBRATION_BAR.MODE

	if(p3k_Cal_data.OffsetFlag & 0x01)
		Adj_company =1;
	if(p3k_Cal_data.OffsetFlag & 0x02) //allow dispaly flag
		display_range = 0; //display range H or L
	//UBYTE y_postion=72;

	Displine(2,65,316,MEM_GRAY);
	Displine(2,66,316,GW_ORANGE_ku);
	Displine(2,67,316,MEM_WHITE);
	if((CalMode==CC_MODE)||(CalMode==CR_MODE)||(CalMode==CP_MODE)||(CalMode>=Ext_V_CC_MODE)) {
		//y_postion =97;
		if(CalMessageFlag&Clear_Message) {
			CalMessageFlag &= ~Clear_Message;
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_GotoXY(70, 150);
			GUI_DispChars(' ',60);
		}

		if(CalMessageFlag&Show_Message) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(GW_LIGHTRED);
			GUI_SetTextAlign(GUI_TA_LEFT);

			if(CtrlFlag1&Cal_Wait_moment)
				GUI_DispStringAt("Wait a moment...", 90, 150);
			else
				GUI_DispStringAt("Data Out Of Range", 90, 150);

			GUI_SetColor(MEM_WHITE);
			CalMessageFlag &= ~Show_Message;
			CalMessageFlag |= Clear_Message;
		}

		if(DispMode == DispMode_SELECT_CH) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_DispStringAt("Calibration", 125, 30);
			ClearP3KCalBG(Parameter_Bottom_Bolor);
			if( display_range )
				GUI_SetBkColor(Parameter_Select_Bar_Bolor);
			if((CalMode==CR_MODE)||(CalMode==CP_MODE)) {
				GUI_GotoXY(5, 72);
				GUI_DispChars(' ',62);
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt("OffsetAdj", 10,72);
				GUI_SetColor(Parameter_Font_R_Bolor);
				sprintf(str,"%5d",p3k_Cal_data.OffsetAdjCnt1);
				GUI_DispStringAt(str, 105+8, 72);
			} else {
				GUI_GotoXY(60, 72);
				GUI_DispChars(' ',43);
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt("OffsetAdj", 65,72);
				GUI_SetColor(Parameter_Font_R_Bolor);
				sprintf(str,"%5d",p3k_Cal_data.OffsetAdjCnt1);
				GUI_DispStringAt(str, 170+8, 72);
			}
			for( i=0 ; i<Cal_Item_Num ; i++) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);

				//if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				//	continue;

				if( display_range ) {

				} else if( i == DispCT )
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);

				if(Cal_High_Point==i) {
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Volt,Volt_str,5);
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Curr,Curr_str,5);
				} else if(Cal_Low_Point==i) {
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Volt,Volt_str,5);
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Curr,Curr_str,5);
				}

				if((CalMode==CR_MODE)||(CalMode==CP_MODE) ) {
					GUI_GotoXY(5, 97+i*25);
					GUI_DispChars(' ',62);
					if(Adj_company)
						GUI_SetColor(Parameter_Font_L_Bolor);
					else
						GUI_SetColor(MEM_LIGHTGRAY);
					GUI_DispStringAt(CalMode_title[i], 10,97+i*25);
					if(Adj_company)
						GUI_SetColor(Parameter_Font_R_Bolor);
					else
						GUI_SetColor(MEM_LIGHTGRAY);
					GUI_DispStringAt(Volt_str, 105, 97+i*25);
					GUI_DispStringAt(Curr_str, 210, 97+i*25);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt(CalMode_unit[CalMode], 190,97+i*25);
					GUI_DispStringAt("A", 295,97+i*25);
				} else {
					GUI_GotoXY(60, 97+i*25);
					GUI_DispChars(' ',43);
					if(Adj_company)
						GUI_SetColor(Parameter_Font_L_Bolor);
					else
						GUI_SetColor(MEM_LIGHTGRAY);
					GUI_DispStringAt(CalMode_title[i], 65,97+i*25);
					if(Adj_company)
						GUI_SetColor(Parameter_Font_R_Bolor);
					else
						GUI_SetColor(MEM_LIGHTGRAY);
					GUI_DispStringAt(Volt_str, 170, 97+i*25);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt(CalMode_unit[CalMode], 255,97+i*25);
				}
			}
		} else {
			GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
			GUI_SetColor(Parameter_Select_Font_Bolor);

			if((CalMode==CR_MODE)||(CalMode==CP_MODE)) {
				if( display_range ) {
					ShowSpace(7, 180, 72);
				} else {
					if(Select_Curr==P3K_CALIBRATION_BAR.Volt_Curr_Sel) {
						ShowSpace(7, 290, 97+DispCT*25);
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
						GUI_SetColor(Parameter_Font_R_Bolor);
					}
					ShowSpace(7, 180, 97+DispCT*25);
				}
			} else {
				if(display_range)
					ShowSpace(7, 250, 72);
				else
					ShowSpace(7, 250, 97+DispCT*25);
			}

			GUI_SetTextAlign(GUI_TA_LEFT);

			if( KeyInFlag & DIGI_KEY_IN ) {
				if((CalMode==CR_MODE)||(CalMode==CP_MODE)) {
					if( display_range )
						sprintf( str, " %s " , KeyinBuf );
					else if(Select_Curr==P3K_CALIBRATION_BAR.Volt_Curr_Sel)
						sprintf( Curr_str, " %s " , KeyinBuf );
					else if(Select_Volt==P3K_CALIBRATION_BAR.Volt_Curr_Sel)
						sprintf( Volt_str, " %s " , KeyinBuf );
				} else {
					if( display_range )
						sprintf( str, " %s " , KeyinBuf );
					else
						sprintf( Volt_str, " %s " , KeyinBuf );
				}
			} else {
				if( display_range )
					sprintf( str, " %5d " , p3k_Cal_data.OffsetAdjCnt1 );
				else if(Cal_High_Point==DispCT) {
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Volt,Volt_str,5);
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Curr,Curr_str,5);
				} else if(Cal_Low_Point==DispCT) {
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Volt,Volt_str,5);
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Curr,Curr_str,5);
				}
			}

			if( display_range) {
				if((CalMode==CR_MODE)||(CalMode==CP_MODE)) {
					GUI_DispStringAt(str, 105+8, 72);
				} else {
					GUI_DispStringAt(str, 170+8, 72);
				}
			} else if((CalMode==CR_MODE)||(CalMode==CP_MODE) ) {
				if(Select_Curr==P3K_CALIBRATION_BAR.Volt_Curr_Sel) {
					GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
					GUI_SetColor(Parameter_Select_Font_Bolor);
					GUI_DispStringAt(Curr_str, 210, 97+DispCT*25);
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					GUI_SetColor(Parameter_Font_R_Bolor);

					if(Cal_High_Point==DispCT)
						Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Volt,Volt_str,5);
					else
						Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Volt,Volt_str,5);
				}
				GUI_DispStringAt(Volt_str, 105, 97+DispCT*25);
			} else
				GUI_DispStringAt(Volt_str, 170, 97+DispCT*25);
		}

		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Noted_Font_Bolor);
#if 1
		if((CalMessageFlag&0x03)==0)
			GUI_DispStringAt("Power Supply Setting", 75, 150);
#else
		if((CalMessageFlag&Show_Message)==0)
			GUI_DispStringAt("Power Supply Setting", 75, 150);
#endif
		GUI_DispStringAt("VOLT:", 20, 175);
		GUI_DispStringAt("V", 140, 175);
		GUI_DispStringAt("CURR:", 170, 175);
		GUI_DispStringAt("A", 290, 175);
		GUI_SetTextAlign(GUI_TA_RIGHT);

		val = (P3K_CALIBRATION_BAR.RANGE*MODE_Number+CalMode);


		for( i=0 ; i<= 1 ; i++) {
			if((CalMode == CR_MODE) && (DispCT == 1)) {
				if(i)
					point = ((ptrMODEL_TYPE->CALI_PowSet_C)[val].Max)*((ptrMODEL_TYPE->CALI_PowSet_C)[val].Resolution) ;
				else
					point = ((ptrMODEL_TYPE->CALI_PowSet_V)[val].Def)*((ptrMODEL_TYPE->CALI_PowSet_V)[val].Resolution) ;
			} else {
				if(i)
					point = ((ptrMODEL_TYPE->CALI_PowSet_C)[val].Max)*((ptrMODEL_TYPE->CALI_PowSet_C)[val].Resolution);
				else
					point = ((ptrMODEL_TYPE->CALI_PowSet_V)[val].Max)*((ptrMODEL_TYPE->CALI_PowSet_V)[val].Resolution);
			}

			if(point<10)
				sprintf( str, "%1.3f", point);
			else if(point<100)
				sprintf( str, "%2.2f", point);
			else
				sprintf( str, "%3.1f", point);

			GUI_DispStringAt(str, 137+i*102, 175);
		}






	} else { //else CC,CR,CP,ExtV,ExtR MODE=============================,, ====================================
		if(CalMessageFlag&Clear_Message) {
			CalMessageFlag &= ~Clear_Message;
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_GotoXY(70, 125);
			GUI_DispChars(' ',60);
		}
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_GotoXY(5, 97+25);
		GUI_DispChars(' ',62);

		if(CalMessageFlag&Show_Message) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(GW_LIGHTRED);
			GUI_SetTextAlign(GUI_TA_LEFT);

			if(CtrlFlag1&Cal_Wait_moment)
				GUI_DispStringAt("Wait a moment...", 90, 125);
			else
				GUI_DispStringAt("Data Out Of Range", 90, 125);

			GUI_SetColor(MEM_WHITE);
			CalMessageFlag &= ~Show_Message;
			CalMessageFlag |= Clear_Message;
		}

		if(DispMode == DispMode_SELECT_CH) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_DispStringAt("Calibration", 125, 30);
			ClearP3KCalBG(Parameter_Bottom_Bolor);
			for( i=0 ; i<Cal_Item_Num ; i++) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);

				if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
					continue;

				if( i == DispCT )
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);

				if(Cal_High_Point==i) {
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Volt,Volt_str,5);
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Curr,Curr_str,5);
				} else if(Cal_Low_Point==i) {
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Volt,Volt_str,5);
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Curr,Curr_str,5);
				}

				if((CalMode==CR_MODE)||(CalMode==CP_MODE) ) {
					GUI_GotoXY(5, 72+i*25);
					GUI_DispChars(' ',62);
					GUI_SetColor(Parameter_Font_L_Bolor);
					GUI_DispStringAt(CalMode_title[i], 10,72+i*25);
					GUI_SetColor(Parameter_Font_R_Bolor);
					GUI_DispStringAt(Volt_str, 105, 72+i*25);
					GUI_DispStringAt(Curr_str, 210, 72+i*25);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt(CalMode_unit[CalMode], 190,72+i*25);
					GUI_DispStringAt("A", 295,72+i*25);
				} else if( (CalMode==F_IMON_MODE)||(CalMode==R_IMON_MODE) ) {
					GUI_GotoXY(5, 72+i*25);
					GUI_DispChars(' ',62);
					GUI_SetColor(Parameter_Font_L_Bolor);
					GUI_DispStringAt("IMON Curr", 10,72+i*25);
					GUI_SetColor(Parameter_Font_R_Bolor);
					GUI_DispStringAt(Volt_str, 105, 72+i*25);
					GUI_DispStringAt(Curr_str, 210, 72+i*25);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt(CalMode_unit[CalMode], 190,72+i*25);
					GUI_DispStringAt("A", 295,72+i*25);
				} else {
					GUI_GotoXY(60, 72+i*25);
					GUI_DispChars(' ',43);
					GUI_SetColor(Parameter_Font_L_Bolor);
					GUI_DispStringAt(CalMode_title[i], 65,72+i*25);
					GUI_SetColor(Parameter_Font_R_Bolor);
					GUI_DispStringAt(Volt_str, 170, 72+i*25);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt(CalMode_unit[CalMode], 255,72+i*25);
				}
			}
		} else {
			GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
			GUI_SetColor(Parameter_Select_Font_Bolor);

			if( (CalMode==CR_MODE)||(CalMode==CP_MODE)||(CalMode==F_IMON_MODE)||(CalMode==R_IMON_MODE) ) {
				if(Select_Curr==P3K_CALIBRATION_BAR.Volt_Curr_Sel) {
					ShowSpace(7, 290, 72+DispCT*25);
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					GUI_SetColor(Parameter_Font_R_Bolor);
				}
				ShowSpace(7, 180, 72+DispCT*25);
			} else
				ShowSpace(7, 250, 72+DispCT*25);

			GUI_SetTextAlign(GUI_TA_LEFT);

			if( KeyInFlag & DIGI_KEY_IN ) {
				if( (CalMode==CR_MODE)||(CalMode==CP_MODE)||(CalMode==F_IMON_MODE)||(CalMode==R_IMON_MODE) ) {
					if(Select_Curr==P3K_CALIBRATION_BAR.Volt_Curr_Sel)
						sprintf( Curr_str, " %s " , KeyinBuf );
					else if(Select_Volt==P3K_CALIBRATION_BAR.Volt_Curr_Sel)
						sprintf( Volt_str, " %s " , KeyinBuf );
				} else
					sprintf( Volt_str, " %s " , KeyinBuf );
			} else {
				if(Cal_High_Point==DispCT) {
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Volt,Volt_str,5);
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Curr,Curr_str,5);
				} else if(Cal_Low_Point==DispCT) {
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Volt,Volt_str,5);
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Curr,Curr_str,5);
				}
			}

			if( (CalMode==CR_MODE)||(CalMode==CP_MODE)||(CalMode==F_IMON_MODE)||(CalMode==R_IMON_MODE) ) {
				if(Select_Curr==P3K_CALIBRATION_BAR.Volt_Curr_Sel) {
					GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
					GUI_SetColor(Parameter_Select_Font_Bolor);
					GUI_DispStringAt(Curr_str, 210, 72+DispCT*25);
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					GUI_SetColor(Parameter_Font_R_Bolor);

					if(Cal_High_Point==DispCT)
						Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Volt,Volt_str,5);
					else
						Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Volt,Volt_str,5);
				}
				GUI_DispStringAt(Volt_str, 105, 72+DispCT*25);
			} else
				GUI_DispStringAt(Volt_str, 170, 72+DispCT*25);
		}

		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Noted_Font_Bolor);
		GUI_DispStringAt("Power Supply Setting", 75, 150);
		GUI_DispStringAt("VOLT:", 20, 175);
		GUI_DispStringAt("V", 140, 175);
		GUI_DispStringAt("CURR:", 170, 175);
		GUI_DispStringAt("A", 290, 175);
		GUI_SetTextAlign(GUI_TA_RIGHT);

		val = (P3K_CALIBRATION_BAR.RANGE*MODE_Number+CalMode);


		for( i=0 ; i<= 1 ; i++) {
			if((CalMode == CR_MODE) && (DispCT == 1)) {
				if(i)
					point = ((ptrMODEL_TYPE->CALI_PowSet_C)[val].Max)*((ptrMODEL_TYPE->CALI_PowSet_C)[val].Resolution) ;
				else
					point = ((ptrMODEL_TYPE->CALI_PowSet_V)[val].Def)*((ptrMODEL_TYPE->CALI_PowSet_V)[val].Resolution) ;
			} else {
				if(i)
					point = ((ptrMODEL_TYPE->CALI_PowSet_C)[val].Max)*((ptrMODEL_TYPE->CALI_PowSet_C)[val].Resolution);
				else
					point = ((ptrMODEL_TYPE->CALI_PowSet_V)[val].Max)*((ptrMODEL_TYPE->CALI_PowSet_V)[val].Resolution);
			}

			if(point<10)
				sprintf( str, "%1.3f", point);
			else if(point<100)
				sprintf( str, "%2.2f", point);
			else
				sprintf( str, "%3.1f", point);

			GUI_DispStringAt(str, 137+i*102, 175);
		}
	}
}


#else //2014_0922
void RedrawCalMode(void)
{
	char str[9],val,Volt_str[9],Curr_str[9];
	double point;
	UWORD i;
	UBYTE display_range=1;
	UBYTE Adj_company =0;

	if(p3k_Cal_data.OffsetFlag & 0x01)
		Adj_company =1;
	if(p3k_Cal_data.OffsetFlag & 0x02) //allow dispaly flag
		display_range = 0; //display range H or L
	//UBYTE y_postion=72;

	Displine(2,65,316,MEM_GRAY);
	Displine(2,66,316,GW_ORANGE_ku);
	Displine(2,67,316,MEM_WHITE);
	if((P3K_CALIBRATION_BAR.MODE==CC_MODE)||(P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)) {
		//y_postion =97;
		if(CalMessageFlag&Clear_Message) {
			CalMessageFlag &= ~Clear_Message;
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_GotoXY(70, 150);
			GUI_DispChars(' ',60);
		}

		if(CalMessageFlag&Show_Message) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(GW_LIGHTRED);
			GUI_SetTextAlign(GUI_TA_LEFT);

			if(CtrlFlag1&Cal_Wait_moment)
				GUI_DispStringAt("Wait a moment...", 90, 150);
			else
				GUI_DispStringAt("Data Out Of Range", 90, 150);

			GUI_SetColor(MEM_WHITE);
			CalMessageFlag &= ~Show_Message;
			CalMessageFlag |= Clear_Message;
		}

		if(DispMode == DispMode_SELECT_CH) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_DispStringAt("Calibration", 125, 30);
			ClearP3KCalBG(Parameter_Bottom_Bolor);
			if( display_range )
				GUI_SetBkColor(Parameter_Select_Bar_Bolor);
			if((P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)) {
				GUI_GotoXY(5, 72);
				GUI_DispChars(' ',62);
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt("OffsetAdj", 10,72);
				GUI_SetColor(Parameter_Font_R_Bolor);
				sprintf(str,"%5d",p3k_Cal_data.OffsetAdjCnt1);
				GUI_DispStringAt(str, 105+8, 72);
			} else {
				GUI_GotoXY(60, 72);
				GUI_DispChars(' ',43);
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt("OffsetAdj", 65,72);
				GUI_SetColor(Parameter_Font_R_Bolor);
				sprintf(str,"%5d",p3k_Cal_data.OffsetAdjCnt1);
				GUI_DispStringAt(str, 170+8, 72);
			}
			for( i=0 ; i<Cal_Item_Num ; i++) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);

				//if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				//	continue;

				if( display_range ) {

				} else if( i == DispCT )
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);

				if(Cal_High_Point==i) {
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Volt,Volt_str,5);
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Curr,Curr_str,5);
				} else if(Cal_Low_Point==i) {
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Volt,Volt_str,5);
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Curr,Curr_str,5);
				}

				if( (P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE) ) {
					GUI_GotoXY(5, 97+i*25);
					GUI_DispChars(' ',62);
					if(Adj_company)
						GUI_SetColor(Parameter_Font_L_Bolor);
					else
						GUI_SetColor(MEM_LIGHTGRAY);
					GUI_DispStringAt(CalMode_title[i], 10,97+i*25);
					if(Adj_company)
						GUI_SetColor(Parameter_Font_R_Bolor);
					else
						GUI_SetColor(MEM_LIGHTGRAY);
					GUI_DispStringAt(Volt_str, 105, 97+i*25);
					GUI_DispStringAt(Curr_str, 210, 97+i*25);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt(CalMode_unit[P3K_CALIBRATION_BAR.MODE], 190,97+i*25);
					GUI_DispStringAt("A", 295,97+i*25);
				} else {
					GUI_GotoXY(60, 97+i*25);
					GUI_DispChars(' ',43);
					if(Adj_company)
						GUI_SetColor(Parameter_Font_L_Bolor);
					else
						GUI_SetColor(MEM_LIGHTGRAY);
					GUI_DispStringAt(CalMode_title[i], 65,97+i*25);
					if(Adj_company)
						GUI_SetColor(Parameter_Font_R_Bolor);
					else
						GUI_SetColor(MEM_LIGHTGRAY);
					GUI_DispStringAt(Volt_str, 170, 97+i*25);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt(CalMode_unit[P3K_CALIBRATION_BAR.MODE], 255,97+i*25);
				}
			}
		} else {
			GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
			GUI_SetColor(Parameter_Select_Font_Bolor);

			if( (P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)) {
				if( display_range ) {
					ShowSpace(7, 180, 72);
				} else {
					if(Select_Curr==P3K_CALIBRATION_BAR.Volt_Curr_Sel) {
						ShowSpace(7, 290, 97+DispCT*25);
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
						GUI_SetColor(Parameter_Font_R_Bolor);
					}
					ShowSpace(7, 180, 97+DispCT*25);
				}
			} else {
				if(display_range)
					ShowSpace(7, 250, 72);
				else
					ShowSpace(7, 250, 97+DispCT*25);
			}

			GUI_SetTextAlign(GUI_TA_LEFT);

			if( KeyInFlag & DIGI_KEY_IN ) {
				if( (P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)) {
					if( display_range )
						sprintf( str, " %s " , KeyinBuf );
					else if(Select_Curr==P3K_CALIBRATION_BAR.Volt_Curr_Sel)
						sprintf( Curr_str, " %s " , KeyinBuf );
					else if(Select_Volt==P3K_CALIBRATION_BAR.Volt_Curr_Sel)
						sprintf( Volt_str, " %s " , KeyinBuf );
				} else {
					if( display_range )
						sprintf( str, " %s " , KeyinBuf );
					else
						sprintf( Volt_str, " %s " , KeyinBuf );
				}
			} else {
				if( display_range )
					sprintf( str, " %5d " , p3k_Cal_data.OffsetAdjCnt1 );
				else if(Cal_High_Point==DispCT) {
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Volt,Volt_str,5);
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Curr,Curr_str,5);
				} else if(Cal_Low_Point==DispCT) {
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Volt,Volt_str,5);
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Curr,Curr_str,5);
				}
			}

			if( display_range) {
				if((P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)) {
					GUI_DispStringAt(str, 105+8, 72);
				} else {
					GUI_DispStringAt(str, 170+8, 72);
				}
			} else if( (P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE) ) {
				if(Select_Curr==P3K_CALIBRATION_BAR.Volt_Curr_Sel) {
					GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
					GUI_SetColor(Parameter_Select_Font_Bolor);
					GUI_DispStringAt(Curr_str, 210, 97+DispCT*25);
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					GUI_SetColor(Parameter_Font_R_Bolor);

					if(Cal_High_Point==DispCT)
						Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Volt,Volt_str,5);
					else
						Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Volt,Volt_str,5);
				}
				GUI_DispStringAt(Volt_str, 105, 97+DispCT*25);
			} else
				GUI_DispStringAt(Volt_str, 170, 97+DispCT*25);
		}

		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Noted_Font_Bolor);
		if((CalMessageFlag&Show_Message)==0)
			GUI_DispStringAt("Power Supply Setting", 75, 150);
		GUI_DispStringAt("VOLT:", 20, 175);
		GUI_DispStringAt("V", 140, 175);
		GUI_DispStringAt("CURR:", 170, 175);
		GUI_DispStringAt("A", 290, 175);
		GUI_SetTextAlign(GUI_TA_RIGHT);

		val = (P3K_CALIBRATION_BAR.RANGE*MODE_Number+P3K_CALIBRATION_BAR.MODE);


		for( i=0 ; i<= 1 ; i++) {
			if((P3K_CALIBRATION_BAR.MODE == CR_MODE) && (DispCT == 1)) {
				if(i)
					point = ((ptrMODEL_TYPE->CALI_PowSet_C)[val].Max)*((ptrMODEL_TYPE->CALI_PowSet_C)[val].Resolution) ;
				else
					point = ((ptrMODEL_TYPE->CALI_PowSet_V)[val].Def)*((ptrMODEL_TYPE->CALI_PowSet_V)[val].Resolution) ;
			} else {
				if(i)
					point = ((ptrMODEL_TYPE->CALI_PowSet_C)[val].Max)*((ptrMODEL_TYPE->CALI_PowSet_C)[val].Resolution);
				else
					point = ((ptrMODEL_TYPE->CALI_PowSet_V)[val].Max)*((ptrMODEL_TYPE->CALI_PowSet_V)[val].Resolution);
			}

			if(point<10)
				sprintf( str, "%1.3f", point);
			else if(point<100)
				sprintf( str, "%2.2f", point);
			else
				sprintf( str, "%3.1f", point);

			GUI_DispStringAt(str, 137+i*102, 175);
		}






	} else { //else CC,CR,CP MODE=================================================================
		if(CalMessageFlag&Clear_Message) {
			CalMessageFlag &= ~Clear_Message;
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_GotoXY(70, 125);
			GUI_DispChars(' ',60);
		}
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_GotoXY(5, 97+25);
		GUI_DispChars(' ',62);

		if(CalMessageFlag&Show_Message) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(GW_LIGHTRED);
			GUI_SetTextAlign(GUI_TA_LEFT);

			if(CtrlFlag1&Cal_Wait_moment)
				GUI_DispStringAt("Wait a moment...", 90, 125);
			else
				GUI_DispStringAt("Data Out Of Range", 90, 125);

			GUI_SetColor(MEM_WHITE);
			CalMessageFlag &= ~Show_Message;
			CalMessageFlag |= Clear_Message;
		}

		if(DispMode == DispMode_SELECT_CH) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_DispStringAt("Calibration", 125, 30);
			ClearP3KCalBG(Parameter_Bottom_Bolor);
			for( i=0 ; i<Cal_Item_Num ; i++) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);

				if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
					continue;

				if( i == DispCT )
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);

				if(Cal_High_Point==i) {
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Volt,Volt_str,5);
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Curr,Curr_str,5);
				} else if(Cal_Low_Point==i) {
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Volt,Volt_str,5);
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Curr,Curr_str,5);
				}

				if( (P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE) ) {
					GUI_GotoXY(5, 72+i*25);
					GUI_DispChars(' ',62);
					GUI_SetColor(Parameter_Font_L_Bolor);
					GUI_DispStringAt(CalMode_title[i], 10,72+i*25);
					GUI_SetColor(Parameter_Font_R_Bolor);
					GUI_DispStringAt(Volt_str, 105, 72+i*25);
					GUI_DispStringAt(Curr_str, 210, 72+i*25);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt(CalMode_unit[P3K_CALIBRATION_BAR.MODE], 190,72+i*25);
					GUI_DispStringAt("A", 295,72+i*25);
				} else if( (P3K_CALIBRATION_BAR.MODE==F_IMON_MODE)||(P3K_CALIBRATION_BAR.MODE==R_IMON_MODE) ) {
					GUI_GotoXY(5, 72+i*25);
					GUI_DispChars(' ',62);
					GUI_SetColor(Parameter_Font_L_Bolor);
					GUI_DispStringAt("IMON Curr", 10,72+i*25);
					GUI_SetColor(Parameter_Font_R_Bolor);
					GUI_DispStringAt(Volt_str, 105, 72+i*25);
					GUI_DispStringAt(Curr_str, 210, 72+i*25);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt(CalMode_unit[P3K_CALIBRATION_BAR.MODE], 190,72+i*25);
					GUI_DispStringAt("A", 295,72+i*25);
				} else {
					GUI_GotoXY(60, 72+i*25);
					GUI_DispChars(' ',43);
					GUI_SetColor(Parameter_Font_L_Bolor);
					GUI_DispStringAt(CalMode_title[i], 65,72+i*25);
					GUI_SetColor(Parameter_Font_R_Bolor);
					GUI_DispStringAt(Volt_str, 170, 72+i*25);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt(CalMode_unit[P3K_CALIBRATION_BAR.MODE], 255,72+i*25);
				}
			}
		} else {
			GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
			GUI_SetColor(Parameter_Select_Font_Bolor);

			if( (P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)||(P3K_CALIBRATION_BAR.MODE==F_IMON_MODE)||(P3K_CALIBRATION_BAR.MODE==R_IMON_MODE) ) {
				if(Select_Curr==P3K_CALIBRATION_BAR.Volt_Curr_Sel) {
					ShowSpace(7, 290, 72+DispCT*25);
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					GUI_SetColor(Parameter_Font_R_Bolor);
				}
				ShowSpace(7, 180, 72+DispCT*25);
			} else
				ShowSpace(7, 250, 72+DispCT*25);

			GUI_SetTextAlign(GUI_TA_LEFT);

			if( KeyInFlag & DIGI_KEY_IN ) {
				if( (P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)||(P3K_CALIBRATION_BAR.MODE==F_IMON_MODE)||(P3K_CALIBRATION_BAR.MODE==R_IMON_MODE) ) {
					if(Select_Curr==P3K_CALIBRATION_BAR.Volt_Curr_Sel)
						sprintf( Curr_str, " %s " , KeyinBuf );
					else if(Select_Volt==P3K_CALIBRATION_BAR.Volt_Curr_Sel)
						sprintf( Volt_str, " %s " , KeyinBuf );
				} else
					sprintf( Volt_str, " %s " , KeyinBuf );
			} else {
				if(Cal_High_Point==DispCT) {
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Volt,Volt_str,5);
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Curr,Curr_str,5);
				} else if(Cal_Low_Point==DispCT) {
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Volt,Volt_str,5);
					Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Curr,Curr_str,5);
				}
			}

			if( (P3K_CALIBRATION_BAR.MODE==CR_MODE)||(P3K_CALIBRATION_BAR.MODE==CP_MODE)||(P3K_CALIBRATION_BAR.MODE==F_IMON_MODE)||(P3K_CALIBRATION_BAR.MODE==R_IMON_MODE) ) {
				if(Select_Curr==P3K_CALIBRATION_BAR.Volt_Curr_Sel) {
					GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
					GUI_SetColor(Parameter_Select_Font_Bolor);
					GUI_DispStringAt(Curr_str, 210, 72+DispCT*25);
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					GUI_SetColor(Parameter_Font_R_Bolor);

					if(Cal_High_Point==DispCT)
						Display_Parameter_Pro(P3K_CALIBRATION_BAR.HP_Volt,Volt_str,5);
					else
						Display_Parameter_Pro(P3K_CALIBRATION_BAR.LP_Volt,Volt_str,5);
				}
				GUI_DispStringAt(Volt_str, 105, 72+DispCT*25);
			} else
				GUI_DispStringAt(Volt_str, 170, 72+DispCT*25);
		}

		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Noted_Font_Bolor);
		GUI_DispStringAt("Power Supply Setting", 75, 150);
		GUI_DispStringAt("VOLT:", 20, 175);
		GUI_DispStringAt("V", 140, 175);
		GUI_DispStringAt("CURR:", 170, 175);
		GUI_DispStringAt("A", 290, 175);
		GUI_SetTextAlign(GUI_TA_RIGHT);

		val = (P3K_CALIBRATION_BAR.RANGE*MODE_Number+P3K_CALIBRATION_BAR.MODE);


		for( i=0 ; i<= 1 ; i++) {
			if((P3K_CALIBRATION_BAR.MODE == CR_MODE) && (DispCT == 1)) {
				if(i)
					point = ((ptrMODEL_TYPE->CALI_PowSet_C)[val].Max)*((ptrMODEL_TYPE->CALI_PowSet_C)[val].Resolution) ;
				else
					point = ((ptrMODEL_TYPE->CALI_PowSet_V)[val].Def)*((ptrMODEL_TYPE->CALI_PowSet_V)[val].Resolution) ;
			} else {
				if(i)
					point = ((ptrMODEL_TYPE->CALI_PowSet_C)[val].Max)*((ptrMODEL_TYPE->CALI_PowSet_C)[val].Resolution);
				else
					point = ((ptrMODEL_TYPE->CALI_PowSet_V)[val].Max)*((ptrMODEL_TYPE->CALI_PowSet_V)[val].Resolution);
			}

			if(point<10)
				sprintf( str, "%1.3f", point);
			else if(point<100)
				sprintf( str, "%2.2f", point);
			else
				sprintf( str, "%3.1f", point);

			GUI_DispStringAt(str, 137+i*102, 175);
		}
	}
}
#endif

void Draw_Cursor_Line(void)
{
	unsigned char Dot_Interval,Precision;
	unsigned short x0=0,x1=0,y0=0,y1=0;

	P3k_Disp_Str 	*Disp_tmp	= &P3k_Disp_Data;

	GL_SetColor(MEM_ORANGE_ku);
	GUI_SetTextAlign(GUI_TA_RIGHT);
	Precision = CursorPrecision;

	if(Magnification_Cnt >= Precision)
		Dot_Interval = 5;
	else
		Dot_Interval = 0;

	if(Precision) {
		x0 = 184-(Magnification_Cnt*11)-Dot_Interval;
		x1 = 193-(Magnification_Cnt*11)-Dot_Interval;
		y0 = 141+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval;
		y1 = 141+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval;
	} else {
		x0 = 184-(Magnification_Cnt*11);
		x1 = 193-(Magnification_Cnt*11);
		y0 = 141+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval;
		y1 = 141+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval;
	}

	GL_DrawLine1(x0,y0+0,x1,y1+0);
	GL_DrawLine1(x0,y0+1,x1,y1+1);
	GL_DrawLine1(x0,y0+2,x1,y1+2);
}


void Draw_Incremental_Line(void)
{
	unsigned char Dot_Interval;
	unsigned short x0=0,x1=0,y0=0,y1=0;

	P3k_Disp_Str 	*Disp_tmp	= &P3k_Disp_Data;

	GL_SetColor(MEM_ORANGE_ku);
	GUI_SetTextAlign(GUI_TA_RIGHT);

	x0 = 180-(Magnification_Cnt*11);
	x1 = 193;
	y0 = 141+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval;
	y1 = 141+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval;

	GL_DrawLine1(x0,y0+0,x1,y1+0);
	GL_DrawLine1(x0,y0+1,x1,y1+1);
	GL_DrawLine1(x0,y0+2,x1,y1+2);
}



#if 1//Enable_Optim_display


void RedrawCCModeData(void)
{
	long dat;
	int i,j;
	char Total_Display_Item,Sta_Dyna,str[20],ScrollBar_Flag=0,space_Flag=0;
	double fdat;
	P3k_Data_Str 	*Data_tmp	= &P3k_Chan_Data;
	P3k_Disp_Str 	*Disp_tmp	= &P3k_Disp_Data;

	if(Data_tmp->CONF.Ext_Setting.Control) {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt( cc_sta[0]	, Disp_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetColor(Parameter_Font_R_Bolor);
		dat = (ptrMODEL_TYPE->CC)[10*Disp_tmp->IRange].Max;
		fdat = StepToReal(dat,0);
		fdat /= 1.02;					/*Max Setting(1.05) ->Setting(1) */
		fdat *= p3k_Measure_Data.Ext_Percent;
		Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[10*Disp_tmp->IRange].precision);
		ShowSpace( 7, Para_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_LEFT);
		GUI_DispStringAt( cc_sta_unit[0], Unit_Start_X, Disp_Start_Y1+0*Disp_Interval);
		return;
	}

	Sta_Dyna = Disp_tmp->CC.STADYNA;

	if(Sta_Dyna)
		Total_Display_Item = CCCR_Dyn_Max;
	else
		Total_Display_Item = CCCR_Sta_Max;


	if(DispMode <= DispMode_BROWSE_ITEMS) {
		DrawBar(0,Total_Display_Item,Disp_Start_Y1);

		for(i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(DrawBar(2,i,j)) {
				if(DispScrCurrLoc == i)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_SetColor(Parameter_Font_L_Bolor);
				if(Sta_Dyna) {
					if(Disp_tmp->CONF.Dyna_Level && !Disp_tmp->CONF.Dyna_Time)
						GUI_DispStringAt( ccr_dyna_percent[i], Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
					else if(!Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
						GUI_DispStringAt( ccr_dyna_freq_duty[i], Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
					else if(Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
						GUI_DispStringAt( ccr_dyna_percent_freq_duty[i], Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
					else
						GUI_DispStringAt( ccr_dyna[i], Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
				} else
					GUI_DispStringAt( cc_sta[i],   Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);

				GUI_SetColor(Parameter_Font_R_Bolor);
				dat = GetChanData(i,0);
				fdat = StepToReal(dat,i);

				if(((Sta_Dyna==Function_Dynamic)&&(i==CCCR_Dyn_Add_CV))||((Sta_Dyna==Function_Static)&&(i==CCCR_Sta_Add_CV))) {
					fdat=StepToReal(dat,i);
					if(fdat < 0)
						sprintf( str, " OFF ");
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[Disp_tmp->VRange*3].precision);
				} else if(((Sta_Dyna==Function_Dynamic)&&(i==CCCR_Dyn_CV_Response))||((Sta_Dyna==Function_Static)&&(i==CCCR_Sta_CV_Response))) {
					sprintf( str,cxcv_reponse[dat]);
				} else {
					if(((Disp_tmp->CONF.Dyna_Level) && (i == CCCR_Dyn_L2) && (Disp_tmp->CC.STADYNA==Function_Dynamic)) || ((Disp_tmp->CONF.Dyna_Time) && (i == CCCR_Dyn_T2) && (Disp_tmp->CC.STADYNA==Function_Dynamic)))
						Display_Parameter_Pro(fdat,str,1);
					else if((i == CCCR_Sta_SR) && (!Disp_tmp->CC.STADYNA==Function_Dynamic))
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[i+(10*Disp_tmp->IRange)].precision);
					else if(((i == CCCR_Dyn_SRUP) || (i == CCCR_Dyn_SRDN)) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) {
						if(i == CCCR_Dyn_SRUP)
							Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[i+(10*Disp_tmp->IRange)].precision);
						else
							Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[i+(10*Disp_tmp->IRange)].precision);
					} else if((i == CCCR_Dyn_T1) && (Disp_tmp->CC.STADYNA==Function_Dynamic) && (Disp_tmp->CONF.Dyna_Time)) {
						if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency_Range == 3)
							Display_Parameter_Pro(fdat,str,1);
						else
							Display_Parameter_Pro(fdat,str,0);
					} else if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].T1_RANGE && (i == CCCR_Dyn_T1) && (Disp_tmp->CC.STADYNA==Function_Dynamic))
						Display_Parameter_Pro(fdat,str,0);
					else if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].T2_RANGE && (i == CCCR_Dyn_T2) && (Disp_tmp->CC.STADYNA==Function_Dynamic) && (!Disp_tmp->CONF.Dyna_Time))
						Display_Parameter_Pro(fdat,str,0);
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[i+(10*Disp_tmp->IRange)+(4*Disp_tmp->CC.STADYNA)].precision);
				}

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+j*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_LEFT);
				if(Sta_Dyna) {
					if(Disp_tmp->CONF.Dyna_Level && !Disp_tmp->CONF.Dyna_Time)
						GUI_DispStringAt( cc_dyna_percent_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
					else if(!Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
						GUI_DispStringAt( cc_dyna_freq_duty_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
					else if(Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
						GUI_DispStringAt( cc_dyna_percent_freq_duty_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
					else
						GUI_DispStringAt( cc_dyna_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
				} else
					GUI_DispStringAt( cc_sta_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		dat = GetChanData(DispScrCurrLoc,0);

		if( KeyInFlag & DIGI_KEY_IN )
			sprintf( str, " %s " , KeyinBuf );
		else {
			getcursortime = 1;
			fdat = StepToReal(dat, DispScrCurrLoc);
			if(((Sta_Dyna==Function_Dynamic)&&(DispScrCurrLoc==CCCR_Dyn_Add_CV))||((Sta_Dyna==Function_Static)&&(DispScrCurrLoc==CCCR_Sta_Add_CV))) {
				fdat = StepToReal(dat,DispScrCurrLoc);
				if(fdat < 0)
					sprintf( str, " OFF ");
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[Disp_tmp->VRange*3].precision);
			} else if(((Sta_Dyna==Function_Dynamic)&&(DispScrCurrLoc==CCCR_Dyn_CV_Response))||((Sta_Dyna==Function_Static)&&(DispScrCurrLoc==CCCR_Sta_CV_Response))) {
				sprintf( str,cxcv_reponse[dat]);
				space_Flag = 1;
			} else {
				if(((Disp_tmp->CONF.Dyna_Level) && (DispScrCurrLoc == CCCR_Dyn_L2) && (Disp_tmp->CC.STADYNA==Function_Dynamic)) || ((Disp_tmp->CONF.Dyna_Time) && (DispScrCurrLoc == CCCR_Dyn_T2) && (Disp_tmp->CC.STADYNA==Function_Dynamic)))
					Display_Parameter_Pro(fdat,str,1);
				else if((DispScrCurrLoc == CCCR_Sta_SR) && (!Disp_tmp->CC.STADYNA==Function_Dynamic))
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[2+(10*Disp_tmp->IRange)].precision);
				else if(((DispScrCurrLoc == CCCR_Dyn_SRUP) || (DispScrCurrLoc == CCCR_Dyn_SRDN)) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) {
					if(DispScrCurrLoc == CCCR_Dyn_SRUP)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[2+(10*Disp_tmp->IRange)].precision);
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[2+(10*Disp_tmp->IRange)].precision);
				} else if((DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CC.STADYNA==Function_Dynamic) && (Disp_tmp->CONF.Dyna_Time)) {
					if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency_Range == 3)
						Display_Parameter_Pro(fdat,str,1);
					else
						Display_Parameter_Pro(fdat,str,0);
				} else if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].T1_RANGE && (DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CC.STADYNA==Function_Dynamic))
					Display_Parameter_Pro(fdat,str,0);
				else if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].T2_RANGE && (DispScrCurrLoc == CCCR_Dyn_T2) && (Disp_tmp->CC.STADYNA==Function_Dynamic) && (!Disp_tmp->CONF.Dyna_Time))
					Display_Parameter_Pro(fdat,str,0);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[DispScrCurrLoc+(10*Disp_tmp->IRange)+(4*Disp_tmp->CC.STADYNA)].precision);
			}
			getcursortime = 0;
		}
		if(space_Flag)
			ShowSpace( 4, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		else
			ShowSpace( 7, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);

		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		if(Disp_tmp->CONF.Knob_Status)
			Draw_Cursor_Line();
		if((DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CC.STADYNA==Function_Dynamic) && (Disp_tmp->CONF.Dyna_Time)&&(DispScrEndCT>4)) {
			dat = GetChanData(CCCR_Dyn_T2,0);
			fdat = StepToReal(dat,CCCR_Dyn_T2);
			Display_Parameter_Pro(fdat,str,1);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(Parameter_Font_R_Bolor);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT+1)*Disp_Interval);
		}
		_CursorResolution = StepToReal(1, DispScrCurrLoc);
	}
}

void RedrawCRModeData(void)
{
	long dat;
	int i,j;
	char Total_Display_Item,Sta_Dyna,str[20],ScrollBar_Flag=0,space_Flag=0;
	double fdat;

	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	if(Data_tmp->CONF.Ext_Setting.Control) {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt( cr_sta[0]	, Disp_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetColor(Parameter_Font_R_Bolor);
		dat = (ptrMODEL_TYPE->CR)[10*Disp_tmp->IRange].Max;
		fdat = StepToReal(dat,0);
		fdat /= 1.02;		/*Max Setting(1.05) ->Setting(1) */
		fdat *= p3k_Measure_Data.Ext_Percent;
		if(Data_tmp->CONF.D_CR_Unit)
			Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[10*Disp_tmp->IRange].precision);
		else {
			if(fdat)
				Display_Parameter_Pro((1000.0/fdat),str,7);
			else
				sprintf(str," OPEN ");
		}
		ShowSpace( 7, Para_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_LEFT);
		if(Data_tmp->CONF.D_CR_Unit)
			GUI_DispStringAt( cg_sta_unit[0], Unit_Start_X, Disp_Start_Y1+0*Disp_Interval);
		else
			GUI_DispStringAt( cr_sta_unit[0], Unit_Start_X, Disp_Start_Y1+0*Disp_Interval);
		return;
	}

	Sta_Dyna = Disp_tmp->CR.STADYNA;

	if(Sta_Dyna)
		Total_Display_Item = CCCR_Dyn_Max;
	else
		Total_Display_Item = CCCR_Sta_Max;

	if( DispMode <= DispMode_BROWSE_ITEMS) {

		DrawBar(0,Total_Display_Item,Disp_Start_Y1);
		for(i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {			
			if(DispScrCurrLoc == i)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);
			else					GUI_SetBkColor(Parameter_Bottom_Bolor);			
			if(DrawBar(2,i,j)) {
				GUI_SetColor(Parameter_Font_L_Bolor);
				if(Sta_Dyna) {
					if(Disp_tmp->CONF.Dyna_Level && !Disp_tmp->CONF.Dyna_Time)
						GUI_DispStringAt( ccr_dyna_percent[i], Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
					else if(!Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
						GUI_DispStringAt( ccr_dyna_freq_duty[i], Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
					else if(Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
						GUI_DispStringAt( ccr_dyna_percent_freq_duty[i], Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
					else
						GUI_DispStringAt( ccr_dyna[i], Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
				} else
					GUI_DispStringAt( cr_sta[i]	, Disp_Start_X, Disp_Start_Y1+j*Disp_Interval );
				GUI_SetColor(Parameter_Font_R_Bolor);
				dat = GetChanData(i,0);
				fdat = StepToReal(dat,i);
				if(((Sta_Dyna==Function_Dynamic)&&(i==CCCR_Dyn_Add_CV))||((Sta_Dyna==Function_Static)&&(i==CCCR_Sta_Add_CV))) {
					fdat=StepToReal(dat,i);
					if(fdat < 0)
						sprintf( str, " OFF ");
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[Disp_tmp->VRange*3].precision);
				} else if(((Sta_Dyna==Function_Dynamic)&&(i==CCCR_Dyn_CV_Response))||((Sta_Dyna==Function_Static)&&(i==CCCR_Sta_CV_Response))) {
					sprintf( str,cxcv_reponse[dat]);
				} else {
					if(((Disp_tmp->CONF.Dyna_Level) && (i == CCCR_Dyn_L2) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) || ((Disp_tmp->CONF.Dyna_Time) && (i == CCCR_Dyn_T2) && (Disp_tmp->CR.STADYNA==Function_Dynamic)))
						Display_Parameter_Pro(fdat,str,1);
					else if((i == CCCR_Sta_SR) && (!Disp_tmp->CR.STADYNA==Function_Dynamic))
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR[i+(10*Disp_tmp->IRange)].precision));
					else if(((i == CCCR_Dyn_SRUP) || (i == CCCR_Dyn_SRDN)) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) {
						if(i == CCCR_Dyn_SRUP)
							Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR[i+(10*Disp_tmp->IRange)].precision));
						else
							Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR[i+(10*Disp_tmp->IRange)].precision));
					} else if((i == CCCR_Dyn_T1) && (Disp_tmp->CR.STADYNA==Function_Dynamic) && (Disp_tmp->CONF.Dyna_Time)) {
						if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency_Range == 3)
							Display_Parameter_Pro(fdat,str,1);
						else
							Display_Parameter_Pro(fdat,str,0);
					} else if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].T1_RANGE && (i == CCCR_Dyn_T1) && (Disp_tmp->CR.STADYNA==Function_Dynamic))
						Display_Parameter_Pro(fdat,str,0);
					else if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].T2_RANGE && (i == CCCR_Dyn_T2) && (Disp_tmp->CR.STADYNA==Function_Dynamic) && (!Disp_tmp->CONF.Dyna_Time))
						Display_Parameter_Pro(fdat,str,0);
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[i+(10*Disp_tmp->IRange)+(4*Disp_tmp->CR.STADYNA)].precision);

					if( (Data_tmp->CONF.D_CR_Unit==OHM_Unit)&&(i<=CCCR_Dyn_L2) ) {
						if((Disp_tmp->CONF.Dyna_Level) && (i == CCCR_Dyn_L2) && (Disp_tmp->CR.STADYNA==Function_Dynamic))
							Display_Parameter_Pro(fdat,str,1);
						else {
							if(fdat)
								Display_Parameter_Pro((1000.0/fdat),str,7);
							else
								sprintf(str," OPEN ");
						}
					}
				}
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+j*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_LEFT);
				if(Data_tmp->CONF.D_CR_Unit) {
					if(Sta_Dyna) {
						if(Disp_tmp->CONF.Dyna_Level && !Disp_tmp->CONF.Dyna_Time)
							GUI_DispStringAt( cg_dyna_percent_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
						else if(!Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
							GUI_DispStringAt( cg_dyna_freq_duty_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
						else if(Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
							GUI_DispStringAt( cg_dyna_percent_freq_duty_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
						else
							GUI_DispStringAt( cg_dyna_unit[i]	, Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
					} else
						GUI_DispStringAt( cg_sta_unit[i]	, Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
				} else {
					if(Sta_Dyna) {
						if(Disp_tmp->CONF.Dyna_Level && !Disp_tmp->CONF.Dyna_Time)
							GUI_DispStringAt( cr_dyna_percent_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
						else if(!Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
							GUI_DispStringAt( cr_dyna_freq_duty_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
						else if(Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
							GUI_DispStringAt( cr_dyna_percent_freq_duty_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
						else
							GUI_DispStringAt( cr_dyna_unit[i]	, Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
					} else
						GUI_DispStringAt( cr_sta_unit[i]	, Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
				}
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		dat = GetChanData(DispScrCurrLoc,0);

		if( KeyInFlag & DIGI_KEY_IN )
			sprintf( str, " %s " , KeyinBuf );
		else {
			getcursortime = 1;
			fdat = StepToReal(dat,DispScrCurrLoc);

			if(((Sta_Dyna==Function_Dynamic)&&(DispScrCurrLoc==CCCR_Dyn_Add_CV))||((Sta_Dyna==Function_Static)&&(DispScrCurrLoc==CCCR_Sta_Add_CV))) {
				fdat = StepToReal(dat,DispScrCurrLoc);
				if(fdat < 0)
					sprintf( str, " OFF ");
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[Disp_tmp->VRange*3].precision);
			} else if(((Sta_Dyna==Function_Dynamic)&&(DispScrCurrLoc==CCCR_Dyn_CV_Response))||((Sta_Dyna==Function_Static)&&(DispScrCurrLoc==CCCR_Sta_CV_Response))) {
				sprintf( str,cxcv_reponse[dat]);
				space_Flag = 1;
			} else {
				if(((Disp_tmp->CONF.Dyna_Level) && (DispScrCurrLoc == CCCR_Dyn_L2) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) || ((Disp_tmp->CONF.Dyna_Time) && (DispScrCurrLoc == CCCR_Dyn_T2) && (Disp_tmp->CR.STADYNA==Function_Dynamic)))
					Display_Parameter_Pro(fdat,str,1);
				else if((DispScrCurrLoc == CCCR_Sta_SR) && (!Disp_tmp->CR.STADYNA==Function_Dynamic))
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR[2+(10*Disp_tmp->IRange)].precision));
				else if(((DispScrCurrLoc == CCCR_Dyn_SRUP) || (DispScrCurrLoc == CCCR_Dyn_SRDN)) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) {
					if(DispScrCurrLoc == CCCR_Dyn_SRUP)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR[2+(10*Disp_tmp->IRange)].precision));
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR[2+(10*Disp_tmp->IRange)].precision));
				} else if((DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CR.STADYNA==Function_Dynamic) && (Disp_tmp->CONF.Dyna_Time)) {
					if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency_Range == 3)
						Display_Parameter_Pro(fdat,str,1);
					else
						Display_Parameter_Pro(fdat,str,0);
				} else if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].T1_RANGE && (DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CR.STADYNA==Function_Dynamic))
					Display_Parameter_Pro(fdat,str,0);
				else if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].T2_RANGE && (DispScrCurrLoc == CCCR_Dyn_T2) && (Disp_tmp->CR.STADYNA==Function_Dynamic) && (!Disp_tmp->CONF.Dyna_Time))
					Display_Parameter_Pro(fdat,str,0);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[DispScrCurrLoc+(10*Disp_tmp->IRange)+(4*Disp_tmp->CR.STADYNA)].precision);

				if((Data_tmp->CONF.D_CR_Unit == OHM_Unit) && (DispScrCurrLoc<=CCCR_Dyn_L2)) {
					if((Disp_tmp->CONF.Dyna_Level) && (DispScrCurrLoc == CCCR_Dyn_L2) && (Disp_tmp->CR.STADYNA==Function_Dynamic))
						Display_Parameter_Pro(fdat,str,1);
					else {
						if(fdat)
							Display_Parameter_Pro((1000.0/fdat),str,7);
						else
							sprintf(str," OPEN "); 
					}
				}
			}
			getcursortime = 0;
		}
		if(space_Flag)
			ShowSpace( 4, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		else
			ShowSpace( 8, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);

		if(Disp_tmp->CONF.Knob_Status) {
			if((DispScrCurrLoc <= CCCR_Sta_B_VALUE)&&(Disp_tmp->CONF.D_CR_Unit==OHM_Unit))
				Draw_Incremental_Line();
			else
				Draw_Cursor_Line();
		}
		if((DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CR.STADYNA==Function_Dynamic) && (Disp_tmp->CONF.Dyna_Time)&&(DispScrEndCT>4)) {
			dat = GetChanData(5,0);
			fdat = StepToReal(dat,5);
			Display_Parameter_Pro(fdat,str,1);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(Parameter_Font_R_Bolor);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT+1)*Disp_Interval);
		}
		_CursorResolution = StepToReal(1, DispScrCurrLoc);
	}
}

void RedrawCVModeData(void)
{
	long dat;
	int i;
	char str[20];
	double fdat;

	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	DispScrCurrLoc = DispCT;
	if(Data_tmp->CONF.Ext_Setting.Control) {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt( cv_sta[0]	, Disp_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetColor(Parameter_Font_R_Bolor);
		dat = (ptrMODEL_TYPE->CV)[3*Disp_tmp->VRange].Max;
		fdat = StepToReal(dat,0);
		fdat /= 1.02;		/*Max Setting(1.05) ->Setting(1) */
		fdat *= p3k_Measure_Data.Ext_Percent;
		Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[3*Disp_tmp->VRange].precision);
		ShowSpace( 7, Para_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_LEFT);
		GUI_DispStringAt( cv_unit[0], Unit_Start_X, Disp_Start_Y1+0*Disp_Interval);
		return;
	}

	if( DispMode <= DispMode_BROWSE_ITEMS) {

		DrawBar(0,4,Disp_Start_Y1);

		for( i=0 ; i<CV_Max ; i++){
			if(DispScrCurrLoc == i)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);
			else					GUI_SetBkColor(Parameter_Bottom_Bolor);	
			if(DrawBar(1,i,i)) {
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cv_sta[i], Disp_Start_X, Disp_Start_Y1+i*Disp_Interval);
				GUI_SetColor(Parameter_Font_R_Bolor);
				dat = GetChanData(i,0);				/* Get Parameter */
				fdat = StepToReal(dat,i);
				Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[i+Disp_tmp->VRange*3].precision);
				if((0==Disp_tmp->CONF.Ext_Setting.Control)||(DataRedrawFlag&BG_CLEAR_FLAG))
					ShowSpace( 7, Para_Start_X, Disp_Start_Y1+i*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+i*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( cv_unit[i], Unit_Start_X, Disp_Start_Y1+i*Disp_Interval);
			}
		}
	}
	else if(DispMode == DispMode_SET_PARAMETERS)
	{
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		dat = GetChanData(DispCT,0);

		if( KeyInFlag & DIGI_KEY_IN )
			sprintf( str, " %s " , KeyinBuf );
		else {
			getcursortime = 1;
			fdat = StepToReal(dat,DispCT);
			Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[DispCT+Disp_tmp->VRange*3].precision);
			getcursortime = 0;
		}

		ShowSpace( 7, Para_Start_X, Disp_Start_Y1+DispCT*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+DispCT*Disp_Interval);

		if(Disp_tmp->CONF.Knob_Status)
			Draw_Cursor_Line();
		_CursorResolution = StepToReal(1, DispScrCurrLoc);
	}
}

void RedrawCPModeData(void)
{
	long dat;
	int i,j;
	char Total_Display_Item,Sta_Dyna,str[20],ScrollBar_Flag=0,space_Flag=0;
	double fdat;

	P3k_Disp_Str *Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str *Data_tmp = &P3k_Chan_Data;

	if(Data_tmp->CONF.Ext_Setting.Control) {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt( cp_sta[0]	, Disp_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetColor(Parameter_Font_R_Bolor);
		dat = (ptrMODEL_TYPE->CP)[10*Disp_tmp->IRange].Max;
		fdat = StepToReal(dat,0);
		fdat /= 1.02;		/*Max Setting(1.05) ->Setting(1) */
		fdat *= p3k_Measure_Data.Ext_Percent;
		Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[10*Disp_tmp->IRange].precision);
		ShowSpace( 7, Para_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_LEFT);
		GUI_DispStringAt( cp_unit[0], Unit_Start_X, Disp_Start_Y1+0*Disp_Interval);
		return;
	}

	Sta_Dyna = Disp_tmp->CP.STADYNA;

	Total_Display_Item = CP_Sta_Max;

	if( DispMode <= DispMode_BROWSE_ITEMS) {
		DispCT = DispScrCurrLoc;
		DrawBar(0,Total_Display_Item,Disp_Start_Y1);
		for(i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++){				
			GUI_SetBkColor(Parameter_Bottom_Bolor);			
			if(DrawBar(2,i,j)){
				if(DispScrCurrLoc == i)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				else					GUI_SetBkColor(Parameter_Bottom_Bolor);	
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cp_sta[i]	, Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
				GUI_SetColor(Parameter_Font_R_Bolor);
				dat = GetChanData(i,0);
				fdat = StepToReal(dat,i);
				if(i==CP_Sta_Add_CV) {
					fdat = StepToReal(dat,i);
					if(fdat < 0)
						sprintf( str, " OFF ");
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[Disp_tmp->VRange*3].precision);
				} else if(i==CP_Sta_CV_Response) {
					sprintf( str,cxcv_reponse[dat]);
				} else {
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[i+(10*Disp_tmp->IRange)+(4*Disp_tmp->CP.STADYNA)].precision);
				}
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+j*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( cp_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		dat = GetChanData(DispScrCurrLoc,0);

		if( KeyInFlag & DIGI_KEY_IN )
			sprintf( str, " %s " , KeyinBuf );
		else {
			getcursortime = 1;
			fdat = StepToReal(dat, DispScrCurrLoc);

			if(DispScrCurrLoc==CP_Sta_Add_CV) {
				fdat = StepToReal(dat,DispScrCurrLoc);
				if(fdat < 0)
					sprintf( str, " OFF ");
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[Disp_tmp->VRange*3].precision);
			} else if(DispScrCurrLoc==CP_Sta_CV_Response) {
				sprintf( str,cxcv_reponse[dat]);
				space_Flag = 1;
			} else {
				Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[DispScrCurrLoc+(10*Disp_tmp->IRange)+(4*Disp_tmp->CP.STADYNA)].precision);
			}
			getcursortime = 0;
		}
		if(space_Flag)
			ShowSpace( 4, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		else
			ShowSpace( 7, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);

		if(Disp_tmp->CONF.Knob_Status)
			Draw_Cursor_Line();
		_CursorResolution = StepToReal(1, DispScrCurrLoc);
	}
}

void ConfigureSeparator(void)
{
	UWORD i;

	Displine(2,65,268,MEM_GRAY);
	Displine(2,66,268,GW_ORANGE_ku);
	Displine(2,67,268,MEM_WHITE);
	Displine(2,68,268,MEM_LIGHTGRAY_ku);

	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);
	GUI_SetTextAlign(GUI_TA_LEFT);
	GUI_DispStringAt("Configure", 105, 30);
}

void RedrawProtectionData(void)
{
	int i,j;
	long dat;
	char str[20];
	static char RecoderStartCT;
	double fdat;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;


	if(DispMode == DispMode_SELECT_CH)	DispMode = DispMode_BROWSE_ITEMS;




	GUI_SetBkColor(Parameter_Bottom_Bolor);
	if(DispMode == DispMode_BROWSE_ITEMS) {
		if(DrawBar(0,P_OVP_LEVEL+1,Disp_Start_Y0))ConfigureSeparator();
		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {

			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(DrawBar(2,i,j)) {
				if(DispScrCurrLoc == i)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( prot_title_str[i], Disp_Start_X, Disp_Start_Y0+j*Disp_Interval);
				GUI_SetColor(Parameter_Font_R_Bolor);
#if Enable_OPPOCP_off
				if(i<=P_OCP_SETTING){
					if((Disp_tmp->CURRMODE>=P_CV)&&(Disp_tmp->IRange==LOW_RANGE)&&(Disp_tmp->PROT.OCP[1]>ptrMODEL_TYPE->PROT[0].Max)){
						GUI_SetColor(Parameter_Font_Bolor_Para);
					}
				}
#endif
				GUI_DispStringAt( prot_unit[i], Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );			/* Display Unit */

				dat = GetChanData(i,0);
				if((i==P_OCP_SETTING)||(i==P_OPP_SETTING)) {
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( prot_str[dat], Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				} else {
					fdat=StepToReal(dat, i);
					if((DispScrCurrLoc != DispScrEndCT)&&(DispScrCurrLoc != DispScrStartCT)){
#if Enable_Ring_Count
						if(i==P_UVP_SETTING)
							ShowSpace( 4 , Para_Start_X, Disp_Start_Y0+j*Disp_Interval );
						else
#endif

						ShowSpace( 7 , Para_Start_X, Disp_Start_Y0+j*Disp_Interval );
					}

					if(((i==P_UVP_LEVEL)&&(fdat==0))||((i==P_OVP_LEVEL)&&(fdat==((ptrMODEL_TYPE->PROT)[PROT_OVP_L+Disp_tmp->VRange].Max) * ((ptrMODEL_TYPE->PROT)[PROT_OVP_L+Disp_tmp->VRange].Resolution))))
						sprintf( str, " OFF ");
					else {
						if(i==P_OCP_LEVEL)
							Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[PROT_OCP_H].precision);
						else if(i==P_OPP_LEVEL)
							Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[PROT_OPP_H].precision);
						else if(i==P_UVP_LEVEL){
							Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_UVP_L].precision);
#if Enable_Ring_Count
						}else if(i==P_UVP_SETTING){
							if(fdat==601)	sprintf( str, "Infinity");
							else if(fdat==0)	sprintf(str,"OFF");
							else			Display_Parameter_Pro(fdat,str,0);
#endif

						}else if(i==P_OVP_LEVEL)
							Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_OVP_L].precision);
					}
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				}
			}

		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
#if Enable_Ring_Count
		if(DispScrCurrLoc==P_UVP_SETTING)
			ShowSpace( 4, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		else
#endif
		ShowSpace( 7, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);

		if( KeyInFlag & DIGI_KEY_IN ) {
			/* Show Keyin Data on Screen */
			sprintf( str, " %s " , KeyinBuf );
			//ShowSpace( 7, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		} else {
			dat = GetChanData(DispScrCurrLoc,0);
			if((DispScrCurrLoc==P_OCP_SETTING)||(DispScrCurrLoc==P_OPP_SETTING)) {
				//ShowSpace( 7, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( prot_str[dat], Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			} else {
				fdat=StepToReal(dat, DispScrCurrLoc);
				if((DispScrCurrLoc==P_UVP_LEVEL)&&(fdat==0))
					sprintf( str, " OFF ");
				else if((DispScrCurrLoc==P_OVP_LEVEL)&&(fdat==((ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_OVP_L].Max) * ((ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_OVP_L].Resolution)))
					sprintf( str, " OFF ");
				else {
					if(DispScrCurrLoc==P_OCP_LEVEL)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[PROT_OCP_H].precision);
					else if(DispScrCurrLoc==P_OPP_LEVEL)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[PROT_OPP_H].precision);
					else if(DispScrCurrLoc==P_UVP_LEVEL){
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_UVP_L].precision);
#if Enable_Ring_Count
					}else if(DispScrCurrLoc==P_UVP_SETTING){
						if(fdat==601)		sprintf( str, "Infinity");
						else if(fdat==0)		sprintf(str,"OFF");
						else			Display_Parameter_Pro(fdat,str,0);
												
#endif
					}else if(DispScrCurrLoc==P_OVP_LEVEL)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_OVP_L].precision);
				}
#if Enable_Ring_Count
				if(DispScrCurrLoc==P_UVP_SETTING)
					ShowSpace( 4 , Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval );
				else
#endif
				ShowSpace( 7 , Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval );
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			}
		}
	}
//FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_C);
}




void RedrawConfigureOther(void)
{
	long dat;
	char str[20],range;
	int i,j;
	double fdat;
	static char load_status;

	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;

	if(DispMode==DispMode_SELECT_CH)		DispMode=DispMode_BROWSE_ITEMS;

	if(UTILITY.LOAD_CTL){
		DispMode = DispMode_BROWSE_ITEMS;
		KeyinBuf[0]=KeyinBuf[1]=KeyinBuf[2]=KeyinBuf[3]=KeyinBuf[4]=KeyinBuf[5]=KeyinCT=0x00;
	}

	if(DispMode == DispMode_BROWSE_ITEMS) {
		if(DrawBar(0,P_Conf_Max,Disp_Start_Y0))
			ConfigureSeparator();
		if(load_status!=UTILITY.LOAD_CTL){
			load_status = UTILITY.LOAD_CTL;
			DataRedrawFlag |= BG_CLEAR_FLAG;
			B_DispCT = DispScrCurrLoc;
		}
		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(DrawBar(2,i,j)) {
				if(DispScrCurrLoc == i)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);

				if(UTILITY.LOAD_CTL)
					GUI_SetColor(MEM_DARKGRAY);
				else
					GUI_SetColor(Parameter_Font_L_Bolor);
#if Enable_Short_invalidate
				if((i>=P_SHORT_KEY)&&(Data_tmp->CONF.Short_Fun==0))GUI_SetColor(MEM_DARKGRAY);
#endif

				if((P3k_Disp_Data.CURRMODE==CR_MODE)&&(i==P_Von_Delay))
					GUI_DispStringAt(" Von Delay-CR",Disp_Start_X, Disp_Start_Y0+j*Disp_Interval);
				else
					GUI_DispStringAt(conf_other[i],Disp_Start_X, Disp_Start_Y0+j*Disp_Interval);
				ShowSpace( conf_other_space[i], Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				dat = GetChanData(i,0);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				if(UTILITY.LOAD_CTL)
					GUI_SetColor(MEM_DARKGRAY);
				else
					GUI_SetColor(Parameter_Font_R_Bolor);
				switch(i) {
				case P_SOFT_START:
					fdat=StepToReal(dat,i);
					if(fdat==0)
						sprintf( str, " OFF ");
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CONF)[2].precision);
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt( " ms ", Conf_Unit_Start_X, Disp_Start_Y0+j*Disp_Interval);//
					break;
				case P_VON_VOLTAGE:
					fdat=StepToReal(dat, i);
					if(((ptrMODEL_TYPE->CONF)[Data_tmp->VRange].precision)==0) {
						dat=fdat;
						sprintf( str, " %d ", dat );
					} else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CONF)[Data_tmp->VRange].precision);

					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt( " V ", Conf_Unit_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_VON_LATCH:
				case P_COUNTTIME:
					GUI_DispStringAt( onoff_str[dat], Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_Von_Delay:
					fdat=StepToReal(dat,i);
					if((fdat < 2.0)||((fdat < 5.0)&&(P3k_Disp_Data.CURRMODE==CR_MODE)))
						sprintf( str, " OFF ");
					else
						Display_Parameter_Pro(fdat,str,1);
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt( " ms ", Conf_Unit_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_CUTOFFTIME:
					if(P3k_Chan_Data.CONF.cut_off_time_total)
						sprintf( str, " %03dh: %02dm: %02ds ",P3k_Chan_Data.CONF.Cut_Off_Time_h,P3k_Chan_Data.CONF.Cut_Off_Time_m,P3k_Chan_Data.CONF.Cut_Off_Time_s);
					else
						sprintf( str, "  OFF          ");
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, 260, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_CR_Unit:
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( Input_Mode[dat], Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_Dyna_Level:
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( Dyna_Level[dat], Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_Dyna_Time:
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( Dyna_Time[dat], Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_Mem_Recall:
					GUI_DispStringAt( Memory_str[dat],Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_SHORT_KEY:
#if Enable_Short_invalidate				
				if(Data_tmp->CONF.Short_Fun==0)GUI_SetColor(MEM_DARKGRAY);
#endif					
					GUI_DispStringAt( short_key[dat],Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
#if Enable_Short_invalidate
			case P_SHORT_Fun:
				GUI_DispStringAt( onoff_str[dat],Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				break;				
			case P_SHORT_Safety:	
				if(Data_tmp->CONF.Short_Fun==0)GUI_SetColor(MEM_DARKGRAY);
				GUI_DispStringAt( onoff_str[dat],Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				break;
#endif					
				default:
					break;
				}
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		if(DispScrCurrLoc==P_CUTOFFTIME) {
			if(1) {
				GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(Disp_Start_X,Disp_Start_Y0+j*Disp_Interval);
				GUI_DispChars(' ',HiLight_Length);
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt(conf_other[P_CUTOFFTIME],Disp_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_SetColor(Parameter_Font_R_Bolor);
				sprintf( str, " %03dh: %02dm: %02ds ",P3k_Chan_Data.CONF.Cut_Off_Time_h,P3k_Chan_Data.CONF.Cut_Off_Time_m,P3k_Chan_Data.CONF.Cut_Off_Time_s);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, 260, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			}
			GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
			if(P3k_Chan_Data.CONF.Cut_Off_cnt==0)
				ShowSpace( 4,155,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			else if(P3k_Chan_Data.CONF.Cut_Off_cnt==1)
				ShowSpace( 3,197,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			else if(P3k_Chan_Data.CONF.Cut_Off_cnt==2)
				ShowSpace( 3,245,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		} else
			ShowSpace( conf_other_space[DispScrCurrLoc],Conf_Para_Start_X,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		if(KeyInFlag & DIGI_KEY_IN) {
			if(DispScrCurrLoc!=P_CUTOFFTIME) {
				sprintf( str, " %s " , KeyinBuf );
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			} else {
				GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
				GUI_SetColor(Parameter_Select_Font_Bolor);
				sprintf( str, " %s " , KeyinBuf );
				GUI_SetTextAlign(GUI_TA_RIGHT);
				if(P3k_Chan_Data.CONF.Cut_Off_cnt==0)
					GUI_DispStringAt( str, 155, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				else if(P3k_Chan_Data.CONF.Cut_Off_cnt==1)
					GUI_DispStringAt( str, 197, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				else if(P3k_Chan_Data.CONF.Cut_Off_cnt==2)
					GUI_DispStringAt( str, 245, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			}
		} else {
			dat = GetChanData(DispScrCurrLoc,0);

			switch(DispScrCurrLoc) {
			case P_SOFT_START:
				if( KeyInFlag & DIGI_KEY_IN )
					sprintf( str, " %s " , KeyinBuf );
				else {
					fdat = StepToReal(dat,DispScrCurrLoc);
					if(fdat==0)
						sprintf( str, " OFF ");
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CONF)[2].precision);
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				}
				break;
			case P_VON_VOLTAGE:
				fdat=StepToReal(dat, DispScrCurrLoc);

				if(((ptrMODEL_TYPE->CONF)[Data_tmp->VRange].precision)==0) {
					dat = fdat;
					if(dat > 0)
						sprintf( str, " %d ", dat );
				} else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CONF)[Data_tmp->VRange].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_CUTOFFTIME:
				if(P3k_Chan_Data.CONF.Cut_Off_cnt==0)
					dat = P3k_Chan_Data.CONF.Cut_Off_Time_h;
				else if(P3k_Chan_Data.CONF.Cut_Off_cnt==1)
					dat = P3k_Chan_Data.CONF.Cut_Off_Time_m;
				else if(P3k_Chan_Data.CONF.Cut_Off_cnt==2)
					dat = P3k_Chan_Data.CONF.Cut_Off_Time_s;
				GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
				GUI_SetColor(Parameter_Select_Font_Bolor);

				fdat= dat;
				range = 3;
				if(((ptrMODEL_TYPE->CONF)[range].precision)==0) {
					if(P3k_Chan_Data.CONF.cut_off_time_total)
						sprintf( str, " %d ", dat );
					else
						sprintf( str, "     OFF      ");
				} else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CONF)[range].precision);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				if(P3k_Chan_Data.CONF.cut_off_time_total) {
					if(P3k_Chan_Data.CONF.Cut_Off_cnt==0)
						GUI_DispStringAt( str, 155, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
					else if(P3k_Chan_Data.CONF.Cut_Off_cnt==1)
						GUI_DispStringAt( str, 197, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
					else if(P3k_Chan_Data.CONF.Cut_Off_cnt==2)
						GUI_DispStringAt( str, 245, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				} else {
					GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				}
				break;
			case P_VON_LATCH:
			case P_COUNTTIME:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( onoff_str[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_Von_Delay:
				if( KeyInFlag & DIGI_KEY_IN )
					sprintf( str, " %s " , KeyinBuf );
				else {
					fdat = StepToReal(dat,DispScrCurrLoc);
					if((fdat < 2.0)||((fdat < 5.0)&&(P3k_Disp_Data.CURRMODE==CR_MODE)))
						sprintf( str, " OFF ");
					else
						Display_Parameter_Pro(fdat,str,1);
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				}
				break;
#if 0
			case P_Response:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Chan_Response[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
#endif
			case P_CR_Unit:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Input_Mode[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_Dyna_Level:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Dyna_Level[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_Dyna_Time:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Dyna_Time[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_Mem_Recall:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Memory_str[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_SHORT_KEY:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( short_key[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
#if Enable_Short_invalidate
			case P_SHORT_Fun:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( onoff_str[dat],Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;				
			case P_SHORT_Safety:	
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( onoff_str[dat],Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
#endif					
			default:
				break;
			}
		}
	}
}



void RedrawSpecData(void)
{
	long dat,centerval;
	int i,j;
	char tmp,tmp1,str[20],type,ScrollBar_Flag=0,Total_Display_Item;
	double fdat,fdat1;
	UBYTE Precision=1;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;

	type =  Disp_tmp->SPECTYPE;

	if(type)	Total_Display_Item = P_SPEC_CENTER+1;
	else		Total_Display_Item = P_SPEC_CENTER;



	if(DispMode == DispMode_SELECT_CH)
		DispMode = DispMode_BROWSE_ITEMS;

	if(DispMode == DispMode_BROWSE_ITEMS) {
		if(DrawBar(0,Total_Display_Item,Disp_Start_Y0))
			ConfigureSeparator();

#if 1
		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(DrawBar((1+type),i,j)) {
				if(DispScrCurrLoc == i)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);
#else
		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(type) {
				ShowScrollBar_Other(Scroll_Bar_Start_X,Disp_Start_Y0,Total_Display_Item,Disp_Item_Num1,Disp_Interval,Scroll_Bar_Width,DispScrStartCT);
				GUI_SetBkColor(Parameter_Bottom_Bolor);
			}
			if((DispScrCurrLoc == DispScrEndCT)||(DispScrCurrLoc == DispScrStartCT)) {
				if( i == DispScrCurrLoc)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(Disp_Start_X,Disp_Start_Y0+j*Disp_Interval);
				GUI_DispChars(' ',HiLight_Length);
			} else {
				if( i == DispScrCurrLoc || i == B_DispCT ) {
					if( i==DispScrCurrLoc)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					GUI_GotoXY(Disp_Start_X,Disp_Start_Y0+j*Disp_Interval);
					GUI_DispChars(' ',HiLight_Length);
				}
			}
#endif
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( spec_str[i], Disp_Start_X, Disp_Start_Y0+j*Disp_Interval);

				if(i==P_SPEC_TEST) {
					if(Disp_tmp->SPEC)	sprintf( str, " ON ");
					else				sprintf( str, " OFF ");
				} else if(i==P_SPEC_DELAY) {
					fdat=Disp_tmp->P_F_Delay/10.0;
					Display_Parameter_Pro(fdat,str,1);
				} else if(i==P_SPEC_ENTRY) {
					if(Disp_tmp->SPECTYPE)	sprintf( str, " Percent ");
					else					sprintf( str, " Value ");
				} else if(i==P_SPEC_CENTER) {
					/*Center*/
					dat = GetChanData(i+1,0);				/* Get Paramter */
					fdat = StepToReal(dat,0);				/* Get Resolution, Max, Min */
					if(CV_MODE!=Disp_tmp->CURRMODE)	Precision = (ptrMODEL_TYPE->CC_SPEC)[0].precision;
					else							Precision = (ptrMODEL_TYPE->CV_SPEC)[0].precision;
					Display_Parameter_Pro(fdat,str,Precision);
				} else {
					if(type) {
						/*High and Low*/
						dat = GetChanData( i+6,0);
						fdat1 = dat/10.0;
						Display_Parameter_Pro(fdat1,str,1);
					} else {
						dat = GetChanData( i+4,0);
						fdat = StepToReal(dat, i-3);
						if(CV_MODE!=Disp_tmp->CURRMODE)	Precision = (ptrMODEL_TYPE->CC_SPEC)[0].precision;
						else							Precision = (ptrMODEL_TYPE->CV_SPEC)[0].precision;
						Display_Parameter_Pro(fdat,str,Precision);
					}
				}
				GUI_SetColor(Parameter_Font_R_Bolor);
				if( (i==P_SPEC_TEST)||(i==P_SPEC_DELAY) )	ShowSpace( 4 , Para_Start_X, Disp_Start_Y0+j*Disp_Interval );
				else										ShowSpace( 7 , Para_Start_X, Disp_Start_Y0+j*Disp_Interval );
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_LEFT);
				if(i==P_SPEC_DELAY)
					GUI_DispStringAt( " s ", Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
				if(i<P_SPEC_HIGH)
					continue;
				if( type ) {
					if( M_num==P_CC_SPEC || M_num==P_CR_SPEC || M_num==P_CP_SPEC )
						GUI_DispStringAt( spec_unit_pcet[i-3], Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
					else
						GUI_DispStringAt( spec1_unit_pcet[i-3], Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
				} else {
					if( M_num==P_CC_SPEC || M_num==P_CR_SPEC || M_num==P_CP_SPEC )
						GUI_DispStringAt( spec_unit_val[i-3], Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
					else
						GUI_DispStringAt( spec1_unit_val[i-3], Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
				}
			}
		}

	}
	else if(DispMode == DispMode_SET_PARAMETERS)
	{
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if( KeyInFlag & DIGI_KEY_IN ) {
			/* Show Keyin Data on Screen */
			sprintf( str, " %s " , KeyinBuf );
		} else {
			/* Show Memory Data on Screen */
			if(DispScrCurrLoc==P_SPEC_TEST) {
				if(Disp_tmp->SPEC)	sprintf( str, " ON ");
				else				sprintf( str, " OFF ");
			} else if(DispScrCurrLoc==P_SPEC_DELAY) {
				fdat=Disp_tmp->P_F_Delay/10.0;
				Display_Parameter_Pro(fdat,str,1);
			} else if(DispScrCurrLoc==P_SPEC_ENTRY) {
				if(Disp_tmp->SPECTYPE)	sprintf( str, " Percent ");
				else					sprintf( str, " Value ");
			} else if(DispScrCurrLoc==P_SPEC_CENTER) {
				dat = GetChanData( DispScrCurrLoc+1,0);				/* Get Paramter */
				fdat = StepToReal(dat,0);					/* Get Resolution, Max, Min */
				if(CV_MODE!=Disp_tmp->CURRMODE)	Precision = (ptrMODEL_TYPE->CC_SPEC)[0].precision;
				else							Precision = (ptrMODEL_TYPE->CV_SPEC)[0].precision;
				Display_Parameter_Pro(fdat,str,Precision);
			} else {
				if(type) {
					dat = GetChanData( DispScrCurrLoc+6,0);
					fdat1 = dat/10.0;
					Display_Parameter_Pro(fdat1,str,1);
				} else {
					dat = GetChanData( DispScrCurrLoc+4,0);
					fdat = StepToReal(dat, DispScrCurrLoc-3);
					if(CV_MODE!=Disp_tmp->CURRMODE)	Precision = (ptrMODEL_TYPE->CC_SPEC)[0].precision;
					else							Precision = (ptrMODEL_TYPE->CV_SPEC)[0].precision;
					Display_Parameter_Pro(fdat,str,Precision);
				}
			}
		}
		if((DispScrCurrLoc==P_SPEC_TEST)||(DispScrCurrLoc==P_SPEC_DELAY))
			ShowSpace( 4 , Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval );
		else
			ShowSpace( 7 , Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval );
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
	}
}

void RedrawSync(void)
{
#define data_xaddr		35
	long dat;
	int i,j;
	char Total_Display_Item,Sta_Dyna,str[20],ScrollBar_Flag=0;
	double fdat;
	unsigned char Total_Item;

	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	ConfigureSeparator();

	if(DispMode_BROWSE_ITEMS==DispMode) {
		for(i = 0 ; i < P_Sync_MAX; i++) {
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&(DispMode == DispMode_BROWSE_ITEMS) && ( i != B_DispCT && i != DispCT ) )
				continue;
			GUI_SetBkColor(Parameter_Bottom_Bolor);

			if(DispMode != DispMode_SELECT_CH && ( i == B_DispCT || i == DispCT ) ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				Draw_Bar_25(Disp_Start_X, Disp_Start_Y0+ i*Disp_Interval,HiLight_Length);				
			}
			GUI_SetTextAlign(GUI_TA_LEFT);
			
			GUI_SetColor(Parameter_Font_L_Bolor);			
			GUI_DispStringAt( Parallel_item[i], Disp_Start_X, Disp_Start_Y0+i*Disp_Interval);
			ShowSpace( 6, Para_Start_X+data_xaddr, Disp_Start_Y0 + i*Disp_Interval);
			

			dat = GetChanData(i,0);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			
			GUI_SetColor(Parameter_Font_R_Bolor);

			if((i==P_Sync_TrigIn)||(i==P_Sync_TrigOut)){	
				GUI_DispStringAt(Parallel_Mode[dat],Para_Start_X+data_xaddr, Disp_Start_Y0 + i*Disp_Interval);
			} else {
				fdat = dat;
				fdat =fdat/2;
				sprintf( str, " %3.1f ", fdat );
				GUI_DispStringAt(str,Para_Start_X+data_xaddr, Disp_Start_Y0 + i*Disp_Interval);
				
				GUI_DispStringAt( "us", Para_Start_X+data_xaddr+2, Disp_Start_Y0 + i*Disp_Interval);
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		if(KeyInFlag & DIGI_KEY_IN) {
			ShowSpace( Sync_space[DispCT], Para_Start_X+data_xaddr, Disp_Start_Y0 + DispCT*Disp_Interval);
			sprintf( str, " %s " , KeyinBuf );
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X+data_xaddr, Disp_Start_Y0 + DispCT*Disp_Interval);
		}else{
			dat = GetChanData(DispCT,0);
			ShowSpace( Sync_space[DispCT], Para_Start_X+data_xaddr, Disp_Start_Y0 + DispCT*Disp_Interval);
			GUI_SetTextAlign(GUI_TA_RIGHT);

			//GUI_DispStringAt(Parallel_Mode[dat], Para_Start_X+data_xaddr, Disp_Start_Y0 + DispCT*Disp_Interval);

			if((DispCT==P_Sync_TrigIn)||(DispCT==P_Sync_TrigOut))	
				GUI_DispStringAt(Parallel_Mode[dat],Para_Start_X+data_xaddr, Disp_Start_Y0 + DispCT*Disp_Interval);
			else {
				fdat = dat;
				fdat =fdat/2;
				sprintf( str, " %3.1f ", fdat );
				GUI_DispStringAt(str,Para_Start_X+data_xaddr, Disp_Start_Y0 + DispCT*Disp_Interval);
			}
		}
	}
}

void RedrawKnobData(void)
{
	long dat;
	char str[20],range,Total_Display_Item;
	int i,j;
	double fdat;
	double Para_s = Get_Parallel_Parameter(P3k_Chan_Data.IRange);
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	Total_Display_Item = P_Konb_MAX;



	if(DispMode==DispMode_SELECT_CH)		DispMode=DispMode_BROWSE_ITEMS;

	if(DispMode == DispMode_BROWSE_ITEMS) {
		if(DrawBar(0,Total_Display_Item,Disp_Start_Y0))
			ConfigureSeparator();
		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(DrawBar(2,i,j)) {
				if(DispScrCurrLoc == i)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);


				if(Disp_tmp->CONF.Knob_Status && i>=P_CCH_STEP)
					GUI_SetColor(MEM_DARKGRAY);
				else
					GUI_SetColor(Parameter_Font_L_Bolor);

				GUI_DispStringAt(conf_knob[i],Disp_Start_X, Disp_Start_Y0+j*Disp_Interval);
				ShowSpace( 7, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);

				dat = GetChanData(i,0);
				GUI_SetTextAlign(GUI_TA_RIGHT);

				if(Disp_tmp->CONF.Knob_Status && i>=P_CCH_STEP)
					GUI_SetColor(MEM_DARKGRAY);
				else
					GUI_SetColor(Parameter_Font_R_Bolor);

				switch(i) {
				case P_Knob_Status:
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( knob_status[dat], Para_Start_X+52, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_CCH_STEP://	case P_CCM_STEP:
				case P_CCL_STEP:
					fdat=StepToReal(dat, i)*Para_s;

					if(i==P_CCH_STEP)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[10].precision);
					//else if(i==P_CCM_STEP)
					//	Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[10].precision);
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[0].precision);

					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt( " A ", Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
					break;
				case P_CRH_STEP://case P_CRM_STEP:
				case P_CRL_STEP:
					fdat=StepToReal(dat, i)*Para_s;

					if(i==P_CRH_STEP)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[10].precision);
					//else if(i==P_CRM_STEP)
					//	Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[10].precision);
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[0].precision);

					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt( " mS ", Unit_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_CVH_STEP:
				case P_CVL_STEP:
					fdat=StepToReal(dat, i);

					if(i==P_CVH_STEP)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[3].precision);
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[0].precision);

					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt( " V ", Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
					break;
				case P_CPH_STEP:
					//case P_CPM_STEP:
				case P_CPL_STEP:
					fdat=StepToReal(dat, i)*Para_s;

					if(i==P_CPH_STEP)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[10].precision);
					//else if(i==P_CPM_STEP)
					//	Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[10].precision);
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[0].precision);

					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt( " W ", Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
					break;
				default:
					break;
				}
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN) {
			ShowSpace( conf_knob_space[DispScrCurrLoc], Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			sprintf( str, " %s " , KeyinBuf );
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		} else {
			dat = GetChanData(DispScrCurrLoc,0);
			ShowSpace( conf_knob_space[DispScrCurrLoc], Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			fdat=StepToReal(dat, DispScrCurrLoc);

			switch(DispScrCurrLoc) {
			case P_Knob_Status:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( knob_status[dat], Para_Start_X+52, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_CCH_STEP:
				//case P_CCM_STEP:
			case P_CCL_STEP:
				fdat=StepToReal(dat, DispScrCurrLoc)*Para_s;

				if(DispScrCurrLoc==P_CCH_STEP)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[10].precision);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[0].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_CRH_STEP:
				//case P_CRM_STEP:
			case P_CRL_STEP:
				fdat=StepToReal(dat, DispScrCurrLoc)*Para_s;

				if(DispScrCurrLoc==P_CRH_STEP)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[10].precision);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[0].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_CVH_STEP:
			case P_CVL_STEP:
				fdat=StepToReal(dat, DispScrCurrLoc);

				if(DispScrCurrLoc==P_CVH_STEP)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[3].precision);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[0].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_CPH_STEP:
				//case P_CPM_STEP:
			case P_CPL_STEP:
				fdat=StepToReal(dat, DispScrCurrLoc)*Para_s;

				if(DispScrCurrLoc==P_CPH_STEP)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[10].precision);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[0].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			default:
				break;
			}
		}
	}
}

void RedrawExtFunction(void)
{
	long dat;
	int i,j;
	char Total_Display_Item,Sta_Dyna,str[20],ScrollBar_Flag=0;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;


	DispScrCurrLoc = DispCT;
	if(DispMode_BROWSE_ITEMS == DispMode) {
		if(DrawBar(0,5,72))		ConfigureSeparator();
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		for(i=0 ; i<P_Ext_MAX ; i++) {
			if(DrawBar(1,i,i)) {
				if(DispScrCurrLoc == i)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);
#if NF_flag
				if(i>= P_Extmulti_para)break;
#endif
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( External_item[i], Disp_Start_X, Disp_Start_Y0+i*Disp_Interval);
				ShowSpace( 6, Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
				dat = GetChanData(i,0);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_SetColor(Parameter_Font_R_Bolor);

				if(P_Ext_Control==i)
					GUI_DispStringAt(External_Control[dat],	Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
				else if(P_Ext_LoadON_IN==i) {
					if(P3k_Chan_Data.CONF.Ext_Setting.MultilPara)
						GUI_SetColor(Parameter_Font_Bolor_Para);
					GUI_DispStringAt(External_LoadOnIn[dat], Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
				} else
					GUI_DispStringAt(External_Multi[dat], Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		dat = GetChanData(DispCT,0);
		ShowSpace( 6, Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);

		if(P_Ext_Control==DispCT)
			GUI_DispStringAt(External_Control[dat],	Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		else if(P_Ext_LoadON_IN==DispCT) {
			GUI_DispStringAt(External_LoadOnIn[dat], Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		} else if(P_Extmulti_para==DispCT) {
			GUI_DispStringAt(External_Multi[dat], Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		}

	}
}



static const char Media_USB_Item[4][25]	= { " Data Type ",	" Save File ",		" Recall File "," Save Folder " };
static const char FileChan_title[3][25]	= { " Memory ",		" Setup Memory ",	" Preset " };
static const char FileChan_Data[5][25]	= { " Memory ",		" Setup ",			" Preset ",		" NSeq. ", " FSeq. " };
static const int FileChan_space[2]= {9,5};
static const int Memory_y_addr[2] = { 65, 100 };
static const int USB_y_addr[3]	 = {65, 100, 125  };		/* USB string Y location */

void RedrawFileChan(void)
{
	int i;
	char str[30];
	OverWrite_Flag = 0;

	if(Save_Recall_InfoFlag&Data_Process) { /*Show Message*/
		if( (F_Media_USB==p3k_File_Utility_BAR.MEDIA)||(F_Media_Default==p3k_File_Utility_BAR.MEDIA) ) { /*Media USB*/
			GUI_SetBkColor(Message_Bottom_Bolor);
			GUI_GotoXY(Disp_Start_X, 175);
			GUI_DispChars(' ',51);
			GUI_SetColor(Message_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);

			if(Save_Recall_InfoFlag&Save_Ok) {
				Save_Recall_InfoFlag&=~Save_Ok;
				sprintf(str," %s Save Ok ",SaveFileName_Temp);
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else if(Save_Recall_InfoFlag&Save_Fail) {
				Save_Recall_InfoFlag&=~Save_Fail;
				sprintf(str," %s Save Failed ",SaveFileName_Temp);
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else if(Save_Recall_InfoFlag&Save_All_Ok) {
				Save_Recall_InfoFlag&=~Save_All_Ok;
				sprintf(str," %s Save Ok ",SaveFileName_Temp);
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else if(Save_Recall_InfoFlag&Save_All_Fail) {
				Save_Recall_InfoFlag&=~Save_All_Fail;
				sprintf(str," %s Save Failed ",SaveFileName_Temp);
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else if(Save_Recall_InfoFlag&Recall_Ok) {
				Save_Recall_InfoFlag&=~Recall_Ok;
				sprintf(str," %s Recall Ok ",RecallFileName);
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else if(Save_Recall_InfoFlag&Recall_Fail) {
				Save_Recall_InfoFlag&=~Recall_Fail;
				sprintf(str," %s Recall Failed ",RecallFileName);
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else if(Save_Recall_InfoFlag&Type_Error) {
				Save_Recall_InfoFlag&=~Type_Error;
				sprintf(str," Machine Type Error ");
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else if(Save_Recall_InfoFlag&Device_Error) {
				Save_Recall_InfoFlag&=~Device_Error;
				sprintf(str," Device Open Error ");
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else if(Save_Recall_InfoFlag&No_File) {
				Save_Recall_InfoFlag&=~No_File;
				sprintf(str," No File to Recall ");
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else
				Save_Recall_InfoFlag&=~Data_Process;
		} else
			Save_Recall_InfoFlag&=~Data_Process;
	}
	/*-------------------Media:Default------------------*/
	if(F_Media_Default==p3k_File_Utility_BAR.MEDIA) { /*Media Default*/
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt(" Load Default Setup ", Disp_Start_X, 40);
		DispMode = DispMode_SELECT_CH;
		DispCT = 0;
		return;
	}
	/*-------------------Media:USB------------------*/
	if(F_Media_USB==p3k_File_Utility_BAR.MEDIA) { /*Media USB*/
		Displine(2,94,267,MEM_GRAY);
		Displine(2,95,267,GW_ORANGE_ku);
		Displine(2,96,267,MEM_WHITE);
		if(DispMode ==DispMode_SELECT_CH) {
			for( i=0 ; i < P_USB_Max ; i++) {
				if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i!=B_DispCT && i!=DispCT ) )
					continue;
				GUI_SetBkColor(Parameter_Bottom_Bolor);

				if( i==DispCT )
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);

				GUI_GotoXY(Disp_Start_X, USB_y_addr[i]);
				GUI_DispChars(' ',52);

				if(i==P_USB_Type)
					GUI_SetColor(Parameter_Font_U_Bolor);
				else
					GUI_SetColor(Parameter_Font_L_Bolor);

				GUI_DispStringAt(Media_USB_Item[i], Disp_Start_X, USB_y_addr[i]);

				if(i==P_USB_Type)
					sprintf(str, " %s ", FileChan_Data[p3k_File_Utility_BAR.USB_Data_Type]);
				else if(i==P_USB_Save) {
					if(SaveFileName[0]==0)
						sprintf( SaveFileName, " No File ");

					sprintf( str, " %s ", SaveFileName);
				} else if(i==P_USB_Recall) {
					if(RecallFileName[0]==0)
						sprintf( RecallFileName, " No File ");

					sprintf( str, " %s ", RecallFileName);
				}
				GUI_SetColor(Parameter_Font_R_Bolor);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt(str, 260, USB_y_addr[i]);
			}
		} else {
			GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
			GUI_SetColor(Parameter_Select_Font_Bolor);

			if(DispCT==P_USB_Type)
				sprintf(str, " %s ", FileChan_Data[p3k_File_Utility_BAR.USB_Data_Type]);
			else if(DispCT==P_USB_Save)
				sprintf(str, " %s ", SaveFileName);
			else if(DispCT==P_USB_Recall)
				sprintf(str, " %s ", RecallFileName);

			if(DispCT==P_USB_Type)
				ShowSpace( 11, 260+5, USB_y_addr[DispCT]);
			else {
				GUI_GotoXY(135, USB_y_addr[DispCT]);
				GUI_DispChars(' ',26);
			}
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, 260, USB_y_addr[DispCT]);
		}

		if(USB_Status_Display==USB_Exist) {
			GUI_SetBkColor(Message_Bottom_Bolor);
			GUI_SetColor(Noted_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_DispStringAt(" Path: ", Disp_Start_X, 150);
			GUI_DispStringAt(FMShowfilePath, 65, 150);
		}
		return;
	}
	/*-------------------Media:Memory------------------*/
	if(DispMode ==DispMode_SELECT_CH) {
		Displine(2,94,267,MEM_GRAY);
		Displine(2,95,267,GW_ORANGE_ku);
		Displine(2,96,267,MEM_WHITE);
		for( i=0 ; i<P_Memory_Max ; i++) {
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				continue;

			GUI_SetBkColor(Parameter_Bottom_Bolor);

			if( i==DispCT )
				GUI_SetBkColor(Parameter_Select_Bar_Bolor);

			GUI_GotoXY(5, Memory_y_addr[i]);
			GUI_DispChars(' ',52);

			if(i==P_Memory_Type) {
				GUI_SetColor(Parameter_Font_U_Bolor);
				GUI_DispStringAt(" Data Type ", 5, Memory_y_addr[i]);
			} else {
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt(FileChan_title[p3k_File_Utility_BAR.Mem_Data_Type], 5, Memory_y_addr[i]);
			}

			GUI_SetColor(Parameter_Font_R_Bolor);

			if(i==P_Memory_Type)
				sprintf(str, " %s ", FileChan_Data[p3k_File_Utility_BAR.Mem_Data_Type]);
			else if(i==P_Memory_Number) {
				if(p3k_File_Utility_BAR.Mem_Data_Type==F_Memory_Data)
					sprintf(str," M%03d ",	p3k_File_Utility_BAR.MEMORY_ADDR+1);
				else if(p3k_File_Utility_BAR.Mem_Data_Type==F_Setup_Data)
					sprintf(str," %d ",		p3k_File_Utility_BAR.SMEMORY_ADDR+1);
				else if(p3k_File_Utility_BAR.Mem_Data_Type==F_Preset_Data)
					sprintf(str," P%d ",	p3k_File_Utility_BAR.PRE_MEMORY_ADDR);
			}

			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt(str, 260, Memory_y_addr[i]);
		}
		GUI_SetBkColor(Message_Bottom_Bolor);

		if(MEMORY_SAVE_FLAG==M_Clear_Message) {
			GUI_SetColor(Message_Font_Bolor);
			GUI_GotoXY(Disp_Start_X, 175);
			GUI_DispChars(' ',51);
			MEMORY_SAVE_FLAG = M_Nothing;
		}

		if(MEMORY_SAVE_FLAG==M_Memory_Save_Ok) {
			GUI_SetColor(Message_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			sprintf(str," Memory No %03d Save Ok ",p3k_File_Utility_BAR.MEMORY_ADDR+1);
			GUI_DispStringAt(str, Disp_Start_X, 175);
			MEMORY_SAVE_FLAG = M_Clear_Message;
		}

		if(MEMORY_SAVE_FLAG==M_Setup_Save_Ok) {
			GUI_SetColor(Message_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			sprintf(str," Setup Memory %d Save Ok ",p3k_File_Utility_BAR.SMEMORY_ADDR+1);
			GUI_DispStringAt(str, Disp_Start_X, 175);
			MEMORY_SAVE_FLAG = M_Clear_Message;
		}

		if(MEMORY_SAVE_FLAG==M_Setup_Recall_Ok) {
			GUI_SetColor(Message_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			sprintf(str," Setup Memory %d Recall Ok ",p3k_File_Utility_BAR.SMEMORY_ADDR+1);
			GUI_DispStringAt(str, Disp_Start_X, 175);
			MEMORY_SAVE_FLAG = M_Clear_Message;
		}

		if(MEMORY_SAVE_FLAG==M_Preset_Save_Ok) {
			GUI_SetColor(Message_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			sprintf(str," Preset P%d Save Ok ",p3k_File_Utility_BAR.PRE_MEMORY_ADDR);
			GUI_DispStringAt(str, Disp_Start_X, 175);
			MEMORY_SAVE_FLAG = M_Clear_Message;
		}
	} else {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN)
			sprintf(str, " %s ", KeyinBuf);
		else {
			if(DispCT==P_Memory_Type)
				sprintf(str, " %s ", FileChan_Data[p3k_File_Utility_BAR.Mem_Data_Type]);
			else if(DispCT==P_Memory_Number) {
				if(p3k_File_Utility_BAR.Mem_Data_Type==F_Memory_Data)
					sprintf(str," M%03d ",	p3k_File_Utility_BAR.MEMORY_ADDR+1);
				else if(p3k_File_Utility_BAR.Mem_Data_Type==F_Setup_Data)
					sprintf(str," %d ",		p3k_File_Utility_BAR.SMEMORY_ADDR+1);
				else if(p3k_File_Utility_BAR.Mem_Data_Type==F_Preset_Data)
					sprintf(str," P%d ",	p3k_File_Utility_BAR.PRE_MEMORY_ADDR);
			}
		}
		ShowSpace( FileChan_space[DispCT], 260, Memory_y_addr[DispCT]);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, 260, Memory_y_addr[DispCT]);
	}
}

void RedrawFileMachine(void)
{
}

void RedrawUtilityMain(void)
{
	/* Utility Main Frame */
	/* Just show Utility Function string on screen */
	GUI_SetColor(Parameter_Font_U_Bolor);
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_DispStringAt( " Utility Function ", 40, 40+0*25);
	//GUI_DispStringAt("Test...", 145, 120);
}

void RedrawInterface(void)
{
	long dat;
	char i,i_temp,str[20],DispCT_temp;

	if( DispMode == DispMode_SELECT_CH) {
		for( i=0 ; i<= 4 ; i++) {
			if((UTILITY.INTERFACE==INTERFACE_GPIB)&&(i==4))
				i_temp=1;
			else
				i_temp=i;
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i_temp != B_DispCT && i_temp != DispCT ) )
				continue;
			if((UTILITY.INTERFACE==INTERFACE_GPIB)&&(i>0)&&(i<4))
				continue;
			if((UTILITY.INTERFACE==INTERFACE_RS232)&&(i==4))
				continue;
			if((UTILITY.INTERFACE==INTERFACE_USB)&&(i>0))
				continue;
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if( i_temp == B_DispCT || i_temp == DispCT ) {
				if( i_temp == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				//GUI_GotoXY(45, Interface_addr_y[i]);
				//GUI_DispChars(' ',45);
				Draw_Bar_25(45, Interface_addr_y[i],45);
			}

			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt(Interface_title[i], 45, Interface_addr_y[i]);

			GUI_SetTextAlign(GUI_TA_RIGHT);

			dat=GetChanData(i,0);
			GUI_SetColor(Parameter_Font_R_Bolor);
			if(i==0)		GUI_DispStringAt( Interface_Kind[dat],	260, Interface_addr_y[i]);
			else if(i==1)	GUI_DispStringAt( baudrate[dat],		260, Interface_addr_y[i]);
			else if(i==2)	GUI_DispStringAt( stopbit[dat], 		260, Interface_addr_y[i]);
			else if(i==3)	GUI_DispStringAt( parity[dat], 		260, Interface_addr_y[i]);
			else {
				sprintf( str, " %02d ", dat);
				GUI_DispStringAt( str, 260, Interface_addr_y[i]);
			}
		}
	} else {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		if( (UTILITY.INTERFACE==INTERFACE_GPIB)&&(DispCT==1) )		DispCT_temp = DispCT+3;
		else													DispCT_temp = DispCT;
		ShowSpace(Interface_space[DispCT_temp], 250, Interface_addr_y[DispCT_temp] );
		dat=GetChanData(DispCT_temp, 0);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		if(DispCT_temp==0)			GUI_DispStringAt( Interface_Kind[dat],	260,Interface_addr_y[DispCT_temp]);
		else if(DispCT_temp==1)		GUI_DispStringAt( baudrate[dat],		260,Interface_addr_y[DispCT_temp]);
		else if(DispCT_temp==2)		GUI_DispStringAt( stopbit[dat],		260,Interface_addr_y[DispCT_temp]);
		else if(DispCT_temp==3)		GUI_DispStringAt( parity[dat],		260,Interface_addr_y[DispCT_temp]);
		else {
			sprintf( str, " %02d ", dat);
			GUI_DispStringAt( str, 260, Interface_addr_y[DispCT_temp]);
		}
	}
}
void RedrawDateTime(void)
{
	int i;
	char str[20];
	long dat;

	if(DispMode==DispMode_SELECT_CH) {
		GUI_SetColor(Parameter_Font_U_Bolor);
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		if(DataRedrawFlag&BG_CLEAR_FLAG)
			GUI_DispStringAt( " Date/Time ", 110, 45 );
		for( i=0 ; i<= 4 ; i++) {
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&& ( i != B_DispCT && i != DispCT ) )
				continue;
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				//GUI_GotoXY(45, 70+i*25);
				//GUI_DispChars(' ',45);
				Draw_Bar_25(45, 70+i*25,45);
			}

			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt(DateTime_title[i], 45, 70+i*25);

			GUI_SetTextAlign(GUI_TA_RIGHT);

			dat = GetChanData( i, 0);
			sprintf( str, "   %d  ", dat);
			GUI_SetColor(Parameter_Font_R_Bolor);
			GUI_DispStringAt( str, 260, 70+i*25);
		}
	} else {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		if( KeyInFlag & DIGI_KEY_IN ) {
			/* Show Keyin Data on Screen */
			sprintf( str, "   %s  " , KeyinBuf );
		} else {
			dat = GetChanData( DispCT, 0);
			sprintf( str, "   %d  ", dat);
		}
		ShowSpace( DateTime_space[DispCT], 250, 70+DispCT*25);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, 260, 70+DispCT*25);
	}
}

void RedrawUtility(void)
{
	int i,j;
	short dat;
	char str[20];

	if(DispMode==DispMode_SELECT_CH) {
		if(DataRedrawFlag&BG_CLEAR_FLAG){
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_DispStringAt( " Other Setting ", 90, 45);
		}
		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);

			if( (DispScrCurrLoc == DispScrEndCT) || (DispScrCurrLoc == DispScrStartCT) ) {
				ShowScrollBar_Other(305,70,8,5,25,10,DispScrStartCT);
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				if( i == DispScrCurrLoc)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				Draw_Bar_25(45,70+j*25,45);
			} else {
				if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != DispScrCurrLoc && i != B_DispCT ) )
					continue;

				if( i == DispScrCurrLoc || i == B_DispCT ) {
					if( i==DispScrCurrLoc)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					Draw_Bar_25(45,70+j*25,45);
				}
			}

			
			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt(utility_Other[i], 45, 70+j*25);

			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_SetColor(Parameter_Font_R_Bolor);

			switch(i) {
			case Util_Knob_Type:
				GUI_DispStringAt(knob_type[UTILITY.KEYKNOB], 260, 70+j*25);
				break;
			case Util_Speaker:
				GUI_DispStringAt(onoff_str[UTILITY.BEEP_ONOFF], 260, 70+j*25);
				break;
			case Util_Alarm_Tone:
				GUI_DispStringAt(onoff_str[UTILITY.Master_Alarm_Tone], 260, 70+j*25);
				break;
			case Util_UnReg_Tone:
				GUI_DispStringAt(onoff_str[UTILITY.UnReg_Alarm_Tone], 260, 70+j*25);
				break;
			case Util_Go_NoGO_Tone:
				GUI_DispStringAt(onoff_str[UTILITY.Master_NG_Tone], 260, 70+j*25);
				break;
			case Util_Contrast:
				dat = UTILITY.CONTRAST_LV;
				sprintf( str, "%d ", dat);
				GUI_DispStringAt( str, 260, 70+j*25);
				break;
			case Util_Brightness:
				dat = UTILITY.BRIGHTNESS_LV;
				sprintf( str, "%d ", dat);
				GUI_DispStringAt( str, 260, 70+j*25);
				break;
			case Util_Language:
				GUI_DispStringAt(display_Language[0], 260, 70+j*25);
				break;
			default:
				break;
			}
		}
	} else {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		ShowSpace(utility_Other_space[DispScrCurrLoc], 250, 70+(DispScrCurrLoc - DispScrStartCT)*25);
		GUI_SetTextAlign(GUI_TA_RIGHT);

		switch(DispScrCurrLoc) {
		case Util_Knob_Type:
			GUI_DispStringAt(knob_type[UTILITY.KEYKNOB], 260, 70+(DispScrCurrLoc - DispScrStartCT)*25);
			break;
		case Util_Speaker:
			GUI_DispStringAt(onoff_str[UTILITY.BEEP_ONOFF], 260, 70+(DispScrCurrLoc - DispScrStartCT)*25);
			break;
		case Util_Alarm_Tone:
			GUI_DispStringAt(onoff_str[UTILITY.Master_Alarm_Tone], 260, 70+(DispScrCurrLoc - DispScrStartCT)*25);
			break;
		case Util_UnReg_Tone:
			GUI_DispStringAt(onoff_str[UTILITY.UnReg_Alarm_Tone], 260, 70+(DispScrCurrLoc - DispScrStartCT)*25);
			break;
		case Util_Go_NoGO_Tone:
			GUI_DispStringAt(onoff_str[UTILITY.Master_NG_Tone], 260, 70+(DispScrCurrLoc - DispScrStartCT)*25);
			break;
		case Util_Contrast:
			dat = UTILITY.CONTRAST_LV;
			sprintf( str, "%d ", dat);
			GUI_DispStringAt( str, 260, 70+(DispScrCurrLoc - DispScrStartCT)*25);
			break;
		case Util_Brightness:
			dat = UTILITY.BRIGHTNESS_LV;
			sprintf( str, "%d ", dat);
			GUI_DispStringAt( str, 260, 70+(DispScrCurrLoc - DispScrStartCT)*25);
			break;
		case Util_Language:
			GUI_DispStringAt(display_Language[0], 260, 70+(DispScrCurrLoc - DispScrStartCT)*25);
			break;
		default:
			break;
		}
	}
}

extern UWORD PEL3000_FPGA_Date;
void RedrawSystemInfo(void)
{
	char str[20],i,j;
	char systemInfo_item[18][30];
	char systemInfo_Data[18][30];
	char model_temp[6];
	char p3k_Model_Number[20];

	Serial_Number_Str	*Serial = &P3k_Serial_Number;

	if(Serial->Version == TEXIO_Version) {
		if(MODEL3031E==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "LSG-175");
		else if(MODEL3032E==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "LSG-350");		
		else
			sprintf( p3k_Model_Number, "LSG-Default");
	} else {
		if(MODEL3031E==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "PEL-3031E");
		else if(MODEL3032E==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "PEL-3032E");		
		else
			sprintf( p3k_Model_Number, "PEL-Default");
	}

	systemInfo_count=0;

	if(DispScrCurrLoc==0)
		ClrDispCnt(0x00, 0x00, 3, 0x00, 0x00, 0x00);

	/*-------------Show Master firmware------------------*/

	sprintf( systemInfo_item[systemInfo_count],		" Model : ");
	sprintf( systemInfo_Data[systemInfo_count++],	" %s ",p3k_Model_Number);

	sprintf( systemInfo_item[systemInfo_count],  	" Serial Number : ");
	sprintf( systemInfo_Data[systemInfo_count++],	" %s ",P3k_Serial_Number.Product_Serial_Number);


	sprintf( systemInfo_item[systemInfo_count],		" Firmware Ver. : ");
	//sprintf( systemInfo_Data[systemInfo_count++],	" %d.%02d.%03d",Main_Version,Sub_Version,Machine_Number);
	sprintf( systemInfo_Data[systemInfo_count++],	" %d.%02d",Main_Version,Sub_Version);

	sprintf( systemInfo_item[systemInfo_count], 	" \n ");
	sprintf( systemInfo_item[systemInfo_count++],	" \n ");

	if(Serial->Version == TEXIO_Version)
		sprintf( systemInfo_item[systemInfo_count++], 	" http://www.texio.co.jp");
	else
		sprintf( systemInfo_item[systemInfo_count++], 	" http://www.goodwill.com.tw");


	DispScrEndCT=systemInfo_count-1;

	if((DispScrEndCT-DispScrStartCT)>5)
		DispScrEndCT=DispScrStartCT+5;

	for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
		GUI_SetBkColor(Parameter_Bottom_Bolor);

		GUI_GotoXY(Disp_Start_X,40+j*25);
		GUI_DispChars(' ',60);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt( systemInfo_item[i], 10, 40+j*25);
		GUI_SetColor(Noted_Font_Bolor);
		if(i!=DispScrEndCT)

			GUI_DispString( systemInfo_Data[i]);
	}

#if Normal_TEST
	sprintf( systemInfo_item[systemInfo_count++], 	debug_word );
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_GotoXY(Disp_Start_X,40+j*25);
	GUI_DispChars(' ',60);
	GUI_SetColor(Parameter_Font_R_Bolor);
	GUI_DispStringAt( systemInfo_item[i], 45, 40+j*25);
#endif

}

void RedrawSystemMemo(void)
{
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_GotoXY(Disp_Start_X,40);
	GUI_DispChars(' ',60);
	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_DispStringAt( " System Memo ", 10, 40);
}

void RedrawFuncPower(void)
{
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);
	GUI_SetTextAlign(GUI_TA_LEFT);
	GUI_DispStringAt( " Power Analysis ", 105, 30);
	Displine(2,65,316,MEM_GRAY);
	Displine(2,66,316,GW_ORANGE_ku);
	Displine(2,67,316,MEM_WHITE);
}

void RedrawPassword(void)
{
	char str[6];
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_SetTextAlign(GUI_TA_LEFT);
	GUI_DispStringAt(" Please Input Password : ", 46, 90);
	sprintf( str, " %s " , KeyinBuf );
	GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
	GUI_SetColor(Parameter_Select_Font_Bolor);
	ShowSpace_LEFT( 5, 127, 115);
	GUI_SetTextAlign(GUI_TA_LEFT);
	GUI_DispStringAt(str, 130, 115);

	if(Save_Recall_InfoFlag&Data_Process) { /*Show Message*/
		GUI_SetBkColor(Message_Bottom_Bolor);
		GUI_GotoXY(Disp_Start_X, 175);
		GUI_DispChars(' ',51);
		GUI_SetColor(Message_Font_Bolor);
		GUI_SetTextAlign(GUI_TA_LEFT);
		if(Save_Recall_InfoFlag&password_error) {
			Save_Recall_InfoFlag&=~password_error;
			GUI_DispStringAt(" Password Error ", Disp_Start_X, 175);
		} else
			Save_Recall_InfoFlag &= ~Data_Process;
	}
}
extern unsigned char debugmode;
#if 1
void RedrawTestFunction(void)
{
	int i;
	char tmp,tmp1,tmp2,str[20],str1[20];
	unsigned char y_data;
	y_data = Disp_Start_Y2 + Disp_Interval;
	if(debugmode==0) {
		if( DispMode <= DispMode_BROWSE_ITEMS) {

			FPGASetting =FPGA_W[RecordCMD];
			FPGAStatus = FPGA_R[RecordCMD];
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			//GUI_SetColor(MEM_DARKGREEN_ku);
			//GUI_DispStringAt( "FPGA_Register",	Disp_Start_X, Disp_Start_Y2 );
			//GUI_SetColor(MEM_DARKGREEN_ku);
			GUI_SetColor(Parameter_Font_R_Bolor);
			GUI_DispStringAt( "FPGA_Register",	Disp_Start_X, Disp_Start_Y2 );
#if 1
			sprintf( str1, "Ver:%04d",PEL3000_FPGA_Date);
			GUI_DispStringAt( str1,	Disp_Start_X+150, Disp_Start_Y2 );

#endif
			for( i=0 ; i<test_mode_end; i++) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				if(DispMode != DispMode_SELECT_CH && ( i == B_DispCT || i == DispCT ) ) {
					if( i == DispCT)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					GUI_GotoXY(	Disp_Start_X, y_data+ i*Disp_Interval);
					GUI_DispChars(' ', HiLight_Length+20);
				}
				GUI_SetColor(Parameter_Font_L_Bolor);
				if(i>=DispMode_ReadRecord)
					GUI_SetColor(Parameter_Font_U_Bolor);
				if(i==DispMode_SELECT_CH)
					GUI_DispStringAt( "Action",	Disp_Start_X, y_data+i*Disp_Interval );
				else if(i==DispMode_BROWSE_ITEMS)
					GUI_DispStringAt( "CMD",	Disp_Start_X, y_data+i*Disp_Interval );
				else if(i==DispMode_SET_PARAMETERS)
					GUI_DispStringAt( "DATA",	Disp_Start_X, y_data+i*Disp_Interval );
				else if(i==DispMode_ReadRecord)
					GUI_DispStringAt( "RecordCMD",	Disp_Start_X, y_data+i*Disp_Interval );
				else if(i==DispMode_dis_fpga_setting)
					GUI_DispStringAt( "fpgaSetting",	Disp_Start_X, y_data+i*Disp_Interval );
				else if(i==DispMode_dis_fpga_status)
					GUI_DispStringAt( "fpgaStatus",	Disp_Start_X, y_data+i*Disp_Interval );

				GUI_SetColor(Parameter_Font_R_Bolor);
				/* Get Resolution ,Max, Min */
				ShowSpace( 7, Para_Start_X+30, y_data+i*Disp_Interval);
				if(i==DispMode_SELECT_CH) {
					if(P3K_CMD_R_W)	sprintf( str, " Write ");
					else			sprintf( str, " Read ");
				} else if(i==DispMode_BROWSE_ITEMS) {
					sprintf( str, " %03d ",P3K_CMD);
					sprintf( str1, " %02X ",P3K_CMD);
				} else if(i==DispMode_SET_PARAMETERS) {
					sprintf( str, " %05d ",P3K_DATA);
					sprintf( str1, " %04X ",P3K_DATA);
				} else if(i==DispMode_ReadRecord) {
					sprintf( str, " %03d ",RecordCMD);
					sprintf( str1, "%02X ",RecordCMD);
				} else if(i==DispMode_dis_fpga_setting) {
					sprintf( str, " %05d ",FPGASetting);
					sprintf( str1, " %04X ",FPGASetting);
				} else if(i==DispMode_dis_fpga_status) {
					sprintf( str, " %05d ",FPGAStatus);
					sprintf( str1, " %04X ",FPGAStatus);
				}

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X+30, y_data+i*Disp_Interval);
				if(i!=DispMode_SELECT_CH) {
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str1, Para_Start_X+110, y_data+i*Disp_Interval);
				}
			}
		} else if(DispMode == DispMode_SET_PARAMETERS ) {
			GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
			GUI_SetColor(Parameter_Select_Font_Bolor);

			if( KeyInFlag & DIGI_KEY_IN ) {
				sprintf( str, " %s " , KeyinBuf );
			} else {
				/* Show Memory Data on Screen */
				if(DispCT==DispMode_SELECT_CH) {
					if(P3K_CMD_R_W)	sprintf( str, " Write ");
					else			sprintf( str, " Read ");
				} else if(DispCT==DispMode_BROWSE_ITEMS) {
					sprintf( str, " %03d ",P3K_CMD);
					sprintf( str1, " %02X ",P3K_CMD);
				} else if(DispCT==DispMode_SET_PARAMETERS) {
					sprintf( str, " %05d ",P3K_DATA);
					sprintf( str1, " %04X ",P3K_DATA);
				} else if(DispCT==DispMode_ReadRecord) {
					sprintf( str, " %03d ",RecordCMD);
					sprintf( str1, " %02X ",RecordCMD);
				}
			}
			ShowSpace( 7, Para_Start_X+30, y_data+DispCT*Disp_Interval);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X+30, y_data+DispCT*Disp_Interval);
			if(DispCT!=DispMode_SELECT_CH) {
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str1, Para_Start_X+110, y_data+DispCT*Disp_Interval);
			}
			if(DispCT==DispMode_ReadRecord) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				GUI_SetColor(Parameter_Font_R_Bolor);
				sprintf( str, " %05d ",FPGASetting);
				sprintf( str1, " %04X ",FPGASetting);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X+30, y_data+4*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str1, Para_Start_X+110, y_data+4*Disp_Interval);
				sprintf( str, " %05d ",FPGAStatus);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X+30, y_data+5*Disp_Interval);
				sprintf( str, " %04X ",FPGAStatus);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X+110, y_data+5*Disp_Interval);
			}
		}
		// slect Download
	} else if(debugmode==1){
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(MEM_DARKGREEN_ku);
		GUI_DispStringAt( "Download",	Disp_Start_X, Disp_Start_Y2 );
		GUI_SetColor(Parameter_Font_R_Bolor);
		for( i=0 ; i<DownModeEnd; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(DispMode != DispMode_SELECT_CH && ( i == B_DispCT || i == DispCT ) ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(	Disp_Start_X, y_data+ i*Disp_Interval);
				GUI_DispChars(' ', HiLight_Length+20);
			}
			GUI_SetColor(Parameter_Font_L_Bolor);

			if(i==MeasureMode)
				GUI_DispStringAt( "Catch Measure",	Disp_Start_X, y_data+i*Disp_Interval );
			else if(i==CalTxtMode)
				GUI_DispStringAt( "Calibration(excle)",	Disp_Start_X, y_data+i*Disp_Interval );
			else if(i==CalBackup)
				GUI_DispStringAt( "Calibation(backup)",	Disp_Start_X, y_data+i*Disp_Interval );
			else if(i==printScreen)
				GUI_DispStringAt( "Print Screen(bmp)",	Disp_Start_X, y_data+i*Disp_Interval );
			else if(i==RunningRecord)
				GUI_DispStringAt( "RunningRecord(excel)",	Disp_Start_X, y_data+i*Disp_Interval );
		}
	}
#if debug_tool
	else if(debugmode==2){
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(MEM_DARKGREEN_ku);
		GUI_DispStringAt( "FPGA test",	Disp_Start_X, Disp_Start_Y2 );
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_DispStringAt( "Run times:",	Disp_Start_X, 2*Disp_Interval );
		GUI_DispStringAt( "Error times:",	Disp_Start_X, 3*Disp_Interval );
		
		GUI_SetColor(Parameter_Font_R_Bolor);
		sprintf( str1, "%d",FPGA_test_cnt);
		GUI_DispStringAt( str1,	Disp_Start_X+150, 2*Disp_Start_Y2 );
		sprintf( str1, "%d",FPGA_err_cnt);
		GUI_DispStringAt( str1,	Disp_Start_X+150, 3*Disp_Start_Y2 );
	}
#endif
}

#else
void RedrawTestFunction(void)
{
	int i;
	char tmp,tmp1,tmp2,str[20];
	char str1[50];
	sprintf(str1," ");
	if( DispMode <= DispMode_BROWSE_ITEMS) {
		FPGASetting =FPGA_W[RecordCMD];
		FPGAStatus = FPGA_R[RecordCMD];
		for( i=0 ; i<test_mode_end; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(DispMode != DispMode_SELECT_CH&&( i == B_DispCT || i == DispCT )) {
				if(i==DispCT)		GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(	Disp_Start_X, Disp_Start_Y2+ i*Disp_Interval);
				GUI_DispChars(' ', HiLight_Length+10);
			}
			GUI_SetColor(Parameter_Font_L_Bolor);
			if(i>=DispMode_ReadRecord)		GUI_SetColor(Parameter_Font_U_Bolor);
			if(i==DispMode_SELECT_CH)
				GUI_DispStringAt( "Action",	Disp_Start_X, Disp_Start_Y2+i*Disp_Interval );
			else if(i==DispMode_BROWSE_ITEMS)
				GUI_DispStringAt( "CMD",	Disp_Start_X, Disp_Start_Y2+i*Disp_Interval );
			else if(i==DispMode_SET_PARAMETERS)
				GUI_DispStringAt( "DATA",	Disp_Start_X, Disp_Start_Y2+i*Disp_Interval );
			else if(i==DispMode_ReadRecord)
				GUI_DispStringAt( "RecordCMD",	Disp_Start_X, Disp_Start_Y2+i*Disp_Interval );
			else if(i==DispMode_dis_fpga_setting)
				GUI_DispStringAt( "fpgaSetting",	Disp_Start_X, Disp_Start_Y2+i*Disp_Interval );
			else if(i==DispMode_dis_fpga_status)
				GUI_DispStringAt( "fpgaStatus",	Disp_Start_X, Disp_Start_Y2+i*Disp_Interval );
			GUI_SetColor(Parameter_Font_R_Bolor);
			ShowSpace( 7, Para_Start_X+50, Disp_Start_Y2+i*Disp_Interval);
			if(i==DispMode_SELECT_CH) {
				if(P3K_CMD_R_W)	sprintf( str, " Write ");
				else			sprintf( str, " Read ");
			} else if(i==DispMode_BROWSE_ITEMS) {
				sprintf( str, " %03d ",P3K_CMD);
				sprintf( str1, " 0x%02X ",P3K_CMD);
			} else if(i==DispMode_SET_PARAMETERS) {
				sprintf( str, " %05d ",P3K_DATA);
				sprintf( str1, " 0x%04X ",P3K_DATA);
			} else if(i==DispMode_ReadRecord) {
				sprintf( str, " %03d ",RecordCMD);
				sprintf( str1, " 0x%02X ",RecordCMD);
			} else if(i==DispMode_dis_fpga_setting) {
				sprintf( str, " %05d ",FPGASetting);
				sprintf( str1, " 0x%04X ",FPGASetting);
			} else if(i==DispMode_dis_fpga_status) {
				sprintf( str, " %05d ",FPGAStatus);
				sprintf( str1, " 0x%04X ",FPGAStatus);
			}
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X+5, Disp_Start_Y2+i*Disp_Interval);
			GUI_SetColor(MEM_DARKGRAY);
			GUI_DispStringAt( str1, Para_Start_X+30, Disp_Start_Y2+i*Disp_Interval);
		}
	} else if(DispMode == DispMode_SET_PARAMETERS ) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		if(KeyInFlag & DIGI_KEY_IN) {
			sprintf( str, " %s " , KeyinBuf );
		} else {
			if(DispCT==DispMode_SELECT_CH) {
				if(P3K_CMD_R_W)	sprintf( str, " Write ");
				else			sprintf( str, " Read ");
			} else if(DispCT==DispMode_BROWSE_ITEMS) {
				sprintf( str, " %03d ",P3K_CMD);
				sprintf( str1, " 0x%02X ",P3K_CMD);
			} else if(DispCT==DispMode_SET_PARAMETERS) {
				sprintf( str, " %05d ",P3K_DATA);
				sprintf( str1, " 0x%04X ",P3K_DATA);
			} else if(DispCT==DispMode_ReadRecord) {
				sprintf( str, " %03d ",RecordCMD);
				sprintf( str1, " 0x%02X ",RecordCMD);
			}
		}
		ShowSpace( 7, Para_Start_X+5, Disp_Start_Y2+DispCT*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X+5, Disp_Start_Y2+DispCT*Disp_Interval);
		GUI_DispStringAt( str1, Para_Start_X+30, Disp_Start_Y2+DispCT*Disp_Interval);
		if(DispCT==DispMode_ReadRecord) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(Parameter_Font_R_Bolor);
			sprintf( str, " %05d ",FPGASetting);
			sprintf( str1, " 0x%04X ",FPGASetting);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X+5, Disp_Start_Y2+4*Disp_Interval);
			GUI_DispStringAt( str1, Para_Start_X+30, Disp_Start_Y2+4*Disp_Interval);
			sprintf( str, " %05d ",FPGAStatus);
			sprintf( str1, " 0x%04X ",FPGAStatus);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X+5, Disp_Start_Y2+5*Disp_Interval);
			GUI_DispStringAt( str1, Para_Start_X+30, Disp_Start_Y2+5*Disp_Interval);
		}
	}
}
#endif
void RedrawCalValue(void)
{
#define Disp_Interval1		17
#define Disp_Start_Y2_1		50
	static const char cal_title_1[9][12] = { "OFFSET:","Off_CCH","Off_CCL","Off_CRH","Off_CRL","Off_CPH","Off_CPL","Off_CVH","Off_CVL"};
	static const char cal_title_1_2[5][12] = { "OFFSET:","Off_ExtVH","Off_ExtVL","Off_ExtRH","Off_ExtRL"};
	static const char cal_title_2[9][12] = { "SETTING:","CCH","CCL","CRH","CRL","CVH","CVL","CPH","CPL"};
#if 1
	static const char cal_title_3[7][12] = { "SETTING:","IMON_H","IMON_L","EXT_VH_CC","EXT_VL_CC","EXT_RH_CC","EXT_RL_CC"};
	static const char cal_title_4[9][12] = { "SETTING:","EXT_VH_CR","EXT_VL_CR","EXT_RH_CR","EXT_RL_CR","EXT_VH_CV","EXT_VL_CV","EXT_RH_CV","EXT_RL_CV"};
	static const char cal_title_5[5][12] = { "SETTING:","EXT_VH_CP","EXT_VL_CP","EXT_RH_CP","EXT_RL_CP"};

	static const char cal_title_6[7][12] = { "MEASURE:","M_Volt_H","M_Volt_L","M_Curr_H","M_Curr_L","EXT_SonserV","EXT_SonserR"};
	static const char cal_title_7[9][12] = { "MEASURE:","M_VH_ExtV","M_VL_ExtV","M_VH_ExtR","M_VL_ExtR","M_IH_ExtV","M_IL_ExtV","M_IH_ExtR","M_IL_ExtR"};
	static const char cal_title_8[7][12] = { "PROTECION:","OCP","OCP_Cal_H","OCP_Cal_L","OPP","OPP_Cal_H","OPP_Cal_L"};
	static const char cal_title_9[6][12] = { "PROTECION:","CCP","CCP_Cal_H","CCP_Cal_L","CXCV_CAL_H","CXCV_CAL_L"};
	static const char cal_title_10[7][12] = { "PSENSOR:","XH","YH","ZH","XL","YL","ZL"};
#else
	static const char cal_title_3[7][12] = { "SETTING:","IMON_H","IMON_L","EXT_VH","EXT_VL","EXT_RH","EXT_RL"};
	static const char cal_title_4[7][12] = { "MEASURE:","M_Volt_H","M_Volt_L","M_Curr_H","M_Curr_L","EXT_SonserV","EXT_SonserR"};
	static const char cal_title_5[9][12] = { "MEASURE:","M_VH_ExtV","M_VL_ExtV","M_VH_ExtR","M_VL_ExtR","M_IH_ExtV","M_IL_ExtV","M_IH_ExtR","M_IL_ExtR"};
	static const char cal_title_6[7][12] = { "PROTECION:","OCP","OCP_Cal_H","OCP_Cal_L","OPP","OPP_Cal_H","OPP_Cal_L"};
	static const char cal_title_7[6][12] = { "PROTECION:","CCP","CCP_Cal_H","CCP_Cal_L","CXCV_CAL_H","CXCV_CAL_L"};
	static const char cal_title_8[7][12] = { "PSENSOR:","XH","YH","ZH","XL","YL","ZL"};
#endif
	int i;
	char str[30],str1[30];


	if( DispMode <= DispMode_BROWSE_ITEMS) {

		GUI_SetFont(Right_Font);
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_R_Bolor);
		sprintf( str, "page:%02d",(DispCT+1));
		GUI_DispStringAt( str, 5, 25);
		for( i=0 ; i<9; i++) {
			GUI_GotoXY(	Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1);
			GUI_DispChars(' ', 85);
		}
		switch(DispCT) {
		case 0:
			for( i=0 ; i<9; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_1[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " Value ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.CC_offseAdj[1]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.CC_offseAdj[0]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.CR_offseAdj[1]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.CR_offseAdj[0]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==5) {
					sprintf( str, "%d" , p3k_Cal_data.CP_offseAdj[1]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==6) {
					sprintf( str, "%d" , p3k_Cal_data.CP_offseAdj[0]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==7) {
					sprintf( str, "%d" , p3k_Cal_data.CV_offseAdj[1]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==8) {
					sprintf( str, "%d" , p3k_Cal_data.CV_offseAdj[0]);	//sprintf( str1, " %05d ",FPGASetting);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				//GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
		case 1:
			for( i=0 ; i<5; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_1_2[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " Value ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_offseAdj[1]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_offseAdj[0]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_offseAdj[1]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_offseAdj[0]);	//sprintf( str1, " %05d ",FPGASetting);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				//GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
		case 2:
			for( i=0 ; i<9; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_2[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%1.4f" , p3k_Cal_data.CC_Data[1].Cal_Value_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.CC_Data[1].Cal_Value_Offset);
				} else if(i==2) {
					sprintf( str, "%1.4f" , p3k_Cal_data.CC_Data[0].Cal_Value_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.CC_Data[0].Cal_Value_Offset);
				} else if(i==3) {
					sprintf( str, "%1.4f" , p3k_Cal_data.CR_Data[1].Cal_Value_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.CR_Data[1].Cal_Value_Offset);
				} else if(i==4) {
					sprintf( str, "%1.4f" , p3k_Cal_data.CR_Data[0].Cal_Value_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.CR_Data[0].Cal_Value_Offset);
				} else if(i==5) {
					sprintf( str, "%1.4f" , p3k_Cal_data.CV_Data[1].Cal_Value_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.CV_Data[1].Cal_Value_Offset);
				} else if(i==6) {
					sprintf( str, "%1.4f" , p3k_Cal_data.CV_Data[0].Cal_Value_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.CV_Data[0].Cal_Value_Offset);
				} else if(i==7) {
					sprintf( str, "%1.4f" , p3k_Cal_data.CP_Data[1].Cal_Value_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.CP_Data[1].Cal_Value_Offset);
				} else if(i==8) {
					//p3k_Cal_data.CP_Data[0].Cal_Value_Gain = 1;
					sprintf( str, "%f" , p3k_Cal_data.CP_Data[0].Cal_Value_Gain);
					sprintf( str1, "%f" , p3k_Cal_data.CP_Data[0].Cal_Value_Offset);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
#if 1
		case 3:
			for( i=0 ; i<7; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_3[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");			//sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Rear_IMON[1]);	//sprintf( str1, "%f" , p3k_Cal_data.CC_Data[1].Cal_Value_Offset);
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.Rear_IMON[0]);	//sprintf( str1, "%f" , p3k_Cal_data.CC_Data[0].Cal_Value_Offset);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_CC[1]);	//sprintf( str1, "%f" , p3k_Cal_data.CR_Data[1].Cal_Value_Offset);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_CC[0]);	//sprintf( str1, "%f" , p3k_Cal_data.CR_Data[0].Cal_Value_Offset);
				} else if(i==5) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_CC[1]);	//sprintf( str1, "%f" , p3k_Cal_data.CV_Data[1].Cal_Value_Offset);
				} else if(i==6) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_CC[0]);	//sprintf( str1, "%f" , p3k_Cal_data.CV_Data[0].Cal_Value_Offset);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				//GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
		case 4:
			for( i=0 ; i<9; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_4[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");			//sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_CR[1]);	//sprintf( str1, "%f" , p3k_Cal_data.CR_Data[1].Cal_Value_Offset);
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_CR[0]);	//sprintf( str1, "%f" , p3k_Cal_data.CR_Data[0].Cal_Value_Offset);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_CR[1]);	//sprintf( str1, "%f" , p3k_Cal_data.CV_Data[1].Cal_Value_Offset);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_CR[0]);	//sprintf( str1, "%f" , p3k_Cal_data.CV_Data[0].Cal_Value_Offset);
				} else if(i==5) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_CV[1]); //sprintf( str1, "%f" , p3k_Cal_data.CR_Data[1].Cal_Value_Offset);
				} else if(i==6) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_CV[0]); //sprintf( str1, "%f" , p3k_Cal_data.CR_Data[0].Cal_Value_Offset);
				} else if(i==7) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_CV[1]); //sprintf( str1, "%f" , p3k_Cal_data.CV_Data[1].Cal_Value_Offset);
				} else if(i==8) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_CV[0]); //sprintf( str1, "%f" , p3k_Cal_data.CV_Data[0].Cal_Value_Offset);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				//GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;	
		case 5:
			for( i=0 ; i<5; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_5[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");			//sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_CP[1]);	//sprintf( str1, "%f" , p3k_Cal_data.CR_Data[1].Cal_Value_Offset);
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_CP[0]);	//sprintf( str1, "%f" , p3k_Cal_data.CR_Data[0].Cal_Value_Offset);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_CP[1]);	//sprintf( str1, "%f" , p3k_Cal_data.CV_Data[1].Cal_Value_Offset);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_CP[0]);	//sprintf( str1, "%f" , p3k_Cal_data.CV_Data[0].Cal_Value_Offset);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				//GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;				
		case 6: //MEASURE
			for( i=0 ; i<7; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_6[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");
					sprintf( str1, " OFFSET ");	//p3k_Cal_data.Volt[1].Meas_Value_Gain*p3k_Cal_data.Volt[1].Meas_Value_Offset/65535.0)
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Volt[1].Meas_Value_Gain);
					sprintf( str1, "%d" , ((p3k_Cal_data.Volt[1].Meas_Value_Gain*p3k_Cal_data.Volt[1].Meas_Value_Offset)>>16));
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.Volt[0].Meas_Value_Gain);
					sprintf( str1, "%d" , (p3k_Cal_data.Volt[0].Meas_Value_Gain*p3k_Cal_data.Volt[0].Meas_Value_Offset)>>16);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.Curr[1].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Curr[1].Meas_Value_Gain*p3k_Cal_data.Curr[1].Meas_Value_Offset>>16);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.Curr[0].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Curr[0].Meas_Value_Gain*p3k_Cal_data.Curr[0].Meas_Value_Offset>>16);
				} else if(i==5) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_Sense.Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_V_Sense.Meas_Value_Gain*p3k_Cal_data.Ext_V_Sense.Meas_Value_Offset>>16);
				} else if(i==6) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_Sense.Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_R_Sense.Meas_Value_Gain*p3k_Cal_data.Ext_R_Sense.Meas_Value_Offset>>16);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;

		case 7: //MEASURE
			for( i=0 ; i<9; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_7[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_Volt[1].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_V_Volt[1].Meas_Value_Gain*p3k_Cal_data.Ext_V_Volt[1].Meas_Value_Offset>>16);
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_Volt[0].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_V_Volt[0].Meas_Value_Gain*p3k_Cal_data.Ext_V_Volt[0].Meas_Value_Offset>>16);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_Volt[1].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_R_Volt[1].Meas_Value_Gain*p3k_Cal_data.Ext_R_Volt[1].Meas_Value_Offset>>16);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_Volt[0].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_R_Volt[0].Meas_Value_Gain*p3k_Cal_data.Ext_R_Volt[0].Meas_Value_Offset>>16);
				} else if(i==5) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_Curr[1].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_V_Curr[1].Meas_Value_Gain*p3k_Cal_data.Ext_V_Curr[1].Meas_Value_Offset>>16);
				} else if(i==6) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_Curr[0].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_V_Curr[0].Meas_Value_Gain*p3k_Cal_data.Ext_V_Curr[0].Meas_Value_Offset>>16);
				} else if(i==7) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_Curr[1].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_R_Curr[1].Meas_Value_Gain*p3k_Cal_data.Ext_R_Curr[1].Meas_Value_Offset>>16);
				} else {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_Curr[0].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_R_Curr[0].Meas_Value_Gain*p3k_Cal_data.Ext_R_Curr[0].Meas_Value_Offset>>16);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;

		case 8: //PROCTION_1
			for( i=0 ; i<7; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_8[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Protection[1].OCP);
					sprintf( str1, " " );
				} else if(i==2) {
					sprintf( str, "%1.4f" , p3k_Cal_data.Protection[1].OCP_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.Protection[1].OCP_Offset);
				} else if(i==3) {
					sprintf( str, "%1.4f" , p3k_Cal_data.Protection[0].OCP_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.Protection[0].OCP_Offset);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.Protection[1].OPP);
					sprintf( str1, "  " );
				} else if(i==5) {
					sprintf( str, "%1.4f" , p3k_Cal_data.Protection[1].OPP_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.Protection[1].OPP_Offset);
				} else if(i==6) {
					sprintf( str, "%1.4f" , p3k_Cal_data.Protection[0].OPP_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.Protection[0].OPP_Offset);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
		case 9: //PROCTION_2
			for( i=0 ; i<6; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_9[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Protection[1].CPP);
					sprintf( str1, "  ");
				} else if(i==2) {
					sprintf( str, "%1.4f" , p3k_Cal_data.Protection[1].CPP_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.Protection[1].CPP_Offset);
				} else if(i==3) {
					sprintf( str, "%1.4f" , p3k_Cal_data.Protection[0].CPP_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.Protection[0].CPP_Offset);
				} else if(i==4) {
					sprintf( str, "%1.4f" , p3k_Cal_data.Protection[1].CxCV_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.Protection[1].CxCV_Offset);
				} else if(i==5) {
					sprintf( str, "%1.4f" , p3k_Cal_data.Protection[0].CxCV_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.Protection[0].CxCV_Offset);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
		case 10: //PSENSOR
			for( i=0 ; i<7; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_10[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.XH_Value);
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.YH_Value);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.ZH_Value);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.XL_Value);
				} else if(i==5) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.YL_Value);
				} else if(i==6) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.ZL_Value);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				//GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
#else
		case 3:
			for( i=0 ; i<7; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_3[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");			//sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Rear_IMON[1]);	//sprintf( str1, "%f" , p3k_Cal_data.CC_Data[1].Cal_Value_Offset);
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.Rear_IMON[0]);	//sprintf( str1, "%f" , p3k_Cal_data.CC_Data[0].Cal_Value_Offset);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_CC[1]);	//sprintf( str1, "%f" , p3k_Cal_data.CR_Data[1].Cal_Value_Offset);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_CC[0]);	//sprintf( str1, "%f" , p3k_Cal_data.CR_Data[0].Cal_Value_Offset);
				} else if(i==5) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_CC[1]);	//sprintf( str1, "%f" , p3k_Cal_data.CV_Data[1].Cal_Value_Offset);
				} else if(i==6) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_CC[0]);	//sprintf( str1, "%f" , p3k_Cal_data.CV_Data[0].Cal_Value_Offset);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				//GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
		case 4: //MEASURE
			for( i=0 ; i<7; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_4[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");
					sprintf( str1, " OFFSET ");	//p3k_Cal_data.Volt[1].Meas_Value_Gain*p3k_Cal_data.Volt[1].Meas_Value_Offset/65535.0)
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Volt[1].Meas_Value_Gain);
					sprintf( str1, "%d" , ((p3k_Cal_data.Volt[1].Meas_Value_Gain*p3k_Cal_data.Volt[1].Meas_Value_Offset)>>16));
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.Volt[0].Meas_Value_Gain);
					sprintf( str1, "%d" , (p3k_Cal_data.Volt[0].Meas_Value_Gain*p3k_Cal_data.Volt[0].Meas_Value_Offset)>>16);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.Curr[1].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Curr[1].Meas_Value_Gain*p3k_Cal_data.Curr[1].Meas_Value_Offset>>16);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.Curr[0].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Curr[0].Meas_Value_Gain*p3k_Cal_data.Curr[0].Meas_Value_Offset>>16);
				} else if(i==5) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_Sense.Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_V_Sense.Meas_Value_Gain*p3k_Cal_data.Ext_V_Sense.Meas_Value_Offset>>16);
				} else if(i==6) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_Sense.Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_R_Sense.Meas_Value_Gain*p3k_Cal_data.Ext_R_Sense.Meas_Value_Offset>>16);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;

		case 5: //MEASURE
			for( i=0 ; i<9; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_5[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_Volt[1].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_V_Volt[1].Meas_Value_Gain*p3k_Cal_data.Ext_V_Volt[1].Meas_Value_Offset>>16);
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_Volt[0].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_V_Volt[0].Meas_Value_Gain*p3k_Cal_data.Ext_V_Volt[0].Meas_Value_Offset>>16);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_Volt[1].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_R_Volt[1].Meas_Value_Gain*p3k_Cal_data.Ext_R_Volt[1].Meas_Value_Offset>>16);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_Volt[0].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_R_Volt[0].Meas_Value_Gain*p3k_Cal_data.Ext_R_Volt[0].Meas_Value_Offset>>16);
				} else if(i==5) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_Curr[1].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_V_Curr[1].Meas_Value_Gain*p3k_Cal_data.Ext_V_Curr[1].Meas_Value_Offset>>16);
				} else if(i==6) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_Curr[0].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_V_Curr[0].Meas_Value_Gain*p3k_Cal_data.Ext_V_Curr[0].Meas_Value_Offset>>16);
				} else if(i==7) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_Curr[1].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_R_Curr[1].Meas_Value_Gain*p3k_Cal_data.Ext_R_Curr[1].Meas_Value_Offset>>16);
				} else {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_Curr[0].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_R_Curr[0].Meas_Value_Gain*p3k_Cal_data.Ext_R_Curr[0].Meas_Value_Offset>>16);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;

		case 6: //PROCTION_1
			for( i=0 ; i<7; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_6[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Protection[1].OCP);
					sprintf( str1, " " );
				} else if(i==2) {
					sprintf( str, "%1.4f" , p3k_Cal_data.Protection[1].OCP_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.Protection[1].OCP_Offset);
				} else if(i==3) {
					sprintf( str, "%1.4f" , p3k_Cal_data.Protection[0].OCP_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.Protection[0].OCP_Offset);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.Protection[1].OPP);
					sprintf( str1, "  " );
				} else if(i==5) {
					sprintf( str, "%1.4f" , p3k_Cal_data.Protection[1].OPP_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.Protection[1].OPP_Offset);
				} else if(i==6) {
					sprintf( str, "%1.4f" , p3k_Cal_data.Protection[0].OPP_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.Protection[0].OPP_Offset);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
		case 7: //PROCTION_2
			for( i=0 ; i<6; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_7[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Protection[1].CPP);
					sprintf( str1, "  ");
				} else if(i==2) {
					sprintf( str, "%1.4f" , p3k_Cal_data.Protection[1].CPP_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.Protection[1].CPP_Offset);
				} else if(i==3) {
					sprintf( str, "%1.4f" , p3k_Cal_data.Protection[0].CPP_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.Protection[0].CPP_Offset);
				} else if(i==4) {
					sprintf( str, "%1.4f" , p3k_Cal_data.Protection[1].CxCV_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.Protection[1].CxCV_Offset);
				} else if(i==5) {
					sprintf( str, "%1.4f" , p3k_Cal_data.Protection[0].CxCV_Gain);
					sprintf( str1, "%1.4f" , p3k_Cal_data.Protection[0].CxCV_Offset);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
		case 8: //PSENSOR
			for( i=0 ; i<7; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_8[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.XH_Value);
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.YH_Value);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.ZH_Value);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.XL_Value);
				} else if(i==5) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.YL_Value);
				} else if(i==6) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.ZL_Value);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				//GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
#endif			
		default:
			break;
		}
	}
}


#if Enable_AutoLoad
void RedrawAutoLoad(void)
{
	int i;

	if(DispMode==DispMode_SELECT_CH) {
		if(DataRedrawFlag&BG_CLEAR_FLAG){
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_DispStringAt( " Load Setting For Power On", 40, 45);
		}
		DispScrCurrLoc = DispCT;
#if Enable_Short_invalidate
		for( i=0 ; i<= 3 ; i++) 
#else
		for( i=0 ; i<= 4 ; i++) 
#endif		
		{
			GUI_SetBkColor(Parameter_Bottom_Bolor);
#if 0			
			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(45, 70+i*25);
				GUI_DispChars(' ',45);
			}
#else		
			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT){
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					if((DataRedrawFlag&BG_CLEAR_FLAG)==0){
						Draw_New_Bar_25(45, 70+i*25,45,1);
						continue;
					}
				}else{
					if((DataRedrawFlag&BG_CLEAR_FLAG)==0){
						Draw_New_Bar_25(45, 70+i*25,45,0);
						continue;
					}
				}
				if(DataRedrawFlag&BG_CLEAR_FLAG){
					Draw_Bar_25(45, 70+i*25,45);
				}	
			}


#endif			
			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt(AutoLoad_title[i], 50, 70+i*25);

			ShowSpace(AutoLoad_space[i], 260, 70+i*25);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_SetColor(Parameter_Font_R_Bolor);
			if(i==0)	 GUI_DispStringAt(onoff_str[UTILITY.ALOAD], 260, 70+i*25);
			else if(i==1)GUI_DispStringAt(AutoLoad_mode[UTILITY.ALOAD_MODE], 260, 70+i*25);
			else if(i==2)GUI_DispStringAt(onoff_str[UTILITY.AutoLoadOffMode], 260, 70+i*25);
			else if(i==3)GUI_DispStringAt(onoff_str[UTILITY.AutoLoadOffRange], 260, 70+i*25);
#if Enable_Short_invalidate==0
			else		GUI_DispStringAt(onoff_str[UTILITY.ShortonLoadoff], 260, 70+i*25);
#endif			
		}
	} else {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		ShowSpace(AutoLoad_space[DispCT], 250, 70+DispCT*25);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		if(DispCT==0)
			GUI_DispStringAt(onoff_str[UTILITY.ALOAD], 260, 70+DispCT*25);
		else if(DispCT==1)
			GUI_DispStringAt(AutoLoad_mode[UTILITY.ALOAD_MODE], 260, 70+DispCT*25);
		else if(DispCT==2)
			GUI_DispStringAt(onoff_str[UTILITY.AutoLoadOffMode], 260, 70+DispCT*25);
		else if(DispCT==3)
			GUI_DispStringAt(onoff_str[UTILITY.AutoLoadOffRange], 260, 70+DispCT*25);
#if Enable_Short_invalidate==0
		else
			GUI_DispStringAt(onoff_str[UTILITY.ShortonLoadoff], 260, 70+DispCT*25);
#endif		
	}
}
#else
void RedrawAutoLoad(void)
{
	int i;

	if(DispMode==DispMode_SELECT_CH) {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_U_Bolor);
		GUI_DispStringAt( " Load Setting For Power On", 40, 45);
		for( i=0 ; i<= 1 ; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(45, 70+i*25);
				GUI_DispChars(' ',45);
			}
			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt(AutoLoad_title[i], 50, 70+i*25);

			ShowSpace(AutoLoad_space[i], 260, 70+i*25);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_SetColor(Parameter_Font_R_Bolor);
			if(i==0)	GUI_DispStringAt(onoff_str[UTILITY.ALOAD], 260, 70+i*25);
			else		GUI_DispStringAt(AutoLoad_mode[UTILITY.ALOAD_MODE], 260, 70+i*25);
		}
	} else {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		ShowSpace(AutoLoad_space[DispCT], 250, 70+DispCT*25);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		if(DispCT==0)
			GUI_DispStringAt(onoff_str[UTILITY.ALOAD], 260, 70+DispCT*25);
		else
			GUI_DispStringAt(AutoLoad_mode[UTILITY.ALOAD_MODE], 260, 70+DispCT*25);
	}
}
#endif


void RedrawProgMain(void)
{
	int i,j;
	char str[20];
	long dat;
	double fdat;

	if(DispMode == DispMode_SELECT_CH) {
		if(DataRedrawFlag&BG_CLEAR_FLAG) {
			Displine(2,94,316,MEM_GRAY);
			Displine(2,95,316,GW_ORANGE_ku);
			Displine(2,96,316,MEM_WHITE);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_DispStringAt( " Timing Edit for Program ", 55, 40);
		}else{
#if Enable_Optim_display		
			if(only_text==2)	only_text = 0;
			else 			only_text = 1;
#endif			
		}
		DispScrCurrLoc = DispCT;		
		for( i=0 ; i<=7 ; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				continue;
			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT){
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					if((DataRedrawFlag&BG_CLEAR_FLAG)==0){
						Draw_New_Bar_25(SeqMain_item_x_addr[i]-5,SeqMain_item_y_addr[i],hilight_space[i],1);
						continue;
					}
				}else{
					if((DataRedrawFlag&BG_CLEAR_FLAG)==0){
						Draw_New_Bar_25(SeqMain_item_x_addr[i]-5,SeqMain_item_y_addr[i],hilight_space[i],0);
						continue;
					}
				}

				if(DataRedrawFlag&BG_CLEAR_FLAG){
					Draw_Bar_25(SeqMain_item_x_addr[i]-5,SeqMain_item_y_addr[i],hilight_space[i]);
					//printf(":3\n");
				}
				
			}
			if(i<2)		GUI_SetColor(Parameter_Font_U_Bolor);
			else		GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( item_str[i], SeqMain_item_x_addr[i], SeqMain_item_y_addr[i]);
			dat = GetChanData( i , 0);

			if( i==Program_PROG || i==Program_STEP)	sprintf( str, "%02d", dat+1);
			else if( i==Program_Memory)				sprintf( str, "M%03d", dat+1);
			else if( i==Program_Run)				strcpy( str, run[dat]);
			else if( i==Program_P_F_Time) {
				fdat = dat *0.1;
				if(fdat==0)		sprintf(str, " Off ");
				else 			Display_Parameter_Pro(fdat,str,1);
			} else {
				fdat = dat *0.1;
				if(fdat==0)		sprintf(str, " Off ");
				else 			Display_Parameter_Pro(fdat,str,1);
			}
			GUI_SetColor(Parameter_Font_R_Bolor);
			ShowSpace(val_space[i], val_space_x_addr[i], SeqMain_item_y_addr[i]);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, SeqMain_val_x_addr[i], SeqMain_item_y_addr[i]);
		}
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_SetTextAlign(GUI_TA_LEFT);
	} else if(DispMode == DispMode_BROWSE_ITEMS) {
		if((DispCT==Program_PROG)||(DispCT==Program_STEP)) {
			for( i=0 ; i<=7 ; i++) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);

				if( i == DispCT)
					continue;

				if(i<2)		GUI_SetColor(Parameter_Font_U_Bolor);
				else		GUI_SetColor(Parameter_Font_L_Bolor);

				GUI_DispStringAt( item_str[i], SeqMain_item_x_addr[i], SeqMain_item_y_addr[i]);
				dat = GetChanData( i , 0);

				if( i==Program_PROG || i==Program_STEP)		sprintf( str, "%02d", dat+1);
				else if( i==Program_Memory)					sprintf( str, "M%03d", dat+1);
				else if( i==Program_Run)					strcpy( str, run[dat]);
				else if( i==Program_P_F_Time) {
					fdat = dat *0.1;
					if(fdat==0)		sprintf(str, " Off ");
					else 			Display_Parameter_Pro(fdat,str,1);
				} else {
					fdat = dat *0.1;
					if(fdat==0)		sprintf(str, " Off ");
					else			Display_Parameter_Pro(fdat,str,1);
				}
				GUI_SetColor(Parameter_Font_R_Bolor);
				ShowSpace(val_space[i], val_space_x_addr[i], SeqMain_item_y_addr[i]);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, SeqMain_val_x_addr[i], SeqMain_item_y_addr[i]);
			}
		}
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN)
			sprintf(str, "%s", KeyinBuf);
		else {
			dat = GetChanData(DispCT,0);
			if( DispCT==Program_PROG || DispCT==Program_STEP)		sprintf( str, "%02d", dat+1);
			else if( DispCT == Program_Memory)					sprintf( str, "M%03d", dat+1);
			else if( DispCT==Program_Run)							strcpy( str, run[dat]);
			else if( DispCT==Program_P_F_Time) {
				fdat = dat *0.1;
				if(fdat==0)		sprintf(str, " Off ");
				else			Display_Parameter_Pro(fdat,str,1);
			} else {
				fdat = dat *0.1;
				if(fdat==0)		sprintf(str, " Off ");
				else			Display_Parameter_Pro(fdat,str,1);
			}
		}
		ShowSpace(val_space[DispCT], val_space_x_addr[DispCT], SeqMain_item_y_addr[DispCT]);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, SeqMain_val_x_addr[DispCT], SeqMain_item_y_addr[DispCT]);
	}
}
void RedrawProgChain(void)
{
	char tmp,str[20];
	int i,j,tmp1;
	
	if(DataRedrawFlag&BG_CLEAR_FLAG){
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_U_Bolor);
		GUI_DispStringAt( " Program Chain Set ", 70, Disp_Start_Y2+ 0*Disp_Interval);
	}
	if(DispMode == DispMode_SELECT_CH)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);
	else								GUI_SetBkColor(Parameter_Bottom_Bolor);
	
	if(DataRedrawFlag&BG_CLEAR_FLAG){
		Draw_Bar_25( 103, Disp_Start_Y2+ 1*Disp_Interval,11 );
		sprintf( str, " Start " );
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt(str, 105, Disp_Start_Y2+ 1*Disp_Interval);
	}
	if(DispMode==DispMode_SELECT_CH) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
	} else {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_R_Bolor);
	}
	if((DispMode==DispMode_SELECT_CH)||(DataRedrawFlag&BG_CLEAR_FLAG)){
		tmp = p3k_Disp_PROG.Chain_Start_Prog;
		sprintf( str, " P%02d ", tmp+1);
		ShowSpace(2, 203, Disp_Start_Y2+ 1*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt(str, 200, Disp_Start_Y2+ 1*Disp_Interval);
	}

	/* Show Parameter */
	if(DispMode <= DispMode_BROWSE_ITEMS) {
#if Enable_Optim_display		
		if(only_text==2)	only_text = 0;
		else			only_text = 1;
#endif		
		for ( i=DispScrStartCT, j=0 ; i<= DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(DispMode == DispMode_BROWSE_ITEMS) {
				if( (DispScrCurrLoc == DispScrEndCT) || (DispScrCurrLoc == DispScrStartCT) ) {
					ShowScrollBar_Other(305,Disp_Start_Y2+2*Disp_Interval,16,4,Disp_Interval,10,DispScrStartCT);
					GUI_SetBkColor(Parameter_Bottom_Bolor);
					if( i == DispScrCurrLoc)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					Draw_Bar_25(76,Disp_Start_Y2+((j+2)*Disp_Interval),33);
				} else {
					if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != DispScrCurrLoc && i != B_DispCT ) )
						continue;
					if( i == DispScrCurrLoc || i == B_DispCT ) {
						if( i==DispScrCurrLoc)
							GUI_SetBkColor(Parameter_Select_Bar_Bolor);
						if(DataRedrawFlag&BG_CLEAR_FLAG)
							Draw_Bar_25(76,Disp_Start_Y2+((j+2)*Disp_Interval),33);
						else{
							if(i==DispScrCurrLoc)
								Draw_New_Bar_25(76,Disp_Start_Y2+((j+2)*Disp_Interval),33,1);
							else
								Draw_New_Bar_25(76,Disp_Start_Y2+((j+2)*Disp_Interval),33,0);
							continue;
						}
					}
				}
			}
			sprintf( str, "P%02d", i+1);
			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( str, 90, Disp_Start_Y2+((j+2)*Disp_Interval));
			/* Draw Arrow Point */
			DrawArrowPoint(145, 12+Disp_Start_Y2+((j+2)*Disp_Interval));

			/* Show Prog Mirror Number */
			tmp = p3k_Disp_PROG.PROGSEQ[i];

			if( tmp == 0)	sprintf( str, " Off " );
			else			sprintf( str, "P%02d", tmp);
			GUI_SetColor(Parameter_Font_R_Bolor);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, 230, Disp_Start_Y2+((j+2)*Disp_Interval));
		}
	}
	if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		tmp1 = DispScrCurrLoc - DispScrStartCT;
		if(KeyInFlag&DIGI_KEY_IN)
			sprintf(str, "P%s", KeyinBuf);
		else {
			/* Show Prog Mirror Number */
			tmp = p3k_Disp_PROG.PROGSEQ[DispScrCurrLoc];
			if( tmp == 0)	sprintf( str, " Off " );
			else			sprintf( str, "P%02d", tmp);
		}
		ShowSpace(3,233,Disp_Start_Y2+((tmp1+2)*Disp_Interval));
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, 230, Disp_Start_Y2+((tmp1+2)*Disp_Interval));
	}
}
void RedrawSeqRun(void)
{
	char tmp,str[20];
	int i,j,tmp1;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);
	GUI_DispStringAt( "Active Channels for Program Mode", 10, Disp_Start_Y2);
	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_DispStringAt( "CH", 85, Disp_Start_Y2+ 1*Disp_Interval);
	GUI_DispStringAt( "Active", 186, Disp_Start_Y2+ 1*Disp_Interval);

	/* Show Parameter */
	if(DispMode == DispMode_SELECT_CH) {
		for ( i=DispScrStartCT, j=0 ; i<= DispScrEndCT ; i++, j++) {
			/* Show Prog Number */
			GUI_SetBkColor(Parameter_Bottom_Bolor);

			if( (DispScrCurrLoc == DispScrEndCT) || (DispScrCurrLoc == DispScrStartCT) ) {
				if(Data_tmp->CONF.Ext_Setting.Control) {
					GUI_SetColor(Message_Font_Bolor);
					GUI_DispStringAt( " EXT ", 250, Disp_Start_Y2+((j+2)*Disp_Interval));
				} else
					ShowSpace_LEFT( 4, 250, Disp_Start_Y2+((j+2)*Disp_Interval));
				if( i == DispScrCurrLoc)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				//GUI_GotoXY(76,Disp_Start_Y2+((j+2)*Disp_Interval));
				//GUI_DispChars(' ',33);
				Draw_Bar_25(76,Disp_Start_Y2+((j+2)*Disp_Interval),33);
			} else {
				if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != DispScrCurrLoc && i != B_DispCT ) )
					continue;
				if( i == DispScrCurrLoc || i == B_DispCT ) {
					if( i==DispScrCurrLoc)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					//GUI_GotoXY(76,Disp_Start_Y2+((j+2)*Disp_Interval));
					//GUI_DispChars(' ',33);
					Draw_Bar_25(76,Disp_Start_Y2+((j+2)*Disp_Interval),33);
				}
			}
			/* Draw Channel No */
			sprintf( str, "%02d", i+1);
			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( str, 90, Disp_Start_Y2+((j+2)*Disp_Interval));
			/* Draw Arrow Point */
			//DrawArrowPoint(145, 96+j*22);
			DrawArrowPoint(145, 12+Disp_Start_Y2+((j+2)*Disp_Interval));
			/* Show Prog Mirror Number */
			tmp = D_RUNPROG.ACTCH[i];
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_SetColor(Parameter_Font_R_Bolor);
			GUI_DispStringAt( onoff_str[tmp], 230, Disp_Start_Y2+((j+2)*Disp_Interval));
		}
	}
	if(DispMode == DispMode_BROWSE_ITEMS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		/* Show Prog Mirror Number */
		tmp = D_RUNPROG.ACTCH[DispScrCurrLoc];
		tmp1 = DispScrCurrLoc - DispScrStartCT;
		ShowSpace( 4, 233, Disp_Start_Y2+((tmp1+2)*Disp_Interval));
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( onoff_str[tmp], 230, Disp_Start_Y2+((tmp1+2)*Disp_Interval));
	}
}


void RedrawProgExecute(void)
{
	char str[9];
	UWORD dat,dat1,SPEC_Result_Temp;
	UWORD Display_Count_Temp;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

#if	redraw_new_flag == 0 
	RedrawMeasure();
#endif

	DMA_Update_Flag = 1;

	GUI_SetFont(Parameter_Font);
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);
	Display_Count_Temp = Prog_Seq_Data.Display_Count/3;

	if(Prog_Seq_Data.Total_Count)
		GUI_DispStringAt(" Run Program ", 5, 110);
	else {
		GUI_DispStringAt(" No Program ", 5, 110);
		return;
	}

	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_DispStringAt( " Program No. :", 30, 140);
	dat = Prog_Seq_Data.Prog_Disp_Data[Display_Count_Temp].Prog_No+1;
	sprintf( str, "%02d", dat);
	GUI_SetColor(Parameter_Font_R_Bolor);
	GUI_DispStringAt( str, 190, 140 );

	Displine(0,107,320,MEM_GRAY);
	Displine(0,108,320,GW_ORANGE_ku);
	Displine(0,109,320,MEM_WHITE);

	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_DispStringAt( " Step(Memory) : ", 30, 170);
	dat = Prog_Seq_Data.Prog_Disp_Data[Display_Count_Temp].Mem_NO+1;
	dat1= Prog_Seq_Data.Prog_Disp_Data[Display_Count_Temp].Step_No+1;
	sprintf( str, "%02d(%03d)", dat1,dat);
	GUI_SetColor(Parameter_Font_R_Bolor);
	GUI_DispStringAt( str, 190, 170);

	SPEC_Result_Temp = Prog_Seq_Data.Prog_Disp_Data[Display_Count_Temp].SPEC_Result_Backup;

	if(1 == SPEC_Result_Temp)
		GUI_SetColor(NG_Font_Bolor);
	else
		GUI_SetColor(GO_Font_Bolor);
	GUI_DispStringAt(okng[SPEC_Result_Temp], 270, 170);
}


#if Enable_Func_DisTime
extern unsigned long StepStarTime;
#define Time_Unit_1uS							0x0000	/*Bit 13~15*/
#define Time_Unit_10uS							0x2000	/*Bit 13~15*/
#define Time_Unit_100uS							0x4000	/*Bit 13~15*/
#define Time_Unit_1mS							0x6000	/*Bit 13~15*/
#define Time_Unit_100mS							0x8000	/*Bit 13~15*/
#define Time_Unit_1S							0xA000	/*Bit 13~15*/
#define Time_Unit_10S							0xC000	/*Bit 13~15*/
#define Time_Unit_1min							0xE000	/*Bit 13~15*/
#endif

void RedrawNSeqExecute(void) {
	char str[20];
	long dat;
	long dat_loop;

	P3k_FPGA_Seq_Str	*SEQ = &Prog_Seq_Data.FPGA_Seq_Data[Prog_Seq_Data.Display_Count];;
	///P3k_Prog_Disp_Str *SEQ = &Prog_Seq_Data.Prog_Disp_Data[Prog_Seq_Data.Display_Count];
	unsigned long C_sum_sec;
	ULONG C_step_sec;
	static UBYTE last_sec=0xff;
	static UWORD last_Step,last_loop;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
#if	redraw_new_flag == 0 
	RedrawMeasure();
#endif
	DMA_Update_Flag = 1;

	GUI_SetFont(Parameter_Font);
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);

	if(Prog_Seq_Data.Total_Count)

		GUI_DispStringAt(" Run N.Seq. ", 5, 110);
	else {
		GUI_DispStringAt(" No N.Seq. ", 5, 110);
		last_menu = 0xFF;
		return;
	}

	Displine(0,107,320,MEM_GRAY);
	Displine(0,108,320,GW_ORANGE_ku);
	Displine(0,109,320,MEM_WHITE);

	/* Show Program Number 1~12 */
	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_DispStringAt( " Seq. No. :", 130, 115);
	GUI_DispStringAt( " Step : ",   130, 145);
	GUI_DispStringAt( " Loop : ",   130, 175);

	GUI_SetColor(Parameter_Font_R_Bolor);

	dat = Prog_Seq_Data.Prog_Disp_Data[Prog_Seq_Data.Display_Count].Prog_No+1;
	dat_loop = dat -1;
	sprintf( str, "%02d", dat);
	GUI_DispStringAt( str, 240, 115 );

	dat = Prog_Seq_Data.Prog_Disp_Data[Prog_Seq_Data.Display_Count].Step_No+1;
	sprintf( str, "%04d", dat);
	GUI_DispStringAt( str, 240, 145);

	dat = Prog_Seq_Data.FPGA_Loop_Count[Prog_Seq_Data.Prog_Disp_Data[Prog_Seq_Data.Display_Count].Loop_Address]+1;


	if (P3k_NSeq_Disp.NSeq_Seq[dat_loop].NSeq_Loop)
		sprintf( str, "%04d", dat);
	else
		sprintf( str, " Infinity ");

	GUI_DispStringAt( str, 240, 175);
#if Enable_Func_DisTime	
		if(dat != last_loop){
			last_loop = dat;
			StepStarTime = p3k_Measure_Data.Hour*3600 +p3k_Measure_Data.Min*60+p3k_Measure_Data.Sec;
		}
	if( Data_tmp->CONF.Count_Time||Data_tmp->CONF.cut_off_time_total) {
		if((last_sec!=p3k_Measure_Data.Sec)||(Prog_Seq_Data.Display_Count!=last_Step)||(0==p3k_Measure_Data.Sec)) {
			last_Step = Prog_Seq_Data.Display_Count;
			last_sec=p3k_Measure_Data.Sec;	
			switch(SEQ->CS1_Setting&0xE000){
				case Time_Unit_1min:
					C_step_sec = SEQ->Duration_Setting*60;
					break;
				case Time_Unit_10S:
					C_step_sec = SEQ->Duration_Setting*10;
					break;
				case Time_Unit_1S:
					C_step_sec = SEQ->Duration_Setting;
					break;
				case Time_Unit_100mS:
					C_step_sec = SEQ->Duration_Setting/10;
					break;
				case Time_Unit_1mS:
					C_step_sec = SEQ->Duration_Setting/1000;
					break;
				case Time_Unit_100uS:
					C_step_sec = SEQ->Duration_Setting/10000;
					break;
				default:	
					C_step_sec = 0;
					break;
			}
			C_sum_sec = p3k_Measure_Data.Hour*3600 +p3k_Measure_Data.Min*60+p3k_Measure_Data.Sec;
			if(C_sum_sec > StepStarTime){
				C_sum_sec = C_sum_sec - StepStarTime;
			}else{
				StepStarTime = C_sum_sec; 
				C_sum_sec = 0;
			}
		
			if(C_step_sec>C_sum_sec){
				if(Data_tmp->CONF.T_count_up)
					C_step_sec = C_sum_sec;
				else	
					C_step_sec -= C_sum_sec;
			}else{
				if(Data_tmp->CONF.T_count_up)
					C_step_sec = C_step_sec;
				else
					C_step_sec = 0;
				StepStarTime = C_sum_sec;
			}

			GUI_SetFont(Time_Alarm_Font);
			if(Data_tmp->CONF.T_count_up)
				GUI_SetColor(Noted_Font_Bolor);
			else	
				GUI_SetColor(GO_Font_Bolor);
			//sprintf( str, "     %01d:%02d:%02d ", C_sum_sec/3600, (C_sum_sec/60)%60, C_sum_sec%60);
			sprintf( str, "     %01d:%02d:%02d ", C_step_sec/3600, (C_step_sec/60)%60, C_step_sec%60);
			//sprintf( str, "3:21:31");
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, 105, 140);
		}						
	}				
#endif		
			
}

///#endif//Enable_fun_disTime

void RedrawFSeqExecute(void)
{
	char str[20];
	long dat;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

#if	redraw_new_flag == 0 
	RedrawMeasure();
#endif

	DMA_Update_Flag = 1;

	GUI_SetFont(Parameter_Font);
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);

	if(P3k_FSeq_Disp.FSeq_Max_Step<0xFF00)
		GUI_DispStringAt(" Run F.Seq. ", 5, 110);
	else {
		GUI_DispStringAt(" No F.Seq. ", 5, 110);
		return;
	}

	Displine(0,107,320,MEM_GRAY);
	Displine(0,108,320,GW_ORANGE_ku);
	Displine(0,109,320,MEM_WHITE);

	/* Show Program Number 1~12 */
	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_DispStringAt( " Step : ",   130, 130);
	GUI_DispStringAt( " Loop : ",   130, 160);

	GUI_SetColor(Parameter_Font_R_Bolor);
	dat = Prog_Seq_Data.Display_Count+1;
	sprintf( str, "%04d", dat);
	GUI_DispStringAt( str, 240, 130);

	dat = Prog_Seq_Data.FPGA_Loop_Count[0]+1;
	if (P3k_FSeq_Disp.FSeq_Loop)
		sprintf( str, "%04d", dat);
	else
		sprintf( str, " Infinity ");

	GUI_DispStringAt( str, 240, 160);
}

void RedrawProgDetail(void)
{
	char i=0,j=0,k,l,m;
	char str[4];
	UBYTE Prog_Setting,Step_Setting;
	UWORD Display_Count_Temp,SPEC_Result_Temp;

	P3k_Prog_Disp_Str	*Prog_Disp_Ptr;

	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);

	if(!Prog_Seq_Data.Total_Count) {
		GUI_DispStringAt( "No Program ", 5, 40);
		return;
	} else
		GUI_DispStringAt(" Run Program Detail Result", 30, 30);

	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_DispStringAt( "Program",10, 65);
	GUI_DispStringAt( "Step", 	100, 65);
	GUI_DispStringAt( "Result", 180, 65);

	Displine(10,64,290,MEM_GRAY);
	Displine(10,65,290,GW_ORANGE_ku);
	Displine(10,66,290,MEM_WHITE);

	for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		if((DispScrCurrLoc == DispScrEndCT) || (DispScrCurrLoc == DispScrStartCT)) {
			if(Prog_Seq_Data.Total_Count > 4) {
				ShowScrollBar_Other(305,70,Prog_Seq_Data.Total_Count,4,30,10,DispScrStartCT);
				GUI_SetBkColor(Parameter_Bottom_Bolor);
			}
			if( i == DispScrCurrLoc)
				GUI_SetBkColor(Parameter_Select_Bar_Bolor);
			//GUI_GotoXY(Disp_Start_X,ProgDetail_Item_Y_Addr[j]);
			//GUI_DispChars(' ',50);
			Draw_Bar_25(Disp_Start_X,ProgDetail_Item_Y_Addr[j],50);
		} else {
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != DispScrCurrLoc && i != B_DispCT ) )
				continue;
			if( i == DispScrCurrLoc || i == B_DispCT ) {
				if( i==DispScrCurrLoc)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				Draw_Bar_25(Disp_Start_X,ProgDetail_Item_Y_Addr[j],50);
			}
		}

		Prog_Disp_Ptr = &Prog_Seq_Data.Prog_Disp_Data[i];
		GUI_SetColor(Parameter_Font_L_Bolor);
		sprintf( str, "%d", Prog_Disp_Ptr->Prog_No+1);
		GUI_DispStringAt( str, 40, ProgDetail_Item_Y_Addr[j]);
		sprintf( str, "%d", Prog_Disp_Ptr->Step_No+1);
		GUI_DispStringAt( str, 115,ProgDetail_Item_Y_Addr[j]);

		SPEC_Result_Temp = Prog_Seq_Data.Prog_Disp_Data[i].SPEC_Result;
		sprintf( str, ViewNext_G_N[SPEC_Result_Temp]);

		if(SPEC_Result_Temp == 1)
			GUI_SetColor(NG_Font_Bolor);
		else
			GUI_SetColor(GO_Font_Bolor);
		GUI_DispStringAt(str, 195, ProgDetail_Item_Y_Addr[j]);
	}
}

void RedrawLuaExecute(void)
{
	UBYTE err;
	char str[8],i;
	char str_temp[5][8] = { "a", "ab" ,"abc" ,"abcd" ,"abcde"};
	int item_x_addr[5] = {	32, 96, 160, 224, 288};		/* Item string X location */
	if(OSSemAccept(LuaDispEventSemPtr)) {
		OSSemPost(LuaDispReadySemPtr);
		OSSemPend(LuaDispDoneSemPtr, 0, &err);
	}
#if 0
	if(Script[0].functionname[0]!=0) {
		GUI_SetFont(&GUI_FontArial15);
		GUI_SetBkColor(GW_GRAY);
		GUI_SetColor(GW_BLACK);
		strncpy(str,(const char *)&Script[0].functionname,8);
		GUI_DispStringAt(str, 0, 205);
	}
#endif
#if 0
	GUI_SetFont(&GUI_FontArial15);
	GUI_SetBkColor(GW_GRAY);
	GUI_SetColor(GW_BLACK);
#endif
#if 0
	GUI_SetTextAlign(GUI_TA_RIGHT);
//	GUI_SetTextAlign(GUI_TA_LEFT);
//	GUI_SetTextAlign(GUI_TA_CENTER);
	GUI_DispStringAt("a", 32, 216);
	GUI_DispStringAt("ab", 96, 216);
	GUI_DispStringAt("abc", 160, 216);
	GUI_DispStringAt("abcd", 224, 216);
	GUI_DispStringAt("abcde", 288, 216);
#endif
#if 0
	for(i=0; i<5; i++) {
		GUI_SetTextAlign(GUI_TA_CENTER);
		GUI_DispStringAt(str_temp[i], item_x_addr[i], 216);
	}
#endif
}
static const char FuncMain[P_Func_M_Max][30] = { "Function Select ", "Complete Ring Time", "NSEQ Timer"  };
static const char FunMain_space[P_Func_M_Max] = { 5,5,9 };

void RedrawFuncMain(void)
{
	int i,j;
	UWORD dat;
	char str[20];
	UBYTE x_gap = 82;
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);
	GUI_SetTextAlign(GUI_TA_LEFT);
	GUI_DispStringAt( " FUNCTION ", 105, 30);
	Displine(2,65,316,MEM_GRAY);
	Displine(2,66,316,GW_ORANGE_ku);
	Displine(2,67,316,MEM_WHITE);	
	if(DispMode==DispMode_SELECT_CH){
		for( i=0;i<P_Func_M_Max;i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if( (DispCT == DispScrEndCT) || (DispCT == DispScrStartCT) ) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				Draw_Bar_25(36,Disp_Start_Y0+i*25,55);
			} else {
				if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != DispCT && i != B_DispCT ) )
					continue;
				if( i == DispCT || i == B_DispCT ) {
					if( i==DispCT)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					Draw_Bar_25(36,Disp_Start_Y0+i*25,55);
				}
			}
			GUI_SetColor(Parameter_Font_L_Bolor);
			if((i==P_Func_M_count)&&(P3k_Disp_Data.Load_Type!=NSeq_Load))
				GUI_SetColor(Parameter_Font_Bolor_Para);
			else
				GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( FuncMain[i], 45, Disp_Start_Y0+i*25);
			dat = GetChanData(i,0);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_SetColor(Parameter_Font_R_Bolor);
			if(i==P_Func_M_start){
				if(dat==Normal_Load)	sprintf( str, "OFF");
				else if(dat==Prog_Load)	sprintf( str, "PROG");
				else if(dat==NSeq_Load)	sprintf( str, "NSEQ");
				else if(dat==FSeq_Load)	sprintf( str, "FSEQ");
				else if(dat==OCP_Load)	sprintf( str, "OCP");
#if Enable_Battery_Discharge
				else if(dat==OPP_Load)	sprintf( str, "OPP");
				else if(dat==BATT_Load)	sprintf( str, "BATT");
#endif
#if Enable_LED_function
				else if(dat==FLED_Load)	sprintf( str, "LED");
				else if(dat==CLED_Load)	sprintf( str, "CLED");
#endif				
				else sprintf( str, "OFF");
			}else if(i==P_Func_M_comp){
				GUI_DispStringAt("s", Para_Start_X + x_gap+15, Disp_Start_Y0+i*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				if(dat==601)	sprintf( str, "Infinity");
				else if(dat==0)sprintf(str,"OFF");
				else 			Display_Parameter_Pro(dat,str,0);
			}else if(i==P_Func_M_count){
				if(dat)	sprintf(str,"Elapsed  ");
				else	sprintf(str,"Remaining");
				if(P3k_Disp_Data.Load_Type!=NSeq_Load){
					GUI_SetColor(Parameter_Font_Bolor_Para);
				}				
			}			
			
			GUI_DispStringAt(str, Para_Start_X + x_gap, Disp_Start_Y0+i*Disp_Interval);
		
		}
	} else {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		ShowSpace(FunMain_space[DispCT], Para_Start_X + x_gap+2, Disp_Start_Y0+(DispCT - DispScrStartCT)*25);
		GUI_SetTextAlign(GUI_TA_RIGHT);

		if( KeyInFlag & DIGI_KEY_IN ) {
			sprintf( str, " %s " , KeyinBuf );
			GUI_DispStringAt( str, Para_Start_X + 76, Disp_Start_Y0+(DispCT )*Disp_Interval);
		} else {
			dat = GetChanData(DispCT,0);
			if(DispCT==P_Func_M_start){
				if(dat==Normal_Load)	sprintf( str, "OFF");
				else if(dat==Prog_Load)	sprintf( str, "PROG");
				else if(dat==NSeq_Load)	sprintf( str, "NSEQ");
				else if(dat==FSeq_Load)	sprintf( str, "FSEQ");
				else if(dat==OCP_Load)	sprintf( str, "OCP");
#if Enable_Battery_Discharge
				else if(dat==OPP_Load)	sprintf( str, "OPP");
				else if(dat==BATT_Load)	sprintf( str, "BATT");
#endif
#if Enable_LED_function
				else if(dat==FLED_Load)	sprintf( str, "LED");
				else if(dat==CLED_Load)	sprintf( str, "CLED");
#endif				
				else sprintf( str, "OFF");
			}else if(DispCT==P_Func_M_comp){
				if(dat==601)	sprintf( str, "Infinity");
				else if(dat==0)sprintf(str,"OFF");
				else 			Display_Parameter_Pro(dat,str,0);
			}else if(DispCT==P_Func_M_count){
				if(dat)	sprintf(str,"Elapsed  ");
				else	sprintf(str,"Remaining");
			}
			GUI_DispStringAt(str, Para_Start_X + x_gap, Disp_Start_Y0+(DispCT )*Disp_Interval);
		}			
	}
}

void RedrawSeqFunction(void)
{
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);
	GUI_SetTextAlign(GUI_TA_LEFT);
	GUI_DispStringAt( " Sequence Function ", 75, 30);
	Displine(2,65,316,MEM_GRAY);
	Displine(2,66,316,GW_ORANGE_ku);
	Displine(2,67,316,MEM_WHITE);
}
void RedrawAppFunction(void)
{
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);
	GUI_SetTextAlign(GUI_TA_LEFT);
	GUI_DispStringAt( " APP Function ", 75, 30);
	Displine(2,65,316,MEM_GRAY);
	Displine(2,66,316,GW_ORANGE_ku);
	Displine(2,67,316,MEM_WHITE);
}
void RedrawAppFunOCP(void)
{
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);
	GUI_SetTextAlign(GUI_TA_LEFT);
	GUI_DispStringAt( " OCP Function ", 75, 30);
	Displine(2,65,316,MEM_GRAY);
	Displine(2,66,316,GW_ORANGE_ku);
	Displine(2,67,316,MEM_WHITE);
}

static const char NSeq_item_Data[P_NSeq_Max][20]	= { "Start:", "Seq. No:", "Memo:", "Mode:", "Range:", "Loop:", "Last Load:", "Last:", "Chain:" };
static const int NSeq_item_X_Addr[P_NSeq_Max]		= { 55,       160,        10,      10,      10,       10,      160,          160,         160      };
static const int NSeq_item_Y_Addr[P_NSeq_Max]		= { 45,       45,         90,      115,     140,      165,     115,          140,         165      };
static const int NSeq_Value_X_Addr[P_NSeq_Max]		= { 145,      280,        80,      145,     145,      145,     305,          284,         305      };
static const char NSeq_space[P_NSeq_Max]			= { 2,        2,          4,       4,       5,        6,       4,            7,           4        };
//static const int NSeq_light_space[P_NSeq_Max]		= { 22,       20,         29,      29,      29,       29,      29,           29,          29       };
static const int NSeq_light_space[P_NSeq_Max]		= { 22,       26,         61,      29,      29,       29,      33,           33,          33       };
static const char NSeq_Mode_Item[4][20]				= { " CC ", " CR ", " CV ", " CP " };
static const char NSeq_Mode_Unit[4][20]				= { " A   ", "mS ", " V   ", " W  " };
static const char NSeq_Range_Item[4][20]			= { " ILVL ", " IHVL ", " ILVH ", " IHVH " };
static const char NSeq_Range_Item_CR[4][20]			= { " ILVL ", " SHVL ", " SLVH ", " IHVH " };


void RedrawSeqNormal(void)
{
	int i;
	char str[50];
	long dat;
	double fdat;
	static unsigned char flag_loopInfinity;
	static unsigned char flag_ChainNone;
	unsigned char chain_num;
	if(DispMode_SELECT_CH==DispMode) {
		DispScrCurrLoc = DispCT;
		if(DataRedrawFlag&BG_CLEAR_FLAG) {
			Displine(2,79,316,MEM_GRAY);
			Displine(2,80,316,GW_ORANGE_ku);
			Displine(2,81,316,MEM_WHITE);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_DispStringAt( " Timing Edit for Normal Sequence ", 15, 20);
		}
		for( i=0 ; i<P_NSeq_Max ; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				continue;			

			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT){
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					if((DataRedrawFlag&BG_CLEAR_FLAG)==0){
						Draw_New_Bar_25(NSeq_item_X_Addr[i]-5,NSeq_item_Y_Addr[i],NSeq_light_space[i],1);
						continue;
					}
				}else{
					if((DataRedrawFlag&BG_CLEAR_FLAG)==0){
						Draw_New_Bar_25(NSeq_item_X_Addr[i]-5,NSeq_item_Y_Addr[i],NSeq_light_space[i],0);
						continue;
					}
				}

				if(DataRedrawFlag&BG_CLEAR_FLAG){
					Draw_Bar_25(NSeq_item_X_Addr[i]-5,NSeq_item_Y_Addr[i],NSeq_light_space[i]);
				}				
			}
	
			if(i<2) 	GUI_SetColor(Parameter_Font_U_Bolor);
			else if((flag_loopInfinity)&&(i>=P_NSeq_Last_Load))GUI_SetColor(MEM_DARKGRAY);
			else if((flag_ChainNone==0)&&((i==P_NSeq_Last_Load)||(i==P_NSeq_Last_Set)))GUI_SetColor(MEM_DARKGRAY);
			else		GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( NSeq_item_Data[i], NSeq_item_X_Addr[i], NSeq_item_Y_Addr[i]);
			dat = GetChanData( i , 0);
			if( i==P_NSeq_Start||i==P_NSeq_No ) sprintf( str, " S%02d ", dat+1);
			else if( i==P_NSeq_Memo) {
				if(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Memo[0]==0)
					sprintf( str, " No Memo ");
				else
					sprintf( str, " %s ",P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Memo);
			} else if( i==P_NSeq_Mode)			strcpy(  str, NSeq_Mode_Item[dat]);
			else if( i==P_NSeq_Range){
				if(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode != CR_MODE)
					strcpy(  str, NSeq_Range_Item[dat]);
				else
					strcpy(  str, NSeq_Range_Item_CR[dat]);
			}else if( i==P_NSeq_Loop) {
				if(dat) {
					sprintf( str, " %04d ", dat);
					flag_loopInfinity =0;
				} else {
					sprintf( str, " Infinity ");
					flag_loopInfinity =1;
				}
				chain_num =GetChanData( P_NSeq_Chain , 0);
				if(chain_num) {
					if(P3k_NSeq_Data.NSeq_Seq[chain_num-1].NSeq_Max_Step)flag_ChainNone = 0;
					else flag_ChainNone = 1;
				} else {
					flag_ChainNone = 1;
				}
			} else if(i==P_NSeq_Last_Load)
				strcpy( str, onoff_str[dat]);
			else if(i==P_NSeq_Last_Set) {
				GUI_SetColor(Parameter_Font_R_Bolor);
				if((flag_loopInfinity)&&(i>=P_NSeq_Last_Load))GUI_SetColor(MEM_DARKGRAY);
				else if((flag_ChainNone==0)&&((i==P_NSeq_Last_Load)||(i==P_NSeq_Last_Set)))GUI_SetColor(MEM_DARKGRAY);
				GUI_DispStringAt( NSeq_Mode_Unit[GetChanData( 3 , 0)], NSeq_Value_X_Addr[i], 140);
				fdat = StepToReal(dat,0);
				Display_Parameter_Pro(fdat,str,Search_precision(0));
			} else { /*P_NSeq_Chain*/
				if(dat) {
					sprintf(str, " S%02d ", dat);
				} else {
					sprintf(str, " Off ");
				}
			}
			GUI_SetColor(Parameter_Font_R_Bolor);
			if((flag_loopInfinity)&&(i>=P_NSeq_Last_Load))GUI_SetColor(MEM_DARKGRAY);
			else if((flag_ChainNone==0)&&((i==P_NSeq_Last_Load)||(i==P_NSeq_Last_Set)))GUI_SetColor(MEM_DARKGRAY);
			if( i==P_NSeq_Memo) {
				GUI_SetTextAlign(GUI_TA_RIGHT);
				//GUI_GotoXY(NSeq_Value_X_Addr[i], NSeq_item_Y_Addr[i]);
				//GUI_DispChars(' ',46);
				Draw_Bar_25(NSeq_Value_X_Addr[i], NSeq_item_Y_Addr[i],46);
				GUI_SetTextAlign(GUI_TA_LEFT);
			} else {
				ShowSpace(NSeq_space[i], NSeq_Value_X_Addr[i], NSeq_item_Y_Addr[i]);
				GUI_SetTextAlign(GUI_TA_RIGHT);
			}
			GUI_DispStringAt( str, NSeq_Value_X_Addr[i], NSeq_item_Y_Addr[i]);
		}
	} else if(DispMode_BROWSE_ITEMS==DispMode) {
		if(P_NSeq_No==DispCT) {
			for( i=0 ; i<P_NSeq_Max ; i++) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				if( i == DispCT)
					continue;
				if(i<2) 	GUI_SetColor(Parameter_Font_U_Bolor);
				else		GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( NSeq_item_Data[i], NSeq_item_X_Addr[i], NSeq_item_Y_Addr[i]);
				dat = GetChanData( i , 0);
				if( i==P_NSeq_Start||i==P_NSeq_No ) sprintf( str, " S%02d ", dat+1);
				else if( i==P_NSeq_Memo) {
					if(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Memo[0]==0)
						sprintf( str, " No Memo ");
					else
						sprintf( str, " %s ",P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Memo);
				} else if( i==P_NSeq_Mode)			strcpy(  str, NSeq_Mode_Item[dat]);
				else if( i==P_NSeq_Range){
					if(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode != CR_MODE)
						strcpy(  str, NSeq_Range_Item[dat]);
					else
						strcpy(  str, NSeq_Range_Item_CR[dat]);
				}else if( i==P_NSeq_Loop) {
					if(dat)	sprintf( str, " %04d ", dat);
					else	sprintf( str, " Infinity ");
				} else if(i==P_NSeq_Last_Load)		strcpy( str, onoff_str[dat]);
				else if(i==P_NSeq_Last_Set) {
					GUI_SetColor(Parameter_Font_R_Bolor);
					GUI_DispStringAt( NSeq_Mode_Unit[GetChanData( 3 , 0)], NSeq_Value_X_Addr[i], 140);
					fdat = StepToReal(dat,0);
					Display_Parameter_Pro(fdat,str,Search_precision(0));
				} else {
					if(dat)	sprintf(str, " S%02d ", dat);
					else	sprintf(str, " Off ");
				}
				GUI_SetColor(Parameter_Font_R_Bolor);
				if( i==P_NSeq_Memo) {
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_GotoXY(NSeq_Value_X_Addr[i], NSeq_item_Y_Addr[i]);
					GUI_DispChars(' ',46);
					GUI_SetTextAlign(GUI_TA_LEFT);
				} else {
					ShowSpace(NSeq_space[i], NSeq_Value_X_Addr[i], NSeq_item_Y_Addr[i]);
					GUI_SetTextAlign(GUI_TA_RIGHT);
				}
				GUI_DispStringAt( str, NSeq_Value_X_Addr[i], NSeq_item_Y_Addr[i]);
			}
		}
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN)
			sprintf(str, "%s", KeyinBuf);
		else {
			dat = GetChanData(DispCT,0);
			if( DispCT==P_NSeq_Start||DispCT==P_NSeq_No ) sprintf( str, " S%02d ", dat+1);
			else if( DispCT==P_NSeq_Memo) {
				if(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Memo[0]==0)
					sprintf( str, " No Memo ");
				else
					sprintf( str, " %s ",P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Memo);
			} else if( DispCT==P_NSeq_Mode)					strcpy(  str, NSeq_Mode_Item[dat]);
			else if( DispCT==P_NSeq_Range){	
				if(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode != CR_MODE)
					strcpy(  str, NSeq_Range_Item[dat]);
				else
					strcpy(  str, NSeq_Range_Item_CR[dat]);
			}else if( DispCT==P_NSeq_Loop) {
				if(dat) sprintf( str, " %04d ", dat);
				else	sprintf( str, " Infinity ");
			} else if(DispCT==P_NSeq_Last_Load)		strcpy( str, onoff_str[dat]);
			else if(DispCT==P_NSeq_Last_Set) {
				fdat = StepToReal(dat,0);
				Display_Parameter_Pro(fdat,str,Search_precision(0));
			} else {
				if(dat) sprintf(str, " S%02d ", dat);
				else	sprintf(str, " Off ");
			}
		}
		if( DispCT==P_NSeq_Memo) {
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_GotoXY(NSeq_Value_X_Addr[DispCT], NSeq_item_Y_Addr[DispCT]);
			GUI_DispChars(' ',46);
			GUI_SetTextAlign(GUI_TA_LEFT);
		} else {
			ShowSpace(NSeq_space[DispCT], NSeq_Value_X_Addr[DispCT], NSeq_item_Y_Addr[DispCT]);
			GUI_SetTextAlign(GUI_TA_RIGHT);
		}
		GUI_DispStringAt( str, NSeq_Value_X_Addr[DispCT], NSeq_item_Y_Addr[DispCT]);
	}
}



static const char FSeqFill_item_Data[P_Fill_Max][20]	= { "Start_Value:", "End_Value:", "Start_Step:", "End_Step:"	};
static const char FSeq_Mode_Unit[2][20]             = { " A   ", "mS "};
void RedrawFSeqFill(void)
{
	UBYTE i;
	long dat;
	double fdat;
	char str[50];
	if(DispMode_SELECT_CH==DispMode) {
		if(DataRedrawFlag&BG_CLEAR_FLAG) {
			Displine(2,65,316,MEM_GRAY);
			Displine(2,66,316,GW_ORANGE_ku);
			Displine(2,67,316,MEM_WHITE);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_DispStringAt( " Fill Edit for Fast Sequence ", 45, 30);
		}
		DispScrCurrLoc = DispCT;
		for(i=0 ; i<P_Fill_Max ; i++) {
			
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast) && ( i != B_DispCT && i != DispCT ) )
				continue;
			GUI_SetBkColor(Parameter_Bottom_Bolor);			

			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT){
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					if((DataRedrawFlag&BG_CLEAR_FLAG)==0){
						Draw_New_Bar_25(Disp_Start_X, Disp_Start_Y0+ i*Disp_Interval,HiLight_Length,1);
						continue;
					}
				}else{
					if((DataRedrawFlag&BG_CLEAR_FLAG)==0){
						Draw_New_Bar_25(Disp_Start_X, Disp_Start_Y0+ i*Disp_Interval,HiLight_Length,0);
						continue;
					}
				}

				if(DataRedrawFlag&BG_CLEAR_FLAG){
					Draw_Bar_25(Disp_Start_X, Disp_Start_Y0+ i*Disp_Interval,HiLight_Length);
				}				
			}
			
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_SetColor(Parameter_Font_L_Bolor);

			GUI_DispStringAt( FSeqFill_item_Data[i], Disp_Start_X, Disp_Start_Y0+i*Disp_Interval);
			ShowSpace( 7, Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
			dat = GetChanData(i,0);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_SetColor(Parameter_Font_R_Bolor);

			if( (i==P_Fill_Value_S)||(i==P_Fill_Value_E) ) {
				fdat = StepToReal(dat,0);
				Display_Parameter_Pro(fdat,str,Search_precision(0));
			} else
				sprintf( str, " %04d ", dat+1);
			GUI_DispStringAt(str,Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
			if (i <= 1)GUI_DispStringAt( FSeq_Mode_Unit[P3k_FSeq_Disp.FSeq_Mode] ,Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
		}
	} else if(DispMode_BROWSE_ITEMS==DispMode) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN)
			sprintf(str, "%s", KeyinBuf);
		else {
			dat = GetChanData(DispCT,0);
			if( (DispCT==P_Fill_Value_S)||(DispCT==P_Fill_Value_E) ) {
				fdat = StepToReal(dat,0);
				Display_Parameter_Pro(fdat,str,Search_precision(0));
			} else
				sprintf( str, " %04d ", dat+1);
		}
		ShowSpace( 7, Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt(str,Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
	}
}
#if Enable_FSEQ_RPT
static const char FSeqEdit_item_Data[P_FSeqEdit_Max][20]	= { "Step:", "Value:", "TRIG OUT:"	};
static const int  FSeqEdit_item_X_Addr[P_FSeqEdit_Max]		= { 30,      10,       10			};
static const int  FSeqEdit_item_Y_Addr[P_FSeqEdit_Max]		= { 45,      90,       115			};
static const int  FSeqEdit_Value_X_Addr[P_FSeqEdit_Max]		= { 130,     150,      160			};
static const char FSeqEdit_space[P_FSeqEdit_Max]			= { 4,       7,        4			};
static const int  FSeqEdit_light_space[P_FSeqEdit_Max]		= { 22,      20,       25			};

void RedrawFSeqEdit(void)
{
	UBYTE i;
	long dat;
	double fdat;
	char str[50];

	unsigned char DARKGRAY_flag;
	if(P3k_FSeq_Disp.FSeq_Max_Step>0xFF00)	DARKGRAY_flag=1;
	else									DARKGRAY_flag=0;
	if(DispMode_SELECT_CH==DispMode) {
		if(DataRedrawFlag&BG_CLEAR_FLAG) {
			Displine(2,79,316,MEM_GRAY);
			Displine(2,80,316,GW_ORANGE_ku);
			Displine(2,81,316,MEM_WHITE);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_DispStringAt( " Data Edit for Fast Sequence ", 45, 20);
		}
		for( i=0 ; i<P_FSeqEdit_Max ; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				continue;
			if(( i==B_DispCT||i==DispCT )&&(DARKGRAY_flag==0)){
				if( i==DispCT ) {
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				}
				Draw_Bar_25(FSeqEdit_item_X_Addr[i]-5,FSeqEdit_item_Y_Addr[i],FSeqEdit_light_space[i]);
			}

			if(i<1)	GUI_SetColor(Parameter_Font_U_Bolor);
			else	GUI_SetColor(Parameter_Font_L_Bolor);

			if (DARKGRAY_flag)GUI_SetColor(MEM_DARKGRAY);

			GUI_DispStringAt( FSeqEdit_item_Data[i], FSeqEdit_item_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
			dat  = GetChanData(i,0);

			if((i==P_FSeqEdit_Step)&&(DARKGRAY_flag)) {
				dat =-1;
			}

			if(i==P_FSeqEdit_Step)
				sprintf( str, " %04d ", dat+1);
			else if( i==P_FSeqEdit_Value) {
				GUI_SetColor(Parameter_Font_R_Bolor);
				if (DARKGRAY_flag)GUI_SetColor(MEM_DARKGRAY);
				GUI_DispStringAt( FSeq_Mode_Unit[P3k_FSeq_Disp.FSeq_Mode],FSeqEdit_Value_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
				fdat = StepToReal(dat,0);
				Display_Parameter_Pro(fdat,str,Search_precision(0));
			} else
				strcpy(  str, onoff_str[dat]);
			GUI_SetColor(Parameter_Font_R_Bolor);
			if (DARKGRAY_flag)GUI_SetColor(MEM_DARKGRAY);

			ShowSpace(FSeqEdit_space[i], FSeqEdit_Value_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, FSeqEdit_Value_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
			if( P_FSeqEdit_Step==i) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				if (DARKGRAY_flag)	sprintf( str, " /   %04d ",0);
				else				sprintf( str, " /   %04d ", GetChanData( P_FSeqEdit_Max , 0)+1);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, FSeqEdit_Value_X_Addr[i]+80, FSeqEdit_item_Y_Addr[i]);
			}
		}
		if (DARKGRAY_flag)	GUI_SetColor(MEM_DARKGRAY);
		else				GUI_SetColor(MEM_ORANGE_ku);
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		sprintf( str, "RPT:%04d", P3k_FSeq_Disp.RPTStep+1);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, FSeqEdit_Value_X_Addr[0]+175, FSeqEdit_item_Y_Addr[0]);
	} else if(DispMode_BROWSE_ITEMS==DispMode) {

		if(DARKGRAY_flag)return;
		if(P_FSeqEdit_Step==DispCT) {
			for( i=P_FSeqEdit_Step+1 ; i<P_FSeqEdit_Max ; i++) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( FSeqEdit_item_Data[i], FSeqEdit_item_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
				dat = GetChanData(i,0);
				if( i==P_FSeqEdit_Value) {
					fdat = StepToReal(dat,0);
					Display_Parameter_Pro(fdat,str,Search_precision(0));
				} else
					strcpy(  str, onoff_str[dat]);
				GUI_SetColor(Parameter_Font_R_Bolor);
				ShowSpace(FSeqEdit_space[i], FSeqEdit_Value_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, FSeqEdit_Value_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
			}
		}
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN)
			sprintf(str, "%s", KeyinBuf);
		else {
			dat = GetChanData(DispCT,0);
			if(DispCT==P_FSeqEdit_Step)
				sprintf( str, " %04d ", dat+1);
			else if( DispCT==P_FSeqEdit_Value) {
				fdat = StepToReal(dat,0);
				Display_Parameter_Pro(fdat,str,Search_precision(0));
			} else
				strcpy(  str, onoff_str[dat]);
		}
		ShowSpace(FSeqEdit_space[DispCT], FSeqEdit_Value_X_Addr[DispCT], FSeqEdit_item_Y_Addr[DispCT]);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, FSeqEdit_Value_X_Addr[DispCT], FSeqEdit_item_Y_Addr[DispCT]);
	}
}

#else

static const char FSeqEdit_item_Data[P_FSeqEdit_Max][20]	= { "Step:", "Value:", "TRIG OUT:"	};
static const int  FSeqEdit_item_X_Addr[P_FSeqEdit_Max]		= { 90,      10,       10			};
static const int  FSeqEdit_item_Y_Addr[P_FSeqEdit_Max]		= { 45,      90,       115			};
static const int  FSeqEdit_Value_X_Addr[P_FSeqEdit_Max]		= { 190,     150,      160			};
static const char FSeqEdit_space[P_FSeqEdit_Max]			= { 4,       7,        4			};
//static const int  FSeqEdit_light_space[P_FSeqEdit_Max]		= { 22,      20,       25			};
static const int  FSeqEdit_light_space[P_FSeqEdit_Max]		= { 22,      35,       32			};

void RedrawFSeqEdit(void)
{
	UBYTE i;
	long dat;
	double fdat;
	char str[50];

	unsigned char DARKGRAY_flag;
	if(P3k_FSeq_Disp.FSeq_Max_Step>0xFF00)
		DARKGRAY_flag=1;
	else
		DARKGRAY_flag=0;
	if(DispMode_SELECT_CH==DispMode) {
		if(DataRedrawFlag&BG_CLEAR_FLAG) {
			Displine(2,79,316,MEM_GRAY);
			Displine(2,80,316,GW_ORANGE_ku);
			Displine(2,81,316,MEM_WHITE);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_DispStringAt( " Data Edit for Fast Sequence ", 45, 20);
		}
		DispScrCurrLoc = DispCT;
		for( i=0 ; i<P_FSeqEdit_Max ; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				continue;

			if(( i == B_DispCT || i == DispCT )&&(DARKGRAY_flag==0)) {
				if( i == DispCT){
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					if((DataRedrawFlag&BG_CLEAR_FLAG)==0){
						Draw_New_Bar_25(FSeqEdit_item_X_Addr[i]-5,FSeqEdit_item_Y_Addr[i],FSeqEdit_light_space[i],1);
						continue;
					}
				}else{
					if((DataRedrawFlag&BG_CLEAR_FLAG)==0){
						Draw_New_Bar_25(FSeqEdit_item_X_Addr[i]-5,FSeqEdit_item_Y_Addr[i],FSeqEdit_light_space[i],0);
						continue;
					}
				}
				if(DataRedrawFlag&BG_CLEAR_FLAG){
					Draw_Bar_25(FSeqEdit_item_X_Addr[i]-5,FSeqEdit_item_Y_Addr[i],FSeqEdit_light_space[i]);
				}				
			}
			

			if(i<1)
				GUI_SetColor(Parameter_Font_U_Bolor);
			else
				GUI_SetColor(Parameter_Font_L_Bolor);

			if (DARKGRAY_flag)GUI_SetColor(MEM_DARKGRAY);


			GUI_DispStringAt( FSeqEdit_item_Data[i], FSeqEdit_item_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
			dat  = GetChanData(i,0);

			if((i==P_FSeqEdit_Step)&&(DARKGRAY_flag)) {
				dat =-1;
			}

			if(i==P_FSeqEdit_Step)
				sprintf( str, " %04d ", dat+1);
			else if( i==P_FSeqEdit_Value) {

				GUI_SetColor(Parameter_Font_R_Bolor);

				if (DARKGRAY_flag)GUI_SetColor(MEM_DARKGRAY);

				GUI_DispStringAt( FSeq_Mode_Unit[P3k_FSeq_Disp.FSeq_Mode],FSeqEdit_Value_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
				fdat = StepToReal(dat,0);
				Display_Parameter_Pro(fdat,str,Search_precision(0));
			} else
				strcpy(  str, onoff_str[dat]);
			GUI_SetColor(Parameter_Font_R_Bolor);

			if (DARKGRAY_flag)GUI_SetColor(MEM_DARKGRAY);

			ShowSpace(FSeqEdit_space[i], FSeqEdit_Value_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, FSeqEdit_Value_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
			if( P_FSeqEdit_Step==i) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				if (DARKGRAY_flag)
					sprintf( str, " /   %04d ",0);
				else

					sprintf( str, " /   %04d ", GetChanData( P_FSeqEdit_Max , 0)+1);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, FSeqEdit_Value_X_Addr[i]+80, FSeqEdit_item_Y_Addr[i]);
			}
		}
	} else if(DispMode_BROWSE_ITEMS==DispMode) {

		if(DARKGRAY_flag)return;
		if(P_FSeqEdit_Step==DispCT) {
			for( i=P_FSeqEdit_Step+1 ; i<P_FSeqEdit_Max ; i++) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( FSeqEdit_item_Data[i], FSeqEdit_item_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
				dat = GetChanData(i,0);
				if( i==P_FSeqEdit_Value) {
					fdat = StepToReal(dat,0);
					Display_Parameter_Pro(fdat,str,Search_precision(0));
				} else
					strcpy(  str, onoff_str[dat]);
				GUI_SetColor(Parameter_Font_R_Bolor);
				ShowSpace(FSeqEdit_space[i], FSeqEdit_Value_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, FSeqEdit_Value_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
			}
		}
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN)
			sprintf(str, "%s", KeyinBuf);
		else {
			dat = GetChanData(DispCT,0);
			if(DispCT==P_FSeqEdit_Step)
				sprintf( str, " %04d ", dat+1);
			else if( DispCT==P_FSeqEdit_Value) {
				fdat = StepToReal(dat,0);
				Display_Parameter_Pro(fdat,str,Search_precision(0));
			} else
				strcpy(  str, onoff_str[dat]);
		}
		ShowSpace(FSeqEdit_space[DispCT], FSeqEdit_Value_X_Addr[DispCT], FSeqEdit_item_Y_Addr[DispCT]);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, FSeqEdit_Value_X_Addr[DispCT], FSeqEdit_item_Y_Addr[DispCT]);
	}
}

#endif

static const char NSeqEdit_item_Data[P_NSeqEdit_Max][20]	= { "Step:", "Value:", "Time:", "Time:", "Time:", "Time:", "LOAD:", "RAMP:", "TRIG OUT:", "PAUSE:" };
static const int NSeqEdit_item_X_Addr[P_NSeqEdit_Max]		= { 90,      10,       10,      10,      10,      10,      10,      10,      160,     160      };
static const int NSeqEdit_item_Y_Addr[P_NSeqEdit_Max]		= { 45,      90,       115,     115,     115,     115,     140,     165,     140,     165      };
static const char NSeqEdit_Time_Unit[4][20]					= { "H:",    "M:",     "s",    "ms"};

#if Enable_NSEQ_Usec
static const int NSeqEdit_Value_X_Addr[P_NSeqEdit_Max]		= { 190,     150,      101,     153,     206,     287,     145,     145,     311,     311      };
static const int NSeqEdit_Time_X_Addr[4]					= 					{  101,     153,     206,     287};
static const int NSeqEdit_light_space[P_NSeqEdit_Max]		= { 22,      20,       10,      10,      10,      10,      29,      29,      29,      29       };
static const char NSeqEdit_space[P_NSeqEdit_Max]			= { 4,       7,        3,       2,       2,       6,       4,       4,       4,       4        };

#else
static const int NSeqEdit_Value_X_Addr[P_NSeqEdit_Max]		= { 190,     150,      110,     165,     220,     280,     145,     145,     311,     311      };
static const int NSeqEdit_Time_X_Addr[4]					= { 110,     165,      220,     280};
static const int NSeqEdit_light_space[P_NSeqEdit_Max]		= { 22,      20,       10,      10,      10,      10,      29,      29,      29,      29       };
static const char NSeqEdit_space[P_NSeqEdit_Max]			= { 4,       7,        3,       2,       2,       3,       4,       4,       4,       4        };

#endif

char Time_Temp = '*';

void RedrawNSeqEdit(void)
{
	int i,previous_i=DispCT;
	char str[50];
	long dat;
	double fdat;
	unsigned char CV_flag=0;
	if(DispMode_SELECT_CH==DispMode) {
		if(DataRedrawFlag&BG_CLEAR_FLAG) {
			Displine(2,79,316,MEM_GRAY);
			Displine(2,80,316,GW_ORANGE_ku);
			Displine(2,81,316,MEM_WHITE);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_DispStringAt( "   Data Edit for Normal Sequence ", 15, 20);
		}
#if Enable_NSEQ_Usec
		unsigned long Ramp_mS_Time;
		UWORD N_Hour,N_Min,N_Sec,N_MUsec;
		UBYTE Dis_flag = 2+1; // sec(bit1)  /msec(bit0)
		N_Hour = GetChanData(2,0);
		N_Min = GetChanData(3,0);
		N_Sec= GetChanData(4,0);
		N_MUsec = GetChanData(5,0);

		Ramp_mS_Time = N_Hour*60*60*1000 + N_Min*60*1000 + N_Sec*1000 + (N_MUsec/20);

		/*
		1uS 		~	60mS		1uS
		60mS		~	600mS		10uS
		600mS		~	6S			100uS
		6S			~	1min		1mS
		1min		~	100min		100mS
		100min		~	1000min 	1S
		1000min 		~	10000min	10S
		10000min	~	1000H		1min
		*/
		if(Ramp_mS_Time>10000*60*1000) {	/* 10000 Minute ~ 1000 Hour */
			Dis_flag = 0;
		} else if(Ramp_mS_Time>1000*60*1000) {	/* 1000 Minute ~ 10000 Minute	*/
			Dis_flag=2;
		} else if(Ramp_mS_Time>100*60*1000) {	/* 100 Minute ~1000 Minute	*/
			Dis_flag=2;
		} else if(Ramp_mS_Time>1*60*1000) { /* 1 Minute ~ 100 Minute	*/
			Dis_flag=3;
		} else {						/* 1 us ~ 60 ms */
			Dis_flag=3;
		}
#endif		

		for( i=0; i<P_NSeqEdit_Max; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				continue;

			if( (i==B_DispCT||i==DispCT)&&(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step)) {
				if(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode==CV_MODE) {
					if( (previous_i>=i) && (i==P_NSeqEdit_Ramp) ) {
						previous_i=i;
						i=P_NSeqEdit_Load;
						DispCT=i;
					} else if ( (previous_i<=i) && (i==P_NSeqEdit_Ramp)  ) {
						i=P_NSeqEdit_Trig;
						DispCT=i;
						previous_i=i;
					}

					if( (i==DispCT) && (i!=P_NSeqEdit_Ramp)	) {
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					}
					CV_flag =1;
				} else {
					if(i == DispCT)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					CV_flag =0;

				}
				previous_i=i;

				//GUI_GotoXY(NSeqEdit_item_X_Addr[i]-5,NSeqEdit_item_Y_Addr[i]);

				if(i==P_NSeqEdit_Time_H){
					//GUI_DispChars(' ',20);
					Draw_Bar_25(NSeqEdit_item_X_Addr[i]-5,NSeqEdit_item_Y_Addr[i],20);
				}else{
					//GUI_DispChars(' ',NSeqEdit_light_space[i]);
					Draw_Bar_25(NSeqEdit_item_X_Addr[i]-5,NSeqEdit_item_Y_Addr[i],NSeqEdit_light_space[i]);
				}
			}

			if(i<1)
				GUI_SetColor(Parameter_Font_U_Bolor);
			else
				GUI_SetColor(Parameter_Font_L_Bolor);

			if((0==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step) ||( (P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode==CV_MODE) && (i==P_NSeqEdit_Ramp) ) )
				GUI_SetColor(MEM_DARKGRAY);

			GUI_DispStringAt( NSeqEdit_item_Data[i], NSeqEdit_item_X_Addr[i], NSeqEdit_item_Y_Addr[i]);
			dat  = GetChanData(i,0);
#if Enable_NSEQ_Usec
			
			if(i==P_NSeqEdit_Step)
				sprintf( str, " %04d ", dat);
			else if( i==P_NSeqEdit_Value) {
				fdat = StepToReal(dat,0);
				Display_Parameter_Pro(fdat,str,Search_precision(0));
			} else if(i==P_NSeqEdit_Time_H)
				sprintf( str, " %03d ", dat);
			else if(i==P_NSeqEdit_Time_mS) {
				fdat = dat*0.05;
				Display_Parameter_Pro(fdat,str,2);
			} else if( i==P_NSeqEdit_Time_M||i==P_NSeqEdit_Time_S)
				sprintf( str, " %02d ", dat);
			else if ((i==P_NSeqEdit_Ramp)&&(CV_flag))
				strcpy(  str, onoff_str[0]);
			else
				strcpy(  str, onoff_str[dat]);


#else
			if(i==P_NSeqEdit_Step)
				sprintf( str, " %04d ", dat);
			else if( i==P_NSeqEdit_Value) {
				fdat = StepToReal(dat,0);
				Display_Parameter_Pro(fdat,str,Search_precision(0));
			} else if( i==P_NSeqEdit_Time_H||i==P_NSeqEdit_Time_mS)
				sprintf( str, " %03d ", dat);
			else if( i==P_NSeqEdit_Time_M||i==P_NSeqEdit_Time_S)
				sprintf( str, " %02d ", dat);
			else if ((i==P_NSeqEdit_Ramp)&&(CV_flag))
				strcpy(  str, onoff_str[0]);
			else
				strcpy(  str, onoff_str[dat]);
			
#endif			
			
			if((0==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step) ||( (P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode==CV_MODE) && (i==P_NSeqEdit_Ramp) ) )
				GUI_SetColor(MEM_DARKGRAY);
#if Enable_NSEQ_Usec
			else if((i==P_NSeqEdit_Time_S)&&((Dis_flag&0x02)==0))
				GUI_SetColor(MEM_DARKGRAY);
			else if((i==P_NSeqEdit_Time_mS)&&((Dis_flag&0x01)==0))
				GUI_SetColor(MEM_DARKGRAY);
#endif			
			else
				GUI_SetColor(Parameter_Font_R_Bolor);


			ShowSpace(NSeqEdit_space[i], NSeqEdit_Value_X_Addr[i], NSeqEdit_item_Y_Addr[i]);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, NSeqEdit_Value_X_Addr[i], NSeqEdit_item_Y_Addr[i]);

			if( P_NSeqEdit_Step==i) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				sprintf( str, " /   %04d ", GetChanData( P_NSeqEdit_Max , 0));
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, NSeqEdit_Value_X_Addr[i]+80, NSeqEdit_item_Y_Addr[i]);
			}

			if( i==P_NSeqEdit_Value) {
				if(CC_MODE==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode)
					sprintf( str, " A    ");
				else if(CR_MODE==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode)
					sprintf( str, " mS ");
				else if(CV_MODE==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode)
					sprintf( str, " V    ");
				else
					sprintf( str, " W    ");
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( str, NSeqEdit_Value_X_Addr[i], NSeqEdit_item_Y_Addr[i]);
			}

			if( (i>=P_NSeqEdit_Time_H)&&(i<=P_NSeqEdit_Time_mS) ) {
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( NSeqEdit_Time_Unit[i-P_NSeqEdit_Time_H], NSeqEdit_Time_X_Addr[i-P_NSeqEdit_Time_H], NSeqEdit_item_Y_Addr[i] );
				if( (DispCT>=P_NSeqEdit_Time_H)&&(DispCT<=P_NSeqEdit_Time_mS) ) {
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					if(0==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step)

						GUI_SetColor(MEM_DARKGRAY);
					else
						GUI_SetColor(Parameter_Font_L_Bolor);

					//GUI_GotoXY(NSeqEdit_item_X_Addr[i]-5,NSeqEdit_item_Y_Addr[i]);
					//GUI_DispChars(' ',NSeqEdit_light_space[i]);
					Draw_Bar_25(NSeqEdit_item_X_Addr[i]-5,NSeqEdit_item_Y_Addr[i],NSeqEdit_light_space[i]);
					GUI_DispStringAt( NSeqEdit_item_Data[i], NSeqEdit_item_X_Addr[i], NSeqEdit_item_Y_Addr[i]);
				}
			}

		}
	} else if(DispMode_BROWSE_ITEMS==DispMode) {
		if(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode==CV_MODE)
			CV_flag =1;

		if((P_NSeqEdit_Step==DispCT)&&(0!=P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step)) {
			for( i=P_NSeqEdit_Step+1 ; i<P_NSeqEdit_Max ; i++) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( NSeqEdit_item_Data[i], NSeqEdit_item_X_Addr[i], NSeqEdit_item_Y_Addr[i]);
				dat = GetChanData(i,0);

#if Enable_NSEQ_Usec
				if(i==P_NSeqEdit_Value) {
					fdat = StepToReal(dat,0);
					Display_Parameter_Pro(fdat,str,Search_precision(0));
				} else if( i==P_NSeqEdit_Time_H)
					sprintf( str, " %03d ", dat);
				else if(i==P_NSeqEdit_Time_mS) {
					fdat = dat*0.05;
					Display_Parameter_Pro(fdat,str,2);
				} else if( i==P_NSeqEdit_Time_M||i==P_NSeqEdit_Time_S)
					sprintf( str, " %02d ", dat);
				else if ((i==P_NSeqEdit_Ramp)&&(CV_flag))
					strcpy(  str, onoff_str[0]);
				else
					strcpy(  str, onoff_str[dat]);
#else
				if(i==P_NSeqEdit_Value) {
					fdat = StepToReal(dat,0);
					Display_Parameter_Pro(fdat,str,Search_precision(0));
				} else if( i==P_NSeqEdit_Time_H||i==P_NSeqEdit_Time_mS)
					sprintf( str, " %03d ", dat);
				else if( i==P_NSeqEdit_Time_M||i==P_NSeqEdit_Time_S)
					sprintf( str, " %02d ", dat);
				else if ((i==P_NSeqEdit_Ramp)&&(CV_flag))
					strcpy(  str, onoff_str[0]);
				else
					strcpy(  str, onoff_str[dat]);
#endif
				GUI_SetColor(Parameter_Font_R_Bolor);
				ShowSpace(NSeqEdit_space[i], NSeqEdit_Value_X_Addr[i], NSeqEdit_item_Y_Addr[i]);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, NSeqEdit_Value_X_Addr[i], NSeqEdit_item_Y_Addr[i]);
			}
		}

		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(0!=P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step) {
			if(KeyInFlag & DIGI_KEY_IN)
				sprintf(str, "%s", KeyinBuf);
			else {
				dat = GetChanData(DispCT,0);
				if(DispCT==P_NSeqEdit_Step)
					sprintf( str, " %04d ", dat);
				else if( DispCT==P_NSeqEdit_Value) {
					fdat = StepToReal(dat,0);
					Display_Parameter_Pro(fdat,str,Search_precision(0));
#if Enable_NSEQ_Usec
				} else if(DispCT==P_NSeqEdit_Time_H)
					sprintf( str, " %03d ", dat);
				else if(DispCT==P_NSeqEdit_Time_mS) {
					fdat = dat*0.05;
					Display_Parameter_Pro(fdat,str,2);
				}
#else
				}
				else if( DispCT==P_NSeqEdit_Time_H||DispCT==P_NSeqEdit_Time_mS)
					sprintf( str, " %03d ", dat);
#endif				
				else if( DispCT==P_NSeqEdit_Time_M||DispCT==P_NSeqEdit_Time_S)
					sprintf( str, " %02d ", dat);
				else
					strcpy(  str, onoff_str[dat]);
			}

			ShowSpace(NSeqEdit_space[DispCT], NSeqEdit_Value_X_Addr[DispCT], NSeqEdit_item_Y_Addr[DispCT]);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, NSeqEdit_Value_X_Addr[DispCT], NSeqEdit_item_Y_Addr[DispCT]);
		}
	}
}

static const char FSeq_item_Data[P_FSeq_Max][20]	= { "Memo:", "Mode:", "Range:", "Loop:", "Time Base:", "Last Load:", "Last:", "RPTSTEP:" };
static const int  FSeq_item_X_Addr[P_FSeq_Max]		= { 10,		 10,	  10,       10,      10,           160,          160,         160        };
static const int  FSeq_item_Y_Addr[P_FSeq_Max]		= { 65,      90,      115,      140,     165,          90,           115,         140        };
static const int  FSeq_Value_X_Addr[P_FSeq_Max]		= { 80,      118,     130,      128,     190,          310,          283,         310        };
static const char FSeq_space[P_FSeq_Max]			= { 2,       3,       4,        5,       7,            4,            7,           4          };
static const int  FSeq_light_space[P_FSeq_Max]		= { 22,      20,      24,       24,      40,           29,           29,          29         };
static const char FSeq_Mode_Item[2][20]				= { " CC ", " CR "};
static const char FSeq_Range_Item[4][20]			= { " ILVL ", " IHVL ", " ILVH ", " IHVH " };
static const char FSeq_Range_Item_CR[4][20]			= { " ILVL ", " SHVL ", " SLVH ", " IHVH " };

void RedrawSeqFast(void)
{
	UBYTE i;
	char str[50];
	long dat;
	double fdat;

	if(DispMode_SELECT_CH==DispMode) {
		if(DataRedrawFlag&BG_CLEAR_FLAG) {
			Displine(2,55,316,MEM_GRAY);
			Displine(2,56,316,GW_ORANGE_ku);
			Displine(2,57,316,MEM_WHITE);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_DispStringAt( " Timing Edit for Fast Sequence ", 30, 25);
		}

		for( i=0 ; i<P_FSeq_Max ; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);

			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				continue;

			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				//GUI_GotoXY(FSeq_item_X_Addr[i]-5,FSeq_item_Y_Addr[i]);
				//GUI_DispChars(' ',FSeq_light_space[i]);
				Draw_Bar_25(FSeq_item_X_Addr[i]-5,FSeq_item_Y_Addr[i],FSeq_light_space[i]);
			}

			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( FSeq_item_Data[i], FSeq_item_X_Addr[i], FSeq_item_Y_Addr[i]);
			dat = GetChanData( i , 0);

			if( i==P_FSeq_Memo) {
				if(P3k_FSeq_Disp.FSeq_Memo[0]==0)
					sprintf( str, " No Memo ");
				else
					sprintf( str, " %s ",P3k_FSeq_Disp.FSeq_Memo);
			} else if( i==P_FSeq_Mode)
				strcpy(  str, FSeq_Mode_Item[dat]);
			else if( i==P_FSeq_Range){
				if(P3k_FSeq_Disp.FSeq_Mode!=CR_MODE)
					strcpy(  str, FSeq_Range_Item[dat]);
				else
					strcpy(  str, FSeq_Range_Item_CR[dat]);
			}else if( i==P_FSeq_Loop) {
				if(dat)
					sprintf( str, " %04d ", dat);
				else
					sprintf( str, " Infinity ");
			} else if(i==P_FSeq_TimeBase) {
				fdat = StepToReal(dat,i);
				Display_Parameter_Pro(fdat,str,Search_precision(i));
			} else if(i==P_FSeq_Last_Load)
				strcpy( str, onoff_str[dat]);
			else if(i==P_FSeq_Last_Set) {
				GUI_SetColor(Parameter_Font_R_Bolor);
				GUI_DispStringAt( FSeq_Mode_Unit[GetChanData( 1 , 0)], FSeq_Value_X_Addr[i], FSeq_item_Y_Addr[i]);

				fdat = StepToReal(dat,i);
				Display_Parameter_Pro(fdat,str,Search_precision(i));
			} else { /*P_FSeq_RptStep*/
				sprintf(str, " %04d ", dat+1);
			}

			GUI_SetColor(Parameter_Font_R_Bolor);

			if( i==P_FSeq_Memo) {
				GUI_SetTextAlign(GUI_TA_RIGHT);
				//GUI_GotoXY(FSeq_Value_X_Addr[i], FSeq_item_Y_Addr[i]);
				//GUI_DispChars(' ',46);
				Draw_Bar_25(FSeq_Value_X_Addr[i], FSeq_item_Y_Addr[i],46);
				GUI_SetTextAlign(GUI_TA_LEFT);
			} else {
				ShowSpace(FSeq_space[i], FSeq_Value_X_Addr[i], FSeq_item_Y_Addr[i]);
				GUI_SetTextAlign(GUI_TA_RIGHT);
			}

			GUI_DispStringAt( str, FSeq_Value_X_Addr[i], FSeq_item_Y_Addr[i]);

			if(P_FSeq_TimeBase==i) {
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( " ms ", FSeq_Value_X_Addr[P_FSeq_TimeBase]+2, FSeq_item_Y_Addr[P_FSeq_TimeBase]);
			}
		}
	} else if(DispMode_BROWSE_ITEMS==DispMode) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN)
			sprintf(str, "%s", KeyinBuf);
		else {
			dat = GetChanData(DispCT,0);
			if(DispCT==P_FSeq_Memo) {
				if(P3k_FSeq_Disp.FSeq_Memo[0]==0)
					sprintf( str, " No Memo ");
				else
					sprintf( str, " %s ",P3k_FSeq_Disp.FSeq_Memo);
			} else if(DispCT==P_FSeq_Mode)
				strcpy(  str, FSeq_Mode_Item[dat]);
			else if(DispCT==P_FSeq_Range){
				if(P3k_FSeq_Disp.FSeq_Mode!=CR_MODE)
					strcpy(  str, FSeq_Range_Item[dat]);
				else
					strcpy(  str, FSeq_Range_Item_CR[dat]);
			}else if(DispCT==P_FSeq_Loop) {
				if(dat)
					sprintf( str, " %04d ", dat);
				else
					sprintf( str, " Infinity ");
			} else if(DispCT==P_FSeq_TimeBase) {
				fdat = StepToReal(dat,DispCT);
				Display_Parameter_Pro(fdat,str,Search_precision(DispCT));
			} else if(DispCT==P_FSeq_Last_Load)
				strcpy( str, onoff_str[dat]);
			else if(DispCT==P_FSeq_Last_Set) {
				fdat = StepToReal(dat,DispCT);
				Display_Parameter_Pro(fdat,str,Search_precision(DispCT));
			} else { /*P_FSeq_RptStep*/
				sprintf(str, " %04d ", dat+1);
			}
		}
		if( DispCT==P_FSeq_Memo) {
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_GotoXY(FSeq_Value_X_Addr[DispCT], FSeq_item_Y_Addr[DispCT]);
			GUI_DispChars(' ',46);
			GUI_SetTextAlign(GUI_TA_LEFT);
		} else {
			ShowSpace(FSeq_space[DispCT], FSeq_Value_X_Addr[DispCT], FSeq_item_Y_Addr[DispCT]);
			GUI_SetTextAlign(GUI_TA_RIGHT);
		}
		GUI_DispStringAt( str, FSeq_Value_X_Addr[DispCT], FSeq_item_Y_Addr[DispCT]);
	}
}
#else
void RedrawCCModeData(void)
{
	long dat;
	int i,j;
	char Total_Display_Item,Sta_Dyna,str[20],ScrollBar_Flag=0,space_Flag=0;
	double fdat;

	P3k_Data_Str 	*Data_tmp	= &P3k_Chan_Data;
	P3k_Disp_Str 	*Disp_tmp	= &P3k_Disp_Data;

	if(Data_tmp->CONF.Ext_Setting.Control) {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt( cc_sta[0]	, Disp_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetColor(Parameter_Font_R_Bolor);
		dat = (ptrMODEL_TYPE->CC)[10*Disp_tmp->IRange].Max;
		fdat = StepToReal(dat,0);
		fdat /= 1.02;					/*Max Setting(1.05) ->Setting(1) */
		fdat *= p3k_Measure_Data.Ext_Percent;
		Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[10*Disp_tmp->IRange].precision);
		ShowSpace( 7, Para_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_LEFT);
		GUI_DispStringAt( cc_sta_unit[0], Unit_Start_X, Disp_Start_Y1+0*Disp_Interval);
		return;
	}

	Sta_Dyna = Disp_tmp->CC.STADYNA;

	if(Sta_Dyna)
		Total_Display_Item = CCCR_Dyn_Max;
	else
		Total_Display_Item = CCCR_Sta_Max;

	if(DispMode <= DispMode_BROWSE_ITEMS) {
		for(i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {

			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if((DispScrCurrLoc == DispScrEndCT)||(DispScrCurrLoc == DispScrStartCT)) {
				if( (ScrollBar_Flag==0)&&(Total_Display_Item>3) ) {
					ShowScrollBar_Other(Scroll_Bar_Start_X,Disp_Start_Y1,Total_Display_Item,Disp_Item_Num0,Disp_Interval,Scroll_Bar_Width,DispScrStartCT);
					GUI_SetBkColor(Parameter_Bottom_Bolor);
					ScrollBar_Flag=1;
				}
				if( i == DispScrCurrLoc)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(Disp_Start_X,Disp_Start_Y1+j*Disp_Interval);
				GUI_DispChars(' ',HiLight_Length);
			} else {
				if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&(DispMode == DispMode_BROWSE_ITEMS) && ( i != B_DispCT && i!= DispScrCurrLoc ) )
					continue;
				if((DispMode != DispMode_SELECT_CH) && (i == DispScrCurrLoc || i == B_DispCT) ) {
					if( i==DispScrCurrLoc)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					GUI_GotoXY(Disp_Start_X,Disp_Start_Y1+j*Disp_Interval);
					GUI_DispChars(' ',HiLight_Length);
				}
			}

			GUI_SetColor(Parameter_Font_L_Bolor);

			if(Sta_Dyna) {
				if(Disp_tmp->CONF.Dyna_Level && !Disp_tmp->CONF.Dyna_Time)
					GUI_DispStringAt( ccr_dyna_percent[i], Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
				else if(!Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
					GUI_DispStringAt( ccr_dyna_freq_duty[i], Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
				else if(Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
					GUI_DispStringAt( ccr_dyna_percent_freq_duty[i], Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
				else
					GUI_DispStringAt( ccr_dyna[i], Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
			} else
				GUI_DispStringAt( cc_sta[i],   Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);

			GUI_SetColor(Parameter_Font_R_Bolor);
			dat = GetChanData(i,0);
			fdat = StepToReal(dat,i);

			if(((Sta_Dyna==Function_Dynamic)&&(i==CCCR_Dyn_Add_CV))||((Sta_Dyna==Function_Static)&&(i==CCCR_Sta_Add_CV))) {
				fdat=StepToReal(dat,i);
				if(fdat < 0)
					sprintf( str, " OFF ");
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[Disp_tmp->VRange*3].precision);
			} else if(((Sta_Dyna==Function_Dynamic)&&(i==CCCR_Dyn_CV_Response))||((Sta_Dyna==Function_Static)&&(i==CCCR_Sta_CV_Response))) {
				sprintf( str,cxcv_reponse[dat]);
			} else {
				if(((Disp_tmp->CONF.Dyna_Level) && (i == CCCR_Dyn_L2) && (Disp_tmp->CC.STADYNA==Function_Dynamic)) || ((Disp_tmp->CONF.Dyna_Time) && (i == CCCR_Dyn_T2) && (Disp_tmp->CC.STADYNA==Function_Dynamic)))
					Display_Parameter_Pro(fdat,str,1);
				else if((i == CCCR_Sta_SR) && (!Disp_tmp->CC.STADYNA==Function_Dynamic))
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[i+(10*Disp_tmp->IRange)].precision);
				else if(((i == CCCR_Dyn_SRUP) || (i == CCCR_Dyn_SRDN)) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) {
					if(i == CCCR_Dyn_SRUP)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[i+(10*Disp_tmp->IRange)].precision);
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[i+(10*Disp_tmp->IRange)].precision);
				} else if((i == CCCR_Dyn_T1) && (Disp_tmp->CC.STADYNA==Function_Dynamic) && (Disp_tmp->CONF.Dyna_Time)) {
					if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency_Range == 3)
						Display_Parameter_Pro(fdat,str,1);
					else
						Display_Parameter_Pro(fdat,str,0);
				} else if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].T1_RANGE && (i == CCCR_Dyn_T1) && (Disp_tmp->CC.STADYNA==Function_Dynamic))
					Display_Parameter_Pro(fdat,str,0);
				else if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].T2_RANGE && (i == CCCR_Dyn_T2) && (Disp_tmp->CC.STADYNA==Function_Dynamic) && (!Disp_tmp->CONF.Dyna_Time))
					Display_Parameter_Pro(fdat,str,0);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[i+(10*Disp_tmp->IRange)+(4*Disp_tmp->CC.STADYNA)].precision);
			}

			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+j*Disp_Interval);
			GUI_SetTextAlign(GUI_TA_LEFT);
			if(Sta_Dyna) {
				if(Disp_tmp->CONF.Dyna_Level && !Disp_tmp->CONF.Dyna_Time)
					GUI_DispStringAt( cc_dyna_percent_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
				else if(!Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
					GUI_DispStringAt( cc_dyna_freq_duty_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
				else if(Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
					GUI_DispStringAt( cc_dyna_percent_freq_duty_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
				else
					GUI_DispStringAt( cc_dyna_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
			} else
				GUI_DispStringAt( cc_sta_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		dat = GetChanData(DispScrCurrLoc,0);

		if( KeyInFlag & DIGI_KEY_IN )
			sprintf( str, " %s " , KeyinBuf );
		else {
			getcursortime = 1;
			fdat = StepToReal(dat, DispScrCurrLoc);
			if(((Sta_Dyna==Function_Dynamic)&&(DispScrCurrLoc==CCCR_Dyn_Add_CV))||((Sta_Dyna==Function_Static)&&(DispScrCurrLoc==CCCR_Sta_Add_CV))) {
				fdat = StepToReal(dat,DispScrCurrLoc);
				if(fdat < 0)
					sprintf( str, " OFF ");
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[Disp_tmp->VRange*3].precision);
			} else if(((Sta_Dyna==Function_Dynamic)&&(DispScrCurrLoc==CCCR_Dyn_CV_Response))||((Sta_Dyna==Function_Static)&&(DispScrCurrLoc==CCCR_Sta_CV_Response))) {
				sprintf( str,cxcv_reponse[dat]);
				space_Flag = 1;
			} else {
				if(((Disp_tmp->CONF.Dyna_Level) && (DispScrCurrLoc == CCCR_Dyn_L2) && (Disp_tmp->CC.STADYNA==Function_Dynamic)) || ((Disp_tmp->CONF.Dyna_Time) && (DispScrCurrLoc == CCCR_Dyn_T2) && (Disp_tmp->CC.STADYNA==Function_Dynamic)))
					Display_Parameter_Pro(fdat,str,1);
				else if((DispScrCurrLoc == CCCR_Sta_SR) && (!Disp_tmp->CC.STADYNA==Function_Dynamic))
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[2+(10*Disp_tmp->IRange)].precision);
				else if(((DispScrCurrLoc == CCCR_Dyn_SRUP) || (DispScrCurrLoc == CCCR_Dyn_SRDN)) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) {
					if(DispScrCurrLoc == CCCR_Dyn_SRUP)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[2+(10*Disp_tmp->IRange)].precision);
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[2+(10*Disp_tmp->IRange)].precision);
				} else if((DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CC.STADYNA==Function_Dynamic) && (Disp_tmp->CONF.Dyna_Time)) {
					if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].Frequency_Range == 3)
						Display_Parameter_Pro(fdat,str,1);
					else
						Display_Parameter_Pro(fdat,str,0);
				} else if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].T1_RANGE && (DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CC.STADYNA==Function_Dynamic))
					Display_Parameter_Pro(fdat,str,0);
				else if(Disp_tmp->CC.DYNA[Disp_tmp->IRange].T2_RANGE && (DispScrCurrLoc == CCCR_Dyn_T2) && (Disp_tmp->CC.STADYNA==Function_Dynamic) && (!Disp_tmp->CONF.Dyna_Time))
					Display_Parameter_Pro(fdat,str,0);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[DispScrCurrLoc+(10*Disp_tmp->IRange)+(4*Disp_tmp->CC.STADYNA)].precision);
			}
			getcursortime = 0;
		}
		if(space_Flag)
			ShowSpace( 4, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		else
			ShowSpace( 7, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);

		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		if(Disp_tmp->CONF.Knob_Status)
			Draw_Cursor_Line();
		if((DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CC.STADYNA==Function_Dynamic) && (Disp_tmp->CONF.Dyna_Time)&&(DispScrEndCT>4)) {
			dat = GetChanData(CCCR_Dyn_T2,0);
			fdat = StepToReal(dat,CCCR_Dyn_T2);
			Display_Parameter_Pro(fdat,str,1);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(Parameter_Font_R_Bolor);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT+1)*Disp_Interval);
		}
		_CursorResolution = StepToReal(1, DispScrCurrLoc);
	}
}

void RedrawCRModeData(void)
{
	long dat;
	int i,j;
	char Total_Display_Item,Sta_Dyna,str[20],ScrollBar_Flag=0,space_Flag=0;
	double fdat;

	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	if(Data_tmp->CONF.Ext_Setting.Control) {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt( cr_sta[0]	, Disp_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetColor(Parameter_Font_R_Bolor);
		dat = (ptrMODEL_TYPE->CR)[10*Disp_tmp->IRange].Max;
		fdat = StepToReal(dat,0);
		fdat /= 1.02;		/*Max Setting(1.05) ->Setting(1) */
		fdat *= p3k_Measure_Data.Ext_Percent;
		if(Data_tmp->CONF.D_CR_Unit)
			Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[10*Disp_tmp->IRange].precision);
		else {
			if(fdat)
				Display_Parameter_Pro((1000.0/fdat),str,7);
			else
				sprintf(str," OPEN ");
		}
		ShowSpace( 7, Para_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_LEFT);
		if(Data_tmp->CONF.D_CR_Unit)
			GUI_DispStringAt( cg_sta_unit[0], Unit_Start_X, Disp_Start_Y1+0*Disp_Interval);
		else
			GUI_DispStringAt( cr_sta_unit[0], Unit_Start_X, Disp_Start_Y1+0*Disp_Interval);
		return;
	}

	Sta_Dyna = Disp_tmp->CR.STADYNA;

	if(Sta_Dyna)
		Total_Display_Item = CCCR_Dyn_Max;
	else
		Total_Display_Item = CCCR_Sta_Max;

	if( DispMode <= DispMode_BROWSE_ITEMS) {
		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if((DispScrCurrLoc == DispScrEndCT)||(DispScrCurrLoc == DispScrStartCT)) {
				if( (ScrollBar_Flag==0)&&(Total_Display_Item>3) ) {
					ShowScrollBar_Other(Scroll_Bar_Start_X,Disp_Start_Y1,Total_Display_Item,Disp_Item_Num0,Disp_Interval,Scroll_Bar_Width,DispScrStartCT);
					GUI_SetBkColor(Parameter_Bottom_Bolor);
					ScrollBar_Flag=1;
				}
				if( i == DispScrCurrLoc)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(Disp_Start_X, Disp_Start_Y1+ j*Disp_Interval);
				GUI_DispChars(' ',HiLight_Length);
			} else {
				if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&(DispMode == DispMode_BROWSE_ITEMS) && ( i != B_DispCT && i != DispScrCurrLoc ) )
					continue;
				if(DispMode != DispMode_SELECT_CH && ( i == B_DispCT || i == DispScrCurrLoc ) ) {
					if( i == DispScrCurrLoc)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					GUI_GotoXY( Disp_Start_X, Disp_Start_Y1+ j*Disp_Interval);
					GUI_DispChars(' ', HiLight_Length);
				}
			}
			GUI_SetColor(Parameter_Font_L_Bolor);
			if(Sta_Dyna) {
				if(Disp_tmp->CONF.Dyna_Level && !Disp_tmp->CONF.Dyna_Time)
					GUI_DispStringAt( ccr_dyna_percent[i], Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
				else if(!Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
					GUI_DispStringAt( ccr_dyna_freq_duty[i], Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
				else if(Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
					GUI_DispStringAt( ccr_dyna_percent_freq_duty[i], Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
				else
					GUI_DispStringAt( ccr_dyna[i], Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
			} else
				GUI_DispStringAt( cr_sta[i]	, Disp_Start_X, Disp_Start_Y1+j*Disp_Interval );
			GUI_SetColor(Parameter_Font_R_Bolor);
			dat = GetChanData(i,0);
			fdat = StepToReal(dat,i);
			if(((Sta_Dyna==Function_Dynamic)&&(i==CCCR_Dyn_Add_CV))||((Sta_Dyna==Function_Static)&&(i==CCCR_Sta_Add_CV))) {
				fdat=StepToReal(dat,i);
				if(fdat < 0)
					sprintf( str, " OFF ");
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[Disp_tmp->VRange*3].precision);
			} else if(((Sta_Dyna==Function_Dynamic)&&(i==CCCR_Dyn_CV_Response))||((Sta_Dyna==Function_Static)&&(i==CCCR_Sta_CV_Response))) {
				sprintf( str,cxcv_reponse[dat]);
			} else {
				if(((Disp_tmp->CONF.Dyna_Level) && (i == CCCR_Dyn_L2) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) || ((Disp_tmp->CONF.Dyna_Time) && (i == CCCR_Dyn_T2) && (Disp_tmp->CR.STADYNA==Function_Dynamic)))
					Display_Parameter_Pro(fdat,str,1);
				else if((i == CCCR_Sta_SR) && (!Disp_tmp->CR.STADYNA==Function_Dynamic))
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR[i+(10*Disp_tmp->IRange)].precision));
				else if(((i == CCCR_Dyn_SRUP) || (i == CCCR_Dyn_SRDN)) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) {
					if(i == CCCR_Dyn_SRUP)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR[i+(10*Disp_tmp->IRange)].precision));
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR[i+(10*Disp_tmp->IRange)].precision));
				} else if((i == CCCR_Dyn_T1) && (Disp_tmp->CR.STADYNA==Function_Dynamic) && (Disp_tmp->CONF.Dyna_Time)) {
					if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency_Range == 3)
						Display_Parameter_Pro(fdat,str,1);
					else
						Display_Parameter_Pro(fdat,str,0);
				} else if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].T1_RANGE && (i == CCCR_Dyn_T1) && (Disp_tmp->CR.STADYNA==Function_Dynamic))
					Display_Parameter_Pro(fdat,str,0);
				else if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].T2_RANGE && (i == CCCR_Dyn_T2) && (Disp_tmp->CR.STADYNA==Function_Dynamic) && (!Disp_tmp->CONF.Dyna_Time))
					Display_Parameter_Pro(fdat,str,0);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[i+(10*Disp_tmp->IRange)+(4*Disp_tmp->CR.STADYNA)].precision);

				if( (Data_tmp->CONF.D_CR_Unit==OHM_Unit)&&(i<=CCCR_Dyn_L2) ) {
					if((Disp_tmp->CONF.Dyna_Level) && (i == CCCR_Dyn_L2) && (Disp_tmp->CR.STADYNA==Function_Dynamic))
						Display_Parameter_Pro(fdat,str,1);
					else {
						if(fdat)
							Display_Parameter_Pro((1000.0/fdat),str,7);
						else
							sprintf(str," OPEN ");
					}
				}
			}
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+j*Disp_Interval);
			GUI_SetTextAlign(GUI_TA_LEFT);
			if(Data_tmp->CONF.D_CR_Unit) {
				if(Sta_Dyna) {
					if(Disp_tmp->CONF.Dyna_Level && !Disp_tmp->CONF.Dyna_Time)
						GUI_DispStringAt( cg_dyna_percent_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
					else if(!Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
						GUI_DispStringAt( cg_dyna_freq_duty_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
					else if(Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
						GUI_DispStringAt( cg_dyna_percent_freq_duty_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
					else
						GUI_DispStringAt( cg_dyna_unit[i]	, Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
				} else
					GUI_DispStringAt( cg_sta_unit[i]	, Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
			} else {
				if(Sta_Dyna) {
					if(Disp_tmp->CONF.Dyna_Level && !Disp_tmp->CONF.Dyna_Time)
						GUI_DispStringAt( cr_dyna_percent_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
					else if(!Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
						GUI_DispStringAt( cr_dyna_freq_duty_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
					else if(Disp_tmp->CONF.Dyna_Level && Disp_tmp->CONF.Dyna_Time)
						GUI_DispStringAt( cr_dyna_percent_freq_duty_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
					else
						GUI_DispStringAt( cr_dyna_unit[i]	, Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
				} else
					GUI_DispStringAt( cr_sta_unit[i]	, Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		dat = GetChanData(DispScrCurrLoc,0);

		if( KeyInFlag & DIGI_KEY_IN )
			sprintf( str, " %s " , KeyinBuf );
		else {
			getcursortime = 1;
			fdat = StepToReal(dat,DispScrCurrLoc);

			if(((Sta_Dyna==Function_Dynamic)&&(DispScrCurrLoc==CCCR_Dyn_Add_CV))||((Sta_Dyna==Function_Static)&&(DispScrCurrLoc==CCCR_Sta_Add_CV))) {
				fdat = StepToReal(dat,DispScrCurrLoc);
				if(fdat < 0)
					sprintf( str, " OFF ");
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[Disp_tmp->VRange*3].precision);
			} else if(((Sta_Dyna==Function_Dynamic)&&(DispScrCurrLoc==CCCR_Dyn_CV_Response))||((Sta_Dyna==Function_Static)&&(DispScrCurrLoc==CCCR_Sta_CV_Response))) {
				sprintf( str,cxcv_reponse[dat]);
				space_Flag = 1;
			} else {
				if(((Disp_tmp->CONF.Dyna_Level) && (DispScrCurrLoc == CCCR_Dyn_L2) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) || ((Disp_tmp->CONF.Dyna_Time) && (DispScrCurrLoc == CCCR_Dyn_T2) && (Disp_tmp->CR.STADYNA==Function_Dynamic)))
					Display_Parameter_Pro(fdat,str,1);
				else if((DispScrCurrLoc == CCCR_Sta_SR) && (!Disp_tmp->CR.STADYNA==Function_Dynamic))
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR[2+(10*Disp_tmp->IRange)].precision));
				else if(((DispScrCurrLoc == CCCR_Dyn_SRUP) || (DispScrCurrLoc == CCCR_Dyn_SRDN)) && (Disp_tmp->CR.STADYNA==Function_Dynamic)) {
					if(DispScrCurrLoc == CCCR_Dyn_SRUP)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR[2+(10*Disp_tmp->IRange)].precision));
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR[2+(10*Disp_tmp->IRange)].precision));
				} else if((DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CR.STADYNA==Function_Dynamic) && (Disp_tmp->CONF.Dyna_Time)) {
					if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].Frequency_Range == 3)
						Display_Parameter_Pro(fdat,str,1);
					else
						Display_Parameter_Pro(fdat,str,0);
				} else if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].T1_RANGE && (DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CR.STADYNA==Function_Dynamic))
					Display_Parameter_Pro(fdat,str,0);
				else if(Disp_tmp->CR.DYNA[Disp_tmp->IRange].T2_RANGE && (DispScrCurrLoc == CCCR_Dyn_T2) && (Disp_tmp->CR.STADYNA==Function_Dynamic) && (!Disp_tmp->CONF.Dyna_Time))
					Display_Parameter_Pro(fdat,str,0);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[DispScrCurrLoc+(10*Disp_tmp->IRange)+(4*Disp_tmp->CR.STADYNA)].precision);

				if((Data_tmp->CONF.D_CR_Unit == OHM_Unit) && (DispScrCurrLoc<=CCCR_Dyn_L2)) {
					if((Disp_tmp->CONF.Dyna_Level) && (DispScrCurrLoc == CCCR_Dyn_L2) && (Disp_tmp->CR.STADYNA==Function_Dynamic))
						Display_Parameter_Pro(fdat,str,1);
					else {
						if(fdat)
							Display_Parameter_Pro((1000.0/fdat),str,7);
						else
							sprintf(str," OPEN ");
					}
				}
			}
			getcursortime = 0;
		}
		if(space_Flag)
			ShowSpace( 4, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		else
			ShowSpace( 8, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);

		if(Disp_tmp->CONF.Knob_Status) {
			if((DispScrCurrLoc <= CCCR_Sta_B_VALUE)&&(Disp_tmp->CONF.D_CR_Unit==OHM_Unit))
				Draw_Incremental_Line();
			else
				Draw_Cursor_Line();
		}
		if((DispScrCurrLoc == CCCR_Dyn_T1) && (Disp_tmp->CR.STADYNA==Function_Dynamic) && (Disp_tmp->CONF.Dyna_Time)&&(DispScrEndCT>4)) {
			dat = GetChanData(5,0);
			fdat = StepToReal(dat,5);
			Display_Parameter_Pro(fdat,str,1);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(Parameter_Font_R_Bolor);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT+1)*Disp_Interval);
		}
		_CursorResolution = StepToReal(1, DispScrCurrLoc);
	}
}

void RedrawCVModeData(void)
{
	long dat;
	int i;
	char str[20];
	double fdat;

	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	if(Data_tmp->CONF.Ext_Setting.Control) {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt( cv_sta[0]	, Disp_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetColor(Parameter_Font_R_Bolor);
		dat = (ptrMODEL_TYPE->CV)[3*Disp_tmp->VRange].Max;
		fdat = StepToReal(dat,0);
		fdat /= 1.02;		/*Max Setting(1.05) ->Setting(1) */
		fdat *= p3k_Measure_Data.Ext_Percent;
		Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[3*Disp_tmp->VRange].precision);
		ShowSpace( 7, Para_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_LEFT);
		GUI_DispStringAt( cv_unit[0], Unit_Start_X, Disp_Start_Y1+0*Disp_Interval);
		return;
	}

	if( DispMode <= DispMode_BROWSE_ITEMS) {
		for( i=0 ; i<CV_Max ; i++) {
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&(DispMode == DispMode_BROWSE_ITEMS) && ( i != B_DispCT && i != DispCT ) )
				continue;

			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(DispMode != DispMode_SELECT_CH && ( i == B_DispCT || i == DispCT ) ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(	Disp_Start_X, Disp_Start_Y1+ i*Disp_Interval);
				GUI_DispChars(' ', HiLight_Length);
			}
			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( cv_sta[i], Disp_Start_X, Disp_Start_Y1+i*Disp_Interval);
			GUI_SetColor(Parameter_Font_R_Bolor);
			dat = GetChanData(i,0);				/* Get Parameter */
			fdat = StepToReal(dat,i);
			Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[i+Disp_tmp->VRange*3].precision);
			if((0==Disp_tmp->CONF.Ext_Setting.Control)||(DataRedrawFlag&BG_CLEAR_FLAG))
				ShowSpace( 7, Para_Start_X, Disp_Start_Y1+i*Disp_Interval);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+i*Disp_Interval);
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_DispStringAt( cv_unit[i], Unit_Start_X, Disp_Start_Y1+i*Disp_Interval);
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		DispScrCurrLoc = DispCT;
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		dat = GetChanData(DispCT,0);

		if( KeyInFlag & DIGI_KEY_IN )
			sprintf( str, " %s " , KeyinBuf );
		else {
			getcursortime = 1;
			fdat = StepToReal(dat,DispCT);
			Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[DispCT+Disp_tmp->VRange*3].precision);
			getcursortime = 0;
		}

		ShowSpace( 7, Para_Start_X, Disp_Start_Y1+DispCT*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+DispCT*Disp_Interval);

		if(Disp_tmp->CONF.Knob_Status)
			Draw_Cursor_Line();
		_CursorResolution = StepToReal(1, DispScrCurrLoc);
	}
}

void RedrawCPModeData(void)
{
	long dat;
	int i,j;
	char Total_Display_Item,Sta_Dyna,str[20],ScrollBar_Flag=0,space_Flag=0;
	double fdat;

	P3k_Disp_Str *Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str *Data_tmp = &P3k_Chan_Data;

	if(Data_tmp->CONF.Ext_Setting.Control) {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt( cp_sta[0]	, Disp_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetColor(Parameter_Font_R_Bolor);
		dat = (ptrMODEL_TYPE->CP)[10*Disp_tmp->IRange].Max;
		fdat = StepToReal(dat,0);
		fdat /= 1.02;		/*Max Setting(1.05) ->Setting(1) */
		fdat *= p3k_Measure_Data.Ext_Percent;
		Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[10*Disp_tmp->IRange].precision);
		ShowSpace( 7, Para_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+0*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_LEFT);
		GUI_DispStringAt( cp_unit[0], Unit_Start_X, Disp_Start_Y1+0*Disp_Interval);
		return;
	}

	Sta_Dyna = Disp_tmp->CP.STADYNA;

	Total_Display_Item = CP_Sta_Max;

	if( DispMode <= DispMode_BROWSE_ITEMS) {
		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);

			if((DispScrCurrLoc == DispScrEndCT)||(DispScrCurrLoc == DispScrStartCT)) {
				if(ScrollBar_Flag==0) {
					ShowScrollBar_Other(Scroll_Bar_Start_X,Disp_Start_Y1,Total_Display_Item,Disp_Item_Num0,Disp_Interval,Scroll_Bar_Width,DispScrStartCT);
					GUI_SetBkColor(Parameter_Bottom_Bolor);
					ScrollBar_Flag=1;
				}

				if( i == DispScrCurrLoc)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);

				GUI_GotoXY(Disp_Start_X,Disp_Start_Y1+j*Disp_Interval);
				GUI_DispChars(' ',HiLight_Length);
			} else {
				if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&(DispMode == DispMode_BROWSE_ITEMS) && ( i != B_DispCT && i!= DispScrCurrLoc ) )
					continue;

				if((DispMode != DispMode_SELECT_CH) &&(i == DispScrCurrLoc || i == B_DispCT) ) {
					if( i==DispScrCurrLoc)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					GUI_GotoXY(Disp_Start_X,Disp_Start_Y1+j*Disp_Interval);
					GUI_DispChars(' ',HiLight_Length);
				}
			}
			GUI_SetColor(Parameter_Font_L_Bolor);

			GUI_DispStringAt( cp_sta[i]	, Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);

			GUI_SetColor(Parameter_Font_R_Bolor);
			dat = GetChanData(i,0);
			fdat = StepToReal(dat,i);

			if(i==CP_Sta_Add_CV) {
				fdat = StepToReal(dat,i);
				if(fdat < 0)
					sprintf( str, " OFF ");
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[Disp_tmp->VRange*3].precision);
			} else if(i==CP_Sta_CV_Response) {
				sprintf( str,cxcv_reponse[dat]);
			} else {
				Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[i+(10*Disp_tmp->IRange)+(4*Disp_tmp->CP.STADYNA)].precision);
			}

			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+j*Disp_Interval);
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_DispStringAt( cp_unit[i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		dat = GetChanData(DispScrCurrLoc,0);

		if( KeyInFlag & DIGI_KEY_IN )
			sprintf( str, " %s " , KeyinBuf );
		else {
			getcursortime = 1;
			fdat = StepToReal(dat, DispScrCurrLoc);

			if(DispScrCurrLoc==CP_Sta_Add_CV) {
				fdat = StepToReal(dat,DispScrCurrLoc);
				if(fdat < 0)
					sprintf( str, " OFF ");
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[Disp_tmp->VRange*3].precision);
			} else if(DispScrCurrLoc==CP_Sta_CV_Response) {
				sprintf( str,cxcv_reponse[dat]);
				space_Flag = 1;
			} else {
				Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[DispScrCurrLoc+(10*Disp_tmp->IRange)+(4*Disp_tmp->CP.STADYNA)].precision);
			}
			getcursortime = 0;
		}
		if(space_Flag)
			ShowSpace( 4, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		else
			ShowSpace( 7, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);

		if(Disp_tmp->CONF.Knob_Status)
			Draw_Cursor_Line();
		_CursorResolution = StepToReal(1, DispScrCurrLoc);
	}
}

void ConfigureSeparator(void)
{
	UWORD i;

	Displine(2,65,268,MEM_GRAY);
	Displine(2,66,268,GW_ORANGE_ku);
	Displine(2,67,268,MEM_WHITE);
	Displine(2,68,268,MEM_LIGHTGRAY_ku);

	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);
	GUI_SetTextAlign(GUI_TA_LEFT);
	GUI_DispStringAt("Configure", 105, 30);
}
#if Enable_Optim_display
void RedrawProtectionData(void)
{
	int i,j;
	long dat;
	char str[20];
	char DrawFlag;
	static char RecoderStartCT;
	double fdat;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;


	if(DispMode == DispMode_SELECT_CH)	DispMode = DispMode_BROWSE_ITEMS;


	if(DrawBar(0,P_OVP_LEVEL+1,Disp_Start_Y0))ConfigureSeparator();

	GUI_SetBkColor(Parameter_Bottom_Bolor);
	if(DispMode == DispMode_BROWSE_ITEMS) {

		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {

			GUI_SetBkColor(Parameter_Bottom_Bolor);
			DrawFlag = DrawBar(2,i,j);
			if(DrawFlag) {
				if(DrawFlag==2)break;
				if(DispScrCurrLoc == i)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( prot_title_str[i], Disp_Start_X, Disp_Start_Y0+j*Disp_Interval);
				GUI_SetColor(Parameter_Font_R_Bolor);
				GUI_DispStringAt( prot_unit[i], Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );			/* Display Unit */

				dat = GetChanData(i,0);
				if((i==P_OCP_SETTING)||(i==P_OPP_SETTING)) {
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( prot_str[dat], Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				} else {
					fdat=StepToReal(dat, i);
					if((DispScrCurrLoc != DispScrEndCT)&&(DispScrCurrLoc != DispScrStartCT))
						ShowSpace( 7 , Para_Start_X, Disp_Start_Y0+j*Disp_Interval );

					if(((i==P_UVP_LEVEL)&&(fdat==0))||((i==P_OVP_LEVEL)&&(fdat==((ptrMODEL_TYPE->PROT)[PROT_OVP_L+Disp_tmp->VRange].Max) * ((ptrMODEL_TYPE->PROT)[PROT_OVP_L+Disp_tmp->VRange].Resolution))))
						sprintf( str, " OFF ");
					else {
						if(i==P_OCP_LEVEL)
							Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[PROT_OCP_H].precision);
						else if(i==P_OPP_LEVEL)
							Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[PROT_OPP_H].precision);
						else if(i==P_UVP_LEVEL)
							Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_UVP_L].precision);
						else if(i==P_OVP_LEVEL)
							Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_OVP_L].precision);
					}
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				}
			}

		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		ShowSpace( 7, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);

		if( KeyInFlag & DIGI_KEY_IN ) {
			/* Show Keyin Data on Screen */
			sprintf( str, " %s " , KeyinBuf );
			//ShowSpace( 7, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		} else {
			dat = GetChanData(DispScrCurrLoc,0);
			if((DispScrCurrLoc==P_OCP_SETTING)||(DispScrCurrLoc==P_OPP_SETTING)) {
				//ShowSpace( 7, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( prot_str[dat], Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			} else {
				fdat=StepToReal(dat, DispScrCurrLoc);
				if((DispScrCurrLoc==P_UVP_LEVEL)&&(fdat==0))
					sprintf( str, " OFF ");
				else if((DispScrCurrLoc==P_OVP_LEVEL)&&(fdat==((ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_OVP_L].Max) * ((ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_OVP_L].Resolution)))
					sprintf( str, " OFF ");
				else {
					if(DispScrCurrLoc==P_OCP_LEVEL)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[PROT_OCP_H].precision);
					else if(DispScrCurrLoc==P_OPP_LEVEL)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[PROT_OPP_H].precision);
					else if(DispScrCurrLoc==P_UVP_LEVEL)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_UVP_L].precision);
					else if(DispScrCurrLoc==P_OVP_LEVEL)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_OVP_L].precision);
				}
				ShowSpace( 7 , Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval );
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			}
		}
	}
//FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_C);
}

#else
void RedrawProtectionData(void)
{
	int i,j;
	long dat;
	char str[20],ScrollBar_Flag=0,Total_Display_Item;
	double fdat;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;

	Total_Display_Item = P_OVP_LEVEL+1;
	ConfigureSeparator();

	if(DispMode == DispMode_SELECT_CH)
		DispMode = DispMode_BROWSE_ITEMS;

	if(DispMode == DispMode_BROWSE_ITEMS) {
		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if((DispScrCurrLoc == DispScrEndCT)||(DispScrCurrLoc == DispScrStartCT)) {
				if(ScrollBar_Flag==0) {
					ShowScrollBar_Other(Scroll_Bar_Start_X,Disp_Start_Y0,Total_Display_Item,Disp_Item_Num1,Disp_Interval,Scroll_Bar_Width,DispScrStartCT);
					GUI_SetBkColor(Parameter_Bottom_Bolor);
					ScrollBar_Flag=1;
				}

				if( i == DispScrCurrLoc)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(Disp_Start_X,Disp_Start_Y0+j*Disp_Interval);
				GUI_DispChars(' ',HiLight_Length);
			} else {
				if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispScrCurrLoc ) )
					continue;
				if( i == DispScrCurrLoc || i == B_DispCT ) {
					if( i==DispScrCurrLoc)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					GUI_GotoXY(Disp_Start_X,Disp_Start_Y0+j*Disp_Interval);
					GUI_DispChars(' ',HiLight_Length);
				}
			}
			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( prot_title_str[i], Disp_Start_X, Disp_Start_Y0+j*Disp_Interval);
			GUI_SetColor(Parameter_Font_R_Bolor);
			GUI_DispStringAt( prot_unit[i], Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );			/* Display Unit */

			dat = GetChanData(i,0);
			if((i==P_OCP_SETTING)||(i==P_OPP_SETTING)) {
				//if((DispScrCurrLoc != DispScrEndCT)&&(DispScrCurrLoc != DispScrStartCT))
				//ShowSpace( 5 , Para_Start_X, Disp_Start_Y0+j*Disp_Interval );
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( prot_str[dat], Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
			} else {
				/* Get Resolution, Max, Min */
				fdat=StepToReal(dat, i);
				if((DispScrCurrLoc != DispScrEndCT)&&(DispScrCurrLoc != DispScrStartCT))
					ShowSpace( 7 , Para_Start_X, Disp_Start_Y0+j*Disp_Interval );

				if(((i==P_UVP_LEVEL)&&(fdat==0))||((i==P_OVP_LEVEL)&&(fdat==((ptrMODEL_TYPE->PROT)[PROT_OVP_L+Disp_tmp->VRange].Max) * ((ptrMODEL_TYPE->PROT)[PROT_OVP_L+Disp_tmp->VRange].Resolution))))
					sprintf( str, " OFF ");
				else {
					if(i==P_OCP_LEVEL)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[PROT_OCP_H].precision);
					else if(i==P_OPP_LEVEL)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[PROT_OPP_H].precision);
					else if(i==P_UVP_LEVEL)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_UVP_L].precision);
					else if(i==P_OVP_LEVEL)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_OVP_L].precision);
				}
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		ShowSpace( 7, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);

		if( KeyInFlag & DIGI_KEY_IN ) {
			/* Show Keyin Data on Screen */
			sprintf( str, " %s " , KeyinBuf );
			//ShowSpace( 7, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		} else {
			dat = GetChanData(DispScrCurrLoc,0);
			if((DispScrCurrLoc==P_OCP_SETTING)||(DispScrCurrLoc==P_OPP_SETTING)) {
				//ShowSpace( 7, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( prot_str[dat], Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			} else {
				fdat=StepToReal(dat, DispScrCurrLoc);
				if((DispScrCurrLoc==P_UVP_LEVEL)&&(fdat==0))
					sprintf( str, " OFF ");
				else if((DispScrCurrLoc==P_OVP_LEVEL)&&(fdat==((ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_OVP_L].Max) * ((ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_OVP_L].Resolution)))
					sprintf( str, " OFF ");
				else {
					if(DispScrCurrLoc==P_OCP_LEVEL)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[PROT_OCP_H].precision);
					else if(DispScrCurrLoc==P_OPP_LEVEL)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[PROT_OPP_H].precision);
					else if(DispScrCurrLoc==P_UVP_LEVEL)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_UVP_L].precision);
					else if(DispScrCurrLoc==P_OVP_LEVEL)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->PROT)[Disp_tmp->VRange + PROT_OVP_L].precision);
				}
				ShowSpace( 7 , Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval );
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			}
		}
	}
}
#endif

#if Enable_Optim_display
void RedrawConfigureOther(void)
{
	long dat;
	char str[20],range;
	int i,j;
	double fdat;
	char DrawFlag;

	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;

	if(DispMode==DispMode_SELECT_CH)		DispMode=DispMode_BROWSE_ITEMS;

	if(DispMode == DispMode_BROWSE_ITEMS) {
		if(DrawBar(0,P_Conf_Max,Disp_Start_Y0))
			ConfigureSeparator();
		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			DrawFlag = DrawBar(2,i,j);
			if(DrawFlag) {
				if(DrawFlag==2)break;
				if(DispScrCurrLoc == i)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);

				if(UTILITY.LOAD_CTL)
					GUI_SetColor(MEM_DARKGRAY);
				else
					GUI_SetColor(Parameter_Font_L_Bolor);
				if((P3k_Disp_Data.CURRMODE==CR_MODE)&&(i==P_Von_Delay))
					GUI_DispStringAt(" Von Delay-CR",Disp_Start_X, Disp_Start_Y0+j*Disp_Interval);
				else
					GUI_DispStringAt(conf_other[i],Disp_Start_X, Disp_Start_Y0+j*Disp_Interval);
				ShowSpace( conf_other_space[i], Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				dat = GetChanData(i,0);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				if(UTILITY.LOAD_CTL)
					GUI_SetColor(MEM_DARKGRAY);
				else
					GUI_SetColor(Parameter_Font_R_Bolor);
				switch(i) {
				case P_SOFT_START:
					fdat=StepToReal(dat,i);
					if(fdat==0)
						sprintf( str, " OFF ");
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CONF)[2].precision);
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt( " ms ", Conf_Unit_Start_X, Disp_Start_Y0+j*Disp_Interval);//
					break;
				case P_VON_VOLTAGE:
					fdat=StepToReal(dat, i);
					if(((ptrMODEL_TYPE->CONF)[Data_tmp->VRange].precision)==0) {
						dat=fdat;
						sprintf( str, " %d ", dat );
					} else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CONF)[Data_tmp->VRange].precision);

					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt( " V ", Conf_Unit_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_VON_LATCH:
				case P_COUNTTIME:
					GUI_DispStringAt( onoff_str[dat], Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_Von_Delay:
					fdat=StepToReal(dat,i);
					if((fdat < 2.0)||((fdat < 5.0)&&(P3k_Disp_Data.CURRMODE==CR_MODE)))
						sprintf( str, " OFF ");
					else
						Display_Parameter_Pro(fdat,str,1);
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt( " ms ", Conf_Unit_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_CUTOFFTIME:
					if(P3k_Chan_Data.CONF.cut_off_time_total)
						sprintf( str, " %03dh: %02dm: %02ds ",P3k_Chan_Data.CONF.Cut_Off_Time_h,P3k_Chan_Data.CONF.Cut_Off_Time_m,P3k_Chan_Data.CONF.Cut_Off_Time_s);
					else
						sprintf( str, "  OFF          ");
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, 260, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_CR_Unit:
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( Input_Mode[dat], Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_Dyna_Level:
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( Dyna_Level[dat], Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_Dyna_Time:
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( Dyna_Time[dat], Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_Mem_Recall:
					GUI_DispStringAt( Memory_str[dat],Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_SHORT_KEY:
					GUI_DispStringAt( short_key[dat],Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
				default:
					break;
				}
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		if(DispScrCurrLoc==P_CUTOFFTIME) {
			if(1) {
				GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(Disp_Start_X,Disp_Start_Y0+j*Disp_Interval);
				GUI_DispChars(' ',HiLight_Length);
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt(conf_other[P_CUTOFFTIME],Disp_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_SetColor(Parameter_Font_R_Bolor);
				sprintf( str, " %03dh: %02dm: %02ds ",P3k_Chan_Data.CONF.Cut_Off_Time_h,P3k_Chan_Data.CONF.Cut_Off_Time_m,P3k_Chan_Data.CONF.Cut_Off_Time_s);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, 260, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			}
			GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
			if(P3k_Chan_Data.CONF.Cut_Off_cnt==0)
				ShowSpace( 4,155,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			else if(P3k_Chan_Data.CONF.Cut_Off_cnt==1)
				ShowSpace( 3,197,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			else if(P3k_Chan_Data.CONF.Cut_Off_cnt==2)
				ShowSpace( 3,245,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		} else
			ShowSpace( conf_other_space[DispScrCurrLoc],Conf_Para_Start_X,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		if(KeyInFlag & DIGI_KEY_IN) {
			if(DispScrCurrLoc!=P_CUTOFFTIME) {
				sprintf( str, " %s " , KeyinBuf );
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			} else {
				GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
				GUI_SetColor(Parameter_Select_Font_Bolor);
				sprintf( str, " %s " , KeyinBuf );
				GUI_SetTextAlign(GUI_TA_RIGHT);
				if(P3k_Chan_Data.CONF.Cut_Off_cnt==0)
					GUI_DispStringAt( str, 155, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				else if(P3k_Chan_Data.CONF.Cut_Off_cnt==1)
					GUI_DispStringAt( str, 197, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				else if(P3k_Chan_Data.CONF.Cut_Off_cnt==2)
					GUI_DispStringAt( str, 245, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			}
		} else {
			dat = GetChanData(DispScrCurrLoc,0);

			switch(DispScrCurrLoc) {
			case P_SOFT_START:
				if( KeyInFlag & DIGI_KEY_IN )
					sprintf( str, " %s " , KeyinBuf );
				else {
					fdat = StepToReal(dat,DispScrCurrLoc);
					if(fdat==0)
						sprintf( str, " OFF ");
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CONF)[2].precision);
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				}
				break;
			case P_VON_VOLTAGE:
				fdat=StepToReal(dat, DispScrCurrLoc);

				if(((ptrMODEL_TYPE->CONF)[Data_tmp->VRange].precision)==0) {
					dat = fdat;
					if(dat > 0)
						sprintf( str, " %d ", dat );
				} else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CONF)[Data_tmp->VRange].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_CUTOFFTIME:
				if(P3k_Chan_Data.CONF.Cut_Off_cnt==0)
					dat = P3k_Chan_Data.CONF.Cut_Off_Time_h;
				else if(P3k_Chan_Data.CONF.Cut_Off_cnt==1)
					dat = P3k_Chan_Data.CONF.Cut_Off_Time_m;
				else if(P3k_Chan_Data.CONF.Cut_Off_cnt==2)
					dat = P3k_Chan_Data.CONF.Cut_Off_Time_s;
				GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
				GUI_SetColor(Parameter_Select_Font_Bolor);

				fdat= dat;
				range = 3;
				if(((ptrMODEL_TYPE->CONF)[range].precision)==0) {
					if(P3k_Chan_Data.CONF.cut_off_time_total)
						sprintf( str, " %d ", dat );
					else
						sprintf( str, "     OFF      ");
				} else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CONF)[range].precision);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				if(P3k_Chan_Data.CONF.cut_off_time_total) {
					if(P3k_Chan_Data.CONF.Cut_Off_cnt==0)
						GUI_DispStringAt( str, 155, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
					else if(P3k_Chan_Data.CONF.Cut_Off_cnt==1)
						GUI_DispStringAt( str, 197, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
					else if(P3k_Chan_Data.CONF.Cut_Off_cnt==2)
						GUI_DispStringAt( str, 245, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				} else {
					GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				}
				break;
			case P_VON_LATCH:
			case P_COUNTTIME:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( onoff_str[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_Von_Delay:
				if( KeyInFlag & DIGI_KEY_IN )
					sprintf( str, " %s " , KeyinBuf );
				else {
					fdat = StepToReal(dat,DispScrCurrLoc);
					if((fdat < 2.0)||((fdat < 5.0)&&(P3k_Disp_Data.CURRMODE==CR_MODE)))
						sprintf( str, " OFF ");
					else
						Display_Parameter_Pro(fdat,str,1);
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				}
				break;
#if 0
			case P_Response:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Chan_Response[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
#endif
			case P_CR_Unit:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Input_Mode[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_Dyna_Level:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Dyna_Level[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_Dyna_Time:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Dyna_Time[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_Mem_Recall:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Memory_str[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_SHORT_KEY:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( short_key[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			default:
				break;
			}
		}
	}
}

#else
void RedrawConfigureOther(void)
{
	long dat;
	char str[20],range,Total_Display_Item;
	int i,j;
	double fdat;

	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;

	Total_Display_Item = P_Conf_Max;

	if(DispMode==DispMode_SELECT_CH)
		DispMode=DispMode_BROWSE_ITEMS;

	if(DispMode == DispMode_BROWSE_ITEMS) {
		if(DataRedrawFlag&BG_CLEAR_FLAG)
			ConfigureSeparator();

		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if( (DispScrCurrLoc == DispScrEndCT) || (DispScrCurrLoc == DispScrStartCT) ) {
				ShowScrollBar_Other(Scroll_Bar_Start_X,Disp_Start_Y0,Total_Display_Item,Disp_Item_Num1,Disp_Interval,Scroll_Bar_Width,DispScrStartCT);
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				if((i == DispScrCurrLoc) && (!UTILITY.LOAD_CTL))
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(Disp_Start_X,Disp_Start_Y0+j*Disp_Interval);
				GUI_DispChars(' ',HiLight_Length);
			} else {
				if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispScrCurrLoc ) )
					continue;
				if( i == DispScrCurrLoc || i == B_DispCT ) {
					if( i==DispScrCurrLoc)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					GUI_GotoXY(Disp_Start_X,Disp_Start_Y0+j*Disp_Interval);
					GUI_DispChars(' ',HiLight_Length);
				}
			}
			if(UTILITY.LOAD_CTL)
				GUI_SetColor(MEM_DARKGRAY);
			else
				GUI_SetColor(Parameter_Font_L_Bolor);
			if((P3k_Disp_Data.CURRMODE==CR_MODE)&&(i==P_Von_Delay))
				GUI_DispStringAt(" Von Delay-CR",Disp_Start_X, Disp_Start_Y0+j*Disp_Interval);
			else
				GUI_DispStringAt(conf_other[i],Disp_Start_X, Disp_Start_Y0+j*Disp_Interval);
			ShowSpace( conf_other_space[i], Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
			dat = GetChanData(i,0);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			if(UTILITY.LOAD_CTL)
				GUI_SetColor(MEM_DARKGRAY);
			else
				GUI_SetColor(Parameter_Font_R_Bolor);
			switch(i) {
			case P_SOFT_START:
				fdat=StepToReal(dat,i);
				if(fdat==0)
					sprintf( str, " OFF ");
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CONF)[2].precision);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( " ms ", Conf_Unit_Start_X, Disp_Start_Y0+j*Disp_Interval);//
				break;
			case P_VON_VOLTAGE:
				fdat=StepToReal(dat, i);
				if(((ptrMODEL_TYPE->CONF)[Data_tmp->VRange].precision)==0) {
					dat=fdat;
					sprintf( str, " %d ", dat );
				} else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CONF)[Data_tmp->VRange].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( " V ", Conf_Unit_Start_X, Disp_Start_Y0+j*Disp_Interval);
				break;
			case P_VON_LATCH:
			case P_COUNTTIME:
				GUI_DispStringAt( onoff_str[dat], Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				break;
			case P_Von_Delay:
				fdat=StepToReal(dat,i);
				if((fdat < 2.0)||((fdat < 5.0)&&(P3k_Disp_Data.CURRMODE==CR_MODE)))
					sprintf( str, " OFF ");
				else
					Display_Parameter_Pro(fdat,str,1);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( " ms ", Conf_Unit_Start_X, Disp_Start_Y0+j*Disp_Interval);
				break;
#if 0
			case P_Response:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Chan_Response[dat], Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				break;
#endif
			case P_CUTOFFTIME:
				if(P3k_Chan_Data.CONF.cut_off_time_total)
					sprintf( str, " %03dh: %02dm: %02ds ",P3k_Chan_Data.CONF.Cut_Off_Time_h,P3k_Chan_Data.CONF.Cut_Off_Time_m,P3k_Chan_Data.CONF.Cut_Off_Time_s);
				else
					sprintf( str, "  OFF          ");
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, 260, Disp_Start_Y0+j*Disp_Interval);
				break;
			case P_CR_Unit:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Input_Mode[dat], Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				break;
			case P_Dyna_Level:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Dyna_Level[dat], Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				break;
			case P_Dyna_Time:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Dyna_Time[dat], Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				break;
			case P_Mem_Recall:
				GUI_DispStringAt( Memory_str[dat],Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				break;
			case P_SHORT_KEY:
				GUI_DispStringAt( short_key[dat],Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				break;
			default:
				break;
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		if(DispScrCurrLoc==P_CUTOFFTIME) {
			if(1) {
				GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(Disp_Start_X,Disp_Start_Y0+j*Disp_Interval);
				GUI_DispChars(' ',HiLight_Length);
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt(conf_other[P_CUTOFFTIME],Disp_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_SetColor(Parameter_Font_R_Bolor);
				sprintf( str, " %03dh: %02dm: %02ds ",P3k_Chan_Data.CONF.Cut_Off_Time_h,P3k_Chan_Data.CONF.Cut_Off_Time_m,P3k_Chan_Data.CONF.Cut_Off_Time_s);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, 260, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			}
			GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
			if(P3k_Chan_Data.CONF.Cut_Off_cnt==0)
				ShowSpace( 4,155,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			else if(P3k_Chan_Data.CONF.Cut_Off_cnt==1)
				ShowSpace( 3,197,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			else if(P3k_Chan_Data.CONF.Cut_Off_cnt==2)
				ShowSpace( 3,245,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		} else
			ShowSpace( conf_other_space[DispScrCurrLoc],Conf_Para_Start_X,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		if(KeyInFlag & DIGI_KEY_IN) {
			if(DispScrCurrLoc!=P_CUTOFFTIME) {
				sprintf( str, " %s " , KeyinBuf );
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			} else {
				GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
				GUI_SetColor(Parameter_Select_Font_Bolor);
				sprintf( str, " %s " , KeyinBuf );
				GUI_SetTextAlign(GUI_TA_RIGHT);
				if(P3k_Chan_Data.CONF.Cut_Off_cnt==0)
					GUI_DispStringAt( str, 155, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				else if(P3k_Chan_Data.CONF.Cut_Off_cnt==1)
					GUI_DispStringAt( str, 197, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				else if(P3k_Chan_Data.CONF.Cut_Off_cnt==2)
					GUI_DispStringAt( str, 245, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			}
		} else {
			dat = GetChanData(DispScrCurrLoc,0);

			switch(DispScrCurrLoc) {
			case P_SOFT_START:
				if( KeyInFlag & DIGI_KEY_IN )
					sprintf( str, " %s " , KeyinBuf );
				else {
					fdat = StepToReal(dat,DispScrCurrLoc);
					if(fdat==0)
						sprintf( str, " OFF ");
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CONF)[2].precision);
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				}
				break;
			case P_VON_VOLTAGE:
				fdat=StepToReal(dat, DispScrCurrLoc);

				if(((ptrMODEL_TYPE->CONF)[Data_tmp->VRange].precision)==0) {
					dat = fdat;
					if(dat > 0)
						sprintf( str, " %d ", dat );
				} else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CONF)[Data_tmp->VRange].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_CUTOFFTIME:
				if(P3k_Chan_Data.CONF.Cut_Off_cnt==0)
					dat = P3k_Chan_Data.CONF.Cut_Off_Time_h;
				else if(P3k_Chan_Data.CONF.Cut_Off_cnt==1)
					dat = P3k_Chan_Data.CONF.Cut_Off_Time_m;
				else if(P3k_Chan_Data.CONF.Cut_Off_cnt==2)
					dat = P3k_Chan_Data.CONF.Cut_Off_Time_s;
				GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
				GUI_SetColor(Parameter_Select_Font_Bolor);

				fdat= dat;
				range = 3;
				if(((ptrMODEL_TYPE->CONF)[range].precision)==0) {
					if(P3k_Chan_Data.CONF.cut_off_time_total)
						sprintf( str, " %d ", dat );
					else
						sprintf( str, "     OFF      ");
				} else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CONF)[range].precision);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				if(P3k_Chan_Data.CONF.cut_off_time_total) {
					if(P3k_Chan_Data.CONF.Cut_Off_cnt==0)
						GUI_DispStringAt( str, 155, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
					else if(P3k_Chan_Data.CONF.Cut_Off_cnt==1)
						GUI_DispStringAt( str, 197, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
					else if(P3k_Chan_Data.CONF.Cut_Off_cnt==2)
						GUI_DispStringAt( str, 245, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				} else {
					GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				}
				break;
			case P_VON_LATCH:
			case P_COUNTTIME:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( onoff_str[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_Von_Delay:
				if( KeyInFlag & DIGI_KEY_IN )
					sprintf( str, " %s " , KeyinBuf );
				else {
					fdat = StepToReal(dat,DispScrCurrLoc);
					if((fdat < 2.0)||((fdat < 5.0)&&(P3k_Disp_Data.CURRMODE==CR_MODE)))
						sprintf( str, " OFF ");
					else
						Display_Parameter_Pro(fdat,str,1);
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				}
				break;
#if 0
			case P_Response:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Chan_Response[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
#endif
			case P_CR_Unit:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Input_Mode[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_Dyna_Level:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Dyna_Level[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_Dyna_Time:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Dyna_Time[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_Mem_Recall:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( Memory_str[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_SHORT_KEY:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( short_key[dat], Conf_Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			default:
				break;
			}
		}
	}
}

#endif
#if Enable_Optim_display
void RedrawSpecData(void)
{
	long dat,centerval;
	int i,j;
	char tmp,tmp1,str[20],type,ScrollBar_Flag=0,Total_Display_Item;
	double fdat,fdat1;
	UBYTE Precision=1;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	char DrawFlag;


	type =  Disp_tmp->SPECTYPE;

	if(type)	Total_Display_Item = P_SPEC_CENTER+1;
	else		Total_Display_Item = P_SPEC_CENTER;

	if(DrawBar(0,Total_Display_Item,Disp_Start_Y0))
		ConfigureSeparator();

	if(DispMode == DispMode_SELECT_CH)
		DispMode = DispMode_BROWSE_ITEMS;

	if(DispMode == DispMode_BROWSE_ITEMS) {

#if 1
		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			DrawFlag = DrawBar((1+type),i,j);
			if(DrawFlag) {
				if(DrawFlag==2)break;
				if(DispScrCurrLoc == i)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);
#else
for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	if(type) {
		ShowScrollBar_Other(Scroll_Bar_Start_X,Disp_Start_Y0,Total_Display_Item,Disp_Item_Num1,Disp_Interval,Scroll_Bar_Width,DispScrStartCT);
		GUI_SetBkColor(Parameter_Bottom_Bolor);
	}
	if((DispScrCurrLoc == DispScrEndCT)||(DispScrCurrLoc == DispScrStartCT)) {
		if( i == DispScrCurrLoc)
			GUI_SetBkColor(Parameter_Select_Bar_Bolor);
		GUI_GotoXY(Disp_Start_X,Disp_Start_Y0+j*Disp_Interval);
		GUI_DispChars(' ',HiLight_Length);
	} else {
		if( i == DispScrCurrLoc || i == B_DispCT ) {
			if( i==DispScrCurrLoc)
				GUI_SetBkColor(Parameter_Select_Bar_Bolor);
			GUI_GotoXY(Disp_Start_X,Disp_Start_Y0+j*Disp_Interval);
			GUI_DispChars(' ',HiLight_Length);
		}
	}
#endif
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( spec_str[i], Disp_Start_X, Disp_Start_Y0+j*Disp_Interval);

				if(i==P_SPEC_TEST) {
					if(Disp_tmp->SPEC)	sprintf( str, " ON ");
					else				sprintf( str, " OFF ");
				} else if(i==P_SPEC_DELAY) {
					fdat=Disp_tmp->P_F_Delay/10.0;
					Display_Parameter_Pro(fdat,str,1);
				} else if(i==P_SPEC_ENTRY) {
					if(Disp_tmp->SPECTYPE)	sprintf( str, " Percent ");
					else					sprintf( str, " Value ");
				} else if(i==P_SPEC_CENTER) {
					/*Center*/
					dat = GetChanData(i+1,0);				/* Get Paramter */
					fdat = StepToReal(dat,0);				/* Get Resolution, Max, Min */
					if(CV_MODE!=Disp_tmp->CURRMODE)	Precision = (ptrMODEL_TYPE->CC_SPEC)[0].precision;
					else							Precision = (ptrMODEL_TYPE->CV_SPEC)[0].precision;
					Display_Parameter_Pro(fdat,str,Precision);
				} else {
					if(type) {
						/*High and Low*/
						dat = GetChanData( i+6,0);
						fdat1 = dat/10.0;
						Display_Parameter_Pro(fdat1,str,1);
					} else {
						dat = GetChanData( i+4,0);
						fdat = StepToReal(dat, i-3);
						if(CV_MODE!=Disp_tmp->CURRMODE)	Precision = (ptrMODEL_TYPE->CC_SPEC)[0].precision;
						else							Precision = (ptrMODEL_TYPE->CV_SPEC)[0].precision;
						Display_Parameter_Pro(fdat,str,Precision);
					}
				}
				GUI_SetColor(Parameter_Font_R_Bolor);
				if( (i==P_SPEC_TEST)||(i==P_SPEC_DELAY) )	ShowSpace( 4 , Para_Start_X, Disp_Start_Y0+j*Disp_Interval );
				else										ShowSpace( 7 , Para_Start_X, Disp_Start_Y0+j*Disp_Interval );
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_LEFT);
				if(i==P_SPEC_DELAY)
					GUI_DispStringAt( " s ", Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
				if(i<P_SPEC_HIGH)
					continue;
				if( type ) {
					if( M_num==P_CC_SPEC || M_num==P_CR_SPEC || M_num==P_CP_SPEC )
						GUI_DispStringAt( spec_unit_pcet[i-3], Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
					else
						GUI_DispStringAt( spec1_unit_pcet[i-3], Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
				} else {
					if( M_num==P_CC_SPEC || M_num==P_CR_SPEC || M_num==P_CP_SPEC )
						GUI_DispStringAt( spec_unit_val[i-3], Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
					else
						GUI_DispStringAt( spec1_unit_val[i-3], Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
				}
			}
		}

	}
	else if(DispMode == DispMode_SET_PARAMETERS)
	{
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if( KeyInFlag & DIGI_KEY_IN ) {
			/* Show Keyin Data on Screen */
			sprintf( str, " %s " , KeyinBuf );
		} else {
			/* Show Memory Data on Screen */
			if(DispScrCurrLoc==P_SPEC_TEST) {
				if(Disp_tmp->SPEC)	sprintf( str, " ON ");
				else				sprintf( str, " OFF ");
			} else if(DispScrCurrLoc==P_SPEC_DELAY) {
				fdat=Disp_tmp->P_F_Delay/10.0;
				Display_Parameter_Pro(fdat,str,1);
			} else if(DispScrCurrLoc==P_SPEC_ENTRY) {
				if(Disp_tmp->SPECTYPE)	sprintf( str, " Percent ");
				else					sprintf( str, " Value ");
			} else if(DispScrCurrLoc==P_SPEC_CENTER) {
				dat = GetChanData( DispScrCurrLoc+1,0);				/* Get Paramter */
				fdat = StepToReal(dat,0);					/* Get Resolution, Max, Min */
				if(CV_MODE!=Disp_tmp->CURRMODE)	Precision = (ptrMODEL_TYPE->CC_SPEC)[0].precision;
				else							Precision = (ptrMODEL_TYPE->CV_SPEC)[0].precision;
				Display_Parameter_Pro(fdat,str,Precision);
			} else {
				if(type) {
					dat = GetChanData( DispScrCurrLoc+6,0);
					fdat1 = dat/10.0;
					Display_Parameter_Pro(fdat1,str,1);
				} else {
					dat = GetChanData( DispScrCurrLoc+4,0);
					fdat = StepToReal(dat, DispScrCurrLoc-3);
					if(CV_MODE!=Disp_tmp->CURRMODE)	Precision = (ptrMODEL_TYPE->CC_SPEC)[0].precision;
					else							Precision = (ptrMODEL_TYPE->CV_SPEC)[0].precision;
					Display_Parameter_Pro(fdat,str,Precision);
				}
			}
		}
		if((DispScrCurrLoc==P_SPEC_TEST)||(DispScrCurrLoc==P_SPEC_DELAY))
			ShowSpace( 4 , Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval );
		else
			ShowSpace( 7 , Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval );
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
	}
}

void RedrawSync(void)
{
	long dat;
	int i,j;
	char Total_Display_Item,Sta_Dyna,str[20],ScrollBar_Flag=0;
	double fdat;
	unsigned char Total_Item;

	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	ConfigureSeparator();

	if(DispMode_BROWSE_ITEMS==DispMode) {
		Displine(2,100,268,MEM_GRAY);
		Displine(2,101,268,GW_ORANGE_ku);
		Displine(2,102,268,MEM_WHITE);
		Displine(2,103,268,MEM_LIGHTGRAY_ku);

		if((Model_Number == MODEL3031E) ||(Model_Number == MODEL3032E))
			Total_Item = P_Para_MAX - 1;
		else
			Total_Item = P_Para_MAX;

		for(i = 0 ; i < Total_Item ; i++) {
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&(DispMode == DispMode_BROWSE_ITEMS) && ( i != B_DispCT && i != DispCT ) )
				continue;
			GUI_SetBkColor(Parameter_Bottom_Bolor);

			if(DispMode != DispMode_SELECT_CH && ( i == B_DispCT || i == DispCT ) ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);

				if(i==P_Para_Operation) {
					//GUI_GotoXY(	Disp_Start_X, Disp_Start_Y0+ i*Disp_Interval);
					Draw_Bar_25(Disp_Start_X, Disp_Start_Y0+ i*Disp_Interval,HiLight_Length);
				} else {
					//GUI_GotoXY(	Disp_Start_X, Disp_Start_Y0+ i*Disp_Interval+10);
					Draw_Bar_25(Disp_Start_X, Disp_Start_Y0+ i*Disp_Interval+10,HiLight_Length);
				}
				//GUI_DispChars(' ', HiLight_Length);
			}
			GUI_SetTextAlign(GUI_TA_LEFT);

			if((Operation_Slave==Disp_tmp->CONF.Para_Data.Mode)&&(i>P_Para_Operation))
				GUI_SetColor(MEM_DARKGRAY);
			else if(Disp_tmp->CONF.Para_Data.Parallel_Number && (i == P_Para_Booster) )
				GUI_SetColor(MEM_DARKGRAY);
			else if( Disp_tmp->CONF.Para_Data.Booster_Number && (i == P_Para_Unit) )
				GUI_SetColor(MEM_DARKGRAY);
			else
				GUI_SetColor(Parameter_Font_L_Bolor);

			if(i==P_Para_Operation) {
				GUI_DispStringAt( Parallel_item[i], Disp_Start_X, Disp_Start_Y0+i*Disp_Interval);
				ShowSpace( 6, Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
			} else {
				GUI_DispStringAt( Parallel_item[i], Disp_Start_X, Disp_Start_Y0+i*Disp_Interval+10);
				ShowSpace( 6, Para_Start_X, Disp_Start_Y0 + i*Disp_Interval+10);
			}

			dat = GetChanData(i,0);
			GUI_SetTextAlign(GUI_TA_RIGHT);

			if( (Operation_Slave==Disp_tmp->CONF.Para_Data.Mode)&&(i>P_Para_Operation) )
				GUI_SetColor(MEM_DARKGRAY);
			else if( Disp_tmp->CONF.Para_Data.Parallel_Number && (i == P_Para_Booster) )
				GUI_SetColor(MEM_DARKGRAY);
			else if( Disp_tmp->CONF.Para_Data.Booster_Number && (i == P_Para_Unit) )
				GUI_SetColor(MEM_DARKGRAY);
			else
				GUI_SetColor(Parameter_Font_R_Bolor);

			if(i==P_Para_Operation)	GUI_DispStringAt(Parallel_Mode[dat],
				                Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
			else {
				if(dat) {
					if(P_Para_Unit==i)
						sprintf( str, " %d ", dat+1 );
					else
						sprintf( str, " %d ", dat );
				} else
					sprintf( str, " OFF ");
				GUI_DispStringAt(str,Para_Start_X, Disp_Start_Y0 + i*Disp_Interval+10);
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		dat = GetChanData(DispCT,0);
		if(DispCT==P_Para_Operation)
			ShowSpace( 6, Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		else
			ShowSpace( 6, Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval+10);
		GUI_SetTextAlign(GUI_TA_RIGHT);

		if(DispCT==P_Para_Operation)
			GUI_DispStringAt(Parallel_Mode[dat], Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		else {
			if(dat) {
				if(P_Para_Unit==DispCT)
					sprintf( str, " %d ", dat+1 );
				else
					sprintf( str, " %d ", dat );
			} else
				sprintf( str, " OFF ");
			GUI_DispStringAt(str,Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval+10);
		}
	}
}

void RedrawKnobData(void)
{
	long dat;
	char str[20],range,Total_Display_Item;
	int i,j;
	double fdat;
	double Para_s = Get_Parallel_Parameter(P3k_Chan_Data.IRange);
	char DrawFlag;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	Total_Display_Item = P_Konb_MAX;

	if(DrawBar(0,Total_Display_Item,Disp_Start_Y0))
		ConfigureSeparator();

	if(DispMode==DispMode_SELECT_CH)
		DispMode=DispMode_BROWSE_ITEMS;

	if(DispMode == DispMode_BROWSE_ITEMS) {

		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			DrawFlag = DrawBar(2,i,j);
			if(DrawFlag) {
				if(DrawFlag==2)break;
				if(DispScrCurrLoc == i)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);


				if(Disp_tmp->CONF.Knob_Status && i>=P_CCH_STEP)
					GUI_SetColor(MEM_DARKGRAY);
				else
					GUI_SetColor(Parameter_Font_L_Bolor);

				GUI_DispStringAt(conf_knob[i],Disp_Start_X, Disp_Start_Y0+j*Disp_Interval);
				ShowSpace( 7, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);

				dat = GetChanData(i,0);
				GUI_SetTextAlign(GUI_TA_RIGHT);

				if(Disp_tmp->CONF.Knob_Status && i>=P_CCH_STEP)
					GUI_SetColor(MEM_DARKGRAY);
				else
					GUI_SetColor(Parameter_Font_R_Bolor);

				switch(i) {
				case P_Knob_Status:
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( knob_status[dat], Para_Start_X+52, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_CCH_STEP://	case P_CCM_STEP:
				case P_CCL_STEP:
					fdat=StepToReal(dat, i)*Para_s;

					if(i==P_CCH_STEP)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[10].precision);
					//else if(i==P_CCM_STEP)
					//	Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[10].precision);
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[0].precision);

					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt( " A ", Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
					break;
				case P_CRH_STEP://case P_CRM_STEP:
				case P_CRL_STEP:
					fdat=StepToReal(dat, i)*Para_s;

					if(i==P_CRH_STEP)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[10].precision);
					//else if(i==P_CRM_STEP)
					//	Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[10].precision);
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[0].precision);

					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt( " mS ", Unit_Start_X, Disp_Start_Y0+j*Disp_Interval);
					break;
				case P_CVH_STEP:
				case P_CVL_STEP:
					fdat=StepToReal(dat, i);

					if(i==P_CVH_STEP)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[3].precision);
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[0].precision);

					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt( " V ", Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
					break;
				case P_CPH_STEP:
					//case P_CPM_STEP:
				case P_CPL_STEP:
					fdat=StepToReal(dat, i)*Para_s;

					if(i==P_CPH_STEP)
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[10].precision);
					//else if(i==P_CPM_STEP)
					//	Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[10].precision);
					else
						Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[0].precision);

					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
					GUI_SetTextAlign(GUI_TA_LEFT);
					GUI_DispStringAt( " W ", Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
					break;
				default:
					break;
				}
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN) {
			ShowSpace( conf_knob_space[DispScrCurrLoc], Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			sprintf( str, " %s " , KeyinBuf );
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		} else {
			dat = GetChanData(DispScrCurrLoc,0);
			ShowSpace( conf_knob_space[DispScrCurrLoc], Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			fdat=StepToReal(dat, DispScrCurrLoc);

			switch(DispScrCurrLoc) {
			case P_Knob_Status:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( knob_status[dat], Para_Start_X+52, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_CCH_STEP:
				//case P_CCM_STEP:
			case P_CCL_STEP:
				fdat=StepToReal(dat, DispScrCurrLoc)*Para_s;

				if(DispScrCurrLoc==P_CCH_STEP)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[10].precision);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[0].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_CRH_STEP:
				//case P_CRM_STEP:
			case P_CRL_STEP:
				fdat=StepToReal(dat, DispScrCurrLoc)*Para_s;

				if(DispScrCurrLoc==P_CRH_STEP)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[10].precision);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[0].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_CVH_STEP:
			case P_CVL_STEP:
				fdat=StepToReal(dat, DispScrCurrLoc);

				if(DispScrCurrLoc==P_CVH_STEP)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[3].precision);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[0].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_CPH_STEP:
				//case P_CPM_STEP:
			case P_CPL_STEP:
				fdat=StepToReal(dat, DispScrCurrLoc)*Para_s;

				if(DispScrCurrLoc==P_CPH_STEP)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[10].precision);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[0].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			default:
				break;
			}
		}
	}
}

void RedrawExtFunction(void)
{
	long dat;
	int i,j;
	char Total_Display_Item,Sta_Dyna,str[20],ScrollBar_Flag=0;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;
	char DrawFlag;

	if(DrawBar(0,5,72))
		ConfigureSeparator();
	DispScrCurrLoc = DispCT;
	if(DispMode_BROWSE_ITEMS == DispMode) {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		for(i=0 ; i<P_Ext_MAX ; i++) {
			DrawFlag = DrawBar(1,i,i);
			if(DrawFlag) {
				if(DrawFlag==2)break;
				if(DispScrCurrLoc == i)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);
#if NF_flag
				if(i>= P_Extmulti_para)break;
#endif
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( External_item[i], Disp_Start_X, Disp_Start_Y0+i*Disp_Interval);
				ShowSpace( 6, Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
				dat = GetChanData(i,0);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_SetColor(Parameter_Font_R_Bolor);

				if(P_Ext_Control==i)
					GUI_DispStringAt(External_Control[dat],	Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
				else if(P_Ext_LoadON_IN==i) {
					if(P3k_Chan_Data.CONF.Ext_Setting.MultilPara)
						GUI_SetColor(Parameter_Font_Bolor_Para);
					GUI_DispStringAt(External_LoadOnIn[dat], Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
				} else
					GUI_DispStringAt(External_Multi[dat], Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		dat = GetChanData(DispCT,0);
		ShowSpace( 6, Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);

		if(P_Ext_Control==DispCT)
			GUI_DispStringAt(External_Control[dat],	Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		else if(P_Ext_LoadON_IN==DispCT) {
			GUI_DispStringAt(External_LoadOnIn[dat], Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		} else if(P_Extmulti_para==DispCT) {
			GUI_DispStringAt(External_Multi[dat], Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		}

	}
}

#else
void RedrawSpecData(void)
{
	long dat,centerval;
	int i,j;
	char tmp,tmp1,str[20],type,ScrollBar_Flag=0,Total_Display_Item;
	double fdat,fdat1;
	UBYTE Precision=1;
	P3k_Disp_Str		*Disp_tmp = &P3k_Disp_Data;
	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	ConfigureSeparator();

	type =  Disp_tmp->SPECTYPE;

	if(type)	Total_Display_Item = P_SPEC_CENTER+1;
	else		Total_Display_Item = P_SPEC_CENTER;

	if(DispMode == DispMode_SELECT_CH)
		DispMode = DispMode_BROWSE_ITEMS;

	if(DispMode == DispMode_BROWSE_ITEMS) {
		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(type) {
				ShowScrollBar_Other(Scroll_Bar_Start_X,Disp_Start_Y0,Total_Display_Item,Disp_Item_Num1,Disp_Interval,Scroll_Bar_Width,DispScrStartCT);
				GUI_SetBkColor(Parameter_Bottom_Bolor);
			}
			if((DispScrCurrLoc == DispScrEndCT)||(DispScrCurrLoc == DispScrStartCT)) {
				if( i == DispScrCurrLoc)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(Disp_Start_X,Disp_Start_Y0+j*Disp_Interval);
				GUI_DispChars(' ',HiLight_Length);
			} else {
				if( i == DispScrCurrLoc || i == B_DispCT ) {
					if( i==DispScrCurrLoc)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					GUI_GotoXY(Disp_Start_X,Disp_Start_Y0+j*Disp_Interval);
					GUI_DispChars(' ',HiLight_Length);
				}
			}
			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( spec_str[i], Disp_Start_X, Disp_Start_Y0+j*Disp_Interval);

			if(i==P_SPEC_TEST) {
				if(Disp_tmp->SPEC)	sprintf( str, " ON ");
				else				sprintf( str, " OFF ");
			} else if(i==P_SPEC_DELAY) {
				fdat=Disp_tmp->P_F_Delay/10.0;
				Display_Parameter_Pro(fdat,str,1);
			} else if(i==P_SPEC_ENTRY) {
				if(Disp_tmp->SPECTYPE)	sprintf( str, " Percent ");
				else					sprintf( str, " Value ");
			} else if(i==P_SPEC_CENTER) {
				/*Center*/
				dat = GetChanData(i+1,0);				/* Get Paramter */
				fdat = StepToReal(dat,0);				/* Get Resolution, Max, Min */
				if(CV_MODE!=Disp_tmp->CURRMODE)	Precision = (ptrMODEL_TYPE->CC_SPEC)[0].precision;
				else							Precision = (ptrMODEL_TYPE->CV_SPEC)[0].precision;
				Display_Parameter_Pro(fdat,str,Precision);
			} else {
				if(type) {
					/*High and Low*/
					dat = GetChanData( i+6,0);
					fdat1 = dat/10.0;
					Display_Parameter_Pro(fdat1,str,1);
				} else {
					dat = GetChanData( i+4,0);
					fdat = StepToReal(dat, i-3);
					if(CV_MODE!=Disp_tmp->CURRMODE)	Precision = (ptrMODEL_TYPE->CC_SPEC)[0].precision;
					else							Precision = (ptrMODEL_TYPE->CV_SPEC)[0].precision;
					Display_Parameter_Pro(fdat,str,Precision);
				}
			}
			GUI_SetColor(Parameter_Font_R_Bolor);
			if( (i==P_SPEC_TEST)||(i==P_SPEC_DELAY) )	ShowSpace( 4 , Para_Start_X, Disp_Start_Y0+j*Disp_Interval );
			else										ShowSpace( 7 , Para_Start_X, Disp_Start_Y0+j*Disp_Interval );
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
			GUI_SetTextAlign(GUI_TA_LEFT);
			if(i==P_SPEC_DELAY)
				GUI_DispStringAt( " s ", Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
			if(i<P_SPEC_HIGH)
				continue;
			if( type ) {
				if( M_num==P_CC_SPEC || M_num==P_CR_SPEC || M_num==P_CP_SPEC )
					GUI_DispStringAt( spec_unit_pcet[i-3], Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
				else
					GUI_DispStringAt( spec1_unit_pcet[i-3], Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
			} else {
				if( M_num==P_CC_SPEC || M_num==P_CR_SPEC || M_num==P_CP_SPEC )
					GUI_DispStringAt( spec_unit_val[i-3], Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
				else
					GUI_DispStringAt( spec1_unit_val[i-3], Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if( KeyInFlag & DIGI_KEY_IN ) {
			/* Show Keyin Data on Screen */
			sprintf( str, " %s " , KeyinBuf );
		} else {
			/* Show Memory Data on Screen */
			if(DispScrCurrLoc==P_SPEC_TEST) {
				if(Disp_tmp->SPEC)	sprintf( str, " ON ");
				else				sprintf( str, " OFF ");
			} else if(DispScrCurrLoc==P_SPEC_DELAY) {
				fdat=Disp_tmp->P_F_Delay/10.0;
				Display_Parameter_Pro(fdat,str,1);
			} else if(DispScrCurrLoc==P_SPEC_ENTRY) {
				if(Disp_tmp->SPECTYPE)	sprintf( str, " Percent ");
				else					sprintf( str, " Value ");
			} else if(DispScrCurrLoc==P_SPEC_CENTER) {
				dat = GetChanData( DispScrCurrLoc+1,0);				/* Get Paramter */
				fdat = StepToReal(dat,0);					/* Get Resolution, Max, Min */
				if(CV_MODE!=Disp_tmp->CURRMODE)	Precision = (ptrMODEL_TYPE->CC_SPEC)[0].precision;
				else							Precision = (ptrMODEL_TYPE->CV_SPEC)[0].precision;
				Display_Parameter_Pro(fdat,str,Precision);
			} else {
				if(type) {
					dat = GetChanData( DispScrCurrLoc+6,0);
					fdat1 = dat/10.0;
					Display_Parameter_Pro(fdat1,str,1);
				} else {
					dat = GetChanData( DispScrCurrLoc+4,0);
					fdat = StepToReal(dat, DispScrCurrLoc-3);
					if(CV_MODE!=Disp_tmp->CURRMODE)	Precision = (ptrMODEL_TYPE->CC_SPEC)[0].precision;
					else							Precision = (ptrMODEL_TYPE->CV_SPEC)[0].precision;
					Display_Parameter_Pro(fdat,str,Precision);
				}
			}
		}
		if((DispScrCurrLoc==P_SPEC_TEST)||(DispScrCurrLoc==P_SPEC_DELAY))
			ShowSpace( 4 , Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval );
		else
			ShowSpace( 7 , Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval );
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
	}
}

void RedrawSync(void)
{
	long dat;
	int i,j;
	char Total_Display_Item,Sta_Dyna,str[20],ScrollBar_Flag=0;
	double fdat;
	unsigned char Total_Item;

	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	ConfigureSeparator();

	if(DispMode_BROWSE_ITEMS==DispMode) {
		Displine(2,100,268,MEM_GRAY);
		Displine(2,101,268,GW_ORANGE_ku);
		Displine(2,102,268,MEM_WHITE);
		Displine(2,103,268,MEM_LIGHTGRAY_ku);

		if((Model_Number == MODEL3031E) ||(Model_Number == MODEL3032E))
			Total_Item = P_Para_MAX - 1;
		else
			Total_Item = P_Para_MAX;

		for(i = 0 ; i < Total_Item ; i++) {
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&(DispMode == DispMode_BROWSE_ITEMS) && ( i != B_DispCT && i != DispCT ) )
				continue;
			GUI_SetBkColor(Parameter_Bottom_Bolor);

			if(DispMode != DispMode_SELECT_CH && ( i == B_DispCT || i == DispCT ) ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);

				if(i==P_Para_Operation)
					GUI_GotoXY(	Disp_Start_X, Disp_Start_Y0+ i*Disp_Interval);
				else
					GUI_GotoXY(	Disp_Start_X, Disp_Start_Y0+ i*Disp_Interval+10);
				GUI_DispChars(' ', HiLight_Length);
			}
			GUI_SetTextAlign(GUI_TA_LEFT);

			if((Operation_Slave==Disp_tmp->CONF.Para_Data.Mode)&&(i>P_Para_Operation))
				GUI_SetColor(MEM_DARKGRAY);
			else if(Disp_tmp->CONF.Para_Data.Parallel_Number && (i == P_Para_Booster) )
				GUI_SetColor(MEM_DARKGRAY);
			else if( Disp_tmp->CONF.Para_Data.Booster_Number && (i == P_Para_Unit) )
				GUI_SetColor(MEM_DARKGRAY);
			else
				GUI_SetColor(Parameter_Font_L_Bolor);

			if(i==P_Para_Operation) {
				GUI_DispStringAt( Parallel_item[i], Disp_Start_X, Disp_Start_Y0+i*Disp_Interval);
				ShowSpace( 6, Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
			} else {
				GUI_DispStringAt( Parallel_item[i], Disp_Start_X, Disp_Start_Y0+i*Disp_Interval+10);
				ShowSpace( 6, Para_Start_X, Disp_Start_Y0 + i*Disp_Interval+10);
			}

			dat = GetChanData(i,0);
			GUI_SetTextAlign(GUI_TA_RIGHT);

			if( (Operation_Slave==Disp_tmp->CONF.Para_Data.Mode)&&(i>P_Para_Operation) )
				GUI_SetColor(MEM_DARKGRAY);
			else if( Disp_tmp->CONF.Para_Data.Parallel_Number && (i == P_Para_Booster) )
				GUI_SetColor(MEM_DARKGRAY);
			else if( Disp_tmp->CONF.Para_Data.Booster_Number && (i == P_Para_Unit) )
				GUI_SetColor(MEM_DARKGRAY);
			else
				GUI_SetColor(Parameter_Font_R_Bolor);

			if(i==P_Para_Operation)	GUI_DispStringAt(Parallel_Mode[dat],
				                Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
			else {
				if(dat) {
					if(P_Para_Unit==i)
						sprintf( str, " %d ", dat+1 );
					else
						sprintf( str, " %d ", dat );
				} else
					sprintf( str, " OFF ");
				GUI_DispStringAt(str,Para_Start_X, Disp_Start_Y0 + i*Disp_Interval+10);
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		dat = GetChanData(DispCT,0);
		if(DispCT==P_Para_Operation)
			ShowSpace( 6, Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		else
			ShowSpace( 6, Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval+10);
		GUI_SetTextAlign(GUI_TA_RIGHT);

		if(DispCT==P_Para_Operation)
			GUI_DispStringAt(Parallel_Mode[dat], Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		else {
			if(dat) {
				if(P_Para_Unit==DispCT)
					sprintf( str, " %d ", dat+1 );
				else
					sprintf( str, " %d ", dat );
			} else
				sprintf( str, " OFF ");
			GUI_DispStringAt(str,Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval+10);
		}
	}
}

void RedrawKnobData(void)
{
	long dat;
	char str[20],range,Total_Display_Item;
	int i,j;
	double fdat;
	double Para_s = Get_Parallel_Parameter(P3k_Chan_Data.IRange);

	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	Total_Display_Item = P_Konb_MAX;

	ConfigureSeparator();

	if(DispMode==DispMode_SELECT_CH)
		DispMode=DispMode_BROWSE_ITEMS;

	if(DispMode == DispMode_BROWSE_ITEMS) {
		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);

			if( (DispScrCurrLoc == DispScrEndCT) || (DispScrCurrLoc == DispScrStartCT) ) {
				ShowScrollBar_Other(Scroll_Bar_Start_X,Disp_Start_Y0,Total_Display_Item,Disp_Item_Num1,Disp_Interval,Scroll_Bar_Width,DispScrStartCT);
				GUI_SetBkColor(Parameter_Bottom_Bolor);

				if(((i == DispScrCurrLoc) && (!Disp_tmp->CONF.Knob_Status))||((Disp_tmp->CONF.Knob_Status) && i==P_Knob_Status))
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);

				GUI_GotoXY(Disp_Start_X,Disp_Start_Y0+j*Disp_Interval);
				GUI_DispChars(' ',HiLight_Length);
			} else {
				if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispScrCurrLoc ) )
					continue;

				if( i == DispScrCurrLoc || i == B_DispCT ) {
					if( i==DispScrCurrLoc )
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);

					GUI_GotoXY(Disp_Start_X,Disp_Start_Y0+j*Disp_Interval);
					GUI_DispChars(' ',HiLight_Length);
				}
			}

			if(Disp_tmp->CONF.Knob_Status && i>=P_CCH_STEP)
				GUI_SetColor(MEM_DARKGRAY);
			else
				GUI_SetColor(Parameter_Font_L_Bolor);

			GUI_DispStringAt(conf_knob[i],Disp_Start_X, Disp_Start_Y0+j*Disp_Interval);
			ShowSpace( 7, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);

			dat = GetChanData(i,0);
			GUI_SetTextAlign(GUI_TA_RIGHT);

			if(Disp_tmp->CONF.Knob_Status && i>=P_CCH_STEP)
				GUI_SetColor(MEM_DARKGRAY);
			else
				GUI_SetColor(Parameter_Font_R_Bolor);

			switch(i) {
			case P_Knob_Status:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( knob_status[dat], Para_Start_X+52, Disp_Start_Y0+j*Disp_Interval);
				break;
			case P_CCH_STEP://	case P_CCM_STEP:
			case P_CCL_STEP:
				fdat=StepToReal(dat, i)*Para_s;

				if(i==P_CCH_STEP)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[10].precision);
				//else if(i==P_CCM_STEP)
				//	Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[10].precision);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[0].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( " A ", Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
				break;
			case P_CRH_STEP://case P_CRM_STEP:
			case P_CRL_STEP:
				fdat=StepToReal(dat, i)*Para_s;

				if(i==P_CRH_STEP)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[10].precision);
				//else if(i==P_CRM_STEP)
				//	Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[10].precision);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[0].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( " mS ", Unit_Start_X, Disp_Start_Y0+j*Disp_Interval);
				break;
			case P_CVH_STEP:
			case P_CVL_STEP:
				fdat=StepToReal(dat, i);

				if(i==P_CVH_STEP)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[3].precision);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[0].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( " V ", Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
				break;
			case P_CPH_STEP:
				//case P_CPM_STEP:
			case P_CPL_STEP:
				fdat=StepToReal(dat, i)*Para_s;

				if(i==P_CPH_STEP)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[10].precision);
				//else if(i==P_CPM_STEP)
				//	Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[10].precision);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[0].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+j*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( " W ", Unit_Start_X, Disp_Start_Y0+j*Disp_Interval );
				break;
			default:
				break;
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN) {
			ShowSpace( conf_knob_space[DispScrCurrLoc], Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			sprintf( str, " %s " , KeyinBuf );
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		} else {
			dat = GetChanData(DispScrCurrLoc,0);
			ShowSpace( conf_knob_space[DispScrCurrLoc], Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			fdat=StepToReal(dat, DispScrCurrLoc);

			switch(DispScrCurrLoc) {
			case P_Knob_Status:
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( knob_status[dat], Para_Start_X+52, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_CCH_STEP:
				//case P_CCM_STEP:
			case P_CCL_STEP:
				fdat=StepToReal(dat, DispScrCurrLoc)*Para_s;

				if(DispScrCurrLoc==P_CCH_STEP)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[10].precision);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[0].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_CRH_STEP:
				//case P_CRM_STEP:
			case P_CRL_STEP:
				fdat=StepToReal(dat, DispScrCurrLoc)*Para_s;

				if(DispScrCurrLoc==P_CRH_STEP)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[10].precision);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[0].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_CVH_STEP:
			case P_CVL_STEP:
				fdat=StepToReal(dat, DispScrCurrLoc);

				if(DispScrCurrLoc==P_CVH_STEP)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[3].precision);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CV)[0].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			case P_CPH_STEP:
				//case P_CPM_STEP:
			case P_CPL_STEP:
				fdat=StepToReal(dat, DispScrCurrLoc)*Para_s;

				if(DispScrCurrLoc==P_CPH_STEP)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[10].precision);
				else
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[0].precision);

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				break;
			default:
				break;
			}
		}
	}
}


void RedrawExtFunction(void)
{
	long dat;
	int i,j;
	char Total_Display_Item,Sta_Dyna,str[20],ScrollBar_Flag=0;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	ConfigureSeparator();

	if(DispMode_BROWSE_ITEMS == DispMode) {
		for(i=0 ; i<P_Ext_MAX ; i++) {
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&(DispMode == DispMode_BROWSE_ITEMS) && ( i != B_DispCT && i != DispCT ) )
				continue;
#if NF_flag
			if(i>= P_Extmulti_para)break;
#endif
			GUI_SetBkColor(Parameter_Bottom_Bolor);

			if(DispMode != DispMode_SELECT_CH && ( i == B_DispCT || i == DispCT ) ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);

				GUI_GotoXY(	Disp_Start_X, Disp_Start_Y0+ i*Disp_Interval);
				GUI_DispChars(' ', HiLight_Length);
			}

			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( External_item[i], Disp_Start_X, Disp_Start_Y0+i*Disp_Interval);
			ShowSpace( 6, Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
			dat = GetChanData(i,0);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_SetColor(Parameter_Font_R_Bolor);

			if(P_Ext_Control==i)
				GUI_DispStringAt(External_Control[dat],	Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
			else if(P_Ext_LoadON_IN==i) {
				if(P3k_Chan_Data.CONF.Ext_Setting.MultilPara)
					GUI_SetColor(Parameter_Font_Bolor_Para);
				GUI_DispStringAt(External_LoadOnIn[dat], Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
			} else
				GUI_DispStringAt(External_Multi[dat], Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);

		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		dat = GetChanData(DispCT,0);
		ShowSpace( 6, Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);

		if(P_Ext_Control==DispCT)
			GUI_DispStringAt(External_Control[dat],	Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		else if(P_Ext_LoadON_IN==DispCT) {
			GUI_DispStringAt(External_LoadOnIn[dat], Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		} else if(P_Extmulti_para==DispCT) {
			GUI_DispStringAt(External_Multi[dat], Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		}

	}
}
#endif

void RedrawProgMain(void)
{
	int i,j;
	char str[20];
	long dat;
	double fdat;

	if(DispMode == DispMode_SELECT_CH) {
		if(DataRedrawFlag&BG_CLEAR_FLAG) {
			Displine(2,94,316,MEM_GRAY);
			Displine(2,95,316,GW_ORANGE_ku);
			Displine(2,96,316,MEM_WHITE);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_DispStringAt( " Timing Edit for Program ", 55, 40);
		}
		for( i=0 ; i<=7 ; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				continue;
			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(SeqMain_item_x_addr[i]-5,SeqMain_item_y_addr[i]);
				GUI_DispChars(' ',hilight_space[i]);
			}
			if(i<2)		GUI_SetColor(Parameter_Font_U_Bolor);
			else		GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( item_str[i], SeqMain_item_x_addr[i], SeqMain_item_y_addr[i]);
			dat = GetChanData( i , 0);

			if( i==Program_PROG || i==Program_STEP)	sprintf( str, "%02d", dat+1);
			else if( i==Program_Memory)				sprintf( str, "M%03d", dat+1);
			else if( i==Program_Run)				strcpy( str, run[dat]);
			else if( i==Program_P_F_Time) {
				fdat = dat *0.1;
				if(fdat==0)		sprintf(str, " Off ");
				else 			Display_Parameter_Pro(fdat,str,1);
			} else {
				fdat = dat *0.1;
				if(fdat==0)		sprintf(str, " Off ");
				else 			Display_Parameter_Pro(fdat,str,1);
			}
			GUI_SetColor(Parameter_Font_R_Bolor);
			ShowSpace(val_space[i], val_space_x_addr[i], SeqMain_item_y_addr[i]);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, SeqMain_val_x_addr[i], SeqMain_item_y_addr[i]);
		}
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_SetTextAlign(GUI_TA_LEFT);
	} else if(DispMode == DispMode_BROWSE_ITEMS) {
		if((DispCT==Program_PROG)||(DispCT==Program_STEP)) {
			for( i=0 ; i<=7 ; i++) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);

				if( i == DispCT)
					continue;

				if(i<2)		GUI_SetColor(Parameter_Font_U_Bolor);
				else		GUI_SetColor(Parameter_Font_L_Bolor);

				GUI_DispStringAt( item_str[i], SeqMain_item_x_addr[i], SeqMain_item_y_addr[i]);
				dat = GetChanData( i , 0);

				if( i==Program_PROG || i==Program_STEP)		sprintf( str, "%02d", dat+1);
				else if( i==Program_Memory)					sprintf( str, "M%03d", dat+1);
				else if( i==Program_Run)					strcpy( str, run[dat]);
				else if( i==Program_P_F_Time) {
					fdat = dat *0.1;
					if(fdat==0)		sprintf(str, " Off ");
					else 			Display_Parameter_Pro(fdat,str,1);
				} else {
					fdat = dat *0.1;
					if(fdat==0)		sprintf(str, " Off ");
					else			Display_Parameter_Pro(fdat,str,1);
				}
				GUI_SetColor(Parameter_Font_R_Bolor);
				ShowSpace(val_space[i], val_space_x_addr[i], SeqMain_item_y_addr[i]);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, SeqMain_val_x_addr[i], SeqMain_item_y_addr[i]);
			}
		}
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN)
			sprintf(str, "%s", KeyinBuf);
		else {
			dat = GetChanData(DispCT,0);
			if( DispCT==Program_PROG || DispCT==Program_STEP)		sprintf( str, "%02d", dat+1);
			else if( DispCT == Program_Memory)					sprintf( str, "M%03d", dat+1);
			else if( DispCT==Program_Run)							strcpy( str, run[dat]);
			else if( DispCT==Program_P_F_Time) {
				fdat = dat *0.1;
				if(fdat==0)		sprintf(str, " Off ");
				else			Display_Parameter_Pro(fdat,str,1);
			} else {
				fdat = dat *0.1;
				if(fdat==0)		sprintf(str, " Off ");
				else			Display_Parameter_Pro(fdat,str,1);
			}
		}
		ShowSpace(val_space[DispCT], val_space_x_addr[DispCT], SeqMain_item_y_addr[DispCT]);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, SeqMain_val_x_addr[DispCT], SeqMain_item_y_addr[DispCT]);
	}
}
void RedrawProgChain(void)
{
	char tmp,str[20];
	int i,j,tmp1;
	/* Show Title */
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);
	GUI_DispStringAt( " Program Chain Set ", 70, Disp_Start_Y2+ 0*Disp_Interval);

	if(DispMode == DispMode_SELECT_CH)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);
	else								GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_GotoXY( 103, Disp_Start_Y2+ 1*Disp_Interval );
	GUI_DispChars(' ',11);

	sprintf( str, " Start " );
	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_DispStringAt(str, 105, Disp_Start_Y2+ 1*Disp_Interval);

	/* Show Run PROGram Start No */
	if(DispMode==DispMode_SELECT_CH) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
	} else {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_R_Bolor);
	}

	tmp = p3k_Disp_PROG.Chain_Start_Prog;
	sprintf( str, " P%02d ", tmp+1);
	ShowSpace(2, 203, Disp_Start_Y2+ 1*Disp_Interval);
	GUI_SetTextAlign(GUI_TA_RIGHT);
	GUI_DispStringAt(str, 200, Disp_Start_Y2+ 1*Disp_Interval);

	/* Show Parameter */
	if(DispMode <= DispMode_BROWSE_ITEMS) {
		for ( i=DispScrStartCT, j=0 ; i<= DispScrEndCT ; i++, j++) {
			/* Show Prog Number */
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(DispMode == DispMode_BROWSE_ITEMS) {
				if( (DispScrCurrLoc == DispScrEndCT) || (DispScrCurrLoc == DispScrStartCT) ) {
					ShowScrollBar_Other(305,Disp_Start_Y2+2*Disp_Interval,16,4,Disp_Interval,10,DispScrStartCT);
					GUI_SetBkColor(Parameter_Bottom_Bolor);
					if( i == DispScrCurrLoc)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					GUI_GotoXY(76,Disp_Start_Y2+((j+2)*Disp_Interval));
					GUI_DispChars(' ',33);
				} else {
					if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != DispScrCurrLoc && i != B_DispCT ) )
						continue;
					if( i == DispScrCurrLoc || i == B_DispCT ) {
						if( i==DispScrCurrLoc)
							GUI_SetBkColor(Parameter_Select_Bar_Bolor);
						GUI_GotoXY(76,Disp_Start_Y2+((j+2)*Disp_Interval));
						GUI_DispChars(' ',33);
					}
				}
			}
			sprintf( str, "P%02d", i+1);
			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( str, 90, Disp_Start_Y2+((j+2)*Disp_Interval));
			/* Draw Arrow Point */
			DrawArrowPoint(145, 12+Disp_Start_Y2+((j+2)*Disp_Interval));

			/* Show Prog Mirror Number */
			tmp = p3k_Disp_PROG.PROGSEQ[i];

			if( tmp == 0)	sprintf( str, " Off " );
			else			sprintf( str, "P%02d", tmp);
			GUI_SetColor(Parameter_Font_R_Bolor);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, 230, Disp_Start_Y2+((j+2)*Disp_Interval));
		}
	}
	if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		tmp1 = DispScrCurrLoc - DispScrStartCT;
		if(KeyInFlag&DIGI_KEY_IN)
			sprintf(str, "P%s", KeyinBuf);
		else {
			/* Show Prog Mirror Number */
			tmp = p3k_Disp_PROG.PROGSEQ[DispScrCurrLoc];
			if( tmp == 0)	sprintf( str, " Off " );
			else			sprintf( str, "P%02d", tmp);
		}
		ShowSpace(3,233,Disp_Start_Y2+((tmp1+2)*Disp_Interval));
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, 230, Disp_Start_Y2+((tmp1+2)*Disp_Interval));
	}
}
void RedrawSeqRun(void)
{
	char tmp,str[20];
	int i,j,tmp1;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);
	GUI_DispStringAt( "Active Channels for Program Mode", 10, Disp_Start_Y2);
	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_DispStringAt( "CH", 85, Disp_Start_Y2+ 1*Disp_Interval);
	GUI_DispStringAt( "Active", 186, Disp_Start_Y2+ 1*Disp_Interval);

	/* Show Parameter */
	if(DispMode == DispMode_SELECT_CH) {
		for ( i=DispScrStartCT, j=0 ; i<= DispScrEndCT ; i++, j++) {
			/* Show Prog Number */
			GUI_SetBkColor(Parameter_Bottom_Bolor);

			if( (DispScrCurrLoc == DispScrEndCT) || (DispScrCurrLoc == DispScrStartCT) ) {
				if(Data_tmp->CONF.Ext_Setting.Control) {
					GUI_SetColor(Message_Font_Bolor);
					GUI_DispStringAt( " EXT ", 250, Disp_Start_Y2+((j+2)*Disp_Interval));
				} else
					ShowSpace_LEFT( 4, 250, Disp_Start_Y2+((j+2)*Disp_Interval));
				if( i == DispScrCurrLoc)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(76,Disp_Start_Y2+((j+2)*Disp_Interval));
				GUI_DispChars(' ',33);
			} else {
				if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != DispScrCurrLoc && i != B_DispCT ) )
					continue;
				if( i == DispScrCurrLoc || i == B_DispCT ) {
					if( i==DispScrCurrLoc)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					GUI_GotoXY(76,Disp_Start_Y2+((j+2)*Disp_Interval));
					GUI_DispChars(' ',33);
				}
			}
			/* Draw Channel No */
			sprintf( str, "%02d", i+1);
			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( str, 90, Disp_Start_Y2+((j+2)*Disp_Interval));
			/* Draw Arrow Point */
			//DrawArrowPoint(145, 96+j*22);
			DrawArrowPoint(145, 12+Disp_Start_Y2+((j+2)*Disp_Interval));
			/* Show Prog Mirror Number */
			tmp = D_RUNPROG.ACTCH[i];
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_SetColor(Parameter_Font_R_Bolor);
			GUI_DispStringAt( onoff_str[tmp], 230, Disp_Start_Y2+((j+2)*Disp_Interval));
		}
	}
	if(DispMode == DispMode_BROWSE_ITEMS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		/* Show Prog Mirror Number */
		tmp = D_RUNPROG.ACTCH[DispScrCurrLoc];
		tmp1 = DispScrCurrLoc - DispScrStartCT;
		ShowSpace( 4, 233, Disp_Start_Y2+((tmp1+2)*Disp_Interval));
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( onoff_str[tmp], 230, Disp_Start_Y2+((tmp1+2)*Disp_Interval));
	}
}

static const char Media_USB_Item[4][25]	= { " Data Type ",	" Save File ",		" Recall File "," Save Folder " };
static const char FileChan_title[3][25]	= { " Memory ",		" Setup Memory ",	" Preset " };
static const char FileChan_Data[5][25]	= { " Memory ",		" Setup ",			" Preset ",		" NSeq. ", " FSeq. " };
static const int FileChan_space[2]= {9,5};
static const int Memory_y_addr[2] = { 65, 100 };
static const int USB_y_addr[3]	 = {65, 100, 125  };		/* USB string Y location */

void RedrawFileChan(void)
{
	int i;
	char str[30];
	OverWrite_Flag = 0;

	if(Save_Recall_InfoFlag&Data_Process) { /*Show Message*/
		if( (F_Media_USB==p3k_File_Utility_BAR.MEDIA)||(F_Media_Default==p3k_File_Utility_BAR.MEDIA) ) { /*Media USB*/
			GUI_SetBkColor(Message_Bottom_Bolor);
			GUI_GotoXY(Disp_Start_X, 175);
			GUI_DispChars(' ',51);
			GUI_SetColor(Message_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);

			if(Save_Recall_InfoFlag&Save_Ok) {
				Save_Recall_InfoFlag&=~Save_Ok;
				sprintf(str," %s Save Ok ",SaveFileName_Temp);
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else if(Save_Recall_InfoFlag&Save_Fail) {
				Save_Recall_InfoFlag&=~Save_Fail;
				sprintf(str," %s Save Failed ",SaveFileName_Temp);
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else if(Save_Recall_InfoFlag&Save_All_Ok) {
				Save_Recall_InfoFlag&=~Save_All_Ok;
				sprintf(str," %s Save Ok ",SaveFileName_Temp);
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else if(Save_Recall_InfoFlag&Save_All_Fail) {
				Save_Recall_InfoFlag&=~Save_All_Fail;
				sprintf(str," %s Save Failed ",SaveFileName_Temp);
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else if(Save_Recall_InfoFlag&Recall_Ok) {
				Save_Recall_InfoFlag&=~Recall_Ok;
				sprintf(str," %s Recall Ok ",RecallFileName);
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else if(Save_Recall_InfoFlag&Recall_Fail) {
				Save_Recall_InfoFlag&=~Recall_Fail;
				sprintf(str," %s Recall Failed ",RecallFileName);
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else if(Save_Recall_InfoFlag&Type_Error) {
				Save_Recall_InfoFlag&=~Type_Error;
				sprintf(str," Machine Type Error ");
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else if(Save_Recall_InfoFlag&Device_Error) {
				Save_Recall_InfoFlag&=~Device_Error;
				sprintf(str," Device Open Error ");
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else if(Save_Recall_InfoFlag&No_File) {
				Save_Recall_InfoFlag&=~No_File;
				sprintf(str," No File to Recall ");
				GUI_DispStringAt(str, Disp_Start_X, 175);
			} else
				Save_Recall_InfoFlag&=~Data_Process;
		} else
			Save_Recall_InfoFlag&=~Data_Process;
	}
	/*-------------------Media:Default------------------*/
	if(F_Media_Default==p3k_File_Utility_BAR.MEDIA) { /*Media Default*/
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt(" Load Default Setup ", Disp_Start_X, 40);
		DispMode = DispMode_SELECT_CH;
		DispCT = 0;
		return;
	}
	/*-------------------Media:USB------------------*/
	if(F_Media_USB==p3k_File_Utility_BAR.MEDIA) { /*Media USB*/
		Displine(2,94,267,MEM_GRAY);
		Displine(2,95,267,GW_ORANGE_ku);
		Displine(2,96,267,MEM_WHITE);
		if(DispMode ==DispMode_SELECT_CH) {
			for( i=0 ; i < P_USB_Max ; i++) {
				if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i!=B_DispCT && i!=DispCT ) )
					continue;
				GUI_SetBkColor(Parameter_Bottom_Bolor);

				if( i==DispCT )
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);

				GUI_GotoXY(Disp_Start_X, USB_y_addr[i]);
				GUI_DispChars(' ',52);

				if(i==P_USB_Type)
					GUI_SetColor(Parameter_Font_U_Bolor);
				else
					GUI_SetColor(Parameter_Font_L_Bolor);

				GUI_DispStringAt(Media_USB_Item[i], Disp_Start_X, USB_y_addr[i]);

				if(i==P_USB_Type)
					sprintf(str, " %s ", FileChan_Data[p3k_File_Utility_BAR.USB_Data_Type]);
				else if(i==P_USB_Save) {
					if(SaveFileName[0]==0)
						sprintf( SaveFileName, " No File ");

					sprintf( str, " %s ", SaveFileName);
				} else if(i==P_USB_Recall) {
					if(RecallFileName[0]==0)
						sprintf( RecallFileName, " No File ");

					sprintf( str, " %s ", RecallFileName);
				}
				GUI_SetColor(Parameter_Font_R_Bolor);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt(str, 260, USB_y_addr[i]);
			}
		} else {
			GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
			GUI_SetColor(Parameter_Select_Font_Bolor);

			if(DispCT==P_USB_Type)
				sprintf(str, " %s ", FileChan_Data[p3k_File_Utility_BAR.USB_Data_Type]);
			else if(DispCT==P_USB_Save)
				sprintf(str, " %s ", SaveFileName);
			else if(DispCT==P_USB_Recall)
				sprintf(str, " %s ", RecallFileName);

			if(DispCT==P_USB_Type)
				ShowSpace( 11, 260+5, USB_y_addr[DispCT]);
			else {
				GUI_GotoXY(135, USB_y_addr[DispCT]);
				GUI_DispChars(' ',26);
			}
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, 260, USB_y_addr[DispCT]);
		}

		if(USB_Status_Display==USB_Exist) {
			GUI_SetBkColor(Message_Bottom_Bolor);
			GUI_SetColor(Noted_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_DispStringAt(" Path: ", Disp_Start_X, 150);
			GUI_DispStringAt(FMShowfilePath, 65, 150);
		}
		return;
	}
	/*-------------------Media:Memory------------------*/
	if(DispMode ==DispMode_SELECT_CH) {
		Displine(2,94,267,MEM_GRAY);
		Displine(2,95,267,GW_ORANGE_ku);
		Displine(2,96,267,MEM_WHITE);
		for( i=0 ; i<P_Memory_Max ; i++) {
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				continue;

			GUI_SetBkColor(Parameter_Bottom_Bolor);

			if( i==DispCT )
				GUI_SetBkColor(Parameter_Select_Bar_Bolor);

			GUI_GotoXY(5, Memory_y_addr[i]);
			GUI_DispChars(' ',52);

			if(i==P_Memory_Type) {
				GUI_SetColor(Parameter_Font_U_Bolor);
				GUI_DispStringAt(" Data Type ", 5, Memory_y_addr[i]);
			} else {
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt(FileChan_title[p3k_File_Utility_BAR.Mem_Data_Type], 5, Memory_y_addr[i]);
			}

			GUI_SetColor(Parameter_Font_R_Bolor);

			if(i==P_Memory_Type)
				sprintf(str, " %s ", FileChan_Data[p3k_File_Utility_BAR.Mem_Data_Type]);
			else if(i==P_Memory_Number) {
				if(p3k_File_Utility_BAR.Mem_Data_Type==F_Memory_Data)
					sprintf(str," M%03d ",	p3k_File_Utility_BAR.MEMORY_ADDR+1);
				else if(p3k_File_Utility_BAR.Mem_Data_Type==F_Setup_Data)
					sprintf(str," %d ",		p3k_File_Utility_BAR.SMEMORY_ADDR+1);
				else if(p3k_File_Utility_BAR.Mem_Data_Type==F_Preset_Data)
					sprintf(str," P%d ",	p3k_File_Utility_BAR.PRE_MEMORY_ADDR);
			}

			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt(str, 260, Memory_y_addr[i]);
		}
		GUI_SetBkColor(Message_Bottom_Bolor);

		if(MEMORY_SAVE_FLAG==M_Clear_Message) {
			GUI_SetColor(Message_Font_Bolor);
			GUI_GotoXY(Disp_Start_X, 175);
			GUI_DispChars(' ',51);
			MEMORY_SAVE_FLAG = M_Nothing;
		}

		if(MEMORY_SAVE_FLAG==M_Memory_Save_Ok) {
			GUI_SetColor(Message_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			sprintf(str," Memory No %03d Save Ok ",p3k_File_Utility_BAR.MEMORY_ADDR+1);
			GUI_DispStringAt(str, Disp_Start_X, 175);
			MEMORY_SAVE_FLAG = M_Clear_Message;
		}

		if(MEMORY_SAVE_FLAG==M_Setup_Save_Ok) {
			GUI_SetColor(Message_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			sprintf(str," Setup Memory %d Save Ok ",p3k_File_Utility_BAR.SMEMORY_ADDR+1);
			GUI_DispStringAt(str, Disp_Start_X, 175);
			MEMORY_SAVE_FLAG = M_Clear_Message;
		}

		if(MEMORY_SAVE_FLAG==M_Setup_Recall_Ok) {
			GUI_SetColor(Message_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			sprintf(str," Setup Memory %d Recall Ok ",p3k_File_Utility_BAR.SMEMORY_ADDR+1);
			GUI_DispStringAt(str, Disp_Start_X, 175);
			MEMORY_SAVE_FLAG = M_Clear_Message;
		}

		if(MEMORY_SAVE_FLAG==M_Preset_Save_Ok) {
			GUI_SetColor(Message_Font_Bolor);
			GUI_SetTextAlign(GUI_TA_LEFT);
			sprintf(str," Preset P%d Save Ok ",p3k_File_Utility_BAR.PRE_MEMORY_ADDR);
			GUI_DispStringAt(str, Disp_Start_X, 175);
			MEMORY_SAVE_FLAG = M_Clear_Message;
		}
	} else {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN)
			sprintf(str, " %s ", KeyinBuf);
		else {
			if(DispCT==P_Memory_Type)
				sprintf(str, " %s ", FileChan_Data[p3k_File_Utility_BAR.Mem_Data_Type]);
			else if(DispCT==P_Memory_Number) {
				if(p3k_File_Utility_BAR.Mem_Data_Type==F_Memory_Data)
					sprintf(str," M%03d ",	p3k_File_Utility_BAR.MEMORY_ADDR+1);
				else if(p3k_File_Utility_BAR.Mem_Data_Type==F_Setup_Data)
					sprintf(str," %d ",		p3k_File_Utility_BAR.SMEMORY_ADDR+1);
				else if(p3k_File_Utility_BAR.Mem_Data_Type==F_Preset_Data)
					sprintf(str," P%d ",	p3k_File_Utility_BAR.PRE_MEMORY_ADDR);
			}
		}
		ShowSpace( FileChan_space[DispCT], 260, Memory_y_addr[DispCT]);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, 260, Memory_y_addr[DispCT]);
	}
}

void RedrawFileMachine(void)
{
}

void RedrawUtilityMain(void)
{
	/* Utility Main Frame */
	/* Just show Utility Function string on screen */
	GUI_SetColor(Parameter_Font_U_Bolor);
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_DispStringAt( " Utility Function ", 40, 40+0*25);
	//GUI_DispStringAt("Test...", 145, 120);
}

void RedrawInterface(void)
{
	long dat;
	char i,i_temp,str[20],DispCT_temp;

	if( DispMode == DispMode_SELECT_CH) {
		for( i=0 ; i<= 4 ; i++) {
			if((UTILITY.INTERFACE==INTERFACE_GPIB)&&(i==4))
				i_temp=1;
			else
				i_temp=i;
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i_temp != B_DispCT && i_temp != DispCT ) )
				continue;
			if((UTILITY.INTERFACE==INTERFACE_GPIB)&&(i>0)&&(i<4))
				continue;
			if((UTILITY.INTERFACE==INTERFACE_RS232)&&(i==4))
				continue;
			if((UTILITY.INTERFACE==INTERFACE_USB)&&(i>0))
				continue;
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if( i_temp == B_DispCT || i_temp == DispCT ) {
				if( i_temp == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(45, Interface_addr_y[i]);
				GUI_DispChars(' ',45);
			}

			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt(Interface_title[i], 45, Interface_addr_y[i]);

			GUI_SetTextAlign(GUI_TA_RIGHT);

			dat=GetChanData(i,0);
			GUI_SetColor(Parameter_Font_R_Bolor);
			if(i==0)		GUI_DispStringAt( Interface_Kind[dat],	260, Interface_addr_y[i]);
			else if(i==1)	GUI_DispStringAt( baudrate[dat],		260, Interface_addr_y[i]);
			else if(i==2)	GUI_DispStringAt( stopbit[dat], 		260, Interface_addr_y[i]);
			else if(i==3)	GUI_DispStringAt( parity[dat], 		260, Interface_addr_y[i]);
			else {
				sprintf( str, " %02d ", dat);
				GUI_DispStringAt( str, 260, Interface_addr_y[i]);
			}
		}
	} else {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		if( (UTILITY.INTERFACE==INTERFACE_GPIB)&&(DispCT==1) )		DispCT_temp = DispCT+3;
		else													DispCT_temp = DispCT;
		ShowSpace(Interface_space[DispCT_temp], 250, Interface_addr_y[DispCT_temp] );
		dat=GetChanData(DispCT_temp, 0);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		if(DispCT_temp==0)			GUI_DispStringAt( Interface_Kind[dat],	260,Interface_addr_y[DispCT_temp]);
		else if(DispCT_temp==1)		GUI_DispStringAt( baudrate[dat],		260,Interface_addr_y[DispCT_temp]);
		else if(DispCT_temp==2)		GUI_DispStringAt( stopbit[dat],		260,Interface_addr_y[DispCT_temp]);
		else if(DispCT_temp==3)		GUI_DispStringAt( parity[dat],		260,Interface_addr_y[DispCT_temp]);
		else {
			sprintf( str, " %02d ", dat);
			GUI_DispStringAt( str, 260, Interface_addr_y[DispCT_temp]);
		}
	}
}
void RedrawDateTime(void)
{
	int i;
	char str[20];
	long dat;

	if(DispMode==DispMode_SELECT_CH) {
		GUI_SetColor(Parameter_Font_U_Bolor);
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_DispStringAt( " Date/Time ", 110, 45 );
		for( i=0 ; i<= 4 ; i++) {
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&& ( i != B_DispCT && i != DispCT ) )
				continue;
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(45, 70+i*25);
				GUI_DispChars(' ',45);
			}

			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt(DateTime_title[i], 45, 70+i*25);

			GUI_SetTextAlign(GUI_TA_RIGHT);

			dat = GetChanData( i, 0);
			sprintf( str, "   %d  ", dat);
			GUI_SetColor(Parameter_Font_R_Bolor);
			GUI_DispStringAt( str, 260, 70+i*25);
		}
	} else {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		if( KeyInFlag & DIGI_KEY_IN ) {
			/* Show Keyin Data on Screen */
			sprintf( str, "   %s  " , KeyinBuf );
		} else {
			dat = GetChanData( DispCT, 0);
			sprintf( str, "   %d  ", dat);
		}
		ShowSpace( DateTime_space[DispCT], 250, 70+DispCT*25);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, 260, 70+DispCT*25);
	}
}

void RedrawUtility(void)
{
	int i,j;
	short dat;
	char str[20];

	if(DispMode==DispMode_SELECT_CH) {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_U_Bolor);
		GUI_DispStringAt( " Other Setting ", 90, 45);

		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);

			if( (DispScrCurrLoc == DispScrEndCT) || (DispScrCurrLoc == DispScrStartCT) ) {
				ShowScrollBar_Other(305,70,8,5,25,10,DispScrStartCT);
				GUI_SetBkColor(Parameter_Bottom_Bolor);

				if( i == DispScrCurrLoc)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);

				GUI_GotoXY(45,70+j*25);
				GUI_DispChars(' ',45);
			} else {
				if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != DispScrCurrLoc && i != B_DispCT ) )
					continue;

				if( i == DispScrCurrLoc || i == B_DispCT ) {
					if( i==DispScrCurrLoc)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);

					GUI_GotoXY(45,70+j*25);
					GUI_DispChars(' ',45);
				}
			}
			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt(utility_Other[i], 45, 70+j*25);

			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_SetColor(Parameter_Font_R_Bolor);

			switch(i) {
			case Util_Knob_Type:
				GUI_DispStringAt(knob_type[UTILITY.KEYKNOB], 260, 70+j*25);
				break;
			case Util_Speaker:
				GUI_DispStringAt(onoff_str[UTILITY.BEEP_ONOFF], 260, 70+j*25);
				break;
			case Util_Alarm_Tone:
				GUI_DispStringAt(onoff_str[UTILITY.Master_Alarm_Tone], 260, 70+j*25);
				break;
			case Util_UnReg_Tone:
				GUI_DispStringAt(onoff_str[UTILITY.UnReg_Alarm_Tone], 260, 70+j*25);
				break;
			case Util_Go_NoGO_Tone:
				GUI_DispStringAt(onoff_str[UTILITY.Master_NG_Tone], 260, 70+j*25);
				break;
			case Util_Contrast:
				dat = UTILITY.CONTRAST_LV;
				sprintf( str, "%d ", dat);
				GUI_DispStringAt( str, 260, 70+j*25);
				break;
			case Util_Brightness:
				dat = UTILITY.BRIGHTNESS_LV;
				sprintf( str, "%d ", dat);
				GUI_DispStringAt( str, 260, 70+j*25);
				break;
			case Util_Language:
				GUI_DispStringAt(display_Language[0], 260, 70+j*25);
				break;
			default:
				break;
			}
		}
	} else {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		ShowSpace(utility_Other_space[DispScrCurrLoc], 250, 70+(DispScrCurrLoc - DispScrStartCT)*25);
		GUI_SetTextAlign(GUI_TA_RIGHT);

		switch(DispScrCurrLoc) {
		case Util_Knob_Type:
			GUI_DispStringAt(knob_type[UTILITY.KEYKNOB], 260, 70+(DispScrCurrLoc - DispScrStartCT)*25);
			break;
		case Util_Speaker:
			GUI_DispStringAt(onoff_str[UTILITY.BEEP_ONOFF], 260, 70+(DispScrCurrLoc - DispScrStartCT)*25);
			break;
		case Util_Alarm_Tone:
			GUI_DispStringAt(onoff_str[UTILITY.Master_Alarm_Tone], 260, 70+(DispScrCurrLoc - DispScrStartCT)*25);
			break;
		case Util_UnReg_Tone:
			GUI_DispStringAt(onoff_str[UTILITY.UnReg_Alarm_Tone], 260, 70+(DispScrCurrLoc - DispScrStartCT)*25);
			break;
		case Util_Go_NoGO_Tone:
			GUI_DispStringAt(onoff_str[UTILITY.Master_NG_Tone], 260, 70+(DispScrCurrLoc - DispScrStartCT)*25);
			break;
		case Util_Contrast:
			dat = UTILITY.CONTRAST_LV;
			sprintf( str, "%d ", dat);
			GUI_DispStringAt( str, 260, 70+(DispScrCurrLoc - DispScrStartCT)*25);
			break;
		case Util_Brightness:
			dat = UTILITY.BRIGHTNESS_LV;
			sprintf( str, "%d ", dat);
			GUI_DispStringAt( str, 260, 70+(DispScrCurrLoc - DispScrStartCT)*25);
			break;
		case Util_Language:
			GUI_DispStringAt(display_Language[0], 260, 70+(DispScrCurrLoc - DispScrStartCT)*25);
			break;
		default:
			break;
		}
	}
}

extern UWORD PEL3000_FPGA_Date;
void RedrawSystemInfo(void)
{
	char str[20],i,j;
	char systemInfo_item[18][30];
	char systemInfo_Data[18][30];
	char model_temp[6];
	char p3k_Model_Number[20];

	Serial_Number_Str	*Serial = &P3k_Serial_Number;

	if(Serial->Version == TEXIO_Version) {
		if(MODEL3020==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "LSG-0175");
		else if(MODEL3031E==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "LSG-175");
		else if(MODEL3032E==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "LSG-350");
		else if(MODEL3070==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "LSG-700");
		else if(MODEL3111==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "LSG-1050");
		else
			sprintf( p3k_Model_Number, "LSG-Default");
	} else {
		if(MODEL3020==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "PEL-3020");
		else if(MODEL3031E==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "PEL-1031");
		else if(MODEL3032E==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "PEL-1033");
		else if(MODEL3070==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "PEL-3070");
		else if(MODEL3111==P3k_Chan_Data.INFO.MACHTYPE)
			sprintf( p3k_Model_Number, "PEL-3111");
		else
			sprintf( p3k_Model_Number, "PEL-Default");
	}

	systemInfo_count=0;

	if(DispScrCurrLoc==0)
		ClrDispCnt(0x00, 0x00, 3, 0x00, 0x00, 0x00);

	/*-------------Show Master firmware------------------*/

	sprintf( systemInfo_item[systemInfo_count],		" Model : ");
	sprintf( systemInfo_Data[systemInfo_count++],	" %s ",p3k_Model_Number);

	sprintf( systemInfo_item[systemInfo_count],  	" Serial Number : ");
	sprintf( systemInfo_Data[systemInfo_count++],	" %s ",P3k_Serial_Number.Product_Serial_Number);


	sprintf( systemInfo_item[systemInfo_count],		" Firmware Ver. : ");
	sprintf( systemInfo_Data[systemInfo_count++],	" %d.%02d.%03d",Main_Version,Sub_Version,Machine_Number);

	sprintf( systemInfo_item[systemInfo_count], 	" \n ");
	sprintf( systemInfo_item[systemInfo_count++],	" \n ");

	if(Serial->Version == TEXIO_Version)
		sprintf( systemInfo_item[systemInfo_count++], 	" http://www.texio.co.jp");
	else
		sprintf( systemInfo_item[systemInfo_count++], 	" http://www.goodwill.com.tw");


	DispScrEndCT=systemInfo_count-1;

	if((DispScrEndCT-DispScrStartCT)>5)
		DispScrEndCT=DispScrStartCT+5;

	for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
		GUI_SetBkColor(Parameter_Bottom_Bolor);

		GUI_GotoXY(Disp_Start_X,40+j*25);
		GUI_DispChars(' ',60);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt( systemInfo_item[i], 10, 40+j*25);
		GUI_SetColor(Noted_Font_Bolor);
		if(i!=DispScrEndCT)

			GUI_DispString( systemInfo_Data[i]);
	}

#if Normal_TEST
	sprintf( systemInfo_item[systemInfo_count++], 	debug_word );
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_GotoXY(Disp_Start_X,40+j*25);
	GUI_DispChars(' ',60);
	GUI_SetColor(Parameter_Font_R_Bolor);
	GUI_DispStringAt( systemInfo_item[i], 45, 40+j*25);
#endif

}

void RedrawSystemMemo(void)
{
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_GotoXY(Disp_Start_X,40);
	GUI_DispChars(' ',60);
	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_DispStringAt( " System Memo ", 10, 40);
}

void RedrawFuncPower(void)
{
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);
	GUI_SetTextAlign(GUI_TA_LEFT);
	GUI_DispStringAt( " Power Analysis ", 105, 30);
	Displine(2,65,316,MEM_GRAY);
	Displine(2,66,316,GW_ORANGE_ku);
	Displine(2,67,316,MEM_WHITE);
}

void RedrawPassword(void)
{
	char str[6];
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_SetTextAlign(GUI_TA_LEFT);
	GUI_DispStringAt(" Please Input Password : ", 46, 90);
	sprintf( str, " %s " , KeyinBuf );
	GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
	GUI_SetColor(Parameter_Select_Font_Bolor);
	ShowSpace_LEFT( 5, 127, 115);
	GUI_SetTextAlign(GUI_TA_LEFT);
	GUI_DispStringAt(str, 130, 115);

	if(Save_Recall_InfoFlag&Data_Process) { /*Show Message*/
		GUI_SetBkColor(Message_Bottom_Bolor);
		GUI_GotoXY(Disp_Start_X, 175);
		GUI_DispChars(' ',51);
		GUI_SetColor(Message_Font_Bolor);
		GUI_SetTextAlign(GUI_TA_LEFT);
		if(Save_Recall_InfoFlag&password_error) {
			Save_Recall_InfoFlag&=~password_error;
			GUI_DispStringAt(" Password Error ", Disp_Start_X, 175);
		} else
			Save_Recall_InfoFlag &= ~Data_Process;
	}
}
extern unsigned char debugmode;
#if 1
void RedrawTestFunction(void)
{
	int i;
	char tmp,tmp1,tmp2,str[20],str1[20];
	unsigned char y_data;
	y_data = Disp_Start_Y2 + Disp_Interval;
	if(debugmode==0) {
		if( DispMode <= DispMode_BROWSE_ITEMS) {

			FPGASetting =FPGA_W[RecordCMD];
			FPGAStatus = FPGA_R[RecordCMD];
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			//GUI_SetColor(MEM_DARKGREEN_ku);
			//GUI_DispStringAt( "FPGA_Register",	Disp_Start_X, Disp_Start_Y2 );
			//GUI_SetColor(MEM_DARKGREEN_ku);
			GUI_SetColor(Parameter_Font_R_Bolor);
			GUI_DispStringAt( "FPGA_Register",	Disp_Start_X, Disp_Start_Y2 );
#if 1
			sprintf( str1, "Ver:%04d",PEL3000_FPGA_Date);
			GUI_DispStringAt( str1,	Disp_Start_X+150, Disp_Start_Y2 );

#endif
			for( i=0 ; i<test_mode_end; i++) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				if(DispMode != DispMode_SELECT_CH && ( i == B_DispCT || i == DispCT ) ) {
					if( i == DispCT)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					GUI_GotoXY(	Disp_Start_X, y_data+ i*Disp_Interval);
					GUI_DispChars(' ', HiLight_Length+20);
				}
				GUI_SetColor(Parameter_Font_L_Bolor);
				if(i>=DispMode_ReadRecord)
					GUI_SetColor(Parameter_Font_U_Bolor);
				if(i==DispMode_SELECT_CH)
					GUI_DispStringAt( "Action",	Disp_Start_X, y_data+i*Disp_Interval );
				else if(i==DispMode_BROWSE_ITEMS)
					GUI_DispStringAt( "CMD",	Disp_Start_X, y_data+i*Disp_Interval );
				else if(i==DispMode_SET_PARAMETERS)
					GUI_DispStringAt( "DATA",	Disp_Start_X, y_data+i*Disp_Interval );
				else if(i==DispMode_ReadRecord)
					GUI_DispStringAt( "RecordCMD",	Disp_Start_X, y_data+i*Disp_Interval );
				else if(i==DispMode_dis_fpga_setting)
					GUI_DispStringAt( "fpgaSetting",	Disp_Start_X, y_data+i*Disp_Interval );
				else if(i==DispMode_dis_fpga_status)
					GUI_DispStringAt( "fpgaStatus",	Disp_Start_X, y_data+i*Disp_Interval );

				GUI_SetColor(Parameter_Font_R_Bolor);
				/* Get Resolution ,Max, Min */
				ShowSpace( 7, Para_Start_X+30, y_data+i*Disp_Interval);
				if(i==DispMode_SELECT_CH) {
					if(P3K_CMD_R_W)	sprintf( str, " Write ");
					else			sprintf( str, " Read ");
				} else if(i==DispMode_BROWSE_ITEMS) {
					sprintf( str, " %03d ",P3K_CMD);
					sprintf( str1, " %02X ",P3K_CMD);
				} else if(i==DispMode_SET_PARAMETERS) {
					sprintf( str, " %05d ",P3K_DATA);
					sprintf( str1, " %04X ",P3K_DATA);
				} else if(i==DispMode_ReadRecord) {
					sprintf( str, " %03d ",RecordCMD);
					sprintf( str1, "%02X ",RecordCMD);
				} else if(i==DispMode_dis_fpga_setting) {
					sprintf( str, " %05d ",FPGASetting);
					sprintf( str1, " %04X ",FPGASetting);
				} else if(i==DispMode_dis_fpga_status) {
					sprintf( str, " %05d ",FPGAStatus);
					sprintf( str1, " %04X ",FPGAStatus);
				}

				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X+30, y_data+i*Disp_Interval);
				if(i!=DispMode_SELECT_CH) {
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_DispStringAt( str1, Para_Start_X+110, y_data+i*Disp_Interval);
				}
			}
		} else if(DispMode == DispMode_SET_PARAMETERS ) {
			GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
			GUI_SetColor(Parameter_Select_Font_Bolor);

			if( KeyInFlag & DIGI_KEY_IN ) {
				sprintf( str, " %s " , KeyinBuf );
			} else {
				/* Show Memory Data on Screen */
				if(DispCT==DispMode_SELECT_CH) {
					if(P3K_CMD_R_W)	sprintf( str, " Write ");
					else			sprintf( str, " Read ");
				} else if(DispCT==DispMode_BROWSE_ITEMS) {
					sprintf( str, " %03d ",P3K_CMD);
					sprintf( str1, " %02X ",P3K_CMD);
				} else if(DispCT==DispMode_SET_PARAMETERS) {
					sprintf( str, " %05d ",P3K_DATA);
					sprintf( str1, " %04X ",P3K_DATA);
				} else if(DispCT==DispMode_ReadRecord) {
					sprintf( str, " %03d ",RecordCMD);
					sprintf( str1, " %02X ",RecordCMD);
				}
			}
			ShowSpace( 7, Para_Start_X+30, y_data+DispCT*Disp_Interval);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X+30, y_data+DispCT*Disp_Interval);
			if(DispCT!=DispMode_SELECT_CH) {
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str1, Para_Start_X+110, y_data+DispCT*Disp_Interval);
			}
			if(DispCT==DispMode_ReadRecord) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				GUI_SetColor(Parameter_Font_R_Bolor);
				sprintf( str, " %05d ",FPGASetting);
				sprintf( str1, " %04X ",FPGASetting);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X+30, y_data+4*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str1, Para_Start_X+110, y_data+4*Disp_Interval);
				sprintf( str, " %05d ",FPGAStatus);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X+30, y_data+5*Disp_Interval);
				sprintf( str, " %04X ",FPGAStatus);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X+110, y_data+5*Disp_Interval);
			}
		}
		// slect Download
	} else {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(MEM_DARKGREEN_ku);
		GUI_DispStringAt( "Download",	Disp_Start_X, Disp_Start_Y2 );
		GUI_SetColor(Parameter_Font_R_Bolor);
		for( i=0 ; i<DownModeEnd; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(DispMode != DispMode_SELECT_CH && ( i == B_DispCT || i == DispCT ) ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(	Disp_Start_X, y_data+ i*Disp_Interval);
				GUI_DispChars(' ', HiLight_Length+20);
			}
			GUI_SetColor(Parameter_Font_L_Bolor);

			if(i==MeasureMode)
				GUI_DispStringAt( "Catch Measure 2k",	Disp_Start_X, y_data+i*Disp_Interval );
			else if(i==CalTxtMode)
				GUI_DispStringAt( "Calibration Value",	Disp_Start_X, y_data+i*Disp_Interval );
			else if(i==printScreen)
				GUI_DispStringAt( "Print Screen",	Disp_Start_X, y_data+i*Disp_Interval );
			else if(i==CalBackup)
				GUI_DispStringAt( "Calibation Backup",	Disp_Start_X, y_data+i*Disp_Interval );
		}
	}
}

#else
void RedrawTestFunction(void)
{
	int i;
	char tmp,tmp1,tmp2,str[20];
	char str1[50];
	sprintf(str1," ");
	if( DispMode <= DispMode_BROWSE_ITEMS) {
		FPGASetting =FPGA_W[RecordCMD];
		FPGAStatus = FPGA_R[RecordCMD];
		for( i=0 ; i<test_mode_end; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(DispMode != DispMode_SELECT_CH&&( i == B_DispCT || i == DispCT )) {
				if(i==DispCT)		GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(	Disp_Start_X, Disp_Start_Y2+ i*Disp_Interval);
				GUI_DispChars(' ', HiLight_Length+10);
			}
			GUI_SetColor(Parameter_Font_L_Bolor);
			if(i>=DispMode_ReadRecord)		GUI_SetColor(Parameter_Font_U_Bolor);
			if(i==DispMode_SELECT_CH)
				GUI_DispStringAt( "Action",	Disp_Start_X, Disp_Start_Y2+i*Disp_Interval );
			else if(i==DispMode_BROWSE_ITEMS)
				GUI_DispStringAt( "CMD",	Disp_Start_X, Disp_Start_Y2+i*Disp_Interval );
			else if(i==DispMode_SET_PARAMETERS)
				GUI_DispStringAt( "DATA",	Disp_Start_X, Disp_Start_Y2+i*Disp_Interval );
			else if(i==DispMode_ReadRecord)
				GUI_DispStringAt( "RecordCMD",	Disp_Start_X, Disp_Start_Y2+i*Disp_Interval );
			else if(i==DispMode_dis_fpga_setting)
				GUI_DispStringAt( "fpgaSetting",	Disp_Start_X, Disp_Start_Y2+i*Disp_Interval );
			else if(i==DispMode_dis_fpga_status)
				GUI_DispStringAt( "fpgaStatus",	Disp_Start_X, Disp_Start_Y2+i*Disp_Interval );
			GUI_SetColor(Parameter_Font_R_Bolor);
			ShowSpace( 7, Para_Start_X+50, Disp_Start_Y2+i*Disp_Interval);
			if(i==DispMode_SELECT_CH) {
				if(P3K_CMD_R_W)	sprintf( str, " Write ");
				else			sprintf( str, " Read ");
			} else if(i==DispMode_BROWSE_ITEMS) {
				sprintf( str, " %03d ",P3K_CMD);
				sprintf( str1, " 0x%02X ",P3K_CMD);
			} else if(i==DispMode_SET_PARAMETERS) {
				sprintf( str, " %05d ",P3K_DATA);
				sprintf( str1, " 0x%04X ",P3K_DATA);
			} else if(i==DispMode_ReadRecord) {
				sprintf( str, " %03d ",RecordCMD);
				sprintf( str1, " 0x%02X ",RecordCMD);
			} else if(i==DispMode_dis_fpga_setting) {
				sprintf( str, " %05d ",FPGASetting);
				sprintf( str1, " 0x%04X ",FPGASetting);
			} else if(i==DispMode_dis_fpga_status) {
				sprintf( str, " %05d ",FPGAStatus);
				sprintf( str1, " 0x%04X ",FPGAStatus);
			}
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X+5, Disp_Start_Y2+i*Disp_Interval);
			GUI_SetColor(MEM_DARKGRAY);
			GUI_DispStringAt( str1, Para_Start_X+30, Disp_Start_Y2+i*Disp_Interval);
		}
	} else if(DispMode == DispMode_SET_PARAMETERS ) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		if(KeyInFlag & DIGI_KEY_IN) {
			sprintf( str, " %s " , KeyinBuf );
		} else {
			if(DispCT==DispMode_SELECT_CH) {
				if(P3K_CMD_R_W)	sprintf( str, " Write ");
				else			sprintf( str, " Read ");
			} else if(DispCT==DispMode_BROWSE_ITEMS) {
				sprintf( str, " %03d ",P3K_CMD);
				sprintf( str1, " 0x%02X ",P3K_CMD);
			} else if(DispCT==DispMode_SET_PARAMETERS) {
				sprintf( str, " %05d ",P3K_DATA);
				sprintf( str1, " 0x%04X ",P3K_DATA);
			} else if(DispCT==DispMode_ReadRecord) {
				sprintf( str, " %03d ",RecordCMD);
				sprintf( str1, " 0x%02X ",RecordCMD);
			}
		}
		ShowSpace( 7, Para_Start_X+5, Disp_Start_Y2+DispCT*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X+5, Disp_Start_Y2+DispCT*Disp_Interval);
		GUI_DispStringAt( str1, Para_Start_X+30, Disp_Start_Y2+DispCT*Disp_Interval);
		if(DispCT==DispMode_ReadRecord) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(Parameter_Font_R_Bolor);
			sprintf( str, " %05d ",FPGASetting);
			sprintf( str1, " 0x%04X ",FPGASetting);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X+5, Disp_Start_Y2+4*Disp_Interval);
			GUI_DispStringAt( str1, Para_Start_X+30, Disp_Start_Y2+4*Disp_Interval);
			sprintf( str, " %05d ",FPGAStatus);
			sprintf( str1, " 0x%04X ",FPGAStatus);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, Para_Start_X+5, Disp_Start_Y2+5*Disp_Interval);
			GUI_DispStringAt( str1, Para_Start_X+30, Disp_Start_Y2+5*Disp_Interval);
		}
	}
}
#endif
void RedrawCalValue(void)
{
#define Disp_Interval1		17
#define Disp_Start_Y2_1		50
	static const char cal_title_1[9][12] = { "OFFSET:","Off_CCH","Off_CCL","Off_CRH","Off_CRL","Off_CPH","Off_CPL","Off_CVH","Off_CVL"};
	static const char cal_title_1_2[5][12] = { "OFFSET:","Off_ExtVH","Off_ExtVL","Off_ExtRH","Off_ExtRL"};
	static const char cal_title_2[9][12] = { "SETTING:","CCH","CCL","CRH","CRL","CVH","CVL","CPH","CPL"};
	static const char cal_title_3[7][12] = { "SETTING:","IMON_H","IMON_L","EXT_VH","EXT_VL","EXT_RH","EXT_RL"};
	static const char cal_title_4[7][12] = { "MEASURE:","M_Volt_H","M_Volt_L","M_Curr_H","M_Curr_L","EXT_SonserV","EXT_SonserR"};
#if Enable_Ext_Measure
	static const char cal_title_5[9][12] = { "MEASURE:","M_VH_ExtV","M_VL_ExtV","M_VH_ExtR","M_VL_ExtR","M_IH_ExtV","M_IL_ExtV","M_IH_ExtR","M_IL_ExtR"};
#endif
	static const char cal_title_6[7][12] = { "PROTECION:","OCP","OCP_Cal_H","OCP_Cal_L","OPP","OPP_Cal_H","OPP_Cal_L"};
	static const char cal_title_7[6][12] = { "PROTECION:","CCP","CCP_Cal_H","CCP_Cal_L","CXCV_CAL_H","CXCV_CAL_L"};
	static const char cal_title_8[7][12] = { "PSENSOR:","XH","YH","ZH","XL","YL","ZL"};

	int i;
	char str[30],str1[30];


	if( DispMode <= DispMode_BROWSE_ITEMS) {

		GUI_SetFont(Right_Font);
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_R_Bolor);
		sprintf( str, "page:%02d",(DispCT+1));
		GUI_DispStringAt( str, 5, 25);
		for( i=0 ; i<9; i++) {
			GUI_GotoXY(	Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1);
			GUI_DispChars(' ', 85);
		}
		switch(DispCT) {
		case 0:
			for( i=0 ; i<9; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_1[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " Value ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.CC_offseAdj[1]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.CC_offseAdj[0]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.CR_offseAdj[1]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.CR_offseAdj[0]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==5) {
					sprintf( str, "%d" , p3k_Cal_data.CP_offseAdj[1]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==6) {
					sprintf( str, "%d" , p3k_Cal_data.CP_offseAdj[0]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==7) {
					sprintf( str, "%d" , p3k_Cal_data.CV_offseAdj[1]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==8) {
					sprintf( str, "%d" , p3k_Cal_data.CV_offseAdj[0]);	//sprintf( str1, " %05d ",FPGASetting);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				//GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
		case 1:
			for( i=0 ; i<5; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_1_2[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " Value ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_offseAdj[1]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_offseAdj[0]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_offseAdj[1]);	//sprintf( str1, " %05d ",FPGASetting);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_offseAdj[0]);	//sprintf( str1, " %05d ",FPGASetting);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				//GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
		case 2:
			for( i=0 ; i<9; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_2[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%f" , p3k_Cal_data.CC_Data[1].Cal_Value_Gain);
					sprintf( str1, "%f" , p3k_Cal_data.CC_Data[1].Cal_Value_Offset);
				} else if(i==2) {
					sprintf( str, "%f" , p3k_Cal_data.CC_Data[0].Cal_Value_Gain);
					sprintf( str1, "%f" , p3k_Cal_data.CC_Data[0].Cal_Value_Offset);
				} else if(i==3) {
					sprintf( str, "%f" , p3k_Cal_data.CR_Data[1].Cal_Value_Gain);
					sprintf( str1, "%f" , p3k_Cal_data.CR_Data[1].Cal_Value_Offset);
				} else if(i==4) {
					sprintf( str, "%f" , p3k_Cal_data.CR_Data[0].Cal_Value_Gain);
					sprintf( str1, "%f" , p3k_Cal_data.CR_Data[0].Cal_Value_Offset);
				} else if(i==5) {
					sprintf( str, "%f" , p3k_Cal_data.CV_Data[1].Cal_Value_Gain);
					sprintf( str1, "%f" , p3k_Cal_data.CV_Data[1].Cal_Value_Offset);
				} else if(i==6) {
					sprintf( str, "%f" , p3k_Cal_data.CV_Data[0].Cal_Value_Gain);
					sprintf( str1, "%f" , p3k_Cal_data.CV_Data[0].Cal_Value_Offset);
				} else if(i==7) {
					sprintf( str, "%f" , p3k_Cal_data.CP_Data[1].Cal_Value_Gain);
					sprintf( str1, "%f" , p3k_Cal_data.CP_Data[1].Cal_Value_Offset);
				} else if(i==8) {
					//p3k_Cal_data.CP_Data[0].Cal_Value_Gain = 1;
					sprintf( str, "%f" , p3k_Cal_data.CP_Data[0].Cal_Value_Gain);
					sprintf( str1, "%f" , p3k_Cal_data.CP_Data[0].Cal_Value_Offset);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
		case 3:
			for( i=0 ; i<7; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_3[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");			//sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Rear_IMON[1]);	//sprintf( str1, "%f" , p3k_Cal_data.CC_Data[1].Cal_Value_Offset);
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.Rear_IMON[0]);	//sprintf( str1, "%f" , p3k_Cal_data.CC_Data[0].Cal_Value_Offset);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_CC[1]);	//sprintf( str1, "%f" , p3k_Cal_data.CR_Data[1].Cal_Value_Offset);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_CC[0]);	//sprintf( str1, "%f" , p3k_Cal_data.CR_Data[0].Cal_Value_Offset);
				} else if(i==5) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_CC[1]);	//sprintf( str1, "%f" , p3k_Cal_data.CV_Data[1].Cal_Value_Offset);
				} else if(i==6) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_CC[0]);	//sprintf( str1, "%f" , p3k_Cal_data.CV_Data[0].Cal_Value_Offset);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				//GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
		case 4: //MEASURE
			for( i=0 ; i<7; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_4[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");
					sprintf( str1, " OFFSET ");	//p3k_Cal_data.Volt[1].Meas_Value_Gain*p3k_Cal_data.Volt[1].Meas_Value_Offset/65535.0)
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Volt[1].Meas_Value_Gain);
					sprintf( str1, "%d" , ((p3k_Cal_data.Volt[1].Meas_Value_Gain*p3k_Cal_data.Volt[1].Meas_Value_Offset)>>16));
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.Volt[0].Meas_Value_Gain);
					sprintf( str1, "%d" , (p3k_Cal_data.Volt[0].Meas_Value_Gain*p3k_Cal_data.Volt[0].Meas_Value_Offset)>>16);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.Curr[1].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Curr[1].Meas_Value_Gain*p3k_Cal_data.Curr[1].Meas_Value_Offset>>16);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.Curr[0].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Curr[0].Meas_Value_Gain*p3k_Cal_data.Curr[0].Meas_Value_Offset>>16);
				} else if(i==5) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_Sense.Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_V_Sense.Meas_Value_Gain*p3k_Cal_data.Ext_V_Sense.Meas_Value_Offset>>16);
				} else if(i==6) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_Sense.Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_R_Sense.Meas_Value_Gain*p3k_Cal_data.Ext_R_Sense.Meas_Value_Offset>>16);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
#if Enable_Ext_Measure
		case 5: //MEASURE
			for( i=0 ; i<9; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_5[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_Volt[1].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_V_Volt[1].Meas_Value_Gain*p3k_Cal_data.Ext_V_Volt[1].Meas_Value_Offset>>16);
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_Volt[0].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_V_Volt[0].Meas_Value_Gain*p3k_Cal_data.Ext_V_Volt[0].Meas_Value_Offset>>16);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_Volt[1].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_R_Volt[1].Meas_Value_Gain*p3k_Cal_data.Ext_R_Volt[1].Meas_Value_Offset>>16);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_Volt[0].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_R_Volt[0].Meas_Value_Gain*p3k_Cal_data.Ext_R_Volt[0].Meas_Value_Offset>>16);
				} else if(i==5) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_Curr[1].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_V_Curr[1].Meas_Value_Gain*p3k_Cal_data.Ext_V_Curr[1].Meas_Value_Offset>>16);
				} else if(i==6) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_V_Curr[0].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_V_Curr[0].Meas_Value_Gain*p3k_Cal_data.Ext_V_Curr[0].Meas_Value_Offset>>16);
				} else if(i==7) {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_Curr[1].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_R_Curr[1].Meas_Value_Gain*p3k_Cal_data.Ext_R_Curr[1].Meas_Value_Offset>>16);
				} else {
					sprintf( str, "%d" , p3k_Cal_data.Ext_R_Curr[0].Meas_Value_Gain);
					sprintf( str1, "%d" , p3k_Cal_data.Ext_R_Curr[0].Meas_Value_Gain*p3k_Cal_data.Ext_R_Curr[0].Meas_Value_Offset>>16);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
#endif
		case 6: //PROCTION_1
			for( i=0 ; i<7; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_6[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Protection[1].OCP);
					sprintf( str1, " " );
				} else if(i==2) {
					sprintf( str, "%f" , p3k_Cal_data.Protection[1].OCP_Gain);
					sprintf( str1, "%f" , p3k_Cal_data.Protection[1].OCP_Offset);
				} else if(i==3) {
					sprintf( str, "%f" , p3k_Cal_data.Protection[0].OCP_Gain);
					sprintf( str1, "%f" , p3k_Cal_data.Protection[0].OCP_Offset);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.Protection[1].OPP);
					sprintf( str1, "  " );
				} else if(i==5) {
					sprintf( str, "%f" , p3k_Cal_data.Protection[1].OPP_Gain);
					sprintf( str1, "%f" , p3k_Cal_data.Protection[1].OPP_Offset);
				} else if(i==6) {
					sprintf( str, "%f" , p3k_Cal_data.Protection[0].OPP_Gain);
					sprintf( str1, "%f" , p3k_Cal_data.Protection[0].OPP_Offset);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
		case 7: //PROCTION_2
			for( i=0 ; i<6; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_7[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.Protection[1].CPP);
					sprintf( str1, "  ");
				} else if(i==2) {
					sprintf( str, "%f" , p3k_Cal_data.Protection[1].CPP_Gain);
					sprintf( str1, "%f" , p3k_Cal_data.Protection[1].CPP_Offset);
				} else if(i==3) {
					sprintf( str, "%f" , p3k_Cal_data.Protection[0].CPP_Gain);
					sprintf( str1, "%f" , p3k_Cal_data.Protection[0].CPP_Offset);
				} else if(i==4) {
					sprintf( str, "%f" , p3k_Cal_data.Protection[1].CxCV_Gain);
					sprintf( str1, "%f" , p3k_Cal_data.Protection[1].CxCV_Offset);
				} else if(i==5) {
					sprintf( str, "%f" , p3k_Cal_data.Protection[0].CxCV_Gain);
					sprintf( str1, "%f" , p3k_Cal_data.Protection[0].CxCV_Offset);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
		case 8: //PSENSOR
			for( i=0 ; i<7; i++) {
				if(i==0)GUI_SetColor(Parameter_Select_Font_Bolor);
				else	GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( cal_title_8[i], Disp_Start_X, Disp_Start_Y2_1+i*Disp_Interval1 );
				GUI_SetColor(Noted_Font_Bolor);
				if(i==0) {
					sprintf( str, " GAIN ");
					sprintf( str1, " OFFSET ");
					GUI_SetColor(Parameter_Select_Font_Bolor);
				} else if(i==1) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.XH_Value);
				} else if(i==2) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.YH_Value);
				} else if(i==3) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.ZH_Value);
				} else if(i==4) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.XL_Value);
				} else if(i==5) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.YL_Value);
				} else if(i==6) {
					sprintf( str, "%d" , p3k_Cal_data.PSensor.ZL_Value);
				}
				GUI_DispStringAt( str, 100, Disp_Start_Y2_1+i*Disp_Interval1);
				//GUI_DispStringAt( str1, 180, Disp_Start_Y2_1+i*Disp_Interval1);
			}
			break;
		default:
			break;
		}
	}
}


#if Enable_AutoLoad
void RedrawAutoLoad(void)
{
	int i;

	if(DispMode==DispMode_SELECT_CH) {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_U_Bolor);
		GUI_DispStringAt( " Load Setting For Power On", 40, 45);
		for( i=0 ; i<= 4 ; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(45, 70+i*25);
				GUI_DispChars(' ',45);
			}
			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt(AutoLoad_title[i], 50, 70+i*25);

			ShowSpace(AutoLoad_space[i], 260, 70+i*25);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_SetColor(Parameter_Font_R_Bolor);
			if(i==0)	 GUI_DispStringAt(onoff_str[UTILITY.ALOAD], 260, 70+i*25);
			else if(i==1)GUI_DispStringAt(AutoLoad_mode[UTILITY.ALOAD_MODE], 260, 70+i*25);
			else if(i==2)GUI_DispStringAt(onoff_str[UTILITY.AutoLoadOffMode], 260, 70+i*25);
			else if(i==3)GUI_DispStringAt(onoff_str[UTILITY.AutoLoadOffRange], 260, 70+i*25);
			else		GUI_DispStringAt(onoff_str[UTILITY.ShortonLoadoff], 260, 70+i*25);
		}
	} else {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		ShowSpace(AutoLoad_space[DispCT], 250, 70+DispCT*25);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		if(DispCT==0)
			GUI_DispStringAt(onoff_str[UTILITY.ALOAD], 260, 70+DispCT*25);
		else if(DispCT==1)
			GUI_DispStringAt(AutoLoad_mode[UTILITY.ALOAD_MODE], 260, 70+DispCT*25);
		else if(DispCT==2)
			GUI_DispStringAt(onoff_str[UTILITY.AutoLoadOffMode], 260, 70+DispCT*25);
		else if(DispCT==3)
			GUI_DispStringAt(onoff_str[UTILITY.AutoLoadOffRange], 260, 70+DispCT*25);
		else
			GUI_DispStringAt(onoff_str[UTILITY.ShortonLoadoff], 260, 70+DispCT*25);
	}
}
#else
void RedrawAutoLoad(void)
{
	int i;

	if(DispMode==DispMode_SELECT_CH) {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_U_Bolor);
		GUI_DispStringAt( " Load Setting For Power On", 40, 45);
		for( i=0 ; i<= 1 ; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(45, 70+i*25);
				GUI_DispChars(' ',45);
			}
			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt(AutoLoad_title[i], 50, 70+i*25);

			ShowSpace(AutoLoad_space[i], 260, 70+i*25);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_SetColor(Parameter_Font_R_Bolor);
			if(i==0)	GUI_DispStringAt(onoff_str[UTILITY.ALOAD], 260, 70+i*25);
			else		GUI_DispStringAt(AutoLoad_mode[UTILITY.ALOAD_MODE], 260, 70+i*25);
		}
	} else {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		ShowSpace(AutoLoad_space[DispCT], 250, 70+DispCT*25);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		if(DispCT==0)
			GUI_DispStringAt(onoff_str[UTILITY.ALOAD], 260, 70+DispCT*25);
		else
			GUI_DispStringAt(AutoLoad_mode[UTILITY.ALOAD_MODE], 260, 70+DispCT*25);
	}
}
#endif

void RedrawProgExecute(void)
{
	char str[9];
	UWORD dat,dat1,SPEC_Result_Temp;
	UWORD Display_Count_Temp;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	RedrawMeasure();
	DMA_Update_Flag = 1;

	GUI_SetFont(Parameter_Font);
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);
	Display_Count_Temp = Prog_Seq_Data.Display_Count/3;

	if(Prog_Seq_Data.Total_Count)
		GUI_DispStringAt(" Run Program ", 5, 110);
	else {
		GUI_DispStringAt(" No Program ", 5, 110);
		return;
	}

	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_DispStringAt( " Program No. :", 30, 140);
	dat = Prog_Seq_Data.Prog_Disp_Data[Display_Count_Temp].Prog_No+1;
	sprintf( str, "%02d", dat);
	GUI_SetColor(Parameter_Font_R_Bolor);
	GUI_DispStringAt( str, 190, 140 );

	Displine(0,107,320,MEM_GRAY);
	Displine(0,108,320,GW_ORANGE_ku);
	Displine(0,109,320,MEM_WHITE);

	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_DispStringAt( " Step(Memory) : ", 30, 170);
	dat = Prog_Seq_Data.Prog_Disp_Data[Display_Count_Temp].Mem_NO+1;
	dat1= Prog_Seq_Data.Prog_Disp_Data[Display_Count_Temp].Step_No+1;
	sprintf( str, "%02d(%03d)", dat1,dat);
	GUI_SetColor(Parameter_Font_R_Bolor);
	GUI_DispStringAt( str, 190, 170);

	SPEC_Result_Temp = Prog_Seq_Data.Prog_Disp_Data[Display_Count_Temp].SPEC_Result_Backup;

	if(1 == SPEC_Result_Temp)
		GUI_SetColor(NG_Font_Bolor);
	else
		GUI_SetColor(GO_Font_Bolor);
	GUI_DispStringAt(okng[SPEC_Result_Temp], 270, 170);
}

void RedrawNSeqExecute(void)
{
	char str[20];
	long dat;
	long dat_loop;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	RedrawMeasure();
	DMA_Update_Flag = 1;

	GUI_SetFont(Parameter_Font);
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);

	if(Prog_Seq_Data.Total_Count)

		GUI_DispStringAt(" Run N.Seq. ", 5, 110);
	else {
		GUI_DispStringAt(" No N.Seq. ", 5, 110);
		return;
	}

	Displine(0,107,320,MEM_GRAY);
	Displine(0,108,320,GW_ORANGE_ku);
	Displine(0,109,320,MEM_WHITE);

	/* Show Program Number 1~12 */
	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_DispStringAt( " Seq. No. :", 130, 115);
	GUI_DispStringAt( " Step : ",   130, 145);
	GUI_DispStringAt( " Loop : ",   130, 175);

	GUI_SetColor(Parameter_Font_R_Bolor);
	dat = Prog_Seq_Data.Prog_Disp_Data[Prog_Seq_Data.Display_Count].Prog_No+1;
	dat_loop = dat -1;
	sprintf( str, "%02d", dat);
	GUI_DispStringAt( str, 240, 115 );

	dat = Prog_Seq_Data.Prog_Disp_Data[Prog_Seq_Data.Display_Count].Step_No+1;
	sprintf( str, "%04d", dat);
	GUI_DispStringAt( str, 240, 145);

	dat = Prog_Seq_Data.FPGA_Loop_Count[Prog_Seq_Data.Prog_Disp_Data[Prog_Seq_Data.Display_Count].Loop_Address]+1;

	if (P3k_NSeq_Disp.NSeq_Seq[dat_loop].NSeq_Loop)
		sprintf( str, "%04d", dat);
	else
		sprintf( str, " Infinity ");

	GUI_DispStringAt( str, 240, 175);
}

void RedrawFSeqExecute(void)
{
	char str[20];
	long dat;

	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;

	RedrawMeasure();
	DMA_Update_Flag = 1;

	GUI_SetFont(Parameter_Font);
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);

	if(P3k_FSeq_Disp.FSeq_Max_Step<0xFF00)
		GUI_DispStringAt(" Run F.Seq. ", 5, 110);
	else {
		GUI_DispStringAt(" No F.Seq. ", 5, 110);
		return;
	}

	Displine(0,107,320,MEM_GRAY);
	Displine(0,108,320,GW_ORANGE_ku);
	Displine(0,109,320,MEM_WHITE);

	/* Show Program Number 1~12 */
	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_DispStringAt( " Step : ",   130, 130);
	GUI_DispStringAt( " Loop : ",   130, 160);

	GUI_SetColor(Parameter_Font_R_Bolor);
	dat = Prog_Seq_Data.Display_Count+1;
	sprintf( str, "%04d", dat);
	GUI_DispStringAt( str, 240, 130);

	dat = Prog_Seq_Data.FPGA_Loop_Count[0]+1;
	if (P3k_FSeq_Disp.FSeq_Loop)
		sprintf( str, "%04d", dat);
	else
		sprintf( str, " Infinity ");

	GUI_DispStringAt( str, 240, 160);
}

void RedrawProgDetail(void)
{
	char i=0,j=0,k,l,m;
	char str[4];
	UBYTE Prog_Setting,Step_Setting;
	UWORD Display_Count_Temp,SPEC_Result_Temp;

	P3k_Prog_Disp_Str	*Prog_Disp_Ptr;

	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);

	if(!Prog_Seq_Data.Total_Count) {
		GUI_DispStringAt( "No Program ", 5, 40);
		return;
	} else
		GUI_DispStringAt(" Run Program Detail Result", 30, 30);

	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_DispStringAt( "Program",10, 65);
	GUI_DispStringAt( "Step", 	100, 65);
	GUI_DispStringAt( "Result", 180, 65);

	Displine(10,64,290,MEM_GRAY);
	Displine(10,65,290,GW_ORANGE_ku);
	Displine(10,66,290,MEM_WHITE);

	for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		if((DispScrCurrLoc == DispScrEndCT) || (DispScrCurrLoc == DispScrStartCT)) {
			if(Prog_Seq_Data.Total_Count > 4) {
				ShowScrollBar_Other(305,70,Prog_Seq_Data.Total_Count,4,30,10,DispScrStartCT);
				GUI_SetBkColor(Parameter_Bottom_Bolor);
			}
			if( i == DispScrCurrLoc)
				GUI_SetBkColor(Parameter_Select_Bar_Bolor);
			GUI_GotoXY(Disp_Start_X,ProgDetail_Item_Y_Addr[j]);
			GUI_DispChars(' ',50);
		} else {
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != DispScrCurrLoc && i != B_DispCT ) )
				continue;
			if( i == DispScrCurrLoc || i == B_DispCT ) {
				if( i==DispScrCurrLoc)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(Disp_Start_X,ProgDetail_Item_Y_Addr[j]);
				GUI_DispChars(' ',50);
			}
		}

		Prog_Disp_Ptr = &Prog_Seq_Data.Prog_Disp_Data[i];
		GUI_SetColor(Parameter_Font_L_Bolor);
		sprintf( str, "%d", Prog_Disp_Ptr->Prog_No+1);
		GUI_DispStringAt( str, 40, ProgDetail_Item_Y_Addr[j]);
		sprintf( str, "%d", Prog_Disp_Ptr->Step_No+1);
		GUI_DispStringAt( str, 115,ProgDetail_Item_Y_Addr[j]);

		SPEC_Result_Temp = Prog_Seq_Data.Prog_Disp_Data[i].SPEC_Result;
		sprintf( str, ViewNext_G_N[SPEC_Result_Temp]);

		if(SPEC_Result_Temp == 1)
			GUI_SetColor(NG_Font_Bolor);
		else
			GUI_SetColor(GO_Font_Bolor);
		GUI_DispStringAt(str, 195, ProgDetail_Item_Y_Addr[j]);
	}
}

void RedrawLuaExecute(void)
{
	UBYTE err;
	char str[8],i;
	char str_temp[5][8] = { "a", "ab" ,"abc" ,"abcd" ,"abcde"};
	int item_x_addr[5] = {	32, 96, 160, 224, 288};		/* Item string X location */
	if(OSSemAccept(LuaDispEventSemPtr)) {
		OSSemPost(LuaDispReadySemPtr);
		OSSemPend(LuaDispDoneSemPtr, 0, &err);
	}
#if 0
	if(Script[0].functionname[0]!=0) {
		GUI_SetFont(&GUI_FontArial15);
		GUI_SetBkColor(GW_GRAY);
		GUI_SetColor(GW_BLACK);
		strncpy(str,(const char *)&Script[0].functionname,8);
		GUI_DispStringAt(str, 0, 205);
	}
#endif
#if 0
	GUI_SetFont(&GUI_FontArial15);
	GUI_SetBkColor(GW_GRAY);
	GUI_SetColor(GW_BLACK);
#endif
#if 0
	GUI_SetTextAlign(GUI_TA_RIGHT);
//	GUI_SetTextAlign(GUI_TA_LEFT);
//	GUI_SetTextAlign(GUI_TA_CENTER);
	GUI_DispStringAt("a", 32, 216);
	GUI_DispStringAt("ab", 96, 216);
	GUI_DispStringAt("abc", 160, 216);
	GUI_DispStringAt("abcd", 224, 216);
	GUI_DispStringAt("abcde", 288, 216);
#endif
#if 0
	for(i=0; i<5; i++) {
		GUI_SetTextAlign(GUI_TA_CENTER);
		GUI_DispStringAt(str_temp[i], item_x_addr[i], 216);
	}
#endif
}

void RedrawFuncMain(void)
{
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);
	GUI_SetTextAlign(GUI_TA_LEFT);
	GUI_DispStringAt( " FUNCTION ", 105, 30);
	Displine(2,65,316,MEM_GRAY);
	Displine(2,66,316,GW_ORANGE_ku);
	Displine(2,67,316,MEM_WHITE);
}

void RedrawSeqFunction(void)
{
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	GUI_SetColor(Parameter_Font_U_Bolor);
	GUI_SetTextAlign(GUI_TA_LEFT);
	GUI_DispStringAt( " Sequence Function ", 75, 30);
	Displine(2,65,316,MEM_GRAY);
	Displine(2,66,316,GW_ORANGE_ku);
	Displine(2,67,316,MEM_WHITE);
}

static const char NSeq_item_Data[P_NSeq_Max][20]	= { "Start:", "Seq. No:", "Memo:", "Mode:", "Range:", "Loop:", "Last Load:", "Last:", "Chain:" };
static const int NSeq_item_X_Addr[P_NSeq_Max]		= { 55,       160,        10,      10,      10,       10,      160,          160,         160      };
static const int NSeq_item_Y_Addr[P_NSeq_Max]		= { 45,       45,         90,      115,     140,      165,     115,          140,         165      };
static const int NSeq_Value_X_Addr[P_NSeq_Max]		= { 145,      280,        80,      145,     145,      145,     305,          284,         305      };
static const char NSeq_space[P_NSeq_Max]			= { 2,        2,          4,       4,       5,        6,       4,            7,           4        };
static const int NSeq_light_space[P_NSeq_Max]		= { 22,       20,         29,      29,      29,       29,      29,           29,          29       };
static const char NSeq_Mode_Item[4][20]				= { " CC ", " CR ", " CV ", " CP " };
static const char NSeq_Mode_Unit[4][20]				= { " A   ", "mS ", " V   ", " W  " };
static const char NSeq_Range_Item[4][20]			= { " ILVL ", " IHVL ", " ILVH ", " IHVH " };
void RedrawSeqNormal(void)
{
	int i;
	char str[50];
	long dat;
	double fdat;
	static unsigned char flag_loopInfinity;
	static unsigned char flag_ChainNone;
	unsigned char chain_num;
	if(DispMode_SELECT_CH==DispMode) {
		if(DataRedrawFlag&BG_CLEAR_FLAG) {
			Displine(2,79,316,MEM_GRAY);
			Displine(2,80,316,GW_ORANGE_ku);
			Displine(2,81,316,MEM_WHITE);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_DispStringAt( " Timing Edit for Normal Sequence ", 15, 20);
		}
		for( i=0 ; i<P_NSeq_Max ; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				continue;
			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(NSeq_item_X_Addr[i]-5,NSeq_item_Y_Addr[i]);
				GUI_DispChars(' ',NSeq_light_space[i]);
			}
			if(i<2) 	GUI_SetColor(Parameter_Font_U_Bolor);
			else if((flag_loopInfinity)&&(i>=P_NSeq_Last_Load))GUI_SetColor(MEM_DARKGRAY);
			else if((flag_ChainNone==0)&&((i==P_NSeq_Last_Load)||(i==P_NSeq_Last_Set)))GUI_SetColor(MEM_DARKGRAY);
			else		GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( NSeq_item_Data[i], NSeq_item_X_Addr[i], NSeq_item_Y_Addr[i]);
			dat = GetChanData( i , 0);
			if( i==P_NSeq_Start||i==P_NSeq_No ) sprintf( str, " S%02d ", dat+1);
			else if( i==P_NSeq_Memo) {
				if(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Memo[0]==0)
					sprintf( str, " No Memo ");
				else
					sprintf( str, " %s ",P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Memo);
			} else if( i==P_NSeq_Mode)			strcpy(  str, NSeq_Mode_Item[dat]);
			else if( i==P_NSeq_Range)		strcpy(  str, NSeq_Range_Item[dat]);
			else if( i==P_NSeq_Loop) {
				if(dat) {
					sprintf( str, " %04d ", dat);
					flag_loopInfinity =0;
				} else {
					sprintf( str, " Infinity ");
					flag_loopInfinity =1;
				}
				chain_num =GetChanData( P_NSeq_Chain , 0);
				if(chain_num) {
					if(P3k_NSeq_Data.NSeq_Seq[chain_num-1].NSeq_Max_Step)flag_ChainNone = 0;
					else flag_ChainNone = 1;
				} else {
					flag_ChainNone = 1;
				}
			} else if(i==P_NSeq_Last_Load)
				strcpy( str, onoff_str[dat]);
			else if(i==P_NSeq_Last_Set) {
				GUI_SetColor(Parameter_Font_R_Bolor);
				if((flag_loopInfinity)&&(i>=P_NSeq_Last_Load))GUI_SetColor(MEM_DARKGRAY);
				else if((flag_ChainNone==0)&&((i==P_NSeq_Last_Load)||(i==P_NSeq_Last_Set)))GUI_SetColor(MEM_DARKGRAY);
				GUI_DispStringAt( NSeq_Mode_Unit[GetChanData( 3 , 0)], NSeq_Value_X_Addr[i], 140);
				fdat = StepToReal(dat,0);
				Display_Parameter_Pro(fdat,str,Search_precision(0));
			} else { /*P_NSeq_Chain*/
				if(dat) {
					sprintf(str, " S%02d ", dat);
				} else {
					sprintf(str, " Off ");
				}
			}
			GUI_SetColor(Parameter_Font_R_Bolor);
			if((flag_loopInfinity)&&(i>=P_NSeq_Last_Load))GUI_SetColor(MEM_DARKGRAY);
			else if((flag_ChainNone==0)&&((i==P_NSeq_Last_Load)||(i==P_NSeq_Last_Set)))GUI_SetColor(MEM_DARKGRAY);
			if( i==P_NSeq_Memo) {
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_GotoXY(NSeq_Value_X_Addr[i], NSeq_item_Y_Addr[i]);
				GUI_DispChars(' ',46);
				GUI_SetTextAlign(GUI_TA_LEFT);
			} else {
				ShowSpace(NSeq_space[i], NSeq_Value_X_Addr[i], NSeq_item_Y_Addr[i]);
				GUI_SetTextAlign(GUI_TA_RIGHT);
			}
			GUI_DispStringAt( str, NSeq_Value_X_Addr[i], NSeq_item_Y_Addr[i]);
		}
	} else if(DispMode_BROWSE_ITEMS==DispMode) {
		if(P_NSeq_No==DispCT) {
			for( i=0 ; i<P_NSeq_Max ; i++) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				if( i == DispCT)
					continue;
				if(i<2) 	GUI_SetColor(Parameter_Font_U_Bolor);
				else		GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( NSeq_item_Data[i], NSeq_item_X_Addr[i], NSeq_item_Y_Addr[i]);
				dat = GetChanData( i , 0);
				if( i==P_NSeq_Start||i==P_NSeq_No ) sprintf( str, " S%02d ", dat+1);
				else if( i==P_NSeq_Memo) {
					if(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Memo[0]==0)
						sprintf( str, " No Memo ");
					else
						sprintf( str, " %s ",P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Memo);
				} else if( i==P_NSeq_Mode)			strcpy(  str, NSeq_Mode_Item[dat]);
				else if( i==P_NSeq_Range)			strcpy(  str, NSeq_Range_Item[dat]);
				else if( i==P_NSeq_Loop) {
					if(dat)	sprintf( str, " %04d ", dat);
					else	sprintf( str, " Infinity ");
				} else if(i==P_NSeq_Last_Load)		strcpy( str, onoff_str[dat]);
				else if(i==P_NSeq_Last_Set) {
					GUI_SetColor(Parameter_Font_R_Bolor);
					GUI_DispStringAt( NSeq_Mode_Unit[GetChanData( 3 , 0)], NSeq_Value_X_Addr[i], 140);
					fdat = StepToReal(dat,0);
					Display_Parameter_Pro(fdat,str,Search_precision(0));
				} else {
					if(dat)	sprintf(str, " S%02d ", dat);
					else	sprintf(str, " Off ");
				}
				GUI_SetColor(Parameter_Font_R_Bolor);
				if( i==P_NSeq_Memo) {
					GUI_SetTextAlign(GUI_TA_RIGHT);
					GUI_GotoXY(NSeq_Value_X_Addr[i], NSeq_item_Y_Addr[i]);
					GUI_DispChars(' ',46);
					GUI_SetTextAlign(GUI_TA_LEFT);
				} else {
					ShowSpace(NSeq_space[i], NSeq_Value_X_Addr[i], NSeq_item_Y_Addr[i]);
					GUI_SetTextAlign(GUI_TA_RIGHT);
				}
				GUI_DispStringAt( str, NSeq_Value_X_Addr[i], NSeq_item_Y_Addr[i]);
			}
		}
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN)
			sprintf(str, "%s", KeyinBuf);
		else {
			dat = GetChanData(DispCT,0);
			if( DispCT==P_NSeq_Start||DispCT==P_NSeq_No ) sprintf( str, " S%02d ", dat+1);
			else if( DispCT==P_NSeq_Memo) {
				if(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Memo[0]==0)
					sprintf( str, " No Memo ");
				else
					sprintf( str, " %s ",P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Memo);
			} else if( DispCT==P_NSeq_Mode)					strcpy(  str, NSeq_Mode_Item[dat]);
			else if( DispCT==P_NSeq_Range)				strcpy(  str, NSeq_Range_Item[dat]);
			else if( DispCT==P_NSeq_Loop) {
				if(dat) sprintf( str, " %04d ", dat);
				else	sprintf( str, " Infinity ");
			} else if(DispCT==P_NSeq_Last_Load)		strcpy( str, onoff_str[dat]);
			else if(DispCT==P_NSeq_Last_Set) {
				fdat = StepToReal(dat,0);
				Display_Parameter_Pro(fdat,str,Search_precision(0));
			} else {
				if(dat) sprintf(str, " S%02d ", dat);
				else	sprintf(str, " Off ");
			}
		}
		if( DispCT==P_NSeq_Memo) {
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_GotoXY(NSeq_Value_X_Addr[DispCT], NSeq_item_Y_Addr[DispCT]);
			GUI_DispChars(' ',46);
			GUI_SetTextAlign(GUI_TA_LEFT);
		} else {
			ShowSpace(NSeq_space[DispCT], NSeq_Value_X_Addr[DispCT], NSeq_item_Y_Addr[DispCT]);
			GUI_SetTextAlign(GUI_TA_RIGHT);
		}
		GUI_DispStringAt( str, NSeq_Value_X_Addr[DispCT], NSeq_item_Y_Addr[DispCT]);
	}
}



static const char FSeqFill_item_Data[P_Fill_Max][20]	= { "Start_Value:", "End_Value:", "Start_Step:", "End_Step:"	};
static const char FSeq_Mode_Unit[2][20]             = { " A   ", "mS "};
void RedrawFSeqFill(void)
{
	UBYTE i;
	long dat;
	double fdat;
	char str[50];
	if(DispMode_SELECT_CH==DispMode) {
		if(DataRedrawFlag&BG_CLEAR_FLAG) {
			Displine(2,65,316,MEM_GRAY);
			Displine(2,66,316,GW_ORANGE_ku);
			Displine(2,67,316,MEM_WHITE);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_DispStringAt( " Fill Edit for Fast Sequence ", 45, 30);
		}

		for(i=0 ; i<P_Fill_Max ; i++) {
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&(DispMode == DispMode_BROWSE_ITEMS) && ( i != B_DispCT && i != DispCT ) )
				continue;
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY( Disp_Start_X, Disp_Start_Y0+ i*Disp_Interval);
				GUI_DispChars(' ', HiLight_Length);
			}
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_SetColor(Parameter_Font_L_Bolor);

			GUI_DispStringAt( FSeqFill_item_Data[i], Disp_Start_X, Disp_Start_Y0+i*Disp_Interval);
			ShowSpace( 7, Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
			dat = GetChanData(i,0);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_SetColor(Parameter_Font_R_Bolor);

			if( (i==P_Fill_Value_S)||(i==P_Fill_Value_E) ) {
				fdat = StepToReal(dat,0);
				Display_Parameter_Pro(fdat,str,Search_precision(0));
			} else
				sprintf( str, " %04d ", dat+1);
			GUI_DispStringAt(str,Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
			if (i <= 1)GUI_DispStringAt( FSeq_Mode_Unit[P3k_FSeq_Disp.FSeq_Mode] ,Para_Start_X, Disp_Start_Y0 + i*Disp_Interval);
		}
	} else if(DispMode_BROWSE_ITEMS==DispMode) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN)
			sprintf(str, "%s", KeyinBuf);
		else {
			dat = GetChanData(DispCT,0);
			if( (DispCT==P_Fill_Value_S)||(DispCT==P_Fill_Value_E) ) {
				fdat = StepToReal(dat,0);
				Display_Parameter_Pro(fdat,str,Search_precision(0));
			} else
				sprintf( str, " %04d ", dat+1);
		}
		ShowSpace( 7, Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt(str,Para_Start_X, Disp_Start_Y0 + DispCT*Disp_Interval);
	}
}

static const char FSeqEdit_item_Data[P_FSeqEdit_Max][20]	= { "Step:", "Value:", "TRIG OUT:"	};
static const int  FSeqEdit_item_X_Addr[P_FSeqEdit_Max]		= { 90,      10,       10			};
static const int  FSeqEdit_item_Y_Addr[P_FSeqEdit_Max]		= { 45,      90,       115			};
static const int  FSeqEdit_Value_X_Addr[P_FSeqEdit_Max]		= { 190,     150,      160			};
static const char FSeqEdit_space[P_FSeqEdit_Max]			= { 4,       7,        4			};
static const int  FSeqEdit_light_space[P_FSeqEdit_Max]		= { 22,      20,       25			};

void RedrawFSeqEdit(void)
{
	UBYTE i;
	long dat;
	double fdat;
	char str[50];

	unsigned char DARKGRAY_flag;
	if(P3k_FSeq_Disp.FSeq_Max_Step>0xFF00)
		DARKGRAY_flag=1;
	else
		DARKGRAY_flag=0;
	if(DispMode_SELECT_CH==DispMode) {
		if(DataRedrawFlag&BG_CLEAR_FLAG) {
			Displine(2,79,316,MEM_GRAY);
			Displine(2,80,316,GW_ORANGE_ku);
			Displine(2,81,316,MEM_WHITE);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_DispStringAt( " Data Edit for Fast Sequence ", 45, 20);
		}
		for( i=0 ; i<P_FSeqEdit_Max ; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				continue;
			if(( i==B_DispCT||i==DispCT )&&(DARKGRAY_flag==0))

			{
				if( i==DispCT ) {
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				}
				GUI_GotoXY(FSeqEdit_item_X_Addr[i]-5,FSeqEdit_item_Y_Addr[i]);
				GUI_DispChars(' ',FSeqEdit_light_space[i]);
			}

			if(i<1)
				GUI_SetColor(Parameter_Font_U_Bolor);
			else
				GUI_SetColor(Parameter_Font_L_Bolor);

			if (DARKGRAY_flag)GUI_SetColor(MEM_DARKGRAY);


			GUI_DispStringAt( FSeqEdit_item_Data[i], FSeqEdit_item_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
			dat  = GetChanData(i,0);

			if((i==P_FSeqEdit_Step)&&(DARKGRAY_flag)) {
				dat =-1;
			}

			if(i==P_FSeqEdit_Step)
				sprintf( str, " %04d ", dat+1);
			else if( i==P_FSeqEdit_Value) {

				GUI_SetColor(Parameter_Font_R_Bolor);

				if (DARKGRAY_flag)GUI_SetColor(MEM_DARKGRAY);

				GUI_DispStringAt( FSeq_Mode_Unit[P3k_FSeq_Disp.FSeq_Mode],FSeqEdit_Value_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
				fdat = StepToReal(dat,0);
				Display_Parameter_Pro(fdat,str,Search_precision(0));
			} else
				strcpy(  str, onoff_str[dat]);
			GUI_SetColor(Parameter_Font_R_Bolor);

			if (DARKGRAY_flag)GUI_SetColor(MEM_DARKGRAY);

			ShowSpace(FSeqEdit_space[i], FSeqEdit_Value_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, FSeqEdit_Value_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
			if( P_FSeqEdit_Step==i) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				if (DARKGRAY_flag)
					sprintf( str, " /   %04d ",0);
				else

					sprintf( str, " /   %04d ", GetChanData( P_FSeqEdit_Max , 0)+1);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, FSeqEdit_Value_X_Addr[i]+80, FSeqEdit_item_Y_Addr[i]);
			}
		}
	} else if(DispMode_BROWSE_ITEMS==DispMode) {

		if(DARKGRAY_flag)return;
		if(P_FSeqEdit_Step==DispCT) {
			for( i=P_FSeqEdit_Step+1 ; i<P_FSeqEdit_Max ; i++) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( FSeqEdit_item_Data[i], FSeqEdit_item_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
				dat = GetChanData(i,0);
				if( i==P_FSeqEdit_Value) {
					fdat = StepToReal(dat,0);
					Display_Parameter_Pro(fdat,str,Search_precision(0));
				} else
					strcpy(  str, onoff_str[dat]);
				GUI_SetColor(Parameter_Font_R_Bolor);
				ShowSpace(FSeqEdit_space[i], FSeqEdit_Value_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, FSeqEdit_Value_X_Addr[i], FSeqEdit_item_Y_Addr[i]);
			}
		}
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN)
			sprintf(str, "%s", KeyinBuf);
		else {
			dat = GetChanData(DispCT,0);
			if(DispCT==P_FSeqEdit_Step)
				sprintf( str, " %04d ", dat+1);
			else if( DispCT==P_FSeqEdit_Value) {
				fdat = StepToReal(dat,0);
				Display_Parameter_Pro(fdat,str,Search_precision(0));
			} else
				strcpy(  str, onoff_str[dat]);
		}
		ShowSpace(FSeqEdit_space[DispCT], FSeqEdit_Value_X_Addr[DispCT], FSeqEdit_item_Y_Addr[DispCT]);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, FSeqEdit_Value_X_Addr[DispCT], FSeqEdit_item_Y_Addr[DispCT]);
	}
}

static const char NSeqEdit_item_Data[P_NSeqEdit_Max][20]	= { "Step:", "Value:", "Time:", "Time:", "Time:", "Time:", "LOAD:", "RAMP:", "TRIG OUT:", "PAUSE:" };
static const int NSeqEdit_item_X_Addr[P_NSeqEdit_Max]		= { 90,      10,       10,      10,      10,      10,      10,      10,      160,     160      };
static const int NSeqEdit_item_Y_Addr[P_NSeqEdit_Max]		= { 45,      90,       115,     115,     115,     115,     140,     165,     140,     165      };
static const int NSeqEdit_Value_X_Addr[P_NSeqEdit_Max]		= { 190,     150,      110,     165,     220,     280,     145,     145,     311,     311      };
static const char NSeqEdit_space[P_NSeqEdit_Max]			= { 4,       7,        3,       2,       2,       3,       4,       4,       4,       4        };
static const int NSeqEdit_light_space[P_NSeqEdit_Max]		= { 22,      20,       10,      10,      10,      10,      29,      29,      29,      29       };
static const char NSeqEdit_Time_Unit[4][20]					= { "H:",    "M:",     "s.",    "ms"};
static const int NSeqEdit_Time_X_Addr[4]					= { 110,     165,      220,     280};
char Time_Temp = '*';
void RedrawNSeqEdit(void)
{
	int i,previous_i=DispCT;
	char str[50];
	long dat;
	double fdat;
	unsigned char CV_flag=0;
	if(DispMode_SELECT_CH==DispMode) {
		if(DataRedrawFlag&BG_CLEAR_FLAG) {
			Displine(2,79,316,MEM_GRAY);
			Displine(2,80,316,GW_ORANGE_ku);
			Displine(2,81,316,MEM_WHITE);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_DispStringAt( "   Data Edit for Normal Sequence ", 15, 20);
		}

		for( i=0; i<P_NSeqEdit_Max; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				continue;

			if( (i==B_DispCT||i==DispCT)&&(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step)) {
				if(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode==CV_MODE) {
					if( (previous_i>=i) && (i==P_NSeqEdit_Ramp) ) {
						previous_i=i;
						i=P_NSeqEdit_Load;
						DispCT=i;
					} else if ( (previous_i<=i) && (i==P_NSeqEdit_Ramp)  ) {
						i=P_NSeqEdit_Trig;
						DispCT=i;
						previous_i=i;
					}

					if( (i==DispCT) && (i!=P_NSeqEdit_Ramp)	) {
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					}
					CV_flag =1;
				} else {
					if(i == DispCT)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					CV_flag =0;

				}
				previous_i=i;

				GUI_GotoXY(NSeqEdit_item_X_Addr[i]-5,NSeqEdit_item_Y_Addr[i]);

				if(i==P_NSeqEdit_Time_H)
					GUI_DispChars(' ',20);
				else
					GUI_DispChars(' ',NSeqEdit_light_space[i]);
			}

			if(i<1)
				GUI_SetColor(Parameter_Font_U_Bolor);
			else
				GUI_SetColor(Parameter_Font_L_Bolor);

			if((0==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step) ||( (P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode==CV_MODE) && (i==P_NSeqEdit_Ramp) ) )
				GUI_SetColor(MEM_DARKGRAY);

			GUI_DispStringAt( NSeqEdit_item_Data[i], NSeqEdit_item_X_Addr[i], NSeqEdit_item_Y_Addr[i]);
			dat  = GetChanData(i,0);
			if(i==P_NSeqEdit_Step)
				sprintf( str, " %04d ", dat);
			else if( i==P_NSeqEdit_Value) {
				fdat = StepToReal(dat,0);
				Display_Parameter_Pro(fdat,str,Search_precision(0));
			} else if( i==P_NSeqEdit_Time_H||i==P_NSeqEdit_Time_mS)
				sprintf( str, " %03d ", dat);
			else if( i==P_NSeqEdit_Time_M||i==P_NSeqEdit_Time_S)
				sprintf( str, " %02d ", dat);
			else if ((i==P_NSeqEdit_Ramp)&&(CV_flag))
				strcpy(  str, onoff_str[0]);
			else
				strcpy(  str, onoff_str[dat]);
			if((0==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step) ||( (P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode==CV_MODE) && (i==P_NSeqEdit_Ramp) ) )
				GUI_SetColor(MEM_DARKGRAY);
			else
				GUI_SetColor(Parameter_Font_R_Bolor);


			ShowSpace(NSeqEdit_space[i], NSeqEdit_Value_X_Addr[i], NSeqEdit_item_Y_Addr[i]);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, NSeqEdit_Value_X_Addr[i], NSeqEdit_item_Y_Addr[i]);

			if( P_NSeqEdit_Step==i) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				sprintf( str, " /   %04d ", GetChanData( P_NSeqEdit_Max , 0));
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, NSeqEdit_Value_X_Addr[i]+80, NSeqEdit_item_Y_Addr[i]);
			}

			if( i==P_NSeqEdit_Value) {
				if(CC_MODE==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode)
					sprintf( str, " A    ");
				else if(CR_MODE==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode)
					sprintf( str, " mS ");
				else if(CV_MODE==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode)
					sprintf( str, " V    ");
				else
					sprintf( str, " W    ");
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( str, NSeqEdit_Value_X_Addr[i], NSeqEdit_item_Y_Addr[i]);
			}

			if( (i>=P_NSeqEdit_Time_H)&&(i<=P_NSeqEdit_Time_mS) ) {
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( NSeqEdit_Time_Unit[i-P_NSeqEdit_Time_H], NSeqEdit_Time_X_Addr[i-P_NSeqEdit_Time_H], NSeqEdit_item_Y_Addr[i] );
				if( (DispCT>=P_NSeqEdit_Time_H)&&(DispCT<=P_NSeqEdit_Time_mS) ) {
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					if(0==P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step)

						GUI_SetColor(MEM_DARKGRAY);
					else
						GUI_SetColor(Parameter_Font_L_Bolor);

					GUI_GotoXY(NSeqEdit_item_X_Addr[i]-5,NSeqEdit_item_Y_Addr[i]);
					GUI_DispChars(' ',NSeqEdit_light_space[i]);
					GUI_DispStringAt( NSeqEdit_item_Data[i], NSeqEdit_item_X_Addr[i], NSeqEdit_item_Y_Addr[i]);
				}
			}

		}
	} else if(DispMode_BROWSE_ITEMS==DispMode) {
		if(P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Mode==CV_MODE)
			CV_flag =1;

		if((P_NSeqEdit_Step==DispCT)&&(0!=P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step)) {
			for( i=P_NSeqEdit_Step+1 ; i<P_NSeqEdit_Max ; i++) {
				GUI_SetBkColor(Parameter_Bottom_Bolor);
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( NSeqEdit_item_Data[i], NSeqEdit_item_X_Addr[i], NSeqEdit_item_Y_Addr[i]);
				dat = GetChanData(i,0);

				if(i==P_NSeqEdit_Value) {
					fdat = StepToReal(dat,0);
					Display_Parameter_Pro(fdat,str,Search_precision(0));
				} else if( i==P_NSeqEdit_Time_H||i==P_NSeqEdit_Time_mS)
					sprintf( str, " %03d ", dat);
				else if( i==P_NSeqEdit_Time_M||i==P_NSeqEdit_Time_S)
					sprintf( str, " %02d ", dat);
				else if ((i==P_NSeqEdit_Ramp)&&(CV_flag))
					strcpy(  str, onoff_str[0]);

				else
					strcpy(  str, onoff_str[dat]);

				GUI_SetColor(Parameter_Font_R_Bolor);
				ShowSpace(NSeqEdit_space[i], NSeqEdit_Value_X_Addr[i], NSeqEdit_item_Y_Addr[i]);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, NSeqEdit_Value_X_Addr[i], NSeqEdit_item_Y_Addr[i]);
			}
		}

		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(0!=P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Max_Step) {
			if(KeyInFlag & DIGI_KEY_IN)
				sprintf(str, "%s", KeyinBuf);
			else {
				dat = GetChanData(DispCT,0);
				if(DispCT==P_NSeqEdit_Step)
					sprintf( str, " %04d ", dat);
				else if( DispCT==P_NSeqEdit_Value) {
					fdat = StepToReal(dat,0);
					Display_Parameter_Pro(fdat,str,Search_precision(0));
				} else if( DispCT==P_NSeqEdit_Time_H||DispCT==P_NSeqEdit_Time_mS)
					sprintf( str, " %03d ", dat);
				else if( DispCT==P_NSeqEdit_Time_M||DispCT==P_NSeqEdit_Time_S)
					sprintf( str, " %02d ", dat);
				else
					strcpy(  str, onoff_str[dat]);
			}

			ShowSpace(NSeqEdit_space[DispCT], NSeqEdit_Value_X_Addr[DispCT], NSeqEdit_item_Y_Addr[DispCT]);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, NSeqEdit_Value_X_Addr[DispCT], NSeqEdit_item_Y_Addr[DispCT]);
		}
	}
}

static const char FSeq_item_Data[P_FSeq_Max][20]	= { "Memo:", "Mode:", "Range:", "Loop:", "Time Base:", "Last Load:", "Last:", "RPTSTEP:" };
static const int  FSeq_item_X_Addr[P_FSeq_Max]		= { 10,		 10,	  10,       10,      10,           160,          160,         160        };
static const int  FSeq_item_Y_Addr[P_FSeq_Max]		= { 65,      90,      115,      140,     165,          90,           115,         140        };
static const int  FSeq_Value_X_Addr[P_FSeq_Max]		= { 80,      118,     130,      128,     190,          310,          283,         310        };
static const char FSeq_space[P_FSeq_Max]			= { 2,       3,       4,        5,       7,            4,            7,           4          };
static const int  FSeq_light_space[P_FSeq_Max]		= { 22,      20,      24,       24,      40,           29,           29,          29         };
static const char FSeq_Mode_Item[2][20]				= { " CC ", " CR "};
static const char FSeq_Range_Item[4][20]			= { " ILVL ", " IHVL ", " ILVH ", " IHVH " };
void RedrawSeqFast(void)
{
	UBYTE i;
	char str[50];
	long dat;
	double fdat;

	if(DispMode_SELECT_CH==DispMode) {
		if(DataRedrawFlag&BG_CLEAR_FLAG) {
			Displine(2,55,316,MEM_GRAY);
			Displine(2,56,316,GW_ORANGE_ku);
			Displine(2,57,316,MEM_WHITE);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_DispStringAt( " Timing Edit for Fast Sequence ", 30, 25);
		}

		for( i=0 ; i<P_FSeq_Max ; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);

			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				continue;

			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(FSeq_item_X_Addr[i]-5,FSeq_item_Y_Addr[i]);
				GUI_DispChars(' ',FSeq_light_space[i]);
			}

			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( FSeq_item_Data[i], FSeq_item_X_Addr[i], FSeq_item_Y_Addr[i]);
			dat = GetChanData( i , 0);

			if( i==P_FSeq_Memo) {
				if(P3k_FSeq_Disp.FSeq_Memo[0]==0)
					sprintf( str, " No Memo ");
				else
					sprintf( str, " %s ",P3k_FSeq_Disp.FSeq_Memo);
			} else if( i==P_FSeq_Mode)
				strcpy(  str, FSeq_Mode_Item[dat]);
			else if( i==P_FSeq_Range)
				strcpy(  str, FSeq_Range_Item[dat]);
			else if( i==P_FSeq_Loop) {
				if(dat)
					sprintf( str, " %04d ", dat);
				else
					sprintf( str, " Infinity ");
			} else if(i==P_FSeq_TimeBase) {
				fdat = StepToReal(dat,i);
				Display_Parameter_Pro(fdat,str,Search_precision(i));
			} else if(i==P_FSeq_Last_Load)
				strcpy( str, onoff_str[dat]);
			else if(i==P_FSeq_Last_Set) {
				GUI_SetColor(Parameter_Font_R_Bolor);
				GUI_DispStringAt( FSeq_Mode_Unit[GetChanData( 1 , 0)], FSeq_Value_X_Addr[i], FSeq_item_Y_Addr[i]);

				fdat = StepToReal(dat,i);
				Display_Parameter_Pro(fdat,str,Search_precision(i));
			} else { /*P_FSeq_RptStep*/
				sprintf(str, " %04d ", dat+1);
			}

			GUI_SetColor(Parameter_Font_R_Bolor);

			if( i==P_FSeq_Memo) {
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_GotoXY(FSeq_Value_X_Addr[i], FSeq_item_Y_Addr[i]);
				GUI_DispChars(' ',46);
				GUI_SetTextAlign(GUI_TA_LEFT);
			} else {
				ShowSpace(FSeq_space[i], FSeq_Value_X_Addr[i], FSeq_item_Y_Addr[i]);
				GUI_SetTextAlign(GUI_TA_RIGHT);
			}

			GUI_DispStringAt( str, FSeq_Value_X_Addr[i], FSeq_item_Y_Addr[i]);

			if(P_FSeq_TimeBase==i) {
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( " ms ", FSeq_Value_X_Addr[P_FSeq_TimeBase]+2, FSeq_item_Y_Addr[P_FSeq_TimeBase]);
			}
		}
	} else if(DispMode_BROWSE_ITEMS==DispMode) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN)
			sprintf(str, "%s", KeyinBuf);
		else {
			dat = GetChanData(DispCT,0);
			if(DispCT==P_FSeq_Memo) {
				if(P3k_FSeq_Disp.FSeq_Memo[0]==0)
					sprintf( str, " No Memo ");
				else
					sprintf( str, " %s ",P3k_FSeq_Disp.FSeq_Memo);
			} else if(DispCT==P_FSeq_Mode)
				strcpy(  str, FSeq_Mode_Item[dat]);
			else if(DispCT==P_FSeq_Range)
				strcpy(  str, FSeq_Range_Item[dat]);
			else if(DispCT==P_FSeq_Loop) {
				if(dat)
					sprintf( str, " %04d ", dat);
				else
					sprintf( str, " Infinity ");
			} else if(DispCT==P_FSeq_TimeBase) {
				fdat = StepToReal(dat,DispCT);
				Display_Parameter_Pro(fdat,str,Search_precision(DispCT));
			} else if(DispCT==P_FSeq_Last_Load)
				strcpy( str, onoff_str[dat]);
			else if(DispCT==P_FSeq_Last_Set) {
				fdat = StepToReal(dat,DispCT);
				Display_Parameter_Pro(fdat,str,Search_precision(DispCT));
			} else { /*P_FSeq_RptStep*/
				sprintf(str, " %04d ", dat+1);
			}
		}
		if( DispCT==P_FSeq_Memo) {
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_GotoXY(FSeq_Value_X_Addr[DispCT], FSeq_item_Y_Addr[DispCT]);
			GUI_DispChars(' ',46);
			GUI_SetTextAlign(GUI_TA_LEFT);
		} else {
			ShowSpace(FSeq_space[DispCT], FSeq_Value_X_Addr[DispCT], FSeq_item_Y_Addr[DispCT]);
			GUI_SetTextAlign(GUI_TA_RIGHT);
		}
		GUI_DispStringAt( str, FSeq_Value_X_Addr[DispCT], FSeq_item_Y_Addr[DispCT]);
	}
}


#endif

#if Enable_OCP_function

static const char F_OCP_item_Data[P_F_OCP_Max][20]	= { "OCP. No:", "Range:", "Start C:", "End C:","Step C:","Step T:", "Delay:", "Trig V:",  "last C:" };
static const int  F_OCP_item_X_Addr[P_F_OCP_Max]		= { 65,		 10,	  10,       10,      10,    	165,       165,      165,    	165        };
static const int  F_OCP_item_Y_Addr[P_F_OCP_Max]		= { 65,      90,      115,      140,     165,        90,       115,      140 ,		165       };

static const int  F_OCP_Value_X_Addr[P_F_OCP_Max]		= { 210,     155,     155,      155,     155,        305,      305,      305 ,		305       };
static const char F_OCP_space[P_F_OCP_Max]				= { 3,       7,       7,        7,       7,          7,         7,        7   ,		7       };
static const int  F_OCP_light_space[P_F_OCP_Max]		= { 30,      28,      28,       28,      28,         28,        28,       28,		28         };
static const char F_OCP_Range_Item[3][20]				= { " Low ", " High ", " XX " };





void RedrawFuncOCP(void)
{
	UBYTE i;
	char str[50];
	long dat;
	double fdat;
	UBYTE CurrTemp,CurrRange;

	CurrTemp = P3K_OCP_Disp.CurrTemp ;
	F_OCP_OPP_Str *OCP = &P3K_OCP_Disp.Seq[CurrTemp];
	CurrRange = OCP->Range;
		
	double CurrRes = (ptrMODEL_TYPE->CC)[CurrRange*10].Resolution;//0.005;
	UBYTE CurrPre = (ptrMODEL_TYPE->CC)[CurrRange*10].precision;
	double VoltRes = (ptrMODEL_TYPE->CV)[3].Resolution;
	UBYTE VoltPre = (ptrMODEL_TYPE->CV)[3].precision;
	double TimeRes = 0.01;
	UBYTE TimePre = 2;
	
	if(DispMode_SELECT_CH==DispMode) {


		//OCP->Range = HIGH_RANGE;
		//OCP->StartCurrWatt = 1234;
		//OCP->EndCurrWatt = 5678;
		//OCP->StepCurrWatt = 1234;
		//OCP->StepTime = 9;
		//OCP->TrigVolt = 20;
		//OCP->DelayTime= 77;
		//OCP->LastCurrWatt= 98;


		if(DataRedrawFlag&BG_CLEAR_FLAG) {
			Displine(2,55,316,MEM_GRAY);
			Displine(2,56,316,GW_ORANGE_ku);
			Displine(2,57,316,MEM_WHITE);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_DispStringAt( " OCP Function ", 85, 25);
		}

		for( i=0 ; i<P_F_OCP_Max ; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);

			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				continue;
// blue bar
			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				Draw_Bar_25(F_OCP_item_X_Addr[i]-5,F_OCP_item_Y_Addr[i],F_OCP_light_space[i]);
				//GUI_DispChars(' ',F_OCP_light_space[i]);
			}
			if(i==P_F_OCP_CurrTemp)
				GUI_SetColor(Parameter_Font_U_Bolor);
			else
				GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( F_OCP_item_Data[i], F_OCP_item_X_Addr[i], F_OCP_item_Y_Addr[i]);
			//dat = GetChanData( i , 0);
			///if(i!=P_F_OCP_CurrTemp)
			///	ShowSpace(F_OCP_space[DispCT], F_OCP_Value_X_Addr[i], F_OCP_item_Y_Addr[i]);

			GUI_SetColor(Parameter_Font_R_Bolor);
			if(i==P_F_OCP_CurrTemp) {
				sprintf( str, " %02d ",CurrTemp+1);
			} else if(i==P_F_OCP_Range) {
				strcpy(  str, F_OCP_Range_Item[OCP->Range]);
			} else if(i==P_F_OCP_StartCurr) {
				fdat = OCP->StartCurrWatt*CurrRes;
				Display_Parameter_Pro(fdat,str,CurrPre);
			} else if(i==P_F_OCP_EndCurr) {
				fdat = OCP->EndCurrWatt*CurrRes;
				Display_Parameter_Pro(fdat,str,CurrPre);
			} else if(i==P_F_OCP_StepCurr) {
				fdat = OCP->StepCurrWatt*CurrRes;
				Display_Parameter_Pro(fdat,str,CurrPre);
			} else if(i==P_F_OCP_StepTime) {
				fdat = OCP->StepTime*TimeRes;
				Display_Parameter_Pro(fdat,str,TimePre);
			} else if(i==P_F_OCP_TrigVolt) {
				fdat = OCP->TrigVolt*VoltRes;
				Display_Parameter_Pro(fdat,str,VoltPre);
			} else if(i==P_F_OCP_DelayTrig) {
				fdat = OCP->DelayTime*TimeRes;
				Display_Parameter_Pro(fdat,str,TimePre);
			} else if(i==P_F_OCP_LastCurr) {
				fdat = OCP->LastCurrWatt*CurrRes;
				Display_Parameter_Pro(fdat,str,CurrPre);
			}

			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, F_OCP_Value_X_Addr[i], F_OCP_item_Y_Addr[i]);


		}
	} else if(DispMode_BROWSE_ITEMS==DispMode) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN)
			sprintf(str, "%s", KeyinBuf);
		else {
			if(DispCT==P_F_OCP_CurrTemp) {
				sprintf( str, " %02d ",CurrTemp+1);
			} else if(DispCT==P_F_OCP_Range) {
				strcpy(  str, F_OCP_Range_Item[OCP->Range]);
			} else if(DispCT==P_F_OCP_StartCurr) {
				fdat = OCP->StartCurrWatt*CurrRes;
				Display_Parameter_Pro(fdat,str,CurrPre);
			} else if(DispCT==P_F_OCP_EndCurr) {
				fdat = OCP->EndCurrWatt*CurrRes;
				Display_Parameter_Pro(fdat,str,CurrPre);
			} else if(DispCT==P_F_OCP_StepCurr) {
				fdat = OCP->StepCurrWatt*CurrRes;
				Display_Parameter_Pro(fdat,str,CurrPre);
			} else if(DispCT==P_F_OCP_StepTime) {
				fdat = OCP->StepTime*TimeRes;
				Display_Parameter_Pro(fdat,str,TimePre);
			} else if(DispCT==P_F_OCP_TrigVolt) {
				fdat = OCP->TrigVolt*VoltRes;
				Display_Parameter_Pro(fdat,str,VoltPre);
			} else if(DispCT==P_F_OCP_DelayTrig) {
				fdat = OCP->DelayTime*TimeRes;
				Display_Parameter_Pro(fdat,str,TimePre);
			} else if(DispCT==P_F_OCP_LastCurr) {
				fdat = OCP->LastCurrWatt*CurrRes;
				Display_Parameter_Pro(fdat,str,CurrPre);
			}
		}


		ShowSpace(F_OCP_space[DispCT], F_OCP_Value_X_Addr[DispCT], F_OCP_item_Y_Addr[DispCT]);
		GUI_SetTextAlign(GUI_TA_RIGHT);

		GUI_DispStringAt( str, F_OCP_Value_X_Addr[DispCT], F_OCP_item_Y_Addr[DispCT]);
	}
}

void RedrawFOcpExecute(void)
{
	#define data_Y		18

	char str[20],i;
	long dat;
	float dat1;
	UBYTE CurrTemp,CurrRange;
	static UBYTE tcont;
	
	CurrTemp = P3K_OCP_Disp.CurrTemp ;
	F_OCP_OPP_Str *OCP = &P3K_OCP_Disp.Seq[CurrTemp];
	CurrRange = OCP->Range;
		
	double CurrRes = (ptrMODEL_TYPE->CC)[CurrRange*10].Resolution;//0.005;
	UBYTE CurrPre = (ptrMODEL_TYPE->CC)[CurrRange*10].precision;
	double VoltRes = (ptrMODEL_TYPE->CV)[3].Resolution;
	UBYTE VoltPre = (ptrMODEL_TYPE->CV)[3].precision;

#if	redraw_new_flag == 0 
	RedrawMeasure();
#endif

	DMA_Update_Flag = 1;
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	if(P3K_OCP_Disp.UpdataFlag==1){
		tcont = 0;		
		GUI_SetFont(Parameter_Font);		
		GUI_SetColor(Parameter_Font_U_Bolor);
		GUI_DispStringAt("OCP Test ", 10, 115);
		Displine(0,111,320,MEM_GRAY);
		Displine(0,112,320,GW_ORANGE_ku);
		Displine(0,113,320,MEM_WHITE);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_SetFont(Upper_Font);
		GUI_DispStringAt( " Set Curr:  ",   180, 117);
		GUI_DispStringAt( " Fetch Volt: ",   245, 117);
	}
	if((P3K_OCP_Disp.Complete==1)||(P3K_OCP_Disp.UpdataFlag == 2)){
		GUI_SetFont(Parameter_Font);
		GUI_SetColor(Parameter_Font_R_Bolor);
		tcont+=16;
		if(tcont<50)			GUI_DispStringAt(" Running    ", 20, 138);
		else if(tcont<100)	GUI_DispStringAt(" Running.   ", 20, 138);
		else if(tcont<150)	GUI_DispStringAt(" Running..  ", 20, 138);
		else if(tcont<200)	GUI_DispStringAt(" Running... ", 20, 138);
		else 				GUI_DispStringAt(" Running....", 20, 138);
		GUI_SetFont(Upper_Font);		
		for (i=0;i<4;i++){			
			dat1 = P3K_OCP_Disp.RecCurr[i]*CurrRes;
			GUI_SetTextAlign(GUI_TA_RIGHT);
			if((dat1==0)&&(i!=0))	break;			
			Display_Parameter_Pro(dat1,str,CurrPre);
			GUI_DispStringAt( str, 233,(132+i*data_Y));
#if 1
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( " 				", 290,(132+i*data_Y));
#endif
			GUI_SetTextAlign(GUI_TA_RIGHT);
			dat1 = P3K_OCP_Disp.RecVolt[i]*0.01;	
			sprintf( str, "%3.2f", dat1);
			GUI_DispStringAt( str, 290,(132+i*data_Y));			
		}
	}else if(P3K_OCP_Disp.Complete==2){
		//GUI_SetFont(Parameter_Font);
		//GUI_SetColor(Parameter_Font_L_Bolor);
#if 1
		GUI_SetFont(Parameter_Font);		
		GUI_SetColor(Parameter_Font_U_Bolor);
		GUI_DispStringAt("OCP Test ", 10, 115);
		Displine(0,111,320,MEM_GRAY);
		Displine(0,112,320,GW_ORANGE_ku);
		Displine(0,113,320,MEM_WHITE);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_SetFont(Upper_Font);
		GUI_DispStringAt( " Set Curr:  ",   180, 117);
		GUI_DispStringAt( " Fetch Volt: ",   245, 117);
#endif
		GUI_SetFont(Parameter_Font);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt("                 ", 20, 138);
		GUI_DispStringAt("Current:  ", 40, 145);
		dat1 = P3K_OCP_Disp.RecCurr[1]*CurrRes;
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_SetFont(Measure_Unit_Font);
		GUI_SetColor(Parameter_Font_R_Bolor);
		Display_Parameter_Pro(dat1,str,CurrPre);
		GUI_DispStringAt( str, 110,170);
		GUI_DispStringAt("A", 110, 170);

		
	}else if(P3K_OCP_Disp.Complete==3){
		GUI_SetFont(Parameter_Font);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt("OCP time out ", 20, 138);
	}else if(P3K_OCP_Disp.Complete==4){
		GUI_SetFont(Parameter_Font);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt("Config Error ", 20, 138); 
	}
	P3K_OCP_Disp.UpdataFlag = 0;
	
}



#endif
#if Enable_OPP_function

static const char F_OPP_item_Data[P_F_OPP_Max][20]	= { "OPP. No:", "Range:", "Start W:", "End W:","Step W:","Step T:", "Delay:", "Trig V:",  "last W:" };
static const int  F_OPP_item_X_Addr[P_F_OPP_Max]		= { 65,		 10,	  10,       10,      10,    	165,       165,      165,    	165        };
static const int  F_OPP_item_Y_Addr[P_F_OPP_Max]		= { 65,      90,      115,      140,     165,        90,       115,      140 ,		165       };

static const int  F_OPP_Value_X_Addr[P_F_OPP_Max]		= { 210,     155,     155,      155,     155,        305,      305,      305 ,		305       };
static const char F_OPP_space[P_F_OPP_Max]				= { 3,       7,       7,        7,       7,          7,         7,        7   ,		7       };
static const int  F_OPP_light_space[P_F_OPP_Max]		= { 30,      28,      28,       28,      28,         28,        28,       28,		28         };
static const char F_OPP_Range_Item[2][20]				= { " Low ",  " High " };



void RedrawFuncOPP(void) {
	UBYTE i;
	char str[50];
	long dat;
	double fdat;
	UBYTE CurrTemp,CurrRange;

	CurrTemp = P3K_OPP_Disp.CurrTemp ;
	F_OCP_OPP_Str *OPP = &P3K_OPP_Disp.Seq[CurrTemp];
	CurrRange = OPP->Range;

	double WattRes = (ptrMODEL_TYPE->CP)[CurrRange*10].Resolution;//0.005;
	UBYTE WattPre = (ptrMODEL_TYPE->CP)[CurrRange*10].precision;
	double VoltRes = (ptrMODEL_TYPE->CV)[3].Resolution;
	UBYTE VoltPre = (ptrMODEL_TYPE->CV)[3].precision;
	double TimeRes = 0.01;
	UBYTE TimePre = 2;

	if(DispMode_SELECT_CH==DispMode) {

		if(DataRedrawFlag&BG_CLEAR_FLAG) {
			Displine(2,55,316,MEM_GRAY);
			Displine(2,56,316,GW_ORANGE_ku);
			Displine(2,57,316,MEM_WHITE);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_DispStringAt( " OPP Function ", 85, 25);
		}

		for( i=0 ; i<P_F_OPP_Max ; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);

			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				continue;
// blue bar
			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				Draw_Bar_25(F_OPP_item_X_Addr[i]-5,F_OPP_item_Y_Addr[i],F_OPP_light_space[i]);
				//GUI_DispChars(' ',F_OCP_light_space[i]);
			}
			if(i==P_F_OCP_CurrTemp)
				GUI_SetColor(Parameter_Font_U_Bolor);
			else
				GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( F_OPP_item_Data[i], F_OPP_item_X_Addr[i], F_OPP_item_Y_Addr[i]);
			//dat = GetChanData( i , 0);
			///if(i!=P_F_OCP_CurrTemp)
			///	ShowSpace(F_OCP_space[DispCT], F_OCP_Value_X_Addr[i], F_OCP_item_Y_Addr[i]);

			GUI_SetColor(Parameter_Font_R_Bolor);
			if(i==P_F_OCP_CurrTemp) {
				sprintf( str, " %02d ",CurrTemp+1);
			} else if(i==P_F_OPP_Range) {
				strcpy(  str, F_OPP_Range_Item[OPP->Range]);
			} else if(i==P_F_OPP_StartCurr) {
				fdat = OPP->StartCurrWatt*WattRes;
				fdat *= Get_Parallel_Parameter(OPP->Range);
				Display_Parameter_Pro(fdat,str,WattPre);
			} else if(i==P_F_OPP_EndCurr) {
				fdat = OPP->EndCurrWatt*WattRes;
				fdat *= Get_Parallel_Parameter(OPP->Range);
				Display_Parameter_Pro(fdat,str,WattPre);
			} else if(i==P_F_OPP_StepCurr) {
				fdat = OPP->StepCurrWatt*WattRes;
				fdat *= Get_Parallel_Parameter(OPP->Range);
				Display_Parameter_Pro(fdat,str,WattPre);
			} else if(i==P_F_OPP_StepTime) {
				fdat = OPP->StepTime*TimeRes;
				Display_Parameter_Pro(fdat,str,TimePre);
			} else if(i==P_F_OPP_TrigVolt) {
				fdat = OPP->TrigVolt*VoltRes;
				Display_Parameter_Pro(fdat,str,VoltPre);
			} else if(i==P_F_OPP_DelayTrig) {
				fdat = OPP->DelayTime*TimeRes;
				Display_Parameter_Pro(fdat,str,TimePre);
			} else if(i==P_F_OPP_LastCurr) {
				fdat = OPP->LastCurrWatt*WattRes;
				fdat *= Get_Parallel_Parameter(OPP->Range);
				Display_Parameter_Pro(fdat,str,WattPre);
			}

			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, F_OPP_Value_X_Addr[i], F_OPP_item_Y_Addr[i]);


		}
	} else if(DispMode_BROWSE_ITEMS==DispMode) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN)
			sprintf(str, "%s", KeyinBuf);
		else {
			if(DispCT==P_F_OPP_CurrTemp) {
				sprintf( str, " %02d ",CurrTemp+1);
			} else if(DispCT==P_F_OPP_Range) {
				strcpy(  str, F_OPP_Range_Item[OPP->Range]);
			} else if(DispCT==P_F_OPP_StartCurr) {
				fdat = OPP->StartCurrWatt*WattRes;
				fdat *= Get_Parallel_Parameter(OPP->Range);
				Display_Parameter_Pro(fdat,str,WattPre);
			} else if(DispCT==P_F_OPP_EndCurr) {
				fdat = OPP->EndCurrWatt*WattRes;
				fdat *= Get_Parallel_Parameter(OPP->Range);
				Display_Parameter_Pro(fdat,str,WattPre);
			} else if(DispCT==P_F_OPP_StepCurr) {
				fdat = OPP->StepCurrWatt*WattRes;
				fdat *= Get_Parallel_Parameter(OPP->Range);
				Display_Parameter_Pro(fdat,str,WattPre);
			} else if(DispCT==P_F_OPP_StepTime) {
				fdat = OPP->StepTime*TimeRes;
				Display_Parameter_Pro(fdat,str,TimePre);
			} else if(DispCT==P_F_OPP_TrigVolt) {
				fdat = OPP->TrigVolt*VoltRes;
				Display_Parameter_Pro(fdat,str,VoltPre);
			} else if(DispCT==P_F_OPP_DelayTrig) {
				fdat = OPP->DelayTime*TimeRes;
				Display_Parameter_Pro(fdat,str,TimePre);
			} else if(DispCT==P_F_OPP_LastCurr) {
				fdat = OPP->LastCurrWatt*WattRes;
				fdat *= Get_Parallel_Parameter(OPP->Range);
				Display_Parameter_Pro(fdat,str,WattPre);
			}
		}


		ShowSpace(F_OPP_space[DispCT], F_OPP_Value_X_Addr[DispCT], F_OPP_item_Y_Addr[DispCT]);
		GUI_SetTextAlign(GUI_TA_RIGHT);

		GUI_DispStringAt( str, F_OPP_Value_X_Addr[DispCT], F_OPP_item_Y_Addr[DispCT]);
	}
}

void RedrawFOppExecute(void) {
#define data_Y		18

	char str[20],i;
	long dat;
	float dat1;
	UBYTE CurrTemp,CurrRange;
	static UBYTE tcont;

	CurrTemp = P3K_OPP_Disp.CurrTemp ;
	F_OCP_OPP_Str *OPP = &P3K_OPP_Disp.Seq[CurrTemp];
	CurrRange = OPP->Range;

	double WattRes = (ptrMODEL_TYPE->CP)[CurrRange*10].Resolution;//0.005;
	UBYTE WattPre = (ptrMODEL_TYPE->CP)[CurrRange*10].precision;
	double VoltRes = (ptrMODEL_TYPE->CV)[3].Resolution;
	UBYTE VoltPre = (ptrMODEL_TYPE->CV)[3].precision;
#if	redraw_new_flag == 0 
	RedrawMeasure();
#endif
	DMA_Update_Flag = 1;
	GUI_SetBkColor(Parameter_Bottom_Bolor);
	if(P3K_OPP_Disp.UpdataFlag==1) {
		tcont = 0;
		GUI_SetFont(Parameter_Font);
		GUI_SetColor(Parameter_Font_U_Bolor);
		GUI_DispStringAt("OPP Test ", 10, 115);
		Displine(0,111,320,MEM_GRAY);
		Displine(0,112,320,GW_ORANGE_ku);
		Displine(0,113,320,MEM_WHITE);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_SetFont(Upper_Font);
		GUI_DispStringAt( " Set Watt:  ",   180, 117);
		GUI_DispStringAt( " Fetch Volt: ",   245, 117);
	}
	if((P3K_OPP_Disp.Complete==F_OCP_OPP_LOOKFOR)||(P3K_OPP_Disp.UpdataFlag == F_OCP_OPP_COMPLETE)) {
		GUI_SetFont(Parameter_Font);
		GUI_SetColor(Parameter_Font_R_Bolor);
		tcont+=16;
		if(tcont<50)			GUI_DispStringAt(" Running    ", 20, 138);
		else if(tcont<100)	GUI_DispStringAt(" Running.   ", 20, 138);
		else if(tcont<150)	GUI_DispStringAt(" Running..  ", 20, 138);
		else if(tcont<200)	GUI_DispStringAt(" Running... ", 20, 138);
		else 				GUI_DispStringAt(" Running....", 20, 138);
		GUI_SetFont(Upper_Font);

		for (i=0; i<4; i++) {
			dat1 = P3K_OPP_Disp.RecCurr[i]*WattRes;
			dat1 *= Get_Parallel_Parameter(OPP->Range);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			if((dat1==0)&&(i!=0))	break;
			Display_Parameter_Pro(dat1,str,WattPre);
			GUI_DispStringAt( str, 233,(132+i*data_Y));			
#if 1
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( "                 ", 290,(132+i*data_Y));
#endif		
			GUI_SetTextAlign(GUI_TA_RIGHT);
			dat1 = P3K_OPP_Disp.RecVolt[i]*0.01;
			sprintf( str, "%3.2f", dat1);
			GUI_DispStringAt( str, 290,(132+i*data_Y));
		}
	} else if(P3K_OPP_Disp.Complete==F_OCP_OPP_COMPLETE) {
		GUI_SetFont(Parameter_Font);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt("                 ", 20, 138);
		GUI_DispStringAt("Watt:        ", 40, 145);
		dat1 = P3K_OPP_Disp.RecCurr[1]*WattRes;
		dat1 *= Get_Parallel_Parameter(OPP->Range);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_SetFont(Measure_Unit_Font);
		GUI_SetColor(Parameter_Font_R_Bolor);
		Display_Parameter_Pro(dat1,str,WattPre);
		GUI_DispStringAt( str, 110,170);
		GUI_DispStringAt("W", 110, 170);


	} else if(P3K_OPP_Disp.Complete==F_OCP_OPP_TIMEOUT) {
		GUI_SetFont(Parameter_Font);
		GUI_SetColor(Parameter_Font_L_Bolor);
		//GUI_DispStringAt("Search Fail  ", 20, 138);
		GUI_DispStringAt("OPP time out ", 20, 138);
	} else if(P3K_OPP_Disp.Complete==F_OCP_OPP_CONFIG_ERR) {
		GUI_SetFont(Parameter_Font);
		GUI_SetColor(Parameter_Font_L_Bolor);
		GUI_DispStringAt("Config Error ", 20, 138);
	}
	P3K_OPP_Disp.UpdataFlag = 0;

}
#endif


#if Enable_Battery_Discharge


static const char F_BATT_item_Data[P_F_BATT_Max][20]	= { "Mode:", "Range:", "Setting:","SR \x80 ","SR \x7F","Stop V:", "Stop T:", "Stop C:" };
static const int  F_BATT_item_X_Addr[P_F_BATT_Max]		= { 10,		 10,	  10,       165,     165,    	10,       10,      165        };
static const int  F_BATT_item_Y_Addr[P_F_BATT_Max]		= { 65,      90,      115,      65,     90,        145,       170,      145     };
static const int  F_BATT_Value_X_Addr[P_F_BATT_Max]		= { 155,     155,     155,      305,     305,        155,      210,      305       };
static const char F_BATT_space[P_F_BATT_Max]				= { 7,       7,       7,        7,       7,          7,         7,        7         };
static const int  F_BATT_light_space[P_F_BATT_Max]		= { 30,      28,      28,       28,      28,         28,        28,       28       };

static const char F_BATT_Range_Item[4][20]				= { " ILVL ", " IHVL ", " ILVH ",  " IHVH " };

static const char F_BATT_item_Data2[P_F_BATT_Max][20]	= { "Mode:", "Range:", "Setting:","SlewRate \x80 ","SlewRate \x7F","Stop Volt:", "Stop Time:", "Stop AH:" };
static const int  F_BATT_item_X_Addr2[P_F_BATT_Max]		= { 10,		 10,	  10,       165,     165,    	10,       10,      165        };
static const int  F_BATT_item_Y_Addr2[P_F_BATT_Max]		= { 65,      90,      115,      65,     90,        145,       170,      145     };

static const int  F_BATT_Value_X_Addr2[P_F_BATT_Max]		= { 155,     155,     155,      305,     305,        155,      210,      305       };
static const char F_BATT_space2[P_F_BATT_Max]				= { 7,       7,       7,        7,       7,          7,         7,        7         };
//static const int  F_BATT_light_space2[P_F_BATT_Max]		= { 30,      28,      28,       28,      28,         28,        28,       28       };
static const char F_BATT_Range_mode[3][20]				= { "CC ", "CR ", "CP " };

static const char F_BATT_light_space2[P_F_BATT_Max] = { 4,5,7,7,7,7,2,7 };

static const char F_BATT_Unit[3][6] = {" A ", " mS ", " W "};


void RedrawFuncBatt2(void) {
	UBYTE i;
	char str[50];
	long dat;
	double fdat;
	UBYTE CurrTemp,CurrRange;

	CurrTemp = P3K_OCP_Disp.CurrTemp ;
	F_OCP_OPP_Str *OCP = &P3K_OCP_Disp.Seq[CurrTemp];
	CurrRange = OCP->Range;

	double CurrRes = (ptrMODEL_TYPE->CC)[CurrRange*10].Resolution;//0.005;
	UBYTE CurrPre = (ptrMODEL_TYPE->CC)[CurrRange*10].precision;
	double VoltRes = (ptrMODEL_TYPE->CV)[3].Resolution;
	UBYTE VoltPre = (ptrMODEL_TYPE->CV)[3].precision;
	double TimeRes = 0.01;
	UBYTE TimePre = 2;

	Displine(2,140,318,MEM_GRAY);
	Displine(2,141,318,GW_ORANGE_ku);
	Displine(2,142,318,MEM_WHITE);
	Displine(2,143,318,MEM_LIGHTGRAY_ku);
		
	if(DispMode_BROWSE_ITEMS==DispMode) {

		if(DataRedrawFlag&BG_CLEAR_FLAG) {
			Displine(2,55,316,MEM_GRAY);
			Displine(2,56,316,GW_ORANGE_ku);
			Displine(2,57,316,MEM_WHITE);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_DispStringAt( "Data Edit for Battery Discharge", 25, 25);
		}

		for( i=0 ; i<P_F_BATT_Max; i++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);

			if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispCT ) )
				continue;
// blue bar
			if( i == B_DispCT || i == DispCT ) {
				if( i == DispCT)
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				Draw_Bar_25(F_BATT_item_X_Addr[i]-5,F_BATT_item_Y_Addr[i],F_BATT_light_space[i]);
				
			}

			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt( F_BATT_item_Data[i], F_BATT_item_X_Addr[i], F_BATT_item_Y_Addr[i]);
			//dat = GetChanData( i , 0);
			///if(i!=P_F_OCP_CurrTemp)
			///	ShowSpace(F_OCP_space[DispCT], F_OCP_Value_X_Addr[i], F_OCP_item_Y_Addr[i]);

			GUI_SetColor(Parameter_Font_R_Bolor);
			if(i==P_F_BATT_Mode) {
				sprintf( str, " CC ");
			} else if(i==P_F_BATT_Range) {
				sprintf( str, " IHVL ");
			} else if(i==P_F_BATT_Set) {
				sprintf( str, "0.12345");
			} else if(i==P_F_BATT_SRUP) {
				sprintf( str, "0.12345");
			} else if(i==P_F_BATT_SRDW) {
				sprintf( str, "0.12345");
			} else if(i==P_F_BATT_StopV) {
				sprintf( str, "150.12");
			} else if(i==P_F_BATT_StopT) {
				sprintf( str, "999h:59m:59s");
			} else if(i==P_F_BATT_StopC) {
				sprintf( str, "98765");
			}

			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, F_BATT_Value_X_Addr[i], F_BATT_item_Y_Addr[i]);


		}
	} else if(DispMode_BROWSE_ITEMS==DispMode) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if(KeyInFlag & DIGI_KEY_IN)
			sprintf(str, "%s", KeyinBuf);
		else {
			if(DispCT==P_F_BATT_Mode) {
				sprintf( str, " %02d ",CurrTemp+1);
			} else if(DispCT==P_F_BATT_Mode) {
				strcpy(  str, F_BATT_Range_Item[OCP->Range]);
			} else if(DispCT==P_F_BATT_Mode) {
				fdat = OCP->StartCurrWatt*CurrRes;
				fdat *= Get_Parallel_Parameter(OCP->Range);
				Display_Parameter_Pro(fdat,str,CurrPre);
			} else if(DispCT==P_F_BATT_Mode) {
				fdat = OCP->EndCurrWatt*CurrRes;
				fdat *= Get_Parallel_Parameter(OCP->Range);
				Display_Parameter_Pro(fdat,str,CurrPre);
			} else if(DispCT==P_F_BATT_Mode) {
				fdat = OCP->StepCurrWatt*CurrRes;
				fdat *= Get_Parallel_Parameter(OCP->Range);
				Display_Parameter_Pro(fdat,str,CurrPre);
			} else if(DispCT==P_F_BATT_Mode) {
				fdat = OCP->StepTime*TimeRes;
				Display_Parameter_Pro(fdat,str,TimePre);
			} else if(DispCT==P_F_BATT_Mode) {
				fdat = OCP->TrigVolt*VoltRes;
				Display_Parameter_Pro(fdat,str,VoltPre);
			} else if(DispCT==P_F_BATT_Mode) {
				fdat = OCP->DelayTime*TimeRes;
				Display_Parameter_Pro(fdat,str,TimePre);
			} else if(DispCT==P_F_BATT_Mode) {
				fdat = OCP->LastCurrWatt*CurrRes;
				fdat *= Get_Parallel_Parameter(OCP->Range);
				Display_Parameter_Pro(fdat,str,CurrPre);
			}
		}


		ShowSpace(F_BATT_space[DispCT], F_BATT_Value_X_Addr[DispCT], F_BATT_item_Y_Addr[DispCT]);
		GUI_SetTextAlign(GUI_TA_RIGHT);

		GUI_DispStringAt( str, F_BATT_Value_X_Addr[DispCT], F_BATT_item_Y_Addr[DispCT]);
	}
}





#define Scroll_Bar_Start_X2 280
#define Conf_Para_Start_X2	200
#define Disp_Start_X2	15
void RedrawFuncBatt(void) {

	long dat;
	char str[20],range,Total_Display_Item,ScrollBar_Flag=0;
	int i,j;
	double fdat;

	P3k_Data_Str		*Data_tmp = &P3k_Chan_Data;
	UBYTE mode = BattDisp.Mode;
	UBYTE irang = BattDisp.Range%2;

	Total_Display_Item = P_F_BATT_Max;

	//DispScrStartCT = DispCT;
	if(DispMode == DispMode_BROWSE_ITEMS) {
		if(DataRedrawFlag&BG_CLEAR_FLAG){
			Displine(2,55,316,MEM_GRAY);
			Displine(2,56,316,GW_ORANGE_ku);
			Displine(2,57,316,MEM_WHITE);
			GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_DispStringAt( "Data Edit for Battery Discharge", 25, 25);
		}
		

		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			GUI_SetBkColor(Parameter_Bottom_Bolor);
			GUI_SetColor(Parameter_Font_L_Bolor);
			if( (DispScrCurrLoc == DispScrEndCT) || (DispScrCurrLoc == DispScrStartCT) ) {
				if(ScrollBar_Flag==0) {
					ShowScrollBar_Other(Scroll_Bar_Start_X2+4,Disp_Start_Y0,Total_Display_Item,Disp_Item_Num1,Disp_Interval,Scroll_Bar_Width,DispScrStartCT);
					GUI_SetBkColor(Parameter_Bottom_Bolor);
					ScrollBar_Flag = 1;
				}
				if(i == DispScrCurrLoc) 
					GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				Draw_Bar_25(Disp_Start_X2-4,Disp_Start_Y0+j*Disp_Interval,HiLight_Length+4);
			} else {
				if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispScrCurrLoc ) )
					continue;

				if(( i == B_DispCT)||( i == DispScrCurrLoc)) {
					if( i == DispScrCurrLoc)
						GUI_SetBkColor(Parameter_Select_Bar_Bolor);
					if((DataRedrawFlag&PARA_CHANGE_Fast)&&((DataRedrawFlag&BG_CLEAR_FLAG)==0)) {
						if( i == DispScrCurrLoc)
							Draw_New_Bar_25(Disp_Start_X2-4,Disp_Start_Y0+j*Disp_Interval,HiLight_Length+4,1);
						else
							Draw_New_Bar_25(Disp_Start_X2-4,Disp_Start_Y0+j*Disp_Interval,HiLight_Length+4,0);
						continue;
					} else {
						Draw_Bar_25(Disp_Start_X2-4,Disp_Start_Y0+j*Disp_Interval,HiLight_Length+4);
					}
				}
			}
			//GUI_SetColor(Parameter_Select_Font_Bolor);
			GUI_DispStringAt(F_BATT_item_Data2[i],Disp_Start_X2, Disp_Start_Y0+j*Disp_Interval);
			ShowSpace( F_BATT_light_space2[i], Conf_Para_Start_X2, Disp_Start_Y0+j*Disp_Interval);
			///dat = GetChanData(i,0);
					
			GUI_SetColor(Parameter_Font_R_Bolor);
			if(i==P_F_BATT_Mode) {
				sprintf( str, F_BATT_Range_mode[BattDisp.Mode]);				
			} else if(i==P_F_BATT_Range) {
				sprintf( str,F_BATT_Range_Item[BattDisp.Range]);
			} else if(i==P_F_BATT_Set) {
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( F_BATT_Unit[mode], Conf_Unit_Start_X, Disp_Start_Y0+j*Disp_Interval);
				fdat = StepToReal(BattDisp.Setting,i);
				if(CC_MODE==mode)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[irang*10].precision);
				else if(CR_MODE==mode){
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[irang*10].precision);
				}else{
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[irang*10].precision);
				}			
			} else if(i==P_F_BATT_SRUP) {
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( "mA/us", Conf_Unit_Start_X, Disp_Start_Y0+j*Disp_Interval);
				fdat = StepToReal(BattDisp.SRUP,i);
				if(CC_MODE==mode)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[irang*10+2].precision-BattDisp.SRUPRange);
				else if(CR_MODE==mode)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[irang*10+2].precision-BattDisp.SRUPRange);
				else
					sprintf( str, "default");
			} else if(i==P_F_BATT_SRDW) {
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( "mA/us", Conf_Unit_Start_X, Disp_Start_Y0+j*Disp_Interval);
				fdat = StepToReal(BattDisp.SRDW,i);
				if(CC_MODE==mode)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[irang*10+2].precision-0);
				else if(CR_MODE==mode)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[irang*10+2].precision-0);
				else
					sprintf( str, "default");
			} else if(i==P_F_BATT_StopV) {
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( "V", Conf_Unit_Start_X, Disp_Start_Y0+j*Disp_Interval);
				fdat = BattDisp.StopValt*0.01;
				Display_Parameter_Pro(fdat,str,2);
			} else if(i==P_F_BATT_StopT) {
				if(BattDisp.StopTime)
					sprintf( str, " %03dh: %02dm: %02ds ",BattDisp.StopHour,BattDisp.StopMin,BattDisp.StopSec);
				else
					sprintf( str, "     OFF      ");
				
			} else if(i==P_F_BATT_StopC) {
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( "Ah", Conf_Unit_Start_X, Disp_Start_Y0+j*Disp_Interval);
				fdat =BattDisp.StopCapa*0.01;
				if(BattDisp.StopCapa)
					Display_Parameter_Pro(fdat,str,2);
				else
					sprintf( str, "OFF");
			}
			GUI_SetTextAlign(GUI_TA_RIGHT);
			
			if(i==P_F_BATT_StopT)
				GUI_DispStringAt( str, 260, Disp_Start_Y0+j*Disp_Interval);
			else
				GUI_DispStringAt( str, Conf_Para_Start_X2, Disp_Start_Y0+j*Disp_Interval);
			
			
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		if(DispScrCurrLoc==P_F_BATT_StopT) {
			if(1) {
				GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				GUI_GotoXY(Disp_Start_X2,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				GUI_DispChars(' ',HiLight_Length);
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt(F_BATT_item_Data2[P_F_BATT_StopT],Disp_Start_X2, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_SetColor(Parameter_Font_R_Bolor);
				sprintf( str, " %03dh: %02dm: %02ds ",BattDisp.StopHour,BattDisp.StopMin,BattDisp.StopSec);
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, 260, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			}
			GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
			if(BattDisp.timeCnt==0)
				ShowSpace( 4,155,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			else if(BattDisp.timeCnt==1)
				ShowSpace( 3,197,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			else if(BattDisp.timeCnt==2)
				ShowSpace( 3,245,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		} else 
			ShowSpace( F_BATT_light_space2[DispScrCurrLoc],Conf_Para_Start_X2,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		if(KeyInFlag & DIGI_KEY_IN) {
			sprintf( str, " %s " , KeyinBuf );
			GUI_SetTextAlign(GUI_TA_RIGHT);
			if(DispScrCurrLoc!=P_F_BATT_StopT){				
				GUI_DispStringAt( str, Conf_Para_Start_X2, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);	
			}else{
				GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
				GUI_SetColor(Parameter_Select_Font_Bolor);
				if(BattDisp.timeCnt==0)
					GUI_DispStringAt( str, 155, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				else if(BattDisp.timeCnt==1)
					GUI_DispStringAt( str, 197, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				else if(BattDisp.timeCnt==2)
					GUI_DispStringAt( str, 245, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			}
		} else {
			dat = GetChanData(DispScrCurrLoc,0);
			if(DispScrCurrLoc==P_F_BATT_Mode) {
				sprintf( str, F_BATT_Range_mode[BattDisp.Mode]);				
			} else if(DispScrCurrLoc==P_F_BATT_Range) {
				sprintf( str,F_BATT_Range_Item[BattDisp.Range]);
			} else if(DispScrCurrLoc==P_F_BATT_Set) {
				fdat = StepToReal(BattDisp.Setting,DispScrCurrLoc);
				if(CC_MODE==mode)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[irang*10].precision);
				else if(CR_MODE==mode){
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[irang*10].precision);
				}else{
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[irang*10].precision);
				}			
			} else if(DispScrCurrLoc==P_F_BATT_SRUP) {
				fdat = StepToReal(BattDisp.SRUP,DispScrCurrLoc);
				if(CC_MODE==mode)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[irang*10+2].precision-BattDisp.SRUPRange);
				else if(CR_MODE==mode)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[irang*10+2].precision-BattDisp.SRUPRange);
				else
					sprintf( str, "default");
			} else if(DispScrCurrLoc==P_F_BATT_SRDW) {
				fdat = StepToReal(BattDisp.SRDW,DispScrCurrLoc);
				if(CC_MODE==mode)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[irang*10+2].precision-BattDisp.SRUPRange);
				else if(CR_MODE==mode)
					Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[irang*10+2].precision-BattDisp.SRUPRange);
				else
					sprintf( str, "default");
			} else if(DispScrCurrLoc==P_F_BATT_StopV) {
				fdat = BattDisp.StopValt*0.01;
				Display_Parameter_Pro(fdat,str,2);
			} else if(DispScrCurrLoc==P_F_BATT_StopC) {
				fdat =BattDisp.StopCapa*0.01;				
				Display_Parameter_Pro(fdat,str,2);
			}else if(DispScrCurrLoc==P_F_BATT_StopT){
				if(BattDisp.timeCnt==0)
					dat = BattDisp.StopHour;
				else if(BattDisp.timeCnt==1)
					dat = BattDisp.StopMin;
				else if(BattDisp.timeCnt==2)
					dat = BattDisp.StopSec;
				GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
				GUI_SetColor(Parameter_Select_Font_Bolor);

				fdat= dat;
				sprintf( str, " %d ", dat );				
				GUI_SetTextAlign(GUI_TA_RIGHT);
				
				if(BattDisp.timeCnt==0)
					GUI_DispStringAt( str, 155, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				else if(BattDisp.timeCnt==1)
					GUI_DispStringAt( str, 197, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
				else if(BattDisp.timeCnt==2)
					GUI_DispStringAt( str, 245, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			
			}
			
			if(DispScrCurrLoc!=P_F_BATT_StopT){
				GUI_SetTextAlign(GUI_TA_RIGHT);				
				GUI_DispStringAt( str, Conf_Para_Start_X2, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
			}
		}				
		
	}
}




void RedrawFuncBattExecute(void) {

	char str[70],str1[20];
	long dat;
	UBYTE mode,irang;
	float fdat;
	double data;
	ULONG disDA;
#if	redraw_new_flag == 0 
	RedrawMeasure();
#endif
	DMA_Update_Flag = 1;
	GUI_SetBkColor(Parameter_Bottom_Bolor);

	if(DataRedrawFlag&BG_CLEAR_FLAG) {	
		Displine(0,107+5,320,MEM_GRAY);
		Displine(0,108+5,320,GW_ORANGE_ku);
		Displine(0,109+5,320,MEM_WHITE);
	}
	GUI_SetColor(File_Message_Font_Bolor);
	GUI_SetFont(Measure_Unit_Font);
	GUI_SetTextAlign(GUI_TA_RIGHT);
	data = (double)BattDisp.AmpereHour/3600/8000;
	if(data<9.99){
		disDA = data*10000;
		data = disDA *0.0001; 
		sprintf(str,"%1.4f",data);
	}else if(data<99.99){
		disDA = data*1000;
		data = disDA *0.001; 
		sprintf(str,"%1.3f",data);
	}else if(data<999.99){ 
		disDA = data*100;
		data = disDA *0.01; 
		sprintf(str,"%1.2f",data);
	}else{
		disDA = data*10;
		data = disDA *0.1; 
		sprintf(str,"%1.1f",data);
	}
	GUI_DispStringAt( str,  115+10, 110+5);
	data = (double)BattDisp.WattHour/3600/8000;
	if(data<9.99){
		disDA = data*10000;
		data = disDA *0.0001; 
		sprintf(str,"%1.4f",data);
	}else if(data<99.99){
		disDA = data*1000;
		data = disDA *0.001; 
		sprintf(str,"%1.3f",data);
	}else if(data<999.99){ 
		disDA = data*100;
		data = disDA *0.01; 
		sprintf(str,"%1.2f",data);
	}else{
		disDA = data*10;
		data = disDA *0.1; 
		sprintf(str,"%1.1f",data);
	}
	GUI_SetTextAlign(GUI_TA_RIGHT);
	GUI_DispStringAt( str,  260+10, 110+5);

	
	if(DataRedrawFlag&BG_CLEAR_FLAG) {
		GUI_SetFont(File_Font);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( "Ah",  138+10, 120+5);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( "Wh",  290+10, 120+5);
#if 0
		GUI_SetFont(File_Font);
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_U_Bolor);

		if(BattDisp.status == BATT_COMPLETE){
			if(BattDisp.stopStatus==5)
				GUI_DispStringAt("Stop discharge:", 10, 142);
			else				
				GUI_DispStringAt("Complete discharge:", 10, 142);
		}else
			GUI_DispStringAt("Run BATT: ", 10, 142);
#endif		
		//GUI_SetFont(Time_Alarm_Font); 
   		GUI_SetFont(Parameter_Font);
		GUI_SetColor(Parameter_Font_R_Bolor);
		sprintf(str,"%s,  %s,",F_BATT_Range_mode[BattDisp.Mode],F_BATT_Range_Item[BattDisp.Range]);
		GUI_DispStringAt( str,  20, 156);
		mode = BattDisp.Mode;
		irang = BattDisp.Range%2;

		sprintf( str1,F_BATT_Unit[mode]);
		fdat = StepToReal(BattDisp.Setting,P_F_BATT_Set);
		if(CC_MODE==mode)
			Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CC)[irang*10].precision);
		else if(CR_MODE==mode){
			Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CR)[irang*10].precision);
		}else{
			Display_Parameter_Pro(fdat,str,(ptrMODEL_TYPE->CP)[irang*10].precision);
		}	
		sprintf(str,"%s%s",str,str1);

		GUI_DispStringAt( str,  130, 156);

#if 1
		GUI_SetFont(File_Font);
		GUI_SetBkColor(Parameter_Bottom_Bolor);
		GUI_SetColor(Parameter_Font_U_Bolor);
		if(BattDisp.status == BATT_COMPLETE){
			if(BattDisp.stopStatus==5)
				GUI_DispStringAt("Stop discharge:", 10, 142);
			else				
				GUI_DispStringAt("Complete discharge:", 10, 142);
		}else
			GUI_DispStringAt("Run BATT: ", 10, 142);		
#endif
		//GUI_SetFont(Time_Alarm_Font);
		GUI_SetFont(Parameter_Font);

		GUI_SetColor(Parameter_Font_L_Bolor);

		if(BattDisp.status == BATT_COMPLETE){
			sprintf(str,"                                                           ");
			GUI_DispStringAt( str, 20, 177);
			if(BattDisp.stopStatus==2)
				sprintf(str,"Stop Time : %d:%02d:%02d",BattDisp.StopHour,BattDisp.StopMin,BattDisp.StopSec);
			else if(BattDisp.stopStatus==3)
				sprintf(str,"Stop AH: %1.2fAh",BattDisp.StopCapa*0.01);
			else if(BattDisp.stopStatus==4)
				sprintf(str,"Stop Volt : %1.2fV",BattDisp.StopValt*0.01);
			GUI_DispStringAt( str, 20, 177);
		}else{			
			if((BattDisp.StopTime)&&(BattDisp.StopCapa))				
				sprintf(str,"Stop:%d:%02d:%02d,%1.2fV,%1.2fAh",BattDisp.StopHour,BattDisp.StopMin,BattDisp.StopSec,BattDisp.StopValt*0.01,BattDisp.StopCapa*0.01);
			else if(BattDisp.StopTime)
				sprintf(str,"Stop: %d:%02d:%02d,  %1.2fV",BattDisp.StopHour,BattDisp.StopMin,BattDisp.StopSec,BattDisp.StopValt*0.01);
			else if(BattDisp.StopCapa)
				sprintf(str,"Stop: %1.2fV,  %1.2fAh",BattDisp.StopValt*0.01,BattDisp.StopCapa*0.01);
			else
				sprintf(str,"Stop: %1.2fV",BattDisp.StopValt*0.01);			
			GUI_DispStringAt( str, 20, 177);
		}
	}	
}

#endif
#if Enable_LED_function
extern void set_start_ponit(UWORD x, UWORD y);
extern draw_clear_1(UWORD px,UWORD py,UWORD lenth,UWORD width,UWORD color);
extern void draw_clear_the_color(UWORD px,UWORD py,UWORD lenth,UWORD width,UWORD color1,UWORD color2);
extern void draw_dotted_line(UWORD px1, UWORD py1,UWORD px2, UWORD py2, UWORD color);
extern void draw_line(UWORD px1, UWORD py1,UWORD px2, UWORD py2, UWORD color);
extern void draw_point(WORD px, WORD py, UWORD color);
extern void draw_cir_point (UWORD x, UWORD y,UWORD color);
void drawVITable(UWORD vol, UWORD curr,UBYTE precisionV,UBYTE precisionC){
	UBYTE x,y;
	char str[70];
	set_start_ponit(8,56);
	draw_clear_1(0,0,307,182,MEM_WHITE);

	set_start_ponit(45,72);
	
#if 0
	draw_line(0,0,0,144,File_Bottom_Bolor);
	draw_line(240,0,240,144,File_Bottom_Bolor);
	draw_line(0,0,240,0,File_Bottom_Bolor);
	draw_line(0,144,240,144,File_Bottom_Bolor);
	for(x=1;x<=15;x++){		
		if(x%4==0){
			draw_line(x*15,1,x*15,143,MEM_LIGHTGRAY_ku);
			draw_point(x*15,-1,File_Bottom_Bolor);
			draw_point(x*15,-2,File_Bottom_Bolor);
			draw_point(x*15,-3,File_Bottom_Bolor);
		}else{
			draw_line(x*15,1,x*15,143,MEM_DARKGREEN_ku);
		}
	}
	for(y=1;y<=15;y++){		
		if(y%4==0){
			draw_line(1,y*9,239,y*9,MEM_LIGHTGRAY_ku);
			draw_point(-1,y*9,File_Bottom_Bolor);
			draw_point(-2,y*9,File_Bottom_Bolor);
			draw_point(-3,y*9,File_Bottom_Bolor);
		}else{
			draw_line(1,y*9,239,y*9,MEM_DARKGREEN_ku);
		}
	}	
#else
	draw_line(0,0,0,128,File_Bottom_Bolor);
	draw_line(256,0,256,128,File_Bottom_Bolor);
	draw_line(0,0,256,0,File_Bottom_Bolor);
	draw_line(0,128,256,128,File_Bottom_Bolor);

	for(x=1;x<=15;x++){		
		if(x%4==0){
			draw_line(x*16,1,x*16,127,MEM_LIGHTGRAY_ku);
			draw_point(x*16,-1,File_Bottom_Bolor);
			draw_point(x*16,-2,File_Bottom_Bolor);
			draw_point(x*16,-3,File_Bottom_Bolor);
		}else{
			draw_line(x*16,1,x*16,127,MEM_DARKGREEN_ku);
		}
	}
	for(y=1;y<=15;y++){		
		if(y%4==0){
			draw_line(1,y*8,255,y*8,MEM_LIGHTGRAY_ku);
			draw_point(-1,y*8,File_Bottom_Bolor);
			draw_point(-2,y*8,File_Bottom_Bolor);
			draw_point(-3,y*8,File_Bottom_Bolor);
		}else{
			draw_line(1,y*8,255,y*8,MEM_DARKGREEN_ku);
		}
	}	
#endif
	GUI_SetFont(Right_Font);
	GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
	GUI_SetColor(MEM_DARKBLUE_ku);
	GUI_DispStringAt( "Voltage-Current relationship for LED mode", 45, 30);

	GUI_SetFont(Right_Font);
	GUI_SetColor(File_Bottom_Bolor);
	GUI_SetTextAlign(GUI_TA_RIGHT);
	GUI_DispStringAt( "0A/0V", 50, 187);

	for (x=0;x<4;x++){
		sprintf(str,"%.*fV",precisionV,vol*0.01/4*(x+1));
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, 115+65*x, 187);
	}
	for (y=0;y<4;y++){
		sprintf(str,"%.*fA",precisionC,curr*0.01/4*(y+1));
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, 40, 145-32*y);
	}
}

static const char F_LED_item_Data[][20]	= 	{"LED No.:","Momo:","Range:","Response:","Parameter:"};

static const char F_LED_Range_Item[][20]= 	{ " ILVL ", " IHVL ", " ILVH ",  " IHVH " };
static const char F_LED_Para_Item[][20]	= 	{ " Vo,Io ", "Vo,Io,Rdcoeff", " Vo,Io,Rd ",  " Vo,Io,Vf ",  " Vf,Rd,pcs " };
static const char F_LED_Response_Item[][20]={ "Fast ", "Middle ", "Slow " };

static const char F_LED_light_space[] 		= { 4,7,5,6,11 };

#define LED_titile_x	25
#define LED_paramter_x	250
#define draw_title(x,x1,y1,z)	if(DataRedrawFlag&BG_CLEAR_FLAG){\
							Displine(2,x,316,MEM_GRAY);\
							Displine(2,x+1,316,GW_ORANGE_ku);\
							Displine(2,x+2,316,MEM_WHITE);\
							GUI_SetColor(Parameter_Font_U_Bolor);\
							GUI_SetBkColor(Parameter_Bottom_Bolor);\
							GUI_DispStringAt( z, x1, y1);}
#if 1
#define draw_form_1
#else
#define draw_form_1			Disp_ext_line(270,110,96,MEM_GRAY);\
							Disp_ext_line(271,110,96,GW_ORANGE_ku);\
							Disp_ext_line(272,110,96,MEM_WHITE);\
							Displine(2,109,316,MEM_GRAY);\
							Displine(2,110,316,GW_ORANGE_ku);\
							Displine(2,111,316,MEM_WHITE)
#endif
							//FloatSetPixel(100,i,Cursor1Col2);	/*LIGHT GRAY*/
							//FloatSetPixel(101,i,Cursor1Col3);	/*ORANGE*/
							//FloatSetPixel(102,i,Cursor1Col2);

#define draw_bar(x1,y1,barFlag)		GUI_SetBkColor(Parameter_Bottom_Bolor);\
								GUI_SetColor(Parameter_Font_L_Bolor);\
								if((DispScrCurrLoc == DispScrEndCT)||(DispScrCurrLoc == DispScrStartCT)){\
									if((ScrollBar_Flag==0)&& barFlag) {\
										ShowScrollBar_Other(x1+HiLight_Length*5,y1,Total_Display_Item,Disp_Item_Num1,Disp_Interval,Scroll_Bar_Width,DispScrStartCT);\
										GUI_SetBkColor(Parameter_Bottom_Bolor);\
										ScrollBar_Flag = 1;\
									}\
									if(i==DispScrCurrLoc)GUI_SetBkColor(Parameter_Select_Bar_Bolor);\
									Draw_Bar_25(x1-5,y1+j*Disp_Interval,HiLight_Length);\
								} else {\
									if(((DataRedrawFlag&BG_CLEAR_FLAG)==0)&&(DataRedrawFlag&PARA_CHANGE_Fast)&&( i != B_DispCT && i != DispScrCurrLoc))\
										continue;\
									if(( i == B_DispCT)||( i == DispScrCurrLoc)) {\
										if( i == DispScrCurrLoc)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);\
										if((DataRedrawFlag&PARA_CHANGE_Fast)&&((DataRedrawFlag&BG_CLEAR_FLAG)==0)) {\
											if( i == DispScrCurrLoc)\
												Draw_New_Bar_25(x1-5,y1+j*Disp_Interval,HiLight_Length,1);\
											else\
												Draw_New_Bar_25(x1-5,y1+j*Disp_Interval,HiLight_Length,0);\
											continue;\
										} else {\
											Draw_Bar_25(x1-5,y1+j*Disp_Interval,HiLight_Length);}}}




void DrawFLedPara(UBYTE cnt,char* str){
	UBYTE ledNo = P3k_FLed_Disp.currTemp;
	//ledNo = 0;
	F_LED_Str		*Disp_tmp = &P3k_FLed_Disp.seq[ledNo];
	///UBYTE irang = Disp_tmp->range%2;	
	
	if(cnt==P_F_LED_No) {
		sprintf( str,"%d",ledNo+1);
	}else if(cnt==P_F_LED_Momo) {
		if(Disp_tmp->name[0]==0)
			sprintf( str, " No Memo ");
		else
			sprintf( str, " %s ",Disp_tmp->name);	
	} else if(cnt==P_F_LED_Range) {
		sprintf( str,F_LED_Range_Item[Disp_tmp->range]);					
	} else if(cnt==P_F_LED_RESPONSE) {				
		sprintf( str,"%d ",Disp_tmp->response);
	}else if(cnt==P_F_LED_PATAMTER) {
		sprintf( str, F_LED_Para_Item[Disp_tmp->mode]);
	}
}

void RedrawFLed (void){ 
	char str[60],range,Total_Display_Item,ScrollBar_Flag=0;
	int i,j;
	char *str1 = str;

	Total_Display_Item = P_F_LED_Max;
	DispScrCurrLoc = DispCT;
 	
	if(DispMode <= DispMode_BROWSE_ITEMS) {
		draw_title(55,85,25,"LED Function");
		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			draw_bar (LED_titile_x,Disp_Start_Y0,0);			
			if(P_F_LED_No==i) GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_DispStringAt(F_LED_item_Data[i],LED_titile_x, Disp_Start_Y0+j*Disp_Interval);
			//ShowSpace( F_LED_light_space[i], LED_paramter_x, Disp_Start_Y0+j*Disp_Interval);
					
			GUI_SetColor(Parameter_Font_R_Bolor);
			DrawFLedPara(i,str1);			
			GUI_SetTextAlign(GUI_TA_RIGHT);			
			GUI_DispStringAt( str, LED_paramter_x, Disp_Start_Y0+j*Disp_Interval);			
			if(i==3){
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( "%", LED_paramter_x, Disp_Start_Y0+j*Disp_Interval);
			}		
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		ShowSpace( F_LED_light_space[DispScrCurrLoc],LED_paramter_x,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		if(KeyInFlag & DIGI_KEY_IN) {
			sprintf( str, " %s " , KeyinBuf );
			GUI_SetTextAlign(GUI_TA_RIGHT);		
			GUI_DispStringAt( str, LED_paramter_x, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);		
		} else {
			DrawFLedPara(DispScrCurrLoc,str1);
			GUI_SetTextAlign(GUI_TA_RIGHT); 			
			GUI_DispStringAt( str, LED_paramter_x , Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		}		
	}
	//FPGA_W[252] =1;
}

//static const char LED_PARA_1[5][15] = 	{" Vo "," Io "," Vf "," Rd" };
static const char LED_PARA_1[5][3][10] = {{" Vo "," Io "," "},{" Vo "," Io ","Rd ceoff"},{" Vo "," Io ","Rd"},{" Vo "," Io ","Vf"},{" Vf"," Rd ","pcs"}};
static const char led_unit[5][3][4] = {{"V","A"," "},{"V","A","%"},{"V","A","\x82"},{"V","A","V"},{"V","\x82",""}};
static const char cled_unit[6][4] = {"","","","%","V","A"};
static const char cled_unit3[6][4] = {"V","A","%"};


//static const char led_num[5]= {2,3,3,3,3};


void DrawVI (UBYTE mode){

#define table_color1 		MEM_WHITE
#define table_color2 		MEM_LIGNTGREEN

#define paramter_color1 	MEM_ORANGE_ku
#define paramter_color2 	MEM_WHITE
#define table_line_color2 	MEM_DARKRED
#define table_line_color 	MEM_DARKRED_ku




	UBYTE i;
	char str[70];
	char const disFlag[]={0x03,0x0B,0x07,0x13,0x34};
	/* Vo, Io, Rd, Rcoff, Vf, pcs*/
	
	if(DataRedrawFlag&BG_CLEAR_FLAG){		
		ClearP3KMeasBG(MEM_BLACK);
		draw_form_1;
		set_start_ponit(60,142);
		//draw_clear_1(0,0,170,92,MEM_BLACK);//draw_clear_1(0,0,140,72,MEM_WHITE);
		GUI_SetFont(Right_Font);	
		GUI_SetBkColor(MEM_BLACK);	//GUI_SetBkColor(MEM_WHITE);	
		
		if(disFlag[mode]&0x01)	GUI_SetColor(paramter_color1);
		else					GUI_SetColor(paramter_color2);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( "Vo", 195-34, 88);		
		
		if(disFlag[mode]&0x02)	GUI_SetColor(paramter_color1);
		else					GUI_SetColor(paramter_color2);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( "Io", 72-36, 30);

		if(disFlag[mode]&0x04){
			GUI_SetColor(paramter_color1);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( "Rd =", 250-30, 42+8);
			GUI_SetColor(paramter_color2);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( "Vo - Vf", 292-30, 32+8);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( "Io", 280-30, 48+8);
		}else{
			
		}
		if(disFlag[mode]&0x08){
			GUI_SetColor(paramter_color1);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( "Rcoff =", 250-30, 42+8);
			GUI_SetColor(paramter_color2);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( "Vo - Vf", 292-30, 32+8);
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( "Vo", 280-30, 48+8);
		}else{
			
		}

		if(disFlag[mode]&0x10)	GUI_SetColor(paramter_color1);
		else					GUI_SetColor(paramter_color2);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( "Vf", 135-30, 88);
		//GUI_SetTextAlign(GUI_TA_RIGHT);
		
		if(disFlag[mode]&0x20){
			//GUI_SetColor(MEM_ORANGE_ku);
		}else{
			//GUI_SetColor(MEM_WHITE);
		}		

		set_start_ponit(40,170);
		if(disFlag[mode]&0x0C)draw_line(182,38-8,224,38-8,table_color1);
		
		draw_line(0,0,0,60,table_color2);
		draw_line(1,0,1,60,table_color2);
		draw_line(0,0,125,0,table_color2);
		draw_line(0,1,125,1,table_color2);
		
		draw_line(2,2,60,2,table_line_color);
		draw_line(2,3,60,3,table_line_color);
		draw_line(2,4,60,4,table_line_color);
		draw_line(2,5,60,5,table_line_color2);
		
		draw_line(60,2,120,58,table_line_color);
		draw_line(60,3,120,59,table_line_color);
		draw_line(60,4,120,60,table_line_color);		
		draw_line(60,5,120,61,table_line_color2);
		
		
		draw_dotted_line(110,1,110,50,table_color2); //MEM_LIGHTGRAY_ku);
		draw_dotted_line(1,50,110,50,table_color2);
		draw_cir_point(110,50,MEM_DARKRED_ku);	

	}
}
void DrawFLedEditPara (void){
	UBYTE x,y;
	char str[70];
	F_LED_Str *Disp_tmp = &P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp];
	long dat;
	int i,j;
	char Total_Display_Item,ScrollBar_Flag=0,space_Flag=0;
	double fdat;
	char prec;
	///printf("flag:%x",DataRedrawFlag);
	GUI_SetColor(Parameter_Font_L_Bolor);
	GUI_SetBkColor(Parameter_Bottom_Bolor);	
	GUI_SetFont(Parameter_Font);

	Total_Display_Item = 2;//CP_Sta_Max;
	DispCT = DispScrCurrLoc;
	if( DispMode <= DispMode_BROWSE_ITEMS) {		
		DrawBar(0,Total_Display_Item,Disp_Start_Y1);
		for(i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++){				
			GUI_SetBkColor(Parameter_Bottom_Bolor);			
			if(DrawBar(1,i,j)){				
				if(DispScrCurrLoc == i)	GUI_SetBkColor(Parameter_Select_Bar_Bolor);
				else					GUI_SetBkColor(Parameter_Bottom_Bolor);	
				GUI_SetColor(Parameter_Font_L_Bolor);
				GUI_DispStringAt( LED_PARA_1[Disp_tmp->mode][i] , Disp_Start_X, Disp_Start_Y1+j*Disp_Interval);
				GUI_SetColor(Parameter_Font_R_Bolor);
				dat = GetChanData(i,0);
				fdat = StepToReal(dat,i);
				prec = get_chan_prec(i);
				if(prec != 7)
					Display_Parameter_Pro(fdat,str,prec);
				else {
					if(fdat)
						Display_Parameter_Pro((1000.0/fdat),str,7);
					else
						sprintf(str," OPEN ");
				}
				
				GUI_SetTextAlign(GUI_TA_RIGHT);
				GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+j*Disp_Interval);
				GUI_SetTextAlign(GUI_TA_LEFT);
				GUI_DispStringAt( led_unit[Disp_tmp->mode][i], Unit_Start_X, Disp_Start_Y1+j*Disp_Interval);
			}
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);

		if( KeyInFlag & DIGI_KEY_IN )
			sprintf( str, " %s " , KeyinBuf );
		else {
			dat = GetChanData(DispScrCurrLoc,0);
			fdat = StepToReal(dat, DispScrCurrLoc);
			prec = get_chan_prec(DispScrCurrLoc);
			if(prec != 7)
				Display_Parameter_Pro(fdat,str,prec);
			else {
				if(fdat)
					Display_Parameter_Pro((1000.0/fdat),str,7);
				else
					sprintf(str," OPEN ");
			}
		}
		ShowSpace( 7, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( str, Para_Start_X, Disp_Start_Y1+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
	}
}

void RedrawFLedEdit (void){	
	F_LED_Str *Disp_tmp = &P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp];
	DrawVI(Disp_tmp->mode);	
	DrawFLedEditPara();
}

void RedrawFLedExecute(void){	
	//RedrawMeasure();
	if(DataRedrawFlag&BG_CLEAR_FLAG){
		RedrawMeasure();
		draw_form_1;
	}
	DrawFLedEditPara();
}


static const char F_CLED_item_Data[][20]	= 	{"CLED No.:","Momo:","Range:","Response:","Vo:","Io"};
static const char F_CLED_Para_Item[][20]	= 	{ "Vo,Io", "Vo,Io,Coff", "Vo,Io,Rd",  "Vo,Io,Vf",  "Vf,Rd,pcs" };
static const char F_CLED_light_space[] 		= { 4,7,5,6,8,8 };



void DrawCLedPara(UBYTE cnt,char* str){
	UBYTE ledNo = P3k_CLed_Disp.currTemp;
	F_LED_Str		*Disp_tmp = &P3k_CLed_Disp.seq[ledNo];
	UWORD dat;
	double fdat;
	UBYTE prec;
	
	if(cnt==P_CLED_No) {
		sprintf( str,"%d",ledNo+1);
	}else if(cnt==P_CLED_Momo) {
		if(Disp_tmp->name[0]==0)
			sprintf( str, " No Memo ");
		else
			sprintf( str, " %s ",Disp_tmp->name);	
	} else if(cnt==P_CLED_Range) {
		sprintf( str,F_LED_Range_Item[Disp_tmp->range]);					
	} else if(cnt==P_CLED_RESPONSE) {	
		sprintf( str,"%d ",Disp_tmp->response);
		//sprintf( str,F_LED_Response_Item[Disp_tmp->response]);
	}else if((cnt==P_CLED_VO)||(cnt==P_CLED_IO)) {
		dat = GetChanData(cnt,0);
		fdat = StepToReal(dat,cnt);
		prec = get_chan_prec(cnt);
		Display_Parameter_Pro(fdat,str,prec);
	}
}

void RedrawCLed (void){ 
	char str[60],range,Total_Display_Item,ScrollBar_Flag=0;
	int i,j;
	char *str1 = str;

	Total_Display_Item = P_CLED_Max;
	DispScrCurrLoc = DispCT;
 	
	if(DispMode <= DispMode_BROWSE_ITEMS) {
		draw_title(55,75,25,"Curve LED Function");
		for( i=DispScrStartCT, j=0 ; i<=DispScrEndCT ; i++, j++) {
			draw_bar (LED_titile_x,Disp_Start_Y0,1);			
			if(P_F_LED_No==i) GUI_SetColor(Parameter_Font_U_Bolor);
			GUI_DispStringAt(F_CLED_item_Data[i],LED_titile_x, Disp_Start_Y0+j*Disp_Interval);
			ShowSpace( F_CLED_light_space[i], LED_paramter_x, Disp_Start_Y0+j*Disp_Interval);
					
			GUI_SetColor(Parameter_Font_R_Bolor);
			DrawCLedPara(i,str1);			
			GUI_SetTextAlign(GUI_TA_RIGHT);			
			GUI_DispStringAt( str, LED_paramter_x, Disp_Start_Y0+j*Disp_Interval);
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_DispStringAt( cled_unit[i], LED_paramter_x, Disp_Start_Y0+j*Disp_Interval);
		}
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		ShowSpace( F_CLED_light_space[DispScrCurrLoc],LED_paramter_x,Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		if(KeyInFlag & DIGI_KEY_IN) {
			sprintf( str, " %s " , KeyinBuf );
			GUI_SetTextAlign(GUI_TA_RIGHT);		
			GUI_DispStringAt( str, LED_paramter_x, Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);		
		} else {
			DrawCLedPara(DispScrCurrLoc,str1);
			GUI_SetTextAlign(GUI_TA_RIGHT); 			
			GUI_DispStringAt( str, LED_paramter_x , Disp_Start_Y0+(DispScrCurrLoc - DispScrStartCT)*Disp_Interval);
		}		
	}
}
void draw_curve_back_table(float vol, float curr,UBYTE precisionV,UBYTE precisionC){
	UBYTE x,y;
	char str[70];
#define back_color		MEM_BLACK
#define form_color1 	MEM_WHITE//MEM_LIGNTGREEN
#define form_color2 	GW_LIGHTGRAY_ku
#define form_color3 	GW_DARKGRAY


#define title_color 	MEM_LIGNTGREEN//MEM_WHITE
#define para_color 		MEM_WHITE

#define line_color		File_Bottom_Bolor


	
	if(DataRedrawFlag&BG_CLEAR_FLAG)	{
		set_start_ponit(3,86);
		draw_clear_1(0,0,315,152,back_color);
	}else{
		set_start_ponit(45,102);
		draw_clear_1(0,0,260,115,back_color);
	}	

	set_start_ponit(45,101);
	draw_line(0,0,256,0,form_color1);
	
	set_start_ponit(45,102);
	draw_line(0,0,0,112,form_color1);
	draw_line(256,0,256,112,form_color1);
	draw_line(0,0,256,0,form_color2);
	draw_line(0,112,256,112,form_color1);

	for(x=1;x<=15;x++){		
		if(x%4==0){
			draw_line(x*16,1,x*16,111,form_color2);
			draw_point(x*16,-1,form_color2);
			draw_point(x*16,-2,form_color2);
			draw_point(x*16,-3,form_color2);
		}else{
			draw_line(x*16,1,x*16,111,form_color3);
		}
	}
	for(y=1;y<=15;y++){		
		if(y%4==0){
			draw_line(1,y*7,255,y*7,form_color2);
			draw_point(-1,y*7,form_color2);
			draw_point(-2,y*7,form_color2);
			draw_point(-3,y*7,form_color2);
		}else{
			draw_line(1,y*7,255,y*7,form_color3);
		}
	}
	
#if 1
	if(DataRedrawFlag&BG_CLEAR_FLAG)	{
		GUI_SetFont(Right_Font);
		GUI_SetBkColor(back_color);
		GUI_SetColor(title_color);
		GUI_DispStringAt( "Voltage-Current relationship for LED mode", 45, 24);

		GUI_SetFont(Right_Font);
		GUI_SetColor(para_color);
		GUI_SetTextAlign(GUI_TA_RIGHT);
		GUI_DispStringAt( "0A/0V", 50, 155);

		for (x=0;x<4;x++){
			sprintf(str,"%.*fV",precisionV,vol/4*(x+1));
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, 115+65*x, 155);
		}
		for (y=0;y<4;y++){
			sprintf(str,"%.*fA",precisionC,curr/4*(y+1));
			GUI_SetTextAlign(GUI_TA_RIGHT);
			GUI_DispStringAt( str, 40, 120-28*y);
		}
	}
#endif	
}


void DrawCLedTable (void){
	UWORD i;
	static UWORD sY=0;
	UWORD x,y;	
	float getVolt,getCurr;
	F_LED_Str *Disp_tmp = &P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp];
	UBYTE vRange = Disp_tmp->range / 2;
	UBYTE iRange = Disp_tmp->range % 2;
	float Vo = Disp_tmp->vo *(ptrMODEL_TYPE->CV)[vRange*3].Resolution;	
	float Io = Disp_tmp->io*(ptrMODEL_TYPE->CC)[iRange*10].Resolution;
	float Ir = Disp_tmp->ir;	
	float C = Disp_tmp->c;
	float maxV = Vo*4/3;
	float maxI = Io*2;
	char drawFlag = 0; //bit0: imax=sys_max

	if(maxV>((ptrMODEL_TYPE->CV)[vRange*3].Resolution*(ptrMODEL_TYPE->CV)[vRange*3].Max))
		maxV = ((ptrMODEL_TYPE->CV)[vRange*3].Resolution*(ptrMODEL_TYPE->CV)[vRange*3].Max);
	if(maxI>((ptrMODEL_TYPE->CC)[iRange*10].Resolution*(ptrMODEL_TYPE->CC)[iRange*10].Max)){
		maxI = ((ptrMODEL_TYPE->CC)[iRange*10].Resolution*(ptrMODEL_TYPE->CC)[iRange*10].Max);
		drawFlag = 1;
	}

	float vGap = maxV/256;
	float iGap = maxI/112;

	draw_curve_back_table(maxV,maxI,1,1);
	draw_cir_point(Vo/vGap,Io/iGap,MEM_DARKRED_ku);	


	for(i=0;i<=256;i++){
		getVolt = i*vGap;
		getCurr = Ir * (exp(C*getVolt)-1);
		
		if (getCurr > maxI){
			x = i;
			if(sY){
				draw_line(x,sY,x,111,MEM_DARKRED_ku);
				sY = 0;
			}else{
				///if(drawFlag) draw_point(x,111,MEM_DARKRED_ku);
			}
		}else{
			x = i;
			y = getCurr / iGap;
			if((y-1)>sY){
				draw_line(x,sY,x,y,MEM_DARKRED_ku);
			}else{
				draw_point(x,y,MEM_DARKRED_ku);
				draw_point(x,y+1,MEM_DARKRED_ku);
			}
			sY = y;///+1;
		}
		//if((i%64)==0)printf("I:%1.3f\n",getCurr);
	}
	

	GUI_SetFont(Parameter_Font);
}

void DrawCLedEditPara(void){
	UWORD dat;
	float fdat;
	UBYTE prec;
	char str[16];
#if 1
	if(DispMode == DispMode_BROWSE_ITEMS) {
		GUI_SetBkColor(Parameter_Select_Bar_Bolor);
		GUI_SetColor(Parameter_Font_L_Bolor);
		if(DataRedrawFlag&BG_CLEAR_FLAG)	{
			Draw_Bar_25(3,5+Disp_Start_Y1+2*Disp_Interval,HiLight_Length+12);
			GUI_DispStringAt("Rd coeff",LED_titile_x-18, 5+Disp_Start_Y1+2*Disp_Interval);
		}
		ShowSpace( 8, LED_paramter_x-80, 5+Disp_Start_Y1+2*Disp_Interval);
		dat = GetChanData(0,0);
		fdat = StepToReal(dat,0);
		prec = get_chan_prec(0);
		Display_Parameter_Pro(fdat,str,prec);
		GUI_SetColor(Parameter_Font_R_Bolor);			
		GUI_SetTextAlign(GUI_TA_RIGHT);			
		GUI_DispStringAt( str, LED_paramter_x-80, 5+Disp_Start_Y1+2*Disp_Interval);	
		GUI_SetTextAlign(GUI_TA_LEFT);
		GUI_DispStringAt( "%", LED_paramter_x-80, 5+Disp_Start_Y1+2*Disp_Interval);
		GUI_SetTextAlign(GUI_TA_RIGHT);	
		sprintf(str,"%f",P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].ir);
		GUI_DispStringAt( str, LED_paramter_x+45, 5+Disp_Start_Y1+2*Disp_Interval);	
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		ShowSpace( 8, LED_paramter_x-80, 5+Disp_Start_Y1+2*Disp_Interval);
		if(KeyInFlag & DIGI_KEY_IN) {
			sprintf( str, " %s " , KeyinBuf );
			GUI_SetTextAlign(GUI_TA_RIGHT);		
			GUI_DispStringAt( str, LED_paramter_x-80, 5+Disp_Start_Y1+2*Disp_Interval);		
		} else {
			dat = GetChanData(0,0);
			fdat = StepToReal(dat,0);
			prec = get_chan_prec(0);
			Display_Parameter_Pro(fdat,str,prec);
			GUI_SetTextAlign(GUI_TA_RIGHT); 			
			GUI_DispStringAt( str, LED_paramter_x-80 , 5+Disp_Start_Y1+2*Disp_Interval);
		}		
	}
#else
	if(DispMode == DispMode_BROWSE_ITEMS) {
		GUI_SetBkColor(Parameter_Select_Bar_Bolor);
		GUI_SetColor(Parameter_Font_L_Bolor);
		if(DataRedrawFlag&BG_CLEAR_FLAG)	{
			Draw_Bar_25(3,5+Disp_Start_Y1+2*Disp_Interval,HiLight_Length+12);
			GUI_DispStringAt("Rd coeff",LED_titile_x, 5+Disp_Start_Y1+2*Disp_Interval);
		}
		ShowSpace( 8, LED_paramter_x, 5+Disp_Start_Y1+2*Disp_Interval);
		dat = GetChanData(0,0);
		fdat = StepToReal(dat,0);
		prec = get_chan_prec(0);
		Display_Parameter_Pro(fdat,str,prec);
		GUI_SetColor(Parameter_Font_R_Bolor);			
		GUI_SetTextAlign(GUI_TA_RIGHT);			
		GUI_DispStringAt( str, LED_paramter_x, 5+Disp_Start_Y1+2*Disp_Interval);	
		GUI_SetTextAlign(GUI_TA_LEFT);
		GUI_DispStringAt( "%", LED_paramter_x, 5+Disp_Start_Y1+2*Disp_Interval);
	} else if(DispMode == DispMode_SET_PARAMETERS) {
		GUI_SetBkColor(Parameter_Select_Bottom_Bolor);
		GUI_SetColor(Parameter_Select_Font_Bolor);
		ShowSpace( 8, LED_paramter_x, 5+Disp_Start_Y1+2*Disp_Interval);
		if(KeyInFlag & DIGI_KEY_IN) {
			sprintf( str, " %s " , KeyinBuf );
			GUI_SetTextAlign(GUI_TA_RIGHT);		
			GUI_DispStringAt( str, LED_paramter_x, 5+Disp_Start_Y1+2*Disp_Interval);		
		} else {
			dat = GetChanData(0,0);
			fdat = StepToReal(dat,0);
			prec = get_chan_prec(0);
			Display_Parameter_Pro(fdat,str,prec);
			GUI_SetTextAlign(GUI_TA_RIGHT); 			
			GUI_DispStringAt( str, LED_paramter_x , 5+Disp_Start_Y1+2*Disp_Interval);
		}		
	}
#endif	
}

void RedrawCLedEdit(void){	
	DrawCLedTable();
	DrawCLedEditPara();	
}
static const char F_CLED_exe_item_Data[][20] = {"Vo:","Io:","Rd coeff"};

void RedrawCLedExecute(void){
	char i;
	UWORD dat;
	float fdat;
	UBYTE prec;
	char str[16];
	
	//RedrawMeasure();
	if(DataRedrawFlag&BG_CLEAR_FLAG)	{
		RedrawMeasure();
		draw_form_1;
		GUI_SetFont(Parameter_Font);
		for(i=0;i<P_CLED_EXE_Max;i++){
			GUI_SetColor(Parameter_Font_L_Bolor);
			GUI_DispStringAt(F_CLED_exe_item_Data[i],LED_titile_x,Disp_Start_Y1+i*Disp_Interval);
			dat = GetChanData(i,0);
			fdat = StepToReal(dat,i);
			prec = get_chan_prec(i);
			Display_Parameter_Pro(fdat,str,prec);
			GUI_SetColor(Parameter_Font_R_Bolor);			
			GUI_SetTextAlign(GUI_TA_RIGHT);			
			GUI_DispStringAt( str, LED_paramter_x-20, Disp_Start_Y1+i*Disp_Interval);
			GUI_SetTextAlign(GUI_TA_LEFT);
			GUI_DispStringAt( cled_unit3[i], LED_paramter_x-20, Disp_Start_Y1+i*Disp_Interval);
		}
	}
}

#if 0
void DrawFLedTable (void){
	UWORD x,y;
	
	float vGina;
	float vMax,vGap,getVolt;
	float iMax,iGap;
	UWORD currStep;
	UWORD i;
	
	UBYTE sDispFlag=0;
	UBYTE v1to8,c1to8;
	UBYTE vTable[4]={8,4,2,1};
	UBYTE vRange ;//= P3k_FLed_Disp.Seq.range/2;
	UBYTE iRange = P3k_FLed_Disp.seq[0].range%2;

	
	iMax = (ptrMODEL_TYPE->CC)[iRange*10].Max;
	if(c1to8>8)c1to8 =8;
	else if(c1to8>4)c1to8 =4;
	else if(c1to8>3)c1to8 =3;
	else if(c1to8>2)c1to8 =2;
	else c1to8 = 1;
	
	drawVITable(5600/v1to8,1530/c1to8,1,1);

	vGina = (ptrMODEL_TYPE->CV)[vRange*3].Resolution/v1to8;
	if(Model_Number==MODEL3031E)	vGina = (ptrMODEL_TYPE->CV)[vRange*3].Resolution*MEASURE_GAIN_3031;
	else						vGina = (ptrMODEL_TYPE->CV)[vRange*3].Resolution*MEASURE_GAIN_3032;	
	vMax = (ptrMODEL_TYPE->CV)[vRange*3].Resolution*(ptrMODEL_TYPE->CV)[vRange*3].Def*MEASURE_GAIN_3032;

	vGap = vMax / 256; //56V / 256 = 0.21875 V
	iGap = iMax/128/c1to8;
	
	for(i=0;i<8192;i++){
		getVolt = i*8*vGina;
///		currStep = P3k_FLed_Disp.Seq[0].viTable[i];
		if (getVolt > vMax){

		}else{
			x = getVolt / vGap;
			y = currStep / iGap;
			draw_point(x,y,MEM_DARKRED_ku);
		}
	}
}
#endif
#if 0
void RedrawFLed(void) {
	//P3k_FLed_Disp.disFlag 
	
	if(P3k_FLed_Disp.disFlag==0){
		RedrawFuncLEDSet();
	}else{	
		DrawFLedTable();
	}
	//draw_line(0,0,180,20,MEM_DARKRED_ku);
	//draw_line(180,20,200,120,MEM_DARKRED_ku);

	//FPGA_W[252] =1;
	
	
}
#endif

#endif


void DispParameter(BYTE cnt)
{
	p3k_send_tx_list tx_data;
	char range;
	double VON_temp1,VON_temp2;
	short VON_rawdata,VON_VOLT_H,VON_VOLT_L;
	P3k_Data_Str	*Data_tmp = &P3k_Chan_Data;
	P3k_Disp_Str	*Disp_tmp = &P3k_Disp_Data;

	if(((DataRedrawFlag & BG_CLEAR)==0)&&((DataRedrawFlag & PARA_CHANGE)==0))
		return;
	if( DataRedrawFlag &BG_CLEAR ) {
		DataRedrawFlag &= (~BG_CLEAR);
		DataRedrawFlag |= BG_CLEAR_FLAG;
		DataRedrawFlag |= PARA_CHANGE;
		if(M_num<=P_CP)
			ClearP3KDataSomeBG(Parameter_Bottom_Bolor);
		else
			ClearP3KDataAllBG(Parameter_Bottom_Bolor);
		Frame_Change();
		last_menu = 0xFF;
		DMA_Update_Flag = 1;
	}

	if(DataRedrawFlag & PARA_CHANGE) {	/* Redraw Data of use VarKnob or First Start */
		DataRedrawFlag &= (~PARA_CHANGE);
		GUI_SetFont(Parameter_Font);
		range = Disp_tmp->VRange;
		range&=0x01;
		VON_VOLT_H = Disp_tmp->CONF.VON_VOLT[1];
		VON_VOLT_L = Disp_tmp->CONF.VON_VOLT[0];

		VON_temp1 = Disp_tmp->CONF.VON_VOLT[range]*(ptrMODEL_TYPE->CONF[range].Resolution);
		range++;
		range&=0x01;
		VON_temp2 = Disp_tmp->CONF.VON_VOLT[range]*(ptrMODEL_TYPE->CONF[range].Resolution);
		if(VON_temp2 > VON_temp1) {
			VON_rawdata = VON_temp1 / ptrMODEL_TYPE->CONF[range].Resolution;
			if(VON_rawdata>ptrMODEL_TYPE->CONF[range].Max)			VON_rawdata = ptrMODEL_TYPE->CONF[range].Max;
			else if(VON_rawdata<ptrMODEL_TYPE->CONF[range].Min)	VON_rawdata = ptrMODEL_TYPE->CONF[range].Min;
			Data_tmp->CONF.VON_VOLT[range] = Disp_tmp->CONF.VON_VOLT[range] = VON_rawdata;
		}

		if((VON_VOLT_H!=Disp_tmp->CONF.VON_VOLT[1])||(VON_VOLT_L != Disp_tmp->CONF.VON_VOLT[0])) {
			tx_data.ADDRH = Machine_Command;
			tx_data.ADDRL = Machine_Von_Voltage;
			SendTXData(&tx_data);
		}
#if Enable_Optim_display
		///FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_S);
		DMA_Update_Flag = 1;
#endif
		switch(M_num) {
		case P_CC:
			RedrawCCModeData();
			break;
		case P_CR:
			RedrawCRModeData();
			break;
		case P_CV:
			RedrawCVModeData();
			break;
		case P_CP:
			RedrawCPModeData();
			break;
		case P_CC_SPEC:
		case P_CR_SPEC:
		case P_CV_SPEC:
		case P_CP_SPEC:
			RedrawSpecData();
			break;
		case P_CONF_PROT:
			RedrawProtectionData();
			break;
		case P_CONF_OTHER:
			RedrawConfigureOther();
			break;
		case P_CONF_KNOB:
			RedrawKnobData();
			break;
		case P_PROG_MAIN:
			RedrawProgMain();
			break;
		case P_PROG_CHAIN:
			RedrawProgChain();
			break;
		case P_FILE_CHAN:
			RedrawFileChan();
			break;
		case P_FILE_MACHINE:
			RedrawFileMachine();
			break;
		case P_CAL_MODE:
			RedrawCalMode();
			break;
		case P_UTIL_MAIN:
			RedrawUtilityMain();
			break;
		case P_UTIL_INTERFACE:
			RedrawInterface();
			break;
#if 0
		case P_UTIL_GPIB:
			RedrawGPIB();
			break;
#endif
		case P_UTIL_T_DATE:
			RedrawDateTime();
			break;
		case P_UTIL_LOAD:
			RedrawAutoLoad();
			break;
		case P_UTIL_OTHER:
			RedrawUtility();
			break;
		case P_UTIL_SYSINFO:
			RedrawSystemInfo();
			break;
		case P_HELP_HELP:
			HelpBrowser(inform_cnt, NewHelpStr);
			inform_cnt=0;
			break;
		case P_PROG_EXECUTE:
			RedrawProgExecute();
			break;
		case P_PROG_Detail:
			RedrawProgDetail();
			MenuRedrawFlag |= MENU_CHANGE; //Adam_Debug
			break;
		case P_LUA_EXECUTE:
			RedrawLuaExecute();
			break;
		case P_FUNC_MAIN:
		case P_FUNC_MAIN_2:		
			RedrawFuncMain();
			break;
		case P_Input_Password:
			RedrawPassword();
			break;
		case P_CONF_Para:
			RedrawSync();
			break;
		case P_Test_Func:
			RedrawTestFunction();
			break;
		case P_Cal_Value:
			RedrawCalValue();
			break;
		case P_CONF_Ext:
			RedrawExtFunction();
			break;
		case P_Seq_FUNC:
			RedrawSeqFunction();
			break;
		case P_Seq_Normal:
			RedrawSeqNormal();
			break;
		case P_Seq_Fast:
			RedrawSeqFast();
			break;
		case P_NSeq_Edit:
			RedrawNSeqEdit();
			break;
		case P_FSeq_Edit:
			RedrawFSeqEdit();
			break;
		case P_NSeq_EXECUTE:
			RedrawNSeqExecute();
			break;
		case P_FSeq_EXECUTE:
			RedrawFSeqExecute();
			break;
		case P_FSeq_Fill:
			RedrawFSeqFill();
			break;
		case P_UTIL_SYSMEMO:
			RedrawSystemMemo();
			break;
		case P_FUNC_POWER:
			RedrawFuncPower();
			break;
#if Enable_OCP_function
		//case P_FUNC_MAIN_2:		
		//	RedrawAppFunction();
		//	break;
		case P_FUNC_OCP:		
			RedrawFuncOCP();
			break;
		case P_FUNC_OCP_EXECUTE:
			RedrawFOcpExecute();
			break;		
#endif		
#if Enable_Battery_Discharge
		case P_FUNC_batt:
			RedrawFuncBatt();
			break;
		case P_FUNC_batt_EXECUTE:
			RedrawFuncBattExecute();
			break;	
#endif			
#if Enable_OPP_function			
		case P_FUNC_OPP:
			RedrawFuncOPP();
			break;
		case P_FUNC_OPP_EXECUTE:
			RedrawFOppExecute();
			break;
#endif			
#if Enable_LED_function
		case P_FUNC_FLED:
			RedrawFLed();
			break;
		case P_FUNC_FLED_EDIT:
			RedrawFLedEdit();
			break;			
		case P_FUNC_FLED_EXECUTE:
			RedrawFLedExecute();
			break;
		case P_FUNC_CLED:
			RedrawCLed();
			break;
		case P_FUNC_CLED_EDIT:
			RedrawCLedEdit();
			break;			
		case P_FUNC_CLED_EXECUTE:
			RedrawCLedExecute();
			break;	
#endif	

		}
		DataRedrawFlag &= (~BG_CLEAR_FLAG + PARA_CHANGE_Fast);
		//DMA_Update_Flag = 1;
#if Enable_Optim_display
		only_text = 0;
		///FIO_ANOM_0311_FLAG_W(PF12,pFIO_FLAG_C);
#else
		DMA_Update_Flag = 1;
#endif
	}
}


