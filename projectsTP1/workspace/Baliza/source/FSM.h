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

//Defincion de constantes y parametros
//#define NUM_TIMERS 2 //Numero de timers que se utilizan.
#define ID_LENGTH 8 //Longitud maxima del ID del usuario.
#define PIN_LENGTH 5 //Longitud maxima del PIN del usuario.
//#define NUM_EVENTS 3  //Cantidad de eventos posibles.

enum timers{INACTIVITY, DISPLAY, NUM_TIMERS}; //Timers utilizados
enum states{WAITING_ID, RECEIVING_ID, RECEIVING_PIN, ACCESS_GRANTED, ADMIN_MODE, ADDING_USER,
			REMOVING_USER, CHANGING_PIN, NUM_STATES}; //Estados posibles de la FSM
enum events{INPUT_EV, TIMER_EV, KEYCARD_EV, NUM_EVENTS};


//UserData contiene toda la informacion necesaria que necesita una rutina para manejar
//un evento que se saco de la cola.
typedef struct{
   char received_ID[ID_LENGTH]; //String con el ID recibido del usuario.
   char received_PIN[PIN_LENGTH]; //String con el PIN recibido del usuario.
   bool timers[NUM_TIMERS]; //Arreglo que indica que timers expiraron.
}UserData_t;

//Tipo de datos que ses almacena en la cola de eventos.
typedef struct{
   char ev_name; //Tipo de evento recibido.
   UserData_t * data; //Informacion necesaria para atender el evento.
}event_t;

struct state;
typedef struct state (*StateRoutinePtr_t)(UserData_t *);

typedef struct state{
   unsigned char name_of_state;
   StateRoutinePtr_t Routines[NUM_EVENTS]; //La cantidad de rutinas es igual a la cantidad de eventos possibles.
}state_t;

#endif /* FSM_H_ */
