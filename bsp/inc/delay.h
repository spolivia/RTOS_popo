/*
 * delay.h
 *
 *  Created on: 12 / 02 /2021
 *      Author: Gabin BLOT
 */

#ifndef BSP_INC_DELAY_H_
#define BSP_INC_DELAY_H_

#include "stm32f0xx.h"

/*
 * Software counting delays
 */

void BSP_DELAY_ms	(uint32_t delay);
void BSP_DELAY_us	(uint32_t delay);

#endif /* BSP_INC_DELAY_H_ */
