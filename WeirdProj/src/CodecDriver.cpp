/*
 * CodecDriver.cpp
 *
 *  Created on: 21 окт. 2018 г.
 *      Author: maro4_000
 */

#include "CodecDriver.hpp"

#ifdef CODEC_CUSTOM_CFG
uint8_t CodecDriver::config[CodecDriver::numOfRegisters]
								  = {0xA8, 0x0C, 0x79, 0x00, 0x00, 0x00, 0x02};
#else
uint8_t CodecDriver::config[CodecDriver::numOfRegisters]
								  = {0, 0, 0, 0, 0, 0, 0};
#endif

void CodecDriver::initCodec() {
	resetCodec();
	//HAL_Delay(1); - wait for codec MCLK to appear

	//Activate Control Port Mode
	uint8_t tmp = CPEN | PDN;
	HAL_I2C_Mem_Write(&instance, codecAddress, Mode_Ctrl_2, CODEC_MEMADD_SIZE, &tmp, 1, 1);

	//Write contents of 6 registers, then clear PDN bit and power codec up
	for(uint8_t i = Mode_Control_1; i < Chip_ID; i++)
		HAL_I2C_Mem_Write(&instance, codecAddress, i, CODEC_MEMADD_SIZE, CodecDriver::config + i, 1, 1);
};

void CodecDriver::resetCodec() {
	HAL_GPIO_WritePin(CODEC_RESET_PORT, CODEC_RESET_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(CODEC_RESET_PORT, CODEC_RESET_Pin, GPIO_PIN_SET);


};
