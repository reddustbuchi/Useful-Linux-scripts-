////////////////////////////////////////////////////////////////
// xTerrainmask
////////////////////////////////////////////////////////////////
// (c) 2010 MAXON Computer GmbH, all rights reserved
////////////////////////////////////////////////////////////////

CONTAINER xTerrainmask
{
	NAME xTerrainmask;

	INCLUDE Mpreview;
	INCLUDE Xbase;

	GROUP ID_SHADERPROPERTIES
	{
		COLUMNS 3;
		
		GRADIENT		XTMASK_GRADIENT								{ COLOR; ICC_BASEDOCUMENT; }
		STATICTEXT	{ JOINENDSCALE; }
		STATICTEXT	{ JOINENDSCALE; }

		SEPARATOR																	{ LINE; }
		STATICTEXT	{ JOINENDSCALE; }
		STATICTEXT	{ JOINENDSCALE; }

		BOOL				XTMASK_ALTITUDE_ENABLE					{  }
		STATICTEXT	{ JOINEND; }
		STATICTEXT	{ JOINEND; }

		SEPARATOR																{  }
		STATICTEXT	{ JOINENDSCALE; }
		STATICTEXT	{ JOINENDSCALE; }
		

		REAL		XTMASK_ALTITUDE_MIN							{ UNIT METER; }
		REAL		XTMASK_ALTITUDE_MAX							{ UNIT METER; }
		STATICTEXT	{ JOINENDSCALE; }


		REAL		XTMASK_ALTITUDE_SOFTEN_MIN			{ UNIT PERCENT; MIN 0.0; MAX 100.0; CUSTOMGUI REALSLIDER; }
		STATICTEXT	{ JOINENDSCALE; }
		STATICTEXT	{ JOINENDSCALE; }
		
		REAL		XTMASK_ALTITUDE_SOFTEN_MAX			{ UNIT PERCENT; MIN 0.0; MAX 100.0; CUSTOMGUI REALSLIDER; }
		STATICTEXT	{ JOINENDSCALE; }
		STATICTEXT	{ JOINENDSCALE; }

		REAL		XTMASK_ALTITUDE_NOISE_HEIGHT		{ UNIT METER; }
		REAL		XTMASK_ALTITUDE_NOISE_SCALE			{ UNIT PERCENT; }
		STATICTEXT	{ JOINENDSCALE; }

		SEPARATOR																{ LINE; }
		STATICTEXT	{ JOINENDSCALE; }
		STATICTEXT	{ JOINENDSCALE; }

		BOOL		XTMASK_SLOPE_ENABLE							{  }
		STATICTEXT	{ JOINEND; }
		STATICTEXT	{ JOINEND; }

		SEPARATOR																{  }
		STATICTEXT	{ JOINENDSCALE; }
		STATICTEXT	{ JOINENDSCALE; }

		REAL		XTMASK_SLOPE_MIN								{ UNIT DEGREE; MIN 0.0; MAX 179.0; }
		REAL		XTMASK_SLOPE_MAX								{ UNIT DEGREE; MIN 1.0; MAX 180.0; }
		STATICTEXT	{ JOINENDSCALE; }

		REAL		XTMASK_SLOPE_SOFTEN_MIN					{ UNIT PERCENT; MIN 0.0; MAX 100.0; CUSTOMGUI REALSLIDER; }
		STATICTEXT	{ JOINENDSCALE; }
		STATICTEXT	{ JOINENDSCALE; }
		
		REAL		XTMASK_SLOPE_SOFTEN_MAX					{ UNIT PERCENT; MIN 0.0; MAX 100.0; CUSTOMGUI REALSLIDER; }
		STATICTEXT	{ JOINENDSCALE; }
		STATICTEXT	{ JOINENDSCALE; }
		
		BOOL		XTMASK_SLOPE_USEBUMP						{  }
		STATICTEXT	{  }
		STATICTEXT	{  }
		
		LONG		XTMASK_SLOPE_DIRECTION
		{
			CYCLE
			{
				XTMASK_DIRECTION_X2;
				XTMASK_DIRECTION_X;
				XTMASK_DIRECTION_Y2;
				XTMASK_DIRECTION_Y;
				XTMASK_DIRECTION_Z2;
				XTMASK_DIRECTION_Z;
				XTMASK_DIRECTION_CUSTOM;
			}
		}
		STATICTEXT	{  }
		STATICTEXT	{  }
		
		VECTOR	XTMASK_SLOPE_DIRECTION_CUSTOM		{  }
		STATICTEXT	{ JOINEND; }
		STATICTEXT	{ JOINEND; }
		
		BOOL		XTMASK_SLOPE_ALTERNATIVEBLENDING							{  }
		STATICTEXT	{ JOINEND; }
		STATICTEXT	{ JOINEND; }

		REAL		XTMASK_SLOPE_ALTERNATIVEBLENDING_HARDNESS			{ UNIT PERCENT; MIN 0.0; MAX 100.0; }
		STATICTEXT	{ JOINEND; }
		STATICTEXT	{ JOINEND; }

		SEPARATOR																{ LINE; }
		STATICTEXT	{ JOINENDSCALE; }
		STATICTEXT	{ JOINENDSCALE; }

		BOOL		XTMASK_GLOBAL										{  }
		STATICTEXT	{ JOINEND; }
		STATICTEXT	{ JOINEND; }
		
		BOOL		XTMASK_INVERT										{  }
		STATICTEXT	{ JOINEND; }
		STATICTEXT	{ JOINEND; }
	}
}
