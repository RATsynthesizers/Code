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

void Wire::unplug() {
	consumer.setInputBufferPointer(bufferNumber, nullptr);
	delete this;
};
