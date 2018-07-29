/*
 * SinGenerator.cpp
 *
 *  Created on: 16 ���. 2018 �.
 *      Author: maro4_000
 */

#include <SinGenerator.hpp>

SinGenerator::SinGenerator(const uint32_t& smpInPeriod, const uint32_t& amp,
		const MemBlocks& memManag, Heap& hp) :
		samplesInPeriod(smpInPeriod), amplification(amp), blocksQueue(nullptr),
		numberOfCellsInLastBlock(0), memBlocks(memManag), heap(hp) {};

uint32_t SinGenerator::getSamplesInPeriod() {
	return samplesInPeriod;
};

SinGenerator::Error SinGenerator::setSamplesInPeriod(const uint32_t& smpInPeriod) {
	samplesInPeriod = smpInPeriod;
	return Error::NO_ERROR;
};

uint32_t SinGenerator::getAmplification() {
	return amplification;
};

SinGenerator::Error SinGenerator::setAmplification(const uint32_t& amp) {
	amplification = amp;
	return Error::NO_ERROR;
};

SinGenerator::Error SinGenerator::getNumberOfCellsInLastBlock(uint32_t& NumberOfCells) {
	NumberOfCells = numberOfCellsInLastBlock;
	return Error::NO_ERROR;
};

SinGenerator::Error SinGenerator::getCurrentBlockAddress(uint32_t_ptr& currentBlockAddress) {
	if (!blocksQueue)
		return Error::EMPTY_QUEUE;

	if(const_cast<MemBlocks&>(memBlocks).getBlockAddress(blocksQueue->numberOfCurrentBlock, currentBlockAddress) == MemBlocks::Error::INVALID_BLOCK_NUMBER) {
		return Error::INVALID_QUEUE_VALUE;
	};
	return Error::NO_ERROR;
};

SinGenerator::Error SinGenerator::releaseCurrentBlock() {
	if (!blocksQueue)
		return Error::EMPTY_QUEUE;

	const_cast<MemBlocks&>(memBlocks).releaseBlock(blocksQueue->numberOfCurrentBlock);
	QueueBlocks *blockToDelete = blocksQueue;
	blocksQueue = blocksQueue->nextBlock;
	heap.releaseHeapCells(reinterpret_cast<uint32_t_ptr>(blockToDelete), sizeof(QueueBlocks) / ::BYTES);
	return Error::NO_ERROR;
};

SinGenerator::Error SinGenerator::generate() {
	/*uint32_t blocks = samplesInPeriod / static_cast<uint32_t>(MemBlocks::MemBlocksParam::SAMPLES_IN_BLOCK);
	numberOfCellsInLastBlock = samplesInPeriod -
			blocks * static_cast<uint32_t>(MemBlocks::MemBlocksParam::SAMPLES_IN_BLOCK);
	uint32_t_ptr currentBufferPointer = nullptr;
	memBlocks.getBlockAddress(0, currentBufferPointer);

	for(uint32_t i = 0; i < (blocks + (numberOfCellsInLastBlock != 0)); i++) {
		//Each SAMPLES_IN_BLOCK reserve new memory block
		if(!(i & (static_cast<uint32_t>(MemBlocks::MemBlocksParam::SAMPLES_IN_BLOCK) - 1))) {
			QueueBlocks *lastBlock = nullptr;
			if(!blocksQueue) {
				while (heap.reserveHeapCells(reinterpret_cast<uint32_t_ptr>(blocksQueue),
						sizeof(QueueBlocks) / ::BYTES) != Heap::Error::NO_ERROR) {};
				//blocksQueue = new QueueBlocks;
				lastBlock = blocksQueue;
			}
			else {
				lastBlock = blocksQueue;

				while(lastBlock->nextBlock) {
					lastBlock = lastBlock->nextBlock;
				};

				while (heap.reserveHeapCells(reinterpret_cast<uint32_t_ptr>(lastBlock->nextBlock),
						sizeof(QueueBlocks) / ::BYTES) != Heap::Error::NO_ERROR) {};
				//lastBlock->nextBlock = new QueueBlocks;
				lastBlock = lastBlock->nextBlock;
			};

			lastBlock->nextBlock = nullptr;
			while (memBlocks.reserveNextBlock(lastBlock->numberOfCurrentBlock)
					!= MemBlocks::Error::NO_ERROR) {};
			memBlocks.getBlockAddress(lastBlock->numberOfCurrentBlock, currentBufferPointer);

			if (i < blocks) {
				for (uint32_t j = 0; j < static_cast<uint32_t>(MemBlocks::MemBlocksParam::SAMPLES_IN_BLOCK);
						currentBufferPointer++, j++) {
					sin(j + i * static_cast<uint32_t>(MemBlocks::MemBlocksParam::SAMPLES_IN_BLOCK),
							currentBufferPointer);
				};
			} else {
				for (uint32_t j = 0; j < numberOfCellsInLastBlock; currentBufferPointer++, j++) {
					sin(j + i * static_cast<uint32_t>(MemBlocks::MemBlocksParam::SAMPLES_IN_BLOCK),
							currentBufferPointer);
				};
			};
		};
	};*/

	return Error::NO_ERROR;
};

void SinGenerator::sin(const uint32_t& position, const uint32_t_ptr bufferPointer) {
	//float arg = position * (2 * PI / samplesInPeriod);
};
