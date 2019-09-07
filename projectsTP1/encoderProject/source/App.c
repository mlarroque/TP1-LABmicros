/***************************************************************************//**
  @file     App.c
  @brief    Application functions
  @author   G5
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <magnetCardLector.h>
#include "doorManagement.h"
#include "encoder.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

magnetLectorData_t dataLector;
encoderUd_t dataEncoder;

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
	initMagnetCardLector();
	initializeEncoder();

	doorInit();
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{
	int delayTime = 1000000UL;
	while(delayTime--);

	if(isEncEventValid())
	{
		dataEncoder = popEncoderEvent();;
		if(dataEncoder.isValid)
		{
			if(dataEncoder.input == UP)
			{
				//openDoor();
			}
			else if(dataEncoder.input == DOWN)
			{
				//closeDoor();
			}
			else if(dataEncoder.input == ENTER)
			{
				openDoor();
			}

			//openDoorTemporally();
		}
	}
	//espero interrupciones y realizo ISRs.
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/*******************************************************************************
 ******************************************************************************/
