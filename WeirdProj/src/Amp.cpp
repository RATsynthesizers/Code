/*
 * Amp.cpp
 *
 *  Created on: 31 авг. 2018 г.
 *      Author: wetfloor
 */

#include <Amp.hpp>

uint32_t Amp::instance = 0;

Amp::Amp(uint32_t amp_) {
	moduleType = ModuleType::AMPLIFIER;
	instance++;

	amp = amp_;
	ampBufferCounter = 0;
	for(uint32_t i = 0; i < ::LINKS;
		inputBufferPointer[i] = nullptr, i++);

};

uint32_t Amp::getInstance() {
	return instance;
};

void Amp::process() {
	for(uint32_t buf_cnt =0; buf_cnt < SAMPLES_IN_BLOCK; buf_cnt++) {
	outputBuffer[buf_cnt] = (amp + *(ampBufferPointer + buf_cnt) * (*(inputBufferPointer[0] + buf_cnt));
	}
};

