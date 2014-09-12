/** @file dmm.c 
*   @brief DMM Driver Implementation File
*   @date 20.May.2014
*   @version 04.00.00
*
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

#include "dmm.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @fn void dmmInit(void)
*   @brief Initializes the DMM Driver
*
*   This function initializes the DMM module.
*/
/* SourceId : DMM_SourceId_001 */
/* DesignId : DMM_DesignId_001 */
/* Requirements: HL_SR351 */
void dmmInit(void)
{

/* USER CODE BEGIN (2) */
/* USER CODE END */

    /** @b intalise @b DMM */

    /** @b initialize @b DMM @b Port */
    dmmREG->PC3 = (uint32)0U            /* DMM SYNC */
                | (uint32)((uint32)0U << 1U)     /* DMM CLK */
                | (uint32)((uint32)0U << 2U)     /* DATA[0] */
                | (uint32)((uint32)0U << 3U)     /* DATA[1] */
                | (uint32)((uint32)0U << 4U)     /* DATA[2] */
                | (uint32)((uint32)0U << 5U)     /* DATA[3] */
                | (uint32)((uint32)0U << 6U)     /* DATA[4] */
                | (uint32)((uint32)0U << 7U)     /* DATA[5] */
                | (uint32)((uint32)0U << 8U)     /* DATA[6] */
                | (uint32)((uint32)0U << 9U)     /* DATA[7] */
                | (uint32)((uint32)0U << 10U)   /* DATA[8] */
                | (uint32)((uint32)1U << 11U)   /* DATA[9] */
                | (uint32)((uint32)1U << 12U)   /* DATA[10] */
                | (uint32)((uint32)1U << 13U)   /* DATA[11] */
                | (uint32)((uint32)0U << 14U)   /* DATA[12] */
                | (uint32)((uint32)1U << 15U)   /* DATA[13] */
                | (uint32)((uint32)1U << 16U)   /* DATA[14] */
                | (uint32)((uint32)1U << 17U)   /* DATA[15] */
                | (uint32)((uint32)0U << 18U);  /* DMM ENA */

    /** - DMM Port direction */
    dmmREG->PC1 = (uint32) 1U             /* DMM SYNC */
                | (uint32)((uint32)1U << 1U)      /* DMM CLK */
                | (uint32)((uint32)1U << 2U)      /* DATA[0] */
                | (uint32)((uint32)1U << 3U)      /* DATA[1] */
                | (uint32)((uint32)0U << 4U)      /* DATA[2] */
                | (uint32)((uint32)1U << 5U)      /* DATA[3] */
                | (uint32)((uint32)1U << 6U)      /* DATA[4] */
                | (uint32)((uint32)0U << 7U)      /* DATA[5] */
                | (uint32)((uint32)0U << 8U)      /* DATA[6] */
                | (uint32)((uint32)1U << 9U)      /* DATA[7] */
                | (uint32)((uint32)1U << 10U)    /* DATA[8] */
                | (uint32)((uint32)0U << 11U)    /* DATA[9] */
                | (uint32)((uint32)0U << 12U)    /* DATA[10] */
                | (uint32)((uint32)1U << 13U)    /* DATA[11] */
                | (uint32)((uint32)1U << 14U)    /* DATA[12] */
                | (uint32)((uint32)1U << 15U)    /* DATA[13] */
                | (uint32)((uint32)0U << 16U)    /* DATA[14] */
                | (uint32)((uint32)1U << 17U)    /* DATA[15] */
                | (uint32)((uint32)1U << 18U);   /* DMM ENA */
                
    /** - DMM Port open drain enable */
    dmmREG->PC6 = (uint32) 0U             /* DMM SYNC */
                | (uint32)((uint32)0U << 1U)      /* DMM CLK */
                | (uint32)((uint32)0U << 2U)      /* DATA[0] */
                | (uint32)((uint32)1U << 3U)      /* DATA[1] */
                | (uint32)((uint32)1U << 4U)      /* DATA[2] */
                | (uint32)((uint32)1U << 5U)      /* DATA[3] */
                | (uint32)((uint32)1U << 6U)      /* DATA[4] */
                | (uint32)((uint32)0U << 7U)      /* DATA[5] */
                | (uint32)((uint32)0U << 8U)      /* DATA[6] */
                | (uint32)((uint32)0U << 9U)      /* DATA[7] */
                | (uint32)((uint32)0U << 10U)    /* DATA[8] */
                | (uint32)((uint32)0U << 11U)    /* DATA[9] */
                | (uint32)((uint32)0U << 12U)    /* DATA[10] */
                | (uint32)((uint32)0U << 13U)    /* DATA[11] */
                | (uint32)((uint32)1U << 14U)    /* DATA[12] */
                | (uint32)((uint32)0U << 15U)    /* DATA[13] */
                | (uint32)((uint32)0U << 16U)    /* DATA[14] */
                | (uint32)((uint32)0U << 17U)    /* DATA[15] */
                | (uint32)((uint32)0U << 18U);   /* DMM ENA */

    /** - DMM Port pullup / pulldown selection */
    dmmREG->PC8 = (uint32) 0U             /* DMM SYNC */
                | (uint32)((uint32)0U << 1U)      /* DMM CLK */
                | (uint32)((uint32)0U << 2U)      /* DATA[0] */
                | (uint32)((uint32)0U << 3U)      /* DATA[1] */
                | (uint32)((uint32)0U << 4U)      /* DATA[2] */
                | (uint32)((uint32)0U << 5U)      /* DATA[3] */
                | (uint32)((uint32)0U << 6U)      /* DATA[4] */
                | (uint32)((uint32)0U << 7U)      /* DATA[5] */
                | (uint32)((uint32)0U << 8U)      /* DATA[6] */
                | (uint32)((uint32)0U << 9U)      /* DATA[7] */
                | (uint32)((uint32)0U << 10U)    /* DATA[8] */
                | (uint32)((uint32)0U << 11U)    /* DATA[9] */
                | (uint32)((uint32)0U << 12U)    /* DATA[10] */
                | (uint32)((uint32)0U << 13U)    /* DATA[11] */
                | (uint32)((uint32)1U << 14U)    /* DATA[12] */
                | (uint32)((uint32)0U << 15U)    /* DATA[13] */
                | (uint32)((uint32)0U << 16U)    /* DATA[14] */
                | (uint32)((uint32)0U << 17U)    /* DATA[15] */
                | (uint32)((uint32)0U << 18U);   /* DMM ENA */

    /** - DMM Port pullup / pulldown enable*/
    dmmREG->PC7 = (uint32) 0U           /* DMM SYNC */
                | (uint32)((uint32)0U << 1U)    /* DMM CLK */
                | (uint32)((uint32)0U << 2U)    /* DATA[0] */
                | (uint32)((uint32)0U << 3U)    /* DATA[1] */
                | (uint32)((uint32)0U << 4U)    /* DATA[2] */
                | (uint32)((uint32)0U << 5U)    /* DATA[3] */
                | (uint32)((uint32)0U << 6U)    /* DATA[4] */
                | (uint32)((uint32)0U << 7U)    /* DATA[5] */
                | (uint32)((uint32)0U << 8U)    /* DATA[6] */
                | (uint32)((uint32)0U << 9U)    /* DATA[7] */
                | (uint32)((uint32)0U << 10U)  /* DATA[8] */
                | (uint32)((uint32)0U << 11U)  /* DATA[9] */
                | (uint32)((uint32)0U << 12U)  /* DATA[10] */
                | (uint32)((uint32)0U << 13U)  /* DATA[11] */
                | (uint32)((uint32)1U << 14U)  /* DATA[12] */
                | (uint32)((uint32)0U << 15U)  /* DATA[13] */
                | (uint32)((uint32)0U << 16U)  /* DATA[14] */
                | (uint32)((uint32)0U << 17U)  /* DATA[15] */
                | (uint32)((uint32)0U << 18U); /* DMM ENA */

    /* DMM set all pins to functional */
    dmmREG->PC0 = (uint32) 0U           /* DMM SYNC */
                | (uint32)((uint32)0U << 1U)    /* DMM CLK */
                | (uint32)((uint32)0U << 2U)    /* DATA[0] */
                | (uint32)((uint32)0U << 3U)    /* DATA[1] */
                | (uint32)((uint32)0U << 4U)    /* DATA[2] */
                | (uint32)((uint32)0U << 5U)    /* DATA[3] */
                | (uint32)((uint32)0U << 6U)    /* DATA[4] */
                | (uint32)((uint32)0U << 7U)    /* DATA[5] */
                | (uint32)((uint32)0U << 8U)    /* DATA[6] */
                | (uint32)((uint32)0U << 9U)    /* DATA[7] */
                | (uint32)((uint32)0U << 10U)  /* DATA[8] */  
                | (uint32)((uint32)0U << 11U)  /* DATA[9] */  
                | (uint32)((uint32)0U << 12U)  /* DATA[10] */  
                | (uint32)((uint32)0U << 13U)  /* DATA[11] */  
                | (uint32)((uint32)0U << 14U)  /* DATA[12] */  
                | (uint32)((uint32)0U << 15U)  /* DATA[13] */  
                | (uint32)((uint32)0U << 16U)  /* DATA[14] */  
                | (uint32)((uint32)0U << 17U)  /* DATA[15] */  
                | (uint32)((uint32)0U << 18U); /* DMM ENA */  

/* USER CODE BEGIN (3) */
/* USER CODE END */

}

/** @fn void dmmGetConfigValue(dmm_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the DMM configuration registers
*
*   @param[in] *config_reg: pointer to the struct to which the initial or current 
*                           value of the configuration registers need to be stored
*   @param[in] type:    whether initial or current value of the configuration registers need to be stored
*                       - InitialValue: initial value of the configuration registers will be stored 
*                                       in the struct pointed by config_reg
*                       - CurrentValue: initial value of the configuration registers will be stored 
*                                       in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type') 
*   of the configuration registers to the struct pointed by config_reg
*
*/
/* SourceId : DMM_SourceId_002 */
/* DesignId : DMM_DesignId_002 */
/* Requirements: HL_SR352 */
void dmmGetConfigValue(dmm_config_reg_t *config_reg, config_value_type_t type)
{
    if (type == InitialValue)
    {
        config_reg->CONFIG_PC0 = DMM_PC0_CONFIGVALUE;
        config_reg->CONFIG_PC1 = DMM_PC1_CONFIGVALUE;
        config_reg->CONFIG_PC3 = DMM_PC3_CONFIGVALUE;
        config_reg->CONFIG_PC6 = DMM_PC6_CONFIGVALUE;
        config_reg->CONFIG_PC7 = DMM_PC7_CONFIGVALUE;
        config_reg->CONFIG_PC8 = DMM_PC8_CONFIGVALUE;
    }
    else
    {
    /*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "LDRA Tool issue" */
        config_reg->CONFIG_PC0 = dmmREG->PC0;
        config_reg->CONFIG_PC1 = dmmREG->PC1;
        config_reg->CONFIG_PC3 = dmmREG->PC3;
        config_reg->CONFIG_PC6 = dmmREG->PC6;
        config_reg->CONFIG_PC7 = dmmREG->PC7; 
        config_reg->CONFIG_PC8 = dmmREG->PC8;
    }
}
