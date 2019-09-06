/*
 * stateMenu.c
 *
 *  Created on: Sep 1, 2019
 *      Author: Manuel Mollon
 */

#include "stateMenu.h"
#include "stateChangeIntensity.h"
#include "stateReceivingID.h"
#include "stateReceivingPIN.h"

#include "display.h"
#include "encoder.h"
#include "dataBase.h"

#define INCREMENT	1
#define INITIAL	0

typedef enum {ENTER_ENCODER_ID, INTENSITY,MENU_OPTIONS}option_name;
const char * menuStrings[MENU_OPTIONS] = {"ID","GLOW"};


state_t MinputEvHandler(UserData_t * ud)
{
	state_t nextState;
	switch(ud->encoderUd->input)
	{
		case UP: // change current option
			if(ud->option < MENU_OPTIONS){
				ud->option += INCREMENT;
			}
			else{
				ud->option = INITIAL;
			}
			// show option to user
			PrintMessage(menuStrings[ud->option], false);
			nextState.name = STAY;
			break;
		case DOWN: // change current option
			if(ud->option > INITIAL){
				ud->option -= INCREMENT;
			}
			else{
				ud->option = MENU_OPTIONS;
			}
			// show option to user
			PrintMessage(menuStrings[ud->option], false);
			nextState.name = STAY;
			break;
		case ENTER: // Selects current option
			switch(ud->option)
			{
				case ENTER_ENCODER_ID:
					userDataReset(false, false, false, true, ud);
					nextState.name = RECEIVING_ID;
					nextState.routines[INPUT_EV] = &RIinputEvHandler;
					nextState.routines[TIMER_EV] = &RItimerEvHandler;
					nextState.routines[KEYCARD_EV] = &RIkeycardEvHandler;
					break;
				case INTENSITY:
					userDataReset(false, false, false, true, ud);
					nextState.name = CHANGE_INTENSITY;
					nextState.routines[INPUT_EV] = &CIinputEvHandler;
					nextState.routines[TIMER_EV] = &CItimerEvHandler;
					nextState.routines[KEYCARD_EV] = &CIkeycardEvHandler;
					break;
			}
			break;
		case CANCEL:
			nextState.name = STAY;
			break; // Cancel does nothing in menu state
		default:
			nextState.name = STAY;
			break;
	}
	return nextState;
}

state_t MtimerEvHandler(UserData_t * ud)
{
	state_t nextState;
	nextState.name = STAY;
	if(ud->timerUd.timers[DISPLAY]){
		UpdateDisplay();
	}
	return nextState;
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
		PrintMessage("VALID ID - ENTER PIN", true);
		ud->received_ID = ud->magnetLectorUd.id;
		ud->option = -1;
		userDataReset(false, false, false, true, ud);
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
