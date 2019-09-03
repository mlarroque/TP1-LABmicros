/*
 * encoder.c
 *
 *  Created on: Sep 1, 2019
 *      Author: Lu
 */

_Bool IsClockwise(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT]);
_Bool IsValid(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT]);
_Bool WasThereChange(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT]);

_Bool CheckEnterRisingEdge(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT])
{
  //true si se presionó el ENTER (flanco ascendente)
	return (prev_data[C]==LOW) && (curr_data[C]==HIGH);
}

_Bool CheckEnterFallingEdge(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT])
{
  //true si se dejó de presionar el ENTER (flanco descendente)
	return (prev_data[C]==HIGH) && (curr_data[C]==LOW);
}

counter_type ReadInput(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT])
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


_Bool IsClockwise(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT])
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


_Bool IsValid(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT])
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

_Bool WasThereChange(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT])
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
