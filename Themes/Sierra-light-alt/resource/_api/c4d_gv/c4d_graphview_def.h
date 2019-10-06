/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_GRAPHVIEW_DEF_H
#define __C4D_GRAPHVIEW_DEF_H

////////////////////////////////

#include "c4d_general.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"
#include "c4d_graphview_enum.h"
#include "lib_description.h"

////////////////////////////////

class BaseDocument;
class BaseDrawHelp;
class BaseDraw;
class GeDialog;
class GeUserArea;
class BaseBitmap;
class GvNodeMaster;
class GvOperatorData;
class	GvNode;
class	GvPort;
class GvNodeGUI;
class GvShape;
class GvRun;
class GvCalc;
class GvQuery;
class GvInit;
class GvValue;
class GvWorld;
class GvCalcTable;
class GvCalcTime;
class GvPortList;
class String;

struct GvPortListEntry;
struct GvCopyBuffer;
struct OPERATORPLUGIN;

typedef NodeData *DataAllocator(void);

////////////////////////////////
// current versions

#define GV_NODEMASTER_VERSION										5
#define GV_NODE_VERSION													5
#define GV_GROUPNODE_VERSION										5

#define VERSION_OPERATOR_GROUP									5
#define VERSION_OPERATOR_DUMMY									0

#define VERSION_OPERATOR_OBJECT									2
#define VERSION_OPERATOR_RANDOM									2
#define VERSION_OPERATOR_REAL2VECT							2
#define VERSION_OPERATOR_VECT2REAL							2
#define VERSION_OPERATOR_ADAPTER								2
#define VERSION_OPERATOR_CROSS									2
#define VERSION_OPERATOR_EQU										2
#define VERSION_OPERATOR_NIL										2
#define VERSION_OPERATOR_TIME										2
#define VERSION_OPERATOR_TRIGO									2
#define VERSION_OPERATOR_MATRIX2VECT						2
#define VERSION_OPERATOR_VECT2MATRIX						2
#define VERSION_OPERATOR_NOT										2
#define VERSION_OPERATOR_POINT									2
#define VERSION_OPERATOR_TRACK									2
#define VERSION_OPERATOR_CLAMP									2
#define VERSION_OPERATOR_VECTCALCMATRIX					2
#define VERSION_OPERATOR_MATRIXCALCHPB					2
#define VERSION_OPERATOR_DISTANCE								2
#define VERSION_OPERATOR_CONDITION							2
#define VERSION_OPERATOR_RESULT									2
#define VERSION_OPERATOR_SPY										2
#define VERSION_OPERATOR_CONST									2
#define VERSION_OPERATOR_MATH										2
#define VERSION_OPERATOR_BOOL										2
#define VERSION_OPERATOR_INV										2
#define VERSION_OPERATOR_NEG										2
#define VERSION_OPERATOR_CMP										2
#define VERSION_OPERATOR_ORDER									2
#define VERSION_OPERATOR_SWITCH									2
#define VERSION_OPERATOR_MIX										2
#define VERSION_OPERATOR_COMMENT								2
#define VERSION_OPERATOR_MEMORY									2
#define VERSION_OPERATOR_ITERATE								4
#define VERSION_OPERATOR_FREEZE									2
#define VERSION_OPERATOR_FORMULA								2
#define VERSION_OPERATOR_ABS										2
#define VERSION_OPERATOR_DEGREE									2
#define VERSION_OPERATOR_RANGEMAPPER						2
#define VERSION_OPERATOR_FLOATMATH							2
#define VERSION_OPERATOR_FLOATFUNC							2
#define VERSION_OPERATOR_POLYGON								2
#define VERSION_OPERATOR_DOT										2
#define VERSION_OPERATOR_COLORSPACE							2
#define VERSION_OPERATOR_SOUND									2
#define VERSION_OPERATOR_NOISE									2
#define VERSION_OPERATOR_TRIGGER								2
#define VERSION_OPERATOR_BOX										2
#define VERSION_OPERATOR_COLLISION							2
#define VERSION_OPERATOR_SPLINE									2
#define VERSION_OPERATOR_MATRIXMULVECTOR				2
#define VERSION_OPERATOR_SELECTION							3
#define VERSION_OPERATOR_HIERARCHY							3
#define VERSION_OPERATOR_DETAILS								2
#define VERSION_OPERATOR_TAG										3
#define	VERSION_OPERATOR_COFFEE									2
#define VERSION_OPERATOR_MONOFLOP								2
#define VERSION_OPERATOR_REFERENCE							2
#define VERSION_OPERATOR_WEIGHTMAP							2
#define VERSION_OPERATOR_MATERIAL								3
#define VERSION_OPERATOR_INCLUDE								3
#define VERSION_OPERATOR_LINK										2
#define VERSION_OPERATOR_RAY										2
#define VERSION_OPERATOR_BITMAP									2
#define VERSION_OPERATOR_COLORTEMP							2

////////////////////////////////

#define GV_NODEMASTER_RELEASE							(1102)

////////////////////////////////
// priorities of the gv modules

#define GRAPHVIEW_CORE_PRIORITY						30000
#define GRAPHVIEW_EDITOR_PRIORITY					2000
#define GRAPHVIEW_HOOK_PRIORITY						1000

////////////////////////////////
// node ids

#define ID_GRAPHVIEW											1001100
#define ID_GV_NODEDATA										1001101 // == GVbase
#define ID_GV_GROUPDATA										1001102
#define ID_GV_NODEMASTERDATA							1001103
#define ID_GRAPHVIEW_PRIVATE							1001104

////////////////////////////////

#define ID_GV_VALGROUP_TYPE_GENERAL				1001110

#define ID_GV_OPCLASS_TYPE_GENERAL				1001111

#define ID_GV_OPGROUP_TYPE_GENERAL				1001112
#define ID_GV_OPGROUP_TYPE_ADAPTER				1001113
#define ID_GV_OPGROUP_TYPE_BOOL						1001114
#define ID_GV_OPGROUP_TYPE_CALCULATE			1001115
#define ID_GV_OPGROUP_TYPE_LOGICAL				1001116
#define ID_GV_OPGROUP_TYPE_ITERATOR				1001117
#define ID_GV_OPGROUP_TYPE_SCRIPTING			1026358

////////////////////////////////
// system data & value types

#define ID_GV_VALUE_TYPE_NONE							0
#define ID_GV_VALUE_TYPE_UNDEFINED				400007000
#define ID_GV_VALUE_TYPE_BOOL							400007001
#define ID_GV_VALUE_TYPE_INTEGER					400007002
#define ID_GV_VALUE_TYPE_REAL							400007003
#define ID_GV_VALUE_TYPE_VECTOR						400007004
#define ID_GV_VALUE_TYPE_NORMAL						400007005
#define ID_GV_VALUE_TYPE_MATRIX						400007006
#define ID_GV_VALUE_TYPE_TIME							400007007
#define ID_GV_VALUE_TYPE_STRING						400007008
#define ID_GV_VALUE_TYPE_GENERAL_OBJECT		400007009
#define ID_GV_VALUE_TYPE_GENERAL_TAG			400007010
#define ID_GV_VALUE_TYPE_GENERAL_MATERIAL	400007011
#define ID_GV_VALUE_TYPE_GENERAL_INSTANCE	400007012

#define ID_GV_DATA_TYPE_NONE							0						// DA_NIL
#define ID_GV_DATA_TYPE_UNDEFINED					400006000		//
#define ID_GV_DATA_TYPE_BOOL							400006001		//
#define ID_GV_DATA_TYPE_INTEGER						15					// DA_LONG
#define ID_GV_DATA_TYPE_REAL							19					// DA_REAL
#define ID_GV_DATA_TYPE_VECTOR						23					// DA_VECTOR
#define ID_GV_DATA_TYPE_NORMAL						400006005		//
#define ID_GV_DATA_TYPE_MATRIX						25					// DA_MATRIX
#define ID_GV_DATA_TYPE_TIME							22					// DA_TIME
#define ID_GV_DATA_TYPE_STRING						130					// DA_STRING
#define ID_GV_DATA_TYPE_GENERAL_OBJECT		400006009		//
#define ID_GV_DATA_TYPE_GENERAL_TAG				400006010		//
#define ID_GV_DATA_TYPE_GENERAL_MATERIAL	400006011		//
#define ID_GV_DATA_TYPE_GENERAL_INSTANCE	400006012		//

#define CUSTOMGUI_NORMAL									ID_GV_DATA_TYPE_NORMAL

////////////////////////////////
// system operators

#define ID_GV_OPERATOR_DUMMY							1001143
#define ID_GV_OPERATOR_GROUP							1001144

#define ID_OPERATOR_OBJECT								400001000

#define ID_OPERATOR_RANDOM								400001100
#define ID_OPERATOR_REAL2VECT							400001101
#define ID_OPERATOR_VECT2REAL							400001102
#define ID_OPERATOR_ADAPTER								400001103
#define ID_OPERATOR_CROSS									400001104
#define ID_OPERATOR_EQU										400001105
#define ID_OPERATOR_NIL										400001106
#define ID_OPERATOR_TIME									400001107
#define ID_OPERATOR_TRIGO									400001108
#define ID_OPERATOR_MATRIX2VECT						400001109
#define ID_OPERATOR_VECT2MATRIX						400001110
#define ID_OPERATOR_NOT										400001111
#define ID_OPERATOR_POINT									400001112
#define ID_OPERATOR_CLAMP									400001113
#define ID_OPERATOR_VECTCALCMATRIX				400001114
#define ID_OPERATOR_MATRIXCALCHPB					400001115
#define ID_OPERATOR_DISTANCE							400001116
#define ID_OPERATOR_CONDITION							400001117
#define ID_OPERATOR_RESULT								400001118
#define ID_OPERATOR_SPY										400001119
#define ID_OPERATOR_CONST									400001120
#define ID_OPERATOR_MATH									400001121
#define ID_OPERATOR_BOOL									400001122
#define ID_OPERATOR_INV										400001123
#define ID_OPERATOR_NEG										400001124
#define ID_OPERATOR_CMP										400001125
#define ID_OPERATOR_ORDER									400001126
#define ID_OPERATOR_SWITCH								400001127
#define ID_OPERATOR_MIX										400001128
#define ID_OPERATOR_COMMENT								400001129
#define ID_OPERATOR_MEMORY								400001130
#define ID_OPERATOR_ITERATE								400001131
#define ID_OPERATOR_FREEZE								400001132
#define ID_OPERATOR_FORMULA								400001133
#define ID_OPERATOR_ABS										400001134
#define ID_OPERATOR_DEGREE								400001135
#define ID_OPERATOR_RANGEMAPPER						400001136
#define ID_OPERATOR_FLOATMATH							400001138
#define ID_OPERATOR_FLOATFUNC							400001139
#define ID_OPERATOR_POLYGON								400001140
#define ID_OPERATOR_DOT										400001141
#define ID_OPERATOR_COLORSPACE						400001142
#define ID_OPERATOR_SOUND									400001143
#define ID_OPERATOR_NOISE									400001144
#define ID_OPERATOR_TRIGGER								400001145
#define ID_OPERATOR_BOX										400001146
#define ID_OPERATOR_COLLISION							400001147
#define ID_OPERATOR_SPLINE								400001148
#define ID_OPERATOR_MATRIXMULVECTOR				400001149
#define ID_OPERATOR_SELECTION							400001150
#define ID_OPERATOR_HIERARCHY							400001151
#define ID_OPERATOR_DETAILS								400001152
#define ID_OPERATOR_TAG										400001153
#define	ID_OPERATOR_COFFEE								400001154
#define ID_OPERATOR_MONOFLOP							400001155
#define ID_OPERATOR_REFERENCE							400001156
#define ID_OPERATOR_WEIGHTMAP							400001157
#define ID_OPERATOR_MATERIAL							400001158
#define ID_OPERATOR_INCLUDE								400001159
#define ID_OPERATOR_LINK									400001160
#define ID_OPERATOR_RAY										400001161
#define ID_OPERATOR_BITMAP								450000037
#define ID_OPERATOR_COLORTEMP							450000060
#define ID_OPERATOR_TRACK									1027923

////////////////////////////////
// operator owner types

#define ID_GV_SYSTEM_OWNER								1001140
#define ID_GV_GENERAL_OWNER								1001141
#define ID_GV_IGNORE_OWNER								1001142

////////////////////////////////
// the plugin ids

#define ID_OPERATORPOOL_PLUGIN						1001138
#define ID_TREEVIEW_PLUGIN								1001145
#define ID_OBJECT_PLUGIN									1001146
#define ID_SCENEHOOK_PLUGIN								1001147
#define ID_EXPRESSION_PLUGIN							1001148
#define ID_EXPRESSION_TAG									1001149

#define ID_GRAPHVIEW_PREFS								400005000
#define ID_GRAPHVIEW_GUI_PREFS						400005001
#define ID_GRAPHVIEW_COLORS_PREFS					400005002
#define ID_GRAPHVIEW_WORLD_PREFS					400005003
#define ID_GRAPHVIEW_MASTER_PREFS					400005004

////////////////////////////////
// used when dragging nodes into an editor

#define DRAGTYPE_GVNODE_EDITOR						400007000
#define DRAGTYPE_GVNODE_MANAGER						400007001
#define DRAGTYPE_GVNODE_STORE							400007002
#define DRAGTYPE_GVNODE_DUMMY							400007003

////////////////////////////////
// internal use only

#define ID_OPERATORCONTAINER							1000
#define ID_SHAPECONTAINER									1001

////////////////////////////////

enum
{
	GV_GROUP_INPUT_FIRST_PRIVATE_ID =		10000,
	GV_GROUP_INPUT_LAST_PRIVATE_ID =		49999,
	GV_GROUP_OUTPUT_FIRST_PRIVATE_ID =	50000,
	GV_GROUP_OUTPUT_LAST_PRIVATE_ID =		89999,

	GV_GROUP_INPUT_FIRST_ID  =	1000000,
	GV_GROUP_INPUT_LAST_ID =		536870911,
	GV_GROUP_OUTPUT_FIRST_ID =  536870912,
	GV_GROUP_OUTPUT_LAST_ID =		1073741824
};

////////////////////////////////
// internal use only

enum GvFileIdent
{
	GV_MACRO_IDENT = 1000,
	GV_PRESET_IDENT
};

////////////////////////////////
// predefined ids for operators BaseContainer

#define GV_OPERATOR_PORTS_ID					101
#define GV_OPERATOR_DATA_ID						102

////////////////////////////////
// message types sended by the GvNodeMaster

enum
{
	GV_MESSAGE_FIRST_DATA_ID = 100
};

enum GvMessage
{
	GV_MESSAGE_NONE = 0,
	// internal use only
	GV_MESSAGE_PORT_ADDED = 400000000,
	// io					= (GvPortIO)bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 0);
	// main_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 1);
	// sub_id			= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 2);
	// index			= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 3);
	GV_MESSAGE_PORT_REMOVED,
	// io					= (GvPortIO)bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 0);
	// main_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 1);
	// sub_id			= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 2);
	// index			= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 3);
	GV_MESSAGE_ADD_PORT_EX,
	// io					= (GvPortIO)bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 0);
	// main_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 1);
	GV_MESSAGE_REMOVE_PORT_EX,
	// io					= (GvPortIO)bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 0);
	// index			= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 1);
	GV_MESSAGE_PORT_RENAMED,
	// io					= (GvPortIO)bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 0);
	// index			= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 1);
	// name				= bc->GetString(GV_MESSAGE_FIRST_DATA_ID + 2);
	// old_name   = bc->GetString(GV_MESSAGE_FIRST_DATA_ID + 3);
	// sub_id			= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 4);
	GV_MESSAGE_VIEW_CHANGED,
	// state			= (GvDrawState)bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 0);
	GV_MESSAGE_RENAME_PORT_EX,
	// io					= (GvPortIO)bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 0);
	// index			= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 1);
	// name				= bc->GetString(GV_MESSAGE_FIRST_DATA_ID + 2);
	GV_MESSAGE_NODE_RENAMED,
	// node				= bc->GetLink(GV_MESSAGE_FIRST_DATA_ID + 0);
	// oper_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 1);
	// owner_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 2);
	// name				= bc->GetString(GV_MESSAGE_FIRST_DATA_ID + 3);
	GV_MESSAGE_NODE_ENABLED,
	// node				= bc->GetLink(GV_MESSAGE_FIRST_DATA_ID + 0);
	// oper_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 1);
	// owner_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 2);
	GV_MESSAGE_NODE_DISABLED,
	// node				= bc->GetLink(GV_MESSAGE_FIRST_DATA_ID + 0);
	// oper_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 1);
	// owner_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 2);
	GV_MESSAGE_NODE_CREATED,
	// node				= bc->GetLink(GV_MESSAGE_FIRST_DATA_ID + 0);
	// oper_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 1);
	// owner_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 2);
	GV_MESSAGE_NODE_REMOVED,
	// node				= bc->GetLink(GV_MESSAGE_FIRST_DATA_ID + 0);
	// oper_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 1);
	// owner_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 2);
	GV_MESSAGE_NODE_SELECTED,
	// node				= bc->GetLink(GV_MESSAGE_FIRST_DATA_ID + 0);
	// oper_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 1);
	// owner_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 2);
	GV_MESSAGE_NODE_DESELECTED,
	// node				= bc->GetLink(GV_MESSAGE_FIRST_DATA_ID + 0);
	// oper_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 1);
	// owner_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 2);
	GV_MESSAGE_OPERATOR_MENU,
	// node				= bc->GetLink(GV_MESSAGE_FIRST_DATA_ID + 0);
	// oper_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 1);
	// owner_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 2);
	// menu_index	= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 3);
	GV_MESSAGE_OPERATOR_EDIT_SETTINGS,
	// node				= bc->GetLink(GV_MESSAGE_FIRST_DATA_ID + 0);
	// oper_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 1);
	// owner_id		= bc->GetInt32(GV_MESSAGE_FIRST_DATA_ID + 2);
	GV_MESSAGE_MASTER_INIT,
	// no parms
	GV_MESSAGE_MASTER_REDRAW,
	// no parms
	GV_MESSAGE_TRANSLATE_ID
	// internal use only
};

////////////////////////////////
// some defines & typedefs

#define GV_INITIAL_OPCLASS_SUB_ID		(-1)
#define GV_INITIAL_OPGROUP_SUB_ID		(-1)
#define GV_INITIAL_VALGROUP_SUB_ID	(-1)
#define GV_INITIAL_DATA_SUB_ID			(-1)
#define GV_INITIAL_VALUE_SUB_ID			(-1)

typedef Int32 GvOpClassSubID;
typedef Int32 GvOpGroupSubID;
typedef Int32 GvValGroupSubID;
typedef Int32 GvDataSubID;
typedef Int32 GvValueSubID;

////////////////////////////////
// internal use only

enum GvOperatorType
{
	GV_OPERATOR_TYPE_INVALID = 0,
	GV_OPERATOR_TYPE_GROUP,
	GV_OPERATOR_TYPE_NODE,
	GV_OPERATOR_TYPE_DUMMY,
	GV_OPERATOR_TYPE_GENERAL,
	GV_OPERATOR_TYPE_CALCULATE,
	GV_OPERATOR_TYPE_ITERATOR,
	GV_OPERATOR_TYPE_BOOL,
	GV_OPERATOR_TYPE_LOGICAL,
	GV_OPERATOR_TYPE_ADAPTER,
	GV_OPERATOR_TYPE_THINKINGPARTICLES
};

////////////////////////////////
// failure priorities

enum GvCalcState
{
	GV_CALC_STATE_NO_FAILURE = 0,
	GV_CALC_STATE_DISABLED_FAILURE,
	GV_CALC_STATE_LOCAL_FAILURE,
	GV_CALC_STATE_MASTER_FAILURE,
	GV_CALC_STATE_GLOBAL_FAILURE
};

////////////////////////////////
// port types

enum GvPortIO
{
	GV_PORT_INVALID = 0,
	GV_PORT_INPUT,
	GV_PORT_OUTPUT,
	GV_PORT_INPUT_OR_GEDATA
};

////////////////////////////////
// internal use only

enum GvBodyDefaultSize
{
	GV_DEFAULT_BODY_WIDTH = 32,
	GV_DEFAULT_BODY_HEIGHT = 12
};

////////////////////////////////
// internal use only

#define GV_INVALID_POS_VALUE						(LIMIT<Int32>::MAX)
#define GV_COPY_OFFSET_X								10
#define GV_COPY_OFFSET_Y								10
#define GV_PACK_NODES_EXTRA_BORDER			12
#define GV_OPTIMIZE_NODES_EXTRA_BORDER	6

////////////////////////////////
// user interaction states of a node

enum GvState
{
	GV_STATE_NORMAL = 0,
	GV_STATE_SELECTED,
	GV_STATE_DISABLED,
	GV_STATE_SELECTED_AND_DISABLED,
	GV_NR_OF_STATES
};

////////////////////////////////
// internal use only

enum GvRunId
{
	GV_RESET_RUN_ID = -1,
	GV_INITIAL_RUN_ID = 1
};

////////////////////////////////
// internal use only

#define GV_NODE_INVALID_INDEX		(-1)
#define GV_PORT_INVALID_ID			(-1)
#define GV_PORT_INVALID_INDEX		(-1)
#define GV_PORT_INVALID_SUB_ID	(-1)
#define GV_USERDATA_INVALID_ID	(-1)
#define GV_OPERATOR_INVALID_ID  (-1)
#define GV_PORT_INVALID_DESC		DescID()

////////////////////////////////
// used with operators SetData/IsSetDataAllowed()

enum
{
	GV_INVALID = 0,
	GV_ATOMARRAY = DRAGTYPE_ATOMARRAY,
	GV_BOOL = 400000000,
	GV_INT,
	GV_REAL,
	GV_VECTOR,
	GV_NORMAL,
	GV_MATRIX,
	GV_TIME,
	GV_STRING,
	GV_ATOM,
	GV_USERDEF,
	GV_DESCID
};

typedef Int32 GvDataType;

enum GvOpSetDataMode
{
	GV_OP_NOP = 0,
	GV_OP_SET,
	GV_OP_DROP,
	GV_OP_DROP_IN_BODY,
	GV_OP_DROP_IN_INDOCK,
	GV_OP_DROP_IN_OUTDOCK
};

////////////////////////////////
// offsets of in/out ports

enum GvPortID
{
	GV_INPUT_FIRST_ID						=	10000000,
	GV_INPUT_LAST_ID						= 19999990,
	GV_OUTPUT_FIRST_ID					=	20000000,
	GV_OUTPUT_LAST_ID						= 29999990,
	GV_INPUT_FIRST_PRIVATE_ID		= 30000000,
	GV_INPUT_LAST_PRIVATE_ID		= 39999990,
	GV_OUTPUT_FIRST_PRIVATE_ID	= 40000000,
	GV_OUTPUT_LAST_PRIVATE_ID		= 49999990
};

////////////////////////////////
// direction of editor layout

enum GvLayoutType
{
	GV_LAYOUT_IN_LEFT = 0,
	GV_LAYOUT_IN_RIGHT,
	GV_LAYOUT_IN_TOP,
	GV_LAYOUT_IN_BOTTOM,
	GV_NR_OF_LAYOUT_TYPES
};

////////////////////////////////
// direction of editor layout

enum GvConnMode
{
	GV_CONNECTION_MODE_DIRECT = 0,
	GV_CONNECTION_MODE_STRAIGHT,
	GV_CONNECTION_MODE_NORMAL,
	GV_CONNECTION_MODE_CURVED
};

////////////////////////////////
// nodes display states

enum GvDrawState
{
	GV_DRAW_NONE = -1,
	GV_DRAW_MINIMIZED = 0,
	GV_DRAW_NORMAL,
	GV_DRAW_EXTENDED,
	GV_DRAW_FULLSCREEN
};

////////////////////////////////
// preferences IDs

#define GV_GUI_PREFERENCES_ID 40000000
#define GV_WORLD_PREFERENCES_ID 40000001
#define GV_MASTER_PREFERENCES_ID 40000002

enum GvGuiConfigIDs
{
	GV_GUI_CONFIG_LAYOUT_TYPE = 1000,
	GV_GUI_CONFIG_CONNECTION_MODE,
	GV_GUI_CONFIG_GRID_X,
	GV_GUI_CONFIG_GRID_Y,
	GV_GUI_CONFIG_STATUS_BAR,
	GV_GUI_CONFIG_CONNECTION_MIN_OFFSET,
	GV_GUI_CONFIG_CONNECTION_MAX_OFFSET,
	GV_GUI_CONFIG_TEXT_BORDER_HORZ,
	GV_GUI_CONFIG_TEXT_BORDER_VERT,
	GV_GUI_CONFIG_BORDER_SIZE,
	GV_GUI_CONFIG_DOCK_WIDTH,
	GV_GUI_CONFIG_DOCK_HEIGHT,
	GV_GUI_CONFIG_PORT_WIDTH,
	GV_GUI_CONFIG_PORT_HEIGHT,
	GV_GUI_CONFIG_PAN_WIDTH,
	GV_GUI_CONFIG_PAN_HEIGHT,
	GV_GUI_CONFIG_ZOOM_WIDTH,
	GV_GUI_CONFIG_ZOOM_HEIGHT,
	GV_GUI_CONFIG_PORT_SPACE,
	GV_GUI_CONFIG_HEAD_HEIGHT,
	GV_GUI_CONFIG_FOOT_HEIGHT,
	GV_GUI_CONFIG_CONNECTION_SELECT_DISTANCE,
	GV_GUI_CONFIG_ADDITIONAL_FRAME_SELECT_DISTANCE,
	GV_GUI_CONFIG_ADDITIONAL_PORT_LABEL_SPACE,
	GV_GUI_CONFIG_LINE_SPACE,
	GV_GUI_CONFIG_TEXT_COLOR,
	GV_GUI_CONFIG_HEAD_NORMAL_COLOR,
	GV_GUI_CONFIG_HEAD_ERROR_COLOR,
	GV_GUI_CONFIG_FOOT_COLOR,
	GV_GUI_CONFIG_BODY_COLOR,
	GV_GUI_CONFIG_GRID_COLOR,
	GV_GUI_CONFIG_INPORT_AREA_COLOR,
	GV_GUI_CONFIG_OUTPORT_AREA_COLOR,
	GV_GUI_CONFIG_INPORT_COLOR,
	GV_GUI_CONFIG_OUTPORT_COLOR,
	GV_GUI_CONFIG_INDOCK_COLOR,
	GV_GUI_CONFIG_OUTDOCK_COLOR,
	GV_GUI_CONFIG_PAN_COLOR,
	GV_GUI_CONFIG_ZOOM_COLOR,
	GV_GUI_CONFIG_SELECTBOX_COLOR,
	GV_GUI_CONFIG_BORDER_NORMAL_COLOR,
	GV_GUI_CONFIG_BORDER_SELECTED_COLOR,
	GV_GUI_CONFIG_INPORTLABEL_COLOR,
	GV_GUI_CONFIG_OUTPORTLABEL_COLOR,
	GV_GUI_CONFIG_INPORTLABEL_BORDER_COLOR,
	GV_GUI_CONFIG_OUTPORTLABEL_BORDER_COLOR,
	GV_GUI_CONFIG_CONNECTION_NORMAL_COLOR,
	GV_GUI_CONFIG_CONNECTION_TEMP_COLOR,
	GV_GUI_CONFIG_CONNECTION_VALID_COLOR,
	GV_GUI_CONFIG_CONNECTION_DISABLED_COLOR,
	GV_GUI_CONFIG_CONNECTION_FORBIDDEN_COLOR,
	GV_GUI_CONFIG_CONNECTION_SELECTED_COLOR,
	GV_GUI_CONFIG_CONNECTION_IN_FOCUS_COLOR,
	GV_GUI_CONFIG_PORTS_SQUARE,
	GV_GUI_CONFIG_BORDER_NORMAL_DISABLED_COLOR,
	GV_GUI_CONFIG_BORDER_SELECTED_DISABLED_COLOR,
	GV_GUI_CONFIG_SORT_MENUS,
	GV_GUI_CONFIG_SORT_PORTS,

	GV_GUI_CONFIG_NR_OF_ENTRIES
};

////////////////////////////////
// used with master->Set/GetPrefs()

enum GvMasterConfigIDs
{
	GV_MASTER_CONFIG_LIVE_REFRESH = 100,							//bool to enable
	GV_MASTER_CONFIG_ANIM_REFRESH,										//bool to enable

	GV_MASTER_CONFIG_PERFORMANCEVIEW_ENABLE,					//bool for on
	GV_MASTER_CONFIG_PERFORMANCEVIEW_MODE,						//GvPerfMode for mode
	GV_MASTER_CONFIG_PERFORMANCEVIEW_INTENSITY_COUNT,	//long
	GV_MASTER_CONFIG_PERFORMANCEVIEW_INTENSITY_TIME		//real
};

////////////////////////////////
// used with world->Set/GetPrefs()

enum GvWorldConfigIDs
{
	GV_WORLD_CONFIG_UNDO_DEPTH = 100,
};

////////////////////////////////

typedef Int32 GvOperatorID;
typedef Int32 GvOpClassID;
typedef Int32 GvOpGroupID;
typedef Int32 GvValGroupID;
typedef Int32 GvDataID;
typedef Int32 GvValueID;
typedef Int32 GvUserDataID;

////////////////////////////////
// operator class & group hierarchy

struct GV_OPCLASS_HANDLER
{
		GvOpClassID		class_id;

		const String*	(*GetName)(void);
		BaseBitmap*		(*GetIcon)(void);
};

struct GV_OPGROUP_HANDLER
{
		GvOpGroupID		group_id;

		const String*	(*GetName)(void);
		BaseBitmap*		(*GetIcon)(void);
};

////////////////////////////////
// generic value types

struct GV_VALUE_HANDLER
{

		GvValueID				value_id;
		GvValueFlags		value_flags;
		void*						userdata;

		Bool						(*Alloc								)(void *userdata,void *&data, Int32 nr_of_cpus);
		void						(*Free								)(void *userdata,void *&data, Int32 nr_of_cpus);
		GvCalcError			(*Convert							)(void *userdata,GvValueID source_id, const void* const source, GvValueID dest_id, void *dest, Int32 cpu_id);
		GvCalcError			(*Calculate						)(void *userdata,GvValueID id, const void* const source1, const void* const source2, void *dest, Int32 cpu_id, GvValueFlags calculation, Float parm1);
		void						(*CopyFrom						)(void *userdata,const void* const source, void *dest, Int32 cpu_id);
		void						(*CopyTo							)(void *userdata,const void* const source, void *dest, Int32 cpu_id);
		Int32						(*GetConversionsFrom	)(void *userdata,GvValueID *&table);
		Int32						(*GetConversionsTo		)(void *userdata,GvValueID *&table);
		const String*		(*GetName							)(void *userdata);
		Bool						(*Read								)(void *userdata,void* data, Int32 nr_of_cpus, HyperFile &hf, Int32 level);
		Bool						(*Write								)(void *userdata,const void* const data, Int32 nr_of_cpus, HyperFile &hf);
		BaseBitmap*			(*GetIcon							)(void *userdata);
		const void*			(*GetDataInstance			)(void *userdata,const void* const source, Int32 cpu_id);
};

struct GV_VALGROUP_HANDLER
{
		GvValGroupID	group_id;
		void*					userdata;

		const String*	(*GetName							)(void *userdata);
};

#define GV_RESOURCE_SYMBOL_MAX_LENGTH 32

struct GV_DATA_HANDLER
{
		GV_DATA_HANDLER(void) { x_flags = 0; disclevel = 1; }

		GvDataID			data_id;
		GvValueID			value_id;
		GvValGroupID	group_id;
		void*					userdata;
		Int32					edit_id;
		char					resource_symbol[GV_RESOURCE_SYMBOL_MAX_LENGTH];
		UInt32					x_flags;

		const String*	(*GetName							)(void *userdata);
		BaseBitmap*		(*GetIcon							)(void *userdata);
		Int32					(*GetDefaultsList			)(void *userdata, BaseContainer &bc);
		Bool					(*SetDefault					)(void *userdata, Int32 id, void *data, Int32 cpu_id);

		Int32					disclevel;
};

#define GV_DATAHANDLER_FLAGS_DISCLEVEL	(1<<0)

#define GV_CONSTANT_NONE		0
#define GV_CONSTANT_FIRST		1

////////////////////////////////
// internal use only

struct GvDataInfo
{
	GV_DATA_HANDLER*				data_handler;
	GV_VALUE_HANDLER*				value_handler;
	GV_VALGROUP_HANDLER*		group_handler;
};

#define INDEX_GV_VALUE_TYPE_UNDEFINED	0
#define INDEX_GV_DATA_TYPE_UNDEFINED	0
#define INDEX_GV_GROUP_TYPE_UNDEFINED	0
#define INDEX_GV_CLASS_TYPE_UNDEFINED	0

#define INDEX_GV_VALUE_TYPE_INVALID		(-1)
#define INDEX_GV_DATA_TYPE_INVALID		(-1)
#define INDEX_GV_GROUP_TYPE_INVALID		(-1)
#define INDEX_GV_CLASS_TYPE_INVALID		(-1)

#define GV_DATA_TYPE_MENU_OFFSET 1000

#define GV_VALUE_SEPERATOR					String(";")
#define GV_VALUE_SEPERATOR_SPACED		String(" ; ")
#define GV_VALUE_SEPERATOR_CHR			';'

#define GV_ELEMENT_SEPERATOR				String("|")
#define GV_ELEMENT_SEPERATOR_SPACED	String(" | ")
#define GV_ELEMENT_SEPERATOR_CHR		'|'

////////////////////////////////
// used with struct GvCalc

enum GvCalcFlags
{
	GV_CALC_FLAG_NONE					= (0),
	// operators are not allowed to write to the document
	GV_CALC_FLAG_READ_ONLY		= (1 << 0)
};

////////////////////////////////
// the connections destination

struct GvDestination
{
	GvDestination(void) : node(nullptr), port(nullptr) { }

	GvNode*	node;
	GvPort* port;
};

////////////////////////////////
// used with GetPortDescription()

enum GvPortDescFlags
{
	GV_PORTDESCRIPTION_NONE				= (0),
	GV_PORTDESCRIPTION_MULTIPLE		= (1 << 0),
	GV_PORTDESCRIPTION_INVISIBLE	= (1 << 1),
	GV_PORTDESCRIPTION_STATIC			= (1 << 2),
	GV_PORTDESCRIPTION_FIXED			= (1 << 3),
	GV_PORTDESCRIPTION_PORTONLY		= (1 << 4),
	GV_PORTDESCRIPTION_NEEDED			= (1 << 5),
	GV_PORTDESCRIPTION_ITERATOR		= (1 << 6)
};

struct GvPortDescription
{
	GvPortDescription(void) : name(String()), flags(GV_PORTDESCRIPTION_NONE), data_id(ID_GV_DATA_TYPE_NONE), ports_min(0), ports_max(0), parent_id(GV_PORT_INVALID_ID) { }

	String					name;
	GvPortDescFlags	flags;
	GvDataID				data_id;
	Int32						ports_min;
	Int32						ports_max;
	Int32						parent_id;
};

struct GvPortInfo
{
	String				io;
	String				name;
	String				data;
	String				value;
};

enum GvPortFlags
{
	GV_PORT_FLAG_NONE						= 0,
	GV_PORT_FLAG_IS_VISIBLE			= (1 << 0),
	GV_PORT_FLAG_IS_ITERATE			= (1 << 1)
};

////////////////////////////////
// convience struct for port definitions

struct GvPortDescInfo
{
	Int32						count;
	GvDataID*				types;
	UInt32*					flags;
	Int32*						ids;
	Int32*						name_ids;
	const String**	names;
};

struct GvPortsDescInfo
{
	GvPortDescInfo	in;
	GvPortDescInfo	out;
};

////////////////////////////////
// convience struct for port calculation speedup

struct GvPortsInfo
{
	GvPortsInfo(void) : in_ports(nullptr), out_ports(nullptr), nr_of_in_ports(0), nr_of_out_ports(0) { }

	GvPort**	in_ports;
	GvPort**	out_ports;
	Int32			nr_of_in_ports;
	Int32			nr_of_out_ports;
};

struct GvValuesInfo
{
	GvValuesInfo(void) : in_values(nullptr), out_ports(nullptr), nr_of_in_values(0), nr_of_out_ports(0) { }

	GvValue**	in_values;
	GvPort**	out_ports;
	Int32			nr_of_in_values;
	Int32			nr_of_out_ports;

	GvValue*	GetInValue(Int32 value_index) { return in_values && value_index >= 0 && value_index < nr_of_in_values ? in_values[value_index] : nullptr;  }
};

////////////////////////////////
// convience struct for port calculation setup

struct GvDynamicData
{
	GvDynamicData(void) : data(nullptr), info(nullptr), cpu_count(0) { }

	void*				data;
	GvDataInfo*	info;
	Int32				cpu_count;
};

////////////////////////////////
// returned by GetOperatorDescription()

enum GvOperatorDescriptionFlags
{
	GV_DESCRIPTIONFLAG_NONE					= (0)
};

struct GvOperatorDescription
{
	GvOperatorDescriptionFlags			flags;
};

////////////////////////////////
// used as info flags with GvRegisterOperatorPlugin()

enum GvOperatorFlags
{
	GV_OPERATORFLAG_NONE								= (0),
	GV_OPERATORFLAG_MP_SAVE							= (1 << 0),
	GV_OPERATORFLAG_READ_ONLY_SAVE			= (1 << 1),
	GV_OPERATORFLAG_MULTIPLE_DRAW				= (1 << 2),
	GV_OPERATORFLAG_REFRESH_ON_DELETE		= (1 << 3),
	GV_OPERATORFLAG_ITERATOR						= (1 << 4),
	GV_OPERATORFLAG_SAVE								= (GV_OPERATORFLAG_MP_SAVE | GV_OPERATORFLAG_READ_ONLY_SAVE)
};

#define GV_OPERATORFLAGS_MASK			0x0000ffff

////////////////////////////////
// hook functions

struct GvDropHook
{
	GvDropHook(void) : master(nullptr), document(nullptr), user(nullptr), parent(nullptr), type(GV_INVALID), data(nullptr), mode(GV_OP_NOP), x(0), y(0), activate(true) { }

	GvNodeMaster*		master;
	BaseDocument*		document;
	void*						user;
	GvNode*					parent;
	GvDataType			type;
	void*						data;
	GvOpSetDataMode	mode;
	Int32						x,y;
	Bool						activate;
};

struct GvCalcHook
{
	GvCalcHook(void) : master(nullptr), document(nullptr), user(nullptr), calc(nullptr), status(false) { }

	GvNodeMaster*		master;
	BaseDocument*		document;
	void*						user;
	GvCalc*					calc;
	Bool						status;
};

struct GvMenuHook
{
	GvMenuHook(void) : master(nullptr), document(nullptr), user(nullptr), menu_id(0), menu(BaseContainer()) { }

	GvNodeMaster*		master;
	BaseDocument*		document;
	void*						user;
	Int32						menu_id;
	BaseContainer		menu;
};

struct GvMessHook
{
	GvMessHook(void) : master(nullptr), document(nullptr), user(nullptr), id(GV_MESSAGE_NONE), mess(BaseContainer()) { }

	GvNodeMaster*		master;
	BaseDocument*		document;
	void*						user;
	Int32						id;
	BaseContainer   mess;
};

struct GvAnimHook
{
	GvAnimHook(void) : document(nullptr), user(nullptr), time(nullptr) { }

	BaseDocument*		document;
	void*						user;
	GvCalcTime*			time;
};

struct GvDrawHook
{
	GvDrawHook(void) : document(nullptr), user(nullptr), base_draw(nullptr), draw_help(nullptr) { }

	BaseDocument*		document;
	void*						user;
	BaseDraw*				base_draw;
	BaseDrawHelp*		draw_help;
	BaseThread*			base_thread;
	Int32						flags;
};

typedef Bool (*GvDropHookFunc)(GvDropHook &hook);
typedef Bool (*GvCalcHookFunc)(GvCalcHook &hook);
typedef Bool (*GvMenuHookFunc)(GvMenuHook &hook);
typedef Bool (*GvMessHookFunc)(GvMessHook &hook);
typedef Bool (*GvAnimHookFunc)(GvAnimHook &hook);
typedef void (*GvDrawHookFunc)(GvDrawHook &hook);

struct GvHook
{
	GvHook(void) :
		drop_function(nullptr), init_calculation(nullptr), begin_calculation(nullptr), end_calculation(nullptr),
		begin_recalculation(nullptr), end_recalculation(nullptr), free_calculation(nullptr), menu_command(nullptr),
		build_menu(nullptr), message(nullptr), hook_init(nullptr), hook_main(nullptr), hook_free(nullptr),
		draw(nullptr),
		hook_id(0), owner_id(0), hook_name(String()), menu_name(String()) { }

	GvDropHookFunc			drop_function;
	GvCalcHookFunc			init_calculation;
	GvCalcHookFunc			begin_calculation;
	GvCalcHookFunc			end_calculation;
	GvCalcHookFunc			begin_recalculation;
	GvCalcHookFunc			end_recalculation;
	GvCalcHookFunc			free_calculation;
	GvMenuHookFunc			menu_command;
	GvMenuHookFunc			build_menu;
	GvMessHookFunc			message;
	GvAnimHookFunc			hook_init;
	GvAnimHookFunc			hook_main;
	GvAnimHookFunc			hook_free;
	GvDrawHookFunc			draw;

	Int32								hook_id;
	Int32								owner_id;
	String							hook_name;
	String							menu_name;
};

enum GvCalcHookType
{
	GV_CALC_HOOK_INIT = 0,
	GV_CALC_HOOK_BEGIN,
	GV_CALC_HOOK_END,
	GV_CALC_HOOK_RECALCULATE_BEGIN,
	GV_CALC_HOOK_RECALCULATE_END,
	GV_CALC_HOOK_FREE
};

enum GvAnimHookType
{
	GV_ANIM_HOOK_INIT = 0,
	GV_ANIM_HOOK_FREE,
	GV_ANIM_HOOK_MAIN
};

typedef BaseList2D *(*GvHookCallback)(BaseDocument *doc, Int32 id);

////////////////////////////////
// used with SetHierarchy()

enum GvInsertMode
{
	GV_INSERT_UNDER = 0,
	GV_INSERT_UNDER_LAST,
	GV_INSERT_BEFORE,
	GV_INSERT_AFTER,
	GV_INSERT_NONE
};

////////////////////////////////
// global functions

struct C4D_GvGlobals
{
	GvWorld*						(*GetWorld									)(void);

	void								(*OperatorDefaultDraw				)(GvNode *node, GvNodeGUI* gui, GeUserArea *da, Int32 x1, Int32 y1, Int32 x2, Int32 y2);
	Vector							(*GetDefaultBodyColor				)(GvNode *node);
	void								(*GetDefaultBodySize				)(Int32 *width, Int32 *height);
	Bool								(*DefaultSetRecalculate			)(GvNode *bn, GvPort *port, GvRun *r, Bool force_set);
	Int32								(*FillPortsMenu							)(GvNode *bn, BaseContainer &names, BaseContainer &ids, GvValueID value_type, GvPortIO port, Int32 first_menu_id);

	void								(*GetPortList								)(GvPortsDescInfo *info, GvPortIO port, GvPortList &portlist);
	Bool								(*GetAllDataTypes						)(GvPortDescInfo *info, UInt32 default_flag, Int32 first_id);
	void								(*FreePortDescInfo					)(GvPortDescInfo *info);

	Bool								(*RegisterOperatorPlugin		)(GvOperatorID id, const String &str, Int32 info, DataAllocator *at, Int32 disklevel, GvOpClassID op_class, GvOpGroupID op_group, Int32 op_owner, OPERATORPLUGIN *plug, BaseBitmap *icon);
	Bool								(*RegisterOpClassType				)(GV_OPCLASS_HANDLER *data, Int32 struct_size);
	Bool								(*RegisterOpGroupType				)(GV_OPGROUP_HANDLER *data, Int32 struct_size);
	Bool								(*RegisterValGroupType			)(GV_VALGROUP_HANDLER *data, Int32 struct_size);
	Bool								(*RegisterValueType					)(GV_VALUE_HANDLER *data, Int32 struct_size);
	Bool								(*RegisterDataType					)(GV_DATA_HANDLER *data, Int32 struct_size, const char *symbol);

	GV_OPCLASS_HANDLER* (*FindRegisteredOpClass			)(GvOpClassID id);
	GV_OPGROUP_HANDLER* (*FindRegisteredOpGroup			)(GvOpGroupID id);

	const String				(*GetEmptyString						)(void);
	const String				(*GetErrorString						)(const String &command, Int32 err);
	Bool								(*LoadIconEx								)(BaseBitmap *&bm, const String &name);
};

///////////////////////////////
// GvWorld functions

struct C4D_GvWorld
{
	GvNodeMaster*		(*AllocNodeMaster						)(GvWorld *world, BaseList2D *object, Bool add_to_list, Bool send_messages);
	void						(*FreeNodeMaster						)(GvWorld *world, GvNodeMaster *&master);

	GvShape*				(*AllocShape								)(GvWorld *world);
	GvShape*				(*AllocGroupShape						)(GvWorld *world);
	void						(*FreeShape									)(GvWorld *world, GvShape *&shape);

	GvNodeGUI*			(*AllocNodeGUI							)(GvWorld *world, GvShape *shape, GvShape *group, Int32 user_area_id);
	void						(*FreeNodeGUI								)(GvWorld *world, GvNodeGUI *&gui);
	Bool						(*AttachNode								)(GvWorld *world, GvNodeMaster *master, GvNode *node, Int32 x, Int32 y);
	void						(*RedrawAll									)(GvWorld *world);
	void						(*RedrawMaster							)(GvWorld *world, GvNodeMaster *master);

	const String		(*GetString									)(GvWorld *world, const String &title, const String &default_value);
	Float						(*GetFloat										)(GvWorld *world, const String &title, Float default_value);
	Int32						(*GetInteger								)(GvWorld *world, const String &title, Int32 default_value);

	Int32						(*GetDataTypesMenu					)(GvWorld *world, BaseContainer &bc, BaseContainer &index, Int32 first_menu_id, Int32 first_sub_id, Bool show_undefined_type, GvValueFlags flags);
	Int32						(*GetDataTypes							)(GvWorld *world, BaseContainer &bc, GvDataOptions options, GvValueFlags flags);
	Bool						(*GetDataTypesTable					)(GvWorld *world, GvDataInfo *&info, Int32 &count);
	Int32						(*GetDataTypeIndex					)(GvWorld *world, GvDataID id);
	GvDataInfo*			(*GetDataTypeInfo						)(GvWorld *world, Int32 index);

	Bool						(*RegisterHook							)(GvWorld *world, const GvHook &hook, void *user);
	Bool						(*AttachHook								)(GvWorld *world, Int32 hook_id, GvHookCallback callback);
	void						(*DetachHook								)(GvWorld *world, Int32 hook_id);
	BaseList2D*			(*GetHookInstance						)(GvWorld *world, BaseDocument *doc, Int32 hook_id);

	Bool						(*SendHookMessage						)(GvWorld *world, BaseDocument *doc, GvNodeMaster *master, GvMessHook &data, Int32 owner_id);
	Bool						(*SendOperatorMessage				)(GvWorld *world, BaseDocument *doc, Int32 message_id, void *data);

	Bool						(*OpenDialog								)(GvWorld *world, Int32 id, GvNodeMaster *master);
	void						(*CloseDialog								)(GvWorld *world, Int32 id);

	GvNodeGUI*			(*GetMasterGUI							)(GvWorld *world, GvNodeMaster *master, UInt32 nr);
	UInt32						(*GetUniqueID								)(GvWorld *world);

	BaseBitmap*			(*GetDefaultOperatorIcon		)(GvWorld *world, GvOperatorType type);

	void						(*WorldSetPrefs							)(GvWorld *world, const BaseContainer &bc);
	void						(*WorldGetPrefs							)(GvWorld *world, BaseContainer &bc);

	Int32						(*GetDataTypeNames					)(GvWorld *world, BaseContainer &bc, GvDataID *ids);
	GvNodeMaster*		(*GetMaster									)(GvWorld *world, Int32 id);
};

////////////////////////////////
// GvNodeMaster functions

struct C4D_GvNodeMaster
{
	GvNode*					(*AllocNode									)(GvNodeMaster *master, Int32 id);
	void						(*FreeNode									)(GvNodeMaster *master, GvNode *&node);
	GvNode*					(*CreateNode								)(GvNodeMaster *master, GvNode *parent, Int32 id, GvNode *insert, Int32 x, Int32 y);
	GvNode*					(*GetRoot										)(GvNodeMaster *master);
	BaseList2D*			(*GetOwner									)(GvNodeMaster *master);
	Bool						(*IsConnectionValid					)(GvNodeMaster *master, GvNode *source_node, GvPort *source_port, GvNode *dest_node, GvPort *dest_port, GvNode *&source_node_out, GvPort *&source_port_out, GvNode *&dest_node_out, GvPort *&dest_port_out);
	Bool						(*InsertFirst								)(GvNodeMaster *master, GvNode *parent, GvNode *node);
	Bool						(*InsertLast								)(GvNodeMaster *master, GvNode *parent, GvNode *node);
	Bool						(*SetHierarchy							)(GvNodeMaster *master, GvNode *insert, GvNode *node, GvInsertMode mode);
	GvCalcError			(*QueryCalculation					)(GvNodeMaster *master, GvQuery *query, BaseThread *thread);
	GvCalcError			(*InitCalculation						)(GvNodeMaster *master, GvInit *init, BaseThread *thread);
	GvCalcError			(*Calculate									)(GvNodeMaster *master, Int32 cpu_id);
	GvCalcError			(*Recalculate								)(GvNodeMaster *master, GvNode *node, Int32 cpu_id);
	void						(*FreeCalculation						)(GvNodeMaster *master);
	GvRun*					(*GetRun										)(GvNodeMaster *master);
	GvCalc*					(*GetCalc										)(GvNodeMaster *master);
	GvQuery*				(*AllocQuery								)(GvNodeMaster *master);
	void						(*FreeQuery									)(GvNodeMaster *master, GvQuery *&query);
	GvInit*					(*AllocInit									)(GvNodeMaster *master);
	void						(*FreeInit									)(GvNodeMaster *master, GvInit *&init);
	GvUserDataID		(*RegisterUserData					)(GvNodeMaster *master, void *data);
	void						(*SetUserData								)(GvNodeMaster *master, GvUserDataID id, void *data);
	void*						(*GetUserData								)(GvNodeMaster *master, GvUserDataID id);
	GvCalcTable*		(*AllocCalculationTable			)(GvNodeMaster *master, Int32 cpu_count, Bool sort, Int32 nr_of_preallocated_entries, Bool iteration);
	void						(*FreeCalculationTable			)(GvNodeMaster *master, GvCalcTable *&table);
	Bool						(*AddToDrawList							)(GvNodeMaster *master, GvNode *bn, void **data, Int32 data_size);
	void						(*MasterSetPrefs						)(GvNodeMaster *master, const BaseContainer &bc);
	void						(*MasterGetPrefs						)(GvNodeMaster *master, BaseContainer &bc);
	GvCopyBuffer*		(*GetCopyBuffer							)(GvNodeMaster *master, GvNode *first, Bool copy_selected);
	void						(*FreeCopyBuffer						)(GvNodeMaster *master, GvCopyBuffer *&buffer);
	Bool						(*PasteFromBuffer						)(GvNodeMaster *master, GvCopyBuffer &buffer, GvInsertMode mode, GvNode *dest, Int32 x, Int32 y, Bool center, void *info);
	Bool						(*IsEnabled									)(GvNodeMaster *master);
	GvCalcError			(*Execute										)(GvNodeMaster *master, BaseThread *thread);
	Int32						(*GetBranchInfo							)(GvNodeMaster *master, BranchInfo *info, Int32 max);
	Bool						(*AddUndo										)(GvNodeMaster *master);
	GvCalcError			(*Execute2									)(GvNodeMaster *master, BaseThread *thread, GvCalcFlags flags);
};

////////////////////////////////
// GvNodeGUI functions

struct C4D_GvNodeGUI
{
	Bool						(*GuiAttach									)(GvNodeGUI *gui, GeDialog *dialog, GvNodeMaster *master);
	void						(*GuiDetach									)(GvNodeGUI *gui);
	Bool						(*GuiInitShapes							)(GvNodeGUI *gui);
	void						(*GuiDraw										)(GvNodeGUI *gui);
	void						(*GuiMouseDown							)(GvNodeGUI *gui, Int32 x, Int32 y, Int32 chn, Int32 qa, const BaseContainer &msg);
	Int32						(*GuiMessage								)(GvNodeGUI *gui, const BaseContainer &msg, BaseContainer &result);
	Int32						(*GuiCommand								)(GvNodeGUI *gui, Int32 id);
	void						(*GuiSelectAllNodes					)(GvNodeGUI *gui, GvNode *node, Bool select_state, Bool add_to_selection);
	void						(*GuiRemoveAllSelectedNodes	)(GvNodeGUI *gui, GvNode *node);
	void						(*GuiSelectNode							)(GvNodeGUI *gui, GvNode *node, Bool select_state, Bool add_to_selection, Bool send_message);
	GvNode*					(*GuiGetNodeGlobal					)(GvNodeGUI *gui, Int32 x, Int32 y);
	GvNode*					(*GuiGetNodeLocal						)(GvNodeGUI *gui, GvNode *node, Int32 x, Int32 y);
	Bool						(*GuiIsInNodeBody						)(GvNodeGUI *gui, GvNode *node, Int32 x, Int32 y);
	Bool						(*GuiIsInNodeHead						)(GvNodeGUI *gui, GvNode *node, Int32 x, Int32 y);
	void						(*GuiRedraw									)(GvNodeGUI *gui);
	GeUserArea*			(*GuiGetUserArea						)(GvNodeGUI *gui);
	GvNodeMaster*		(*GuiGetMaster							)(GvNodeGUI *gui);
	GeDialog*				(*GuiGetDialog							)(GvNodeGUI *gui);
	void						(*GuiDisableSelected				)(GvNodeGUI *gui, GvNode *node, Bool disable_state);
	void						(*GuiSetPrefs								)(GvNodeGUI *gui, const BaseContainer &bc);
	void						(*GuiGetPrefs								)(GvNodeGUI *gui, BaseContainer &bc);
	void						(*GuiSetNodePosGlobal				)(GvNodeGUI *gui, GvNode *node, Int32 x, Int32 y, Bool center);
	Bool						(*GuiNodeContextMenu				)(GvNodeGUI *gui, GvNode *node);
	void						(*GuiSetFocusEx							)(GvNodeGUI *gui, GvNode *node);
	void						(*GuiSetNodePos							)(GvNodeGUI *gui, GvNode *node, Int32 x, Int32 y);
	void						(*GuiSetNodeSize						)(GvNodeGUI *gui, GvNode *node, Int32 width, Int32 height);
	void						(*GuiOptimizeNode						)(GvNodeGUI *gui, GvNode *node);
	void						(*GuiShowAllNodes						)(GvNodeGUI *gui, GvNode *node);
	void						(*GuiCenterNodes						)(GvNodeGUI *gui, GvNode *node);
	void						(*GuiAlignNodesToUpperLeft	)(GvNodeGUI *gui, GvNode *node);
	void						(*GuiGetZoom								)(GvNodeGUI *gui, GvNode *node, Float &zoom);
	void						(*GuiSetFocus								)(GvNodeGUI *gui, GvNode *node, Bool activate);
};


////////////////////////////////
// GvNode functions

struct C4D_GvNode
{
	void						(*Redraw										)(GvNode *gn);
	GvPort*					(*AddPort										)(GvNode *gn, GvPortIO io, Int32 id, GvPortFlags flags, Bool message);
	Bool						(*AddPortIsOK								)(GvNode *gn, GvPortIO io, Int32 id);
	Bool						(*SetPortType								)(GvNode *gn, GvPort *port, Int32 id);
	Bool						(*ResetPortType							)(GvNode *gn, Int32 id);
	void						(*RemovePort								)(GvNode *gn, GvPort *port, Bool message);
	Bool						(*RemovePortIsOK						)(GvNode *gn, GvPort *port);
	void						(*RemoveUnusedPorts					)(GvNode *gn, Bool message);
	GvPort*					(*AddConnection							)(GvNode *gn, GvNode *source_node, GvPort *source_port, GvNode *dest_node, GvPort *dest_port);
	void						(*RemoveNodeConnections			)(GvNode *gn);
	Int32						(*GetInPortCount						)(GvNode *gn);
	Int32						(*GetOutPortCount						)(GvNode *gn);
	GvPort*					(*GetInPort									)(GvNode *gn, Int32 index);
	GvPort*					(*GetOutPort								)(GvNode *gn, Int32 index);
	GvPort*					(*GetInPortMainID						)(GvNode *gn, Int32 id, Int32 &start);
	GvPort*					(*GetOutPortMainID					)(GvNode *gn, Int32 id, Int32 &start);
	GvPort*					(*GetInPortFirstMainID			)(GvNode *gn, Int32 id);
	GvPort*					(*GetOutPortFirstMainID			)(GvNode *gn, Int32 id);
	GvPort*					(*GetInPortSubID						)(GvNode *gn, Int32 id);
	GvPort*					(*GetOutPortSubID						)(GvNode *gn, Int32 id);
	GvNodeMaster*		(*GetNodeMaster							)(GvNode *gn);
	GvOperatorData*	(*GetOperatorData						)(GvNode *gn);
	Int32						(*GetOperatorID							)(GvNode *gn);
	Int32						(*GetOwnerID								)(GvNode *gn);
	Bool						(*IsGroupNode								)(GvNode *gn);
	GvPort*					(*NodeCalculateInPortIndex	)(GvNode *gn, Int32 port_index, GvRun *run, GvCalc *calc);
	GvPort*					(*NodeCalculateOutPortIndex	)(GvNode *gn, Int32 port_index, GvRun *run, GvCalc *calc);
	BaseContainer*	(*GetOpContainerInstance		)(GvNode *gn);
	BaseContainer		(*GetOperatorContainer			)(GvNode *gn);
	void						(*SetOperatorContainer			)(GvNode *gn, const BaseContainer &bc);
	Bool						(*SetRecalculate						)(GvNode *gn, GvRun *run, Bool force_set);
	Int32						(*GetPortIndex							)(GvNode *gn, Int32 sub_id);
	GvPort*					(*GetPort										)(GvNode *gn, Int32 sub_id);
	GvPort*					(*NodeCalculateInPort				)(GvNode *gn, GvPort *port, GvRun *run, GvCalc *calc);
	GvPort*					(*NodeCalculateOutPort			)(GvNode *gn, GvPort *port, GvRun *run, GvCalc *calc);
	const String		(*OperatorGetDetailedText		)(GvNode *gn);
	const String		(*OperatorGetErrorString		)(GvNode *gn, Int32 error);
	Bool						(*OperatorSetData						)(GvNode *gn, GvDataType type, void *data, GvOpSetDataMode mode);
	Bool						(*OperatorIsSetDataAllowed	)(GvNode *gn, GvDataType type, void *data, GvOpSetDataMode mode);
	Bool						(*GetSelectState						)(GvNode *gn);
	Bool						(*GetFailureState						)(GvNode *gn);
	Bool						(*GetDisabledState					)(GvNode *gn);
	Bool						(*GetOpenState							)(GvNode *gn);
	void						(*SetOpenState							)(GvNode *gn, Bool state);
	Bool						(*GetLockState							)(GvNode *gn);
	void						(*SetLockState							)(GvNode *gn, Bool state);
	Bool						(*GetShowPortNamesState			)(GvNode *gn);
	void						(*SetShowPortNamesState			)(GvNode *gn, Bool state);
	void						(*OperatorGetIcon						)(GvNode *gn, IconData &dat);
	GvValue*				(*AllocCalculationHandler		)(GvNode *gn, Int32 main_id, GvCalc *calc, GvRun *run, Int32 singleport);
	void						(*FreeCalculationHandler		)(GvNode *gn, GvValue *&value);

	Bool						(*GetPortDescription				)(GvNode *gn, GvPortIO port, Int32 id, GvPortDescription *pd, Int32 privateflags);
	void						(*GetPortList								)(GvNode *bn, GvPortIO port, GvPortList &portlist, Int32 privateflags);
	const String		(*GetTitle									)(GvNode *bn, Int32 privateflags);
	void						(*SetTitle									)(GvNode *bn, const String &title, Int32 privateflags);
	Bool						(*CreateOperator						)(GvNode *bn, Int32 privateflags);

	Bool						(*CalculateRawData					)(GvNode *bn, GvValueID value_id, const void* const data1, const void* const data2, void *dest, GvValueFlags calculation, Float parm1);
};

////////////////////////////////
// GvPort functions

struct C4D_GvPort
{
	void						(*RemoveConnection					)(GvPort *port);
	Int32						(*GetNrOfConnections				)(GvPort *port);
	void						(*RemovePortConnections			)(GvPort *port);
	Bool						(*IsIncomingConnected				)(GvPort *port);
	Bool						(*GetIncomingDestination		)(GvPort *port, GvNode *&node, GvPort *&prt);
	Bool						(*GetIncomingSource					)(GvPort *port, GvNode *&node, GvPort *&prt);
	GvPortIO				(*GetIO											)(GvPort *port);
	void						(*SetMainID									)(GvPort *port, Int32 id);
	Int32						(*GetMainID									)(GvPort *port);
	void						(*SetUserID									)(GvPort *port, Int32 id);
	Int32						(*GetUserID									)(GvPort *port);
	Int32						(*GetSubID									)(GvPort *port);
	GvValueID				(*GetValueType							)(GvPort *port);
	void						(*SetVisible								)(GvPort *port, Bool v);
	Bool						(*GetVisible								)(GvPort *port);
	void						(*SetValid									)(GvPort *port, GvRun *r, Bool v);
	Bool						(*GetValid									)(GvPort *port, GvRun *r);
	void						(*SetCalculated							)(GvPort *port, GvRun *r);
	GvPort*					(*Calculate									)(GvPort *port, GvNode *bn, GvRun *r, GvCalc *c);
	Bool						(*SetRecalculate						)(GvPort *port, GvRun *r, Bool force_set);
	Bool						(*GetBool										)(GvPort *port, Bool *b, GvRun *r);
	Bool						(*GetInteger								)(GvPort *port, Int32 *i, GvRun *r);
	Bool						(*GetFloat										)(GvPort *port, Float *f, GvRun *r);
	Bool						(*GetVector									)(GvPort *port, Vector *v, GvRun *r);
	Bool						(*GetNormal									)(GvPort *port, Vector *n, GvRun *r);
	Bool						(*GetMatrix									)(GvPort *port, Matrix *m, GvRun *r);
	Bool						(*GetTime										)(GvPort *port, BaseTime *t, GvRun *r);
	Bool						(*GetData										)(GvPort *port, void *d, GvValueID type, GvRun *r);
	Bool						(*SetBool										)(GvPort *port, Bool b, GvRun *r);
	Bool						(*SetInteger								)(GvPort *port, Int32 i, GvRun *r);
	Bool						(*SetFloat										)(GvPort *port, Float f, GvRun *r);
	Bool						(*SetVector									)(GvPort *port, const Vector &v, GvRun *r);
	Bool						(*SetNormal									)(GvPort *port, const Vector &n, GvRun *r);
	Bool						(*SetMatrix									)(GvPort *port, const Matrix &m, GvRun *r);
	Bool						(*SetTime										)(GvPort *port, const BaseTime &t, GvRun *r);
	Bool						(*SetData										)(GvPort *port, const void* const d, GvValueID type, GvRun *r);
	const String		(*GetName										)(GvPort *port, GvNode *node);
	void						(*SetName										)(GvPort *port, const String &name);
	Bool						(*CopyRawData								)(GvPort *port, void *source, GvRun *r);
	Bool						(*CopyPortData							)(GvPort *port, GvPort *source, GvRun *r);
	Bool						(*CalculateRawData					)(GvPort *port, void *data, void *dest, GvRun *r, GvValueFlags calculation, Float parm1);
	Bool						(*CalculateRawRawData				)(GvPort *port, void *data1, void *dats2, void *dest, GvRun *r, GvValueFlags calculation, Float parm1);
	Bool						(*CalculatePortData					)(GvPort *port, GvPort *data, void *dest, GvRun *r, GvValueFlags calculation, Float parm1);
	Bool						(*GetString									)(GvPort *port, String *s, GvRun *r);
	Bool						(*SetString									)(GvPort *port, const String &s, GvRun *r);
	Bool						(*GetObject									)(GvPort *port, BaseList2D *&o, GvRun *r);
	Bool						(*SetObject									)(GvPort *port, const BaseList2D* const o, GvRun *r);
	Bool						(*CalculateRawDataRev				)(GvPort *port, void *data, void *dest, GvRun *r, GvValueFlags calculation, Float parm1);
	Bool						(*GetDataInstance						)(GvPort *port, const void *&d, GvValueID type, GvRun *r);
	Bool						(*GetTag										)(GvPort *port, BaseList2D *&t, GvRun *r, Int32 *index);
	Bool						(*SetTag										)(GvPort *port, const BaseList2D* const t, GvRun *r, Int32 index);
	Bool						(*GetMaterial								)(GvPort *port, BaseList2D *&m, GvRun *r, Int32 *index);
	Bool						(*SetMaterial								)(GvPort *port, const BaseList2D* const m, GvRun *r, Int32 index);
	Bool						(*GetInstance								)(GvPort *port, BaseList2D *&i, GvRun *r, Int32 *index);
	Bool						(*SetInstance								)(GvPort *port, const BaseList2D* const i, GvRun *r, Int32 index);
	Bool						(*GetObjectWithIndex				)(GvPort *port, BaseList2D *&o, GvRun *r, Int32 *index);
	Bool						(*SetObjectWithIndex				)(GvPort *port, const BaseList2D* const o, GvRun *r, Int32 index);
	GvDestination*	(*GetOutgoing								)(GvPort *port, Int32 index);
};

////////////////////////////////
// GvRun functions

struct C4D_GvRun
{
	void						(*SetError									)(GvRun *run, GvCalcError error);
	GvCalcError			(*GetError									)(GvRun *run);
	void						(*SetState									)(GvRun *run, GvCalcState state);
	GvCalcState			(*GetState									)(GvRun *run);
	void						(*IncrementID								)(GvRun *run);
	void						(*SetCalculationTable				)(GvRun *run, GvCalcTable *t);
	Bool						(*AddNodeToCalculationTable	)(GvRun *run, GvNode *node, Bool force_add);
	Bool						(*CalculateTable						)(GvRun *run, GvCalc *calc);
	Int32						(*GetCpuID									)(GvRun *run);
	Bool						(*IsIterationPath						)(GvRun *run);
};

////////////////////////////////
// GvCalcTable functions

struct C4D_GvCalcTable
{
	Bool						(*AddNodeToTable						)(GvCalcTable *table, GvRun *run, GvNode *node);
	void						(*ResetTable								)(GvCalcTable *table, GvRun *run);
	Int32						(*GetTableCount							)(GvCalcTable *table, GvRun *run);
	GvNode*					(*GetTableNode							)(GvCalcTable *table, GvRun *run, Int32 id);
};

////////////////////////////////
// GvQuery functions

struct C4D_GvQuery
{
	void						(*SetFlags									)(GvQuery *query, GvCalcFlags flags);
	GvCalcFlags			(*GetFlags									)(GvQuery *query);
	void						(*SetError									)(GvQuery *query, GvCalcError error);
	GvCalcError			(*GetError									)(GvQuery *query);
};

////////////////////////////////
// GvInit functions

struct C4D_GvInit
{
	void						(*SetError									)(GvInit *init, GvCalcError error);
	GvCalcError			(*GetError									)(GvInit *init);
};

////////////////////////////////
// GvValue functions

typedef Int32 GvValueType;
#define GV_MULTIPLE_PORTS		((GvValueType)(-1))

typedef Int32* GvIdTablePtr;
#define GV_EXISTING_PORTS		((GvIdTablePtr)(0x00000000))
#define GV_DEFINED_PORTS		((GvIdTablePtr)(Int)(-1))

struct C4D_GvValue
{
	Bool						(*Calculate									)(GvValue *value, GvNode *node, GvPortIO io, GvRun *r, GvCalc *c, Int32 index, BaseTime *time);
	Bool						(*IsConnected								)(GvValue *value, Int32 index);
	Bool						(*IsPort										)(GvValue *value);
	Int32						(*NrOfPorts									)(GvValue *value);
	GvValueID				(*GetValueID								)(GvValue *value);
	GvPort*					(*GetPort										)(GvValue *value, Int32 index);
	Int32						(*GetMainID									)(GvValue *value);
};

class iGvPortList;

struct C4D_GvPortList
{
	iGvPortList*		(*Alloc											)();
	void						(*Free											)(iGvPortList* &list);

	Int32						(iGvPortList::*GetCount			)(void) const;
	Bool						(iGvPortList::*Append				)(GvPortListEntry *e);
	Bool						(iGvPortList::*Remove				)(GvPortListEntry *e);
	GvPortListEntry*(iGvPortList::*GetIndex			)(Int32 i) const;
	void						(iGvPortList::*FlushAll			)(void);
};

////////////////////////////////
// Global function table

struct C4D_GraphView
{
	C4D_GvGlobals*		globals;
	C4D_GvWorld*			world;
	C4D_GvNodeGUI*		gui;
	C4D_GvNode*				node;
	C4D_GvPort*				port;
	C4D_GvNodeMaster*	master;
	C4D_GvRun*				run;
	C4D_GvCalcTable*	table;
	C4D_GvQuery*			query;
	C4D_GvInit*				init;
	C4D_GvValue*			value;
	C4D_GvPortList*		portlist;
};

////////////////////////////////

struct GvWrapper
{
	void *data;
};

////////////////////////////////

#endif //__C4D_GRAPHVIEW_H

////////////////////////////////
