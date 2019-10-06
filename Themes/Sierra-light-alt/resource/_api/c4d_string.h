/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DSTRING_H
#define __C4DSTRING_H

#ifdef __API_INTERN__
	#include "ge_string.h"
#else

#ifdef __MAC
	#if defined(__cplusplus)
		#include <new>
		using namespace std;
	#endif
#elif defined __LINUX
	#include <new>
#elif	defined	__PC
	#include <new>
#endif

#include "operatingsystem.h"

class String
{
	#define StCall(fnc) (this->*C4DOS.St->fnc)

private:
	C4D_RESERVE_PRIVATE_TYPE(Int32, dummy1);
	C4D_RESERVE_PRIVATE_TYPE(Int32, dummy2);
	C4D_RESERVE_PRIVATE_TYPE(void*, dummy3);
	C4D_RESERVE_PRIVATE_TYPE(void*, dummy4);

public:
#ifdef	__C4D_NO_NEW_DELETE__

	void* operator new(size_t, const std::nothrow_t&, int line, const Char* file) throw()
	{
		return C4DOS.St->Alloc();
	}

	void operator delete(void* del, int line, const Char* file)
	{
		C4DOS.St->Free((String*)del);
	}

	void operator delete(void* del)
	{
		C4DOS.St->Free((String*)del);
	}

	void* operator new(size_t, void* place) { return place; }
	void operator delete(void*, void*) { }
#endif

	void CopyTo(String* str) const
	{
		C4DOS.St->CopyTo(this, str);
	}

	const String& operator = (const String& cs)
	{
		C4DOS.St->CopyTo(&cs, this);
		return *this;
	}

	String(void)
	{
		C4DOS.St->Init(this);
	}

	String(const String& cs)
	{
		C4DOS.St->Init(this);
		C4DOS.St->CopyTo(&cs, this);
	}

	String(const UInt16* s)
	{
		C4DOS.St->Init(this);
		StCall(SetUcBlock) (s, -1);
	}

	String(const Char* cstr, STRINGENCODING type = STRINGENCODING_XBIT)
	{
		C4DOS.St->Init(this);
		C4DOS.St->InitCString(this, cstr, -1, type);
	}

	String(Int count, UInt16 fillch)
	{
		C4DOS.St->Init(this);
		C4DOS.St->InitArray(this, Int32(count), fillch);
	}

	~String(void)
	{
		C4DOS.St->Flush(this);
	}

	Int32 GetLength() const
	{
		return StCall(GetLength) ();
	}

	Bool Content() const { return GetLength() != 0; }

	friend const String operator + (const String& Str1, const String& Str2)
	{
		String s(Str1);
		s += Str2;
		return s;
	}

	const String& operator += (const String& Str)
	{
		Insert(GetLength(), Str);
		return *this;
	}

	Bool operator < (const String& Str) const
	{
		return Compare(Str) < 0;
	}

	Bool operator > (const String& Str) const
	{
		return Compare(Str) > 0;
	}

	Bool operator <= (const String& Str) const
	{
		return Compare(Str) <= 0;
	}

	Bool operator >= (const String& Str) const
	{
		return Compare(Str) >= 0;
	}

	Bool operator == (const String& Str) const
	{
		return Compare(Str) == 0;
	}

	Bool operator != (const String& Str) const
	{
		return Compare(Str) != 0;
	}

	// 0 == , <0 < , >0 >
	Int Compare(const String& cs) const
	{
		return StCall(Compare) (cs);
	}

	Int LexCompare(const String& cs) const
	{
		return StCall(LexCompare) (cs);
	}

	Int RelCompare(const String& cs) const
	{
		return StCall(RelCompare) (cs);
	}

	Int ComparePart(const String& Str, Int cnt, Int pos) const
	{
		return StCall(ComparePart) (Str, Int32(cnt), Int32(pos));
	}

	Int LexComparePart(const String& Str, Int cnt, Int pos) const
	{
		return StCall(LexComparePart) (Str, Int32(cnt), Int32(pos));
	}

	Bool FindFirst(const String& cs, Int32* pos, Int start = 0) const
	{
		return StCall(FindFirst) (cs, pos, Int32(start));
	}

	Bool FindLast(const String& cs, Int32* pos, Int start = -1) const
	{
		return StCall(FindLast) (cs, pos, Int32(start));
	}

	Bool FindFirst(UInt16 ch, Int32* pos, Int start = 0) const
	{
		return StCall(FindFirstCh) (ch, pos, Int32(start));
	}

	Bool FindLast(UInt16 ch, Int32* pos, Int start = -1) const
	{
		return StCall(FindLastCh) (ch, pos, Int32(start));
	}

	// searches a string case insensitive, "findupper" has to be uppercase!!!
	Bool FindFirstUpper(const String& findupper, Int32* pos, Int start) const
	{
		return StCall(FindFirstUpper) (findupper, pos, Int32(start));
	}

	Bool FindLastUpper(const String& findupper, Int32* pos, Int start) const
	{
		return StCall(FindLastUpper) (findupper, pos, Int32(start));
	}

	void Delete(Int pos, Int count)
	{
		StCall(Delete) (Int32(pos), Int32(count));
	}

	void Insert(Int pos, UInt16 ch)
	{
		String tmp = String(1, ch);
		StCall(Insert) (Int32(pos), tmp, -1, -1);
	}

	void Insert(Int pos, const String& cs, Int start = -1, Int end = -1)
	{
		StCall(Insert) (Int32(pos), cs, Int32(start), Int32(end));
	}

	String SubStr(Int start, Int count) const
	{
		return StCall(SubStr) (Int32(start), Int32(count));
	}

	String Left(Int count) const
	{
		return SubStr(0, Int32(count));
	}

	String Right(Int count) const
	{
		return SubStr(GetLength() - Int32(count), Int32(count));
	}

	Float ParseToFloat(Int32* error = nullptr, Int unit = 0, Int angletype = 0, Int base = 10) const
	{
		return StCall(ParseToFloat) (error, Int32(unit), Int32(angletype), Int32(base));
	}

	Int32 ParseToInt32(Int32* error = nullptr) const
	{
		return StCall(ParseToInt32) (error);
	}

	static String MemoryToString(Int64 mem) { return C4DOS.St->MemoryToString(mem); }
	static String HexToString(UInt32 v, Bool prefix0x = true) { return C4DOS.St->HexToString32(v, prefix0x); }
	static String HexToString(UInt64 v, Bool prefix0x = true) { return C4DOS.St->HexToString64(v, prefix0x); }
	static String IntToString(Int32 l) { return C4DOS.St->IntToString64((Int64)l); }
	static String IntToString(Int64 l) { return C4DOS.St->IntToString64(l); }
	static String UIntToString(UInt32 l) { return C4DOS.St->UIntToString64((UInt64)l); }
	static String UIntToString(UInt64 l) { return C4DOS.St->UIntToString64(l); }
	static String FloatToString(Float32 v, Int32 vvk = -1, Int32 nnk = -1, Bool e = false, UInt16 xchar = '0') { return C4DOS.St->FloatToString32(v, vvk, nnk, e, xchar); }
	static String FloatToString(Float64 v, Int32 vvk = -1, Int32 nnk = -1, Bool e = false, UInt16 xchar = '0') { return C4DOS.St->FloatToString64(v, vvk, nnk, e, xchar); }

	static String VectorToString(const Vector64& v, Int32 nnk = -1)
	{
		return "(" + FloatToString((Float64)v.x, -1, nnk) + ";" + FloatToString((Float64)v.y, -1, nnk) + ";" + FloatToString((Float64)v.z, -1, nnk) + ")";
	}

	static String VectorToString(const Vector32& v, Int32 nnk = -1)
	{
		return "(" + FloatToString((Float32)v.x, -1, nnk) + ";" + FloatToString((Float32)v.y, -1, nnk) + ";" + FloatToString((Float32)v.z, -1, nnk) + ")";
	}

	Int64 ToInt64(Bool* error = nullptr) const { return StCall(ToInt64) (error); }
	Int32 ToInt32(Bool* error = nullptr) const { return StCall(ToInt32) (error); }
	UInt64 ToUInt64(Bool* error = nullptr) const { return StCall(ToUInt64) (error); }
	UInt32 ToUInt32(Bool* error = nullptr) const { return StCall(ToUInt32) (error); }

	Float ToFloat(Bool* error = nullptr) const { return StCall(ToFloat) (error); }

	Int ToInt(Bool* error = nullptr) const
	{
#ifdef __C4D_64BIT
		return ToInt64(error);
#else
		return ToInt32(error);
#endif
	}

	UInt ToUInt(Bool* error = nullptr) const
	{
#ifdef __C4D_64BIT
		return ToUInt64(error);
#else
		return ToUInt32(error);
#endif
	}

	String ToUpper() const
	{
		return StCall(ToUpper) ();
	}

	String ToLower() const
	{
		return StCall(ToLower) ();
	}

	Int32 GetCStringLen(STRINGENCODING type = STRINGENCODING_XBIT) const
	{
		return StCall(GetCStringLen) (type);
	}

	Int32 GetCString(Char* scstr, Int max, STRINGENCODING type = STRINGENCODING_XBIT) const
	{
		return StCall(GetCString) (scstr, Int32(max), type);
	}

	Char* GetCStringCopy(STRINGENCODING type = STRINGENCODING_XBIT) const;

	void SetCString(const Char* cstr, Int count = -1, STRINGENCODING type = STRINGENCODING_XBIT)
	{
		C4DOS.St->InitCString(this, cstr, Int32(count), type);
	}

	Int32 SetCStringR(const Char* cstr, Int count = -1, STRINGENCODING type = STRINGENCODING_XBIT)
	{
		C4DOS.St->InitCString(this, cstr, Int32(count), type);
		return GetLength();
	}

	void GetUcBlock(UInt16* Ubc, Int maxSize) const
	{
		StCall(GetUcBlock) (Ubc, Int32(maxSize));
	}

	void GetUcBlockNull(UInt16* Ubc, Int maxSize) const
	{
		StCall(GetUcBlockNull) (Ubc, Int32(maxSize));
	}

	void SetUcBlock(const UInt16* Ubc, Int count)
	{
		StCall(SetUcBlock) (Ubc, Int32(count));
	}

	class PChar
	{
		friend class String;

private:
		String* _str;
		Int32		_pos;

		PChar(String* str, Int pos)
		{
			_str = str;
			_pos = Int32(pos);
		}

public:
		PChar& operator = (const PChar& rhs)
		{
			C4DOS.St->SetChr(_str, _pos, C4DOS.St->GetChr(rhs._str, rhs._pos));
			return *this;
		}

		PChar& operator = (UInt16 c)
		{
			C4DOS.St->SetChr(_str, _pos, c);
			return *this;
		}

		operator UInt16() const
		{
			return C4DOS.St->GetChr(_str, _pos);
		}
	};

	const PChar operator[] (Int pos) const
	{
		return PChar((String*)this, Int32(pos));
	}

	PChar operator[] (Int pos)
	{
		return PChar((String*)this, Int32(pos));
	}
};

#ifdef __LEGACY_API
inline String LongToString(Int32 l) { return C4DOS.St->LongToString(l); }
inline String LLongToString(Int64 l) { return C4DOS.St->LLongToString(l); }
inline String RealToString(Float v, Int32 vvk = -1, Int32 nnk = -1, Bool e = false, UInt16 xchar = '0') { return C4DOS.St->RealToString(v, vvk, nnk, e, xchar); }
inline String PtrToString(const void* hex) { return String::HexToString((UInt)hex); }
inline String MemoryToString(Int64 mem) { return String::MemoryToString(mem); }
#endif

#endif

#endif
