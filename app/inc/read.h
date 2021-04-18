#ifndef READ_H
#define READ_H

#include "main.h"

#define	SENSOR1_SET 		( (EventBits_t)( 0x01 << 0) ) //EventBits_t type en u16
#define	SENSOR1_CLEARED 	( (EventBits_t)( 0x01 << 1) )
#define	SENSOR2_SET 		( (EventBits_t)( 0x01 << 2) )
#define	SENSOR2_CLEARED 	( (EventBits_t)( 0x01 << 3) )

#define READ_DEBUG

#define READ_SENSORS_SIZE	2

void READ_Init(void);
void vTaskRead(void *pvParameters);

#endif
