/***********************************************************************************
 *    This file is modified from GDS830 c3_msg.h
 *The content of structure of the type MITEMS is: 
 *     1. (MITEM *) 
 *     2. (Func) 
 *     3. variable for "n"th item display 
 *     4. the number of different items 
 *     5. variable for frame type     0:no frame  
 *                                    1:pop up and frame with separator  
 *                                    2:pop up and frame without separator  
 *                                    3:special frame
 *                                    4:softkey Pressed
 *                                    5:sub- menu arrow with separator
 *                                    6:next- menu arrow        
 *                                    7:pre- menu arrow
 ***********************************************************************************/
#include "../INCLUDES.H"  
#include "../menu/head.h"
#include "../bmp/bmp.h"
#include "../menu/menu_msg.h"
#include "help_msg.h"
#include "Keypad.h"
#include "menu_pro.h"
//#include "help_msg.h"

//extern vertical CH1, CH2;
//extern horsys   HORSYS;
//extern char CurrChanID;
//extern chan_str ChanID[8];

//MK_keypad

extern BYTE Empty_Func(BYTE menu_no, BYTE item_no);
extern BYTE KeyPadSave(BYTE n1, BYTE n2);
extern BYTE FMselect(BYTE n1, BYTE n2);
extern BYTE FMdelete(BYTE n1, BYTE n2);
extern BYTE Script_Funselect(BYTE chnum,BYTE x);
extern BYTE OptionUninstall(BYTE chnum, BYTE x);
extern char USB_Status;
extern char USB_Status_Display;
/****************************************************************/
/* The initial condition value of item blocks                   */
/****************************************************************/
/*English,Russan,Deutsch,Italiano,Francais,Finnish,Polish,Spanish,Chinese(s),Chinese(t),Korean*/ /*old*/

										/*English,0						Chinese(t),1						Chinese(s),2						Korean,3							Spanish,4							Russan,5							Japan,6							German,7							Polish,8							Italian,9						10								11*/
const MITEM Null_F1[]= {{0,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0}};
const MITEM Null_F2[]= {{64,205,	{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0}};
const MITEM Null_F3[]= {{128,205,	{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0}};
const MITEM Null_F4[]= {{192,205,	{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0}};
const MITEM Null_F5[]= {{256,205,	{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0}};

const MITEM _normal_mode[]={
					{0,205, 		{(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,		(GUI_BITMAP*)&bmmode,		(GUI_BITMAP*)&bmmode,		},0},	
					{0,224, 		{(GUI_BITMAP*)&bmcc,			(GUI_BITMAP*)&bmcc,				(GUI_BITMAP*)&bmcc,				(GUI_BITMAP*)&bmcc,				(GUI_BITMAP*)&bmcccv,			(GUI_BITMAP*)&bmcc,				(GUI_BITMAP*)&bmcc,				(GUI_BITMAP*)&bmcc,				(GUI_BITMAP*)&bmcc,				(GUI_BITMAP*)&bmcc,			(GUI_BITMAP*)&bmcc,			(GUI_BITMAP*)&bmcc,			},0},
					{0,224,			{(GUI_BITMAP*)&bmcr,			(GUI_BITMAP*)&bmcr,				(GUI_BITMAP*)&bmcr,				(GUI_BITMAP*)&bmcr,				(GUI_BITMAP*)&bmcrcv,			(GUI_BITMAP*)&bmcr,				(GUI_BITMAP*)&bmcr,				(GUI_BITMAP*)&bmcr,				(GUI_BITMAP*)&bmcr,				(GUI_BITMAP*)&bmcr,			(GUI_BITMAP*)&bmcr,			(GUI_BITMAP*)&bmcr,			},0},
					{0,224,			{(GUI_BITMAP*)&bmcv,			(GUI_BITMAP*)&bmcv,				(GUI_BITMAP*)&bmcv,				(GUI_BITMAP*)&bmcv,				(GUI_BITMAP*)&bmcv,				(GUI_BITMAP*)&bmcv,				(GUI_BITMAP*)&bmcv,				(GUI_BITMAP*)&bmcv,				(GUI_BITMAP*)&bmcv,				(GUI_BITMAP*)&bmcv,			(GUI_BITMAP*)&bmcv,			(GUI_BITMAP*)&bmcv,			},0},
					{0,224,			{(GUI_BITMAP*)&bmcp,			(GUI_BITMAP*)&bmcp,				(GUI_BITMAP*)&bmcp,				(GUI_BITMAP*)&bmcp,				(GUI_BITMAP*)&bmcpcv,			(GUI_BITMAP*)&bmcp,				(GUI_BITMAP*)&bmcp,				(GUI_BITMAP*)&bmcp,				(GUI_BITMAP*)&bmcp,				(GUI_BITMAP*)&bmcp,			(GUI_BITMAP*)&bmcp,			(GUI_BITMAP*)&bmcp,			},0}};

const MITEM _cal_mode[]={
					{0,205, 		{(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,			(GUI_BITMAP*)&bmmode,		(GUI_BITMAP*)&bmmode,		(GUI_BITMAP*)&bmmode,		},0},	
					{0,224, 		{(GUI_BITMAP*)&bmcc,			(GUI_BITMAP*)&bmcc,				(GUI_BITMAP*)&bmcc,				(GUI_BITMAP*)&bmcc,				(GUI_BITMAP*)&bmcc,				(GUI_BITMAP*)&bmcc,				(GUI_BITMAP*)&bmcc,				(GUI_BITMAP*)&bmcc,				(GUI_BITMAP*)&bmcc,				(GUI_BITMAP*)&bmcc,			(GUI_BITMAP*)&bmcc,			(GUI_BITMAP*)&bmcc,			},0},
					{0,224,			{(GUI_BITMAP*)&bmcr,			(GUI_BITMAP*)&bmcr,				(GUI_BITMAP*)&bmcr,				(GUI_BITMAP*)&bmcr,				(GUI_BITMAP*)&bmcr,				(GUI_BITMAP*)&bmcr,				(GUI_BITMAP*)&bmcr,				(GUI_BITMAP*)&bmcr,				(GUI_BITMAP*)&bmcr,				(GUI_BITMAP*)&bmcr,			(GUI_BITMAP*)&bmcr,			(GUI_BITMAP*)&bmcr,			},0},
					{0,224,			{(GUI_BITMAP*)&bmcv,			(GUI_BITMAP*)&bmcv,				(GUI_BITMAP*)&bmcv,				(GUI_BITMAP*)&bmcv,				(GUI_BITMAP*)&bmcv,				(GUI_BITMAP*)&bmcv,				(GUI_BITMAP*)&bmcv,				(GUI_BITMAP*)&bmcv,				(GUI_BITMAP*)&bmcv,				(GUI_BITMAP*)&bmcv,			(GUI_BITMAP*)&bmcv,			(GUI_BITMAP*)&bmcv,			},0},
					{0,224,			{(GUI_BITMAP*)&bmcp,			(GUI_BITMAP*)&bmcp,				(GUI_BITMAP*)&bmcp,				(GUI_BITMAP*)&bmcp,				(GUI_BITMAP*)&bmcp,				(GUI_BITMAP*)&bmcp,				(GUI_BITMAP*)&bmcp,				(GUI_BITMAP*)&bmcp,				(GUI_BITMAP*)&bmcp,				(GUI_BITMAP*)&bmcp,			(GUI_BITMAP*)&bmcp,			(GUI_BITMAP*)&bmcp,			},0},
					{0,224,			{(GUI_BITMAP*)&bmcxcv,			(GUI_BITMAP*)&bmcxcv,			(GUI_BITMAP*)&bmcxcv,			(GUI_BITMAP*)&bmcxcv,			(GUI_BITMAP*)&bmcxcv,			(GUI_BITMAP*)&bmcxcv,			(GUI_BITMAP*)&bmcxcv,			(GUI_BITMAP*)&bmcxcv,			(GUI_BITMAP*)&bmcxcv,			(GUI_BITMAP*)&bmcxcv,		(GUI_BITMAP*)&bmcxcv,		(GUI_BITMAP*)&bmcxcv,		},0},
					{0,224,			{(GUI_BITMAP*)&bmf_imon,		(GUI_BITMAP*)&bmf_imon,			(GUI_BITMAP*)&bmf_imon,			(GUI_BITMAP*)&bmf_imon,			(GUI_BITMAP*)&bmf_imon,			(GUI_BITMAP*)&bmf_imon,			(GUI_BITMAP*)&bmf_imon,			(GUI_BITMAP*)&bmf_imon,			(GUI_BITMAP*)&bmf_imon,			(GUI_BITMAP*)&bmf_imon,		(GUI_BITMAP*)&bmf_imon,		(GUI_BITMAP*)&bmf_imon,		},0},
					{0,224,			{(GUI_BITMAP*)&bmr_imon,		(GUI_BITMAP*)&bmr_imon,			(GUI_BITMAP*)&bmr_imon,			(GUI_BITMAP*)&bmr_imon,			(GUI_BITMAP*)&bmr_imon,			(GUI_BITMAP*)&bmr_imon,			(GUI_BITMAP*)&bmr_imon,			(GUI_BITMAP*)&bmr_imon,			(GUI_BITMAP*)&bmr_imon,			(GUI_BITMAP*)&bmr_imon,		(GUI_BITMAP*)&bmr_imon,		(GUI_BITMAP*)&bmr_imon,		},0},
					{0,224, 		{(GUI_BITMAP*)&bmext_v_cc,		(GUI_BITMAP*)&bmext_v_cc,		(GUI_BITMAP*)&bmext_v_cc,		(GUI_BITMAP*)&bmext_v_cc,		(GUI_BITMAP*)&bmext_v_cc,		(GUI_BITMAP*)&bmext_v_cc,		(GUI_BITMAP*)&bmext_v_cc,		(GUI_BITMAP*)&bmext_v_cc,		(GUI_BITMAP*)&bmext_v_cc,		(GUI_BITMAP*)&bmext_v_cc,	(GUI_BITMAP*)&bmext_v_cc,	(GUI_BITMAP*)&bmext_v_cc,	},0},
					{0,224, 		{(GUI_BITMAP*)&bmext_r_cc,		(GUI_BITMAP*)&bmext_r_cc,		(GUI_BITMAP*)&bmext_r_cc,		(GUI_BITMAP*)&bmext_r_cc,		(GUI_BITMAP*)&bmext_r_cc,		(GUI_BITMAP*)&bmext_r_cc,		(GUI_BITMAP*)&bmext_r_cc,		(GUI_BITMAP*)&bmext_r_cc,		(GUI_BITMAP*)&bmext_r_cc,		(GUI_BITMAP*)&bmext_r_cc,	(GUI_BITMAP*)&bmext_r_cc,	(GUI_BITMAP*)&bmext_r_cc,	},0}};

const MITEM _normal_irange[]={		/* PEL-1031 Parallel * 1 */			/* PEL-3070 Parallel * 1 */	   		/* PEL-3111 Parallel * 1 */	 		/* PEL-1033 Parallel * 1 */			/* PEL-1031 Parallel * 2 */			/* PEL-3070 Parallel * 2 */	   		/* PEL-3111 Parallel * 2 */	 		/* PEL-1033 Parallel * 2 */			/* PEL-1031 Parallel * 3 */			/* PEL-3070 Parallel * 3 */	   	/* PEL-3111 Parallel * 3 */	 	/* PEL-1033 Parallel * 3 */		/* PEL-1031 Parallel * 4 */		/* PEL-3070 Parallel * 4 */	   	/* PEL-3111 Parallel * 4 */	 	/* PEL-1033 Parallel * 4 */		/* PEL-1031 Parallel * 5 */		/* PEL-3070 Parallel * 5 */	   	/* PEL-3111 Parallel * 5 */	 	/* PEL-1033 Parallel * 5 */		/* PEL-3111 Booster * 1 */		/* PEL-3111 Booster * 2 */		/* PEL-3111 Booster * 3 */		/* PEL-3111 Booster * 4 */
					{64,205, 		{(GUI_BITMAP*)&bmirange,			(GUI_BITMAP*)&bmirange,			(GUI_BITMAP*)&bmirange,			(GUI_BITMAP*)&bmirange,			(GUI_BITMAP*)&bmirange,			(GUI_BITMAP*)&bmirange,			(GUI_BITMAP*)&bmirange,			(GUI_BITMAP*)&bmirange,			(GUI_BITMAP*)&bmirange,			(GUI_BITMAP*)&bmirange,		(GUI_BITMAP*)&bmirange,		(GUI_BITMAP*)&bmirange,		(GUI_BITMAP*)&bmirange,		(GUI_BITMAP*)&bmirange,		(GUI_BITMAP*)&bmirange,		(GUI_BITMAP*)&bmirange,		(GUI_BITMAP*)&bmirange,		(GUI_BITMAP*)&bmirange,		(GUI_BITMAP*)&bmirange,		(GUI_BITMAP*)&bmirange,		(GUI_BITMAP*)&bmirange,		(GUI_BITMAP*)&bmirange,		(GUI_BITMAP*)&bmirange,		(GUI_BITMAP*)&bmirange,	},0},	
					{64,224, 		{(GUI_BITMAP*)&bml6a,			(GUI_BITMAP*)&bml14a,			(GUI_BITMAP*)&bml21a,			(GUI_BITMAP*)&bmL1_5a,			(GUI_BITMAP*)&bml12a,			(GUI_BITMAP*)&bml14a,			(GUI_BITMAP*)&bml4_2a,			(GUI_BITMAP*)&bml12a,			(GUI_BITMAP*)&bml18a,			(GUI_BITMAP*)&bml21a,		(GUI_BITMAP*)&bml6_3a,		(GUI_BITMAP*)&bml18a,		(GUI_BITMAP*)&bml24a,		(GUI_BITMAP*)&bml2_8a,		(GUI_BITMAP*)&bml8_4a,		(GUI_BITMAP*)&bml24a,		(GUI_BITMAP*)&bml30a,		(GUI_BITMAP*)&bml30a,		(GUI_BITMAP*)&bml10_5a,		(GUI_BITMAP*)&bml30a,		(GUI_BITMAP*)&bml6_3a,		(GUI_BITMAP*)&bml10_5a,		(GUI_BITMAP*)&bml14_5a,		(GUI_BITMAP*)&bml18_9a,	},0},
					//{64,224,		{(GUI_BITMAP*)&bmm3_5a,			(GUI_BITMAP*)&bmm14a,			(GUI_BITMAP*)&bmm21a,			(GUI_BITMAP*)&bmm7a,			(GUI_BITMAP*)&bmm7a,			(GUI_BITMAP*)&bmm14a,			(GUI_BITMAP*)&bmm42a,			(GUI_BITMAP*)&bmm14a,			(GUI_BITMAP*)&bmm10_5a,			(GUI_BITMAP*)&bmm21a,		(GUI_BITMAP*)&bmm63a,		(GUI_BITMAP*)&bmm21a,		(GUI_BITMAP*)&bmm14a,		(GUI_BITMAP*)&bmm28a,		(GUI_BITMAP*)&bmm84a,		(GUI_BITMAP*)&bmm28a,		(GUI_BITMAP*)&bmm17_5a,		(GUI_BITMAP*)&bmm35a,		(GUI_BITMAP*)&bmm105a,		(GUI_BITMAP*)&bmm35a,		(GUI_BITMAP*)&bmm63a,		(GUI_BITMAP*)&bmm105a,		(GUI_BITMAP*)&bmm145a,		(GUI_BITMAP*)&bmm189a,	},0},
					{64,224,		{(GUI_BITMAP*)&bmh60a,			(GUI_BITMAP*)&bml14a,			(GUI_BITMAP*)&bml21a,			(GUI_BITMAP*)&bmh15a,			(GUI_BITMAP*)&bmh120a,			(GUI_BITMAP*)&bml14a,			(GUI_BITMAP*)&bmm42a,			(GUI_BITMAP*)&bmh120a,			(GUI_BITMAP*)&bmh180a,			(GUI_BITMAP*)&bml21a,		(GUI_BITMAP*)&bmm63a,		(GUI_BITMAP*)&bmh180a,		(GUI_BITMAP*)&bmh240a,		(GUI_BITMAP*)&bmm28a,		(GUI_BITMAP*)&bmm84a,		(GUI_BITMAP*)&bmh240a,		(GUI_BITMAP*)&bmh300a,		(GUI_BITMAP*)&bmh300a,		(GUI_BITMAP*)&bmm105a,		(GUI_BITMAP*)&bmh300a,		(GUI_BITMAP*)&bmm63a,		(GUI_BITMAP*)&bmm105a,		(GUI_BITMAP*)&bmm145a,		(GUI_BITMAP*)&bmm189a,	},0},
					{64,224,		{(GUI_BITMAP*)&bmh35a,			(GUI_BITMAP*)&bmh140a,			(GUI_BITMAP*)&bmh210a,			(GUI_BITMAP*)&bmh70a,			(GUI_BITMAP*)&bmh70a,			(GUI_BITMAP*)&bmh140a,			(GUI_BITMAP*)&bmh420a,			(GUI_BITMAP*)&bmh140a,			(GUI_BITMAP*)&bmh105a,			(GUI_BITMAP*)&bmh210a,		(GUI_BITMAP*)&bmh630a,		(GUI_BITMAP*)&bmh210a,		(GUI_BITMAP*)&bmh140a,		(GUI_BITMAP*)&bmh280a,		(GUI_BITMAP*)&bmh840a,		(GUI_BITMAP*)&bmh280a,		(GUI_BITMAP*)&bmh175a,		(GUI_BITMAP*)&bmh350a,		(GUI_BITMAP*)&bmh1050a,		(GUI_BITMAP*)&bmh350a,		(GUI_BITMAP*)&bmh630a,		(GUI_BITMAP*)&bmh1050a,		(GUI_BITMAP*)&bmh1450a,		(GUI_BITMAP*)&bmh1890a,	},0},
					{64,205,		{(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,		(GUI_BITMAP*)&bmnull_b,		(GUI_BITMAP*)&bmnull_b,		(GUI_BITMAP*)&bmnull_b,		(GUI_BITMAP*)&bmnull_b,		(GUI_BITMAP*)&bmnull_b,		(GUI_BITMAP*)&bmnull_b,		(GUI_BITMAP*)&bmnull_b,		(GUI_BITMAP*)&bmnull_b,		(GUI_BITMAP*)&bmnull_b,		(GUI_BITMAP*)&bmnull_b,		(GUI_BITMAP*)&bmnull_b,		(GUI_BITMAP*)&bmnull_b,		(GUI_BITMAP*)&bmnull_b,		(GUI_BITMAP*)&bmnull_b,	},0}};

const MITEM _normal_vrange[]={
					{128,205,		{(GUI_BITMAP*)&bmvrange,			(GUI_BITMAP*)&bmvrange,			(GUI_BITMAP*)&bmvrange,			(GUI_BITMAP*)&bmvrange,			(GUI_BITMAP*)&bmvrange,			(GUI_BITMAP*)&bmvrange,			(GUI_BITMAP*)&bmvrange,			(GUI_BITMAP*)&bmvrange,			(GUI_BITMAP*)&bmvrange,			(GUI_BITMAP*)&bmvrange,		(GUI_BITMAP*)&bmvrange,		(GUI_BITMAP*)&bmvrange,		},0},	
					{128,224,		{(GUI_BITMAP*)&bml15v,			(GUI_BITMAP*)&bml15v,			(GUI_BITMAP*)&bml15v,			(GUI_BITMAP*)&bml50v,			(GUI_BITMAP*)&bml15v,			(GUI_BITMAP*)&bml15v,			(GUI_BITMAP*)&bml15v,			(GUI_BITMAP*)&bml15v,			(GUI_BITMAP*)&bml15v,			(GUI_BITMAP*)&bml15v,		(GUI_BITMAP*)&bml15v,		(GUI_BITMAP*)&bml15v,		},0},
					{128,224,		{(GUI_BITMAP*)&bmh150v,			(GUI_BITMAP*)&bmh150v,			(GUI_BITMAP*)&bmh150v,			(GUI_BITMAP*)&bmh500v,			(GUI_BITMAP*)&bmh150v,			(GUI_BITMAP*)&bmh150v,			(GUI_BITMAP*)&bmh150v,			(GUI_BITMAP*)&bmh150v,			(GUI_BITMAP*)&bmh150v,			(GUI_BITMAP*)&bmh150v,		(GUI_BITMAP*)&bmh150v,		(GUI_BITMAP*)&bmh150v,		},0},
					{128,205,		{(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b, 		(GUI_BITMAP*)&bmnull_b, 		(GUI_BITMAP*)&bmnull_b, 		(GUI_BITMAP*)&bmnull_b, 		(GUI_BITMAP*)&bmnull_b, 		(GUI_BITMAP*)&bmnull_b, 		(GUI_BITMAP*)&bmnull_b, 		(GUI_BITMAP*)&bmnull_b, 		(GUI_BITMAP*)&bmnull_b, 	(GUI_BITMAP*)&bmnull_b, 	(GUI_BITMAP*)&bmnull_b, 	},0}};					

const MITEM _cal_range[]={
					{64,205, 		{(GUI_BITMAP*)&bmrange,			(GUI_BITMAP*)&bmrange,			(GUI_BITMAP*)&bmrange,			(GUI_BITMAP*)&bmrange,			(GUI_BITMAP*)&bmrange,			(GUI_BITMAP*)&bmrange,			(GUI_BITMAP*)&bmrange,			(GUI_BITMAP*)&bmrange,			(GUI_BITMAP*)&bmrange,			(GUI_BITMAP*)&bmrange,		(GUI_BITMAP*)&bmrange,		(GUI_BITMAP*)&bmrange,		},0},	
					{64,224, 		{(GUI_BITMAP*)&bmlow,			(GUI_BITMAP*)&bmlow,			(GUI_BITMAP*)&bmlow,			(GUI_BITMAP*)&bmlow,			(GUI_BITMAP*)&bmlow,			(GUI_BITMAP*)&bmlow,			(GUI_BITMAP*)&bmlow,			(GUI_BITMAP*)&bmlow,			(GUI_BITMAP*)&bmlow,			(GUI_BITMAP*)&bmlow,		(GUI_BITMAP*)&bmlow,		(GUI_BITMAP*)&bmlow,		},0},
//					{64,224,		{(GUI_BITMAP*)&bmmiddle,		(GUI_BITMAP*)&bmmiddle,			(GUI_BITMAP*)&bmmiddle,			(GUI_BITMAP*)&bmmiddle,			(GUI_BITMAP*)&bmmiddle,			(GUI_BITMAP*)&bmmiddle,			(GUI_BITMAP*)&bmmiddle,			(GUI_BITMAP*)&bmmiddle,			(GUI_BITMAP*)&bmmiddle,			(GUI_BITMAP*)&bmmiddle,		(GUI_BITMAP*)&bmmiddle,		(GUI_BITMAP*)&bmmiddle,		},0},
					{64,224,		{(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,		(GUI_BITMAP*)&bmhigh,		(GUI_BITMAP*)&bmhigh,		},0},
					{64,224,		{(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,			(GUI_BITMAP*)&bmhigh,		(GUI_BITMAP*)&bmhigh,		(GUI_BITMAP*)&bmhigh,		},0},
					{64,205,		{(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,			(GUI_BITMAP*)&bmnull_b,		(GUI_BITMAP*)&bmnull_b,		(GUI_BITMAP*)&bmnull_b,		},0}};

const MITEM _normal_stadyna[]={
					{192,205,		{(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		(GUI_BITMAP*)&bmfunction,		},0},	
					{192,224,		{(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	(GUI_BITMAP*)&bmstatic_64x16,	},0},	
					{192,224,		{(GUI_BITMAP*)&bmdyna_64x16,		(GUI_BITMAP*)&bmdyna_64x16,		(GUI_BITMAP*)&bmdyna,			(GUI_BITMAP*)&bmdyna,			(GUI_BITMAP*)&bmdyna,			(GUI_BITMAP*)&bmdyna,			(GUI_BITMAP*)&bmdyna,			(GUI_BITMAP*)&bmdyna,			(GUI_BITMAP*)&bmdyna,			(GUI_BITMAP*)&bmdyna,			(GUI_BITMAP*)&bmdyna,			(GUI_BITMAP*)&bmdyna,			(GUI_BITMAP*)&bmdyna_64x16,		(GUI_BITMAP*)&bmdyna_64x16,		(GUI_BITMAP*)&bmdyna,			(GUI_BITMAP*)&bmdyna,			(GUI_BITMAP*)&bmdyna,			(GUI_BITMAP*)&bmdyna,			(GUI_BITMAP*)&bmdyna,			(GUI_BITMAP*)&bmdyna,			},0}};

const MITEM _config_main[]={
					{256,205,		{(GUI_BITMAP*)&bmconfigure,		(GUI_BITMAP*)&bmconfigure,		(GUI_BITMAP*)&bmconfigure,		(GUI_BITMAP*)&bmconfigure,		(GUI_BITMAP*)&bmconfigure,		(GUI_BITMAP*)&bmconfigure,		(GUI_BITMAP*)&bmconfigure,		(GUI_BITMAP*)&bmconfigure,		(GUI_BITMAP*)&bmconfigure,		(GUI_BITMAP*)&bmconfigure,		(GUI_BITMAP*)&bmconfigure,		(GUI_BITMAP*)&bmconfigure,		},0}};	

const MITEM _cvcp_response[]={
					{192,205, 		{(GUI_BITMAP*)&bmresponse,		(GUI_BITMAP*)&bmresponse,		(GUI_BITMAP*)&bmresponse,		(GUI_BITMAP*)&bmresponse,		(GUI_BITMAP*)&bmresponse,		(GUI_BITMAP*)&bmresponse,		(GUI_BITMAP*)&bmresponse,		(GUI_BITMAP*)&bmresponse,		(GUI_BITMAP*)&bmresponse,		(GUI_BITMAP*)&bmresponse,		(GUI_BITMAP*)&bmresponse,		(GUI_BITMAP*)&bmresponse,		},0},	
					{192,224,		{(GUI_BITMAP*)&bmslow,			(GUI_BITMAP*)&bmslow,			(GUI_BITMAP*)&bmslow,			(GUI_BITMAP*)&bmslow,			(GUI_BITMAP*)&bmslow,			(GUI_BITMAP*)&bmslow,			(GUI_BITMAP*)&bmslow,			(GUI_BITMAP*)&bmslow,			(GUI_BITMAP*)&bmslow,			(GUI_BITMAP*)&bmslow,			(GUI_BITMAP*)&bmslow,			(GUI_BITMAP*)&bmslow,			},0},
					{192,224,		{(GUI_BITMAP*)&bmnormal,			(GUI_BITMAP*)&bmnormal,			(GUI_BITMAP*)&bmnormal,			(GUI_BITMAP*)&bmnormal,			(GUI_BITMAP*)&bmnormal,			(GUI_BITMAP*)&bmnormal,			(GUI_BITMAP*)&bmnormal,			(GUI_BITMAP*)&bmnormal,			(GUI_BITMAP*)&bmnormal,			(GUI_BITMAP*)&bmnormal,			(GUI_BITMAP*)&bmnormal,			(GUI_BITMAP*)&bmnormal,			},0},
					{192,224, 		{(GUI_BITMAP*)&bmfast,			(GUI_BITMAP*)&bmfast,			(GUI_BITMAP*)&bmfast,			(GUI_BITMAP*)&bmfast,			(GUI_BITMAP*)&bmfast,			(GUI_BITMAP*)&bmfast,			(GUI_BITMAP*)&bmfast,			(GUI_BITMAP*)&bmfast,			(GUI_BITMAP*)&bmfast,			(GUI_BITMAP*)&bmfast,			(GUI_BITMAP*)&bmfast,			(GUI_BITMAP*)&bmfast,			},0}};
					
const MITEM _gonogo_spec[]={
					{0,205, 		{(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			},0},	
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224,			{(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				},0}};

#if 0
const MITEM _test_Function[]={
					{0,215, 		{(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			},0}};
const MITEM _test2_Function[]={
					{64,215, 		{(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			},0}};
#else
const MITEM _test_Function[]={
					{0,205, 		{(GUI_BITMAP*)&bmselect,			(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		},0}};
					//{0,205, 		{(GUI_BITMAP*)&bmeasure,		(GUI_BITMAP*)&bmeasure,		(GUI_BITMAP*)&bmeasure,			(GUI_BITMAP*)&bmeasure,		GUI_BITMAP*)&bmeasure,			(GUI_BITMAP*)&bmeasure,		(GUI_BITMAP*)&bmeasure,		(GUI_BITMAP*)&bmeasure,		(GUI_BITMAP*)&bmeasure,		(GUI_BITMAP*)&bmeasure,		(GUI_BITMAP*)&bmeasure,		(GUI_BITMAP*)&bmeasure,		},0}};
const MITEM _savetool[]={				
					{64,205,		{(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			},0}};							
const MITEM _test2_Function[]={
					{64,205, 		{(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		},0}};
const MITEM _displayCal[]={
					{192,205,		{(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		(GUI_BITMAP*)&bmcal_data,		},0}};

#endif
const MITEM _test3_Function[]={
					{128,215, 		{(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			},0}};
const MITEM _test4_Function[]={
					{192,215, 		{(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			},0}};
const MITEM _test5_Function[]={
					{256,215, 		{(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			(GUI_BITMAP*)&bmtest,			},0}};										

const MITEM _gonogo_preval[]={
					{64,205, 		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			},0},	
					{64,205, 		{(GUI_BITMAP*)&bmvalue,			(GUI_BITMAP*)&bmvalue,			(GUI_BITMAP*)&bmvalue,			(GUI_BITMAP*)&bmvalue,			(GUI_BITMAP*)&bmvalue,			(GUI_BITMAP*)&bmvalue,			(GUI_BITMAP*)&bmvalue,			(GUI_BITMAP*)&bmvalue,			(GUI_BITMAP*)&bmvalue,			(GUI_BITMAP*)&bmvalue,			(GUI_BITMAP*)&bmvalue,			(GUI_BITMAP*)&bmvalue,			},0},	
					{64,205, 		{(GUI_BITMAP*)&bmpercent,		(GUI_BITMAP*)&bmpercent,		(GUI_BITMAP*)&bmpercent,		(GUI_BITMAP*)&bmpercent,		(GUI_BITMAP*)&bmpercent,		(GUI_BITMAP*)&bmpercent,		(GUI_BITMAP*)&bmpercent,		(GUI_BITMAP*)&bmpercent,		(GUI_BITMAP*)&bmpercent,		(GUI_BITMAP*)&bmpercent,		(GUI_BITMAP*)&bmpercent,		(GUI_BITMAP*)&bmpercent,		},0}};	

const MITEM _config_rvpclear[]={
					{128,205, 		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			},0},
					{128,205, 		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			},0},
					{128,205,		{(GUI_BITMAP*)&bmrvpclear,		(GUI_BITMAP*)&bmrvpclear,		(GUI_BITMAP*)&bmrvpclear,		(GUI_BITMAP*)&bmrvpclear,		(GUI_BITMAP*)&bmrvpclear,		(GUI_BITMAP*)&bmrvpclear,		(GUI_BITMAP*)&bmrvpclear,		(GUI_BITMAP*)&bmrvpclear,		(GUI_BITMAP*)&bmrvpclear,		(GUI_BITMAP*)&bmrvpclear,		(GUI_BITMAP*)&bmrvpclear,		(GUI_BITMAP*)&bmrvpclear,		},0},	
					{128,205, 		{(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		},0}};
				
const MITEM _seqedit[]={
					{128,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0},	
					{128,205, 		{(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		},0},
					{128,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0},
					{128,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0}};

const MITEM _config_proclear[]={
					{192,205, 		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			},0},
					{192,205, 		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			},0},
					{192,205, 		{(GUI_BITMAP*)&bmpclearall,		(GUI_BITMAP*)&bmpclearall,		(GUI_BITMAP*)&bmpclearall,		(GUI_BITMAP*)&bmpclearall,		(GUI_BITMAP*)&bmpclearall,		(GUI_BITMAP*)&bmpclearall,		(GUI_BITMAP*)&bmpclearall,		(GUI_BITMAP*)&bmpclearall,		(GUI_BITMAP*)&bmpclearall,		(GUI_BITMAP*)&bmpclearall,		(GUI_BITMAP*)&bmpclearall,		(GUI_BITMAP*)&bmpclearall,		},0},
					{192,205, 		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			},0}};
					
const MITEM _Prog_chain[]={
					{64,205, 		{(GUI_BITMAP*)&bmchain,			(GUI_BITMAP*)&bmchain,			(GUI_BITMAP*)&bmchain,			(GUI_BITMAP*)&bmchain,			(GUI_BITMAP*)&bmchain,			(GUI_BITMAP*)&bmchain,			(GUI_BITMAP*)&bmchain,			(GUI_BITMAP*)&bmchain,			(GUI_BITMAP*)&bmchain,			(GUI_BITMAP*)&bmchain,			(GUI_BITMAP*)&bmchain,			(GUI_BITMAP*)&bmchain,			},0}};	
	
const MITEM _prog_save[]={
					{128,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0},
					{128,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0},
					{128,205, 		{(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			},0}};

const MITEM _seq_save[]={
					{128,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0},
					{128,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0},
					{128,205, 		{(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			},0}};
					
#if Enable_fseq_deletAll					
const MITEM _fseq_edit_save[]={
					{128,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0},
					{128,205,		{(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,	(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,			(GUI_BITMAP*)&bmdeletall,		},0},			
					{128,205,		{(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			},0}};
					
					
#endif

const MITEM _seq_clearall[]={
					{128,205, 		{(GUI_BITMAP*)&bmclearall,		(GUI_BITMAP*)&bmclearall,		(GUI_BITMAP*)&bmclearall,		(GUI_BITMAP*)&bmclearall,		(GUI_BITMAP*)&bmclearall,		(GUI_BITMAP*)&bmclearall,		(GUI_BITMAP*)&bmclearall,		(GUI_BITMAP*)&bmclearall,		(GUI_BITMAP*)&bmclearall,		(GUI_BITMAP*)&bmclearall,		(GUI_BITMAP*)&bmclearall,		(GUI_BITMAP*)&bmclearall,		},0}};	

const MITEM _pre_menu[]={
					{256,205, 		{(GUI_BITMAP*)&bmpremenu,		(GUI_BITMAP*)&bmpremenu,		(GUI_BITMAP*)&bmpremenu,		(GUI_BITMAP*)&bmpremenu,		(GUI_BITMAP*)&bmpremenu,		(GUI_BITMAP*)&bmpremenu,		(GUI_BITMAP*)&bmpremenu,		(GUI_BITMAP*)&bmpremenu,		(GUI_BITMAP*)&bmpremenu,		(GUI_BITMAP*)&bmpremenu,		(GUI_BITMAP*)&bmpremenu,		(GUI_BITMAP*)&bmpremenu,		},0}};	

const MITEM _prog_editstart[]={
					{0,205, 		{(GUI_BITMAP*)&bmeditstart,		(GUI_BITMAP*)&bmeditstart,		(GUI_BITMAP*)&bmeditstart,		(GUI_BITMAP*)&bmeditstart,		(GUI_BITMAP*)&bmeditstart,		(GUI_BITMAP*)&bmeditstart,		(GUI_BITMAP*)&bmeditstart,		(GUI_BITMAP*)&bmeditstart,		(GUI_BITMAP*)&bmeditstart,		(GUI_BITMAP*)&bmeditstart,		(GUI_BITMAP*)&bmeditstart,		(GUI_BITMAP*)&bmeditstart,		},0}};	

const MITEM _trig_in[]={
					{256,205, 		{(GUI_BITMAP*)&bmtrigin,		(GUI_BITMAP*)&bmtrigin,			(GUI_BITMAP*)&bmtrigin,			(GUI_BITMAP*)&bmtrigin,			(GUI_BITMAP*)&bmtrigin,			(GUI_BITMAP*)&bmtrigin,			(GUI_BITMAP*)&bmtrigin,			(GUI_BITMAP*)&bmtrigin,			(GUI_BITMAP*)&bmtrigin,			(GUI_BITMAP*)&bmtrigin,			(GUI_BITMAP*)&bmtrigin,			(GUI_BITMAP*)&bmtrigin,			},0},	
					{256,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},	
					{256,224, 		{(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				},0}};	

const MITEM _file_media[]={
					{0,205,			{(GUI_BITMAP*)&bmmedia,			(GUI_BITMAP*)&bmmedia,			(GUI_BITMAP*)&bmmedia,			(GUI_BITMAP*)&bmmedia,			(GUI_BITMAP*)&bmmedia,			(GUI_BITMAP*)&bmmedia,			(GUI_BITMAP*)&bmmedia,			(GUI_BITMAP*)&bmmedia,			(GUI_BITMAP*)&bmmedia,			(GUI_BITMAP*)&bmmedia,			(GUI_BITMAP*)&bmmedia,			(GUI_BITMAP*)&bmmedia,			},0},
					{0,224,			{(GUI_BITMAP*)&bmmemory,		(GUI_BITMAP*)&bmmemory,			(GUI_BITMAP*)&bmmemory,			(GUI_BITMAP*)&bmmemory,			(GUI_BITMAP*)&bmmemory,			(GUI_BITMAP*)&bmmemory,			(GUI_BITMAP*)&bmmemory,			(GUI_BITMAP*)&bmmemory,			(GUI_BITMAP*)&bmmemory,			(GUI_BITMAP*)&bmmemory,			(GUI_BITMAP*)&bmmemory,			(GUI_BITMAP*)&bmmemory,			},0},
					{0,224,			{(GUI_BITMAP*)&bmusb,			(GUI_BITMAP*)&bmusb,			(GUI_BITMAP*)&bmusb,			(GUI_BITMAP*)&bmusb,			(GUI_BITMAP*)&bmusb,			(GUI_BITMAP*)&bmusb,			(GUI_BITMAP*)&bmusb,			(GUI_BITMAP*)&bmusb,			(GUI_BITMAP*)&bmusb,			(GUI_BITMAP*)&bmusb,			(GUI_BITMAP*)&bmusb,			(GUI_BITMAP*)&bmusb,			},0},
					{0,224,			{(GUI_BITMAP*)&bmdefault,		(GUI_BITMAP*)&bmdefault,		(GUI_BITMAP*)&bmdefault,		(GUI_BITMAP*)&bmdefault,		(GUI_BITMAP*)&bmdefault,		(GUI_BITMAP*)&bmdefault,		(GUI_BITMAP*)&bmdefault,		(GUI_BITMAP*)&bmdefault,		(GUI_BITMAP*)&bmdefault,		(GUI_BITMAP*)&bmdefault,		(GUI_BITMAP*)&bmdefault,		(GUI_BITMAP*)&bmdefault,		},0}};

const MITEM _recall[]={
					{192,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0},	
					{192,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0},	
					{192,205,		{(GUI_BITMAP*)&bmrecall,		(GUI_BITMAP*)&bmrecall,			(GUI_BITMAP*)&bmrecall,			(GUI_BITMAP*)&bmrecall,			(GUI_BITMAP*)&bmrecall,			(GUI_BITMAP*)&bmrecall,			(GUI_BITMAP*)&bmrecall,			(GUI_BITMAP*)&bmrecall,			(GUI_BITMAP*)&bmrecall,			(GUI_BITMAP*)&bmrecall,			(GUI_BITMAP*)&bmrecall,			(GUI_BITMAP*)&bmrecall,			},0}};

const MITEM _save[]={
					{128,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0},
					{128,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0},
					{128,205, 		{(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			},0}};

const MITEM _save2[]={				
					{128,205, 		{(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			},0}};						

const MITEM _copyscr[]={				
					{128,205, 		{(GUI_BITMAP*)&bmcopyscr,		(GUI_BITMAP*)&bmcopyscr,			(GUI_BITMAP*)&bmcopyscr,			(GUI_BITMAP*)&bmcopyscr,			(GUI_BITMAP*)&bmcopyscr,			(GUI_BITMAP*)&bmcopyscr,			(GUI_BITMAP*)&bmcopyscr,			(GUI_BITMAP*)&bmcopyscr,			(GUI_BITMAP*)&bmcopyscr,			(GUI_BITMAP*)&bmcopyscr,			(GUI_BITMAP*)&bmcopyscr,			(GUI_BITMAP*)&bmcopyscr,			},0}};																
const MITEM _file_util[]={
					{256,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0},	
					{256,205,		{(GUI_BITMAP*)&bmnodevice,		(GUI_BITMAP*)&bmnodevice,		(GUI_BITMAP*)&bmnodevice,		(GUI_BITMAP*)&bmnodevice,		(GUI_BITMAP*)&bmnodevice,		(GUI_BITMAP*)&bmnodevice,		(GUI_BITMAP*)&bmnodevice,		(GUI_BITMAP*)&bmnodevice,		(GUI_BITMAP*)&bmnodevice,		(GUI_BITMAP*)&bmnodevice,		(GUI_BITMAP*)&bmnodevice,		(GUI_BITMAP*)&bmnodevice,		},0},
					{256,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,			},0},
					{256,205,		{(GUI_BITMAP*)&bmfileutility,	(GUI_BITMAP*)&bmfileutility,	(GUI_BITMAP*)&bmfileutility,	(GUI_BITMAP*)&bmfileutility,	(GUI_BITMAP*)&bmfileutility,	(GUI_BITMAP*)&bmfileutility,	(GUI_BITMAP*)&bmfileutility,	(GUI_BITMAP*)&bmfileutility,	(GUI_BITMAP*)&bmfileutility,	(GUI_BITMAP*)&bmfileutility,	(GUI_BITMAP*)&bmfileutility,	(GUI_BITMAP*)&bmfileutility,	},0}};

const MITEM _prog_pause[]={
					{0,205,			{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	},0},	
					{0,205,			{(GUI_BITMAP*)&bmpause,			(GUI_BITMAP*)&bmpause, 			(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		},0},	
					{0,205,			{(GUI_BITMAP*)&bmcontinue,		(GUI_BITMAP*)&bmcontinue,		(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	},0},
					{0,205,			{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0}};


const MITEM _seq_pause[]={
					{0,205,			{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	(GUI_BITMAP*)&bmnull_a, 	},0},	
					{0,205,			{(GUI_BITMAP*)&bmpause,			(GUI_BITMAP*)&bmpause, 			(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		(GUI_BITMAP*)&bmpause, 		},0},	
					{0,205,			{(GUI_BITMAP*)&bmcontinue,		(GUI_BITMAP*)&bmcontinue,		(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	(GUI_BITMAP*)&bmcontinue,	},0},
					{0,205,			{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0}};
					
const MITEM _t_date[]={
					{0,205,			{(GUI_BITMAP*)&bmtdate,			(GUI_BITMAP*)&bmtdate,			(GUI_BITMAP*)&bmtdate,		(GUI_BITMAP*)&bmtdate,		(GUI_BITMAP*)&bmtdate,		(GUI_BITMAP*)&bmtdate,		(GUI_BITMAP*)&bmtdate,		(GUI_BITMAP*)&bmtdate,		(GUI_BITMAP*)&bmtdate,		(GUI_BITMAP*)&bmtdate,		(GUI_BITMAP*)&bmtdate,		(GUI_BITMAP*)&bmtdate,		},0}};

const MITEM _t_time[]={
					{0,205,			{(GUI_BITMAP*)&bmtime,			(GUI_BITMAP*)&bmtime,			(GUI_BITMAP*)&bmtime,		(GUI_BITMAP*)&bmtime,			(GUI_BITMAP*)&bmtime,	(GUI_BITMAP*)&bmtime,		(GUI_BITMAP*)&bmtime,		(GUI_BITMAP*)&bmtime,		(GUI_BITMAP*)&bmtime,		(GUI_BITMAP*)&bmtime,		(GUI_BITMAP*)&bmtime,		(GUI_BITMAP*)&bmtime,		},0}};

const MITEM _time_date[]={
					{64,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0},
					{64,205,		{(GUI_BITMAP*)&bmyear,			(GUI_BITMAP*)&bmyear,			(GUI_BITMAP*)&bmyear,		(GUI_BITMAP*)&bmyear,		(GUI_BITMAP*)&bmyear,		(GUI_BITMAP*)&bmyear,		(GUI_BITMAP*)&bmyear,		(GUI_BITMAP*)&bmyear,		(GUI_BITMAP*)&bmyear,		(GUI_BITMAP*)&bmyear,		(GUI_BITMAP*)&bmyear,		(GUI_BITMAP*)&bmyear,		},0},
					{64,205,		{(GUI_BITMAP*)&bmmonth,			(GUI_BITMAP*)&bmmonth,			(GUI_BITMAP*)&bmmonth,		(GUI_BITMAP*)&bmmonth,		(GUI_BITMAP*)&bmmonth,		(GUI_BITMAP*)&bmmonth,		(GUI_BITMAP*)&bmmonth,		(GUI_BITMAP*)&bmmonth,		(GUI_BITMAP*)&bmmonth,		(GUI_BITMAP*)&bmmonth,		(GUI_BITMAP*)&bmmonth,		(GUI_BITMAP*)&bmmonth,		},0},
					{64,205,		{(GUI_BITMAP*)&bmday,			(GUI_BITMAP*)&bmday,			(GUI_BITMAP*)&bmday,		(GUI_BITMAP*)&bmday,		(GUI_BITMAP*)&bmday,		(GUI_BITMAP*)&bmday,		(GUI_BITMAP*)&bmday,		(GUI_BITMAP*)&bmday,		(GUI_BITMAP*)&bmday,		(GUI_BITMAP*)&bmday,		(GUI_BITMAP*)&bmday,		(GUI_BITMAP*)&bmday,		},0}};

const MITEM _time_time[]={
					{64,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0},
					{64,205,		{(GUI_BITMAP*)&bmhour,			(GUI_BITMAP*)&bmhour,			(GUI_BITMAP*)&bmhour,		(GUI_BITMAP*)&bmhour,		(GUI_BITMAP*)&bmhour,		(GUI_BITMAP*)&bmhour,		(GUI_BITMAP*)&bmhour,		(GUI_BITMAP*)&bmhour,		(GUI_BITMAP*)&bmhour,		(GUI_BITMAP*)&bmhour,		(GUI_BITMAP*)&bmhour,		(GUI_BITMAP*)&bmhour,		},0},
					{64,205,		{(GUI_BITMAP*)&bmminute,		(GUI_BITMAP*)&bmminute,			(GUI_BITMAP*)&bmminute,		(GUI_BITMAP*)&bmminute,		(GUI_BITMAP*)&bmminute,		(GUI_BITMAP*)&bmminute,		(GUI_BITMAP*)&bmminute,		(GUI_BITMAP*)&bmminute,		(GUI_BITMAP*)&bmminute,		(GUI_BITMAP*)&bmminute,		(GUI_BITMAP*)&bmminute,		(GUI_BITMAP*)&bmminute,		},0}};

const MITEM _util_sysin[]={
					{0,205,			{(GUI_BITMAP*)&bmsystem,		(GUI_BITMAP*)&bmsystem,			(GUI_BITMAP*)&bmsystem,		(GUI_BITMAP*)&bmsystem,		(GUI_BITMAP*)&bmsystem,		(GUI_BITMAP*)&bmsystem,		(GUI_BITMAP*)&bmsystem,		(GUI_BITMAP*)&bmsystem,		(GUI_BITMAP*)&bmsystem,		(GUI_BITMAP*)&bmsystem,		(GUI_BITMAP*)&bmsystem,		(GUI_BITMAP*)&bmsystem,		},0},
					{0,224,			{(GUI_BITMAP*)&bminfo,			(GUI_BITMAP*)&bminfo,			(GUI_BITMAP*)&bminfo,		(GUI_BITMAP*)&bminfo,		(GUI_BITMAP*)&bminfo,		(GUI_BITMAP*)&bminfo,		(GUI_BITMAP*)&bminfo,		(GUI_BITMAP*)&bminfo,		(GUI_BITMAP*)&bminfo,		(GUI_BITMAP*)&bminfo,		(GUI_BITMAP*)&bminfo,		(GUI_BITMAP*)&bminfo,		},0},
					{0,224,			{(GUI_BITMAP*)&bmmemo,			(GUI_BITMAP*)&bmmemo,			(GUI_BITMAP*)&bmmemo,		(GUI_BITMAP*)&bmmemo,		(GUI_BITMAP*)&bmmemo,		(GUI_BITMAP*)&bmmemo,		(GUI_BITMAP*)&bmmemo,		(GUI_BITMAP*)&bmmemo,		(GUI_BITMAP*)&bmmemo,		(GUI_BITMAP*)&bmmemo,		(GUI_BITMAP*)&bmmemo,		(GUI_BITMAP*)&bmmemo,		},0}};

const MITEM _util_sysinfo[]={
					{0,205,			{(GUI_BITMAP*)&bmsysteminfo,	(GUI_BITMAP*)&bmsysteminfo,		(GUI_BITMAP*)&bmsysteminfo,		(GUI_BITMAP*)&bmsysteminfo,	(GUI_BITMAP*)&bmsysteminfo,		(GUI_BITMAP*)&bmsysteminfo,		(GUI_BITMAP*)&bmsysteminfo,		(GUI_BITMAP*)&bmsysteminfo,		(GUI_BITMAP*)&bmsysteminfo,		(GUI_BITMAP*)&bmsysteminfo,		(GUI_BITMAP*)&bmsysteminfo,		(GUI_BITMAP*)&bmsysteminfo,		},0}};

const MITEM _util_interface[]={
					{128,205,		{(GUI_BITMAP*)&bminterface,		(GUI_BITMAP*)&bminterface,		(GUI_BITMAP*)&bminterface,		(GUI_BITMAP*)&bminterface,	(GUI_BITMAP*)&bminterface,		(GUI_BITMAP*)&bminterface,		(GUI_BITMAP*)&bminterface,		(GUI_BITMAP*)&bminterface,		(GUI_BITMAP*)&bminterface,		(GUI_BITMAP*)&bminterface,		(GUI_BITMAP*)&bminterface,		(GUI_BITMAP*)&bminterface,		},0}};

const MITEM _util_timeset[]={
					{192,205,		{(GUI_BITMAP*)&bmtimeset,		(GUI_BITMAP*)&bmtimeset,		(GUI_BITMAP*)&bmtimeset,		(GUI_BITMAP*)&bmtimeset,	(GUI_BITMAP*)&bmtimeset,		(GUI_BITMAP*)&bmtimeset,		(GUI_BITMAP*)&bmtimeset,		(GUI_BITMAP*)&bmtimeset,		(GUI_BITMAP*)&bmtimeset,		(GUI_BITMAP*)&bmtimeset,		(GUI_BITMAP*)&bmtimeset,		(GUI_BITMAP*)&bmtimeset,		},0}};

const MITEM _util_other[]={
					{256,205,		{(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,		(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			},0}};

const MITEM _util_keypad_enter[]={
					{0,205,			{(GUI_BITMAP*)&bmenterchar,		(GUI_BITMAP*)&bmenterchar,		(GUI_BITMAP*)&bmenterchar,		(GUI_BITMAP*)&bmenterchar,	(GUI_BITMAP*)&bmenterchar,		(GUI_BITMAP*)&bmenterchar,		(GUI_BITMAP*)&bmenterchar,		(GUI_BITMAP*)&bmenterchar,		(GUI_BITMAP*)&bmenterchar,		(GUI_BITMAP*)&bmenterchar,		(GUI_BITMAP*)&bmenterchar,		(GUI_BITMAP*)&bmenterchar,		},0}};

const MITEM _password_enter[]={
					{0,205,			{(GUI_BITMAP*)&bmenter,			(GUI_BITMAP*)&bmenter,			(GUI_BITMAP*)&bmenter,			(GUI_BITMAP*)&bmenter,		(GUI_BITMAP*)&bmenter,			(GUI_BITMAP*)&bmenter,			(GUI_BITMAP*)&bmenter,			(GUI_BITMAP*)&bmenter,			(GUI_BITMAP*)&bmenter,			(GUI_BITMAP*)&bmenter,			(GUI_BITMAP*)&bmenter,			(GUI_BITMAP*)&bmenter,			},0}};

const MITEM _util_keypad_back[]={
					{64,205,		{(GUI_BITMAP*)&bmbackspace,		(GUI_BITMAP*)&bmbackspace,		(GUI_BITMAP*)&bmbackspace,		(GUI_BITMAP*)&bmbackspace,	(GUI_BITMAP*)&bmbackspace,		(GUI_BITMAP*)&bmbackspace,		(GUI_BITMAP*)&bmbackspace,		(GUI_BITMAP*)&bmbackspace,		(GUI_BITMAP*)&bmbackspace,		(GUI_BITMAP*)&bmbackspace,		(GUI_BITMAP*)&bmbackspace,		(GUI_BITMAP*)&bmbackspace,		},0}};

const MITEM _util_file_sel[]={
					{0,205,			{(GUI_BITMAP*)&bmselect,		(GUI_BITMAP*)&bmselect,			(GUI_BITMAP*)&bmselect,			(GUI_BITMAP*)&bmselect,		(GUI_BITMAP*)&bmselect,			(GUI_BITMAP*)&bmselect,			(GUI_BITMAP*)&bmselect,			(GUI_BITMAP*)&bmselect,			(GUI_BITMAP*)&bmselect,			(GUI_BITMAP*)&bmselect,			(GUI_BITMAP*)&bmselect,			(GUI_BITMAP*)&bmselect,			},0}};

const MITEM _util_file_newfol[]={
					{64,205,		{(GUI_BITMAP*)&bmnewfolder,		(GUI_BITMAP*)&bmnewfolder,		(GUI_BITMAP*)&bmnewfolder,		(GUI_BITMAP*)&bmnewfolder,	(GUI_BITMAP*)&bmnewfolder,		(GUI_BITMAP*)&bmnewfolder,		(GUI_BITMAP*)&bmnewfolder,		(GUI_BITMAP*)&bmnewfolder,		(GUI_BITMAP*)&bmnewfolder,		(GUI_BITMAP*)&bmnewfolder,		(GUI_BITMAP*)&bmnewfolder,		(GUI_BITMAP*)&bmnewfolder,		},0}};

const MITEM _util_file_rename[]={
					{128,205,		{(GUI_BITMAP*)&bmrename,		(GUI_BITMAP*)&bmrename,			(GUI_BITMAP*)&bmrename,			(GUI_BITMAP*)&bmrename,		(GUI_BITMAP*)&bmrename,			(GUI_BITMAP*)&bmrename,			(GUI_BITMAP*)&bmrename,			(GUI_BITMAP*)&bmrename,			(GUI_BITMAP*)&bmrename,			(GUI_BITMAP*)&bmrename,			(GUI_BITMAP*)&bmrename,			(GUI_BITMAP*)&bmrename,			},0}};

const MITEM _util_file_del[]={
					{192,205,		{(GUI_BITMAP*)&bmdel,			(GUI_BITMAP*)&bmdel,			(GUI_BITMAP*)&bmdel,			(GUI_BITMAP*)&bmdel,		(GUI_BITMAP*)&bmdel,			(GUI_BITMAP*)&bmdel,			(GUI_BITMAP*)&bmdel,			(GUI_BITMAP*)&bmdel,			(GUI_BITMAP*)&bmdel,			(GUI_BITMAP*)&bmdel,			(GUI_BITMAP*)&bmdel,			(GUI_BITMAP*)&bmdel,			},0}};

const MITEM _cancel[]={	
					{256,205, 		{(GUI_BITMAP*)&bmcancel,		(GUI_BITMAP*)&bmcancel,			(GUI_BITMAP*)&bmcancel,			(GUI_BITMAP*)&bmcancel,		(GUI_BITMAP*)&bmcancel,			(GUI_BITMAP*)&bmcancel,			(GUI_BITMAP*)&bmcancel,			(GUI_BITMAP*)&bmcancel,			(GUI_BITMAP*)&bmcancel,			(GUI_BITMAP*)&bmcancel,			(GUI_BITMAP*)&bmcancel,			(GUI_BITMAP*)&bmcancel,			},0}};

const MITEM _prog_func[]={
					{0,205,			{(GUI_BITMAP*)&bmprogram,		(GUI_BITMAP*)&bmprogram,		(GUI_BITMAP*)&bmprogram,		(GUI_BITMAP*)&bmprogram,	(GUI_BITMAP*)&bmprogram,		(GUI_BITMAP*)&bmprogram,		(GUI_BITMAP*)&bmprogram,		(GUI_BITMAP*)&bmprogram,		(GUI_BITMAP*)&bmprogram,		(GUI_BITMAP*)&bmprogram,		(GUI_BITMAP*)&bmprogram,		(GUI_BITMAP*)&bmprogram,		},0}};

const MITEM _ins_point[]={
					{0,205,			{(GUI_BITMAP*)&bminspoint,		(GUI_BITMAP*)&bminspoint,		(GUI_BITMAP*)&bminspoint,		(GUI_BITMAP*)&bminspoint,	(GUI_BITMAP*)&bminspoint,		(GUI_BITMAP*)&bminspoint,		(GUI_BITMAP*)&bminspoint,		(GUI_BITMAP*)&bminspoint,		(GUI_BITMAP*)&bminspoint,		(GUI_BITMAP*)&bminspoint,		(GUI_BITMAP*)&bminspoint,		(GUI_BITMAP*)&bminspoint,		},0}};			

const MITEM _add_point[]={
					{0,205,			{(GUI_BITMAP*)&bmaddpoint,		(GUI_BITMAP*)&bmaddpoint,		(GUI_BITMAP*)&bmaddpoint,		(GUI_BITMAP*)&bmaddpoint,	(GUI_BITMAP*)&bmaddpoint,		(GUI_BITMAP*)&bmaddpoint,		(GUI_BITMAP*)&bmaddpoint,		(GUI_BITMAP*)&bmaddpoint,		(GUI_BITMAP*)&bmaddpoint,		(GUI_BITMAP*)&bmaddpoint,		(GUI_BITMAP*)&bmaddpoint,		(GUI_BITMAP*)&bmaddpoint,		},0}};			
					
const MITEM _del_point[]={
					{64,205,		{(GUI_BITMAP*)&bmdeletepoint,	(GUI_BITMAP*)&bmdeletepoint,	(GUI_BITMAP*)&bmdeletepoint,	(GUI_BITMAP*)&bmdeletepoint,(GUI_BITMAP*)&bmdeletepoint,	(GUI_BITMAP*)&bmdeletepoint,	(GUI_BITMAP*)&bmdeletepoint,	(GUI_BITMAP*)&bmdeletepoint,	(GUI_BITMAP*)&bmdeletepoint,	(GUI_BITMAP*)&bmdeletepoint,	(GUI_BITMAP*)&bmdeletepoint,	(GUI_BITMAP*)&bmdeletepoint,	},0}};			
const MITEM _del_pointall[]={
					{192,205,		{(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,	(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,		(GUI_BITMAP*)&bmdeletall,	},0}};			

const MITEM _seq_func[]={
					{64,205,		{(GUI_BITMAP*)&bmsequence,		(GUI_BITMAP*)&bmsequence,		(GUI_BITMAP*)&bmsequence,		(GUI_BITMAP*)&bmsequence,	(GUI_BITMAP*)&bmsequence,		(GUI_BITMAP*)&bmsequence,		(GUI_BITMAP*)&bmsequence,		(GUI_BITMAP*)&bmsequence,		(GUI_BITMAP*)&bmsequence,		(GUI_BITMAP*)&bmsequence,		(GUI_BITMAP*)&bmsequence,		(GUI_BITMAP*)&bmsequence,		},0}};

//const MITEM _para_func[]={
//					{128,205,		{(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,	(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		},0}};										
const MITEM _para_func[]={
					{128,205,		{(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,	(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmparallel,		},0}};										
					

const MITEM _speaker[]={
					{64,205,		{(GUI_BITMAP*)&bmspeaker,		(GUI_BITMAP*)&bmspeaker,		(GUI_BITMAP*)&bmspeaker,		(GUI_BITMAP*)&bmspeaker,	(GUI_BITMAP*)&bmspeaker,		(GUI_BITMAP*)&bmspeaker,		(GUI_BITMAP*)&bmspeaker,		(GUI_BITMAP*)&bmspeaker,		(GUI_BITMAP*)&bmspeaker,		(GUI_BITMAP*)&bmspeaker,		(GUI_BITMAP*)&bmspeaker,		(GUI_BITMAP*)&bmspeaker,		},0},
					{64,224,		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,		(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{64,224,		{(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				},0}};

const MITEM _recalldef[]={
					{192,205,		{(GUI_BITMAP*)&bmrecalldefault,	(GUI_BITMAP*)&bmrecalldefault,	(GUI_BITMAP*)&bmrecalldefault,	(GUI_BITMAP*)&bmrecalldefault,	(GUI_BITMAP*)&bmrecalldefault,	(GUI_BITMAP*)&bmrecalldefault,	(GUI_BITMAP*)&bmrecalldefault,	(GUI_BITMAP*)&bmrecalldefault,	(GUI_BITMAP*)&bmrecalldefault,	(GUI_BITMAP*)&bmrecalldefault,	(GUI_BITMAP*)&bmrecalldefault,	(GUI_BITMAP*)&bmrecalldefault,	},0}};

const MITEM _onhelp[]={
					{0,205,			{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0},
					{0,205,			{(GUI_BITMAP*)&bmhelponhelp,	(GUI_BITMAP*)&bmhelponhelp,		(GUI_BITMAP*)&bmhelponhelp,	(GUI_BITMAP*)&bmhelponhelp,	(GUI_BITMAP*)&bmhelponhelp,	(GUI_BITMAP*)&bmhelponhelp,	(GUI_BITMAP*)&bmhelponhelp,	(GUI_BITMAP*)&bmhelponhelp,	(GUI_BITMAP*)&bmhelponhelp,	(GUI_BITMAP*)&bmhelponhelp,	(GUI_BITMAP*)&bmhelponhelp,	(GUI_BITMAP*)&bmhelponhelp,	},0},
					{0,205,			{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0}};


const MITEM _exit[]={
					{256,205,		{(GUI_BITMAP*)&bmexit,			(GUI_BITMAP*)&bmexit,			(GUI_BITMAP*)&bmexit,		(GUI_BITMAP*)&bmexit,		(GUI_BITMAP*)&bmexit,		(GUI_BITMAP*)&bmexit,		(GUI_BITMAP*)&bmexit,		(GUI_BITMAP*)&bmexit,		(GUI_BITMAP*)&bmexit,		(GUI_BITMAP*)&bmexit,		(GUI_BITMAP*)&bmexit,		(GUI_BITMAP*)&bmexit,		},0}};

const MITEM _next[]={
					{0,205,			{(GUI_BITMAP*)&bmnext,			(GUI_BITMAP*)&bmnext,			(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		},0}};

const MITEM _detail[]={
					{0,205,			{(GUI_BITMAP*)&bmdetail,		(GUI_BITMAP*)&bmdetail,			(GUI_BITMAP*)&bmdetail,		(GUI_BITMAP*)&bmdetail,		(GUI_BITMAP*)&bmdetail,		(GUI_BITMAP*)&bmdetail,		(GUI_BITMAP*)&bmdetail,		(GUI_BITMAP*)&bmdetail,		(GUI_BITMAP*)&bmdetail,		(GUI_BITMAP*)&bmdetail,		(GUI_BITMAP*)&bmdetail,		(GUI_BITMAP*)&bmdetail,		},0}};

const MITEM _util_load[]={	
					{64,205,		{(GUI_BITMAP*)&bmload,			(GUI_BITMAP*)&bmload,			(GUI_BITMAP*)&bmload,		(GUI_BITMAP*)&bmload,		(GUI_BITMAP*)&bmload,		(GUI_BITMAP*)&bmload,		(GUI_BITMAP*)&bmload,		(GUI_BITMAP*)&bmload,		(GUI_BITMAP*)&bmload,		(GUI_BITMAP*)&bmload,		(GUI_BITMAP*)&bmload,		(GUI_BITMAP*)&bmload,		},0}};

const MITEM _cal_start[]={
					{192,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0},			
					{192,205,		{(GUI_BITMAP*)&bmstart,			(GUI_BITMAP*)&bmstart,			(GUI_BITMAP*)&bmstart,		(GUI_BITMAP*)&bmstart,		(GUI_BITMAP*)&bmstart,		(GUI_BITMAP*)&bmstart,		(GUI_BITMAP*)&bmstart,		(GUI_BITMAP*)&bmstart,		(GUI_BITMAP*)&bmstart,		(GUI_BITMAP*)&bmstart,		(GUI_BITMAP*)&bmstart,		(GUI_BITMAP*)&bmstart,		},0},
					{192,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0}};			

const MITEM _cal_save[]={
					{192,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0},			
					{192,205,		{(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,			(GUI_BITMAP*)&bmsave,		(GUI_BITMAP*)&bmsave,		(GUI_BITMAP*)&bmsave,		(GUI_BITMAP*)&bmsave,		(GUI_BITMAP*)&bmsave,		(GUI_BITMAP*)&bmsave,		(GUI_BITMAP*)&bmsave,		(GUI_BITMAP*)&bmsave,		(GUI_BITMAP*)&bmsave,		(GUI_BITMAP*)&bmsave,		},0},
					{192,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0}};			

const MITEM _cal_psense[]={
					{128,205,		{(GUI_BITMAP*)&bmnull_c,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0},
					{128,205,		{(GUI_BITMAP*)&bmnull_c,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0},
					{128,205,		{(GUI_BITMAP*)&bmpsense,		(GUI_BITMAP*)&bmpsense,			(GUI_BITMAP*)&bmpsense,		(GUI_BITMAP*)&bmpsense,		(GUI_BITMAP*)&bmpsense,		(GUI_BITMAP*)&bmpsense,		(GUI_BITMAP*)&bmpsense,		(GUI_BITMAP*)&bmpsense,		(GUI_BITMAP*)&bmpsense,		(GUI_BITMAP*)&bmpsense,		(GUI_BITMAP*)&bmpsense,		(GUI_BITMAP*)&bmpsense,		},0},
					{128,205,		{(GUI_BITMAP*)&bmnull_c,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0}};

const MITEM _prog_next[]={
					{64,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0},
					{64,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0},
					{64,205,		{(GUI_BITMAP*)&bmnext,			(GUI_BITMAP*)&bmnext,			(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		},0}};

const MITEM _seq_next[]={
					{64,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0},
					{64,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,			(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a,		},0},
					{64,205,		{(GUI_BITMAP*)&bmnext,			(GUI_BITMAP*)&bmnext,			(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		(GUI_BITMAP*)&bmnext,		},0}};

const MITEM _bmdefinetrigout[]={
					{64,205,		{(GUI_BITMAP*)&bmdefinetrigout,	(GUI_BITMAP*)&bmdefinetrigout,		(GUI_BITMAP*)&bmdefinetrigout,	(GUI_BITMAP*)&bmdefinetrigout,	(GUI_BITMAP*)&bmdefinetrigout,	(GUI_BITMAP*)&bmdefinetrigout,	(GUI_BITMAP*)&bmdefinetrigout,	(GUI_BITMAP*)&bmdefinetrigout,	(GUI_BITMAP*)&bmdefinetrigout,	(GUI_BITMAP*)&bmdefinetrigout,	(GUI_BITMAP*)&bmdefinetrigout,	(GUI_BITMAP*)&bmdefinetrigout,	},0}};

const MITEM _Config_Prot[]={
					{0,205, 		{(GUI_BITMAP*)&bmprotection,	(GUI_BITMAP*)&bmprotection,			(GUI_BITMAP*)&bmprotection,		(GUI_BITMAP*)&bmprotection,		(GUI_BITMAP*)&bmprotection,		(GUI_BITMAP*)&bmprotection,		(GUI_BITMAP*)&bmprotection,		(GUI_BITMAP*)&bmprotection,		(GUI_BITMAP*)&bmprotection,		(GUI_BITMAP*)&bmprotection,		(GUI_BITMAP*)&bmprotection,		(GUI_BITMAP*)&bmprotection,		},0}};	

const MITEM _Config_Other[]={
					{64,205, 		{(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,				(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			(GUI_BITMAP*)&bmother,			},0}};	
					
const MITEM _Config_GONG[]={
					{128,205,		{(GUI_BITMAP*)&bmgonogo,		(GUI_BITMAP*)&bmgonogo, 			(GUI_BITMAP*)&bmgonogo, 		(GUI_BITMAP*)&bmgonogo, 		(GUI_BITMAP*)&bmgonogo, 		(GUI_BITMAP*)&bmgonogo, 		(GUI_BITMAP*)&bmgonogo, 		(GUI_BITMAP*)&bmgonogo, 		(GUI_BITMAP*)&bmgonogo, 		(GUI_BITMAP*)&bmgonogo, 		(GUI_BITMAP*)&bmgonogo, 		(GUI_BITMAP*)&bmgonogo, 		},0}};	

const MITEM _Config_Next[]={
					{192,205, 		{(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,			(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		},0}};

//const MITEM _Config_Parallel[]={	
//					{0,205, 		{(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,			(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		(GUI_BITMAP*)&bmparallel,		},0}};
const MITEM _Config_Parallel[]={	
					{0,205, 		{(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,			(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,		(GUI_BITMAP*)&bmsync,		},0}};

const MITEM _Config_Knob[]={
					{64,205,		{(GUI_BITMAP*)&bmknob,			(GUI_BITMAP*)&bmknob,				(GUI_BITMAP*)&bmknob,			(GUI_BITMAP*)&bmknob,			(GUI_BITMAP*)&bmknob,			(GUI_BITMAP*)&bmknob,			(GUI_BITMAP*)&bmknob,			(GUI_BITMAP*)&bmknob,			(GUI_BITMAP*)&bmknob,			(GUI_BITMAP*)&bmknob,			(GUI_BITMAP*)&bmknob,			(GUI_BITMAP*)&bmknob,			},0}};

const MITEM _Config_External[]={
					{128,205, 		{(GUI_BITMAP*)&bmexternal,		(GUI_BITMAP*)&bmexternal,			(GUI_BITMAP*)&bmexternal,		(GUI_BITMAP*)&bmexternal,		(GUI_BITMAP*)&bmexternal,		(GUI_BITMAP*)&bmexternal,		(GUI_BITMAP*)&bmexternal,		(GUI_BITMAP*)&bmexternal,		(GUI_BITMAP*)&bmexternal,		(GUI_BITMAP*)&bmexternal,		(GUI_BITMAP*)&bmexternal,		(GUI_BITMAP*)&bmexternal,		},0}};	

const MITEM _Normal_Sequence[]={
					{64,205, 		{(GUI_BITMAP*)&bmnormalsequence,(GUI_BITMAP*)&bmnormalsequence,		(GUI_BITMAP*)&bmnormalsequence,	(GUI_BITMAP*)&bmnormalsequence,	(GUI_BITMAP*)&bmnormalsequence,	(GUI_BITMAP*)&bmnormalsequence,	(GUI_BITMAP*)&bmnormalsequence,	(GUI_BITMAP*)&bmnormalsequence,	(GUI_BITMAP*)&bmnormalsequence,	(GUI_BITMAP*)&bmnormalsequence,	(GUI_BITMAP*)&bmnormalsequence,	(GUI_BITMAP*)&bmnormalsequence,	},0}};	
					
const MITEM _Fast_Sequence[]={
					{128,205, 		{(GUI_BITMAP*)&bmfastsequence,	(GUI_BITMAP*)&bmfastsequence,		(GUI_BITMAP*)&bmfastsequence,	(GUI_BITMAP*)&bmfastsequence,	(GUI_BITMAP*)&bmfastsequence,	(GUI_BITMAP*)&bmfastsequence,	(GUI_BITMAP*)&bmfastsequence,	(GUI_BITMAP*)&bmfastsequence,	(GUI_BITMAP*)&bmfastsequence,	(GUI_BITMAP*)&bmfastsequence,	(GUI_BITMAP*)&bmfastsequence,	(GUI_BITMAP*)&bmfastsequence,	},0}};	

const MITEM _func_Next[]= {
	{256,205, 		{(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,			(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmnextmenu,		},0}
};

const MITEM _OPP[]= { 
	{0,205, 		{(GUI_BITMAP*)&bmopp_b,		(GUI_BITMAP*)&bmopp_b,			(GUI_BITMAP*)&bmopp_b,		(GUI_BITMAP*)&bmopp_b,		(GUI_BITMAP*)&bmopp_b,		(GUI_BITMAP*)&bmopp_b,		(GUI_BITMAP*)&bmopp_b,		(GUI_BITMAP*)&bmopp_b,		(GUI_BITMAP*)&bmopp_b,		(GUI_BITMAP*)&bmopp_b,		(GUI_BITMAP*)&bmopp_b,		(GUI_BITMAP*)&bmopp_b,		},0}
};
const MITEM _batt[]= {
	{64,205, 		{(GUI_BITMAP*)&bmBATT,		(GUI_BITMAP*)&bmBATT,			(GUI_BITMAP*)&bmBATT,		(GUI_BITMAP*)&bmBATT,		(GUI_BITMAP*)&bmBATT,		(GUI_BITMAP*)&bmBATT,		(GUI_BITMAP*)&bmBATT,		(GUI_BITMAP*)&bmBATT,		(GUI_BITMAP*)&bmBATT,		(GUI_BITMAP*)&bmBATT,		(GUI_BITMAP*)&bmnextmenu,		(GUI_BITMAP*)&bmBATT,		},0}
};
const MITEM _battDischarge[]= {
	{128,205, 		{(GUI_BITMAP*)&bmbattery_discharge,		(GUI_BITMAP*)&bmbattery_discharge,			(GUI_BITMAP*)&bmbattery_discharge,		(GUI_BITMAP*)&bmbattery_discharge,		(GUI_BITMAP*)&bmbattery_discharge,		(GUI_BITMAP*)&bmbattery_discharge,		(GUI_BITMAP*)&bmbattery_discharge,		(GUI_BITMAP*)&bmbattery_discharge,		(GUI_BITMAP*)&bmbattery_discharge,		(GUI_BITMAP*)&bmbattery_discharge,		(GUI_BITMAP*)&bmbattery_discharge,		(GUI_BITMAP*)&bmbattery_discharge,		},0}
};
const MITEM _LED[]= {
	{128,205, 		{(GUI_BITMAP*)&bmLED,		(GUI_BITMAP*)&bmLED,			(GUI_BITMAP*)&bmLED,		(GUI_BITMAP*)&bmLED,		(GUI_BITMAP*)&bmLED,		(GUI_BITMAP*)&bmLED,		(GUI_BITMAP*)&bmLED,		(GUI_BITMAP*)&bmLED,		(GUI_BITMAP*)&bmLED,		(GUI_BITMAP*)&bmLED,		(GUI_BITMAP*)&bmLED,		(GUI_BITMAP*)&bmLED,		},0}
};
const MITEM _LED2[]= {
	{192,205, 		{(GUI_BITMAP*)&bmled2,		(GUI_BITMAP*)&bmled2,			(GUI_BITMAP*)&bmled2,		(GUI_BITMAP*)&bmled2,		(GUI_BITMAP*)&bmled2,		(GUI_BITMAP*)&bmled2,		(GUI_BITMAP*)&bmled2,		(GUI_BITMAP*)&bmled2,		(GUI_BITMAP*)&bmled2,		(GUI_BITMAP*)&bmled2,		(GUI_BITMAP*)&bmled2,		(GUI_BITMAP*)&bmled2,		},0}
};


const MITEM _Prog_ONOFF[]={
					{0,205, 		{(GUI_BITMAP*)&bmprog,			(GUI_BITMAP*)&bmprog,				(GUI_BITMAP*)&bmprog,			(GUI_BITMAP*)&bmprog,			(GUI_BITMAP*)&bmprog,			(GUI_BITMAP*)&bmprog,			(GUI_BITMAP*)&bmprog,			(GUI_BITMAP*)&bmprog,			(GUI_BITMAP*)&bmprog,			(GUI_BITMAP*)&bmprog,			(GUI_BITMAP*)&bmprog,			(GUI_BITMAP*)&bmprog,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,					(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0}};

const MITEM _NSeq_ONOFF[]={
					{0,205, 		{(GUI_BITMAP*)&bmnormal_seq,	(GUI_BITMAP*)&bmnormal_seq,			(GUI_BITMAP*)&bmnormal_seq,		(GUI_BITMAP*)&bmnormal_seq,		(GUI_BITMAP*)&bmnormal_seq,		(GUI_BITMAP*)&bmnormal_seq,		(GUI_BITMAP*)&bmnormal_seq,		(GUI_BITMAP*)&bmnormal_seq,		(GUI_BITMAP*)&bmnormal_seq,		(GUI_BITMAP*)&bmnormal_seq,		(GUI_BITMAP*)&bmnormal_seq,		(GUI_BITMAP*)&bmnormal_seq,		},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,					(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0}};

const MITEM _FSeq_ONOFF[]={
					{0,205, 		{(GUI_BITMAP*)&bmfast_seq,		(GUI_BITMAP*)&bmfast_seq,			(GUI_BITMAP*)&bmfast_seq,		(GUI_BITMAP*)&bmfast_seq,		(GUI_BITMAP*)&bmfast_seq,		(GUI_BITMAP*)&bmfast_seq,		(GUI_BITMAP*)&bmfast_seq,		(GUI_BITMAP*)&bmfast_seq,		(GUI_BITMAP*)&bmfast_seq,		(GUI_BITMAP*)&bmfast_seq,		(GUI_BITMAP*)&bmfast_seq,		(GUI_BITMAP*)&bmfast_seq,		},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,					(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0}};

const MITEM _seq_edit[]={
					{64,205, 		{(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,			(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		(GUI_BITMAP*)&bmseqedit,		},0}};

const MITEM _fill[]={
					{192,205, 		{(GUI_BITMAP*)&bmfill,			(GUI_BITMAP*)&bmfill,				(GUI_BITMAP*)&bmfill,			(GUI_BITMAP*)&bmfill,			(GUI_BITMAP*)&bmfill,			(GUI_BITMAP*)&bmfill,			(GUI_BITMAP*)&bmfill,			(GUI_BITMAP*)&bmfill,			(GUI_BITMAP*)&bmfill,			(GUI_BITMAP*)&bmfill,			(GUI_BITMAP*)&bmfill,			(GUI_BITMAP*)&bmfill,			},0}};
#if Enable_OCP_function
const MITEM _function_app[]={
					{192,205,		{(GUI_BITMAP*)&bmAPP_b, 		(GUI_BITMAP*)&bmAPP_b,			(GUI_BITMAP*)&bmAPP_b,			(GUI_BITMAP*)&bmAPP_b,	(GUI_BITMAP*)&bmAPP_b,		(GUI_BITMAP*)&bmAPP_b,		(GUI_BITMAP*)&bmAPP_b,		(GUI_BITMAP*)&bmAPP_b,		(GUI_BITMAP*)&bmAPP_b,		(GUI_BITMAP*)&bmAPP_b,		(GUI_BITMAP*)&bmAPP_b,		(GUI_BITMAP*)&bmAPP_b,		},0}};
const MITEM _function_ocp_s[]={
					{0,205, 		{(GUI_BITMAP*)&bmocp_s, 		(GUI_BITMAP*)&bmocp_s,			(GUI_BITMAP*)&bmocp_s,		(GUI_BITMAP*)&bmocp_s,		(GUI_BITMAP*)&bmocp_s,		(GUI_BITMAP*)&bmocp_s,		(GUI_BITMAP*)&bmocp_s,		(GUI_BITMAP*)&bmocp_s,		(GUI_BITMAP*)&bmocp_s,		(GUI_BITMAP*)&bmocp_s,		(GUI_BITMAP*)&bmocp_s,		(GUI_BITMAP*)&bmocp_s,		},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 		(GUI_BITMAP*)&bmon, 		(GUI_BITMAP*)&bmon, 		(GUI_BITMAP*)&bmon, 		(GUI_BITMAP*)&bmon, 		(GUI_BITMAP*)&bmon, 		(GUI_BITMAP*)&bmon, 		(GUI_BITMAP*)&bmon, 		(GUI_BITMAP*)&bmon, 		(GUI_BITMAP*)&bmon, 		},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0}};
const MITEM _function_ocp_b[]={
					{192,205, 	{(GUI_BITMAP*)&bmocp_b, 		(GUI_BITMAP*)&bmocp_b,			(GUI_BITMAP*)&bmocp_b,			(GUI_BITMAP*)&bmocp_b,	(GUI_BITMAP*)&bmocp_b,		(GUI_BITMAP*)&bmocp_b,		(GUI_BITMAP*)&bmocp_b,		(GUI_BITMAP*)&bmocp_b,		(GUI_BITMAP*)&bmocp_b,		(GUI_BITMAP*)&bmocp_b,		(GUI_BITMAP*)&bmocp_b,		(GUI_BITMAP*)&bmocp_b,		},0}};
					
#endif

#if Enable_OCP_function

const MITEM _function_opp_s[]= {
					{0,205,			{(GUI_BITMAP*)&bmopp_s,			(GUI_BITMAP*)&bmopp_s,			(GUI_BITMAP*)&bmopp_s,		(GUI_BITMAP*)&bmopp_s,		(GUI_BITMAP*)&bmopp_s,		(GUI_BITMAP*)&bmopp_s,		(GUI_BITMAP*)&bmopp_s,		(GUI_BITMAP*)&bmopp_s,		(GUI_BITMAP*)&bmopp_s,		(GUI_BITMAP*)&bmopp_s,		(GUI_BITMAP*)&bmopp_s,		(GUI_BITMAP*)&bmopp_s,		},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
					{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0}
};

const MITEM _function_opp_b[]= {
	{0,205,			{(GUI_BITMAP*)&bmopp_b, 		(GUI_BITMAP*)&bmopp_b,			(GUI_BITMAP*)&bmopp_b,			(GUI_BITMAP*)&bmopp_b,	(GUI_BITMAP*)&bmopp_b,		(GUI_BITMAP*)&bmopp_b,		(GUI_BITMAP*)&bmopp_b,		(GUI_BITMAP*)&bmopp_b,		(GUI_BITMAP*)&bmopp_b,		(GUI_BITMAP*)&bmopp_b,		(GUI_BITMAP*)&bmopp_b,		(GUI_BITMAP*)&bmopp_b,		},0}
};

#endif

const MITEM _batt_ONOFF[]= {
	{0,205,			{(GUI_BITMAP*)&bmbatt_s,			(GUI_BITMAP*)&bmbatt_s,			(GUI_BITMAP*)&bmbatt_s,		(GUI_BITMAP*)&bmbatt_s,		(GUI_BITMAP*)&bmbatt_s,		(GUI_BITMAP*)&bmbatt_s,		(GUI_BITMAP*)&bmbatt_s,		(GUI_BITMAP*)&bmbatt_s,		(GUI_BITMAP*)&bmbatt_s,		(GUI_BITMAP*)&bmbatt_s,		(GUI_BITMAP*)&bmbatt_s,		(GUI_BITMAP*)&bmbatt_s,		},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			(GUI_BITMAP*)&bmon,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0}
};
const MITEM _LED_ONOFF[]= {
	{0,205,			{(GUI_BITMAP*)&bmLED_s,			(GUI_BITMAP*)&bmLED_s,			(GUI_BITMAP*)&bmLED_s,		(GUI_BITMAP*)&bmLED_s,		(GUI_BITMAP*)&bmLED_s,		(GUI_BITMAP*)&bmLED_s,		(GUI_BITMAP*)&bmLED_s,		(GUI_BITMAP*)&bmLED_s,		(GUI_BITMAP*)&bmLED_s,		(GUI_BITMAP*)&bmLED_s,		(GUI_BITMAP*)&bmLED_s,		(GUI_BITMAP*)&bmLED_s,		},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon, 				(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0}
};


const MITEM _CLED_ONOFF[]= {
	{0,205,			{(GUI_BITMAP*)&bmcled_s,			(GUI_BITMAP*)&bmcled_s,			(GUI_BITMAP*)&bmcled_s,		(GUI_BITMAP*)&bmcled_s,		(GUI_BITMAP*)&bmcled_s,		(GUI_BITMAP*)&bmcled_s,		(GUI_BITMAP*)&bmcled_s,		(GUI_BITMAP*)&bmcled_s,		(GUI_BITMAP*)&bmcled_s,		(GUI_BITMAP*)&bmcled_s,		(GUI_BITMAP*)&bmcled_s,		(GUI_BITMAP*)&bmcled_s,		},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0},
	{0,224, 		{(GUI_BITMAP*)&bmon,				(GUI_BITMAP*)&bmon, 				(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			(GUI_BITMAP*)&bmon, 			},0},
	{0,224, 		{(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,				(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			(GUI_BITMAP*)&bmoff,			},0}
};


#if Enable_LED_function
const MITEM _editLed[]= {
	{64,205, 		{(GUI_BITMAP*)&bmEditLed,		(GUI_BITMAP*)&bmEditLed,			(GUI_BITMAP*)&bmEditLed,		(GUI_BITMAP*)&bmEditLed,		(GUI_BITMAP*)&bmVolt_Curr,		(GUI_BITMAP*)&bmEditLed,		(GUI_BITMAP*)&bmEditLed,		(GUI_BITMAP*)&bmEditLed,		(GUI_BITMAP*)&bmEditLed,		(GUI_BITMAP*)&bmEditLed,		(GUI_BITMAP*)&bmEditLed,		(GUI_BITMAP*)&bmEditLed,		},0}
};
const MITEM _voltCurr[]= {
	{192,205, 		{(GUI_BITMAP*)&bmVolt_Curr,		(GUI_BITMAP*)&bmVolt_Curr,			(GUI_BITMAP*)&bmVolt_Curr,		(GUI_BITMAP*)&bmVolt_Curr,		(GUI_BITMAP*)&bmVolt_Curr,		(GUI_BITMAP*)&bmVolt_Curr,		(GUI_BITMAP*)&bmVolt_Curr,		(GUI_BITMAP*)&bmVolt_Curr,		(GUI_BITMAP*)&bmVolt_Curr,		(GUI_BITMAP*)&bmVolt_Curr,		(GUI_BITMAP*)&bmVolt_Curr,		(GUI_BITMAP*)&bmVolt_Curr,		},0}
};

#endif

const MITEM _factorydefault[]={
					{64,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 			(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0},
					{64,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 			(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0},
					{64,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 			(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0},
					{64,205,		{(GUI_BITMAP*)&bmfactorydefault,(GUI_BITMAP*)&bmfactorydefault,		(GUI_BITMAP*)&bmfactorydefault,	(GUI_BITMAP*)&bmfactorydefault,	(GUI_BITMAP*)&bmfactorydefault,	(GUI_BITMAP*)&bmfactorydefault,	(GUI_BITMAP*)&bmfactorydefault,	(GUI_BITMAP*)&bmfactorydefault,	(GUI_BITMAP*)&bmfactorydefault,	(GUI_BITMAP*)&bmfactorydefault,	(GUI_BITMAP*)&bmfactorydefault,	(GUI_BITMAP*)&bmfactorydefault,	},0}};

const MITEM _poweranalysis[]={
					{128,205, 		{(GUI_BITMAP*)&bmpoweranalysis,	(GUI_BITMAP*)&bmpoweranalysis,		(GUI_BITMAP*)&bmpoweranalysis,	(GUI_BITMAP*)&bmpoweranalysis,	(GUI_BITMAP*)&bmpoweranalysis,	(GUI_BITMAP*)&bmpoweranalysis,	(GUI_BITMAP*)&bmpoweranalysis,	(GUI_BITMAP*)&bmpoweranalysis,	(GUI_BITMAP*)&bmpoweranalysis,	(GUI_BITMAP*)&bmpoweranalysis,	(GUI_BITMAP*)&bmpoweranalysis,	(GUI_BITMAP*)&bmpoweranalysis,	},0}};

const MITEM _uninstall[]={
					{192,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 			(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0},
					{192,205,		{(GUI_BITMAP*)&bmnull_a,		(GUI_BITMAP*)&bmnull_a, 			(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a,	 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		(GUI_BITMAP*)&bmnull_a, 		},0},
					{192,205,		{(GUI_BITMAP*)&bmuninstall,		(GUI_BITMAP*)&bmuninstall,			(GUI_BITMAP*)&bmuninstall,		(GUI_BITMAP*)&bmuninstall,		(GUI_BITMAP*)&bmuninstall,		(GUI_BITMAP*)&bmuninstall,		(GUI_BITMAP*)&bmuninstall,		(GUI_BITMAP*)&bmuninstall,		(GUI_BITMAP*)&bmuninstall,		(GUI_BITMAP*)&bmuninstall,		(GUI_BITMAP*)&bmuninstall,		(GUI_BITMAP*)&bmuninstall,		},0}};
					
/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/

MITEMS _normal_cc[]={		{(MITEM *)_normal_mode,			(Func)Normal_Mode,					&P3k_Disp_Data.CURRMODE,				4,1},
							{(MITEM *)_normal_irange,		(Func)Normal_IRange,				&P3k_Disp_Data.IRange,					3,1},
							{(MITEM *)_normal_vrange, 		(Func)Normal_VRange, 				&P3k_Disp_Data.VRange,					2,1},
							{(MITEM *)_normal_stadyna,		(Func)Normal_Type,					&P3k_Disp_Data.CC.STADYNA,				3,1},
							{(MITEM *)_config_main,			(Func)Configure_Main,				NULL1,									0,2}};

MITEMS _normal_cr[]={		{(MITEM *)_normal_mode,			(Func)Normal_Mode,					&P3k_Disp_Data.CURRMODE,				4,1},
							{(MITEM *)_cal_range,			(Func)Normal_IRange,				&P3k_Disp_Data.IRange,					3,1},
							{(MITEM *)_normal_vrange,		(Func)Normal_VRange,				&P3k_Disp_Data.VRange,					2,1},
							{(MITEM *)_normal_stadyna, 		(Func)Normal_Type, 					&P3k_Disp_Data.CR.STADYNA,				3,1},
							{(MITEM *)_config_main,			(Func)Configure_Main,				NULL1,									0,2}};

MITEMS _normal_cv[]={		{(MITEM *)_normal_mode,			(Func)Normal_Mode,					&P3k_Disp_Data.CURRMODE,				4,1},
							{(MITEM *)_normal_irange,		(Func)Normal_IRange,				&P3k_Disp_Data.IRange,					3,1},
							{(MITEM *)_normal_vrange,		(Func)Normal_VRange,				&P3k_Disp_Data.VRange,					2,1},
							{(MITEM *)_cvcp_response,		(Func)Normal_Type,				&P3k_Disp_Data.CV.RESPONSE,				3,1},
							{(MITEM *)_config_main,			(Func)Configure_Main,				NULL1,									0,2}};

MITEMS _normal_cp[]={		{(MITEM *)_normal_mode,			(Func)Normal_Mode,					&P3k_Disp_Data.CURRMODE,				4,1},
							{(MITEM *)_normal_irange,		(Func)Normal_IRange,				&P3k_Disp_Data.IRange,					3,1},
							{(MITEM *)_normal_vrange,		(Func)Normal_VRange,				&P3k_Disp_Data.VRange,					2,1},						
							{(MITEM *)_cvcp_response, 		(Func)Normal_Type, 					&P3k_Disp_Data.CP.RESPONSE,				3,1},
							{(MITEM *)_config_main,			(Func)Configure_Main,				NULL1,									0,2}};

MITEMS _config_Prot[]={
							{(MITEM *)_Config_Prot,			(Func)Config_Protection,			NULL1,								0,2},
							{(MITEM *)_Config_Other,		(Func)Config_Other,					NULL1,								0,2},
							{(MITEM *)_Config_GONG,	 		(Func)Config_GoNoGo,				NULL1,								0,2},
							{(MITEM *)_Config_Next,			(Func)Config_Parallel,				NULL1,								0,2},
							{(MITEM *)_pre_menu,			(Func)Pre_Menu,						NULL1,								0,2}};
MITEMS _config_Para[]={
							{(MITEM *)_Config_Parallel,		(Func)Config_Parallel,				NULL1,								0,2},
							{(MITEM *)_Config_Knob,			(Func)Config_Knob,					NULL1,								0,2},
							{(MITEM *)_Config_External,	 	(Func)Config_External,				NULL1,								0,2},
							{(MITEM *)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM *)_pre_menu,			(Func)Pre_Menu,						NULL1,								0,2}};

MITEMS _prog_main[]={
							{(MITEM *)_Prog_ONOFF,			(Func)EnableFlag,					&P3k_Chan_Data.Load_Type,			10,1},
							{(MITEM *)_Prog_chain,			(Func)Prog_Chain,					NULL1,								0,2},
							{(MITEM *)_prog_save,			(Func)Save_Data,					&SEQ_Save_Status,					2,2},
							{(MITEM *)_recalldef,			(Func)Recall_Data,					NULL1,								0,2},
							{(MITEM *)_pre_menu,			(Func)Pre_Menu,						NULL1,								0,2}};							
MITEMS _prog_chain[]={
							{(MITEM *)_prog_editstart,		(Func)Edit_Chain_Start,				NULL1,								0,2},
							{(MITEM *)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM *)_prog_save,			(Func)Save_Data,					&SEQ_Save_Status,					2,2},
							{(MITEM *)_recalldef,			(Func)Recall_Data,					NULL1,								0,2},
							{(MITEM *)_pre_menu,			(Func)Pre_Menu,						NULL1,								0,2}};

MITEMS _file[]={
							{(MITEM*)_file_media,			(Func)FileMedia_Proc,				&p3k_File_Utility_BAR.MEDIA,			3,1},
							{(MITEM*)_factorydefault,		(Func)Recall_Factory_Default,		&p3k_File_Utility_BAR.MEDIA,			3,2},
							{(MITEM*)_save,					(Func)Save_Data,					(UBYTE *)&Save_Status,					2,2},
							{(MITEM*)_recall,				(Func)Recall_Data,					(UBYTE *)&Recall_Status,				2,2},
							{(MITEM*)_file_util,			(Func)FileUtil_Proc,				(UBYTE *)&USB_Status_Display,			3,2}};
							
MITEMS _file_machine[]={
							{(MITEM*)Null_F1,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F3,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F5,				(Func)Empty_Func,					NULL1,								0,2}};
							
#if Enable_delet_RCT
MITEMS _utility_main[]={
							{(MITEM*)_util_sysin,			(Func)Utility_Proc,					&System_Info_Memo,					2,1},
							{(MITEM*)_util_load,			(Func)Utility_Proc,					NULL1,								0,2},
							{(MITEM*)_util_interface,		(Func)Utility_Proc,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_util_other,			(Func)Utility_Proc,					NULL1,								0,2}};
	

#else
MITEMS _utility_main[]={
							{(MITEM*)_util_sysin,			(Func)Utility_Proc,					&System_Info_Memo,					2,1},
							{(MITEM*)_util_load,			(Func)Utility_Proc,					NULL1,								0,2},
							{(MITEM*)_util_interface,		(Func)Utility_Proc,					NULL1,								0,2},
							{(MITEM*)_util_timeset,			(Func)Utility_Proc,					NULL1,								0,2},
							{(MITEM*)_util_other,			(Func)Utility_Proc,					NULL1,								0,2}};
#endif
MITEMS _utility_keypad[]={
							{(MITEM*)_util_keypad_enter,	(Func)EnterChrFunc,					NULL1,								0,2},
							{(MITEM*)_util_keypad_back,		(Func)BackSpaceFunc,				NULL1,								0,2},
							{(MITEM*)_save2,				(Func)KeyPadSave,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_pre_menu,				(Func)Pre_Menu,						NULL1,								0,2}};

MITEMS _utility_file[]={
							{(MITEM*)_util_file_sel,		(Func)FMselect,						NULL1,								0,2},
							{(MITEM*)_util_file_newfol,		(Func)FileKeyPad_Proc,				NULL1,								0,2},
							{(MITEM*)_util_file_rename,		(Func)FileKeyPad_Proc,				NULL1,								0,2},
							{(MITEM*)_util_file_del,		(Func)FMdelete,						NULL1,								0,2},
							{(MITEM*)_pre_menu,				(Func)Pre_Menu,						NULL1,								0,2}};

MITEMS _cal_main[]={
							{(MITEM*)_cal_mode,				(Func)Cal_Func,						&P3K_CALIBRATION_BAR.MODE,			MODE_Number,1},
							{(MITEM*)_cal_range,			(Func)Cal_Func,						&P3K_CALIBRATION_BAR.RANGE,			4,1},
							{(MITEM*)_cal_psense,			(Func)Cal_PSense,					&P3K_CALIBRATION_BAR.PSense,		3,2},
							{(MITEM*)_cal_save,				(Func)Cal_Save,						&P3K_CALIBRATION_BAR.START,			2,2},
							{(MITEM*)_exit,					(Func)Pre_Menu,						NULL1,								0,2}};
MITEMS _help_help[]={
							{(MITEM*)_onhelp,				(Func)Help_func,					&Help_Key_Flag,						2,2},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F3,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_exit,					(Func)Pre_Menu,						NULL1,								0,2}};
				
MITEMS _prog_execute[]={
							{(MITEM*)_prog_pause,			(Func)Prog_Seq_Stop_Continue,		&Prog_Seq_Data.SEQ_Stop_Continue,	3,2},
							{(MITEM*)_prog_next,			(Func)Prog_Seq_Next,				&Prog_Seq_Data.MANUAL_CTRL,			2,2},
							{(MITEM*)Null_F3,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F5,				(Func)Empty_Func,					NULL1,								0,2}};

MITEMS _prog_detail[]={
							{(MITEM*)Null_F1,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_save,					(Func)Save_Data,					&Go_NG_Save_Status,					2,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_exit,					(Func)Pre_Menu,						NULL1,								0,2}};
MITEMS _Lua_execute[]={
							{(MITEM*)Null_F1,				(Func)Script_Funselect,				NULL1,								0,2},
							{(MITEM*)Null_F2,				(Func)Script_Funselect,				NULL1,								0,2},
							{(MITEM*)Null_F3,				(Func)Script_Funselect,				NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Script_Funselect,				NULL1,								0,2},
							{(MITEM*)Null_F5,			 	(Func)Script_Funselect, 			NULL1,								0,2}};

#if Enable_Menu_optim==0
MITEMS _Func_Main[]={
							{(MITEM*)_prog_func,			(Func)Prog_Function,				NULL1,								0,2},
							{(MITEM*)_seq_func,				(Func)Seq_Function,					NULL1,								0,2},
							{(MITEM*)Null_F3,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F5,				(Func)Empty_Func,					NULL1,								0,2}};

#else
MITEMS _Func_Main[]={
							{(MITEM*)_prog_func,			(Func)Prog_Function,				NULL1,								0,2},
							{(MITEM*)_Normal_Sequence,		(Func)Seq_Select,					NULL1,								0,2},
							{(MITEM*)_Fast_Sequence,		(Func)Seq_Select,					NULL1,								0,2},
							{(MITEM*)_function_ocp_b,		(Func)APP_Function_OCP,				NULL1,								0,2},

#if Enable_OPP_function
							{(MITEM*)_func_Next,			(Func)goto_func_main2,				NULL1,								0,2}};
#else
							{(MITEM*)Null_F5,				(Func)Empty_Func,					NULL1,								0,2}};
#endif
#endif

MITEMS _Input_Password[]={
							{(MITEM*)_password_enter,		(Func)Password_Process,				NULL1,								0,2},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F3,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_exit, 				(Func)Pre_Menu, 					NULL1,								0,2}};
MITEMS _Input_Serial[]={
							{(MITEM*)Null_F1,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F3,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_exit, 				(Func)Pre_Menu, 					NULL1,								0,2}};

MITEMS _Nothing[]={
							{(MITEM*)Null_F1,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F3,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F5, 				(Func)Empty_Func, 					NULL1,								0,2}};

#if 1
MITEMS _Test_Func[]={		
							{(MITEM*)_test_Function,		(Func)DebugToolSelet,			NULL1,								0,2},
							{(MITEM*)_savetool,				(Func)DebugToolSave,			NULL1,								0,2},
							{(MITEM*)Null_F3,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_displayCal,			(Func)JumpCalValue,					NULL1,								0,2},
							{(MITEM*)_exit, 				(Func)Pre_Menu, 					NULL1,								0,2}};
#else
MITEMS _Test_Func[]={		
							{(MITEM*)_test_Function,		(Func)Save_1K_Meas_Data,			NULL1,								0,2},
							{(MITEM*)_test2_Function,		(Func)Save_CalData_To_USB,			NULL1,								0,2},
							{(MITEM*)_copyscr,				(Func)Save_PrintScr_To_USB,			NULL1,								0,2},
							{(MITEM*)_displayCal,			(Func)JumpCalValue,					NULL1,								0,2},
							{(MITEM*)_exit, 				(Func)Pre_Menu, 					NULL1,								0,2}};

#endif
MITEMS _Cal_Value[]={
							{(MITEM*)Null_F1,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_seq_clearall,			(Func)Read_CalDefault,				NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_exit,					(Func)Pre_Menu,						NULL1,								0,2}};

MITEMS _Seq_Main[]={
							{(MITEM*)_Normal_Sequence,		(Func)Seq_Select,					NULL1,								0,2},
							{(MITEM*)_Fast_Sequence,		(Func)Seq_Select,					NULL1,								0,2},
							{(MITEM*)Null_F3,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_pre_menu,				(Func)Pre_Menu,						NULL1,								0,2}};

MITEMS _Seq_Normal[]={
							{(MITEM*)_NSeq_ONOFF,			(Func)EnableFlag,					&P3k_Chan_Data.Load_Type,			10,1},
							{(MITEM*)_seq_edit,				(Func)EditNormalSeq,				NULL1,								0,2},
							{(MITEM*)_seq_save,				(Func)Save_Data,					&SEQ_Save_Status,					2,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_pre_menu,				(Func)Pre_Menu,						NULL1,								0,2}};

MITEMS _Seq_Fast[]={
							{(MITEM*)_FSeq_ONOFF,			(Func)EnableFlag,					&P3k_Chan_Data.Load_Type,			10,1},
							{(MITEM*)_seq_edit,				(Func)EditFastSeq,					NULL1,								0,2},
							{(MITEM*)_seq_save,				(Func)Save_Data,					&SEQ_Save_Status,					2,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_pre_menu,				(Func)Pre_Menu,						NULL1,								0,2}};

MITEMS _NSeq_EDIT[]={
							{(MITEM*)_ins_point,			(Func)Add_NSeq,						NULL1,								0,2},
							{(MITEM*)_del_point,			(Func)Del_NSeq,						NULL1,								0,2},
							{(MITEM*)_seq_save,				(Func)Save_Data,					&SEQ_Save_Status,					2,2},		
							{(MITEM*)_del_pointall,			(Func)Del_NSeq_all,					NULL1,								0,2},

							{(MITEM*)_pre_menu,				(Func)Pre_Menu,						NULL1,								0,2}};

MITEMS _FSeq_EDIT[]={
							{(MITEM*)_ins_point,			(Func)Add_FSeq,						NULL1,								0,2},
							{(MITEM*)_del_point,			(Func)Del_FSeq,						NULL1,								0,2},
#if Enable_fseq_deletAll
							{(MITEM*)_fseq_edit_save,		(Func)Save_Data,					&SEQ_Save_Status,					2,2},
#else
							{(MITEM*)_seq_save,				(Func)Save_Data,					&SEQ_Save_Status,					2,2},
#endif
							{(MITEM*)_fill,					(Func)Fill_Function,				NULL1,								0,2},
							{(MITEM*)_pre_menu,				(Func)Pre_Menu,						NULL1,								0,2}};

MITEMS _FSeq_FILL[]={
							{(MITEM*)Null_F1,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_save2,				(Func)Save_Fill_Action,				NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_pre_menu,				(Func)Pre_Menu,						NULL1,								0,2}};

MITEMS _NSeq_execute[]={
							{(MITEM*)_seq_pause,			(Func)Prog_Seq_Stop_Continue,		&Prog_Seq_Data.SEQ_Stop_Continue,	3,2},
							{(MITEM*)_seq_next,				(Func)Prog_Seq_Next,				&Prog_Seq_Data.MANUAL_CTRL,			2,2},
							{(MITEM*)Null_F3,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F5,				(Func)Empty_Func,					NULL1,								0,2}};

MITEMS _Power_Func[]={
							{(MITEM*)Null_F1,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F3,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_uninstall,			(Func)OptionUninstall,				&OptionInfo[0].Un_install,			2,2},
							{(MITEM*)_pre_menu,				(Func)Pre_Menu,						NULL1,								0,2}};


MITEMS _Func_Main_2[]= {
#if Enable_OPP_function	
							{(MITEM*)_function_opp_b,		(Func)APP_Function_OPP,				NULL1,								0,2},
#else
							{(MITEM*)Null_F1,				(Func)Empty_Func,					NULL1,								0,2},
#endif
#if Enable_Battery_Discharge
							{(MITEM*)_batt,					(Func)goto_func_batt,				NULL1,								0,2},
#else
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
#endif
#if Enable_LED_function
							{(MITEM*)_LED,					(Func)goto_func_led,				NULL1,								0,2},
							{(MITEM*)_LED2,					(Func)goto_curve_led,				NULL1,								0,2},
#else
							{(MITEM*)Null_F3,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
#endif
							{(MITEM*)_pre_menu,				(Func)Pre_Menu,						NULL1,								0,2}
};

#if Enable_OCP_function

MITEMS _Func_OCP[]={
							{(MITEM*)_function_ocp_s,		(Func)EnableFlag,					&P3k_Chan_Data.Load_Type,			10,1},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_seq_save,				(Func)Save_Data,					&SEQ_Save_Status,					2,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_pre_menu,				(Func)Pre_Menu,						NULL1,								0,2}};

MITEMS _Func_OCP_execute[]={
							{(MITEM*)Null_F1,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F3,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F5,				(Func)Empty_Func,					NULL1,								0,2}};


MITEMS _Cal_Value_1[]={
							{(MITEM*)Null_F1,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_seq_clearall,			(Func)Read_CalDefault,				NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_exit,					(Func)Pre_Menu,						NULL1,								0,2}};

MITEMS _Func_OPP[]= {
							{(MITEM*)_function_opp_s,		(Func)EnableFlag,					&P3k_Chan_Data.Load_Type,			10,1},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_seq_save,				(Func)Save_Data,					&SEQ_Save_Status,					2,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_pre_menu,				(Func)Pre_Menu,						NULL1,								0,2}
};

MITEMS _Func_OPP_execute[]= {
							{(MITEM*)Null_F1,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F3,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F5,				(Func)Empty_Func,					NULL1,								0,2}
};

#if Enable_Battery_Discharge

MITEMS _Func_batt[]= {
							{(MITEM*)_batt_ONOFF,			(Func)EnableFlag,					&P3k_Chan_Data.Load_Type,			10,1},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F3,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_pre_menu,				(Func)Pre_Menu,						NULL1,								0,2}
};

MITEMS _Func_batt_execute[]= {	
							{(MITEM*)Null_F1,				(Func)Empty_Func,					NULL1,								3,2},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F3, 				(Func)Empty_Func, 					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_exit,					(Func)Pre_Menu,						NULL1,								0,2}
};
#endif
#if Enable_LED_function
MITEMS _Func_LED[]= {
							{(MITEM*)_LED_ONOFF,			(Func)EnableFlag,						&P3k_Chan_Data.Load_Type,		10,1},
							{(MITEM*)_editLed,				(Func)goto_fled_option,				&P3k_Chan_Data.Load_Type,			0,2},
							{(MITEM*)_Config_GONG, 			(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					&P3k_Chan_Data.Load_Type,			0,2},
							{(MITEM*)_pre_menu,				(Func)Pre_Menu,						NULL1,								0,2}
};

MITEMS _Func_LED_edit[]= {
							{(MITEM*)Null_F1,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_seq_save,				(Func)Save_Data,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_pre_menu,				(Func)Pre_Menu,						NULL1,								0,2}
};

MITEMS _Func_LED_execute[]= {
							{(MITEM*)Null_F1,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F3,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_exit,					(Func)Pre_Menu,						NULL1,								0,2}
};

MITEMS _Func_CLED[]= {
							{(MITEM*)_CLED_ONOFF,			(Func)EnableFlag,					&P3k_Chan_Data.Load_Type,			10,1},
							{(MITEM*)_editLed,				(Func)goto_cled_option,				&P3k_Chan_Data.Load_Type,			0,2},
							{(MITEM*)_Config_GONG, 			(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					&P3k_Chan_Data.Load_Type,			0,2},
							{(MITEM*)_pre_menu,				(Func)Pre_Menu,						NULL1,								0,2}
};

MITEMS _Func_CLED_edit[]= {
							{(MITEM*)Null_F1,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_seq_save,				(Func)Save_Data,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_pre_menu,				(Func)Pre_Menu,						NULL1,								0,2}
};

MITEMS _Func_CLED_execute[]= {
							{(MITEM*)Null_F1,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F2,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F3,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)Null_F4,				(Func)Empty_Func,					NULL1,								0,2},
							{(MITEM*)_exit,					(Func)Pre_Menu,						NULL1,								0,2}
};

#endif

#endif


/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/

MENU _menu[MAXMENU]={
				(MENU)_normal_cc,			/* 0x00 P_CC				*/
				(MENU)_normal_cr,			/* 0x01 P_CR				*/
				(MENU)_normal_cv,			/* 0x02 P_CV				*/
				(MENU)_normal_cp,			/* 0x03 P_CP				*/
				(MENU)_config_Prot,			/* 0x04 P_CC_SPEC		*/
				(MENU)_config_Prot,			/* 0x05 P_CR_SPEC		*/
				(MENU)_config_Prot,			/* 0x06 P_CV_SPEC		*/
				(MENU)_config_Prot,			/* 0x07 P_CP_SPEC		*/
				
				(MENU)_config_Prot,			/* 0x08 P_CONF_PROT		*/
				(MENU)_config_Prot,			/* 0x09 P_CONF_OTHER	*/
				(MENU)_config_Para,			/* 0x0A P_CONF_Para		*/
				(MENU)_config_Para,			/* 0x0B P_CONF_KNOB		*/
				(MENU)_config_Para,			/* 0x0C P_CONF_Ext		*/

				(MENU)_Func_Main,			/* 0x0D P_FUNC_MAIN		*/
				
				(MENU)_prog_main,			/* 0x0E P_PROG_MAIN		*/
				(MENU)_prog_chain,			/* 0x0F P_PROG_CHAIN	*/
				(MENU)_prog_execute,		/* 0x10 P_PROG_EXECUTE	*/
				(MENU)_prog_detail,			/* 0x11 P_PROG_Detail		*/
				
				(MENU)_Seq_Main,			/* 0x12 P_Seq_FUNC		*/
				(MENU)_Seq_Normal,			/* 0x13 P_Seq_Normal		*/
				(MENU)_Seq_Fast,			/* 0x14 P_Seq_Fast		*/
				(MENU)_NSeq_EDIT,			/* 0x15 P_NSeq_Edit		*/
				(MENU)_FSeq_EDIT,			/* 0x16 P_FSeq_Edit		*/
				(MENU)_NSeq_execute,		/* 0x17 P_NSeq_EXECUTE	*/
				(MENU)_FSeq_FILL,			/* 0x18 P_FSeq_Fill		*/
				(MENU)_Nothing,				/* 0x19 P_FSeq_EXECUTE	*/	
				
				(MENU)_file,				/* 0x1A P_FILE_CHAN		*/
				(MENU)_file_machine,		/* 0x1B P_FILE_MACHINE	*/
				
				(MENU)_cal_main,			/* 0x1C P_CAL_MODE		*/
				
				(MENU)_utility_main,		/* 0x1D P_UTIL_MAIN		*/
				(MENU)_utility_main,		/* 0x1E P_UTIL_INTERFACE	*/
				(MENU)_utility_main,		/* 0x1F P_UTIL_T_DATE	*/
				(MENU)_utility_main,		/* 0x20 P_UTIL_LOAD		*/
				(MENU)_utility_main,		/* 0x21 P_UTIL_OTHER		*/
				(MENU)_utility_main,		/* 0x22 P_UTIL_SYSINFO	*/
				(MENU)_utility_main,		/* 0x23 P_UTIL_SYSMEMO	*/
				
				(MENU)_utility_keypad,		/* 0x24 P_UTIL_KEYPAD	*/
				(MENU)_utility_file,		/* 0x25 P_UTIL_FILE		*/

				(MENU)_Input_Password,		/* 0x26 P_Input_Password	*/
				(MENU)_Input_Serial,		/* 0x27 P_Input_Serial		*/

				(MENU)_help_help,			/* 0x28 P_HELP_HELP		*/

				(MENU)_Lua_execute,			/* 0x29 P_LUA_EXECUTE	*/
				
				(MENU)_Test_Func,			/* 0x2A P_Test_Func		*/
				(MENU)_Power_Func,			/* 0x2B P_FUNC_POWER	*/
				(MENU)_Cal_Value,			/* 0x2C P_Cal_Value	*/
#if Enable_OCP_function
				(MENU)_Func_Main_2, 			/* 0x2D P_FUNC_new1 	*/
				(MENU)_Func_OCP,			/* 0x2E P_FUNC_new2 	*/
				(MENU)_Func_OCP_execute,	/* 0x2F P_FUNC_new3 	*/
#endif
#if Enable_OPP_function
				(MENU)_Func_OPP,			/* 0x30 Func_OPP 			*/
				(MENU)_Func_OPP_execute,	/* 0x31 Func_OPP_execute	*/
				(MENU)_Func_batt,			/* 0x32 Func_batt 			*/
				(MENU)_Func_batt_execute,	/* 0x33 Func_batt_execute	*/
#endif
#if Enable_LED_function			
				(MENU)_Func_LED,			/* 0x34 Func_LED 			*/
				(MENU)_Func_LED_edit,		/* 0x35 Func_LED_execute	*/				
				(MENU)_Func_LED_execute,	/* 0x36 Func_LED_execute	*/
				(MENU)_Func_CLED,			/* 0x37 Func_LED_execute	*/
				(MENU)_Func_CLED_edit,		/* 0x38 Func_LED_execute	*/
				(MENU)_Func_CLED_execute,	/* 0x39 Func_LED_execute	*/
				(MENU)_Func_LED_execute,	/* 0x3A Func_LED_execute	*/
				(MENU)_Func_LED_execute,	/* 0x3B Func_LED_execute	*/
				(MENU)_Func_LED_execute,	/* 0x3C Func_LED_execute	*/
				(MENU)_Func_LED_execute,	/* 0x3D Func_LED_execute	*/
				(MENU)_Func_LED_execute,	/* 0x3E Func_LED_execute	*/
				(MENU)_Func_LED_execute,	/* 0x3F Func_LED_execute	*/
				(MENU)_Func_LED_execute,	/* 0x40 Func_LED_execute	*/
				(MENU)_Func_LED_execute,	/* 0x41 Func_LED_execute	*/
				(MENU)_Func_LED_execute,	/* 0x42 Func_LED_execute	*/
				(MENU)_Func_LED_execute,	/* 0x43 Func_LED_execute	*/
				(MENU)_Func_LED_execute,	/* 0x44 Func_LED_execute	*/
				(MENU)_Func_LED_execute,	/* 0x45 Func_LED_execute	*/
#endif

               	 };

/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/

BYTE *HelpMenuStr[MAXMENU+5][MAX_LANGUAGE]={
/* LANGUAGE						English*/ 
/* 0x00	P_CC		 	*/	{(BYTE *)Help_CC,				(BYTE *)Help_CC_T,				(BYTE *)Help_CC,				(BYTE *)Help_CC,				(BYTE *)Help_CC,				(BYTE *)Help_CC,				(BYTE *)Help_CC,				(BYTE *)Help_CC,				(BYTE *)Help_CC,				(BYTE *)Help_CC,				(BYTE *)Help_CC,				(BYTE *)Help_CC,			},
/* 0x01	P_CR			*/	{(BYTE *)Help_CR,				(BYTE *)Help_CR_T,				(BYTE *)Help_CR,				(BYTE *)Help_CR,				(BYTE *)Help_CR,				(BYTE *)Help_CR,				(BYTE *)Help_CR,				(BYTE *)Help_CR,				(BYTE *)Help_CR,				(BYTE *)Help_CR,				(BYTE *)Help_CR,				(BYTE *)Help_CR,			},
/* 0x01 P_CR			*///	{(BYTE *)&Help_CR[0],				(BYTE *)&Help_CR[0],				(BYTE *)&Help_CR[0],				(BYTE *)&Help_CR[0],				(BYTE *)&Help_CR[0],				(BYTE *)&Help_CR[0],				(BYTE *)&Help_CR[0],				(BYTE *)&Help_CR[0],				(BYTE *)&Help_CR[0],				(BYTE *)&Help_CR[0],				(BYTE *)&Help_CR[0],				(BYTE *)&Help_CR[0],			},
/* 0x02	P_CV			*/ 	{(BYTE *)Help_CV,				(BYTE *)Help_CV_T,				(BYTE *)Help_CV,				(BYTE *)Help_CV,				(BYTE *)Help_CV,				(BYTE *)Help_CV,				(BYTE *)Help_CV,				(BYTE *)Help_CV,				(BYTE *)Help_CV,				(BYTE *)Help_CV,				(BYTE *)Help_CV,				(BYTE *)Help_CV,			},
/* 0x03	P_CP	 		*/	{(BYTE *)Help_CP,				(BYTE *)Help_CP_T, 				(BYTE *)Help_CP, 				(BYTE *)Help_CP, 				(BYTE *)Help_CP, 				(BYTE *)Help_CP, 				(BYTE *)Help_CP, 				(BYTE *)Help_CP, 				(BYTE *)Help_CP, 				(BYTE *)Help_CP, 				(BYTE *)Help_CP, 				(BYTE *)Help_CP, 			},

/* 0x04 	P_CC_SPEC		*/ 	{(BYTE *)Help_Conf_GONG,		(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,		},
/* 0x05 	P_CR_SPEC		*/ 	{(BYTE *)Help_Conf_GONG,		(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,		},
/* 0x06 	P_CV_SPEC		*/ 	{(BYTE *)Help_Conf_GONG,		(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,		},
/* 0x07 	P_CP_SPEC		*/	{(BYTE *)Help_Conf_GONG,		(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,			(BYTE *)Help_Conf_GONG,		},

/* 0x08	P_CONF_PROT		*/	{(BYTE *)Help_Conf_Prot,		(BYTE *)Help_Conf_Prot_T,			(BYTE *)Help_Conf_Prot,			(BYTE *)Help_Conf_Prot,			(BYTE *)Help_Conf_Prot,			(BYTE *)Help_Conf_Prot,			(BYTE *)Help_Conf_Prot,			(BYTE *)Help_Conf_Prot,			(BYTE *)Help_Conf_Prot,			(BYTE *)Help_Conf_Prot,			(BYTE *)Help_Conf_Prot,			(BYTE *)Help_Conf_Prot,		},
/* 0x09	P_CONF_OTHER	*/	{(BYTE *)Help_Conf_Other,		(BYTE *)Help_Conf_Other,		(BYTE *)Help_Conf_Other,		(BYTE *)Help_Conf_Other,		(BYTE *)Help_Conf_Other,		(BYTE *)Help_Conf_Other,		(BYTE *)Help_Conf_Other,		(BYTE *)Help_Conf_Other,		(BYTE *)Help_Conf_Other,		(BYTE *)Help_Conf_Other,		(BYTE *)Help_Conf_Other,		(BYTE *)Help_Conf_Other,	},
/* 0x0A 	P_CONF_Para		*/	{(BYTE *)Help_Conf_Para,		(BYTE *)Help_Conf_Para_T,			(BYTE *)Help_Conf_Para,			(BYTE *)Help_Conf_Para,			(BYTE *)Help_Conf_Para,			(BYTE *)Help_Conf_Para,			(BYTE *)Help_Conf_Para,			(BYTE *)Help_Conf_Para,			(BYTE *)Help_Conf_Para,			(BYTE *)Help_Conf_Para,			(BYTE *)Help_Conf_Para,			(BYTE *)Help_Conf_Para,		},		
/* 0x0B 	P_CONF_KNOB	*/	{(BYTE *)Help_Conf_Knob,		(BYTE *)Help_Conf_Knob,			(BYTE *)Help_Conf_Knob,			(BYTE *)Help_Conf_Knob,			(BYTE *)Help_Conf_Knob,			(BYTE *)Help_Conf_Knob,			(BYTE *)Help_Conf_Knob,			(BYTE *)Help_Conf_Knob,			(BYTE *)Help_Conf_Knob,			(BYTE *)Help_Conf_Knob,			(BYTE *)Help_Conf_Knob,			(BYTE *)Help_Conf_Knob,		},
/* 0x0C 	P_CONF_Ext		*/	{(BYTE *)Help_Conf_Ext,			(BYTE *)Help_Conf_Ext,			(BYTE *)Help_Conf_Ext,			(BYTE *)Help_Conf_Ext,			(BYTE *)Help_Conf_Ext,			(BYTE *)Help_Conf_Ext,			(BYTE *)Help_Conf_Ext,			(BYTE *)Help_Conf_Ext,			(BYTE *)Help_Conf_Ext,			(BYTE *)Help_Conf_Ext,			(BYTE *)Help_Conf_Ext,			(BYTE *)Help_Conf_Ext,		},

/* 0x0D	P_FUNC_MAIN		*/	{(BYTE *)Help_Func_Main,		(BYTE *)Help_Func_Main,			(BYTE *)Help_Func_Main,			(BYTE *)Help_Func_Main,			(BYTE *)Help_Func_Main,			(BYTE *)Help_Func_Main,			(BYTE *)Help_Func_Main,			(BYTE *)Help_Func_Main,			(BYTE *)Help_Func_Main,			(BYTE *)Help_Func_Main,			(BYTE *)Help_Func_Main,			(BYTE *)Help_Func_Main,		},

/* 0x0E	P_PROG_MAIN		*/	{(BYTE *)Help_Prog_main,		(BYTE *)Help_Prog_main_T,			(BYTE *)Help_Prog_main,			(BYTE *)Help_Prog_main,			(BYTE *)Help_Prog_main,			(BYTE *)Help_Prog_main,			(BYTE *)Help_Prog_main,			(BYTE *)Help_Prog_main,			(BYTE *)Help_Prog_main,			(BYTE *)Help_Prog_main,			(BYTE *)Help_Prog_main,			(BYTE *)Help_Prog_main,		},
/* 0x0F	P_PROG_CHAIN	*/	{(BYTE *)Help_Prog_chain,		(BYTE *)Help_Prog_chain,		(BYTE *)Help_Prog_chain,		(BYTE *)Help_Prog_chain,		(BYTE *)Help_Prog_chain,		(BYTE *)Help_Prog_chain,		(BYTE *)Help_Prog_chain,		(BYTE *)Help_Prog_chain,		(BYTE *)Help_Prog_chain,		(BYTE *)Help_Prog_chain,		(BYTE *)Help_Prog_chain,		(BYTE *)Help_Prog_chain,	},
/* 0x10 	P_PROG_EXECUTE	*/	{(BYTE *)Help_Prog_Execute, 	(BYTE *)Help_Prog_Execute,		(BYTE *)Help_Prog_Execute,		(BYTE *)Help_Prog_Execute,		(BYTE *)Help_Prog_Execute,		(BYTE *)Help_Prog_Execute,		(BYTE *)Help_Prog_Execute,		(BYTE *)Help_Prog_Execute,		(BYTE *)Help_Prog_Execute,		(BYTE *)Help_Prog_Execute,		(BYTE *)Help_Prog_Execute,		(BYTE *)Help_Prog_Execute,	},
/* 0x11 	P_PROG_Detail	*/	{(BYTE *)Help_Prog_Next,		(BYTE *)Help_Prog_Next, 		(BYTE *)Help_Prog_Next, 		(BYTE *)Help_Prog_Next, 		(BYTE *)Help_Prog_Next, 		(BYTE *)Help_Prog_Next, 		(BYTE *)Help_Prog_Next, 		(BYTE *)Help_Prog_Next, 		(BYTE *)Help_Prog_Next, 		(BYTE *)Help_Prog_Next, 		(BYTE *)Help_Prog_Next, 		(BYTE *)Help_Prog_Next, 	},

/* 0x12	P_Seq_FUNC		*/	{(BYTE *)Help_Seq_Func,			(BYTE *)Help_Seq_Func,			(BYTE *)Help_Seq_Func,			(BYTE *)Help_Seq_Func,			(BYTE *)Help_Seq_Func,			(BYTE *)Help_Seq_Func,			(BYTE *)Help_Seq_Func,			(BYTE *)Help_Seq_Func,			(BYTE *)Help_Seq_Func,			(BYTE *)Help_Seq_Func,			(BYTE *)Help_Seq_Func,			(BYTE *)Help_Seq_Func,		},
/* 0x13	P_Seq_Normal		*/	{(BYTE *)Help_Seq_Normal,		(BYTE *)Help_Seq_Normal,		(BYTE *)Help_Seq_Normal,		(BYTE *)Help_Seq_Normal,		(BYTE *)Help_Seq_Normal,		(BYTE *)Help_Seq_Normal,		(BYTE *)Help_Seq_Normal,		(BYTE *)Help_Seq_Normal,		(BYTE *)Help_Seq_Normal,		(BYTE *)Help_Seq_Normal,		(BYTE *)Help_Seq_Normal,		(BYTE *)Help_Seq_Normal,	},
/* 0x14	P_Seq_Fast		*/	{(BYTE *)Help_Seq_Fast,			(BYTE *)Help_Seq_Fast,			(BYTE *)Help_Seq_Fast,			(BYTE *)Help_Seq_Fast,			(BYTE *)Help_Seq_Fast,			(BYTE *)Help_Seq_Fast,			(BYTE *)Help_Seq_Fast,			(BYTE *)Help_Seq_Fast,			(BYTE *)Help_Seq_Fast,			(BYTE *)Help_Seq_Fast,			(BYTE *)Help_Seq_Fast,			(BYTE *)Help_Seq_Fast,		},
/* 0x15	P_NSeq_Edit		*/	{(BYTE *)Help_NSeq_Edit,		(BYTE *)Help_NSeq_Edit,			(BYTE *)Help_NSeq_Edit,			(BYTE *)Help_NSeq_Edit,			(BYTE *)Help_NSeq_Edit,			(BYTE *)Help_NSeq_Edit,			(BYTE *)Help_NSeq_Edit,			(BYTE *)Help_NSeq_Edit,			(BYTE *)Help_NSeq_Edit,			(BYTE *)Help_NSeq_Edit,			(BYTE *)Help_NSeq_Edit,			(BYTE *)Help_NSeq_Edit,		},
/* 0x16	P_FSeq_Edit		*/	{(BYTE *)Help_FSeq_Edit,		(BYTE *)Help_FSeq_Edit,			(BYTE *)Help_FSeq_Edit,			(BYTE *)Help_FSeq_Edit,			(BYTE *)Help_FSeq_Edit,			(BYTE *)Help_FSeq_Edit,			(BYTE *)Help_FSeq_Edit,			(BYTE *)Help_FSeq_Edit,			(BYTE *)Help_FSeq_Edit,			(BYTE *)Help_FSeq_Edit,			(BYTE *)Help_FSeq_Edit,			(BYTE *)Help_FSeq_Edit,		},
/* 0x17	P_NSeq_EXECUTE	*/	{(BYTE *)Help_NSeq_Execute,		(BYTE *)Help_NSeq_Execute,		(BYTE *)Help_NSeq_Execute,		(BYTE *)Help_NSeq_Execute,		(BYTE *)Help_NSeq_Execute,		(BYTE *)Help_NSeq_Execute,		(BYTE *)Help_NSeq_Execute,		(BYTE *)Help_NSeq_Execute,		(BYTE *)Help_NSeq_Execute,		(BYTE *)Help_NSeq_Execute,		(BYTE *)Help_NSeq_Execute,		(BYTE *)Help_NSeq_Execute,	},
/* 0x18	P_FSeq_Fill		*/	{(BYTE *)Help_FSeq_Fill,		(BYTE *)Help_FSeq_Fill,			(BYTE *)Help_FSeq_Fill,			(BYTE *)Help_FSeq_Fill,			(BYTE *)Help_FSeq_Fill,			(BYTE *)Help_FSeq_Fill,			(BYTE *)Help_FSeq_Fill,			(BYTE *)Help_FSeq_Fill,			(BYTE *)Help_FSeq_Fill,			(BYTE *)Help_FSeq_Fill,			(BYTE *)Help_FSeq_Fill,			(BYTE *)Help_FSeq_Fill,		},
/* 0x19	P_FSeq_EXECUTE	*/	{(BYTE *)Help_FSeq_Execute,		(BYTE *)Help_FSeq_Execute,		(BYTE *)Help_FSeq_Execute,		(BYTE *)Help_FSeq_Execute,		(BYTE *)Help_FSeq_Execute,		(BYTE *)Help_FSeq_Execute,		(BYTE *)Help_FSeq_Execute,		(BYTE *)Help_FSeq_Execute,		(BYTE *)Help_FSeq_Execute,		(BYTE *)Help_FSeq_Execute,		(BYTE *)Help_FSeq_Execute,		(BYTE *)Help_FSeq_Execute,	},

/* 0x1A	P_FILE_CHAN		*/	{(BYTE *)Help_File_chan,		(BYTE *)Help_File_chan,			(BYTE *)Help_File_chan,			(BYTE *)Help_File_chan,			(BYTE *)Help_File_chan,			(BYTE *)Help_File_chan,			(BYTE *)Help_File_chan,			(BYTE *)Help_File_chan,			(BYTE *)Help_File_chan,			(BYTE *)Help_File_chan,			(BYTE *)Help_File_chan,			(BYTE *)Help_File_chan,		},
/* 0x1B	P_FILE_MACHINE	*/	{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,	},

/* 0x1C	P_CAL_MODE		*/	{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,	},

/* 0x1D	P_UTIL_MAIN		*/	{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,	},
/* 0x1E	P_UTIL_INTERFACE*/	{(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo_T,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,	},
/* 0x1F	P_UTIL_T_DATE	*/	{(BYTE *)Help_Util_sysinfo, 	(BYTE *)Help_Util_sysinfo_T,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,	},
/* 0x20	P_UTIL_LOAD		*/	{(BYTE *)Help_Util_sysinfo, 	(BYTE *)Help_Util_sysinfo_T,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,	},
/* 0x21	P_UTIL_OTHER	*/	{(BYTE *)Help_Util_sysinfo, 	(BYTE *)Help_Util_sysinfo_T,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,	},
/* 0x22	P_UTIL_SYSINFO	*/	{(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo_T,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,		(BYTE *)Help_Util_sysinfo,	},
/* 0x23  	P_UTIL_SYSMEMO	*/	{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,	},

/* 0x24	P_UTIL_KEYPAD	*/	{(BYTE *)Help_Util_keypad,		(BYTE *)Help_Util_keypad,		(BYTE *)Help_Util_keypad,		(BYTE *)Help_Util_keypad,		(BYTE *)Help_Util_keypad,		(BYTE *)Help_Util_keypad,		(BYTE *)Help_Util_keypad,		(BYTE *)Help_Util_keypad,		(BYTE *)Help_Util_keypad,		(BYTE *)Help_Util_keypad,		(BYTE *)Help_Util_keypad,		(BYTE *)Help_Util_keypad,	},
/* 0x25	P_UTIL_FILE		*/	{(BYTE *)Help_Util_file,		(BYTE *)Help_Util_file,			(BYTE *)Help_Util_file,			(BYTE *)Help_Util_file,			(BYTE *)Help_Util_file,			(BYTE *)Help_Util_file,			(BYTE *)Help_Util_file,			(BYTE *)Help_Util_file,			(BYTE *)Help_Util_file,			(BYTE *)Help_Util_file,			(BYTE *)Help_Util_file,			(BYTE *)Help_Util_file,		},		

/* 0x26	P_Input_Password	*/	{(BYTE *)Help_Input_Password,	(BYTE *)Help_Input_Password,	(BYTE *)Help_Input_Password,	(BYTE *)Help_Input_Password,	(BYTE *)Help_Input_Password,	(BYTE *)Help_Input_Password,	(BYTE *)Help_Input_Password,	(BYTE *)Help_Input_Password,	(BYTE *)Help_Input_Password,	(BYTE *)Help_Input_Password,	(BYTE *)Help_Input_Password,	(BYTE *)Help_Input_Password,},
/* 0x27	P_Input_Serial	*/	{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,	},		

/* 0x28	P_HELP_HELP		*/	{(BYTE *)Help_Help_Key,			(BYTE *)Help_Help_Key,			(BYTE *)Help_Help_Key,			(BYTE *)Help_Help_Key,			(BYTE *)Help_Help_Key,			(BYTE *)Help_Help_Key,			(BYTE *)Help_Help_Key,			(BYTE *)Help_Help_Key,			(BYTE *)Help_Help_Key,			(BYTE *)Help_Help_Key,			(BYTE *)Help_Help_Key,			(BYTE *)Help_Help_Key,		},
/* 0x29	P_LUA_EXECUTE	*/	{(BYTE *)Help_Lua_Execute,		(BYTE *)Help_Lua_Execute,		(BYTE *)Help_Lua_Execute,		(BYTE *)Help_Lua_Execute,		(BYTE *)Help_Lua_Execute,		(BYTE *)Help_Lua_Execute,		(BYTE *)Help_Lua_Execute,		(BYTE *)Help_Lua_Execute,		(BYTE *)Help_Lua_Execute,		(BYTE *)Help_Lua_Execute,		(BYTE *)Help_Lua_Execute,		(BYTE *)Help_Lua_Execute,	},

/* 0x2A	P_Test_Func*/		{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,	},		
/* 0x2B	P_FUNC_POWER*/		{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,	},
/* 0x2C  P_Cal_Value	*/		{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,	},
#if Enable_OCP_function
	/* 0x2C P_FUNC_MAIN_2*/		{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
	/* 0x2D 	P_FUNC_OCP*/		{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
	/* 0x2E 	P_FUNC_OCP_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	

	/* 0x2F 	_Cal_Value*/			{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
#endif
#if Enable_OPP_function
	/* 0x30	P_FUNC_OPP*/		{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},
	/* 0x31	P_FUNC_OPP_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},
	/* 0x32	_Func_batt*/			{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},
	/* 0x33	_Func_batt_execute*/	{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},
	/* 0x34	P_FUNC_FLED*/		{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},
	/* 0x35	P_FUNC_FLED_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
#endif
#if Enable_LED_function
	/* 0x36	P_FUNC_FLED_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
	/* 0x37	P_FUNC_FLED_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
	/* 0x38	P_FUNC_FLED_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
	/* 0x39	P_FUNC_FLED_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
	/* 0x3A	P_FUNC_FLED_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
	/* 0x3B	P_FUNC_FLED_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
	/* 0x3C	P_FUNC_FLED_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
	/* 0x3D	P_FUNC_FLED_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
	/* 0x3E	P_FUNC_FLED_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
	/* 0x3F	P_FUNC_FLED_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
	/* 0x40	P_FUNC_FLED_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
	/* 0x41	P_FUNC_FLED_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
	/* 0x42	P_FUNC_FLED_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
	/* 0x43	P_FUNC_FLED_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
	/* 0x44	P_FUNC_FLED_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
	/* 0x45	P_FUNC_FLED_EXECUTE*/{(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,		(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,			(BYTE *)Help_No_Content,		},	
#endif
	};
