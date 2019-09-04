#include "RingBuffer.h"



void RingBuffer_Create(RingBuff_t *ring, void *ringdata, uint16_t itemSize, uint16_t ringSize)
{
	ring->RingData = ringdata;
	ring->ItemSize = itemSize;
	ring->RingSize = ringSize;
	
}

void RingBuffer_Reset(RingBuff_t *ring)
{
	ring->ItemSize = 0;
	ring->RingSize = 0;
}

uint16_t RingBuffer_Get(RingBuff_t *ring, void *res)
{
	uint16_t ret = 0;
	if (ring->ReadIdx != ring->WriteIdx)
	{
		memcpy((char *)res,(const char*)(ring->RingData + (ring->ReadIdx)*(ring->ItemSize)), (size_t)(ring->ItemSize));
		ring->ReadIdx = ring->ReadIdx + 1;
		if (ring->ReadIdx >= ring->RingSize)
		{
			ring->ReadIdx = 0;
		}
		ret = 1;
	}

	return ret;
}

uint16_t RingBuffer_Set(RingBuff_t *ring, const void *data)
{
	memcpy((char *)(ring->RingData + (ring->WriteIdx)*(ring->ItemSize)), ( const char *)data, (size_t)(ring->ItemSize));
	ring->WriteIdx = ring->WriteIdx + 1;
	if (ring->WriteIdx >= ring->RingSize)
	{
		ring->WriteIdx = 0;
	}
	return 1;
}

void RingBuffer_SetReadBack(RingBuff_t *ring, uint8_t NumOfIdx)
{
	if (ring->ReadIdx < NumOfIdx)
	{
		ring->ReadIdx = ring->RingSize - NumOfIdx + ring->ReadIdx ;
	}
	else
	{
		ring->ReadIdx = ring->ReadIdx - NumOfIdx;
	}
}

uint8_t RingBuffer_CheckNewData(RingBuff_t *ring)
{
	if (ring->ReadIdx != ring->WriteIdx)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
