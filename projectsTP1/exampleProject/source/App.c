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

#define DELAY_BASE 900000UL
#define DELAY_LIMIT_CONST 10


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void delayLoop(uint32_t veces);
_Bool buttonLastState = false;
_Bool isBalizaOn = false;
int delayLimit = DELAY_LIMIT_CONST;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
    gpioMode(PIN_LED_RED, OUTPUT);
    //gpioMode(PIN_LED_BLUE, OUTPUT);
    gpioMode(PIN_SW3 , SW_INPUT_TYPE);
    //gpioMode(PIN_SW2 , SW_INPUT_TYPE);
    gpioMode(PIN_LED_EXTERNAL , EXTERNAL_LED_TYPE);
    //gpioMode(PIN_SWITCH_EXTERNAL , EXTERNAL_SW_TYPE);
    gpioWrite(PIN_LED_RED, HIGH);
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{

	_Bool buttonResult = !gpioRead(PIN_SW3); //SW3 es  activo bajo, esta presionado cuando se lee cero lógico
	if((buttonResult != (buttonLastState)) && (buttonResult) ) //Se ingresa al bloque si se presionó el botón.
	{
		isBalizaOn = !isBalizaOn;
		gpioToggle(PIN_LED_RED);
		if (isBalizaOn)
		{
			gpioWrite(PIN_LED_EXTERNAL, HIGH); //que la baliza arranque prendida
		}
		else
		{
			gpioWrite(PIN_LED_EXTERNAL, LOW); //que la baliza se apague inmediatamente
		}
	}
	buttonLastState = buttonResult;
	if (isBalizaOn)
	{

		delayLoop(DELAY_BASE);
		if (!(delayLimit--))
		{
			gpioToggle(PIN_LED_EXTERNAL);
			delayLimit = DELAY_LIMIT_CONST;
		}

	}
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void delayLoop(uint32_t veces)
{
    while ((veces--)) asm("nop");
}


/*******************************************************************************
 ******************************************************************************/
