/*
 * encoderDecoder.c
 *
 *  Created on: Sep 4, 2019
 *      Author: Lu
 */

#include "encoderDecoder.h"

typedef enum {A, B, C, ENC_SIGNAL_COUNT}encoder_signal;


static encoder_t encoder;



void updateData(_Bool value, int signal)
{
	_Bool temp = encoder.curr_data[signal];
		//seteo el estado anterior igual al estado actual
	encoder.curr_data[signal] = value;
	encoder.prev_data[signal] = temp;
		//seteo el estado actual donde sea que empiece el encoder

}
void resetStartingToRotate(void)
{
	encoder.first_edge_A = false;
	encoder.first_edge_B = false;
}

counter_type decodeEncoder()
{

	counter_type event = NO_CHANGE;
	if(encoder.curr_data[B] != encoder.prev_data[B])	//flanco descendente de B
	{
		if(encoder.prev_data[A])	//si la señal anterior de A estaba en HIGH, fue primer flanco de B
			event = COUNT_UP;
		//else
		//	event = COUNT_DOWN;
	}
	else if (encoder.curr_data[A] != encoder.prev_data[A])	//flanco descendente de A
	{
		if(encoder.prev_data[B])	//si la señal anterior de B estaba en HIGH, fue primer flanco de A
			event = COUNT_DOWN;
		//else
		//	event = COUNT_UP;
	}
	return event;

}

void updateButtonState(_Bool value)
{
	//_Bool temp = encoder.curr_data[C];			//guardo valor actual, que pasará a ser valor anterior
	//encoder.curr_data[C] = value;  				//leo valor actual
	//encoder.prev_data[C] = temp;				//actualizo valor anterior
	_Bool temp = encoder.curr_data[C];
			//seteo el estado anterior igual al estado actual
	encoder.curr_data[C] = value;
	encoder.prev_data[C] = temp;
}

_Bool checkEnterRisingEdge()
{
  //true si se presionó el ENTER (flanco ascendente)
	return (encoder.prev_data[C]==LOW) && (encoder.curr_data[C]==HIGH);
}

_Bool checkEnterFallingEdge(void)
{
  //true si se dejó de presionar el ENTER (flanco descendente)
	return (encoder.prev_data[C]==HIGH) && (encoder.curr_data[C]==LOW);
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

