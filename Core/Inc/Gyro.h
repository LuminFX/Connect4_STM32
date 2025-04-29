/*
 * Gyro.h
 *
 *  Created on: Apr 3, 2025
 *      Author: tylerschmitz
 */

#ifndef INC_GYRO_H_
#define INC_GYRO_H_

#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include "ErrorHandling.h"
#include <stdio.h>

#define GYRO_SIGNAL_NO_MOVE 0
#define GYRO_SIGNAL_MOVE_LEFT 1
#define GYRO_SIGNAL_MOVE_RIGHT 2

#define GYRO_MOVEMENT_THRESHOLD 50

#define WHO_AM_I 0x0F
#define CTRL_REG1 0x20
#define CTRL_REG5 0x24
#define OUT_TEMP 0x26
#define STATUS_REG 0x27
#define Y_STAT_REG_POS 0x2

#define DEG_PER_SEC_CONVERSION 0.00875f

#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B


// GPIOF GYRO PINS
#define GYRO_SCK_PIN GPIO_PIN_7
#define GYRO_MOSI_PIN GPIO_PIN_9
#define GYRO_MISO_PIN GPIO_PIN_8
#define GYRO_MISO_PORT GPIOF

//GPIOC GYRO PINS
#define GYRO_CS_PIN GPIO_PIN_1
#define GYRO_CS_PORT GPIOC

//Other
#define GYRO_READ (0x1 << 7)
#define GYRO_WRITE (0x0 << 0x7)
#define GYRO_TIMEOUT 0x20
#define GYRO_DATA_SIZE 0x2
#define GYRO_POWER_ON 0x1F
#define GYRO_REBOOT_MEM_ENABLE 0x80

#define GYRO_TEMP_NORMALIZE 8

void gyroInit();
void gyroPrintDeviceId();
void gyroPower();
void gyroPrintTemp();
void gyroConfigRegisters();
void gyroReadRegisters();
void gyroVerifyHALStatus();
void gyroEnableCommunication();
void gyroDisableCommunication();
uint8_t gyroGetData(uint8_t regToRead);
void gyroWriteData(uint8_t regToWrite, uint8_t dataToWrite);

uint8_t getGyroConnect4Move();


#endif /* INC_GYRO_H_ */
