/*
 * doorManagement.c
 *
 *  Created on: 4 sep. 2019
 *      Author: G5
 */
#include "doorManagement.h"
#include "gpio.h"
#include "timer.h"
#include <stdint.h>

#define PIN_LED_GREEN PORTNUM2PIN(PE,26)

#define LED_ACTIVE      LOW

void closeAfterTimeOut(void);

void doorInit(void)
{
	gpioMode (PIN_LED_GREEN, OUTPUT);
	closeDoor();
	InitializeTimers();

}

void openDoorTemporally(){
	uint32_t timeOut = TIME_OUT_DOOR;
	openDoor();
	SetTimer(DOOR, timeOut, closeAfterTimeOut);
}

void closeAfterTimeOut(void){
	closeDoor();
	DisableTimer(DOOR);
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


