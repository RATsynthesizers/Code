/*
 * CodecDriver.cpp
 *
 *  Created on: 21 окт. 2018 г.
 *      Author: maro4_000
 */

#include "CodecDriver.hpp"

#ifdef DESIRED_CONFIG
const uint8_t CodecDriver::config[CodecDriver::numOfRegisters]
								  = {0xA8, 0x0C, 0x79, 0x00, 0x00, 0x00, 0x03};
#else
const uint8_t CodecDriver::config[CodecDriver::numOfRegisters]
								  = {0, 0, 0, 0, 0, 0, 0};
#endif

void CodecDriver::initCodec() {
	resetCodec();
	HAL_Delay(1);
	//HAL_I2C_Mem_Write(&instance, )

};

void CodecDriver::resetCodec() {

};
