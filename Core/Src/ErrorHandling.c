/*
 * ErrorHandling.c
 *
 *  Created on: Apr 3, 2025
 *      Author: tylerschmitz
 */

#include "ErrorHandling.h"

void APPLICATION_ASSERT(bool bVal){
	if (!bVal){
		while (1){};
	}
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

