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

/**
 * HAL Code Generator settings:
 * 	on tab TMS570LS3137ZWT
 * 		on tab Driver Enable
 * 			check Enable EMIF driver
 * 			check Enable SCI2 driver
 * 		on tab R4-MPU-PMU
 * 			check enable Region 6 Configuration
 * 			uncheck all Disable Sub-Region
 * 			set base 0x80000000
 * 			set size: 8_MB
 * 			set type: STRONGLYORDERED_SHARABLE
 * 			set permission: PRIV_RW_USER_RW_EXEC
 * 	on tab PINMUX
 * 		check EMIF
 * 		check Gate off EMIF_CLK output
 * 	on tab EMIF
 * 		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * 		!!!!! APPLY ONLY FOR ISSI IS 442S16400F SDRAM CHIP !!!!!
 * 		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * 		on tab EMIF General
 * 			check Enable EMIF SDRAM
 * 		on tab EMIF SDRAM
 * 			t(rc or trfc): 63ns
 * 			t(rp): 20ns
 * 			t(rcd): 20ns
 * 			t(wr) or t(rdl): 11ns
 * 			t(ras): 42ns
 * 			t(rc): 63ns
 * 			t(rrd): 14ns
 * 			t(xsr): 70ns
 * 			Refresh Period 64ns
 * 			Refresh Cycles: 4096
 * 			CAS Latency: 3
 * 			Banks: 4
 * 			Page size 256
 */

/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "emif.h"
#include "sci.h"
#include "stdio.h"

#define UART scilinREG
#define SDRAM_BASE_ADDRESS 0x80000000
#define SDRAM_END_ADDREESS 0x807FFFFF
#define MAX_BUFFER_LEN 512
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
int32_t sci_printf(const char* format, ...);
int32_t sci_vprintf(const char* format, va_list argList);
/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */
	emif_SDRAMInit();
	sciInit();
	volatile int* sdram__base_ptr = (volatile int *)SDRAM_BASE_ADDRESS;
	int value = 0xAAAAFFFF;
	sci_printf("Writing:\r\n");

	while (sdram__base_ptr < (volatile int*)SDRAM_END_ADDREESS) {
		sci_printf("\tWriting 0x%X on address 0x%X \r\n", value, sdram__base_ptr);
		*sdram__base_ptr = value;
		sdram__base_ptr+=100000;
		value++;
	}
	sci_printf("Reading:\r\n");
	sdram__base_ptr = (volatile int *)SDRAM_BASE_ADDRESS;
	while (sdram__base_ptr < (volatile int*)SDRAM_END_ADDREESS) {
		value = *sdram__base_ptr;
		sci_printf("\tReading 0x%X on address 0x%X \r\n", value, sdram__base_ptr);
		sdram__base_ptr+=100000;
	}
	sci_printf("Done.\r\n");
	wait_forever();
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

int32_t sci_printf(const char* format, ...)
{
	int length = -1;
    va_list argList;
    va_start(argList, format);
    length = sci_vprintf(format, argList);
    va_end(argList);

    return length;
}

int32_t sci_vprintf(const char* format, va_list argList)
{
    char str[MAX_BUFFER_LEN];
    int length = -1;

    length = vsnprintf(str, sizeof(str), format, argList);

    if(length > 0) {
        // According to the C stdlib about vsnprintf:
        // If the resulting string would be longer than n-1 characters, the
        // remaining characters are discarded and not stored, but counted
        // for the value returned by the function.
        // In consequence we need to trim the value if larger than buffer.
        if(length > sizeof(str)) {
            length = sizeof(str);
        }
        sciDisplayText(UART, (uint8_t*)str, length);
    }

    return length;
}

void inline wait_forever() {
	while (1) ;
}
/* USER CODE END */
