/*
 * custom.h
 *
 *  Created on: Apr 6, 2026
 *      Author: Debasish Das
 */

#ifndef INC_CUSTOM_H_
#define INC_CUSTOM_H_

#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "cmsis_os2.h"


#define MAX_QUEUE_SIZE 10

typedef struct someQueue
{
	uint8_t someData[MAX_QUEUE_SIZE];

	uint8_t head;
	uint8_t tail;
	uint8_t count;
}someQueue_t;


void initSomeQueue(someQueue_t *myQueue);
void enqueueData(someQueue_t *myQueue, uint8_t qData);
uint8_t dequeueData(someQueue_t *myQueue);



void ITM_TPIU_Init();
void SWO_Pin_Init(void);
void sendtoITM(char ch);
void ITM_sendStr(const char *str);
void ITM_sendStringwithTime(const char *str);


#endif /* INC_CUSTOM_H_ */
