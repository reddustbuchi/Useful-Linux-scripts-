/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

/// @addtogroup Sculpting
/// @{
#ifndef __LIB_SCULPTBRUSH_H__
#define __LIB_SCULPTBRUSH_H__

#include "c4d_library.h"
#include "ge_math.h"
#include "lib_description.h"

#include "c4d_baseobject.h"
#include "c4d_basetag.h"
#include "c4d_tooldata.h"
#include "c4d_descriptiondialog.h"
#include "../../modules/sculpt/res/description/toolsculptbrushbase.h"

class _SculptBrushToolBase;
class iSculptBrushBase;
class SculptBrushToolData;

//----------------------------------------------------------------------------------------
/// When the user first clicks on a SculptObject this determines what the returned hitpoint will be.
//----------------------------------------------------------------------------------------
enum FIRSTHITPPOINTTYPE
{
	FIRSTHITPPOINTTYPE_SELECTED,	// This will use the exact hit location on the surface as the hitpoint
	FIRSTHITPPOINTTYPE_AVERAGE,		// This will use the average location of all the points that the brush dab touches.
} ENUM_END_LIST(FIRSTHITPPOINTTYPE);

//----------------------------------------------------------------------------------------
/// A brush be one of 2 modes
//----------------------------------------------------------------------------------------
enum SCULPTBRUSHMODE
{
	SCULPTBRUSHMODE_NORMAL, // Samples the surface as the user moves over it the SculptObject and returns a new hitpoint and normal each time.  
	SCULPTBRUSHMODE_GRAB,	// Calculates affected points, hitpoint and normal the first time the user clicks. These are the only points that are affected as the user moves the mouse. This mode is used by the Grab Tool which uses the GetMousePos3D() method to get the mouse position in 3D space as the user moves it in 3D space.
} ENUM_END_LIST(SCULPTBRUSHMODE);

//----------------------------------------------------------------------------------------
/// Specifies what kind of data is affected by the brush
//----------------------------------------------------------------------------------------
enum SCULPTBRUSHDATATYPE
{
	SCULPTBRUSHDATATYPE_NONE = 0,
	SCULPTBRUSHDATATYPE_POINT = 1<<0,				// The points are changed.
	SCULPTBRUSHDATATYPE_MASK = 1<<1,				// The mask data is changed.
	SCULPTBRUSHDATATYPE_COLOR = 1<<2,				// Internal.
	SCULPTBRUSHDATATYPE_DIRTYPOINTS = 1<<3,			// Internally used by tiles to check if all its points have already been marked as dirty or not.
} ENUM_END_FLAGS(SCULPTBRUSHDATATYPE);

//----------------------------------------------------------------------------------------
/// Overrides are set by modifier keys to signal to the brush that it should do something different.
//----------------------------------------------------------------------------------------
enum OVERRIDE
{
	OVERRIDE_INVERT = 1<<0,		// If the user holds down the Ctrl key then the brush should Invert its functionality.
	OVERRIDE_SMOOTH = 1<<1,		// The user is holding down the Shift key and a smooth operation should be done. Tools can choose to specify their own operation for smooth, like the Mask Tool which does a blur.
	OVERRIDE_SMOOTHTOOL = 1<<2  // Internal. This is used internally to specify that the smooth is tool specific.
} ENUM_END_FLAGS(OVERRIDE);

//----------------------------------------------------------------------------------------
/// The sample mode to use when sampling the textures for stamps or stencils.
//----------------------------------------------------------------------------------------
enum SAMPLEMODE
{
	SAMPLEMODE_0 = 1<<0,					// Takes the exact pixel at the intersection point.
} ENUM_END_FLAGS(SAMPLEMODE);


//----------------------------------------------------------------------------------------
/// Flags for the OffsetPoint methods to allow you to use or ignore settings for the layer such as Mask and Strength.
//----------------------------------------------------------------------------------------
enum SCULPTOFFSETFLAGS
{
	SCULPTOFFSETFLAGS_0 = 0,
	SCULPTOFFSETFLAGS_RESPECTSTRENGTH = 1<<0,		//Respect the Strength of the current layer. 
	SCULPTOFFSETFLAGS_IGNOREMASK = 1<<1,				//Ignore the Mask setting for the current layer.
} ENUM_END_FLAGS(SCULPTOFFSETFLAGS);

#define LIBRARY_SCULPTBRUSH	1028489

//----------------------------------------------------------------------------------------
/// The data for each point in a brush dab.
//----------------------------------------------------------------------------------------
struct BrushPointData
{
	Int32 internalData;	// Private
	Int32 pointIndex;	// Index of the the point on the PolygonObject/SculptObject.
	Float distance;		// Distance from the hitpoint of the dab.
};

//----------------------------------------------------------------------------------------
/// The data for each point in a brush dab.
//----------------------------------------------------------------------------------------
struct BrushPolyData
{
	Int32 polyIndex; // The index of the polygon on the PolygonObject/SculptObject
};


class SculptPointData; // Internal
class SculptLayer;
class SculptObject;


//----------------------------------------------------------------------------------------
/// The brush data for an individual dab. This is passed into the method defined by the user in surfaceMovePointFunc. 
//----------------------------------------------------------------------------------------
class BrushDabData
{
private:
	BrushDabData();
	~BrushDabData();

public:
	//----------------------------------------------------------------------------------------
	/// Gets the BaseContainer for the Tool.
	/// @return				The BaseContainer.
	//----------------------------------------------------------------------------------------
	const BaseContainer *	GetData();

	//----------------------------------------------------------------------------------------
	/// Gets the SculptObject that the dab is for.
	/// @return				The SculptObject.
	//----------------------------------------------------------------------------------------
	const SculptObject *	GetObject();

	//----------------------------------------------------------------------------------------
	/// Gets the list of points that are affected by the brush. Use GetPointCount() to get the number of points in the returned array.
	/// @return				The list of points.
	//----------------------------------------------------------------------------------------
	const BrushPointData *	GetPointData();

	//----------------------------------------------------------------------------------------
	/// Gets the list of the polygons that are affected by the brush. Use GetPolyCount() to get the number of polygons in the returned array.
	/// @return				The list of polygons.
	//----------------------------------------------------------------------------------------
	const BrushPolyData *   GetPolyData();

	//----------------------------------------------------------------------------------------
	/// Gets the PolygonObject for the SculptObject that is currently being displayed in the viewport.
	/// @return				The PolygonObject.
	//----------------------------------------------------------------------------------------
	PolygonObject *			GetPolygonObject();

	//----------------------------------------------------------------------------------------
	/// Gets the original object that the SculptTag is applied to. In the case where this there is no SculptTag on then this will
	/// return the same as the call to GetPolygonObject();
	/// @return				The PolygonObject.
	//----------------------------------------------------------------------------------------
	PolygonObject *			GetBaseObject();

	//----------------------------------------------------------------------------------------
	/// Gets the number of points that are touched by the dab that are in the array returned from GetPointData().
	/// @return				The number of points.
	//----------------------------------------------------------------------------------------
	Int32					GetPointCount();  //Number of points returned by GetPointData();

	//----------------------------------------------------------------------------------------
	/// Gets the number of polygons that are touched by the dab that are in the array returned from GetPolyData().
	/// @return				The number of points.
	//----------------------------------------------------------------------------------------
	Int32					GetPolyCount();	 

	//----------------------------------------------------------------------------------------
	/// This will get the Neighbor information for the SculptObject if SculptObject is currently at level 0.
	/// If the user is sculpting a regular unsubdivided PolygonObject then this will also return a valid pointer.
	/// @return				The Neighbor information if SculptObject is at level 0 (or if the user is sculpting on a regular PolygonObject) otherwise it will return nullptr.
	//----------------------------------------------------------------------------------------
	Neighbor *				GetNeighbor();

	//----------------------------------------------------------------------------------------
	/// Returns the currently selected Layer for a Subdivided SculptObject. If the user is sculpting a regular PolygonObject then this will return a nullptr.
	/// @return				The currently selected layer in the LayerManager if it is a subdivided SculptObject, otherwise nullptr.
	//----------------------------------------------------------------------------------------
	SculptLayer *			GetLayer();

	//----------------------------------------------------------------------------------------
	/// Returns the live points that are modified on the surface during a brush stroke. These points may already have been modified by previous brush dabs during the current brush stroke.
	/// @return				The points on the PolygonObject that is currently displayed in the viewport.
	//----------------------------------------------------------------------------------------
	const Vector *			GetPoints();

	//----------------------------------------------------------------------------------------
	/// Returns a copy of the points in their state BEFORE the brush stroke started. You can use these points to compare where the surface was before the user started sculpting.
	/// As an example this data is used by the grab tool to correctly offset the points based on their original location on the surface at the first mouse click.
	/// @return				The points of the PolygonObject at the state it was in when the user first pressed the left mouse button down.
	//----------------------------------------------------------------------------------------
	const Vector32 *		GetOriginalPoints();

	//----------------------------------------------------------------------------------------
	/// This method returns the Normal at the current hitpoint for the dab. This is the average vertex normal of all the points that are affected by the dab.
	/// @return				The Normal at the current hitpoint
	//----------------------------------------------------------------------------------------
	Vector					GetNormal();

	//----------------------------------------------------------------------------------------
	/// Gets the brush strength for the dab. 
	/// This strength is not the same as the strength in the BaseContainer. This also takes into account many other variables including tablet pressure to create the value.
	/// @return				The strength of the brush.
	//----------------------------------------------------------------------------------------
	Float					GetBrushStrength();

	//----------------------------------------------------------------------------------------
	/// Gets the brush radius for the dab. 
	/// This is not the same as the brush size in the BaseContainer. This also takes into account other factors such as the distance from the camera and scale of the object
	/// and tablet values to determine the correct brush radius. The size of the radius is in the sculpt objects local space.
	/// @return				The radius of the brush.
	//----------------------------------------------------------------------------------------
	Float					GetBrushRadius();

	//----------------------------------------------------------------------------------------
	/// If the brush mode is SCULPTBRUSHMODE_GRAB then this method can be used to get the location of the mouse pointer in world space in the scene.
	/// @return				If the SculptMode is SCULPTBRUSHMODE_GRAB it will return position of the mouse in world space, otherwise it returns a Vector(0,0,0)
	//----------------------------------------------------------------------------------------
	Vector					GetMousePos3D();

	//----------------------------------------------------------------------------------------
	/// Gets the point on the surface of the SculptObject where the dab is going to be placed. This is the center of the dab.
	/// If the mode is set to SCULPTBRUSHMODE_GRAB then this always returns the initial hit point that occurred when the user first pressed the left mouse button down.
	/// @return				The hitpoint on the surface.
	//----------------------------------------------------------------------------------------
	Vector					GetHitPoint();

	//----------------------------------------------------------------------------------------
	/// Gets the hit point for the previous dab during the stroke.
	/// @return				The hitpoint on the surface.
	//----------------------------------------------------------------------------------------
	Vector					GetLastHitPoint();

	//----------------------------------------------------------------------------------------
	/// This is the location of the mouse in local space above the model. 
	/// This point is created by interpolating between previous and next real mouse hitpoint on the surface of the SculptObject. 
	/// This is then projected down onto the surface of the model to get the real hitpoint for this interpolated value.
	/// @return				The virtual mouse location in local space above the surface of the SculptObject.
	//----------------------------------------------------------------------------------------
	Vector					GetEyePoint();

	//----------------------------------------------------------------------------------------
	/// This will return true if this dab is for a mirrored brush stroke. 
	/// @return				True if its a mirrored dab or False if its the main brush stroke.
	//----------------------------------------------------------------------------------------
	Bool					IsMirroredDab();

	//----------------------------------------------------------------------------------------
	/// Gets the override flags. This could be any combination of the OVERRIDE_X flags.
	/// @return				Returns the Overrides if there are any or 0 if there are none.
	//----------------------------------------------------------------------------------------
	Int32					GetBrushOverride();

	//----------------------------------------------------------------------------------------
	/// Gets the BaseDraw that the user is currently drawing in.
	/// @return				Returns the BaseDraw
	//----------------------------------------------------------------------------------------
	BaseDraw *				GetBaseDraw();

	//----------------------------------------------------------------------------------------
	/// Depending on what the FixedPlane (MDATA_SCULPTBRUSH_SETTINGS_FIXEDPLANE) setting is for the brush this will return one of 3 things.
	///
	/// - MDATA_SCULPTBRUSH_SETTINGS_FIXEDPLANE_OFF
	///		- averagePoint	= The average location of all the points that are touched by the dab.
	///		- normal		= The normal at the hitpoint on the surface of the SculptObject
	/// - MDATA_SCULPTBRUSH_SETTINGS_FIXEDPLANE_MOUSEDOWN
	///		- averagePoint	= The average location of all the points under the dab area when the mouse was mouse button was first pressed.
	///		- normal		= The average normal of all the points under the dab area when the mouse was mouse button was first pressed.
	/// - MDATA_SCULPTBRUSH_SETTINGS_FIXEDPLANE_WORKPLANE
	///		- averagePoint	= The point on the workplane that is above the hitpoint on the surface of the SculptObject 
	///		- normal		= The normal of the workplane.
	///
	///	@param[in,out] averagePoint		Returns the averagePoint based on the fixedplane setting.
	///	@param[in,out] normal				Returns the normal based on the fixedplane setting.
	//----------------------------------------------------------------------------------------
	void					GetAveragePointAndNormal(Vector &averagePoint, Vector &normal);

	//----------------------------------------------------------------------------------------
	/// Calling this will apply a effect of the smooth brush to the current dab. Call this after you have modified the dab to smooth it out if you need to.
	//----------------------------------------------------------------------------------------
	void					ApplySmooth();

	//----------------------------------------------------------------------------------------
	/// Get the vertex normals for the SculptObject. The number of vertex normals is equal to the number of points on the PolygonObject returned from GetPolygonObject().
	/// @return		The vertex normals for the SculptObject.
	//----------------------------------------------------------------------------------------
	const Vector32*			GetVertexNormals();

	//----------------------------------------------------------------------------------------
	/// This returns a value which represents the scale of the sculpt object. 
	/// This can be used to convert a distance in object space with the value returned from GetBrushRadius() to help adjust the algorithm for your brush
	/// since the value returned from GetBrushRadius is also already adjusted using the same value.
	/// @param[in] noRadius						true means it will not take into account the radius of the object in its calculation and will only use the scale.
	/// @return									The scale value with which to adjust your local space vector or distance value.
	//----------------------------------------------------------------------------------------
	Float					GetAutoScaleValue(Bool noRadius);

	//----------------------------------------------------------------------------------------
	/// Returns the brush falloff for the point specified by the index value. 
	/// The falloff is already adjusted by using the values from the stamp and stencil so it can be used directly to adjust the strength of an offset that you wish to add to the layer.
	/// Internally this method will use the distance that this point is from the hitpoint in its calculation (BrushPointData.distance). You can use a custom value instead by
	/// passing in a value to pCustomDistance if you wish to use something different.
	/// Additionally the color of the stencil can be returned from this call by passing in a Vector for the parameter pRetStencilColor. This saves an additional call to GetStencilColor().
	/// @param[in] index						The index of the point in the BrushPointData returned from the call to GetPointData();
	/// @param[out] pRetStencilColor			The color of the stencil
	/// @param[in] pCustomDistance				The custom distance to use instead of the points actual distance from the hit point.
	/// @return									The final falloff value that can be used to adjust the offset value.
	//----------------------------------------------------------------------------------------
	Float					GetBrushFalloff(Int32 index, Vector32 *pRetStencilColor=nullptr, Float *pCustomDistance=nullptr);

	//----------------------------------------------------------------------------------------
	/// Returns the falloff value, defined by the falloff curve, based on the distance from input pos to the hitpoint for the dab.
	/// @param[in] pos						A point in 3D space to get the falloff for.
	/// @return										The falloff value.
	//----------------------------------------------------------------------------------------
	Float					GetBrushFalloffFromPos(const Vector &pos);

	//----------------------------------------------------------------------------------------
	/// Offset the point on the layer by the given offset amount.
	/// This method should be used if IsPreviewDab() returns false, otherwise you should use the OffsetPreviewPoint() method.
	/// @param[in] index				The index of the point on the SculptObject. This value can be found for the current point using BrushPointData.pointIndex.
	/// @param[in] offset				The vector to offset the point by.
	/// @param[in] pVertexColor			Private! Used internally.
	/// @param[in] flags				SCULPTOFFSETFLAGS to let you use or ignore settings such as the layers mask or strength when offsetting the point. By setting the SCULPTOFFSETFLAGS_IGNOREMASK flag it will ignore what ever the mask checkbox state is for the layer. Otherwise it uses this state to determine if it should use the mask.
	//----------------------------------------------------------------------------------------
	void					OffsetPoint(Int32 index, const Vector &offset, Vector32 *pVertexColor=nullptr, SCULPTOFFSETFLAGS flags=SCULPTOFFSETFLAGS_0);

	//----------------------------------------------------------------------------------------
	/// Returns True if this dab is a preview dab. Currently only DragRect and DragDab support preview brushes.
	/// @return							True if it is a preview dab, False if not.
	//----------------------------------------------------------------------------------------
	Bool					IsPreviewDab();

	//----------------------------------------------------------------------------------------
	/// If IsPreviewDab() returns true then you should apply your offset using this method. This adds the offset to a temporary preview layer
	/// that is created when using the DragDab and DragRect draw modes. If IsPreviewDab() is false then you should use the method OffsetPoint(...) instead.
	/// @param[in] index				The index of the point on the SculptObject. This value can be found for the current point using BrushPointData.pointIndex.
	/// @param[in] offset				The vector to offset the point by.
	/// @param[in] flags				You can choose to ignore the mask by setting it to SCULPTOFFSETFLAGS_IGNOREMASK. Otherwise it uses this state of the mask checkbox for the layer to determine if it should use the mask or not. 
	//----------------------------------------------------------------------------------------
	void					OffsetPreviewPoint(Int32 index, const Vector &offset, SCULPTOFFSETFLAGS flags=SCULPTOFFSETFLAGS_0);

	//----------------------------------------------------------------------------------------
	/// Dirty all the points for this dab according to the SCULPTBRUSHDATATYPE
	/// @param[in] type					The SCULPTBRUSHDATATYPE to use.
	//----------------------------------------------------------------------------------------
	void					DirtyAllPoints(SCULPTBRUSHDATATYPE type);

	//----------------------------------------------------------------------------------------
	/// When using symmetry another mirrored brush may change the point. 
	/// You can use this to check if a another brush stroke has changed a point and if so then you can do something different for this current stroke.
	/// @param[in] index				The index of the point on the SculptObject.
	/// @return							True if the point was modified, False if not.
	//----------------------------------------------------------------------------------------
	Bool					IsPointModified(Int32 index); //

	//----------------------------------------------------------------------------------------
	/// Get the color, and gray value, of the stencil for a point in the sculpt objects local space. 
	/// @param[in] point				Point on the surface of the sculpt object for which to get a color for.
	/// @param[out] pRetColor			The returned color of the stencil
	/// @param[out] pRetCoords			The returned coordinates of the pixel on the stencil bitmap
	/// @param[in] mode					The sample mode used to sample the stencil texture
	/// @return							The grey scale value of the stencil, which has been adjusted by the stencils Gray Value.
	//----------------------------------------------------------------------------------------
	Float					GetStencilColor(const Vector &point, Vector32 *pRetColor = nullptr, Vector32 *pRetCoords = nullptr, SAMPLEMODE mode = SAMPLEMODE_0);

	//----------------------------------------------------------------------------------------
	/// Get the color, and gray value, of the stamp for a point in the sculpt objects local space.
	/// @param[in] point							A point in the sculpt objects coordinate system which is used to sample the stamp on the current dab.
	/// @param[in] distanceFromHitPoint		Can be either the BrushPointData.distance value, the length of the vector (hitpoint - point) or a custom distance value. This is used to get the correct falloff for the point.
	/// @param[out] pRetColor						The returned color of the stamp
	/// @param[out] pRetCoords						The returned coordinates of the pixel on the stamp bitmap
	/// @param[in] mode								The sample mode used to sample the stencil texture
	/// @return										The grey scale value of the stamp, which has been adjusted by the stamps Gray Value.
	//----------------------------------------------------------------------------------------
	Float					GetStampColor(const Vector &point, Float distanceFromHitPoint, Vector32 *pRetColor = nullptr, Vector32 *pRetCoords = nullptr, SAMPLEMODE mode = SAMPLEMODE_0);

	//----------------------------------------------------------------------------------------
	/// Get the stamp used for this dab
	/// @return				The bitmap for the stamp
	//----------------------------------------------------------------------------------------
	const BaseBitmap* GetStamp();

	//----------------------------------------------------------------------------------------
	/// Get the stencil used for this dab
	/// @return				The bitmap for the stencil
	//----------------------------------------------------------------------------------------
	const BaseBitmap* GetStencil();

	//----------------------------------------------------------------------------------------
	/// Gets the Brush being used. 
	/// This will only return the brush if EnableBrushAccess(true) has been set in the SculptBrushParams.
	/// Always check to make sure the returned pointer is not a nullptr. 
	/// @return										Returns a pointer to the brush. 
	//----------------------------------------------------------------------------------------
	SculptBrushToolData*	GetBrush();

	//----------------------------------------------------------------------------------------
	/// Gets the ID of the stroke instance that this dab is being drawn for.
	/// @return										The instance ID;
	//----------------------------------------------------------------------------------------
	Int32					GetStrokeInstanceID();

	//----------------------------------------------------------------------------------------
	/// This will return true if the object being touched is SculptObject (ie has a SculptTag).
	/// @return				True if its a SculptObject. False if not.
	//----------------------------------------------------------------------------------------
	Bool					IsSculptObject();

};

class CustomSculptBrushBase
{
	friend class SculptBrushHotkeyCommandData;
private:

	CustomSculptBrushBase();
	~CustomSculptBrushBase();

	_SculptBrushToolBase *m_pBase;

public:

	static CustomSculptBrushBase *Alloc();
	static void Free(CustomSculptBrushBase *&p);

	Bool InitTool(BaseDocument* doc, BaseContainer& data, BaseThread* bt, SculptBrushToolData *tool);
	void FreeTool(BaseDocument* doc, BaseContainer& data, SculptBrushToolData *tool);
	void InitDefaultSettings(BaseDocument *doc, BaseContainer &data, SculptBrushToolData *tool);
	Bool GetDEnabling(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc, SculptBrushToolData *tool);
	Bool SetDParameter(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_SET& flags, SculptBrushToolData *tool);
	Bool GetDDescription(BaseDocument* doc, BaseContainer& data, Description* description, DESCFLAGS_DESC& flags, SculptBrushToolData *tool);
	Bool Message(BaseDocument *doc, BaseContainer &data, Int32 type, void *t_data, SculptBrushToolData *tool);
	Bool GetCursorInfo(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, Float x, Float y, BaseContainer& bc, SculptBrushToolData *tool);
	Bool MouseInput(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg, SculptBrushToolData *tool);
	Bool KeyboardInput(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, EditorWindow *win, const BaseContainer &msg, SculptBrushToolData *tool);
	Int32 GetState(BaseDocument *doc, SculptBrushToolData *tool);
	TOOLDRAW Draw(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, BaseDrawHelp *bh, BaseThread *bt,TOOLDRAWFLAGS flags, SculptBrushToolData *tool);
	Bool GetDParameter(BaseDocument* doc, BaseContainer& data, const DescID& id, GeData& t_data, DESCFLAGS_GET& flags, SculptBrushToolData *tool);
	Bool DisplayControl(BaseDocument* doc, BaseObject* op, BaseObject* chainstart, BaseDraw* bd, BaseDrawHelp* bh, ControlDisplayStruct& cds, SculptBrushToolData *tool);
	Bool InitDisplayControl(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, const AtomArray* active, SculptBrushToolData *tool);
	void FreeDisplayControl(SculptBrushToolData *tool);

	//Virtual
public:
	void StartStroke(Int32 strokeCount, const BaseContainer &data);
	void StartStrokeInstance(Int32 strokeInstanceID);
	void StartSymmetry();
	void StartStrokeInstanceDabs(Int32 strokeInstanceID);
	void StartDab(Int32 strokeInstanceID);
	void EndDab(Int32 strokeInstanceID);
	void EndStrokeInstanceDabs(Int32 strokeInstanceID);
	void EndSymmetry();
	void EndStrokeInstance(Int32 strokeInstanceID);
	void EndStroke();

	void OverwriteLoadedPresetSettings(BaseContainer &data);
	void PostInitDefaultSettings(BaseDocument *doc, BaseContainer &data);
	Bool GetEnabling(Int32 id); 
	Bool HandleFillTool(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg);
	Bool HandleNonModelPickMode(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg);
	Bool DrawNonModelPickMode(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, BaseDrawHelp *bh, BaseThread *bt,TOOLDRAWFLAGS flags);
	void FloodSelectedLayer(SculptObject *pSculpt, SculptLayer *pLayer, const BaseContainer& brushData, Int32 function, Bool preview, Float *customStrength=nullptr, const Vector32 *pVertexNormals=nullptr);
	Bool HasDrawMode(Int32 mode);

	//Non Virtual
public:
	Bool Flood(BaseDocument* doc, BaseDraw* bd, const BaseContainer& brushData, Int32 button = MDATA_SCULPTBRUSH_SETTINGS_FLOOD);
	void EnableSpecialDrawGizmo();
	void DisableSpecialDrawGizmo();
	void SetMouseDrag(Bool value);
	Bool IsMouseDrag();
	void CacheObjects(BaseDocument *doc);
	Int32 GetSelectionCacheCount();
	BaseList2D *GetSelectionCacheObject(Int32 index); 
	Float GetBrushStrength(Bool original);
	void InitZoomScale(BaseDocument *doc);

	//Methods called by the Preset System
	Bool WritePresetData(HyperFile *hf);
	Bool ReadPresetData(HyperFile *hf,Int32 level);
	Bool WriteStampPresetData(HyperFile *hf);
	Bool ReadStampPresetData(HyperFile *hf,Int32 level);
	Bool WriteSplinePresetData(HyperFile *hf);
	Bool ReadSplinePresetData(HyperFile *hf,Int32 level);
	void UpdateSettingsAfterPresetLoad(BaseContainer *data);

	const BaseBitmap *GetStamp();
	const BaseBitmap *GetStencil();
};

//----------------------------------------------------------------------------------------
/// The parameters to pass in when registering a SculptingBrush.
///
/// @code
/// SculptBrushParams *pParams = SculptBrushParams::Alloc();
/// RegisterToolPlugin(ID_YOUR_BRUSH_ID,"BrushName",PLUGINFLAG_HIDEPLUGINMENU|PLUGINFLAG_TOOL_SCULPTBRUSH|PLUGINFLAG_TOOL_NO_OBJECTOUTLINE,nullptr,"Help Text",NewObjClear(YourSculptBrush,params));
///
/// By default the .res file includes the tabs for Stamps and Stencils and the options for Size, Pressure, Steady Stroke, Spacing and the Draw Modes.
/// If you do not want or use any of these options then you will need to hide them in your .res file by adding the following lines to the top of your .res file.
/// CONTAINER toolmysculptbrush
/// {
///		NAME toolmysculptbrush;
///		INCLUDE  toolsculptbrushbase;  
///
///		HIDE MDATA_SCULPTBRUSH_STAMP_GROUP;
///		HIDE MDATA_SCULPTBRUSH_STENCIL_GROUP;
///		HIDE MDATA_SCULPTBRUSH_SETTINGS_RADIUS;			//This is Size
///		HIDE MDATA_SCULPTBRUSH_SETTINGS_RADIUS_MOD;		//This is the FX option for Size.
///		HIDE MDATA_SCULPTBRUSH_SETTINGS_STRENGTH;		//This is Pressure
///		HIDE MDATA_SCULPTBRUSH_SETTINGS_STRENGTH_MOD;	//This is the FX option for Pressure.
///		HIDE MDATA_SCULPTBRUSH_SETTINGS_STEADYSTROKE;
///		HIDE MDATA_SCULPTBRUSH_SETTINGS_STEADYSTROKE_VALUE;
///		HIDE MDATA_SCULPTBRUSH_SETTINGS_STAMPSPACING;
///		HIDE MDATA_SCULPTBRUSH_SETTINGS_STAMPSPACING_VALUE;
///		HIDE MDATA_SCULPTBRUSH_SETTINGS_DRAWMODE;
///		HIDE MDATA_SCULPTBRUSH_SETTINGS_FILL_BACKFACES;
///		HIDE MDATA_SCULPTBRUSH_SETTINGS_DRAWMODE_FILL_SYMMETRY;
/// }
/// 
/// 
/// By Default the Draw Modes that are available are Freehand, Line, Lasso Fill, Poly Fill and Rectangle Fill. If you wish to remove any of these or add more you can do so
/// by customizing the list yourself. Here is an example below where we are adding support for all the different modes, including DragDab and DragRect. 
/// Just remove any from this list to suit your brush. By default FreeHand is set, so if you hide the DrawModes your brush will still work.
///
///	CONTAINER toolmysculptbrush
///	{
///		NAME toolmysculptbrush;
///		INCLUDE toolsculptbrushbase;
///
///		GROUP MDATA_SCULPTBRUSH_SETTINGS_GROUP
///		{
///			COLUMNS 3;
///
///			GROUP
///			{
///				COLUMNS 3;
///				LONG MDATA_SCULPTBRUSH_SETTINGS_DRAWMODE
///				{
///					CYCLE
///					{
///						MDATA_SCULPTBRUSH_SETTINGS_DRAWMODE_FREEHAND;
///						MDATA_SCULPTBRUSH_SETTINGS_DRAWMODE_DRAGRECT;
///						MDATA_SCULPTBRUSH_SETTINGS_DRAWMODE_DRAGDAB;
///						MDATA_SCULPTBRUSH_SETTINGS_DRAWMODE_LINE;
///						MDATA_SCULPTBRUSH_SETTINGS_DRAWMODE_LASSO_FILL;
///						MDATA_SCULPTBRUSH_SETTINGS_DRAWMODE_POLY_FILL;
///						MDATA_SCULPTBRUSH_SETTINGS_DRAWMODE_RECTANGLE_FILL;
///					}
///				}
///				BOOL MDATA_SCULPTBRUSH_SETTINGS_DRAWMODE_FILL_SYMMETRY { }
///				BOOL MDATA_SCULPTBRUSH_SETTINGS_FILL_BACKFACES { }
///			}
///			STATICTEXT { JOINENDSCALE; }
///			STATICTEXT { JOINEND; }
///		}
/// }
///
/// You will also need to make sure the priority for any sculpting plugins are set correctly. Your plugins need to be loaded AFTER the main sculpting plugin.
/// To ensure this you need to set the priority in PluginMessage(Int32 id, void *data) as shown below.
///
/// Bool PluginMessage(Int32 id, void *data)
/// {
///		switch (id)
///		{
///			case C4DPL_INIT_SYS:
///				if (!resource.Init()) return false;
///				return true;
///			case C4DMSG_PRIORITY:
///				SetPluginPriority(data,C4DPL_INIT_PRIORITY_MODULES+1); 
///				return true;
///		}
///		return false;
/// }
/// @endcode
//----------------------------------------------------------------------------------------
class SculptBrushParams
{
private:
	SculptBrushParams();
	~SculptBrushParams();

public:
	static SculptBrushParams *Alloc();
	static void Free(SculptBrushParams *&params);

	//----------------------------------------------------------------------------------------
	/// Does the brush use stencils?
	/// Settings this to false will let the brush know that you are not going to be using stencils. This will free up some resource and computation time.
	/// Note that setting to false will not remove the tab from the brush interface. You will need to add the line "HIDE MDATA_SCULPTBRUSH_STENCIL_GROUP;" to the brushes .res file to remove the tab.
	/// @param[in] enable							true if the brush uses stencils, false if not. Default is true.
	//----------------------------------------------------------------------------------------
	void EnableStencil(Bool enable);

	//----------------------------------------------------------------------------------------
	/// Does the brush use stamps?
	/// Settings this will to false will let the brush know that you are not going to be using stamps. This will free up some resource and computation time.
	/// Note that setting to false will not remove the tab from the brush interface. You will need to add the line "HIDE MDATA_SCULPTBRUSH_STAMP_GROUP;" to the brushes .res file to remove the tab.
	/// @param[in] enable							true if the brush uses stencils, false if not. Default is true.
	//----------------------------------------------------------------------------------------
	void EnableStamp(Bool enable);

	//----------------------------------------------------------------------------------------
	/// Does the brush use the invert checkbox?
	/// Lets the system know if you are using the invert checkbox or not. 
	/// Note that by default the invert checkbox is not part of the base .res file so you will need to add it yourself to your own brushes .res file. 
	///
	/// To do this just add the following data to your .res file exactly as shown.
	///
	/// @code
	/// GROUP MDATA_SCULPTBRUSH_SETTINGS_GROUP
	/// {
	///		COLUMNS 3;
	///		
	///		BOOL MDATA_SCULPTBRUSH_SETTINGS_INVERT { }
	///		STATICTEXT { DUMMY; }
	///		STATICTEXT { DUMMY; }
	///	}
	/// @endcode
	/// @param[in] enable							true if the brush uses the invert checkbox, false if not. Default is false.
	//----------------------------------------------------------------------------------------
	void EnableInvertCheckbox(Bool enable);

	//----------------------------------------------------------------------------------------
	/// Does the brush use the buildup slider?
	/// Lets the system know if you are using the buildup slider or not. 
	/// Note that by default the buildup slider is not part of the base .res file so you will need to add it yourself to your own brushes .res file. 
	///
	/// To do this just add the following data to your .res file exactly as shown.
	///
	/// @code
	/// GROUP MDATA_SCULPTBRUSH_SETTINGS_GROUP
	/// {
	///		COLUMNS 3;
	///
	///		REAL MDATA_SCULPTBRUSH_SETTINGS_BUILDUP { MIN 1; MAX 100; MINSLIDER 1; MAXSLIDER 100; CUSTOMGUI REALSLIDER; FIT_H; SCALE_H; }
	///		STATICTEXT { JOINENDSCALE; }
	///		STATICTEXT { JOINEND; }
	///	}
	/// @endcode
	/// @param[in] enable							true if the brush uses the buildup slider, false if not. Default is false.
	//----------------------------------------------------------------------------------------
	void EnableBuildup(Bool enable);

	//----------------------------------------------------------------------------------------
	/// Does the brush do anything if the user clicks off of a model. IE have you implemented HandleNonModelPickMode and DrawNonModelPickMode.
	/// @param[in] enable							true if you have implemented those methods, false if not. Default is false.
	//----------------------------------------------------------------------------------------
	void EnableNonModelPickMode(Bool enable);

	//----------------------------------------------------------------------------------------
	/// Does the brush have a flood function. IE have you implemented FloodSelectedLayer.
	/// Note that by default the flood button is not part of the base .res file so you will need to add it yourself to your own brushes .res file. 
	/// 
	/// To do this just add the following data to your .res file exactly as shown.
	///
	/// @code
	/// GROUP MDATA_SCULPTBRUSH_SETTINGS_GROUP
	/// {
	///		COLUMNS 3;
	///
	///		BUTTON MDATA_SCULPTBRUSH_SETTINGS_FLOOD{ }
	///		STATICTEXT { JOINENDSCALE; }
	///		STATICTEXT { JOINEND; }
	///	}
	/// @endcode
	/// @param[in] enable							true if you have implemented the method, false if not. Default is false.
	//----------------------------------------------------------------------------------------
	void EnableFlood(Bool enable);

	//----------------------------------------------------------------------------------------
	/// PRIVATE! DO NOT ENABLE!
	/// 
	/// Tells the system that the brush can be multithreaded. If true then the dabs are distributed over multiple threads and will be drawn in any order.
	/// Any calls to the MovePointFunc could now be for any stroke instance and could be out of order and from different threads. 
	/// @param[in] enable							true if multithreaded, false if not. Default is false.
	//----------------------------------------------------------------------------------------
	void EnableMultiThreading(Bool enable);

	//----------------------------------------------------------------------------------------
	/// Enabling this will give you access to the brush via the dab->GetBrush() method.
	/// @param[in] enable							true if you need access to the brush, false if not. Default is false.
	//----------------------------------------------------------------------------------------
	void EnableBrushAccess(Bool enable);

	//----------------------------------------------------------------------------------------
	/// Does the brush have its own smooth operation that gets used when you press the shift key.
	/// You can check for this in the MovePointFunc method by checking if (GetBrushOverride() & OVERRIDE_SMOOTHTOOL) is true and then you can implement your own smooth method.
	/// Otherwise it will use the Smooth Brush for smoothing.
	/// @param[in] enable							true if you are handling smoothing yourself, false if not. Default is false.
	//----------------------------------------------------------------------------------------
	void EnableToolSpecificSmooth(Bool enable);

	//----------------------------------------------------------------------------------------
	/// Specifies what kind of data the flood operation will change (points or mask).
	/// @param[in] type		The flood data type. Default is SCULPTBRUSHDATATYPE_POINT.
	//----------------------------------------------------------------------------------------
	void SetFloodType(SCULPTBRUSHDATATYPE type);

	//----------------------------------------------------------------------------------------
	/// Specifies what type of brush this is (grab or normal).
	/// @param[in] mode		The brush mode. Default is SCULPTBRUSHMODE_NORMAL.
	//----------------------------------------------------------------------------------------
	void SetBrushMode(SCULPTBRUSHMODE mode);

	//----------------------------------------------------------------------------------------
	/// Specifies what should happen when the user first clicks on model before dragging.
	/// @param[in] type		The first hitpoint type. Default is FIRSTHITPPOINTTYPE_SELECTED.
	//----------------------------------------------------------------------------------------
	void SetFirstHitPointType(FIRSTHITPPOINTTYPE type);

	//----------------------------------------------------------------------------------------
	/// Specifies what kind of data the brush will be changing and storing in the undo system (point or mask).
	/// @param[in] type		The brush data type. Default is SCULPTBRUSHDATATYPE_POINT.
	//----------------------------------------------------------------------------------------
	void SetUndoType(SCULPTBRUSHDATATYPE type);

	//----------------------------------------------------------------------------------------
	/// A pointer to the static method that will be called to modify the sculpt object.
	/// The MovePointFunc method must be implemented and must be passed in here. 
	/// @code
	/// //To implement the method you should create one like the following.
	/// 
	/// //Your header file will contain something like this...
	/// class MySculptBrush : public SculptBrushToolData
	/// {
	///		public:
	///		MySculptBrush(SculptBrushParams *pParams) : SculptBrushToolData(pParams) { }
	///		virtual Int32 GetToolPluginId();			// Return the unique id for your plugin as obtained from www.plugincafe.com
	///		virtual const String GetResourceSymbol();	// Return the name of your resource file for this brush. This will be something like "toolmysculptbrush", where the resource file will be called toolmysculptbrush.res
	///
	///		static Bool MovePointsFunc(BrushDabData *dab); //This is the static implementation for the MovePointFunc
	/// };
	/// 
	/// //Then you declare the method like so...
	///	Bool MySculptBrush::MovePointsFunc(BrushDabData *dab)
	/// {
	///		//Implement the functionality of your brush here!
	///		return true;
	/// }
	/// 
	/// //Then you pass it into the params method like so...
	/// pParams->SetMovePointFunc(&MySculptBrush::MovePointsFunc);
	/// @endcode
	/// @param[in] surfaceMovePointFunc		The static method to call for each brush dab.
	//----------------------------------------------------------------------------------------
	void SetMovePointFunc(Bool (*surfaceMovePointFunc)(BrushDabData *dab));
};


//----------------------------------------------------------------------------------------
/// Derive your new brush from this class and register it.
/// @code
/// class MySculptBrush : public SculptBrushToolData
/// {
///		public:
///		MySculptBrush(SculptBrushParams *pParams) : SculptBrushToolData(pParams) { }
///		virtual Int32 GetToolPluginId();			// Return the unique id for your plugin as obtained from www.plugincafe.com
///		virtual const String GetResourceSymbol();	// Return the name of your resource file for this brush. This will be something like "toolmysculptbrush", where the resource file will be called toolmysculptbrush.res
///
///		static Bool MovePointsFunc(BrushDabData *dab); //This is the static implementation for the MovePointFunc
/// };
///
/// Bool RegisterMyBrush()
/// {
///		SculptBrushParams *pParams = SculptBrushParams::Alloc();
///		return RegisterToolPlugin(ID_YOUR_BRUSH_ID,"BrushName",PLUGINFLAG_HIDEPLUGINMENU|PLUGINFLAG_TOOL_SCULPTBRUSH|PLUGINFLAG_TOOL_NO_OBJECTOUTLINE,nullptr,"Help Text",NewObjClear(MySculptBrush,params));
/// }
/// @endcode
//----------------------------------------------------------------------------------------
class SculptBrushToolData : public DescriptionToolData
{
	INSTANCEOF(SculptBrushToolData,DescriptionToolData)

public:

	SculptBrushToolData(SculptBrushParams *pParams) :m_pParams(pParams), m_pBrushBase(nullptr) { }
	~SculptBrushToolData() 
	{ 
		CustomSculptBrushBase::Free(m_pBrushBase); 
		SculptBrushParams::Free(m_pParams);
	}

	SculptBrushParams *m_pParams;
	CustomSculptBrushBase *m_pBrushBase;

	//////////////////////////////////////////////////////////////////////////
	//Base Virtual Methods. See the standard Cinema4D SDK documentation for more information on these methods.
	//////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------------------------------------
	/// This method is defined in the SDK Documentation.
	/// If this method is overridden then make sure to also call this method directly SculptBrushToolData::InitTool(doc,data,bt) at the start and check that it returns true.
	//----------------------------------------------------------------------------------------
	virtual Bool InitTool(BaseDocument* doc, BaseContainer& data, BaseThread* bt);

	//----------------------------------------------------------------------------------------
	/// This method is defined in the SDK Documentation.
	/// If this method is overridden then make sure to also call this method directly SculptBrushToolData::FreeTool(doc,data) at the end.
	//----------------------------------------------------------------------------------------
	virtual void FreeTool(BaseDocument* doc, BaseContainer& data);

	//----------------------------------------------------------------------------------------
	/// This method is defined in the SDK Documentation.
	/// If this method is overridden then make sure to also call this method directly SculptBrushToolData::InitDefaultSettings(doc,data) at the start.
	//----------------------------------------------------------------------------------------
	virtual void InitDefaultSettings(BaseDocument *doc, BaseContainer &data);

	//----------------------------------------------------------------------------------------
	/// This method is defined in the SDK Documentation.
	/// If this method is overridden then make sure to also call this method directly SculptBrushToolData::GetDEnabling(doc,data,id,t_data,flags,itemdesc) at the end.
	//----------------------------------------------------------------------------------------
	virtual Bool GetDEnabling(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc);

	//----------------------------------------------------------------------------------------
	/// This method is defined in the SDK Documentation.
	/// If this method is overridden then make sure to also call this method directly SculptBrushToolData::SetDParameter(doc,data,id,t_data,flags) at the start.
	//----------------------------------------------------------------------------------------
	virtual Bool SetDParameter(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_SET& flags);

	//----------------------------------------------------------------------------------------
	/// This method is defined in the SDK Documentation.
	/// If this method is overridden then make sure to also call this method directly SculptBrushToolData::GetDDescription(doc,data,description,flags) at the start.
	//----------------------------------------------------------------------------------------
	virtual Bool GetDDescription(BaseDocument* doc, BaseContainer& data, Description* description, DESCFLAGS_DESC& flags);

	//----------------------------------------------------------------------------------------
	/// This method is defined in the SDK Documentation.
	/// If this method is overridden then make sure to also call this method directly SculptBrushToolData::Message(doc,data,type,t_data) at the end.
	//----------------------------------------------------------------------------------------
	virtual Bool Message(BaseDocument *doc, BaseContainer &data, Int32 type, void *t_data);

	//----------------------------------------------------------------------------------------
	/// This method is defined in the SDK Documentation.
	/// If this method is overridden then make sure to also call this method directly SculptBrushToolData::GetCursorInfo(doc,data,x,y,bc) at the end.
	//----------------------------------------------------------------------------------------
	virtual Bool GetCursorInfo(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, Float x, Float y, BaseContainer& bc);

	//----------------------------------------------------------------------------------------
	/// This method is defined in the SDK Documentation.
	/// If this method is overridden then make sure to also call this method directly SculptBrushToolData::MouseInput(doc,data,bd,win,msg) at the end.
	//----------------------------------------------------------------------------------------
	virtual Bool MouseInput(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg);

	//----------------------------------------------------------------------------------------
	/// This method is defined in the SDK Documentation.
	/// If this method is overridden then make sure to also call this method directly SculptBrushToolData::KeyboardInput(doc,data,bd,win,msg) at the end.
	//----------------------------------------------------------------------------------------
	virtual Bool KeyboardInput(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, EditorWindow *win, const BaseContainer &msg);

	//----------------------------------------------------------------------------------------
	/// This method is defined in the SDK Documentation.
	/// If this method is overridden then make sure to also call this method directly SculptBrushToolData::Draw(doc,data,bd,bh,bt,flags) at the end.
	//----------------------------------------------------------------------------------------
	virtual TOOLDRAW Draw(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, BaseDrawHelp *bh, BaseThread *bt, TOOLDRAWFLAGS flags);

	//----------------------------------------------------------------------------------------
	/// This method is defined in the SDK Documentation.
	/// If this method is overridden then make sure to also call this method directly SculptBrushToolData::GetDParameter(doc,data,id,t_data,flags) at the end.
	//----------------------------------------------------------------------------------------
	virtual Bool GetDParameter(BaseDocument* doc, BaseContainer& data, const DescID& id, GeData& t_data, DESCFLAGS_GET& flags);

	//----------------------------------------------------------------------------------------
	/// This method is defined in the SDK Documentation.
	/// If this method is overridden then make sure to also call this method directly SculptBrushToolData::DisplayControl(doc,op,chainstart,bd,bh,cds) at the end.
	//----------------------------------------------------------------------------------------
	virtual Bool DisplayControl(BaseDocument* doc, BaseObject* op, BaseObject* chainstart, BaseDraw* bd, BaseDrawHelp* bh, ControlDisplayStruct& cds);

	//----------------------------------------------------------------------------------------
	/// This method is defined in the SDK Documentation.
	/// If this method is overridden then make sure to also call this method directly SculptBrushToolData::InitDisplayControl(doc,data,bd,active) at the end.
	//----------------------------------------------------------------------------------------
	virtual Bool InitDisplayControl(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, const AtomArray* active);

	//----------------------------------------------------------------------------------------
	/// This method is defined in the SDK Documentation.
	/// If this method is overridden then make sure to also call this method directly SculptBrushToolData::FreeDisplayControl() at the end.
	//----------------------------------------------------------------------------------------
	virtual void FreeDisplayControl(void);

	//----------------------------------------------------------------------------------------
	/// This method is defined in the SDK Documentation.
	/// Indicates if the brush is active or not (greyed out in the interface).
	/// If this method is overridden then make sure to also call this method directly SculptBrushToolData::GetState() at the end.
	//----------------------------------------------------------------------------------------
	virtual Int32 GetState(BaseDocument *doc);


	//////////////////////////////////////////////////////////////////////////
	//Sculpt Brush Virtual Methods.
	//////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------------------------------------
	/// StartStroke is called once at the start of the stroke.
	/// It passes the total number of instances of the brush that will be drawn. The number of instances will change depending on the symmetry mirroring and radial settings. 
	///
	/// Use this method to setup any data on your brush that you might want to access from within your MovePointFunc function via the dab->GetBrush() method.
	///
	/// This method will only be called if SculptBrushParams->EnableBrushAccess(true) has been set.
	///
	/// Calling order for brush stroke virtual methods
	/// @code
	/// - StartStroke: Called once at the start of the stroke
	///		- StartStrokeInstance: Call for each instance of a stroke that will be used. Use this to initialize any data you might need for the duration of the entire brush stroke.
	///			- StartSymmetry: Called once before all the instances are about to be drawn for a small mouse movement. This will be called MANY times during a stroke as the mouse moves over the model.
	///				- StartStrokeInstanceDabs: Called once before a bunch of consecutive dabs will be draw for a single instance (mirrored brush).
	///					- StartDab: Called for each dab that needs to be drawn between 2 mouse locations on the object for a single brush stroke instance
	///						- The static method MovePointFunc gets called to process the dab
	///					- EndDab
	///				- EndStrokeInstanceDabs
	///			- EndSymmetry: Called once when all symmetrical strokes have finished.
	///		- EndStrokeInstance: Called for each instance of a stroke that was used
	///	- EndStroke
	/// @endcode
	/// 
	/// When Multithreading is enable for this brush then this method can be used to allocate data for each stroke instance. Each instance or dab can then safely read from this this data during
	/// a brush stroke. This will only be done once at mouse down.
	///
	/// @param[in] strokeCount					Number of instances of the brush that will be drawn
	/// @param[in] data									The BaseContainer data for the brush
	//----------------------------------------------------------------------------------------
	virtual void StartStroke(Int32 strokeCount, const BaseContainer &data);

	//----------------------------------------------------------------------------------------
	/// Called after StartStroke. This is called once for each brush instance at the start of a stroke. 
	/// The number of instances will change depending on the symmetry mirroring and radial settings. 
	/// Use this method to allocate any data you may want to access during a brush stroke, that may be specific for each individual instance.
	///
	/// This should also be used to setup any data on your brush that you might want to access from within your MovePointFunc function via the dab->GetBrush() method.
	/// This method will only be called if SculptBrushParams->EnableBrushAccess(true) has been set.
	/// 
	/// When Multithreading is enable for this brush then this method can be used to initialize data for each stroke instance. This will only be done once at mouse down.
	/// @param[in] strokeInstanceID				The ID of the brush instance being drawn.
	//----------------------------------------------------------------------------------------
	virtual void StartStrokeInstance(Int32 strokeInstanceID);

	//----------------------------------------------------------------------------------------
	/// Called directly before each individual brush instance is about to be handled. Between this method and EndSymmetry all the dabs
	/// for each instance will be drawn from one mouse location on the surface of the model to another. This method will be called
	/// every time the user moves their mouse over the object on the screen to indicate that a new batch of dabs is going to be drawn.
	///
	/// Use this method to setup any data on your brush that you might want to access from within your MovePointFunc function via the dab->GetBrush() method.
	/// This method will only be called if SculptBrushParams->EnableBrushAccess(true) has been set.
	/// 
	/// When Multithreading is enable for this brush then this method can be used to reset any data required for each instance. Between this method and EndSymmetry 
	/// the dabs could now be drawn out or order by different threads so no data should be allocated or changed between these 2 calls.
	//----------------------------------------------------------------------------------------
	virtual void StartSymmetry();

	//----------------------------------------------------------------------------------------
	/// Called before all the dabs for a single instance are about to be drawn. After this call all the dabs for just one instance of the brush on the surface
	/// will interpolate between the 2 mouse locations on the object then draw all the dabs for that instance. 
	///
	/// Use this method to setup any data on your brush that you might want to access from within your MovePointFunc function via the dab->GetBrush() method.
	/// This method will only be called if SculptBrushParams->EnableBrushAccess(true) has been set.
	/// 
	/// When Multithreading is enabled no data should be changed on the brush.
	///
	/// @param[in] strokeInstanceID				The ID of the brush instance being drawn.
	//----------------------------------------------------------------------------------------
	virtual void StartStrokeInstanceDabs(Int32 strokeInstanceID);

	//----------------------------------------------------------------------------------------
	/// Called before the MovePointFunc function is called which will then process the dab.
	///
	/// Use this method to setup any data on your brush that you might want to access from within your MovePointFunc function via the dab->GetBrush() method.
	/// This method will only be called if SculptBrushParams->EnableBrushAccess(true) has been set.
	/// 
	/// When Multithreading is enabled no data should be changed on the brush.
	///
	/// @param[in] strokeInstanceID				The ID of the brush instance being drawn.
	//----------------------------------------------------------------------------------------
	virtual void StartDab(Int32 strokeInstanceID);

	//----------------------------------------------------------------------------------------
	/// Called after the MovePointFunc function is called.
	///
	/// This method will only be called if SculptBrushParams->EnableBrushAccess(true) has been set.
	///
	/// @param[in] strokeInstanceID				The ID of the brush instance being drawn.
	//----------------------------------------------------------------------------------------
	virtual void EndDab(Int32 strokeInstanceID);

	//----------------------------------------------------------------------------------------
	/// Called after all the dabs have been drawn for a single instance of the brush.
	///
	/// This method will only be called if SculptBrushParams->EnableBrushAccess(true) has been set.
	///
	/// @param[in] strokeInstanceID				The ID of the brush instance being drawn.
	//----------------------------------------------------------------------------------------
	virtual void EndStrokeInstanceDabs(Int32 strokeInstanceID);

	//----------------------------------------------------------------------------------------
	/// Called after all the dabs for all the instances have been drawn for a single mouse movement on screen.
	///
	/// This method will only be called if SculptBrushParams->EnableBrushAccess(true) has been set.
	/// 
	/// If Multithreading was enabled then you can reset any data for each instance from this method and be ready for the next set of dabs.
	///
	/// @param[in] strokeInstanceID				The ID of the brush instance being drawn.
	//----------------------------------------------------------------------------------------
	virtual void EndSymmetry();

	//----------------------------------------------------------------------------------------
	/// Called on mouse up after a brush stroke. This method is called once for each instance.
	/// Use this method to delete any temporary data you may have allocated during the StartStrokeInstance method.
	/// This method will only be called if SculptBrushParams->EnableBrushAccess(true) has been set.
	/// 
	/// If Multithreading was enabled then you can reset or any data you allocated for each brush instance from within this method.
	///
	/// @param[in] strokeInstanceID				The ID of the brush instance being drawn.
	//----------------------------------------------------------------------------------------
	virtual void EndStrokeInstance(Int32 strokeInstanceID);

	//----------------------------------------------------------------------------------------
	/// Called on mouse up after EndStrokeInstance has been called for each instance.
	/// This method will only be called if SculptBrushParams->EnableBrushAccess(true) has been set.
	/// 
	/// If Multithreading was enabled then you can free any data you allocated for each brush instance from within this method.
	///
	/// @param[in] strokeInstanceID				The ID of the brush instance being drawn.
	//----------------------------------------------------------------------------------------
	virtual void EndStroke();

	//----------------------------------------------------------------------------------------
	/// After a preset has been loaded this method will get called to allow the brush to disable or change any of the loaded settings if required.
	/// @param[in] data				The BaseContainer that contains all the settings for the loaded brush.
	//----------------------------------------------------------------------------------------
	virtual void OverwriteLoadedPresetSettings(BaseContainer &data);

	//----------------------------------------------------------------------------------------
	/// When a brush is reset by the user, in the UI, then it sets it back to its defaults. Afterwards this method is called so you can overwrite any of the standard
	/// brush settings with your own for this brush.
	/// @param[in] doc				The BaseDocument
	/// @param[in] data				The BaseContainer that contains all the settings for the loaded brush.
	//----------------------------------------------------------------------------------------
	virtual void PostInitDefaultSettings(BaseDocument *doc, BaseContainer &data);

	//----------------------------------------------------------------------------------------
	/// Similar to GetDEnabling this method also gets called internally by the sculpting system to check if a feature is enabled or not.
	/// If this method is overridden then make sure to also check the return value of this method directly by calling SculptBrushToolData::GetEnabling(id) at the end.
	/// @param[in] id				The id of the UI element from the .res file.
	//----------------------------------------------------------------------------------------
	virtual Bool GetEnabling(Int32 id); 

	//----------------------------------------------------------------------------------------
	/// PRIVATE!
	///
	/// @param[in] doc							The current document.
	/// @param[in] data							BaseContainer for the brush data.
	/// @param[in] bd								BaseDraw the tool is being used in.
	/// @param[in] win							The Window the tool is being used in.
	/// @param[in] msg							The mouse/tablet message data.
	/// @return									Return True if successful or False if not.
	//----------------------------------------------------------------------------------------
	virtual Bool HandleFillTool(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg);

	//----------------------------------------------------------------------------------------
	/// PRIVATE!
	///
	/// Do something special when the first mouse click is not on the model. 
	/// @param[in] doc							The current document.
	/// @param[in] data							BaseContainer for the brush data.
	/// @param[in] bd								BaseDraw the tool is being used in.
	/// @param[in] win							The Window the tool is being used in.
	/// @param[in] msg							The mouse/tablet message data.
	/// @return									Return True if successful or False if not.
	//----------------------------------------------------------------------------------------
	virtual Bool HandleNonModelPickMode(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg);

	//----------------------------------------------------------------------------------------
	/// PRIVATE!
	///
	/// @param[in] doc							The current document.
	/// @param[in] data							BaseContainer for the brush data.
	/// @param[in] bd								BaseDraw the tool is being used in.
	/// @param[in] bh								BaseDrawHelp.
	/// @param[in] bt								Thread this method is being called from.
	/// @param[in] flags							TOOLDRAWFLAGS for this call.
	/// @return									Return True if successful or False if not.
	//----------------------------------------------------------------------------------------
	virtual Bool DrawNonModelPickMode(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, BaseDrawHelp *bh, BaseThread *bt,TOOLDRAWFLAGS flags);

	//----------------------------------------------------------------------------------------
	/// Override to allow flooding of the entire layer with a specific operation. This method gets called by the default Flood button (which has the function id: MDATA_SCULPTBRUSH_SETTINGS_FLOOD).
	///	Setting SculptBrushParams::SetFloodType() will define what data is being affected by the flood. This can be either SCULPTBRUSHDATATYPE_POINT or SCULPTBRUSHDATATYPE_MASK.
	/// Setting SculptBrushParams::EnableFlood() to True will indicate that this method is available to be used, the Flood button will then be active in the UI.
	/// @param[in] pSculpt						The SculptObject 
	/// @param[in] pLayer						The Layer to Flood
	/// @param[in] brushData					The brushes BaseContainer data.
	/// @param[in] function						ID of the function to apply. The default Flood button has the id MDATA_SCULPTBRUSH_SETTINGS_FLOOD.
	/// @param[in] preview						True when the Flooding is part of an interactive process, such as when the user is moving a slider such as the Interactive Inflate option.
	/// @param[in] customStrength				If not a nullptr then this contains a special strength value that should be used instead of the one from the brushData. This strength is used for interactive flooding along with the preview option.
	/// @param[in] pVertexNormals				If not a nullptr then this contains the vertex normals on the current object. These can be used for interactive flooding along with the preview option.
	//----------------------------------------------------------------------------------------
	virtual void FloodSelectedLayer(SculptObject *pSculpt, SculptLayer *pLayer, const BaseContainer& brushData, Int32 function, Bool preview, Float *customStrength=nullptr, const Vector32 *pVertexNormals=nullptr);

	//----------------------------------------------------------------------------------------
	/// Override to let the system know what draw modes the brush supports.
	/// The system will call this method to check if a draw mode is supported by this brush. If the brush supports all the draw modes then it can just return true.
	/// Otherwise you can specify which draw modes should be enabled by checking each of them.
	/// @param[in] mode			The ID for the DrawMode. For example MDATA_SCULPTBRUSH_SETTINGS_DRAWMODE_LINE.
	/// @return					true if the DrawMode is supported, false if not.
	//----------------------------------------------------------------------------------------
	virtual Bool HasDrawMode(Int32 mode);

	//////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------------------------------------
	/// Floods the entire layer by calling virtual method FloodSelectedLayer(...).
	/// If your brush has different flooding methods (like blur, erase, sharpen etc...) then you can pass in a different flag for the button id.
	/// FloodSelectedLayer is then called with this setting passed as the "function" parameter. 
	/// By default the button is set to the MDATA_SCULPTBRUSH_SETTINGS_FLOOD which is the standard Flood button that the brushes have.
	/// If you use a different button then this method should be called from the Bool Message(BaseDocument* doc, BaseContainer& data, Int32 type, void* t_data) when a button is pushed in the interface.
	/// @param[in] doc			The current document. The BaseDocument passed from Message(...)
	/// @param[in] bd			The viewport that should be used. Usually doc->GetActiveBaseDraw();
	/// @param[in] brushData	The tools data passed from Message(...)
	/// @param[in] button		The ID of the button in the UI to use as the function parameter in the subsequent call to FloodSelectedLayer.
	/// @return					True if successful. False if not.
	//----------------------------------------------------------------------------------------
	Bool Flood(BaseDocument* doc, BaseDraw* bd, const BaseContainer& brushData, Int32 button = MDATA_SCULPTBRUSH_SETTINGS_FLOOD);

	//----------------------------------------------------------------------------------------
	/// Enables a flag so that the brush preview gets drawn.
	//----------------------------------------------------------------------------------------
	void EnableSpecialDrawGizmo();

	//----------------------------------------------------------------------------------------
	/// Clears the flag so that the drawing of the brush preview is not forced.
	//----------------------------------------------------------------------------------------
	void DisableSpecialDrawGizmo();

	//----------------------------------------------------------------------------------------
	/// Tell the brush when the mouse button is down. 
	/// This method should be called from within HandleFillTool() to let the system know that you are polling the mouse for input.
	/// @param[in] value		Set to True to indicate that you are polling the mouse. Set to False when finished.
	//----------------------------------------------------------------------------------------
	void SetMouseDrag(Bool value);

	//----------------------------------------------------------------------------------------
	/// Is a mouse button held down and being dragged.
	/// @return					Return True if the mouse button is down.
	//----------------------------------------------------------------------------------------
	Bool IsMouseDrag();


	//----------------------------------------------------------------------------------------
	/// Cache Sculptable objects in the scene so the tool is ready to use on them. 
	/// This includes SculptObjects (those with a SculptTag) as well as the first selected PolygonObject(without a tag).
	/// It will cache objects that are visible in the currently active viewport.
	/// @param[in] doc		The document to check.
	//----------------------------------------------------------------------------------------
	void CacheObjects(BaseDocument *doc);

	//----------------------------------------------------------------------------------------
	/// Get the number of SculptObjects currently selected. This includes SculptObjects (those with a SculptTag) as well as other internal objects.
	/// Checking if object is of type SCULPT_OBJECT_ID allows the caller to cast to a SculptObject.
	/// @return					Number of SculptObjects selected.
	//----------------------------------------------------------------------------------------
	Int32 GetSelectionCacheCount(); 

	//----------------------------------------------------------------------------------------
	/// Get a cached SculptObject.
	/// @param[in] index		Index of the cachedObject.
	/// @return					The cached Object. If GetType()==SCULPT_OBJECT_ID then it is a SculptObject.
	//----------------------------------------------------------------------------------------
	BaseList2D *GetSelectionCacheObject(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Get the strength of the Brush. 
	/// This is useful when used in the Flood method to get the strength that the flood should apply.
	/// @param[in] original		When True it will return the value as defined in the UI. When False it will be an interpolated value between the current and the next sample point and then also adjusted according to any effector settings such as pen pressure.
	/// @return					The strength value.
	//----------------------------------------------------------------------------------------
	Float GetBrushStrength(Bool original);

	//----------------------------------------------------------------------------------------
	/// Initializes the scaling settings for each sculpt brush according to the distance the camera is from the SculptObject.
	/// Each currently selected SculptObject in the scene will have its scaling information updated.
	/// Plugin developers should never have to call this method. It is used internally when a sculpt tag is first applied to an object to ensure the selected brush works correctly.
	/// @param[in] doc			The document to check for SculptObjects to update.
	//----------------------------------------------------------------------------------------
	void InitZoomScale(BaseDocument *doc);

	//----------------------------------------------------------------------------------------
	/// PRIVATE!
	///
	/// Writes the Brush Preset Data.
	/// @param[in] hf			The HyperFile to write to.
	/// @return					True if successful, false if not.
	//----------------------------------------------------------------------------------------
	Bool WritePresetData(HyperFile *hf);

	//----------------------------------------------------------------------------------------
	/// PRIVATE!
	///
	/// Reads the Brush Preset Data.
	/// @param[in] hf			The HyperFile to write to.
	/// @param[in] level		The version of the plugin that the brush data was written with.
	/// @return					True if successful, false if not.
	//----------------------------------------------------------------------------------------
	Bool ReadPresetData(HyperFile *hf,Int32 level);

	//----------------------------------------------------------------------------------------
	/// PRIVATE!
	///
	/// Writes the Brush Stamp Preset Data.
	/// @param[in] hf			The HyperFile to write to.
	/// @return					True if successful, false if not.
	//----------------------------------------------------------------------------------------
	Bool WriteStampPresetData(HyperFile *hf);

	//----------------------------------------------------------------------------------------
	/// PRIVATE!
	///
	/// Reads the Brush Stamp Preset Data.
	/// @param[in] hf			The HyperFile to write to.
	/// @param[in] level		The version of the plugin that the stamp data was written with.
	/// @return					True if successful, false if not.
	//----------------------------------------------------------------------------------------
	Bool ReadStampPresetData(HyperFile *hf,Int32 level);

	//----------------------------------------------------------------------------------------
	/// PRIVATE!
	//----------------------------------------------------------------------------------------
	Bool WriteSplinePresetData(HyperFile *hf);

	//----------------------------------------------------------------------------------------
	/// PRIVATE!
	//----------------------------------------------------------------------------------------
	Bool ReadSplinePresetData(HyperFile *hf,Int32 level);

	//----------------------------------------------------------------------------------------
	/// PRIVATE!
	///
	/// After preset data has been loaded this method is called to adjust adjust any settings that are specific for this brush. 
	/// @param[in] data				The BaseContainer for the Sculpt Brush (Tool).
	//----------------------------------------------------------------------------------------
	virtual void UpdateSettingsAfterPresetLoad(BaseContainer *data);

	//----------------------------------------------------------------------------------------
	/// Get the BaseBitmap that is being used for the Stamp of the Sculpt Brush.
	/// @return				Returns the Stamp that this brush is using.
	//----------------------------------------------------------------------------------------
	const BaseBitmap *GetStamp();

	//----------------------------------------------------------------------------------------
	/// Get the BaseBitmap that is being used for the Stencil of the Sculpt Brush.
	/// @return				Returns the Stencil that this brush is using.
	//----------------------------------------------------------------------------------------
	const BaseBitmap *GetStencil();
};

struct SculptBrushBaseLibrary : public C4DLibrary
{
	iSculptBrushBase *(*Alloc)();
	void (*Free)(iSculptBrushBase *&p);


	//================================================
	// BrushDabData
	//================================================
	const BaseContainer *	(*brushDabDataGetData)(BrushDabData *dab);
	const SculptObject *	(*brushDabDataGetObject)(BrushDabData *dab);
	const BrushPointData *	(*brushDabDataGetPointData)(BrushDabData *dab);
	const BrushPolyData *	(*brushDabDataGetPolyData)(BrushDabData *dab);
	PolygonObject *			(*brushDabDataGetPolygonObject)(BrushDabData *dab);
	PolygonObject *			(*brushDabDataGetBaseObject)(BrushDabData *dab);
	Int32					(*brushDabDataGetPointCount)(BrushDabData *dab);
	Int32					(*brushDabDataGetPolyCount)(BrushDabData *dab);
	Neighbor *				(*brushDabDataGetNeighbor)(BrushDabData *dab);
	SculptLayer *			(*brushDabDataGetLayer)(BrushDabData *dab);
	const Vector *			(*brushDabDataGetPoints)(BrushDabData *dab);
	const Vector32 *		(*brushDabDataGetOriginalPoints)(BrushDabData *dab);
	Vector					(*brushDabDataGetNormal)(BrushDabData *dab);
	Float					(*brushDabDataGetBrushStrength)(BrushDabData *dab);
	Float					(*brushDabDataGetBrushRadius)(BrushDabData *dab);
	Vector					(*brushDabDataGetMousePos3D)(BrushDabData *dab);
	Vector					(*brushDabDataGetHitPoint)(BrushDabData *dab);
	Vector					(*brushDabDataGetLastHitPoint)(BrushDabData *dab);
	Vector					(*brushDabDataGetEyePoint)(BrushDabData *dab);
	Bool					(*brushDabDataIsMirroredDab)(BrushDabData *dab);
	Int32					(*brushDabDataGetBrushOverride)(BrushDabData *dab);
	BaseDraw *				(*brushDabDataGetBaseDraw)(BrushDabData *dab);
	void					(*brushDabDataGetAveragePointAndNormal)(BrushDabData *dab, Vector &averagePoint, Vector &normal);

	Float					(*brushDabDataGetBrushFalloff)(BrushDabData *dab, Int32 index, Vector32 *pRetStencilColor, Float *pCustomDistance);
	Float					(*brushDabDataGetBrushFalloffFromPos)(BrushDabData *dab, const Vector &pos);
	void					(*brushDabDataOffsetPoint)(BrushDabData *dab, Int32 index, const Vector &offset, Vector32 *pVertexColor, SCULPTOFFSETFLAGS flags);
	Bool					(*brushDabDataIsPreviewDab)(BrushDabData *dab);
	void					(*brushDabDataOffsetPreviewPoint)(BrushDabData *dab, Int32 index, const Vector &offset, SCULPTOFFSETFLAGS flags);
	void					(*brushDabDataApplySmooth)(BrushDabData *dab);
	const Vector32*			(*brushDabDataGetVertexNormals)(BrushDabData *dab);
	Float					(*brushDabDataGetAutoScaleValue)(BrushDabData *dab, Bool noRadius);
	void					(*brushDabDataDirtyAllPoints)(BrushDabData *dab, SCULPTBRUSHDATATYPE type);
	Bool					(*brushDabDataIsPointModified)(BrushDabData *dab, Int32 index);
	Float					(*brushDabDataGetStencilColor)(BrushDabData *dab, const Vector &point, Vector32 *pRetColor, Vector32 *pRetCoords, SAMPLEMODE mode);
	Float					(*brushDabDataGetStampColor)(BrushDabData *dab, const Vector &point, Float distanceFromHitPoint, Vector32 *pRetColor, Vector32 *pRetCoords, SAMPLEMODE mode);
	const BaseBitmap* (*brushDabDataGetStamp)(BrushDabData *dab);
	const BaseBitmap* (*brushDabDataGetStencil)(BrushDabData *dab);
	SculptBrushToolData*	(*brushDabDataGetBrush)(BrushDabData *dab);
	Int32					(*brushDabDataGetStrokeInstanceID)(BrushDabData *dab);
	Bool					(*brushDabDataIsSculptObject)(BrushDabData *dab);

	//================================================
	// iSculptBrushBase
	//================================================
	//Virtual
	Bool (iSculptBrushBase::*InitTool)(BaseDocument* doc, BaseContainer& data, BaseThread* bt, SculptBrushToolData *tool);
	void (iSculptBrushBase::*FreeTool)(BaseDocument* doc, BaseContainer& data, SculptBrushToolData *tool);
	void (iSculptBrushBase::*InitDefaultSettings)(BaseDocument *doc, BaseContainer &data, SculptBrushToolData *tool);
	Bool (iSculptBrushBase::*GetDEnabling)(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc, SculptBrushToolData *tool);
	Bool (iSculptBrushBase::*SetDParameter)(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_SET& flags, SculptBrushToolData *tool);
	Bool (iSculptBrushBase::*GetDDescription)(BaseDocument* doc, BaseContainer& data, Description* description, DESCFLAGS_DESC& flags, SculptBrushToolData *tool);
	Bool (iSculptBrushBase::*Message)(BaseDocument *doc, BaseContainer &data, Int32 type, void *t_data, SculptBrushToolData *tool);
	Bool (iSculptBrushBase::*GetCursorInfo)(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, Float x, Float y, BaseContainer& bc, SculptBrushToolData *tool);
	Bool (iSculptBrushBase::*MouseInput)(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg, SculptBrushToolData *tool);
	Bool (iSculptBrushBase::*KeyboardInput)(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, EditorWindow *win, const BaseContainer &msg, SculptBrushToolData *tool);
	Int32 (iSculptBrushBase::*GetState)(BaseDocument *doc, SculptBrushToolData *tool);
	TOOLDRAW (iSculptBrushBase::*Draw)(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, BaseDrawHelp *bh, BaseThread *bt,TOOLDRAWFLAGS flags, SculptBrushToolData *tool);
	Bool (iSculptBrushBase::*GetDParameter)(BaseDocument* doc, BaseContainer& data, const DescID& id, GeData& t_data, DESCFLAGS_GET& flags, SculptBrushToolData *tool);
	Bool (iSculptBrushBase::*DisplayControl)(BaseDocument* doc, BaseObject* op, BaseObject* chainstart, BaseDraw* bd, BaseDrawHelp* bh, ControlDisplayStruct& cds, SculptBrushToolData *tool);
	Bool (iSculptBrushBase::*InitDisplayControl)(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, const AtomArray* active, SculptBrushToolData *tool);
	void (iSculptBrushBase::*FreeDisplayControl)(SculptBrushToolData *tool);

	void (iSculptBrushBase::*StartStroke)(Int32 strokeCount, const BaseContainer &data);
	void (iSculptBrushBase::*EndStroke)();
	void (iSculptBrushBase::*StartStrokeInstance)(Int32 strokeInstanceID);
	void (iSculptBrushBase::*EndStrokeInstance)(Int32 strokeInstanceID);
	void (iSculptBrushBase::*StartStrokeInstanceDabs)(Int32 strokeInstanceID);
	void (iSculptBrushBase::*EndStrokeInstanceDabs)(Int32 strokeInstanceID);
	void (iSculptBrushBase::*StartSymmetry)();
	void (iSculptBrushBase::*EndSymmetry)();
	void (iSculptBrushBase::*StartDab)(Int32 strokeInstanceID);
	void (iSculptBrushBase::*EndDab)(Int32 strokeInstanceID);

	void (iSculptBrushBase::*OverwriteLoadedPresetSettings)(BaseContainer &data);
	void (iSculptBrushBase::*PostInitDefaultSettings)(BaseDocument *doc, BaseContainer &data);
	Bool (iSculptBrushBase::*GetEnabling)(Int32 id); 
	Bool (iSculptBrushBase::*HandleFillTool)(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg);
	Bool (iSculptBrushBase::*HandleNonModelPickMode)(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg);
	Bool (iSculptBrushBase::*DrawNonModelPickMode)(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, BaseDrawHelp *bh, BaseThread *bt,TOOLDRAWFLAGS flags);
	void (iSculptBrushBase::*FloodSelectedLayer)(SculptObject *pSculpt, SculptLayer *pLayer, const BaseContainer& brushData, Int32 function, Bool preview, Float *customStrength, const Vector32 *pVertexNormals);
	Bool (iSculptBrushBase::*HasDrawMode)(Int32 mode);

	//Non Virtual
	Bool (iSculptBrushBase::*Flood)(BaseDocument* doc, BaseDraw* bd, const BaseContainer& brushData, Int32 button);
	void (iSculptBrushBase::*EnableSpecialDrawGizmo)();
	void (iSculptBrushBase::*DisableSpecialDrawGizmo)();
	void (iSculptBrushBase::*SetMouseDrag)(Bool value);
	Bool (iSculptBrushBase::*IsMouseDrag)();
	void (iSculptBrushBase::*CacheObjects)(BaseDocument *doc);
	Int32 (iSculptBrushBase::*GetSelectionCacheCount)();
	BaseList2D *(iSculptBrushBase::*GetSelectionCacheObject)(Int32 index);
	Float (iSculptBrushBase::*GetBrushStrength)(Bool original);
	void (iSculptBrushBase::*InitZoomScale)(BaseDocument *doc);

	//Presets
	Bool (iSculptBrushBase::*WritePresetData)(HyperFile *hf);
	Bool (iSculptBrushBase::*ReadPresetData)(HyperFile *hf,Int32 level);
	Bool (iSculptBrushBase::*WriteStampPresetData)(HyperFile *hf);
	Bool (iSculptBrushBase::*ReadStampPresetData)(HyperFile *hf,Int32 level);
	Bool (iSculptBrushBase::*WriteSplinePresetData)(HyperFile *hf);
	Bool (iSculptBrushBase::*ReadSplinePresetData)(HyperFile *hf,Int32 level);
	void (iSculptBrushBase::*UpdateSettingsAfterPresetLoad)(BaseContainer *data);

	//Other
	const BaseBitmap *(iSculptBrushBase::*GetStamp)();
	const BaseBitmap *(iSculptBrushBase::*GetStencil)();


	//================================================
	// SculptBrushParams
	//================================================
	SculptBrushParams* (*sculptbrushparamsAlloc)();
	void (*sculptbrushparamsFree)(SculptBrushParams *&params);
	void (*sculptbrushparamsEnableStencil)(SculptBrushParams *pParams, Bool enable);
	void (*sculptbrushparamsEnableStamp)(SculptBrushParams *pParams, Bool enable);
	void (*sculptbrushparamsEnableInvertCheckbox)(SculptBrushParams *pParams, Bool enable);
	void (*sculptbrushparamsEnableBuildup)(SculptBrushParams *pParams, Bool enable);
	void (*sculptbrushparamsEnableNonModelPickMode)(SculptBrushParams *pParams, Bool enable);
	void (*sculptbrushparamsEnableFlood)(SculptBrushParams *pParams, Bool enable);
	void (*sculptbrushparamsEnableToolSpecificSmooth)(SculptBrushParams *pParams, Bool enable);
	void (*sculptbrushparamsEnableMultiThreading)(SculptBrushParams *pParams, Bool enable);
	void (*sculptbrushparamsEnableBrushAccess)(SculptBrushParams *pParams, Bool enable);

	void (*sculptbrushparamsSetFloodType)(SculptBrushParams *pParams, SCULPTBRUSHDATATYPE type);
	void (*sculptbrushparamsSetBrushMode)(SculptBrushParams *pParams, SCULPTBRUSHMODE mode);
	void (*sculptbrushparamsSetFirstHitPointType)(SculptBrushParams *pParams, FIRSTHITPPOINTTYPE type);
	void (*sculptbrushparamsSetUndoType)(SculptBrushParams *pParams, SCULPTBRUSHDATATYPE type);
	void (*sculptbrushparamsSetMovePointFunc)(SculptBrushParams *pParams, Bool (*surfaceMovePointFunc)(BrushDabData *dab));
};

//----------------------------------------------------------------------------------------
/// A helper method used to determine if a tool is a Sculpt Brush or not.
/// @code
/// Int32 tool = GetActiveDocument()->GetAction();
/// Bool isBrush = IsSculptBrush(tool);
/// @endcode
/// @param[in] toolID			The ID of the tool to check
/// @return						Returns True if this tool is a SculptBrush, False if not.
//----------------------------------------------------------------------------------------
Bool IsSculptBrush(Int32 toolID);

//----------------------------------------------------------------------------------------
/// This will return a pointer to the currently selected SculptBrush if one is currently active.
/// Otherwise this will return a nullptr.
/// @param[in] doc			The document to check
//----------------------------------------------------------------------------------------
SculptBrushToolData *GetSelectedSculptBrush(BaseDocument *doc);

#endif	// __LIB_SCULPTBRUSH_H__

/// @}
