/*
 * encoderQueue.h
 *
 *  Created on: Sep 4, 2019
 *      Author: Lu
 */

#ifndef ENCODERQUEUE_H_
#define ENCODERQUEUE_H_

void initializeQueue(void);
encoderQueue_t popEvent(void);
void pushEvent(encoderQueue_t ev);

encoderQueue_t getEncoderQueue(void);


#endif /* ENCODERQUEUE_H_ */
