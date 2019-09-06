/*
 * magnetCardLector.c
 *
 *  Created on: 6 sep. 2019
 *      Author: G5
 */

#include "magnetCardLector.h"
#include "magnetLectorHAL.h"
#include "magnetCardDecode.h"
#include <stdbool.h>

void initMagnetCardLector(void){
	hwLectorInit();
}

_Bool someMagnetCard2Read(void){
	return isEventinLectorQueue();
}
magnetLectorData_t getLectureDecoded(void){
	magnetLectorData_t ret;
	if(isEventinLectorQueue())
	{
		if(magnetDataParser(getLectureEvent(), ret.trackString, &(ret.trackNum)))
		{
			ret.isValid = true;
		}
		else
		{
			ret.isValid = false;
		}
	}
	return ret;
}


