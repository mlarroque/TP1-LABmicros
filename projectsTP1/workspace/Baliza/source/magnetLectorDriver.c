//magnetLectorDriver.c

#include "gpio.h"
#include "magnetCardDecode.h"

//DEBUG
#include "board.h"
//////////

#define CLOCK_PIN PORTNUM2PIN(PC, 9) //cable verde
#define DATA_PIN PORTNUM2PIN(PC, 7)  //cable azul
#define ENABLE_PIN PORTNUM2PIN(PC, 5) //cable amarillo

void clockRoutine(void);

void enableRoutine(void);

void debugSwitchRoutine(void);

_Bool hwLectorIsInit = false;
_Bool enable = false;

uint32_t counterDataIn = 0;

bufferMagnetDataEncoded_Type bufferDataEncoded[DATA_LEN];
bufferMagnetDataDecoded_Type bufferDataDecoded[DATA_LEN];

void hwLectorInit(void)
{
	if (!hwLectorIsInit)
	{

		gpioMode(CLOCK_PIN , INPUT_PULLUP);  //inicialización de señales del lector
		gpioMode(DATA_PIN, INPUT_PULLUP);
		gpioMode(ENABLE_PIN, INPUT_PULLUP);

		gpioIRQ(ENABLE_PIN, GPIO_IRQ_MODE_BOTH_EDGES, (pinIrqFun_t) enableRoutine);
		enable = false;
		//DEBUG
		gpioMode(PIN_LED_RED, OUTPUT);
		gpioMode(PIN_LED_BLUE, OUTPUT);
		gpioMode(PIN_LED_GREEN, OUTPUT);
		gpioMode(PIN_SW3, SW_INPUT_TYPE);

		gpioIRQ(PIN_SW3, GPIO_IRQ_MODE_RISING_EDGE, (pinIrqFun_t) debugSwitchRoutine);
		gpioWrite(PIN_LED_RED, HIGH); //el led arranca apagado (es activo bajo)
		gpioWrite(PIN_LED_GREEN, HIGH); //el led arranca apagado (es activo bajo)
		gpioWrite(PIN_LED_BLUE, HIGH);
	}

}

void clockRoutine(void)
{
	if(counterDataIn < DATA_LEN)  //si queda lugar en el buffer, sigo ingresando datos
	{
		bufferDataEncoded[counterDataIn] = !gpioRead(DATA_PIN);  //activo bajo
		counterDataIn++;
	}

}

void enableRoutine(void)
{
	enable = !enable;
	//gpioToggle(PIN_LED_BLUE);
	if(enable) //se comienza a leer la tarjeta
	{
		counterDataIn = 0;
		//gpioToggle(PIN_LED_RED); //se apaga el led (es activo bajo)
		gpioIRQ(CLOCK_PIN, GPIO_IRQ_MODE_FALLING_EDGE, (pinIrqFun_t) clockRoutine);

		//DEBUG
		//gpioToggle(PIN_LED_RED); //se apaga el led (es activo bajo)
	}
	else
	{
		//gpioToggle(PIN_LED_RED);
		gpioIRQ(CLOCK_PIN, GPIO_IRQ_MODE_DISABLE, (pinIrqFun_t) clockRoutine);
		if(magnetDataParser(bufferDataEncoded, bufferDataDecoded))  //si los datos ingresados son correctos
		{
			//HAY QUE GUARDAR LA DATA DECODEDDDDDDDDDDD
			//DEBUG
			//gpioToggle(PIN_LED_RED); //se prende el led (es activo alto)
			gpioToggle(PIN_LED_GREEN); //se prende el led (es activo alto)
		}
	}
}


void debugSwitchRoutine(void)
{
	gpioToggle(PIN_LED_BLUE);
}
