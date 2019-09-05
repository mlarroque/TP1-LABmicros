/*
 * encoder.c
 *
 *  Created on: Sep 1, 2019
 *      Author: Lu
 */

#include "encoder.h"
#include "encoderDecoder.h"
#include "encoderHAL.h"

/******************************************************************************
 *									DEFINICIONES
 ******************************************************************************/

#define ENCODER_EVENTS		200

//#define CANCEL_COUNT	20			//el tiempo que tiene que pasar para que sea evento CANCEL es CANCEL_COUNT*ENCODER_TIME (=200ms*20)
#define BACK_COUNT		15			//entre 1 y 3 segundos para que sea evento = BACK
#define ENTER_COUNT		5			//<1 segundo para que el evento sea = ENTER

/*******************************************************************************
 *								VARIABLES ESTATICAS
 *******************************************************************************/

static bool initialized_enc = false;
//static encoderUd_t encoderData;
static encoderQueue_t encoderQueue[ENCODER_EVENTS];

/*******************************************************************************
 * 								FUNCIONES LOCALES
 *******************************************************************************/

void setEncCallbacks(void);

void signalACallback(void);
void signalBCallback(void);
void signalCCallback(void);


encoderQueue_t popEncoderEvent(void);
void initializeEncoderQueue(void);
encoderQueue_t getEncoderEvent(void);

/********************************************************************************
 * 							FUNCIONES DEL HEADER
 ********************************************************************************/

void initializeEncoder(void)
{
	if(!initialized_enc)
	{
		uint8_t i;
		initializeEncoderHAL();		//setea gpio y timer count
		setEncCallbacks();			//setea callbacks para señal
		initializeQueue();			//inicializo queue de encoder

		for(i=0;i<ENC_SIGNAL_COUNT;i++)
			initData(readEncoderSignalX(i), i);				//inicializo estructura encoder_t con las señales en el instante actual y el anterior

		encoderData.input = CANCEL;
		initialized_enc = true;
	}
}

void setEncCallbacks(void)
{
	setSignalCallback(signalACallback, A);
	setSignalCallback(signalBCallback, B);
	setSignalCallback(signalCCallback, C);
}

void signalACallback(void)
{
	uint8_t i;
	encoderQueue_t eventForQueue;
	counter_type event = decodeEncoder(readEncoderSignalX(A), A);
	if(event == COUNT_UP)
		eventForQueue.event.input = UP;
	else if(event == COUNT_DOWN)
		eventForQueue.event.input = DOWN;
	else if(event == NO_CHANGE);	//si no hay cambio no hago nada
	else if(event == ERROR)			//si hay un error, e.g. se movió muy rápido el encoder, leo de nuevo las señales
	{
		for(i=0;i<ENC_SIGNAL_COUNT;i++)
			initData(readEncoderSignalX(i), i);
	}
	pushEvent(eventForQueue);
}
void signalBCallback(void)
{
	uint8_t i;
	encoderQueue_t eventForQueue;
	counter_type event = decodeEncoder(readEncoderSignalX(B), B);
	if(event == COUNT_UP)
		eventForQueue.event.input = UP;
	else if(event == COUNT_DOWN)
		eventForQueue.event.input = DOWN;
	else if(event == NO_CHANGE);	//si no hay cambio no hago nada
	else if(event == ERROR)			//si hay un error, e.g. se movió muy rápido el encoder, leo de nuevo las señales
	{
		for(i=0;i<ENC_SIGNAL_COUNT;i++)
			initData(readEncoderSignalX(i), i);
	}
	pushEvent(eventForQueue);
}

void signalCCallback(void)
{
	//uint8_t i;
	encoderQueue_t eventForQueue;
	updateButtonState(readEncoderSignalX(C));
	if(checkEnterRisingEdge())				//si fue flanco ascendente recién se presionó el botón
	{
		resetEncoderTimerCount();			//reseteo el contador
	}
	else if(checkEnterFallingEdge())		//si fue un flanco descendente me fijo cuánto tiempo se presionó el botón para saber si fue ENTER; BACK o CANCEL
	{
		if(getEncTimerCount() >= BACK_COUNT)		//si fue más de BACK_COUNT, tomó que fue evento = CANCEL
		{
			eventForQueue.event.input = CANCEL;
			resetEncoderTimerCount();				//reseteo el contador
			pushEvent(eventForQueue);
		}
		else if(getEncTimerCount() >= ENTER_COUNT)	//si es menos de BACK_COUNT o mas de ENTER_COUNT el evento es BACK
		{
			eventForQueue.event.input = BACK;
			resetEncoderTimerCount();				//reseteo el contador
			pushEvent(eventForQueue);
		}
		else		//si es menor a ENTER_COUNT el evento es ENTER
		{
			eventForQueue.event.input = ENTER;
			resetEncoderTimerCount();				//reseteo el contador
			pushEvent(eventForQueue);
		}
	}
}

encoderQueue_t getEncoderQueue(void)
{
	return encoderQueue;
}


void initializeEncoderQueue(void)
{
	encoderQueue.top = -1;
}

encoderQueue_t popEncoderEvent(void)
{
	encoderQueue_t poppedEvent;
	if(encoderQueue->top == -1){ // queue empty -> top = -1
		return NULL;
	}
	else
	{
		poppedEvent = encoderQueue.events[top]; //popEvent
		queue->top -= 1; // Decrement queue counter
		return poppedEvent;
	}
}

void pushEncoderEvent(encoderQueue_t ev)
{
	if(encoderQueue->top == ENCODER_EVENTS-1){ // event overflow
		encoderQueue->top = 0;
		encoderQueue->event[top] = ev;
	}
	else{
		encoderQueue->top += 1;
		encoderQueue->event[top] = ev;
	}
	return;
}




