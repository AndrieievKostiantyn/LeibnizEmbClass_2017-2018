/*
 * drvTrafficLight.h
 *
 *  Created on: 04.12.2017
 *      Author: kostiantyn_andreev
 */

#ifndef DL_DRVTRAFFICLIGHT_H_
#define DL_DRVTRAFFICLIGHT_H_

#include "stm32f4xx.h"

typedef enum {
	drvTrafficLight_States_STOP,
	drvTrafficLight_States_WAIT,
	drvTrafficLight_States_GO,
	drvTrafficLight_States_SERVICE,
	drvTrafficLight_States_DELAY
}drvTrafficLight_States_t;

typedef enum {
	drvTrafficLight_List_Auto_0,
	drvTrafficLight_List_Auto_1,
	drvTrafficLight_List_Pedestrian_2,
	drvTrafficLight_List_Amount
}drvTrafficLight_List;

void drvTrafficLight_Init(void);
void drvTrafficLight_Run(void);

#endif /* DL_DRVTRAFFICLIGHT_H_ */
