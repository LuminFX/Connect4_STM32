/*
 * Timer_Driver.h
 *
 *  Created on: Apr 22, 2025
 *      Author: tylerschmitz
 */

#ifndef INC_TIMER_DRIVER_H_
#define INC_TIMER_DRIVER_H_

#include "stm32f4xx_hal.h"
#include "ErrorHandling.h"

void MX_TIM2_Init(void);
void startGameTimer();
void stopGameTimer();
void callTIM2IRQHandler();

#endif /* INC_TIMER_DRIVER_H_ */
