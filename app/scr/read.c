#include "main.h"
#include "read.h"

// Kernel objects
EventGroupHandle_t sensorsEventGroup;

void READ_Init(void)
{
	// Create Task
	xTaskCreate(vTaskRead, 	"TaskRead", 256, NULL, 10, NULL);
	// Create Event Group
	sensorsEventGroup = xEventGroupCreate();
}

// For buffer size
extern uint8_t DMA_USART2_RX_BUFFER[16];

// Read task
void vTaskRead(void *pvParameters)
{
	uint8_t		DMA_Counter;
	uint8_t		count;
	uint8_t		rx_buff;

	portTickType	xLastWakeTime;

	// Initialize timing
	xLastWakeTime = xTaskGetTickCount();

	// Initialize variables
	DMA_Counter = DMA1_Channel5->CNDTR;
	count = DMA_Counter;

	while(1)
	{
		// Get actual DMA counter value
		DMA_Counter = DMA1_Channel5->CNDTR;


		// While buffer isn't full
		while (count != DMA_Counter)
		{
			// Read and report the content of
			rx_buff = DMA_USART2_RX_BUFFER[8-count];

	#ifdef READ_DEBUG
			my_printf("\r\nYou've hit the '%c' key", rx_buff);
	#endif

			switch(rx_buff)
			{
				case 'a':
					//We clear all about sensor 1 to have a cleared area to work
					xEventGroupClearBits(sensorsEventGroup, (SENSOR1_CLEARED | SENSOR1_SET));
					xEventGroupSetBits(sensorsEventGroup, SENSOR1_SET);


					#ifdef READ_DEBUG
					my_printf("Sensor 1--> 1\r\n");
					#endif

					break;

				case 'b':
					xEventGroupClearBits(sensorsEventGroup, (SENSOR1_CLEARED | SENSOR1_SET));
					xEventGroupSetBits(sensorsEventGroup, SENSOR1_CLEARED);


					#ifdef READ_DEBUG
					my_printf("Sensor 1 --> 0\r\n");
					#endif

					break;


				case 'c':
					xEventGroupClearBits(sensorsEventGroup, (SENSOR2_CLEARED | SENSOR2_SET));
					xEventGroupSetBits(sensorsEventGroup, SENSOR2_SET);

					#ifdef READ_DEBUG
					my_printf("Sensor 2 --> 1\r\n");
					#endif

					break;

				case 'd':
					xEventGroupClearBits(sensorsEventGroup, (SENSOR2_CLEARED | SENSOR2_SET));
					xEventGroupSetBits(sensorsEventGroup, SENSOR2_CLEARED);

					#ifdef READ_DEBUG
					my_printf("sensor 2 --> 0 \r\n");
					#endif

					break;
				default:

					#ifdef READ_DEBUG
					my_printf("It's empty here\r\n");
					#endif

					break;

			}

			// Circular buffer count updated
			count--;
			if (count == 0)
				count = 8;
		}

		vTaskDelayUntil (&xLastWakeTime, (200/portTICK_RATE_MS));
	}
}
