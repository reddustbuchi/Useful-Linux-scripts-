CONTAINER ToolPolySelection
{
	NAME ToolPolySelection;
	INCLUDE ToolBase;
	INCLUDE ToolModelingAxis;
	INCLUDE ToolSoftSelection;

	GROUP MDATA_MAINGROUP
	{
		BOOL MDATA_SELECTION_TOLERANCE	{ }
		BOOL MDATA_SELECTION_VISIBLE	{ }
	}

	HIDE MDATA_COMMANDGROUP;
}
