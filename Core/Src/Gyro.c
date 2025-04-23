/*
 * Gyro.c
 *
 *  Created on: Apr 3, 2025
 *      Author: tylerschmitz
 */

#include "Gyro.h"

static SPI_HandleTypeDef hspi5;
static HAL_StatusTypeDef gyroHALStatus;

void gyroInit(){

	GPIO_InitTypeDef GPIOFpinConfig;

	// GPIOF Init
	__HAL_RCC_GPIOF_CLK_ENABLE();
	GPIOFpinConfig.Mode = GPIO_MODE_AF_PP;
	GPIOFpinConfig.Pin = GYRO_MISO_PIN | GYRO_MOSI_PIN | GYRO_SCK_PIN;
	GPIOFpinConfig.Pull = GPIO_NOPULL;
	GPIOFpinConfig.Speed = GPIO_SPEED_FREQ_LOW;
	GPIOFpinConfig.Alternate = GPIO_AF5_SPI5;
	HAL_GPIO_Init(GYRO_MISO_PORT, &GPIOFpinConfig);

	// SPI5 Init
	__HAL_RCC_SPI5_CLK_ENABLE();
	hspi5.Instance = SPI5;
	hspi5.Init.Mode = SPI_MODE_MASTER;
	hspi5.Init.Direction = SPI_DIRECTION_2LINES;
	hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi5.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi5.Init.CLKPhase = SPI_PHASE_2EDGE;

	hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;

	hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;

	hspi5.Init.NSS = SPI_NSS_SOFT;

	gyroHALStatus = HAL_SPI_Init(&hspi5);
	if (gyroHALStatus == HAL_OK){
		APPLICATION_ASSERT(true);
	}
	else{
		APPLICATION_ASSERT(false);
	}

	// GPIOC Init
	GPIO_InitTypeDef GPIOCPinConfig;

	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIOCPinConfig.Mode = GPIO_MODE_OUTPUT_PP;
	GPIOCPinConfig.Pin = GYRO_CS_PIN;
	GPIOCPinConfig.Pull = GPIO_PULLDOWN;
	GPIOCPinConfig.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GYRO_CS_PORT, &GPIOCPinConfig);

	HAL_GPIO_WritePin(GYRO_CS_PORT, GYRO_CS_PIN, GPIO_PIN_SET);

	gyroConfigRegisters();

}

void gyroPower(){

	gyroWriteData(CTRL_REG1, GYRO_POWER_ON);

}

void gyroConfigRegisters(){

	gyroPower();
	gyroWriteData(CTRL_REG5, GYRO_REBOOT_MEM_ENABLE);

}

void gyroVerifyHALStatus(){

	if (gyroHALStatus == HAL_OK){
		APPLICATION_ASSERT(true);
	}
	else{
		APPLICATION_ASSERT(false);
	}

}

void gyroEnableCommunication(){
	HAL_GPIO_WritePin(GYRO_CS_PORT, GYRO_CS_PIN, GPIO_PIN_RESET);
}

void gyroDisableCommunication(){
	HAL_GPIO_WritePin(GYRO_CS_PORT, GYRO_CS_PIN, GPIO_PIN_SET);
}

uint8_t gyroGetData(uint8_t regToRead){

	uint8_t commandToSend = (GYRO_READ | regToRead);
	uint16_t receivedData = 0x00;

	gyroEnableCommunication();

	while (HAL_GPIO_ReadPin(GYRO_CS_PORT, GYRO_CS_PIN) != GPIO_PIN_RESET);

	gyroHALStatus = HAL_SPI_TransmitReceive(&hspi5, &commandToSend, (uint8_t*) &receivedData, GYRO_DATA_SIZE, GYRO_TIMEOUT);

	gyroVerifyHALStatus(gyroHALStatus);

	uint8_t DataReturned = (receivedData >> 8) & 0xFF;

	gyroDisableCommunication();

	return DataReturned;

}

void gyroWriteData(uint8_t regToWrite, uint8_t dataToWrite){

	uint16_t commandToSend = ((dataToWrite << 8) | (GYRO_WRITE | regToWrite));

	gyroEnableCommunication();

	while (HAL_GPIO_ReadPin(GYRO_CS_PORT, GYRO_CS_PIN) != GPIO_PIN_RESET);

	gyroHALStatus = HAL_SPI_Transmit(&hspi5, (uint8_t*) &commandToSend, GYRO_DATA_SIZE, GYRO_TIMEOUT);

	if (gyroHALStatus == HAL_OK){
		APPLICATION_ASSERT(true);
	}
	else{
		APPLICATION_ASSERT(false);
	}

	gyroDisableCommunication();

}

uint8_t getGyroConnect4Move(){

//	uint8_t id = gyroGetData(WHO_AM_I);
//	uint8_t ctrl = gyroGetData(CTRL_REG1);
//	uint8_t stat = gyroGetData(STATUS_REG);

	HAL_Delay(5);
	if (gyroGetData(STATUS_REG) & 0x02){

		uint8_t hi = gyroGetData(OUT_Y_H);
		uint8_t lo = gyroGetData(OUT_Y_L);
		int16_t y_rate = (int16_t)((hi << 8) | lo);
		float dps = y_rate * 0.00875f;

		if (dps > GYRO_MOVEMENT_THRESHOLD){
			return GYRO_SIGNAL_MOVE_RIGHT;
		}
		if (dps < -GYRO_MOVEMENT_THRESHOLD){
			return GYRO_SIGNAL_MOVE_LEFT;
		}
	}
	return GYRO_SIGNAL_NO_MOVE;

}







