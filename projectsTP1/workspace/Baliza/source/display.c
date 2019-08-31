/*
 * display.c
 *
 *  Created on: Aug 31, 2019
 *      Author: Ezequiel Vijande
 */
#include "display.h"

#define DISPLAY_SIZE 4
/******************************************************************************
 *
 * 							VARIABLES GLOBALES
 *
 ******************************************************************************/
static const char* current_string;
static unsigned int string_position;
static unsigned int display_position;
static bool moving_message;

/*******************************************************************************
 *
 * 							FUNCIONES AUXILIARES
 *
 *******************************************************************************/

void PrintChar(const char c,unsigned int pos);
void ShiftLeft(const char c); //desplaza todos los caracteres una posicion hacia la izquierda y agrega c.
unsigned int GetStringSize(const char* str);

/******************************************************************************
 *
 *							FUNCIONES DEL HEADER
 *
 ******************************************************************************/
void ClearDisplay(void)
{
	int i;
	for(i=0; i<DISPLAY_SIZE; i++)
	{
		PrintChar(' ', i);
	}
	moving_message = false;
	current_string = "";
	string_position = 0;
	display_position = 0;
}
void PrintMessage(const char* string, bool moving_string)

{
	ClearDisplay();

	if(!moving_String) //Solo muestro los ultimos caracteres que entran
	{
		moving_message = false;
		unsigned int size = GetStringSize(string);
		if(size > DISPLAY_SIZE)
		{
			current_string = string +(size - DISPLAY_SIZE);
		}
		else
		{
			current_string = string;
		}
		string_position = 0;
		display_position = 0;
		int i=0;
		while(current_string[i] != '\0')
		{
			PrintChar(current_string[i++], display_position++);
		}

	}
	else
	{
		moving_message = true;
		current_string = string;
		string_position = 0;
		display_position = DISPLAY_SIZE-1; //El mensaje se mueve de derecha a izquierda.
	}
}

/*******************************************************************************
 *
 * 							FUNCIONES AUXILIARES
 *
 *******************************************************************************/

unsigned int GetStringSize(const char* str)
{
	unsigned int size = 0;
	while (str[size++] != '\0');
	return --size;
}
