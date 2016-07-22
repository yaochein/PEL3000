#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "fs_api.h"
#include "../includes.h"
#include "../guix/SSD1906.h"
#include "../1906API/include/bitmap.h"
#include "head.h"
#include "keydef.h"
#include "fm.h"
#include "savrec.h"
//#include "JPEG_api_encoder.h"

#define B_Width 0x12
#define B_Height 0x16
#define BitCount 0x1C
#define B_Compression 0x1E
#define Date_start 0x436
#define B_Size_Addr 0x05
#define Bh_Size 0x02
#define Bi_Size 0x22

#define MAX_LOADSTRING 100
#define ID_TIMER 1
#define TIME_INTERVAL 10
#define COLOR_SIZE 256
#define HEAD_SIZE 1078
#define IMG_SIZE 81920
#define FILE_SIZE (HEAD_SIZE + IMG_SIZE)
#define IMG_HEIGHT 256
#define Real_HEIGHT 234
#define IMG_WIDTH 320
#define TAIL_SIZE 31008
#define cCursor_Size 15504 //0x3C90
#define aColor_Set_Num 16

#define Cur_Color_yollow 0x90
#define Cur_Color_white 0x91

char *RGB_to_RLE(char *, char *, unsigned int, unsigned int);
char *RLE_to_RGB(char *, char *, unsigned int, unsigned int);
int WriteBmpFile(char);
void WriteBMPBuf(ULONG, BYTE*);
BYTE RecallBmpBuf(void);
void DrawRefImage(void);
void ClearRefImage(void);
//char* Bmp_proc(char *, char*);
//int WriteBMPFile(void);
extern int  FileNameConvert(int, char *, char);
extern int  NextFileName(int, char *, char, char);
extern void WriteFile(void *, int , char *);
extern void CursorSetPixel_A2(UWORD, UWORD, UBYTE);
extern void ClearCursor2(void);
extern WORD WRFlashData(ULONG);

extern char FSdev[];
extern char FMnowPath[];
extern char AllFileName[15];
extern char  NowFileName[20];
extern char  AllFileDir[10];
extern const LCD_COLOR  GW_LCD_PhysColors[];  //0x112233: B:11, G:22, R:33
extern char FMShowSRPath[];
extern unsigned char  cRead[];
extern BYTE USB_PrintStatus;
extern UWORD MarkRedrawFlag;
extern WORD AutomeasRedrawFlag;

WORD BmpFileCount=0;
char  ColorSetFlag; //0: not write LUT for 8bpp Indexed Color 1: already write LUT for 8bpp Indexed Color
char  bmp_Buf[IMG_SIZE],  cCursor[62016];
//char  cRead[IMG_SIZE+TAIL_SIZE];
char  *bmp_buf_ptr;
unsigned long aColor_Set[COLOR_SIZE];
unsigned long aColor_Set_Buf[aColor_Set_Num];
unsigned long aColor_Set_Cur[2];
BYTE PaletteLayoutBuf;
UBYTE head_buf[HEAD_SIZE];
UBYTE Ref_Image_buf[32][200]; // X=250/8=31.25 , Y=200
BYTE Old_Ref_Image_Status;
UBYTE RefImageFlag;

int WriteBmpFile(char Mode)
{
//Mode 0: Select "Save Image" ,  Save Image to USB
//Mode 1: Select "Save All"   ,      Save Image to USB
//Mode 2: Select "Hardcopy" ,      printer
   int aColorSep[3];
   char temp_fname[maxdirlen];
   static BITMAPFILEHEADER bfile;
   static BITMAPINFOHEADER binfo;
   int i,j;
   char *bmp_ptr;
   char *new_ptr, *new_end_ptr, sou_ptr;
   unsigned long new_total;
   DWORD	dwReadSize;
   unsigned char	c, a, *cRead_total;
   int		k,x,y;
   FS_FILE *Bmp_File;
   FILE *PC_File; //test write to PC
   long Length;
   unsigned long aColor_Buf[3];
   
   //Initial BMP Header
   bfile.bfType=0x4d42;
   bfile.bfSize=75958; //75958=320*234+1078  82998=320*256+1078 
   bfile.bfReserved1=0x0;
   bfile.bfReserved2=0x0;
   bfile.bfOffBits=1078;

   //Initial Image Information
   binfo.biSize=40;
   binfo.biWidth=320; 
   binfo.biHeight=234;
   binfo.biPlanes=1;
   binfo.biBitCount=8; //8bpp
   binfo.biCompression=0; //none Compressed
   binfo.biSizeImage=320*234; //
   binfo.biXPelsPerMeter=3780;
   binfo.biYPelsPerMeter=3780;
   binfo.biClrUsed=0x0;
   binfo.biClrImportant=0x0;
   
   //printf("Writing File.\n");
   //Write BMP data
   dwReadSize = IMG_SIZE+TAIL_SIZE;
   cRead_total=cRead;
   i=0;
   while(i< dwReadSize){
     *(cRead_total++)=*( (char *)(0x20340000+i) );
	 i++;
   }
   
   for(i=0;i<51;i++){
   	  for(j=0;j<304;j++){
   		k=i*304+j;
   		x = 50 - i;
   		y =  j;
   		c = *(cRead + IMG_SIZE  + k);
   		a= (c & 0xC0 ) >> 6 ;
   		if(a == 0x01) cCursor[ (x*4+0) * 304 + y] = 0x0e;
   		if(a == 0x02) cCursor[ (x*4+0) * 304 + y] = 0x08;
   		if(a == 0x03) cCursor[ (x*4+0) * 304 + y] = 0x04;
   		if(a == 0x00) cCursor[ (x*4+0) * 304 + y] = 0x00;
   		a= (c & 0x30 ) >> 4 ; 
   		if(a == 0x01) cCursor[ (x*4+1) * 304 + y] = 0x0e;
   		if(a == 0x02) cCursor[ (x*4+1) * 304 + y] = 0x08;
   		if(a == 0x03) cCursor[ (x*4+1) * 304 + y] = 0x04;
   		if(a == 0x00) cCursor[ (x*4+1) * 304 + y] = 0x00;
   		a= (c & 0x0C ) >> 2 ; 
   		if(a == 0x01) cCursor[ (x*4+2) * 304 + y] = 0x0e;
   		if(a == 0x02) cCursor[ (x*4+2) * 304 + y] = 0x08;
   		if(a == 0x03) cCursor[ (x*4+2) * 304 + y] = 0x04;
   		if(a == 0x00) cCursor[ (x*4+2) * 304 + y] = 0x00;
   		a= (c & 0x03 ); 
   		if(a == 0x01) cCursor[ (x*4+3) * 304 + y] = 0x0e;
   		if(a == 0x02) cCursor[ (x*4+3) * 304 + y] = 0x08;
   		if(a == 0x03) cCursor[ (x*4+3) * 304 + y] = 0x04;
   		if(a == 0x00) cCursor[ (x*4+3) * 304 + y] = 0x00;
   	  }
   }
   
   for(i=0;i<320;i++){
   	  for(j=0;j<256;j++){
   		if(j < 212 && j >= 8 && i < 311 && i >= 10 ){
   			c = cCursor[(j-8)*304 + i - 10 ];
   			if(c != 0x00) 
   				*(cRead + i * 256 + j) = c;
   		}
   		*(bmp_Buf + i* 256 +j) = *(cRead + i * 256 + j);				
   	  }
   }
   
   for(i=0;i<51;i++){
   	  for(j=0;j<304;j++){
   		k=i*304+j;
   		x = 50 - i;
   		y =  j;
   		c = *(cRead + IMG_SIZE  + 304 * 51 + k);
   		a= (c & 0xC0 ) >> 6 ;
   		if(a == 0x01) cCursor[ (x*4+0) * 304 + y] = 0x90;
   		if(a == 0x02) cCursor[ (x*4+0) * 304 + y] = 0x91;
   		if(a == 0x03) cCursor[ (x*4+0) * 304 + y] = 0x06;
   		if(a == 0x00) cCursor[ (x*4+0) * 304 + y] = 0x00;
   		a= (c & 0x30 ) >> 4 ; 
   		if(a == 0x01) cCursor[ (x*4+1) * 304 + y] = 0x90;
   		if(a == 0x02) cCursor[ (x*4+1) * 304 + y] = 0x91;
   		if(a == 0x03) cCursor[ (x*4+1) * 304 + y] = 0x06;
   		if(a == 0x00) cCursor[ (x*4+1) * 304 + y] = 0x00;
   		a= (c & 0x0C ) >> 2 ; 
   		if(a == 0x01) cCursor[ (x*4+2) * 304 + y] = 0x90;
   		if(a == 0x02) cCursor[ (x*4+2) * 304 + y] = 0x91;
   		if(a == 0x03) cCursor[ (x*4+2) * 304 + y] = 0x06;
   		if(a == 0x00) cCursor[ (x*4+2) * 304 + y] = 0x00;
   		a= (c & 0x03 ); 
   		if(a == 0x01) cCursor[ (x*4+3) * 304 + y] = 0x90;
   		if(a == 0x02) cCursor[ (x*4+3) * 304 + y] = 0x91;
   		if(a == 0x03) cCursor[ (x*4+3) * 304 + y] = 0x06;
   		if(a == 0x00) cCursor[ (x*4+3) * 304 + y] = 0x00;
   	  }
   }
   
   for(i=0;i<320;i++){
   	  for(j=0;j<256;j++){
   		if(j < 212 && j >= 8 && i < 311 && i >= 10 ){
   			c = cCursor[(j-8)*304 + i - 10 ];
   			if(c != 0x00) 
   				*(cRead + i * 256 + j) = c;
   		}
   		*(bmp_Buf + i* 256 +j) = *(cRead + i * 256 + j);				
   	  }
   }	
   
   if(Mode==0){
         sprintf(temp_fname, "Saving image to %s\\%s", FMShowSRPath, NowFileName);
   }
   else if(Mode==1){
   	  sprintf(NowFileName, "%sDS.bmp", AllFileName);
         sprintf(temp_fname, "Saving all to %s\\%s", FMShowSRPath, AllFileDir);
   }
   else if(Mode==2){
         USB_PrintStatus=USB_PrintBusy;
         PaletteLayoutBuf=HARDCOPY.PaletteLayout;
         if( (M_num>=P_HCOPYIMAGE) && (M_num<=P_HCOPYPRT) )
             MenuRedrawFlag|=MENU2_CHANGE;
   	  sprintf(NowFileName, "%sDS.bmp", AllFileName);
   	  sprintf(temp_fname, "printing");
   }
   HintDelay(temp_fname);
   
   for(i=0;i<256;i++){
   	  for(j=0;j<320;j++){
   		cRead[i * 320 + j]=bmp_Buf[(255 - i) + (319 - j) * 256]; //bmp_ptr
   		//bmp_ptr[i * 320 + j]=bmp_Buf[i + j * 256];
   	  }
   }
   if(ColorSetFlag==0){
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
       for(j=0;j<aColor_Set_Num;j++)
           aColor_Set_Buf[j]=aColor_Set[j];
       aColor_Set_Cur[0]=aColor_Set[Cur_Color_yollow];
       aColor_Set_Cur[1]=aColor_Set[Cur_Color_white];
	ColorSetFlag=1;
   }
   new_ptr=(char*)cRead;
   new_ptr+= IMG_WIDTH * (IMG_HEIGHT -Real_HEIGHT);
   memcpy(bmp_Buf, new_ptr, bfile.bfSize);
   if(HARDCOPY.InkSaver){
        aColor_Set[0]=0xffffff; //For V0.50 and latter.   Kevin Meng 2006.08.31
        aColor_Set[1]=0x000000; //
        aColor_Set[2]=0xffb000;
        aColor_Set[7]=0;
        aColor_Set[10]=0xffffff;
        aColor_Set[11]=0xdddddd;
        aColor_Set[12]=0xdddddd;
        aColor_Set[15]=0; //
        aColor_Set[Cur_Color_yollow]=0xffb100;
        aColor_Set[Cur_Color_white]=0;
   }
   else{
       for(i=0;i<aColor_Set_Num;i++)
           aColor_Set[i]=aColor_Set_Buf[i];
       aColor_Set[Cur_Color_yollow]=aColor_Set_Cur[0];
       aColor_Set[Cur_Color_white]=aColor_Set_Cur[1];
  }
   if(Mode<2){
	/*if( (HARDCOPY.PaletteLayout==1) || (HARDCOPY.PaletteLayout==3) ){
	    memcpy(cRead, bmp_Buf, bfile.bfSize);
	    binfo.biWidth=234; 
	    binfo.biHeight=320;
	    for(i=0;i<320;i++){
	   	  for(j=0;j<234;j++){
	   		bmp_Buf[i * 236 + 233 - j]=cRead[i + j * 320]; //bmp_ptr
	   	  }
		  bmp_Buf[i * 236 + 234]=bmp_Buf[i * 236 + 235]=0;
	    }
	}*/
       bmp_ptr=bmp_Buf;
       //bmp_ptr+= IMG_WIDTH * (IMG_HEIGHT -Real_HEIGHT);
       new_ptr=(char*)cRead;
       new_end_ptr=RGB_to_RLE(bmp_ptr, new_ptr, binfo.biWidth, binfo.biHeight);
       new_total=new_end_ptr - new_ptr;
       binfo.biCompression=1; //Compressed*/
       //new_total=236*320;
       bfile.bfSize=new_total+Date_start;
       binfo.biSizeImage=new_total;
       //memcpy(cRead, bmp_Buf, binfo.biSizeImage);
      
        bmp_buf_ptr=bmp_Buf;
        WriteBMPBuf(sizeof(bfile), (BYTE *)&bfile);
        WriteBMPBuf(sizeof(binfo), (BYTE *)&binfo);
        WriteBMPBuf(sizeof(aColor_Set), (BYTE *)&aColor_Set);
        WriteBMPBuf(new_total, (BYTE *)&cRead);
        //WriteFile((void*)&cRead, bfile.bfSize, NowFileName);
        sprintf(temp_fname, "%s\\%s", FMnowPath, NowFileName);
        Bmp_File=FS_FOpen(temp_fname,"wb");
        /*//Write Header
        FS_FWrite((void *)&bfile, sizeof(char), sizeof(bfile), Bmp_File);
        //Write Information
        FS_FWrite((void *)&binfo, sizeof(char), sizeof(binfo), Bmp_File);
        //Write LUT for 8bpp Indexed Color   
        FS_FWrite((void *)&aColor_Set, sizeof(long), COLOR_SIZE, Bmp_File);
        //Write Data
        FS_FWrite(new_ptr, sizeof(char), binfo.biSizeImage, Bmp_File);
        //FS_FWrite(bmp_ptr, sizeof(char), binfo.biSizeImage, Bmp_File);
     	  */
        FS_FWrite((void *)&bmp_Buf, sizeof(char), bfile.bfSize, Bmp_File);
        FS_FClose(Bmp_File);
    #ifdef DEBUG_MODE //test write to PC
        //printf("Write File test\n");
        Bmp_File=FS_FOpen(temp_fname,"rb");
        FS_FRead(cRead, sizeof(char), bfile.bfSize, Bmp_File);
        FS_FClose(Bmp_File);
        //if(Mode==1)
        	//sprintf(NowFileName, "%s.bmp", AllFileDir);
        PC_File=fopen(NowFileName, "wb");
        fwrite(cRead, sizeof(char), bfile.bfSize, PC_File);
        fclose(PC_File);
    #endif   
   
   }
   else{
   	;
   }
   return 0;
}
/*
void test_jpeg()
{
	tJpegEncoder	   			*lBaseJpegEnc = NULL;
	tJpegParam		   			lImageEncParam = { 0 };
    
	lBaseJpegEnc = JPEG_Encoder_NEW(&lImageEncParam);

}
//*/
void WriteBMPBuf(ULONG length, BYTE* source)
{
   ULONG  i;

   for(i=0;i<length;i++)
       *bmp_buf_ptr++=*source++;
}
//#pragma optimize_off

BYTE RecallBmpBuf()
{
    char temp_fname[maxdirlen];
    UBYTE temp_uc;
    UBYTE power_x=0, temp_x1, temp_x2;
    WORD x, y;
    LONG FileSize;
    FS_FILE *Image_File;
    BYTE Compression;
    FILE *PC_File; //test write to PC
    
    sprintf(temp_fname, "%s\\%s", FMnowPath, NowFileName);
    if( (Image_File=FS_FOpen(temp_fname, "rb") )==0){
    	//HintDelay("WaveForm File can't open");
 	return 0;
    }
    else{
 	 //get File Size
        FS_FSeek(Image_File, 0, FS_SEEK_END);
        FileSize=FS_FTell(Image_File);	
        FS_FSeek(Image_File, 0, SEEK_SET);
        
        if(FileSize>75958){ //75958=320*234+1078  82998=320*256+1078 
            FS_FClose(Image_File);
            return 0;
        }
        FS_FRead(head_buf, sizeof(char), HEAD_SIZE, Image_File);
        if( head_buf[0]!=0x42 || head_buf[1]!=0x4d //bfile.bfType=0x4d42; //offset 0 = 0x42, 1 = 0x4d
         || head_buf[10]!=0x36 || head_buf[11]!=0x04 || head_buf[12]!=0x00 // bfile.bfOffBits=1078; //offset 10 = 0x36, 11 = 0x04, 12 = 0x00
         || head_buf[18]!=0x40 || head_buf[19]!=0x01 // binfo.biWidth=320; //offset 18 = 0x40, 19 = 0x01
         || head_buf[22]!=0xea || head_buf[23]!=0x00 //binfo.biHeight=234; //offset 22 = 0xea, 23 = 0x00
         || head_buf[28]!=0x08 || head_buf[29]!=0x00 //binfo.biBitCount=8; //8bpp offset 28 = 0x08, 29 = 0x00
         || head_buf[0x276]!=0x00 ||(head_buf[0x277]!=0xff && head_buf[0x277]!=0xb1)|| head_buf[0x278]!=0xff //color yellow
         ||(head_buf[0x27a]+head_buf[0x27b]+head_buf[0x27c]!=0 && head_buf[0x27a]+head_buf[0x27b]+head_buf[0x27c]!=0x2fd ) ){ //color white or black ff+ff+ff=2fd
            FS_FClose(Image_File);
            return 0;
        }
        Compression=head_buf[30]; //binfo.biCompression=0; //none Compressed offset 30 = 0x00 */
        if( (Compression !=0) && (Compression !=1) ){
            FS_FClose(Image_File);
            return 0;
        }
        //FS_FClose(Image_File);return 1;//test
        FileSize-=HEAD_SIZE;
        FS_FRead(bmp_Buf, sizeof(char), FileSize, Image_File);
        FS_FClose(Image_File);
        if(Compression==1)
            RLE_to_RGB(bmp_Buf, cRead, IMG_WIDTH, Real_HEIGHT);
        else
            memcpy(cRead, bmp_Buf, FileSize);

        if( (SAVEREC.Ref_Image_Status==TRACE_AVAILABLE) && (SAVEREC.Ref_Image_On_Off==ON) ){
            ClearRefImage();
            MarkRedrawFlag|=(HOR_MARK+TRIG_MARK);
        }
        for(y=0;y<200;y++)
            for(x=0;x<250;x++)
                Ref_Image_buf[x][y]=0;
        
        for(y=0;y<200;y++){
            for(x=0;x<250;x++){
                temp_uc=cRead[x + 10 + (Real_HEIGHT - y - 11) * IMG_WIDTH];
                if( (temp_uc==GW_YELLOW) || (temp_uc==Cur_Color_white) ){
                    temp_x1=1<<(x%8);
                    temp_x2=x/8;
                    Ref_Image_buf[temp_x2][y]+=temp_x1;
                    //CursorSetPixel_A2(x + 4, y + 2, Cursor2Col2);
                }
            }
        }
        SAVEREC.Ref_Image_Status=TRACE_AVAILABLE;
        SAVEREC.Ref_Image_On_Off=ON;
        WRFlashData(DFlashWriteRefImage);
        DrawRefImage();
        MenuRedrawFlag|=MENU2_CHANGE;
        return 1;
    }
 
}

BYTE Image_Disp(BYTE menu_no, BYTE item_no)
{
    UBYTE power_x=0, temp_x1, temp_x2;
    WORD x, y;
    
    switch(item_no){
        case P_SOFT3:
            if(SAVEREC.Ref_Image_On_Off==ON){
               if(SAVEREC.Ref_Image_Status==TRACE_EMPTY){
                    SAVEREC.Ref_Image_On_Off=OFF;
                    MenuRedrawFlag|=MENU2_CHANGE;
                    return 0;
                }
                ClearRefImage();
                SAVEREC.Ref_Image_On_Off=OFF;
                MarkRedrawFlag|=(HOR_MARK+TRIG_MARK);
                Old_Ref_Image_Status=OFF;
             }
            else if(SAVEREC.Ref_Image_On_Off==OFF){
                SAVEREC.Ref_Image_On_Off=ON;
                if(SAVEREC.Ref_Image_Status==TRACE_EMPTY){
                    MenuRedrawFlag|=MENU2_CHANGE;
                    return 0;
                }
                DrawRefImage();
            }
            MenuRedrawFlag|=MENU2_CHANGE;
            break;
    }
    return 1;
}

void DrawRefImage(void)
{
    UBYTE power_x=0, temp_x1, temp_x2;
    WORD x, y;
    if( (SAVEREC.Ref_Image_Status==TRACE_AVAILABLE) && (SAVEREC.Ref_Image_On_Off==ON) ){
        for(y=0;y<200;y++){
            for(x=0;x<32;x++){
                power_x=0;
                temp_x1=Ref_Image_buf[x][y];
                while(temp_x1>0){
                    temp_x2=temp_x1%2;
                    if(temp_x2==1)
                        CursorSetPixel_A2(x * 8 + power_x + 4, y + 2, Cursor2Col2);
                    temp_x1=temp_x1>>1;
                    power_x++;
                }
            }
        }
        CtrlFlag|=CHANNEL_MARK_CHANGE;
    }
}

void ClearRefImage(void)
{
    if( (SAVEREC.Ref_Image_Status==TRACE_AVAILABLE) && (SAVEREC.Ref_Image_On_Off==ON) ){
        SAVEREC.Ref_Image_On_Off=OFF;
        ClearCursor2();
        RedrawMark(0,1);
        RedrawMark(1,1);
        RedrawMark(2,1);
        CtrlFlag|=CHANNEL_MARK_CHANGE;
        //MarkRedrawFlag|=(HOR_MARK+TRIG_MARK);
    }
}

void RefImageProc(void)
{
    if(SAVEREC.Ref_Image_Status==TRACE_EMPTY)
        return;
    
    if(RefImageFlag&RefImage_Clear){
        RefImageFlag&=~RefImage_Clear;
        if(SAVEREC.Ref_Image_On_Off==ON){
            Old_Ref_Image_Status=ON;
            ClearRefImage();
        }
    }
    if(RefImageFlag&RefImage_Draw){
        RefImageFlag&=~RefImage_Draw;
        DrawRefImage();
    }
    if(RefImageFlag&RefImage_Redraw){
        RefImageFlag&=~RefImage_Redraw;
        if( (Old_Ref_Image_Status==ON) 
            && ( (MEASMENU.DispAll==DISPALL_OFF) ||( M_num>=P_SavSetFile && M_num<=P_RecImg) ) ){
        //if(Old_Ref_Image_Status==ON){
            Old_Ref_Image_Status=OFF;
            SAVEREC.Ref_Image_On_Off=ON;
            DrawRefImage();
            MenuRedrawFlag|=MENU2_CHANGE;
        }
    }
    
}

char* RGB_to_RLE(char *bmp_ptr, char *new_ptr, unsigned int Width, unsigned int Height)
{
   unsigned char count=1;
   unsigned int Wcount=1;
   char W_4_comp; //Width 4 complement
   char *bmp_total_ptr;

   //*(new_ptr -Date_start+B_Compression)=1;
   W_4_comp=Width%4;
   if(W_4_comp!=0)
       W_4_comp=4-W_4_comp;

   bmp_total_ptr=bmp_ptr + Width*Height;
   while(bmp_ptr < bmp_total_ptr){
	if(Wcount>=Width){
		 if( (count>1)  || ( *(bmp_ptr)!=*(bmp_ptr-1) ) ){
	    	 	*(new_ptr++)=count;
	    	 	*(new_ptr++)=*(bmp_ptr);
	    		count=1;
		 }
		 *(new_ptr++)=0;
		 *(new_ptr++)=0;
		 Wcount=0;
		 bmp_ptr+=W_4_comp;
	}
	else if( *(bmp_ptr)==*(bmp_ptr+1) ){
	    count++;
	    if(count==0xff){
	    	 *(new_ptr++)=count;
	    	 *(new_ptr++)=*(bmp_ptr);
	    	 count=1;
		 bmp_ptr++;
		 Wcount++;
	    }
	}
	else{
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

char* RLE_to_RGB(char *bmp_ptr, char *new_ptr, unsigned int Width, unsigned int Height)
{
   unsigned char count;
   unsigned int Wcount=1;
   char W_4_comp; //Width 4 complement
   char Even_Odd;
   char *bmp_total_ptr;

   *(new_ptr -Date_start+B_Compression)=0;
   W_4_comp=Width%4;
   if(W_4_comp!=0)
       W_4_comp=4-W_4_comp;

   bmp_total_ptr=bmp_ptr + Width*Height;
   while(bmp_ptr < bmp_total_ptr){
   	if( *(bmp_ptr)==0){
	    if( *(bmp_ptr+1)==1){
	    	 count=W_4_comp;
	    	 for( ; count>0; count--)
		     *(new_ptr++)=0;
		 return(new_ptr);
	    }
	    else if( *(bmp_ptr+1)==0){ //next line
	    	 count=W_4_comp;
	    	 for( ; count>0; count--)
		      *(new_ptr++)=0;
		 bmp_ptr+=2;
	    }
	    else if( *(bmp_ptr+1)>=3){
	    	 count=*(++bmp_ptr);
		 bmp_ptr++;
		 Even_Odd=count%2;
	    	 for( ; count>0; count--){
	    	      *(new_ptr++)=*(bmp_ptr++);
	    	 }
		 if(Even_Odd)
		      bmp_ptr++;
	    }
	    else{
		 printf("File is wrong BMP");
	    }
   	}
   	else{
	    count=*(bmp_ptr++);
	    for( ; count>0; count--){
	    	  *(new_ptr++)=*(bmp_ptr);
	    }
	    bmp_ptr++;
   	}
   }
   return(0);
}
