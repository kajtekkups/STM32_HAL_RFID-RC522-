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
	OPERATION_ERROR,
	DONE_CORRECTLY
}MFRC522_Operation_Status;

/***********************************************************
 * using SPI2 on stm32l152ret6
 * SPI speed: 8 Mbit/s
 * CS: SPI2_CS - HIGH
 **********************************************************/


/***********************************************************
 *Initialization of the MFRC522 module
 ***********************************************************/
extern MFRC522_Operation_Status RFID_init_MFRC522();

extern MFRC522_Operation_Status Request_Card_MFRC522();

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


extern void Write_Register_MFRC522(uint8_t adress, uint8_t value);
extern uint8_t* Read_Register_MFRC522(uint8_t adress);
#endif /* INC_RFID_H_ */
