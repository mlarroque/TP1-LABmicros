/***************************************************************************//**
  @file     gpio.h
  @brief    Simple GPIO Pin services, similar to Arduino
  @author   Nicolás Magliola
 ******************************************************************************/

#ifndef _MAGNETCARDDECODE_H_
#define _MAGNETCARDDECODE_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "cardStandard.h"
#include <stdint.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define DATA_LEN 1024
#define TERMINATOR_DATA_DECODED '\0'

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef uint8_t bufferMagnetDataEncoded_Type;
typedef char bufferMagnetDataDecoded_Type;

_Bool magnetDataParser(bufferMagnetDataEncoded_Type * bufferDataIn, bufferMagnetDataDecoded_Type * bufferDataOut);


#endif //_MAGNETCARDDECODE_H_