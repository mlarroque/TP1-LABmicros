/*
 * queue.c
 *
 *  Created on: Sep 1, 2019
 *      Author: Manuel Mollon
 */

#include "queue.h"

queue_t queue;

void initializeQueue(void)
{
	queue.top = -1;
}

event_t popEvent(void)
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

void pushEvent(event_t ev)
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

void organizeEvents(dispalyQueue_t * dispalyQueue, magnetLectorQueue_t * magnetLectorQueue, encoderQueue_t * encoderQueue)
{
	//TERMINAR
}

void userDataReset(bool resetID, bool resetPIN, bool resetCategory, bool resetOption, UserData_t * ud)
{
	int i;
	if(resetID){
	    for(i=0;i<ID_LENGTH;++i){
	    	ud->received_ID[i] = -1;
	    } // clean user ID
	}
	if(resetPIN){
	    for(i=0;i<PIN_MAX_LENGTH;++i){
	    	ud->received_PIN[i] = -1;
	    } // clean user PIN
	}
	if(resetCategory){
		ud->category = -1;
	}
	if(resetOption){
		ud->option = -1;
	}
}

