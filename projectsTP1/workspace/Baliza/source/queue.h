/*
 * queue.h
 *
 *  Created on: Sep 1, 2019
 *      Author: Manuel Mollon
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#define MAX_EVENTS 1000

#include "display.h"
// #include "encoder.h"
// #include "lector.h"

typedef enum {INPUT_EV, TIMER_EV, KEYCARD_EV, NUM_EVENTS}ev_name;

//Tipo de datos que se almacena en la cola de eventos.
typedef struct{
	ev_name name; //Tipo de evento recibido.
	UserData_t data; //Informacion necesaria para atender el evento.
}event_t;

//Cola de eventos
typedef struct{
	int top; //contador de eventos
	event_t events[MAX_EVENTS]; //arreglo con los eventos en la cola
}queue_t;

event_t popEvent(queue_t * queue);

void pushEvent(queue_t * queue, event_t ev);

void organizeEvents(queue_t * queue, dispalyQueue_t * dispalyQueue, magnetLectorQueue_t * magnetLectorQueue, encoderQueue_t * encoderQueue);

#endif /* QUEUE_H_ */
