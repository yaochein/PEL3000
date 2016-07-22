#ifndef SAVREC_H
#define SAVREC_H

#define WaveMain  0
#define WaveZoom 1
#define WaveRoll    2
#define WaveScan  3
#define WaveXY      4

#define DFlash_WavePageSize 50
#define DFlash_RefImagePageSize 15
#define DFlash_PrinterPageSize 10
#define DFlash_SetupStart 0
#define DFlash_RefStart DFlash_SetupStart + MemSetupTotal
#define DFlash_Program DFlash_RefStart + DFlash_WavePageSize * TotalWaveCell
#define DFlash_Printer DFlash_Program + 1
#define DFlash_RefImage DFlash_Printer + DFlash_PrinterPageSize
#define DFlash_MemWaveStart DFlash_RefImage + DFlash_RefImagePageSize

#define DFlashReadSetup             0x00001
#define DFlashReadRef                 0x00002
#define DFlashReadMemWave       0x00004
#define DFlashReadMemWaveInfo 0x00008
#define DFlashReadGonogoMax     0x00010
#define DFlashReadGonogoMin      0x00020
#define DFlashReadAll                   0x00080

#define DFlashWriteSetup             0x00100
#define DFlashWriteRef                 0x00200
#define DFlashWriteMemWave       0x00400
#define DFlashWriteMemWaveInfo 0x00800
#define DFlashWriteGonogo           0x01000
#define DFlashWriteProgram          0x04000
#define DFlashWritePrinter           0x08000
#define DFlashWriteRefImage       0x10000

#define RefImage_Clear     0x01
#define RefImage_Draw     0x02
#define RefImage_Redraw  0x04

//#define USBNumerTotal 10000
#define SOUR_FFT 5
#define SOUR_GONOGO 6
#define SetupFileSize sizeof(RSSETUP)
#define SetupFileSize_new	sizeof(LPSETUP)

#define USB_NotExist 0
#define USB_Busy 1
#define USB_Exist 2

#define USB_PrintFree 4
#define USB_PrintBusy 5

#define DoNothing 0
#define ReturnMenu 1
#define RecallFile 2
#define RedrawSRMenu 1

#define DispLongRefWaveSize 15000
#define DispLongMemWaveSize 12500

#define TmplMax 0
#define TmplMin 1
#define TmplAuto 2
#define TmplWaveSize 250

#define GNWaveClr        0x0001
#define TmplIni              0x0002
#define TmplIniFin         0x0004
#define TmplBackup       0x0008
#define TmplBackupFin  0x0010

#define Parameter_NR3  3
#define Para_NR3_SaveFile  4

#define Utility_USB_CDC   0
#define Utility_USB_TMC   1

typedef struct{
    WORD POS;  //The original GND position of saved channel
    WORD Offset;  // The adjustable offset changed by user.
    
    //UBYTE Status;  //0:none waveform 1:have waveform
    UWORD WaveLength;
    char      TriggerLevel[12];
    char    TimeBase[8];  /* Main Time Base Index value IDX refer to   SEC_DATA*/
    char    V_Div[8];
    BYTE   Prob; // 0: x1 , 1: x10 , 2: x100
    BYTE   Coupling;     /*Range:0->DC,  1->AC  2->GND*/
    BYTE   Chan;    /*Which trace saved here. 0:CH1, 1:CH2, 2:CH3, 3:CH4, 4:MATH, 5:FFT 6:GONOGO*/
    BYTE   Hor_Mode; //0:Main , 1:Windows Zoom , 2: Roll , 3: Scan , 4: X-Y
    WORD LastDotAddr; //Waveform Last Dot Address
    char    Hor_Pos_Str[12];  //H_POS_STR;
    char    Time_Str[18];
    float    DotNumPerColumn;      //The real sample points on each column of screen.
    BYTE   INTP_MODE; //Interpolation mode: 0:Real time(sinc), 1:ET
    UBYTE   Checksum; //default 0xa5
    WORD   Reserve;
	
    UBYTE WaveS[25000];
}SaveRec_WaveData;

typedef struct{
    //WORD POS;  //The original GND position of saved channel
    //WORD Offset;  // The adjustable offset changed by user.
    char      TimeBase[8];  /* Main Time Base Index value IDX refer to   SEC_DATA*/
    char      V_Div[8];
    UWORD WaveLength; //500, 25k
    BYTE     LoadDFlashInfo; // 0: No Data , 1: Loaded Data Flash Memeory WaveForm TimeBase and V_Div
    BYTE     Tmpl_Status; //  0: No Data , 1:Drew GONOGO Template form M1~M20
    //UBYTE  Template[250];
}SR_MemWaveTemp;

typedef struct{
    WORD POS;  //The original GND position of saved channel
    WORD Offset;  // The adjustable offset changed by user.
    UWORD WaveLength; //500, 25k
    BYTE   Hor_Mode; //0:Main , 1:Windows Zoom , 2: Roll , 3: Scan , 4: X-Y
    WORD LastDotAddr; //Waveform Last Dot Address
    float    DotNumPerColumn;      //The real sample points on each column of screen.
    BYTE   Reserve1;
    UBYTE WaveS[DispLongMemWaveSize];
}Template_MaxMinData;

#endif   /* ifdef SAVREC_H */
