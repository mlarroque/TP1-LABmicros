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
	encoder.prev_data[signal] = encoder.curr_data[signal];
	encoder.curr_data[signal] = value;
}

counter_type decodeEncoder()
{
	counter_type event = NO_CHANGE;
	if((encoder.prev_data[B] == HIGH) && (encoder.curr_data[B] == LOW))	//flanco descendente de B
	{
		if(encoder.prev_data[A]){
			event = COUNT_UP;
		}
	}
	else if((encoder.prev_data[B] == LOW) && (encoder.curr_data[B] == HIGH))
			event = RESET;
	if ((encoder.prev_data[A] == HIGH) && (encoder.curr_data[A] == LOW))	//flanco descendente de A
	{
		if(encoder.prev_data[B]){	//si la señal anterior de B estaba en HIGH, fue primer flanco de A
			event = COUNT_DOWN;
		}
	}
	else if((encoder.prev_data[A] == LOW) && (encoder.curr_data[A] == HIGH))
		event = RESET;

	return event;
}


void resetData(void)
{
	uint8_t i;
	for(i = 0; i<STATES; i++)
	{
		updateData(HIGH, A);
		updateData(HIGH, B);
	}
}

_Bool checkEnterRisingEdge()
{
	return encoder.curr_data[C];			//true si se deja de presionar el botón
}

_Bool checkEnterFallingEdge(void)
{
	return !encoder.curr_data[C];   //true si se presiona el botón (flanco descendente)
}


