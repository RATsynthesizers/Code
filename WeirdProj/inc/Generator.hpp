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

class Generator : public Module {
public:
	Generator(uint32_t amp, uint32_t freq);
private:
	Generator();
	Generator(const Generator& in);

	static uint32_t instance;

	uint32_t amplification;
	uint32_t frequency;
};

#endif /* GENERATOR_HPP_ */
