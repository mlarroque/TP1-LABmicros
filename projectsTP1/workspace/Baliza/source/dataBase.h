/*
 * dataBase.h
 *
 *  Created on: Sep 1, 2019
 *      Author: Manuel Mollon
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <stdbool.h>

#define MAX_CANT_USERS	10000
#define ID_LENGTH 8 //Longitud del ID del usuario.
#define PIN_MAX_LENGTH 5 //Longitud maxima del PIN del usuario.
#define PIN_MIN_LENGTH 4 //Longitud minima del PIN del usuario

typedef enum {ADMIN,BASIC}category_name;

typedef enum {SUCCESSFULL,DATABASE_FULL,ID_ALREADY_EXISTS,ID_NOT_FOUND}status;

typedef struct{
	char usersID[ID_LENGTH];
	char usersPIN[PIN_MAX_LENGTH];
	char category;
}user_t;

typedef struct{
	user_t userList[MAX_CANT_USERS];
	int top;
}dataBase_t;

status addUser(user_t newUser, dataBase_t * dataBase);

status removeUser(user_t userToDelete, dataBase_t * dataBase);

bool verifyID(char usersID[ID_LENGTH], dataBase_t * dataBase);

bool verifyPIN(char usersID[ID_LENGTH],char usersPIN[PIN_MAX_LENGTH], dataBase_t * dataBase);

char verifyCategory(char usersID[ID_LENGTH], dataBase_t * dataBase);




#endif /* DATABASE_H_ */
