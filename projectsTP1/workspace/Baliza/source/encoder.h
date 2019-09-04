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


/******************************************************************************
 *									DEFINICIONES
 ******************************************************************************/
#ifndef LOW
#define LOW 0
#define HIGH 1

typedef enum {COUNT_UP/*clockwise*/, COUNT_DOWN/*counterClockwise*/, NO_CHANGE, ERROR}counter_type; //el ERROR se debe a cambios rápidos de velocidad
typedef enum {UP, DOWN, ENTER, CANCEL}enc_type;

typedef struct{
	enc_type input;
}encoderUd_t;

/******************************************************************************
 *							FUNCIONES DEL HEADER
 ******************************************************************************/
void initializeEncoder(void);
enc_type readInput();


//Devuelve si se movió en sentido horario (COUNT_UP), antihorario (COUNT_DOWN), si no hubo cambio, o si se movió muy rápido el encoder, generando ERROR
counter_type readRotation(bool prev_data[ENC_SIGNAL_COUNT], bool curr_data[ENC_SIGNAL_COUNT]);

//Devuelve true si se presionó el ENTER (flanco ascendente)
bool checkEnterRisingEdge(bool prev_data[ENC_SIGNAL_COUNT], bool curr_data[ENC_SIGNAL_COUNT]);

//Devuelve true si se dejó de presionar el ENTER (flanco descendente)
bool checkEnterFallingEdge(bool prev_data[ENC_SIGNAL_COUNT], bool curr_data[ENC_SIGNAL_COUNT]);






#endif /* ENCODER_H_ */
