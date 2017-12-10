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
		{PORT_A, 5},
		{PORT_C, 13},
		{PORT_A, 0},
		{PORT_A, 1},
		{PORT_A, 4},
		{PORT_B, 5},
		{PORT_B, 6},
		{PORT_B, 7},
		{PORT_B, 8},
		{PORT_B, 10}
};

void drvGPIO_Init(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitTypeDef GPIO_ButtonInitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;

	GPIO_ButtonInitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_ButtonInitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_ButtonInitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_ButtonInitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_ButtonInitStruct.GPIO_Speed = GPIO_Speed_25MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_Init(GPIOC, &GPIO_ButtonInitStruct);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4);


	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_10;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;

	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_ResetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_10);

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
