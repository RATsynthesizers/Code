/*
 * CodecDriver.hpp
 *
 *  Created on: 20 окт. 2018 г.
 *      Author: maro4_000
 */

#ifndef CODECDRIVER_HPP_
#define CODECDRIVER_HPP_

#include <main.h>
#include "stm32f4xx_hal.h"

#define CODEC_ADDR_DEFAULT (1 << 5)

/*
 * This class contains desired codec configuration and required init function.
 * Any codec configuration may be chosen by writing specific values
 * in codec registers.
 */
class CodecDriver {
public:
	CodecDriver(const I2C_HandleTypeDef& instance_, const uint8_t hwAddress_)
			: instance(instance_), hwAddress(hwAddress_) {};

	void initCodec(void);

	void resetCodec(void);
private:
	//Number of codec registers
	static const uint8_t numOfRegisters = 7;

	//Array of values of codec registers
	static const uint8_t config[numOfRegisters];

	//I2C identifier
	const I2C_HandleTypeDef& instance;

	//Codec hardware address
	const uint8_t hwAddress;
};



#endif /* CODECDRIVER_HPP_ */
