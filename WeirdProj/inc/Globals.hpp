/*
 * Globals.hpp
 *
 *  Created on: 18 ���. 2018 �.
 *      Author: maro4_000
 */

#ifndef GLOBALS_HPP_
#define GLOBALS_HPP_

#include "stm32f4xx.h"
#include "DWT.h"       // for speed measurements

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u32_ptr = uint32_t*;
using c_u32_ptr = const uint32_t*;

enum GlobalParameters {
	DIGITS = 32,    //For 32-bit processor ??
	BYTES = 4,      // ??
	BLOCKSIZE = 32, // block size in blocks
	SOCKETS = 16    // max inputs for 1 parameter
//MAX_OBSZ = 4      // max output buffer size in blocks
};

#endif /* GLOBALS_HPP_ */
