CONTAINER ToolSetObject
{
  NAME ToolSetObject;

	GROUP ID_MAIN_GROUP
	{
		SCALE_V;
		GROUP
		{
			LINK SETOBJECT_OBJ { }
		}
		GROUP
		{
			FILENAME SETOBJECT_FILENAME { TEXTURE; }
		}
		GROUP
		{
			COLUMNS 2;
			REAL SETOBJECT_AZIMUTH { UNIT DEGREE; MIN 0; MAX 360; }
			REAL SETOBJECT_ALTTUDE { UNIT DEGREE; MIN -90; MAX 90; }
		}
	}
}