CONTAINER Osds
{
  NAME Osds;
  INCLUDE Obase;

  GROUP ID_OBJECTPROPERTIES
  {
		LONG SDSOBJECT_TYPE
		{
			CYCLE
			{
				SDSOBJECT_TYPE_CM;
				SDSOBJECT_TYPE_CM_N;
			}
		}
		BOOL SDSOBJECT_R12_COMPATIBILITY {ANIM OFF;}

    LONG SDSOBJECT_SUBEDITOR_CM           { MIN 0; MAX 6; }
    LONG SDSOBJECT_SUBRAY_CM              { MIN 0; MAX 6; }

    LONG SDSOBJECT_SUBDIVIDE_UV 
    {
      CYCLE
      {
        SDSOBJECT_SUBDIVIDE_UV_STANDARD;
        SDSOBJECT_SUBDIVIDE_UV_BOUNDARY;
        SDSOBJECT_SUBDIVIDE_UV_EDGE;
      } 
    }
  }
}
