/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

//---------------------------------------------------
#ifndef _C4D_DATETIMEPARSER_H_
#define _C4D_DATETIMEPARSER_H_

#ifdef __API_INTERN__
#include "customgui_datetime.h"
//#include "c4d_basetime.h"
#include "ge_string.h"
//#include "c4d_library.h"
//#include "c4d_gui.h"
#else
#include "c4d.h"
#include "customgui_datetime.h"
#endif
//
//class GeListNode;
//class Filename;
//class BaseBitmap;
//class BaseDocument;
//class String;
//class BaseSound;

#define C4D_DATETIMEPARSER_LIBRARY_ID		1025589

enum DATETIMEPARSERMODE
{
	DATETIMEPARSERMODE_DATE,
	DATETIMEPARSERMODE_TIME
} ENUM_END_LIST(DATETIMEPARSERMODE);

class DateTimeParser
{
private:
	DateTimeParser(void) {}
	~DateTimeParser(void) {}

public:
	// Maybe we need an empty constructor, but we leave them out for now

	Bool ParseString(const String &str, DateTime &result, DATETIMEPARSERMODE mode);
	String MakeString(const DateTime &dt, DATETIMEPARSERMODE mode);

	void SetFormatString(const String &sFormat, DATETIMEPARSERMODE mode);
	String GetFormatString(DATETIMEPARSERMODE mode);

	static DateTimeParser	*Alloc(void);
	static void Free(DateTimeParser *&dtp);
};

//---------------------------------------------------
//	---INTERNAL STUFF

class iDateTimeParser;

struct DateTimeParserLibrary : public C4DLibrary
{
//	DateTimeParser	(iDateTimeParser::*DateTimeParser)		(void);

	Bool					(iDateTimeParser::*ParseString)				(const String &str, DateTime &result, DATETIMEPARSERMODE mode);
	String				(iDateTimeParser::*MakeString)				(const DateTime &dt, DATETIMEPARSERMODE mode);

	void					(iDateTimeParser::*SetFormatString)		(const String &sFormat, DATETIMEPARSERMODE mode);
	String				(iDateTimeParser::*GetFormatString)		(DATETIMEPARSERMODE mode);

	iDateTimeParser* (*Alloc)														(void);
	void						(*Free)															(iDateTimeParser *&dtp);
};

#endif
