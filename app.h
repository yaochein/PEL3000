/*******************************************************************************
*							µCOS-II Blackfin port test example
*							Blackfin Applications Team, Analog Devices Inc.,
*								Norwood, MA, US
*
* File: 				app.h
* Author: 				Deep Bodapati 
* Last Modified: 		10-22-2006
* Project:				µCOS-II Blackfin port test example
* Platform: 			ADSP-BF533 EZKit Lite Evaluation Board (silicon rev 0.4 and higher)
* Tools:				VisualDSP++ 4.5 (Updated September 2006)
* µCOS-II Version: 		v2.83
*																			
* Note: The user LEDs on the ADSP-BF533 EZKit Lite Evaluation Board are labeled
* LEDs #4 through 9. On the other hand, the user LEDs on the ADSP-BF537 EZKit 
* Lite Evaluation Board are labeled LEDs #1 through 6. For uniform software 
* naming convention, the LEDs are labeled LEDs# 1 through 6 for both EZKits.
* 
* This file is part of the test example, Ex1, of the µCOS-II port to the
* Blackfin processor. The test launches a boot thread, which in turn launches 
* 4 threads of priorities 6, 7, 8 and 9 blink LEDs# 2, 3, 4 and 5 on the 
* ADSP-BF533 EZKit Lite Evaluation Board and yield the processor by sleeping 
* for 7, 8, 9 and 10 ticks respectively (thus effectively blinking the LEDs). 
* In addition, the boot thread also launches two threads of priorities 5 
* and 10 that blink LEDs# 1 and 6 controlled through the push-button switches 
* SW4 and SW5 respectively.
******************************************************************************/
/*
Copyright...

This code is placed in the public domain, and can be distributed freely with no restrictions provided that the heading
of each source module file is not modified to remove the credit to the original author.
  
Disclaimer...

This program code is provided "as is". There is no warranty, either expressed or implied as to its fitness for use in
any application. It is provided only as an example of porting the MicroC/OS operating system to the Blackfin processor.
Its use is strictly at the risk of the user. The author will not be liable for any damages direct or consequential related
to the use of this software including, but not limited to loss of profit.
*/
#ifndef APP_H
#define APP_H

#if defined(_LANGUAGE_ASM)

#define OS_ADI_IVG11_ISR_Type 	OS_ADI_NonReentrant_ISR
#define OS_ADI_IVG12_ISR_Type 	OS_ADI_NonReentrant_ISR


#else /* (_LANGUAGE_C) */

#include <includes.h>
/*********************************************************************
Defintions/Typedefs
*********************************************************************/
#define STACK_SIZE 			(4000)		// stack size in # of entries
typedef struct task_params_list
{
	int LED;
	OS_EVENT *event;
}task_params_list_t;



/*********************************************************************
Global variables
*********************************************************************/

/*********************************************************************
Function prototypes
*********************************************************************/
extern void app_init (void);
extern void app_main (void);
extern void app_launch_threads (void);
extern void IVG12_ISR_Hook(void);
extern void SW5_push_button_Callback (void);
EX_INTERRUPT_HANDLER (IVG12_ISR);

#endif /* (_LANGUAGE_C) */

#endif /* APP_H */
