/*
 * DemoMain.h
 *
 *  Created on: Feb 15, 2016
 *      Author: root
 */
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <ManualResetEvent.h>

#ifndef DEMOMAIN_H_
#define DEMOMAIN_H_


class DemoMain {
public:
	DemoMain();
	virtual ~DemoMain();
	pthread_t m_CounterThread;
	pthread_t m_SleeperThread;
	pthread_t m_ManualResetEventThread;

private:
	static void * CounterThread(void * obj);
	static void * SleeperThread(void * obj);
	static void * ManualResetEventThread(void * obj);

};

#endif /* DEMOMAIN_H_ */
