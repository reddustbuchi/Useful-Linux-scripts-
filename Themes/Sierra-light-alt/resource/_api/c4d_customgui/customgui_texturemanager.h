/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_TEXTUREMANAGER_H_
#define _CUSTOMGUI_TEXTUREMANAGER_H_

#include "customgui_base.h"
#include "c4d_basecontainer.h"



#define CUSTOMGUI_TEXTUREMANAGER		200000247



class TextureManagerCustomGui : public BaseCustomGui<CUSTOMGUI_TEXTUREMANAGER>
{
		TextureManagerCustomGui();
		~TextureManagerCustomGui();

	public:

		void SetTexture(PaintTexture *tex);
		void SetTexture(MultipassBitmap *bmp);
};



// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#ifndef _INTERNAL_DEF_
	class iTextureManagerCustomGui
	{
	};
#else
	class iTextureManagerCustomGui;
#endif

struct TextureManagerLib : public BaseCustomGuiLib
{
	void			(iTextureManagerCustomGui::*SetTexture1)(PaintTexture *tex);
	void			(iTextureManagerCustomGui::*SetTexture2)(MultipassBitmap *bmp);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
