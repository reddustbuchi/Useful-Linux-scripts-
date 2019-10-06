enum
{
	// Shader names
	IDS_SLA_GRADIENT = 1000,
	IDS_SLA_FALLOFF,
	IDS_SLA_TILES,
	IDS_SLA_FRESNEL,
	IDS_SLA_LUMAS,
	IDS_SLA_PROXIMAL,
	IDS_SLA_BUFFY,
	IDS_SLA_BANJ,
	IDS_SLA_FUSION,
	IDS_SLA_POSTERIZER,
	IDS_SLA_COLORIZER,
	IDS_SLA_HUE,
	IDS_SLA_DISTORTER,
	IDS_SLA_PROJECTOR,
	IDS_SLA_NOISE,
	IDS_SLA_LAYER,
	IDS_SLA_SPLINE,
	IDS_SLA_FILTER,

	IDS_NUKEI_TIME,
	IDS_NUKEI_SPEED,
	IDS_SPLINE_TEXT_DEFAULT,

	// Material names
	IDS_SLA_DANEL,
	IDS_SLA_BANJI,
	IDS_SLA_BANZI,
	IDS_SLA_CHEEN,
	IDS_SLA_MABEL,
	IDS_SLA_NUKEI,
	IDS_SLA_WAVE,

	// blend
	IDS_DATATYPE_BLEND,
	IDS_ADD_IMAGE,
	IDS_ADD_SHADER,
	IDS_DELETE,
	IDS_ADD_FOLDER,
	IDS_ADD_EFFECT,
	IDS_BLEND_MODE_NORMAL,
	IDS_BLEND_MODE_MULTIPLY,
	IDS_BLEND_MODE_SCREEN,
	IDS_BLEND_MODE_OVERLAY,
	IDS_BLEND_MODE_HARD_LIGHT,
	IDS_BLEND_MODE_SOFT_LIGHT,
	IDS_BLEND_MODE_DODGE,
	IDS_BLEND_MODE_BURN,
	IDS_BLEND_MODE_DARKEN,
	IDS_BLEND_MODE_LIGHTEN,
	IDS_BLEND_MODE_ADD,
	IDS_BLEND_MODE_SUBTRACT,
	IDS_BLEND_MODE_DIFFERENCE,
	IDS_BLEND_MODE_EXCLUSION,
	IDS_BLEND_MODE_HUE,
	IDS_BLEND_MODE_SAT,
	IDS_BLEND_MODE_COLOR,
	IDS_BLEND_MODE_LUMINANCE,
	IDS_BLEND_MODE_LEVR,
	IDS_BELND_USE_AS_ALPHA,

	IDS_BRIGHTNESS,
	IDS_CONTRAST,
	IDS_GAMMA,
	IDS_HUE,
	IDS_SATURATION,
	IDS_LIGHTNESS,
	IDS_COLORIZE,
	IDS_LEVELS,
	IDS_WIDTH,
	IDS_INPUT,
	IDS_GRADIENT,
	IDS_COL_LUM,
	IDS_COL_HUE,
	IDS_COL_SAT,
	IDS_COL_LIGHT,
	IDS_COL_RED,
	IDS_COL_GREEN,
	IDS_COL_BLUE,
	IDS_CYCLE,
	IDS_HIGH_CLIP,
	IDS_LOW_CLIP,
	IDS_HIGH_CLAMP,
	IDS_LOW_CLAMP,
	IDS_ANGLE,
	IDS_MIRROR,
	IDS_FLIP,
	IDS_SCALE,
	IDS_MOVE,
	IDS_DISTORTION_STRENGTH,
	IDS_DISTORTION_3D,
	IDS_DISTORTION_NOISE,
	IDS_DISTORTION_WRAP,
	IDS_WRAP_NONE,
	IDS_WRAP_CLAMP,
	IDS_WRAP_CYCLE,
	IDS_WRAP_SEAMLESS,
	IDS_OCTAVES,
	IDS_TIMESCALE,
	IDS_NOISESCALE,
	IDS_SAMPLE_DISTANCE,
	IDS_SPACE,
	IDS_SPACE_UV,
	IDS_SPACE_OBJECT,
	IDS_SPACE_WORLD,
	IDS_STRENGTH,
	IDS_SUBSAMPLING,

	IDS_OUTPUT_INV_IMG,
	IDS_OUTPUT_INV_IMG_OFF,
	IDS_ALPHA_FLAGS_OFF,
	IDS_ALPHA_FLAGS_ON,
	IDS_ALPHA_FLAGS_INVERT,
	IDS_BLEND_INVERT_IMAGE,
	IDS_BLEND_USE_ALPHA,
	IDS_BLEND_INVERT_ALPHA,
	IDS_BLEND_IMAGE_ALPHA,
	IDS_BLEND_REMOVE,
	IDS_FOLDER,
	IDS_EMPTY,
	IDS_BLEND,
	IDS_MENU_BRIGHTNESS_CONTRAST,
	IDS_MENU_HSL,
	IDS_MENU_POSTERIZER,
	IDS_MENU_COLORIZER,
	IDS_MENU_CLAMP,
	IDS_MENU_CLIP,
	IDS_MENU_TRANSFORM,
	IDS_MENU_EASY_DISTORTER,
	IDS_BRIGHTNESS_CONTRAST,
	IDS_HSL,
	IDS_POSTERIZER,
	IDS_COLORIZER,
	IDS_CLAMP,
	IDS_CLIP,
	IDS_TRANSFORM,
	IDS_EASY_DISTORTER,

	// noise names
	IDS_SLA_NOISE_BOX_NOISE,
	IDS_SLA_NOISE_BLIST_TURB,
	IDS_SLA_NOISE_BUYA,
	IDS_SLA_NOISE_CELL_NOISE,
	IDS_SLA_NOISE_CRANAL,
	IDS_SLA_NOISE_DENTS,
	IDS_SLA_NOISE_DISPL_TURB,
	IDS_SLA_NOISE_FBM,
	IDS_SLA_NOISE_HAMA,
	IDS_SLA_NOISE_LUKA,
	IDS_SLA_NOISE_MOD_NOISE,
	IDS_SLA_NOISE_NAKI,
	IDS_SLA_NOISE_NOISE,
	IDS_SLA_NOISE_NUTOUS,
	IDS_SLA_NOISE_OBER,
	IDS_SLA_NOISE_PEZO,
	IDS_SLA_NOISE_POXO,
	IDS_SLA_NOISE_RANDOM,
	IDS_SLA_NOISE_SEMA,
	IDS_SLA_NOISE_STUPL,
	IDS_SLA_NOISE_TURBULENCE,
	IDS_SLA_NOISE_VL_NOISE,
	IDS_SLA_NOISE_WAVY_TURB,
	IDS_SLA_NOISE_FIRE,
	IDS_SLA_NOISE_ELECTRIC,
	IDS_SLA_NOISE_GASEOUS,
	IDS_SLA_NOISE_CELL_VORONOI,
	IDS_SLA_NOISE_DISPL_VORONOI,
	IDS_SLA_NOISE_SPARSE_CONV,
	IDS_SLA_NOISE_VORONOI_1,
	IDS_SLA_NOISE_VORONOI_2,
	IDS_SLA_NOISE_VORONOI_3,
	IDS_SLA_NOISE_ZADA,
	IDS_SLA_NOISE_NONE,
	IDS_NOISE_GUI,

	// Baker
	IDS_BAKER,
	IDS_BAKER_CANCEL_Q,
	IDS_BAKER_INITIALIZING,
	IDS_BAKER_NO_ACTIVE_DOC,
	IDS_BAKER_NO_RENDER_MEM,
	IDS_BAKER_NO_RENDER_DOC,
	IDS_BAKER_NO_ACTIVE_OBJ,
	IDS_BAKER_NO_TEX_TAG,
	IDS_BAKER_PROJ_UVW,
	IDS_BAKER_NO_UVW_TAG,
	IDS_BAKER_NO_SOURCE_UVW_TAG,
	IDS_BAKER_MEM_RENDER,
	IDS_BAKER_NO_TEX,
	IDS_BAKER_MEM_DATA_STRUCT,
	IDS_BAKER_NO_OPTIMAL_MAPPING,
	IDS_BAKER_SAMPLING_CHANNEL,
	IDS_BAKER_TAG,
	IDS_BAKER_CHANNEL_AMBIENT_OCCLUSION,
	IDS_BAKER_CHANNEL_NORMAL,
	IDS_BAKER_CHANNEL_S_COLOR,
	IDS_BAKER_CHANNEL_COLOR,
	IDS_BAKER_CHANNEL_LUMINANCE,
	IDS_BAKER_CHANNEL_DIFFUSION,
	IDS_BAKER_CHANNEL_BUMP,
	IDS_BAKER_CHANNEL_ALPHA,
	IDS_BAKER_CHANNEL_TRANS,
	IDS_BAKER_CHANNEL_ILLUM,
	IDS_BAKER_CHANNEL_UVMAP,
	IDS_BAKER_CHANNEL_SHADOWS,
	IDS_BAKER_CHANNEL_REFLECTION,
	IDS_BAKER_CHANNEL_DISPLACEMENT,
	IDS_LAYER,
	IDS_FILE_ALREADY_EXIST,
	IDS_SEQUENCE_ALREADY_EXIST,
	IDS_BAKETEXTURE_COLOR_DEPTH_8,
	IDS_BAKETEXTURE_COLOR_DEPTH_16,
	IDS_BAKETEXTURE_COLOR_DEPTH_32,
	IDS_BAKER_PROGR_PREPARE,
	IDS_BAKER_PROGR_INIT,
	IDS_BAKER_PROGR_GI_PREPASS,
	IDS_BAKER_PROGR_CALC_TEX,
	IDS_BAKER_PROGR_COMPLETE,
	IDS_BITMAPSAVE_ERR,
	IDS_BITMAPSAVE_ERR_CONTINUE,
	IDS_BAKE_OBJECT,
	IDS_BAKE_OBJECT_HELP,
	IDS_BAKE_FILENAME_EMPTY,
	IDS_BAKE_OBJECT_STATUS,
	IDS_BAKE_TEX_ERR_NO_MEM,
	IDS_BAKE_TEX_ERR_TEXTURE_MISSING,
	IDS_BAKE_TEX_ERR_UNKNOWN,

	// Dirty
	IDS_DIRTY_MAP_NAME,
	IDS_SLA_DIRTY,
	IDS_SLA_DIRTY_VMAP,

	// Dialog definitions of IDD_BAKER_DIALOG start here
	IDD_BAKER_DIALOG,
	IDC_BAKER_CHANNEL_COMBO,
	ID_BAKER_CHANNEL_COLOR,
	ID_BAKER_CHANNEL_DIFFUSION,
	ID_BAKER_CHANNEL_LUMINANCE,
	ID_BAKER_CHANNEL_BUMP,
	ID_BAKER_CHANNEL_ALPHA,
	ID_BAKER_CHANNEL_ILLUMINATION,
	ID_BAKER_CHANNEL_SHADOWS,
	ID_BAKER_CHANNEL_COMPOSITE,
	IDC_BAKER_ILLUMINATION_CHK,
	IDC_BAKER_SHADOWS_CHK,
	IDC_BAKER_LUMINANCE_CHK,
	IDC_BAKER_DIFFUSION_CHK,
	IDC_BAKER_BUMP_CHK,
	IDC_BAKERK_CAMERA_VECTOR_CHK,
	IDC_BAKER_PREVIEW,
	IDC_BAKER_BAKE_TO_UV_CHK,
	IDC_BAKER_USE_POLYSEL_CHK,
	IDC_BAKER_X_RESOLUTION_EDIT,
	IDC_BAKER_Y_RESOLUTION_EDIT,
	IDC_BAKER_BUFFER_SIZE_EDIT,
	IDC_BAKER_FILL_COLOR,
	IDC_BAKER_FILENAME_PATH_BTN,
	IDC_BAKER_FILENAME_PATH_EDIT,
	IDC_BAKER_FILETYPE_COMBO,
	ID_BAKER_TYPE_TIF,
	ID_BAKER_TYPE_TGA,
	ID_BAKER_TYPE_BMP,
	ID_BAKER_TYPE_IFF,
	ID_BAKER_TYPE_JPG,
	ID_BAKER_TYPE_PICT,
	ID_BAKER_TYPE_PSD,
	IDC_BAKER_START_BTN,
	IDC_BAKER_STOP_BTN,
	// Dialog definitions of IDD_BAKER_DIALOG end here

	// Dialog definitions of IDD_DIRTY_DIALOG start here
	IDD_DIRTY_DIALOG,
	IDC_DIRTY_MAPTYPE_COMBO,
	ID_DIRTY_MAP_VERTICE,
	ID_DIRTY_MAP_IMAGE,
	IDC_DIRTY_RAY_BIAS_EDIT,
	IDC_DIRTY_MAX_DISTANCE_EDIT,
	IDC_DIRTY_NUM_RAYS_EDIT,
	IDC_DIRTY_SPREAD_EDIT,
	IDC_DIRTY_CONTRAST_EDIT,
	IDC_DIRTY_SUBOBJECTS_NAME,
	IDC_DIRTY_SUBOBJECTS_CHK,
	IDC_DIRTY_PREVIEW,
	IDC_DIRTY_IMAGEGROUP,
	IDC_DIRTY_X_RESOLUTION_EDIT,
	IDC_DIRTY_Y_RESOLUTION_EDIT,
	IDC_DIRTY_BUFFER_SIZE_EDIT,
	IDC_DIRTY_FILL_COLOR,
	IDC_DIRTY_FILENAME_PATH_BTN,
	IDC_DIRTY_FILENAME_EDIT,
	IDC_DIRTY_FILENAME_TYPE_COMBO,
	ID_DIRTY_TYPE_TIF,
	ID_DIRTY_TYPE_TGA,
	ID_DIRTY_TYPE_BMP,
	ID_DIRTY_TYPE_IFF,
	ID_DIRTY_TYPE_JPG,
	ID_DIRTY_TYPE_PICT,
	ID_DIRTY_TYPE_PSD,
	IDC_DIRTY_START_BTN,
	IDC_DIRTY_STOP_BTN,
	// Dialog definitions of IDD_DIRTY_DIALOG end here

	// Dialog definitions of IDD_BAKE_OBJECT_DIALOG start here
	IDD_BAKE_OBJECT_DIALOG,
	IDC_BAKE_OBJECT_AO_CHK,
	IDC_BAKE_OBJECT_NORMAL_CHK,
	IDC_BAKE_OBJECT_KEEP_UV_CHK,
	IDC_BAKE_OBJECT_ILLUM_CHK,
	IDC_BAKE_OBJECT_SINGLE_TEX_CHK,
	IDC_BAKE_OBJECT_REPLACE_CHK,
	IDC_BAKE_OBJECT_SUPERSAMPLING_EDIT,
	IDC_BAKE_OBJECT_PBORDER_EDIT,
	IDC_BAKE_OBJECT_WIDTH_EDIT,
	IDC_BAKE_OBJECT_HEIGHT_EDIT,
	IDC_BAKE_OBJECT_FORMAT_COMBO,
	IDC_BAKE_OBJECT_BPP_COMBO,
	IDC_BAKE_OBJECT_OPTIONS_BTN,
	IDC_BAKE_OBJECT_COLOR_PROFILE,
	IDC_BAKE_OBJECT_PREVIEW,
	IDC_BAKE_OBJECT_FILENAME_EDIT,
	IDC_BAKE_OBJECT_BAKE_BTN,
	IDC_BAKE_OBJECT_CANCEL_BTN,
	// Dialog definitions of IDD_BAKE_OBJECT_DIALOG end here



 // Dialog definitions of IDD_SCULPT_BAKE_DIALOG start here
	IDD_SCULPTBAKE_DIALOG,

	IDC_SCULPTBAKE_OPTIONS, //Group
	IDC_SCULPTBAKE_BAKING, //Group
	IDC_SCULPTBAKE_SETTINGS, //Group

	IDS_SUBDIVISIONLEVEL,
	IDC_SCULPTBAKE_TARGETLEVEL_INCLUDETOP,

	IDC_SCULPTBAKE_PREVIEW,
	IDC_SCULPTBAKE_BAKE,
	IDC_SCULPTBAKE_STOP,
	IDC_SCULPTBAKE_DELETE,

	IDC_SCULPTBAKE_FILENAME,
	IDC_SCULPTBAKE_FORMAT,
	IDC_SCULPTBAKE_FORMAT_OPTIONS,
	IDC_SCULPTBAKE_COLORPROFILE,
	IDC_SCULPTBAKE_COLORDEPTH,
	IDC_SCULPTBAKE_WIDTH,
	IDC_SCULPTBAKE_HEIGHT,
	IDC_SCULPTBAKE_PIXELBORDER,
	IDC_SCULPTBAKE_BACKGROUND,
	IDC_SCULPTBAKE_PREVIEWIMAGE,
	IDC_SCULPTBAKE_SIZEPRESET,
	IDC_SCULPTBAKE_LOCKRATIO,

	IDC_SCULPTBAKE_MAPPING,
		IDC_SCULPTBAKE_MAPPING_OFF = 0,
		IDC_SCULPTBAKE_MAPPING_CUBIC = 1,
		IDC_SCULPTBAKE_MAPPING_ANGLE = 2,
	IDC_SCULPTBAKE_RELAXCOUNT,

	IDC_SCULPTBAKE_CHANNEL_DISPLACEMENT,
	IDC_SCULPTBAKE_CHANNEL_NORMAL,
	IDC_SCULPTBAKE_CHANNEL_AMBIENTOCCLUSION,
	IDC_SCULPTBAKE_CHANNEL_LUMINANCE,
	IDC_SCULPTBAKE_CHANNEL_DIFFUSION,
	IDC_SCULPTBAKE_CHANNEL_BUMP,
	IDC_SCULPTBAKE_CHANNEL_ALPHA,
	IDC_SCULPTBAKE_CHANNEL_TRANS,
	IDC_SCULPTBAKE_CHANNEL_S_COLOR,
	IDC_SCULPTBAKE_CHANNEL_ILLUMINATION,
	IDC_SCULPTBAKE_CHANNEL_SHADOWS,
	IDC_SCULPTBAKE_CHANNEL_REFLECTION,

	IDC_SCULPTBAKE_SOURCELIST,
	IDC_SCULPTBAKE_TARGETLIST,

	//Displacement
	IDC_SCULPTBAKE_DISPLACEMENT_SETTINGS,
	IDC_SCULPTBAKE_DISPLACEMENT_METHOD,
	IDC_SCULPTBAKE_DISPLACEMENT_METHOD_OBJECT,
	IDC_SCULPTBAKE_DISPLACEMENT_METHOD_TANGET,
	IDC_SCULPTBAKE_DISPLACEMENT_METHOD_WORLD,
	IDC_SCULPTBAKE_DISPLACEMENT_METHOD_INTENSITY,
	IDC_SCULPTBAKE_DISPLACEMENT_METHOD_INTENSITYCENTERED,
	IDC_SCULPTBAKE_DISPLACEMENT_METHOD_REDGREEN,
	IDC_SCULPTBAKE_DISPLACEMENT_ROUNDGEOMETRY,
	IDC_SCULPTBAKE_DISPLACEMENT_ROUNDCOUNTOUR,

	//Normal
	IDC_SCULPTBAKE_NORMAL_SETTINGS,
	IDC_SCULPTBAKE_NORMAL_METHOD,
	IDC_SCULPTBAKE_NORMAL_METHOD_OBJECT,
	IDC_SCULPTBAKE_NORMAL_METHOD_TANGET,
	IDC_SCULPTBAKE_NORMAL_METHOD_WORLD,
	IDC_SCULPTBAKE_NORMAL_FLIP_X,
	IDC_SCULPTBAKE_NORMAL_FLIP_Y,
	IDC_SCULPTBAKE_NORMAL_FLIP_Z,
	IDC_SCULPTBAKE_NORMAL_SWAP_YZ,
	IDC_SCULPTBAKE_NORMAL_CONTINUEUVS,

	//AO
	IDC_SCULPTBAKE_AO_SETTINGS,
	IDC_SCULPTBAKE_AO_SELFINTERSECTION,
	IDC_SCULPTBAKE_AO_TO_VERTEX,
	IDC_SCULPTBAKE_AO_ANTIALIASING,
	IDC_SCULPTBAKE_AO_CONTINUEUVS,

	IDC_SCULPTBAKE_SINGLEFILE,

	//Strings
	IDS_SCULPTBAKE_COMMAND,
	IDS_SCULPTBAKE_COMMAND_HELP,
	IDS_SCULPTBAKE_TREE_LEVELS,
	IDS_SCULPTBAKE_TREE_DEST,
	IDS_SCULPTBAKE_TREE_SOURCE,
	IDS_SCULPTBAKE_SIZEPRESET_CUSTOM,
	IDS_SCULPTBAKE_SOURCE,
	IDS_SCULPTBAKE_TARGET,

	IDC_SCULPTBAKE_CREATERESULTCOPY,

// End of symbol definition
	_DUMMY_ELEMENT_
};
