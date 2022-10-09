/*
 * RFID.c
 *
 *  Created on: Oct 5, 2022
 *      Author: studia
 */

#include <stdio.h>
#include "RFID.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

#include "usart.h"

void MFRC522_Write_Register(uint8_t adress, uint8_t value){

	//starting comunication
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);

	uint8_t size = 2;
	uint8_t Data[2];

	//data format specified by rc522 datasheet
	Data[0] = ( 0x7E & (adress << 1) );
	Data[1] = value;

	HAL_SPI_Transmit ( &hspi2 , Data,  size, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
}

uint8_t MFRC522_Read_Register(uint8_t adress){

	//starting communication
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);

	//data format specified by rc522 datasheet
	uint8_t Data = ( (0x80 | (adress << 1)) & 0xFE );

	uint8_t recive_buffor;

	HAL_SPI_TransmitReceive( &hspi2 , &Data , &recive_buffor, 1, HAL_MAX_DELAY);


	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);

	return recive_buffor;
}

MFRC522_Operation_Status MFRC522_Card_Operation(uint8_t command, uint8_t* sendingData, uint8_t sDataLenght, uint8_t* recivedData, uint8_t* rDataLenght){


	MFRC522_Operation_Status status = DONE_CORRECTLY;


/* 1. Flushing FIFO buffer */
	uint8_t lvlRegisterData = 0x80 | MFRC522_Read_Register(PCD_REG_FIFOLevelReg);
	MFRC522_Write_Register(PCD_REG_FIFOLevelReg, lvlRegisterData);

/* 2. Making sure that no commend is proceed */
	MFRC522_Write_Register(PCD_REG_COMMAND, PCD_COMM_IDLE);

/* 3. Writing data to the FIFO buffer */
	for(int i = 0; i < sDataLenght; i++){
		MFRC522_Write_Register(PCD_REG_FIFODataReg, sendingData[i]);
	}

/* 4.1 Command execution*/
	MFRC522_Write_Register(PCD_REG_COMMAND, command);

	if(command == PCD_COMM_TRANCIVE){
		uint8_t bitMask = 0x80 | MFRC522_Read_Register(PCD_REG_BitFramingReg);

		MFRC522_Write_Register(PCD_REG_BitFramingReg, bitMask);
	}

/* 5. checking transmition status */

	// Setting interrupt status register
	MFRC522_Write_Register(PCD_REG_ComIrqReg, 0x7F);

	MFRC522_Write_Register(PCD_REG_ComlEnReg, 0xF7); //TODO: check proper value for ComlEnReg (error)

	// Setting command interrupt register check value
	uint8_t  ComIrqRegCheckValue;
	switch(command){
		case PCD_COMM_TRANCIVE: {

			ComIrqRegCheckValue = 0x20; //TODO: check if value is correct
		}
		//TODO: add transmit and authentification
	}

	uint8_t ComIrqRegState;
	int loopsNumber = 20000; //TODO: set correct value (depending on the time of the loop)
	do{
		ComIrqRegState = MFRC522_Read_Register(PCD_REG_ComIrqReg);
		loopsNumber--;

	}while((loopsNumber > 0) && !( ComIrqRegState & ComIrqRegCheckValue));

/* 6. Clear bit framing register */
	MFRC522_Write_Register(PCD_REG_BitFramingReg, 0x7F);

/* 7. reading data from the FIFO buffer */
	if(MFRC522_Read_Register(PCD_REG_ErrorReg ) & 0x1B){

		status = OPERATION_ERROR;

	}else{

		if(loopsNumber > 0){
			*rDataLenght = MFRC522_Read_Register(PCD_REG_FIFOLevelReg);
			for(int i = 0; i < *rDataLenght; i++){
				recivedData[i] = MFRC522_Read_Register(PCD_REG_FIFODataReg);
			}
		}else{
			status = OPERATION_ERROR;
		}
	}


	return status;
}

__io_putchar(int ch)
{
  if (ch == '\n') {
    __io_putchar('\r');
  }

  HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, HAL_MAX_DELAY);

  return (int)1;
}

MFRC522_Operation_Status MFRC522_Request_Card(){


	/* 1. Set card transmit framing */
	MFRC522_Write_Register(PCD_REG_BitFramingReg, 0x07);  //TODO: Not sure if the value is right


	/* 2. request */
	uint8_t srData[2] = {0x26, 0}; //Buffer for sent and received data
	uint8_t sDataLenght = 1;
	uint8_t rDataLenght;

	MFRC522_Operation_Status status;
	status = MFRC522_Card_Operation(PCD_COMM_TRANCIVE, srData, sDataLenght, srData, &rDataLenght);




	//TODO: check ATQA
	if(rDataLenght != 2){
		status = OPERATION_ERROR;
	}
	//TODO:just for debuging
	for(uint8_t i = 0; i < rDataLenght; i++){
		printf("ATQA: %d \n", srData[i]);
	}

	/* 3. Set transmit framing */
	MFRC522_Write_Register(PCD_REG_BitFramingReg, 0x07);

	return status;
}




