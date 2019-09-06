/***************************************************************************//**
  @file     App.c
  @brief    Application functions
  @author   Grupo 5
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdbool.h>
#include "FSM.h"
#include "queue.h"
#include "dataBase.h"


//IO
#include "display.h"
#include "encoder.h"
#include "magnetCardLector.h"
#include "timer.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// FSM.h
FSM_t fsm;
state_t nextState;
UserData_t userData;
// queue.h
event_t newEvent;
// App.c
bool chaningState = false;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
	// IO Initialization
    InitializeTimers();
    initializeEncoder();
    InitializeDisplay();
    initMagnetCardLector();


    // FSM/Queue Initialization
    initFSM(fsm);
    initializeDataBase();
    initializeQueue();

    // User Data init
    userDataReset(true, true, true, true, ud);

}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{
	organizeEvents(); // organize events of all queues
	newEvent = popEvent(); // get new event
	switch(newEvent.name){ // which type of event?
		case INPUT_EV:
			userData.encoderUd = newEvent.data.encoderUd; // get specific data for that event
			nextState = (fsm.currentState.routines[INPUT_EV])(&userData); // action routine
			if(nextState.name != STAY){ // if state changes
				changingState = true;
			}
			break;
		case TIMER_EV:
			userData.timerUd = newEvent.data.timerUd; // get specific data for that event
			nextState = (fsm.currentState.routines[TIMER_EV])(&userData); // action routine
			if(nextState.name != STAY){ // if state changes
				changingState = true;
			}
			break;
		case KEYCARD_EV:
			userData.keycardUd = newEvent.data.keycardUd; // get specific data for that event
			nextState = (fsm.currentState.routines[KEYCARD_EV])(&userData); // action routine
			if(nextState.name != STAY){ // if state changes
				changingState = true;
			}
			break;
		default:
			break;
	}
	if(changingState){
		fsm.currentState = nextState;
		changingState = false;
	}
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/*******************************************************************************
 ******************************************************************************/
