/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DBASECONTAINER_H
#define __C4DBASECONTAINER_H

#ifdef __API_INTERN__
	#include "basecontainer.h"
#else

	#include "ge_math.h"
	#include "c4d_basetime.h"
	#include "c4d_string.h"
	#include "c4d_file.h"
	#include "c4d_gedata.h"
	#include "c4d_uuid.h"

	#ifdef __MAC
		#if defined(__cplusplus) && defined(_MSL_USING_NAMESPACE)
using namespace std;
		#endif
	#elif !defined __PC
		#include <stddef.h>
	#endif

class BaseDocument;
class BaseObject;
class BaseMaterial;

class BaseContainer
{
	#define BcCall(fnc) (this->*C4DOS.Bc->fnc)

private:
	C4D_RESERVE_PRIVATE_TYPE(void*, dummy1);
	C4D_RESERVE_PRIVATE_TYPE(Int, dummy2);
	C4D_RESERVE_PRIVATE_TYPE(Int32, dummy3);
	C4D_RESERVE_PRIVATE_TYPE(Int32, dummy4);
	C4D_RESERVE_PRIVATE_TYPE(Int32, dummy5);

public:
#ifdef	__C4D_NO_NEW_DELETE__
	void* operator new(size_t, const std::nothrow_t&, int line, const Char* file) throw();
	void operator delete(void* del);
	void operator delete(void* del, int line, const Char* file);

	void* operator new(size_t, void* place) { return place; }
	void operator delete(void*, void*) { }
#endif

	BaseContainer(void);
	BaseContainer(Int32 id);
	BaseContainer(const BaseContainer& n);
	~BaseContainer(void);

	const BaseContainer& operator = (const BaseContainer& n);
	BaseContainer* GetClone(COPYFLAGS flags, AliasTrans* trans) const { return BcCall(GetClone) (flags, trans); }
	Bool CopyTo(BaseContainer* dst, COPYFLAGS flags, AliasTrans* trans) const { return BcCall(CopyTo) (dst, flags, trans); }

	void FlushAll(void) { return BcCall(FlushAll) (); }

	Int32 GetId() const { return BcCall(GetId) (); }
	void SetId(Int32 c_id){ BcCall(SetId) (c_id); }
	UInt32 GetDirty() const { return BcCall(GetDirty) (); }

	Bool RemoveData(Int32 id) { return BcCall(RemoveData) (id); }
	Bool RemoveIndex(Int32 i) { return BcCall(RemoveIndex) (i); }

	Int32 FindIndex(Int32 id, GeData** ppData = nullptr) const { return BcCall(FindIndex) (id, ppData); }
	Int32 GetIndexId(Int32 index) const { return BcCall(GetIndexId) (index); }
	const GeData* GetDataPointer(Int32 id) const { return BcCall(GetDataPointer) (id); }
	void GetDataPointers(const Int32* ids, Int32 cnt, const GeData** data) const { return BcCall(GetDataPointers) (ids, cnt, data); }

	GeData* GetIndexData(Int32 index) const { return BcCall(GetIndexData) (index); }
	GeData* InsData(Int32 id, const GeData& n) { return BcCall(InsData) (id, n); }
	GeData* InsDataAfter(Int32 id, const GeData& n, GeData* last) { return BcCall(InsDataAfter) (id, n, last); }
	GeData* SetData(Int32 id, const GeData& n) { return BcCall(SetData) (id, n); }
	const GeData& GetData(Int32 id) const { return BcCall(GetData) (id); }

	Bool operator == (const BaseContainer& d) const;
	Bool operator != (const BaseContainer& d) const;

	Bool GetBool		 (Int32 id, Bool preset = false) const { return BcCall(GetBool) (id, preset); }
	Int32	GetInt32		(Int32 id, Int32 preset = 0) const { return BcCall(GetInt32) (id, preset); }
	UInt32 GetUInt32	 (Int32 id, UInt32 preset = 0) const { return BcCall(GetUInt32) (id, preset); }
	Int64	GetInt64		(Int32 id, Int64 preset = 0) const { return BcCall(GetInt64) (id, preset); }
	UInt64 GetUInt64	 (Int32 id, UInt64 preset = 0) const { return BcCall(GetUInt64) (id, preset); }
	Float	GetFloat		(Int32 id, Float preset = 0.0) const { return BcCall(GetFloat) (id, preset); }
	void*									GetVoid			(Int32 id, void* preset = nullptr) const { return BcCall(GetVoid) (id, preset); }
	void*									GetMemoryAndRelease	(Int32 id, Int& count, void* preset = nullptr) { return BcCall(GetMemoryAndRelease) (id, count, preset); }
	void*									GetMemory		(Int32 id, Int& count, void* preset = nullptr) const { return BcCall(GetMemory) (id, count, preset); }
	Vector GetVector	 (Int32 id, const Vector& preset = Vector()) const { return BcCall(GetVector) (id, preset); }
	Matrix GetMatrix	 (Int32 id, const Matrix& preset = Matrix()) const { return BcCall(GetMatrix) (id, preset); }
	String GetString	 (Int32 id, const String& preset = String()) const { return BcCall(GetString) (id, preset); }
	C4DUuid	GetUuid			(Int32 id, const C4DUuid& preset = C4DUuid(DC)) const { return BcCall(GetUuid) (id, preset); }
	Filename GetFilename (Int32 id, const Filename& preset = Filename()) const { return BcCall(GetFilename) (id, preset); }
	BaseTime GetTime		 (Int32 id, const BaseTime& preset = BaseTime()) const { return BcCall(GetTime) (id, preset); }
	BaseContainer	GetContainer(Int32 id) const { return BcCall(GetContainer) (id); }
	BaseContainer*				GetContainerInstance(Int32 id) const { return BcCall(GetContainerInstance) (id); }
	BaseList2D*						GetLink					(Int32 id, const BaseDocument* doc, Int32 instanceof = 0) const { return BcCall(GetLink) (id, doc, instanceof); }
	BaseObject*						GetObjectLink		(Int32 id, const BaseDocument* doc) const;
	BaseMaterial*					GetMaterialLink	(Int32 id, const BaseDocument* doc) const;
	BaseLink*							GetBaseLink (Int32 id) const;
	const CustomDataType*	GetCustomDataType	(Int32 id, Int32 datatype) const;

	Int32	GetType(Int32 id) const;

	void SetBool				(Int32 id, Bool b) { return BcCall(SetBool) (id, b); }
	void SetInt32				(Int32 id, Int32 l) { return BcCall(SetInt32) (id, l); }
	void SetUInt32			(Int32 id, UInt32 l) { return BcCall(SetUInt32) (id, l); }
	void SetInt64				(Int32 id, Int64 l) { return BcCall(SetInt64) (id, l); }
	void SetUInt64			(Int32 id, UInt64 l) { return BcCall(SetUInt64) (id, l); }
	void SetFloat				(Int32 id, Float r) { return BcCall(SetFloat) (id, r); }
	void SetVoid				(Int32 id, void* v) { return BcCall(SetVoid) (id, v); }
	void SetMemory			(Int32 id, void* mem, Int count) { return BcCall(SetMemory) (id, mem, count); }
	void SetVector			(Int32 id, const Vector& v) { return BcCall(SetVector) (id, v); }
	void SetMatrix			(Int32 id, const Matrix& m) { return BcCall(SetMatrix) (id, m); }
	void SetString			(Int32 id, const String& s) { return BcCall(SetString) (id, s); }
	void SetUuid				(Int32 id, const C4DUuid& u) { return BcCall(SetUuid) (id, u); }
	void SetFilename		(Int32 id, const Filename& f) { return BcCall(SetFilename) (id, f); }
	void SetTime				(Int32 id, const BaseTime& b) { return BcCall(SetTime) (id, b); }
	void SetContainer		(Int32 id, const BaseContainer& s) { return BcCall(SetContainer) (id, s); }
	void SetLink				(Int32 id, C4DAtomGoal* link) { return BcCall(SetLink) (id, link); }

	void MergeContainer(const BaseContainer& src);

	Bool GetParameter(const DescID& id, GeData& t_data) const { return BcCall(GetParameter) (id, t_data); }
	Bool SetParameter(const DescID& id, const GeData& t_data) { return BcCall(SetParameter) (id, t_data); }

	void Sort() { BcCall(Sort) (); };
};

#endif

#endif
