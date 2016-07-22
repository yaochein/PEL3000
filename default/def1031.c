#include "../includes.h" 
#include "../menu/head.h"

const default_str P1031_CC[]={
/*		Def		Max		Min		Resolution	Unit		precision*/
	//------------------------------------------------------------------------------------------------
	{	0,		30600,	0,		0.0002,		0,			4		},	/* CC (Static Low) A/B Value			*/
	{	0,		30600,	0,		0.0002,		0,			4		},	/* CC (Static Low) Measure			*/
	{	250,	250,	1,		1, 			0,			0		},	/* CC (Static Low) SlewRate Up		*/
	{	250,	250,	1,		1, 			0,			0		},	/* CC (Static Low) SlewRate Dn		*/
	{	0,		30600,	0,		0.0002,		0,			4		},	/* CC (Dyna Low) Label 1 			*/
	{	0,		30600,	0,		0.0002,		0,			4		},	/* CC (Dyna Low) Label 2 			*/
	{	250,	250,	1,		1, 			0,			0		},	/* CC (Dyna Low) SlewRate Up 		*/
	{	250,	250,	1,		1, 			0,			0		},	/* CC (Dyna Low) SlewRate Dn 		*/
	{	1,		DyMax,	50, 	0.001,		0,			3		},	/* CC (Dyna Low) Time 1			*/
	{	1,		DyMax,	50, 	0.001,		0,			3		},	/* CC (Dyna Low) Time 2			*/
	//------------------------------------------------------------------------------------------------
	{	0,		30600,	0,		0.002,		0,			3	 	},	/* CC (Static Hi) A/B Value			*/
	{	0,		30600,	0,		0.002,		0,			3	 	},	/* CC (Static Hi) Measure			*/
	{	250,	250,	1,		10,			0,			0	 	},	/* CC (Static Hi) SlewRate Up 		*/
	{	250,	250,	1,		10,			0,			0	 	},	/* CC (Static Hi) SlewRate Dn 		*/
	{	0,		30600,	0,		0.002,		0,			3	 	},	/* CC (Dyna Hi) Label 1				*/
	{	0,		30600,	0,		0.002,		0,			3	 	},	/* CC (Dyna Hi) Label 2 			*/
	{	250,	250,	1,		10,			0,			0	 	},	/* CC (Dyna Hi) SlewRate Up 		*/
	{	250,	250,	1,		10,			0,			0	 	},	/* CC (Dyna Hi) SlewRate Dn 		*/
	{	1,		DyMax,	50,		1,			0,			3	 	},	/* CC (Dyna Hi) Time 1 			*/
	{	1,		DyMax,	50,		1,			0,			3	 	}	/* CC (Dyna Hi) Time 2 			*/
};

/* CR mode resolurtion = Max value of Ohm */
const default_str P1031_CR[]={
	//------------------------------------------------------------------------------------------------
	{	0,		30000,	0,		0.2,			0,			1		},	/* CR (Static Low) A Value			*/
	{	0,		30000,	0,		0.2,			0,			1		},	/* CR (Static Low) B Value			*/
	{	250,	250,	1,		1,	 		0,			0		},	/* CR (Static Low) SlewRate Up		*/
	{	250,	250,	1,		1,			0,			0		},	/* CR (Static Low) SlewRate Dn		*/
	{	0,		30000,	0,		0.2,			0,			1		},	/* CR (Dyna Low) A Value 			*/
	{	0,		30000,	0,		0.2,			0,			1		},	/* CR (Dyna Low) B Value 			*/
	{	250,	250,	1,		1, 			0,			0		},	/* CR (Dyna Low) SlewRate Up 		*/
	{	250,	250,	1,		1, 			0,			0		},	/* CR (Dyna Low) SlewRate Dn 		*/
	{	1,		DyMax,	50, 	0.001,		0,			3		},	/* CR (Dyna Low) Time 1			*/
	{	1,		DyMax,	50, 	0.001,		0,			3		},	/* CR (Dyna Low) Time 2			*/			
	//------------------------------------------------------------------------------------------------
	{	0,		30000,	0,		2,			0,			0		},	/* CR (Static Hi) A Value 			*/
	{	0,		30000,	0,		2,			0,			0		},	/* CR (Static Hi) B Value 			*/
	{	250,	250,	1,		10,			0,			0		},	/* CR (Static Hi) SlewRate Up		*/
	{	250,	250,	1,		10,			0,			0		},	/* CR (Static Hi) SlewRate Dn		*/
	{	0,		30000,	0,		2,			0,			0		},	/* CR (Dyna Hi) A Value 			*/
	{	0,		30000,	0,		2,			0,			0		},	/* CR (Dyna Hi) B Value 			*/
	{	250,	250,	1,		10,			0,			0		},	/* CR (Dyna Hi) SlewRate Up		*/
	{	250,	250,	1,		10,			0,			0		},	/* CR (Dyna Hi) SlewRate Dn		*/
	{	1,		DyMax,	50,		1,			0,			3	 	},	/* CR (Dyna Hi) Time 1 			*/
	{	1,		DyMax,	50,		1,			0,			3	 	}	/* CR (Dyna Hi) Time 2 			*/		
};

const default_str P1031_CV[]={
	{	30000,	30600,	0,		0.0005,		0,			4		},	/* CV (Volt Range Low) A Value		*/
	{	30000,	30600,	0,		0.0005,		0,			4		},	/* CV (Volt Range Low) B Value		*/
	{	30000,	30600,	0,		0.0002,		0,			4		},	/* CV (Range Low) Current Limit		*/ 
	{	30000,	30600,	0,		0.005,		0,			3		},	/* CV (Volt Range Hi) A Value		*/
	{	30000,	30600,	0,		0.005,		0,			3		},	/* CV (Volt Range Hi) B Value		*/
	{	30000,	30600,	0,		0.002,		0,			3		},	/* CV (Range Mid) Current Limit		*/ 	
	{	3000,	15750,	0,		0.01,		0,			2		},	/* Not Use						*/
	{	3000,	15750,	0,		0.01,		0,			2		},	/* Not Use						*/
	{	30000,	30600,	0,		0.02,		0,			3		}	/* CV (Range Hi) Current Limit		*/ 
};

const default_str P1031_CP[]={
	//------------------------------------------------------------------------------------------------
	{	0,		30600,	0,		0.001,		0,			3		},	/* CP (Static Low) A Value			*/
	{	0,		30600,	0,		0.001,		0,			3		},	/* CP (Static Low) B Value			*/
	{	2500,	2500,	250,	0.0002,		0,			4		},	/* CP (Static Low) SlewRate Up		*/
	{	2500,	2500,	250,	0.0002,		0,			4		},	/* CP (Static Low) SlewRate Dn		*/
	{	0,		30600,	0,		0.001,		0,			3		},	/* CP (Dyna Low) Label 1 			*/
	{	0,		30600,	0,		0.001,		0,			3		},	/* CP (Dyna Low) Label 2 			*/
	{	2500,	2500,	250,	0.0002, 		0,			4		},	/* CP (Dyna Low) SlewRate Up		*/
	{	2500,	2500,	250,	0.0002, 		0,			4		},	/* CP (Dyna Low) SlewRate Dn		*/
	{	1,		DyMax,	50, 	1,			0,			3		},	/* CP (Dyna Low) Time 1			*/
	{	1,		DyMax,	50, 	1,			0,			3		},	/* CP (Dyna Low) Time 2			*/
	//------------------------------------------------------------------------------------------------
	{	0,		30600,	0,		0.01,		0,			2	 	},	/* CP (Static Hi) A Value			*/
	{	0,		30600,	0,		0.01,		0,			2	 	},	/* CP (Static Hi) B Value			*/
	{	2500,	2500,	250,	0.002,		0,			3	 	},	/* CP (Static Hi) SlewRate Up		*/
	{	2500,	2500,	250,	0.002,		0,			3	 	},	/* CP (Static Hi) SlewRate Dn		*/
	{	0,		30600,	0,		0.01,		0,			2	 	},	/* CP (Dyna Hi) Label 1				*/
	{	0,		30600,	0,		0.01,		0,			2	 	},	/* CP (Dyna Hi) Label 2 			*/
	{	2500,	2500,	250,	0.002,		0,			3	 	},	/* CP (Dyna Hi) SlewRate Up		*/
	{	2500,	2500,	250,	0.002,		0,			3	 	},	/* CP (Dyna Hi) SlewRate Dn		*/
	{	1,		DyMax,	50,		1,			0,			3	 	},	/* CP (Dyna Hi) Time 1 				*/
	{	1,		DyMax,	50,		1,			0,			3	 	}	/* CP (Dyna Hi) Time 2 				*/
};

const default_str P1031_CC_SPEC[]={
	{	7500,	15000,	0,		0.01,		0,			2		},	/* CC Spec Center Value			*/
	{	15000,	15000,	0,		0.01,		0,			2		},	/* CC Spec High Value				*/
	{	0,		0,		0,		0.01,		0,			2		}	/* CC Spec Low Value				*/
};

const default_str P1031_CR_SPEC[]={
	{	7500,	15000,	0,		0.01,		0,			2		},	/* CR Spec Center Value			*/
	{	15000,	15000,	0,		0.01,		0,			2		},	/* CR Spec High Value				*/
	{	0,		0,		0,		0.01,		0,			2		}	/* CR Spec Low Value				*/
};

const default_str P1031_CV_SPEC[]={
	{	17500,	35000,	0,		0.002,		0,			3		},	/* CV Spec Center Value			*/
	{	35000,	35000,	0,		0.002,		0,			3		},	/* CV Spec High Value				*/
	{	0,		0,		0,		0.002,		0,			3		}	/* CV Spec Low Value				*/
};

const default_str P1031_CP_SPEC[]={
	{	7500,	15000,	0,		0.01,		0,			2		},	/* CP Spec Center Value			*/
	{	15000,	15000,	0,		0.01,		0,			2		},	/* CP Spec High Value				*/
	{	0,		0,		0,		0.01,		0,			2		}	/* CP Spec Low Value				*/
};

const default_str P1031_CONF[]={
	{	0,		15000,	0,		0.001,		0,			3		},	/* Von Voltage (Low) 				*/
	{	0,		15000,	0,		0.01,		0,			2		},	/* Von Voltage (Hi)				*/
	{	0,		200,	0,		1,			0,			0		},	/* Soft Start Time(ms)				*/
	{	0,		500,	0,		1,			0,			0		}	/* Cut Off Time(S)					*/
};



#if 1
const default_str P1031_PROT[]={

	{	3150,	3300,	150,	0.002,		0,			3		},	/* 		OCP (Low)				*/
	{	31500,	31500,	150,	0.002,		0,			3		},	/* 		OCP	(High)				*/
	{	31500,	31500,	300,	0.01, 		0,			2		},	/*		OPP (Low)				*/
	{	31500,	31500,	300,	0.01,		0,			2		},	/*		OPP (High)				*/
	{	0,		30600,	0,		0.0005,		0,			4		},	/*		UVP(Low)					*/
	{	0,		30600,	0,		0.005,		0,			3		},	/* 		UVP(Hi)					*/	
	{	31500,	31500,	0,		0.0005,		0,			4		},	/*		OVP(Low)				*/
	{	31500,	31500,	0,		0.005,		0,			3		}	/* 		OVP(Hi)					*/	
};

#else
const default_str P1031_PROT[]={

	{	420,	420,	2,		0.015,		0,			3		},	/* 		OCP (Low)				*/
	///{	3850,	3850,	30, 	0.002,		0,			3		},	/*		OCP (Mid)				*/
	{	420,	420,	2,		0.15,		0,			2		},	/* 		OCP	(High)				*/
	{	210,	210,	2, 		1.5, 		0,			1		},	/*		OPP (Low)				*/
	///{	38500,	38500,	10, 	0.001,		0,			3		},	/*		OPP (Mid)				*/
	{	210,	210,	2, 		1.5,			0,			1		},	/*		OPP (High)				*/
	{	0,		30600,	0,		0.0005,		0,			4		},	/*		UVP(Low)					*/
	{	0,		30600,	0,		0.005,		0,			3		},	/* 		UVP(Hi)					*/	
	{	31500,	31500,	0,		0.0005,		0,			4		},	/*		OVP(Low)				*/
	{	31500,	31500,	0,		0.005,		0,			3		}	/* 		OVP(Hi)					*/	
};
#endif
/*		Def		Max		Min		Resolution	Unit		precision*/
const default_str P1031_CALI_HP[]={
	{	27000,	10000,	13500,	0.0002,		0,			4		},	//5.4A	//2A		//3A (cc_res)
	{	15000,	16500,	15000,	0.001,		0,			3		},	//13.5V
	{	27000,	33000,	30000,	0.0005,		0,			4		},	//13.5V (cv_res) //2015.03.10
	{	10000,	10000,	10000,	0.001,		0,			4		},	//10V
	{	27000,	33000,	30000,	0.0005,		0,			4		},	//13.5V
// {	333,	1000,	0,		1.5,			0,			3		},	// ----//CPP,OPP_Resolution
	{	333,	1000,	0,		0.01,		0,			3		},	// ----//CPP,OPP_Resolution
	{	333,	10000,	0,		0.001,		0,			3		},	//0.333V
	{	27000,	27000,	30000,	0.0002,		0,			4		},	//6A (exv) 	//5.4A //6(I_Mon_Curr)	
	{	27000,	38500,	30000,	0.0002,		0,			4		},	//6A(exr)
	//------------------------------------------------------------------------------------------------
	{	27000,	10000,	13500,	0.002,		0,			3		},	//54A	//20A	//30A		/* CCH Unit:A 					*/
	{	15000,	16500,	15000,	0.0001,		0,			4		},	//1.5V				/* CRH Unit:1/R -- use G (1/R) value	*/
	{	27000,	33000,	30000,	0.005,		0,			3		},	//135V				/* CVH Unit:V 					*/
	{	10000,	10000,	10000,	0.001,		0,			4		},	//10V				/* CPH 							*/
	{	27000,	33000,	30000,	0.005,		0,			3		},	//135V				/* CXCVH						*/
	{	33,		100,	0,		0.002,		0,			3		},	//---//OCP_Resolution				/* F_IMON						*/
	{	3333,	1000,	0,		0.001,		0,			3		},	//3.33V				/* R_IMON						*/
	{	27000,	27000,	30000,	0.002,		0,			3		},	//60A	//54A //6(I_Mon_Curr)			/* External V(CCH) Unit:A 			*/
	{	27000,	38500,	30000,	0.002,		0,			3		},	//60A					/* External R(CCH) Unit:A 			*/
};

const default_str P1031_CALI_LP[]={
	{	27000,	10000,	13500,	0.00002,		0,			5		},	//0.54A	//2A		//0.3A
	{	13500,	16500,	15000,	0.01,		0,			2		},	//135V
	{	13500,	16500,	15000,	0.0001,		0,			4		},	//1.35V
	{	10000,	10000,	10000,	0.001,		0,			4		},	//10V
	{	13500,	16500,	15000,	0.0001,		0,			4		},	//1.35V
	{	333,	1000,	0,		0.001,		0,			3		},	//---
	{	333,	10000,	0,		0.001,		0,			3		},	//0.333V
	{	27000,	30000,	30000,	0.00002,		0,			5		},	//06A	//0.6A(I_Mon_Curr)	
	{	27000,	38500,	30000,	0.00002,		0,			5		},	//0.6A
	//------------------------------------------------------------------------------------------------
	{	27000,	10000,	13500,	0.0002,		0,			4		},	//5.4A	//20A	//3A			/* CCH Unit:A 					*/
	{	13500,	16500,	15000,	0.001,		0,			3		},	//13.5V				/* CRH Unit:1/R -- use G (1/R) value*/
	{	13500,	16500,	15000,	0.001,		0,			3		},	//13.5V				/* CVH Unit:V 					*/
	{	10000,	10000,	10000,	0.001,		0,			4		},	//10V				/* CPH					 		*/	
	{	13500,	16500,	15000,	0.001,		0,			3		},	//13.5V				/* CXCVH				 		*/	
	{	33,		100,	0,		0.001,		0,			3		},	//---				/* F_IMON						*/
	{	3333,	1000,	0,		0.001,		0,			3		},	//3.33V				/* R_IMON						*/
	{	27000,	30000,	30000,	0.0002,		0,			4		},	//6A	  //		//6A(I_Mon_Curr)			/* External V(CCH) Unit:A 			*/
	{	27000,	38500,	30000,	0.0002,		0,			4		},	//6A					/* External R(CCH) Unit:A 			*/
				
};

const default_str P1031_CALI_PowSet_V[]={
	{	5,		5,		5,		1,			0,			0		},//5V	
	{	135,	15,		1,		1,			0,			0		},//15V/135V		H/L	
	{	153,	153,	153,	0.1,			0,			0		},//15.3V	
	{	10,		10,		10,		1,			0,			0		},//10V	
	{	153,	153,	153,	0.1,			0,			0		},//15.3V	
	{	5,		5,		5,		1,			0,			0		},//NONE	
	{	5,		5,		5,		1,			0,			0		},//5V	
	{	5,		5,		5,		1,			0,			0		},//5V	
	{	5,		5,		5,		1,			0,			0		},//5V	
	//------------------------------------------------------------------------------------------------
	{	5,		5,		5,		1,			0,			0		},//5V			/*	CCH							*/
	{	135,	18,		12,		0.1,			0,			0		},//1.5V/13.5V	/*	CRH							*/
	{	153,	153,	153,	1,			0,			0		},//153V			/*	CVH							*/
	{	10,		10,		10,		1,			0,			0		},//10V			/*	CPH							*/
	{	153,	153,	153,	1,			0,			0		},//153V			/*	CXCVH						*/
	{	5,		5,		5,		1,			0,			0		},//NONE			/*	F_IMON_H					*/
	{	5,		5,		5,		1,			0,			0		},//5V			/*	R_IMON_H					*/
	{	5,		5,		5,		1,			0,			0		},//5V			/*	External V(CCH)				*/
	{	5,		5,		5,		1,			0,			0		},//5V			/*	External R(CCH)				*/
};

const default_str P1031_CALI_PowSet_C[]={
	{	330,	330,	385,	0.02,		0,			0		},	//6.6A
	{	60,		60,		30,		0.1,			0,			0		},	//6A
	{	1,		1,		1,		1,			0,			0		},	//1A
	{	360,	360,	360,	0.01,		0,			0		},	//3.3A
	{	1,		1,		1,		1,			0,			0		},	//1A
	{	66,		77,		77,		0.1,			0,			0		},	//NONE
	{	66,		66,		66,		0.1,			0,			0		},	
	{	66,		66,		66,		0.1,			0,			0		},	
	{	66,		66,		66,		0.1,			0,			0		},	
	//------------------------------------------------------------------------------------------------
	{	330,	330,	385,	0.2,			0,			0		},	//66A		/*	CCL							*/
	{	60,		60,		30,		1,			0,			0		},	//60A		/*	CRL							*/
	{	1, 		1,	 	1,	 	1,			0,			0		},	//1A			/*	CVL							*/
	{	360,	360,	360,	0.1,			0,			0		},	//33A		/*	CPL							*/
	{	1,		1,		1,		1,			0,			0		},	//1A			/*	CXCVL						*/
	{	77,		77,		77,		0.1,			0,			0		},	//NONE		/*	F_IMON_L					*/
	{	660,	660,	660,	0.1,			0,			0		},				/*	R_IMON_L					*/
	{	660,	660,	660,	0.1,			0,			0		},				/*	External V(CCM)				*/
	{	660,	660,	660,	0.1,			0,			0		},				/*	External R(CCM)				*/
				
};


const Parallel_Default_str P1031_IRange_Display[]={
	/* Current     Resistance     Power */
	{	6,		6,		30		},	/*	Low	X 1	*/
	{	60,		60,		300		},	/*	Hing	X 1	*/
	{	70,		46.6672,	350		},	

	{	12,		12,		60		},	/*	Low	X 2	*/
	{	120,	120,	600		},	/*	Hing	X 2	*/
	{	140,	93.3344,	700		},	

	{	18,		18,		90		},	/*	Low	X 3	*/
	{	180,	180,	900		},	/*	Hing	X 3	*/
	{	210,	140.001,	1050	},	

	{	24,		24,		120		},	/*	Low	X 4	*/
	{	240,	240,	1200	},	/*	Hing	X 4	*/
	{	280,	186.668,	1400	},	

	{	30,		30,		150		},	/*	Low	X 5	*/
	{	300,	300,	1500	},	/*	Hing	X 5	*/
	{	350,	233.336,	1750	}		
};

const Parallel_Compensation_DA_str P1031_Compasation_DA_Magnification[]={
	{	1	},	/*	 Parallel 2	*/
	{	1	},	/*	 Parallel 3	*/
	{	1	},	/*	 Parallel 4	*/
	{	1	},	/*	 Parallel 5	*/	
};

const type_default P1031E = {	(default_str*)P1031_CC,
								(default_str*)P1031_CR,
								(default_str*)P1031_CV,
								(default_str*)P1031_CP,
								(default_str*)P1031_CC_SPEC,
								(default_str*)P1031_CR_SPEC,
								(default_str*)P1031_CV_SPEC,
								(default_str*)P1031_CP_SPEC,
								(default_str*)P1031_CONF,
								(default_str*)P1031_PROT,
								(default_str*)P1031_CALI_HP,
								(default_str*)P1031_CALI_LP,
								(default_str*)P1031_CALI_PowSet_V,
								(default_str*)P1031_CALI_PowSet_C,
								(Parallel_Default_str*)P1031_IRange_Display,
								(Parallel_Compensation_DA_str*)P1031_Compasation_DA_Magnification
							};

