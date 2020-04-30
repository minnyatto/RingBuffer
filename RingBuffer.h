/*
	Author: minnyatto@gmail.com
*/


#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>


#define MULTI_USER_MAX	10

typedef enum
{
	RINGBUFFER_STATE_NULL,
	RINGBUFFER_STATE_NORMAL,
	RINGBUFFER_STATE_ERROR,
} RingBuff_State_e;

typedef enum
{
	RINGBUFFER_NODATA,
	RINGBUFFER_NEWDATA,
	RINGBUFFER_OK,
	RINGBUFFER_NG,
	RINGBUFFER_CREATED,
	
} RingBuff_Return_e;
	

typedef struct
{
	void     				*RingData;
	uint16_t 				ItemSize;
	uint16_t 				RingSize;
	uint16_t 				ReadIdx[MULTI_USER_MAX];
	uint16_t 				WriteIdx;
	RingBuff_State_e		UserState[MULTI_USER_MAX];
	uint8_t					UserCount;
	RingBuff_State_e		RingState;
	
} RingBuff_t;

RingBuff_Return_e 	RingBuffer_Create(RingBuff_t *ring, void *ringdata, uint16_t itemSize, uint16_t ringSize);
RingBuff_Return_e 	RingBuffer_AddUser(RingBuff_t *ring, int8_t *userID);
RingBuff_Return_e 	RingBuffer_ResetUser(uint8_t userID, RingBuff_t *ring);
RingBuff_Return_e 	RingBuffer_Get(uint8_t userID, RingBuff_t *ring, void *res);
RingBuff_Return_e 	RingBuffer_Set(RingBuff_t *ring, const void *data);
RingBuff_Return_e 	RingBuffer_SetReadBack(uint8_t userID, RingBuff_t *ring, uint8_t NumOfIdx);
RingBuff_Return_e 	RingBuffer_CheckNewData(uint8_t userID, RingBuff_t *ring);

#endif
