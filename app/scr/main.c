/*
 * main.c
 *
 *  Created on: 27/01/2021
 *      Author: Olivia SP
 */

#include "main.h"


// Kernel Objects
xSemaphoreHandle xSemUART2_TC;


// Main program
int main()
{
	// Configure System Clock
	SystemClock_Config();

	// Initialize LED pin
	BSP_LED_Init();

	// Initialize the user Push-Button
	BSP_PB_Init();

	// Initialize Debug Console
	BSP_Console_Init();

	// Start Trace Recording
	vTraceEnable(TRC_START);


	// Create Semaphore object (this is not a 'give')
	xSemUART2_TC = xSemaphoreCreateBinary();

	// Create Queue to hold console messages
	xConsoleQueue = xQueueCreate(10, sizeof(message_t *));


	// Give a nice name to the Queue in the trace recorder
	vTraceSetQueueName(xConsoleQueue, "Console Queue");
	vTraceSetSemaphoreName(xSemUART2_TC, "xSEM_UART_TC");


	// Create Tasks
	xTaskCreate(vTask1, 		"Task_1", 		256, NULL, 2, NULL);
	xTaskCreate(vTask2, 		"Task_2", 		256, NULL, 2, NULL);
	xTaskCreate(vTaskWrite, 	"Task_Write", 	256, NULL, 1, NULL);

	// Start the Scheduler
	vTaskStartScheduler();

	while(1)
	{

		// The program should never be here...
	}
}

/*
 *	Task_1
 */
void vTask1 (void *pvParameters)
{
	message_t 	message;
	message_t	*pm;

	while(1)
	{
		// Prepare message
		my_sprintf((char *)message, "Arthour ! Pas changer assiette pour fromage !\r\n");

		// Send message to the Console Queue
		pm = &message;
		xQueueSendToBack(xConsoleQueue, &pm, 0);

		// Wait for 100ms
		vTaskDelay((100/portTICK_RATE_MS));
	}
}

/*
 *	Task_2
 */
void vTask2 (void *pvParameters)
{
	message_t 	message;
	message_t	*pm;

	while(1)
	{
		// Prepare message
		my_sprintf((char *)message, "Arthour ! Couhillere !\r\n");

		// Send message to Console Queue
		pm = &message;
		xQueueSendToBack(xConsoleQueue, &pm, 0);

		// Wait for 100ms
		vTaskDelay((100/portTICK_RATE_MS));
	}
}

/*
 * Task_Console
 */
void vTaskWrite (void *pvParameters)
{
	message_t *message;

	// Create Semaphore object
	xSemUART2_TC = xSemaphoreCreateBinary();

	// Give a nice name to the Semaphore in the trace recorder
	vTraceSetSemaphoreName(xSemUART2_TC, "xSemUART2_TC");

	// Initialize Debug Console
	BSP_Console_Init();

	NVIC_SetPriority(USART2_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1);

	NVIC_EnableIRQ(USART2_IRQn);


	while(1)
	{
		// Wait for something in the message Queue
		xQueueReceive(xConsoleQueue, &message, portMAX_DELAY);

		// Send message to console
		my_printf((const char *)message);
	}

}

