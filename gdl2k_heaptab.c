/* MANAGED-BY-SYSTEM-BUILDER                                    */

/*
** User heap source file generated on Sep 06, 2007 at 10:19:38.
**
** Copyright (C) 2000-2007 Analog Devices Inc., All Rights Reserved.
**
** This file is generated automatically based upon the options selected
** in the LDF Wizard. Changes to the LDF configuration should be made by
** changing the appropriate options rather than editing this file.
**
** Configuration:-
**     crt_doj:                                .\Debug\gdl2k_basiccrt.doj
**     processor:                              ADSP-BF531
**     si_revision:                            0.3
**     using_cplusplus:                        true
**     mem_init:                               false
**     use_vdk:                                false
**     use_eh:                                 true
**     use_argv:                               false
**     running_from_internal_memory:           true
**     user_heap_src_file:                     D:\workdsp\gel2000\gdl2k_heaptab.c
**     libraries_use_stdlib:                   true
**     libraries_use_fileio_libs:              false
**     libraries_use_ieeefp_emulation_libs:    false
**     libraries_use_eh_enabled_libs:          false
**     system_heap:                            L1
**     system_heap_min_size:                   2K
**     system_stack:                           L1
**     system_stack_min_size:                  2K
**     use_sdram:                              true
**     use_sdram_size:                         16M
**     use_sdram_partitioned:                  default
**     num_user_heaps:                         1
**     user_heap0:                             L3
**     user_heap0_min_size:                    1024K
**     user_heap0_heap_name:                   MyHeap
**
*/

#ifdef _MISRA_RULES
#pragma diag(push)
#pragma diag(suppress:misra_rule_2_2)
#pragma diag(suppress:misra_rule_8_10)
#pragma diag(suppress:misra_rule_10_1_a)
#pragma diag(suppress:misra_rule_11_3)
#pragma diag(suppress:misra_rule_12_7)
#endif /* _MISRA_RULES */


extern "asm" int ldf_heap_space;
extern "asm" int ldf_heap_length;
extern "asm" int MyHeap_space;
extern "asm" int MyHeap_length;


struct heap_table_t
{
  void          *base;
  unsigned long  length;
  long int       userid;
};

#pragma file_attr("libData=HeapTable")
#pragma section("constdata")
struct heap_table_t heap_table[3] =
{


  { &ldf_heap_space, (int) &ldf_heap_length, 0 },
  { &MyHeap_space, (int) &MyHeap_length, 1 },


  { 0, 0, 0 }
};


#ifdef _MISRA_RULES
#pragma diag(pop)
#endif /* _MISRA_RULES */

