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

void ITM_TPIU_Init();
void SWO_Pin_Init(void);
void sendtoITM(char ch);
void ITM_sendStr(const char *str);
void ITM_sendStringwithTime(const char *str);


#endif /* INC_CUSTOM_H_ */
