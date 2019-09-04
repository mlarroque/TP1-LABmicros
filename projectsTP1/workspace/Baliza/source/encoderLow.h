/*
 * encoderDRV.h
 *
 *  Created on: Sep 3, 2019
 *      Author: Lu
 */

#ifndef ENCODERLOW_H_
#define ENCODERLOW_H_

#include <stdbool.h>

/******************************************************************************************
 *  				TIPOS DE DATOS, CONSTANTES Y VARIABLES GLOBALES
 ******************************************************************************************/
typedef enum {A, B, C, ENC_SIGNAL_COUNT}encoder_signal;
typedef void (*callback_ptr)(void);


/********************************************************************************************
 * 										FUNCIONES
 ********************************************************************************************/
void initializeEncoderLow(void);
bool readEncoderSignalX(encoder_signal);

#endif /* ENCODERLOW_H_ */

