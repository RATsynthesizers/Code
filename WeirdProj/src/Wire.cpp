/*
 * Wire.cpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */

#include <Wire.hpp>

Wire::Wire(const Module& src, Module& dst)
	: dstModule(dst) {
	bufferNumber = dstModule.getNumberOfNextFreeInputBuffer();
	if (bufferNumber < ::LINKS) {
		dstModule.setInputBufferPointer(bufferNumber,
				src.getOutputBufferPointer());
	};
};

Wire::~Wire() {
	dstModule.setInputBufferPointer(bufferNumber, nullptr);
};
