CONTAINER Oeformula
{
	NAME		Oeformula;

	INCLUDE Obaseeffector;

	GROUP		ID_MG_BASEEFFECTOR_GROUPEFFECTOR
	{
		GROUP
		{
			COLUMNS 1;
			STRING	MGFORMULAEFFECTOR_STRING {}
		}
		GROUP MGFORMULAEFFECTOR_GRP
		{
			COLUMNS 1;
			STATICTEXT	MGFORMULAEFFECTOR_HELP02 {}
			STATICTEXT	MGFORMULAEFFECTOR_HELP03 {}
			STATICTEXT	MGFORMULAEFFECTOR_HELP04 {}
			STATICTEXT	MGFORMULAEFFECTOR_HELP05 {}
			STATICTEXT	MGFORMULAEFFECTOR_HELP06 {}
			STATICTEXT	MGFORMULAEFFECTOR_HELP07 {}
			STATICTEXT	MGFORMULAEFFECTOR_HELP08 {}
			GROUP
			{
				REAL	MGFORMULAEFFECTOR_TIME
				{
					MINSLIDER -1.0;
					MAXSLIDER 1.0;
					STEP 0.001;
					CUSTOMGUI REALSLIDER;
				}
				REAL	MGFORMULAEFFECTOR_FREQ
				{
					MINSLIDER -1.0;
					MAXSLIDER 1.0;
					STEP 0.001;
					CUSTOMGUI REALSLIDER;
				}
			}
		}
	}
}
