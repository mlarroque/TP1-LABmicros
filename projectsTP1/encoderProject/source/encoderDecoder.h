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
	_Bool prev_data[SIGNAL_COUNT]; //estados de las señales en el instante anterior para el encoder
	_Bool curr_data[SIGNAL_COUNT]; //estados de las señales en el instante actual para el encoder
	_Bool edge_B;
	_Bool edge_A;
}encoder_t;


void resetEdgeFlag(void);
void resetData(void);
void updateData(_Bool value, int signal);
counter_type decodeEncoder();

//Devuelve si se movió en sentido horario (COUNT_UP), antihorario (COUNT_DOWN), si no hubo cambio, o si se movió muy rápido el encoder, generando ERROR
counter_type readRotation(void);


_Bool checkEnterRisingEdge();


_Bool checkEnterFallingEdge(void);

_Bool isClockwise(void);
_Bool isValid(void);
_Bool wasThereChange(void);



#endif /* ENCODERDECODER_H_ */
