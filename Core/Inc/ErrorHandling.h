/*
 * ErrorHandling.h
 *
 *  Created on: Apr 3, 2025
 *      Author: tylerschmitz
 */

#ifndef INC_ERRORHANDLING_H_
#define INC_ERRORHANDLING_H_

#include <stdbool.h>
#include "stm32f4xx_hal.h"

void APPLICATION_ASSERT(bool bVal);
void Error_Handler(void);

#endif /* INC_ERRORHANDLING_H_ */
