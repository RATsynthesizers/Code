/*
 * Wire.cpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */

#include <Wire.hpp>

Wire::Wire(const Module& providerParam, Module& consumerParam)
	: consumer(consumerParam) {
	bufferNumber = consumer.getNumberOfNextFreeInputBuffer();
	if (bufferNumber < ::LINKS) {
		consumer.setInputBufferPointer(bufferNumber,
				providerParam.getOutputBufferPointer());
	};
};

Wire::Wire(const Module& providerParam, Module& consumerParam,
		uint32_t_ptr& inBufPtr_, uint32_t& bufCnt_) : consumer(consumerParam), bufferNumber(0) {
	if(bufCnt_ < ::LINKS) {
		*(inBufPtr_+ bufCnt_) = reinterpret_cast<uint32_t>(providerParam.getOutputBufferPointer());
	};




};

void Wire::unplug() {
	if (bufferNumber < ::LINKS) {
		consumer.setInputBufferPointer(bufferNumber, nullptr);
	};
	delete this;
};
