// C4D-DialogResource

DIALOG P_PAINT_COLORSOURCE
{
  NAME TITLE;

	SCALE_H;
	SCALE_V;

	SCROLLGROUP
	{
		SCROLL_AUTO_V;
		SCROLL_AUTO_H;
		SCALE_H;
		SCALE_V;

		GROUP
		{
			COLUMNS 1;
			SCALE_H;
			SPACE 4,2;

			GROUP IDC_COLORSOURCE_GROUP_CHANNELS
			{
				COLUMNS 1;
				SPACE 4,1;
				SCALE_H;
				QUICKTAB { SCALE_H; BAR; BARTITLE TCHN; }
				USERAREA IDC_COLORSOURCE_CHANNELS { SCALE_H; }
			}

			GROUP IDC_COLORSOURCE_GROUP_PREVIEW
			{
				COLUMNS 1;
				SCALE_H;
				SPACE 4,2;

				QUICKTAB { SCALE_H; BAR; BARTITLE T2; }

				GROUP 
				{
					SCALE_H;
					SPACE 4,1;
					ROWS 1;

//					GROUP
//					{
//						FIT_H;
//						FIT_V;
//						BORDERSIZE 1,1,1,1;
//						BORDERSTYLE BORDER_THIN_IN;
//						BITMAPBUTTON IDC_COLORSOURCE_PREVIEW { SIZE -50,0; SCALE_V; IGNORE_BITMAP_HEIGHT; }
//					}

					GROUP
					{
						SCALE_H;
						SPACE 4,1;
						ROWS 1;
						
						EDITSLIDER IDC_COLORSOURCE_STRENGTH { SIZE 50,11; SCALE_H; }
						COMBOBOX IDC_COLORSOURCE_BLENDING
						{
							SIZE 0,11;
							CHILDS 
							{
								0, TL0;
								0, TSEP;
								1, TL1;
								2, TL2;
								3, TL3;
								4, TL4;
								5, TL5;
								6, TL6;
								7, TL7;
								8, TL8;
								9, TL9;
							}
						}						
					}
				}
			}
				
			GROUP IDC_COLORSOURCE_GROUP_COLOR
			{
				COLUMNS 1;
				SCALE_H;
				SPACE 4,2;

				QUICKTAB { SCALE_H; BAR; BARTITLE TCOLOR; }

				GROUP 
				{
					COLUMNS 2;

					RADIOGADGET IDC_COLORSOURCE_SOLIDCOLOR { NAME T4; }
					RADIOGADGET IDC_COLORSOURCE_TEXTURE { NAME T5; }
				}

				TAB IDC_COLORSOURCE_TAB
				{
					SELECTION_NONE;
					SCALE_H;
					FIT_V;

					GROUP IDC_COLORSOURCE_TABSOLIDCOLOR
					{
						SCALE_H; SCALE_V;
						COLUMNS 1;
						COLORFIELD IDC_COLORSOURCE_RGB { SCALE_H; SCALE_V; ICC_BPTEXTURE; }
					}

					GROUP IDC_COLORSOURCE_TABTEXTURE
					{
						SCALE_H; FIT_V; COLUMNS 1;

						GROUP
						{
							COLUMNS 2;
							SCALE_H;

							GROUP
							{
								FIT_V;
								BORDERSIZE 1,1,1,1;
								BORDERSTYLE BORDER_THIN_IN;
								USERAREA IDC_COLORSOURCE_TEXTURE_PREVIEW { SIZE 50,0; SCALE_V; }
							}

							GROUP
							{
								SCALE_H;
								ROWS 1;
								SPACE 1,0;

								POPUPBUTTON IDC_COLORSOURCE_TEXTUREPOPUP { FIT_V; }

								GROUP
								{
									SCALE_H;
									FIT_V;
									BORDERSIZE 1,1,1,1;
									BORDERSTYLE BORDER_THIN_IN;
									STATICTEXT IDC_COLORSOURCE_TEXTURENAME { SCALE_H; SIZE 50,11; }
								}
							}
						}

						GROUP IDC_COLORSOURCE_TEXTUREGROUP
						{
							SCALE_H; FIT_V; COLUMNS 3;
							SPACE 4,1;

							STATICTEXT { NAME T7; }
							GROUP
							{
								SCALE_H; FIT_V; COLUMNS 2;
								SPACE 1,1;
								
								EDITNUMBERARROWS IDC_COLORSOURCE_TEXTURE_SX { SCALE_H; SIZE 40,11; }
								EDITNUMBERARROWS IDC_COLORSOURCE_TEXTURE_SY { SCALE_H; SIZE 40,11; }
							}
							CHECKBOX IDC_COLORSOURCE_TEXTURE_TILING { NAME T8; }

							STATICTEXT { NAME T9; }
							GROUP
							{
								SCALE_H; FIT_V; ROWS 1;
								SPACE 1,1;
								EDITNUMBERARROWS IDC_COLORSOURCE_TEXTURE_DX { SCALE_H; SIZE 40,11; }
								EDITNUMBERARROWS IDC_COLORSOURCE_TEXTURE_DY { SCALE_H; SIZE 40,11; }
							}

							COMBOBOX IDC_COLORSOURCE_TEXTUREDEST
							{
								SIZE 70,11;
								FIT_H;
								CHILDS 
								{
									0, TN0;
									1, TN1;
									2, TN2;
								}
							}
						}

						GROUP IDC_COLORSOURCE_TEXTUREGROUP
						{
							SCALE_H; FIT_V; COLUMNS 2;
							SPACE 4,1;


							GROUP
							{
								ROWS 1;
								CHECKBOX IDC_COLORSOURCE_TEXTURE_SCALE_ON { }
								DESCRIPTIONPROPERTY IDC_COLORSOURCE_TEXTURE_SCALE_MOD { NAME T10; }
							}
							EDITSLIDER IDC_COLORSOURCE_TEXTURE_SCALE { SCALE_H; SIZE 50,11; }

							GROUP
							{
								ROWS 1;
								CHECKBOX IDC_COLORSOURCE_TEXTURE_ROTATION_ON { }
								DESCRIPTIONPROPERTY IDC_COLORSOURCE_TEXTURE_ROTATION_MOD { NAME T11; }
							}
							EDITSLIDER IDC_COLORSOURCE_TEXTURE_ROTATION { SCALE_H; SIZE 50,11; }
						}
					}
				}
			}

			GROUP IDC_COLORSOURCE_GROUP_MIXING
			{
				SCALE_H;
				COLUMNS 1;
				SPACE 4,2;

				QUICKTAB { SCALE_H; BAR; BARTITLE T6; }

				GROUP
				{
					COLUMNS 2;
					SCALE_H;

					GROUP
					{
						FIT_V;
						BORDERSIZE 1,1,1,1;
						BORDERSTYLE BORDER_THIN_IN;
						USERAREA IDC_COLORSOURCE_WALLPAPERPREVIEW { SIZE 50,0; SCALE_V; }
					}
					
					GROUP
					{
						SCALE_H;
						ROWS 1;
						SPACE 1,0;

						POPUPBUTTON IDC_COLORSOURCE_WALLPAPERPOPUP { FIT_V; }

						GROUP
						{
							SCALE_H;
							FIT_V;
							BORDERSIZE 1,1,1,1;
							BORDERSTYLE BORDER_THIN_IN;
							STATICTEXT IDC_COLORSOURCE_WALLPAPERNAME { SCALE_H; SIZE 50,11; }
						}
					}
				}

				GROUP IDC_COLORSOURCE_WALLPAPERGROUP
				{
					SCALE_H; FIT_V;
					COLUMNS 1;

					GROUP
					{
						SCALE_H;
						COLUMNS 2;
						
						EDITSLIDER IDC_COLORSOURCE_WALLPAPERSTRENGTH { SCALE_H; SIZE 50,11; }

						COMBOBOX IDC_COLORSOURCE_WALLPAPERBLENDING
						{
							SIZE 0,11;
							CHILDS 
							{
								0, TL0;
								0, TSEP;
								1, TL1;
								2, TL2;
								3, TL3;
								4, TL4;
								5, TL5;
								6, TL6;
								7, TL7;
								8, TL8;
								9, TL9;
							}
						}
					}
				}

				CHECKBOX IDC_COLORSOURCE_IGNOREFILTER { NAME T3; }
			}
		}
	}
}
