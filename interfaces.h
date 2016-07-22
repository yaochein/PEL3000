#ifndef INTERFACE_H
#define INTERFACE_H

void InterfaceTask(void *para);

extern void (*WOutgoBuffer)(UBYTE *, UBYTE);
extern void (*WBOutgoBuffer)(UBYTE *, ULONG, UBYTE);
extern gpibpar GPIBPAR;
extern rs_232 RS232;
extern void USBCDC_WBOutGoBuffer(unsigned char *Block, ULONG BSize, unsigned char end_flag);
extern void USBCDC_WOutGoBuffer(unsigned char * STR,unsigned char end_flag);
char UART_ParserGetc(unsigned char *err);
char USBCDC_ParserGetc(unsigned char *err);
char GPIB_ParserGetc(unsigned char *err);
void disconnect_USB(void);
void connect_USB(void);

#define GPIB_CONNECTED	    0x01

//for RmtProcessCtrl
#define RCMD_NOTIFY 0  /*Notifying remote command.*/
#define RCMD_PARSER_CMD 1 /*Parsing remote command.*/
#define RCMD_WAITING_DAT 2  /*Waiting for remote data.*/
#define RCMD_FINAL_CMD 3 /*Get the final command*/
#define RCMD_STOP   99 /*STOP RCMD Process*/

#ifdef INTERFACE_GLOBALS
#define INTERFACE_EXT
#else
#define INTERFACE_EXT extern
#endif
//Globle Vars
INTERFACE_EXT volatile UBYTE SYSType;
INTERFACE_EXT OS_EVENT *InterfaceReadySemPtr;

#endif   /* ifdef INTERFACE_H */


