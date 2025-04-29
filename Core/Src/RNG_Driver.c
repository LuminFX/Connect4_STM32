/*
 * RNG_Driver.c
 *
 *  Created on: Apr 23, 2025
 *      Author: tylerschmitz
 */

#include "RNG_Driver.h"

RNG_HandleTypeDef hrng;

/**
  * @brief RNG Initialization Function
  * @param None
  * @retval None
  */
void MX_RNG_Init(void)
{

  /* USER CODE BEGIN RNG_Init 0 */

  /* USER CODE END RNG_Init 0 */

  /* USER CODE BEGIN RNG_Init 1 */

  /* USER CODE END RNG_Init 1 */
  hrng.Instance = RNG;
  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RNG_Init 2 */

  /* USER CODE END RNG_Init 2 */

}

uint8_t getRandomColumn() {
    uint32_t randomNum = 0;
    HAL_StatusTypeDef status = HAL_RNG_GenerateRandomNumber(&hrng, &randomNum);

    if (status == HAL_OK) {

        return (uint8_t)(randomNum % RANDOM_NUM_MAX);

    } else {

        return 0;

    }
}
