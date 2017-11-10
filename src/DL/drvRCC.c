/*
 *  drvRCC.c
 *
 *  Created on: November 11, 2017
 *  Author: Kostiantyn Andrieiev
 */

#include "drvRCC.h"
#include "stm32f4xx.h"

void drvRCC_Init(void){
	RCC_DeInit();
	RCC_PLLConfig(RCC_PLLSource_HSI, 8, 100, 2, 4);
	RCC_PLLCmd(ENABLE);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	FLASH_SetLatency(FLASH_Latency_3);
}


