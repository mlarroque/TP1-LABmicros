/***************************************************************************//**
  @file     magnetCardDecode.c
  @brief    Magnet card decoding functions
  @author   G5
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "magnetCardDecode.h"



/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define NUMBER_OF_CHARS_TRACK1 79
#define NUMBER_OF_CHARS_TRACK2 40
#define NUMBER_OF_CHARS_TRACK3 107

#define SIZE_OF_CHARS_TRACK1 7
#define SIZE_OF_CHARS_TRACK2 5
#define SIZE_OF_CHARS_TRACK3 5

#define NUMBER_OF_BITS_TRACK1 (SIZE_OF_CHARS_TRACK1 * NUMBER_OF_CHARS_TRACK1)
#define NUMBER_OF_BITS_TRACK2 (SIZE_OF_CHARS_TRACK2 * NUMBER_OF_CHARS_TRACK2)
#define NUMBER_OF_BITS_TRACK3 (SIZE_OF_CHARS_TRACK3 * NUMBER_OF_CHARS_TRACK3)



/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
void decodeTrackX(bufferMagnetDataEncoded_Type * bufferDataIn, bufferMagnetDataDecoded_Type * bufferDataOut, uint8_t bitCounter);

void decodeTrack1(bufferMagnetDataEncoded_Type * bufferDataIn, bufferMagnetDataDecoded_Type * bufferDataOut);
void decodeTrack2(bufferMagnetDataEncoded_Type * bufferDataIn, bufferMagnetDataDecoded_Type * bufferDataOut);
void decodeTrack3(bufferMagnetDataEncoded_Type * bufferDataIn, bufferMagnetDataDecoded_Type * bufferDataOut);


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


/*******************************************************************************
 ******************************************************************************/
