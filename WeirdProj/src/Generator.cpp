/*
 * Generator.cpp
 *
 *  Created on: 31 июл. 2018 г.
 *      Author: wetfloor
 */

#include <Generator.hpp>

uint32_t Generator::instance = 0;

Generator::Generator(const uint32_t& amp, const uint32_t& freq,
		const uint32_t& offst)
	: amplification(amp), frequency(freq), offset(offst) {
	moduleType = ModuleType::GENERATOR;
	instance++;
};

uint32_t Generator::getAmplification() const {
	return amplification;
};

void Generator::setAmplification(const uint32_t& amp) {
	amplification = amp;
};

uint32_t Generator::getFrequency() const {
	return frequency;
};

void Generator::setFrequency(uint32_t freq) {
	frequency = freq;
};

uint32_t Generator::getOffset() const {
	return offset;
};

void Generator::setOffset(const uint32_t& offst) {
	offset = offst;
};

uint32_t Generator::getInstance() {
	return instance;
};
