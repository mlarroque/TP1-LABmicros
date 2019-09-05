/*
 * encoderQueue.c
 *
 *  Created on: Sep 4, 2019
 *      Author: Lu
 */


#include "encoderQueue.h"

#define NULL 0
#define ENCODER_EVENTS		500

static encoderQueue_t encoderQueue[ENCODER_EVENTS];


void initializeQueue(void)
{
	encoderQueue.top = -1;
}

encoderQueue_t popEvent(void)
{
	encoderQueue_t poppedEvent;
	if(encoderQueue->top == -1){ // queue empty -> top = -1
		return NULL;
	}
	else
	{
		poppedEvent = encoderQueue.events[top]; //popEvent
		queue->top -= 1; // Decrement queue counter
		return poppedEvent;
	}
}

void pushEvent(encoderQueue_t ev)
{
	if(encoderQueue->top == ENCODER_EVENTS-1){ // event overflow
		encoderQueue->top = 0;
		encoderQueue->event[top] = ev;
	}
	else{
		encoderQueue->top += 1;
		encoderQueue->event[top] = ev;
	}
	return;
}
