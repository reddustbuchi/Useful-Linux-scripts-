CONTAINER Flwimport
{
	NAME Flwimport;
	INCLUDE Fbase;

	GROUP LWIMPORTFILTER_GROUP
	{
		UNITSCALE LWIMPORTFILTER_SCALE	{ }
		BOOL LWIMPORTFILTER_TEXTURES { DEFAULT 1;}
		BOOL LWIMPORTFILTER_LIGHTS { DEFAULT 1;}
		BOOL LWIMPORTFILTER_SPLITOBJECTS { DEFAULT 0;}
	}
}