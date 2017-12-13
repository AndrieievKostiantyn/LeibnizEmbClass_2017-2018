/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "DL/drvRCC.h"
#include "DL/drvSysClock.h"
#include "DL/drvGPIO.h"
#include "DL/drvIWDG.h"
#include "DL/drvKeyboard.h"
#include "UL/ulRingBuffer.h"

void BSP_Init(void);

uint8_t lastEvent = noEvent;

int main(void) {
	BSP_Init();

	while(1) {
		drvIWDG_Run();
		drvKeyboard_Run();

		if (drv_Keyboard_getLastEvent(keyCentre) == isPressed) {
			drvGPIO_SetPin(drvGPIO_LED_G_2);
		} else {
			drvGPIO_ResetPin(drvGPIO_LED_G_2);
		}
	}
}

void BSP_Init(void) {
	drvRCC_Init();
	drvSysClock_Init();
	drvGPIO_Init();
	drvIWDG_Init();
}
