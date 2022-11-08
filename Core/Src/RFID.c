/*
 * RFID.c
 *
 *  Created on: Nov 5, 2022
 *      Author: studia
 */

#include "RFID.h"


uint8_t MFRC522_Read_Register(uint8_t Register_adress){

	//starting communication
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);

	//data format specified by rc522 datasheet
	uint8_t Data[2] = {(( 0x7E & (Register_adress << 1)) | 0x80), 0x00};

	uint8_t recive_buffor[2];
	uint16_t dataSize = 2;


	HAL_SPI_TransmitReceive(&hspi1, Data, recive_buffor, dataSize, HAL_MAX_DELAY);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

	//end of communication
  	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);

	return recive_buffor[1];
}


void MFRC522_Write_Register(uint8_t adress, uint8_t value){

	//starting comunication
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);

	uint8_t size = 2;
	uint8_t Data[2];

	//data format specified by rc522 datasheet
	Data[0] = ( 0x7E & (adress << 1) );
	Data[1] = value;

	HAL_SPI_Transmit ( &hspi1 , Data,  size, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);
}
