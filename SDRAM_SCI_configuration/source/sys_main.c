/** @file sys_main.c 
*   @brief Application main file
*   @date 28.Aug.2015
*   @version 04.05.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2015 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "emif.h"
#include "sci.h"
#include "stdio.h"
#include "string.h"

#define UART sciREG
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
int memtest(int start_addr, int end_addr, int addr_inc);
int run_mentest();
/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */
	_mpuInit_();
	emif_SDRAMInit();
	sciInit();
	sci_printf("\r\n----\r\n");
	run_mentest();
	sci_printf("\r\nBoard is ready...\r\n");
	wait_forever();
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
int run_mentest() {
	sci_printf("Running memory test...");
	int err_cnt = memtest(SDRAM_BASE_ADDRESS, SDRAM_END_ADDREESS, 1);
	if (err_cnt > 0) {
		sci_printf("failed:  %d errors\r\n", err_cnt);
		return 1;
	}
	else {
		sci_printf("passed\r\n");
		return 0;
	}
}

void sciDisplayText(sciBASE_t *sci, uint8 *text,uint32 length)
{
    while(length--)
    {
        while ((UART->FLR & 0x4) == 4); /* wait until busy */
        sciSendByte(sci,*text++);      /* send out text   */
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
    char str1[MAX_BUFFER_LEN];
    char str2[MAX_BUFFER_LEN];
    int length1 = -1;

    length1 = vsnprintf(str1, sizeof(str1), format, argList);
    strcpy(str2, str1);
    int length2 = length1;

    if(length1 > 0) {
        // According to the C stdlib about vsnprintf:
        // If the resulting string would be longer than n-1 characters, the
        // remaining characters are discarded and not stored, but counted
        // for the value returned by the function.
        // In consequence we need to trim the value if larger than buffer.
        if(length1 > sizeof(str1)) {
            length1 = sizeof(str1);
            length2 = length1;
        }
        sciDisplayText(UART, (uint8_t*)str1, length1);
        sciDisplayText(scilinREG, (uint8_t*)str2, length2);
    }
    return length1;
}

void inline wait_forever() {
	while (1) ;
}

int memtest(int start_addr, int end_addr, int addr_inc) {
	const uint32_t PATTERN = 0x55555555U;
	const uint32_t INCREMEMNT = 0x55555555U;
	volatile uint32_t* addrPtr = (uint32_t*)start_addr;
	volatile uint32_t* endAddr = (uint32_t*)end_addr;
	uint32_t pattern = PATTERN;
	uint32_t cnt = 0;
	uint32_t errCnt = 0;
	uint32_t readVal = 0;

	while (addrPtr <= endAddr) {
			//sci_printf("writting 0x%x to address 0x%x\r\n", pattern, addrPtr);
			*addrPtr = pattern;
			pattern += INCREMEMNT;
			addrPtr+=addr_inc;
	}

	pattern = PATTERN;
	while (addrPtr <= endAddr) {
		readVal = *addrPtr;
		//sci_printf("reading 0x%x from address 0x%x - ", readVal, addrPtr);
		if (pattern == readVal){
			cnt++;
			//sci_printf("ok\r\n");
		}
		else {
			//sci_printf("failed\r\n");
			errCnt++;
		}
		pattern += INCREMEMNT;
		addrPtr+=addr_inc;
	}
	return errCnt;
}

/* USER CODE END */
