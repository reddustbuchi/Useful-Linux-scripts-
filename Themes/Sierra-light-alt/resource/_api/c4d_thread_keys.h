/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DTHREAD_KEYS_H
#define	__C4DTHREAD_KEYS_H

#ifndef __API_INTERN__

	#include "ge_math.h"

	#ifdef __PC

typedef unsigned long	GeThreadVariableKey;

// for debugging purposes
inline Bool	GeIsValidThreadVariableKey(GeThreadVariableKey key)
{
	return key != GeThreadVariableKey(-1);
}

// no inlines because we get to many conflicts with Windows headers
extern Bool	GeCreateThreadVariable(GeThreadVariableKey* key);
extern Bool	GeDeleteThreadVariable(GeThreadVariableKey key);
extern void* GeGetThreadVariable(GeThreadVariableKey key);
extern Bool	GeSetThreadVariable(GeThreadVariableKey key, void* value);

	#else

		#include <pthread.h>
typedef pthread_key_t	GeThreadVariableKey;

// for debugging purposes
inline Bool	GeIsValidThreadVariableKey(GeThreadVariableKey key)
{
	return key != (GeThreadVariableKey)0;
}

// returns GE_INVALID_THREAD_KEY if thread variable cannot be created
inline Bool	GeCreateThreadVariable(GeThreadVariableKey* key)
{
	return pthread_key_create(key, nullptr) == 0;
}

inline Bool	GeDeleteThreadVariable(GeThreadVariableKey key)
{
	return pthread_key_delete(key) == 0;
}

// if no value has been set for the key, this function returns nullptr
inline void* GeGetThreadVariable(GeThreadVariableKey key)
{
	return (void*) pthread_getspecific(key);
}

inline Bool	GeSetThreadVariable(GeThreadVariableKey key, void* value)
{
	return pthread_setspecific(key, value) == 0;
}

	#endif
#endif
#endif
