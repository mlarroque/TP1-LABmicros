/*
 * encoderDRV.c
 *
 *  Created on: Sep 3, 2019
 *      Author: Lu
 */

#include "encoderLow.h"
#include "timer.h"
#include "gpio.h"


/**************************************************************************
 * 									DEFINICIONES
 **************************************************************************/
#define SIGNAL_A PORTNUM2PIN(PC,3)// PTC3
#define SIGNAL_B PORTNUM2PIN(PC,2)// PTC2
#define SIGNALC PORTNUM2PIN(PA,2)// PTA2

/*******************************************************************************
 *								VARIABLES ESTATICAS
 *******************************************************************************/
static bool initialized_enc_low = false;


/*******************************************************************************
 *									FUNCIONES
 *******************************************************************************/
void initializeEncoderLow(void)
{
	if(!initialized_enc_low)
	{
		gpioMode(SIGNAL_A, INPUT_PULLDOWN);
		gpioMode(SIGNAL_B, INPUT_PULLDOWN);
		gpioMode(SIGNAL_C, INPUT_PULLDOWN);

		initialized_enc_low = true;
	}
}


