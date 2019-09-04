//magnetLectorDriver.h

#define NO_TRACK_DATAID -1
#define TRACK1_DATAID 1
#define TRACK2_DATAID 2
#define TRACK3_DATAID 3

#define MAX_TRACK_LEN 200


typedef struct{

	int trackNum;
	char trackString[MAX_TRACK_LEN];

}magnetLectorData_t;

typedef struct queue{
	int top = 0;
	magnetLectorData_t magnetLectorDataQueue[MAX_ITEMS_LECTOR_QUEUE];
	_Bool isEmpty;
}lectorQueue_t;



magnetLectorData_t getLectureEvent(void);
void hwLectorInit(void);
