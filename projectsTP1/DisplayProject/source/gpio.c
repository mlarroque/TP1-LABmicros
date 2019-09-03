/*
 * gpio.c
 *
 *  Created on: 23 ago. 2019
 *      Author: g5
 */

#include "gpio.h"
#include "MK64F12.h"

// Mux consts
#ifndef GPIO_MUX
#define GPIO_MUX     001
#endif // GPIO_MUX

//Struct Types
#ifndef GPIO_STRUCT
#define GPIO_STRUCT 1
#define PORT_STRUCT 2
#endif //GPIO_STRUCT

_Bool isPinValid(pin_t pin);

void setPCRmux(PORT_Type * p2port, uint8_t numPin, uint8_t mux);

void setPCRpullEnable(PORT_Type * portPointer, uint8_t numPin);

void setPCRpullUp(PORT_Type * portPointer, uint8_t numPin);

void setPCRpullDown(PORT_Type * portPointer, uint8_t numPin);

void setGPIOdataOut(GPIO_Type * gpioPortPointer, uint8_t numPin, _Bool value);

void setGPIOddr(GPIO_Type * p2port, uint8_t numPin, uint32_t mode);

void gpioMode (pin_t pin, uint8_t mode);

void gpioWrite (pin_t pin, _Bool value);

void gpioToggle (pin_t pin);


_Bool gpioRead (pin_t pin);




/**
* @brief Configures the specified pin to behave either as an input or an output
 * @param pin the pin whose mode you wish to set (according PORTNUM2PIN)
 * @param mode INPUT, OUTPUT, INPUT_PULLUP or INPUT_PULLDOWN.
 */
void gpioMode (pin_t pin, uint8_t mode)
{
	uint8_t port = PIN2PORT(pin);
	uint8_t numPin = PIN2NUM(pin);
	PORT_Type * portPointer[] = PORT_BASE_PTRS;
	GPIO_Type * gpioPortPointer[] = GPIO_BASE_PTRS;
	if (isPinValid(pin))  //procedo a configurar el pin siempre que este pertenezca a algunos de los puertos A,B,C,D o E
	{
		//portPointer = (PORT_Type *)getStructAccess(PORT_STRUCT, port);
		//gpioPortPointer = (GPIO_Type *)getStructAccess(GPIO_STRUCT, port);

		setPCRmux(portPointer[port], numPin, GPIO_MUX); //configuro el pin como GPIO modificando el mux del PCR

		if(mode == INPUT_PULLUP || mode == INPUT_PULLDOWN) //se modifica el PCR en caso de que el usuario requiera un pull up/down por software
		{
			setPCRpullEnable(portPointer[port], numPin);
			if (mode == INPUT_PULLUP)
			{
				setPCRpullUp(portPointer[port], numPin);
			}
			else
			{
				setPCRpullDown(portPointer[port], numPin);
			}
			mode = INPUT;

		}
		setGPIOddr(gpioPortPointer[port], numPin, (uint32_t) mode); //configuro el pin como entrada o salida modificando el data direction register (ddr)

	}
}


/**
 * @brief Write a HIGH or a LOW value to a digital pin
 * @param pin the pin to write (according PORTNUM2PIN)
 * @param val Desired value (HIGH or LOW)
 */
void gpioWrite (pin_t pin, _Bool value)
{
	uint8_t port = PIN2PORT(pin);
	uint8_t numPin = PIN2NUM(pin);
	GPIO_Type * gpioPortPointer[] = GPIO_BASE_PTRS;
	uint32_t maskPin = (uint32_t)(1 << numPin);
	//gpioPortPointer = (GPIO_Type *)getStructAccess(GPIO_STRUCT, port);
	if((gpioPortPointer[port]->PDDR) & maskPin)  //Si es un pin de output
	{
		setGPIOdataOut(gpioPortPointer[port], numPin, value);

	}
}

/**
 * @brief Toggle the value of a digital pin (HIGH<->LOW)
 * @param pin the pin to toggle (according PORTNUM2PIN)
 */
void gpioToggle (pin_t pin)
{
	uint8_t port = PIN2PORT(pin);
	uint8_t numPin = PIN2NUM(pin);
	GPIO_Type * gpioPortPointer[] = GPIO_BASE_PTRS;
	//gpioPortPointer = (GPIO_Type *)getStructAccess(GPIO_STRUCT, port);
	uint32_t mask2write = ((uint32_t)(1<<numPin));
	uint32_t mask2delete = ~mask2write;
	gpioPortPointer[port]->PTOR = gpioPortPointer[port]->PTOR & mask2delete;
	gpioPortPointer[port]->PTOR = gpioPortPointer[port]->PTOR | mask2write;
}

/**
 * @brief Reads the value from a specified digital pin, either HIGH or LOW.
 * @param pin the pin to read (according PORTNUM2PIN)
 * @return HIGH or LOW
 */
_Bool gpioRead (pin_t pin)
{
	uint8_t port = PIN2PORT(pin);
	uint8_t numPin = PIN2NUM(pin);
	GPIO_Type * gpioPortPointer[] = GPIO_BASE_PTRS;
	//gpioPortPointer = (GPIO_Type *)getStructAccess(GPIO_STRUCT, port);
	uint32_t mask2read = (uint32_t)(1<<numPin);
	return ((gpioPortPointer[port]->PDIR) & mask2read);

}


_Bool isPinValid(pin_t pin)
{
	_Bool ret = false;
	if((pin >= PORTNUM2PIN(PA,0)) && (pin <= PORTNUM2PIN(PE,31)))
	{
		ret = true;
	}

	return ret;
}

void setPCRmux(PORT_Type * p2port, uint8_t numPin, uint8_t mux)
{
	uint32_t actualPCR = (p2port->PCR)[numPin]; //obtengo el antiguo PCR para luego actualizarlo
	actualPCR = (actualPCR) & (~PORT_PCR_MUX_MASK); //elimino el contenido anterior del mux del PCR
	actualPCR = actualPCR | PORT_PCR_MUX(mux); //ingreso el mux con el contenido deseado por el usuario de esta función
	(p2port->PCR)[numPin] = actualPCR; //finalmente actualizo el PCR

}

void setPCRpullEnable(PORT_Type * portPointer, uint8_t numPin)
{
	uint32_t maskPE = (HIGH << PORT_PCR_PE_SHIFT);
	(portPointer->PCR)[numPin] = ((portPointer->PCR)[numPin] | maskPE);
}
void setPCRpullUp(PORT_Type * portPointer, uint8_t numPin)
{
	uint32_t maskPE = (HIGH << PORT_PCR_PS_SHIFT);
	(portPointer->PCR)[numPin] = ((portPointer->PCR)[numPin] | maskPE);
}
void setPCRpullDown(PORT_Type * portPointer, uint8_t numPin)
{
	uint32_t maskPE = (HIGH << PORT_PCR_PE_SHIFT);
	(portPointer->PCR)[numPin] = ((portPointer->PCR)[numPin] & (~maskPE));
}


void setGPIOddr(GPIO_Type * p2port, uint8_t numPin, uint32_t mode)
{
	uint32_t maskDDR = (mode << numPin);  //mode es 1 o 0 dependiendo si es INPUT o OUTPUT
	p2port->PDDR = ((p2port->PDDR) | maskDDR);

}

void setGPIOdataOut(GPIO_Type * gpioPortPointer, uint8_t numPin, _Bool value)
{
	uint32_t maskDataOut = (uint32_t)(value << numPin);
	uint32_t mask2delete = ~((uint32_t)(1 << numPin));
	gpioPortPointer->PDOR = (gpioPortPointer->PDOR & mask2delete);
	gpioPortPointer->PDOR = (gpioPortPointer->PDOR | maskDataOut);
}
/*
void * getStructAccess(int structType, uint8_t port)
{
	int i;
	void * p2struct = NULL;
	switch(structType)
	{
		case GPIO_STRUCT:
			p2struct = (void *) (GPIOA + port);
			break;
		case PORT_STRUCT:
			p2struct = (void *) (PORTA + port);;
			break;
	}

	return p2struct;

}


//Las funciones que se presentan a continuación pueden ser reemplazadas por "getStructAccess".
GPIO_Type * getGPIOaccess(uint8_t port)
{
	GPIO_Type * gpioPortPointer = GPIOA;
	switch(port)
	{
		case PA: gpioPortPointer = GPIOA;
			//portPointer = PORTA;
			break;
		case PB: gpioPortPointer = GPIOB;
			//portPointer = PORTB;
			break;
		case PC: gpioPortPointer = GPIOC;
			//portPointer = PORTC;
			break;
		case PD: gpioPortPointer = GPIOD;
			//portPointer = PORTD;
			break;
		case PE: gpioPortPointer = GPIOE;
			//portPointer = PORTE;
			break;
	}
	return gpioPortPointer;
}


GPIO_Type * getPORTaccess(uint8_t port)
{
	PORT_Type * portPointer = PORTA;
	switch(port)
	{
		case PA: //gpioPortPointer = GPIOA;
			portPointer = PORTA;
			break;
		case PB: //gpioPortPointer = GPIOB;
			portPointer = PORTB;
			break;
		case PC: //gpioPortPointer = GPIOC;
			portPointer = PORTC;
			break;
		case PD: //gpioPortPointer = GPIOD;
			portPointer = PORTD;
			break;
		case PE: //gpioPortPointer = GPIOE;
			portPointer = PORTE;
			break;
	}
	return portPointer;
}

*/
