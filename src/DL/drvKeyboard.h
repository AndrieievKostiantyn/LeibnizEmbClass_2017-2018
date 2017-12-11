/*
 * drvKeyboard.h
 *
 *  Created on: 25 Apr 2016
 *      Author: kostiantyn_andreev
 */

#ifndef DRVKEYBOARD_H_
#define DRVKEYBOARD_H_

#include "stm32f4xx.h"

typedef enum {
	keyLeft,
	keyCentre,
	keyRight,
	keyAmount
}drvKeyboard_keyList_t;

typedef enum {
	noEvent,
	isPressed,
	isReleased,
	isHeld
}drvKeyboard_keyEvent_t;

void drvKeyboard_Init(void);

void drvKeyboard_Run(void);

void drvKeyboard_setHoldTime(drvKeyboard_keyList_t keyName, uint32_t newHoldTime);

drvKeyboard_keyEvent_t drv_Keyboard_getLastEvent(drvKeyboard_keyList_t keyName);

void keyPressed_Handler(drvKeyboard_keyList_t keyName);

void keyReleased_Handler(drvKeyboard_keyList_t keyName);

void keyHeld_Handler(drvKeyboard_keyList_t keyName);

#endif /* DRVKEYBOARD_H_ */
