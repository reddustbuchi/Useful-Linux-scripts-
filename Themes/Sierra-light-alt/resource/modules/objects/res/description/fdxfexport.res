CONTAINER Fdxfexport
{
	NAME Fdxfexport;
	INCLUDE Fbase;

	GROUP DXFEXPORTFILTER_GROUP
	{
		DEFAULT 1;
		COLUMNS 2;
		UNITSCALE DXFEXPORTFILTER_SCALE	{ }
		STATICTEXT {}
		LONG DXFEXPORTFILTER_MODE	{ CYCLE { DXFEXPORTFILTER_MODE_POLYLINE; DXFEXPORTFILTER_MODE_SOLID; DXFEXPORTFILTER_MODE_3DFACE; } DEFAULT DXFEXPORTFILTER_MODE_POLYLINE;}
		STATICTEXT {}
	}
}
