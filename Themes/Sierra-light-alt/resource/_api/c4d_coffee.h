/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DCOFFEE_H
#define __C4DCOFFEE_H

#ifdef __API_INTERN__
abc def xyz
#endif

class String;
class Coffee;
class Value;
class GeData;

Bool GeCoffeeCompileString(Coffee* cof, const String& src);
Bool GeCoffeeCompileFile(Coffee* cof, const Filename& file);

VALUE* GeCoffeeAddGlobalSymbol(Coffee* cof, const String& name);
VALUE* GeCoffeeFindGlobalSymbol(Coffee* cof, const String& name);

Coffee* GetCoffeeMaster(void);

Bool GeCoffeeExecute(Coffee* cof, VALUE* func, GeData* retval = nullptr, GeData* arg1 = nullptr, GeData* arg2 = nullptr, GeData* arg3 = nullptr);
Bool GeCoffeeGeData2Value(Coffee* cof, const GeData& src, VALUE* dest);
Bool GeCoffeeValue2GeData(Coffee* cof, VALUE* src, GeData* dest);
Bool GeCoffeeGetLastError(Coffee* cof, String* err_string, Int32* err_line, Int32* err_pos);

Bool CodeEditor_Open(BaseList2D* obj, CodeEditorCallback* callback, const BaseContainer& bc = BaseContainer());

enum COFFEE_STYPE
{
	COFFEE_STYPE_CLASS		= 1,	// class definition
	COFFEE_STYPE_DATA			= 2,	// public data
	COFFEE_STYPE_CDATA		= 3,	// protected/static data
	COFFEE_STYPE_PDATA		= 4,	// private data
	COFFEE_STYPE_FUNCTION	= 5,	// function
	COFFEE_STYPE_METHOD		= 6,	// public method
	COFFEE_STYPE_CMETHOD	= 7,	// protected method
	COFFEE_STYPE_PMETHOD	= 8		// private method
} ENUM_END_LIST(COFFEE_STYPE);

enum COFFEE_VTYPE
{
	COFFEE_VTYPE_NIL				= 0,
	COFFEE_VTYPE_LONG				= 1,
	COFFEE_VTYPE_FLOAT			= 2,
	COFFEE_VTYPE_VECTOR			= 3,
	COFFEE_VTYPE_VOID				= 4,
	COFFEE_VTYPE_BYTES			= 5,
	COFFEE_VTYPE_STRING			= 6,
	COFFEE_VTYPE_CLASS			= 7,
	COFFEE_VTYPE_OBJECT			= 8,
	COFFEE_VTYPE_ARRAY			= 9,
	COFFEE_VTYPE_BYTECODE		= 10,
	COFFEE_VTYPE_CODE				= 11,
	COFFEE_VTYPE_EXTCODE		= 12,

	COFFEE_VTYPE_EXCEPTION	= 13,
	COFFEE_VTYPE_SEXCEPTION	= 14,
	COFFEE_VTYPE_DICTIONARY	= 15,
	COFFEE_VTYPE_ENTRY			= 16,
	COFFEE_VTYPE_INSTANCE		= 17,

	COFFEE_VTYPE_NUMBER			= 99
} ENUM_END_LIST(COFFEE_VTYPE);

enum CoffeeError
{
	COFFEEERROR_BBLOCK			= 1,
	COFFEEERROR_MEM					= 2,
	COFFEEERROR_ARGV				= 3,
	COFFEEERROR_ARGW				= 4,
	COFFEEERROR_BTYP				= 5,
	COFFEEERROR_BOPCODE			= 6,
	COFFEEERROR_NPROC				= 7,
	COFFEEERROR_BMETHOD			= 8,
	COFFEEERROR_NMETHOD			= 9,
	COFFEEERROR_NPUBLIC			= 10,
	COFFEEERROR_MPROTECTED	= 11,
	COFFEEERROR_MPRIVATE		= 12,
	COFFEEERROR_SUBSCR			= 13,
	COFFEEERROR_STACKOV			= 14,
	COFFEEERROR_DIV0				= 15,
	COFFEEERROR_EXEPT				= 16,
	COFFEEERROR_INVALIDID		= 17,
	COFFEEERROR_PARAMACCESS	= 18,
	COFFEEERROR_PARAMVALUE	= 19,
	COFFEEERROR_PARAMTYPE		= 20,
	COFFEEERROR_EDEC				= 100,
	COFFEEERROR_EMDEC				= 101,
	COFFEEERROR_EFUNC				= 102,
	COFFEEERROR_IRDEF				= 103,
	COFFEEERROR_ECNAME			= 104,
	COFFEEERROR_TMLOOP			= 105,
	COFFEEERROR_BOLOOP			= 106,
	COFFEEERROR_COLOOP			= 107,
	COFFEEERROR_SOLOOP			= 108,
	COFFEEERROR_NCASE				= 109,
	COFFEEERROR_NVAR				= 110,
	COFFEEERROR_ELVAL				= 111,
	COFFEEERROR_NCLASSM			= 112,
	COFFEEERROR_BPARENT			= 113,
	COFFEEERROR_NPARENT			= 114,
	COFFEEERROR_BSUPER			= 115,
	COFFEEERROR_NSUPER			= 116,
	COFFEEERROR_PROTECT			= 117,
	COFFEEERROR_EVAR				= 118,
	COFFEEERROR_EPRIM				= 119,
	COFFEEERROR_ISPACE			= 120,
	COFFEEERROR_ECLOSE			= 121,
	COFFEEERROR_PARGV				= 122,
	COFFEEERROR_PARGW				= 123,
	COFFEEERROR_SYNTAX			= 124,
	COFFEEERROR_INCLUDE			= 125,
	COFFEEERROR_VARONLY			= 126,
	COFFEEERROR_CLASSB			= 200,
	COFFEEERROR_CLASS				= 201,
	COFFEEERROR_FUNC				= 202,
	COFFEEERROR_MEMBERF			= 203,
	COFFEEERROR_EXPECT			= 204
} ENUM_END_LIST(CoffeeError);

// Opcodes

class VALUE
{
	COFFEE_VTYPE v_type;
	union
	{
		Int32	v_integer;
		Float	v_float;
		Float	v_vector[3];
		void*	v_void;
	} v;

public:
	VALUE(void);

	Bool IsType(COFFEE_VTYPE type) const;

	COFFEE_VTYPE GetType(void) const;
	void SetNil(void);

	Int32	GetInt32(Int32* err = nullptr) const;
	Float	GetFloat(Int32* err = nullptr) const;
	Vector GetVector(Int32* err = nullptr) const;
	void*		GetVoid(Int32* err = nullptr) const;

	void SetVoid(const void* v);
	void SetInt32(Int32 i);
	void SetFloat(Float f);
	void SetVector(const Vector& v);

	VALUE*	GetObjMember(Int32 nr);

	VALUE*	GetArrayMember(Int32 i);
	void SetArray(ARRAY* a);

	OBJECT*	GetObject(Int32* err = nullptr);
	void SetObject(OBJECT* o);

	void SetString(CSTRING* s);
	String GetString(void);

	Bool IsInstanceOf(VALUE* cl, Int32* err = nullptr);

	Int32	GetSize(void);
	UChar*	GetBytes(void);
};

class	Coffee
{
private:
	Coffee();
	~Coffee();

public:
	VALUE*	GetGlobalClass(const String& name);

	CLASS*	AddGlobalClass(const String& name, const String& parent = String());
	Bool AddGlobalSymbol(const String& name, const VALUE* v, COFFEE_STYPE type);
	Bool AddGlobalFunction(const String& name, V_CODE fcn);

	Bool AddClassMember(const String& name, CLASS* c, COFFEE_STYPE type);
	Bool AddClassMethod(const String& name, CLASS* c, COFFEE_STYPE type, V_CODE fcn, Int32 argc = -1);

	CSTRING*	AllocString(const String& s);

	OBJECT*	NewObject(const String& cl_name);
	ARRAY*	NewArray(Int32 size);

	void Wrongcnt(Int32 n, Int32 cnt);
	void ErrCheckType(VALUE* v, COFFEE_VTYPE type, Int32* err = nullptr);
	void ErrCheckObjectType(VALUE* v, const String& cl_name, Int32* err = nullptr);
	void ErrCheckArgCount(Int32 argc, Int32 cnt, Int32* err = nullptr);

	void SetError(Int32 type, const String& s1 = String(), const String& s2 = String());
	void InstallErrorHook(COFFEE_ERRORHANDLER* priv_hndl, void* priv_data);

	Int32	GetType(void);

	const Filename&	GetRootFile(void);
	void SetRootFile(const Filename& fn);

	OBJECT* AllocDynamic(BaseList2D* bl, Bool coffeeallocation);
	CLASS*  AddInheritance(Int32 id, const String& name, const String& from, Bool use_constructor = true);

	static Coffee* Alloc();
	static void Free(Coffee*& cof);

	Bool CompileFile(const Filename& fn, Bool tofile);
};

#endif
