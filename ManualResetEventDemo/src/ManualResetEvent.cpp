/*
 * ManualResetEvent.cpp
 *
 *  Created on: Feb 15, 2016
 *      Author: RoshanF
 */

#include <ManualResetEvent.h>



ManualResetEvent::ManualResetEvent() {
	// TODO Auto-generated constructor stub
}

ManualResetEvent::~ManualResetEvent() {
	// TODO Auto-generated destructor stub
}


void ManualResetEvent::init(struct MREStruct *ev) {
    pthread_mutex_init(&ev->mutex, 0);
    pthread_cond_init(&ev->cond, 0);
    ev->triggered = false;
}

void ManualResetEvent::trigger(struct MREStruct *ev) {
    pthread_mutex_lock(&ev->mutex);
    ev->triggered = true;
    pthread_cond_broadcast(&ev->cond);
    pthread_mutex_unlock(&ev->mutex);
}

void ManualResetEvent::reset(struct MREStruct *ev) {
    pthread_mutex_lock(&ev->mutex);
    ev->triggered = false;
    pthread_mutex_unlock(&ev->mutex);
}

void ManualResetEvent::wait(struct MREStruct *ev) {
     pthread_mutex_lock(&ev->mutex);
     while (!ev->triggered)
         pthread_cond_wait(&ev->cond, &ev->mutex);
     pthread_mutex_unlock(&ev->mutex);
}
