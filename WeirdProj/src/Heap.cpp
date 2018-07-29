/*
 * Heap.cpp
 *
 *  Created on: 19 ���. 2018 �.
 *      Author: maro4_000
 */

#include <Heap.hpp>

Heap::Heap() {
	for (uint32_t i = 0; i < (static_cast<uint32_t>(HeapParam::HEAP_CELL_COUNT) - 1) / ::DIGITS + 1;
			heapBitMap[i] = 0, i++);

	for (uint32_t i = 0; i < static_cast<uint32_t>(HeapParam::HEAP_CELL_COUNT);
			heapArea[i] = 0, i++);
};

Heap::Error Heap::releaseAllHeapCells() {
	for (uint32_t i = 0; i < (static_cast<uint32_t>(HeapParam::HEAP_CELL_COUNT) - 1) / ::DIGITS + 1;
			heapBitMap[i] = 0, i++);

	for (uint32_t i = 0; i < static_cast<uint32_t>(HeapParam::HEAP_CELL_COUNT);
			heapArea[i] = 0, i++);

	return Error::NO_ERROR;
};

Heap::Error Heap::reserveHeapCells(uint32_t_ptr& pointerToReservedCells, const uint32_t& sizeInCells) {
	if(!sizeInCells)
		return Error::INVALID_SIZE;

	if(sizeInCells > static_cast<uint32_t>(HeapParam::HEAP_CELL_COUNT))
		return Error::SIZE_TOO_LARGE;

	uint32_t_ptr base = heapArea;
	uint32_t cellCounter = 0;
	uint32_t cellsToReserve[(static_cast<uint32_t>(HeapParam::HEAP_CELL_COUNT) - 1) / ::DIGITS + 1];

	for (uint32_t i = 0; i < (static_cast<uint32_t>(HeapParam::HEAP_CELL_COUNT) - 1) / ::DIGITS + 1;
		cellsToReserve[i] = 0, i++);

	for (uint32_t i = 0; i < (static_cast<uint32_t>(HeapParam::HEAP_CELL_COUNT) - 1) / ::DIGITS + 1; i++) {
		uint32_t shiftingValue = heapBitMap[i];
		uint32_t bitNumberInShiftingValue = 0;

		while (bitNumberInShiftingValue < ::DIGITS) {
			while (shiftingValue & 1) {
				for (uint32_t j = 0; j < (static_cast<uint32_t>(HeapParam::HEAP_CELL_COUNT) - 1) / ::DIGITS + 1;
					cellsToReserve[j] = 0, j++);

				cellCounter = 0;
				shiftingValue >>= 1;
				bitNumberInShiftingValue++;
			};

			while (!(shiftingValue & 1) && (bitNumberInShiftingValue < ::DIGITS)) {
				if (!cellCounter)
					base = heapArea + (i * ::DIGITS + bitNumberInShiftingValue);

				cellsToReserve[i] |= (1 << bitNumberInShiftingValue);
				cellCounter++;
				shiftingValue >>= 1;
				bitNumberInShiftingValue++;

				if (cellCounter == sizeInCells) {
					for (uint32_t j = 0; j < (static_cast<uint32_t>(HeapParam::HEAP_CELL_COUNT) - 1) / ::DIGITS + 1;
						heapBitMap[j] |= cellsToReserve[j], j++);

					pointerToReservedCells = base;
					return Error::NO_ERROR;
				};
			};
		};
	};
	return Error::NOT_ENOUGH_HEAP_CELLS;
};

Heap::Error Heap::releaseHeapCells(const uint32_t_ptr& pointerToReservedCells, const uint32_t& sizeInCells) {
	if (!sizeInCells)
		return Error::INVALID_SIZE;

	if (!pointerToReservedCells)
		return Error::INVALID_POINTER;

	if (sizeInCells > static_cast<uint32_t>(HeapParam::HEAP_CELL_COUNT))
		return Error::SIZE_TOO_LARGE;

	uint32_t offset = reinterpret_cast<uint32_t>(pointerToReservedCells) - reinterpret_cast<uint32_t>(heapArea);
	//Imitate uint32_t_ptr
	offset /= ::BYTES;
	uint32_t bitMapIndex = offset / static_cast<uint32_t>(::DIGITS);
	uint32_t bitNumber = offset - bitMapIndex * static_cast<uint32_t>(::DIGITS);

	if(!(heapBitMap[bitMapIndex] & (1 << bitNumber))) {
		return Error::CELLS_ALREADY_RELEASED;
	};

	uint32_t cellCounter = 1;
	for(uint32_t i = bitMapIndex; i < (static_cast<uint32_t>(HeapParam::HEAP_CELL_COUNT) - 1) / ::DIGITS + 1; i++) {
		uint32_t shiftingValue = heapBitMap[i] >> bitNumber;
		while (bitNumber < ::DIGITS) {
			if (!shiftingValue) {
				return Error::CELLS_ALREADY_RELEASED;
			};

			heapBitMap[i] &= ~(1 << bitNumber);
			if (cellCounter == sizeInCells) {
				//Release cells
				return Error::NO_ERROR;
			};

			cellCounter++;
			bitNumber++;
			shiftingValue >>= 1;
		};

		bitNumber = 0;
	};
	return Error::SIZE_TOO_LARGE;
};
