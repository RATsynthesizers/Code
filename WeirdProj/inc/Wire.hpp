/*
 * Wire.hpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */

//==============================================
//---------------- Wire Class ------------------
//==============================================

#ifndef WIRE_HPP_
#define WIRE_HPP_

#include "stm32f4xx.h"
#include <Modules.hpp>

class Wire {
public:
	Wire(Module& src_, Module& dst_,
			Parameter::ParamName param_);

	void unplug();                           // unplug wire from provider & consumer
	void replugConsumer(Module& dst_,        // unplug from one consumer and plug to another
			Parameter::ParamName param_);
	void replugProvider(Module& src_);       // unplug from one provider and plug to another

	uint32_t paramSocket;              // wire is connected to this parameter's socket 
	uint32_t paramIndex;               // index of parameter in module's parameter array
private:
	Module *destination;               // destination module (consumer)
	Module *source;                    // source module (provider)

	void plug(Parameter::ParamName param_);  // plug wire to modules (specify param in destination module)
};

#endif /* WIRE_HPP_ */
