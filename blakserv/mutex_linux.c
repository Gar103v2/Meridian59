// Meridian 59, Copyright 1994-2012 Andrew Kirmse and Chris Kirmse.
// All rights reserved.
//
// This software is distributed under a license that is described in
// the LICENSE file that accompanies it.
//
// Meridian is a registered trademark.
/*
 * mutex_linux.c
 */

#include "blakserv.h"

Mutex MutexCreate() {
   Mutex mutex = new MutexWrapper();
   pthread_mutex_init(&mutex->mutex, NULL);
   return mutex;
}

bool MutexAcquire(Mutex mutex) {
   return pthread_mutex_lock(&mutex->mutex) == 0;
}

bool MutexAcquireWithTimeout(Mutex mutex, int timeoutMs) {
	timespec ts;

	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += (timeoutMs / 1000L);
	ts.tv_nsec += (timeoutMs - ((timeoutMs / 1000L) * 1000L)) * 1000000L;

	return pthread_mutex_timedlock(&mutex->mutex, &ts) == 0;
}

bool MutexRelease(Mutex mutex) {
   return pthread_mutex_unlock(&mutex->mutex) == 0;
}

bool MutexClose(Mutex mutex) {
   return pthread_mutex_destroy(&mutex->mutex) == 0;
}
