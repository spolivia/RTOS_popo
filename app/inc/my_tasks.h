#ifndef MY_TASK_H
#define MY_TASK_H

#include "stm32f0xx.h"
#include <stdbool.h>

void Tasks_Init(void);

// FreeRTOS tasks
void vTask1 	(void *pvParameters);
void vTask2 	(void *pvParameters);

#endif
