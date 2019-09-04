/*
 * stateMenu.c
 *
 *  Created on: Sep 1, 2019
 *      Author: Manuel Mollon
 */

#include "stateMenu.h"
#include "display.h"
#include "dataBase.h"

state_t MinputEvHandler(UserData_t * ud)
{
	//TERMINAR
	state_t nextState;
	switch(ud->encoderUd->input)
	{
		case UP: // change current option
			nextState.name = CHANGE_INTENSITY;
			nextState.routines[INPUT_EV] = &CIinputEvHandler;
			nextState.routines[TIMER_EV] = &CItimerEvHandler;
			nextState.routines[KEYCARD_EV] = &CIkeycardEvHandler;
			break;
		case DOWN: // change current option
			nextState.name = RECEIVING_ID;
			nextState.routines[INPUT_EV] = &RIinputEvHandler;
			nextState.routines[TIMER_EV] = &RItimerEvHandler;
			nextState.routines[KEYCARD_EV] = &RIkeycardEvHandler;
		case ENTER: // Selects current option
			switch(ud->encoderUd)
			break;
		case CANCEL:
			break; // Cancel does nothing in menu state
		default:
			break;
	}
	return nextState;
}

state_t MtimerEvHandler(UserData_t * ud)
{
	state_t nextState;
	if(ud->timerUd.timers[DISPLAY])
	{
		UpdateDisplay();
	}
}

state_t MkeycardEvHandler(UserData_t * ud)
{
	state_t nextState;
	char cardID[ID_LENGTH];
	int i;
	for(i=0;i<ID_LENGTH;++i){
		cardID[i] = ud->magnetLectorUd.id[i];
	}
	bool IDExists = verifyID(cardID);
	if(IDExists){
		// show message in display
		//TERMINAR
		nextState.name = RECEIVING_PIN;
		nextState.routines[INPUT_EV] = &RIinputEvHandler;
		nextState.routines[TIMER_EV] = &RItimerEvHandler;
		nextState.routines[KEYCARD_EV] = &RIkeycardEvHandler;
	}
	else{
		// show message in display
		//TERMINAR
	}

}
