/*
 * 7SegmentDisplay.c
 *
 *  Created on: Sep 1, 2019
 *      Author: G5
 */


#include "SegmentDisplay.h"
#include "gpio.h"
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
#define CSEGA PORTNUM2PIN(PC,3)// PTC3
#define CSEGB PORTNUM2PIN(PC,2)// PTC2
#define CSEGC PORTNUM2PIN(PA,2)// PTA2
#define CSEGD PORTNUM2PIN(PB,23)// PTB23
#define CSEGE PORTNUM2PIN(PA,1)// PTA1
#define CSEGF PORTNUM2PIN(PB,9)// PTB9
#define CSEGG PORTNUM2PIN(PC,17)// PTC17
#define CSEGDP PORTNUM2PIN(PC,16)// PTC16
#define SEL1 PORTNUM2PIN(PC,4)// PTC4
#define SEL2 PORTNUM2PIN(PA,0)// PTA0

/**************************************************************************
 * 								MASCARAS
 **************************************************************************/
#define DP_MASK 0x80
#define G_MASK 0x40
#define F_MASK 0x20
#define E_MASK 0x10
#define D_MASK 0x08
#define C_MASK 0x04
#define B_MASK 0x02
#define A_MASK 0x01

/**************************************************************************
 * 							FUNCIONES LOCALES
 **************************************************************************/

//Recibe que segmentos prender en value, y que digito se desea prender en
//select_line.
//interpreto los bits de value como:
	//b7	b6	b5	b4	b3	b2	b1	b0
	//dp	g	f	e	d	c	b	a
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

/**************************************************************************
 * 							FUNCIONES LOCALES
 **************************************************************************/

//Recibe que segmentos prender en value, y que digito se desea prender en
//select_line.
void SetDigit(const unsigned char value,unsigned int select_line)
{
	//Actualizo el valor de cada segmento
		//Segmento G
		if( value & G_MASK )
		{
			gpioWrite(CSEGG, HIGH);
		}
		else
		{
			gpioWrite(CSEGG, LOW);
		}
		//Segmento F
		if( value & F_MASK )
		{
			gpioWrite(CSEGF, HIGH);
		}
		else
		{
			gpioWrite(CSEGF, LOW);
		}
		//Segmento E
		if( value & E_MASK )
		{
			gpioWrite(CSEGE, HIGH);
		}
		else
		{
			gpioWrite(CSEGE, LOW);
		}
		//Segmento D
		if( value & D_MASK )
		{
			gpioWrite(CSEGD, HIGH);
		}
		else
		{
			gpioWrite(CSEGD, LOW);
		}
		//Segmento C
		if( value & C_MASK )
		{
			gpioWrite(CSEGC, HIGH);
		}
		else
		{
			gpioWrite(CSEGC, LOW);
		}
		//Segmento B
		if( value & B_MASK )
		{
			gpioWrite(CSEGB, HIGH);
		}
		else
		{
			gpioWrite(CSEGB, LOW);
		}
		//Segmento A
		if( value & A_MASK )
		{
			gpioWrite(CSEGA, HIGH);
		}
		else
		{
			gpioWrite(CSEGA, LOW);
		}
	//Selecciono el digito del display a escribir

}


