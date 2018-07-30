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

	Module();
	virtual ~Module();

	const_uint32_t_ptr getOutputBufferPointer() const;

	//Returns ::LINKS if all input buffers were reserved
	uint32_t getNumberOfNextFreeInputBuffer();
	Error setInputBufferPointer(uint32_t bufferNumber, const_uint32_t_ptr pointer);

	const std::type_info& getModuleType() const;

	virtual void update() = 0;

	//inline static void initializeInstance();
private:
	const_uint32_t_ptr inputBufferPointer[::LINKS];
	uint32_t outputBuffer[::SAMPLES_IN_BLOCK];
	const std::type_info& moduleType;//Is it really necessary to keep this field?

	//static uint32_t instance;
};

#endif /* MODULE_HPP_ */
