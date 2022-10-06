/*
 * RFID.c
 *
 *  Created on: Oct 5, 2022
 *      Author: studia
 */

#include "RFID.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

MFRC522_Operation_Status Request_Card_MFRC522(){


}


void Write_Register_MFRC522(uint8_t adress, uint8_t value){

	//starting comunication
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);

	uint8_t size = 2;
	uint8_t Data[2];

	//data format specified by rc522 datasheet
	Data[1] = ( 0x7E & (adress << 1) );
	Data[2] = value;

	HAL_SPI_Transmit ( &hspi2 , Data,  size, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
}

uint8_t* Read_Register_MFRC522(uint8_t adress){

	//starting comunication
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);

	//data format specified by rc522 datasheet
	uint8_t Data = ( (0x80 | (adress << 1)) & 0xFE );

	uint8_t recive_buffor;

	HAL_SPI_TransmitReceive( &hspi2 , &Data , &recive_buffor, 1, HAL_MAX_DELAY);


	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
}






