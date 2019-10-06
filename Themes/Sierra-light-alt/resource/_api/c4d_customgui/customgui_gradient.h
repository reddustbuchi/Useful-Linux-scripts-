/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_GRADIENT_H_
#define _CUSTOMGUI_GRADIENT_H_

#include "c4d_library.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"
#include "c4d_customdatatype.h"
#include "customgui_base.h"


#define CUSTOMGUI_GRADIENT			1000480
#define CUSTOMDATATYPE_GRADIENT 1000481
#define ID_GRADIENTGUI_BROWSERPRESET	1027759
#define ID_GRADIENTGUI_POPUPDIALOG		1027760

#define GRADIENTPROPERTY_COLOR				'colr'
#define GRADIENTPROPERTY_ALPHA				'alph'
#define GRADIENTPROPERTY_NOEDITCOLOR	'nedc'
#define GRADIENTPROPERTY_NOPRESETS		'nopr'
// these 2 options are allowed from DTYPE_COLOR
// DR_COLORFIELD_ICC_BASEDOC			= 8, // use iccprofile of the current basedocument
// DR_COLORFIELD_ICC_BPTEX				= 16, // uses iccprofile of the current bp texture

enum
{
	GRADIENT_INTERPOLATION_CUBICKNOT						= 0,
	GRADIENT_INTERPOLATION_CUBICBIAS						= 1,
	GRADIENT_INTERPOLATION_SMOOTHKNOT						= 2,
	GRADIENT_INTERPOLATION_LINEARKNOT						= 3,
	GRADIENT_INTERPOLATION_LINEAR								= 4,
	GRADIENT_INTERPOLATION_NONE									= 5,
	GRADIENT_INTERPOLATION_EXP_UP								= 6,
	GRADIENT_INTERPOLATION_EXP_DOWN							= 7
};

#define GRADIENTMODE_COLOR					0
#define GRADIENTMODE_ALPHA					1
#define GRADIENTMODE_COLORALPHA			2

#define GRADIENT_INTERPOLATION	1000	// Int32
#define GRADIENT_KNOT						1001	// BASECONTAINER
#define GRADIENT_MODE						1002	// Int32
#define GRADIENT_UNCLAMPED			1003  // BOOL

#define GRADIENTKNOT_COLOR			1000	// VECTOR
#define GRADIENTKNOT_BRIGHTNESS	1001	// REAL
#define GRADIENTKNOT_POSITION		1002	// REAL
#define GRADIENTKNOT_BIAS				1003	// REAL
#define GRADIENTKNOT_ID					1004  // Int32

struct GradientKnot
{
	GradientKnot(void) { col=Vector(1.0); brightness=1.0; pos=0.0; bias=0.5; index=0; }

	Vector	col;
	Float		brightness;
	Float		pos;
	Float		bias;
	Int32		index;
};

class Gradient : public CustomDataType
{
		Gradient(void);
		~Gradient(void);

	public:
		Bool					InvertKnots(void);
		Bool					DoubleKnots(void);
		void					FlushKnots(void);

		Bool					InitRender(const InitRenderStruct &irs);
		void					FreeRender(void);
		Vector				CalcGradientPixel(Float pos);

		Int32					GetKnotCount(void) const;

		Int32					InsertKnot(const GradientKnot &knot);
		Bool					RemoveKnot(Int32 index);

		GradientKnot	GetKnot(Int32 index) const;
		void					SetKnot(Int32 index, const GradientKnot &k);

		GeData				GetData(Int32 id) const;
		Bool					SetData(Int32 id,const GeData &data);

		GradientKnot	*GetRenderKnot(Int32 index);
		Int32					GetRenderKnotCount(void);

		Gradient*			GetAlphaGradient(void);
		Gradient*			AllocAlphaGradient(void);
		UInt32					GetChecksum() const;

		void					ConvertToAlphaGradient();
		static void		ConvertToAlphaGradient(BaseContainer* bc, Int32 id);

		static Gradient *Alloc();
		static void Free(Gradient *&grad);
};

class GradientCustomGui : public BaseCustomGui<CUSTOMGUI_GRADIENT>
{
		GradientCustomGui();
		~GradientCustomGui();

	public:
		Gradient *GetGradient();
		Bool SetGradient(Gradient *grad);

		Int32 GetActiveKnot(Bool &bias);
		void SetActiveKnot(Int32 index, Bool bias);

};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#ifndef _INTERNAL_DEF_
	class iGradientCustomGui
	{
	};
	class iGradient
	{
	};
#else
	class iGradientCustomGui;
	class iGradient;
#endif


struct CustomGuiGradientLib : public BaseCustomGuiLib
{
	Bool							(iGradient::*InvertKnots)(void);
	Bool							(iGradient::*DoubleKnots)(void);
	void							(iGradient::*FlushKnots)(void);

	Bool							(iGradient::*InitRender)(const InitRenderStruct &irs);
	void							(iGradient::*FreeRender)(void);
	Vector						(iGradient::*CalcGradientPixel)(Float pos);

	Int32							(iGradient::*GetKnotCount)(void) const;

	Int32							(iGradient::*InsertKnot)(const GradientKnot &knot);
	Bool							(iGradient::*RemoveKnot)(Int32 index);

	GradientKnot			(iGradient::*GetKnot)(Int32 index) const;
	void							(iGradient::*SetKnot)(Int32 index, const GradientKnot &k);

	GeData						(iGradient::*iGetData)(Int32 id) const;
	Bool							(iGradient::*iSetData)(Int32 id,const GeData &data);

	GradientKnot*			(iGradient::*GetRenderKnot)(Int32 index);
	Int32							(iGradient::*GetRenderKnotCount)(void);

	Gradient*					(iGradient::*GetAlphaGradient)(void);

	Gradient*					(*AllocGradient)(void);
	void							(*FreeGradient)(Gradient *grad);

	Gradient*					(iGradientCustomGui::*GetGradient)();

	Int32							(iGradientCustomGui::*GetActiveKnot)(Bool &bias);
	void							(iGradientCustomGui::*SetActiveKnot)(Int32 index, Bool bias);
	UInt32							(iGradient::*GetChecksum)() const;

	Gradient*					(iGradient::*AllocAlphaGradient)(void);
	void							(iGradient::*ConvertToAlphaGradient)();

	Bool							(iGradientCustomGui::*SetGradient)(Gradient *grad);
};

#endif
