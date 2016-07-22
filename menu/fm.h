#ifndef FM_H
#define FM_H
#define maxfreelen 10	/*�����Ѿl�Ŷ���max length*/
#define maxdirlen 120		/*�������|���r��max length*/
//#define maxshowdir 25	/*�e���W��ܸ��|��max length*/
#define maxshowdir 30	/*Max length for path display.*/
#define maxshowsrdir 7	/*Max length for save / recall path display.*/
#define maxshowfiledir 12	/*Max length for save / recall path display.*/

#define FileMax 1000  /*   not including "usb:\" and "..\"        */

extern char mybuffer[];
extern UBYTE KeypadSubSTR[];
//extern UWORD Sort_F[];
extern UBYTE KeypadSTR[];

/*File system command flag define for FMinfo.*/
#define FM_READ_DEVICE				0x0002  /*read device again (change directory , delete) */
#define FM_RENAME					0x0008  /*Rename a file or directory*/
#define FM_RMDIR					0x0010  /*Remove a directory.*/
#define FM_REMOVE					0x0020  /*Delete a file.*/
#define FM_MKDIR					0x0040  /*Create a new directory.*/
#define FM_DEL_CONFIRM				0x0200  /*Delete confirm*/
#define FM_UPG_CONFIRM				0x1000  /*Upgrade confirm for *.upg*/
#define FM_PLUGIN_READ				0x2000  /*do it when plugin*/ 
#define FM_MNT_CONFIRM    		    0x4000  /*Upgrade confirm for monitor.mnt*/
#define FM_FPG_CONFIRM    		    0x4000  /*Upgrade confirm for monitor.mnt*/
#define FM_IPC_CONFIRM        		0x10000  /*Upgrade confirm for initpic.ipc*/


/*File manager display flag define for FM_InfoFlag.*/
#define FM_NO_DISPLAY				0x0001  /*Do not show space, directory, file list, scroll bar..., but error message do.*/
#define FM_SHOW_INIT				0x0002  /*File manager display initialization.*/
#define FM_SHOW_FREE_SPACE			0x0004  /*Show free space.*/
#define FM_SHOW_PATH				0x0008  /*Show directory.*/
#define FM_SHOW_FILE_LIST			0x0010  /*Show file name list.*/
#define FM_SHOW_SCROLL_BAR			0x0020  /*Show scroll bar.*/
#define FM_SHOW_FOLDER_FILE_NUM		0x0040  /*Show the total number of files and folders.*/
#define FM_SHOW_KEYPAD				0x0080  /*Show keypad.*/
#define FM_SHOW_DEVICE_ERROR		0x0100  /*Show device error message. (device hardware error....)*/
#define FM_DEVICE_ERROR_TAG			0x0200  /*A tag indicate that once a device error occurred.*/
#define FM_SHOW_OPERATION_ERROR		0x0400  /*Show operation error message.(disk full.....)*/
#define FM_OPERATION_ERROR_TAG		0x0800	/*A tag indicate that once a operation error occurred.*/
#define FM_SHOW_READING				0x1000	/*when reading data from usb*/
#define FM_SHOW_ALL					0x2000  /* display all */
#define FM_CHANGE_PAGE				0x4000  /* display all */
#define FM_SHOW_Message				0x8000  /* display Message */

typedef struct{/*27 bytes*/
    BYTE my_type;/*1:folder  0:file*/
    char my_name[13];
    LONG my_size;
    UWORD my_year;
    char my_month[13];
    UWORD my_day;
    UWORD my_hour;
    UWORD my_min;
    //UWORD my_sec;
}FMfilestru[FileMax+2];/*including ram:\  &  ..\    */

typedef struct
{
UWORD DispStartPos;/*�e���W�Ĥ@���ɮ׬O�Ҧ��ɮת��ĴX��*/
WORD SelPtr;/*�ثe���V�Ҧ��ɮת��ĴX��*/
UWORD ColDef;/*�ثe��ܪ��ɮ��C��ϧO   1:�ϥ�   0:���ϥ�*/
UBYTE fPreFlag;/*���s��ܤW�@���Q���(�ϥ�)���ɮ�*/
UBYTE fRollFlag;/*��sroll bar  �P  ���s��ܩҦ��ɮ�(�Ĥ@����ܩεe������)
				�p�G��0 , �ȧ�s�W�����(�����ϥ�)�P�o�����(�ݭn�ϥ�)���ɮ�*/
UWORD TotalFiles;/*�����|�ɮ׭Ӽ�,folder and file*/
WORD FolderVal;/*folder �Ӽ�*/
WORD FileVal;/*file �Ӽ�*/ 
} FMvar;
//Global Vars
#ifdef FM_GLOBALS
#define FM_EXT
#else
#define FM_EXT extern
#endif

FM_EXT unsigned long FMinfo;

#endif
