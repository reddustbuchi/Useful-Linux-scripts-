/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_PARTICLESNEW_H
#define __C4D_PARTICLESNEW_H

////////////////////////////////
#define ID_THINKINGPARTICLES			1001428
#define ID_TP_PGROUP							1001381
#define ID_TP_PARTICLEGEOMETRY		1001414

#define ID_TP_VALUE_TYPE_PARTICLE	1001394
#define ID_TP_DATA_TYPE_PARTICLE	1001395
#define ID_TP_VALUE_TYPE_SHAPE		1001396
#define ID_TP_DATA_TYPE_SHAPE			1001397
#define ID_TP_VALUE_TYPE_GROUP		1001398
#define ID_TP_DATA_TYPE_GROUP			1001399
#define ID_TP_VALUE_TYPE_SPIN			1001433
#define ID_TP_DATA_TYPE_SPIN			1001434


#define ID_TP_OPCLASS							1001385
#define ID_TP_OPGROUP_CONDITION		1001386
#define ID_TP_OPGROUP_HELPER			1001387
#define ID_TP_OPGROUP_INITIATOR		1001388
#define ID_TP_OPGROUP_GENERATOR		1001389
#define ID_TP_OPGROUP_STANDARD		1001390
#define ID_TP_OPGROUP_DYNAMIC			1001391


#define ID_TP_OP_STORM						1001382
#define ID_TP_IN_SELFDYNAMIC			1001435
#define ID_TP_HP_PARTICLEDATA			1001403
#define ID_TP_OP_PARTICLEDATA			1001404
#define ID_TP_IN_INTERACT					1001405
#define ID_TP_IF_PARTICLEAGE			1001406
#define ID_TP_HP_SPINCONVERT			1001408
#define ID_TP_HP_PGROUP						1001409
#define ID_TP_HP_VELOCITYCONVERT	1001410
#define ID_TP_OP_DEFLECTOR				1001411
#define ID_TP_OP_POSFOLLOW				1001412
#define ID_TP_OP_OBJECTSHAPE			1001413
#define ID_TP_OP_SPIN							1001415
#define ID_TP_OP_ALIGNMENT				1001416
#define ID_TP_OP_PGROUP						1001417
#define ID_TP_OP_MASS							1001418
#define ID_TP_OP_SIZE							1001419
#define ID_TP_OP_SCALE						1001420
#define ID_TP_OP_FRICTION					1001421
#define ID_TP_OP_VELOCITY					1001422
#define ID_TP_OP_MOTIONINHERI			1001423
#define ID_TP_OP_BUBBLE						1001424
#define ID_TP_OP_DIE							1001425
#define ID_TP_OP_GRAVITY					1001426
#define ID_TP_OP_WIND							1001427
#define ID_TP_HP_TIMER						1001429
#define ID_TP_HP_CHRONOMETER			1001430
#define ID_TP_OP_FRAGMENT					1001431
#define ID_TP_OP_FREEZE						1001432
#define ID_TP_OP_REPULSEBOUNCE		1001436
#define ID_TP_OP_ROLLING					1001437
#define ID_TP_IF_LIGHT						1001438
#define ID_THINKINGCOMMAND				1001439
#define ID_TP_HP_SURFACEPOSITION	1001440
#define ID_TP_HP_VOLUMEPOSITION		1001441
#define ID_TP_OP_BORN							1001442
#define TP_SN_HOOK								1001443
#define ID_TP_OP_BLURP						1001444
#define ID_TP_OP_PARTICLEDRAW			1001445
#define ID_TP_OP_PARTICLEDRAWTOOL	1001446
#define ID_TP_OP_MATTERWAVES			1001447
////////////////////////////////

#include "ge_math.h"
#include "c4d_misc.h"
#ifdef USE_API_MAXON
#include "basearray.h"
#endif
#include "c4d_library.h"
#include "c4d_string.h"
#include "c4d_baselist.h"
#include "c4d_nodedata.h"
#include "c4d_objectdata.h"
#include "c4d_graphview.h"
#include "c4d_baseobject.h"
#include "c4d_basedocument.h"
#include "lib_collider.h"

#define THINKINGPARTICLES_VERSION			1
#define THINKINGPARTICLES_PRIORITY		GRAPHVIEW_HOOK_PRIORITY - 100



class TP_PGroup;
class TP_ParticleNode;
class TP_MasterSystem;


#define TP_PGroupInfo	      	BaseContainer

#define TP_DataChannelInfo		BaseContainer
#define DATACHANNEL_INFO_CHAN	100
#define DATACHANNEL_INFO_NAME	101
#define DATACHANNEL_INFO_TYPE	102



class TP_PGroupArray : public maxon::BaseArray<TP_PGroup*>
{
public:
	TP_PGroupArray() {}

	// In the move constructor you can use std::move() to initialize class members. Extra care must be taken if you want to call
	// the move constructor of your base class. Instead of BaseClass(std::move(src)) you should call C4D_MISC_MOVE_BASE_CLASS(src, BaseClass).
	// For compiler with C++11 rvalue reference this is equivalent to BaseClass(std::move(src)), but for older compilers it makes
	// sure that std::move() is called with a reference to src's base class (otherwise the compiler would try to call the copy constructor).
	TP_PGroupArray(TP_PGroupArray&& src) : maxon::BaseArray<TP_PGroup*>(std::move(src))
	{
	}

	Bool CopyTo(TP_PGroupArray *dest) const
	{
		return dest->CopyFrom(*this,false);
	}

	TP_PGroup* GetIndex(Int32 i) const
	{
		if (i < 0 || i >= GetCount())
			return nullptr; // unfortunately this case was allowed in old GeTempDynArrays and is heavily used

		return maxon::BaseArray<TP_PGroup*>::operator[](i);
	}
};

struct TP_Spin
{
	Vector axis;
	Float   speed;
};

// used with SetPGroupHierarchy()
enum TP_InsertMode
{
	TP_INSERT_NONE = 0,
	TP_INSERT_UNDERFIRST,
	TP_INSERT_UNDERLAST,
	TP_INSERT_BEFORE,
	TP_INSERT_AFTER
};
////////////////////////////////
// used with GetParticleGroups()
enum TP_GetPGroupMode
{
	TP_GETPGROUP_ALL = 0,
	TP_GETPGROUP_WITHPARTICLES,
	TP_GETPGROUP_SELECTED
};
////////////////////////////////



#define TP_Collision	Int32


class TP_BaseCollision {};

struct TP_CollisionInterface
{
	TP_BaseCollision *base;

	Bool (TP_BaseCollision::*CheckCollision)(TP_Collision collision, TP_MasterSystem *msys, Int32 pid, Float t, Vector &pos, Vector &vel, TP_Spin &spin, Float dt, Float &ct);
};

#include <string.h>

struct TP_PShapeI
{
	Int32	owner_id;
	Int32  refcnt;

	TP_PShapeI(void) : owner_id(NOTOK),refcnt(0) { }

	virtual ~TP_PShapeI()
	{
	}
};

class TP_PShapePtr
{
		TP_PShapeI *ptr;
	public:
		TP_PShapePtr() { ptr=nullptr; }
		TP_PShapePtr(const TP_PShapePtr &p)
		{
			ptr = p.ptr;
			if (ptr)
			{
				ptr->refcnt++;
			}
		}
		TP_PShapePtr(TP_PShapeI *p)
		{
			ptr = p;
			if (ptr)
			{
				ptr->refcnt++;
			}
		}
		Bool operator == (const TP_PShapePtr &p)
		{
			return ptr==p.ptr;
		}
		Bool operator != (const TP_PShapePtr &p)
		{
			return ptr!=p.ptr;
		}
		const TP_PShapePtr& operator = (const TP_PShapePtr &p)
		{
			if (ptr)
			{
				ptr->refcnt--;
				if (ptr->refcnt==0)
				{
					DeleteObj(ptr);
				}
			}
			ptr = p.ptr;
			if (ptr)
			{
				ptr->refcnt++;
			}
			return *this;
		}
		const TP_PShapePtr& operator = (TP_PShapeI *p)
		{
			*this = TP_PShapePtr(p);
			return *this;
		}
		Bool Content() const
		{
			return ptr!=nullptr;
		}
		TP_PShapeI *Get() const
		{
			return ptr;
		}
		~TP_PShapePtr()
		{
			if (ptr)
			{
				ptr->refcnt--;
				if (ptr->refcnt==0)
				{
					DeleteObj(ptr);
				}
			}
		}
};


class TP_BaseShape {};

struct TP_PShapeInterface
{
	TP_BaseShape *base;

	TP_PShapePtr  (TP_BaseShape::*GetShapeClone)       (const TP_PShapePtr &shape , TP_MasterSystem *msys, Int32 pid, COPYFLAGS flags, AliasTrans *trn);
	TP_PShapePtr  (TP_BaseShape::*GetShape)            (const TP_PShapePtr &shape , TP_MasterSystem *msys, Int32 pid, Int32 owner_id);
	BaseObject* (TP_BaseShape::*GetShapeVirtualObjects)(const TP_PShapePtr &shape , TP_MasterSystem *msys, Int32 pid, BaseDocument *doc, HierarchyHelp *hh);
	Float        (TP_BaseShape::*GetShapeScale)         (const TP_PShapePtr &shape , TP_MasterSystem *msys, Int32 pid);
	void        (TP_BaseShape::*FreeShape)             (TP_PShapePtr &shape , TP_MasterSystem *msys, Int32 pid);
};



//CallBacks
struct TP_FreeParticle_CB
{
	void (*FreeParticle)(TP_FreeParticle_CB *cb, Int32 pid);
};

struct TP_FreePShape_CB
{
	void (*FreePShape)(TP_FreePShape_CB *cb, Int32 pid, const TP_PShapePtr &shape);
};
//

enum
{
	TP_MSG_PGROUP_PREREMOVE = 1000000,	//data *TP_PGroup
	TP_MSG_PGROUP_TREECHANGED,					//data nullptr
	TP_MSG_DCHANNEL_PREREMOVE,					//data chan
	TP_MSG_DCHANNEL_CHANGED,						//data nullptr
	TP_MSG_OBJECT_GETPARTICLES_EX,			//
	TP_MSG_GET_PSHAPEINTERFACE,					//data **TP_PShapeInterface
	TP_MSG_GET_COLLISIONINTERFACE,			//data **TP_CollisionInterface
	TP_MSG_OBJECT_GETPARTICLES					//data *TP_PGroupArray
};

struct TP_Msg
{
	Int32             msg;
	TP_MasterSystem *msys;
	void            *data;
};

struct TP_PGroupPreRemove
{
	TP_PGroup *pgroup;
	Bool       used;
};



struct C4D_TP_MASTERSYSTEM
{
	Int32 (TP_MasterSystem::*AllocParticle   )(void);
	Int32 (TP_MasterSystem::*AllocParticles  )(Int32 num, Int32 *ids);
	void (TP_MasterSystem::*FreeParticle    )(Int32 pid);
	void (TP_MasterSystem::*FreeAllParticles)(void);

	TP_PGroup    *(TP_MasterSystem::*AllocParticleGroup)		(void);
	void				  (TP_MasterSystem::*FreeParticleGroup)			(TP_PGroup *&group);
	Bool				  (TP_MasterSystem::*SetPGroupHierarchy)	  (TP_PGroup *parent , TP_PGroup *group, TP_InsertMode mode);
	Int32				  (TP_MasterSystem::*GetParticleGroupsEx)	  (TP_PGroup *ingroup, TP_PGroupArray *gtab, TP_GetPGroupMode mode, Bool subgroups);
	Int32				  (TP_MasterSystem::*GetGroupParticleCount)	(TP_PGroup *ingroup, Bool subgroups);
	BaseObject   *(TP_MasterSystem::*GetVirtualObjects)     (TP_PGroup *ingroup, Bool inRender, Bool subgroups, HierarchyHelp *hh);
	TP_PGroupInfo*(TP_MasterSystem::*GetGroupInfo)    (TP_PGroup     *group);
	TP_PGroup*    (TP_MasterSystem::*GetGroupFromInfo)(TP_PGroupInfo *info );

	Int32       (TP_MasterSystem::*NumParticles)(void);
	Bool       (TP_MasterSystem::*Alive)       (Int32 pid);
	Bool       (TP_MasterSystem::*IsBorn)      (Int32 pid);
	Bool       (TP_MasterSystem::*IsDie)       (Int32 pid);
	Bool       (TP_MasterSystem::*EntersGroup) (Int32 pid);
	TP_PGroup* (TP_MasterSystem::*Group)       (Int32 pid);
	Vector     (TP_MasterSystem::*Position)    (Int32 pid);
	Vector     (TP_MasterSystem::*Velocity)    (Int32 pid);
	Float       (TP_MasterSystem::*Mass)        (Int32 pid);
	TP_Spin    (TP_MasterSystem::*Spin)        (Int32 pid);
	Float       (TP_MasterSystem::*Size)        (Int32 pid);
	Vector     (TP_MasterSystem::*Scale)       (Int32 pid);
	BaseTime   (TP_MasterSystem::*Age)         (Int32 pid);
	BaseTime   (TP_MasterSystem::*Life)        (Int32 pid);
	Matrix     (TP_MasterSystem::*Alignment)   (Int32 pid);
	Int32       (TP_MasterSystem::*Randomseed)  (Int32 pid);
	TP_PShapePtr (TP_MasterSystem::*Shape)       (Int32 pid);
	Matrix     (TP_MasterSystem::*Transform)   (Int32 pid);
	UInt16      (TP_MasterSystem::*Flags)       (Int32 pid);
	Float       (TP_MasterSystem::*DTFactor)    (Int32 pid);

	void (TP_MasterSystem::*SetPosition)	(Int32 pid, const Vector &p);
	void (TP_MasterSystem::*SetVelocity)	(Int32 pid, const Vector &p);
	void (TP_MasterSystem::*SetMass)			(Int32 pid, Float mass);
	void (TP_MasterSystem::*SetSpin)			(Int32 pid, TP_Spin &spin);
	void (TP_MasterSystem::*SetAge)				(Int32 pid, const BaseTime &age);
	void (TP_MasterSystem::*SetLife)			(Int32 pid, const BaseTime &life);
	void (TP_MasterSystem::*SetGroup)			(Int32 pid, TP_PGroup *group);
	void (TP_MasterSystem::*SetSize)			(Int32 pid, Float size );
	void (TP_MasterSystem::*SetScale)			(Int32 pid, const Vector &scale);
	void (TP_MasterSystem::*SetAlignment)	(Int32 pid, const Matrix &align);
	void (TP_MasterSystem::*SetRandomseed)(Int32 pid, Int32 seed );
	void (TP_MasterSystem::*SetShape)			(Int32 pid, const TP_PShapePtr &shape, Bool deleteold);
	void (TP_MasterSystem::*SetCollision)	(Int32 pid, TP_Collision collision);
	void (TP_MasterSystem::*SetDTFactor)	(Int32 pid, Float dt    );


	//Particle Data Channels
	Bool			(TP_MasterSystem::*AddDataChannel)			(GvDataID type, const String& str);
	Bool			(TP_MasterSystem::*RemoveDataChannel)		(Int32 chan);
	Int32			(TP_MasterSystem::*NumDataChannels)			(void);
	GvDataID	(TP_MasterSystem::*DataChannelType)			(Int32 chan);
	String		(TP_MasterSystem::*DataChannelName)			(Int32 chan);
	Int32			(TP_MasterSystem::*DataChannelUniqueID)	(Int32 chan);
	Int32			(TP_MasterSystem::*DataChannelID)				(Int32 unique_id);

	Bool (TP_MasterSystem::*SetData)        (Int32 pid, Int32 chan, void *data, GvValueID type);
	Bool (TP_MasterSystem::*GetData)        (Int32 pid, Int32 chan, void *data, GvValueID type);
	Bool (TP_MasterSystem::*SetDataFromPort)(Int32 pid, Int32 chan, GvPort *p, GvRun *r);
	Bool (TP_MasterSystem::*SetDataToPort)  (Int32 pid, Int32 chan, GvPort *p, GvRun *r);

	TP_DataChannelInfo *(TP_MasterSystem::*GetDataChannelInfo)    (Int32 chan);
	Int32                (TP_MasterSystem::*GetDataChannelFromInfo)(TP_DataChannelInfo *info);
	///

	//Call Backs
	void (TP_MasterSystem::*Reg_FreeParticle_CB) (TP_FreeParticle_CB *cb);
	void (TP_MasterSystem::*UReg_FreeParticle_CB)(TP_FreeParticle_CB *cb);
	void (TP_MasterSystem::*Reg_FreePShape_CB)   (TP_FreePShape_CB   *cb);
	void (TP_MasterSystem::*UReg_FreePShape_CB)  (TP_FreePShape_CB   *cb);
	//

	//Operator Link Table
	Int32            (TP_MasterSystem::*GetOperatorID)(GvNode *op);
	GvOperatorData *(TP_MasterSystem::*GetOperator)  (Int32    id);

	UInt32            (TP_MasterSystem::*GetDirty)(void);
	void             (TP_MasterSystem::*SetDirty)(void);

	// Collision
	Bool (TP_MasterSystem::*CheckCollision)(TP_Collision collision, Int32 pid, Float t, Vector &pos, Vector &vel, TP_Spin &spin, Float dt, Float &ct);

	//Particle Shape
	TP_PShapePtr (TP_MasterSystem::*GetShapeClone)        (const TP_PShapePtr &shape , Int32 pid, COPYFLAGS flags, AliasTrans *trn);
	TP_PShapePtr (TP_MasterSystem::*GetShape)             (const TP_PShapePtr &shape , Int32 pid, Int32 owner_id);
	BaseObject* (TP_MasterSystem::*GetShapeVirtualObjects)(const TP_PShapePtr &shape , Int32 pid, BaseDocument *doc, HierarchyHelp *hh);
	Float        (TP_MasterSystem::*GetShapeScale)         (const TP_PShapePtr &shape , Int32 pid);
	void        (TP_MasterSystem::*FreeShape)             (TP_PShapePtr &shape, Int32 pid);

	//ColliderCache
	GeColliderCache *(TP_MasterSystem::*ColliderCache)(Int32 pid);

	Int32				  (TP_MasterSystem::*GetParticleGroups)	  (TP_PGroup *ingroup, TP_PGroupArray *gtab, TP_GetPGroupMode mode, Bool subgroups);
};

struct C4D_TP_PGROUP
{
	Int32             (TP_PGroup::*GetLevel)      (void);
	TP_ParticleNode *(TP_PGroup::*GetFirstNode)  (void);
	TP_ParticleNode *(TP_PGroup::*GetLastNode )  (void);
	Int32             (TP_PGroup::*NumParticles)  (void);
	Bool             (TP_PGroup::*IsSubGroup  )  (TP_PGroup *group);
	Int32             (TP_PGroup::*GetGroupID  )  (void);
	const String     (TP_PGroup::*GetTitle)		   (void);
	void             (TP_PGroup::*SetTitle)      (const String &title);
	void             (TP_PGroup::*SetViewType)   (Int32 type);
	Int32             (TP_PGroup::*GetViewType)   (void);
	void             (TP_PGroup::*SetShowObjects)(Bool show);
	Bool             (TP_PGroup::*GetShowObjects)(void);
	void             (TP_PGroup::*SetColor)      (Vector &col);
	Vector           (TP_PGroup::*GetColor)      (void);
	Bool             (TP_PGroup::*EditSettings)  (void);
	Bool             (TP_PGroup::*IsSelected)    (void);
	Bool             (TP_PGroup::*IsOpened)      (void);
	void             (TP_PGroup::*Select)        (Int32 mode);
	void             (TP_PGroup::*Open)					 (Bool onoff);
};

struct C4D_TP_PARTICLENODE
{
	Int32             (TP_ParticleNode::*GetParticleID)(void);
	TP_ParticleNode *(TP_ParticleNode::*GetNext      )(void);
	TP_ParticleNode *(TP_ParticleNode::*GetPrev      )(void);
};


struct C4DLibrary_TPOS : public C4DLibrary
{
	C4D_TP_MASTERSYSTEM   *MSYS;
	C4D_TP_PGROUP					*GROUP;
	C4D_TP_PARTICLENODE   *PART;
};

extern C4DLibrary_TPOS *TPOS;








#define TpCall(fnc) (this->*TPOS->MSYS->fnc)

class TP_MasterSystem : public BaseSceneHook
{
private:
	TP_MasterSystem();
	~TP_MasterSystem();
public:
	Int32 AllocParticle   (void)               { return TpCall(AllocParticle)(); }
	Int32 AllocParticles  (Int32 num, Int32 *ids){ return TpCall(AllocParticles)(num, ids); }
	void FreeParticle    (Int32 pid)           { TpCall(FreeParticle)(pid); }
	void FreeAllParticles(void)               { TpCall(FreeAllParticles)(); }

	TP_PGroup     *AllocParticleGroup		(void){ return TpCall(AllocParticleGroup)(); }
	void				   FreeParticleGroup			(TP_PGroup *&group){ TpCall(FreeParticleGroup)(group); }
	Bool				   SetPGroupHierarchy		(TP_PGroup *parent , TP_PGroup *group, TP_InsertMode mode){ return TpCall(SetPGroupHierarchy)(parent, group, mode); }
	Int32				   GetParticleGroups	    (TP_PGroup *ingroup, TP_PGroupArray *gtab, TP_GetPGroupMode mode, Bool subgroups = true){ return TpCall(GetParticleGroups)(ingroup, gtab, mode, subgroups); }
	Int32				   GetGroupParticleCount	(TP_PGroup *ingroup, Bool subgroups = true){ return TpCall(GetGroupParticleCount)(ingroup, subgroups); }
	BaseObject    *GetVirtualObjects     (TP_PGroup *ingroup, Bool inRender = true, Bool subgroups = true, HierarchyHelp *hh = nullptr){ return TpCall(GetVirtualObjects)(ingroup, inRender, subgroups, hh); }
	TP_PGroupInfo *GetGroupInfo    (TP_PGroup     *group){ return TpCall(GetGroupInfo)(group);    }
	TP_PGroup     *GetGroupFromInfo(TP_PGroupInfo *info ){ return TpCall(GetGroupFromInfo)(info); }


	Int32       NumParticles(void)    { return TpCall(NumParticles)(); }
	Bool       Alive       (Int32 pid){ return TpCall(Alive)(pid); }
	Bool       IsBorn      (Int32 pid){ return TpCall(IsBorn)(pid); }
	Bool       IsDie       (Int32 pid){ return TpCall(IsDie)(pid); }
	Bool       EntersGroup (Int32 pid){ return TpCall(EntersGroup)(pid); }
	TP_PGroup *Group       (Int32 pid){ return TpCall(Group)(pid); }
	Vector     Position    (Int32 pid){ return TpCall(Position)(pid); }
	Vector     Velocity    (Int32 pid){ return TpCall(Velocity)(pid); }
	Float       Mass        (Int32 pid){ return TpCall(Mass)(pid); }
	TP_Spin    Spin        (Int32 pid){ return TpCall(Spin)(pid); }
	Float       Size        (Int32 pid){ return TpCall(Size)(pid); }
	Vector     Scale       (Int32 pid){ return TpCall(Scale)(pid); }
	BaseTime   Age         (Int32 pid){ return TpCall(Age)(pid); }
	BaseTime   Life        (Int32 pid){ return TpCall(Life)(pid); }
	Matrix     Alignment   (Int32 pid){ return TpCall(Alignment)(pid); }
	Int32       Randomseed  (Int32 pid){ return TpCall(Randomseed)(pid); }
	TP_PShapePtr Shape      (Int32 pid){ return TpCall(Shape)(pid); }
	Matrix     Transform   (Int32 pid){ return TpCall(Transform)(pid); }
	UInt16      Flags       (Int32 pid){ return TpCall(Flags)(pid); }
	Float       DTFactor    (Int32 pid){ return TpCall(DTFactor)(pid); }



	void SetPosition	(Int32 pid, const Vector &p){ TpCall(SetPosition)(pid, p); }
	void SetVelocity	(Int32 pid, const Vector &p){ TpCall(SetVelocity)(pid, p); }
	void SetMass			(Int32 pid, Float mass){ TpCall(SetMass)(pid, mass); }
	void SetSpin			(Int32 pid, TP_Spin &spin){ TpCall(SetSpin)(pid, spin); }
	void SetAge				(Int32 pid, const BaseTime &age){ TpCall(SetAge)(pid, age); }
	void SetLife			(Int32 pid, const BaseTime &life){ TpCall(SetLife)(pid, life); }
	void SetGroup			(Int32 pid, TP_PGroup *group){ TpCall(SetGroup)(pid, group); }
	void SetSize			(Int32 pid, Float size ){ TpCall(SetSize)(pid, size); }
	void SetScale			(Int32 pid, const Vector &scale){ TpCall(SetScale)(pid, scale); }
	void SetAlignment	(Int32 pid, const Matrix &align){ TpCall(SetAlignment)(pid, align); }
	void SetRandomseed(Int32 pid, Int32 seed ){ TpCall(SetRandomseed)(pid, seed); }
	void SetShape			(Int32 pid, const TP_PShapePtr &shape, Bool deleteold = true){ TpCall(SetShape)(pid, shape, deleteold); }
	void SetCollision	(Int32 pid, TP_Collision collision){ TpCall(SetCollision)(pid, collision); }
	void SetDTFactor	(Int32 pid, Float dt    ){ TpCall(SetDTFactor)(pid, dt); }


	//Particle Data Channels
	Bool			AddDataChannel			(GvDataID type, const String& str){ return TpCall(AddDataChannel)(type, str); }
	Bool			RemoveDataChannel		(Int32 chan){ return TpCall(RemoveDataChannel)(chan); }
	Int32			NumDataChannels			(void){ return TpCall(NumDataChannels)(); }
	GvDataID	DataChannelType			(Int32 chan){ return TpCall(DataChannelType)(chan); }
	String 		DataChannelName			(Int32 chan){ return TpCall(DataChannelName)(chan); }
	Int32			DataChannelUniqueID	(Int32 chan){ return TpCall(DataChannelUniqueID)(chan); }
	Int32			DataChannelID				(Int32 unique_id){ return TpCall(DataChannelID)(unique_id); }

	Bool SetData(Int32 pid, Int32 chan, void *data, GvValueID type) { return TpCall(SetData)(pid, chan, data, type); }
	Bool GetData(Int32 pid, Int32 chan, void *data, GvValueID type) { return TpCall(GetData)(pid, chan, data, type); }
	Bool SetDataFromPort(Int32 pid, Int32 chan, GvPort *p, GvRun *r){ return TpCall(SetDataFromPort)(pid, chan, p, r); }
	Bool SetDataToPort  (Int32 pid, Int32 chan, GvPort *p, GvRun *r){ return TpCall(SetDataToPort)(pid, chan, p, r);   }
	TP_DataChannelInfo *GetDataChannelInfo    (Int32 chan)         { return TpCall(GetDataChannelInfo)(chan);   }
	Int32                GetDataChannelFromInfo(TP_DataChannelInfo *info){ return TpCall(GetDataChannelFromInfo)(info);   }
	///


	//Call Backs
	void Reg_FreeParticle_CB (TP_FreeParticle_CB *cb){ TpCall(Reg_FreeParticle_CB)(cb);  }
	void UReg_FreeParticle_CB(TP_FreeParticle_CB *cb){ TpCall(UReg_FreeParticle_CB)(cb); }
	void Reg_DeletePShape_CB (TP_FreePShape_CB   *cb){ TpCall(Reg_FreePShape_CB)(cb);  }
	void UReg_DeletePShape_CB(TP_FreePShape_CB   *cb){ TpCall(UReg_FreePShape_CB)(cb); }
	//

	//Operator Link Table
	Int32            GetOperatorID(GvNode *op){ return TpCall(GetOperatorID)(op); }
	GvOperatorData *GetOperator  (Int32    id){ return TpCall(GetOperator)(id);   }

	UInt32            GetDirty(void){ return TpCall(GetDirty)(); }
	void             SetDirty(void){ TpCall(SetDirty)(); }

	// Collision
	Bool CheckCollision(TP_Collision collision, Int32 pid, Float t, Vector &pos, Vector &vel, TP_Spin &spin, Float dt, Float &ct){ return TpCall(CheckCollision)(collision, pid, t, pos, vel, spin, dt, ct); }

	//Particle Shape
	TP_PShapePtr GetShapeClone        (const TP_PShapePtr &shape , Int32 pid, COPYFLAGS flags, AliasTrans *trn){ return TpCall(GetShapeClone)(shape, pid, flags, trn); }
	TP_PShapePtr GetShape             (const TP_PShapePtr &shape , Int32 pid, Int32 owner_id){ return TpCall(GetShape)(shape, pid, owner_id); }
	BaseObject* GetShapeVirtualObjects(const TP_PShapePtr &shape , Int32 pid, BaseDocument *doc, HierarchyHelp *hh){ return TpCall(GetShapeVirtualObjects)(shape, pid, doc, hh); }
	Float        GetShapeScale         (const TP_PShapePtr &shape , Int32 pid){ return TpCall(GetShapeScale)(shape, pid); }
	void        FreeShape             (TP_PShapePtr &shape, Int32 pid){ TpCall(FreeShape)(shape, pid); }

	// ColliderCache
	GeColliderCache* ColliderCache(Int32 pid){ return TpCall(ColliderCache)(pid); }
};

#define PartCall(fnc) (this->*TPOS->PART->fnc)

class TP_ParticleNode
{
public:
	Int32             GetParticleID(void){ return PartCall(GetParticleID)(); }
	TP_ParticleNode *GetNext      (void){ return PartCall(GetNext)();       }
	TP_ParticleNode *GetPrev      (void){ return PartCall(GetPrev)();       }
};


#define PGroupCall(fnc) (this->*TPOS->GROUP->fnc)

class TP_PGroup : public BaseList2D
{
	private:
		TP_PGroup();
		~TP_PGroup();
	public:
		Int32             GetLevel(void)                  { return PGroupCall(GetLevel)();        }
		TP_ParticleNode *GetFirstNode(void)              { return PGroupCall(GetFirstNode)();    }
		TP_ParticleNode *GetLastNode(void)	             { return PGroupCall(GetLastNode)();     }
		Int32             NumParticles(void)              { return PGroupCall(NumParticles)();    }
		Bool             IsSubGroup(TP_PGroup *group)    { return PGroupCall(IsSubGroup)(group); }
		Int32             GetGroupID(void)                { return PGroupCall(GetGroupID)();      }
		const String     GetTitle(void)                  { return PGroupCall(GetTitle)();        }
		void             SetTitle(const String &title)   { PGroupCall(SetTitle)(title);          }
		void             SetViewType(Int32 type)          { PGroupCall(SetViewType)(type);        }
		Int32             GetViewType(void)               { return PGroupCall(GetViewType)();     }
		void             SetShowObjects(Bool show)       { PGroupCall(SetShowObjects)(show);     }
		Bool             GetShowObjects(void)            { return PGroupCall(GetShowObjects)();  }
		void             SetColor(Vector &col)           { PGroupCall(SetColor)(col);            }
		Vector           GetColor(void)                  { return PGroupCall(GetColor)();        }
		Bool             EditSettings(void)              { return PGroupCall(EditSettings)();    }
		Bool             IsSelected(void)								 { return PGroupCall(IsSelected)();      }
		Bool             IsOpened(void)									 { return PGroupCall(IsOpened)();        }
		void             Select(Int32 mode )							 { PGroupCall(Select)(mode);             }
		void             Open(Bool onoff)								 { PGroupCall(Open)(onoff);              }
};

////////////////////////////////

inline Bool InitThinkingParticles(void)
{
	return nullptr != CheckLib(ID_THINKINGPARTICLES, 0, (C4DLibrary**)&TPOS);
}

////////////////////////////////

#endif //__C4D_PARTICLES_H

////////////////////////////////
