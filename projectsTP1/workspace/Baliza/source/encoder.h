/*
 * encoder.h
 *
 * Header con las definiciones de las funciones necesarias
 * para interpretar lo ingresado por el usuario mediante el encoder.
 *
 *
 *  Created on: Aug 31, 2019
 *      Author: Lu
 */

#ifndef ENCODER_H_
#define ENCODER_H_


/******************************************************************************
 *									DEFINICIONES
 ******************************************************************************/
#define LOW 0
#define HIGH 1

typedef enum {UP, DOWN, BACK, ENTER, CANCEL}enc_type;

typedef struct{
	enc_type input;
}encoderUd_t;

typedef struct{
	int top; 			//contador de eventos
	encoderUd_t event;
}encoderQueue_t;

/******************************************************************************
 *							FUNCIONES DEL HEADER
 ******************************************************************************/
void initializeEncoder(void);


encoderQueue_t popEvent(void);
encoderQueue_t getEncoderQueue(void);



#endif /* ENCODER_H_ */
