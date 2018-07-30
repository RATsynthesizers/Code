/*
 * Wire.cpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */

#include <Wire.hpp>

Wire::Wire(const Module& src, Module& dst)
	: dstModule(dst) {
	dstModule.setInputBufferPointer(
			src.getOutputBufferPointer());
};

Wire::~Wire() {
	dstModule.setInputBufferPointer(nullptr);
};
