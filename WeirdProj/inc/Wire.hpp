/*
 * Wire.hpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */

#ifndef WIRE_HPP_
#define WIRE_HPP_

#include <Module.hpp>

class Wire {
public:
	Wire(const Module& src, Module& dst);
	~Wire();
private:
	Wire();
	Wire(const Wire& in);

	Module& dstModule;
	u32 bufferNumber;
};

#endif /* WIRE_HPP_ */
