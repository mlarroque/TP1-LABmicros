/*
 * display.c
 *
 *  Created on: Aug 31, 2019
 *      Author: G5
 */
#include "display.h"
#include "SegmentDisplay.h"
#include "timer.h"

#define STRING_TIME 375000 //Delay en us entre cada shifteo hacia la izquierda.
#define FPS 60 //Frames per second
#define MIN_BRIGHTNESS 1
#define MAX_BRIGHTNESS 10
#define US_BETWEEN_SYMBOLS ( (1000000/FPS)/(DISPLAY_SIZE) )
/******************************************************************************
 *
 * 							VARIABLES GLOBALES
 *
 ******************************************************************************/
static const char* current_string;
static unsigned int string_position;
static unsigned int display_position;
static unsigned int string_size;
static unsigned char brigthness;
static bool brightness_ev; //Indica que se debe apagar el ultimo simbolo enviado al display
static bool initialized = false;
static dispalyQueue_t display_queue;

/*******************************************************************************
 *
 * 							FUNCIONES LOCALES
 *
 *******************************************************************************/
unsigned int GetStringSize(const char* str);
void GenerateDisplayEv(void);
void GenerateBrightnessEv(void);

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
		SetTimer(DISPLAY, US_BETWEEN_SYMBOLS, &GenerateDisplayEv);
		SetTimer(MESSAGE,STRING_TIME, &ShiftLeft);//Setteo el timer con la velocidad de movimiento del string.
		DisableTimer(MESSAGE); //Por default asumo que se desea un mensaje que nose mueva a traves del display.
		brigthness = MAX_BRIGHTNESS; //Por default comienza con la intensidad del display al maximo.
		brightness_ev = false;
		display_queue.curr_ev = 0;
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

void SetBrightness(unsigned char brightness_factor)
{
	if( (brightness_factor >= MIN_BRIGHTNESS) && (brightness_factor <= MAX_BRIGHTNESS) )
	{
		brigthness = brightness_factor;

	}
}

void UpdateDisplay(void)
{
	if(!brightness_ev) //Escribo el digito que sigue en el display
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
					if(string_position == (string_size + DISPLAY_SIZE) ) //Si se mostro todo el mensaje, vuelve a pasarlo.
					{
						string_position = -1;
						display_position = DISPLAY_SIZE-2;
					}
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
			SetTimer(DISPLAY_INTENSITY, (brigthness/MAX_BRIGHTNESS)*US_BETWEEN_SYMBOLS, &GenerateBrightnessEv);
	}
	else //Apago el ultimo simbolo enviado
	{
		if( (display_position-1) < 0 )
		{
			PrintChar(' ',DISPLAY_SIZE-1);
		}
		else
		{
			PrintChar(' ',display_position-1);
		}
		brightness_ev = false;
	}
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
	//event_t new_ev = {TIMER_EV,};
	//Pongo el evento en la cola
}

void GenerateBrightnessEv(void)
{
	DisableTimer(DISPLAY_INTENSITY);
	//Pongo evento de display en la cola
	brightness_ev = true;
}
