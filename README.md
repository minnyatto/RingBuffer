# RingBuffer
this is a RingBuffer Module for embedded system

Author: minnyatto@gmail.com

****why should we use ringbuffer: 
	lets see whyuse.JPG file 
	
	In Embedded System, we have some kinds of communication as SPI, I2C, USB, USART,...
	when data receive from these communications, receiving speed is higher than data processing speed
	so we need to keep or store received data to some where and process it later
	this is why we need a buffer. But in Embedded system, memory is small size and not enough for creating a large buffer
	we need reuse  last buffer slot, and we call this is a ring buffer
	for example:
		I have a buffer with 64 item size:   myRing[64];
		I put received data in each item of myRing and process it one by one
		when one data was processed, I reuse the item which stored the data
		by using this mechanism, the ringbuffer item index will be running cyclically
		and can save memory

****how to use:
	
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
