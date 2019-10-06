CONTAINER GVcollision
{
	NAME GVcollision;
	INCLUDE GVbase;

	GROUP ID_GVPROPERTIES
	{
		LONG GV_COLLISION_TYPE
		{ 
			CYCLE 
			{ 
				GV_COLLISION_OPERATOR_TYPE_CUBE;
				GV_COLLISION_OPERATOR_TYPE_SPHERE;
				GV_COLLISION_OPERATOR_TYPE_POLYGON;
				GV_COLLISION_OPERATOR_TYPE_DISTANCE;
				GV_COLLISION_OPERATOR_TYPE_TOLERANCE;
			}
		}
		BOOL GV_COLLISION_USE_DEFORMED { }
		LONG GV_COLLISION_MODE { CYCLE { GV_COLLISION_OPERATOR_MODE_GLOBAL; GV_COLLISION_OPERATOR_MODE_LOCAL; } }
		BOOL GV_COLLISION_USE_HIERARCHY { }
		LINK GV_COLLISION_SELECTION1 { ACCEPT { Tpolygonselection; } }
		LINK GV_COLLISION_SELECTION2 { ACCEPT { Tpolygonselection; } }
	}

	GROUP ID_GVPORTS
	{
		GVGENERALOBJECT GV_COLLISION_INPUT_OBJECT1 { INPORT; STATICPORT; CREATEPORT; }
		GVGENERALOBJECT GV_COLLISION_INPUT_OBJECT2 { INPORT; STATICPORT; CREATEPORT; }
		REAL GV_COLLISION_INPUT_TOLERANCE { INPORT; MIN 0; }
		
		BOOL GV_COLLISION_OUTPUT { OUTPORT; STATICPORT; CREATEPORT; }
		REAL GV_COLLISION_OUTPUT_DISTANCE { OUTPORT; }
		LONG GV_COLLISION_OUTPUT_INDEX1 { OUTPORT; }
		LONG GV_COLLISION_OUTPUT_INDEX2 { OUTPORT; }
		VECTOR GV_COLLISION_OUTPUT_POINT1 { OUTPORT; }
		VECTOR GV_COLLISION_OUTPUT_POINT2 { OUTPORT; }
	}
}