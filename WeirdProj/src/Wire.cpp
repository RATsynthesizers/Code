/*
 * Wire.cpp
 *
 *  Created on: 29 июл. 2018 г.
 *      Author: wetfloor
 */

#include <Wire.hpp>

Wire::Wire(const Module& provider_, Module& consumer_,
		Parameter::ParameterName parameter) :
		consumer(consumer_) {
	uint8_t realParamNum;
	switch (consumer_.getModuleType()) {
		case Module::ModuleType::GENERATOR: {
			for (realParamNum = 0;realParamNum < sizeof(parameter) / sizeof(Parameter::ParameterName);
					realParamNum++) {
				if (parameter == dynamic_cast<Generator&>(consumer_).parameter[realParamNum].paramType)
					break;
				//dynamic_cast<Generator&>(consumer_).parameter[realParamNum]
			};
		};
	};
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
	/*if (bufferNumber < ::LINKS) {
	 consumer.setInputBufferPointer(bufferNumber, nullptr);
	 };
	 delete this;*/
}
;
