/**
 *  \file   mdio.h
 *
 *  \brief  MDIO APIs and macros.
 *
 *   This file contains the driver API prototypes and macro definitions.
 */

/* (c) Texas Instruments 2009-2014, All rights reserved. */

#ifndef __MDIO_H__
#define __MDIO_H__

#include "sys_common.h"
#include "hw_mdio.h"

#ifdef __cplusplus
extern "C" {
#endif

/* MDIO input and output frequencies in Hz */
#define MDIO_FREQ_INPUT           32000000U
#define MDIO_FREQ_OUTPUT          1000000U
/*****************************************************************************/

/**
 *  @addtogroup EMACMDIO
 *  @{
 */
/*
** Prototypes for the APIs
*/
extern uint32 MDIOPhyAliveStatusGet(uint32 baseAddr);
extern uint32 MDIOPhyLinkStatusGet(uint32 baseAddr);
extern void MDIOInit(uint32 baseAddr, uint32 mdioInputFreq,
                     uint32 mdioOutputFreq);
extern boolean MDIOPhyRegRead(uint32 baseAddr, uint32 phyAddr,
                                   uint32 regNum, volatile uint16 * dataPtr);
extern void MDIOPhyRegWrite(uint32 baseAddr, uint32 phyAddr,
                            uint32 regNum, uint16 RegVal);
extern void MDIOEnable(uint32 baseAddr);
extern void MDIODisable(uint32 baseAddr);

#ifdef __cplusplus
}
#endif

/**@}*/
#endif /* __MDIO_H__ */
