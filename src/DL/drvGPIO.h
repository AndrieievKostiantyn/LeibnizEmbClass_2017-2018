/*
 *  drvGPIO.h
 *
 *  Created on: 10 November 2017
 *  Author: Kostiantyn Andrieiev
 */

#ifndef DRVGPIO_H_
#define DRVGPIO_H_

#include "stm32f4xx.h"

typedef enum{
	drvGPIO_List_Amount
}drvGPIO_List_t;


void drvGPIO_Init(void);
void drvGPIO_SetPin(drvGPIO_List_t pinName);
void drvGPIO_ResetPin(drvGPIO_List_t pinName);
uint8_t drvGPIO_ReadPin(drvGPIO_List_t pinName);

#endif /* DRVGPIO_H_ */
