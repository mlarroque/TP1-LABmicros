/***************************************************************************//**
  @file     App.c
  @brief    Application functions
  @author   Nicolás Magliola
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "board.h"
#include "gpio.h"
#include "FSM.h"
#include "display.h"
#include "SysTick.h"
#include "timer.h"

#define DELAY_BASE 900000UL
#define DELAY_LIMIT_CONST 10
unsigned int timers_on_array = 0;
timer_t timers[NUM_TIMERS];

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
//Devuelve cuantos ticks de SysTick se requieren para el tiempo deseado
#define TIME_TO_PULSES(t) (t*SYSTICK_ISR_FREQ_HZ)


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
void sysTickCallback(void);
void RED_LED_callback(void);
void GREEN_LED_callback(void);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
    gpioMode(PIN_LED_RED, OUTPUT);
    gpioMode(PIN_LED_GREEN, OUTPUT);
    gpioWrite(PIN_LED_RED, LOW);
    gpioWrite(PIN_LED_GREEN,HIGH );
    SysTick_Init(&sysTickCallback);
    unsigned int desired_time = 2; //Tiempo en segundos entre toggle de LED.
    SetTimer(TIME_TO_PULSES(desired_time), &RED_LED_callback);
    SetTimer(TIME_TO_PULSES(desired_time), &GREEN_LED_callback);
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{

}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


void sysTickCallback(void)
{
	int i;
	for(i=0; i < timers_on_array; i++)
	{
		if( ++( (timers+i)->counter ) >= ( (timers+i)->timeout ) )
		{
			(timers+i)->counter = 0; //Si el contador excede el timeout lo reinicio
			((timers+i)->func)();		// y llamo al callback correspondiente al timer.
		}
	}
}

void RED_LED_callback(void)
{
	gpioToggle(PIN_LED_RED);
}

void GREEN_LED_callback(void)
{
	gpioToggle(PIN_LED_GREEN);
}


/*******************************************************************************
 ******************************************************************************/
