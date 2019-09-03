/*
 * queue.h
 *
 *  Created on: Sep 1, 2019
 *      Author: Manuel Mollon
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "FSM.h"

#define MAX_EVENTS 1000

//Cola de eventos
typedef struct{
	int top; //contador de eventos
	event_t events[MAX_EVENTS]; //arreglo con los eventos en la cola
}queue_t;

event_t popEvent(queue_t * queue);

void pushEvent(queue_t * queue, event_t ev);

#endif /* QUEUE_H_ */
