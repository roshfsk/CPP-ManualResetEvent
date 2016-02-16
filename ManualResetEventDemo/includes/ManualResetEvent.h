/*
 * ManualResetEvent.h
 *
 *  Created on: Feb 15, 2016
 *      Author: root
 */
#include <pthread.h>
#include <stdbool.h>

#ifndef MANUALRESETEVENT_H_
#define MANUALRESETEVENT_H_

using namespace std;

class ManualResetEvent {
public:
	ManualResetEvent();
	virtual ~ManualResetEvent();

	struct MREStruct {
		pthread_mutex_t mutex;
		pthread_cond_t cond;
		bool triggered;
	} eventStruct;

	virtual void trigger(struct MREStruct *ev);
	virtual void wait(struct MREStruct *ev);
	virtual void reset(struct MREStruct *ev);
	virtual void init(struct MREStruct *ev);

};

#endif /* MANUALRESETEVENT_H_ */
