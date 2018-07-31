/*
 * Module.cpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */
#include <Module.hpp>

Module::Module() {                        //@rat: see hpp
	for(u32 i = 0; i < ::SAMPLES_IN_BLOCK;
			oB[i] = 0, i++);

	for(uint32_t i = 0; i < ::LINKS;
			iBptr_parameter[i] = nullptr, i++);
};

c_u32ptr Module::getOutputBufferPointer() const {
	return oB;
};

u32 Module::getNumberOfNextFreeInputBuffer() const {              //@rat: see hpp
	for (u32 i = 0; i < ::LINKS; i++) {
		if (!iBptr_parameter[i])
			return i;
	};
	return ::LINKS;
};

Module::Error Module::setInputBufferPointer(u32 bufferNumber,     //@rat: see hpp
		c_u32ptr pointer) {
	if (bufferNumber >= ::LINKS)
		return Error::INVALID_BUFFER_NUMBER;

	iBptr_parameter[bufferNumber] = pointer;
	return Error::NO_ERROR;
};

const Module::ModuleType Module::getModuleType() const {
	return moduleType;
};
