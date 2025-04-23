/*
 * Button_Driver.c
 *
 *  Created on: Feb 11, 2025
 *      Author: tylerschmitz
 */

#include "Button_Driver.h"

void Button_Init_Interrupt_Mode(){

	GPIO_InitTypeDef pinConfig;
	pinConfig.Mode = GPIO_MODE_IT_RISING;
	pinConfig.Pin = GPIO_PIN_0; // are these equal?
	pinConfig.Pull = GPIO_NOPULL;
	pinConfig.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIOA, &pinConfig);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}

void Button_Init(){

	GPIO_InitTypeDef pinConfig;
	pinConfig.Mode = GPIO_MODE_INPUT;
	pinConfig.Pin = GPIO_PIN_0; // are these equal?
	pinConfig.Pull = GPIO_NOPULL;
	pinConfig.Speed = GPIO_SPEED_FREQ_MEDIUM;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA, &pinConfig);

}

bool Button_Is_Pressed(){

	GPIO_PinState buttonVal = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
	if (buttonVal == GPIO_PIN_SET){
		return true;
	}
	else if (buttonVal == GPIO_PIN_RESET){
		return false;
	}
	else {
		return false;
	}


}
