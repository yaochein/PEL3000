#include "../includes.h" 
#include "../menu/head.h"

const default_str P3070_CC[]={
/*		Def		Max		Min		Resolution	Unit		precision*/
	{ 	0,		14700,	0,		0.0001,		0,			4		},	/* CC (Static Low) A Value		 	*/
	{	0,		14700,	0,		0.0001,		0,			4		},	/* CC (Static Low) B Value			*/
	{ 	2500,	2500,	250,	0.0004,		0,			4	 	},	/* CC (Static Low) SlewRate Up 		*/
	{ 	2500,	2500,	250,	0.0004,		0,			4	 	},	/* CC (Static Low) SlewRate Dn 		*/
	{ 	0,		14700,	0,		0.0001,		0,			4	 	},	/* CC (Dyna Low) Label 1		 	*/
	{	0,		14700,	0,		0.0001,		0,			4	 	},	/* CC (Dyna Low) Label 2 			*/
	{	2500,	2500,	250,	0.0004,		0,			4	 	},	/* CC (Dyna Low) SlewRate Up 		*/
	{	2500,	2500,	250,	0.0004,		0,			4	 	},	/* CC (Dyna Low) SlewRate Dn	 	*/
	{	25,		10000,	25,		0.001,		0,			3	 	},	/* CC (Dyna Low) Time 1 			*/
	{	25,		10000,	25,		0.001,		0,			3	 	},	/* CC (Dyna Low) Time 2 			*/		
	{	0,		14700,	0,		0.001,		0,			3		},	/* CC (Static Mid) A Value			*/
	{	0,		14700,	0,		0.001,		0,			3		},	/* CC (Static Mid) B Value			*/
	{	2500,	2500,	250,	0.004, 		0,			3		},	/* CC (Static Mid) SlewRate Up		*/
	{	2500,	2500,	250,	0.004, 		0,			3		},	/* CC (Static Mid) SlewRate Dn		*/
	{	0,		14700,	0,		0.001,		0,			4		},	/* CC (Dyna Mid) Label 1 			*/
	{	0,		14700,	0,		0.001,		0,			4		},	/* CC (Dyna Mid) Label 2 			*/
	{	2500,	2500,	250,	0.004, 		0,			3		},	/* CC (Dyna Mid) SlewRate Up 		*/
	{	2500,	2500,	250,	0.004, 		0,			3		},	/* CC (Dyna Mid) SlewRate Dn 		*/
	{	1,		30000,	10, 	1,			0,			3		},	/* CC (Dyna Mid) Time 1			*/
	{	1,		30000,	10, 	1,			0,			3		},	/* CC (Dyna Mid) Time 2			*/
	{	0,		14700,	0,		0.01,		0,			2	 	},	/* CC (Static Hi) A Value			*/
	{	0,		14700,	0,		0.01,		0,			2	 	},	/* CC (Static Hi) B Value			*/
	{	2500,	2500,	250,	0.04,		0,			2	 	},	/* CC (Static Hi) SlewRate Up 		*/
	{	2500,	2500,	250,	0.04,		0,			2	 	},	/* CC (Static Hi) SlewRate Dn 		*/
	{	0,		14700,	0,		0.01,		0,			2	 	},	/* CC (Dyna Hi) Label 1				*/
	{	0,		14700,	0,		0.01,		0,			2	 	},	/* CC (Dyna Hi) Label 2 			*/
	{	2500,	2500,	250,	0.04,		0,			2	 	},	/* CC (Dyna Hi) SlewRate Up 		*/
	{	2500,	2500,	250,	0.04,		0,			2	 	},	/* CC (Dyna Hi) SlewRate Dn 		*/
	{	1,		30000,	10,		1,			0,			3	 	},	/* CC (Dyna Hi) Time 1 			*/
	{	1,		30000,	10,		1,			0,			3	 	}	/* CC (Dyna Hi) Time 2 			*/
};

/* CR mode resolurtion = Max value of Ohm */
const default_str P3070_CR[]={
	{	0,		61250,	0,		0.016,		0,			3		},	/* CR (Static Low) A Value 			*/
	{	0,		61250,	0,		0.016,		0,			3		},	/* CR (Static Low) B Value 			*/
	{	2500,	2500,	250,	0.00004,	0,			5		},	/* CR (Static Low) SlewRate Up		*/
	{	2500,	2500,	250,	0.00004,	0,			5		},	/* CR (Static Low) SlewRate Dn		*/
	{	0,		61250,	0,		0.016,		0,			3		},	/* CR (Dyna Low) A Value			*/
	{	0,		61250,	0,		0.016,		0,			3		},	/* CR (Dyna Low) B Value			*/
	{	2500,	2500,	250,	0.00004,	0,			4		},	/* CR (Dyna Low) SlewRate Up		*/
	{	2500,	2500,	250,	0.00004,	0,			4		},	/* CR (Dyna Low) SlewRate Dn		*/
	{	25, 	10000,	25, 	0.001,		0,			3		},	/* CR (Dyna Low) Time 1 			*/
	{	25, 	10000,	25, 	0.001,		0,			3		},	/* CR (Dyna Low) Time 2 			*/		
	{	0,		61250,	0,		0.16,		0,			2		},	/* CR (Static Mid) A Value			*/
	{	0,		61250,	0,		0.16,		0,			2		},	/* CR (Static Mid) B Value			*/
	{	2500,	2500,	250,	0.0004, 	0,			4		},	/* CR (Static Mid) SlewRate Up		*/
	{	2500,	2500,	250,	0.0004,		0,			4		},	/* CR (Static Mid) SlewRate Dn		*/
	{	0,		61250,	0,		0.16,		0,			2		},	/* CR (Dyna Mid) A Value 			*/
	{	0,		61250,	0,		0.16,		0,			2		},	/* CR (Dyna Mid) B Value 			*/
	{	2500,	2500,	250,	0.0004, 	0,			4		},	/* CR (Dyna Mid) SlewRate Up 		*/
	{	2500,	2500,	250,	0.0004, 	0,			4		},	/* CR (Dyna Mid) SlewRate Dn 		*/
	{	1,		30000,	10, 	1,			0,			3		},	/* CR (Dyna Mid) Time 1			*/
	{	1,		30000,	10, 	1,			0,			3		},	/* CR (Dyna Mid) Time 2			*/			
	{	0,		61250,	0,		1.6,		0,			1		},	/* CR (Static Hi) A Value 			*/
	{	0,		61250,	0,		1.6,		0,			1		},	/* CR (Static Hi) B Value 			*/
	{	2500,	2500,	250,	0.004,		0,			3		},	/* CR (Static Hi) SlewRate Up		*/
	{	2500,	2500,	250,	0.004,		0,			3		},	/* CR (Static Hi) SlewRate Dn		*/
	{	0,		61250,	0,		1.6,		0,			1		},	/* CR (Dyna Hi) A Value 			*/
	{	0,		61250,	0,		1.6,		0,			1		},	/* CR (Dyna Hi) B Value 			*/
	{	2500,	2500,	250,	0.004,		0,			3		},	/* CR (Dyna Hi) SlewRate Up		*/
	{	2500,	2500,	250,	0.004,		0,			3		},	/* CR (Dyna Hi) SlewRate Dn		*/
	{	1,		30000,	10,		1,			0,			3	 	},	/* CR (Dyna Hi) Time 1 			*/
	{	1,		30000,	10,		1,			0,			3	 	}	/* CR (Dyna Hi) Time 2 			*/		
};

const default_str P3070_CV[]={
	{	15000,	15750,	0,		0.001,		0,			3		},	/* CV (Volt Range Low) A Value		*/
	{	15000,	15750,	0,		0.001,		0,			3		},	/* CV (Volt Range Low) B Value		*/
	{	14000,	14700,	0,		0.0001,		0,			5		},	/* CV (Range Low) Current Limit		*/
	{	15000,	15750,	0,		0.01,		0,			2		},	/* CV (Volt Range Hi) A Value		*/
	{	15000,	15750,	0,		0.01,		0,			2		},	/* CV (Volt Range Hi) B Value		*/
	{	14000,	14700,	0,		0.001,		0,			4		},	/* CV (Range Mid) Current Limit		*/	
	{	15000,	15750,	0,		0.01,		0,			2		},	/* Not Use						*/
	{	15000,	15750,	0,		0.01,		0,			2		},	/* Not Use						*/
	{	14000,	14700,	0,		0.01,		0,			3		}	/* CV (Range Hi) Current Limit		*/
};

const default_str P3070_CP[]={
	{ 	0,		36750,	0,		0.0002,		0,			4		},	/* CP (Static Low) A Value		 	*/
	{	0,		36750,	0,		0.0002,		0,			4		},	/* CP (Static Low) B Value			*/
	{ 	2500,	2500,	250,	0.00004,	0,			5	 	},	/* CP (Static Low) SlewRate Up		*/
	{ 	2500,	2500,	250,	0.00004,	0,			5	 	},	/* CP (Static Low) SlewRate Dn		*/
	{ 	0,		36750,	0,		0.0002,		0,			4	 	},	/* CP (Dyna Low) Label 1		 	*/
	{	0,		36750,	0,		0.0002,		0,			4	 	},	/* CP (Dyna Low) Label 2 			*/
	{	2500,	2500,	250,	0.00004,	0,			5	 	},	/* CP (Dyna Low) SlewRate Up		*/
	{	2500,	2500,	250,	0.00004,	0,			5	 	},	/* CP (Dyna Low) SlewRate Dn		*/
	{	25,		10000,	25,		0.001,		0,			3	 	},	/* CP (Dyna Low) Time 1 			*/
	{	25,		10000,	25,		0.001,		0,			3	 	},	/* CP (Dyna Low) Time 2 			*/		
	{	0,		36750,	0,		0.002,		0,			3		},	/* CP (Static Mid) A Value			*/
	{	0,		36750,	0,		0.002,		0,			3		},	/* CP (Static Mid) B Value			*/
	{	2500,	2500,	250,	0.0004,		0,			4		},	/* CP (Static Mid) SlewRate Up		*/
	{	2500,	2500,	250,	0.0004,		0,			4		},	/* CP (Static Mid) SlewRate Dn		*/
	{	0,		36750,	0,		0.002,		0,			3		},	/* CP (Dyna Mid) Label 1 			*/
	{	0,		36750,	0,		0.002,		0,			3		},	/* CP (Dyna Mid) Label 2 			*/
	{	2500,	2500,	250,	0.0004, 	0,			4		},	/* CP (Dyna Mid) SlewRate Up		*/
	{	2500,	2500,	250,	0.0004, 	0,			4		},	/* CP (Dyna Mid) SlewRate Dn		*/
	{	1,		30000,	10, 	1,			0,			3		},	/* CP (Dyna Mid) Time 1			*/
	{	1,		30000,	10, 	1,			0,			3		},	/* CP (Dyna Mid) Time 2			*/
	{	0,		36750,	0,		0.02,		0,			2	 	},	/* CP (Static Hi) A Value			*/
	{	0,		36750,	0,		0.02,		0,			2	 	},	/* CP (Static Hi) B Value			*/
	{	2500,	2500,	250,	0.004,		0,			3	 	},	/* CP (Static Hi) SlewRate Up		*/
	{	2500,	2500,	250,	0.004,		0,			3	 	},	/* CP (Static Hi) SlewRate Dn		*/
	{	0,		36750,	0,		0.02,		0,			2	 	},	/* CP (Dyna Hi) Label 1				*/
	{	0,		36750,	0,		0.02,		0,			2	 	},	/* CP (Dyna Hi) Label 2 			*/
	{	2500,	2500,	250,	0.004,		0,			3	 	},	/* CP (Dyna Hi) SlewRate Up		*/
	{	2500,	2500,	250,	0.004,		0,			3	 	},	/* CP (Dyna Hi) SlewRate Dn		*/
	{	1,		30000,	10,		1,			0,			3	 	},	/* CP (Dyna Hi) Time 1 				*/
	{	1,		30000,	10,		1,			0,			3	 	}	/* CP (Dyna Hi) Time 2 				*/
};

const default_str P3070_CC_SPEC[]={
	{	7500,	15000,	0,		0.01,		0,			2		},	/* CC Spec Center Value			*/
	{	15000,	15000,	0,		0.01,		0,			2		},	/* CC Spec High Value				*/
	{	0,		0,		0,		0.01,		0,			2		}	/* CC Spec Low Value				*/
};

const default_str P3070_CR_SPEC[]={
	{	7500,	15000,	0,		0.01,		0,			2		},	/* CR Spec Center Value			*/
	{	15000,	15000,	0,		0.01,		0,			2		},	/* CR Spec High Value				*/
	{	0,		0,		0,		0.01,		0,			2		}	/* CR Spec Low Value				*/
};

const default_str P3070_CV_SPEC[]={
	{	7000,	14000,	0,		0.01,		0,			3		},	/* CV Spec Center Value		*/
	{	14000,	14000,	0,		0.01,		0,			3		},	/* CV Spec High Value			*/
	{	0,		0,		0,		0.01,		0,			3		}	/* CV Spec Low Value			*/
};

const default_str P3070_CP_SPEC[]={
	{	7500,	15000,	0,		0.01,		0,			2		},	/* CP Spec Center Value			*/
	{	15000,	15000,	0,		0.01,		0,			2		},	/* CP Spec High Value				*/
	{	0,		0,		0,		0.01,		0,			2		}	/* CP Spec Low Value				*/
};

const default_str P3070_CONF[]={
	{	0,		15000,	0,		0.001,		0,			3		},	/* Von Voltage (Low) 				*/
	{	0,		15000,	0,		0.01,		0,			2		},	/* Von Voltage (Hi)				*/
	{	0,		200,	0,		1,			0,			0		},	/* Soft Start Time(ms)				*/
	{	0,		500,	0,		1,			0,			0		}	/* Cut Off Time(S)					*/
};

const default_str P3070_PROT[]={
	{	385,	385,	30,		0.04,		0,			2		},	/* 		OCP (Low)				*/
	{	3850,	3850,	30, 	0.04,		0,			2		},	/*		OCP (Mid)				*/
	{	38500,	38500,	30,		0.04,		0,			2		},	/* 		OCP	(High)				*/
	{	19250,	19250,	10,		0.0004,		0,			4		},	/* 		OPP	(Low)				*/
	{	19250,	19250,	10, 	0.004, 		0,			3		},	/*		OPP (Mid)				*/
	{	19250,	19250,	10,		0.04,		0,			2		},	/* 		OPP	(High)				*/
	{	0,		16500,	0,		0.001,		0,			3		},	/*		UVP(Low)					*/
	{	0,		16500,	0,		0.01,		0,			2		},	/* 		UVP(Hi)					*/	
	{	16501,	16501,	0,		0.001,		0,			3		},	/*		OVP(Low)				*/
	{	16501,	16501,	0,		0.01,		0,			2		}	/* 		OVP(Hi)					*/	
};
/*		Def		Max		Min		Resolution	Unit		precision*/
const default_str P3070_CALI_HP[]={
	{	14000,	15400,	14000,	0.0001,		0,			5		},	/* CCL Unit:A 					*/
	{	15000,	16500,	15000,	0.0001,		0,			4		},	/* CRL Unit:1/R -- use G (1/R) value */
	{	15000,	16500,	15000,	0.001,		0,			3		},	/* CVL 							*/
	{	50000,	16500,	50000,	0.0001,		0,			4		},	/* CPL							*/
	{	15000,	16500,	15000,	0.001,		0,			3		},	/* CXCVL							*/
	{	333,	1000,	0,		0.001,		0,			3		},	/* F_IMON						*/
	{	3333,	10000,	0,		0.001,		0,			3		},	/* R_IMON						*/
	{	14000,	15400,	14000,	0.0001,		0,			5		},	/* External V(CCL) Unit:A			*/
	{	14000,	15400,	14000,	0.0001,		0,			5		},	/* External R(CCL) Unit:A			*/

	{	14000,	15400,	14000,	0.001,		0,			4		},	/* CCM Unit:A 					*/
	{	15000,	16500,	15000,	0.0001,		0,			4		},	/* CRM Unit:1/R -- use G (1/R) value	*/
	{	15000,	16500,	15000,	0.001,		0,			3		},	/* CVM Unit:V 					*/
	{	50000,	16500,	50000,	0.0001,		0,			4		},	/* CPM 							*/
	{	15000,	16500,	15000,	0.001,		0,			3		},	/* CXCVM						*/
	{	33,		100,	0,		0.001,		0,			3		},	/* F_IMON						*/
	{	333,	1000,	0,		0.001,		0,			3		},	/* R_IMON						*/
	{	14000,	15400,	14000,	0.001,		0,			4		},	/* External V(CCM) Unit:A 			*/
	{	14000,	15400,	14000,	0.001,		0,			4		},	/* External R(CCM) Unit:A 			*/
	
	{	14000,	15400,	14000,	0.01,		0,			3		},	/* CCH Unit:A 					*/
	{	15000,	16500,	15000,	0.0001,		0,			4		},	/* CRH Unit:1/R -- use G (1/R) value*/
	{	15000,	16500,	15000,	0.01,		0,			2		},	/* CVH Unit:V 					*/
	{	50000,	16500,	50000,	0.0001,		0,			4		},	/* CPH 							*/
	{	15000,	16500,	15000,	0.01,		0,			2		},	/* CXCVH						*/
	{	333,	1000,	0,		0.001,		0,			3		},	/* F_IMON						*/
	{	3333,	10000,	0,		0.001,		0,			3		},	/* R_IMON						*/
	{	14000,	15400,	14000,	0.01,		0,			3		},	/* External V(CCH) Unit:A 			*/
	{	14000,	15400,	14000,	0.01,		0,			3		}	/* External R(CCH) Unit:A 			*/
};

const default_str P3070_CALI_LP[]={
	{	14000,	15400,	14000,	0.00001,	0,			6		},	/* CCL Unit:A 					*/
	{	15000,	16500,	15000,	0.0001,		0,			4		},	/* CRL Unit:1/R -- use G (1/R) value	*/
	{	15000,	16500,	15000,	0.0001,		0,			4		},	/* CVL  							*/
	{	50000,	16500,	50000,	0.0001,		0,			4		},	/* CPL							*/
	{	15000,	16500,	15000,	0.0001,		0,			4		},	/* CXCVL 						*/
	{	333,	1000,	0,		0.001,		0,			3		},	/* F_IMON						*/
	{	3333,	10000,	0,		0.001,		0,			3		},	/* R_IMON						*/
	{	14000,	15400,	14000,	0.00001,	0,			6		},	/* External V(CCL) Unit:A 			*/
	{	14000,	15400,	14000,	0.00001,	0,			6		},	/* External R(CCL) Unit:A 			*/
	
	{	14000,	15400,	14000,	0.0001,		0,			5		},	/* CCM Unit:A 					*/
	{	15000,	16500,	15000,	0.0001,		0,			4		},	/* CRM Unit:1/R -- use G (1/R) value*/
	{	15000,	16500,	15000,	0.001,		0,			3		},	/* CVM Unit:V 					*/
	{	50000,	16500,	50000,	0.0001,		0,			4		},	/* CPM					 		*/	
	{	15000,	16500,	15000,	0.001,		0,			3		},	/* CXCVM				 		*/	
	{	33,		100,	0,		0.001,		0,			3		},	/* F_IMON						*/
	{	333,	1000,	0,		0.001,		0,			3		},	/* R_IMON						*/
	{	14000,	15400,	14000,	0.0001,		0,			5		},	/* External V(CCM) Unit:A 			*/
	{	14000,	15400,	14000,	0.0001,		0,			5		},	/* External R(CCM) Unit:A 			*/
	
	{	14000,	15400,	14000,	0.001,		0,			4		},	/* CCH Unit:A 					*/
	{	15000,	16500,	15000,	0.0001,		0,			4		},	/* CRH Unit:1/R -- use G (1/R) value	*/
	{	15000,	16500,	15000,	0.001,		0,			3		},	/* CVH Unit:V 					*/
	{	50000,	16500,	50000,	0.0001,		0,			4		},	/* CPH							*/
	{	15000,	16500,	15000,	0.001,		0,			3		},	/* CXCVH						*/
	{	333,	1000,	0,		0.001,		0,			3		},	/* F_IMON						*/
	{	3333,	10000,	0,		0.001,		0,			3		},	/* R_IMON						*/
	{	14000,	15400,	14000,	0.001,		0,			4		},	/* External V(CCH) Unit:A 			*/
	{	14000,	15400,	14000,	0.001,		0,			4		}	/* External R(CCH) Unit:A 			*/
};

const default_str P3070_CALI_PowSet_V[]={
	{	5,		5,		5,		1,			0,			0		},	/*	CCL							*/
	{	15,		15,		15,		0.1,		0,			0		},	/*	CRL							*/
	{	165,	165,	165,	0.1,		0,			0		},	/*	CVL							*/
	{	5,		5,		5,		1,			0,			0		},	/*	CPL							*/
	{	165,	165,	165,	0.1,		0,			0		},	/*	CXCVL						*/
	{	5,		5,		5,		1,			0,			0		},	/*	F_IMON_L					*/
	{	5,		5,		5,		1,			0,			0		},	/*	R_IMON_L					*/
	{	5,		5,		5,		1,			0,			0		},	/*	External V(CCL)				*/
	{	5,		5,		5,		1,			0,			0		},	/*	External R(CCL)				*/

	{	5,		5,		5,		1,			0,			0		},	/*	CCM							*/
	{	15,		15,		15,		0.1,		0,			0		},	/*	CRM							*/
	{	165,	165,	165,	1,			0,			0		},	/*	CVM							*/
	{	5,		5,		5,		1,			0,			0		},	/*	CPM							*/
	{	165,	165,	165,	1,			0,			0		},	/*	CXCVM						*/
	{	5,		5,		5,		1,			0,			0		},	/*	F_IMON_M					*/
	{	5,		5,		5,		1,			0,			0		},	/*	R_IMON_M					*/
	{	5,		5,		5,		1,			0,			0		},	/*	External V(CCM)				*/
	{	5,		5,		5,		1,			0,			0		},	/*	External R(CCM)				*/

	{	5,		5,		5,		1,			0,			0		},	/*	CCH							*/
	{	15,		15,		15,		0.1,		0,			0		},	/*	CRH							*/
	{	165,	165,	165,	1,			0,			0		},	/*	CVH							*/
	{	5,		5,		5,		1,			0,			0		},	/*	CPH							*/
	{	165,	165,	165,	1,			0,			0		},	/*	CXCVH						*/
	{	5,		5,		5,		1,			0,			0		},	/*	F_IMON_H					*/
	{	5,		5,		5,		1,			0,			0		},	/*	R_IMON_H					*/
	{	5,		5,		5,		1,			0,			0		},	/*	External V(CCH)				*/
	{	5,		5,		5,		1,			0,			0		}	/*	External R(CCH)				*/
};

const default_str P3070_CALI_PowSet_C[]={
	{	154,	154,	154,	0.01,		0,			0		},	/*	CCL							*/
	{	154,	154,	154,	0.01,		0,			0		},	/*	CRL							*/
	{	1,		1,		1,		1,			0,			0		},	/*	CVL							*/
	{	154,	154,	154,	0.01,		0,			0		},	/*	CPL							*/
	{	1,		1,		1,		1,			0,			0		},	/*	CXCVL						*/
	{	154,	154,	154,	0.01,		0,			0		},	/*	F_IMON_L					*/
	{	154,	154,	154,	0.01,		0,			0		},	/*	R_IMON_L					*/
	{	154,	154,	154,	0.01,		0,			0		},	/*	External V(CCL)				*/
	{	154,	154,	154,	0.01,		0,			0		},	/*	External R(CCL)				*/

	{	154,	154,	154,	0.1,		0,			0		},	/*	CCM							*/
	{	154,	154,	154,	0.1,		0,			0		},	/*	CRM							*/
	{	1, 		1,	 	1,	 	1,			0,			0		},	/*	CVM							*/
	{	154,	154,	154,	0.1,		0,			0		},	/*	CPM							*/
	{	1,		1,		1,		1,			0,			0		},	/*	CXCVM						*/
	{	154,	154,	154,	0.1,		0,			0		},	/*	F_IMON_M					*/
	{	154,	154,	154,	0.1,		0,			0		},	/*	R_IMON_M					*/
	{	154,	154,	154,	0.1,		0,			0		},	/*	External V(CCM)				*/
	{	154,	154,	154,	0.1,		0,			0		},	/*	External R(CCM)				*/
	
	{	154,	154,	154,	1,			0,			0		},	/*	CCH							*/
	{	154,	154,	154,	1,			0,			0		},	/*	CRH							*/
	{	1, 		1,	 	1,	 	1,			0,			0		},	/*	CVH							*/
	{	154,	154,	154,	1,			0,			0		},	/*	CPH							*/
	{	1,		1,		1,		1,			0,			0		},	/*	CXCVH						*/
	{	154,	154,	154,	1,			0,			0		},	/*	F_IMON_H					*/
	{	154,	154,	154,	1,			0,			0		},	/*	R_IMON_H					*/
	{	154,	154,	154,	1,			0,			0		},	/*	External V(CCH)				*/
	{	154,	154,	154,	1,			0,			0		}	/*	External R(CCH)				*/
};

const type_default P3070E = {	(default_str*)P3070_CC,
								(default_str*)P3070_CR,
								(default_str*)P3070_CV,
								(default_str*)P3070_CP,
								(default_str*)P3070_CC_SPEC,
								(default_str*)P3070_CR_SPEC,
								(default_str*)P3070_CV_SPEC,
								(default_str*)P3070_CP_SPEC,
								(default_str*)P3070_CONF,
								(default_str*)P3070_PROT,
								(default_str*)P3070_CALI_HP,
								(default_str*)P3070_CALI_LP,
								(default_str*)P3070_CALI_PowSet_V,
								(default_str*)P3070_CALI_PowSet_C
							};

