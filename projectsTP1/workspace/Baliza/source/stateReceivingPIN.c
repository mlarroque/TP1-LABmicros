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
#define LAST_OPTION_PIN	(PIN_OPTIONS-1)
#define INCREMENT	1
#define INITIAL	0
#define MAX_TRIES	3
#define HIDDEN '-'
#define STRING_CANT	(PIN_MAX_LENGTH+1)
#define INT2CHAR(x)	((char)(x+48))

typedef enum {ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,ERASE_LAST,ERASE_ALL}idOption_name;
static const char pinStrings[PIN_OPTIONS] = {'0','1','2','3','4','5','6','7','8','9','L','A'};
static char PINstring[STRING_CANT];

static void createPINString(UserData_t * ud);

static void createPINString(UserData_t * ud){
	int i=0;
	while(ud->received_PIN[i] != '\0'){
		PINstring[i] = HIDDEN;
		i++;
	}
	if(ud->option != -1){
		PINstring[i] = pinStrings[ud->option];
		i++;
	}
	PINstring[i] = '\0';
}

int tryNro = 0;

state_t RPinputEvHandler(UserData_t * ud)
{
	state_t nextState;
	int j = 0;
	int k = 0;
	bool validPIN = false;
	switch(ud->encoderUd.input)
	{
		case BACK:
			break;
		case UP: // change current option
			if(ud->option < LAST_OPTION_PIN){
				ud->option += INCREMENT;
			}
			else{
				ud->option = INITIAL;
			}
			// show option to user
			createPINString(ud);
			PrintMessage(PINstring, false);
			nextState.name = STAY;
			break;
		case DOWN: // change current option
			if(ud->option > INITIAL){
				ud->option -= INCREMENT;
			}
			else{
				ud->option = LAST_OPTION_PIN;
			}
			// show option to user
			createPINString(ud);
			PrintMessage(PINstring, false);
			nextState.name = STAY;
			break;
		case ENTER: // Selects current option
			while(ud->received_PIN[j] != '\0'){
				j++;
			}
			switch(ud->option)
			{
				case ERASE_LAST:
					if(j>INITIAL){
						ud->received_PIN[j-1] = '\0';
					}
					createPINString(ud);
					PrintMessage(PINstring, false);
					nextState.name = STAY;
					break;
				case ERASE_ALL:
					while(ud->received_PIN[k] != '\0'){
						ud->received_PIN[k] = '\0';
						k += 1;
					}
					createPINString(ud);
					PrintMessage(PINstring, false);
					nextState.name = STAY;
					break;
				default: // number
					if((ud->option >= INITIAL) && (j < PIN_MAX_LENGTH)){
						ud->received_PIN[j] = INT2CHAR(ud->option);
						j++;
						userDataReset(false ,false ,false ,true ,ud);
						createPINString(ud);
						PrintMessage(PINstring, false);
						nextState.name = STAY;
					}
					if(j == PIN_MAX_LENGTH){ // check if pin valid
						validPIN = verifyPIN(ud->received_ID, ud->received_PIN);
						if(validPIN){
							nextState.name = USER_APPROVED;
							tryNro = 0;
							nextState.routines[INPUT_EV] = &UAinputEvHandler;
							nextState.routines[TIMER_EV] = &UAtimerEvHandler;
							nextState.routines[KEYCARD_EV] = &UAkeycardEvHandler;
							PrintMessage("USER APPROVED", true);
						}
						else
						{
							PrintMessage("INCORRECT PIN", true);
							userDataReset(false ,true ,false ,true ,ud);
						    tryNro += 1;
						    if(tryNro < MAX_TRIES){
						    	nextState.name = STAY;
						    }
						    else{
								nextState.name = BLOCKED;
								nextState.routines[INPUT_EV] = &BinputEvHandler;
								nextState.routines[TIMER_EV] = &BtimerEvHandler;
								nextState.routines[KEYCARD_EV] = &BkeycardEvHandler;
								PrintMessage("USER BLOCKED", true);
								//init blocked timer
						    }
						}
					}
					else{
						createPINString(ud);
						PrintMessage(PINstring, false);
						nextState.name = STAY;
					}
					break;
			}
			userDataReset(false ,false ,false ,true ,ud);
			break;
		case CANCEL:
			userDataReset(true ,true ,true ,true ,ud);
		    tryNro = 0;
			nextState.name = MENU;
			nextState.routines[INPUT_EV] = &MinputEvHandler;
			nextState.routines[TIMER_EV] = &MtimerEvHandler;
			nextState.routines[KEYCARD_EV] = &MkeycardEvHandler;
			PrintMessage("MENU", false);
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
		tryNro = 0;
		nextState.name = MENU;
		nextState.routines[INPUT_EV] = &MinputEvHandler;
		nextState.routines[TIMER_EV] = &MtimerEvHandler;
		nextState.routines[KEYCARD_EV] = &MkeycardEvHandler;
		PrintMessage("MENU", false);
		//resetear timer
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
		tryNro = 0;
		ud->category = verifyCategory(ud->received_ID);
		int i;
		for(i=0;i<ID_LENGTH;++i){
			ud->received_ID[i] = cardID[i];
		}
		userDataReset(false, true, false, true, ud);
		nextState.name = RECEIVING_PIN;
		nextState.routines[INPUT_EV] = &RPinputEvHandler;
		nextState.routines[TIMER_EV] = &RPtimerEvHandler;
		nextState.routines[KEYCARD_EV] = &RPkeycardEvHandler;
		PrintMessage("ENTER PIN", true);
	}
	else{
		// show message in display
		PrintMessage("INVALID ID", true);
		nextState.name = STAY;
	}
	return nextState;
}
