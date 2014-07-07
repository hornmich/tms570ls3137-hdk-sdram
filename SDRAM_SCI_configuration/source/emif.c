/** @file emif.c
*   @brief emif Driver Implementation File
*   @date 20.May.2014
*   @version 04.00.00
*
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

#include "emif.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */
/** @fn void emif_SDRAMInit(void)
*   @brief Initializes the emif Driver for SDRAM
*
*   This function initializes the emif driver for SDRAM (SDRAM initialization function).
*/

/* SourceId : EMIF_SourceId_001 */
/* DesignId : EMIF_DesignId_001 */
/* Requirements: HL_SR334 */
void emif_SDRAMInit(void)
{
/* USER CODE BEGIN (2) */
/* USER CODE END */

   uint32 buffer;

   emifREG->SDTIMR  = (uint32)((uint32)5U << 27U)|
                      (uint32)((uint32)1U << 24U)|
                      (uint32)((uint32)0U << 23U)|
                      (uint32)((uint32)1U << 20U)|
                      (uint32)((uint32)0U << 19U)|
                      (uint32)((uint32)1U << 16U)|
                      (uint32)((uint32)3U << 12U)|
                      (uint32)((uint32)5U << 8U)|
                      (uint32)((uint32)0U << 7U)|
                      (uint32)((uint32)1U << 4U)|
                      (uint32)((uint32)0U << 3U);

 /* configure refresh rate*/
   emifREG->SDSRETR = (uint32)5U;  
   emifREG->SDRCR   = 2000U;	

/**  -general clearing of register
*    -for NM for setting 16 bit data bus
*    -cas latency
*    -BIT11_9CLOCK to allow the cl field to be written
*    -selecting the banks
*    -setting the pagesize
*/   
    emifREG->SDCR   = (uint32)((uint32)0U << 31U)|                               	
                      (uint32)((uint32)1U << 14U)|                               	
                      (uint32)((uint32)2U << 9U)|  	
                      (uint32)((uint32)1U << 8U)|                                	
                      (uint32)((uint32)2U << 4U)|              	
                      (uint32)((uint32)elements_256);         	
/* wait for a read to happen*/
   buffer           = *PTR;                                	
   buffer           = buffer;
   emifREG->SDRCR   = 31U;	

/* USER CODE BEGIN (3) */
   emifREG->SDRCR   = 312U;	
/* USER CODE END */
}





/* USER CODE BEGIN (10) */
/* USER CODE END */

/** @fn void emifGetConfigValue(emif_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the EMIF configuration registers
*
*	@param[in] *config_reg: pointer to the struct to which the initial or current 
*                           value of the configuration registers need to be stored
*	@param[in] type: 	whether initial or current value of the configuration registers need to be stored
*						- InitialValue: initial value of the configuration registers will be stored 
*                                       in the struct pointed by config_reg
*						- CurrentValue: initial value of the configuration registers will be stored 
*                                       in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type') 
*   of the configuration registers to the struct pointed by config_reg
*
*/
/* SourceId : EMIF_SourceId_005 */
/* DesignId : EMIF_DesignId_003 */
/* Requirements: HL_SR336 */
void emifGetConfigValue(emif_config_reg_t *config_reg, config_value_type_t type)
{
	if (type == InitialValue)
	{
		config_reg->CONFIG_AWCC    = EMIF_AWCC_CONFIGVALUE;  
		config_reg->CONFIG_SDCR    = EMIF_SDCR_CONFIGVALUE;  
		config_reg->CONFIG_SDRCR   = EMIF_SDRCR_CONFIGVALUE;
		config_reg->CONFIG_CE2CFG  = EMIF_CE2CFG_CONFIGVALUE;
		config_reg->CONFIG_CE3CFG  = EMIF_CE3CFG_CONFIGVALUE;
		config_reg->CONFIG_CE4CFG  = EMIF_CE4CFG_CONFIGVALUE;
		config_reg->CONFIG_CE5CFG  = EMIF_CE5CFG_CONFIGVALUE;
		config_reg->CONFIG_SDTIMR  = EMIF_SDTIMR_CONFIGVALUE;
		config_reg->CONFIG_SDSRETR = EMIF_SDSRETR_CONFIGVALUE;
		config_reg->CONFIG_INTRAW  = EMIF_INTRAW_CONFIGVALUE;
		config_reg->CONFIG_INTMSK  = EMIF_INTMSK_CONFIGVALUE;
		config_reg->CONFIG_PMCR    = EMIF_PMCR_CONFIGVALUE;
	}
	else
	{
	/*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "LDRA Tool issue" */
		config_reg->CONFIG_AWCC     = emifREG->AWCC;  
		config_reg->CONFIG_SDCR     = emifREG->SDCR;  
		config_reg->CONFIG_SDRCR    = emifREG->SDRCR ;
		config_reg->CONFIG_CE2CFG   = emifREG->CE2CFG;
		config_reg->CONFIG_CE3CFG   = emifREG->CE3CFG;
		config_reg->CONFIG_CE4CFG   = emifREG->CE4CFG;
		config_reg->CONFIG_CE5CFG   = emifREG->CE5CFG;
		config_reg->CONFIG_SDTIMR   = emifREG->SDTIMR;
		config_reg->CONFIG_SDSRETR  = emifREG->SDSRETR;
		config_reg->CONFIG_INTRAW   = emifREG->INTRAW;
		config_reg->CONFIG_INTMSK   = emifREG->INTMSK;
		config_reg->CONFIG_PMCR     = emifREG->PMCR;
	}
}


