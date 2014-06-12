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

#include "sci.h"

#define  TSIZE1 10
uint8  TEXT1[TSIZE1]= {'H','E','R','C','U','L','E','S',' ',' '};
#define  TSIZE2 18
uint8  TEXT2[TSIZE2]= {'M','I','C','R','O','C','O','N','T','R','O','L','L','E','R','S',' ',' '};
#define  TSIZE3 19
uint8  TEXT3[TSIZE3]= {'T','E','X','A','S',' ','I','N','S','T','R','U','M','E','N','T','S','\n','\r'};

void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 length);
void wait(uint32 time);

#define UART1 sciREG // SCI1, connected to the external uart-rs203 usb converter
#define UART2 scilinREG // SCI2 connected to the FTDI
#define UART UART1
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
    sciInit();      /* initialize sci/sci-lin    */
    /* even parity , 2 stop bits */
    while(1)        /* continious desplay        */
    {
    	sciDisplayText(UART,&TEXT1[0],TSIZE1);   /* send text code 1 */
    	sciDisplayText(UART,&TEXT2[0],TSIZE2);   /* send text code 2 */
    	sciDisplayText(UART,&TEXT3[0],TSIZE3);   /* send text code 3 */
    	wait(200);
    };
	/* USER CODE END */
}

/* USER CODE BEGIN (4) */
void sciDisplayText(sciBASE_t *sci, uint8 *text,uint32 length){
	while(length--)
	{
		while ((UART->FLR & 0x4) == 4); /* wait until busy */
		sciSendByte(UART,*text++);      /* send out text   */
	};
}

void wait(uint32 time){
	time--;
}
/* USER CODE END */
