/*
 * userData.h
 *
 *  Created on: Sep 6, 2019
 *      Author: Manuel Mollon
 */

#ifndef USERDATA_H_
#define USERDATA_H_

#include "timer.h"
#include "encoder.h"
#include "magnetCardLector.h"

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

#endif /* USERDATA_H_ */
