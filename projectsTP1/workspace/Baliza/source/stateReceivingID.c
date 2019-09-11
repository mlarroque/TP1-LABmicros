/*
 * stateReceivingID.c
 *
 *  Created on: Sep 1, 2019
 *      Author: Manuel Mollon
 */

#include "stateReceivingID.h"
#include "stateReceivingPIN.h"
#include "stateMenu.h"

#include "dataBase.h"
#include "display.h"
#include "encoder.h"

#define ID_OPTIONS	12
#define LAST_OPTION_ID	(ID_OPTIONS-1)
#define INCREMENT	1
#define INITIAL	0
#define STRING_CANT	(ID_LENGTH+1)
#define INT2CHAR(x)	((char)(x+48))

typedef enum {ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,ERASE_LAST,ERASE_ALL}idOption_name;
static const char idStrings[ID_OPTIONS] = {'0','1','2','3','4','5','6','7','8','9','L','A'};
static char IDstring[STRING_CANT];

char * createIDString(UserData_t * ud);

char * createIDString(UserData_t * ud){
	int i=0;
	while(ud->received_ID[i] != '\0'){
		IDstring[i] = ud->received_ID[i];
	}
	i++;
	if(ud->option != -1)
	{
		IDstring[i] = idStrings[ud->option];
	}
	i++;
	IDstring[i] = '\0';
}

state_t RIinputEvHandler(UserData_t * ud)
{
	state_t nextState;
	char * string;
	int j = 0;
	int k = 0;
	bool validID = false;
	switch(ud->encoderUd.input)
	{
		case BACK:
			break; //AGREGAR SI PINTA
		case UP: // change current option
			if(ud->option < ID_OPTIONS){
				ud->option += INCREMENT;
			}
			else{
				ud->option = INITIAL;
			}
			// show option to user
			string = createIDString(ud);
			PrintMessage(string, false);
			nextState.name = STAY;
			break;
		case DOWN: // change current option
			if(ud->option > INITIAL){
				ud->option -= INCREMENT;
			}
			else{
				ud->option = LAST_OPTION_ID;
			}
			// show option to user
			string = createIDString(ud);
			PrintMessage(string, false);
			nextState.name = STAY;
			break;
		case ENTER: // Selects current option
			while(ud->received_ID[j] != '\0'){
				j += 1;
			}
			switch(ud->option)
			{
				case ERASE_LAST:
					if(j>INITIAL)
					{
						ud->received_ID[j-1] = '\0';
					}
					break;
				case ERASE_ALL:
					while(ud->received_ID[k] != '\0'){
						ud->received_ID[k] = '\0';
						k += 1;
					}
					break;
				default: // number
					ud->received_ID[j] = INT2CHAR(ud->option);
					if(j == ID_LENGTH){ // check if pin valid
						validID = verifyID(ud->received_ID);
						if(validID){
							PrintMessage("ENTER PIN", true);
							nextState.name = RECEIVING_PIN;
							char cat = verifyCategory(ud->received_ID);
							ud->category = cat;
							nextState.routines[INPUT_EV] = &RPinputEvHandler;
							nextState.routines[TIMER_EV] = &RPtimerEvHandler;
							nextState.routines[KEYCARD_EV] = &RPkeycardEvHandler;
							PrintMessage("ENTER PIN", true);
						}
						else
						{
							PrintMessage("INVALID ID", true);
							userDataReset(false ,true ,false ,false ,ud);
						}
					}
					break;
			}
			string = createIDString(ud);
			PrintMessage(string, false);
			userDataReset(false ,false ,false ,true ,ud);
			break;
		case CANCEL:
			userDataReset(true ,false ,false ,true ,ud);
			nextState.name = MENU;
			nextState.routines[INPUT_EV] = &MinputEvHandler;
			nextState.routines[TIMER_EV] = &MtimerEvHandler;
			nextState.routines[KEYCARD_EV] = &MkeycardEvHandler;
			PrintMessage("MENU", false);
			break; // Cancels selection and back to menu
	}
	return nextState;
}

state_t RItimerEvHandler(UserData_t * ud)
{
	state_t nextState;
	nextState.name = STAY;
	if(ud->timerUd == DISPLAY){
		UpdateDisplay();
	}
	if(ud->timerUd == INACTIVITY){
		userDataReset(true ,false ,false ,true ,ud);
		nextState.name = MENU;
		nextState.routines[INPUT_EV] = &MinputEvHandler;
		nextState.routines[TIMER_EV] = &MtimerEvHandler;
		nextState.routines[KEYCARD_EV] = &MkeycardEvHandler;
		PrintMessage("MENU", false);
		//resetear timer
	}
	return nextState;
}

state_t RIkeycardEvHandler(UserData_t * ud)
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
		userDataReset(false, false, false, true, ud);
		nextState.name = RECEIVING_PIN;
		nextState.routines[INPUT_EV] = &RPinputEvHandler;
		nextState.routines[TIMER_EV] = &RPtimerEvHandler;
		nextState.routines[KEYCARD_EV] = &RPkeycardEvHandler;
		PrintMessage("ENTER PIN", false);
	}
	else{
		// show message in display
		PrintMessage("INVALID ID", true);
		nextState.name = STAY;
	}
	return nextState;
}
