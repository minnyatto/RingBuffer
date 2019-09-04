/*
	Author: minnyatto@gmail.com
	
	how to use:
	
		1. Declare RingBuff, RingData like follow example
				
				typedef struct
				{
					int16_t 	ItemNum;
					char		ItemData[64];
					int16_t		ItemCount;
				} myRingData_t;
				
				
				RingBuff_t 		myRingBuffer;
				myRingData_t	myRingData[32];
				
		2. Create RingBuffer
		
				RingBuffer_Create(&myRingBuffer, 
								&myRingData[0], 
								sizeof(myRingData[0]), 
								sizeof(myRingData)/sizeof(myRingData[0]));
				
		3. Use
			
			myRingData_t itemData;
			
			ret = RingBuffer_Get(&myRingBuffer, (void *)&itemData);
			
			ret = RingBuffer_Set(&myRingBuffer, (void *)&itemData);	

			//When you want to know there is new data in RingBuffer or not but you dont
			want to get the new data, use follow function and see the return value
			
			ret = RingBuffer_CheckNewData(&myRingBuffer);
*/

#include "RingBuffer.h"

RingBuff_Return_e RingBuffer_Create(RingBuff_t *ring, void *ringdata, uint16_t itemSize, uint16_t ringSize)
{
	if (ring->State != RINGBUFFER_STATE_NULL)
	{
		return RINGBUFFER_CREATED;
	}
	
	ring->RingData = ringdata;
	ring->ItemSize = itemSize;
	ring->RingSize = ringSize;
	ring->State	   = RINGBUFFER_STATE_NORMAL;

	return RINGBUFFER_OK;
}

RingBuff_Return_e RingBuffer_Reset(RingBuff_t *ring)
{
	if (ring->State == RINGBUFFER_STATE_NULL)
	{
		return RINGBUFFER_NG;
	}
	
	ring->ReadIdx = 0;
	ring->WriteIdx = 0;
	ring->State	   = RINGBUFFER_STATE_NORMAL;

	return RINGBUFFER_OK;
}

RingBuff_Return_e RingBuffer_Get(RingBuff_t *ring, void *res)
{
	if (ring->State != RINGBUFFER_STATE_NORMAL)
	{
		return RINGBUFFER_NG;
	}
	
	RingBuff_Return_e ret = RINGBUFFER_NODATA;

	if (ring->ReadIdx != ring->WriteIdx)
	{
		memcpy((char *)res,(const char*)(ring->RingData + (ring->ReadIdx)*(ring->ItemSize)), (size_t)(ring->ItemSize));
		ring->ReadIdx = ring->ReadIdx + 1;
		if (ring->ReadIdx >= ring->RingSize)
		{
			ring->ReadIdx = 0;
		}
		ret = RINGBUFFER_NEWDATA;
	}

	return ret;
}

RingBuff_Return_e RingBuffer_Set(RingBuff_t *ring, const void *data)
{
	if (ring->State != RINGBUFFER_STATE_NORMAL)
	{
		return RINGBUFFER_NG;
	}
	
	memcpy((char *)(ring->RingData + (ring->WriteIdx)*(ring->ItemSize)), ( const char *)data, (size_t)(ring->ItemSize));
	ring->WriteIdx = ring->WriteIdx + 1;
	if (ring->WriteIdx >= ring->RingSize)
	{
		ring->WriteIdx = 0;
	}
	return RINGBUFFER_OK;
}

RingBuff_Return_e RingBuffer_SetReadBack(RingBuff_t *ring, uint8_t NumOfIdx)
{
	if (ring->State != RINGBUFFER_STATE_NORMAL)
	{
		return RINGBUFFER_NG;
	}
	
	if (ring->ReadIdx < NumOfIdx)
	{
		ring->ReadIdx = ring->RingSize - NumOfIdx + ring->ReadIdx ;
	}
	else
	{
		ring->ReadIdx = ring->ReadIdx - NumOfIdx;
	}

	return RINGBUFFER_OK;
}

RingBuff_Return_e RingBuffer_CheckNewData(RingBuff_t *ring)
{
	if (ring->State != RINGBUFFER_STATE_NORMAL)
	{
		return RINGBUFFER_NG;
	}
	
	if (ring->ReadIdx != ring->WriteIdx)
	{
		return RINGBUFFER_NEWDATA;
	}
	else
	{
		return RINGBUFFER_NODATA;
	}
}
