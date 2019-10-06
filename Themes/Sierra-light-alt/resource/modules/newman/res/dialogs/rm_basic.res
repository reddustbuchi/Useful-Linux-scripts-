DIALOG RM_BASIC
{
	FIT_H;
	SCALE_H;
	GROUP
	{
		BORDERSIZE 4,4,4,4;
		SPACE 4,4;
		COLUMNS 1;
		FIT_H;
		SCALE_H; 
		GROUP
		{
				
			SCALE_H;
			FIT_H; 
			
			GROUP
			{
				COLUMNS 2;
				SCALE_H;
				FIT_H; 

				GROUP
				{
					USERAREA ID_RM_BA_USER { CENTER_V; CENTER_H; SIZE 150, 130; }
				}
				
				GROUP
				{
					COLUMNS 2;
					SCALE_H;
					FIT_H; 
					
					STATICTEXT ID_RM_BA_JOB {NAME IDS_JOB; CENTER_V; ALIGN_LEFT; }
					STATICTEXT ID_RM_BA_JOBTEXT {NAME IDS_EMPTY; CENTER_V; SCALE_H; }
					STATICTEXT ID_RM_BA_MESSAGE {NAME IDS_MESSAGE; CENTER_V; ALIGN_LEFT; }
					STATICTEXT ID_RM_BA_MESSAGETXT {NAME IDS_EMPTY; CENTER_V; SCALE_H;}
					STATICTEXT ID_RM_BA_NAME {NAME IDS_NAME; CENTER_V; ALIGN_LEFT; }
					STATICTEXT ID_RM_BA_NAMETXT {NAME IDS_EMPTY; CENTER_V; SCALE_H; }
					STATICTEXT ID_RM_BA_QUEUE {NAME IDS_QUEUE; CENTER_V; ALIGN_LEFT; }
					STATICTEXT ID_RM_BA_QUEUETXT {NAME IDS_EMPTY; CENTER_V; SCALE_H; }
					STATICTEXT ID_RM_BA_OUTPUTSTR {NAME IDS_OPATH; CENTER_V; ALIGN_LEFT; }
					STATICTEXT ID_RM_BA_OUTPUTSTRTXT {NAME IDS_EMPTY; CENTER_V; SCALE_H;}
					STATICTEXT ID_RM_BA_MPSTR {NAME IDS_MPATH; CENTER_V; ALIGN_LEFT; }
					STATICTEXT ID_RM_BA_OUTPUTMULTISTRTXT {NAME IDS_EMPTY; CENTER_V;SCALE_H;}
				}
			
			}
		}
		
		SEPARATOR {SCALE_H;}
		GROUP
		{
			COLUMNS 2;
			SCALE_H;
			FIT_H; 
			
			GROUP
			{
				COLUMNS 2;
				SCALE_H;
				STATICTEXT ID_RM_BA_START {NAME IDS_START; CENTER_V; ALIGN_LEFT; }
				STATICTEXT ID_RM_BA_STARTTXT {NAME IDS_EMPTY; CENTER_V; SCALE_H; }
				STATICTEXT ID_RM_BA_RTIME {NAME IDS_RTIME; CENTER_V; ALIGN_LEFT; }
				STATICTEXT ID_RM_BA_RTIMETXT {NAME IDS_EMPTY; CENTER_V; SCALE_H;}
			}
			GROUP
			{
				SCALE_H;
				COLUMNS 2;
			
				STATICTEXT ID_RM_BA_ETIME {NAME IDS_ETIME; CENTER_V; ALIGN_LEFT; }
				STATICTEXT ID_RM_BA_ETIMETXT {NAME IDS_EMPTY; CENTER_V; SCALE_H;}
				STATICTEXT ID_RM_BA_LFRAME {NAME IDS_LFRAME; CENTER_V; ALIGN_LEFT; }
				STATICTEXT ID_RM_BA_LFRAMETXT {NAME IDS_EMPTY; CENTER_V; SCALE_H; }
			}
		}

 		GROUP
 		{
 			SCALE_H;
 			FIT_H; 

 			COLUMNS 1;
 			GROUP
 			{
				ALIGN_TOP;  
                BORDERSTYLE BORDER_THIN_IN; BORDERSIZE 0, 0, 0, 0; 
                COLUMNS 1;
                SCALE_H;
                FIT_H; 
                          
               PROGRESSBAR ID_RM_BA_PROG { CENTER_V; SCALE_H;  SIZE 100,15; }
                        
            }
            GROUP
			{
				SCALE_H;
				FIT_H; 

				COLUMNS 3;
	            
				STATICTEXT ID_RM_BA_LEFT {NAME IDS_EMPTY;  CENTER_V; ALIGN_LEFT; SCALE_H; }
				STATICTEXT ID_RM_BA_CENTER {NAME IDS_EMPTY; CENTER_V; CENTER_H; SCALE_H; }
				STATICTEXT ID_RM_BA_RIGHT {NAME IDS_EMPTY;CENTER_V; ALIGN_RIGHT; }
			}
 		}
 		

		
		
		SEPARATOR {SCALE_H;}
		
		GROUP
		{
			COLUMNS 1;
			SCALE_H;
			FIT_H; 
			GROUP
			{
			  COLUMNS 4;
			  SCALE_H;
			  
			  STATICTEXT {NAME IDS_RENDER; CENTER_V; ALIGN_LEFT; }
			  COMBOBOX ID_RM_BA_RENDER
			  {
				SCALE_V;
				SCALE_H;
				SIZE 100, 0; 
			  
				CHILDS
				{
				}
			  }
			  
  			  STATICTEXT {NAME IDS_CAMERA; CENTER_V; ALIGN_LEFT; }
  			  COMBOBOX ID_RM_BA_CAMERA
  			  {
  				SCALE_V;
  				SCALE_H;
  				SIZE 100, 0; 
	  		  
  				CHILDS
  				{
  				}
  			  }
			}

			}
			
			GROUP
			{
			  COLUMNS 2;
			  SCALE_H;
			  FIT_H;

			  STATICTEXT { NAME IDS_OPATH;CENTER_V; ALIGN_LEFT; }
			  
			  FILENAME ID_RM_BA_OPATH {CENTER_V; SCALE_H;  SIZE 400,0; SAVE; }
			  STATICTEXT {CENTER_V; ALIGN_LEFT; }
			  STATICTEXT { NAME IDS_WARNING;CENTER_V; ALIGN_LEFT; }
			  
			  STATICTEXT { NAME IDS_MPATH;CENTER_V; ALIGN_LEFT;}
			  FILENAME ID_RM_BA_MPATH {CENTER_V; SCALE_H;FIT_H;SIZE 400,0; SAVE; }
			  
			  STATICTEXT ID_RM_BA_LOGPATHTXT {CENTER_V; ALIGN_LEFT; NAME IDS_LOGPATH;}
			  FILENAME ID_RM_BA_LOGPATH {CENTER_V; SCALE_H;FIT_H; SIZE 400,0; DIRECTORY; }
			  
			}
			
		}
	}
}
