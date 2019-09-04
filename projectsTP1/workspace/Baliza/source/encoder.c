/*
 * encoder.c
 *
 *  Created on: Sep 1, 2019
 *      Author: Lu
 */

#include "encoder.h"
#include "encoderLow.h"
#include "timer.h"
#include "queue.h"

/******************************************************************************
 *									DEFINICIONES
 ******************************************************************************/
#define CANCEL_TIMER 2000 //si presiona C (enter) por mas de 2 segundos se cancela el intento, y tiene que ingresar id de nuevo

/*******************************************************************************
 *								VARIABLES ESTATICAS
 *******************************************************************************/

static bool initialized_enc = false;
static bool prev_encoder_data[ENC_SIGNAL_COUNT]; //estados de las señales en el instante anterior para el encoder
static bool curr_encoder_data[ENC_SIGNAL_COUNT]; //estados de las señales en el instante actual para el encoder

/*******************************************************************************
 * 								FUNCIONES LOCALES
 *******************************************************************************/
//void sysTickCallback(void);

bool isClockwise(bool prev_data[ENC_SIGNAL_COUNT], bool curr_data[ENC_SIGNAL_COUNT]);
bool isValid(bool prev_data[ENC_SIGNAL_COUNT], bool curr_data[ENC_SIGNAL_COUNT]);
bool wasThereChange(bool prev_data[ENC_SIGNAL_COUNT], bool curr_data[ENC_SIGNAL_COUNT]);

/********************************************************************************
 * 							FUNCIONES DEL HEADER
 ********************************************************************************/

void initializeEncoder(void)
{
	if(!initialized_enc)
	{
		initializeEncoderLow();
		InitializeTimers();
		ClearDisplay();
		SetTimer(DISPLAY, MS_BETWEEN_SYMBOLS, &GenerateDisplayEv);
		SetTimer(MESSAGE,STRING_TIME, &ShiftLeft);//Setteo el timer con la velocidad de movimiento del string.
		initialized_enc = true;
	}
}


enc_type readInput()
{
	//TERMINAR
	readEncoderSignalX()
}


bool checkEnterRisingEdge(bool prev_data[ENC_SIGNAL_COUNT], bool curr_data[ENC_SIGNAL_COUNT])
{
  //true si se presionó el ENTER (flanco ascendente)
	return (prev_data[C]==LOW) && (curr_data[C]==HIGH);
}

bool checkEnterFallingEdge(bool prev_data[ENC_SIGNAL_COUNT], bool curr_data[ENC_SIGNAL_COUNT])
{
  //true si se dejó de presionar el ENTER (flanco descendente)
	return (prev_data[C]==HIGH) && (curr_data[C]==LOW);
}

counter_type readRotation(bool prev_data[ENC_SIGNAL_COUNT], bool curr_data[ENC_SIGNAL_COUNT])
{
	counter_type status = ERROR;

	if(WasThereChange(prev_data, curr_data))
	{
		if(IsValid(prev_data, curr_data))
		{
			if(IsClockwise(prev_data, curr_data))
				status = COUNT_UP;
			else
				status = COUNT_DOWN;
		}
		else
			status = ERROR;
	}
	else
		status = NO_CHANGE;

	return status;

}


bool isClockwise(bool prev_data[ENC_SIGNAL_COUNT], bool curr_data[ENC_SIGNAL_COUNT])
{
	bool clockwise = false;
	//si A adelanta a B, es clockwise //CHEQUEAR
	if(prev_data[A] != curr_data[A])
	{
		if(curr_data[B] != curr_data[A])
			clockwise = true;
		else
			clockwise = false;
	}
	else
	{
		if(curr_data[B] == curr_data[A])
			clockwise = true;
		else
			clockwise = false;
	}

	return clockwise;
}


bool isValid(bool prev_data[ENC_SIGNAL_COUNT], bool curr_data[ENC_SIGNAL_COUNT])
{
	status = false;
	//los únicos cambios válidos son los del código de Gray de 2 bits
	// A	0	1	1	0
	// B	0	0	1	1
	// -------------------->tiempo


	if((prev_data[A] == LOW) && (prev_data[B] == LOW))		//si paso de A,B = 0,0 a A,B = 1,0; es válido
		if((curr_data[A] == HIGH) && (curr_data[B] == LOW))
			status = true;
	else if((prev_data[A] == HIGH) && (prev_data[B] == LOW))		//si paso de A,B = 1,0 a A,B = 1,1; es válido
		if((curr_data[A] == HIGH) && (curr_data[B] == HIGH))
			status = true;
	else if((prev_data[A] == HIGH) && (prev_data[B] == HIGH))		//si paso de A,B = 1,1 a A,B = 1,0; es válido
		if((curr_data[A] == LOW) && (curr_data[B] == HIGH))
			status = true;
	else if((prev_data[A] == HIGH) && (prev_data[B] == HIGH))		//si paso de A,B = 1,0 a A,B = 0,0; es válido
		if((curr_data[A] == LOW) && (curr_data[B] == LOW))
			status = true;
	else;

	return status;
}

bool wasThereChange(bool prev_data[ENC_SIGNAL_COUNT], bool curr_data[ENC_SIGNAL_COUNT])
{
	status = false;
	int i;
	for (i=0; i<ENC_SIGNAL_COUNT; i++)
	{
		if(prev_data[i] != curr_data[i])
		{
			status = true;
			break;
		}
		else;
	}
	return status;
}
