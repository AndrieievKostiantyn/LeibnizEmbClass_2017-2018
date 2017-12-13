/*
 * ulRingBuffer.h
 *
 *  Created on: 21 мая 2016 г.
 *      Author: kostiantyn_andreev
 */

#ifndef ULRINGBUFFER_H_
#define ULRINGBUFFER_H_

#include "stm32f4xx.h"

typedef char* string_t;

typedef enum {
	ulRingBuffer_Empty,
	ulRingBuffer_HasData,
	ulRingBuffer_IsFull
}ulRingBuffer_states_t;

typedef struct {
	string_t* ptrToBuffer;
	uint8_t size;
	ulRingBuffer_states_t bufferState;
	uint8_t indexWrite;
	uint8_t indexRead;
	uint8_t fullness;
}ulRingBuffer_t;

void ulRingBuffer_Create(ulRingBuffer_t* ringBuffer, string_t* ptrToBuffer, uint8_t size);

void ulRingBuffer_PutToBuffer(ulRingBuffer_t* ringBuffer, string_t data);

string_t ulRingBuffer_ReadFromBuffer(ulRingBuffer_t* ringBuffer);

ulRingBuffer_states_t ulRingBuffer_GetBufferState(ulRingBuffer_t* ringBuffer);

#endif /* ULRINGBUFFER_H_ */
