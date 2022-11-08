/*
 * tests.c
 *
 *  Created on: Nov 8, 2022
 *      Author: studia
 */

#include "tests.h"

// reads board version register, if wynik == decimal 142 program is working
void Stable_communication_read(){

	uint8_t wynik = MFRC522_Read_Register(PCD_REG_VersionReg);

	printf(" %u \n", wynik);
	HAL_Delay(100);


}


// output on the logic analzayzer should be 2, 3
void Stable_communication_write(){

	MFRC522_Write_Register(PCD_REG_COMMAND, 3);
	HAL_Delay(100);
}
