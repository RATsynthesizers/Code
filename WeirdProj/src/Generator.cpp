/*
 * Generator.cpp
 *
 *  Created on: 31 июл. 2018 г.
 *      Author: wetfloor
 */

#include <Generator.hpp>

uint32_t Generator::instance = 0;

Generator::Generator(uint32_t amp, uint32_t freq)
	: amplification(amp), frequency(freq) {
	moduleType = ModuleType::GENERATOR;
	instance++;
};
