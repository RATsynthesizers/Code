/*
 * Heap.hpp
 *
 *  Created on: 19 ���. 2018 �.
 *      Author: maro4_000
 */

#ifndef HEAP_HPP_
#define HEAP_HPP_

#include <Globals.hpp>
#include "stm32f4xx.h"

class Heap {
public:
	enum class Error {
		NO_ERROR = 0, INVALID_SIZE = 1, SIZE_TOO_LARGE = 2, CELLS_ALREADY_RELEASED = 3,
		NOT_ENOUGH_HEAP_CELLS = 4, INVALID_POINTER = 5
	};

	Heap();

	//Use these methods carefully
	//pointerToReservedCells is output parameter, sizeInCells is input parameter
	Error reserveHeapCells(uint32_t_ptr& pointerToReservedCells, const uint32_t& sizeInCells);
	Error releaseAllHeapCells();
	//pointerToReservedCells is input parameter, sizeInCells is input parameter
	Error releaseHeapCells(const uint32_t_ptr& pointerToReservedCells, const uint32_t& sizeInCells);
private:
	Heap(const Heap& in);

	//Heap size is ::BYTES * HEAP_CELL_COUNT bytes
	enum class HeapParam {
		HEAP_CELL_COUNT = 512
	};

	uint32_t heapArea[static_cast<uint32_t>(HeapParam::HEAP_CELL_COUNT)];
	uint32_t heapBitMap[(static_cast<uint32_t>(HeapParam::HEAP_CELL_COUNT) - 1) / ::DIGITS + 1];
};

#endif /* HEAP_HPP_ */
