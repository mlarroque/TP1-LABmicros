/*
 * encoderLow.h
 *
 *  Created on: Sep 3, 2019
 *      Author: Lu
 */

#ifndef ENCODERHAL_H_
#define ENCODERHAL_H_

#include <stdbool.h>

/******************************************************************************************
 *  				TIPOS DE DATOS, CONSTANTES Y VARIABLES GLOBALES
 ******************************************************************************************/
typedef enum {A, B, C, ENC_SIGNAL_COUNT}encoder_signal;
typedef void (*callback_ptr)(void);


/********************************************************************************************
 * 										FUNCIONES
 ********************************************************************************************/
void initializeEncoderHAL(void);
void setSignalCallback (void (*funcallback)(void), encoder_signal);
bool readEncoderSignalX(encoder_signal);
void resetEncoderTimerCount(void);
//void setEnterCallback(void (*funcallback)(void));
//void setBackCallback(void (*funcallback)(void));
//void setCancelCallback(void (*funcallback)(void));

#endif /* ENCODERHAL_H_ */

