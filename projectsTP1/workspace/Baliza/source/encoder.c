/*
 * encoder.c
 *
 *  Created on: Sep 1, 2019
 *      Author: Lu
 */

_Bool IsValid(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT]);
_Bool WasThereChange(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT]);

_Bool CheckEnter(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT])
{
  //true si se presionó el ENTER (flanco ascendente)
	return (prev_data[C]==LOW) && (curr_data[C]==HIGH);
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
			else if(IsCounterClockwise(prev_data, curr_data))
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
	//si A adelanta a B, es clockwise
	if (IsValid(curr_data));


}

_Bool IsCounterClockwise(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT])
{

}


_Bool IsValid(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT])
{
	status = false;
	//los únicos cambios válidos son los del código de Gray de 2 bits
	// A	0	1	1	0
	// B	0	0	1	1
	//   ------------------>tiempo


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
