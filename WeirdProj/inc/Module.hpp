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

	c_u32ptr getOutputBufferPointer() const;

	//Returns ::LINKS if all input buffers were reserved
	u32 getNumberOfNextFreeInputBuffer() const;//                     @rat: all parameters are module-specific
	Error setInputBufferPointer(u32 bufferNumber, c_u32ptr pointer);//and all get/set funcs for these parameters are module-specific too

	const ModuleType getModuleType() const;

	virtual void update() = 0;
protected:
	c_u32ptr iBptr_parameter[::LINKS]; //@rat:  parameters will have different names, so will buffer pointers
	u32 oB[::SAMPLES_IN_BLOCK];//       (parameters and input buffer pointers are module-specific)
	ModuleType moduleType = ModuleType::NOT_INITIALIZED;
};

#endif /* MODULE_HPP_ */
