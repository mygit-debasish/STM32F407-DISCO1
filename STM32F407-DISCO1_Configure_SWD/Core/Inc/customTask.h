/*
 * customTask.h
 *
 *  Created on: Apr 6, 2026
 *      Author: Debasish Das
 */

#ifndef INC_CUSTOMTASK_H_
#define INC_CUSTOMTASK_H_

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os2.h"
#include "stm32f4xx.h"


void StartDebugTask(void *argument);
void StartAcquireTask(void *argument);
void StartAcquireTask2(void *argument);

void ITM_Get_TasknamePriority(osThreadAttr_t *OsThreadAttr);
void ITM_Get_TasknamePriorityTaskHandle(osThreadId_t OsTaskHandle);
void ITM_Get_TasknamePriorityData(osThreadId_t OsTaskHandle, void *pData);

/*Debug private function */
void DWT_Int();



#endif /* INC_CUSTOMTASK_H_ */
