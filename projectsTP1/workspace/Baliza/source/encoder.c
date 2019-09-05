/*
 * encoder.c
 *
 *  Created on: Sep 1, 2019
 *      Author: Lu
 */

#include "encoder.h"
#include "encoderDecoder.h"
#include "encoderHAL.h"
#include "encoderQueue.h"

/******************************************************************************
 *									DEFINICIONES
 ******************************************************************************/

//typedef struct{
//	bool enterTimerFinished;
//	bool backTimerFinished;
//	bool cancelTimerFinished;
//}encTimers_t;

/*******************************************************************************
 *								VARIABLES ESTATICAS
 *******************************************************************************/

static bool initialized_enc = false;
static encoderUd_t encoderData;
//static encTimers_t encoderTimers;

/*******************************************************************************
 * 								FUNCIONES LOCALES
 *******************************************************************************/

void setEncCallbacks(void);

void signalACallback(void);
void signalBCallback(void);
void signalCCallback(void);
//void enterCallback(void);
//void backCallback(void);
//void cancelCallback(void);


/********************************************************************************
 * 							FUNCIONES DEL HEADER
 ********************************************************************************/

void initializeEncoder(void)
{
	if(!initialized_enc)
	{
		uint8_t i;
		initializeEncoderLow();		//setea gpio y timer count
		setEncCallbacks();			//setea callbacks para señal
		initializeQueue();			//inicializo queue de encoder

		for(i=0;i<ENC_SIGNAL_COUNT;i++)
			initData(readEncoderSignalX(i), i);				//inicializo estructura encoder_t con las señales en el instante actual y el anterior

//		encoderTimers.enterTimerFinished = false; //no arrancó ningun timer
//		encoderTimers.backTimerFinished = false;
//		encoderTimers.cancelTimerFinished = false;
		encoderData.input = CANCEL;
		initialized_enc = true;
	}
}

void setEncCallbacks(void)
{
	setSignalCallback(signalACallback, A);
	setSignalCallback(signalBCallback, B);
	setSignalCallback(signalCCallback, C);
	//setCancelCallback(cancelCallback);
}

void signalACallback(void)
{
	counter_type event = decodeEncoder(readEncoderSignalX(A), A);
	if(event == COUNT_UP)
		encoderData.input = UP;
	else if(event == COUNT_DOWN)
		encoderData.input = DOWN;
	else if(event == NO_CHANGE);	//si no hay cambio no hago nada
	else if(event == ERROR)			//si hay un error, e.g. se movió muy rápido el encoder, leo de nuevo las señales
	{
		for(i=0;i<ENC_SIGNAL_COUNT;i++)
			initData(readEncoderSignalX(i), i);
	}

	push(encoderQueue)

}
void signalBCallback(void)
{

}
void signalCCallback(void)
{
	resetEncoderTimerCount();
}

encoderQueue_t getEncoderEvent(void)
{
	//llama al encoderqueue.c
	return encoderQueue;
}



