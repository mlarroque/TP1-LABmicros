/*
 * FSM.h
 *
 * Header con las definiciones de las estructuras utilizadas
 * para los  estados, eventos y la FSM.
 *
 *  Created on: Aug 28, 2019
 *      Author: Ezequiel Vijande
 */

#ifndef FSM_H_
#define FSM_H_

#include "display.h"

void organizeEvents(void);


typedef enum {MENU, CHANGE_INTENSITY, RECEIVING_ID, RECEIVING_PIN, ACCESS_GRANTED, ADMIN_MODE, ADDING_USER,
			REMOVING_USER, CHANGING_PIN, BLOCKED, NUM_STATES,STAY}state_name; //Estados posibles de la FSM
typedef enum {UP,DOWN,ENTER,CANCEL,EMPTY}input_name;


//UserData contiene toda la informacion necesaria que necesita una rutina para manejar
//un evento que se saco de la cola.
typedef struct{
   //bool timers[NUM_TIMERS]; //Arreglo que indica que timers expiraron.
	timerUd_t timerUd;
	magnetLectorUd_t magnetLectorUd;
	encoderUd_t encoderUd;
	char received_ID[ID_LENGTH]; //String con el ID recibido del usuario.
	char received_PIN[PIN_MAX_LENGTH]; //String con el PIN recibido del usuario.
	char option; // Si usuario emitio un pedido
	category_name category;
}UserData_t;

struct state;
typedef struct state (*StateRoutinePtr_t)(UserData_t *);

typedef struct state{
	state_name name;
	StateRoutinePtr_t routines[NUM_EVENTS]; //La cantidad de rutinas es igual a la cantidad de eventos posibles.
}state_t;

typedef struct{
	state_t currentState;
	bool exit;
}FSM_t;

#endif /* FSM_H_ */
