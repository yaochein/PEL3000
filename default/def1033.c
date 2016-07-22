#include "../includes.h" 
#include "../menu/head.h"

const default_str P1033_CC[]={
/*		Def		Max		Min		Resolution	Unit		precision*/
	//------------------------------------------------------------------------------------------------
	{	0,		30600,	0,		0.00005,		0,			5		},	/* CC (Static Low) A/B Value			*/
	{	0,		30600,	0,		0.00005,		0,			5		},	/* CC (Static Low) Measure			*/
	{	250,	250,	1,		0.25, 		0,			2		},	/* CC (Static Low) SlewRate Up		*/
	{	250,	250,	1,		0.25, 		0,			2		},	/* CC (Static Low) SlewRate Dn		*/
	{	0,		30600,	0,		0.00005,		0,			5		},	/* CC (Dyna Low) Label 1 			*/
	{	0,		30600,	0,		0.00005,		0,			5		},	/* CC (Dyna Low) Label 2 			*/
	{	250,	250,	1,		0.25, 		0,			2		},	/* CC (Dyna Low) SlewRate Up 		*/
	{	250,	250,	1,		0.25, 		0,			2		},	/* CC (Dyna Low) SlewRate Dn 		*/
	{	1,		DyMax,	50, 	0.001,		0,			3		},	/* CC (Dyna Low) Time 1			*/
	{	1,		DyMax,	50, 	0.001,		0,			3		},	/* CC (Dyna Low) Time 2			*/
	//------------------------------------------------------------------------------------------------
	{	0,		30600,	0,		0.0005,		0,			4	 	},	/* CC (Static Hi) A/B Value			*/
	{	0,		30600,	0,		0.0005,		0,			4	 	},	/* CC (Static Hi) Measure			*/
	{	250,	250,	1,		2.5,			0,			1	 	},	/* CC (Static Hi) SlewRate Up 		*/
	{	250,	250,	1,		2.5,			0,			1	 	},	/* CC (Static Hi) SlewRate Dn 		*/
	{	0,		30600,	0,		0.0005,		0,			4	 	},	/* CC (Dyna Hi) Label 1				*/
	{	0,		30600,	0,		0.0005,		0,			4	 	},	/* CC (Dyna Hi) Label 2 			*/
	{	250,	250,	1,		2.5,			0,			1	 	},	/* CC (Dyna Hi) SlewRate Up 		*/
	{	250,	250,	1,		2.5,			0,			1	 	},	/* CC (Dyna Hi) SlewRate Dn 		*/
	{	1,		DyMax,	50,		1,			0,			3	 	},	/* CC (Dyna Hi) Time 1 			*/
	{	1,		DyMax,	50,		1,			0,			3	 	}	/* CC (Dyna Hi) Time 2 			*/
};

/* CR mode resolurtion = Max value of Ohm */
const default_str P1033_CR[]={
	//------------------------------------------------------------------------------------------------
	{	0,		30000,	0,		0.02,		0,			2		},	/* CR (Static Low) A Value			*/
	{	0,		30000,	0,		0.02,		0,			2		},	/* CR (Static Low) B Value			*/
	{	250,	250,	1,		0.25,	 	0,			2		},	/* CR (Static Low) SlewRate Up		*/
	{	250,	250,	1,		0.25,		0,			2		},	/* CR (Static Low) SlewRate Dn		*/
	{	0,		30000,	0,		0.02,		0,			2		},	/* CR (Dyna Low) A Value 			*/
	{	0,		30000,	0,		0.02,		0,			2		},	/* CR (Dyna Low) B Value 			*/
	{	250,	250,	1,		0.25, 		0,			2		},	/* CR (Dyna Low) SlewRate Up 		*/
	{	250,	250,	1,		0.25, 		0,			2		},	/* CR (Dyna Low) SlewRate Dn 		*/
	{	1,		DyMax,	50, 	0.001,		0,			3		},	/* CR (Dyna Low) Time 1			*/
	{	1,		DyMax,	50, 	0.001,		0,			3		},	/* CR (Dyna Low) Time 2			*/			
	//------------------------------------------------------------------------------------------------
	{	0,		30000,	0,		0.2,			0,			1		},	/* CR (Static Hi) A Value 			*/
	{	0,		30000,	0,		0.2,			0,			1		},	/* CR (Static Hi) B Value 			*/
	{	250,	250,	1,		2.5,			0,			1		},	/* CR (Static Hi) SlewRate Up		*/
	{	250,	250,	1,		2.5,			0,			1		},	/* CR (Static Hi) SlewRate Dn		*/
	{	0,		30000,	0,		0.2,			0,			1		},	/* CR (Dyna Hi) A Value 			*/
	{	0,		30000,	0,		0.2,			0,			1		},	/* CR (Dyna Hi) B Value 			*/
	{	250,	250,	1,		2.5,			0,			1		},	/* CR (Dyna Hi) SlewRate Up		*/
	{	250,	250,	1,		2.5,			0,			1		},	/* CR (Dyna Hi) SlewRate Dn		*/
	{	1,		DyMax,	50,		1,			0,			3	 	},	/* CR (Dyna Hi) Time 1 			*/
	{	1,		DyMax,	50,		1,			0,			3	 	}	/* CR (Dyna Hi) Time 2 			*/		
};

const default_str P1033_CV[]={
	{	50000,	51000,	0,		0.001,		0,			3		},	/* CV (Volt Range Low) A Value		*/
	{	50000,	51000,	0,		0.001,		0,			3		},	/* CV (Volt Range Low) B Value		*/
	{	30000,	30600,	0,		0.00005,		0,			5		},	/* CV (Range Low) Current Limit		*/ 
	{	50000,	51000,	0,		0.01,		0,			2		},	/* CV (Volt Range Hi) A Value		*/
	{	50000,	51000,	0,		0.01,		0,			2		},	/* CV (Volt Range Hi) B Value		*/
	{	30000,	30600,	0,		0.0005,		0,			4		},	/* CV (Range Mid) Current Limit		*/ 	
	///{	3000,	15750,	0,		0.01,		0,			2		},	/* Not Use						*/
	///{	3000,	15750,	0,		0.01,		0,			2		},	/* Not Use						*/
	///{	30000,	30600,	0,		0.02,		0,			3		}	/* CV (Range Hi) Current Limit		*/ 
};

const default_str P1033_CP[]={
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

const default_str P1033_CC_SPEC[]={
	{	25500,	51000,	0,		0.01,		0,			2		},	/* CC Spec Center Value			*/
	{	51000,	51000,	0,		0.01,		0,			2		},	/* CC Spec High Value				*/
	{	0,		0,		0,		0.01,		0,			2		}	/* CC Spec Low Value				*/
};

const default_str P1033_CR_SPEC[]={
	{	25500,	51000,	0,		0.01,		0,			2		},	/* CR Spec Center Value			*/
	{	51000,	51000,	0,		0.01,		0,			2		},	/* CR Spec High Value				*/
	{	0,		0,		0,		0.01,		0,			2		}	/* CR Spec Low Value				*/
};

const default_str P1033_CV_SPEC[]={
	{	7500,	15000,	0,		0.001,		0,			3		},	/* CV Spec Center Value		*/
	{	15000,	15000,	0,		0.001,		0,			3		},	/* CV Spec High Value			*/
	{	0,		0,		0,		0.001,		0,			3		}	/* CV Spec Low Value			*/
};

const default_str P1033_CP_SPEC[]={
	{	25500,	51000,	0,		0.01,		0,			2		},	/* CP Spec Center Value			*/
	{	51000,	51000,	0,		0.01,		0,			2		},	/* CP Spec High Value				*/
	{	0,		0,		0,		0.01,		0,			2		}	/* CP Spec Low Value				*/
};

const default_str P1033_CONF[]={
	{	0,		51000,	0,		0.001,		0,			3		},	/* Von Voltage (Low) 				*/
	{	0,		51000,	0,		0.01,		0,			2		},	/* Von Voltage (Hi)				*/
	{	0,		200,	0,		1,			0,			0		},	/* Soft Start Time(ms)				*/
	{	0,		500,	0,		1,			0,			0		}	/* Cut Off Time(S)					*/
};

const default_str P1033_PROT[]={

	{	3150,	3300,	150,	0.0005,		0,			4		},	/* 		OCP (Low)				*/
	{	31500,	31500,	150,	0.0005,		0,			4		},	/* 		OCP	(High)				*/
	{	31500,	31500,	300,	0.01, 		0,			2		},	/*		OPP (Low)				*/
	{	31500,	31500,	300,	0.01,		0,			2		},	/*		OPP (High)				*/
	{	0,		51000,	0,		0.001,		0,			3		},	/*		UVP(Low)					*/
	{	0,		51000,	0,		0.01,		0,			2		},	/* 		UVP(Hi)					*/	
	{	52500,	52500,	0,		0.001,		0,			3		},	/*		OVP(Low)				*/
	{	52500,	52500,	0,		0.01,		0,			2		}	/* 		OVP(Hi)					*/	
};


/*		Def		Max		Min		Resolution	Unit		precision*/
const default_str P1033_CALI_HP[]={
	{	27000,	10000,	18000,	0.00005,		0,			5		},	//CC //I_MON	//CP (A)
	{	50000,	0,		0,		0.001,		0,			3		},	//CR (V)
	{	45000,	0,		0,		0.001,		0,			3		},	//CV (V)
	{	30000,	0,		0,		0.001,		0,			4		},	//CP (V)
	{	45000,	0,		0,		0.001,		0,			3		},	//CXCV (V)
	{	333,	0,		0,		0.01,		0,			3		},	// ----//CPP,OPP_Resolution
	{	333,	0,		0,		0.001,		0,			3		},	//IMON (V)
	{	13500,	13500,	15000,	0.0001,		0,			4		},	//ExtV(A)	//IMON(A) // ExtV full Curr (A)	
	{	13500,	0,		15000,	0.0001,		0,			4		},	//ExtR(A) //             // ExtV full Curr (A)
	//------------------------------------------------------------------------------------------------
	{	27000,	10000,	18000,	0.0005,		0,			4		},	//CC //I_MON	//CP (A)
	{	50000,	0,		0,		0.0001,		0,			4		},	//CR (V)
	{	45000,	0,		0,		0.01,		0,			2		},	//CV (V)
	{	30000,	0,		0,		0.001,		0,			4		},	//CP (V)
	{	45000,	0,		0,		0.01,		0,			2		},	//CXCV (V)
	{	33,		0,		0,		0.002,		0,			3		},	//---
	{	3333,	0,		0,		0.001,		0,			3		},	//IMON (V)
	{	13500,	13500,	15000,	0.001,		0,			3		},	//ExtV(A)	//IMON(A) // ExtV full Curr (A)	
	{	13500,	0,		15000,	0.001,		0,			3		},	//ExtR(A) //             // ExtV full Curr (A)
};

const default_str P1033_CALI_LP[]={
	{	13500,	50000,	9000,	0.00001,		0,			5		},	//CC //I_MON	//CP (A)
	{	45000,	0,		0,		0.01,		0,			2		},	//CR (V)
	{	4500,	0,		0,		0.001,		0,			3		},	//CV (V)
	{	30000,	0,		0,		0.001,		0,			4		},	//CP (V)
	{	45000,	0,		0,		0.0001,		0,			4		},	//CXCV (V)
	{	333,	0,		0,		0.001,		0,			3		},	//---
	{	333,	0,		0,		0.001,		0,			3		},	//IMON (V)
	{	13500,	15000,	15000,	0.00001,		0,			5		},	//ExtV(A)	//IMON(A) // ExtV full Curr (A)	
	{	13500,	0,		15000,	0.00001,		0,			5		},	//ExtR(A) //             // ExtV full Curr (A)
	//------------------------------------------------------------------------------------------------
	{	13500,	50000,	9000,	0.0001,		0,			4		},	//CC //I_MON	//CP (A)
	{	45000,	0,		0,		0.001,		0,			3		},	//CR (V)
	{	4500,	0,		0,		0.01,		0,			2		},	//CV (V)
	{	30000,	0,		0,		0.001,		0,			4		},	//CP (V)
	{	45000,	0,		0,		0.001,		0,			3		},	//CXCV (V)
	{	33,		0,		0,		0.001,		0,			3		},	//---				
	{	3333,	0,		0,		0.001,		0,			3		},	//IMON (V)			
	{	13500,	15000,	15000,	0.0001,		0,			4		},	//ExtV(A)	//IMON(A) // ExtV full Curr (A)	
	{	13500,	0,		15000,	0.0001,		0,			4		},	//ExtR(A) //             // ExtV full Curr (A)
				
};

const default_str P1033_CALI_PowSet_V[]={
	{	0,		20,		2,		1,			0,			0		},//5V	
	{	450,	50,		0,		1,			0,			0		},//15V/135V		H/L	
	{	0,		510,	0,		0.1,			0,			1		},//15.3V	
	{	0,		30,		0,		1,			0,			0		},//10V	
	{	0,		510,	0,		0.1,			0,			1		},//15.3V	
	{	0,		20,		0,		1,			0,			0		},//NONE	
	{	0,		20,		0,		1,			0,			0		},//5V	
	{	0,		20,		0,		1,			0,			0		},//5V	
	{	0,		20,		0,		1,			0,			0		},//5V	
	//------------------------------------------------------------------------------------------------
	{	0,		20,		0,		1,			0,			0		},//5V			/*	CCH							*/
	{	450,	50,		0,		0.1,			0,			1		},//1.5V/13.5V		/*	CRH							*/
	{	0,		510,	0,		1,			0,			0		},//153V			/*	CVH							*/
	{	0,		30,		0,		1,			0,			0		},//10V			/*	CPH							*/
	{	0,		510,	0,		1,			0,			0		},//153V				/*	CXCVH						*/
	{	0,		20,		0,		1,			0,			0		},//NONE				/*	F_IMON_H					*/
	{	0,		20,		0,		1,			0,			0		},//5V				/*	R_IMON_H					*/
	{	0,		20,		0,		1,			0,			0		},//5V				/*	External V(CCH)				*/
	{	0,		20,		0,		1,			0,			0		},//5V				/*	External R(CCH) 				*/
};

const default_str P1033_CALI_PowSet_C[]={
	{	170,	170,	3,		0.01,		0,			2		},	//6.6A
	{	17,		17,		0,		0.1,			0,			1		},	//6A
	{	5,		5,		0,		0.1,			0,			1		},	//0.5A
	{	120,	120,	0,		0.01,		0,			2		},	//3.3A
	{	5,		5,		0,		0.1,			0,			1		},	//0.5A
	{	0,		0,		0,		0.1,			0,			1		},	//NONE
	{	170,	170,	0,		0.1,			0,			1		},	
	{	170,	170,	0,		0.1,			0,			1		},	
	{	170,	170,	0,		0.1,			0,			1		},	
	//------------------------------------------------------------------------------------------------
	{	0,		170,	5,		0.1,			0,			1		},	//66A		/*	CCL							*/
	{	0,		17,		0,		1,			0,			0		},	//60A		/*	CRL							*/
	{	0, 		5,	 	0,	 	0.1,			0,			1		},	//0.5A		/*	CVL							*/
	{	0,		120,	0,		0.1,			0,			1		},	//33A		/*	CPL							*/
	{	0,		5,		0,		0.1,			0,			1		},	//0.5A		/*	CXCVL						*/
	{	0,		0,		0,		0.1,			0,			1		},	//NONE		/*	F_IMON_L					*/
	{	0,		170,	0,		0.1,			0,			1		},			/*	R_IMON_L					*/
	{	0,		170,	0,		0.1,			0,			1		},			/*	External V(CCM)				*/
	{	0,		170,	0,		0.1,			0,			1		},			/*	External R(CCM)				*/
				
};


const Parallel_Default_str P1033_IRange_Display[]={
	/* Current     Resistance     Power */
	{	1.5,		0.6,		30		},	/*	Low	X 1	*/
	{	15,		6,		300		},	/*	Hing	X 1	*/
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

const Parallel_Compensation_DA_str P1033_Compasation_DA_Magnification[]={
	{	1	},	/*	 Parallel 2	*/
	{	1	},	/*	 Parallel 3	*/
	{	1	},	/*	 Parallel 4	*/
	{	1	},	/*	 Parallel 5	*/	
};

const type_default P1033E = {	(default_str*)P1033_CC,
								(default_str*)P1033_CR,
								(default_str*)P1033_CV,
								(default_str*)P1033_CP,
								(default_str*)P1033_CC_SPEC,
								(default_str*)P1033_CR_SPEC,
								(default_str*)P1033_CV_SPEC,
								(default_str*)P1033_CP_SPEC,
								(default_str*)P1033_CONF,
								(default_str*)P1033_PROT,
								(default_str*)P1033_CALI_HP,
								(default_str*)P1033_CALI_LP,
								(default_str*)P1033_CALI_PowSet_V,
								(default_str*)P1033_CALI_PowSet_C,
								(Parallel_Default_str*)P1033_IRange_Display,
								(Parallel_Compensation_DA_str*)P1033_Compasation_DA_Magnification
							};

