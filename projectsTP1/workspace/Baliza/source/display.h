/*
 * display.h
 *
 *  Created on: Aug 28, 2019
 *      Author: Ezequiel Vijande
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <stdbool.h>

//Borra el contenido del display
void ClearDisplay(void);

//Imprime el string que recibe en el display.El segundo argumento indica si solo se desean mostrar
//los ultimos simbolos del string tal que el mensaje entre en el display(moving_string=false),
//o si se desea que el mensaje vaya apareciendo en el display de derecha a izquierda(moving_string=true).
void PrintMessage(const char* string, bool moving_string);

//Borra el ultimo caracter impreso en el display
void ClearLast(void);

//Actualiza el contenido del diplay.
void UpdateDisplay(void);

#endif /* DISPLAY_H_ */
