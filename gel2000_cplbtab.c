/* MANAGED-BY-SYSTEM-BUILDER                                    */

/*
** CPLB table definitions generated on Mar 31, 2008 at 14:30:55.
**
** Copyright (C) 2000-2007 Analog Devices Inc., All Rights Reserved.
**
** This file is generated automatically based upon the options selected
** in the LDF Wizard. Changes to the LDF configuration should be made by
** changing the appropriate options rather than editing this file.
**
** Configuration:-
**     crt_doj:                                .\Release\gel2000_basiccrt.doj
**     processor:                              ADSP-BF531
**     si_revision:                            0.3
**     cplb_init_cplb_ctrl:                    81
**     cplb_init_cplb_src_file:                D:\workdsp\gel2000\gel2000_cplbtab.c
**     cplb_init_cplb_obj_file:                .\Release\gel2000_cplbtab.doj
**     using_cplusplus:                        true
**     mem_init:                               false
**     use_vdk:                                false
**     use_eh:                                 true
**     use_argv:                               false
**     running_from_internal_memory:           true
**     user_heap_src_file:                     D:\workdsp\gel2000\gel2000_heaptab.c
**     libraries_use_stdlib:                   true
**     libraries_use_fileio_libs:              false
**     libraries_use_ieeefp_emulation_libs:    false
**     libraries_use_eh_enabled_libs:          false
**     system_heap:                            L3
**     system_heap_size:                       8704K
**     system_stack:                           L3
**     system_stack_size:                      448K
**     use_sdram:                              true
**     use_sdram_size:                         16M
**     use_sdram_partitioned:                  none
**
*/

#ifdef _MISRA_RULES
#pragma diag(push)
#pragma diag(suppress:misra_rule_2_2)
#pragma diag(suppress:misra_rule_8_10)
#pragma diag(suppress:misra_rule_10_1_a)
#endif /* _MISRA_RULES */


#define CACHE_MEM_MODE CPLB_DNOCACHE



#include <sys/platform.h>
#include <cplbtab.h>

#pragma section("cplb_data")

cplb_entry dcplbs_table[] = {



/*$VDSG<customisable-data-cplb-table>                           */
/* This code is preserved if the CPLB tables are re-generated.  */


   // L1 Data A & B, (set write-through bit to avoid 1st write exceptions)
   {0xFF800000, (PAGE_SIZE_4MB | CPLB_DNOCACHE | CPLB_LOCK | CPLB_WT)}, 

   // Async Memory Bank 2 (Second)
   // Async Memory Bank 1 (Prim B)
   // Async Memory Bank 0 (Prim A)
   {0x20200000, (PAGE_SIZE_1MB | CPLB_DNOCACHE)}, 
   {0x20100000, (PAGE_SIZE_1MB | CACHE_MEM_MODE)}, 
   {0x20000000, (PAGE_SIZE_1MB | CACHE_MEM_MODE)}, 

   // 128 MB (Maximum) SDRAM memory space (32/64 MB populated on Ez-kit)
   {0x00000000, (PAGE_SIZE_4MB | CACHE_MEM_MODE | CPLB_DIRTY | CPLB_LOCK)}, 
   {0x00400000, (PAGE_SIZE_4MB | CACHE_MEM_MODE | CPLB_DIRTY | CPLB_LOCK)}, 
   
   // CPLBs covering 8MB
   {0x00800000, (PAGE_SIZE_1MB | CACHE_MEM_MODE)},
   {0x00900000, (PAGE_SIZE_1MB | CACHE_MEM_MODE)},
   {0x00a00000, (PAGE_SIZE_1MB | CACHE_MEM_MODE)},
   {0x00b00000, (PAGE_SIZE_1MB | CACHE_MEM_MODE)},
   {0x00c00000, (PAGE_SIZE_1MB | CACHE_MEM_MODE)},
   {0x00d00000, (PAGE_SIZE_1MB | CACHE_MEM_MODE)},
   {0x00e00000, (PAGE_SIZE_1MB | CACHE_MEM_MODE)},
   {0x00f00000, (PAGE_SIZE_1MB | CACHE_MEM_MODE)},

   // Async Memory Bank 3
   {0x20300000, (PAGE_SIZE_1MB | CPLB_DNOCACHE)}, 

   // end of section - termination
   {0xffffffff, 0}, 
/*$VDSG<customisable-data-cplb-table>                           */


}; /* dcplbs_table */

cplb_entry icplbs_table[] = {



/*$VDSG<customisable-instr-cplb-table>                          */
/* This code is preserved if the CPLB tables are re-generated.  */


   // L1 Code
   {0xFFA00000, (PAGE_SIZE_1MB | CPLB_I_PAGE_MGMT)}, 

   // Async Memory Bank 2 (Secnd)
   // Async Memory Bank 1 (Prim B)
   // Async Memory Bank 0 (Prim A)
   {0x20200000, (PAGE_SIZE_1MB | CPLB_INOCACHE)}, 
   {0x20100000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)}, 
   {0x20000000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)}, 

   // 128 MB (Maximum) SDRAM memory space (32/64 MB populated on Ez-kit)
   
   // CPLBs covering 16MB
   {0x00000000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)},
   {0x00100000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)},
   {0x00200000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)},
   {0x00300000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)},
   {0x00400000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)},
   {0x00500000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)},
   {0x00600000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)},
   {0x00700000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)},
   {0x00800000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)},
   {0x00900000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)},
   {0x00a00000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)},
   {0x00b00000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)},
   {0x00c00000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)},
   {0x00d00000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)},
   {0x00e00000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)},
   {0x00f00000, (PAGE_SIZE_1MB | CPLB_IDOCACHE)},

   // Async Memory Bank 3 
   {0x20300000, (PAGE_SIZE_1MB | CPLB_INOCACHE)}, 

   // end of section - termination
   {0xffffffff, 0}, 
/*$VDSG<customisable-instr-cplb-table>                          */


}; /* icplbs_table */


#ifdef _MISRA_RULES
#pragma diag(pop)
#endif /* _MISRA_RULES */

