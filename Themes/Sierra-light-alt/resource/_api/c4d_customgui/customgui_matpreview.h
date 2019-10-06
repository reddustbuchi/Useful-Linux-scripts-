/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_MATPREVIEW_H_
#define _CUSTOMGUI_MATPREVIEW_H_

#include "c4d_library.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"
#include "c4d_customdatatype.h"
#include "customgui_base.h"
#include "c4d_baselist.h"
#include "c4d_thread.h"

#define CUSTOMGUI_MATPREVIEW          1011152
#define CUSTOMDATATYPE_MATPREVIEW     1011153

#define MATPREVIEW_MIN_WIDTH          1000 // long
#define MATPREVIEW_MIN_HEIGHT         1001 // long
#define MATPREVIEW_NO_SIZE_POPUP      1002 // bool
#define MATPREVIEW_NO_BORDER          1003 // bool
#define MATPREVIEW_NO_ANIMATION       1004 // bool
#define MATPREVIEW_NO_FLOATWINDOW     1005 // bool
#define MATPREVIEW_NO_SCENESETTINGS   1006 // bool
#define MATPREVIEW_RECTSELECT         1007 // bool (only used if a callback function is used to render the preview)

#define MATPREVIEW_GET_OBJECT_INFO    1011147
#define MATPREVIEW_GENERATE_IMAGE     1011148
#define MATPREVIEW_MODIFY_CACHE_SCENE 1011149
#define MATPREVIEW_PREPARE_SCENE      1011142
#define MATPREVIEW_GET_PREVIEW_ID     1011143
#define MATPREVIEW_GET_POPUP_OPTIONS  1011141
#define MATPREVIEW_HANDLE_POPUP_MSG   1011144
#define MATPREVIEW_FREE_USERDATA      450000029
#define MATPREVIEW_COPY_USERDATA      450000030
#define MATPREVIEW_DRAGNDROP_RECV     450000062 // preview has received drag & drop
#define MATPREVIEW_DRAGNDROP_START    450000063 // start drag & drop (fill MatPreviewHandleDragnDrop structure)
#define MATPREVIEW_DRAGNDROP_END      450000064 // drag & drop finished, free data
#define MATPREVIEW_GET_DIRTY_COUNT    450000065
#define MATPREVIEW_POPUP_NAME         99999
#define MATPREVIEW_NULL_SIZE_NAME     "null-size"

#define MATPREVIEW_FLAG_HIDE_ROTATION       1
#define MATPREVIEW_FLAG_HIDE_SCENES         2
#define MATPREVIEW_FLAG_HIDE_ANIMATE        4
#define MATPREVIEW_FLAG_HIDE_SIZE           8
#define MATPREVIEW_FLAG_HIDE_OPEN           16
#define MATPREVIEW_FLAG_HIDE_SCENE_SETTINGS 32
#define MATPREVIEW_FLAG_ALLOW_DRAGNDROP     64

class MaterialPreviewData;

enum MatPreviewType
{
	MatPreviewDefault = 999,
	MatPreviewFlat2D = 1000,
	MatPreviewCube,
	MatPreviewPlane,
	MatPreviewCylinder,
	MatPreviewTorus,
	MatPreviewPlaneBack,
	MatPreviewSphere,
	MatPreview2Torus,
	MatPreviewRoundedCube,
	MatPreviewKnot,
	MatPreviewUser = 1050
};

enum MatPreviewSize
{
	MatPreviewSizeDefault = 2000, // use system default
	MatPreviewSizeSmall,
	MatPreviewSizeMedium,
	MatPreviewSizeBig,
	MatPreviewSizeLarge
};

struct MatPreviewObjectInfo
{
	// set true, if your material has its own preview handler
	Bool bHandlePreview;
	// set true, if the material must modify the default scenes
	Bool bNeedsOwnScene;
	// set true, if no scene should appear in the popup menu and you want to create your own preview scene
	// bNeedsOwnScene must be true if you don't use a standard scene.
	Bool bNoStandardScene;
	Int32 lFlags; // return a combination of the MATPREVIEW_FLAGs here, it is only evaluated if bHandlePreview is set
};

struct MatPreviewModifyCacheScene
{
	MatPreviewType t;
	String strUserScene;
	BaseDocument* pDoc;
};

struct MatPreviewPrepareScene
{
	Bool bScenePrepared;  // set true, if you modified the scene, the preview will do this for you otherwise
	BaseLink* pLink;      // may be nullptr, link the cloned object here.
	BaseDocument* pDoc;   // the preview document (a clone of the scene cache entry)
	Matrix matrDefault;   // the default object matrix
	MaterialPreviewData* pPreviewData; // the preview data - may be nullptr
	BaseDocument* pOriginalDoc; // the original document - only access it if there is no other way
};

struct MatPreviewGenerateImage
{
	BaseDocument* pDoc; // the document (may be nullptr)
	BaseBitmap* pDest;  // an initialized bitmap you must render to
	BaseThread* pThread;// the rendering thread (may be nullptr)
	Float rTime;         // current preview time
	Bool bEditorPreview; // never used
	Float rWorldSize;    // scale your scene (usually the object named NULL_SIZE_NAME) by rWorldSize using SetScale. Scale it by 1 after your render is complete
	Bool bLowQuality;   // true, if you may render in low quality (e.g. during rotating the object)
	RENDERRESULT lResult;       // return one of the RAY_* constants here
	Bool bIsAnimating;  // indicates whether the user has chosen Animate in the preview
};

struct MatPreviewCopyUserData
{
	void* src;
	void* dst;
};

struct MatPreviewHandleDragnDrop
{
	Int32 lType;
	void* pObj;
	GeDialog* pDlg;
	const BaseContainer* pDragData;
	Int32 lReturn;
};

typedef Bool (*RenderPreviewImageCallback)(Int32 lMessage, void* pData, void* pUserData);

class MaterialPreviewData : public CustomDataType
{
private:
	MaterialPreviewData();
	~MaterialPreviewData();
public:
	Bool Init(BaseChannel *pChannel, Int32 lCount);
	Bool Init(BaseShader* pShader, Int32 lCount);
	Bool Init(BaseMaterial* pMaterial, Int32 lCount);
	Bool Init(BaseBitmap* pImage, Int32 lCount);
	Bool Init(RenderPreviewImageCallback fn, void* pUserData, Int32 lUserID, Int32 lCount); // pUserData may be deleted after the function has finished

	void AnimatePreview(Bool bAnimate);
	Bool PreviewIsAnimated();
	void SetPreviewType(MatPreviewType t);
	MatPreviewType GetPreviewType();
	void SetUserPreviewSceneName(const String &strName);
	String GetUserPreviewSceneName();
	void SetPreviewSize(MatPreviewSize s);
	MatPreviewSize GetPreviewSize();
	void SetObjectMatrix(const Matrix &m);
	Bool GetObjectMatrix(Matrix &m); // returns false, if matrix is not initialized
	void ClearObjectMatrix(); // sets the object matrix to uninitialized
	Float GetWorldSize();
	void SetWorldSize(Float r);
	Float GetPreviewStartTime();
	void SetPreviewStartTime(Float r);
	void GetEnvironment(Vector &col, Float &strength);
	void SetEnvironment(const Vector &col, const Float &strength);
	Int32 GetDirtyCount();
	Bool GetRegion(Float &l, Float &t, Float &r, Float &b);
	void SetRegion(Bool bActive, Float l, Float t, Float r, Float b);
	Int32 GetPreviewChannel();
	void SetPreviewChannel(Int32 lChannel);
};

Bool SetDParameterPreview(BaseContainer* pContainer, const GeData* pData, DESCFLAGS_SET &lFlags, Int32 lID);
Bool GetDParameterPreview(BaseContainer* pContainer, GeData* pData, DESCFLAGS_GET &lFlags, Int32 lID, Int32 lCount, BaseMaterial* pMaterial);
Bool GetDParameterPreview(BaseContainer* pContainer, GeData* pData, DESCFLAGS_GET &lFlags, Int32 lID, Int32 lCount, BaseShader* pShader);
BaseContainer GetPreviewScenes(Bool bIncludeFlat2D, Bool bIncludeDefault = false, Int32 lObjectID = -1); // use the container's elements in menus
Bool HandlePreviewSceneMessage(Int32 lID, MatPreviewType &t, String &strScene); // generates the type and the scene name from the menu item generated by GetPreviewScenes
Bool AddUserPreviewScene(const Filename &fn, Int32 lID, String* pstrName); // adds a user scene that only shows up in the materials with type lID, pstrName may be nullptr

// flags for RenderMaterialPreview and RenderShaderPreview
#define RENDER_PREVIEW_USE_BMP_SIZE				1 // renders in full bitmap size, ignores the settings in the material or shader data
RENDERRESULT RenderMaterialPreview(const Filename &docpath, BaseMaterial* pMatClone, BaseMaterial* pOrigMat, BaseThread* pThread, BaseBitmap* pDest, BaseDocument *pOriginalDoc, Float rCurrentTime, Int32 lFlags = 0);
RENDERRESULT RenderShaderPreview(const Filename &docpath, BaseShader* pShaderClone, BaseShader* pOrigShader, BaseThread* pThread, BaseBitmap* pDest, BaseDocument *pOriginalDoc, Float rCurrentTime, Int32 lFlags = 0);
RENDERRESULT RenderCustomPreview(RenderPreviewImageCallback fn, void* pUserData, Int32 lUserID, BaseThread* pThread, BaseBitmap* pDest, Int32 lFlags = 0);

class MaterialPreviewCustomGui : public BaseCustomGui<CUSTOMGUI_MATPREVIEW>
{
		MaterialPreviewCustomGui();
		~MaterialPreviewCustomGui();
};


// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#ifndef _MATPREVIEW_INTERNAL_DEF_
	class iMatPreviewCustomGui
	{
	};
	class iMatPreviewData
	{
	};
#else
	class iMatPreviewCustomGui;
	class iMatPreviewData;
#endif

struct CustomGuiMatPreviewLib : public BaseCustomGuiLib
{
	Bool        (iMatPreviewData::*InitChannel)(BaseChannel *pChannel, Int32 lCount);
	Bool        (iMatPreviewData::*InitShader)(BaseShader* pShader, Int32 lCount);
	Bool        (iMatPreviewData::*InitMaterial)(BaseMaterial* pMaterial, Int32 lCount);
	Bool        (iMatPreviewData::*InitBitmap)(BaseBitmap* pImage, Int32 lCount);
	void        (iMatPreviewData::*AnimatePreview)(Bool bAnimate);
	Bool        (iMatPreviewData::*PreviewIsAnimated)();
	void        (iMatPreviewData::*SetPreviewType)(MatPreviewType t);
	MatPreviewType  (iMatPreviewData::*GetPreviewType)();
	void        (iMatPreviewData::*SetPreviewSize)(MatPreviewSize s);
	MatPreviewSize  (iMatPreviewData::*GetPreviewSize)();
	void        (iMatPreviewData::*SetObjectMatrix)(const Matrix &m);
	Bool        (iMatPreviewData::*GetObjectMatrix)(Matrix &m);
	void        (iMatPreviewData::*SetUserPreviewSceneName)(const String &strName);
	String      (iMatPreviewData::*GetUserPreviewSceneName)();
	void        (iMatPreviewData::*ClearObjectMatrix)();

	Bool        (*MatPreview_SetDParameterPreview)(BaseContainer* pContainer, const GeData* pData, DESCFLAGS_SET &lFlags, Int32 lID);
	Bool        (*MatPreview_GetDParameterPreviewMat)(BaseContainer* pContainer, GeData* pData, DESCFLAGS_GET &lFlags, Int32 lID, Int32 lCount, BaseMaterial* pMaterial);
	Bool        (*MatPreview_GetDParameterPreviewShd)(BaseContainer* pContainer, GeData* pData, DESCFLAGS_GET &lFlags, Int32 lID, Int32 lCount, BaseShader* pShader);
	BaseContainer (*MatPreview_GetPreviewScenes)(Bool bIncludeFlat2D, Bool bIncludeDefault, Int32 lObjectID);
	Bool        (*MatPreview_HandlePreviewSceneMessage)(const Int32 lID, MatPreviewType &t, String &strScene);
	Bool        (*MatPreview_AddUserPreviewScene)(const Filename &fn, Int32 lID, String* pstrName);

	Float        (iMatPreviewData::*GetWorldSize)();
	void        (iMatPreviewData::*SetWorldSize)(Float r);
	Float        (iMatPreviewData::*GetPreviewStartTime)();
	void        (iMatPreviewData::*SetPreviewStartTime)(Float r);
	void        (iMatPreviewData::*GetEnvironment)(Vector &col, Float &strength);
	void        (iMatPreviewData::*SetEnvironment)(const Vector &col, const Float &strength);

	Int32        (iMatPreviewData::*GetDirtyCount)();
	Bool        (iMatPreviewData::*InitFunction)(RenderPreviewImageCallback fn, void* pUserData, Int32 lUserID, Int32 lCount);
	Bool				(iMatPreviewData::*GetRegion)(Float &l, Float &t, Float &r, Float &b);
	void				(iMatPreviewData::*SetRegion)(Bool bActive, Float l, Float t, Float r, Float b);

	RENDERRESULT(*MatPreview_RenderMaterialPreview)(const Filename &docpath, BaseMaterial* pMatClone, BaseMaterial* pOrigMat, BaseThread* pThread, BaseBitmap* pDest, BaseDocument *pOriginalDoc, Float rCurrentTime, Int32 lFlags);
	RENDERRESULT(*MatPreview_RenderShaderPreview)(const Filename &docpath, BaseShader* pShaderClone, BaseShader* pOrigShader, BaseThread* pThread, BaseBitmap* pDest, BaseDocument *pOriginalDoc, Float rCurrentTime, Int32 lFlags);
	RENDERRESULT(*MatPreview_RenderCustomPreview)(RenderPreviewImageCallback fn, void* pUserData, Int32 lUserID, BaseThread* pThread, BaseBitmap* pDest, Int32 lFlags);

	Int32				(iMatPreviewData::*GetPreviewChannel)();
	void				(iMatPreviewData::*SetPreviewChannel)(Int32 lChannel);
};

#endif // _CUSTOMGUI_MATPREVIEW_H_
