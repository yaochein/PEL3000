#include "scpiStruct.h"
#include "scpiID.h"
#include "scpiKeyword.h"
#include "scpiNode.h"


//Declare SonNodes
const NODES _sonCommon[];
const NODES _sonRoot[];
const NODES _sonSYSTem[];
const NODES _sonSYSTemERRor[];
const NODES _sonINPut[];
const NODES _sonINPutSTATe[];
const NODES _sonOUTPut[];
const NODES _sonOUTPutSTATe[];
const NODES _sonINITiate[];
const NODES _sonCURRent[];
const NODES _sonCURRentLEVel[];
const NODES _sonCURRentLEVelVA[];
const NODES _sonCURRentLEVelVATRIGgered[];
const NODES _sonSOURce[];
const NODES _sonSOURceCURRent[];
const NODES _sonSOURceCURRentLEVel[];
const NODES _sonSOURceCURRentLEVelVA[];
const NODES _sonSOURceCURRentLEVelVATRIGgered[];
const NODES _sonSOURceCURRentVA[];
const NODES _sonSOURceCURRentVATRIGgered[];
const NODES _sonCURRentVA[];
const NODES _sonCURRentVATRIGgered[];
const NODES _sonSOURceCURRentLEVelTRIGgered[];
const NODES _sonCURRentLEVelTRIGgered[];
const NODES _sonSOURceCURRentTRIGgered[];
const NODES _sonCURRentTRIGgered[];
const NODES _sonRESistance[];
const NODES _sonRESistanceVA[];
const NODES _sonCONDuctance[];
const NODES _sonCONDuctanceVA[];
const NODES _sonCONDuctanceVATRIGgered[];
const NODES _sonSOURceCONDuctance[];
const NODES _sonSOURceCONDuctanceVA[];
const NODES _sonSOURceCONDuctanceVATRIGgered[];
const NODES _sonSOURceCONDuctanceTRIGgered[];
const NODES _sonCONDuctanceTRIGgered[];
const NODES _sonTRIGger[];
const NODES _sonTRIGgerDELay[];
const NODES _sonTRIGgerPULSe[];
const NODES _sonSHORt[];
const NODES _sonINPutSHORt[];
const NODES _sonOUTPup[];
const NODES _sonOUTPupSHORt[];
const NODES _sonINPutPROTection[];
const NODES _sonOUTPutPROTection[];
const NODES _sonINPutSTATeTIMer[];
const NODES _sonINPutTIMer[];
const NODES _sonOUTPutSTATeTIMer[];
const NODES _sonOUTPutTIMer[];
const NODES _sonMEASure[];
const NODES _sonMEASureSCALar[];
const NODES _sonMEASureSCALarCURRent[];
const NODES _sonMEASureCURRent[];
const NODES _sonMEASureSCALarVOLTage[];
const NODES _sonMEASureVOLTage[];
const NODES _sonMEASureSCALarPOWer[];
const NODES _sonMEASurePOWer[];
const NODES _sonFETCh[];
const NODES _sonCONFigure[];
const NODES _sonUVP[];
const NODES _sonCONFigureUVP[];
const NODES _sonCONFigureSHORt[];
const NODES _sonGNG[];
const NODES _sonCONFigureGNG[];
const NODES _sonSTEP[];
const NODES _sonCONFigureSTEP[];
const NODES _sonEXTernal[];
const NODES _sonCONFigureEXTernal[];
const NODES _sonMODE[];
const NODES _sonCURRentCV[];
const NODES _sonRESistanceCV[];
const NODES _sonVOLTage[];
const NODES _sonPOWer[];
const NODES _sonPOWerCV[];
const NODES _sonFUNCtion[];
const NODES _sonFUNCtionCOMPlete[];
const NODES _sonFUNCtionCOMPleteRING[];
const NODES _sonFUNCtionRING[];
const NODES _sonPROGram[];
const NODES _sonPROGramRECall[];
const NODES _sonCHAin[];
const NODES _sonPROGramCHAin[];
const NODES _sonCHAinRECall[];
const NODES _sonPROGramCHAinRECall[];
const NODES _sonSEQuence[];
const NODES _sonSEQuenceCOMPlete[];
const NODES _sonSEQuenceCOMPleteRING[];
const NODES _sonSEQuenceRING[];
const NODES _sonNSEQuence[];
const NODES _sonNSEQuenceEDIT[];
const NODES _sonNSEQuenceDELet[];
const NODES _sonFSEQuence[];
const NODES _sonFSEQuenceEDIT[];
const NODES _sonFSEQuenceDELet[];
const NODES _sonOCP[];
const NODES _sonOCPEDIT[];
const NODES _sonOCPCHANnel[];
const NODES _sonOCPCHANnelSTEP[];
const NODES _sonOCPSTEP[];
const NODES _sonUTILity[];
const NODES _sonUTILityREMote[];
const NODES _sonUTILityLOAD[];
const NODES _sonMEMory[];
const NODES _sonPRESet[];
const NODES _sonSETup[];
const NODES _sonFACTory[];
const NODES _sonUSER[];
const NODES _sonUSERDEFault[];
const NODES _sonSERial[];
const NODES _sonSTATus[];
const NODES _sonSTATusQUEStionable[];
const NODES _sonSTATusOPERation[];
const NODES _sonSTATusCSUMmary[];
const NODES _sonSYNC[];
const NODES _sonSYNCDEFault[];
const NODES _sonCURRentPROTection[];
const NODES _sonCURRentPROTectionLEVel[];
const NODES _sonSOURceCURRentPROTection[];
const NODES _sonSOURceCURRentPROTectionLEVel[];
const NODES _sonCURRentLEVelIMMediate[];
const NODES _sonSOURceCURRentLEVelIMMediate[];
const NODES _sonSOURceCURRentIMMediate[];
const NODES _sonCURRentIMMediate[];
const NODES _sonPOWerPROTection[];
const NODES _sonPOWerPROTectionLEVel[];
const NODES _sonSOURcePOWer[];
const NODES _sonSOURcePOWerPROTection[];
const NODES _sonSOURcePOWerPROTectionLEVel[];
const NODES _sonPOWerLEVel[];
const NODES _sonPOWerLEVelIMMediate[];
const NODES _sonSOURcePOWerLEVel[];
const NODES _sonSOURcePOWerLEVelIMMediate[];
const NODES _sonSOURcePOWerIMMediate[];
const NODES _sonPOWerIMMediate[];
const NODES _sonCONDuctanceLEVel[];
const NODES _sonCONDuctanceLEVelIMMediate[];
const NODES _sonSOURceCONDuctanceLEVel[];
const NODES _sonSOURceCONDuctanceLEVelIMMediate[];
const NODES _sonSOURceCONDuctanceIMMediate[];
const NODES _sonCONDuctanceIMMediate[];
const NODES _sonVOLTagePROTection[];
const NODES _sonVOLTagePROTectionLEVel[];
const NODES _sonSOURceVOLTage[];
const NODES _sonSOURceVOLTagePROTection[];
const NODES _sonSOURceVOLTagePROTectionLEVel[];
const NODES _sonVOLTageLEVel[];
const NODES _sonVOLTageLEVelIMMediate[];
const NODES _sonSOURceVOLTageLEVel[];
const NODES _sonSOURceVOLTageLEVelIMMediate[];
const NODES _sonSOURceVOLTageIMMediate[];
const NODES _sonVOLTageIMMediate[];
const NODES _sonSOURceFUNCtion[];
const NODES _sonSELected[];
const NODES _sonPROGramSELected[];
const NODES _sonPROGramSELectedNSPeed[];
const NODES _sonPROGramSELectedNSPeedSTEP[];
const NODES _sonPROGramNSPeed[];
const NODES _sonPROGramNSPeedSTEP[];
const NODES _sonPROGramSELectedNSPeedSTEPDELete[];
const NODES _sonPROGramNSPeedSTEPDELete[];
const NODES _sonPROGramSELectedNSPeedDELete[];
const NODES _sonPROGramNSPeedDELete[];
const NODES _sonPROGramSELectedFSPeed[];
const NODES _sonPROGramSELectedFSPeedSTEP[];
const NODES _sonPROGramFSPeed[];
const NODES _sonPROGramFSPeedSTEP[];
const NODES _sonPROGramSELectedFSPeedSTEPEDIT[];
const NODES _sonPROGramFSPeedSTEPEDIT[];
const NODES _sonPROGramSELectedFSPeedEDIT[];
const NODES _sonPROGramFSPeedEDIT[];
const NODES _sonCALibrate[];


//Create Root Node
const COMD_SUFFIX _cpNull = {-1, -1};
//-----------------------------------------------------------------------------
//--- NODE DATA ---------------------------------------------------------------
//                       parant node   son nodes           name             COMD_SUFFIX          type          id
const NODE _nodeCommon ={(NODES) 0  ,(NODES*)_sonCommon ,(COMD_WORD*) 0 ,(COMD_SUFFIX*)&_cpNull ,(char)T____ ,(unsigned int)0          };
const NODE _nodeRoot   ={(NODES) 0  ,(NODES*)_sonRoot   ,(COMD_WORD*) 0 ,(COMD_SUFFIX*)&_cpNull ,(char)T____ ,(unsigned int)0          };


//Create Common Nodes
const NODE _node_CAL ={(NODES)&_nodeRoot ,(NODES*)0   ,(COMD_WORD*)&_kw_CAL,(COMD_SUFFIX*)&_cpNull ,(char)T___S,(unsigned int) _id_CAL };
const NODE _node_CLS ={(NODES)&_nodeRoot ,(NODES*)0   ,(COMD_WORD*)&_kw_CLS,(COMD_SUFFIX*)&_cpNull ,(char)T___S,(unsigned int) _id_CLS };
const NODE _node_ESE ={(NODES)&_nodeRoot ,(NODES*)0   ,(COMD_WORD*)&_kw_ESE,(COMD_SUFFIX*)&_cpNull ,(char)T__QS,(unsigned int) _id_ESE };
const NODE _node_ESR ={(NODES)&_nodeRoot ,(NODES*)0   ,(COMD_WORD*)&_kw_ESR,(COMD_SUFFIX*)&_cpNull ,(char)T__Q_,(unsigned int) _id_ESR };
const NODE _node_IDN ={(NODES)&_nodeRoot ,(NODES*)0   ,(COMD_WORD*)&_kw_IDN,(COMD_SUFFIX*)&_cpNull ,(char)T__Q_,(unsigned int) _id_IDN };
const NODE _node_OPC ={(NODES)&_nodeRoot ,(NODES*)0   ,(COMD_WORD*)&_kw_OPC,(COMD_SUFFIX*)&_cpNull ,(char)T__Q_,(unsigned int) _id_OPC };
const NODE _node_RCL ={(NODES)&_nodeRoot ,(NODES*)0   ,(COMD_WORD*)&_kw_RCL,(COMD_SUFFIX*)&_cpNull ,(char)T___S,(unsigned int) _id_RCL };
const NODE _node_RST ={(NODES)&_nodeRoot ,(NODES*)0   ,(COMD_WORD*)&_kw_RST,(COMD_SUFFIX*)&_cpNull ,(char)T___S,(unsigned int) _id_RST };
const NODE _node_SAV ={(NODES)&_nodeRoot ,(NODES*)0   ,(COMD_WORD*)&_kw_SAV,(COMD_SUFFIX*)&_cpNull ,(char)T___S,(unsigned int) _id_SAV };
const NODE _node_SRE ={(NODES)&_nodeRoot ,(NODES*)0   ,(COMD_WORD*)&_kw_SRE,(COMD_SUFFIX*)&_cpNull ,(char)T__QS,(unsigned int) _id_SRE };
const NODE _node_STB ={(NODES)&_nodeRoot ,(NODES*)0   ,(COMD_WORD*)&_kw_STB,(COMD_SUFFIX*)&_cpNull ,(char)T__Q_,(unsigned int) _id_STB };
const NODE _node_TRG ={(NODES)&_nodeRoot ,(NODES*)0   ,(COMD_WORD*)&_kw_TRG,(COMD_SUFFIX*)&_cpNull ,(char)T___S,(unsigned int) _id_TRG };
const NODE _node_TST ={(NODES)&_nodeRoot ,(NODES*)0   ,(COMD_WORD*)&_kw_TST,(COMD_SUFFIX*)&_cpNull ,(char)T__Q_,(unsigned int) _id_TST };
const NODE _node_WAI ={(NODES)&_nodeRoot ,(NODES*)0   ,(COMD_WORD*)&_kw_WAI,(COMD_SUFFIX*)&_cpNull ,(char)T___S,(unsigned int) _id_WAI };


const NODES _sonCommon[]={
(NODES)&_node_CAL,(NODES)&_node_CLS,(NODES)&_node_ESE,(NODES)&_node_ESR,(NODES)&_node_IDN,
(NODES)&_node_OPC,(NODES)&_node_RCL,(NODES)&_node_RST,(NODES)&_node_SAV,(NODES)&_node_SRE,
(NODES)&_node_STB,(NODES)&_node_TRG,(NODES)&_node_TST,(NODES)&_node_WAI,(NODES) 0 };


//Create Special Nodes
const NODE _nodeABORt={
(NODES)&_nodeRoot ,(NODES*)0,(COMD_WORD*)&_kwABORt
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idABORt};

const NODE _nodeSYSTem={
(NODES)&_nodeRoot ,(NODES*)_sonSYSTem,(COMD_WORD*)&_kwSYSTem
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeSYSTemERRor={
(NODES)&_nodeSYSTem ,(NODES*)_sonSYSTemERRor,(COMD_WORD*)&_kwERRor
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idSYSTemERRorNEXT};

const NODE _nodeSYSTemERRorNEXT={
(NODES)&_nodeSYSTemERRor ,(NODES*)0,(COMD_WORD*)&_kwNEXT
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idSYSTemERRorNEXT};

const NODE _nodeINPut={
(NODES)&_nodeRoot ,(NODES*)_sonINPut,(COMD_WORD*)&_kwINPut
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idINPutSTATeIMMediate};

const NODE _nodeINPutSTATe={
(NODES)&_nodeINPut ,(NODES*)_sonINPutSTATe,(COMD_WORD*)&_kwSTATe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idINPutSTATeIMMediate};

const NODE _nodeINPutSTATeTRIGgered={
(NODES)&_nodeINPutSTATe ,(NODES*)0,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idINPutSTATeTRIGgered};

const NODE _nodeINPutTRIGgered={
(NODES)&_nodeINPut ,(NODES*)0,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idINPutSTATeTRIGgered};

const NODE _nodeOUTPut={
(NODES)&_nodeRoot ,(NODES*)_sonOUTPut,(COMD_WORD*)&_kwOUTPut
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOUTPutSTATeIMMediate};

const NODE _nodeOUTPutSTATe={
(NODES)&_nodeOUTPut ,(NODES*)_sonOUTPutSTATe,(COMD_WORD*)&_kwSTATe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOUTPutSTATeIMMediate};

const NODE _nodeOUTPutSTATeTRIGgered={
(NODES)&_nodeOUTPutSTATe ,(NODES*)0,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idOUTPutSTATeTRIGgered};

const NODE _nodeOUTPutTRIGgered={
(NODES)&_nodeOUTPut ,(NODES*)0,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idOUTPutSTATeTRIGgered};

const NODE _nodeINITiate={
(NODES)&_nodeRoot ,(NODES*)_sonINITiate,(COMD_WORD*)&_kwINITiate
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idINITiateIMMediate};

const NODE _nodeINITiateIMMediate={
(NODES)&_nodeINITiate ,(NODES*)0,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idINITiateIMMediate};

const NODE _nodeINITiateCONTinuous={
(NODES)&_nodeINITiate ,(NODES*)0,(COMD_WORD*)&_kwCONTinuous
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idINITiateCONTinuous};

const NODE _nodeCURRent={
(NODES)&_nodeRoot ,(NODES*)_sonCURRent,(COMD_WORD*)&_kwCURRent
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCURRentVA};

const NODE _nodeCURRentLEVel={
(NODES)&_nodeCURRent ,(NODES*)_sonCURRentLEVel,(COMD_WORD*)&_kwLEVel
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCURRentLEVel};

const NODE _nodeCURRentLEVelVA={
(NODES)&_nodeCURRentLEVel ,(NODES*)_sonCURRentLEVelVA,(COMD_WORD*)&_kwVA
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeCURRentLEVelVATRIGgered={
(NODES)&_nodeCURRentLEVelVA ,(NODES*)_sonCURRentLEVelVATRIGgered,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCURRentLEVelVATRIGgeredAMPLitude};

const NODE _nodeCURRentLEVelVATRIGgeredAMPLitude={
(NODES)&_nodeCURRentLEVelVATRIGgered ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCURRentLEVelVATRIGgeredAMPLitude};

const NODE _nodeSOURce={
(NODES)&_nodeRoot ,(NODES*)_sonSOURce,(COMD_WORD*)&_kwSOURce
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeSOURceCURRent={
(NODES)&_nodeSOURce ,(NODES*)_sonSOURceCURRent,(COMD_WORD*)&_kwCURRent
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentLEVelIMMediateAMPLitude};

const NODE _nodeSOURceCURRentLEVel={
(NODES)&_nodeSOURceCURRent ,(NODES*)_sonSOURceCURRentLEVel,(COMD_WORD*)&_kwLEVel
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentLEVelIMMediateAMPLitude};

const NODE _nodeSOURceCURRentLEVelVA={
(NODES)&_nodeSOURceCURRentLEVel ,(NODES*)_sonSOURceCURRentLEVelVA,(COMD_WORD*)&_kwVA
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeSOURceCURRentLEVelVATRIGgered={
(NODES)&_nodeSOURceCURRentLEVelVA ,(NODES*)_sonSOURceCURRentLEVelVATRIGgered,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCURRentLEVelVATRIGgeredAMPLitude};

const NODE _nodeSOURceCURRentLEVelVATRIGgeredAMPLitude={
(NODES)&_nodeSOURceCURRentLEVelVATRIGgered ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCURRentLEVelVATRIGgeredAMPLitude};

const NODE _nodeSOURceCURRentVA={
(NODES)&_nodeSOURceCURRent ,(NODES*)_sonSOURceCURRentVA,(COMD_WORD*)&_kwVA
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeSOURceCURRentVATRIGgered={
(NODES)&_nodeSOURceCURRentVA ,(NODES*)_sonSOURceCURRentVATRIGgered,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCURRentLEVelVATRIGgeredAMPLitude};

const NODE _nodeSOURceCURRentVATRIGgeredAMPLitude={
(NODES)&_nodeSOURceCURRentVATRIGgered ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCURRentLEVelVATRIGgeredAMPLitude};

const NODE _nodeCURRentVA={
(NODES)&_nodeCURRent ,(NODES*)_sonCURRentVA,(COMD_WORD*)&_kwVA
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCURRentVA};

const NODE _nodeCURRentVATRIGgered={
(NODES)&_nodeCURRentVA ,(NODES*)_sonCURRentVATRIGgered,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCURRentLEVelVATRIGgeredAMPLitude};

const NODE _nodeCURRentVATRIGgeredAMPLitude={
(NODES)&_nodeCURRentVATRIGgered ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCURRentLEVelVATRIGgeredAMPLitude};

const NODE _nodeSOURceCURRentLEVelTRIGgered={
(NODES)&_nodeSOURceCURRentLEVel ,(NODES*)_sonSOURceCURRentLEVelTRIGgered,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCURRentLEVelVATRIGgeredAMPLitude};

const NODE _nodeSOURceCURRentLEVelTRIGgeredAMPLitude={
(NODES)&_nodeSOURceCURRentLEVelTRIGgered ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCURRentLEVelVATRIGgeredAMPLitude};

const NODE _nodeCURRentLEVelTRIGgered={
(NODES)&_nodeCURRentLEVel ,(NODES*)_sonCURRentLEVelTRIGgered,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCURRentLEVelVATRIGgeredAMPLitude};

const NODE _nodeCURRentLEVelTRIGgeredAMPLitude={
(NODES)&_nodeCURRentLEVelTRIGgered ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCURRentLEVelVATRIGgeredAMPLitude};

const NODE _nodeSOURceCURRentTRIGgered={
(NODES)&_nodeSOURceCURRent ,(NODES*)_sonSOURceCURRentTRIGgered,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCURRentLEVelVATRIGgeredAMPLitude};

const NODE _nodeSOURceCURRentTRIGgeredAMPLitude={
(NODES)&_nodeSOURceCURRentTRIGgered ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCURRentLEVelVATRIGgeredAMPLitude};

const NODE _nodeCURRentTRIGgered={
(NODES)&_nodeCURRent ,(NODES*)_sonCURRentTRIGgered,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCURRentLEVelVATRIGgeredAMPLitude};

const NODE _nodeCURRentTRIGgeredAMPLitude={
(NODES)&_nodeCURRentTRIGgered ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCURRentLEVelVATRIGgeredAMPLitude};

const NODE _nodeRESistance={
(NODES)&_nodeRoot ,(NODES*)_sonRESistance,(COMD_WORD*)&_kwRESistance
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idRESistanceVA};

const NODE _nodeRESistanceVA={
(NODES)&_nodeRESistance ,(NODES*)_sonRESistanceVA,(COMD_WORD*)&_kwVA
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idRESistanceVA};

const NODE _nodeRESistanceVATRIGgered={
(NODES)&_nodeRESistanceVA ,(NODES*)0,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idRESistanceVATRIGgered};

const NODE _nodeRESistanceTRIGgered={
(NODES)&_nodeRESistance ,(NODES*)0,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idRESistanceVATRIGgered};

const NODE _nodeCONDuctance={
(NODES)&_nodeRoot ,(NODES*)_sonCONDuctance,(COMD_WORD*)&_kwCONDuctance
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONDuctanceVA};

const NODE _nodeCONDuctanceVA={
(NODES)&_nodeCONDuctance ,(NODES*)_sonCONDuctanceVA,(COMD_WORD*)&_kwVA
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONDuctanceVA};

const NODE _nodeCONDuctanceVATRIGgered={
(NODES)&_nodeCONDuctanceVA ,(NODES*)_sonCONDuctanceVATRIGgered,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCONDuctanceVATRIGgeredAMPLitude};

const NODE _nodeCONDuctanceVATRIGgeredAMPLitude={
(NODES)&_nodeCONDuctanceVATRIGgered ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCONDuctanceVATRIGgeredAMPLitude};

const NODE _nodeSOURceCONDuctance={
(NODES)&_nodeSOURce ,(NODES*)_sonSOURceCONDuctance,(COMD_WORD*)&_kwCONDuctance
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCONDuctanceLEVelIMMediateAMPLitude};

const NODE _nodeSOURceCONDuctanceVA={
(NODES)&_nodeSOURceCONDuctance ,(NODES*)_sonSOURceCONDuctanceVA,(COMD_WORD*)&_kwVA
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeSOURceCONDuctanceVATRIGgered={
(NODES)&_nodeSOURceCONDuctanceVA ,(NODES*)_sonSOURceCONDuctanceVATRIGgered,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCONDuctanceVATRIGgeredAMPLitude};

const NODE _nodeSOURceCONDuctanceVATRIGgeredAMPLitude={
(NODES)&_nodeSOURceCONDuctanceVATRIGgered ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCONDuctanceVATRIGgeredAMPLitude};

const NODE _nodeSOURceCONDuctanceTRIGgered={
(NODES)&_nodeSOURceCONDuctance ,(NODES*)_sonSOURceCONDuctanceTRIGgered,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCONDuctanceVATRIGgeredAMPLitude};

const NODE _nodeSOURceCONDuctanceTRIGgeredAMPLitude={
(NODES)&_nodeSOURceCONDuctanceTRIGgered ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCONDuctanceVATRIGgeredAMPLitude};

const NODE _nodeCONDuctanceTRIGgered={
(NODES)&_nodeCONDuctance ,(NODES*)_sonCONDuctanceTRIGgered,(COMD_WORD*)&_kwTRIGgered
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCONDuctanceVATRIGgeredAMPLitude};

const NODE _nodeCONDuctanceTRIGgeredAMPLitude={
(NODES)&_nodeCONDuctanceTRIGgered ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceCONDuctanceVATRIGgeredAMPLitude};

const NODE _nodeTRIGger={
(NODES)&_nodeRoot ,(NODES*)_sonTRIGger,(COMD_WORD*)&_kwTRIGger
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeTRIGgerDELay={
(NODES)&_nodeTRIGger ,(NODES*)_sonTRIGgerDELay,(COMD_WORD*)&_kwDELay
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeTRIGgerDELayTIME={
(NODES)&_nodeTRIGgerDELay ,(NODES*)0,(COMD_WORD*)&_kwTIME
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idTRIGgerDELayTIME};

const NODE _nodeTRIGgerTIME={
(NODES)&_nodeTRIGger ,(NODES*)0,(COMD_WORD*)&_kwTIME
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idTRIGgerDELayTIME};

const NODE _nodeTRIGgerPULSe={
(NODES)&_nodeTRIGger ,(NODES*)_sonTRIGgerPULSe,(COMD_WORD*)&_kwPULSe
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeTRIGgerPULSeWIDTh={
(NODES)&_nodeTRIGgerPULSe ,(NODES*)0,(COMD_WORD*)&_kwWIDTh
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idTRIGgerPULSeWIDTh};

const NODE _nodeTRIGgerWIDTh={
(NODES)&_nodeTRIGger ,(NODES*)0,(COMD_WORD*)&_kwWIDTh
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idTRIGgerPULSeWIDTh};

const NODE _nodeINPutSTATeIMMediate={
(NODES)&_nodeINPutSTATe ,(NODES*)0,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idINPutSTATeIMMediate};

const NODE _nodeINPutIMMediate={
(NODES)&_nodeINPut ,(NODES*)0,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idINPutSTATeIMMediate};

const NODE _nodeOUTPutSTATeIMMediate={
(NODES)&_nodeOUTPutSTATe ,(NODES*)0,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOUTPutSTATeIMMediate};

const NODE _nodeOUTPutIMMediate={
(NODES)&_nodeOUTPut ,(NODES*)0,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOUTPutSTATeIMMediate};

const NODE _nodeSHORt={
(NODES)&_nodeRoot ,(NODES*)_sonSHORt,(COMD_WORD*)&_kwSHORt
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idINPutSHORtSTATe};

const NODE _nodeSHORtSTATe={
(NODES)&_nodeSHORt ,(NODES*)0,(COMD_WORD*)&_kwSTATe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idINPutSHORtSTATe};

const NODE _nodeINPutSHORt={
(NODES)&_nodeINPut ,(NODES*)_sonINPutSHORt,(COMD_WORD*)&_kwSHORt
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idINPutSHORtSTATe};

const NODE _nodeINPutSHORtSTATe={
(NODES)&_nodeINPutSHORt ,(NODES*)0,(COMD_WORD*)&_kwSTATe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idINPutSHORtSTATe};

const NODE _nodeOUTPup={
(NODES)&_nodeRoot ,(NODES*)_sonOUTPup,(COMD_WORD*)&_kwOUTPup
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeOUTPupSHORt={
(NODES)&_nodeOUTPup ,(NODES*)_sonOUTPupSHORt,(COMD_WORD*)&_kwSHORt
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOUTPupSHORtSTATe};

const NODE _nodeOUTPupSHORtSTATe={
(NODES)&_nodeOUTPupSHORt ,(NODES*)0,(COMD_WORD*)&_kwSTATe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOUTPupSHORtSTATe};

const NODE _nodeINPutPROTection={
(NODES)&_nodeINPut ,(NODES*)_sonINPutPROTection,(COMD_WORD*)&_kwPROTection
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeINPutPROTectionCLEar={
(NODES)&_nodeINPutPROTection ,(NODES*)0,(COMD_WORD*)&_kwCLEar
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idINPutPROTectionCLEar};

const NODE _nodeOUTPutPROTection={
(NODES)&_nodeOUTPut ,(NODES*)_sonOUTPutPROTection,(COMD_WORD*)&_kwPROTection
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeOUTPutPROTectionCLEar={
(NODES)&_nodeOUTPutPROTection ,(NODES*)0,(COMD_WORD*)&_kwCLEar
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idOUTPutPROTectionCLEar};

const NODE _nodeINPutSTATeTIMer={
(NODES)&_nodeINPutSTATe ,(NODES*)_sonINPutSTATeTIMer,(COMD_WORD*)&_kwTIMer
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idINPutSTATeTIMerSTATe};

const NODE _nodeINPutSTATeTIMerSTATe={
(NODES)&_nodeINPutSTATeTIMer ,(NODES*)0,(COMD_WORD*)&_kwSTATe
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idINPutSTATeTIMerSTATe};

const NODE _nodeINPutTIMer={
(NODES)&_nodeINPut ,(NODES*)_sonINPutTIMer,(COMD_WORD*)&_kwTIMer
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idINPutSTATeTIMerSTATe};

const NODE _nodeINPutTIMerSTATe={
(NODES)&_nodeINPutTIMer ,(NODES*)0,(COMD_WORD*)&_kwSTATe
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idINPutSTATeTIMerSTATe};

const NODE _nodeOUTPutSTATeTIMer={
(NODES)&_nodeOUTPutSTATe ,(NODES*)_sonOUTPutSTATeTIMer,(COMD_WORD*)&_kwTIMer
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idOUTPutSTATeTIMerSTATe};

const NODE _nodeOUTPutSTATeTIMerSTATe={
(NODES)&_nodeOUTPutSTATeTIMer ,(NODES*)0,(COMD_WORD*)&_kwSTATe
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idOUTPutSTATeTIMerSTATe};

const NODE _nodeOUTPutTIMer={
(NODES)&_nodeOUTPut ,(NODES*)_sonOUTPutTIMer,(COMD_WORD*)&_kwTIMer
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idOUTPutSTATeTIMerSTATe};

const NODE _nodeOUTPutTIMerSTATe={
(NODES)&_nodeOUTPutTIMer ,(NODES*)0,(COMD_WORD*)&_kwSTATe
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idOUTPutSTATeTIMerSTATe};

const NODE _nodeINPutMODE={
(NODES)&_nodeINPut ,(NODES*)0,(COMD_WORD*)&_kwMODE
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idINPutMODE};

const NODE _nodeMEASure={
(NODES)&_nodeRoot ,(NODES*)_sonMEASure,(COMD_WORD*)&_kwMEASure
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeMEASureSCALar={
(NODES)&_nodeMEASure ,(NODES*)_sonMEASureSCALar,(COMD_WORD*)&_kwSCALar
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeMEASureSCALarCURRent={
(NODES)&_nodeMEASureSCALar ,(NODES*)_sonMEASureSCALarCURRent,(COMD_WORD*)&_kwCURRent
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idMEASureSCALarCURRentDC};

const NODE _nodeMEASureSCALarCURRentDC={
(NODES)&_nodeMEASureSCALarCURRent ,(NODES*)0,(COMD_WORD*)&_kwDC
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idMEASureSCALarCURRentDC};

const NODE _nodeMEASureCURRent={
(NODES)&_nodeMEASure ,(NODES*)_sonMEASureCURRent,(COMD_WORD*)&_kwCURRent
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idMEASureSCALarCURRentDC};

const NODE _nodeMEASureCURRentDC={
(NODES)&_nodeMEASureCURRent ,(NODES*)0,(COMD_WORD*)&_kwDC
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idMEASureSCALarCURRentDC};

const NODE _nodeMEASureSCALarVOLTage={
(NODES)&_nodeMEASureSCALar ,(NODES*)_sonMEASureSCALarVOLTage,(COMD_WORD*)&_kwVOLTage
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idMEASureSCALarVOLTageDC};

const NODE _nodeMEASureSCALarVOLTageDC={
(NODES)&_nodeMEASureSCALarVOLTage ,(NODES*)0,(COMD_WORD*)&_kwDC
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idMEASureSCALarVOLTageDC};

const NODE _nodeMEASureVOLTage={
(NODES)&_nodeMEASure ,(NODES*)_sonMEASureVOLTage,(COMD_WORD*)&_kwVOLTage
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idMEASureSCALarVOLTageDC};

const NODE _nodeMEASureVOLTageDC={
(NODES)&_nodeMEASureVOLTage ,(NODES*)0,(COMD_WORD*)&_kwDC
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idMEASureSCALarVOLTageDC};

const NODE _nodeMEASureSCALarPOWer={
(NODES)&_nodeMEASureSCALar ,(NODES*)_sonMEASureSCALarPOWer,(COMD_WORD*)&_kwPOWer
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idMEASureSCALarPOWerDC};

const NODE _nodeMEASureSCALarPOWerDC={
(NODES)&_nodeMEASureSCALarPOWer ,(NODES*)0,(COMD_WORD*)&_kwDC
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idMEASureSCALarPOWerDC};

const NODE _nodeMEASurePOWer={
(NODES)&_nodeMEASure ,(NODES*)_sonMEASurePOWer,(COMD_WORD*)&_kwPOWer
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idMEASureSCALarPOWerDC};

const NODE _nodeMEASurePOWerDC={
(NODES)&_nodeMEASurePOWer ,(NODES*)0,(COMD_WORD*)&_kwDC
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idMEASureSCALarPOWerDC};

const NODE _nodeMEASureSCALarETIMe={
(NODES)&_nodeMEASureSCALar ,(NODES*)0,(COMD_WORD*)&_kwETIMe
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idMEASureSCALarETIMe};

const NODE _nodeMEASureETIMe={
(NODES)&_nodeMEASure ,(NODES*)0,(COMD_WORD*)&_kwETIMe
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idMEASureSCALarETIMe};

const NODE _nodeFETCh={
(NODES)&_nodeRoot ,(NODES*)_sonFETCh,(COMD_WORD*)&_kwFETCh
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeFETChCURRent={
(NODES)&_nodeFETCh ,(NODES*)0,(COMD_WORD*)&_kwCURRent
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idFETChCURRent};

const NODE _nodeFETChVOLTage={
(NODES)&_nodeFETCh ,(NODES*)0,(COMD_WORD*)&_kwVOLTage
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idFETChVOLTage};

const NODE _nodeFETChPOWer={
(NODES)&_nodeFETCh ,(NODES*)0,(COMD_WORD*)&_kwPOWer
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idFETChPOWer};

const NODE _nodeOCP={
(NODES)&_nodeRoot ,(NODES*)_sonOCP,(COMD_WORD*)&_kwOCP
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureOCP};

const NODE _nodeCONFigure={
(NODES)&_nodeRoot ,(NODES*)_sonCONFigure,(COMD_WORD*)&_kwCONFigure
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeCONFigureOCP={
(NODES)&_nodeCONFigure ,(NODES*)0,(COMD_WORD*)&_kwOCP
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureOCP};

const NODE _nodeOPP={
(NODES)&_nodeRoot ,(NODES*)0,(COMD_WORD*)&_kwOPP
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureOPP};

const NODE _nodeCONFigureOPP={
(NODES)&_nodeCONFigure ,(NODES*)0,(COMD_WORD*)&_kwOPP
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureOPP};

const NODE _nodeUVP={
(NODES)&_nodeRoot ,(NODES*)_sonUVP,(COMD_WORD*)&_kwUVP
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureUVP};

const NODE _nodeCONFigureUVP={
(NODES)&_nodeCONFigure ,(NODES*)_sonCONFigureUVP,(COMD_WORD*)&_kwUVP
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureUVP};

const NODE _nodeUVPTIME={
(NODES)&_nodeUVP ,(NODES*)0,(COMD_WORD*)&_kwTIME
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureUVPTIME};

const NODE _nodeCONFigureUVPTIME={
(NODES)&_nodeCONFigureUVP ,(NODES*)0,(COMD_WORD*)&_kwTIME
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureUVPTIME};

const NODE _nodeOVP={
(NODES)&_nodeRoot ,(NODES*)0,(COMD_WORD*)&_kwOVP
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureOVP};

const NODE _nodeCONFigureOVP={
(NODES)&_nodeCONFigure ,(NODES*)0,(COMD_WORD*)&_kwOVP
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureOVP};

const NODE _nodeSSTart={
(NODES)&_nodeRoot ,(NODES*)0,(COMD_WORD*)&_kwSSTart
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSSTart};

const NODE _nodeCONFigureSSTart={
(NODES)&_nodeCONFigure ,(NODES*)0,(COMD_WORD*)&_kwSSTart
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSSTart};

const NODE _nodeVON={
(NODES)&_nodeRoot ,(NODES*)0,(COMD_WORD*)&_kwVON
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureVON};

const NODE _nodeCONFigureVON={
(NODES)&_nodeCONFigure ,(NODES*)0,(COMD_WORD*)&_kwVON
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureVON};

const NODE _nodeVDELay={
(NODES)&_nodeRoot ,(NODES*)0,(COMD_WORD*)&_kwVDELay
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureVDELay};

const NODE _nodeCONFigureVDELay={
(NODES)&_nodeCONFigure ,(NODES*)0,(COMD_WORD*)&_kwVDELay
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureVDELay};

const NODE _nodeCONFigureRESPonse={
(NODES)&_nodeCONFigure ,(NODES*)0,(COMD_WORD*)&_kwRESPonse
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureRESPonse};

const NODE _nodeCNTime={
(NODES)&_nodeRoot ,(NODES*)0,(COMD_WORD*)&_kwCNTime
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureCNTime};

const NODE _nodeCONFigureCNTime={
(NODES)&_nodeCONFigure ,(NODES*)0,(COMD_WORD*)&_kwCNTime
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureCNTime};

const NODE _nodeCOTime={
(NODES)&_nodeRoot ,(NODES*)0,(COMD_WORD*)&_kwCOTime
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureCOTime};

const NODE _nodeCONFigureCOTime={
(NODES)&_nodeCONFigure ,(NODES*)0,(COMD_WORD*)&_kwCOTime
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureCOTime};

const NODE _nodeCRUNit={
(NODES)&_nodeRoot ,(NODES*)0,(COMD_WORD*)&_kwCRUNit
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureCRUNit};

const NODE _nodeCONFigureCRUNit={
(NODES)&_nodeCONFigure ,(NODES*)0,(COMD_WORD*)&_kwCRUNit
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureCRUNit};

const NODE _nodeCONFigureDYNamic={
(NODES)&_nodeCONFigure ,(NODES*)0,(COMD_WORD*)&_kwDYNamic
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureDYNamic};

const NODE _nodeCONFigureMEMory={
(NODES)&_nodeCONFigure ,(NODES*)0,(COMD_WORD*)&_kwMEMory
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureMEMory};

const NODE _nodeCONFigureSHORt={
(NODES)&_nodeCONFigure ,(NODES*)_sonCONFigureSHORt,(COMD_WORD*)&_kwSHORt
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSHORt};

const NODE _nodeCONFigureSHORtFUNCtion={
(NODES)&_nodeCONFigureSHORt ,(NODES*)0,(COMD_WORD*)&_kwFUNCtion
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSHORtFUNCtion};

const NODE _nodeCONFigureSHORtSAFety={
(NODES)&_nodeCONFigureSHORt ,(NODES*)0,(COMD_WORD*)&_kwSAFety
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSHORtSAFety};

const NODE _nodeGNG={
(NODES)&_nodeRoot ,(NODES*)_sonGNG,(COMD_WORD*)&_kwGNG
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idCONFigureGNGPASS};

const NODE _nodeGNGSPECtest={
(NODES)&_nodeGNG ,(NODES*)0,(COMD_WORD*)&_kwSPECtest
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureGNGSPECtest};

const NODE _nodeCONFigureGNG={
(NODES)&_nodeCONFigure ,(NODES*)_sonCONFigureGNG,(COMD_WORD*)&_kwGNG
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idCONFigureGNGPASS};

const NODE _nodeCONFigureGNGSPECtest={
(NODES)&_nodeCONFigureGNG ,(NODES*)0,(COMD_WORD*)&_kwSPECtest
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureGNGSPECtest};

const NODE _nodeGNGDTIMe={
(NODES)&_nodeGNG ,(NODES*)0,(COMD_WORD*)&_kwDTIMe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureGNGDTIMe};

const NODE _nodeCONFigureGNGDTIMe={
(NODES)&_nodeCONFigureGNG ,(NODES*)0,(COMD_WORD*)&_kwDTIMe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureGNGDTIMe};

const NODE _nodeGNGMODE={
(NODES)&_nodeGNG ,(NODES*)0,(COMD_WORD*)&_kwMODE
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureGNGMODE};

const NODE _nodeCONFigureGNGMODE={
(NODES)&_nodeCONFigureGNG ,(NODES*)0,(COMD_WORD*)&_kwMODE
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureGNGMODE};

const NODE _nodeGNGPASS={
(NODES)&_nodeGNG ,(NODES*)0,(COMD_WORD*)&_kwPASS
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idCONFigureGNGPASS};

const NODE _nodeCONFigureGNGPASS={
(NODES)&_nodeCONFigureGNG ,(NODES*)0,(COMD_WORD*)&_kwPASS
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idCONFigureGNGPASS};

const NODE _nodeGNGH={
(NODES)&_nodeGNG ,(NODES*)0,(COMD_WORD*)&_kwH
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureGNGH};

const NODE _nodeCONFigureGNGH={
(NODES)&_nodeCONFigureGNG ,(NODES*)0,(COMD_WORD*)&_kwH
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureGNGH};

const NODE _nodeGNGL={
(NODES)&_nodeGNG ,(NODES*)0,(COMD_WORD*)&_kwL
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureGNGL};

const NODE _nodeCONFigureGNGL={
(NODES)&_nodeCONFigureGNG ,(NODES*)0,(COMD_WORD*)&_kwL
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureGNGL};

const NODE _nodeGNGC={
(NODES)&_nodeGNG ,(NODES*)0,(COMD_WORD*)&_kwC
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureGNGC};

const NODE _nodeCONFigureGNGC={
(NODES)&_nodeCONFigureGNG ,(NODES*)0,(COMD_WORD*)&_kwC
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureGNGC};

const NODE _nodeSTEP={
(NODES)&_nodeRoot ,(NODES*)_sonSTEP,(COMD_WORD*)&_kwSTEP
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeSTEPCCH={
(NODES)&_nodeSTEP ,(NODES*)0,(COMD_WORD*)&_kwCCH
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSTEPCCH};

const NODE _nodeCONFigureSTEP={
(NODES)&_nodeCONFigure ,(NODES*)_sonCONFigureSTEP,(COMD_WORD*)&_kwSTEP
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeCONFigureSTEPCCH={
(NODES)&_nodeCONFigureSTEP ,(NODES*)0,(COMD_WORD*)&_kwCCH
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSTEPCCH};

const NODE _nodeSTEPCCL={
(NODES)&_nodeSTEP ,(NODES*)0,(COMD_WORD*)&_kwCCL
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSTEPCCL};

const NODE _nodeCONFigureSTEPCCL={
(NODES)&_nodeCONFigureSTEP ,(NODES*)0,(COMD_WORD*)&_kwCCL
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSTEPCCL};

const NODE _nodeSTEPCC={
(NODES)&_nodeSTEP ,(NODES*)0,(COMD_WORD*)&_kwCC
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idCONFigureSTEPCC};

const NODE _nodeCONFigureSTEPCC={
(NODES)&_nodeCONFigureSTEP ,(NODES*)0,(COMD_WORD*)&_kwCC
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idCONFigureSTEPCC};

const NODE _nodeSTEPCRH={
(NODES)&_nodeSTEP ,(NODES*)0,(COMD_WORD*)&_kwCRH
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSTEPCRH};

const NODE _nodeCONFigureSTEPCRH={
(NODES)&_nodeCONFigureSTEP ,(NODES*)0,(COMD_WORD*)&_kwCRH
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSTEPCRH};

const NODE _nodeSTEPCRL={
(NODES)&_nodeSTEP ,(NODES*)0,(COMD_WORD*)&_kwCRL
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSTEPCRL};

const NODE _nodeCONFigureSTEPCRL={
(NODES)&_nodeCONFigureSTEP ,(NODES*)0,(COMD_WORD*)&_kwCRL
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSTEPCRL};

const NODE _nodeSTEPCR={
(NODES)&_nodeSTEP ,(NODES*)0,(COMD_WORD*)&_kwCR
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idCONFigureSTEPCR};

const NODE _nodeCONFigureSTEPCR={
(NODES)&_nodeCONFigureSTEP ,(NODES*)0,(COMD_WORD*)&_kwCR
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idCONFigureSTEPCR};

const NODE _nodeSTEPCVH={
(NODES)&_nodeSTEP ,(NODES*)0,(COMD_WORD*)&_kwCVH
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSTEPCVH};

const NODE _nodeCONFigureSTEPCVH={
(NODES)&_nodeCONFigureSTEP ,(NODES*)0,(COMD_WORD*)&_kwCVH
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSTEPCVH};

const NODE _nodeSTEPCVL={
(NODES)&_nodeSTEP ,(NODES*)0,(COMD_WORD*)&_kwCVL
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSTEPCVL};

const NODE _nodeCONFigureSTEPCVL={
(NODES)&_nodeCONFigureSTEP ,(NODES*)0,(COMD_WORD*)&_kwCVL
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSTEPCVL};

const NODE _nodeSTEPCV={
(NODES)&_nodeSTEP ,(NODES*)0,(COMD_WORD*)&_kwCV
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idCONFigureSTEPCV};

const NODE _nodeCONFigureSTEPCV={
(NODES)&_nodeCONFigureSTEP ,(NODES*)0,(COMD_WORD*)&_kwCV
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idCONFigureSTEPCV};

const NODE _nodeSTEPCPH={
(NODES)&_nodeSTEP ,(NODES*)0,(COMD_WORD*)&_kwCPH
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSTEPCPH};

const NODE _nodeCONFigureSTEPCPH={
(NODES)&_nodeCONFigureSTEP ,(NODES*)0,(COMD_WORD*)&_kwCPH
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSTEPCPH};

const NODE _nodeSTEPCPL={
(NODES)&_nodeSTEP ,(NODES*)0,(COMD_WORD*)&_kwCPL
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSTEPCPL};

const NODE _nodeCONFigureSTEPCPL={
(NODES)&_nodeCONFigureSTEP ,(NODES*)0,(COMD_WORD*)&_kwCPL
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureSTEPCPL};

const NODE _nodeSTEPCP={
(NODES)&_nodeSTEP ,(NODES*)0,(COMD_WORD*)&_kwCP
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idCONFigureSTEPCP};

const NODE _nodeCONFigureSTEPCP={
(NODES)&_nodeCONFigureSTEP ,(NODES*)0,(COMD_WORD*)&_kwCP
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idCONFigureSTEPCP};

const NODE _nodeEXTernal={
(NODES)&_nodeRoot ,(NODES*)_sonEXTernal,(COMD_WORD*)&_kwEXTernal
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureEXTernalCONTrol};

const NODE _nodeEXTernalCONTrol={
(NODES)&_nodeEXTernal ,(NODES*)0,(COMD_WORD*)&_kwCONTrol
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureEXTernalCONTrol};

const NODE _nodeCONFigureEXTernal={
(NODES)&_nodeCONFigure ,(NODES*)_sonCONFigureEXTernal,(COMD_WORD*)&_kwEXTernal
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureEXTernalCONTrol};

const NODE _nodeCONFigureEXTernalCONTrol={
(NODES)&_nodeCONFigureEXTernal ,(NODES*)0,(COMD_WORD*)&_kwCONTrol
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureEXTernalCONTrol};

const NODE _nodeEXTernalLOADonin={
(NODES)&_nodeEXTernal ,(NODES*)0,(COMD_WORD*)&_kwLOADonin
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureEXTernalLOADonin};

const NODE _nodeCONFigureEXTernalLOADonin={
(NODES)&_nodeCONFigureEXTernal ,(NODES*)0,(COMD_WORD*)&_kwLOADonin
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureEXTernalLOADonin};

const NODE _nodeEXTernalSYNC={
(NODES)&_nodeEXTernal ,(NODES*)0,(COMD_WORD*)&_kwSYNC
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureEXTernalSYNC};

const NODE _nodeCONFigureEXTernalSYNC={
(NODES)&_nodeCONFigureEXTernal ,(NODES*)0,(COMD_WORD*)&_kwSYNC
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONFigureEXTernalSYNC};

const NODE _nodeMODE={
(NODES)&_nodeRoot ,(NODES*)_sonMODE,(COMD_WORD*)&_kwMODE
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idMODE};

const NODE _nodeCRANge={
(NODES)&_nodeRoot ,(NODES*)0,(COMD_WORD*)&_kwCRANge
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idMODECRANge};

const NODE _nodeMODECRANge={
(NODES)&_nodeMODE ,(NODES*)0,(COMD_WORD*)&_kwCRANge
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idMODECRANge};

const NODE _nodeVRANge={
(NODES)&_nodeRoot ,(NODES*)0,(COMD_WORD*)&_kwVRANge
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idMODEVRANge};

const NODE _nodeMODEVRANge={
(NODES)&_nodeMODE ,(NODES*)0,(COMD_WORD*)&_kwVRANge
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idMODEVRANge};

const NODE _nodeDYNamic={
(NODES)&_nodeRoot ,(NODES*)0,(COMD_WORD*)&_kwDYNamic
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idMODEDYNamic};

const NODE _nodeMODEDYNamic={
(NODES)&_nodeMODE ,(NODES*)0,(COMD_WORD*)&_kwDYNamic
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idMODEDYNamic};

const NODE _nodeCURRentRECall={
(NODES)&_nodeCURRent ,(NODES*)0,(COMD_WORD*)&_kwRECall
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCURRentRECall};

const NODE _nodeCURRentVB={
(NODES)&_nodeCURRent ,(NODES*)0,(COMD_WORD*)&_kwVB
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCURRentVB};

const NODE _nodeCURRentSRATe={
(NODES)&_nodeCURRent ,(NODES*)0,(COMD_WORD*)&_kwSRATe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCURRentSRATe};

const NODE _nodeCURRentL12={
(NODES)&_nodeCURRent ,(NODES*)0,(COMD_WORD*)&_kwL
,(COMD_SUFFIX*)&_cp1,(char)T_RQS,(unsigned int)_idCURRentL12};

const NODE _nodeCURRentSET={
(NODES)&_nodeCURRent ,(NODES*)0,(COMD_WORD*)&_kwSET
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCURRentSET};

const NODE _nodeCURRentRISE={
(NODES)&_nodeCURRent ,(NODES*)0,(COMD_WORD*)&_kwRISE
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCURRentRISE};

const NODE _nodeCURRentFALL={
(NODES)&_nodeCURRent ,(NODES*)0,(COMD_WORD*)&_kwFALL
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCURRentFALL};

const NODE _nodeCURRentT12={
(NODES)&_nodeCURRent ,(NODES*)0,(COMD_WORD*)&_kwT
,(COMD_SUFFIX*)&_cp1,(char)T_RQS,(unsigned int)_idCURRentT12};

const NODE _nodeCURRentFREQuency={
(NODES)&_nodeCURRent ,(NODES*)0,(COMD_WORD*)&_kwFREQuency
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCURRentFREQuency};

const NODE _nodeCURRentDUTY={
(NODES)&_nodeCURRent ,(NODES*)0,(COMD_WORD*)&_kwDUTY
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCURRentDUTY};

const NODE _nodeCURRentCV={
(NODES)&_nodeCURRent ,(NODES*)_sonCURRentCV,(COMD_WORD*)&_kwCV
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeCURRentCVRESPonse={
(NODES)&_nodeCURRentCV ,(NODES*)0,(COMD_WORD*)&_kwRESPonse
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCURRentCVRESPonse};

const NODE _nodeRESistanceRECall={
(NODES)&_nodeRESistance ,(NODES*)0,(COMD_WORD*)&_kwRECall
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idRESistanceRECall};

const NODE _nodeCONDuctanceRECall={
(NODES)&_nodeCONDuctance ,(NODES*)0,(COMD_WORD*)&_kwRECall
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONDuctanceRECall};

const NODE _nodeCONDuctanceVB={
(NODES)&_nodeCONDuctance ,(NODES*)0,(COMD_WORD*)&_kwVB
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONDuctanceVB};

const NODE _nodeRESistanceVB={
(NODES)&_nodeRESistance ,(NODES*)0,(COMD_WORD*)&_kwVB
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idRESistanceVB};

const NODE _nodeRESistanceSRATe={
(NODES)&_nodeRESistance ,(NODES*)0,(COMD_WORD*)&_kwSRATe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idRESistanceSRATe};

const NODE _nodeCONDuctanceL12={
(NODES)&_nodeCONDuctance ,(NODES*)0,(COMD_WORD*)&_kwL
,(COMD_SUFFIX*)&_cp1,(char)T_RQS,(unsigned int)_idCONDuctanceL12};

const NODE _nodeCONDuctanceSET={
(NODES)&_nodeCONDuctance ,(NODES*)0,(COMD_WORD*)&_kwSET
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCONDuctanceSET};

const NODE _nodeRESistanceL12={
(NODES)&_nodeRESistance ,(NODES*)0,(COMD_WORD*)&_kwL
,(COMD_SUFFIX*)&_cp1,(char)T_RQS,(unsigned int)_idRESistanceL12};

const NODE _nodeRESistanceSET={
(NODES)&_nodeRESistance ,(NODES*)0,(COMD_WORD*)&_kwSET
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idRESistanceSET};

const NODE _nodeRESistanceLEVel={
(NODES)&_nodeRESistance ,(NODES*)0,(COMD_WORD*)&_kwLEVel
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idRESistanceLEVel};

const NODE _nodeRESistanceRISE={
(NODES)&_nodeRESistance ,(NODES*)0,(COMD_WORD*)&_kwRISE
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idRESistanceRISE};

const NODE _nodeRESistanceFALL={
(NODES)&_nodeRESistance ,(NODES*)0,(COMD_WORD*)&_kwFALL
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idRESistanceFALL};

const NODE _nodeRESistanceT12={
(NODES)&_nodeRESistance ,(NODES*)0,(COMD_WORD*)&_kwT
,(COMD_SUFFIX*)&_cp1,(char)T_RQS,(unsigned int)_idRESistanceT12};

const NODE _nodeRESistanceFREQuency={
(NODES)&_nodeRESistance ,(NODES*)0,(COMD_WORD*)&_kwFREQuency
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idRESistanceFREQuency};

const NODE _nodeRESistanceDUTY={
(NODES)&_nodeRESistance ,(NODES*)0,(COMD_WORD*)&_kwDUTY
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idRESistanceDUTY};

const NODE _nodeRESistanceCV={
(NODES)&_nodeRESistance ,(NODES*)_sonRESistanceCV,(COMD_WORD*)&_kwCV
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeRESistanceCVRESPonse={
(NODES)&_nodeRESistanceCV ,(NODES*)0,(COMD_WORD*)&_kwRESPonse
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idRESistanceCVRESPonse};

const NODE _nodeVOLTage={
(NODES)&_nodeRoot ,(NODES*)_sonVOLTage,(COMD_WORD*)&_kwVOLTage
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idVOLTageVA};

const NODE _nodeVOLTageRECall={
(NODES)&_nodeVOLTage ,(NODES*)0,(COMD_WORD*)&_kwRECall
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idVOLTageRECall};

const NODE _nodeVOLTageVA={
(NODES)&_nodeVOLTage ,(NODES*)0,(COMD_WORD*)&_kwVA
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idVOLTageVA};

const NODE _nodeVOLTageVB={
(NODES)&_nodeVOLTage ,(NODES*)0,(COMD_WORD*)&_kwVB
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idVOLTageVB};

const NODE _nodeVOLTageRESPonse={
(NODES)&_nodeVOLTage ,(NODES*)0,(COMD_WORD*)&_kwRESPonse
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idVOLTageRESPonse};

const NODE _nodePOWer={
(NODES)&_nodeRoot ,(NODES*)_sonPOWer,(COMD_WORD*)&_kwPOWer
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPOWerVA};

const NODE _nodePOWerRECall={
(NODES)&_nodePOWer ,(NODES*)0,(COMD_WORD*)&_kwRECall
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPOWerRECall};

const NODE _nodePOWerVA={
(NODES)&_nodePOWer ,(NODES*)0,(COMD_WORD*)&_kwVA
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPOWerVA};

const NODE _nodePOWerVB={
(NODES)&_nodePOWer ,(NODES*)0,(COMD_WORD*)&_kwVB
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPOWerVB};

const NODE _nodePOWerRESPonse={
(NODES)&_nodePOWer ,(NODES*)0,(COMD_WORD*)&_kwRESPonse
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPOWerRESPonse};

const NODE _nodePOWerCV={
(NODES)&_nodePOWer ,(NODES*)_sonPOWerCV,(COMD_WORD*)&_kwCV
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodePOWerCVRESPonse={
(NODES)&_nodePOWerCV ,(NODES*)0,(COMD_WORD*)&_kwRESPonse
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPOWerCVRESPonse};

const NODE _nodeFUNCtion={
(NODES)&_nodeRoot ,(NODES*)_sonFUNCtion,(COMD_WORD*)&_kwFUNCtion
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceFUNCtionMODE};

const NODE _nodeFUNCtionCOMPlete={
(NODES)&_nodeFUNCtion ,(NODES*)_sonFUNCtionCOMPlete,(COMD_WORD*)&_kwCOMPlete
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeFUNCtionCOMPleteRING={
(NODES)&_nodeFUNCtionCOMPlete ,(NODES*)_sonFUNCtionCOMPleteRING,(COMD_WORD*)&_kwRING
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeFUNCtionCOMPleteRINGTIME={
(NODES)&_nodeFUNCtionCOMPleteRING ,(NODES*)0,(COMD_WORD*)&_kwTIME
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFUNCtionCOMPleteRINGTIME};

const NODE _nodeFUNCtionRING={
(NODES)&_nodeFUNCtion ,(NODES*)_sonFUNCtionRING,(COMD_WORD*)&_kwRING
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeFUNCtionRINGTIME={
(NODES)&_nodeFUNCtionRING ,(NODES*)0,(COMD_WORD*)&_kwTIME
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFUNCtionCOMPleteRINGTIME};

const NODE _nodeFUNCtionCOMPleteTIME={
(NODES)&_nodeFUNCtionCOMPlete ,(NODES*)0,(COMD_WORD*)&_kwTIME
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFUNCtionCOMPleteRINGTIME};

const NODE _nodeFUNCtionTIME={
(NODES)&_nodeFUNCtion ,(NODES*)0,(COMD_WORD*)&_kwTIME
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFUNCtionCOMPleteRINGTIME};

const NODE _nodePROGram={
(NODES)&_nodeRoot ,(NODES*)_sonPROGram,(COMD_WORD*)&_kwPROGram
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGram};

const NODE _nodePROGramSTATe={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwSTATe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSTATe};

const NODE _nodePROGramRECall={
(NODES)&_nodePROGram ,(NODES*)_sonPROGramRECall,(COMD_WORD*)&_kwRECall
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodePROGramRECallDEFault={
(NODES)&_nodePROGramRECall ,(NODES*)0,(COMD_WORD*)&_kwDEFault
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramRECallDEFault};

const NODE _nodePROGramDEFault={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwDEFault
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramRECallDEFault};

const NODE _nodePROGramSTARt={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwSTARt
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSTARt};

const NODE _nodePROGramSTEP={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwSTEP
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSTEP};

const NODE _nodePROGramMEMory={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwMEMory
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramMEMory};

const NODE _nodePROGramRUN={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwRUN
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramRUN};

const NODE _nodePROGramONTime={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwONTime
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramONTime};

const NODE _nodePROGramOFFTime={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwOFFTime
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramOFFTime};

const NODE _nodePROGramPFTime={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwPFTime
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramPFTime};

const NODE _nodePROGramSTIMe={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwSTIMe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSTIMe};

const NODE _nodeCHAin={
(NODES)&_nodeRoot ,(NODES*)_sonCHAin,(COMD_WORD*)&_kwCHAin
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramCHAin};

const NODE _nodeCHAinSTARt={
(NODES)&_nodeCHAin ,(NODES*)0,(COMD_WORD*)&_kwSTARt
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramCHAinSTARt};

const NODE _nodePROGramCHAin={
(NODES)&_nodePROGram ,(NODES*)_sonPROGramCHAin,(COMD_WORD*)&_kwCHAin
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramCHAin};

const NODE _nodePROGramCHAinSTARt={
(NODES)&_nodePROGramCHAin ,(NODES*)0,(COMD_WORD*)&_kwSTARt
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramCHAinSTARt};

const NODE _nodeCHAinP2P={
(NODES)&_nodeCHAin ,(NODES*)0,(COMD_WORD*)&_kwP2P
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramCHAinP2P};

const NODE _nodePROGramCHAinP2P={
(NODES)&_nodePROGramCHAin ,(NODES*)0,(COMD_WORD*)&_kwP2P
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramCHAinP2P};

const NODE _nodeCHAinRECall={
(NODES)&_nodeCHAin ,(NODES*)_sonCHAinRECall,(COMD_WORD*)&_kwRECall
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeCHAinRECallDEFault={
(NODES)&_nodeCHAinRECall ,(NODES*)0,(COMD_WORD*)&_kwDEFault
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramCHAinRECallDEFault};

const NODE _nodePROGramCHAinRECall={
(NODES)&_nodePROGramCHAin ,(NODES*)_sonPROGramCHAinRECall,(COMD_WORD*)&_kwRECall
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodePROGramCHAinRECallDEFault={
(NODES)&_nodePROGramCHAinRECall ,(NODES*)0,(COMD_WORD*)&_kwDEFault
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramCHAinRECallDEFault};

const NODE _nodePROGramCHAinDEFault={
(NODES)&_nodePROGramCHAin ,(NODES*)0,(COMD_WORD*)&_kwDEFault
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramCHAinRECallDEFault};

const NODE _nodeCHAinDEFault={
(NODES)&_nodeCHAin ,(NODES*)0,(COMD_WORD*)&_kwDEFault
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramCHAinRECallDEFault};

const NODE _nodePROGramSAVE={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwSAVE
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSAVE};

const NODE _nodeSEQuence={
(NODES)&_nodeRoot ,(NODES*)_sonSEQuence,(COMD_WORD*)&_kwSEQuence
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeSEQuenceCOMPlete={
(NODES)&_nodeSEQuence ,(NODES*)_sonSEQuenceCOMPlete,(COMD_WORD*)&_kwCOMPlete
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeSEQuenceCOMPleteRING={
(NODES)&_nodeSEQuenceCOMPlete ,(NODES*)_sonSEQuenceCOMPleteRING,(COMD_WORD*)&_kwRING
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeSEQuenceCOMPleteRINGTIME={
(NODES)&_nodeSEQuenceCOMPleteRING ,(NODES*)0,(COMD_WORD*)&_kwTIME
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSEQuenceCOMPleteRINGTIME};

const NODE _nodeSEQuenceRING={
(NODES)&_nodeSEQuence ,(NODES*)_sonSEQuenceRING,(COMD_WORD*)&_kwRING
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeSEQuenceRINGTIME={
(NODES)&_nodeSEQuenceRING ,(NODES*)0,(COMD_WORD*)&_kwTIME
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSEQuenceCOMPleteRINGTIME};

const NODE _nodeSEQuenceCOMPleteTIME={
(NODES)&_nodeSEQuenceCOMPlete ,(NODES*)0,(COMD_WORD*)&_kwTIME
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSEQuenceCOMPleteRINGTIME};

const NODE _nodeSEQuenceTIME={
(NODES)&_nodeSEQuence ,(NODES*)0,(COMD_WORD*)&_kwTIME
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSEQuenceCOMPleteRINGTIME};

const NODE _nodeNSEQuence={
(NODES)&_nodeRoot ,(NODES*)_sonNSEQuence,(COMD_WORD*)&_kwNSEQuence
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idNSEQuence};

const NODE _nodeNSEQuenceTIMer={
(NODES)&_nodeNSEQuence ,(NODES*)0,(COMD_WORD*)&_kwTIMer
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idNSEQuenceTIMer};

const NODE _nodeNSEQuenceCOTime={
(NODES)&_nodeNSEQuence ,(NODES*)0,(COMD_WORD*)&_kwCOTime
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idNSEQuenceCOTime};

const NODE _nodeNSEQuenceSTATe={
(NODES)&_nodeNSEQuence ,(NODES*)0,(COMD_WORD*)&_kwSTATe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idNSEQuenceSTATe};

const NODE _nodeNSEQuenceSTARt={
(NODES)&_nodeNSEQuence ,(NODES*)0,(COMD_WORD*)&_kwSTARt
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idNSEQuenceSTARt};

const NODE _nodeNSEQuenceNUMBer={
(NODES)&_nodeNSEQuence ,(NODES*)0,(COMD_WORD*)&_kwNUMBer
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idNSEQuenceNUMBer};

const NODE _nodeNSEQuenceMEMO={
(NODES)&_nodeNSEQuence ,(NODES*)0,(COMD_WORD*)&_kwMEMO
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idNSEQuenceMEMO};

const NODE _nodeNSEQuenceMODE={
(NODES)&_nodeNSEQuence ,(NODES*)0,(COMD_WORD*)&_kwMODE
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idNSEQuenceMODE};

const NODE _nodeNSEQuenceRANGe={
(NODES)&_nodeNSEQuence ,(NODES*)0,(COMD_WORD*)&_kwRANGe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idNSEQuenceRANGe};

const NODE _nodeNSEQuenceLOOP={
(NODES)&_nodeNSEQuence ,(NODES*)0,(COMD_WORD*)&_kwLOOP
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idNSEQuenceLOOP};

const NODE _nodeNSEQuenceLLOad={
(NODES)&_nodeNSEQuence ,(NODES*)0,(COMD_WORD*)&_kwLLOad
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idNSEQuenceLLOad};

const NODE _nodeNSEQuenceLAST={
(NODES)&_nodeNSEQuence ,(NODES*)0,(COMD_WORD*)&_kwLAST
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idNSEQuenceLAST};

const NODE _nodeNSEQuenceCHAin={
(NODES)&_nodeNSEQuence ,(NODES*)0,(COMD_WORD*)&_kwCHAin
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idNSEQuenceCHAin};

const NODE _nodeNSEQuenceEDIT={
(NODES)&_nodeNSEQuence ,(NODES*)_sonNSEQuenceEDIT,(COMD_WORD*)&_kwEDIT
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idNSEQuenceEDIT};

const NODE _nodeNSEQuenceEDITPOINt={
(NODES)&_nodeNSEQuenceEDIT ,(NODES*)0,(COMD_WORD*)&_kwPOINt
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idNSEQuenceEDITPOINt};

const NODE _nodeNSEQuenceEDITEND={
(NODES)&_nodeNSEQuenceEDIT ,(NODES*)0,(COMD_WORD*)&_kwEND
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idNSEQuenceEDITEND};

const NODE _nodeNSEQuenceDELet={
(NODES)&_nodeNSEQuence ,(NODES*)_sonNSEQuenceDELet,(COMD_WORD*)&_kwDELet
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeNSEQuenceDELetALL={
(NODES)&_nodeNSEQuenceDELet ,(NODES*)0,(COMD_WORD*)&_kwALL
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idNSEQuenceDELetALL};

const NODE _nodeNSEQuenceALL={
(NODES)&_nodeNSEQuence ,(NODES*)0,(COMD_WORD*)&_kwALL
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idNSEQuenceDELetALL};

const NODE _nodeNSEQuenceSAVE={
(NODES)&_nodeNSEQuence ,(NODES*)0,(COMD_WORD*)&_kwSAVE
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idNSEQuenceSAVE};

const NODE _nodeFSEQuence={
(NODES)&_nodeRoot ,(NODES*)_sonFSEQuence,(COMD_WORD*)&_kwFSEQuence
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFSEQuence};

const NODE _nodeFSEQuenceSTATe={
(NODES)&_nodeFSEQuence ,(NODES*)0,(COMD_WORD*)&_kwSTATe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFSEQuenceSTATe};

const NODE _nodeFSEQuenceMEMO={
(NODES)&_nodeFSEQuence ,(NODES*)0,(COMD_WORD*)&_kwMEMO
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFSEQuenceMEMO};

const NODE _nodeFSEQuenceMODE={
(NODES)&_nodeFSEQuence ,(NODES*)0,(COMD_WORD*)&_kwMODE
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFSEQuenceMODE};

const NODE _nodeFSEQuenceRANGe={
(NODES)&_nodeFSEQuence ,(NODES*)0,(COMD_WORD*)&_kwRANGe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFSEQuenceRANGe};

const NODE _nodeFSEQuenceLOOP={
(NODES)&_nodeFSEQuence ,(NODES*)0,(COMD_WORD*)&_kwLOOP
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFSEQuenceLOOP};

const NODE _nodeFSEQuenceTBASe={
(NODES)&_nodeFSEQuence ,(NODES*)0,(COMD_WORD*)&_kwTBASe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFSEQuenceTBASe};

const NODE _nodeFSEQuenceLLOad={
(NODES)&_nodeFSEQuence ,(NODES*)0,(COMD_WORD*)&_kwLLOad
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFSEQuenceLLOad};

const NODE _nodeFSEQuenceLAST={
(NODES)&_nodeFSEQuence ,(NODES*)0,(COMD_WORD*)&_kwLAST
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFSEQuenceLAST};

const NODE _nodeFSEQuenceRPTStep={
(NODES)&_nodeFSEQuence ,(NODES*)0,(COMD_WORD*)&_kwRPTStep
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFSEQuenceRPTStep};

const NODE _nodeFSEQuenceEDIT={
(NODES)&_nodeFSEQuence ,(NODES*)_sonFSEQuenceEDIT,(COMD_WORD*)&_kwEDIT
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFSEQuenceEDIT};

const NODE _nodeFSEQuenceEDITPOINt={
(NODES)&_nodeFSEQuenceEDIT ,(NODES*)0,(COMD_WORD*)&_kwPOINt
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFSEQuenceEDITPOINt};

const NODE _nodeFSEQuenceEDITEND={
(NODES)&_nodeFSEQuenceEDIT ,(NODES*)0,(COMD_WORD*)&_kwEND
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idFSEQuenceEDITEND};

const NODE _nodeFSEQuenceDELet={
(NODES)&_nodeFSEQuence ,(NODES*)_sonFSEQuenceDELet,(COMD_WORD*)&_kwDELet
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeFSEQuenceDELetALL={
(NODES)&_nodeFSEQuenceDELet ,(NODES*)0,(COMD_WORD*)&_kwALL
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idFSEQuenceDELetALL};

const NODE _nodeFSEQuenceALL={
(NODES)&_nodeFSEQuence ,(NODES*)0,(COMD_WORD*)&_kwALL
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idFSEQuenceDELetALL};

const NODE _nodeFSEQuenceEDITFILL={
(NODES)&_nodeFSEQuenceEDIT ,(NODES*)0,(COMD_WORD*)&_kwFILL
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFSEQuenceEDITFILL};

const NODE _nodeFSEQuenceFILL={
(NODES)&_nodeFSEQuence ,(NODES*)0,(COMD_WORD*)&_kwFILL
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idFSEQuenceEDITFILL};

const NODE _nodeFSEQuenceSAVE={
(NODES)&_nodeFSEQuence ,(NODES*)0,(COMD_WORD*)&_kwSAVE
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idFSEQuenceSAVE};

const NODE _nodeOCPSTATe={
(NODES)&_nodeOCP ,(NODES*)0,(COMD_WORD*)&_kwSTATe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPSTATe};

const NODE _nodeOCPEDIT={
(NODES)&_nodeOCP ,(NODES*)_sonOCPEDIT,(COMD_WORD*)&_kwEDIT
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPEDITCHANnel};

const NODE _nodeOCPEDITCHANnel={
(NODES)&_nodeOCPEDIT ,(NODES*)0,(COMD_WORD*)&_kwCHANnel
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPEDITCHANnel};

const NODE _nodeOCPCHANnel={
(NODES)&_nodeOCP ,(NODES*)_sonOCPCHANnel,(COMD_WORD*)&_kwCHANnel
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeOCPCHANnelTEMP={
(NODES)&_nodeOCPCHANnel ,(NODES*)0,(COMD_WORD*)&_kwTEMP
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelTEMP};

const NODE _nodeOCPTEMP={
(NODES)&_nodeOCP ,(NODES*)0,(COMD_WORD*)&_kwTEMP
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelTEMP};

const NODE _nodeOCPCHANnelRANGe={
(NODES)&_nodeOCPCHANnel ,(NODES*)0,(COMD_WORD*)&_kwRANGe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelRANGe};

const NODE _nodeOCPRANGe={
(NODES)&_nodeOCP ,(NODES*)0,(COMD_WORD*)&_kwRANGe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelRANGe};

const NODE _nodeOCPCHANnelSTARt={
(NODES)&_nodeOCPCHANnel ,(NODES*)0,(COMD_WORD*)&_kwSTARt
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelSTARt};

const NODE _nodeOCPSTARt={
(NODES)&_nodeOCP ,(NODES*)0,(COMD_WORD*)&_kwSTARt
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelSTARt};

const NODE _nodeOCPCHANnelEND={
(NODES)&_nodeOCPCHANnel ,(NODES*)0,(COMD_WORD*)&_kwEND
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelEND};

const NODE _nodeOCPEND={
(NODES)&_nodeOCP ,(NODES*)0,(COMD_WORD*)&_kwEND
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelEND};

const NODE _nodeOCPCHANnelSTEP={
(NODES)&_nodeOCPCHANnel ,(NODES*)_sonOCPCHANnelSTEP,(COMD_WORD*)&_kwSTEP
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeOCPCHANnelStepCurrWattent={
(NODES)&_nodeOCPCHANnelSTEP ,(NODES*)0,(COMD_WORD*)&_kwCURRent
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelStepCurrWattent};

const NODE _nodeOCPSTEP={
(NODES)&_nodeOCP ,(NODES*)_sonOCPSTEP,(COMD_WORD*)&_kwSTEP
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeOCPStepCurrWattent={
(NODES)&_nodeOCPSTEP ,(NODES*)0,(COMD_WORD*)&_kwCURRent
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelStepCurrWattent};

const NODE _nodeOCPCHANnelLAST={
(NODES)&_nodeOCPCHANnel ,(NODES*)0,(COMD_WORD*)&_kwLAST
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelLAST};

const NODE _nodeOCPLAST={
(NODES)&_nodeOCP ,(NODES*)0,(COMD_WORD*)&_kwLAST
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelLAST};

const NODE _nodeOCPCHANnelSTEPTIME={
(NODES)&_nodeOCPCHANnelSTEP ,(NODES*)0,(COMD_WORD*)&_kwTIME
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelSTEPTIME};

const NODE _nodeOCPSTEPTIME={
(NODES)&_nodeOCPSTEP ,(NODES*)0,(COMD_WORD*)&_kwTIME
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelSTEPTIME};

const NODE _nodeOCPCHANnelDELay={
(NODES)&_nodeOCPCHANnel ,(NODES*)0,(COMD_WORD*)&_kwDELay
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelDELay};

const NODE _nodeOCPDELay={
(NODES)&_nodeOCP ,(NODES*)0,(COMD_WORD*)&_kwDELay
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelDELay};

const NODE _nodeOCPCHANnelTRIGger={
(NODES)&_nodeOCPCHANnel ,(NODES*)0,(COMD_WORD*)&_kwTRIGger
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelTRIGger};

const NODE _nodeOCPTRIGger={
(NODES)&_nodeOCP ,(NODES*)0,(COMD_WORD*)&_kwTRIGger
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idOCPCHANnelTRIGger};

const NODE _nodeOCPSAVE={
(NODES)&_nodeOCP ,(NODES*)0,(COMD_WORD*)&_kwSAVE
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idOCPSAVE};

const NODE _nodeOCPRESult={
(NODES)&_nodeOCP ,(NODES*)0,(COMD_WORD*)&_kwRESult
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idOCPRESult};

const NODE _nodeOCPRUN={
(NODES)&_nodeOCP ,(NODES*)0,(COMD_WORD*)&_kwRUN
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idOCPRUN};

const NODE _nodeUTILity={
(NODES)&_nodeRoot ,(NODES*)_sonUTILity,(COMD_WORD*)&_kwUTILity
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeUTILitySYSTem={
(NODES)&_nodeUTILity ,(NODES*)0,(COMD_WORD*)&_kwSYSTem
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idUTILitySYSTem};

const NODE _nodeUTILityREMote={
(NODES)&_nodeUTILity ,(NODES*)_sonUTILityREMote,(COMD_WORD*)&_kwREMote
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idUTILityREMote};

const NODE _nodeUTILityREMoteMODE={
(NODES)&_nodeUTILityREMote ,(NODES*)0,(COMD_WORD*)&_kwMODE
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idUTILityREMoteMODE};

const NODE _nodeUTILityLOAD={
(NODES)&_nodeUTILity ,(NODES*)_sonUTILityLOAD,(COMD_WORD*)&_kwLOAD
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idUTILityLOAD};

const NODE _nodeUTILityLOADMODE={
(NODES)&_nodeUTILityLOAD ,(NODES*)0,(COMD_WORD*)&_kwMODE
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idUTILityLOADMODE};

const NODE _nodeUTILityLOADRANGe={
(NODES)&_nodeUTILityLOAD ,(NODES*)0,(COMD_WORD*)&_kwRANGe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idUTILityLOADRANGe};

const NODE _nodeUTILityINTerface={
(NODES)&_nodeUTILity ,(NODES*)0,(COMD_WORD*)&_kwINTerface
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idUTILityINTerface};

const NODE _nodeUTILityTIME={
(NODES)&_nodeUTILity ,(NODES*)0,(COMD_WORD*)&_kwTIME
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idUTILityTIME};

const NODE _nodeUTILityKNOB={
(NODES)&_nodeUTILity ,(NODES*)0,(COMD_WORD*)&_kwKNOB
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idUTILityKNOB};

const NODE _nodeUTILitySPEaker={
(NODES)&_nodeUTILity ,(NODES*)0,(COMD_WORD*)&_kwSPEaker
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idUTILitySPEaker};

const NODE _nodeUTILityALARm={
(NODES)&_nodeUTILity ,(NODES*)0,(COMD_WORD*)&_kwALARm
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idUTILityALARm};

const NODE _nodeUTILityUNReg={
(NODES)&_nodeUTILity ,(NODES*)0,(COMD_WORD*)&_kwUNReg
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idUTILityUNReg};

const NODE _nodeUTILityGNG={
(NODES)&_nodeUTILity ,(NODES*)0,(COMD_WORD*)&_kwGNG
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idUTILityGNG};

const NODE _nodeUTILityCONTrast={
(NODES)&_nodeUTILity ,(NODES*)0,(COMD_WORD*)&_kwCONTrast
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idUTILityCONTrast};

const NODE _nodeUTILityBRIGhtness={
(NODES)&_nodeUTILity ,(NODES*)0,(COMD_WORD*)&_kwBRIGhtness
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idUTILityBRIGhtness};

const NODE _nodeUTILityLANGuage={
(NODES)&_nodeUTILity ,(NODES*)0,(COMD_WORD*)&_kwLANGuage
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idUTILityLANGuage};

const NODE _nodeMEMory={
(NODES)&_nodeRoot ,(NODES*)_sonMEMory,(COMD_WORD*)&_kwMEMory
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeMEMorySAVE={
(NODES)&_nodeMEMory ,(NODES*)0,(COMD_WORD*)&_kwSAVE
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idMEMorySAVE};

const NODE _nodeMEMoryRECall={
(NODES)&_nodeMEMory ,(NODES*)0,(COMD_WORD*)&_kwRECall
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idMEMoryRECall};

const NODE _nodePRESet={
(NODES)&_nodeRoot ,(NODES*)_sonPRESet,(COMD_WORD*)&_kwPRESet
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodePRESetSAVE={
(NODES)&_nodePRESet ,(NODES*)0,(COMD_WORD*)&_kwSAVE
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPRESetSAVE};

const NODE _nodePRESetRECall={
(NODES)&_nodePRESet ,(NODES*)0,(COMD_WORD*)&_kwRECall
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPRESetRECall};

const NODE _nodeSETup={
(NODES)&_nodeRoot ,(NODES*)_sonSETup,(COMD_WORD*)&_kwSETup
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeSETupSAVE={
(NODES)&_nodeSETup ,(NODES*)0,(COMD_WORD*)&_kwSAVE
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSETupSAVE};

const NODE _nodeSETupRECall={
(NODES)&_nodeSETup ,(NODES*)0,(COMD_WORD*)&_kwRECall
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSETupRECall};

const NODE _nodeFACTory={
(NODES)&_nodeRoot ,(NODES*)_sonFACTory,(COMD_WORD*)&_kwFACTory
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idFACToryRECall};

const NODE _nodeFACToryRECall={
(NODES)&_nodeFACTory ,(NODES*)0,(COMD_WORD*)&_kwRECall
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idFACToryRECall};

const NODE _nodeUSER={
(NODES)&_nodeRoot ,(NODES*)_sonUSER,(COMD_WORD*)&_kwUSER
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeUSERDEFault={
(NODES)&_nodeUSER ,(NODES*)_sonUSERDEFault,(COMD_WORD*)&_kwDEFault
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeUSERDEFaultSAVE={
(NODES)&_nodeUSERDEFault ,(NODES*)0,(COMD_WORD*)&_kwSAVE
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idUSERDEFaultSAVE};

const NODE _nodeUSERSAVE={
(NODES)&_nodeUSER ,(NODES*)0,(COMD_WORD*)&_kwSAVE
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idUSERDEFaultSAVE};

const NODE _nodeUSERDEFaultRECall={
(NODES)&_nodeUSERDEFault ,(NODES*)0,(COMD_WORD*)&_kwRECall
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idUSERDEFaultRECall};

const NODE _nodeUSERRECall={
(NODES)&_nodeUSER ,(NODES*)0,(COMD_WORD*)&_kwRECall
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idUSERDEFaultRECall};

const NODE _nodeSERial={
(NODES)&_nodeRoot ,(NODES*)_sonSERial,(COMD_WORD*)&_kwSERial
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSERialMASTer};

const NODE _nodeSERialMASTer={
(NODES)&_nodeSERial ,(NODES*)0,(COMD_WORD*)&_kwMASTer
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSERialMASTer};

const NODE _nodeSTATus={
(NODES)&_nodeRoot ,(NODES*)_sonSTATus,(COMD_WORD*)&_kwSTATus
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeSTATusPRESet={
(NODES)&_nodeSTATus ,(NODES*)0,(COMD_WORD*)&_kwPRESet
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSTATusPRESet};

const NODE _nodeSTATusQUEStionable={
(NODES)&_nodeSTATus ,(NODES*)_sonSTATusQUEStionable,(COMD_WORD*)&_kwQUEStionable
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idSTATusQUEStionableEVENt};

const NODE _nodeSTATusQUEStionableCONDition={
(NODES)&_nodeSTATusQUEStionable ,(NODES*)0,(COMD_WORD*)&_kwCONDition
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idSTATusQUEStionableCONDition};

const NODE _nodeSTATusQUEStionableENABle={
(NODES)&_nodeSTATusQUEStionable ,(NODES*)0,(COMD_WORD*)&_kwENABle
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSTATusQUEStionableENABle};

const NODE _nodeSTATusQUEStionableEVENt={
(NODES)&_nodeSTATusQUEStionable ,(NODES*)0,(COMD_WORD*)&_kwEVENt
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idSTATusQUEStionableEVENt};

const NODE _nodeSTATusQUEStionableNTRansition={
(NODES)&_nodeSTATusQUEStionable ,(NODES*)0,(COMD_WORD*)&_kwNTRansition
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSTATusQUEStionableNTRansition};

const NODE _nodeSTATusQUEStionablePTRansition={
(NODES)&_nodeSTATusQUEStionable ,(NODES*)0,(COMD_WORD*)&_kwPTRansition
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSTATusQUEStionablePTRansition};

const NODE _nodeSTATusOPERation={
(NODES)&_nodeSTATus ,(NODES*)_sonSTATusOPERation,(COMD_WORD*)&_kwOPERation
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idSTATusOPERationEVENt};

const NODE _nodeSTATusOPERationCONDition={
(NODES)&_nodeSTATusOPERation ,(NODES*)0,(COMD_WORD*)&_kwCONDition
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idSTATusOPERationCONDition};

const NODE _nodeSTATusOPERationENABle={
(NODES)&_nodeSTATusOPERation ,(NODES*)0,(COMD_WORD*)&_kwENABle
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSTATusOPERationENABle};

const NODE _nodeSTATusOPERationEVENt={
(NODES)&_nodeSTATusOPERation ,(NODES*)0,(COMD_WORD*)&_kwEVENt
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idSTATusOPERationEVENt};

const NODE _nodeSTATusOPERationNTRansition={
(NODES)&_nodeSTATusOPERation ,(NODES*)0,(COMD_WORD*)&_kwNTRansition
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSTATusOPERationNTRansition};

const NODE _nodeSTATusOPERationPTRansition={
(NODES)&_nodeSTATusOPERation ,(NODES*)0,(COMD_WORD*)&_kwPTRansition
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSTATusOPERationPTRansition};

const NODE _nodeSTATusCSUMmary={
(NODES)&_nodeSTATus ,(NODES*)_sonSTATusCSUMmary,(COMD_WORD*)&_kwCSUMmary
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idSTATusCSUMmaryEVENt};

const NODE _nodeSTATusCSUMmaryCONDition={
(NODES)&_nodeSTATusCSUMmary ,(NODES*)0,(COMD_WORD*)&_kwCONDition
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idSTATusCSUMmaryCONDition};

const NODE _nodeSTATusCSUMmaryENABle={
(NODES)&_nodeSTATusCSUMmary ,(NODES*)0,(COMD_WORD*)&_kwENABle
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSTATusCSUMmaryENABle};

const NODE _nodeSTATusCSUMmaryEVENt={
(NODES)&_nodeSTATusCSUMmary ,(NODES*)0,(COMD_WORD*)&_kwEVENt
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idSTATusCSUMmaryEVENt};

const NODE _nodeSTATusCSUMmaryNTRansition={
(NODES)&_nodeSTATusCSUMmary ,(NODES*)0,(COMD_WORD*)&_kwNTRansition
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSTATusCSUMmaryNTRansition};

const NODE _nodeSTATusCSUMmaryPTRansition={
(NODES)&_nodeSTATusCSUMmary ,(NODES*)0,(COMD_WORD*)&_kwPTRansition
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSTATusCSUMmaryPTRansition};

const NODE _nodeSYNC={
(NODES)&_nodeRoot ,(NODES*)_sonSYNC,(COMD_WORD*)&_kwSYNC
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeSYNCWAIT={
(NODES)&_nodeSYNC ,(NODES*)0,(COMD_WORD*)&_kwWAIT
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSYNCWAIT};

const NODE _nodeSYNCDEFault={
(NODES)&_nodeSYNC ,(NODES*)_sonSYNCDEFault,(COMD_WORD*)&_kwDEFault
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeSYNCDEFaultRECall={
(NODES)&_nodeSYNCDEFault ,(NODES*)0,(COMD_WORD*)&_kwRECall
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSYNCDEFaultRECall};

const NODE _nodeSYNCRECall={
(NODES)&_nodeSYNC ,(NODES*)0,(COMD_WORD*)&_kwRECall
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSYNCDEFaultRECall};

const NODE _nodeSYNCCHEaksum={
(NODES)&_nodeSYNC ,(NODES*)0,(COMD_WORD*)&_kwCHEaksum
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idSYNCCHEaksum};

const NODE _nodeCV={
(NODES)&_nodeRoot ,(NODES*)0,(COMD_WORD*)&_kwCV
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCV};

const NODE _nodeSYSTemKLOCk={
(NODES)&_nodeSYSTem ,(NODES*)0,(COMD_WORD*)&_kwKLOCk
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSYSTemKLOCk};

const NODE _nodeCURRentPROTection={
(NODES)&_nodeCURRent ,(NODES*)_sonCURRentPROTection,(COMD_WORD*)&_kwPROTection
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentPROTectionLEVelOVER};

const NODE _nodeCURRentPROTectionLEVel={
(NODES)&_nodeCURRentPROTection ,(NODES*)_sonCURRentPROTectionLEVel,(COMD_WORD*)&_kwLEVel
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentPROTectionLEVelOVER};

const NODE _nodeCURRentPROTectionLEVelOVER={
(NODES)&_nodeCURRentPROTectionLEVel ,(NODES*)0,(COMD_WORD*)&_kwOVER
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentPROTectionLEVelOVER};

const NODE _nodeSOURceCURRentPROTection={
(NODES)&_nodeSOURceCURRent ,(NODES*)_sonSOURceCURRentPROTection,(COMD_WORD*)&_kwPROTection
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentPROTectionLEVelOVER};

const NODE _nodeSOURceCURRentPROTectionLEVel={
(NODES)&_nodeSOURceCURRentPROTection ,(NODES*)_sonSOURceCURRentPROTectionLEVel,(COMD_WORD*)&_kwLEVel
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentPROTectionLEVelOVER};

const NODE _nodeSOURceCURRentPROTectionLEVelOVER={
(NODES)&_nodeSOURceCURRentPROTectionLEVel ,(NODES*)0,(COMD_WORD*)&_kwOVER
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentPROTectionLEVelOVER};

const NODE _nodeSOURceCURRentPROTectionOVER={
(NODES)&_nodeSOURceCURRentPROTection ,(NODES*)0,(COMD_WORD*)&_kwOVER
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentPROTectionLEVelOVER};

const NODE _nodeCURRentPROTectionOVER={
(NODES)&_nodeCURRentPROTection ,(NODES*)0,(COMD_WORD*)&_kwOVER
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentPROTectionLEVelOVER};

const NODE _nodeCURRentPROTectionACTion={
(NODES)&_nodeCURRentPROTection ,(NODES*)0,(COMD_WORD*)&_kwACTion
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentPROTectionACTion};

const NODE _nodeSOURceCURRentPROTectionACTion={
(NODES)&_nodeSOURceCURRentPROTection ,(NODES*)0,(COMD_WORD*)&_kwACTion
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentPROTectionACTion};

const NODE _nodeCURRentRANGe={
(NODES)&_nodeCURRent ,(NODES*)0,(COMD_WORD*)&_kwRANGe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentRANGe};

const NODE _nodeSOURceCURRentRANGe={
(NODES)&_nodeSOURceCURRent ,(NODES*)0,(COMD_WORD*)&_kwRANGe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentRANGe};

const NODE _nodeCURRentLEVelIMMediate={
(NODES)&_nodeCURRentLEVel ,(NODES*)_sonCURRentLEVelIMMediate,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentLEVelIMMediateAMPLitude};

const NODE _nodeCURRentLEVelIMMediateAMPLitude={
(NODES)&_nodeCURRentLEVelIMMediate ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentLEVelIMMediateAMPLitude};

const NODE _nodeSOURceCURRentLEVelIMMediate={
(NODES)&_nodeSOURceCURRentLEVel ,(NODES*)_sonSOURceCURRentLEVelIMMediate,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentLEVelIMMediateAMPLitude};

const NODE _nodeSOURceCURRentLEVelIMMediateAMPLitude={
(NODES)&_nodeSOURceCURRentLEVelIMMediate ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentLEVelIMMediateAMPLitude};

const NODE _nodeSOURceCURRentIMMediate={
(NODES)&_nodeSOURceCURRent ,(NODES*)_sonSOURceCURRentIMMediate,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentLEVelIMMediateAMPLitude};

const NODE _nodeSOURceCURRentIMMediateAMPLitude={
(NODES)&_nodeSOURceCURRentIMMediate ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentLEVelIMMediateAMPLitude};

const NODE _nodeCURRentIMMediate={
(NODES)&_nodeCURRent ,(NODES*)_sonCURRentIMMediate,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentLEVelIMMediateAMPLitude};

const NODE _nodeCURRentIMMediateAMPLitude={
(NODES)&_nodeCURRentIMMediate ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentLEVelIMMediateAMPLitude};

const NODE _nodeSOURceCURRentLEVelAMPLitude={
(NODES)&_nodeSOURceCURRentLEVel ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentLEVelIMMediateAMPLitude};

const NODE _nodeCURRentLEVelAMPLitude={
(NODES)&_nodeCURRentLEVel ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentLEVelIMMediateAMPLitude};

const NODE _nodeSOURceCURRentAMPLitude={
(NODES)&_nodeSOURceCURRent ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentLEVelIMMediateAMPLitude};

const NODE _nodeCURRentAMPLitude={
(NODES)&_nodeCURRent ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentLEVelIMMediateAMPLitude};

const NODE _nodeCURRentSLEW={
(NODES)&_nodeCURRent ,(NODES*)0,(COMD_WORD*)&_kwSLEW
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentSLEW};

const NODE _nodeSOURceCURRentSLEW={
(NODES)&_nodeSOURceCURRent ,(NODES*)0,(COMD_WORD*)&_kwSLEW
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCURRentSLEW};

const NODE _nodePOWerPROTection={
(NODES)&_nodePOWer ,(NODES*)_sonPOWerPROTection,(COMD_WORD*)&_kwPROTection
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerPROTectionLEVelOVER};

const NODE _nodePOWerPROTectionLEVel={
(NODES)&_nodePOWerPROTection ,(NODES*)_sonPOWerPROTectionLEVel,(COMD_WORD*)&_kwLEVel
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerPROTectionLEVelOVER};

const NODE _nodePOWerPROTectionLEVelOVER={
(NODES)&_nodePOWerPROTectionLEVel ,(NODES*)0,(COMD_WORD*)&_kwOVER
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerPROTectionLEVelOVER};

const NODE _nodeSOURcePOWer={
(NODES)&_nodeSOURce ,(NODES*)_sonSOURcePOWer,(COMD_WORD*)&_kwPOWer
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerLEVelIMMediateAMPLitude};

const NODE _nodeSOURcePOWerPROTection={
(NODES)&_nodeSOURcePOWer ,(NODES*)_sonSOURcePOWerPROTection,(COMD_WORD*)&_kwPROTection
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerPROTectionLEVelOVER};

const NODE _nodeSOURcePOWerPROTectionLEVel={
(NODES)&_nodeSOURcePOWerPROTection ,(NODES*)_sonSOURcePOWerPROTectionLEVel,(COMD_WORD*)&_kwLEVel
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerPROTectionLEVelOVER};

const NODE _nodeSOURcePOWerPROTectionLEVelOVER={
(NODES)&_nodeSOURcePOWerPROTectionLEVel ,(NODES*)0,(COMD_WORD*)&_kwOVER
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerPROTectionLEVelOVER};

const NODE _nodeSOURcePOWerPROTectionOVER={
(NODES)&_nodeSOURcePOWerPROTection ,(NODES*)0,(COMD_WORD*)&_kwOVER
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerPROTectionLEVelOVER};

const NODE _nodePOWerPROTectionOVER={
(NODES)&_nodePOWerPROTection ,(NODES*)0,(COMD_WORD*)&_kwOVER
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerPROTectionLEVelOVER};

const NODE _nodePOWerPROTectionACTion={
(NODES)&_nodePOWerPROTection ,(NODES*)0,(COMD_WORD*)&_kwACTion
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerPROTectionACTion};

const NODE _nodeSOURcePOWerPROTectionACTion={
(NODES)&_nodeSOURcePOWerPROTection ,(NODES*)0,(COMD_WORD*)&_kwACTion
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerPROTectionACTion};

const NODE _nodePOWerRANGe={
(NODES)&_nodePOWer ,(NODES*)0,(COMD_WORD*)&_kwRANGe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerRANGe};

const NODE _nodeSOURcePOWerRANGe={
(NODES)&_nodeSOURcePOWer ,(NODES*)0,(COMD_WORD*)&_kwRANGe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerRANGe};

const NODE _nodePOWerLEVel={
(NODES)&_nodePOWer ,(NODES*)_sonPOWerLEVel,(COMD_WORD*)&_kwLEVel
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerLEVelIMMediateAMPLitude};

const NODE _nodePOWerLEVelIMMediate={
(NODES)&_nodePOWerLEVel ,(NODES*)_sonPOWerLEVelIMMediate,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerLEVelIMMediateAMPLitude};

const NODE _nodePOWerLEVelIMMediateAMPLitude={
(NODES)&_nodePOWerLEVelIMMediate ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerLEVelIMMediateAMPLitude};

const NODE _nodeSOURcePOWerLEVel={
(NODES)&_nodeSOURcePOWer ,(NODES*)_sonSOURcePOWerLEVel,(COMD_WORD*)&_kwLEVel
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerLEVelIMMediateAMPLitude};

const NODE _nodeSOURcePOWerLEVelIMMediate={
(NODES)&_nodeSOURcePOWerLEVel ,(NODES*)_sonSOURcePOWerLEVelIMMediate,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerLEVelIMMediateAMPLitude};

const NODE _nodeSOURcePOWerLEVelIMMediateAMPLitude={
(NODES)&_nodeSOURcePOWerLEVelIMMediate ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerLEVelIMMediateAMPLitude};

const NODE _nodeSOURcePOWerIMMediate={
(NODES)&_nodeSOURcePOWer ,(NODES*)_sonSOURcePOWerIMMediate,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerLEVelIMMediateAMPLitude};

const NODE _nodeSOURcePOWerIMMediateAMPLitude={
(NODES)&_nodeSOURcePOWerIMMediate ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerLEVelIMMediateAMPLitude};

const NODE _nodePOWerIMMediate={
(NODES)&_nodePOWer ,(NODES*)_sonPOWerIMMediate,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerLEVelIMMediateAMPLitude};

const NODE _nodePOWerIMMediateAMPLitude={
(NODES)&_nodePOWerIMMediate ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerLEVelIMMediateAMPLitude};

const NODE _nodeSOURcePOWerLEVelAMPLitude={
(NODES)&_nodeSOURcePOWerLEVel ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerLEVelIMMediateAMPLitude};

const NODE _nodePOWerLEVelAMPLitude={
(NODES)&_nodePOWerLEVel ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerLEVelIMMediateAMPLitude};

const NODE _nodeSOURcePOWerAMPLitude={
(NODES)&_nodeSOURcePOWer ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerLEVelIMMediateAMPLitude};

const NODE _nodePOWerAMPLitude={
(NODES)&_nodePOWer ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURcePOWerLEVelIMMediateAMPLitude};

const NODE _nodeCONDuctanceLEVel={
(NODES)&_nodeCONDuctance ,(NODES*)_sonCONDuctanceLEVel,(COMD_WORD*)&_kwLEVel
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCONDuctanceLEVelIMMediateAMPLitude};

const NODE _nodeCONDuctanceLEVelIMMediate={
(NODES)&_nodeCONDuctanceLEVel ,(NODES*)_sonCONDuctanceLEVelIMMediate,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCONDuctanceLEVelIMMediateAMPLitude};

const NODE _nodeCONDuctanceLEVelIMMediateAMPLitude={
(NODES)&_nodeCONDuctanceLEVelIMMediate ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCONDuctanceLEVelIMMediateAMPLitude};

const NODE _nodeSOURceCONDuctanceLEVel={
(NODES)&_nodeSOURceCONDuctance ,(NODES*)_sonSOURceCONDuctanceLEVel,(COMD_WORD*)&_kwLEVel
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCONDuctanceLEVelIMMediateAMPLitude};

const NODE _nodeSOURceCONDuctanceLEVelIMMediate={
(NODES)&_nodeSOURceCONDuctanceLEVel ,(NODES*)_sonSOURceCONDuctanceLEVelIMMediate,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCONDuctanceLEVelIMMediateAMPLitude};

const NODE _nodeSOURceCONDuctanceLEVelIMMediateAMPLitude={
(NODES)&_nodeSOURceCONDuctanceLEVelIMMediate ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCONDuctanceLEVelIMMediateAMPLitude};

const NODE _nodeSOURceCONDuctanceIMMediate={
(NODES)&_nodeSOURceCONDuctance ,(NODES*)_sonSOURceCONDuctanceIMMediate,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCONDuctanceLEVelIMMediateAMPLitude};

const NODE _nodeSOURceCONDuctanceIMMediateAMPLitude={
(NODES)&_nodeSOURceCONDuctanceIMMediate ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCONDuctanceLEVelIMMediateAMPLitude};

const NODE _nodeCONDuctanceIMMediate={
(NODES)&_nodeCONDuctance ,(NODES*)_sonCONDuctanceIMMediate,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCONDuctanceLEVelIMMediateAMPLitude};

const NODE _nodeCONDuctanceIMMediateAMPLitude={
(NODES)&_nodeCONDuctanceIMMediate ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCONDuctanceLEVelIMMediateAMPLitude};

const NODE _nodeSOURceCONDuctanceLEVelAMPLitude={
(NODES)&_nodeSOURceCONDuctanceLEVel ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCONDuctanceLEVelIMMediateAMPLitude};

const NODE _nodeCONDuctanceLEVelAMPLitude={
(NODES)&_nodeCONDuctanceLEVel ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCONDuctanceLEVelIMMediateAMPLitude};

const NODE _nodeSOURceCONDuctanceAMPLitude={
(NODES)&_nodeSOURceCONDuctance ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCONDuctanceLEVelIMMediateAMPLitude};

const NODE _nodeCONDuctanceAMPLitude={
(NODES)&_nodeCONDuctance ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCONDuctanceLEVelIMMediateAMPLitude};

const NODE _nodeCONDuctanceRANGe={
(NODES)&_nodeCONDuctance ,(NODES*)0,(COMD_WORD*)&_kwRANGe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCONDuctanceRANGe};

const NODE _nodeSOURceCONDuctanceRANGe={
(NODES)&_nodeSOURceCONDuctance ,(NODES*)0,(COMD_WORD*)&_kwRANGe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceCONDuctanceRANGe};

const NODE _nodeVOLTagePROTection={
(NODES)&_nodeVOLTage ,(NODES*)_sonVOLTagePROTection,(COMD_WORD*)&_kwPROTection
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTagePROTectionLEVelUNDer};

const NODE _nodeVOLTagePROTectionLEVel={
(NODES)&_nodeVOLTagePROTection ,(NODES*)_sonVOLTagePROTectionLEVel,(COMD_WORD*)&_kwLEVel
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTagePROTectionLEVelUNDer};

const NODE _nodeVOLTagePROTectionLEVelUNDer={
(NODES)&_nodeVOLTagePROTectionLEVel ,(NODES*)0,(COMD_WORD*)&_kwUNDer
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTagePROTectionLEVelUNDer};

const NODE _nodeSOURceVOLTage={
(NODES)&_nodeSOURce ,(NODES*)_sonSOURceVOLTage,(COMD_WORD*)&_kwVOLTage
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTageLEVelIMMediateAMPLitude};

const NODE _nodeSOURceVOLTagePROTection={
(NODES)&_nodeSOURceVOLTage ,(NODES*)_sonSOURceVOLTagePROTection,(COMD_WORD*)&_kwPROTection
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTagePROTectionLEVelUNDer};

const NODE _nodeSOURceVOLTagePROTectionLEVel={
(NODES)&_nodeSOURceVOLTagePROTection ,(NODES*)_sonSOURceVOLTagePROTectionLEVel,(COMD_WORD*)&_kwLEVel
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTagePROTectionLEVelUNDer};

const NODE _nodeSOURceVOLTagePROTectionLEVelUNDer={
(NODES)&_nodeSOURceVOLTagePROTectionLEVel ,(NODES*)0,(COMD_WORD*)&_kwUNDer
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTagePROTectionLEVelUNDer};

const NODE _nodeSOURceVOLTagePROTectionUNDer={
(NODES)&_nodeSOURceVOLTagePROTection ,(NODES*)0,(COMD_WORD*)&_kwUNDer
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTagePROTectionLEVelUNDer};

const NODE _nodeVOLTagePROTectionUNDer={
(NODES)&_nodeVOLTagePROTection ,(NODES*)0,(COMD_WORD*)&_kwUNDer
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTagePROTectionLEVelUNDer};

const NODE _nodeVOLTageLEVel={
(NODES)&_nodeVOLTage ,(NODES*)_sonVOLTageLEVel,(COMD_WORD*)&_kwLEVel
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTageLEVelIMMediateAMPLitude};

const NODE _nodeVOLTageLEVelIMMediate={
(NODES)&_nodeVOLTageLEVel ,(NODES*)_sonVOLTageLEVelIMMediate,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTageLEVelIMMediateAMPLitude};

const NODE _nodeVOLTageLEVelIMMediateAMPLitude={
(NODES)&_nodeVOLTageLEVelIMMediate ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTageLEVelIMMediateAMPLitude};

const NODE _nodeSOURceVOLTageLEVel={
(NODES)&_nodeSOURceVOLTage ,(NODES*)_sonSOURceVOLTageLEVel,(COMD_WORD*)&_kwLEVel
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTageLEVelIMMediateAMPLitude};

const NODE _nodeSOURceVOLTageLEVelIMMediate={
(NODES)&_nodeSOURceVOLTageLEVel ,(NODES*)_sonSOURceVOLTageLEVelIMMediate,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTageLEVelIMMediateAMPLitude};

const NODE _nodeSOURceVOLTageLEVelIMMediateAMPLitude={
(NODES)&_nodeSOURceVOLTageLEVelIMMediate ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTageLEVelIMMediateAMPLitude};

const NODE _nodeSOURceVOLTageIMMediate={
(NODES)&_nodeSOURceVOLTage ,(NODES*)_sonSOURceVOLTageIMMediate,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTageLEVelIMMediateAMPLitude};

const NODE _nodeSOURceVOLTageIMMediateAMPLitude={
(NODES)&_nodeSOURceVOLTageIMMediate ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTageLEVelIMMediateAMPLitude};

const NODE _nodeVOLTageIMMediate={
(NODES)&_nodeVOLTage ,(NODES*)_sonVOLTageIMMediate,(COMD_WORD*)&_kwIMMediate
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTageLEVelIMMediateAMPLitude};

const NODE _nodeVOLTageIMMediateAMPLitude={
(NODES)&_nodeVOLTageIMMediate ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTageLEVelIMMediateAMPLitude};

const NODE _nodeSOURceVOLTageLEVelAMPLitude={
(NODES)&_nodeSOURceVOLTageLEVel ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTageLEVelIMMediateAMPLitude};

const NODE _nodeVOLTageLEVelAMPLitude={
(NODES)&_nodeVOLTageLEVel ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTageLEVelIMMediateAMPLitude};

const NODE _nodeSOURceVOLTageAMPLitude={
(NODES)&_nodeSOURceVOLTage ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTageLEVelIMMediateAMPLitude};

const NODE _nodeVOLTageAMPLitude={
(NODES)&_nodeVOLTage ,(NODES*)0,(COMD_WORD*)&_kwAMPLitude
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTageLEVelIMMediateAMPLitude};

const NODE _nodeVOLTagePROTectionSTATe={
(NODES)&_nodeVOLTagePROTection ,(NODES*)0,(COMD_WORD*)&_kwSTATe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTagePROTectionSTATe};

const NODE _nodeSOURceVOLTagePROTectionSTATe={
(NODES)&_nodeSOURceVOLTagePROTection ,(NODES*)0,(COMD_WORD*)&_kwSTATe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTagePROTectionSTATe};

const NODE _nodeVOLTageRANGe={
(NODES)&_nodeVOLTage ,(NODES*)0,(COMD_WORD*)&_kwRANGe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTageRANGe};

const NODE _nodeSOURceVOLTageRANGe={
(NODES)&_nodeSOURceVOLTage ,(NODES*)0,(COMD_WORD*)&_kwRANGe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceVOLTageRANGe};

const NODE _nodeFUNCtionSSTart={
(NODES)&_nodeFUNCtion ,(NODES*)0,(COMD_WORD*)&_kwSSTart
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceFUNCtionSSTart};

const NODE _nodeSOURceFUNCtion={
(NODES)&_nodeSOURce ,(NODES*)_sonSOURceFUNCtion,(COMD_WORD*)&_kwFUNCtion
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceFUNCtionMODE};

const NODE _nodeSOURceFUNCtionSSTart={
(NODES)&_nodeSOURceFUNCtion ,(NODES*)0,(COMD_WORD*)&_kwSSTart
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceFUNCtionSSTart};

const NODE _nodeFUNCtionRESPonse={
(NODES)&_nodeFUNCtion ,(NODES*)0,(COMD_WORD*)&_kwRESPonse
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceFUNCtionRESPonse};

const NODE _nodeSOURceFUNCtionRESPonse={
(NODES)&_nodeSOURceFUNCtion ,(NODES*)0,(COMD_WORD*)&_kwRESPonse
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceFUNCtionRESPonse};

const NODE _nodeFUNCtionCTIMe={
(NODES)&_nodeFUNCtion ,(NODES*)0,(COMD_WORD*)&_kwCTIMe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceFUNCtionCTIMe};

const NODE _nodeSOURceFUNCtionCTIMe={
(NODES)&_nodeSOURceFUNCtion ,(NODES*)0,(COMD_WORD*)&_kwCTIMe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idSOURceFUNCtionCTIMe};

const NODE _nodeFUNCtionMODE={
(NODES)&_nodeFUNCtion ,(NODES*)0,(COMD_WORD*)&_kwMODE
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceFUNCtionMODE};

const NODE _nodeSOURceFUNCtionMODE={
(NODES)&_nodeSOURceFUNCtion ,(NODES*)0,(COMD_WORD*)&_kwMODE
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSOURceFUNCtionMODE};

const NODE _nodeCLEar={
(NODES)&_nodeRoot ,(NODES*)0,(COMD_WORD*)&_kwCLEar
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramCLEar};

const NODE _nodeSTATe={
(NODES)&_nodeRoot ,(NODES*)0,(COMD_WORD*)&_kwSTATe
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedSTATe};

const NODE _nodeSELected={
(NODES)&_nodeRoot ,(NODES*)_sonSELected,(COMD_WORD*)&_kwSELected
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeSELectedSTATe={
(NODES)&_nodeSELected ,(NODES*)0,(COMD_WORD*)&_kwSTATe
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedSTATe};

const NODE _nodeEXECuting={
(NODES)&_nodeRoot ,(NODES*)0,(COMD_WORD*)&_kwEXECuting
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idPROGramSELectedEXECuting};

const NODE _nodeSELectedEXECuting={
(NODES)&_nodeSELected ,(NODES*)0,(COMD_WORD*)&_kwEXECuting
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idPROGramSELectedEXECuting};

const NODE _nodePROGramSELected={
(NODES)&_nodePROGram ,(NODES*)_sonPROGramSELected,(COMD_WORD*)&_kwSELected
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodePROGramSELectedNAME={
(NODES)&_nodePROGramSELected ,(NODES*)0,(COMD_WORD*)&_kwNAME
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNAME};

const NODE _nodePROGramNAME={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwNAME
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNAME};

const NODE _nodePROGramSELectedMEMO={
(NODES)&_nodePROGramSELected ,(NODES*)0,(COMD_WORD*)&_kwMEMO
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedMEMO};

const NODE _nodePROGramMEMO={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwMEMO
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedMEMO};

const NODE _nodePROGramSELectedMODE={
(NODES)&_nodePROGramSELected ,(NODES*)0,(COMD_WORD*)&_kwMODE
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedMODE};

const NODE _nodePROGramMODE={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwMODE
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedMODE};

const NODE _nodePROGramSELectedVRANge={
(NODES)&_nodePROGramSELected ,(NODES*)0,(COMD_WORD*)&_kwVRANge
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedVRANge};

const NODE _nodePROGramVRANge={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwVRANge
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedVRANge};

const NODE _nodePROGramSELectedCRANge={
(NODES)&_nodePROGramSELected ,(NODES*)0,(COMD_WORD*)&_kwCRANge
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedCRANge};

const NODE _nodePROGramCRANge={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwCRANge
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedCRANge};

const NODE _nodePROGramSELectedLOOP={
(NODES)&_nodePROGramSELected ,(NODES*)0,(COMD_WORD*)&_kwLOOP
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedLOOP};

const NODE _nodePROGramLOOP={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwLOOP
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedLOOP};

const NODE _nodePROGramSELectedLINPut={
(NODES)&_nodePROGramSELected ,(NODES*)0,(COMD_WORD*)&_kwLINPut
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedLINPut};

const NODE _nodePROGramLINPut={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwLINPut
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedLINPut};

const NODE _nodePROGramSELectedLOUTput={
(NODES)&_nodePROGramSELected ,(NODES*)0,(COMD_WORD*)&_kwLOUTput
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedLOUTput};

const NODE _nodePROGramLOUTput={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwLOUTput
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedLOUTput};

const NODE _nodePROGramSELectedLVALue={
(NODES)&_nodePROGramSELected ,(NODES*)0,(COMD_WORD*)&_kwLVALue
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedLVALue};

const NODE _nodePROGramLVALue={
(NODES)&_nodePROGram ,(NODES*)0,(COMD_WORD*)&_kwLVALue
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedLVALue};

const NODE _nodePROGramSELectedCHAin={
(NODES)&_nodePROGramSELected ,(NODES*)0,(COMD_WORD*)&_kwCHAin
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedCHAin};

const NODE _nodePROGramSELectedNSPeed={
(NODES)&_nodePROGramSELected ,(NODES*)_sonPROGramSELectedNSPeed,(COMD_WORD*)&_kwNSPeed
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodePROGramSELectedNSPeedSTEP={
(NODES)&_nodePROGramSELectedNSPeed ,(NODES*)_sonPROGramSELectedNSPeedSTEP,(COMD_WORD*)&_kwSTEP
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodePROGramSELectedNSPeedSTEPINSert={
(NODES)&_nodePROGramSELectedNSPeedSTEP ,(NODES*)0,(COMD_WORD*)&_kwINSert
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPINSert};

const NODE _nodePROGramNSPeed={
(NODES)&_nodePROGram ,(NODES*)_sonPROGramNSPeed,(COMD_WORD*)&_kwNSPeed
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodePROGramNSPeedSTEP={
(NODES)&_nodePROGramNSPeed ,(NODES*)_sonPROGramNSPeedSTEP,(COMD_WORD*)&_kwSTEP
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodePROGramNSPeedSTEPINSert={
(NODES)&_nodePROGramNSPeedSTEP ,(NODES*)0,(COMD_WORD*)&_kwINSert
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPINSert};

const NODE _nodePROGramSELectedNSPeedINSert={
(NODES)&_nodePROGramSELectedNSPeed ,(NODES*)0,(COMD_WORD*)&_kwINSert
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPINSert};

const NODE _nodePROGramNSPeedINSert={
(NODES)&_nodePROGramNSPeed ,(NODES*)0,(COMD_WORD*)&_kwINSert
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPINSert};

const NODE _nodePROGramSELectedNSPeedSTEPADD={
(NODES)&_nodePROGramSELectedNSPeedSTEP ,(NODES*)0,(COMD_WORD*)&_kwADD
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPADD};

const NODE _nodePROGramNSPeedSTEPADD={
(NODES)&_nodePROGramNSPeedSTEP ,(NODES*)0,(COMD_WORD*)&_kwADD
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPADD};

const NODE _nodePROGramSELectedNSPeedADD={
(NODES)&_nodePROGramSELectedNSPeed ,(NODES*)0,(COMD_WORD*)&_kwADD
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPADD};

const NODE _nodePROGramNSPeedADD={
(NODES)&_nodePROGramNSPeed ,(NODES*)0,(COMD_WORD*)&_kwADD
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPADD};

const NODE _nodePROGramSELectedNSPeedSTEPDELete={
(NODES)&_nodePROGramSELectedNSPeedSTEP ,(NODES*)_sonPROGramSELectedNSPeedSTEPDELete,(COMD_WORD*)&_kwDELete
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPDELete};

const NODE _nodePROGramNSPeedSTEPDELete={
(NODES)&_nodePROGramNSPeedSTEP ,(NODES*)_sonPROGramNSPeedSTEPDELete,(COMD_WORD*)&_kwDELete
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPDELete};

const NODE _nodePROGramSELectedNSPeedDELete={
(NODES)&_nodePROGramSELectedNSPeed ,(NODES*)_sonPROGramSELectedNSPeedDELete,(COMD_WORD*)&_kwDELete
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPDELete};

const NODE _nodePROGramNSPeedDELete={
(NODES)&_nodePROGramNSPeed ,(NODES*)_sonPROGramNSPeedDELete,(COMD_WORD*)&_kwDELete
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPDELete};

const NODE _nodePROGramSELectedNSPeedSTEPDELeteALL={
(NODES)&_nodePROGramSELectedNSPeedSTEPDELete ,(NODES*)0,(COMD_WORD*)&_kwALL
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPDELeteALL};

const NODE _nodePROGramNSPeedSTEPDELeteALL={
(NODES)&_nodePROGramNSPeedSTEPDELete ,(NODES*)0,(COMD_WORD*)&_kwALL
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPDELeteALL};

const NODE _nodePROGramSELectedNSPeedDELeteALL={
(NODES)&_nodePROGramSELectedNSPeedDELete ,(NODES*)0,(COMD_WORD*)&_kwALL
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPDELeteALL};

const NODE _nodePROGramNSPeedDELeteALL={
(NODES)&_nodePROGramNSPeedDELete ,(NODES*)0,(COMD_WORD*)&_kwALL
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPDELeteALL};

const NODE _nodePROGramSELectedNSPeedSTEPCOUNt={
(NODES)&_nodePROGramSELectedNSPeedSTEP ,(NODES*)0,(COMD_WORD*)&_kwCOUNt
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idPROGramSELectedNSPeedSTEPCOUNt};

const NODE _nodePROGramNSPeedSTEPCOUNt={
(NODES)&_nodePROGramNSPeedSTEP ,(NODES*)0,(COMD_WORD*)&_kwCOUNt
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idPROGramSELectedNSPeedSTEPCOUNt};

const NODE _nodePROGramSELectedNSPeedCOUNt={
(NODES)&_nodePROGramSELectedNSPeed ,(NODES*)0,(COMD_WORD*)&_kwCOUNt
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idPROGramSELectedNSPeedSTEPCOUNt};

const NODE _nodePROGramNSPeedCOUNt={
(NODES)&_nodePROGramNSPeed ,(NODES*)0,(COMD_WORD*)&_kwCOUNt
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idPROGramSELectedNSPeedSTEPCOUNt};

const NODE _nodePROGramSELectedNSPeedSTEPEDIT={
(NODES)&_nodePROGramSELectedNSPeedSTEP ,(NODES*)0,(COMD_WORD*)&_kwEDIT
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPEDIT};

const NODE _nodePROGramNSPeedSTEPEDIT={
(NODES)&_nodePROGramNSPeedSTEP ,(NODES*)0,(COMD_WORD*)&_kwEDIT
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPEDIT};

const NODE _nodePROGramSELectedNSPeedEDIT={
(NODES)&_nodePROGramSELectedNSPeed ,(NODES*)0,(COMD_WORD*)&_kwEDIT
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPEDIT};

const NODE _nodePROGramNSPeedEDIT={
(NODES)&_nodePROGramNSPeed ,(NODES*)0,(COMD_WORD*)&_kwEDIT
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedNSPeedSTEPEDIT};

const NODE _nodePROGramSELectedFSPeed={
(NODES)&_nodePROGramSELected ,(NODES*)_sonPROGramSELectedFSPeed,(COMD_WORD*)&_kwFSPeed
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodePROGramSELectedFSPeedSTEP={
(NODES)&_nodePROGramSELectedFSPeed ,(NODES*)_sonPROGramSELectedFSPeedSTEP,(COMD_WORD*)&_kwSTEP
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodePROGramSELectedFSPeedSTEPEND={
(NODES)&_nodePROGramSELectedFSPeedSTEP ,(NODES*)0,(COMD_WORD*)&_kwEND
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedFSPeedSTEPEND};

const NODE _nodePROGramFSPeed={
(NODES)&_nodePROGram ,(NODES*)_sonPROGramFSPeed,(COMD_WORD*)&_kwFSPeed
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodePROGramFSPeedSTEP={
(NODES)&_nodePROGramFSPeed ,(NODES*)_sonPROGramFSPeedSTEP,(COMD_WORD*)&_kwSTEP
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodePROGramFSPeedSTEPEND={
(NODES)&_nodePROGramFSPeedSTEP ,(NODES*)0,(COMD_WORD*)&_kwEND
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedFSPeedSTEPEND};

const NODE _nodePROGramSELectedFSPeedEND={
(NODES)&_nodePROGramSELectedFSPeed ,(NODES*)0,(COMD_WORD*)&_kwEND
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedFSPeedSTEPEND};

const NODE _nodePROGramFSPeedEND={
(NODES)&_nodePROGramFSPeed ,(NODES*)0,(COMD_WORD*)&_kwEND
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedFSPeedSTEPEND};

const NODE _nodePROGramSELectedFSPeedSTEPEDIT={
(NODES)&_nodePROGramSELectedFSPeedSTEP ,(NODES*)_sonPROGramSELectedFSPeedSTEPEDIT,(COMD_WORD*)&_kwEDIT
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedFSPeedSTEPEDITPOINt};

const NODE _nodePROGramSELectedFSPeedSTEPEDITPOINt={
(NODES)&_nodePROGramSELectedFSPeedSTEPEDIT ,(NODES*)0,(COMD_WORD*)&_kwPOINt
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedFSPeedSTEPEDITPOINt};

const NODE _nodePROGramFSPeedSTEPEDIT={
(NODES)&_nodePROGramFSPeedSTEP ,(NODES*)_sonPROGramFSPeedSTEPEDIT,(COMD_WORD*)&_kwEDIT
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedFSPeedSTEPEDITPOINt};

const NODE _nodePROGramFSPeedSTEPEDITPOINt={
(NODES)&_nodePROGramFSPeedSTEPEDIT ,(NODES*)0,(COMD_WORD*)&_kwPOINt
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedFSPeedSTEPEDITPOINt};

const NODE _nodePROGramSELectedFSPeedEDIT={
(NODES)&_nodePROGramSELectedFSPeed ,(NODES*)_sonPROGramSELectedFSPeedEDIT,(COMD_WORD*)&_kwEDIT
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedFSPeedSTEPEDITPOINt};

const NODE _nodePROGramSELectedFSPeedEDITPOINt={
(NODES)&_nodePROGramSELectedFSPeedEDIT ,(NODES*)0,(COMD_WORD*)&_kwPOINt
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedFSPeedSTEPEDITPOINt};

const NODE _nodePROGramFSPeedEDIT={
(NODES)&_nodePROGramFSPeed ,(NODES*)_sonPROGramFSPeedEDIT,(COMD_WORD*)&_kwEDIT
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedFSPeedSTEPEDITPOINt};

const NODE _nodePROGramFSPeedEDITPOINt={
(NODES)&_nodePROGramFSPeedEDIT ,(NODES*)0,(COMD_WORD*)&_kwPOINt
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedFSPeedSTEPEDITPOINt};

const NODE _nodePROGramSELectedFSPeedTIME={
(NODES)&_nodePROGramSELectedFSPeed ,(NODES*)0,(COMD_WORD*)&_kwTIME
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedFSPeedTIME};

const NODE _nodePROGramFSPeedTIME={
(NODES)&_nodePROGramFSPeed ,(NODES*)0,(COMD_WORD*)&_kwTIME
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idPROGramSELectedFSPeedTIME};

const NODE _nodePROGramSELectedFSPeedSTEPEDITLINear={
(NODES)&_nodePROGramSELectedFSPeedSTEPEDIT ,(NODES*)0,(COMD_WORD*)&_kwLINear
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedFSPeedSTEPEDITLINear};

const NODE _nodePROGramFSPeedSTEPEDITLINear={
(NODES)&_nodePROGramFSPeedSTEPEDIT ,(NODES*)0,(COMD_WORD*)&_kwLINear
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedFSPeedSTEPEDITLINear};

const NODE _nodePROGramSELectedFSPeedEDITLINear={
(NODES)&_nodePROGramSELectedFSPeedEDIT ,(NODES*)0,(COMD_WORD*)&_kwLINear
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedFSPeedSTEPEDITLINear};

const NODE _nodePROGramFSPeedEDITLINear={
(NODES)&_nodePROGramFSPeedEDIT ,(NODES*)0,(COMD_WORD*)&_kwLINear
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedFSPeedSTEPEDITLINear};

const NODE _nodePROGramSELectedFSPeedSTEPEDITWAVE={
(NODES)&_nodePROGramSELectedFSPeedSTEPEDIT ,(NODES*)0,(COMD_WORD*)&_kwWAVE
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedFSPeedSTEPEDITWAVE};

const NODE _nodePROGramFSPeedSTEPEDITWAVE={
(NODES)&_nodePROGramFSPeedSTEPEDIT ,(NODES*)0,(COMD_WORD*)&_kwWAVE
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedFSPeedSTEPEDITWAVE};

const NODE _nodePROGramSELectedFSPeedEDITWAVE={
(NODES)&_nodePROGramSELectedFSPeedEDIT ,(NODES*)0,(COMD_WORD*)&_kwWAVE
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedFSPeedSTEPEDITWAVE};

const NODE _nodePROGramFSPeedEDITWAVE={
(NODES)&_nodePROGramFSPeedEDIT ,(NODES*)0,(COMD_WORD*)&_kwWAVE
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idPROGramSELectedFSPeedSTEPEDITWAVE};

const NODE _nodeSYSTemGTLocal={
(NODES)&_nodeSYSTem ,(NODES*)0,(COMD_WORD*)&_kwGTLocal
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSYSTemGTLocal};

const NODE _nodeSYSTemLLOut={
(NODES)&_nodeSYSTem ,(NODES*)0,(COMD_WORD*)&_kwLLOut
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSYSTemLLOut};

const NODE _nodeSYSTemRENable={
(NODES)&_nodeSYSTem ,(NODES*)0,(COMD_WORD*)&_kwRENable
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idSYSTemRENable};

const NODE _nodeSYSTemVERSion={
(NODES)&_nodeSYSTem ,(NODES*)0,(COMD_WORD*)&_kwVERSion
,(COMD_SUFFIX*)&_cpNull,(char)T__Q_,(unsigned int)_idSYSTemVERSion};

const NODE _nodeCALibrate={
(NODES)&_nodeRoot ,(NODES*)_sonCALibrate,(COMD_WORD*)&_kwCALibrate
,(COMD_SUFFIX*)&_cpNull,(char)T____,(unsigned int)0};

const NODE _nodeCALibratePASSword={
(NODES)&_nodeCALibrate ,(NODES*)0,(COMD_WORD*)&_kwPASSword
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idCALibratePASSword};

const NODE _nodeCALibrateMODE={
(NODES)&_nodeCALibrate ,(NODES*)0,(COMD_WORD*)&_kwMODE
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCALibrateMODE};

const NODE _nodeCALibrateRANGe={
(NODES)&_nodeCALibrate ,(NODES*)0,(COMD_WORD*)&_kwRANGe
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCALibrateRANGe};

const NODE _nodeCALibrateLEVel={
(NODES)&_nodeCALibrate ,(NODES*)0,(COMD_WORD*)&_kwLEVel
,(COMD_SUFFIX*)&_cpNull,(char)T__QS,(unsigned int)_idCALibrateLEVel};

const NODE _nodeCALibrateVALue={
(NODES)&_nodeCALibrate ,(NODES*)0,(COMD_WORD*)&_kwVALue
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idCALibrateVALue};

const NODE _nodeCALibrateBIValue={
(NODES)&_nodeCALibrate ,(NODES*)0,(COMD_WORD*)&_kwBIValue
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idCALibrateBIValue};

const NODE _nodeCALibrateRUN={
(NODES)&_nodeCALibrate ,(NODES*)0,(COMD_WORD*)&_kwRUN
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idCALibrateRUN};

const NODE _nodeCALibratePSENsor={
(NODES)&_nodeCALibrate ,(NODES*)0,(COMD_WORD*)&_kwPSENsor
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idCALibratePSENsor};

const NODE _nodeCALibrateSAVE={
(NODES)&_nodeCALibrate ,(NODES*)0,(COMD_WORD*)&_kwSAVE
,(COMD_SUFFIX*)&_cpNull,(char)T___S,(unsigned int)_idCALibrateSAVE};

//Create sonRoot
const NODES _sonRoot[]={
(NODES)&_nodeABORt,(NODES)&_nodeSYSTem,(NODES)&_nodeINPut,(NODES)&_nodeOUTPut,(NODES)&_nodeINITiate,
(NODES)&_nodeCURRent,(NODES)&_nodeSOURce,(NODES)&_nodeRESistance,(NODES)&_nodeCONDuctance,(NODES)&_nodeTRIGger,
(NODES)&_nodeSHORt,(NODES)&_nodeOUTPup,(NODES)&_nodeMEASure,(NODES)&_nodeFETCh,(NODES)&_nodeOCP,
(NODES)&_nodeCONFigure,(NODES)&_nodeOPP,(NODES)&_nodeUVP,(NODES)&_nodeOVP,(NODES)&_nodeSSTart,
(NODES)&_nodeVON,(NODES)&_nodeVDELay,(NODES)&_nodeCNTime,(NODES)&_nodeCOTime,(NODES)&_nodeCRUNit,
(NODES)&_nodeGNG,(NODES)&_nodeSTEP,(NODES)&_nodeEXTernal,(NODES)&_nodeMODE,(NODES)&_nodeCRANge,
(NODES)&_nodeVRANge,(NODES)&_nodeDYNamic,(NODES)&_nodeVOLTage,(NODES)&_nodePOWer,(NODES)&_nodeFUNCtion,
(NODES)&_nodePROGram,(NODES)&_nodeCHAin,(NODES)&_nodeSEQuence,(NODES)&_nodeNSEQuence,(NODES)&_nodeFSEQuence,
(NODES)&_nodeUTILity,(NODES)&_nodeMEMory,(NODES)&_nodePRESet,(NODES)&_nodeSETup,(NODES)&_nodeFACTory,
(NODES)&_nodeUSER,(NODES)&_nodeSERial,(NODES)&_nodeSTATus,(NODES)&_nodeSYNC,(NODES)&_nodeCV,
(NODES)&_nodeCLEar,(NODES)&_nodeSTATe,(NODES)&_nodeSELected,(NODES)&_nodeEXECuting,(NODES)&_nodeCALibrate,
(NODES) 0 };


//Create sonNodes
const NODES _sonSYSTem[]={
(NODES)&_nodeSYSTemERRor,
(NODES)&_nodeSYSTemKLOCk,
(NODES)&_nodeSYSTemGTLocal,
(NODES)&_nodeSYSTemLLOut,
(NODES)&_nodeSYSTemRENable,
(NODES)&_nodeSYSTemVERSion,
(NODES) 0 };

const NODES _sonSYSTemERRor[]={
(NODES)&_nodeSYSTemERRorNEXT,
(NODES) 0 };

const NODES _sonINPut[]={
(NODES)&_nodeINPutSTATe,
(NODES)&_nodeINPutTRIGgered,
(NODES)&_nodeINPutIMMediate,
(NODES)&_nodeINPutSHORt,
(NODES)&_nodeINPutPROTection,
(NODES)&_nodeINPutTIMer,
(NODES)&_nodeINPutMODE,
(NODES) 0 };

const NODES _sonINPutSTATe[]={
(NODES)&_nodeINPutSTATeTRIGgered,
(NODES)&_nodeINPutSTATeIMMediate,
(NODES)&_nodeINPutSTATeTIMer,
(NODES) 0 };

const NODES _sonOUTPut[]={
(NODES)&_nodeOUTPutSTATe,
(NODES)&_nodeOUTPutTRIGgered,
(NODES)&_nodeOUTPutIMMediate,
(NODES)&_nodeOUTPutPROTection,
(NODES)&_nodeOUTPutTIMer,
(NODES) 0 };

const NODES _sonOUTPutSTATe[]={
(NODES)&_nodeOUTPutSTATeTRIGgered,
(NODES)&_nodeOUTPutSTATeIMMediate,
(NODES)&_nodeOUTPutSTATeTIMer,
(NODES) 0 };

const NODES _sonINITiate[]={
(NODES)&_nodeINITiateIMMediate,
(NODES)&_nodeINITiateCONTinuous,
(NODES) 0 };

const NODES _sonCURRent[]={
(NODES)&_nodeCURRentLEVel,
(NODES)&_nodeCURRentVA,
(NODES)&_nodeCURRentTRIGgered,
(NODES)&_nodeCURRentRECall,
(NODES)&_nodeCURRentVB,
(NODES)&_nodeCURRentSRATe,
(NODES)&_nodeCURRentL12,
(NODES)&_nodeCURRentSET,
(NODES)&_nodeCURRentRISE,
(NODES)&_nodeCURRentFALL,
(NODES)&_nodeCURRentT12,
(NODES)&_nodeCURRentFREQuency,
(NODES)&_nodeCURRentDUTY,
(NODES)&_nodeCURRentCV,
(NODES)&_nodeCURRentPROTection,
(NODES)&_nodeCURRentRANGe,
(NODES)&_nodeCURRentIMMediate,
(NODES)&_nodeCURRentAMPLitude,
(NODES)&_nodeCURRentSLEW,
(NODES) 0 };

const NODES _sonCURRentLEVel[]={
(NODES)&_nodeCURRentLEVelVA,
(NODES)&_nodeCURRentLEVelTRIGgered,
(NODES)&_nodeCURRentLEVelIMMediate,
(NODES)&_nodeCURRentLEVelAMPLitude,
(NODES) 0 };

const NODES _sonCURRentLEVelVA[]={
(NODES)&_nodeCURRentLEVelVATRIGgered,
(NODES) 0 };

const NODES _sonCURRentLEVelVATRIGgered[]={
(NODES)&_nodeCURRentLEVelVATRIGgeredAMPLitude,
(NODES) 0 };

const NODES _sonSOURce[]={
(NODES)&_nodeSOURceCURRent,
(NODES)&_nodeSOURceCONDuctance,
(NODES)&_nodeSOURcePOWer,
(NODES)&_nodeSOURceVOLTage,
(NODES)&_nodeSOURceFUNCtion,
(NODES) 0 };

const NODES _sonSOURceCURRent[]={
(NODES)&_nodeSOURceCURRentLEVel,
(NODES)&_nodeSOURceCURRentVA,
(NODES)&_nodeSOURceCURRentTRIGgered,
(NODES)&_nodeSOURceCURRentPROTection,
(NODES)&_nodeSOURceCURRentRANGe,
(NODES)&_nodeSOURceCURRentIMMediate,
(NODES)&_nodeSOURceCURRentAMPLitude,
(NODES)&_nodeSOURceCURRentSLEW,
(NODES) 0 };

const NODES _sonSOURceCURRentLEVel[]={
(NODES)&_nodeSOURceCURRentLEVelVA,
(NODES)&_nodeSOURceCURRentLEVelTRIGgered,
(NODES)&_nodeSOURceCURRentLEVelIMMediate,
(NODES)&_nodeSOURceCURRentLEVelAMPLitude,
(NODES) 0 };

const NODES _sonSOURceCURRentLEVelVA[]={
(NODES)&_nodeSOURceCURRentLEVelVATRIGgered,
(NODES) 0 };

const NODES _sonSOURceCURRentLEVelVATRIGgered[]={
(NODES)&_nodeSOURceCURRentLEVelVATRIGgeredAMPLitude,
(NODES) 0 };

const NODES _sonSOURceCURRentVA[]={
(NODES)&_nodeSOURceCURRentVATRIGgered,
(NODES) 0 };

const NODES _sonSOURceCURRentVATRIGgered[]={
(NODES)&_nodeSOURceCURRentVATRIGgeredAMPLitude,
(NODES) 0 };

const NODES _sonCURRentVA[]={
(NODES)&_nodeCURRentVATRIGgered,
(NODES) 0 };

const NODES _sonCURRentVATRIGgered[]={
(NODES)&_nodeCURRentVATRIGgeredAMPLitude,
(NODES) 0 };

const NODES _sonSOURceCURRentLEVelTRIGgered[]={
(NODES)&_nodeSOURceCURRentLEVelTRIGgeredAMPLitude,
(NODES) 0 };

const NODES _sonCURRentLEVelTRIGgered[]={
(NODES)&_nodeCURRentLEVelTRIGgeredAMPLitude,
(NODES) 0 };

const NODES _sonSOURceCURRentTRIGgered[]={
(NODES)&_nodeSOURceCURRentTRIGgeredAMPLitude,
(NODES) 0 };

const NODES _sonCURRentTRIGgered[]={
(NODES)&_nodeCURRentTRIGgeredAMPLitude,
(NODES) 0 };

const NODES _sonRESistance[]={
(NODES)&_nodeRESistanceVA,
(NODES)&_nodeRESistanceTRIGgered,
(NODES)&_nodeRESistanceRECall,
(NODES)&_nodeRESistanceVB,
(NODES)&_nodeRESistanceSRATe,
(NODES)&_nodeRESistanceL12,
(NODES)&_nodeRESistanceSET,
(NODES)&_nodeRESistanceLEVel,
(NODES)&_nodeRESistanceRISE,
(NODES)&_nodeRESistanceFALL,
(NODES)&_nodeRESistanceT12,
(NODES)&_nodeRESistanceFREQuency,
(NODES)&_nodeRESistanceDUTY,
(NODES)&_nodeRESistanceCV,
(NODES) 0 };

const NODES _sonRESistanceVA[]={
(NODES)&_nodeRESistanceVATRIGgered,
(NODES) 0 };

const NODES _sonCONDuctance[]={
(NODES)&_nodeCONDuctanceVA,
(NODES)&_nodeCONDuctanceTRIGgered,
(NODES)&_nodeCONDuctanceRECall,
(NODES)&_nodeCONDuctanceVB,
(NODES)&_nodeCONDuctanceL12,
(NODES)&_nodeCONDuctanceSET,
(NODES)&_nodeCONDuctanceLEVel,
(NODES)&_nodeCONDuctanceIMMediate,
(NODES)&_nodeCONDuctanceAMPLitude,
(NODES)&_nodeCONDuctanceRANGe,
(NODES) 0 };

const NODES _sonCONDuctanceVA[]={
(NODES)&_nodeCONDuctanceVATRIGgered,
(NODES) 0 };

const NODES _sonCONDuctanceVATRIGgered[]={
(NODES)&_nodeCONDuctanceVATRIGgeredAMPLitude,
(NODES) 0 };

const NODES _sonSOURceCONDuctance[]={
(NODES)&_nodeSOURceCONDuctanceVA,
(NODES)&_nodeSOURceCONDuctanceTRIGgered,
(NODES)&_nodeSOURceCONDuctanceLEVel,
(NODES)&_nodeSOURceCONDuctanceIMMediate,
(NODES)&_nodeSOURceCONDuctanceAMPLitude,
(NODES)&_nodeSOURceCONDuctanceRANGe,
(NODES) 0 };

const NODES _sonSOURceCONDuctanceVA[]={
(NODES)&_nodeSOURceCONDuctanceVATRIGgered,
(NODES) 0 };

const NODES _sonSOURceCONDuctanceVATRIGgered[]={
(NODES)&_nodeSOURceCONDuctanceVATRIGgeredAMPLitude,
(NODES) 0 };

const NODES _sonSOURceCONDuctanceTRIGgered[]={
(NODES)&_nodeSOURceCONDuctanceTRIGgeredAMPLitude,
(NODES) 0 };

const NODES _sonCONDuctanceTRIGgered[]={
(NODES)&_nodeCONDuctanceTRIGgeredAMPLitude,
(NODES) 0 };

const NODES _sonTRIGger[]={
(NODES)&_nodeTRIGgerDELay,
(NODES)&_nodeTRIGgerTIME,
(NODES)&_nodeTRIGgerPULSe,
(NODES)&_nodeTRIGgerWIDTh,
(NODES) 0 };

const NODES _sonTRIGgerDELay[]={
(NODES)&_nodeTRIGgerDELayTIME,
(NODES) 0 };

const NODES _sonTRIGgerPULSe[]={
(NODES)&_nodeTRIGgerPULSeWIDTh,
(NODES) 0 };

const NODES _sonSHORt[]={
(NODES)&_nodeSHORtSTATe,
(NODES) 0 };

const NODES _sonINPutSHORt[]={
(NODES)&_nodeINPutSHORtSTATe,
(NODES) 0 };

const NODES _sonOUTPup[]={
(NODES)&_nodeOUTPupSHORt,
(NODES) 0 };

const NODES _sonOUTPupSHORt[]={
(NODES)&_nodeOUTPupSHORtSTATe,
(NODES) 0 };

const NODES _sonINPutPROTection[]={
(NODES)&_nodeINPutPROTectionCLEar,
(NODES) 0 };

const NODES _sonOUTPutPROTection[]={
(NODES)&_nodeOUTPutPROTectionCLEar,
(NODES) 0 };

const NODES _sonINPutSTATeTIMer[]={
(NODES)&_nodeINPutSTATeTIMerSTATe,
(NODES) 0 };

const NODES _sonINPutTIMer[]={
(NODES)&_nodeINPutTIMerSTATe,
(NODES) 0 };

const NODES _sonOUTPutSTATeTIMer[]={
(NODES)&_nodeOUTPutSTATeTIMerSTATe,
(NODES) 0 };

const NODES _sonOUTPutTIMer[]={
(NODES)&_nodeOUTPutTIMerSTATe,
(NODES) 0 };

const NODES _sonMEASure[]={
(NODES)&_nodeMEASureSCALar,
(NODES)&_nodeMEASureCURRent,
(NODES)&_nodeMEASureVOLTage,
(NODES)&_nodeMEASurePOWer,
(NODES)&_nodeMEASureETIMe,
(NODES) 0 };

const NODES _sonMEASureSCALar[]={
(NODES)&_nodeMEASureSCALarCURRent,
(NODES)&_nodeMEASureSCALarVOLTage,
(NODES)&_nodeMEASureSCALarPOWer,
(NODES)&_nodeMEASureSCALarETIMe,
(NODES) 0 };

const NODES _sonMEASureSCALarCURRent[]={
(NODES)&_nodeMEASureSCALarCURRentDC,
(NODES) 0 };

const NODES _sonMEASureCURRent[]={
(NODES)&_nodeMEASureCURRentDC,
(NODES) 0 };

const NODES _sonMEASureSCALarVOLTage[]={
(NODES)&_nodeMEASureSCALarVOLTageDC,
(NODES) 0 };

const NODES _sonMEASureVOLTage[]={
(NODES)&_nodeMEASureVOLTageDC,
(NODES) 0 };

const NODES _sonMEASureSCALarPOWer[]={
(NODES)&_nodeMEASureSCALarPOWerDC,
(NODES) 0 };

const NODES _sonMEASurePOWer[]={
(NODES)&_nodeMEASurePOWerDC,
(NODES) 0 };

const NODES _sonFETCh[]={
(NODES)&_nodeFETChCURRent,
(NODES)&_nodeFETChVOLTage,
(NODES)&_nodeFETChPOWer,
(NODES) 0 };

const NODES _sonCONFigure[]={
(NODES)&_nodeCONFigureOCP,
(NODES)&_nodeCONFigureOPP,
(NODES)&_nodeCONFigureUVP,
(NODES)&_nodeCONFigureOVP,
(NODES)&_nodeCONFigureSSTart,
(NODES)&_nodeCONFigureVON,
(NODES)&_nodeCONFigureVDELay,
(NODES)&_nodeCONFigureRESPonse,
(NODES)&_nodeCONFigureCNTime,
(NODES)&_nodeCONFigureCOTime,
(NODES)&_nodeCONFigureCRUNit,
(NODES)&_nodeCONFigureDYNamic,
(NODES)&_nodeCONFigureMEMory,
(NODES)&_nodeCONFigureSHORt,
(NODES)&_nodeCONFigureGNG,
(NODES)&_nodeCONFigureSTEP,
(NODES)&_nodeCONFigureEXTernal,
(NODES) 0 };

const NODES _sonUVP[]={
(NODES)&_nodeUVPTIME,
(NODES) 0 };

const NODES _sonCONFigureUVP[]={
(NODES)&_nodeCONFigureUVPTIME,
(NODES) 0 };

const NODES _sonCONFigureSHORt[]={
(NODES)&_nodeCONFigureSHORtFUNCtion,
(NODES)&_nodeCONFigureSHORtSAFety,
(NODES) 0 };

const NODES _sonGNG[]={
(NODES)&_nodeGNGSPECtest,
(NODES)&_nodeGNGDTIMe,
(NODES)&_nodeGNGMODE,
(NODES)&_nodeGNGPASS,
(NODES)&_nodeGNGH,
(NODES)&_nodeGNGL,
(NODES)&_nodeGNGC,
(NODES) 0 };

const NODES _sonCONFigureGNG[]={
(NODES)&_nodeCONFigureGNGSPECtest,
(NODES)&_nodeCONFigureGNGDTIMe,
(NODES)&_nodeCONFigureGNGMODE,
(NODES)&_nodeCONFigureGNGPASS,
(NODES)&_nodeCONFigureGNGH,
(NODES)&_nodeCONFigureGNGL,
(NODES)&_nodeCONFigureGNGC,
(NODES) 0 };

const NODES _sonSTEP[]={
(NODES)&_nodeSTEPCCH,
(NODES)&_nodeSTEPCCL,
(NODES)&_nodeSTEPCC,
(NODES)&_nodeSTEPCRH,
(NODES)&_nodeSTEPCRL,
(NODES)&_nodeSTEPCR,
(NODES)&_nodeSTEPCVH,
(NODES)&_nodeSTEPCVL,
(NODES)&_nodeSTEPCV,
(NODES)&_nodeSTEPCPH,
(NODES)&_nodeSTEPCPL,
(NODES)&_nodeSTEPCP,
(NODES) 0 };

const NODES _sonCONFigureSTEP[]={
(NODES)&_nodeCONFigureSTEPCCH,
(NODES)&_nodeCONFigureSTEPCCL,
(NODES)&_nodeCONFigureSTEPCC,
(NODES)&_nodeCONFigureSTEPCRH,
(NODES)&_nodeCONFigureSTEPCRL,
(NODES)&_nodeCONFigureSTEPCR,
(NODES)&_nodeCONFigureSTEPCVH,
(NODES)&_nodeCONFigureSTEPCVL,
(NODES)&_nodeCONFigureSTEPCV,
(NODES)&_nodeCONFigureSTEPCPH,
(NODES)&_nodeCONFigureSTEPCPL,
(NODES)&_nodeCONFigureSTEPCP,
(NODES) 0 };

const NODES _sonEXTernal[]={
(NODES)&_nodeEXTernalCONTrol,
(NODES)&_nodeEXTernalLOADonin,
(NODES)&_nodeEXTernalSYNC,
(NODES) 0 };

const NODES _sonCONFigureEXTernal[]={
(NODES)&_nodeCONFigureEXTernalCONTrol,
(NODES)&_nodeCONFigureEXTernalLOADonin,
(NODES)&_nodeCONFigureEXTernalSYNC,
(NODES) 0 };

const NODES _sonMODE[]={
(NODES)&_nodeMODECRANge,
(NODES)&_nodeMODEVRANge,
(NODES)&_nodeMODEDYNamic,
(NODES) 0 };

const NODES _sonCURRentCV[]={
(NODES)&_nodeCURRentCVRESPonse,
(NODES) 0 };

const NODES _sonRESistanceCV[]={
(NODES)&_nodeRESistanceCVRESPonse,
(NODES) 0 };

const NODES _sonVOLTage[]={
(NODES)&_nodeVOLTageRECall,
(NODES)&_nodeVOLTageVA,
(NODES)&_nodeVOLTageVB,
(NODES)&_nodeVOLTageRESPonse,
(NODES)&_nodeVOLTagePROTection,
(NODES)&_nodeVOLTageLEVel,
(NODES)&_nodeVOLTageIMMediate,
(NODES)&_nodeVOLTageAMPLitude,
(NODES)&_nodeVOLTageRANGe,
(NODES) 0 };

const NODES _sonPOWer[]={
(NODES)&_nodePOWerRECall,
(NODES)&_nodePOWerVA,
(NODES)&_nodePOWerVB,
(NODES)&_nodePOWerRESPonse,
(NODES)&_nodePOWerCV,
(NODES)&_nodePOWerPROTection,
(NODES)&_nodePOWerRANGe,
(NODES)&_nodePOWerLEVel,
(NODES)&_nodePOWerIMMediate,
(NODES)&_nodePOWerAMPLitude,
(NODES) 0 };

const NODES _sonPOWerCV[]={
(NODES)&_nodePOWerCVRESPonse,
(NODES) 0 };

const NODES _sonFUNCtion[]={
(NODES)&_nodeFUNCtionCOMPlete,
(NODES)&_nodeFUNCtionRING,
(NODES)&_nodeFUNCtionTIME,
(NODES)&_nodeFUNCtionSSTart,
(NODES)&_nodeFUNCtionRESPonse,
(NODES)&_nodeFUNCtionCTIMe,
(NODES)&_nodeFUNCtionMODE,
(NODES) 0 };

const NODES _sonFUNCtionCOMPlete[]={
(NODES)&_nodeFUNCtionCOMPleteRING,
(NODES)&_nodeFUNCtionCOMPleteTIME,
(NODES) 0 };

const NODES _sonFUNCtionCOMPleteRING[]={
(NODES)&_nodeFUNCtionCOMPleteRINGTIME,
(NODES) 0 };

const NODES _sonFUNCtionRING[]={
(NODES)&_nodeFUNCtionRINGTIME,
(NODES) 0 };

const NODES _sonPROGram[]={
(NODES)&_nodePROGramSTATe,
(NODES)&_nodePROGramRECall,
(NODES)&_nodePROGramDEFault,
(NODES)&_nodePROGramSTARt,
(NODES)&_nodePROGramSTEP,
(NODES)&_nodePROGramMEMory,
(NODES)&_nodePROGramRUN,
(NODES)&_nodePROGramONTime,
(NODES)&_nodePROGramOFFTime,
(NODES)&_nodePROGramPFTime,
(NODES)&_nodePROGramSTIMe,
(NODES)&_nodePROGramCHAin,
(NODES)&_nodePROGramSAVE,
(NODES)&_nodePROGramSELected,
(NODES)&_nodePROGramNAME,
(NODES)&_nodePROGramMEMO,
(NODES)&_nodePROGramMODE,
(NODES)&_nodePROGramVRANge,
(NODES)&_nodePROGramCRANge,
(NODES)&_nodePROGramLOOP,
(NODES)&_nodePROGramLINPut,
(NODES)&_nodePROGramLOUTput,
(NODES)&_nodePROGramLVALue,
(NODES)&_nodePROGramNSPeed,
(NODES)&_nodePROGramFSPeed,
(NODES) 0 };

const NODES _sonPROGramRECall[]={
(NODES)&_nodePROGramRECallDEFault,
(NODES) 0 };

const NODES _sonCHAin[]={
(NODES)&_nodeCHAinSTARt,
(NODES)&_nodeCHAinP2P,
(NODES)&_nodeCHAinRECall,
(NODES)&_nodeCHAinDEFault,
(NODES) 0 };

const NODES _sonPROGramCHAin[]={
(NODES)&_nodePROGramCHAinSTARt,
(NODES)&_nodePROGramCHAinP2P,
(NODES)&_nodePROGramCHAinRECall,
(NODES)&_nodePROGramCHAinDEFault,
(NODES) 0 };

const NODES _sonCHAinRECall[]={
(NODES)&_nodeCHAinRECallDEFault,
(NODES) 0 };

const NODES _sonPROGramCHAinRECall[]={
(NODES)&_nodePROGramCHAinRECallDEFault,
(NODES) 0 };

const NODES _sonSEQuence[]={
(NODES)&_nodeSEQuenceCOMPlete,
(NODES)&_nodeSEQuenceRING,
(NODES)&_nodeSEQuenceTIME,
(NODES) 0 };

const NODES _sonSEQuenceCOMPlete[]={
(NODES)&_nodeSEQuenceCOMPleteRING,
(NODES)&_nodeSEQuenceCOMPleteTIME,
(NODES) 0 };

const NODES _sonSEQuenceCOMPleteRING[]={
(NODES)&_nodeSEQuenceCOMPleteRINGTIME,
(NODES) 0 };

const NODES _sonSEQuenceRING[]={
(NODES)&_nodeSEQuenceRINGTIME,
(NODES) 0 };

const NODES _sonNSEQuence[]={
(NODES)&_nodeNSEQuenceTIMer,
(NODES)&_nodeNSEQuenceCOTime,
(NODES)&_nodeNSEQuenceSTATe,
(NODES)&_nodeNSEQuenceSTARt,
(NODES)&_nodeNSEQuenceNUMBer,
(NODES)&_nodeNSEQuenceMEMO,
(NODES)&_nodeNSEQuenceMODE,
(NODES)&_nodeNSEQuenceRANGe,
(NODES)&_nodeNSEQuenceLOOP,
(NODES)&_nodeNSEQuenceLLOad,
(NODES)&_nodeNSEQuenceLAST,
(NODES)&_nodeNSEQuenceCHAin,
(NODES)&_nodeNSEQuenceEDIT,
(NODES)&_nodeNSEQuenceDELet,
(NODES)&_nodeNSEQuenceALL,
(NODES)&_nodeNSEQuenceSAVE,
(NODES) 0 };

const NODES _sonNSEQuenceEDIT[]={
(NODES)&_nodeNSEQuenceEDITPOINt,
(NODES)&_nodeNSEQuenceEDITEND,
(NODES) 0 };

const NODES _sonNSEQuenceDELet[]={
(NODES)&_nodeNSEQuenceDELetALL,
(NODES) 0 };

const NODES _sonFSEQuence[]={
(NODES)&_nodeFSEQuenceSTATe,
(NODES)&_nodeFSEQuenceMEMO,
(NODES)&_nodeFSEQuenceMODE,
(NODES)&_nodeFSEQuenceRANGe,
(NODES)&_nodeFSEQuenceLOOP,
(NODES)&_nodeFSEQuenceTBASe,
(NODES)&_nodeFSEQuenceLLOad,
(NODES)&_nodeFSEQuenceLAST,
(NODES)&_nodeFSEQuenceRPTStep,
(NODES)&_nodeFSEQuenceEDIT,
(NODES)&_nodeFSEQuenceDELet,
(NODES)&_nodeFSEQuenceALL,
(NODES)&_nodeFSEQuenceFILL,
(NODES)&_nodeFSEQuenceSAVE,
(NODES) 0 };

const NODES _sonFSEQuenceEDIT[]={
(NODES)&_nodeFSEQuenceEDITPOINt,
(NODES)&_nodeFSEQuenceEDITEND,
(NODES)&_nodeFSEQuenceEDITFILL,
(NODES) 0 };

const NODES _sonFSEQuenceDELet[]={
(NODES)&_nodeFSEQuenceDELetALL,
(NODES) 0 };

const NODES _sonOCP[]={
(NODES)&_nodeOCPSTATe,
(NODES)&_nodeOCPEDIT,
(NODES)&_nodeOCPCHANnel,
(NODES)&_nodeOCPTEMP,
(NODES)&_nodeOCPRANGe,
(NODES)&_nodeOCPSTARt,
(NODES)&_nodeOCPEND,
(NODES)&_nodeOCPSTEP,
(NODES)&_nodeOCPLAST,
(NODES)&_nodeOCPDELay,
(NODES)&_nodeOCPTRIGger,
(NODES)&_nodeOCPSAVE,
(NODES)&_nodeOCPRESult,
(NODES)&_nodeOCPRUN,
(NODES) 0 };

const NODES _sonOCPEDIT[]={
(NODES)&_nodeOCPEDITCHANnel,
(NODES) 0 };

const NODES _sonOCPCHANnel[]={
(NODES)&_nodeOCPCHANnelTEMP,
(NODES)&_nodeOCPCHANnelRANGe,
(NODES)&_nodeOCPCHANnelSTARt,
(NODES)&_nodeOCPCHANnelEND,
(NODES)&_nodeOCPCHANnelSTEP,
(NODES)&_nodeOCPCHANnelLAST,
(NODES)&_nodeOCPCHANnelDELay,
(NODES)&_nodeOCPCHANnelTRIGger,
(NODES) 0 };

const NODES _sonOCPCHANnelSTEP[]={
(NODES)&_nodeOCPCHANnelStepCurrWattent,
(NODES)&_nodeOCPCHANnelSTEPTIME,
(NODES) 0 };

const NODES _sonOCPSTEP[]={
(NODES)&_nodeOCPStepCurrWattent,
(NODES)&_nodeOCPSTEPTIME,
(NODES) 0 };

const NODES _sonUTILity[]={
(NODES)&_nodeUTILitySYSTem,
(NODES)&_nodeUTILityREMote,
(NODES)&_nodeUTILityLOAD,
(NODES)&_nodeUTILityINTerface,
(NODES)&_nodeUTILityTIME,
(NODES)&_nodeUTILityKNOB,
(NODES)&_nodeUTILitySPEaker,
(NODES)&_nodeUTILityALARm,
(NODES)&_nodeUTILityUNReg,
(NODES)&_nodeUTILityGNG,
(NODES)&_nodeUTILityCONTrast,
(NODES)&_nodeUTILityBRIGhtness,
(NODES)&_nodeUTILityLANGuage,
(NODES) 0 };

const NODES _sonUTILityREMote[]={
(NODES)&_nodeUTILityREMoteMODE,
(NODES) 0 };

const NODES _sonUTILityLOAD[]={
(NODES)&_nodeUTILityLOADMODE,
(NODES)&_nodeUTILityLOADRANGe,
(NODES) 0 };

const NODES _sonMEMory[]={
(NODES)&_nodeMEMorySAVE,
(NODES)&_nodeMEMoryRECall,
(NODES) 0 };

const NODES _sonPRESet[]={
(NODES)&_nodePRESetSAVE,
(NODES)&_nodePRESetRECall,
(NODES) 0 };

const NODES _sonSETup[]={
(NODES)&_nodeSETupSAVE,
(NODES)&_nodeSETupRECall,
(NODES) 0 };

const NODES _sonFACTory[]={
(NODES)&_nodeFACToryRECall,
(NODES) 0 };

const NODES _sonUSER[]={
(NODES)&_nodeUSERDEFault,
(NODES)&_nodeUSERSAVE,
(NODES)&_nodeUSERRECall,
(NODES) 0 };

const NODES _sonUSERDEFault[]={
(NODES)&_nodeUSERDEFaultSAVE,
(NODES)&_nodeUSERDEFaultRECall,
(NODES) 0 };

const NODES _sonSERial[]={
(NODES)&_nodeSERialMASTer,
(NODES) 0 };

const NODES _sonSTATus[]={
(NODES)&_nodeSTATusPRESet,
(NODES)&_nodeSTATusQUEStionable,
(NODES)&_nodeSTATusOPERation,
(NODES)&_nodeSTATusCSUMmary,
(NODES) 0 };

const NODES _sonSTATusQUEStionable[]={
(NODES)&_nodeSTATusQUEStionableCONDition,
(NODES)&_nodeSTATusQUEStionableENABle,
(NODES)&_nodeSTATusQUEStionableEVENt,
(NODES)&_nodeSTATusQUEStionableNTRansition,
(NODES)&_nodeSTATusQUEStionablePTRansition,
(NODES) 0 };

const NODES _sonSTATusOPERation[]={
(NODES)&_nodeSTATusOPERationCONDition,
(NODES)&_nodeSTATusOPERationENABle,
(NODES)&_nodeSTATusOPERationEVENt,
(NODES)&_nodeSTATusOPERationNTRansition,
(NODES)&_nodeSTATusOPERationPTRansition,
(NODES) 0 };

const NODES _sonSTATusCSUMmary[]={
(NODES)&_nodeSTATusCSUMmaryCONDition,
(NODES)&_nodeSTATusCSUMmaryENABle,
(NODES)&_nodeSTATusCSUMmaryEVENt,
(NODES)&_nodeSTATusCSUMmaryNTRansition,
(NODES)&_nodeSTATusCSUMmaryPTRansition,
(NODES) 0 };

const NODES _sonSYNC[]={
(NODES)&_nodeSYNCWAIT,
(NODES)&_nodeSYNCDEFault,
(NODES)&_nodeSYNCRECall,
(NODES)&_nodeSYNCCHEaksum,
(NODES) 0 };

const NODES _sonSYNCDEFault[]={
(NODES)&_nodeSYNCDEFaultRECall,
(NODES) 0 };

const NODES _sonCURRentPROTection[]={
(NODES)&_nodeCURRentPROTectionLEVel,
(NODES)&_nodeCURRentPROTectionOVER,
(NODES)&_nodeCURRentPROTectionACTion,
(NODES) 0 };

const NODES _sonCURRentPROTectionLEVel[]={
(NODES)&_nodeCURRentPROTectionLEVelOVER,
(NODES) 0 };

const NODES _sonSOURceCURRentPROTection[]={
(NODES)&_nodeSOURceCURRentPROTectionLEVel,
(NODES)&_nodeSOURceCURRentPROTectionOVER,
(NODES)&_nodeSOURceCURRentPROTectionACTion,
(NODES) 0 };

const NODES _sonSOURceCURRentPROTectionLEVel[]={
(NODES)&_nodeSOURceCURRentPROTectionLEVelOVER,
(NODES) 0 };

const NODES _sonCURRentLEVelIMMediate[]={
(NODES)&_nodeCURRentLEVelIMMediateAMPLitude,
(NODES) 0 };

const NODES _sonSOURceCURRentLEVelIMMediate[]={
(NODES)&_nodeSOURceCURRentLEVelIMMediateAMPLitude,
(NODES) 0 };

const NODES _sonSOURceCURRentIMMediate[]={
(NODES)&_nodeSOURceCURRentIMMediateAMPLitude,
(NODES) 0 };

const NODES _sonCURRentIMMediate[]={
(NODES)&_nodeCURRentIMMediateAMPLitude,
(NODES) 0 };

const NODES _sonPOWerPROTection[]={
(NODES)&_nodePOWerPROTectionLEVel,
(NODES)&_nodePOWerPROTectionOVER,
(NODES)&_nodePOWerPROTectionACTion,
(NODES) 0 };

const NODES _sonPOWerPROTectionLEVel[]={
(NODES)&_nodePOWerPROTectionLEVelOVER,
(NODES) 0 };

const NODES _sonSOURcePOWer[]={
(NODES)&_nodeSOURcePOWerPROTection,
(NODES)&_nodeSOURcePOWerRANGe,
(NODES)&_nodeSOURcePOWerLEVel,
(NODES)&_nodeSOURcePOWerIMMediate,
(NODES)&_nodeSOURcePOWerAMPLitude,
(NODES) 0 };

const NODES _sonSOURcePOWerPROTection[]={
(NODES)&_nodeSOURcePOWerPROTectionLEVel,
(NODES)&_nodeSOURcePOWerPROTectionOVER,
(NODES)&_nodeSOURcePOWerPROTectionACTion,
(NODES) 0 };

const NODES _sonSOURcePOWerPROTectionLEVel[]={
(NODES)&_nodeSOURcePOWerPROTectionLEVelOVER,
(NODES) 0 };

const NODES _sonPOWerLEVel[]={
(NODES)&_nodePOWerLEVelIMMediate,
(NODES)&_nodePOWerLEVelAMPLitude,
(NODES) 0 };

const NODES _sonPOWerLEVelIMMediate[]={
(NODES)&_nodePOWerLEVelIMMediateAMPLitude,
(NODES) 0 };

const NODES _sonSOURcePOWerLEVel[]={
(NODES)&_nodeSOURcePOWerLEVelIMMediate,
(NODES)&_nodeSOURcePOWerLEVelAMPLitude,
(NODES) 0 };

const NODES _sonSOURcePOWerLEVelIMMediate[]={
(NODES)&_nodeSOURcePOWerLEVelIMMediateAMPLitude,
(NODES) 0 };

const NODES _sonSOURcePOWerIMMediate[]={
(NODES)&_nodeSOURcePOWerIMMediateAMPLitude,
(NODES) 0 };

const NODES _sonPOWerIMMediate[]={
(NODES)&_nodePOWerIMMediateAMPLitude,
(NODES) 0 };

const NODES _sonCONDuctanceLEVel[]={
(NODES)&_nodeCONDuctanceLEVelIMMediate,
(NODES)&_nodeCONDuctanceLEVelAMPLitude,
(NODES) 0 };

const NODES _sonCONDuctanceLEVelIMMediate[]={
(NODES)&_nodeCONDuctanceLEVelIMMediateAMPLitude,
(NODES) 0 };

const NODES _sonSOURceCONDuctanceLEVel[]={
(NODES)&_nodeSOURceCONDuctanceLEVelIMMediate,
(NODES)&_nodeSOURceCONDuctanceLEVelAMPLitude,
(NODES) 0 };

const NODES _sonSOURceCONDuctanceLEVelIMMediate[]={
(NODES)&_nodeSOURceCONDuctanceLEVelIMMediateAMPLitude,
(NODES) 0 };

const NODES _sonSOURceCONDuctanceIMMediate[]={
(NODES)&_nodeSOURceCONDuctanceIMMediateAMPLitude,
(NODES) 0 };

const NODES _sonCONDuctanceIMMediate[]={
(NODES)&_nodeCONDuctanceIMMediateAMPLitude,
(NODES) 0 };

const NODES _sonVOLTagePROTection[]={
(NODES)&_nodeVOLTagePROTectionLEVel,
(NODES)&_nodeVOLTagePROTectionUNDer,
(NODES)&_nodeVOLTagePROTectionSTATe,
(NODES) 0 };

const NODES _sonVOLTagePROTectionLEVel[]={
(NODES)&_nodeVOLTagePROTectionLEVelUNDer,
(NODES) 0 };

const NODES _sonSOURceVOLTage[]={
(NODES)&_nodeSOURceVOLTagePROTection,
(NODES)&_nodeSOURceVOLTageLEVel,
(NODES)&_nodeSOURceVOLTageIMMediate,
(NODES)&_nodeSOURceVOLTageAMPLitude,
(NODES)&_nodeSOURceVOLTageRANGe,
(NODES) 0 };

const NODES _sonSOURceVOLTagePROTection[]={
(NODES)&_nodeSOURceVOLTagePROTectionLEVel,
(NODES)&_nodeSOURceVOLTagePROTectionUNDer,
(NODES)&_nodeSOURceVOLTagePROTectionSTATe,
(NODES) 0 };

const NODES _sonSOURceVOLTagePROTectionLEVel[]={
(NODES)&_nodeSOURceVOLTagePROTectionLEVelUNDer,
(NODES) 0 };

const NODES _sonVOLTageLEVel[]={
(NODES)&_nodeVOLTageLEVelIMMediate,
(NODES)&_nodeVOLTageLEVelAMPLitude,
(NODES) 0 };

const NODES _sonVOLTageLEVelIMMediate[]={
(NODES)&_nodeVOLTageLEVelIMMediateAMPLitude,
(NODES) 0 };

const NODES _sonSOURceVOLTageLEVel[]={
(NODES)&_nodeSOURceVOLTageLEVelIMMediate,
(NODES)&_nodeSOURceVOLTageLEVelAMPLitude,
(NODES) 0 };

const NODES _sonSOURceVOLTageLEVelIMMediate[]={
(NODES)&_nodeSOURceVOLTageLEVelIMMediateAMPLitude,
(NODES) 0 };

const NODES _sonSOURceVOLTageIMMediate[]={
(NODES)&_nodeSOURceVOLTageIMMediateAMPLitude,
(NODES) 0 };

const NODES _sonVOLTageIMMediate[]={
(NODES)&_nodeVOLTageIMMediateAMPLitude,
(NODES) 0 };

const NODES _sonSOURceFUNCtion[]={
(NODES)&_nodeSOURceFUNCtionSSTart,
(NODES)&_nodeSOURceFUNCtionRESPonse,
(NODES)&_nodeSOURceFUNCtionCTIMe,
(NODES)&_nodeSOURceFUNCtionMODE,
(NODES) 0 };

const NODES _sonSELected[]={
(NODES)&_nodeSELectedSTATe,
(NODES)&_nodeSELectedEXECuting,
(NODES) 0 };

const NODES _sonPROGramSELected[]={
(NODES)&_nodePROGramSELectedNAME,
(NODES)&_nodePROGramSELectedMEMO,
(NODES)&_nodePROGramSELectedMODE,
(NODES)&_nodePROGramSELectedVRANge,
(NODES)&_nodePROGramSELectedCRANge,
(NODES)&_nodePROGramSELectedLOOP,
(NODES)&_nodePROGramSELectedLINPut,
(NODES)&_nodePROGramSELectedLOUTput,
(NODES)&_nodePROGramSELectedLVALue,
(NODES)&_nodePROGramSELectedCHAin,
(NODES)&_nodePROGramSELectedNSPeed,
(NODES)&_nodePROGramSELectedFSPeed,
(NODES) 0 };

const NODES _sonPROGramSELectedNSPeed[]={
(NODES)&_nodePROGramSELectedNSPeedSTEP,
(NODES)&_nodePROGramSELectedNSPeedINSert,
(NODES)&_nodePROGramSELectedNSPeedADD,
(NODES)&_nodePROGramSELectedNSPeedDELete,
(NODES)&_nodePROGramSELectedNSPeedCOUNt,
(NODES)&_nodePROGramSELectedNSPeedEDIT,
(NODES) 0 };

const NODES _sonPROGramSELectedNSPeedSTEP[]={
(NODES)&_nodePROGramSELectedNSPeedSTEPINSert,
(NODES)&_nodePROGramSELectedNSPeedSTEPADD,
(NODES)&_nodePROGramSELectedNSPeedSTEPDELete,
(NODES)&_nodePROGramSELectedNSPeedSTEPCOUNt,
(NODES)&_nodePROGramSELectedNSPeedSTEPEDIT,
(NODES) 0 };

const NODES _sonPROGramNSPeed[]={
(NODES)&_nodePROGramNSPeedSTEP,
(NODES)&_nodePROGramNSPeedINSert,
(NODES)&_nodePROGramNSPeedADD,
(NODES)&_nodePROGramNSPeedDELete,
(NODES)&_nodePROGramNSPeedCOUNt,
(NODES)&_nodePROGramNSPeedEDIT,
(NODES) 0 };

const NODES _sonPROGramNSPeedSTEP[]={
(NODES)&_nodePROGramNSPeedSTEPINSert,
(NODES)&_nodePROGramNSPeedSTEPADD,
(NODES)&_nodePROGramNSPeedSTEPDELete,
(NODES)&_nodePROGramNSPeedSTEPCOUNt,
(NODES)&_nodePROGramNSPeedSTEPEDIT,
(NODES) 0 };

const NODES _sonPROGramSELectedNSPeedSTEPDELete[]={
(NODES)&_nodePROGramSELectedNSPeedSTEPDELeteALL,
(NODES) 0 };

const NODES _sonPROGramNSPeedSTEPDELete[]={
(NODES)&_nodePROGramNSPeedSTEPDELeteALL,
(NODES) 0 };

const NODES _sonPROGramSELectedNSPeedDELete[]={
(NODES)&_nodePROGramSELectedNSPeedDELeteALL,
(NODES) 0 };

const NODES _sonPROGramNSPeedDELete[]={
(NODES)&_nodePROGramNSPeedDELeteALL,
(NODES) 0 };

const NODES _sonPROGramSELectedFSPeed[]={
(NODES)&_nodePROGramSELectedFSPeedSTEP,
(NODES)&_nodePROGramSELectedFSPeedEND,
(NODES)&_nodePROGramSELectedFSPeedEDIT,
(NODES)&_nodePROGramSELectedFSPeedTIME,
(NODES) 0 };

const NODES _sonPROGramSELectedFSPeedSTEP[]={
(NODES)&_nodePROGramSELectedFSPeedSTEPEND,
(NODES)&_nodePROGramSELectedFSPeedSTEPEDIT,
(NODES) 0 };

const NODES _sonPROGramFSPeed[]={
(NODES)&_nodePROGramFSPeedSTEP,
(NODES)&_nodePROGramFSPeedEND,
(NODES)&_nodePROGramFSPeedEDIT,
(NODES)&_nodePROGramFSPeedTIME,
(NODES) 0 };

const NODES _sonPROGramFSPeedSTEP[]={
(NODES)&_nodePROGramFSPeedSTEPEND,
(NODES)&_nodePROGramFSPeedSTEPEDIT,
(NODES) 0 };

const NODES _sonPROGramSELectedFSPeedSTEPEDIT[]={
(NODES)&_nodePROGramSELectedFSPeedSTEPEDITPOINt,
(NODES)&_nodePROGramSELectedFSPeedSTEPEDITLINear,
(NODES)&_nodePROGramSELectedFSPeedSTEPEDITWAVE,
(NODES) 0 };

const NODES _sonPROGramFSPeedSTEPEDIT[]={
(NODES)&_nodePROGramFSPeedSTEPEDITPOINt,
(NODES)&_nodePROGramFSPeedSTEPEDITLINear,
(NODES)&_nodePROGramFSPeedSTEPEDITWAVE,
(NODES) 0 };

const NODES _sonPROGramSELectedFSPeedEDIT[]={
(NODES)&_nodePROGramSELectedFSPeedEDITPOINt,
(NODES)&_nodePROGramSELectedFSPeedEDITLINear,
(NODES)&_nodePROGramSELectedFSPeedEDITWAVE,
(NODES) 0 };

const NODES _sonPROGramFSPeedEDIT[]={
(NODES)&_nodePROGramFSPeedEDITPOINt,
(NODES)&_nodePROGramFSPeedEDITLINear,
(NODES)&_nodePROGramFSPeedEDITWAVE,
(NODES) 0 };

const NODES _sonCALibrate[]={
(NODES)&_nodeCALibratePASSword,
(NODES)&_nodeCALibrateMODE,
(NODES)&_nodeCALibrateRANGe,
(NODES)&_nodeCALibrateLEVel,
(NODES)&_nodeCALibrateVALue,
(NODES)&_nodeCALibrateBIValue,
(NODES)&_nodeCALibrateRUN,
(NODES)&_nodeCALibratePSENsor,
(NODES)&_nodeCALibrateSAVE,
(NODES) 0 };





//Create Parameter Node
const STR_PARAMS1 parameters[]= {
// Command Node Name
//-----ID_NO --------|------ SET COMMAND --------|------- QUERY COMMAND -------|
//-------------------|-- min,max,-------type ----|-- min,max,------- type -----|
//*CAL
	{_id_CAL, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//*CLS
	{_id_CLS, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//*ESE
	{_id_ESE, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//*ESR
	{_id_ESR, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//*IDN
	{_id_IDN, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//*OPC
	{_id_OPC, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//*RCL
	{_id_RCL, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//*RST
	{_id_RST, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//*SAV
	{_id_SAV, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//*SRE
	{_id_SRE, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//*STB
	{_id_STB, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//*TRG
	{_id_TRG, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//*TST
	{_id_TST, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//*WAI
	{_id_WAI, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:ABORt
	{_idABORt, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:SYSTem:ERRor[:NEXT]
	{_idSYSTemERRorNEXT, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:INPut[:STATe]:TRIGgered
	{_idINPutSTATeTRIGgered, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:OUTPut[:STATe]:TRIGgered
	{_idOUTPutSTATeTRIGgered, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:INITiate[:IMMediate]
	{_idINITiateIMMediate, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:INITiate:CONTinuous
	{_idINITiateCONTinuous, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:CURRent[:LEVel][:VA]:TRIGgered[:AMPLitude]
	{_idSOURceCURRentLEVelVATRIGgeredAMPLitude, {{1, 1, (PARAM_ITEM*) &_pg3},  {0, 0, (PARAM_ITEM*)0}}},
//:RESistance[:VA]:TRIGgered
	{_idRESistanceVATRIGgered, {{1, 1, (PARAM_ITEM*) &_pg4},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:CONDuctance[:VA]:TRIGgered[:AMPLitude]
	{_idSOURceCONDuctanceVATRIGgeredAMPLitude, {{1, 1, (PARAM_ITEM*) &_pg5},  {0, 0, (PARAM_ITEM*)0}}},
//:TRIGger[:DELay]:TIME
	{_idTRIGgerDELayTIME, {{1, 1, (PARAM_ITEM*) &_pg6},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:TRIGger[:PULSe]:WIDTh
	{_idTRIGgerPULSeWIDTh, {{1, 1, (PARAM_ITEM*) &_pg6},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:INPut[:STATe][:IMMediate]
	{_idINPutSTATeIMMediate, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:OUTPut[:STATe][:IMMediate]
	{_idOUTPutSTATeIMMediate, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//[:INPut]:SHORt[:STATe]
	{_idINPutSHORtSTATe, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:OUTPup:SHORt[:STATe]
	{_idOUTPupSHORtSTATe, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:INPut:PROTection:CLEar
	{_idINPutPROTectionCLEar, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:OUTPut:PROTection:CLEar
	{_idOUTPutPROTectionCLEar, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:INPut[:STATe]:TIMer[:STATe]
	{_idINPutSTATeTIMerSTATe, {{1, 1, (PARAM_ITEM*) &_pg8},  {0, 0, (PARAM_ITEM*)0}}},
//:OUTPut[:STATe]:TIMer[:STATe]
	{_idOUTPutSTATeTIMerSTATe, {{1, 1, (PARAM_ITEM*) &_pg8},  {0, 0, (PARAM_ITEM*)0}}},
//:INPut:MODE
	{_idINPutMODE, {{1, 1, (PARAM_ITEM*) &_pg9},  {0, 0, (PARAM_ITEM*)0}}},
//:MEASure[:SCALar]:CURRent[:DC]
	{_idMEASureSCALarCURRentDC, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:MEASure[:SCALar]:VOLTage[:DC]
	{_idMEASureSCALarVOLTageDC, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:MEASure[:SCALar]:POWer[:DC]
	{_idMEASureSCALarPOWerDC, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:MEASure[:SCALar]:ETIMe
	{_idMEASureSCALarETIMe, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:FETCh:CURRent
	{_idFETChCURRent, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:FETCh:VOLTage
	{_idFETChVOLTage, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:FETCh:POWer
	{_idFETChPOWer, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:OCP
	{_idCONFigureOCP, {{1, 1, (PARAM_ITEM*) &_pg10},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//[:CONFigure]:OPP
	{_idCONFigureOPP, {{1, 1, (PARAM_ITEM*) &_pg11},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//[:CONFigure]:UVP
	{_idCONFigureUVP, {{1, 1, (PARAM_ITEM*) &_pg12},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//[:CONFigure]:UVP:TIME
	{_idCONFigureUVPTIME, {{1, 1, (PARAM_ITEM*) &_pg13},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//[:CONFigure]:OVP
	{_idCONFigureOVP, {{1, 1, (PARAM_ITEM*) &_pg12},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//[:CONFigure]:SSTart
	{_idCONFigureSSTart, {{1, 1, (PARAM_ITEM*) &_pg14},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//[:CONFigure]:VON
	{_idCONFigureVON, {{1, 1, (PARAM_ITEM*) &_pg15},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:VDELay
	{_idCONFigureVDELay, {{1, 1, (PARAM_ITEM*) &_pg14},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:CONFigure:RESPonse
	{_idCONFigureRESPonse, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//[:CONFigure]:CNTime
	{_idCONFigureCNTime, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:COTime
	{_idCONFigureCOTime, {{1, 1, (PARAM_ITEM*) &_pg14},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//[:CONFigure]:CRUNit
	{_idCONFigureCRUNit, {{1, 1, (PARAM_ITEM*) &_pg17},  {0, 0, (PARAM_ITEM*)0}}},
//:CONFigure:DYNamic
	{_idCONFigureDYNamic, {{1, 1, (PARAM_ITEM*) &_pg18},  {0, 0, (PARAM_ITEM*)0}}},
//:CONFigure:MEMory
	{_idCONFigureMEMory, {{1, 1, (PARAM_ITEM*) &_pg19},  {0, 0, (PARAM_ITEM*)0}}},
//:CONFigure:SHORt:FUNCtion
	{_idCONFigureSHORtFUNCtion, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:CONFigure:SHORt
	{_idCONFigureSHORt, {{1, 1, (PARAM_ITEM*) &_pg20},  {0, 0, (PARAM_ITEM*)0}}},
//:CONFigure:SHORt:SAFety
	{_idCONFigureSHORtSAFety, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:GNG:SPECtest
	{_idCONFigureGNGSPECtest, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:GNG:DTIMe
	{_idCONFigureGNGDTIMe, {{1, 1, (PARAM_ITEM*) &_pg6},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//[:CONFigure]:GNG:MODE
	{_idCONFigureGNGMODE, {{1, 1, (PARAM_ITEM*) &_pg21},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:GNG[:PASS]
	{_idCONFigureGNGPASS, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:GNG:H
	{_idCONFigureGNGH, {{1, 1, (PARAM_ITEM*) &_pg22},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:GNG:L
	{_idCONFigureGNGL, {{1, 1, (PARAM_ITEM*) &_pg22},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:GNG:C
	{_idCONFigureGNGC, {{1, 1, (PARAM_ITEM*) &_pg22},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:STEP:CCH
	{_idCONFigureSTEPCCH, {{1, 1, (PARAM_ITEM*) &_pg3},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:STEP:CCL
	{_idCONFigureSTEPCCL, {{1, 1, (PARAM_ITEM*) &_pg3},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:STEP:CC
	{_idCONFigureSTEPCC, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:STEP:CRH
	{_idCONFigureSTEPCRH, {{1, 1, (PARAM_ITEM*) &_pg23},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:STEP:CRL
	{_idCONFigureSTEPCRL, {{1, 1, (PARAM_ITEM*) &_pg23},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:STEP:CR
	{_idCONFigureSTEPCR, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:STEP:CVH
	{_idCONFigureSTEPCVH, {{1, 1, (PARAM_ITEM*) &_pg12},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:STEP:CVL
	{_idCONFigureSTEPCVL, {{1, 1, (PARAM_ITEM*) &_pg12},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:STEP:CV
	{_idCONFigureSTEPCV, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:STEP:CPH
	{_idCONFigureSTEPCPH, {{1, 1, (PARAM_ITEM*) &_pg24},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:STEP:CPL
	{_idCONFigureSTEPCPL, {{1, 1, (PARAM_ITEM*) &_pg24},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:STEP:CP
	{_idCONFigureSTEPCP, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:EXTernal[:CONTrol]
	{_idCONFigureEXTernalCONTrol, {{1, 1, (PARAM_ITEM*) &_pg25},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:EXTernal:LOADonin
	{_idCONFigureEXTernalLOADonin, {{1, 1, (PARAM_ITEM*) &_pg26},  {0, 0, (PARAM_ITEM*)0}}},
//[:CONFigure]:EXTernal:SYNC
	{_idCONFigureEXTernalSYNC, {{1, 1, (PARAM_ITEM*) &_pg27},  {0, 0, (PARAM_ITEM*)0}}},
//:MODE
	{_idMODE, {{1, 1, (PARAM_ITEM*) &_pg28},  {0, 0, (PARAM_ITEM*)0}}},
//[:MODE]:CRANge
	{_idMODECRANge, {{1, 1, (PARAM_ITEM*) &_pg29},  {0, 0, (PARAM_ITEM*)0}}},
//[:MODE]:VRANge
	{_idMODEVRANge, {{1, 1, (PARAM_ITEM*) &_pg29},  {0, 0, (PARAM_ITEM*)0}}},
//[:MODE]:DYNamic
	{_idMODEDYNamic, {{1, 1, (PARAM_ITEM*) &_pg30},  {0, 0, (PARAM_ITEM*)0}}},
//:CURRent:RECall
	{_idCURRentRECall, {{1, 1, (PARAM_ITEM*) &_pg31},  {0, 0, (PARAM_ITEM*)0}}},
//:CURRent[:VA]
	{_idCURRentVA, {{1, 1, (PARAM_ITEM*) &_pg3},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:CURRent:VB
	{_idCURRentVB, {{1, 1, (PARAM_ITEM*) &_pg3},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:CURRent:SRATe
	{_idCURRentSRATe, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:CURRent:L<1|2>
	{_idCURRentL12, {{1, 1, (PARAM_ITEM*) &_pg3},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:CURRent:SET
	{_idCURRentSET, {{1, 1, (PARAM_ITEM*) &_pg3},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:CURRent:LEVel
	{_idCURRentLEVel, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:CURRent:RISE
	{_idCURRentRISE, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:CURRent:FALL
	{_idCURRentFALL, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:CURRent:T<1|2>
	{_idCURRentT12, {{1, 1, (PARAM_ITEM*) &_pg6},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:CURRent:FREQuency
	{_idCURRentFREQuency, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:CURRent:DUTY
	{_idCURRentDUTY, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:CURRent:CV:RESPonse
	{_idCURRentCVRESPonse, {{1, 1, (PARAM_ITEM*) &_pg32},  {0, 0, (PARAM_ITEM*)0}}},
//:RESistance:RECall
	{_idRESistanceRECall, {{1, 1, (PARAM_ITEM*) &_pg31},  {0, 0, (PARAM_ITEM*)0}}},
//:CONDuctance:RECall
	{_idCONDuctanceRECall, {{1, 1, (PARAM_ITEM*) &_pg31},  {0, 0, (PARAM_ITEM*)0}}},
//:CONDuctance[:VA]
	{_idCONDuctanceVA, {{1, 1, (PARAM_ITEM*) &_pg5},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:CONDuctance:VB
	{_idCONDuctanceVB, {{1, 1, (PARAM_ITEM*) &_pg5},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:RESistance[:VA]
	{_idRESistanceVA, {{1, 1, (PARAM_ITEM*) &_pg4},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:RESistance:VB
	{_idRESistanceVB, {{1, 1, (PARAM_ITEM*) &_pg4},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:RESistance:SRATe
	{_idRESistanceSRATe, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:CONDuctance:L<1|2>
	{_idCONDuctanceL12, {{1, 1, (PARAM_ITEM*) &_pg5},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:CONDuctance:SET
	{_idCONDuctanceSET, {{1, 1, (PARAM_ITEM*) &_pg5},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:RESistance:L<1|2>
	{_idRESistanceL12, {{1, 1, (PARAM_ITEM*) &_pg4},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:RESistance:SET
	{_idRESistanceSET, {{1, 1, (PARAM_ITEM*) &_pg4},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:RESistance:LEVel
	{_idRESistanceLEVel, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:RESistance:RISE
	{_idRESistanceRISE, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:RESistance:FALL
	{_idRESistanceFALL, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:RESistance:T<1|2>
	{_idRESistanceT12, {{1, 1, (PARAM_ITEM*) &_pg6},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:RESistance:FREQuency
	{_idRESistanceFREQuency, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:RESistance:DUTY
	{_idRESistanceDUTY, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:RESistance:CV:RESPonse
	{_idRESistanceCVRESPonse, {{1, 1, (PARAM_ITEM*) &_pg32},  {0, 0, (PARAM_ITEM*)0}}},
//:VOLTage:RECall
	{_idVOLTageRECall, {{1, 1, (PARAM_ITEM*) &_pg31},  {0, 0, (PARAM_ITEM*)0}}},
//:VOLTage[:VA]
	{_idVOLTageVA, {{1, 1, (PARAM_ITEM*) &_pg12},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:VOLTage:VB
	{_idVOLTageVB, {{1, 1, (PARAM_ITEM*) &_pg12},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:VOLTage:RESPonse
	{_idVOLTageRESPonse, {{1, 1, (PARAM_ITEM*) &_pg33},  {0, 0, (PARAM_ITEM*)0}}},
//:POWer:RECall
	{_idPOWerRECall, {{1, 1, (PARAM_ITEM*) &_pg31},  {0, 0, (PARAM_ITEM*)0}}},
//:POWer[:VA]
	{_idPOWerVA, {{1, 1, (PARAM_ITEM*) &_pg24},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:POWer:VB
	{_idPOWerVB, {{1, 1, (PARAM_ITEM*) &_pg24},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:POWer:RESPonse
	{_idPOWerRESPonse, {{1, 1, (PARAM_ITEM*) &_pg33},  {0, 0, (PARAM_ITEM*)0}}},
//:POWer:CV:RESPonse
	{_idPOWerCVRESPonse, {{1, 1, (PARAM_ITEM*) &_pg32},  {0, 0, (PARAM_ITEM*)0}}},
//:FUNCtion[:COMPlete][:RING]:TIME
	{_idFUNCtionCOMPleteRINGTIME, {{1, 1, (PARAM_ITEM*) &_pg13},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:PROGram:STATe
	{_idPROGramSTATe, {{1, 1, (PARAM_ITEM*) &_pg34},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram
	{_idPROGram, {{8, 8, (PARAM_ITEM*) &_pg35},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:RECall]:DEFault
	{_idPROGramRECallDEFault, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram:STARt
	{_idPROGramSTARt, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram:STEP
	{_idPROGramSTEP, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram:MEMory
	{_idPROGramMEMory, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram:RUN
	{_idPROGramRUN, {{1, 1, (PARAM_ITEM*) &_pg36},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram:ONTime
	{_idPROGramONTime, {{1, 1, (PARAM_ITEM*) &_pg37},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram:OFFTime
	{_idPROGramOFFTime, {{1, 1, (PARAM_ITEM*) &_pg38},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram:PFTime
	{_idPROGramPFTime, {{1, 1, (PARAM_ITEM*) &_pg38},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram:STIMe
	{_idPROGramSTIMe, {{1, 1, (PARAM_ITEM*) &_pg38},  {0, 0, (PARAM_ITEM*)0}}},
//[:PROGram]:CHAin:STARt
	{_idPROGramCHAinSTARt, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//[:PROGram]:CHAin
	{_idPROGramCHAin, {{16, 16, (PARAM_ITEM*) &_pg39},  {0, 0, (PARAM_ITEM*)0}}},
//[:PROGram]:CHAin:P2P
	{_idPROGramCHAinP2P, {{2, 2, (PARAM_ITEM*) &_pg40},  {0, 1, (PARAM_ITEM*) &_pg41}}},
//[:PROGram]:CHAin[:RECall]:DEFault
	{_idPROGramCHAinRECallDEFault, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram:SAVE
	{_idPROGramSAVE, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:SEQuence[:COMPlete][:RING]:TIME
	{_idSEQuenceCOMPleteRINGTIME, {{1, 1, (PARAM_ITEM*) &_pg13},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//:NSEQuence:TIMer
	{_idNSEQuenceTIMer, {{1, 1, (PARAM_ITEM*) &_pg42},  {0, 0, (PARAM_ITEM*)0}}},
//:NSEQuence:COTime
	{_idNSEQuenceCOTime, {{1, 1, (PARAM_ITEM*) &_pg43},  {0, 0, (PARAM_ITEM*)0}}},
//:NSEQuence:STATe
	{_idNSEQuenceSTATe, {{1, 1, (PARAM_ITEM*) &_pg34},  {0, 0, (PARAM_ITEM*)0}}},
//:NSEQuence
	{_idNSEQuence, {{9, 9, (PARAM_ITEM*) &_pg44},  {0, 0, (PARAM_ITEM*)0}}},
//:NSEQuence:STARt
	{_idNSEQuenceSTARt, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:NSEQuence:NUMBer
	{_idNSEQuenceNUMBer, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:NSEQuence:MEMO
	{_idNSEQuenceMEMO, {{1, 1, (PARAM_ITEM*) &_pg45},  {0, 0, (PARAM_ITEM*)0}}},
//:NSEQuence:MODE
	{_idNSEQuenceMODE, {{1, 1, (PARAM_ITEM*) &_pg46},  {0, 0, (PARAM_ITEM*)0}}},
//:NSEQuence:RANGe
	{_idNSEQuenceRANGe, {{1, 1, (PARAM_ITEM*) &_pg47},  {0, 0, (PARAM_ITEM*)0}}},
//:NSEQuence:LOOP
	{_idNSEQuenceLOOP, {{1, 1, (PARAM_ITEM*) &_pg48},  {0, 0, (PARAM_ITEM*)0}}},
//:NSEQuence:LLOad
	{_idNSEQuenceLLOad, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:NSEQuence:LAST
	{_idNSEQuenceLAST, {{1, 1, (PARAM_ITEM*) &_pg22},  {0, 0, (PARAM_ITEM*)0}}},
//:NSEQuence:CHAin
	{_idNSEQuenceCHAin, {{1, 1, (PARAM_ITEM*) &_pg49},  {0, 0, (PARAM_ITEM*)0}}},
//:NSEQuence:EDIT
	{_idNSEQuenceEDIT, {{11, 11, (PARAM_ITEM*) &_pg50},  {0, 0, (PARAM_ITEM*)0}}},
//:NSEQuence:EDIT:POINt
	{_idNSEQuenceEDITPOINt, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:NSEQuence:EDIT:END
	{_idNSEQuenceEDITEND, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:NSEQuence[:DELet]:ALL
	{_idNSEQuenceDELetALL, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:NSEQuence:SAVE
	{_idNSEQuenceSAVE, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:FSEQuence:STATe
	{_idFSEQuenceSTATe, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:FSEQuence
	{_idFSEQuence, {{8, 8, (PARAM_ITEM*) &_pg51},  {0, 0, (PARAM_ITEM*)0}}},
//:FSEQuence:MEMO
	{_idFSEQuenceMEMO, {{1, 1, (PARAM_ITEM*) &_pg45},  {0, 0, (PARAM_ITEM*)0}}},
//:FSEQuence:MODE
	{_idFSEQuenceMODE, {{1, 1, (PARAM_ITEM*) &_pg52},  {0, 0, (PARAM_ITEM*)0}}},
//:FSEQuence:RANGe
	{_idFSEQuenceRANGe, {{1, 1, (PARAM_ITEM*) &_pg47},  {0, 0, (PARAM_ITEM*)0}}},
//:FSEQuence:LOOP
	{_idFSEQuenceLOOP, {{1, 1, (PARAM_ITEM*) &_pg48},  {0, 0, (PARAM_ITEM*)0}}},
//:FSEQuence:TBASe
	{_idFSEQuenceTBASe, {{1, 1, (PARAM_ITEM*) &_pg37},  {0, 0, (PARAM_ITEM*)0}}},
//:FSEQuence:LLOad
	{_idFSEQuenceLLOad, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:FSEQuence:LAST
	{_idFSEQuenceLAST, {{1, 1, (PARAM_ITEM*) &_pg22},  {0, 0, (PARAM_ITEM*)0}}},
//:FSEQuence:RPTStep
	{_idFSEQuenceRPTStep, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:FSEQuence:EDIT
	{_idFSEQuenceEDIT, {{4, 4, (PARAM_ITEM*) &_pg53},  {0, 0, (PARAM_ITEM*)0}}},
//:FSEQuence:EDIT:POINt
	{_idFSEQuenceEDITPOINt, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:FSEQuence:EDIT:END
	{_idFSEQuenceEDITEND, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:FSEQuence[:DELet]:ALL
	{_idFSEQuenceDELetALL, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:FSEQuence[:EDIT]:FILL
	{_idFSEQuenceEDITFILL, {{4, 4, (PARAM_ITEM*) &_pg54},  {0, 0, (PARAM_ITEM*)0}}},
//:FSEQuence:SAVE
	{_idFSEQuenceSAVE, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:OCP:STATe
	{_idOCPSTATe, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:OCP:EDIT[:CHANnel]
	{_idOCPEDITCHANnel, {{9, 9, (PARAM_ITEM*) &_pg55},  {0, 0, (PARAM_ITEM*)0}}},
//:OCP[:CHANnel]:TEMP
	{_idOCPCHANnelTEMP, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:OCP[:CHANnel]:RANGe
	{_idOCPCHANnelRANGe, {{1, 1, (PARAM_ITEM*) &_pg56},  {0, 0, (PARAM_ITEM*)0}}},
//:OCP[:CHANnel]:STARt
	{_idOCPCHANnelSTARt, {{1, 1, (PARAM_ITEM*) &_pg22},  {0, 0, (PARAM_ITEM*)0}}},
//:OCP[:CHANnel]:END
	{_idOCPCHANnelEND, {{1, 1, (PARAM_ITEM*) &_pg22},  {0, 0, (PARAM_ITEM*)0}}},
//:OCP[:CHANnel]:STEP:CURRent
	{_idOCPCHANnelStepCurrWattent, {{1, 1, (PARAM_ITEM*) &_pg22},  {0, 0, (PARAM_ITEM*)0}}},
//:OCP[:CHANnel]:LAST
	{_idOCPCHANnelLAST, {{1, 1, (PARAM_ITEM*) &_pg22},  {0, 0, (PARAM_ITEM*)0}}},
//:OCP[:CHANnel]:STEP:TIME
	{_idOCPCHANnelSTEPTIME, {{1, 1, (PARAM_ITEM*) &_pg22},  {0, 0, (PARAM_ITEM*)0}}},
//:OCP[:CHANnel]:DELay
	{_idOCPCHANnelDELay, {{1, 1, (PARAM_ITEM*) &_pg22},  {0, 0, (PARAM_ITEM*)0}}},
//:OCP[:CHANnel]:TRIGger
	{_idOCPCHANnelTRIGger, {{1, 1, (PARAM_ITEM*) &_pg22},  {0, 0, (PARAM_ITEM*)0}}},
//:OCP:SAVE
	{_idOCPSAVE, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:OCP:RESult
	{_idOCPRESult, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:OCP:RUN
	{_idOCPRUN, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:UTILity:SYSTem
	{_idUTILitySYSTem, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:UTILity:REMote
	{_idUTILityREMote, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:UTILity:REMote:MODE
	{_idUTILityREMoteMODE, {{1, 1, (PARAM_ITEM*) &_pg57},  {0, 0, (PARAM_ITEM*)0}}},
//:UTILity:LOAD
	{_idUTILityLOAD, {{1, 1, (PARAM_ITEM*) &_pg58},  {0, 0, (PARAM_ITEM*)0}}},
//:UTILity:LOAD:MODE
	{_idUTILityLOADMODE, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:UTILity:LOAD:RANGe
	{_idUTILityLOADRANGe, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:UTILity:INTerface
	{_idUTILityINTerface, {{1, 1, (PARAM_ITEM*) &_pg59},  {0, 0, (PARAM_ITEM*)0}}},
//:UTILity:TIME
	{_idUTILityTIME, {{5, 5, (PARAM_ITEM*) &_pg60},  {0, 0, (PARAM_ITEM*)0}}},
//:UTILity:KNOB
	{_idUTILityKNOB, {{1, 1, (PARAM_ITEM*) &_pg61},  {0, 0, (PARAM_ITEM*)0}}},
//:UTILity:SPEaker
	{_idUTILitySPEaker, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:UTILity:ALARm
	{_idUTILityALARm, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:UTILity:UNReg
	{_idUTILityUNReg, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:UTILity:GNG
	{_idUTILityGNG, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:UTILity:CONTrast
	{_idUTILityCONTrast, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:UTILity:BRIGhtness
	{_idUTILityBRIGhtness, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:UTILity:LANGuage
	{_idUTILityLANGuage, {{1, 1, (PARAM_ITEM*) &_pg62},  {0, 0, (PARAM_ITEM*)0}}},
//:MEMory:SAVE
	{_idMEMorySAVE, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:MEMory:RECall
	{_idMEMoryRECall, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:PRESet:SAVE
	{_idPRESetSAVE, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:PRESet:RECall
	{_idPRESetRECall, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:SETup:SAVE
	{_idSETupSAVE, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:SETup:RECall
	{_idSETupRECall, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:FACTory[:RECall]
	{_idFACToryRECall, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:USER[:DEFault]:SAVE
	{_idUSERDEFaultSAVE, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:USER[:DEFault]:RECall
	{_idUSERDEFaultRECall, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:SERial[:MASTer]
	{_idSERialMASTer, {{1, 1, (PARAM_ITEM*) &_pg45},  {0, 0, (PARAM_ITEM*)0}}},
//:STATus:PRESet
	{_idSTATusPRESet, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:STATus:QUEStionable:CONDition
	{_idSTATusQUEStionableCONDition, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:STATus:QUEStionable:ENABle
	{_idSTATusQUEStionableENABle, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:STATus:QUEStionable[:EVENt]
	{_idSTATusQUEStionableEVENt, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:STATus:QUEStionable:NTRansition
	{_idSTATusQUEStionableNTRansition, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:STATus:QUEStionable:PTRansition
	{_idSTATusQUEStionablePTRansition, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:STATus:OPERation:CONDition
	{_idSTATusOPERationCONDition, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:STATus:OPERation:ENABle
	{_idSTATusOPERationENABle, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:STATus:OPERation[:EVENt]
	{_idSTATusOPERationEVENt, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:STATus:OPERation:NTRansition
	{_idSTATusOPERationNTRansition, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:STATus:OPERation:PTRansition
	{_idSTATusOPERationPTRansition, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:STATus:CSUMmary:CONDition
	{_idSTATusCSUMmaryCONDition, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:STATus:CSUMmary:ENABle
	{_idSTATusCSUMmaryENABle, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:STATus:CSUMmary[:EVENt]
	{_idSTATusCSUMmaryEVENt, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:STATus:CSUMmary:NTRansition
	{_idSTATusCSUMmaryNTRansition, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:STATus:CSUMmary:PTRansition
	{_idSTATusCSUMmaryPTRansition, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:SYNC:WAIT
	{_idSYNCWAIT, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:SYNC[:DEFault]:RECall
	{_idSYNCDEFaultRECall, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:SYNC:CHEaksum
	{_idSYNCCHEaksum, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:CV
	{_idCV, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:SYSTem:KLOCk
	{_idSYSTemKLOCk, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:CURRent:PROTection[:LEVel][:OVER]
	{_idSOURceCURRentPROTectionLEVelOVER, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//[:SOURce]:CURRent:PROTection:ACTion
	{_idSOURceCURRentPROTectionACTion, {{1, 1, (PARAM_ITEM*) &_pg63},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:CURRent:RANGe
	{_idSOURceCURRentRANGe, {{1, 1, (PARAM_ITEM*) &_pg64},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:CURRent[:LEVel][:IMMediate][:AMPLitude]
	{_idSOURceCURRentLEVelIMMediateAMPLitude, {{1, 1, (PARAM_ITEM*) &_pg3},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:CURRent:SLEW
	{_idSOURceCURRentSLEW, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:POWer:PROTection[:LEVel][:OVER]
	{_idSOURcePOWerPROTectionLEVelOVER, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//[:SOURce]:POWer:PROTection:ACTion
	{_idSOURcePOWerPROTectionACTion, {{1, 1, (PARAM_ITEM*) &_pg63},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:POWer:RANGe
	{_idSOURcePOWerRANGe, {{1, 1, (PARAM_ITEM*) &_pg64},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:POWer[:LEVel][:IMMediate][:AMPLitude]
	{_idSOURcePOWerLEVelIMMediateAMPLitude, {{1, 1, (PARAM_ITEM*) &_pg24},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:CONDuctance[:LEVel][:IMMediate][:AMPLitude]
	{_idSOURceCONDuctanceLEVelIMMediateAMPLitude, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:CONDuctance:RANGe
	{_idSOURceCONDuctanceRANGe, {{1, 1, (PARAM_ITEM*) &_pg64},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:VOLTage:PROTection[:LEVel][:UNDer]
	{_idSOURceVOLTagePROTectionLEVelUNDer, {{1, 1, (PARAM_ITEM*) &_pg16},  {0, 1, (PARAM_ITEM*) &_pg7}}},
//[:SOURce]:VOLTage[:LEVel][:IMMediate][:AMPLitude]
	{_idSOURceVOLTageLEVelIMMediateAMPLitude, {{1, 1, (PARAM_ITEM*) &_pg12},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:VOLTage:PROTection:STATe
	{_idSOURceVOLTagePROTectionSTATe, {{1, 1, (PARAM_ITEM*) &_pg65},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:VOLTage:RANGe
	{_idSOURceVOLTageRANGe, {{1, 1, (PARAM_ITEM*) &_pg29},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:FUNCtion:SSTart
	{_idSOURceFUNCtionSSTart, {{1, 1, (PARAM_ITEM*) &_pg6},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:FUNCtion:RESPonse
	{_idSOURceFUNCtionRESPonse, {{1, 1, (PARAM_ITEM*) &_pg6},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:FUNCtion:CTIMe
	{_idSOURceFUNCtionCTIMe, {{1, 1, (PARAM_ITEM*) &_pg65},  {0, 0, (PARAM_ITEM*)0}}},
//[:SOURce]:FUNCtion[:MODE]
	{_idSOURceFUNCtionMODE, {{1, 1, (PARAM_ITEM*) &_pg66},  {0, 0, (PARAM_ITEM*)0}}},
//PROGram:CLEar
	{_idPROGramCLEar, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//PROGram[:SELected]:STATe
	{_idPROGramSELectedSTATe, {{1, 1, (PARAM_ITEM*) &_pg67},  {0, 0, (PARAM_ITEM*)0}}},
//PROGram[:SELected]:EXECuting
	{_idPROGramSELectedEXECuting, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:NAME
	{_idPROGramSELectedNAME, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:MEMO
	{_idPROGramSELectedMEMO, {{1, 1, (PARAM_ITEM*) &_pg45},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:MODE
	{_idPROGramSELectedMODE, {{1, 1, (PARAM_ITEM*) &_pg68},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:VRANge
	{_idPROGramSELectedVRANge, {{1, 1, (PARAM_ITEM*) &_pg29},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:CRANge
	{_idPROGramSELectedCRANge, {{1, 1, (PARAM_ITEM*) &_pg64},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:LOOP
	{_idPROGramSELectedLOOP, {{1, 1, (PARAM_ITEM*) &_pg48},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:LINPut
	{_idPROGramSELectedLINPut, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:LOUTput
	{_idPROGramSELectedLOUTput, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:LVALue
	{_idPROGramSELectedLVALue, {{1, 1, (PARAM_ITEM*) &_pg22},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:CHAin
	{_idPROGramSELectedCHAin, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:NSPeed[:STEP]:INSert
	{_idPROGramSELectedNSPeedSTEPINSert, {{7, 7, (PARAM_ITEM*) &_pg69},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:NSPeed[:STEP]:ADD
	{_idPROGramSELectedNSPeedSTEPADD, {{6, 6, (PARAM_ITEM*) &_pg70},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:NSPeed[:STEP]:DELete
	{_idPROGramSELectedNSPeedSTEPDELete, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:NSPeed[:STEP]:DELete:ALL
	{_idPROGramSELectedNSPeedSTEPDELeteALL, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:NSPeed[:STEP]:COUNt
	{_idPROGramSELectedNSPeedSTEPCOUNt, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:NSPeed[:STEP]:EDIT
	{_idPROGramSELectedNSPeedSTEPEDIT, {{7, 7, (PARAM_ITEM*) &_pg69},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:FSPeed[:STEP]:END
	{_idPROGramSELectedFSPeedSTEPEND, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:FSPeed[:STEP]:EDIT[:POINt]
	{_idPROGramSELectedFSPeedSTEPEDITPOINt, {{3, 3, (PARAM_ITEM*) &_pg71},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:FSPeed:TIME
	{_idPROGramSELectedFSPeedTIME, {{1, 1, (PARAM_ITEM*) &_pg22},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:FSPeed[:STEP]:EDIT:LINear
	{_idPROGramSELectedFSPeedSTEPEDITLINear, {{4, 4, (PARAM_ITEM*) &_pg72},  {0, 0, (PARAM_ITEM*)0}}},
//:PROGram[:SELected]:FSPeed[:STEP]:EDIT:WAVE
	{_idPROGramSELectedFSPeedSTEPEDITWAVE, {{9, 9, (PARAM_ITEM*) &_pg73},  {0, 0, (PARAM_ITEM*)0}}},
//:SYSTem:GTLocal
	{_idSYSTemGTLocal, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:SYSTem:LLOut
	{_idSYSTemLLOut, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:SYSTem:RENable
	{_idSYSTemRENable, {{1, 1, (PARAM_ITEM*) &_pg2},  {0, 0, (PARAM_ITEM*)0}}},
//:SYSTem:VERSion
	{_idSYSTemVERSion, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:CALibrate:PASSword
	{_idCALibratePASSword, {{1, 1, (PARAM_ITEM*) &_pg1},  {0, 0, (PARAM_ITEM*)0}}},
//:CALibrate:MODE
	{_idCALibrateMODE, {{1, 1, (PARAM_ITEM*) &_pg74},  {0, 0, (PARAM_ITEM*)0}}},
//:CALibrate:RANGe
	{_idCALibrateRANGe, {{1, 1, (PARAM_ITEM*) &_pg75},  {0, 0, (PARAM_ITEM*)0}}},
//:CALibrate:LEVel
	{_idCALibrateLEVel, {{1, 1, (PARAM_ITEM*) &_pg76},  {0, 0, (PARAM_ITEM*)0}}},
//:CALibrate:VALue
	{_idCALibrateVALue, {{1, 1, (PARAM_ITEM*) &_pg22},  {0, 0, (PARAM_ITEM*)0}}},
//:CALibrate:BIValue
	{_idCALibrateBIValue, {{2, 2, (PARAM_ITEM*) &_pg77},  {0, 0, (PARAM_ITEM*)0}}},
//:CALibrate:RUN
	{_idCALibrateRUN, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:CALibrate:PSENsor
	{_idCALibratePSENsor, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
//:CALibrate:SAVE
	{_idCALibrateSAVE, {{0, 0, (PARAM_ITEM*)0},  {0, 0, (PARAM_ITEM*)0}}},
};


