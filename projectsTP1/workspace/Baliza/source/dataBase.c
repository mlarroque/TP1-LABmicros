/*
 * dataBase.c
 *
 *  Created on: Sep 1, 2019
 *      Author: Manuel Mollon
 */

#include "dataBase.h"
#include <stdbool.h>

static dataBase_t dataBase;

void initializeDataBase(void)
{
	dataBase.top = -1;
	user_t newUser = {{0,1,2,3,4,5,6,7},{1,2,3,4,5},ADMIN};
	addUser(newUser);
}

void changePIN(char usersID[ID_LENGTH], char usersNewPIN[PIN_MAX_LENGTH])
{
	// checks if ID is on list
	bool IDfound = false;
	int i;
	for(i=0 ; i< (dataBase.top + 1) ; ++i){
		int j;
		bool same = true;
		for(j=0 ; i<ID_LENGTH ; ++i){
			if(dataBase.userList[i].usersID[j] != usersID[j]){
				same = false;
			}
		}
		if(same){
			IDfound = true;
			break;
		}
	}
	int j;
	for(i=0;i<PIN_MAX_LENGTH;++i){
		dataBase.userList[i].usersPIN[j] = usersNewPIN[j];
	}
}

status addUser(user_t newUser)
{
	if(dataBase.top == MAX_CANT_USERS-1){ // user overflow
		return DATABASE_FULL;
	}
	else{
		// checks if ID already on list
		bool IDused = verifyID(newUser.usersID);
		if(!IDused)
		{
			// if not on list, user is added
			dataBase.top += 1;
			dataBase.userList[dataBase.top] = newUser;
			return SUCCESSFULL;
		}
		else
		{
			return ID_ALREADY_EXISTS;
		}
	}
}

status removeUser(user_t userToDelete)
{
		// checks if ID is on list
		bool IDfound = false;
		int i; //position where ID is, if found
		for(i=0 ; i< (dataBase.top + 1) ; ++i){
			int j;
			bool same = true;
			for(j=0 ; i<ID_LENGTH ; ++i){
				if(dataBase.userList[i].usersID[j] != userToDelete.usersID[j]){
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
			user_t topUser = dataBase.userList[dataBase.top];
			dataBase.userList[i] = topUser; // overwrites user to be removed
			dataBase.top -= 1; // decrements top pointer
			return SUCCESSFULL;
		}
		else
		{
			return ID_NOT_FOUND;
		}
}

bool verifyID(char usersID[ID_LENGTH])
{
	// checks if ID is on list
	bool IDfound = false;
	int i;
	for(i=0 ; i< (dataBase.top + 1) ; ++i){
		int j;
		bool same = true;
		for(j=0 ; i<ID_LENGTH ; ++i){
			if(dataBase.userList[i].usersID[j] != usersID[j]){
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

bool verifyPIN(char usersID[ID_LENGTH], char usersPIN[PIN_MAX_LENGTH])
{
	// checks if ID is on list
	bool IDfound = false;
	int i,j;
	for(i=0 ; i< (dataBase.top + 1) ; ++i){
		int j;
		bool same = true;
		for(j=0 ; i<ID_LENGTH ; ++i){
			if(dataBase.userList[i].usersID[j] != usersID[j]){
				same = false;
			}
		}
		if(same){
			IDfound = true;
			break;
		}
	}
	bool correctPIN = true;
	for(j=0 ; j<PIN_MAX_LENGTH ; ++j){
		if(dataBase.userList[i].usersPIN[j] != usersPIN[j]){
			correctPIN = false;
		}
	}
	return correctPIN;
}

char verifyCategory(char usersID[ID_LENGTH])
{
	// checks if ID is on list
	bool IDfound = false;
	int i;
	for(i=0 ; i< (dataBase.top + 1) ; ++i){
		int j;
		bool same = true;
		for(j=0 ; i<ID_LENGTH ; ++i){
			if(dataBase.userList[i].usersID[j] != usersID[j]){
				same = false;
			}
		}
		if(same){
			IDfound = true;
			break;
		}
	}
	return dataBase.userList[i].category;
}
