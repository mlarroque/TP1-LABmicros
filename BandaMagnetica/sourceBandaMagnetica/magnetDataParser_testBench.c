//magnetDataParser_testBench.c

#include <stdio.h>
#include "magnetCardDecode.h"
int main(void)
{
    bufferMagnetDataEncoded_Type track2Encoded_1[] = {1, 1, 0, 1, 0, //SS
                                                            0, 0, 1, 0, 0, //4
                                                            1, 0, 1, 0, 1, //5
                                                            1, 0, 0, 0, 0, //1
                                                            1, 1, 1, 0, 0, //7
                                                            0, 1, 1, 0, 1, //6
                                                            0, 1, 1, 0, 1, //6
                                                            0, 0, 0, 0, 1, //0
                                                            1, 0, 0, 1, 1, //9
                                                            1, 0, 1, 1, 0, //FS
                                                            0, 0, 0, 0, 1, //0
                                                            0, 0, 0, 1, 0, //8
                                                            0, 0, 0, 0, 1, //0
                                                            1, 1, 0, 0, 1, //3
                                                            0, 0, 1, 0, 0, //4
                                                            1, 1, 0, 0, 1, //3
                                                            0, 0, 0, 1, 0, //8
                                                            1, 0, 0, 0, 0, //1 
                                                            1, 1, 1, 1, 1, //ES 
                                                            1, 0, 1, 1, 0}; //LRC                                                                          
                                                            //tarjeta de ingreso a universidad: SS451766009fs08034381ESLRC
    bufferMagnetDataDecoded_Type track2Decoded_1[200];

    bufferMagnetDataEncoded_Type track2Encoded_2[] = {1, 1, 0, 1, 0, //SS
                                                            0, 0, 1, 0, 0, //4
                                                            1, 0, 1, 0, 1, //5
                                                            1, 0, 0, 0, 0, //1
                                                            1, 1, 1, 0, 0, //7
                                                            0, 1, 1, 0, 1, //6
                                                            0, 1, 1, 0, 1, //6
                                                            0, 0, 0, 0, 1, //0
                                                            1, 0, 0, 1, 1, //9
                                                            1, 0, 1, 1, 0, //FS
                                                            0, 0, 0, 0, 1, //0
                                                            0, 0, 0, 1, 0, //8
                                                            0, 0, 0, 0, 1, //0
                                                            1, 1, 0, 0, 1, //3
                                                            0, 0, 1, 0, 0, //4
                                                            1, 1, 0, 0, 1, //3
                                                            0, 0, 0, 1, 0, //8
                                                            1, 0, 0, 0, 0, //1 
                                                            1, 1, 1, 1, 1}; //ES                                                                          
                                                            //tarjeta de ingreso a la universidad erronea (sin LRC)

    bufferMagnetDataDecoded_Type track2Decoded_2[200];

    if(magnetDataParser(track2Encoded_1, track2Decoded_1))
    {
        printf("%s\n", track2Decoded_1);
    }
    else
    {
        printf("ERROR IN TRACK2 prueba 1\n");
    }

    if(magnetDataParser(track2Encoded_2, track2Decoded_2))
    {
        printf("%s\n", track2Decoded_2);
    }
    else
    {
        printf("ERROR IN TRACK2 prueba 2\n");
    }

}

