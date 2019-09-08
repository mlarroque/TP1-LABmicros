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

static _Bool initialized_enc = false;
//static encoderUd_t encoderData;
static encoderQueue_t encoderQueue[ENCODER_EVENTS];
//static _Bool initEv = false;

/*******************************************************************************
 * 								FUNCIONES LOCALES
 *******************************************************************************/

void setEncCallbacks(void);

void signalACallback(void);
void signalBCallback(void);
void setEncCallbacks(void);
void signalCCallback(void);


void pushEncoderEvent(encoderUd_t ev);
encoderUd_t popEncoderEvent(void);
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
		uint8_t j;
		initializeEncoderHAL();		//setea gpio y timer count
		setEncCallbacks();			//setea callbacks para señal
		initializeEncoderQueue();			//inicializo queue de encoder

		for(j=0; j<2;j++)
			for(i=0;i<ENC_SIGNAL_COUNT;i++)
				updateData(readEncoderSignalX(i), i);				//inicializo estructura encoder_t con las señales en el instante actual y el anterior
		resetEdgeFlag();
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
	updateData(LOW, A);
	//updateData(readEncoderSignalX(B), B);
	/*for(i=0;i<(ENC_SIGNAL_COUNT-1);i++)
	{
		updateData(readEncoderSignalX(i), i);
	}*/

	encoderUd_t eventForQueue;
	eventForQueue.isValid = true;
	counter_type event = decodeEncoder();


	if(event == COUNT_UP)
	{
		eventForQueue.input = UP;
		resetData();
	}
	else if(event == COUNT_DOWN)
	{
		eventForQueue.input = DOWN;
		resetData();
	}
	else if(event == NO_CHANGE)
	{
		eventForQueue.isValid = false;
		resetEdgeFlag();
		resetData();
	}
	pushEncoderEvent(eventForQueue);

}
void signalBCallback(void)
{
	updateData(LOW, B);
	//updateData(readEncoderSignalX(B), 1);
	//updateData(readEncoderSignalX(A), 0);
	encoderUd_t eventForQueue;
	eventForQueue.isValid = true;

	counter_type event = decodeEncoder();

	if(event == COUNT_UP)
	{
		eventForQueue.input = UP;
		resetData();
	}
	else if(event == COUNT_DOWN)
	{
		eventForQueue.input = DOWN;
		resetData();
	}
	else if(event == NO_CHANGE)	//si no hay cambio no hago nada
	{
		eventForQueue.isValid = false;
		resetEdgeFlag();
		resetData();
	}
	pushEncoderEvent(eventForQueue);
}

void signalCCallback(void)
{
	updateData(readEncoderSignalX(C), C);

	encoderQueue_t eventForQueue;
 	eventForQueue.event.isValid = true;
	if(checkEnterFallingEdge())				//si fue flanco descendente recién se presionó el botón
	{
		resetEncoderTimerCount();			//reseteo el contador
	}
	else if(checkEnterRisingEdge())		//si fue un flanco descendente me fijo cuánto tiempo se presionó el botón para saber si fue ENTER; BACK o CANCEL
	{
		if(getEncTimerCount() >= BACK_COUNT)		//si fue más de BACK_COUNT, tomó que fue evento = CANCEL
		{
			eventForQueue.event.input = CANCEL;
			resetEncoderTimerCount();				//reseteo el contador
			pushEncoderEvent(eventForQueue.event);
		}
		else if(getEncTimerCount() >= ENTER_COUNT)	//si es menos de BACK_COUNT o mas de ENTER_COUNT el evento es BACK
		{
			eventForQueue.event.input = BACK;
			resetEncoderTimerCount();				//reseteo el contador
			pushEncoderEvent(eventForQueue.event);
		}
		else		//si es menor a ENTER_COUNT el evento es ENTER
		{
			eventForQueue.event.input = ENTER;
			resetEncoderTimerCount();				//reseteo el contador
			pushEncoderEvent(eventForQueue.event);
		}
	}
}




void initializeEncoderQueue(void)
{
	encoderQueue->top = -1;
	encoderQueue->isEmpty = true;
}

encoderUd_t popEncoderEvent(void)
{
	encoderUd_t poppedEvent;
	if(encoderQueue->top == -1)
	{ // queue empty -> top = -1
		encoderQueue->isEmpty = true;
		poppedEvent.isValid = false;
	}
	else
	{
		poppedEvent = encoderQueue[encoderQueue->top].event; //popEvent
		poppedEvent.isValid = true;
		encoderQueue->top -= 1; // Decrement queue counter
		if(encoderQueue->top == -1)
		{
			encoderQueue->isEmpty = true;
		}
	}
	return poppedEvent;
}

_Bool isEncEventValid(void)
{
	return !encoderQueue->isEmpty;
}
void pushEncoderEvent(encoderUd_t ev)
{
	if(encoderQueue->top == ENCODER_EVENTS-1)
	{ // event overflow
		encoderQueue->top = 0;
		encoderQueue[encoderQueue->top].event = ev;
		encoderQueue->isEmpty = false;
	}
	else{
		encoderQueue->top += 1;
		encoderQueue[encoderQueue->top].event = ev;
		encoderQueue->isEmpty = false;
	}
	return;
}




