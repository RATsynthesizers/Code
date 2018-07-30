/*
 * Module.cpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */
#include <Module.hpp>

Module::Module()
	: moduleType(typeid(this)) {
	for(uint32_t i = 0; i < ::SAMPLES_IN_BLOCK;
			outputBuffer[i] = 0, i++);

	for(uint32_t i = 0; i < ::LINKS;
			inputBufferPointer[i] = nullptr, i++);

	//instance++;
};

const_uint32_t_ptr Module::getOutputBufferPointer() const {
	return outputBuffer;
};

uint32_t Module::getNumberOfNextFreeInputBuffer() {
	for (uint32_t i = 0; i < ::LINKS; i++) {
		if (!inputBufferPointer[i])
			return i;
	};
	return ::LINKS;
};

Module::Error Module::setInputBufferPointer(uint32_t bufferNumber,
		const_uint32_t_ptr pointer) {
	if (bufferNumber >= ::LINKS)
		return Error::INVALID_BUFFER_NUMBER;

	inputBufferPointer[bufferNumber] = pointer;
	return Error::NO_ERROR;
};

const std::type_info& Module::getModuleType() const {
	return moduleType;
};

/*inline void Module::initializeInstance() {
	instance = 0;
};*/
