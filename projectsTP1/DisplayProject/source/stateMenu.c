/*
 * stateMenu.c
 *
 *  Created on: Sep 1, 2019
 *      Author: Manuel Mollon
 */

#include "stateMenu.h"
#include "display.h"

state_t MinputEvHandler(UserData_t * ud)
{
	//TERMINAR
	state_t nextState;
	switch(ud->input)
	{
		case INTENSITY: // user wants to change intensity
			nextState.name = CHANGE_INTENSITY;
			nextState.routines[INPUT_EV] = &CIinputEvHandler;
			nextState.routines[TIMER_EV] = &CItimerEvHandler;
			nextState.routines[KEYCARD_EV] = &CIkeycardEvHandler;
			break;
		case ENCODER_ID: // user wants to enter ID manually
			nextState.name = RECEIVING_ID;
			nextState.routines[INPUT_EV] = &RIinputEvHandler;
			nextState.routines[TIMER_EV] = &RItimerEvHandler;
			nextState.routines[KEYCARD_EV] = &RIkeycardEvHandler;
			break;
		default:
			break;
	}
	return nextState;
}

state_t MtimerEvHandler(UserData_t * ud)
{
	if(ud->timers[DISPLAY])
	{
		UpdateDisplay();
	}
}

state_t MkeycardEvHandler(UserData_t * ud)
{

}
