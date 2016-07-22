/******************************************************************************
 * Filename:	thread_Interface.c
 */
//==========================================================
//  include
//==========================================================
#include "scpiMain.h"

//==========================================================
//  DEBUG
//==========================================================

//==========================================================
//  define
//==========================================================

//==========================================================
//  typedef
//==========================================================

//==========================================================
//  struct & variable & constant
//==========================================================

//==========================================================
//  Function
//==========================================================
int isIntegerPoint(unsigned long addr)
{
	return (addr % 4) ? 0 : 1;
}

int isParserThreadError(STR_PARSER *p, char *name)
{
	if(!(isIntegerPoint((unsigned long)&(p->dev)) && isIntegerPoint((unsigned long)&(p->errQueue))&&
		isIntegerPoint((unsigned long)&(p->msgRcv)) && isIntegerPoint((unsigned long)&(p->msgSend)))) {
		_DEBUG_SHOW_THREAD_ERROR(name);
		return -1;
	}
	return 0;
}

int scpiRequestProcess(STR_PARSER *p)
{
	int request = intfRequest_IsRequest(p->pInterface);

	if(0 < request) {
		//--- Main Request ---//
		if(_INTF_REQUEST_RESET & request) {
			//Reset the parser is required.
			scpiInitParser((STR_PARSER_COMD *) (p->pComd));
			p->pComd->pNow = (NODES)&_nodeRoot;
		}
		if(_INTF_REQUEST_ENABLE & request) {
			//Enable the parser is required.
			intfStatus_SetStatus(p->pInterface, _INTF_STATUS_ACTIVE);
		}
		if(_INTF_REQUEST_CLEAN_RX & request) {
			//Clean the Rx-buffer is required.
			if(_DEVICE_PRESENT == (p->ctrl)(_GW_IOCTL_DEV_PRESENT, 0)) {
				(p->ctrl)(_GW_IOCTL_RX_BUF_CLEAN, 0);
			}
		}
		if(_INTF_REQUEST_CLEAN_TX & request) {
			//Clean the Tx-buffer is required.
			if(_DEVICE_PRESENT == (p->ctrl)(_GW_IOCTL_DEV_PRESENT, 0)) {
				(p->ctrl)(_GW_IOCTL_TX_BUF_CLEAN, 0);
			}
		}
		if(_INTF_REQUEST_ADDRESS & request) {
			//Configure the GPIB address or RS485 address.
			if(_DEVICE_PRESENT == (p->ctrl)(_GW_IOCTL_DEV_PRESENT, 0)) {
				unsigned int addr;
				if(intfRequest_GetData(p->pInterface, _INTF_REQUEST_ADDRESS, (unsigned long)&addr) == 0) {
					(p->ctrl)(_GW_IOCTL_SET_ADDRESS, addr);
				}
			}
		}
		if(_INTF_REQUEST_TERMINAL & request) {
			//Configure terminal.
			if(_DEVICE_PRESENT == (p->ctrl)(_GW_IOCTL_DEV_PRESENT, 0)) {
				int data;//struct termios data;
				if(intfRequest_GetData(p->pInterface, _INTF_REQUEST_TERMINAL, (unsigned long)&data) == 0) {
					(p->ctrl)(_GW_IOCTL_TERMINAL, (unsigned long)&data);
				}
			}
		}
		if(_INTF_REQUEST_DISABLE & request) {
			//Disable the parser is required.
		#if 0
			if(_DEVICE_PRESENT == (p->ctrl)(_GW_IOCTL_DEV_PRESENT, 0)) {
				scpi_InitErrorQueue(p);
				(p->ctrl)(_GW_IOCTL_RX_BUF_CLEAN, 0);
				(p->ctrl)(_GW_IOCTL_TX_BUF_CLEAN, 0);
				(p->close)();
				sleep(1);
			}
		#endif
			intfStatus_CleanStatus(p->pInterface, _INTF_STATUS_ACTIVE);
		}
	}
	return request;
}

int scpiRequestReturn(STR_PARSER *p)
{
	return intfRequest_Clean(p->pInterface);
}

