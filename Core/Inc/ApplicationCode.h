/*
 * ApplicationCode.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */

#include "LCD_Driver.h"
#include "stm32f4xx_hal.h"
#include "gameDriver.h"
#include "Button_Driver.h"
#include "Timer_Driver.h"
#include "gyro.h"

#include <stdio.h>

#define USE_GYRO_FLAG 1
#define RUN_TESTS 0

#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

void ApplicationInit(void);
void displayConnect4();
void initConnect4();
void LCD_Touch_Polling_Connect4();
void runTests();

void initGameTimer();

#if (COMPILE_TOUCH_FUNCTIONS == 1)
void LCD_Touch_Polling_Demo(void);
#endif // (COMPILE_TOUCH_FUNCTIONS == 1)

#endif /* INC_APPLICATIONCODE_H_ */
