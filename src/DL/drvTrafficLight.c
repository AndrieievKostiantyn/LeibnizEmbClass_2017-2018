/*

 * drvTrafficLight.c
 *
 *  Created on: 04.12.2017
 *      Author: kostiantyn_andreev


#include "drvTrafficLight.h"
#include "drvSysClock.h"
#include "drvGPIO.h"

typedef enum {
	drvTrafficLight_Type_AUTO,
	drvTrafficLight_Type_PEDESTRIAN
}drvTrafficLight_Type_t;

typedef struct {
	drvTrafficLight_Type_t type;
	uint32_t lastTime;
	drvTrafficLight_States_t currentState;
	drvTrafficLight_States_t lastState;
	drvGPIO_List_t lightSTOP;
	drvGPIO_List_t lightWAIT;
	drvGPIO_List_t lightGO;
}drvTrafficLight_t;

drvTrafficLight_t drvTrafficLight[drvTrafficLight_List_Amount] = {
		{drvTrafficLight_Type_AUTO, 0, drvTrafficLight_States_STOP, drvTrafficLight_States_STOP, drvGPIO_LED_R_0, drvGPIO_LED_Y_0, drvGPIO_LED_G_0},
		{drvTrafficLight_Type_AUTO, 0, drvTrafficLight_States_GO, drvTrafficLight_States_GO, drvGPIO_LED_R_1, drvGPIO_LED_Y_1, drvGPIO_LED_G_1},
		{drvTrafficLight_Type_PEDESTRIAN, 0, drvTrafficLight_States_GO, drvTrafficLight_States_GO, drvGPIO_LED_R_2, drvGPIO_LED_R_2, drvGPIO_LED_G_2}
};

void drvTrafficLight_StateMachine(drvTrafficLight_List TrafficLight_Name);

void drvTrafficLight_Run(void) {
	drvTrafficLight_List currentTrafficLight = drvTrafficLight_List_Auto_0;

	for (currentTrafficLight = drvTrafficLight_List_Auto_0;
			currentTrafficLight < drvTrafficLight_List_Amount;
			currentTrafficLight++) {
		drvTrafficLight_StateMachine(currentTrafficLight);
	}
}

void drvTrafficLight_StateMachine(drvTrafficLight_List TrafficLight_Name) {
	switch(drvTrafficLight[TrafficLight_Name].currentState) {
		case drvTrafficLight_States_STOP:
			drvGPIO_ResetPin(drvTrafficLight[TrafficLight_Name].lightGO);
			drvGPIO_SetPin(drvTrafficLight[TrafficLight_Name].lightSTOP);
			drvTrafficLight[TrafficLight_Name].lastTime = drvSysClock_GetTime();
			drvTrafficLight[TrafficLight_Name].currentState = drvTrafficLight_States_DELAY;
			drvTrafficLight[TrafficLight_Name].lastState = drvTrafficLight_States_STOP;
		break;

		case drvTrafficLight_States_WAIT:
			drvTrafficLight[TrafficLight_Name].lastTime = drvSysClock_GetTime();

			if (drvTrafficLight[TrafficLight_Name].type == drvTrafficLight_Type_PEDESTRIAN) {
				drvGPIO_SetPin(drvTrafficLight[TrafficLight_Name].lightWAIT);
			} else {
				drvGPIO_SetPin(drvTrafficLight[TrafficLight_Name].lightWAIT);
			}

			drvTrafficLight[TrafficLight_Name].currentState = drvTrafficLight_States_DELAY;
			drvTrafficLight[TrafficLight_Name].lastState = drvTrafficLight_States_WAIT;
		break;

		case drvTrafficLight_States_GO:
			drvTrafficLight[TrafficLight_Name].lastTime = drvSysClock_GetTime();

			if (drvTrafficLight[TrafficLight_Name].type == drvTrafficLight_Type_PEDESTRIAN) {
				drvGPIO_ResetPin(drvTrafficLight[TrafficLight_Name].lightSTOP);
				drvGPIO_SetPin(drvTrafficLight[TrafficLight_Name].lightGO);
			} else {
				drvGPIO_ResetPin(drvTrafficLight[TrafficLight_Name].lightSTOP);
				drvGPIO_ResetPin(drvTrafficLight[TrafficLight_Name].lightWAIT);
				drvGPIO_SetPin(drvTrafficLight[TrafficLight_Name].lightGO);
			}

			drvTrafficLight[TrafficLight_Name].currentState = drvTrafficLight_States_DELAY;
			drvTrafficLight[TrafficLight_Name].lastState = drvTrafficLight_States_GO;
		break;

		case drvTrafficLight_States_SERVICE:

		break;

		case drvTrafficLight_States_DELAY:
			if (drvSysClock_isTimeSpent(drvTrafficLight[TrafficLight_Name].lastTime, 5000)) {
				if (drvTrafficLight[TrafficLight_Name].lastState == drvTrafficLight_States_STOP) {
					drvTrafficLight[TrafficLight_Name].currentState = drvTrafficLight_States_WAIT;
				} else if (drvTrafficLight[TrafficLight_Name].lastState == drvTrafficLight_States_WAIT) {
					drvTrafficLight[TrafficLight_Name].currentState = drvTrafficLight_States_GO;
				} else if (drvTrafficLight[TrafficLight_Name].lastState == drvTrafficLight_States_GO) {
					drvTrafficLight[TrafficLight_Name].currentState = drvTrafficLight_States_STOP;
				}

				drvTrafficLight[TrafficLight_Name].lastState = drvTrafficLight_States_DELAY;
			}
		break;
	}
}
*/
