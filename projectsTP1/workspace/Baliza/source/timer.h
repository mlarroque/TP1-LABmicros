/*
 * timer.h
 *
 *  Created on: Aug 31, 2019
 *      Author: G5
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "FSM.h"
/******************************************************************************************
 *  				TIPOS DE DATOS, CONSTANTES Y VARIABLES GLOBALES
 ******************************************************************************************/
typedef void (*callback_ptr)(void);

typedef struct{
	unsigned int timeout; //Cada cuanto se llama al callback(medido en ticks de SysTick)
	callback_ptr func;
	unsigned int counter; //Cuanto tiempo transcurrio desde el ultimo llamado
}timer_t;

extern timer_t timers[NUM_TIMERS]; //Arreglo global con los timers inicializados
extern unsigned int timers_on_array;
/********************************************************************************************
 * 										FUNCIONES
 ********************************************************************************************/
void SetTimer(unsigned int timeout, callback_ptr func);

#endif /* TIMER_H_ */
