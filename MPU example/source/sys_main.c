/** @file sys_main.c 
*   @brief Application main file
*   @date 20.May.2014
*   @version 04.00.00
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "system.h"
#include "sys_mpu.h"
#include "sci.h"
#include "stdio.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 length);
void inline wait_forever();

#define MPU_ERR_NUMBER_OF_REGIONS 0x00000001
#define MPU_ERR_REGION_SELECTION 0x00000002
#define MPU_ERR_REGION_BASE_ADDRESS 0x00000004
#define MPU_ERR_REGION_TYPE 0x00000008
#define MPU_ERR_REGION_PERMISSION 0x00000010
#define SDRAM_BASE_ADDRESS 0x80000000

#define UART scilinREG
/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */
	uint32 No_Of_MPU_Region = 0;
	uint32 error = 0;
	sciInit();

	/* Initialize memory protection unit.
	* Region configurations are selected using MPU Tab in HALCoGen.
	* MPU is enabled in mpuInit function if "Enable MPU" in GUI is selected */
	_mpuInit_();

	/* This function returns the number of implemented mpu regions. */
	No_Of_MPU_Region = _mpuGetNumberOfRegions_();

	/* Check that device supports 12 Region. */
	if(No_Of_MPU_Region != 12) {
		error |= MPU_ERR_NUMBER_OF_REGIONS;
	}
	/* Select MPU Region 1 */
	_mpuSetRegion_(mpuREGION6);

	/* Check whether MPU Region 6 is selected */
	if(_mpuGetRegion_() != mpuREGION6) {
		/* Region 6 was Not selected */
		error |= MPU_ERR_REGION_SELECTION;
	}
	/* Check the Base address configured for MPU Region 6 */
	else if(_mpuGetRegionBaseAddress_() != SDRAM_BASE_ADDRESS) {
		/*Region 6 Base address wrong */
		error |= MPU_ERR_REGION_BASE_ADDRESS;
	}
	/* Check the Type configured for MPU Region 6 */
	else if(_mpuGetRegionType_() != MPU_STRONGLYORDERED_SHAREABLE) {
		/*Region 6 Type configured wrong */
		error |= MPU_ERR_REGION_TYPE;
	}
	/* Check the Permission configured for MPU Region 6 */
	else if(_mpuGetRegionPermission_() != MPU_PRIV_RW_USER_RW_EXEC) {
		/*Region 6 Permission configured wrong */
		error |= MPU_ERR_REGION_PERMISSION;
	}
	else {
		/* Region 1 Configurations are checked,
		* Matches MPU configuration through HALCoGen GUI */
		asm("	nop");
	}

    if(error != 0)
    {
    	uint8_t buffer [50];
    	int n;
    	n=sprintf ((char*)buffer, "MPU check failed: 0x%X\r\n", error);
    	sciDisplayText(UART, buffer, n);
    	/* Test Failed */
    	wait_forever();
    }
    else
    {
    	uint8_t buffer [50];
    	int n;
    	n=sprintf ((char*)buffer, "MPU check passed.\r\n");
    	sciDisplayText(UART, buffer, n);
    	wait_forever();
    }

/* USER CODE END */
}


/* USER CODE BEGIN (4) */
void sciDisplayText(sciBASE_t *sci, uint8 *text,uint32 length)
{
    while(length--)
    {
        while ((UART->FLR & 0x4) == 4); /* wait until busy */
        sciSendByte(UART,*text++);      /* send out text   */
    };
}

void wait(uint32 time)
{
    time--;
}

void inline wait_forever() {
	while (1) ;
}

/* USER CODE END */
