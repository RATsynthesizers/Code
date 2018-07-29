/*
 * Globals.hpp
 *
 *  Created on: 18 ���. 2018 �.
 *      Author: maro4_000
 */

#ifndef GLOBALS_HPP_
#define GLOBALS_HPP_

#include "stm32f4xx.h"
typedef uint32_t* uint32_t_ptr;
typedef const uint32_t* const_uint32_t_ptr;

enum GlobalParameters {
	DIGITS = 32, //For 32-bit processor
	BYTES = 4,
	SAMPLES_IN_BLOCK = 32
};

#endif /* GLOBALS_HPP_ */
