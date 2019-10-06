/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_DATE_EDIT_H_
#define _CUSTOMGUI_DATE_EDIT_H_

#define DATETIME_GUI      1009383		// ID of DateTime CustomGUI
#define DATETIME_DATA     1009398		// ID of DateTime CustomDataType

#define DATETIME_TIME_CONTROL			'dttc'    // true, if this is just a clock
#define DATETIME_DATE_CONTROL			'dtdc'    // true, if this is just a calendar
#define DATETIME_NOW_BUTTON				'dtnw'		// true, if there's a NOW button
#define DATETIME_NO_SECONDS				'dtns'    // true, if we don't want to show seconds in the GUI
#define DATETIME_SHOW_LABELS			'shlb'		// true, if we want to show the "Date" and "Time" labels
// Legacy (from pre-R12 DateTime CustomGUI)
#define DATETIME_COMPACT_MODE			'dtcm'    // *LEGACY* true, if you want a compact mode
/*#define DATETIME_COMPACT_OPEN			'dtco'*/    // *LEGACY* true, if the compact mode is open [REMOVED]
#define DATETIME_COLUMN						'dtco'    // *LEGACY* true, if the calendar and the clock should be in one column
#define DATETIME_TIME_NOW					'dttn'    // *LEGACY* true, if the clock has a "now" button
#define DATETIME_DATE_TODAY				'dtdt'    // *LEGACY* true, if the calendar has a "today" button
#define DATETIME_CLOCK_OPEN				'dtcl'    // *LEGACY* true, if the clock is visible
#define DATETIME_CALENDAR_OPEN		'dtca'    // *LEGACY* true, if the calendar is open
#define DATETIME_NO_DATE_COLLAPSE	'dtda'    // *LEGACY* true, if the date open/close arrow should be hidden
#define DATETIME_NO_TIME_COLLAPSE	'dtta'    // *LEGACY* true, if the time open/close arrow should be hidden

#include "customgui_base.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"
#include "c4d_customdatatype.h"


struct DateTime
{
	DateTime() { year=2000; month=day=1; hour=minute=second=0; }
	DateTime(Int32 t_year, Int32 t_month, Int32 t_day, Int32 t_hour, Int32 t_minute, Int32 t_second) : year(t_year), month(t_month), day(t_day), hour(t_hour), minute(t_minute), second(t_second)
	{	}

	Int32 year, month, day;
	Int32 hour, minute, second;

	Bool operator == (const DateTime &b) const;
	Bool operator != (const DateTime &b) const;
	Bool operator <= (const DateTime &b) const;
	Bool operator < (const DateTime &b) const;
	Bool operator >= (const DateTime &b) const;
	Bool operator > (const DateTime &b) const;
};

Int32 CompareDateTime(const DateTime &a, const DateTime &b);

class DateTimeControl : public BaseCustomGui<DATETIME_GUI>
{
private:
	DateTimeControl();
	~DateTimeControl();

public:
	DateTime GetDateTime() const;
	void SetDateTime(const DateTime &d, Bool bSetDate = true, Bool bSetTime = true);
};


class DateTimeData : public CustomDataType
{
private:
	DateTimeData();
	~DateTimeData();

public:
	static DateTimeData* Alloc();
	static void Free(DateTimeData *&pData);

	DateTime GetDateTime() const;
	void SetDateTime(const DateTime &d, Bool bSetDate = true, Bool bSetTime = true);
};

enum DayOfWeek
{
	Monday    = 0,
	Tuesday   = 1,
	Wednesday = 2,
	Thursday  = 3,
	Friday    = 4,
	Saturday  = 5,
	Sunday    = 6
} ENUM_END_LIST(DayOfWeek);

enum MonthOfYear
{
	January		= 1,
	February	= 2,
	March			= 3,
	April			= 4,
	May				= 5,
	June			= 6,
	July			= 7,
	August		= 8,
	September	= 9,
	October		= 10,
	November	= 11,
	December	= 12
} ENUM_END_LIST(MonthOfYear);

// generates a modified the Julian day. To get the correct Julian day,
// take the integer of this value and subtract .5
Float64 GetJulianDay(const DateTime &t);
DateTime FromJulianDay(Float64 j);
void GetDateTimeNow(DateTime& t);
void GetDateTimeNowGM(DateTime& t);

// converts local time to GMT depending on the OS time zone settings, tGMT is set to tLocal in case of an error
// returns false if the local date is before Jan 1 of 1970, 2.01 am or after Jan 18, 2038 7 pm
Bool LocalToGMTime(const DateTime &tLocal, DateTime &tGMT); // converts local time to GMT depending on the OS time zone settings, tGMT is set to tLocal in case of an error
Bool GMTimeToLocal(const DateTime &tGMT, DateTime &tLocal); // converts GMT to local time depending on the OS time zone settings, tLocal is set to tGMT in case of an error
DayOfWeek GetDayOfWeek(Int32 lYear, Int32 lMonth, Int32 lDay); // Monday = 0
String FormatTime(const char* pszFormat, const DateTime &t);
// Additions for new DateTime CustomGUI
Bool ParseTimeString(String timestr, Int32 &hour, Int32 &minute, Int32 &second); // Parses a time string (e.g. "12:34:56")
Bool ParseDateString(String datestr, Int32 &year, Int32 &month, Int32 &day); // Parses a date string (e.g. "1/4/2010")
String TimeToString(const DateTime &d, const Bool bShowSeconds = true); // Returns a time as a formatted string (e.g. "12:34:56")
String DateToString(const DateTime &d); // Returns a date as a formatted string (e.g. 1/4/2010)
String GetMonthName(const Int32 &month); // Returns the name of a month in the current language. For input values, see Enum MonthOfYear.
void ValidateDate(Int32 &year, Int32 &month, Int32 &day); // Invalid date values are corrected
void ValidateTime(Int32 &hour, Int32 &minute, Int32 &second); // Invalid time values are corrected



// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#ifndef _DATETIMECONTROL_INTERNAL_DEF_
	class iDateTimeControl : public iBaseCustomGui
	{
		iDateTimeControl(const BaseContainer &settings,CUSTOMGUIPLUGIN *plugin) : iBaseCustomGui(settings,plugin) { }
	};
	class iDateTimeData
	{
	};
#else
	class iDateTimeControl;
	class iDateTimeData;
#endif

struct DateTimechooserLib : public BaseCustomGuiLib
{
	DateTime      (iDateTimeControl::*GetDateTimeGUI)() const;
	void             (iDateTimeControl::*SetDateTimeGUI)(const DateTime &d, Bool bSetDate, Bool bSetTime);

	DateTime      (iDateTimeData::*GetDateTimeData)() const;
	void             (iDateTimeData::*SetDateTimeData)(const DateTime &d, Bool bSetDate, Bool bSetTime);

	Float64             (*GetJulianDay)(const DateTime &t);
	DateTime					(*FromJulianDay)(Float64 j);
	void              (*GetDateTimeNow)(DateTime& t);
	Bool              (*LocalToGMTime)(const DateTime &tLocal, DateTime &tGMT);
	Bool              (*GMTimeToLocal)(const DateTime &tGMT, DateTime &tLocal);
	DayOfWeek         (*GetDayOfWeek)(Int32 lYear, Int32 lMonth, Int32 lDay);

	DateTimeData*			(*DateTimeData_Alloc)();
	void							(*DateTimeData_Free)(DateTimeData *&pData);
	String						(*FormatTime)(const char* pszFormat, const DateTime &t);

	// Additions for new DateTime CustomGUI
	Bool							(*ParseTimeString)(String timestr, Int32 &hour, Int32 &minute, Int32 &second);
	Bool							(*ParseDateString)(String datestr, Int32 &year, Int32 &month, Int32 &day);
	String						(*TimeToString)(const DateTime &d, const Bool bShowSeconds);
	String						(*DateToString)(const DateTime &d);
	String						(*GetMonthName)(const Int32 &month);
	void							(*ValidateDate)(Int32 &year, Int32 &month, Int32 &day);
	void							(*ValidateTime)(Int32 &hour, Int32 &minute, Int32 &second);

};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#endif // _CUSTOMGUI_DATE_EDIT_H_
