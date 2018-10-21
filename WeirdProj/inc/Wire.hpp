/*
 * Wire.hpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */

#ifndef WIRE_HPP_
#define WIRE_HPP_

#include "stm32f4xx.h"
#include <Modules.hpp>

class Wire {
public:
	Wire(Module& src_, Module& dst_,
			Parameter::ParamName param_);

	void unplug();
	void replugConsumer(Module& dst_,
			Parameter::ParamName param_);
	void replugProvider(Module& src_);

	uint32_t bufferNumber;
	uint32_t realParamNum;
private:
	Module *destination;
	Module *source;

	void plug(Parameter::ParamName param_);
};

#endif /* WIRE_HPP_ */
