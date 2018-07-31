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
	Generator(const uint32_t& amp, const uint32_t& freq, const uint32_t& offst);

	uint32_t getAmplification() const;
	void setAmplification(const uint32_t& amp);

	uint32_t getFrequency() const;
	void setFrequency(uint32_t freq);

	uint32_t getOffset() const;
	void setOffset(const uint32_t& offst);

	static uint32_t getInstance();
private:
	Generator();
	Generator(const Generator& in);

	static uint32_t instance;

	uint32_t amplification;
	uint32_t frequency;

	uint32_t offset;
};

#endif /* GENERATOR_HPP_ */
