/*
 * drvKeyboard.c
 *
 *  Created on: 25 Apr 2016
 *      Author: kostiantyn_andreev
 */

#include "drvKeyboard.h"
#include "drvSysClock.h"
#include "drvGPIO.h"

#define HOLD_TIME_DEFAULT 2000
#define KEY_COUNTER_MIN 2
#define KEY_COUNTER_MAX 100
#define KEY_COUNTER_PRESSED 90
#define KEY_COUNTER_RELEASED 30

/*
 * The driver controls the keyboard plugged in the MCU.
 * It is based on counter that identifies the the type of press.
 * There are two directions of a counter: from down to up and from up to down. If key's state is 'not pressed',
 * counter counts from down to up, as long as it is 'pressed' the direction of the counter changes.
 * There are some values for the counter to reach.
 *
 * */

typedef enum {
	low, high
} drvKeyboard_activeState;

/* *
 * Describes buttons' configuration.
 * WARNING: do not change it as it may lead to the driver crash!
 * */
typedef struct {
	drvKeyboard_keyList_t keyName;
	drvKeyboard_activeState activeState;
	drvKeyboard_keyEvent_t currentState;
	uint8_t counter;
	uint32_t saveTime;
	uint32_t holdTime;
	drvKeyboard_keyEvent_t lastEvent;
	drvGPIO_List_t gpioKeyName;
} drvKeyboard_confTable;

/* *
 * Change this to configure all the necessary buttons.
 * By default, this block configured for 3 buttons being released and having a low active state.
 * */
drvKeyboard_confTable keyboard[keyAmount] = {
		{ keyLeft, low, isReleased, KEY_COUNTER_MIN, 0, HOLD_TIME_DEFAULT, 0, drvGPIO_Button_0 },
		{ keyCentre, low, isReleased, KEY_COUNTER_MIN, 0, HOLD_TIME_DEFAULT, 0, drvGPIO_Button_1 },
		{ keyRight, low, isReleased, KEY_COUNTER_MIN, 0, HOLD_TIME_DEFAULT, 0, drvGPIO_Button_2 } };

/* To prevent contact bounce */
static void contactBounceElimination(uint32_t keyName);

drvKeyboard_keyEvent_t newKeyState = 0;

/* *
 * @brief		runs the counter to eliminate the contact bounce;
 * 				sets the button state, depending on a counter value.
 * @retval		last event of a button, e.g. isPressed, isHeld etc.
 * @note		use this method to run the keyboard driver
 * */
void drvKeyboard_Run(void) {
	uint32_t keyName = 0;

	for (keyName = keyLeft; keyName < keyAmount; keyName++) {
		newKeyState = keyboard[keyName].currentState;

		contactBounceElimination(keyName);

		switch (keyboard[keyName].currentState) {
		case isReleased:
			if (keyboard[keyName].counter > KEY_COUNTER_PRESSED) {
				newKeyState = isPressed;
				keyboard[keyName].lastEvent = isPressed;
				keyboard[keyName].saveTime = drvSysClock_GetTime();
			}
			break;

		case isPressed:
			if (keyboard[keyName].counter < KEY_COUNTER_RELEASED) {
				newKeyState = isReleased;
				keyboard[keyName].lastEvent = isReleased;
			} else if (drvSysClock_isTimeSpent(keyboard[keyName].saveTime, keyboard[keyName].holdTime)) {
				keyboard[keyName].saveTime = drvSysClock_GetTime();
				keyboard[keyName].lastEvent = isHeld;
			}
			break;

		default:
			keyboard[keyName].counter = KEY_COUNTER_MIN;
			keyboard[keyName].currentState = isReleased;
		}
		keyboard[keyName].currentState = newKeyState;
	}
}

drvKeyboard_keyEvent_t drv_Keyboard_getLastEvent(drvKeyboard_keyList_t keyName) {
	drvKeyboard_keyEvent_t event = 0;

	event = keyboard[keyName].lastEvent;

	return event;
}

void drvKeyboard_setHoldTime(drvKeyboard_keyList_t keyName,
		uint32_t newHoldTime) {
	keyboard[keyName].holdTime = newHoldTime;
}

/* *
 * @brief	Reads the state of a pin to which a button is connected.
 * 			If the pin state is the same as button active state -> count up,
 * 			If it is different -> count down.
 * */
void contactBounceElimination(uint32_t keyName) {
	drvKeyboard_activeState keyState = 0;

	if (drvGPIO_ReadPin(keyboard[keyName].gpioKeyName) == 1) {
		keyState = high;
	} else {
		keyState = low;
	}

	if (keyState == keyboard[keyName].activeState) {
		keyboard[keyName].counter++;
	} else {
		keyboard[keyName].counter--;
	}

	if (keyboard[keyName].counter > KEY_COUNTER_MAX) {
		keyboard[keyName].counter = KEY_COUNTER_MAX;
	}

	if (keyboard[keyName].counter < KEY_COUNTER_MIN) {
		keyboard[keyName].counter = KEY_COUNTER_MIN;
	}
}
