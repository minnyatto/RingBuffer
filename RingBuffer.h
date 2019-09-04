#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
	void     *RingData;
	uint16_t ItemSize;
	uint16_t RingSize;
	uint16_t ReadIdx;
	uint16_t WriteIdx;
	
} RingBuff_t;

void RingBuffer_Create(RingBuff_t *ring, void *ringdata, uint16_t itemSize, uint16_t ringSize);
uint16_t RingBuffer_Get(RingBuff_t *ring, void *res);
uint16_t RingBuffer_Set(RingBuff_t *ring, const void *data);
void RingBuffer_SetReadBack(RingBuff_t *ring, uint8_t NumOfIdx);
uint8_t RingBuffer_CheckNewData(RingBuff_t *ring);

#endif
