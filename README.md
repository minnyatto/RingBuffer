# RingBuffer
this is a RingBuffer Module for embed system

Author: minnyatto@gmail.com

why should we use ringbuffer: lets see whyuse.JPG file 

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
