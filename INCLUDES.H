#define   BF531         1           /* CPU define                                                   */
#define   MODULE_COMMBUF2  1           /*    Real-Time Kernel      buffered serial I/O                 */
#define   MODULE_DIO       1           /* Discrete I/O module                                          */
#define   MODULE_FPGADL    1         /* FPGA Download module*/
#define   MODULE_GUI     1
#define   MODULE_GPIB    1
#define   MODULE_BFUART  1
#if MODULE_BFUART
#define USE_DD_SSL
#endif

#if defined(_LANGUAGE_ASM)
//#define OS_ADI_IVG12_ISR_Type 	OS_ADI_Reentrant_ISR
#else /* (_LANGUAGE_C) */

/*
*********************************************************************************************************
*                                              DATA TYPES
*********************************************************************************************************
*/
#ifndef DATA_TYPES
#define DATA_TYPES
typedef unsigned char  UBYTE;					 /* Unsigned  8 bit quantity						   */
typedef unsigned char  UCHAR;
typedef signed	 char  BYTE;					 /* Signed	  8 bit quantity						   */
typedef unsigned short UWORD;					 /* Unsigned 16 bit quantity						   */
typedef signed	 short WORD;					 /* Signed	 16 bit quantity						   */
typedef unsigned long  ULONG;					 /* Unsigned 32 bit quantity						   */
typedef signed long    LONG;					 /* Signed   32 bit quantity							 */
typedef float FP;						/* Single precision floating point					  */
typedef double	DFP;				
#endif
/*
*********************************************************************************************************
*										  Standard Libraries 
*********************************************************************************************************
*/
#include <stdlib.h>
#include <stdio.h>
#include <STRING.H>
#include <CTYPE.H>

/*
*********************************************************************************************************
*                                            CPU Header Files
*********************************************************************************************************
*/
#if         BF531
//--------------------------------------------------------------------------//
// Header files																//
//--------------------------------------------------------------------------//
/******** Processor specific ********/
#include <sys\exception.h>
#include <cdefBF533.h>
#include <cdefBF53x.h>
#include <ccblkfn.h>
#include <signal.h>
#include <sys/exception.h>
#include <sys/05000311.h>
#include "./drivers/Bf533_rtc.h"

#endif

/*
*********************************************************************************************************
*                                            uC/OS Header Files
*********************************************************************************************************
*/

#include <ucos_ii.h>
#include "ucos_ii_boot.h"

/*
*********************************************************************************************************
*                                            Module Header Files
*********************************************************************************************************
*/
	// Define System Constants
#if SCLK_50Mhz
#define XTAL_FREQ	25000000		/*	25MHz Xtal			*/
#define VCO_FREQ	(XTAL_FREQ*16)	/*	PLL * 16  = 400MHz	*/
#define SYS_CLOCK   (VCO_FREQ/8)	/*	50MHz				*/
#else
#define XTAL_FREQ	40000000		/*	40MHz Xtal			*/
#define VCO_FREQ	(XTAL_FREQ*10)	/*	PLL * 10  = 400MHz	*/
#define SYS_CLOCK   (VCO_FREQ/4)	/*	100MHz				*/
#endif
#define CORE_CLOCK 	(VCO_FREQ/1)	/*	400Mhz				*/


#include    "./menu/menu.h"
#include    "./menu/head.h"
#include    "./interfaces.h"
#include    "./menu/fm.h"
#if         MODULE_DIO
#include    "./dio/DIO.H"
#endif

#if         MODULE_COMMBUF2
#include    "./comm/COMMBUF2.H"
#include    "./comm/comm_bf533.h"
#include    "./comm/comm_fpga.h"
#endif

#if         MODULE_FPGADL
#include    "./fpgadl/fpgadl_ss.h"
#endif
#if         MODULE_GUI
#include    "./GUI/GWColor.h"
#include    "./GuiX/lcd13xx.h"
#include    "./GuiX/gwlcd.h"
#include    "./GuiX/ssd1906.h"
#include    "./GUI/GUI.h"
#include    "./GUI/LCD.H"
#include    "./Config/LCDConf.h"
#endif
#if         MODULE_GPIB
#define GPIB_RX_BUF_SIZE CommData_Size
#define GPIB_TX_BUF_SIZE CommData_Size
#define  CMD_QSIZE             255                /*Added by Ching-kai Meng 2003.06.03                  */

#include     "./gpib/gpibbuf.h"
#include     "./gpib/nat9914.h"
#endif

#endif /* (_LANGUAGE_C) */


