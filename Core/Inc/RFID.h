/*
 * RFID.h
 *
 *  Created on: Oct 5, 2022
 *      Author: studia
 */

#ifndef INC_RFID_H_
#define INC_RFID_H_

#include "stm32l1xx_hal.h"


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

/* MFRC522 Commands */
#define PCD_COMM_TRANCIVE              0X0C
#define PCD_COMM_IDLE                  0X00



/***********************************************************
 *Initialization of the MFRC522 module
 ***********************************************************/
extern MFRC522_Operation_Status RFID_init_MFRC522();

extern MFRC522_Operation_Status MFRC522_Request_Card();

/***********************************************************
 * Function is combining anti-colision process and card activation,
 * since this library for know does not handle multi card connection
 * @return pointer to a 4 bytes long table with NUID
 ***********************************************************/
extern uint8_t* Anticollision_UID_MFRC522();

extern MFRC522_Operation_Status Authorization_Card_MFRC522();

/***********************************************************
 * The funckcion is checking chosen block in card memory
 * @return Pointer to 16 bytes long table with blocks data
 * *********************************************************/
extern uint8_t* Check_Block_MFRC522(uint8_t blockNumber);


extern void MFRC522_Write_Register(uint8_t adress, uint8_t value);

extern uint8_t MFRC522_Read_Register(uint8_t adress);

extern MFRC522_Operation_Status MFRC522_Card_Operation(uint8_t command, uint8_t* sendingData, uint8_t sDataLenght, uint8_t* recivedData, uint8_t* rDataLenght);


#endif /* INC_RFID_H_ */
