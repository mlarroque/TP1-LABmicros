/*
 * encoderDecoder.c
 *
 *  Created on: Sep 4, 2019
 *      Author: Lu
 */

#include "encoderDecoder.h"

typedef enum {A, B, C, ENC_SIGNAL_COUNT}encoder_signal;


static encoder_t encoder;

void resetEdgeFlag(void)
{
	encoder.edge_A = false;
	encoder.edge_B = false;
}

void updateData(_Bool value, int signal)
{
	encoder.prev_data[signal] = encoder.curr_data[signal];
	encoder.curr_data[signal] = value;

}

counter_type decodeEncoder()
{
	counter_type event = NO_CHANGE;
	if(encoder.curr_data[B] != encoder.prev_data[B])	//flanco descendente de B
	{
		if(encoder.edge_A == false)	//si la señal anterior de A estaba en HIGH, fue primer flanco de B
		{
			event = COUNT_UP;
			encoder.edge_B = true;
		}
	}
	else if (encoder.curr_data[A] != encoder.prev_data[A])	//flanco descendente de A
	{
		if(encoder.edge_B == false)	//si la señal anterior de B estaba en HIGH, fue primer flanco de A
		{
			event = COUNT_DOWN;
			encoder.edge_A = true;
		}
	}
	return event;

}

void resetData(void)
{
	updateData(HIGH, A);
	updateData(HIGH, A);
	updateData(HIGH, B);
	updateData(HIGH, B);
}


_Bool checkEnterRisingEdge()
{
	return encoder.curr_data[C];			//true si se deja de presionar el botón
}

_Bool checkEnterFallingEdge(void)
{
	return !encoder.curr_data[C];   //true si se presiona el botón (flanco descendente)
}

counter_type readRotation(void)
{
	counter_type status;// = ERROR;

	if(isClockwise())
	{
		status = COUNT_UP;
	}
	else
		status = COUNT_DOWN;
	//status = NO_CHANGE;

//	if(wasThereChange())
//	{
//		//if(isValid())
//		//{
//			if(isClockwise())
//				status = COUNT_UP;
//			else
//				status = COUNT_DOWN;
//	//}
//		//else
//		//	status = ERROR;
//	}
//	else
//		status = NO_CHANGE;

	return status;
}

_Bool isClockwise(void)
{
	_Bool clockwise;
	if(encoder.prev_data[B] != encoder.curr_data[B])			//me fijo qué flanco fue, si de la señal A o B
	{															//fue señal B
		if(encoder.curr_data[B] != encoder.curr_data[A])
			clockwise = true;
		else
			clockwise = false;
	}
	else if(encoder.prev_data[A] != encoder.curr_data[A])		//fue señal A
	{
		if(encoder.curr_data[B] != encoder.curr_data[A])
			clockwise = false;
		else
			clockwise = true;
	}

	return clockwise;
}

_Bool isValid(void)
{
	_Bool status = false;
	//los únicos cambios válidos son los del código de Gray de 2 bits
	// A	0	1	1	0
	// B	0	0	1	1
	// -------------------->tiempo


	if((encoder.prev_data[A] == LOW) && (encoder.prev_data[B] == LOW))		//si paso de A,B = 0,0 a A,B = 1,0; es válido
		if((encoder.curr_data[A] == HIGH) && (encoder.curr_data[B] == LOW))
			status = true;
	else if((encoder.prev_data[A] == HIGH) && (encoder.prev_data[B] == LOW))		//si paso de A,B = 1,0 a A,B = 1,1; es válido
		if((encoder.curr_data[A] == HIGH) && (encoder.curr_data[B] == HIGH))
			status = true;
	else if((encoder.prev_data[A] == HIGH) && (encoder.prev_data[B] == HIGH))		//si paso de A,B = 1,1 a A,B = 1,0; es válido
		if((encoder.curr_data[A] == LOW) && (encoder.curr_data[B] == HIGH))
			status = true;
	else if((encoder.prev_data[A] == HIGH) && (encoder.prev_data[B] == HIGH))		//si paso de A,B = 1,0 a A,B = 0,0; es válido
		if((encoder.curr_data[A] == LOW) && (encoder.curr_data[B] == LOW))
			status = true;
	else;

	return status;
}

_Bool wasThereChange(void)
{
	_Bool status = false;
	int i;
	for (i=0; i<ENC_SIGNAL_COUNT; i++)
	{
		if(encoder.prev_data[i] != encoder.curr_data[i])
		{
			status = true;
			break;
		}
		else;
	}
	return status;
}

