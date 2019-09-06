/*
 * stateUserApproved.c
 *
 *  Created on: Sep 5, 2019
 *      Author: Manuel Mollon
 */

#include "stateUserApproved.h"
#include "stateAdminMode.h"
#include "stateChangingPIN.h"

#include "doorManagement.h"
#include "dataBase.h"
#include "display.h"
#include "encoder.h"

#define INCREMENT	1
#define INITIAL	0

typedef enum {GRANT_ACCESS,CHANGE_PIN,ADMIN_OPTION,MENU_OPTIONS}option_name;
const char * menuStrings[MENU_OPTIONS] = {"OPEN","PIN","ADM"};

state_t UAinputEvHandler(UserData_t * ud)
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
				case GRANT_ACCESS:
					userDataReset(true ,true ,true ,true ,ud);
					nextState.name = MENU;
					nextState.routines[INPUT_EV] = &MinputEvHandler;
					nextState.routines[TIMER_EV] = &MtimerEvHandler;
					nextState.routines[KEYCARD_EV] = &MkeycardEvHandler;
					openDoorTemporally();
					break;
				case CHANGE_PIN:
					userDataReset(false ,false ,false ,true ,ud);
					nextState.name = CHANGING_PIN;
					nextState.routines[INPUT_EV] = &CPinputEvHandler;
					nextState.routines[TIMER_EV] = &CPtimerEvHandler;
					nextState.routines[KEYCARD_EV] = &CPkeycardEvHandler;
					break;
				case ADMIN_OPTION:
					char categoty = verifyCategory(ud->received_ID);
					if(categroy == ADMIN){
						userDataReset(false ,false ,false ,true ,ud);
						nextState.name = ADMIN_MODE;
						nextState.routines[INPUT_EV] = &AMinputEvHandler;
						nextState.routines[TIMER_EV] = &AMtimerEvHandler;
						nextState.routines[KEYCARD_EV] = &AMkeycardEvHandler;
					}
					else{
						PrintMessage("ACCESS DENIED - USER NOT ADMIN", true);
						nextState.name = STAY;
					}
					break;
			}
			break;
		case CANCEL:
			userDataReset(true ,true ,true ,true ,ud);
			nextState.name = MENU;
			nextState.routines[INPUT_EV] = &MinputEvHandler;
			nextState.routines[TIMER_EV] = &MtimerEvHandler;
			nextState.routines[KEYCARD_EV] = &MkeycardEvHandler;
			break;
		default:
			nextState.name = STAY;
			break;
	}
	return nextState;
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
		userDataReset(false ,true ,true ,true ,ud);
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
