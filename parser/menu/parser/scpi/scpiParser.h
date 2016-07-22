#ifndef __SCPI_PARSER_H__
#define __SCPI_PARSER_H__

#include "scpiStruct.h"
#include "../../Parser_Lib/Parser.h"

extern void scpiInitParser(STR_PARSER_COMD *p);
extern void scpiParser(STR_PARSER *p);
//extern void scpiSendMSQ(STR_PARSER *p);
//extern int scpiReceiveMSQ(STR_PARSER *p);
extern void scpiRunMSQ(void);

//-----------------------------------------------
extern int lua_MsgQueue(STR_PARSER *p, unsigned int id, unsigned int query, unsigned int num, PARAM_INF *param);

#endif //__SCPI_PARSER_H__

