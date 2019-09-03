/*
 * queue.c
 *
 *  Created on: Sep 1, 2019
 *      Author: Manuel Mollon
 */

#include "queue.h"

event_t popEvent(queue_t * queue)
{
	event_t poppedEvent;
	if(queue->top == -1){ // queue empty -> top = -1
		poppedEvent.name = NUM_EVENTS; // default event when queue is empty
		return poppedEvent;
	}
	else{
		poppedEvent = queue.events[top]; //popEvent
		queue->top -= 1; // Decrement queue counter
		return poppedEvent;
	}
}

void pushEvent(queue_t * queue, event_t ev)
{
	if(queue->top == MAX_EVENTS-1){ // event overflow
		queue->top = 0;
		queue->events[top] = ev;
	}
	else{
		queue->top += 1;
		queue->events[top] = ev;
	}
	return;
}

