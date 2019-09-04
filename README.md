# RingBuffer
this is a RingBuffer Module for embedded system

Author: minnyatto@gmail.com

****why should we use ringbuffer: 
	![](https://lh3.googleusercontent.com/2w2oZUR9L8fsSxBuPZV8MiiHNyrLHFBnXT59_LzMK2bq-AJ2CK6Hdtrx_eqVWNrlr6mP--Hxr_ouraxlgddwJLhxekj6PXFwcJyQ6LDvhHp_uDc6MuKA4yqnSLOWSM3t43Nc_cRTbHeQVSGasS08BihMw87m49GShPWq1wgTHi6RyAkvzqb2606bUEBaZFhOJ8qVlyHtltnAh0kbcFs8yMH46voDAD7Uga2_HWmIPszl-WFhrflESIAQ3COnE5yho7hWWta2Uy5AGCWZ8173z4JSKa8pNvLJwQXwiKFo_QGd3N5F5VRqWQfnpyWOkyXjUm-zbpq8424xhyAcss2afB8h7ym1RlEJwtRNB2AZUzbtl7giVSYh2Z85ZDTuBF3xyWFVJHBnyNuIFHO1aDy0etREBqvWlIDrZ35OopXM9095syU7bRWVGrn-NDO7b4v6vIXXteN4BJJ9HV2OWLXvHM9gf2rdfTKnHoPWjR7pJ_SewhVdovgby8xlztyFzIZsc9HdrwoJV5DnxvjcJ5eDKaDP0RK_JjRs0m1rS3wv58tzfXlOYp8GlxSsOSkyHe6dbw_Y2mbxCNbZ-iTC4_KTOmo32riNLCX9p0tYYpqKwdVnkbpkrgE2pEyFQY81lKC-uwvSL8_yw1TLmYhmAC9qg-FZwvP_eIfvhhuUBM0xUEpRg8jTBPN0T4NER2bq1GIK8ShekOXuKAy0nCOr_yAEbPGZ9kAtmStWMwQqg5avm0GqS0E=w1209-h685-no)
	
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
