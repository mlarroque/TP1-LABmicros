/***************************************************************************//**
  @file     App.c
  @brief    Application functions
  @author   Nicolás Magliola
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdbool.h>
#include "FSM.h"
#include "queue.h"
#include "dataBase.h"

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
queue_t queue;
// dataBase.h
dataBase_t users;
// App.c
bool chaningState = false;
// queues
timerQueue_t timerQueue;
magnetLectorQueue_t magnetLectorQueue;
encoderQueue_t encoderQueue;

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

    // FSM/Queue Initialization
    nextState.name = MENU;
    nextState.routines[INPUT_EV] = &MinputEvHandler;
    nextState.routines[TIMER_EV] = &MtimerEvHandler;
    nextState.routines[KEYCARD_EV] = &MkeycardEvHandler;
    fsm.currentState = nextState;
    queue.top = -1;
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{
	organizeEvents(&queue, &timerQueue, &magnetLectorQueue, &encoderQueue);
	newEvent = popEvent(&queue);
	switch(newEvent.name){
		case INPUT_EV:
			newState = (fsm.currentState.routines[INPUT_EV])(&userData);
			changingState = true;
			break;
		case TIMER_EV:
			newState = (fsm.currentState.routines[TIMER_EV])(&userData);
			changingState = true;
			break;
		case KEYCARD_EV:
			newState = (fsm.currentState.routines[KEYCARD_EV])(&userData);
			changingState = true;
			break;
		default:
			break;
	}
	if(changingState){
		fsm.currentState = newState;
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
