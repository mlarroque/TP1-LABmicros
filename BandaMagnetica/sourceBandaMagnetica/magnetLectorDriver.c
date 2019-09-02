//magnetLectorDriver.c

void hwLectorInit(void)
{

}

void setEvent(void)
{

}

//////sobre las interrupciones:
///en principio, debe haber una interrupción de enable enable del lector que habilite interrucion de clock del lector. Finalmente el enable
///también debe deshabilitar las interrupciones de clock. Al terminar el enable, se debe deshabilitar la interrupcion de enable hasta
//terminar de decodificar.
///en cuanto a las interrupciones de clock, ante un flanco descendente, se debe interpretar un 1 si el pin de data esta en "bajo", mientras que
//se debe corrsponder a un 0 el hecho de que el pin de data este en "alto".
//estos 0s y 1s deben introducirse en un buffer, el cual se decodifica ante un flanco alto de enable. Al terminar la decodificación
//se debe volver a habilitar la interrupción de enable.