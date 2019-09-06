/*
 * encoderLow.c
 *
 *  Created on: Sep 3, 2019
 *      Author: Lu
 */

#include "encoderHAL.h"
#include "timer.h"
#include "gpio.h"


/**************************************************************************
 * 									DEFINICIONES
 **************************************************************************/
#define SIGNAL_A_PIN PORTNUM2PIN(PD,2)// PTD1
#define SIGNAL_B_PIN PORTNUM2PIN(PD,3)// PTD3
#define SIGNAL_C_PIN PORTNUM2PIN(PD,1)// PTD2


#define ENCODER_TIME 	200000 		// 200 milisegundos


typedef void (*callback_t)(void);

/*******************************************************************************
 *								VARIABLES ESTATICAS
 *******************************************************************************/

static bool initialized_enc_low = false;
static uint8_t encoder_timer_count = 0;

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
		gpioMode(SIGNAL_B_PIN, INPUT_PULLUP);
		gpioMode(SIGNAL_C_PIN, INPUT_PULLUP);
		SetTimer(ENCODER_TIMER, ENCODER_TIME, encTimerRoutine);
		DisableTimer(ENCODER_TIMER);		//lo inicializo sólo cuando se presiona el enter

		initialized_enc_low = true;
	}
}


void encTimerRoutine(void)
{
	if(gpioRead(SIGNAL_C_PIN))		//si el botón está presionado aumento el contador
		encoder_timer_count++;
}

void resetEncoderTimerCount(void)
{
	encoder_timer_count = 0;
}

bool readEncoderSignalX (encoder_signal signal)
{
	bool lecture;
	if(signal == A)
		lecture = gpioRead(SIGNAL_A_PIN);
	else if (signal == B)
		lecture = gpioRead(SIGNAL_B_PIN);
	else if (signal == C)
		lecture = gpioRead(SIGNAL_C_PIN);
	else
		lecture = false;
	return lecture;
}

void setSignalCallback(void (*funcallback)(void), encoder_signal signal)
{
	switch (signal)
	{
		case A:
			gpioIRQ(SIGNAL_A_PIN, GPIO_IRQ_MODE_BOTH_EDGES, (pinIrqFun_t) funcallback);
			break;
		case B:
			gpioIRQ(SIGNAL_B_PIN, GPIO_IRQ_MODE_BOTH_EDGES, (pinIrqFun_t) funcallback);
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

