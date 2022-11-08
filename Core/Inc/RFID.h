/*
 * RFID.h
 *
 *  Created on: Nov 5, 2022
 *      Author: studia
 */

#ifndef INC_RFID_H_
#define INC_RFID_H_

#include <stdio.h>
#include "stm32l1xx_hal.h"
#include "spi.h"
#include "gpio.h"



typedef enum{
	OPERATION_ERROR = 0,
	DONE_CORRECTLY
}MFRC522_Operation_Status;

/***********************************************************
 * using SPI2 on stm32l152ret6
 * SPI speed: 8 Mbit/s
 * CS: SPI2_CS - HIGH
 * CPOL = 1
 * CPHA = 1
 **********************************************************/


/* MFRC522 registers adress */
#define PCD_REG_COMMAND                0x01
#define PCD_REG_FIFODataReg            0x09
#define PCD_REG_FIFOLevelReg           0x0A
#define PCD_REG_BitFramingReg          0x0D
#define PCD_REG_ComIrqReg              0x04
#define PCD_REG_ErrorReg               0x06
#define PCD_REG_ComlEnReg              0x02
#define PCD_REG_VersionReg			   0x37

/* MFRC522 Commands */
#define PCD_COMM_TRANCIVE              0X0C
#define PCD_COMM_IDLE                  0X00



/* **************************************
 * Reads data
 * @return data from specified register
 * **************************************/
uint8_t MFRC522_Read_Register(uint8_t Register_adress);


/* **************************************
 * Writes data
 * **************************************/
void MFRC522_Write_Register(uint8_t adress, uint8_t value);


#endif /* INC_RFID_H_ */
