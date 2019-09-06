/*
 * encoderDecoder.c
 *
 *  Created on: Sep 4, 2019
 *      Author: Lu
 */

#include "encoderDecoder.h"

typedef enum {A, B, C, ENC_SIGNAL_COUNT}encoder_signal;


static encoder_t encoder;



void initData(bool value, int signal)
{
	encoder.curr_data[signal] = value;	//seteo el estado actual donde sea que empiece el encoder
	encoder.prev_data[signal] = encoder.curr_data[signal];	//seteo el estado anterior igual al estado actual

}

counter_type decodeEncoder(bool value, int signal)
{
	bool temp = encoder.curr_data[signal];			//guardo valor actual, que pasará a ser valor anterior
	encoder.curr_data[signal] = value;  //leo valor actual
	encoder.prev_data[signal] = temp;				//actualizo valor anterior

	counter_type event = readRotation();
	return event;

}

void updateButtonState(bool value)
{
	bool temp = encoder.curr_data[C];			//guardo valor actual, que pasará a ser valor anterior
	encoder.curr_data[C] = value;  //leo valor actual
	encoder.prev_data[C] = temp;				//actualizo valor anterior
}

bool checkEnterRisingEdge(void)
{
  //true si se presionó el ENTER (flanco ascendente)
	return (encoder.prev_data[C]==LOW) && (encoder.curr_data[C]==HIGH);
}

bool checkEnterFallingEdge(void)
{
  //true si se dejó de presionar el ENTER (flanco descendente)
	return (encoder.prev_data[C]==HIGH) && (encoder.curr_data[C]==LOW);
}

counter_type readRotation(void)
{
	counter_type status = ERROR;

	if(wasThereChange())
	{
		//if(isValid())
		//{
			if(isClockwise())
				status = COUNT_UP;
			else
				status = COUNT_DOWN;
	//}
		//else
		//	status = ERROR;
	}
	else
		status = NO_CHANGE;

	return status;
}

bool isClockwise(void)
{
	bool clockwise = false;
	//si A adelanta a B, es clockwise //CHEQUEAR
	if(encoder.prev_data[A] != encoder.curr_data[A])
	{
		if(encoder.curr_data[B] != encoder.curr_data[A])
			clockwise = true;
		else
			clockwise = false;
	}
	else
	{
		if(encoder.curr_data[B] == encoder.curr_data[A])
			clockwise = true;
		else
			clockwise = false;
	}

	return clockwise;
}

bool isValid(void)
{
	bool status = false;
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

bool wasThereChange(void)
{
	bool status = false;
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

