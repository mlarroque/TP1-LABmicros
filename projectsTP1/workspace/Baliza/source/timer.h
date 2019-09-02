/*
 * timer.h
 *
 *  Created on: Aug 31, 2019
 *      Author: G5
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdbool.h>
#include <stdint.h>
#include "SysTick.h"
/*******************************************************************************************
 * 										MACROS
 *******************************************************************************************/

//Devuelve cuantos ticks de SysTick se requieren para el tiempo deseado
#define TIME_TO_PULSES(t) ( (t*SYSTICK_ISR_FREQ_HZ)/1000 ) //Asume que recibe el t en milisegundos.

/******************************************************************************************
 *  				TIPOS DE DATOS, CONSTANTES Y VARIABLES GLOBALES
 ******************************************************************************************/
typedef enum {INACTIVITY, DISPLAY, MESSAGE, NUM_TIMERS}timer_name; //Timers utilizados
typedef void (*callback_ptr)(void);

typedef struct{
	unsigned int timeout; //Cada cuanto se llama al callback(medido en ticks de SysTick)
	callback_ptr func;
	unsigned int counter; //Cuanto tiempo transcurrio desde el ultimo llamado
	bool enabled;
}timer_t;

extern timer_t timers[NUM_TIMERS]; //Arreglo global con los timers inicializados
/********************************************************************************************
 * 										FUNCIONES
 ********************************************************************************************/
void InitializeTimers(void);
void SetTimer(unsigned char index,unsigned int timeout, callback_ptr func);
void DisableTimer(unsigned char index);
void EnableTimer(unsigned char index);

#endif /* TIMER_H_ */
