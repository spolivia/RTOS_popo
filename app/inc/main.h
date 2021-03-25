/*
 * main.h
 *
 *  Created on: 29 Jan. 2020
 *      Author: gabin
 */

#ifndef APP_INC_MAIN_H_
#define APP_INC_MAIN_H_

// Device header
#include "stm32f0xx.h"

// BSP functions
#include "bsp.h"

//Clock functions
#include "clock.h"

// FreeRTOS headers
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "queue.h"
#include "event_groups.h"
#include "stream_buffer.h"



// Static functions
void SystemClock_Config	(void);

// Global functions
int my_printf	(const char *format, ...);
int my_sprintf	(char *out, const char *format, ...);

// FreeRTOS tasks
void vTask1 		(void *pvParameters);
void vTask2 		(void *pvParameters);
void vTaskWrite 	(void *pvParameters);

// Kernel objects
xSemaphoreHandle xSem;

// Trace User Events Channels
traceString ue1, ue2;

// Kernel Objects
xQueueHandle	xConsoleQueue;

// Define the message_t type as an array of 60 char
typedef uint8_t message_t[60];

#endif /* APP_INC_MAIN_H_ */
