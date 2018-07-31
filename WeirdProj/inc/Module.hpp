/*
 * Module.hpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */

#ifndef MODULE_HPP_
#define MODULE_HPP_

#include <typeinfo>
#include "stm32f4xx.h"
#include <Globals.hpp>

class Module {
public:
	enum class Error {
		NO_ERROR = 0, INVALID_BUFFER_NUMBER = 1
	};

	enum class ModuleType {
		NOT_INITIALIZED = 0, GENERATOR = 1
	};

	Module();
	virtual ~Module();

	const_uint32_t_ptr getOutputBufferPointer() const;

	//Returns ::LINKS if all input buffers were reserved
	uint32_t getNumberOfNextFreeInputBuffer() const;
	Error setInputBufferPointer(const uint32_t& bufferNumber,
			const_uint32_t_ptr pointer);

	ModuleType getModuleType() const;

	virtual void process() = 0;
protected:
	const_uint32_t_ptr inputBufferPointer[::LINKS];
	uint32_t outputBuffer[::SAMPLES_IN_BLOCK];
	ModuleType moduleType = ModuleType::NOT_INITIALIZED;
};

#endif /* MODULE_HPP_ */
