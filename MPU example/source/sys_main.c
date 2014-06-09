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
void wait(uint32 time);

#define UART scilinREG
#define  TSIZE1 9
uint8  TEXT1[TSIZE1]= {'R','u','n','i','n','g','.','.','.'};
/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */
    uint32 No_Of_MPU_Region = 0;
    uint32 error = 0;
    sciInit();
    sciDisplayText(UART,&TEXT1[0],TSIZE1);   /* send text code 1 */

    /* Initialize memory protection unit.
     * Region configurations are selected using MPU Tab in HALCoGen.
     * MPU is enabled in mpuInit function if "Enable MPU" in GUI is selected */
    _mpuInit_();

    /* This function disables memory protection unit.
     * Added just to show how to disable MPU */
    _mpuDisable_();

    /* This function Enables memory protection unit.
     * Added just to show how to enable MPU, mpuInit function
     * will enable MPU if "Enable MPU" in GUI selected */
    _mpuEnable_();

    /* This function returns the number of implemented mpu regions. */
    No_Of_MPU_Region = _mpuGetNumberOfRegions_();

	   /* Check that device supports 12 Region. */
	   if(No_Of_MPU_Region != 12)
	   {
	      /* Check the device */
       asm("	nop");
       error |= 0x00000001;
	   }
    /* Select MPU Region 1 */
    _mpuSetRegion_(mpuREGION1);

    /* Check whether MPU Region 1 is selected */
    if(_mpuGetRegion_() != mpuREGION1)
    {
       /*Region 1 was Not selected */
       asm("	nop");
       error |= 0x00000002;
    }
    /* Check the Base address configured for MPU Region 1 */
    else if(_mpuGetRegionBaseAddress_() != 0x00000000)
    {
       /*Region 1 Base address wrong */
       asm("	nop");
       error |= 0x00000004;
    }
    /* Check the Type configured for MPU Region 1 */
    else if(_mpuGetRegionType_() != MPU_NORMAL_OINC_NONSHARED)
    {
       /*Region 1 Type configured wrong */
       asm("	nop");
       error |= 0x00000008;
    }
    /* Check the Permission configured for MPU Region 1 */
    else if(_mpuGetRegionPermission_() != MPU_PRIV_NA_USER_NA_NOEXEC)
    {
       /*Region 1 Permission configured wrong */
       asm("	nop");
       error |= 0x00000010;
    }
    else
    {
       /* Region 1 Configurations are checked,
        * Matches MPU configuration through HALCoGen GUI */
       asm("	nop");
    }

    /* This function disables memory protection unit.
     * Added just to show how to disable MPU */
    _mpuDisable_();

    if(error != 0)
    {
      /* Test Failed */
      asm("	nop");
    }
    else
    {
      /* Test Passed */
      asm("	nop");
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

/* USER CODE END */
