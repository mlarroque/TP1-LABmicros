/***************************************************************************//**
  @file     magnetCardDecode.c
  @brief    Magnet card decoding functions
  @author   G5
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "magnetCardDecode.h"
#include "cardStandard.h"
#include <stdbool.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define BITS_CAPACITY 32
#if BITS_CAPACITY >= 32
#define UINT_T uint32_t
#else
#define UINT_T unit8_t
#endif

#define MAX_DATA_LEN DATA_LEN

#define NO_TRACK 255
#define TRACK1 0
#define TRACK2 1
#define TRACK3 2




typedef struct{

UINT_T nBits;
UINT_T nBitsPerChar;
UINT_T nChars;
UINT_T parity;
bufferMagnetDataEncoded_Type ssSymbol;
bufferMagnetDataEncoded_Type fsSymbol;
bufferMagnetDataEncoded_Type esSymbol;
bufferMagnetDataEncoded_Type minValue;
bufferMagnetDataEncoded_Type maxValue;
bufferMagnetDataEncoded_Type asciiOffset;

}trackXdata_t;



/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

uint8_t getTrackShaped(bufferMagnetDataEncoded_Type * bufferDataIn);

_Bool identifyCardSymbol(bufferMagnetDataEncoded_Type * bufferDataIn, UINT_T indexStart, 
                UINT_T indexLimit, bufferMagnetDataEncoded_Type symbol, uint8_t symbolSize, UINT_T * indexFounded, uint8_t step);

void shapeMagnetTrack(bufferMagnetDataEncoded_Type * bufferDataIn, UINT_T indexStart, UINT_T indexEnd);

void initializeTrackAsTRACK1(trackXdata_t * trackData);
void initializeTrackAsTRACK2(trackXdata_t * trackData);
void initializeTrackAsTRACK3(trackXdata_t * trackData);

_Bool decodeTrackX(bufferMagnetDataEncoded_Type * bufferDataIn, bufferMagnetDataDecoded_Type * bufferDataOut, 
                                                                                        trackXdata_t * p2trackData);

//

/*******************************************************************************
 *******************************************************************************
                        GLOBAL VARS
 *******************************************************************************
 ******************************************************************************/


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
_Bool magnetDataParser(bufferMagnetDataEncoded_Type * bufferDataIn, bufferMagnetDataDecoded_Type * bufferDataOut)
{
    _Bool dataErrorReport = false;

    trackXdata_t trackData;
    int trackNumber = getTrackShaped(bufferDataIn);

    switch(trackNumber)
    {
        case TRACK1:
            initializeTrackAsTRACK1(&trackData);
            break;
        case TRACK2:
            initializeTrackAsTRACK2(&trackData);
            break;
        case TRACK3:
            initializeTrackAsTRACK3(&trackData);
            break;
        default:  //si no es ninguno de los tracks, hay un error en la data ingresada por el lector de banda magnética
            dataErrorReport = true;
            break;
    }
    if(!dataErrorReport)
    {
        dataErrorReport = !decodeTrackX(bufferDataIn, bufferDataOut, &trackData);
    }

    return !dataErrorReport;
}

uint8_t getTrackShaped(bufferMagnetDataEncoded_Type * bufferDataIn)
{
    uint8_t ntrackFounded = NO_TRACK; //inicializo como NO_TRACK, pero actualizo si es posible identificar un track
    UINT_T indexStartSentinel = 0;
    UINT_T indexEndSentinel = 0;
    UINT_T indexFinalBit = 0;  //en este entero se guardará el indice del último elemento (bit) que forma parte del track

    if(identifyCardSymbol(bufferDataIn, 0, MAX_DATA_LEN/2, START_SENTINEL_TRACK2, SIZE_OF_CHARS_TRACK2, &indexStartSentinel, 1) && 
        identifyCardSymbol(bufferDataIn, indexStartSentinel, indexStartSentinel + NUMBER_OF_BITS_TRACK2 - 1, END_SENTINEL_TRACK2, SIZE_OF_CHARS_TRACK2, &indexEndSentinel, SIZE_OF_CHARS_TRACK2))
    {  //si se indentifica ss y espara track2
        ntrackFounded = TRACK2;
        indexFinalBit = indexEndSentinel + (2*SIZE_OF_CHARS_TRACK2) - 1; //desde el inicio de es, se debe sumar el tamaño de
                                                                        //es y el tamaño de LRC.
    }
    else if(identifyCardSymbol(bufferDataIn, 0, MAX_DATA_LEN/2, START_SENTINEL_TRACK1, SIZE_OF_CHARS_TRACK1, &indexStartSentinel, 1) &&
            identifyCardSymbol(bufferDataIn, indexStartSentinel, indexStartSentinel + NUMBER_OF_BITS_TRACK1 - 1, END_SENTINEL_TRACK1, SIZE_OF_CHARS_TRACK1, &indexEndSentinel, SIZE_OF_CHARS_TRACK1))
    {  //si se identifica ss  es para track1
        
        ntrackFounded = TRACK1;
        indexFinalBit = indexEndSentinel + (2*SIZE_OF_CHARS_TRACK1) - 1; //desde el inicio de es, se debe sumar el tamaño de
                                                              //es y el tamaño de LRC.
    }
    else if(identifyCardSymbol(bufferDataIn, 0, MAX_DATA_LEN/2, START_SENTINEL_TRACK3, SIZE_OF_CHARS_TRACK3, &indexStartSentinel, 1) &&
            identifyCardSymbol(bufferDataIn, indexStartSentinel, indexStartSentinel + NUMBER_OF_BITS_TRACK3 - 1, END_SENTINEL_TRACK3, SIZE_OF_CHARS_TRACK3, &indexEndSentinel, SIZE_OF_CHARS_TRACK3))
    {   //si se identifica ss y es para track3
        ntrackFounded = TRACK3;
        indexFinalBit = indexEndSentinel + (2*SIZE_OF_CHARS_TRACK1) - 1; //desde el inicio de es, se debe sumar el tamaño de
        
    }

    if(ntrackFounded != NO_TRACK)
    {
        shapeMagnetTrack(bufferDataIn, indexStartSentinel, indexFinalBit);
    }
    return ntrackFounded;
}

_Bool identifyCardSymbol(bufferMagnetDataEncoded_Type * bufferDataIn, UINT_T indexStart, UINT_T indexLimit, bufferMagnetDataEncoded_Type symbol, uint8_t symbolSize, UINT_T * indexFounded, uint8_t step)
{
    UINT_T i, j;
    bufferMagnetDataEncoded_Type value;
    _Bool symbolFounded = false;
    if(indexLimit > (indexStart + symbolSize - 1))
    {
        for(i = indexStart; ( i <= (indexLimit - symbolSize + 1) ) && ( !symbolFounded ); i += step)  //se recorre data encoded
        {
            value = 0; //inicio de cero cada vez que busco símbolo
            for(j = 0; j < (symbolSize - 1); j++) //se compara data con el simbolo en cuestión
            {
                value += (bufferDataIn[i+j] << j);  //sumo las j-esimas potencias de 2 (primero se envían los bits más significativos).
            }
            if(value == (symbol)) //al salir del bucle for, i+j hace referencia al
            {                                                 //índice del bit de paridad. Si se da la paridad, y además 
                                                        //se da con el valor buscado, se ha encontrado el símbolo.
                symbolFounded = true;
                *indexFounded = i;
            }
        }
    }
    
    return symbolFounded;
}

void shapeMagnetTrack(bufferMagnetDataEncoded_Type * bufferDataIn, UINT_T indexStart, UINT_T indexEnd)
{
    UINT_T i;
    if(indexStart > 0)
    {
        for(i = 0; i <= (indexEnd - indexStart); i++)
        {
            bufferDataIn[i] = bufferDataIn[i + indexStart];
        }
    }
    
}


_Bool decodeTrackX(bufferMagnetDataEncoded_Type * bufferDataIn, bufferMagnetDataDecoded_Type * bufferDataOut, trackXdata_t * p2trackData)
{
    UINT_T i, j, charCounter = 0;
    bufferMagnetDataEncoded_Type controlParity, value;
    bufferMagnetDataEncoded_Type controlLRC;
    uint8_t k, indicatorsCounter = 0;  //vale 0 si no llego ningun counter, cambia a 1 cuando llega ss,
                                //cambia 2 si llega fs, a 3 si llega  es (da lugar a corroborar LRC).
    _Bool dataFailed = false;
    _Bool data2saveFlag = false;
    _Bool messageHasFinished = false;

    //inicializo controLRC
    controlLRC = 0;
    for (k = 0; k < (p2trackData->nBitsPerChar - 1); k++)
    {
        controlLRC += (p2trackData->parity << k); //armo el controlLRC para realizar XOR más adelante
    }

    for(i = 0; (i < p2trackData->nBits) && !dataFailed && !messageHasFinished; i += p2trackData->nBitsPerChar)
    {
        value = 0;  //inicializo el valor en cero antes de leer cada caracter
        controlParity = p2trackData->parity;  //inicializo el control de paridad antes de leer cada caracter
        for(j = 0; j < (p2trackData->nBitsPerChar)-1; j++) //recorro el i-esimo caracter, sin contar el bit de paridad
        {
            value += (bufferDataIn[i+j] << j);  //sumo las j-esimas potencias de 2 (primero se envían los bits más significativos).
            controlParity ^= bufferDataIn[i+j];  //realizo XOR entre los bits para controlar paridad
        }

        if(controlParity != bufferDataIn[i+j]) //al salir del bucle for, i+j hace referencia al índice del bit de paridad
        {
            dataFailed = true;
        }
        else //si paso el control del bit de paridad, se corroboran los indicadores especiales en caso de ser necesario
        {
            if((value == p2trackData->ssSymbol) && (indicatorsCounter == 0) && (i == 0)) //el primer caracter debe ser el start sentinel 
            {                                                                       //(ademas de ser el primer indicador)
                indicatorsCounter++;  //se da lugar a que venga el field separator
                data2saveFlag = false; //vino un sentinel entonces no se guarda en el arreglo de salida
            }
            else if((value == p2trackData->fsSymbol) && (indicatorsCounter == 1)) //si llega field separator luego de que llego start sentinel
            {
                indicatorsCounter++;  //se da lugar al end sentinel
                data2saveFlag = false;  //no se guarda el separador en el arreglo de salida
            } 
            else if((value == p2trackData->esSymbol) && (indicatorsCounter == 2))
            {
                indicatorsCounter++; //se da lugar a que se pueda corroborar el LRC 
                data2saveFlag = false; //no se guarda el end sentinel en el arreglo de salida
            }
            else if((indicatorsCounter == 3) && (controlLRC == value)) //si se cumple el control longitudinal, justo despues del end sentinel
            {
                data2saveFlag = false;
                messageHasFinished = true;
            }
            else if((value >= p2trackData->minValue) && (value <= p2trackData->maxValue))
            {
                data2saveFlag = true;
            }
            else
            {
                dataFailed = true;
            }
            
        }

        if(!dataFailed)
        {
            controlLRC ^= value;   //sabiendo que la data es valida actualizo LRC para control longitudinal
            if(charCounter < (p2trackData->nChars-1))
            { //entro a escribir el buffer de data si no me pase de caracteres (resto 1 para dejar lugar al terminador),
                // si value no se va de rango, y si el caracter que vino no corresponde a un separador.
                if(data2saveFlag)
                {
                    bufferDataOut[charCounter] = (bufferMagnetDataDecoded_Type)(value + p2trackData->asciiOffset);  //escribo, teniendo en cuenta el derivado 
                                                                        //del ascii utilizado en la codificación
                charCounter++;
                }
                
            }
            else
            {
                dataFailed = true;
            }
            
        }
    }

    if(!messageHasFinished)  //si el mensaje aun no ha terminado (por que no se validaron todos los indicadores), la salida es erróonea.
    {
        dataFailed = true;
    }

    bufferDataOut[charCounter] = TERMINATOR_DATA_DECODED;

    return !dataFailed;
}


void initializeTrackAsTRACK1(trackXdata_t * trackData)
{
    trackData->nBits = NUMBER_OF_BITS_TRACK1;
    trackData->nBitsPerChar = SIZE_OF_CHARS_TRACK1;
    trackData->nChars = NUMBER_OF_CHARS_TRACK1;
    trackData->parity = PARITY_TRACK1;
    trackData->ssSymbol = START_SENTINEL_TRACK1;
    trackData->fsSymbol = FIELD_SEPARATOR_TRACK1;
    trackData->esSymbol = END_SENTINEL_TRACK1;
    trackData->minValue = MIN_VALUE_TRACK1;
    trackData->maxValue = MAX_VALUE_TRACK1;
    trackData->asciiOffset = DATA_OFFSET_ASCII_TRACK1;
}

void initializeTrackAsTRACK2(trackXdata_t * trackData)
{
    trackData->nBits = NUMBER_OF_BITS_TRACK2;
    trackData->nBitsPerChar = SIZE_OF_CHARS_TRACK2;
    trackData->nChars = NUMBER_OF_CHARS_TRACK2;
    trackData->parity = PARITY_TRACK2;
    trackData->ssSymbol = START_SENTINEL_TRACK2;
    trackData->fsSymbol = FIELD_SEPARATOR_TRACK2;
    trackData->esSymbol = END_SENTINEL_TRACK2;
    trackData->minValue = MIN_VALUE_TRACK2;
    trackData->maxValue = MAX_VALUE_TRACK2;
    trackData->asciiOffset = DATA_OFFSET_ASCII_TRACK2;
}

void initializeTrackAsTRACK3(trackXdata_t * trackData)
{
    trackData->nBits = NUMBER_OF_BITS_TRACK3;
    trackData->nBitsPerChar = SIZE_OF_CHARS_TRACK3;
    trackData->nChars = NUMBER_OF_CHARS_TRACK3;
    trackData->parity = PARITY_TRACK3;
    trackData->ssSymbol = START_SENTINEL_TRACK3;
    trackData->fsSymbol = FIELD_SEPARATOR_TRACK3;
    trackData->esSymbol = END_SENTINEL_TRACK3;
    trackData->minValue = MIN_VALUE_TRACK3;
    trackData->maxValue = MAX_VALUE_TRACK3;
    trackData->asciiOffset = DATA_OFFSET_ASCII_TRACK3; 
}
/*******************************************************************************
 ******************************************************************************/
