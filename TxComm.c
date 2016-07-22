#include "keydef.h"
#include <app.h>
#include "TxComm.h"

/************************************/
UBYTE TxBoardCastInit=0x00;
/************************************/
extern char DispMode,TXData[250];
float Maximum_Select(float *data, char number)
	{
	float Maximum_data=0;
	char i;
		for(i=0;i<number;i++)
			{
			if(*data>Maximum_data)
				Maximum_data=*data;
			data++;
			}
	return Maximum_data;
	}

