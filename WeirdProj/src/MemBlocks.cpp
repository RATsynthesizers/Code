/*
 * MemBlocks.cpp
 *
 *  Created on: 16 ���. 2018 �.
 *      Author: maro4_000
 */

#include <MemBlocks.hpp>
#include "stm32f4xx.h"

MemBlocks::MemBlocks() {
	for (uint32_t i = 0; i < (static_cast<uint32_t>(MemBlocksParam::MEM_BLOCK_COUNT) - 1) / ::DIGITS + 1;
			memBitMap[i] = 0, i++);

	for (uint32_t i = 0; i < static_cast<uint32_t>(MemBlocksParam::SAMPLES_IN_BLOCK)
			* static_cast<uint32_t>(MemBlocksParam::MEM_BLOCK_COUNT); memBlocksArray[i] = 0, i++);
};

//Returns number of next reserved block and error code
MemBlocks::Error MemBlocks::reserveNextBlock(uint32_t& numberOfNextReservedBlock) {
	uint32_t blockNumber = 0;
	for (uint32_t i = 0; i < (static_cast<uint32_t>(MemBlocksParam::MEM_BLOCK_COUNT) - 1) / ::DIGITS + 1; i++) {
		uint32_t shiftingValue = memBitMap[i];
		uint32_t bitNumberInShiftingValue = 0;

		while (shiftingValue & 1) {
			shiftingValue >>= 1;
			blockNumber++;
			bitNumberInShiftingValue++;
		};

		if ((i * ::DIGITS + bitNumberInShiftingValue) >= static_cast<uint32_t>(MemBlocksParam::MEM_BLOCK_COUNT)) {
			return Error::ALL_BLOCKS_ARE_RESERVED;
		};

		if (bitNumberInShiftingValue < ::DIGITS) {
			memBitMap[i] |= (1 << bitNumberInShiftingValue);
			numberOfNextReservedBlock = blockNumber;
			return Error::NO_ERROR;
		};
	};

	return Error::ALL_BLOCKS_ARE_RESERVED;
};

//Returns error code
MemBlocks::Error MemBlocks::releaseBlock(const uint32_t& blockNumber) {
	if (blockNumber >= static_cast<uint32_t>(MemBlocksParam::MEM_BLOCK_COUNT)) {
		return Error::INVALID_BLOCK_NUMBER;
	};

	uint32_t indexInBitMap = blockNumber / ::DIGITS;
	if (!(memBitMap[indexInBitMap] & (1 << (blockNumber - indexInBitMap * ::DIGITS)))) {
		return Error::BLOCK_ALREADY_RELEASED;
	};

	memBitMap[blockNumber / ::DIGITS] &= ~(1 << (blockNumber - indexInBitMap * ::DIGITS));
	return Error::NO_ERROR;
};

//Returns address of chosen block and error code
MemBlocks::Error MemBlocks::getBlockAddress(const uint32_t& blockNumber, uint32_t_ptr& blockAddress) {
	if(blockNumber > static_cast<uint32_t>(MemBlocks::MemBlocksParam::MEM_BLOCK_COUNT)) {
		return Error::INVALID_BLOCK_NUMBER;
	};

	//Block address is baseOffset + blockNumber * SAMPLES_IN_BLOCK * ::BYTES
	blockAddress = memBlocksArray
			+ blockNumber * static_cast<uint32_t>(MemBlocksParam::SAMPLES_IN_BLOCK);
	return Error::NO_ERROR;
};
