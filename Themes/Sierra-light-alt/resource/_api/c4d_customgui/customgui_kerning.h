/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_KERNING_H_
#define _CUSTOMGUI_KERNING_H_

#include "customgui_base.h"
#include "c4d_customguidata.h"
#include "c4d_basecontainer.h"
#include "c4d_customdatatype.h"
#include "c4d_objectdata.h"
#ifdef USE_API_MAXON
#include "basearray.h"
#else
#include "c4d_misc/datastructures/basearray.h"
#endif

#ifdef __API_INTERN__
#include "hyperfile.h"
#include "baseobject.h"
#else
#include "c4d_baseobject.h"
#include "c4d_file.h"
#endif

// Unique IDs
#define CUSTOMDATATYPE_KERNING							1028639		///< Plugin ID for the KerningData type
#define CUSTOMGUI_KERNING										1028640		///< Plugin ID for the KerningGui
#define TEXTSPLINE_RESULTS									1029376		///< Container ID for the text spline generation results
#define MSG_DESCRIPTION_KERNINGDATACHANGED	1029460		///< Message ID for the message that sends changed KerningData to an object after a handle has been moved
#define MSG_KERNING_GETGUIHELPER						1029466		///< Message ID for the message that fetches the KerningVpGuiHelper pointer of an object

// Kerning result container set IDs
#define TEXTSPLINE_RESULT_X						'trsx'		///< Float; returns the x coordinate of a char's left border (including kerning, tracking, et cetera)
#define TEXTSPLINE_RESULT_Y						'trsy'		///< Float; returns the y coordinate of a char's bottom border (including baseline shift)
#define TEXTSPLINE_RESULT_Y_BASE			'trby'		///< Float; returns the y coordinate of a char's line's bottom border (no baseline shift)
#define TEXTSPLINE_RESULT_HEIGHT_BASE	'trbh'		///< Float; returns the basic height of a char's line (no scale, no baseline shift)
#define TEXTSPLINE_RESULT_WIDTH				'trsw'		///< Float; returns the actual width of a char
#define TEXTSPLINE_RESULT_HEIGHT			'trsh'		///< Float; returns the actual height of a char (including scale)


//----------------------------------------------------------------------------------------
/// This struct holds the Kerning parameters for one character in a string.
//----------------------------------------------------------------------------------------
struct Kerning
{
	Float _kerning;					///< moves the character along its X axis, to create (or remove) space before the character
	Float _tracking;				///< like Kerning, but for a group of characters
	Float _scale;						///< scales the character
	Float _scaleH;					///< scales the character along its X axis
	Float _scaleV;					///< scales the character along its Y axis
	Float _baselineShift;		///< moves the character along its Y axis
	Float _leading;					///< (Not used currently)

	//----------------------------------------------------------------------------------------
	/// Default constructor
	//----------------------------------------------------------------------------------------
	Kerning() :
		_kerning(0.0),
		_tracking(0.0),
		_scale(1.0),
		_scaleH(1.0),
		_scaleV(1.0),
		_baselineShift(0.0),
		_leading(0.0)
	{	}

	//----------------------------------------------------------------------------------------
	/// Copy constructor
	/// @param[in] source				The Kerning object to copy members from
	//----------------------------------------------------------------------------------------
	Kerning(const Kerning& source) :
		_kerning(source._kerning),
		_tracking(source._tracking),
		_scale(source._scale),
		_scaleH(source._scaleH),
		_scaleV(source._scaleV),
		_baselineShift(source._baselineShift),
		_leading(source._leading)
	{	}

	//----------------------------------------------------------------------------------------
	/// Constructor with parameters
	//----------------------------------------------------------------------------------------
	Kerning(Float kerning, Float tracking, Float scale, Float scaleH, Float scaleV, Float baselineShift, Float leading) :
		_kerning(kerning),
		_tracking(tracking),
		_scale(scale),
		_scaleH(scaleH),
		_scaleV(scaleV),
		_baselineShift(baselineShift),
		_leading(leading)
	{	}

	//----------------------------------------------------------------------------------------
	/// Checks for equality
	/// @return							true, if equal
	//----------------------------------------------------------------------------------------
	friend Bool operator == (const Kerning &k1, const Kerning &k2)
	{
		return	((k1._kerning == k2._kerning) &&
						(k1._tracking == k2._tracking) &&
						(k1._scale == k2._scale) &&
						(k1._scaleH == k2._scaleH) &&
						(k1._scaleV == k2._scaleV) &&
						(k1._baselineShift == k2._baselineShift) && 
						(k1._leading == k2._leading));
	}

	//----------------------------------------------------------------------------------------
	/// Checks for inequality
	/// @return							true, if not equal
	//----------------------------------------------------------------------------------------
	friend Bool operator != (const Kerning &k1, const Kerning &k2)
	{
		return	((k1._kerning != k2._kerning) ||
						(k1._tracking != k2._tracking) ||
						(k1._scale != k2._scale) ||
						(k1._scaleH != k2._scaleH) ||
						(k1._scaleV != k2._scaleV) ||
						(k1._baselineShift != k2._baselineShift) || 
						(k1._leading != k2._leading));
	}

	//----------------------------------------------------------------------------------------
	/// Combines two Kerning objects
	/// Offsets are added, scales are taken from second Kerning object
	/// @param[in] k1				The first Kerning object
	/// @param[in] k2				The second Kerning object
	/// @return							The resulting Kerning object
	//----------------------------------------------------------------------------------------
	friend Kerning Combine(const Kerning &k1, const Kerning &k2)
	{
		return Kerning(	k1._kerning + k2._kerning,
										k1._tracking + k2._tracking,
										k2._scale,
										k2._scaleH,
										k2._scaleV,
										k1._baselineShift + k2._baselineShift,
										k1._leading + k2._leading);
	}

	//----------------------------------------------------------------------------------------
	/// Reads the Kerning object from a HyperFile
	/// @param[in] hf				The HyperFile to read from
	/// @param[in] level		The file level
	/// @return							true, if reading was successful
	//----------------------------------------------------------------------------------------
	Bool	ReadHF(HyperFile* hf, Int32 level);

	//----------------------------------------------------------------------------------------
	/// Writes the Kerning object to a HyperFile
	/// @param[in] hf			The HyperFile to write to
	/// @return						true if writing was successful
	//----------------------------------------------------------------------------------------
	Bool	WriteHF(HyperFile* hf) const;

	//----------------------------------------------------------------------------------------
	/// Computes a vector that combines kerning, tracking, baseline shift and leading
	/// @return						The offset vector
	//----------------------------------------------------------------------------------------
	Vector	GetOffsetVector() const;

	//----------------------------------------------------------------------------------------
	/// Computes a vector that combines scale, horizontal scale and vertical scale
	/// @return						The scale vector
	//----------------------------------------------------------------------------------------
	Vector	GetScaleVector() const;

	//----------------------------------------------------------------------------------------
	/// Converts the Kerning value to a readable string
	/// @return						The string
	//----------------------------------------------------------------------------------------
	String ToString() const;
};


//----------------------------------------------------------------------------------------
///	TriState helper for class Kerning
//----------------------------------------------------------------------------------------
struct KerningTriState
{
	TriState<Float>		_kerning;					///< TriState for Kerning
	TriState<Float>		_tracking;				///< TriState for Tracking
	TriState<Float>		_scale;						///< TriState for Scale
	TriState<Float>		_scaleH;					///< TriState for Horizontal Scale
	TriState<Float>		_scaleV;					///< TriState for Vertical Scale
	TriState<Float>		_baselineShift;		///< TriState for Baseline Shift
	TriState<Float>		_leading;					///< TriState for Leading

	//----------------------------------------------------------------------------------------
	/// Default constructor
	//----------------------------------------------------------------------------------------
	KerningTriState()
	{	}

	//----------------------------------------------------------------------------------------
	/// Copy constructor
	/// @param[in] k				The KerningTriState object to copy members from
	//----------------------------------------------------------------------------------------
	KerningTriState(const Kerning& k) : 
		_kerning(TriState<Float>(k._kerning)),
		_tracking(TriState<Float>(k._tracking)),
		_scale(TriState<Float>(k._scale)),
		_scaleH(TriState<Float>(k._scaleH)),
		_scaleV(TriState<Float>(k._scaleV)),
		_baselineShift(TriState<Float>(k._baselineShift)),
		_leading(TriState<Float>(k._leading))
	{	}

	//----------------------------------------------------------------------------------------
	/// Adds a Kerning object to the TriState
	/// @param[in] k				The Kerning object to add
	//----------------------------------------------------------------------------------------
	void Add(const Kerning& k)
	{
		_kerning.Add(k._kerning);
		_tracking.Add(k._tracking);
		_scale.Add(k._scale);
		_scaleH.Add(k._scaleH);
		_scaleV.Add(k._scaleV);
		_baselineShift.Add(k._baselineShift);
		_leading.Add(k._leading);
	}

	//----------------------------------------------------------------------------------------
	/// Returns the TriState's value
	/// @return							The TriState's value
	//----------------------------------------------------------------------------------------
	Kerning GetValue() const
	{
		return Kerning(	_kerning.GetValue(),
			_tracking.GetValue(),
			_scale.GetValue(),
			_scaleH.GetValue(),
			_scaleV.GetValue(),
			_baselineShift.GetValue(),
			_leading.GetValue());
	}

	//----------------------------------------------------------------------------------------
	/// Returns the TriState
	/// @return							true, if the TriState is ambiguous
	//----------------------------------------------------------------------------------------
	Bool GetTri() const
	{
		return	_kerning.GetTri() ||
						_tracking.GetTri() ||
						_scale.GetTri() ||
						_scaleH.GetTri() ||
						_scaleV.GetTri() ||
						_baselineShift.GetTri() ||
						_leading.GetTri();
	}
};


//----------------------------------------------------------------------------------------
/// This is the CustomDataType that contains a complete array of struct Kerning.
//----------------------------------------------------------------------------------------
class KerningData : public CustomDataType
{
public:
	static KerningData* Alloc();
	static void Free(KerningData *&pData);

	//----------------------------------------------------------------------------------------
	/// Returns the Kerning object with the settings for 'index'
	/// @param[in] index				Index of the desired Kerning object
	/// @return									The Kerning object for index
	//----------------------------------------------------------------------------------------
	Kerning	GetKerning(Int32 index) const;

	//----------------------------------------------------------------------------------------
	/// Calculates the actual Kerning for 'index'
	/// All offsets & scale of the previous array elements will be taken into account
	/// @param[in] index					Index of the desired Kerning object
	/// @param[in] s							Pass a string here to consider line breaks
	/// @return										The Kerning object for index
	//----------------------------------------------------------------------------------------
	Kerning	CalculateKerning(Int32 index, const String& s) const;

	//----------------------------------------------------------------------------------------
	/// Sets Kerning dataset for 'index'
	/// @param[in] index					Index
	/// @param[in] kerning				Kerning dataset
	/// @param[in] combine				If false, existing Kerning dataset will be overwritten with new one. If true, both will be combined.
	/// @return										true if successful
	//----------------------------------------------------------------------------------------
	Bool		SetKerning(Int32 index, const Kerning& kerning, Bool combine = false);

	//----------------------------------------------------------------------------------------
	/// Sets Kerning values for a range of indices
	/// @param[in] index_start		Range start index
	/// @param[in] index_end			Range end index
	/// @param[in] kerning				Kerning dataset
	/// @param[in] combine				If false, existing Kerning datasets will be overwritten with new one. If true, they will be combined.
	/// @return										true if successful
	//----------------------------------------------------------------------------------------
	Bool		SetKerning(Int32 index_start, Int32 index_end, const Kerning& kerning, Bool combine = false);

	//----------------------------------------------------------------------------------------
	/// Sets KerningTriState values for a range of indices
	/// @param[in] index_start		Range start index
	/// @param[in] index_end			Range end index
	/// @param[in] tristate				Kerning dataset
	/// @return										true if successful
	//----------------------------------------------------------------------------------------
	Bool		SetKerning(Int32 index_start, Int32 index_end, const KerningTriState& tristate);

	//----------------------------------------------------------------------------------------
	/// Resets Kerning dataset for index to default values
	/// @param[in] index					The index of the Kerning dataset to reset
	//----------------------------------------------------------------------------------------
	void		ResetKerning(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Resets all Kerning datasets to default values (count will be preserved)
	//----------------------------------------------------------------------------------------
	void		ResetKerning();

	//----------------------------------------------------------------------------------------
	/// Initializes Kerning dataset array with length of 's'
	/// @param[in] s						The length of the Kerning data array will be set to length of s
	/// @param[in] preserve			Keep keep existing Kerning data (false for default values in all elements)
	/// @return									true if successful
	//----------------------------------------------------------------------------------------
	Bool		Init(const String& s, Bool preserve);

	//----------------------------------------------------------------------------------------
	/// Initializes Kerning dataset array with length count
	/// @param[in] count				The length of the Kerning data array
	/// @param[in] preserve			Keep keep existing Kerning data (false for default values in all elements)
	/// @return									true if successful
	//----------------------------------------------------------------------------------------
	Bool		Init(Int32 count, Bool preserve = false);

	//----------------------------------------------------------------------------------------
	/// Returns length of Kerning dataset array
	/// @return									The Kerning dataset array's length
	//----------------------------------------------------------------------------------------
	Int32		GetCount() const;

	//----------------------------------------------------------------------------------------
	/// Clears all Kerning data (count is reset to 0, too)
	//----------------------------------------------------------------------------------------
	void		Clear();

	//----------------------------------------------------------------------------------------
	/// Copies this KerningData object to another one
	/// @param[in] pDest				Pointer to the destination KerningData object
	/// @return									true if successful
	//----------------------------------------------------------------------------------------
	Bool		CopyTo(KerningData* pDest) const;

	//----------------------------------------------------------------------------------------
	/// Returns the string that the KerningData has been initialized with.
	/// @return									The string
	//----------------------------------------------------------------------------------------
	String	GetString() const;

	//----------------------------------------------------------------------------------------
	/// Sets the index of the selection start
	/// @param[in] start				The index of the selection start. 0 <= start < GetString().GetLength()
	//----------------------------------------------------------------------------------------
	void		SetSelectionStart(Int32 start);

	//----------------------------------------------------------------------------------------
	/// Returns the index of the selection start
	/// @return									The index of the selection start
	//----------------------------------------------------------------------------------------
	Int32		GetSelectionStart() const;

	//----------------------------------------------------------------------------------------
	/// Sets the index of the selection end
	/// @param[in] end					The index of the selection start. 0 < end <= GetString().GetLength()
	//----------------------------------------------------------------------------------------
	void		SetSelectionEnd(Int32 end);

	//----------------------------------------------------------------------------------------
	/// Returns the index of the selection end
	/// @return									The index of the selection end
	//----------------------------------------------------------------------------------------
	Int32		GetSelectionEnd() const;

	//----------------------------------------------------------------------------------------
	/// Sets the indexes of the selection start and end
	/// @param[in] start				The index of the selection start
	/// @param[in] end					The index of the selection end
	//----------------------------------------------------------------------------------------
	void		SetSelection(Int32 start, Int32 end);

	//----------------------------------------------------------------------------------------
	/// Returns the length of the selection (selection_end - selection_start)
	/// @return									The length of the selection
	//----------------------------------------------------------------------------------------
	Int32		GetSelectionLength() const;

	//----------------------------------------------------------------------------------------
	/// Returns the edit mode state
	/// @return									true, if edit mode is enabled
	//----------------------------------------------------------------------------------------
	Bool		GetEditmode() const;

	//----------------------------------------------------------------------------------------
	/// Sets the edit mode state
	/// @param[in] editmode			true, if edit mode is enabled
	//----------------------------------------------------------------------------------------
	void		SetEditmode(Bool editmode);

	KerningData()
	{ }

	~KerningData()
	{ }
};


// Helper typedef for debugging
#ifdef _DEBUG
static maxon::BaseArray<Kerning> g_kerning_debug_hack;
#endif

//----------------------------------------------------------------------------------------
/// The CustomGui to display and edit Kerning data
//----------------------------------------------------------------------------------------
class KerningCustomGui : public BaseCustomGui<CUSTOMGUI_KERNING>
{
	KerningCustomGui();
	~KerningCustomGui();
};


//----------------------------------------------------------------------------------------
/// A helper class that does all the drawing and handle management
//----------------------------------------------------------------------------------------
class KerningVpGuiHelper
{
public:
	//----------------------------------------------------------------------------------------
	/// Allocates a new instance of the KerningVpGuiHelper class
	/// @return								Pointer to the newly allocated KerningVpGuiHelper instance
	//----------------------------------------------------------------------------------------
	static KerningVpGuiHelper* Alloc();

	//----------------------------------------------------------------------------------------
	/// Frees an instance of the KerningVpGuiHelper class
	/// @param[in,out] pData				Pointer to the KerningVpGuiHelper instance
	//----------------------------------------------------------------------------------------
	static void Free(KerningVpGuiHelper*& pData);

	//----------------------------------------------------------------------------------------
	/// Initializes the KerningVpGuiHelper.
	/// Must be called after each successful generation of a text spline, and before calling Draw(), GetHandleCount(), GetHandle(), SetHandle()
	/// @param[in] s					The string that the text spline was generated from
	/// @param[in] generationresults				A pointer to the BaseContainer with generation results (get the container with GetContainer(TEXTSPLINE_RESULTS) from the text spline's container)
	/// @param[in] kd					A pointer to the KerningData that was used for text spline generation
	/// @return								false, if initialization failed
	//----------------------------------------------------------------------------------------
	Bool Init(const String& s, BaseContainer* generationresults, KerningData* kd, Int32 plane);

	//----------------------------------------------------------------------------------------
	/// Draws the complete Kerning Viewport GUI into the current drawpass.
	/// Drawing is automatically skipped if the KerningData's editmode is inactive.
	/// Call this from your NodeData's Draw() function.
	/// Init() must be called before calling this function.
	/// @param[in] op					Pass 'op' from your NodeData's Draw() function.
	/// @param[in] bd					Pass 'bd' from your NodeData's Draw() function.
	/// @param[in] bh					Pass 'bh' from your NodeData's Draw() function.
	/// @return								If you want, return this in your NodeData's Draw() function.
	//----------------------------------------------------------------------------------------
	DRAWRESULT Draw(BaseObject *op, BaseDraw *bd, BaseDrawHelp *bh);

	//----------------------------------------------------------------------------------------
	/// Used for managing the Kerning handles.
	/// Call this from your NodeData's DetectHandle() function.
	/// Init() must be called before calling this function.
	/// @param[in] op					Pass 'op' from your NodeData's DetectHandle() function.
	/// @param[in] bd					Pass 'bd' from your NodeData's DetectHandle() function.
	/// @param[in] x					Pass 'x' from your NodeData's DetectHandle() function.
	/// @param[in] y					Pass 'y' from your NodeData's DetectHandle() function.
	/// @param[in] qualifier	Pass 'qualifier' from your NodeData's DetectHandle() function.
	/// @return								Return this in your NodeData's DetectHandle() function.
	//----------------------------------------------------------------------------------------
	Int32 DetectHandle(BaseObject *op, BaseDraw *bd, Int32 x, Int32 y, QUALIFIER qualifier);

	//----------------------------------------------------------------------------------------
	/// Used for managing the Kerning handles.
	/// Call this from your NodeData's MoveHandle() function.
	/// Init() must be called before calling this function.
	/// @param[in] op					Pass 'op' from your NodeData's MoveHandle() function.
	/// @param[in] undo				Pass 'undo' from your NodeData's MoveHandle() function.
	/// @param[in] mouse_pos	Pass 'mouse_pos' from your NodeData's MoveHandle() function.
	/// @param[in] hit_id			Pass 'hit_id' from your NodeData's MoveHandle() function.
	/// @param[in] qualifier	Pass 'qualifier' from your NodeData's MoveHandle() function.
	/// @param[in] bd					Pass 'bd' from your NodeData's MoveHandle() function.
	/// @return								Return this in your NodeData's MoveHandle() function.
	//----------------------------------------------------------------------------------------
	Bool MoveHandle(BaseObject *op, BaseObject *undo, const Vector &mouse_pos, Int32 hit_id, QUALIFIER qualifier, BaseDraw *bd);

	//----------------------------------------------------------------------------------------
	/// Used for managing the Kerning handles.
	/// Call this from your NodeData's GetHandle() function.
	/// Init() must be called before calling this function.
	/// @param[in] op					Pass 'op' from your NodeData's GetHandle() function.
	/// @param[in] i					Pass 'i' from your NodeData's GetHandle() function.
	/// @param[in] info				Pass 'info' from your NodeData's GetHandle() function.
	//----------------------------------------------------------------------------------------
	void GetHandle(BaseObject *op, Int32 i, HandleInfo &info);

	//----------------------------------------------------------------------------------------
	/// Copies all data of the class to another KerningVpGuiHelper object.
	/// @param[in] dest				A pointer to the destination KerningVpGuiHelper object. Must not be nullptr.
	/// @return								true, if copying was successful.
	//----------------------------------------------------------------------------------------
	Bool CopyTo(KerningVpGuiHelper* dest);

	//----------------------------------------------------------------------------------------
	/// Used internally by HandleKerningMessages() to handle drag-less clicks on handles
	/// @param[in] release		false on MouseDown, true on MouseUp
	/// @param[in] op					The BaseObject from which the HandleKerningMessages() call originated
	/// @return								false, if an error occurred
	//----------------------------------------------------------------------------------------
	Bool ClickHandle(Bool release, BaseObject* op);

	KerningVpGuiHelper();
	~KerningVpGuiHelper();
};


//----------------------------------------------------------------------------------------
/// Message data struct for MSG_KERNING_GETGUIHELPER
/// Used internally by HandleKerningMessages() to retrieve the pointer to the KerningVpGuiHelper object of a NodeData.
/// @see HandleKerningMessages().
//----------------------------------------------------------------------------------------
struct KerningGetGuiHelperMsg
{
	KerningVpGuiHelper* _ptr;		///< The pointer

	KerningGetGuiHelperMsg() : _ptr(nullptr)
	{}

	KerningGetGuiHelperMsg(const KerningGetGuiHelperMsg& src) : _ptr(src._ptr)
	{}
};


//----------------------------------------------------------------------------------------
/// Blends the values of two Kerning objects, using simple linear interpolation
/// @param[in] k1					The first Kerning object
/// @param[in] k2					The second Kerning object
/// @param[in] mix				The blend weight. 0.0 <= mix <= 1.0
/// @return								A Kerning object that contains the blended values
//----------------------------------------------------------------------------------------
Kerning BlendKerning(const Kerning& k1, const Kerning& k2, Float mix);

//----------------------------------------------------------------------------------------
/// Takes care of all the messages that are important for the Kerning Viewport GUI to work.
/// Simply call this function from within your NodeData's Message() function.
/// @param[in] node				Pass 'node' from your NodeData's Message() function.
/// @param[in] msgId			Pass 'msgId' from your NodeData's Message() function.
/// @param[in] descID			Pass 'descID' from your NodeData's Message() function.
/// @param[in] msgData		Pass 'msgData' from your NodeData's Message() function.
/// @param[in] guihelper	Pass pointer to allocated instance of your NodeData's KerningVpGuiHelper class.
/// @return								false, if anything went wrong
//----------------------------------------------------------------------------------------
Bool HandleKerningMessages(GeListNode *node, Int32 msgId, Int32 kerningDescID, Int32 textDescID, void* msgData, KerningVpGuiHelper* guihelper);


// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#ifndef _INTERNAL_KERNING_DEF_
	class iKerningGui : public iBaseCustomGui
	{
		iKerningGui(const BaseContainer &settings,CUSTOMGUIPLUGIN *plugin) : iBaseCustomGui(settings,plugin) { }
	};
	class iKerningData
	{
	};
	class iKerningVpGuiHelper
	{
	};
#else
	class iKerningGui;
	class iKerningData;
	class iKerningVpGuiHelper;
#endif

struct KerningLib : public BaseCustomGuiLib
{
	// KerningData member functions
	Bool					(iKerningGui::*GuiGetEditMode)() const;
	void					(iKerningGui::*GuiGetRange)(UInt32& index_start, UInt32& index_end) const;
	void					(iKerningGui::*GuiSetEditMode)(Bool active);
	void					(iKerningGui::*GuiSetRange)(UInt32 index_start, UInt32 index_end);

	KerningData*	(*KerningData_Alloc)();
	void					(*KerningData_Free)(KerningData *&pData);
	Kerning				(iKerningData::*GetKerning)(Int32 index) const;
	Kerning				(iKerningData::*CalculateKerning)(Int32 index, const String& s) const;
	Bool					(iKerningData::*SetKerning1)(Int32 index, const Kerning& kerning, Bool combine);
	Bool					(iKerningData::*SetKerning2)(Int32 index_start, Int32 index_end, const Kerning& kerning, Bool combine);
	Bool					(iKerningData::*SetKerning3)(Int32 index_start, Int32 index_end, const KerningTriState& tristate);
	void					(iKerningData::*ResetKerning1)(Int32 index);
	void					(iKerningData::*ResetKerning2)();
	Bool					(iKerningData::*Init1)(const String& s, Bool preserve);
	Bool					(iKerningData::*Init2)(Int32 count, Bool preserve);
	Int32					(iKerningData::*GetCount)() const;
	void					(iKerningData::*Clear)();
	Bool					(iKerningData::*CopyTo)(iKerningData* pDest) const;
	String				(iKerningData::*GetString)()const;
	void					(iKerningData::*SetSelectionStart)(Int32 start);
	Int32					(iKerningData::*GetSelectionStart)() const;
	void					(iKerningData::*SetSelectionEnd)(Int32 start);
	Int32					(iKerningData::*GetSelectionEnd)() const;
	void					(iKerningData::*SetSelection)(Int32 start, Int32 end);
	Int32					(iKerningData::*GetSelectionLength)() const;
	Bool					(iKerningData::*GetEditmode)() const;
	void					(iKerningData::*SetEditmode)(Bool editmode);

	// VpGuiHelper member functions
	KerningVpGuiHelper*	(*VpGuiHelper_Alloc)();
	void					(*VpGuiHelper_Free)(KerningVpGuiHelper*& pData);
	Bool					(iKerningVpGuiHelper::*VpGuiHelper_Init)(const String& s, BaseContainer* generationresults, KerningData* kd, Int32 plane);
	DRAWRESULT		(iKerningVpGuiHelper::*VpGuiHelper_Draw)(BaseObject *op, BaseDraw *bd, BaseDrawHelp *bh) const;
	Int32					(iKerningVpGuiHelper::*VpGuiHelper_DetectHandle)(BaseObject *op, BaseDraw *bd, Int32 x, Int32 y, QUALIFIER qualifier);
	Bool					(iKerningVpGuiHelper::*VpGuiHelper_MoveHandle)(BaseObject *op, BaseObject *undo, const Vector &mouse_pos, Int32 hit_id, QUALIFIER qualifier, BaseDraw *bd);
	void					(iKerningVpGuiHelper::*VpGuiHelper_GetHandle)(BaseObject *op, Int32 i, HandleInfo &info);
	Bool					(iKerningVpGuiHelper::*VpGuiHelper_CopyTo)(iKerningVpGuiHelper* dest) const;
	Bool					(iKerningVpGuiHelper::*VpGuiHelper_ClickHandle)(Bool release, BaseObject* op);

	// Kerning member functions
	Bool					(*Kerning_ReadHF)(Kerning* k, HyperFile* hf, Int32 level);
	Bool					(*Kerning_WriteHF)(const Kerning* k, HyperFile* hf);

	// Helper functions
	Bool					(*HandleKerningMessages)(GeListNode *node, Int32 msgId, Int32 kerningDescID, Int32 textDescID, void* msgData, KerningVpGuiHelper* guihelper);
	Kerning				(*BlendKerning)(const Kerning& k1, const Kerning& k2, Float mix);
};


// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
