#include "scpiStruct.h"
#include "scpiNode.h"
//------------------------------------------------------------------
//const	COMD_WORD ID_NAME = 	{ MIN,	 MAX,	 (char*) STRING};
const	COMD_WORD _kw_CAL = 	{ 	4,	4,	(char*)"*CAL"	};
const	COMD_WORD _kw_CLS = 	{ 	4,	4,	(char*)"*CLS"	};
const	COMD_WORD _kw_ESE = 	{ 	4,	4,	(char*)"*ESE"	};
const	COMD_WORD _kw_ESR = 	{ 	4,	4,	(char*)"*ESR"	};
const	COMD_WORD _kw_IDN = 	{ 	4,	4,	(char*)"*IDN"	};
const	COMD_WORD _kw_OPC = 	{ 	4,	4,	(char*)"*OPC"	};
const	COMD_WORD _kw_RCL = 	{ 	4,	4,	(char*)"*RCL"	};
const	COMD_WORD _kw_RST = 	{ 	4,	4,	(char*)"*RST"	};
const	COMD_WORD _kw_SAV = 	{ 	4,	4,	(char*)"*SAV"	};
const	COMD_WORD _kw_SRE = 	{ 	4,	4,	(char*)"*SRE"	};
const	COMD_WORD _kw_STB = 	{ 	4,	4,	(char*)"*STB"	};
const	COMD_WORD _kw_TRG = 	{ 	4,	4,	(char*)"*TRG"	};
const	COMD_WORD _kw_TST = 	{ 	4,	4,	(char*)"*TST"	};
const	COMD_WORD _kw_WAI = 	{ 	4,	4,	(char*)"*WAI"	};
const	COMD_WORD _kwA = 	{ 	1,	1,	(char*)"a"	};
const	COMD_WORD _kwABORt = 	{ 	4,	5,	(char*)"abort"	};
const	COMD_WORD _kwACTion = 	{ 	3,	6,	(char*)"action"	};
const	COMD_WORD _kwADD = 	{ 	3,	3,	(char*)"add"	};
const	COMD_WORD _kwALARm = 	{ 	4,	5,	(char*)"alarm"	};
const	COMD_WORD _kwALL = 	{ 	3,	3,	(char*)"all"	};
const	COMD_WORD _kwAMPLitude = 	{ 	4,	9,	(char*)"amplitude"	};
const	COMD_WORD _kwAUTO = 	{ 	4,	4,	(char*)"auto"	};
const	COMD_WORD _kwB = 	{ 	1,	1,	(char*)"b"	};
const	COMD_WORD _kwBIValue = 	{ 	3,	7,	(char*)"bivalue"	};
const	COMD_WORD _kwBRIGhtness = 	{ 	4,	10,	(char*)"brightness"	};
const	COMD_WORD _kwC = 	{ 	1,	1,	(char*)"c"	};
const	COMD_WORD _kwCALibrate = 	{ 	3,	9,	(char*)"calibrate"	};
const	COMD_WORD _kwCC = 	{ 	2,	2,	(char*)"cc"	};
const	COMD_WORD _kwCCCV = 	{ 	4,	4,	(char*)"cccv"	};
const	COMD_WORD _kwCCH = 	{ 	3,	3,	(char*)"cch"	};
const	COMD_WORD _kwCCL = 	{ 	3,	3,	(char*)"ccl"	};
const	COMD_WORD _kwCHAin = 	{ 	3,	5,	(char*)"chain"	};
const	COMD_WORD _kwCHANnel = 	{ 	4,	7,	(char*)"channel"	};
const	COMD_WORD _kwCHEaksum = 	{ 	3,	8,	(char*)"cheaksum"	};
const	COMD_WORD _kwCLEar = 	{ 	3,	5,	(char*)"clear"	};
const	COMD_WORD _kwCNTime = 	{ 	3,	6,	(char*)"cntime"	};
const	COMD_WORD _kwCOMPlete = 	{ 	4,	8,	(char*)"complete"	};
const	COMD_WORD _kwCONDition = 	{ 	4,	9,	(char*)"condition"	};
const	COMD_WORD _kwCONDuctance = 	{ 	4,	11,	(char*)"conductance"	};
const	COMD_WORD _kwCONFigure = 	{ 	4,	9,	(char*)"configure"	};
const	COMD_WORD _kwCONTinue = 	{ 	4,	8,	(char*)"continue"	};
const	COMD_WORD _kwCONTinuous = 	{ 	4,	10,	(char*)"continuous"	};
const	COMD_WORD _kwCONTrast = 	{ 	4,	8,	(char*)"contrast"	};
const	COMD_WORD _kwCONTrol = 	{ 	4,	7,	(char*)"control"	};
const	COMD_WORD _kwCOTime = 	{ 	3,	6,	(char*)"cotime"	};
const	COMD_WORD _kwCOUNt = 	{ 	4,	5,	(char*)"count"	};
const	COMD_WORD _kwCP = 	{ 	2,	2,	(char*)"cp"	};
const	COMD_WORD _kwCPCV = 	{ 	4,	4,	(char*)"cpcv"	};
const	COMD_WORD _kwCPH = 	{ 	3,	3,	(char*)"cph"	};
const	COMD_WORD _kwCPL = 	{ 	3,	3,	(char*)"cpl"	};
const	COMD_WORD _kwCR = 	{ 	2,	2,	(char*)"cr"	};
const	COMD_WORD _kwCRANge = 	{ 	4,	6,	(char*)"crange"	};
const	COMD_WORD _kwCRCV = 	{ 	4,	4,	(char*)"crcv"	};
const	COMD_WORD _kwCRH = 	{ 	3,	3,	(char*)"crh"	};
const	COMD_WORD _kwCRL = 	{ 	3,	3,	(char*)"crl"	};
const	COMD_WORD _kwCRUNit = 	{ 	4,	6,	(char*)"crunit"	};
const	COMD_WORD _kwCSUMmary = 	{ 	4,	8,	(char*)"csummary"	};
const	COMD_WORD _kwCTIMe = 	{ 	4,	5,	(char*)"ctime"	};
const	COMD_WORD _kwCURRent = 	{ 	4,	7,	(char*)"current"	};
const	COMD_WORD _kwCV = 	{ 	2,	2,	(char*)"cv"	};
const	COMD_WORD _kwCVH = 	{ 	3,	3,	(char*)"cvh"	};
const	COMD_WORD _kwCVL = 	{ 	3,	3,	(char*)"cvl"	};
const	COMD_WORD _kwCXCV = 	{ 	4,	4,	(char*)"cxcv"	};
const	COMD_WORD _kwDC = 	{ 	2,	2,	(char*)"dc"	};
const	COMD_WORD _kwDEFault = 	{ 	3,	7,	(char*)"default"	};
const	COMD_WORD _kwDELay = 	{ 	3,	5,	(char*)"delay"	};
const	COMD_WORD _kwDELet = 	{ 	3,	5,	(char*)"delet"	};
const	COMD_WORD _kwDELete = 	{ 	3,	6,	(char*)"delete"	};
const	COMD_WORD _kwDIRect = 	{ 	3,	6,	(char*)"direct"	};
const	COMD_WORD _kwDOWN = 	{ 	4,	4,	(char*)"down"	};
const	COMD_WORD _kwDTIMe = 	{ 	4,	5,	(char*)"dtime"	};
const	COMD_WORD _kwDUTY = 	{ 	4,	4,	(char*)"duty"	};
const	COMD_WORD _kwDYNamic = 	{ 	3,	7,	(char*)"dynamic"	};
const	COMD_WORD _kwEDIT = 	{ 	4,	4,	(char*)"edit"	};
const	COMD_WORD _kwELAPsed = 	{ 	4,	7,	(char*)"elapsed"	};
const	COMD_WORD _kwENABle = 	{ 	4,	6,	(char*)"enable"	};
const	COMD_WORD _kwEND = 	{ 	3,	3,	(char*)"end"	};
const	COMD_WORD _kwENGLish = 	{ 	4,	7,	(char*)"english"	};
const	COMD_WORD _kwERRor = 	{ 	3,	5,	(char*)"error"	};
const	COMD_WORD _kwETIMe = 	{ 	4,	5,	(char*)"etime"	};
const	COMD_WORD _kwEVENt = 	{ 	4,	5,	(char*)"event"	};
const	COMD_WORD _kwEXECuting = 	{ 	4,	9,	(char*)"executing"	};
const	COMD_WORD _kwEXTernal = 	{ 	3,	8,	(char*)"external"	};
const	COMD_WORD _kwEXTR = 	{ 	4,	4,	(char*)"extr"	};
const	COMD_WORD _kwEXTV = 	{ 	4,	4,	(char*)"extv"	};
const	COMD_WORD _kwFACTory = 	{ 	4,	7,	(char*)"factory"	};
const	COMD_WORD _kwFALL = 	{ 	4,	4,	(char*)"fall"	};
const	COMD_WORD _kwFAST = 	{ 	4,	4,	(char*)"fast"	};
const	COMD_WORD _kwFCC = 	{ 	3,	3,	(char*)"fcc"	};
const	COMD_WORD _kwFCR = 	{ 	3,	3,	(char*)"fcr"	};
const	COMD_WORD _kwFDUTy = 	{ 	4,	5,	(char*)"fduty"	};
const	COMD_WORD _kwFETCh = 	{ 	4,	5,	(char*)"fetch"	};
const	COMD_WORD _kwFILL = 	{ 	4,	4,	(char*)"fill"	};
const	COMD_WORD _kwFIMon = 	{ 	3,	5,	(char*)"fimon"	};
const	COMD_WORD _kwFREQuency = 	{ 	4,	9,	(char*)"frequency"	};
const	COMD_WORD _kwFSEQ = 	{ 	4,	4,	(char*)"fseq"	};
const	COMD_WORD _kwFSEQuence = 	{ 	4,	9,	(char*)"fsequence"	};
const	COMD_WORD _kwFSPeed = 	{ 	3,	6,	(char*)"fspeed"	};
const	COMD_WORD _kwFUNCtion = 	{ 	4,	8,	(char*)"function"	};
const	COMD_WORD _kwGNG = 	{ 	3,	3,	(char*)"gng"	};
const	COMD_WORD _kwGPIB = 	{ 	4,	4,	(char*)"gpib"	};
const	COMD_WORD _kwGTLocal = 	{ 	3,	7,	(char*)"gtlocal"	};
const	COMD_WORD _kwH = 	{ 	1,	1,	(char*)"h"	};
const	COMD_WORD _kwHIGH = 	{ 	4,	4,	(char*)"high"	};
const	COMD_WORD _kwHOLD = 	{ 	4,	4,	(char*)"hold"	};
const	COMD_WORD _kwHP = 	{ 	2,	2,	(char*)"hp"	};
const	COMD_WORD _kwIHVH = 	{ 	4,	4,	(char*)"ihvh"	};
const	COMD_WORD _kwIHVL = 	{ 	4,	4,	(char*)"ihvl"	};
const	COMD_WORD _kwILVH = 	{ 	4,	4,	(char*)"ilvh"	};
const	COMD_WORD _kwILVL = 	{ 	4,	4,	(char*)"ilvl"	};
const	COMD_WORD _kwIMMediate = 	{ 	3,	9,	(char*)"immediate"	};
const	COMD_WORD _kwINFinity = 	{ 	3,	8,	(char*)"infinity"	};
const	COMD_WORD _kwINITiate = 	{ 	4,	8,	(char*)"initiate"	};
const	COMD_WORD _kwINPut = 	{ 	3,	5,	(char*)"input"	};
const	COMD_WORD _kwINSert = 	{ 	3,	6,	(char*)"insert"	};
const	COMD_WORD _kwINTerface = 	{ 	3,	9,	(char*)"interface"	};
const	COMD_WORD _kwKLOCk = 	{ 	4,	5,	(char*)"klock"	};
const	COMD_WORD _kwKNOB = 	{ 	4,	4,	(char*)"knob"	};
const	COMD_WORD _kwL = 	{ 	1,	1,	(char*)"l"	};
const	COMD_WORD _kwLANGuage = 	{ 	4,	8,	(char*)"language"	};
const	COMD_WORD _kwLAST = 	{ 	4,	4,	(char*)"last"	};
const	COMD_WORD _kwLEVel = 	{ 	3,	5,	(char*)"level"	};
const	COMD_WORD _kwLIMit = 	{ 	3,	5,	(char*)"limit"	};
const	COMD_WORD _kwLINear = 	{ 	3,	6,	(char*)"linear"	};
const	COMD_WORD _kwLINPut = 	{ 	4,	6,	(char*)"linput"	};
const	COMD_WORD _kwLLOad = 	{ 	3,	5,	(char*)"lload"	};
const	COMD_WORD _kwLLOut = 	{ 	3,	5,	(char*)"llout"	};
const	COMD_WORD _kwLOAD = 	{ 	4,	4,	(char*)"load"	};
const	COMD_WORD _kwLOADonin = 	{ 	4,	8,	(char*)"loadonin"	};
const	COMD_WORD _kwLOFF = 	{ 	4,	4,	(char*)"loff"	};
const	COMD_WORD _kwLON = 	{ 	3,	3,	(char*)"lon"	};
const	COMD_WORD _kwLOOP = 	{ 	4,	4,	(char*)"loop"	};
const	COMD_WORD _kwLOUTput = 	{ 	4,	7,	(char*)"loutput"	};
const	COMD_WORD _kwLOW = 	{ 	3,	3,	(char*)"low"	};
const	COMD_WORD _kwLP = 	{ 	2,	2,	(char*)"lp"	};
const	COMD_WORD _kwLVALue = 	{ 	4,	6,	(char*)"lvalue"	};
const	COMD_WORD _kwMANual = 	{ 	3,	6,	(char*)"manual"	};
const	COMD_WORD _kwMASTer = 	{ 	4,	6,	(char*)"master"	};
const	COMD_WORD _kwMAXimum = 	{ 	3,	7,	(char*)"maximum"	};
const	COMD_WORD _kwMEASure = 	{ 	4,	7,	(char*)"measure"	};
const	COMD_WORD _kwMEDium = 	{ 	3,	6,	(char*)"medium"	};
const	COMD_WORD _kwMEMO = 	{ 	4,	4,	(char*)"memo"	};
const	COMD_WORD _kwMEMory = 	{ 	3,	6,	(char*)"memory"	};
const	COMD_WORD _kwMHO = 	{ 	3,	3,	(char*)"mho"	};
const	COMD_WORD _kwMIDDle = 	{ 	4,	6,	(char*)"middle"	};
const	COMD_WORD _kwMINimum = 	{ 	3,	7,	(char*)"minimum"	};
const	COMD_WORD _kwMODE = 	{ 	4,	4,	(char*)"mode"	};
const	COMD_WORD _kwNAME = 	{ 	4,	4,	(char*)"name"	};
const	COMD_WORD _kwNCC = 	{ 	3,	3,	(char*)"ncc"	};
const	COMD_WORD _kwNCP = 	{ 	3,	3,	(char*)"ncp"	};
const	COMD_WORD _kwNCR = 	{ 	3,	3,	(char*)"ncr"	};
const	COMD_WORD _kwNCV = 	{ 	3,	3,	(char*)"ncv"	};
const	COMD_WORD _kwNEXT = 	{ 	4,	4,	(char*)"next"	};
const	COMD_WORD _kwNORMal = 	{ 	4,	6,	(char*)"normal"	};
const	COMD_WORD _kwNSEQ = 	{ 	4,	4,	(char*)"nseq"	};
const	COMD_WORD _kwNSEQuence = 	{ 	4,	9,	(char*)"nsequence"	};
const	COMD_WORD _kwNSPeed = 	{ 	3,	6,	(char*)"nspeed"	};
const	COMD_WORD _kwNTRansition = 	{ 	3,	11,	(char*)"ntransition"	};
const	COMD_WORD _kwNUMBer = 	{ 	4,	6,	(char*)"number"	};
const	COMD_WORD _kwOCP = 	{ 	3,	3,	(char*)"ocp"	};
const	COMD_WORD _kwOFF = 	{ 	3,	3,	(char*)"off"	};
const	COMD_WORD _kwOFFSet = 	{ 	4,	6,	(char*)"offset"	};
const	COMD_WORD _kwOFFTime = 	{ 	4,	7,	(char*)"offtime"	};
const	COMD_WORD _kwOHM = 	{ 	3,	3,	(char*)"ohm"	};
const	COMD_WORD _kwOLD = 	{ 	3,	3,	(char*)"old"	};
const	COMD_WORD _kwON = 	{ 	2,	2,	(char*)"on"	};
const	COMD_WORD _kwONTime = 	{ 	3,	6,	(char*)"ontime"	};
const	COMD_WORD _kwOPERation = 	{ 	4,	9,	(char*)"operation"	};
const	COMD_WORD _kwOPP = 	{ 	3,	3,	(char*)"opp"	};
const	COMD_WORD _kwOUTPup = 	{ 	4,	6,	(char*)"outpup"	};
const	COMD_WORD _kwOUTPut = 	{ 	4,	6,	(char*)"output"	};
const	COMD_WORD _kwOVER = 	{ 	4,	4,	(char*)"over"	};
const	COMD_WORD _kwOVP = 	{ 	3,	3,	(char*)"ovp"	};
const	COMD_WORD _kwP1 = 	{ 	2,	2,	(char*)"p1"	};
const	COMD_WORD _kwP10 = 	{ 	3,	3,	(char*)"p10"	};
const	COMD_WORD _kwP11 = 	{ 	3,	3,	(char*)"p11"	};
const	COMD_WORD _kwP12 = 	{ 	3,	3,	(char*)"p12"	};
const	COMD_WORD _kwP13 = 	{ 	3,	3,	(char*)"p13"	};
const	COMD_WORD _kwP14 = 	{ 	3,	3,	(char*)"p14"	};
const	COMD_WORD _kwP15 = 	{ 	3,	3,	(char*)"p15"	};
const	COMD_WORD _kwP16 = 	{ 	3,	3,	(char*)"p16"	};
const	COMD_WORD _kwP2 = 	{ 	2,	2,	(char*)"p2"	};
const	COMD_WORD _kwP2P = 	{ 	3,	3,	(char*)"p2p"	};
const	COMD_WORD _kwP3 = 	{ 	2,	2,	(char*)"p3"	};
const	COMD_WORD _kwP4 = 	{ 	2,	2,	(char*)"p4"	};
const	COMD_WORD _kwP5 = 	{ 	2,	2,	(char*)"p5"	};
const	COMD_WORD _kwP6 = 	{ 	2,	2,	(char*)"p6"	};
const	COMD_WORD _kwP7 = 	{ 	2,	2,	(char*)"p7"	};
const	COMD_WORD _kwP8 = 	{ 	2,	2,	(char*)"p8"	};
const	COMD_WORD _kwP9 = 	{ 	2,	2,	(char*)"p9"	};
const	COMD_WORD _kwPASS = 	{ 	4,	4,	(char*)"pass"	};
const	COMD_WORD _kwPASSword = 	{ 	4,	8,	(char*)"password"	};
const	COMD_WORD _kwPAUSe = 	{ 	4,	5,	(char*)"pause"	};
const	COMD_WORD _kwPERCent = 	{ 	4,	7,	(char*)"percent"	};
const	COMD_WORD _kwPFTime = 	{ 	3,	6,	(char*)"pftime"	};
const	COMD_WORD _kwPOINt = 	{ 	4,	5,	(char*)"point"	};
const	COMD_WORD _kwPOWer = 	{ 	3,	5,	(char*)"power"	};
const	COMD_WORD _kwPRESet = 	{ 	4,	6,	(char*)"preset"	};
const	COMD_WORD _kwPROG = 	{ 	4,	4,	(char*)"prog"	};
const	COMD_WORD _kwPROGram = 	{ 	4,	7,	(char*)"program"	};
const	COMD_WORD _kwPROTection = 	{ 	4,	10,	(char*)"protection"	};
const	COMD_WORD _kwPSENsor = 	{ 	4,	7,	(char*)"psensor"	};
const	COMD_WORD _kwPTRansition = 	{ 	3,	11,	(char*)"ptransition"	};
const	COMD_WORD _kwPULSe = 	{ 	4,	5,	(char*)"pulse"	};
const	COMD_WORD _kwQUEStionable = 	{ 	4,	12,	(char*)"questionable"	};
const	COMD_WORD _kwRANGe = 	{ 	4,	5,	(char*)"range"	};
const	COMD_WORD _kwRECall = 	{ 	3,	6,	(char*)"recall"	};
const	COMD_WORD _kwREMaining = 	{ 	3,	9,	(char*)"remaining"	};
const	COMD_WORD _kwREMote = 	{ 	3,	6,	(char*)"remote"	};
const	COMD_WORD _kwRENable = 	{ 	3,	7,	(char*)"renable"	};
const	COMD_WORD _kwRESistance = 	{ 	3,	10,	(char*)"resistance"	};
const	COMD_WORD _kwRESPonse = 	{ 	4,	8,	(char*)"response"	};
const	COMD_WORD _kwRESult = 	{ 	3,	6,	(char*)"result"	};
const	COMD_WORD _kwRIMon = 	{ 	3,	5,	(char*)"rimon"	};
const	COMD_WORD _kwRING = 	{ 	4,	4,	(char*)"ring"	};
const	COMD_WORD _kwRINV = 	{ 	4,	4,	(char*)"rinv"	};
const	COMD_WORD _kwRISE = 	{ 	4,	4,	(char*)"rise"	};
const	COMD_WORD _kwRPTStep = 	{ 	4,	7,	(char*)"rptstep"	};
const	COMD_WORD _kwRUN = 	{ 	3,	3,	(char*)"run"	};
const	COMD_WORD _kwSAFety = 	{ 	3,	6,	(char*)"safety"	};
const	COMD_WORD _kwSAVE = 	{ 	4,	4,	(char*)"save"	};
const	COMD_WORD _kwSCALar = 	{ 	4,	6,	(char*)"scalar"	};
const	COMD_WORD _kwSELected = 	{ 	3,	8,	(char*)"selected"	};
const	COMD_WORD _kwSEQuence = 	{ 	3,	8,	(char*)"sequence"	};
const	COMD_WORD _kwSERial = 	{ 	3,	6,	(char*)"serial"	};
const	COMD_WORD _kwSET = 	{ 	3,	3,	(char*)"set"	};
const	COMD_WORD _kwSETup = 	{ 	3,	5,	(char*)"setup"	};
const	COMD_WORD _kwSHORt = 	{ 	4,	5,	(char*)"short"	};
const	COMD_WORD _kwSHVL = 	{ 	4,	4,	(char*)"shvl"	};
const	COMD_WORD _kwSKIP = 	{ 	4,	4,	(char*)"skip"	};
const	COMD_WORD _kwSLAVe = 	{ 	4,	5,	(char*)"slave"	};
const	COMD_WORD _kwSLEW = 	{ 	4,	4,	(char*)"slew"	};
const	COMD_WORD _kwSLOW = 	{ 	4,	4,	(char*)"slow"	};
const	COMD_WORD _kwSLVH = 	{ 	4,	4,	(char*)"slvh"	};
const	COMD_WORD _kwSOURce = 	{ 	4,	6,	(char*)"source"	};
const	COMD_WORD _kwSPEaker = 	{ 	3,	7,	(char*)"speaker"	};
const	COMD_WORD _kwSPECtest = 	{ 	4,	8,	(char*)"spectest"	};
const	COMD_WORD _kwSRATe = 	{ 	4,	5,	(char*)"srate"	};
const	COMD_WORD _kwSSTart = 	{ 	3,	6,	(char*)"sstart"	};
const	COMD_WORD _kwSTARt = 	{ 	4,	5,	(char*)"start"	};
const	COMD_WORD _kwSTATe = 	{ 	4,	5,	(char*)"state"	};
const	COMD_WORD _kwSTATic = 	{ 	4,	6,	(char*)"static"	};
const	COMD_WORD _kwSTATus = 	{ 	4,	6,	(char*)"status"	};
const	COMD_WORD _kwSTEP = 	{ 	4,	4,	(char*)"step"	};
const	COMD_WORD _kwSTIMe = 	{ 	4,	5,	(char*)"stime"	};
const	COMD_WORD _kwSTOP = 	{ 	4,	4,	(char*)"stop"	};
const	COMD_WORD _kwSYNC = 	{ 	4,	4,	(char*)"sync"	};
const	COMD_WORD _kwSYSTem = 	{ 	4,	6,	(char*)"system"	};
const	COMD_WORD _kwT = 	{ 	1,	1,	(char*)"t"	};
const	COMD_WORD _kwTBASe = 	{ 	4,	5,	(char*)"tbase"	};
const	COMD_WORD _kwTEMP = 	{ 	4,	4,	(char*)"temp"	};
const	COMD_WORD _kwTIME = 	{ 	4,	4,	(char*)"time"	};
const	COMD_WORD _kwTIMer = 	{ 	3,	5,	(char*)"timer"	};
const	COMD_WORD _kwTOGGle = 	{ 	4,	6,	(char*)"toggle"	};
const	COMD_WORD _kwTRIGger = 	{ 	4,	7,	(char*)"trigger"	};
const	COMD_WORD _kwTRIGgered = 	{ 	4,	9,	(char*)"triggered"	};
const	COMD_WORD _kwTRIP = 	{ 	4,	4,	(char*)"trip"	};
const	COMD_WORD _kwTRUN = 	{ 	4,	4,	(char*)"trun"	};
const	COMD_WORD _kwUNDer = 	{ 	3,	5,	(char*)"under"	};
const	COMD_WORD _kwUNReg = 	{ 	3,	5,	(char*)"unreg"	};
const	COMD_WORD _kwUP = 	{ 	2,	2,	(char*)"up"	};
const	COMD_WORD _kwUPDated = 	{ 	3,	7,	(char*)"updated"	};
const	COMD_WORD _kwUSB = 	{ 	3,	3,	(char*)"usb"	};
const	COMD_WORD _kwUSER = 	{ 	4,	4,	(char*)"user"	};
const	COMD_WORD _kwUTILity = 	{ 	4,	7,	(char*)"utility"	};
const	COMD_WORD _kwUVP = 	{ 	3,	3,	(char*)"uvp"	};
const	COMD_WORD _kwVA = 	{ 	2,	2,	(char*)"va"	};
const	COMD_WORD _kwVALue = 	{ 	3,	5,	(char*)"value"	};
const	COMD_WORD _kwVB = 	{ 	2,	2,	(char*)"vb"	};
const	COMD_WORD _kwVDELay = 	{ 	4,	6,	(char*)"vdelay"	};
const	COMD_WORD _kwVERSion = 	{ 	4,	7,	(char*)"version"	};
const	COMD_WORD _kwVOLTage = 	{ 	4,	7,	(char*)"voltage"	};
const	COMD_WORD _kwVON = 	{ 	3,	3,	(char*)"von"	};
const	COMD_WORD _kwVRANge = 	{ 	4,	6,	(char*)"vrange"	};
const	COMD_WORD _kwWAIT = 	{ 	4,	4,	(char*)"wait"	};
const	COMD_WORD _kwWAVE = 	{ 	4,	4,	(char*)"wave"	};
const	COMD_WORD _kwWIDTh = 	{ 	4,	5,	(char*)"width"	};



//------------------------------------------------------------------
// keyword Group
//const PARAM_KEYWORD _kgNAME[]= {
//	  {(COMD_WORD*)(&_kwMEMBER0),    0 },
//	  {(COMD_WORD*)(&_kwMEMBER1),    1 },
//	  {(COMD_WORD*)(&_kwMEMBER2),    2 },
//};
const	PARAM_KEYWORD _kg1[]  = { 
	{(COMD_WORD*)(&_kwOFF),	0},
	{(COMD_WORD*)(&_kwON),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg2[]  = { 
	{(COMD_WORD*)(&_kwMINimum),	0},
	{(COMD_WORD*)(&_kwMAXimum),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg3[]  = { 
	{(COMD_WORD*)(&_kwMINimum),	0},
	{(COMD_WORD*)(&_kwMAXimum),	1},
	{(COMD_WORD*)(&_kwOFF),	2},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg4[]  = { 
	{(COMD_WORD*)(&_kwLOAD),	0},
	{(COMD_WORD*)(&_kwPROG),	1},
	{(COMD_WORD*)(&_kwNSEQ),	2},
	{(COMD_WORD*)(&_kwFSEQ),	3},
	{(COMD_WORD*)(&_kwOCP),	4},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg5[]  = { 
	{(COMD_WORD*)(&_kwMINimum),	0},
	{(COMD_WORD*)(&_kwMAXimum),	1},
	{(COMD_WORD*)(&_kwLIMit),	2},
	{(COMD_WORD*)(&_kwLOFF),	3},
	{(COMD_WORD*)(&_kwOFF),	4},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg6[]  = { 
	{(COMD_WORD*)(&_kwMINimum),	0},
	{(COMD_WORD*)(&_kwMAXimum),	1},
	{(COMD_WORD*)(&_kwINFinity),	2},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg7[]  = { 
	{(COMD_WORD*)(&_kwMINimum),	0},
	{(COMD_WORD*)(&_kwMAXimum),	1},
	{(COMD_WORD*)(&_kwLON),	2},
	{(COMD_WORD*)(&_kwLOFF),	3},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg8[]  = { 
	{(COMD_WORD*)(&_kwOHM),	0},
	{(COMD_WORD*)(&_kwMHO),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg9[]  = { 
	{(COMD_WORD*)(&_kwVALue),	0},
	{(COMD_WORD*)(&_kwPERCent),	1},
	{(COMD_WORD*)(&_kwTIME),	2},
	{(COMD_WORD*)(&_kwFDUTy),	3},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg10[]  = { 
	{(COMD_WORD*)(&_kwSAFety),	0},
	{(COMD_WORD*)(&_kwDIRect),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg11[]  = { 
	{(COMD_WORD*)(&_kwTOGGle),	0},
	{(COMD_WORD*)(&_kwHOLD),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg12[]  = { 
	{(COMD_WORD*)(&_kwVALue),	0},
	{(COMD_WORD*)(&_kwPERCent),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg13[]  = { 
	{(COMD_WORD*)(&_kwOFF),	0},
	{(COMD_WORD*)(&_kwVOLTage),	1},
	{(COMD_WORD*)(&_kwRESistance),	2},
	{(COMD_WORD*)(&_kwRINV),	3},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg14[]  = { 
	{(COMD_WORD*)(&_kwOFF),	0},
	{(COMD_WORD*)(&_kwHIGH),	1},
	{(COMD_WORD*)(&_kwLOW),	2},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg15[]  = { 
	{(COMD_WORD*)(&_kwOFF),	0},
	{(COMD_WORD*)(&_kwMASTer),	1},
	{(COMD_WORD*)(&_kwSLAVe),	2},
	{(COMD_WORD*)(&_kwON),	3},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg16[]  = { 
	{(COMD_WORD*)(&_kwCC),	0},
	{(COMD_WORD*)(&_kwCR),	1},
	{(COMD_WORD*)(&_kwCV),	2},
	{(COMD_WORD*)(&_kwCP),	3},
	{(COMD_WORD*)(&_kwCCCV),	4},
	{(COMD_WORD*)(&_kwCRCV),	5},
	{(COMD_WORD*)(&_kwCPCV),	6},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg17[]  = { 
	{(COMD_WORD*)(&_kwHIGH),	0},
	{(COMD_WORD*)(&_kwLOW),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg18[]  = { 
	{(COMD_WORD*)(&_kwSTATic),	0},
	{(COMD_WORD*)(&_kwDYNamic),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg19[]  = { 
	{(COMD_WORD*)(&_kwA),	0},
	{(COMD_WORD*)(&_kwB),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg20[]  = { 
	{(COMD_WORD*)(&_kwSLOW),	0},
	{(COMD_WORD*)(&_kwFAST),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg21[]  = { 
	{(COMD_WORD*)(&_kwSLOW),	0},
	{(COMD_WORD*)(&_kwNORMal),	1},
	{(COMD_WORD*)(&_kwFAST),	2},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg22[]  = { 
	{(COMD_WORD*)(&_kwOFF),	0},
	{(COMD_WORD*)(&_kwON),	1},
	{(COMD_WORD*)(&_kwPAUSe),	2},
	{(COMD_WORD*)(&_kwCONTinue),	3},
	{(COMD_WORD*)(&_kwNEXT),	4},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg23[]  = { 
	{(COMD_WORD*)(&_kwSKIP),	0},
	{(COMD_WORD*)(&_kwAUTO),	1},
	{(COMD_WORD*)(&_kwMANual),	2},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg24[]  = { 
	{(COMD_WORD*)(&_kwOFF),	0},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg25[]  = { 
	{(COMD_WORD*)(&_kwP1),	0},
	{(COMD_WORD*)(&_kwP2),	1},
	{(COMD_WORD*)(&_kwP3),	2},
	{(COMD_WORD*)(&_kwP4),	3},
	{(COMD_WORD*)(&_kwP5),	4},
	{(COMD_WORD*)(&_kwP6),	5},
	{(COMD_WORD*)(&_kwP7),	6},
	{(COMD_WORD*)(&_kwP8),	7},
	{(COMD_WORD*)(&_kwP9),	8},
	{(COMD_WORD*)(&_kwP10),	9},
	{(COMD_WORD*)(&_kwP11),	10},
	{(COMD_WORD*)(&_kwP12),	11},
	{(COMD_WORD*)(&_kwP13),	12},
	{(COMD_WORD*)(&_kwP14),	13},
	{(COMD_WORD*)(&_kwP15),	14},
	{(COMD_WORD*)(&_kwP16),	15},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg26[]  = { 
	{(COMD_WORD*)(&_kwELAPsed),	0},
	{(COMD_WORD*)(&_kwREMaining),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg27[]  = { 
	{(COMD_WORD*)(&_kwUP),	0},
	{(COMD_WORD*)(&_kwDOWN),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg28[]  = { 
	{(COMD_WORD*)(&_kwCC),	0},
	{(COMD_WORD*)(&_kwCR),	1},
	{(COMD_WORD*)(&_kwCV),	2},
	{(COMD_WORD*)(&_kwCP),	3},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg29[]  = { 
	{(COMD_WORD*)(&_kwILVL),	0},
	{(COMD_WORD*)(&_kwIHVL),	1},
	{(COMD_WORD*)(&_kwILVH),	2},
	{(COMD_WORD*)(&_kwIHVH),	3},
	{(COMD_WORD*)(&_kwSLVH),	4},
	{(COMD_WORD*)(&_kwSHVL),	5},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg30[]  = { 
	{(COMD_WORD*)(&_kwINFinity),	0},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg31[]  = { 
	{(COMD_WORD*)(&_kwCC),	0},
	{(COMD_WORD*)(&_kwCR),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg32[]  = { 
	{(COMD_WORD*)(&_kwLOW),	0},
	{(COMD_WORD*)(&_kwMIDDle),	1},
	{(COMD_WORD*)(&_kwHIGH),	2},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg33[]  = { 
	{(COMD_WORD*)(&_kwNORMal),	0},
	{(COMD_WORD*)(&_kwFAST),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg34[]  = { 
	{(COMD_WORD*)(&_kwOFF),	0},
	{(COMD_WORD*)(&_kwON),	1},
	{(COMD_WORD*)(&_kwLOAD),	2},
	{(COMD_WORD*)(&_kwPROG),	3},
	{(COMD_WORD*)(&_kwNSEQ),	4},
	{(COMD_WORD*)(&_kwFSEQ),	5},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg35[]  = { 
	{(COMD_WORD*)(&_kwUSB),	0},
	{(COMD_WORD*)(&_kwGPIB),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg36[]  = { 
	{(COMD_WORD*)(&_kwOLD),	0},
	{(COMD_WORD*)(&_kwUPDated),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg37[]  = { 
	{(COMD_WORD*)(&_kwENGLish),	0},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg38[]  = { 
	{(COMD_WORD*)(&_kwLIMit),	0},
	{(COMD_WORD*)(&_kwTRIP),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg39[]  = { 
	{(COMD_WORD*)(&_kwHIGH),	0},
	{(COMD_WORD*)(&_kwMEDium),	1},
	{(COMD_WORD*)(&_kwLOW),	2},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg40[]  = { 
	{(COMD_WORD*)(&_kwCC),	0},
	{(COMD_WORD*)(&_kwCV),	1},
	{(COMD_WORD*)(&_kwCP),	2},
	{(COMD_WORD*)(&_kwCR),	3},
	{(COMD_WORD*)(&_kwCCCV),	4},
	{(COMD_WORD*)(&_kwCRCV),	5},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg41[]  = { 
	{(COMD_WORD*)(&_kwTRUN),	0},
	{(COMD_WORD*)(&_kwRUN),	1},
	{(COMD_WORD*)(&_kwSTOP),	2},
	{(COMD_WORD*)(&_kwPAUSe),	3},
	{(COMD_WORD*)(&_kwCONTinue),	4},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg42[]  = { 
	{(COMD_WORD*)(&_kwNCC),	0},
	{(COMD_WORD*)(&_kwNCR),	1},
	{(COMD_WORD*)(&_kwNCV),	2},
	{(COMD_WORD*)(&_kwNCP),	3},
	{(COMD_WORD*)(&_kwFCC),	4},
	{(COMD_WORD*)(&_kwFCR),	5},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg43[]  = { 
	{(COMD_WORD*)(&_kwCC),	0},
	{(COMD_WORD*)(&_kwCR),	1},
	{(COMD_WORD*)(&_kwCV),	2},
	{(COMD_WORD*)(&_kwCP),	3},
	{(COMD_WORD*)(&_kwCXCV),	4},
	{(COMD_WORD*)(&_kwFIMon),	5},
	{(COMD_WORD*)(&_kwRIMon),	6},
	{(COMD_WORD*)(&_kwEXTV),	7},
	{(COMD_WORD*)(&_kwEXTR),	8},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg44[]  = { 
	{(COMD_WORD*)(&_kwLOW),	0},
	{(COMD_WORD*)(&_kwHIGH),	1},
	{(COMD_WORD*) 0 ,	0}
};

const	PARAM_KEYWORD _kg45[]  = { 
	{(COMD_WORD*)(&_kwOFFSet),	0},
	{(COMD_WORD*)(&_kwHP),	1},
	{(COMD_WORD*)(&_kwLP),	2},
	{(COMD_WORD*) 0 ,	0}
};




//------------------------------------------------------------------
// Parameter Group
//const PARAM_ITEM  _pgNAME[]= {
//	  {{_PARAM_TYPE},  _PARAM_UNIT, (PARAM_KEYWORD*)&_KEYWORD_GROUP}, //Parameter 0
//	  {{_PARAM_TYPE},  _PARAM_UNIT, (PARAM_KEYWORD*)&_KEYWORD_GROUP}, //Parameter 1
//	  {{_PARAM_TYPE},  _PARAM_UNIT, (PARAM_KEYWORD*)&_KEYWORD_GROUP}, //Parameter 2
//};
const	PARAM_ITEM _pg1[]  = { 
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg2[]  = { 
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg3[]  = { 
	{{_NUMBER|_KEYWORD|_FLOAT},	_AMP,	(PARAM_KEYWORD*)& _kg2},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg4[]  = { 
	{{_NUMBER|_KEYWORD|_FLOAT},	_OHM,	(PARAM_KEYWORD*)& _kg2},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg5[]  = { 
	{{_NUMBER|_KEYWORD|_FLOAT},	_MHO,	(PARAM_KEYWORD*)& _kg2},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg6[]  = { 
	{{_NUMBER|_KEYWORD|_FLOAT},	_SEC,	(PARAM_KEYWORD*)& _kg2},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg7[]  = { 
	{{_KEYWORD|_OPTION},	0,	(PARAM_KEYWORD*)& _kg2},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg8[]  = { 
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg3},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg9[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg4},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg10[]  = { 
	{{_NUMBER|_KEYWORD|_FLOAT},	_AMP,	(PARAM_KEYWORD*)& _kg5},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg11[]  = { 
	{{_NUMBER|_KEYWORD|_FLOAT},	_WATT,	(PARAM_KEYWORD*)& _kg5},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg12[]  = { 
	{{_NUMBER|_KEYWORD|_FLOAT},	_VOLT,	(PARAM_KEYWORD*)& _kg2},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg13[]  = { 
	{{_NUMBER|_KEYWORD},	_SEC,	(PARAM_KEYWORD*)& _kg6},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg14[]  = { 
	{{_NUMBER|_KEYWORD|_FLOAT},	_SEC,	(PARAM_KEYWORD*)& _kg3},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg15[]  = { 
	{{_NUMBER|_KEYWORD|_FLOAT},	_VOLT,	(PARAM_KEYWORD*)& _kg7},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg16[]  = { 
	{{_NUMBER|_KEYWORD|_FLOAT},	0,	(PARAM_KEYWORD*)& _kg2},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg17[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg8},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg18[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg9},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg19[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg10},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg20[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg11},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg21[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg12},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg22[]  = { 
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg23[]  = { 
	{{_NUMBER|_KEYWORD|_FLOAT},	0,	(PARAM_KEYWORD*)& _kg2},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg24[]  = { 
	{{_NUMBER|_KEYWORD|_FLOAT},	_WATT,	(PARAM_KEYWORD*)& _kg2},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg25[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg13},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg26[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg14},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg27[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg15},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg28[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg16},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg29[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg17},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg30[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg18},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg31[]  = { 
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg19},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg32[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg20},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg33[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg21},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg34[]  = { 
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg22},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg35[]  = { 
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg23},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_KEYWORD|_FLOAT},	0,	(PARAM_KEYWORD*)& _kg24},
	{{_NUMBER|_KEYWORD|_FLOAT},	0,	(PARAM_KEYWORD*)& _kg24},
	{{_NUMBER|_KEYWORD|_FLOAT},	0,	(PARAM_KEYWORD*)& _kg24},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg36[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg23},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg37[]  = { 
	{{_NUMBER|_FLOAT},	_SEC,	(PARAM_KEYWORD*)0},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg38[]  = { 
	{{_NUMBER|_KEYWORD|_FLOAT},	_SEC,	(PARAM_KEYWORD*)& _kg24},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg39[]  = { 
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg40[]  = { 
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg41[]  = { 
	{{_KEYWORD|_OPTION},	0,	(PARAM_KEYWORD*)& _kg25},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg42[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg26},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg43[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg27},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg44[]  = { 
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_STRING1},	0,	(PARAM_KEYWORD*)0},
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg28},
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg29},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg30},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg45[]  = { 
	{{_STRING1},	0,	(PARAM_KEYWORD*)0},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg46[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg28},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg47[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg29},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg48[]  = { 
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg30},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg49[]  = { 
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg24},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg50[]  = { 
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg51[]  = { 
	{{_STRING1},	0,	(PARAM_KEYWORD*)0},
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg31},
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg29},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg30},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg52[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg31},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg53[]  = { 
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg54[]  = { 
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg55[]  = { 
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg32},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg56[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg32},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg57[]  = { 
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg33},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg58[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg34},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg59[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg35},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg60[]  = { 
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg61[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg36},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg62[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg37},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg63[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg38},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg64[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg39},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg65[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg66[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg40},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg67[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg41},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg68[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg42},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg69[]  = { 
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg70[]  = { 
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg71[]  = { 
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg1},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg72[]  = { 
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg73[]  = { 
	{{_NUMBER},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg74[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg43},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg75[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg44},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg76[]  = { 
	{{_KEYWORD},	0,	(PARAM_KEYWORD*)& _kg45},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

const	PARAM_ITEM _pg77[]  = { 
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{_NUMBER|_FLOAT},	0,	(PARAM_KEYWORD*)0},
	{{0},	0,	(PARAM_KEYWORD*)0}
};

//------------------------------------------------------------------
// Suffix Group
const COMD_SUFFIX _cp1= {1, 2};

