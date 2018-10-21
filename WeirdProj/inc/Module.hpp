/*
 * Module.hpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */

//==============================================
//------------- Module Base Class --------------
//==============================================

#ifndef MODULE_HPP_
#define MODULE_HPP_


#include "stm32f4xx.h"
#include <Globals.hpp>

struct Parameter      // parameter structure
{
	enum class ParamName {                                         // List of all  parameter types in all modules
		AUDIO_IN = 0, FREQUENCY, AMPLIFICATION, OFFSET, WAVEFORM   // ?P ?M
	};

	uint32_t  value;                // parameter value
	c_u32_ptr iBptr[::SOCKETS];     // array of pointers to connected buffers ("sockets")
	uint32_t  socketbit;            // bit mask for sockets ^ (1 => socket is used, 0 => socket is free)
	ParamName paramType;            // type of the parameter

	//uint32_t setInputBufferPointer(const_uint32_t_ptr pointer);  // ??
};

class Module {
public:
	enum class ModuleType {                                        // List of all module types
		NOT_INITIALIZED = -1, GENERATOR, AMPLIFIER                 // ?M
	};

	Module();
	virtual ~Module() {};

	c_u32_ptr getOutputBufferPointer() const;    // get pointer to module's output buffer
	ModuleType getModuleType() const;            // get type of the module

	virtual void process() = 0;                  // module's processing method
    uint32_t connectedWires;                     // number of wires connected to otput; is module connected => needs to be updated?
protected:
	uint32_t outputBuffer[::BLOCKSIZE];          // module's outbut audio buffer
	ModuleType moduleType = ModuleType::NOT_INITIALIZED;  // module type
};

#endif /* MODULE_HPP_ */
