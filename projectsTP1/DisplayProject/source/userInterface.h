/*
 * inputInterface.h
 *
 * interrupciones para A, B, C en flancos
 * La capa que separa la app del hal encoder
 *
 *  Created on: Sep 1, 2019
 *      Author: Lu
 */

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include "encoder.h"


#include "timer.h"

#define CANCEL_TIMER 2 //si presiona C (enter) por mas de 2 segundos se cancela el intento, y tiene que ingresar id de nuevo

typedef struct{
	   bool prev_encoder_data[ENC_SIGNAL_COUNT]; //estados de las señales en el instante anterior para el encoder
	   bool curr_encoder_data[ENC_SIGNAL_COUNT]; //estados de las señales en el instante actual para el encoder
}input_t;

void SetCancelAttemptTimer();


#endif /* USERINTERFACE_H_ */
