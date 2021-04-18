#ifndef WRITE_H
#define WRITE_H

#include "main.h"
#define MESSAGE_SIZE 60

void WRITE_Init(void);
void vTaskWrite(void *pvParameters);

// Kernel Objects
xQueueHandle	xConsoleQueue;
xSemaphoreHandle xSem_DMA_TC;

// Define the message_t type as an array of 60 char
typedef uint8_t message_t[MESSAGE_SIZE];

uint8_t DMA_USART2_TX_BUFFER[MESSAGE_SIZE];

#endif
