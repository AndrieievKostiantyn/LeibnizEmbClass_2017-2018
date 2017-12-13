/*
 *  drvGPIO.c
 *
 *  Created on: 10 November 2017
 *  Author: Kostiantyn Andrieiev
 */

#include "drvGPIO.h"

typedef enum {
	PORT_A,
	PORT_B,
	PORT_C,
} drvGPIO_PORT_t;

typedef struct {
	drvGPIO_PORT_t PORT;
	uint16_t PIN;
} drvGPIO_ConfigTable_t;

drvGPIO_ConfigTable_t drvGPIO_ConfigTable[drvGPIO_List_Amount]={
		{PORT_C, 3},
		{PORT_C, 1},
		{PORT_C, 0},
		{PORT_C, 12},
		{PORT_B, 9},
		{PORT_C, 10}
};

void drvGPIO_Init(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef GPIO_LED_InitStruct;
	GPIO_InitTypeDef GPIO_ButtonInitStruct_B;
	GPIO_InitTypeDef GPIO_ButtonInitStruct_C;

	GPIO_LED_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_LED_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3;
	GPIO_LED_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_LED_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_LED_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;

	GPIO_Init(GPIOC, &GPIO_LED_InitStruct);
	GPIO_ResetBits(GPIOC, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3);

	GPIO_ButtonInitStruct_B.GPIO_Mode = GPIO_Mode_IN;
	GPIO_ButtonInitStruct_B.GPIO_Pin = GPIO_Pin_9;
	GPIO_ButtonInitStruct_B.GPIO_OType = GPIO_OType_PP;
	GPIO_ButtonInitStruct_B.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_ButtonInitStruct_B.GPIO_Speed = GPIO_Speed_25MHz;

	GPIO_Init(GPIOB, &GPIO_ButtonInitStruct_B);
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);

	GPIO_ButtonInitStruct_C.GPIO_Mode = GPIO_Mode_IN;
	GPIO_ButtonInitStruct_C.GPIO_Pin = GPIO_Pin_9;
	GPIO_ButtonInitStruct_C.GPIO_OType = GPIO_OType_PP;
	GPIO_ButtonInitStruct_C.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_ButtonInitStruct_C.GPIO_Speed = GPIO_Speed_25MHz;

	GPIO_Init(GPIOC, &GPIO_ButtonInitStruct_C);
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);
}

void drvGPIO_SetPin(drvGPIO_List_t pinName) {
	switch (drvGPIO_ConfigTable[pinName].PORT) {
	case PORT_A:
		GPIO_SetBits(GPIOA, 1 << drvGPIO_ConfigTable[pinName].PIN);
		break;
	case PORT_B:
		GPIO_SetBits(GPIOB, 1 << drvGPIO_ConfigTable[pinName].PIN);
		break;
	case PORT_C:
		GPIO_SetBits(GPIOC, 1 << drvGPIO_ConfigTable[pinName].PIN);
		break;
	}
}

void drvGPIO_ResetPin(drvGPIO_List_t pinName) {
	switch (drvGPIO_ConfigTable[pinName].PORT) {
		case PORT_A:
			GPIO_ResetBits(GPIOA, 1 << drvGPIO_ConfigTable[pinName].PIN);
			break;
		case PORT_B:
			GPIO_ResetBits(GPIOB, 1 << drvGPIO_ConfigTable[pinName].PIN);
			break;
		case PORT_C:
			GPIO_ResetBits(GPIOC, 1 << drvGPIO_ConfigTable[pinName].PIN);
			break;
	}
}

uint8_t drvGPIO_ReadPin(drvGPIO_List_t pinName) {
	uint8_t returnValue = 0;

	switch (drvGPIO_ConfigTable[pinName].PORT) {
		case PORT_A:
			returnValue = GPIO_ReadInputDataBit(GPIOA, 1 << drvGPIO_ConfigTable[pinName].PIN);
			break;
		case PORT_B:
			returnValue = GPIO_ReadInputDataBit(GPIOB, 1 << drvGPIO_ConfigTable[pinName].PIN);
			break;
		case PORT_C:
			returnValue = GPIO_ReadInputDataBit(GPIOC, 1 << drvGPIO_ConfigTable[pinName].PIN);
			break;
	}

	return returnValue;
}
