/*
 * dataBase.c
 *
 *  Created on: Sep 1, 2019
 *      Author: Manuel Mollon
 */

#include "dataBase.h"

status addUser(user_t newUser, dataBase_t * dataBase)
{
	if(dataBase->top == MAX_CANT_USERS-1){ // user overflow
		return DATABASE_FULL;
	}
	else{
		// checks if ID already on list
		bool IDused = verifyID( newUser.usersID[ID_LENGTH] , dataBase);
		if(!IDused)
		{
			// if not on list, user is added
			dataBase->top += 1;
			dataBase->userList[top] = newUser;
			return SUCCESSFULL;
		}
		else
		{
			return ID_ALREADY_EXISTS;
		}
	}
}

status removeUser(user_t userToDelete, dataBase_t * dataBase)
{
		// checks if ID is on list
		bool IDfound = false;
		int i; //position where ID is, if found
		for(i=0 ; i< (dataBase->top + 1) ; ++i){
			int j;
			bool same = true;
			for(j=0 ; i<ID_LENGTH ; ++i){
				if(dataBase->userList[i].usersID[j] != userToDelete.usersID[j]){
					same = false;
				}
			}
			if(same){
				IDfound = true;
				break;
			}
		}
		if(IDfound)
		{
			// if on list, user is deleted
			user_t topUser = dataBase->userList[top];
			dataBase->userList[i] = topUser; // overwrites user to be removed
			dataBase->top -= 1; // decrements top pointer
			return SUCCESSFULL;
		}
		else
		{
			return ID_NOT_FOUND;
		}
}

bool verifyID(char usersID[ID_LENGTH], dataBase_t * dataBase)
{
	// checks if ID is on list
	bool IDfound = false;
	int i;
	for(i=0 ; i< (dataBase->top + 1) ; ++i){
		int j;
		bool same = true;
		for(j=0 ; i<ID_LENGTH ; ++i){
			if(dataBase->userList[i].usersID[j] != usersID[j]){
				same = false;
			}
		}
		if(same){
			IDfound = true;
			break;
		}
	}
	return IDfound;
}

bool verifyPIN(char usersID[ID_LENGTH], char usersPIN[PIN_MAX_LENGTH], dataBase_t * dataBase)
{
	// checks if ID is on list
	bool IDfound = false;
	int i;
	for(i=0 ; i< (dataBase->top + 1) ; ++i){
		int j;
		bool same = true;
		for(j=0 ; i<ID_LENGTH ; ++i){
			if(dataBase->userList[i].usersID[j] != usersID[j]){
				same = false;
			}
		}
		if(same){
			IDfound = true;
			break;
		}
	}
	bool correctPIN = true;
	for(j=0 ; i<PIN_MAX_LENGTH ; ++i){
		if(dataBase->userList[i].usersPIN[j] != usersPIN[j]){
			correctPIN = false;
		}
	}
	return correctPIN;
}

char verifyCategory(char usersID[ID_LENGTH], dataBase_t * dataBase)
{
	// checks if ID is on list
	bool IDfound = false;
	int i;
	for(i=0 ; i< (dataBase->top + 1) ; ++i){
		int j;
		bool same = true;
		for(j=0 ; i<ID_LENGTH ; ++i){
			if(dataBase->userList[i].usersID[j] != usersID[j]){
				same = false;
			}
		}
		if(same){
			IDfound = true;
			break;
		}
	}
	return dataBase->userList[i].category;
}
