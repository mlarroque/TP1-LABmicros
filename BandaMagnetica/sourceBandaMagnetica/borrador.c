//borrador

void decodeTrack2(bufferMagnetDataEncoded_Type * bufferDataIn, bufferMagnetDataDecoded_Type * bufferDataOut);
void decodeTrack3(bufferMagnetDataEncoded_Type * bufferDataIn, bufferMagnetDataDecoded_Type * bufferDataOut);


//identifySymbol:
//Brief: this function identify symbol in bufferDataIn, in case of success the index of the bufferDataIn that corresponds
// with the symbol identified is save in the variable indexFounded whose pointer is passed as an argument of the function
//args: dataIn, indexLimit for dataIn, indexStart for dataIn, symbol, symbolSize, and a pointer for a variable 
//to save the dataIndex in case of succcess.
//return: true in case of success, False in case the symbol is not founded.
_Bool identifySymbol(bufferMagnetDataEncoded_Type * bufferDataIn, UINT_T indexLimit, UINT_T indexStart, bufferMagnetDataEncoded_Type * symbol, uint8_t symbolSize, UINT_T * indexFounded);





//deleteBorders:
//Brief: this function select the zone of dataIn between startCentinel and endCentinel, and then
//set this zone at the beggining of the bufferDataIn.
//args: dataIn and index to indicate de zone (indexStartCentinel < indexEndCentinel).
//Ensure that indexEndCentinel < MAX_DATA_LEN.
void deleteBorders(bufferMagnetDataEncoded_Type * bufferDataIn, UINT_T indexStartCentinel, UINT_T indexEndCentinel);




bufferMagnetDataEncoded_Type startCentinelTrack1[] = {1, 0, 0, 0, 1, 0, 1};
bufferMagnetDataEncoded_Type startCentinelTrack2[] = {0, 1, 0 ,1, 1};
bufferMagnetDataEncoded_Type startCentinelTrack3[] = {0, 1, 0 ,1, 1};

bufferMagnetDataEncoded_Type startCentinelTrack1[] = {1, 0, 0, 0, 1, 0, 1};
bufferMagnetDataEncoded_Type startCentinelTrack2[] = {0, 1, 0 ,1, 1};
bufferMagnetDataEncoded_Type startCentinelTrack3[] = {0, 1, 0 ,1, 1};

bufferMagnetDataEncoded_Type fieldSeparatorTrack1[] = {0, 1, 1, 1, 1, 1, 0};
bufferMagnetDataEncoded_Type fieldSeparatoTrack2[] = {0, 1, 1, 0, 1};
bufferMagnetDataEncoded_Type fieldSeparatorTrack3[] = {0, 1, 1, 0, 1};



_Bool decodeTrackX(bufferMagnetDataEncoded_Type * bufferDataIn, bufferMagnetDataDecoded_Type * bufferDataOut)
 {

     _Bool isDecodeOK = false;
     
     switch(magnetDataParser(bufferDataIn))
     {
         case TRACK1:
                    isDecodeOK = decodeTrack1(bufferDataIn, bufferDataOut);
                    break;
        case TRACK2:
                    isDecodeOK = decodeTrack2(bufferDataIn, bufferDataOut);
                    break;
        case TRACK3:
                    isDecodeOK = decodeTrack3(bufferDataIn, bufferDataOut);
                    break;

     }

     return isDecodeOK;
 }


 uint8_t magnetDataParser(bufferMagnetDataEncoded_Type * bufferDataIn)
{
    UINT_T indexStartCentinel;
    UINT_T indexEndCentinel;
    uint8_t trackFounded = NO_TRACK;
    
    if(identifySimbol(bufferDataIn, MAX_LEN_DATA, 0, startCentinelTrack2, SIZE_OF_CHARS_TRACK2, &indexStartCentinel))  //busco start centinel de track2
    {
        if(identifySimbol(bufferDataIn, MAX_LEN_DATA, (indexStartCentinel + NUMBER_OF_CHARS_TRACK2 - 1), endCentinelTrack2, SIZE_OF_CHARS_TRACK1, &indexEndCentinel)) //busco end centinel de track2
        {
            if( (indexEndCentinel - indexStartCentinel) == (NUMBER_OF_CHARS_TRACK1 - 2) )   //se verifica la correcta longitud del track (se resta 2 al comparar debido al caracter de LRC)
            {
                deleteBorders(bufferDataIn, indexStartCentinel, indexEndCentinel);
                trackFounded = TRACK1;
            }
             
        }
    }

    //para encontrar el numero de track, primero busco el "start_centinel (SC), luego busco el "end_centinel" (ES) 
    //y por último cuento la cantidad de datos entre estos indicadores.

    for(i = 0; i < (MAX_LEN_DATA - SIZE_OF_CHARS_TRACK1); i++)
    {
        for(j = 0; j < SIZE_OF_CHARS_TRACK1 ; j++)
        {
            if(!SCfounded)  //estoy buscando start centinela para el track1
            {
                count(bufferDataIn[i+j] == startCentinelTrack1[j])
            }
            else if(!ESfounded) //estoy buscando end centinela
            {
                
            }
            a = (a == b) ? c: b;bufferDataIn[i+j] == startCentinelTrack1[j]
        }
        for(k = 0; k < SIZE_OF_CHARS_TRACK2; j++)
        {

        }
        bufferDataIn[i]
    }
    

    return ret;
}

_Bool identifySymbol(bufferMagnetDataEncoded_Type * bufferDataIn, UINT_T indexLimit, UINT_T indexStart, bufferMagnetDataEncoded_Type symbol, uint8_t symbolSize, U_INT * indexFounded)
{
    UINT_T i, j;
    _Bool symbolFounded = false;
    _Bool comparationFailed = false;
    for(i = 0; (i < indexLimit) && (!symbolFounded); i++)  //se recorre data encoded
    {
        for(j = 0; (j < symbolSize) && (!comparationFailed); j++) //se compara data con el simbolo en cuestión
        {
            
        }

        if((j == symbolSize) && (!comparationFailed))
        {
            symbolFounded = true;       //se termina la busqueda al encontrar el simbolo
            *indexFounded = i;
        }
    }
    return symbolFounded;
}

void deleteBorders(bufferMagnetDataEncoded_Type * bufferDataIn, UINT_T indexStartCentinel, UINT_T indexEndCentinel)
{
    UINT_T i;
    for(i = 0; i <= (indexEndCentinel - indexStartCentinel); i++)
    {
        bufferDataIn[i] = bufferDataIn[i + indexStartCentinel];
    }
}
















///////////////////77
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

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define BITS_CAPACITY 32
#if BITS_CAPACITY >= 32
#define UINT_T uint32_t
#else
#define UINT_T unit8_t
#endif

#define NO_TRACK -1
#define TRACK1 0
#define TRACK2 1
#define TRACK3 2

#define TERMINATOR_DATA_DECODED '\0'


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

int getTrackShaped(bufferMagnetDataEncoded_Type * bufferDataIn);

void initializeTrackAsTRACK1(trackXdata_t * trackData);
void initializeTrackAsTRACK2(trackXdata_t * trackData);
void initializeTrackAsTRACK3(trackXdata_t * trackData);

_Bool decodeTrackX(bufferMagnetDataEncoded_Type * bufferDataIn, bufferMagnetDataDecoded_Type * bufferDataOut, trackXdata_t * p2trackData);

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
        dataErrorReport = decodeTrackX(bufferDataIn, bufferDataOut, &trackData);
    }

    return !dataErrorReport;
}

uint8_t getTrackShaped(bufferMagnetDataEncoded_Type * bufferDataIn)
{
    
}


void initializeTrackAsTRACK1(trackXdata_t * trackData)
{
    trackData.nBits = NUMBER_OF_BITS_TRACK1;
    trackData.nBitsPerChar = SIZE_OF_CHARS_TRACK1;
    trackData.nChars = NUMBER_OF_CHARS_TRACK1;
    trackData.parity = PARITY_TRACK1;
    trackData.ssSymbol = START_CENTINEL_TRACK1;
    trackData.fsSymbol = FIELD_SEPARATOR_TRACK1;
    trackData.esSymbol = END_SENTINEL_TRACK1;
    trackData.minValue = MIN_VALUE_TRACK1;
    trackData.maxValue = MAX_VALUE_TRACK1;
    trackData.asciiOffset = DATA_OFFSET_ASCII_TRACK1;
}

void initializeTrackAsTRACK2(trackXdata_t * trackData)
{
    trackData.nBits = NUMBER_OF_BITS_TRACK2;
    trackData.nBitsPerChar = SIZE_OF_CHARS_TRACK2;
    trackData.nChars = NUMBER_OF_CHARS_TRACK2;
    trackData.parity = PARITY_TRACK2;
    trackData.ssSymbol = START_CENTINEL_TRACK2;
    trackData.fsSymbol = FIELD_SEPARATOR_TRACK2;
    trackData.esSymbol = END_SENTINEL_TRACK2;
    trackData.minValue = MIN_VALUE_TRACK2;
    trackData.maxValue = MAX_VALUE_TRACK2;
    trackData.asciiOffset = DATA_OFFSET_ASCII_TRACK2;
}

void initializeTrackAsTRACK3(trackXdata_t * trackData)
{
    trackData.nBits = NUMBER_OF_BITS_TRACK3;
    trackData.nBitsPerChar = SIZE_OF_CHARS_TRACK3;
    trackData.nChars = NUMBER_OF_CHARS_TRACK3;
    trackData.parity = PARITY_TRACK3;
    trackData.ssSymbol = START_CENTINEL_TRACK3;
    trackData.fsSymbol = FIELD_SEPARATOR_TRACK3;
    trackData.esSymbol = END_SENTINEL_TRACK3;
    trackData.minValue = MIN_VALUE_TRACK3;
    trackData.maxValue = MAX_VALUE_TRACK3;
    trackData.asciiOffset = DATA_OFFSET_ASCII_TRACK3; 
}

_Bool decodeTrackX(bufferMagnetDataEncoded_Type * bufferDataIn, bufferMagnetDataDecoded_Type * bufferDataOut, trackXdata_t * p2trackData)
{
    U_INT i, j, charCounter = 0;
    bufferMagnetDataEncoded_Type controlParity, value;
    bufferMagnetDataEncoded_Type controlLRC;
    uint8_t k, indicatorsCounter = 0;  //vale 0 si no llego ningun counter, cambia a 1 cuando llega ss,
                                //cambia 2 si llega fs, a 3 si llega  es (da lugar a corroborar LRC).
    _Bool dataFailed = false;
    _Bool data2saveFlag = false;
    _Bool messageHasFinished = false;

    //inicializo controLRC
    controlLRC = 0;
    for (k = 0; k < (p2trackData->nBitsPerChar); k++)
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
            if((charCounter < p2trackData->nChars-1) && data2saveFlag)
            { //entro a escribir el buffer de data si no me pase de caracteres (resto 1 para dejar lugar al terminador),
                // si value no se va de rango, y si el caracter que vino no corresponde a un separador.
                bufferDataOut[charCounter] = (bufferMagnetDataDecoded_Type)(value + p2trackData->asciiOffset);  //escribo, teniendo en cuenta el derivado 
                                                                        //del ascii utilizado en la codificación
                charCounter++;
            }
            else
            {
                dataFailed = true;
            }
            
        }
    }

    bufferDataOut[charCounter] = TERMINATOR_DATA_DECODED;

    return !dataFailed;
}

/*******************************************************************************
 ******************************************************************************/