/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

//Base Effector class
#ifndef _C4D_BASEEFFECTOR_H_
#define _C4D_BASEEFFECTOR_H_

#ifdef __API_INTERN__
abc def xyz
#endif

#include "c4d.h"
#include "ge_dynamicarray.h"
#include "c4d_quaternion.h"

#define Obaseeffector			1018560
#define Obasemogen				1018639
#define ID_BASE_EDEFORMER	1019305
#define ID_MOTAGDATA			1018625	//Tag containing the MoData on a MoGraph Object
#define ID_MOBAKETAG			1019337	//MoGraph Bake Tag
#define Tmgselection			1021338

#define BASEEFFECTORLIB_ID 1019554
#define MODATALIB_ID			 440000059

#define MSG_EXECUTE_EFFECTOR			1018630
#define MSG_SAMPLE_EFFECTOR_VALUE	1019294
#define MSG_GET_MODATA						1019522
#define MSG_GET_MODATASELECTION		1021339
#define BC_ID_MODATAINDEX					440000062
#define BC_ID_MODATATAGINDEX			440000063

#define MSG_DISABLE_DELAY_EFFECTOR 440000146
#define MSG_ENABLE_DELAY_EFFECTOR	 440000147

#define BLEND_COUNT 21

//Effector Flags
#define EFFECTORFLAGS_HASFALLOFF			(1 << 0)
#define EFFECTORFLAGS_TIMEDEPENDENT		(1 << 1)
#define EFFECTORFLAGS_CAMERADEPENDENT	(1 << 2)

//MoData Flags
#define MOGENFLAG_CLONE_ON	(1 << 0)	//particles visibility
#define MOGENFLAG_DISABLE		(1 << 1)	//particle permanently disabled
#define MOGENFLAG_BORN			(1 << 2)	//just generated (INTERNAL USE ONLY)
#define MOGENFLAG_MODATASET	(1 << 3)	//the modata has been set and doesn't need the input of the transform panel
#define MOGENFLAG_COLORSET	(1 << 4)	//the modata color has been set and doesn't need to be updated
#define MOGENFLAG_TIMESET		(1 << 5)	//the modata time has been set and doesn't need to be updated

#define MDDIRTY_ARRAYCOUNT (1 << 0)		//Dirtyness for the array count itself (number of different arrays rather than length of arrays)
#define MDDIRTY_COUNT			 (1 << 1)		//Dirtyness for the length of the arrays
#define MDDIRTY_DATA			 (1 << 2)		//Dirtyness for the data in the arrays, must be manually set

class C4D_Falloff;

enum MD_TYPE
{
	MD_NONE		=	DA_NIL,
	MD_CHAR		= 40000000,
	MD_UCHAR	=	40000001,
	MD_LONG		= DTYPE_LONG,
	MD_ULONG	=	40000002,
	MD_LLONG	=	DA_LLONG,
	MD_MATRIX	= DA_MATRIX,
	MD_COLOR	= DTYPE_COLOR,
	MD_VECTOR	=	DTYPE_VECTOR,
	MD_NORMAL	= DTYPE_NORMAL,
	MD_REAL		= DTYPE_REAL,
	MD_BOOL		= DTYPE_BOOL
} ENUM_END_LIST(MD_TYPE);

enum
{
	MODATA_MATRIX	=	40000000,
	MODATA_COLOR,
	MODATA_SIZE,
	MODATA_UVW,
	MODATA_FLAGS,
	MODATA_WEIGHT,
	MODATA_CLONE,
	MODATA_TIME,
	MODATA_LASTMAT,
	MODATA_STARTMAT,
	MODATA_ALT_INDEX,
	MODATA_FALLOFF_WGT,
	MODATA_SPLINE_SEGMENT,
	MODATA_GROWTH
};

inline GeData GetMoDataDefault(Int32 id)
{
	switch (id)
	{
		case MODATA_LASTMAT:
		case MODATA_STARTMAT:
		case MODATA_MATRIX: return GeData(Matrix()); break;
		case MODATA_COLOR: return GeData(Vector(0.5)); break;
		case MODATA_SIZE: return GeData(Vector(1.0)); break;
		case MODATA_UVW: return GeData(Vector(0.0)); break;
		case MODATA_FLAGS: return GeData(MOGENFLAG_CLONE_ON | MOGENFLAG_BORN); break;
		case MODATA_WEIGHT:
		case MODATA_CLONE:
		case MODATA_TIME: return GeData(0.0); break;
		case MODATA_SPLINE_SEGMENT: return GeData(0); break;
		case MODATA_ALT_INDEX: return GeData(NOTOK); break;
		case MODATA_FALLOFF_WGT:
		case MODATA_GROWTH: return GeData(1.0); break;
		default: break;
	}

	return GeData();
};

inline MD_TYPE GetMoDataDefaultType(Int32 id)
{
	switch (id)
	{
		case MODATA_LASTMAT:
		case MODATA_STARTMAT:
		case MODATA_MATRIX: return MD_MATRIX; break;
		case MODATA_COLOR: return MD_COLOR; break;
		case MODATA_SIZE:
		case MODATA_UVW: return MD_VECTOR; break;
		case MODATA_SPLINE_SEGMENT:
		case MODATA_ALT_INDEX:
		case MODATA_FLAGS: return MD_LONG; break;
		case MODATA_WEIGHT:
		case MODATA_CLONE:
		case MODATA_FALLOFF_WGT:
		case MODATA_GROWTH:
		case MODATA_TIME: return MD_REAL; break;
		default: break;
	}
	
	return MD_NONE;
};

#define MDARRAYFLAG_NOTSEENBYEFFECTOR	 (1 << 0)	//Data is seen and modified by the Effector
#define MDARRAYFLAG_SEPERATECOMPONENTS (1 << 1)	//Vector should have seperate components in Effector (e.g. UV)
#define MDARRAYFLAG_2DVECTOR					 (1 << 2)	//Vector is a 2D vector rather than 3D (e.g. UV)

enum
{
	ID_MODATA_PASS = 100
};


// Motion Particle Transformation Data
struct Dpoint
{
	Matrix				m;

	inline Vector GetPos(void) const
	{
		return m.off;
	}

	inline Vector GetSize(void)
	{
		return Vector(Len(m.v1), Len(m.v2), Len(m.v3));
	}

	inline void GetMatrix(Matrix& h, const Vector& size) const
	{
		h = m;
		h.v1 -= h.off;
		h.v2 -= h.off;
		h.v3 -= h.off;
		h.v1	= !Cross(h.v2, h.v3) * size.x;
		h.v2	= !Cross(h.v3, h.v1) * size.y;
		h.v3	= !Cross(h.v1, h.v2) * size.z;
	}
};

// "Info Point" handles the information for each particle.
struct Ipoint
{
public:
	Ipoint()
	{
		flags	 = MOGENFLAG_CLONE_ON | MOGENFLAG_BORN;
		color	 = Vector(0.5);
		size	 = Vector(1.0);
		weight = 0.0;
		clone	 = 1.0;
		uvw	 = Vector(0.0);
		time = 0.0;
		alt_index = NOTOK;
	}
	~Ipoint()
	{
	}

	Vector color;			//color of the particle
	Vector size;			//size of the particle
	Vector uvw;				//particles direct UVW position
	Int32	 flags;			//particle flags
	Float	 weight;		//offset against falloff value to allow effectors to drive other effectors
	Float	 clone;			//the index of the child that will be cloned in the cloner object
	Float	 time;			//delta time for each clone
	Matrix lastmat;		//last position
	Matrix startmat;	//starting position
	Int32	 alt_index;	//alternative index for particles, instancer etc with some effectors, e.g. step.
};

template <class TYPE> class MDArray
{
private:
	TYPE*				 ptr;
	mutable TYPE dv;
	Int					 count;

public:
	MDArray(void) { ptr = nullptr; dv = TYPE(); count = 0; }
	MDArray(TYPE* array_pointer, Int32 array_count, TYPE default_value/*= TYPE()*/)
	{
		ptr = array_pointer;
		dv	= default_value;
		count = array_count;
	}
	~MDArray(void) { }

	void Fill(const TYPE& default_value)
	{
		if (ptr && count)
		{
			Int i = 0;
			for (i = count - 1; i >= 0; --i)
				ptr[i] = default_value;
		}
		dv = default_value;
	}
	operator TYPE*()
	{
		return ptr;
	}
	TYPE* GetPointer(void)									{ return ptr; }
	Bool operator!()												{ return ptr == nullptr; }
	TYPE& operator[](Int32 i) const	{ DebugAssert(!ptr || (i >= 0 && i < count)); return (!ptr || i < 0 || i >= count) ? dv : ptr[i]; }
	TYPE& operator[] (Int64 i) const { DebugAssert(!ptr || (i >= 0 && i < count)); return (!ptr || i < 0 || i >= count) ? dv : ptr[i]; }
	TYPE* const* operator &()							 { return &ptr;	}
};

struct MoDataEx
{
	Int32									 count;	//maximum number of particles
	Int32									 pass;	//pass for multi-index calls
	GeDynamicArray<Dpoint> mat;		//matrices
	GeDynamicArray<Ipoint> data;	//other data
};

// Structure for passing cloned points around
class MoData
{
private:
	MoData(void);
	~MoData(void);

	MoData& operator=(const MoData& d);
	MoData* operator=(MoData* d);

public:
	//General functions
	UInt32 GetDirty(DIRTYFLAGS mask = DIRTYFLAGS_0);
	void SetDirty(DIRTYFLAGS mask = DIRTYFLAGS_0);

	Bool SetWithEx(const MoDataEx& md);

	void Clear(Bool reset);

	Bool Read(HyperFile* hf);
	Bool Write(HyperFile* hf);

	Int GetMemorySize(void);

	//Get and set the length of the arrays
	Bool SetCount(Int cnt);
	Int GetCount(void);

	//Helper functions, get's the number of arrays
	Int32 GetArrayCount(void);

	DescID GetArrayDescID(Int32 index) const;
	Int32 GetArrayID(Int32 index) const;
	Int32 GetArrayIndexType(Int32 index);
	Int32 GetArrayType(Int32 id);
	Int GetArrayIndex(const DescID& id);
	Int GetArrayIndex(Int32 id);

	//Basic single unit data
	BaseContainer* GetDataInstance(const DescID& id);
	BaseContainer* GetDataInstance(Int32 id = NOTOK);
	BaseContainer* GetDataIndexInstance(Int32 index);
	BaseContainer GetData(Int32 id = NOTOK);
	void SetData(const BaseContainer& bc, Int32 id = NOTOK);

	//Must be used before using any of the array functions
	AutoLock& GetAutoLock(void);

	//Array add/remove functions
	Int32 AddArray(const DescID& id, String name = "", Int32 default_flags = 0);
	Int32 AddArray(Int32 id, Int32 type, String name = "", Int32 default_flags = 0);

	Bool RemoveArray(const DescID& id);
	Bool RemoveArray(Int32 id);

	//Handle array flags
	Int32 GetFlags(const DescID& id);
	Int32 GetFlags(Int32 id);
	Int32 GetIndexFlags(Int32 index);

	void SetFlags(const DescID& id, Int32 flags);
	void SetFlags(Int32 id, Int32 flags);
	void SetIndexFlags(Int32 index, Int32 flags);

	void SetFlag(const DescID& id, Int32 flag);
	void SetFlag(Int32 id, Int32 flag);
	void SetIndexFlag(Int32 index, Int32 flag);

	void DelFlag(const DescID& id, Int32 flag);
	void DelFlag(Int32 id, Int32 flag);
	void DelIndexFlag(Int32 index, Int32 flag);

	void SetName(const DescID& id, const String& name);
	void SetName(Int32 id, const String& name);
	void SetIndexName(Int32 index, const String& name);

	String GetName(const DescID& id);
	String GetName(Int32 id);
	String GetIndexName(Int32 index);

	//Get arrays using DescIDs
	void* GetArray(const DescID& id) const;
	MDArray<Char> GetCharArray(const DescID& id, Char default_value = 0) const;
	MDArray<UChar> GetUCharArray(const DescID& id, UChar default_value = 0) const;
	MDArray<Int32> GetLongArray(const DescID& id, Int32 default_value = 0) const;
	MDArray<UInt32> GetULongArray(const DescID& id, UInt32 default_value = 0) const;
	MDArray<Bool> GetBoolArray(const DescID& id, Bool default_value = true) const;
	MDArray<Int64> GetLLongArray(const DescID& id, Int64 default_value = 0) const;
	MDArray<Float> GetRealArray(const DescID& id, Float default_value = 1.0) const;
	MDArray<Matrix> GetMatrixArray(const DescID& id, Matrix default_value = Matrix()) const;
	MDArray<Vector> GetVectorArray(const DescID& id, Vector default_value = Vector()) const;

	//Get arrays using Int32 ids
	void* GetArray(Int32 id, MD_TYPE type = MD_NONE) const;
	MDArray<Char> GetCharArray(Int32 id, Char default_value = 0) const;
	MDArray<UChar> GetUCharArray(Int32 id, UChar default_value = 0) const;
	MDArray<Int32> GetLongArray(Int32 id, Int32 default_value = 0) const;
	MDArray<UInt32> GetULongArray(Int32 id, UInt32 default_value = 0) const;
	MDArray<Bool> GetBoolArray(Int32 id, Bool default_value = true) const;
	MDArray<Int64> GetLLongArray(Int32 id, Int64 default_value = 0) const;
	MDArray<Float> GetRealArray(Int32 id, Float default_value = 1.0) const;
	MDArray<Matrix> GetMatrixArray(Int32 id, Matrix default_value = Matrix()) const;
	MDArray<Vector> GetVectorArray(Int32 id, Vector default_value = Vector()) const;

	//Get arrays using Int32 indexes
	void* GetIndexArray(Int32 index) const;
	MDArray<Char> GetCharIndexArray(Int32 index) const;
	MDArray<UChar> GetUCharIndexArray(Int32 index) const;
	MDArray<Int32> GetLongIndexArray(Int32 index) const;
	MDArray<UInt32> GetULongIndexArray(Int32 index) const;
	MDArray<Bool> GetBoolIndexArray(Int32 index) const;
	MDArray<Int64> GetLLongIndexArray(Int32 index) const;
	MDArray<Float> GetRealIndexArray(Int32 index) const;
	MDArray<Matrix> GetMatrixIndexArray(Int32 index) const;
	MDArray<Vector> GetVectorIndexArray(Int32 index) const;

	Bool CopyTo(MoData* dest, Bool merge_data = false, Int max_count = NOTOK);
	Bool MergeData(MoData* source, Float percent);

	void Flush(void);
	void SetOffset(Int offset = 0);
	void SetLimit(Int limit = NOTOK);

	//--------------------------------
	//For AutoAlloc
	static MoData* Alloc(void);
	static void Free(MoData*& d);
};

// Structure for passing modata around
struct GetMoDataMessage
{
	GetMoDataMessage(void) { index = 0; modata = nullptr; user_owned = false; }
	~GetMoDataMessage(void)
	{
		if (user_owned && modata)
			MoData::Free(modata);
	}
	MoData* modata;				//The returned MoData
	Int32		index;				//The index of the MoData, in a Text Object there can be 4 MoDatas, Paragraph, Line, Word, Letter
	Bool		user_owned;		//The Modata is either owned by C4D or by the User, if it is User owned then the user must free the modata

	MoData* Release(void)	//Release the modata to the user, they must then free the result
	{
		if (!user_owned)
		{
			MoData* md = MoData::Alloc();
			if (!md)
				return nullptr;
			if (!modata->CopyTo(md))
			{
				MoData::Free(md);
				return nullptr;
			}
			modata = md;
		}
		user_owned = false;
		return modata;
	}
};

// Structure for passing mograph selectino data around
struct GetMGSelectionMessage
{
	BaseSelect* sel;
};

//-------------------
// structure to pass with execute effector message
struct Effector_PassData
{
	Effector_PassData (void)
	{
		op = nullptr;
		md = nullptr;
		weight = 1.0;
		thread = nullptr;
	}
	BaseObject* op;
	MoData*			md;
	Float				weight;
	BaseThread* thread;
};

// structure to get pass with sample effector value
struct Effector_PassValueData
{
	Effector_PassValueData (void)
	{
		value = 0.0;
		pos = Vector(0.0);
	}
	Float	 value;
	Vector pos;
};

struct EffectorStrengths
{
	Vector pos, scale, rot, col, other, other2, other3;
};

struct EffectorDataStruct
{
	EffectorDataStruct(void)
	{
		falloff_time = 0.0;
		strength = 1.0;
		maxstrength = 1.0;
		minstrength = 0.0;
		trans_mode	= col_mode = blend_mode = 0;
		ClearMemType(strengths, BLEND_COUNT);
	}
	~EffectorDataStruct(void)
	{
	}
	Float	 falloff_time;
	Vector pos, scale, rot, col;		//position, scale, rotation, color
	Float	 strength;								//effector strength
	Float	 maxstrength;							//effector minimum strength
	Float	 minstrength;							//effector minimum strength
	Int32	 trans_mode;							//transform mode
	Int32	 col_mode;								//color mode
	Int32	 blend_mode;							//blending mode
	Float	 strengths[BLEND_COUNT];	//amount of strengths for each value, of in order, position, scale, rotation, color (anything else we want to affect)
};

struct EffectorDataParameters;

class EffectorData : public ObjectData
{
public:
	EffectorDataParameters* edata;

	//-----------------------------------------------------
	//Inherited from ObjectData
	virtual Bool Init(GeListNode* node);
	virtual void Free(GeListNode* node);
	virtual Bool GetDDescription(GeListNode* node, Description* description, DESCFLAGS_DESC& flags);
	virtual DRAWRESULT Draw(BaseObject* op, DRAWPASS drawpass, BaseDraw* bd, BaseDrawHelp* bh);
	virtual void GetDimension(BaseObject* op, Vector* mp, Vector* rad);
	virtual Bool AddToExecution(BaseObject* op, PriorityList* list);
	virtual EXECUTIONRESULT	Execute(BaseObject* op, BaseDocument* doc, BaseThread* bt, Int32 priority, EXECUTIONFLAGS flags);
	virtual Bool ModifyObject(BaseObject* mod, BaseDocument* doc, BaseObject* op, const Matrix& op_mg, const Matrix& mod_mg, Float lod, Int32 flags, BaseThread* thread);
	virtual Bool Message(GeListNode* node, Int32 type, void* t_data);
	virtual Int32	GetHandleCount(BaseObject* op);
	virtual void GetHandle(BaseObject* op, Int32 i,	HandleInfo& info);
	virtual void SetHandle(BaseObject* op, Int32 i, Vector p, const HandleInfo& info);
	virtual Bool CopyTo(NodeData* dest, GeListNode* snode, GeListNode* dnode, COPYFLAGS flags, AliasTrans* trn);
	virtual Bool IsInstanceOf(const GeListNode* node, Int32 type) const;

	//Internal versions of inherited routines
	virtual Bool InitEffector(GeListNode* node);
	virtual void FreeEffector(GeListNode* node);

	//-----------------------------------------------------
	//Effector Routines
	EffectorDataStruct*						GetEffectorData(void);
	C4D_Falloff*									GetFalloff(void);
	void AddEffectorDependence(BaseObject* op);

	virtual Int32	GetEffectorFlags(void);
	virtual Bool ModifyDDescription(GeListNode* node, Description* description, AtomArray* ar);

	virtual Bool ExecuteEffector(BaseObject* op, BaseDocument* doc, BaseObject* gen, MoData* md, Float strength, BaseThread* thread);
	virtual void InitPoints(BaseObject* op, BaseObject* gen, BaseDocument* doc, EffectorDataStruct* data, MoData* md, BaseThread* thread);
	virtual void ModifyPoints(BaseObject* op, BaseObject* gen, BaseDocument* doc, EffectorDataStruct* data, MoData* md, BaseThread* thread);
	virtual void FreePoints(void);

	//------------------------------------------------------
	//for random etc, where a value must be calculated even if it's not used
	virtual void CalcPlacebo(BaseObject* op, BaseObject* gen, BaseDocument* doc, EffectorDataStruct* data, Int32 index, MoData* md, const Vector& globalpos, Float fall_weight);

	//modify data->strengths values accordingly in CalcPointValue
	virtual void CalcPointValue(BaseObject* op, BaseObject* gen, BaseDocument* doc, EffectorDataStruct* data, Int32 index, MoData* md, const Vector& globalpos, Float fall_weight);

	//called separately as it may not be needed (and therefore sometimes might reduce number of calculations
	virtual Vector CalcPointColor(BaseObject* op, BaseObject* gen, BaseDocument* doc, EffectorDataStruct* data, Int32 index, MoData* md, const Vector& globalpos, Float fall_weight);
};

Bool RegisterEffectorPlugin(Int32 id, const String& str, Int32 info, DataAllocator* g, const String& description, BaseBitmap* icon, Int32 disklevel);

#endif

