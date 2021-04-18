/*
 * delay.c
 *
 *  Created on: 12 / 02 /2021
 *      Author: Gabin BLOT
 */

#include "delay.h"

/*
 *  Basic delay functions
 */

void BSP_DELAY_ms(uint32_t delay)
{
	uint32_t	i;
	for(i=0; i<(delay*2500); i++);		// Tuned for ms at 48MHz
}

void BSP_DELAY_us(uint32_t delay)
{
	uint32_t	i;
	for(i=0; i<(delay*3); i++);		// Tuned for �s at 48MHz
}
