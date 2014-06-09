/** @file reg_pom.h
*   @brief POM Register Layer Header File
*   @date 20.May.2014
*   @version 04.00.00
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the POM driver.
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */

#ifndef __REG_POM_H__
#define __REG_POM_H__

#include "sys_common.h"



/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Pom Register Frame Definition */
/** @struct POMBase
*   @brief POM Register Frame Definition
*
*   This structure is used to access the POM module registers(POM Register Map).
*/
typedef struct
{
  uint32 POMGLBCTRL;   /* 0x00      */
  uint32 POMREV;       /* 0x04      */
  uint32 POMCLKCTRL;   /* 0x08      */
  uint32 POMFLG;       /* 0x0C      */
  struct
  {
    uint32   rsdv1;
  }RESERVED_REG[124U];
  struct                    /* 0x200 ...    */
  {
    uint32 POMPROGSTART; 
    uint32 POMOVLSTART; 
    uint32 POMREGSIZE; 
    uint32   rsdv2; 
  }POMRGNCONF_ST[32U];
}pomBASE_t;


/** @struct POM_CORESIGHT_ST
*   @brief POM_CORESIGHT_ST Register Definition
*
*   This structure is used to access the POM module registers(POM CoreSight Registers ).
*/
typedef struct
{
    uint32 POMITCTRL;                  /* 0xF00            */
    struct                                  /* 0xF04 to 0xF9C   */                     
    {
        uint32 Reserved_Reg;
    }Reserved1_ST[39U];
    uint32 POMCLAIMSET;                /* 0xFA0      */
    uint32 POMCLAIMCLR;                /* 0xFA4      */
    uint32   rsvd1[2U];                    /* 0xFA8      */
    uint32 POMLOCKACCESS;              /* 0xFB0      */
    uint32 POMLOCKSTATUS;              /* 0xFB4      */
    uint32 POMAUTHSTATUS;              /* 0xFB8      */
    uint32   rsvd2[3U];                    /* 0xFBC      */
    uint32 POMDEVID;                   /* 0xFC8      */
    uint32 POMDEVTYPE;                 /* 0xFCC      */
    uint32 POMPERIPHERALID4;           /* 0xFD0      */
    uint32 POMPERIPHERALID5;           /* 0xFD4      */
    uint32 POMPERIPHERALID6;           /* 0xFD8      */
    uint32 POMPERIPHERALID7;           /* 0xFDC      */
    uint32 POMPERIPHERALID0;           /* 0xFE0      */
    uint32 POMPERIPHERALID1;           /* 0xFE4      */
    uint32 POMPERIPHERALID2;           /* 0xFE8      */
    uint32 POMPERIPHERALID3;           /* 0xFEC      */            
    uint32 POMCOMPONENTID0;            /* 0xFF0      */
    uint32 POMCOMPONENTID1;            /* 0xFF4      */
    uint32 POMCOMPONENTID2;            /* 0xFF8      */
    uint32 POMCOMPONENTID3;            /* 0xFFC      */
}POM_CORESIGHT_ST;


#define pomREG ((pomBASE_t *)0xFFA04000U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
