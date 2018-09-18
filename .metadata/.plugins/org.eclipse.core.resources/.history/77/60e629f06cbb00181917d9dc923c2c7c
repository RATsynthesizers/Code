/*
 * Module.cpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */
#include <Module.hpp>

/*uint32_t Parameter::setInputBufferPointer(const_uint32_t_ptr pointer) {
	uint32_t shiftingValue = bitmap;
	uint32_t socketNumber = 0;

	while (shiftingValue & 1) {
		shiftingValue >>= 1;
		socketNumber++;
	};

	Parameter::inputBufferPointer[socketNumber] = pointer;
	return socketNumber;
};*/

Module::Module() : connectedWires(0) {
	for(uint32_t i = 0; i < ::SAMPLES_IN_BLOCK;
			outputBuffer[i] = 0, i++);
};

const_uint32_t_ptr Module::getOutputBufferPointer() const {
	return outputBuffer;
};

Module::ModuleType Module::getModuleType() const {
	return moduleType;
};
