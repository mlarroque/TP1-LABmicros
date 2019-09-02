/*
 * encoder.h
 *
 * Header con las definiciones de las funciones necesarias
 * para interpretar lo ingresado por el usuario mediante el encoder.
 *
 * El encoder envía tres señales, A, B y C, siendo C el ENTER
 * y A/B las propias de la rotación, desfasadas 90°.
 *If A leads B, for example, the disk is rotating in a clockwise direction. If B leads A, then the disk is rotating in a counter-clockwise direction.
 *
 *  Created on: Aug 31, 2019
 *      Author: Lu
 */

#ifndef ENCODER_H_
#define ENCODER_H_


#define LOW 0
#define HIGH 1

typedef enum {A, B, C, ENC_SIGNAL_COUNT}encoder_signal;
//typedef enum {A_HIGH, A_LOW, B_HIGH, B_LOW, C_HIGH, C_LOW}encoder_type;
typedef enum {COUNT_UP/*clockwise*/, COUNT_DOWN/*counterClockwise*/, NO_CHANGE, ERROR}counter_type; //el ERROR se debe a cambios rápidos de velocidad

_Bool IsClockwise(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT]);
_Bool IsCounterClockwise(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT]);

counter_type ReadInput(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT]);

//Devuelve true si se presionó el ENTER (flanco ascendente)
_Bool CheckEnter(_Bool prev_data[ENC_SIGNAL_COUNT], _Bool curr_data[ENC_SIGNAL_COUNT]);

void SetCancelAttemptTimer();





#endif /* ENCODER_H_ */
