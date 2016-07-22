#include "scpiStruct.h"
#if 1

//--------------------------------------------
//--- Multiple ---
//-IEEE488.1--name--abbreviation--multiple-
//	EX		  exa		E			10^18
//	PE		  peta		P			10^15
//	T		  tera		T       	10^12
//	G		  giga		G       	10^9
//	MA		  mega		M       	10^6
//	K		  kilo		k       	10^3
//	M		  milli		m       	10^-3
//	U		  micro		£g      	10^-6
//	N		  nano		n       	10^-9
//	P		  pico		p       	10^-12
//	F		  femto		f       	10^-15
//	A		  atto		a       	10^-18
//--------------------------------------------

const PARAM_UNIT U_VOLT[]={
    { "v",    0 },/* Volt      */
	{ "kv",   3 },/* KiloVolt  */
	{ "mv",  -3 },/* MilliVolt */
	{ "mav",  6 },/* MegaVolt  */
	{ "uv",  -6 },/* MicroVolt */
	{ "gv",   9 },/* GigaVolt  */
	{ "nv",  -9 },/* NanoVolt  */
	{ "tv",  12 },/* TeraVolt  */
	{ "pv", -12 },/* PicoVolt  */
	{ "pev", 15 },/* PetaVolt  */
	{ "fv", -15 },/* FemtoVolt */
	{ "exv", 18 },/* ExaVolt   */
	{ "av", -18 },/* AttoVolt  */
    {  0  ,   0 }
};

const PARAM_UNIT U_AMP[]={
    { "a",    0 },/* Amp      */
	{ "ka",   3 },/* KiloAmp  */
	{ "ma",  -3 },/* MilliAmp */
	{ "maa",  6 },/* MegaAmp  */
	{ "ua",  -6 },/* MicroAmp */
	{ "ga",   9 },/* GigaAmp  */
	{ "na",  -9 },/* NanoAmp  */
	{ "ta",  12 },/* TeraAmp  */
	{ "pa", -12 },/* PicoAmp  */
	{ "pea", 15 },/* PetaAmp  */
	{ "fa", -15 },/* FemtoAmp */
	{ "exa", 18 },/* ExaAmp   */
	{ "aa", -18 },/* AttoAmp  */
    {  0  , 0  }
};

const PARAM_UNIT U_OHM[]={
	/*(Note: no MilliOhms in SCPI - see MegaOhm) */
	{ "r",     0  },/* Ohm      */
	{ "ohm",   0  },/* Ohm      */
	{ "kr",    3  },/* KiloOhm  */
	{ "kohm",  3  },/* KiloOhm  */
	{ "mr",    6  },/* MegaOhm (in SCPI, MR=MAR=MegaOhm) */
	{ "mar",   6  },/* MegaOhm  */
	{ "mohm",  6  },/* MegaOhm  */
	{ "maohm", 6  },/* MegaOhm  */
	{ "ur",   -6  },/* MicroOhm */
	{ "uohm", -6  },/* MicroOhm */
	{ "gr",    9  },/* GigaOhm  */
	{ "gohm",  9  },/* GigaOhm  */
	{ "nohm", -9  },/* NanoOhm  */
	{ "tohm",  12 },/* TeraOhm	*/
	{ "pohm", -12 },/* PicoOhm	*/
	{ "peohm", 15 },/* PetaOhm  */
	{ "fohm", -15 },/* FemtoOhm */
	{ "exohm", 18 },/* ExaOhm   */
	{ "aohm", -18 },/* AttoOhm  */
	{   0,    0  }
};

const PARAM_UNIT U_WATT[]={
    { "w",    0 },/* Watt      */
	{ "kw",   3 },/* KiloWatt  */
	{ "mw",  -3 },/* MilliWatt */
	{ "maw",  6 },/* MegaWatt  */
	{ "uw",  -6 },/* MicroWatt */
	{ "gw",   9 },/* GigaWatt  */
	{ "nw",  -9 },/* NanoWatt  */
	{ "tw",  12 },/* TeraWatt  */
	{ "pw", -12 },/* PicoWatt  */
	{ "pew", 15 },/* PetaWatt  */
	{ "fw", -15 },/* FemtoWatt */
	{ "exw", 18 },/* ExaWatt   */
	{ "aw", -18 },/* AttoWatt  */
    {   0,  0  }
};

const PARAM_UNIT U_DB_W[]={
	{ "dbw",    0 },/* Decibel Watt     */
	{ "dbkw",   3 },/* Decibel KiloWatt	*/
	{ "dbm",   -3 },/* Decibel MilliWatt*/
	{ "dbmw",  -3 },/* Decibel MilliWatt*/
	{ "dbmaw",  6 },/* Decibel MegaWatt	*/
	{ "dbuw",  -6 },/* Decibel MicroWatt*/
	{ "dbgw",   9 },/* Decibel GigaWatt	*/
	{ "dbnw",  -9 },/* Decibel NanoWatt	*/
	{ "dbtw",  12 },/* Decibel TeraWatt	*/
	{ "dbpw", -12 },/* Decibel PicoWatt	*/
	{ "dbpew", 15 },/* Decibel PetaWatt	*/
	{ "dbfw", -15 },/* Decibel FemtoWatt*/
	{ "dbexw", 18 },/* Decibel ExaWatt	*/
	{ "dbaw", -18 },/* Decibel AttoWatt	*/
	{	0, 0  }

};

const PARAM_UNIT U_JOULE[]={
	{ "j",	  0 },/* Joule		*/
	{ "kj",   3 },/* KiloJoule	*/
	{ "mj",  -3 },/* MilliJoule */
	{ "maj",  6 },/* MegaJoule	*/
	{ "uj",  -6 },/* MicroJoule */
	{ "gj",   9 },/* GigaJoule	*/
	{ "nj",  -9 },/* NanoJoule	*/
	{ "tj",  12 },/* TeraJoule	*/
	{ "pj", -12 },/* PicoJoule	*/
	{ "pej", 15 },/* PetaJoule	*/
	{ "fj", -15 },/* FemtoJoule */
	{ "exj", 18 },/* ExaJoule	*/
	{ "aj", -18 },/* AttoJoule	*/
	{	0, 0  }
};

const PARAM_UNIT U_FARAD[]={
	{ "f",	  0 },/* Farad		*/
	{ "kf",   3 },/* KiloFarad	*/
	{ "mf",  -3 },/* MilliFarad */
	{ "maf",  6 },/* MegaFarad	*/
	{ "uf",  -6 },/* MicroFarad */
	{ "gf",   9 },/* GigaFarad	*/
	{ "nf",  -9 },/* NanoFarad	*/
	{ "tf",  12 },/* TeraFarad	*/
	{ "pf", -12 },/* PicoFarad	*/
	{ "pef", 15 },/* PetaFarad	*/
	{ "ff", -15 },/* FemtoFarad */
	{ "exf", 18 },/* ExaFarad	*/
	{ "af", -18 },/* AttoFarad	*/
	{	0, 0  }
};

const PARAM_UNIT U_HENRY[]={
	{ "h",	  0 },/* Henry      */
	{ "kh",   3 },/* KiloHenry  */
	{ "mh",  -3 },/* MilliHenry */
	{ "mah",  6 },/* MegaHenry  */
	{ "uh",  -6 },/* MicroHenry */
	{ "gh",   9 },/* GigaHenry  */
	{ "nh",  -9 },/* NanoHenry  */
	{ "th",  12 },/* TeraHenry  */
	{ "ph", -12 },/* PicoHenry  */
	{ "peh", 15 },/* PetaHenry  */
	{ "fh", -15 },/* FemtoHenry */
	{ "exh", 18 },/* ExaHenry   */
	{ "ah", -18 },/* AttoHenry  */
	{	0, 0  }
};

const PARAM_UNIT U_HERTZ[]={
    { "hz",    0 },/* Amp      */
	{ "khz",   3 },/* KiloAmp  */
	{ "mhz",   6 },/* MegaAmp (in SCPI,MHZ=MAHZ=MegaHertz) */
	{ "mahz",  6 },/* MegaAmp  */
	{ "uhz",  -6 },/* MicroAmp */
	{ "ghz",   9 },/* GigaAmp  */
	{ "nhz",  -9 },/* NanoAmp  */
	{ "thz",  12 },/* TeraAmp  */
	{ "phz", -12 },/* PicoAmp  */
	{ "pehz", 15 },/* PetaAmp  */
	{ "fhz", -15 },/* FemtoAmp */
	{ "exhz", 18 },/* ExaAmp   */
	{ "ahz", -18 },/* AttoAmp  */
    {   0,   0  }
};

const PARAM_UNIT U_SEC[]={
    { "s",    0 },/* Second      */
	{ "ks",   3 },/* KiloSecond  */
	{ "ms",  -3 },/* MilliSecond */
	{ "mas",  6 },/* MegaSecond  */
	{ "us",  -6 },/* MicroSecond */
	{ "gs",   9 },/* GigaSecond  */
	{ "ns",  -9 },/* NanoSecond  */
	{ "tS",  12 },/* TeraSecond  */
	{ "ps", -12 },/* PicoSecond  */
	{ "pes", 15 },/* PetaSecond  */
	{ "fs", -15 },/* FemtoSecond */
	{ "exs", 18 },/* ExaSecond   */
	{ "as", -18 },/* AttoSecond  */
    {   0, 0  }
};

const PARAM_UNIT U_TEMPERATURE[]={
    { "k",  0  },/* Degree Kelvin     */
    { "cel",0  },/* Degree Celsius    */
    { "far",0  },/* Degree Fahrenheit */
    {   0,  0  }
};

const PARAM_UNIT U_MHO[]={
	/*(Note: no MilliOhms in SCPI - see MegaOhm) */
	{ "r",     0  },/* Ohm      */
	{ "mho",   0  },/* Ohm      */
	{ "kr",    3  },/* KiloOhm  */
	{ "kmho",  3  },/* KiloOhm  */
	{ "mr",    6  },/* MegaOhm (in SCPI, MR=MAR=MegaOhm) */
	{ "mar",   6  },/* MegaOhm  */
	{ "mmho",  6  },/* MegaOhm  */
	{ "mamho", 6  },/* MegaOhm  */
	{ "ur",   -6  },/* MicroOhm */
	{ "umho", -6  },/* MicroOhm */
	{ "gr",    9  },/* GigaOhm  */
	{ "gmho",  9  },/* GigaOhm  */
	{ "nmho", -9  },/* NanoOhm  */
	{ "tmho",  12 },/* TeraOhm	*/
	{ "pmho", -12 },/* PicoOhm	*/
	{ "pemho", 15 },/* PetaOhm  */
	{ "fmho", -15 },/* FemtoOhm */
	{ "exmho", 18 },/* ExaOhm   */
	{ "amho", -18 },/* AttoOhm  */
	{   0,    0  }
};


//----------------------------
//---
const PARAM_UNIT* units[]= {
	(PARAM_UNIT*) U_VOLT,
	(PARAM_UNIT*) U_AMP,
	(PARAM_UNIT*) U_OHM,
	(PARAM_UNIT*) U_WATT,
	(PARAM_UNIT*) U_DB_W,
	(PARAM_UNIT*) U_JOULE,
	(PARAM_UNIT*) U_FARAD,
	(PARAM_UNIT*) U_HENRY,
	(PARAM_UNIT*) U_HERTZ,
	(PARAM_UNIT*) U_SEC,
	(PARAM_UNIT*) U_TEMPERATURE,
	(PARAM_UNIT*) U_MHO
};

#endif
