CONTAINER GVcross
{
	NAME GVcross;
	INCLUDE GVdynamic;

	GROUP ID_GVPROPERTIES
	{
	}

	GROUP ID_GVPORTS
	{
		DYNAMIC GV_CROSS_INPUT1	{ INPORT; STATICPORT; CREATEPORT; }
		DYNAMIC GV_CROSS_INPUT2	{ INPORT; STATICPORT; CREATEPORT; }
		DYNAMIC GV_CROSS_OUTPUT	{ OUTPORT; STATICPORT; CREATEPORT; }
	}
}