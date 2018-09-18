/*
 * Generator.hpp
 *
 *  Created on: 31 июл. 2018 г.
 *      Author: wetfloor
 */

#ifndef GENERATOR_HPP_
#define GENERATOR_HPP_

#include <Module.hpp>
#include "stm32f4xx.h"

class Generator: public Module {
public:

	enum class Params {
		Number = 4
	};

	//const static uint32_t numberOfParameters;

	Generator(const uint32_t& amp, const uint32_t& freq, const uint32_t& offst);

	static uint32_t getInstance();

	void process();

	Parameter parameter[static_cast<uint32_t>(Params::Number)];
private:
	Generator();
	Generator(const Generator& in);

	static uint32_t instance;

};

#endif /* GENERATOR_HPP_ */
