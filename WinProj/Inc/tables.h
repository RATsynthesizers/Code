/*
 * tables.h
 *
 *  Created on: Oct 26, 2018
 *      Author: Roman
 */


// temporary file for test sin generation
#ifndef INC_TABLES_H_
#define INC_TABLES_H_

#include <stdint.h>

#define SIN_1000_SMP_SZ 100

float sin_1000_smp[SIN_1000_SMP_SZ];

void prepareSin(uint16_t outBuf[200]);
uint16_t* packForCodec(float *flo, uint32_t size);

#endif /* INC_TABLES_H_ */
