//magnetLectorDriver.h
#ifndef _MAGNETLECTOR_H_
#define _MAGNETLECTOR_H_
#define NO_TRACK_DATAID -1
#define TRACK1_DATAID 1
#define TRACK2_DATAID 2
#define TRACK3_DATAID 3

#define MAX_TRACK_LEN 200
#define MAX_ITEMS_LECTOR_QUEUE 5

typedef struct{

	int trackNum;
	char trackString[MAX_TRACK_LEN];
	_Bool isValid;

}magnetLectorData_t;



_Bool isEventinLectorQueue(void);

magnetLectorData_t getLectureEvent(void);
void hwLectorInit();


#endif //_MAGNETLECTOR_H_
