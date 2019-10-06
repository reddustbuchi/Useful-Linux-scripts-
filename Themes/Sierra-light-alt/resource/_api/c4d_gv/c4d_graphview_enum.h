/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_GRAPHVIEW_ENUM_H
#define __C4D_GRAPHVIEW_ENUM_H

////////////////////////////////
// predefined errors

enum GvError
{
	GV_IO_ERR_NONE = 0,
	GV_CALC_ERR_NONE = 0,

	GV_CALC_ERR_NO_MEMORY,
	GV_CALC_ERR_UNDEFINED,
	GV_CALC_ERR_UNKNOWN_TYPE,
	GV_CALC_ERR_NOT_IMPLEMENTED,
	GV_CALC_ERR_NOT_INITIALIZED,
	GV_CALC_ERR_NOT_VALID,
	GV_CALC_ERR_NO_OUTPORT,
	GV_CALC_ERR_NOT_CONNECTED,
	GV_CALC_ERR_NO_PORT,
	GV_CALC_ERR_DIVISION_BY_ZERO,
	GV_CALC_ERR_TYPE_MISMATCH,
	GV_CALC_ERR_INIT_FAILED,
	GV_CALC_ERR_QUERY_FAILED,
	GV_CALC_ERR_CALCULATION_FAILED,
	GV_CALC_ERR_PARAMETER,

	GV_IO_ERR_NO_MEMORY,
	GV_IO_ERR_FILE_NOT_FOUND,
	GV_IO_ERR_READ,
	GV_IO_ERR_WRITE,
	GV_IO_ERR_NOT_A_GROUPNODE,

	GV_NR_OF_SYSTEM_ERRORS,
	GV_CALC_ERR_USER_DEFINED = 10000
};

typedef GvError GvCalcError;
typedef GvError GvIoError;

enum GvValueFlags
{
	GV_CALC_NOP			= (0),						// no calculation
	GV_CALC_CLR			= (1 <<  0),			// clear					((TYPE*)dest)[cpu_id] = 0
	GV_CALC_SET			= (1 <<  1),			// set						((TYPE*)dest)[cpu_id] = source1[cpu_id]
	GV_CALC_ADD			= (1 <<  2),			// add						((TYPE*)dest)[cpu_id] = source1[cpu_id] + source2[cpu_id]
	GV_CALC_SUB			= (1 <<  3),			// subtract				((TYPE*)dest)[cpu_id] = source1[cpu_id] - source2[cpu_id]
	GV_CALC_MUL			= (1 <<  4),			// multiply				((TYPE*)dest)[cpu_id] = source1[cpu_id] * source2[cpu_id]
	GV_CALC_DIV			= (1 <<  5),			// divide					((TYPE*)dest)[cpu_id] = source1[cpu_id] / source2[cpu_id]
	GV_CALC_MOD			= (1 <<  6),			// modulo					((TYPE*)dest)[cpu_id] = source1[cpu_id] % source2[cpu_id]
	GV_CALC_CRS			= (1 <<  7),			// cross product	((TYPE*)dest)[cpu_id] = source1[cpu_id] x source2[cpu_id]
	GV_CALC_INV			= (1 <<  8),			// invert					((TYPE*)dest)[cpu_id] = 1/source1[cpu_id]
	GV_CALC_NEG			= (1 <<  9),			// negate					((TYPE*)dest)[cpu_id] = -source1[cpu_id]
	GV_CALC_CMP			= (1 << 10),			// compare				((Int32*)dest)[cpu_id] = source1[cpu_id] <,==,> source2[cpu_id] -> -1,0,1
	GV_CALC_EQU			= (1 << 12),			// equal					((Bool*)dest)[cpu_id] = source1[cpu_id] == source2[cpu_id]
	GV_CALC_NIL			= (1 << 13),			// is null				((Bool*)dest)[cpu_id] = source1[cpu_id] == 0
	GV_CALC_STR			= (1 << 14),			// print          *((String*)dest) = String(source1[cpu_id])
	GV_CALC_MIX			= (1 << 15),			// mix						((TYPE*)dest)[cpu_id] = source1[cpu_id] * parm1 + source2[cpu] * (1 - parm1)
	GV_CALC_ABS			= (1 << 16),			// absolute value	((TYPE*)dest)[cpu_id] = ABS(source1[cpu_id])
	GV_CALC_ADR			= (1 << 17),			// add real				((TYPE*)dest)[cpu_id] = source1[cpu_id] + parm1
	GV_CALC_SUR			= (1 << 18),			// subtract real	((TYPE*)dest)[cpu_id] = source1[cpu_id] - parm1
	GV_CALC_MUR			= (1 << 19),			// multiply	real	((TYPE*)dest)[cpu_id] = source1[cpu_id] * parm1
	GV_CALC_DIR			= (1 << 20),			// divide	real		((TYPE*)dest)[cpu_id] = source1[cpu_id] / parm1
	GV_CALC_DEF			= (1 << 21),			// set real				((TYPE*)dest)[cpu_id] = default value with id (Int32)parm1
	GV_CALC_DOT			= (1 << 22),			// dot product		((Float*)dest)[cpu_id] = source1[cpu_id] * source2[cpu_id]

	GV_CALC_STD			= (GV_CALC_CLR | GV_CALC_SET)	// must be implemented
};

enum GvDataOptions
{
	GV_DATA_OPTIONS_NONE								= (0),
	GV_DATA_OPTIONS_SHOW_UNDEFINED			= (1 << 0),
	GV_DATA_OPTIONS_HIDE_NOT_EDITABLE		= (1 << 1)
};

////////////////////////////////

#endif //__C4D_GRAPHVIEW_H

////////////////////////////////
