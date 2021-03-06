CONTAINER Osplinedeformer
{
	NAME Osplinedeformer;
	INCLUDE Obase;

	GROUP ID_OBJECTPROPERTIES
	{
    LINK SPLINEDEFORMEROBJECT_ORIGINAL_SPLINE
		{
			ACCEPT
			{
				Obase; 
			}
		}

		LINK SPLINEDEFORMEROBJECT_MODIFY_SPLINE
		{
			ACCEPT
			{
				Obase; 
			}
		}
    LONG SPLINEDEFORMEROBJECT_B_APPROX { MIN 1; MAX 100; }
		REAL SPLINEDEFORMEROBJECT_RADIUS      { MIN 0; UNIT METER; }
    BOOL SPLINEDEFORMEROBJECT_USE_LENGTH { }
    BOOL SPLINEDEFORMEROBJECT_USE_POLYS { }
    SPLINE  SPLINEDEFORMEROBJECT_SPLINECONTROL { SHOWGRID_H; SHOWGRID_V; GRIDSIZE_H 8; GRIDSIZE_V 8; HAS_PRESET_BTN; MINSIZE_H 120;
                                      MINSIZE_V 90; EDIT_H; EDIT_V; LABELS_H; LABELS_V; HAS_ROUND_SLIDER;
                                      X_MIN 0; X_MAX 100; Y_MIN 0; Y_MAX 1; X_STEPS 1; Y_STEPS 1; }
	}
}
