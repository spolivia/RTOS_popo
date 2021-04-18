#ifndef APP_INC_MAIN_H
#define APP_INC_MAIN_H

// Device header
#include "stm32f0xx.h"

// BSP functions
#include "bsp.h"

// FreeRTOS headers
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"

#include <stdbool.h>
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "queue.h"
#include "event_groups.h"
#include "stream_buffer.h"

// Global functions
int my_printf	(const char *format, ...);
int my_sprintf	(char *out, const char *format, ...);


uint8_t DMA_USART2_RX_BUFFER[16];


#define ElevatorMoving_bit    11
#define ElevatorGFloor_bit    6
#define Elevator1Floor_bit    7
#define Elevator2Floor_bit    8
#define ElevatorPalletIn_bit  12
#define ElevatorPalletOut_bit 9
#define BoxDistriCreated_bit  0
#define BoxDistriStart_bit    1
#define BoxDistriEnd_bit      2

#endif
