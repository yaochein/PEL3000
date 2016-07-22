#define FM_GLOBALS
#include <includes.h>
#include "keydef.h"
#include "../fs240/fs/device/usb/usb.h"
#include "../guix/bitmap.h"

char FSdev[5]="ram:";
FMvar FM;

FMfilestru FMfile;

WORD PreFMTotalFiles;
WORD WaveFileCount=0;
WORD RecWaveFileCount=0;
WORD RecImageFileCount=0;
WORD ImportPrtFileCount=0;
UWORD Sort_F[FileMax+2];//Record folder and file in order. including full path and root path.

//FS_FILE *myfile;
char mybuffer[150];
char mybuffer1[50];
char FMnowPath[maxdirlen];//Record current path
char FMShowPath[maxdirlen];//The current path for display.
char FMShowSRPath[maxshowsrdir];//The current path for display.
char FMShowfilePath[maxshowfiledir];//The current path for display in file menu.
char FMOperationErrorStr[50];
char FMDeviceErrorStr[50];
char ShowMessage_Delayflag=0;

FS_FILE *myfile;
char SpaceBuf[maxfreelen];
char FileSizeBuf[maxfreelen];

extern char usbstr [20];

//Software Fragements for intergation
char USB_PrintStatus;
char PaletteLayoutBuf;
char USB_Error_Code;
char hintdelay_count;
char printer_link_status;
volatile LONG USBPlugState=0;
UWORD FM_InfoFlag=0;
char USB_Status=USB_NotExist; // 0: USB Not Exist, 1:USB Busy 2:USB Exist
char USB_Status_Display=USB_Busy; // 0: USB Not Exist, 1:USB Busy 2:USB Exist

#define WITH_RAM_DISK    //Kevin Meng 2006.04.03
#define BIG_FILE_TEST    //
#define fmFreeYpos 15	/*Free space 起始 Y座標*/
#define fmDirYpos 20		/*Directory 起始Y座標*/

#define fmXpos 9												/*檔案顯示起始 X座標 */
#define fmDispStartYpos 66										/*檔案顯示起始 Y座標 */
#define FM_TotalLin 6											/* 一頁可 顯示之檔案數目*/
#define fmfiledis 18											/*每個檔案間隔*/
#define fmDispLastYpos fmDispStartYpos+((FM_TotalLin-1)*fmfiledis)	/* 檔案顯示結束 Y 座標 */
UWORD fmYpos=fmDispStartYpos;
WORD FMSelPtrPre=0,MsgDispCount;
extern struct tm CurrentTime, OldTime;

//#define FM_Scroll_Xpos 6
//#define FM_Scroll_Ypos 43
#define FM_Scroll_Xpos 304
#define FM_Scroll_Ypos fmDispStartYpos

void FileUtilDispProc(void);
void DrawRectangle(UWORD startX, UWORD startY, UWORD Lx, UWORD Ly);
void DrawScrBarFrame(UWORD startX, UWORD startY);
void ShowPath(void);
void USB_unplug(void);
void FMShowPathProc(char ,char*);
void PrintFileName(void);
void ShowScrollBar(void);
void ShowMessage(char* STR);
void WriteBMPBuf(ULONG length, BYTE* source);
char* RGB_to_RLE(char *bmp_ptr, char *new_ptr, unsigned int Width, unsigned int Height);
UBYTE ReadAPPLicense(char *FileName);
UBYTE ReadMBRLicense(void);
void CreateAPPLicense(void);
extern BYTE File_Test_FPGA (char *FileName);
extern void ClearScrollBarBG(UWORD c);
extern void ClearPathBG(UWORD c);
extern void ClearMessageBG(UWORD c);
extern void ClearXstFileNameBG(UWORD c,UBYTE X_line);
extern void ClearFileNameBG(UWORD c);
extern int NextFileName(int FileCount, char *FileName, char Mode, char cnt);
extern void RecallFileNameFun(const char *name, char *FileName, char Mode, char cnt);
extern BYTE RecallDataFromFile(char Data_Type,char *FileName);
extern BYTE Upgrading(char source,char *FileName);
extern void Script_Load(UBYTE *Scriptname,char *file_name);
extern void ClearKeyBoard(void);
extern BYTE UpgradingMain(char *FileName);
extern BYTE UpgradingFPGA(char *FileName);
extern void Update_Panel(void);
extern void Debug_printf(char *Message);
extern void SaveCalData_DataFlash(void);
extern UWORD FileUtilRedrawFlag;
void FileUtilDispProc(void)
	{
	if(FileUtilRedrawFlag & FILEUTIL_DISP_INIT)
		{
		FileUtilRedrawFlag&=(~FILEUTIL_DISP_INIT);
		if(FM_InfoFlag&FM_SHOW_INIT)
			{
			FM_InfoFlag&=~FM_SHOW_INIT;
			//GUI_SetFont(&GUI_FontTimesNewRoman17);
			GUI_SetFont(File_Font); 
			ClearP3KDataAllBG(File_Bottom_Bolor);
			ClearP3KChanAllBG(File_Bottom_Bolor);
			DrawRectangle(5,39,310,21);
			DrawRectangle(5,63,310,135);
			//DrawScrBarFrame(305,70);		
			DispScrStartCT=0;
			DispScrEndCT=5;
			}
		if(FM_InfoFlag&FM_SHOW_PATH)
			{
			FM_InfoFlag&=~FM_SHOW_PATH;			
			ShowPath();
			}	
		if(FM_InfoFlag&FM_SHOW_FILE_LIST)
			{
			FM_InfoFlag&=~FM_SHOW_FILE_LIST;			
			PrintFileName();
			}
		if((FM_InfoFlag&FM_SHOW_SCROLL_BAR)||(FM_InfoFlag&FM_SHOW_ALL)||(FM_InfoFlag&FM_CHANGE_PAGE))
			{
			FM_InfoFlag&=~FM_SHOW_SCROLL_BAR;			
			ShowScrollBar();
			}		
		if(FM_InfoFlag&FM_SHOW_ALL)			
			FM_InfoFlag&=~FM_SHOW_ALL;					
		if(FM_InfoFlag&FM_CHANGE_PAGE)			
			FM_InfoFlag&=~FM_CHANGE_PAGE;							
		/* Show Dir & File Name */
		DMA_Update_Flag = 1;
		}

	if(FileUtilRedrawFlag & FILEUTIL_SHOW_DIR){
		FileUtilRedrawFlag&=(~FILEUTIL_SHOW_DIR);
		DMA_Update_Flag = 1;
		}
	if(FileUtilRedrawFlag & FILEUTIL_SHOW_PATH){
		FileUtilRedrawFlag&=(~FILEUTIL_SHOW_PATH);
		ShowPath();
		DMA_Update_Flag = 1;
		}
	if(FileUtilRedrawFlag & FILEUTIL_SHOW_SCR){
		FileUtilRedrawFlag&=(~FILEUTIL_SHOW_SCR);
		DMA_Update_Flag = 1;
		}
	}

void DrawRectangle(UWORD startX,UWORD startY,UWORD Lx,UWORD Ly)
	{
	WORD i;

	GUI_SetBkColor(GW_BLACK);
	GUI_SetColor(GW_WHITE);

	for(i=startY;i<startY+Ly;i++)		/*	left line			*/
		GUI_DrawPixel(startX,i);
	
	for(i=startY;i<startY+Ly;i++)		/*	right line			*/
		GUI_DrawPixel(startX+Lx,i);
	
	for(i=startX;i<startX+Lx+1;i++)		/*	top line			*/
		GUI_DrawPixel(i,startY);
	
	for(i=startX;i<startX+Lx+1;i++)		/*	bottom line		*/
		GUI_DrawPixel(i,startY+Ly);

	for(i=startY+1;i<startY+Ly-1;i++)	/*	right inside line	*/
		GUI_DrawPixel(startX+Lx-1,i);
	
	for(i=startX+1;i<startX+Lx;i++)		/*	bottom inside line	*/
		GUI_DrawPixel(i,startY+Ly-1);

	GUI_SetColor(GW_LIGHTGRAY);

	for(i=startY+1;i<startY+Ly-1;i++)	/*	left inside line		*/
		GUI_DrawPixel(startX+1,i);
	
	for(i=startX+1;i<startX+Lx;i++)		/*	top inside line		*/
		GUI_DrawPixel(i,startY+1);
	}
void DrawScrBarFrame(UWORD startX,UWORD startY)
	{
	int i;
	for(i=startY+1;i<startY+120;i++)
		GUI_DrawPixel(startX,i);
	
	for(i=startY+1;i<startY+120;i++)
		GUI_DrawPixel(startX+6,i);

	for(i=startX+1;i<startX+6;i++)
		GUI_DrawPixel(i,startY);
	
	for(i=startX+1;i<startX+6;i++)
		GUI_DrawPixel(i,startY+120);
	}
static void _log(const char *msg,const char *msg1,BYTE logtype)
	{
	UWORD fmlastpos;

    if(FM.ColDef==1)
		{
		GUI_SetColor(File_Print_Font_Bolor);
		GUI_SetBkColor(File_Select_Bar_Bolor);
		//GUI_GotoXY( fmXpos, fmDispStartYpos);
		GUI_GotoXY( fmXpos, fmYpos);
		GUI_DispChars(' ', 73);
    	}
    else
		{
		GUI_SetBkColor(File_Bottom_Bolor);
		GUI_SetColor(File_Print_Font_Bolor);
    	}
    GUI_SetTextAlign(GUI_TA_LEFT);
    GUI_DispStringAt(msg,fmXpos,fmYpos);
    if(logtype==1)
    	{
    	GUI_SetTextAlign(GUI_TA_RIGHT);
        GUI_DispStringAt(msg1,fmXpos+290,fmYpos);
    	}

    if( (FM.TotalFiles+2)>=FM_TotalLin )	fmlastpos = fmDispLastYpos;
    else									fmlastpos = fmDispStartYpos+((FM.TotalFiles+2)-1)*fmfiledis;
    if(fmYpos>fmlastpos-1)	fmYpos =  fmDispStartYpos;
    else					fmYpos += fmfiledis;
	}
void VarSelect(BYTE cnt)
	{
    if(cnt)
		{
        FM.SelPtr -= cnt;
        if(FM.SelPtr<0)						FM.SelPtr = 0;
        else if(FM.SelPtr>FM.TotalFiles+1)	FM.SelPtr = FM.TotalFiles+1;

        if(FM.SelPtr-FM.DispStartPos>FM_TotalLin-1)	FM.DispStartPos = FM.SelPtr-FM_TotalLin+1;
        else if(FM.SelPtr<FM.DispStartPos)			FM.DispStartPos = FM.SelPtr;

        if(FM.SelPtr!=FMSelPtrPre)
        	{
            FM_InfoFlag|=FM_SHOW_FILE_LIST;//Print file list and redraw scroll bar.
			FileUtilRedrawFlag|=FILEUTIL_DISP_INIT;  
			if(FM.SelPtr<DispScrStartCT)
				{
				DispScrStartCT = FM.SelPtr;
				DispScrEndCT = DispScrStartCT+FM_TotalLin-1;
				FM_InfoFlag |= FM_CHANGE_PAGE;
				}
			if(FM.SelPtr>DispScrEndCT)
				{
				DispScrEndCT = FM.SelPtr;
				DispScrStartCT = DispScrEndCT-FM_TotalLin+1;				
				FM_InfoFlag |= FM_CHANGE_PAGE;
				}
        	}
        
        if(FM_InfoFlag&FM_OPERATION_ERROR_TAG)
			{
            FM_InfoFlag &= ~FM_OPERATION_ERROR_TAG;//Let error message covered by files and folders information.
            FM_InfoFlag |= FM_SHOW_FOLDER_FILE_NUM;
            MsgDispCount = -2;
        	}
        else if(FMinfo&FM_DEL_CONFIRM)//If delete key pressed, but the file selection changed.
        	{
            FMinfo &= ~FM_DEL_CONFIRM;  // => Clear the message and flag. Kevin Meng 2006.04.20
            FM_InfoFlag |= FM_SHOW_FOLDER_FILE_NUM;
            MsgDispCount = -2;
        	}			
		else if(FMinfo&FM_UPG_CONFIRM)//If delete key pressed, but the file selection changed.
        	{
            FMinfo &= ~FM_UPG_CONFIRM;  // => Clear the message and flag. Kevin Meng 2006.04.20
            FM_InfoFlag |= FM_SHOW_FOLDER_FILE_NUM;
            MsgDispCount = -2;
        	}
		else if(FMinfo&FM_MNT_CONFIRM)//If delete key pressed, but the file selection changed.
        	{
            FMinfo &= ~FM_MNT_CONFIRM;  // => Clear the message and flag. Kevin Meng 2006.04.20
            FM_InfoFlag |= FM_SHOW_FOLDER_FILE_NUM;
            MsgDispCount = -2;
        	}
		else if(FMinfo&FM_FPG_CONFIRM)//If delete key pressed, but the file selection changed.
        	{
            FMinfo &= ~FM_FPG_CONFIRM;  // => Clear the message and flag. Kevin Meng 2006.04.20
            FM_InfoFlag |= FM_SHOW_FOLDER_FILE_NUM;
            MsgDispCount = -2;
        	}
		else if(FMinfo&FM_IPC_CONFIRM)//If delete key pressed, but the file selection changed.
        	{
            FMinfo &= ~FM_IPC_CONFIRM;  // => Clear the message and flag. Kevin Meng 2006.04.20
            FM_InfoFlag |= FM_SHOW_FOLDER_FILE_NUM;
            MsgDispCount = -2;
        	}
    	}
	}
void SpaceCal(FP space, char *buf)
	{
    if(space<1000)			sprintf(buf,"%.0fKB",space);
    else if(space<10000)	sprintf(buf,"%.2fMB",space/1000);
    else if(space<100000)	sprintf(buf,"%.1fMB",space/1000);
    else if(space<1000000)	sprintf(buf,"%.0fMB",space/1000);
    else					sprintf(buf,"%.0fGB",space/1000000);
	}
void ShowScrollBar(void)
	{
	UBYTE Ypos,Len;
	UBYTE i,j;

    //Scroll bar clear
    ClearScrollBarBG(Parameter_Bottom_Bolor);
    if((FM.TotalFiles+2)<=FM_TotalLin)
		{
        Ypos=FM_Scroll_Ypos;
		Len=FM_TotalLin*fmfiledis-1;
    	}
    else{
        Ypos=((FM_TotalLin*fmfiledis*FM.DispStartPos)/(FM.TotalFiles+2))+FM_Scroll_Ypos;
        Len=(FM_TotalLin*fmfiledis*FM_TotalLin)/(FM.TotalFiles+2);
    }

    if(!Len)
        Len=1;
		
    //GUI_SetBkColor(GW_BLACK);
    GUI_SetColor(MEM_WHITE);

    if(Ypos>FM_Scroll_Ypos)
		{
        for(i=FM_Scroll_Ypos;i<Ypos;i++)
			for(j=1;j<=7;j++)
				GUI_DrawPixel(FM_Scroll_Xpos+j,i);		

    	}

    if((Ypos+Len)<fmDispLastYpos+fmfiledis-1)
		{
        for(i=Ypos+Len;i<fmDispLastYpos+fmfiledis-1;i++)
			for(j=1;j<=7;j++)
				GUI_DrawPixel(FM_Scroll_Xpos+j,i);		
    	}
	
    //Scroll bar
    //GUI_SetBkColor(GW_BLACK);
    GUI_SetColor(MEM_ORANGE_ku);
	

    for(i=Ypos;i<Len+Ypos;i++)
		for(j=1;j<=7;j++)
			GUI_DrawPixel(FM_Scroll_Xpos+j,i);   	
 	
}
void PrintFileName(void)
{
	WORD times;
	WORD sort;	
	UBYTE Clear_Line=1;
	
	GUI_SetFont(File_Font); 
	fmYpos=fmDispStartYpos;

	if(FM_InfoFlag&FM_SHOW_ALL)
	{
		ClearFileNameBG(File_Bottom_Bolor);

		
		if(ShowMessage_Delayflag==0)
			ClearMessageBG(File_Bottom_Bolor);
	}
    if(FM.DispStartPos<1)
	{
        if(FM.SelPtr==0)
            FM.ColDef=1;
        else
            FM.ColDef=0;
        sprintf(mybuffer,"%s\\",FSdev);
		if((FM.SelPtr==0)||(FMSelPtrPre==0)||(FM_InfoFlag&FM_SHOW_ALL)||(FM_InfoFlag&FM_CHANGE_PAGE))
		{
			ClearXstFileNameBG(File_Bottom_Bolor,Clear_Line++);				
	    	_log(mybuffer,mybuffer,0);
		}
		else
		{
			Clear_Line++;
			fmYpos+=fmfiledis;
		}
    }

    if(FM.DispStartPos<2)
	{
        if(FM.SelPtr==1)
            FM.ColDef=1;
        else
            FM.ColDef=0;
		
		if((FM.SelPtr==1)||(FMSelPtrPre==1)||(FM_InfoFlag&FM_SHOW_ALL)||(FM_InfoFlag&FM_CHANGE_PAGE))
		{
			ClearXstFileNameBG(File_Bottom_Bolor,Clear_Line++);
			_log("..\\",mybuffer,0);
		}
		else
		{
			Clear_Line++;
			fmYpos+=fmfiledis;
		}		
    }
	
    for(times=2;times<FM.TotalFiles+2;times++)
	{
        sort=Sort_F[times];
        if((times>=FM.DispStartPos)&&(times<=FM.DispStartPos+FM_TotalLin-1))
		{
            if(FM.SelPtr==times)
                FM.ColDef=1;
            else
                FM.ColDef=0;
            //check folder or file
            if(FMfile[sort].my_type)
                sprintf(mybuffer,"\x80 ");//folder
            else
                sprintf(mybuffer,"\x81 ");//file

#if 0			 
            //check size
            if(FMfile[sort].my_size==-1)
                sprintf(FileSizeBuf," ");
            else if(FMfile[sort].my_size<1024)
                sprintf(FileSizeBuf,"%dB ",FMfile[sort].my_size);
            else
                SpaceCal((FMfile[sort].my_size)/1024, FileSizeBuf);
#else
			sprintf(FileSizeBuf," ");
#endif			
            sprintf(mybuffer+2, "%-12s  ", 
                      FMfile[sort].my_name);
            sprintf(mybuffer1, "%7s  %02d-%s-%02d  %02d:%02d", 
                      FileSizeBuf, 
                      FMfile[sort].my_day,
                      FMfile[sort].my_month,
                      FMfile[sort].my_year, 
                      FMfile[sort].my_hour, 
                      FMfile[sort].my_min );			
			if((times==FM.SelPtr)||(times==FMSelPtrPre)||(FM_InfoFlag&FM_SHOW_ALL)||(FM_InfoFlag&FM_CHANGE_PAGE))
			{
				ClearXstFileNameBG(File_Bottom_Bolor,Clear_Line++);				
				_log(mybuffer,mybuffer1,1);
			}
			else
			{
				Clear_Line++;
				fmYpos+=fmfiledis;
			}
        }
    }
	FMSelPtrPre=FM.SelPtr;
	sprintf(mybuffer,"%d folder(s) , %d file(s)",FM.FolderVal,FM.FileVal);

	if((FM_InfoFlag&FM_SHOW_ALL)||(FM_InfoFlag&FM_CHANGE_PAGE)||(FM_InfoFlag&FM_SHOW_Message))
	{
		FM_InfoFlag&=(~FM_SHOW_Message);
		if(ShowMessage_Delayflag)
		{
			FM_InfoFlag|=FM_SHOW_Message;
			ShowMessage_Delayflag=0;
		}
		else			
			ShowMessage(mybuffer);
	}
}

void SortFolder(void)
	{
	UWORD i,j=2;
    Sort_F[0]=0;
    Sort_F[1]=1;

    //Tag number for folders display.
    for(i=2;i<FM.TotalFiles+2;i++){
        if(FMfile[i].my_type)
            Sort_F[j++]=i;
    }

    //Tag number for files display.
    for(i=2;i<FM.TotalFiles+2;i++){
        if(!(FMfile[i].my_type))
            Sort_F[j++]=i;
    }
}

void ShowMessage(char* STR)
	{
	char Message_Temp[50];
	ClearMessageBG(File_Bottom_Bolor);
	GUI_SetFont(File_Font);
	GUI_SetBkColor(File_Bottom_Bolor);
	GUI_SetColor(File_Message_Font_Bolor);
	GUI_SetTextAlign(GUI_TA_LEFT);
	sprintf(Message_Temp,STR);
	GUI_DispStringAt(Message_Temp,fmXpos,fmDispLastYpos+fmfiledis);
	DMA_Update_Flag = 1;
	Update_Panel();
	}
void ShowPath(void)
	{
	GUI_SetFont(File_Font); 
	ClearPathBG(File_Bottom_Bolor);
	GUI_SetColor(File_Path_Font_Bolor);
	GUI_SetBkColor(File_Bottom_Bolor);
	GUI_SetTextAlign(GUI_TA_LEFT); 
	GUI_DispStringAt("Path:",9,41);
	GUI_DispStringAt(FMShowPath,50,41);
	}
static char *month_name[]={ "???", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
#pragma optimize_off
void GetDirInformation(const char *name) 
	{
	FS_DIR *dirp;
	struct FS_DIRENT *direntp;
	WORD times=0;
	UBYTE Attr;
	UBYTE len;
	FS_U32   timestamp;
	FS_FILETIME  filetime;

	FMShowPathProc(maxshowdir, FMShowPath);
	FMShowPathProc(maxshowsrdir, FMShowSRPath);
	FMShowPathProc(maxshowfiledir, FMShowfilePath);
	dirp = FS_OpenDir(name);
    if(dirp)
		{
        times=2;
        FM.FolderVal=0;
        FM.FileVal=0;
        do
			{
            direntp=FS_ReadDir(dirp);
            if(direntp){
                if((direntp->DirName[0])=='.')
                    continue;

                if(times==FileMax+2){
                    sprintf(FMOperationErrorStr,"The number of files is over %d(Max)!!",FileMax);
					ShowMessage(FMOperationErrorStr);
					ShowMessage_Delayflag=1;
                    FM_InfoFlag|=(FM_SHOW_OPERATION_ERROR+FM_OPERATION_ERROR_TAG);
                    break;
                }

                FS_DirEnt2Attr(direntp, &Attr);
                if ((Attr & FS_ATTR_DIRECTORY)){
                    FMfile[times].my_type=1;//folder
                    FMfile[times].my_size=-1;
                    FM.FolderVal++;
                }
                else{
                    FMfile[times].my_type=0;//file
                    FMfile[times].my_size=direntp->Size;
                    FM.FileVal++;
                }

                FS_TimeStampToFileTime(FS_DirEnt2Time(direntp),&filetime); 

                sprintf(FMfile[times].my_name,direntp->DirName);
                FMfile[times].my_year=(filetime.Year%100);
                filetime.Month=filetime.Month>12 ? 12 :filetime.Month;
                sprintf(FMfile[times].my_month,month_name[filetime.Month]);
                FMfile[times].my_day=filetime.Day;
                filetime.Hour=filetime.Hour>59 ? 0 :filetime.Hour;
                FMfile[times].my_hour=filetime.Hour;
                FMfile[times].my_min=filetime.Minute;

                times++;
            }
		} while (direntp);
        FS_CloseDir(dirp);
        FM.TotalFiles=FM.FolderVal+FM.FileVal;
        PreFMTotalFiles=FM.TotalFiles; //ul
        RecNSeqFileCount = RecFSeqFileCount = RecSEQFileCount = RecPresetFileCount = RecMemoryFileCount = RecSetupFileCount = FM.TotalFiles; //ul
        
        SortFolder();//Tag number for folders and files display.
        FM_InfoFlag|=(FM_SHOW_FILE_LIST+FM_SHOW_SCROLL_BAR);//Print file list and redraw scroll bar.
        //SetupFileCount=0;
        if(p3k_File_Utility_BAR.USB_Data_Type==F_Setup_Data)
        	{
        	SavSetupFileCount=NextFileName(SavSetupFileCount,SaveFileName,Sav_Set,0);
			RecallFileNameFun(FMnowPath, RecallFileName, Sav_Set, 0);
        	}
		else if(p3k_File_Utility_BAR.USB_Data_Type==F_Memory_Data)
			{
        	SavMemoryFileCount=NextFileName(SavMemoryFileCount,SaveFileName,Sav_Memory,0);		
			RecallFileNameFun(FMnowPath, RecallFileName, Sav_Memory, 0);
			}	
		else if(p3k_File_Utility_BAR.USB_Data_Type==F_Preset_Data)
			{
        	SavPresetFileCount=NextFileName(SavPresetFileCount,SaveFileName,Sav_Preset,0);
			RecallFileNameFun(FMnowPath, RecallFileName, Sav_Preset, 0);
			}
		else if(p3k_File_Utility_BAR.USB_Data_Type==F_NSeq_Data)
			{
        	SavNSeqFileCount = NextFileName(SavNSeqFileCount,SaveFileName,Sav_NSeq,0);		
			RecallFileNameFun(FMnowPath, RecallFileName, Sav_NSeq, 0);
			}
		else if(p3k_File_Utility_BAR.USB_Data_Type==F_FSeq_Data)
			{
        	SavFSeqFileCount = NextFileName(SavFSeqFileCount,SaveFileName,Sav_FSeq,0);		
			RecallFileNameFun(FMnowPath, RecallFileName, Sav_FSeq, 0);
			}
		
		ResultFileCount = NextFileName(ResultFileCount,SaveResultFileName,Sav_Result,0);	
		
		if((M_num==P_FILE_CHAN)&&(F_Media_USB==p3k_File_Utility_BAR.MEDIA)&&(!Upgrading_Flag))
			{
			Freeze_Keyboard=1;	
			DispMode =DispMode_SELECT_CH;
			DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
			}
		}
    else{
		Save_Recall_InfoFlag|=Data_Process+Device_Error;
		if(M_num==P_FILE_CHAN)
			{
			DispMode =DispMode_SELECT_CH;
			DataRedrawFlag |= BG_CLEAR + PARA_CHANGE;
			}
#if Normal_TEST		
		printf("Unable to open directory!!\n");
#endif
        //sprintf(FMOperationErrorStr,"Unable to open directory!!");
		//ShowMessage(FMOperationErrorStr);
		//ShowMessage_Delayflag=1;
        //FM_InfoFlag|=(FM_SHOW_OPERATION_ERROR+FM_OPERATION_ERROR_TAG);//???
        len=strlen(FMnowPath);
        if(len!=4){//Root selected, do nothing.
	        while(*(FMnowPath+len+1)!=0x5C){ /* '\' */
	            *(FMnowPath+len+1)=0x00;
	            len--;
	        }
	        *(FMnowPath+len+1)=0x00;
    	  }
        if(len>maxshowdir){//The path name is too long.
               sprintf(FMShowPath,"...%s",FMShowPath+(len-maxshowdir));
        }
        else
               sprintf(FMShowPath,FMnowPath);
		
        //FM_InfoFlag|=(FM_SHOW_FILE_LIST+FM_SHOW_SCROLL_BAR);//Print file list and redraw scroll bar.
        //_error("Unable to open directory\n");
    }
}
void FM_MainTask(void)
	{
	if(USBPlugState==1)
		{
		//close RAM disk.
		//If program come here, it means USB flash disk was pluged in.
		FMinfo=0;
		FM_InfoFlag=0;
		Save_Recall_InfoFlag=0;
		sprintf(FSdev,"usb:");
		sprintf(FMnowPath,FSdev);
		FMinfo|=FM_PLUGIN_READ;	
		}
	else if(USBPlugState==2)
		{
		//If program come here, it means USB flash disk was unpluged.
		FMinfo=0;
		FM_InfoFlag=0;
		USB_unplug();
	
		USB_Status=USB_NotExist;
		Go_NG_Save_Status=0;
		if(F_Media_USB==p3k_File_Utility_BAR.MEDIA)/* Media = USB	*/	
			{
			USB_Status_Display=USB_NotExist;
			Save_Status	= 0;
			Recall_Status	= 0;
			}
		else
			USB_Status_Display=USB_Busy;
		USBPlugState=0;
		}	
	if(FMinfo&FM_RENAME)     //Rename a file or folder.
		{
		if(FS_Rename(mybuffer,(char *)KeypadSTR)==(-1))
			{
		    sprintf(FMOperationErrorStr,"Rename error!!");
			ShowMessage(FMOperationErrorStr);
			ShowMessage_Delayflag=1;
		    FM_InfoFlag|=(FM_SHOW_OPERATION_ERROR+FM_OPERATION_ERROR_TAG);
		    MsgDispCount=-1;
			}
		FMinfo&=~FM_RENAME;
		}
	else if(FMinfo&FM_RMDIR) //Delete a folder.
		{
		if(FS_RmDir(mybuffer)==(-1))
			{
		    sprintf(FMOperationErrorStr,"Error!!This folder may be not empty!!");
			ShowMessage(FMOperationErrorStr);
			ShowMessage_Delayflag=1;
		    FM_InfoFlag|=(FM_SHOW_OPERATION_ERROR+FM_OPERATION_ERROR_TAG);
		    MsgDispCount=-1;
			}
		else
			sprintf(FMOperationErrorStr,"Reading....");
		ShowMessage(FMOperationErrorStr);			
		FMinfo&=~FM_RMDIR;
		}
	else if(FMinfo&FM_REMOVE)//Delete a file.
		{
		if(FS_Remove(mybuffer)==(-1))
			{
		    sprintf(FMOperationErrorStr,"Remove file error!!");
			ShowMessage(FMOperationErrorStr);
			ShowMessage_Delayflag=1;
		    FM_InfoFlag|=(FM_SHOW_OPERATION_ERROR+FM_OPERATION_ERROR_TAG);//???
		    MsgDispCount=-1;
			}
		else
			sprintf(FMOperationErrorStr,"Reading.....");
		ShowMessage(FMOperationErrorStr);
		FMinfo&=~FM_REMOVE;
		}	
	else if(FMinfo&FM_MKDIR) //Create a folder.
		{
		if((FS_MkDir(mybuffer))==(-1))
			{
		    sprintf(FMOperationErrorStr,"Create a directory error!!");
			ShowMessage(FMOperationErrorStr);	
			ShowMessage_Delayflag=1;
		    FM_InfoFlag|=(FM_SHOW_OPERATION_ERROR+FM_OPERATION_ERROR_TAG);
		    MsgDispCount=-1;
			}
		FMinfo&=~FM_MKDIR;
		}	
	else if(FMinfo&FM_PLUGIN_READ)
		{
		GetDirInformation(FMnowPath);
//		FM_InfoFlag=0;//only read,do not display.
		if(!(Save_Recall_InfoFlag&Device_Error))
			{
			USB_Status=USB_Exist;
			Go_NG_Save_Status=1;
			if(F_Media_USB==p3k_File_Utility_BAR.MEDIA)/* Media = USB	*/
				{
				USB_Status_Display=USB_Exist;
				Save_Status	= 1;	
				Recall_Status	= 1;
				}
			else
				USB_Status_Display=USB_Busy;
			if((M_num==P_FILE_CHAN)&&(F_Media_USB==p3k_File_Utility_BAR.MEDIA))
				{
				Soft_Key_Temp=0;
				MenuRedrawFlag|=MENU_CHANGE;
				}
			}		
		USBPlugState=0;				
		FMinfo&=(~FM_PLUGIN_READ);	
		}	
	//read device again (change directory , delete) 
	else if(FMinfo&FM_READ_DEVICE)
		{
		FM.SelPtr=0;
		FM.DispStartPos=0;
		DispScrStartCT=0;
		DispScrEndCT=5;		
		MsgDispCount=-1;	
		if(FM.SelPtr-FM.DispStartPos>FM_TotalLin-1)
			{
			FM.DispStartPos=FM.SelPtr-FM_TotalLin+1;
			}
		else if(FM.SelPtr<FM.DispStartPos)
			{
			FM.DispStartPos=FM.SelPtr;
			}
		GetDirInformation(FMnowPath);
		if(M_num==P_UTIL_FILE)
			{
			FM_InfoFlag|=FM_SHOW_FILE_LIST+FM_SHOW_PATH+FM_SHOW_ALL;//Print file list and redraw scroll bar.
			FileUtilRedrawFlag|=FILEUTIL_DISP_INIT;		
			}
		FMinfo&=(~FM_READ_DEVICE);
		}
	}
BYTE ExamineFMfileExtension(UWORD fmsel)
	{
	UBYTE len;
    char str[20];

    len=strlen(FMfile[fmsel].my_name);
	sprintf(str,FMfile[fmsel].my_name+len-4);
	if(strcmp(str,".LUA")==0)		return 4; 
	else if(strcmp(str,".UPG")==0)	return 5;
	else if(strcmp(str,".IPC")==0)	return 6;
	else if(strcmp(str,".MNT")==0)	return 7;
	else if(strcmp(str,".FPG")==0)	return 8;
	else if(strcmp(str,".CAL")==0)	return 9;
	else if(strcmp(str,".UP2")==0)	return 10;
	else if(strcmp(str,".CSV")==0)	return 12;
	else if(strcmp(str,".LIS")==0)	return 15;
	else if(strcmp(str,".LIC")==0)	return 16;
	else
		{
		sprintf(str,FMfile[fmsel].my_name+len-2);	
		if(strcmp(str,".P")==0)			return 1;	/*Preset*/
		else if(strcmp(str,".M")==0)	return 2;	/*Prog Memory*/
		else if(strcmp(str,".S")==0)	return 3;	/*Setep*/
		else if(strcmp(str,".A")==0)	return 11;	/*Seq*/
		else if(strcmp(str,".F")==0)	return 13;	/*FSeq*/
		else if(strcmp(str,".N")==0)	return 14;	/*NSeq*/
		else							return 0;
		}
	}
/****************************************************
    this function is used to comparsion the IPC file name 
    with the OEM name.
        correct :return 0
        incorrect: return 1

    ex: if OEM is GW,the correct bootlogo file should be GW.IPC         
****************************************************/
int ComparsionIPCName(UWORD fmsel)
{  char str[20];	  
//    sprintf(str,"%s.IPC",System[FactorySet.GDS_OEMNum].Logo);  /*add .IPC in the end of "System[FactorySet.GDS_OEMNum].Logo"*/
    if(strcmp(str,FMfile[fmsel].my_name)!=0)   /*comparison the file name*/	 		 
	 return 0;    /*file name != OEM name return 0 */     
    else
        return 1;    /*file name = OEM name ,return 1*/ 		
}
char Select_FileName[30];
BYTE FMselect(BYTE n1, BYTE n2)
	{
	UBYTE len,err,File_Type;
	char status,str[150],Recall_result;
	//char Select_FileName[30];

	if(FMinfo&FM_READ_DEVICE)//avoid entering too fast
	return(0);

    /*USB:/	ROOT*/
    if(FM.SelPtr==0)
		{
		MenuRedrawFlag |= MENU_CHANGE;	
        if(FM_InfoFlag&FM_OPERATION_ERROR_TAG)
			{
            FM_InfoFlag&=~FM_OPERATION_ERROR_TAG;//Let error message covered by files and folders information.
            FM_InfoFlag|=FM_SHOW_FOLDER_FILE_NUM;
            MsgDispCount=-2;
        	}
        len=strlen(FMnowPath);
        if(len==4)//Root selected, do nothing.
            return(0);
        
        sprintf(FMnowPath,FSdev);
        if(FM_InfoFlag&FM_OPERATION_ERROR_TAG)
			{
            FM_InfoFlag&=~FM_OPERATION_ERROR_TAG;//Let error message covered by files and folders information.
            FM_InfoFlag|=FM_SHOW_FOLDER_FILE_NUM;
            MsgDispCount=-2;
        	}
        FMinfo|=FM_READ_DEVICE;
    	}
    /*../     UPPER*/
    else if(FM.SelPtr==1)
		{
		MenuRedrawFlag |= MENU_CHANGE;	
        if(FM_InfoFlag&FM_OPERATION_ERROR_TAG)
			{
            FM_InfoFlag&=~FM_OPERATION_ERROR_TAG;//Let error message covered by files and folders information.
            FM_InfoFlag|=FM_SHOW_FOLDER_FILE_NUM;
            MsgDispCount=-2;
            //Prevent message cleared by HintDelay().   Kevin Meng 2006.03.31
        	}
        len=strlen(FMnowPath);
        if(len==4)//Root selected, do nothing.
            return(0);
        
        while(*(FMnowPath+len+1)!=0x5C) /* '\' */
			{
            *(FMnowPath+len+1)=0x00;
            len--;
        	}
        *(FMnowPath+len+1)=0x00;
        FMinfo|=FM_READ_DEVICE;
		}
    else  /*folder or file*/	
		{
		MenuRedrawFlag |= MENU_CHANGE;	
        if ((FMfile[Sort_F[FM.SelPtr]].my_type)&&(FM.SelPtr>1))  /*selected is a folder*/
			{
            sprintf(mybuffer,"%s\x5C%s",FMnowPath,FMfile[Sort_F[FM.SelPtr]].my_name);
            sprintf(FMnowPath,mybuffer);
            FMinfo|=FM_READ_DEVICE;
        	}			
		 else /*selected is a file*/
		 	{ 
		 	File_Type=ExamineFMfileExtension(Sort_F[FM.SelPtr]);/*examine the file extension*/ 
			switch(File_Type)
				{
				case 1:  /*selected file is .P*/
#if Normal_TEST
					printf("Recall %s\n",FMfile[Sort_F[FM.SelPtr]].my_name);
#endif
					sprintf(mybuffer,"Recall %s ...",FMfile[Sort_F[FM.SelPtr]].my_name);
					ShowMessage(mybuffer);

					Recall_result = RecallDataFromFile(Recall_DataType_Preset,FMfile[Sort_F[FM.SelPtr]].my_name);
						 if(Recall_result==Recall_Complete)			sprintf(mybuffer,"Recall complete");
					else if(Recall_result==Machine_Type_Error)		sprintf(mybuffer,"Machine Type Error");
					else if(Recall_result==Memory_Version_Error)	sprintf(mybuffer,"Memory Version Error");
					else											sprintf(mybuffer,"Recall Failed");
					ShowMessage(mybuffer);
					FM_InfoFlag|=FM_SHOW_Message;						
					break;
				case 2:  /*selected file is .M*/						
#if Normal_TEST
					printf("Recall %s\n",FMfile[Sort_F[FM.SelPtr]].my_name);
#endif
					sprintf(mybuffer,"Recall %s ...",FMfile[Sort_F[FM.SelPtr]].my_name);
					ShowMessage(mybuffer);

					Recall_result = RecallDataFromFile(Recall_DataType_Prog,FMfile[Sort_F[FM.SelPtr]].my_name);
						 if(Recall_result==Recall_Complete)			sprintf(mybuffer,"Recall complete");
					else if(Recall_result==Machine_Type_Error)		sprintf(mybuffer,"Machine Type Error");
					else if(Recall_result==Memory_Version_Error)	sprintf(mybuffer,"Memory Version Error");
					else											sprintf(mybuffer,"Recall Failed");
					ShowMessage(mybuffer);
					FM_InfoFlag|=FM_SHOW_Message;
					break;
				case 3:  /*selected file is .S*/
					sprintf(str,"Recall %s\n",FMfile[Sort_F[FM.SelPtr]].my_name);
					Debug_printf(str);
					
					sprintf(mybuffer,"Recall %s ...",FMfile[Sort_F[FM.SelPtr]].my_name);
					ShowMessage(mybuffer);

					Recall_result = RecallDataFromFile(Recall_DataType_Setup,FMfile[Sort_F[FM.SelPtr]].my_name);
						 if(Recall_result==Recall_Complete)			sprintf(mybuffer,"Recall complete");
					else if(Recall_result==Machine_Type_Error)		sprintf(mybuffer,"Machine Type Error");
					else if(Recall_result==Memory_Version_Error)	sprintf(mybuffer,"Memory Version Error");
					else											sprintf(mybuffer,"Recall Failed");
					ShowMessage(mybuffer);
					FM_InfoFlag|=FM_SHOW_Message;
					break;
				case 4:   /*selected file is .LUA*/
					sprintf(usbstr, "%s\x5C%s", FMnowPath,FMfile[Sort_F[FM.SelPtr]].my_name);
					Script_Load((UBYTE *)usbstr,FMfile[Sort_F[FM.SelPtr]].my_name);
					break;	
#if 0
				case 5:			/*selected file is .UPG*/
					if(FMinfo&FM_UPG_CONFIRM)
						{
						Upgrading_Flag=1;
						Recall_result=Upgrading(0,FMfile[Sort_F[FM.SelPtr]].my_name);
						if(!Recall_result)
							{
							ClearKeyBoard();
							Upgrading_Flag=0;
							}
						FMinfo&=(~FM_UPG_CONFIRM);
						FM_InfoFlag|=FM_SHOW_Message;
						}
					else
						{
						sprintf(mybuffer,"Warning!Press F1 again will do Upgrading!\n");
						ShowMessage(mybuffer);						
						FMinfo|=FM_UPG_CONFIRM;
						} 
					break;
#else
				case 5:			/*selected file is .UPG*/
					if(FMinfo&FM_UPG_CONFIRM)
						{
						System_Ready		= 0;	/*Stop Communication with Slave*/
						Upgrading_Flag		= 1;
						Recall_result	= UpgradingMain(FMfile[Sort_F[FM.SelPtr]].my_name);
						if(!Recall_result)
							{
							ClearKeyBoard();
							Upgrading_Flag = 0;
							}
						FMinfo		&= (~FM_UPG_CONFIRM);
						FM_InfoFlag 	|= FM_SHOW_Message;
						}
					else
						{
						sprintf(mybuffer,"Warning!Press F1 again will do Upgrading!\n");
						ShowMessage(mybuffer);						
						FMinfo |= FM_UPG_CONFIRM;
						}
					break;
#endif					
				case 6:			/*selected file is .IPC*/
					if(FMinfo&FM_IPC_CONFIRM)
						{	
						System_Ready=0;	/*Stop Communication with Slave*/
						Upgrading_Flag=1;
						Recall_result=Upgrading(1,FMfile[Sort_F[FM.SelPtr]].my_name);
						if(!Recall_result)
							{
							ClearKeyBoard();
							Upgrading_Flag=0;
							}
						FMinfo&=(~FM_IPC_CONFIRM);
						FM_InfoFlag|=FM_SHOW_Message;
						}
					else
						{
						sprintf(mybuffer,"Warning!Press F1 again will do Upgrading!\n");
						ShowMessage(mybuffer);						
						FMinfo|=FM_IPC_CONFIRM;
						} 
					break;
				case 7:			/*selected file is .MNT*/
					if(FMinfo&FM_MNT_CONFIRM)
						{		
						System_Ready=0;	/*Stop Communication with Slave*/
						Upgrading_Flag=1;
						Recall_result=Upgrading(2,FMfile[Sort_F[FM.SelPtr]].my_name);
						if(!Recall_result)
							{
							ClearKeyBoard();
							Upgrading_Flag=0;
							}
						FMinfo&=(~FM_MNT_CONFIRM);
						FM_InfoFlag|=FM_SHOW_Message;
						}
					else
						{
						sprintf(mybuffer,"Warning!Press F1 again will do Upgrading!\n");
						ShowMessage(mybuffer);						
						FMinfo|=FM_MNT_CONFIRM;
						} 
					break;
				case 8:			/*selected file is .FPG*/
					if(FMinfo&FM_FPG_CONFIRM)
						{			
						System_Ready=0;	/*Stop Communication with Slave*/
						Upgrading_Flag=1;
						Recall_result=Upgrading(3,FMfile[Sort_F[FM.SelPtr]].my_name);
						if(!Recall_result)
							{
							ClearKeyBoard();
							Upgrading_Flag=0;
							}
						FMinfo&=(~FM_FPG_CONFIRM);
						FM_InfoFlag|=FM_SHOW_Message;
						}
					else
						{
						sprintf(mybuffer,"Warning!Press F1 again will do Upgrading!\n");
						ShowMessage(mybuffer);						
						FMinfo|=FM_FPG_CONFIRM;
						} 
					break;
				case 9:			/*selected file is .SDA*/
					//if(debug_pass_flag==0)return 0;
						sprintf(str,"Recall %s\n",FMfile[Sort_F[FM.SelPtr]].my_name);
						Debug_printf(str);

						sprintf(mybuffer,"Recall %s ...",FMfile[Sort_F[FM.SelPtr]].my_name);
						ShowMessage(mybuffer);

						Recall_result = RecallDataFromFile(Recall_DataType_Cal,FMfile[Sort_F[FM.SelPtr]].my_name);
						if(Recall_result==Recall_Complete) {
							sprintf(mybuffer,"Recall complete");
							SaveCalData_DataFlash();//Rem_Save_Cal_Data();
						} else if(Recall_result==Machine_Type_Error)		sprintf(mybuffer,"Machine Type Error");
						else if(Recall_result==Memory_Version_Error)	sprintf(mybuffer,"Memory Version Error");
						else											sprintf(mybuffer,"Recall Failed");
						ShowMessage(mybuffer);
						FM_InfoFlag |= FM_SHOW_Message;
						break;
				case 10:			/*selected file is .UP2*/
					if(FMinfo&FM_UPG_CONFIRM)
						{
						System_Ready	= 0;	/*Stop Communication with Slave*/
						Upgrading_Flag	= 1;
						Recall_result = Upgrading(0,FMfile[Sort_F[FM.SelPtr]].my_name);
						if(!Recall_result)
							{
							ClearKeyBoard();
							Upgrading_Flag=0;
							}
						FMinfo &= (~FM_UPG_CONFIRM);
						FM_InfoFlag |= FM_SHOW_Message;
						}
					else
						{
						sprintf(mybuffer,"Warning!Press F1 again will do Upgrading!\n");
						ShowMessage(mybuffer);
						FMinfo|=FM_UPG_CONFIRM;
						}
					break;
				case 11:  /*selected file is .A*/
					break;
				case 12:  /*selected file is .CSV*/
					sprintf(str,"Recall %s\n",FMfile[Sort_F[FM.SelPtr]].my_name);
					Debug_printf(str);
					sprintf(mybuffer,"Recall %s ...",FMfile[Sort_F[FM.SelPtr]].my_name);
					ShowMessage(mybuffer);
#if 0
					Recall_result=UpgradingFPGA(FMfile[Sort_F[FM.SelPtr]].my_name);
					if(Recall_result)
						sprintf(mybuffer,"Recall complete");
					else
						{
						OSTimeDly(1000);
						sprintf(mybuffer,"Recall Failed");
						}
					

#else
					Recall_result=File_Test_FPGA(FMfile[Sort_F[FM.SelPtr]].my_name);
					if(Recall_result)
						{
						Debug_printf("Send To FPGA Command And Data ok\n");
						sprintf(mybuffer,"Send Data complete");
						}
					else
						{
						Debug_printf("Send To FPGA Command And Data Failed\n");
						sprintf(mybuffer,"Read Data Failed");
						}
#endif					
					ShowMessage(mybuffer);
					FM_InfoFlag|=FM_SHOW_Message;
					break;
				case 13:  /*selected file is .F*/	/*Fseq*/
					sprintf(str,"Recall %s\n",FMfile[Sort_F[FM.SelPtr]].my_name);
					Debug_printf(str);
					
					sprintf(mybuffer,"Recall %s ...",FMfile[Sort_F[FM.SelPtr]].my_name);
					ShowMessage(mybuffer);

					Recall_result = RecallDataFromFile(Recall_DataType_FSEQ,FMfile[Sort_F[FM.SelPtr]].my_name);
						 if(Recall_result==Recall_Complete)			sprintf(mybuffer,"Recall complete");
					else if(Recall_result==Machine_Type_Error)		sprintf(mybuffer,"Machine Type Error");
					else if(Recall_result==Memory_Version_Error)	sprintf(mybuffer,"Memory Version Error");
					else											sprintf(mybuffer,"Recall Failed");
					ShowMessage(mybuffer);
					FM_InfoFlag |= FM_SHOW_Message;
					break;
				case 14:  /*selected file is .N*/	/*Nseq*/
					sprintf(str,"Recall %s\n",FMfile[Sort_F[FM.SelPtr]].my_name);
					Debug_printf(str);
					
					sprintf(mybuffer,"Recall %s ...",FMfile[Sort_F[FM.SelPtr]].my_name);
					ShowMessage(mybuffer);

					Recall_result = RecallDataFromFile(Recall_DataType_NSEQ,FMfile[Sort_F[FM.SelPtr]].my_name);
						 if(Recall_result==Recall_Complete)			sprintf(mybuffer,"Recall complete");
					else if(Recall_result==Machine_Type_Error)		sprintf(mybuffer,"Machine Type Error");
					else if(Recall_result==Memory_Version_Error)	sprintf(mybuffer,"Memory Version Error");
					else											sprintf(mybuffer,"Recall Failed");
					ShowMessage(mybuffer);
					FM_InfoFlag |= FM_SHOW_Message;
					break;
				case 15:  /*selected file is .LIS */	/*License for File */					
					sprintf(mybuffer,"Read %s ...",FMfile[Sort_F[FM.SelPtr]].my_name);
					ShowMessage(mybuffer);
					//Debug_printf(mybuffer);

					Recall_result = ReadAPPLicense(FMfile[Sort_F[FM.SelPtr]].my_name);
					if(Recall_result==Recall_Complete)	sprintf(mybuffer,"Recall complete");
					else								sprintf(mybuffer,"Recall Failed");
					ShowMessage(mybuffer);
					FM_InfoFlag |= FM_SHOW_Message;
					break;
				case 16:  /*selected file is .LIC */	/*License for USB MBR */
					sprintf(str,"Read %s ...",FMfile[Sort_F[FM.SelPtr]].my_name);
					ShowMessage(str);
					//Debug_printf(mybuffer);

					Recall_result = ReadMBRLicense();
					if(Recall_result==Recall_Complete)	sprintf(str,"Recall complete");
					else								sprintf(str,"Recall Failed");
					ShowMessage(str);
					FM_InfoFlag |= FM_SHOW_Message;
					break;
				default:			/*Selected file is not support*/
					break;
				}
		 	}	 
    	}	 		
    return(0);
	}
BYTE FMdelete(BYTE n1, BYTE n2)
{
UBYTE err;
	MenuRedrawFlag |= MENU_CHANGE;	
    if(FM.SelPtr>1){		
        if(FMinfo&FM_DEL_CONFIRM){
            MsgDispCount=-1;//Prevent message cleared by HintDelay().   Kevin Meng 2006.03.31			
            
			sprintf(mybuffer,"Deleting.....");
			ShowMessage(mybuffer);			
            sprintf(mybuffer,"%s\x5C%s",FMnowPath,FMfile[Sort_F[FM.SelPtr]].my_name);
            if(FMfile[Sort_F[FM.SelPtr]].my_type)
                FMinfo|=FM_RMDIR;  //Delete a folder.
            else
                FMinfo|=FM_REMOVE; //Delete a file.
            FMinfo|=FM_READ_DEVICE;
            FMinfo&=(~FM_DEL_CONFIRM);
        }
        else{
            sprintf(mybuffer,"Press F4 again to confirm this process.");
			ShowMessage(mybuffer);		
            MsgDispCount=-1;//Prevent message cleared by HintDelay().   Kevin Meng 2006.03.31
            FMinfo|=FM_DEL_CONFIRM;
        }
    }
    else if(FM_InfoFlag&FM_OPERATION_ERROR_TAG){
        FM_InfoFlag&=~FM_OPERATION_ERROR_TAG;//Let error message covered by files and folders information.
        FM_InfoFlag|=FM_SHOW_FOLDER_FILE_NUM;
        MsgDispCount=-2;
    }
    return(0);
}
int FMrename(void)
{
BYTE i,j,k;

    if(FM.SelPtr>1){
        //A folder
        if (FMfile[Sort_F[FM.SelPtr]].my_type){
            sprintf((char*)KeypadSTR,FMfile[Sort_F[FM.SelPtr]].my_name);
            for(j=0;j<4;j++)
                *(KeypadSubSTR+j)=0x00;
        }
        //A file
        else{
            for(i=0;i<9;i++){//MK V1.03
                if(*(FMfile[Sort_F[FM.SelPtr]].my_name+i)!='.')
                    *(KeypadSTR+i)=(UBYTE)*(FMfile[Sort_F[FM.SelPtr]].my_name+i);
                else{
                    for(k=i;k<13;k++)
                        *(KeypadSTR+k)=0;
                    break;
                }
            }
            for(j=0;j<4;j++,i++)
                *(KeypadSubSTR+j)=(UBYTE)*(FMfile[Sort_F[FM.SelPtr]].my_name+i);

        }

//        FMinfo&=(~FM_DEL_CONFIRM);
        return 0;
    }
    else{
        if(FM_InfoFlag&FM_OPERATION_ERROR_TAG){
            FM_InfoFlag&=~FM_OPERATION_ERROR_TAG;//Let error message covered by files and folders information.
            FM_InfoFlag|=FM_SHOW_FOLDER_FILE_NUM;
            MsgDispCount=-2;
        }
        return(-1);
    }
}
BYTE KeyPadSave(BYTE n1, BYTE n2)
	{
	UBYTE str,*Memo_Ptr,i;
	if((K_M_num==P_Seq_Normal)||(K_M_num==P_Seq_Fast)||(K_M_num==P_FUNC_FLED)||(K_M_num==P_FUNC_CLED) )
		{
		Soft_Key_Temp = 0;
		M_num = K_M_num;
		MenuRedrawFlag |= MENU_CHANGE;
		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
		if(K_M_num==P_Seq_Normal)		Memo_Ptr = &P3k_NSeq_Disp.NSeq_Seq[P3k_NSeq_Disp.NSeq_Number].NSeq_Memo[0];
		else if(K_M_num==P_Seq_Fast)		Memo_Ptr = &P3k_FSeq_Disp.FSeq_Memo[0];
#if Enable_LED_function
		else if(K_M_num==P_FUNC_FLED){ 
			Memo_Ptr = &P3k_FLed_Disp.seq[P3k_FLed_Disp.currTemp].name[0];
			DispMode = DispMode_BROWSE_ITEMS;
			DataRedrawFlag |= BG_CLEAR_FLAG;
		}else if(K_M_num==P_FUNC_CLED){ 
			Memo_Ptr = &P3k_CLed_Disp.seq[P3k_CLed_Disp.currTemp].name[0];	
			DispMode = DispMode_BROWSE_ITEMS;
			DataRedrawFlag |= BG_CLEAR_FLAG;
		}
#endif
		for(i=0 ; i<12 ; i++)
			*(Memo_Ptr++) = KeypadSTR[i];
		*(Memo_Ptr) = 0;
		for(i=0 ; i<13 ; i++)
			KeypadSTR[i] = 0;
		return(0);
		}

	if(KeypadSTR[0]==0x00)
		return(0);

	Soft_Key_Temp = 0;
	M_num = P_UTIL_FILE;
	MenuRedrawFlag |= MENU_CHANGE;
	//clear ' '
	str = (UBYTE)strlen((char *)KeypadSTR);
	while(KeypadSTR[--str]==' ')
		{
		KeypadSTR[str]=0x00;
		}

	if(SaveFileFlag&SaveFileFlagNewFolder)
		{
		if(FM.TotalFiles==FileMax)
			{
			sprintf(FMOperationErrorStr,"The number of files is over %d(Max)!!",FileMax);
			ShowMessage(FMOperationErrorStr);
			ShowMessage_Delayflag=1;
			FM_InfoFlag|=(FM_SHOW_OPERATION_ERROR+FM_OPERATION_ERROR_TAG);
			// M_num=P_File_Utils;
			FMinfo|=FM_READ_DEVICE;
			}
        else
			{
			sprintf(mybuffer,"%s\\%s",FMnowPath,KeypadSTR);	
			if(strlen(mybuffer)>maxdirlen-1)
				{
				sprintf(FMOperationErrorStr,"The max depth levels are reached!!");
				ShowMessage(FMOperationErrorStr);
				ShowMessage_Delayflag=1;
				FM_InfoFlag|=(FM_SHOW_OPERATION_ERROR+FM_OPERATION_ERROR_TAG);
				// M_num=P_File_Utils;
				FMinfo|=FM_READ_DEVICE;
				}
            else
				{
				FMinfo|=FM_MKDIR;
				//   M_num=P_File_Utils;
				FMinfo|=FM_READ_DEVICE;
				}
			}
		}
    else if(SaveFileFlag&SaveFileFlagRename)
		{
		sprintf((char *)KeypadSTR,"%s%s",(char *)KeypadSTR,(char *)KeypadSubSTR);
		//check if repeated?
		sprintf(mybuffer,"%s\x5C%s",FMnowPath,KeypadSTR);	
		myfile=FS_FOpen(mybuffer,"r");
        if(myfile)//repeated
			{
			FS_FClose(myfile);
			sprintf(FMOperationErrorStr,"This name is repeated!!");
			ShowMessage(FMOperationErrorStr);
			ShowMessage_Delayflag=1;
			FM_InfoFlag|=(FM_SHOW_OPERATION_ERROR+FM_OPERATION_ERROR_TAG);
			}
        else//not repeated
			{
			sprintf(mybuffer,"%s\x5C%s",FMnowPath,FMfile[Sort_F[FM.SelPtr]].my_name);
			FMinfo|=FM_RENAME;
			}
		//M_num=P_File_Utils;
		FMinfo|=FM_READ_DEVICE;
		}
		return(0);
	}
void USB_unplug(void)
	{
	char i;
	if(Upgrading_Flag)
		return;
	//DispMode =DispMode_SELECT_CH;
	//if(M_num==P_CONF_OTHER)
		DispMode = DispMode_SELECT_CH;

	if(M_num<=P_CONF_Ext)
		DispMode =DispMode_BROWSE_ITEMS;
	
	
	for(i=0;i<30;i++)
		{
		SaveFileName[i]=0;
		RecallFileName[i]=0;
		}		
	if( ((M_num==P_UTIL_KEYPAD)&&(K_M_num==P_UTIL_FILE))||(M_num==P_UTIL_FILE)||((M_num==P_FILE_CHAN)&&(F_Media_USB==p3k_File_Utility_BAR.MEDIA)) )
		{
		Freeze_Keyboard = 1;
		Soft_Key_Temp	 = 0;
		
		if( (M_num==P_UTIL_FILE)||(M_num==P_UTIL_KEYPAD) )
			M_num = P_M_num;
		ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
		DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
		MenuRedrawFlag |= MENU_CHANGE;
		}
	if(M_num==P_PROG_Detail)
		{
		Soft_Key_Temp=0;
		MenuRedrawFlag|=MENU_CHANGE;
		}
	}
void FMShowPathProc(char ShowDirLength, char* ShowPath)
{
UBYTE len;

    len=strlen(FMnowPath);
    if(len>ShowDirLength){//The path name is too long.
        len=len- ShowDirLength;
        if(len<4)
		len=4;	
        sprintf(ShowPath,"...%s", FMnowPath+len);
    }
    else
        sprintf(ShowPath,FMnowPath);
}
#define BMP_WIDTH 320
#define BMP_HEIGHT 240
#define BMP_OFFSET 1078
#define Color_Memory_WIDTH 320
#define Color_Memory_HEIGHT 256
#define Cursor_Memory_WIDTH 320
#define Cursor_Memory_HEIGHT 256
#define Date_start BMP_OFFSET
#define COLOR_SIZE Color_Memory_HEIGHT
#define IMG_SIZE Color_Memory_WIDTH*Color_Memory_HEIGHT
#define CURSOR_1_SIZE Cursor_Memory_WIDTH*(Cursor_Memory_HEIGHT/4)
#define CURSOR_2_SIZE Cursor_Memory_WIDTH*(Cursor_Memory_HEIGHT/4)
#define Float_SIZE Color_Memory_WIDTH*Color_Memory_HEIGHT
#define IMG_HEIGHT Color_Memory_HEIGHT
#define Real_HEIGHT BMP_HEIGHT
#define IMG_WIDTH BMP_WIDTH
UBYTE cRead[204800];
char ColorSetFlag; //0: not write LUT for 8bpp Indexed Color 1: already write LUT for 8bpp Indexed Color
char bmp_Buf[234640];
char cCursor[Cursor_Memory_WIDTH*Cursor_Memory_HEIGHT]; /*320*256=81920*/
unsigned long aColor_Set[COLOR_SIZE];
extern const LCD_COLOR GW_LCD_PhysColors[];
char  *bmp_buf_ptr;
UBYTE BMPCount = 0;


int WriteBmpFile(void)	{	
	char NowFileName[30];
	char temp_fname[maxdirlen];
	static BITMAPFILEHEADER bfile;
	static BITMAPINFOHEADER binfo;
	int i,j;
	char *bmp_ptr;
	char *new_ptr, *new_end_ptr;
	unsigned long new_total;
	DWORD dwReadSize;
	unsigned char *cRead_total;
	FS_FILE *Bmp_File;
	unsigned long aColor_Buf[3];
	
	unsigned char c,a;
	int	k,x,y;
	BYTE bRd;
	UWORD Start_X,Start_Y,End_X,End_Y;
	BYTE Data_1,Data_2;
   
	//Initial BMP Header
	bfile.bfType=0x4d42;
	bfile.bfSize=BMP_WIDTH*BMP_HEIGHT+BMP_OFFSET; //75958=320*234+1078  82998=320*256+1078 //77878=320*240+1078
	bfile.bfReserved1=0x0;
	bfile.bfReserved2=0x0;
	bfile.bfOffBits=BMP_OFFSET;

	//Initial Image Information
	binfo.biSize=40;
	binfo.biWidth=BMP_WIDTH; 
	binfo.biHeight=BMP_HEIGHT;
	binfo.biPlanes=1;
	binfo.biBitCount=8; //8bpp
	binfo.biCompression=0; //none Compressed
	binfo.biSizeImage=BMP_WIDTH*BMP_HEIGHT; //
	binfo.biXPelsPerMeter=3780;
	binfo.biYPelsPerMeter=3780;
	binfo.biClrUsed=0x0;
	binfo.biClrImportant=0x0;
   
	//Write BMP data
	dwReadSize = IMG_SIZE+CURSOR_1_SIZE+CURSOR_2_SIZE+Float_SIZE;
	cRead_total=cRead;
	i=0;
	while(i< dwReadSize)
		{
		*(cRead_total++)=*( (char *)(MemAddress+i) );
		i++;
		}
	/*-----------Float Windows----------------*/
#if 1			
	bRd = ReadRegByte(REG_SPECIAL_EFFECTS);
	if(bRd&0x10)
		{		
		Data_1	=	ReadRegByte(REG_FLOAT_WIN_X_START_POS0);
		Data_2	=	ReadRegByte(REG_FLOAT_WIN_X_START_POS1);
		Start_X	=	((Data_2&0xFF)<<8) + (Data_1&0xFF);
		Data_1	=	ReadRegByte(REG_FLOAT_WIN_Y_START_POS0);
		Data_2	=	ReadRegByte(REG_FLOAT_WIN_Y_START_POS1);
		Start_Y	=	((Data_2&0xFF)<<8) + (Data_1&0xFF);	

		Data_1	=	ReadRegByte(REG_FLOAT_WIN_X_END_POS0);
		Data_2	=	ReadRegByte(REG_FLOAT_WIN_X_END_POS1);
		End_X	=	((Data_2&0xFF)<<8) + (Data_1&0xFF);
		
		Data_1	=	ReadRegByte(REG_FLOAT_WIN_Y_END_POS0);
		Data_2	=	ReadRegByte(REG_FLOAT_WIN_Y_END_POS1);
		End_Y	=	((Data_2&0xFF)<<8) + (Data_1&0xFF);
//		printf("Start(x,y)=0x%x,0x%x\n",Start_X,Start_Y);
//		printf("End(x,y)=0x%x,0x%x\n",End_X,End_Y);
		
		new_ptr=(char*)cRead;
		new_ptr+= IMG_SIZE+CURSOR_1_SIZE+CURSOR_2_SIZE;
		memcpy(cCursor,new_ptr, Float_SIZE);
		for(i=Start_X;i<End_X+1;i++)
			{
			for(j=(BMP_HEIGHT-(End_Y+1)*4);j<(BMP_HEIGHT-(Start_Y*4));j++)				
				*(cRead + i * Color_Memory_HEIGHT + j) = cCursor[ (i-Start_X) * Color_Memory_HEIGHT + (j+(Start_Y*4)) ];				
			}
		}
#endif	
	/*-----------Cursor 1----------------*/
	for(i=0;i<(Cursor_Memory_HEIGHT/4);i++)
		{
		for(j=0;j<Cursor_Memory_WIDTH;j++)
			{
			k=i*Cursor_Memory_WIDTH+j;
			x = ((Cursor_Memory_HEIGHT/4)-1) - i;
			y =  j;
			c = *(cRead + IMG_SIZE  + k);
			a= (c & 0xC0 ) >> 6 ;
			if(a == Cursor1Col1) cCursor[ (x*4+0) * Cursor_Memory_WIDTH + y] = Cursor1Ind1;
			if(a == Cursor1Col2) cCursor[ (x*4+0) * Cursor_Memory_WIDTH + y] = Cursor1Ind2;
			if(a == Cursor1Col3) cCursor[ (x*4+0) * Cursor_Memory_WIDTH + y] = Cursor1Ind3;
			if(a == Cursor1Col0) cCursor[ (x*4+0) * Cursor_Memory_WIDTH + y] = 0x00;
			a= (c & 0x30 ) >> 4 ; 
			if(a == Cursor1Col1) cCursor[ (x*4+1) * Cursor_Memory_WIDTH + y] = Cursor1Ind1;
			if(a == Cursor1Col2) cCursor[ (x*4+1) * Cursor_Memory_WIDTH + y] = Cursor1Ind2;
			if(a == Cursor1Col3) cCursor[ (x*4+1) * Cursor_Memory_WIDTH + y] = Cursor1Ind3;
			if(a == Cursor1Col0) cCursor[ (x*4+1) * Cursor_Memory_WIDTH + y] = 0x00;
			a= (c & 0x0C ) >> 2 ; 
			if(a == Cursor1Col1) cCursor[ (x*4+2) * Cursor_Memory_WIDTH + y] = Cursor1Ind1;
			if(a == Cursor1Col2) cCursor[ (x*4+2) * Cursor_Memory_WIDTH + y] = Cursor1Ind2;
			if(a == Cursor1Col3) cCursor[ (x*4+2) * Cursor_Memory_WIDTH + y] = Cursor1Ind3;
			if(a == Cursor1Col0) cCursor[ (x*4+2) * Cursor_Memory_WIDTH + y] = 0x00;
			a= (c & 0x03 ); 
			if(a == Cursor1Col1) cCursor[ (x*4+3) * Cursor_Memory_WIDTH + y] = Cursor1Ind1;
			if(a == Cursor1Col2) cCursor[ (x*4+3) * Cursor_Memory_WIDTH + y] = Cursor1Ind2;
			if(a == Cursor1Col3) cCursor[ (x*4+3) * Cursor_Memory_WIDTH + y] = Cursor1Ind3;
			if(a == Cursor1Col0) cCursor[ (x*4+3) * Cursor_Memory_WIDTH + y] = 0x00;
			}
		}

	for(i=0;i<Color_Memory_WIDTH;i++)
		{
		for(j=0;j<Color_Memory_HEIGHT;j++)
			{
			c = cCursor[(j+16)*Cursor_Memory_WIDTH + i - 0 ];
			if(c != 0x00) 
				*(cRead + i * Color_Memory_HEIGHT + j) = c;		 
			*(bmp_Buf + i* Color_Memory_HEIGHT +j) = *(cRead + i * Color_Memory_HEIGHT + j);				 
			}
		}
	/*-----------Cursor 2----------------*/
	for(i=0;i<(Cursor_Memory_HEIGHT/4);i++)
		{
		for(j=0;j<Cursor_Memory_WIDTH;j++)
			{
			k=i*Cursor_Memory_WIDTH+j;
			x = ((Cursor_Memory_HEIGHT/4)-1) - i;
			y =  j;
			c = *(cRead + IMG_SIZE  + CURSOR_1_SIZE + k);
			a= (c & 0xC0 ) >> 6 ;
			if(a == Cursor2Col1) cCursor[ (x*4+0) * Cursor_Memory_WIDTH + y] = Cursor2Ind1;
			if(a == Cursor2Col2) cCursor[ (x*4+0) * Cursor_Memory_WIDTH + y] = Cursor2Ind2;
			if(a == Cursor2Col3) cCursor[ (x*4+0) * Cursor_Memory_WIDTH + y] = Cursor2Ind3;
			if(a == Cursor2Col0) cCursor[ (x*4+0) * Cursor_Memory_WIDTH + y] = 0x00;
			a= (c & 0x30 ) >> 4 ; 
			if(a == Cursor2Col1) cCursor[ (x*4+1) * Cursor_Memory_WIDTH + y] = Cursor2Ind1;
			if(a == Cursor2Col2) cCursor[ (x*4+1) * Cursor_Memory_WIDTH + y] = Cursor2Ind2;
			if(a == Cursor2Col3) cCursor[ (x*4+1) * Cursor_Memory_WIDTH + y] = Cursor2Ind3;
			if(a == Cursor2Col0) cCursor[ (x*4+1) * Cursor_Memory_WIDTH + y] = 0x00;
			a= (c & 0x0C ) >> 2 ; 
			if(a == Cursor2Col1) cCursor[ (x*4+2) * Cursor_Memory_WIDTH + y] = Cursor2Ind1;
			if(a == Cursor2Col2) cCursor[ (x*4+2) * Cursor_Memory_WIDTH + y] = Cursor2Ind2;
			if(a == Cursor2Col3) cCursor[ (x*4+2) * Cursor_Memory_WIDTH + y] = Cursor2Ind3;
			if(a == Cursor2Col0) cCursor[ (x*4+2) * Cursor_Memory_WIDTH + y] = 0x00;
			a= (c & 0x03 ); 
			if(a == Cursor2Col1) cCursor[ (x*4+3) * Cursor_Memory_WIDTH + y] = Cursor2Ind1;
			if(a == Cursor2Col2) cCursor[ (x*4+3) * Cursor_Memory_WIDTH + y] = Cursor2Ind2;
			if(a == Cursor2Col3) cCursor[ (x*4+3) * Cursor_Memory_WIDTH + y] = Cursor2Ind3;
			if(a == Cursor2Col0) cCursor[ (x*4+3) * Cursor_Memory_WIDTH + y] = 0x00;
			}
		}

	for(i=0;i<Color_Memory_WIDTH;i++)
		{
		for(j=0;j<Color_Memory_HEIGHT;j++)
			{
			c = cCursor[(j+16)*Cursor_Memory_WIDTH + i - 0 ];
			if(c != 0x00) 
				*(cRead + i * Color_Memory_HEIGHT + j) = c;		 
			*(bmp_Buf + i* Color_Memory_HEIGHT +j) = *(cRead + i * Color_Memory_HEIGHT + j);				 
			}
		}
	for(i=0 ; i<30 ; i++)
		NowFileName[i] = 0;
	if(BMPCount<10)			sprintf(NowFileName, "BMP00%d.bmp",	BMPCount++);
	else if(BMPCount<100)	sprintf(NowFileName, "BMP0%d.bmp",	BMPCount++);
	else					sprintf(NowFileName, "BMP%d.bmp",	BMPCount++);

    memcpy(bmp_Buf,cRead, IMG_SIZE);
	for(i=0;i<Color_Memory_HEIGHT;i++)
		{
		for(j=0;j<Color_Memory_WIDTH;j++)			
			cRead[i * Color_Memory_WIDTH + j]=bmp_Buf[((Color_Memory_HEIGHT-1) - i) + ((Color_Memory_WIDTH-1) - j) * Color_Memory_HEIGHT]; 			
		}
	
	if(ColorSetFlag==0)
		{
		//Write LUT for 8bpp Indexed Color
		for (i = 0; i < (1<< binfo.biBitCount ); i++)
			{
			aColor_Buf[0]=GW_LCD_PhysColors[i];
			aColor_Buf[1]=aColor_Buf[0]<<16;
			aColor_Buf[2]=aColor_Buf[0]>>16;
			aColor_Buf[0]&=0x0000ff00;
			aColor_Buf[0]|=aColor_Buf[1]&0x00ff0000;
			aColor_Buf[0]|=aColor_Buf[2]&0x000000ff;
			aColor_Set[i]=aColor_Buf[0];
			}		  
		aColor_Set[10]=0x0000e5;
		ColorSetFlag=1;
		}
	new_ptr=(char*)cRead;
	new_ptr+= IMG_WIDTH * (IMG_HEIGHT -Real_HEIGHT);
	memcpy(bmp_Buf, new_ptr, bfile.bfSize);

	bmp_ptr=bmp_Buf;
	new_ptr=(char*)cRead;
	new_end_ptr=RGB_to_RLE(bmp_ptr, new_ptr, binfo.biWidth, binfo.biHeight);
	new_total=new_end_ptr - new_ptr;
	binfo.biCompression=1; //Compressed*/
	bfile.bfSize=new_total+Date_start;
	binfo.biSizeImage=new_total; 

	bmp_buf_ptr=bmp_Buf;
	WriteBMPBuf(sizeof(bfile), (BYTE *)&bfile);
	WriteBMPBuf(sizeof(binfo), (BYTE *)&binfo);
	WriteBMPBuf(sizeof(aColor_Set), (BYTE *)&aColor_Set);
	WriteBMPBuf(new_total, (BYTE *)&cRead);
	sprintf(temp_fname, "%s\\%s", FMnowPath, NowFileName);
	Bmp_File=FS_FOpen(temp_fname,"wb");

	FS_FWrite((void *)&bmp_Buf, sizeof(char), bfile.bfSize, Bmp_File);
	FS_FClose(Bmp_File);

	///FMinfo|=FM_READ_DEVICE; 
	OSTimeDly(7);   	
	return 0;
	}
void WriteBMPBuf(ULONG length, BYTE* source)
	{
	ULONG  i;

	for(i=0;i<length;i++)
		*bmp_buf_ptr++=*source++;
	}
char* RGB_to_RLE(char *bmp_ptr, char *new_ptr, unsigned int Width, unsigned int Height)
	{
	unsigned char count=1;
	unsigned int Wcount=1;
	char W_4_comp; //Width 4 complement
	char *bmp_total_ptr;

	W_4_comp=Width%4;
	if(W_4_comp!=0)
		W_4_comp=4-W_4_comp;

	bmp_total_ptr=bmp_ptr + Width*Height;
	while(bmp_ptr < bmp_total_ptr)
		{
		if(Wcount>=Width)
			{
			if( (count>1)  || ( *(bmp_ptr)!=*(bmp_ptr-1) ) )
				{
				*(new_ptr++)=count;
				*(new_ptr++)=*(bmp_ptr);
				count=1;
				}
			*(new_ptr++)=0;
			*(new_ptr++)=0;
			Wcount=0;
			bmp_ptr+=W_4_comp;
			}
		else if( *(bmp_ptr)==*(bmp_ptr+1) )
			{
			count++;
			if(count==0xff)
				{
				*(new_ptr++)=count;
				*(new_ptr++)=*(bmp_ptr);
				count=1;
				bmp_ptr++;
				Wcount++;
				}
			}
		else
			{
			*(new_ptr++)=count;
			*(new_ptr++)=*(bmp_ptr);
			count=1;
			}
		Wcount++;
		bmp_ptr++;
		}
	//new_ptr--;
	*--new_ptr=1;
	*++new_ptr=0;
	return(++new_ptr);
	}
typedef signed int			uint32_t;
void encrypt (uint32_t* v, uint32_t* k)
	{
	//uint32_t v0=v[0], v1=v[1], sum=0, i;			 /* set up */
	//uint32_t delta=0x9e3779b9;					 /* a key schedule constant */
	//uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];	 /* cache key */
	int v0=v[0], v1=v[1], sum=0, i; 		  /* set up */
	int delta=0x9e3779b9;					  /* a key schedule constant */
	int k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */

	for (i=0; i < 32; i++) 					   /* basic cycle start */
		{
		sum += delta;
		v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
		v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);  
		}											   /* end cycle */
	v[0]=v0; v[1]=v1;
	}

void decrypt (uint32_t* v, uint32_t* k) 
	{
	//uint32_t v0=v[0], v1=v[1], sum=0xC6EF3720, i;  /* set up */
	//uint32_t delta=0x9e3779b9;					 /* a key schedule constant */
	//uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];	 /* cache key */
	int v0=v[0], v1=v[1], sum=0xC6EF3720, i;  /* set up */
	int delta=0x9e3779b9;					  /* a key schedule constant */
	int k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */

	for (i=0; i<32; i++) 						   /* basic cycle start */
		{
		v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
		v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
		sum -= delta;									
		}											   /* end cycle */
	v[0]=v0; v[1]=v1;
	}
void ReadLicenseData(char *File_ptr,char *Lic_ptr)
	{
	while(*File_ptr!='[')
		File_ptr++;
	File_ptr++;
	
	while(*File_ptr!=']')
		{
		*Lic_ptr = *File_ptr;
		File_ptr++;
		Lic_ptr++;
		}
	*Lic_ptr = 0x00;
	}
#define Max_License_Data 30
extern void BackupAPPInfo(void);
typedef struct	{//read USB VID,PID,Serial Number
				unsigned long SNumber1;
				unsigned long SNumber2;
				unsigned long PID;
				unsigned long VID;
				uint64_t 	  MBR_Data;
				}Usb_Info_str;						/*Total 16 bytes.*/

typedef struct	{//read USB VID,PID,Serial Number
				unsigned long PID;
				unsigned long VID;
				}Vendor_Info_str;

#define Vendor_Max_Number	10
Usb_Info_str	Usb_Info_Data;
typedef struct USB_MBR{
	char USB_SYS[224];
	uint64_t Model[26];
	char Company[80];
}USB_MBR_Str;
USB_MBR_Str USB_MBR_Data;
char WriteOptionLicence(unsigned int SoftNum,unsigned int SoftVer,UBYTE Lic_Source,UBYTE Lic_Action)
	{
	/* Lic_Source:license Source for File or USB */
	/* Lic_Action:license Action is install or uninstall*/
	if(Lic_Action==Lic_Install)
		{
		if(OptionInfo[SoftNum].ModuleFlag)
	    	return Action_Failed;
		else
			{
	        OptionInfo[SoftNum].ModuleFlag	= 1;
	        OptionInfo[SoftNum].SoftVer		= SoftVer;
	        OptionInfo[SoftNum].SoftNum		= SoftNum;
	    	}
		}
	else	/* Lic_Uninstall */
		{
		OptionInfo[SoftNum].ModuleFlag	= 0;
		OptionInfo[SoftNum].SoftVer		= 0;
		OptionInfo[SoftNum].SoftNum		= 0;
		}

	if( (Lic_Source==USB_Source)&&(Lic_Action==Lic_Install) )
		{
		OptionInfo[SoftNum].Un_install= 1;
		OptionInfo[SoftNum].SNumber1	= Usb_Info_Data.SNumber1;
		OptionInfo[SoftNum].SNumber2	= Usb_Info_Data.SNumber2;
		OptionInfo[SoftNum].PID		= Usb_Info_Data.PID;
		OptionInfo[SoftNum].VID		= Usb_Info_Data.VID;
		OptionInfo[SoftNum].MBR_Data	= Usb_Info_Data.MBR_Data;
		USB_MBR_Data.Model[0] = 0;
		FS_Write_MBR((char *)&USB_MBR_Data);
		sprintf(mybuffer,"%s\x5C%s",FMnowPath,FMfile[Sort_F[FM.SelPtr]].my_name);
		FMinfo |= FM_REMOVE;		/*Delete a file.*/
		FMinfo |= FM_READ_DEVICE;
		}
	else
		{
		OptionInfo[SoftNum].Un_install= 0;
		OptionInfo[SoftNum].SNumber1	= 0;
		OptionInfo[SoftNum].SNumber2	= 0;
		OptionInfo[SoftNum].PID		= 0;
		OptionInfo[SoftNum].VID		= 0;
		OptionInfo[SoftNum].MBR_Data	= 0;
		}
	BackupAPPInfo();
    return Action_Success;
	}
void GetCache_key(UBYTE Lic_Source,uint32_t* Cache_key)
	{
	if(Lic_Source==USB_Source)
		{
		Cache_key[0] = Usb_Info_Data.SNumber1;
		Cache_key[1] = Usb_Info_Data.SNumber2;
		Cache_key[2] = Usb_Info_Data.PID;
		Cache_key[3] = Usb_Info_Data.VID;
		}
	else	/* if(Lic_Source==File_Source) */
		{
		Cache_key[0] = 0x11111111;
		Cache_key[1] = 0xabababab;
		Cache_key[2] = 0x22222222;
		Cache_key[3] = 0xcdcdcdcd;
		}
	}
void CreateAPPLicense(void)
	{
	char Check_Data_Str[20],i;
	char Eload_SN[20];
	UBYTE APP_Command,APP_SoftVer;
	unsigned int APP_SoftNum;
	unsigned int eload_Serial_Num=0,eload_Product_ID=0;
	uint32_t License_Code_Data[2],Internal_code[4];
	
	sprintf(Eload_SN,"EL147852");
	APP_Command = 1;
	APP_SoftNum = 0;
	APP_SoftVer = 3;

	for(i=0 ; i<20 ; i++)
		Check_Data_Str[i] = 0;
	sprintf(Check_Data_Str,"%s",Eload_SN+strlen(Eload_SN)-4);
	eload_Serial_Num = atoi(Check_Data_Str);
	eload_Serial_Num = eload_Serial_Num&0x0000FFFF;
#if 0
	printf("eload_Serial_Num_str=%s\n",Check_Data_Str);
	printf("eload_Serial_Num=0x%x\n",eload_Serial_Num);
#endif
	for(i=0 ; i<20 ; i++)
		Check_Data_Str[i] = 0;
	strncpy(Check_Data_Str,Eload_SN,strlen(Eload_SN)-4);
	for(i=0;i<strlen(Check_Data_Str);i++)
		eload_Product_ID += Check_Data_Str[i];
	eload_Product_ID = eload_Product_ID&0x0000FFFF;
#if 0
	printf("eload_Product_ID_str=%s\n",Check_Data_Str);
	printf("eload_Product_ID=0x%x\n",eload_Product_ID);
#endif	

	License_Code_Data[1] = ((APP_Command<<24)&0xFF000000)    | ((eload_Serial_Num<<8)&0x00FFFF00) | ((eload_Product_ID>>8)&0x000000FF);
	License_Code_Data[0] = (eload_Product_ID<<24)&0xFF000000 | ((APP_SoftNum<<8)&0x00FFFF00)      | (APP_SoftVer&0x000000FF);
#if 0
	printf("64 bits lisence_code:0x%08x", License_Code_Data[1]);
	printf("%08x\n", License_Code_Data[0]);
#endif
	GetCache_key(File_Source,Internal_code);
	encrypt(License_Code_Data, Internal_code);
	printf("64 bits ecode :0x%08x", License_Code_Data[1]);	
	printf("%08x\n", License_Code_Data[0]);
	}

UBYTE ReadAPPLicense(char *FileName)
	{
	char temp_fname[maxdirlen],Lic_File_Data[Max_License_Data],Lic_Code[Max_License_Data];
	char Check_Data_Str[20];
	LONG FileSize;
	FS_FILE *Wave_File;	
	long long License_Code_num;
	uint32_t License_Code_Data[2],Internal_code[4];
	UBYTE i;
	UBYTE APP_Command,APP_SoftVer;
	unsigned int APP_Serial_Num=0,APP_Product_ID=0,APP_SoftNum;
	unsigned int eload_Serial_Num=0,eload_Product_ID=0;
	
	sprintf(temp_fname, "%s\\%s", FMnowPath, FileName);
	if( (Wave_File=FS_FOpen(temp_fname, "rb") )==0)
		{
		Debug_printf("Open Lis File Error\n");
		return Recall_Failed;
		}
	else
		{
		FS_FSeek(Wave_File, 0, FS_SEEK_END);
		FileSize = FS_FTell(Wave_File);
		FS_FSeek(Wave_File,0,SEEK_SET);
		if(FileSize<Max_License_Data)
			{
			FS_FRead(Lic_File_Data, sizeof(char), FileSize, Wave_File);
			FS_FClose(Wave_File);
			}
		else
			{
			FS_FClose(Wave_File);
			Debug_printf("File Size Over 30 Bytes\n");
			return Recall_Failed;
			}
		ReadLicenseData(Lic_File_Data,Lic_Code);
		License_Code_num		= strtoull(Lic_Code,NULL,16);
		License_Code_Data[0]	=  License_Code_num&0x00000000FFFFFFFF;
		License_Code_Data[1]	= (License_Code_num)>>32&0x00000000FFFFFFFF;
#if 0
		printf("64 bits encode :0x%08x", License_Code_Data[1]);
		printf("%08x\n", License_Code_Data[0]);
#endif
		if(License_Code_num==0xef1e62c2aa048285)
			{
			/* Disable All APP*/
			for(i=0 ; i<10 ; i++)
				WriteOptionLicence(i,0,0,Lic_Uninstall);
			return Recall_Complete;
			}
		GetCache_key(File_Source,Internal_code);
		decrypt(License_Code_Data, Internal_code);
#if 0
		printf("64 bits decode :0x%08x", License_Code_Data[1]);	
		printf("%08x\n", License_Code_Data[0]);
#endif
		APP_Command		=  (License_Code_Data[1])>>24&0x000000ff;
		APP_Serial_Num	=  (License_Code_Data[1])>>8 &0x0000ffff;
		APP_Product_ID	= ((License_Code_Data[1]<<8) &0x0000ff00)| ( (License_Code_Data[0]>>24)&0x000000ff );
		APP_SoftNum		=  (License_Code_Data[0]>>8) &0x0000ffff;
		APP_SoftVer		=   License_Code_Data[0]     &0x000000ff;
#if 0
		printf("APP_Command=0x%x\n", 	APP_Command);
		printf("APP_Serial_Num=0x%x\n", APP_Serial_Num);
		printf("APP_Product_ID=0x%x\n", APP_Product_ID);
		printf("APP_SoftNum=0x%x\n", 	APP_SoftNum);
		printf("APP_SoftVer=0x%x\n", 	APP_SoftVer);
#endif
		/* Check APP Command		*/

		/* Check Serial Number		*/
		for(i=0 ; i<20 ; i++)
			Check_Data_Str[i] = 0;
		sprintf(Check_Data_Str,"%s",P3k_Serial_Number.Product_Serial_Number+strlen((const char *)P3k_Serial_Number.Product_Serial_Number)-4);
		eload_Serial_Num = atoi(Check_Data_Str);
		eload_Serial_Num = eload_Serial_Num&0x0000FFFF;
#if 0
		printf("eload_Serial_Num_str=%s\n",Check_Data_Str);
		printf("eload_Serial_Num=0x%x\n",eload_Serial_Num);
#endif
		if(eload_Serial_Num!=APP_Serial_Num)
			{
			Debug_printf("Serial Number Error\n");
			return Recall_Failed;
			}
		/* Check Product ID 		*/
		for(i=0 ; i<20 ; i++)
			Check_Data_Str[i] = 0;
		strncpy(Check_Data_Str,(const char *)P3k_Serial_Number.Product_Serial_Number,strlen((const char *)P3k_Serial_Number.Product_Serial_Number)-4);
		for(i=0;i<strlen(Check_Data_Str);i++)
			eload_Product_ID += Check_Data_Str[i];
		eload_Product_ID = eload_Product_ID&0x0000FFFF;
#if 0
		printf("eload_Product_ID_str=%s\n",Check_Data_Str);
		printf("eload_Product_ID=0x%x\n",eload_Product_ID);
#endif
		if(eload_Product_ID!=APP_Product_ID)
			{
			Debug_printf("Product ID Error\n");
			return Recall_Failed;
			}
		/* Check Softwave Number	*/
		/* Check Softwave Version	*/


		/* Enable APP Softwave */
#if 0
		printf("Enable APP Softwave\n");
		printf("APP_Command=0x%x\n", 	APP_Command);
		printf("APP_SoftNum=0x%x\n", 	APP_SoftNum);
		printf("APP_SoftVer=0x%x\n", 	APP_SoftVer);
#endif
		if(WriteOptionLicence(0,0,File_Source,Lic_Install)==0)
			return Recall_Failed;
		}
	return Recall_Complete;
	}
extern void WriteFile(void *pData, unsigned long Size, char *FileName);
extern unsigned short ReadUsbVID(void);
extern unsigned short ReadUsbPID(void);
extern char ReadUsbSerialNum(char *buff);
void Create_vfile(void) /* Creat virtual File */
	{
	FS_FILE *Write_File;
	char temp_fname[maxdirlen];
	ULONG Total_time;
    uint64_t licnum=0;
    uint64_t i=0,j=0;
    char data_str[30];

	Total_time = CurrentTime.tm_sec + CurrentTime.tm_min*100 + CurrentTime.tm_hour*10000 + CurrentTime.tm_mday*1000000 + CurrentTime.tm_mon* 100000000;

	srand( (int)Total_time ); 
    for(i=0 ; i<16 ; i++)
    	{
        j = rand()%16;
        licnum = licnum|(j<<(i*4));
        j=0;
    	}
	 for(i=0 ; i<sizeof(data_str) ; i++)
        data_str[i] = 0;
	//printf(" 0x%llx\n",licnum);
	sprintf(data_str,"[%llx]",licnum);
	
	sprintf(temp_fname, "usb:\\USB_MBR.lic");
	if( (Write_File=FS_FOpen(temp_fname,"wb"))==0)
		Debug_printf("write file error\n");
	else
		{
		if(FS_FWrite(data_str, sizeof(char), strlen(data_str), Write_File)!=strlen(data_str))
			Debug_printf("Writing Failed/n");
		FS_FClose(Write_File);
		}
	FMinfo |= FM_READ_DEVICE;
	}
void Create_Lic(void)
	{
    char Serial_Num_str[20];
    char Product_ID_str[20];
    short i;
    unsigned int Serial_Num=0,Product_ID=0;
    unsigned int APP_Command=0,APP_SoftNum=0;
    uint32_t licence_code[2],Internal_code[4];

    for(i=0;i<20;i++)
		{
		Serial_Num_str[i] = 0;
		Product_ID_str[i] = 0;
		}
	sprintf(Serial_Num_str,"%lx",Usb_Info_Data.SNumber1);
	sprintf(Product_ID_str,"%lx",Usb_Info_Data.SNumber2);
#if 0
	printf("Serial_Num_str=%s\n",Serial_Num_str);
	printf("Product_ID_str=%s\n",Product_ID_str);
#endif
    for(i=0;i<strlen(Serial_Num_str);i++)
        Serial_Num += Serial_Num_str[i];
    Serial_Num = Serial_Num&0x0000FFFF;
	//printf("Serial_Num=0x%x\n",Serial_Num);

    for(i=0;i<strlen(Product_ID_str);i++)
        Product_ID += Product_ID_str[i];
    Product_ID = Product_ID&0x0000FFFF;
	//printf("Product_ID=0x%x\n",Product_ID);

    APP_SoftNum = 0x00;
    APP_Command = 0x06;

	licence_code[1] = ((APP_Command<<24)&0xFF000000)|((Serial_Num<<8)&0x00FFFF00) |((Product_ID>>8)&0x000000FF);
    licence_code[0] = (Product_ID<<24)&0xFF000000	|((APP_SoftNum<<8)&0x00000f00);
	//printf("64 bits lisence_code:0x%08x", licence_code[1]);
	//printf("%08x\n", licence_code[0]);

	GetCache_key(USB_Source,Internal_code);
#if 0
	printf("128 bits ClearlyCode :0x%08lx", Usb_Info_Data.VID);
	printf("%08lx",  Usb_Info_Data.PID);
	printf("%08lx",  Usb_Info_Data.SNumber2);
	printf("%08lx\n",Usb_Info_Data.SNumber1);

	printf("128 bits Internal_code :0x%08x", Internal_code[3]);
	printf("%08x",	Internal_code[2]);
	printf("%08x",	Internal_code[1]);
	printf("%08x\n",Internal_code[0]);
#endif

    encrypt(licence_code, Internal_code);
	//printf("64 bits ecode :0x%08x", licence_code[1]);
	//printf("%08x\n", licence_code[0]);

    USB_MBR_Data.Model[0]	= licence_code[1];
	USB_MBR_Data.Model[0]	= ((USB_MBR_Data.Model[0]<<32)&0xFFFFFFFF00000000) + (licence_code[0]&0x00000000FFFFFFFF);
	//printf("USB_MBR_Data.Model[0]=0x%llx\n",USB_MBR_Data.Model[0]);

#if 0
    decrypt(licence_code, Internal_code);
    printf("64 bits decode :0x%08x", licence_code[1]);
    printf("%08x\n", licence_code[0]);
#endif
	}

void APP_Create_Option_LIC(void)
	{
	Vendor_Info_str	Vendor_Info_Data[Vendor_Max_Number];
	char Usb_SerialNum[50],USBMatch;
	short i;

	for(i=0 ; i<sizeof(Usb_SerialNum) ; i++)
		Usb_SerialNum[i] = 0;
	
	if( (USB_Status!=USB_Exist)||(ReadUsbSerialNum(Usb_SerialNum)==0) )
		{
		Debug_printf("No USB\n");
		return;
		}
	Usb_Info_Data.PID		= ReadUsbPID();
	Usb_Info_Data.VID		= ReadUsbVID();
	Usb_Info_Data.SNumber1	= strtoull(Usb_SerialNum,NULL,16);
	Usb_Info_Data.SNumber2	= (strtoull(Usb_SerialNum,NULL,16)>>32);
	/* Input available USB PID and VID 	*/
	for(i=0 ; i<Vendor_Max_Number ; i++)
		{
		Vendor_Info_Data[i].PID = 0;
		Vendor_Info_Data[i].VID = 0;
		}
	Vendor_Info_Data[0].PID = 0xC96A;
	Vendor_Info_Data[0].VID = 0x125F;

	USBMatch = 0;
	for(i=0 ; i<Vendor_Max_Number ; i++)
		{
		if( (Vendor_Info_Data[i].PID==Usb_Info_Data.PID)
		  &&(Vendor_Info_Data[i].VID==Usb_Info_Data.VID) )
			{
			USBMatch = 1;
			break;
			}
		}

	if(USBMatch==0)
		{
		Debug_printf(" VID Err or PID Err!!!\n ");
		return;
		}

	FS_Read_MBR((char *)&USB_MBR_Data);

	for(i=0 ; i<26 ; i++)
		USB_MBR_Data.Model[i] = 0;
	
	Create_Lic();
	Create_vfile();	
	
	FS_Write_MBR((char *)&USB_MBR_Data);
	}
UBYTE ReadMBRLicense(void)//option can transfer
	{
    char Serial_Num_str[20];
    char Product_ID_str[20];
    unsigned int Serial_Num=0,Product_ID=0;
    unsigned int APP_Command=0,lSerial_Num=0,lProduct_ID=0,APP_SoftNum=0,APP_SoftVer=0;
    uint32_t licence_code[2], Internal_code[4];
	
	Vendor_Info_str	Vendor_Info_Data[Vendor_Max_Number];
	char Usb_SerialNum[50],USBMatch;
	short i;

	for(i=0 ; i<sizeof(Usb_SerialNum) ; i++)
		Usb_SerialNum[i] = 0;
	
	if( (USB_Status!=USB_Exist)||(ReadUsbSerialNum(Usb_SerialNum)==0) )
		{
		Debug_printf("No USB\n");
		return 0;
		}
	Usb_Info_Data.PID		= ReadUsbPID();
	Usb_Info_Data.VID		= ReadUsbVID();
	Usb_Info_Data.SNumber1	= strtoull(Usb_SerialNum,NULL,16);
	Usb_Info_Data.SNumber2	= (strtoull(Usb_SerialNum,NULL,16)>>32);
	/* Input available USB PID and VID 	*/
	for(i=0 ; i<Vendor_Max_Number ; i++)
		{
		Vendor_Info_Data[i].PID = 0;
		Vendor_Info_Data[i].VID = 0;
		}
	Vendor_Info_Data[0].PID = 0xC96A;
	Vendor_Info_Data[0].VID = 0x125F;

	USBMatch = 0;
	for(i=0 ; i<Vendor_Max_Number ; i++)
		{
		if( (Vendor_Info_Data[i].PID==Usb_Info_Data.PID)
		  &&(Vendor_Info_Data[i].VID==Usb_Info_Data.VID) )
			{
			USBMatch = 1;
			break;
			}
		}

	if(USBMatch==0)
		{
		Debug_printf(" VID Err or PID Err!!!\n ");
		return 0;
		}

    FS_Read_MBR((char *)&USB_MBR_Data);
	Usb_Info_Data.MBR_Data = USB_MBR_Data.Model[0];
	 
	licence_code[0] =  USB_MBR_Data.Model[0]&0x00000000FFFFFFFF;
	licence_code[1] = (USB_MBR_Data.Model[0]>>32)&0x00000000FFFFFFFF;
	
#if 0
	printf("64 bits code :0x%08x", licence_code[1]);
	printf("%08x\n", licence_code[0]);
#endif

    for(i=0;i<20;i++)
    	{
        Serial_Num_str[i]=0;
        Product_ID_str[i]=0;        
    	}

    sprintf(Serial_Num_str,"%lx",Usb_Info_Data.SNumber1);
    sprintf(Product_ID_str,"%lx",Usb_Info_Data.SNumber2);
#if 0
	printf("Serial_Num_str=%s\n",Serial_Num_str);
	printf("Product_ID_str=%s\n",Product_ID_str);    
#endif

    for(i=0;i<strlen(Serial_Num_str);i++)
        Serial_Num+=Serial_Num_str[i];
    Serial_Num=Serial_Num&0x0000FFFF;
	//printf("Serial_Num=0x%x\n",Serial_Num);

    for(i=0;i<strlen(Product_ID_str);i++)
        Product_ID+=Product_ID_str[i];
    Product_ID=Product_ID&0x0000FFFF;
	//printf("Product_ID=0x%x\n",Product_ID);

	GetCache_key(USB_Source,Internal_code);
#if 0
	printf("128 bits Internal_code :0x%08x", Internal_code[3]);
	printf("%08x",	Internal_code[2]);
	printf("%08x",	Internal_code[1]);
	printf("%08x\n",Internal_code[0]);
#endif

    decrypt(licence_code, Internal_code);
#if 0
	printf("64 bits decode :0x%08x", licence_code[1]);
	printf("%08x\n", licence_code[0]);
#endif
    
    APP_Command		=  licence_code[1]>>24&0x000000ff;
    lSerial_Num		=  licence_code[1]>>8&0x0000ffff;
    lProduct_ID		= (licence_code[1]<<8&0x0000ff00)|( licence_code[0]>>24&0x000000ff);
    APP_SoftNum		=  licence_code[0]>>8&0x0000ffff;
    APP_SoftVer		=  licence_code[0]&0x000000ff;
#if 0
	printf("APP_Command=0x%x\n", APP_Command);
	printf("lSerial_Num=0x%x\n", lSerial_Num);
	printf("lProduct_ID=0x%x\n", lProduct_ID);
	printf("APP_SoftNum=0x%x\n", APP_SoftNum);        
	printf("APP_SoftVer=0x%x\n", APP_SoftVer); 
#endif

    if(lSerial_Num==Serial_Num &&  lProduct_ID==Product_ID)
    	{
    	if(WriteOptionLicence(APP_SoftNum,APP_SoftVer,USB_Source,Lic_Install)==0)
    		{
    		Debug_printf(" Licence double Install!!!\n ");
			return 0;
    		}
    	}
	else
		{
		Debug_printf(" USB MBR Data Error !!!\n ");
		return 0;
		}
	return 1;
	}
void Read_USB_Info(void)
	{
	FS_FILE *Write_File;
	char temp_fname[maxdirlen];
	char Usb_SerialNum[50];
	short i;

	for(i=0 ; i<sizeof(Usb_SerialNum) ; i++)
		Usb_SerialNum[i] = 0;
	
	if( (USB_Status!=USB_Exist)||(ReadUsbSerialNum(Usb_SerialNum)==0) )
		{
		Debug_printf("No USB\n");
		return;
		}
	FS_Read_MBR((char *)&USB_MBR_Data);
	Usb_Info_Data.PID		= ReadUsbPID();
	Usb_Info_Data.VID		= ReadUsbVID();
	Usb_Info_Data.SNumber1	= strtoull(Usb_SerialNum,NULL,16);
	Usb_Info_Data.SNumber2	= (strtoull(Usb_SerialNum,NULL,16)>>32);
	Usb_Info_Data.MBR_Data	= USB_MBR_Data.Model[0];

	sprintf(temp_fname, "usb:\\USB_D1.DAT");
	if( (Write_File=FS_FOpen(temp_fname,"wb"))==0)
		Debug_printf("write file error\n");
	else
		{
		if(FS_FWrite(&Usb_Info_Data, sizeof(char), sizeof(Usb_Info_Data), Write_File)!=sizeof(Usb_Info_Data))
			Debug_printf("Writing Failed/n");
		FS_FClose(Write_File);
		}
	FMinfo |= FM_READ_DEVICE;

	sprintf(temp_fname, "usb:\\USB_D2.DAT");
	if( (Write_File=FS_FOpen(temp_fname,"wb"))==0)
		Debug_printf("write file error\n");
	else
		{
		if(FS_FWrite(&USB_MBR_Data, sizeof(char), sizeof(USB_MBR_Data), Write_File)!=sizeof(USB_MBR_Data))
			Debug_printf("Writing Failed/n");
		FS_FClose(Write_File);
		}
	FMinfo |= FM_READ_DEVICE;
	}
BYTE OptionUninstall(BYTE chnum, BYTE x)
	{
	short i;
	char Usb_SerialNum[50];

	if(OptionInfo[0].Un_install==0)
		return 0;

	for(i=0 ; i<sizeof(Usb_SerialNum) ; i++)
		Usb_SerialNum[i] = 0;
	
	if( (USB_Status!=USB_Exist)||(ReadUsbSerialNum(Usb_SerialNum)==0) )
		{
		Debug_printf("No USB\n");
		return 0;
		}

	Usb_Info_Data.PID		= ReadUsbPID();
	Usb_Info_Data.VID		= ReadUsbVID();
	Usb_Info_Data.SNumber1	= strtoull(Usb_SerialNum,NULL,16);
	Usb_Info_Data.SNumber2	= (strtoull(Usb_SerialNum,NULL,16)>>32);

#if 0
	printf("128 bits ClearlyCode :0x%08lx", Usb_Info_Data.VID);
	printf("%08lx", Usb_Info_Data.PID);
	printf("%08lx", Usb_Info_Data.SNumber2);
	printf("%08lx\n", Usb_Info_Data.SNumber1);
#endif

	if( (OptionInfo[0].VID!=Usb_Info_Data.VID)||(OptionInfo[0].PID!=Usb_Info_Data.PID)||(OptionInfo[0].SNumber1!=Usb_Info_Data.SNumber1)||(OptionInfo[0].SNumber2!=Usb_Info_Data.SNumber2) )
		{
		Debug_printf("VID Err or PID Err or SN Err!!!\n");
		Debug_printf("Please use the same USB device!!!\n");
		return 0;
		}

	FS_Read_MBR((char *)&USB_MBR_Data);
	USB_MBR_Data.Model[0] = OptionInfo[0].MBR_Data;

	//printf("USB_MBR_Data.Model[0]=0x%llx\n",USB_MBR_Data.Model[0]);
	Create_vfile();

	FS_Write_MBR((char *)&USB_MBR_Data);
	WriteOptionLicence(0,0,USB_Source,Lic_Uninstall);
	
	M_num = P_FUNC_MAIN;
	Soft_Key_Temp  = 0;
	ChanRedrawFlag |= CHAN_STATUS + BG_CLEAR;
	DataRedrawFlag |= PARA_CHANGE + BG_CLEAR;
	MenuRedrawFlag |= MENU_CHANGE;
	return 1;
	}

