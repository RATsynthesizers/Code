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
	enum class ParamName {
		AUDIO_IN = 0, FREQUENCY, AMPLIFICATION, OFFSET, WAVEFORM   // ?P ?M
	};

	uint32_t  value;
	c_u32_ptr iBptr[::SOCKETS];
	uint32_t  socketbit;
	ParamName paramType;

	//uint32_t setInputBufferPointer(const_uint32_t_ptr pointer);
};

class Module {
public:
	enum class ModuleType {
		NOT_INITIALIZED = -1, GENERATOR, AMPLIFIER                 // ?M
	};

	Module();
	virtual ~Module() {};

	c_u32_ptr getOutputBufferPointer() const;
	ModuleType getModuleType() const;

	virtual void process() = 0;
    uint32_t connectedWires;
protected:
	uint32_t outputBuffer[::BLOCKSIZE];
	ModuleType moduleType = ModuleType::NOT_INITIALIZED;
};

#endif /* MODULE_HPP_ */