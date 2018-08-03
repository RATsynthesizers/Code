/*
 * Wire.hpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */

#ifndef WIRE_HPP_
#define WIRE_HPP_

#include <Module.hpp>
#include "stm32f4xx.h"

class Wire {
public:
	Wire(const Module& providerParam, Module& consumerParam);

	void unplug();
private:
	Wire();
	Wire(const Wire& in);

	Module& consumer;
	uint32_t bufferNumber;
};

#endif /* WIRE_HPP_ */
