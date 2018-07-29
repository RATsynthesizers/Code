/*
 * Module.cpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */
#include <Module.hpp>

Module::Module()
	: inputBufferPointer(nullptr), moduleType(typeid(this)) {
	for(uint32_t i = 0; i < ::SAMPLES_IN_BLOCK;
			outputBuffer[i] = 0, i++);

	//instance++;
};

const_uint32_t_ptr Module::getOutputBufferPointer() const {
	return outputBuffer;
};

uint32_t_ptr Module::getInputBufferPointer() {
	return inputBufferPointer;
};

void Module::setInputBufferPointer(const_uint32_t_ptr pointer) {
	inputBufferPointer = const_cast<uint32_t_ptr>(pointer);
};

/*inline bool Module::isConnected() {
	return inputBufferPointer;
};*/

const std::type_info& Module::getModuleType() const {
	return moduleType;
};

/*inline void Module::initializeInstance() {
	instance = 0;
};*/
