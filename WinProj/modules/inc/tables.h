/*
 * tables.h
 *
 *  Created on: Oct 26, 2018
 *      Author: Roman
 */

#ifndef INC_TABLES_H_
#define INC_TABLES_H_

#include <stdint.h>

#define SIN_1000_SMP_SZ 1000

float sin_1000_smp[SIN_1000_SMP_SZ];

void packForCodec(float *flo_, uint32_t size_, uint16_t *outBuf_);

#endif /* INC_TABLES_H_ */
