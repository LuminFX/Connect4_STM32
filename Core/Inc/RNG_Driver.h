/*
 * RNG_Driver.h
 *
 *  Created on: Apr 23, 2025
 *      Author: tylerschmitz
 */

#ifndef INC_RNG_DRIVER_H_
#define INC_RNG_DRIVER_H_

#include "stm32f4xx_hal.h"
#include "ErrorHandling.h"

#define RANDOM_NUM_MAX 7

void MX_RNG_Init();
uint8_t getRandomColumn();


#endif /* INC_RNG_DRIVER_H_ */
