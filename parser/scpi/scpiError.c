#include "scpiError.h"

//=============================================================================
//  include
//=============================================================================

//=============================================================================
//  Define
//=============================================================================

//=========================================================
//=== 1999 SCPI Define Error String ===

//-------------------------------------
//--- Command No Errors. ---
#define _sERR_000 "+0, \"No error.\""

//-------------------------------------
//--- Command errors. ---
// The command error bit in the standard Event Status Register (ESR) is set to ．1' when such an error occurs.
#define _sERR_100    "-100, \"Command error\""
#define _sERR_101    "-101, \"Invalid character\""
#define _sERR_102    "-102, \"Syntax error\""
#define _sERR_103    "-103, \"Invalid separator\""
#define _sERR_104    "-104, \"Data type error\""
#define _sERR_105    "-105, \"GET not allowed\""
#define _sERR_108    "-108, \"Parameter not allowed\""
#define _sERR_109    "-109, \"Missing parameter\""
#define _sERR_110    "-110, \"Command header error\""
#define _sERR_111    "-111, \"Header separator error\""
#define _sERR_112    "-112, \"Program mnemonic too long\""
#define _sERR_113    "-113, \"Undefined header\""
#define _sERR_114    "-114, \"Header suffix out of range\""
#define _sERR_115    "-115, \"Unexpected number of parameters\""
#define _sERR_120    "-120, \"Numeric data error\""
#define _sERR_121    "-121, \"Invalid character in number\""
#define _sERR_123    "-123, \"Exponent too large\""
#define _sERR_124    "-124, \"Too many digits\""
#define _sERR_128    "-128, \"Numeric data not allowed\""
#define _sERR_130    "-130, \"Suffix error\""
#define _sERR_131    "-131, \"Invalid suffix\""
#define _sERR_134    "-134, \"Suffix too long\""
#define _sERR_138    "-138, \"Suffix not allowed\""
#define _sERR_140    "-140, \"Character data error\""
#define _sERR_141    "-141, \"Invalid character data\""
#define _sERR_144    "-144, \"Character data too long\""
#define _sERR_148    "-148, \"Character data not allowed\""
#define _sERR_150    "-150, \"String data error\""
#define _sERR_151    "-151, \"Invalid string data\""
#define _sERR_158    "-158, \"String data not allowed\""
#define _sERR_160    "-160, \"Block data error\""
#define _sERR_161    "-161, \"Invalid block data\""
#define _sERR_168    "-168, \"Block data not allowed\""
#define _sERR_170    "-170, \"Expression error\""
#define _sERR_171    "-171, \"Invalid expression\""
#define _sERR_178    "-178, \"Expression data not allowed\""
#define _sERR_180    "-180, \"Macro error\""
#define _sERR_181    "-181, \"Invalid outside macro definition\""
#define _sERR_183    "-183, \"Invalid inside macro definition\""
#define _sERR_184    "-184, \"Macro parameter error\""


//-------------------------------------
//--- Execution errors ---
// The execution error bit in the standard Event Status Register (ESR) is set to ．1' when such an error occurs.
#define _sERR_200    "-200, \"Execution error\""
#define _sERR_201    "-201, \"Invalid while in local\""
#define _sERR_202    "-202, \"Settings lost due to rtl\""
#define _sERR_203    "-203, \"Command protected\""
#define _sERR_210    "-210, \"Trigger error\""
#define _sERR_211    "-211, \"Trigger ignored\""
#define _sERR_212    "-212, \"Arm ignored\""
#define _sERR_213    "-213, \"Init ignored\""
#define _sERR_214    "-214, \"Trigger deadlock\""
#define _sERR_215    "-215, \"Arm deadlock\""
#define _sERR_220    "-220, \"Parameter error\""
#define _sERR_221    "-221, \"Settings conflict\""
#define _sERR_222    "-222, \"Data out of range\""
#define _sERR_223    "-223, \"Too much data\""
#define _sERR_224    "-224, \"Illegal parameter value\""
#define _sERR_225    "-225, \"Out of memory\""
#define _sERR_226    "-226, \"Lists not same length\""
#define _sERR_230    "-230, \"Data corrupt or stale\""
#define _sERR_231    "-231, \"Data questionable\""
#define _sERR_232    "-232, \"Invalid format\""
#define _sERR_233    "-233, \"Invalid version\""
#define _sERR_240    "-240, \"Hardware error\""
#define _sERR_241    "-241, \"Hardware missing\""
#define _sERR_250    "-250, \"Mass storage error\""
#define _sERR_251    "-251, \"Missing mass storage\""
#define _sERR_252    "-252, \"Missing media\""
#define _sERR_253    "-253, \"Corrupt media\""
#define _sERR_254    "-254, \"Media full\""
#define _sERR_255    "-255, \"Directory full\""
#define _sERR_256    "-256, \"File name not found\""
#define _sERR_257    "-257, \"File name error\""
#define _sERR_258    "-258, \"Media protected\""
#define _sERR_260    "-260, \"Expression error\""
#define _sERR_261    "-261, \"Math error in expression\""
#define _sERR_270    "-270, \"Macro error\""
#define _sERR_271    "-271, \"Macro syntax error\""
#define _sERR_272    "-272, \"Macro execution error\""
#define _sERR_273    "-273, \"Illegal macro label\""
#define _sERR_274    "-274, \"Macro parameter error\""
#define _sERR_275    "-275, \"Macro definition too long\""
#define _sERR_276    "-276, \"Macro recursion error\""
#define _sERR_277    "-277, \"Macro redefinition not allowed\""
#define _sERR_278    "-278, \"Macro header not found\""
#define _sERR_280    "-280, \"Program error\""
#define _sERR_281    "-281, \"Cannot create program\""
#define _sERR_282    "-282, \"Illegal program name\""
#define _sERR_283    "-283, \"Illegal variable name\""
#define _sERR_284    "-284, \"Program currently running\""
#define _sERR_285    "-285, \"Program syntax error\""
#define _sERR_286    "-286, \"Program runtime error\""
#define _sERR_290    "-290, \"Memory use error\""
#define _sERR_291    "-291, \"Out of memory\""
#define _sERR_292    "-292, \"Referenced name does not exist\""
#define _sERR_293    "-293, \"Referenced name already exists\""
#define _sERR_294    "-294, \"Incompatible type\""



//-------------------------------------
//--- Device specific errors ---
// The device dependant error bit in the standard Event Status Register (ESR) is set to ．1' when such an error occurs.
#define _sERR_300    "-300, \"Device-specific error\""
#define _sERR_310    "-310, \"System error\""
#define _sERR_311    "-311, \"Memory error\""
#define _sERR_312    "-312, \"PUD memory lost\""
#define _sERR_313    "-313, \"Calibration memory lost\""
#define _sERR_314    "-314, \"Save/recall memory lost\""
#define _sERR_315    "-315, \"Configuration memory lost\""
#define _sERR_320    "-320, \"Storage fault\""
#define _sERR_321    "-321, \"Out of memory\""
#define _sERR_330    "-330, \"Self-test failed\""
#define _sERR_340    "-340, \"Calibration failed\""
#define _sERR_350    "-350, \"Queue overflow\""
#define _sERR_360    "-360, \"Communication error\""
#define _sERR_361    "-361, \"Parity error in program message\""
#define _sERR_362    "-362, \"Framing error in program message\""
#define _sERR_363    "-363, \"Input buffer overrun\""
#define _sERR_365    "-365, \"Time out error\""



//-------------------------------------
//--- Query errors ---
// The query error bit in the standard Event Status Register (ESR) is set to ．1' when such an error occurs.
#define _sERR_400    "-400, \"Query error\""
#define _sERR_410    "-410, \"Query INTERRUPTED\""
#define _sERR_420    "-420, \"Query UNTERMINATED\""
#define _sERR_430    "-430, \"Query DEADLOCKED\""
#define _sERR_440    "-440, \"Query UNTERMINATED after indefinite response\""

//-------------------------------------
//--- Other SCPI defined error values ---
// The corresponding bit in the standard Event Status Register (ESR) is set to ．1' when such an event occurs.
#define _sERR_500    "-500, \"Power on\""
#define _sERR_600    "-600, \"User request\""
#define _sERR_700    "-700, \"Request control\""
#define _sERR_800    "-800, \"Operation complete\""

//=========================================================
//=== GW Define Error String ===


//=============================================================================
//  typedef & struct
//=============================================================================

//=============================================================================
//  variable & constant
//=============================================================================
const char *Error[]={
	_sERR_000,
	_sERR_100,
	_sERR_101,
	_sERR_102,
	_sERR_103,
	_sERR_104,
	_sERR_105,
	_sERR_108,
	_sERR_109,
	_sERR_110,
	_sERR_111,
	_sERR_112,
	_sERR_113,
	_sERR_114,
	_sERR_115,
	_sERR_120,
	_sERR_121,
	_sERR_123,
	_sERR_124,
	_sERR_128,
	_sERR_130,
	_sERR_131,
	_sERR_134,
	_sERR_138,
	_sERR_140,
	_sERR_141,
	_sERR_144,
	_sERR_148,
	_sERR_150,
	_sERR_151,
	_sERR_158,
	_sERR_160,
	_sERR_161,
	_sERR_168,
	_sERR_170,
	_sERR_171,
	_sERR_178,
	_sERR_180,
	_sERR_181,
	_sERR_183,
	_sERR_184,
	_sERR_200,
	_sERR_201,
	_sERR_202,
	_sERR_203,
	_sERR_210,
	_sERR_211,
	_sERR_212,
	_sERR_213,
	_sERR_214,
	_sERR_215,
	_sERR_220,
	_sERR_221,
	_sERR_222,
	_sERR_223,
	_sERR_224,
	_sERR_225,
	_sERR_226,
	_sERR_230,
	_sERR_231,
	_sERR_232,
	_sERR_233,
	_sERR_240,
	_sERR_241,
	_sERR_250,
	_sERR_251,
	_sERR_252,
	_sERR_253,
	_sERR_254,
	_sERR_255,
	_sERR_256,
	_sERR_257,
	_sERR_258,
	_sERR_260,
	_sERR_261,
	_sERR_270,
	_sERR_271,
	_sERR_272,
	_sERR_273,
	_sERR_274,
	_sERR_275,
	_sERR_276,
	_sERR_277,
	_sERR_278,
	_sERR_280,
	_sERR_281,
	_sERR_282,
	_sERR_283,
	_sERR_284,
	_sERR_285,
	_sERR_286,
	_sERR_290,
	_sERR_291,
	_sERR_292,
	_sERR_293,
	_sERR_294,
	_sERR_300,
	_sERR_310,
	_sERR_311,
	_sERR_312,
	_sERR_313,
	_sERR_314,
	_sERR_315,
	_sERR_320,
	_sERR_321,
	_sERR_330,
	_sERR_340,
	_sERR_350,
	_sERR_360,
	_sERR_361,
	_sERR_362,
	_sERR_363,
	_sERR_400,
	_sERR_410,
	_sERR_420,
	_sERR_430,
	_sERR_440,
	_sERR_500,
	_sERR_600,
	_sERR_700,
	_sERR_800,
};

