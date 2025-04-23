/*
 * Button_Driver.h
 *
 *  Created on: Feb 11, 2025
 *      Author: tylerschmitz
 */

#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_

#include <stdbool.h>
#include "stm32f4xx_hal.h"

#define BUTTON_PORT 0
#define BUTTON_PIN 0
#define IS_PRESSED 1
#define NOT_PRESSED 0

void Button_Init();
bool Button_Is_Pressed();
void Button_Init_Interrupt_Mode();

#endif /* BUTTON_DRIVER_H_ */
