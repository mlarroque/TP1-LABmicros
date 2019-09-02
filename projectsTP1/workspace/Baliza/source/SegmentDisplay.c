/*
 * 7SegmentDisplay.c
 *
 *  Created on: Sep 1, 2019
 *      Author: G5
 */


#include "SegmentDisplay.h"
#define NUMBER_OF_DIGITS 4
/**************************************************************************
 * VARIABLES Y DEFINICIONES
 **************************************************************************/

//Arreglo que guarda que segmentos prender para los numeros del 0-9.
//Esta ordenado tal que el primer elemento corresponde al '0' y el ultimo
//al '9'.
static const unsigned char number_segment_array[]=
{		//0		1	 2		3	 4		5	 6		7	 8		9
		0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};
static const unsigned char letters_segment_array[]=
{		//A		B	  C		D	  E		F	  G		H	 I		J
		0x37, 0x7F, 0x39, 0x5E, 0x79, 0x71, 0x7D, 0x76, 0x06, 0x0E,
		//K		L	 M		N	 O		P	 Q		R	 S		T
		0x76, 0x38, 0x37, 0x54, 0x3F, 0x73, 0x67, 0x31, 0x6D, 0x07,
		//U		V	 W		X	 Y		Z
		0x3E, 0x1C, 0x76, 0x76, 0x66, 0x5B
};
/**************************************************************************
 * 							FUNCIONES LOCALES
 **************************************************************************/

//Recibe que segmentos prender en value, y que digito se desea prender en
//select_line.
void SetDigit(const unsigned char value,unsigned int select_line);

/**************************************************************************
 * 							FUNCIONES DEL HEADER
 **************************************************************************/
void PrintChar(const char c,unsigned int pos)
{
	if( pos< NUMBER_OF_DIGITS )
	{
		if( (c >= '0') && (c <= '9') )
		{
			SetDigit(number_segment_array[c-'0'],pos);
		}
		else if( (c >= 'A') && (c <= 'Z') )
		{
			SetDigit(number_segment_array[c-'A'],pos);
		}
		else if( (c >= 'a') && (c <= 'z') )
		{
			SetDigit(number_segment_array[c-'a'],pos);
		}
	}
}


