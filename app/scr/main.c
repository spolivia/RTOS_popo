#include <my_tasks.h>
#include "main.h"
#include "clocks.h"
#include "delay.h"



// Main program
int main()
{
	// Configure System Clock
	SystemClock_Config();

	// Initialize LED pin
	BSP_LED_Init();

	// Initialize Push Button
	BSP_PB_Init();

	// Initialize Debug Console
	BSP_Console_Init();

	// Start Trace Recording
	vTraceEnable(TRC_START);

	Tasks_Init();

	// Initialize Debug Console
	BSP_Console_Init();

	// Start the Scheduler
	vTaskStartScheduler();

	while(1)
	{
		// The program should never be here...
	}
}


