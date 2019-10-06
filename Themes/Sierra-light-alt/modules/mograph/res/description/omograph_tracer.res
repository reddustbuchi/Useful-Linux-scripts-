CONTAINER Omograph_tracer
{
	NAME		Omograph_tracer;
	INCLUDE Obase;

	GROUP		ID_OBJECTPROPERTIES
	{
		GROUP
		{
			COLUMNS 2;

			IN_EXCLUDE	MGTRACEROBJECT_OBJECTLIST
			{
				ACCEPT
				{
					Obase;
					1001381;
				}
				REFUSE
				{
					GVbase;
					VPbase;
					Tbase;
					Mbase;
				}
			}
			STATICTEXT { JOINEND; }

			SEPARATOR
			{
				LINE;
			}
			STATICTEXT { JOINEND; }

			LONG	MGTRACEROBJECT_MODE
			{
				FIT_H;
				CYCLE
				{
					MGTRACEROBJECT_MODE_TRACE;
					MGTRACEROBJECT_MODE_LINK;
					MGTRACEROBJECT_MODE_SEGLINK;
				}
			}
			STATICTEXT { JOINEND; }

			LONG	MGTRACEROBJECT_SAMPLESTEP
			{
				MIN 1;
			}
			BOOL	MGTRACEROBJECT_ACTIVE
			{
			}
			BOOL	MGTRACEROBJECT_USEPOINTS
			{
			}
			BOOL	MGTRACEROBJECT_USETPSUBGROUPS
			{
			}
			LONG	MGTRACEROBJECT_MGMODE
			{
				FIT_H;
				CYCLE
				{
					MGTRACEROBJECT_MGMODE_SINGLE;
					MGTRACEROBJECT_MGMODE_CHILDS;
					MGTRACEROBJECT_MGMODE_ACHILDS;
				}
			}
			BOOL	MGTRACEROBJECT_INCLUDECLONER
			{
			}

			SEPARATOR { LINE; }
			STATICTEXT { JOINEND; }

			LONG	MGTRACEROBJECT_SPACE
			{
				CYCLE
				{
					MGTRACEROBJECT_SPACE_GLOBAL;
					MGTRACEROBJECT_SPACE_LOCAL;
				}
			}
			STATICTEXT { JOINEND; }

			LONG	MGTRACEROBJECT_LIMITMODE
			{
				CYCLE
				{
					MGTRACEROBJECT_LIMITMODE_NONE;
					MGTRACEROBJECT_LIMITMODE_START;
					MGTRACEROBJECT_LIMITMODE_END;
				}
			}
			LONG	MGTRACEROBJECT_LIMITMODE_AMMOUNT
			{
				MIN 1;
			}
		}
		SEPARATOR
		{
			LINE;
		}
		INCLUDE Ospline;

		BOOL		MGTRACEROBJECT_REVERSESPLINE
		{
		}
	}
}
