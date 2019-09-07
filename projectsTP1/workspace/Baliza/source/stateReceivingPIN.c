/*
 * stateReceivingPIN.c
 *
 *  Created on: Sep 1, 2019
 *      Author: Manuel Mollon
 */

#include "stateReceivingPIN.h"
#include "stateBlocked.h"
#include "stateMenu.h"
#include "stateUserApproved.h"

#include "display.h"
#include "encoder.h"
#include "dataBase.h"
#include <stdbool.h>

#define PIN_OPTIONS	12
#define INCREMENT	1
#define INITIAL	0
#define MAX_TRIES	3
#define TERMINATOR	'\0'

typedef enum {ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,ERASE_LAST,ERASE_ALL}idOption_name;
const char pinStrings[PIN_OPTIONS] = {'0','1','2','3','4','5','6','7','8','9','L','A'};
char string[STRING_CANT];

char * createString(UserData_t * ud);

char * createString(UserData_t * ud){
	int i=0;
	while(ud->received_PIN[i] != -1){
		string[i] = idStrings[ud->received_PIN[i]];
	}
	i += 1;
	string[i] = idStrings[ud->option];
	i += 1;
	string[i] = TERMINATOR;
}

char tryNro = 0;

state_t RPinputEvHandler(UserData_t * ud)
{
	state_t nextState;
	char * string;
	switch(ud->encoderUd.input)
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
			int j = 0;
			int k = 0;
			while(ud->received_PIN[j] != -1){
				j += 1;
			}
			switch(ud->option)
			{
				case ERASE_LAST:
					if(j>INITIAL)
					{
						ud->received_PIN[j-1] = -1;
					}
					string = createString(ud);
					PrintMessage(string, false);
					nextState.name = STAY;
					break;
				case ERASE_ALL:
					while(ud->received_PIN[k] != -1){
						ud->received_PIN[k] = -1;
						k += 1;
					}
					string = createString(ud);
					PrintMessage(string, false);
					nextState.name = STAY;
					break;
				default: // number
					ud->received_PIN[j] = ud->option;
					bool validPIN = false;
					if(j == PIN_MAX_LENGTH){ // check if pin valid
						validPIN = verifyPIN(ud->received_ID, ud->received_PIN);
						if(validPIN){
							PrintMessage("USER APPROVED", true);
							nextState.name = USER_APPROVED;
							tryNro = 0;
							nextState.routines[INPUT_EV] = &UAinputEvHandler;
							nextState.routines[TIMER_EV] = &UAtimerEvHandler;
							nextState.routines[KEYCARD_EV] = &UAkeycardEvHandler;
						}
						else
						{
							PrintMessage("INCORRECT PIN", true);
							userDataReset(false ,true ,false ,false ,ud);
						    tryNro += 1;
						    if(tryNro < MAX_TRIES){
						    	nextState.name = STAY;
						    }
						    else{
								PrintMessage("USER BLOCKED", true);
								nextState.name = BLOCKED;
								nextState.routines[INPUT_EV] = &BinputEvHandler;
								nextState.routines[TIMER_EV] = &BtimerEvHandler;
								nextState.routines[KEYCARD_EV] = &BkeycardEvHandler;
						    }
						}
					}
					else{
						string = createString(ud);
						PrintMessage(string, false);
						nextState.name = STAY;
					}
					break;
			}
			userDataReset(false ,false ,false ,true ,ud);
			break;
		case CANCEL:
			userDataReset(true ,true ,false ,true ,ud);
		    tryNro = 0;
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
	nextState.name = STAY;
	if(ud->timerUd == DISPLAY){
		UpdateDisplay();
	}
	if(ud->timerUd == INACTIVITY){
		userDataReset(true ,true ,false ,true ,ud);
		nextState.name = MENU;
		nextState.routines[INPUT_EV] = &MinputEvHandler;
		nextState.routines[TIMER_EV] = &MtimerEvHandler;
		nextState.routines[KEYCARD_EV] = &MkeycardEvHandler;
	}
	return nextState;
}

state_t RPkeycardEvHandler(UserData_t * ud)
{
	state_t nextState;
	char cardID[ID_LENGTH];
	int i;
	for(i=0;i<ID_LENGTH;++i){
		cardID[i] = ud->magnetLectorUd.trackString[i];
	}
	bool IDExists = verifyID(cardID);
	if(IDExists){
		// show message in display
		PrintMessage("VALID ID - ENTER PIN", true);
		int i;
		for(i=0;i<ID_LENGTH;++i){
			ud->received_ID[i] = cardID[i];
		}
		userDataReset(false, true, false, true, ud);
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
