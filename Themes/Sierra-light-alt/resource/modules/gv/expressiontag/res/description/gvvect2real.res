CONTAINER GVvect2real
{
	NAME GVvect2real;
	INCLUDE GVbase;

	GROUP ID_GVPROPERTIES
	{
	}

	GROUP ID_GVPORTS
	{
		VECTOR GV_VECT2REAL_INPUT { INPORT; STATICPORT; CREATEPORT; }

		REAL GV_VECT2REAL_OUTPUTX { OUTPORT; STATICPORT; CREATEPORT; }
		REAL GV_VECT2REAL_OUTPUTY { OUTPORT; STATICPORT; CREATEPORT; }
		REAL GV_VECT2REAL_OUTPUTZ { OUTPORT; STATICPORT; CREATEPORT; }
	}
}
