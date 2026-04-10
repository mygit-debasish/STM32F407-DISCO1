/*
 * custom.c
 *
 *  Created on: Apr 6, 2026
 *      Author: Debasish Das
 */

#include "custom.h"
#include "stm32f4xx_hal.h"
#include "string.h"
#include "stdio.h"
#include "cmsis_os.h"

void SWO_Pin_Init(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF0_TRACE;

	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void ITM_TPIU_Init()
{
	/* Enable Trace */
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

	/* Unlock ITM */
	ITM->LAR = 0xC5ACCE55;

	/* Enable ITM stimulus port 0 */
	ITM->TER |= (1UL << 0);

	/* Enable ITM */
	ITM->TCR = ITM_TCR_ITMENA_Msk |
	ITM_TCR_SYNCENA_Msk |
	ITM_TCR_TSENA_Msk;
}

void sendtoITM(char ch)
{
	ITM_SendChar(ch);
	ITM_SendChar('\n');

}

void ITM_sendStr(const char *str)
{
	while (*str)
	{
		ITM_SendChar(*(str++));
	}
}


void ITM_sendStringwithTime(const char *str)
{
	static uint16_t SeqCounter = 0 ;


	char msgBuff[80];

	snprintf(msgBuff, sizeof(msgBuff), "[%d] %s \n", SeqCounter++, str);
	ITM_sendStr(msgBuff);
}

void initSomeQueue(someQueue_t *myQueue)
{

	myQueue->head = 0;
	myQueue->tail = 0;
	myQueue->count = 0;

	memset(&myQueue->someData[0], 0, MAX_QUEUE_SIZE);
}

void enqueueData(someQueue_t *myQueue, uint8_t qData)
{
	if(myQueue->count == MAX_QUEUE_SIZE )
	{
		return;
	}

	myQueue->someData[(myQueue->tail)] = qData;
	myQueue->tail = (myQueue->tail +1 ) % MAX_QUEUE_SIZE;
	myQueue->count++;
}

uint8_t dequeueData(someQueue_t *myQueue)
{
	uint8_t ret;

	if(myQueue->count == 0 )
		{
			return 10;
		}


	ret = myQueue->someData[(myQueue->head) % MAX_QUEUE_SIZE ];
	myQueue->head = (myQueue->head +1) % MAX_QUEUE_SIZE;
	myQueue->count--;

	return ret;
}




