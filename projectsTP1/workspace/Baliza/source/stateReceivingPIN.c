/*
 * stateReceivingPIN.c
 *
 *  Created on: Sep 1, 2019
 *      Author: Manuel Mollon
 */

#include "stateReceivingPIN.h"
#include "stateBlocked.h"
#include "stateMenu.h"
//#include "stateUserApproved.h"
#include "dataBase.h"

#define PIN_OPTIONS	12
#define INCREMENT	1
#define INITIAL	0

typedef enum {ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,ERASE_LAST,ERASE_ALL}idOption_name;
const char pinStrings[PIN_OPTIONS] = {'0','1','2','3','4','5','6','7','8','9','L','A'};

char * createString(UserData_t * ud);

char * createString(UserData_t * ud){
	//TERMINAR
}

state_t RPinputEvHandler(UserData_t * ud)
{
	state_t nextState;
	char * string;
	switch(ud->encoderUd->input)
	{
		case UP: // change current option
			if(ud->option < PIN_OPTIONS){
				ud->option += INCREMENT;
			}
			else{
				ud->option = INITIAL;
			}
			// show option to user
			string = createString(ud);
			PrintMessage(string, false);
			nextState.name = STAY;
			break;
		case DOWN: // change current option
			if(ud->option > INITIAL){
				ud->option -= INCREMENT;
			}
			else{
				ud->option = PIN_OPTIONS;
			}
			// show option to user
			string = createString(ud);
			PrintMessage(string, false);
			nextState.name = STAY;
			break;
		case ENTER: // Selects current option
			switch(ud->option)
			{
				int j = 0;
				while(ud->received_PIN[j] != -1){
					j += 1;
				}
				case ERASE_LAST:
					if(j>INITIAL)
					{
						ud->received_PIN[j-1] = -1;
					}
					break;
				case ERASE_ALL:
					int j = 0;
					while(ud->received_PIN[j] != -1){
						ud->received_PIN[j] = -1;
						j += 1;
					}
					break;
				default: // number
					ud->received_PIN[j] = ud->option;
					break;
			}
			string = createString(ud);
			PrintMessage(string, false);
			ud->option = -1;
			break;
		case CANCEL:
			ud->option = -1;
		    int i;
		    for(i=0;i<PIN_MAX_LENGTH;++i){
		    	userData.received_PIN[i] = -1;
		    } // clean user PIN
		    for(i=0;i<ID_LENGTH;++i){
		    	userData.received_ID[i] = -1;
		    } // clean user ID
			nextState.name = MENU;
			nextState.routines[INPUT_EV] = &MinputEvHandler;
			nextState.routines[TIMER_EV] = &MtimerEvHandler;
			nextState.routines[KEYCARD_EV] = &MkeycardEvHandler;
			break; // Cancels selection and back to menu
	}
	return nextState;
}

state_t RPtimerEvHandler(UserData_t * ud)
{
	state_t nextState;
	if(ud->timerUd.timers[DISPLAY]){
		UpdateDisplay();
	}
	// TERMINAR (agregar el timer de inactividad y de bloqueo)
	nextState.name = STAY;
	return nextState;
}

state_t RPkeycardEvHandler(UserData_t * ud)
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
	}
	else{
		// show message in display
		PrintMessage("INVALID ID", true);
	}
	nextState.name = STAY;
	return nextState;
}
