/*
 * CodecDriver.cpp
 *
 *  Created on: 21 окт. 2018 г.
 *      Author: maro4_000
 */

#include "CodecDriver.hpp"

#ifdef DESIRED_CONFIG
uint8_t CodecDriver::config[CodecDriver::numOfRegisters]
								  = {0xA8, 0x0C, 0x79, 0x00, 0x00, 0x00, 0x02};
#else
uint8_t CodecDriver::config[CodecDriver::numOfRegisters]
								  = {0, 0, 0, 0, 0, 0, 0};
#endif

void CodecDriver::initCodec() {
	resetCodec();
	//HAL_Delay(1);

	//Activate Control Port Mode
	uint8_t tmp = CPEN | PDN;
	HAL_I2C_Mem_Write(&instance, codecAddress, Mode_Ctrl_2, CODEC_MEMADD_SIZE, &tmp, 1, 1);

	//Write contents of all required registers
	for(uint8_t i = Mode_Control_1; i < Chip_ID; i++) {
		HAL_I2C_Mem_Write(&instance, codecAddress, i, CODEC_MEMADD_SIZE, CodecDriver::config + i, 1, 1);
	};
};

void CodecDriver::resetCodec() {

};
