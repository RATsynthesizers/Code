/*
 * Generator.cpp
 *
 *  Created on: 31 июл. 2018 г.
 *      Author: wetfloor
 */

#include <Generator.hpp>

uint32_t Generator::instance = 0;
//const uint32_t Generator::numberOfParameters = 4;

Generator::Generator(const uint32_t& amp, const uint32_t& freq,
		const uint32_t& offst)
	/*: amplification(amp), frequency(freq), offset(offst), wavePhase(0) */{
	moduleType = ModuleType::GENERATOR;

	parameter[0].paramType= Parameter::ParameterName::FREQUENCY;
	parameter[1].paramType= Parameter::ParameterName::AMPLIFICATION;
	parameter[2].paramType= Parameter::ParameterName::OFFSET;
	parameter[3].paramType= Parameter::ParameterName::WAVEFORM;

	for(uint32_t i = 0; i < static_cast<uint32_t>(Params::Number); i++) {
		parameter[i].bitmap = 0;
		parameter[i].value = 0;

		for(uint32_t j = 0; j < ::LINKS; parameter[i].inputBufferPointer[j] = nullptr, j++);
	};

	instance++;
};

/*uint32_t Generator::getAmplification() const {
	return amplification;
};

void Generator::setAmplification(const uint32_t& amp) {
	amplification = amp;
};*/

/*uint32_t Generator::getFrequency() const {
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
};*/

uint32_t Generator::getInstance() {
	return instance;
};

void Generator::process() {
	/*for(uint32_t buf_cnt = 0; buf_cnt < ::SAMPLES_IN_BLOCK; buf_cnt++) {
		if(wavePhase == frequency)
			wavePhase = 0;

		if(wavePhase < frequency/2)
			outputBuffer[buf_cnt] = amplification;
		 else
			outputBuffer[buf_cnt] = 0;
		wavePhase++;
	};*/
//	wave_cnt;
//for(buf_cnt = 0; buf_cnt < BSZ; buf_cnt++) {
//	if(wave_cnt == smpInPer) {
//		wave_cnt = 0;
//	}
//	buf[buf_cnt] = calculate(wave_cnt)
// wave_cnt++;
//}   дима

};
