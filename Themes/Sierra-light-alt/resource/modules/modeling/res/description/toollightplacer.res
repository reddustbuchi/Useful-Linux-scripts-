CONTAINER ToolLightPlacer
{
  NAME ToolLightPlacer;
	INCLUDE ToolBase;

  GROUP MDATA_MAINGROUP
  {
		GROUP
		{
			COLUMNS 1;

			LONG MDATA_LIGHTPLACER_MODE
			{
				CYCLE
				{
					MDATA_LIGHTPLACER_MODE_TRACKBALL;
					MDATA_LIGHTPLACER_MODE_SURFACE;
					MDATA_LIGHTPLACER_MODE_DIFFUSE;
					MDATA_LIGHTPLACER_MODE_SPECULAR;
					MDATA_LIGHTPLACER_MODE_TARGET;
					MDATA_LIGHTPLACER_MODE_PIVOT;
				}
			}
			
			LONG MDATA_LIGHTPLACER_SELMODE
			{
				CYCLE
				{
					MDATA_LIGHTPLACER_SELMODE_ANGLE;
					MDATA_LIGHTPLACER_SELMODE_LIGHT;
				}
			}

			GROUP
			{
				COLUMNS 3;
				BOOL MDATA_LIGHTPLACER_LIGHTONLY { FIT_H; }
				BOOL MDATA_LIGHTPLACER_HIGHLIGHTING { FIT_H;}
			//	BOOL MDATA_LIGHTPLACER_QUICK { FIT_H; }
			}

			SEPARATOR { LINE; }
			
			VECTOR MDATA_LIGHTPLACER_PIVOT { UNIT METER; }
			GROUP
			{
				COLUMNS 2;
				BUTTON MDATA_LIGHTPLACER_PLACEPIVOT { FIT_H;}
				BUTTON MDATA_LIGHTPLACER_ADDLIGHT { FIT_H;}
			}
		}
	}
	
	HIDE MDATA_COMMANDGROUP;
}
