
//==========================================================
//  include
//==========================================================
//#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
#include <math.h>

//#include "gw_board.h"
//#include "gw_CLib.h"
//#include "gwFunction.h"
//#include "gwMassMem.h"
#include "scpiStruct.h"
#include "scpiError.h"
#include "scpiNode.h"
#include "scpiUnit.h"
#include "scpiErrQueue.h"
#include "scpiID.h"
#include "scpiAPI.h"
#include "tty/devTtyDefine.h"

//==========================================================
//  Debug
//==========================================================

//==========================================================
//  Define
//==========================================================

//==========================================================
//  typedef & struct
//==========================================================

//==========================================================
//  variable & constant
//==========================================================

//==========================================================
//  Function
//==========================================================

int scpiSpecialProcess(STR_PARSER *p)
{
#if 0
	STR_PARSER_COMD *pComd = (STR_PARSER_COMD *) (p->pComd);
	STR_PARSER_DATA *pData = (STR_PARSER_DATA*)  (p->pData);
	int fd = 0, file_size = 0, head_size = 0, read_size = 0, err = 0;
	char *pblock;

	if(_PARSER_SPECIAL_PROCESS == pComd->fun) {
		if(_idMEMoryDATATST == pData->id) { /*
			if(1 == p->specProc.act) {
				pblock = (char *)registerMassMemory();
				if(0 != pblock) {
					file_size = getFileSize(p->specProc.file_name);
					if(getSizeMassMemory() < file_size) {
						scpi_SetCommandError( p, _ERR_291_Out_of_memory);
						err = -1;
					}
					else {
						if(0 < file_size) {
							head_size = doBlockHead(pblock, file_size);
							if(0 < head_size) {
								fd = open(p->specProc.file_name, O_RDONLY);
								if(-1 == fd) { //open file is error.
									scpi_SetCommandError( p, _ERR_250_Mass_storage_error);
									err = -1;
								}
								else {
									read_size = read(fd, (char*)(pblock + head_size), file_size);
									close(fd);
									usleep(2000);
									sync();
									if(read_size != file_size) {
										scpi_SetCommandError( p, _ERR_310_System_error);
										err = -1;
									}
									swapByte((char*)(pblock + head_size), file_size);
									usleep(2000);
								}
							}
							else {
								scpi_SetCommandError( p, _ERR_310_System_error);
								err = -1;
							}
						}
						else {
							file_size = 0;
							read_size = 0;
						}
					}

					if(0 == err) {
						//----------------------------------------------------------------
						p->specProc.buf = (char *) pblock;
						p->specProc.ctr = head_size + file_size;
						scpi_Write(p, p->specProc.buf, p->specProc.ctr, _GW_IOWR_BULK, 0);
						//--approve temporary data.--
						(p->write)(0, 0, _GW_IOWR_BUF_APP);
						//----------------------------------------------------------------
						p->specProc.act = 2;
					}
					else {
						freeMassMemory();
						p->specProc.act = 0;
					}
				}
				else {
					scpi_SetCommandError( p, _ERR_290_Memory_use_error);
					p->specProc.act = 0;
				}
			}
			else if(2 == p->specProc.act) {
				if(0 == scpi_IsEmptyOutputBuffer(p)) {
					freeMassMemory();
					p->specProc.act = 0;
				}
			} */
		}
		else if(_idMEMoryDATACSV == pData->id) {
			if(1 == p->specProc.act) {
				pblock = (char *)registerMassMemory();
				if(0 != pblock) {
					file_size = getFileSize(p->specProc.file_name);
					if(getSizeMassMemory() < file_size) {
						scpi_SetCommandError( p, _ERR_291_Out_of_memory);
						err = -1;
					}
					else {
						if(0 < file_size) {
							head_size = doBlockHead(pblock, file_size);
							if(0 < head_size) {
								fd = open(p->specProc.file_name, O_RDONLY);
								if(-1 == fd) { //open file is error.
									scpi_SetCommandError( p, _ERR_250_Mass_storage_error);
									err = -1;
								}
								else {
									read_size = read(fd, (char*)(pblock + head_size), file_size);
									close(fd);
									usleep(2000);
									sync();
									if(read_size != file_size) {
										scpi_SetCommandError( p, _ERR_310_System_error);
										err = -1;
									}
								}
							}
							else {
								scpi_SetCommandError( p, _ERR_310_System_error);
								err = -1;
							}
						}
						else {
							file_size = 0;
							read_size = 0;
						}
					}

					if(0 == err) {
						//----------------------------------------------------------------
						p->specProc.buf = (char *) pblock;
						p->specProc.ctr = head_size + file_size;
						scpi_Write(p, p->specProc.buf, p->specProc.ctr, _GW_IOWR_BULK, 0);
						//--approve temporary data.--
						(p->write)(0, 0, _GW_IOWR_BUF_APP);
						//----------------------------------------------------------------
						p->specProc.act = 2;
					}
					else {
						freeMassMemory();
						p->specProc.act = 0;
					}
				}
				else {
					scpi_SetCommandError( p, _ERR_290_Memory_use_error);
					p->specProc.act = 0;
				}
			}
			else if(2 == p->specProc.act) {
				if(0 == scpi_IsEmptyOutputBuffer(p)) {
					freeMassMemory();
					p->specProc.act = 0;
				}
			} */
		}
		else if(_idMMEMoryDATA == pData->id) {
			if(1 == p->specProc.act) { /*
				pblock = (char *)registerMassMemory();
				if(0 != pblock) {
					file_size = getFileSize(p->specProc.file_name);
					if(getSizeMassMemory() < file_size) {
						scpi_SetCommandError( p, _ERR_291_Out_of_memory);
						err = -1;
					}
					else {
						if(0 < file_size) {
							head_size = doBlockHead(pblock, file_size);
							if(0 < head_size) {
								fd = open(p->specProc.file_name, O_RDONLY);
								if(-1 == fd) { //open file is error.
									scpi_SetCommandError( p, _ERR_250_Mass_storage_error);
									err = -1;
								}
								else {
									read_size = read(fd, (char*)(pblock + head_size), file_size);
									close(fd);
									usleep(2000);
									sync();
									if(read_size != file_size) {
										scpi_SetCommandError( p, _ERR_310_System_error);
										err = -1;
									}
								}
							}
							else {
								scpi_SetCommandError( p, _ERR_310_System_error);
								err = -1;
							}
						}
						else {
							file_size = 0;
							read_size = 0;
						}
					}

					if(0 == err) {
						//----------------------------------------------------------------
						p->specProc.buf = (char *) pblock;
						p->specProc.ctr = head_size + file_size;
						scpi_Write(p, p->specProc.buf, p->specProc.ctr, _GW_IOWR_BULK, 0);
						//--approve temporary data.--
						(p->write)(0, 0, _GW_IOWR_BUF_APP);
						//----------------------------------------------------------------
						p->specProc.act = 2;
					}
					else {
						freeMassMemory();
						p->specProc.act = 0;
					} */
				}
				else {
					scpi_SetCommandError( p, _ERR_290_Memory_use_error);
					p->specProc.act = 0;
				}
			}
			else if(2 == p->specProc.act) {
				if(0 == scpi_IsEmptyOutputBuffer(p)) {
					freeMassMemory();
					p->specProc.act = 0;
				}
			}
		}

		if(0 == p->specProc.act) {
		//	pComd->err = _ERR_000_No_Error;
			pComd->fun = _PARSER_GET_NEXT_COMMAND;
		}
	} */

#endif
	return 0;
}

