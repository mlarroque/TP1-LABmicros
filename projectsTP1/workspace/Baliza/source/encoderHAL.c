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
#define SIGNAL_A_PIN PORTNUM2PIN(PC,3)// PTC3
#define SIGNAL_B_PIN PORTNUM2PIN(PC,2)// PTC2
#define SIGNAL_C_PIN PORTNUM2PIN(PA,2)// PTA2


#define ENCODER_TIME 	500000 		// 0.5 segundos


typedef void (*callback_t)(void);

/*******************************************************************************
 *								VARIABLES ESTATICAS
 *******************************************************************************/
static bool initialized_enc_low = false;
static uint8_t encoder_timer_count = 0;

/*******************************************************************************
 *								FUNCIONES LOCALES
 *******************************************************************************/

/*******************************************************************************
 *									PROTOTIPOS
 *******************************************************************************/


//void signalARoutine(void);
//void signalBRoutine(void);
//void signalCRoutine(void);
void encTimerRoutine(void);

/*******************************************************************************
 *									FUNCIONES
 *******************************************************************************/

void initializeEncoderLow(void)
{
	if(!initialized_enc_low)
	{
		gpioMode(SIGNAL_A_PIN, INPUT_PULLDOWN);
		gpioMode(SIGNAL_B_PIN, INPUT_PULLDOWN);
		gpioMode(SIGNAL_C_PIN, INPUT_PULLDOWN);
		SetTimer(ENCODER_TIMER, ENCODER_TIME, encTimerRoutine);
		DisableTimer(ENCODER_TIMER);		//lo inicializo sólo cuando se presiona el enter

		initialized_enc_low = true;
	}
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


void signalARoutine(void)
{
	bool temp = encoder.curr_data[A];			//guardo valor actual, que pasará a ser valor anterior
	encoder.curr_data[A] = gpioRead(SIGNAL_A_PIN);  //leo valor actual
	encoder.prev_data[A] = temp;				//actualizo valor anterior
}

void signalBRoutine(void)
{

}

void signalCRoutine(void)
{
	bool temp = encoder.curr_data[C];					//guardo valor actual para reemplazar al prev value
	encoder.curr_data[C] = gpioRead(SIGNAL_C_PIN);		//leo valor actual
	encoder.prev_data[C] = temp;						//actualizo valor anterior

	if(checkEnterRisingEdge())		//si es flanco ascendente, seteo los timers para ver si es enter, back o cancel
	{
		SetTimer(ENTER_TIMER, ENTER_TIME, enterTimerRoutine);
		SetTimer(BACK_TIMER, BACK_TIME, backTimerRoutine);
		SetTimer(CANCEL_TIMER, CANCEL_TIME, cancelTimerRoutine);
	}
	if(checkEnterFallingEdge())
	{
;
	}

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

void setTimerCallback(void (*funcallback)(void))
{
	SetTimer(CANCEL_TIMER, CANCEL_TIME, funcallback);		//un timer genérico
	DisableTimer(CANCEL_TIMER);
}

//void setEnterCallback(void (*funcallback)(void))
//{
//	SetTimer(ENTER_TIMER, ENTER_TIME, funcallback);
//	DisableTimer(ENTER_TIMER);
//}
//void setBackCallback(void (*funcallback)(void))
//{
//	SetTimer(BACK_TIMER, BACK_TIME, funcallback);
//	DisableTimer(BACK_TIMER);
//}





