/*
 * doorManagement.c
 *
 *  Created on: 4 sep. 2019
 *      Author: G5
 */
#include "gpio.h"

#define PIN_LED_GREEN PORTNUM2PIN(PE,26)

#define LED_ACTIVE      LOW

void doorInit(void)
{
	gpioMode (PIN_LED_GREEN, OUTPUT);
	closeDoor();
}
void openDoor(void)
{
	gpioWrite(PIN_LED_GREEN, LED_ACTIVE);
}
void closeDoor(void)
{
	gpioWrite(PIN_LED_GREEN, !LED_ACTIVE);
}

void toggleDoor(void)
{
	gpioToggle(PIN_LED_GREEN);
}


