/*
 * DemoMain.cpp
 *
 *  Created on: Feb 15, 2016
 *      Author: RoshanF
 */

#include "DemoMain.h"
using namespace std;

static int counter;
static ManualResetEvent * mreHandle;
pthread_mutex_t m_MREventLock;

DemoMain::DemoMain() {
	// TODO Auto-generated constructor stub
	cout << "DemoMain constructed" << endl;

	pthread_mutexattr_t mAttr;
	pthread_mutexattr_init(&mAttr);
	pthread_mutexattr_settype(&mAttr, PTHREAD_MUTEX_RECURSIVE_NP);
	pthread_mutex_init(&m_MREventLock, &mAttr);
	pthread_mutexattr_destroy(&mAttr);

	mreHandle = new ManualResetEvent();
	mreHandle->init(&mreHandle->eventStruct);

	counter = 0;
	int rc;

	rc = pthread_create(&m_CounterThread, NULL, CounterThread, (void *)0);
	if (rc) {
		cout << "Error:unable to create CounterThread," << rc << endl;
		exit(-1);
	}

	rc = pthread_create(&m_SleeperThread, NULL, SleeperThread, (void *)1);
	if (rc) {
		cout << "Error:unable to create SleeperThread," << rc << endl;
		exit(-1);
	}

	rc = pthread_create(&m_ManualResetEventThread, NULL, ManualResetEventThread, (void *)2);
	if (rc) {
		cout << "Error:unable to create thread," << rc << endl;
		exit(-1);
	}
}

DemoMain::~DemoMain() {
	// TODO Auto-generated destructor stub
}

#define NUM_THREADS     5



int main ()
{
	cout << "App started" << endl;
	DemoMain * dm = new DemoMain();

	pthread_exit(NULL);
}

void * DemoMain::CounterThread(void * obj) {

	while(true) {
		usleep(1000 * 1000 * 2); // 2 seconds
		counter++;

		pthread_mutex_lock(&m_MREventLock);
		mreHandle->trigger(&mreHandle->eventStruct);
		pthread_mutex_unlock(&m_MREventLock);

		cout << "CounterThread counter update: " << counter << endl;
	}
	pthread_exit(NULL);
}

void * DemoMain::SleeperThread(void * obj) {

	while(true) {
		usleep(1000 * 100 * 5); // 0.5 seconds
		cout << "SleeperThread Counter" << counter << endl;
	}
	pthread_exit(NULL);
}

void * DemoMain::ManualResetEventThread(void * obj) {

	while(true) {
		mreHandle->wait(&mreHandle->eventStruct);

		//lock
		pthread_mutex_lock(&m_MREventLock);
		cout << "ManualResetEventThread Counter" << counter << endl;
		mreHandle->reset(&mreHandle->eventStruct);
		pthread_mutex_unlock(&m_MREventLock);
		//unlock

	}
	pthread_exit(NULL);
}

