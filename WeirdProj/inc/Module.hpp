/*
 * Module.hpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */

#ifndef MODULE_HPP_
#define MODULE_HPP_


#include "stm32f4xx.h"
#include <Globals.hpp>

struct Parameter
{

	enum class ParameterName {
		AUDIO_IN = 0, FREQUENCY, AMPLIFICATION, OFFSET, WAVEFORM
	};

	uint32_t value;
	const_uint32_t_ptr inputBufferPointer[::LINKS];
	uint32_t bitmap;
	ParameterName paramType;

	//uint32_t setInputBufferPointer(const_uint32_t_ptr pointer);
};

class Module {
public:
	enum class ModuleType {
		NOT_INITIALIZED = -1, GENERATOR, AMPLIFIER
	};

	Module();
	virtual ~Module() {};

	const_uint32_t_ptr getOutputBufferPointer() const;
	ModuleType getModuleType() const;

	virtual void process() = 0;
    uint32_t connectedWires;
protected:
	uint32_t outputBuffer[::SAMPLES_IN_BLOCK];
	ModuleType moduleType = ModuleType::NOT_INITIALIZED;
};

#endif /* MODULE_HPP_ */
