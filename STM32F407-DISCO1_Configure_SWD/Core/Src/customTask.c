/*
 * customTask.c
 *
 *  Created on: Apr 6, 2026
 *      Author: debasish Das
 */

#include "customTask.h"
#include "custom.h"

extern osThreadAttr_t taskDubug_attribute;
extern osThreadAttr_t newAcquireTask_attributes;
extern osThreadAttr_t newAcquireTask2_attributes;

extern osThreadId_t debugTaskHandle;
extern osThreadId_t newAcquireTaskHandle;
extern osThreadId_t newAcquireTask2Handle;

extern osMutexId_t myMutexITMHandle;

/************* Task Definition starts ***********************/

void StartDebugTask(void *argument)
{
	for (;;)
	{
		/*Acquire the Mutex */
		osMutexAcquire(&myMutexITMHandle, 200);
		ITM_Get_TasknamePriorityTaskHandle(debugTaskHandle);
		osMutexRelease(&myMutexITMHandle);

		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

/**
 * @brief Function implementing the newAcquireTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartAcquireTask */
void StartAcquireTask(void *argument)
{
	for (;;)
	{
		/*Acquire the Mutex */
		osMutexAcquire(&myMutexITMHandle, 200);

		ITM_Get_TasknamePriorityTaskHandle(newAcquireTaskHandle);
		osMutexRelease(&myMutexITMHandle);

		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}


/* USER CODE BEGIN Header_StartAcquireTask2 */
/**
* @brief Function implementing the newAcquireTask2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAcquireTask2 */
void StartAcquireTask2(void *argument)
{
	for (;;)
	{
		/*Acquire the Mutex */
		osMutexAcquire(&myMutexITMHandle, 200);
		ITM_Get_TasknamePriorityTaskHandle(newAcquireTask2Handle);
		osMutexRelease(&myMutexITMHandle);

		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}


void ITM_Get_TasknamePriority(osThreadAttr_t *OsThreadAttr)
{
	char taskName[40];
	(void) snprintf(taskName, sizeof(taskName), "[%d]: [%s]",
			OsThreadAttr->priority, OsThreadAttr->name);

	ITM_sendStringwithTime(taskName);
}

void ITM_Get_TasknamePriorityTaskHandle(osThreadId_t OsTaskHandle)
{
	char taskName[40];
	(void) snprintf(taskName, sizeof(taskName), "[%d]: [%s]",
			osThreadGetPriority(OsTaskHandle),
			osThreadGetName(OsTaskHandle));

	ITM_sendStringwithTime(taskName);
}


