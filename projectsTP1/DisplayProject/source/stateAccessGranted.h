/*
 * stateAccessGranted.h
 *
 *  Created on: Aug 31, 2019
 *      Author: Manuel Mollon
 */

#ifndef ACCESS_GRANTED_H_
#define ACCESS_GRANTED_H_

#include "FSM.h"

state_t AGinputEvHandler(UserData_t * ud);

state_t AGtimerEvHandler(UserData_t * ud);

state_t AGkeycardEvHandler(UserData_t * ud);

#endif /* ACCESS_GRANTED_H_ */


