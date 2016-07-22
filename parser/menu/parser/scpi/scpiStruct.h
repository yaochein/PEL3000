#ifndef __SCPI_STRUCT_H__
#define __SCPI_STRUCT_H__

//==========================================================
//  include
//==========================================================
////#include "gw_board.h"
#include "../dev/gwMsgQueue.h"
#include "scpiRegister.h"

//==========================================================
//  define
//==========================================================

//----------------------------------
//--- Communicate Interface --------
#define _COMM_GPIB		0
#define _COMM_USB		1
#define _COMM_SOCKETS	2
#define _COMM_WEB		3
#define _COMM_UART		4

//---------------------------
//--- Command Supply --------
#define _COMMAND_AGILENT	0
#define _COMMAND_KEPCO		0
#define _COMMAND_KIKUSU		0
#define _COMMAND_PSH		1
#define _COMMAND_TAKASAGO	0
#define _COMMAND_TEST_READ	1
#define _COMMAND_TEST_FAN	0
#define _COMMAND_TEST_BLOCK	0
#define _COMMAND_TEST_VP2VP	0

//---------------------------
//--- Error Queue -----------
#define _ERROR_QUEUE_SIZE	16

//---------------------------
//--- Command Type ---
// 1. S: Set command.
// 2. Q: Query command.
// 3. R: Required suffix variable.
// 4. O: Optional suffix variable.
#define T____	0x00 //Not command & No suffix variable.
#define T___S	0x01 //Set command & No suffix variable.
#define T__Q_	0x02 //Query command & No suffix variable.
#define T__QS	0x03 //Set & Query command & No suffix variable.
#define T_R__	0x10 //Not command & Required suffix variable.
#define T_R_S	0x11 //Set command & Required suffix variable.
#define T_RQ_	0x12 //Query command & Required suffix variable.
#define T_RQS	0x13 //Set & Query command & Required suffix variable.
#define TO___	0x20 //Not command & Optional suffix variable.
#define TO__S	0x21 //Set command & Optional suffix variable.
#define TO_Q_	0x22 //Set & Query command & Optional suffix variable.
#define TO_QS	0x23 //Set & Query command & Optional suffix variable.

#define T_QUERY_MASK	0x03
#define T_SUFFIX_MASK	0x30

//---------------------------
//--- Parameter Type---
#define _NOP    0/* No parameter */
#define _OPT    1/* Optional parameter */
#define _REQ    2/* Required parameter */

//---------------------------
//--- SCPI DEFINE ---
#define _SCPI_COMMAND_LENGTH_MAX    12
#define _SCPI_COMMAND_LEVEL_MAX     6
#define _SCPI_PARAMETER_LENGTH_MAX	256
#define _SCPI_PARAMETER_LEVEL_MAX	100
#define _SCPI_UNIT_LENGTH_MAX		12
#define _SCPI_PARAMETER_BUFFER_SIZE	(1024*1024+1024)

//---------------------------
//--- PARSER Function ---

#define _PARSER_GET_COMMAND			0
#define _PARSER_CHECK_COMMAND		1
#define _PARSER_GET_PARAMETER		2
#define _PARSER_CHECK_PARAMETER		3
#define _PARSER_PACKAGE_MSQ			4
#define _PARSER_SEND_MSQ			5
#define _PARSER_RECEIVE_MSQ			6
#define _PARSER_GET_ENDWORD			7
#define _PARSER_GET_NEXT_COMMAND	8
#define _PARSER_SPECIAL_PROCESS		9
//---------------------------
//--- PARAMETER TYPE ---
#define _NODATA		0		//no data.
#define _NUMBER		0x01	//number(integer).
#define _KEYWORD	0x02	//keyword.
#define _STRING1	 	0x04	//string.
#define _FLOAT		0x08	//double.
#define _EXPRESSION	0x10	//Expression program data.
#define _BLOCK		0x20	//Block data.
#define _LIST		0x40	//list.
#define _OPTION		0x80	//option.

#define _HAVE_PARAM	(_NUMBER | _KEYWORD | _STRING1 | _FLOAT | _EXPRESSION | _BLOCK)	//Have Parameter.

//---------------------------
//--- UNIT DEFINE ---
#define _VOLT			1
#define _AMP			2
#define _OHM			3
#define _WATT			4
#define _DB_W			5
#define _JOULE			6
#define _FARAD			7
#define _HENRY			8
#define _HERTZ			9
#define _SEC			10
#define _TEMPERATURE	11
#define _MHO			12


//---------------------------
//--- Data Process ---
// Used by STR_PARSER_PARAM.p_status
#define _DP_N_SIGN 	    (1<< 0)
#define _DP_N_INTEGER	(1<< 1)
#define _DP_N_DOT		(1<< 2)
#define _DP_N_DECIMAL	(1<< 3)
#define _DP_N_SPACE1	(1<< 4)
#define _DP_E_SYMBOL	(1<< 5)
#define _DP_N_SPACE2	(1<< 6)
#define _DP_E_SIGN 	    (1<< 7)
#define _DP_E_INTEGER	(1<< 8)
#define _DP_N_SPACE3	(1<< 9)
#define _DP_N_UNIT 	    (1<< 10)
#define _DP_N_SPACE4	(1<< 11)

//==========================================================
//  typedef & struct
//==========================================================

#pragma pack(1)

//------------------------------------------------------
//--- SPECIAL TYPE ---
typedef union _COMMON_TYPE{
	char	sc[8];
	short	ss[4];
	int 	si;
	long	sl;
	float	f;
	unsigned char	uc[8];
	unsigned short	us[4];
	unsigned int	ui;
	unsigned long	ul;
	double			d;
} COMMON_TYPE;

//------------------------------------------------------
//--- PARAMETER TYPE ---
typedef union _STR_PARAMETER_TYPE{
	unsigned int data;
	struct {
		unsigned int num		:1;//bit 0; number /integer.
		unsigned int kw			:1;//bit 1; keyword.
		unsigned int str		:1;//bit 2; string.
		unsigned int fl			:1;//bit 3; double.
		unsigned int expr		:1;//bit 4; Expression program data.
   		unsigned int block		:1;//bit 5; block data. definitely length & indefinite length arbitrary block program data.
		unsigned int list		:1;//bit 6; list.
		unsigned int opt		:1;//bit 7; option.
		unsigned int reserved	:24;//bit 8~31.
	};
} PARAM_TYPE;

//------------------------------------------------------
//--- COMMAND WORD ---
typedef struct _STR_COMD_WORD {//size=6bytes.
    int min;   /* Required Minimum Length of command   */
    int max;   /* Required Maximum Length of command   */
    char *word;  
} COMD_WORD;

typedef struct _STR_COMD_SUFFIX {//size=8bytes.
    int min;   /* Minimum of Numeric Suffix, ext. channel<x> , x = 1,2,3,... */
    int max;   /* Maximum of Numeric Suffix, ext. channel<x> , x = 1,2,3,... */
} COMD_SUFFIX;

//------------------------------------------------------
//--- COMMAND NODE ---
typedef  struct _STR_COMD_NODE *NODES;//size=4bytes.
typedef struct  _STR_COMD_NODE {//size=14bytes.
    NODES           parant; /* point to it's parant node */
    NODES           *son;   /* point to it's son node    */
    COMD_WORD       *name;  /* name of current node      */
	COMD_SUFFIX     *suffix;/* numeric suffix            */
    unsigned int    type;   /* bit0:Set command, bit1:Query command */
    unsigned int    id;
} NODE;

//--------------------------------------
//--- PARAMETER UNIT ---
typedef struct _STR_PARAMETER_UNIT {
	const char    *sunit;	/* Pointer to start of Units String (e.g. "UV")*/
	int   exp;	/* Exponent of units, e.g. -6 for microvolts if volts are base units*/
} PARAM_UNIT;

//--------------------------------------
//--- PARAMETER KEYWORD ---
typedef struct _STR_PARAMETER_KEYWORD {
	COMD_WORD 		*name;//keyword.
	unsigned int    value;//value.
} PARAM_KEYWORD;

//--------------------------------------
//--- PARAMETER ITEM ---
typedef struct _SCPI_PARAMETER_ITEM {
	PARAM_TYPE      type;
	unsigned int    unit;
	PARAM_KEYWORD	*keys;
} PARAM_ITEM;

//--------------------------------------
//--- PARAMETERS ---
typedef struct _STR_PARAMETERS {
	unsigned int	min;
	unsigned int	max;
	PARAM_ITEM		*items;
} STR_PARAMS;

typedef struct _STR_PARAMETERS_1 {
	unsigned int	id;
	STR_PARAMS		data[2];
} __attribute__((packed)) STR_PARAMS1;

//--------------------------------------
//--- PARAMETER INFORMATION ---
typedef struct _STR_PARAMETER_INFORMATION {
    PARAM_TYPE      type;
    unsigned int	size;	// the size of data.
    char			*addr;	// point to parameter buffer.
} PARAM_INF ;

//--------------------------------------
//--- PARSER DATA ---
typedef struct _STR_PARSER_DATA {
	unsigned int  	id;
	unsigned int	dev;
	unsigned int	query;
	unsigned int	number; //number of information.
	unsigned int	total; //use capacity of buffer.
	int				suf_level;
	int				suffix[_SCPI_COMMAND_LEVEL_MAX];//numeric suffix.ext. memory<x>, channel<x>.
	PARAM_INF		info[_SCPI_PARAMETER_LEVEL_MAX];//the information of data.
	char			buf[_SCPI_PARAMETER_BUFFER_SIZE];
} STR_PARSER_DATA;

//--------------------------------------
//--- COMMAND PROCESS ---
typedef struct _STR_PARSER_COMD {
    //-------------------------------------------------------------------------
    //--- command process ---
	int   fun; //function.
	int   cnt; //counter.
	int   level;
    union {
        unsigned int status;
        struct {
		unsigned int reset			:1;//bit0, tree reset.
		unsigned int asterisk 		:1;//bit1, 0x2A,'*'.
		unsigned int colon 			:1;//bit2, 0x3A,':'.
		unsigned int query 			:1;//bit3, 0:Set Command;1:Query Command.
		unsigned int mhp			:1;//bit4, May have parameters; White Spase ,or 0x2C,','.
		unsigned int space			:1;//bit5, 0x00~0x09,0x0b~0x20.
		unsigned int endword		:1;//bit6, '\n' or '\r'.
		unsigned int double_quote	:1;//bit7, string, Double Quote Head.
		unsigned int dq_start		:1;//bit8, Double Quote character, string start, 0x22, '\"'.
		unsigned int dq_end			:1;//bit9, Double Quote character, string end, 0x22, '\"'.
		unsigned int single_quote	:1;//bit10, string, Single Quote Head.
		unsigned int sq_start		:1;//bit11, Single Quote character, string start, 0x27, '\''.
		unsigned int sq_end			:1;//bit12, Single Quote character, string end, 0x27, '\''.
		unsigned int block			:1;//bit13.Is a '#' font at the beginning of the large amounts of data.
		unsigned int suffix			:1;//bit14, Have suffix variable.
		unsigned int no_suffix		:1;//bit15, Arabic numerals as the standard characters, not the suffix variable.
		unsigned int idn			:1;//bit16, Have "idn?" command.
		unsigned int reserved		:15;//bit17~31.
        };
    };
	int  err;
	int  check;
    char com[_SCPI_COMMAND_LEVEL_MAX][_SCPI_COMMAND_LENGTH_MAX];//command buf.
    int  len[_SCPI_COMMAND_LEVEL_MAX];//command length.
    char suf_com[_SCPI_COMMAND_LEVEL_MAX][_SCPI_COMMAND_LENGTH_MAX];//character of suffix variable.ext. memory<x>, channel<x>.
    int  suf_len[_SCPI_COMMAND_LEVEL_MAX];//length of suffix variable.
    int  suf_var[_SCPI_COMMAND_LEVEL_MAX];//suffix variable.ext. memory<x>, channel<x>.
    char *pCmd;
    NODES pNow;
} STR_PARSER_COMD ;

//--------------------------------------
//--- PARAM PROCESS ---



typedef struct _STR_PARSER_PARAM {
    //-------------------------------------------------------------------------
    //--- parameter process ---
    // number   : [+/-][integer][Dot][decimal][{e/E}[+/-][integer]][space1][unit][space2] { ',' | '\n' | '\r' }
    // Keyword : {min | max | def}[space1] { ',' | '\n' | '\r' }
    // string     : "(start)string1"(end)["(start)stringN"(end)][space1] { ',' | '\n' | '\r' }
	union {
		unsigned int p_status;
		struct {
			//--- nmuber process ---
			// number	: [+/-][integer][Dot][decimal][space1][{e/E}[space2][+/-][integer]][space3][unit][space4] { ',' | '\n' | '\r' }
			unsigned int n_sign		:1;//bit0, number '-' or '+'.
			unsigned int n_integer	:1;//bit1, integer number.
			unsigned int n_dot		:1;//bit2, dot.
			unsigned int n_decimal	:1;//bit3, decimal.
			unsigned int n_space1	:1;//bit4, space1.
			unsigned int e_symbol 	:1;//bit5, exponential symbol, 'E' or 'e'.
			unsigned int n_space2	:1;//bit6, space2.
			unsigned int e_sign		:1;//bit7, exponential '-' or '+'.
			unsigned int e_integer	:1;//bit8, exponential number.
			unsigned int n_space3	:1;//bit9, space3.
			unsigned int n_unit		:1;//bit10, unit.
			unsigned int n_space4	:1;//bit11, space4.

			//--- string process ---
			unsigned int dq_start	:1;//bit12, Double Quote character, string start, 0x22, '\"'.
			unsigned int dq_end		:1;//bit13, Double Quote character, string end, 0x22, '\"'.
			unsigned int sq_start	:1;//bit14, Single Quote character, string start, 0x27, '\''.
			unsigned int sq_end		:1;//bit15, Single Quote character, string end, 0x27, '\''.
			//--- parameter type ---
			unsigned int t_num		:1;//bit16,Numeric Value type.
			unsigned int t_kw		:1;//bit17,keyword type.
			unsigned int t_str		:1;//bit18,string type.
			unsigned int t_base2	:1;//bit19,Binary base data.
			unsigned int t_base8	:1;//bit20,Octonary base data.
			unsigned int t_base16	:1;//bit21,Hexadecimal base data.
			unsigned int t_block_def:1;//bit22,arbitrary block program data, definitely length.
			unsigned int t_block_ind:1;//bit23,arbitrary block program data, indefinitely length.
			unsigned int t_n_dec	:1;//bit24,Non-Decimal numberic program data.
			unsigned int t_express	:1;//bit25,Expression program data,ext: "(@1:3)" or "(6/20)".
			//--- active ---
			unsigned int get_count	:1;//bit26, get <byte count>.
			unsigned int open_paren	:1;//bit27. Open parenthesis,0x28,'('.
			unsigned int at_sign	:1;//bit28. at sign, 0x40, '@'.
			unsigned int colon		:1;//bit29. colon, 0x3A, ':'.
			unsigned int close_paren:1;//bit30. Close parenthesis,0x29,')'.
			//--- reserved ---
			unsigned int bit31		:1;//bit31.
		};
	};
	unsigned int p_len;//parameter length.
	unsigned int u_len;//unit length.
	char p_buf[_SCPI_PARAMETER_LENGTH_MAX];//parameter buffer.
	char u_buf[_SCPI_UNIT_LENGTH_MAX];//unit buffer.
    //-------------------------------------------------------------------------
    //save the data of block data.
    //Defined length of block data. Format : #<number digits in byte count><byte count><Byte1><Byte2>...<ByteN>.
    //Undefined length of block data. Format : #0<Byte1><Byte2>...<ByteN>+NL+^END.
	int bd_digital;	//number digits in byte count.
	int bd_count;	//byte count.
	int bd_data;	//data count.
    //-------------------------------------------------------------------------
    //save the data from string to number.
    COMMON_TYPE change;
} STR_PARSER_PARAM ;



//--------------------------------------
//--- ERROR QUEUE ---
typedef struct _STR_ERROR_QUEUE {
	int cnt;
	int inptr;
	int outptr;
	int buf[_ERROR_QUEUE_SIZE];
} STR_ERROR_QUEUE;

//--------------------------------------
typedef struct _STR_SPECIAL_PROCESS {
	int act;
	int ctr;
	char *buf;
	char file_name[128];
} STR_SPECIAL_PROCESS;

//---------------------------------------------------------------------------------------
// --- Defined length of block Program Data ---
// format : #<number digits in byte count><byte count><Byte1><Byte2>...<ByteN>+NL.
// <Byte1><Byte2>...<ByteN> : <mode><reserved><file data><checksum>.
// <mode> : 1byte.
// <reserved> : 1byte.
// <file data> : N byte.
// <checksum> : 2bytes. <checksum> = <mode> + <reserved> + <file data> byte sum.

typedef struct _STR_BLOCK_INFORMATION {
	int number_digit;
	int byte_count;
	char *block_data;
} __attribute__((packed)) STR_BLOCK_INFO;

#pragma pack()

//--------------------------------------
//--- SCPI PARSER ---

typedef struct _STR_PARSER {//size=978bytes.
    int	dev;
	//-------------------------------------------------------------------------
	int countQuery;
	//-------------------------------------------------------------------------
	//--- ERROR QUEUE ---
	STR_ERROR_QUEUE errQueue;
	//-------------------------------------------------------------------------
	STR_MESSAGE_QUEUE msgRcv, msgSend;
	//-------------------------------------------------------------------------
	STR_SPECIAL_PROCESS specProc;
	//-------------------------------------------------------------------------
	STR_INTF	*pInterface;
    //-------------------------------------------------------------------------
    //--- command process ---
    STR_PARSER_COMD  *pComd;
    //-------------------------------------------------------------------------
    //--- parameter process ---
    STR_PARSER_PARAM *pParam;
	//-------------------------------------------------------------------------
	STR_PARSER_DATA	 *pData;//parameter data.
	//-------------------------------------------------------------------------
	int (*init) (void);
	int (*open) (void);
	int (*write)(char *, unsigned int, unsigned int);
	int (*read) (char *, unsigned int, unsigned int);
	int (*ctrl) (unsigned int, unsigned long);
	int (*close)(void);
	int (*release)(void);
} STR_PARSER ;

//__attribute__((aligned (4),packed))

//--------------------------------------
#endif //__SCPI_STRUCT_H__


