#ifndef _LIB_BIG_INTEGER_H_
#define _LIB_BIG_INTEGER_H_

#define BIG_INTEGER_LIB			450000264

#include "c4d_library.h"
#include "lib_secure_random.h"
#include "c4d_misc.h"

#ifdef __API_INTERN__
#include "c4d_library.h"
#include "intbaselist.h"
#endif

#undef Mod

class BigInteger
{
private:
	BigInteger();
	~BigInteger();

public:
	static BigInteger* Alloc();
	static void Free(BigInteger *&pAES);

	//----------------------------------------------------------------------------------------
	/// Sets the value of this BigInteger.
	/// @param[in] c									The new value.
	/// @return												True if the operation was successful.
	//----------------------------------------------------------------------------------------
	Bool Set(maxon::Char c);

	//----------------------------------------------------------------------------------------
	/// Sets the value of this BigInteger.
	/// @param[in] c									The new value.
	/// @return												True if the operation was successful.
	//----------------------------------------------------------------------------------------
	Bool Set(maxon::UChar c);

	//----------------------------------------------------------------------------------------
	/// Sets the value of this BigInteger.
	/// @param[in] i									The new value.
	/// @return												True if the operation was successful.
	//----------------------------------------------------------------------------------------
	Bool Set(maxon::Int16 i);

	//----------------------------------------------------------------------------------------
	/// Sets the value of this BigInteger.
	/// @param[in] u									The new value.
	/// @return												True if the operation was successful.
	//----------------------------------------------------------------------------------------
	Bool Set(maxon::UInt16 u);

	//----------------------------------------------------------------------------------------
	/// Sets the value of this BigInteger.
	/// @param[in] i									The new value.
	/// @return												True if the operation was successful.
	//----------------------------------------------------------------------------------------
	Bool Set(maxon::Int32 i);

	//----------------------------------------------------------------------------------------
	/// Sets the value of this BigInteger.
	/// @param[in] u									The new value.
	/// @return												True if the operation was successful.
	//----------------------------------------------------------------------------------------
	Bool Set(maxon::UInt32 u);

	//----------------------------------------------------------------------------------------
	/// Sets the value of this BigInteger.
	/// @param[in] i									The new value.
	/// @return												True if the operation was successful.
	//----------------------------------------------------------------------------------------
	Bool Set(maxon::Int64 i);

	//----------------------------------------------------------------------------------------
	/// Sets the value of this BigInteger.
	/// @param[in] u									The new value.
	/// @return												True if the operation was successful.
	//----------------------------------------------------------------------------------------
	Bool Set(maxon::UInt64 u);

	//----------------------------------------------------------------------------------------
	/// Assigns a random value to this BigInteger. The number is always positive.
	/// @param[in] bitCount						The number of bits to set. This value must be greater than 0.
	/// @param[in] provider						A secure random provider that can be used with SecureRandom. If nullptr is passed an unsecure default provider is chosen.
	/// @return												True if the operation was successful.
	//----------------------------------------------------------------------------------------
	Bool SetRandom(maxon::Int bitCount, SecureRandomProvider provider = nullptr);

	//----------------------------------------------------------------------------------------
	/// Assigns a random prime number value to this BigInteger. The number is always positive, odd and the (bitCount - 1) bit will be set.
	/// @param[in] bitCount						The number of bits to set. This value must be greater than 1.
	/// @param[in] certainity					The generated number is a prime number with a probability of 1-0.5**certainity. This parameter must be greater than 0. The execution time of this function raises with the certainity.
	/// @param[in] provider						A secure random provider that can be used with SecureRandom. If nullptr is passed an unsecure default provider is chosen.
	/// @return												True if the operation was successful.
	//----------------------------------------------------------------------------------------
	Bool SetRandomPrime(maxon::Int bitCount, maxon::UInt certainity, SecureRandomProvider provider = nullptr);

	//----------------------------------------------------------------------------------------
	/// Checks if the value is even.
	/// @return												True if the value is even.
	//----------------------------------------------------------------------------------------
	Bool IsEven() const;

	//----------------------------------------------------------------------------------------
	/// Checks if the value is odd.
	/// @return												True if the value is odd.
	//----------------------------------------------------------------------------------------
	Bool IsOdd() const;

	//----------------------------------------------------------------------------------------
	/// Checks if the value is one.
	/// @return												True if the value is one.
	//----------------------------------------------------------------------------------------
	Bool IsOne() const;

	//----------------------------------------------------------------------------------------
	/// Checks if the value is zero.
	/// @return												True if the value is zero.
	//----------------------------------------------------------------------------------------
	Bool IsZero() const;

	//----------------------------------------------------------------------------------------
	/// Checks if the value is negative.
	/// @return												True if the value is negative.
	//----------------------------------------------------------------------------------------
	Bool IsNegative() const;

	//----------------------------------------------------------------------------------------
	/// Checks if the value is a power of 2.
	/// @return												True if the value is a power of 2.
	//----------------------------------------------------------------------------------------
	Bool IsPowerOfTwo() const;

	//----------------------------------------------------------------------------------------
	/// Checks if the number is probably prime. The result will be false if this is smaller than one.
	/// @param[in] certainity					The generated number is a prime number with a probability of 1-0.5**certainity. This parameter must be greater than 0.
	/// @return												True if number is greater than zero and prime with a probability of 1-0.5**certainity.
	//----------------------------------------------------------------------------------------
	Bool IsProbablyPrime(maxon::UInt certainity) const;

	//----------------------------------------------------------------------------------------
	/// Gets the sign.
	/// @return												-1 if the number is negative, 0 if it is zero, 1 if it is positive.
	//----------------------------------------------------------------------------------------
	maxon::Int Sign() const;

	//----------------------------------------------------------------------------------------
	/// Gets the highest bit position that is different than the sign bit. This is the position incremented by one for negative numbers.
	/// @return												The bit position. The return value is -1 if the number is 0.
	//----------------------------------------------------------------------------------------
	maxon::Int GetHighestNonSignBit() const;

	//----------------------------------------------------------------------------------------
	/// Gets the lowest bit position that is zero.
	/// @return												The bit position. The return value is -1 if the number is 0.
	//----------------------------------------------------------------------------------------
	maxon::Int GetLowestSetBit() const;

	//----------------------------------------------------------------------------------------
	/// Gets the lowest bit position that is zero.
	/// @return												The bit position. The return value is -1 if the number is -1.
	//----------------------------------------------------------------------------------------
	maxon::Int GetLowestClearedBit() const;

	//----------------------------------------------------------------------------------------
	/// Checks if the bit at a certain position is set.
	/// @return												True, if the bit is set, false otherwise.
	//----------------------------------------------------------------------------------------
	Bool IsBitSet(maxon::Int bit) const;

	//----------------------------------------------------------------------------------------
	/// Get the lowest 8 bits.
	/// @return												The lowest 8 bits as an unsigned 8-bit integer.
	//----------------------------------------------------------------------------------------
	maxon::UChar GetLowestBits8U() const;

	//----------------------------------------------------------------------------------------
	/// Get the lowest 8 bits.
	/// @return												The lowest 8 bits as an signed 8-bit integer.
	//----------------------------------------------------------------------------------------
	maxon::Char GetLowestBits8S() const;

	//----------------------------------------------------------------------------------------
	/// Get the lowest 32 bits.
	/// @return												The lowest 32 bits as an unsigned 32-bit integer.
	//----------------------------------------------------------------------------------------
	maxon::UInt32 GetLowestBits32U() const;

	//----------------------------------------------------------------------------------------
	/// Get the lowest 32 bits.
	/// @return												The lowest 32 bits as an signed 32-bit integer.
	//----------------------------------------------------------------------------------------
	maxon::Int32 GetLowestBits32S() const;

	//----------------------------------------------------------------------------------------
	/// Get the lowest 64 bits.
	/// @return												The lowest 64 bits as an unsigned 64-bit integer.
	//----------------------------------------------------------------------------------------
	maxon::UInt64 GetLowestBits64U() const;

	//----------------------------------------------------------------------------------------
	/// Get the lowest 64 bits.
	/// @return												The lowest 64 bits as an signed 64-bit integer.
	//----------------------------------------------------------------------------------------
	maxon::Int64 GetLowestBits64S() const;

	//----------------------------------------------------------------------------------------
	/// Gets a copy of the internal data.
	/// @param data										The BaseArray that will hold the data copy.
	/// @return												True, if the function succeeded, false otherwise.
	//----------------------------------------------------------------------------------------
	Bool GetDataCopy(maxon::BaseArray<maxon::UChar>& data) const;

	//----------------------------------------------------------------------------------------
	/// Performs the add operation.
	/// @param[in] b									The value to add to this.
	//----------------------------------------------------------------------------------------
	void Add(const BigInteger* b);

	//----------------------------------------------------------------------------------------
	/// Performs the subtract operation.
	/// @param[in] b									The value to subtract to this.
	//----------------------------------------------------------------------------------------
	void Sub(const BigInteger* b);

	//----------------------------------------------------------------------------------------
	/// Increments the value by one.
	//----------------------------------------------------------------------------------------
	void Inc();

	//----------------------------------------------------------------------------------------
	/// Decrements the value by one.
	//----------------------------------------------------------------------------------------
	void Dec();

	//----------------------------------------------------------------------------------------
	/// Performs the multiply operation.
	/// @param[in] b									The value to multiply to this.
	//----------------------------------------------------------------------------------------
	void Mul(const BigInteger* b);

	//----------------------------------------------------------------------------------------
	/// Performs the divide operation.
	/// @param[in] b									The value with which is this to divide. The result is 0, if b is 0 or if its absolute value is bigger than the absolute value of this.
	//----------------------------------------------------------------------------------------
	void Div(const BigInteger* b);

	//----------------------------------------------------------------------------------------
	/// Performs the modulo operation.
	/// @param[in] b									The value with which is this to divide. The result is 0, if b is 0 or if its absolute value is bigger than the absolute value of this.
	//----------------------------------------------------------------------------------------
	void Mod(const BigInteger* b);

	//----------------------------------------------------------------------------------------
	/// Performs the divide and modulo operation.
	/// @param[in] b									The value with which is this to divide. The result is 0, if b is 0 or if its absolute value is bigger than the absolute value of this.
	/// @param[in] r									The remainder of the division will be stored in r.
	//----------------------------------------------------------------------------------------
	void DivMod(const BigInteger* b, BigInteger* r);

	//----------------------------------------------------------------------------------------
	/// Performs the power operation.
	/// @param[in] b									Raises this to the power of b. The result will be 0 if b is negative.
	//----------------------------------------------------------------------------------------
	void Pow(const BigInteger* b);

	//----------------------------------------------------------------------------------------
	/// Performs the power operation and takes the result modulo mod.
	/// @param[in] b									Raises this to the power of b. The result will be 0 if b is negative.
	/// @param[in] mod								The modulo value.
	//----------------------------------------------------------------------------------------
	void PowMod(const BigInteger* b, const BigInteger* mod);

	//----------------------------------------------------------------------------------------
	/// Calculates the greatest common divisor of this and b. Both values must be greater than zero, otherwise the value will remain unchanged.
	/// @param[in] b									Another BigInteger.
	//----------------------------------------------------------------------------------------
	void GreatestCommonDivisor(const BigInteger* b);

	//----------------------------------------------------------------------------------------
	/// Calculates the multiplicative inverse of this modulo m. This must be smaller than m. The new result of this will be greater or equal to zero and smaller than m.
	/// @param[in] m									Another BigInteger. This value must be greater than zero.
	/// @return												True, if there is a multiplicative inverse, false otherwise. The value of this is unchanged if there is no multiplicative inverse.
	//----------------------------------------------------------------------------------------
	Bool MultiplicativeInverse(const BigInteger* m);

	//----------------------------------------------------------------------------------------
	/// Performs the Left shift operation. If the number of bits to shift is less than 0 the bits are shifted right.
	/// @param[in] s									The number of bits to shift.
	//----------------------------------------------------------------------------------------
	void LeftShift(maxon::Int s);

	//----------------------------------------------------------------------------------------
	/// Performs the Right shift operation. If the number of bits to shift is less than 0 the bits are shifted left.
	/// @param[in] s									The number of bits to shift.
	//----------------------------------------------------------------------------------------
	void RightShift(maxon::Int s);

	//----------------------------------------------------------------------------------------
	/// Negates the value.
	//----------------------------------------------------------------------------------------
	void Negate();

	//----------------------------------------------------------------------------------------
	/// Sets a bit in the integer.
	/// @param[in] bit								The position if the bit which is to set.
	//----------------------------------------------------------------------------------------
	void SetBit(maxon::Int bit);

	//----------------------------------------------------------------------------------------
	/// Clears a bit in the integer.
	/// @param[in] bit								The position if the bit which is to clear.
	//----------------------------------------------------------------------------------------
	void ClearBit(maxon::Int bit);

	//----------------------------------------------------------------------------------------
	/// Toggles a bit in the integer.
	/// @param[in] bit								The position if the bit which is to toggle.
	//----------------------------------------------------------------------------------------
	void ToggleBit(maxon::Int bit);

	//----------------------------------------------------------------------------------------
	/// Compares two BigInteger values.
	/// @return												The comparison result.
	//----------------------------------------------------------------------------------------
	maxon::COMPARERESULT Compare(const BigInteger* arg2) const;

	//----------------------------------------------------------------------------------------
	// Copies the data from another BigInteger.
	/// @param[in] src								The source value.
	/// @return												True, if the function succeeded, false otherwise.
	//----------------------------------------------------------------------------------------
	Bool CopyFrom(const BigInteger* src);
};


// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

class iBigInteger;

struct BigIntegerLib : public C4DLibrary
{
	BigInteger*		(*BigInteger_Alloc)();
	void					(*BigInteger_Free)(BigInteger *&pBigInteger);

	Bool					(iBigInteger::*Set1)(maxon::Char c);
	Bool					(iBigInteger::*Set2)(maxon::UChar c);
	Bool					(iBigInteger::*Set3)(maxon::Int16 i);
	Bool					(iBigInteger::*Set4)(maxon::UInt16 u);
	Bool					(iBigInteger::*Set5)(maxon::Int32 i);
	Bool					(iBigInteger::*Set6)(maxon::UInt32 u);
	Bool					(iBigInteger::*Set7)(maxon::Int64 i);
	Bool					(iBigInteger::*Set8)(maxon::UInt64 u);
	Bool					(iBigInteger::*SetRandom)(maxon::Int bitCount, SecureRandomProvider provider);
	Bool					(iBigInteger::*SetRandomPrime)(maxon::Int bitCount, maxon::UInt certainity, SecureRandomProvider provider);
	Bool					(iBigInteger::*IsEven)() const;
	Bool					(iBigInteger::*IsOdd)() const;
	Bool					(iBigInteger::*IsOne)() const;
	Bool					(iBigInteger::*IsZero)() const;
	Bool					(iBigInteger::*IsNegative)() const;
	Bool					(iBigInteger::*IsPowerOfTwo)() const;
	Bool					(iBigInteger::*IsProbablyPrime)(maxon::UInt certainity) const;
	maxon::Int (iBigInteger::*Sign)() const;
	maxon::Int (iBigInteger::*GetHighestNonSignBit)() const;
	maxon::Int (iBigInteger::*GetLowestSetBit)() const;
	maxon::Int (iBigInteger::*GetLowestClearedBit)() const;
	Bool					(iBigInteger::*IsBitSet)(maxon::Int bit) const;
	maxon::UChar (iBigInteger::*GetLowestBits8U)() const;
	maxon::Char (iBigInteger::*GetLowestBits8S)() const;
	maxon::UInt32 (iBigInteger::*GetLowestBits32U)() const;
	maxon::Int32 (iBigInteger::*GetLowestBits32S)() const;
	maxon::UInt64 (iBigInteger::*GetLowestBits64U)() const;
	maxon::Int64 (iBigInteger::*GetLowestBits64S)() const;
	Bool					(iBigInteger::*GetDataCopy)(maxon::BaseArray<maxon::UChar>& data) const;
	void					(iBigInteger::*Add)(const BigInteger* b);
	void					(iBigInteger::*Sub)(const BigInteger* b);
	void					(iBigInteger::*Inc)();
	void					(iBigInteger::*Dec)();
	void					(iBigInteger::*Mul)(const BigInteger* b);
	void					(iBigInteger::*Div)(const BigInteger* b);
	void					(iBigInteger::*Mod)(const BigInteger* b);
	void					(iBigInteger::*DivMod)(const BigInteger* b, BigInteger* r);
	void					(iBigInteger::*Pow)(const BigInteger* b);
	void					(iBigInteger::*PowMod)(const BigInteger* b, const BigInteger* mod);
	void					(iBigInteger::*GreatestCommonDivisor)(const BigInteger* b);
	Bool					(iBigInteger::*MultiplicativeInverse)(const BigInteger* m);
	void					(iBigInteger::*LeftShift)(maxon::Int s);
	void					(iBigInteger::*RightShift)(maxon::Int s);
	void					(iBigInteger::*Negate)();
	void					(iBigInteger::*SetBit)(maxon::Int bit);
	void					(iBigInteger::*ClearBit)(maxon::Int bit);
	void					(iBigInteger::*ToggleBit)(maxon::Int bit);
	maxon::COMPARERESULT (iBigInteger::*Compare)(const BigInteger* arg2) const;
	Bool					(iBigInteger::*CopyFrom)(const BigInteger* src);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif // _LIB_BIG_INTEGER_H_
