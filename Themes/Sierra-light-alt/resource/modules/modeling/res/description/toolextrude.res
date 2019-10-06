CONTAINER ToolExtrude
{
  NAME ToolExtrude;
	INCLUDE ToolBase;

  GROUP MDATA_MAINGROUP
  {
	  GROUP
	  {
			COLUMNS 2;
			REAL MDATA_EXTRUDE_ANGLE { UNIT DEGREE; }
			STATICTEXT { JOINEND; }

			REAL MDATA_EXTRUDE_OFFSET { UNIT METER; }
			REAL MDATA_EXTRUDE_VARIANCE { UNIT PERCENT; MIN 0; MAX 200; }
			REAL MDATA_EXTRUDE_BEVEL { UNIT METER; }
			REAL MDATA_EXTRUDE_BEVEL_VARIANCE { UNIT PERCENT; MIN 0; MAX 200; }
			

			LONG MDATA_EXTRUDE_SUBDIVISION { MIN 0; }
			STATICTEXT { JOINEND; }
			BOOL MDATA_EXTRUDE_CREATENGONS { }
			BOOL MDATA_EXTRUDE_CREATECAPS { }
			STATICTEXT { JOINEND; }

			REAL MDATA_EXTRUDE_EDGEANGLE { UNIT DEGREE; }
			STATICTEXT { JOINEND; }
			BOOL MDATA_EXTRUDE_EDGESNAP { }
			REAL MDATA_EXTRUDE_EDGESNAPVALUE { UNIT DEGREE; }
			STATICTEXT { JOINEND; }

			BOOL MDATA_EXTRUDE_PRESERVEGROUPS { }
			STATICTEXT { JOINEND; }

			//BOOL MDATA_EXTRUDE_KEEPSEL { }
			STATICTEXT { JOINEND; }
		}
	}
}
