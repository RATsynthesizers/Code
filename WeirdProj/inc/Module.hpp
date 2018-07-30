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

	c_u32ptr getOutputBufferPointer() const;

	//Returns nullptr if module was not connected to another one

	//u32ptr getInputBufferPointer();                //@rat: all parameters are module-specific
	//void setInputBufferPointer(c_u32ptr pointer);  //      and all get/set funcs for these parameters are module-specific too
	//inline bool isConnected();

	const std::type_info& getModuleType() const;

	virtual void update() = 0;

	//inline static void initializeInstance();
private:
	//u32ptr iBptr_parameter;                        //@rat:  parameters will have different names, so will buffer pointers
	                                                 //       (parameters and input buffer pointers are module-specific)
	uint32_t oB[::SAMPLES_IN_BLOCK];
	const std::type_info& moduleType;//Is it really necessary to keep this field?

	//static uint32_t instance;
};

#endif /* MODULE_HPP_ */
