CONTAINER Oparticle
{
	NAME Oparticle;
	INCLUDE Obase;

	GROUP ID_PARTICLE
	{
		DEFAULT 1;
		LONG PARTICLEOBJECT_BIRTHEDITOR    { MIN 1; MAX 10000; ANIM OFF; }
		LONG PARTICLEOBJECT_BIRTHRAYTRACER { MIN 1; MAX 10000; ANIM OFF; }
		REAL PARTICLEOBJECT_VISIBILITY     { UNIT PERCENT; MIN 0.0; MAX 100.0; }
		BASETIME PARTICLEOBJECT_START      { ANIM OFF; }
		BASETIME PARTICLEOBJECT_STOP       { ANIM OFF; }
		LONG PARTICLEOBJECT_SEED           { MIN 0; MAX 10000; }
		GROUP
		{
			COLUMNS 2;
			BASETIME PARTICLEOBJECT_LIFETIME	 { MIN 0; MINEX; }
			REAL PARTICLEOBJECT_LIFETIMEVAR		 { UNIT PERCENT; MIN 0.0; MAX 100.0; }
			REAL PARTICLEOBJECT_SPEED					 { UNIT METER; }
			REAL PARTICLEOBJECT_SPEEDVAR			 { UNIT PERCENT; MIN 0.0; MAX 100.0; }
			REAL PARTICLEOBJECT_ROTATION			 { UNIT DEGREE; }
			REAL PARTICLEOBJECT_ROTATIONVAR		 { UNIT PERCENT; MIN 0.0; MAX 100.0; }
			REAL PARTICLEOBJECT_SIZE					 { MIN 0.0; STEP 0.01; }
			REAL PARTICLEOBJECT_SIZEVAR				 { UNIT PERCENT; MIN 0.0; MAX 100.0; }
		}
		BOOL PARTICLEOBJECT_TANGENTIAL		 { }
		BOOL PARTICLEOBJECT_SHOWOBJECTS		 { }
		BOOL PARTICLEOBJECT_RENDERINSTANCES { }
	}
	GROUP ID_EMITTER
	{
		LONG PARTICLEOBJECT_TYPE					 { CYCLE { PARTICLEOBJECT_TYPE_PYRAMID;PARTICLEOBJECT_TYPE_CONE;} }
		REAL PARTICLEOBJECT_SIZEX          { UNIT METER; MIN 0.0; }
		REAL PARTICLEOBJECT_SIZEY          { UNIT METER; MIN 0.0; }

		REAL PARTICLEOBJECT_ANGLEH				 { UNIT DEGREE; MIN 0.0; MAX 360.0; }
		REAL PARTICLEOBJECT_ANGLEV				 { UNIT DEGREE; MIN 0.0; MAX 180.0; }
	}
	GROUP ID_INCLUDE
	{
		SCALE_V;

		LONG PARTICLEOBJECT_MODE { CYCLE { PARTICLEOBJECT_MODE_INCLUDE; PARTICLEOBJECT_MODE_EXCLUDE; } }

		IN_EXCLUDE  PARTICLEOBJECT_INCLUDE
		{
			NUM_FLAGS 0; INIT_STATE 0; SEND_SELCHNGMSG 1;
			ACCEPT { Obase; };
		}
	}
}