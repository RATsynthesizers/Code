/*
 * Wire.hpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */

#ifndef WIRE_HPP_
#define WIRE_HPP_

#include <Module.hpp>
#include <Generator.hpp>
#include <Amp.hpp>
#include "stm32f4xx.h"

class Wire {
public:
	Wire(Module& provider_, Module& consumer_,
			Parameter::ParameterName parameter_);

	void unplug();
	void replugConsumer(const Module& consumer_,
			Parameter::ParameterName parameter_);
	void replugProvider(const Module& provider_);

	uint32_t bufferNumber;
private:
	Module& consumer;
	Module& provider;

	void plug(Parameter::ParameterName parameter_);
};

#endif /* WIRE_HPP_ */
