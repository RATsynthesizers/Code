/*
 * Wire.cpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */

#include <Wire.hpp>

Wire::Wire(Module& source_, Module& destination_,
		Parameter::ParameterName parameter_) :
		provider(&source_), consumer(&destination_), bufferNumber(0) {

	plug(parameter_);
	source_.connectedWires++;
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

/*Wire::Wire(const Module& providerParam, Module& consumerParam, )
 : consumer(consumerParam) {
 bufferNumber = consumer.getNumberOfNextFreeInputBuffer();
 if (bufferNumber < ::LINKS) {
 consumer.setInputBufferPointer(bufferNumber,
 providerParam.getOutputBufferPointer());
 };
 };*/

void Wire::unplug() {
	dynamic_cast<Generator&>(*consumer).parameter[realParamNum].bitmap &= ~(1
			<< bufferNumber);
	provider->connectedWires--;
	/*if (bufferNumber < ::LINKS) {
	 consumer.setInputBufferPointer(bufferNumber, nullptr);
	 };
	 delete this;*/
};

void Wire::replugConsumer(Module& consumer_,
		Parameter::ParameterName parameter_) {
	dynamic_cast<Generator&>(*consumer).parameter[realParamNum].bitmap &= ~(1
			<< bufferNumber);
	consumer = &consumer_;
	plug(parameter_);
};

void Wire::replugProvider(Module& provider_) {
	provider->connectedWires--;
	provider = &provider_;
	provider->connectedWires++;
	switch (consumer->getModuleType()) {
	case Module::ModuleType::GENERATOR: {
		dynamic_cast<Generator&>(*consumer).parameter[realParamNum].inputBufferPointer[bufferNumber] =
				provider->getOutputBufferPointer();

		};
	};
};

void Wire::plug(Parameter::ParameterName parameter_) {
	switch (consumer->getModuleType()) {
		case Module::ModuleType::GENERATOR: {
			for (realParamNum = 0;
					realParamNum
							< sizeof(Generator::parameter)
									/ sizeof(Parameter::ParameterName);
					realParamNum++) {
				if (parameter_
						== dynamic_cast<Generator&>(*consumer).parameter[realParamNum].paramType) {
					uint32_t shiftingValue =
							dynamic_cast<Generator&>(*consumer).parameter[realParamNum].bitmap;
					uint32_t socketNumber = 0;

					while (shiftingValue & 1) {
						shiftingValue >>= 1;
						socketNumber++;
					};

					dynamic_cast<Generator&>(*consumer).parameter[realParamNum].inputBufferPointer[socketNumber] =
							provider->getOutputBufferPointer();

					dynamic_cast<Generator&>(*consumer).parameter[realParamNum].bitmap |=
							(1 << socketNumber);

					bufferNumber = socketNumber;
					break;
				};
				//dynamic_cast<Generator&>(consumer_).parameter[realParamNum]
			};
		}
			;
		};
};
