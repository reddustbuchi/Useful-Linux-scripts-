#ifndef _LIB_AES_H_
#define _LIB_AES_H_

#define AES_LIB			450000218

#include "c4d_library.h"

#ifdef __API_INTERN__
#include "c4d_library.h"
#include "intbaselist.h"
#endif

typedef Bool (*PFNRIJINDAEL_CIPHER_PROGRESS)(Int lProgress, Int lLength, void* pData);

class AES
{
private:
	AES();
	~AES();

public:
	static AES* Alloc();
	static void Free(AES *&pAES);

	// block length and key length must be 128, 192 or 256 (bits)
	Bool Init(Int32 lBlockLength, Int32 lKeyLength);

	static Int CalcEncryptedDataSize(Int32 lBlockLength, Int lDataLength); // lBlockLength in bits, lDataLength in bytes

	// the data array must be big enough to hold (lBlockLength/8) more bytes than lDataLength
	Bool Encrypt(void* pData, Int lDataLength, const void* pKey);
	Bool Decrypt(void* pData, Int lDataLength, const void* pKey);
	void SetProgresCallback(PFNRIJINDAEL_CIPHER_PROGRESS fn, void* pData);
};


// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

class RijndaelCipher;

struct AESLib : public C4DLibrary
{
	RijndaelCipher*		(*RijndaelCipher_Alloc)();
	void		(*RijndaelCipher_Free)(RijndaelCipher *&pAES);
	Int		(*RijndaelCipher_CalcEncryptedDataSize)(Int32 lBlockLength, Int lDataLength); // lBlockLength in bits, lDataLength in bytes

	Bool		(RijndaelCipher::*Init)(Int32 lBlockLength, Int32 lKeyLength);
	Bool		(RijndaelCipher::*Encrypt)(void* pData, Int lDataLength, const void* pKey);
	Bool		(RijndaelCipher::*Decrypt)(void* pData, Int lDataLength, const void* pKey);
	void		(RijndaelCipher::*SetProgresCallback)(PFNRIJINDAEL_CIPHER_PROGRESS fn, void* pData);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif // _LIB_AES_H_
