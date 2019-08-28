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

//Definicion de constantes y parametros
#define ID_LENGTH 8 //Longitud maxima del ID del usuario.
#define PIN_LENGTH 5 //Longitud maxima del PIN del usuario.

typedef enum {INACTIVITY, DISPLAY, NUM_TIMERS}timer_name; //Timers utilizados
typedef enum {WAITING_ID, RECEIVING_ID, RECEIVING_PIN, ACCESS_GRANTED, ADMIN_MODE, ADDING_USER,
			REMOVING_USER, CHANGING_PIN, NUM_STATES}state_name; //Estados posibles de la FSM
typedef enum {INPUT_EV, TIMER_EV, KEYCARD_EV, NUM_EVENTS}ev_name;


//UserData contiene toda la informacion necesaria que necesita una rutina para manejar
//un evento que se saco de la cola.
typedef struct{
   char received_ID[ID_LENGTH]; //String con el ID recibido del usuario.
   char received_PIN[PIN_LENGTH]; //String con el PIN recibido del usuario.
   bool timers[NUM_TIMERS]; //Arreglo que indica que timers expiraron.
}UserData_t;

//Tipo de datos que se almacena en la cola de eventos.
typedef struct{
	ev_name name; //Tipo de evento recibido.
   UserData_t * data; //Informacion necesaria para atender el evento.
}event_t;

struct state;
typedef struct state (*StateRoutinePtr_t)(UserData_t *);

typedef struct state{
	state_name name;
   StateRoutinePtr_t Routines[NUM_EVENTS]; //La cantidad de rutinas es igual a la cantidad de eventos posibles.
}state_t;

#endif /* FSM_H_ */
