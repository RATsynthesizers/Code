/*
 * Module.cpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */
#include <Module.hpp>

Module::Module()
	: /*inputBufferPointer(nullptr)*/, moduleType(typeid(this)) {  //@rat: see hpp
	for(u32 i = 0; i < ::SAMPLES_IN_BLOCK;
			oB[i] = 0, i++);

	//instance++;
};

c_u32ptr Module::getOutputBufferPointer() const {
	return oB;
};

// uint32_t_ptr Module::getInputBufferPointer() {                 //@rat: see hpp
// 	return inputBufferPointer;
// };

// void Module::setInputBufferPointer(c_u32ptr pointer) {         //@rat: see hpp
// 	inputBufferPointer = const_cast<uint32_t_ptr>(pointer);
// };

/*inline bool Module::isConnected() {
	return inputBufferPointer;
};*/

const std::type_info& Module::getModuleType() const {
	return moduleType;
};

/*inline void Module::initializeInstance() {
	instance = 0;
};*/
