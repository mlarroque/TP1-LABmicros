/*
 * encoderLow.c
 *
 *  Created on: Sep 3, 2019
 *      Author: Lu
 */

#include "encoderHAL.h"
#include "timer.h"
#include "gpio.h"

#include "doorManagement.h"


/**************************************************************************
 * 									DEFINICIONES
 **************************************************************************/
#define SIGNAL_A_PIN PORTNUM2PIN(PD,3)// PTD3
#define SIGNAL_B_PIN PORTNUM2PIN(PD,1)// PTD1
#define SIGNAL_C_PIN PORTNUM2PIN(PD,2)// PTD2


#define ENCODER_TIME 	100000 		// 100 milisegundos


typedef void (*callback_t)(void);

/*******************************************************************************
 *								VARIABLES ESTATICAS
 *******************************************************************************/

static _Bool initialized_enc_low = false;
static uint8_t encoder_timer_count;

/*******************************************************************************
 *								FUNCIONES LOCALES
 *******************************************************************************/

void encTimerRoutine(void);

/*******************************************************************************
 *									FUNCIONES
 *******************************************************************************/

void initializeEncoderHAL(void)
{
	if(!initialized_enc_low)
	{
		gpioMode(SIGNAL_A_PIN, INPUT_PULLUP);
		setPassiveFilter(SIGNAL_A_PIN);
		gpioMode(SIGNAL_B_PIN, INPUT_PULLUP);
		setPassiveFilter(SIGNAL_B_PIN);
		gpioMode(SIGNAL_C_PIN, INPUT_PULLUP);
		setPassiveFilter(SIGNAL_C_PIN);
		encoder_timer_count = 0;
		InitializeTimers();
		SetTimer(ENCODER_TIMER, ENCODER_TIME, &encTimerRoutine);
		//EnableTimer(ENCODER_TIMER);
		initialized_enc_low = true;
	}
}


void encTimerRoutine(void)
{
	if(!gpioRead(SIGNAL_C_PIN))		//si el botón está presionado aumento el contador
		encoder_timer_count++;
}

void resetEncoderTimerCount(void)
{
	encoder_timer_count = 0;
}

_Bool readEncoderSignalX (encoder_signal signal)
{
	_Bool value;
	switch(signal)
	{
		case A:
			value = gpioRead(SIGNAL_A_PIN);
			break;
		case B:
			value = gpioRead(SIGNAL_B_PIN);
			break;
		case C:
			value = gpioRead(SIGNAL_C_PIN);
			break;
		default:
			break;
	}
	return value;
}

void setSignalCallback(void (*funcallback)(void), encoder_signal signal)
{
	switch (signal)
	{
		case A:
			gpioIRQ(SIGNAL_A_PIN, GPIO_IRQ_MODE_FALLING_EDGE, (pinIrqFun_t) funcallback);
			break;
		case B:
			gpioIRQ(SIGNAL_B_PIN, GPIO_IRQ_MODE_FALLING_EDGE, (pinIrqFun_t) funcallback);
			break;
		case C:
			gpioIRQ(SIGNAL_C_PIN, GPIO_IRQ_MODE_BOTH_EDGES, (pinIrqFun_t) funcallback);
			break;
		default:
			break;
	}
}

uint8_t getEncTimerCount(void)
{
	return encoder_timer_count;
}

