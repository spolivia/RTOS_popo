#include "write.h"


		//Memo : pour envoyer un message à la console directement sans passer par le DMA
		//my_printf((const char *)message);

void WRITE_Init(void)
{
	// Queue pour garder les messages consoles
	xConsoleQueue = xQueueCreate(10, sizeof(message_t *));
	vTraceSetQueueName(xConsoleQueue, "Console Queue");
	xTaskCreate(vTaskWrite, "TaskWrite", 256, NULL, 10, NULL);
}

/*
 * WRITE_Task
 */
void vTaskWrite(void *pvParameters)
{
	message_t *message;

	// Create Semaphore object
	xSem_DMA_TC = xSemaphoreCreateBinary();

	// Give a nice name to the Semaphore in the trace recorder
	vTraceSetSemaphoreName(xSem_DMA_TC, "xSem_DMATC");

	// Set maximum priority for DMA1 interrupts
	NVIC_SetPriority(DMA1_Channel4_5_6_7_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1);

	// Enable EXTI line 4 to 15 (user button on line 13) interrupts
	NVIC_EnableIRQ(DMA1_Channel4_5_6_7_IRQn);


	while(1)
	{
		// Wait for something in the message Queue
		xQueueReceive(xConsoleQueue, &message, portMAX_DELAY);

		int n = 0;

		while((*message)[n] != '\0'){
			DMA_USART2_TX_BUFFER[n] = (*message)[n];
			n++;
		}

		// Enable from DMA transmission request
		USART2->CR3 |= USART_CR3_DMAT;

		// Set Memory Buffer size
		DMA1_Channel4->CNDTR = n;

		// Enable DMA1 Channel 4
		DMA1_Channel4->CCR |= DMA_CCR_EN;

		xSemaphoreTake(xSem_DMA_TC, portMAX_DELAY);

		// Disable DMA1 Channel 4
		DMA1_Channel4->CCR &= ~DMA_CCR_EN;

		// Disable from DMA transmission request
		USART2->CR3 &= ~USART_CR3_DMAT;
	}

}
