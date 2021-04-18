
#include "my_tasks.h"
#include "read.h"
#include "write.h"
#include "main.h"
#include "delay.h"

// Kernel objects
xSemaphoreHandle xSemPB;
xSemaphoreHandle xSemLed;


extern EventGroupHandle_t sensorsEventGroup;
extern xQueueHandle xConsoleQueue;

void Tasks_Init()
{
	// Create Semaphore objects
	xSemPB = xSemaphoreCreateBinary();
	xSemLed = xSemaphoreCreateBinary();

	xSemaphoreGive(xSemLed);

	// Create Tasks
	xTaskCreate(vTask1, 	"Task_1"	, 256, NULL, 1, NULL);
	xTaskCreate(vTask2, 	"Task_2"	, 256, NULL, 1, NULL);

	// Give a nice name to the Semaphore in the trace recorder
	vTraceSetSemaphoreName(xSemPB, "xSemPB");
	vTraceSetSemaphoreName(xSemLed, "xSemLed");

	READ_Init();
	WRITE_Init();
}

/*
 *	Task1 led on quickly  "a - b"
 */
void vTask1 (void *pvParameters)
{
	message_t msg = "Hello from task1 \r\n" ;
	message_t * pm ;
	pm = &msg ;
	while(1)
	{

		xQueueSendToBack(xConsoleQueue, &pm, portMAX_DELAY);

		xEventGroupWaitBits(sensorsEventGroup, SENSOR1_SET, pdFALSE, pdTRUE, portMAX_DELAY);

		if(xSemaphoreTake(xSemLed, 5000/portTICK_RATE_MS) == pdPASS)
		{
			BSP_LED_On();
			BSP_DELAY_ms(100);
			BSP_LED_Off();
			BSP_DELAY_ms(200);
			xSemaphoreGive(xSemLed);
		}


		xEventGroupWaitBits(sensorsEventGroup, SENSOR1_CLEARED, pdFALSE, pdTRUE, portMAX_DELAY);

		if(xSemaphoreTake(xSemLed, 5000/portTICK_RATE_MS) == pdPASS)
		{
			BSP_LED_On();
			BSP_DELAY_ms(100);
			BSP_LED_Off();
			BSP_DELAY_ms(200);
			BSP_LED_On();
			BSP_DELAY_ms(100);
			BSP_LED_Off();
			BSP_DELAY_ms(200);
			xSemaphoreGive(xSemLed);
		}
	}
}


/*
 *	Task2 led on slowly
 */
void vTask2 (void *pvParameters)
{
	while(1)
	{
		xEventGroupWaitBits(sensorsEventGroup, SENSOR2_SET, pdFALSE, pdTRUE, portMAX_DELAY);

		if(xSemaphoreTake(xSemLed, 5000/portTICK_RATE_MS) == pdPASS)
		{
			BSP_LED_On();
			BSP_DELAY_ms(500);
			BSP_LED_Off();
			BSP_DELAY_ms(500);
			xSemaphoreGive(xSemLed);
		}


		xEventGroupWaitBits(sensorsEventGroup, SENSOR2_CLEARED, pdFALSE, pdTRUE, portMAX_DELAY);

		if(xSemaphoreTake(xSemLed, 5000/portTICK_RATE_MS) == pdPASS)
		{
			BSP_LED_On();
			BSP_DELAY_ms(500);
			BSP_LED_Off();
			BSP_DELAY_ms(500);
			BSP_LED_On();
			BSP_DELAY_ms(500);
			BSP_LED_Off();
			BSP_DELAY_ms(500);
			xSemaphoreGive(xSemLed);
		}
	}
}


