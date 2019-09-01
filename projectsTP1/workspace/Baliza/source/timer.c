/*
 * timer.c
 *
 *  Created on: Aug 31, 2019
 *      Author: G5
 */
#include "timer.h"

void SetTimer(unsigned int timeout, callback_ptr func)
{
	timer_t new_timer = {timeout, func, 0};
	timers[timers_on_array] = new_timer;
	++timers_on_array;
}

