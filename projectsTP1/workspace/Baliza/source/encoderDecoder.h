/*
 * encoderDecoder.h
 *
 *  Created on: Sep 4, 2019
 *      Author: Lu
 */

#ifndef ENCODERDECODER_H_
#define ENCODERDECODER_H_

#include <stdbool.h>
#include <stdint.h>

#define LOW 0
#define HIGH 1

#define SIGNAL_COUNT	3


typedef enum {COUNT_UP/*clockwise*/, COUNT_DOWN/*counterClockwise*/, NO_CHANGE, ERROR}counter_type; //el ERROR se debe a cambios rápidos de velocidad

typedef struct{
	bool prev_data[SIGNAL_COUNT]; //estados de las señales en el instante anterior para el encoder
	bool curr_data[SIGNAL_COUNT]; //estados de las señales en el instante actual para el encoder
}encoder_t;


void initData(bool value, int signal);
counter_type decodeEncoder(bool value, int signal);
void updateButtonState(bool value);

//Devuelve si se movió en sentido horario (COUNT_UP), antihorario (COUNT_DOWN), si no hubo cambio, o si se movió muy rápido el encoder, generando ERROR
counter_type readRotation(void);

//Devuelve true si se presionó el ENTER (flanco ascendente)
bool checkEnterRisingEdge(void);

//Devuelve true si se dejó de presionar el ENTER (flanco descendente)
bool checkEnterFallingEdge(void);

bool isClockwise(void);
bool isValid(void);
bool wasThereChange(void);



#endif /* ENCODERDECODER_H_ */
