/*
 * SinGenerator.h
 *
 *  Created on: 16 ���. 2018 �.
 *      Author: maro4_000
 */

#ifndef SINGENERATOR_HPP_
#define SINGENERATOR_HPP_

#include <Globals.hpp>
#include <MemBlocks.hpp>
#include <Heap.hpp>
#include "stm32f4xx.h"

class SinGenerator {
public:
	enum class Error {
		NO_ERROR = 0, INVALID_PARAM_VALUE = 1, EMPTY_QUEUE = 2,
		INVALID_QUEUE_VALUE = 3
	};

	SinGenerator(const uint32_t& smpInPeriod, const uint32_t& amp, const MemBlocks& memManag, Heap& hp);

	inline uint32_t getSamplesInPeriod();
	inline Error setSamplesInPeriod(const uint32_t& smpInPeriod);

	inline uint32_t getAmplification();
	inline Error setAmplification(const uint32_t& amp);

	Error generate();
	Error getCurrentBlockAddress(uint32_t_ptr& currentBlockAddress);
	Error releaseCurrentBlock();

	inline Error getNumberOfCellsInLastBlock(uint32_t& NumberOfCells);
private:
	SinGenerator();
	SinGenerator(const SinGenerator& in);

	struct QueueBlocks {
		uint32_t numberOfCurrentBlock;
		QueueBlocks *nextBlock;
	};

	//Input parameters
	uint32_t samplesInPeriod;
	uint32_t amplification;

	//Internal fields
	QueueBlocks *blocksQueue;
	uint32_t numberOfCellsInLastBlock;
	const MemBlocks& memBlocks;
	Heap& heap;

	inline void sin(const uint32_t& position, const uint32_t_ptr bufferPointer);
};

#endif /* SINGENERATOR_HPP_ */
