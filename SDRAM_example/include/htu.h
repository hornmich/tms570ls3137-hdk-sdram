/** @file htu.h
*   @brief HTU Driver Definition File
*   @date 20.May.2014
*   @version 04.00.00
*   
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */


#ifndef __HTU_H__
#define __HTU_H__

#include "reg_htu.h"

#ifdef __cplusplus
extern "C" {
#endif

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* HTU General Definitions */

#define HTU1PARLOC		(*(volatile uint32 *)0xFF4E0200U)
#define HTU2PARLOC		(*(volatile uint32 *)0xFF4C0200U)

#define HTU1RAMLOC		(*(volatile uint32 *)0xFF4E0000U)
#define HTU2RAMLOC		(*(volatile uint32 *)0xFF4C0000U)

/* USER CODE BEGIN (1) */
/* USER CODE END */

#ifdef __cplusplus
}
#endif /*extern "C" */

#endif
