/*
 * stateBlocked.c
 *
 *  Created on: Sep 1, 2019
 *      Author: Manuel Mollon
 */

#include "stateBlocked.h"
#include "stateReceivingID.h"

#include "display.h"
#include "encoder.h"

state_t BinputEvHandler(UserData_t * ud)
{
	state_t nextState;
	nextState.name = STAY;
	return nextState;
}

state_t BtimerEvHandler(UserData_t * ud)
{
	state_t nextState;
	nextState.name = STAY;
	if(ud->timerUd == DISPLAY){
		UpdateDisplay();
	}
	if(ud->timerUd == UNBLOCKED){
		userDataReset(false ,true ,false ,true ,ud);
		nextState.name = RECEIVING_ID;
		nextState.routines[INPUT_EV] = &RIinputEvHandler;
		nextState.routines[TIMER_EV] = &RItimerEvHandler;
		nextState.routines[KEYCARD_EV] = &RIkeycardEvHandler;
		PrintMessage("BLOCKED TIME OVER", true);
		//apagar (?) timer
	}
	return nextState;
}

state_t BkeycardEvHandler(UserData_t * ud)
{
	state_t nextState;
	nextState.name = STAY;
	return nextState;
}

