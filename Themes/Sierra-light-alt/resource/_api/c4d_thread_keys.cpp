/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __API_INTERN__
#ifdef __PC

	#include "windows_include.h"

	#include "c4d_thread_keys.h"

// returns false if thread variable cannot be created
Bool GeCreateThreadVariable(GeThreadVariableKey* key)
{
	*key = TlsAlloc();
	return *key != GeThreadVariableKey(-1);
}

Bool GeDeleteThreadVariable(GeThreadVariableKey key)
{
	return TlsFree(key);
}

// if no value has been set for the key, this function returns nullptr
void* GeGetThreadVariable(GeThreadVariableKey key)
{
	return (void*) TlsGetValue(key);
}

Bool GeSetThreadVariable(GeThreadVariableKey key, void* value)
{
	return TlsSetValue(key, value);
}

#endif
#endif
