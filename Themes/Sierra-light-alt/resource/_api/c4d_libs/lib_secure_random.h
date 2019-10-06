#ifndef _LIB_SECURE_RANDOM_H_
#define _LIB_SECURE_RANDOM_H_

#define SECURE_RANDOM_LIB			450000265

#include "c4d_library.h"

#ifdef __API_INTERN__
#include "c4d_library.h"
#include "intbaselist.h"
#endif

struct _SecureRandomProvider;
typedef _SecureRandomProvider* SecureRandomProvider;

class SecureRandom
{
public:
	static SecureRandomProvider GetDefaultProvider();
	static Bool GetRandomNumber(SecureRandomProvider provider, void* buffer, Int size);
};


// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

struct SecureRandomLib : public C4DLibrary
{
	SecureRandomProvider		(*SecureRandom_GetDefaultProvider)();
	Int		(*SecureRandom_GetRandomNumber)(SecureRandomProvider provider, void* buffer, Int size); // lBlockLength in bits, lDataLength in bytes
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif // _LIB_SECURE_RANDOM_H_
