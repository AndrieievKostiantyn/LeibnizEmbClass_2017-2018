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
#include "DL/drvTrafficLight.h"
#include "DL/drvIWDG.h"

void BSP_Init(void);

int main(void) {
	BSP_Init();


	while(1) {
		drvIWDG_Run();
		drvTrafficLight_Run();
	}

}

void BSP_Init(void) {
	drvRCC_Init();
	drvSysClock_Init();
	drvGPIO_Init();
	drvIWDG_Init();
}
