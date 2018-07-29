/*
 * Wire.cpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */

#include <Wire.hpp>

Wire::Wire(const Module& providerParam, Module& consumerParam)
	: consumer(consumerParam) {
	consumer.setInputBufferPointer(
			providerParam.getOutputBufferPointer());
};

Wire::~Wire() {
	consumer.setInputBufferPointer(nullptr);
};
