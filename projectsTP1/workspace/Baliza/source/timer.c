/*
 * timer.c
 *
 *  Created on: Aug 31, 2019
 *      Author: G5
 */
#include "timer.h"
#include "SysTick.h"

/******************************************************************************
 *									DEFINCIONES
 ******************************************************************************/
#define NULL 0
typedef struct{
	unsigned int timeout; //Cada cuanto se llama al callback(medido en ticks de SysTick)
	callback_ptr func;
	unsigned int counter; //Cuanto tiempo transcurrio desde el ultimo llamado
	bool enabled;
}timer_t;

/*******************************************************************************************
 * 										MACROS
 *******************************************************************************************/
//Devuelve cuantos ticks de SysTick se requieren para el tiempo deseado
#define MS_TO_PULSES(t) ( (t*SYSTICK_ISR_FREQ_HZ)/1000 ) //Asume que recibe el t en milisegundos.

/*******************************************************************************
 *								VARIABLES ESTATICAS
 *******************************************************************************/
static timer_t timers[NUM_TIMERS]; //Arreglo global con los timers inicializados
static bool initialized = false;

/*******************************************************************************
 * 								FUNCIONES LOCALES
 *******************************************************************************/
void sysTickCallback(void);
/********************************************************************************
 * 							FUNCIONES DEL HEADER
 ********************************************************************************/

void InitializeTimers(void)
{
	if(!initialized)
	{
		int i;
		for(i=0; i< NUM_TIMERS; i++)
		{
			(timers+i)->timeout = INT_FAST8_MAX;
			(timers+i)->func = NULL;
			(timers+i)->counter = 0;
			(timers+i)->enabled = false;
		}
		SysTick_Init(&sysTickCallback);
		initialized = true;
	}

}
void SetTimer(unsigned char index, unsigned int timeout_, callback_ptr func_)
{
	(timers+index)->enabled = false; //Deshabilto el timer para efectuar los cambios.
	(timers+index)->timeout = MS_TO_PULSES(timeout_);
	(timers+index)->func = func_;
	(timers+index)->counter = 0;
	(timers+index)->enabled = true;
}
void EnableTimer(unsigned char index)
{
	(timers+index)->enabled = true;
}

void DisableTimer(unsigned char index)
{
	(timers+index)->enabled = false;
}

/*******************************************************************************
 * 								FUNCIONES LOCALES
 *******************************************************************************/
void sysTickCallback(void)
{
	int i;
	for(i=0; i < NUM_TIMERS; i++)
	{
		if( (timers+i)->enabled )
		{
			if( ++( (timers+i)->counter ) >= ( (timers+i)->timeout ) )
					{
						(timers+i)->counter = 0; //Si el contador excede el timeout lo reinicio
						((timers+i)->func)();		// y llamo al callback correspondiente al timer.
					}
		}

	}
}
