/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

/// @addtogroup Sculpting
/// @{
#ifndef _LIB_SCULPT_H_
#define _LIB_SCULPT_H_

#include <stdarg.h>

#include "c4d_library.h"
#include "c4d_baseobject.h"
#include "c4d_basetag.h"

#define LIBRARY_SCULPT	1027453
#define SCULPT_LAYER_ID 1026657
#define SCULPT_FOLDER_ID 1025836
#define SCULPT_OBJECT_ID 1024033
#define SCULPT_LAYERDATA_ID 1024016
#define SCULPT_LAYERSYSTEM_ID 1024014
#define SCULPT_BAKESETTINGS 1027539			//BaseContainer ID for SculptObjects BakeSettings

//----------------------------------------------------------------------------------------
///	SculptLayerData
/// A SculptObject contains a SculptLayerSystem. This LayerSystem can have many layers where each layer has exactly 1 SculptLayerData.
/// There is one exception to this rule, and that is the BaseLayer, which has a SculptLayerData for every subdivision level. 
///
/// A SculptLayerData node contains all the offset data and mask data for that layer at its subdivision level.
//----------------------------------------------------------------------------------------
class SculptLayerData : public BaseList2D
{
private:
	SculptLayerData();
	~SculptLayerData();

public:
	//----------------------------------------------------------------------------------------
	/// Get the level that this layer contains data for.
	/// @return									The subdivision level
	//----------------------------------------------------------------------------------------
	Int32 GetSubdivisionLevel();

	//----------------------------------------------------------------------------------------
	/// Get the number of points on the polygon object that this layer has.
	/// @return									Number of points on the polygon object.
	//----------------------------------------------------------------------------------------
	Int32 GetPointCount();

	//----------------------------------------------------------------------------------------
	/// Get the offset for the given point index on the layer.
	/// @param[in] index						Index of the point on the polygon object
	/// @param[out] offset						The returned offset value for the point
	/// @return									True if data was found or False if there was no data at this point
	//----------------------------------------------------------------------------------------
	Bool GetOffset(Int32 index, Vector &offset);

	//----------------------------------------------------------------------------------------
	/// Sets the offset for the given point. 
	/// Be sure to call SculptObject::Update() after all changes to the offets have been made. This will update the SculptObject display.
	/// You will also need to call SculptObject::UpdateCollision() if you intend on using any of the SculptObject::Hit() methods aftewards.
	/// If this method is going to be called from multiple threads then be sure to call InitializeAllPointData before calling this method.
	/// @param[in] index							Index of the point on the polygon object
	/// @param[out] fullOffset						The offset vector to set.
	//----------------------------------------------------------------------------------------
	void SetOffset(Int32 index, const Vector &fullOffset);

	//----------------------------------------------------------------------------------------
	/// Adds to the existing offset value at the given point.
	/// Be sure to call SculptObject::Update() after all changes to the offets have been made. This will update the SculptObject display.
	/// You will also need to call SculptObject::UpdateCollision() if you intend on using any of the SculptObject::Hit() methods aftewards.
	/// If this method is going to be called from multiple threads then be sure to call InitializeAllPointData before calling this method.
	/// @param[in] index						Index of the point on the polygon object
	/// @param[out] offset						The offset vector to add.
	//----------------------------------------------------------------------------------------
	void AddOffset(Int32 index, const Vector &offset);

	//----------------------------------------------------------------------------------------
	/// Gets the value of the mask at the given point. The value is between 0 and 1 where 0 means no mask and 1 is fully masked.
	/// @param[in] index							Index of the point on the polygon object
	/// @param[out] mask							The mask value returned.
	/// @return										True if there was a mask value at that point, False if there was no mask for that point.
	//----------------------------------------------------------------------------------------
	Bool GetMask(Int32 index, Float32 &mask);

	//----------------------------------------------------------------------------------------
	/// Sets the the mask at the given point. The value will be clamped between 0 and 1. The value is between 0 and 1 where 0 means no mask and 1 is fully masked.
	/// If this method is going to be called from multiple threads then be sure to call InitializeAllMaskData before calling this method.
	/// @param[in] index							Index of the point on the polygon object
	/// @param[in] mask							The value of the mask.
	//----------------------------------------------------------------------------------------
	void SetMask(Int32 index, Float32 mask);

	//----------------------------------------------------------------------------------------
	/// Adds the the mask at the given point. The value will be clamped between 0 and 1. The value is between 0 and 1 where 0 means no mask and 1 is fully masked.
	/// If this method is going to be called from multiple threads then be sure to call InitializeAllMaskData before calling this method.
	/// @param[in] index							Index of the point on the polygon object
	/// @param[in] mask							The amount to add to the existing mask.
	//----------------------------------------------------------------------------------------
	void AddToMask(Int32 index, Float32 mask);

	//----------------------------------------------------------------------------------------
	/// Check to see if this Layer has a mask applied to it.
	/// @return									True if there is mask data otherwise False.
	//----------------------------------------------------------------------------------------
	Bool HasMask();

	//----------------------------------------------------------------------------------------
	/// Clears all the mask data for this layer
	//----------------------------------------------------------------------------------------
	void ClearMask();

	//----------------------------------------------------------------------------------------
	/// Clears all the offsets for this layer
	//----------------------------------------------------------------------------------------
	void ClearLayer();

	//----------------------------------------------------------------------------------------
	/// Make sure all the data has been allocated to store all the point data.
	/// If you are going to be calling SetOffset or AddOffset from multiple threads then the data needs to be initialized before these calls are made.
	/// If you are not using multiple threads the calls to SetOffset and AddOffset will only allocate data if required.
	//----------------------------------------------------------------------------------------
	void InitializeAllPointData();

	//----------------------------------------------------------------------------------------
	/// Make sure all the data has been allocated to store all the mask data.
	/// If you are going to be calling SetMask or AddToMask from multiple threads then the data needs to be initialized before these calls are made.
	/// If you are not using multiple threads the calls to SetMask and AddToMask will only allocate data if required.
	//----------------------------------------------------------------------------------------
	void InitializeAllMaskData();

	//----------------------------------------------------------------------------------------
	/// Marks the point so that any modifications to it can be undone.
	/// Must be called after SculptObject::StartUndo().
	/// This method can not be called from multiple threads.
	//----------------------------------------------------------------------------------------
	void TouchPointForUndo(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Marks the masked point so that any modifications to the mask can be undone.
	/// Must be called after SculptObject::StartUndo().
	/// This method can not be called from multiple threads.
	//----------------------------------------------------------------------------------------
	void TouchMaskForUndo(Int32 index);
};


//----------------------------------------------------------------------------------------
///	SculptLayerBase
//----------------------------------------------------------------------------------------
class SculptLayerBase : public BaseList2D
{
private:
	SculptLayerBase();
	~SculptLayerBase();

public:

	//----------------------------------------------------------------------------------------
	/// Select the layer. This will only work if the subdivision level is at the same level as this layer.
	/// @return					True if the layer was selected
	//----------------------------------------------------------------------------------------
	Bool Select();

	//----------------------------------------------------------------------------------------
	/// Check if the layer is currently visible on the sculpt object.
	/// @return					True if visible, False if invisible
	//----------------------------------------------------------------------------------------
	Bool IsVisible();

	//----------------------------------------------------------------------------------------
	/// Sets the visibility of this layer on the sculpt object.
	/// @param[in] value		The visibility state
	//----------------------------------------------------------------------------------------
	void SetVisible(Bool value);

	//----------------------------------------------------------------------------------------
	/// Check if the layer is currently locked on the sculpt object.
	/// @return					True if locked, False if unlocked
	//----------------------------------------------------------------------------------------
	Bool IsLocked();

	//----------------------------------------------------------------------------------------
	/// Sets the locked status of the layer on the sculpt object.
	/// @param[in] value		The locked state
	//-------------------------------------------------------------------------------------
	void SetLocked(Bool value);

	//----------------------------------------------------------------------------------------
	/// Get the currents strength of the layer.
	/// @return					The strength value.
	//----------------------------------------------------------------------------------------
	Float GetStrength();

	//----------------------------------------------------------------------------------------
	/// Sets the strength of the layer on the sculpt object.
	/// @param[in] value		The strength value to set
	//----------------------------------------------------------------------------------------
	void SetStrength(Float value);
};


//----------------------------------------------------------------------------------------
///	A Sculpt Layer can contain one or more SculptLayerData children.
//----------------------------------------------------------------------------------------
class SculptLayer : public SculptLayerBase
{
private:
	SculptLayer();
	~SculptLayer();

public:
	//----------------------------------------------------------------------------------------
	/// Get the first layer data for this layer, the BaseLayer will have more than one, other layers only have 1.
	/// @return					The SculptLayerData
	//----------------------------------------------------------------------------------------
	SculptLayerData *GetFirstSculptLayerData();

	//----------------------------------------------------------------------------------------
	/// Get the currently used layer data. In the case of the BaseLayer it will get the data for the current subdivision level. 
	/// For all other layers it will return the same as GetFirstSculptLayerData().
	/// @return					The SculptLayerData
	//----------------------------------------------------------------------------------------
	SculptLayerData *GetCurrentSculptLayerData();

	//----------------------------------------------------------------------------------------
	/// Get the number of points this layer has. The point count will be the same as the number of points on the PolygonObject
	/// for the subdivision level that this layer is at.
	/// @return					The number of points
	//----------------------------------------------------------------------------------------
	Int32 GetPointCount();								

	//----------------------------------------------------------------------------------------
	/// Get the offset value for this point on the layer.
	/// This method will get the correct SculptLayerData for this layer and call the corresponding method for it.
	/// @param[in] index		The index of the point on the layer
	/// @param[out] offset		The offset of the point
	/// @return					True if there was offset data for the point. False if no offset data was allocated at this point location
	//----------------------------------------------------------------------------------------
	Bool GetOffset(Int32 index, Vector &offset);

	//----------------------------------------------------------------------------------------
	/// Sets the offset Vector for the given point on the layer.
	/// This method will get the correct SculptLayerData for this layer and call the corresponding method for it.
	/// Be sure to call SculptObject::Update() after all changes to the offets have been made. This will update the SculptObject display.
	/// You will also need to call SculptObject::UpdateCollision() if you intend on using any of the SculptObject::Hit() methods aftewards.
	/// If this method is going to be called from multiple threads then be sure to call InitializeAllPointData before calling this method.
	/// @param[in] index		The index of the point on the layer
	/// @param[in] fullOffset	The offset of the point
	//----------------------------------------------------------------------------------------
	void SetOffset(Int32 index, const Vector &fullOffset);

	//----------------------------------------------------------------------------------------
	/// Add an offset Vector to the existing offset for the given point on the layer.
	/// This method will get the correct SculptLayerData for this layer and call the corresponding method for it.
	/// Be sure to call SculptObject::Update() after all changes to the offets have been made. This will update the SculptObject display.
	/// You will also need to call SculptObject::UpdateCollision() if you intend on using any of the SculptObject::Hit() methods aftewards.
	/// If this method is going to be called from multiple threads then be sure to call InitializeAllPointData before calling this method.
	/// @param[in] index		The index of the point on the layer
	/// @param[in] offset		The offset of the point
	//----------------------------------------------------------------------------------------
	void AddOffset(Int32 index, const Vector &offset);

	//----------------------------------------------------------------------------------------
	/// Get the mask value for the point (between 0 and 1).
	/// This method will get the correct SculptLayerData for this layer and call the corresponding method for it.
	/// @param[in] index		The index of the point on the layer
	/// @param[in] mask			The mask value for the given point
	/// @return					True if there was mask data for the point. False if no mask data was allocated at this point location
	//----------------------------------------------------------------------------------------
	Bool GetMask(Int32 index, Float32 &mask);

	//----------------------------------------------------------------------------------------
	/// Set the mask value for the point (between 0 and 1).
	/// This method will get the correct SculptLayerData for this layer and call the corresponding method for it.
	/// If this method is going to be called from multiple threads then be sure to call InitializeAllMaskData before calling this method.
	/// @param[in] index		The index of the point on the layer
	/// @param[in] mask			The mask value for the given point.
	//----------------------------------------------------------------------------------------
	void SetMask(Int32 index, Float32 mask);

	//----------------------------------------------------------------------------------------
	/// Add to the existing mask value at this point (between 0 and 1).
	/// This method will get the correct SculptLayerData for this layer and call the corresponding method for it.
	/// If this method is going to be called from multiple threads then be sure to call InitializeAllMaskData before calling this method.
	/// @param[in] index		The index of the point on the layer
	/// @param[in] mask			The value to add to the mask.
	//----------------------------------------------------------------------------------------
	void AddToMask(Int32 index, Float32 mask);

	//----------------------------------------------------------------------------------------
	/// Clear the mask data for the layer.
	/// This method will get the correct SculptLayerData for this layer and call the corresponding method for it.
	//----------------------------------------------------------------------------------------
	void ClearMask();

	//----------------------------------------------------------------------------------------
	/// Clear all the offset data for this layer.
	/// This method will get the correct SculptLayerData for this layer and call the corresponding method for it.
	//----------------------------------------------------------------------------------------
	void ClearLayer();

	//----------------------------------------------------------------------------------------
	/// Make sure all the data has been allocated to store all the point data.
	/// If you are going to be calling SetOffset or AddOffset from multiple threads then the data needs to be initialized before these calls are made.
	/// If you are not using multiple threads the calls to SetOffset and AddOffset will only allocate data if required.
	//----------------------------------------------------------------------------------------
	void InitializeAllPointData();

	//----------------------------------------------------------------------------------------
	/// Make sure all the data has been allocated to store all the mask data.
	/// If you are going to be calling SetMask or AddToMask from multiple threads then the data needs to be initialized before these calls are made.
	/// If you are not using multiple threads the calls to SetMask and AddToMask will only allocate data if required.
	//----------------------------------------------------------------------------------------
	void InitializeAllMaskData();

	//----------------------------------------------------------------------------------------
	/// Marks the point so that any modifications to it can be undone.
	/// Must be called after SculptObject::StartUndo().
	/// This method can not be called from multiple threads.
	//----------------------------------------------------------------------------------------
	void TouchPointForUndo(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Marks the masked point so that any modifications to the mask can be undone.
	/// Must be called after SculptObject::StartUndo().
	/// This method can not be called from multiple threads.
	//----------------------------------------------------------------------------------------
	void TouchMaskForUndo(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Check if this layer is the BaseLayer in which case it will have more than one ScultLayerData children.
	/// @return					True if this layer is the BaseLayer, False if it is a regular layer.
	//----------------------------------------------------------------------------------------
	Bool IsBaseLayer();

	//----------------------------------------------------------------------------------------
	/// Check if this layer has a mask at the current subdivision level.
	/// This method will get the correct SculptLayerData for this layer and call the corresponding method for it.
	/// @return					True if there is a mask, False if there is no mask.
	//----------------------------------------------------------------------------------------
	Bool HasMask();

	//----------------------------------------------------------------------------------------
	/// Check if the mask is enabled for this layer at the current subdivision level.
	/// This method will get the correct SculptLayerData for this layer and call the corresponding method for it.
	/// @return					True if mask is enabled, False if the mask is disabled.
	//----------------------------------------------------------------------------------------
	Bool IsMaskEnabled();

	//----------------------------------------------------------------------------------------
	/// Sets the mask enabled flag for the current layer data at this current subdivision level.
	/// This method will get the correct SculptLayerData for this layer and call the corresponding method for it.
	/// @param[in] value		The state of the mask
	//----------------------------------------------------------------------------------------
	void SetMaskEnabled(Bool value);
};

//----------------------------------------------------------------------------------------
/// A SculptFolder can contain many SculptLayers or other SculptFolders as children.
//----------------------------------------------------------------------------------------
class SculptFolder : public SculptLayerBase
{
private:
	SculptFolder();
	~SculptFolder();
};


//----------------------------------------------------------------------------------------
/// A SculptLayerSystem has one or more SculptLayer or SculptFolders as children. 
/// - SculptObject
///		- SculptLayerSystem
///			- SculptLayer (if this is the BaseLayer it will have more than one SculptLayerData as children, one for each subdivision level
///				- SculptLayerData (Level 0)
///				- SculptLayerData (Level 1)
///				- SculptLayerData (Level 2)...
///			- SculptFolder
///				- SculptLayer (Other layers have one SculptLayerData for the subdivision level that the layer was created at).
///					- SculptLayerData (Level 2)
///			- SculptLayer
///				- SculptLayerData (Level 1)
///			- SculptLayer
///				- SculptLayerData (Level 2)
//----------------------------------------------------------------------------------------
class SculptLayerSystem : public BaseList2D
{
private:
	SculptLayerSystem();
	~SculptLayerSystem();
};

//----------------------------------------------------------------------------------------
/// This data structure is filled out by the SculptObject::Hit(...) methods.
//----------------------------------------------------------------------------------------
struct SculptHitData
{
	Vector localHitPoint;			// Location of the hitpoint on the surface of the object in the objects local coordinate system
	Vector32 localHitNormal;		// The Normal of the hitpoint on the surface of the object in the objects local coordinate system
	Int32 selectedPolygon;			// The polygon that was hit
	Float distance;					// The distance from rayp
	Bool backface;					// The hit polygon was a backfacing polygon
};

//----------------------------------------------------------------------------------------
/// A SculptObject what you use to interact with the data referenced by a SculptTag. 
/// The SculptTag on a PolygonObject references a SculptObject that is stored in a SceneHook
/// within the document. When the SculptTag is deleted this SculptObject is also deleted.
//----------------------------------------------------------------------------------------
class SculptObject : public BaseList2D
{
private:
	SculptObject();
	~SculptObject();

public:
	//----------------------------------------------------------------------------------------
	/// Get the number of Subdivisions that this SculptObject currently has. IE how many times it has been subdivided by the user.
	/// @return				The number of subdivision levels.
	//----------------------------------------------------------------------------------------
	Int32 GetSubdivisionCount();

	//----------------------------------------------------------------------------------------
	/// Get a copy of the SculptObject at a specific subdivision level. The caller owns the returned PolygonObject. 
	/// The returned object will not contain a copy of the SculptTag.
	/// @param[in] subdivisionLevel				The Subdivision Level which to copy the PolyonObject from.
	/// @param[in] includeTopLevels				When set to True this will include all the detail from any layers that are above subdivisionLevel that was specified. When False this will only return the sculpting data for all layers up to and including the subdivionLevel specified.	
	/// @return									The PolygonObject for the subdivision level. The caller owns this object.
	//----------------------------------------------------------------------------------------
	PolygonObject *GetPolygonCopy(Int32 subdivisionLevel, Bool includeTopLevels=true); 

	//----------------------------------------------------------------------------------------
	/// Get the original PolygonObject that the SculptTag is applied to. 
	/// @return									The PolygonObject that the SculptTag is applied to. The document owns this object.
	//----------------------------------------------------------------------------------------
	PolygonObject *GetOriginalObject(); 

	//----------------------------------------------------------------------------------------
	/// From a viewport cast a ray, in screen space, onto the SculptObject and return any data if the ray hits the object.
	/// This will return the closest hit point if multiple intersections are found. If backfaces is enabled, and the back facing hit point is closer than the front hit point, then it will be returned.
	/// To use the hit functions the mesh must be unfrozen and both NeedCollisionUpdate(true) and UpdateCollision() should be called to initialize the collision data.
	/// @param[in] bd							The BaseDraw that the user is casting the ray from
	/// @param[in] mx							The x coordinate (IE mouse coordinate) in screen space
	/// @param[in] my							The y coordinate (IE mouse coordinate) in screen space
	/// @param[in] backfaces					Allow back facing polygons to be hit tested.
	/// @param[out] hitData						The intersection data will be filled out if the object was hit
	/// @return									True if the SculptObject was hit, False if not.
	//----------------------------------------------------------------------------------------
	Bool Hit(BaseDraw* bd, Float mx, Float my, Bool backfaces, SculptHitData  &hitData);

	//----------------------------------------------------------------------------------------
	/// Given a ray in object space do a hit intersection against the SculptObject and return any data if the ray hits the object.
	/// This will return the closest hit point if multiple intersections are found. If backfaces is enabled, and the back facing hit point is closer than the front hit point, then it will be returned.
	/// To use the hit functions the mesh must be unfrozen and both NeedCollisionUpdate(true) and UpdateCollision() should be called to initialize the collision data.
	/// @param[in] rayp							The starting position of the ray in object space.
	/// @param[in] rayv							The direction the ray is pointing.
	/// @param[in] backfaces					Allow back facing polygons to be hit tested.
	/// @param[out] hitData						The intersection data will be filled out if the object was hit.
	/// @return									True if the SculptObject was hit, False if not.
	//----------------------------------------------------------------------------------------
	Bool Hit(const Vector &rayp, const Vector &rayv, Bool backfaces, SculptHitData  &hitData);
 

	//----------------------------------------------------------------------------------------
	/// Gets the number of polygons at the current subdivision level.
	/// @return									The number of polygons
	//----------------------------------------------------------------------------------------
	Int32	GetPolygonCount();

	//----------------------------------------------------------------------------------------
	/// Gets the number of points at the current subdivision level.
	/// @return									The number of points
	//----------------------------------------------------------------------------------------
	Int32	GetPointCount();

	//----------------------------------------------------------------------------------------
	/// Gets the currently selected layer, or folder, selected for this SculptObject.
	/// @return									The sculptlayer or folder.
	//----------------------------------------------------------------------------------------
	SculptLayerBase	*GetCurrentLayer();

	//----------------------------------------------------------------------------------------
	/// Gets the current subdivision level that the SculptObject is currently at.
	/// @return									The subdivision level
	//----------------------------------------------------------------------------------------
	Int32	GetCurrentLevel();

	//----------------------------------------------------------------------------------------
	/// Gets the amount of memory currently used for this SculptObject. This does not include any memory used by OpenGL.
	/// @return									The memory used in bytes.
	//----------------------------------------------------------------------------------------
	UInt32	GetMemoryUsage();

	//----------------------------------------------------------------------------------------
	/// Creates a new layer on the SculptObject at the current subdivision level.
	/// @return									The SculptLayer added. The SculptObject owns the layer.
	//----------------------------------------------------------------------------------------
	SculptLayer *AddLayer();

	//----------------------------------------------------------------------------------------
	/// Creates a new folder for the SculptObject. 
	/// @return									The folder added. The SculptObject owns the folder.
	//----------------------------------------------------------------------------------------
	SculptFolder *AddFolder();

	//----------------------------------------------------------------------------------------
	/// Deletes the currently selected layer (or folder) on the sculpt object (as specified in the Sculpt Layer Manager UI).
	/// If the currently selected layer is a folder then it will only delete the folder if all the layers
	/// that are contained in that folder are at the same subdivision level as the current subdivion level. 
	/// @return									True if the layer was deleted, False if not.
	//----------------------------------------------------------------------------------------
	Bool DeleteSelectedLayer();

	//----------------------------------------------------------------------------------------
	/// Recomposites all the layers and updates the SculptObject.
	//----------------------------------------------------------------------------------------
	void Update();

	//----------------------------------------------------------------------------------------
	/// Get the vertex normals for the PolygonObject at its current subdivision level.
	/// @return									The vertex normals.
	//----------------------------------------------------------------------------------------
	const Vector32 *GetVertexNormals();

	//----------------------------------------------------------------------------------------
	/// Get read only access to the points that will be used for the PolygonObject at the current subdivision level.
	/// @return									The points.
	//----------------------------------------------------------------------------------------
	const Vector *GetPointR();

	//----------------------------------------------------------------------------------------
	/// Get write access to the points on that will be used for the display of the PolygonObject at the current subdivision level in the viewport. 
	/// This method should only ever be used with the call OffsetPoint, which should only ever be called from the SculptBrushToolData::FloodSelectedLayer method of a Sculpt Brush
	/// which gets called during an InteractiveFlood user interation.
	/// @return									The points.
	//----------------------------------------------------------------------------------------
	Vector *GetPointW();

	//----------------------------------------------------------------------------------------
	/// Subdivide the SculptObject to the next level.
	/// This method will only work if the sculpt object is already at the top most level and the memory limit (as specified in the preferences) has not been exceeded and also only if there is enough memory on the users computer to successfully do the subdivision.
	/// @return									True if the object was successfully subdivided, False if it was not able to subdivide.
	//----------------------------------------------------------------------------------------
	Bool	Subdivide();

	//----------------------------------------------------------------------------------------
	/// Increase the subdivision level to the next highest level. If it is already at the top subdivision level then it will do nothing.
	/// @return									True if it was able go up a level, False if not.
	//----------------------------------------------------------------------------------------
	Bool	IncreaseSubdivisionLevel();

	//----------------------------------------------------------------------------------------
	/// Decrease the subdivision level to the down one level. If it is already at level 0 then it will do nothing.
	/// @return									True if it was able go down a level, False if not.
	//----------------------------------------------------------------------------------------
	Bool	DecreaseSubdivisionLevel();


	//----------------------------------------------------------------------------------------
	/// Gets the first layer under the SculptLayerSystem. This is usually the BaseLayer.
	/// @return									The Layer
	//----------------------------------------------------------------------------------------
	SculptLayerBase *GetFirstLayer();

	//----------------------------------------------------------------------------------------
	/// Gets the BaseLayer, which is the special layer that has multiple SculptLayerData children, one for each subdivison level, that allows the user to sculpt on while at any subdivision level.
	/// @return									The BaseLayer
	//----------------------------------------------------------------------------------------
	SculptLayer		*GetBaseLayer();

	//----------------------------------------------------------------------------------------
	/// Gets the LayerSystem that contains all the layers. This is a child node of the SculptObject.
	/// @return									The SculptLayerSystem.
	//----------------------------------------------------------------------------------------
	SculptLayerSystem *GetLayerSystem();

	//----------------------------------------------------------------------------------------
	/// Has the SculptObject been frozen. This is also able to be set on the SculptTag in the Cinema4D UI.
	/// @return									True if the object was frozen, False if not.
	//----------------------------------------------------------------------------------------
	Bool	IsFrozen();

	//----------------------------------------------------------------------------------------
	/// Sets the Frozen state of the SculptObject. In the UI this is showin in the SculpTag.
	/// When the object is frozen no changes to the SculptObject or any of its layers are allowed.
	///
	/// PhongTag:
	/// If the PolygonObject has a PhongTag it will also become active when the SculptObject is Frozen. 
	/// When not Frozen then SculptObject uses its own internal Vertex Normals and disables the PhongTag on the PolygonObject.
	///
	/// @param[in] value						The state.
	//----------------------------------------------------------------------------------------
	void	SetFrozen(Bool value);

	//----------------------------------------------------------------------------------------
	/// Is this object allowed to be deformed by any deformers. This is also able to be set on the SculptTag in the Cinema4D UI.
	/// This option on works if the object is also Frozen. When both these options are enabled any deformers, that are children of the PolygonObject that the SculptTag is applied to,
	/// will be able to deform the object in the viewport. 
	/// @return									True if the object was frozen, False if not.
	//----------------------------------------------------------------------------------------
	Bool	GetAllowDeformations();

	//----------------------------------------------------------------------------------------
	/// Sets the AllowDeformations checkbox thereby allowing any deformers to have an effect on the display of the SculptObject, as long as it is also frozen. 
	/// This option can also be found in the SculptTag UI.
	/// @param[in] value							State of the Allow Deformation flag.
	//----------------------------------------------------------------------------------------
	void	SetAllowDeformations(Bool value);

	//----------------------------------------------------------------------------------------
	/// Update any collision data after any changes to the SculptLayer Offsets have been made. 
	/// This is required before you call the Hit() methods.
	//----------------------------------------------------------------------------------------
	void	UpdateCollision();

	//----------------------------------------------------------------------------------------
	/// Tell the SculptObject that it requires a collision Update before the user tries to use any of the SculptTools. Then next time a user tries to use
	/// a tool it will first call UpdateCollision() to ensure that the Hit() calls will be correct.
	/// @param[in] fullUpdate						Set to True to update the full mesh, this is not always required.
	//----------------------------------------------------------------------------------------
	void	NeedCollisionUpdate(Bool fullUpdate=false);		

	//----------------------------------------------------------------------------------------
	/// Offset a point on the layer when when the interactive flood operation has finished. This is called on the SculptObject by the SculptingTools.
	/// This method should only be called from within SculptBrushToolData::FloodSelectedLayer().
	/// @param[in] pLayer							The SculptLayer that the brush is operation on.
	/// @param[in] pPoints						The points from the call to GetPoints() which are used to directly effect the drawing of the SculptObject in the viewport
	/// @param[in] useMask						Should the operation respect the Mask on the Layer or not.
	/// @param[in] strength						The strength of the SculptLayer.
	/// @param[in] index							The index of the point on the PolygonObject for the current subdivision level.
	/// @param[in] offset							The offset to apply to the preview layer
	/// @param[in] respectLayerStrength			Should it respect the strength of the layer or ignore it updating the mesh on screen.
	//----------------------------------------------------------------------------------------
	void	OffsetPoint(SculptLayer *pLayer, Vector *pPoints, Bool useMask, Float strength, Int32 index, const Vector &offset, Bool respectLayerStrength=false);

	//----------------------------------------------------------------------------------------
	/// Adds to the value of the offset on the preview layer when used to do interactive flood updates on the SculptObject by the SculptingTools.
	/// This method should only be called from within SculptBrushToolData::FloodSelectedLayer()
	/// @param[in] pLayer							The SculptLayer that the brush is operation on.
	/// @param[in] useMask						Should the operation respect the Mask on the Layer or not.
	/// @param[in] strength						The strength of the SculptLayer.
	/// @param[in] index							The index of the point on the PolygonObject for the current subdivision level.
	/// @param[in] offset							The offset to apply to the preview layer
	/// @param[in] respectLayerStrength			Should it respect the strength of the layer or ignore it updating the mesh on screen.
	//----------------------------------------------------------------------------------------
	void	OffsetPreviewPoint(SculptLayer *pLayer, Bool useMask, Float strength, Int32 index, const Vector &offset, Bool respectLayerStrength=false);

	//----------------------------------------------------------------------------------------
	/// Sets the value of the offset on the preview layer when used to do interactive flood updates on the SculptObject by the SculptingTools.
	/// This method should only be called from within SculptBrushToolData::FloodSelectedLayer()
	/// @param[in] pLayer							The SculptLayer that the brush is operation on.
	/// @param[in] useMask						Should the operation respect the Mask on the Layer or not.
	/// @param[in] strength						The strength of the SculptLayer.
	/// @param[in] index							The index of the point on the PolygonObject for the current subdivision level.
	/// @param[in] offset							The offset to set on the preview layer
	/// @param[in] respectLayerStrength			Should it respect the strength of the layer or ignore it updating the mesh on screen.
	//----------------------------------------------------------------------------------------
	void	SetPreviewPoint(SculptLayer *pLayer, Bool useMask, Float strength, Int32 index, const Vector &offset, Bool respectLayerStrength=false);


	//----------------------------------------------------------------------------------------
	/// Call before any calls to AddOffset, SetOffset, AddToMask or SetMask if you wish it to be undone.
	/// This will only work if you are only making changes to a single layer. Changes to multiple layers or layers at different levels is not allowed.
	/// You must be at the current subdivision level of the layer being changed for these calls to work properly.
	/// EndUndo() must be called after all calls to the above functions have been done.
	/// This must NEVER be called by a SculptBrush during a brush stroke.
	//----------------------------------------------------------------------------------------
	void	StartUndo();

	//----------------------------------------------------------------------------------------
	/// Must be called after StartUndo() once all the point and masks have been changed on the layers.
	/// This must NEVER be called by a SculptBrush during a brush stroke.
	//----------------------------------------------------------------------------------------
	void	EndUndo();

	//----------------------------------------------------------------------------------------
	/// Smooth the sculpt object and apply the offsets to the currently selected layer.
	/// @param[in] count				The number of times to run the smooth algorithm
	/// @param[in] respectMask			If True it will not smooth any masked out points, if False it will apply it to every point.
	//----------------------------------------------------------------------------------------
	void	Smooth(Int32 count, Bool respectMask);

};

//----------------------------------------------------------------------------------------
/// When an PolygonObject is made sculptable it will contain a SculptTag. 
/// Each SculptTag references a SculptObject in the Document. This SculptObject contains
/// all the layers and offsets used by the Sculpt Tools.
//----------------------------------------------------------------------------------------
class SculptTag : public BaseTag
{
private:
	SculptTag();
	~SculptTag();
public:
	//----------------------------------------------------------------------------------------
	// Create a new SculptTag.
	/// This does not usually need to be used. Instead use the helper method MakeSculptObject().
	/// @return									The new SculptTag
	//----------------------------------------------------------------------------------------
	static SculptTag *Alloc() { return (SculptTag*)BaseTag::Alloc(Tsculpt); }

	//----------------------------------------------------------------------------------------
	/// Free the SculptTag.
	/// @param[in] pTag							The SculptTag to free.
	//----------------------------------------------------------------------------------------
	static void Free(SculptTag *&pTag) { BaseTag *tag=pTag; BaseTag::Free(tag); pTag=nullptr; }

	//----------------------------------------------------------------------------------------
	/// Get the SculptObject for this SculptTag.
	/// @return									The SculptObject that this tag references.
	//----------------------------------------------------------------------------------------
	SculptObject *GetSculptObject();
};

struct SculptLibrary : public C4DLibrary
{
	//SculptLayerData R14
	Int32						(*sculptlayerdataGetSubdivisionLevel)(SculptLayerData *layerData);
	Int32						(*sculptlayerdataGetPointCount)(SculptLayerData *layerData);
	Bool						(*sculptlayerdataGetOffset)(SculptLayerData *layerData, Int32 index, Vector &offset);
	void						(*sculptlayerdataSetOffset)(SculptLayerData *layerData, Int32 index, const Vector &fullOffset);
	void						(*sculptlayerdataAddOffset)(SculptLayerData *layerData, Int32 index, const Vector &offset);
	Bool						(*sculptlayerdataGetMask)(SculptLayerData *layerData, Int32 index, Float32 &mask);
	void						(*sculptlayerdataSetMask)(SculptLayerData *layerData, Int32 index, Float32 mask);
	void						(*sculptlayerdataAddToMask)(SculptLayerData *layerData, Int32 index, Float32 mask);
	Bool						(*sculptlayerdataSelect)(SculptLayerData *layerData);
	Bool						(*sculptlayerdataHasMask)(SculptLayerData *layerData);

	//SculptLayerBase R14
	Bool						(*sculptlayerbaseSelect)(SculptLayerBase *layer);
	Bool						(*sculptlayerbaseIsVisible)(SculptLayerBase *layer);
	void						(*sculptlayerbaseSetVisible)(SculptLayerBase *layer, Bool value);
	Bool						(*sculptlayerbaseIsLocked)(SculptLayerBase *layer);
	void						(*sculptlayerbaseSetLocked)(SculptLayerBase *layer, Bool value);
	Float						(*sculptlayerbaseGetStrength)(SculptLayerBase *layer);
	void						(*sculptlayerbaseSetStrength)(SculptLayerBase *layer, Float value);

	//SculptLayer R14
	SculptLayerData*			(*sculptlayerGetFirstSculptLayerData)(SculptLayer *layer);
	Int32						(*sculptlayerGetPointCount)(SculptLayer *layer);
	Bool						(*sculptlayerGetOffset)(SculptLayer *layer, Int32 index, Vector &offset);
	void						(*sculptlayerSetOffset)(SculptLayer *layer, Int32 index, const Vector &fullOffset);
	void						(*sculptlayerAddOffset)(SculptLayer *layer, Int32 index, const Vector &offset);
	Bool						(*sculptlayerGetMask)(SculptLayer *layer, Int32 index, Float32 &mask);
	void						(*sculptlayerSetMask)(SculptLayer *layer, Int32 index, Float32 mask);
	void						(*sculptlayerAddToMask)(SculptLayer *layer, Int32 index, Float32 mask);
	Bool						(*sculptlayerIsBaseLayer)(SculptLayer *layer);
	Bool						(*sculptlayerHasMask)(SculptLayer *layer);
	Bool						(*sculptlayerIsMaskEnabled)(SculptLayer *layer);
	void						(*sculptlayerSetMaskEnabled)(SculptLayer *layer, Bool value);

	//SculptObject R14
	Int32						(*sculptobjGetSubdivisionCount)(SculptObject *obj);
	PolygonObject*				(*sculptobjGetPolygonCopy)(SculptObject *obj,Int32 subdivisionLevel,Bool includeTopLevels);
	PolygonObject*				(*sculptobjGetOriginalObject)(SculptObject *obj);
	Int32						(*sculptobjGetPolygonCount)(SculptObject *obj);
	SculptLayerBase*			(*sculptobjGetCurrentLayer)(SculptObject *obj);
	Int32						(*sculptobjGetCurrentLevel)(SculptObject *obj);
	UInt32						(*sculptobjGetMemoryUsage)(SculptObject *obj);
	Bool						(*sculptobjHitScreenEx)(SculptObject *obj,BaseDraw* bd, Float mx, Float my, SculptHitData &hitData);
	Bool						(*sculptobjHitObjectEx)(SculptObject *obj,const Vector &rayp, const Vector &rayv, SculptHitData &hitData);
	SculptLayer*				(*sculptobjAddLayer)(SculptObject *obj);
	SculptFolder*				(*sculptobjAddFolder)(SculptObject *obj);
	Bool						(*sculptobjDeleteSelectedLayer)(SculptObject *obj);
	void						(*sculptobjUpdate)(SculptObject *obj);
	Bool						(*sculptobjSubdivide)(SculptObject *obj);
	Bool						(*sculptobjIncreaseSubdivisionLevel)(SculptObject *obj);
	Bool						(*sculptobjDecreaseSubdivisionLevel)(SculptObject *obj);
	SculptLayerBase*			(*sculptobjGetFirstLayer)(SculptObject *obj);
	SculptLayer*				(*sculptobjGetBaseLayer)(SculptObject *obj);
	Bool						(*sculptobjIsFrozen)(SculptObject *obj);
	void						(*sculptobjSetFrozen)(SculptObject *obj, Bool value);
	void						(*sculptobjUpdateCollision)(SculptObject *obj);
	void						(*sculptobjNeedCollisionUpdate)(SculptObject *obj, Bool fullUpdate);
	Bool						(*sculptobjGetAllowDeformations)(SculptObject *obj);
	void						(*sculptobjSetAllowDeformations)(SculptObject *obj, Bool value);

	//SculptTag R14
	SculptObject*				(*sculpttagGetSculptObject)(SculptTag *tag);

	//SculptLayerData R15
	void						(*sculptlayerdataClearMask)(SculptLayerData *layerData);
	void						(*sculptlayerdataClearLayer)(SculptLayerData *layerData);
	void						(*sculptlayerdataInitializeAllPointData)(SculptLayerData *layerData);
	void						(*sculptlayerdataInitializeAllMaskData)(SculptLayerData *layerData);
	void						(*sculptlayerdataTouchPointForUndo)(SculptLayerData *layerData, Int32 index);
	void						(*sculptlayerdataTouchMaskForUndo)(SculptLayerData *layerData, Int32 index);

	//SculptLayer R15
	SculptLayerData*			(*sculptlayerGetCurrentSculptLayerData)(SculptLayer *layer);
	void						(*sculptlayerClearMask)(SculptLayer *layer);
	void						(*sculptlayerClearLayer)(SculptLayer *layer);
	void						(*sculptlayerInitializeAllPointData)(SculptLayer *layer);
	void						(*sculptlayerInitializeAllMaskData)(SculptLayer *layer);
	void						(*sculptlayerTouchPointForUndo)(SculptLayer *layer, Int32 index);
	void						(*sculptlayerTouchMaskForUndo)(SculptLayer *layer, Int32 index);

	//SculptObject R15
	Int32						(*sculptobjGetPointCount)(SculptObject *obj);
	Bool						(*sculptobjHitScreen)(SculptObject *obj,BaseDraw* bd, Float mx, Float my, Bool backfaces, SculptHitData &hitData);
	Bool						(*sculptobjHitObject)(SculptObject *obj,const Vector &rayp, const Vector &rayv, Bool backfaces, SculptHitData &hitData);
	const Vector32 *			(*sculptobjGetVertexNormals)(SculptObject *obj);
	Vector *					(*sculptobjGetPointW)(SculptObject *obj);
	const Vector *				(*sculptobjGetPointR)(SculptObject *obj);
	void						(*sculptobjOffsetPoint)(SculptObject *obj, SculptLayer *pLayer, Vector *pPoints, Bool useMask, Float opacity, Int32 index, const Vector &offset, Bool respectOpacity);
	void						(*sculptobjOffsetPreviewPoint)(SculptObject *obj, SculptLayer *pLayer, Bool useMask, Float opacity, Int32 index, const Vector &offset, Bool respectOpacity);
	void						(*sculptobjSetPreviewPoint)(SculptObject *obj, SculptLayer *pLayer, Bool useMask, Float opacity, Int32 index, const Vector &offset, Bool respectOpacity);
	SculptLayerSystem*			(*sculptobjGetLayerSystem)(SculptObject *obj);
	void						(*sculptobjStartUndo)(SculptObject *obj);
	void						(*sculptobjEndUndo)(SculptObject *obj);
	void						(*sculptobjSmooth)(SculptObject *obj, Int32 count, Bool respectMask);

};


//----------------------------------------------------------------------------------------
/// Get the currently selected SculptObject in the document. This will the first selected PolygonObject that has a SculptTag.
/// @param[in] doc							The document to search
/// @param[in] includeHiddenObjects			If true it will include selected hidden objects.
/// @return									The SculptObject that the SculptTag references
//----------------------------------------------------------------------------------------
SculptObject *GetSelectedSculptObject(BaseDocument *doc, Bool includeHiddenObjects = false);

//----------------------------------------------------------------------------------------
/// Add a SculptTag to the PolygonObject if one does not exist then return the SculptObject that the newly created SculptTag references.
/// @param[in] poly							The PolygonObject to add the SculptTag to.
/// @param[in] doc							The Document that the PolygonObject belongs to.
/// @param[in] addUndo						If true then an undo event will be added so that the addition of the sculpt tag can be undone.
/// @return									The SculptObject that the SculpTag is referencing.
//----------------------------------------------------------------------------------------
SculptObject *MakeSculptObject(PolygonObject *poly, BaseDocument *doc, Bool addUndo = false);

//----------------------------------------------------------------------------------------
/// A helper method to check if an object is currently visible in the viewport.
/// @param[in] pObject						The object to check
/// @return									True if the object is enabled in the editor viewport
//----------------------------------------------------------------------------------------
Bool IsObjectEnabled(BaseObject *pObject);

//----------------------------------------------------------------------------------------
/// If you copy the polygon object that has a sculpt tag on it then you will need to ensure that its initialized 
/// correctly straight after adding it to a document. 
/// @param[in] obj					The PolygonObject that has the SculptTag
/// @param[in] doc					The document the object belongs to
//----------------------------------------------------------------------------------------
void EnsureSculptObjectReady(PolygonObject *obj, BaseDocument *doc);



#endif
/// @}
