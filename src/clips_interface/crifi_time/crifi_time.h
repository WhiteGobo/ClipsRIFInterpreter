#pragma once
/** crifi_time.h
 * Implements iso8601 parser and serializer.
 * Also offers methods to transform clipsvalues to <time.h>
 */

#include <time.h>
#include <clips.h>
#include <crifi_numeric.h>
#include <crifi_timedata.h>

typedef enum {
	CRIFI_TIME_DATETIMESTAMP_UNKNOWN_TYPE = -1,
	CRIFI_TIME_DATETIMESTAMP_DATETIME,
	CRIFI_TIME_DATETIMESTAMP_TIME,
	CRIFI_TIME_DATETIMESTAMP_DATE,
	CRIFI_TIME_DATETIMESTAMP_GYEARMONTH,
	CRIFI_TIME_DATETIMESTAMP_GYEAR,
	CRIFI_TIME_DATETIMESTAMP_GMONTHDAY,
	CRIFI_TIME_DATETIMESTAMP_GMONTH,
	CRIFI_TIME_DATETIMESTAMP_GDAY
} CRIFI_TIME_DATETIMESTAMP_TYPE;

typedef struct crifi_datetimestamp {
	CRIFI_TIME_DATETIMESTAMP_TYPE type;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int millisecond;
	int timezone_minute;
	bool is_negative_duration;
	bool no_timezone_data;
} DateTimeStamp;

typedef struct crifi_duration {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int millisecond;
	bool is_negative_duration;
} CrifiDuration;

typedef struct crifi_yearMonthDur {
	int year;
	int month;
	bool is_negative_duration;
} YearMonthDuration;

/*
typedef struct crifi_dayTimeDur {
	int year;
	int month;
	bool is_negative_duration;
} DayTimeDuration;
*/

//struct tm
//
//bool check_is_date(Environment *env, CLIPSValue val, DateTimeStamp *result);
//bool check_is_dateTime(Environment *env, CLIPSValue val, DateTimeStamp *result);
//bool check_is_dateTimeStamp(Environment *env, CLIPSValue val, DateTimeStamp *result);
//bool check_is_time(Environment *env, CLIPSValue val, DateTimeStamp *result);
bool check_is_dayTimeDuration(Environment *env, CLIPSValue val, DateTimeStamp *result);
bool check_is_yearMonthDuration(Environment *env, CLIPSValue val, YearMonthDuration *result);

bool crifi_time_clips_to_duration(Environment *env, CLIPSValue *val, CrifiDuration *result);
bool crifi_time_clips_to_time(Environment *env, CLIPSValue *val, DateTimeStamp *result);

/**
 * See `https://www.w3.org/TR/xpath-functions/#casting-to-durations`_
 */
void crifi_time_cast_as_yearMonthDuration(CrifiDuration *result);

/**
 * See `https://www.w3.org/TR/xpath-functions/#casting-to-durations`_
 */
void crifi_time_cast_as_dayTimeDuration(CrifiDuration *result);


bool crifi_time_cast_as_time(DateTimeStamp *time);
bool crifi_time_cast_as_dateTime(DateTimeStamp *time);
bool crifi_time_cast_as_date(DateTimeStamp *time);

CLIPSValue crifi_create_dayTimeDuration(Environment *env, bool invert, int day, int hour, int minute, int seconds, int milliseconds);
CLIPSValue crifi_create_yearMonthDuration(Environment *env, YearMonthDuration val);

CrifiDuration crifi_new_dayTimeDuration(bool invert, int day, int hour, int minute, int seconds, int milliseconds);
CrifiDuration crifi_new_yearMonthDuration(bool invert, int year, int month);

bool crifi_time_duration_to_clips(Environment *env, CrifiDuration *val, CLIPSValue *result);
bool crifi_time_time_to_clips(Environment *env, const DateTimeStamp *val, CLIPSValue *result);

CrifiDuration subtract_dateTime(DateTimeStamp val1, DateTimeStamp val2);

YearMonthDuration add_yearMonthDuration(YearMonthDuration val1, YearMonthDuration val2);
YearMonthDuration subtract_yearMonthDuration(YearMonthDuration val1, YearMonthDuration val2);
YearMonthDuration divide_yearMonthDuration(YearMonthDuration dur, float mult);

NumericValue divide_yearMonthDuration_by_yearMonthDuration(YearMonthDuration dur1, YearMonthDuration dur2);

CrifiDuration add_durations(CrifiDuration dur1, CrifiDuration dur2);
CrifiDuration subtract_durations(CrifiDuration dur1, CrifiDuration dur2);

CrifiDuration multiply_duration(CrifiDuration dur, double mult);
CrifiDuration divide_duration(CrifiDuration dur, double mult);
//DateTimeStamp multiply_dayTimeDuration(DateTimeStamp dur, float mult);
//DateTimeStamp divide_dayTimeDuration(DateTimeStamp dur, float mult);

DateTimeStamp add_duration_to_time(DateTimeStamp intime, CrifiDuration dur);
DateTimeStamp subtract_duration_from_time(DateTimeStamp intime, CrifiDuration dur);

NumericValue divide_dayTimeDuration_by_dayTimeDuration(DateTimeStamp dur1, DateTimeStamp dur2);
DateTimeStamp add_yearMonthDuration_to_dateTime(DateTimeStamp time, YearMonthDuration dur);
DateTimeStamp subtract_yearMonthDuration_from_dateTime(DateTimeStamp time, YearMonthDuration dur);


//DateTimeStamp add_dayTimeDuration_to_dateTime(DateTimeStamp time, DateTimeStamp dur);
//DateTimeStamp subtract_dayTimeDuration_from_dateTime(DateTimeStamp time, DateTimeStamp dur);


CLIPSValue crifi_create_dateTime(Environment *env, DateTimeStamp time);
CLIPSValue crifi_create_date(Environment *env, DateTimeStamp time);
CLIPSValue crifi_create_time(Environment *env, DateTimeStamp time);

bool equal_dateTime(DateTimeStamp left, DateTimeStamp right);
bool less_than_dateTime(DateTimeStamp left, DateTimeStamp right);
bool greater_than_dateTime(DateTimeStamp left, DateTimeStamp right);

bool greater_than_dayTimeDuration(DateTimeStamp inleft, DateTimeStamp inright);
bool less_than_dayTimeDuration(DateTimeStamp inleft, DateTimeStamp inright);
bool equal_dayTimeDuration(DateTimeStamp inleft, DateTimeStamp inright);

bool greater_than_yearMonthDuration(YearMonthDuration inleft, YearMonthDuration inright);
bool less_than_yearMonthDuration(YearMonthDuration inleft, YearMonthDuration inright);
bool equal_yearMonthDuration(YearMonthDuration left, YearMonthDuration right);
