CONTAINER GVreference
{
	NAME GVreference;
	INCLUDE GVbase;

	GROUP ID_GVPROPERTIES
	{

	}

	GROUP ID_GVPORTS
	{
		GVGENERALINSTANCE GV_REFERENCE_INPUT_OBJECT { INPORT; STATICPORT; CREATEPORT; }
		STRING GV_REFERENCE_INPUT_PATH { INPORT; STATICPORT; CREATEPORT; }

		GVGENERALINSTANCE GV_REFERENCE_OUTPUT_OBJECT { OUTPORT; STATICPORT; CREATEPORT; }
	}
}
