/*
 * ulRingBuffer.c
 *
 *  Created on: 21 мая 2016 г.
 *      Author: kostiantyn_andreev
 */

#include "ulRingBuffer.h"

// Method prototype. It configures indexes of a ring buffer
uint8_t ConfigureIndex(uint8_t index, uint8_t maxValue);

void ulRingBuffer_Create(ulRingBuffer_t *ringBuffer, string_t* ptrToBuffer, uint8_t size) {
	ringBuffer->ptrToBuffer = ptrToBuffer;
	ringBuffer->size = size;
	ringBuffer->bufferState = ulRingBuffer_Empty;
	ringBuffer->indexRead = 0;
	ringBuffer->indexWrite = 0;
	ringBuffer->fullness = 0;
}

void ulRingBuffer_PutToBuffer(ulRingBuffer_t *ringBuffer, string_t data) {
	if (ulRingBuffer_GetBufferState(ringBuffer) != ulRingBuffer_IsFull) {
		ringBuffer->ptrToBuffer[ringBuffer->indexWrite] = data;
		ringBuffer->indexWrite = ConfigureIndex(ringBuffer->indexWrite, ringBuffer->size);
		ringBuffer->fullness++;
	}
}

string_t ulRingBuffer_ReadFromBuffer(ulRingBuffer_t *ringBuffer) {
	char *bufferData = 0;

	if (ulRingBuffer_GetBufferState(ringBuffer) != ulRingBuffer_Empty) {
		bufferData = ringBuffer->ptrToBuffer[ringBuffer->indexRead];
		ringBuffer->indexRead = ConfigureIndex(ringBuffer->indexRead, ringBuffer->size);
		ringBuffer->fullness--;
	}

	return bufferData;
}

ulRingBuffer_states_t ulRingBuffer_GetBufferState(ulRingBuffer_t *ringBuffer) {
	if (ringBuffer->fullness == 0) {
		ringBuffer->bufferState = ulRingBuffer_Empty;
	} else if (ringBuffer->fullness >= ringBuffer->size) {
		ringBuffer->bufferState = ulRingBuffer_IsFull;
	} else {
		ringBuffer->bufferState = ulRingBuffer_HasData;
	}
	return ringBuffer->bufferState;
}

uint8_t ConfigureIndex(uint8_t index, uint8_t maxValue) {
	if (index < maxValue) {
		index++;
	}
	if (index == maxValue) {
		index = 0;
	}
	return index;
}
