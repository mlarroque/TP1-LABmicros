/*
 * timer.c
 *
 *  Created on: Aug 31, 2019
 *      Author: G5
 */
#include "timer.h"
#define NULL 0

/********************************************************************************
 * 							FUNCIONES DEL HEADER
 ********************************************************************************/

void InitializeTimers(void)
{
	int i;
	for(i=0; i< NUM_TIMERS; i++)
	{
		(timers+i)->timeout = INT_FAST8_MAX;
		(timers+i)->func = NULL;
		(timers+i)->counter = 0;
		(timers+i)->enabled = false;
	}
}
void SetTimer(unsigned char index, unsigned int timeout_, callback_ptr func_)
{
	(timers+index)->timeout = timeout_;
	(timers+index)->func = func_;
	(timers+index)->counter = 0;
	(timers+index)->enabled = true;
}
void EnableTimer(unsigned char index)
{
	(timers+index)->enabled = true;
}

void DisableTimer(unsigned char index)
{
	(timers+index)->enabled = false;
}

