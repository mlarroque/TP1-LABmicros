/*
 * stateUserApproved.c
 *
 *  Created on: Sep 5, 2019
 *      Author: Manuel Mollon
 */

#include "stateUserApproved.h"
#include "stateAdminMode.h"
#include "stateChangingPIN.h"

state_t UAinputEvHandler(UserData_t * ud)
{

}

state_t UAtimerEvHandler(UserData_t * ud)
{
	state_t nextState;
	if(ud->timerUd.timers[DISPLAY]){
		UpdateDisplay();
	}
	// TERMINAR (agregar el timer de inactividad)
	nextState.name = STAY;
	return nextState;
}

state_t UAkeycardEvHandler(UserData_t * ud)
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
		PrintMessage("VALID ID - ENTER PIN", true);
		ud->received_ID = ud->magnetLectorUd.id;
		int i;
	    for(i=0;i<PIN_MAX_LENGTH;++i){
	    	userData.received_PID[i] = -1;
	    } // clean user PIN
		ud->option = -1;
		nextState.name = RECEIVING_PIN;
		nextState.routines[INPUT_EV] = &RPinputEvHandler;
		nextState.routines[TIMER_EV] = &RPtimerEvHandler;
		nextState.routines[KEYCARD_EV] = &RPkeycardEvHandler;
	}
	else{
		// show message in display
		PrintMessage("INVALID ID", true);
		nextState.name = STAY;
	}
	return nextState;
}
