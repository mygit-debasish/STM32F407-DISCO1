/*
 * customTask.c
 *
 *  Created on: Apr 6, 2026
 *      Author: debasish Das
 */

#include "customTask.h"
#include "custom.h"

#include "FreeRTOS.h"
#include "queue.h"

extern osThreadAttr_t taskDubug_attribute;
extern osThreadAttr_t newAcquireTask_attributes;
extern osThreadAttr_t newAcquireTask2_attributes;

extern osThreadId_t debugTaskHandle;
extern osThreadId_t newAcquireTaskHandle;
extern osThreadId_t newAcquireTask2Handle;

extern osMutexId_t myMutexITMHandle;

/* Queue Declaration */
extern QueueHandle_t myQueue;

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
	static char ch = 48;

	for (;;)
	{
		/*Acquire the Mutex */
		osMutexAcquire(&myMutexITMHandle, 200);

//		if (xQueueSend(myQueue, &ch, portMAX_DELAY) != pdPASS)
//		{
//			vTaskDelay(pdMS_TO_TICKS(10));
//		}
		ITM_Get_TasknamePriorityTaskHandle(newAcquireTaskHandle);

		osMutexRelease(&myMutexITMHandle);

		ch++;
		sendtoITM(ch);

		if (ch >= 58)
		{
			ch = 48;
			osThreadTerminate(newAcquireTaskHandle);
			newAcquireTaskHandle = NULL;
		}

		vTaskDelay(pdMS_TO_TICKS(500));
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
	uint8_t Rec;

	for (;;)
	{
		/*Acquire the Mutex */
		osMutexAcquire(&myMutexITMHandle, 200);

//		if (xQueueReceive(myQueue, &Rec, portMAX_DELAY) != pdPASS)
//		{
//			vTaskDelay(pdMS_TO_TICKS(10));i
//		}

		ITM_Get_TasknamePriorityTaskHandle(newAcquireTask2Handle);

		osMutexRelease(&myMutexITMHandle);

		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

/* Private functions definition */
void ITM_Get_TasknamePriority(osThreadAttr_t *OsThreadAttr)
{
	char taskName[40];
	(void) snprintf(taskName, sizeof(taskName), "[%d] [%s]",
			OsThreadAttr->priority, OsThreadAttr->name);

	ITM_sendStringwithTime(taskName);
}

void ITM_Get_TasknamePriorityTaskHandle(osThreadId_t OsTaskHandle)
{
	char taskName[60];
	UBaseType_t freeStack = uxTaskGetStackHighWaterMark(OsTaskHandle);

	(void) snprintf(taskName, sizeof(taskName), "[P:%d] [%-15s] [Free: %u] [CYLCNT: %lu]",
			osThreadGetPriority(OsTaskHandle), osThreadGetName(OsTaskHandle),
			freeStack,
			DWT->CYCCNT);

	ITM_sendStringwithTime(taskName);
}

void ITM_Get_TasknamePriorityData(osThreadId_t OsTaskHandle, void *pData)
{
	char taskName[40];
	(void) snprintf(taskName, sizeof(taskName), "[%d]: [%s] [%c]",
			osThreadGetPriority(OsTaskHandle), osThreadGetName(OsTaskHandle),
			(*(char*) pData));

	ITM_sendStringwithTime(taskName);
}



void DWT_Int()
{
	/* Enable Debug Exception and Monitor Control Registser */
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

	/* Resett the cycle counter */
	DWT->CYCCNT = 0;

	/* Start counting */
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}
