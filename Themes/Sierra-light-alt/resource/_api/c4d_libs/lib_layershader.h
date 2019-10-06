#ifndef _LIB_LAYERSHADER_H_
#define _LIB_LAYERSHADER_H_

#include "c4d_library.h"
#include "c4d_basecontainer.h"

#ifdef __API_INTERN__
#include "pluginshader.h"
#else
#include "c4d_basechannel.h"
#endif

class BlendLayer;

#define LAYER_SHADER_LIB			450000055

enum LayerType
{
	TypeUnknown = 0,
	TypeFolder = 1,
	TypeShader = 2,
	TypeBrightnessContrast = 3,
	TypeHSL = 4,
	TypePosterize = 5,
	TypeColorize = 6,
	TypeClamp = 7,
	TypeClip = 8,
	TypeDistorter = 9,
	TypeTransform = 10
};

enum LayerFlags
{
	LAYER_INVERT        = 1,
	LAYER_ALPHA         = 2,
	LAYER_INVERT_ALPHA  = 6, // 2 + 4
	LAYER_IMAGE_ALPHA		= 8
};

enum BlendMode
{
	BlendNormal = 1,
	BlendMultiply,
	BlendScreen,
	BlendOverlay,
	BlendHardLight,
	BlendSoftLight,
	BlendDodge,
	BlendBurn,
	BlendDarken,
	BlendLighten,
	BlendAdd,
	BlendSubtract,
	BlendDifference,
	BlendExclusion,
	BlendHue,
	BlendSat,
	BlendColor,
	BlendLuminance,
	BlendLevr,
	BlendAlphaMask
};

// common for all layers
#define LAYER_S_PARAM_ALL_ACTIVE        1000 // long
#define LAYER_S_PARAM_ALL_SELECTED      1001 // long
#define LAYER_S_PARAM_ALL_FLAGS         1002 // long

// folder
#define LAYER_S_PARAM_FOLDER_MODE       2000 // BlendMode
#define LAYER_S_PARAM_FOLDER_BLEND      2001 // real
#define LAYER_S_PARAM_FOLDER_OPEN       2002 // long
#define LAYER_S_PARAM_FOLDER_FIRSTCHILD	2003 // pointer to a LayerShaderLayer, read-only

// shader
#define LAYER_S_PARAM_SHADER_MODE       2000 // BlendMode
#define LAYER_S_PARAM_SHADER_BLEND      2001 // real
#define LAYER_S_PARAM_SHADER_LINK       2002 // pointer to a BaseLink that contains the shader, read-only

// brightness / contrast effect
#define LAYER_S_PARAM_BC_BRIGHTNESS     2000 // real
#define LAYER_S_PARAM_BC_CONTRAST       2001 // real
#define LAYER_S_PARAM_BC_GAMMA          2002 // real

// HSL
#define LAYER_S_PARAM_HSL_HUE           2000 // real
#define LAYER_S_PARAM_HSL_SATURATION    2001 // real
#define LAYER_S_PARAM_HSL_LIGHTNESS     2002 // real
#define LAYER_S_PARAM_HSL_COLORIZE      2003 // long

// Posterize
#define LAYER_S_PARAM_POSTER_LEVELS     2000 // long
#define LAYER_S_PARAM_POSTER_WIDTH      2001 // real

// Colorize
#define LAYER_S_PARAM_COLORIZE_INPUT    2000 // long [0..6], same order as in the combo box
#define LAYER_S_PARAM_COLORIZE_GRADIENT 2001 // gradient
#define LAYER_S_PARAM_COLORIZE_OPEN     2002 // long
#define LAYER_S_PARAM_COLORIZE_CYCLE    2003 // long

// Clamp
#define LAYER_S_PARAM_CLAMP_LOW_CLIP    2000 // real
#define LAYER_S_PARAM_CLAMP_HIGH_CLIP   2001 // real

// Clip
#define LAYER_S_PARAM_CLIP_LOW_CLIP     2000 // real
#define LAYER_S_PARAM_CLIP_HIGH_CLIP    2001 // real

// Transform
#define LAYER_S_PARAM_TRANS_ANGLE       2000 // real
#define LAYER_S_PARAM_TRANS_MIRROR      2001 // long
#define LAYER_S_PARAM_TRANS_FLIP        2002 // long
#define LAYER_S_PARAM_TRANS_SCALE       2003 // vector
#define LAYER_S_PARAM_TRANS_MOVE        2004 // vector

// Distorter
#define LAYER_S_PARAM_DISTORT_NOISE     2000 // noise type
#define LAYER_S_PARAM_DISTORT_STRENGTH  2001 // real
#define LAYER_S_PARAM_DISTORT_OCTACES   2002 // real
#define LAYER_S_PARAM_DISTORT_TIME_SCALE  2003 // real
#define LAYER_S_PARAM_DISTORT_NOISE_SCALE 2004 // real
#define LAYER_S_PARAM_DISTORT_3D_NOISE  2005 // long
#define LAYER_S_PARAM_DISTORT_WRAP      2006 // long [0..3], same order as in the combo box


class LayerShaderLayer
{
private:
	LayerShaderLayer();
	~LayerShaderLayer();

public:
	LayerShaderLayer* GetNext();
	LayerType GetType();
	String GetName(BaseDocument* doc);
	BaseBitmap* GetPreview();

	Bool GetParameter(Int32 id, GeData &d) const;
	Bool SetParameter(Int32 id, const GeData &d);
};

class LayerShader : public BaseShader
{
private:
	LayerShader();
	~LayerShader();

public:
	LayerShaderLayer* GetFirstLayer();
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
struct LayerShaderLib : public C4DLibrary
{
	LayerShaderLayer*		(*GetFirstLayer)(BaseShader* op);

	LayerShaderLayer*		(BlendLayer::*GetNext)();
	LayerType						(BlendLayer::*GetType)();
	String							(BlendLayer::*GetName)(BaseDocument* pDoc);
	BaseBitmap*					(BlendLayer::*GetPreview)();
	Bool								(BlendLayer::*GetParameter)(Int32 id, GeData &d) const;
	Bool								(BlendLayer::*SetParameter)(Int32 id, const GeData &d);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif // _LIB_LAYERSHADER_H_
