#ifndef __SCPI_ERROR_H__
#define __SCPI_ERROR_H__
//------------------------------------------------------------------------------
#define _SCPI_ERROR_SELECT	1


extern const char *Error[];
/******************************************************************************
 *   This file is used to define the error code for GPIB/RS232 CARD.          *
 *   All the string's length can't longer than 80.                            *
 *****************************************************************************/

//=============================================================================
//=== 1999 SCPI Command Reference ===
enum _SCPI_ERROR {
	//----------------------------------------
	//--- SCPI Define Error Code ---
	 _ERR_000_No_Error = 0
	,_ERR_100_Command_error
	,_ERR_101_Invalid_character
	,_ERR_102_Syntax_error
	,_ERR_103_Invalid_separator
	,_ERR_104_Data_type_error
	,_ERR_105_GET_not_allowed
	,_ERR_108_Parameter_not_allowed
	,_ERR_109_Missing_parameter
	,_ERR_110_Command_header_error
	,_ERR_111_Header_separator_error
	,_ERR_112_Program_mnemonic_too_long
	,_ERR_113_Undefined_header
	,_ERR_114_Header_suffix_out_of_range
	,_ERR_115_Unexpected_number_of_parameters
	,_ERR_120_Numeric_data_error
	,_ERR_121_Invalid_character_in_number
	,_ERR_123_Exponent_too_large
	,_ERR_124_Too_many_digits
	,_ERR_128_Numeric_data_not_allowed
	,_ERR_130_Suffix_error
	,_ERR_131_Invalid_suffix
	,_ERR_134_Suffix_too_long
	,_ERR_138_Suffix_not_allowed
	,_ERR_140_Character_data_error
	,_ERR_141_Invalid_character_data
	,_ERR_144_Character_data_too_long
	,_ERR_148_Character_data_not_allowed
	,_ERR_150_String_data_error
	,_ERR_151_Invalid_string_data
	,_ERR_158_String_data_not_allowed
	,_ERR_160_Block_data_error
	,_ERR_161_Invalid_block_data
	,_ERR_168_Block_data_not_allowed
	,_ERR_170_Expression_error
	,_ERR_171_Invalid_expression
	,_ERR_178_Expression_data_not_allowed
	,_ERR_180_Macro_error
	,_ERR_181_Invalid_outside_macro_definition
	,_ERR_183_Invalid_inside_macro_definition
	,_ERR_184_Macro_parameter_error
	,_ERR_200_Execution_error
	,_ERR_201_Invalid_while_in_local
	,_ERR_202_Settings_lost_due_to_rtl
	,_ERR_203_Command_protected
	,_ERR_210_Trigger_error
	,_ERR_211_Trigger_ignored
	,_ERR_212_Arm_ignored
	,_ERR_213_Init_ignored
	,_ERR_214_Trigger_deadlock
	,_ERR_215_Arm_deadlock
	,_ERR_220_Parameter_error
	,_ERR_221_Settings_conflict
	,_ERR_222_Data_out_of_range
	,_ERR_223_Too_much_data
	,_ERR_224_Illegal_parameter_value
	,_ERR_225_Out_of_memory
	,_ERR_226_Lists_not_same_length
	,_ERR_230_Data_corrupt_or_stale
	,_ERR_231_Data_questionable
	,_ERR_232_Invalid_format
	,_ERR_233_Invalid_version
	,_ERR_240_Hardware_error
	,_ERR_241_Hardware_missing
	,_ERR_250_Mass_storage_error
	,_ERR_251_Missing_mass_storage
	,_ERR_252_Missing_media
	,_ERR_253_Corrupt_media
	,_ERR_254_Media_full
	,_ERR_255_Directory_full
	,_ERR_256_File_name_not_found
	,_ERR_257_File_name_error
	,_ERR_258_Media_protected
	,_ERR_260_Expression_error
	,_ERR_261_Math_error_in_expression
	,_ERR_270_Macro_error
	,_ERR_271_Macro_syntax_error
	,_ERR_272_Macro_execution_error
	,_ERR_273_Illegal_macro_label
	,_ERR_274_Macro_parameter_error
	,_ERR_275_Macro_definition_too_long
	,_ERR_276_Macro_recursion_error
	,_ERR_277_Macro_redefinition_not_allowed
	,_ERR_278_Macro_header_not_found
	,_ERR_280_Program_error
	,_ERR_281_Cannot_create_program
	,_ERR_282_Illegal_program_name
	,_ERR_283_Illegal_variable_name
	,_ERR_284_Program_currently_running
	,_ERR_285_Program_syntax_error
	,_ERR_286_Program_runtime_error
	,_ERR_290_Memory_use_error
	,_ERR_291_Out_of_memory
	,_ERR_292_Referenced_name_does_not_exist
	,_ERR_293_Referenced_name_already_exists
	,_ERR_294_Incompatible_type
	,_ERR_300_Device_specific_error
	,_ERR_310_System_error
	,_ERR_311_Memory_error
	,_ERR_312_PUD_memory_lost
	,_ERR_313_Calibration_memory_lost
	,_ERR_314_Save_recall_memory_lost
	,_ERR_315_Configuration_memory_lost
	,_ERR_320_Storage_fault
	,_ERR_321_Out_of_memory
	,_ERR_330_Self_test_failed
	,_ERR_340_Calibration_failed
	,_ERR_350_Queue_overflow
	,_ERR_360_Communication_error
	,_ERR_361_Parity_error_in_program_message
	,_ERR_362_Framing_error_in_program_message
	,_ERR_363_Input_buffer_overrun
	,_ERR_365_Time_out_error
	,_ERR_400_Query_error
	,_ERR_410_Query_INTERRUPTED
	,_ERR_420_Query_UNTERMINATED
	,_ERR_430_Query_DEADLOCKED
	,_ERR_440_Query_UNTERMINATED_after_indefinite_response
	,_ERR_500_Power_on
	,_ERR_600_User_request
	,_ERR_700_Request_control
	,_ERR_800_Operation_complete
	//----------------------------------------
	//--- GW Define Error Code ---
};

#endif //__SCPI_ERROR_H__

