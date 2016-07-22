#include "../includes.h" 
#include "../menu/head.h"

const default_str P3111_CC[]={
/*		Def		Max		Min		Resolution	Unit		precision*/
	{ 	0,		22050,	0,		0.0001,		0,			4		},	/* CC (Static Low) A Value		 		*/
	{	0,		22050,	0,		0.0001,		0,			4		},	/* CC (Static Low) B Value				*/
	{ 	2667,	2668,	266,	0.0006,		0,			4	 	},	/* CC (Static Low) SlewRate Up 			*/
	{ 	2667,	2668,	266,	0.0006,		0,			4	 	},	/* CC (Static Low) SlewRate Dn 			*/
	{ 	0,		22050,	0,		0.0001,		0,			4	 	},	/* CC (Dyna Low) Label 1		 		*/
	{	0,		22050,	0,		0.0001,		0,			4	 	},	/* CC (Dyna Low) Label 2 				*/
	{	2667,	2668,	266,	0.0006,		0,			4	 	},	/* CC (Dyna Low) SlewRate Up 			*/
	{	2667,	2668,	266,	0.0006,		0,			4	 	},	/* CC (Dyna Low) SlewRate Dn		 	*/
	{	25,		10000,	25,		0.001,		0,			3	 	},	/* CC (Dyna Low) Time 1 				*/
	{	25,		10000,	25,		0.001,		0,			3	 	},	/* CC (Dyna Low) Time 2 				*/		
	{	0,		22050,	0,		0.001,		0,			3		},	/* CC (Static Mid) A Value				*/
	{	0,		22050,	0,		0.001,		0,			3		},	/* CC (Static Mid) B Value				*/
	{	2667,	2668,	266,	0.006, 		0,			3		},	/* CC (Static Mid) SlewRate Up			*/
	{	2667,	2668,	266,	0.006, 		0,			3		},	/* CC (Static Mid) SlewRate Dn			*/
	{	0,		22050,	0,		0.001,		0,			3		},	/* CC (Dyna Mid) Label 1 				*/
	{	0,		22050,	0,		0.001,		0,			3		},	/* CC (Dyna Mid) Label 2 				*/
	{	2667,	2668,	266,	0.006, 		0,			3		},	/* CC (Dyna Mid) SlewRate Up 			*/
	{	2667,	2668,	266,	0.006, 		0,			3		},	/* CC (Dyna Mid) SlewRate Dn 			*/
	{	1,		30000,	10, 	1,			0,			3		},	/* CC (Dyna Mid) Time 1				*/
	{	1,		30000,	10, 	1,			0,			3		},	/* CC (Dyna Mid) Time 2				*/
	{	0,		22050,	0,		0.01,		0,			2	 	},	/* CC (Static Hi) A Value				*/
	{	0,		22050,	0,		0.01,		0,			2	 	},	/* CC (Static Hi) B Value				*/
	{	2667,	2668,	266,	0.06, 		0,			2 		},	/* CC (Static Hi) SlewRate Up 			*/
	{	2667,	2668,	266,	0.06, 		0,			2	 	},	/* CC (Static Hi) SlewRate Dn 			*/
	{	0,		22050,	0,		0.01,		0,			2	 	},	/* CC (Dyna Hi) Label 1					*/
	{	0,		22050,	0,		0.01,		0,			2	 	},	/* CC (Dyna Hi) Label 2 				*/
	{	2667,	2668,	266,	0.06, 		0,			2	 	},	/* CC (Dyna Hi) SlewRate Up 			*/
	{	2667,	2668,	266,	0.06, 		0,			2	 	},	/* CC (Dyna Hi) SlewRate Dn 			*/
	{	1,		30000,	10,		1,			0,			3	 	},	/* CC (Dyna Hi) Time 1 				*/
	{	1,		30000,	10,		1,			0,			3	 	}	/* CC (Dyna Hi) Time 2 				*/
};

/* CR mode resolurtion = Max value of Ohm */
const default_str P3111_CR[]={
	{	0,		61250,	0,		0.0240,		0,			4		},	/* CR (Static Low) A Value 				*/
	{	0,		61250,	0,		0.0240, 	0,			4		},	/* CR (Static Low) B Value 				*/
	{	2667,	2668,	266,	0.00006,	0,			5		},	/* CR (Static Low) SlewRate Up			*/
	{	2667,	2668,	266,	0.00006,	0,			5		},	/* CR (Static Low) SlewRate Dn			*/
	{	0,		61250,	0,		0.0240,		0,			4		},	/* CR (Dyna Low) A Value				*/
	{	0,		61250,	0,		0.0240,		0,			4		},	/* CR (Dyna Low) B Value				*/
	{	2667,	2668,	266,	0.00006, 	0,			5		},	/* CR (Dyna Low) SlewRate Up			*/
	{	2667,	2668,	266,	0.00006, 	0,			5		},	/* CR (Dyna Low) SlewRate Dn			*/
	{	25, 	10000,	25, 	0.001,		0,			3		},	/* CR (Dyna Low) Time 1 				*/
	{	25, 	10000,	25, 	0.001,		0,			3		},	/* CR (Dyna Low) Time 2 				*/		
	{	0,		61250,	0,		0.240,		0,			3		},	/* CR (Static Mid) A Value				*/
	{	0,		61250,	0,		0.240,		0,			3		},	/* CR (Static Mid) B Value				*/
	{	2667,	2668,	266,	0.0006,		0,			4		},	/* CR (Static Mid) SlewRate Up			*/
	{	2667,	2668,	266,	0.0006,		0,			4		},	/* CR (Static Mid) SlewRate Dn			*/
	{	0,		61250,	0,		0.240,		0,			3		},	/* CR (Dyna Mid) A Value 				*/
	{	0,		61250,	0,		0.240,		0,			3		},	/* CR (Dyna Mid) B Value 				*/
	{	2667,	2668,	266,	0.0006, 	0,			4		},	/* CR (Dyna Mid) SlewRate Up 			*/
	{	2667,	2668,	266,	0.0006,		0,			4		},	/* CR (Dyna Mid) SlewRate Dn 			*/
	{	1,		30000,	10, 	1,			0,			3		},	/* CR (Dyna Mid) Time 1				*/
	{	1,		30000,	10, 	1,			0,			3		},	/* CR (Dyna Mid) Time 2				*/			
	{	0,		61250,	0,		2.40,		0,			2		},	/* CR (Static Hi) A Value 				*/
	{	0,		61250,	0,		2.40,		0,			2		},	/* CR (Static Hi) B Value 				*/
	{	2667,	2668,	266,	0.006,		0,			3		},	/* CR (Static Hi) SlewRate Up			*/
	{	2667,	2668,	266,	0.006,		0,			3		},	/* CR (Static Hi) SlewRate Dn			*/
	{	0,		61250,	0,		2.40,		0,			2		},	/* CR (Dyna Hi) A Value 				*/
	{	0,		61250,	0,		2.40,		0,			2		},	/* CR (Dyna Hi) B Value 				*/
	{	2667,	2668,	266,	0.006,		0,			3		},	/* CR (Dyna Hi) SlewRate Up			*/
	{	2667,	2668,	266,	0.006,		0,			3		},	/* CR (Dyna Hi) SlewRate Dn			*/
	{	1,		30000,	10,		1,			0,			3	 	},	/* CR (Dyna Hi) Time 1 				*/
	{	1,		30000,	10,		1,			0,			3	 	}	/* CR (Dyna Hi) Time 2 				*/		
};

const default_str P3111_CV[]={
	{	15000,	15750,	0,		0.001,		0,			3		},	/* CV (Volt Range Low) A Value			*/
	{	15000,	15750,	0,		0.001,		0,			3		},	/* CV (Volt Range Low) B Value			*/
	{	21000,	22050,	0,		0.00001,	0,			5		},	/* CV (Range Low) Current Limit			*/
	{	15000,	15750,	0,		0.01,		0,			2		},	/* CV (Volt Range Hi) A Value			*/
	{	15000,	15750,	0,		0.01,		0,			2		},	/* CV (Volt Range Hi) B Value			*/
	{	21000,	22050,	0,		0.0001,		0,			4		},	/* CV (Range Mid) Current Limit			*/	
	{	15000,	15750,	0,		0.01,		0,			2		},	/* Not Use							*/
	{	15000,	15750,	0,		0.01,		0,			2		},	/* Not Use							*/
	{	21000,	22050,	0,		0.001,		0,			3		}	/* CV (Range Hi) Current Limit			*/
};

const default_str P3111_CP[]={
	{ 	0,		11025,	0,		0.001,		0,			3		},	/* CP (Static Low) A Value		 		*/
	{	0,		11025,	0,		0.001,		0,			3		},	/* CP (Static Low) B Value				*/
	{ 	2667,	2668,	266,	0.00006,	0,			5	 	},	/* Not Use 							*/
	{ 	2667,	2668,	266,	0.00006,	0,			5	 	},	/* Not Use 							*/
	{ 	0,		11025,	0,		0.001,		0,			3	 	},	/* CP (Dyna Low) Label 1		 		*/
	{	0,		11025,	0,		0.001,		0,			3	 	},	/* CP (Dyna Low) Label 2 				*/
	{	2667,	2668,	266,	0.00006,	0,			5	 	},	/* Not Use 							*/
	{	2667,	2668,	266,	0.00006,	0,			5	 	},	/* Not Use		 					*/
	{	25,		10000,	25,		0.001,		0,			3	 	},	/* CP (Dyna Low) Time 1 				*/
	{	25,		10000,	25,		0.001,		0,			3	 	},	/* CP (Dyna Low) Time 2 				*/		
	{	0,		11025,	0,		0.01,		0,			2		},	/* CP (Static Mid) A Value				*/
	{	0,		11025,	0,		0.01,		0,			2		},	/* CP (Static Mid) B Value				*/
	{	2667,	2668,	266,	0.0006,		0,			4		},	/* Not Use 							*/
	{	2667,	2668,	266,	0.0006,		0,			4		},	/* Not Use 							*/
	{	0,		11025,	0,		0.01,		0,			2		},	/* CP (Dyna Mid) Label 1 				*/
	{	0,		11025,	0,		0.01,		0,			2		},	/* CP (Dyna Mid) Label 2 				*/
	{	2667,	2668,	266,	0.0006,		0,			4		},	/* Not Use 							*/
	{	2667,	2668,	266,	0.0006,		0,			4		},	/* Not Use 							*/
	{	1,		30000,	10, 	1,			0,			3		},	/* CP (Dyna Mid) Time 1				*/
	{	1,		30000,	10, 	1,			0,			3		},	/* CP (Dyna Mid) Time 2				*/
	{	0,		11025,	0,		0.1,		0,			1	 	},	/* CP (Static Hi) A Value				*/
	{	0,		11025,	0,		0.1,		0,			1	 	},	/* CP (Static Hi) B Value				*/
	{	2667,	2668,	266,	0.006,		0,			3	 	},	/* Not Use 							*/
	{	2667,	2668,	266,	0.006,		0,			3	 	},	/* Not Use 							*/
	{	0,		11025,	0,		0.1,		0,			1	 	},	/* CP (Dyna Hi) Label 1					*/
	{	0,		11025,	0,		0.1,		0,			1	 	},	/* CP (Dyna Hi) Label 2 				*/
	{	2667,	2668,	266,	0.006,		0,			3	 	},	/* Not Use 							*/
	{	2667,	2668,	266,	0.006,		0,			3	 	},	/* Not Use 							*/
	{	1,		30000,	10,		1,			0,			3	 	},	/* CP (Dyna Hi) Time 1 					*/
	{	1,		30000,	10,		1,			0,			3	 	}	/* CP (Dyna Hi) Time 2 					*/
};

const default_str P3111_CC_SPEC[]={
	{	7500,	15000,	0,		0.01,		0,			2		},	/* CC Spec Center Value			*/
	{	15000,	15000,	0,		0.01,		0,			2		},	/* CC Spec High Value				*/
	{	0,		0,		0,		0.01,		0,			2		}	/* CC Spec Low Value				*/
};

const default_str P3111_CR_SPEC[]={
	{	7500,	15000,	0,		0.01,		0,			2		},	/* CR Spec Center Value			*/
	{	15000,	15000,	0,		0.01,		0,			2		},	/* CR Spec High Value				*/
	{	0,		0,		0,		0.01,		0,			2		}	/* CR Spec Low Value				*/
};

const default_str P3111_CV_SPEC[]={
	{	10500,	21000,	0,		0.01,		0,			2		},	/* CV Spec Center Value			*/
	{	21000,	21000,	0,		0.01,		0,			2		},	/* CV Spec High Value			*/
	{	0,		0,		0,		0.01,		0,			2		}	/* CV Spec Low Value			*/
};

const default_str P3111_CP_SPEC[]={
	{	7500,	15000,	0,		0.01,		0,			2		},	/* CP Spec Center Value			*/
	{	15000,	15000,	0,		0.01,		0,			2		},	/* CP Spec High Value				*/
	{	0,		0,		0,		0.01,		0,			2		}	/* CP Spec Low Value				*/
};

const default_str P3111_CONF[]={
	{	0,		15000,	0,		0.001,		0,			3		},	/* Von Voltage (Low) 				*/
	{	0,		15000,	0,		0.01,		0,			2		},	/* Von Voltage (Hi)				*/
	{	0,		200,	0,		1,			0,			0		},	/* Soft Start Time(ms)				*/
	{	0,		500,	0,		1,			0,			0		}	/* Cut Off Time(S)					*/ //不用, Adam 只接寫在code裡
};

const default_str P3111_PROT[]={
	{	231,	231,	20,		0.01,		0,			2		},	/* 		OCP (Low)				*/
	{	2310,	2310,	20, 	0.01,		0,			2		},	/*		OCP (Mid)				*/
	{	23100,	23100,	20,		0.01,		0,			2		},	/* 		OCP	(High)				*/
	{	11550,	11550,	10,		0.1,		0,			4		},	/* 		OPP	(Low)				*/
	{	11550,	11550,	10, 	0.1, 		0,			3		},	/*		OPP (Mid)				*/
	{	11550,	11550,	10,		0.1,		0,			2		},	/* 		OPP	(High)				*/
	{	0,		16500,	0,		0.001,		0,			3		},	/*		UVP(Low)					*/
	{	0,		16500,	0,		0.01,		0,			2		},	/* 		UVP(Hi)					*/	
	{	16501,	16501,	0,		0.001,		0,			3		},	/*		OVP(Low)				*/
	{	16501,	16501,	0,		0.01,		0,			2		}	/* 		OVP(Hi)					*/	
	};

const default_str P3111_CALI_HP[]={
	{	21000,	7000,	10500,	0.0001,		0,			5		},	/* CCL Unit:A 					*/
	{	17000,	16500,	15000,	0.0001,		0,			4		},	/* CRL Unit:1/R -- use G (1/R) value */
	{	15000,	16500,	15000,	0.001,		0,			3		},	/* CVL Unit:V						*/
	{	10000,	10000,	10000,	0.001,		0,			4		},	/* CPL							*/
	{	15000,	16500,	15000,	0.001,		0,			3		},	/* CXCVL							*/
	{	333,	1000,	0,		0.001,		0,			3		},	/* F_IMON						*/
	{	3333,	10000,	0,		0.001,		0,			3		},	/* R_IMON						*/
	{	21000,	19685,	21000,	0.0001,		0,			5		},	/* External V(CCL) Unit:A 			*/
	{	21000,	23100,	21000,	0.0001,		0,			5		},	/* External R(CCL) Unit:A 			*/

	{	21000,	7000,	10500,	0.001,		0,			4		},	/* CCM Unit:A 					*/
	{	17000,	16500,	15000,	0.0001,		0,			4		},	/* CRM Unit:1/R -- use G (1/R) value	*/
	{	15000,	16500,	15000,	0.001,		0,			3		},	/* CVM Unit:V 					*/
	{	10000,	10000,	10000,	0.001,		0,			4		},	/* CPM 							*/
	{	15000,	16500,	15000,	0.001,		0,			3		},	/* CXCVM						*/
	{	33,		100,	0,		0.001,		0,			3		},	/* F_IMON						*/
	{	333,	1000,	0,		0.001,		0,			3		},	/* R_IMON						*/
	{	21000,	19685,	21000,	0.001,		0,			4		},	/* External V(CCM) Unit:A 			*/
	{	21000,	23100,	21000,	0.001,		0,			4		},	/* External R(CCM) Unit:A 			*/
	
	{	21000,	7000,	10500,	0.01,		0,			3		},	/* CCH Unit:A 					*/
	{	17000,	16500,	15000,	0.0001,		0,			4		},	/* CRH Unit:1/R -- use G (1/R) value*/
	{	15000,	16500,	15000,	0.01,		0,			2		},	/* CVH Unit:V 					*/
	{	10000,	10000,	10000,	0.001,		0,			4		},	/* CPH 							*/
	{	15000,	16500,	15000,	0.01,		0,			2		},	/* CXCVH						*/
	{	333,	1000,	0,		0.001,		0,			3		},	/* F_IMON						*/
	{	3333,	10000,	0,		0.001,		0,			3		},	/* R_IMON						*/
	{	21000,	19685,	21000,	0.01,		0,			3		},	/* External V(CCH) Unit:A 			*/
	{	21000,	23100,	21000,	0.01,		0,			3		}	/* External R(CCH) Unit:A 			*/
};

const default_str P3111_CALI_LP[]={
	{	21000,	7000,	10500,	0.00001,	0,			6		},	/* CCL Unit:A 					*/
	{	12000,	16500,	15000,	0.01,		0,			2		},	/* CRL Unit:1/R -- use G (1/R) value	*/
	{	15000,	16500,	15000,	0.0001,		0,			4		},	/* CVL  							*/
	{	10000,	10000,	10000,	0.001,		0,			4		},	/* CPL							*/
	{	15000,	16500,	15000,	0.0001,		0,			4		},	/* CXCVL 						*/
	{	333,	1000,	0,		0.001,		0,			3		},	/* F_IMON						*/
	{	3333,	10000,	0,		0.001,		0,			3		},	/* R_IMON						*/
	{	21000,	8338,	21000,	0.00001,	0,			6		},	/* External V(CCL) Unit:A 			*/
	{	21000,	23100,	21000,	0.00001,	0,			6		},	/* External R(CCL) Unit:A 			*/
	
	{	21000,	7000,	10500,	0.0001,		0,			5		},	/* CCM Unit:A 					*/
	{	12000,	16500,	15000,	0.01,		0,			2		},	/* CRM Unit:1/R -- use G (1/R) value*/
	{	15000,	16500,	15000,	0.001,		0,			3		},	/* CVM Unit:V 					*/
	{	10000,	10000,	10000,	0.001,		0,			4		},	/* CPM					 		*/	
	{	15000,	16500,	15000,	0.001,		0,			3		},	/* CXCVM				 		*/	
	{	33,		100,	0,		0.001,		0,			3		},	/* F_IMON						*/
	{	333,	1000,	0,		0.001,		0,			3		},	/* R_IMON						*/
	{	21000,	8338,	21000,	0.0001,		0,			5		},	/* External V(CCM) Unit:A 			*/
	{	21000,	23100,	21000,	0.0001,		0,			5		},	/* External R(CCM) Unit:A 			*/
	
	{	21000,	7000,	10500,	0.001,		0,			4		},	/* CCH Unit:A 					*/
	{	12000,	16500,	15000,	0.01,		0,			2		},	/* CRH Unit:1/R -- use G (1/R) value	*/
	{	15000,	16500,	15000,	0.001,		0,			3		},	/* CVH Unit:V 					*/
	{	10000,	10000,	10000,	0.001,		0,			4		},	/* CPH							*/
	{	15000,	16500,	15000,	0.001,		0,			3		},	/* CXCVH						*/
	{	333,	1000,	0,		0.001,		0,			3		},	/* F_IMON						*/
	{	3333,	10000,	0,		0.001,		0,			3		},	/* R_IMON						*/
	{	21000,	8338,	21000,	0.001,		0,			4		},	/* External V(CCH) Unit:A 			*/
	{	21000,	23100,	21000,	0.001,		0,			4		}	/* External R(CCH) Unit:A 			*/
};
const default_str P3111_CALI_PowSet_V[]={
	{	5,		5,		5,		1,			0,			0		},	/*	CCL							*/
	{	17,		17,		12,		0.1,		0,			0		},	/*	CRL							*/
	{	165,	165,	165,	0.1,		0,			0		},	/*	CVL							*/
	{	10,		10,		10,		1,			0,			0		},	/*	CPL							*/
	{	165,	165,	165,	0.1,		0,			0		},	/*	CXCVL						*/
	{	5,		5,		5,		1,			0,			0		},	/*	F_IMON_L					*/
	{	5,		5,		5,		1,			0,			0		},	/*	R_IMON_L					*/
	{	5,		5,		5,		1,			0,			0		},	/*	External V(CCL)				*/
	{	5,		5,		5,		1,			0,			0		},	/*	External R(CCL)				*/

	{	5,		5,		5,		1,			0,			0		},	/*	CCM							*/
	{	17,		17,		12,		0.1,		0,			0		},	/*	CRM							*/
	{	165,	165,	165,	1,			0,			0		},	/*	CVM							*/
	{	10,		10,		10,		1,			0,			0		},	/*	CPM							*/
	{	165,	165,	165,	1,			0,			0		},	/*	CXCVM						*/
	{	5,		5,		5,		1,			0,			0		},	/*	F_IMON_M					*/
	{	5,		5,		5,		1,			0,			0		},	/*	R_IMON_M					*/
	{	5,		5,		5,		1,			0,			0		},	/*	External V(CCM)				*/
	{	5,		5,		5,		1,			0,			0		},	/*	External R(CCM)				*/

	{	5,		5,		5,		1,			0,			0		},	/*	CCH							*/
	{	17,		17,		12,		0.1,		0,			0		},	/*	CRH							*/
	{	165,	165,	165,	1,			0,			0		},	/*	CVH							*/
	{	10,		10,		10,		1,			0,			0		},	/*	CPH							*/
	{	165,	165,	165,	1,			0,			0		},	/*	CXCVH						*/
	{	5,		5,		5,		1,			0,			0		},	/*	F_IMON_H					*/
	{	5,		5,		5,		1,			0,			0		},	/*	R_IMON_H					*/
	{	5,		5,		5,		1,			0,			0		},	/*	External V(CCH)				*/
	{	5,		5,		5,		1,			0,			0		}	/*	External R(CCH)				*/
};

const default_str P3111_CALI_PowSet_C[]={
	{	231,	231,	231,	0.01,		0,			0		},	/*	CCL							*/
	{	231,	231,	100,	0.01,			0,			0		},	/*	CRL							*/
	{	1,		1,		1,		1,			0,			0		},	/*	CVL							*/
	{	1155,	1155,	1155,	0.001,		0,			0		},	/*	CPL							*/
	{	1,		1,		1,		1,			0,			0		},	/*	CXCVL						*/
	{	231,	231,	231,	0.01,		0,			0		},	/*	F_IMON_L					*/
	{	231,	231,	231,	0.01,		0,			0		},	/*	R_IMON_L					*/
	{	231,	231,	231,	0.01,		0,			0		},	/*	External V(CCL)				*/
	{	231,	231,	231,	0.01,		0,			0		},	/*	External R(CCL)				*/

	{	231,	231,	231,	0.1,		0,			0		},	/*	CCM							*/
	{	231,	231,	100,	0.1,			0,			0		},	/*	CRM							*/
	{	1, 		1,	 	1,	 	1,			0,			0		},	/*	CVM							*/
	{	1155,	1155,	1155,	0.01,		0,			0		},	/*	CPM							*/
	{	1,		1,		1,		1,			0,			0		},	/*	CXCVM						*/
	{	231,	231,	231,	0.1,		0,			0		},	/*	F_IMON_M					*/
	{	231,	231,	231,	0.1,		0,			0		},	/*	R_IMON_M					*/
	{	231,	231,	231,	0.1,		0,			0		},	/*	External V(CCM)				*/
	{	231,	231,	231,	0.1,		0,			0		},	/*	External R(CCM)				*/
	
	{	231,	231,	231,	1,			0,			0		},	/*	CCH							*/
	{	231,	231,	100,	1,			0,			0		},	/*	CRH							*/
	{	1, 		1,	 	1,	 	1,			0,			0		},	/*	CVH							*/
	{	1155,	1155,	1155,	0.1,		0,			0		},	/*	CPH							*/
	{	1,		1,		1,		1,			0,			0		},	/*	CXCVH						*/
	{	231,	231,	231,	1,			0,			0		},	/*	F_IMON_H					*/
	{	231,	231,	231,	1,			0,			0		},	/*	R_IMON_H					*/
	{	231,	231,	231,	1,			0,			0		},	/*	External V(CCH)				*/
	{	231,	231,	231,	1,			0,			0		}	/*	External R(CCH)				*/
};



const Parallel_Default_str P3111_IRange_Display[]={
	/* Current     Resistance     Power */
	{	2.1,	1.400016,	10.5	},	/*	Low	X Parallel 1	*/
	{	21,		14.00016,	105		},	/*	Mid	X Parallel 1	*/
	{	210,	140.0016,	1050	},	/*	High	X Parallel 1	*/

	{	4.2,	2.800032,	21		},	/*	Low	X Parallel 2	*/
	{	42,		28.00032,	210		},	/*	Mid	X Parallel 2	*/
	{	420,	280.0032,	2100	},	/*	High	X Parallel 2	*/

	{	6.3,	4.200048,	31.5	},	/*	Low	X Parallel 3	*/
	{	63,		42.00048,	315		},	/*	Mid	X Parallel 3	*/
	{	630,	420.0048,	3150	},	/*	High	X Parallel 3	*/

	{	8.4,	5.200064,	42		},	/*	Low	X Parallel 4	*/
	{	84,		52.00064,	420		},	/*	Mid	X Parallel 4	*/
	{	840,	520.0064,	4200	},	/*	High	X Parallel 4	*/

	{	10.5,	7.00008,	52.5	},	/*	Low	X Parallel 5	*/
	{	105,	70.0008,	525		},	/*	Mid	X Parallel 5	*/
	{	1050,	700.008,	5250	},	/*	High	X Parallel 5	*/	

	{	2.1,	1.400016,	10.5	},
//	{	6.3,	4.200048,	31.5	},	/*	Low	X Booster 1 	*/ //
	{	63,		42.00048,	315 	},	/*	Mid  X Booster 1 	*/
	{	630,	420.0048,	3150	},	/*	High	X Booster 1 	*/

	{	2.1,	1.400016,	10.5	},
	//{	10.5,	7.00008,	52.5	},	/*	Low	X Booster 2 	*/ 
	{	105,	70.0008,	525 	},	/*	Mid 	X Booster 2 	*/
	{	1050,	700.008,	5250	},	/*	High	X Booster 2 	*/

	{	2.1,	1.400016,	10.5	},
//	{	14.5,	9.800064,	73.5	},	/*	Low 	X Booster 3 	*/
	{	147, 	98.00112,	735 	},	/*	Mid 	X Booster 3 	*/
	{	1470,	980.0112,	7350	},	/*	High	X Booster 3	*/

	{	2.1,	1.400016,	10.5	},
//	{	18.9,	12.60008,	94.5	},	/*	Low 	X Booster 4 	*/ 
	{	189,	126.0008,	945 	},	/*	Mid 	X Booster 4	*/
	{	1890,	1260.008,	9450	}	/*	High	X Booster 4 	*/	
};


#if 1
const Parallel_Compensation_DA_str P3111_Compasation_DA_Magnification[]={
	{	1	},	/*	 Parallel 2	*/
	{	1	},	/*	 Parallel 3	*/
	{	1	},	/*	 Parallel 4	*/
	{	1	},	/*	 Parallel 5	*/	

	{	1.012269939	},	/*	 Booster 1	*/
	{	1.014760148	},	/*	 Booster 2	*/
	{	1.015831135	},	/*	 Booster 3	*/
	{	1.016427105	}	/*	 Booster 4	*/	
};

#else
const Parallel_Compensation_DA_str P3111_Compasation_DA_Magnification[]={
	{	1.009174312	},	/*	 Parallel 2	*/
	{	1.012269939	},	/*	 Parallel 3	*/
	{	1.013824885	},	/*	 Parallel 4	*/
	{	1.014760148	},	/*	 Parallel 5	*/	

	{	1.012269939	},	/*	 Booster 1	*/
	{	1.014760148	},	/*	 Booster 2	*/
	{	1.015831135	},	/*	 Booster 3	*/
	{	1.016427105	}	/*	 Booster 4	*/	
};
#endif

const type_default P3111E = {	(default_str*)P3111_CC, 
								(default_str*)P3111_CR, 
								(default_str*)P3111_CV, 
								(default_str*)P3111_CP,
								(default_str*)P3111_CC_SPEC, 
								(default_str*)P3111_CR_SPEC,
								(default_str*)P3111_CV_SPEC, 
								(default_str*)P3111_CP_SPEC, 
								(default_str*)P3111_CONF,
								(default_str*)P3111_PROT,
								(default_str*)P3111_CALI_HP,
								(default_str*)P3111_CALI_LP,
								(default_str*)P3111_CALI_PowSet_V,
								(default_str*)P3111_CALI_PowSet_C,
								(Parallel_Default_str*)P3111_IRange_Display,
								(Parallel_Compensation_DA_str*)P3111_Compasation_DA_Magnification
							};
