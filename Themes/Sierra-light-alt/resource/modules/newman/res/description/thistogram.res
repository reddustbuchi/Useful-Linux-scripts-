CONTAINER Thistogram
{
	NAME Thistogram;
	
	GROUP HISTOGRAM_PROPERTIES
	{
		GROUP
		{
			BITMAPBUTTON	HISTOGRAM_IMAGE
			{
				FIT_H;
				BORDER;
			}
		}
		
		GROUP
		{
		BOOL HISTOGRAM_RED {}
		BOOL HISTOGRAM_GREEN {}			
		BOOL HISTOGRAM_BLUE {}
		BOOL HISTOGRAM_LUMA {}	
		}	
	}
}
