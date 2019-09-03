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


/******************************************************************************************
 *  				TIPOS DE DATOS, CONSTANTES Y VARIABLES GLOBALES
 ******************************************************************************************/
typedef enum {INACTIVITY, DISPLAY, MESSAGE, NUM_TIMERS}timer_name; //Timers utilizados
typedef void (*callback_ptr)(void);


/********************************************************************************************
 * 										FUNCIONES
 ********************************************************************************************/
void InitializeTimers(void);
//Recibe el timeout en milisegundos
void SetTimer(unsigned char index,unsigned int timeout, callback_ptr func);
void DisableTimer(unsigned char index);
void EnableTimer(unsigned char index);

#endif /* TIMER_H_ */
