#ifndef OSCENEINSTANCE_H__
#define OSCENEINSTANCE_H__

enum
{
	SCENEINSTANCE_FILENAME	= 1000,
	SCENEINSTANCE_EDITSCENE,
	SCENEINSTANCE_RELOADSCENE,

	SCENEINSTANCE_ANIMATE,
	SCENEINSTANCE_STARTTIME,
	SCENEINSTANCE_ENDTIME,

	SCENEINSTANCE_WARNING,
	SCENEINSTANCE_INFO,
	SCENEINSTANCE_RELOADALLSCENES,

	SCENEINSTANCE_OBJECTS_GROUP,
	SCENEINSTANCE_OBJECTS,

	SCENEINSTANCE_MATERIALS_GROUP,
	SCENEINSTANCE_MATERIALS,

	SCENEINSTANCE_INFO_GROUP,
	SCENEINSTANCE_INFO_OBJECTS,
	SCENEINSTANCE_INFO_MATERIALS,
	SCENEINSTANCE_INFO_MEMORY,
	SCENEINSTANCE_INFO_FRAMERATE,
	SCENEINSTANCE_INFO_FRAMEPROJECTLENGTH,
	SCENEINSTANCE_INFO_PATH,
	SCENEINSTANCE_INFO_FILE,

	SCENEINSTANCE_OBJECTS_MODE,
	SCENEINSTANCE_OBJECTS_PIVOT,
	SCENEINSTANCE_OBJECTS_PIVOT_GROUP,
		SCENEINSTANCE_OBJECTS_PIVOT_POS,
		SCENEINSTANCE_OBJECTS_PIVOT_SCL,
		SCENEINSTANCE_OBJECTS_PIVOT_ROT,

	SCENEINSTANCE_
};

enum
{
	SCENEINSTANCE_OBJECTS_MODE_INCLUDE,
	SCENEINSTANCE_OBJECTS_MODE_EXCLUDE
};

#endif	// OSCENEINSTANCE_H__