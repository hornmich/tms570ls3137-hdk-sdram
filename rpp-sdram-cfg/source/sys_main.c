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
#include "dmm.h"
#include "emif.h"
#include "can.h"
#include "sci.h"
#include "stdio.h"
#include "string.h"

#define UART sciREG
#define SDRAM_BASE_ADDRESS 0x80000000
#define SDRAM_END_ADDREESS 0x83FFFFFF
#define MAX_BUFFER_LEN 512
#define  D_SIZE 9

uint8  tx_data[D_SIZE]  = {'R','P','P',' ','C','A','N','\0'};

void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 length);
void inline wait_forever();
int32_t sci_printf(const char* format, ...);
int32_t sci_vprintf(const char* format, va_list argList);
int memtest(uint32_t start_addr, uint32_t end_addr, int addr_inc);
void can_wake_up();
void wait(int ms);
int run_mentest();
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */
	_mpuInit_();
	dmmInit();
	sciInit();
	sci_printf("\r\n\nRPP SDRAM configuration\r\n=======\r\n");
	emif_SDRAMInit();
	sci_printf("EMIF SDRAM configured.\r\n");
	canInit();
	can_wake_up();
	sci_printf("CAN initialized.\r\n");
	run_mentest();
	sci_printf("Endless loop...\r\n");

	while(1) {
		//sci_printf("CAN msg transmitted.\r\n");
		//canTransmit(canREG1, canMESSAGE_BOX1, tx_data);
		//wait(250);
		;
	}

	// We should never get here
	wait_forever();

/* USER CODE END */
}

/* USER CODE BEGIN (4) */
void can_wake_up() {
	dmmREG->PC4 = (1<<(13)); // set CAN_NSTB
	wait(50);
	dmmREG->PC5 = (1<<(15)); // clr CAN_EN
	wait(50);
	dmmREG->PC5 = (1<<(13)); // clr CAN_NSTB
	wait(50);
	dmmREG->PC4 = (1<<(13)); // set CAN_NSTB
	wait(50);
	dmmREG->PC4 = (1<<(15)); // set CAN_EN
	wait(50);
}

void wait(int ms) {
	volatile long i = 0;
	for (i = 0; i < ms*10000; i++) {
		;
	}
}

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
    int length1 = -1;

    length1 = vsnprintf(str1, sizeof(str1), format, argList);

    if(length1 > 0) {
        // According to the C stdlib about vsnprintf:
        // If the resulting string would be longer than n-1 characters, the
        // remaining characters are discarded and not stored, but counted
        // for the value returned by the function.
        // In consequence we need to trim the value if larger than buffer.
        if(length1 > sizeof(str1)) {
            length1 = sizeof(str1);
        }
        sciDisplayText(UART, (uint8_t*)str1, length1);
    }
    return length1;
}

void inline wait_forever() {
	while (1) ;
}

int memtest(uint32_t start_addr, uint32_t end_addr, int addr_inc) {
	const uint32_t PATTERN = 0x55555555U;
	const uint32_t INCREMEMNT = 0x0D170D17U;
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
			sci_printf("reading 0x%x from address 0x%x - failed", readVal, addrPtr);
			errCnt++;
		}
		pattern += INCREMEMNT;
		addrPtr+=addr_inc;
		// Too many error, SDRAM is not functional
		if (errCnt > 100) {
			sci_printf("Too many error, SDRAM not configured properly.\r\n");
			return errCnt;
		}
	}
	return errCnt;
}
/* USER CODE END */
