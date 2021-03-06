/*
 * Wire.cpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */

#include <Wire.hpp>

Wire::Wire(Module& src_, Module& dst_, Parameter::ParamName param_) :
		source(&src_), destination(&dst_), paramSocket(0) {

	plug(param_);             // plug when wire is created ??
	src_.connectedWires++;    // new wire is connected to the output buffer


	// shit
	/*uint32_t realParamNum;
	 switch (consumer_.getModuleType()) {
	 case Module::ModuleType::GENERATOR: {
	 for (realParamNum = 0;
	 realParamNum
	 < sizeof(Generator::parameter)
	 / sizeof(Parameter::ParameterName);
	 realParamNum++) {
	 if (parameter_
	 == dynamic_cast<Generator&>(consumer_).parameter[realParamNum].paramType) {
	 uint32_t shiftingValue =
	 dynamic_cast<Generator&>(consumer_).parameter[realParamNum].bitmap;
	 uint32_t socketNumber = 0;

	 while (shiftingValue & 1) {
	 shiftingValue >>= 1;
	 socketNumber++;
	 };

	 dynamic_cast<Generator&>(consumer_).parameter[realParamNum].inputBufferPointer[socketNumber] =
	 provider_.getOutputBufferPointer();

	 dynamic_cast<Generator&>(consumer_).parameter[realParamNum].bitmap |=
	 (1 << socketNumber);

	 bufferNumber = socketNumber;
	 break;
	 };
	 //dynamic_cast<Generator&>(consumer_).parameter[realParamNum]
	 };
	 }
	 ;
	 };*/
};

// shit
/*Wire::Wire(const Module& providerParam, Module& consumerParam, )
 : consumer(consumerParam) {
 bufferNumber = consumer.getNumberOfNextFreeInputBuffer();
 if (bufferNumber < ::LINKS) {
 consumer.setInputBufferPointer(paramSocketNumber,
 providerParam.getOutputBufferPointer());
 };
 };*/

void Wire::unplug() {
	dynamic_cast<Generator&>(*destination).prm[paramIndex].socketbit &= ~(1 << paramSocket);   // ?M  // this parameter's socket is now free
	source->connectedWires--;                                 // source module looses 1 output wire

	//shit
	/*if (bufferNumber < ::SOCKETS) {
	 consumer.setInputBufferPointer(paramSocketNumber, nullptr);
	 };
	 delete this;*/
};

void Wire::replugConsumer(Module& dst_, Parameter::ParamName param_) {
	dynamic_cast<Generator&>(*destination).prm[paramIndex].socketbit &= ~(1 << paramSocket);   // ?M  // this parameter's socket is now free
	destination = &dst_;                                     // update destination module
	plug(param_);                                            // plug wire to new parameter in new detination module
};

void Wire::replugProvider(Module& src_) {
	source->connectedWires--;                                // source module looses 1 output wire
	source = &src_;                                          // update source module
	source->connectedWires++;                                // new wire is connected to output buffer in new source module
	switch (destination->getModuleType()) {       // depending on the destination module type, connect new source's outBuf to destination's parameter's socket
	case Module::ModuleType::GENERATOR: {                                       // ?M
		dynamic_cast<Generator&>(*destination).prm[paramIndex].iBptr[paramSocket] =
				source->getOutputBufferPointer();

	};
	};
};

void Wire::plug(Parameter::ParamName param_) {
	switch (destination->getModuleType()) {
	case Module::ModuleType::GENERATOR: {
		for (paramIndex = 0;                       // find parameter with required type in destianation's array of parameters
				paramIndex
						< sizeof(Generator::prm) / sizeof(Parameter::ParamName);
				paramIndex++) {
			if (param_
					== dynamic_cast<Generator&>(*destination).prm[paramIndex].paramType) {
				uint32_t shiftingValue =           // get parameters socket bit mask
						dynamic_cast<Generator&>(*destination).prm[paramIndex].socketbit;
				uint32_t socketNumber_tmp = 0;

				while (shiftingValue & 1) {       // shift that mask and find the number of the first zero bit
					shiftingValue >>= 1;
					socketNumber_tmp++;           //  the number of the first zero bit
				};

				dynamic_cast<Generator&>(*destination).prm[paramIndex].iBptr[socketNumber_tmp] =
						source->getOutputBufferPointer();   // connect source to this ^ parameter's socket

				dynamic_cast<Generator&>(*destination).prm[paramIndex].socketbit |=
						(1 << socketNumber_tmp);  // now this socket is busy, update bit mask

				paramSocket = socketNumber_tmp;   // wire is now connected to this socket
				break;
			};

		};
	};
	};
};
