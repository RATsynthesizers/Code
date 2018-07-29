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
	Module();
	virtual ~Module();

	const_uint32_t_ptr getOutputBufferPointer() const;

	//Returns nullptr if module was not connected to another one
	uint32_t_ptr getInputBufferPointer();
	void setInputBufferPointer(const_uint32_t_ptr pointer);
	//inline bool isConnected();

	const std::type_info& getModuleType() const;

	virtual void update() = 0;

	//inline static void initializeInstance();
private:
	uint32_t_ptr inputBufferPointer;
	uint32_t outputBuffer[::SAMPLES_IN_BLOCK];
	const std::type_info& moduleType;//Is it really necessary to keep this field?

	//static uint32_t instance;
};

#endif /* MODULE_HPP_ */
