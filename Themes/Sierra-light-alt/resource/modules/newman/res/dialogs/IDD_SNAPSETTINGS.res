// C4D-DialogResource
DIALOG IDD_SNAPSETTINGS
{
  NAME IDS_DIALOG; CENTER_V; CENTER_H; 
  
  GROUP IDC_STATIC
  {
    FIT_V; FIT_H; 
    BORDERSTYLE BORDER_NONE; BORDERSIZE 4, 4, 4, 4; 
    ROWS 2;
    EQUAL_ROWS; 
    SPACE 4, 4;
    
    GROUP IDC_GROUP_GENERAL
    {
      NAME IDS_STATICGENERAL; ALIGN_TOP; ALIGN_LEFT; 
      BORDERSTYLE BORDER_GROUP_IN; BORDERSIZE 4, 4, 4, 4; 
      COLUMNS 2;
      SPACE 4, 4;
      
      CHECKBOX IDC_SNAP_PRJIN { NAME IDS_PRJIN; ALIGN_TOP; ALIGN_LEFT;  }
      CHECKBOX IDC_SNAP_PRJOUT { NAME IDS_PRJOUT; ALIGN_TOP; ALIGN_LEFT;  }
      CHECKBOX IDC_SNAP_CURTIME { NAME IDS_CURTIME; ALIGN_TOP; ALIGN_LEFT;  }
      CHECKBOX IDC_SNAP_PREVIEW { NAME IDS_PREVIEW; ALIGN_TOP; ALIGN_LEFT;  }
      CHECKBOX IDC_SNAP_MARKER { NAME IDS_MARKER; ALIGN_TOP; ALIGN_LEFT;  }
      CHECKBOX IDC_SNAP_KEY { NAME IDS_KEY; ALIGN_TOP; ALIGN_LEFT;  }
      CHECKBOX IDC_SNAP_CLIP { NAME IDS_CLIP; ALIGN_TOP; ALIGN_LEFT;  }
      GROUP 
      {
        ALIGN_TOP; ALIGN_LEFT; 
        BORDERSIZE 0, 0, 0, 0; 
        COLUMNS 2;
        SPACE 4, 4;
        
        STATICTEXT IDC_SNAP_TEXT1 { NAME IDS_SNAP_STATIC; CENTER_V; ALIGN_LEFT; }
        EDITNUMBERARROWS IDC_SNAP_DISTANCE
        { CENTER_V; CENTER_H; SIZE 100, 0; }
      }
    }
    GROUP IDC_GROUP_FCURVE
    {
      NAME IDS_STATICFC; ALIGN_TOP; ALIGN_LEFT; 
      BORDERSTYLE BORDER_GROUP_IN; BORDERSIZE 4, 4, 4, 4; 
      COLUMNS 2;
      SPACE 4, 4;
      
      CHECKBOX IDC_SNAP_F_KEY { NAME IDS_F_KEY; ALIGN_TOP; ALIGN_LEFT;  }
      CHECKBOX IDC_SNAP_F_GRID { NAME IDS_F_GRID; ALIGN_TOP; ALIGN_LEFT;  }
      GROUP 
      {
        ALIGN_TOP; ALIGN_LEFT; 
        BORDERSIZE 0, 0, 0, 0; 
        COLUMNS 2;
        SPACE 4, 4;
        
        STATICTEXT IDC_SNAP_TEXT2 { NAME IDS_SNAP_STATIC1; CENTER_V; ALIGN_LEFT; }
        EDITNUMBERARROWS IDC_SNAP_DISTANCE2
        { CENTER_V; CENTER_H; SIZE 70, 0; }
      }
    }
  }
}