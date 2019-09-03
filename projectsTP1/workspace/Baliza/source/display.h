/*
 * display.h
 *
 *  Created on: Aug 28, 2019
 *      Author: G5
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <stdbool.h>
#include <stdint.h>
#define DISPLAY_SIZE 4

//Inicializa los recursos necesrios para utilizar el display
void InitializeDisplay(void);

//Borra el contenido del display
void ClearDisplay(void);

//Imprime el string que recibe en el display.El segundo argumento indica si solo se desean mostrar
//los ultimos simbolos del string tal que el mensaje entre en el display(moving_string=false),
//o si se desea que el mensaje vaya apareciendo en el display de derecha a izquierda(moving_string=true).
void PrintMessage(const char* string, bool moving_string);

//Borra el ultimo caracter impreso en el display
void ClearLast(void);

//desplaza todos los caracteres una posicion hacia la izquierda y agrega c.
void ShiftLeft(void);

//Actualiza el contenido del diplay.
void UpdateDisplay(void);

#endif /* DISPLAY_H_ */
