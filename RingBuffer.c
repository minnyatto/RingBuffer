/*
	Author: minnyatto@gmail.com
	
	how to use:
	
		1. Declare RingBuff, RingData, UserID like follow example
				
				typedef struct
				{
					int16_t 	ItemNum;
					char		ItemData[64];
					int16_t		ItemCount;
				} myRingData_t;
				
				
				RingBuff_t 		myRingBuffer;
				myRingData_t	myRingData[32];
				
				int8_t		UserID1			
				int8_t		UserID2
				//ReadIdx of UserID1 and UserID2 is Different
				
		2. Create RingBuffer
		
				RingBuffer_Create(&myRingBuffer, 
								&myRingData[0], 
								sizeof(myRingData[0]), 
								sizeof(myRingData)/sizeof(myRingData[0]));
		3. Add User
				
				RingBuffer_AddUser(&myRingBuffer, &UserID1);
				RingBuffer_AddUser(&myRingBuffer, &UserID2);
				
		3. Use
			
			**********Read Data
			myRingData_t itemData1;
			myRingData_t itemData2;
			ret1 = RingBuffer_Get(UserID1, &myRingBuffer, (void *)&itemData1);
			ret2 = RingBuffer_Get(UserID2, &myRingBuffer, (void *)&itemData2);
			
			**********Write Data
			* Write Process can not be from multi user, so this process dont need User ID
			myRingData_t newitemData;
			ret = RingBuffer_Set(&myRingBuffer, (void *)&newitemData);	


			//When you want to know there is new data in RingBuffer or not but you dont
			want to get the new data, use follow function and see the return value
			
			ret = RingBuffer_CheckNewData(&myRingBuffer);
*/

#include "RingBuffer.h"

RingBuff_Return_e RingBuffer_Create(RingBuff_t *ring, void *ringdata, uint16_t itemSize, uint16_t ringSize)
{
	if (ring->RingState != RINGBUFFER_STATE_NULL)
	{
		return RINGBUFFER_NG;
	}
	ring->RingData = ringdata;
	ring->ItemSize = itemSize;
	ring->RingSize = ringSize;


	ring->UserCount = 0;

	ring->RingState = RINGBUFFER_STATE_NORMAL;

	return RINGBUFFER_OK;
}

/*
 * use for multi user want to access one ringbuffer. Each user will have an UserID and ReadIdx[userID] unique
 *
 *
 */
RingBuff_Return_e RingBuffer_AddUser(RingBuff_t *ring, int8_t *userID)
{
	if (ring->UserCount == MULTI_USER_MAX)
	{
		*userID = -1;
		return RINGBUFFER_NG;		//Can not add user any more
	}
	*userID = ring->UserCount;
	ring->UserCount = ring->UserCount + 1;	//One user added
	ring->UserState[*userID] = RINGBUFFER_STATE_NORMAL;
	return RINGBUFFER_OK;
}


RingBuff_Return_e RingBuffer_ResetUser(uint8_t userID, RingBuff_t *ring)
{
	if (ring->UserState[userID] == RINGBUFFER_STATE_NULL)
	{
		return RINGBUFFER_NG;
	}

	ring->ReadIdx[userID] 		= ring->WriteIdx;
	ring->UserState[userID]   	= RINGBUFFER_STATE_NORMAL;

	return RINGBUFFER_OK;
}


RingBuff_Return_e RingBuffer_Get(uint8_t userID, RingBuff_t *ring, void *res)
{
	if (ring->UserState[userID] != RINGBUFFER_STATE_NORMAL)
	{
		return RINGBUFFER_NG;
	}
	
	RingBuff_Return_e ret = RINGBUFFER_NODATA;

	if (ring->ReadIdx[userID] != ring->WriteIdx)
	{
		memcpy((char *)res,(const char*)(ring->RingData + (ring->ReadIdx[userID])*(ring->ItemSize)), (size_t)(ring->ItemSize));
		ring->ReadIdx[userID] = ring->ReadIdx[userID] + 1;
		if (ring->ReadIdx[userID] >= ring->RingSize)
		{
			ring->ReadIdx[userID] = 0;
		}
		ret = RINGBUFFER_NEWDATA;
	}

	return ret;
}

RingBuff_Return_e RingBuffer_Set(RingBuff_t *ring, const void *data)
{

	if (ring->RingState != RINGBUFFER_STATE_NORMAL)
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

RingBuff_Return_e RingBuffer_SetReadBack(uint8_t userID, RingBuff_t *ring, uint8_t NumOfIdx)
{
	if (ring->UserState[userID] != RINGBUFFER_STATE_NORMAL)
	{
		return RINGBUFFER_NG;
	}
	
	if (ring->ReadIdx[userID] < NumOfIdx)
	{
		ring->ReadIdx[userID] = ring->RingSize - NumOfIdx + ring->ReadIdx[userID] ;
	}
	else
	{
		ring->ReadIdx[userID] = ring->ReadIdx[userID] - NumOfIdx;
	}

	return RINGBUFFER_OK;
}

RingBuff_Return_e RingBuffer_CheckNewData(uint8_t userID, RingBuff_t *ring)
{
	if (ring->UserState[userID] != RINGBUFFER_STATE_NORMAL)
	{
		return RINGBUFFER_NG;
	}
	
	if (ring->ReadIdx[userID] != ring->WriteIdx)
	{
		return RINGBUFFER_NEWDATA;
	}
	else
	{
		return RINGBUFFER_NODATA;
	}
}
