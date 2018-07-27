/*
 * MemBlocks.h
 *
 *  Created on: 16 ���. 2018 �.
 *      Author: maro4_000
 */

#ifndef MEMBLOCKS_HPP_
#define MEMBLOCKS_HPP_

#include <Globals.hpp>
#include "stm32f4xx.h"

class MemBlocks {
public:
	enum class MemBlocksParam {
		SAMPLES_IN_BLOCK = 32, MEM_BLOCK_COUNT = 16
	};

	enum class Error {
		NO_ERROR = 0, ALL_BLOCKS_ARE_RESERVED = 1, BLOCK_ALREADY_RELEASED = 2, INVALID_BLOCK_NUMBER = 3
	};

	MemBlocks();

	//Returns number of next reserved block and error code
	Error reserveNextBlock(uint32_t& numberOfNextReservedBlock);

	//Returns error code
	Error releaseBlock(const uint32_t& blockNumber);

	//Returns address of chosen block and error code
	//To get address of memBlocksArray blockNumber must be equal 0
	Error getBlockAddress(const uint32_t& blockNumber, uint32_t_ptr& blockAddress);
private:
	//Don't even try to call this ctor
	MemBlocks(const MemBlocks& in);

	uint32_t memBlocksArray[static_cast<uint32_t>(MemBlocksParam::SAMPLES_IN_BLOCK)
			* static_cast<uint32_t>(MemBlocksParam::MEM_BLOCK_COUNT)];

	uint32_t memBitMap[(static_cast<uint32_t>(MemBlocksParam::MEM_BLOCK_COUNT) - 1) / ::DIGITS + 1];
};



#endif /* MEMBLOCKS_HPP_ */
