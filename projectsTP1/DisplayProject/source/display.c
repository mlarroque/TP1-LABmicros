/*
 * display.c
 *
 *  Created on: Aug 31, 2019
 *      Author: G5
 */
#include "display.h"
#include "SegmentDisplay.h"
#include "timer.h"
#include "queue.h"

#define STRING_TIME 375 //Delay en ms entre cada shifteo hacia la izquierda.
#define FPS 60 //Frames per second
#define MS_BETWEEN_SYMBOLS ( (1000/FPS)/(DISPLAY_SIZE) )
/******************************************************************************
 *
 * 							VARIABLES GLOBALES
 *
 ******************************************************************************/
static const char* current_string;
static unsigned int string_position;
static unsigned int display_position;
static unsigned int string_size;
static bool initialized = false;
static bool need_update; //FLAG DE DEBUGGEO

/*******************************************************************************
 *
 * 							FUNCIONES LOCALES
 *
 *******************************************************************************/
unsigned int GetStringSize(const char* str);
void GenerateDisplayEv(void);

/******************************************************************************
 *
 *							FUNCIONES DEL HEADER
 *
 ******************************************************************************/

void InitializeDisplay(void)
{
	if(!initialized)
	{
		InitializeSegmentDisplay();
		InitializeTimers();
		ClearDisplay();
		SetTimer(DISPLAY, MS_BETWEEN_SYMBOLS, &GenerateDisplayEv);
		SetTimer(MESSAGE,STRING_TIME, &ShiftLeft);//Setteo el timer con la velocidad de movimiento del string.
		DisableTimer(MESSAGE); //Por default asumo que se desea un mensaje que nose mueva a traves del display.
		need_update = false; //SOLO PARA DEBUGGEO
		initialized = true;
	}
}
void ClearDisplay(void)
{
	current_string = "";
	string_position = 0;
	display_position = 0;
	string_size = -1;
}
void PrintMessage(const char* string, bool moving_string)

{
	ClearDisplay();
	string_size = INT_FAST8_MAX; //Asumo que el string es de largo 'infinito'.

	if(!moving_string) //Solo muestro los ultimos caracteres que entran
	{
		DisableTimer(MESSAGE);//Deshabilito el timer
		string_size = GetStringSize(string);
		if(string_size > DISPLAY_SIZE)
		{
			current_string = string +(string_size - DISPLAY_SIZE);
		}
		else
		{
			current_string = string;
		}
		string_position = 0;
		display_position = 0;

	}
	else
	{
		current_string = string;
		string_position = 0;
		display_position = DISPLAY_SIZE-1; //El mensaje se mueve de derecha a izquierda.
		EnableTimer(MESSAGE);
	}
}

void ShiftLeft(void)
{
	string_position++;
}

void UpdateDisplay(void)
{
	if(string_position < 0)
	{
		PrintChar(' ',display_position); //Imprimo espacio en blanco
	}
	else
	{
		if(string_position > string_size)
		{
			PrintChar(' ',display_position);
		}
		else if(current_string[string_position] == '\0')
		{
			string_size = string_position;
			PrintChar(' ',display_position);
		}
		else
		{
			PrintChar(current_string[string_position],display_position);
		}
	}
	string_position++;
	display_position++;
	if(display_position == DISPLAY_SIZE)
	{
		string_position -= DISPLAY_SIZE;
		display_position -= DISPLAY_SIZE;
	}
	need_update = false; //SOLO PARA DEBUGGEOOOOO
}

bool GetNeedUpdate(void)
{
	return need_update;
}

/*******************************************************************************
 *
 * 							FUNCIONES LOCALES
 *
 *******************************************************************************/

unsigned int GetStringSize(const char* str)
{
	unsigned int size = 0;
	while (str[size++] != '\0');
	return --size;
}

void GenerateDisplayEv(void)
{
	need_update = true;
}

